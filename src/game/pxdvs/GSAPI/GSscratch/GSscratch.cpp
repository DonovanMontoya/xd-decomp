#include <game/pxdvs/GSAPI/GSscratch/GSscratch.hpp>
#include <dolphin/os.h>

struct ScratchBlock {
    u8 start, count;
    GSscratchCallback callback;
};
static ScratchBlock _blockTable[32];
static u32 _stackSize;
static u32 _entriesQueued;
static u8* _scratchPadBase;
static u32 _scratchInitLR;
static u8 _scratchInvalid;
static u32 _blockMap;

#pragma dont_inline on
extern "C" void GSscratchSetValid() {
    if (_scratchInvalid) {
        s32 i = 31;
        ScratchBlock* block = _blockTable;
        do {
            if (block->start != 255 && block->callback)
                block->callback(1, _scratchPadBase + (block->start << 9), block->count);
        } while (++block, i--);
        _scratchInvalid = 0;
    }
}
#pragma dont_inline reset
#pragma dont_inline on
extern "C" void GSscratchSetInvalid() {
    if (_scratchInvalid != 1) {
        s32 i = 31;
        ScratchBlock* block = _blockTable;
        do {
            if (block->start != 255 && block->callback)
                block->callback(0, _scratchPadBase + (block->start << 9), block->count);
        } while (++block, i--);
        _scratchInvalid = 1;
    }
}
#pragma dont_inline reset
extern "C" u8 GSscratchIsPtr(void* pointer) {
    return ((u32)pointer & 0xf0000000) == ((u32)_scratchPadBase & 0xf0000000);
}
extern "C" void GSscratchWaitForCompletion() {
    LCQueueWait(_entriesQueued);
    _entriesQueued = 0;
}
extern "C" s32 GSscratchStore(void* destination, void* source, u32 bytes) {
    if (LCQueueLength() >= 15) return 1;
    if (((u32)source & 31) || ((u32)destination & 31)) return 2;
    if (bytes & 31) return 2;
    _entriesQueued += LCStoreData(destination, source, bytes);
    return 0;
}

static inline ScratchBlock* scratchFindBlock(u8 start) {
    ScratchBlock* block = _blockTable;
    for (s32 i = 0; i < 32; ++block, ++i) {
        if (block->start == start) return block;
    }
    return 0;
}
static inline ScratchBlock* scratchFindFreeBlock()
{
    return scratchFindBlock(0xFF);
}
static inline u32 scratchRangeMask(u8 start, u8 count) {
    u32 occupied = 0;
    u32 bit = 0x80000000;
    while (start--) bit >>= 1;
    while (count--) {
        occupied <<= 1;
        if (bit) {
            if (_blockMap & bit) occupied |= 1;
            bit >>= 1;
        } else occupied |= 1;
    }
    return occupied;
}
extern "C" void GSscratchFree(void* pointer) {
    u8 start = ((u32)pointer - (u32)_scratchPadBase) >> 9;
    ScratchBlock* block = scratchFindBlock(start);
    if (block) {
        u32 bit;
        u8 index;
        u8 count;
        count = block->count;
        bit = 0x80000000;
        index = block->start;
        while (index--) bit >>= 1;
        u32 map = _blockMap;
        while (count--) {
            map &= ~bit;
            bit >>= 1;
        }
        _blockMap = map;
        block->start = 255;
    }
}
static inline void scratchSetRange(u8 index, u8 count)
{
    u32 mask;
    u32 map;

    mask = 0x80000000;
    while (index-- != 0) {
        mask >>= 1;
    }
    map = _blockMap;
    while (count-- != 0) {
        map |= mask;
        mask >>= 1;
    }
    _blockMap = map;
}
extern "C" void* GSscratchAlloc(u8 blocks, GSscratchCallback callback)
{
    u32 scanMask;
    u32 occupied;
    u8 shift;
    u8 remaining;
    u32 map;
    u8 candidate;
    ScratchBlock* entry;

    if (_scratchInvalid == 1) {
        return 0;
    }
    if (blocks == 0 || blocks > 32) {
        return 0;
    }

    map = _blockMap;
    for (candidate = 0; candidate < 32; candidate++) {
        remaining = blocks;
        shift = candidate;
        occupied = 0;
        scanMask = 0x80000000;
        while (shift-- != 0) {
            scanMask >>= 1;
        }
        while (remaining-- != 0) {
            occupied <<= 1;
            if (scanMask != 0) {
                if ((map & scanMask) != 0) {
                    occupied |= 1;
                }
                scanMask >>= 1;
            } else {
                occupied |= 1;
            }
        }
        if (occupied == 0) {
            if ((entry = scratchFindFreeBlock()) == 0) {
                return 0;
            }

            entry->start = candidate;
            entry->count = blocks;
            entry->callback = callback;
            scratchSetRange(candidate, blocks);
            return (u8*)_scratchPadBase + entry->start * 0x200;
        }
    }
    return 0;
}

extern "C" asm void GSscratchInit(u8 stackBlocks) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r1
    stw r30, 0x8(r1)
    mr r30, r3
    mflr r3
    li r7, 0x0
    stw r3, _scratchInitLR
    stw r7, _blockMap
    lis r4, _blockTable@ha
    li r0, 0x4
    addi r4, r4, _blockTable@l
    li r6, 0xff
    mtctr r0
initializeBlockTable:
    stbx r6, r4, r7
    addi r7, r7, 0x8
    stbx r6, r4, r7
    addi r7, r7, 0x8
    stbx r6, r4, r7
    addi r7, r7, 0x8
    stbx r6, r4, r7
    addi r7, r7, 0x8
    stbx r6, r4, r7
    addi r7, r7, 0x8
    stbx r6, r4, r7
    addi r7, r7, 0x8
    stbx r6, r4, r7
    addi r7, r7, 0x8
    stbx r6, r4, r7
    addi r7, r7, 0x8
    bdnz initializeBlockTable
    bl LCEnable
    clrlslwi r0, r30, 24, 9
    lis r6, 0xe000
    clrlwi. r4, r30, 24
    stw r0, _stackSize
    stw r6, _scratchPadBase
    beq setValid
    mr r7, r30
    li r6, 0x0
    lis r4, 0x8000
    b testStartIndex
shiftStartBit:
    srwi r4, r4, 1
testStartIndex:
    clrlwi. r0, r6, 24
    subi r6, r6, 0x1
    bne shiftStartBit
    b testBlockCount
reserveBlock:
    lwz r0, _blockMap
    or r0, r0, r4
    srwi r4, r4, 1
    stw r0, _blockMap
testBlockCount:
    clrlwi. r0, r7, 24
    subi r7, r7, 0x1
    bne reserveBlock
    li r0, 0x0
    lis r4, _blockTable@ha
    stbu r0, _blockTable@l(r4)
    stb r30, 0x1(r4)
setValid:
    li r4, 0x0
    clrlwi. r0, r30, 24
    stb r4, _scratchInvalid
    bne switchStack
    li r3, 0x1
    b restoreStack
switchStack:
    lwz r3, _scratchPadBase
    lwz r5, _stackSize
    add r3, r3, r5
    subi r1, r3, 0x8
    li r3, -0x1
    stw r3, 0x0(r1)
    lwz r3, _scratchInitLR
    mtlr r3
    blr
    li r3, 0x1
restoreStack:
    mr r10, r31
    lwz r31, 0xc(r31)
    lwz r30, 0x8(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
}
