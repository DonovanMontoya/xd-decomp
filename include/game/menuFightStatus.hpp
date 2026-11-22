#ifndef GAME_MENU_FIGHT_STATUS_HPP
#define GAME_MENU_FIGHT_STATUS_HPP

#include <dolphin/types.h>

extern "C" {
void menuFightStatusSetActive(u32 menuId, u32 active);
void menuFightStatusSetHP(s32 menuId, s16 hp);
void menuFightStatusStartAnimHP(s32 menuId, s16 hp);
s32 menuFightStatusWaitAnimeHP(s32 menuId, u8 wait);
void menuFightStatusStartAnimEXP(s32 menuId, u32 exp);
s32 menuFightStatusWaitAnimeEXP(s32 menuId, u8 wait);

void fightMenuFightStatusStartAnimHP(s32 menuId, s16 hp);
}

#endif
