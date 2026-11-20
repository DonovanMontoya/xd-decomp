#ifndef HERO_PARTY_HPP
#define HERO_PARTY_HPP

#include <dolphin/types.h>

class Hero;

extern "C" {
u32 heroGetPokeomCount(Hero* hero);
s32 heroGetEmptySlot(Hero* hero);
s32 heroGetLivingPokemonCount(Hero* hero);
}

#endif
