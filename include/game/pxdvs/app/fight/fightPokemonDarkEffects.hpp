#ifndef FIGHT_POKEMON_DARK_EFFECTS_HPP
#define FIGHT_POKEMON_DARK_EFFECTS_HPP

#include <dolphin/types.h>

struct FightOutPokemon;

extern "C" {
void fightOutPokemonDarkPokemonEffect(FightOutPokemon*, u8 openMenu, u8 kind, u8 phase);
void fightOutPokemonDarkPokemonKaijoEffect(FightOutPokemon*, u8 wokeFromSleep, u8 endedHyperMode,
                                           u8 raisedAccuracy, u32 messageId, u8 phase);
}

#endif
