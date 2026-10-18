#ifndef GBA_COMMAND_PRIVATE_HPP
#define GBA_COMMAND_PRIVATE_HPP
#include <global.h>
struct GbaPokemonRecord {u8 data[0x64];};
struct GbaExchangePacket {u32 status, pokemonId;GbaPokemonRecord pokemon;s8 ribbons[12];};
struct GbaWazaText {u8 text[0x780];};
typedef char GbaExchangeSize[sizeof(GbaExchangePacket)==0x78?1:-1];
struct FightOutPokemon;
struct GbaPartyActionRecord {
    u16 hp;u8 condition;
    u8 held:1,mail:1,pokerusPast:1,pokerusActive:1,conditionHigh:4;
    u16 item,reserved;
    u16 moves[4];s8 pp[4];u8 descriptions[4][0x50];
};
struct GbaOpponentActionRecord {
    u8 nickname[10];
    u8 sex:2,nidoranMale:1,nidoranFemale:1,japanese:1,controller:3;
    s8 level;u32 random;u16 species,hp,maxHp,form;
};
struct GbaActionPacket {
    u32 selection:24,special:1,slot:7;
    u32 swaps:24,count:8;
    u32 random[2];u16 species,form,moves[4];s8 pp[4];u16 available;
    u8 forcedMove:4,forbidden:4;
    u8 trappedBy:4,trap:4;
    GbaPartyActionRecord party[6];GbaOpponentActionRecord opponents[4];
};
typedef char GbaPartyActionSize[sizeof(GbaPartyActionRecord)==0x154?1:-1];
typedef char GbaOpponentActionSize[sizeof(GbaOpponentActionRecord)==0x18?1:-1];
#endif
