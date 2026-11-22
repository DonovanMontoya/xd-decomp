#ifndef PE_RESOURCE_DATA_HPP
#define PE_RESOURCE_DATA_HPP

#include <dolphin/mtx.h>
#include <game/pxdvs/GSAPI/GSparticle/particleTexture.hpp>
#include <game/pxdvs/GSAPI/GSparticle/peSplinePrivate.hpp>

class GSgfxLight;
struct HSD_JObj;

// Bank conversion replaces each signed resource ID with the resolved resource.
struct _peParticle {
    u32 flags;
    f32 sizeX, sizeY, rangeX, rangeY;
    PeSpline *widthSpline, *heightSpline;
    f32 offsetX, offsetY, angle, angularMin, angularRange, frameDuration;
    PeSpline* angleSpline;
    PeColorSpline *colorSpline, *extraColorSpline;
    PeSpline* alphaSpline;
    union {
        f32 textureCoordinates[4];
        struct {
            s16 u0, v0, u1, v1;
            f32 yaw, roll;
        } converted;
    };
    union { s32 textureId; GStexture* texture; ParticleTextureAnimation* textureAnimation; };
};

struct _peParticleStrip {
    u32 flags;
    f32 frameRate;
    PeColorSpline *colorSpline, *secondColorSpline;
    PeSpline* alphaSpline;
    f32 v0, v1;
    union { s32 textureId; GStexture* texture; ParticleTextureAnimation* textureAnimation; };
    Vec direction;
    f32 speedMin, speedRange;
};

struct _peDistortion {
    u32 flags;
    f32 width, height, widthRange, heightRange;
    PeSpline *widthSpline, *heightSpline;
    f32 offsetX, offsetY, angle, angularMin, angularRange;
    PeSpline *angleSpline, *alphaSpline;
    u8 reserved38[0x18];
    f32 u0, v0, u1, v1;
    union { s32 textureId; GStexture* texture; };
};

struct _peModel {
    u32 flags;
    Vec rotation, angularSpeed, scale, scaleRange;
    PeSpline *rotationSpline[3], *scaleSpline[3];
    union { s32 id; HSD_JObj* jobj; u32 primitive; } resource;
    f32 duration, field54;
};

struct _peShape {
    u32 flags;
    Vec rotation, angularSpeed, scale, scaleRange;
    PeSpline *rotationSpline[3], *scaleSpline[3];
    PeColorSpline* colorSpline;
    PeSpline* alphaSpline;
    f32 radius;
    u8 segments0, segments1;
    u16 reserved5a;
    Vec position;
    GSgfxColAu8 ambient, lightColor;
    f32 shininess;
    union { s32 textureId; GStexture* texture; };
    GSgfxLight *light0, *light1;
};

#endif
