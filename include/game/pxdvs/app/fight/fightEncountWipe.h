#ifndef GAME_PXDVS_APP_FIGHT_FIGHT_ENCOUNT_WIPE_H
#define GAME_PXDVS_APP_FIGHT_FIGHT_ENCOUNT_WIPE_H

#include <dolphin/types.h>

typedef void (*FightEncountWipeFunction)(void);

typedef struct FightEncountWipeRecord {
    u8 snapshotUse;
    u16 effectSndId;
    f32 effectTime;
    FightEncountWipeFunction function;
} FightEncountWipeRecord;

#endif
