#ifndef GS_PSINTERPRET_H
#define GS_PSINTERPRET_H
#include "particle.h"
#include "game/maximum/GSAPI/baselib/mtx_base.h"
PSParticle* psInterpretParticle0(PSParticle*, PSParticle*);
typedef HSD_Mtx PSMtx;
void HSD_JObjSetMtxDirtySub(PSJObj*); PSJObj* HSD_JObjAlloc(void);

s32 U8ClampAdd(u8,f32); PSParticle* _psListGetNext(PSParticle*);

void PSMTXScale(PSMtx,f32,f32,f32); void PSMTXCopy(PSMtx,PSMtx); s32 PSMTXInverse(PSMtx,PSMtx);
f32 sinf(f32); f32 cosf(f32); f32 tanf(f32); f32 sqrtf(f32);
extern PSJObj* psPointJObj[8]; extern f32 __float_min[],__float_nan[],__float_epsilon[];
f64 fabs(f64);
typedef union PSByteFloat { u8 bytes[4]; f32 value; } PSByteFloat;

void psInterpretParticles(u32);
#endif
