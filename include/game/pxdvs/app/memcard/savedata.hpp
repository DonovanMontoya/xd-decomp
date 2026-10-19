#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <global.h>
#include <libc/stddef.h>
#include <game/pxdvs/app/hero/hero.hpp>
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>

// In-memory save data (pokecolo_savedata, 0x287D0 bytes). The live pointer is now_savedata_ptr
// (savedataBiosGetNowSavedataPtr). Region offsets come from the savedataBiosGet*Ptr functions;
// sub-region sizes are the gaps up to the next known region (contents of those are not typed here).
// savedataGetStatus(save, id) returns a region pointer: 1 gamedata, 2 hero, 3 pcbox, 4/5/6 flag levels 0-2,
// 0xF dark pokemon table.
struct savedata {
  u8 header[0xA0];                 // 0x0
  u8 gamedata[0x140 - 0xA0];       // 0xA0
  Hero hero;                       // 0x140
  u8 unkAB8[0xAD0 - 0xAB8];        // 0xAB8
  u8 pcbox[0xC730 - 0xAD0];        // 0xAD0
  u8 mailbox[0xC790 - 0xC730];     // 0xC730
  u8 sodateya[0xC870 - 0xC790];    // 0xC790
  u8 memoData[0xE000 - 0xC870];    // 0xC870
  u8 tool[0xE380 - 0xE000];        // 0xE000
  DarkPokemon darkPokemon[0x80];   // 0xE380, 0x48 bytes each
  u8 unk10780[0x10790 - 0x10780];  // 0x10780
  u8 flagLevel0[0x107B0 - 0x10790]; // 0x10790
  u8 flagLevel1[0x10830 - 0x107B0]; // 0x107B0
  u8 flagLevel2[0x10E60 - 0x10830]; // 0x10830
  u8 exRibbon[0x10E80 - 0x10E60];  // 0x10E60
  u8 anywaySave[0x1D690 - 0x10E80]; // 0x10E80
  u8 relive[0x1F940 - 0x1D690];    // 0x1D690
  u8 yobi1[0x1FD50 - 0x1F940];     // 0x1F940
  u8 yobi2[0x20560 - 0x1FD50];     // 0x1FD50
  u8 yobi3[0x21570 - 0x20560];     // 0x20560
  u8 yobi4[0x287D0 - 0x21570];     // 0x21570
};

typedef char savedata_size_check[(sizeof(savedata) == 0x287D0) ? 1 : -1];
typedef char savedata_gamedata_check[(offsetof(savedata, gamedata) == 0xA0) ? 1 : -1];
typedef char savedata_hero_check[(offsetof(savedata, hero) == 0x140) ? 1 : -1];
typedef char savedata_pcbox_check[(offsetof(savedata, pcbox) == 0xAD0) ? 1 : -1];
typedef char savedata_dark_check[(offsetof(savedata, darkPokemon) == 0xE380) ? 1 : -1];
typedef char savedata_flags_check[(offsetof(savedata, flagLevel0) == 0x10790) ? 1 : -1];
typedef char savedata_relive_check[(offsetof(savedata, relive) == 0x1D690) ? 1 : -1];

extern "C" void *savedataGetStatus(savedata *, u16);

#endif
