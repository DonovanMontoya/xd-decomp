#ifndef GAME_MENU_POKEMON_STATUS_HPP
#define GAME_MENU_POKEMON_STATUS_HPP

#include <dolphin/types.h>

struct Pokemon;
struct FightPokemon;
struct FightOutPokemon;

struct MENU_POKEMON_STATUS {
    u16 name[11];
    u8 hideSubbar;
    u8 level;
    s16 maxHp;
    s16 hp;
    union {
        u32 nextExp;
        f32 darkMax;
    };
    union {
        u32 nowExp;
        f32 darkNow;
    };
    u16 joutaiSprite;
    u16 faceId;
    u8 sex;
    u8 darkState;
    u16 itemId;
    u8 reserved2C;
    u8 opening;
    u8 reserved2E[2];
};

extern "C" {
void pokemonToMenuPokemonStatus(Pokemon*, FightPokemon*, MENU_POKEMON_STATUS*, s8 rare);
void pokemonToMenuPokemonStatusSubBar(Pokemon*, MENU_POKEMON_STATUS*);
void fightOutPokemonToMenuPokemonStatus(FightOutPokemon*, MENU_POKEMON_STATUS*);
}

#endif
