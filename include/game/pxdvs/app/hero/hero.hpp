#ifndef HERO_MEMBER_FUNCTIONS_H
#define HERO_MEMBER_FUNCTIONS_H

#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
#include <game/pxdvs/app/hero/heroPokemonGet.hpp>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

#include <game/pxdvs/app/item/itemBiosLayout.hpp>

// Canonical Hero (player) record, size 0x978. Lives at savedata+0x140 (savedataBiosGetHeroPtr);
// battle code keeps a copy in fight_floor trainer data (heroBiosCopy copies 0x978 bytes).
// Offsets verified against heroBios.s / heroMemberFunctions.s (see build/findings/trackA.md).
class Hero {
public:
  char16 heroName[11];           // 0x0, wide chars
  char16 heroNameCopy[11];       // 0x16
  u32 heroRnd;                   // OT ID, 0x2c
  Pokemon partyPokemon[6];       // 0x30
  ItemBiosRecord items[30];      // Items, 0x4c8
  ItemBiosRecord keyItems[43];   // Key Items, 0x540
  ItemBiosRecord ballItems[16];  // Balls, 0x5ec
  ItemBiosRecord TMHMItems[64];  // TMs/HMs, 0x62c
  ItemBiosRecord berryItems[46]; // Berries, 0x72c
  ItemBiosRecord cologneItems[3]; // Cologne, 0x7e4
  ItemBiosRecord battleCDItems[60]; // Battle CDs, 0x7f0
  u8 sexDataID;                  // 0x8e0
  u8 homePlace;                  // 0x8e1
  u8 pad8E2[2];                  // 0x8e2
  u32 pokedollars;               // money, 0x8e4
  u32 pokecoupons;               // 0x8e8
  u32 pokecouponsAll;            // 0x8ec
  u8 badge01Flag;                // 0x8f0
  u8 badge02Flag;                // 0x8f1
  u8 badge03Flag;                // 0x8f2
  u8 badge04Flag;                // 0x8f3
  u8 badge05Flag;                // 0x8f4
  u8 badge06Flag;                // 0x8f5
  u8 badge07Flag;                // 0x8f6
  u8 badge08Flag;                // 0x8f7
  u8 hizukiFlag;                 // 0x8f8
  u8 pad8F9;                     // 0x8f9
  ItemBiosRecord hizukiItems[10]; // 0x8fa
  char16 hizukiName[11];         // 0x922, wide chars
  u8 meetShadowPokemonCount;     // 0x938
  u8 followerID;                 // 0x939
  s16 restartPosAngle;           // 0x93a, degrees
  GSvec restartPos;              // 0x93c
  u32 footStep;                  // 0x948
  u32 followerResID;             // 0x94c
  u32 followerGrpID;             // 0x950
  u32 followerObjID;             // 0x954
  u8 followerModelLevel;         // 0x958
  u8 heroStyle;                  // 0x959
  u16 battleResumeFloorID;       // 0x95a
  u8 battleResumeFloorIndex;     // 0x95c
  u8 unk95D[0x978 - 0x95D];      // 0x95d

  bool itemSort(u8);
  void setBattleResumeFloorIndex(u8);
  u8 getBattleResumeFloorIndex() const;
  void setBattleResumeFloorID(unsigned int);
  u16 getBattleResumeFloorID() const;
  u32 getHeroObjID(s32, s32);
  void setHeroStyle(u8, bool);
  u8 getHeroStyle() const;
  s16 pokemonGet(HeroPokemonGetParam *, bool);
  u32 getLegendPokemonSize() const;
  u32 itemQuantity(u16);
  static Hero *getHeroPtr();
  void getRestertPos(GSvec *, short &) const;
  void setRestertPos();
  bool deletePokemon(s32);
  bool setPokemon(const Pokemon *, s32);
  u32 addPokemon(const Pokemon *);
  Pokemon *getPokemon(s32, bool &);
  const Pokemon *getPokemon(s32) const;
  Pokemon *getPokemon(s32);
  void setMeetDarkPokemonCount(u8);
  u8 getMeetDarkPokemonCount() const;
  ItemBiosRecord *getDisk();
  void addFootStep(u32);
  u32 getFootStep() const;
  u8 getFollowerModelLevel();
  void setFollowerModelLevel(u8);
  u8 getFollowerID();
  void setFollowerID(u8);
  u32 getFollowerGrpID();
  u32 getFollowerResID();
  void setFollowerObjID(u32);
  void setFollowerGrpID(u32);
  void setFollowerResID(u32);
  u32 getHeroRnd() const;
};

typedef char Hero_size_check[(sizeof(Hero) == 0x978) ? 1 : -1];
typedef char Hero_rnd_check[(offsetof(Hero, heroRnd) == 0x2C) ? 1 : -1];
typedef char Hero_party_check[(offsetof(Hero, partyPokemon) == 0x30) ? 1 : -1];
typedef char Hero_items_check[(offsetof(Hero, items) == 0x4C8) ? 1 : -1];
typedef char Hero_keyItems_check[(offsetof(Hero, keyItems) == 0x540) ? 1 : -1];
typedef char Hero_balls_check[(offsetof(Hero, ballItems) == 0x5EC) ? 1 : -1];
typedef char Hero_tmhm_check[(offsetof(Hero, TMHMItems) == 0x62C) ? 1 : -1];
typedef char Hero_berries_check[(offsetof(Hero, berryItems) == 0x72C) ? 1 : -1];
typedef char Hero_cologne_check[(offsetof(Hero, cologneItems) == 0x7E4) ? 1 : -1];
typedef char Hero_battleCD_check[(offsetof(Hero, battleCDItems) == 0x7F0) ? 1 : -1];
typedef char Hero_sex_check[(offsetof(Hero, sexDataID) == 0x8E0) ? 1 : -1];
typedef char Hero_money_check[(offsetof(Hero, pokedollars) == 0x8E4) ? 1 : -1];
typedef char Hero_coupons_check[(offsetof(Hero, pokecoupons) == 0x8E8) ? 1 : -1];
typedef char Hero_badges_check[(offsetof(Hero, badge01Flag) == 0x8F0) ? 1 : -1];
typedef char Hero_hizukiItems_check[(offsetof(Hero, hizukiItems) == 0x8FA) ? 1 : -1];
typedef char Hero_hizukiName_check[(offsetof(Hero, hizukiName) == 0x922) ? 1 : -1];
typedef char Hero_meet_check[(offsetof(Hero, meetShadowPokemonCount) == 0x938) ? 1 : -1];
typedef char Hero_restart_check[(offsetof(Hero, restartPosAngle) == 0x93A && offsetof(Hero, restartPos) == 0x93C) ? 1 : -1];
typedef char Hero_footStep_check[(offsetof(Hero, footStep) == 0x948) ? 1 : -1];
typedef char Hero_follower_check[(offsetof(Hero, followerResID) == 0x94C) ? 1 : -1];
typedef char Hero_resume_check[(offsetof(Hero, battleResumeFloorID) == 0x95A) ? 1 : -1];

#endif
