static void HSD_SaveContext(void);

#include "game/maximum/GSAPI/baselib/debug.h"
#include <dolphin/os/OSContext.h>

extern void OSReport(const char*, ...);
extern void OSPanic(const char*, unsigned int, const char*, ...);
static unsigned char debug_context[0x2C8];
static void (*panic_func)(void*, ...);
void __assert(const char* file, unsigned int line, const char* expression)
{
    OSReport("assertion \"%s\" failed", expression);
    HSD_Panic(file, line, "");
}
void HSD_Panic(const char* file, unsigned int line, const char* message)
{
    if (panic_func != 0) {
        HSD_SaveContext();
        OSReport("%s in %s on line %d.\n", message, file, line);
        panic_func(debug_context);
    }
    OSPanic(file, line, message);
}

static asm void HSD_SaveContext(void)
{
    nofralloc
    mtsprg 0, r3
    lis r3, debug_context@ha
    addi r3, r3, debug_context@l
    stmw r0, 0x0(r3)
    mfsprg r4, 0
    stw r4, 0xc(r3)
    mfspr r4, GQR0
    stw r4, 0x1a4(r3)
    mfspr r4, GQR1
    stw r4, 0x1a8(r3)
    mfspr r4, GQR2
    stw r4, 0x1ac(r3)
    mfspr r4, GQR3
    stw r4, 0x1b0(r3)
    mfspr r4, GQR4
    stw r4, 0x1b4(r3)
    mfspr r4, GQR5
    stw r4, 0x1b8(r3)
    mfspr r4, GQR6
    stw r4, 0x1bc(r3)
    mfspr r4, GQR7
    stw r4, 0x1c0(r3)
    mfcr r4
    stw r4, 0x80(r3)
    mflr r4
    stw r4, 0x84(r3)
    mfctr r4
    stw r4, 0x88(r3)
    mfxer r4
    stw r4, 0x8c(r3)
    mfsrr0 r4
    stw r4, 0x198(r3)
    mfsrr1 r4
    stw r4, 0x19c(r3)
    lhz r4, 0x1a2(r3)
    ori r4, r4, 0x1
    sth r4, 0x1a2(r3)
    b OSFillFPUContext
}
