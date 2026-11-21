#ifndef GSSHAPE_OBJECT_PRIVATE_HPP
#define GSSHAPE_OBJECT_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>

enum GSgfxTunitOp {
    GS_TEV_ADD = GX_TEV_ADD,
    GS_TEV_SUB = GX_TEV_SUB,
};
enum GSgfxTunitBias {
    GS_TB_ZERO = GX_TB_ZERO,
};
enum GSgfxTunitScale {
    GS_CS_SCALE_1 = GX_CS_SCALE_1,
};
enum GSgfxTunitReg {
    GS_TEVPREV = GX_TEVPREV,
    GS_TEVREG0 = GX_TEVREG0,
    GS_TEVREG1 = GX_TEVREG1,
};
enum GSgfxTunitCArg {
    GS_CC_CPREV = GX_CC_CPREV,
    GS_CC_C0 = GX_CC_C0,
    GS_CC_C1 = GX_CC_C1,
    GS_CC_TEXC = GX_CC_TEXC,
    GS_CC_TEXA = GX_CC_TEXA,
    GS_CC_RASC = GX_CC_RASC,
    GS_CC_ONE = GX_CC_ONE,
    GS_CC_KONST = GX_CC_KONST,
    GS_CC_ZERO = GX_CC_ZERO,
};
enum GSgfxTunitAArg {
    GS_CA_APREV = GX_CA_APREV,
    GS_CA_A0 = GX_CA_A0,
    GS_CA_A1 = GX_CA_A1,
    GS_CA_TEXA = GX_CA_TEXA,
    GS_CA_RASA = GX_CA_RASA,
    GS_CA_KONST = GX_CA_KONST,
    GS_CA_ZERO = GX_CA_ZERO,
};

struct GSgfxTunitOpState { u32 operation, bias, scale; u8 clamp; u8 reserved0d[3]; u32 output; };
struct GSgfxTunitMapState { u32 texture, coordinate, color; };

struct GSgfxShaderState { u8 state[0xbc]; };

// Only the layer state touched by the shape renderer is modelled here.
struct GSgfxLayer {
    u8 reserved0000[0xd8c];
    u32 cullMode;
    u8 reservedD90[0xeb0 - 0xd90];
    GSgfxTunitMapState mapping[16];
    u32 colorArgs[16][4];
    u32 alphaArgs[16][4];
    GSgfxTunitOpState colorOps[16];
    GSgfxTunitOpState alphaOps[16];
    u8 reserved13f0[0x1504 - 0x13f0];
    u32 konstColors[16], konstAlphas[16];
    u8 reserved1584[0x1644 - 0x1584];
    u32 blendMode, blendSource, blendDestination, blendLogic;
    u8 reserved1654[2];
    u8 colorUpdate, alphaUpdate, destinationAlpha;
    u8 reserved1659[3];
    u8 depthEnable;
    u8 reserved165d[3];
    u32 depthFunction;
    u8 reserved1664[0x16a8 - 0x1664];
    u32 dirty, rasterDirty;
    u8 reserved16b0[8];
    u32 transformDirty;
    u8 reserved16bc[0x16d0 - 0x16bc];
    u32 mappingDirty, colorArgDirty, alphaArgDirty, colorOpDirty, alphaOpDirty;
    u8 reserved16e4[0x16fc - 0x16e4];
    u32 konstColorDirty, konstAlphaDirty;
    u8 reserved1704[0x170c - 0x1704];
    u32 pixelDirty;
    u8 reserved1710[0x173c - 0x1710];
    u32 textureDirty;
    GStexture* textures[8];
    u32 savedDirty, savedRasterDirty;
    u8 reserved1768[8];
    u32 savedTransformDirty;
    u8 reserved1774[0x1788 - 0x1774];
    u32 savedMappingDirty, savedColorArgDirty, savedAlphaArgDirty, savedColorOpDirty, savedAlphaOpDirty;
    u8 reserved179c[0x17b4 - 0x179c];
    u32 savedKonstColorDirty, savedKonstAlphaDirty;
    u8 reserved17bc[0x17c4 - 0x17bc];
    u32 savedPixelDirty;
    u8 reserved17c8[0x17f4 - 0x17c8];
    u32 savedTextureDirty;
    GStexture* savedTextures[8];
    GSgfxShaderState shaders[2];
    GSgfxShaderState* shader;
    s32 shaderIndex;
    u32 primitive;
    void* vertexFormat;

    inline void selectShader(s32 index) {
        if (shaderIndex != index) {
            shaderIndex = index;
            shader = &shaders[shaderIndex];
        }
    }
    inline void markPixel(u32 mask) {
        pixelDirty |= mask; dirty |= 0x40;
        savedPixelDirty |= mask; savedDirty |= 0x40;
    }
    inline void setBlend(u32 mode, u32 source, u32 destination, u32 logic) {
        blendMode = mode; blendSource = source; blendDestination = destination; blendLogic = logic;
        markPixel(1);
    }
    void tunitMapping(u8, u8, u8, u8);
    void texSelect(u8, GStexture*);
    void tunitColorOp(u8, GSgfxTunitOp, GSgfxTunitBias, GSgfxTunitScale, bool, GSgfxTunitReg);
    void tunitAlphaOp(u8, GSgfxTunitOp, GSgfxTunitBias, GSgfxTunitScale, bool, GSgfxTunitReg);
    void tunitColorArg(u8, GSgfxTunitCArg, GSgfxTunitCArg, GSgfxTunitCArg, GSgfxTunitCArg);
    void tunitAlphaArg(u8, GSgfxTunitAArg, GSgfxTunitAArg, GSgfxTunitAArg, GSgfxTunitAArg);
};
typedef char GSgfxLayerKonstColorOffsetCheck[offsetof(GSgfxLayer, konstColors) == 0x1504 ? 1 : -1];
typedef char GSgfxLayerKonstAlphaOffsetCheck[offsetof(GSgfxLayer, konstAlphas) == 0x1544 ? 1 : -1];
typedef char GSgfxLayerKonstDirtyOffsetCheck[offsetof(GSgfxLayer, konstColorDirty) == 0x16fc ? 1 : -1];
typedef char GSgfxLayerSavedKonstDirtyOffsetCheck[offsetof(GSgfxLayer, savedKonstColorDirty) == 0x17b4 ? 1 : -1];
typedef char GSgfxLayerTunitOpOffsetCheck[offsetof(GSgfxLayer, alphaOps) == 0x12b0 ? 1 : -1];
typedef char GSgfxLayerShaderOffsetCheck[offsetof(GSgfxLayer, shaders) == 0x1818 ? 1 : -1];
typedef char GSgfxLayerShaderIndexOffsetCheck[offsetof(GSgfxLayer, shaderIndex) == 0x1994 ? 1 : -1];
typedef char GSgfxLayerDirtyOffsetCheck[offsetof(GSgfxLayer, dirty) == 0x16a8 ? 1 : -1];
typedef char GSgfxLayerSavedTextureOffsetCheck[offsetof(GSgfxLayer, savedTextures) == 0x17f8 ? 1 : -1];
struct ShapeTextureBinding {u32 reserved00;u16 index;u8 minFilter,magFilter,wrapS,wrapT,blend;};
struct ShapeTextureEntry {u8 reserved00[0xe];u8 colorRange;};
struct GsShapeTexture {ShapeTextureEntry *entry;GStexture *texture;};
#endif
