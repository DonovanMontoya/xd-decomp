#include <game/maximum/GSAPI/baselib/objalloc.h>

extern void* HSD_Alloc(unsigned int);
extern void HSD_Free(void*);
extern int HSD_GetNbBits(unsigned int);
extern void __assert(const char*, int, const char*);
extern void* memset(void*, int, unsigned int);

typedef struct ObjHeap {
    unsigned int top;
    unsigned int curr;
    unsigned int size;
    unsigned int remain;
} ObjHeap;

static ObjHeap obj_heap = {0, 0, ~0U, ~0U};
static HSD_ObjAllocData* alloc_datas;

void _HSD_ObjAllocForgetMemory(void*, void*);
void HSD_ObjFree(HSD_ObjAllocData* data, void* object);
void* HSD_ObjAlloc(HSD_ObjAllocData* data);
void HSD_ObjSetHeap(unsigned int size, void* ptr);

void HSD_ObjSetHeap(unsigned int size, void* ptr);
void HSD_ObjAllocInit(HSD_ObjAllocData* data, unsigned int size, unsigned int align);
void* HSD_ObjAlloc(HSD_ObjAllocData* data);
void HSD_ObjFree(HSD_ObjAllocData* data, void* object);
void _HSD_ObjAllocForgetMemory(void*, void*);

void HSD_ObjSetHeap(unsigned int size, void* ptr)
{
    obj_heap.curr = (unsigned int) ptr;
    obj_heap.top = (unsigned int) ptr;
    obj_heap.remain = size;
    obj_heap.size = size;
}

void* HSD_ObjAlloc(HSD_ObjAllocData* data)
{
    unsigned int used;
    if ((data->num_limit_flag && data->used >= data->num_limit)) {
        return 0;
    }
    data->used += 1;
    used = data->used;
    if (used > data->peak) {
        data->peak = used;
    }
    return HSD_Alloc(data->size);
}

void HSD_ObjFree(HSD_ObjAllocData* data, void* object)
{
    unsigned int used = data->used;
    data->used = used - 1;
    HSD_Free(object);
}

void HSD_ObjAllocInit(HSD_ObjAllocData* data, unsigned int size, unsigned int align)
{
    HSD_ObjAllocData** link;
    HSD_ObjAllocData* cur;

    if (data == 0) {
        __assert("objalloc.c", 0x17D, "data");
    }
    if (data != 0) {
        link = &alloc_datas;
        while ((cur = *link) != 0) {
            if (cur == data) {
                *link = cur->next;
            } else {
                link = &cur->next;
            }
        }
    } else {
        alloc_datas = 0;
    }
    memset(data, 0, sizeof(*data));
    data->num_limit = -1;
    data->heap_limit_size = 0;
    data->heap_limit_num = -1;
    if (align > 0x20) {
        __assert("objalloc.c", 0x188, "align <= 32");
    }
    if (HSD_GetNbBits(align) != 1) {
        __assert("objalloc.c", 0x189, "HSD_GetNbBits(align) == 1");
    }
    data->align = align;
    data->size = (size + data->align - 1) & ~(data->align - 1);
    data->next = alloc_datas;
    alloc_datas = data;
}

void _HSD_ObjAllocForgetMemory(void*, void*)
{
    alloc_datas = 0;
}
