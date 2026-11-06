#include <dolphin/types.h>

#pragma force_active on

/* Group and resource IDs loaded by the ModelSequence constructors. */
typedef struct PkxEntry {
    u32 group;
    u32 resource;
} PkxEntry;

PkxEntry deoxys_pokemon_pkx_data[] = {
    { 902, 0x06681E00 },
    { 2075, 0x17C01E00 },
    { 2076, 0x17C11E00 },
    { 2077, 0x17C21E00 },
};

u32 deoxys_pokemon_pkx_data_number = sizeof(deoxys_pokemon_pkx_data) / sizeof(deoxys_pokemon_pkx_data[0]);

#pragma force_active reset
