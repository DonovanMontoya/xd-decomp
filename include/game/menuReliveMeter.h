#ifndef GAME_MENU_RELIVE_METER_H
#define GAME_MENU_RELIVE_METER_H

#include <dolphin/types.h>

struct Pokemon;
struct DarkPokemon;

#ifdef __cplusplus
extern "C" {
#endif

void menuDrawReliveUpdate(void);
void menuDrawReliveMeter(struct Pokemon* pokemon, s32 width, s32 height, s32 layerID);
void menuDrawReliveMeter3(struct Pokemon* pokemon, s32 x, s32 y, s32 width, s32 height, u8 alpha, s32 layerID);
void menuDrawReliveMeterByDarkPokemon(struct DarkPokemon* pokemon, s32 x, s32 y, s32 width, s32 height,
                                      u8 alpha, s32 layerID);

#ifdef __cplusplus
}
#endif

#endif
