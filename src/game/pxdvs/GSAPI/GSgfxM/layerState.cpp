#include "layer_private.h"
#include <dolphin/os/OSFastCast.h>
#include <game/pxdvs/GSAPI/GSgfxM/layerStatePrivate.hpp>
static const LayerColor defaultColor={0x80808080};
extern "C" {
u8 GSgfxRenderModuleIsRendering__Fv();
u8 GSgfxVFGetColorCount(void*); u8 GSgfxVFGetTextureCount(void*); u8 GSgfxVFHasElement(void*,s32);
void SetupRenderState__10GSgfxLayerFv(void*); void SetupGPUState__10GSgfxLayerFv(void*);
void GSgfxLayerUpdateActiveFifoStats__Fv();
void setRenderState__10GSgfxLayerFP7GSgfxVF(void*,void*);
void setRenderState__10GSgfxLayerFbUcb(void*,u8,u8,u8);
void renderState_NL_NVC_NT__10GSgfxLayerFv(void*);
void renderState_NL_NVC_T__10GSgfxLayerFUc(void*,u8);
void renderState_NL_VC_T__10GSgfxLayerFUc(void*,u8);
void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(void*,u8,s32,s32,void*,bool,void*);
void tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(void*,u8,u32);
void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(void*,u8,s32,s32,s32,u32,void**,s32,s32);
void FlushState__10GSgfxLayerFv(void *arg0) {
    SetupFifo__10GSgfxLayerFv(arg0);
    SetupRenderState__10GSgfxLayerFv(arg0);
    GSgfxLayerUpdateActiveFifoStats__Fv();
}

void InvalidateState__10GSgfxLayerFv(void *arg0) {
    if (GSgfxRenderModuleIsRendering__Fv() == 1) {
        GXFlush();
    }
    memset(static_cast<u8*>(arg0) + 0x16A8, 0, 0xB8);
    memset(static_cast<u8*>(arg0) + 0x1760, 0, 0xB8);
    layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 0x80000000);
}

void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(void *arg0, void* arg1) {
    setRenderState__10GSgfxLayerFP7GSgfxVF(arg0, arg1);
    layerField<void*>(arg0, 0x199C) = arg1;
}

void setRenderState__10GSgfxLayerFP7GSgfxVF(void *arg0, void *arg1) {
    u8 temp_r30;
    u8 temp_r31;
    u8 var_r29;

    temp_r31 = GSgfxVFGetColorCount(arg1);
    temp_r30 = GSgfxVFGetTextureCount(arg1);
    var_r29 = 0;
    if ((GSgfxVFHasElement(arg1, 0xA) != 0) || (GSgfxVFHasElement(arg1, 0x19) != 0)) {
        var_r29 = 1;
    }
    if (temp_r31 == 0) {
        setRenderState__10GSgfxLayerFbUcb(arg0, 0U, temp_r30, var_r29);
        return;
    }
    setRenderState__10GSgfxLayerFbUcb(arg0, 1U, temp_r30, var_r29);
}

void setRenderState__10GSgfxLayerFbUcb(void *arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 sp8;

    if (arg3 == 0) {
        if (arg1 == 0) {
            if (arg2 == 0) {
                renderState_NL_NVC_NT__10GSgfxLayerFv(arg0);
                return;
            }
            renderState_NL_NVC_T__10GSgfxLayerFUc(arg0,arg2);
            return;
        }
        if (arg2 == 0) {
            layerField<u8>(arg0, 0xDB8) = 1;
            layerField<u32>(arg0, 0x16BC) = (s32) (layerField<u32>(arg0, 0x16BC) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
            layerField<u32>(arg0, 0x1774) = (s32) (layerField<u32>(arg0, 0x1774) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
            layerField<u8>(arg0, 0xC70) = 0;
            layerField<u32>(arg0, 0x16AC) = (s32) (layerField<u32>(arg0, 0x16AC) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 1);
            layerField<u32>(arg0, 0x1764) = (s32) (layerField<u32>(arg0, 0x1764) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 1);
            layerField<u8>(arg0, 0xEAC) = 1;
            layerField<u32>(arg0, 0x16CC) = (s32) (layerField<u32>(arg0, 0x16CC) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
            layerField<u32>(arg0, 0x1784) = (s32) (layerField<u32>(arg0, 0x1784) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
            layerField<u8>(arg0, 0x14B0) = 0;
            layerField<u32>(arg0, 0x16EC) = (s32) (layerField<u32>(arg0, 0x16EC) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x80);
            layerField<u32>(arg0, 0x17A4) = (s32) (layerField<u32>(arg0, 0x17A4) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x80);
            sp8 = 0;
            cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(arg0,0,2,0,1,0,0,2,0);
            layerField<u32>(arg0, 0xEB0) = 0xFF;
            layerField<u32>(arg0, 0xEB4) = 0xFF;
            layerField<u32>(arg0, 0xEB8) = 4;
            layerField<u32>(arg0, 0x16D0) = (s32) (layerField<u32>(arg0, 0x16D0) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
            layerField<u32>(arg0, 0x1788) = (s32) (layerField<u32>(arg0, 0x1788) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, 0U, 4);
            layerField<u32>(arg0, 0x1584) = 0;
            layerField<u32>(arg0, 0x1588) = 0;
            layerField<u32>(arg0, 0x1704) = (s32) (layerField<u32>(arg0, 0x1704) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x20);
            layerField<u32>(arg0, 0x17BC) = (s32) (layerField<u32>(arg0, 0x17BC) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x20);
            return;
        }
        renderState_NL_VC_T__10GSgfxLayerFUc(arg0,arg2);
    }
}

void ResetVertexFormat__10GSgfxLayerFP7GSgfxVF(void *arg0, u32 arg1) {
    LayerPassVertexFormats *pass = reinterpret_cast<LayerPassVertexFormats *>(static_cast<u8 *>(arg0) + 0x16A8);
    if (arg1 == layerField<u32>(arg0, 0x199C)) {
        layerField<u32>(arg0, 0x199C) = 0;
    }
    for (s32 i = 0; i < 2; i++, pass++) {
        if (pass->format == arg1) {
            pass->format = 0;
        }
        for (s32 j = 0; j < 8; j++) {
            if (pass->formats[j] == arg1) {
                pass->formats[j] = 0;
            }
        }
    }
}

void renderState_NL_VC_T__10GSgfxLayerFUc(void *arg0, u8 arg1) {
    s32 sp8;
    s32 temp_r31;
    u8 var_r29;
    u8 var_r30;
    u8 *temp_r4;
    u8 *temp_r5;

    layerField<u8>(arg0, 0xDB8) = 1;
    layerField<u32>(arg0, 0x16BC) = (s32) (layerField<u32>(arg0, 0x16BC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
    layerField<u32>(arg0, 0x1774) = (s32) (layerField<u32>(arg0, 0x1774) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
    layerField<u8>(arg0, 0xC70) = arg1;
    layerField<u32>(arg0, 0x16AC) = (s32) (layerField<u32>(arg0, 0x16AC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 1);
    layerField<u32>(arg0, 0x1764) = (s32) (layerField<u32>(arg0, 0x1764) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 1);
    layerField<u8>(arg0, 0xEAC) = arg1;
    layerField<u32>(arg0, 0x16CC) = (s32) (layerField<u32>(arg0, 0x16CC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
    layerField<u32>(arg0, 0x1784) = (s32) (layerField<u32>(arg0, 0x1784) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
    layerField<u8>(arg0, 0x14B0) = 0;
    layerField<u32>(arg0, 0x16EC) = (s32) (layerField<u32>(arg0, 0x16EC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x80);
    layerField<u32>(arg0, 0x17A4) = (s32) (layerField<u32>(arg0, 0x17A4) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x80);
    sp8 = 0;
    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(arg0,0,2,0,1,0,0,2,0);
    var_r30 = 0;
    while (var_r30 < arg1) {
        tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(arg0, var_r30, 1, var_r30 + 4, 0, 0, 0);
        var_r30 += 1;
    }
    var_r29 = 0;
    while (var_r29 < arg1) {
        temp_r31 = 1 << var_r29;
        layerField<s32>(arg0,var_r29*0x24+0x1420) = 0;
        temp_r5 = static_cast<u8*>(arg0) + (var_r29 * 0xC);
        layerField<u32>(arg0, 0x16E8) = (s32) (layerField<u32>(arg0, 0x16E8) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
        layerField<u32>(arg0, 0x17A0) = (s32) (layerField<u32>(arg0, 0x17A0) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
        layerField<u32>(temp_r5, 0xEB0) = (s32) var_r29;
        layerField<u32>(temp_r5, 0xEB4) = (s32) var_r29;
        layerField<u32>(temp_r5, 0xEB8) = 4;
        layerField<u32>(arg0, 0x16D0) = (s32) (layerField<u32>(arg0, 0x16D0) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
        layerField<u32>(arg0, 0x1788) = (s32) (layerField<u32>(arg0, 0x1788) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
        if (var_r29 == 0) {
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, var_r29, 0);
        } else {
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, var_r29, 7);
        }
        temp_r4 = static_cast<u8*>(arg0) + (var_r29 * 8);
        var_r29 += 1;
        layerField<u32>(temp_r4, 0x1584) = 0;
        layerField<u32>(temp_r4, 0x1588) = 0;
        layerField<u32>(arg0, 0x1704) = (s32) (layerField<u32>(arg0, 0x1704) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x20);
        layerField<u32>(arg0, 0x17BC) = (s32) (layerField<u32>(arg0, 0x17BC) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x20);
    }
}

void renderState_NL_NVC_T__10GSgfxLayerFUc(void *arg0, u8 arg1) {
    s32 temp_r31;
    u8 var_r29;
    u8 var_r29_2;
    u8 *temp_r4;
    u8 *temp_r5;

    var_r29 = 0;
    layerField<u8>(arg0, 0xDB8) = 0;
    layerField<u32>(arg0, 0x16BC) = (s32) (layerField<u32>(arg0, 0x16BC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
    layerField<u32>(arg0, 0x1774) = (s32) (layerField<u32>(arg0, 0x1774) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
    layerField<u8>(arg0, 0xC70) = arg1;
    layerField<u32>(arg0, 0x16AC) = (s32) (layerField<u32>(arg0, 0x16AC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 1);
    layerField<u32>(arg0, 0x1764) = (s32) (layerField<u32>(arg0, 0x1764) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 1);
    layerField<u8>(arg0, 0xEAC) = arg1;
    layerField<u32>(arg0, 0x16CC) = (s32) (layerField<u32>(arg0, 0x16CC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
    layerField<u32>(arg0, 0x1784) = (s32) (layerField<u32>(arg0, 0x1784) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
    layerField<u8>(arg0, 0x14B0) = 0;
    layerField<u32>(arg0, 0x16EC) = (s32) (layerField<u32>(arg0, 0x16EC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x80);
    layerField<u32>(arg0, 0x17A4) = (s32) (layerField<u32>(arg0, 0x17A4) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x80);
    while (var_r29 < arg1) {
        tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(arg0, var_r29, 1, var_r29 + 4, 0, 0, 0);
        var_r29 += 1;
    }
    var_r29_2 = 0;
    while (var_r29_2 < arg1) {
        temp_r31 = 1 << var_r29_2;
        layerField<s32>(arg0,var_r29_2*0x24+0x1420) = 0;
        temp_r5 = static_cast<u8*>(arg0) + (var_r29_2 * 0xC);
        layerField<u32>(arg0, 0x16E8) = (s32) (layerField<u32>(arg0, 0x16E8) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
        layerField<u32>(arg0, 0x17A0) = (s32) (layerField<u32>(arg0, 0x17A0) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
        layerField<u32>(temp_r5, 0xEB0) = (s32) var_r29_2;
        layerField<u32>(temp_r5, 0xEB4) = (s32) var_r29_2;
        layerField<u32>(temp_r5, 0xEB8) = 0xFF;
        layerField<u32>(arg0, 0x16D0) = (s32) (layerField<u32>(arg0, 0x16D0) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
        layerField<u32>(arg0, 0x1788) = (s32) (layerField<u32>(arg0, 0x1788) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
        if (var_r29_2 == 0) {
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, var_r29_2, 3);
        } else {
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, var_r29_2, 5);
        }
        temp_r4 = static_cast<u8*>(arg0) + (var_r29_2 * 8);
        var_r29_2 += 1;
        layerField<u32>(temp_r4, 0x1584) = 0;
        layerField<u32>(temp_r4, 0x1588) = 0;
        layerField<u32>(arg0, 0x1704) = (s32) (layerField<u32>(arg0, 0x1704) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x20);
        layerField<u32>(arg0, 0x17BC) = (s32) (layerField<u32>(arg0, 0x17BC) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x20);
    }
}

void renderState_NL_NVC_NT__10GSgfxLayerFv(void *arg0) {
    LayerColor sp18;
    LayerColor sp14;
    LayerColor sp10;
    s32 sp8;

    layerField<u8>(arg0, 0xDB8) = 1;
    sp18 = defaultColor;
    layerField<u32>(arg0, 0x16BC) = (s32) (layerField<u32>(arg0, 0x16BC) | 1);
    sp10 = defaultColor;
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
    sp14 = defaultColor;
    layerField<u32>(arg0, 0x1774) = (s32) (layerField<u32>(arg0, 0x1774) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
    layerField<u8>(arg0, 0xC70) = 0;
    layerField<u32>(arg0, 0x16AC) = (s32) (layerField<u32>(arg0, 0x16AC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 1);
    layerField<u32>(arg0, 0x1764) = (s32) (layerField<u32>(arg0, 0x1764) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 1);
    layerField<u8>(arg0, 0xEAC) = 1;
    layerField<u32>(arg0, 0x16CC) = (s32) (layerField<u32>(arg0, 0x16CC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
    layerField<u32>(arg0, 0x1784) = (s32) (layerField<u32>(arg0, 0x1784) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
    layerField<u8>(arg0, 0x14B0) = 0;
    layerField<u32>(arg0, 0x16EC) = (s32) (layerField<u32>(arg0, 0x16EC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x80);
    layerField<u32>(arg0, 0x17A4) = (s32) (layerField<u32>(arg0, 0x17A4) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x80);
    layerField<LayerColor>(arg0, 0xE9C) = sp10;
    layerField<LayerColor>(arg0, 0xEA4) = sp14;
    layerField<u32>(arg0, 0x16C4) = (s32) (layerField<u32>(arg0, 0x16C4) | 1);
    layerField<u32>(arg0, 0x16C8) = (s32) (layerField<u32>(arg0, 0x16C8) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
    layerField<u32>(arg0, 0x177C) = (s32) (layerField<u32>(arg0, 0x177C) | 1);
    layerField<u32>(arg0, 0x1780) = (s32) (layerField<u32>(arg0, 0x1780) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
    sp8 = 0;
    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(arg0,0,2,0,0,0,0,2,0);
    layerField<u32>(arg0, 0xEB0) = 0xFF;
    layerField<u32>(arg0, 0xEB4) = 0xFF;
    layerField<u32>(arg0, 0xEB8) = 4;
    layerField<u32>(arg0, 0x16D0) = (s32) (layerField<u32>(arg0, 0x16D0) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
    layerField<u32>(arg0, 0x1788) = (s32) (layerField<u32>(arg0, 0x1788) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
    tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, 0U, 4);
    layerField<u32>(arg0, 0x1584) = 0;
    layerField<u32>(arg0, 0x1588) = 0;
    layerField<u32>(arg0, 0x1704) = (s32) (layerField<u32>(arg0, 0x1704) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x20);
    layerField<u32>(arg0, 0x17BC) = (s32) (layerField<u32>(arg0, 0x17BC) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x20);
}

}

extern "C" {
void* _layerStateLastHWState;
s32 _foo;
void GSgfx_GCInvalidateState();
void PPCSync();
void Load__10GSgfxLightFUc(void*,u8);
void GSgfx_GCWriteLoadTlut(void*,s32); void GSgfx_GCWriteLoadTexObj(void*,s32);
void GSgfx_GCWriteVtxDesc(void*); void GSgfx_GCWriteVtxAttrFmt(s32,void*);
void GSgfx_GCWriteArray(s32,void*,u8);
struct LayerHWView { u8 pad[0x30]; u8 hw[0xc40]; };
void LoadHWState__10GSgfxLayerFv(void* layer) {
    LayerHWView* view=static_cast<LayerHWView*>(layer);
    if (_layerStateLastHWState!=view->hw) {
        if (_layerStateLastHWState) memcpy(_layerStateLastHWState,gsgfxState,0xc40);
        memcpy(gsgfxState,view->hw,0xc40); _layerStateLastHWState=view->hw;
    }
}
}
struct LayerArray { u16 flags; u8 stride,padding; s32 attribute; void* data; u32 size; };
ABI_SIZE(LayerArray,0x10);
struct LayerMatrixIndex { u8 reserved:2, index:6; };
ABI_SIZE(LayerMatrixIndex,1);
static void loadLayerMatrix(void* layer,u8* dirty) {
    GSgfxMatrixStack* stack=layerField<GSgfxMatrixStack*>(layer,0x19a0);
    GSgfxMatrixStack::Entry* entry=stack->current;
    if ((entry->flags&1) || entry!=layerField<GSgfxMatrixStack::Entry*>(dirty,0x8c)) {
        GXLoadPosMtxImm(entry->matrix,0x1b);
        stack=layerField<GSgfxMatrixStack*>(layer,0x19a0);
        if (stack->current->flags&1) {
            PSMTXInvXpose(stack->current->matrix,stack->current->inverse);
            stack->current->flags&=~1;
        }
        GXLoadNrmMtxImm(stack->current->inverse,0x1b);
        layerField<GSgfxMatrixStack::Entry*>(dirty,0x8c)=layerField<GSgfxMatrixStack*>(layer,0x19a0)->current;
    }
    if (layerField<u8>(dirty,0x90)==0) {
        layerField<LayerMatrixIndex>(gsgfxState,0x1f3).index=0x1b;
        gsgfxState->dirty|=0x40; layerField<u8>(dirty,0x90)=1;
    }
}
struct LayerRenderLights { u8 reserved[0x128]; void* lights[8]; };
struct LayerRenderTextures { u8 reserved[0x98]; u8* textures[8]; };
ABI_OFF(LayerRenderLights,lights,0x128);
ABI_OFF(LayerRenderTextures,textures,0x98);
union LayerBPCommand { u32 value; struct { u32 address:8, payload:24; } fields; };
ABI_SIZE(LayerBPCommand,4);
extern "C" void SetupRenderState__10GSgfxLayerFv(void* layer) {
    LoadHWState__10GSgfxLayerFv(layer);
    u32& flags=layerField<u32>(layer,4);
    if (flags&0x80000000) { GSgfx_GCInvalidateState(); flags&=~0x80000000; }
    if (flags&0x20000000) { gsgfxState->dirty|=0x10; flags&=~0x20000000; }
    if (flags&0x08000000) { *(volatile u8*)0xcc008000=0x48; flags&=~0x08000000; }
    if (flags&0x10000000) {
        LayerBPCommand invalidate;
        LayerBPCommand indirect;
        indirect.value=0;
        invalidate.value=0;
        indirect.fields.address=0x0f;
        *(volatile u8*)0xcc008000=0x61; *(volatile u32*)0xcc008000=indirect.value;
        invalidate.fields.address=0x66;
        invalidate.fields.payload=0x1000;
        *(volatile u8*)0xcc008000=0x61; *(volatile u32*)0xcc008000=invalidate.value;
        invalidate.fields.payload=0x1100;
        *(volatile u8*)0xcc008000=0x61; *(volatile u32*)0xcc008000=invalidate.value;
        gsgfxState->dirty|=0x800; flags&=~0x10000000;
    }
    if (flags&0x40000000) {
        LayerBPCommand invalidate;
        invalidate.fields.address=0x63;
        invalidate.fields.payload=0;
        *(volatile u8*)0xcc008000=0x61; *(volatile u32*)0xcc008000=invalidate.value;
        flags&=~0x40000000;
    }
    u8* state=static_cast<u8*>(layer)+0xc70;
    u8* dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
    if ((layerField<u32>(dirty,0)&4) && (layerField<u32>(dirty,0x14)&0x10)) {
        u8 count=layerField<u8>(state,0x124);
        for (u8 i=0;i<count;i++) Load__10GSgfxLightFUc(reinterpret_cast<LayerRenderLights*>(state)->lights[i],i);
        layerField<u32>(dirty,0x14)&=~0x10;
    }
    SetupGPUState__10GSgfxLayerFv(layer);
    dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
    if (layerField<u32>(dirty,0x94) && layerField<u8>(layer,0xc70)) {
        for (s32 i=0;i<8;i++) if (layerField<u32>(dirty,0x94)&(1<<i)) {
            u8* tex=reinterpret_cast<LayerRenderTextures*>(dirty)->textures[i];
            if (!layerField<u16>(tex,0) || !layerField<u16>(tex,2)) ++_foo;
            if (layerField<void*>(tex,0x48)) {
                GXInitTexObjTlut(reinterpret_cast<GXTexObj*>(tex+0x54),i);
                GSgfx_GCWriteLoadTlut(tex+0x74,i);
            }
            GSgfx_GCWriteLoadTexObj(tex+0x54,i); layerField<u8>(tex,7)=0;
        }
        layerField<u32>(dirty,0x94)=0;
    }
    u8* format=layerField<u8*>(layer,0x199c);
    if (format) {
        dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
        if (layerField<void*>(dirty,0x88)!=format || (layerField<u16>(format,0)&4)) {
            GSgfx_GCWriteVtxDesc(format+0x1b8);
            for (LayerArray* a=reinterpret_cast<LayerArray*>(format+0x290);a->attribute!=255;a++)
                GSgfx_GCWriteArray(a->attribute,a->data,a->stride);
            layerField<void*>(dirty,0x88)=format;
        }
        if (layerField<void*>(dirty,0x68+layerField<u32>(format,4)*4)!=format || (layerField<u16>(format,0)&2)) {
            GSgfx_GCWriteVtxAttrFmt(layerField<u32>(format,4),format+8); layerField<void*>(dirty,0x68+layerField<u32>(format,4)*4)=format;
        }
        u8 sync=0;
        for (LayerArray* a=reinterpret_cast<LayerArray*>(format+0x290);a->attribute!=255;a++) if (a->flags&1) {
            DCStoreRangeNoSync(a->data,a->size); sync=1; a->flags&=~1;
        }
        if (sync==1) PPCSync();
        if (layerField<u16>(format,0)&8) *(volatile u8*)0xcc008000=0x48;
        layerField<u16>(format,0)&=~6;
        if (GSgfxVFHasElement(layerField<void*>(layer,0x199c),0)==0) {
            dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
            loadLayerMatrix(layer,dirty);
        }
    } else {
        dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
        loadLayerMatrix(layer,dirty);
    }
    GSgfx_GCFlushState();
}

#define LAYER_STATE_FIELD(type, base, offset) (*reinterpret_cast<type*>(reinterpret_cast<u8*>(base) + (offset)))
struct LayerBlendCache { u8 reserved[0xBB4]; s32 mode; s32 source; s32 destination; s32 operation; };
struct LayerSwapTableCache { u8 reserved[0xB24]; s32 red; s32 green; s32 blue; s32 alpha; };
struct LayerIndScaleCache { u8 reserved[0xB94]; s32 s; s32 t; };
struct LayerIndOrderCache { u8 reserved[0xB74]; s32 coordinate; s32 map; };
struct LayerTevAlphaInputCache { u8 reserved[0x690]; s32 a; s32 b; s32 c; s32 d; };
struct LayerTevColorInputCache { u8 reserved[0x590]; s32 a; s32 b; s32 c; s32 d; };
struct LayerTevAlphaOperationCache { u8 reserved[0x8D0]; s32 operation; s32 bias; s32 scale; u8 clamp; u8 padding[3]; s32 output; };
struct LayerTevColorOperationCache { u8 reserved[0x790]; s32 operation; s32 bias; s32 scale; u8 clamp; u8 padding[3]; s32 output; };
struct LayerTevOrderCache { u8 reserved[0x4CC]; s32 coordinate; s32 map; s32 color; };
struct LayerScissorCache { u8 reserved[0x444]; u16 x; u16 y; u16 width; u16 height; s32 offsetX; s32 offsetY; };
struct LayerAlphaCompareCache { u8 reserved[0xbc8]; s32 compare0,operation,compare1; u8 reference0,reference1; };
ABI_OFF(LayerAlphaCompareCache,reference0,0xbd4);
// Cached hardware setters recovered from layerState's weak assembly bodies.
extern "C" {
static const u8 layerTevColorChannel[16]={0,1,0,1,0,1,7,5,6,0,0,0,0,0,0,7};
static const u8 layerCullMode[4]={0,2,1,3};
void GSgfx_GCWriteTexCoordGen(s32,s32,s32,u32,u8,u32);
void GSgfx_GCWriteFog(s32,float,float,float,float);
void GSgfx_GCWriteTevIndBumpST(s32,u8,s32);
void GSgfx_GCWriteTevIndTile(s32,u8,u16,u16,u16,u16,s32,s32,u8,u8);
void* GSgfxVideoGetViewport();
void GSgfxVideoSetViewport__Fffffb(float,float,float,float,bool);
__declspec(weak) void GSgfx_GCSetFogRangeAdj(u8 arg0, u16 arg1, u8 *arg2);
__declspec(weak) void GSgfx_GCSetAlphaCompare(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4);
__declspec(weak) void GSgfx_GCSetBlendMode(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
__declspec(weak) void GSgfx_GCSetTevSwapModeTable(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
__declspec(weak) void GSgfx_GCSetTevKColor(s32 arg0, GXColor arg1);
__declspec(weak) void GSgfx_GCSetIndTexCoordScale(s32 arg0, s32 arg1, s32 arg2);
__declspec(weak) void GSgfx_GCSetIndTexOrder(s32 arg0, s32 arg1, s32 arg2);
__declspec(weak) void GSgfx_GCSetTevIndRepeat(s32 arg0);
__declspec(weak) void GSgfx_GCSetTevIndBumpXYZ(s32 arg0, s32 arg1, s32 arg2);
__declspec(weak) void GSgfx_GCSetTevIndWarp(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4);
__declspec(weak) void GSgfx_GCSetTevIndirect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, u8 arg_sp8, s32 arg_spC);
__declspec(weak) void GSgfx_GCSetTevDirect(s32 arg0);
__declspec(weak) void GSgfx_GCSetTevAlphaOp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
__declspec(weak) void GSgfx_GCSetTevColorOp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
__declspec(weak) void GSgfx_GCSetTevAlphaIn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
__declspec(weak) void GSgfx_GCSetTevColorIn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
__declspec(weak) void GSgfx_GCSetTevOrder(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
__declspec(weak) void GSgfx_GCSetMatColor(s32 arg0, GXColor arg1);
__declspec(weak) void GSgfx_GCSetAmbColor(s32 arg0, GXColor arg1);
__declspec(weak) void GSgfx_GCSetChanCtrl(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
__declspec(weak) void GSgfx_GCSetScissor(u16 arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5);
__declspec(weak) void GSgfx_GCSetProjection(s32 arg0, u8 *arg1);

struct LayerTevRegularColorRegister { u32 address:8, bank:1, high:11, reserved:1, low:11; };
struct LayerTevRegularColorRegisters { u8 reserved[0x2A4]; LayerTevRegularColorRegister ra[4], bg[4]; };
ABI_SIZE(LayerTevRegularColorRegister, 4);
ABI_OFF(LayerTevRegularColorRegisters, ra, 0x2A4);
ABI_OFF(LayerTevRegularColorRegisters, bg, 0x2B4);
struct LayerGpuPassArray { u8 reserved[0x16A8]; LayerPassVertexFormats pass[2]; };
ABI_OFF(LayerGpuPassArray, pass, 0x16A8);
void SetupGPUState__10GSgfxLayerFv(void *arg0) {
    s32 sp38;
    s32 sp34;
    u32 sp30;
    u32 sp2C;
    u32 sp28;
    u32 sp24;
    u32 sp20;
    s32 sp1C;
    u32 sp18;
    u32 sp14;
    s32 spC;
    s32 sp8;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r10_3;
    s32 temp_r10_4;
    s32 temp_r11;
    s32 temp_r12_3;
    s32 temp_r24_2;
    s32 temp_r25;
    s32 temp_r3_3;
    s32 temp_r4_3;
    s32 temp_r4_4;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r6_3;
    s32 temp_r6_4;
    s32 temp_r6_5;
    s32 temp_r6_6;
    s32 temp_r8;
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 var_ctr;
    s32 var_r24_2;
    s32 var_r25;
    s32 var_r26;
    s32 var_r26_10;
    s32 var_r26_11;
    s32 var_r26_2;
    s32 var_r26_3;
    s32 var_r26_4;
    s32 var_r26_5;
    s32 var_r26_6;
    s32 var_r26_7;
    s32 var_r26_8;
    s32 var_r26_9;
    s32 var_r27;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29_3;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    s32 var_r4_5;
    s32 var_r5;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 var_r5_6;
    s32 var_r6;
    s32 var_r6_3;
    s32 var_r7;
    u32 temp_r0;
    u32 temp_r0_4;
    u32 temp_r3_4;
    u32 temp_r3_5;
    u8 temp_r0_5;
    u8 temp_r12;
    u8 temp_r24;
    u8 temp_r4;
    u8 temp_r4_10;
    u8 temp_r4_11;
    u8 temp_r4_12;
    u8 temp_r4_13;
    u8 temp_r4_2;
    u8 temp_r4_5;
    u8 temp_r4_7;
    u8 temp_r4_8;
    u8 temp_r4_9;
    u8 temp_r5;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 temp_r5_4;
    u8 temp_r5_5;
    u8 var_r28_3;
    u8 var_r5_2;
    u8 **var_r6_2;
    u8 *temp_r30;
    u8 *temp_r31;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u8 *temp_r3_6;
    u8 *temp_r4_6;
    u8 *temp_r7;
    u8 *temp_r7_4;
    u8 *var_r24;
    u8 *var_r25_10;
    u8 *var_r25_11;
    u8 *var_r25_12;
    u8 *var_r25_2;
    u8 *var_r25_3;
    u8 *var_r25_4;
    u8 *var_r25_5;
    u8 *var_r25_6;
    u8 *var_r25_7;
    u8 *var_r25_8;
    u8 *var_r25_9;
    u8 *var_r29;
    u8 *var_r29_2;
    u8 *var_r3;
    u8 *var_r3_2;
    u8 *var_r3_3;
    u8 *var_r3_4;
    u8 *var_r3_5;

    temp_r30 = reinterpret_cast<u8*>(&reinterpret_cast<LayerGpuPassArray*>(arg0)->pass[LAYER_STATE_FIELD(s32,arg0,0x1994)]);
    temp_r0 = LAYER_STATE_FIELD(s32, temp_r30, 0x0);
    if (temp_r0 != 0) {
        temp_r31 = static_cast<u8*>(arg0) + 0xC70;
        if (temp_r0 & 1) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x4) & 1) {
                temp_r4 = LAYER_STATE_FIELD(u8, arg0, 0xC70);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x3F8) != temp_r4) {
                    LAYER_STATE_FIELD(LayerGenModeCounts, gsgfxState, 0x33).textures = temp_r4;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x02000000 | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x3F8) = temp_r4;
                }
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x8) != 0) {
                var_r29 = temp_r31;
                var_r28 = 0;
                var_r27 = 0;
                while (var_r28 < (s32) LAYER_STATE_FIELD(u8, arg0, 0xC70)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x8) & (1 << var_r28)) {
                        temp_r3 = LAYER_STATE_FIELD(u8*, var_r29, 0x18);
                        if (temp_r3 != NULL) {
                            LAYER_STATE_FIELD(s32, var_r29, 0x4) = (s32) (LAYER_STATE_FIELD(u8, temp_r3, 0x7C) + 2);
                        }
                        s32 function=LAYER_STATE_FIELD(s32,var_r29,4);
                        s32 source=LAYER_STATE_FIELD(s32,var_r29,8);
                        u32 matrix=LAYER_STATE_FIELD(u32,var_r29,12);
                        u8 normalize=LAYER_STATE_FIELD(u8,var_r29,16);
                        u32 postMatrix=LAYER_STATE_FIELD(u32,var_r29,20);
                        temp_r3_2 = reinterpret_cast<u8*>(gsgfxState) + var_r27;
                        if (((s32) LAYER_STATE_FIELD(s32, temp_r3_2, 0x358) != (s32) function) || ((s32) LAYER_STATE_FIELD(s32, temp_r3_2, 0x35C) != (s32) source) || ((u32) LAYER_STATE_FIELD(u32, temp_r3_2, 0x360) != (u32) matrix) || ((u8) LAYER_STATE_FIELD(u8, temp_r3_2, 0x364) != (u8) normalize) || ((u32) LAYER_STATE_FIELD(u32, temp_r3_2, 0x368) != (u32) postMatrix)) {
                            GSgfx_GCWriteTexCoordGen(var_r28, function, source, matrix, normalize, postMatrix);
                        }
                    }
                    var_r29 += 0x18;
                    var_r28 += 1;
                    var_r27 += 0x14;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x8) = 0U;
            }
            if ((LAYER_STATE_FIELD(s32, temp_r30, 0x4) & 4) && ((temp_r5 = LAYER_STATE_FIELD(u8, temp_r31, 0xC4), temp_r6 = LAYER_STATE_FIELD(s32, temp_r31, 0xC8), (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x3FC) == temp_r5) == 0)) || ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0x400) != temp_r6))) {
                LAYER_STATE_FIELD(u8, gsgfxState, 0x1EF) = temp_r5;
                LAYER_STATE_FIELD(u8, gsgfxState, 0x1ED) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x1ED) & ~7) | (temp_r6 & 7));
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x400);
                LAYER_STATE_FIELD(u8, gsgfxState, 0x3FC) = temp_r5;
                LAYER_STATE_FIELD(s32, gsgfxState, 0x400) = temp_r6;
            }
            if ((LAYER_STATE_FIELD(s32, temp_r30, 0x4) & 8) && ((temp_r5_2 = LAYER_STATE_FIELD(u8, temp_r31, 0xCC), temp_r6_2 = LAYER_STATE_FIELD(s32, temp_r31, 0xD0), (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x404) == temp_r5_2) == 0)) || ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0x408) != temp_r6_2))) {
                LAYER_STATE_FIELD(u8, gsgfxState, 0x1EE) = temp_r5_2;
                LAYER_STATE_FIELD(u8, gsgfxState, 0x1ED) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x1ED) & ~0x38) | ((temp_r6_2 << 3) & 0x38));
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x400);
                LAYER_STATE_FIELD(u8, gsgfxState, 0x404) = temp_r5_2;
                LAYER_STATE_FIELD(s32, gsgfxState, 0x408) = temp_r6_2;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0xC) != 0) {
                var_r3 = temp_r31;
                var_r4 = 0;
                var_r5 = 0;
                var_r6 = 0;
                while (var_r4 < (s32) LAYER_STATE_FIELD(u8, arg0, 0xC70)) {
                    if ((LAYER_STATE_FIELD(s32, temp_r30, 0xC) & (1 << var_r4)) && ((temp_r12 = LAYER_STATE_FIELD(u8, var_r3, 0xD4), temp_r7 = reinterpret_cast<u8*>(gsgfxState) + var_r6, temp_r24 = LAYER_STATE_FIELD(u8, var_r3, 0xD5), (((u8) LAYER_STATE_FIELD(u8, temp_r7, 0x40C) == temp_r12) == 0)) || ((u8) LAYER_STATE_FIELD(u8, temp_r7, 0x40D) != temp_r24))) {
                        temp_r11 = var_r5 + 0x1AD;
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~4) | ((temp_r12 << 2) & 4);
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~8) | ((temp_r24 << 3) & 8);
                        LAYER_STATE_FIELD(s32, gsgfxState, 0xC) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0xC) | (1 << var_r4));
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + (var_r6 + 0x40C), 0) = temp_r12;
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + (var_r6 + 0x40D), 0) = temp_r24;
                    }
                    var_r3 += 2;
                    var_r4 += 1;
                    var_r5 += 4;
                    var_r6 += 2;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0xC) = 0U;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x4) & 0x20) {
                GSgfx_GCSetProjection(LAYER_STATE_FIELD(s32, temp_r31, 0xE4), temp_r31 + 0xE8);
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x4) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 2) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 8) {
                temp_r4_2 = LAYER_STATE_FIELD(u8, temp_r31, 0x118);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x438) != temp_r4_2) {
                    LAYER_STATE_FIELD(LayerRasterEnable, gsgfxState, 0x31).enabled = temp_r4_2;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x438) = temp_r4_2;
                }
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 2) {
                temp_r4_3 = LAYER_STATE_FIELD(s32, temp_r31, 0x11C);
                if ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0x43C) != temp_r4_3) {
                    LAYER_STATE_FIELD(LayerGenModeStages, gsgfxState, 0x32).cull = layerCullMode[temp_r4_3];
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 1);
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x43C) = temp_r4_3;
                }
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 4) {
                temp_r4_4 = LAYER_STATE_FIELD(s32, temp_r31, 0x120);
                if ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0x440) != temp_r4_4) {
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x54) = temp_r4_4;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x04000000);
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x440) = temp_r4_4;
                }
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 1) {
                GSgfx_GCSetScissor(LAYER_STATE_FIELD(u16, temp_r31, 0x100), LAYER_STATE_FIELD(u16, temp_r31, 0x102), LAYER_STATE_FIELD(u16, temp_r31, 0x104), LAYER_STATE_FIELD(u16, temp_r31, 0x106), 0, 0);
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 0x10) {
                GSgfxVideoSetViewport__Fffffb( LAYER_STATE_FIELD(float, temp_r31, 0x108), LAYER_STATE_FIELD(float, temp_r31, 0x10C), LAYER_STATE_FIELD(float, temp_r31, 0x110), LAYER_STATE_FIELD(float, temp_r31, 0x114), false);
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x10) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 4) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x14) & 1) {
                temp_r4_5 = LAYER_STATE_FIELD(u8, temp_r31, 0x148);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x454) != temp_r4_5) {
                    LAYER_STATE_FIELD(LayerGenModeCounts, gsgfxState, 0x33).channels = temp_r4_5;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x01000000 | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x454) = temp_r4_5;
                }
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x18) != 0) {
                var_r25 = 0;
                var_r24 = temp_r31;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x18) & (1 << var_r25)) {
                        if ((u8) LAYER_STATE_FIELD(u8, var_r24, 0x14C) != 0) {
                            temp_r8 = LAYER_STATE_FIELD(s32, var_r24, 0x160);
                            var_r6_2 = reinterpret_cast<u8**>(var_r24 + 0x164);
                            var_r7 = 0;
                            while ((temp_r4_6 = *var_r6_2) != NULL) {
                                var_r5_2 = 0;
                                while (var_r5_2 < 8U) {
                                    temp_r0_2 = LAYER_STATE_FIELD(s32, temp_r4_6, 0x4);
                                    if ((temp_r8 == temp_r0_2) || ((temp_r8 == 2) && (temp_r0_2 == 1))) {
                                        var_r7 |= 1 << LAYER_STATE_FIELD(u8, temp_r4_6, 0x7C);
                                    }
                                    var_r5_2 += 1;
                                }
                                ++var_r6_2;
                            }
                            LAYER_STATE_FIELD(s32, var_r24, 0x158) = var_r7;
                        } else {
                            LAYER_STATE_FIELD(s32, var_r24, 0x158) = 0;
                        }
                        GSgfx_GCSetChanCtrl(var_r25, LAYER_STATE_FIELD(u8, var_r24, 0x14C), LAYER_STATE_FIELD(s32, var_r24, 0x150), LAYER_STATE_FIELD(s32, var_r24, 0x154), LAYER_STATE_FIELD(s32, var_r24, 0x158), LAYER_STATE_FIELD(s32, var_r24, 0x15C), LAYER_STATE_FIELD(s32, var_r24, 0x160));
                    }
                    var_r25 += 1;
                    var_r24 += 0x38;
                } while (var_r25 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x18) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x1C) != 0) {
                var_r25_2 = temp_r31;
                var_r26 = 0;
                while (var_r26 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x148)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x1C) & (1 << var_r26)) {
                        GSgfx_GCSetAmbColor(var_r26 + 4, LAYER_STATE_FIELD(GXColor, var_r25_2, 0x22C));
                    }
                    var_r25_2 += 4;
                    var_r26 += 1;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x1C) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x20) != 0) {
                var_r25_3 = temp_r31;
                var_r26_2 = 0;
                while (var_r26_2 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x148)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x20) & (1 << var_r26_2)) {
                        GSgfx_GCSetMatColor(var_r26_2 + 4, LAYER_STATE_FIELD(GXColor, var_r25_3, 0x234));
                    }
                    var_r25_3 += 4;
                    var_r26_2 += 1;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x20) = 0U;
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x14) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 8) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x24) & 1) {
                temp_r4_7 = LAYER_STATE_FIELD(u8, temp_r31, 0x23C);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x58C) != temp_r4_7) {
                    LAYER_STATE_FIELD(LayerGenModeStages, gsgfxState, 0x32).stages = temp_r4_7 - 1;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x58C) = temp_r4_7;
                }
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x28) != 0) {
                var_r25_4 = temp_r31;
                var_r26_3 = 0;
                while (var_r26_3 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x28) & (1 << var_r26_3)) {
                        GSgfx_GCSetTevOrder(var_r26_3, LAYER_STATE_FIELD(s32, var_r25_4, 0x240), LAYER_STATE_FIELD(s32, var_r25_4, 0x244), LAYER_STATE_FIELD(s32, var_r25_4, 0x248));
                    }
                    var_r25_4 += 0xC;
                    var_r26_3 += 1;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x28) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x2C) != 0) {
                var_r25_5 = temp_r31;
                var_r26_4 = 0;
                while (var_r26_4 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x2C) & (1 << var_r26_4)) {
                        GSgfx_GCSetTevColorIn(var_r26_4, LAYER_STATE_FIELD(s32, var_r25_5, 0x300), LAYER_STATE_FIELD(s32, var_r25_5, 0x304), LAYER_STATE_FIELD(s32, var_r25_5, 0x308), LAYER_STATE_FIELD(s32, var_r25_5, 0x30C));
                    }
                    var_r25_5 += 0x10;
                    var_r26_4 += 1;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x2C) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x30) != 0) {
                var_r25_6 = temp_r31;
                var_r26_5 = 0;
                while (var_r26_5 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x30) & (1 << var_r26_5)) {
                        GSgfx_GCSetTevAlphaIn(var_r26_5, LAYER_STATE_FIELD(s32, var_r25_6, 0x400), LAYER_STATE_FIELD(s32, var_r25_6, 0x404), LAYER_STATE_FIELD(s32, var_r25_6, 0x408), LAYER_STATE_FIELD(s32, var_r25_6, 0x40C));
                    }
                    var_r25_6 += 0x10;
                    var_r26_5 += 1;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x30) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x34) != 0) {
                var_r25_7 = temp_r31;
                var_r26_6 = 0;
                while (var_r26_6 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x34) & (1 << var_r26_6)) {
                        GSgfx_GCSetTevColorOp(var_r26_6, LAYER_STATE_FIELD(s32, var_r25_7, 0x500), LAYER_STATE_FIELD(s32, var_r25_7, 0x504), LAYER_STATE_FIELD(s32, var_r25_7, 0x508), LAYER_STATE_FIELD(u8, var_r25_7, 0x50C), LAYER_STATE_FIELD(s32, var_r25_7, 0x510));
                    }
                    var_r25_7 += 0x14;
                    var_r26_6 += 1;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x34) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x38) != 0) {
                var_r25_8 = temp_r31;
                var_r26_7 = 0;
                while (var_r26_7 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x38) & (1 << var_r26_7)) {
                        GSgfx_GCSetTevAlphaOp(var_r26_7, LAYER_STATE_FIELD(s32, var_r25_8, 0x640), LAYER_STATE_FIELD(s32, var_r25_8, 0x644), LAYER_STATE_FIELD(s32, var_r25_8, 0x648), LAYER_STATE_FIELD(u8, var_r25_8, 0x64C), LAYER_STATE_FIELD(s32, var_r25_8, 0x650));
                    }
                    var_r25_8 += 0x14;
                    var_r26_7 += 1;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x38) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x3C) != 0) {
                var_r3_2 = temp_r31;
                var_r4_2 = 0;
                var_ctr = 4;
                do {
                    temp_r0_3 = 1 << var_r4_2;
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x3C) & temp_r0_3) {
                        if ((u32) LAYER_STATE_FIELD(u32, var_r3_2, 0x780) == 0U) {
                            sp1C = LAYER_STATE_FIELD(s32, var_r3_2, 0x784);
                            reinterpret_cast<LayerTevRegularColorRegisters*>(gsgfxState)->ra[var_r4_2].low = LAYER_STATE_FIELD(u8,&sp1C,0);
                            reinterpret_cast<LayerTevRegularColorRegisters*>(gsgfxState)->ra[var_r4_2].high = LAYER_STATE_FIELD(u8,&sp1C,3);
                            reinterpret_cast<LayerTevRegularColorRegisters*>(gsgfxState)->bg[var_r4_2].low = LAYER_STATE_FIELD(u8,&sp1C,2);
                            reinterpret_cast<LayerTevRegularColorRegisters*>(gsgfxState)->bg[var_r4_2].high = LAYER_STATE_FIELD(u8,&sp1C,1);
                            LAYER_STATE_FIELD(s32, gsgfxState, 0x24) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x24) | temp_r0_3);
                        } else {
                            sp34 = LAYER_STATE_FIELD(s32, var_r3_2, 0x784);
                            sp38 = LAYER_STATE_FIELD(s32, var_r3_2, 0x788);
                            reinterpret_cast<LayerTevRegularColorRegisters*>(gsgfxState)->ra[var_r4_2].low = LAYER_STATE_FIELD(s16,&sp34,0);
                            reinterpret_cast<LayerTevRegularColorRegisters*>(gsgfxState)->ra[var_r4_2].high = LAYER_STATE_FIELD(s16,&sp38,2);
                            reinterpret_cast<LayerTevRegularColorRegisters*>(gsgfxState)->bg[var_r4_2].low = LAYER_STATE_FIELD(s16,&sp38,0);
                            reinterpret_cast<LayerTevRegularColorRegisters*>(gsgfxState)->bg[var_r4_2].high = LAYER_STATE_FIELD(s16,&sp34,2);
                            LAYER_STATE_FIELD(s32, gsgfxState, 0x24) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x24) | temp_r0_3);
                        }
                    }
                    var_r3_2 += 0xC;
                    var_r4_2 += 1;
                    var_ctr -= 1;
                } while (var_ctr != 0);
                LAYER_STATE_FIELD(s32, temp_r30, 0x3C) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x40) != 0) {
                var_r28_2 = 0;
                var_r29_2 = temp_r31;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x40) & (1 << var_r28_2)) {
                        temp_r0_4 = LAYER_STATE_FIELD(s32, var_r29_2, 0x7B0);
                        switch (temp_r0_4) {
                        case 0:
                            GSgfx_GCSetTevDirect(var_r28_2);
                            break;
                        case 1:
                            sp8 = (s32) LAYER_STATE_FIELD(u8, var_r29_2, 0x7D1);
                            spC = LAYER_STATE_FIELD(s32, var_r29_2, 0x7CC);
                            GSgfx_GCSetTevIndirect(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), LAYER_STATE_FIELD(s32, var_r29_2, 0x7B8), LAYER_STATE_FIELD(s32, var_r29_2, 0x7BC), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C0), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C4), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C8), LAYER_STATE_FIELD(u8, var_r29_2, 0x7D0), sp8, spC);
                            break;
                        case 2:
                            GSgfx_GCSetTevIndWarp(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), LAYER_STATE_FIELD(u8, var_r29_2, 0x7B5), LAYER_STATE_FIELD(u8, var_r29_2, 0x7B6), LAYER_STATE_FIELD(s32, var_r29_2, 0x7B8));
                            break;
                        case 3:
                            sp8 = LAYER_STATE_FIELD(s32, var_r29_2, 0x7C8);
                            spC = LAYER_STATE_FIELD(s32, var_r29_2, 0x7CC);
                            GSgfx_GCWriteTevIndTile(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), (u16) LAYER_STATE_FIELD(u16, var_r29_2, 0x7B6), (u16) LAYER_STATE_FIELD(u16, var_r29_2, 0x7B8), LAYER_STATE_FIELD(u16, var_r29_2, 0x7BA), (u16) LAYER_STATE_FIELD(u16, var_r29_2, 0x7BC), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C0), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C4), sp8, spC);
                            break;
                        case 4:
                            GSgfx_GCWriteTevIndBumpST(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), LAYER_STATE_FIELD(s32, var_r29_2, 0x7B8));
                            break;
                        case 5:
                            GSgfx_GCSetTevIndBumpXYZ(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), LAYER_STATE_FIELD(s32, var_r29_2, 0x7B8));
                            break;
                        case 6:
                            GSgfx_GCSetTevIndRepeat(var_r28_2);
                            break;
                        }
                    }
                    var_r28_2 += 1;
                    var_r29_2 += 0x24;
                } while (var_r28_2 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x40) = 0U;
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x24) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 0x80) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x44) & 1) {
                temp_r4_8 = LAYER_STATE_FIELD(u8, temp_r31, 0x840);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x58D) != temp_r4_8) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x31) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x31) & ~7) | (temp_r4_8 & 7));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x58D) = temp_r4_8;
                }
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x48) != 0) {
                var_r25_9 = temp_r31;
                var_r26_8 = 0;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x48) & (1 << var_r26_8)) {
                        GSgfx_GCSetIndTexOrder(var_r26_8, LAYER_STATE_FIELD(s32, var_r25_9, 0x844), LAYER_STATE_FIELD(s32, var_r25_9, 0x848));
                    }
                    var_r26_8 += 1;
                    var_r25_9 += 8;
                } while (var_r26_8 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x48) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x4C) != 0) {
                var_r25_10 = temp_r31;
                var_r26_9 = 0;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x4C) & (1 << var_r26_9)) {
                        GSgfx_GCSetIndTexCoordScale(var_r26_9, LAYER_STATE_FIELD(s32, var_r25_10, 0x864), LAYER_STATE_FIELD(s32, var_r25_10, 0x868));
                    }
                    var_r26_9 += 1;
                    var_r25_10 += 8;
                } while (var_r26_9 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x4C) = 0U;
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x44) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 0x10) {
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x50) != 0) {
                var_r25_11 = temp_r31;
                var_r26_10 = 0;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x50) & (1 << var_r26_10)) {
                        sp28 = LAYER_STATE_FIELD(s32, var_r25_11, 0x884);
                        GSgfx_GCSetTevKColor(var_r26_10, *reinterpret_cast<GXColor*>(&sp28));
                    }
                    var_r26_10 += 1;
                    var_r25_11 += 4;
                } while (var_r26_10 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x50) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x54) != 0) {
                var_r3_3 = temp_r31;
                var_r4_3 = 0;
                var_r5_4 = 0;
                while (var_r4_3 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x54) & (1 << var_r4_3)) {
                        temp_r9_2 = LAYER_STATE_FIELD(s32, var_r3_3, 0x894);
                        if ((s32) LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r5_4 + 0xA24), 0) != temp_r9_2) {
                            temp_r10_3 = var_r4_3 >> 1;
                            if (var_r4_3 & 1) {
                                temp_r6_3 = (temp_r10_3 * 4) + 0x204;
                                LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r6_3, 0) = (LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r6_3, 0) & ~0x7C000) | ((temp_r9_2 << 0xE) & 0x7C000);
                            } else {
                                temp_r6_4 = (temp_r10_3 * 4) + 0x206;
                                LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r6_4, 0) = (LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r6_4, 0) & ~0x1F0) | ((temp_r9_2 << 4) & 0x1F0);
                            }
                            LAYER_STATE_FIELD(s32, gsgfxState, 0x18) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x18) | (1 << temp_r10_3));
                            LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r5_4 + 0xA24), 0) = temp_r9_2;
                        }
                    }
                    var_r3_3 += 4;
                    var_r4_3 += 1;
                    var_r5_4 += 4;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x54) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x58) != 0) {
                var_r3_4 = temp_r31;
                var_r4_4 = 0;
                var_r5_5 = 0;
                while (var_r4_4 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x58) & (1 << var_r4_4)) {
                        temp_r9_3 = LAYER_STATE_FIELD(s32, var_r3_4, 0x8D4);
                        if ((s32) LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r5_5 + 0xA64), 0) != temp_r9_3) {
                            temp_r10_4 = var_r4_4 >> 1;
                            if (var_r4_4 & 1) {
                                temp_r6_5 = (temp_r10_4 * 4) + 0x205;
                                LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r6_5, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r6_5, 0) & ~0xF8) | ((temp_r9_3 << 3) & 0xF8);
                            } else {
                                temp_r6_6 = (temp_r10_4 * 4) + 0x206;
                                LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r6_6, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r6_6, 0) & ~0x3E) | ((temp_r9_3 << 1) & 0x3E);
                            }
                            LAYER_STATE_FIELD(s32, gsgfxState, 0x18) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x18) | (1 << temp_r10_4));
                            LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r5_5 + 0xA64), 0) = temp_r9_3;
                        }
                    }
                    var_r3_4 += 4;
                    var_r4_4 += 1;
                    var_r5_5 += 4;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x58) = 0U;
            }
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 0x20) {
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x5C) != 0) {
                var_r3_5 = temp_r31;
                var_r4_5 = 0;
                var_r5_6 = 0;
                var_r6_3 = 0;
                while (var_r4_5 < (s32) LAYER_STATE_FIELD(u8, temp_r31, 0x23C)) {
                    if ((LAYER_STATE_FIELD(s32, temp_r30, 0x5C) & (1 << var_r4_5)) && ((temp_r24_2 = LAYER_STATE_FIELD(s32, var_r3_5, 0x914), temp_r7_4 = reinterpret_cast<u8*>(gsgfxState) + var_r6_3, temp_r25 = LAYER_STATE_FIELD(s32, var_r3_5, 0x918), (((s32) LAYER_STATE_FIELD(s32, temp_r7_4, 0xAA4) == temp_r24_2) == 0)) || ((s32) LAYER_STATE_FIELD(s32, temp_r7_4, 0xAA8) != temp_r25))) {
                        temp_r12_3 = var_r5_6 + 0x267;
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r12_3, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r12_3, 0) & ~3) | (temp_r24_2 & 3);
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r12_3, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r12_3, 0) & ~0xC) | ((temp_r25 << 2) & 0xC);
                        LAYER_STATE_FIELD(s32, gsgfxState, 0x20) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x20) | (1 << var_r4_5));
                        LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r6_3 + 0xAA4), 0) = temp_r24_2;
                        LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r6_3 + 0xAA8), 0) = temp_r25;
                    }
                    var_r3_5 += 8;
                    var_r4_5 += 1;
                    var_r5_6 += 4;
                    var_r6_3 += 8;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x5C) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x60) != 0) {
                var_r25_12 = temp_r31;
                var_r26_11 = 0;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x60) & (1 << var_r26_11)) {
                        GSgfx_GCSetTevSwapModeTable(var_r26_11, LAYER_STATE_FIELD(s32, var_r25_12, 0x994), LAYER_STATE_FIELD(s32, var_r25_12, 0x998), LAYER_STATE_FIELD(s32, var_r25_12, 0x99C), LAYER_STATE_FIELD(s32, var_r25_12, 0x9A0));
                    }
                    var_r26_11 += 1;
                    var_r25_12 += 0x10;
                } while (var_r26_11 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x60) = 0U;
            }
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 0x40) {
            var_r29_3 = LAYER_STATE_FIELD(s32, temp_r31, 0x9F0);
            temp_r0_5 = LAYER_STATE_FIELD(u8, temp_r31, 0x9EC) != 0;
            var_r28_3 = temp_r0_5;
            if (((u8) LAYER_STATE_FIELD(u8, temp_r31, 0x9E8) == 1) && (temp_r0_5 == 0)) {
                var_r28_3 = 1;
                var_r29_3 = 7;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 1) {
                GSgfx_GCSetBlendMode(LAYER_STATE_FIELD(s32, temp_r31, 0x9D4), LAYER_STATE_FIELD(s32, temp_r31, 0x9D8), LAYER_STATE_FIELD(s32, temp_r31, 0x9DC), LAYER_STATE_FIELD(s32, temp_r31, 0x9E0));
            }
            if ((LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 2) && ((temp_r4_9 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E4), temp_r5_3 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E5), (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBF2) == temp_r4_9) == 0)) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBF3) != temp_r5_3))) {
                LAYER_STATE_FIELD(u8, gsgfxState, 0x3E) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x3E) & ~1) | (temp_r4_9 & 1));
                LAYER_STATE_FIELD(u8, gsgfxState, 0x3F) = temp_r5_3;
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 8);
                LAYER_STATE_FIELD(u8, gsgfxState, 0xBF2) = temp_r4_9;
                LAYER_STATE_FIELD(u8, gsgfxState, 0xBF3) = temp_r5_3;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 4) {
                temp_r4_10 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E6);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBC4) != temp_r4_10) {
                    LAYER_STATE_FIELD(LayerColorUpdate, gsgfxState, 0x3B).color = temp_r4_10;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 4);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBC4) = temp_r4_10;
                }
                temp_r4_11 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E7);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBC5) != temp_r4_11) {
                    LAYER_STATE_FIELD(LayerColorUpdate, gsgfxState, 0x3B).alpha = temp_r4_11;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 4);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBC5) = temp_r4_11;
                }
                temp_r5_4 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E8);
                if (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBE4) != var_r28_3) || ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0xBE8) != var_r29_3) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBEC) != temp_r5_4)) {
                    LAYER_STATE_FIELD(LayerZMode, gsgfxState, 0x37).enabled = var_r28_3;
                    LAYER_STATE_FIELD(LayerZMode, gsgfxState, 0x37).compare = var_r29_3;
                    LAYER_STATE_FIELD(LayerZMode, gsgfxState, 0x37).update = temp_r5_4;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 2);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBE4) = var_r28_3;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0xBE8) = var_r29_3;
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBEC) = temp_r5_4;
                }
            }
            if ((LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 8) && ((temp_r5_5 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E8), (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBE4) == var_r28_3) == 0)) || ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0xBE8) != var_r29_3) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBEC) != temp_r5_5))) {
                LAYER_STATE_FIELD(LayerZMode, gsgfxState, 0x37).enabled = var_r28_3;
                LAYER_STATE_FIELD(LayerZMode, gsgfxState, 0x37).compare = var_r29_3;
                LAYER_STATE_FIELD(LayerZMode, gsgfxState, 0x37).update = temp_r5_5;
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 2);
                LAYER_STATE_FIELD(u8, gsgfxState, 0xBE4) = var_r28_3;
                LAYER_STATE_FIELD(s32, gsgfxState, 0xBE8) = var_r29_3;
                LAYER_STATE_FIELD(u8, gsgfxState, 0xBEC) = temp_r5_5;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 0x10) {
                GSgfx_GCSetAlphaCompare(LAYER_STATE_FIELD(s32, temp_r31, 0x9F4), LAYER_STATE_FIELD(u8, temp_r31, 0xA00), LAYER_STATE_FIELD(s32, temp_r31, 0x9F8), LAYER_STATE_FIELD(s32, temp_r31, 0x9FC), LAYER_STATE_FIELD(u8, temp_r31, 0xA01));
                temp_r4_12 = LAYER_STATE_FIELD(u8, temp_r31, 0xA02);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBF0) != temp_r4_12) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x43) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x43) & ~0x40) | ((temp_r4_12 << 6) & 0x40));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x10);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBF0) = temp_r4_12;
                }
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 0x20) {
                temp_r4_13 = LAYER_STATE_FIELD(u8, temp_r31, 0xA04);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBF1) != temp_r4_13) {
                    LAYER_STATE_FIELD(LayerColorUpdate, gsgfxState, 0x3B).dither = temp_r4_13;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 4);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBF1) = temp_r4_13;
                }
            }
            temp_r3_3 = LAYER_STATE_FIELD(s32, temp_r30, 0x64);
            if (temp_r3_3 & 0x40) {
                if ((u8) LAYER_STATE_FIELD(u8, temp_r31, 0xA37) == 1) {
                    var_r24_2 = LAYER_STATE_FIELD(s32, temp_r31, 0xA08);
                    if (var_r24_2 == 0) {
                        LAYER_STATE_FIELD(u8, temp_r31, 0xA37) = 0U;
                    }
                } else {
                    var_r24_2 = 0;
                }
                f32 startZ=LAYER_STATE_FIELD(float,temp_r31,0xa0c);
                f32 endZ=LAYER_STATE_FIELD(float,temp_r31,0xa10);
                f32 nearZ=LAYER_STATE_FIELD(float,temp_r31,0xa14);
                f32 farZ=LAYER_STATE_FIELD(float,temp_r31,0xa18);
                if (((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0xBF4) != var_r24_2) || (LAYER_STATE_FIELD(float, gsgfxState, 0xBF8) != startZ) || (LAYER_STATE_FIELD(float, gsgfxState, 0xBFC) != endZ) || (LAYER_STATE_FIELD(float, gsgfxState, 0xC00) != nearZ) || (LAYER_STATE_FIELD(float, gsgfxState, 0xC04) != farZ)) {
                    GSgfx_GCWriteFog(var_r24_2, startZ, endZ, nearZ, farZ);
                }
                if ((var_r24_2 != 0) && ((temp_r3_4 = LAYER_STATE_FIELD(s32, temp_r31, 0xA1C), sp24 = temp_r3_4, (((u32) LAYER_STATE_FIELD(u32, gsgfxState, 0xC09) == temp_r3_4) == 0)) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xC08) == 1))) {
                    sp18 = sp24;
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x2F5) = LAYER_STATE_FIELD(u8, &sp18,0);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x2F6) = LAYER_STATE_FIELD(u8, &sp18,1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x2F7) = LAYER_STATE_FIELD(u8, &sp18,2);
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x20000);
                    LAYER_STATE_FIELD(s32, gsgfxState, 0xC09) = sp24;
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xC08) = 0U;
                }
            } else if ((temp_r3_3 & 0x80) && ((temp_r3_5 = LAYER_STATE_FIELD(s32, temp_r31, 0xA1C), sp20 = temp_r3_5, (((u32) LAYER_STATE_FIELD(u32, gsgfxState, 0xC09) == temp_r3_5) == 0)) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xC08) == 1))) {
                sp14 = sp20;
                LAYER_STATE_FIELD(u8, gsgfxState, 0x2F5) = LAYER_STATE_FIELD(u8, &sp14,0);
                LAYER_STATE_FIELD(u8, gsgfxState, 0x2F6) = LAYER_STATE_FIELD(u8, &sp14,1);
                LAYER_STATE_FIELD(u8, gsgfxState, 0x2F7) = LAYER_STATE_FIELD(u8, &sp14,2);
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x20000);
                LAYER_STATE_FIELD(s32, gsgfxState, 0xC09) = sp20;
                LAYER_STATE_FIELD(u8, gsgfxState, 0xC08) = 0U;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 0x100) {
                Mtx44 fogProjection={0};
                temp_r3_6 = static_cast<u8*>(GSgfxVideoGetViewport());
                if ((s32) LAYER_STATE_FIELD(s32, temp_r31, 0xE4) == 0) {
                    fogProjection[0][0] = LAYER_STATE_FIELD(float, temp_r31, 0xE8);
                    fogProjection[0][2] = LAYER_STATE_FIELD(float, temp_r31, 0xEC);
                    fogProjection[0][3] = 0.0f;
                    fogProjection[1][1] = LAYER_STATE_FIELD(float, temp_r31, 0xF0);
                    fogProjection[1][2] = LAYER_STATE_FIELD(float, temp_r31, 0xF4);
                    fogProjection[1][3] = 0.0f;
                    fogProjection[2][2] = LAYER_STATE_FIELD(float, temp_r31, 0xF8);
                    fogProjection[2][3] = LAYER_STATE_FIELD(float, temp_r31, 0xFC);
                    fogProjection[3][2] = -1.0f;
                    fogProjection[3][3] = 0.0f;
                } else {
                    fogProjection[0][0] = LAYER_STATE_FIELD(float, temp_r31, 0xE8);
                    fogProjection[0][2] = 0.0f;
                    fogProjection[0][3] = LAYER_STATE_FIELD(float, temp_r31, 0xEC);
                    fogProjection[1][1] = LAYER_STATE_FIELD(float, temp_r31, 0xF0);
                    fogProjection[1][2] = 0.0f;
                    fogProjection[1][3] = LAYER_STATE_FIELD(float, temp_r31, 0xF4);
                    fogProjection[2][2] = LAYER_STATE_FIELD(float, temp_r31, 0xF8);
                    fogProjection[2][3] = LAYER_STATE_FIELD(float, temp_r31, 0xFC);
                    fogProjection[3][2] = -1.0f;
                    fogProjection[3][3] = 0.0f;
                }
                u16 fogWidth = __OSf32tou16(LAYER_STATE_FIELD(float, temp_r3_6, 8));
                GXInitFogAdjTable(reinterpret_cast<GXFogAdjTable*>(temp_r31 + 0xA20), fogWidth, fogProjection);
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 0x200) {
                GSgfx_GCSetFogRangeAdj(LAYER_STATE_FIELD(u8, temp_r31, 0xA36), LAYER_STATE_FIELD(u16, temp_r31, 0xA34), temp_r31 + 0xA20);
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x64) = 0;
        }
        LAYER_STATE_FIELD(s32, temp_r30, 0x0) = 0U;
    }
}

struct LayerFogRangeRegister { u32 address:8, reserved:13, enable:1, center:10; };
struct LayerFogRangeKRegister { u32 address:8, high:12, low:12; };
struct LayerFogRangeRegisters { u8 reserved[0x2f8]; LayerFogRangeRegister range; LayerFogRangeKRegister k[5]; };
struct LayerFogRangeTable { u32 v[5]; };
struct LayerFogRangeCache { u8 reserved[0xc0d]; u8 enable; u16 center; LayerFogRangeTable table; };
#define LAYER_FOG_RANGE (reinterpret_cast<LayerFogRangeRegisters*>(gsgfxState))
#define LAYER_FOG_RANGE_CACHE (reinterpret_cast<LayerFogRangeCache*>(gsgfxState))
inline void GSgfx_GCWriteFogRangeAdj(u8 enable, u16 center, GXFogAdjTable *table) {
    LAYER_FOG_RANGE->range.enable = enable;
    LAYER_FOG_RANGE->range.center = (u16)(center + 342);
    layerField<s32>(gsgfxState, 0x0) |= 0x40000;
    LAYER_FOG_RANGE_CACHE->enable = enable;
    LAYER_FOG_RANGE_CACHE->center = center;
    if (enable == 1) {
        LAYER_FOG_RANGE->k[0].low = table->r[0];
        LAYER_FOG_RANGE->k[0].high = table->r[1];
        LAYER_FOG_RANGE->k[1].low = table->r[2];
        LAYER_FOG_RANGE->k[1].high = table->r[3];
        LAYER_FOG_RANGE->k[2].low = table->r[4];
        LAYER_FOG_RANGE->k[2].high = table->r[5];
        LAYER_FOG_RANGE->k[3].low = table->r[6];
        LAYER_FOG_RANGE->k[3].high = table->r[7];
        LAYER_FOG_RANGE->k[4].low = table->r[8];
        LAYER_FOG_RANGE->k[4].high = table->r[9];
        layerField<s32>(gsgfxState, 0x0) |= 0x80000;
        LayerFogRangeTable *c = &LAYER_FOG_RANGE_CACHE->table;
        LayerFogRangeTable *t = reinterpret_cast<LayerFogRangeTable*>(table);
        c->v[0] = t->v[0]; c->v[1] = t->v[1]; c->v[2] = t->v[2]; c->v[3] = t->v[3]; c->v[4] = t->v[4];
    }
}
__declspec(weak) void GSgfx_GCSetFogRangeAdj(u8 arg0, u16 arg1, u8 *arg2) {
    LayerFogRangeTable *p = reinterpret_cast<LayerFogRangeTable*>(arg2);
    u8 changed;
    if (LAYER_FOG_RANGE_CACHE->enable != arg0 || LAYER_FOG_RANGE_CACHE->center != arg1) changed = 1;
    else {
        changed = 0;
        for (s32 i = 0; i < 5; i++) {
            if (LAYER_FOG_RANGE_CACHE->table.v[i] != p->v[i]) { changed = 1; break; }
        }
    }
    if (changed == 1)
        GSgfx_GCWriteFogRangeAdj(arg0, arg1, reinterpret_cast<GXFogAdjTable*>(arg2));
}


__declspec(weak) void GSgfx_GCSetAlphaCompare(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4) {
    if (((s32) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->compare0 != arg0) || ((u8) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->reference0 != arg1) || ((s32) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->operation != arg2) || ((s32) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->compare1 != arg3) || ((u8) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->reference1 != arg4)) {
        layerField<u8>(gsgfxState, 0x1FB) = arg1;
        layerField<u8>(gsgfxState, 0x1FA) = arg4;
        layerField<u8>(gsgfxState, 0x1F9) = (u8) ((layerField<u8>(gsgfxState, 0x1F9) & ~7) | (arg0 & 7));
        layerField<u8>(gsgfxState, 0x1F9) = (u8) ((layerField<u8>(gsgfxState, 0x1F9) & ~0x38) | ((arg3 << 3) & 0x38));
        layerField<u8>(gsgfxState, 0x1F9) = (u8) ((layerField<u8>(gsgfxState, 0x1F9) & ~0xC0) | ((arg2 << 6) & 0xC0));
        layerField<s32>(gsgfxState, 0x0) = (s32) (layerField<s32>(gsgfxState, 0x0) | 0x100);
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->compare0 = arg0;
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->reference0 = arg1;
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->operation = arg2;
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->compare1 = arg3;
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->reference1 = arg4;
    }
}

__declspec(weak) void GSgfx_GCSetBlendMode(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r0;

    if (((s32) reinterpret_cast<LayerBlendCache*>(gsgfxState)->mode != arg0) || ((s32) reinterpret_cast<LayerBlendCache*>(gsgfxState)->source != arg1) || ((s32) reinterpret_cast<LayerBlendCache*>(gsgfxState)->destination != arg2) || ((s32) reinterpret_cast<LayerBlendCache*>(gsgfxState)->operation != arg3)) {
        var_r0 = 0;
        if ((arg0 == 1) || (arg0 == 3)) {
            var_r0 = 1;
        }
        LAYER_BLEND_STATE->blend.fields.blend = var_r0;
        LAYER_BLEND_STATE->blend.fields.logic = (u8)(arg0 == 2);
        LAYER_BLEND_STATE->blend.fields.source = arg1;
        LAYER_BLEND_STATE->blend.fields.destination = arg2;
        LAYER_BLEND_STATE->blend.fields.subtract = (u8)(arg0 == 3);
        LAYER_BLEND_STATE->blend.fields.operation = arg3;
        layerField<s32>(gsgfxState, 0x0) = (s32) (layerField<s32>(gsgfxState, 0x0) | 4);
        reinterpret_cast<LayerBlendCache*>(gsgfxState)->mode = arg0;
        reinterpret_cast<LayerBlendCache*>(gsgfxState)->source = arg1;
        reinterpret_cast<LayerBlendCache*>(gsgfxState)->destination = arg2;
        reinterpret_cast<LayerBlendCache*>(gsgfxState)->operation = arg3;
    }
}

__declspec(weak) void GSgfx_GCSetTevSwapModeTable(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *cached = reinterpret_cast<u8*>(gsgfxState) + arg0 * sizeof(LayerSwapTable);
    if (reinterpret_cast<LayerSwapTableCache*>(cached)->red != arg1 || reinterpret_cast<LayerSwapTableCache*>(cached)->green != arg2 || reinterpret_cast<LayerSwapTableCache*>(cached)->blue != arg3 || reinterpret_cast<LayerSwapTableCache*>(cached)->alpha != arg4) {
        s32 b;
        s32 a;
        a = arg0 * 2;
        b = a + 1;
        LAYER_TEV_KSEL_STATE->ksel[a].fields.swap0 = arg1;
        LAYER_TEV_KSEL_STATE->ksel[a].fields.swap1 = arg2;
        LAYER_TEV_KSEL_STATE->ksel[b].fields.swap0 = arg3;
        LAYER_TEV_KSEL_STATE->ksel[b].fields.swap1 = arg4;
        layerField<s32>(gsgfxState, 0x18) |= 1 << a;
        layerField<s32>(gsgfxState, 0x18) |= 1 << b;
        layerSwapTableCache()[arg0].red = arg1;
        layerSwapTableCache()[arg0].green = arg2;
        layerSwapTableCache()[arg0].blue = arg3;
        layerSwapTableCache()[arg0].alpha = arg4;
    }
}


struct LayerColor4 { u8 r, g, b, a; };
struct LayerChanColorCache { u8 dirty; LayerColor4 color; };
#define LAYER_AMB_CACHE (reinterpret_cast<LayerChanColorCache*>(reinterpret_cast<u8*>(gsgfxState) + 0x4b8))
#define LAYER_MAT_CACHE (reinterpret_cast<LayerChanColorCache*>(reinterpret_cast<u8*>(gsgfxState) + 0x4c2))
#define LAYER_GC_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<u8*>(gsgfxState) + offset))
#define LAYER_KCOLOR_CACHE (reinterpret_cast<LayerChanColorCache*>(reinterpret_cast<u8*>(gsgfxState) + 0xa10))
struct LayerTevKColorRegister { u32 address:8, bank:1, high:11, reserved:1, low:11; };
struct LayerTevKColorRegisters { u8 reserved[0x2c4]; LayerTevKColorRegister ra[4]; LayerTevKColorRegister bg[4]; };
inline void GSgfx_GCWriteTevKColor(s32 id, LayerColor4 color) {
    reinterpret_cast<LayerTevKColorRegisters*>(gsgfxState)->ra[id].low = color.r;
    reinterpret_cast<LayerTevKColorRegisters*>(gsgfxState)->ra[id].high = color.a;
    reinterpret_cast<LayerTevKColorRegisters*>(gsgfxState)->bg[id].low = color.b;
    reinterpret_cast<LayerTevKColorRegisters*>(gsgfxState)->bg[id].high = color.g;
    layerField<s32>(gsgfxState, 0x28) |= 1 << id;
    LAYER_GC_FIELD(u32, (u32)id * 5 + 0xa11) = *(u32*)&color;
    LAYER_KCOLOR_CACHE[(u32)id].dirty = 0;
}
__declspec(weak) void GSgfx_GCSetTevKColor(s32 arg0, GXColor arg1) {
    if (LAYER_GC_FIELD(u32, 0xa11 + arg0 * 5) != *reinterpret_cast<u32*>(&arg1) || LAYER_KCOLOR_CACHE[arg0].dirty == 1)
        GSgfx_GCWriteTevKColor(arg0, *reinterpret_cast<LayerColor4*>(&arg1));
}


inline void GSgfx_GCWriteIndTexCoordScale(s32 stage, s32 scaleS, s32 scaleT) {
    s32 reg = stage >> 1;
    if (stage & 1) {
        LAYER_IND_STATE->scale[reg].fields.s1 = scaleS;
        LAYER_IND_STATE->scale[reg].fields.t1 = scaleT;
    } else {
        LAYER_IND_STATE->scale[reg].fields.s0 = scaleS;
        LAYER_IND_STATE->scale[reg].fields.t1 = scaleT;
    }
    layerField<s32>(gsgfxState, 0x8) |= 1 << reg;
    layerIndScaleCache()[(u32)stage].s = scaleS;
    layerIndScaleCache()[(u32)stage].t = scaleT;
}
__declspec(weak) void GSgfx_GCSetIndTexCoordScale(s32 arg0, s32 arg1, s32 arg2) {
    if (reinterpret_cast<LayerIndCache*>(gsgfxState)->scale[arg0].s != arg1 || reinterpret_cast<LayerIndCache*>(gsgfxState)->scale[arg0].t != arg2)
        GSgfx_GCWriteIndTexCoordScale(arg0, arg1, arg2);
}


__declspec(weak) void GSgfx_GCSetIndTexOrder(s32 arg0, s32 arg1, s32 arg2) {
    u8 *cached = reinterpret_cast<u8*>(gsgfxState) + arg0 * sizeof(LayerIndOrder);
    if (reinterpret_cast<LayerIndOrderCache*>(cached)->coordinate != arg1 || reinterpret_cast<LayerIndOrderCache*>(cached)->map != arg2) {
        switch (arg0) {
        case 0:
            LAYER_IND_STATE->order.fields.map0 = arg2;
            LAYER_IND_STATE->order.fields.coordinate0 = arg1;
            break;
        case 1:
            LAYER_IND_STATE->order.fields.map1 = arg2;
            LAYER_IND_STATE->order.fields.coordinate1 = arg1;
            break;
        case 2:
            LAYER_IND_STATE->order.fields.map2 = arg2;
            LAYER_IND_STATE->order.fields.coordinate2 = arg1;
            break;
        case 3:
            LAYER_IND_STATE->order.fields.map3 = arg2;
            LAYER_IND_STATE->order.fields.coordinate3 = arg1;
            break;
        }
        layerField<s32>(gsgfxState, 0x0) |= 0x2000;
        layerField<s32>(gsgfxState, 0xC) |= 1 << arg1;
        layerIndOrderCache()[arg0].coordinate = arg1;
        layerIndOrderCache()[arg0].map = arg2;
    }
}


struct LayerTevStatusView { u8 pad[0xB64]; u8 status[16]; };
inline u8 *layerTevIndirectMode() { return reinterpret_cast<LayerTevStatusView*>(gsgfxState)->status; }
#define TEVST(i) (layerTevIndirectMode()[i])

static inline void layerSetTevIndirect(s32 stage, s32 indStage, GXIndTexFormat format, GXIndTexBiasSel bias, GXIndTexMtxID matrix, GXIndTexWrap wrapS, GXIndTexWrap wrapT, u8 addPrevious, u8 useOriginalLod, s32 alpha) {
    LAYER_INDIRECT_STATE->indirect[stage].fields.stage = indStage;
    LAYER_INDIRECT_STATE->indirect[stage].fields.format = format;
    LAYER_INDIRECT_STATE->indirect[stage].fields.bias = bias;
    LAYER_INDIRECT_STATE->indirect[stage].fields.alpha = alpha;
    LAYER_INDIRECT_STATE->indirect[stage].fields.matrix = matrix;
    LAYER_INDIRECT_STATE->indirect[stage].fields.wrapS = wrapS;
    LAYER_INDIRECT_STATE->indirect[stage].fields.wrapT = wrapT;
    LAYER_INDIRECT_STATE->indirect[stage].fields.useOriginalLod = useOriginalLod;
    LAYER_INDIRECT_STATE->indirect[stage].fields.addPrevious = addPrevious;
    layerField<s32>(gsgfxState, 0x2C) |= 1 << stage;
    TEVST(stage) = 2;
}
__declspec(weak) void GSgfx_GCSetTevIndRepeat(s32 arg0) {
    layerSetTevIndirect(arg0, 0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_0, GX_ITW_0, 1, 0, 0);
}


__declspec(weak) void GSgfx_GCSetTevIndBumpXYZ(s32 arg0, s32 arg1, s32 arg2) {
    layerSetTevIndirect(arg0, arg1, GX_ITF_8, GX_ITB_STU, (GXIndTexMtxID)arg2, GX_ITW_OFF, GX_ITW_OFF, 0, 0, 0);
}


__declspec(weak) void GSgfx_GCSetTevIndWarp(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    GXIndTexWrap wrap = arg3 ? GX_ITW_0 : GX_ITW_OFF;
    layerSetTevIndirect(arg0, arg1, GX_ITF_8, arg2 ? GX_ITB_STU : GX_ITB_NONE, (GXIndTexMtxID)arg4, wrap, wrap, 0, 0, 0);
}


__declspec(weak) void GSgfx_GCSetTevIndirect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, u8 arg_sp8, s32 arg_spC) {
    layerSetTevIndirect(arg0, arg1, (GXIndTexFormat)arg2, (GXIndTexBiasSel)arg3, (GXIndTexMtxID)arg4, (GXIndTexWrap)arg5, (GXIndTexWrap)arg6, arg7, arg_sp8, arg_spC);
}


__declspec(weak) void GSgfx_GCSetTevDirect(s32 arg0) {
    if (TEVST(arg0) != 1) {
        layerSetTevIndirect(arg0, 0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, 0, 0, 0);
        TEVST(arg0) = 1;
    }
}


__declspec(weak) void GSgfx_GCSetTevAlphaOp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    u8 *cached = reinterpret_cast<u8*>(gsgfxState) + arg0 * sizeof(LayerTevOperation);
    if (reinterpret_cast<LayerTevAlphaOperationCache*>(cached)->operation != arg1 || reinterpret_cast<LayerTevAlphaOperationCache*>(cached)->bias != arg2 || reinterpret_cast<LayerTevAlphaOperationCache*>(cached)->scale != arg3 || reinterpret_cast<LayerTevAlphaOperationCache*>(cached)->clamp != arg4 || reinterpret_cast<LayerTevAlphaOperationCache*>(cached)->output != arg5) {
        if (arg1 <= 1) {
            LAYER_TEV_STATE->alpha[arg0].fields.bias = arg2;
            LAYER_TEV_STATE->alpha[arg0].fields.sub = arg1;
            LAYER_TEV_STATE->alpha[arg0].fields.clamp = arg4;
            LAYER_TEV_STATE->alpha[arg0].fields.shift = arg3;
            LAYER_TEV_STATE->alpha[arg0].fields.dest = arg5;
        } else {
            LAYER_TEV_STATE->alpha[arg0].fields.bias = 3;
            LAYER_TEV_STATE->alpha[arg0].fields.sub = arg1;
            LAYER_TEV_STATE->alpha[arg0].fields.clamp = arg4;
            LAYER_TEV_STATE->alpha[arg0].fields.shift = (arg1 >> 1) & 3;
            LAYER_TEV_STATE->alpha[arg0].fields.dest = arg5;
        }
        layerField<s32>(gsgfxState, 0x20) |= 1 << arg0;
        layerTevAlphaOpCache()[arg0].operation = arg1;
        layerTevAlphaOpCache()[arg0].bias = arg2;
        layerTevAlphaOpCache()[arg0].scale = arg3;
        layerTevAlphaOpCache()[arg0].clamp = arg4;
        layerTevAlphaOpCache()[arg0].output = arg5;
    }
}


__declspec(weak) void GSgfx_GCSetTevColorOp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    u8 *cached = reinterpret_cast<u8*>(gsgfxState) + arg0 * sizeof(LayerTevOperation);
    if (reinterpret_cast<LayerTevColorOperationCache*>(cached)->operation != arg1 || reinterpret_cast<LayerTevColorOperationCache*>(cached)->bias != arg2 || reinterpret_cast<LayerTevColorOperationCache*>(cached)->scale != arg3 || reinterpret_cast<LayerTevColorOperationCache*>(cached)->clamp != arg4 || reinterpret_cast<LayerTevColorOperationCache*>(cached)->output != arg5) {
        if (arg1 <= 1) {
            LAYER_TEV_STATE->color[arg0].fields.bias = arg2;
            LAYER_TEV_STATE->color[arg0].fields.sub = arg1;
            LAYER_TEV_STATE->color[arg0].fields.clamp = arg4;
            LAYER_TEV_STATE->color[arg0].fields.shift = arg3;
            LAYER_TEV_STATE->color[arg0].fields.dest = arg5;
        } else {
            LAYER_TEV_STATE->color[arg0].fields.bias = 3;
            LAYER_TEV_STATE->color[arg0].fields.sub = arg1;
            LAYER_TEV_STATE->color[arg0].fields.clamp = arg4;
            LAYER_TEV_STATE->color[arg0].fields.shift = (arg1 >> 1) & 3;
            LAYER_TEV_STATE->color[arg0].fields.dest = arg5;
        }
        layerField<s32>(gsgfxState, 0x1C) |= 1 << arg0;
        layerTevColorOpCache()[arg0].operation = arg1;
        layerTevColorOpCache()[arg0].bias = arg2;
        layerTevColorOpCache()[arg0].scale = arg3;
        layerTevColorOpCache()[arg0].clamp = arg4;
        layerTevColorOpCache()[arg0].output = arg5;
    }
}


__declspec(weak) void GSgfx_GCSetTevAlphaIn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *cached = reinterpret_cast<u8*>(gsgfxState) + arg0 * sizeof(LayerTevInput);
    if (reinterpret_cast<LayerTevAlphaInputCache*>(cached)->a != arg1 || reinterpret_cast<LayerTevAlphaInputCache*>(cached)->b != arg2 || reinterpret_cast<LayerTevAlphaInputCache*>(cached)->c != arg3 || reinterpret_cast<LayerTevAlphaInputCache*>(cached)->d != arg4) {
        LAYER_TEV_STATE->alpha[arg0].fields.a = arg1;
        LAYER_TEV_STATE->alpha[arg0].fields.b = arg2;
        LAYER_TEV_STATE->alpha[arg0].fields.c = arg3;
        LAYER_TEV_STATE->alpha[arg0].fields.d = arg4;
        layerField<s32>(gsgfxState, 0x20) |= 1 << arg0;
        layerTevAlphaInCache()[arg0].a = arg1;
        layerTevAlphaInCache()[arg0].b = arg2;
        layerTevAlphaInCache()[arg0].c = arg3;
        layerTevAlphaInCache()[arg0].d = arg4;
    }
}


__declspec(weak) void GSgfx_GCSetTevColorIn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *cached = reinterpret_cast<u8*>(gsgfxState) + arg0 * sizeof(LayerTevInput);
    if (reinterpret_cast<LayerTevColorInputCache*>(cached)->a != arg1 || reinterpret_cast<LayerTevColorInputCache*>(cached)->b != arg2 || reinterpret_cast<LayerTevColorInputCache*>(cached)->c != arg3 || reinterpret_cast<LayerTevColorInputCache*>(cached)->d != arg4) {
        LAYER_TEV_STATE->color[arg0].fields.a = arg1;
        LAYER_TEV_STATE->color[arg0].fields.b = arg2;
        LAYER_TEV_STATE->color[arg0].fields.c = arg3;
        LAYER_TEV_STATE->color[arg0].fields.d = arg4;
        layerField<s32>(gsgfxState, 0x1C) |= 1 << arg0;
        layerTevColorInCache()[arg0].a = arg1;
        layerTevColorInCache()[arg0].b = arg2;
        layerTevColorInCache()[arg0].c = arg3;
        layerTevColorInCache()[arg0].d = arg4;
    }
}


struct LayerTevOrderRegister { u32 address:8, reserved1:2, channel1:3, enabled1:1, coordinate1:3, texture1:3, reserved0:2, channel0:3, enabled0:1, coordinate0:3, texture0:3; };
struct LayerTevOrderRegisters { u8 reserved[0x58]; LayerTevOrderRegister order[8]; };
struct LayerTevOrderArgs { s32 coordinate, map, color; };
#define LAYER_TEV_ORDER (reinterpret_cast<LayerTevOrderRegisters*>(gsgfxState))
struct LayerTevOrderArgCache { u8 reserved[0x4cc]; LayerTevOrderArgs stage[16]; };
#define LAYER_TEV_ORDER_CACHE (reinterpret_cast<LayerTevOrderArgCache*>(gsgfxState))
#define LAYER_TEV_ORDER_ARGS (reinterpret_cast<LayerTevOrderArgs*>(reinterpret_cast<u8*>(gsgfxState) + 0x4cc))
inline void GSgfx_GCWriteTevOrder(s32 stage, s32 coord, s32 map, s32 color) {
    static u8 c2r[16] = {0, 1, 0, 1, 0, 1, 7, 5, 6, 0, 0, 0, 0, 0, 0, 7};
    s32 reg = stage >> 1;
    if (stage & 1) {
        LAYER_TEV_ORDER->order[reg].texture1 = map & 7;
        LAYER_TEV_ORDER->order[reg].coordinate1 = coord & 7;
        LAYER_TEV_ORDER->order[reg].enabled1 = map != 255 && !(map & 0x100);
        LAYER_TEV_ORDER->order[reg].channel1 = c2r[color & 15];
    } else {
        LAYER_TEV_ORDER->order[reg].texture0 = map & 7;
        LAYER_TEV_ORDER->order[reg].coordinate0 = coord & 7;
        LAYER_TEV_ORDER->order[reg].enabled0 = map != 255 && !(map & 0x100);
        LAYER_TEV_ORDER->order[reg].channel0 = c2r[color & 15];
    }
    layerField<s32>(gsgfxState, 0x4) |= 1 << reg;
    if (coord != 255) layerField<s32>(gsgfxState, 0xC) |= 1 << coord;
    LAYER_TEV_ORDER_ARGS[(u32)stage].coordinate = coord;
    LAYER_TEV_ORDER_ARGS[(u32)stage].map = map;
    LAYER_TEV_ORDER_ARGS[(u32)stage].color = color;
}
__declspec(weak) void GSgfx_GCSetTevOrder(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (LAYER_TEV_ORDER_CACHE->stage[arg0].coordinate != arg1 || LAYER_TEV_ORDER_CACHE->stage[arg0].map != arg2 || LAYER_TEV_ORDER_CACHE->stage[arg0].color != arg3)
        GSgfx_GCWriteTevOrder(arg0, arg1, arg2, arg3);
}

inline void GSgfx_GCWriteMatColor(s32 chan, LayerColor4 color) {
    s32 idx = chan - 4;
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u16 = 0;
    GXWGFifo.u16 = 0x100c + (chan & 1);
    GXWGFifo.u32 = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
    LAYER_GC_FIELD(u32, idx * 5 + 0x4c3) = *(u32*)&color;
    LAYER_MAT_CACHE[idx].dirty = 0;
}
inline void GSgfx_GCWriteAmbColor(s32 chan, LayerColor4 color) {
    s32 idx = chan - 4;
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u16 = 0;
    GXWGFifo.u16 = 0x100a + (chan & 1);
    GXWGFifo.u32 = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
    LAYER_GC_FIELD(u32, idx * 5 + 0x4b9) = *(u32*)&color;
    LAYER_AMB_CACHE[idx].dirty = 0;
}
__declspec(weak) void GSgfx_GCSetMatColor(s32 arg0, GXColor arg1) {
    s32 idx = arg0 - 4;
    if (LAYER_GC_FIELD(u32, 0x4c3 + idx * 5) != *reinterpret_cast<u32*>(&arg1) || LAYER_MAT_CACHE[idx].dirty == 1)
        GSgfx_GCWriteMatColor(arg0, *reinterpret_cast<LayerColor4*>(&arg1));
}


__declspec(weak) void GSgfx_GCSetAmbColor(s32 arg0, GXColor arg1) {
    s32 idx = arg0 - 4;
    if (LAYER_GC_FIELD(u32, 0x4b9 + idx * 5) != *reinterpret_cast<u32*>(&arg1) || LAYER_AMB_CACHE[idx].dirty == 1)
        GSgfx_GCWriteAmbColor(arg0, *reinterpret_cast<LayerColor4*>(&arg1));
}


struct LayerChanCtrlArgs { u8 enable; u8 pad[3]; s32 ambient, material, lights, diffuse, attenuation; };
struct LayerChanCtrlCache { u8 reserved[0x458]; LayerChanCtrlArgs chan[4]; };
#define LAYER_CHAN_CTRL_CACHE (reinterpret_cast<LayerChanCtrlCache*>(gsgfxState))
#define LAYER_CHAN_CTRL_ARGS (reinterpret_cast<LayerChanCtrlArgs*>(reinterpret_cast<u8*>(gsgfxState) + 0x458))
inline void GSgfx_GCWriteChanCtrl(s32 chan, u8 enable, s32 ambient, s32 material, s32 lights, s32 diffuse, s32 attenuation) {
    s32 diffuseFunction = diffuse;
    if (attenuation == 0) diffuseFunction = 0;
    GXWGFifo.u8 = 0x10; GXWGFifo.u16 = 0; GXWGFifo.u16 = 0x100e + (chan & 3);
    GXWGFifo.u32 = ((lights << 7) & 0x7800) | ((((u32)(-attenuation | attenuation) >> 21) & 0x400) |
        ((((u32)((2 - attenuation) | (attenuation - 2)) >> 22) & 0x200) |
        ((ambient << 6) | (((lights * 4) & 0x3c) | (material | ((enable * 2) & 0x1fe))) | (diffuseFunction << 7))));
    LAYER_CHAN_CTRL_ARGS[(u32)chan].enable = enable;
    LAYER_CHAN_CTRL_ARGS[(u32)chan].ambient = ambient;
    LAYER_CHAN_CTRL_ARGS[(u32)chan].material = material;
    LAYER_CHAN_CTRL_ARGS[(u32)chan].lights = lights;
    LAYER_CHAN_CTRL_ARGS[(u32)chan].diffuse = diffuse;
    LAYER_CHAN_CTRL_ARGS[(u32)chan].attenuation = attenuation;
}
__declspec(weak) void GSgfx_GCSetChanCtrl(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (LAYER_CHAN_CTRL_ARGS[arg0].enable != arg1 || LAYER_CHAN_CTRL_CACHE->chan[arg0].ambient != arg2 || LAYER_CHAN_CTRL_CACHE->chan[arg0].material != arg3 ||
        LAYER_CHAN_CTRL_CACHE->chan[arg0].lights != arg4 || LAYER_CHAN_CTRL_CACHE->chan[arg0].diffuse != arg5 || LAYER_CHAN_CTRL_CACHE->chan[arg0].attenuation != arg6)
        GSgfx_GCWriteChanCtrl(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

struct LayerScissorRegister { u32 address:8, x:12, y:12; };
#define LAYER_SC(off) (*reinterpret_cast<LayerScissorRegister*>(reinterpret_cast<u8*>(gsgfxState) + (off)))
inline void GSgfx_GCWriteScissor(u32 left, u32 top, u32 wd, u32 ht) {
    LAYER_SC(0x4C).x = left;
    LAYER_SC(0x4C).y = top;
    LAYER_SC(0x50).x = LAYER_SC(0x4C).x + wd - 1;
    LAYER_SC(0x50).y = LAYER_SC(0x4C).y + ht - 1;
    layerField<s32>(gsgfxState, 0x0) |= 0x4000;
}
__declspec(weak) void GSgfx_GCSetScissor(u16 arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5) {
    LayerScissorCache *c = reinterpret_cast<LayerScissorCache*>(gsgfxState);
    if (c->x != arg0 || c->y != arg1 || c->width != arg2 || c->height != arg3 || c->offsetX != arg4 || c->offsetY != arg5) {
        GSgfx_GCWriteScissor(arg0 + arg4 + 342, arg1 + arg5 + 342, arg2, arg3);
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->x = arg0;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->y = arg1;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->width = arg2;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->height = arg3;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->offsetX = arg4;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->offsetY = arg5;
    }
}

struct ProjArgs { u32 v[6]; };
struct ProjCache { s32 type; ProjArgs args; };
#define PROJ_CACHE (*reinterpret_cast<ProjCache*>(reinterpret_cast<u8*>(gsgfxState) + 0x41C))
__declspec(weak) void GSgfx_GCSetProjection(s32 arg0, u8 *arg1) {
    ProjArgs *p = reinterpret_cast<ProjArgs*>(arg1);
    u32 *cached;
    u32 *input;
    u8 changed;
    if (PROJ_CACHE.type != arg0) changed = 1;
    else {
        changed = 0;
        cached=PROJ_CACHE.args.v;
        input=p->v;
        for (s32 i=0;i<6;i++,cached++,input++) {
            if (*cached != *input) { changed=1; break; }
        }
    }
    if (changed == 1) {
        GXWGFifo.u8 = 0x10;
        GXWGFifo.u16 = 6;
        GXWGFifo.u16 = 0x1020;
        GXWGFifo.f32 = layerField<float>(arg1, 0x0);
        GXWGFifo.f32 = layerField<float>(arg1, 0x4);
        GXWGFifo.f32 = layerField<float>(arg1, 0x8);
        GXWGFifo.f32 = layerField<float>(arg1, 0xC);
        GXWGFifo.f32 = layerField<float>(arg1, 0x10);
        GXWGFifo.f32 = layerField<float>(arg1, 0x14);
        GXWGFifo.u32 = arg0;
        PROJ_CACHE.type = arg0;
        ProjCache *c = &PROJ_CACHE;
        c->args.v[0] = p->v[0]; c->args.v[1] = p->v[1]; c->args.v[2] = p->v[2];
        c->args.v[3] = p->v[3]; c->args.v[4] = p->v[4]; c->args.v[5] = p->v[5];
    }
}

}

#undef LAYER_STATE_FIELD
