#include <dolphin/types.h>

#pragma auto_inline off

struct FightTrainer {
    u8 unk0[0x3744];
};
struct FightPokemon;
struct FightOutPokemon;
struct FightAction;
struct FightKindData;
struct FightTrainerEnemyPokemon;
struct FightTrainerKindData;
struct Hero;
struct Item {
    u8 unk0[4];
};
class DeckTrainer {
public:
    static DeckTrainer* getDeckTrainerObj(u32 id);
    u16 getDarkPokemonDataID(u8 index) const;
};
struct Pokemon {
    u8 unk0[0xC4];

    void setRnd(u32 rnd);
    void setItemDataId(u16 id);
};
class FIGHT_ENCOUNT {
public:
    u8 getFightMode() const;
    u8 getAddMode() const;
    u8 getAddPlace() const;
    u8 getAddID() const;
    u8 getSwapMode() const;
    u16 getSwapDeckNO() const;
};
class DarkPokemon {
public:
    s32 getStatus() const;
    u16 getDarkPokemonID() const;
    u32 getEscapeTime() const;
    s32 getSnatchFromWho() const;
    u16 getCatchFloorId() const;
    void setRnd(u32 rnd);
};
class DeckDarkPokemon {
public:
    static DeckDarkPokemon* getDeckDarkPokemonObj(u32 id);
    u16 getDeckPokemonID() const;
    u8 getWorth() const;
};
struct EsabaPokemonData {
    u8 minLevel;
    u8 maxLevel;
    u16 pokemonId;
    u8 unk4[8];
};
struct EsabaPokemonTable {
    u32* num;
    EsabaPokemonData* data;
};
struct EsabaData {
    u8 unk0[0x18];
    EsabaPokemonTable** pokemon;
};

u16 deckDataVirtualDB_GetItemID(u16 disk, u8 index);
u8 deckDataVirtualDB_GetItemNum(u16 disk, u8 index);

static void _fightTrainerCreateRndCheckRare(Hero* hero, bool rare);
static bool _fightTrainerCreateDeckPokemon(Hero* hero, u16 pokemonId, u16 darkId, u16 ballId, Pokemon* pokemon, u8 index,
                                           u16 encountId);
static void _fightTrainerCreateDeckNormal(u16 id, Hero* hero, u16 encountId);
static void _fightTrainerCreateDeckWildPoke(u16 id, Hero* hero);
static void _fightTrainerCreateDeckVirtual(u16 id, Hero* hero, u16 encountId);
static void _fightTrainerCreateDeckBingo(u16 id, Hero* hero);
static void _fightTrainerCreateDeckUnderTakerInColosseum(u16 id, Hero* hero, u16 encountId);
static void _fightTrainerCreateDeckUnderTaker(u16 id, Hero* hero, u16 encountId);
static void _fightTrainer_GetUnderTakerDarkPoke(u8* list, u8 count, u8 start, Hero* hero, u8 num, u16 encountId);
static void _fightTrainer_SortUnderTakerDarkPoke(u8* list, u8 count);
static u8 _fightTrainer_GetListUnderTakerDarkPoke(u8* list);

struct BINGO_PANEL_dd_ {
    u8 type;
    u8 tokusei;
    u8 seikaku;
    u8 sex;
    u16 no;
    u16 waza;
    u16 hosei;
};
struct BINGO_DATA_dd_ {
    u8 no;
    u8 unk1[2];
    u8 level;
    u8 unk4;
    u8 ball;
    u8 unk6[0x10 - 6];
    u16 score[10];
    BINGO_PANEL_dd_ panel[14];
};
class bingo_bios {
public:
    static u8 getPanelHoseiVal(BINGO_DATA_dd_* data, u32 index);
    static u8 getPanelHoseiKind(BINGO_DATA_dd_* data, u32 index);
    static u8 getStaticIdx(u8 index);
    static BINGO_DATA_dd_* getStaticSheet();
};
u32 deckDataVirtualDB_GetEnemyDeck(u16 id);
u32 deckDataVirtualDB_GetAllyDeck(u16 id);
u8 deckDataVirtualDB_GetPokemonNum(u16 id);
class DeckPokemon {
public:
    static DeckPokemon* getDeckPokemonObj(u32 id);
    u16 getPokemonID() const;
    u8 getRandomSetting() const;
    u8 getLevel() const;
    u8 getFriendLevel() const;
    s8 getSex() const;
    s8 getSeikakuID() const;
    u8 getTokuseiFlag() const;
    u16 getHoldItem() const;
    u8 getComboPartnerAll() const;
    u8 getStatusRnd(u8 index) const;
    u8 getStatusEffort(u8 index) const;
    u16 getWazaID(u8 index) const;
};
class DeckTrainerAI {
public:
    static DeckTrainerAI* getDeckTrainerAIObj(u32 id);
};
struct GSvec {
    f32 x, y, z;
};

static u8 _fightTrainerGetHeroKind(u16 id);

extern "C" {

void* fightEncountDataBiosGetPtr(u16 id);
u8 fightEncountDataBiosGetFightKind(void* encount);
u16 fightEncountDataBiosGetFightTrainerDataId(void* encount, u32 side);
FightKindData* fightKindDataBiosGetPtr(u16 id);
u8 fightKindDataBiosGetHostEnemyMsgFlag(FightKindData* data);
u16 fightGetFightResultId(void);

DeckTrainer* fightTrainerDataBiosGetPtr(u16 id);
u16 fightTrainerDB_GetName(u16 id);
u8 fightTrainerDB_GetKindDataId(u16 id);
u16 fightTrainerDB_GetAiDataId(u16 id);
u16 fightTrainerDB_GetPkxDataId(u16 id);
FightTrainerKindData* fightTrainerKindDataBiosGetPtr(u16 id);
u32 fightTrainerKindDataBiosGetPrefixName(FightTrainerKindData* data);

Hero* fightTrainer_GetHeroPtr(FightTrainer* trainer);
u16 fightTrainer_GetFightTrainerDataId(FightTrainer* trainer);
u8 fightTrainer_GetControllerId(FightTrainer* trainer);
FightPokemon* fightTrainer_GetFightPokemonPtr(FightTrainer* trainer, u16 index);
FightOutPokemon* fightTrainer_GetFightoutPokemonPtr(FightTrainer* trainer, u16 index);
FightOutPokemon* fightTrainer_GetFightoutPokemonBuffPtr(FightTrainer* trainer);
FightTrainerEnemyPokemon* fightTrainer_GetFightTrainerEnemyPokemonAryPtr(FightTrainer* trainer, u8 index);
FightAction* fightTrainer_GetFightActionBuffPtr(FightTrainer* trainer);
void fightTrainer_SetFightTrainerDataId(FightTrainer* trainer, u16 id);
void fightTrainer_SetControllerId(FightTrainer* trainer, u8 id);
void fightTrainer_SetSequencePtr(FightTrainer* trainer, u32 seq);
void fightTrainer_SetOkaneBai(FightTrainer* trainer, u8 value);
void fightTrainer_SetKoban(FightTrainer* trainer, u32 value);
void fightTrainer_SetNigeruCount(FightTrainer* trainer, u8 value);

u8 fightTrainerEnemyPokemonCheckValid(FightTrainerEnemyPokemon* p);
void fightTrainerEnemyPokemonInitFightOutStatus(FightTrainerEnemyPokemon* p);
void fightTrainerEnemyPokemonInitAry(FightTrainerEnemyPokemon* p, u16 num);

u8 fightPokemonCheckValid(FightPokemon* fp);
u8 fightPokemonCheckFightOut(FightPokemon* fp);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon* fp);
u8 fightPokemon_GetHokakuFlag(FightPokemon* fp);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon* fp);
Pokemon* fightPokemon_GetMotoPokemonPtr(FightPokemon* fp);
s16 fightPokemon_GetEntryId(FightPokemon* fp);
u8 fightPokemonCheckMotoFightPokemon(FightPokemon* fp, FightOutPokemon* fo);
void fightPokemonInitAry(FightPokemon* fp, u16 num);

u8 fightOutPokemonCheckValid(FightOutPokemon* fo);
u8 fightOutPokemonCheckFightOut(FightOutPokemon* fo);
u16 fightOutPokemonGetFightActionUseItemDataId(FightOutPokemon* fo);
u8 fightOutPokemonIsFightActionUseItemKind(FightOutPokemon* fo, u32 a, u32 b, u32 c);
FightAction* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon* fo);
u8 fightOutPokemonCheckIrekaeReserveFightPokemon(FightOutPokemon* fo, FightPokemon* fp);
void fightOutPokemonInitFightActionBuff(FightOutPokemon* fo);
void fightOutPokemonInitAry(FightOutPokemon* fo, u16 num);
void fightOutPokemonInit(FightOutPokemon* fo);
u8 fightActionCheckValid(FightAction* action);
void fightActionInit(FightAction* action);

u32 heroGetStatus(Hero* hero, u32 kind, u16 index);
u8 heroCheckValid(Hero* hero);
u8 heroIsMinePokemon(Hero* hero, Pokemon* pokemon);
void heroInit(Hero* hero);
void heroBiosCopy(Hero* dst, Hero* src);
Item* heroItemGetItemKindToItemAryPtr(Hero* hero, u32 kind, u16* count, u32 a, u32 b, u32 c);
u8 itemCheckValid(Item* item);
u16 item_GetItemDataId(Item* item);
u16 item_GetNum(Item* item);
u8 pokemonCheckValid(Pokemon* pokemon);
u8 pokemonIsJoutaiNormal(Pokemon* pokemon);
u16 pokemonGetSoubiItemDataId(Pokemon* pokemon);
void pokemonBiosCopy(Pokemon* dst, Pokemon* src);
u8 pokemonIsJoutaiDataId(Pokemon* pokemon, u32 id);
void pokemonSetCountAsJoutaiDataId(Pokemon* pokemon, u32 id, u32 count);
void pokemon_SetItemDataId(Pokemon* pokemon, u16 id);

u16 charNameBiosSearchIndex(u32 nameID);
u16 charNameBiosGetHearFlag(u16 index);
void GSflagOn(u32 id);
void fightMsgctrlSetValue(u32 id, u32 value);
u16* GSmsgGetGSchar(u32 id);
void* fightTargetGetPtr(u32 kind, void* a, u32 b);
u32 Sequence_LoadTrainer(u32 id);
void Sequence_SetVisibility(u32 seq, u32 visible);
void fightFloorSetShadow(void);

struct FightActionData;
extern FightActionData fight_action_data_waza;
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon* fo, u32 kind);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon* fo);
u16 pokemon_GetPokemonWazaDataId(Pokemon* pokemon, s32 index);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon* fo, s32 index, u32 a, u32 b);
void* fightSeqSelectDefensePokemonPtr(FightOutPokemon* fo, u16 waza, u32 side, u32 a, u32 b, u32 c, s32 d);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void* target, u32 side);
void fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon* fo, u32 a, u32 kind, u32 b, FightActionData* data,
                                                u32 waza, u32 target, s8 index, u32 flag);
void fightTrainerAiSelectFightAction(FightTrainer* trainer, u32 side);
void fightMenuFightTrainerGcHeroOpenMenu(FightTrainer* trainer, u32 side, u32 flag);
u8 fightMenuFightTrainerAgbHeroOpenMenu(FightTrainer* trainer, u32 side);
u8 dbgMenuFightGetAllFightTrainerOperateFlag(void);
s16 fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(FightTrainer* trainer, u32 a, u32 b, u32 c, u32 d);
s16 fightTrainerAiSelectIrekaeDasuFightPokemon(FightTrainer* trainer, u32 a, u32 b, u32 c);
s16 fightMenuFightTrainerAgbHeroSelectIrekaeFightPokemon(FightTrainer* trainer, u32 a, u32 b, u32 c);
u32 fightTrainer_GetSequencePtr(FightTrainer* trainer);
void Sequence_LoadWaza(u32 seq, u32 id, u32 kind, u32 flag);
u32 Sequence_GetWaza(u32 seq, u32 id, u32 kind);
void WazaSequence_Start(u32 waza, u32 flag);
u8 WazaSequence_IsActive(u32 waza);
void WazaSequence_Free(u32 waza);
void GSthreadSwitch(void);
FightTrainerEnemyPokemon* fightTrainerEnemyPokemonSearchAry(FightTrainerEnemyPokemon* ary, u16 num, s16 id);
void fightTrainerAllInitFightActionBuff(FightTrainer* trainer);
void fightEncountDataBiosSetFightTrainerDataId(void* encount, u32 side, u16 id);
void fightEncountDataBiosSetPokemon(void* encount, u8 num);
void pokemonSetTokuseiFlag(Pokemon* pokemon, u8 flag);
u32 pokemonCreateRndFit(Pokemon* pokemon, s8 sex, s8 seikaku, u32 a, u32 rnd);
void pokemon_SetRnd(Pokemon* pokemon, u32 rnd);
void pokemonWazaInit(Pokemon* pokemon, u32 index);
void pokemonWazaCreate(Pokemon* pokemon, u8 index, u16 waza);
void pokemonSetStatus(Pokemon* pokemon, u32 a, u16 kind, u32 b, u16 value);
u16 pokemonGetStatus(Pokemon* pokemon, u32 a, u16 kind, u32 b);
s32 GSflagGet(u32 id);
void fightFreeResourceID(u32 a, u32 id);
void fightReadResourceID(u32 a, u32 id);
u8 darkPokemonBiosGetFightFlag(u16 id);
s8 darkPokemonBiosGetStatusRnd(u16 id, s32 index);
void darkPokemonBiosSetStatusRnd(u16 id, s32 index, s8 value);
u32 darkPokemonBiosGetRnd(u16 id);
void darkPokemonBiosSetRnd(u16 id, u32 rnd);
u32 heroBiosGetRnd(Hero* hero);
void pokemon_SetFriend(Pokemon* pokemon, u8 level);
void pokemon_SetComboPartnerAll(Pokemon* pokemon, u8 combo);
void pokemonDoItemSoubi(Pokemon* pokemon, u16 item, u32 mode);
u8 wazaCheckDarkWaza(u16 waza);
void pokemonSetDarkPokemonStatus(Pokemon* pokemon, u16 darkId);
s8 underTakerDeckRand = -1;
FIGHT_ENCOUNT* fightEncountGetStrObj(void);
u16 fightGetFightEncountDataId(void);
u16 fightEncountDataBiosGetDiskId(void* encount);
u8 fightTrainerAiDB_GetPokemonDataOrderOutFlag(u16 id);
void fightTrainerAiSortFirstSelectPokemonAry(FightTrainer* trainer, Hero* hero, Pokemon** ary, u16 num, u32 mode);
void pokemonInit(Pokemon* pokemon);
void* memcpy(void* dst, const void* src, u32 size);
void* savedataGetStatus(u32 a, u32 kind);
Pokemon* heroBiosGetPokemonPtr(Hero* hero, u16 index);
u8 pokemon_GetLevel(Pokemon* pokemon);
u16* heroBiosGetNamePtr(Hero* hero);
void heroCreate(Hero* hero, u16* name, u32 sex);
s32 heroItemAddItemDataId(Hero* hero, u16 item, u8 num, s32 slot);
u32 fightTrainerDB_GetSexDataId(u16 id);
void pokemon_SetLevel(Pokemon* pokemon, u8 level);
u32 pokemonGetLevelToExp(Pokemon* pokemon, u8 level);
void pokemon_SetExp(Pokemon* pokemon, u32 exp);
void pokemonResetBasisStatus(Pokemon* pokemon);
void heroSetStatus(Hero* hero, u32 kind, u32 value);
u16 pokemon_GetPokemonDataId(Pokemon* pokemon);
u32 pokemon_GetRnd(Pokemon* pokemon);
u8 pokemonCheckRareRnd(u32 heroRnd, u32 pokemonRnd);
u32 heroCreateRnd(void);
void pokemon_SetCatchTrainerRnd(Pokemon* pokemon, u32 rnd);
DarkPokemon* darkPokemonGetDarkPokemon(u32 id);
u8 fightTrainerCreateFightTrainerPokemonDataIdToPokemon(u16 id, Pokemon* pokemon, u32 rnd, u16 darkId, u16 level);
void deckCreate(u16 id, u16 pokemonId, Pokemon* pokemon);
void pokemon_SetFightTrainerPokemonDataId(Pokemon* pokemon, u16 id);
s16 heroCatchPokemon(Hero* hero, Pokemon* pokemon, u32 a, u16 ballId, u32 b);
u16 HSD_Rand(void);
u16 fightFloor_GetFightFloorDataId(u32 side);
void heroBiosSetRnd(Hero* hero, u32 rnd);
u16 esabaGetPokemonID(s32 index);
u32 esabaGetPokemonRnd(s32 index);
u32 gamedataGetStatus(u32 a, u32 kind);
void pokemonCreate(Pokemon* pokemon, u16 id, u8 level, u32 trainer);
u16 pokemonDB_GetItemDataId(u16 id, u32 index);
extern EsabaData* esabadata;
extern u32* esabadata_number;
void fightTrainerDB_SetAiDataId(u16 id, u16 value);
void fightTrainerDB_SetName(u16 id, u16 value);
void fightTrainerDB_SetKindDataId(u16 id, u8 value);
void fightTrainerDB_SetTemotiPokemonId(u16 id, u8 index, u16 value);
void fightTrainerDB_SetTemotiItemDataId(u16 id, u8 index, u16 value);
void fightTrainerDB_SetSyoukaiWzxDataId(u16 id, u16 value);
void fightTrainerDB_SetSerihuMsgId(u16 id, u8 index, u16 value);
void fightTrainerDB_SetPkxDataId(u16 id, u16 value);
void fightTrainerPokemonPartDB_SetName(u16 id, u32 value);
void fightTrainerPokemonPartDB_SetWazaTypeRevise(u16 id, u8 index, u8 value);
void fightTrainerPokemonDB_SetNickname(u16 id, u32 value);
void fightTrainerPokemonDB_SetStatusRnd(u16 id, u8 index, u8 value);
void fightTrainerPokemonDB_SetStatusEffort(u16 id, u8 index, u8 value);
void fightTrainerPokemonDB_SetLevel(u16 id, u8 value);
void fightTrainerPokemonDB_SetItemBallId(u16 id, u16 value);
void fightTrainerPokemonDB_SetDarkPokemonFlag(u16 id, u8 value);
void fightTrainerPokemonDB_SetTokuseiFlag(u16 id, u8 value);
void fightTrainerPokemonDB_SetPokemonDataId(u16 id, u16 value);
void fightTrainerPokemonDB_SetItemDataId(u16 id, u16 value);
void fightTrainerPokemonDB_SetWazaDataId(u16 id, u8 index, u16 value);
void fightTrainerPokemonDB_SetPpCnt(u16 id, u8 index, u8 value);
void fightTrainerPokemonDB_SetFriend(u16 id, u8 value);
void fightTrainerPokemonDB_SetSexDataId(u16 id, u8 value);
void fightTrainerPokemonDB_SetSeikakuDataId(u16 id, u8 value);
void fightTrainerPokemonDB_SetKeyPlayerFlag(u16 id, u8 value);
void fightTrainerPokemonDB_SetPartDataId(u16 id, u8 value);
void fightTrainerAiDB_SetPokemonSelectRandomFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetPokemonSelectWeakPointFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetPokemonDataOrderOutFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetPokemonDataOrderAceBossFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetKeyPlayerFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetPokemonJoutaiFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetComboValue(u16 id, u8 value);
void fightTrainerAiDB_SetIrekaeValue(u16 id, u8 value);
void fightTrainerAiDB_SetItemValue(u16 id, u8 value);
void fightTrainerAiDB_SetParamExpectFlag(u16 id, u8 value);
void fightTrainerAiDB_SetParamStoreFlag(u16 id, u8 value);
void fightTrainerAiDB_SetZokuseiCheckFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetTokuseiCheckFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetNokoriHpValue(u16 id, u8 value);
void fightTrainerAiDB_SetWazaDamageFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetAbicntMaxValue(u16 id, u8 value);
void fightTrainerAiDB_SetAbicntMinValue(u16 id, u8 value);
void fightTrainerAiDB_SetDefensePokemonRndSelectFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetWazaRndSelectFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetWazaInitValueFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetPartFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetWazaHitFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetWazaAvgValue(u16 id, u8 value);
void fightTrainerAiDB_SetWazaRiskFlag(u16 id, u8 flag);
void fightTrainerAiDB_SetWazaNokoriPpValue(u16 id, u8 value);
void fightTrainerAiDB_SetLastValueRevise(u16 id, u8 value);
void fightTrainerAiDB_SetZokuseiReviseZokuseiDataId(u16 id, u8 index, u8 value);
void fightTrainerAiDB_SetZokuseiReviseValue(u16 id, u8 index, u8 value);
void fightTrainerAiDB_SetWazaTypeReviseTypeDataId(u16 id, u8 index, u8 value);
void fightTrainerAiDB_SetWazaTypeReviseValue(u16 id, u8 index, u8 value);
void fightTrainerAiValueAddsubDB_SetValue(u16 id, u32 value);
void fightTrainerAiValueAddsubDB_SetName(u16 id, u32 value);
void fightTrainerAiValueAddsubDB_SetKoudouName(u16 id, u32 value);
void fightTrainerAiValueAddsubDB_SetPrefixName(u16 id, u32 value);
void fightTrainer_SetEnemyNowhp1banhikuiFlag(FightTrainer* trainer, s16 id, u8 flag);
void fightTrainer_SetEnemyLv1banhikuiFlag(FightTrainer* trainer, s16 id, u8 flag);
void fightTrainer_SetEnemyDefense1banhikuiFlag(FightTrainer* trainer, s16 id, u8 flag);
void fightTrainer_SetEnemyBadwazaHaveFlag(FightTrainer* trainer, s16 id, u8 flag);
void fightTrainer_SetEnemyParam1bantakaiFlag(FightTrainer* trainer, s16 id, u8 flag);
u8 fightTrainerEnemyPokemonRegistAry(FightTrainerEnemyPokemon* ary, u16 num, s16 id);
u8 fightTrainerEnemyPokemonEraseAry(FightTrainerEnemyPokemon* ary, u16 num, s16 id);
FightTrainerEnemyPokemon* fightTrainerGetFightEntryIdToEnemyPokemonPtr(FightTrainer* trainer, s16 entryId);
u16 fightTrainerDB_GetTemotiPokemonId(u16 id, u8 index);
u16 fightTrainerDB_GetTemotiItemDataId(u16 id, u8 index);
u16 fightTrainerDB_GetSyoukaiWzxDataId(u16 id);
u16 fightTrainerDB_GetSerihuMsgId(u16 id, u8 index);
u32 fightTrainerPokemonPartDB_GetName(u16 id);
u8 fightTrainerPokemonPartDB_GetWazaTypeRevise(u16 id, u8 index);
u32 fightTrainerPokemonDB_GetNickname(u16 id);
u8 fightTrainerPokemonDB_GetStatusRnd(u16 id, u8 index);
u8 fightTrainerPokemonDB_GetStatusEffort(u16 id, u8 index);
u8 fightTrainerPokemonDB_GetLevel(u16 id);
u16 fightTrainerPokemonDB_GetItemBallId(u16 id);
u8 fightTrainerPokemonDB_GetDarkPokemonFlag(u16 id);
u8 fightTrainerPokemonDB_GetTokuseiFlag(u16 id);
u16 fightTrainerPokemonDB_GetPokemonDataId(u16 id);
u16 fightTrainerPokemonDB_GetItemDataId(u16 id);
u16 fightTrainerPokemonDB_GetWazaDataId(u16 id, u8 index);
u8 fightTrainerPokemonDB_GetPpCnt(u16 id, u8 index);
u8 fightTrainerPokemonDB_GetFriend(u16 id);
u8 fightTrainerPokemonDB_GetSexDataId(u16 id);
u8 fightTrainerPokemonDB_GetSeikakuDataId(u16 id);
u8 fightTrainerPokemonDB_GetKeyPlayerFlag(u16 id);
u8 fightTrainerPokemonDB_GetPartDataId(u16 id);
u8 fightTrainerAiDB_GetPokemonSelectRandomFlag(u16 id);
u8 fightTrainerAiDB_GetPokemonSelectWeakPointFlag(u16 id);
u8 fightTrainerAiDB_GetPokemonDataOrderOutFlag(u16 id);
u8 fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(u16 id);
u8 fightTrainerAiDB_GetKeyPlayerFlag(u16 id);
u8 fightTrainerAiDB_GetPokemonJoutaiFlag(u16 id);
u8 fightTrainerAiDB_GetComboValue(u16 id);
u8 fightTrainerAiDB_GetIrekaeValue(u16 id);
u8 fightTrainerAiDB_GetItemValue(u16 id);
u8 fightTrainerAiDB_GetParamExpectFlag(u16 id);
u8 fightTrainerAiDB_GetParamStoreFlag(u16 id);
u8 fightTrainerAiDB_GetZokuseiCheckFlag(u16 id);
u8 fightTrainerAiDB_GetTokuseiCheckFlag(u16 id);
u8 fightTrainerAiDB_GetNokoriHpValue(u16 id);
u8 fightTrainerAiDB_GetWazaDamageFlag(u16 id);
u8 fightTrainerAiDB_GetAbicntMaxValue(u16 id);
u8 fightTrainerAiDB_GetAbicntMinValue(u16 id);
u8 fightTrainerAiDB_GetDefensePokemonRndSelectFlag(u16 id);
u8 fightTrainerAiDB_GetWazaRndSelectFlag(u16 id);
u8 fightTrainerAiDB_GetWazaInitValueFlag(u16 id);
u8 fightTrainerAiDB_GetPartFlag(u16 id);
u8 fightTrainerAiDB_GetWazaHitFlag(u16 id);
u8 fightTrainerAiDB_GetWazaAvgValue(u16 id);
u8 fightTrainerAiDB_GetWazaRiskFlag(u16 id);
u8 fightTrainerAiDB_GetWazaNokoriPpValue(u16 id);
u8 fightTrainerAiDB_GetLastValueRevise(u16 id);
u8 fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(u16 id, u8 index);
u8 fightTrainerAiDB_GetZokuseiReviseValue(u16 id, u8 index);
u8 fightTrainerAiDB_GetWazaTypeReviseTypeDataId(u16 id, u8 index);
u8 fightTrainerAiDB_GetWazaTypeReviseValue(u16 id, u8 index);
u32 fightTrainerAiValueAddsubDB_GetValue(u16 id);
u32 fightTrainerAiValueAddsubDB_GetName(u16 id);
u32 fightTrainerAiValueAddsubDB_GetKoudouName(u16 id);
u32 fightTrainerAiValueAddsubDB_GetPrefixName(u16 id);
u8 fightTrainer_GetOkaneBai(FightTrainer* trainer);
u32 fightTrainer_GetKoban(FightTrainer* trainer);
u8 fightTrainer_GetNigeruCount(FightTrainer* trainer);
u8 fightTrainer_GetEnemyNowhp1banhikuiFlag(FightTrainer* trainer, s16 id);
u8 fightTrainer_GetEnemyLv1banhikuiFlag(FightTrainer* trainer, s16 id);
u8 fightTrainer_GetEnemyDefense1banhikuiFlag(FightTrainer* trainer, s16 id);
u8 fightTrainer_GetEnemyBadwazaHaveFlag(FightTrainer* trainer, s16 id);
u8 fightTrainer_GetEnemyParam1bantakaiFlag(FightTrainer* trainer, s16 id);
void* fightTrainerPokemonPartDataBiosGetPtr(u16 id);
void* fightTrainerAiValueAddsubDataBiosGetPtr(u16 id);
u8 fightFloor_GetFightKind(u32 side);
u16 itemBallDB_GetThrowWzxDataId(u16 ballId);
u16 itemBallDB_GetSnatchAttackWzxDataId(u16 ballId);
u8 pokemon_GetCatchBallId(Pokemon* pokemon);
void battleGridBackupModelVisibilityFlags(void);
void battleGridStoreModelVisibilityFlags(void);
void Sequence_GetPosition(u32 seq, GSvec* pos);
void Sequence_GetRotation(u32 seq, GSvec* rot);
void Sequence_SetPosition(u32 seq, GSvec* pos);
void Sequence_SetRotation(u32 seq, GSvec* rot);
void Sequence_Free(u32 seq);
u32 snatchSequencePtr;

u8 fightTrainerCheckTrainerDataIdValid(u16 id, s32 allowNoAi);
bool fightTrainerCheckValid(FightTrainer* trainer);
u16 fightTrainerGetSelectedItemDataId(FightTrainer* trainer, u16* ids);
FightPokemon* fightTrainerCheckTemotiPokemonFightEntry(FightTrainer* trainer, Pokemon* pokemon);
FightPokemon* fightTrainerGetValidFightPokemonPtr(FightTrainer* trainer, u16 index);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FightTrainer* trainer, u16 index);
u8 fightTrainerCheckCanIrekaeFightPokemon(FightTrainer* trainer, FightPokemon* fp);
u8 fightTrainerCheckIrekaeReserveFightPokemon(FightTrainer* trainer, FightPokemon* fp);
FightOutPokemon* fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(FightTrainer* trainer, FightPokemon* fp);
FightPokemon* fightTrainerSearchIrekaeFightPokemon(FightTrainer* trainer, u16* index);
u8 fightTrainerIsMinePokemon(FightTrainer* trainer, Pokemon* pokemon);
u8 fightTrainerIsGcHero(FightTrainer* trainer);
void fightTrainerInit(FightTrainer* trainer);
void fightTrainerInitFightActionBuff(FightTrainer* trainer);
int fightTrainerGetDoFightOutFightPokemonCount(FightTrainer* trainer);

}

static inline EsabaPokemonTable* _esabaGetPokemonTable(u32 index) {
    if (index >= *esabadata_number) {
        return 0;
    }
    return *esabadata[index].pokemon;
}

extern "C" {

void fightTrainerBallThrowEffect(FightTrainer* trainer, FightOutPokemon* fo, u8 mode) {
    u32 seq = fightTrainer_GetSequencePtr(trainer);
    u16 wzx;
    u32 waza;

    if (seq == 0) {
        return;
    }
    wzx = itemBallDB_GetThrowWzxDataId(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(fo)));
    if (mode == 0) {
        Sequence_LoadWaza(seq, wzx, 4, 0);
    } else if (mode == 1) {
        WazaSequence_Start(Sequence_GetWaza(seq, wzx, 4), 1);
    } else if (mode == 2) {
        waza = Sequence_GetWaza(seq, wzx, 4);
        while (WazaSequence_IsActive(waza)) {
            GSthreadSwitch();
        }
    } else if (mode == 3) {
        WazaSequence_Free(Sequence_GetWaza(seq, wzx, 4));
    }
}

void fightTrainerHokakuThrowEffect(FightTrainer* trainer, u16 ballId, u8 mode) {
    u32 seq = fightTrainer_GetSequencePtr(trainer);
    u32 waza;
    u16 wzx;
    u8 snatch;
    GSvec pos;
    GSvec rot;

    if (seq == 0) {
        return;
    }
    if (fightFloor_GetFightKind(0) == 12 || fightFloor_GetFightKind(0) == 13) {
        wzx = itemBallDB_GetThrowWzxDataId(ballId);
        snatchSequencePtr = seq;
        snatch = 0;
    } else {
        wzx = itemBallDB_GetSnatchAttackWzxDataId(ballId);
        snatch = 1;
    }
    if (mode == 0) {
        if (snatch) {
            snatchSequencePtr = Sequence_LoadTrainer(0x42);
        }
        Sequence_LoadWaza(snatchSequencePtr, wzx, 4, 0);
    } else if (mode == 1) {
        if (snatch) {
            battleGridBackupModelVisibilityFlags();
            Sequence_GetPosition(seq, &pos);
            Sequence_GetRotation(seq, &rot);
            Sequence_SetPosition(snatchSequencePtr, &pos);
            Sequence_SetRotation(snatchSequencePtr, &rot);
            Sequence_SetVisibility(seq, 0);
            battleGridStoreModelVisibilityFlags();
            Sequence_SetVisibility(snatchSequencePtr, 1);
        }
        waza = Sequence_GetWaza(snatchSequencePtr, wzx, 4);
        WazaSequence_Start(waza, 1);
        while (WazaSequence_IsActive(waza)) {
            GSthreadSwitch();
        }
    } else if (mode == 2) {
        WazaSequence_Free(Sequence_GetWaza(snatchSequencePtr, wzx, 4));
        if (snatch) {
            Sequence_SetVisibility(snatchSequencePtr, 0);
            Sequence_Free(snatchSequencePtr);
            Sequence_SetVisibility(seq, 1);
        }
    } else if (mode == 3) {
        Sequence_LoadWaza(seq, 0x57, 4, 0);
    } else if (mode == 4) {
        WazaSequence_Start(Sequence_GetWaza(seq, 0x57, 4), 1);
    } else if (mode == 5) {
        waza = Sequence_GetWaza(seq, 0x57, 4);
        while (WazaSequence_IsActive(waza)) {
            GSthreadSwitch();
        }
    } else if (mode == 6) {
        WazaSequence_Free(Sequence_GetWaza(seq, 0x57, 4));
    }
}

void fightTrainerCallEffect(FightTrainer* trainer, u8 mode) {
    u32 seq = fightTrainer_GetSequencePtr(trainer);
    u32 waza;

    if (seq == 0) {
        return;
    }
    if (mode == 0) {
        Sequence_LoadWaza(seq, 0x57, 4, 0);
    } else if (mode == 1) {
        WazaSequence_Start(Sequence_GetWaza(seq, 0x57, 4), 1);
    } else if (mode == 2) {
        waza = Sequence_GetWaza(seq, 0x57, 4);
        while (WazaSequence_IsActive(waza)) {
            GSthreadSwitch();
        }
    } else if (mode == 3) {
        WazaSequence_Free(Sequence_GetWaza(seq, 0x57, 4));
    }
}

}

static u8 _fightTrainerGetHeroKind(u16 id) {
    u8 kind = fightTrainerDB_GetKindDataId(id);

    if (kind == 1) {
        return 0;
    }
    if (kind == 2 || kind == 3) {
        return 1;
    }
    return 2;
}

extern "C" {

FightTrainerEnemyPokemon* fightTrainerGetFightEntryIdToEnemyPokemonPtr(FightTrainer* trainer, s16 entryId) {
    FightTrainerEnemyPokemon* ary;

    if (entryId < 0) {
        return 0;
    }
    ary = fightTrainer_GetFightTrainerEnemyPokemonAryPtr(trainer, 0);
    if (ary == 0) {
        return 0;
    }
    return fightTrainerEnemyPokemonSearchAry(ary, 12, entryId);
}

u8 fightTrainerIsGcHero(FightTrainer* trainer) {
    return _fightTrainerGetHeroKind(fightTrainer_GetFightTrainerDataId(trainer)) == 0;
}

u32 fightTrainerGetStatus(FightTrainer* trainer, u16 id, u16 kind, u16 arg) {
    void* data = trainer;

    if (kind == 0 || kind >= 0x5b) {
        return 0;
    }
    if (kind < 10) {
        data = fightTrainerDataBiosGetPtr(id);
        if (data == 0) {
            return 0;
        }
    } else if (kind < 13) {
        data = fightTrainerPokemonPartDataBiosGetPtr(id);
        if (data == 0) {
            return 0;
        }
    } else if (kind < 0x1e) {
        data = DeckPokemon::getDeckPokemonObj(id);
        if (data == 0) {
            return 0;
        }
    } else if (kind < 0x3d) {
        data = DeckTrainerAI::getDeckTrainerAIObj(id);
        if (data == 0) {
            return 0;
        }
    } else if (kind < 0x42) {
        data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
        if (data == 0) {
            return 0;
        }
    }
    if (data == 0) {
        return 0;
    }
    switch (kind) {
    case 0x2:
        return fightTrainerDB_GetAiDataId(id);
    case 0x3:
        return fightTrainerDB_GetName(id);
    case 0x4:
        return fightTrainerDB_GetKindDataId(id);
    case 0x5:
        return fightTrainerDB_GetTemotiPokemonId(id, arg);
    case 0x6:
        return fightTrainerDB_GetTemotiItemDataId(id, arg);
    case 0x7:
        return fightTrainerDB_GetSyoukaiWzxDataId(id);
    case 0x8:
        return fightTrainerDB_GetSerihuMsgId(id, arg);
    case 0x9:
        return fightTrainerDB_GetPkxDataId(id);
    case 0xb:
        return fightTrainerPokemonPartDB_GetName(id);
    case 0xc:
        return fightTrainerPokemonPartDB_GetWazaTypeRevise(id, arg);
    case 0xe:
        return fightTrainerPokemonDB_GetNickname(id);
    case 0xf:
        return fightTrainerPokemonDB_GetStatusRnd(id, arg);
    case 0x10:
        return fightTrainerPokemonDB_GetStatusEffort(id, arg);
    case 0x11:
        return fightTrainerPokemonDB_GetLevel(id);
    case 0x12:
        return fightTrainerPokemonDB_GetItemBallId(id);
    case 0x13:
        return fightTrainerPokemonDB_GetDarkPokemonFlag(id);
    case 0x14:
        return fightTrainerPokemonDB_GetTokuseiFlag(id);
    case 0x15:
        return fightTrainerPokemonDB_GetPokemonDataId(id);
    case 0x16:
        return fightTrainerPokemonDB_GetItemDataId(id);
    case 0x17:
        return fightTrainerPokemonDB_GetWazaDataId(id, arg);
    case 0x18:
        return fightTrainerPokemonDB_GetPpCnt(id, arg);
    case 0x19:
        return fightTrainerPokemonDB_GetFriend(id);
    case 0x1a:
        return fightTrainerPokemonDB_GetSexDataId(id);
    case 0x1b:
        return fightTrainerPokemonDB_GetSeikakuDataId(id);
    case 0x1c:
        return fightTrainerPokemonDB_GetKeyPlayerFlag(id);
    case 0x1d:
        return fightTrainerPokemonDB_GetPartDataId(id);
    case 0x1f:
        return fightTrainerAiDB_GetPokemonSelectRandomFlag(id);
    case 0x20:
        return fightTrainerAiDB_GetPokemonSelectWeakPointFlag(id);
    case 0x21:
        return fightTrainerAiDB_GetPokemonDataOrderOutFlag(id);
    case 0x22:
        return fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(id);
    case 0x23:
        return fightTrainerAiDB_GetKeyPlayerFlag(id);
    case 0x24:
        return fightTrainerAiDB_GetPokemonJoutaiFlag(id);
    case 0x25:
        return fightTrainerAiDB_GetComboValue(id);
    case 0x26:
        return fightTrainerAiDB_GetIrekaeValue(id);
    case 0x27:
        return fightTrainerAiDB_GetItemValue(id);
    case 0x28:
        return fightTrainerAiDB_GetParamExpectFlag(id);
    case 0x29:
        return fightTrainerAiDB_GetParamStoreFlag(id);
    case 0x2a:
        return fightTrainerAiDB_GetZokuseiCheckFlag(id);
    case 0x2b:
        return fightTrainerAiDB_GetTokuseiCheckFlag(id);
    case 0x2c:
        return fightTrainerAiDB_GetNokoriHpValue(id);
    case 0x2d:
        return fightTrainerAiDB_GetWazaDamageFlag(id);
    case 0x2e:
        return fightTrainerAiDB_GetAbicntMaxValue(id);
    case 0x2f:
        return fightTrainerAiDB_GetAbicntMinValue(id);
    case 0x30:
        return fightTrainerAiDB_GetDefensePokemonRndSelectFlag(id);
    case 0x31:
        return fightTrainerAiDB_GetWazaRndSelectFlag(id);
    case 0x32:
        return fightTrainerAiDB_GetWazaInitValueFlag(id);
    case 0x33:
        return fightTrainerAiDB_GetPartFlag(id);
    case 0x34:
        return fightTrainerAiDB_GetWazaHitFlag(id);
    case 0x35:
        return fightTrainerAiDB_GetWazaAvgValue(id);
    case 0x36:
        return fightTrainerAiDB_GetWazaRiskFlag(id);
    case 0x37:
        return fightTrainerAiDB_GetWazaNokoriPpValue(id);
    case 0x38:
        return fightTrainerAiDB_GetLastValueRevise(id);
    case 0x39:
        return fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(id, arg);
    case 0x3a:
        return fightTrainerAiDB_GetZokuseiReviseValue(id, arg);
    case 0x3b:
        return fightTrainerAiDB_GetWazaTypeReviseTypeDataId(id, arg);
    case 0x3c:
        return fightTrainerAiDB_GetWazaTypeReviseValue(id, arg);
    case 0x3e:
        return fightTrainerAiValueAddsubDB_GetValue(id);
    case 0x3f:
        return fightTrainerAiValueAddsubDB_GetName(id);
    case 0x40:
        return fightTrainerAiValueAddsubDB_GetKoudouName(id);
    case 0x41:
        return fightTrainerAiValueAddsubDB_GetPrefixName(id);
    case 0x44:
        return (u32)fightTrainer_GetHeroPtr((FightTrainer*)data);
    case 0x43:
        return fightTrainer_GetFightTrainerDataId((FightTrainer*)data);
    case 0x45:
        return (u32)fightTrainer_GetFightPokemonPtr((FightTrainer*)data, arg);
    case 0x46:
        return (u32)fightTrainer_GetFightoutPokemonPtr((FightTrainer*)data, arg);
    case 0x47:
        return (u32)fightTrainer_GetFightoutPokemonBuffPtr((FightTrainer*)data);
    case 0x48:
        return fightTrainer_GetOkaneBai((FightTrainer*)data);
    case 0x49:
        return fightTrainer_GetKoban((FightTrainer*)data);
    case 0x4a:
        return fightTrainer_GetNigeruCount((FightTrainer*)data);
    case 0x4b:
        return fightTrainer_GetControllerId((FightTrainer*)data);
    case 0x4d:
        return (u32)fightTrainer_GetFightActionBuffPtr((FightTrainer*)data);
    case 0x4c:
        return (u32)fightTrainer_GetSequencePtr((FightTrainer*)data);
    case 0x4e:
        return (u32)fightTrainer_GetFightTrainerEnemyPokemonAryPtr((FightTrainer*)data, arg);
    case 0x52:
        return fightTrainer_GetEnemyNowhp1banhikuiFlag((FightTrainer*)data, id);
    case 0x53:
        return fightTrainer_GetEnemyLv1banhikuiFlag((FightTrainer*)data, id);
    case 0x54:
        return fightTrainer_GetEnemyDefense1banhikuiFlag((FightTrainer*)data, id);
    case 0x55:
        return fightTrainer_GetEnemyBadwazaHaveFlag((FightTrainer*)data, id);
    case 0x56:
        return fightTrainer_GetEnemyParam1bantakaiFlag((FightTrainer*)data, id);
    }
    return 0;
}

void fightTrainerSetStatus(FightTrainer* trainer, u16 id, u16 kind, u16 arg, u32 value) {
    void* data = trainer;
    FightTrainerEnemyPokemon* enemy;

    if (kind == 0 || kind >= 0x5b) {
        return;
    }
    if (kind < 10) {
        data = fightTrainerDataBiosGetPtr(id);
        if (data == 0) {
            return;
        }
    } else if (kind < 13) {
        data = fightTrainerPokemonPartDataBiosGetPtr(id);
        if (data == 0) {
            return;
        }
    } else if (kind < 0x1e) {
        data = DeckPokemon::getDeckPokemonObj(id);
        if (data == 0) {
            return;
        }
    } else if (kind < 0x3d) {
        data = DeckTrainerAI::getDeckTrainerAIObj(id);
        if (data == 0) {
            return;
        }
    } else if (kind < 0x42) {
        data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
        if (data == 0) {
            return;
        }
    }
    if (data == 0) {
        return;
    }
    switch (kind) {
    case 0x2:
        fightTrainerDB_SetAiDataId(id, value);
        break;
    case 0x3:
        fightTrainerDB_SetName(id, value);
        break;
    case 0x4:
        fightTrainerDB_SetKindDataId(id, value);
        break;
    case 0x5:
        fightTrainerDB_SetTemotiPokemonId(id, arg, value);
        break;
    case 0x6:
        fightTrainerDB_SetTemotiItemDataId(id, arg, value);
        break;
    case 0x7:
        fightTrainerDB_SetSyoukaiWzxDataId(id, value);
        break;
    case 0x8:
        fightTrainerDB_SetSerihuMsgId(id, arg, value);
        break;
    case 0x9:
        fightTrainerDB_SetPkxDataId(id, value);
        break;
    case 0xb:
        fightTrainerPokemonPartDB_SetName(id, value);
        break;
    case 0xc:
        fightTrainerPokemonPartDB_SetWazaTypeRevise(id, arg, value);
        break;
    case 0xe:
        fightTrainerPokemonDB_SetNickname(id, value);
        break;
    case 0xf:
        fightTrainerPokemonDB_SetStatusRnd(id, arg, value);
        break;
    case 0x10:
        fightTrainerPokemonDB_SetStatusEffort(id, arg, value);
        break;
    case 0x11:
        fightTrainerPokemonDB_SetLevel(id, value);
        break;
    case 0x12:
        fightTrainerPokemonDB_SetItemBallId(id, value);
        break;
    case 0x13:
        fightTrainerPokemonDB_SetDarkPokemonFlag(id, value);
        break;
    case 0x14:
        fightTrainerPokemonDB_SetTokuseiFlag(id, value);
        break;
    case 0x15:
        fightTrainerPokemonDB_SetPokemonDataId(id, value);
        break;
    case 0x16:
        fightTrainerPokemonDB_SetItemDataId(id, value);
        break;
    case 0x17:
        fightTrainerPokemonDB_SetWazaDataId(id, arg, value);
        break;
    case 0x18:
        fightTrainerPokemonDB_SetPpCnt(id, arg, value);
        break;
    case 0x19:
        fightTrainerPokemonDB_SetFriend(id, value);
        break;
    case 0x1a:
        fightTrainerPokemonDB_SetSexDataId(id, value);
        break;
    case 0x1b:
        fightTrainerPokemonDB_SetSeikakuDataId(id, value);
        break;
    case 0x1c:
        fightTrainerPokemonDB_SetKeyPlayerFlag(id, value);
        break;
    case 0x1d:
        fightTrainerPokemonDB_SetPartDataId(id, value);
        break;
    case 0x1f:
        fightTrainerAiDB_SetPokemonSelectRandomFlag(id, (u8)value != 0);
        break;
    case 0x20:
        fightTrainerAiDB_SetPokemonSelectWeakPointFlag(id, (u8)value != 0);
        break;
    case 0x21:
        fightTrainerAiDB_SetPokemonDataOrderOutFlag(id, (u8)value != 0);
        break;
    case 0x22:
        fightTrainerAiDB_SetPokemonDataOrderAceBossFlag(id, (u8)value != 0);
        break;
    case 0x23:
        fightTrainerAiDB_SetKeyPlayerFlag(id, (u8)value != 0);
        break;
    case 0x24:
        fightTrainerAiDB_SetPokemonJoutaiFlag(id, (u8)value != 0);
        break;
    case 0x25:
        fightTrainerAiDB_SetComboValue(id, value);
        break;
    case 0x26:
        fightTrainerAiDB_SetIrekaeValue(id, value);
        break;
    case 0x27:
        fightTrainerAiDB_SetItemValue(id, value);
        break;
    case 0x28:
        fightTrainerAiDB_SetParamExpectFlag(id, value);
        break;
    case 0x29:
        fightTrainerAiDB_SetParamStoreFlag(id, value);
        break;
    case 0x2a:
        fightTrainerAiDB_SetZokuseiCheckFlag(id, (u8)value != 0);
        break;
    case 0x2b:
        fightTrainerAiDB_SetTokuseiCheckFlag(id, (u8)value != 0);
        break;
    case 0x2c:
        fightTrainerAiDB_SetNokoriHpValue(id, value);
        break;
    case 0x2d:
        fightTrainerAiDB_SetWazaDamageFlag(id, (u8)value != 0);
        break;
    case 0x2e:
        fightTrainerAiDB_SetAbicntMaxValue(id, value);
        break;
    case 0x2f:
        fightTrainerAiDB_SetAbicntMinValue(id, value);
        break;
    case 0x30:
        fightTrainerAiDB_SetDefensePokemonRndSelectFlag(id, (u8)value != 0);
        break;
    case 0x31:
        fightTrainerAiDB_SetWazaRndSelectFlag(id, (u8)value != 0);
        break;
    case 0x32:
        fightTrainerAiDB_SetWazaInitValueFlag(id, (u8)value != 0);
        break;
    case 0x33:
        fightTrainerAiDB_SetPartFlag(id, (u8)value != 0);
        break;
    case 0x34:
        fightTrainerAiDB_SetWazaHitFlag(id, (u8)value != 0);
        break;
    case 0x35:
        fightTrainerAiDB_SetWazaAvgValue(id, value);
        break;
    case 0x36:
        fightTrainerAiDB_SetWazaRiskFlag(id, (u8)value != 0);
        break;
    case 0x37:
        fightTrainerAiDB_SetWazaNokoriPpValue(id, value);
        break;
    case 0x38:
        fightTrainerAiDB_SetLastValueRevise(id, value);
        break;
    case 0x39:
        fightTrainerAiDB_SetZokuseiReviseZokuseiDataId(id, arg, value);
        break;
    case 0x3a:
        fightTrainerAiDB_SetZokuseiReviseValue(id, arg, value);
        break;
    case 0x3b:
        fightTrainerAiDB_SetWazaTypeReviseTypeDataId(id, arg, value);
        break;
    case 0x3c:
        fightTrainerAiDB_SetWazaTypeReviseValue(id, arg, value);
        break;
    case 0x3e:
        fightTrainerAiValueAddsubDB_SetValue(id, value);
        break;
    case 0x3f:
        fightTrainerAiValueAddsubDB_SetName(id, value);
        break;
    case 0x40:
        fightTrainerAiValueAddsubDB_SetKoudouName(id, value);
        break;
    case 0x41:
        fightTrainerAiValueAddsubDB_SetPrefixName(id, value);
        break;
    case 0x43:
        fightTrainer_SetFightTrainerDataId((FightTrainer*)data, value);
        break;
    case 0x48:
        fightTrainer_SetOkaneBai((FightTrainer*)data, value);
        break;
    case 0x49:
        fightTrainer_SetKoban((FightTrainer*)data, value);
        break;
    case 0x4a:
        fightTrainer_SetNigeruCount((FightTrainer*)data, value);
        break;
    case 0x4b:
        fightTrainer_SetControllerId((FightTrainer*)data, value);
        break;
    case 0x4c:
        fightTrainer_SetSequencePtr((FightTrainer*)data, value);
        break;
    case 0x52:
        fightTrainer_SetEnemyNowhp1banhikuiFlag((FightTrainer*)data, id, value != 0);
        break;
    case 0x53:
        fightTrainer_SetEnemyLv1banhikuiFlag((FightTrainer*)data, id, value != 0);
        break;
    case 0x54:
        fightTrainer_SetEnemyDefense1banhikuiFlag((FightTrainer*)data, id, value != 0);
        break;
    case 0x55:
        fightTrainer_SetEnemyBadwazaHaveFlag((FightTrainer*)data, id, value != 0);
        break;
    case 0x56:
        fightTrainer_SetEnemyParam1bantakaiFlag((FightTrainer*)data, id, value != 0);
        break;
    case 0x57:
        enemy = fightTrainer_GetFightTrainerEnemyPokemonAryPtr((FightTrainer*)data, 0);
        if (enemy != 0) {
            fightTrainerEnemyPokemonRegistAry(enemy, 12, value);
        }
        break;
    case 0x58:
        enemy = fightTrainer_GetFightTrainerEnemyPokemonAryPtr((FightTrainer*)data, 0);
        if (enemy != 0) {
            fightTrainerEnemyPokemonEraseAry(enemy, 12, value);
        }
        break;
    case 0x59:
        enemy = fightTrainerGetFightEntryIdToEnemyPokemonPtr((FightTrainer*)data, id);
        if (enemy != 0) {
            fightTrainerEnemyPokemonInitFightOutStatus(enemy);
        }
        break;
    }
}

void fightTrainerInitFightActionBuff(FightTrainer* trainer) {
    FightAction* action = fightTrainer_GetFightActionBuffPtr(trainer);

    if (action != 0) {
        fightActionInit(action);
    }
}

void fightTrainerInit(FightTrainer* trainer) {
    if (trainer == 0) {
        return;
    }
    heroInit(fightTrainer_GetHeroPtr(trainer));
    fightTrainer_SetFightTrainerDataId(trainer, 0);
    fightPokemonInitAry(fightTrainer_GetFightPokemonPtr(trainer, 0), 6);
    fightOutPokemonInitAry(fightTrainer_GetFightoutPokemonPtr(trainer, 0), 2);
    fightOutPokemonInit(fightTrainer_GetFightoutPokemonBuffPtr(trainer));
    fightTrainer_SetOkaneBai(trainer, 1);
    fightTrainer_SetKoban(trainer, 0);
    fightTrainer_SetNigeruCount(trainer, 0);
    fightTrainer_SetControllerId(trainer, 0);
    fightTrainer_SetSequencePtr(trainer, 0);
    fightTrainerInitFightActionBuff(trainer);
    fightTrainerEnemyPokemonInitAry(fightTrainer_GetFightTrainerEnemyPokemonAryPtr(trainer, 0), 12);
}

void fightTrainerInitAry(FightTrainer* ary, u16 num) {
    u16 i;

    if (ary == 0) {
        return;
    }
    for (i = 0; i < num; i++) {
        fightTrainerInit(&ary[i]);
    }
}

void fightTrainerCreate(FightTrainer* trainer, Hero* src, u16 id, u32 controllerId, u32 seq) {
    Hero* hero;

    if (trainer == 0) {
        return;
    }
    if (src == 0) {
        return;
    }
    fightTrainerInit(trainer);
    hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == 0) {
        return;
    }
    heroBiosCopy(hero, src);
    fightTrainer_SetFightTrainerDataId(trainer, id);
    fightTrainer_SetControllerId(trainer, controllerId);
    if (seq != 0) {
        fightTrainer_SetSequencePtr(trainer, seq);
        fightFloorSetShadow();
    }
}

bool fightTrainerCheckValid(FightTrainer* trainer) {
    Hero* hero;

    if (trainer == 0) {
        return 0;
    }
    if (fightGetFightResultId() == 1) {
        return 0;
    }
    if (fightTrainer_GetFightTrainerDataId(trainer) == 0) {
        return 0;
    }
    hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == 0) {
        return 0;
    }
    return heroCheckValid(hero) != 0;
}

bool fightTrainerCheckDoFight(FightTrainer* trainer) {
    if (fightTrainerCheckValid(trainer) == 0) {
        return 0;
    }
    return (u8)fightTrainerGetDoFightOutFightPokemonCount(trainer) != 0;
}

u8 fightTrainerCheckTrainerDataIdValid(u16 id, s32 allowNoAi) {
    u16 aiId = fightTrainerDB_GetAiDataId(id);

    if (id == 0) {
        return 0;
    }
    if (aiId == 0 && allowNoAi == 0) {
        return 0;
    }
    return 1;
}

u8 fightTrainerCreateFightTrainerPokemonDataIdToPokemon(u16 id, Pokemon* pokemon, u32 unused, u16 darkId, u16 encountId) {
    enum TsE { TsE0 };
    u16 rndKinds[6] = {0x93, 0x94, 0x95, 0x96, 0x97, 0x98};
    enum TsE sex;
    u8 statusRnd[6];
    u8 statusEffort[6];
    u16 waza[4];
    DeckPokemon* deck;
    u8 darkFlag;
    Hero* save;
    u8 fightKind;
    u16 pokemonId;
    u32 heroRnd;
    u8 level;
    u32 friendLevel;
    u16 effortKinds[6] = {0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92};
    u8 seikaku;
    u8 tokusei;
    u16 item;
    u8 combo;
    u8 i;
    DarkPokemon* dark;
    u32 floorId;
    u8 random;
    u16 total;
    u16 tries;
    u8 j;
    u8 done;
    u16 w;
    u32 rnd;

    deck = DeckPokemon::getDeckPokemonObj(id);
    darkFlag = 0;
    save = (Hero*)savedataGetStatus(0, 2);
    if (encountId == 0) {
        encountId = fightGetFightEncountDataId();
    }
    fightKind = fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(encountId));
    pokemonId = deck->getPokemonID();
    if (pokemonId == 0) {
        return 0;
    }
    random = deck->getRandomSetting() != 0;
    level = deck->getLevel();
    friendLevel = deck->getFriendLevel();
    sex = (enum TsE)(deck->getSex());
    seikaku = deck->getSeikakuID();
    tokusei = deck->getTokuseiFlag();
    item = deck->getHoldItem();
    combo = deck->getComboPartnerAll();
    for (i = 0; i < 6; i++) {
        statusRnd[i] = deck->getStatusRnd(i);
    }
    for (i = 0; i < 6; i++) {
        statusEffort[i] = deck->getStatusEffort(i);
    }
    for (i = 0; i < 4; i++) {
        waza[i] = deck->getWazaID(i);
    }
    pokemonCreate(pokemon, pokemonId, level, gamedataGetStatus(0, 1));
    dark = darkPokemonGetDarkPokemon(darkId);
    if (dark != 0) {
        floorId = dark->getCatchFloorId();
        if (darkPokemonBiosGetFightFlag(darkId) == 1 && floorId != 0xB5) {
            darkFlag = 1;
        } else {
            darkFlag = 0;
        }
    }
    heroRnd = heroBiosGetRnd(save);
    if (darkId != 0 && darkFlag == 1) {
        for (i = 0; i < 6; i++) {
            s32 tmp4 = (u16)darkPokemonBiosGetStatusRnd(darkId, i);
            pokemonSetStatus(pokemon, 0, rndKinds[i], 0, tmp4);
        }
        pokemon_SetRnd(pokemon, darkPokemonBiosGetRnd(darkId));
    }
    if (darkId == 0) {
        pokemon_SetFriend(pokemon, friendLevel);
        if (random == 0) {
            pokemon_SetRnd(pokemon, pokemonCreateRndFit(pokemon, sex, seikaku, 0, heroRnd));
            pokemonSetTokuseiFlag(pokemon, tokusei != 0);
            for (i = 0; i < 6; i++) {
                pokemonSetStatus(pokemon, 0, rndKinds[i], 0, statusRnd[i]);
            }
            for (i = 0; i < 6; i++) {
                pokemonSetStatus(pokemon, 0, effortKinds[i], 0, statusEffort[i]);
            }
        }
        if (random == 1) {
            pokemon_SetRnd(pokemon, pokemonCreateRndFit(pokemon, -1, -1, 0, heroRnd));
            for (i = 0; i < 6; i++) {
                statusEffort[i] = 0;
            }
            tries = 0;
            do {
                total = 0;
                for (j = 0; j < 6; j++) {
                    statusEffort[j] += (u16)HSD_Rand() % 256;
                    total += statusEffort[j];
                }
                if (fightKind == 10 || fightKind == 17) {
                    if (total == 510) {
                        goto apply;
                    }
                    if (total > 490 && total < 530) {
                        done = 0;
                        goto adjust;
                    }
                } else if (total <= 510) {
                    goto apply;
                }
                if (total > 510 && tries < 100) {
                    for (i = 0; i < 6; i++) {
                        statusEffort[i] = 0;
                    }
                }
            } while (tries++ < 100);
            done = 0;
        adjust:
            if (!done) {
                for (;;) {
                    for (i = 0; i < 6; i++) {
                        if (fightKind == 10 || fightKind == 17) {
                            if (total < 510 && statusEffort[i] < 255) {
                                statusEffort[i]++;
                                total++;
                            } else if (total > 510 && statusEffort[i] != 0) {
                                statusEffort[i]--;
                                total--;
                            }
                            if (total == 510) {
                                goto apply;
                            }
                        } else {
                            if (statusEffort[i] != 0) {
                                statusEffort[i]--;
                                total--;
                            }
                            if (total <= 510) {
                                goto apply;
                            }
                        }
                    }
                }
            }
        apply:
            for (i = 0; i < 6; i++) {
                pokemonSetStatus(pokemon, 0, effortKinds[i], 0, statusEffort[i]);
            }
        }
    }
    pokemon_SetComboPartnerAll(pokemon, combo);
    pokemonDoItemSoubi(pokemon, item, 1);
    for (i = 0; i < 4; i++) {
        w = waza[i];
        if (w == 0 && wazaCheckDarkWaza(w) == 1 && w == 0x176 && w == 0x163) {
            pokemonWazaInit(pokemon, (s32)i);
        } else {
            pokemonWazaCreate(pokemon, (u8)i, w);
        }
    }
    if (darkId != 0) {
        pokemonSetDarkPokemonStatus(pokemon, darkId);
        if (darkFlag == 0) {
            rnd = pokemonCreateRndFit(pokemon, -1, -1, 0, heroRnd);
            darkPokemonBiosSetRnd((u16)darkId, rnd);
            pokemon_SetRnd(pokemon, rnd);
            if (dark != 0) {
                dark->setRnd(rnd);
            }
            for (i = 0; i < 6; i++) {
                s32 tmp2 = pokemonGetStatus(pokemon, 0, rndKinds[i], 0);
                darkPokemonBiosSetStatusRnd(darkId, i, tmp2);
            }
        }
    }
    pokemonResetBasisStatus(pokemon);
    return 1;
}

}

static u8 _fightTrainer_GetListUnderTakerDarkPoke(u8* list) {
    u8 count = 0;
    u8 i;
    DarkPokemon* dark;
    DeckDarkPokemon* deckDark;

    for (i = 0; i < 0x80; i++) {
        deckDark = DeckDarkPokemon::getDeckDarkPokemonObj(i);
        dark = darkPokemonGetDarkPokemon(i);
        if (dark->getStatus() != 2) {
            continue;
        }
        if (dark->getSnatchFromWho() != 0) {
            continue;
        }
        if (deckDark->getWorth() == 0) {
            continue;
        }
        if (deckDark->getDeckPokemonID() == 0) {
            continue;
        }
        list[count++] = i;
    }
    return count;
}

static void _fightTrainer_SortUnderTakerDarkPoke(u8* list, u8 count) {
    u8 i;
    u8 j;
    u8 worthI;
    u8 worthJ;
    u32 escapeI;
    u32 escapeJ;
    u8 tmp;

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            worthI = DeckDarkPokemon::getDeckDarkPokemonObj(list[i])->getWorth();
            worthJ = DeckDarkPokemon::getDeckDarkPokemonObj(list[j])->getWorth();
            escapeI = darkPokemonGetDarkPokemon(list[i])->getEscapeTime();
            escapeJ = darkPokemonGetDarkPokemon(list[j])->getEscapeTime();
            if ((u8)((worthI << 16) || escapeI) > (u8)((worthJ << 16) || escapeJ)) {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
    }
}

static void _fightTrainer_GetUnderTakerDarkPoke(u8* list, u8 count, u8 start, Hero* hero, u8 num, u16 encountId) {
    f32 step = 20.0f / count;
    u8 i;
    u8 first = start;
    DeckDarkPokemon* deckDark;
    DarkPokemon* dark;
    f32 limit;
    u8 loops = 0;
    f32 total = 0.0f;
    u16 ballId;
    u16 darkId;
    u8 used[2] = {0, 0};
    Pokemon pokemon;

    do {
        total += step;
        loops++;
        limit = 80.0f - total;
        for (i = 0; i < count; i++) {
            if (limit < (u16)HSD_Rand() % 100) {
                deckDark = DeckDarkPokemon::getDeckDarkPokemonObj(list[i]);
                dark = darkPokemonGetDarkPokemon(list[i]);
                if (used[0] == list[i] || used[1] == list[i]) {
                    continue;
                }
                ballId = fightTrainerPokemonDB_GetItemBallId(deckDark->getDeckPokemonID());
                if (!_fightTrainerCreateDeckPokemon(hero, deckDark->getDeckPokemonID(), dark->getDarkPokemonID(), ballId, &pokemon, start,
                                                    encountId)) {
                    break;
                }
                used[start++ - first] = list[i];
                if (start >= num + 2) {
                    break;
                }
            }
        }
    } while (start < first + num && count >= num && loops <= 100);
}

static void _fightTrainerCreateDeckUnderTaker(u16 id, Hero* hero, u16 encountId) {
    u8 list[0x80];
    Pokemon pokemon;
    u8 i;
    u32 deck;
    u16 trainerId;
    u16 ballId;
    u16 pokemonId;
    u16 darkId;
    u8 count;

    for (i = 0; i < 0x80; i++) {
        list[i] = 0;
    }
    switch (GSflagGet(0x5DC)) {
    case 0:
        switch ((u16)HSD_Rand() % 2) {
        case 0:
            deck = 0x10002;
            break;
        case 1:
            deck = 0x10003;
            break;
        }
        break;
    case 1:
        switch ((u16)HSD_Rand() % 2) {
        case 0:
            deck = 0x10004;
            break;
        case 1:
            deck = 0x10005;
            break;
        }
        break;
    case 2:
        switch ((u16)HSD_Rand() % 2) {
        case 0:
            deck = 0x10006;
            break;
        case 1:
            deck = 0x10007;
            break;
        }
        break;
    }
    trainerId = deck;
    for (i = 0;; i++) {
        pokemonId = fightTrainerDB_GetTemotiPokemonId(trainerId, i);
        darkId = DeckTrainer::getDeckTrainerObj(trainerId)->getDarkPokemonDataID(i);
        ballId = fightTrainerPokemonDB_GetItemBallId(pokemonId);
        if (!_fightTrainerCreateDeckPokemon(hero, pokemonId, darkId, ballId, &pokemon, i,
                                            encountId)) {
            break;
        }
    }
    count = _fightTrainer_GetListUnderTakerDarkPoke(list);
    if (count != 0) {
        _fightTrainer_SortUnderTakerDarkPoke(list, count);
        _fightTrainer_GetUnderTakerDarkPoke(list, count, i, hero, (u32)count > 6 ? 2 : 1, encountId);
    }
}

static void _fightTrainerCreateDeckUnderTakerInColosseum(u16 id, Hero* hero, u16 encountId) {
    u8 list[0x80];
    Pokemon pokemon;
    u32 deck;
    u16 trainerId;
    u16 ballId;
    u8 i;
    u16 pokemonId;
    u16 darkId;
    u8 count;

    if (fightFloor_GetFightFloorDataId(0) == 0x1f) {
        switch (underTakerDeckRand) {
        case 0:
            deck = 0x60001;
            break;
        case 1:
            deck = 0x60002;
            break;
        case 2:
            deck = 0x60003;
            break;
        case 3:
            deck = 0x60004;
            break;
        }
    } else if (fightFloor_GetFightFloorDataId(0) == 0x21) {
        switch (underTakerDeckRand) {
        case 0:
            deck = 0x60005;
            break;
        case 1:
            deck = 0x60006;
            break;
        case 2:
            deck = 0x60007;
            break;
        case 3:
            deck = 0x60008;
            break;
        }
    }
    trainerId = deck;
    for (i = 0;; i++) {
        pokemonId = fightTrainerDB_GetTemotiPokemonId(trainerId, i);
        darkId = DeckTrainer::getDeckTrainerObj(trainerId)->getDarkPokemonDataID(i);
        ballId = fightTrainerPokemonDB_GetItemBallId(pokemonId);
        if (!_fightTrainerCreateDeckPokemon(hero, pokemonId, darkId, ballId, &pokemon, i,
                                            encountId)) {
            break;
        }
    }
    fightFreeResourceID(0x842, 0x184C3400);
    fightReadResourceID(0x842, 0x18503400);
    count = _fightTrainer_GetListUnderTakerDarkPoke(list);
    if (count != 0) {
        _fightTrainer_SortUnderTakerDarkPoke(list, count);
        _fightTrainer_GetUnderTakerDarkPoke(list, count, i, hero, 1, encountId);
    }
    fightFreeResourceID(0x842, 0x18503400);
    fightReadResourceID(0x842, 0x184C3400);
}

static void _fightTrainerCreateDeckBingo(u16 id, Hero* hero) {
    u16 trainerPokemonId;
    u8 i;
    u8 index;
    BINGO_DATA_dd_* sheet;
    u8 hoseiKind;
    u8 level;
    u32 rnd;
    u16 no;
    Pokemon pokemon;
    u16 waza;
    u8 tokusei;
    u8 hoseiVal;
    u32 pokemonRnd;
    u8 sex;
    u8 seikaku;
    u16 hosei;

    trainerPokemonId = fightTrainerDB_GetTemotiPokemonId(id, 0);
    rnd = heroGetStatus(hero, 2, 0);
    u16 effortKinds[6] = {0x93, 0x94, 0x95, 0x96, 0x97, 0x98};
    u16 hoseiKinds[7] = {0, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92};

    sheet = bingo_bios::getStaticSheet();
    if (sheet == 0) {
        return;
    }
    if (id == 5000) {
        index = bingo_bios::getStaticIdx(0);
    } else {
        index = bingo_bios::getStaticIdx(1);
    }
    level = sheet->level;
    no = sheet->panel[index].no;
    sex = sheet->panel[index].sex;
    seikaku = sheet->panel[index].seikaku;
    waza = sheet->panel[index].waza;
    tokusei = sheet->panel[index].tokusei;
    hosei = sheet->panel[index].hosei;
    hoseiKind = bingo_bios::getPanelHoseiKind(sheet, index);
    hoseiVal = bingo_bios::getPanelHoseiVal(sheet, index);
    pokemonCreate(&pokemon, no, level, gamedataGetStatus(0, 1));
    pokemonSetTokuseiFlag(&pokemon, tokusei != 0);
    pokemonRnd = pokemonCreateRndFit(&pokemon, sex, seikaku, 0, rnd);
    pokemon_SetRnd(&pokemon, pokemonRnd);
    for (i = 0; i < 4; i++) {
        pokemonWazaInit(&pokemon, i);
    }
    pokemonWazaCreate(&pokemon, 0, waza);
    if (hosei != 0) {
        pokemonSetStatus(&pokemon, 0, hoseiKinds[hoseiKind], 0, hoseiVal);
    }
    for (i = 0; i < 6; i++) {
        pokemonSetStatus(&pokemon, 0, effortKinds[i], 0, 16);
    }
    pokemonResetBasisStatus(&pokemon);
    deckCreate(trainerPokemonId, no, &pokemon);
    pokemon_SetFightTrainerPokemonDataId(&pokemon, trainerPokemonId);
    if (heroCatchPokemon(hero, &pokemon, 0, 1, 0) < 0) {
        return;
    }
}

static void _fightTrainerCreateDeckVirtual(u16 id, Hero* hero, u16 encountId) {
    u16 trainerId;
    u32 deck;
    u8 i;
    Pokemon pokemon;
    u16 pokemonId;
    void* encount;
    u16 darkId;
    u16 disk;
    u16 ballId;

    if (encountId == 0) {
        encountId = fightGetFightEncountDataId();
    }
    encount = fightEncountDataBiosGetPtr(encountId);
    disk = fightEncountDataBiosGetDiskId(encount);
    if (_fightTrainerGetHeroKind(id) == 0) {
        deck = deckDataVirtualDB_GetAllyDeck(disk);
        fightEncountDataBiosSetFightTrainerDataId(encount, 0, deck);
    } else {
        deck = deckDataVirtualDB_GetEnemyDeck(disk);
        fightEncountDataBiosSetFightTrainerDataId(encount, 1, deck);
    }
    fightEncountDataBiosSetPokemon(encount, deckDataVirtualDB_GetPokemonNum(disk));
    trainerId = deck;
    for (i = 0;; i++) {
        pokemonId = fightTrainerDB_GetTemotiPokemonId(trainerId, i);
        darkId = DeckTrainer::getDeckTrainerObj(trainerId)->getDarkPokemonDataID(i);
        ballId = fightTrainerPokemonDB_GetItemBallId(pokemonId);
        if (!_fightTrainerCreateDeckPokemon(hero, pokemonId, darkId, ballId, &pokemon, i,
                                            encountId)) {
            break;
        }
    }
}

static void _fightTrainerCreateDeckWildPoke(u16 id, Hero* hero) {
    u16 trainerPokemonId;
    u8 itemRnd = (u16)HSD_Rand() % 100;
    u16 floorId = fightFloor_GetFightFloorDataId(0);
    u8 slot;
    u16 pokemonId;
    u32 rnd;
    s32 esabaIndex;
    u8 k;
    EsabaPokemonTable* table;
    u32 maxLevel;
    u8 minLevel;
    u32 levelRnd;
    Pokemon pokemon;
    u16 item0;
    u16 item1;

    s32 tmp1 = heroGetStatus(0, 2, 0);

    heroBiosSetRnd(hero, tmp1);
    switch (floorId) {
    case 0x39:
        esabaIndex = 0;
        break;
    case 0x3a:
        esabaIndex = 1;
        break;
    case 0x3b:
        esabaIndex = 2;
        break;
    }
    pokemonId = esabaGetPokemonID(esabaIndex);
    rnd = esabaGetPokemonRnd(esabaIndex);
    if (pokemonId == 0) {
        switch (floorId) {
        case 0x39:
            pokemonId = 0x1b;
            break;
        case 0x3a:
            pokemonId = 0xbb;
            break;
        case 0x3b:
            pokemonId = 0x4a;
            break;
        }
    }
    for (k = 0; k < 3; k++) {
        table = _esabaGetPokemonTable(esabaIndex);
        if (pokemonId == (table != 0 ? table->data[k].pokemonId : 0)) {
            slot = k;
            break;
        }
    }
    table = _esabaGetPokemonTable(esabaIndex);
    maxLevel = table != 0 ? table->data[slot].maxLevel : 0;
    table = _esabaGetPokemonTable(esabaIndex);
    minLevel = table != 0 ? table->data[slot].minLevel : 0;
    levelRnd = HSD_Rand();
    trainerPokemonId = fightTrainerDB_GetTemotiPokemonId(id, 0);
    DeckTrainer::getDeckTrainerObj(id)->getDarkPokemonDataID(0);
    pokemonCreate(&pokemon, pokemonId, minLevel + levelRnd % (maxLevel - minLevel + 1), gamedataGetStatus(0, 1));
    if (rnd != 0) {
        pokemon.setRnd(rnd);
        pokemonResetBasisStatus(&pokemon);
    }
    item0 = pokemonDB_GetItemDataId(pokemonId, 0);
    item1 = pokemonDB_GetItemDataId(pokemonId, 1);
    if (item0 == item1) {
        pokemon.setItemDataId(item0);
    } else if (itemRnd >= 45) {
        if (itemRnd < 95) {
            pokemon.setItemDataId(item0);
        } else {
            pokemon.setItemDataId(item1);
        }
    }
    deckCreate(trainerPokemonId, pokemonId, &pokemon);
    pokemon_SetFightTrainerPokemonDataId(&pokemon, trainerPokemonId);
    heroCatchPokemon(hero, &pokemon, 0, 0, 0);
}

static void _fightTrainerCreateDeckNormal(u16 id, Hero* hero, u16 encountId) {
    u8 j;
    u16 darkId;
    u8 hasDark;
    u16 ballId;
    u16 swapDeck;
    DarkPokemon* dark;
    Pokemon pokemon;
    u16 swapId;
    u8 i;
    u16 pokemonId;
    FIGHT_ENCOUNT* encount;
    u32 swapMode;

    hasDark = 0;
    encount = fightEncountGetStrObj();
    swapMode = encount->getSwapMode();
    swapDeck = encount->getSwapDeckNO();
    for (i = 0; i < 6; i++) {
        fightTrainerDB_GetTemotiPokemonId(id, i);
        dark = darkPokemonGetDarkPokemon(DeckTrainer::getDeckTrainerObj(id)->getDarkPokemonDataID(i));
        if (dark != 0 && dark->getStatus() >= 2) {
            hasDark = 1;
            break;
        }
    }
    swapId = swapDeck;
    for (j = 0;; j++) {
        if (swapMode == 2 && hasDark == 1) {
            pokemonId = fightTrainerDB_GetTemotiPokemonId((u16)swapId, j);
            darkId = DeckTrainer::getDeckTrainerObj(swapId)->getDarkPokemonDataID(j);
        } else {
            pokemonId = fightTrainerDB_GetTemotiPokemonId(id, j);
            darkId = DeckTrainer::getDeckTrainerObj(id)->getDarkPokemonDataID(j);
        }
        ballId = fightTrainerPokemonDB_GetItemBallId(pokemonId);
        if (!_fightTrainerCreateDeckPokemon(hero, pokemonId, darkId, ballId, &pokemon, j, encountId)) {
            break;
        }
    }
}

static bool _fightTrainerCreateDeckPokemon(Hero* hero, u16 pokemonId, u16 darkId, u16 ballId, Pokemon* pokemon, u8 index,
                                           u16 encountId) {
    u16 swapDeck;
    DarkPokemon* dark;
    u8 addId;
    u32 fightMode;
    u32 swapMode;
    u8 addPlace;
    FIGHT_ENCOUNT* encount;
    u32 addMode;

    dark = darkPokemonGetDarkPokemon(darkId);
    encount = fightEncountGetStrObj();
    fightMode = encount->getFightMode();
    addMode = encount->getAddMode();
    addPlace = encount->getAddPlace();
    addId = encount->getAddID();
    swapMode = encount->getSwapMode();
    swapDeck = encount->getSwapDeckNO();

    if (dark != 0 && dark->getStatus() >= 2) {
        if (fightMode == 1) {
            return true;
        }
        if (swapMode == 1) {
            darkId = swapDeck;
            if (darkId == 0) {
                return true;
            }
            pokemonId = fightTrainerDB_GetTemotiPokemonId(darkId, index);
            darkId = DeckTrainer::getDeckTrainerObj(darkId)->getDarkPokemonDataID(0);
        }
    }
    if (addMode == 1 && addPlace == index) {
        u8 deckId = addId;
        DeckDarkPokemon* deckDark = DeckDarkPokemon::getDeckDarkPokemonObj(deckId);
        DarkPokemon* addDark = darkPokemonGetDarkPokemon(deckId);
        pokemonId = deckDark->getDeckPokemonID();
        darkId = addDark->getDarkPokemonID();
    } else if (addMode == 2 && addPlace == index) {
        u8 deckId = addId;
        DeckDarkPokemon* deckDark = DeckDarkPokemon::getDeckDarkPokemonObj(deckId);
        DarkPokemon* addDark = darkPokemonGetDarkPokemon(deckId);
        pokemonId = deckDark->getDeckPokemonID();
        darkId = addDark->getDarkPokemonID();
    }
    if (!fightTrainerCreateFightTrainerPokemonDataIdToPokemon(pokemonId, pokemon, heroGetStatus(hero, 2, 0), darkId, encountId)) {
        return false;
    }
    deckCreate(pokemonId, DeckPokemon::getDeckPokemonObj(pokemonId)->getPokemonID(), pokemon);
    pokemon_SetFightTrainerPokemonDataId(pokemon, pokemonId);
    return heroCatchPokemon(hero, pokemon, 0, ballId, 0) >= 0;
}

static void _fightTrainerCreateRndCheckRare(Hero* hero, bool rare) {
    u16 retry = 10000;
    Pokemon* p;
    u8 i;
    Pokemon * *new_var;
    u32 rnd;
    u32 pokemonRnd;
    u8 j;
    Pokemon* party[6];
    u8 found;

    for (i = 0; i < 6; i++) {
        party[i] = 0;
    }
    rnd = heroGetStatus(hero, 2, 0);
    for (;;) {
        found = 0;
        for (j = 0; j < 6; j++) {
            party[j] = heroBiosGetPokemonPtr(hero, j);
            p = party[j];
            if (p == 0) {
                continue;
            }
            if (pokemon_GetPokemonDataId(p) == 0) {
                continue;
            }
            pokemonRnd = pokemon_GetRnd(p);
            if (pokemonRnd == 0) {
                continue;
            }
            if ((rare != pokemonCheckRareRnd(rnd, pokemonRnd)) != 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            break;
        }
        rnd = heroCreateRnd();
        if ((--retry) == 0) {
            rnd = heroGetStatus(0, 2, 0);
            break;
        }
    }
    heroSetStatus(hero, 2, rnd);
    new_var = party;
    for (i = 0; i < 6; i++) {
        party[i] = heroBiosGetPokemonPtr(hero, i);
        if (party[i] != 0) {
            pokemon_SetCatchTrainerRnd(new_var[i], rnd);
        }
    }
}

extern "C" {

void fightTrainerCreateFightTrainerDataIdToHero(u16 id, s32 allowNoAi, Hero* hero, u16 encountId_in) {
    u8 i;
    Hero* player;
    u32 num;
    u8 fightKind;
    u32 sex;
    u8 maxLevel;
    u16 item;
    u16 disk;
    Pokemon* p;
    u16 encountId = encountId_in;

    if (encountId == 0) {
        encountId = fightGetFightEncountDataId();
    }
    fightKind = fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr((u8)encountId));
    if (hero == 0) {
        return;
    }
    if (!fightTrainerCheckTrainerDataIdValid(id, allowNoAi)) {
        return;
    }
    player = (Hero*)savedataGetStatus(0, 2);
    if (player != 0) {
        maxLevel = 0;
        for (i = 0; i < 6; i++) {
            u8 level = pokemon_GetLevel(heroBiosGetPokemonPtr(player, i));
            if (maxLevel < level) {
                maxLevel = level;
            }
        }
    }
    if (_fightTrainerGetHeroKind(id) == 0) {
        if (player == 0) {
            return;
        }
        if (fightKind == 13) {
            heroCreate(hero, heroBiosGetNamePtr(player), 0);
            _fightTrainerCreateDeckBingo(id, hero);
            _fightTrainerCreateRndCheckRare(hero, false);
        } else if (fightKind == 15 || fightKind == 14) {
            heroCreate(hero, heroBiosGetNamePtr(player), 0);
            _fightTrainerCreateDeckVirtual(id, hero, encountId);
            disk = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(encountId));
            for (i = 0; i < 4; i++) {
                item = deckDataVirtualDB_GetItemID(disk, i);
                if (item == 0) {
                    continue;
                }
                num = deckDataVirtualDB_GetItemNum(disk, i);
                if (num == 0) {
                    continue;
                }
                if (heroItemAddItemDataId(hero, item, num, -1) < 0) {
                    return;
                }
            }
        } else {
            heroBiosCopy(hero, player);
        }
        return;
    }
    _fightTrainerGetHeroKind(id);
    sex = fightTrainerDB_GetSexDataId(id);
    heroCreate(hero, GSmsgGetGSchar(fightTrainerDB_GetName(id)), sex);
    if (encountId == 0x73) {
        _fightTrainerCreateDeckUnderTakerInColosseum(id, hero, encountId);
        _fightTrainerCreateRndCheckRare(hero, false);
    } else if (fightKind == 16) {
        _fightTrainerCreateDeckUnderTaker(id, hero, encountId);
        _fightTrainerCreateRndCheckRare(hero, false);
    } else if (fightKind == 13) {
        _fightTrainerCreateDeckBingo(id, hero);
        _fightTrainerCreateRndCheckRare(hero, false);
    } else if (fightKind == 12) {
        _fightTrainerCreateDeckWildPoke(id, hero);
    } else if (fightKind == 15 || fightKind == 14) {
        _fightTrainerCreateDeckVirtual(id, hero, encountId);
        _fightTrainerCreateRndCheckRare(hero, false);
    } else if (fightKind == 6 || fightKind == 7) {
        _fightTrainerCreateDeckNormal(id, hero, encountId);
        _fightTrainerCreateRndCheckRare(hero, false);
        if (maxLevel > 60) {
            for (i = 0; i < 6; i++) {
                p = heroBiosGetPokemonPtr(hero, i);
                if (p != 0) {
                    pokemon_SetLevel(p, maxLevel);
                    s32 tmp1 = pokemonGetLevelToExp(p, maxLevel);
                    pokemon_SetExp(p, tmp1);
                    pokemonResetBasisStatus(p);
                }
            }
        }
    } else {
        _fightTrainerCreateDeckNormal(id, hero, encountId);
        _fightTrainerCreateRndCheckRare(hero, false);
    }
    if (fightKind == 15 || fightKind == 14) {
        disk = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(encountId));
        for (i = 0; i < 4; i++) {
            item = deckDataVirtualDB_GetItemID(disk, i);
            if (item == 0) {
                continue;
            }
            num = deckDataVirtualDB_GetItemNum(disk, i);
            if (num == 0) {
                continue;
            }
            if (heroItemAddItemDataId(hero, item, num, -1) < 0) {
                break;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            item = fightTrainerDB_GetTemotiItemDataId(id, i);
            if (item == 0) {
                continue;
            }
            if (heroItemAddItemDataId(hero, item, 1, -1) < 0) {
                break;
            }
        }
    }
    heroSetStatus(hero, 0xf, 0);
    heroSetStatus(hero, 0x10, 0);
    heroSetStatus(hero, 0x11, 0);
    heroSetStatus(hero, 0x12, 0);
    heroSetStatus(hero, 0x13, 0);
    heroSetStatus(hero, 0x14, 0);
    heroSetStatus(hero, 0x15, 0);
    heroSetStatus(hero, 0x16, 0);
}

void fightTrainerSortFightTrainerDataIdToHeroTemotiPokemon(FightTrainer* trainer, u16 num, u32 mode) {
    Pokemon* ary[6];
    Pokemon pokemon[6];
    u16 swapDeck;
    u16 id;
    u16 aiId;
    Hero* hero;
    u8 i;
    u8 count;
    Pokemon* p;

    swapDeck = fightEncountGetStrObj()->getSwapDeckNO();
    if (trainer == 0) {
        return;
    }
    if (fightTrainerCheckValid(trainer) == 0) {
        return;
    }
    id = fightTrainer_GetFightTrainerDataId(trainer);
    aiId = fightTrainerDB_GetAiDataId(id);
    hero = fightTrainer_GetHeroPtr(trainer);
    if (aiId == 0) {
        return;
    }
    if (_fightTrainerGetHeroKind(id) == 0 || _fightTrainerGetHeroKind(id) == 1) {
        return;
    }
    if (swapDeck != 0 && fightTrainerAiDB_GetPokemonDataOrderOutFlag(aiId) == 1) {
        return;
    }
    for (i = 0; i < 6; i++) {
        ary[i] = 0;
        pokemonInit(&pokemon[i]);
    }
    if (num > 6) {
        num = 6;
    }
    fightTrainerAiSortFirstSelectPokemonAry(trainer, hero, ary, num, mode);
    count = 0;
    for (i = 0; i < num; i++) {
        p = ary[i];
        if (p != 0 && pokemonCheckValid(p)) {
            memcpy(&pokemon[count], p, sizeof(Pokemon));
            count++;
        }
    }
    for (i = 0; i < 6; i++) {
        p = (Pokemon*)heroGetStatus(hero, 3, i);
        if (p != 0) {
            memcpy(p, &pokemon[i], sizeof(Pokemon));
        }
    }
}

FightPokemon* fightTrainerCheckTemotiPokemonFightEntry(FightTrainer* trainer, Pokemon* pokemon) {
    u16 i;
    FightPokemon* fp;
    Pokemon* moto;

    for (i = 0; i < 6; i++) {
        fp = fightTrainer_GetFightPokemonPtr(trainer, i);
        if (!fightPokemonCheckValid(fp)) {
            continue;
        }
        moto = fightPokemon_GetMotoPokemonPtr(fp);
        if (moto != 0 && pokemon == moto) {
            return fp;
        }
    }
    return 0;
}

int fightTrainerGetDoFightOutFightPokemonCount(FightTrainer* trainer) {
    u8 i;
    int count = 0;

    for (i = 0; i < 6; i++) {
        if (fightPokemonCheckFightOut(fightTrainer_GetFightPokemonPtr(trainer, i))) {
            count++;
        }
    }
    return count;
}

int fightTrainerGetDoFightOutFightOutPokemonCount(FightTrainer* trainer) {
    u8 i;
    int count = 0;

    for (i = 0; i < 2; i++) {
        if (fightOutPokemonCheckFightOut(fightTrainer_GetFightoutPokemonPtr(trainer, i))) {
            count++;
        }
    }
    return count;
}

FightPokemon* fightTrainerGetValidFightPokemonPtr(FightTrainer* trainer, u16 index) {
    FightPokemon* fp = fightTrainer_GetFightPokemonPtr(trainer, index);

    if (fightPokemonCheckValid(fp) == 0) {
        return 0;
    }
    return fp;
}

FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FightTrainer* trainer, u16 index) {
    FightOutPokemon* fo = fightTrainer_GetFightoutPokemonPtr(trainer, index);

    if (fightOutPokemonCheckValid(fo) == 0) {
        return 0;
    }
    return fo;
}

void fightTrainerAllInitFightActionBuff(FightTrainer* trainer) {
    u16 i;

    fightTrainerInitFightActionBuff(trainer);
    for (i = 0; i < 2; i++) {
        fightOutPokemonInitFightActionBuff(fightTrainer_GetFightoutPokemonPtr(trainer, i));
    }
    fightOutPokemonInitFightActionBuff(fightTrainer_GetFightoutPokemonBuffPtr(trainer));
}

s16 fightTrainerSelectIrekaeFightPokemon(FightTrainer* trainer, u32 a, u32 b, u32 c) {
    u16 aiId;
    u16 id;
    s16 result;
    int controllerId;

    result = -1;
    id = fightTrainer_GetFightTrainerDataId(trainer);
    aiId = fightTrainerDB_GetAiDataId(id);
    if (dbgMenuFightGetAllFightTrainerOperateFlag() == 1) {
        result = fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(trainer, 0, a, b, 0);
    } else {
        controllerId = fightTrainer_GetControllerId(trainer);
        if (aiId != 0 && controllerId == 0) {
            result = fightTrainerAiSelectIrekaeDasuFightPokemon(trainer, a, b, c);
        } else if (_fightTrainerGetHeroKind(id) == 0) {
            result = fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(trainer, 0, a, b, 0);
        } else if (_fightTrainerGetHeroKind(id) == 1) {
            result = fightMenuFightTrainerAgbHeroSelectIrekaeFightPokemon(trainer, a, b, c);
        }
    }
    return result;
}

s16 fightTrainerTimeOutSelectIrekaeFightPokemon(FightTrainer* trainer) {
    u16 index = 0;
    FightPokemon* fp = fightTrainerSearchIrekaeFightPokemon(trainer, &index);

    if (fp != 0) {
        return fightPokemon_GetEntryId(fp);
    }
    return -1;
}

u8 fightTrainerSelectFightAction(FightTrainer* trainer, u32 side) {
    u16 aiId;
    u16 id;
    int controllerId;

    fightTrainerAllInitFightActionBuff(trainer);
    if (fightGetFightResultId() == 1) {
        return 0;
    }
    id = fightTrainer_GetFightTrainerDataId(trainer);
    aiId = fightTrainerDB_GetAiDataId(id);
    controllerId = fightTrainer_GetControllerId(trainer);
    if (aiId != 0 && controllerId == 0) {
        fightTrainerAiSelectFightAction(trainer, side);
    } else if (_fightTrainerGetHeroKind(id) == 0) {
        fightMenuFightTrainerGcHeroOpenMenu(trainer, side, 0);
    } else if (_fightTrainerGetHeroKind(id) == 1) {
        if (!fightMenuFightTrainerAgbHeroOpenMenu(trainer, side)) {
            return 0;
        }
    } else {
        fightMenuFightTrainerGcHeroOpenMenu(trainer, side, 0);
    }
    return 1;
}

void fightTrainerTimeOutSelectFightAction(FightTrainer* trainer, FightOutPokemon* fo, u32 side) {
    u16 waza;
    s8 i;
    void* target;

    if (fightOutPokemonCheckFightActionWazaSelect(fo, 1)) {
        return;
    }
    for (i = 0; i < 4; i++) {
        waza = pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(fo), 0);
        if (!fightOutPokemonCheckCanOutOkWazaBanme(fo, i, 1, 0)) {
            waza = pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(fo), i);
            break;
        }
    }
    target = fightSeqSelectDefensePokemonPtr(fo, waza, side, 0, 1, 0, -1);
    fightOutPokemonCreateFightActionAttackWaza(fo, 0, 0x13, 0, &fight_action_data_waza, waza,
                                               fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, side), i, 0);
}

u8 fightTrainerIsMinePokemon(FightTrainer* trainer, Pokemon* pokemon) {
    Hero* hero = fightTrainer_GetHeroPtr(trainer);

    if (hero == 0) {
        return 0;
    }
    return heroIsMinePokemon(hero, pokemon);
}

u8 fightTrainerIsMineFightPokemon(FightTrainer* trainer, FightPokemon* fp) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(fp);

    if (pokemon == 0) {
        return 0;
    }
    return fightTrainerIsMinePokemon(trainer, pokemon);
}

u8 fightTrainerCheckCanGetExp(FightTrainer* trainer) {
    return fightTrainerIsGcHero(trainer) == 1;
}

u32 fightTrainerCreateSequence(u16 id) {
    u32 seq = Sequence_LoadTrainer(fightTrainerDB_GetPkxDataId(id));

    if (seq == 0) {
        return 0;
    }
    Sequence_SetVisibility(seq, 0);
    return seq;
}

FightPokemon* fightTrainerGetEntryIdToFightPokemonPtr(FightTrainer* trainer, s16 entryId) {
    u16 i;
    FightPokemon* fp;

    if (entryId < 0) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        fp = fightTrainerGetValidFightPokemonPtr(trainer, i);
        if (fp != 0 && entryId == fightPokemon_GetEntryId(fp)) {
            return fp;
        }
    }
    return 0;
}

FightOutPokemon* fightTrainerCheckFightPokemonFightOut(FightTrainer* trainer, FightPokemon* fp) {
    FightOutPokemon* fo;

    if (trainer == 0) {
        return 0;
    }
    if (fp == 0) {
        return 0;
    }
    fo = fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(trainer, fp);
    if (fo != 0 && !fightOutPokemonCheckFightOut(fo)) {
        fo = 0;
    }
    return fo;
}

FightOutPokemon* fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(FightTrainer* trainer, FightPokemon* fp) {
    u16 i;
    FightOutPokemon* fo;

    if (trainer == 0) {
        return 0;
    }
    if (fp == 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        fo = fightTrainerGetValidFightOutPokemonPtr(trainer, i);
        if (fo != 0 && fightPokemonCheckMotoFightPokemon(fp, fo) == 1) {
            return fo;
        }
    }
    return 0;
}

u8 fightTrainerCheckIrekaeReserveFightPokemon(FightTrainer* trainer, FightPokemon* fp) {
    u16 i;
    FightOutPokemon* fo;

    if (trainer == 0) {
        return 0;
    }
    if (fp == 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        fo = fightTrainerGetValidFightOutPokemonPtr(trainer, i);
        if (fo != 0 && fightOutPokemonCheckIrekaeReserveFightPokemon(fo, fp) == 1) {
            return 1;
        }
    }
    return 0;
}

u8 fightTrainerCheckCanIrekaeFightPokemon(FightTrainer* trainer, FightPokemon* fp) {
    if (!fightPokemonCheckFightOut(fp)) {
        return 1;
    }
    if (fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(trainer, fp) != 0) {
        return 2;
    }
    return fightTrainerCheckIrekaeReserveFightPokemon(trainer, fp) == 1 ? (u8)3 : (u8)0;
}

FightPokemon* fightTrainerSearchIrekaeFightPokemon(FightTrainer* trainer, u16* index) {
    FightPokemon* fp;

    if (trainer == 0) {
        return 0;
    }
    if (index == 0) {
        return 0;
    }
    for (; *index < 6; (*index)++) {
        fp = fightTrainer_GetFightPokemonPtr(trainer, *index);
        if (!fightTrainerCheckCanIrekaeFightPokemon(trainer, fp)) {
            break;
        }
    }
    if (*index >= 6) {
        return 0;
    }
    return fp;
}

u16 fightTrainerGetIrekaeFightPokemonAry(FightTrainer* trainer, FightPokemon** ary) {
    u16 index;
    u16 count;
    FightPokemon* fp;

    for (index = 0; index < 6; index++) {
        ary[index] = 0;
    }
    count = 0;
    index = 0;
    for (;;) {
        fp = fightTrainerSearchIrekaeFightPokemon(trainer, &index);
        if (fp == 0) {
            break;
        }
        ary[count++] = fp;
        index++;
    }
    return count;
}

void fightTrainerBackFightPokemonToTemotiPokemon(FightTrainer* trainer, u8 restoreItem) {
    u16 i;
    FightPokemon* fp;
    Pokemon* buff;
    u16 item;
    Pokemon* moto;

    if (trainer == 0) {
        return;
    }
    for (i = 0; i < 6; i++) {
        fp = fightTrainerGetValidFightPokemonPtr(trainer, i);
        if (fp == 0) {
            continue;
        }
        buff = fightPokemon_GetPokemonBuffPtr(fp);
        if (buff == 0) {
            continue;
        }
        item = pokemonGetSoubiItemDataId(buff);
        moto = fightPokemon_GetMotoPokemonPtr(fp);
        if (moto == 0) {
            continue;
        }
        pokemonBiosCopy(moto, buff);
        if (pokemonIsJoutaiDataId(moto, 4) == 1) {
            pokemonSetCountAsJoutaiDataId(moto, 4, 1);
        }
        if (restoreItem == 1) {
            pokemon_SetItemDataId(moto, item);
        }
    }
}

s16 fightTrainerGetFightPokemonToTemotiBanme(FightTrainer* trainer, FightPokemon* fp) {
    s16 i;

    if (trainer == 0) {
        return -1;
    }
    if (fp == 0) {
        return -1;
    }
    for (i = 0; i < 6; i++) {
        if (fp == fightTrainer_GetFightPokemonPtr(trainer, i)) {
            return i;
        }
    }
    return -1;
}

s16 fightTrainerGetFightOutPokemonToTemotiBanme(FightTrainer* trainer, FightOutPokemon* fo) {
    s16 i;

    if (trainer == 0) {
        return -1;
    }
    if (fo == 0) {
        return -1;
    }
    for (i = 0; i < 2; i++) {
        if (fo == fightTrainer_GetFightoutPokemonPtr(trainer, i)) {
            return i;
        }
    }
    return -1;
}

FightOutPokemon* fightTrainerGetNoActionFightOutPokemonPtr(FightTrainer* trainer, u16 index) {
    FightOutPokemon* fo = fightTrainerGetValidFightOutPokemonPtr(trainer, index);
    FightAction* action;

    if (fo == 0) {
        return 0;
    }
    action = fightOutPokemon_GetFightActionBuffPtr(fo);
    if (action == 0) {
        return 0;
    }
    if (fightActionCheckValid(action) == 1) {
        return 0;
    }
    return fo;
}

void fightTrainerInitEnemyPokemonFightOutStatus(FightTrainer* trainer, u8 mode) {
    FightTrainerEnemyPokemon* p;
    u8 i;

    if (trainer == 0) {
        return;
    }
    for (i = 0; i < 12; i++) {
        p = fightTrainer_GetFightTrainerEnemyPokemonAryPtr(trainer, i);
        if (mode != 1 || fightTrainerEnemyPokemonCheckValid(p)) {
            fightTrainerEnemyPokemonInitFightOutStatus(p);
        }
    }
}

u8 fightTrainerIsAllyFightTargetPtr(FightTrainer* trainer, FightTrainer* other, u32 id) {
    if (trainer == 0) {
        return 0;
    }
    if (other == 0) {
        return 0;
    }
    void* target = fightTargetGetPtr(2, trainer, id);
    return target == fightTargetGetPtr(2, other, id);
}

u16 fightTrainerGetHikaeFightPokemonNum(FightTrainer* trainer, u16 num, u16 reserve) {
    u16 i;
    u16 hikae;
    u16 out;
    FightPokemon* fp;
    u8 result;

    if (trainer == 0) {
        return 0;
    }
    hikae = 0;
    out = 0;
    for (i = 0; i < num; i++) {
        fp = fightTrainerGetValidFightPokemonPtr(trainer, i);
        if (fp == 0) {
            continue;
        }
        result = fightTrainerCheckCanIrekaeFightPokemon(trainer, fp);
        if (result == 1) {
            continue;
        }
        if (result == 2) {
            out++;
        } else {
            hikae++;
        }
    }
    for (;;) {
        if (out >= reserve) {
            break;
        }
        if (hikae < 1) {
            break;
        }
        hikae--;
        out++;
    }
    return hikae;
}

u32 fightTrainerGetNamePtr(FightTrainer* trainer) {
    Hero* hero;

    if (trainer == 0) {
        return 0;
    }
    if (!fightTrainerCheckValid(trainer)) {
        return 0;
    }
    hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == 0) {
        return 0;
    }
    return heroGetStatus(hero, 1, 0);
}

u16* fightTrainerGetPrefixNamePtr(FightTrainer* trainer) {
    if (trainer == 0) {
        return 0;
    }
    if (!fightTrainerCheckValid(trainer)) {
        return 0;
    }
    FightTrainerKindData* kind =
        fightTrainerKindDataBiosGetPtr(fightTrainerDB_GetKindDataId(fightTrainer_GetFightTrainerDataId(trainer)));
    return GSmsgGetGSchar(fightTrainerKindDataBiosGetPrefixName(kind));
}

FightPokemon* fightTrainerSearchInvalidFightPokemonPtr(FightTrainer* trainer, u16 num) {
    u16 i;
    FightPokemon* fp;

    if (trainer == 0) {
        return 0;
    }
    for (i = 0; i < num; i++) {
        fp = fightTrainer_GetFightPokemonPtr(trainer, i);
        if (!fightPokemonCheckValid(fp)) {
            return fp;
        }
    }
    return 0;
}

u8 fightTrainerIsSelectedItemBall(FightTrainer* trainer) {
    FightOutPokemon* fo;
    u16 i;

    for (i = 0; i < 2; i++) {
        fo = fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (fightOutPokemonCheckFightOut(fo) && fightOutPokemonIsFightActionUseItemKind(fo, 1, 1, 0) == 1) {
            return 1;
        }
    }
    return 0;
}

u8 fightTrainerIsUsedItem(FightTrainer* trainer) {
    FightOutPokemon* fo;
    u16 i;

    for (i = 0; i < 2; i++) {
        fo = fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (fightOutPokemonCheckFightOut(fo) && fightOutPokemonIsFightActionUseItemKind(fo, 1, 0, 0) == 1) {
            return 1;
        }
    }
    return 0;
}

u16 fightTrainerGetSelectedItemDataId(FightTrainer* trainer, u16* ids) {
    u16 j;
    FightOutPokemon* fo;
    u16 count;
    u16 i;
    u16 id;

    for (i = 0; i < 2; i++) {
        ids[i] = 0;
    }
    count = 0;
    for (j = 0; j < 2; j++) {
        fo = fightTrainer_GetFightoutPokemonPtr(trainer, j);
        if (!fightOutPokemonCheckFightOut(fo)) {
            continue;
        }
        id = fightOutPokemonGetFightActionUseItemDataId(fo);
        if (id == 0) {
            continue;
        }
        ids[count++] = id;
    }
    return count;
}

u16 fightTrainerGetTemotiNormalItemDataIdAry(FightTrainer* trainer, u16* out, u16 count, u8 mode) {
    u16 itemCount;
    u16 used[2];
    Hero* hero;
    Item* items;
    Item* item;
    u16 usedCount;
    u16 j;
    u16 n;
    u16 i;
    u16 k;
    u16 id;
    u16 num;

    hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == 0) {
        return 0;
    }
    items = heroItemGetItemKindToItemAryPtr(hero, 2, &itemCount, 0, 0, 0);
    if (items == 0) {
        return 0;
    }
    usedCount = fightTrainerGetSelectedItemDataId(trainer, used);
    for (i = 0; i < count; i++) {
        out[i] = 0;
    }
    n = 0;
    for (j = 0; j < itemCount; j++) {
        item = &items[j];
        if (!itemCheckValid(item)) {
            continue;
        }
        id = item_GetItemDataId(item);
        if (id == 0) {
            continue;
        }
        num = item_GetNum(item);
        if (num == 0) {
            continue;
        }
        if (mode == 1) {
            for (k = 0; k < usedCount; k++) {
                if (id == used[k] && num != 0) {
                    num--;
                }
            }
            if (num == 0) {
                continue;
            }
        }
        if (n < count) {
            out[n++] = id;
        }
    }
    return n;
}

void fightTrainerToMenuBallStatus(FightTrainer* trainer, u8* status) {
    Hero* hero;
    u16 i;
    u16 j;
    Pokemon* pokemon;
    FightPokemon* fp;

    if (trainer == 0) {
        return;
    }
    if (!fightTrainerCheckValid(trainer)) {
        return;
    }
    hero = fightTrainer_GetHeroPtr(trainer);
    for (j = 0; j < 6; j++) {
        status[j] = 0;
    }
    for (i = 0; i < 6; i++) {
        pokemon = (Pokemon*)heroGetStatus(hero, 3, i);
        if (!pokemonCheckValid(pokemon)) {
            continue;
        }
        fp = fightTrainerCheckTemotiPokemonFightEntry(trainer, pokemon);
        if (fp == 0) {
            continue;
        }
        if (!fightPokemonCheckValid(fp)) {
            continue;
        }
        if (fightPokemon_GetHokakuFlag(fp) == 1) {
            continue;
        }
        if (!fightPokemonCheckFightOut(fp)) {
            status[i] = 3;
        } else if (!pokemonIsJoutaiNormal(fightPokemonGetPokemonPtr(fp))) {
            status[i] = 2;
        } else {
            status[i] = 1;
        }
    }
}

void fightTrainerSetNameHearFlag(u16 encountId) {
    void* encount = fightEncountDataBiosGetPtr(encountId);
    u16 id;
    u16 index;
    u16 flag;
    FightKindData* kind = fightKindDataBiosGetPtr(fightEncountDataBiosGetFightKind(encount));

    if (kind == 0) {
        return;
    }
    if (!fightKindDataBiosGetHostEnemyMsgFlag(kind)) {
        return;
    }
    id = fightEncountDataBiosGetFightTrainerDataId(encount, 1);
    if (fightTrainerDataBiosGetPtr(id) == 0) {
        return;
    }
    id = fightTrainerDB_GetName(id);
    index = charNameBiosSearchIndex(id);
    if (index != 0) {
        flag = charNameBiosGetHearFlag(index);
        if (flag != 0) {
            GSflagOn(flag);
        }
    }
    fightMsgctrlSetValue(0x59, id);
}

}
