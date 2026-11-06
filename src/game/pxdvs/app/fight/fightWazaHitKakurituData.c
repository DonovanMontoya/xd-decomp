#include <dolphin/types.h>

typedef struct FightRatio { u8 kake; u8 waru; } FightRatio;

FightRatio fight_waza_hit_kakuritu_data[] = {
    {33, 100},
    {36, 100},
    {43, 100},
    {50, 100},
    {60, 100},
    {75, 100},
    {1, 1},
    {133, 100},
    {166, 100},
    {2, 1},
    {233, 100},
    {133, 50},
    {3, 1},
};

u32 fight_waza_hit_kakuritu_data_number = 13;
