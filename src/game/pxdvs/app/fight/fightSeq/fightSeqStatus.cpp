#include <global.h>

extern "C" {
u8* fightSeq_GetWazaSeq();
void fightSeq_NextWazaSeq(u32);
s32 statusSetStatus(u8, s32, s32, s32, s32, s32);
s32 statusGetStatus(u8, s32, s32, s32, s32);
}

#define STATUS_ARGS(T) \
    u8* command = fightSeq_GetWazaSeq(); \
    s32* ptr2 = *(s32**)(command + 2); \
    u8 status = command[1]; \
    u8* ptr6 = *(u8**)(command + 6); \
    u16 type = *(u16*)(command + 0xA); \
    u8* ptrC = *(u8**)(command + 0xC); \
    T* result = *(T**)(command + 0x10); \
    s32 value2; \
    s32 value6; \
    s32 valueC; \
    if (ptr2 == 0) value2 = 0; else value2 = *ptr2; \
    if (ptr6 == 0) value6 = 0; else value6 = *ptr6; \
    if (ptrC == 0) valueC = 0; else valueC = *ptrC

extern "C" void WS_STATUS_SET32() {
    STATUS_ARGS(s32);
    statusSetStatus(status, value2, value6, type, valueC, *result);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_SET16() {
    STATUS_ARGS(u16);
    statusSetStatus(status, value2, value6, type, valueC, *result);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_SET8() {
    STATUS_ARGS(u8);
    statusSetStatus(status, value2, value6, type, valueC, *result);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_GET32() {
    STATUS_ARGS(s32);
    *result = statusGetStatus(status, value2, value6, type, valueC);
    fightSeq_NextWazaSeq(0x14);
}
#pragma peephole on
extern "C" void WS_STATUS_GET16() {
    STATUS_ARGS(u16);
    *result = statusGetStatus(status, value2, value6, type, valueC);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_GET8() {
    STATUS_ARGS(u8);
    *result = statusGetStatus(status, value2, value6, type, valueC);
    fightSeq_NextWazaSeq(0x14);
}

#pragma peephole reset
