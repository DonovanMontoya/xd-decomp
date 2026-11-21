#ifndef GSGFX_FIFO_HPP
#define GSGFX_FIFO_HPP

#include <dolphin/types.h>

struct GSgfx_GCFifoObj {
    void* base;
    void* end;
    u32 size;
    u32 high;
    u32 low;
    void* read;
    void* write;
    s32 count;
    u8 wrap;
    u8 link;
    u8 pad22[0x2a];
    u32 complete;
    u8 pad50[0x30];
};

extern "C" void GSgfxGPUSetFifoWritePtr__FP15GSgfx_GCFifoObjPv(GSgfx_GCFifoObj*, void*);

#endif
