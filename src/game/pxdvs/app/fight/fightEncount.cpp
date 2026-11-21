#include <global.h>
#include <game/pxdvs/app/fight/fightEncountBiosLayout.hpp>
#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/hero/hero.hpp>

class FIGHT_ENCOUNT {
public:
    u16 field;
    u16 messages[4];
    u8 addMode, addPlace, addID, swapMode;
    u16 swapDeck;
    u8 fightMode, trainerKind, destroyFlag;
    u32 roundNo;
    u8 dirtyFlag;
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
typedef char FightEncountSizeCheck[sizeof(FIGHT_ENCOUNT) == 0x1c ? 1 : -1];

// The original callers use the resume floor id as a full word.
extern "C" u32 getBattleResumeFloorID__4HeroCFv(const Hero *);
extern "C" {
FIGHT_ENCOUNT _fightEncount;
u32 heroGetStatus(Hero*, u16, u16);
void heroDecPokedoru(void *, s32);
void recoveryPokemon();
u16 fightGetFightEncountDataId();
u16 fightGetFightResultId();
u8 fightFloorIsGcHeroWin(void *, u16);
void GSfsysFree(s32);
void GSflagOff(u32);
void peopleAllBlockMoveScript();
void floorSetFloorChangeInfo(u32, u32);
void floorPopAndChange(u32);
void floorSetFadeScript(u32, u32);
void floorWaitForChange();
u32 fightFloorDB_GetEnvSndId(u16);
u32 fightFloorDB_GetBgmSndId(u16);
u8 fightTrainerDB_GetKindDataId(u32);
void *fightTrainerKindDataBiosGetPtr(u32);
u32 fightTrainerKindDataBiosGetBgmSndId(void *);

u8 fightReadDeck(u16);
void fightSetFightResultId(u16);
void fightSetFightEncountDataId(u16);
void fightDataRewrite();
u32 GSfloorGetCurrent();
void fightFloor_SetEncountFloorId(void *, u32);
u16 fightFloorDB_GetFloorDataId(u16);
void mailMainReceiveTerminate();
void fightTrainerSetNameHearFlag(u16);
u32 soundGetBGMID();
u32 soundGetEnvID();
s32 soundOpenPlay(u32, s32, s32);
void soundStopEnv(u32);
void fadeSet(u16, f32);
s8 fadeCheck(u8);
s32 fadeSetEX(u16, FightEncountWipeFunction, u8, f32, f32);
s32 GSsndPlay(u32, u16, u32);
void fightSoundOpenPlayInit();
void fightFreeDeck(u16);
s32 GSfloorPush(u32);
void floorSetPrevFloorID(u32);
void floorLinkWithSE(u32, u32, u32);
u32 fightFloorSetStatus(void*, u16, u16, u32, u32);
s32 soundOpenPlayEnv(u32, s32, s32);
void GSflagOn(u32);
u8 GSflagTest(u32);
void floorExecSoundScript();
void floorClearReturnPoint();
extern s8 underTakerDeckRand;

u32 fightEncountGetBgmSndDataId(u16 id);

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

FIGHT_ENCOUNT *fightEncountGetStrObj() { return &_fightEncount; }


s32 fightEncountCheckZenmetu() {
    FightEncountRecord *data = fightEncountDataBiosGetPtr(fightGetFightEncountDataId());
    Hero *hero = Hero::getHeroPtr();
    if (getBattleResumeFloorID__4HeroCFv(hero) == 0) return 0;
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
    floorSetFloorChangeInfo(getBattleResumeFloorID__4HeroCFv(hero), index);
    floorPopAndChange(getBattleResumeFloorID__4HeroCFv(hero));
    floorSetFadeScript(0, 0x05960008);
    floorWaitForChange();
    return 1;
}

static inline void playEncountWipe(FightEncountRecord* data) {
    FightEncountWipeRecord *wipe = fightEncountWipeDataBiosGetPtr(fightEncountDataBiosGetWipeId(data));
    u8 snapshot = fightEncountDataBiosGetWipeSnapshotUse(wipe);
    FightEncountWipeFunction function = fightEncountDataBiosGetWipeFunction(wipe);
    fadeSetEX(9, function, snapshot, 1.0f, fightEncountDataBiosGetWipeEffectTime(wipe));
    u16 sound = fightEncountDataBiosGetWipeEffectSndID(wipe);
    if (sound != 0) GSsndPlay(sound, 0, 0);
}

u16 fightEncount(u16 id) {
    FIGHT_ENCOUNT *settings;
    u8 i;
    FightEncountRecord *data;
    u8 kind;
    u32 currentFloor;
    u16 floor;
    u32 bgm;
    u32 ambient;
    settings = fightEncountGetStrObj();
    settings->getField();
    settings->getFightMode();
    settings->getDestroyFlag();
    for (i=0;i<4;++i) settings->getMsg(i);
    if (id == 0) return 0;
    fightReadDeck(id);
    data = fightEncountDataBiosGetPtr(id);
    kind = fightEncountDataBiosGetFightKind(data);
    fightSetFightResultId(0);
    GSflagOff(0x30E);
    fightSetFightEncountDataId(id);
    underTakerDeckRand = -1;
    fightDataRewrite();
    currentFloor=GSfloorGetCurrent();
    fightFloor_SetEncountFloorId(0,currentFloor);
    floor = fightFloorDB_GetFloorDataId(fightEncountDataBiosGetFightFloorDataId(data));
    mailMainReceiveTerminate();
    fightTrainerSetNameHearFlag(id);
    bgm = soundGetBGMID();
    ambient = soundGetEnvID();
    soundOpenPlay(8,1000,255);
    soundStopEnv(1000);
    if (kind == 0xF && fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(id)) == 0) {
        fadeSet(3,0.5f);
        u32 sound = fightEncountGetBgmSndDataId(id);
        if (sound != 0) soundOpenPlay(sound,0,255);
    } else {
        playEncountWipe(data);
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
        floorLinkWithSE(getBattleResumeFloorID__4HeroCFv(hero),index,0);
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

u32 fightEncountGetEnvSndDataId(u16 id) {
    return fightFloorDB_GetEnvSndId(fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(id)));
}
u32 fightEncountGetBgmSndDataId(u16 id) {
    FightEncountRecord *data = fightEncountDataBiosGetPtr(id);
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

void FIGHT_ENCOUNT::setDirtyFlag(bool value) {
    if (this) dirtyFlag = value;
}

u8 FIGHT_ENCOUNT::getDirtyFlag() const {
    if (this == 0) return 0;
    return dirtyFlag;
}

void FIGHT_ENCOUNT::setRoundNo(u32 value) {
    if (this) roundNo = value;
}

u32 FIGHT_ENCOUNT::getRoundNo() const {
    if (this == 0) return 0;
    return roundNo;
}

void FIGHT_ENCOUNT::setDestroyFlag(u8 value) {
    if (this) destroyFlag = value;
}

u8 FIGHT_ENCOUNT::getDestroyFlag() const {
    if (this == 0) return 0;
    return destroyFlag;
}

void FIGHT_ENCOUNT::setTrainerKind(u8 value) {
    if (this) trainerKind = value;
}

u8 FIGHT_ENCOUNT::getTrainerKind() const {
    if (this == 0) return 0;
    return trainerKind;
}

void FIGHT_ENCOUNT::setFightMode(u8 value) {
    if (this) fightMode = value;
}

u8 FIGHT_ENCOUNT::getFightMode() const {
    if (this == 0) return 0;
    return fightMode;
}

void FIGHT_ENCOUNT::setSwapDeckNO(u16 value) {
    if (this) swapDeck = value;
}

u16 FIGHT_ENCOUNT::getSwapDeckNO() const {
    if (this == 0) return 0;
    return swapDeck;
}

void FIGHT_ENCOUNT::setSwapMode(u8 value) {
    if (this) swapMode = value;
}

u8 FIGHT_ENCOUNT::getSwapMode() const {
    if (this == 0) return 0;
    return swapMode;
}

void FIGHT_ENCOUNT::setAddID(u8 value) {
    if (this) addID = value;
}

u8 FIGHT_ENCOUNT::getAddID() const {
    if (this == 0) return 0;
    return addID;
}

void FIGHT_ENCOUNT::setAddPlace(u8 value) {
    if (this) addPlace = value;
}

u8 FIGHT_ENCOUNT::getAddPlace() const {
    if (this == 0) return 0;
    return addPlace;
}

void FIGHT_ENCOUNT::setAddMode(u8 value) {
    if (this) addMode = value;
}

u8 FIGHT_ENCOUNT::getAddMode() const {
    if (this == 0) return 0;
    return addMode;
}

void FIGHT_ENCOUNT::setMsg(u8 index, u16 value) {
    if (this) messages[index] = value;
}

u16 FIGHT_ENCOUNT::getMsg(u8 index) const {
    if (this == 0) return 0;
    return messages[index];
}

void FIGHT_ENCOUNT::setField(u16 value) {
    if (this) field = value;
}

u16 FIGHT_ENCOUNT::getField() const {
    if (this == 0) return 0;
    return field;
}

void FIGHT_ENCOUNT::clear() {
    field = 0;
    addMode = 0;
    addPlace = 0;
    addID = 0;
    swapMode = 0;
    swapDeck = 0;
    fightMode = 0;
    trainerKind = 0;
    for (u8 i = 0; i < 4; ++i) messages[i] = 0;
    destroyFlag = 0;
    roundNo = 0;
    dirtyFlag = 0;
}
