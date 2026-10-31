#include <dolphin/types.h>

#pragma auto_inline off

struct FightOutPokemon {
    u8 data[0x894];
};
struct Pokemon {
    u8 data[0xC4];
};
struct FightWaza {
    u8 data[0xAC];
};
struct FightAction {
    u8 data[0x38];
};
struct FightPokemon;
struct FIGHT_TRAINER;
struct FightItem;
struct HeroPtr;
struct ServerWorkData {
    u8 work[8];
};

typedef void (*WazaSeqFunc)(void);
typedef void (*FightSeqDamageFunc)(void*, u16, FightOutPokemon*, void*);
typedef u8 (*FightFloorLoopFunc)(void*, u16, void*);

static u8 _fightSeqInitSubFightOutPokemon(void*, u16, void*);
static u8 _fightSeqPreSub(void*, u16, void*);
static u8 _fightSeqTurnCheckSubFightOutPokemon(void*, u16, void*);
static u8 _fightSeqClearOneTurnCountSub(void*, u16, void*);
static u8 _fightSeqClearOneSelfTurnCountSub(void*, u16, void*);

extern "C" {
extern u32 ServerStatusFlag;
extern ServerWorkData ServerWork;
extern u8* UserWork;
extern u8 ActionSeqNo;
extern FightAction* fight_seq_now_fight_action_ptr;
extern u8 fight_seq_server_work3_temp;
extern u8 lbl_804EB918;
extern u8 fightseq_attack_pokemon_joutai_check_buff;
extern u32 fight_waza_critical_data_number;
extern u8 fight_action_data_turn[];
extern u8 fight_action_data_waza[];
extern u8 WAZA_KiaiPunch[];
extern u8 WAZA_PokeReshuffle[];
extern void* WazaEffectTbl[];
extern void* ItemNormalTbl[];
extern void* ItemBallTbl[];
extern void* ItemFightTbl[];
extern u32 AbiCntMsgTbl[];

FightOutPokemon* fightFloor_GetAttackPokemonPtr(void*);
FightOutPokemon* fightFloor_GetDefensePokemonPtr(void*);
FightOutPokemon* fightFloor_GetIrekaePokemonPtr(void*);
void fightFloor_SetAttackPokemonPtr(void*, FightOutPokemon*);
void fightFloor_SetDefensePokemonPtr(void*, FightOutPokemon*);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(void*, FightOutPokemon*);
void fightFloor_SetAppointPokemonPtr(void*, FightOutPokemon*);
void fightFloor_SetAttackMsgId(void*, u32);
void fightFloor_SetCriticakMsgId(void*, u32);
void fightFloor_SetWazakoukaMsgId(void*, u32);
s32 fightFloor_GetFightType(void*);
u16 fightFloor_GetEncountDataId(void*);
u16 fightFloor_GetTurnCount(void*);
void fightFloor_SetTurnCount(void*, u16);
void fightFloor_SetFisstAttackRnd(void*, u16);
u8 fightFloor_GetFightKindDoCriticalAttackFlag(void*);
u8 fightFloorGetNowTenkouDataId(void*, u8);
u8 fightFloorIsNowEncountTuusinTaisen(void*);
u8 fightFloorLoopValidFightOutPokemon(void*, FightFloorLoopFunc, void*, u8);
void fightFloorInitFightOutPokemonPtrAryFightWazaJoutai(void*);
void* fightFloorGetValidFightSidePtr(void*, u16);
FIGHT_TRAINER* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*, FightOutPokemon*);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*, FIGHT_TRAINER*, FightOutPokemon**, u8, u8);
void fightSideInitJoutaiDataId(void*, u16);

FightOutPokemon* fightTargetGetPtrAsNowFightType(u8, void*);
u16 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon*, u8);

void* fightSeq_GetWazaSeq(void);
void fightSeq_JumpWazaSeq(void*);
void fightSeq_CallWazaSeqCustom(void*, void*, u8);
void fightSeqTypeCheckHikaePokemon(void*, u8, u8, u8);
s32 fightSeqWazaDamageCalcHikaePokemon(FightOutPokemon*, void*, FightOutPokemon*, u16, s32, s32);

u8 fightSeqWazaOutBeforeCheckSub(void*, u16, void*);
u8 fightSeqTameWazaCheck(u16);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u16, u8, void*, s32, s32, s32);
void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon*, u16);
void fightSeqFloorJoutaiCheck(void);
void fightSeqSideJoutaiCheck(void);
void fightSeqSideJoutaiCheck2(void);
void fightSeqGetExpCheck(void);
void WS_CRITICAL_CHECK(void);
void WS_DAMAGE_CALC(void);
void WS_TYPE_CHECK(void);
void WS_DAMAGE_LOSS(void);
void wazaSequenceSysFreeAllWaza(void);

void fightOutPokemonBiosCopy(FightOutPokemon*, FightOutPokemon*);
void pokemonBiosCopy(Pokemon*, Pokemon*);
Pokemon* fightPokemon_GetPokemonBuffPtr(void*);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
void fightWazaBiosCopy(FightWaza*, FightWaza*);
void fightWazaInit(FightWaza*);
void fightWazaCreate(FightWaza*, u32, u16, u32, u32);
u8 fightWazaIsHit(FightWaza*);
s32 fightWaza_GetDamage(FightWaza*);
void fightWaza_SetDamage(FightWaza*, s32);
s32 fightWaza_GetIryoku(FightWaza*);
u16 fightWaza_GetZokusei(FightWaza*);
u8 fightWaza_GetCritical(FightWaza*);
u8 fightWaza_GetDamageValue(FightWaza*);
void fightWaza_SetCritical(FightWaza*, u8);
void fightWazaInitJoutaiDataId(FightWaza*, u8);
u16 fightOutPokemon_GetUseWazaDataId(FightOutPokemon*);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon*);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon*, u8);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemon_GetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon*);
u16 figthOutPokemonGetPokemonDataId(FightOutPokemon*);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon*);
void fightOutPokemonInitOneTurn(FightOutPokemon*);
void fightOutPokemonInitOneSelfTurn(FightOutPokemon*);
FightAction* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon*);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon*);
FightItem* fightOutPokemon_GetFightItemPtr(FightOutPokemon*);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
u16 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon*, u16);
s32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon*, u16);
FightAction* fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon*, s32, s32, s32, void*, u16, u16, s8, u8);
u8 fightOutPokemon_GetAbicntAverage(FightOutPokemon*);
void fightOutPokemon_SetAbicntAverage(FightOutPokemon*, u8);
void fightOutPokemonDarkPokemonKaijoEffect(FightOutPokemon*, u8, u8, u8, u16, u8);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon*);
u32 fightOutPokemonGetNicknamePtr(FightOutPokemon*);
void fightOutPokemon_SetHitWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetHitWazaZokuseiDataId(FightOutPokemon*, u8);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon*);
void fightOutPokemon_SetFightoutTurnCount(FightOutPokemon*, u16);
s32 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon*, u16);
s32 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonSetNowKaisuuJoutaiDataId(FightOutPokemon*, u16, s8);
s32 fightOutPokemonGetJoutaiMigawariHp(FightOutPokemon*);

u8 fightActionCreate(FightAction*, void*, FightOutPokemon*, u8, u8, void*);
void fightActionBiosSetBuffDataPtr(FightAction*, void*);
u8 fightActionFlowFifo(FightAction*);
u8 fightActionCheckValid(FightAction*);
void* fightActionBiosGetFightActionDataPtr(FightAction*);

u16 pokemon_GetPokemonDataId(Pokemon*);
s32 pokemon_GetTokuseiFlag(Pokemon*);
u8 pokemonDB_GetTokuseiDataId(u16, u8);
u16 pokemon_GetPokemonWazaDataId(Pokemon*, u16);
u8 pokemonIsDarkPokemon(Pokemon*);
u8 pokemonGetDarkPokemonCallKakuritu(Pokemon*);
void pokemonAddDpFormPokemonDpFilterId(Pokemon*, u32, u32);
u16 pokemonGetSoubiItemDataId(Pokemon*);
u16 pokemonGetSoubiItemSoubiDataId(Pokemon*);
u16 pokemonGetTokuseiDataId(Pokemon*);
void* pokemonTokuseiDataBiosGetPtr(u16);
u32 pokemonTokuseiDataBiosGetName(void*);
u16 wazaDB_GetSeqId(u16);
u32 wazaDB_GetName(u16);
u8 wazaCheckDarkWaza(u16);
u32 wazaGetStatus(u32, u32, u32, u32);
void* fightWazaCriticalDataBiosGetPtr(u16);
u8 fightWazaCriticalDataBiosGetBunbo(void*);
s32 HSD_Rand(void);

void fightItem_GetTargetDataId(FightItem*);
u32 fightItem_GetCount(FightItem*);
s32 fightItem_GetBuff(FightItem*);
void* itemDataBiosGetPtr(u16);
void* itemDataBiosGetItemEffectParam(void*);
void* itemParamGetPtr(void*);
u8 itemDB_GetKind(u16);
u32 itemDB_GetName(u16);
u8 itemParamGetHPUp(void*);
u8 itemParamGetSleepFlag(void*);
u8 itemParamGetPoisonFlag(void*);
u8 itemParamGetBurnFlag(void*);
u8 itemParamGetFreezeFlag(void*);
u8 itemParamGetParalyzeFlag(void*);
u8 itemParamGetConfuseFlag(void*);
u8 itemParamGetCriticalFlag(void*);
u8 itemParamGetAttackUp(void*);
u8 itemParamGetDefenceUp(void*);
u8 itemParamGetQuickUp(void*);
u8 itemParamGetHitUp(void*);
u8 itemParamGetSpAttackUp(void*);
u8 itemParamGetGuardFlag(void*);
s32 heroItemDecItemDataId(HeroPtr*, u16, u32, s16);

HeroPtr* fightTrainer_GetHeroPtr(FIGHT_TRAINER*);
u32 fightTrainerGetPrefixNamePtr(FIGHT_TRAINER*);
u32 fightTrainerGetNamePtr(FIGHT_TRAINER*);
void fightTrainerCallEffect(FIGHT_TRAINER*, u32);
void* fightEncountDataBiosGetPtr(u16);
u8 fightEncountDataBiosGetFightKind(void*);
u16 fightGetFightResultId(void);

u32 GSmsgGetGSchar(u32);
void fightMsgctrlSetValue(s32, u32);
void fightMainAllCamera(u32, u32);
void fightMainWaitFrame(u32);
u8 fightMenuOpenMsg(u32);
void fightMenuCloseMsg(void);
void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon*, u8, u32);
void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon*, u8, u32);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(void*, FightOutPokemon*, u8, u32, u32);
void fightMenuAllFightTrainerCloseStatusMenu(void*);
void fightMenuAllFightOutPokemonCloseStatusMenu(void*);
}

extern "C" {
void CriticalCheckHikaePokemon(void* hikae);
void DamageCalcHikaePokemon(void* hikae);
void fightSeqClearOneTurnCount(u8 flag);
void fightSeqClearOneSelfTurnCount(void);
void fightSeqTurnCheck(void);
void SCA_End(void);
void SCA_EndCheck(void);
void fightSeqSpecificationActionCounterInit(FightOutPokemon* pokemon);
u8 fightSeqGetItemType(u16 itemId, FightOutPokemon* pokemon);
u8 fightSeqFightActionCreate(FightAction* action, void* a, FightOutPokemon* pokemon, u8 kind, u8 b, void* data, void* buff);
}

extern "C" {
void WS_ABARERU(void);
void WS_ADDVALUE(void);
void WS_ADD_POKE(void);
void WS_AKUBI(void);
void WS_ALERTEND(void);
void WS_ALERT_MESSAGE(void);
void WS_ALERT_MESSAGE_TBL(void);
void WS_APPEAR_EFFECT(void);
void WS_APPEAR_EFFECT_INIT(void);
void WS_APPEAR_EFFECT_WAIT(void);
void WS_ASOBI(void);
void WS_ATTACK_MESSAGE(void);
void WS_ATTACK_MESSAGE2(void);
void WS_BADGECHECK(void);
void WS_BALL_GAUGE_OFF(void);
void WS_BALL_GAUGE_SET(void);
void WS_BALL_THROW(void);
void WS_CHECK_TYPE(void);
void WS_CHIISAKUNARU(void);
void WS_CHIKYUUNAGE(void);
void WS_CHOUHATSU(void);
void WS_CLIENT_BIT_WAIT(void);
void WS_CONDCHG(void);
void WS_CONDCHG_CHECK(void);
void WS_CONDITION2_CHECK(void);
void WS_CONDITION_CHECK(void);
void WS_CONDITION_GAUGE(void);
void WS_COND_CHG_BIT_CHECK(void);
void WS_COND_CHG_WORK_SET(void);
void WS_COUNTER(void);
void WS_CRITICAL_CHECK(void);
void WS_CRITICAL_MESSAGE(void);
void WS_DAMAGE_CALC(void);
void WS_DAMAGE_CHG(void);
void WS_DAMAGE_LOSS(void);
void WS_DAMAGE_LOSS_ONLY(void);
void WS_DARKREMOVE(void);
void WS_EFFECT_WAIT(void);
void WS_ENCORE(void);
void WS_END_FIGHT(void);
void WS_ESCAPE_CHECK(void);
void WS_EXPFLAG_CLEAR(void);
void WS_FIGHT_EFFECT(void);
void WS_FIGHT_EFFECT2(void);
void WS_GAMAN(void);
void WS_GAMUSYARA(void);
void WS_GETEND(void);
void WS_GET_EXP(void);
void WS_GET_RESHUFFLE_CLIENT(void);
void WS_GOSUB(void);
void WS_GUARDCHECK(void);
void WS_GUARD_SUCCESS_CHECK(void);
void WS_HAKIDASU(void);
void WS_HARADAIKO(void);
void WS_HENSHIN(void);
void WS_HIKARINOKABE(void);
void WS_HIMITUNOTIKARA(void);
void WS_HITCHECK(void);
void WS_HOGOSYOKU(void);
void WS_HOROBINOUTA(void);
void WS_HPHALF(void);
void WS_HP_CHECK(void);
void WS_HP_DEC(void);
void WS_HP_DEC_WAIT(void);
void WS_HP_GAUGE_REDRAW(void);
void WS_HUKITOBASHI(void);
void WS_HUKITOBASHI_OIUCHI(void);
void WS_HUKURODATAKI(void);
void WS_HUNKA(void);
void WS_HUUIN(void);
void WS_IBARU(void);
void WS_ICHAMON(void);
void WS_ICHIGEKI(void);
void WS_IF16(void);
void WS_IF32(void);
void WS_IF8(void);
void WS_IFWEQ(void);
void WS_IFWNE(void);
void WS_IKAKU(void);
void WS_INC_RECORD(void);
void WS_ITAMIWAKE(void);
void WS_ITEMEND(void);
void WS_ITEM_CONDITION_RECOVER(void);
void WS_ITEM_HP_KAIFUKU(void);
void WS_IYASHINOSUZU(void);
void WS_JIBAKU(void);
void WS_JIBAKU_INIT(void);
void WS_JIBAKU_LOOP(void);
void WS_JIKOANJI(void);
void WS_JISIN(void);
void WS_JITABATA(void);
void WS_JUMP(void);
void WS_JUUDEN(void);
void WS_KAIFUKU(void);
void WS_KANASHIBARI(void);
void WS_KAWARAWARI(void);
void WS_KETAGURI(void);
void WS_KIAIDAME(void);
void WS_KIAIPUNCH(void);
void WS_KIERUTAME(void);
void WS_KIERUTAME_AFTAR(void);
void WS_KILLITEM(void);
void WS_KIZETSU(void);
void WS_KIZETSU_CHECK(void);
void WS_KIZETSU_WAIT(void);
void WS_KOBAN_CHECK(void);
void WS_KONOYUBITOMARE(void);
void WS_KORAERU_CHECK(void);
void WS_KOROGARU(void);
void WS_KOUSOKUSPIN(void);
void WS_KUROIKIRI(void);
void WS_LOCKON(void);
void WS_LOOP(void);
void WS_LOOPCNT(void);
void WS_LOOP_INIT(void);
void WS_MAGICCORT(void);
void WS_MAGNITUDE(void);
void WS_MAKIBISHI(void);
void WS_MARUKUNARU(void);
void WS_MEROMERO(void);
void WS_MESSAGE(void);
void WS_MESSAGE_TBL(void);
void WS_MESSAGE_WAIT(void);
void WS_MEZAMERUPOWER(void);
void WS_ME_PLAY(void);
void WS_MICHIDURE(void);
void WS_MICHIDURE_CHECK(void);
void WS_MIGAWARI(void);
void WS_MIRAIYOCHI(void);
void WS_MIRRORCOAT(void);
void WS_MIYABURU(void);
void WS_MODOSU_EFFECT(void);
void WS_MONOHIROI(void);
void WS_MONOMANE(void);
void WS_MONS_TYPE(void);
void WS_NARIKIRI(void);
void WS_NATSUKI(void);
void WS_NEGAIGOTO(void);
void WS_NEGOTO(void);
void WS_NEKODAMASHI(void);
void WS_NEKONOTE(void);
void WS_NEMURU(void);
void WS_NEWOHARU(void);
void WS_NICKNAME(void);
void WS_NOMIKOMU(void);
void WS_NOROI(void);
void WS_OBOEWAZANO_SET(void);
void WS_OIUCHI_CHECK(void);
void WS_OKIMIYAGE(void);
void WS_OKODUKAI_CALC(void);
void WS_ONNEN(void);
void WS_OUMU_CHECK(void);
void WS_POKEDELACTOR(void);
void WS_POKE_BLINK(void);
void WS_POKE_HPDEC_RATE(void);
void WS_POKE_HPMAX_RATE(void);
void WS_POKE_RESHUFFLE(void);
void WS_POKE_RESHUFFLE_END(void);
void WS_POKE_RESHUFFLE_WAIT(void);
void WS_PP_DEC(void);
void WS_PRESENT(void);
void WS_PSYCHOWAVE(void);
void WS_RECYCLE(void);
void WS_REFLEC(void);
void WS_REFLESH(void);
void WS_RENZOKU(void);
void WS_RENZOKUGIRI(void);
void WS_RENZOKU_NUM_INIT(void);
void WS_RESET16BIT(void);
void WS_RESET32BIT(void);
void WS_RESET8BIT(void);
void WS_RESHUFFLE_CHECK(void);
void WS_RESHUFFLE_NICKNAME(void);
void WS_REVENGE(void);
void WS_SAKUJO(void);
void WS_SAWAGU(void);
void WS_SAWAGU_CHECK(void);
void WS_SCA_END_SET(void);
void WS_SEQEND(void);
void WS_SEQRET(void);
void WS_SET16BIT(void);
void WS_SET32BIT(void);
void WS_SET8BIT(void);
void WS_SETVALUE(void);
void WS_SETWORK(void);
void WS_SETWORKOFS(void);
void WS_SE_PLAY(void);
void WS_SHINPINOMAMORI(void);
void WS_SHIROIKIRI(void);
void WS_SHIZENNOCHIKARA(void);
void WS_SIDECONDITION_CHECK(void);
void WS_SIZENKAIHUKU(void);
void WS_SKETCH(void);
void WS_SKILLSWAP(void);
void WS_SPEABIEND(void);
void WS_SPEABI_CHECK(void);
void WS_SPEABI_HAVE_CHECK(void);
void WS_STATUS_EFFECT(void);
void WS_STATUS_EFFECT2(void);
void WS_STATUS_EFFECT_DIRECT(void);
void WS_STATUS_GET16(void);
void WS_STATUS_GET32(void);
void WS_STATUS_GET8(void);
void WS_STATUS_RECOVER(void);
void WS_STATUS_SET16(void);
void WS_STATUS_SET32(void);
void WS_STATUS_SET8(void);
void WS_STATUS_WINDOW(void);
void WS_SUBROUTINE_CALL(void);
void WS_SUBVALUE(void);
void WS_SUITORI(void);
void WS_SWITCH_A_D(void);
void WS_TAKUWAERU(void);
void WS_TEDASUKE(void);
void WS_TELEPORT(void);
void WS_TENKIYA(void);
void WS_TENKIYA_CHECK(void);
void WS_TEXTURE(void);
void WS_TEXTURE2(void);
void WS_TOKUSEI_SET(void);
void WS_TOKUSYUNO_SET(void);
void WS_TRAINER_APPEAR(void);
void WS_TRICK(void);
void WS_TSUIKA_CHECK(void);
void WS_TSUIKA_DIRECT_ACT(void);
void WS_TSUIKA_INDIRECT_ACT(void);
void WS_TYPE_CHECK(void);
void WS_TYPE_CHECK_NO_HIT(void);
void WS_URAMI(void);
void WS_VANISH_OFF(void);
void WS_VOICE(void);
void WS_WAIT(void);
void WS_WAZAAKIRAME_CHECK(void);
void WS_WAZAEND(void);
void WS_WAZAKOUKA_CHECK(void);
void WS_WAZAKOUKA_MESSAGE(void);
void WS_WAZAKOUKA_SE(void);
void WS_WAZAOBOE_CHECK(void);
void WS_WAZASEQADRS(void);
void WS_WAZAWASURE_CHECK(void);
void WS_WAZA_EFFECT(void);
void WS_WAZA_GET(void);
void WS_WEATHERKAIFUKU(void);
void WS_WEATHER_BALL(void);
void WS_WEATHER_CHANGE(void);
void WS_WEATHER_KEEP(void);
void WS_WKC_ACT(void);
void WS_YADORIGI(void);
void WS_YES_NO_WINDOW(void);
void WS_YOKODORI(void);
void WS_YOKODORI_CLIENT_SET(void);
void WS_YUBIWOHURU(void);
void WS_ZENMETSU_CHECK(void);
void WS_ZUKAN(void);
void WS_ZUKAN_CHECK(void);
}

static WazaSeqFunc const WazaSequenceTbl[] = {
    WS_BADGECHECK,
    WS_HITCHECK,
    WS_ATTACK_MESSAGE,
    WS_ATTACK_MESSAGE2,
    WS_PP_DEC,
    WS_CRITICAL_CHECK,
    WS_DAMAGE_CALC,
    WS_TYPE_CHECK,
    WS_DAMAGE_LOSS,
    WS_DAMAGE_LOSS_ONLY,
    WS_WAZA_EFFECT,
    WS_EFFECT_WAIT,
    WS_HP_DEC,
    WS_HP_DEC_WAIT,
    WS_CRITICAL_MESSAGE,
    WS_WAZAKOUKA_SE,
    WS_WAZAKOUKA_MESSAGE,
    WS_MESSAGE,
    WS_ALERT_MESSAGE,
    WS_MESSAGE_WAIT,
    WS_MESSAGE_TBL,
    WS_ALERT_MESSAGE_TBL,
    WS_TSUIKA_CHECK,
    WS_TSUIKA_DIRECT_ACT,
    WS_TSUIKA_INDIRECT_ACT,
    WS_SAKUJO,
    WS_KIZETSU_CHECK,
    WS_KIZETSU,
    WS_KIZETSU_WAIT,
    WS_CONDITION_CHECK,
    WS_CONDITION2_CHECK,
    WS_SPEABI_CHECK,
    WS_SIDECONDITION_CHECK,
    WS_CONDCHG_CHECK,
    WS_WAZAKOUKA_CHECK,
    WS_CHECK_TYPE,
    WS_GET_EXP,
    WS_ZENMETSU_CHECK,
    WS_LOOP_INIT,
    WS_LOOPCNT,
    WS_LOOP,
    WS_JUMP,
    WS_IF8,
    WS_IF16,
    WS_IF32,
    WS_IFWEQ,
    WS_IFWNE,
    WS_SETVALUE,
    WS_ADDVALUE,
    WS_SUBVALUE,
    WS_SETWORK,
    WS_SETWORKOFS,
    WS_SET8BIT,
    WS_SET16BIT,
    WS_SET32BIT,
    WS_RESET8BIT,
    WS_RESET16BIT,
    WS_RESET32BIT,
    WS_WAIT,
    WS_CLIENT_BIT_WAIT,
    WS_HP_GAUGE_REDRAW,
    WS_SEQRET,
    WS_WAZAEND,
    WS_SEQEND,
    WS_SPEABIEND,
    WS_GUARDCHECK,
    WS_GOSUB,
    WS_MONS_TYPE,
    WS_SPEABI_HAVE_CHECK,
    WS_ALERTEND,
    WS_FIGHT_EFFECT,
    WS_FIGHT_EFFECT2,
    WS_COND_CHG_WORK_SET,
    WS_COND_CHG_BIT_CHECK,
    WS_WKC_ACT,
    WS_TYPE_CHECK_NO_HIT,
    WS_MODOSU_EFFECT,
    WS_APPEAR_EFFECT_INIT,
    WS_APPEAR_EFFECT,
    WS_APPEAR_EFFECT_WAIT,
    WS_RESHUFFLE_CHECK,
    WS_POKE_RESHUFFLE,
    WS_POKE_RESHUFFLE_WAIT,
    WS_POKE_RESHUFFLE_END,
    WS_TRAINER_APPEAR,
    WS_SE_PLAY,
    WS_ME_PLAY,
    WS_VOICE,
    WS_END_FIGHT,
    WS_POKEDELACTOR,
    WS_WAZAOBOE_CHECK,
    WS_WAZAWASURE_CHECK,
    WS_WAZAAKIRAME_CHECK,
    WS_POKE_BLINK,
    WS_OKODUKAI_CALC,
    WS_WAZA_GET,
    WS_SWITCH_A_D,
    WS_INC_RECORD,
    WS_BALL_GAUGE_SET,
    WS_BALL_GAUGE_OFF,
    WS_WAZASEQADRS,
    WS_STATUS_EFFECT,
    WS_STATUS_EFFECT2,
    WS_STATUS_EFFECT_DIRECT,
    WS_YES_NO_WINDOW,
    WS_SCA_END_SET,
    WS_KORAERU_CHECK,
    WS_KILLITEM,
    WS_RESHUFFLE_NICKNAME,
    WS_STATUS_WINDOW,
    WS_EXPFLAG_CLEAR,
    WS_GET_RESHUFFLE_CLIENT,
    WS_VANISH_OFF,
    WS_TOKUSYUNO_SET,
    WS_OBOEWAZANO_SET,
    WS_ESCAPE_CHECK,
    WS_POKE_HPMAX_RATE,
    WS_POKE_HPDEC_RATE,
    WS_STATUS_RECOVER,
    WS_SUBROUTINE_CALL,
    WS_TOKUSEI_SET,
    WS_GUARD_SUCCESS_CHECK,
    WS_JIBAKU_INIT,
    WS_JIBAKU,
    WS_JIBAKU_LOOP,
    WS_KAIFUKU,
    WS_OUMU_CHECK,
    WS_REFLEC,
    WS_YADORIGI,
    WS_DAMAGE_CHG,
    WS_NEMURU,
    WS_NEKODAMASHI,
    WS_SAWAGU,
    WS_SAWAGU_CHECK,
    WS_TAKUWAERU,
    WS_HAKIDASU,
    WS_NOMIKOMU,
    WS_SUITORI,
    WS_CONDCHG,
    WS_KUROIKIRI,
    WS_GAMAN,
    WS_ABARERU,
    WS_RENZOKU,
    WS_RENZOKU_NUM_INIT,
    WS_HUKITOBASHI,
    WS_TEXTURE,
    WS_KOBAN_CHECK,
    WS_HIKARINOKABE,
    WS_ICHIGEKI,
    WS_HPHALF,
    WS_WEATHER_CHANGE,
    WS_WEATHER_KEEP,
    WS_MEROMERO,
    WS_CONDITION_GAUGE,
    WS_SHIROIKIRI,
    WS_KIAIDAME,
    WS_HENSHIN,
    WS_MIGAWARI,
    WS_MONOMANE,
    WS_YUBIWOHURU,
    WS_CHIKYUUNAGE,
    WS_PSYCHOWAVE,
    WS_COUNTER,
    WS_MIRRORCOAT,
    WS_KANASHIBARI,
    WS_ENCORE,
    WS_ITAMIWAKE,
    WS_TEXTURE2,
    WS_LOCKON,
    WS_SKETCH,
    WS_NEGOTO,
    WS_MICHIDURE,
    WS_MICHIDURE_CHECK,
    WS_JITABATA,
    WS_URAMI,
    WS_IYASHINOSUZU,
    WS_NOROI,
    WS_MAKIBISHI,
    WS_MIYABURU,
    WS_HOROBINOUTA,
    WS_KOROGARU,
    WS_IBARU,
    WS_RENZOKUGIRI,
    WS_NATSUKI,
    WS_PRESENT,
    WS_SHINPINOMAMORI,
    WS_MAGNITUDE,
    WS_OIUCHI_CHECK,
    WS_HARADAIKO,
    WS_JIKOANJI,
    WS_KOUSOKUSPIN,
    WS_MARUKUNARU,
    WS_WEATHERKAIFUKU,
    WS_MEZAMERUPOWER,
    WS_JISIN,
    WS_MIRAIYOCHI,
    WS_HUKURODATAKI,
    WS_KIERUTAME,
    WS_KIERUTAME_AFTAR,
    WS_CHIISAKUNARU,
    WS_OKIMIYAGE,
    WS_KONOYUBITOMARE,
    WS_JUUDEN,
    WS_SHIZENNOCHIKARA,
    WS_REFLESH,
    WS_ICHAMON,
    WS_KIAIPUNCH,
    WS_CHOUHATSU,
    WS_TEDASUKE,
    WS_TRICK,
    WS_NARIKIRI,
    WS_NEGAIGOTO,
    WS_NEWOHARU,
    WS_REVENGE,
    WS_AKUBI,
    WS_GAMUSYARA,
    WS_HUNKA,
    WS_SKILLSWAP,
    WS_HUUIN,
    WS_ONNEN,
    WS_KETAGURI,
    WS_NEKONOTE,
    WS_MAGICCORT,
    WS_YOKODORI,
    WS_IKAKU,
    WS_SIZENKAIHUKU,
    WS_HP_CHECK,
    WS_HIMITUNOTIKARA,
    WS_MONOHIROI,
    WS_TENKIYA,
    WS_TENKIYA_CHECK,
    WS_ASOBI,
    WS_WEATHER_BALL,
    WS_RECYCLE,
    WS_HOGOSYOKU,
    WS_HUKITOBASHI_OIUCHI,
    WS_YOKODORI_CLIENT_SET,
    WS_KAWARAWARI,
    WS_DARKREMOVE,
    WS_TELEPORT,
    WS_BALL_THROW,
    WS_ADD_POKE,
    WS_ZUKAN_CHECK,
    WS_ZUKAN,
    WS_NICKNAME,
    WS_ITEM_HP_KAIFUKU,
    WS_ITEM_CONDITION_RECOVER,
    WS_ITEMEND,
    WS_GETEND,
    WS_STATUS_GET8,
    WS_STATUS_GET16,
    WS_STATUS_GET32,
    WS_STATUS_SET8,
    WS_STATUS_SET16,
    WS_STATUS_SET32,
};

static inline void ServerWorkClear(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        ServerWork.work[i] = 0;
    }
}

extern "C" {

s32 fightSeqGetWazaDamageHikaePokemon(void* floor, u16 wazaId, FightOutPokemon* attack, void* hikae, u8 critical,
                                      FightSeqDamageFunc before, FightSeqDamageFunc after) {
    ServerWorkData work;
    Pokemon pokemonSave;
    FightWaza* waza;
    void* seq;
    FightOutPokemon* oldAttack;
    FightOutPokemon attackSave;
    FightWaza wazaSave;
    s32 damage;
    u32 flag;
    s32 i;

    oldAttack = fightFloor_GetAttackPokemonPtr(0);
    seq = fightSeq_GetWazaSeq();
    flag = ServerStatusFlag;
    for (i = 0; i < 8; i++) {
        work.work[i] = ServerWork.work[i];
    }
    fightOutPokemonBiosCopy(&attackSave, attack);
    pokemonBiosCopy(&pokemonSave, fightPokemon_GetPokemonBuffPtr(hikae));
    fightFloor_SetAttackPokemonPtr(0, attack);
    waza = fightOutPokemon_GetFightWazaPtr(attack);
    fightWazaBiosCopy(&wazaSave, waza);
    fightWazaInit(waza);
    fightWazaCreate(waza, 0, wazaId, 0, 0);
    ServerStatusFlag = 0;
    ServerWorkClear();
    if (before != 0) {
        before(floor, wazaId, attack, hikae);
    }
    if (critical == 1) {
        CriticalCheckHikaePokemon(hikae);
    }
    DamageCalcHikaePokemon(hikae);
    fightSeqTypeCheckHikaePokemon(hikae, 1, 1, 0);
    if (after != 0) {
        after(floor, wazaId, attack, hikae);
    }
    damage = fightWazaIsHit(waza) == 1 ? fightWaza_GetDamage(waza) : 0;
    fightFloor_SetAttackPokemonPtr(0, oldAttack);
    fightWazaBiosCopy(waza, &wazaSave);
    fightSeq_JumpWazaSeq(seq);
    ServerStatusFlag = flag;
    for (i = 0; i < 8; i++) {
        ServerWork.work[i] = work.work[i];
    }
    fightOutPokemonBiosCopy(attack, &attackSave);
    pokemonBiosCopy(fightPokemon_GetPokemonBuffPtr(hikae), &pokemonSave);
    return damage;
}

void DamageCalcHikaePokemon(void* hikae) {
    FightOutPokemon* attack;
    FightOutPokemon* side;
    u16 zokusei;
    u16 wazaId;
    s32 iryoku;
    FightWaza* waza;
    s32 damage;

    attack = fightTargetGetPtrAsNowFightType(0x11, 0);
    side = fightTargetGetPtrAsNowFightType(3, attack);
    wazaId = fightOutPokemon_GetUseWazaDataId(attack);
    waza = fightOutPokemon_GetFightWazaPtr(attack);
    iryoku = fightWaza_GetIryoku(waza);
    zokusei = fightWaza_GetZokusei(waza);
    damage = fightSeqWazaDamageCalcHikaePokemon(attack, hikae, side, wazaId, iryoku, zokusei);
    damage = damage * fightWaza_GetCritical(waza);
    damage = damage * fightWaza_GetDamageValue(waza);
    if (fightOutPokemonIsJoutaiDataId(attack, 0x24) == 1 && zokusei == 0xD) {
        damage *= 2;
    }
    if (fightOutPokemonIsJoutaiDataId(attack, 0x32) == 1) {
        damage = damage * 15 / 10;
    }
    fightWaza_SetDamage(waza, damage);
}

void CriticalCheckHikaePokemon(void* hikae) {
    u8 luckyPunch;
    FightWaza* waza;
    u16 rnd;
    FightOutPokemon* attack;
    u16 rank;
    u16 monsno;
    u8 naganegi;
    u16 wazaId;
    u16 defMonsno;
    u16 item;
    u8 tokuseiFlag;

    attack = fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemonGetTokuseiDataId(attack);
    item = fightOutPokemonGetSoubiItemSoubiDataId(attack);
    waza = fightOutPokemon_GetFightWazaPtr(attack);
    wazaId = fightOutPokemon_GetUseWazaDataId(attack);
    monsno = figthOutPokemonGetPokemonDataId(attack);
    defMonsno = pokemon_GetPokemonDataId(fightPokemon_GetPokemonBuffPtr(hikae));
    tokuseiFlag = pokemon_GetTokuseiFlag(fightPokemon_GetPokemonBuffPtr(hikae));
    luckyPunch = 0;
    if (item == 0x3F && monsno == 0x71) {
        luckyPunch = 1;
    }
    naganegi = 0;
    if (item == 0x42 && monsno == 0x53) {
        naganegi = 1;
    }
    rank = (fightOutPokemonIsJoutaiDataId(attack, 0xF) == 1) * 2 + (wazaDB_GetSeqId(wazaId) == 0x2B) +
           (wazaDB_GetSeqId(wazaId) == 0x4B) + (wazaDB_GetSeqId(wazaId) == 0xC8) + (wazaDB_GetSeqId(wazaId) == 0xD1) +
           (item == 0x29) + luckyPunch * 2 + naganegi * 2;
    if (rank > fight_waza_critical_data_number - 1) {
        rank = fight_waza_critical_data_number - 1;
    }
    if (pokemonDB_GetTokuseiDataId(defMonsno, tokuseiFlag) != 4 && pokemonDB_GetTokuseiDataId(defMonsno, tokuseiFlag) != 0x4B &&
        fightFloor_GetFightKindDoCriticalAttackFlag(0) == 1) {
        rnd = HSD_Rand();
        if (rnd % fightWazaCriticalDataBiosGetBunbo(fightWazaCriticalDataBiosGetPtr(rank)) == 0) {
            fightWaza_SetCritical(waza, 2);
        } else {
            fightWaza_SetCritical(waza, 1);
        }
    } else {
        fightWaza_SetCritical(waza, 1);
    }
}

s32 fightSeqGetNromalWazaDamage(void* floor, u16 wazaId, FightOutPokemon* attack, FightOutPokemon* defense, u8 critical, u8 loss,
                                FightSeqDamageFunc before, FightSeqDamageFunc after) {
    FightOutPokemon attackSave;
    FightWaza* waza;
    s32 i;
    s32 damage;
    FightOutPokemon defenseSave;
    void* seq;
    ServerWorkData work;
    FightOutPokemon* oldAttack;
    FightOutPokemon* oldDefense;
    FightWaza wazaSave;
    u32 flag;

    oldAttack = fightFloor_GetAttackPokemonPtr(0);
    oldDefense = fightFloor_GetDefensePokemonPtr(0);
    seq = fightSeq_GetWazaSeq();
    flag = ServerStatusFlag;
    for (i = 0; i < 8; i++) {
        work.work[i] = ServerWork.work[i];
    }
    fightOutPokemonBiosCopy(&attackSave, attack);
    fightOutPokemonBiosCopy(&defenseSave, defense);
    fightFloor_SetAttackPokemonPtr(0, attack);
    fightFloor_SetDefensePokemonPtr(0, defense);
    waza = fightOutPokemon_GetFightWazaPtr(attack);
    fightWazaBiosCopy(&wazaSave, waza);
    fightWazaInit(waza);
    fightWazaCreate(waza, 0, wazaId, 0, 0);
    ServerStatusFlag = 0;
    ServerWorkClear();
    if (before != 0) {
        before(floor, wazaId, attack, defense);
    }
    if (critical == 1) {
        WS_CRITICAL_CHECK();
    }
    WS_DAMAGE_CALC();
    WS_TYPE_CHECK();
    if (loss == 1) {
        WS_DAMAGE_LOSS();
    }
    if (after != 0) {
        after(floor, wazaId, attack, defense);
    }
    damage = fightWazaIsHit(waza) == 1 ? fightWaza_GetDamage(waza) : 0;
    fightFloor_SetAttackPokemonPtr(0, oldAttack);
    fightFloor_SetDefensePokemonPtr(0, oldDefense);
    fightWazaBiosCopy(waza, &wazaSave);
    fightSeq_JumpWazaSeq(seq);
    ServerStatusFlag = flag;
    for (i = 0; i < 8; i++) {
        ServerWork.work[i] = work.work[i];
    }
    fightOutPokemonBiosCopy(attack, &attackSave);
    fightOutPokemonBiosCopy(defense, &defenseSave);
    return damage;
}

#pragma peephole off
bool fightSeqGetEffectAminFlag(void) {
    return (ServerStatusFlag & 0x80) == 0;
}

#pragma peephole reset
void fightSeqSetEffectAminFlag(u8 flag) {
    if (flag == 1) {
        ServerStatusFlag &= ~0x80;
    } else {
        ServerStatusFlag |= 0x80;
    }
}

void fightSeqInit(void) {
    fightSeqClearOneTurnCount(0);
    fightSeqClearOneSelfTurnCount();
    ServerWorkClear();
    fight_seq_now_fight_action_ptr = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightSeqInitSubFightOutPokemon, 0, 0);
}

}

static u8 _fightSeqInitSubFightOutPokemon(void* pokemonPtr, u16 fightType, void* data) {
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;

    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    fightOutPokemonInitJoutaiDataId(pokemon, 0x11);
    return 1;
}

extern "C" {

u8 fightSeqFightActionCreateAndFlowFifo(void* a, FightOutPokemon* pokemon, u8 kind, u8 b, void* data, void* buff) {
    FightAction action;
    u8 r = fightSeqFightActionCreate(&action, a, pokemon, kind, b, data, buff);
    if (r != 1) {
        return r;
    }
    return fightActionFlowFifo(&action);
}

#pragma peephole off
u8 fightSeqFightActionCreate(FightAction* action, void* a, FightOutPokemon* pokemon, u8 kind, u8 b, void* data, void* buff) {
    u8 result = fightActionCreate(action, a, pokemon, kind, b, data);
    if (result != 1) {
        return result;
    }
    fightActionBiosSetBuffDataPtr(action, buff);
    return 1;
}

#pragma peephole reset
void fightSeqPost(void) {
    ServerStatusFlag &= ~0x100000;
    fightSeqTurnCheck();
}

void fightSeqPre(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqPreSub, 0, 1);
    fightFloorLoopValidFightOutPokemon(0, fightSeqWazaOutBeforeCheckSub, 0, 1);
    fight_seq_server_work3_temp = 0;
    ServerWork.work[3] = 0;
    ServerWork.work[4] = 0;
    UserWork[0x16002] = 0;
    UserWork[0x160A1] = 0;
    wazaSequenceSysFreeAllWaza();
}

}

static u8 _fightSeqPreSub(void* pokemonPtr, u16 fightType, void* data) {
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;
    FightAction* action;

    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    action = fightOutPokemon_GetFightActionBuffPtr(pokemon);
    if (action == 0) {
        return 1;
    }
    if (!fightActionCheckValid(action)) {
        return 1;
    }
    if (fightOutPokemon_GetMotoWazaDataId(pokemon) == 0x108 && !fightOutPokemonIsJoutaiDataId(pokemon, 8) &&
        !fightOutPokemon_GetNamakeFlag(pokemon)) {
        fightSeqFightActionCreateAndFlowFifo(fightActionBiosGetFightActionDataPtr(fight_seq_now_fight_action_ptr), pokemon, 0xC, 0,
                                             fight_action_data_turn, WAZA_KiaiPunch);
    }
    return 1;
}

extern "C" {

void fightSeqExec(FightAction* action, void* seq, u8 sca) {
    FightAction* oldAction = fight_seq_now_fight_action_ptr;
    u8 oldSeqNo = ActionSeqNo;
    void* oldSeq = fightSeq_GetWazaSeq();

    fightSeq_JumpWazaSeq(seq);
    if (!sca) {
        ActionSeqNo = 0;
    }
    fight_seq_now_fight_action_ptr = action;
    while (1) {
        WazaSequenceTbl[(u16)*(u8*)fightSeq_GetWazaSeq()]();
        if (sca) {
            if (ActionSeqNo == 1) {
                SCA_EndCheck();
            }
            if (ActionSeqNo == 2) {
                SCA_End();
                break;
            }
        } else if (ActionSeqNo == 1 || ActionSeqNo == 2) {
            break;
        }
    }
    if (sca) {
        ServerStatusFlag &= ~0x200;
        ServerStatusFlag &= ~0x80000;
    }
    fight_seq_now_fight_action_ptr = oldAction;
    ActionSeqNo = oldSeqNo;
    fightSeq_JumpWazaSeq(oldSeq);
}

void fightSeqItemExec(void* floor, u16 itemId) {
    u8 fightType;
    FightOutPokemon* attack;
    FightOutPokemon* defense;
    FIGHT_TRAINER* trainer;
    HeroPtr* hero;
    FightItem* item;
    int count;
    u8 buff;

    void* param;
    u8 save601E;
    u8 save60A4;
    void* seq;
    u8 type;
    s16 up;

    fightType = fightFloor_GetFightType(0);
    attack = fightTargetGetPtrAsNowFightType(0x11, 0);
    defense = fightTargetGetPtrAsNowFightType(0x12, 0);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attack);
    hero = fightTrainer_GetHeroPtr(trainer);
    item = fightOutPokemon_GetFightItemPtr(attack);
    if (item == 0) {
        return;
    }
    fightItem_GetTargetDataId(item);
    count = fightItem_GetCount(item);
    buff = fightItem_GetBuff(item) != 0;
    param = itemParamGetPtr(itemDataBiosGetItemEffectParam(itemDataBiosGetPtr(itemId)));
    save601E = UserWork[0x1601E];
    save60A4 = UserWork[0x160A4];
    fightSeqSpecificationActionCounterInit(attack);
    if (buff == 1) {
        seq = ItemNormalTbl[0];
    } else if (itemDB_GetKind(itemId) == 1) {
        seq = ItemBallTbl[itemId];
    } else if (itemId == 0x50 || itemId == 0x51) {
        seq = ItemFightTbl[0];
    } else {
        type = fightSeqGetItemType(itemId, attack);
        if (type == 7) {
            seq = ItemNormalTbl[0];
        } else {
            fightFloor_SetAppointPokemonPtr(0, attack);
            ServerWork.work[5] = 0;
            switch (type) {
            case 3:
                if (itemParamGetSleepFlag(param) == 1 && itemParamGetPoisonFlag(param) == 1 && itemParamGetBurnFlag(param) == 1 &&
                    itemParamGetFreezeFlag(param) == 1 && itemParamGetParalyzeFlag(param) == 1) {
                    if (fightOutPokemonIsJoutaiDataId(attack, 8) == 1) {
                        ServerWork.work[5] = 5;
                    } else if (fightOutPokemonIsJoutaiDataId(attack, 3) == 1) {
                        ServerWork.work[5] = 4;
                    } else if (fightOutPokemonIsJoutaiDataId(attack, 4) == 1) {
                        ServerWork.work[5] = 4;
                    } else if (fightOutPokemonIsJoutaiDataId(attack, 6) == 1) {
                        ServerWork.work[5] = 3;
                    } else if (fightOutPokemonIsJoutaiDataId(attack, 7) == 1) {
                        ServerWork.work[5] = 2;
                    } else if (fightOutPokemonIsJoutaiDataId(attack, 5) == 1) {
                        ServerWork.work[5] = 1;
                    }
                } else if (itemParamGetSleepFlag(param) == 1) {
                    ServerWork.work[5] = 5;
                } else if (itemParamGetPoisonFlag(param) == 1) {
                    ServerWork.work[5] = 4;
                } else if (itemParamGetBurnFlag(param) == 1) {
                    ServerWork.work[5] = 3;
                } else if (itemParamGetFreezeFlag(param) == 1) {
                    ServerWork.work[5] = 2;
                } else if (itemParamGetParalyzeFlag(param) == 1) {
                    ServerWork.work[5] = 1;
                } else if (itemParamGetConfuseFlag(param) == 1) {
                    ServerWork.work[5] = 0;
                }
                break;
            case 4:
                ServerWork.work[5] = 5;
                break;
            case 5:
                ServerWork.work[5] = 4;
                if ((up = itemParamGetAttackUp(param)) > 0) {
                    fightMsgctrlSetValue(0xD, GSmsgGetGSchar(AbiCntMsgTbl[1]));
                    UserWork[0x1601E] = 1;
                } else if ((up = itemParamGetDefenceUp(param)) > 0) {
                    fightMsgctrlSetValue(0xD, GSmsgGetGSchar(AbiCntMsgTbl[2]));
                    UserWork[0x1601E] = 2;
                } else if ((up = itemParamGetQuickUp(param)) > 0) {
                    fightMsgctrlSetValue(0xD, GSmsgGetGSchar(AbiCntMsgTbl[3]));
                    UserWork[0x1601E] = 3;
                } else if ((up = itemParamGetHitUp(param)) > 0) {
                    fightMsgctrlSetValue(0xD, GSmsgGetGSchar(AbiCntMsgTbl[6]));
                    UserWork[0x1601E] = 6;
                } else if ((up = itemParamGetSpAttackUp(param)) > 0) {
                    fightMsgctrlSetValue(0xD, GSmsgGetGSchar(AbiCntMsgTbl[4]));
                    UserWork[0x1601E] = 4;
                }
                if (up < 0) {
                    if (up == 1 || up == -1) {
                        fightMsgctrlSetValue(0xE, GSmsgGetGSchar(0x4F9C));
                        UserWork[0x1601E] = (UserWork[0x1601E] & 0xF) + 0x15;
                    } else {
                        fightMsgctrlSetValue(0xE, GSmsgGetGSchar(0x4F11));
                        UserWork[0x160A4] = (UserWork[0x1601E] & 0xF) + 0x2D;
                    }
                    fightMsgctrlSetValue(0x41, GSmsgGetGSchar(0x4F12));
                } else {
                    if (up == 1 || up == -1) {
                        fightMsgctrlSetValue(0xE, GSmsgGetGSchar(0x4F9C));
                        UserWork[0x160A4] = (UserWork[0x1601E] & 0xF) + 0xE;
                    } else {
                        fightMsgctrlSetValue(0xE, GSmsgGetGSchar(0x4F0F));
                        UserWork[0x160A4] = (UserWork[0x1601E] & 0xF) + 0x26;
                    }
                    fightMsgctrlSetValue(0x41, GSmsgGetGSchar(0x4F10));
                }
                break;
            case 0:
            case 1:
            case 2:
            case 6:
                break;
            }
            seq = ItemNormalTbl[type];

        }
    }
    ActionSeqNo = 0;
    fightMsgctrlSetValue(0x22, fightTrainerGetPrefixNamePtr(trainer));
    fightMsgctrlSetValue(0x23, fightTrainerGetNamePtr(trainer));
    fightMsgctrlSetValue(0x13, fightTrainerGetNamePtr(trainer));
    fightMsgctrlSetValue(0x29, GSmsgGetGSchar(itemDB_GetName(itemId)));
    fightMainAllCamera(1, 0);
    if (buff == 0) {
        fightMenuFightOutPokemonOpenStatusMenu(defense, fightType, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, defense, fightType, 0, 1);
    }
    fightSeq_CallWazaSeqCustom(floor, seq, 1);
    if (buff == 0) {
        if (heroItemDecItemDataId(hero, itemId, 1, count) < 0) {
            heroItemDecItemDataId(hero, itemId, 1, -1);
        }
    }
    UserWork[0x1601E] = save601E;
    UserWork[0x160A4] = save60A4;
    wazaSequenceSysFreeAllWaza();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
}

u8 fightSeqGetItemType(u16 itemId, FightOutPokemon* pokemon) {
    void* param = itemParamGetPtr(itemDataBiosGetItemEffectParam(itemDataBiosGetPtr(itemId)));

    if (param == 0) {
        return 7;
    }
    if (itemId == 0x13) {
        return 1;
    }
    if (itemParamGetHPUp(param)) {
        return 2;
    }
    if (itemParamGetSleepFlag(param) == 1 || itemParamGetPoisonFlag(param) == 1 || itemParamGetBurnFlag(param) == 1 ||
        itemParamGetFreezeFlag(param) == 1 || itemParamGetParalyzeFlag(param) == 1 || itemParamGetConfuseFlag(param) == 1) {
        return 3;
    }
    if (itemParamGetCriticalFlag(param) == 1) {
        return 4;
    }
    if (itemParamGetAttackUp(param) || itemParamGetDefenceUp(param) || itemParamGetQuickUp(param) || itemParamGetHitUp(param) ||
        itemParamGetSpAttackUp(param)) {
        return 5;
    }
    if (itemParamGetGuardFlag(param) == 1) {
        return 6;
    }
    return 7;
}

void fightSeqSpecificationActionCounterInit(FightOutPokemon* pokemon) {
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x2E) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2E);
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x15) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x15);
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x28) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x28);
    }
}

void fightSeqWazaExec(void* floor, u16 wazaId) {
    u8 fightType;
    u16 seqId;
    FightOutPokemon* attack;
    void* attackSide;
    FightOutPokemon* defense;
    void* defenseSide;
    u16 id;
    int buffId;
    FightOutPokemon* select;
    u16 waza;
    u16 seq;

    fightType = fightFloor_GetFightType(0);
    seqId = wazaDB_GetSeqId(wazaId);
    attack = fightTargetGetPtrAsNowFightType(0x11, 0);
    attackSide = fightTargetGetPtrAsNowFightType(2, attack);
    defense = fightTargetGetPtrAsNowFightType(0x12, 0);
    defenseSide = fightTargetGetPtrAsNowFightType(2, defense);
    if (!fightOutPokemonCheckFightOut(attack)) {
        return;
    }
    if (!fightActionCheckValid(fightOutPokemon_GetFightActionBuffPtr(attack))) {
        return;
    }
    fightFloor_SetAttackMsgId(0, 0);
    fightFloor_SetCriticakMsgId(0, 0);
    fightFloor_SetWazakoukaMsgId(0, 0);
    ServerWork.work[6] = 0;
    lbl_804EB918 = 0;
    fightseq_attack_pokemon_joutai_check_buff = 0;
    if (fightOutPokemonIsJoutaiDataId(attack, 0x2A) == 1 && wazaId != 0xA5) {
        id = fightOutPokemonGetIdBuffJoutaiDataId(attack, 0x2A);
        buffId = fightOutPokemonGetBuffJoutaiDataId(attack, 0x2A);
        waza = pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(attack), buffId);
        if (id != waza) {
            fightOutPokemonInitJoutaiDataId(attack, 0x2A);
        }
        select = fightSeqSelectDefensePokemonPtr(attack, waza, fightType, 0, 1, 1, -1);
        fightOutPokemonCreateFightActionAttackWaza(attack, 0, 0x13, 0, fight_action_data_waza, (u16)waza,
                                                   fightTargetGetTragetPtrToRelativeHostSideFightTargetId(select, fightType), buffId, 1);
        wazaId = waza;
        fightFloor_SetDefensePokemonPtr(0, select);
        defense = fightTargetGetPtrAsNowFightType(0x12, 0);
        defenseSide = fightTargetGetPtrAsNowFightType(2, defense);
    }
    if (wazaId == 0xA5 || wazaCheckDarkWaza(wazaId) == 1) {
        ServerStatusFlag |= 0x800;
    }
    if (fightSeqTameWazaCheck(wazaId) == 1 && !fightOutPokemonIsJoutaiDataId(attack, 0x22)) {
        if (seqId == 0x97 && fightFloorGetNowTenkouDataId(0, 1) == 1) {
            select = fightSeqSelectDefensePokemonPtr(attack, wazaId, fightType, 0, 0, 1, -1);
            if (select != 0) {
                defense = select;
                fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, select);
                defenseSide = fightTargetGetPtrAsNowFightType(2, select);
            }
        }
    } else {
        select = fightSeqSelectDefensePokemonPtr(attack, wazaId, fightType, 0, 0, 1, -1);
        if (select != 0) {
            defense = select;
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, select);
            defenseSide = fightTargetGetPtrAsNowFightType(2, select);
        }
    }
    if (!fightOutPokemonCheckFightOut(defense)) {
        if (attackSide == defenseSide) {
            defense = fightTargetGetPtrAsNowFightType(0xF, attack);
            if (fightOutPokemonCheckFightOut(defense)) {
                goto found;
            }
        }
        defense = fightTargetGetPtrAsNowFightType(0xE, defense);
        if (defense != 0) {
            if (fightOutPokemonCheckFightOut(defense)) {
                goto found;
            }
            return;
        }
        return;
    found:
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, defense);
        fightTargetGetPtrAsNowFightType(2, defense);
    }
    seq = wazaDB_GetSeqId(wazaId);
    ActionSeqNo = 0;
    fightMsgctrlSetValue(0x28, GSmsgGetGSchar(wazaDB_GetName(wazaId)));
    fightSeq_CallWazaSeqCustom(floor, WazaEffectTbl[seq], 1);
    wazaSequenceSysFreeAllWaza();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
}

void fightSeqCallExec(void* floor) {
    u16 msgId;
    u8 kaijo;
    u8 hyper;
    FightOutPokemon* attack;
    u8 fightType;
    u8 abicnt;
    FIGHT_TRAINER* trainer;
    u8 kakuritu;

    kaijo = 0;
    hyper = 0;
    abicnt = 0;
    fightType = fightFloor_GetFightType(0);
    attack = fightFloor_GetAttackPokemonPtr(0);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attack);
    fightSeqSpecificationActionCounterInit(attack);
    if (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(attack)) == 1) {
        kakuritu = pokemonGetDarkPokemonCallKakuritu(fightOutPokemonGetPokemonPtr(attack));
        if (fightOutPokemonIsJoutaiDataId(attack, 0x3E) == 1) {
            if ((u16)HSD_Rand() % 100 < kakuritu) {
                msgId = 0x4FD3;
                hyper = 1;
                if (fightOutPokemonIsJoutaiDataId(attack, 8) == 1) {
                    kaijo = 1;
                }
            } else {
                msgId = 0x4FD4;
                if (fightOutPokemonIsJoutaiDataId(attack, 8) == 1 && (u16)HSD_Rand() % 100 < kakuritu / 2) {
                    kaijo = 1;
                }
            }
        } else if (fightOutPokemonIsJoutaiDataId(attack, 8) == 1) {
            msgId = 0x4FD2;
            kaijo = 1;
        } else {
            abicnt = 1;
        }
    } else if (fightOutPokemonIsJoutaiDataId(attack, 8) == 1) {
        msgId = 0x4FD2;
        kaijo = 1;
    } else {
        abicnt = 1;
    }
    if (abicnt == 1) {
        abicnt = fightOutPokemon_GetAbicntAverage(attack);
        if (abicnt < 0xC) {
            msgId = 0x4F13;
            GSmsgGetGSchar(wazaGetStatus(0, 0xDB, 1, 0));
            fightMsgctrlSetValue(0xD, GSmsgGetGSchar(0x4F79));
            fightMsgctrlSetValue(0xE, GSmsgGetGSchar(0x4F9C));
            fightMsgctrlSetValue(0x41, GSmsgGetGSchar(0x4F10));
            fightOutPokemon_SetAbicntAverage(attack, abicnt + 1);
            abicnt = 1;
        } else {
            msgId = 0x4F18;
            abicnt = 0;
        }
    }
    fightTrainerCallEffect(trainer, 0);
    fightOutPokemonDarkPokemonKaijoEffect(attack, kaijo, hyper, abicnt, 0, 0);
    fightMsgctrlSetValue(0x13, fightTrainerGetNamePtr(trainer));
    fightMainAllCamera(1, 0);
    fightMenuOpenMsg(0x4FD0);
    fightMainWaitFrame(0x40);
    fightMenuCloseMsg();
    fightTrainerCallEffect(trainer, 1);
    fightMenuFightOutPokemonOpenStatusMenu(attack, fightType, 1);
    fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, attack, fightType, 0, 1);
    fightMenuOpenMsg(0x4FD1);
    fightTrainerCallEffect(trainer, 2);
    fightMenuCloseMsg();
    if (kaijo == 1) {
        fightOutPokemonInitJoutaiDataId(attack, 8);
        fightOutPokemonInitJoutaiDataId(attack, 0x17);
        fightSeqCheckSetHensinBuffToMotoPokemon(attack, 0x7C);
    }
    if (hyper == 1) {
        fightOutPokemonInitJoutaiDataId(attack, 0x3E);
        fightSeqCheckSetHensinBuffToMotoPokemon(attack, 0xC8);
        if (fightOutPokemonIsGcHeroFightOutPokemon(attack) == 1 &&
            pokemon_GetPokemonDataId(fightOutPokemonGetPokemonPtr(attack)) != 0xF9) {
            pokemonAddDpFormPokemonDpFilterId(fightOutPokemonGetPokemonPtr(attack), 0, 2);
            fightSeqCheckSetHensinBuffToMotoPokemon(attack, 0xC5);
        }
    }
    fightOutPokemonDarkPokemonKaijoEffect(attack, kaijo, hyper, abicnt, msgId, 1);
    fightOutPokemonDarkPokemonKaijoEffect(attack, kaijo, hyper, abicnt, 0, 2);
    fightMenuCloseMsg();
    fightMenuFightOutPokemonCloseStatusMenu(attack, fightType, 0);
    fightTrainerCallEffect(trainer, 3);
    fightOutPokemonDarkPokemonKaijoEffect(attack, kaijo, hyper, abicnt, 0, 3);
    wazaSequenceSysFreeAllWaza();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
}

void fightSeqIrekaeExec(void* floor) {
    FightOutPokemon* irekae = fightFloor_GetIrekaePokemonPtr(0);

    fightFloor_SetAttackPokemonPtr(0, irekae);
    fightMsgctrlSetValue(0xD, fightOutPokemonGetNicknamePtr(irekae));
    ActionSeqNo = 0;
    fightSeqSpecificationActionCounterInit(irekae);
    fightSeq_CallWazaSeqCustom(floor, WAZA_PokeReshuffle, 1);
    wazaSequenceSysFreeAllWaza();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
}

u8 fightSeqOpenMsg(u32 msgId) {
    u8 result = fightMenuOpenMsg(msgId);

    if (result == 1) {
        ServerWork.work[7] = 1;
    }
    return result;
}

void SCA_End(void) {
    FightOutPokemon* attack;
    FightOutPokemon* defense;
    FightWaza* waza;
    FightWaza* defenseWaza;
    u8 id;
    int i;

    attack = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attack);
    defense = fightTargetGetPtrAsNowFightType(0x12, 0);
    defenseWaza = 0;
    if (defense != 0) {
        defenseWaza = fightOutPokemon_GetFightWazaPtr(defense);
    }
    fightSeqClearOneSelfTurnCount();
    ServerStatusFlag &= 0xF1E892AF;
    ServerWork.work[3] = 0;
    fight_seq_server_work3_temp = 0;
    ServerWork.work[4] = 0;
    UserWork[0x16002] = 0;
    UserWork[0x160A1] = 0;
    fightOutPokemon_SetHitWazaDataId(attack, 0);
    fightOutPokemon_SetHitWazaZokuseiDataId(attack, 9);
    fightWaza_SetDamage(waza, 0);
    for (i = 0x3F; (u8)i <= 0x47; i++) {
        id = i;
        fightWazaInitJoutaiDataId(waza, id);
        if (defenseWaza != 0) {
            fightWazaInitJoutaiDataId(defenseWaza, id);
        }
    }
}

void SCA_EndCheck(void) {
    fightSeqGetExpCheck();
    ActionSeqNo = 2;
}

u8 EscapeNGCheck(FightOutPokemon* pokemon) {
    FightOutPokemon* ary[2];
    s32 i;
    Pokemon* pk;
    u16 item;
    u16 enemyTokusei;
    u16 tokusei;
    void* encount;
    u16 soubi;
    u8 count;

    pk = fightOutPokemonGetPokemonPtr(pokemon);
    encount = fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0));
    item = pokemonGetSoubiItemDataId(pk);
    tokusei = pokemonGetTokuseiDataId(pk);
    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(0, fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon), ary, 0, 1);
    soubi = pokemonGetSoubiItemSoubiDataId(pk);
    fightMsgctrlSetValue(0x29, GSmsgGetGSchar(itemDB_GetName(item)));
    if (fightEncountDataBiosGetFightKind(encount) != 0xC) {
        ServerWork.work[5] = 0;
        return 1;
    }
    if (soubi == 0x25 || fightFloorIsNowEncountTuusinTaisen(0) == 1 || tokusei == 0x32) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        enemyTokusei = fightOutPokemon_GetTokuseiDataId(ary[i]);
        if (enemyTokusei == 0x17) {
            UserWork[0x16003] = i;
            fightMsgctrlSetValue(0x1C, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(enemyTokusei))));
            fightMsgctrlSetValue(0x1E, (u32)ary[i]);
            ServerWork.work[5] = 2;
            return 2;
        }
        if (enemyTokusei == 0x47 && tokusei != 0x1A && !fightOutPokemonIsZokuseiDataId(pokemon, 2)) {
            UserWork[0x16003] = i;
            fightMsgctrlSetValue(0x1C, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(enemyTokusei))));
            fightMsgctrlSetValue(0x1E, (u32)ary[i]);
            ServerWork.work[5] = 2;
            return 2;
        }
        if (enemyTokusei == 0x2A && fightOutPokemonIsZokuseiDataId(pokemon, 8) == 1) {
            UserWork[0x16003] = i - 1;
            fightMsgctrlSetValue(0x1C, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(enemyTokusei))));
            fightMsgctrlSetValue(0x1E, (u32)ary[i]);
            ServerWork.work[5] = 2;
            return 2;
        }
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0xE) == 1 || fightOutPokemonIsJoutaiDataId(pokemon, 0x16) == 1 ||
        fightOutPokemonIsJoutaiDataId(pokemon, 0x25) == 1) {
        ServerWork.work[5] = 0;
        return 1;
    }
    return 0;
}

void fightSeqTurnCheck(void) {
    u8 i;
    u16 turn;

    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
    for (i = 0; i < 8; i++) {
        ServerWork.work[i] = 0;
    }
    fightFloorLoopValidFightOutPokemon(0, _fightSeqTurnCheckSubFightOutPokemon, 0, 0);
    fightFloorInitFightOutPokemonPtrAryFightWazaJoutai(0);
    fightSeqClearOneTurnCount(1);
    fightSeqFloorJoutaiCheck();
    fightSeqSideJoutaiCheck();
    fightSeqGetExpCheck();
    fightSeqSideJoutaiCheck2();
    fightSeqClearOneTurnCount(0);
    ServerStatusFlag &= ~0x200;
    ServerStatusFlag &= ~0x80000;
    ServerStatusFlag &= ~0x400000;
    ServerStatusFlag &= ~0x100000;
    UserWork[0x16002] = 0;
    UserWork[0x160A1] = 0;
    for (i = 0; i < 5; i++) {
        ServerWork.work[i] = 0;
    }
    if (fightGetFightResultId() == 0) {
        turn = fightFloor_GetTurnCount(0);
        turn++;
        if (turn > 0xFF) {
            turn = 0xFF;
        }
        fightFloor_SetTurnCount(0, turn);
        fightFloor_SetFisstAttackRnd(0, HSD_Rand());
        wazaSequenceSysFreeAllWaza();
        fightMenuAllFightTrainerCloseStatusMenu(0);
        fightMenuAllFightOutPokemonCloseStatusMenu(0);
        fightMenuCloseMsg();
    }
}

}

static u8 _fightSeqTurnCheckSubFightOutPokemon(void* pokemonPtr, u16 fightType, void* data) {
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;

    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    fightOutPokemonInitJoutaiDataId(pokemon, 0x11);
    if (fightOutPokemonIsJoutaiDataId(pokemon, 8) == 1 && fightOutPokemonIsJoutaiDataId(pokemon, 0x22) == 1) {
        fightOutPokemonInitJoutaiKeep(pokemon);
    }
    return 1;
}

extern "C" {

void fightSeqClearOneTurnCount(u8 flag) {
    u16 i;
    void* side;

    fightFloorLoopValidFightOutPokemon(0, _fightSeqClearOneTurnCountSub, &flag, 0);
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(0, i);
        if (side != 0) {
            fightSideInitJoutaiDataId(side, 0x4D);
        }
    }
}

}

static u8 _fightSeqClearOneTurnCountSub(void* pokemonPtr, u16 fightType, void* data) {
    int now;
    u16 turn;
    FightOutPokemon* pokemon = (FightOutPokemon*)pokemonPtr;

    if (*(u8*)data == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2B);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2C);
    } else {
        fightOutPokemonInitOneTurn(pokemon);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x32);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x37);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x33);
        turn = fightOutPokemon_GetFightoutTurnCount(pokemon);
        if (turn != 0) {
            fightOutPokemon_SetFightoutTurnCount(pokemon, turn - 1);
        }
        if (fightOutPokemonIsJoutaiDataId(pokemon, 0x12) == 1) {
            now = fightOutPokemonGetNowKaisuuJoutaiDataId(pokemon, 0x12);
            s8 max = fightOutPokemonGetKaisuuJoutaiDataId(pokemon, 0x12);
            if ((s8)((s8)now + 1) >= max) {
                fightOutPokemonInitJoutaiDataId(pokemon, 0x12);
            } else {
                fightOutPokemonSetNowKaisuuJoutaiDataId(pokemon, 0x12, (s8)now + 1);
            }
        }
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(pokemon) <= 0) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x14);
    }
    return 1;
}

extern "C" {

void fightSeqClearOneSelfTurnCount(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqClearOneSelfTurnCountSub, 0, 0);
}

}

static u8 _fightSeqClearOneSelfTurnCountSub(void* pokemon, u16 fightType, void* data) {
    fightOutPokemonInitOneSelfTurn((FightOutPokemon*)pokemon);
    return 1;
}
