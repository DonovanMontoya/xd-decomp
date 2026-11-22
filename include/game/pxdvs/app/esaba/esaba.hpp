#ifndef GAME_ESABA_HPP
#define GAME_ESABA_HPP

#include <dolphin/types.h>

struct EsabaPokemonData {
    u8 minLevel;
    u8 maxLevel;
    u16 pokemonId;
    u32 rate;
    u32 digest;
};

struct EsabaPokemonTable {
    u32* count;
    EsabaPokemonData* data;
};

struct EsabaData {
    s32 amountFlag;
    s32 appFlag;
    s32 stepFlag;
    s32 pokemonFlag;
    s32 randomFlag;
    s32 disableFlag;
    EsabaPokemonTable** list;
};

extern "C" {
extern EsabaData* esabadata;
extern u32* esabadata_number;
u16 esabaGetPokemonID(s32 area);
u32 esabaGetPokemonRnd(s32 area);
}

static inline EsabaPokemonTable* esabaGetPokemonTable(u32 area) {
    if (area >= *esabadata_number) {
        return 0;
    }
    return *esabadata[area].list;
}

#endif
