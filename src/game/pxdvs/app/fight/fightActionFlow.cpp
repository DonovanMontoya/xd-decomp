#include <dolphin/types.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/deck/deck_layout.hpp>
#include <game/pxdvs/app/hero/hero.hpp>

struct FightOutPokemon;
struct FIGHT_FLOOR;
struct FightActionDisplayCopy { s32 value[2]; };
struct FightActionCopy {
    u16 kind;
    s32 buff;
    void *data;
    void *buffData;
    s32 buffDataId;
    void *actor;
    void *motoData;
    s32 fifoIndex;
    FightActionDisplayCopy display[2];
    inline FightActionCopy(const FightActionCopy& source) {
        kind = source.kind;
        buff = source.buff;
        data = source.data;
        buffData = source.buffData;
        buffDataId = source.buffDataId;
        actor = source.actor;
        motoData = source.motoData;
        fifoIndex = source.fifoIndex;
        display[0] = source.display[0];
        display[1] = source.display[1];
    }
};
struct KeyInfoCopy {
    u16 on, off, trigger, repeat, released;
    u8 reserved[0x10];
};

extern "C" {
u32 fightFloor_GetFightType(void *);
void *fightActionBiosGetActorFightTargetPtr(void *);
void fightSeqSpecificationActionCounterInit(void *);
u8 fightTargetIsHostSide(void *, u8);
u8 fightFloorSetFightResultId(void *, s32);
void fightFloor_SetEscapePokemonPtr(void *, void *);
void fightSeqPokemonSoubiItemCheckAppear(FightOutPokemon *);
void fightSeqFightOutPokemonTokuseiCheckAppear(FightOutPokemon *);
u16 fightGetFightEncountDataId(void);
void *fightEncountDataBiosGetPtr(u16);
void *fightFloorGetStatus(u32, u32, u32, u32);
void fightFloorCreate(void *, u16);
void fightFloorInitFightStart(void *);
u32 fightEncountDataBiosGetFightFloorDataId(void *);
void *fightTargetGetPtr(u32, u32, u32);
u32 fightFloorDB_GetFightSideDataId(u32, u32);
void fightSideCreate(void *, u32);
u32 fightFloor_GetEnvSndId(void *);
u8 soundOpenPlayFadeOutIn(s32, s32, s32, u8);
void fightMainWaitFrame(u32);
void *fightOutPokemon_GetSequencePtr(FightOutPokemon *);
void fightSeqFightOutPokemonDarkCheckAppear(FightOutPokemon *, u8);
void fightFloor_SetAttackPokemonPtr(void *, void *);
void fightSeqCallExec(void *);
void *fightActionBiosGetBuffDataPtr(void *);
void fightSeqExec(void *, void *, void *);
u16 fightGetFightResultId(void);
void fightSeqPost(void *);
void fightFloorInitFightTarget(void *);
u8 fightTrainerSelectFightAction(void *, u16);
void fightFloorSetTuusinErrorFightResult(void *);
void fightFloor_SetIrekaePokemonPtr(void *, void *);
s32 fightActionBiosGetBuffDataId(void *);
void fightOutPokemon_SetIrekaeTargetEntryId(void *, s16);
void fightSeqIrekaeExec(void *);
KeyInfoCopy menuGetKeyInfo(s32);
s8 fadeCheck(s32);
u32 fightFloor_GetFightKind(void *);
u32 GSflagGet(u32);
void fightFloorCreateFightOutPokemonPtrAry(void *);
void fightFloorSortFightOutPokemonPtrAry(void *, s32);
void fightSeqPre(void *);
void *fightFloor_GetFightOutPokemonPtrAry(void *, u16);
u8 fightOutPokemonCheckFightOut(void *);
void fightOutPokemon_SetFightActionFlag(void *, u8);
u8 fightOutPokemon_GetFightActionFlag(void *);
void *fightOutPokemon_GetFightActionBuffPtr(void *);
u8 fightActionCheckValid(void *);
u16 fightActionGetKindDataId(void *);
u8 fightActionFlowFifo(FightActionCopy);
void *fightOutPokemon_GetFightItemPtr(void *);
u16 fightItem_GetItemDataId(void *);
u8 itemDB_GetKind(u16);
u32 fightItem_GetTargetDataId(void *);
void *fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u32, u16);
void fightFloor_SetDefensePokemonPtr(void *, void *);
void fightSeqItemExec(void *, u16);
void fightKoukaDoFightKoukaJoukenAndKouka(void *, s32);
u32 fightFloorGetNowTenkouDataId(void *, u8);
u8 fightFloorLoopValidFightOutPokemon(void *, s32 (*)(void *, u16, void *), void *, u8);
u32 tenkouDataBiosGetFightInitMsgId(u8);
void fightFloor_SetAppointMsgPtr(void *, u32);
void fightSeqInit(void);
void *fightActionBiosGetFightActionDataPtr(void *);
u8 fightSeqFightActionCreateAndFlowFifo(void *, void *, u16, s32, void *, void *);
void fightSeqFightOutPokemonTokuseiCheckIkaku(s8);
void fightSeqFightOutPokemonTokuseiCheckTrace(void);
void fightFloorSetMeetEnemyFightPokemonEnemySideAll(void *);
void fightFloorRegistFightTrainerEnemyPokemonFightSideAll(void *);
void fightFloorCreateFightPokemonEnemyAryEnemySideAll(void *);
s32 HSD_Rand(void);
void fightFloor_SetFisstAttackRnd(void *, u16);
void wazaSequenceSysFreeAllWaza(void);
extern u8 fight_action_data_kaisi[];
extern u8 WAZA_FieldWeather[];
u8 dbgMenuFightGetAllFightTrainerOperateFlag(void);
u8 fightFloor_GetFightTypeTrainerNum(void *);
void *fightFloorGetValidFightSidePtr(void *, u32);
void *fightSideGetValidFightTrainerPtr(void *, u16);
#define fightSideGetValidFightTrainerPtrU32 ((void *(*)(void *, u32))fightSideGetValidFightTrainerPtr)
u8 fightMenuFightTrainerGcHeroOpenMenu(void *, u8, u8);
u8 fightFloorLoopValidFightTrainer(void *, s32 (*)(void *, u16, void *), void *, u8);
void *fightOutPokemon_GetFightWazaPtr(void *);
u8 fightWazaCheckValid(void *);
u32 fightWaza_GetTargetDataId(void *);
void *fightOutPokemonGetPokemonPtr(void *);
u16 fightOutPokemon_GetMotoWazaDataId(void *);
u8 fightWaza_GetWazaBanme(void *);
u8 fightWaza_GetAutoMakeFlag(void *);
u16 pokemon_GetPokemonWazaDataId(void *, u16);
void fightWaza_SetMotoWazaDataId(void *, u16);
void fightWazaSetUseWazaStatus(void *, u16);
FightOutPokemon *fightSeqSelectDefensePokemonPtr(void *, u16, u8, void *, u8, u8, s16);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(void *, void *);
void fightSeqWazaExec(void *, u16);
u8 fightOutPokemonIsJoutaiDataId(void *, u16);
void fightSeqCheckDarkPokemonJoutaiHyperAct(void *, u8);
}
u32 deckDataVirtualDB_GetFlag(u16);

extern "C" {
void *fightFloorGetGcHeroFightTrainerPtr(void *);
void *fightTrainer_GetHeroPtr(void *);
void fightTrainerBackFightPokemonToTemotiPokemon(void *, u8);
u8 fightFloor_GetFightKindGetExpFlag(void *);
u8 fightTrainerCheckCanGetExp(void *);
void *heroGetStatus(void *, u32, u32);
u8 pokemonCheckFightOut(void *);
u8 pokemonIsDarkPokemon(void *);
void *fightTrainerCheckTemotiPokemonFightEntry(void *, void *);
u8 fightPokemonCheckFightOut(void *);
u8 fightPokemon_GetLevelUpFlag(void *);
u16 pokemonEvolutionCheck(void *, u32, u32, u16 *, u16 *);
void pokemonEvolutionAll(void *, u16, u16, u16 *, void *, u8, u8, u8);
void fightMainWaitFrameEffect(u32);
u8 fightFloor_GetFightKindMonohiroiFlag(void *);
void heroCheckSetMonohiroiAllTemotiPokemon(void *);
u8 fightFloor_GetFightKindGetInfectPokerusFlag(void *);
u8 fightFloor_GetFightKindBackSaveDataFlag(void *);
void *savedataGetStatus(u32, u32);
u8 heroBiosGetMeetDarkPokemonCount(void *);
void heroBiosCopy(void *, void *);
void heroBiosSetMeetDarkPokemonCount(void *, u8);
u8 menuCBBios_CurrentlyWorkingToolBattle(void);
void *menuCBBios_GetHeroImmediately(u8);
u8 fightTrainerIsGcHero(void *);
void *fightGetMenuCtrlHero(void);
void WazaSequence_Free(u32);
extern u32 fightEnemyTrainerWazaSeqHdl;
}

extern "C" {
u8 fightFloorIsGcHeroWin(void *, u16);
void fightMsgctrlSetValue(u32, void *);
u8 fightMenuOpenMsg(u32);
void fightMenuCloseMsg(void);
void *pokemon_GetNicknamePtr(Pokemon *);
u32 fightFloor_GetFightFloorDataId(void *);
void *fightTargetGetPtrAsNowFightType(u32, void *);
void *fightTrainer_GetSequencePtr(void *);
u32 fightTrainer_GetFightTrainerDataId(void *);
u32 fightFloor_GetSyoukaiWzxDataId(void *);
u16 fightFloor_GetEncountDataId(void *);
u32 fightEncountDataBiosGetSyoukaiWzxDataId(void *);
u16 fightTrainerDB_GetSyoukaiWzxDataId(u32);
u16 fightTrainerDB_GetSerihuMsgId(u32, u32);
u8 fightKind_CheckFightKind(u32);
u8 fightFloorIsNowEncountVirtualBattle(void *);
u8 fightFloorIsNowEncountOpeningVirtualBattle(void *);
u8 fightFloorIsNowEncountHostEnemyPokemonKime(void *);
u8 fightTargetIsHostSide(void *, u8);
void *fightTrainerGetValidFightOutPokemonPtr(void *, u16);
u32 Sequence_LoadWaza(void *, u16, s32, s32);
u8 fightFloor_GetFightKindHostEnemyMsgFlag(void *);
extern u16 _fight_kaisi_pre_trainer_intr_wzx_data_id_ary[5];
extern u8 _fight_kaisi_pre_trainer_intr_wzx_data_id_num;
extern u16 _fight_kaisi_pre_trainer_intr_wzx_data_id;
}

extern "C" s32 fightActionFlowHeijou(void) {
    return 1;
}

static s32 _fightActionFlowKaisiPostSubFightOutPokemonSoubiItemCheckAppear(void *p, u16, void *) {
    fightSeqPokemonSoubiItemCheckAppear((FightOutPokemon *)p);
    return 1;
}

static s32 _fightActionFlowKaisiPostSubFightOutPokemonTokuseiCheckAppear(void *p, u16, void *) {
    fightSeqFightOutPokemonTokuseiCheckAppear((FightOutPokemon *)p);
    return 1;
}

extern "C" s32 fightActionFlowFightNigeru(void *actor) {
    void *target;
    u8 type = fightFloor_GetFightType(0);
    target = fightActionBiosGetActorFightTargetPtr(actor);
    fightSeqSpecificationActionCounterInit(target);
    u8 res;
    if (fightTargetIsHostSide(target, type) == 1) {
        res = fightFloorSetFightResultId(0, 4);
    } else {
        res = fightFloorSetFightResultId(0, 5);
    }
    if (res == 1) {
        fightFloor_SetEscapePokemonPtr(0, target);
    }
    return 1;
}

extern "C" s32 fightActionFlowKaijou(void) {
    void *data;
    u32 floorData;
    void *t;
    u8 type;
    u16 id = fightGetFightEncountDataId();
    data = fightEncountDataBiosGetPtr(id);
    fightFloorCreate(fightFloorGetStatus(0, 0, 0, 0), id);
    fightFloorInitFightStart(0);
    type = fightFloor_GetFightType(0);
    floorData = fightEncountDataBiosGetFightFloorDataId(data);
    t = fightTargetGetPtr(4, 0, type);
    u32 side = fightFloorDB_GetFightSideDataId(floorData, 0);
    fightSideCreate(t, side);
    t = fightTargetGetPtr(5, 0, type);
    fightSideCreate(t, fightFloorDB_GetFightSideDataId(floorData, 1));
    return 1;
}

extern "C" s32 fightActionFlowNullFunc(void) {
    return 1;
}

extern "C" s32 fightActionFlowSyuuryouPre(void) {
    if (fightFloor_GetEnvSndId(0) != 0) {
        soundOpenPlayFadeOutIn(8, 1000, 1000, 255);
        fightMainWaitFrame(60);
    }
    return 1;
}

static s32 _fightActionFlowTenkouInitSubGetSeqFightOutPokemonPtr(void *p, u16, void *out) {
    if (fightOutPokemon_GetSequencePtr((FightOutPokemon *)p) != 0) {
        if (out != 0) {
            *(void **)out = p;
        }
        return 0;
    }
    return 1;
}

static s32 _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear(void *p, u16, void *arg) {
    if (arg != 0) {
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon *)p, *(u8 *)arg);
    } else {
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon *)p, 0);
        fightSeqFightOutPokemonDarkCheckAppear((FightOutPokemon *)p, 1);
    }
    return 1;
}

extern "C" s32 fightActionFlowFightTrainerCall(void *actor) {
    void *target;
    fightFloor_GetFightType(0);
    target = fightActionBiosGetActorFightTargetPtr(actor);
    fightFloor_SetAttackPokemonPtr(0, target);
    fightSeqCallExec(actor);
    return 1;
}

extern "C" s32 fightActionFlowWazaKiaipantiPre(void *actor) {
    fightFloor_SetAttackPokemonPtr(0, fightActionBiosGetActorFightTargetPtr(actor));
    fightSeqExec(actor, fightActionBiosGetBuffDataPtr(actor), 0);
    return 1;
}

extern "C" s32 fightActionFlowOneTurnPost(void *actor) {
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    fightSeqPost(actor);
    fightMainWaitFrame(5);
    fightFloorInitFightTarget(0);
    return 1;
}

static s32 _fightActionFlowFightTrainerSelectFightAction(void *p, u16 q, void *) {
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    if (!fightTrainerSelectFightAction(p, q)) {
        fightFloorSetTuusinErrorFightResult(0);
    }
    return 1;
}

extern "C" s32 fightActionFlowFightOutPokemonIrekae(void *actor) {
    void *target = fightActionBiosGetActorFightTargetPtr(actor);
    fightFloor_SetIrekaePokemonPtr(0, target);
    fightOutPokemon_SetIrekaeTargetEntryId(target, fightActionBiosGetBuffDataId(actor));
    fightSeqIrekaeExec(actor);
    return 1;
}

static u8 _fightActionFlowKaisiPreSubCheckCancel(bool *flag) {
    if (flag == 0) {
        return 0;
    }
    {
        u16 on = menuGetKeyInfo(1).on;
        if (fadeCheck(0) == 0 && (on & 0x20)) {
            *flag = 1;
        }
    }
    return *flag;
}

static bool _fightActionFlowKaisiPreSubCheckVirtualDiskCancel(u16 deck) {
    u8 kind = fightFloor_GetFightKind(0);
    if ((menuGetKeyInfo(1).on & 0x20) && kind == 0xF) {
        if (GSflagGet(0x8F5) == 1 || GSflagGet(deckDataVirtualDB_GetFlag(deck)) == 1) {
            return 1;
        }
    }
    return 0;
}

static s32 _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(FIGHT_FLOOR *floor, u8 flag) {
    void* buff;
    u16 i;
    for (i = 0; i < 8; i++) {
        void *p = fightFloor_GetFightOutPokemonPtrAry(floor, i);
        if (p != 0) {
            if (!fightOutPokemonCheckFightOut(p)) {
                fightOutPokemon_SetFightActionFlag(p, 1);
                continue;
            }
            buff = fightOutPokemon_GetFightActionBuffPtr(p);
            if (buff == 0) {
                fightOutPokemon_SetFightActionFlag(p, 1);
                continue;
            }
            if (!fightActionCheckValid(buff)) {
                fightOutPokemon_SetFightActionFlag(p, 1);
                continue;
            }
            if (!flag) {
                if (fightActionGetKindDataId(buff) != 8) {
                    continue;
                }
            } else {
                if (fightActionGetKindDataId(buff) == 8) {
                    continue;
                }
            }
            if (fightOutPokemon_GetFightActionFlag(p) == 1) {
                continue;
            }
            fightOutPokemon_SetFightActionFlag(p, 1);
            fightActionFlowFifo(*(FightActionCopy *)buff);
            if (flag) {
                fightFloorInitFightTarget(0);
                if (fightGetFightResultId() != 0) {
                    fightGetFightResultId();
                    return 1;
                }
            }
        }
    }
    return 1;
}

extern "C" s32 fightActionFlowAllFightOutPokemonDoFightAction(void *actor) {
    fightFloorCreateFightOutPokemonPtrAry(0);
    fightFloorSortFightOutPokemonPtrAry(0, 1);
    s32 r = _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(0, 0);
    if ((u8)r != 1) {
        return r;
    }
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    fightSeqPre(actor);
    r = _fightActionFlowAllFightOutPokemonDoFightActionOneLoop(0, 1);
    return (u8)r == 1 ? 1 : r;
}

extern "C" s32 fightActionFlowFightTrainerUseItem(void *actor) {
    void *target;
    void *item;
    u16 itemId;
    u8 type;
    void *def;
    type = fightFloor_GetFightType(0);
    target = fightActionBiosGetActorFightTargetPtr(actor);
    fightFloor_SetAttackPokemonPtr(0, target);
    item = fightOutPokemon_GetFightItemPtr(target);
    itemId = fightItem_GetItemDataId(item);
    if (itemDB_GetKind(itemId) == 1) {
        def = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightItem_GetTargetDataId(item), type);
    } else {
        def = target;
    }
    fightFloor_SetDefensePokemonPtr(0, def);
    fightSeqItemExec(actor, itemId);
    return 1;
}

extern "C" s32 fightActionFlowTenkouInit(void *actor) {
    u8 tenkou;
    void *seq;
    fightKoukaDoFightKoukaJoukenAndKouka(0, 1);
    tenkou = fightFloorGetNowTenkouDataId(0, 0);
    seq = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowTenkouInitSubGetSeqFightOutPokemonPtr, &seq, 0);
    if (tenkou != 0) {
        u32 msg;
        fightFloor_SetAttackPokemonPtr(0, seq);
        msg = tenkouDataBiosGetFightInitMsgId(tenkou);
        fightFloor_SetAppointMsgPtr(0, msg);
        fightSeqExec(actor, fightActionBiosGetBuffDataPtr(actor), 0);
    }
    return 1;
}

extern "C" s32 fightActionFlowKaisiPost(void *actor) {
    u8 flag;
    fightFloorCreateFightOutPokemonPtrAry(0);
    fightFloorSortFightOutPokemonPtrAry(0, 0);
    fightSeqInit();
    flag = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear, &flag, 0);
    fightSeqFightActionCreateAndFlowFifo(fightActionBiosGetFightActionDataPtr(actor), 0, 6, 0, fight_action_data_kaisi, WAZA_FieldWeather);
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonTokuseiCheckAppear, 0, 1);
    fightSeqFightOutPokemonTokuseiCheckIkaku(1);
    fightSeqFightOutPokemonTokuseiCheckTrace();
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonSoubiItemCheckAppear, 0, 1);
    flag = 1;
    fightFloorLoopValidFightOutPokemon(0, _fightActionFlowKaisiPostSubFightOutPokemonDarkCheckAppear, &flag, 0);
    fightFloorSetMeetEnemyFightPokemonEnemySideAll(0);
    fightFloorRegistFightTrainerEnemyPokemonFightSideAll(0);
    fightFloorCreateFightPokemonEnemyAryEnemySideAll(0);
    fightFloor_SetFisstAttackRnd(0, HSD_Rand());
    wazaSequenceSysFreeAllWaza();
    return 1;
}

extern "C" s32 fightActionFlowAllFightTrainerSelectFightAction(void) {
    u32 saved;
    u8 operate;
    void *sp;
    u8 num;
    u8 type;
    u16 j;
    u32 side;
    operate = dbgMenuFightGetAllFightTrainerOperateFlag();
    if (operate == 1) {
        type = fightFloor_GetFightType(0);
        num = (u8)fightFloor_GetFightTypeTrainerNum(0);
        for (side = 0; (u16)side < 2; side++) {
        top:
            sp = fightFloorGetValidFightSidePtr(0, side);
            if (sp != 0) {
                saved = (u16)side;
                for (j = 0; (u32)j < (u32)num; j++) {
                    for (;;) {
                        void *tr = fightSideGetValidFightTrainerPtr(sp, j);
                        if (tr == 0) {
                            break;
                        }
                        if (fightMenuFightTrainerGcHeroOpenMenu(tr, type, operate)) {
                            break;
                        }
                        if (saved != 0) {
                            side--;
                            goto top;
                        }
                    }
                }
            }
        }
    } else {
        fightFloorLoopValidFightTrainer(0, _fightActionFlowFightTrainerSelectFightAction, 0, 1);
    }
    return 1;
}

static inline void *_owGetDef(void *w, u8 t) {
    return fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightWaza_GetTargetDataId(w), t);
}

static inline void *_owGetAttacker(void *a) {
    return fightActionBiosGetActorFightTargetPtr(a);
}

extern "C" s32 fightActionFlowFightOutPokemonOutWaza(void *actor) {
    u16 moto;
    void *waza;
    void *sel;
    u8 type;
    void *attacker;
    void *pk;
    u8 banme;
    void *def;

    type = fightFloor_GetFightType(0);
    attacker = _owGetAttacker(actor);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    if (!fightWazaCheckValid(waza)) {
        return 0;
    }
    def = _owGetDef(waza, type);
    fightFloor_SetAttackPokemonPtr(0, attacker);
    fightFloor_SetDefensePokemonPtr(0, def);
    pk = fightOutPokemonGetPokemonPtr(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    moto = fightOutPokemon_GetMotoWazaDataId(attacker);
    banme = fightWaza_GetWazaBanme(waza);
    if (!fightWaza_GetAutoMakeFlag(waza)) {
        if (moto != pokemon_GetPokemonWazaDataId(pk, banme)) {
            moto = pokemon_GetPokemonWazaDataId(pk, banme);
            fightWaza_SetMotoWazaDataId(waza, moto);
            fightWazaSetUseWazaStatus(waza, moto);
            sel = fightSeqSelectDefensePokemonPtr(attacker, moto, type, 0, 1, 0, -1);
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, sel);
        }
    }
    fightSeqWazaExec(actor, moto);
    if (!fightOutPokemonIsJoutaiDataId(attacker, 0x3E)) {
        fightSeqCheckDarkPokemonJoutaiHyperAct(attacker, 0);
    }
    return 1;
}

void _darkPokemonSetUnderTaker(DeckDarkPokemon *deck, Pokemon *pk, u16 id) {
    u32 steps;
    DarkPokemon *dp;
    dp = pk->getDarkPokemon();
    if (deck->getWorth()) {
        steps = Hero::getHeroPtr()->getFootStep();
        if (deck->getUnderTakerFlag() || fightFloorIsGcHeroWin(0, fightGetFightResultId())) {
            if (dp->getStatus() < 2) {
                dp->setStatus(darkStatus2);
                dp->setEscapeTime(steps);
                if (id != 0x17D7) {
                    void *nick = pokemon_GetNicknamePtr(pk);
                    fightMsgctrlSetValue(0x16, nick);
                    fightMenuOpenMsg(0x500B);
                    fightMenuCloseMsg();
                }
            }
        }
    }
}

u16 _fight_kaisi_pre_trainer_intr_wzx_data_id_ary[5] = {0x90, 0x91, 0x92, 0x93, 0x94};
u8 _fight_kaisi_pre_trainer_intr_wzx_data_id_num = 5;
u16 _fight_kaisi_pre_trainer_intr_wzx_data_id;

extern "C" void fightActionFlowKaisiPreSubLoad(void) {
    u16 eid;
    void *t0;
    u32 w3;
    u32 w2;
    void *t1;
    void *seqA;
    u32 msg;
    void *seqB;
    u32 w1;
    u32 trainerId;
    fightFloor_GetFightFloorDataId(0);
    t0 = fightTargetGetPtrAsNowFightType(0xB, 0);
    seqA = fightTrainer_GetSequencePtr(t0);
    t1 = fightTargetGetPtrAsNowFightType(9, t0);
    seqB = fightTrainer_GetSequencePtr(t1);
    trainerId = fightTrainer_GetFightTrainerDataId(t1);
    w1 = fightFloor_GetSyoukaiWzxDataId(0);
    eid = ((u32 (*)(void *))fightFloor_GetEncountDataId)(0);
    w2 = fightEncountDataBiosGetSyoukaiWzxDataId(fightEncountDataBiosGetPtr(eid));
    w3 = fightTrainerDB_GetSyoukaiWzxDataId(trainerId);
    if (w3 == 0) {
        w3 = 0x5F;
    }
    msg = fightTrainerDB_GetSerihuMsgId(trainerId, 0);
    if (fightKind_CheckFightKind(0xA)) {
        msg = 0;
    }
    if (fightFloorIsNowEncountVirtualBattle(0) == 1) {
        Sequence_LoadWaza(seqA, 0x54, 4, 0);
        Sequence_LoadWaza(seqB, 0x55, 4, 0);
        Sequence_LoadWaza(seqA, 0x56, 4, 0);
    } else {
        fightFloorIsNowEncountOpeningVirtualBattle(0);
    }
    if (fightFloorIsNowEncountHostEnemyPokemonKime(0) == 1 && !fightTargetIsHostSide(t1, fightFloor_GetFightType(0))) {
        u32 i;
        for (i = 0; (u8)i < 2; i++) {
            void *p = ((void *(*)(void *, u8))fightTrainerGetValidFightOutPokemonPtr)(t1, i);
            if (p != 0) {
                void *seq = fightOutPokemon_GetSequencePtr((FightOutPokemon *)p);
                if (seq != 0) {
                    Sequence_LoadWaza(seq, 0x9F, 4, 0);
                }
            }
        }
    } else {
        if (w1 != 0) {
            if (w2 != 0) {
                Sequence_LoadWaza(seqB, w2, 4, 0);
            }
            Sequence_LoadWaza(seqB, w1, 4, 0);
            if (fightFloor_GetFightKindHostEnemyMsgFlag(0) == 1) {
                _fight_kaisi_pre_trainer_intr_wzx_data_id = (u16)HSD_Rand() % _fight_kaisi_pre_trainer_intr_wzx_data_id_num;
                _fight_kaisi_pre_trainer_intr_wzx_data_id = _fight_kaisi_pre_trainer_intr_wzx_data_id_ary[_fight_kaisi_pre_trainer_intr_wzx_data_id];
                Sequence_LoadWaza(seqB, _fight_kaisi_pre_trainer_intr_wzx_data_id, 4, 0);
            } else {
                _fight_kaisi_pre_trainer_intr_wzx_data_id = 0;
            }
        }
        if (msg != 0) {
            Sequence_LoadWaza(seqB, 0x5F, 4, 0);
        }
        if (fightFloor_GetFightKindHostEnemyMsgFlag(0) == 1) {
            Sequence_LoadWaza(seqB, w3, 4, 0);
        }
    }
}

extern "C" s32 fightActionFlowSyuuryouPost(void) {
    u32 side2;
    void *sp2;
    u32 j2;
    void *tr2;
    void *h3;
    u32 evoB;
    void *save;
    u16 evo;
    void *gc;
    void *tr;
    u16 evoA;
    void *h2;
    void *h;
    u32 i;
    void *pk;
    void *h4;
    u32 j;
    u32 base;
    u32 num;
    u32 side;
    void *sidep;
    void *sp;
    void *hero;
    num = (u8)fightFloor_GetFightTypeTrainerNum(0);
    if (fightGetFightResultId() == 1) {
        return 1;
    }
    gc = fightFloorGetGcHeroFightTrainerPtr(0);
    if (gc != 0) {
        hero = fightTrainer_GetHeroPtr(gc);
        if (hero != 0) {
            fightTrainerBackFightPokemonToTemotiPokemon(gc, 0);
            if (fightFloorIsGcHeroWin(0, fightGetFightResultId()) == 1) {
                if (fightFloor_GetFightKindGetExpFlag(0) == 1 && fightTrainerCheckCanGetExp(gc) == 1) {
                    for (i = 0; (u16)i < 6; i++) {
                        pk = heroGetStatus(hero, 3, i);
                        if (pokemonCheckFightOut(pk) && pokemonIsDarkPokemon(pk) != 1) {
                            sp = fightTrainerCheckTemotiPokemonFightEntry(gc, pk);
                            if (sp != 0 && fightPokemonCheckFightOut(sp) && fightPokemon_GetLevelUpFlag(sp)) {
                                evo = pokemonEvolutionCheck(pk, 0, 0, &evoA, (u16 *)&evoB);
                                if (evo != 0) {
                                    pokemonEvolutionAll(pk, evo, evoA, (u16 *)&evoB, hero, 1, 1, 0);
                                    fightMainWaitFrameEffect(10);
                                }
                            }
                        }
                    }
                }
                if (fightFloor_GetFightKindMonohiroiFlag(0) == 1) {
                    heroCheckSetMonohiroiAllTemotiPokemon(hero);
                }
                fightFloor_GetFightKindGetInfectPokerusFlag(0);
            }
            if (fightFloor_GetFightKindBackSaveDataFlag(0) == 1) {
                save = savedataGetStatus(0, 2);
                if (save != 0) {
                    u8 cnt = heroBiosGetMeetDarkPokemonCount(save);
                    heroBiosCopy(save, hero);
                    heroBiosSetMeetDarkPokemonCount(save, cnt);
                }
            }
        }
    }
    if (menuCBBios_CurrentlyWorkingToolBattle() == 1) {
        for (side = 0; (u16)side < 2; side++) {
            sidep = fightFloorGetValidFightSidePtr(0, side);
            if (sidep != 0) {
                base = (u16)side * num;
                for (j = 0; (u16)j < num; j++) {
                    tr = fightSideGetValidFightTrainerPtrU32(sidep, j);
                    if (tr != 0) {
                        fightTrainerBackFightPokemonToTemotiPokemon(tr, 0);
                        h = menuCBBios_GetHeroImmediately(j + base);
                        if (h != 0) {
                            h2 = fightTrainer_GetHeroPtr(tr);
                            if (h2 != 0) {
                                heroBiosCopy(h, h2);
                            }
                        }
                    }
                }
            }
        }
    }
    if ((u8)fightFloor_GetFightKind(0) == 6 || (u8)fightFloor_GetFightKind(0) == 7) {
        for (side2 = 0; (u16)side2 < 2; side2++) {
            sp2 = fightFloorGetValidFightSidePtr(0, side2);
            if (sp2 != 0) {
                for (j2 = 0; (u16)j2 < num; j2++) {
                    tr2 = fightSideGetValidFightTrainerPtrU32(sp2, j2);
                    if (tr2 != 0) {
                        if ((u8)fightFloor_GetFightKind(0) == 6 || (u8)fightFloor_GetFightKind(0) == 7) {
                            if (!fightTrainerIsGcHero(tr2)) {
                                continue;
                            }
                        }
                        fightTrainerBackFightPokemonToTemotiPokemon(tr2, 0);
                        h3 = fightGetMenuCtrlHero();
                        if (h3 != 0) {
                            h4 = fightTrainer_GetHeroPtr(tr2);
                            if (h4 != 0) {
                                heroBiosCopy(h3, h4);
                            }
                        }
                    }
                }
            }
        }
    }
    if (fightEnemyTrainerWazaSeqHdl != 0) {
        WazaSequence_Free(fightEnemyTrainerWazaSeqHdl);
    }
    return 1;
}

u32 fightEnemyTrainerWazaSeqHdl;

struct FIGHT_TRAINER;
extern "C" {
u8 fightOutPokemonIsGcHeroFightOutPokemon(void *);
u8 fightFloorIsNowEncountTuusinTaisen(void *);
void *fightTrainerGetPrefixNamePtr(void *);
}

static void _fightActionFlowKaisiNyuujouPokemonSubAppearMsg(FIGHT_TRAINER *trainer, FightOutPokemon *out, u16 number, u16 count, u16, u16 index, u8 mode) {
    void *name;
    bool host = fightOutPokemonIsGcHeroFightOutPokemon(out) == 1;
    bool link = fightFloorIsNowEncountTuusinTaisen(0) == 1;
    if (fightTrainerGetPrefixNamePtr(trainer) == 0 && host == 0) link = 1;
    name = pokemon_GetNicknamePtr((Pokemon *)fightOutPokemonGetPokemonPtr(out));
    if (mode == 0) {
        if (link == 1) {
            if (index == 0) {
                fightMsgctrlSetValue(0x14, name);
                fightMsgctrlSetValue(0x16, name);
            } else {
                fightMsgctrlSetValue(0x15, name);
                fightMsgctrlSetValue(0x17, name);
            }
        } else if (host == 1) {
            if (index == 0) {
                fightMsgctrlSetValue(0x15, name);
                fightMsgctrlSetValue(0x17, name);
            } else {
                fightMsgctrlSetValue(0x14, name);
                fightMsgctrlSetValue(0x16, name);
            }
        } else {
            if (index == 0) {
                fightMsgctrlSetValue(0x14, name);
                fightMsgctrlSetValue(0x16, name);
            } else {
                fightMsgctrlSetValue(0x15, name);
                fightMsgctrlSetValue(0x17, name);
            }
        }
    } else if (mode == 1) {
        u32 message;
        if (number <= 1 && count > 1) {
            if (link == 1) message = 0x4F54;
            else if (host == 1) message = 0x4F59;
            else message = 0x4F51;
        } else {
            fightMsgctrlSetValue(0x14, name);
            fightMsgctrlSetValue(0x16, name);
            if (link == 1) message = 0x4F53;
            else if (host == 1) message = 0x4F58;
            else message = 0x4F50;
        }
        fightMenuOpenMsg(message);
    }
}

extern "C" {
u32 fightActionDataBiosGetBuff(void *);
u8 fightFloor_GetFightTypeFightoutPokemonNum(void *);
u8 fightSideCheckValid(void *);
s32 fightSideGetDoFightTrainerCount(void *);
u8 fightTrainerGetDoFightOutFightOutPokemonCount(void *);
void *fightTrainer_GetFightPokemonPtr(void *, u16);
void menuFaceLoadFightPokemon(void *, s32, s32);
void *pokemonCreateSequence(void *);
void *fightTrainer_GetFightoutPokemonPtr(void *, u16);
void *fightPokemonGetPokemonPtr(void *);
void fightOutPokemonCreate(void *, void *, void *);
void fightOutPokemonRegWzxLoad(void *);
u8 fightFloor_GetFightKindDoZukanMitaFlag(void *);
void fightOutPokemonSetOnZukanFlag(void *, u8);
u16 pokemon_GetDarkpokemonDataId(void *);
void darkPokemonBiosSetFightFlag(u16, u8);
void battleGridAddPokemon(void *, void *);
void fightSeqVanishOff(void *);
void battleGridUpdate();
void fightOutPokemonDasuEffect(void *, void *, u8);
void Sequence_SetVisibility(void *, u8);
void battleGridStoreModelVisibilityFlags();
void fightTrainerBallThrowEffect(void *, void *, u8);
u32 Sequence_GetWaza(void *, u16, s32);
u8 WazaSequence_IsActive(u32);
void GSthreadSwitch();
void *fightTrainerGetNamePtr(void *);
void *fightFloor_GetAttackPokemonPtr(void *);
void fightMenuFightOutPokemonOpenStatusMenuStart(void *, u8, u8);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(void *, void *, u8, u8, u8);
void fightMenuFightOutPokemonCloseStatusMenu(void *, u8, u8);
}
u8 introBossFlag;

extern "C" s32 fightActionFlowKaisiNyuujouPokemon(void *actor) {
    u32 outCount;
    u8 type;
    void *side;
    void *out;
    u32 trainerCount;
    void *sequence;
    u32 sideCount;
    u16 i;
    u16 made;
    void *trainer;
    u16 encounter;
    u16 kind = fightActionDataBiosGetBuff(fightActionBiosGetFightActionDataPtr(actor));
    type = fightFloor_GetFightType(0);
    outCount = (u8)fightFloor_GetFightTypeFightoutPokemonNum(0);
    trainerCount = (u8)fightFloor_GetFightTypeTrainerNum(0);
    encounter = fightFloor_GetEncountDataId(0);
    side = fightTargetGetPtr(kind, 0, type);
    if (!fightSideCheckValid(side)) return 0;
    sideCount = fightSideGetDoFightTrainerCount(side);
    for (i = 0; i < trainerCount; ++i) {
        trainer = fightSideGetValidFightTrainerPtr(side, i);
        if (trainer != 0) {
            sequence = fightTrainer_GetSequencePtr(trainer);
            if (sequence != 0) {
                fightTrainerGetDoFightOutFightOutPokemonCount(trainer);
                made = 0;
                for (u16 party = 0; party < 6; ++party) {
                    if (!(made < outCount && made < 2)) break;
                    void *fightPokemon = fightTrainer_GetFightPokemonPtr(trainer, party);
                    if (fightPokemonCheckFightOut(fightPokemon)) {
                        menuFaceLoadFightPokemon(fightPokemon, 0, 0);
                        void *model = pokemonCreateSequence(fightPokemon);
                        out = fightTrainer_GetFightoutPokemonPtr(trainer, party);
                        void *pokemon = fightPokemonGetPokemonPtr(fightPokemon);
                        fightOutPokemonCreate(out, fightPokemon, model);
                        ++made;
                        fightOutPokemonRegWzxLoad(out);
                        if (fightFloor_GetFightKindDoZukanMitaFlag(0) == 1 && fightOutPokemonIsGcHeroFightOutPokemon(out) == 0) {
                            fightOutPokemonSetOnZukanFlag(out, 0);
                            if (encounter != 0xD9 && encounter != 0x15E && pokemonIsDarkPokemon(pokemon) == 1) {
                                darkPokemonBiosSetFightFlag(pokemon_GetDarkpokemonDataId(pokemon), 0);
                            }
                        }
                        battleGridAddPokemon(sequence, model);
                    }
                }
            }
        }
    }
    if (fightFloorIsNowEncountHostEnemyPokemonKime(0) == 1 && fightTargetIsHostSide(trainer, fightFloor_GetFightType(0)) == 0) {
        for (u16 i = 0; i < trainerCount; ++i) {
            for (u16 j = 0; j < outCount; ++j) {
                void *pokemon = fightTrainerGetValidFightOutPokemonPtr(trainer, j);
                if (pokemon != 0) {
                    fightSeqVanishOff(pokemon);
                    battleGridUpdate();
                }
            }
        }
    } else if (fightFloorIsNowEncountOpeningVirtualBattle(0) == 1) {
        for (u16 i = 0; i < trainerCount; ++i) {
            void *current = fightSideGetValidFightTrainerPtr(side, i);
            if (current != 0) {
                for (u16 j = 0; j < outCount; ++j) {
                    void *pokemon = fightTrainerGetValidFightOutPokemonPtr(current, j);
                    if (pokemon != 0) {
                        fightOutPokemonDasuEffect(current, pokemon, 0);
                        void *model = fightOutPokemon_GetSequencePtr((FightOutPokemon *)pokemon);
                        if (model != 0) {
                            Sequence_SetVisibility(model, 1);
                            battleGridStoreModelVisibilityFlags();
                            battleGridUpdate();
                        }
                    }
                }
            }
        }
    } else {
        for (u16 i = 0; i < trainerCount; ++i) {
            void *current = fightSideGetValidFightTrainerPtr(side, i);
            if (current != 0) {
                u16 j;
                for (j = 0; j < outCount; ++j) {
                    out = fightTrainerGetValidFightOutPokemonPtr(current, j);
                    if (out != 0) break;
                }
                fightTrainerBallThrowEffect(current, out, 0);
                for (j = 0; j < outCount; ++j) {
                    out = fightTrainerGetValidFightOutPokemonPtr(current, j);
                    if (out != 0) fightOutPokemonDasuEffect(current, out, 0);
                }
            }
        }
        for (u16 i = 0; i < trainerCount; ++i) {
            void *current = fightSideGetValidFightTrainerPtr(side, i);
            if (current != 0) {
                u32 intro = fightTrainerDB_GetSyoukaiWzxDataId(fightTrainer_GetFightTrainerDataId(current));
                u8 count = fightTrainerGetDoFightOutFightOutPokemonCount(current);
                u16 j;
                for (j = 0; j < outCount; ++j) {
                    out = fightTrainerGetValidFightOutPokemonPtr(current, j);
                    if (out != 0) _fightActionFlowKaisiNyuujouPokemonSubAppearMsg((FIGHT_TRAINER *)current, (FightOutPokemon *)out, sideCount, count, i, j, 0);
                }
                for (j = 0; j < outCount; ++j) {
                    out = fightTrainerGetValidFightOutPokemonPtr(current, j);
                    if (out != 0) break;
                }
                if (introBossFlag == 1) {
                    u32 handle = Sequence_GetWaza(sequence, intro, 4);
                    while (WazaSequence_IsActive(handle)) GSthreadSwitch();
                    WazaSequence_Free(handle);
                    introBossFlag = 0;
                    fightMenuCloseMsg();
                }
                battleGridUpdate();
                fightTrainerBallThrowEffect(current, out, 1);
                fightMsgctrlSetValue(0x22, fightTrainerGetPrefixNamePtr(current));
                fightMsgctrlSetValue(0x23, fightTrainerGetNamePtr(current));
                fightMsgctrlSetValue(0x25, fightTrainerGetNamePtr(current));
                _fightActionFlowKaisiNyuujouPokemonSubAppearMsg((FIGHT_TRAINER *)current, (FightOutPokemon *)out, sideCount, count, i, j, 1);
                fightTrainerBallThrowEffect(current, out, 2);
                fightOutPokemonDasuEffect(current, out, 1);
                fightOutPokemonDasuEffect(current, out, 2);
                for (j = 0; j < outCount; ++j) {
                    out = fightTrainerGetValidFightOutPokemonPtr(current, j);
                    if (out != 0) {
                        void *attack = fightFloor_GetAttackPokemonPtr(0);
                        fightFloor_SetAttackPokemonPtr(0, out);
                        if (fightOutPokemonIsGcHeroFightOutPokemon(out) == 0) {
                            fightMenuFightOutPokemonOpenStatusMenuStart(out, type, 0);
                            fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, out, type, 0, 1);
                        } else {
                            fightMenuFightOutPokemonOpenStatusMenuStart(out, type, 1);
                            fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, out, type, 0, 1);
                        }
                        fightOutPokemonDasuEffect(current, out, 3);
                        fightOutPokemonDasuEffect(current, out, 4);
                        fightMenuFightOutPokemonCloseStatusMenu(out, type, 0);
                        fightFloor_SetAttackPokemonPtr(0, attack);
                    }
                }
            }
        }
        fightMenuCloseMsg();
        for (u16 i = 0; i < trainerCount; ++i) {
            void *current = fightSideGetValidFightTrainerPtr(side, i);
            if (current != 0) {
                u16 j;
                for (j = 0; j < outCount; ++j) {
                    out = fightTrainerGetValidFightOutPokemonPtr(current, j);
                    if (out != 0) break;
                }
                fightTrainerBallThrowEffect(current, out, 3);
                for (j = 0; j < outCount; ++j) {
                    out = fightTrainerGetValidFightOutPokemonPtr(current, j);
                    if (out != 0) fightOutPokemonDasuEffect(current, out, 5);
                }
            }
        }
    }
    return 1;
}

u8 deckDataVirtualDB_GetAllyJoutai(u16,u8);
u8 deckDataVirtualDB_GetEnemyJoutai(u16,u8);
extern "C" {
u8 fightFloor_GetFightTypeEntryPokemonNum(void *);
u32 fightSide_GetFightSideDataId(void *);
void *fightSide_GetFightTrainerPtr(void *,u8);
u32 fightEncountDataBiosGetFightTrainerDataId(void *,u8);
s32 fightEncountDataBiosGetGSInputDevice(void *,u8);
u8 fightTrainerCheckTrainerDataIdValid(u32,s32);
u8 fightTrainerDB_GetKindDataId(u32);
u8 fightFloor_GetTrainer(void *);
void fightTrainerCreateFightTrainerDataIdToHero(u32,s32,void *,u32);
void *fightTrainerCreateSequence(u32);
void fightTrainerCreate(void *,void *,u32,s32,void *);
u8 fightTrainerCheckValid(void *);
void fightTrainerSortFightTrainerDataIdToHeroTemotiPokemon(void *,u32,u32);
u8 pokemonCheckValid(void *);
u16 fightEncountDataBiosGetDiskId(void *);
void fightPokemonCreate(void *,void *,void *,u32);
u32 fightFloorGetFightPokemonEntryCntInc(void *);
u8 fightFloor_GetFightKindGetFriendFlag(void *);
u8 fightFloor_GetFightKindBossFlag(void *);
void fightPokemonGetFriendFormPokemonFriendFilterId(void *,u32);
void fightSideGetFightTrainerGridParam(u32,u8,u8,u8 *,u8 *);
void battleGridAddTrainer(void *,u8,u8);

static inline u16 getDisk(){return fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));}
static inline void *getFightPokemon(void *t,u16 m){return fightTrainer_GetFightPokemonPtr(t,m);}
s32 fightActionFlowKaisiNyuujouTrainer(void *actor) {
    u32 hero[0x978/4];
    u8 gridX;
    void *data;
    int i;
    u8 idx;
    void *sequence;
    int j;
    void *trainer;
    u16 target;
    u32 trainerId;
    u8 gridY;
    u8 sideCount;
    u8 type;
    s32 offset;
    u32 trainerCount;
    u32 sideId;
    u32 entryCount;
    u32 outCount;
    u8 enemy;
    s32 input;
    void *side;
    void *party;
    void *seq;
    s8 made;
    u8 index;
    target=fightActionDataBiosGetBuff(fightActionBiosGetFightActionDataPtr(actor));
    data=fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0));
    type=fightFloor_GetFightType(0);
    trainerCount=(u8)fightFloor_GetFightTypeTrainerNum(0);
    entryCount=fightFloor_GetFightTypeEntryPokemonNum(0);
    outCount=fightFloor_GetFightTypeFightoutPokemonNum(0);
    side=fightTargetGetPtr(target,0,type);
    if(!fightSideCheckValid(side))return 0;
    if(target!=4)enemy=1;else enemy=0;
    sideId=fightSide_GetFightSideDataId(side);
    offset=enemy*trainerCount;
    for(i=0;(u8)i<(s32)trainerCount;++i) {
        trainer=fightSide_GetFightTrainerPtr(side,i);
        index=(u8)i+offset;
        trainerId=fightEncountDataBiosGetFightTrainerDataId(data,index);
        input=fightEncountDataBiosGetGSInputDevice(data,index);
        if(fightTrainerCheckTrainerDataIdValid(trainerId,input)) {
            if(menuCBBios_CurrentlyWorkingToolBattle()==1)heroBiosCopy(hero,menuCBBios_GetHeroImmediately(index));
            else if(((u8)fightFloor_GetFightKind(0)==6 || (u8)fightFloor_GetFightKind(0)==7) && fightTrainerDB_GetKindDataId(trainerId)==1)heroBiosCopy(hero,fightGetMenuCtrlHero());
            else fightTrainerCreateFightTrainerDataIdToHero(trainerId,input,hero,0);
            seq=fightTrainerCreateSequence(trainerId);
            fightTrainerCreate(trainer,hero,trainerId,input,seq);
            party=fightTrainer_GetHeroPtr(trainer);
            if(fightTrainerCheckValid(trainer)) {
                fightTrainerSortFightTrainerDataIdToHeroTemotiPokemon(trainer,entryCount,outCount);
                if(fightFloor_GetTrainer(0)==0 && fightTrainerIsGcHero(trainer)==0)entryCount=1;
                made=0;
                for(u8 slot=0;slot<6;++slot) {
                    if(!(made<(s32)outCount && made<(u16)entryCount && made<6))break;
                    Pokemon *pokemon=(Pokemon *)heroGetStatus(party,3,slot);
                    if(pokemonCheckFightOut(pokemon) && !fightTrainerCheckTemotiPokemonFightEntry(trainer,pokemon)) {
                        if(fightFloorIsNowEncountVirtualBattle(0)==1 || fightFloorIsNowEncountOpeningVirtualBattle(0)==1) {
                            u16 disk=fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));
                            u8 condition;
                            if(fightTargetIsHostSide(trainer,fightFloor_GetFightType(0))==1)condition=deckDataVirtualDB_GetAllyJoutai(disk,slot);
                            else condition=deckDataVirtualDB_GetEnemyJoutai(disk,slot);
                            pokemon->setCondition(condition);
                        }
                        void *fightPokemon=fightTrainer_GetFightPokemonPtr(trainer,made);
                        fightPokemonCreate(trainer,fightPokemon,pokemon,fightFloorGetFightPokemonEntryCntInc(0));
                        if(fightFloor_GetFightKindGetFriendFlag(0)==1 && fightFloor_GetFightKindBossFlag(0)==1 && fightTrainerIsGcHero(trainer)==1)fightPokemonGetFriendFormPokemonFriendFilterId(fightPokemon,3);
                        ++made;
                    }
                }
                for(u8 slot=0;slot<6;++slot) {
                    if(!(made<(u16)entryCount && made<6))break;
                    Pokemon *pokemon=(Pokemon *)heroGetStatus(party,3,slot);
                    if(pokemonCheckValid(pokemon) && !fightTrainerCheckTemotiPokemonFightEntry(trainer,pokemon)) {
                        if(fightFloorIsNowEncountVirtualBattle(0)==1 || fightFloorIsNowEncountOpeningVirtualBattle(0)==1) {
                            u16 disk=getDisk();
                            u8 condition;
                            if(fightTargetIsHostSide(trainer,fightFloor_GetFightType(0))==1)condition=deckDataVirtualDB_GetAllyJoutai(disk,slot);
                            else condition=deckDataVirtualDB_GetEnemyJoutai(disk,slot);
                            pokemon->setCondition(condition);
                        }
                        void *fightPokemon=getFightPokemon(trainer,made);
                        fightPokemonCreate(trainer,fightPokemon,pokemon,fightFloorGetFightPokemonEntryCntInc(0));
                        if(fightFloor_GetFightKindGetFriendFlag(0)==1 && fightFloor_GetFightKindBossFlag(0)==1 && fightTrainerIsGcHero(trainer)==1)fightPokemonGetFriendFormPokemonFriendFilterId(fightPokemon,3);
                        ++made;
                    }
                }
            }
        }
    }
    sideCount=fightSideGetDoFightTrainerCount(side);
    for(j=0;(u8)j<(s32)trainerCount;++j) {
        idx=j;
        trainer=fightSideGetValidFightTrainerPtr(side,idx);
        if(trainer!=0) {
            sequence=fightTrainer_GetSequencePtr(trainer);
            if(sequence!=0) {
                fightSideGetFightTrainerGridParam(sideId,sideCount,idx,&gridX,&gridY);
                battleGridAddTrainer(sequence,gridX,gridY);
                battleGridUpdate();
                Sequence_SetVisibility(sequence,1);
                battleGridStoreModelVisibilityFlags();
            }
        }
    }
    return 1;
}
}

extern "C" {
u32 GSmsgGetLength(u32);
void GSsndPlayVolume(u32,u32,u32,u32);
void WazaSequence_Start(u32,u32);
void WazaSequence_Stop(u32);
void Sequence_Talk(void *);
void battleCameraStartRandom(u32);
void fadeSet(s32,f32);
void fightMainSetAllDispFlag(u8);
u32 fightFloor_GetBgmSndId(void *);
void soundOpenPlay(u32,u32,u32);
void fightMenuOpenTrainerMsg(u32);
void *fightOutPokemonGetNamePtr(void *);
u16 fightOutPokemonGetVoiceSndId(void *);
u32 fightOutPokemon_GetKanseiSndId(void *);
extern u8 WildPokemonCatchFlag;

s32 fightActionFlowKaisiPre() {
    u32 encounterIntro;
    u16 encounter;
    u32 trainerIntro;
    u8 i;
    void *host;
    void *hostSequence;
    u32 message;
    void *pokemonSequence;
    void *enemy;
    u32 stageIntro;
    void *data;
    u8 virtualCanceled;
    u32 greeting;
    void *pokemon;
    s32 greetingFrames;
    u32 trainerId;
    void *enemySequence;
    bool canceled;
    u16 disk;
    canceled=false;
    virtualCanceled=0;
    fightFloor_GetFightFloorDataId(0);
    host=fightTargetGetPtrAsNowFightType(0xB,0);
    hostSequence=fightTrainer_GetSequencePtr(host);
    enemy=fightTargetGetPtrAsNowFightType(9,host);
    enemySequence=fightTrainer_GetSequencePtr(enemy);
    trainerId=fightTrainer_GetFightTrainerDataId(enemy);
    stageIntro=fightFloor_GetSyoukaiWzxDataId(0);
    encounter=((u32 (*)(void *))fightFloor_GetEncountDataId)(0);
    data=fightEncountDataBiosGetPtr(encounter);
    disk=fightEncountDataBiosGetDiskId(data);
    encounterIntro=fightEncountDataBiosGetSyoukaiWzxDataId(data);
    trainerIntro=fightTrainerDB_GetSyoukaiWzxDataId(trainerId);
    if(trainerIntro==0)trainerIntro=0x5F;
    greeting=fightTrainerDB_GetSerihuMsgId(trainerId,0);
    greetingFrames=GSmsgGetLength(greeting)*5;
    if(fightKind_CheckFightKind(0xA))greeting=0;
    if(fightFloorIsNowEncountOpeningVirtualBattle(0)!=1) {
        if(fightFloorIsNowEncountVirtualBattle(0)==1) {
            Sequence_SetVisibility(enemySequence,0);
            Sequence_SetVisibility(hostSequence,1);
            battleGridStoreModelVisibilityFlags();
            u32 handle=Sequence_GetWaza(hostSequence,0x54,4);
            WazaSequence_Start(handle,1);
            while(WazaSequence_IsActive(handle)) {
                if(_fightActionFlowKaisiPreSubCheckVirtualDiskCancel(disk)) {
                    virtualCanceled=1;
                    goto virtualIntroFinished;
                }
                GSthreadSwitch();
            }
            Sequence_SetVisibility(enemySequence,1);
            battleGridStoreModelVisibilityFlags();
            handle=Sequence_GetWaza(enemySequence,0x55,4);
            WazaSequence_Start(handle,1);
            if(fightFloor_GetFightKindHostEnemyMsgFlag(0)==1) {
                fightMsgctrlSetValue(0x22,fightTrainerGetPrefixNamePtr(enemy));
                fightMsgctrlSetValue(0x23,fightTrainerGetNamePtr(enemy));
                fightMenuOpenTrainerMsg(0x4F4D);
            }
            while(WazaSequence_IsActive(handle)) {
                if(_fightActionFlowKaisiPreSubCheckVirtualDiskCancel(disk)) {
                    fightMenuCloseMsg();
                    virtualCanceled=1;
                    goto virtualIntroFinished;
                }
                GSthreadSwitch();
            }
            if(fightFloor_GetFightKindHostEnemyMsgFlag(0)==1)fightMenuCloseMsg();
            fightMainSetAllDispFlag(1);
            battleGridStoreModelVisibilityFlags();
            handle=Sequence_GetWaza(hostSequence,0x56,4);
            WazaSequence_Start(handle,1);
            while(WazaSequence_IsActive(handle)) {
                if(_fightActionFlowKaisiPreSubCheckVirtualDiskCancel(disk)) {virtualCanceled=1;break;}
                GSthreadSwitch();
            }
        virtualIntroFinished:
            if(virtualCanceled==1) {
                fadeSet(3,0.5f);fadeCheck(1);
                fightMainSetAllDispFlag(1);battleGridStoreModelVisibilityFlags();
                WazaSequence_Stop(Sequence_GetWaza(hostSequence,0x54,4));
                WazaSequence_Stop(Sequence_GetWaza(enemySequence,0x55,4));
                WazaSequence_Stop(Sequence_GetWaza(hostSequence,0x56,4));
                battleCameraStartRandom(1);fadeSet(2,0.5f);canceled=false;
            }
            WazaSequence_Free(Sequence_GetWaza(hostSequence,0x54,4));
            WazaSequence_Free(Sequence_GetWaza(enemySequence,0x55,4));
            WazaSequence_Free(Sequence_GetWaza(hostSequence,0x56,4));
            u32 bgm=fightFloor_GetBgmSndId(0);
            if(bgm!=0)soundOpenPlay(bgm,0,255);
        } else {
            if(stageIntro!=0) {
                if(encounterIntro!=0)WazaSequence_Start(Sequence_GetWaza(enemySequence,encounterIntro,4),1);
                u32 handle=Sequence_GetWaza(enemySequence,stageIntro,4);
                WazaSequence_Start(handle,1);
                for(;;) {
                    if(_fightActionFlowKaisiPreSubCheckCancel(&canceled)==1)goto stageIntroFinished;
                    if(!WazaSequence_IsActive(handle))break;
                    GSthreadSwitch();
                }
                if(fightFloor_GetFightKindHostEnemyMsgFlag(0)==1) {
                    handle=Sequence_GetWaza(enemySequence,_fight_kaisi_pre_trainer_intr_wzx_data_id,4);
                    WazaSequence_Start(handle,1);
                    for(;;) {
                        if(_fightActionFlowKaisiPreSubCheckCancel(&canceled)==1)goto stageIntroFinished;
                        if(!WazaSequence_IsActive(handle))break;
                        GSthreadSwitch();
                    }
                }
                if(encounterIntro!=0) {
                    handle=Sequence_GetWaza(enemySequence,encounterIntro,4);
                    for(;;) {
                        if(_fightActionFlowKaisiPreSubCheckCancel(&canceled)==1)break;
                        if(!WazaSequence_IsActive(handle))break;
                        GSthreadSwitch();
                    }
                }
            }
        stageIntroFinished:
            if(fightFloorIsNowEncountHostEnemyPokemonKime(0)==1 && fightTargetIsHostSide(enemy,fightFloor_GetFightType(0))==0) {
                if((u8)fightFloor_GetFightKind(0)==0xC) {message=0x4FF6;WildPokemonCatchFlag=0;}
                else message=0x4FFD;
                if(encounter==0xD9 || encounter==0x191)message=0;
                for(i=0;i<2;++i) {
                    pokemon=fightTrainerGetValidFightOutPokemonPtr(enemy,i);
                    if(pokemon!=0) {
                        pokemonSequence=fightOutPokemon_GetSequencePtr((FightOutPokemon *)pokemon);
                        if(pokemonSequence!=0) {
                            u32 handle=Sequence_GetWaza(pokemonSequence,0x9F,4);
                            if(message!=0) {fightMsgctrlSetValue(0x16,fightOutPokemonGetNamePtr(pokemon));fightMenuOpenMsg(message);}
                            u32 bgm=fightFloor_GetBgmSndId(0);
                            if(bgm!=0)soundOpenPlay(bgm,0,255);
                            WazaSequence_Start(handle,1);
                            GSsndPlayVolume(fightOutPokemonGetVoiceSndId(pokemon),0,255,0);
                            if(fightFloor_GetEnvSndId(0)!=0)GSsndPlayVolume(fightOutPokemon_GetKanseiSndId(pokemon),0,127,0);
                            while(WazaSequence_IsActive(handle))GSthreadSwitch();
                            if(message!=0)fightMenuCloseMsg();
                            break;
                        }
                    }
                }
            } else {
                if(canceled==1) {
                    fadeSet(3,0.5f);fadeCheck(1);
                    if(encounterIntro!=0)WazaSequence_Stop(Sequence_GetWaza(enemySequence,encounterIntro,4));
                    WazaSequence_Stop(Sequence_GetWaza(enemySequence,stageIntro,4));
                    if(fightFloor_GetFightKindHostEnemyMsgFlag(0)==1)WazaSequence_Stop(Sequence_GetWaza(enemySequence,_fight_kaisi_pre_trainer_intr_wzx_data_id,4));
                }
                if(greeting!=0) {
                    u32 handle=Sequence_GetWaza(enemySequence,0x5F,4);
                    WazaSequence_Start(handle,1);
                    if(canceled==1) {fadeSet(2,0.5f);canceled=false;}
                    Sequence_Talk(enemySequence);
                    fightMenuOpenTrainerMsg(greeting);fightMainWaitFrame(greetingFrames);fightMenuCloseMsg();
                    while(WazaSequence_IsActive(handle))GSthreadSwitch();
                }
                u32 bgm=fightFloor_GetBgmSndId(0);
                if(bgm!=0)soundOpenPlay(bgm,0,255);
                if(fightFloor_GetFightKindHostEnemyMsgFlag(0)==1) {
                    fightMsgctrlSetValue(0x22,fightTrainerGetPrefixNamePtr(enemy));
                    fightMsgctrlSetValue(0x23,fightTrainerGetNamePtr(enemy));
                    u32 handle=Sequence_GetWaza(enemySequence,trainerIntro,4);
                    WazaSequence_Start(handle,1);
                    if(canceled==1) {fadeSet(2,0.5f);canceled=false;}
                    fightMenuOpenTrainerMsg(0x4F4D);
                    if(trainerIntro==0x5F) {
                        while(WazaSequence_IsActive(handle))GSthreadSwitch();
                        introBossFlag=0;fightMenuCloseMsg();
                    } else introBossFlag=1;
                }
            }
            if(canceled==1)fadeSet(2,0.5f);
            if(stageIntro!=0) {
                if(encounterIntro!=0)WazaSequence_Free(Sequence_GetWaza(enemySequence,encounterIntro,4));
                WazaSequence_Free(Sequence_GetWaza(enemySequence,stageIntro,4));
                if(fightFloor_GetFightKindHostEnemyMsgFlag(0)==1)WazaSequence_Free(Sequence_GetWaza(enemySequence,_fight_kaisi_pre_trainer_intr_wzx_data_id,4));
            }
            if(greeting!=0)WazaSequence_Free(Sequence_GetWaza(enemySequence,0x5F,4));
            if(fightFloor_GetFightKindHostEnemyMsgFlag(0)==1 && trainerIntro==0x5F)WazaSequence_Free(Sequence_GetWaza(enemySequence,trainerIntro,4));
            if(fightFloorIsNowEncountHostEnemyPokemonKime(0)==1 && fightTargetIsHostSide(enemy,fightFloor_GetFightType(0))==0) {
                for(i=0;i<2;++i)WazaSequence_Free(Sequence_GetWaza(pokemonSequence,0x9F,4));
            }
        }
    }
    return 1;
}
}

u8 deckDataVirtualDB_GetTurnLimit(u16);
void deckDataVirtualDB_SetFlagData(u16,bool);
u8 fightSeqItemSeq_AddPoke(Pokemon *,u8,FIGHT_TRAINER *,Hero *);
extern "C" {
u16 *GSmsgGetGSchar(u16);
void GSflagSet(u32,u32);
void *GSthreadCreate(u32,u32,u32,u32,u32,void (*)());
u8 GSthreadIsRunning(void *);
void GSthreadSetArgs(void *,u32,...);
void GSthreadSetName(void *,const char *);
void soundOpenPlayME();
u32 floorGetCurrentGroupID();
s32 battleCameraIsSimple();
void battleCameraStop();
void fightMainAllCamera(s32,u32);
u8 wazaSequenceSysLastWazaIsImpactPoint(u32);
u16 fightTrainerDB_GetPkxDataId(u32);
u16 fightTrainerDB_GetName(u32);
u8 fightTrainer_GetNigeruCount(void *);
u16 fightFloor_GetTurnCount(void *);
u8 fightFloor_GetFightKindGetOkaneFlag(void *);
u8 fightFloor_GetFightKindGetNekoniKobanFlag(void *);
u8 fightEncountDataBiosGetFightKind(void *);
void heroMovePoolCounter(u32,s32);
u8 fightFloor_GetStockPokemonNum(void *);
Pokemon *fightFloor_GetStockPokemonPtr(void *,u8);
u8 fightFloor_GetStockPokemonBallID(void *,u8);
u32 fightFloor_GetEncountFloorId();
void fightFloor_SetStockPokemonNum(void *,u8);
u16 darkpokemonBiosGetScenarioNum();
s32 darkPokemonGetSnatchSuccessNum(u16);
u8 fightFloorGetFightTrainerFightPokemonPtrAry(void *,void *,void **,u32,u32);
void fightCloseAllMenu(u8);
extern u8 WAZA_OkodukaiCheck[],WAZA_KobanCheck[];
extern void *_gSoundThread;

s32 fightActionFlowSyuuryou(void *actor) {
    void *party[24];
    u8 retainSequence=0;
    void *data=fightEncountDataBiosGetPtr(fightGetFightEncountDataId());
    u16 disk=fightEncountDataBiosGetDiskId(data);
    u16 result=fightActionDataBiosGetBuff(fightActionBiosGetFightActionDataPtr(actor));
    void *host=fightTargetGetPtrAsNowFightType(0xB,0);
    void *enemy=fightTargetGetPtrAsNowFightType(9,host);
    u32 trainerId=fightTrainer_GetFightTrainerDataId(enemy);
    u16 model=fightTrainerDB_GetPkxDataId(trainerId);
    u16 trainerName=fightTrainerDB_GetName(trainerId);
    fightTrainer_GetFightPokemonPtr(enemy,0);
    void *sequence=fightTrainer_GetSequencePtr(enemy);
    u16 loseMotion=0x5A;
    if(model==0x2A)loseMotion=0x13D;
    u16 winningMessage=fightTrainerDB_GetSerihuMsgId(trainerId,1);
    u16 losingMessage;
    if(fightTrainer_GetNigeruCount(enemy)==0)losingMessage=fightTrainerDB_GetSerihuMsgId(trainerId,2);
    else {
        losingMessage=fightTrainerDB_GetSerihuMsgId(trainerId,3);
        if(losingMessage==0)losingMessage=fightTrainerDB_GetSerihuMsgId(trainerId,2);
    }
    u32 victoryMessage;
    switch(fightFloor_GetEncountDataId(0)) {
    case 0xD9:victoryMessage=0x5006;break;
    case 0x15E:victoryMessage=0x5007;break;
    default:victoryMessage=0x4F4C;break;
    }
    fightMsgctrlSetValue(0x22,fightTrainerGetPrefixNamePtr(enemy));
    fightMsgctrlSetValue(0x23,fightTrainerGetNamePtr(enemy));
    fightMsgctrlSetValue(0x13,fightTrainerGetNamePtr(host));
    fightMsgctrlSetValue(0x25,fightTrainerGetNamePtr(enemy));
    u32 handle;
    s32 oldCamera;
    if(menuCBBios_CurrentlyWorkingToolBattle()==0 || fightKind_CheckFightKind(0x11)) {
        if(result==2) {
            if((u8)fightFloor_GetTrainer(0)==0) {
                fightMainAllCamera(battleCameraIsSimple(),0);fightMenuCloseMsg();
            } else {
                Sequence_LoadWaza(sequence,loseMotion,4,0);
                oldCamera=battleCameraIsSimple();
                fightMsgctrlSetValue(0x5D,0);
                _gSoundThread=GSthreadCreate(0x15,floorGetCurrentGroupID(),0x2000,1,1,soundOpenPlayME);
                if(_gSoundThread!=0) {GSthreadSetArgs(_gSoundThread,3,0x36A,0,255);GSthreadSetName(_gSoundThread,"fightME");}
                if(fightFloor_GetEnvSndId(0)!=0)GSsndPlayVolume(0x549,0,255,0);
                fightMainWaitFrame(50);fightMenuOpenMsg(victoryMessage);fightMenuCloseMsg();
                if(_gSoundThread!=0)while(GSthreadIsRunning(_gSoundThread))GSthreadSwitch();
                retainSequence=1;
                handle=Sequence_GetWaza(sequence,loseMotion,4);
                WazaSequence_Start(handle,1);Sequence_Talk(sequence);
                fightMenuOpenTrainerMsg(losingMessage);fightMainWaitFrame(0);fightMenuCloseMsg();
                while(wazaSequenceSysLastWazaIsImpactPoint(2)!=1)GSthreadSwitch();
                battleCameraStop();fightMainAllCamera(oldCamera,0);
            }
            if((fightFloorIsNowEncountVirtualBattle(0)==1 || fightFloorIsNowEncountOpeningVirtualBattle(0)==1) && deckDataVirtualDB_GetTurnLimit(disk)!=0) {
                u8 limit=deckDataVirtualDB_GetTurnLimit(disk);
                if(fightFloor_GetTurnCount(0)>limit)fightFloorSetFightResultId(0,3);
            }
        } else if(result==3) {
            handle=0;
            if((u8)fightFloor_GetTrainer(0)!=0) {
                retainSequence=1;handle=Sequence_LoadWaza(sequence,0x59,4,0);oldCamera=battleCameraIsSimple();
            }
            if(fightFloor_GetEnvSndId(0)!=0)GSsndPlayVolume(0x54A,0,255,0);
            fightMenuOpenMsg(0x4E38);fightMenuCloseMsg();
            if((u8)fightFloor_GetTrainer(0)!=0) {
                WazaSequence_Start(handle,1);Sequence_Talk(sequence);
                fightMenuOpenTrainerMsg(winningMessage);fightMainWaitFrame(0);fightMenuCloseMsg();
                while(wazaSequenceSysLastWazaIsImpactPoint(2)!=1)GSthreadSwitch();
                battleCameraStop();fightMainAllCamera(oldCamera,0);
            }
            fightMenuOpenMsg(0x4E39);fightMenuCloseMsg();
        } else if((u16)(result-4)>1 && (result==7 || result==6)) {
            if(fightFloor_GetEnvSndId(0)!=0)GSsndPlayVolume(0x54B,0,255,0);
            fightMenuOpenMsg(0x4F26);fightMainWaitFrame(64);fightMenuCloseMsg();
        }
    }
    if(fightFloorIsGcHeroWin(0,fightGetFightResultId())==1) {
        u8 turns=fightFloor_GetTurnCount(0);
        if(turns>8)turns=8;
        heroMovePoolCounter(1,turns*30);
        if(fightFloor_GetFightKindGetOkaneFlag(0)==1)fightSeqExec(actor,WAZA_OkodukaiCheck,0);
        if(fightFloor_GetFightKindGetNekoniKobanFlag(0)==1 && (fightEncountDataBiosGetFightKind(data)!=0xC || WildPokemonCatchFlag!=1))fightSeqExec(actor,WAZA_KobanCheck,0);
        if(fightFloorIsNowEncountVirtualBattle(0)==1)deckDataVirtualDB_SetFlagData(disk,true);
        u8 count=fightFloor_GetStockPokemonNum(0);
        u8 remaining=count;
        for(u8 i=0;i<count;++i) {
            Pokemon *pokemon=fightFloor_GetStockPokemonPtr(0,i);
            if(pokemon!=0) {
                DarkPokemon *dark=pokemon->getDarkPokemon();
                u8 ball=fightFloor_GetStockPokemonBallID(0,i);
                dark->setStatus(darkStatus3);
                dark->setSnatchTime(Hero::getHeroPtr()->getFootStep());
                dark->setOrgTrainer(trainerId);
                dark->setTrainerName(GSmsgGetGSchar(trainerName));
                dark->setCatchBallID(ball);
                u16 floor=dark->getCatchFloorId();
                if(floor==0xB5 || floor==0)dark->setCatchFloorId(fightFloor_GetEncountFloorId());
                u32 message=0x5002;
                if(fightSeqItemSeq_AddPoke(pokemon,ball,(FIGHT_TRAINER *)host,(Hero *)fightTrainer_GetHeroPtr(host))==1)message=0x4F86;
                fightMsgctrlSetValue(0x16,pokemon_GetNicknamePtr(pokemon));
                fightMenuOpenMsg(message);fightMenuCloseMsg();
                if(--remaining==0)break;
            }
        }
        fightFloor_SetStockPokemonNum(0,0);
        u16 scenario=darkpokemonBiosGetScenarioNum();
        if(darkPokemonGetSnatchSuccessNum(scenario)==scenario-1)GSflagSet(0x4A7,0);
    } else {
        if((u8)fightFloor_GetFightKind(0)==0x10 || fightFloor_GetEncountDataId(0)==0x73) {GSflagSet(0x5AA,0);GSflagSet(0x5AC,0);GSflagSet(0x5AB,0);}
        if(fightFloor_GetEncountDataId(0)!=0x15D) {
            u8 count=fightFloor_GetStockPokemonNum(0);
            for(u8 i=0;i<count;++i) {
                Pokemon *pokemon=fightFloor_GetStockPokemonPtr(0,i);
                if(pokemon!=0) {
                    u16 darkId=pokemon->getDarkPokemon()->getDarkPokemonID();
                    if(darkId!=0)_darkPokemonSetUnderTaker(DeckDarkPokemon::getDeckDarkPokemonObj(darkId),pokemon,trainerName);
                }
            }
        }
    }
    u8 count=fightFloorGetFightTrainerFightPokemonPtrAry(0,enemy,party,1,0);
    if(fightFloor_GetEncountDataId(0)!=0x15D) {
        for(u8 i=0;i<count;++i) {
            Pokemon *pokemon=(Pokemon *)fightPokemonGetPokemonPtr(party[i]);
            u16 darkId=pokemon->getDarkpokemonDataID();
            if(darkId!=0)_darkPokemonSetUnderTaker(DeckDarkPokemon::getDeckDarkPokemonObj(darkId),pokemon,trainerName);
        }
    }
    fightEnemyTrainerWazaSeqHdl=retainSequence==1?handle:0;
    fightCloseAllMenu(retainSequence);
    return 1;
}
}
