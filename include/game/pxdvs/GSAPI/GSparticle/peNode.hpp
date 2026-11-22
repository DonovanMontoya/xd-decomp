#ifndef PE_NODE_HPP
#define PE_NODE_HPP

#include <dolphin/mtx.h>

struct peEmitterNode;
struct peContainer;
struct _peEmitter;
struct _pePositionFunction;
struct GSvec;

struct NodeTransform {
    Vec position;
    Quaternion rotation;
    Vec scale;
};

struct _EmitParams {
    f32 life;
    f32 forceFactor;
    Vec position;
    Vec velocity;
    NodeTransform transform;

    _EmitParams() : life(0.0f), forceFactor(0.0f) {}
};

struct peNode {
    f32 life;
    f32 time;
    Vec position;
    Vec velocity;
    NodeTransform* transform;
    f32 forceFactor;
    peNode* next;
    peNode* previous;

    void Start(peEmitterNode*, _EmitParams*);
    u8 Update(peEmitterNode*, f32);
};

struct peEmitterNode : peNode {
    f32 lastLoop;
    f32 emissionRemainder;
    f32 color[4];
    u16 flags, count;
    Vec spin;
    Vec scale;
    Quaternion localRotation;
    Vec offset;
    Quaternion orientation;
    Vec randomOffset;
    Vec force;
    NodeTransform world, previousWorld;
    f32 depth;
    _peEmitter* emitter;
    peContainer* containers;

    static void GetPositionParameter(GSvec*, GSvec*, _pePositionFunction*, f32);
    void CreateParameters(u16, f32);
    void Init(_peEmitter*);
    void Stop(_peEmitter*);
    void Render(_peEmitter*);
    void Release();
    void SetLastLoop();
    void CreateWorldParams();
    bool Update(peEmitterNode*, _peEmitter*, f32);
    void Start(peEmitterNode*, _peEmitter*, _EmitParams*);
};

extern "C" void peNodeTransformsConcat(NodeTransform* out, NodeTransform* parent,
                                       NodeTransform* local, bool billboard);

#endif
