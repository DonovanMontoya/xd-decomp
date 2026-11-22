#ifndef PXDVS_APP_SODATEYA_HPP
#define PXDVS_APP_SODATEYA_HPP

#include <game/pxdvs/app/pokemon/pokemon.hpp>

struct Sodateya {
    u8 active;
    u8 initialLevel;
    u16 steps;
    u32 initialDP;
    Pokemon pokemon;
};

typedef char SodateyaStepsOffset[offsetof(Sodateya, steps) == 2 ? 1 : -1];
typedef char SodateyaInitialDPOffset[offsetof(Sodateya, initialDP) == 4 ? 1 : -1];
typedef char SodateyaPokemonOffset[offsetof(Sodateya, pokemon) == 8 ? 1 : -1];
typedef char SodateyaSize[sizeof(Sodateya) == 0xCC ? 1 : -1];

extern "C" void sodateyaInit(Sodateya*);
extern "C" Pokemon* sodateyaGetPokemonPtr(Sodateya*);

#endif
