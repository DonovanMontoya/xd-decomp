#ifndef GAME_PXDVS_GSAPI_GSGFXM_VF_PRIVATE_HPP
#define GAME_PXDVS_GSAPI_GSGFXM_VF_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSgfxM/vf.hpp>
#include <dolphin/types.h>
#include <libc/stddef.h>
struct VFAttribute { s32 attribute, count, component; u8 fraction; u8 padding[3]; };
struct VFDescriptor { s32 attribute, type; };
struct VFArray { u16 flags; u8 stride, padding; s32 attribute; void *data; u32 size; };
struct GSgfxVF { u16 flags; u8 colors, textures; u32 index; VFAttribute formats[27]; VFDescriptor descriptors[27]; VFArray arrays[27]; };
struct VFLayer { VFLayer *next; };
typedef char VFFormatSizeCheck[sizeof(GSgfxVF) == 0x440 ? 1 : -1];
typedef char VFArrayOffsetCheck[offsetof(GSgfxVF, arrays) == 0x290 ? 1 : -1];
typedef char VFDescriptorsOffsetCheck[offsetof(GSgfxVF, descriptors) == 0x1b8 ? 1 : -1];

extern "C" {
void GSgfxVFInit(GSgfxVF *format);
void GSgfxVFCreate(GSgfxVF *format);
void GSgfxVFSetElement(GSgfxVF *format, s32 attribute, s32 count, s32 component, u8 fraction);
}

#endif
