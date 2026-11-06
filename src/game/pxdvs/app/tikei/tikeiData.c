#include <dolphin/types.h>

/* tikeiBios.cpp uses a 12-byte stride, with type/effect/move at 0/2/4. */
typedef struct TikeiDataRecord {
    u8 type;
    u8 reserved01;
    u16 effect;
    u16 move;
    u16 unknown06;
    u32 unknown08;
} TikeiDataRecord;
TikeiDataRecord tikei_data[] = {
    { 12, 0, 2, 78, 0, 0 },
    { 12, 0, 1, 75, 0, 0 },
    { 4, 0, 27, 89, 0, 0 },
    { 11, 0, 23, 56, 0, 0 },
    { 11, 0, 22, 57, 0, 0 },
    { 11, 0, 24, 61, 0, 0 },
    { 5, 0, 7, 157, 0, 0 },
    { 5, 0, 8, 247, 0, 0 },
    { 0, 0, 5, 129, 0, 0 },
};

u32 tikei_data_number = sizeof(tikei_data) / sizeof(tikei_data[0]);
