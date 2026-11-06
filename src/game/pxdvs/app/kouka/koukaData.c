#include <dolphin/types.h>

/* Field widths and signed values follow koukaBios.cpp. */
typedef struct KoukaDataRecord {
    u8 statusKind;
    u8 var;
    u16 status;
    u16 link;
    s16 value[2];
} KoukaDataRecord;
KoukaDataRecord kouka_data[] = {
    { 0, 0, 0, 0, { 0, 0 } },
    { 5, 2, 131, 0, { 20, 0 } },
    { 7, 0, 10, 0, { 78, 0 } },
    { 7, 0, 10, 0, { 80, 0 } },
    { 7, 0, 10, 0, { 79, 0 } },
    { 7, 0, 10, 0, { 81, 0 } },
    { 7, 0, 10, 0, { 83, 0 } },
    { 7, 0, 10, 0, { 85, 0 } },
    { 7, 0, 10, 0, { 84, 0 } },
};

u32 kouka_data_number = sizeof(kouka_data) / sizeof(kouka_data[0]);
