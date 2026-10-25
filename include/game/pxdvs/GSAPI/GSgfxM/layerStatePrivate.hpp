#ifndef GAME_PXDVS_GSAPI_GSGFXM_LAYER_STATE_PRIVATE_HPP
#define GAME_PXDVS_GSAPI_GSGFXM_LAYER_STATE_PRIVATE_HPP
union LayerBlendRegister {
    u32 value;
    struct { u32 address:8, reserved:11, operation:1, subtract:1, source:3, destination:3, alpha:1, color:1, dither:1, logic:1, blend:1; } fields;
};
struct LayerStateBlendRegisters { u8 reserved[0x38]; LayerBlendRegister blend; };
ABI_OFF(LayerStateBlendRegisters, blend, 0x38);
#define LAYER_BLEND_STATE reinterpret_cast<LayerStateBlendRegisters *>(gsgfxState)
struct LayerAmbDirtyRow { u8 reserved[0x4B8]; u8 dirty; };
struct LayerMatDirtyRow { u8 reserved[0x4C2]; u8 dirty; };
// Per-pass vertex format references cleared by ResetVertexFormat (two passes from layer+0x16A8).
struct LayerPassVertexFormats { u8 reserved[0x68]; u32 formats[8]; u32 format; u8 reserved8C[0xB8 - 0x8C]; };
ABI_SIZE(LayerPassVertexFormats,0xB8);
union LayerColor { u32 value; GXColor rgba; };
ABI_SIZE(LayerColor,4);

// GX indirect command fields, from most to least significant bit.
union LayerIndirectRegister {
    u32 value;
    struct {
        u32 address:8, reserved:3, addPrevious:1, useOriginalLod:1,
            wrapT:3, wrapS:3, matrix:4, alpha:2, bias:3, format:2, stage:2;
    } fields;
};
ABI_SIZE(LayerIndirectRegister,4);
struct LayerIndirectState { u8 reserved[0x310]; LayerIndirectRegister indirect[16]; };
ABI_OFF(LayerIndirectState,indirect,0x310);
#define LAYER_INDIRECT_STATE reinterpret_cast<LayerIndirectState *>(gsgfxState)
// TEV color/alpha environment registers (BP 0xC0-0xDF), most significant bit first.
union LayerTevColorRegister {
    u32 value;
    struct { u32 address:8, dest:2, shift:2, clamp:1, sub:1, bias:2, a:4, b:4, c:4, d:4; } fields;
};
union LayerTevAlphaRegister {
    u32 value;
    struct { u32 address:8, dest:2, shift:2, clamp:1, sub:1, bias:2, a:3, b:3, c:3, d:3, texSwap:2, rasSwap:2; } fields;
};
ABI_SIZE(LayerTevColorRegister,4); ABI_SIZE(LayerTevAlphaRegister,4);
struct LayerTevRegisters { u8 reserved[0x224]; LayerTevColorRegister color[16]; LayerTevAlphaRegister alpha[16]; };
ABI_OFF(LayerTevRegisters,alpha,0x264);
#define LAYER_TEV_STATE reinterpret_cast<LayerTevRegisters *>(gsgfxState)

// Last values passed to the cached TEV setters.
struct LayerTevInput { s32 a, b, c, d; };
struct LayerTevOperation { s32 operation, bias, scale; u8 clamp; s32 output; };
ABI_SIZE(LayerTevInput,0x10); ABI_SIZE(LayerTevOperation,0x14);
struct LayerTevCache {
    u8 reserved[0x590];
    LayerTevInput colorIn[16];
    LayerTevInput alphaIn[16];
    LayerTevOperation colorOp[16];
    LayerTevOperation alphaOp[16];
};
ABI_OFF(LayerTevCache,alphaOp,0x8D0);
inline LayerTevInput *layerTevColorInCache() { return reinterpret_cast<LayerTevCache *>(gsgfxState)->colorIn; }
inline LayerTevInput *layerTevAlphaInCache() { return reinterpret_cast<LayerTevCache *>(gsgfxState)->alphaIn; }
inline LayerTevOperation *layerTevColorOpCache() { return reinterpret_cast<LayerTevCache *>(gsgfxState)->colorOp; }
inline LayerTevOperation *layerTevAlphaOpCache() { return reinterpret_cast<LayerTevCache *>(gsgfxState)->alphaOp; }
// Indirect texture order (BP 0x27) and scale (BP 0x25/0x26) registers.
union LayerIndOrderRegister {
    u32 value;
    struct { u32 address:8, coordinate3:3, map3:3, coordinate2:3, map2:3, coordinate1:3, map1:3, coordinate0:3, map0:3; } fields;
};
union LayerIndScaleRegister {
    u32 value;
    struct { u32 address:8, reserved:8, t1:4, s1:4, t0:4, s0:4; } fields;
};
struct LayerIndRegisters { u8 reserved[0x78]; LayerIndOrderRegister order; LayerIndScaleRegister scale[2]; };
ABI_OFF(LayerIndRegisters,scale,0x7C);
#define LAYER_IND_STATE reinterpret_cast<LayerIndRegisters *>(gsgfxState)
struct LayerIndOrder { s32 coordinate, map; };
struct LayerIndScale { s32 s, t; };
struct LayerIndCache { u8 reserved[0xB74]; LayerIndOrder order[4]; LayerIndScale scale[4]; };
ABI_OFF(LayerIndCache,scale,0xB94);
inline LayerIndOrder *layerIndOrderCache() { return reinterpret_cast<LayerIndCache *>(gsgfxState)->order; }
inline LayerIndScale *layerIndScaleCache() { return reinterpret_cast<LayerIndCache *>(gsgfxState)->scale; }
// TEV konstant/swap select registers (BP 0xF6-0xFD).
union LayerTevKSelRegister {
    u32 value;
    struct { u32 address:8, kasel1:5, kcsel1:5, kasel0:5, kcsel0:5, swap1:2, swap0:2; } fields;
};
struct LayerTevKSelRegisters { u8 reserved[0x204]; LayerTevKSelRegister ksel[8]; };
#define LAYER_TEV_KSEL_STATE reinterpret_cast<LayerTevKSelRegisters *>(gsgfxState)
struct LayerSwapTable { s32 red, green, blue, alpha; };
struct LayerSwapTableCaches { u8 reserved[0xB24]; LayerSwapTable table[4]; };
inline LayerSwapTable *layerSwapTableCache() { return reinterpret_cast<LayerSwapTableCaches *>(gsgfxState)->table; }
// Packed bytes used by SetupGPUState's cached GX setters.
struct LayerGenModeCounts { u8 reserved:2, channels:2, textures:4; };
struct LayerGenModeStages { u8 cull:2, stages:4, reserved:2; };
struct LayerRasterEnable { u8 reserved:4, enabled:1, low:3; };
struct LayerZMode { u8 reserved:3, update:1, compare:3, enabled:1; };
struct LayerColorUpdate { u8 reserved:3, alpha:1, color:1, dither:1, low:2; };
ABI_SIZE(LayerGenModeCounts,1); ABI_SIZE(LayerGenModeStages,1);
ABI_SIZE(LayerRasterEnable,1); ABI_SIZE(LayerZMode,1); ABI_SIZE(LayerColorUpdate,1);
#endif
