#include <dolphin/types.h>

/* tenkouBios.cpp reads solar at 0 and the initial message at 8, stride 24. */
typedef struct TenkouDataRecord {
    u8 solar;
    u8 unknown01;
    u16 unknown02;
    u32 unknown04;
    u32 initialMessage;
    u32 messages[3];
} TenkouDataRecord;
TenkouDataRecord tenkou_data[] = {
    { 1, 0, 78, 0, 0, { 0, 0, 0 } },
    { 1, 0, 79, 0, 0, { 20276, 20277, 20278 } },
    { 0, 0, 80, 0, 20361, { 20268, 20270, 20272 } },
    { 0, 0, 81, 0, 20362, { 20273, 20274, 20275 } },
    { 0, 0, 83, 0, 0, { 20279, 20280, 20281 } },
    { 0, 0, 82, 0, 0, { 20461, 20462, 20463 } },
};

u32 tenkou_data_number = sizeof(tenkou_data) / sizeof(tenkou_data[0]);
