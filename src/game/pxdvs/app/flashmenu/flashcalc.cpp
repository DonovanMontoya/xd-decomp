#include <dolphin/types.h>
struct FlashPoint {f32 unk0,unk4;};struct FlashCurve {f32 unk0,unk4,unk8,unkC,unk10,unk14;};struct FlashMatrix {f32 unk0,unk4,unk8,unkC,unk10,unk14;};struct FlashFixedMatrix {s32 unk0,unk4,unk8,unkC,unk10,unk14;};struct FlashCxform {s16 unk0,unk2,unk4,unk6,unk8,unkA,unkC,unkE;};
extern "C" void flcalcBezier3(FlashPoint *arg0, FlashCurve *arg1, f32 farg0) {
    f32 temp_f5;
    f32 temp_f6;
    f32 temp_f7;

    temp_f7 = farg0 * farg0;
    temp_f5 = 1.0f - farg0;
    temp_f6 = temp_f5 * temp_f5;
    arg0->unk0 = (f32) ((arg1->unk10 * temp_f7) + ((arg1->unk0 * temp_f6) + (farg0 * (2.0f * arg1->unk8 * temp_f5))));
    arg0->unk4 = (f32) ((arg1->unk14 * temp_f7) + ((arg1->unk4 * temp_f6) + (farg0 * (2.0f * arg1->unkC * temp_f5))));
}

extern "C" void flcalcConvFlashMatrix(FlashMatrix*out,FlashFixedMatrix*in){f32 a=in->unk0,b=in->unk4,c=in->unk8,d=in->unkC,e=in->unk10,f=in->unk14;out->unk0=a/65536.0f;out->unk4=b/65536.0f;out->unk8=c/65536.0f;out->unkC=d/65536.0f;out->unk10=e/20.0f;out->unk14=f/20.0f;}

extern "C" s32 flcalcBlendColor(u32 arg0, u32 arg1, f32 farg0) {
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f3;

    temp_f3 = (f32) (arg0 >> 0x18U);
    temp_f30 = (f32)(arg0&0xFFU);
    temp_f29 = (f32) ((arg0 & 0xFF0000U)>>16);
    temp_f28 = (f32) ((arg0 & 0xFF00U)>>8);
    return ((u32) ((farg0 * ((f32) ((arg1 & 0xFF00U)>>8) - temp_f28)) + temp_f28) << 8) | (((u32) ((farg0 * ((f32) ((arg1 & 0xFF0000U)>>16) - temp_f29)) + temp_f29) << 0x10) | ((u32) ((farg0 * ((f32)(arg1&0xFFU) - temp_f30)) + temp_f30) | ((u32) ((farg0 * ((f32) (arg1 >> 0x18U) - temp_f3)) + temp_f3) << 0x18)));
}

extern "C" s32 flcalcBlend(s32 arg0, s32 arg1, f32 farg0) {
    return (s32) ((farg0 * (f32) (arg1 - arg0)) + (f32) arg0);
}

extern "C" void flcalcCreateCxform(FlashCxform *p, u32 color) {
    s16 r = color >> 24;
    s16 g = (color >> 16) & 0xFFU;
    s16 b = (color >> 8) & 0xFFU;
    s16 a = color & 0xFFU;
    p->unk4 = 256;
    p->unk8 = 256;
    p->unkC = 256;
    p->unk0 = 256;
    p->unk6 = 0;
    p->unkA = 0;
    p->unkE = 0;
    p->unk2 = 0;
    p->unk4 = r;
    p->unk8 = g;
    p->unkC = b;
    p->unk0 = a;
}

extern "C" s32 flcalcMultiTransformColor(FlashCxform *arg0, u32 arg1) {
    u32 var_r4;
    u32 var_r5;
    u32 var_r6;
    u32 var_r7;

    var_r5 = arg0->unk6 + ((u32) ((arg1 >> 0x18U) * arg0->unk4) >> 8U);
    if (var_r5 < 0xFFU) {

    } else {
        var_r5 = 0xFF;
    }
    var_r6 = arg0->unkA + ((u32) (((arg1 & 0xFF0000U)>>16) * arg0->unk8) >> 8U);
    if (var_r6 < 0xFFU) {

    } else {
        var_r6 = 0xFF;
    }
    var_r4 = arg0->unkE + ((u32) (((arg1 & 0xFF00U)>>8) * arg0->unkC) >> 8U);
    if (var_r4 < 0xFFU) {

    } else {
        var_r4 = 0xFF;
    }
    var_r7 = arg0->unk2 + ((u32) ((arg1&0xFFU) * arg0->unk0) >> 8U);
    if (var_r7 < 0xFFU) {

    } else {
        var_r7 = 0xFF;
    }
    return (var_r4 << 8) | ((var_r6 << 0x10) | (var_r7 | (var_r5 << 0x18)));
}

extern "C" void flcalcUnitCxform(FlashCxform *arg0) {
    arg0->unk4 = 0x100;
    arg0->unk8 = 0x100;
    arg0->unkC = 0x100;
    arg0->unk0 = 0x100;
    arg0->unk6 = 0;
    arg0->unkA = 0;
    arg0->unkE = 0;
    arg0->unk2 = 0;
}

extern "C" void flcalcMulCxform(FlashCxform *arg0, FlashCxform *arg1, FlashCxform *arg2) {
    arg0->unk4 = (s16) ((s32) (arg1->unk4 * arg2->unk4) / 256);
    arg0->unk8 = (s16) ((s32) (arg1->unk8 * arg2->unk8) / 256);
    arg0->unkC = (s16) ((s32) (arg1->unkC * arg2->unkC) / 256);
    arg0->unk0 = (s16) ((s32) (arg1->unk0 * arg2->unk0) / 256);
    arg0->unk6 = (s16) (arg1->unk6 + arg2->unk6);
    arg0->unkA = (s16) (arg1->unkA + arg2->unkA);
    arg0->unkE = (s16) (arg1->unkE + arg2->unkE);
    arg0->unk2 = (s16) (arg1->unk2 + arg2->unk2);
}

static inline void concatLinearValues(FlashMatrix *arg0, FlashMatrix *arg1, f32 a, f32 b, f32 c, f32 d) {
    arg0->unk0 = (f32) ((arg1->unk0 * a) + (arg1->unk4 * c));
    arg0->unk4 = (f32) ((arg1->unk0 * b) + (arg1->unk4 * d));
    arg0->unk8 = (f32) ((arg1->unk8 * a) + (arg1->unkC * c));
    arg0->unkC = (f32) ((arg1->unk8 * b) + (arg1->unkC * d));
    arg0->unk10 = arg1->unk10;
    arg0->unk14 = arg1->unk14;
}

static inline void concatAffineValues(FlashMatrix *arg0, FlashMatrix *arg1, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f) {
    arg0->unk0 = (f32) ((arg1->unk0 * a) + (arg1->unk4 * c));
    arg0->unk4 = (f32) ((arg1->unk0 * b) + (arg1->unk4 * d));
    arg0->unk8 = (f32) ((arg1->unk8 * a) + (arg1->unkC * c));
    arg0->unkC = (f32) ((arg1->unk8 * b) + (arg1->unkC * d));
    arg0->unk10 = (f32) (e + ((arg1->unk10 * a) + (arg1->unk14 * c)));
    arg0->unk14 = (f32) (f + ((arg1->unk10 * b) + (arg1->unk14 * d)));
}


extern "C" void flcalcMulMatrixf(FlashMatrix *arg0, FlashMatrix *arg1, FlashMatrix *arg2) {
    arg0->unk0 = (f32) ((arg1->unk0 * arg2->unk0) + (arg1->unk4 * arg2->unk8));
    arg0->unk4 = (f32) ((arg1->unk0 * arg2->unk4) + (arg1->unk4 * arg2->unkC));
    arg0->unk8 = (f32) ((arg1->unk8 * arg2->unk0) + (arg1->unkC * arg2->unk8));
    arg0->unkC = (f32) ((arg1->unk8 * arg2->unk4) + (arg1->unkC * arg2->unkC));
    arg0->unk10 = (f32) (arg2->unk10 + ((arg1->unk10 * arg2->unk0) + (arg1->unk14 * arg2->unk8)));
    arg0->unk14 = (f32) (arg2->unk14 + ((arg1->unk10 * arg2->unk4) + (arg1->unk14 * arg2->unkC)));
}

extern "C" void flcalcUnitMatrix2(FlashFixedMatrix *arg0) {
    arg0->unk0 = 0x10000;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0x10000;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
}

extern "C" void flcalcUnitMatrix(FlashMatrix *arg0) {
    arg0->unk0 = 1.0f;
    arg0->unk4 = 0.0f;
    arg0->unk8 = 0.0f;
    arg0->unkC = 1.0f;
    arg0->unk10 = 0.0f;
    arg0->unk14 = 0.0f;
}

extern "C" void flcalcMatrixCopy(FlashMatrix *arg0, FlashMatrix *arg1) {
    arg0->unk0 = (f32) arg1->unk0;
    arg0->unk4 = (f32) arg1->unk4;
    arg0->unk8 = (f32) arg1->unk8;
    arg0->unkC = (f32) arg1->unkC;
    arg0->unk10 = (f32) arg1->unk10;
    arg0->unk14 = (f32) arg1->unk14;
}

extern "C" void flcalcMatrixTranslate(FlashMatrix *out, FlashMatrix *in, FlashPoint *point) {
    f32 tx = point->unk0;
    f32 ty = point->unk4;
    concatAffineValues(out, in, 1.0f, 0.0f, 0.0f, 1.0f, tx, ty);
}

extern "C" void flcalcMatrixScale(FlashMatrix *out, FlashMatrix *in, FlashPoint *point) {
    concatLinearValues(out, in, point->unk0, 0.0f, 0.0f, point->unk4);
}

extern "C" void flcalcMatrix(FlashPoint*out,FlashMatrix*matrix,FlashPoint*point){FlashPoint p=*point;f32 x=matrix->unk0*p.unk0+matrix->unk8*p.unk4;f32 y=matrix->unk4*p.unk0+matrix->unkC*p.unk4;out->unk0=matrix->unk10+x;out->unk4=matrix->unk14+y;}
