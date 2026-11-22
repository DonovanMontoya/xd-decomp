#include <game/pxdvs/app/hero/heroParty.hpp>
#include <global.h>
struct Pokemon;
extern "C" {
Hero*savedataGetStatus(s32,s32);
Pokemon*heroBiosGetPokemonPtr(Hero*,u16);
u8 pokemonCheckValid(Pokemon*);
u32 pokemonBiosGetCatchBallId(Pokemon*);

void pokemonAllKaihuku(Pokemon*);
u32 revoceryCatchPokemonBall(u16 index){Pokemon*pokemon=heroBiosGetPokemonPtr(savedataGetStatus(0,2),index);if(pokemonCheckValid(pokemon)==0){return 0;}else{return pokemonBiosGetCatchBallId(pokemon);}}
void recoveryPokemon(){Hero*hero=savedataGetStatus(0,2);u32 count=heroGetPokeomCount(hero);for(u32 i=0;i<=count;i++){pokemonAllKaihuku(heroBiosGetPokemonPtr(hero,i));}}
}
