#ifndef PE_SHAPE_PRIVATE_HPP
#define PE_SHAPE_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>
#include <game/pxdvs/GSAPI/GSgfxM/light_gfxmPrivate.hpp>
#include <game/pxdvs/GSAPI/GSparticle/peResourceData.hpp>
struct peShapeNode:peNode {NodeTransform world;Quaternion randomRotation,localRotation;Vec baseScale;f32 depth;u32 flips;Vec angularSpeed;GSgfxColAu8 color;bool Update(peEmitterNode*,_peShape*,f32);void Start(peEmitterNode*,_peShape*,_EmitParams*);void Render(_peShape*);};
struct peShapeContainer:peContainer {
    _peShape* shape;
    peShapeContainer(peEmitterNode*,_peShape*,u16);virtual ~peShapeContainer();void Start();void Stop();void Update(f32);u16 Emit(u16);void Render();
};
extern "C" {extern _EmitParams* g_emitParams;extern void* g_currentBound;void GSboundAlwaysInView(void*,s32);}
struct ParticleLayerState {
u8 reserved0[0x28];
u32 unk28;
u8 reserved2c[0x30];
u32 unk5C;
u32 unk60;
u32 unk64;
u8 reserved68[0xd24];
u32 unkD8C;
u8 reservedd90[0x4];
u8 unkD94;
u8 reservedd95[0x3];
GSgfxLight* lights[8];
u8 unkDB8;
u8 reserveddb9[0xe3];
u32 unkE9C,unkEA0,unkEA4,unkEA8;
u8 unkEAC;
u8 reservedead[0x3];
u32 unkEB0;
u32 unkEB4;
u32 unkEB8;
u32 unkEBC;
u32 unkEC0;
u32 unkEC4;
u8 reservedEC8[0x14f4 - 0xec8];
u32 unk14F4;
u8 reserved14f8[0xc];
u32 unk1504;
u8 reserved1508[0x3c];
u32 unk1544;
u8 reserved1548[0x160];
u32 unk16A8;
u8 reserved16ac[0xc];
u32 unk16B8;
u32 unk16BC;
u8 reserved16c0[4];
u32 unk16C4,unk16C8;
u32 unk16CC;
u32 unk16D0;
u8 reserved16D4[0x16f8 - 0x16d4];
u32 unk16F8;
u32 unk16FC;
u32 unk1700;
u8 reserved1704[0x5c];
u32 unk1760;
u8 reserved1764[0xc];
u32 unk1770;
u32 unk1774;
u8 reserved1778[4];
u32 unk177C,unk1780;
u32 unk1784;
u32 unk1788;
u8 reserved178C[0x17b0 - 0x178c];
u32 unk17B0;
u32 unk17B4;
u32 unk17B8;
u8 reserved17bc[0x1d8];
u32 unk1994;
u8 reserved1998[0x4];
GSgfxVF* unk199C;
void* unk19A0;
};
extern "C" {extern s32 g_render_pass;extern MtxPtr g_CameraMatrix;
void particleEngineSetupTexture(u8,void*,s32,s32,s32,s32);void particleEngineSetupBlendMode(u32);void particleEngineSetDefaultRenderState(u8);GSgfxVF* GSgfxVFGetPredef(u32);
void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(GSgfxLayer*,u8,u32,u32,u32,u32,GSgfxLight**,u32,u32);
}
extern "C" {f32 HSD_Randf();s32 EulerToQuat(Vec*,Quaternion*);extern Vec unitScaleVector;}
extern "C" {
void pushMult__16GSgfxMatrixStackFP5GSmtx(void*,Mtx);void pop__16GSgfxMatrixStackFv(void*);
void drawCube__10GSgfxLayerFv(GSgfxLayer*);void drawCylinder__10GSgfxLayerFUc(GSgfxLayer*,u8);void drawDodecaedron__10GSgfxLayerFv(GSgfxLayer*);void drawIcosahedron__10GSgfxLayerFv(GSgfxLayer*);void drawOctahedron__10GSgfxLayerFv(GSgfxLayer*);void drawTorus__10GSgfxLayerFfUcUc(GSgfxLayer*,f32,u8,u8);void drawSphere__10GSgfxLayerFUc(GSgfxLayer*,u8);void drawSphere__10GSgfxLayerFUcUc(GSgfxLayer*,u8,u8);
}
extern "C" {extern Vec g_CameraPosition,g_CameraLookDir;double atan2(double,double);}
#endif
