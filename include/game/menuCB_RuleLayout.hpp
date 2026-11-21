#ifndef GAME_MENUCB_RULE_LAYOUT_HPP
#define GAME_MENUCB_RULE_LAYOUT_HPP
#include <game/menuCBRule.hpp>

#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/hero/hero.hpp>

// One byte of per-pokemon error flags (most significant bit first).
typedef struct MenuCBRuleFlags0 {
    u8 legend : 1;
    u8 sameAt : 1;
    u8 levelMin : 1;
    u8 levelMax : 1;
    u8 errDark : 1;
    u8 errTamago : 1;
    u8 errWaza : 1;
    u8 errStatus : 1;
} MenuCBRuleFlags0;
typedef struct MenuCBRuleFlags1 {
    u8 item1 : 1;
    u8 item2 : 1;
    u8 itemAt : 1;
    u8 errItem : 1;
    u8 trainerLevel : 1;
    u8 trainerCount : 1;
    u8 errValid : 1;
    u8 unk0 : 1;
} MenuCBRuleFlags1;
typedef struct MenuCBRuleFlagEntry {
    MenuCBRuleFlags0 f0;
    MenuCBRuleFlags1 f1;
    u8 reserved2[2];
} MenuCBRuleFlagEntry;

typedef struct MenuCBRuleState {
    u8 reserved0[0x8];
    s32 unk8;
    s32 unkC;
    u8 reserved10[0x9918 - 0x10];
    MenuCBRule rules[6];
    u8 reserved9C78[0xC];
    MenuCBRuleFlagEntry flags[4][6];
} MenuCBRuleState;

extern MenuCBRuleState _CB;
extern u16 itemtoolbattle[];
extern u32 itemtoolbattle_number;
extern u32 *legendPokemonData_number;
extern u16 *legendPokemonData;

#endif
