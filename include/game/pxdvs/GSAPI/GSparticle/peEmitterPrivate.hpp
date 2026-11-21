#ifndef PE_EMITTER_PRIVATE_HPP
#define PE_EMITTER_PRIVATE_HPP
#include <global.h>
#include <game/pxdvs/GSAPI/GSparticle/peEmitterData.hpp>
#include <libc/stddef.h>
#include <game/pxdvs/GSAPI/GSparticle/peNode.hpp>

struct peContainer {
    peEmitterNode* owner; peContainer* next; u8* memory; peNode* freeNodes; peNode* nodes;
    u16 count, capacity; u8 dirty, active; u8 reserved1a[2];
    peContainer(peEmitterNode*, u32, u16);
    void RemoveAll(); void RemoveNode(peNode*); void MoveNode(peNode*, peNode*); u16 CreateNodes(u16);
    virtual ~peContainer();
    virtual void Start(); virtual void PreUpdate(); virtual u16 Emit(u16); virtual void Update(f32); virtual void Render(); virtual void Stop();
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
}
typedef char EmitterNodeSizeCheck[sizeof(peEmitterNode) == 0x104 ? 1 : -1];
typedef char EmitterNodeWorldOffsetCheck[offsetof(peEmitterNode, world) == 0xa8 ? 1 : -1];
typedef char EmitterContainerSizeCheck[sizeof(peEmitterContainer) == 0x24 ? 1 : -1];
#endif
