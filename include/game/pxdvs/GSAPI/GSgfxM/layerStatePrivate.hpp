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
#endif
