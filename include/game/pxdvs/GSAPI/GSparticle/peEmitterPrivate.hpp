#ifndef PE_EMITTER_PRIVATE_HPP
#define PE_EMITTER_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>

struct peEmitterContainer : peContainer {
    _peEmitter* emitter;
    peEmitterContainer(peEmitterNode*, _peEmitter*, u16);
    virtual ~peEmitterContainer();
    void Stop(); void Render(); bool DoRender(); void Update(f32); u16 Emit(u16); void PreUpdate();
};
extern "C" {
extern s32 g_render_pass;
extern _EmitParams* g_emitParams;
}
typedef char EmitterNodeSizeCheck[sizeof(peEmitterNode) == 0x104 ? 1 : -1];
typedef char EmitterNodeWorldOffsetCheck[offsetof(peEmitterNode, world) == 0xa8 ? 1 : -1];
typedef char EmitterContainerSizeCheck[sizeof(peEmitterContainer) == 0x24 ? 1 : -1];
#endif
