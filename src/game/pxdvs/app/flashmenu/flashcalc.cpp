#include <game/pxdvs/app/flashmenu/flashShape.hpp>

extern "C" void flcalcBezier3(GSvec2* out, GSvec2 points[3], f32 t) {
    f32 remaining, remainingSquared, tSquared;
    tSquared = t * t;
    remaining = 1.0f - t;
    remainingSquared = remaining * remaining;
    out->x = points[2].x * tSquared + (points[0].x * remainingSquared + t * (2.0f * points[1].x * remaining));
    out->y = points[2].y * tSquared + (points[0].y * remainingSquared + t * (2.0f * points[1].y * remaining));
}

extern "C" void flcalcConvFlashMatrix(FLASHMATRIXF* out, FLASHMATRIX* in) {
    f32 a = in->m[0], b = in->m[1], c = in->m[2], d = in->m[3];
    f32 tx = in->m[4], ty = in->m[5];
    out->m[0] = a / 65536.0f;
    out->m[1] = b / 65536.0f;
    out->m[2] = c / 65536.0f;
    out->m[3] = d / 65536.0f;
    out->m[4] = tx / 20.0f;
    out->m[5] = ty / 20.0f;
}

extern "C" u32 flcalcBlendColor(u32 arg0, u32 arg1, f32 farg0) {
    f32 alpha;
    f32 green;
    f32 blue;
    f32 red;

    alpha = (f32)(arg0 & 0xFFU);
    red = (f32)(arg0 >> 0x18U);
    green = (f32)((arg0 >> 16U) & 255U);
    blue = (f32)((arg0 >> 8U) & 255U);
    return ((u32)(farg0 * ((f32)((arg1 >> 8) & 255) - blue) + blue) << 8) |
           (((u32)(farg0 * ((f32)((arg1 >> 16) & 255) - green) + green) << 16) |
            ((u32)(farg0 * ((f32)(arg1 & 255) - alpha) + alpha) |
             ((u32)(farg0 * ((f32)(arg1 >> 24) - red) + red) << 24)));
}

extern "C" s32 flcalcBlend(s32 arg0, s32 arg1, f32 farg0) {
    return (s32) ((farg0 * (f32) (arg1 - arg0)) + (f32) arg0);
}

extern "C" void flcalcCreateCxform(FLASHCXFORM *p, u32 color) {
    s16 r = color >> 24;
    s16 g = (color >> 16) & 0xFFU;
    s16 b = (color >> 8) & 0xFFU;
    s16 a = color & 0xFFU;
    p->red.multiplier = 256;
    p->green.multiplier = 256;
    p->blue.multiplier = 256;
    p->alpha.multiplier = 256;
    p->red.offset = 0;
    p->green.offset = 0;
    p->blue.offset = 0;
    p->alpha.offset = 0;
    p->red.multiplier = r;
    p->green.multiplier = g;
    p->blue.multiplier = b;
    p->alpha.multiplier = a;
}

#define FLCALC_CLAMP(x) ((x) < 0xFF ? (x) : 0xFF)
extern "C" u32 flcalcMultiTransformColor(FLASHCXFORM* ct, u32 color) {
    u32 cr = color >> 24;
    u32 cg = (color >> 16) & 0xFF;
    u32 cb = (color >> 8) & 0xFF;
    u32 ca = color & 0xFF;
    u32 r = FLCALC_CLAMP(((cr * ct->red.multiplier) >> 8) + ct->red.offset);
    u32 g = FLCALC_CLAMP(((cg * ct->green.multiplier) >> 8) + ct->green.offset);
    u32 b = FLCALC_CLAMP(((cb * ct->blue.multiplier) >> 8) + ct->blue.offset);
    u32 a = FLCALC_CLAMP(((ca * ct->alpha.multiplier) >> 8) + ct->alpha.offset);
    return a | (r << 24) | (g << 16) | (b << 8);
}
#undef FLCALC_CLAMP

extern "C" void flcalcUnitCxform(FLASHCXFORM *arg0) {
    arg0->red.multiplier = 0x100;
    arg0->green.multiplier = 0x100;
    arg0->blue.multiplier = 0x100;
    arg0->alpha.multiplier = 0x100;
    arg0->red.offset = 0;
    arg0->green.offset = 0;
    arg0->blue.offset = 0;
    arg0->alpha.offset = 0;
}

extern "C" void flcalcMulCxform(FLASHCXFORM *arg0, FLASHCXFORM *arg1, FLASHCXFORM *arg2) {
    arg0->red.multiplier = (s16) ((s32) (arg1->red.multiplier * arg2->red.multiplier) / 256);
    arg0->green.multiplier = (s16) ((s32) (arg1->green.multiplier * arg2->green.multiplier) / 256);
    arg0->blue.multiplier = (s16) ((s32) (arg1->blue.multiplier * arg2->blue.multiplier) / 256);
    arg0->alpha.multiplier = (s16) ((s32) (arg1->alpha.multiplier * arg2->alpha.multiplier) / 256);
    arg0->red.offset = (s16) (arg1->red.offset + arg2->red.offset);
    arg0->green.offset = (s16) (arg1->green.offset + arg2->green.offset);
    arg0->blue.offset = (s16) (arg1->blue.offset + arg2->blue.offset);
    arg0->alpha.offset = (s16) (arg1->alpha.offset + arg2->alpha.offset);
}

static inline void concatLinearValues(FLASHMATRIXF *out, FLASHMATRIXF *left, f32 a, f32 b, f32 c, f32 d) {
    out->m[0] = (f32) ((left->m[0] * a) + (left->m[1] * c));
    out->m[1] = (f32) ((left->m[0] * b) + (left->m[1] * d));
    out->m[2] = (f32) ((left->m[2] * a) + (left->m[3] * c));
    out->m[3] = (f32) ((left->m[2] * b) + (left->m[3] * d));
    out->m[4] = left->m[4];
    out->m[5] = left->m[5];
}

static inline void concatAffineValues(FLASHMATRIXF *out, FLASHMATRIXF *left, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f) {
    out->m[0] = (f32) ((left->m[0] * a) + (left->m[1] * c));
    out->m[1] = (f32) ((left->m[0] * b) + (left->m[1] * d));
    out->m[2] = (f32) ((left->m[2] * a) + (left->m[3] * c));
    out->m[3] = (f32) ((left->m[2] * b) + (left->m[3] * d));
    out->m[4] = (f32) (e + ((left->m[4] * a) + (left->m[5] * c)));
    out->m[5] = (f32) (f + ((left->m[4] * b) + (left->m[5] * d)));
}


extern "C" void flcalcMulMatrixf(FLASHMATRIXF *out, FLASHMATRIXF *left, FLASHMATRIXF *right) {
    out->m[0] = (f32) ((left->m[0] * right->m[0]) + (left->m[1] * right->m[2]));
    out->m[1] = (f32) ((left->m[0] * right->m[1]) + (left->m[1] * right->m[3]));
    out->m[2] = (f32) ((left->m[2] * right->m[0]) + (left->m[3] * right->m[2]));
    out->m[3] = (f32) ((left->m[2] * right->m[1]) + (left->m[3] * right->m[3]));
    out->m[4] = (f32) (right->m[4] + ((left->m[4] * right->m[0]) + (left->m[5] * right->m[2])));
    out->m[5] = (f32) (right->m[5] + ((left->m[4] * right->m[1]) + (left->m[5] * right->m[3])));
}

extern "C" void flcalcUnitMatrix2(FLASHMATRIX *out) {
    out->m[0] = 0x10000;
    out->m[1] = 0;
    out->m[2] = 0;
    out->m[3] = 0x10000;
    out->m[4] = 0;
    out->m[5] = 0;
}

extern "C" void flcalcUnitMatrix(FLASHMATRIXF *out) {
    out->m[0] = 1.0f;
    out->m[1] = 0.0f;
    out->m[2] = 0.0f;
    out->m[3] = 1.0f;
    out->m[4] = 0.0f;
    out->m[5] = 0.0f;
}

extern "C" void flcalcMatrixCopy(FLASHMATRIXF *out, FLASHMATRIXF *left) {
    out->m[0] = left->m[0];
    out->m[1] = left->m[1];
    out->m[2] = left->m[2];
    out->m[3] = left->m[3];
    out->m[4] = left->m[4];
    out->m[5] = left->m[5];
}

extern "C" void flcalcMatrixTranslate(FLASHMATRIXF *out, FLASHMATRIXF *in, GSvec2 *point) {
    f32 tx = point->x;
    f32 ty = point->y;
    concatAffineValues(out, in, 1.0f, 0.0f, 0.0f, 1.0f, tx, ty);
}

extern "C" void flcalcMatrixScale(FLASHMATRIXF *out, FLASHMATRIXF *in, GSvec2 *point) {
    concatLinearValues(out, in, point->x, 0.0f, 0.0f, point->y);
}

extern "C" void flcalcMatrix(GSvec2 *out, FLASHMATRIXF *matrix, GSvec2 *point) {
    GSvec2 p = *point;
    f32 m00 = matrix->m[0], m10 = matrix->m[1];
    f32 m01 = matrix->m[2], m11 = matrix->m[3];

    out->x = matrix->m[4] + (m00 * p.x + m01 * p.y);
    out->y = matrix->m[5] + (m10 * p.x + m11 * p.y);
}
