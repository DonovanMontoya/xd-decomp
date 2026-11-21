#ifndef PXDVS_APP_FLASHMENU_FLASH_COLOR_TRANSFORM_HPP
#define PXDVS_APP_FLASHMENU_FLASH_COLOR_TRANSFORM_HPP

#include <dolphin/types.h>

struct FlashColorChannel {
    s16 multiplier;
    s16 offset;
};

struct FLASHCXFORM {
    FlashColorChannel alpha;
    FlashColorChannel red;
    FlashColorChannel green;
    FlashColorChannel blue;
};

extern "C" {
s32 flcalcBlend(s32 from, s32 to, f32 t);
u32 flcalcBlendColor(u32 from, u32 to, f32 t);
void flcalcUnitCxform(FLASHCXFORM *out);
void flcalcCreateCxform(FLASHCXFORM *out, u32 color);
void flcalcMulCxform(FLASHCXFORM *out, FLASHCXFORM *a, FLASHCXFORM *b);
u32 flcalcMultiTransformColor(FLASHCXFORM *transform, u32 color);
}

#endif
