#ifndef _DOLPHIN_OSFASTCAST
#define _DOLPHIN_OSFASTCAST

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_GQR_F32 0x0000
#define OS_GQR_U8  0x0004
#define OS_GQR_U16 0x0005
#define OS_GQR_S8  0x0006
#define OS_GQR_S16 0x0007

#define OS_FASTCAST_U8  2
#define OS_FASTCAST_U16 3
#define OS_FASTCAST_S8  4
#define OS_FASTCAST_S16 5

// clang-format off
#ifdef __MWERKS__
static inline void OSInitFastCast(void) {
    asm {
        li   r3, OS_GQR_U8
        oris r3, r3, OS_GQR_U8
        mtspr GQR2, r3
        li   r3, OS_GQR_U16
        oris r3, r3, OS_GQR_U16
        mtspr GQR3, r3
        li   r3, OS_GQR_S8
        oris r3, r3, OS_GQR_S8
        mtspr GQR4, r3
        li   r3, OS_GQR_S16
        oris r3, r3, OS_GQR_S16
        mtspr GQR5, r3
    }
}

static inline f32 __OSu8tof32(register u8* in) {
    register f32 r;
    asm { psq_l r, 0(in), 1, OS_FASTCAST_U8 }
    return r;
}
static inline f32 __OSu16tof32(register u16* in) {
    register f32 r;
    asm { psq_l r, 0(in), 1, OS_FASTCAST_U16 }
    return r;
}
static inline f32 __OSs8tof32(register s8* in) {
    register f32 r;
    asm { psq_l r, 0(in), 1, OS_FASTCAST_S8 }
    return r;
}
static inline f32 __OSs16tof32(register s16* in) {
    register f32 r;
    asm { psq_l r, 0(in), 1, OS_FASTCAST_S16 }
    return r;
}

static inline void OSu8tof32(u8* in, volatile f32* out) { *out = __OSu8tof32(in); }
static inline void OSu16tof32(u16* in, volatile f32* out) { *out = __OSu16tof32(in); }
static inline void OSs8tof32(s8* in, volatile f32* out) { *out = __OSs8tof32(in); }
static inline void OSs16tof32(s16* in, volatile f32* out) { *out = __OSs16tof32(in); }

static inline u8 __OSf32tou8(register f32 in) {
    f32 a;
    register f32* ptr = &a;
    u8 r;
    asm { psq_st in, 0(ptr), 1, OS_FASTCAST_U8 }
    r = *(u8*)ptr;
    return r;
}
static inline u16 __OSf32tou16(register f32 in) {
    f32 a;
    register f32* ptr = &a;
    u16 r;
    asm { psq_st in, 0(ptr), 1, OS_FASTCAST_U16 }
    r = *(u16*)ptr;
    return r;
}
static inline s8 __OSf32tos8(register f32 in) {
    f32 a;
    register f32* ptr = &a;
    s8 r;
    asm { psq_st in, 0(ptr), 1, OS_FASTCAST_S8 }
    r = *(s8*)ptr;
    return r;
}
static inline s16 __OSf32tos16(register f32 in) {
    f32 a;
    register f32* ptr = &a;
    s16 r;
    asm { psq_st in, 0(ptr), 1, OS_FASTCAST_S16 }
    r = *(s16*)ptr;
    return r;
}

// GQR6 is configured by the game (s16 with a scale) rather than OSInitFastCast.
static inline s16 __OSf32tos16_q6(register f32 in) {
    f32 a;
    register f32* ptr = &a;
    s16 r;
    asm { psq_st in, 0(ptr), 1, 6 }
    r = *(s16*)ptr;
    return r;
}
static inline void __OSf32tos16x2_q6(register f32* in, register s16* out) {
    register f32 v;
    asm {
        psq_l  v, 0(in), 0, 0
        psq_st v, 0(out), 0, 6
    }
}

static inline void OSf32tou8(f32* in, volatile u8* out) { *out = __OSf32tou8(*in); }
static inline void OSf32tou16(f32* in, volatile u16* out) { *out = __OSf32tou16(*in); }
static inline void OSf32tos8(f32* in, volatile s8* out) { *out = __OSf32tos8(*in); }
static inline void OSf32tos16(f32* in, volatile s16* out) { *out = __OSf32tos16(*in); }
#endif
// clang-format on

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSFASTCAST
