#ifndef GSCOLSYS2_DRAW_PRIVATE_HPP
#define GSCOLSYS2_DRAW_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <dolphin/gx.h>
#include <game/pxdvs/GSAPI/GScolsys/GScolsys2State.hpp>
#include <game/pxdvs/GSAPI/GSgfxM/dlPrivate.hpp>
struct GSmtx { Mtx m; };
struct DrawPolygon { Vec vertices[3],normal; u8 attribute,flags; u16 id; };
struct DrawSunPolygon { Vec vertices[3],normal; };
struct CCD_HITMDL_HEAD { DrawPolygon *polygons; u32 count; u8 grid[32]; };
struct CCD_WALKMDL_HEAD { DrawPolygon *polygons; u32 count; u8 grid[32]; };
struct DrawSunModel { DrawSunPolygon *polygons; u32 count; };
struct DrawObject {
 f32 position[3],rotation[3],scale[3];
 CCD_WALKMDL_HEAD *walk;
 CCD_HITMDL_HEAD *hit,*thru,*check,*npc;
 DrawSunModel *sun;
 u16 flags,padding;
};
struct DrawFile { DrawObject *objects; u32 count; };
typedef char DrawSunPolygonSize[sizeof(DrawSunPolygon)==48?1:-1];
typedef char DrawObjectFlags[offsetof(DrawObject,flags)==0x3c?1:-1];
typedef char DrawObjectWalk[offsetof(DrawObject,walk)==0x24?1:-1];
typedef char DrawObjectSize[sizeof(DrawObject)==64?1:-1];
typedef char DrawPolygonSize[sizeof(DrawPolygon)==52?1:-1];
extern "C" {
DrawFile *GScolsys2GetCCDFileHead();
s32 GScolsys2GetObjMatrix(Mtx,u32);
s32 GScolsys2GetObjRotMatrix(Mtx,u32);
void GSgfxDLPrimitiveType(s32);
void GSgfxDLBeginSurface(u16);
void GSgfxDLEndSurface();
void GSgfxDLBegin(DLDisplayList *,void *,u16,u16);
void GSgfxDLEnd();
void GSgfxDLDraw(DLDisplayList *);
void GSgfxSetupRenderAndSelect(void *);
void GSgfxLayerSetActive(s32);
void GScameraLoadActiveCameraMatrix(s32);
void GSgfxCullMode(s32);
void GSgfxBlendMode(s32,s32,s32);
void GSgfxZCompare(s32,s32);
void GSgfxPixelMode(s32,s32,s32);
u32 GSinputButtonsPressed(s32);
void floorMapSetDisp(s32);
void GScolsys2HumanDispColision();
}
#endif
