#include <dolphin/types.h>
#pragma dont_inline on
#include <game/gbaCommandPrivate.hpp>

extern "C" {
void *heroBiosGetPokemonPtr(void *, u16);
u32 pokemonBiosGetPokemonWazaDataId(void *, u16);
u32 wazaDataBiosGetPtr(u32);
void wazaDataBiosGetDoc(u32);
u16 *GSmsgGetGSchar();
s32 GBAMakeFromGSchar(u8 *, const u16 *, s32);
s32 gamedataGetStatus(s32, s32);
void *memset(void *, int, unsigned long);
}

static s32 convline(u8 *dst, const u16 **src);
extern "C" s32 GetWazaDocGBA(u8 *dst, s32 id);

extern "C" s32 wazaconv(u32 trainer, GbaWazaText *dst) {
    s32 i;
    for (i = 0; i < 6; i++) {
        s32 j;
        void *pokemon;
        pokemon = heroBiosGetPokemonPtr((void *)trainer, i);
        for (j = 0; j < 4; j++) {
            u32 id = pokemonBiosGetPokemonWazaDataId(pokemon, j);
            s32 result = GetWazaDocGBA(dst->text, id);
            if (result != 0) return result;
            dst = (GbaWazaText *)((u8 *)dst + 0x50);
        }
    }
    return 0;
}

extern "C" s32 GetWazaDocGBA(u8 *dst, s32 id) {
    u32 data = wazaDataBiosGetPtr(id);
    memset(dst, 0, 0x50);
    if (data != 0) {
        wazaDataBiosGetDoc(data);
        const u16 *src = GSmsgGetGSchar();
        dst += convline(dst, &src);
        if (*src == 0xFFFF) {
            *dst++ = 0xFE;
            src = (const u16 *)((const u8 *)src + 3);
            dst += convline(dst, &src);
        }
        *dst = 0xFF;
    }
    return 0;
}

static s32 convline(u8 *dst, const u16 **src) {
    u16 text[0x51];
    s32 count = 0;
    while (**src != 0 && **src != 0xFFFF) {
        if (count < 0x50) text[count++] = **src;
        ++*src;
    }
    text[count] = 0;
    return GBAMakeFromGSchar(dst, text, gamedataGetStatus(0, 5));
}
