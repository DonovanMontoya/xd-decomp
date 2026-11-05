#include <dolphin/types.h>

/* The final kind-zero record terminates the action search. */
typedef struct FightActionData { u16 kind; s32 buff; } FightActionData;

FightActionData fight_action_data_syuuryou[] = {
    {14, 0},
    {15, 2},
    {15, 3},
    {15, 4},
    {15, 5},
    {15, 6},
    {15, 7},
    {16, 0},
    {17, 0},
    {0, 0},
};
