#include <global.h>

struct PokemonData;

extern "C" {
u8 pokemonDB_GetZokuseiDataId(u16, u16);
u8 pokemonDataBiosGetZokuseiDataId(PokemonData*, u16);
u16 zokuseiBiosGetSpriteID(u16);
u16 zokuseiBiosGetWazaJoutai(u32, u32);
extern u32* pokemon_data_number;
extern u32* zokusei_data_number;
s32 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16, u16*, u16);

static inline u16 _getWazaJoutai(u16 id, u16 target) {
    return zokuseiBiosGetWazaJoutai(id, target);
}

#pragma force_active on
u16 zokuseiGetPokemonSpriteID(PokemonData* pdata, u16 index) {
    if (index >= 2) {
        return 0;
    }
    return zokuseiBiosGetSpriteID(pokemonDataBiosGetZokuseiDataId(pdata, index));
}
#pragma force_active reset

#pragma force_active on
s32 zokuseiGetAisyouValue(u16 type, u8 attack, u8 side) {
    s32 value;
    u16 result;
    u16 i;
    u16 code1;
    u16 code2;

    value = 0;
    for (i = 0; i < *zokusei_data_number; i++) {
        if (i == 9) {
            continue;
        }
        if (attack == 1) {
            code1 = zokuseiBiosGetWazaJoutai(type, i);
            result = code1;
            if (result == 0x43) {
                if (side != 1) {
                    value -= 10;
                }
            } else if (result == 0x42) {
                if (side != 1) {
                    value -= 10;
                }
            } else if (result == 0x41) {
                if (side != 2) {
                    value += 10;
                }
            }
        } else {
            code2 = zokuseiBiosGetWazaJoutai(i, type);
            result = code2;
            if (result == 0x43) {
                if (side != 2) {
                    value += 10;
                }
            } else if (result == 0x42) {
                if (side != 2) {
                    value += 10;
                }
            } else if (result == 0x41) {
                if (side != 1) {
                    value -= 10;
                }
            }
        }
    }
    return value;
}
#pragma force_active reset

#pragma force_active on
s32 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16 type, u16* arr, u16 count) {
    u16 i;
    u16 countA = 0;
    u16 countB = 0;
    u16 e;
    u16 result;

    for (i = 0; i < count; i++) {
        if (arr[i] == 9) {
            continue;
        }
        e = arr[i];
        result = _getWazaJoutai(type, e);
        if (result == 0x43) {
            return 0x43;
        }
        if (result == 0x41) {
            countA++;
            continue;
        }
        if (result == 0x42) {
            countB++;
        }
    }
    if (countA == 0 && countB == 0) {
        return 0x3f;
    }
    if (countA == countB) {
        return 0x3f;
    }
    if (countA > countB) {
        return 0x41;
    }
    return 0x42;
}
#pragma force_active reset

#pragma force_active on
s32 zokuseiGetWazaJoutai_PokemonId(u16 type, u16 pokemon) {
    u16 types[4];
    u16 count;
    u8 i;
    u16 id;

    if (pokemon > *pokemon_data_number) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 2; i++) {
        id = pokemonDB_GetZokuseiDataId(pokemon, i);
        if (id != 9) {
            types[count] = id;
            count++;
        }
    }
    return zokuseiGetWazaJoutaiAsDefenseZokuseiAry(type, types, count);
}
#pragma force_active reset

#pragma force_active on
u16 zokuseiGetWazaJoutai(u16 id, u16 target) {
    return zokuseiBiosGetWazaJoutai(id, target);
}
#pragma force_active reset

}
