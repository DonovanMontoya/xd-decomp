#include <dolphin/types.h>

typedef struct FightKoukaData { u16 condition; u16 target; u16 effect; } FightKoukaData;

FightKoukaData fight_kouka_data[] = {
    {2, 0, 0},
    {6, 1, 2},
};

u32 fight_kouka_data_number = 2;
