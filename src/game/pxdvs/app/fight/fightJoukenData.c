#include <dolphin/types.h>

typedef struct FightJoukenValue {
    u8 kind; u8 hoseiFlag; s16 kake; s16 waru; u16 target; u16 buff;
} FightJoukenValue;
typedef struct FightJoukenData {
    u8 form; u16 link; FightJoukenValue value[2];
} FightJoukenData;

FightJoukenData fight_jouken_data[] = {
    {1, 0, {{1, 0, 1, 1, 0, 0}, {1, 0, 1, 1, 1, 0}}},
    {1, 0, {{1, 0, 1, 1, 1, 0}, {1, 0, 1, 1, 1, 0}}},
    {1, 0, {{1, 0, 1, 1, 0, 0}, {1, 0, 1, 1, 1, 0}}},
    {1, 0, {{2, 0, 1, 1, 1, 2}, {1, 0, 1, 1, 1, 0}}},
    {1, 0, {{2, 0, 1, 1, 1, 4}, {1, 0, 1, 1, 1, 0}}},
    {1, 0, {{2, 0, 1, 1, 1, 5}, {1, 0, 1, 1, 1, 0}}},
    {1, 0, {{3, 0, 0, 78, 1, 11}, {1, 0, 1, 1, 2, 0}}},
    {1, 0, {{3, 0, 0, 81, 1, 11}, {1, 0, 1, 1, 2, 0}}},
};

u32 fight_jouken_data_number = 8;
