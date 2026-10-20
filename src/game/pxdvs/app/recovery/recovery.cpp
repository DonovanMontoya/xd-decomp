#include <global.h>
struct Pokemon;struct HeroData;
extern "C" {
HeroData*savedataGetStatus(s32,s32);
Pokemon*heroBiosGetPokemonPtr(HeroData*,u16);
u8 pokemonCheckValid(Pokemon*);
u32 pokemonBiosGetCatchBallId(Pokemon*);
u32 heroGetPokeomCount();
void pokemonAllKaihuku(Pokemon*);
u32 revoceryCatchPokemonBall(u16 index){Pokemon*pokemon=heroBiosGetPokemonPtr(savedataGetStatus(0,2),index);if(pokemonCheckValid(pokemon)==0){return 0;}else{return pokemonBiosGetCatchBallId(pokemon);}}
void recoveryPokemon(){HeroData*hero=savedataGetStatus(0,2);u32 count=heroGetPokeomCount();for(u32 i=0;i<=count;i++){pokemonAllKaihuku(heroBiosGetPokemonPtr(hero,i));}}
}
