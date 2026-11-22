#ifndef HERO_PARTY_HPP
#define HERO_PARTY_HPP

#include <dolphin/types.h>

class Hero;

extern "C" {
void heroCreate(Hero* hero, const u16* name, u8 sex);
u32 heroGetPokeomCount(Hero* hero);
s32 heroGetEmptySlot(Hero* hero);
s32 heroGetLivingPokemonCount(Hero* hero);
}

#endif
