#include <dolphin/types.h>

/* The final kind-zero record terminates the action search. */
typedef struct FightActionData { u16 kind; s32 buff; } FightActionData;

FightActionData fight_action_data_kaisi[] = {
    {1, 0},
    {3, 4},
    {3, 5},
    {4, 4},
    {4, 5},
    {2, 0},
    {5, 0},
    {6, 0},
    {0, 0},
};
