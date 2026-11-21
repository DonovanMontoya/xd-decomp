#ifndef PE_EMITTER_DATA_HPP
#define PE_EMITTER_DATA_HPP

#include <dolphin/mtx.h>
#include <libc/stddef.h>

struct PeSpline;
struct PeColorSpline;
struct _peEmitter;

struct _pePositionFunction {
    u16 flags, pad;
    Vec origin, range, axis, direction;
    f32 radius, radiusRange, rate;
};

struct _particleData {
    u32 flags;
    s32 kind;
    union {
        void* data;
        _peEmitter* emitter;
    };
    _particleData* next;
};

struct _peEmitter {
    u32 flags;
    u32 flags2;
    f32 emissionTimeStep;
    f32 rate;
    f32 rateRange;
    PeSpline* rateSpline;
    f32 startTime;
    f32 endTime;
    f32 particleLife, particleLifeRange;
    f32 duration;
    f32 forceFactor, forceFactorRange;
    _pePositionFunction positionFunction;
    u16 velocityFlags;
    u8 reserved76[2];
    union {
        Vec direction;
        struct {
            f32 speed, range;
        } alongNormal;
    } velocity;
    Vec rotationAxis;
    f32 speed, speedRange;
    f32 angle, angleRange;
    f32 friction;
    f32 bounce;
    f32 attraction;
    Vec force;
    PeSpline* forceSpline[3];
    Vec offset;
    PeSpline* offsetSpline[3];
    Vec euler;
    PeSpline* eulerSpline[3];
    Vec angularVelocity;
    Vec angularVelocityRange;
    PeSpline* angularVelocitySpline[3];
    Vec scale;
    PeSpline* scaleSpline[3];
    PeColorSpline* colorSpline;
    PeSpline* alphaSpline;
    _particleData* resources;
};

typedef char ParticleDataSizeCheck[sizeof(_particleData) == 0x10 ? 1 : -1];
typedef char EmitterResourcesOffsetCheck[offsetof(_peEmitter, resources) == 0x138 ? 1 : -1];

#endif
