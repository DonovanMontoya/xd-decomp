#include <dolphin/types.h>

/* The final kind-zero record terminates the action search. */
typedef struct FightActionData { u16 kind; s32 buff; } FightActionData;

FightActionData fight_action_data_waza[] = {
    {19, 0},
    {0, 0},
};
