#include "game/maximum/GSAPI/baselib/initialize.h"
extern "C" {
typedef HSD_MemoryCallbacks MemCallbacks;

static MemCallbacks __mem_cb;

extern void __assert(const char *, int, const char *);

void *HSD_Alloc(unsigned int size) {
    return __mem_cb.alloc(size, 0x20, 0);
}

void HSD_Free(void *ptr) {
    __mem_cb.free(ptr);
}

int _HSD_MemCheckOwn(void *ptr) {
    return __mem_cb.check_own(ptr);
}

void _HSD_MemSetCallbacks(MemCallbacks *callbacks, unsigned int size) {
    if (size != sizeof(MemCallbacks)) {
        __assert("memory.c", 19, "size == sizeof(__mem_cb)");
    }
    __mem_cb = *callbacks;
}
}
