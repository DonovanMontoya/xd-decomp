#ifndef PE_DISTORTION_PRIVATE_HPP
#define PE_DISTORTION_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peShapePrivate.hpp>
struct peDistortionNode:peNode {u16 index,flags;f32 width,height,rotation,angle,angularSpeed;void UpdateRenderData(peEmitterNode*,_peDistortion*,char*,f32);};
struct peDistortionContainer:peRenderContainer {
 _peDistortion *definition;f32 uv[8];
 peDistortionContainer(peEmitterNode*,_peDistortion*,u16);virtual ~peDistortionContainer();
 void Start();void Stop();void Render();void Update(f32);u16 Emit(u16);
};
typedef char DistNodeSize[sizeof(peDistortionNode)==0x48?1:-1];
typedef char DistContainerSize[sizeof(peDistortionContainer)==0x78?1:-1];
extern "C" {extern GSgfxVF g_vertex_format;extern Vec g_CameraUpDir,g_CameraSideDir,xAxisVector,yAxisVector;
 void GSgfxVFSetArray(GSgfxVF*,s32,s32,void*,u8,u32);void particleEngineSetupTevStages(u8,bool,bool);
 void dlDraw__10GSgfxLayerFP7GSgfxDL(GSgfxLayer*,GSgfxDL*);void GSboundAddPoint(void*,f32,f32,f32);
}
#endif
