#pragma force_active on
#include <dolphin/types.h>
struct floorsound_dd_ {u8 type,volume;u16 floor,id,time,fade,flag;};
extern floorsound_dd_ *floorsoundTbl;extern u32 *floorsoundTbl_number;
extern "C" {
u8 GSflagTest(u32);void GSprint(int,int,int,u32,const char*,...);u8 GSsndCheckSE(u32);int GSsndGetVolume(u32);void GSsndSetVolume(u32,u32,u32,u32);int dbgMenuGetLayerID();u32 floorGetCurrent();u8 soundCheckEnv(u32);u32 soundGetBGMID();u32 soundGetVolume(u32);void soundOpenPlay(u32,u32,u32);void soundOpenPlayEnvFadeOutIn(u32,u32,u32,u32);void soundOpenPlayFadeOutIn(u32,u32,u32,u32);void soundSetVolumeID(u32,u32,u32);
}
class FloorBgmMask {public:enum BgmMaskMode {None,Out,Keep,Delay,In};BgmMaskMode mode;u8 enable,volume,original,masked;u32 id;f32 rate,inTime,outTime,remaining,delay;FloorBgmMask();void update(f32);void endMECallback();void startMECallback();void stopMask();void endMask();void startMask();void setFadeOutTime(f32);void setFadeInTime(f32);void setVolumeRate(f32);void finalize();void initialize();void changeMode(BgmMaskMode m);u8 isEnable();};
typedef char FloorBgmMaskSize[sizeof(FloorBgmMask)==0x20?1:-1];
typedef char FloorSoundDataSize[sizeof(floorsound_dd_)==0xC?1:-1];
#pragma push
#pragma suppress_init_code on
// Register construction below, before the emitted inline methods.
static FloorBgmMask _bgmMask;
#pragma pop
static u8 _displaySndFlag;
void FloorBgmMask::update(f32 dt);
void FloorBgmMask::endMECallback();
void FloorBgmMask::startMECallback();
void FloorBgmMask::stopMask();
void FloorBgmMask::endMask();
void FloorBgmMask::startMask();
void FloorBgmMask::setFadeOutTime(f32 f);
void FloorBgmMask::setFadeInTime(f32 f);
void FloorBgmMask::setVolumeRate(f32 f);
void FloorBgmMask::finalize();
void FloorBgmMask::initialize();
FloorBgmMask::FloorBgmMask();
static u8 _playEnvSound(floorsound_dd_ *p);
static u8 _playSound(floorsound_dd_ *p);
extern "C" {
FloorBgmMask* floorSound_getBgmMaskObj();
u8 floorSound_getDispSoundVolume();
void floorSound_setDispSoundVolume(u8 f);
floorsound_dd_* floorSound_SearchTable(u32 floor,floorsound_dd_ *p);
int floorSound_playEnvSound(int type);
int floorSound_playSound();
}

inline void FloorBgmMask::changeMode(BgmMaskMode m);
inline u8 FloorBgmMask::isEnable();

extern "C++" {
void FloorBgmMask::update(f32 dt){const char *state="---";id=soundGetBGMID();if(id==0)changeMode(None);switch(mode){case None:state="noneMask";break;case Out:state="fadeOut";remaining-=dt;if(remaining<=0.0f)changeMode(Keep);break;case Keep:state="fadeKeep";break;case Delay:state="fadeInDelay";remaining-=dt;if(remaining<=0.0f){soundSetVolumeID(id,(u32)(1000.0f*inTime),original);remaining=inTime;changeMode(In);}break;case In:state="fadeIn";remaining-=dt;if(remaining<=0.0f)changeMode(None);break;}
if(_displaySndFlag){int layer=dbgMenuGetLayerID();if(layer!=-1){u32 v=0;if(id)v=soundGetVolume(id);GSprint(layer,8,26,0xFFFFFFFF,"snd_id = %d, curVol %d [%s]",id,v,state);}}}
}
extern "C++" {
void FloorBgmMask::endMECallback(){}
}
extern "C++" {
void FloorBgmMask::startMECallback(){switch(mode){case Delay:soundSetVolumeID(id,(u32)(1000.0f*inTime),original);changeMode(None);break;}}
}
extern "C++" {
void FloorBgmMask::stopMask(){if(isEnable() && mode!=None){soundSetVolumeID(id,(u32)(1000.0f*inTime),original);changeMode(None);}}
}
extern "C++" {
void FloorBgmMask::endMask(){if(isEnable()){remaining=delay;changeMode(Delay);}}
}
extern "C++" {
void FloorBgmMask::startMask(){if(!isEnable()||mode==Out||mode==Keep)return;if(mode==Delay){changeMode(Keep);return;}if(mode==None){id=soundGetBGMID();if(!id)return;volume=127;volume=soundGetVolume(id);original=volume;masked=(u8)((f32)volume*rate);}soundSetVolumeID(id,(u32)(1000.0f*outTime),masked);changeMode(Out);remaining=outTime;}
}
extern "C++" {
void FloorBgmMask::setFadeOutTime(f32 f){outTime=f;}
}
extern "C++" {
void FloorBgmMask::setFadeInTime(f32 f){inTime=f;}
}
extern "C++" {
void FloorBgmMask::setVolumeRate(f32 f){if(f<0.0f||f>1.0f)return;rate=f;}
}
extern "C++" {
void FloorBgmMask::finalize(){inTime=0.0f;stopMask();enable=1;mode=None;volume=0;rate=0.9f;inTime=0.3f;outTime=0.3f;delay=4.0f;}
}
extern "C++" {
void FloorBgmMask::initialize(){}
}
extern "C++" {
FloorBgmMask::FloorBgmMask(){enable=1;mode=None;volume=0;rate=0.9f;inTime=0.3f;outTime=0.3f;delay=4.0f;}
}
extern "C" {
FloorBgmMask* floorSound_getBgmMaskObj(){return &_bgmMask;}
}
extern "C" {
u8 floorSound_getDispSoundVolume(){return _displaySndFlag;}
}
extern "C" {
void floorSound_setDispSoundVolume(u8 f){_displaySndFlag=f;}
}
extern "C" {
int floorSound_playEnvSound(int type){floorsound_dd_ *p;u32 floor=floorGetCurrent();p=floorSound_SearchTable(floor,0);for(;p;p=floorSound_SearchTable(floor,p+1))if((p->flag==0 || GSflagTest(p->flag)) && type==p->type && _playEnvSound(p))return 1;return 0;}
}
extern "C" {
int floorSound_playSound(){floorsound_dd_ *p;u32 floor=floorGetCurrent();p=floorSound_SearchTable(floor,0);for(;p;p=floorSound_SearchTable(floor,p+1))if((p->flag==0 || GSflagTest(p->flag)) && _playSound(p))return 1;return 0;}
}
extern "C" {
floorsound_dd_* floorSound_SearchTable(u32 floor,floorsound_dd_ *p){floorsound_dd_ *end=floorsoundTbl+*floorsoundTbl_number;if(!p)p=floorsoundTbl;for(;p<end;p++)if(p->floor==floor)return p;return 0;}
}
extern "C++" {
static u8 _playEnvSound(floorsound_dd_ *p){if(soundCheckEnv(p->id)==0)return 0;soundOpenPlayEnvFadeOutIn(p->id,p->fade,p->time,p->volume);return 1;}
}
extern "C++" {
static u8 _playSound(floorsound_dd_ *p){if(!p)return 0;if(soundCheckEnv(p->id))return 0;if(GSsndCheckSE(p->id))soundOpenPlay(p->id,p->time,p->volume);else{u32 bgm=soundGetBGMID();u16 id=p->id;if(id==bgm){int v=GSsndGetVolume(id);u8 volume=p->volume;if(volume!=v)GSsndSetVolume(volume,0,1,0);}else soundOpenPlayFadeOutIn(id,500,p->time,p->volume);}return 1;}
}
// The runtime initializer calls the class constructor through its existing ABI.
extern "C" void __ct__12FloorBgmMaskFv(FloorBgmMask*);
extern "C" void __sinit_floorsound_cpp(){__ct__12FloorBgmMaskFv(&_bgmMask);}
extern "C++" {
inline void FloorBgmMask::changeMode(BgmMaskMode m){mode=m;}
}
extern "C++" {
inline u8 FloorBgmMask::isEnable(){return enable;}
}


__declspec(section ".ctors") static void (*const floorSoundInitializers[])(void)={__sinit_floorsound_cpp};
