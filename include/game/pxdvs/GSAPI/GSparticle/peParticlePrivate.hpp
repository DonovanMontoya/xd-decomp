#ifndef PE_PARTICLE_PRIVATE_HPP
#define PE_PARTICLE_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>
#include <game/pxdvs/GSAPI/GSparticle/peResourceData.hpp>
struct peParticleNode:peNode {
    u16 index,sortIndex;u8 texture,reserved35,live,reserved37;f32 width,height,rotation,angle,angularSpeed,depth;
    void SetDisplayIndex(GSgfxDL*,u16,u16,bool);void Start(peEmitterNode*,_peParticle*,GSgfxDL*,_EmitParams*);void Render(_peParticle*,GSgfxDL*,char*);void UpdateRenderData(peEmitterNode*,_peParticle*,char*,f32);
};
struct peParticleContainer:peRenderContainer {
    peParticleNode** sorted;_peParticle* particle;f32 uv[8];
    peParticleContainer(peEmitterNode*,_peParticle*,u16);virtual ~peParticleContainer();void Start();void Stop();u16 Emit(u16);void Update(f32);void Render();void DepthSort();bool RenderForLayer();int PreviousActive(int index) {if(!sorted)return -1;while(index>0){--index;if(sorted[index]->live)return index;}return -1;}
};
extern "C" {extern _EmitParams* g_emitParams;}
#endif
