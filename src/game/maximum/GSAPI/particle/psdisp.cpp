#include "game/maximum/GSAPI/particle/psdisp.h"
#include <dolphin/os/OSFastCast.h>
#undef PS_FIXED6
#define PS_FIXED6(value) __OSf32tos16_q6(value)
#define NULL ((void*)0)
#define fabs __fabs
static f32 vmtx[3][4], rvmtx[3][4], prj[7], pvmtx[3][4], rvmtxRot[3][4];
u8 psFrameNum = 123;
static s32 prevPointSize;
static s32 prevLineWidth;
static f32 rx0;
static f32 rx1;
static f32 ry0;
static f32 ry1;
static f32 rz0;
static f32 rz1;
static s32 prevBlendMode;
static s32 prevChanCtrl;
static GXColor prevChanMat;
static GXColor prevChanAmb;
static GXColor prevColorPrim;
static GXColor prevColorEnv;
static GXColor prevColorMat;
static GXPosNrmMtx currentMtx;
static void* particleFog;
static u8 billboard_tex0_u8[32] __attribute__((aligned(32))) = {0,1,0,0,1,0,1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1,0,1,0,1,1,0,1,0,0};
s32 psDispHasRenderData(s32 arg0);

void psDispBeginFrame(void);
s32 psDispHasRenderData(s32 mask);
__declspec(weak) void setupChanReg(PSParticle *arg0);
__declspec(weak) void setupTevReg(PSParticle *arg0);
__declspec(weak) void psDispSubAPPSRTPoint(PSParticle *arg0);
__declspec(weak) PSParticle *psDispSubPointTrail(PSParticle *arg0);
__declspec(weak) void psDispSubAppSRT(PSParticle *arg0, u32 *arg1);
__declspec(weak) void psDispSubMakePolygon(PSParticle *arg0, u32 *arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 arg_sp8, f32 arg_spC, f32 arg_sp10, f32 arg_sp14);
__declspec(weak) void psDispSub(PSParticle *arg0, u32 *arg1);
static void _psDispParticlesSub(u32 arg0, s32 arg1, PSGenerator *arg2, u32 arg3);
void psDispSetProjection(f32 *arg0);
void psDispParticles(u32 arg0, s32 arg1, u32 arg2);

void psDispBeginFrame(void) {
    u8 var_r0;

    var_r0 = 1;
    if ((u8) psFrameNum < 0xFFU) {
        var_r0 = psFrameNum + 1;
    }
    psFrameNum = var_r0;
}

s32 psDispHasRenderData(s32 mask) {
    PSParticle *opaque, *translucent;
    s32 link;
    for (link = 0; link < 16; link++) {
        if (mask & (1 << link)) {
            particleSort(link, &opaque, &translucent);
            if (opaque != NULL || translucent != NULL) return 1;
        }
    }
    return 0;
}

static inline void getColorPrimEnv(PSParticle *pp, GXColor *primCol, GXColor *envCol) {
    if (pp->primCount) {
        int scale = 65536 * pp->primRemain / pp->primCount;
        primCol->r = ((pp->primTarget[0] << 16) + (pp->primColor[0] - pp->primTarget[0]) * scale) >> 16;
        primCol->g = ((pp->primTarget[1] << 16) + (pp->primColor[1] - pp->primTarget[1]) * scale) >> 16;
        primCol->b = ((pp->primTarget[2] << 16) + (pp->primColor[2] - pp->primTarget[2]) * scale) >> 16;
        primCol->a = ((pp->primTarget[3] << 16) + (pp->primColor[3] - pp->primTarget[3]) * scale) >> 16;
    } else {
        *primCol = *(GXColor *) pp->primColor;
    }
    if (pp->envCount) {
        int scale = 65536 * pp->envRemain / pp->envCount;
        envCol->r = ((pp->envTarget[0] << 16) + (pp->envColor[0] - pp->envTarget[0]) * scale) >> 16;
        envCol->g = ((pp->envTarget[1] << 16) + (pp->envColor[1] - pp->envTarget[1]) * scale) >> 16;
        envCol->b = ((pp->envTarget[2] << 16) + (pp->envColor[2] - pp->envTarget[2]) * scale) >> 16;
        envCol->a = ((pp->envTarget[3] << 16) + (pp->envColor[3] - pp->envTarget[3]) * scale) >> 16;
    } else {
        *envCol = *(GXColor *) pp->envColor;
    }
}

static inline void getColorMatAmb(PSParticle *pp, GXColor *matCol, GXColor *ambCol) {
    if (pp->matCount) {
        int scale = 65536 * pp->matRemain / pp->matCount;
        u8 rgb = ((pp->matRGBTarget << 16) + (pp->matRGB - pp->matRGBTarget) * scale) >> 16;
        matCol->r = matCol->g = matCol->b = rgb;
        matCol->a = ((pp->matAlphaTarget << 16) + (pp->matAlpha - pp->matAlphaTarget) * scale) >> 16;
    } else {
        matCol->r = matCol->g = matCol->b = pp->matRGB;
        matCol->a = pp->matAlpha;
    }
    if (pp->ambCount) {
        int scale = 65536 * pp->ambRemain / pp->ambCount;
        u8 rgb = ((pp->ambRGBTarget << 16) + (pp->ambRGB - pp->ambRGBTarget) * scale) >> 16;
        ambCol->r = ambCol->g = ambCol->b = rgb;
        ambCol->a = ((pp->ambAlphaTarget << 16) + (pp->ambAlpha - pp->ambAlphaTarget) * scale) >> 16;
    } else {
        ambCol->r = ambCol->g = ambCol->b = pp->ambRGB;
        ambCol->a = pp->ambAlpha;
    }
}

__declspec(weak) void setupChanReg(PSParticle *pp) {
    GXColor prim_color;
    GXColor amb_color;
    GXColor mat_color;
    void *lobj;

    if (pp->kind & 0x80000000) {
        getColorMatAmb(pp, &mat_color, &amb_color);
        if (pp->kind & 0x80) {
            prim_color.r = prim_color.g = prim_color.b = 0xFF;
        } else {
            getColorPrimEnv(pp, &prim_color, &mat_color);
            amb_color.r = (u8) ((amb_color.r * prim_color.r) >> 8);
            amb_color.g = (u8) ((amb_color.g * prim_color.g) >> 8);
            amb_color.b = (u8) ((amb_color.b * prim_color.b) >> 8);
        }
        if (prim_color.r != prevChanMat.r || prim_color.g != prevChanMat.g || prim_color.b != prevChanMat.b) {
            prevChanMat = prim_color;
            GXSetChanMatColor(GX_COLOR0, prevChanMat);
        }
        lobj = HSD_LObjGetActiveByID(0x100U);
        if (lobj != NULL) {
            HSD_MulColor(&amb_color, (GXColor *) ((u8 *) lobj + 0x10), &amb_color);
        } else {
            amb_color.r = amb_color.g = amb_color.b = 0;
        }
        if (amb_color.r != prevChanAmb.r || amb_color.g != prevChanAmb.g || amb_color.b != prevChanAmb.b) {
            prevChanAmb = amb_color;
            GXSetChanAmbColor(GX_COLOR0, prevChanAmb);
        }
    }
}

__declspec(weak) void setupTevReg(PSParticle *pp) {
    GXColor prim_color;
    GXColor env_color;
    GXColor mat_color;
    GXColor amb_color;

    getColorPrimEnv(pp, &prim_color, &env_color);
    if ((pp->kind & 0x80) || (!(pp->kind & 0x80000000) && !(pp->kind & 0x100000))) {
        if (prevColorPrim.r != prim_color.r || prevColorPrim.g != prim_color.g || prevColorPrim.b != prim_color.b || prevColorPrim.a != prim_color.a) {
            prevColorPrim = prim_color;
            GXSetTevColor(GX_TEVREG0, prevColorPrim);
        }
        if (pp->kind & 0x80) {
            if (prevColorEnv.r != env_color.r || prevColorEnv.g != env_color.g || prevColorEnv.b != env_color.b || prevColorEnv.a != env_color.a) {
                prevColorEnv = env_color;
                GXSetTevColor(GX_TEVREG1, prevColorEnv);
            }
        } else if (prevColorEnv.r != 0 || prevColorEnv.g != 0 || prevColorEnv.b != 0 || prevColorEnv.a != 0) {
            prevColorEnv.r = prevColorEnv.g = prevColorEnv.b = prevColorEnv.a = 0;
            GXSetTevColor(GX_TEVREG1, prevColorEnv);
        }
    }
    if (pp->kind & 0x80000000) {
        getColorMatAmb(pp, &mat_color, &amb_color);
        if (pp->kind & 0x80) {
            if (prevColorMat.r != mat_color.r || prevColorMat.g != mat_color.g || prevColorMat.b != mat_color.b || prevColorMat.a != mat_color.a) {
                prevColorMat = mat_color;
                GXSetTevColor(GX_TEVREG2, prevColorMat);
            }
        } else {
            mat_color.a = (u8) ((mat_color.a * prim_color.a) >> 8);
            if (prevColorMat.r != mat_color.r || prevColorMat.g != mat_color.g || prevColorMat.b != mat_color.b || prevColorMat.a != mat_color.a) {
                prevColorMat = mat_color;
                GXSetTevColor(GX_TEVREG2, prevColorMat);
            }
        }
    }
}

static inline void calcTornadoAnchor(PSParticle* pp, f32* x, f32* y, f32* z) {
    f32 cosb,cosa,sinb,sina,radius;
    f32 px,py,pz;
    f32 vx0, vz0;
    PSGenerator* gp;
    gp=pp->generator;
    if(gp==NULL) {*x=pp->position.x;*y=pp->position.y;*z=pp->position.z;return;}
    sina=(f32)sin((f64)pp->gravity);
    sinb=(f32)sin((f64)pp->friction);
    cosa=(f32)cos((f64)pp->gravity);
    cosb=(f32)cos((f64)pp->friction);
    vz0=pp->velocity.z-gp->param1;
    vx0=pp->velocity.x-gp->gravity;
    radius=gp->radius;if(radius<0.0f)radius=-radius;
    {f32 angle=gp->angle;if(angle<0.0f)angle=-angle;radius+=vz0*(f32)tan((f64)angle);}
    radius*=pp->velocity.y;
    px=radius*(f32)cos((f64)vx0);
    py=radius*(f32)sin((f64)vx0);
    pz=vz0;
    *x=px*cosb+pz*sinb+gp->position.x;
    *y=-px*sina*sinb+py*cosa+pz*sina*cosb+gp->position.y;
    *z=-px*cosa*sinb-py*sina+pz*cosa*cosb+gp->position.z;
}
static inline void emitParticleColor(u8 r,u8 g,u8 b,u8 a){GXWGFifo.u16=((r<<8)&0xf000)|((g<<4)&0xf00)|(b&0xf0)|(a>>4);}

inline f32 sinf(f32 x) { return (f32)sin(x); }
inline f32 cosf(f32 x) { return (f32)cos(x); }
inline f32 tanf(f32 x) { return (f32)tan(x); }
static inline f32 atan2f(f32 y,f32 x) { return (f32)atan2(y,x); }
static inline void reuseCalcTornadoLastPos(PSParticle* pp, f32* x, f32* y, f32* z)
{
    f32 px, py, pz;
    f32 sina, sinb, cosa, cosb;
    PSGenerator* gp;
    f32 radius;
    f32 vx0;
    f32 vz0;

    gp = pp->generator;
    if (gp == NULL) {
        *x = pp->position.x;
        *y = pp->position.y;
        *z = pp->position.z;
        return;
    }

    sina = sinf(pp->gravity);
    sinb = sinf(pp->friction);
    cosa = cosf(pp->gravity);
    cosb = cosf(pp->friction);

    vz0 = pp->velocity.z - gp->param1;
    vx0 = pp->velocity.x - gp->gravity;

    radius = gp->radius < 0.0f ? -gp->radius : gp->radius;
    radius += vz0 * tanf(gp->angle < 0.0f ? -gp->angle : gp->angle);
    radius *= pp->velocity.y;
    px = radius * cosf(vx0);
    py = radius * sinf(vx0);
    pz = vz0;

    *x = px * cosb + pz * sinb + gp->position.x;
    *y = -px * sina * sinb + py * cosa + pz * sina * cosb + gp->position.y;
    *z = -px * cosa * sinb - py * sina + pz * cosa * cosb + gp->position.z;
}
void HSD_MtxSRT(PSMtx,PSVec*,PSVec*,PSVec*,PSVec*);
#pragma push
#pragma optimization_level 3
void psDispSubAPPSRTPoint(PSParticle *arg0)
{
  PSMtx basis;
  PSMtx originMatrix;
  PSVec position;
  PSVec origin;
  GXColor color;
  GXColor environment;
  s32 coordinates[3];
  PSAppSRT *temp_r3;
  PSAppSRT *temp_r3_2;
  PSAppSRT *temp_r3_3;
  PSAppSRT *temp_r6;
  PSAppSRT *temp_r6_2;
  PSAppSRT *temp_r6_3;
  PSGenerator *temp_r30;
  f32 temp_f0;
  f32 temp_f1;
  f32 temp_f25;
  f32 temp_f25_2;
  f32 temp_f26;
  f32 temp_f26_2;
  f32 temp_f27;
  f32 temp_f27_2;
  f32 temp_f28;
  f32 temp_f29;
  f32 temp_f30;
  f32 temp_f30_2;
  f32 temp_f31;
  f32 temp_f5;
  f32 temp_f9;
  f32 var_f0;
  f32 var_f1;
  f32 var_f29;
  s32 temp_r11;
  u8 temp_r3_4;
  s32 temp_r4;
  u8 savedAlpha;
  u16 temp_r7_2;
  u16 temp_r5;
  u32 temp_r0;
  s32 temp_r12;
  s32 temp_r30_2;
  s32 temp_r6_4;
  s32 temp_r7;
  f32 var_f24_2;
  f32 var_f23_2;
  f32 var_f22_2;
  f32 pointX;
  f32 pointY;
  f32 pointZ;
  if (((s32) currentMtx) != 0)
  {
    currentMtx = 0;
    GXSetCurrentMtx(0U);
  }
  temp_r6 = arg0->appsrt;
  if (((u8) temp_r6->frame) != ((u8) psFrameNum))
  {
    if (((u8) temp_r6->status) != 2)
    {
      HSD_MtxSRT((f32 (*)[4]) temp_r6->matrix[0], &temp_r6->scale, &temp_r6->rotation, &temp_r6->translate, 0);
    }
    temp_r3 = arg0->appsrt;
    if (((u8) temp_r3->status) == 1)
    {
      temp_r3->status = 2;
    }
  }
  arg0->appsrt->frame = psFrameNum;
  PSMTXCopy((f32 (*)[4]) arg0->appsrt->matrix[0], basis);
  temp_r6_2 = arg0->appsrt;
  basis[0][3] -= temp_r6_2->translate.x;
  basis[1][3] -= temp_r6_2->translate.y;
  basis[2][3] -= temp_r6_2->translate.z;
  position.x = arg0->velocity.x;
  position.y = arg0->velocity.y;
  position.z = arg0->velocity.z;
  PSMTXMultVec(basis, &position, &position);
  if (((u8) arg0->appsrt->generatorOwned) != 0)
  {
    PSMTXMultVec(rvmtxRot, &position, &position);
  }
  temp_f25 = position.x;
  temp_f26 = position.y;
  position.x = arg0->position.x;
  temp_f27 = position.z;
  position.y = arg0->position.y;
  position.z = arg0->position.z;
  temp_r3_2 = arg0->appsrt;
  if (((u8) temp_r3_2->generatorOwned) != 0)
  {
    PSMTXMultVec(basis, &position, &position);
    PSMTXMultVec(rvmtxRot, &position, &position);
    temp_r3_3 = arg0->appsrt;
    position.x += temp_r3_3->translate.x;
    position.y += temp_r3_3->translate.y;
    position.z += temp_r3_3->translate.z;
  }
  else
  {
    PSMTXMultVec((f32 (*)[4]) temp_r3_2->matrix[0], &position, &position);
  }
  {
    pointX = position.x;
    pointY = position.y;
    pointZ = position.z;
    if (arg0->kind & 4)
    {
      calcTornadoAnchor(arg0, &var_f24_2, &var_f23_2, &var_f22_2);
      temp_r6_3 = arg0->appsrt;
      HSD_MtxSRT(originMatrix, &temp_r6_3->scale, &temp_r6_3->rotation, &temp_r6_3->translate, 0);
      origin.x = var_f24_2;
      origin.y = var_f23_2;
      origin.z = var_f22_2;
      PSMTXMultVec(originMatrix, &origin, &origin);
      var_f24_2 = origin.x;
      var_f23_2 = origin.y;
      var_f22_2 = origin.z;
    }
    else
    {
      var_f24_2 = pointX - temp_f25;
      var_f23_2 = pointY - temp_f26;
      var_f22_2 = pointZ - temp_f27;
    }
    temp_r3_4 = (arg0->size > 42.5) ? 255.0f : 6.0f * arg0->size;
    if (arg0->kind & 0x100000)
    {
      if (((s32) prevLineWidth) != ((s32) temp_r3_4))
      {
        prevLineWidth = temp_r3_4;
        GXSetLineWidth(temp_r3_4, GX_TO_ONE);
      }
      temp_r0 = arg0->kind;
      temp_r4 = temp_r0 & 0x80000080;
      switch (temp_r4)
      {
        case 0x0:

        case 0x80000000:
          getColorPrimEnv(arg0, &color, &environment);
          break;

        case 0x80:

        case 0x80000080:
          color.a = 0xFF;
          color.b = 0xFF;
          color.g = 0xFF;
          color.r = 0xFF;
          break;

      }

      if (temp_r0 & 0x400)
      {
        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        GXBegin(GX_LINES, GX_VTXFMT2, 2U);
      }
      else
      {
        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXBegin(GX_LINES, GX_VTXFMT3, 2U);
      }

      coordinates[2] = PS_FIXED6(var_f22_2);
      coordinates[1] = PS_FIXED6(var_f23_2);
      coordinates[0] = PS_FIXED6(var_f24_2);
      *((volatile s16 *) 0xCC008000) = coordinates[0];
      *((volatile s16 *) 0xCC008000) = coordinates[1];
      *((volatile s16 *) 0xCC008000) = coordinates[2];
      emitParticleColor(color.r, color.g, color.b, (u8) (((f32) color.a) * arg0->textureScale));
      if (arg0->kind & 0x400)
      {
        *((volatile u8 *) 0xCC008000) = 0;
      }

      coordinates[2] = PS_FIXED6(pointZ);
      coordinates[1] = PS_FIXED6(pointY);
      coordinates[0] = PS_FIXED6(pointX);
      *((volatile s16 *) 0xCC008000) = coordinates[0];
      *((volatile s16 *) 0xCC008000) = coordinates[1];
      *((volatile s16 *) 0xCC008000) = coordinates[2];
      emitParticleColor(color.r, color.g, color.b, color.a);
      if (arg0->kind & 0x400)
      {
        *((volatile u8 *) 0xCC008000) = 1;
      }
    }
    else
    {
      if (((s32) prevPointSize) != ((s32) temp_r3_4))
      {
        prevPointSize = temp_r3_4;
        GXSetPointSize(temp_r3_4, GX_TO_ONE);
      }
      if (arg0->kind & 0x400)
      {
        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        GXBegin(GX_POINTS, GX_VTXFMT0, 1U);
      }
      else
      {
        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXBegin(GX_POINTS, GX_VTXFMT1, 1U);
      }

      coordinates[2] = PS_FIXED6(pointZ);
      coordinates[1] = PS_FIXED6(pointY);
      coordinates[0] = PS_FIXED6(pointX);
      *((volatile s16 *) 0xCC008000) = coordinates[0];
      *((volatile s16 *) 0xCC008000) = coordinates[1];
      *((volatile s16 *) 0xCC008000) = coordinates[2];
      if (arg0->kind & 0x400)
      {
        *((volatile u8 *) 0xCC008000) = 1;
      }
    }
  }
}

#pragma pop

__declspec(weak) PSParticle *psDispSubPointTrail(PSParticle *arg0) {
    union { f64 alignment; u8 bytes[43]; } stack;
    s16 sz0, sy0, sx0, sz1, sy1, sx1;
    PSGenerator *temp_r30;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    f32 temp_f5;
    f32 temp_f9;
    f32 var_f0;
    f32 var_f19;
    f32 var_f1;
    f32 var_f20;
    f32 var_f21;
    f32 var_f29;
    s32 temp_r11;
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r7_2;
    u16 temp_r5;
    u32 temp_r0;
    s32 temp_r12;
    s32 temp_r30_2;
    s32 temp_r6;
    s32 temp_r7;

    if ((s32) currentMtx != 0) {
        currentMtx = 0;
        GXSetCurrentMtx(0U);
    }
    temp_f1 = arg0->size;
    if (temp_f1 > 42.5) {
        var_f0 = 255.0f;
    } else {
        var_f0 = 6.0f * temp_f1;
    }
    temp_r3 = (s32) var_f0;
    if ((s32) prevLineWidth != (s32) (u8) temp_r3) {
        prevLineWidth = (s32) (u8) temp_r3;
        GXSetLineWidth((u8) temp_r3, GX_TO_ONE);
    }
    if (arg0->kind & 4) {
        temp_r30 = arg0->generator;
        if (temp_r30 == NULL) {
            var_f21 = arg0->position.x;
            var_f20 = arg0->position.y;
            var_f19 = arg0->position.z;
        } else {
            temp_f25 = (f32) sin((f64) arg0->gravity);
            temp_f24 = (f32) sin((f64) arg0->friction);
            temp_f23 = (f32) cos((f64) arg0->gravity);
            temp_f22 = (f32) cos((f64) arg0->friction);
            temp_f31 = arg0->velocity.z - temp_r30->param1;
            var_f29 = temp_r30->radius;
            temp_f30 = arg0->velocity.x - temp_r30->gravity;
            if (var_f29 < 0.0f) {
                var_f29 = -var_f29;
            }
            var_f1 = temp_r30->angle;
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            temp_f29 = ((temp_f31 * (f32) tan((f64) var_f1)) + var_f29) * arg0->velocity.y;
            temp_f30_2 = temp_f29 * (f32) cos((f64) temp_f30);
            temp_f9 = -temp_f30_2;
            temp_f5 = temp_f29 * (f32) sin((f64) temp_f30);
            var_f21 = temp_r30->position.x + ((temp_f30_2 * temp_f22) + (temp_f31 * temp_f24));
            var_f20 = temp_r30->position.y + ((temp_f22 * (temp_f31 * temp_f25)) + ((temp_f24 * (temp_f9 * temp_f25)) + (temp_f5 * temp_f23)));
            var_f19 = temp_r30->position.z + ((temp_f22 * (temp_f31 * temp_f23)) + ((temp_f24 * (temp_f9 * temp_f23)) - (temp_f5 * temp_f25)));
        }
    } else {
        var_f21 = arg0->position.x - arg0->velocity.x;
        var_f20 = arg0->position.y - arg0->velocity.y;
        var_f19 = arg0->position.z - arg0->velocity.z;
    }
    temp_r0 = arg0->kind;
    temp_r4 = temp_r0 & 0x80000080;
    switch (temp_r4) {                              /* irregular */
    case 0x80000000:
    case 0x0:
        temp_r5 = arg0->primCount;
        if (temp_r5 != 0) {
            temp_r6 = arg0->primTarget[0];
            temp_r7 = arg0->primTarget[1];
            temp_r11 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r5;
            temp_r12 = arg0->primTarget[2];
            temp_r30_2 = arg0->primTarget[3];
            (*(s8*)(stack.bytes+0x20)) = (s8) ((s32) ((temp_r6 << 0x10) + (temp_r11 * (arg0->primColor[0] - temp_r6))) >> 0x10);
            (*(u8*)(stack.bytes+0x21)) = (u8) ((s32) ((temp_r7 << 0x10) + (temp_r11 * (arg0->primColor[1] - temp_r7))) >> 0x10);
            (*(u8*)(stack.bytes+0x22)) = (u8) ((s32) ((temp_r12 << 0x10) + (temp_r11 * (arg0->primColor[2] - temp_r12))) >> 0x10);
            (*(u8*)(stack.bytes+0x23)) = (u8) ((s32) ((temp_r30_2 << 0x10) + (temp_r11 * (arg0->primColor[3] - temp_r30_2))) >> 0x10);
        } else {
            *(u32*)&(*(s8*)(stack.bytes+0x20)) = (s32) *(u32*)arg0->primColor;
        }
        break;
    case 0x80:
    case 0x80000080:
        (*(u8*)(stack.bytes+0x23)) = 0xFF;
        (*(u8*)(stack.bytes+0x22)) = 0xFF;
        (*(u8*)(stack.bytes+0x21)) = 0xFF;
        (*(u8*)(stack.bytes+0x20)) = 0xFF;
        break;
    }
    if (temp_r0 & 0x400) {
        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        GXBegin(GX_LINES, GX_VTXFMT2, 2U);
    } else {
        GXClearVtxDesc();
        GXInvalidateVtxCache();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXBegin(GX_LINES, GX_VTXFMT3, 2U);
    }
    sz0 = PS_FIXED6(var_f19);
    sy0 = PS_FIXED6(var_f20);
    sx0 = PS_FIXED6(var_f21);
    *(volatile s16 *)0xCC008000 = sx0;
    *(volatile s16 *)0xCC008000 = sy0;
    *(volatile s16 *)0xCC008000 = sz0;
    temp_r7_2 = (((((*(u8*)(stack.bytes+0x21)) * 0x10) & 0xF00 & ~0xF000) | (((u8) (*(s8*)(stack.bytes+0x20)) << 8) & 0xF000)) & ~0xF0) | ((*(u8*)(stack.bytes+0x22)) & 0xF0);
    temp_f0 = (f32) (*(u8*)(stack.bytes+0x23)) * arg0->textureScale;
    *(volatile s16 *)0xCC008000 = (temp_r7_2 & ~0xF) | (((u32) (s32) temp_f0 >> 4U) & 0xF);
    if (arg0->kind & 0x400) {
        *(volatile u8 *)0xCC008000 = 0;
    }
    sz1 = PS_FIXED6(arg0->position.z);
    sy1 = PS_FIXED6(arg0->position.y);
    sx1 = PS_FIXED6(arg0->position.x);
    *(volatile s16 *)0xCC008000 = sx1;
    *(volatile s16 *)0xCC008000 = sy1;
    *(volatile s16 *)0xCC008000 = sz1;
    *(volatile s16 *)0xCC008000 = (s16) ((((*(u8*)(stack.bytes+0x23)) >> 4U) & 0xF) | temp_r7_2);
    if (arg0->kind & 0x400) {
        *(volatile u8 *)0xCC008000 = 1;
    }
    return arg0;
}

__declspec(weak) void psDispSubAppSRT(PSParticle* pp, u32* texform)
{
    PSMtx mtx;
    PSVec v;
    f32 right_x;
    f32 up_x;
    f32 right_y;
    f32 up_y;
    f32 right_z;
    f32 up_z;
    f32 x;
    f32 y;
    f32 z;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 angle;
    f32 dir_x;
    f32 dir_y;
    PSGenerator* gp;

    if (pp->appsrt->frame != psFrameNum) {
        if (pp->appsrt->status != 2) {
            HSD_MtxSRT(pp->appsrt->matrix, &pp->appsrt->scale, &pp->appsrt->rotation,
                       &pp->appsrt->translate, NULL);
        }
        if (pp->appsrt->status == 1) {
            pp->appsrt->status = 2;
        }
    }
    pp->appsrt->frame = psFrameNum;
    PSMTXCopy(pp->appsrt->matrix, mtx);
    mtx[0][3] -= pp->appsrt->translate.x;
    mtx[1][3] -= pp->appsrt->translate.y;
    mtx[2][3] -= pp->appsrt->translate.z;
    v.x = pp->velocity.x;
    v.y = pp->velocity.y;
    v.z = pp->velocity.z;
    PSMTXMultVec(mtx, &v, &v);
    if (pp->appsrt->generatorOwned != 0 && !(pp->kind & 4)) {
        PSMTXMultVec(rvmtxRot, &v, &v);
    }
    vx = v.x;
    vy = v.y;
    vz = v.z;
    v.x = pp->position.x;
    v.y = pp->position.y;
    v.z = pp->position.z;
    if (pp->appsrt->generatorOwned != 0) {
        PSMTXMultVec(mtx, &v, &v);
        PSMTXMultVec(rvmtxRot, &v, &v);
        v.x += pp->appsrt->translate.x;
        v.y += pp->appsrt->translate.y;
        v.z += pp->appsrt->translate.z;
    } else {
        PSMTXMultVec(pp->appsrt->matrix, &v, &v);
    }
    x = v.x;
    y = v.y;
    z = v.z;
    if (texform != NULL) {
        PSMtx smtx;

        PSMTXScale(smtx, pp->appsrt->scale.x, pp->appsrt->scale.y, 1.0f);
        PSMTXConcat(rvmtx, smtx, smtx);
        right_x = smtx[0][0] * pp->size;
        up_x = -smtx[0][1] * pp->size;
        right_y = smtx[1][0] * pp->size;
        up_y = -smtx[1][1] * pp->size;
        right_z = smtx[2][0] * pp->size;
        up_z = -smtx[2][1] * pp->size;
    } else {
        PSVec r;
        PSVec u;

        r.x = pp->appsrt->scale.x + vmtx[0][3];
        r.y = pp->appsrt->scale.y + vmtx[1][3];
        r.z = vmtx[2][3];
        u.x = pp->appsrt->scale.x + vmtx[0][3];
        u.y = -pp->appsrt->scale.y + vmtx[1][3];
        u.z = vmtx[2][3];
        PSMTXMultVec(rvmtx, &r, &r);
        right_x = r.x * pp->size;
        right_y = r.y * pp->size;
        right_z = r.z * pp->size;
        PSMTXMultVec(rvmtx, &u, &u);
        up_x = u.x * pp->size;
        up_y = u.y * pp->size;
        up_z = u.z * pp->size;
    }
    gp = pp->generator;
    if (gp != NULL && (gp->transformFlags & 0x20)) {
        right_x *= gp->scale.x;
        up_x *= gp->scale.x;
        right_y *= gp->scale.y;
        up_y *= gp->scale.y;
        right_z *= gp->scale.z;
        up_z *= gp->scale.z;
    }
    if ((pp->kind & 0x100000) || (pp->kind & 0x200000)) {
        if (0.0f == prj[0]) {
            f32 prev_x;
            f32 prev_y;
            f32 prev_z;
            f32 w1inv;
            f32 w1;
            f32 w0inv;
            f32 w0;

            if (pp->kind & 4) {
                reuseCalcTornadoLastPos(pp, &prev_x, &prev_y, &prev_z);
                v.x = prev_x;
                v.y = prev_y;
                v.z = prev_z;
                if (pp->appsrt->generatorOwned != 0) {
                    PSMTXMultVec(mtx, &v, &v);
                    PSMTXMultVec(rvmtxRot, &v, &v);
                    v.x += pp->appsrt->translate.x;
                    v.y += pp->appsrt->translate.y;
                    v.z += pp->appsrt->translate.z;
                } else {
                    PSMTXMultVec(pp->appsrt->matrix, &v, &v);
                }
                prev_x = v.x;
                prev_y = v.y;
                prev_z = v.z;
            } else {
                prev_x = x - vx;
                prev_y = y - vy;
                prev_z = z - vz;
            }
            w0 = vmtx[2][3] + (vmtx[2][2] * z + (vmtx[2][0] * x + vmtx[2][1] * y));
            if (0.0f == w0) {
                goto no_direction;
            }
            w0inv = -1.0f / w0;
            w1 = vmtx[2][3] + (vmtx[2][2] * prev_z +
                               (vmtx[2][0] * prev_x + vmtx[2][1] * prev_y));
            if (0.0f == w1) {
                goto no_direction;
            }
            w1inv = -1.0f / w1;
            dir_x = w0inv * (pvmtx[0][3] + (pvmtx[0][2] * z +
                                            (pvmtx[0][0] * x + pvmtx[0][1] * y))) -
                    w1inv * (pvmtx[0][3] + (pvmtx[0][2] * prev_z +
                                            (pvmtx[0][0] * prev_x +
                                             pvmtx[0][1] * prev_y)));
            dir_y = w0inv * (pvmtx[1][3] + (pvmtx[1][2] * z +
                                            (pvmtx[1][0] * x + pvmtx[1][1] * y))) -
                    w1inv * (pvmtx[1][3] + (pvmtx[1][2] * prev_z +
                                            (pvmtx[1][0] * prev_x +
                                             pvmtx[1][1] * prev_y)));
        } else if (pp->kind & 4) {
            f32 prev_x;
            f32 prev_y;
            f32 prev_z;
            f32 dx;
            f32 dy;
            f32 dz;

            reuseCalcTornadoLastPos(pp, &prev_x, &prev_y, &prev_z);
            v.x = prev_x;
            v.y = prev_y;
            v.z = prev_z;
            if (pp->appsrt->generatorOwned != 0) {
                PSMTXMultVec(mtx, &v, &v);
                PSMTXMultVec(rvmtxRot, &v, &v);
                v.x += pp->appsrt->translate.x;
                v.y += pp->appsrt->translate.y;
                v.z += pp->appsrt->translate.z;
            } else {
                PSMTXMultVec(pp->appsrt->matrix, &v, &v);
            }
            dx = x - v.x;
            dy = y - v.y;
            dz = z - v.z;
            dir_x = pvmtx[0][2] * dz + (pvmtx[0][0] * dx + pvmtx[0][1] * dy);
            dir_y = pvmtx[1][2] * dz + (pvmtx[1][0] * dx + pvmtx[1][1] * dy);
        } else {
            dir_x = pvmtx[0][2] * vz + (pvmtx[0][0] * vx + pvmtx[0][1] * vy);
            dir_y = pvmtx[1][2] * vz + (pvmtx[1][0] * vx + pvmtx[1][1] * vy);
        }
        if (fabs(dir_y) < (__float_min[0])) {
            angle = (dir_x >= 0.0f) ? 1.5707964f : -1.5707964f;
        } else {
            angle = atan2f(dir_x, dir_y);
        }
        if (pp->kind & 0x200000) {
            angle += pp->rotate;
        }
    } else {
    no_direction:
        angle = pp->rotate;
    }
    if (fabs(angle) > 0.01) {
        PSMtx rmtx;
        PSVec axis;
        f32 rx = right_x;
        f32 ry = right_y;
        f32 rz = right_z;
        f32 ux = up_x;
        f32 uy = up_y;
        f32 uz = up_z;

        axis.x = ry * uz - rz * uy;
        axis.y = rz * ux - rx * uz;
        axis.z = rx * uy - ry * ux;
        PSMTXRotAxisRad(rmtx, &axis, angle);
        right_x = rmtx[0][2] * rz + (rmtx[0][0] * rx + rmtx[0][1] * ry);
        right_y = rmtx[1][2] * rz + (rmtx[1][0] * rx + rmtx[1][1] * ry);
        right_z = rmtx[2][2] * rz + (rmtx[2][0] * rx + rmtx[2][1] * ry);
        up_x = rmtx[0][2] * uz + (rmtx[0][0] * ux + rmtx[0][1] * uy);
        up_y = rmtx[1][2] * uz + (rmtx[1][0] * ux + rmtx[1][1] * uy);
        up_z = rmtx[2][2] * uz + (rmtx[2][0] * ux + rmtx[2][1] * uy);
    }
    psDispSubMakePolygon(pp, texform, x, y, z, vx, vy, vz, right_x, right_y,
                         right_z, up_x, up_y, up_z);
}

__declspec(weak) void psDispSubMakePolygon(PSParticle *arg0, u32 *arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 arg_sp8, f32 arg_spC, f32 arg_sp10, f32 arg_sp14) {
    f32 radialAngleNoSRT;
    f32 radialXNoSRT;
    f32 radialAngle;
    f32 radialX;
    f32 widthClassify;
    f32 distanceClassify;
    s16 trailNearZ;
    s16 trailNearY;
    s16 trailNearX;
    s16 trailCrossZ;
    s16 trailCrossY;
    s16 trailCrossX;
    s16 trailPlusZ;
    s16 trailPlusY;
    s16 trailPlusX;
    s16 trailFarZ;
    s16 trailFarY;
    s16 trailFarX;
    s16 trailCustomZ;
    s16 trailCustomY;
    s16 trailCustomX;
    s16 billboardMinusZ;
    s16 billboardMinusY;
    s16 billboardMinusX;
    s16 billboardCrossZ;
    s16 billboardCrossY;
    s16 billboardCrossX;
    s16 billboardPlusZ;
    s16 billboardPlusY;
    s16 billboardPlusX;
    s16 billboardFarZ;
    s16 billboardFarY;
    s16 billboardFarX;
    s16 customZ;
    s16 customY;
    s16 customX;
    f32 directionZ;
    f32 directionY;
    f32 directionX;
    PSMtx appMtx;
    PSVec position;
    GXColor color;
    f64 saved390;
    PSAppSRT *temp_r6;
    PSGenerator *temp_r27;
    PSGenerator *temp_r27_2;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_13;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_16;
    f32 temp_f0_17;
    f32 temp_f0_18;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f15;
    f32 temp_f15_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f17;
    f32 temp_f17_2;
    f32 temp_f17_3;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f2_4;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 var_f0;
    f32 var_f14;
    f32 var_f14_2;
    f32 var_f15;
    f32 var_f15_2;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f21;
    f32 var_f22;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f5;
    f64 temp_f2;
    f64 temp_f2_2;
    f64 temp_f2_3;
    f64 temp_f2_5;
    f64 temp_f2_6;
    f64 temp_f2_7;
    s16 temp_r8;
    s32 temp_r0_2;
    s32 temp_r11;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r5;
    u16 temp_r5;
    u32 *var_r29;
    u32 *var_r29_2;
    u32 temp_r0;
    u32 temp_r3;
    u32 temp_r3_2;
    u32 temp_r3_5;
    u32 temp_r3_6;
    u32 temp_r3_7;
    u32 temp_r3_8;
    u32 temp_r3_9;
    u32 temp_r4_2;
    u32 temp_r5_2;
    u32 temp_r6_3;
    u32 temp_r6_4;
    u32 var_r25;
    u32 var_r30;
    u8 temp_r12;
    u8 temp_r25;
    u8 temp_r26;
    u8 temp_r26_2;
    u8 temp_r27_3;
    u8 temp_r27_4;
    u8 temp_r6_2;
    u8 temp_r7;
    u32 var_ctr;
    u32 var_ctr_2;

    directionX = farg3;
    directionY = farg4;
    directionZ = farg5;
    if ((s32) currentMtx != 0) {
        currentMtx = 0;
        GXSetCurrentMtx(0U);
    }
    temp_r3 = arg0->kind;
    if (temp_r3 & 0x100000) {
        if (temp_r3 & 4) {
            if ((PSAppSRT *) arg0->appsrt != NULL) {
                temp_r27 = arg0->generator;
                if (temp_r27 == NULL) {
                    var_f15 = arg0->position.x;
                    var_f14 = arg0->position.y;
                    var_f16 = arg0->position.z;
                } else {
                    temp_f17 = (f32) sin((f64) arg0->gravity);
                    temp_f16 = (f32) sin((f64) arg0->friction);
                    temp_f15 = (f32) cos((f64) arg0->gravity);
                    temp_f14 = (f32) cos((f64) arg0->friction);
                    temp_f21 = arg0->velocity.z - temp_r27->param1;
                    var_f22 = temp_r27->radius;
                    radialAngle = arg0->velocity.x - temp_r27->gravity;
                    if (var_f22 < 0.0f) {
                        var_f22 = -var_f22;
                    }
                    var_f1 = temp_r27->angle;
                    if (var_f1 < 0.0f) {
                        var_f1 = -var_f1;
                    }
                    temp_f22 = ((temp_f21 * (f32) tan((f64) var_f1)) + var_f22) * arg0->velocity.y;
                    temp_f0 = temp_f22 * (f32) cos((f64) radialAngle);
                    radialX = temp_f0;
                    temp_f8 = temp_f22 * (f32) sin((f64) radialAngle);
                    temp_f5 = -radialX;
                    var_f15 = temp_r27->position.x + ((radialX * temp_f14) + (temp_f21 * temp_f16));
                    var_f14 = temp_r27->position.y + ((temp_f14 * (temp_f21 * temp_f17)) + ((temp_f16 * (temp_f5 * temp_f17)) + (temp_f8 * temp_f15)));
                    var_f16 = temp_r27->position.z + ((temp_f14 * (temp_f21 * temp_f15)) + ((temp_f16 * (temp_f5 * temp_f15)) - (temp_f8 * temp_f17)));
                }
                temp_r6 = arg0->appsrt;
                HSD_MtxSRT(appMtx, &temp_r6->scale, &temp_r6->rotation, &temp_r6->translate, 0);
                position.x = var_f15;
                position.y = var_f14;
                position.z = var_f16;
                PSMTXMultVec(appMtx, &position, &position);
                var_f14_2 = position.x;
                var_f15_2 = position.y;
                var_f16_2 = position.z;
            } else {
                temp_r27_2 = arg0->generator;
                if (temp_r27_2 == NULL) {
                    var_f14_2 = arg0->position.x;
                    var_f15_2 = arg0->position.y;
                    var_f16_2 = arg0->position.z;
                } else {
                    temp_f14_2 = (f32) sin((f64) arg0->gravity);
                    temp_f15_2 = (f32) sin((f64) arg0->friction);
                    temp_f16_2 = (f32) cos((f64) arg0->gravity);
                    temp_f17_2 = (f32) cos((f64) arg0->friction);
                    temp_f22_2 = arg0->velocity.z - temp_r27_2->param1;
                    var_f21 = temp_r27_2->radius;
                    radialAngleNoSRT = arg0->velocity.x - temp_r27_2->gravity;
                    if (var_f21 < 0.0f) {
                        var_f21 = -var_f21;
                    }
                    var_f1_2 = temp_r27_2->angle;
                    if (var_f1_2 < 0.0f) {
                        var_f1_2 = -var_f1_2;
                    }
                    temp_f21_2 = ((temp_f22_2 * (f32) tan((f64) var_f1_2)) + var_f21) * arg0->velocity.y;
                    temp_f0_2 = temp_f21_2 * (f32) cos((f64) radialAngleNoSRT);
                    radialXNoSRT = temp_f0_2;
                    temp_f8_2 = temp_f21_2 * (f32) sin((f64) radialAngleNoSRT);
                    temp_f5_2 = -radialXNoSRT;
                    var_f14_2 = temp_r27_2->position.x + ((radialXNoSRT * temp_f17_2) + (temp_f22_2 * temp_f15_2));
                    var_f15_2 = temp_r27_2->position.y + ((temp_f17_2 * (temp_f22_2 * temp_f14_2)) + ((temp_f15_2 * (temp_f5_2 * temp_f14_2)) + (temp_f8_2 * temp_f16_2)));
                    var_f16_2 = temp_r27_2->position.z + ((temp_f17_2 * (temp_f22_2 * temp_f16_2)) + ((temp_f15_2 * (temp_f5_2 * temp_f16_2)) - (temp_f8_2 * temp_f14_2)));
                }
            }
        } else {
            var_f14_2 = farg0 - directionX;
            var_f15_2 = farg1 - directionY;
            var_f16_2 = farg2 - directionZ;
        }
        temp_r0 = arg0->kind;
        temp_r4 = temp_r0 & 0x80000080;
        switch (temp_r4) {                          /* switch 1; irregular */
        case 0x80000000:
        case 0x0:                                   /* switch 1 */
            temp_r5 = arg0->primCount;
            if (temp_r5 != 0) {
                temp_r6_2 = arg0->primTarget[0];
                temp_r7 = arg0->primTarget[1];
                temp_r11 = (s32) (arg0->primRemain << 0x10) / (s32) temp_r5;
                temp_r12 = arg0->primTarget[2];
                temp_r27_3 = arg0->primTarget[3];
                color.r = (s8) ((s32) ((temp_r6_2 << 0x10) + (temp_r11 * (arg0->primColor[0] - temp_r6_2))) >> 0x10);
                color.g = (u8) ((s32) ((temp_r7 << 0x10) + (temp_r11 * (arg0->primColor[1] - temp_r7))) >> 0x10);
                color.b = (u8) ((s32) ((temp_r12 << 0x10) + (temp_r11 * (arg0->primColor[2] - temp_r12))) >> 0x10);
                color.a = (u8) ((s32) ((temp_r27_3 << 0x10) + (temp_r11 * (arg0->primColor[3] - temp_r27_3))) >> 0x10);
            } else {
                *(u32*)&color.r = (s32) *(u32*)arg0->primColor;
            }
            break;
        case 0x80:                                  /* switch 1 */
        case 0x80000080:                            /* switch 1 */
            color.a = 0xFF;
            color.b = 0xFF;
            color.g = 0xFF;
            color.r = 0xFF;
            break;
        default:
            break;
        }
        if (arg1 == NULL) {
            if (temp_r0 & 0x400) {
                GXClearVtxDesc();
                GXInvalidateVtxCache();
                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
                GXBegin(GX_QUADS, GX_VTXFMT2, 4U);
            } else {
                GXClearVtxDesc();
                GXInvalidateVtxCache();
                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
                GXBegin(GX_QUADS, GX_VTXFMT3, 4U);
            }
            temp_f0_3 = var_f16_2 - arg_sp8;
            temp_f0_4 = (f32) temp_f0_3;
            trailNearZ = PS_FIXED6(temp_f0_4);
            saved390 = (f64) (var_f15_2 - farg7);

            temp_f0_5 = (f32) saved390;
            trailNearY = PS_FIXED6(temp_f0_5);
            saved390 = (f64) (var_f14_2 - farg6);
            temp_f0_6 = (f32) saved390;
            trailNearX = PS_FIXED6(temp_f0_6);
            saved390 = (f64) temp_f0_6;
            *(volatile s16 *)0xCC008000 = trailNearX;
            *(volatile s16 *)0xCC008000 = trailNearY;
            *(volatile s16 *)0xCC008000 = trailNearZ;
            temp_r0_2 = ((((color.g * 0x10) & 0xF00 & ~0xF000) | (((u8) color.r << 8) & 0xF000)) & ~0xF0) | (color.b & 0xF0);
            *(volatile s16 *)0xCC008000 = (temp_r0_2 & ~0xF) | (((u32) (s32) ((f32) color.a * arg0->textureScale) >> 4U) & 0xF);
            temp_r5_2 = arg0->kind;
            if (temp_r5_2 & 0x400) {
                *(volatile u8 *)0xCC008000 = (s8) ((temp_r5_2 >> 0x10U) & 0xC);
            }
            temp_f0_7 = farg2 - arg_sp14;
            temp_f0_8 = (f32) temp_f0_7;
            trailCrossZ = PS_FIXED6(temp_f0_8);
            saved390 = (f64) (farg1 - arg_sp10);
            temp_f0_9 = (f32) saved390;
            trailCrossY = PS_FIXED6(temp_f0_9);
            saved390 = (f64) (farg0 - arg_spC);
            temp_f0_10 = (f32) saved390;
            trailCrossX = PS_FIXED6(temp_f0_10);
            temp_r8 = ((color.a >> 4U) & 0xF) | temp_r0_2;
            saved390 = (f64) temp_f0_10;
            *(volatile s16 *)0xCC008000 = trailCrossX;
            *(volatile s16 *)0xCC008000 = trailCrossY;
            *(volatile s16 *)0xCC008000 = trailCrossZ;
            *(volatile s16 *)0xCC008000 = temp_r8;
            temp_r6_3 = arg0->kind;
            if (temp_r6_3 & 0x400) {
                *(volatile u8 *)0xCC008000 = (s8) (((temp_r6_3 >> 0x10U) & 0xC) + 1);
            }
            temp_f0_11 = farg2 + arg_sp8;
            temp_f0_12 = (f32) temp_f0_11;
            trailPlusZ = PS_FIXED6(temp_f0_12);
            saved390 = (f64) (farg1 + farg7);
            temp_f0_13 = (f32) saved390;
            trailPlusY = PS_FIXED6(temp_f0_13);
            saved390 = (f64) (farg0 + farg6);
            temp_f0_14 = (f32) saved390;
            trailPlusX = PS_FIXED6(temp_f0_14);
            saved390 = (f64) temp_f0_14;
            *(volatile s16 *)0xCC008000 = trailPlusX;
            *(volatile s16 *)0xCC008000 = trailPlusY;
            *(volatile s16 *)0xCC008000 = trailPlusZ;
            *(volatile s16 *)0xCC008000 = temp_r8;
            temp_r6_4 = arg0->kind;
            if (temp_r6_4 & 0x400) {
                *(volatile u8 *)0xCC008000 = (s8) (((temp_r6_4 >> 0x10U) & 0xC) + 2);
            }
            trailFarZ = PS_FIXED6(var_f16_2 + arg_sp14);
            trailFarY = PS_FIXED6(var_f15_2 + arg_sp10);
            trailFarX = PS_FIXED6(var_f14_2 + arg_spC);
            *(volatile s16 *)0xCC008000 = trailFarX;
            *(volatile s16 *)0xCC008000 = trailFarY;
            *(volatile s16 *)0xCC008000 = trailFarZ;
            *(volatile s16 *)0xCC008000 = (s16) ((((u32) (s32) ((f32) color.a * arg0->textureScale) >> 4U) & 0xF) | temp_r0_2);
            temp_r3_2 = arg0->kind;
            if (temp_r3_2 & 0x400) {
                *(volatile u8 *)0xCC008000 = (s8) (((temp_r3_2 >> 0x10U) & 0xC) + 3);
            }
        } else {
            var_f0 = (arg_sp14 * arg_sp14) + ((arg_spC * arg_spC) + (arg_sp10 * arg_sp10));
            temp_f17_3 = 255.0f * (1.0f - arg0->textureScale);
            if (var_f0 > 0.0f) {
                temp_f2 = __frsqrte(var_f0);
                temp_f2_2 = 0.5 * temp_f2 * -(((f64) var_f0 * (temp_f2 * temp_f2)) - 3.0);
                temp_f2_3 = 0.5 * temp_f2_2 * -(((f64) var_f0 * (temp_f2_2 * temp_f2_2)) - 3.0);
                var_f0 = (f32) ((f64) var_f0 * (0.5 * temp_f2_3 * -(((f64) var_f0 * (temp_f2_3 * temp_f2_3)) - 3.0)));
            } else if (var_f0 < 0.0) {
                var_f0 = __float_nan[0];
            } else {
                widthClassify = var_f0;
                temp_r3_3 = *(s32*)&widthClassify & 0x7F800000;
                switch (temp_r3_3) {                /* switch 2; irregular */
                case 0x7F800000:                    /* switch 2 */
                    if (*(s32*)&widthClassify & 0x7FFFFF) {
                        var_r0 = 1;
                    } else {
                        var_r0 = 2;
                    }
                    break;
                case 0x0:                           /* switch 2 */
                    if (*(s32*)&widthClassify & 0x7FFFFF) {
                        var_r0 = 5;
                    } else {
                        var_r0 = 3;
                    }
                    break;
                default:                            /* switch 2 */
                    var_r0 = 4;
                    break;
                }
                if (var_r0 == 1) {
                    var_f0 = __float_nan[0];
                }
            }
            if (!(fabs(var_f0) < __float_min[0])) {
                temp_f3 = farg0 - var_f14_2;
                temp_f2_4 = farg1 - var_f15_2;
                temp_f4 = farg2 - var_f16_2;
                var_f5 = (temp_f4 * temp_f4) + ((temp_f3 * temp_f3) + (temp_f2_4 * temp_f2_4));
                if (var_f5 > 0.0f) {
                    temp_f2_5 = __frsqrte(var_f5);
                    temp_f2_6 = 0.5 * temp_f2_5 * -(((f64) var_f5 * (temp_f2_5 * temp_f2_5)) - 3.0);
                    temp_f2_7 = 0.5 * temp_f2_6 * -(((f64) var_f5 * (temp_f2_6 * temp_f2_6)) - 3.0);
                    var_f5 = (f32) ((f64) var_f5 * (0.5 * temp_f2_7 * -(((f64) var_f5 * (temp_f2_7 * temp_f2_7)) - 3.0)));
                } else if (var_f5 < 0.0) {
                    var_f5 = __float_nan[0];
                } else {
                    distanceClassify = var_f5;
                    temp_r3_4 = *(s32*)&distanceClassify & 0x7F800000;
                    switch (temp_r3_4) {            /* switch 3; irregular */
                    case 0x7F800000:                /* switch 3 */
                        if (*(s32*)&distanceClassify & 0x7FFFFF) {
                            var_r0_2 = 1;
                        } else {
                            var_r0_2 = 2;
                        }
                        break;
                    case 0x0:                       /* switch 3 */
                        if (*(s32*)&distanceClassify & 0x7FFFFF) {
                            var_r0_2 = 5;
                        } else {
                            var_r0_2 = 3;
                        }
                        break;
                    default:                        /* switch 3 */
                        var_r0_2 = 4;
                        break;
                    }
                    if (var_r0_2 == 1) {
                        var_f5 = __float_nan[0];
                    }
                }
                var_f1_3 = var_f5 / var_f0;
                if (var_f1_3 < 1.0f) {
                    var_f1_3 = 1.0f;
                }
                var_r30 = *arg1;
                var_r29 = (u32*)((u8*)arg1 + 4);
loop_99:
                if (var_r30 != 0) {
                    temp_r26 = ((u8*)var_r29)[0x0];
                    temp_r25 = ((u8*)var_r29)[0x1];
                    var_r29 = (u32*)((u8*)var_r29 + 4);
                    if (arg0->kind & 0x400) {
                        GXClearVtxDesc();
                        GXInvalidateVtxCache();
                        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
                        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
                        GXBegin((enum _GXPrimitive) temp_r26, GX_VTXFMT5, (u16) temp_r25);
                    } else {
                        GXClearVtxDesc();
                        GXInvalidateVtxCache();
                        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
                        GXBegin((enum _GXPrimitive) temp_r26, GX_VTXFMT3, (u16) temp_r25);
                    }
                    for (var_ctr = 0; var_ctr < temp_r25; ++var_ctr) {
                        var_f1_4 = *(f32*)var_r29;
                        temp_r3_5 = arg0->kind;
                        temp_f3_2 = 2.0f * (var_f1_4 - 0.5f);
                        if (temp_r3_5 & 0x40000) {
                            var_f1_4 = 1.0f - var_f1_4;
                        }
                        var_f2 = *(f32*)((u8*)var_r29+4);
                        var_r29 = (u32*)((u8*)var_r29 + 8);
                        var_r5 = (s32) -((var_f2 * temp_f17_3) - 255.0f);
                        if (var_r5 < 0) {
                            var_r5 = 0;
                        }
                        if (var_r5 > 0xFF) {
                            var_r5 = 0xFF;
                        }
                        temp_f4_2 = 2.0f * (var_f2 - 0.5f);
                        if (temp_r3_5 & 0x80000) {
                            var_f2 = 1.0f - var_f2;
                        }
                        trailCustomZ = PS_FIXED6((arg_sp14 * var_f1_3 * temp_f4_2) + ((arg_sp8 * temp_f3_2) + farg2));
                        saved390 = (f64) ((farg7 * temp_f3_2) + farg1);

                        trailCustomY = PS_FIXED6((arg_sp10 * var_f1_3 * temp_f4_2) + (f32) saved390);
                        saved390 = (f64) ((farg6 * temp_f3_2) + farg0);
                        trailCustomX = PS_FIXED6((arg_spC * var_f1_3 * temp_f4_2) + (f32) saved390);
                        *(volatile s16 *)0xCC008000 = trailCustomX;
                        *(volatile s16 *)0xCC008000 = trailCustomY;
                        *(volatile s16 *)0xCC008000 = trailCustomZ;
                        *(volatile s16 *)0xCC008000 = (s16) ((((u32) var_r5 >> 4U) & 0xF) | (((((color.g * 0x10) & 0xF00 & ~0xF000) | (((u8) color.r << 8) & 0xF000)) & ~0xF0) | (color.b & 0xF0)));
                        if (arg0->kind & 0x400) {
                            *(volatile f32 *)0xCC008000 = var_f1_4;
                            *(volatile f32 *)0xCC008000 = var_f2;
                        }
                }
                    var_r30 -= 1;
                    goto loop_99;
                }
            }
        }
    } else if (arg1 == NULL) {
        if (temp_r3 & 0x400) {
            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
        } else {
            GXClearVtxDesc();
            GXInvalidateVtxCache();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXBegin(GX_QUADS, GX_VTXFMT1, 4U);
        }
        temp_f0_15 = farg2 - arg_sp8;
        temp_f0_16 = (f32) temp_f0_15;
        billboardMinusZ = PS_FIXED6(temp_f0_16);
        saved390 = (f64) (farg1 - farg7);

        temp_f0_17 = (f32) saved390;
        billboardMinusY = PS_FIXED6(temp_f0_17);
        saved390 = (f64) (farg0 - farg6);
        temp_f0_18 = (f32) saved390;
        billboardMinusX = PS_FIXED6(temp_f0_18);
        saved390 = (f64) temp_f0_18;
        *(volatile s16 *)0xCC008000 = billboardMinusX;
        *(volatile s16 *)0xCC008000 = billboardMinusY;
        *(volatile s16 *)0xCC008000 = billboardMinusZ;
        temp_r4_2 = arg0->kind;
        if (temp_r4_2 & 0x400) {
            *(volatile u8 *)0xCC008000 = (s8) ((temp_r4_2 >> 0x10U) & 0xC);
        }
        billboardCrossZ = PS_FIXED6(farg2 - arg_sp14);
        billboardCrossY = PS_FIXED6(farg1 - arg_sp10);
        billboardCrossX = PS_FIXED6(farg0 - arg_spC);
        *(volatile s16 *)0xCC008000 = billboardCrossX;
        *(volatile s16 *)0xCC008000 = billboardCrossY;
        *(volatile s16 *)0xCC008000 = billboardCrossZ;
        temp_r3_6 = arg0->kind;
        if (temp_r3_6 & 0x400) {
            *(volatile u8 *)0xCC008000 = (s8) (((temp_r3_6 >> 0x10U) & 0xC) + 1);
        }
        billboardPlusZ = PS_FIXED6(farg2 + arg_sp8);
        billboardPlusY = PS_FIXED6(farg1 + farg7);
        billboardPlusX = PS_FIXED6(farg0 + farg6);
        *(volatile s16 *)0xCC008000 = billboardPlusX;
        *(volatile s16 *)0xCC008000 = billboardPlusY;
        *(volatile s16 *)0xCC008000 = billboardPlusZ;
        temp_r3_7 = arg0->kind;
        if (temp_r3_7 & 0x400) {
            *(volatile u8 *)0xCC008000 = (s8) (((temp_r3_7 >> 0x10U) & 0xC) + 2);
        }
        billboardFarZ = PS_FIXED6(farg2 + arg_sp14);
        billboardFarY = PS_FIXED6(farg1 + arg_sp10);
        billboardFarX = PS_FIXED6(farg0 + arg_spC);
        *(volatile s16 *)0xCC008000 = billboardFarX;
        *(volatile s16 *)0xCC008000 = billboardFarY;
        *(volatile s16 *)0xCC008000 = billboardFarZ;
        temp_r3_8 = arg0->kind;
        if (temp_r3_8 & 0x400) {
            *(volatile u8 *)0xCC008000 = (s8) (((temp_r3_8 >> 0x10U) & 0xC) + 3);
        }
    } else {
        var_r25 = *arg1;
        var_r29_2 = (u32*)((u8*)arg1 + 4);
loop_126:
        if (var_r25 != 0) {
            temp_r26_2 = ((u8*)var_r29_2)[0x0];
            temp_r27_4 = ((u8*)var_r29_2)[0x1];
            var_r29_2 = (u32*)((u8*)var_r29_2 + 4);
            if (arg0->kind & 0x400) {
                GXClearVtxDesc();
                GXInvalidateVtxCache();
                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
                GXBegin((enum _GXPrimitive) temp_r26_2, GX_VTXFMT4, (u16) temp_r27_4);
            } else {
                GXClearVtxDesc();
                GXInvalidateVtxCache();
                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                GXBegin((enum _GXPrimitive) temp_r26_2, GX_VTXFMT1, (u16) temp_r27_4);
            }
            for (var_ctr_2 = 0; var_ctr_2 < temp_r27_4; ++var_ctr_2) {
                var_f1_5 = *(f32*)var_r29_2;
                temp_r3_9 = arg0->kind;
                temp_f3_3 = 2.0f * (var_f1_5 - 0.5f);
                if (temp_r3_9 & 0x40000) {
                    var_f1_5 = 1.0f - var_f1_5;
                }
                var_f2_2 = *(f32*)((u8*)var_r29_2+4);
                var_r29_2 = (u32*)((u8*)var_r29_2 + 8);
                temp_f4_3 = 2.0f * (var_f2_2 - 0.5f);
                if (temp_r3_9 & 0x80000) {
                    var_f2_2 = 1.0f - var_f2_2;
                }
                customZ = PS_FIXED6((arg_sp14 * temp_f4_3) + ((arg_sp8 * temp_f3_3) + farg2));
                saved390 = (f64) ((farg7 * temp_f3_3) + farg1);

                customY = PS_FIXED6((arg_sp10 * temp_f4_3) + (f32) saved390);
                saved390 = (f64) ((farg6 * temp_f3_3) + farg0);
                customX = PS_FIXED6((arg_spC * temp_f4_3) + (f32) saved390);
                *(volatile s16 *)0xCC008000 = customX;
                *(volatile s16 *)0xCC008000 = customY;
                *(volatile s16 *)0xCC008000 = customZ;
                if (arg0->kind & 0x400) {
                    *(volatile f32 *)0xCC008000 = var_f1_5;
                    *(volatile f32 *)0xCC008000 = var_f2_2;
                }
        }
            var_r25 -= 1;
            goto loop_126;
        }
    }
}

__declspec(weak) void psDispSub(PSParticle* pp, u32* texform)
{
    f32 x;
    f32 y;
    f32 z;
    f32 right_x;
    f32 up_x;
    f32 right_y;
    f32 up_y;
    f32 right_z;
    f32 up_z;
    f32 angle;
    f32 dir_x;
    f32 dir_y;
    PSGenerator* gp;

    x = pp->position.x;
    y = pp->position.y;
    z = pp->position.z;
    if (texform != NULL) {
        right_x = rvmtx[0][0] * pp->size;
        up_x = -rvmtx[0][1] * pp->size;
        right_y = rvmtx[1][0] * pp->size;
        up_y = -rvmtx[1][1] * pp->size;
        right_z = rvmtx[2][0] * pp->size;
        up_z = -rvmtx[2][1] * pp->size;
    } else {
        right_x = rx0 * pp->size;
        up_x = rx1 * pp->size;
        right_y = ry0 * pp->size;
        up_y = ry1 * pp->size;
        right_z = rz0 * pp->size;
        up_z = rz1 * pp->size;
    }
    gp = pp->generator;
    if (gp != NULL && (gp->transformFlags & 0x20)) {
        right_x *= gp->scale.x;
        up_x *= gp->scale.x;
        right_y *= gp->scale.y;
        up_y *= gp->scale.y;
        right_z *= gp->scale.z;
        up_z *= gp->scale.z;
    }
    if ((pp->kind & 0x100000) || (pp->kind & 0x200000)) {
        if (0.0f == prj[0]) {
            f32 prev_x;
            f32 prev_y;
            f32 prev_z;
            f32 w1inv;
            f32 w1;
            f32 w0inv;
            f32 w0;

            if (pp->kind & 4) {
                reuseCalcTornadoLastPos(pp, &prev_x, &prev_y, &prev_z);
            } else {
                prev_x = pp->position.x - pp->velocity.x;
                prev_y = pp->position.y - pp->velocity.y;
                prev_z = pp->position.z - pp->velocity.z;
            }
            w0 = vmtx[2][3] +
                 (vmtx[2][2] * pp->position.z +
                  (vmtx[2][0] * pp->position.x + vmtx[2][1] * pp->position.y));
            if (0.0f == w0) {
                goto no_direction;
            }
            w0inv = -1.0f / w0;
            w1 = vmtx[2][3] + (vmtx[2][2] * prev_z +
                               (vmtx[2][0] * prev_x + vmtx[2][1] * prev_y));
            if (0.0f == w1) {
                goto no_direction;
            }
            w1inv = -1.0f / w1;
            dir_x = w0inv * (pvmtx[0][3] + (pvmtx[0][2] * pp->position.z +
                                            (pvmtx[0][0] * pp->position.x +
                                             pvmtx[0][1] * pp->position.y))) -
                    w1inv * (pvmtx[0][3] + (pvmtx[0][2] * prev_z +
                                            (pvmtx[0][0] * prev_x +
                                             pvmtx[0][1] * prev_y)));
            dir_y = w0inv * (pvmtx[1][3] + (pvmtx[1][2] * pp->position.z +
                                            (pvmtx[1][0] * pp->position.x +
                                             pvmtx[1][1] * pp->position.y))) -
                    w1inv * (pvmtx[1][3] + (pvmtx[1][2] * prev_z +
                                            (pvmtx[1][0] * prev_x +
                                             pvmtx[1][1] * prev_y)));
        } else if (pp->kind & 4) {
            f32 prev_x;
            f32 prev_y;
            f32 prev_z;
            f32 dx;
            f32 dy;
            f32 dz;

            reuseCalcTornadoLastPos(pp, &prev_x, &prev_y, &prev_z);
            dx = pp->position.x - prev_x;
            dy = pp->position.y - prev_y;
            dz = pp->position.z - prev_z;
            dir_x = pvmtx[0][2] * dz + (pvmtx[0][0] * dx + pvmtx[0][1] * dy);
            dir_y = pvmtx[1][2] * dz + (pvmtx[1][0] * dx + pvmtx[1][1] * dy);
        } else {
            dir_x = pvmtx[0][2] * pp->velocity.z +
                    (pvmtx[0][0] * pp->velocity.x + pvmtx[0][1] * pp->velocity.y);
            dir_y = pvmtx[1][2] * pp->velocity.z +
                    (pvmtx[1][0] * pp->velocity.x + pvmtx[1][1] * pp->velocity.y);
        }
        if (fabs(dir_y) < (__float_min[0])) {
            angle = (dir_x >= 0.0f) ? 1.5707964f : -1.5707964f;
        } else {
            angle = atan2f(dir_x, dir_y);
        }
        if (pp->kind & 0x200000) {
            angle += pp->rotate;
        }
    } else {
    no_direction:
        angle = pp->rotate;
    }
    if (fabs(angle) > 0.01) {
        PSMtx mtx;
        PSVec axis;
        f32 rx = right_x;
        f32 ry = right_y;
        f32 rz = right_z;
        f32 ux = up_x;
        f32 uy = up_y;
        f32 uz = up_z;

        axis.x = ry * uz - rz * uy;
        axis.y = rz * ux - rx * uz;
        axis.z = rx * uy - ry * ux;
        PSMTXRotAxisRad(mtx, &axis, angle);
        right_x = mtx[0][2] * rz + (mtx[0][0] * rx + mtx[0][1] * ry);
        right_y = mtx[1][2] * rz + (mtx[1][0] * rx + mtx[1][1] * ry);
        right_z = mtx[2][2] * rz + (mtx[2][0] * rx + mtx[2][1] * ry);
        up_x = mtx[0][2] * uz + (mtx[0][0] * ux + mtx[0][1] * uy);
        up_y = mtx[1][2] * uz + (mtx[1][0] * ux + mtx[1][1] * uy);
        up_z = mtx[2][2] * uz + (mtx[2][0] * ux + mtx[2][1] * uy);
    }
    psDispSubMakePolygon(pp, texform, x, y, z, pp->velocity.x, pp->velocity.y,
                         pp->velocity.z, right_x, right_y, right_z, up_x, up_y,
                         up_z);
}

enum HSD_ParticleKind {
    Tornado = 1 << 2,
    TexEdge = 1 << 3,
    ComTLUT = 1 << 4,
    MirrorS = 1 << 5,
    MirrorT = 1 << 6,
    PrimEnv = 1 << 7,
    TexInterpNear = 1 << 9,
    DispTexture = 1 << 10,
    TexFlipS = 1 << 18,
    TexFlipT = 1 << 19,
    Trail = 1 << 20,
    DirVec = 1 << 21,
    DispFog = 1 << 24,
    NoZComp = 1 << 28,
    DispPoint = 1 << 30,
    DispLighting = 1 << 31
};

#define PS_FLAG_HIDDEN 0x20000000

static inline void setVtxDesc(s32 fmt)
{
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    switch (fmt) {
    case 0:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        return;
    case 1:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        return;
    case 2:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        return;
    case 3:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        return;
    case 4:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        return;
    case 5:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        return;
    }
}

static inline void psSetColor(GXColor* color, u8 value)
{
    color->r = value;
    color->g = value;
    color->b = value;
    color->a = value;
}

static inline void setupChanCtrl(PSParticle* pp)
{
    u32 chan_state = pp->kind & (DispLighting | Trail);

    if (chan_state != (u32) prevChanCtrl) {
        prevChanCtrl = chan_state;
        GXSetNumChans(1);
        switch (prevChanCtrl) {
        case Trail:
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0,
                          GX_DF_NONE, GX_AF_NONE);
            break;
        case DispLighting:
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG,
                          HSD_LObjGetLightMaskDiffuse(), GX_DF_NONE,
                          (s32) HSD_LObjGetLightMaskAttnFunc() ? GX_AF_SPOT
                                                         : GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0,
                          GX_DF_NONE, GX_AF_NONE);
            break;
        case DispLighting | Trail:
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG,
                          HSD_LObjGetLightMaskDiffuse(), GX_DF_NONE,
                          (s32) HSD_LObjGetLightMaskAttnFunc() ? GX_AF_SPOT
                                                         : GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0,
                          GX_DF_NONE, GX_AF_NONE);
            break;
        default:
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0,
                          GX_DF_NONE, GX_AF_NONE);
            break;
        }
    }
}

static inline void setBlendMode(int blend_mode)
{
    if (prevBlendMode != blend_mode) {
        prevBlendMode = blend_mode;
        switch (blend_mode) {
        case 0:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                           GX_LO_CLEAR);
            break;
        case 1:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE,
                           GX_LO_CLEAR);
            break;
        case 2:
            GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                           GX_LO_CLEAR);
            break;
        case 3:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTCLR, GX_BL_ZERO,
                           GX_LO_CLEAR);
            break;
        default:
            OSReport("Particle:setBlendMode:Unknown mode\n");
            break;
        }
    }
}

static inline void psSetCurrentMtx(GXPosNrmMtx idx)
{
    if (currentMtx != idx) {
        currentMtx = idx;
        GXSetCurrentMtx(idx);
    }
}

static inline void psSetupVtxFormat(GXVtxFmt format, BOOL has_color,
                                    BOOL has_texture, GXCompType texture_type)
{
    GXSetVtxAttrFmt(format, GX_VA_POS, GX_POS_XYZ, GX_S16, 6U);
    if (has_color) {
        GXSetVtxAttrFmt(format, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0U);
    }
    if (has_texture) {
        GXSetVtxAttrFmt(format, GX_VA_TEX0, GX_TEX_ST, texture_type, 0U);
    }
}

static void _psDispParticlesSub(u32 arg0, s32 arg1, PSGenerator *arg2, u32 arg3) {
    typedef struct _HSD_TlutDesc {
        u16* lut;
        GXTlutFmt fmt;
        u32 tlut_name;
        u16 n_entries;
    } HSD_TlutDesc;
    typedef struct _HSD_PSFormGroup {
        u32 num;
        u8* formTable[1];
    } HSD_PSFormGroup;
    s32 linkNo;
    u32 prevTexEdge;
    s32 alpha_compare_mode;
    u8 prevACmpParam1;
    u8 prevACmpParam2;
    s32 needs_setup;
    PSParticle* pp;
    void* prevTex;
    u32 prevMirror;
    u16* prevLut;
    HSD_TlutDesc tlutdesc;
    GXTexObj texObj;
    PSParticle* sorted_particles;
    PSParticle* non_edge_particles;
    GXTlutObj gx_tlut_obj;
    s32 prev_tex_interp_near;
    u32 prev_kind;

    alpha_compare_mode = 0;
    prev_tex_interp_near = 0;
    prevACmpParam1 = 0;
    prevACmpParam2 = 0xFF;
    needs_setup = 1;
    for (linkNo = 0; linkNo < 16; linkNo++) {
        if (arg0 & (1 << linkNo)) {
            particleSort(linkNo, &sorted_particles, &non_edge_particles);
            switch (arg1) {
            case 1:
                pp = sorted_particles;
                break;
            case 2:
                pp = non_edge_particles;
                break;
            default:
                continue;
            }
            while (pp != NULL) {
                PSTex* tex_group = NULL;
                HSD_PSFormGroup* form_group = NULL;
                HSD_PSFormGroup** form_groups;
                u8* form = NULL;
                GXTexFmt fmt;
                int blend_mode;
                u8 alpha0;
                u8 alpha1;
                u32 width;
                u32 height;
                void* image;
                GXTexWrapMode wrap_s;
                f32 scale_s;
                f32 scale_t;
                GXTexWrapMode wrap_t;
                void** tex_table;

                if (((u32) arg1 == 1) && !(pp->kind & TexEdge)) {
                    break;
                }
                if (!(pp->size < __float_epsilon[0]) &&
                    (arg2 == NULL || pp->id == arg2->id) &&
                    (u32) pp->generator->camera == arg3 &&
                    !(pp->kind & PS_FLAG_HIDDEN))
                {
                    if (needs_setup != 0) {
                        prevLut = NULL;
                        prevPointSize = -1;
                        prevTex = NULL;
                        prevLineWidth = -1;
                        prevChanCtrl = -1;
                        psSetupTevInvalidState();
                        prevMirror = (u32) -1;
                        prev_kind &= 0xFEFFFFFF;
                        prevTexEdge = (u32) -1;
                        HSD_FogSet(NULL);
                        prevChanMat.r = prevChanMat.g = prevChanMat.b = 0xFF;
                        prevChanAmb.r = prevChanAmb.g = prevChanAmb.b = 0xFF;
                        prevChanMat.a = prevChanAmb.a = 0xFF;
                        GXSetChanMatColor(GX_COLOR0A0, prevChanMat);
                        GXSetChanAmbColor(GX_COLOR0A0, prevChanAmb);
                        psSetupTevInvalidState();
                        psSetupTevCommon();
                        psSetColor(&prevColorPrim, 0xFF);
                        psSetColor(&prevColorEnv, 0);
                        psSetColor(&prevColorMat, 0xFF);
                        GXSetTevColor(GX_TEVREG0, prevColorPrim);
                        GXSetTevColor(GX_TEVREG1, prevColorEnv);
                        GXSetTevColor(GX_TEVREG2, prevColorMat);
                        prevBlendMode = -1;
                        GXSetZCompLoc(GX_FALSE);
                        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), vmtx);
                        PSMTXInverse(vmtx, rvmtx);
                        {
                            if (0.0f == prj[0]) {
                                pvmtx[0][0] = prj[1] * vmtx[0][0] + prj[2] * vmtx[2][0];
                                pvmtx[0][1] = prj[1] * vmtx[0][1] + prj[2] * vmtx[2][1];
                                pvmtx[0][2] = prj[1] * vmtx[0][2] + prj[2] * vmtx[2][2];
                                pvmtx[0][3] = prj[1] * vmtx[0][3] + prj[2] * vmtx[2][3];
                                pvmtx[1][0] = prj[3] * vmtx[1][0] + prj[4] * vmtx[2][0];
                                pvmtx[1][1] = prj[3] * vmtx[1][1] + prj[4] * vmtx[2][1];
                                pvmtx[1][2] = prj[3] * vmtx[1][2] + prj[4] * vmtx[2][2];
                                pvmtx[1][3] = prj[3] * vmtx[1][3] + prj[4] * vmtx[2][3];
                            } else {
                                pvmtx[0][0] = prj[1] * vmtx[0][0] + prj[2];
                                pvmtx[0][1] = prj[1] * vmtx[0][1] + prj[2];
                                pvmtx[0][2] = prj[1] * vmtx[0][2] + prj[2];
                                pvmtx[0][3] = prj[1] * vmtx[0][3] + prj[2];
                                pvmtx[1][0] = prj[3] * vmtx[1][0] + prj[4];
                                pvmtx[1][1] = prj[3] * vmtx[1][1] + prj[4];
                                pvmtx[1][2] = prj[3] * vmtx[1][2] + prj[4];
                                pvmtx[1][3] = prj[3] * vmtx[1][3] + prj[4];
                            }
                            rx0 = rvmtx[0][0] + rvmtx[0][1];
                            rx1 = rvmtx[0][0] - rvmtx[0][1];
                            ry0 = rvmtx[1][0] + rvmtx[1][1];
                            ry1 = rvmtx[1][0] - rvmtx[1][1];
                            rz0 = rvmtx[2][0] + rvmtx[2][1];
                            rz1 = rvmtx[2][0] - rvmtx[2][1];
                        }
                        GXLoadPosMtxImm(vmtx, GX_PNMTX0);
                        {
                            PSMtx billboard_mtx = { { 1.0F, 0.0F, 0.0F, 0.0F },
                                                    { 0.0F, 1.0F, 0.0F, 0.0F },
                                                    { 0.0F, 0.0F, 1.0F, 0.0F } };
                            GXLoadPosMtxImm(billboard_mtx, GX_PNMTX1);
                        }
                        currentMtx = GX_PNMTX1;
                        psSetCurrentMtx(GX_PNMTX0);
                        GXEnableTexOffsets(GX_TEXCOORD0, GX_TRUE, GX_TRUE);
                        HSD_MtxGetRotationMtx(rvmtx, rvmtxRot, 'z', 'x');
                        GXSetCullMode(GX_CULL_BACK);
                        GXSetArray(GX_VA_TEX0, billboard_tex0_u8, 2);
                        psSetupVtxFormat(GX_VTXFMT0, FALSE, TRUE, GX_U8);
                        psSetupVtxFormat(GX_VTXFMT1, FALSE, FALSE, GX_U8);
                        psSetupVtxFormat(GX_VTXFMT2, TRUE, TRUE, GX_U8);
                        psSetupVtxFormat(GX_VTXFMT3, TRUE, FALSE, GX_U8);
                        psSetupVtxFormat(GX_VTXFMT4, FALSE, TRUE, GX_F32);
                        psSetupVtxFormat(GX_VTXFMT5, TRUE, TRUE, GX_F32);
                        needs_setup = 0;
                    }

                    blend_mode = (pp->kind >> 0x16U) & 3;
                    setBlendMode(blend_mode);

                    if (pp->alphaCount != 0) {
                        s32 scale = (65536 * pp->alphaRemain) / pp->alphaCount;
                        alpha0 = ((pp->alpha1Target << 16) +
                                  scale * (pp->alpha1 -
                                           pp->alpha1Target)) >>
                                 16;
                        alpha1 = ((pp->alpha2Target << 16) +
                                  scale * (pp->alpha2 -
                                           pp->alpha2Target)) >>
                                 16;
                    } else {
                        alpha0 = pp->alpha1;
                        alpha1 = pp->alpha2;
                    }
                    if ((alpha_compare_mode != pp->alphaMode) ||
                        (prevACmpParam1 != alpha0) ||
                        (prevACmpParam2 != alpha1))
                    {
                        alpha_compare_mode = pp->alphaMode;
                        prevACmpParam1 = alpha0;
                        prevACmpParam2 = alpha1;
                        GXSetAlphaCompare(
                            (alpha_compare_mode >> 3) & 7, prevACmpParam1,
                            (alpha_compare_mode >> 6) & 3,
                            alpha_compare_mode & 7, prevACmpParam2);
                    }

                    psSetupTev(pp);
                    setupChanCtrl(pp);
                    setupChanReg(pp);
                    setupTevReg(pp);
                    if ((pp->kind & (TexEdge | NoZComp)) != prevTexEdge) {
                        prevTexEdge = pp->kind & (TexEdge | NoZComp);
                        if (prevTexEdge & TexEdge) {
                            GXSetZMode((pp->kind & NoZComp) ? GX_FALSE : GX_TRUE,
                                       GX_LEQUAL, GX_TRUE);
                        } else {
                            GXSetZMode((pp->kind & NoZComp) ? GX_FALSE : GX_TRUE,
                                       GX_LEQUAL, GX_FALSE);
                        }
                    }
                    if (((pp->kind ^ prev_kind) & DispFog) != 0) {
                        if (pp->kind & DispFog) {
                            HSD_FogSet(particleFog);
                        } else {
                            HSD_FogSet(NULL);
                        }
                    }



                    form_groups = (HSD_PSFormGroup**) psFormGroupArray[pp->bank];
                    if (form_groups != NULL &&
                        (form_group = form_groups[pp->texGroup]) != NULL
                        && form_group->formTable != NULL
                    )
                    {
                        form = form_group->formTable[pp->pose];
                    } else {
                        form = NULL;
                    }

                    if (pp->kind & DispTexture) {
                        if (pp->kind & MirrorS) {
                            scale_s = 2.0f;
                            wrap_s = GX_MIRROR;
                        } else {
                            scale_s = 1.0f;
                            wrap_s = GX_CLAMP;
                        }
                        if (pp->kind & MirrorT) {
                            scale_t = 2.0f;
                            wrap_t = GX_MIRROR;
                        } else {
                            scale_t = 1.0f;
                            wrap_t = GX_CLAMP;
                        }
                        if ((pp->kind & (MirrorS | MirrorT)) != prevMirror) {
                            PSMtx temp_mtx;

                            prevMirror = pp->kind & (MirrorS | MirrorT);
                            prevTex = NULL;
                            PSMTXScale(temp_mtx, scale_s, scale_t, 1.0f);
                            if (pp->kind & MirrorT) {
                                temp_mtx[1][3] = 1.0f;
                            }
                            GXLoadTexMtxImm(temp_mtx, GX_TEXMTX0, GX_MTX2x4);
                            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4,
                                              GX_TG_TEX0, GX_TEXMTX0, GX_FALSE,
                                              GX_PTIDENTITY);
                        }
                        tex_group = psTexGroupArray[pp->bank][pp->texGroup];
                        if (tex_group != NULL) {
                            fmt = tex_group->format;
                            tex_table = tex_group->textures;
                            width = tex_group->width;
                            height = tex_group->height;
                        } else {
                            fmt = 0;
                            height = 0;
                            width = 0;
                            tex_table = NULL;
                        }
                        if (tex_table != NULL) {
                            image = tex_table[pp->pose];
                        } else {
                            image = NULL;
                        }
                        if ((fmt == GX_TF_C4) || (fmt == GX_TF_C8)) {
                            if (tex_table != NULL) {
                                void** palettes =
                                    (void**) &tex_table[tex_group->count];
                                if (palettes != NULL) {
                                    if (pp->palette != 0xFF) {
                                        tlutdesc.lut = palettes[pp->palette];
                                    } else if (!(pp->kind & ComTLUT)) {
                                        tlutdesc.lut = palettes[pp->pose];
                                    } else {
                                        tlutdesc.lut = palettes[0];
                                    }
                                    if (tlutdesc.lut != prevLut) {
                                        tlutdesc.fmt = (GXTlutFmt)
                                                           tex_group->paletteFormat;
                                        tlutdesc.tlut_name = GX_TLUT0;
                                        tlutdesc.n_entries =
                                            (fmt == GX_TF_C4) ? 16 : 256;
                                        GXInitTlutObj(
                                            &gx_tlut_obj, tlutdesc.lut,
                                            tlutdesc.fmt, tlutdesc.n_entries);
                                        GXLoadTlut(&gx_tlut_obj,
                                                   tlutdesc.tlut_name);
                                    }
                                    prevTex = NULL;
                                }
                            }
                        }
                        if ((prevTex != image) && (image != NULL)) {
                            prevTex = image;
                            switch (fmt) {
                            case GX_TF_C4:
                            case GX_TF_C8:
                                GXInitTexObjCI(&texObj, image, width, height,
                                               fmt, wrap_s, wrap_t, GX_FALSE,
                                               GX_TLUT0);
                                break;
                            case GX_TF_I4:
                            case GX_TF_I8:
                            case GX_TF_IA4:
                            case GX_TF_IA8:
                            case GX_TF_RGB565:
                            case GX_TF_RGB5A3:
                            case GX_TF_RGBA8:
                            case GX_TF_CMPR:
                                GXInitTexObj(&texObj, image, width, height,
                                             fmt, wrap_s, wrap_t, GX_FALSE);
                                break;
                            default:
                                __assert("psdisp.c", 0x7AD, "0");
                                break;
                            }
                            prev_tex_interp_near = pp->kind & TexInterpNear;
                            GXInitTexObjLOD(
                                &texObj,
                                (prev_tex_interp_near != 0) ? GX_NEAR
                                                            : GX_LINEAR,
                                ((pp->kind >> 9) & 1) ? GX_NEAR : GX_LINEAR,
                                0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                GX_ANISO_1);
                            GXLoadTexObj(&texObj, GX_TEXMAP0);
                        }
                        if ((u32) prev_tex_interp_near !=
                            (pp->kind & TexInterpNear))
                        {
                            prev_tex_interp_near = pp->kind & TexInterpNear;
                            GXInitTexObjLOD(
                                &texObj,
                                (prev_tex_interp_near != 0) ? GX_NEAR
                                                            : GX_LINEAR,
                                (s32) (pp->kind & TexInterpNear) != 0
                                    ? GX_NEAR
                                    : GX_LINEAR,
                                0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                GX_ANISO_1);
                            GXLoadTexObj(&texObj, GX_TEXMAP0);
                        }
                    }

                    if (pp->kind & DispPoint) {
                        if (pp->appsrt != NULL) {
                            psDispSubAPPSRTPoint(pp);
                        } else if (pp->kind & Trail) {
                            pp = psDispSubPointTrail(pp);
                        } else {
                            u8 point_size;

                            psSetCurrentMtx(GX_PNMTX0);
                            point_size = (pp->size > 42.5) ? 255.0f : 6.0f * pp->size;
                            if (prevPointSize != (s32) point_size) {
                                prevPointSize = point_size;
                                GXSetPointSize(point_size, GX_TO_ONE);
                            }
                            if (pp->kind & DispTexture) {
                                setVtxDesc(0);
                                GXBegin(GX_POINTS, GX_VTXFMT0, 1);
                            } else {
                                setVtxDesc(1);
                                GXBegin(GX_POINTS, GX_VTXFMT1, 1);
                            }
                            GXPosition3s16(PS_FIXED6(pp->position.x), PS_FIXED6(pp->position.y), PS_FIXED6(pp->position.z));
                            if (pp->kind & DispTexture) {
                                GXTexCoord1x8(1);
                            }
                        }
                    } else if (pp->appsrt != NULL) {
                        psDispSubAppSRT(pp, (u32*) form);
                    } else {
                        psDispSub(pp, (u32*) form);
                    }
                }

                prev_kind = pp->kind;
                pp = pp->next;
            }
        }
    }
    if (needs_setup == 0) {
        HSD_StateInvalidate(-1);
    }
}

void psDispSetProjection(f32 *arg0) {
    memcpy(prj, arg0, 0x1CU);
}

void psDispParticles(u32 arg0, s32 arg1, u32 arg2) {
    _psDispParticlesSub(arg0, arg1, NULL, arg2);
}
