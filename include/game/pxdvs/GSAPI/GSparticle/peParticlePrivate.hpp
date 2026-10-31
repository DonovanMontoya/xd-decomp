#ifndef PE_PARTICLE_PRIVATE_HPP
#define PE_PARTICLE_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>
struct _EmitParams {u8 data[0x48];};
struct ParticleSpline {u8 flags;u8 reserved01[3];f32 value,time;};
struct _peParticle {u32 flags;f32 sizeX,sizeY,rangeX,rangeY;ParticleSpline *widthSpline,*heightSpline;f32 offsetX,offsetY;f32 angle,angularMin,angularRange,frameDuration;ParticleSpline* angleSpline;void *colorSpline,*extraColorSpline;ParticleSpline *alphaSpline;s16 u0,v0,u1,v1;f32 yaw,roll;void* texture;};
struct peParticleNode:peNode {
    u16 index,sortIndex;u8 texture,reserved35,live,reserved37;f32 width,height,rotation,angle,angularSpeed,depth;
    void SetDisplayIndex(GSgfxDL*,u16,u16,bool);void Start(peEmitterNode*,_peParticle*,GSgfxDL*,_EmitParams*);void Render(_peParticle*,GSgfxDL*,char*);void UpdateRenderData(peEmitterNode*,_peParticle*,char*,f32);
};
struct peParticleContainer:peRenderContainer {
    peParticleNode** sorted;_peParticle* particle;f32 uv[8];
    peParticleContainer(peEmitterNode*,_peParticle*,u16);virtual ~peParticleContainer();void Start();void Stop();u16 Emit(u16);void Update(f32);void Render();void DepthSort();bool RenderForLayer();int PreviousActive(int index) {if(!sorted)return -1;while(index>0){--index;if(sorted[index]->live)return index;}return -1;}
};
extern "C" {extern _EmitParams* g_emitParams;}
extern "C" {f32 peSplineGetValue(ParticleSpline*,f32);}
#endif
