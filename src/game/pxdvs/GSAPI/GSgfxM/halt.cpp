#include <dolphin/types.h>

extern "C" {

void OSPanic(const char *file, int line, ...)
{
    (void)file;
    (void)line;
}

void GSgfxHalt(s32 exception, void *context, s32 dsisr, s32 dar, ...)
{
    (void)exception;
    (void)context;
    (void)dsisr;
    (void)dar;
}

void OSSetErrorHandler(s32 exception, void (*handler)(s32, void *, s32, s32, ...));
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32 enabled);
void DCFlushRange(void *addr, u32 nBytes);
void *memset(void *, int, u32);
void *memcpy(void *, const void *, u32);
extern s32 __OSFpscrEnableBits;
}

static u8 _haltOldDSIHandler[0x74];
static u8 _haltOldISIHandler[0x34];
static u8 _haltOldAlignmentHandler[0x34];
static u8 _haltOldProgramHandler[0x34];
static u8 _haltTex[0x80];
static u8 _haltContext[0x2C8];
static u8 _haltCallStack[0x3C];
static u8 _haltHandlerInstalled;
static s32 _haltExceptionType;

void _haltDSIHandler();
void _haltISIHandler();
void _haltAlignmentHandler();

void GSgfxHaltInit()
{
    memset(_haltContext, 0xFF, sizeof(_haltContext));
    OSSetErrorHandler(2, GSgfxHalt);
    OSSetErrorHandler(3, GSgfxHalt);
    OSSetErrorHandler(5, GSgfxHalt);
    OSSetErrorHandler(15, GSgfxHalt);
    __OSFpscrEnableBits = 16;
    OSSetErrorHandler(16, GSgfxHalt);
    s32 interrupts = OSDisableInterrupts();
    memcpy(_haltOldDSIHandler, (void *)0x80000300, 0x74);
    memcpy(_haltOldISIHandler, (void *)0x80000400, 0x34);
    memcpy(_haltOldAlignmentHandler, (void *)0x80000600, 0x34);
    memcpy(_haltOldProgramHandler, (void *)0x80000700, 0x34);
    memcpy((void *)0x80000300, (void *)_haltDSIHandler, 0x74);
    memcpy((void *)0x80000400, (void *)_haltISIHandler, 0x34);
    memcpy((void *)0x80000600, (void *)_haltAlignmentHandler, 0x34);
    DCFlushRange((void *)0x80000300, 0x1000);
    _haltHandlerInstalled = 1;
    OSRestoreInterrupts(interrupts);
}
