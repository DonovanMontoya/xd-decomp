#ifndef PCBOX_PRIVATE_H
#define PCBOX_PRIVATE_H

#include <game/pxdvs/app/pcbox/pcbox.hpp>

extern "C" {
void* savedataGetStatus(u32, u32);
void msgctrlSetValue(u32, s32);
void GSmsgMakeGScharStr(void*, u32, u32);
void GScharCpy(void*, const u16*);
void itemInitAry(void*, u32);
void itemReplace(void*, void*);
u8 itemCheckValid(void*);
u32 itemDataBiosGetPtr(u16);
u32 itemGetStatus(void*, u32, u32, u32);
u16 itemDecItemDataIdAry(void*, u32, u16, u16, s16, u32, u32);
u16 itemAddItemDataIdAry(void*, u32, u16, u16, s16, u32, u32, u32);
u8 pokemonCheckValid(Pokemon*);
void pokemonAllKaihuku(Pokemon*);
}

s32 menuPcBoxGetLastViewBox();
void menuPocketDebugMakePokemonBySN(Pokemon&, u16, bool, f32);

#endif
