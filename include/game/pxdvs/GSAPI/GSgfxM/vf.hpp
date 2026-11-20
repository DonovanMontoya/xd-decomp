#ifndef GAME_PXDVS_GSAPI_GSGFXM_VF_HPP
#define GAME_PXDVS_GSAPI_GSGFXM_VF_HPP

#include <dolphin/types.h>

struct VFFormat;

extern "C" {
VFFormat* GSgfxVFBuildTemp(s32 positionCount, s32 positionComponent, u8 normal, s32 normalCount,
                           u8 colors, s32 colorComponent, u8 textures, s32 textureCount, s32 textureComponent);
void GSgfxSetupRenderAndSelect(void* format);
}

#endif
