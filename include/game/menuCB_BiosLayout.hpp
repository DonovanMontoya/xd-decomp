#ifndef GAME_MENUCB_BIOS_LAYOUT_HPP
#define GAME_MENUCB_BIOS_LAYOUT_HPP
#include <game/menuCBRule.hpp>
#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/hero/hero.hpp>

typedef struct Pokemon Pokemon;

typedef struct MenuCBBiosTrainer {
    u16 unk0;
    u16 unk2;
    s32 unk4;
    u8 reserved8[0x1C];
    s32 unk24;
    s32 unk28;
    Hero hero;
    Hero heroCopy;
    u8 reserved131C[4];
} MenuCBBiosTrainer;

typedef struct _MENUCBWORK {
    u8 reserved0[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 reserved10[4];
    s32 unk14;
    MenuCBBiosTrainer trainers[4];
    MenuCBBiosTrainer orgTrainers[4];
    MenuCBRule rules[6];
    u8 reserved9C78[0xB0E0 - 0x9C78];
    s32 unkB0E0;
    u8 reservedB0E4[0xB5F4 - 0xB0E4];
} _MENUCBWORK;

extern _MENUCBWORK _CB;
extern _MENUCBWORK *pGCB;
#endif
