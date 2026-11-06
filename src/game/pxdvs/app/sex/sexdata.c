#include <dolphin/types.h>

/* sexGetPokemonSexRaitoKotei indexes eight-byte records and reads ratio. */
typedef struct SexDataRecord {
    u8 ratio;
    u32 unknown04;
} SexDataRecord;
SexDataRecord sex_data[] = {
    { 0, 3301 },
    { 254, 3302 },
    { 255, 3303 },
};

u32 sex_data_number = sizeof(sex_data) / sizeof(sex_data[0]);
