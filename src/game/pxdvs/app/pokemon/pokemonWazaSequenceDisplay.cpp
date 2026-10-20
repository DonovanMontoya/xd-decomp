#include <global.h>

extern "C" {
void GSthreadSwitch();
u32 Sequence_LoadPokemon(u16, s32, s32);
u32 Sequence_LoadWaza(u32, u16, u8, u32);
f32 pokecoloGetFrameTime();
s32 pokemonBiosGetRnd(s32);
s32 pokemonGetStatus(s32, s32, s32, s32);
}

static const f32 _waitTimeZero = 0.0f;

extern "C" void waitTime(f32 seconds) {
    f32 elapsed = _waitTimeZero;
    goto test;
body:
    GSthreadSwitch();
    elapsed += pokecoloGetFrameTime();
test:
    if (elapsed < seconds) goto body;
}

struct WazaSequenceDisplayEntry {
    u16 wazaId;
    u16 sequenceId;
};

extern "C" s32 loadSequence(u32* sequence, s32 pokemon, WazaSequenceDisplayEntry* entries, s32 entryCount) {
    s32 randomId;
    s32 canTransform;
    u16 slot = pokemonGetStatus(pokemon, 0, 0x6E, 0);
    if (slot == 0) return 0;
    u16 pokemonId = pokemonGetStatus(0, slot, 0x66, 0);
    if (pokemonId == 0) return 0;
    randomId = pokemonBiosGetRnd(pokemon);
    canTransform = pokemonGetStatus(pokemon, 0, 0xC1, 0) != 0;
    u32 loaded = Sequence_LoadPokemon(pokemonId, randomId, canTransform);
    *sequence = loaded;
    if (loaded == 0) return 0;
    for (s32 i = 0; i < entryCount; ++i) {
        if (Sequence_LoadWaza(*sequence, entries[i].wazaId, entries[i].sequenceId, 0) == 0) return 0;
    }
    return 1;
}
