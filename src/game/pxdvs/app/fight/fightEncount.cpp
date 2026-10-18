#include <global.h>
class FIGHT_ENCOUNT {
public:
    u16 field; u16 messages[4]; u8 addMode, addPlace, addID, swapMode; u16 swapDeck; u8 fightMode, trainerKind, destroyFlag, pad13; u32 roundNo; u8 pad18[4];
    void setDirtyFlag(bool); u8 getDirtyFlag() const;
    void setRoundNo(u32); u32 getRoundNo() const;
    void setDestroyFlag(u8); u8 getDestroyFlag() const;
    void setTrainerKind(u8); u8 getTrainerKind() const;
    void setFightMode(u8); u8 getFightMode() const;
    void setSwapDeckNO(u16); u16 getSwapDeckNO() const;
    void setSwapMode(u8); u8 getSwapMode() const;
    void setAddID(u8); u8 getAddID() const;
    void setAddPlace(u8); u8 getAddPlace() const;
    void setAddMode(u8); u8 getAddMode() const;
    void setMsg(u8,u16); u16 getMsg(u8) const;
    void setField(u16); u16 getField() const;
    void clear();
};
void FIGHT_ENCOUNT::setDirtyFlag(bool v){if(this)((u8*)this)[0x18]=v;}
u8 FIGHT_ENCOUNT::getDirtyFlag() const {if(this==0)return false;return *((u8*)this+0x18);}
void FIGHT_ENCOUNT::setRoundNo(u32 v){if(this)*(u32*)((u8*)this+0x14)=v;}
u32 FIGHT_ENCOUNT::getRoundNo() const {if(this==0)return 0;return *(u32*)((u8*)this+0x14);}
void FIGHT_ENCOUNT::setDestroyFlag(u8 v){if(this)((u8*)this)[0x12]=v;}
u8 FIGHT_ENCOUNT::getDestroyFlag() const {if(this==0)return 0;return ((u8*)this)[0x12];}
void FIGHT_ENCOUNT::setTrainerKind(u8 v){if(this)((u8*)this)[0x11]=v;}
u8 FIGHT_ENCOUNT::getTrainerKind() const {if(this==0)return 0;return ((u8*)this)[0x11];}
void FIGHT_ENCOUNT::setFightMode(u8 v){if(this)((u8*)this)[0x10]=v;}
u8 FIGHT_ENCOUNT::getFightMode() const {if(this==0)return 0;return ((u8*)this)[0x10];}
void FIGHT_ENCOUNT::setSwapDeckNO(u16 v){if(this)*(u16*)((u8*)this+0xe)=v;}
u16 FIGHT_ENCOUNT::getSwapDeckNO() const {if(this==0)return 0;return *(u16*)((u8*)this+0xe);}
void FIGHT_ENCOUNT::setSwapMode(u8 v){if(this)((u8*)this)[0xd]=v;}
u8 FIGHT_ENCOUNT::getSwapMode() const {if(this==0)return 0;return ((u8*)this)[0xd];}
void FIGHT_ENCOUNT::setAddID(u8 v){if(this)((u8*)this)[0xc]=v;}
u8 FIGHT_ENCOUNT::getAddID() const {if(this==0)return 0;return ((u8*)this)[0xc];}
void FIGHT_ENCOUNT::setAddPlace(u8 v){if(this)((u8*)this)[0xb]=v;}
u8 FIGHT_ENCOUNT::getAddPlace() const {if(this==0)return 0;return ((u8*)this)[0xb];}
void FIGHT_ENCOUNT::setAddMode(u8 v){if(this)((u8*)this)[0xa]=v;}
u8 FIGHT_ENCOUNT::getAddMode() const {if(this==0)return 0;return ((u8*)this)[0xa];}
void FIGHT_ENCOUNT::setMsg(u8 i,u16 v){if(this)messages[i]=v;}
u16 FIGHT_ENCOUNT::getMsg(u8 i) const {if(this==0)return 0;return messages[i];}
void FIGHT_ENCOUNT::setField(u16 v){if(this)*(u16*)this=v;}
u16 FIGHT_ENCOUNT::getField() const {if(this==0)return 0;return *(u16*)this;}
void FIGHT_ENCOUNT::clear() {
    field=0; addMode=0; addPlace=0; addID=0; swapMode=0; swapDeck=0; fightMode=0; trainerKind=0;
    for (u8 i=0;i<4;++i) messages[i]=0;
    destroyFlag=0; roundNo=0; ((u8*)this)[0x18]=0;
}

class Pokemon { public: u8 getLevel() const; };
class Hero {
public:
    static Hero *getHeroPtr();
    u32 getBattleResumeFloorID() const;
    u8 getBattleResumeFloorIndex() const;
};
extern "C" {
FIGHT_ENCOUNT _fightEncount;
void *heroGetStatus(void *, u32, u16);
void heroDecPokedoru(void *, s32);
void recoveryPokemon();
u16 fightGetFightEncountDataId();
void *fightEncountDataBiosGetPtr(u16);
u8 fightEncountDataBiosGetZenmetuFlag(void *);
u16 fightGetFightResultId();
u8 fightFloorIsGcHeroWin(void *, u16);
void GSfsysFree(s32);
void GSflagOff(u32);
void peopleAllBlockMoveScript();
void floorSetFloorChangeInfo(u32, u32);
void floorPopAndChange(u32);
void floorSetFadeScript(s32, u32);
void floorWaitForChange();
u32 fightEncountDataBiosGetFightFloorDataId(void *);
u32 fightFloorDB_GetEnvSndId(u32);
u32 fightEncountDataBiosGetBgmSndId(void *);
u32 fightFloorDB_GetBgmSndId(u32);
u32 fightEncountDataBiosGetFightTrainerDataId(void *, u8);
u8 fightTrainerDB_GetKindDataId(u32);
void *fightTrainerKindDataBiosGetPtr(u32);
u32 fightTrainerKindDataBiosGetBgmSndId(void *);

FIGHT_ENCOUNT *fightEncountGetStrObj() { return &_fightEncount; }
void fightEncountAnnihilationRecovery() {
    u16 i;
    u8 highest = 0;
    for (i = 0; i < 6; ++i) {
        u8 level = ((Pokemon *)heroGetStatus(0, 3, i))->getLevel();
        if (highest < level) highest = level;
    }
    heroDecPokedoru(0, highest * 16);
    recoveryPokemon();
}
s32 fightEncountCheckZenmetu() {
    void *data = fightEncountDataBiosGetPtr(fightGetFightEncountDataId());
    Hero *hero = Hero::getHeroPtr();
    if (hero->getBattleResumeFloorID() == 0) return 0;
    if (fightEncountDataBiosGetZenmetuFlag(data) == 0) return 0;
    if (fightFloorIsGcHeroWin(0, fightGetFightResultId()) == 1) return 0;
    GSfsysFree(0x842);
    FIGHT_ENCOUNT *encounter = fightEncountGetStrObj();
    encounter->clear();
    encounter->setDirtyFlag(true);
    GSflagOff(0x323);
    fightEncountAnnihilationRecovery();
    peopleAllBlockMoveScript();
    u32 index = hero->getBattleResumeFloorIndex();
    floorSetFloorChangeInfo(hero->getBattleResumeFloorID(), index);
    floorPopAndChange(hero->getBattleResumeFloorID());
    floorSetFadeScript(0, 0x05960008);
    floorWaitForChange();
    return 1;
}
u32 fightEncountGetEnvSndDataId(u16 id) {
    return fightFloorDB_GetEnvSndId(fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(id)));
}
u32 fightEncountGetBgmSndDataId(u16 id) {
    void *data = fightEncountDataBiosGetPtr(id);
    u32 sound = fightEncountDataBiosGetBgmSndId(data);
    if (sound != 0) return sound;
    sound = fightFloorDB_GetBgmSndId(fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(id)));
    if (sound != 0) return sound;
    for (u16 i = 0; i < 4; ++i) {
        u32 trainer = fightEncountDataBiosGetFightTrainerDataId(data, (u8)i);
        if ((u16)trainer != 0) {
            u8 kind = fightTrainerDB_GetKindDataId(trainer);
            if (kind != 0) {
                sound = fightTrainerKindDataBiosGetBgmSndId(fightTrainerKindDataBiosGetPtr(kind));
                if (sound != 0) return sound;
            }
        }
    }
    return 8;
}
}

extern "C" {
void fightReadDeck(u16);
u8 fightEncountDataBiosGetFightKind(void *);
void fightSetFightResultId(u16);
void fightSetFightEncountDataId(u16);
void fightDataRewrite();
u32 GSfloorGetCurrent();
void fightFloor_SetEncountFloorId(void *, u32);
u16 fightFloorDB_GetFloorDataId(u32);
void mailMainReceiveTerminate();
void fightTrainerSetNameHearFlag(u16);
u32 soundGetBGMID();
u32 soundGetEnvID();
void soundOpenPlay(u32, u32, u32);
void soundStopEnv(u32);
u16 fightEncountDataBiosGetDiskId(void *);
void fadeSet(s32, f32);
void fadeCheck(s32);
u16 fightEncountDataBiosGetWipeId(void *);
void *fightEncountWipeDataBiosGetPtr(u16);
u32 fightEncountDataBiosGetWipeSnapshotUse(void *);
void *fightEncountDataBiosGetWipeFunction(void *);
f32 fightEncountDataBiosGetWipeEffectTime(void *);
u16 fightEncountDataBiosGetWipeEffectSndID(void *);
void fadeSetEX(s32, void *, u32, f32, f32);
void GSsndPlay(u32, s32, s32);
void fightSoundOpenPlayInit();
void fightFreeDeck(u16);
void GSfloorPush(u32);
void floorSetPrevFloorID(u32);
void floorLinkWithSE(u32, u32, u32);
void fightFloorSetStatus(u32, u32, u32, u32, u32);
void soundOpenPlayEnv(u32, u32, u32);
void GSflagOn(u32);
u8 GSflagTest(u32);
void floorExecSoundScript();
void floorClearReturnPoint();
extern s8 underTakerDeckRand;

u16 fightEncount(u16 id) {
    FIGHT_ENCOUNT *settings = fightEncountGetStrObj();
    settings->getField();
    settings->getFightMode();
    settings->getDestroyFlag();
    for (u8 i=0;i<4;++i) settings->getMsg(i);
    if (id == 0) return 0;
    fightReadDeck(id);
    void *data = fightEncountDataBiosGetPtr(id);
    u8 kind = fightEncountDataBiosGetFightKind(data);
    fightSetFightResultId(0);
    GSflagOff(0x30E);
    fightSetFightEncountDataId(id);
    underTakerDeckRand = -1;
    fightDataRewrite();
    u32 currentFloor=GSfloorGetCurrent();
    fightFloor_SetEncountFloorId(0,currentFloor);
    u16 floor = fightFloorDB_GetFloorDataId(fightEncountDataBiosGetFightFloorDataId(data));
    mailMainReceiveTerminate();
    fightTrainerSetNameHearFlag(id);
    u32 bgm = soundGetBGMID();
    u32 ambient = soundGetEnvID();
    soundOpenPlay(8,1000,255);
    soundStopEnv(1000);
    if (kind == 0xF && fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(id)) == 0) {
        fadeSet(3,0.5f);
        u32 sound = fightEncountGetBgmSndDataId(id);
        if (sound != 0) soundOpenPlay(sound,0,255);
    } else {
        void *wipe = fightEncountWipeDataBiosGetPtr(fightEncountDataBiosGetWipeId(data));
        u32 snapshot = fightEncountDataBiosGetWipeSnapshotUse(wipe);
        void *function = fightEncountDataBiosGetWipeFunction(wipe);
        fadeSetEX(9,function,snapshot,1.0f,fightEncountDataBiosGetWipeEffectTime(wipe));
        u16 sound = fightEncountDataBiosGetWipeEffectSndID(wipe);
        if (sound != 0) GSsndPlay(sound,0,0);
    }
    fightSoundOpenPlayInit();
    fightFreeDeck(id);
    GSfloorPush(floor);
    floorSetFadeScript(0,0);
    floorWaitForChange();
    floorSetPrevFloorID(floor);
    GSfsysFree(0x842);
    settings->clear();
    settings->setDirtyFlag(true);
    if (fightEncountDataBiosGetZenmetuFlag(data) != 0 && fightFloorIsGcHeroWin(0,fightGetFightResultId()) == 0) {
        fightSetFightEncountDataId(0);
        GSflagOff(0x323);
        fightEncountAnnihilationRecovery();
        peopleAllBlockMoveScript();
        Hero *hero = Hero::getHeroPtr();
        u32 index = hero->getBattleResumeFloorIndex();
        floorLinkWithSE(hero->getBattleResumeFloorID(),index,0);
        floorSetFadeScript(0,0x05960008);
        floorWaitForChange();
        fightFloorSetStatus(0,0,0xD,0,0);
        return fightGetFightResultId();
    }
    soundOpenPlay(bgm,1000,127);
    soundOpenPlayEnv(ambient,1000,127);
    GSflagOn(0x30E);
    floorExecSoundScript();
    floorClearReturnPoint();
    if (GSflagTest(0x323) == 0) {
        fadeSet(2,0.5f);
        fadeCheck(1);
    }
    fightFloorSetStatus(0,0,0xD,0,0);
    return fightGetFightResultId();
}
}
