#ifndef FIGHT_FLOOR_HPP
#define FIGHT_FLOOR_HPP

// Canonical layout of the battle state (fight_floor, 0x804A1730, 0xE318 bytes) and the structs it embeds.
// Offsets come from fightFloorBios / fightSideBios / fightTrainerBios / fightPokemonBios accessors and the
// strides used by fightFloorDB.cpp, fightSideDB.cpp. See build/findings/trackA.md.
#include <dolphin/types.h>
#include <libc/stddef.h>
#include <game/pxdvs/app/hero/hero.hpp>
#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>

// One trainer taking part in a battle (0x3744 bytes). fight_floor trainer address:
//   fight_floor + 0x14 (floor header) + 0x4 (side header) ... = fight_floor + 0x78 + side * 0x6EF0 + slot * 0x3744
struct FIGHT_TRAINER {
    u16 trainerDataId;               // 0x0 (0x1388 = the player)
    u8 reserved2[2];                 // 0x2
    Hero hero;                       // 0x4, copy of the trainer's Hero (heroBiosCopy, 0x978 bytes)
    FightPokemon fightPokemon[6];    // 0x97C, 0x300 bytes each
    FightOutPokemon fightOutPokemon[2]; // 0x1B7C, 0x894 bytes each (battlefield Pokemon)
    u8 unk2CA4[0x3540 - 0x2CA4];     // 0x2CA4
    u8 controllerId;                 // 0x3540
    u8 unk3541[0x3744 - 0x3541];     // 0x3541
};

// One side of the battle (0x6EF0 bytes), fight_floor + 0x14 + side * 0x6EF0.
struct FightSide {
    u16 fightSideDataId;             // 0x0
    u8 reserved2[2];                 // 0x2
    FightJoutai joutai[6];           // 0x4, 0x10 bytes each
    FIGHT_TRAINER trainer[2];        // 0x64
    u8 makibisiCheckFlag;            // 0x6EEC
    u8 reserved6EED[3];              // 0x6EED
};

typedef char FIGHT_TRAINER_size_check[(sizeof(FIGHT_TRAINER) == 0x3744) ? 1 : -1];
typedef char FIGHT_TRAINER_hero_check[(offsetof(FIGHT_TRAINER, hero) == 0x4) ? 1 : -1];
typedef char FIGHT_TRAINER_fightPokemon_check[(offsetof(FIGHT_TRAINER, fightPokemon) == 0x97C) ? 1 : -1];
typedef char FIGHT_TRAINER_out_check[(offsetof(FIGHT_TRAINER, fightOutPokemon) == 0x1B7C) ? 1 : -1];
typedef char FIGHT_TRAINER_controller_check[(offsetof(FIGHT_TRAINER, controllerId) == 0x3540) ? 1 : -1];
typedef char FightSide_size_check[(sizeof(FightSide) == 0x6EF0) ? 1 : -1];
typedef char FightSide_joutai_check[(offsetof(FightSide, joutai) == 0x4) ? 1 : -1];
typedef char FightSide_trainer_check[(offsetof(FightSide, trainer) == 0x64) ? 1 : -1];
typedef char FightSide_makibisi_check[(offsetof(FightSide, makibisiCheckFlag) == 0x6EEC) ? 1 : -1];

struct StockPokemon { Pokemon pokemon; u8 ballId; u8 reserved[3]; };
// Whole battle state, global fight_floor (0x804A1730), size 0xE318.
struct FIGHT_FLOOR {
    u8 reserved0[0x10];
    u16 turnCount;
    u16 encountDataId;
    FightSide side[2];             // 0x14
    void* attackPokemonPtr;
    void* defensePokemonPtr;
    void* escapePokemonPtr;
    void* irekaePokemonPtr;
    void* kizetuPokemonPtr;
    void* tuikakoukaPokemonPtr;
    void* tokuseiPokemonPtr;
    void* itemPokemonPtr;
    void* appointPokemonPtr;
    void* appointTrainerPtr;
    void* appointWazaPtr;
    void* appointSidePtr;
    void* appointItemPtr;
    u32 attackMsgId, criticalMsgId, wazaEffectMsgId;
    s32 appointMsgId;
    u16 appointPokemonDataId, appointWazaDataId, appointItemDataId, appointTokuseiDataId;
    s16 fightPokemonEntryCnt;
    u8 reservedDE42[0x2];
    void* fightOutPokemon[8];
    u16 firstAttackRnd;
    u8 stockPokemonNum;
    u8 reservedDE67[0x1];
    StockPokemon stockPokemon[6];
};
typedef char FIGHT_FLOOR_size_check[(sizeof(FIGHT_FLOOR) == 0xE318) ? 1 : -1];
typedef char FIGHT_FLOOR_side_check[(offsetof(FIGHT_FLOOR, side) == 0x14) ? 1 : -1];

#endif
