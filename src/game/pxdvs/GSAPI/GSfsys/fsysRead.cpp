extern "C" int sprintf(char*, const char*, ...);
#include <game/pxdvs/GSAPI/GSfsys/fsysRead.hpp>
#include <game/pxdvs/GSAPI/GSfsys/fsysCache.hpp>
#include <dolphin/os.h>
extern "C" {
u8 GSdvdSeekAsync(void*, s32, void (*)(s32, void*));
void _fsysWorkSetTaskStatus(GSfsysRequest*, s32);
GSfsysRequest* _fsysInfo2Work(void*);
GSfsysBGWork* _fsysGetNewBGWork();
void _fsysAddBGWork(GSfsysBGWork*);
void _fsysResHeaderSetTaskStatus(GSfsysResource*, s32);
extern u32 _fsysBlockByteSize;
extern GSfsysDataType fsys_datatype[];
extern u32 fsys_datatype_number;
}
extern "C" {
static void _fsysSeekCallback(s32, void*);
static u32 _fsysReadData(GSfsysRequest*, GSfsysResource*, u32, u32, void*, u32, u32, void (*)(s32, void*), void (*)(u32));
static u8 _fsysAdjustReadFile(GSfsysRequest*);
static u8 _fsysExpandFile(GSfsysRequest*);
static void _fsysReadBlockHandling(GSfsysRequest*, GSfsysResource*);

}

extern "C" {
u8 GSdvdReadAsync(void*, void*, u32, u32, void (*)(s32, void*));
u8 _fsysReadCache(GSfsysRequest*, u32, void*, u32, u32, void (*)(u32));

}

struct GSfsysReadRequest : GSfsysRequest {
    u32 reserved30, reserved34, continuationID, cacheHeap;
};
struct GSfsysReadTransfer {
    u8 reserved[0x30];
    GSfsysRequest* request;
    GSfsysResource* resource;
};
extern "C" {
GSfsysReadTransfer* _fsysArq2ArqTrans(u32);
GSfsysRequest* _fsysGetNewWork();
u32 _fsysID2Index(GSfsysRequest*, u32);
void _fsysWriteCache(GSfsysRequest*, GSfsysResource*, void*, void*, u32, u32, void (*)(u32));
static void _fsysReadHeaderCallbackSub(GSfsysRequest*);
static u32 _fsysReadFile(GSfsysRequest*);
static void _fsysReadDataNext(GSfsysRequest*, GSfsysResource*);
static void _fsysReadHeaderCacheCallback(u32);
static void _fsysReadHeaderDvdCallback(s32, void*);
static void _fsysReadHeaderCacheWriteCallback(u32);
static void _fsysReadBlockCacheCallback(u32);
static void _fsysReadBlockDvdCallback(s32, void*);
static void _fsysReadBlockCacheWriteCallback(u32);
u32 _fsysReadDataExec(GSfsysRequest*, GSfsysResource*);

}
extern "C" {
u8 GSdvdOpenTest(const char*);
void* GSdvdOpen(const char*);
u32 GSdvdGetLength(void*);
void GSdvdClose(void*);
u32 _fsysStreamGetCacheSize();
u32 _fsysStreamGetReadBlockFlag(u32);
s32 _fsysGetActiveTask(s32);

}

extern "C" {
#pragma dont_inline on
void _fsysSeekRequest(GSfsysRequest* request) {
    if (!GSdvdSeekAsync(request->dvd, 0, _fsysSeekCallback)) _fsysWorkSetTaskStatus(request, -994);
}

void _fsysReadRequest(GSfsysRequest* request) {
    if (request->header && request->headerLoaded == 1) {
        _fsysReadHeaderCallbackSub(request);
        return;
    }
    BOOL interrupts;
retry:
    if ((u8)_fsysMemAllocHeader(request) != 1) {
        interrupts = OSDisableInterrupts();
        GSfsysRequest* work = _fsysGetNewWork();
        if (!work) {
            OSRestoreInterrupts(interrupts);
            if (work) _fsysWorkSetTaskStatus(request, -996);
            return;
        }
        *(u32*)((u8*)work + 0x14) = 0;
        OSRestoreInterrupts(interrupts);
        goto retry;
    }
    u32 cached;
    interrupts = OSDisableInterrupts();
    cached = 0;
    if (_fsysCheckCache(request->group, 0xFFFF) == 1) {
        _fsysSetLockCacheFlag(request->group, 0xFFFF, 1);
        cached = 1;
    }
    OSRestoreInterrupts(interrupts);
    _fsysReadData(request, 0, cached, 0xFFFF, request->header, request->directory->headerLength, 0, _fsysReadHeaderDvdCallback, _fsysReadHeaderCacheCallback);
}

static u32 _fsysReadData(GSfsysRequest* request, GSfsysResource* resource, u32 cached, u32 identifier, void* destination, u32 length, u32 offset, void (*dvdCallback)(s32, void*), void (*cacheCallback)(u32)) {
    request->identifier = identifier;
    if ((u8)cached == 1) {
        if (!_fsysReadCache(request, (u32)resource, destination, length, offset, cacheCallback)) {
            _fsysWorkSetTaskStatus(request, -996);
            return 0;
        }
    } else if (resource && resource->dvd) {
        if (!GSdvdReadAsync(resource->dvd, destination, length, offset, dvdCallback)) {
            _fsysWorkSetTaskStatus(request, -996);
            return 0;
        }
    } else {
        if (resource) offset += resource->offset;
        if (!GSdvdReadAsync(request->dvd, destination, length, offset, dvdCallback)) {
            _fsysWorkSetTaskStatus(request, -996);
            return 0;
        }
    }
    return 1;
}

static void _fsysReadHeaderCacheCallback(u32 token) {
    GSfsysReadTransfer* transfer = _fsysArq2ArqTrans(token);
    if (transfer) _fsysReadHeaderCallbackSub(transfer->request);
}

static void _fsysReadHeaderDvdCallback(s32 result, void* info) {
    GSfsysRequest* request = _fsysInfo2Work(info);
    if (request) {
        if (result < 0) { _fsysWorkSetTaskStatus(request, -996); return; }
        void* cache = _fsysMemAllocCache(request, 0xFFFF, request->directory->headerLength, ((GSfsysReadRequest*)request)->cacheHeap);
        if (cache) _fsysWriteCache(request, 0, request->header, cache, request->directory->headerLength, 0, _fsysReadHeaderCacheWriteCallback);
        _fsysReadHeaderCallbackSub(request);
    }
}

static void _fsysReadHeaderCacheWriteCallback(u32) {}

static void _fsysReadHeaderCallbackSub(GSfsysRequest* request) {
    BOOL interrupts = OSDisableInterrupts();
    request->headerLoaded = 1;
    switch (request->state) {
    case 3: break;
    case 4:
    case 1:
        if (_fsysID2Index(request, request->resourceID) != 0xFFFF) {
            request->readIndex = _fsysID2Index(request, request->resourceID);
            request->expandIndex = request->readIndex;
        }
        _fsysReadFile(request);
        break;
    case 2:
        if (_fsysID2Index(request, request->resourceID) != 0xFFFF) {
            if (_fsysCheckCache(request->group, _fsysID2Index(request, request->resourceID)) == 1) {
                _fsysWorkSetTaskStatus(request, 10);
            } else {
                request->readIndex = _fsysID2Index(request, request->resourceID);
                request->expandIndex = request->readIndex;
                _fsysReadFile(request);
            }
        } else if (_fsysAdjustReadFile(request) == 1) _fsysReadFile(request);
        else _fsysWorkSetTaskStatus(request, 10);
        break;
    }
    OSRestoreInterrupts(interrupts);
}

static u32 _fsysReadFile(GSfsysRequest* request) {
    char path[128];
    if (request->cancelled == 1) {
        _fsysWorkSetTaskStatus(request, 10);
        return 0;
    }
    GSfsysResource* resource = _fsysGetResHeader(request, request->readIndex);
    if (resource) {
        char* name = (char*)request->header + resource->nameOffset;
        resource->readPosition = 0;
        resource->cache = 0;
        resource->readBlocks = 0;
        resource->expandBlocks = 0;
        resource->dvd = 0;
        resource->reserved3C = 0;
        resource->token = 0xFFFF;
        resource->flags &= 0xFF70FFF7;
        resource->flags |= 0x800;
        resource->streamBytes = 0;
        resource->streamFlags = 0;
        resource->streamPosition = 0;
        resource->loopStart = 0;
        resource->loopEnd = resource->length;
        if (request->state == 4 && (resource->dataType == 0x14 || resource->dataType == 0x16)) resource->flags |= 0x40000;
        if (_fsysGetHeader(request)->flags & 1) {
            sprintf(path, "debug/%s", name);
            if (GSdvdOpenTest(path) == 1) {
                resource->dvd = GSdvdOpen(path);
                resource->flags &= 0x7FFFFFFF;
                resource->length = GSdvdGetLength(resource->dvd);
                resource->expandedLength = resource->length;
            }
        }
        if (request->state != 4 && _fsysCheckCache(request->group, request->readIndex) == 1) {
            resource->flags |= 0x20000;
            _fsysSetLockCacheFlag(request->group, request->readIndex, 1);
        }
        s32 state = request->state;
        if ((state == 1 || (state == 4 && (resource->flags & 0x40000))) && _fsysExpandFile(request) == 0) return 0;
        return _fsysReadDataExec(request, resource);
    }
    return (u32)resource;
}

u32 _fsysReadDataExec(GSfsysRequest* request, GSfsysResource* resource) {
    BOOL interrupts = OSDisableInterrupts();
    if (request->state == 4 && !(resource->flags & 0x80000)) {
        u32 type = resource->dataType;
        if (type != 0x14 && type != 0x16) {
            GSfsysResource* first;
            if (_fsysID2Index(request, request->resourceID) != 0xFFFF) first = _fsysGetResHeader(request, _fsysID2Index(request, request->resourceID));
            else first = _fsysGetResHeader(request, 0);
            if (!first) {
                _fsysResHeaderSetTaskStatus(resource, 3);
                OSRestoreInterrupts(interrupts);
                return 0;
            }
            if (!(first->flags & 8)) {
                _fsysResHeaderSetTaskStatus(resource, 3);
                OSRestoreInterrupts(interrupts);
                return 0;
            }
            GSfsysDataType* dataType = _fsysGetDataType(resource->dataType);
            if (dataType->begin) dataType->begin(request->group, resource->identifier, resource->length);
            resource->flags |= 0x80000;
        }
    }
    GSfsysBlock* block = _fsysAllocBlock();
    if (!block) {
        _fsysResHeaderSetTaskStatus(resource, 3);
        OSRestoreInterrupts(interrupts);
        return 0;
    }
    _fsysResHeaderSetTaskStatus(resource, 1);
    block->length = resource->readPosition;
    _fsysAddBlock(&resource->readBlocks, block);
    u32 position;
    u32 cached = (resource->flags >> 17) & 1;
    position = resource->readPosition;
    u32 result = _fsysReadData(request, resource, cached, request->readIndex, resource->readBlocks->data, _fsysGetTransLength(resource->length, position), position, _fsysReadBlockDvdCallback, _fsysReadBlockCacheCallback);
    OSRestoreInterrupts(interrupts);
    return result;
}

static void _fsysReadBlockCacheCallback(u32 token) {
    GSfsysReadTransfer* transfer = _fsysArq2ArqTrans(token);
    if (transfer) {
        GSfsysRequest* request;
        GSfsysResource* resource = transfer->resource;
        request = transfer->request;
        _fsysReadBlockHandling(request, resource);
        _fsysReadDataNext(request, resource);
    }
}

static void _fsysReadBlockDvdCallback(s32 result, void* info) {
    u32 position;
    GSfsysRequest* request = _fsysInfo2Work(info);
    if (!request) return;
    if (result < 0) { _fsysWorkSetTaskStatus(request, -996); return; }
    GSfsysResource* resource = _fsysGetResHeader(request, request->readIndex);
    if (!resource) return;
    if (!(resource->flags & 0x10000)) {
        if (request->state == 4) {
            if (resource->flags & 0x40000) resource->cache = 0;
            else resource->cache = _fsysMemAllocCache(request, request->readIndex, _fsysStreamGetCacheSize(), ((GSfsysReadRequest*)request)->cacheHeap);
        } else resource->cache = _fsysMemAllocCache(request, request->readIndex, resource->length, ((GSfsysReadRequest*)request)->cacheHeap);
    }
    resource->flags |= 0x10000;
    if (resource->cache) {
        if (request->state == 4) position = resource->streamPosition;
        else position = resource->readPosition;
        _fsysWriteCache(request, resource, resource->readBlocks->data, resource->cache, _fsysGetTransLength(resource->length, resource->readPosition), position, _fsysReadBlockCacheWriteCallback);
    } else _fsysReadBlockHandling(request, resource);
    _fsysReadDataNext(request, resource);
}

u32 _fsysGetTransLength(u32 length, u32 position) {
    u32 remaining = length - position;
    if (remaining > _fsysBlockByteSize) remaining = _fsysBlockByteSize;
    return (remaining + 31) & ~31;
}

static void _fsysReadBlockCacheWriteCallback(u32 token) {
    GSfsysReadTransfer* transfer = _fsysArq2ArqTrans(token);
    if (transfer) _fsysReadBlockHandling(transfer->request, transfer->resource);
}

static void _fsysReadBlockHandling(GSfsysRequest* request, GSfsysResource* resource) {
    s32 state = request->state;
    if ((state == 1 || (state == 4 && (resource->flags & 0x40000))) && request->cancelled != 1) {
        _fsysMoveBlock(&resource->readBlocks, &resource->expandBlocks);
        return;
    }
    _fsysFreeBlock(&resource->readBlocks, 0);
}

static void _fsysReadDataNext(GSfsysRequest* request, GSfsysResource* resource) {
    resource->readPosition += _fsysBlockByteSize;
    if (request->state == 4 && !(resource->flags & 0x40000)) {
        resource->streamBytes += _fsysBlockByteSize;
        resource->streamFlags |= _fsysStreamGetReadBlockFlag(resource->streamPosition);
        resource->streamPosition += _fsysBlockByteSize;
        if (resource->streamPosition >= _fsysStreamGetCacheSize()) resource->streamPosition = 0;
        if (request->cancelled == 1) { _fsysWorkSetTaskStatus(request, 10); return; }
        if (resource->readPosition >= resource->loopEnd) {
            if (resource->flags & 0x800) { _fsysResHeaderSetTaskStatus(resource, 2); return; }
            if (resource->readPosition < _fsysStreamGetCacheSize()) {
                resource->flags |= 0x800000;
                _fsysResHeaderSetTaskStatus(resource, 2);
                resource->streamFlags = -1;
                return;
            }
            resource->readPosition = resource->loopStart;
        }
        if (resource->streamBytes >= _fsysStreamGetCacheSize()) { _fsysResHeaderSetTaskStatus(resource, 5); return; }
        s32 active = _fsysGetActiveTask(2);
        s32 activeRead = _fsysGetActiveTask(1);
        if (activeRead + active != 0) { _fsysResHeaderSetTaskStatus(resource, 5); return; }
    } else if (resource->readPosition >= resource->length) {
        if (resource->dvd) {
            void* dvd = resource->dvd;
            resource->dvd = 0;
            GSdvdClose(dvd);
        }
        if (request->state == 4 && (s32)((GSfsysReadRequest*)request)->continuationID != 0) request->readIndex = _fsysID2Index(request, ((GSfsysReadRequest*)request)->continuationID);
        else {
            if (_fsysID2Index(request, request->resourceID) != 0xFFFF) { _fsysWorkSetTaskStatus(request, 10); return; }
            ++request->readIndex;
        }
        GSfsysHeader* header = _fsysGetHeader(request);
        if (request->readIndex >= header->fileCount) { _fsysWorkSetTaskStatus(request, 10); return; }
        _fsysReadFile(request);
        return;
    }
    _fsysReadDataExec(request, resource);
}

GSfsysResource* _fsysGetResHeader(GSfsysRequest* request, u32 index) {
    GSfsysHeader* header = _fsysGetHeader(request);
    if (!header) return 0;
    if (index >= header->fileCount) return 0;
    u32* table = (u32*)((u8*)header + header->fileTableOffset);
    return (GSfsysResource*)((u8*)header + table[index]);
}

GSfsysHeader* _fsysGetHeader(GSfsysRequest* request) {
    GSfsysHeader* header = request->header;
    if (!header) return 0;
    if (request->headerLoaded == 0) {
        header = 0;
        return header;
    }
    return header;
}

static u8 _fsysAdjustReadFile(GSfsysRequest* request) {
    GSfsysHeader* header = _fsysGetHeader(request);
    u16 index = 0;
    while (index < header->fileCount) {
        if (!_fsysCheckCache(request->group, index)) break;
        ++index;
    }
    if (index >= header->fileCount) return 0;
    request->readIndex = index;
    return 1;
}

static u8 _fsysExpandFile(GSfsysRequest* request) {
    GSfsysHeader* header = _fsysGetHeader(request);
    if (request->expandIndex >= header->fileCount) return 0;
    GSfsysResource* resource = _fsysGetResHeader(request, request->expandIndex);
    if (!resource) return 0;
    ++request->expandIndex;
    return _fsysExpandFileExec(request, resource);
}

u8 _fsysExpandFileExec(GSfsysRequest* request, GSfsysResource* resource) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysBGWork* work = _fsysGetNewBGWork();
    if (!work) {
        _fsysResHeaderSetTaskStatus(resource, 4);
        OSRestoreInterrupts(interrupts);
        return 0;
    }
    _fsysResHeaderSetTaskStatus(resource, 1);
    work->resource = resource;
    work->request = request;
    if (resource->flags & 0x80000000) work->compressed = 1;
    else work->compressed = 0;
    _fsysAddBGWork(work);
    OSRestoreInterrupts(interrupts);
    return 1;
}

GSfsysDataType* _fsysGetDataType(u32 identifier) {
    GSfsysDataType* type = fsys_datatype;
    for (u32 i = 0; i < fsys_datatype_number; ++i, ++type) if (type->identifier == identifier) return type;
    return 0;
}

static void _fsysSeekCallback(s32 result, void* info) {
    GSfsysRequest* request = _fsysInfo2Work(info);
    if (request) {
        if (result < 0) { _fsysWorkSetTaskStatus(request, -994); return; }
        _fsysWorkSetTaskStatus(request, 11);
    }
}
#pragma dont_inline reset
}
