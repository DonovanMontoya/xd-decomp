#ifndef PE_EMITTER_PRIVATE_HPP
#define PE_EMITTER_PRIVATE_HPP
#include <global.h>
#include <game/pxdvs/GSAPI/GSparticle/peEmitterData.hpp>
#include <libc/stddef.h>
struct peEmitterNode;
struct GSvec;
struct _EmitParams { f32 time, fraction; u8 reserved[0x40]; _EmitParams() { time = 0.0f; fraction = 0.0f; } };
struct peContainer;

struct peContainer {
    peEmitterNode* owner; peContainer* next; u32 reserved08; peEmitterNode* freeNodes; peEmitterNode* nodes;
    u16 count; u8 reserved16[3]; u8 active; u8 reserved1a[2];
    peContainer(peEmitterNode*, u32, u16);
    virtual ~peContainer();
    virtual void Start(); virtual void PreUpdate(); virtual u16 Emit(u16); virtual void Update(f32); virtual void Render(); virtual void Stop();
};
struct EmitterTransforms { Vec position; Quaternion rotation; Vec scale; };
struct peEmitterNode {
    f32 time; f32 life; Vec basePosition; u8 reserved14[0xc]; void* transformParent; u32 reserved24; peEmitterNode* next; peEmitterNode* previous;
    f32 lastLoop; f32 field34; u8 reserved38[0xc]; f32 field44; u16 flags, count; Vec spin; Vec scale; Quaternion localRotation; Vec offset; Quaternion orientation; Vec randomOffset; u8 reserved9c[0xc]; EmitterTransforms world, previousWorld; f32 depth;
    _peEmitter* emitter; peContainer* containers;
    static void GetPositionParameter(GSvec*,GSvec*,_pePositionFunction*,f32);
    void CreateParameters(u16, f32);
    void Init(_peEmitter*); void Stop(_peEmitter*); void Render(_peEmitter*); void Release(); void SetLastLoop(); void CreateWorldParams();
    bool Update(peEmitterNode*, _peEmitter*, f32); void Start(peEmitterNode*, _peEmitter*, _EmitParams*);
};
struct peEmitterContainer : peContainer {
    _peEmitter* emitter;
    peEmitterContainer(peEmitterNode*, _peEmitter*, u16);
    virtual ~peEmitterContainer();
    void Stop(); void Render(); bool DoRender(); void Update(f32); u16 Emit(u16); void PreUpdate();
};
struct ParticleLayer { u8 reserved00[0x28]; s32 kind; };
extern "C" {
extern ParticleLayer* g_current_layer;
extern s32 g_render_pass;
extern _EmitParams* g_emitParams;
void RemoveAll__11peContainerFv(peContainer*);
u16 CreateNodes__11peContainerFUs(peContainer*,u16);
void RemoveNode__11peContainerFP6peNode(peContainer*, peEmitterNode*);
void MoveNode__11peContainerFP6peNodeP6peNode(peContainer*, peEmitterNode*, peEmitterNode*);
}
typedef char EmitterNodeSizeCheck[sizeof(peEmitterNode) == 0x104 ? 1 : -1];
typedef char EmitterNodeWorldOffsetCheck[offsetof(peEmitterNode, world) == 0xa8 ? 1 : -1];
typedef char EmitterContainerSizeCheck[sizeof(peEmitterContainer) == 0x24 ? 1 : -1];
#endif
