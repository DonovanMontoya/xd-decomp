#ifndef HERO_MOVE_PRIVATE_H
#define HERO_MOVE_PRIVATE_H

#include <global.h>
#include <game/pxdvs/app/hero/hero.hpp>
#include <game/pxdvs/app/people/runtime.hpp>

enum HEROMOVE_MEMBER {
    HEROMOVE_MEMBER_0,
    HEROMOVE_MEMBER_1,
    HEROMOVE_MEMBER_2,
    HEROMOVE_MEMBER_3
};

enum FloorEnterMode { FloorEnterModeNone };

struct AnalogStickEmu {
    s8 b0;
    s8 b1;
    s8 b2;
    s8 b3;
    u8 b4;
    u8 b5;

    void init();
    void calculate(s8&, s8&, s8&, s8&);
};

struct HeroMoveMember {
    s32 x0;
    u16 flags;
    u8 pad06[2];
    f32 dist;
    s32 neckMode;
    u8 pad10[0x10];
};

struct HeroMoveQueuedEvent {
    GSvec position[3];
    u32 reserved24[3];
    u16 eventID;
    u16 reserved32;
};

struct HeroMoveWork {
    union {
        u8 raw[0x660];
        struct {
            u8 padState[0x3A8];
            s32 lockFrame;
            u8 smoothFloorLink;
            u8 started;
            u8 stickOverride;
            s8 stickData[4];
            u8 pad3B3;
            u32 autoEvent[5];
            HeroMoveQueuedEvent events3[4];
            HeroMoveQueuedEvent events1[4];
            HeroMoveQueuedEvent events2[4];
            s32 eventCount3;
            s32 eventCount1;
            s32 eventCount2;
            s32 stepPool[4];
            AnalogStickEmu analog;
            s32 frameCounter;
        } state;
        HeroMoveMember members[4];
        struct {
            u8 pad00[0x8C];
            GSvec log[60];
        } leaderLog;
    };
};

struct FOOTWORK {
    f32 v[4];
};

enum FootStepCounter { FOOTSTEP_COUNTER_0, FOOTSTEP_COUNTER_1, FOOTSTEP_COUNTER_2, FOOTSTEP_COUNTER_3 };

struct FloorModuleInterface {
    void (*create)(unsigned int, FloorEnterMode);
    void (*pre)(unsigned int, FloorEnterMode);
    void (*normal)(unsigned int, FloorEnterMode);
    int (*thread)(void*);
    void (*post)(unsigned int, FloorEnterMode);
    void (*free)(unsigned int, FloorEnterMode);
    const char* (*getName)();
    void (*saveState)(int, void*, unsigned long);
    void (*loadState)(int, void*, unsigned long);
    unsigned long (*getStateSize)(int);
    unsigned long (*getStateID)();
};

class FloorBgmMask {
public:
    void stopMask();
};

extern u32 pokecoloFrameCounter;

extern "C" {
u8 cameraGetType();
u8 dbgMenuIsOpen();
u8 menuIsCheck(u32);
s32 floorGetFloorState();
s32 floorExecScriptInteger(s32, s32, s32, s32, s32);
s32 floorEventExecScript(u32, s32);
u8 gimmickBoxIsGimmickMoving();
FloorBgmMask* floorSound_getBgmMaskObj();
void menuFieldMain(u32);
u8 peopleCheckFlag(u32, u32, u32);
void PSVECSubtract(GSvec*, GSvec*, GSvec*);
f32 PSVECMag(GSvec*);
u32 timeGetLastFrameTime();
u32 GSgfxVideoGetVsyncRate();
u32 GSinputButtonsChanged(u32);
u32 GSinputButtonsPressed(u32);
void FloorModuleInterface_clear(FloorModuleInterface*);
u32 floorRegisterModule(u8, u32, FloorModuleInterface*);
void* floorDataBiosGetPtr(u32);
u8 floorDataBiosGetFloorKind(void*);
void floorCreateThread(u32, u32, u32, void (*)());
u8 pokemonCheckValid(void*);
void heroMoveSetLockFrame(s32);
bool heroMoveAppointLeader(s32);
s32 heroMoveAddStepCallback(void (*)(long, FootStepCounter, long), s32);
void peopleRemoveNeckTarget(u32, u32, f32);
void peopleSetNeckTargetHero(u32, u32);
void peopleSetCollision(u32, u32, u32);
void peopleSetFlagOn(u32, u32, u32);
void peopleSetFlagOff(u32, u32, u32);
void* memcpy(void*, const void*, unsigned long);
}

extern "C" {
s32 heroGetStatus(void*, u16, u16);
s32 heroMoveJoinMember(s32);
s32 heroMoveDismissMember(s32);
s32 heroMoveSetNeckMode(s32, s32);
s32 heroMoveGetNeckMode(s32);
s32 heroMoveGetLeader();
bool heroMoveIsMember(s32);
f32 PSVECDistance(GSvec*, GSvec*);
u32 peopleGetHumanID(u32, u32);
void* peopleSearchID(u32);
void peopleUpdateAnimation(void*, u32);
u16 pokemonBiosGetItemDataId(Pokemon*);
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon*, u32, u16);
s32 GSflagGet(u32);
void* GSresGetResource(u32, u32);
void GSmodelSetRotation(void*, GSvec*);
void GSmodelGetRotation(void*, GSvec*);
void GSmodelGetPosition(void*, GSvec*);
void peopleSetPos(u32, u32, GSvec*);
void peopleSetDisp(u32, u32, bool);
void* peopleGet(u32, u32);
u32 itemDataBiosGetPtr(u16);
u32 itemDataBiosGetItemSoubiDataId(u32);
}

#endif
