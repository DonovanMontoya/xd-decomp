#include <dolphin/types.h>

#pragma force_active on

/* Group and resource IDs loaded by the ModelSequence constructors. */
typedef struct PkxEntry {
    u32 group;
    u32 resource;
} PkxEntry;

PkxEntry unknown_pokemon_pkx_data[] = {
    { 504, 0x04131E00 },
    { 505, 0x04141E00 },
    { 506, 0x04151E00 },
    { 507, 0x04161E00 },
    { 508, 0x04171E00 },
    { 509, 0x04181E00 },
    { 510, 0x04191E00 },
    { 511, 0x041A1E00 },
    { 512, 0x041B1E00 },
    { 513, 0x041C1E00 },
    { 514, 0x041D1E00 },
    { 515, 0x041E1E00 },
    { 516, 0x04531E00 },
    { 517, 0x041F1E00 },
    { 518, 0x04201E00 },
    { 519, 0x04211E00 },
    { 520, 0x04221E00 },
    { 521, 0x04231E00 },
    { 522, 0x04241E00 },
    { 523, 0x04251E00 },
    { 524, 0x04261E00 },
    { 525, 0x04271E00 },
    { 526, 0x04281E00 },
    { 527, 0x04291E00 },
    { 528, 0x042A1E00 },
    { 529, 0x04541E00 },
    { 862, 0x05BE1E00 },
    { 863, 0x05BF1E00 },
};

u32 unknown_pokemon_pkx_data_number = sizeof(unknown_pokemon_pkx_data) / sizeof(unknown_pokemon_pkx_data[0]);

#pragma force_active reset
