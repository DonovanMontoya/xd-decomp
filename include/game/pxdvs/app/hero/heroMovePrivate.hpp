#ifndef HERO_MOVE_PRIVATE_H
#define HERO_MOVE_PRIVATE_H

#include <global.h>
#include <game/pxdvs/app/hero/hero.hpp>
#include <game/pxdvs/app/hero/heroMove.hpp>
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

struct FOOTWORK {
    f32 v[4];
};

enum FootStepCounter { FOOTSTEP_COUNTER_0, FOOTSTEP_COUNTER_1, FOOTSTEP_COUNTER_2, FOOTSTEP_COUNTER_3 };

typedef void (*HeroMoveStepCallback)(long, FootStepCounter, long);

struct HeroMoveCallbackSlot {
    HeroMoveStepCallback fn;
    s32 arg;
};

struct HeroMoveMember {
    u16 flags;
    u8 pad02[2];
    f32 dist;
    s32 neckMode;
    s32 field0C;
    FOOTWORK footWork;
};

struct HeroMoveWork {
    s32 leader;
    HeroMoveMember members[4];
    struct {
        s32 field00;
        s32 count;
        GSvec positions[60];
    } leaderLog;
    struct {
        f32 distance;
        HeroMoveCallbackSlot callbacks[8];
        s32 poisonSteps;
        s32 friendshipSteps;
    } footsteps;
    struct {
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
};

typedef char HeroMoveMember_size_check[(sizeof(HeroMoveMember) == 0x20) ? 1 : -1];
typedef char HeroMoveWork_members_check[(offsetof(HeroMoveWork, members) == 0x4) ? 1 : -1];
typedef char HeroMoveMember_footWork_check[(offsetof(HeroMoveMember, footWork) == 0x10) ? 1 : -1];
typedef char HeroMoveWork_callbacks_check[(offsetof(HeroMoveWork, footsteps.callbacks) == 0x360) ? 1 : -1];
typedef char HeroMoveWork_size_check[(sizeof(HeroMoveWork) == 0x660) ? 1 : -1];
typedef char HeroMoveWork_log_check[(offsetof(HeroMoveWork, leaderLog.positions) == 0x8C) ? 1 : -1];
typedef char HeroMoveWork_events3_check[(offsetof(HeroMoveWork, state.events3) == 0x3C8) ? 1 : -1];
typedef char HeroMoveWork_events1_check[(offsetof(HeroMoveWork, state.events1) == 0x498) ? 1 : -1];
typedef char HeroMoveWork_events2_check[(offsetof(HeroMoveWork, state.events2) == 0x568) ? 1 : -1];

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
u8 GSgfxVideoGetVsyncRate();
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
s32 heroMoveAddStepCallback(HeroMoveStepCallback, s32);
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
tagPeopleWork* peopleSearchID(u32);
GSvec* peopleBiosGetPosPtr(tagPeopleWork*);
GSvec* peopleBiosGetRotPtr(tagPeopleWork*);
GSvec* peopleBiosGetPrevPosPtr(tagPeopleWork*);
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
tagPeopleWork* peopleGet(u32, u32);
u32 itemDataBiosGetPtr(u16);
u32 itemDataBiosGetItemSoubiDataId(u32);
}

#endif
