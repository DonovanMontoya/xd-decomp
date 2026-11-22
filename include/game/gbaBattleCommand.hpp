#ifndef GAME_GBA_BATTLE_COMMAND_HPP
#define GAME_GBA_BATTLE_COMMAND_HPP

#include <dolphin/types.h>

struct FIGHT_TRAINER;

extern "C" {
u32 menuFightOpenGBAMain(s32 port, FIGHT_TRAINER* trainer, s32 slot, u16 fightType);
u32 menuFightOpenGBAIrekae(s32 port, FIGHT_TRAINER* trainer, s32 slot, u16 fightType);
u32 gbaCommandRequestAction(s32 port, FIGHT_TRAINER* trainer, s32 slot, s32 irekae);
u32 gbaCommandGetAction(u32 command);
u32 gbaCommandGetGBAChangePokemon(u32 command);
u32 gbaCommandGetWazaDataId(u32 command);
u32 gbaCommandGetWazaTarget(u32 command);
}

#endif
