#include <dolphin/types.h>

/* itemBios.cpp reads a message ID and 25 signed nature adjustments, stride 32. */
typedef struct TasteDataRecord {
    s32 nigateMsgDataId;
    s8 aisyou[25];
} TasteDataRecord;
TasteDataRecord taste_data[] = {
    { 20419, { 0, 1, 1, 1, 1, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0 } },
    { 20420, { 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 1, 1, 1, 0, 1, 0, 0, 0, -1, 0 } },
    { 20421, { 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 1, 1, 0, 1, 1, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0 } },
    { 20422, { 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 1, 1, 1, 1, 0 } },
    { 20423, { 0, -1, 0, 0, 0, 1, 0, 1, 1, 1, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0 } },
};

u32 taste_data_number = sizeof(taste_data) / sizeof(taste_data[0]);
