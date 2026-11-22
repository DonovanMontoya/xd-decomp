#ifndef GAME_MENU_FIGHT_ACTION_HPP
#define GAME_MENU_FIGHT_ACTION_HPP

#include <dolphin/types.h>

struct FIGHT_FLOOR;
struct FIGHT_TRAINER;
struct FightOutPokemon;

struct FightFloorActionMenu {
    u16 name[11];
    u8 escapeDisabled;
    u8 online;
};

typedef char FightFloorActionMenuSizeCheck[sizeof(FightFloorActionMenu) == 0x18 ? 1 : -1];

extern "C" {
void fightFloorSetMenuFightAction(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, FightFloorActionMenu* menu);
s32 menuFightOpenTop(FIGHT_TRAINER* trainer, FightFloorActionMenu* menu, s32* cursor, s32 wait);
}

#endif
