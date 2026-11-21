#ifndef GAME_FIGHT_TRAINER_DB_HPP
#define GAME_FIGHT_TRAINER_DB_HPP

#include <dolphin/types.h>

extern "C" {
u16 fightTrainerDB_GetTemotiPokemonId(u16 id, u8 index);
void fightTrainerDB_SetTemotiPokemonId(u16 id, u8 index, u16 value);
u8 fightTrainerPokemonDB_GetStatusRnd(u16 id, u8 index);
u8 fightTrainerPokemonDB_GetStatusEffort(u16 id, u8 index);
u8 fightTrainerPokemonDB_GetLevel(u16 id);
u8 fightTrainerPokemonDB_GetTokuseiFlag(u16 id);
u16 fightTrainerPokemonDB_GetPokemonDataId(u16 id);
u16 fightTrainerPokemonDB_GetItemDataId(u16 id);
u16 fightTrainerPokemonDB_GetWazaDataId(u16 id, u8 index);
u8 fightTrainerPokemonDB_GetFriend(u16 id);
u8 fightTrainerPokemonDB_GetSexDataId(u16 id);
u8 fightTrainerPokemonDB_GetSeikakuDataId(u16 id);
u8 fightTrainerPokemonDB_GetKeyPlayerFlag(u16 id);
u8 fightTrainerPokemonDB_GetPartDataId(u16 id);
}

#endif
