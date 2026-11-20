#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
#include <game/pxdvs/GSAPI/GSres/GSres.hpp>
#include <dolphin/os/OSCache.h>
#include <libc/string.h>

struct GSmaterial;
struct GSmodel;
struct GSpart;

struct PachiruEffect {
    GSmaterial* material;
    GStexture* texture;
};

extern "C" {
GSpart* GSmodelGetPart(GSmodel* model, s32 index);
GSmaterial* GSpartGetMaterial(GSpart* part, s32 index);
void GSmaterialSetTexture(GSmaterial* material, GStexture* texture);
void GSpartFree(GSpart* part);
void GSlogWrite(const char* fmt, ...);
}

static u8 gPachiruCoords[4][2] = { { 0x06, 0x07 }, { 0x5B, 0x06 }, { 0x1E, 0x41 }, { 0x44, 0x41 } };

static GStexture* _pachiruEffectCreateTexture(GStexture* base, GStexture* spot, u32 seed);

extern "C" {

void pachiruEffectFree(PachiruEffect* effect) {
    effect->material = 0;
    if (effect->texture != 0) {
        GStextureFree(effect->texture);
        effect->texture = 0;
    }
}

u8 pachiruEffectCreate(PachiruEffect* effect, GSmodel* model, u32 seed) {
    u8 ok = 0;
    GSpart* part;
    GStexture* base;
    GStexture* spot;

    if (model == 0) {
        return false;
    }
    part = GSmodelGetPart(model, 2);
    if (part == 0) {
        return false;
    }
    effect->material = 0;
    effect->texture = 0;
    effect->material = GSpartGetMaterial(part, 0);
    if (effect->material != 0) {
        base = (GStexture*)GSresGetResource(0x387, 0x0F7D1200);
        if (base != 0) {
            spot = (GStexture*)GSresGetResource(0x387, 0x0F7E1200);
            if (spot != 0) {
                effect->texture = _pachiruEffectCreateTexture(base, spot, seed);
                if (effect->texture != 0) {
                    GSmaterialSetTexture(effect->material, effect->texture);
                    ok = 1;
                }
            }
        }
    }
    if (!ok) {
        if (effect->texture != 0) {
            GStextureFree(effect->texture);
            effect->texture = 0;
        }
        effect->material = 0;
    }
    GSpartFree(part);
    return ok;
}

}

static GStexture* _pachiruEffectCreateTexture(GStexture* base, GStexture* spotTex, u32 seed) {
    u16* output;
    u16* source;
    GStexture* texture;
    u16* outputPixels;
    u16* sourcePixels;
    u16* lastOutputPixel;
    s16 baseWidth;
    s16 baseHeight;
    s16 spotWidth;
    s16 spotHeight;
    s32 pixelCount;
    s32 size;
    s16 column;
    s16 row;
    s16 spot;
    s32 startPixel;
    s32 x;
    s32 y;
    s16 outputIndex;
    s16 sourceIndex;

    sourcePixels = 0;
    baseWidth = GStextureGetXsize(base);
    baseHeight = GStextureGetYsize(base);
    texture = GStextureCreate(baseWidth, baseHeight, GStextureGetFormat(base), GStextureGetTlutFormat(base),
                              GStextureGetMiplevels(base));
    outputPixels = (u16*)GStextureLockImage(texture, 0);
    if (outputPixels == 0) {
        goto fail;
    }
    sourcePixels = (u16*)GStextureLockImage(base, 0);
    if (sourcePixels == 0) {
        goto fail;
    }

    pixelCount = baseWidth * baseHeight;
    size = pixelCount * 2;
    memcpy(outputPixels, sourcePixels, size);
    DCFlushRange(outputPixels, size);
    GStextureUnlockImage(base);

    GStextureConvertFromHW(texture);
    GStextureConvertFromHW(spotTex);
    sourcePixels = (u16*)GStextureLockImage(spotTex, 0);
    if (sourcePixels == 0) {
        goto fail;
    }

    spotWidth = GStextureGetXsize(spotTex);
    spotHeight = GStextureGetYsize(spotTex);
    if (spotWidth > (baseWidth >> 2) || spotHeight > (baseHeight >> 2)) {
        goto fail;
    }

    lastOutputPixel = outputPixels + (pixelCount - 1);
    for (spot = 0; spot < 4; spot++) {
        x = (s32)(3.4f * (s16)((s16)(seed & 0xF) - 8));
        y = (s32)(3.4f * (s16)((s16)((seed >> 4) & 0xF) - 8));
        seed >>= 8;
        y += gPachiruCoords[spot][1];
        x += gPachiruCoords[spot][0];
        startPixel = (s16)(x + y * baseWidth);
        for (row = 0; row < spotHeight; row++) {
            sourceIndex = row * spotWidth;
            outputIndex = startPixel + row * baseWidth;
            if (outputIndex >= 0) {
                output = outputPixels + outputIndex;
                if (output <= lastOutputPixel) {
                    source = sourcePixels + sourceIndex;
                    for (column = 0; column < spotWidth;) {
                        if (output <= lastOutputPixel && *source > *output) {
                            *output = *source;
                        }
                        column++;
                        output++;
                        source++;
                    }
                }
            }
        }
    }

    GStextureUnlockImage(texture);
    GStextureUnlockImage(spotTex);
    GStextureConvertToHW(spotTex);
    GStextureConvertToHW(texture);
    return texture;

fail:
    GSlogWrite("Failed to create Patchiru texture\n");
    if (outputPixels != 0) {
        GStextureUnlockImage(texture);
    }
    if (sourcePixels != 0) {
        GStextureUnlockImage(spotTex);
    }
    if (texture != 0) {
        GStextureFree(texture);
    }
    return 0;
}
