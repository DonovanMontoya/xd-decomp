#include <dolphin/types.h>

/* The final kind-zero record terminates the action search. */
typedef struct FightActionData { u16 kind; s32 buff; } FightActionData;

FightActionData fight_action_data_turn[] = {
    {7, 0},
    {8, 0},
    {9, 0},
    {10, 0},
    {11, 0},
    {12, 0},
    {13, 0},
    {0, 0},
};
