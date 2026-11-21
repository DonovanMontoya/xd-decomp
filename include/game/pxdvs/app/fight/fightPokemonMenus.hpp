#ifndef FIGHT_POKEMON_MENUS_HPP
#define FIGHT_POKEMON_MENUS_HPP
#include <game/menuWazaStatus.hpp>
#ifndef FIGHT_POKEMON_MENUS_NO_PROTOTYPES
#include <game/pxdvs/app/fight/fightPokemon.hpp>
#endif

struct FightMenuLvupStatus {
    u8 mode;
    u8 reserved01;
    u16 maxHp;
    u16 physicalAttack;
    u16 physicalDefense;
    u16 speed;
    u16 specialAttack;
    u16 specialDefense;
};
#ifndef FIGHT_POKEMON_MENUS_NO_PROTOTYPES
extern "C" {
void pokemon_SetRnd(Pokemon*, u32);
void pokemon_SetCatchTrainerRnd(Pokemon*, u32);
void fightOutPokemonGetRndStatus(FightOutPokemon*, u32*, u32*);
u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon*);
u32 menuSubGetPokemonSexForFightDisp(Pokemon*);
u8 fightFloor_GetFightKindPokemonStatusMenuSubbarFlag(void*);
void pokemonToMenuWazaStatus(Pokemon*, MENU_WAZA_STATUS*);
u32 pokemon_GetMaxHp(Pokemon*);
u32 pokemon_GetPhyAtk(Pokemon*);
u32 pokemon_GetPhyDef(Pokemon*);
u32 pokemon_GetSpeAtk(Pokemon*);
u32 pokemon_GetSpeDef(Pokemon*);
void fightOutPokemonToMenuWazaStatus(FightOutPokemon*, MENU_WAZA_STATUS*);
void fightPokemonToMenuWazaStatus(FightPokemon*, MENU_WAZA_STATUS*);
void fightPokemonToMenuLvupStatus(FightPokemon*, FightMenuLvupStatus*);
}
#endif
#endif
