#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>
#include <dolphin/gx/GXVert.h>

static inline s16 primClampConstant(s16 value) {
    return (value>-1024?value:-1024)<1023 ? (value>-1024?value:-1024) : 1023;
}
static inline void primSetConstant(GSgfxLayer* layer,GXColorS10 value) {
    layer->tevConstantIndex=1;
    layer->tevConstant.r=primClampConstant(value.r);
    layer->tevConstant.g=primClampConstant(value.g);
    layer->tevConstant.b=primClampConstant(value.b);
    layer->tevConstant.a=primClampConstant(value.a);
    layer->tevConstantDirty|=2;layer->dirty|=8;
    layer->savedTevConstantDirty|=2;layer->savedDirty|=8;
}

static inline void position(GSvec2 vertex) { GXWGFifo.f32 = vertex.x; GXWGFifo.f32 = vertex.y; }
static inline void color(GXColor value) { GXColor1u32(*(u32*)&value); }
static inline void lineState() {
    if (primData.lineState != 1) {
        GSprimLayer()->setLineWidth((s32)(6.0f * primData.lineWidth), 0);
        primData.lineState = 1;
    }
}
static inline void selectFormat(u32 id) {
    primData.layer->setRenderStateAndSelect(GSgfxVFGetPredef(id));
}
static inline void beginQuad() {
    GSprimLayer()->primitive = primData.quadPrimitive;
    GSprimLayer()->beginSurface(4);
}

extern "C" void GSprimDraw2DTexQuad4VCA(GSvec2* vertices, GSvec2* uv, GStexture* texture, const GXColor* tint, const GXColorS10* addition) {
    selectFormat(6);
    GSprimLayer()->setTexture(texture);
    primSetConstant(GSprimLayer(),*addition);
    GSprimLayer()->setTevColorOperation(0, 0, 0, 1, 0);
    GSprimLayer()->setTevColorInputs(15, 10, 8, 2);
    GSprimLayer()->setTevAlphaOperation(0, 0, 0, 1, 0);
    GSprimLayer()->setTevAlphaInputs(7, 5, 4, 1);
    beginQuad();
    position(vertices[0]); color(*tint); GXTexCoord2f32(uv[0].x, uv[0].y);
    position(vertices[1]); color(*tint); GXTexCoord2f32(uv[1].x, uv[1].y);
    position(vertices[2]); color(*tint); GXTexCoord2f32(uv[2].x, uv[2].y);
    position(vertices[3]); color(*tint); GXTexCoord2f32(uv[3].x, uv[3].y);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DTexQuad4V(GSvec2* vertices, GSvec2* uv, GStexture* texture, const GXColor* tint) {
    selectFormat(6);
    GSprimLayer()->setTexture(texture);
    beginQuad();
    position(vertices[0]); color(*tint); GXTexCoord2f32(uv[0].x, uv[0].y);
    position(vertices[1]); color(*tint); GXTexCoord2f32(uv[1].x, uv[1].y);
    position(vertices[2]); color(*tint); GXTexCoord2f32(uv[2].x, uv[2].y);
    position(vertices[3]); color(*tint); GXTexCoord2f32(uv[3].x, uv[3].y);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DTexQuad(f32 x0, f32 y0, f32 x1, f32 y1, GStexture* texture, const GXColor* tint) {
    selectFormat(6);
    GSprimLayer()->setTexture(texture);
    beginQuad();
    f32 zero = 0.0f, one = 1.0f;
    GXPosition2f32(x0, y0); color(*tint); GXTexCoord2f32(zero, zero);
    GXPosition2f32(x1, y0); color(*tint); GXTexCoord2f32(one, zero);
    GXPosition2f32(x0, y1); color(*tint); GXTexCoord2f32(zero, one);
    GXPosition2f32(x1, y1); color(*tint); GXTexCoord2f32(one, one);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DQuad4V(GSvec2* vertices, const GXColor* tint) {
    selectFormat(2);
    beginQuad();
    position(vertices[0]); color(*tint);
    position(vertices[1]); color(*tint);
    position(vertices[2]); color(*tint);
    position(vertices[3]); color(*tint);
    GSprimLayer()->endSurface();
}
static inline void quadWHVertices(f32 x, f32 y, f32 width, f32 height, GXColor a, GXColor b, GXColor c, GXColor d) {
    GXPosition2f32(x, y); GXColor1u32(*(u32*)&a);
    GXPosition2f32(x + width, y); GXColor1u32(*(u32*)&b);
    GXPosition2f32(x, y + height); GXColor1u32(*(u32*)&c);
    GXPosition2f32(x + width, y + height); GXColor1u32(*(u32*)&d);
}
extern "C" void GSprimDraw2DQuadWH(f32 x, f32 y, f32 width, f32 height, const GXColor* tint) {
    GXColor copy = *tint;
    selectFormat(2);
    beginQuad();
    quadWHVertices(x, y, width, height, copy, copy, copy, copy);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DQuad(f32 x0, f32 y0, f32 x1, f32 y1, const GXColor* tint) {
    selectFormat(2);
    beginQuad();
    GXPosition2f32(x0, y0); color(*tint);
    GXPosition2f32(x1, y0); color(*tint);
    GXPosition2f32(x0, y1); color(*tint);
    GXPosition2f32(x1, y1); color(*tint);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DPixelListC(const GSprimPixel* vertices, u32 count, const GXColor* colors) {
    if (count == 0) return;
    GSprimLayer()->setPointSize(6, 0);
    selectFormat(3);
    GSprimLayer()->primitive = 0xb8;
    GSprimLayer()->beginSurface(count);
    while (count--) {
        s16 y = ((const volatile GSprimPixel*)vertices)->y;
        s16 x = ((const volatile GSprimPixel*)vertices)->x;
        GXPosition2s16(x, y);
        GXColor1u32(*(const volatile u32*)colors++);
        ++vertices;
    }
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DLineListC(GSvec2* vertices, u32 count, GXColor* colors) {
    if (count < 1) return;
    lineState();
    selectFormat(2);
    GSprimLayer()->primitive = 0xa8;
    GSprimLayer()->beginSurface(count * 2);
    while (count--) {
        position(*vertices++); color(*colors++);
        position(*vertices++); color(*colors++);
    }
    GSprimLayer()->endSurface();
}

static inline void lineVertices(GXColor a, GXColor b, f32 x0, f32 y0, f32 x1, f32 y1) {
    GXPosition2f32(x0, y0); color(a);
    GXPosition2f32(x1, y1); color(b);
}
extern "C" void GSprimDraw2DVLine(f32 x, f32 y0, f32 y1, const GXColor* tint) {
    GXColor second = *tint, first = *tint;
    lineState();
    selectFormat(2);
    GSprimLayer()->primitive = 0xa8;
    GSprimLayer()->beginSurface(2);
    lineVertices(first, second, x, y0, x, y1);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DHLine(f32 x0, f32 x1, f32 y, const GXColor* tint) {
    GXColor second = *tint, first = *tint;
    lineState();
    selectFormat(2);
    GSprimLayer()->primitive = 0xa8;
    GSprimLayer()->beginSurface(2);
    lineVertices(first, second, x0, y, x1, y);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DLine(f32 x0, f32 y0, f32 x1, f32 y1, const GXColor* first, const GXColor* second) {
    lineState();
    selectFormat(2);
    GSprimLayer()->primitive = 0xa8;
    GSprimLayer()->beginSurface(2);
    GXPosition2f32(x0, y0); color(*first);
    GXPosition2f32(x1, y1); color(*second);
    GSprimLayer()->endSurface();
}
