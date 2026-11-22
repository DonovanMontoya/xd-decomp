#ifndef PARTICLE_TEXTURE_HPP
#define PARTICLE_TEXTURE_HPP

#include <global.h>

struct GStexture;

// Serialized frame offsets are relative to the start of the animation.
union ParticleTextureFrame {
    u32 address;
    void* serialized;
    GStexture* texture;
};

struct ParticleTextureAnimation {
    u32 count;
    ParticleTextureFrame frames[1];
};

extern "C" void particleEngineSetupTexture(u32 unit, GStexture* texture, s32 wrapS, s32 wrapT,
                                           s32 minFilter, s32 magFilter);

#endif
