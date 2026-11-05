#include <dolphin/types.h>

#pragma force_active on

/* Species-specific rare model resources searched by the ModelSequence constructor. */
typedef struct RarePkxEntry {
    u16 id;
    u32 group;
    u32 resource;
} RarePkxEntry;

RarePkxEntry rare_pokemon_pkx_data[] = {
    { 3, 1884, 0x11811E00 },
    { 6, 1885, 0x11821E00 },
    { 9, 1886, 0x11831E00 },
    { 130, 1887, 0x11841E00 },
    { 144, 1888, 0x11851E00 },
    { 145, 1889, 0x11861E00 },
    { 146, 1890, 0x11871E00 },
    { 150, 1891, 0x11891E00 },
    { 151, 1892, 0x11881E00 },
    { 154, 1893, 0x118A1E00 },
    { 157, 1894, 0x118B1E00 },
    { 160, 1895, 0x118C1E00 },
    { 164, 1896, 0x118D1E00 },
    { 243, 1897, 0x118E1E00 },
    { 244, 1898, 0x118F1E00 },
    { 245, 1899, 0x11901E00 },
    { 249, 1900, 0x11911E00 },
    { 250, 1901, 0x11921E00 },
    { 251, 1902, 0x11931E00 },
    { 277, 1903, 0x11941E00 },
    { 278, 1904, 0x11951E00 },
    { 279, 1905, 0x11961E00 },
    { 280, 1906, 0x11971E00 },
    { 281, 1907, 0x11981E00 },
    { 282, 1908, 0x11991E00 },
    { 283, 1909, 0x119A1E00 },
    { 284, 1910, 0x119B1E00 },
    { 285, 1911, 0x119C1E00 },
    { 404, 1912, 0x119D1E00 },
    { 405, 1913, 0x119E1E00 },
    { 406, 1914, 0x119F1E00 },
    { 407, 1915, 0x11A01E00 },
    { 408, 1916, 0x11A11E00 },
    { 409, 1917, 0x11A21E00 },
    { 410, 1918, 0x11A31E00 },
};

u32 rare_pokemon_pkx_data_number = sizeof(rare_pokemon_pkx_data) / sizeof(rare_pokemon_pkx_data[0]);

#pragma force_active reset
