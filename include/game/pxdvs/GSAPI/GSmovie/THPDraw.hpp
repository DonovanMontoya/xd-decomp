#ifndef THP_DRAW_HPP
#define THP_DRAW_HPP

#include <global.h>

struct GSgfxLayer;

extern "C" {
void THPGXSetRenderLayer(GSgfxLayer* layer);
void THPGXYuv2RgbSetup();
u16 THPGXYuv2RgbDraw(void* yPlane, void* uPlane, void* vPlane, s16 x, s16 y,
                     s16 textureWidth, s16 textureHeight, s16 drawWidth, s16 drawHeight);
void THPGXRestore();
}

#endif
