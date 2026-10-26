#include <game/pxdvs/app/fight/fightSeq/fightSeqBasis.hpp>
#undef NULL
#define NULL 0

// Battle sequence command operands retain their original byte offsets and widths.
extern "C" {
typedef struct FIGHT_TRAINER FIGHT_TRAINER; typedef FIGHT_TRAINER FightTrainer;
typedef struct FightMenuLvupStatus FightMenuLvupStatus;
typedef struct FightOutPokemon FightOutPokemon;
typedef struct FightPokemon FightPokemon;
typedef struct FightSide FightSide;
typedef struct FightTarget FightTarget;
typedef struct FightWaza FightWaza;
typedef struct Hero Hero;
typedef struct HeroPokemonGetParam HeroPokemonGetParam;
typedef struct Pokemon Pokemon;
typedef struct WazaSequence WazaSequence;
extern FightPokemon *get_exp_fight_pokemon_ptr;
extern s8 ActionSeqNo; extern s32 ServerStatusFlag; extern u8 *UserWork;
char * GSmsgGetGSchar(u32);
s32 GSprint(s32, s32, s32, u32, const char *, ...);
void GSsndPlayVolume(u32, u32, u32, u32);
void GSthreadSwitch(void);
void *fightTrainer_GetSequencePtr(FIGHT_TRAINER*);
void DoModelAnimation__13ModelSequenceFi(void*,s32);
u16 HSD_Rand(void);
void Sequence_Free(void *);
WazaSequence* Sequence_GetWaza(void*, u16, u32);
void * Sequence_LoadWaza(void *,u32,s32,s32);
void Sequence_SetStatus(void *,s32);
void WazaSequence_Free(void *);
u8 WazaSequence_IsActive(void *);
void WazaSequence_Start(void *, u8);
void battleGridReplacePokemon(void *,void *);
s32 battleGridUpdate();
u8 dbgMenuFightGetTuikakoukaFlag();
s32 dbgMenuGetLayerID();
s32 fightAbicntFitMinMax(s32);
void fightAi_AddStoreWaza(FightOutPokemon *, FIGHT_TRAINER *, u16);
void fightAi_DereteExpectWaza(FightOutPokemon *, FIGHT_TRAINER *, u16);
void * fightFloorBiosGetFightFloorPtr(void);
u16 fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(s32, s32);
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(void *,u16,u8,FightOutPokemon *);
u16 fightFloorGetFightOutPokemonPtrAry(void *,u8,u8,FightOutPokemon *,FightOutPokemon **);
FightOutPokemon * fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(void *,u16,u8,u8,FightOutPokemon *);
FightOutPokemon * fightFloorGetFightOutPokemonPtrRandom(void *,u8,u8,FightOutPokemon *);
FIGHT_TRAINER * fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void *,FightOutPokemon *);
void * fightFloorGetFightOutPokemonPtrToHeroPtr(void *,FightOutPokemon *);
u8 fightFloorGetNowTenkouDataId(void *, u8);
s32 fightFloorGetStatus(s32, s32, s32, s32);
u16 fightFloorGetValidFightOutPokemonCount(void *,u8,FightOutPokemon *,u8);
u8 fightFloorIsIrekaeFightOutPokemon(s32);
u8 fightFloorIsNowEncountOpeningVirtualBattle(s32);
u8 fightFloorIsUseFightTimerCommand(s32);
void fightFloorLoopValidFightOutPokemon(void *,s32 (*)(FightOutPokemon *,u16,void *),void *,u8);
void fightFloorLoopValidFightTrainer(void *,s32 (*)(FIGHT_TRAINER *,u16,void *),void *,u8);
s32 fightFloorReplaceFightOutPokemonAttackToDefense(s32);
s32 fightFloorSetFightResultId(s32, s32);
s32 fightFloorSetTuusinErrorFightResult(s32);
s32 fightFloor_GetAppointMsgId(s32);
FightOutPokemon * fightFloor_GetAppointPokemonPtr(void *);
u32 fightFloor_GetEnvSndId(void*);
u8 fightFloor_GetFightKind(void*);
u8 fightFloor_GetFightKindDoCriticalAttackFlag(s32);
u8 fightFloor_GetFightKindGetExpFlag(s32);
u8 fightFloor_GetFightKindGetFriendFlag(s32);
u8 fightFloor_GetFightKindKeikentihueruFlag(s32);
u8 fightFloor_GetFightKindRegulationFlag(s32);
u16 fightFloor_GetFightSideFightOutPokemonSideMax(void *);
u32 fightFloor_GetFightType(void*);
u8 fightFloor_GetFightTypeEntryPokemonNum(s32);
u8 fightFloor_GetFightTypeFightoutPokemonNum(void *);
u8 fightFloor_GetFightTypeTrainerNum(s32);
s32 fightFloor_SetAppointItemDataId(s32, u16);
void fightFloor_SetAppointPokemonPtr(void *,FightOutPokemon *);
s32 fightFloor_SetAttackPokemonFightWazaJoutaiDataId(s32, s32);
s32 fightFloor_SetCriticakMsgId(s32, s32);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(void *,FightOutPokemon *);
void fightFloor_SetIrekaePokemonPtr(void *,FightOutPokemon *);
void fightFloor_SetItemPokemonPtr(void *,FightOutPokemon *);
void fightFloor_SetKizetuPokemonPtr(void *,FightOutPokemon *);
void fightFloor_SetTokuseiPokemonPtr(void *,FightOutPokemon *);
void fightFloor_SetTuikakoukaPokemonPtr(void *,FightOutPokemon *);
s32 fightFloor_SetWazakoukaMsgId(s32, u32);
u16 fightGetFightResultId();
void fightMainAllCamera(u32, u32);
s32 fightMainDebugMenu();
void fightMainWaitFrame(u16);
s32 fightMenuAllFightOutPokemonCloseStatusMenu(s32);
s32 fightMenuAllFightTrainerCloseStatusMenu(s32);
s32 fightMenuCloseInfoMenu(s32);
void fightMenuCloseMsg();
void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon*, u16, u32);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(s32, FightOutPokemon*, u16, u32, u32);
void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon*, u16, u32);
void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon*, u8, u32);
s32 fightMenuFightStatusStartAnimHP(s32, s16);
s32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon *,u8,s32);
u8 fightMenuOpenMsg(u32);
u8 fightMenuWazaKoukaMsg(u32,FightOutPokemon *,u16);
u8 fightMenuWazaOutMsg(FightOutPokemon *,u16);
void fightMsgctrlSetValue(u32, void*);
void fightOutPokemonAddFightOutPokemonEnemyDamage(FightOutPokemon *,FightOutPokemon *,u16);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightOutPokemonCheckMeetEnemyFightPokemon(FightOutPokemon *,FightPokemon *);
u8 fightOutPokemonCheckNoAttackFlag(FightOutPokemon *);
u8 fightOutPokemonCheckValid(FightOutPokemon *);
u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonCreate(FightOutPokemon *,FightPokemon *,s32);
void *fightOutPokemonCreateSequence(FightOutPokemon *, u8, s32);
s32 fightOutPokemonDoItemSoubi(FightOutPokemon *, s32, s32, s32);
s32 fightOutPokemonFreeAllSequenceWaza(FightOutPokemon *);
u32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon*, u16);
u32 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon*, u16);
s32 fightOutPokemonGetJoutaiMigawariHp(FightOutPokemon *);
s32 fightOutPokemonGetNicknamePtr(FightOutPokemon *);
Pokemon * fightOutPokemonGetPokemonPtr(FightOutPokemon *);
u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon *);
u32 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon*);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon *);
u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon*);
u32 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon*, u16);
u32 fightOutPokemonGetWazaZokuseiDataId(FightOutPokemon *);
u16 fightOutPokemonGetZokuseiDataId(FightOutPokemon *, s32);
void fightOutPokemonInit(FightOutPokemon*);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon*);
s32 fightOutPokemonInitJoutaiKie(FightOutPokemon *);
u8 fightOutPokemonIsAlly(FightOutPokemon *,FightOutPokemon *);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon*);
u8 fightOutPokemonIsHinsi(FightOutPokemon *);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon *);
u16 fightOutPokemonIsJoutaiKie(FightOutPokemon *);
u8 fightOutPokemonIsJoutaiNormal(FightOutPokemon *);
u8 fightOutPokemonIsUseHensinBuff(FightOutPokemon *);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon *, u16);
void fightOutPokemonKizetuEffect(FightOutPokemon*, u8);
s32 fightOutPokemonLoadWazaEffect(FightOutPokemon *, s32, s32, s32);
u32 fightOutPokemonNowHpWaruValue(FightOutPokemon *, u16);
void fightOutPokemonSetBuffJoutaiDataId(FightOutPokemon*, u16, u32);
void fightOutPokemonSetHensinStatusAfterLevelUp(FightOutPokemon*);
void fightOutPokemonSetIdBuffJoutaiDataId(FightOutPokemon*, u16, u16);
s32 fightOutPokemonSetJoutaiMigawariHp(FightOutPokemon *, s32);
void fightOutPokemonSetOumuWazaDataId(FightOutPokemon *,FightOutPokemon *,u16);
void fightOutPokemonSetVisibility(FightOutPokemon*, u8);
s32 fightOutPokemonSetWazaEffectDownFlag(FightOutPokemon *, s32);
u16 fightOutPokemonWazaEffect(FightOutPokemon *, s32, s32, s32, s32);
void fightOutPokemonWriteJoutaiDataId(FightOutPokemon*, u16, u16);
u8 fightOutPokemon_GetAbicntAverage(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntAvoid(FightOutPokemon*);
u8 fightOutPokemon_GetFightActionFlag(FightOutPokemon*);
FightPokemon * fightOutPokemon_GetFightPokemonPtr(FightOutPokemon *);
int fightOutPokemon_GetGamanDamageValue(FightOutPokemon*);
s16 fightOutPokemon_GetIrekaeTargetEntryId(FightOutPokemon*);
u8 fightOutPokemon_GetIrekaetaFlag(FightOutPokemon*);
u8 fightOutPokemon_GetItemKoraetaFlag(FightOutPokemon*);
s32 fightOutPokemon_GetKaigaraDamageValue(FightOutPokemon*);
u8 fightOutPokemon_GetKizetuFlag(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon*);
int fightOutPokemon_GetMyselfDamageAtkValue(FightOutPokemon*);
int fightOutPokemon_GetMyselfDamageSpeValue(FightOutPokemon*);
u8 fightOutPokemon_GetNoPressureFlag(FightOutPokemon*);
u8 fightOutPokemon_GetReceivesWazaHiraishinFlag(FightOutPokemon*);
void * fightOutPokemon_GetSequencePtr(FightOutPokemon *);
u32 fightOutPokemon_GetStockItemDataId(FightOutPokemon *);
u8 fightOutPokemon_GetTameWazaFlag(FightOutPokemon*);
u16 fightOutPokemon_GetUseWazaDataId(FightOutPokemon*);
u8 fightOutPokemon_GetVanishoffFlag(FightOutPokemon*);
void fightOutPokemon_SetDamageAtkTargetId(FightOutPokemon *,u32);
void fightOutPokemon_SetDamageAtkValue(FightOutPokemon*, s16);
void fightOutPokemon_SetDamageSpeTargetId(FightOutPokemon *,u32);
void fightOutPokemon_SetDamageSpeValue(FightOutPokemon*, s16);
void fightOutPokemon_SetGamanDamageTargetId(FightOutPokemon *,u32);
void fightOutPokemon_SetGamanDamageValue(FightOutPokemon*, s16);
void fightOutPokemon_SetHitWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetHitWazaZokuseiDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetIrekaeTargetEntryId(FightOutPokemon*, s16);
void fightOutPokemon_SetIrekaetaFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetItemKoraetaFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon*, s32);
void fightOutPokemon_SetKizetuFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetLastReceiveWazaTargetDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetLastSelectWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetLastUseWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetMyselfDamageAtkTargetId(FightOutPokemon *,u32);
void fightOutPokemon_SetMyselfDamageAtkValue(FightOutPokemon*, s16);
void fightOutPokemon_SetMyselfDamageSpeTargetId(FightOutPokemon *,u32);
void fightOutPokemon_SetMyselfDamageSpeValue(FightOutPokemon*, s16);
void fightOutPokemon_SetOutWazaKoukanaiFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetPassPpdecFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetReceivesWazaHiraishinFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetSequencePtr(FightOutPokemon*, void*);
void fightOutPokemon_SetSketchWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetStockItemDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetTameWazaFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetVanishoffFlag(FightOutPokemon*, u8);
u8 fightPokemonCheckFightOut(FightPokemon *);
s32 fightPokemonGetEffortFromPokemon(FightPokemon *, s32, u16);
s32 fightPokemonGetFriendFormPokemonFriendFilterId(FightPokemon *, s32);
u32 fightPokemonGetLevelToExp(FightPokemon *, u8);
char * fightPokemonGetNicknamePtr(FightPokemon *);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
u16 fightPokemonGetSoubiItemSoubiDataId(FightPokemon *);
s32 fightPokemonGrowBasisStatus(FightPokemon *, u32);
void fightPokemonInit(FightPokemon*);
u8 fightPokemonIsJoutaiDataId(FightPokemon*, u16);
void fightPokemonToMenuLvupStatus(FightPokemon*, FightMenuLvupStatus*);
s16 fightPokemon_GetEntryId(FightPokemon*);
u8 fightPokemon_GetHokakuFlag(FightPokemon*);
Pokemon* fightPokemon_GetMotoPokemonPtr(FightPokemon*);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
void fightPokemon_SetLevelUpFlag(FightPokemon*, u8);
u8 fightSeqAttackPokemonJoutaiCheck();
void fightSeqCheckSetHensinBuffToMotoFightPokemon(FightOutPokemon *,u16);
void fightSeqCheckSetHensinBuffToMotoPokemon(FightOutPokemon *,u16);
void fightSeqCheckSetHensinBuffToMotoPokemon2(FightOutPokemon *,u16,s32,s32);
u8 fightSeqCondChgAct(u8, u8, u8, u8*);
u16 fightSeqCondChgActTypeToPokemonStatusId(u8);
u8 fightSeqFightOutPokemonTokuseiCheckSinkuroAtk(FightOutPokemon *,FightOutPokemon *);
u8 fightSeqFightOutPokemonTokuseiCheckSinkuroDef(FightOutPokemon *,FightOutPokemon *);
u8 fightSeqFightOutPokemonTokuseiCheckWazaHit(FightOutPokemon *,FightOutPokemon *,u16);
u8 fightSeqFightOutPokemonTokuseiCheckWazaHitAfter(FightOutPokemon *,FightOutPokemon *);
s32 fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAll();
u8 fightSeqFightOutPokemonTokuseiCheckWazaHitBefore(FightOutPokemon *,FightOutPokemon *);
u8 fightSeqIsDoItemGetWaza(FightOutPokemon *);
void fightSeqKizetuInit(FightOutPokemon *);
s32 fightSeqMichidureCheckAct();
s32 fightSeqOpenMsg(s32);
void fightSeqPressurePpdecCheck(FightOutPokemon *,FightOutPokemon *,u16);
void fightSeqSoubiItemCheckWazaHitAfter(FightOutPokemon *,FightOutPokemon *);
s32 fightSeqSoubiItemCheckWazaHitAfterAll();
u8 fightSeqTameWazaCheck(u16);
u8 fightSeqTameWazaTurnCheck(FightOutPokemon *,u16);
void fightSeqVanishOff(FightOutPokemon *);
s32 fightSeqWazaDamageCalc(FightOutPokemon *,FightOutPokemon *,u32,u16,u32,u16);
void fightSeq_CallWazaSeq(u8 *);
u8 * fightSeq_GetWazaSeqPtr_u8(u32);
void fightSeq_JumpWazaSeq(u8 *);
void fightSeq_NextWazaSeq(u32);
u8 fightSideCheckValid(FightSide *);
u32 fightSideGetFightPokemonNokoriHp(FightSide *, u8, u8);
u32 fightSideGetJoutaiUserFightTargetId(FightSide *,u16);
u16 fightSideGetNokoriFightPokemonNum(FightSide *, u8, u8);
FIGHT_TRAINER * fightSideGetValidFightTrainerPtr(FightSide *,u16);
u8 fightSideIsJoutaiDataId(FightSide *, u16);
FIGHT_TRAINER * fightSide_GetFightTrainerPtr(FightSide *,u16);
s32 fightSide_SetMakibisiCheckFlag(FightSide *, s32);
s32 fightTargetDataBiosGetBuff(void *);
void * fightTargetDataBiosGetPtr(s32);
FightOutPokemon * fightTargetGetPtr(u16,FightOutPokemon *,u16);
FightOutPokemon * fightTargetGetPtrAsNowFightType(u32, FightOutPokemon *);
FightTarget* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u32, u16);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightTarget*, u8);
s32 fightTimerCommandBlock();
s32 fightTimerCommandInit();
s32 fightTimerCommandStart();
s32 fightTimerCommandTerminate();
u8 fightTrainerAiDB_GetParamStoreFlag(u32);
u8 fightTrainerCheckCanGetExp(FIGHT_TRAINER *);
FightOutPokemon * fightTrainerCheckFightPokemonFightOut(FIGHT_TRAINER *,FightPokemon *);
FightPokemon * fightTrainerCheckTemotiPokemonFightEntry(FIGHT_TRAINER *,u32);
u8 fightTrainerCheckValid(FIGHT_TRAINER *);
u32 fightTrainerDB_GetAiDataId(u16);
FightPokemon * fightTrainerGetEntryIdToFightPokemonPtr(FIGHT_TRAINER *,s16);
s32 fightTrainerGetFightOutPokemonToTemotiBanme(FIGHT_TRAINER *,FightOutPokemon *);
FightPokemon * fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER *,u16);
u8 fightTrainerIsGcHero(FightTrainer*);
u8 fightTrainerIsMineFightPokemon(FIGHT_TRAINER *,FightPokemon *);
u32 fightTrainerSearchIrekaeFightPokemon(FIGHT_TRAINER *,s16 *);
s16 fightTrainerSelectIrekaeFightPokemon(FIGHT_TRAINER *,u16,u8,FightOutPokemon *);
FightPokemon* fightTrainer_GetFightPokemonPtr(FightTrainer*, u16);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER *);
FightOutPokemon * fightTrainer_GetFightoutPokemonPtr(FIGHT_TRAINER *,u16);
Hero * fightTrainer_GetHeroPtr(FIGHT_TRAINER *);
u32 fightTrainer_GetKoban(FIGHT_TRAINER *);
s32 fightTrainer_SetKoban(FIGHT_TRAINER *, u32);
s32 fightWazaBiosCopy(void *, void *);
u8 fightWazaCheckWriteJoutaiDataId(FightWaza*, u16);
u8 fightWazaCriticalDataBiosGetBunbo(void *);
void * fightWazaCriticalDataBiosGetPtr(u16);
void fightWazaDoEffectFunc(u16,FightOutPokemon *,FightOutPokemon *,u8);
u8 fightWazaHitKakurituDataBiosGetKake(void *);
void * fightWazaHitKakurituDataBiosGetPtr(s8);
u8 fightWazaHitKakurituDataBiosGetWaru(void *);
void fightWazaInitJoutai(FightWaza*);
void fightWazaInitJoutaiDataId(FightWaza*, u16);
void fightWazaInitLoop(FightWaza *);
u8 fightWazaIsHit(FightWaza*);
u8 fightWazaIsJoutaiDataId(FightWaza*, u16);
u8 fightWazaIsJoutaiSousai(void *);
u8 fightWazaIsMix(void *);
void fightWazaWriteJoutaiDataId(FightWaza*, u16, u32);
u16 fightWazaWzxTypeFuncMigawari(u16,FightOutPokemon *,FightOutPokemon *,u8,u8);
u8 fightWaza_GetCritical(FightWaza*);
u32 fightWaza_GetDamage(FightWaza*);
u8 fightWaza_GetDamageValue(FightWaza*);
u32 fightWaza_GetHitDamage(FightWaza*);
u32 fightWaza_GetIryoku(FightWaza*);
u8 fightWaza_GetKaisuu(FightWaza *);
u16 fightWaza_GetUseWazaDataId(FightWaza*);
s32 fightWaza_GetWazaBanme(FightWaza *);
u32 fightWaza_GetZokusei(FightWaza *);
void fightWaza_SetCritical(FightWaza*, u8);
void fightWaza_SetDamage(FightWaza*, u32);
void fightWaza_SetHitDamage(FightWaza*, u32);
void fightWaza_SetKaisuu(FightWaza *, u8);
void fightWaza_SetMotoWazaDataId(FightWaza*, u16);
u8 figthOutPokemonGetLevel(FightOutPokemon *);
u16 figthOutPokemonGetPokemonDataId(FightOutPokemon *);
u32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon*);
s32 figthPokemonGetExp(FightPokemon *);
u8 figthPokemonGetLevel(FightPokemon *);
s32 figthPokemonSetExp(FightPokemon *, u32);
void fn_8014718C(FightOutPokemon*, u8);
u8 fn_80148688(FightOutPokemon*);
u32 heroGetStatus(Hero*, u32, u32);
u8 itemDataCheckValid(u16);
u8 menuCBRule_EnableSbToIceed();
u8 menuCBRule_EnableSbToSleep();
u8 menuCBRule_EnableSkillSwap();
u8 menuCBRule_EnableSkill_Michidure();
u8 menuCBRule_EnableSkill_SonicBoom();
u8 menuCBRule_ProhibitionSuicide();
s32 menuFightStatusStartAnimEXP(s32, s32);
s32 menuFightStatusWaitAnimeEXP(s32, s32);
s32 menuFightStatusWaitAnimeHP(s32, s32);
u8 menuIsCheck();
u8 pokemonCheckInfectPokerus(Pokemon *, s32);
u16 pokemonDB_GetGiveExp(u16);
u8 pokemonDB_GetTokuseiDataId(u16, u8);
u8 pokemonDB_GetZokuseiDataId(u32,u16);
s32 pokemonGetDarkPokemonLevel(s32);
u32 pokemonGetStatus(Pokemon *,u32,u16,u16);
void pokemonInit(Pokemon *);
u8 pokemonIsDarkPokemon(Pokemon *);
s8 pokemonSearchWazaDataId(Pokemon *,u16);
void pokemonSetStatus(Pokemon *,u32,u16,u16,u32);
u16 pokemon_GetHp(Pokemon *);
u32 pokemon_GetMaxHp(Pokemon*);
u16 pokemon_GetPokemonDataId(Pokemon *);
u16 pokemon_GetPokemonWazaDataId(Pokemon *,s8);
u8 pokemon_GetPokemonWazaPp(Pokemon *,s8);
u32 pokemon_GetPoolExp(Pokemon *);
u32 pokemon_GetSeikaku(Pokemon *);
u8 pokemon_GetTokuseiFlag(Pokemon *);
void pokemon_SetHp(Pokemon *,u32);
void pokemon_SetPokemonWazaPp(Pokemon *,s8,u32);
void pokemon_SetPoolExp(Pokemon *,u32);
s32 soundContinueBGMEX(u32, s32, s32);
u32 soundPauseBGMEX(s32, s32);
s32 soundPlayWait(s32);
u8 wazaCheckDarkWaza(u16);
u8 wazaDB_GetAddFightKoukaAvg(u16);
u8 wazaDB_GetAvg(u32);
u32 wazaDB_GetIryoku(u32);
u8 wazaDB_GetMajikku(u16);
u8 wazaDB_GetMamoru(u16);
u32 wazaDB_GetName(u16);
u8 wazaDB_GetOumugaesi(u16);
u8 wazaDB_GetRangeId(u16);
u16 wazaDB_GetSeqId(u16);
u8 wazaDB_GetYokodori(u16);
u8 wazaDB_GetZokuseiDataId(u16);
u8 wazaSequenceSysLastWazaIsImpactPoint(u32);
u8 waza_GetZokuseiKindData(u16);
u8 zokuseiBiosGetWazaKind(u32);
u16 zokuseiGetWazaJoutai(u16, u16);
void WS_CONDITION_CHECK();
s32 _WsWkcActSubJoutaiMigawari__FPvUsPv(FightOutPokemon *,u16,void *);
s32 _WsWkcActSubSetStockItem__FPvUsPv(FightOutPokemon *,u16,void *);
u32 _fightSeqFightEffectStatusUpDown__FUcUc(u8,u8);
void _fightSeqHinshiFriendCalc__FP15FightOutPokemon(FightOutPokemon *);
void _fightSeqStatusUpDownEffect__FUsUc(u16 , u8 );
s32 _fightSeqWsBadgecheckSubYokodori__FPvUsPv(void *,u16,void *);
s32 _fightSeqZenmetuCheckSubFightOutPokemon__FPvUsPv(void *,u16,void *);
s32 _fightSeqZenmetuCheckSubFightTrainer__FPvUsPv(void *,u16,void *);
u8 fightSeqBadgeCheck(FightOutPokemon *);
void fightSeqDamageLoss(u8,u8);
void fightSeqFightOutPokemonEffect(u32,FightOutPokemon *,u8,u8);
FightOutPokemon * fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(FightOutPokemon *);
u8 fightSeqGuardCheck(u8 , u16 );
u8 fightSeqIsAllwaysHit(u16);
u8 fightSeqIsGuard(FightOutPokemon *,u16);
u8 fightSeqIsTenkouHit(u16);
void fightSeqLoopInitAct(FightWaza *);
void fightSeqPpdecMonomane(FightOutPokemon *,u8,s32);
u8 fightSeqRegulationCheck(u16, FightOutPokemon *, FightOutPokemon *);
u8 fightSeqRegulationOverTwoCheck(u16, FightOutPokemon *);
u8 fightSeqRegulationZenmetuCheck(u16);
void fightSeqTuikaAct(u8,u8);
void fightSeqTypeCheck(u8,u8,u8,u8,u8);
u8 fightSeqWazaFloorJoutaiCheck(FightOutPokemon *,FightOutPokemon *,u16);
void fightSeqWazaSeqSet(u8,u16);
void fightSeqWsBadgeCheckYokodori__FP15FightOutPokemon(FightOutPokemon *);
void figthSeqZokuseiCheckCalc(void *, u16 , u16 , u8 );
FightOutPokemon * fightSeqSelectDefensePokemonPtr(FightOutPokemon *,u16,u16,void *,u8,u8,s8);
FightWaza* fightOutPokemon_GetKeepFightWazaPtr(FightOutPokemon*);
FightWaza * fightOutPokemon_GetFightWazaPtr(FightOutPokemon *);
u8 * fightSeq_GetWazaSeq(void);
void fightSeqFightEffect(u8,u32,u32);
void _fightSeqTuikaActSub__FUcUcPUc(u8,u8,u8 *);
extern u8 fight_seq_cond_chg_multi;
extern s8 fight_seq_server_work3_temp;
extern u8 fight_seq_tuika_param;
extern u8 fight_seq_wkc_work;
extern s32 fight_waza_critical_data_number;
extern u8 lbl_804EB918;
extern s16 msgFrame;
extern FightMenuLvupStatus old_menu_lvup_status;
extern u8 WAZA_AddDorobou[];
extern u8 WAZA_Bakadikara[];
extern u8 WAZA_BlankMsg[];
extern u8 WAZA_CondDownTsuikaMsg[];
extern u8 WAZA_CondUpTsuikaMsg[];
extern u8 WAZA_Genshinochikara[];
extern u8 WAZA_Hatakiotosu[];
extern u8 WAZA_Hiraishin[];
extern u8 WAZA_Ichigeki[];
extern u8 WAZA_Ikari[];
extern u8 WAZA_ItemKoraeta[];
extern u8 WAZA_Juunan[];
extern u8 WAZA_KizetsuA[];
extern u8 WAZA_KizetsuD[];
extern u8 WAZA_KizetsuK[];
extern u8 WAZA_Koraeta[];
extern u8 WAZA_Kousokuspin[];
extern u8 WAZA_LevelUp[];
extern u8 WAZA_MagicCort[];
extern u8 WAZA_Melt2[];
extern u8 WAZA_Meneki[];
extern u8 WAZA_Michidure[];
extern u8 WAZA_MigawariKizetsu[];
extern u8 WAZA_MineReshuffleStart[];
extern u8 WAZA_Mizunobeeru[];
extern u8 WAZA_Nentyaku[];
extern u8 WAZA_Nentyaku2[];
extern u8 WAZA_NoMahi[];
extern u8 WAZA_Onnen[];
extern u8 WAZA_OverHeat[];
extern u8 WAZA_PPNoneAttack[];
extern u8 WAZA_Seisinryoku[];
extern u8 WAZA_Wait[];
extern u8 WAZA_WazaEnd[];
extern u8 WAZA_Yokodori[];

void WS_TYPE_CHECK_NO_HIT(void) {
    fightSeq_GetWazaSeq();
    fightSeqTypeCheck(0U, 1U, 1U, 0U, 1U);
}

void WS_WKC_ACT(void) {
    u16 sp8;
    u8 *temp_r3;
    u32 var_r31;
    u32 var_r30;
    FightOutPokemon *temp_r3_2;
    FightWaza *temp_r3_3;
    FightOutPokemon *temp_r3_4;
    u16 temp_r3_5;
    s8 temp_r3_6;
    u16 temp_r3_7;
    FightOutPokemon *temp_r3_8;
    FightWaza *temp_r3_9;
    FightOutPokemon *temp_r3_10;
    FightOutPokemon *temp_r3_11;
    u16 var_r29;
    u16 var_r28;
    u16 var_r27;
    FightWaza *var_r26;
    u8 temp_r25;
    u8 var_r24;
    u8 var_r23;
    u8 var_r22;
    s32 var_r21;
    s32 var_r20;
    u16 var_r19;
    u16 var_r18;
    FightOutPokemon *var_r17;
    FightOutPokemon *var_r16;
    u32 temp_r15;
    u8 temp_r14;
    s32 temp_r0;
    s32 temp_r0_2;

    sp8 = (u16) fightFloor_GetFightType(NULL);
    var_r23 = 0;
    temp_r3 = fightSeq_GetWazaSeq();
    temp_r25 = *(u8 *)(temp_r3 + 0x1);
    temp_r14 = *(u8 *)(temp_r3 + 0x2);
    temp_r3_2 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    var_r17 = temp_r3_2;
    if (var_r17 != NULL) {
        var_r31 = fightOutPokemonGetSoubiItemSoubiDataId(temp_r3_2);
        temp_r3_3 = fightOutPokemon_GetFightWazaPtr(var_r17);
        var_r26 = temp_r3_3;
        var_r22 = fightWazaIsHit(temp_r3_3);
        var_r29 = fightOutPokemon_GetUseWazaDataId(var_r17);
        var_r27 = fightOutPokemon_GetMotoWazaDataId(var_r17);
        temp_r0 = (var_r27 - 0xFFFF) - 1;
        var_r18 = (var_r27 == 0xFFFF ? 0 : var_r27);
        var_r30 = fightWaza_GetZokusei(var_r26);
        var_r24 = wazaDB_GetRangeId(var_r29);
        var_r28 = wazaDB_GetSeqId(var_r29);
        var_r19 = wazaDB_GetIryoku((u32) var_r29);
    } else {
        var_r31 = 0;
        var_r26 = NULL;
        var_r22 = 0;
        var_r29 = 0;
        var_r27 = 0;
        var_r18 = 0;
        var_r30 = 9;
        var_r24 = 1;
        var_r28 = 0;
        var_r19 = 0;
    }
    temp_r3_4 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    var_r16 = temp_r3_4;
    if (var_r16 != NULL) {
        var_r21 = fightOutPokemon_GetMyselfDamageAtkValue(temp_r3_4);
        var_r20 = fightOutPokemon_GetMyselfDamageSpeValue(var_r16);
    } else {
        var_r21 = 0;
        var_r20 = 0;
    }
loop_6:
    switch (fight_seq_wkc_work) {
    case 0:
        if ((fightOutPokemonIsJoutaiDataId(var_r16, 0x13U) == 1) && (fightOutPokemonCheckFightOut(var_r16) == 1) && (var_r17 != var_r16) && (fightOutPokemonIsAlly(var_r17, var_r16) == 0) && (var_r22 == 1) && (((s16) var_r21 != 0) || ((s16) var_r20 != 0)) && (var_r19 != 0)) {
            temp_r3_5 = fightSeqCondChgActTypeToPokemonStatusId(1U);
            temp_r3_6 = pokemonGetStatus((Pokemon *) var_r16, 0U, temp_r3_5, 0U);
            if (temp_r3_6 < 0xC) {
                pokemonSetStatus((Pokemon *) var_r16, 0U, temp_r3_5, 0U, (u32) (s8) (temp_r3_6 + 1));
                fightSeq_CallWazaSeq(WAZA_Ikari);
                var_r23 = 1;
            }
        }
        fight_seq_wkc_work += 1;
        goto block_112;
    default:
        goto block_112;
    case 1:
        if ((fightOutPokemonIsJoutaiDataId(var_r16, 7U) == 1) && (fightOutPokemonCheckFightOut(var_r16) == 1) && (var_r17 != var_r16) && (fightOutPokemon_GetMyselfDamageSpeValue(var_r16) != 0) && (fightWazaIsHit(var_r26) == 1) && (wazaDB_GetZokuseiDataId(var_r29) == 0xA)) {
            fightOutPokemonInitJoutaiDataId(var_r16, 7U);
            fightSeqCheckSetHensinBuffToMotoPokemon(var_r16, 0x7CU);
            fightSeq_CallWazaSeq(WAZA_Melt2);
            var_r23 = 1;
        }
        fight_seq_wkc_work += 1;
        goto block_112;
    case 2:
        fightSeqFightOutPokemonTokuseiCheckSinkuroDef(var_r17, var_r16);
        fight_seq_wkc_work += 1;
        goto block_112;
    case 3:
        if (fightSeqFightOutPokemonTokuseiCheckWazaHitAfter(var_r17, var_r16) != 0) {
            var_r23 = 1;
        }
        fight_seq_wkc_work += 1;
        goto block_112;
    case 4:
        fightSeqFightOutPokemonTokuseiCheckWazaHitAfterAll();
        fight_seq_wkc_work += 1;
        goto block_112;
    case 5:
        fightSeqFightOutPokemonTokuseiCheckSinkuroAtk(var_r17, var_r16);
        fight_seq_wkc_work += 1;
        goto block_112;
    case 6:
        if ((ServerStatusFlag & 0x02000000) && ((u16) var_r31 == 0x1D) && (var_r27 != 0xA5) && (fightOutPokemonCheckWriteJoutaiDataId(var_r17, 0x36U) == 2)) {
            if ((var_r27 == 0xE2) && (fightWazaIsJoutaiDataId(var_r26, 0x45U) == 1)) {
                fight_seq_wkc_work += 1;
            } else {
                fightOutPokemonWriteJoutaiDataId(var_r17, 0x36U, 0U);
                fightOutPokemonSetIdBuffJoutaiDataId(var_r17, 0x36U, var_r27);
                goto block_41;
            }
        } else {
block_41:
            if (fightOutPokemonIsJoutaiDataId(var_r17, 0x36U) == 1) {
                temp_r15 = fightOutPokemonGetIdBuffJoutaiDataId(var_r17, 0x36U);
                if (pokemonSearchWazaDataId(fightOutPokemonGetPokemonPtr(var_r17), (u16) temp_r15) < 0) {
                    fightOutPokemonInitJoutaiDataId(var_r17, 0x36U);
                }
            }
            fight_seq_wkc_work += 1;
        }
        goto block_112;
    case 7:
        fightFloorLoopValidFightOutPokemon(NULL, _WsWkcActSubSetStockItem__FPvUsPv, NULL, 0U);
        fight_seq_wkc_work += 1;
        goto block_112;
    case 8:
        fightSeqSoubiItemCheckWazaHitAfterAll();
        fight_seq_wkc_work += 1;
        goto block_112;
    case 9:
        fightSeqSoubiItemCheckWazaHitAfter(var_r17, var_r16);
        fight_seq_wkc_work += 1;
        goto block_112;
    case 10:
        if (fightOutPokemonCheckFightOut(var_r17) == 1) {
            temp_r3_7 = fightOutPokemonIsJoutaiKie(var_r17);
            if (temp_r3_7 != 0) {
                if (temp_r3_7 != 0x1F) {
                    fightOutPokemonSetVisibility(var_r17, 0U);
                } else {
                    Sequence_SetStatus(fightOutPokemon_GetSequencePtr(var_r17), 3);
                }
            }
        }
        fight_seq_wkc_work += 1;
        goto block_112;
    case 11:
        if ((fightOutPokemonCheckFightOut(var_r17) == 1) && ((var_r22 == 0) || (fightOutPokemonIsJoutaiKie(var_r17) == 0) || (fightOutPokemonCheckNoAttackFlag(var_r17) == 1))) {
            fightOutPokemonInitJoutaiKie(var_r17);
            if ((var_r29 != 0x39) && (var_r29 != 0x14A)) {
                fightOutPokemon_SetVanishoffFlag(var_r17, 1U);
                fightSeqVanishOff(var_r17);
            }
        }
        fight_seq_wkc_work += 1;
        goto block_112;
    case 12:
        if ((fightOutPokemonCheckFightOut(var_r16) == 1) && (fightOutPokemon_GetVanishoffFlag(var_r16) == 0) && (fightOutPokemonIsJoutaiKie(var_r16) == 0)) {
            fightSeqVanishOff(var_r16);
        }
        fight_seq_wkc_work += 1;
        goto block_112;
    case 13:
        fightFloorLoopValidFightOutPokemon(NULL, _WsWkcActSubJoutaiMigawari__FPvUsPv, NULL, 0U);
        fight_seq_wkc_work += 1;
        goto block_112;
    case 14:
        if (ServerStatusFlag & 0x1000) {
            fightFloorReplaceFightOutPokemonAttackToDefense(0);
            ServerStatusFlag &= 0xFFFFEFFF;
            temp_r3_8 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
            var_r17 = temp_r3_8;
            if (var_r17 != NULL) {
                var_r31 = fightOutPokemonGetSoubiItemSoubiDataId(temp_r3_8);
                temp_r3_9 = fightOutPokemon_GetFightWazaPtr(var_r17);
                var_r26 = temp_r3_9;
                var_r22 = fightWazaIsHit(temp_r3_9);
                var_r29 = fightOutPokemon_GetUseWazaDataId(var_r17);
                var_r27 = fightOutPokemon_GetMotoWazaDataId(var_r17);
                temp_r0_2 = (var_r27 - 0xFFFF) - 1;
                var_r18 = (var_r27 == 0xFFFF ? 0 : var_r27);
                var_r30 = fightWaza_GetZokusei(var_r26);
                var_r24 = wazaDB_GetRangeId(var_r29);
                var_r28 = wazaDB_GetSeqId(var_r29);
                var_r19 = wazaDB_GetIryoku((u32) var_r29);
            } else {
                var_r31 = 0;
                var_r26 = NULL;
                var_r22 = 0;
                var_r29 = 0;
                var_r27 = 0;
                var_r18 = 0;
                var_r30 = 9;
                var_r24 = 1;
                var_r28 = 0;
                var_r19 = 0;
            }
            temp_r3_10 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
            var_r16 = temp_r3_10;
            if (var_r16 != NULL) {
                var_r21 = fightOutPokemon_GetMyselfDamageAtkValue(temp_r3_10);
                var_r20 = fightOutPokemon_GetMyselfDamageSpeValue(var_r16);
            } else {
                var_r21 = 0;
                var_r20 = 0;
            }
        }
        if ((wazaDB_GetSeqId(var_r18) != 0x7F) || ((wazaDB_GetSeqId(var_r18) == 0x7F) && (var_r22 == 0))) {
            fightOutPokemon_SetSketchWazaDataId(var_r17, var_r27);
        }
        if ((fightOutPokemonCheckFightOut(var_r17) == 1) && (wazaDB_GetSeqId(var_r18) != 0x7F)) {
            if (ServerStatusFlag & 0x02000000) {
                fightOutPokemon_SetLastSelectWazaDataId(var_r17, var_r27);
                fightOutPokemon_SetLastUseWazaDataId(var_r17, var_r29);
            } else {
                fightOutPokemon_SetLastSelectWazaDataId(var_r17, 0xFFFFU);
                fightOutPokemon_SetLastUseWazaDataId(var_r17, 0xFFFFU);
            }
            if (fightOutPokemonCheckFightOut(var_r16) == 1) {
                fightOutPokemon_SetLastReceiveWazaTargetDataId(var_r16, fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightTarget *) var_r17, (u8) sp8));
            }
            if ((ServerStatusFlag & 0x02000000) && (var_r22 == 1)) {
                if (var_r27 == 0xFFFFU) {
                    fightOutPokemon_SetHitWazaDataId(var_r16, var_r27);
                } else {
                    fightOutPokemon_SetHitWazaDataId(var_r16, var_r29);
                    fightOutPokemon_SetHitWazaZokuseiDataId(var_r16, (u16) var_r30);
                }
            } else {
                fightOutPokemon_SetHitWazaDataId(var_r16, 0xFFFFU);
            }
        }
        fight_seq_wkc_work += 1;
        goto block_112;
    case 15:
        if ((fightOutPokemonCheckValid(var_r17) == 1) && (wazaDB_GetOumugaesi(var_r18) == 1) && (ServerStatusFlag & 0x02000000) && (var_r17 != var_r16) && (fightOutPokemonCheckValid(var_r16) == 1) && (var_r22 == 1)) {
            fightOutPokemonSetOumuWazaDataId(var_r16, var_r17, var_r27);
        }
        fight_seq_wkc_work += 1;
        goto block_112;
    case 16:
        if (!(ServerStatusFlag & 0x80000) && (fightFloor_GetFightSideFightOutPokemonSideMax(NULL) >= 2U) && (fightOutPokemon_GetTameWazaFlag(var_r17) == 0) && (var_r24 == 4) && !(ServerStatusFlag & 0x200)) {
            temp_r3_11 = fightTargetGetPtrAsNowFightType(0xEU, var_r16);
            if (fightOutPokemonCheckFightOut(temp_r3_11) == 1) {
                fightFloor_SetDefPokemonAndAtkFightWazaTargetId(NULL, temp_r3_11);
                fightSeqLoopInitAct(var_r26);
                fight_seq_wkc_work = 0;
                ServerStatusFlag |= 0x200;
                fightSeq_CallWazaSeq(WAZA_BlankMsg);
                fightSeq_JumpWazaSeq(WazaEffectTbl[var_r28]);
                return;
            }
            ServerStatusFlag |= 0x200;
            goto block_109;
        }
block_109:
        fight_seq_wkc_work += 1;
        goto block_112;
    case 17:
        if (temp_r25 == 0) {
            fightMenuAllFightTrainerCloseStatusMenu(0);
            fightMenuAllFightOutPokemonCloseStatusMenu(0);
            fightMenuCloseMsg();
        }
        goto block_112;
    }
block_112:
    if ((temp_r25 == 1) && (var_r23 == 0)) {
        fight_seq_wkc_work = 0x11;
    }
    if ((temp_r25 == 2) && (temp_r14 == (u8) fight_seq_wkc_work)) {
        fight_seq_wkc_work = 0x11;
    }
    if (((u8) fight_seq_wkc_work == 0x11) || (var_r23 != 0)) {
        if (((u8) fight_seq_wkc_work == 0x11) && (var_r23 == 0)) {
            fightSeq_NextWazaSeq(3U);
        }
        return;
    }
    goto loop_6;
}

s32 _WsWkcActSubJoutaiMigawari__FPvUsPv(FightOutPokemon *arg0, u16 arg1, void *arg2) {
    if ((fightOutPokemonIsJoutaiDataId(arg0, 0x14U) == 1) && (fightOutPokemonGetJoutaiMigawariHp(arg0) <= 0)) {
        fightOutPokemonInitJoutaiDataId(arg0, 0x14U);
    }
    return 1;
}

s32 _WsWkcActSubSetStockItem__FPvUsPv(FightOutPokemon *arg0, u16 arg1, void *arg2) {
    u32 temp_r3;

    temp_r3 = fightOutPokemon_GetStockItemDataId(arg0);
    if ((u16)temp_r3 != 0) {
        fightOutPokemonDoItemSoubi(arg0, (s32) temp_r3, 1, 0);
        fightOutPokemon_SetStockItemDataId(arg0, 0U);
        fightSeqCheckSetHensinBuffToMotoPokemon(arg0, 0x82U);
    }
    return 1;
}

void WS_COND_CHG_BIT_CHECK(void) {
    u32 var_r3;
    u32 bits;
    u8 *temp_r3;
    u16 temp_r31;
    FightOutPokemon *temp_r3_2;
    u16 temp_r3_3;
    u8 temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    FightOutPokemon *temp_r23;
    u8 var_r22;
    s32 temp_r22;
    u16 var_r21;
    s32 var_r20;
    u8 temp_r19;
    u16 var_r0;
    u16 var_r0_2;

    var_r22 = 0;
    var_r21 = 0;
    var_r20 = 0;
    temp_r3 = fightSeq_GetWazaSeq();
    temp_r3_2 = fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    temp_r23 = fightTargetGetPtrAsNowFightType(2U, temp_r3_2);
    temp_r31 = fightOutPokemonGetTokuseiDataId(temp_r3_2);
    temp_r27 = *(u8 *)(temp_r3 + 0x3);
    var_r3 = *(u8 *)(temp_r3 + 0x2);
    if (temp_r27 & 1) {
        temp_r25 = temp_r27 & 2;
        var_r0 = 0x15;
        if (temp_r25 != 0) {
            var_r0 = 0x2D;
        }
        while((u8)var_r3 != 0) {
            bits=(u8)var_r3;
            if (bits & 1) {
                temp_r3_3 = fightSeqCondChgActTypeToPokemonStatusId(var_r22);
                temp_r19 = pokemonGetStatus((Pokemon *) temp_r3_2, 0U, temp_r3_3, 0U);
                if ((s32) (temp_r27 & 8) != 0) {
                    if (temp_r19 != 0) {
                        var_r20 += 1;
                        var_r21 = var_r0 + var_r22;
                    }
                } else if ((fightSideIsJoutaiDataId((FightSide *) temp_r23, 0x4CU) == 0) && (temp_r31 != 0x1D) && (temp_r31 != 0x49) && ((temp_r31 != 0x33) || (temp_r3_3 != 0xEB)) && ((temp_r31 != 0x34) || (temp_r3_3 != 0xE6)) && (temp_r19 != 0)) {
                    var_r20 += 1;
                    var_r21 = var_r0 + var_r22;
                }
            }
            var_r22 += 1;
            var_r3 = (u8) ((s32) bits >> 1);
        }
        if (var_r20 > 1) {
            if (temp_r25 != 0) {
                var_r21 = 0x3A;
            } else {
                var_r21 = 0x39;
            }
        }
    } else {
        temp_r26 = temp_r27 & 2;
        var_r0_2 = 0xE;
        if (temp_r26 != 0) {
            var_r0_2 = 0x26;
        }
        while((u8)var_r3 != 0) {
            bits=(u8)var_r3;
            if ((bits & 1) && ((u8)pokemonGetStatus((Pokemon *) temp_r3_2, 0U, fightSeqCondChgActTypeToPokemonStatusId(var_r22), 0U) < 0xCU)) {
                var_r20 += 1;
                var_r21 = var_r0_2 + var_r22;
            }
            var_r22 += 1;
            var_r3 = (u8) ((s32) bits >> 1);
        }
        if (var_r20 > 1) {
            if (temp_r26 != 0) {
                var_r21 = 0x38;
            } else {
                var_r21 = 0x37;
            }
        }
    }
    temp_r22 = temp_r27 & 4;
    if ((temp_r22 != 0) && (var_r20 < 2)) {
        fightSeq_NextWazaSeq(4U);
        return;
    }
    if ((var_r20 != 0) && ((u8) fight_seq_cond_chg_multi == 0)) {
        _fightSeqStatusUpDownEffect__FUsUc(var_r21, *(u8 *)(temp_r3 + 0x1));
        if ((temp_r22 != 0) && (var_r20 > 1)) {
            fight_seq_cond_chg_multi = 1;
        }
        fightSeq_NextWazaSeq(4U);
        return;
    }
    fightSeq_NextWazaSeq(4U);
}

void _fightSeqStatusUpDownEffect__FUsUc(u16 arg0, u8 arg1) {
    FightOutPokemon *temp_r3;

    temp_r3 = fightTargetGetPtrAsNowFightType(arg1, NULL);
    if (arg0 == 0x37 || arg0 == 0x38) {
        fightSeqFightOutPokemonEffect(0x2CU, temp_r3, 0U, 1U);
        return;
    }
    if (arg0 == 0x39 || arg0 == 0x3A) {
        fightSeqFightOutPokemonEffect(0x3CU, temp_r3, 0U, 1U);
        return;
    }
    switch (arg0) {
    case 0xF:
    case 0x12:
    case 0x27:
    case 0x2A:
        fightSeqFightOutPokemonEffect(0x26U, temp_r3, 0U, 1U);
        return;
    case 0x10:
    case 0x13:
    case 0x15:
    case 0x28:
    case 0x2B:
    case 0x2D:
        fightSeqFightOutPokemonEffect(0x28U, temp_r3, 0U, 1U);
        return;
    case 0x11:
    case 0x29:
        fightSeqFightOutPokemonEffect(0x2AU, temp_r3, 0U, 1U);
        return;
    case 0x14:
    case 0x2C:
        fightSeqFightOutPokemonEffect(0x2CU, temp_r3, 0U, 1U);
        return;
    case 0x16:
    case 0x19:
    case 0x2E:
    case 0x31:
        fightSeqFightOutPokemonEffect(0x27U, temp_r3, 0U, 1U);
        return;
    case 0x17:
    case 0x1A:
    case 0x1C:
    case 0x2F:
    case 0x32:
    case 0x34:
        fightSeqFightOutPokemonEffect(0x29U, temp_r3, 0U, 1U);
        return;
    case 0x18:
    case 0x30:
        fightSeqFightOutPokemonEffect(0x2BU, temp_r3, 0U, 1U);
        return;
    case 0x1B:
    case 0x33:
        fightSeqFightOutPokemonEffect(0x3CU, temp_r3, 0U, 1U);
        /* fallthrough */
        return;
    }
}

void WS_COND_CHG_WORK_SET(void) {
    u32 temp_r3;
    s32 var_r31;
    s32 temp_r0;

    var_r31 = 0;
    fightSeq_GetWazaSeq();
    temp_r3 = UserWork[0x1601E];
    temp_r0 = temp_r3 & 0xF0;
    switch (temp_r0) {                              /* irregular */
    case 0x10:
        var_r31 = 0xF;
        break;
    case 0x20:
        var_r31 = 0x27;
        break;
    case 0x90:
        var_r31 = 0x16;
        break;
    case 0xA0:
        var_r31 = 0x2E;
        break;
    }
    temp_r3 = (temp_r3 & 0xF) - 1;
    UserWork[0x160A4] = (s8)(var_r31 + temp_r3);
    UserWork[0x160A5] = 0;
    fightSeq_NextWazaSeq(1U);
}

void fightSeqFightEffect(u8 arg0, u32 arg1, u32 arg2) {
    BasisServerWork *temp_r5;
    u8 temp_r5_2;
    u32 var_r3;
    u8 temp_r3;
    FightOutPokemon *temp_r31;
    s32 temp_r3_2;
    FightOutPokemon *temp_r29;
    void *temp_r29_2;
    u32 var_r28;
    FightOutPokemon *temp_r28;
    u32 temp_r28_2;
    u8 temp_r27;
    void *temp_r26;
    u8 temp_r0;
    u8 temp_r0_2;

    temp_r27 = fightFloor_GetFightType(NULL);
    temp_r31 = fightTargetGetPtrAsNowFightType(arg0, NULL);
    temp_r29 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r28 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    temp_r0 = UserWork[0x1601E];
    temp_r3 = temp_r0 & 0xF;
    temp_r0_2 = temp_r0 & 0xF0;
    if ((arg1 == 0x11) || ((u32) (arg1 - 1) <= 1U) || (arg1 == 0x1A)) {
        if (arg1 == 1) {
            if ((temp_r5 = &ServerWork) != NULL) {
                temp_r5_2 = temp_r5->flags[3];
                if (temp_r5_2 != 0) {
                    switch (temp_r5_2) {                /* switch 1; irregular */
                    case 15:                            /* switch 1 */
                    case 18:                            /* switch 1 */
                        var_r3 = 0x26;
                        break;
                    case 16:                            /* switch 1 */
                    case 19:                            /* switch 1 */
                    case 21:                            /* switch 1 */
                        var_r3 = 0x28;
                        break;
                    case 17:                            /* switch 1 */
                        var_r3 = 0x2A;
                        break;
                    case 20:                            /* switch 1 */
                        var_r3 = 0x2C;
                        break;
                    case 22:                            /* switch 1 */
                    case 25:                            /* switch 1 */
                        var_r3 = 0x27;
                        break;
                    case 23:                            /* switch 1 */
                    case 26:                            /* switch 1 */
                    case 28:                            /* switch 1 */
                        var_r3 = 0x29;
                        break;
                    case 24:                            /* switch 1 */
                        var_r3 = 0x2B;
                        break;
                    case 27:                            /* switch 1 */
                        var_r3 = 0x3C;
                        break;
                    default:                            /* switch 1 */
                        var_r3 = _fightSeqFightEffectStatusUpDown__FUcUc(temp_r0_2, temp_r3);
                        break;
                    }
                } else {
                    var_r3 = _fightSeqFightEffectStatusUpDown__FUcUc(temp_r0_2, temp_r3);
                }
            } else {
                var_r3 = _fightSeqFightEffectStatusUpDown__FUcUc(temp_r0_2, temp_r3);
            }
            fightSeqFightOutPokemonEffect(var_r3, temp_r31, 0U, 1U);
        }
        if (arg1 == 0x1A) {
            fightSeqFightOutPokemonEffect(0x2DU, temp_r31, 0U, 1U);
        }
        if (arg1 == 0x11) {
            fightOutPokemonLoadWazaEffect(temp_r31, 0x121, 1, 0);
            fightOutPokemonLoadWazaEffect(temp_r29, 0x121, 2, 0);
            fightOutPokemonWazaEffect(temp_r31, 0x121, 1, 1, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            fightOutPokemonWazaEffect(temp_r29, 0x121, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
        }
        if (arg1 == 2) {
            fightWazaWzxTypeFuncMigawari(0xA4U, temp_r31, temp_r31, 0U, 0U);
        }
    } else {
        if (ServerStatusFlag & 0x80) {
            fightSeq_CallWazaSeq(WAZA_Wait);
            return;
        }
        if (((u32) (arg1 - 0xA) <= 3U) || (arg1 == 0x25) || ((u32) (arg1 - 0x20) <= 2U) || (arg1 == 0x1E)) {
            if (arg1 == 0xA) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0xF0, 1, 0);
                fightOutPokemonWazaEffect(temp_r31, 0xF0, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0xB) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0xF1, 1, 0);
                fightOutPokemonWazaEffect(temp_r31, 0xF1, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0xC) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0xC9, 2, 0);
                fightOutPokemonWazaEffect(temp_r31, 0xC9, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0xD) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0x102, 2, 0);
                fightOutPokemonWazaEffect(temp_r31, 0x102, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0x25) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0x16F, 2, 0);
                fightOutPokemonWazaEffect(temp_r31, 0x16F, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0x20) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0xF0, 1, 0);
                fightOutPokemonWazaEffect(temp_r31, 0xF0, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0x22) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0xC9, 1, 0);
                fightOutPokemonWazaEffect(temp_r31, 0xC9, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0x21) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0xF1, 1, 0);
                fightOutPokemonWazaEffect(temp_r31, 0xF1, 1, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0x1E) {
                if (fightFloorGetNowTenkouDataId(NULL, 0U) == 2) {
                    fightSeqFightOutPokemonEffect(0x80U, temp_r31, 0U, 0U);
                    return;
                }
                if (fightFloorGetNowTenkouDataId(NULL, 0U) == 1) {
                    fightSeqFightOutPokemonEffect(0x7FU, temp_r31, 0U, 0U);
                    return;
                }
                if (fightFloorGetNowTenkouDataId(NULL, 0U) == 3) {
                    fightSeqFightOutPokemonEffect(0x7EU, temp_r31, 0U, 0U);
                    return;
                }
                if (fightFloorGetNowTenkouDataId(NULL, 0U) == 4) {
                    fightSeqFightOutPokemonEffect(0x7DU, temp_r31, 0U, 0U);
                    return;
                }
                if (fightFloorGetNowTenkouDataId(NULL, 0U) == 5) {
                    fightSeqFightOutPokemonEffect(0xDCU, temp_r31, 0U, 0U);
                    return;
                }
                fightSeqFightOutPokemonEffect(0x9DU, temp_r31, 0U, 0U);
            }
        } else {
            if (arg1 == 0x17) {
                fightSeqFightOutPokemonEffect(0x57U, temp_r31, 0U, 1U);
            }
            if (arg1 == 0x1F) {
                fightSeqFightOutPokemonEffect(0x9DU, temp_r31, 0U, 0U);
            }
            if (arg1 == 0x18) {
                fightSeqFightOutPokemonEffect(0x58U, temp_r31, 0U, 1U);
            }
            if (arg1 == 0x23) {
                fightSeqFightOutPokemonEffect(0xA3U, temp_r31, 0U, 1U);
            }
            if (arg1 == 0x24) {
                fightSeqFightOutPokemonEffect(0xD8U, temp_r31, 0U, 1U);
            }
            if (arg1 == 0x19) {
                fightOutPokemonLoadWazaEffect(temp_r31, 1, 2, 0);
                fightOutPokemonWazaEffect(temp_r31, 1, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
            }
            if (arg1 == 0xE) {
                fightSeqFightOutPokemonEffect(0x38U, temp_r31, 0U, 1U);
            }
            if (arg1 == 0x16) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0x111, 3, 0);
                fightOutPokemonWazaEffect(temp_r31, 0x111, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0x12) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0xF8, 2, 0);
                fightOutPokemonWazaEffect(temp_r31, 0xF8, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
            }
            if (arg1 == 0x13) {
                fightOutPokemonLoadWazaEffect(temp_r28, 0x161, 2, 0);
                fightOutPokemonWazaEffect(temp_r28, 0x161, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
            }
            if (arg1 == 0x15) {
                fightSeqFightOutPokemonEffect(0x3BU, temp_r31, 0U, 1U);
            }
            if (arg1 == 7) {
                fightSeqFightOutPokemonEffect(0x39U, temp_r31, 0U, 1U);
            }
            if (arg1 == 0x1B) {
                fightSeqFightOutPokemonEffect(0x32U, temp_r31, 0U, 1U);
            }
            if (arg1 == 0x1C) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0x36, 3, 0);
                fightOutPokemonWazaEffect(temp_r31, 0x36, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0x1D) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0x74, 3, 0);
                fightOutPokemonWazaEffect(temp_r31, 0x74, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 9) {
                fightSeqFightOutPokemonEffect(0x86U, temp_r31, 0U, 1U);
            }
            if (arg1 == 6) {
                temp_r3_2 = fightOutPokemonGetIdBuffJoutaiDataId(temp_r31, 0xEU);
                fightOutPokemonLoadWazaEffect(temp_r31, temp_r3_2, 2, 0);
                fightOutPokemonWazaEffect(temp_r31, temp_r3_2, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x12)));
            }
            if (arg1 == 0x10) {
                if (fightOutPokemon_GetUseWazaDataId(temp_r31) == 0x157) {
                    fightOutPokemonLoadWazaEffect(temp_r31, 0x157, 3, 0);
                    fightOutPokemonWazaEffect(temp_r31, 0x157, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
                }
                if (fightOutPokemon_GetUseWazaDataId(temp_r31) == 0xA8) {
                    fightOutPokemonLoadWazaEffect(temp_r31, 0xA8, 3, 0);
                    fightOutPokemonWazaEffect(temp_r31, 0xA8, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
                }
            }
            if (arg1 == 0) {
                temp_r28_2 = (u8)fightFloorGetNowTenkouDataId(NULL, 1U);
                temp_r29_2 = fightOutPokemon_GetSequencePtr(temp_r31);
                temp_r26 = fightOutPokemonCreateSequence(temp_r31, temp_r28_2, -1);
                switch ((s32) temp_r28_2) {         /* switch 2; irregular */
                case 1:                             /* switch 2 */
                    var_r28 = 0x84;
                    break;
                case 2:                             /* switch 2 */
                    var_r28 = 0x85;
                    break;
                case 4:                             /* switch 2 */
                    var_r28 = 0x82;
                    break;
                default:                            /* switch 2 */
                case 3:                             /* switch 2 */
                    var_r28 = 0x83;
                    break;
                }
                Sequence_LoadWaza(temp_r29_2, 0x81U, 4, 0);
                Sequence_LoadWaza(temp_r26, var_r28, 4, 0);
                fightMenuFightOutPokemonOpenStatusMenu(temp_r31, temp_r27, 1U);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, temp_r31, temp_r27, 0U, 1U);
                fightSeqFightOutPokemonEffect(0x81U, temp_r31, 1U, 0U);
                battleGridReplacePokemon(temp_r29_2, temp_r26);
                battleGridUpdate();
                fightOutPokemon_SetSequencePtr(temp_r31, temp_r26);
                fightSeqFightOutPokemonEffect(var_r28, temp_r31, 0U, 0U);
                Sequence_Free(temp_r29_2);
            }
            if (arg1 == 0x14) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0x75, 3, 0);
                fightOutPokemonWazaEffect(temp_r31, 0x75, 3, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
            if (arg1 == 0x26) {
                fightOutPokemonLoadWazaEffect(temp_r31, 0x164, 2, 0);
                fightOutPokemonWazaEffect(temp_r31, 0x164, 2, 0, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
            }
        }
    }
}

u32 _fightSeqFightEffectStatusUpDown__FUcUc(u8 arg0, u8 arg1) {
    u8 var_r5;
    u32 var_r3;

    switch ((s32) arg0) {                    /* irregular */
    case 0x10:
        var_r5 = 1;
        break;
    case 0x20:
        var_r5 = 1;
        break;
    case 0x90:
        var_r5 = 0;
        break;
    case 0xA0:
        var_r5 = 0;
        break;
    }
    if ((arg1 == 1) || (arg1 == 4)) {
        if (var_r5 == 1) {
            var_r3 = 0x26;
        } else {
            var_r3 = 0x27;
        }
    }
    if ((arg1 == 2) || (arg1 == 5) || (arg1 == 7)) {
        if (var_r5 == 1) {
            var_r3 = 0x28;
        } else {
            var_r3 = 0x29;
        }
    }
    if (arg1 == 3) {
        if (var_r5 == 1) {
            var_r3 = 0x2A;
        } else {
            var_r3 = 0x2B;
        }
    }
    if (arg1 == 6) {
        if (var_r5 == 1) {
            var_r3 = 0x2C;
        } else {
            var_r3 = 0x3C;
        }
    }
    return var_r3;
}

void fightSeqFightOutPokemonEffect(u32 arg0, FightOutPokemon *arg1, u8 arg2, u8 arg3) {
    u32 effect = arg0;
    void *temp_r3;
    u8 temp_r30;

    temp_r30 = fightFloor_GetFightType(NULL);
    temp_r3 = fightOutPokemon_GetSequencePtr(arg1);
    if (temp_r3 != NULL) {
        effect = (u32)Sequence_LoadWaza(temp_r3, effect, 4, 0);
        if ((void *)effect != NULL) {
            WazaSequence_Start((void *)effect, 1U);
            if (arg3 == 1) {
                fightMenuFightOutPokemonOpenStatusMenu(arg1, temp_r30, 1U);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, arg1, temp_r30, 0U, 1U);
            }
            if (arg2 == 1) {
                while (WazaSequence_IsActive((void*)effect) != 0) {
                    GSthreadSwitch();
                }
                WazaSequence_Free((void *)effect);
                if (arg3 == 1) {
                    fightMenuFightOutPokemonCloseStatusMenu(arg1, temp_r30, 0U);
                }
            }
        }
    }
}

void WS_FIGHT_EFFECT2(void) {
    s32 temp_r4;
    u8 *var_r3;
    u8 *temp_r3;
    u8 var_r0;
    u16 var_r5;

    temp_r3 = fightSeq_GetWazaSeq();
    fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    temp_r4 = *(u32 *)(temp_r3 + 0x2);
    if ((u32) ((temp_r4 & 0xFF000000) + 0x01000000) == 0U) {
        var_r3 = &UserWork[temp_r4 & 0xFFFFFF];
    } else {
        var_r3 = (u8 *) temp_r4;
    }
    if (var_r3 != NULL) {
        var_r0 = *var_r3;
    } else {
        var_r0 = 0;
    }
    if (*(u16 **)(temp_r3 + 0x6) != NULL) {
        var_r5 = **(u16 **)(temp_r3 + 0x6);
    } else {
        var_r5 = 0;
    }
    fightSeqFightEffect(*(u8 *)(temp_r3 + 0x1), var_r0, var_r5);
    fightSeq_NextWazaSeq(0xAU);
}

void WS_FIGHT_EFFECT(void) {
    u16 *var_r5;
    s32 temp_r4;
    u8 *temp_r3;
    u16 var_r0;

    temp_r3 = fightSeq_GetWazaSeq();
    fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    temp_r4 = *(u32 *)(temp_r3 + 0x3);
    if ((u32) ((temp_r4 & 0xFF000000) + 0x01000000) == 0U) {
        var_r5 = (u16 *)&UserWork[temp_r4 & 0xFFFFFF];
    } else {
        var_r5 = (u16 *) temp_r4;
    }
    if (var_r5 != NULL) {
        var_r0 = *var_r5;
    } else {
        var_r0 = 0;
    }
    fightSeqFightEffect(*(u8 *)(temp_r3 + 0x1), (u32) *(u8 *)(temp_r3 + 0x2), (u32) var_r0);
    fightSeq_NextWazaSeq(7U);
}

void WS_ALERTEND(void) {
    ActionSeqNo = 2;
}

void WS_SPEABI_HAVE_CHECK(void) {
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    if (fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(NULL, (u16) *(u8 *)(temp_r3 + 0x1), 0U, 0U, NULL) != NULL) {
        fightSeq_JumpWazaSeq(*(u8 * *)(temp_r3 + 0x2));
        return;
    }
    fightSeq_NextWazaSeq(6U);
}

void WS_MONS_TYPE(void) {
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    if (fightOutPokemonIsZokuseiDataId(fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL), (u16) *(u8 *)(temp_r3 + 0x2)) == 1) {
        fightSeq_JumpWazaSeq(*(u8 * *)(temp_r3 + 0x3));
        return;
    }
    fightSeq_NextWazaSeq(7U);
}

void WS_GOSUB(void) {
    fightSeq_CallWazaSeq(*(u8 * *)(fightSeq_GetWazaSeq() + 0x1));
    fightSeq_NextWazaSeq(5U);
}

void WS_SPEABIEND(void) {
    ActionSeqNo = 2;
}

void WS_SEQEND(void) {
    ActionSeqNo = 1;
}

void WS_WAZAEND(void) {
    ActionSeqNo = 1;
}

void WS_SEQRET(void) {
    ActionSeqNo = 2;
}

void WS_HP_GAUGE_REDRAW(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(2U);
}

void WS_CLIENT_BIT_WAIT(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1U);
}

void WS_WAIT(void) {
    fightMainWaitFrame(*(u16 *)(fightSeq_GetWazaSeq() + 0x1));
    fightSeq_NextWazaSeq(3U);
}

void WS_RESET32BIT(void) {
    s32 *temp_r6;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r6 = *(s32 * *)(temp_r3 + 0x1);
    *temp_r6 &= *(u32 *)(temp_r3 + 0x5) ^ -1;
    fightSeq_NextWazaSeq(9U);
}

void WS_RESET16BIT(void) {
    u16 *temp_r5;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u16 * *)(temp_r3 + 0x1);
    *temp_r5 &= *(u16 *)(temp_r3 + 0x5) ^ 0xFFFF;
    fightSeq_NextWazaSeq(7U);
}

void WS_RESET8BIT(void) {
    u8 *temp_r5;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u8 * *)(temp_r3 + 0x1);
    *temp_r5 &= *(u8 *)(temp_r3 + 0x5) ^ 0xFF;
    fightSeq_NextWazaSeq(6U);
}

void WS_SET32BIT(void) {
    s32 *temp_r5;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(s32 * *)(temp_r3 + 0x1);
    *temp_r5 |= *(u32 *)(temp_r3 + 0x5);
    fightSeq_NextWazaSeq(9U);
}

void WS_SET16BIT(void) {
    u16 *temp_r5;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u16 * *)(temp_r3 + 0x1);
    *temp_r5 |= *(u16 *)(temp_r3 + 0x5);
    fightSeq_NextWazaSeq(7U);
}

void WS_SET8BIT(void) {
    u8 *temp_r5;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u8 * *)(temp_r3 + 0x1);
    *temp_r5 |= *(u8 *)(temp_r3 + 0x5);
    fightSeq_NextWazaSeq(6U);
}

void WS_SETWORKOFS(void) {
    u8 *dst;
    s32 i;
    u8 *src;
    u8 *srcOfs;
    u8 n;
    u8 *p;

    p = fightSeq_GetWazaSeq();
    n = *(u8 *)(p + 0xD);
    dst = *(u8 **)(p + 0x1);
    src = *(u8 **)(p + 0x5);
    srcOfs = *(u8 **)(p + 0x9);
    for (i = 0; i < n; i++) {
        *dst++ = src[i + *srcOfs];
    }
    fightSeq_NextWazaSeq(0xEU);
}

void WS_SETWORK(void) {
    u8 *dst;
    u8 *src;
    u8 n;
    u8 *p;
    s32 i;

    p = fightSeq_GetWazaSeq();
    dst = *(u8 **)(p + 0x1);
    src = *(u8 **)(p + 0x5);
    n = *(u8 *)(p + 0x9);
    for (i = 0; i < n; i++) {
        dst[i] = src[i];
    }
    fightSeq_NextWazaSeq(0xAU);
}

void WS_SUBVALUE(void) {
    u8 *temp_r4;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r4 = *(u8 * *)(temp_r3 + 0x1);
    *temp_r4 -= *(u8 *)(temp_r3 + 0x5);
    fightSeq_NextWazaSeq(6U);
}

void WS_ADDVALUE(void) {
    u8 *temp_r5;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u8 * *)(temp_r3 + 0x1);
    *temp_r5 += *(u8 *)(temp_r3 + 0x5);
    fightSeq_NextWazaSeq(6U);
}

void WS_SETVALUE(void) {
    u8 *var_r4;
    s32 temp_r5;
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u32 *)(temp_r3 + 0x1);
    if ((u32) ((temp_r5 & 0xFF000000) + 0x01000000) == 0U) {
        var_r4 = UserWork + (temp_r5 & 0xFFFFFF);
    } else {
        var_r4 = (u8 *) temp_r5;
    }
    for (s32 i = 0; i < 1; i++) {
        var_r4[i] = temp_r3[i + 5];
    }
    fightSeq_NextWazaSeq(6U);
}

void WS_IFWNE(void) {
    u8 *var_r5;
    u8 *var_r6;
    u8 temp_r7;
    u8 var_r8;
    u8 *temp_r3;
    u8 *tgt;
    u8 var_r31;

    var_r31 = 0;
    temp_r3 = fightSeq_GetWazaSeq();
    var_r5 = *(u8 * *)(temp_r3 + 0x1);
    var_r8 = 0;
    var_r6 = *(u8 * *)(temp_r3 + 0x5);
    temp_r7 = *(u8 *)(temp_r3 + 0x9);
    tgt = *(u8 * *)(temp_r3 + 0xA);
    for (; var_r8 < temp_r7; var_r8++) {
        if (*var_r5 == *var_r6) {
            var_r31++;
        }
        var_r5++;
        var_r6++;
    }
    if (var_r31 != temp_r7) {
        fightSeq_JumpWazaSeq(tgt);
    } else {
        fightSeq_NextWazaSeq(0xEU);
    }
}

void WS_IFWEQ(void) {
    u8 *var_r4;
    u8 *var_r5;
    u8 *temp_r3;
    u8 *temp_r31;
    u8 temp_r30;
    u8 var_r29;

    temp_r3 = fightSeq_GetWazaSeq();
    var_r4 = *(u8 * *)(temp_r3 + 0x1);
    var_r5 = *(u8 * *)(temp_r3 + 0x5);
    temp_r30 = *(u8 *)(temp_r3 + 0x9);
    temp_r31 = *(u8 * *)(temp_r3 + 0xA);
    for (var_r29 = 0; var_r29 < temp_r30; var_r29++) {
        if (*var_r4 != *var_r5) {
            fightSeq_NextWazaSeq(0xEU);
            break;
        }
        var_r4++;
        var_r5++;
    }
    if (var_r29 == temp_r30) {
        fightSeq_JumpWazaSeq(temp_r31);
    }
}

void WS_IF32(void) {
    s32 temp_r5;
    u8 *temp_r3;
    u8 *temp_r31;
    u32 temp_r30;
    u8 temp_r29;
    u32 *var_r28;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u32 *)(temp_r3 + 0x2);
    if ((u32) ((temp_r5 & 0xFF000000) + 0x01000000) == 0U) {
        var_r28 = (u32 *)&UserWork[temp_r5 & 0xFFFFFF];
    } else {
        var_r28 = (u32 *) temp_r5;
    }
    temp_r29 = *(u8 *)(temp_r3 + 0x1);
    temp_r30 = *(u32 *)(temp_r3 + 0x6);
    temp_r31 = *(u8 * *)(temp_r3 + 0xA);
    fightSeq_NextWazaSeq(0xEU);
    switch ((s32) temp_r29) {                       /* irregular */
    case 0:
        if ((u32) *var_r28 == temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 1:
        if ((u32) *var_r28 != temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 2:
        if ((u32) *var_r28 > temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 3:
        if ((u32) *var_r28 < temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 4:
        if (*var_r28 & temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 5:
        if (!(*var_r28 & temp_r30)) {
            fightSeq_JumpWazaSeq(temp_r31);
        }
        break;
    }
}

void WS_IF16(void) {
    s32 temp_r5;
    u8 *temp_r3;
    u8 *temp_r31;
    u16 temp_r30;
    u8 temp_r29;
    u16 *var_r28;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u32 *)(temp_r3 + 0x2);
    if ((u32) ((temp_r5 & 0xFF000000) + 0x01000000) == 0U) {
        var_r28 = (u16 *)&UserWork[temp_r5 & 0xFFFFFF];
    } else {
        var_r28 = (u16 *) temp_r5;
    }
    temp_r29 = *(u8 *)(temp_r3 + 0x1);
    temp_r30 = *(u16 *)(temp_r3 + 0x6);
    temp_r31 = *(u8 * *)(temp_r3 + 0x8);
    fightSeq_NextWazaSeq(0xCU);
    switch ((s32) temp_r29) {                       /* irregular */
    case 0:
        if ((u16) *var_r28 == temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 1:
        if ((u16) *var_r28 != temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 2:
        if ((u16) *var_r28 > temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 3:
        if ((u16) *var_r28 < temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 4:
        if (*var_r28 & temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 5:
        if (!(*var_r28 & temp_r30)) {
            fightSeq_JumpWazaSeq(temp_r31);
        }
        break;
    }
}

void WS_IF8(void) {
    s32 temp_r5;
    u8 *temp_r3;
    u8 *temp_r31;
    u8 temp_r30;
    u8 temp_r29;
    u8 *var_r28;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r5 = *(u32 *)(temp_r3 + 0x2);
    if ((u32) ((temp_r5 & 0xFF000000) + 0x01000000) == 0U) {
        var_r28 = &UserWork[temp_r5 & 0xFFFFFF];
    } else {
        var_r28 = (u8 *) temp_r5;
    }
    temp_r29 = *(u8 *)(temp_r3 + 0x1);
    temp_r30 = *(u8 *)(temp_r3 + 0x6);
    temp_r31 = *(u8 * *)(temp_r3 + 0x7);
    fightSeq_NextWazaSeq(0xBU);
    switch ((s32) temp_r29) {                       /* irregular */
    case 0:
        if ((u8) *var_r28 == temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 1:
        if ((u8) *var_r28 != temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 2:
        if ((u8) *var_r28 > temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 3:
        if ((u8) *var_r28 < temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 4:
        if (*var_r28 & temp_r30) {
            fightSeq_JumpWazaSeq(temp_r31);
            return;
        }
        break;
    case 5:
        if (!(*var_r28 & temp_r30)) {
            fightSeq_JumpWazaSeq(temp_r31);
        }
        break;
    }
}

void WS_JUMP(void) {
    fightSeq_JumpWazaSeq(*(u8 * *)(fightSeq_GetWazaSeq() + 0x1));
}

void WS_LOOP(void) {
    u8 *temp_r31;
    FightWaza *temp_r30;
    s32 var_r29;

    temp_r30 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11U, NULL));
    temp_r31 = fightSeq_GetWazaSeq();
    var_r29 = fightWaza_GetKaisuu(temp_r30);
    var_r29--;
    if ((s16)var_r29 < 0) {
        var_r29 = 0;
    }
    if ((s16)var_r29 == 0) {
        fightSeq_NextWazaSeq(5U);
    } else {
        fightSeq_JumpWazaSeq(*(u8 * *)(temp_r31 + 0x1));
    }
    fightWaza_SetKaisuu(temp_r30, (u8) var_r29);
}

void WS_LOOPCNT(void) {
    FightWaza *temp_r31;

    temp_r31 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11U, NULL));
    fightWaza_SetKaisuu(temp_r31, *(u8 *)(fightSeq_GetWazaSeq() + 0x1));
    fightSeq_NextWazaSeq(2U);
}

void WS_LOOP_INIT(void) {
    FightWaza *temp_r31;

    temp_r31 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11U, NULL));
    fightSeq_GetWazaSeq();
    fightSeqLoopInitAct(temp_r31);
    fightSeq_NextWazaSeq(1U);
}

void fightSeqLoopInitAct(FightWaza *arg0) {
    fightWazaInitLoop(arg0);
    ServerWork.flags[3] = 0;
    ServerStatusFlag &= ~0x40;
    ServerWork.flags[6] = 0;
    ServerStatusFlag &= ~0x4000;
}

void WS_ZENMETSU_CHECK(void) {
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    FightOutPokemon *temp_r31_2;
    u8 temp_r29;
    u8 temp_r28;
    u16 temp_r27;

    temp_r31 = (u8)(*(u32 *)(fightSeq_GetWazaSeq() + 0x1) != 0);
    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r27 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r29 = (u8)fightFloor_GetFightTypeTrainerNum(0);
    temp_r28 = (u8)fightFloor_GetFightTypeEntryPokemonNum(0);
    if (fightSideGetFightPokemonNokoriHp((FightSide *)fightTargetGetPtrAsNowFightType(5U, NULL), temp_r29, temp_r28) == 0) {
        fightFloorSetFightResultId(0, 2);
    }
    if (fightSideGetFightPokemonNokoriHp((FightSide *)fightTargetGetPtrAsNowFightType(4U, NULL), temp_r29, temp_r28) == 0) {
        fightFloorSetFightResultId(0, 3);
    }
    if (fightGetFightResultId() != 0) {
        if ((fightSeqRegulationZenmetuCheck(temp_r27) == 1) && (fightGetFightResultId() == 7)) {
            fightFloorSetFightResultId(0, 0);
            temp_r31_2 = fightTargetGetPtrAsNowFightType(2U, temp_r3);
            if (fightTargetGetPtrAsNowFightType(4U, NULL) == temp_r31_2) {
                fightFloorSetFightResultId(0, 3);
            } else {
                fightFloorSetFightResultId(0, 2);
            }
        }
        goto block_21;
    }
    if (temp_r31 == 1) {
        if (fightFloorIsIrekaeFightOutPokemon(0) != 0) {
            fightMainDebugMenu();
            if (fightGetFightResultId() != 0) {
                fightSeq_NextWazaSeq(5U);
                return;
            }
            if (fightFloorIsUseFightTimerCommand(0) == 1) {
                fightTimerCommandInit();
                fightTimerCommandStart();
            }
            fightMainAllCamera(0U, 0U);
            fightFloorLoopValidFightTrainer(NULL, (s32 (*)(FIGHT_TRAINER *, u16, void *))_fightSeqZenmetuCheckSubFightTrainer__FPvUsPv, NULL, 1U);
            fightMenuCloseInfoMenu(0);
            if (fightFloorIsUseFightTimerCommand(0) == 1) {
                fightTimerCommandBlock();
                fightTimerCommandTerminate();
            }
            if (fightGetFightResultId() != 0) {
                fightSeq_NextWazaSeq(5U);
                return;
            }
            goto block_20;
        }
block_20:
        fightFloorLoopValidFightOutPokemon(NULL, (s32 (*)(FightOutPokemon *, u16, void *))_fightSeqZenmetuCheckSubFightOutPokemon__FPvUsPv, NULL, 0U);
        goto block_21;
    }
block_21:
    fightSeq_NextWazaSeq(5U);
}

s32 _fightSeqZenmetuCheckSubFightOutPokemon__FPvUsPv(void *arg0, u16 arg1, void *arg2) {
    u8 hokaku;
    u8 kizetu;
    FightOutPokemon *fop;
    FightPokemon *moto;
    FightPokemon *fp;
    Pokemon *motoPokemon;
    Pokemon *buffPokemon;

    fop = (FightOutPokemon *)arg0;
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(NULL, fop);
    fightFloorGetFightOutPokemonPtrToHeroPtr(NULL, fop);
    moto = fightOutPokemon_GetMotoFightPokemonPtr(fop);
    fp = fightOutPokemon_GetFightPokemonPtr(fop);
    motoPokemon = fightPokemon_GetMotoPokemonPtr(moto);
    buffPokemon = fightPokemon_GetPokemonBuffPtr(moto);
    kizetu = fightOutPokemon_GetKizetuFlag(fop);
    hokaku = fightPokemon_GetHokakuFlag(fp);
    if (fightOutPokemonCheckFightOut(fop) == 0) {
        if (fightOutPokemon_GetIrekaeTargetEntryId(fop) < 0) {
            if (kizetu == 1) {
                fightOutPokemonInit(fop);
            }
            if (hokaku == 1) {
                pokemonInit(motoPokemon);
                pokemonInit(buffPokemon);
                fightPokemonInit(moto);
                fightPokemonInit(fp);
                fightOutPokemonInit(fop);
            }
        } else {
            fightFloor_SetIrekaePokemonPtr(NULL, fop);
            fightFloor_SetKizetuPokemonPtr(NULL, fop);
            if (hokaku == 1) {
                pokemonInit(motoPokemon);
                pokemonInit(buffPokemon);
                fightPokemonInit(moto);
                fightPokemonInit(fp);
            }
            fightSeq_CallWazaSeq(WAZA_MineReshuffleStart);
        }
    }
    return 1;
}

s32 _fightSeqZenmetuCheckSubFightTrainer__FPvUsPv(void *arg0, u16 arg1, void *arg2) {
    s16 sp8;
    u16 i;
    FIGHT_TRAINER *trainer;
    FightOutPokemon *fop;
    u32 n;
    u16 id;
    FightPokemon *p;
    FightPokemon *fp;
    s16 entry;
    s32 banme;

    trainer = (FIGHT_TRAINER *)arg0;
    id = arg1;
    if (fightGetFightResultId() != 0) {
        return 1;
    }
    if (fightTrainerCheckValid(trainer) == 0) {
        return 1;
    }
    n = fightFloor_GetFightTypeFightoutPokemonNum(NULL);
    for (i = 0; i < n; i++) {
        fop = fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (fop == NULL || fightOutPokemonCheckFightOut(fop) == 1 || fightOutPokemon_GetIrekaetaFlag(fop) == 1) {
            continue;
        }
        sp8 = 0;
        if (fightTrainerSearchIrekaeFightPokemon(trainer, &sp8) == 0) {
            break;
        }
        entry = -1;
        fp = NULL;
        if (fightOutPokemonCheckValid(fop) == 0) {
            banme = fightTrainerGetFightOutPokemonToTemotiBanme(trainer, fop);
            p = fightTrainer_GetFightPokemonPtr(trainer, banme);
            if (fightPokemonCheckFightOut(p) == 1) {
                fp = p;
                entry = fightPokemon_GetEntryId(p);
            }
        }
        if (fp == NULL) {
            entry = fightTrainerSelectIrekaeFightPokemon(trainer, id, 0U, fop);
            if (entry < 0) {
                if (entry == -2) {
                    fightFloorSetTuusinErrorFightResult(0);
                }
                break;
            }
            fightTrainerGetEntryIdToFightPokemonPtr(trainer, entry);
        }
        if (fightOutPokemonCheckValid(fop) == 0) {
            banme = fightTrainerGetFightOutPokemonToTemotiBanme(trainer, fop);
            fightOutPokemonCreate(fop, fightTrainer_GetFightPokemonPtr(trainer, banme), 0);
            fightOutPokemon_SetKizetuFlag(fop, 1U);
        }
        fightOutPokemon_SetIrekaeTargetEntryId(fop, entry);
        fightOutPokemon_SetIrekaetaFlag(fop, 1U);
    }
    return 1;
}

void WS_GET_EXP(void) {
    FightSide *side;
    FightOutPokemon *foe;
    u8 trainerNum;
    u8 fightType;
    u8 msgOpen;
    u8 camera;
    u32 sum;
    s32 i;
    FIGHT_TRAINER *trainer;
    Hero *hero;
    s32 slot;
    FightPokemon *fp;
    u32 gain;
    FightOutPokemon *fop;
    s32 nShare;
    s32 nPart;
    Pokemon *pokemon;
    u32 cur;
    u32 next;
    s32 menuId;
    u32 bgm;
    u16 giveExp;
    u32 msgId;
    u8 curLevel;
    u16 shareExp;
    u8 level;
    u16 partExp;
    u16 exp;
    s32 pool;
    u16 species;

    fightType = fightFloor_GetFightType(NULL);
    camera = 0;
    foe = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], NULL);
    species = figthOutPokemonGetPokemonDataId(foe);
    giveExp = pokemonDB_GetGiveExp(species);
    level = figthOutPokemonGetLevel(foe);
    if (fightOutPokemonIsGcHeroFightOutPokemon(foe) != 1 && fightFloor_GetFightKindGetExpFlag(0) != 0) {
        side = (FightSide *)fightTargetGetPtrAsNowFightType(3U, foe);
        if (fightSideCheckValid(side) != 0 && fn_80148688(foe) != 1) {
            nPart = 0;
            nShare = 0;
            trainerNum = fightFloor_GetFightTypeTrainerNum(0);
            for (i = 0; i < trainerNum; i++) {
                trainer = fightSideGetValidFightTrainerPtr(side, i);
                if (trainer != NULL && fightTrainerCheckCanGetExp(trainer) != 0) {
                    hero = fightTrainer_GetHeroPtr(trainer);
                    for (slot = 0; slot < 6; slot++) {
                        fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, heroGetStatus(hero, 3U, (u16)slot));
                        if (fp != NULL && fightPokemonCheckFightOut(fp) != 0) {
                            if (fightOutPokemonCheckMeetEnemyFightPokemon(foe, fp) == 1) {
                                nPart++;
                            }
                            if (fightPokemonGetSoubiItemSoubiDataId(fp) == 0x19) {
                                nShare++;
                            }
                        }
                    }
                }
            }
            if (nPart != 0 || nShare != 0) {
                exp = (giveExp * level) / 7;
                if (nShare != 0) {
                    pool = exp / 2;
                    partExp = pool / nPart;
                    if (partExp == 0) {
                        partExp = 1;
                    }
                    shareExp = pool / nShare;
                    if (shareExp == 0) {
                        shareExp = 1;
                    }
                } else {
                    partExp = exp / nPart;
                    if (partExp == 0) {
                        partExp = 1;
                    }
                    shareExp = 0;
                }
                if (fightFloor_GetFightKind(NULL) == 0xC || fightFloor_GetFightKind(NULL) == 0xD) {
                    bgm = soundPauseBGMEX(0x32, 1);
                    GSsndPlayVolume(0x36AU, 0U, 0xFFU, 0U);
                    soundPlayWait(0x36A);
                    if (bgm != 0) {
                        soundContinueBGMEX(bgm, 0x1F4, 1);
                    }
                }
                fn_8014718C(foe, 1U);
                for (i = 0; i < trainerNum; i++) {
                    trainer = fightSide_GetFightTrainerPtr(side, i);
                    if (fightTrainerCheckCanGetExp(trainer) != 0) {
                        hero = fightTrainer_GetHeroPtr(trainer);
                        for (slot = 0; slot < 6; slot++) {
                            gain = 0;
                            fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, heroGetStatus(hero, 3U, (u16)slot));
                            if (fp != NULL && fightPokemonCheckFightOut(fp) != 0 && figthPokemonGetLevel(fp) < 100) {
                                if (fightOutPokemonCheckMeetEnemyFightPokemon(foe, fp) == 1) {
                                    gain = partExp;
                                }
                                if (fightPokemonGetSoubiItemSoubiDataId(fp) == 0x19) {
                                    gain += shareExp;
                                }
                                if (gain != 0) {
                                    if (fightPokemonGetSoubiItemSoubiDataId(fp) == 0x28) {
                                        gain = gain * 150 / 100;
                                    }
                                    if (fightFloor_GetFightKindKeikentihueruFlag(0) == 1) {
                                        gain = gain * 150 / 100;
                                    }
                                    if (fightTrainerIsMineFightPokemon(trainer, fp) == 0) {
                                        msgId = 0x4E25;
                                        gain = gain * 150 / 100;
                                    } else {
                                        msgId = 0x4E24;
                                    }
                                    pokemon = fightPokemonGetPokemonPtr(fp);
                                    if (pokemonIsDarkPokemon(pokemon) == 1) {
                                        pokemonGetDarkPokemonLevel((s32)pokemon);
                                        pokemon_SetPoolExp(pokemon, pokemon_GetPoolExp(pokemon) + gain * 80 / 100);
                                        fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                        if (fop != NULL) {
                                            fightSeqCheckSetHensinBuffToMotoPokemon(fop, 0xC6U);
                                        }
                                    } else {
                                        if (camera == 0) {
                                            fightMainAllCamera(1U, 0U);
                                            camera = 1;
                                        }
                                        fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                        if (fop != NULL) {
                                            fightMenuFightOutPokemonOpenStatusMenu(fop, fightType, 1U);
                                            fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, fop, fightType, 0U, 1U);
                                        }
                                        fightMsgctrlSetValue(0xDU, fightPokemonGetNicknamePtr(fp));
                                        fightMsgctrlSetValue(0xEU, GSmsgGetGSchar(msgId));
                                        fightMsgctrlSetValue(0x2FU, (void *)gain);
                                        msgOpen = fightMenuOpenMsg(0x4E23U);
                                        fightMenuCloseMsg();
                                        fightPokemonGetEffortFromPokemon(fp, pokemonCheckInfectPokerus(fightPokemonGetPokemonPtr(fp), 0), species);
                                        for (;;) {
                                            if (gain == 0 || fightPokemonCheckFightOut(fp) == 0) {
                                                break;
                                            }
                                            curLevel = figthPokemonGetLevel(fp);
                                            if (curLevel >= 100) {
                                                break;
                                            }
                                            fightPokemonToMenuLvupStatus(fp, &old_menu_lvup_status);
                                            get_exp_fight_pokemon_ptr = fp;
                                            cur = figthPokemonGetExp(fp);
                                            next = fightPokemonGetLevelToExp(fp, curLevel + 1);
                                            sum = cur + gain;
                                            if (sum >= next) {
                                                gain = sum - next;
                                                fightPokemonGrowBasisStatus(fp, next);
                                                fightMsgctrlSetValue(0xDU, fightPokemonGetNicknamePtr(fp));
                                                fightMsgctrlSetValue(0x2FU, (void *)figthPokemonGetLevel(fp));
                                                if (fightFloor_GetFightKindGetFriendFlag(0) == 1 && fightTrainerIsGcHero(trainer) == 1) {
                                                    fightPokemonGetFriendFormPokemonFriendFilterId(fp, 0);
                                                }
                                                fightPokemon_SetLevelUpFlag(fp, 1U);
                                                fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                                if (fop != NULL) {
                                                    if (fightOutPokemonIsUseHensinBuff(fop) == 1) {
                                                        fightOutPokemonSetHensinStatusAfterLevelUp(fop);
                                                    }
                                                    fightSeqCheckSetHensinBuffToMotoFightPokemon(fop, 0xD0U);
                                                }
                                                fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                                if (fop != NULL) {
                                                    menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(fop, fightType, 0);
                                                    menuFightStatusStartAnimEXP(menuId, next - fightPokemonGetLevelToExp(fp, curLevel));
                                                    menuFightStatusWaitAnimeEXP(menuId, 1);
                                                    fightMenuFightOutPokemonRenewStatusMenu(fop, fightType, 1U);
                                                }
                                                fightSeq_CallWazaSeq(WAZA_LevelUp);
                                                msgOpen = 0;
                                            } else {
                                                gain = 0;
                                                figthPokemonSetExp(fp, sum);
                                                fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                                if (fop != NULL) {
                                                    menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(fop, fightType, 0);
                                                    menuFightStatusStartAnimEXP(menuId, sum - fightPokemonGetLevelToExp(fp, curLevel));
                                                    fightMainWaitFrame(0x40U);
                                                    menuFightStatusWaitAnimeEXP(menuId, 1);
                                                    fightMenuFightOutPokemonRenewStatusMenu(fop, fightType, 1U);
                                                }
                                            }
                                            get_exp_fight_pokemon_ptr = NULL;
                                        }
                                        if (msgOpen == 1) {
                                            fightMenuCloseMsg();
                                        }
                                        fop = fightTrainerCheckFightPokemonFightOut(trainer, fp);
                                        if (fop != NULL) {
                                            fightMenuFightOutPokemonCloseStatusMenu(fop, fightType, 0U);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    fightSeq_NextWazaSeq(2U);
}

void WS_CHECK_TYPE(void) {
    u8 *temp_r3;
    u8 *temp_r30;
    FightOutPokemon *pokemon;

    temp_r3 = fightSeq_GetWazaSeq();
    pokemon = fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    temp_r30 = *(u8 * *)(temp_r3 + 0x3);
    if (fightOutPokemonIsZokuseiDataId(pokemon, (u16) *(u8 *)(temp_r3 + 0x2)) == 1) {
        fightSeq_JumpWazaSeq(temp_r30);
        return;
    }
    fightSeq_NextWazaSeq(7U);
}

void WS_WAZAKOUKA_CHECK(void) {
    u8 *temp_r3;
    u8 *temp_r30;
    FightOutPokemon *pokemon;
    u8 result;
    u8 flag;

    temp_r3 = fightSeq_GetWazaSeq();
    pokemon = fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    temp_r30 = *(u8 * *)(temp_r3 + 0x7);
    result = fightOutPokemonIsJoutaiDataId(pokemon, (u16) *(u32 *)(temp_r3 + 0x2));
    flag = *(u8 *)(temp_r3 + 0x6);
    if (flag == result) {
        fightSeq_JumpWazaSeq(temp_r30);
        return;
    }
    fightSeq_NextWazaSeq(0xBU);
}

void WS_CONDCHG_CHECK(void) {
    u8 *temp_r3;
    FightOutPokemon *temp_r30;
    u8 temp_r29;
    u8 var_r28;
    u8 temp_r0;
    u8 temp_r3_2;
    u16 id;

    var_r28 = 0;
    temp_r3 = fightSeq_GetWazaSeq();
    temp_r30 = fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    temp_r29 = *(u8 *)(temp_r3 + 0x2);
    id = fightSeqCondChgActTypeToPokemonStatusId(*(u8 *)(temp_r3 + 0x3));
    temp_r3_2 = pokemonGetStatus((Pokemon *) temp_r30, 0U, id, 0U);
    temp_r0 = *(u8 *)(temp_r3 + 0x4);
    switch ((s32) temp_r29) {                       /* irregular */
    case 0:
        if (temp_r3_2 == temp_r0) {
            var_r28 = 1;
        }
        break;
    case 1:
        if (temp_r3_2 != temp_r0) {
            var_r28 = 1;
        }
        break;
    case 2:
        if (temp_r3_2 > temp_r0) {
            var_r28 = 1;
        }
        break;
    case 3:
        if (temp_r3_2 < temp_r0) {
            var_r28 = 1;
        }
        break;
    case 4:
        if (temp_r3_2 & temp_r0) {
            var_r28 = 1;
        }
        break;
    case 5:
        if (!(temp_r3_2 & temp_r0)) {
            var_r28 = 1;
        }
        break;
    }
    if (var_r28 != 0) {
        fightSeq_JumpWazaSeq(*(u8 * *)(temp_r3 + 0x5));
        return;
    }
    fightSeq_NextWazaSeq(9U);
}

void WS_SIDECONDITION_CHECK(void) {
    u8 *temp_r3;
    u8 *temp_r30;
    FightOutPokemon *mon;

    temp_r3 = fightSeq_GetWazaSeq();
    mon = fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    FightSide *side = (FightSide *)fightTargetGetPtrAsNowFightType(2U, mon);
    temp_r30 = *(u8 * *)(temp_r3 + 0x4);
    if (fightSideIsJoutaiDataId(side, *(u16 *)(temp_r3 + 0x2)) == 1) {
        fightSeq_JumpWazaSeq(temp_r30);
        return;
    }
    fightSeq_NextWazaSeq(8U);
}

void WS_SPEABI_CHECK(void) {
    u8 *temp_r3;
    u16 temp_r31;
    u8 *temp_r30;
    FightOutPokemon *temp_r3_2;
    u8 *seq2;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r3_2 = fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    temp_r31 = fightOutPokemonGetTokuseiDataId(temp_r3_2);
    seq2 = fightSeq_GetWazaSeq();
    temp_r30 = *(u8 * *)(temp_r3 + 0x3);
    if (((s32) temp_r31 == (s32) *(u8 *)(seq2 + 0x2)) && (fightFloorIsNowEncountOpeningVirtualBattle(0) == 0)) {
        fightFloor_SetTokuseiPokemonPtr(NULL, temp_r3_2);
        fightSeq_JumpWazaSeq(temp_r30);
        return;
    }
    fightSeq_NextWazaSeq(7U);
}

void WS_CONDITION2_CHECK(void) {
    WS_CONDITION_CHECK();
}

void WS_CONDITION_CHECK(void) {
    s32 temp_r0;
    u8 *temp_r3;
    FightOutPokemon *temp_r3_2;
    u8 *temp_r30;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r3_2 = fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r3 + 0x1), NULL);
    temp_r0 = *(u32 *)(temp_r3 + 0x2);
    temp_r30 = *(u8 * *)(temp_r3 + 0x6);
    if ((u16) temp_r0 == 1) {
        if (fightOutPokemonIsJoutaiNormal(temp_r3_2) == 0) {
            fightSeq_JumpWazaSeq(temp_r30);
            return;
        }
        fightSeq_NextWazaSeq(0xAU);
        return;
    }
    if ((u16) temp_r0 == 2) {
        if (fightOutPokemonIsJoutaiKaragenki(temp_r3_2) == 1) {
            fightSeq_JumpWazaSeq(temp_r30);
            return;
        }
        fightSeq_NextWazaSeq(0xAU);
        return;
    }
    if ((fightOutPokemonIsJoutaiDataId(temp_r3_2, (u16) temp_r0) == 1) && (fightOutPokemonCheckFightOut(temp_r3_2) == 1)) {
        fightSeq_JumpWazaSeq(temp_r30);
        return;
    }
    fightSeq_NextWazaSeq(0xAU);
}

void WS_KIZETSU_WAIT(void) {
    FightOutPokemon *temp_r3;
    u8 temp_r30;

    temp_r30 = fightFloor_GetFightType(NULL);
    temp_r3 = fightTargetGetPtrAsNowFightType(*(u8 *)(fightSeq_GetWazaSeq() + 0x1), NULL);
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(NULL, temp_r3);
    fightOutPokemonKizetuEffect(temp_r3, 2U);
    fightMenuFightOutPokemonCloseStatusMenu(temp_r3, temp_r30, 0U);
    fightOutPokemonKizetuEffect(temp_r3, 3U);
    fightSeqKizetuInit(temp_r3);
    fightSeq_NextWazaSeq(2U);
}

void WS_KIZETSU(void) {
    FightOutPokemon *temp_r3;
    u8 temp_r30;

    temp_r30 = fightFloor_GetFightType(NULL);
    temp_r3 = fightTargetGetPtrAsNowFightType(*(u8 *)(fightSeq_GetWazaSeq() + 0x1), NULL);
    if ((fightOutPokemonIsJoutaiDataId(temp_r3, 0x14U) == 1) && (fightOutPokemonGetJoutaiMigawariHp(temp_r3) > 0)) {
        fightOutPokemonInitJoutaiDataId(temp_r3, 0x14U);
        fightOutPokemonFreeAllSequenceWaza(temp_r3);
        fightWazaWzxTypeFuncMigawari(0xA4U, temp_r3, temp_r3, 0U, 0U);
loop_3:
        if (wazaSequenceSysLastWazaIsImpactPoint(4) != 1) {
            GSthreadSwitch();
            goto loop_3;
        }
    }
    fightOutPokemonFreeAllSequenceWaza(temp_r3);
    fightOutPokemonKizetuEffect(temp_r3, 0U);
    fightOutPokemonKizetuEffect(temp_r3, 1U);
    fightMenuFightOutPokemonOpenStatusMenu(temp_r3, temp_r30, 1U);
    fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, temp_r3, temp_r30, 0U, 1U);
    fightSeq_NextWazaSeq(2U);
}

void WS_KIZETSU_CHECK(void) {
    BasisWazaLayout sp8;
    u8 *temp_r28;
    FightOutPokemon *temp_r3;
    FightOutPokemon *var_r31;
    u8 *var_r30;
    FightOutPokemon *temp_r3_2;
    FightOutPokemon *temp_r3_3;
    FightOutPokemon *temp_r3_4;
    FightOutPokemon *temp_r3_5;
    FightOutPokemon *temp_r3_6;
    void *temp_r3_7;
    FightOutPokemon *var_r29;
    Pokemon *temp_r28_2;
    FightOutPokemon *temp_r27;
    FightOutPokemon *temp_r27_2;
    FightWaza *temp_r25;
    u16 temp_r24;
    s32 var_r23;
    s8 wazaNo;
    u16 temp_r23;
    u8 temp_r0;

    temp_r28 = fightSeq_GetWazaSeq();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
    if ((u8) *(u8 *)(temp_r28 + 0x2) != 0) {
        temp_r3 = fightTargetGetPtrAsNowFightType(*(u8 *)(temp_r28 + 0x1), NULL);
        temp_r27 = fightTargetGetPtrAsNowFightType(2U, temp_r3);
        if (fightOutPokemonIsHinsi(temp_r3) == 1) {
            fightSide_SetMakibisiCheckFlag((FightSide *) temp_r27, 0);
            fightSeq_JumpWazaSeq(*(u8 * *)(temp_r28 + 0x3));
            return;
        }
        goto block_28;
    }
    temp_r0 = *(u8 *)(temp_r28 + 0x1);
    if (temp_r0 == 17) {
        var_r31 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
        fightOutPokemon_GetMotoFightPokemonPtr(var_r31);
        var_r29 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
        var_r30 = WAZA_KizetsuA;
    } else if (temp_r0 == 18) {
        var_r31 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
        fightOutPokemon_GetMotoFightPokemonPtr(var_r31);
        var_r29 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
        var_r30 = WAZA_KizetsuD;
    } else if (temp_r0 == 21) {
        var_r31 = fightTargetGetPtrAsNowFightType(0x15U, NULL);
        fightOutPokemon_GetMotoFightPokemonPtr(var_r31);
        var_r29 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
        var_r30 = WAZA_KizetsuK;
    } else {
        var_r31 = NULL;
        var_r29 = NULL;
        var_r30 = WAZA_KizetsuD;
    }
    if (fightOutPokemonIsHinsi(var_r31) == 1) {
        fightOutPokemon_SetKizetuFlag(var_r31, 1U);
        if (fightOutPokemonIsGcHeroFightOutPokemon(var_r31) == 1) {
            ServerStatusFlag |= 0x400000;
            if (fightFloor_GetFightKindGetFriendFlag(0) == 1) {
                _fightSeqHinshiFriendCalc__FP15FightOutPokemon(var_r31);
            }
        }
        if (!(ServerStatusFlag & 0x01000000)) {
            temp_r3_5 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
            if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3_5, 0x28U) == 1) {
                temp_r3_6 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
                temp_r28_2 = fightOutPokemonGetPokemonPtr(temp_r3_6);
                temp_r25 = fightOutPokemon_GetFightWazaPtr(temp_r3_6);
                temp_r23 = fightOutPokemon_GetMotoWazaDataId(temp_r3_6);
                temp_r24 = fightOutPokemon_GetUseWazaDataId(temp_r3_6);
                if ((fightOutPokemonIsAlly(temp_r3_6, temp_r3_5) == 0) && (fightOutPokemonCheckFightOut(temp_r3_6) == 1) && (temp_r24 != 0xA5) && (wazaCheckDarkWaza(temp_r24) == 0)) {
                    var_r23 = ((s32 (*)(Pokemon *, u16))pokemonSearchWazaDataId)(temp_r28_2, temp_r23);
                    if ((s8)var_r23 < 0) {
                        var_r23 = fightWaza_GetWazaBanme(temp_r25);
                    }
                    wazaNo = var_r23;
                    pokemon_SetPokemonWazaPp(temp_r28_2, wazaNo, 0U);
                    fightSeqPpdecMonomane(temp_r3_6, var_r23, 0);
                    fightSeqCheckSetHensinBuffToMotoPokemon2(temp_r3_6, 0x80U, wazaNo, 0);
                    fightMsgctrlSetValue(0xDU, GSmsgGetGSchar(wazaDB_GetName(pokemon_GetPokemonWazaDataId(temp_r28_2, wazaNo))));
                    fightSeq_CallWazaSeq(WAZA_Onnen);
                }
            }
        }
        if (ServerStatusFlag & 0x40) {
            temp_r3_7 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
            if (fightOutPokemonCheckFightOut((FightOutPokemon *)temp_r3_7) == 1) {
                temp_r3_7 = fightOutPokemon_GetFightWazaPtr((FightOutPokemon *)temp_r3_7);
                fightWazaBiosCopy((FightWaza *)&sp8, (FightWaza *)temp_r3_7);
                fightWaza_SetDamage((FightWaza *)temp_r3_7, (u32) pokemon_GetHp(fightOutPokemonGetPokemonPtr(var_r29)));
                fightWazaInitJoutai((FightWaza *)temp_r3_7);
                fightSeq_CallWazaSeq(WAZA_Michidure);
                fightWazaBiosCopy((FightWaza *)temp_r3_7, (FightWaza *)&sp8);
            }
            ServerStatusFlag &= 0xFFFFFFBF;
        }
        temp_r27_2 = fightFloor_GetAppointPokemonPtr(NULL);
        fightFloor_SetAppointPokemonPtr(NULL, var_r31);
        fightSeq_CallWazaSeq(var_r30);
        fightFloor_SetAppointPokemonPtr(NULL, temp_r27_2);
    }
block_28:
    fightSeq_NextWazaSeq(7U);
}

void _fightSeqHinshiFriendCalc__FP15FightOutPokemon(FightOutPokemon *arg0) {
    FightOutPokemon *sp8[8];
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    s32 temp_r30;
    u8 temp_r29;
    u16 var_r27;
    u8 var_r26;
    FightPokemon *temp_r25;

    if (arg0 != NULL) {
        temp_r25 = fightOutPokemon_GetMotoFightPokemonPtr(arg0);
        temp_r29 = figthOutPokemonGetLevel(arg0);
        temp_r31 = fightFloorGetFightOutPokemonPtrAry(NULL, 0U, 2U, arg0, sp8);
        var_r26 = 0;
        var_r27 = 0;
        while (var_r27 < temp_r31) {
            temp_r30 = (var_r27 * 4) & 0x3FFFC;
            temp_r3 = *(FightOutPokemon **)((u8 *)sp8 + temp_r30);
            if ((temp_r3 != NULL) && (var_r26 < figthOutPokemonGetLevel(temp_r3))) {
                var_r26 = figthOutPokemonGetLevel(*(FightOutPokemon **)((u8 *)sp8 + temp_r30));
            }
            var_r27 += 1;
        }
        if (var_r26 > temp_r29) {
            if ((s32) (var_r26 - temp_r29) >= 0x1E) {
                fightPokemonGetFriendFormPokemonFriendFilterId(temp_r25, 8);
                return;
            }
            fightPokemonGetFriendFormPokemonFriendFilterId(temp_r25, 6);
            return;
        }
        fightPokemonGetFriendFormPokemonFriendFilterId(temp_r25, 6);
    }
}

void WS_SAKUJO(void) {
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r30;
    u16 temp_r29;

    temp_r3 = fightTargetGetPtrAsNowFightType(*(u8 *)(fightSeq_GetWazaSeq() + 0x1), NULL);
    temp_r30 = temp_r3;
    temp_r29 = TSUIKATbl[ServerWork.flags[3]];
    if ((temp_r29 != 0) && (fightOutPokemonIsJoutaiDataId(temp_r3, temp_r29) == 1)) {
        fightOutPokemonInitJoutaiDataId(temp_r30, temp_r29);
    }
    ServerWork.flags[3] = 0U;
    fight_seq_server_work3_temp = 0;
    fightSeq_NextWazaSeq(2U);
}

void WS_TSUIKA_INDIRECT_ACT(void) {
    fightSeqTuikaAct(0U, 0U);
}

void WS_TSUIKA_DIRECT_ACT(void) {
    fightSeqTuikaAct(1U, 0U);
}

void WS_TSUIKA_CHECK(void) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r30;
    u8 temp_r3_2;
    u32 var_r29;
    u16 temp_r28;
    u32 var_r0;

    fightSeq_GetWazaSeq();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r28 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    if (fightOutPokemonGetTokuseiDataId(temp_r3) == 0x20) {
        var_r0 = (wazaDB_GetAddFightKoukaAvg(temp_r28) * 2) & 0x1FE;
    } else {
        var_r0 = wazaDB_GetAddFightKoukaAvg(temp_r28);
    }
    var_r29 = var_r0;
    if (dbgMenuFightGetTuikakoukaFlag() == 1) {
        var_r29 = 0x63;
    }
    if ((ServerWork.flags[3] & 0x80) && (fightWazaIsHit(temp_r30) == 1)) {
        ServerWork.flags[3] = (u8) (ServerWork.flags[3] & 0x7F);
        fightSeqTuikaAct(0U, 0x80U);
    } else {
        temp_r3_2 = ServerWork.flags[3];
        if ((temp_r3_2 & 0x80) && (temp_r28 == 0x175) && ((u8) lbl_804EB918 != 0)) {
            ServerWork.flags[3] = (u8) (temp_r3_2 & 0x7F);
            fightSeqTuikaAct(0U, 0x80U);
        } else if (((s32) (HSD_Rand() % 100) < (s32) (u16) var_r29) && ((u8) ServerWork.flags[3] != 0) && (fightWazaIsHit(temp_r30) == 1)) {
            if ((u16) var_r29 >= 0x64U) {
                fightSeqTuikaAct(0U, 0x80U);
            } else {
                fightSeqTuikaAct(0U, 0U);
            }
        } else {
            fightSeq_NextWazaSeq(1U);
        }
    }
    ServerWork.flags[3] = 0U;
    fight_seq_server_work3_temp = 0;
}

void _fightSeqTuikaActSub__FUcUcPUc(u8 arg0, u8 arg1, u8 *arg2) {
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r20;
    u32 temp_r14_2;
    FightOutPokemon *var_r19;
    u16 temp_r18;
    u16 temp_r14_4;
    u16 temp_r14_5;
    u16 temp_r4_2;
    u8 temp_r14;
    u16 temp_r15_2;
    u16 temp_r30;
    u32 temp_r0_4;
    u8 var_r29;
    u8 temp_r0_5;
    u8 temp_r4_3;
    FIGHT_TRAINER *temp_r3_2;
    u8 temp_r4;
    s32 var_r4_3;
    s32 var_r4_2;
    FightOutPokemon *var_r3;
    u32 var_r28;
    u8 temp_r0;
    u16 temp_r17;
    u8 temp_r0_2;
    u8 var_r14;
    FightOutPokemon *temp_r16;
    FightWaza *temp_r15;
    u16 temp_r22;
    u32 var_r4;
    u32 temp_r14_3;
    u16 temp_r0_3;
    FightWaza *temp_r27;
    u8 temp_r26;

    var_r29 = 0;
    var_r28 = 0;
    temp_r26 = fightFloor_GetFightType(NULL);
    *arg2 = 1;
    temp_r14 = fightFloorGetNowTenkouDataId(NULL, 1U);
    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r30 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r20 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    if (ServerWork.flags[3] & 0x40) {
        var_r19 = temp_r3;
        fightFloor_SetTuikakoukaPokemonPtr(NULL, temp_r3);
        fightFloor_SetAppointPokemonPtr(NULL, temp_r20);
        var_r3 = temp_r20;
        var_r28 = 0x40;
        ServerWork.flags[3] = (u8) (ServerWork.flags[3] & 0xBF);
    } else {
        var_r19 = temp_r20;
        fightFloor_SetTuikakoukaPokemonPtr(NULL, temp_r20);
        fightFloor_SetAppointPokemonPtr(NULL, temp_r3);
        var_r3 = temp_r3;
    }
    temp_r18 = ((u16 (*)(FightTarget*, u8))fightTargetGetTragetPtrToRelativeHostSideFightTargetId)((FightTarget *) var_r3, temp_r26);
    temp_r22 = fightOutPokemonGetTokuseiDataId(var_r19);
    temp_r17 = fightOutPokemonGetSoubiItemDataId(var_r19);
    temp_r16 = fightTargetGetPtrAsNowFightType(2U, var_r19);
    temp_r27 = fightOutPokemon_GetFightWazaPtr(var_r19);
    temp_r15 = fightOutPokemon_GetKeepFightWazaPtr(var_r19);
    if ((temp_r22 == 0x13) && !(ServerStatusFlag & 0x2000) && (arg0 == 0) && ((u8) ServerWork.flags[3] < 0xAU)) {
        ServerWork.flags[3] = 0U;
        return;
    }
    if ((fightSideIsJoutaiDataId((FightSide *) temp_r16, 0x4BU) != 1) || (ServerStatusFlag & 0x2000) || (arg0 != 0) || ((u8) ServerWork.flags[3] >= 8U)) {
        if (fightOutPokemonCheckFightOut(var_r19) == 0) {
            temp_r0 = ServerWork.flags[3];
            if ((temp_r0 != 0xB) && (temp_r0 != 0x1F)) {
                ServerWork.flags[3] = 0U;
                return;
            }
        }
        if ((fightOutPokemonIsJoutaiDataId(var_r19, 0x14U) == 1) && ((u8) var_r28 != 0x40)) {
            ServerWork.flags[3] = 0U;
            return;
        }
        temp_r0_2 = ServerWork.flags[3];
        if (temp_r0_2 < 7U) {
            temp_r0_3 = TSUIKATbl[temp_r0_2];
            switch ((s32) temp_r0_3) {              /* switch 1; irregular */
            case 8:                                 /* switch 1 */
                var_r14 = 1;
                if ((temp_r22 != 0x2B) && (fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(0, 0xB) != 0)) {
                    var_r14 = 0;
                }
                if ((fightOutPokemonIsJoutaiNormal(var_r19) == 1) && (fightOutPokemonCheckWriteJoutaiDataId(var_r19, TSUIKATbl[ServerWork.flags[3]]) == 2) && (var_r14 == 1) && (temp_r22 != 0x48) && (temp_r22 != 0xF) && (fightSeqRegulationOverTwoCheck(8U, var_r19) != 1)) {
                    fightOutPokemonInitJoutaiKeep(var_r19);
                    var_r29 = 1;
                }
                goto block_109;
            case 3:                                 /* switch 1 */
                if ((temp_r22 == 0x11) && ((arg0 == 1) || (arg1 == 0x80))) {
                    if (ServerStatusFlag & 0x2000) {
                        ServerWork.flags[5] = 1;
                        ServerStatusFlag &= 0xFFFFDFFF;
                    } else {
                        ServerWork.flags[5] = 0;
                    }
                    fightSeq_CallWazaSeq(WAZA_Meneki);
                    ServerWork.flags[3] = 0U;
                    return;
                }
                if (((fightOutPokemonIsZokuseiDataId(var_r19, 3U) == 1) || (fightOutPokemonIsZokuseiDataId(var_r19, 8U) == 1)) && (ServerStatusFlag & 0x2000) && ((arg0 == 1) || (arg1 == 0x80))) {
                    ServerWork.flags[5] = 2;
                    fightSeq_CallWazaSeq(WAZA_Meneki);
                    ServerWork.flags[3] = 0U;
                    return;
                }
                if ((fightOutPokemonIsZokuseiDataId(var_r19, 3U) == 0) && (fightOutPokemonIsZokuseiDataId(var_r19, 8U) == 0) && (fightOutPokemonIsJoutaiNormal(var_r19) == 1) && (temp_r22 != 0x11)) {
                    var_r29 = 1;
                }
                goto block_109;
            case 6:                                 /* switch 1 */
                if ((temp_r22 == 0x29) && ((arg0 == 1) || (arg1 == 0x80))) {
                    if (ServerStatusFlag & 0x2000) {
                        ServerWork.flags[5] = 1;
                        ServerStatusFlag &= 0xFFFFDFFF;
                    } else {
                        ServerWork.flags[5] = 0;
                    }
                    fightSeq_CallWazaSeq(WAZA_Mizunobeeru);
                    ServerWork.flags[3] = 0U;
                    return;
                }
                if ((fightOutPokemonIsZokuseiDataId(var_r19, 0xAU) == 1) && (ServerStatusFlag & 0x2000) && ((arg0 == 1) || (arg1 == 0x80))) {
                    ServerWork.flags[5] = 2;
                    fightSeq_CallWazaSeq(WAZA_Mizunobeeru);
                    ServerWork.flags[3] = 0U;
                    return;
                }
                if ((fightOutPokemonIsZokuseiDataId(var_r19, 0xAU) == 0) && (temp_r22 != 0x29) && (fightOutPokemonIsJoutaiNormal(var_r19) == 1)) {
                    var_r29 = 1;
                }
                goto block_109;
            case 7:                                 /* switch 1 */
                if ((fightOutPokemonIsZokuseiDataId(var_r19, 0xFU) == 0) && (fightOutPokemonIsJoutaiNormal(var_r19) == 1) && (temp_r14 != 1) && (temp_r22 != 0x28) && (fightSeqRegulationOverTwoCheck(7U, var_r19) != 1)) {
                    fightOutPokemonInitJoutaiKeep(var_r19);
                    var_r29 = 1;
                }
                goto block_109;
            case 5:                                 /* switch 1 */
                if ((temp_r22 == 7) && ((arg0 == 1) || (arg1 == 0x80))) {
                    if (ServerStatusFlag & 0x2000) {
                        ServerWork.flags[5] = 1;
                        ServerStatusFlag &= 0xFFFFDFFF;
                    } else {
                        ServerWork.flags[5] = 0;
                    }
                    fightSeq_CallWazaSeq(WAZA_Juunan);
                    ServerWork.flags[3] = 0U;
                    return;
                }
                if ((temp_r22 != 7) && (fightOutPokemonIsJoutaiNormal(var_r19) == 1)) {
                    var_r29 = 1;
                }
                goto block_109;
            case 4:                                 /* switch 1 */
                if ((temp_r22 == 0x11) && ((arg0 == 1) || (arg1 == 0x80))) {
                    if (ServerStatusFlag & 0x2000) {
                        ServerWork.flags[5] = 1;
                        ServerStatusFlag &= 0xFFFFDFFF;
                    } else {
                        ServerWork.flags[5] = 0;
                    }
                    fightSeq_CallWazaSeq(WAZA_Meneki);
                    ServerWork.flags[3] = 0U;
                    return;
                }
                if (((fightOutPokemonIsZokuseiDataId(var_r19, 3U) == 1) || (fightOutPokemonIsZokuseiDataId(var_r19, 8U) == 1)) && (ServerStatusFlag & 0x2000) && ((arg0 == 1) || (arg1 == 0x80))) {
                    ServerWork.flags[5] = 2;
                    fightSeq_CallWazaSeq(WAZA_Meneki);
                    ServerWork.flags[3] = 0U;
                    return;
                }
                if (fightOutPokemonIsJoutaiNormal(var_r19) == 1) {
                    if ((fightOutPokemonIsZokuseiDataId(var_r19, 3U) == 0) && (fightOutPokemonIsZokuseiDataId(var_r19, 8U) == 0)) {
                        if (temp_r22 != 0x11) {
                            var_r29 = 1;
                        }
                    } else if (fightWazaCheckWriteJoutaiDataId(temp_r27, 0x43U) == 2) {
                        fightWazaWriteJoutaiDataId(temp_r27, 0x43U, 0U);
                    }
                }
                goto block_109;
            default:                                /* switch 1 */
block_109:
                if (var_r29 != 0) {
                    if (fightOutPokemonCheckWriteJoutaiDataId(var_r19, TSUIKATbl[ServerWork.flags[3]]) == 2) {
                        fightOutPokemonWriteJoutaiDataId(var_r19, TSUIKATbl[ServerWork.flags[3]], 0U);
                    }
                    fightSeqCheckSetHensinBuffToMotoPokemon(var_r19, 0x7CU);
                    if (ServerStatusFlag & 0x2000) {
                        ServerStatusFlag &= 0xFFFFDFFF;
                        ServerWork.flags[5] = 1;
                    } else {
                        ServerWork.flags[5] = 0;
                    }
                    temp_r4 = ServerWork.flags[3];
                    if ((temp_r4 == 2) || ((u8) (temp_r4 - 5) <= 1U) || (temp_r4 == 3)) {
                        fight_seq_tuika_param = temp_r4;
                        ServerStatusFlag |= 0x4000;
                    }
                    fightSeq_CallWazaSeq(TSUIKASeqTbl[temp_r4]);
                    return;
                }
                ServerWork.flags[3] = 0U;
                return;
            }
        } else {
            temp_r4_2 = TSUIKATbl[temp_r0_2];
            if ((temp_r4_2 == 0) || (fightOutPokemonIsJoutaiDataId(var_r19, temp_r4_2) != 1)) {
                temp_r4_3 = ServerWork.flags[3];
                switch (temp_r4_3) {                /* switch 2 */
                case 0x7:                           /* switch 2 */
                    if ((temp_r22 != 0x14) && (fightOutPokemonIsJoutaiDataId(var_r19, 9U) == 0)) {
                        if (fightOutPokemonCheckWriteJoutaiDataId(var_r19, 9U) == 2) {
                            fightOutPokemonWriteJoutaiDataId(var_r19, 9U, 0U);
                        }
                        fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork.flags[3]]);
                    }
                    goto block_204;
                case 0x8:                           /* switch 2 */
                    if ((temp_r22 == 0x27) && ((arg0 == 1) || (arg1 == 0x80))) {
                        fightSeq_JumpWazaSeq(WAZA_Seisinryoku);
                        ServerWork.flags[3] = 0U;
                        *arg2 = 0;
                        return;
                    }
                    if ((temp_r22 != 0x27) && (fightOutPokemon_GetFightActionFlag(var_r19) == 0) && (fightOutPokemonCheckWriteJoutaiDataId(var_r19, TSUIKATbl[ServerWork.flags[3]]) == 2)) {
                        fightOutPokemonWriteJoutaiDataId(var_r19, TSUIKATbl[ServerWork.flags[3]], 0U);
                    }
                    goto block_204;
                case 0xA:                           /* switch 2 */
                    if (fightOutPokemonCheckWriteJoutaiDataId(var_r19, 0xBU) == 2) {
                        fightOutPokemonWriteJoutaiDataId(var_r19, 0xBU, 0U);
                        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x22U, 0U);
                        fightWazaBiosCopy(temp_r15, temp_r27);
                        fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork.flags[3]]);
                    }
                    goto block_204;
                case 0xB:                           /* switch 2 */
                    temp_r3_2 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(NULL, temp_r3);
                    if (temp_r3_2 != NULL) {
                        temp_r14_2 = fightTrainer_GetKoban(temp_r3_2);
                        temp_r0_4 = temp_r14_2 + (figthOutPokemonGetLevel(temp_r3) * 5);
                        var_r4 = 0xFFFF;
                        if (temp_r0_4 <= 0xFFFFU) {
                            var_r4 = temp_r0_4;
                        }
                        fightTrainer_SetKoban(temp_r3_2, var_r4);
                        fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork.flags[3]]);
                    }
                    goto block_204;
                case 0x9:                           /* switch 2 */
                    if (fightOutPokemonIsJoutaiNormal(var_r19) == 1) {
                        ServerWork.flags[3] = (u8) ((HSD_Rand() % 3) + 3);
                        fightSeqTuikaAct(0U, 0U);
                        fightSeq_NextWazaSeq(-1U);
                    }
                    goto block_204;
                case 0xC:                           /* switch 2 */
                    fightOutPokemonWriteJoutaiDataId(var_r19, 0x22U, 0U);
                    fightWazaBiosCopy(temp_r15, temp_r27);
                    fightOutPokemon_SetTameWazaFlag(var_r19, 1U);
                    goto block_204;
                case 0xD:                           /* switch 2 */
                    if (fightOutPokemonCheckWriteJoutaiDataId(var_r19, 0xEU) == 2) {
                        fightOutPokemonWriteJoutaiDataId(var_r19, 0xEU, temp_r18);
                        fightOutPokemonSetIdBuffJoutaiDataId(var_r19, 0xEU, temp_r30);
                        for (ServerWork.flags[5] = 0; ServerWork.flags[5] < 5; ServerWork.flags[5]++) {
                            if (temp_r30 == ShimeWazaNo[ServerWork.flags[5]]) break;
                        }
                        fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork.flags[3]]);
                    }
                    goto block_204;
                case 0xE:                           /* switch 2 */
                    if (temp_r30 == 0x167) {
                        temp_r14_3 = fightOutPokemonNowHpWaruValue(var_r19, 1U);
                        var_r4_2 = fightOutPokemonNowHpWaruValue(var_r19, 2U) & 0xFFFF;
                        if ((u16) temp_r14_3 == var_r4_2) {
                            var_r4_2 = 0;
                        }
                    } else {
                        var_r4_2 = (s32)fightWaza_GetHitDamage(temp_r27) / 4;
                    }
                    if ((temp_r30 != 0x167) && ((s32) var_r4_2 == 0)) {
                        var_r4_2 = 1;
                    }
                    fightWaza_SetDamage(temp_r27, (u32) var_r4_2);
                    fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork.flags[3]]);
                    goto block_204;
                case 0xF:                           /* switch 2 */
                case 0x10:                          /* switch 2 */
                case 0x11:                          /* switch 2 */
                case 0x12:                          /* switch 2 */
                case 0x13:                          /* switch 2 */
                case 0x14:                          /* switch 2 */
                case 0x15:                          /* switch 2 */
                    if (fightSeqCondChgAct(0x10, temp_r4_3 - 0xE, var_r28 & 0xFF, 0) == 0) {
                        UserWork[0x160A4] = (s8) (ServerWork.flags[3] & 0x3F);
                        UserWork[0x160A5] = 0;
                        fightSeq_CallWazaSeq(WAZA_CondUpTsuikaMsg);
                    }
                    goto block_204;
                case 0x16:                          /* switch 2 */
                case 0x17:                          /* switch 2 */
                case 0x18:                          /* switch 2 */
                case 0x19:                          /* switch 2 */
                case 0x1A:                          /* switch 2 */
                case 0x1B:                          /* switch 2 */
                case 0x1C:                          /* switch 2 */
                    if (fightSeqCondChgAct(0x90, temp_r4_3 - 0x15, var_r28 & 0xFF, 0) == 0) {
                        UserWork[0x160A4] = (s8) (ServerWork.flags[3] & 0x3F);
                        UserWork[0x160A5] = 0;
                        fightSeq_CallWazaSeq(WAZA_CondDownTsuikaMsg);
                    }
                    goto block_204;
                case 0x27:                          /* switch 2 */
                case 0x28:                          /* switch 2 */
                case 0x29:                          /* switch 2 */
                case 0x2A:                          /* switch 2 */
                case 0x2B:                          /* switch 2 */
                case 0x2C:                          /* switch 2 */
                case 0x2D:                          /* switch 2 */
                    if (fightSeqCondChgAct(0x20, temp_r4_3 - 0x26, var_r28 & 0xFF, 0) == 0) {
                        UserWork[0x160A4] = (s8) (ServerWork.flags[3] & 0x3F);
                        UserWork[0x160A5] = 0;
                        fightSeq_CallWazaSeq(WAZA_CondUpTsuikaMsg);
                    }
                    goto block_204;
                case 0x2E:                          /* switch 2 */
                case 0x2F:                          /* switch 2 */
                case 0x30:                          /* switch 2 */
                case 0x31:                          /* switch 2 */
                case 0x32:                          /* switch 2 */
                case 0x33:                          /* switch 2 */
                case 0x34:                          /* switch 2 */
                    if (fightSeqCondChgAct(0xA0, temp_r4_3 - 0x2D, var_r28 & 0xFF, 0) == 0) {
                        UserWork[0x160A4] = (s8) (ServerWork.flags[3] & 0x3F);
                        UserWork[0x160A5] = 0;
                        fightSeq_CallWazaSeq(WAZA_CondDownTsuikaMsg);
                    }
                    goto block_204;
                case 0x1D:                          /* switch 2 */
                    if (fightOutPokemonCheckWriteJoutaiDataId(var_r19, 0x12U) == 2) {
                        fightOutPokemonWriteJoutaiDataId(var_r19, 0x12U, 0U);
                    }
                    fightWazaBiosCopy(temp_r15, temp_r27);
                    goto block_204;
                case 0x1E:                          /* switch 2 */
                    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x13U) == 2) {
                        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x13U, 0U);
                    }
                    goto block_204;
                case 0x1F:                          /* switch 2 */
                    if (fightSeqIsDoItemGetWaza(temp_r3) != 0) {
                        temp_r15_2 = fightOutPokemonGetSoubiItemDataId(temp_r3);
                        temp_r14_4 = fightOutPokemonGetTokuseiDataId(temp_r20);
                        temp_r14_5 = fightOutPokemonGetSoubiItemDataId(temp_r20);
                        if ((temp_r14_4 == 0x3C) && (temp_r14_5 != 0)) {
                            fightSeq_CallWazaSeq(WAZA_Nentyaku2);
                        } else if ((temp_r15_2 == 0) && (temp_r14_5 != 0xAF) && (temp_r14_5 != 0) && (itemDataCheckValid(temp_r14_5) == 1)) {
                            fightOutPokemonDoItemSoubi(temp_r20, 0, 0, 0);
                            fightOutPokemon_SetStockItemDataId(temp_r3, temp_r14_5);
                            fightSeqCheckSetHensinBuffToMotoPokemon(temp_r3, 0x82U);
                            fightSeqCheckSetHensinBuffToMotoPokemon(temp_r20, 0x82U);
                            fightOutPokemonInitJoutaiDataId(temp_r20, 0x36U);
                            fightFloor_SetAppointItemDataId(0, temp_r14_5);
                            fightSeq_CallWazaSeq(WAZA_AddDorobou);
                        }
                    }
                    goto block_204;
                case 0x20:                          /* switch 2 */
                    if (fightOutPokemonCheckWriteJoutaiDataId(var_r19, 0x16U) == 2) {
                        fightOutPokemonWriteJoutaiDataId(var_r19, 0x16U, ((u16 (*)(FightTarget*, u8))fightTargetGetTragetPtrToRelativeHostSideFightTargetId)((FightTarget *) temp_r3, temp_r26));
                    }
                    goto block_204;
                case 0x21:                          /* switch 2 */
                    if (fightOutPokemonCheckWriteJoutaiDataId(var_r19, 0x17U) == 2) {
                        fightOutPokemonWriteJoutaiDataId(var_r19, 0x17U, 0U);
                    }
                    goto block_204;
                case 0x22:                          /* switch 2 */
                    fightMsgctrlSetValue(0x10U, var_r19);
                    fightSeq_CallWazaSeq(WAZA_Genshinochikara);
                    fightMsgctrlSetValue(0x10U, temp_r20);
                    goto block_204;
                case 0x23:                          /* switch 2 */
                    fightSeq_CallWazaSeq(WAZA_Kousokuspin);
                    goto block_204;
                case 0x24:                          /* switch 2 */
                    if (fightOutPokemonIsJoutaiDataId(temp_r20, 5U) == 1) {
                        fightOutPokemonInitJoutaiDataId(temp_r20, 5U);
                        fightSeqCheckSetHensinBuffToMotoPokemon(temp_r20, 0x7CU);
                        fightSeq_CallWazaSeq(WAZA_NoMahi);
                    }
                    goto block_204;
                case 0x25:                          /* switch 2 */
                    fightSeq_CallWazaSeq(WAZA_Bakadikara);
                    goto block_204;
                case 0x26:                          /* switch 2 */
                    var_r4_3 = (s32)fightWaza_GetHitDamage(temp_r27) / 3;
                    if (var_r4_3 == 0) {
                        var_r4_3 = 1;
                    }
                    fightWaza_SetDamage(temp_r27, (u32) var_r4_3);
                    fightSeq_CallWazaSeq(TSUIKASeqTbl[ServerWork.flags[3]]);
                    goto block_204;
                default: goto block_204;
                case 0x35:                          /* switch 2 */
                    if (fightOutPokemonCheckWriteJoutaiDataId(var_r19, 0xDU) == 2) {
                        fightOutPokemonWriteJoutaiDataId(var_r19, 0xDU, 0U);
                        fightOutPokemonWriteJoutaiDataId(var_r19, 0x22U, 0U);
                        fightWazaBiosCopy(temp_r15, temp_r27);
                        *arg2 = 0;
                    }
                    goto block_204;
                case 0x36:                          /* switch 2 */
                    if ((temp_r22 == 0x3C) && (temp_r17 != 0)) {
                        fightSeq_JumpWazaSeq(WAZA_Nentyaku);
                        *arg2 = 0;
                    } else if ((temp_r17 != 0) && (fightOutPokemonCheckWriteJoutaiDataId(var_r19, 0x3DU) == 2)) {
                        fightFloor_SetAppointItemDataId(0, temp_r17);
                        fightOutPokemonWriteJoutaiDataId(var_r19, 0x3DU, 0U);
                        fightSeqCheckSetHensinBuffToMotoFightPokemon(var_r19, 0xCDU);
                        fightOutPokemonInitJoutaiDataId(var_r19, 0x36U);
                        fightSeq_CallWazaSeq(WAZA_Hatakiotosu);
                    }
                    goto block_204;
                case 0x3B:                          /* switch 2 */
                    fightSeq_CallWazaSeq(WAZA_OverHeat);
                    goto block_204;
                }
            } else {
block_204:
                ServerWork.flags[3] = 0U;
            }
        }
    }
}

void fightSeqTuikaAct(u8 arg0, u8 arg1) {
    u8 sp8;

    _fightSeqTuikaActSub__FUcUcPUc(arg0, arg1, &sp8);
    fightSeq_NextWazaSeq((u32) sp8);
}

void WS_ALERT_MESSAGE_TBL(void) {
    u32 *temp_r4;
    s32 var_r3;

    temp_r4 = *(u32 **)(fightSeq_GetWazaSeq() + 0x1);
    if (temp_r4 != NULL) {
        var_r3 = temp_r4[ServerWork.flags[5]];
    } else {
        var_r3 = fightFloor_GetAppointMsgId(0);
    }
    fightSeqOpenMsg(var_r3);
    fightSeq_NextWazaSeq(5U);
}

void WS_MESSAGE_TBL(void) {
    u32 *temp_r4;
    s32 var_r3;

    temp_r4 = *(u32 **)(fightSeq_GetWazaSeq() + 0x1);
    if (temp_r4 != NULL) {
        var_r3 = temp_r4[ServerWork.flags[5]];
    } else {
        var_r3 = fightFloor_GetAppointMsgId(0);
    }
    fightSeqOpenMsg(var_r3);
    fightSeq_NextWazaSeq(5U);
}

void WS_MESSAGE_WAIT(void) {
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    if (ServerWork.flags[7] == 1) {
        fightMainWaitFrame(*(u16 *)(temp_r3 + 0x1));
        fightMenuCloseMsg();
        ServerWork.flags[7] = 0U;
    }
    fightSeq_NextWazaSeq(3U);
}

void WS_ALERT_MESSAGE(void) {
    fightSeqOpenMsg((s32) *(u16 *)(fightSeq_GetWazaSeq() + 0x1));
    fightSeq_NextWazaSeq(3U);
}

void WS_MESSAGE(void) {
    fightSeqOpenMsg(*(u32 *)(fightSeq_GetWazaSeq() + 0x1));
    fightSeq_NextWazaSeq(5U);
}

void WS_WAZAKOUKA_MESSAGE(void) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r29;
    u32 var_r28;
    u16 temp_r3_2;

    fightSeq_GetWazaSeq();
    temp_r29 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11U, NULL));
    temp_r3 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    fightOutPokemonGetNicknamePtr(temp_r3);
    temp_r3_2 = fightOutPokemonGetSoubiItemDataId(temp_r3);
    ServerWork.flags[7] = 0;
    var_r28 = 0;
    if (((fightWazaIsJoutaiDataId(temp_r29, 0x40U) == 1) && (fightWazaIsJoutaiDataId(temp_r29, 0x43U) == 0)) || ((fightWazaIsJoutaiDataId(temp_r29, 0x40U) == 1) && ((u8) ServerWork.flags[6] >= 3U))) {
        var_r28 = NoHitMsgTbl[ServerWork.flags[6]];
        goto block_30;
    }
    if (fightWazaIsMix(temp_r29) == 0) {
        if (fightWazaIsJoutaiDataId(temp_r29, 0x41U) == 1) {
            var_r28 = 0x4F20;
            goto block_30;
        }
        if (fightWazaIsJoutaiDataId(temp_r29, 0x42U) == 1) {
            var_r28 = 0x4F1F;
            goto block_30;
        }
        if (fightWazaIsJoutaiDataId(temp_r29, 0x43U) == 1) {
            var_r28 = 0x4E34;
            goto block_30;
        }
        if (fightWazaIsJoutaiDataId(temp_r29, 0x44U) == 1) {
            var_r28 = 0x4F1B;
            goto block_30;
        }
        if (fightWazaIsJoutaiDataId(temp_r29, 0x45U) == 1) {
            var_r28 = 0x4F29;
            goto block_30;
        }
        if (fightWazaIsJoutaiDataId(temp_r29, 0x46U) == 1) {
            var_r28 = 0x4EB4;
            goto block_30;
        }
        if (fightWazaIsJoutaiDataId(temp_r29, 0x47U) == 1) {
            fightWazaInitJoutaiDataId(temp_r29, 0x46U);
            fightWazaInitJoutaiDataId(temp_r29, 0x47U);
            fightFloor_SetAppointItemDataId(0, temp_r3_2);
            fightFloor_SetItemPokemonPtr(NULL, temp_r3);
            fightSeq_CallWazaSeq(WAZA_ItemKoraeta);
            return;
        }
        goto block_30;
    }
    if (fightWazaIsJoutaiDataId(temp_r29, 0x43U) == 1) {
        var_r28 = 0x4E34;
        goto block_30;
    }
    if (fightWazaIsJoutaiDataId(temp_r29, 0x44U) == 1) {
        fightWazaInitJoutaiDataId(temp_r29, 0x44U);
        fightWazaInitJoutaiDataId(temp_r29, 0x41U);
        fightWazaInitJoutaiDataId(temp_r29, 0x42U);
        fightSeq_CallWazaSeq(WAZA_Ichigeki);
        return;
    }
    if (fightWazaIsJoutaiDataId(temp_r29, 0x46U) == 1) {
        fightWazaInitJoutaiDataId(temp_r29, 0x46U);
        fightWazaInitJoutaiDataId(temp_r29, 0x47U);
        fightSeq_CallWazaSeq(WAZA_Koraeta);
        return;
    }
    if (fightWazaIsJoutaiDataId(temp_r29, 0x47U) == 1) {
        fightWazaInitJoutaiDataId(temp_r29, 0x46U);
        fightWazaInitJoutaiDataId(temp_r29, 0x47U);
        fightFloor_SetAppointItemDataId(0, temp_r3_2);
        fightFloor_SetItemPokemonPtr(NULL, temp_r3);
        fightSeq_CallWazaSeq(WAZA_ItemKoraeta);
        return;
    }
    if (fightWazaIsJoutaiDataId(temp_r29, 0x45U) == 1) {
        var_r28 = 0x4F29;
    }
block_30:
    if (var_r28 != 0) {
        fightFloor_SetWazakoukaMsgId(0, var_r28);
        if (fightMenuWazaKoukaMsg(var_r28, temp_r3, temp_r3_2) == 1) {
            ServerWork.flags[7] = 1;
        }
    }
    fightSeq_NextWazaSeq(1U);
}

void WS_WAZAKOUKA_SE(void) {
    FightWaza *temp_r3;
    u16 var_r30;

    var_r30 = 0;
    fightSeq_GetWazaSeq();
    temp_r3 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11U, NULL));
    if (fightWazaIsJoutaiDataId(temp_r3, 0x40U) == 0) {
        if (fightFloor_GetEnvSndId(NULL) != 0) {
            if (fightWazaIsJoutaiDataId(temp_r3, 0x41U) == 1) {
                var_r30 = 0x540;
            } else if (fightWazaIsJoutaiDataId(temp_r3, 0x42U) == 1) {
                var_r30 = 0x541;
            } else if (fightWazaIsJoutaiDataId(temp_r3, 0x43U) == 1) {
                var_r30 = 0x542;
            } else if (fightWazaIsJoutaiDataId(temp_r3, 0x45U) == 1) {
                var_r30 = 0x543;
            } else {
                var_r30 = 0x544;
            }
        }
        if (var_r30 != 0) {
            GSsndPlayVolume((u32) var_r30, 0U, 0xFFU, 0U);
        }
    }
    fightSeq_NextWazaSeq(1U);
}

void WS_CRITICAL_MESSAGE(void) {
    FightWaza *temp_r3;

    fightSeq_GetWazaSeq();
    temp_r3 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11U, NULL));
    if ((fightWaza_GetCritical(temp_r3) == 2) && (fightWazaIsHit(temp_r3) == 1)) {
        fightFloor_SetCriticakMsgId(0, 0x4F1A);
        fightSeqOpenMsg(0x4F1A);
    }
    fightSeq_NextWazaSeq(1U);
}

void WS_HP_DEC_WAIT(void) {
    s32 temp_r31;
    FightOutPokemon *temp_r3;
    u8 fightType;

    fightType = fightFloor_GetFightType(NULL);
    temp_r3 = fightTargetGetPtrAsNowFightType(*(u8 *)(fightSeq_GetWazaSeq() + 0x1), NULL);
    temp_r31 = fightMenuGetFightOutPokemonPtrToStatusMenuId(temp_r3, fightType, 1);
    if (menuIsCheck() == 1) {
        menuFightStatusWaitAnimeHP(temp_r31, 1);
    }
    if (fightOutPokemonIsHinsi(temp_r3) == 1) {
        fightOutPokemonSetWazaEffectDownFlag(temp_r3, 1);
    }
    if ((fightOutPokemonIsJoutaiDataId(temp_r3, 0x14U) == 1) && (fightOutPokemonGetJoutaiMigawariHp(temp_r3) <= 0)) {
loop_6:
        if (wazaSequenceSysLastWazaIsImpactPoint(4) != 1) {
            GSthreadSwitch();
            goto loop_6;
        }
        fightOutPokemonInitJoutaiDataId(temp_r3, 0x14U);
        fightSeq_CallWazaSeq(WAZA_MigawariKizetsu);
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x14U, 0U);
        fightOutPokemonSetBuffJoutaiDataId(temp_r3, 0x14U, 0U);
    }
    fightSeq_NextWazaSeq(2U);
}

void WS_HP_DEC(void) {
    u8 *seq;
    u8 fightType;
    FightOutPokemon *attacker;
    u16 wazaId;
    FightWaza *waza;
    s32 damage;
    u8 kind;
    u32 zokusei;
    FightOutPokemon *defender;
    FightOutPokemon *fop;
    Pokemon *pokemon;
    s32 hp;
    u16 maxHp;
    s32 migawari;
    u32 targetId;
    s32 menuId;
    s16 animHp;

    seq = fightSeq_GetWazaSeq();
    fightType = fightFloor_GetFightType(NULL);
    attacker = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    wazaId = fightOutPokemon_GetUseWazaDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    damage = fightWaza_GetDamage(waza);
    u32 hitDamage = fightWaza_GetHitDamage(waza);
    zokusei = fightWaza_GetZokusei(waza);
    defender = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    if (wazaCheckDarkWaza(wazaId) == 1) {
        kind = waza_GetZokuseiKindData(wazaId);
    } else {
        kind = zokuseiBiosGetWazaKind(zokusei);
        if (wazaId == 0xED) {
            kind = 1;
        }
    }
    if (fightWazaIsHit(waza) == 1) {
        fop = fightTargetGetPtrAsNowFightType(seq[1], NULL);
        pokemon = fightOutPokemonGetPokemonPtr(fop);
        hp = pokemon_GetHp(pokemon);
        maxHp = pokemon_GetMaxHp(pokemon);
        migawari = fightOutPokemonGetJoutaiMigawariHp(fop);
        if (migawari != 0 && !(ServerStatusFlag & 0x100)) {
            if (migawari >= damage) {
                migawari -= damage;
            } else {
                damage = migawari;
                migawari = 0;
            }
            if (fightOutPokemon_GetKaigaraDamageValue(fop) == 0) {
                fightOutPokemon_SetKaigaraDamageValue(fop, damage);
            }
            fightWaza_SetHitDamage(waza, damage);
            fightOutPokemonSetJoutaiMigawariHp(fop, migawari);
            fightMenuOpenMsg(0x4E9CU);
            fightMainWaitFrame(0x40U);
            fightMenuCloseMsg();
        } else {
            ServerStatusFlag &= ~0x100;
            if (damage < 0) {
                hp -= damage;
                if (hp > maxHp) {
                    hp = maxHp;
                }
            } else {
                if (hp > damage) {
                    hitDamage = damage;
                    hp -= damage;
                } else {
                    hitDamage = hp;
                    hp = 0;
                }
                if (ServerStatusFlag & 0x20) {
                    ServerStatusFlag &= ~0x20;
                } else {
                    fightOutPokemon_SetGamanDamageValue(fop, damage + fightOutPokemon_GetGamanDamageValue(fop));
                    if (seq[1] == 0x12) {
                        targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightTarget *)attacker, fightType);
                        fightOutPokemon_SetGamanDamageTargetId(fop, targetId);
                    } else {
                        targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightTarget *)defender, fightType);
                        fightOutPokemon_SetGamanDamageTargetId(fop, targetId);
                    }
                    fightOutPokemonAddFightOutPokemonEnemyDamage(fop, attacker, hitDamage);
                }
                if (fightOutPokemon_GetKaigaraDamageValue(fop) == 0 && !(ServerStatusFlag & 0x100000)) {
                    fightOutPokemon_SetKaigaraDamageValue(fop, hitDamage);
                }
                switch (kind) {
                case 1:
                    if (!(ServerStatusFlag & 0x100000) && wazaId != 0xDC) {
                        fightOutPokemon_SetDamageAtkValue(fop, hitDamage);
                        fightOutPokemon_SetMyselfDamageAtkValue(fop, hitDamage);
                        if (seq[1] == 0x12) {
                            targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightTarget *)attacker, fightType);
                            fightOutPokemon_SetDamageAtkTargetId(fop, targetId);
                            fightOutPokemon_SetMyselfDamageAtkTargetId(fop, targetId);
                        } else {
                            targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightTarget *)defender, fightType);
                            fightOutPokemon_SetDamageAtkTargetId(fop, targetId);
                            fightOutPokemon_SetMyselfDamageAtkTargetId(fop, targetId);
                        }
                    }
                    break;
                case 2:
                    if (!(ServerStatusFlag & 0x100000)) {
                        fightOutPokemon_SetDamageSpeValue(fop, hitDamage);
                        fightOutPokemon_SetMyselfDamageSpeValue(fop, hitDamage);
                        if (seq[1] == 0x12) {
                            targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightTarget *)attacker, fightType);
                            fightOutPokemon_SetDamageSpeTargetId(fop, targetId);
                            fightOutPokemon_SetMyselfDamageSpeTargetId(fop, targetId);
                        } else {
                            targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightTarget *)defender, fightType);
                            fightOutPokemon_SetDamageSpeTargetId(fop, targetId);
                            fightOutPokemon_SetMyselfDamageSpeTargetId(fop, targetId);
                        }
                    }
                    break;
                }
            }
            ServerStatusFlag &= ~0x100000;
            fightWaza_SetHitDamage(waza, hitDamage);
            pokemon_SetHp(pokemon, (u16)hp);
            fightSeqCheckSetHensinBuffToMotoPokemon(fop, 0x83U);
            menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(fop, fightType, 1);
            animHp = hp;
            if (menuIsCheck() == 0) {
                fightMenuFightOutPokemonOpenStatusMenu(fop, fightType, 1U);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, fop, fightType, 0U, 1U);
            }
            fightMenuFightStatusStartAnimHP(menuId, animHp);
        }
    } else {
        fop = fightTargetGetPtrAsNowFightType(seq[1], NULL);
        if (fightOutPokemon_GetKaigaraDamageValue(fop) == 0) {
            fightOutPokemon_SetKaigaraDamageValue(fop, 0xFFFF);
        }
    }
    fightSeq_NextWazaSeq(2U);
}

void WS_WAZA_EFFECT(void) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r30;
    FightOutPokemon *temp_r30_2;
    u16 temp_r29;

    fightSeq_GetWazaSeq();
    fightFloor_GetFightType(NULL);
    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r29 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r30_2 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    if (fightWazaIsHit(temp_r30) == 1) {
        if ((ServerStatusFlag & 0x80) && (temp_r29 != 0x90) && (temp_r29 != 0xA4)) {
            fightSeq_CallWazaSeq(WAZA_Wait);
        } else {
            fightWazaDoEffectFunc(temp_r29, temp_r3, temp_r30_2, UserWork[0x160A1]);
        }
        UserWork[0x16002] = (u8) (UserWork[0x16002] + 1);
        UserWork[0x160A1] = (u8) (UserWork[0x160A1] + 1);
        fightSeq_NextWazaSeq(1U);
        return;
    }
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightSeqFightOutPokemonEffect(0x57U, temp_r30_2, 0U, 1U);
    fightSeq_NextWazaSeq(1U);
}

void WS_DAMAGE_LOSS_ONLY(void) {
    fightSeq_GetWazaSeq();
    fightSeqDamageLoss(0U, 1U);
    fightSeq_NextWazaSeq(1U);
}

void WS_DAMAGE_LOSS(void) {
    fightSeq_GetWazaSeq();
    fightSeqDamageLoss(1U, 1U);
    fightSeq_NextWazaSeq(1U);
}

void fightSeqDamageLoss(u8 arg0, u8 arg1) {
    FightOutPokemon *temp_r3_3;
    u16 temp_r28;
    u32 temp_r23;
    u16 temp_r27;
    u16 temp_r31;
    FightWaza *temp_r3_2;
    u16 temp_r0_2;
    FightOutPokemon *temp_r3;
    u32 var_r25;
    u32 temp_r30;

    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r28 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r3_2 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    var_r25 = fightWaza_GetDamage(temp_r3_2);
    temp_r3_3 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    temp_r27 = fightOutPokemonGetSoubiItemDataId(temp_r3_3);
    temp_r23 = fightOutPokemonGetSoubiItemSoubiDataId(temp_r3_3);
    temp_r30 = figthOutPokemonGetSoubiItemBuff(temp_r3_3);
    temp_r31 = pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r3_3));
    if (arg1 == 1) {
        temp_r0_2 = 0x64 - (HSD_Rand() % 16);
        if ((s32) var_r25 != 0) {
            var_r25 *= temp_r0_2;
            var_r25 = (s32)var_r25 / 100;
            if (var_r25 == 0) {
                var_r25 = 1;
            }
            fightWaza_SetDamage(temp_r3_2, var_r25);
        }
    }
    if (((u16) temp_r23 == 0x27) && ((s32) (HSD_Rand() % 100) < (s32) temp_r30)) {
        fightOutPokemon_SetItemKoraetaFlag(temp_r3_3, 1U);
    }
    if ((fightOutPokemonIsJoutaiDataId(temp_r3_3, 0x14U) == 0) && (((wazaDB_GetSeqId(temp_r28) == 0x65) && (arg0 == 1)) || (fightOutPokemonIsJoutaiDataId(temp_r3_3, 0x2CU) != 0) || (fightOutPokemon_GetItemKoraetaFlag(temp_r3_3) != 0)) && ((s32) pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r3_3)) <= (s32) var_r25)) {
        fightWaza_SetDamage(temp_r3_2, temp_r31 - 1);
        if (fightOutPokemonIsJoutaiDataId(temp_r3_3, 0x2CU) != 0) {
            if (fightWazaCheckWriteJoutaiDataId(temp_r3_2, 0x46U) == 2) {
                fightWazaWriteJoutaiDataId(temp_r3_2, 0x46U, 0U);
            }
        } else if (fightOutPokemon_GetItemKoraetaFlag(temp_r3_3) != 0) {
            if (fightWazaCheckWriteJoutaiDataId(temp_r3_2, 0x47U) == 2) {
                fightWazaWriteJoutaiDataId(temp_r3_2, 0x47U, 0U);
            }
            fightFloor_SetAppointItemDataId(0, temp_r27);
        }
    }
}

void WS_TYPE_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeqTypeCheck(1U, 1U, 1U, 0U, 1U);
}

void fightSeqTypeCheckHikaePokemon(FightPokemon *arg0, u8 arg1, u8 arg2, u8 arg3) {
    u8 spB6;
    u16 spB4;
    u8 spB1;
    u8 spB0;
    u16 spAE;
    u16 spAC;
    s32 spA8;
    s32 spA4;
    u8 spA1;
    u8 spA0;
    BasisWazaJoutaiBlock spC;
    FightOutPokemon *temp_r3;
    u32 temp_r3_2;
    FightWaza *temp_r3_3;
    u32 temp_r3_4;
    u16 temp_r28;
    u16 temp_r27;
    u8 temp_r26;
    u8 temp_r25;
    u16 var_r24;
    u32 temp_r21;
    u16 temp_r20;
    Pokemon *temp_r19;
    u8 temp_r19_2;
    u8 var_r17;
    u8 var_r16;
    u16 var_r14;

    var_r17 = 0;
    var_r16 = 0;
    temp_r19 = fightPokemon_GetPokemonBuffPtr(arg0);
    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r27 = fightOutPokemonGetZokuseiDataId(temp_r3, 0);
    temp_r28 = fightOutPokemonGetZokuseiDataId(temp_r3, 1);
    fightOutPokemonGetTokuseiDataId(temp_r3);
    temp_r3_2 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r20 = wazaDB_GetIryoku(temp_r3_2);
    temp_r3_3 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r21 = fightWaza_GetZokusei(temp_r3_3);
    temp_r3_4 = pokemon_GetPokemonDataId(temp_r19);
    temp_r26 = pokemonDB_GetZokuseiDataId(temp_r3_4, 0U);
    temp_r25 = pokemonDB_GetZokuseiDataId(temp_r3_4, 1U);
    temp_r19_2 = pokemonDB_GetTokuseiDataId((u16) temp_r3_4, pokemon_GetTokuseiFlag(temp_r19));
    if (temp_r3_3 != NULL) {
        spB6 = ((BasisWazaLayout *)temp_r3_3)->kind;
        var_r14 = ((BasisWazaLayout *)temp_r3_3)->originalMove;
        spB4 = ((BasisWazaLayout *)temp_r3_3)->move;
        var_r24 = ((BasisWazaLayout *)temp_r3_3)->power;
        spC = ((BasisWazaLayout *)temp_r3_3)->conditions;
        spA0 = ((BasisWazaLayout *)temp_r3_3)->type;
        spA1 = ((BasisWazaLayout *)temp_r3_3)->critical;
        spA4 = ((BasisWazaLayout *)temp_r3_3)->damage;
        spA8 = ((BasisWazaLayout *)temp_r3_3)->hitDamage;
        spAC = ((BasisWazaLayout *)temp_r3_3)->ability;
        spAE = ((BasisWazaLayout *)temp_r3_3)->target;
        spB0 = ((BasisWazaLayout *)temp_r3_3)->slot;
        spB1 = ((BasisWazaLayout *)temp_r3_3)->count;
    }
    if (((u16) temp_r3_2 != 0xA5) && (wazaCheckDarkWaza((u16) temp_r3_2) != 1) && ((arg3 != 1) || (temp_r20 != 0))) {
        if ((arg1 == 1) && ((temp_r27 == (u16) temp_r21) || (temp_r28 == (u16) temp_r21))) {
            fightWaza_SetDamage(temp_r3_3, (u32) ((s32) (fightWaza_GetDamage(temp_r3_3) * 0xF) / 10));
        }
        if ((temp_r19_2 == 0x1A) && ((u16) temp_r21 == 4)) {
            if (arg2 == 1) {
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x43);
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
            }
            ServerWork.flags[6] = 4;
        } else {
            figthSeqZokuseiCheckCalc(temp_r3_3, zokuseiGetWazaJoutai((u16) temp_r21, (u16) temp_r26), (u16) temp_r3_2, arg1);
            if (temp_r26 != temp_r25) {
                figthSeqZokuseiCheckCalc(temp_r3_3, zokuseiGetWazaJoutai((u16) temp_r21, (u16) temp_r25), (u16) temp_r3_2, arg1);
            }
        }
        if ((temp_r19_2 == 0x19) && (fightSeqTameWazaTurnCheck(temp_r3, (u16) temp_r3_2) == 2) && ((fightWazaIsJoutaiDataId(temp_r3_3, 0x41U) == 0) || (fightWazaIsJoutaiSousai(temp_r3_3) == 1)) && (temp_r20 != 0)) {
            if (arg2 == 1) {
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
            }
            ServerWork.flags[6] = 3;
        }
        if (fightWazaIsJoutaiDataId(temp_r3_3, 0x43U) == 1) {
            fightOutPokemon_SetOutWazaKoukanaiFlag(temp_r3, 1U);
        }
    }
    if (arg1 == 0) {
        if (fightWazaIsJoutaiDataId(temp_r3_3, 0x40U) == 1) {
            var_r17 = 1;
        }
        if (fightWazaIsJoutaiDataId(temp_r3_3, 0x43U) == 1) {
            var_r16 = 1;
        }
        if (temp_r3_3 != NULL) {
            ((BasisWazaLayout *)temp_r3_3)->kind = spB6;
            ((BasisWazaLayout *)temp_r3_3)->move = spB4;
            ((BasisWazaLayout *)temp_r3_3)->originalMove = var_r14;
            ((BasisWazaLayout *)temp_r3_3)->power = var_r24;
            ((BasisWazaLayout *)temp_r3_3)->conditions = spC;
            ((BasisWazaLayout *)temp_r3_3)->type = spA0;
            ((BasisWazaLayout *)temp_r3_3)->critical = spA1;
            ((BasisWazaLayout *)temp_r3_3)->damage = spA4;
            ((BasisWazaLayout *)temp_r3_3)->hitDamage = spA8;
            ((BasisWazaLayout *)temp_r3_3)->ability = spAC;
            ((BasisWazaLayout *)temp_r3_3)->target = spAE;
            ((BasisWazaLayout *)temp_r3_3)->slot = spB0;
            ((BasisWazaLayout *)temp_r3_3)->count = spB1;
        }
        if (var_r17 == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        }
        if (var_r16 == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x43);
        }
    }
}

void fightSeqTypeCheck(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    u8 spBA;
    u16 spB8;
    u16 spB6;
    u16 spB4;
    u8 spB1;
    u8 spB0;
    u16 spAE;
    u16 spAC;
    s32 spA8;
    s32 spA4;
    u8 spA1;
    u8 spA0;
    BasisWazaJoutaiBlock spC;
    FightOutPokemon *temp_r3;
    u32 temp_r3_2;
    FightWaza *temp_r3_3;
    FightOutPokemon *temp_r3_4;
    u16 temp_r28;
    u16 temp_r27;
    u16 temp_r26;
    u16 temp_r25;
    u16 temp_r24;
    u32 temp_r20;
    u16 temp_r19;
    u8 var_r17;
    u8 var_r16;

    var_r17 = 0;
    var_r16 = 0;
    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r26 = fightOutPokemonGetZokuseiDataId(temp_r3, 0);
    temp_r27 = fightOutPokemonGetZokuseiDataId(temp_r3, 1);
    fightOutPokemonGetTokuseiDataId(temp_r3);
    temp_r3_2 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r19 = wazaDB_GetIryoku(temp_r3_2);
    temp_r3_3 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r20 = fightWaza_GetZokusei(temp_r3_3);
    temp_r3_4 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    temp_r25 = fightOutPokemonGetZokuseiDataId(temp_r3_4, 0);
    temp_r24 = fightOutPokemonGetZokuseiDataId(temp_r3_4, 1);
    temp_r28 = fightOutPokemonGetTokuseiDataId(temp_r3_4);
    if (temp_r3_3 != NULL) {
        spBA = ((BasisWazaLayout *)temp_r3_3)->kind;
        spB8 = ((BasisWazaLayout *)temp_r3_3)->move;
        spB6 = ((BasisWazaLayout *)temp_r3_3)->originalMove;
        spB4 = ((BasisWazaLayout *)temp_r3_3)->power;
        spC = ((BasisWazaLayout *)temp_r3_3)->conditions;
        spA0 = ((BasisWazaLayout *)temp_r3_3)->type;
        spA1 = ((BasisWazaLayout *)temp_r3_3)->critical;
        spA4 = ((BasisWazaLayout *)temp_r3_3)->damage;
        spA8 = ((BasisWazaLayout *)temp_r3_3)->hitDamage;
        spAC = ((BasisWazaLayout *)temp_r3_3)->ability;
        spAE = ((BasisWazaLayout *)temp_r3_3)->target;
        spB0 = ((BasisWazaLayout *)temp_r3_3)->slot;
        spB1 = ((BasisWazaLayout *)temp_r3_3)->count;
    }
    if (((u16) temp_r3_2 != 0xA5) && (wazaCheckDarkWaza((u16) temp_r3_2) != 1) && (((u16) temp_r3_2 != 0x137) || (fightFloorGetNowTenkouDataId(NULL, 1U) != 5)) && ((arg3 != 1) || (temp_r19 != 0))) {
        if ((arg0 == 1) && ((temp_r26 == (u16) temp_r20) || (temp_r27 == (u16) temp_r20))) {
            fightWaza_SetDamage(temp_r3_3, (u32) ((s32) (fightWaza_GetDamage(temp_r3_3) * 0xF) / 10));
        }
        if ((temp_r28 == 0x1A) && ((u16) temp_r20 == 4)) {
            if (arg2 == 1) {
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x43);
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
                fightOutPokemon_SetHitWazaDataId(temp_r3_4, 0U);
                fightOutPokemon_SetHitWazaZokuseiDataId(temp_r3_4, 9U);
            }
            ServerWork.flags[6] = 4;
        } else if ((fightOutPokemonIsJoutaiDataId(temp_r3_4, 0x19U) != 1) || ((temp_r25 != 7) && (temp_r24 != 7)) || ((u16) temp_r20 > 1U)) {
            figthSeqZokuseiCheckCalc(temp_r3_3, zokuseiGetWazaJoutai((u16) temp_r20, temp_r25), (u16) temp_r3_2, arg0);
            if (temp_r25 != temp_r24) {
                figthSeqZokuseiCheckCalc(temp_r3_3, zokuseiGetWazaJoutai((u16) temp_r20, temp_r24), (u16) temp_r3_2, arg0);
            }
        }
        if ((temp_r28 == 0x19) && (fightSeqTameWazaTurnCheck(temp_r3, (u16) temp_r3_2) == 2) && ((fightWazaIsJoutaiDataId(temp_r3_3, 0x41U) == 0) || (fightWazaIsJoutaiSousai(temp_r3_3) == 1)) && (temp_r19 != 0)) {
            if (arg2 == 1) {
                fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
                fightOutPokemon_SetHitWazaDataId(temp_r3_4, 0U);
                fightOutPokemon_SetHitWazaZokuseiDataId(temp_r3_4, 9U);
            }
            ServerWork.flags[6] = 3;
        }
        if (fightWazaIsJoutaiDataId(temp_r3_3, 0x43U) == 1) {
            fightOutPokemon_SetOutWazaKoukanaiFlag(temp_r3, 1U);
        }
    }
    if (arg0 == 0) {
        if (fightWazaIsJoutaiDataId(temp_r3_3, 0x40U) == 1) {
            var_r17 = 1;
        }
        if (fightWazaIsJoutaiDataId(temp_r3_3, 0x43U) == 1) {
            var_r16 = 1;
        }
        if (temp_r3_3 != NULL) {
            ((BasisWazaLayout *)temp_r3_3)->kind = spBA;
            ((BasisWazaLayout *)temp_r3_3)->move = spB8;
            ((BasisWazaLayout *)temp_r3_3)->originalMove = spB6;
            ((BasisWazaLayout *)temp_r3_3)->power = spB4;
            ((BasisWazaLayout *)temp_r3_3)->conditions = spC;
            ((BasisWazaLayout *)temp_r3_3)->type = spA0;
            ((BasisWazaLayout *)temp_r3_3)->critical = spA1;
            ((BasisWazaLayout *)temp_r3_3)->damage = spA4;
            ((BasisWazaLayout *)temp_r3_3)->hitDamage = spA8;
            ((BasisWazaLayout *)temp_r3_3)->ability = spAC;
            ((BasisWazaLayout *)temp_r3_3)->target = spAE;
            ((BasisWazaLayout *)temp_r3_3)->slot = spB0;
            ((BasisWazaLayout *)temp_r3_3)->count = spB1;
        }
        if (var_r17 == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        }
        if (var_r16 == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x43);
        }
    }
    if (arg1 == 1) {
        fightSeq_NextWazaSeq((u32) arg4);
    }
}

void figthSeqZokuseiCheckCalc(void *arg0, u16 arg1, u16 arg2, u8 arg3) {
    s32 var_r4;
    u32 temp_r29;
    u8 var_r28;
    u16 temp_r27;

    temp_r29 = fightWaza_GetDamage((FightWaza *) arg0);
    temp_r27 = ((u32 (*)(u16))wazaDB_GetIryoku)(arg2);
    if (((fightWazaIsJoutaiDataId((FightWaza *) arg0, 0x43U) != 1) || (arg3 != 0)) && (arg1 != 0x3F)) {
        if (arg1 == 0x43) {
            var_r28 = 0;
        } else if (arg1 == 0x42) {
            var_r28 = 5;
        } else if (arg1 == 0x41) {
            var_r28 = 20;
        } else {
            return;
        }
        if (arg3 == 1) {
            var_r4 = (s32) (temp_r29 * var_r28) / 10;
            if ((var_r4 == 0) && (var_r28 != 0)) {
                var_r4 = 1;
            }
            fightWaza_SetDamage((FightWaza *) arg0, (u32) var_r4);
        }
        switch ((s32) var_r28) {                /* switch 2; irregular */
        case 0:                                 /* switch 2 */
            if (fightWazaCheckWriteJoutaiDataId((FightWaza *) arg0, arg1) == 2) {
                fightWazaWriteJoutaiDataId((FightWaza *) arg0, arg1, 0U);
            }
            fightWazaInitJoutaiDataId((FightWaza *) arg0, 0x42U);
            fightWazaInitJoutaiDataId((FightWaza *) arg0, 0x41U);
            return;
        case 5:                                 /* switch 2 */
            if ((temp_r27 != 0) && (fightWazaIsHit((FightWaza *) arg0) == 1)) {
                if (fightWazaIsJoutaiDataId((FightWaza *) arg0, 0x41U) == 1) {
                    fightWazaInitJoutaiDataId((FightWaza *) arg0, 0x41U);
                    return;
                }
                if (fightWazaCheckWriteJoutaiDataId((FightWaza *) arg0, arg1) == 2) {
                    fightWazaWriteJoutaiDataId((FightWaza *) arg0, arg1, 0U);
                    return;
                }
            }
            break;
        case 20:                                /* switch 2 */
            if ((temp_r27 != 0) && (fightWazaIsHit((FightWaza *) arg0) == 1)) {
                if (fightWazaIsJoutaiDataId((FightWaza *) arg0, 0x42U) == 1) {
                    fightWazaInitJoutaiDataId((FightWaza *) arg0, 0x42U);
                    return;
                }
                if (fightWazaCheckWriteJoutaiDataId((FightWaza *) arg0, arg1) == 2) {
                    fightWazaWriteJoutaiDataId((FightWaza *) arg0, arg1, 0U);
                }
            }
            break;
        }
    }
}

void WS_DAMAGE_CALC(void) {
    FightOutPokemon *temp_r28;
    FightOutPokemon *temp_r30;
    s32 temp_r30_2;
    FightWaza *temp_r3_2;
    u32 temp_r3_3;
    FightOutPokemon *temp_r3;
    u16 temp_r26;
    s32 temp_r25;
    s32 var_r25;
    s32 temp_r25_2;

    fightFloorBiosGetFightFloorPtr();
    fightSeq_GetWazaSeq();
    temp_r28 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r3 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    temp_r30 = fightTargetGetPtrAsNowFightType(2U, temp_r3);
    temp_r26 = fightOutPokemon_GetUseWazaDataId(temp_r28);
    temp_r3_2 = fightOutPokemon_GetFightWazaPtr(temp_r28);
    temp_r25 = fightWaza_GetIryoku(temp_r3_2);
    temp_r3_3 = fightWaza_GetZokusei(temp_r3_2);
    temp_r30_2 = fightSeqWazaDamageCalc(temp_r28, temp_r3, (u32) temp_r30, temp_r26, (u32)temp_r25, temp_r3_3);
    temp_r25_2 = temp_r30_2 * fightWaza_GetCritical(temp_r3_2);
    var_r25 = temp_r25_2 * fightWaza_GetDamageValue(temp_r3_2);
    if ((fightOutPokemonIsJoutaiDataId(temp_r28, 0x24U) == 1) && ((u16)temp_r3_3 == 0xD)) {
        var_r25 *= 2;
    }
    if (fightOutPokemonIsJoutaiDataId(temp_r28, 0x32U) == 1) {
        var_r25 = (s32) (var_r25 * 0xF) / 10;
    }
    if (wazaCheckDarkWaza(temp_r26) == 1) {
        if (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r3)) == 1) {
            var_r25 = (s32) (var_r25 * 5) / 10;
            if (fightWazaCheckWriteJoutaiDataId(temp_r3_2, 0x42U) == 2) {
                fightWazaWriteJoutaiDataId(temp_r3_2, 0x42U, 0U);
            }
        } else {
            var_r25 *= 2;
            if (fightWazaCheckWriteJoutaiDataId(temp_r3_2, 0x41U) == 2) {
                fightWazaWriteJoutaiDataId(temp_r3_2, 0x41U, 0U);
            }
        }
    }
    fightWaza_SetDamage(temp_r3_2, (u32) var_r25);
    fightSeq_NextWazaSeq(1U);
}

void WS_CRITICAL_CHECK(void) {
    u32 temp_r7;
    FightOutPokemon *temp_r3;
    u8 temp_r31;
    u8 var_r30;
    u8 var_r29;
    u32 temp_r28;
    FightOutPokemon *temp_r27;
    FightWaza *temp_r26;
    u16 var_r25;
    u16 temp_r25;
    s32 temp_r25_2;
    u16 temp_r24;
    s32 temp_r24_2;
    s32 temp_r24_3;
    s32 temp_r24_4;

    fightSeq_GetWazaSeq();
    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    fightOutPokemonGetTokuseiDataId(temp_r3);
    temp_r28 = fightOutPokemonGetSoubiItemSoubiDataId(temp_r3);
    temp_r26 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r25 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r24 = figthOutPokemonGetPokemonDataId(temp_r3);
    var_r29 = 0;
    temp_r27 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    if (((u16) temp_r28 == 0x3F) && (temp_r24 == 0x71)) {
        var_r29 = 1;
    }
    var_r30 = 0;
    if (((u16) temp_r28 == 0x42) && (temp_r24 == 0x53)) {
        var_r30 = 1;
    }
    temp_r24_2 = (fightOutPokemonIsJoutaiDataId(temp_r3, 0xFU) == 1) * 2;
    temp_r31 = wazaDB_GetSeqId(temp_r25) == 0x2B;
    temp_r24_3 = temp_r24_2 + (u8) (wazaDB_GetSeqId(temp_r25) == 0x4B);
    temp_r25_2 = temp_r24_3 + (u8) (wazaDB_GetSeqId(temp_r25) == 0xC8);
    var_r25 = temp_r31 + (temp_r25_2 + (u8) (wazaDB_GetSeqId(temp_r25) == 0xD1) + (u8) ((u16) temp_r28 == 0x29) + ((var_r29 * 2) & 0x1FE) + ((var_r30 * 2) & 0x1FE));
    temp_r7 = fight_waza_critical_data_number - 1;
    if (var_r25 > temp_r7) {
        var_r25 = temp_r7;
    }
    if ((fightOutPokemonGetTokuseiDataId(temp_r27) != 4) && (fightOutPokemonGetTokuseiDataId(temp_r27) != 0x4B) && (fightFloor_GetFightKindDoCriticalAttackFlag(0) == 1)) {
        temp_r24_4 = HSD_Rand();
        if ((temp_r24_4 % fightWazaCriticalDataBiosGetBunbo(fightWazaCriticalDataBiosGetPtr(var_r25))) == 0) {
            fightWaza_SetCritical(temp_r26, 2U);
        } else {
            fightWaza_SetCritical(temp_r26, 1U);
        }
    } else {
        fightWaza_SetCritical(temp_r26, 1U);
    }
    fightSeq_NextWazaSeq(1U);
}

void WS_PP_DEC(void) {
    s32 banme;
    s8 wazaNo;
    u8 n;
    FightOutPokemon *attacker;
    Pokemon *pokemon;
    u8 pp;
    u8 range;
    u16 tokusei;
    FightOutPokemon *defender;
    FightWaza *waza;

    n = 1;
    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    pokemon = fightOutPokemonGetPokemonPtr(attacker);
    defender = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    tokusei = fightOutPokemonGetTokuseiDataId(defender);
    if (!(ServerStatusFlag & 0xA00)) {
        range = wazaDB_GetRangeId(fightOutPokemon_GetUseWazaDataId(attacker));
        banme = fightWaza_GetWazaBanme(waza);
        wazaNo = banme;
        pp = pokemon_GetPokemonWazaPp(pokemon, wazaNo);
        if (fightOutPokemon_GetNoPressureFlag(attacker) == 0) {
            switch (range) {
            case 6:
                n = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x2EU, 0U, attacker) + 1;
                break;
            case 7:
            case 4:
                n = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x2EU, 2U, attacker) + 1;
                break;
            default:
                if (attacker != defender && tokusei == 0x2E) {
                    n = 2;
                }
                break;
            }
        }
        if (pp != 0) {
            fightOutPokemon_SetPassPpdecFlag(attacker, 1U);
            pokemon_SetPokemonWazaPp(pokemon, wazaNo, pp > n ? (u8)(pp - n) : 0);
            fightSeqPpdecMonomane(attacker, banme, 0);
        }
    }
    ServerStatusFlag &= 0xFFFFF7FF;
    fightSeq_NextWazaSeq(1U);
}

void fightSeqPpdecMonomane(FightOutPokemon *arg0, u8 arg1, s32 arg2) {
    u32 buff;
    if ((fightOutPokemonIsJoutaiDataId(arg0, 0x10U) == 0) && (fightOutPokemonIsJoutaiDataId(arg0, 0x31U) == 1)) {
        buff = fightOutPokemonGetBuffJoutaiDataId(arg0, 0x31U);
        if (!(buff & (1 << (u8) arg1))) {
            fightSeqCheckSetHensinBuffToMotoPokemon2(arg0, 0x80U, (u8) arg1, arg2);
        }
    }
}

void WS_ATTACK_MESSAGE(void) {
    FightOutPokemon *temp_r3;
    u8 temp_r30;
    FightOutPokemon *temp_r29;
    FightOutPokemon *temp_r28_2;
    s16 var_r27;
    u16 temp_r27;
    void *temp_r26;
    WazaSequence *temp_r26_2;
    FIGHT_TRAINER *temp_r28;

    temp_r30 = fightFloor_GetFightType(NULL);
    fightSeq_GetWazaSeq();
    if (!(ServerStatusFlag & 0x600)) {
        temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
        temp_r28 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(NULL, temp_r3);
        temp_r29 = ((FightOutPokemon *(*)(u8, FightOutPokemon *, u8))fightTargetGetPtr)(9U, (FightOutPokemon *) temp_r28, fightFloor_GetFightType(NULL));
        temp_r28_2 = ((FightOutPokemon *(*)(u8, FightOutPokemon *, u8))fightTargetGetPtr)(0xAU, (FightOutPokemon *) temp_r28, fightFloor_GetFightType(NULL));
        fightOutPokemonGetNicknamePtr(temp_r3);
        temp_r27 = fightOutPokemon_GetUseWazaDataId(temp_r3);
        temp_r26 = fightOutPokemon_GetSequencePtr(temp_r3);
        fightOutPokemon_GetFightPokemonPtr(temp_r3);
        fightSeqFightOutPokemonEffect(0x9EU, temp_r3, 0U, 1U);
        fightMenuFightOutPokemonOpenStatusMenu(temp_r3, temp_r30, 1U);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, temp_r3, temp_r30, 0U, 1U);
        if (fightMenuWazaOutMsg(temp_r3, temp_r27) == 1) {
            msgFrame = 0x50;
            ServerWork.flags[7] = 2;
        }
        if ((temp_r29 != NULL) && (fightTrainerAiDB_GetParamStoreFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId((FIGHT_TRAINER *) temp_r29))) == 1)) {
            fightAi_AddStoreWaza(temp_r3, (FIGHT_TRAINER *) temp_r29, temp_r27);
            fightAi_DereteExpectWaza(temp_r3, (FIGHT_TRAINER *) temp_r29, temp_r27);
        }
        if ((temp_r28_2 != NULL) && (fightTrainerAiDB_GetParamStoreFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId((FIGHT_TRAINER *) temp_r28_2))) == 1)) {
            fightAi_AddStoreWaza(temp_r3, (FIGHT_TRAINER *) temp_r29, temp_r27);
            fightAi_DereteExpectWaza(temp_r3, (FIGHT_TRAINER *) temp_r29, temp_r27);
        }
        if (temp_r26 != NULL) {
            temp_r26_2 = Sequence_GetWaza(temp_r26, 0x9EU, 4U);
            var_r27 = 0x120;
            while (WazaSequence_IsActive(temp_r26_2) != 0) {
                GSthreadSwitch();
                if (var_r27-- <= 0) {
                    GSprint(dbgMenuGetLayerID(), 0x1E, 0x1E, 0xA000FF, "Attack Msg Eff Play");
                    var_r27 = 0;
                }
            }
            WazaSequence_Free(temp_r26_2);
        } else {
            fightSeq_CallWazaSeq(WAZA_Wait);
        }
        fightMenuFightOutPokemonCloseStatusMenu(temp_r3, temp_r30, 0U);
        ServerStatusFlag |= 0x400;
    }
    fightSeq_NextWazaSeq(1U);
}

void WS_ATTACK_MESSAGE2(void) {
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    u8 temp_r31_2;
    u32 temp_r29;
    WazaSequence *temp_r29_2;
    u16 temp_r28;

    temp_r28 = fightFloorGetStatus(0, 0, 0x14, 0);
    fightSeq_GetWazaSeq();
    if (!(ServerStatusFlag & 0x600)) {
        temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
        fightFloorGetFightOutPokemonPtrToFightTrainerPtr(NULL, temp_r3);
        fightOutPokemonGetNicknamePtr(temp_r3);
        temp_r31 = fightOutPokemonGetUseWazaDataId(temp_r3);
        temp_r29 = pokemonGetStatus((Pokemon *) temp_r3, 0U, 0xEEU, 0U);
        fightSeqFightOutPokemonEffect(0x9EU, temp_r3, 0U, 1U);
        fightMenuFightOutPokemonOpenStatusMenu(temp_r3, temp_r28, 1U);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, temp_r3, temp_r28, 0U, 1U);
        temp_r31_2 = fightMenuWazaOutMsg(temp_r3, temp_r31);
        if (temp_r29 != 0) {
            temp_r29_2 = Sequence_GetWaza((void *) temp_r29, 0x9EU, 4U);
            while (WazaSequence_IsActive(temp_r29_2) != 0) {
                GSthreadSwitch();
            }
            WazaSequence_Free(temp_r29_2);
        } else {
            fightSeq_CallWazaSeq(WAZA_Wait);
        }
        if (temp_r31_2 == 1) {
            fightMenuCloseMsg();
        }
        fightMenuFightOutPokemonCloseStatusMenu(temp_r3, temp_r28, 0U);
        ServerStatusFlag |= 0x400;
    }
    fightSeq_NextWazaSeq(1U);
    ServerWork.flags[7] = 0;
}

void WS_HITCHECK(void) {
    u8 *temp_r3;
    u8 temp_r31;
    u32 var_r30;
    u32 temp_r30;
    u8 var_r30_2;
    FightTarget *temp_r3_2;
    FightOutPokemon *temp_r3_3;
    u8 temp_r29;
    u32 temp_r28;
    u32 temp_r27;
    u16 temp_r26;
    u16 temp_r25;
    u8 temp_r24;
    u8 temp_r23;
    u8 temp_r23_2;
    u16 var_r22;
    s8 temp_r22;
    u16 temp_r22_2;
    BasisServerWork *temp_r22_3;
    u8 temp_r21;
    FightWaza *temp_r21_2;
    u16 var_r20;
    s8 var_r0;

    temp_r21 = fightFloor_GetFightType(NULL);
    temp_r3 = fightSeq_GetWazaSeq();
    var_r20 = *(u16 *)(temp_r3 + 0x5);
    temp_r3_2 = (FightTarget *)fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r30 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(temp_r3_2, temp_r21);
    temp_r21_2 = fightOutPokemon_GetFightWazaPtr((FightOutPokemon *) temp_r3_2);
    temp_r25 = fightOutPokemonGetTokuseiDataId((FightOutPokemon *) temp_r3_2);
    temp_r3_3 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    temp_r26 = fightOutPokemonGetTokuseiDataId(temp_r3_3);
    temp_r27 = fightOutPokemonGetSoubiItemSoubiDataId(temp_r3_3);
    temp_r28 = figthOutPokemonGetSoubiItemBuff(temp_r3_3);
    temp_r29 = fightFloorGetNowTenkouDataId(NULL, 1U);
    if (var_r20 == 0xFFFFU || var_r20 == 0xFFFEU) {
        if ((var_r20 == 0xFFFFU) && (fightOutPokemonIsJoutaiDataId(temp_r3_3, 0x1DU) == 1) && ((u16) temp_r30 == (u16)fightOutPokemonGetUserFightTargetIdJoutaiDataId(temp_r3_3, 0x1DU))) {
            fightSeq_NextWazaSeq(7U);
            return;
        }
        if (fightOutPokemonIsJoutaiKie(temp_r3_3) != 0) {
            fightSeq_JumpWazaSeq(*(u8 * *)(temp_r3 + 0x1));
            return;
        }
        if (fightSeqGuardCheck(7U, 0U) == 0) {
            fightSeq_NextWazaSeq(7U);
        }
    } else {
        if (var_r20 == 0) {
            var_r20 = fightOutPokemon_GetUseWazaDataId((FightOutPokemon *) temp_r3_2);
            var_r30 = fightOutPokemonGetWazaZokuseiDataId((FightOutPokemon *) temp_r3_2);
        } else {
            var_r30 = (u16)wazaDB_GetZokuseiDataId(var_r20);
        }
        if (wazaCheckDarkWaza(var_r20) == 1) {
            var_r30_2 = waza_GetZokuseiKindData(var_r20);
        } else {
            var_r30_2 = zokuseiBiosGetWazaKind((u32) var_r30);
        }
        temp_r31 = wazaDB_GetRangeId(var_r20);
        if (fightSeqRegulationCheck(var_r20, (FightOutPokemon *) temp_r3_2, temp_r3_3) == 1) {
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x45);
            fightSeq_JumpWazaSeq(*(u8 * *)(temp_r3 + 0x1));
            return;
        }
        if ((fightSeqGuardCheck(7U, var_r20) == 0) && (fightSeqWazaFloorJoutaiCheck((FightOutPokemon *) temp_r3_2, temp_r3_3, var_r20) == 0)) {
            temp_r24 = fightOutPokemon_GetAbicntAverage((FightOutPokemon *) temp_r3_2);
            temp_r23 = fightOutPokemon_GetAbicntAvoid(temp_r3_3);
            u8 lockOn = fightOutPokemonIsJoutaiDataId(temp_r3_3, 0x19U);
            var_r0 = (temp_r24 + (0xC - temp_r23)) - 6;
            if (lockOn == 1) {
                var_r0 = (s8) temp_r24;
            }
            temp_r22 = fightAbicntFitMinMax(var_r0);
            u8 var_r23 = wazaDB_GetAvg(var_r20);
            if ((temp_r29 == 1) && (wazaDB_GetSeqId(var_r20) == 0x98)) {
                var_r23 = 0x32;
            }
            temp_r22_2 = var_r23 * fightWazaHitKakurituDataBiosGetKake(fightWazaHitKakurituDataBiosGetPtr(temp_r22));
            var_r22 = (u16) ((s32) temp_r22_2 / (s32) fightWazaHitKakurituDataBiosGetWaru(fightWazaHitKakurituDataBiosGetPtr(temp_r22)));
            if (temp_r25 == 0xE) {
                var_r22 = (u16) ((s32) (var_r22 * 0x82) / 100);
            }
            if ((temp_r29 == 3) && (temp_r26 == 8)) {
                var_r22 = (u16) ((s32) (var_r22 * 0x50) / 100);
            }
            if ((temp_r25 == 0x37) && (var_r30_2 == 1)) {
                var_r22 = (u16) ((s32) (var_r22 * 0x50) / 100);
            }
            if ((u16) temp_r27 == 0x16) {
                var_r22 = (u16) ((s32) (var_r22 * (0x64 - temp_r28)) / 100);
            }
            if ((s32) ((HSD_Rand() % 100) + 1) > (s32) var_r22) {
                if (fightWazaCheckWriteJoutaiDataId(temp_r21_2, 0x40U) == 2) {
                    fightWazaWriteJoutaiDataId(temp_r21_2, 0x40U, 0U);
                }
                if ((fightFloor_GetFightSideFightOutPokemonSideMax(NULL) >= 2U) && ((temp_r31 == 4) || (temp_r31 == 6) || (temp_r31 == 2))) {
                    ServerWork.flags[6] = 2;
                } else {
                    ServerWork.flags[6] = 0;
                }
                temp_r22_3 = &ServerWork;
                temp_r23_2 = temp_r22_3->flags[6];
                fightSeqTypeCheck(0U, 0U, 0U, 1U, 7U);
                if (((u8) temp_r22_3->flags[6] == 3) && ((temp_r23_2 == 2) || (temp_r23_2 == 0)) && (fightWazaIsJoutaiDataId(temp_r21_2, 0x43U) == 0)) {
                    temp_r22_3->flags[6] = temp_r23_2;
                }
            } else if (var_r20 == 0x175) {
                lbl_804EB918 = 1;
            }
            fightSeqWazaSeqSet(7U, var_r20);
        }
    }
}

u8 fightSeqWazaFloorJoutaiCheck(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2) {
    u8 temp_r30;
    s32 temp_r30_2;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;

    temp_r30 = fightFloor_GetFightType(NULL);
    wazaDB_GetSeqId(arg2);
    fightFloorGetNowTenkouDataId(NULL, 1U);
    temp_r30_2 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightTarget *) arg0, temp_r30);
    if (fightOutPokemonIsJoutaiDataId(arg1, 0x1DU) == 1) {
        u16 target = (u16)fightOutPokemonGetUserFightTargetIdJoutaiDataId(arg1, 0x1DU);
        if (target == (u16)temp_r30_2) {
            fightSeqWazaSeqSet(7U, arg2);
            return 1U;
        }
    }
    if (!(ServerStatusFlag & 0x10000) && (fightOutPokemonIsJoutaiDataId(arg1, 0x1FU) == 1)) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeqWazaSeqSet(7U, arg2);
        return 1U;
    }
    temp_cr0_eq = ServerStatusFlag;
    ServerStatusFlag &= 0xFFFEFFFF;
    if (((temp_cr0_eq & 0x20000) == 0) && (fightOutPokemonIsJoutaiDataId(arg1, 0x20U) == 1)) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeqWazaSeqSet(7U, arg2);
        return 1U;
    }
    temp_cr0_eq_2 = ServerStatusFlag;
    ServerStatusFlag &= 0xFFFDFFFF;
    if (((temp_cr0_eq_2 & 0x40000) == 0) && (fightOutPokemonIsJoutaiDataId(arg1, 0x21U) == 1)) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeqWazaSeqSet(7U, arg2);
        return 1U;
    }
    ServerStatusFlag &= 0xFFFBFFFF;
    if (fightSeqIsTenkouHit(arg2) == 1) {
        fightSeqWazaSeqSet(7U, arg2);
        return 1U;
    }
    if (fightSeqIsAllwaysHit(arg2) == 1) {
        fightSeqWazaSeqSet(7U, arg2);
        return 1U;
    }
    return 0U;
}

u8 fightSeqRegulationZenmetuCheck(u16 arg0) {
    u16 temp_r3;
    u8 temp_r31;
    u8 temp_r30;

    temp_r30 = fightFloor_GetFightKindRegulationFlag(0);
    temp_r31 = menuCBRule_ProhibitionSuicide();
    temp_r3 = wazaDB_GetSeqId(arg0);
    if ((temp_r30 == 1) && (temp_r31 == 1) && (temp_r3 == 7)) {
        return 1U;
    }
    return 0U;
}

u16 fightSeqRegulationGetJoutaiCount(u16 arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r3_2;
    FightOutPokemon *temp_r30;
    u8 temp_r29;
    u16 var_r28;
    FIGHT_TRAINER *temp_r3;
    u16 var_r26;
    u16 var_r25;

    var_r28 = 0;
    temp_r30 = fightTargetGetPtrAsNowFightType(2U, arg1);
    temp_r29 = (u8) fightFloor_GetFightTypeTrainerNum(0);
    fightFloor_GetFightTypeEntryPokemonNum(0);
    var_r26 = 0;
    for (; var_r26 < (u32)temp_r29; ++var_r26) {
        temp_r3 = fightSideGetValidFightTrainerPtr((FightSide *) temp_r30, var_r26);
        if (temp_r3 != NULL) {
            var_r25 = 0;
            for (; var_r25 < 6U; ++var_r25) {
                temp_r3_2 = fightTrainerGetValidFightPokemonPtr(temp_r3, var_r25);
                if ((temp_r3_2 != NULL) && (fightPokemonCheckFightOut(temp_r3_2) != 0) && (fightPokemonIsJoutaiDataId(temp_r3_2, arg0) == 1)) {
                    var_r28 += 1;
                }
            }
        }
    }
    return var_r28;
}

u8 fightSeqRegulationOverTwoCheck(u16 arg0, FightOutPokemon *arg1) {
    u8 temp_r3;
    u8 temp_r31;
    u8 temp_r30;

    temp_r30 = fightFloor_GetFightKindRegulationFlag(0);
    temp_r31 = menuCBRule_EnableSbToSleep();
    temp_r3 = menuCBRule_EnableSbToIceed();
    if (temp_r30 == 1) {
        if (arg0 == 8) {
            if ((temp_r31 != 1) && (fightSeqRegulationGetJoutaiCount(arg0, arg1) >= 1U)) {
                return 1U;
            }
            goto block_9;
        }
        if ((arg0 == 7) && (temp_r3 != 1) && (fightSeqRegulationGetJoutaiCount(7U, arg1) >= 1U)) {
            return 1U;
        }
        goto block_9;
    }
block_9:
    return 0U;
}

u8 fightSeqRegulationCheck(u16 arg0, FightOutPokemon *arg1, FightOutPokemon *arg2) {
    u16 temp_r3;
    u8 temp_r31;
    u8 temp_r30;
    u8 temp_r29;
    u8 temp_r28;
    FightOutPokemon *temp_r27_2;
    u8 temp_r27;
    u8 temp_r28_2;

    temp_r27 = fightFloor_GetFightKindRegulationFlag(0);
    temp_r28 = menuCBRule_EnableSkillSwap();
    temp_r29 = menuCBRule_EnableSkill_Michidure();
    temp_r30 = menuCBRule_EnableSkill_SonicBoom();
    temp_r31 = menuCBRule_EnableSbToSleep();
    menuCBRule_EnableSbToIceed();
    if (temp_r27 == 1) {
        if (arg0 == 0x11D) {
            if (temp_r28 != 1) {
                return 1U;
            }
        } else if (arg0 == 0xC3 || arg0 == 0xC2) {
            temp_r27_2 = fightTargetGetPtrAsNowFightType(2U, arg1);
            temp_r28_2 = (u8) fightFloor_GetFightTypeTrainerNum(0);
            if ((fightSideGetNokoriFightPokemonNum((FightSide *) temp_r27_2, temp_r28_2, (u8) fightFloor_GetFightTypeEntryPokemonNum(0)) <= 1U) && (temp_r29 != 1)) {
                return 1U;
            }
        } else if (arg0 == 0x52 || arg0 == 0x31) {
            if (temp_r30 != 1) {
                return 1U;
            }
        } else if (wazaDB_GetSeqId(arg0) == 1) {
            temp_r3 = fightSeqRegulationGetJoutaiCount(8U, arg2);
            if ((temp_r31 != 1) && (temp_r3 >= 1U)) {
                return 1U;
            }
        }
    }
    return 0U;
}

u8 fightSeqGuardCheck(u8 arg0, u16 arg1) {
    u8 var_r31;
    u16 temp_r31;

    temp_r31 = fightOutPokemon_GetUseWazaDataId(fightTargetGetPtrAsNowFightType(0x11U, NULL));
    FightOutPokemon *p = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    var_r31 = 0;
    if (fightSeqIsGuard(p, temp_r31) == 1) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeqWazaSeqSet(arg0, arg1);
        ServerWork.flags[6] = 1;
        var_r31 = 1;
    }
    return var_r31;
}

u8 fightSeqIsTenkouHit(u16 arg0) {
    u16 temp_r31;

    temp_r31 = wazaDB_GetSeqId(arg0);
    if ((fightFloorGetNowTenkouDataId(NULL, 1U) == 2) && (temp_r31 == 0x98)) {
        return 1U;
    }
    return 0U;
}

u8 fightSeqIsAllwaysHit(u16 arg0) {
    u16 temp_r3;

    temp_r3 = wazaDB_GetSeqId(arg0);
    if ((temp_r3 == 0x11) || (temp_r3 == 0x4E)) {
        return 1U;
    }
    return 0U;
}

u8 fightSeqIsGuard(FightOutPokemon *arg0, u16 arg1) {
    u8 temp_r31;

    temp_r31 = wazaDB_GetMamoru(arg1);
    if ((fightOutPokemonIsJoutaiDataId(arg0, 0x2BU) == 1) && (temp_r31 == 1)) {
        return 1U;
    }
    return 0U;
}

void WS_GUARDCHECK(void) {
    u8 temp_r31;
    FightOutPokemon *temp_r30;

    temp_r31 = wazaDB_GetMamoru(fightOutPokemon_GetUseWazaDataId(fightTargetGetPtrAsNowFightType(0x11U, NULL)));
    temp_r30 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    fightSeq_GetWazaSeq();
    if ((fightOutPokemonIsJoutaiDataId(temp_r30, 0x2BU) == 1) && (temp_r31 == 1)) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeqWazaSeqSet(5U, 0U);
        ServerWork.flags[6] = 1;
        return;
    }
    fightSeq_NextWazaSeq(5U);
}

void fightSeqWazaSeqSet(u8 arg0, u16 arg1) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r30;
    FightOutPokemon *temp_r30_2;

    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r30_2 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    if (fightWazaIsHit(temp_r30) == 0) {
        fightOutPokemon_SetHitWazaDataId(temp_r30_2, 0U);
        fightOutPokemon_SetHitWazaZokuseiDataId(temp_r30_2, 9U);
        fightSeq_JumpWazaSeq(fightSeq_GetWazaSeqPtr_u8(1U));
        return;
    }
    fightSeqMichidureCheckAct();
    if (fightSeqFightOutPokemonTokuseiCheckWazaHit(temp_r3, temp_r30_2, arg1) == 0) {
        fightSeq_NextWazaSeq((u32) arg0);
    }
}

void WS_BADGECHECK(void) {
    u8 var_r3;
    FightOutPokemon *temp_r3;
    u8 temp_r31;
    u8 temp_r30;
    u32 temp_r3_2;
    s8 temp_r3_3;
    u8 temp_r3_4;
    FightOutPokemon *temp_r28;
    Pokemon *temp_r27;
    FightWaza *temp_r26;
    FightWaza *temp_r24;
    s32 temp_cr0_eq;

    fightSeq_GetWazaSeq();
    temp_r3 = fightTargetGetPtrAsNowFightType(0x11U, NULL);
    temp_r27 = fightOutPokemonGetPokemonPtr(temp_r3);
    temp_r28 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
    if (fightGetFightResultId() != 0) {
        ActionSeqNo = 2;
        return;
    }
    if ((fightOutPokemonCheckFightOut(temp_r3) == 0) && !(ServerStatusFlag & 0x200)) {
        ServerStatusFlag |= 0x80000;
        fightSeq_JumpWazaSeq(WAZA_WazaEnd);
        return;
    }
    if ((fightSeqAttackPokemonJoutaiCheck() == 0) && (fightSeqFightOutPokemonTokuseiCheckWazaHitBefore(temp_r3, temp_r28) == 0)) {
        temp_r26 = fightOutPokemon_GetFightWazaPtr(temp_r3);
        temp_r3_2 = fightOutPokemon_GetUseWazaDataId(temp_r3);
        temp_r30 = wazaDB_GetMamoru(temp_r3_2);
        temp_r31 = wazaDB_GetMajikku((u16) temp_r3_2);
        temp_r3_3 = fightWaza_GetWazaBanme(temp_r26);
        if ((temp_r3_3 < 0) || ((u16) temp_r3_2 == 0xA5) || (wazaCheckDarkWaza((u16) temp_r3_2) == 1)) {
            var_r3 = 0;
        } else {
            var_r3 = pokemon_GetPokemonWazaPp(temp_r27, temp_r3_3);
        }
        if ((var_r3 == 0) && ((u16) temp_r3_2 != 0xA5) && (wazaCheckDarkWaza((u16) temp_r3_2) == 0) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x22U) == 0) && !(ServerStatusFlag & 0x800200)) {
            if (fightWazaCheckWriteJoutaiDataId(temp_r26, 0x40U) == 2) {
                fightWazaWriteJoutaiDataId(temp_r26, 0x40U, 0U);
            }
            ServerStatusFlag |= 0x80000;
            fightSeq_JumpWazaSeq(WAZA_PPNoneAttack);
            return;
        }
        temp_cr0_eq = (ServerStatusFlag & 0x02000000) == 0;
        ServerStatusFlag &= 0xFF7FFFFF;
        if ((temp_cr0_eq != 0) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x22U) == 0) && (temp_r3_4 = fightSeqBadgeCheck(temp_r3), ((temp_r3_4 == 0) == 0))) {
            if ((s32) temp_r3_4 == 2) {
                ServerStatusFlag |= 0x02000000;
                return;
            }
            if (fightWazaCheckWriteJoutaiDataId(temp_r26, 0x40U) == 2) {
                fightWazaWriteJoutaiDataId(temp_r26, 0x40U, 0U);
            }
        } else {
            ServerStatusFlag |= 0x02000000;
            if ((fightOutPokemonIsJoutaiDataId(temp_r28, 0x37U) == 1) && (temp_r31 == 1)) {
                fightSeqPressurePpdecCheck(temp_r3, temp_r28, 0x115U);
                fightOutPokemonInitJoutaiDataId(temp_r28, 0x37U);
                temp_r24 = fightOutPokemon_GetFightWazaPtr(temp_r28);
                fightSeq_CallWazaSeq(WAZA_MagicCort);
                if ((temp_r26 != NULL) && (temp_r24 != NULL)) {
                    fightWazaBiosCopy(temp_r24, temp_r26);
                    fightWaza_SetMotoWazaDataId(temp_r24, (u16) temp_r3_2);
                }
            } else {
                fightSeqWsBadgeCheckYokodori__FP15FightOutPokemon(temp_r3);
                if (fightOutPokemon_GetReceivesWazaHiraishinFlag(temp_r28) == 1) {
                    fightOutPokemon_SetReceivesWazaHiraishinFlag(temp_r28, 0U);
                    fightSeq_CallWazaSeq(WAZA_Hiraishin);
                }
                if ((fightOutPokemonIsJoutaiDataId(temp_r28, 0x2BU) == 1) && (temp_r30 == 1)) {
                    if (((u16) temp_r3_2 == 0xAE) && (fightOutPokemonIsZokuseiDataId(temp_r3, 7U) == 0)) {
                        fightSeq_NextWazaSeq(1U);
                        return;
                    }
                    if ((fightSeqTameWazaCheck((u16) temp_r3_2) == 0) || (fightOutPokemonIsJoutaiDataId(temp_r3, 0x22U) == 1)) {
                        fightOutPokemonInitJoutaiKeep(temp_r3);
                        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
                        fightOutPokemon_SetHitWazaDataId(temp_r28, 0U);
                        fightOutPokemon_SetHitWazaZokuseiDataId(temp_r28, 9U);
                        ServerWork.flags[6] = 1;
                        fightSeq_NextWazaSeq(1U);
                        return;
                    }
                    goto block_42;
                }
block_42:
                fightSeq_NextWazaSeq(1U);
            }
        }
    }
}

void fightSeqWsBadgeCheckYokodori__FP15FightOutPokemon(FightOutPokemon *arg0) {
    FightOutPokemon *res;
    BasisYokodoriWork search;
    FightWaza *temp_r31;
    FightWaza *temp_r3;
    u16 temp_r29;

    search.attacker = arg0;
    search.result = NULL;
    fightFloorLoopValidFightOutPokemon(NULL, (s32 (*)(FightOutPokemon *, u16, void *))_fightSeqWsBadgecheckSubYokodori__FPvUsPv, &search, 1U);
    res = search.result;
    if (res != NULL) {
        temp_r31 = fightOutPokemon_GetFightWazaPtr(arg0);
        temp_r3 = fightOutPokemon_GetFightWazaPtr(res);
        if ((temp_r3 != NULL) && (temp_r31 != NULL)) {
            temp_r29 = fightWaza_GetUseWazaDataId(temp_r3);
            fightWazaBiosCopy(temp_r3, temp_r31);
            fightWaza_SetMotoWazaDataId(temp_r3, temp_r29);
        }
    }
}

s32 _fightSeqWsBadgecheckSubYokodori__FPvUsPv(void *arg0, u16 arg1, void *arg2) {
    u8 temp_r31;
    FightOutPokemon *pokemon = (FightOutPokemon *)arg0;
    FightOutPokemon *temp_r29;
    BasisYokodoriWork *work = (BasisYokodoriWork *)arg2;

    temp_r29 = work->attacker;
    temp_r31 = wazaDB_GetYokodori(fightOutPokemon_GetUseWazaDataId(temp_r29));
    if (fightOutPokemonCheckFightOut(pokemon) == 0) {
        return 1;
    }
    if ((fightOutPokemonIsJoutaiDataId(pokemon, 0x33U) == 1) && (temp_r31 == 1)) {
        fightSeqPressurePpdecCheck(temp_r29, pokemon, 0x121U);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x33U);
        fightFloor_SetAppointPokemonPtr(NULL, pokemon);
        fightSeq_CallWazaSeq(WAZA_Yokodori);
        work->result = pokemon;
    }
    return 1;
}

u8 fightSeqBadgeCheck(FightOutPokemon *arg0) {
    FIGHT_TRAINER *temp_r3;

    fightFloor_GetFightType(NULL);
    fightOutPokemonGetPokemonPtr(arg0);
    fightTargetGetPtrAsNowFightType(2U, arg0);
    fightOutPokemon_GetFightWazaPtr(arg0);
    figthOutPokemonGetLevel(arg0);
    temp_r3 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(NULL, arg0);
    if (temp_r3 == NULL) {
        return 0U;
    }
    fightTargetGetPtrAsNowFightType(9U, (FightOutPokemon *) temp_r3);
    fightTrainer_GetHeroPtr(temp_r3);
    fightOutPokemon_GetUseWazaDataId(arg0);
    fightOutPokemonGetSoubiItemDataId(arg0);
    fightOutPokemonGetSoubiItemSoubiDataId(arg0);
    pokemon_GetSeikaku(fightOutPokemonGetPokemonPtr(arg0));
    return 0U;
}

FightOutPokemon *fightSeqSelectDefensePokemonPtr(FightOutPokemon *arg0, u16 arg1, u16 arg2, void *arg3, u8 arg4, u8 arg5, s8 arg6) {
    u8 var_r3;
    FightOutPokemon *temp_r3;
    FightOutPokemon *var_r31;
    FightOutPokemon *temp_r3_2;
    FightOutPokemon *temp_r3_3;
    u16 temp_r29;
    u16 temp_r29_2;
    u8 var_r28;
    u16 temp_r28;
    u32 temp_r27;

    var_r31 = NULL;
    if (arg6 < 0) {
        var_r3 = wazaDB_GetRangeId(arg1);
    } else {
        var_r3 = (u8) arg6;
    }
    var_r28 = var_r3;
    if ((arg1 == 0xAE) && (fightOutPokemonIsZokuseiDataId(arg0, 7U) == 0)) {
        var_r28 = 5;
    }
    temp_r27 = wazaDB_GetZokuseiDataId(arg1);
    temp_r29 = fightFloorGetValidFightOutPokemonCount(NULL, 0U, arg0, 1U);
    temp_r28 = fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(NULL, 0x1FU, 2U, arg0);
    switch (var_r28) {
    case 0:
                if (temp_r29 >= 2U) {
                    if (arg4 == 1) {
                        if (arg3 != NULL) {
                            var_r31 = ((FightOutPokemon *(*)(FightOutPokemon *, u16, u16)) arg3)(arg0, arg1, arg2);
                        } else {
                            var_r31 = fightFloorGetFightOutPokemonPtrRandom(NULL, 1U, 2U, arg0);
                        }
                    } else {
                        var_r31 = fightTargetGetPtrAsNowFightType(0x12U, NULL);
                    }
                    if (arg5 == 1) {
                        temp_r29_2 = fightOutPokemonGetTokuseiDataId(var_r31);
                        temp_r3 = fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(arg0);
                        if (temp_r3 != NULL) {
                            var_r31 = temp_r3;
                        } else if ((temp_r29_2 != 0x1F) && (temp_r27 == 0xD) && (temp_r28 != 0)) {
                            var_r31 = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(NULL, 0x1FU, 1U, 2U, arg0);
                            fightOutPokemon_SetReceivesWazaHiraishinFlag(var_r31, 1U);
                        }
                    }
                } else if (arg4 == 1) {
                    var_r31 = fightFloorGetFightOutPokemonPtrRandom(NULL, 1U, 3U, arg0);
                }
        break;
    case 1:
    case 4:
    case 6:
    case 7:
        if (arg4 == 1) {
            var_r31 = fightTargetGetPtr(0xFU, arg0, arg2);
            if (fightOutPokemonCheckFightOut(var_r31) == 0) {
                var_r31 = fightTargetGetPtrAsNowFightType(0xEU, var_r31);
            }
        }
        break;
    case 2:
    case 3:
        if (arg4 == 1) {
            var_r31 = fightFloorGetFightOutPokemonPtrRandom(NULL, 1U, 2U, arg0);
        }
        break;
    case 5:
        if (arg4 == 1) {
            var_r31 = arg0;
        }
        break;
    }
    return var_r31;
}

FightOutPokemon *fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(FightOutPokemon *arg0) {
    u32 temp_r3;
    FightOutPokemon *temp_r31;
    FightTarget *var_r30;
    FightTarget *temp_r3_2;
    u8 temp_r29;

    temp_r31 = fightTargetGetPtrAsNowFightType(3U, arg0);
    temp_r29 = fightFloor_GetFightType(NULL);
    var_r30 = NULL;
    if (fightSideIsJoutaiDataId((FightSide *) temp_r31, 0x4DU) == 1) {
        temp_r3 = fightSideGetJoutaiUserFightTargetId((FightSide *) temp_r31, 0x4DU);
        if ((u16) temp_r3 != 0) {
            temp_r3_2 = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr((u32) temp_r3, (u16) temp_r29);
            if ((temp_r3_2 != NULL) && (fightOutPokemonCheckFightOut((FightOutPokemon *) temp_r3_2) == 1)) {
                var_r30 = temp_r3_2;
            }
        }
    }
    return (FightOutPokemon *) var_r30;
}
}

extern "C" void WS_EFFECT_WAIT(void) {
    FightOutPokemon *defender;
    FightOutPokemon *attacker;
    u16 move;
    void *defenderSequence;
    FIGHT_TRAINER *trainer;
    FightWaza *waza;
    u32 mode;
    u8 *seq;
    void *trainerSequence;
    seq=fightSeq_GetWazaSeq();
    attacker=fightTargetGetPtrAsNowFightType(0x11,0);
    if(!seq)seq=0;
    if(!attacker)attacker=0;
    move=fightOutPokemon_GetUseWazaDataId(attacker);
    waza=fightOutPokemon_GetFightWazaPtr(attacker);
    defender=fightTargetGetPtrAsNowFightType(0x12,0);
    trainer=fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,defender);
    trainerSequence=fightTrainer_GetSequencePtr(trainer);
    defenderSequence=fightOutPokemon_GetSequencePtr(defender);
    if(!(ServerStatusFlag&0x80)||move==0x90||move==0xA4){
        mode=seq[1];
        for(;;){if(wazaSequenceSysLastWazaIsImpactPoint(mode)==1)break;GSthreadSwitch();}
        if(mode==0 && (s32)fightWaza_GetDamage(waza)>0 && fightWazaIsHit(waza)==1 && trainer!=fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,attacker) && trainerSequence){
            if(*((u8*)trainerSequence+0x61))*((void**)((u8*)trainerSequence+0x78))=defenderSequence;
            DoModelAnimation__13ModelSequenceFi(trainerSequence,4);
        }
    }
    if(mode==3||mode==4){
        fightMenuAllFightOutPokemonCloseStatusMenu(0);
        if(trainerSequence && *((u8*)trainerSequence+0x61))*((void**)((u8*)trainerSequence+0x78))=0;
    }
    if(fightOutPokemon_GetUseWazaDataId(attacker)==0xE2 && fightFloorIsUseFightTimerCommand(0)==1){fightTimerCommandInit();fightTimerCommandStart();}
    fightSeq_NextWazaSeq(2);
}
