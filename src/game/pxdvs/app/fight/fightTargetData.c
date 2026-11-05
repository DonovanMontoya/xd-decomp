#include <dolphin/types.h>

typedef struct FightTargetData { u8 statusKind; u8 relativeFlag; u32 buff; } FightTargetData;

FightTargetData fight_target_data[] = {
    {0, 0, 0},
    {7, 1, 0},
    {8, 1, 0},
    {8, 1, 0},
    {8, 0, 0},
    {8, 0, 0},
    {9, 1, 0},
    {9, 1, 1},
    {9, 0, 0},
    {9, 1, 0},
    {9, 1, 1},
    {9, 0, 0},
    {5, 1, 0},
    {5, 1, 1},
    {5, 0, 0},
    {5, 1, 0},
    {5, 1, 1},
    {5, 0, 269},
    {5, 0, 270},
    {5, 0, 0},
    {5, 0, 269},
    {5, 0, 269},
    {5, 0, 269},
    {5, 0, 0},
    {5, 0, 0},
    {5, 0, 0},
    {9, 0, 0},
    {6, 0, 0},
    {8, 0, 0},
    {4, 0, 0},
};

u32 fight_target_data_number = 30;
