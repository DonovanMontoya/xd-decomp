#ifndef GAME_FIGHT_TRAINER_DB_HPP
#define GAME_FIGHT_TRAINER_DB_HPP

#include <dolphin/types.h>

extern "C" {
u16 fightTrainerDB_GetTemotiPokemonId(u16 id, u8 index);
void fightTrainerDB_SetTemotiPokemonId(u16 id, u8 index, u16 value);
}

#endif
