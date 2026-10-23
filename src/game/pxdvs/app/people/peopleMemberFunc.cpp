#include <game/pxdvs/app/people/runtime.hpp>
extern "C" {
u8 GSmodelIsNullAnimation(void *,s32);
void GSmodelSetAnimType(void *,GSmodelAnimType);
void GSmodelSetAnimFrame(void *,f32);
void GSmodelSetAnimBlend(void *,s32,s32);
void GSmodelSetAnimIndex(void *,s32);
void GSmodelSetAnimRate(void *,f32);
u8 GSmodelHasAnimationEnded(void *);
u8 peopleBiosCheckFlag(const tagPeopleWork *,unsigned long);
f32 peopleViewerGetPlaySpeedRate(tagPeopleWork *);
void GSmodelGetAnimIndex(void *,s32 *,s32 *);
}
u8 tagPeopleWork::getMoveType(){return moveType;}
s32 tagPeopleWork::getRunMotion(){if(motions.run>=0){s32 a=motions.run;if(!GSmodelIsNullAnimation(model,a))return a;}s32 b=motions.walk;if(b>=0 && !GSmodelIsNullAnimation(model,b))return b;return 3;}
s32 tagPeopleWork::getWalkMotion(){if(motions.walk>=0){s32 a=motions.walk;if(!GSmodelIsNullAnimation(model,a))return a;}s32 b=motions.run;if(b>=0 && !GSmodelIsNullAnimation(model,b))return b;return 3;}
void tagPeopleWork::setAnimType(GSmodelAnimType type){if(model)GSmodelSetAnimType(model,type);}
void tagPeopleWork::setAnimFrame(f32 frame){if(model){if(frame<0.0f)frame=0.0f;GSmodelSetAnimFrame(model,frame);}}
#pragma opt_common_subs off
void tagPeopleWork::setAnimBlend(int a,int b){if(model && !GSmodelIsNullAnimation(model,a)){if(GSmodelIsNullAnimation(model,b))setAnimIndex(a);else GSmodelSetAnimBlend(model,a,b);}}
#pragma opt_common_subs reset
void tagPeopleWork::setAnimIndex(int i){if(model)GSmodelSetAnimIndex(model,i);}
void tagPeopleWork::setAnimRate(f32 rate,bool viewer){if(model && !checkFlags(0x8000)){if(viewer)rate*=peopleViewerGetPlaySpeedRate(this);GSmodelSetAnimRate(model,rate);}}
u8 tagPeopleWork::isAnimLast() const {u8 r=0;if(model==0)return r;return GSmodelHasAnimationEnded(model);}
u32 tagPeopleWork::getFlags() const {return flags;}
u8 tagPeopleWork::checkFlags(unsigned long mask) const {return peopleBiosCheckFlag(this,mask);}
u8 tagPeopleWork::isWalkStartMotion() const {
 PeopleInfo *p=peopleInfoBiosGetPtr(object);if(!p)return 0;if((p->flags>>1)&1)return 0;
 s32 a,b;GSmodelGetAnimIndex(model,&a,&b);if(b!=-1)return 0;
 if(a==motions.idle || a==motions.walkStart || a==motions.runStart)return 1;return 0;
}
u8 tagPeopleWork::isAlwayBlendChara() const {
 if(object==0x16C90400 || object==0x169E0400 || object==0x169F0400 || object==0x16A00400 || object==0x20250400 || object==0x1EE20400 || object==0x16C70400 || object==0x195B0400 || object==0x1A7C0400 || object==0x19540400)return 1;return 0;
}
