#ifndef GSCOLSYS2_HUMAN_PRIVATE_HPP
#define GSCOLSYS2_HUMAN_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GScolsys/GScolsys2Walk.hpp>
#include <game/pxdvs/GSAPI/GSgfxM/vf.hpp>
#include <dolphin/mtx.h>
#include <game/pxdvs/GSAPI/GScolsys/GScolsys2State.hpp>
struct GSvec { f32 x,y,z; };
struct tagPeopleWork { u8 isHero() const; u8 isFollower() const; };
extern "C" {
u32 peopleGetHumanID(s32,u32);
tagPeopleWork *peopleSearchID(u32);
GSvec *peopleBiosGetPosPtr(tagPeopleWork *);
void peopleGetPos(s32,u32,GSvec *);
f32 peopleGetTalkDistance(s32,u32);
u8 gimmickBoxFixDistanceForPushBox(f32 *,tagPeopleWork *,f32,f32);
u8 gimmickBoxIsBox(tagPeopleWork *);
void heroMoveGetHeroPos(GSvec *);
tagPeopleWork *heroGetFollower();
void GSgfxLayerSetActive(s32);
void GScameraLoadActiveCameraMatrix(s32);
void GSgfxCullMode(s32);
void GSgfxBlendMode(s32,s32,s32);
void GSgfxPixelMode(s32,s32,s32);
void GSgfxSetLineWidth(f32);
void GSgfxSetPrimitiveType(s32);
void GSgfxBeginSurface(s32);
void GSgfxVertex3f(f32,f32,f32);
void GSgfxColor4u8(u8,u8,u8,u8);
void GSgfxEndSurface();
f64 sin(f64); f64 cos(f64);
extern f32 __float_nan[];
}
#endif
