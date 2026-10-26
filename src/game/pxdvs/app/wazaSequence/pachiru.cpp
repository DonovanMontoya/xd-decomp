#include <dolphin/types.h>
struct GStexture;struct GSmodel;struct GSpart;struct GSmaterial;
struct PachiruEffect{GSmaterial*material;GStexture*texture;};
extern "C" {void DCFlushRange(void*,u32);void GSlogWrite(const char*,...);void GSmaterialSetTexture(GSmaterial*,GStexture*);GSpart*GSmodelGetPart(GSmodel*,s32);void GSpartFree(GSpart*);GSmaterial*GSpartGetMaterial(GSpart*,s32);void*GSresGetResource(u32,u32);void GStextureConvertFromHW(GStexture*);void GStextureConvertToHW(GStexture*);GStexture*GStextureCreate(u16,u16,s32,s32,s32);void GStextureFree(GStexture*);s32 GStextureGetFormat(GStexture*);s32 GStextureGetMiplevels(GStexture*);s32 GStextureGetTlutFormat(GStexture*);s16 GStextureGetXsize(GStexture*);s16 GStextureGetYsize(GStexture*);void*GStextureLockImage(GStexture*,s32);void GStextureUnlockImage(GStexture*);void*memcpy(void*,const void*,u32);}
static u8 gPachiruCoords[4][2]={{6,7},{91,6},{30,65},{68,65}};
static GStexture*_pachiruEffectCreateTexture(GStexture*,GStexture*,unsigned long);
extern "C" void pachiruEffectFree(PachiruEffect*effect){effect->material=0;if(effect->texture){GStextureFree(effect->texture);effect->texture=0;}}
extern "C" u8 pachiruEffectCreate(PachiruEffect*effect,GSmodel*model,u32 seed){u8 success=0;if(!model)return 0;GSpart*part=GSmodelGetPart(model,2);if(!part)return 0;effect->material=0;effect->texture=0;effect->material=GSpartGetMaterial(part,0);if(effect->material){GStexture*base=(GStexture*)GSresGetResource(903,0xF7D1200);if(base){GStexture*patch=(GStexture*)GSresGetResource(903,0xF7E1200);if(patch){effect->texture=_pachiruEffectCreateTexture(base,patch,seed);if(effect->texture){GSmaterialSetTexture(effect->material,effect->texture);success=1;}}}}if(!success){if(effect->texture){GStextureFree(effect->texture);effect->texture=0;}effect->material=0;}GSpartFree(part);return success;}
static GStexture* _pachiruEffectCreateTexture(GStexture* base, GStexture* patch, unsigned long seed) {
    u16* source;
    s32 width, height, levels, tlut;
    GStexture* texture;
    u16* image;
    s32 pixels, bytes, patchWidth, patchHeight;
    u16* last;
    u8* coord;
    s16 i, dy, dx, y, origin, offset, x;
    s32 pixel;
    s32 row;
    u16* destination;
    u16* input;
    u16 color;
    source = 0;
    width = GStextureGetXsize(base);
    height = GStextureGetYsize(base);
    levels = GStextureGetMiplevels(base);
    tlut = GStextureGetTlutFormat(base);
    texture = GStextureCreate(width, height, GStextureGetFormat(base), tlut, levels);
    image = (u16*)GStextureLockImage(texture, 0);
    if (image) {
        source = (u16*)GStextureLockImage(base, 0);
        if (source) {
            pixels = width * height;
            bytes = pixels * 2;
            memcpy(image, source, bytes);
            DCFlushRange(image, bytes);
            GStextureUnlockImage(base);
            GStextureConvertFromHW(texture);
            GStextureConvertFromHW(patch);
            source = (u16*)GStextureLockImage(patch, 0);
            if (source) {
                patchWidth = GStextureGetXsize(patch);
                patchHeight = GStextureGetYsize(patch);
                if (patchWidth <= (width >> 2) && patchHeight <= (height >> 2)) {
                    last = image + (pixels - 1);
                    coord = &gPachiruCoords[0][0];
                    for (i = 0; i < 4; coord += 2, i++) {
                        pixel = 0;
                        dy = (s16)((seed >> 4) & 15) - 8;
                        dx = (seed & 15) - 8;
                        row = 0;
                        seed >>= 8;
                        origin = (s32)(3.4f * dx) + coord[0] + (((s32)(3.4f * dy) + coord[1]) * width);
                        for (y = 0; y < patchHeight; pixel += patchWidth, row += width, y++) {
                            offset = origin + row;
                            if (offset >= 0) {
                                destination = image + offset;
                                if (destination <= last) {
                                    input = source + (s16)pixel;
                                    for (x = 0; x < patchWidth; x++, destination++, input++) {
                                        if (destination <= last) {
                                            color = *input;
                                            if (color > *destination) *destination = color;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    GStextureUnlockImage(texture);
                    GStextureUnlockImage(patch);
                    GStextureConvertToHW(patch);
                    GStextureConvertToHW(texture);
                    return texture;
                }
            }
        }
    }
    GSlogWrite("Failed to create Patchiru texture\n");
    if (image) GStextureUnlockImage(texture);
    if (source) GStextureUnlockImage(patch);
    if (texture) GStextureFree(texture);
    return 0;
}
