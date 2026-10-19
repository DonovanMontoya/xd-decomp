#ifndef POKEMON_H
#define POKEMON_H

#include <global.h>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

class Hero;

struct PokemonStatusRnd {
  u8 maxHp; // 0x0
  u8 phyAtk; // 0x1
  u8 phyDef; // 0x2
  u8 speAtk; // 0x3
  u8 speDef; // 0x4
  u8 nimbleness; // 0x5

  void setNimbleness(u8 data);
  void setSpeDef(u8 data);
  void setSpeAtk(u8 data);
  void setPhyDef(u8 data);
  void setPhyAtk(u8 data);
  void setMaxHp(u8 data);
  u32 getNimbleness() const;
  u32 getSpeDef() const;
  u32 getSpeAtk() const;
  u32 getPhyDef() const;
  u32 getPhyAtk() const;
  u32 getMaxHp() const;
};

union Ribbon {
  struct {
    u32 champ : 1;
    u32 winning : 1;
    u32 victory : 1;
    u32 bromide : 1;
    u32 ganba : 1;
    u32 marine : 1;
    u32 land : 1;
    u32 sky : 1;
    u32 country : 1;
    u32 national : 1;
    u32 earth: 1;
    u32 world : 1;
    u32 amari : 8;
    u32 unk2 : 8;
  } bits;
  u32 allBits;
};
struct Attest {
  u8 unk[4];
};

#define MAX_EXPAND_STATUS 2
struct ExpandStatus {
  u8 style;
  u8 beautiful;
  u8 cute;
  u8 clever;
  u8 strong;
};

union PokemonFlags {
  struct {
    u8 tamago: 1;
    u8 tokusei: 1;
    u8 fusei : 1;
    u8 unk : 5;
  } bits;
  u8 allBits;
};

// Waza ("technique") means a move
#define MAX_WAZA 4
struct PokemonWaza {
  u16 dataId;
  u8 pp; // 0x2
  u8 ppCount; // 0x3
};

// Canonical in-memory Pokemon record (size 0xC4). Party/PC box/save/battle copies all use this layout.
// Offsets confirmed against pokemonBios.s / pokemonDB.cpp accessors (see build/findings/trackA.md).
struct Pokemon {
  u16 dataID; // 0x0, species id
  u16 itemDataID; // 0x2, held item
  u16 hp; // 0x4
  u16 friendLevel; // 0x6
  u16 catchFloorId; // 0x8
  u16 amari; // 0xa
  u16 para1Amari; // 0xc
  u8 catchLevel; // 0xe
  u8 catchBallId; // 0xf
  u8 catchTrainerSex; // 0x10
  u8 level; // 0x11
  u8 fur; // 0x12
  u8 pokerus; // 0x13
  u8 pcboxMark; // 0x14
  u8 mailId; // 0x15
  u8 condition; // 0x16
  u8 conditionCount; // 0x17
  u8 conditionTurn; // 0x18
  u8 conditionTurnNow; // 0x19
  u8 flagAmari; // 0x1a
  u8 unk1B[2]; // 0x1b
  PokemonFlags flags; // 0x1d (tamago 0x80, tokusei 0x40 = second ability, fusei 0x20)
  u8 unk1E[2]; // 0x1e
  u32 exp; // 0x20
  u32 catchTrainerRnd; // 0x24, original trainer id
  u32 rnd; // 0x28, personality value
  u32 conditionAmari; // 0x2c

  u32 eventGetFlag; // 0x30
  Attest attest; // 0x34 (language/area id of the origin game)

  u16 catchTrainerName[11]; // 0x38, wide chars
  u16 nickname[11]; // 0x4e, wide chars
  u16 nicknameOrg[11]; // 0x64, wide chars
  u8 unk7A[2]; // 0x7a

  Ribbon ribbon; // 0x7c
  PokemonWaza wazas[MAX_WAZA]; // 0x80
  u16 maxHp; // 0x90
  u16 phyAtk; //0x92
  u16 phyDef; //0x94
  u16 speAtk; //0x96
  u16 speDef; //0x98
  u16 nimbleness; //0x9a
  u16 maxHpEffort; //0x9c
  u16 phyAtkEffort; //0x9e
  u16 phyDefEffort; //0xa0
  u16 speAtkEffort; //0xa2
  u16 speDefEffort; //0xa4
  u16 nimblenessEffort; //0xa6
  PokemonStatusRnd statusRnd; // 0xa8
  ExpandStatus expandStatus[MAX_EXPAND_STATUS]; // 0xae
  u16 fightTrainerPokemonDataId; // 0xb8
  u16 darkPokemonDataID; // 0xba
  u8 comboPartnerAll; // 0xbc
  u8 unkBD[7]; // 0xbd


  // Setters/getters
  u16 getAmari() const;
  u8 getPcboxMark() const;
  u16 getPara1Amari() const;
  u16 getDarkpokemonDataID() const;
  u16 getItemDataId() const;
  u16 getPokemonDataId() const;
  u16 getHp() const;
  u16 getMaxHp() const;
  u16 getFriendLevel() const;
  u8  getLevel() const;
  u8  getCondition() const;
  u8  getConditionCount() const;
  u8  getConditionTurn() const;
  u8  getConditionTurnNow() const;
  u16 getNimbleness() const;
  u16 getSpeDef() const;
  u16 getSpeAtk() const;
  u16 getPhyDef() const;
  u16 getPhyAtk() const;
  u16 getMaxHpEffort() const;
  u16 getNimblenessEffort() const;
  u16 getSpeDefEffort() const;
  u16 getSpeAtkEffort() const;
  u16 getPhyDefEffort() const;
  u16 getPhyAtkEffort() const;
  u32 getRnd() const;
  u32 getCatchTrainerRnd() const;
  Ribbon* getRibbon();
  Attest* getAttest();
  u16* getNicknamePtr();
  bool isFuseiFlag() const;
  PokemonWaza* getPokemonWaza(u16);
  u8 getSpeDefRnd() const;
  u8 getSpeAtkRnd() const;
  u8 getPhyDefRnd() const;
  u8 getPhyAtkRnd() const;
  u8 getMaxHpRnd() const;
  u8 getNimblenessRnd() const;
  u16 getPoolFriendLevel() const;
  u32 getPoolExp() const;
  s32 getDarkPointDirect() const;

  void setPara1Amari(u16);
  void setAmari(u16);
  void setFriendLevel(u16);
  void setPoolFriendLevel(u16);
  void setPoolExp(u32);
  void setNimbleness(u16);
  void setSpeDef(u16);
  void setSpeAtk(u16);
  void setPhyDef(u16);
  void setPhyAtk(u16);
  void setMaxHp(u16);
  void setHp(u16);
  void setMaxHpEffort(u16);
  void setNimblenessEffort(u16);
  void setSpeDefEffort(u16);
  void setSpeAtkEffort(u16);
  void setPhyDefEffort(u16);
  void setPhyAtkEffort(u16);
  void setSpeDefRnd(u16);
  void setSpeAtkRnd(u16);
  void setPhyDefRnd(u16);
  void setPhyAtkRnd(u16);
  void setMaxHpRnd(u16);
  void setNimblenessRnd(u16);
  void setDarkPointDirect(s32);
  void setConditionTurnNow(u8);
  void setConditionTurn(u8);
  void setConditionCount(u8);
  void setCondition(u8);
  void setPcboxMark(u8);
  void setItemDataId(u16);
  void setExp(u32);
  void setCatchTrainerRnd(u32);
  void setCatchTrainerSex(u8);
  void setCatchBallId(u8);
  void setCatchLevel(u8);
  void setCatchFloorId(u16);
  void setRnd(u32);



  bool isHatena() const;
  Pokemon * getPokemon(Hero *, s32);
  DarkPokemon * getDarkPokemon();
  const DarkPokemon* getDarkPokemon() const;
  void setReversMode(bool);
  bool isReversMode() const;
  void setDarkPoint(f32);
  f32 getDarkPoint() const;
  void setNicknameOrgPtr(u16*);
  void setNicknamePtr(u16*);
  void setCatchTrainerNamePtr(u16*);
  bool checkValid() const;
  void clear();
  bool isLegend() const;
  u8 getSex() const;
  bool isTokuseiFlag() const;
  static bool isRareParam(u32 trainerRnd, u32 pokemonRnd);
  bool isRare() const;
  u8 getSeikaku() const;
  bool isDarkPokemon() const;
  void initCondition();
  void copyCondition(const Pokemon*);
  void* getPokemonDataPtr() const;
};

#include <libc/stddef.h>
typedef char Pokemon_size_check[(sizeof(Pokemon) == 0xC4) ? 1 : -1];
typedef char Pokemon_level_check[(offsetof(Pokemon, level) == 0x11) ? 1 : -1];
typedef char Pokemon_flags_check[(offsetof(Pokemon, flags) == 0x1D) ? 1 : -1];
typedef char Pokemon_exp_check[(offsetof(Pokemon, exp) == 0x20) ? 1 : -1];
typedef char Pokemon_otid_check[(offsetof(Pokemon, catchTrainerRnd) == 0x24) ? 1 : -1];
typedef char Pokemon_rnd_check[(offsetof(Pokemon, rnd) == 0x28) ? 1 : -1];
typedef char Pokemon_eventflag_check[(offsetof(Pokemon, eventGetFlag) == 0x30) ? 1 : -1];
typedef char Pokemon_ctname_check[(offsetof(Pokemon, catchTrainerName) == 0x38) ? 1 : -1];
typedef char Pokemon_nickname_check[(offsetof(Pokemon, nickname) == 0x4E) ? 1 : -1];
typedef char Pokemon_nicknameOrg_check[(offsetof(Pokemon, nicknameOrg) == 0x64) ? 1 : -1];
typedef char Pokemon_ribbon_check[(offsetof(Pokemon, ribbon) == 0x7C) ? 1 : -1];
typedef char Pokemon_wazas_check[(offsetof(Pokemon, wazas) == 0x80) ? 1 : -1];
typedef char Pokemon_maxHp_check[(offsetof(Pokemon, maxHp) == 0x90) ? 1 : -1];
typedef char Pokemon_effort_check[(offsetof(Pokemon, maxHpEffort) == 0x9C) ? 1 : -1];
typedef char Pokemon_statusRnd_check[(offsetof(Pokemon, statusRnd) == 0xA8) ? 1 : -1];
typedef char Pokemon_expand_check[(offsetof(Pokemon, expandStatus) == 0xAE) ? 1 : -1];
typedef char Pokemon_darkId_check[(offsetof(Pokemon, darkPokemonDataID) == 0xBA) ? 1 : -1];
typedef char Pokemon_combo_check[(offsetof(Pokemon, comboPartnerAll) == 0xBC) ? 1 : -1];

// Prototypes of the pokemon.cpp C functions. Units that declare conflicting local prototypes can
// define POKEMON_HPP_NO_PROTOTYPES before including this header to get only the struct definitions.
#ifndef POKEMON_HPP_NO_PROTOTYPES
extern "C" void pokemonSetDp(Pokemon*, f32);

extern "C" void pokemonSetTokuseiFlag(Pokemon* , u32);
extern "C" void pokemonInitAry(u32, u16);
extern "C" void pokemonInit(u32);
extern "C" void pokemonInitDarkPokemon(Pokemon*);
extern "C" void pokemonInitJoutai(Pokemon*);
extern "C" void pokemonWazaInitAry(Pokemon* ,u16);
extern "C" void pokemonWazaInit(Pokemon* ,u32);
extern "C" u8 pokemonWazaGetMaxPP(Pokemon*, u16);
extern "C" u32 pokemonCheckRare(Pokemon*);
extern "C" void pokemonGrowBasisStatus(Pokemon*,u32);
extern "C" void pokemonResetBasisStatus(Pokemon*);
extern "C" void pokemonSetStatus(Pokemon*, u32, u16, u16, u32);
extern "C" u32 pokemonGetStatus(Pokemon*, u32, u16, u16);
extern "C" u32 pokemonAdjustValueBySeikaku(u32, u16, u32);
static u8 _pokemonGetSeikaku(Pokemon*);
extern "C" u8 pokemonGetSeikakuAsRnd(u32);
static u8 _pokemonGetHinsi(Pokemon*);
static void _pokemonSetLevelBasisStatus(Pokemon*, u8);
static u16 _pokemonGetLevelOneStatus(Pokemon*, u8, u16, u16, u16, u16, long);
extern "C" u16 pokemonCreateBasisStatus(u16, u8, u16, u8, s32);
static u8 _pokemonGetNowExpToLevel(Pokemon*);
extern "C" u8 pokemonGetExpToLevel(u8, u32);
static int _pokemonGetLevelToExp(u8, u8);
extern "C" int pokemonCheckRareRnd(unsigned long, unsigned long);
static int _pokemonCheckRare(unsigned long, unsigned long);
#endif

#endif
