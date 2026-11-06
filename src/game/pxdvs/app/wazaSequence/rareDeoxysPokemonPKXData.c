#include <dolphin/types.h>

#pragma force_active on

/* Group and resource IDs loaded by the ModelSequence constructors. */
typedef struct PkxEntry {
    u32 group;
    u32 resource;
} PkxEntry;

PkxEntry rare_deoxys_pokemon_pkx_data[] = {
    { 1918, 0x11A31E00 },
    { 2078, 0x17C31E00 },
    { 2079, 0x17C41E00 },
    { 2080, 0x17C51E00 },
};

u32 rare_deoxys_pokemon_pkx_data_number = sizeof(rare_deoxys_pokemon_pkx_data) / sizeof(rare_deoxys_pokemon_pkx_data[0]);

#pragma force_active reset
