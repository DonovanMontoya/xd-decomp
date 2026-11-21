#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <global.h>
#include <libc/stddef.h>
#include <game/pxdvs/app/hero/hero.hpp>
#include <game/pxdvs/app/pcbox/pcbox.hpp>
#include <game/pxdvs/app/sodateya/sodateya.hpp>
#include <game/pxdvs/app/mail/mailbox.hpp>
#include <game/pxdvs/app/memo/memo.hpp>
#include <game/pxdvs/app/reliveHall/reliveHall.hpp>
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
  PCBOX pcbox;                     // 0xAD0
  u8 unkC720[0x10];                // 0xC720
  Mailbox mailbox;                 // 0xC730
  u8 unkC77A[0x16];                // 0xC77A
  Sodateya sodateya;               // 0xC790
  u8 unkC85C[0x14];                // 0xC85C
  Memo memoData;                    // 0xC870
  u8 unkDFE4[0x1C];                // 0xDFE4
  u8 tool[0xE380 - 0xE000];        // 0xE000
  DarkPokemon darkPokemon[0x80];   // 0xE380, 0x48 bytes each
  u8 unk10780[0x10790 - 0x10780];  // 0x10780
  u8 flagLevel0[0x107B0 - 0x10790]; // 0x10790
  u8 flagLevel1[0x10830 - 0x107B0]; // 0x107B0
  u8 flagLevel2[0x10E60 - 0x10830]; // 0x10830
  u8 exRibbon[0x10E80 - 0x10E60];  // 0x10E60
  u8 anywaySave[0x1D690 - 0x10E80]; // 0x10E80
  CReliveHall relive;              // 0x1D690
  u8 unk1F928[0x18];               // 0x1F928
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
