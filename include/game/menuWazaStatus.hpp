#ifndef GAME_MENU_WAZA_STATUS_HPP
#define GAME_MENU_WAZA_STATUS_HPP

#include <dolphin/types.h>

struct FightOutPokemon;

struct MenuFightWazaEntry {
    u16* name;
    u16* typeName;
    u16 type;
    u8 maxPP;
    u8 currentPP;
};

struct MENU_WAZA_STATUS {
    u16* nickname;
    MenuFightWazaEntry entries[4];
    u8 reserved34[0xC];
    FightOutPokemon* fightPokemon;
    u8 online;
};

typedef char MenuWazaStatusSizeCheck[sizeof(MENU_WAZA_STATUS) == 0x48 ? 1 : -1];

#endif
