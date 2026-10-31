#include <dolphin/types.h>

#pragma force_active on

typedef struct DbgMenuPokemonKeyInfo {
    u16 held;
    u16 unk2;
    u16 unk4;
    u16 trigger;
} DbgMenuPokemonKeyInfo;

typedef struct DbgMenuPokemonWindow {
    u8 reserved0[4];
    s32 menu;
    u8 reserved8[0x60];
    u32 pokemon;
    s32* out;
    u8 reserved70[0x18];
    s32 value;
    u8 reserved8C[0x12];
    s16 selected;
    u8 reservedA0[4];
    u8 finished;
} DbgMenuPokemonWindow;

#ifdef __cplusplus
extern "C" {
#endif
void* menuDataBiosGetPtr(s32);
s32 menuGetCursorItemID(s32);
u8 pokemonCheckValid(u32);
u32 pokemonGetStatus(s32, u32, u16, u16);
DbgMenuPokemonKeyInfo* windowGetKeyInfo(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

void dbgMenuPokemonEditButton(DbgMenuPokemonWindow* window) {
    u32 pokemon = window->pokemon;
    s32* out = window->out;
    u16 repeat;
    u16 held;
    s32 delta;
    s32 id;

    if (window != 0) {
        repeat = (u16)windowGetKeyInfo()->trigger;
        held = (u16)windowGetKeyInfo()->held;
        if (((repeat & 0x20) != 0)) {
            window->value = -1;
            window->finished = 1;
        } else if (((repeat & 0x10) != 0)) {
            window->value = -2;
            window->finished = 1;
        } else if (pokemon == 0) {
            window->value = -1;
            window->finished = 1;
        } else {
            delta = 0;
            if (((repeat & 0x80) != 0) && ((held & 0x200) != 0) && ((held & 0x400) != 0)) {
                delta = 100;
            } else if (((repeat & 0x40) != 0) && ((held & 0x200) != 0) && ((held & 0x400) != 0)) {
                delta = -100;
            } else if (((repeat & 0x80) != 0) && ((held & 0x200) != 0)) {
                delta = 10;
            } else if (((repeat & 0x40) != 0) && ((held & 0x200) != 0)) {
                delta = -10;
            } else if (((repeat & 0x80) != 0)) {
                delta = 1;
            } else if (((repeat & 0x40) != 0)) {
                delta = -1;
            } else if (((repeat & 0x100) != 0) && ((held & 0x200) != 0)) {
                delta = 0xFFFF;
            } else if (((repeat & 0x100) != 0)) {
                delta = -0xFFFF;
            }
            if (!pokemonCheckValid(pokemon)) {
                window->selected = 0;
                id = 0x16;
            } else {
                menuDataBiosGetPtr(window->menu);
                id = menuGetCursorItemID(window->menu);
            }
            if (delta != 0) {
                if (out != 0) {
                    *out = delta;
                }
                window->value = id;
                window->finished = 1;
            }
        }
    }
}

u16* GSmsgGetGSchar(s32);
u32 fightTrainerGetStatus(s32,u32,u32,u16);
void fightTrainerSetStatus(s32,u32,u32,u16,u32);
s32 gamedataGetStatus(s32, s32);
u8 itemDataCheckValid(u16);
u8 joutaiDataBiosGetMaxCount(u16);
void menuCloseCustom(s32, s32, s32);
s32 menuOpen(s32, s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
void menuSubCloseNumberInput();
u8 menuSubOpenNumberInput(s32, s32 *, s32, s32, s32, s32);
u16 pokemonBiosGetPokemonDataId(s32);
void pokemonBiosSetEventGetFlag(s32, s32);
u32 pokemonCheckRare(s32);
u8 pokemonCheckWriteJoutaiDataId(s32, u16);
void pokemonCreate(s32, s32, s32, s32);
u32 pokemonCreateRndFit(s32,s8,s8,s8,u32);
void pokemonDoItemSoubi(s32, u16, s32);
s16 pokemonGetCountAsJoutaiDataId(s32, u16);
u16 pokemonGetJoutaiDataId(s32);
s8 pokemonGetKaisuuJoutaiDataId(s32, u16);
s8 pokemonGetNowKaisuuJoutaiDataId(s32, u16);
u32 pokemonGetNowLevelToExp(s32);
u16 pokemonGetSoubiItemDataId(s32);
void pokemonGrowBasisStatus(s32, u32);
void pokemonInit(s32);
void pokemonInitDarkPokemon(s32);
void pokemonInitJoutai(s32);
void pokemonInitJoutaiDataId(s32, s32);
u8 pokemonIsDarkPokemon(s32);
void pokemonSetCatchStatus(s32, s32, s32, s32, s32, s32, s32 *);
void pokemonSetCountAsJoutaiDataId(s32, u16, s16);
void pokemonSetDarkPokemonStatus(s32, u16);
void pokemonSetKaisuuJoutaiDataId(s32, u16, s8);
void pokemonSetNowKaisuuJoutaiDataId(s32, u16, s8);
void pokemonSetStatus(s32,u32,u16,u16,u32);
void pokemonSetTokuseiFlag(s32, u32);
u8 pokemonWazaCheckValid(s32, s32);
void pokemonWazaCreate(s32, s32, u16);
u8 pokemonWazaGetMaxPP(s32, s32);
void pokemonWazaInit(s32, s32);
void pokemonWriteJoutaiDataId(s32, u16, s32);
extern u32 darkPokemonList_number;
extern u32 *fight_trainer_pokemon_part_data_number;
extern u32 *item_data_index_number;
extern u32 *pokemon_data_number;
extern u32 *pokemon_seikaku_data_number;
extern u32 sex_data_number;
u8 wazaCheckDarkWaza(u16);
typedef struct {u32 words[49];} PokemonBackup;
static u16 gRibbonStat[0x12] = {
    0xA3,
    0xA4,
    0xA5,
    0xA6,
    0xA7,
    0xA8,
    0xA9,
    0xAA,
    0xAB,
    0xAC,
    0xAD,
    0xAE,
    0xAF,
    0xB0,
    0xB1,
    0xB2,
    0xB3,
    0xB4,
};
static s32 gRibbonNum;
static s32 pokemon_edit_value;
static s32 dbgMenuPokemonEditSubGetTotalEffort(s32);
#pragma opt_loop_invariants off
#pragma opt_common_subs off
s32 dbgMenuPokemonEditSub(s32 arg0, u8 arg1, s8 *arg2, s8 *arg3, s8 *arg4, s8 *arg5) {
    PokemonBackup backup;
    u32 origin[1]={0};
    u16 individual[6]={0x93,0x94,0x95,0x96,0x97,0x98};
    u16 effort[6]={0x8d,0x8e,0x8f,0x90,0x91,0x92};
    s32 editValue;
    s32 number;
    s32 temp_r0_2;
    s32 temp_r22;
    s8 temp_r22_2;
    s32 temp_r29_2;
    s32 temp_r29_3;
    s32 temp_r3;
    s32 temp_r3_10;
    s32 temp_r3_20;
    s32 temp_r3_22;
    s32 temp_r3_26;
    s32 temp_r3_27;
    s32 temp_r3_6;
    s32 temp_r3_7;
    s32 temp_r3_8;
    s32 temp_r3_9;
    s32 temp_r4;
    s32 temp_r5;
    s32 var_r0;
    s32 var_r0_10;
    s32 var_r0_11;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    s32 var_r0_8;
    s32 var_r0_9;
    s32 var_r7;
    s32 var_r7_10;
    s32 var_r7_11;
    s32 var_r7_12;
    s32 var_r7_13;
    s32 var_r7_14;
    s32 var_r7_15;
    s32 var_r7_16;
    s32 var_r7_17;
    s32 var_r7_18;
    s32 var_r7_19;
    s32 var_r7_20;
    s32 var_r7_21;
    s32 var_r7_22;
    s32 var_r7_23;
    s32 var_r7_2;
    s32 var_r7_3;
    s32 var_r7_4;
    s32 var_r7_5;
    s32 var_r7_6;
    s32 var_r7_7;
    s32 var_r7_8;
    s32 var_r7_9;
    s32 temp_r0;
    u16 temp_r27;
    u32 temp_r3_11;
    u32 temp_r3_12;
    u32 temp_r3_13;
    u32 temp_r3_14;
    u32 temp_r3_15;
    u32 temp_r3_16;
    u32 temp_r3_17;
    u32 temp_r3_18;
    s32 var_r20;
    u32 temp_r3_19;
    u32 temp_r3_21;
    u32 temp_r3_28;
    u32 temp_r3_5;
    u8 temp_r3_3;
    u8 var_r29;
    u32 temp_r29;
    s32 var_r4;
    s32 i;
    u32 personality;
    s32 count;

    if (arg2 != 0) {
        *arg2 = 0;
    }
    if (arg3 != 0) {
        *arg3 = 0;
    }
    if (arg4 != 0) {
        *arg4 = 0;
    }
    if (arg5 != 0) {
        *arg5 = 0;
    }
    backup=*(PokemonBackup*)arg0;
    if (pokemonCheckValid(arg0) == 0) {
        pokemonCreate(arg0, 0x115, 1, gamedataGetStatus(0, 1));
        pokemonSetCatchStatus(arg0, 0, 1, 0, 2, 0, (s32 *) origin);
    }
    temp_r27 = pokemonGetStatus(arg0, 0, 0xC9, 0);
loop_11:
    pokemon_edit_value = 0;
    temp_r3 = menuOpenCustom(0xD, 0, 0, 0, 1, 2, arg0, &pokemon_edit_value);
    temp_r22 = pokemon_edit_value;
    if (temp_r3 == -1) {
        menuCloseCustom(0xD, 0, 1);
        *(PokemonBackup*)arg0=backup;
        return -1;
    }
    if (temp_r3 == -2) {
        if(menuOpen(0x55,1)!=0) {
            menuCloseCustom(0x55,0,1);
            goto loop_11;
        }
        goto finish;
    }

    if (temp_r22 != 0) {
        var_r29 = 0;
        switch (temp_r3) {
        case 0x16:
            var_r20 = pokemonGetStatus(arg0, 0, 0x6E, 0);
            var_r20 += temp_r22;
            if (var_r20 < 0) {
                var_r20 = 0;
            }
            temp_r3_5 = *pokemon_data_number;
            if ((u32) var_r20 >= temp_r3_5) {
                var_r20 = temp_r3_5 - 1;
            }
            pokemonSetStatus(arg0, 0, 0x6E, 0, var_r20);
            pokemonSetStatus(arg0, 0, 0x77, 0, (s32)GSmsgGetGSchar(pokemonGetStatus(0, (s32) (u16) var_r20, 1, 0)));
            pokemonSetTokuseiFlag(arg0, 0U);
            var_r29 = 1;
            if (arg2 != 0) {
                *arg2 = 1;
            }
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x18:
            editValue = pokemonGetStatus(arg0, 0, 0x7A, 0);
            editValue += temp_r22;
            if (editValue <= 0) {
                editValue = 1;
            }
            if (editValue > 0x64) {
                editValue = 0x64;
            }
            pokemonSetStatus(arg0, 0, 0x7A, 0, editValue);
            var_r29 = 1;
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x1A:
            temp_r3_6 = pokemonGetStatus(arg0, 0, 0x79, 0);
            if ((u32) (temp_r22 + 0x10000) == 1U) {
                var_r20 = 1;
                goto block_43;
            }
            if (temp_r22 == 65535) {
                var_r20 = 0x1E8480;
                goto block_43;
            }
            if (menuSubOpenNumberInput(temp_r3_6, &number, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
            } else {
                var_r20 = number;
                menuSubCloseNumberInput();
                if (var_r20 <= 0) {
                    var_r20 = 1;
                }
                if (var_r20 > 0x1E8480) {
                    var_r20 = 0x1E8480;
                }
block_43:
                pokemonSetStatus(arg0, 0, 0x79, 0, var_r20);
                var_r29 = 1;
                if (arg3 != 0) {
                    *arg3 = 1;
                }
            }
            break;
        case 0x1C:
            var_r20 = pokemonGetStatus(arg0, 0, 0x83, 0);
            var_r20 += temp_r22;
            if (var_r20 < 0) {
                var_r20 = 0;
            }
            if (var_r20 > (s32)pokemonGetStatus(arg0, 0, 0x87, 0)) {
                var_r20 = pokemonGetStatus(arg0, 0, 0x87, 0);
            }
            pokemonSetStatus(arg0, 0, 0x83, 0, var_r20);
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x26:
            editValue = pokemonGetStatus(arg0, 0, 0x87, 0);
            editValue += temp_r22;
            if (editValue < 0) {
                editValue = 0;
            }
            if (editValue > 0x3E7) {
                editValue = 0x3E7;
            }
            pokemonSetStatus(arg0, 0, 0x87, 0, editValue);
            pokemonSetStatus(arg0, 0, 0x83, 0, editValue);
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x27:
            var_r7_2 = pokemonGetStatus(arg0, 0, 0x88, 0);
            var_r7_2 += temp_r22;
            if (var_r7_2 < 0) {
                var_r7_2 = 0;
            }
            if (var_r7_2 > 0x3E7) {
                var_r7_2 = 0x3E7;
            }
            pokemonSetStatus(arg0, 0, 0x88, 0, var_r7_2);
            break;
        case 0x28:
            var_r7_3 = pokemonGetStatus(arg0, 0, 0x89, 0);
            var_r7_3 += temp_r22;
            if (var_r7_3 < 0) {
                var_r7_3 = 0;
            }
            if (var_r7_3 > 0x3E7) {
                var_r7_3 = 0x3E7;
            }
            pokemonSetStatus(arg0, 0, 0x89, 0, var_r7_3);
            break;
        case 0x29:
            var_r7_4 = pokemonGetStatus(arg0, 0, 0x8C, 0);
            var_r7_4 += temp_r22;
            if (var_r7_4 < 0) {
                var_r7_4 = 0;
            }
            if (var_r7_4 > 0x3E7) {
                var_r7_4 = 0x3E7;
            }
            pokemonSetStatus(arg0, 0, 0x8C, 0, var_r7_4);
            break;
        case 0x2A:
            var_r7_5 = pokemonGetStatus(arg0, 0, 0x8A, 0);
            var_r7_5 += temp_r22;
            if (var_r7_5 < 0) {
                var_r7_5 = 0;
            }
            if (var_r7_5 > 0x3E7) {
                var_r7_5 = 0x3E7;
            }
            pokemonSetStatus(arg0, 0, 0x8A, 0, var_r7_5);
            break;
        case 0x2B:
            var_r7_6 = pokemonGetStatus(arg0, 0, 0x8B, 0);
            var_r7_6 += temp_r22;
            if (var_r7_6 < 0) {
                var_r7_6 = 0;
            }
            if (var_r7_6 > 0x3E7) {
                var_r7_6 = 0x3E7;
            }
            pokemonSetStatus(arg0, 0, 0x8B, 0, var_r7_6);
            break;
        case 0x2C:
            var_r7_7 = pokemonGetStatus(arg0, 0, 0x93, 0);
            var_r7_7 += temp_r22;
            if (var_r7_7 < 0) {
                var_r7_7 = 0;
            }
            if (var_r7_7 > 0x1F) {
                var_r7_7 = 0x1F;
            }
            pokemonSetStatus(arg0, 0, 0x93, 0, var_r7_7);
            var_r29 = 1;
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x2D:
            var_r7_8 = pokemonGetStatus(arg0, 0, 0x94, 0);
            var_r7_8 += temp_r22;
            if (var_r7_8 < 0) {
                var_r7_8 = 0;
            }
            if (var_r7_8 > 0x1F) {
                var_r7_8 = 0x1F;
            }
            pokemonSetStatus(arg0, 0, 0x94, 0, var_r7_8);
            var_r29 = 1;
            break;
        case 0x2E:
            var_r7_9 = pokemonGetStatus(arg0, 0, 0x95, 0);
            var_r7_9 += temp_r22;
            if (var_r7_9 < 0) {
                var_r7_9 = 0;
            }
            if (var_r7_9 > 0x1F) {
                var_r7_9 = 0x1F;
            }
            pokemonSetStatus(arg0, 0, 0x95, 0, var_r7_9);
            var_r29 = 1;
            break;
        case 0x2F:
            var_r7_10 = pokemonGetStatus(arg0, 0, 0x98, 0);
            var_r7_10 += temp_r22;
            if (var_r7_10 < 0) {
                var_r7_10 = 0;
            }
            if (var_r7_10 > 0x1F) {
                var_r7_10 = 0x1F;
            }
            pokemonSetStatus(arg0, 0, 0x98, 0, var_r7_10);
            var_r29 = 1;
            break;
        case 0x30:
            var_r7_11 = pokemonGetStatus(arg0, 0, 0x96, 0);
            var_r7_11 += temp_r22;
            if (var_r7_11 < 0) {
                var_r7_11 = 0;
            }
            if (var_r7_11 > 0x1F) {
                var_r7_11 = 0x1F;
            }
            pokemonSetStatus(arg0, 0, 0x96, 0, var_r7_11);
            var_r29 = 1;
            break;
        case 0x31:
            var_r7_12 = pokemonGetStatus(arg0, 0, 0x97, 0);
            var_r7_12 += temp_r22;
            if (var_r7_12 < 0) {
                var_r7_12 = 0;
            }
            if (var_r7_12 > 0x1F) {
                var_r7_12 = 0x1F;
            }
            pokemonSetStatus(arg0, 0, 0x97, 0, var_r7_12);
            var_r29 = 1;
            break;
        case 0x32:
            if ((temp_r22 <= 0) || (dbgMenuPokemonEditSubGetTotalEffort(arg0) < 0x1FEU)) {
                var_r7_13 = pokemonGetStatus(arg0, 0, 0x8D, 0);
                var_r7_13 += temp_r22;
                if (var_r7_13 < 0) {
                    var_r7_13 = 0;
                }
                if (var_r7_13 > 0xFF) {
                    var_r7_13 = 0xFF;
                }
                pokemonSetStatus(arg0, 0, 0x8D, 0, var_r7_13);
                var_r29 = 1;
                if (arg3 != 0) {
                    *arg3 = 1;
                }
            }
            break;
        case 0x33:
            if ((temp_r22 <= 0) || (dbgMenuPokemonEditSubGetTotalEffort(arg0) < 0x1FEU)) {
                var_r7_14 = pokemonGetStatus(arg0, 0, 0x8E, 0);
                var_r7_14 += temp_r22;
                if (var_r7_14 < 0) {
                    var_r7_14 = 0;
                }
                if (var_r7_14 > 0xFF) {
                    var_r7_14 = 0xFF;
                }
                pokemonSetStatus(arg0, 0, 0x8E, 0, var_r7_14);
                var_r29 = 1;
            }
            break;
        case 0x34:
            if ((temp_r22 <= 0) || (dbgMenuPokemonEditSubGetTotalEffort(arg0) < 0x1FEU)) {
                var_r7_15 = pokemonGetStatus(arg0, 0, 0x8F, 0);
                var_r7_15 += temp_r22;
                if (var_r7_15 < 0) {
                    var_r7_15 = 0;
                }
                if (var_r7_15 > 0xFF) {
                    var_r7_15 = 0xFF;
                }
                pokemonSetStatus(arg0, 0, 0x8F, 0, var_r7_15);
                var_r29 = 1;
            }
            break;
        case 0x35:
            if ((temp_r22 <= 0) || (dbgMenuPokemonEditSubGetTotalEffort(arg0) < 0x1FEU)) {
                var_r7_16 = pokemonGetStatus(arg0, 0, 0x92, 0);
                var_r7_16 += temp_r22;
                if (var_r7_16 < 0) {
                    var_r7_16 = 0;
                }
                if (var_r7_16 > 0xFF) {
                    var_r7_16 = 0xFF;
                }
                pokemonSetStatus(arg0, 0, 0x92, 0, var_r7_16);
                var_r29 = 1;
            }
            break;
        case 0x36:
            if ((temp_r22 <= 0) || (dbgMenuPokemonEditSubGetTotalEffort(arg0) < 0x1FEU)) {
                var_r7_17 = pokemonGetStatus(arg0, 0, 0x90, 0);
                var_r7_17 += temp_r22;
                if (var_r7_17 < 0) {
                    var_r7_17 = 0;
                }
                if (var_r7_17 > 0xFF) {
                    var_r7_17 = 0xFF;
                }
                pokemonSetStatus(arg0, 0, 0x90, 0, var_r7_17);
                var_r29 = 1;
            }
            break;
        case 0x37:
            if ((temp_r22 <= 0) || (dbgMenuPokemonEditSubGetTotalEffort(arg0) < 0x1FEU)) {
                var_r7_18 = pokemonGetStatus(arg0, 0, 0x91, 0);
                var_r7_18 += temp_r22;
                if (var_r7_18 < 0) {
                    var_r7_18 = 0;
                }
                if (var_r7_18 > 0xFF) {
                    var_r7_18 = 0xFF;
                }
                pokemonSetStatus(arg0, 0, 0x91, 0, var_r7_18);
                var_r29 = 1;
            }
            break;
        case 0x39:
            temp_r3_7 = pokemonGetStatus(arg0, 0, 0x7F, 0);
            if (temp_r3_7 != 0x176) {
                var_r0 = temp_r3_7 + temp_r22;
                if (var_r0 < 0) {
                    pokemonWazaInit(arg0, 0);
                } else {
                    if (var_r0 == 0x163) {
                        var_r0 += temp_r22;
                    }
                    if (var_r0 >= 0x176) {
                        var_r0 = 0x175;
                    }
                    pokemonWazaCreate(arg0, 0, (u16) var_r0);
                }
            }
            break;
        case 0x3A:
            temp_r3_8 = pokemonGetStatus(arg0, 0, 0x7F, 1);
            if (temp_r3_8 != 0x176) {
                var_r0_2 = temp_r3_8 + temp_r22;
                if (var_r0_2 < 0) {
                    pokemonWazaInit(arg0, 1);
                } else {
                    if (var_r0_2 == 0x163) {
                        var_r0_2 += temp_r22;
                    }
                    if (var_r0_2 >= 0x176) {
                        var_r0_2 = 0x175;
                    }
                    pokemonWazaCreate(arg0, 1, (u16) var_r0_2);
                }
            }
            break;
        case 0x3B:
            temp_r3_9 = pokemonGetStatus(arg0, 0, 0x7F, 2);
            if (temp_r3_9 != 0x176) {
                var_r0_3 = temp_r3_9 + temp_r22;
                if (var_r0_3 < 0) {
                    pokemonWazaInit(arg0, 2);
                } else {
                    if (var_r0_3 == 0x163) {
                        var_r0_3 += temp_r22;
                    }
                    if (var_r0_3 >= 0x176) {
                        var_r0_3 = 0x175;
                    }
                    pokemonWazaCreate(arg0, 2, (u16) var_r0_3);
                }
            }
            break;
        case 0x3C:
            temp_r3_10 = pokemonGetStatus(arg0, 0, 0x7F, 3);
            if (temp_r3_10 != 0x176) {
                var_r0_4 = temp_r3_10 + temp_r22;
                if (var_r0_4 < 0) {
                    pokemonWazaInit(arg0, 3);
                } else {
                    if (var_r0_4 == 0x163) {
                        var_r0_4 += temp_r22;
                    }
                    if (var_r0_4 >= 0x176) {
                        var_r0_4 = 0x175;
                    }
                    pokemonWazaCreate(arg0, 3, (u16) var_r0_4);
                }
            }
            break;
        case 0x3D:
            if (pokemonWazaCheckValid(arg0, 0) != 0) {
                temp_r3_11 = pokemonGetStatus(arg0, 0, 0x80, 0);
                if ((wazaCheckDarkWaza(temp_r3_11) != 1) && ((s32) temp_r3_11 != 0x176)) {
                    editValue = temp_r3_11 + temp_r22;
                    if (editValue < 0) {
                        editValue = 0;
                    }
                    if (editValue > (s32) pokemonWazaGetMaxPP(arg0, 0)) {
                        editValue = (s32) pokemonWazaGetMaxPP(arg0, 0);
                    }
                    pokemonSetStatus(arg0, 0, 0x80, 0, (s32) (u8) editValue);
                }
            }
            break;
        case 0x3E:
            if (pokemonWazaCheckValid(arg0, 1) != 0) {
                temp_r3_12 = pokemonGetStatus(arg0, 0, 0x80, 1);
                if ((wazaCheckDarkWaza(temp_r3_12) != 1) && ((s32) temp_r3_12 != 0x176)) {
                    editValue = temp_r3_12 + temp_r22;
                    if (editValue < 0) {
                        editValue = 0;
                    }
                    if (editValue > (s32) pokemonWazaGetMaxPP(arg0, 1)) {
                        editValue = (s32) pokemonWazaGetMaxPP(arg0, 1);
                    }
                    pokemonSetStatus(arg0, 0, 0x80, 1, (s32) (u8) editValue);
                }
            }
            break;
        case 0x3F:
            if (pokemonWazaCheckValid(arg0, 2) != 0) {
                temp_r3_13 = pokemonGetStatus(arg0, 0, 0x80, 2);
                if ((wazaCheckDarkWaza(temp_r3_13) != 1) && ((s32) temp_r3_13 != 0x176)) {
                    editValue = temp_r3_13 + temp_r22;
                    if (editValue < 0) {
                        editValue = 0;
                    }
                    if (editValue > (s32) pokemonWazaGetMaxPP(arg0, 2)) {
                        editValue = (s32) pokemonWazaGetMaxPP(arg0, 2);
                    }
                    pokemonSetStatus(arg0, 0, 0x80, 2, (s32) (u8) editValue);
                }
            }
            break;
        case 0x40:
            if (pokemonWazaCheckValid(arg0, 3) != 0) {
                temp_r3_14 = pokemonGetStatus(arg0, 0, 0x80, 3);
                if ((wazaCheckDarkWaza(temp_r3_14) != 1) && ((s32) temp_r3_14 != 0x176)) {
                    editValue = temp_r3_14 + temp_r22;
                    if (editValue < 0) {
                        editValue = 0;
                    }
                    if (editValue > (s32) pokemonWazaGetMaxPP(arg0, 3)) {
                        editValue = (s32) pokemonWazaGetMaxPP(arg0, 3);
                    }
                    pokemonSetStatus(arg0, 0, 0x80, 3, (s32) (u8) editValue);
                }
            }
            break;
        case 0x41:
            if (pokemonWazaCheckValid(arg0, 0) != 0) {
                temp_r3_15 = pokemonGetStatus(arg0, 0, 0x81, 0);
                if ((wazaCheckDarkWaza(temp_r3_15) != 1) && ((s32) temp_r3_15 != 0x176)) {
                    var_r0_5 = temp_r3_15 + temp_r22;
                    if (var_r0_5 < 0) {
                        var_r0_5 = 0;
                    }
                    if (var_r0_5 > 3) {
                        var_r0_5 = 3;
                    }
                    pokemonSetStatus(arg0, 0, 0x81, 0, (s32) (u8) var_r0_5);
                    pokemonSetStatus(arg0, 0, 0x80, 0, (s32) pokemonWazaGetMaxPP(arg0, 0));
                }
            }
            break;
        case 0x42:
            if (pokemonWazaCheckValid(arg0, 1) != 0) {
                temp_r3_16 = pokemonGetStatus(arg0, 0, 0x81, 1);
                if ((wazaCheckDarkWaza(temp_r3_16) != 1) && ((s32) temp_r3_16 != 0x176)) {
                    var_r0_6 = temp_r3_16 + temp_r22;
                    if (var_r0_6 < 0) {
                        var_r0_6 = 0;
                    }
                    if (var_r0_6 > 3) {
                        var_r0_6 = 3;
                    }
                    pokemonSetStatus(arg0, 0, 0x81, 1, (s32) (u8) var_r0_6);
                    pokemonSetStatus(arg0, 0, 0x80, 1, (s32) pokemonWazaGetMaxPP(arg0, 1));
                }
            }
            break;
        case 0x43:
            if (pokemonWazaCheckValid(arg0, 2) != 0) {
                temp_r3_17 = pokemonGetStatus(arg0, 0, 0x81, 2);
                if ((wazaCheckDarkWaza(temp_r3_17) != 1) && ((s32) temp_r3_17 != 0x176)) {
                    var_r0_7 = temp_r3_17 + temp_r22;
                    if (var_r0_7 < 0) {
                        var_r0_7 = 0;
                    }
                    if (var_r0_7 > 3) {
                        var_r0_7 = 3;
                    }
                    pokemonSetStatus(arg0, 0, 0x81, 2, (s32) (u8) var_r0_7);
                    pokemonSetStatus(arg0, 0, 0x80, 2, (s32) pokemonWazaGetMaxPP(arg0, 2));
                }
            }
            break;
        case 0x44:
            if (pokemonWazaCheckValid(arg0, 3) != 0) {
                temp_r3_18 = pokemonGetStatus(arg0, 0, 0x81, 3);
                if ((wazaCheckDarkWaza(temp_r3_18) != 1) && ((s32) temp_r3_18 != 0x176)) {
                    var_r0_8 = temp_r3_18 + temp_r22;
                    if (var_r0_8 < 0) {
                        var_r0_8 = 0;
                    }
                    if (var_r0_8 > 3) {
                        var_r0_8 = 3;
                    }
                    pokemonSetStatus(arg0, 0, 0x81, 3, (s32) (u8) var_r0_8);
                    pokemonSetStatus(arg0, 0, 0x80, 3, (s32) pokemonWazaGetMaxPP(arg0, 3));
                }
            }
            break;
        case 0x46:
            if ((u8)pokemonGetStatus(arg0, 0, 0xB7, 0) == 1) {
                editValue = 0;
            } else {
                editValue = 1;
            }
            if ((s32)pokemonGetStatus(0, (u16) pokemonGetStatus(arg0, 0, 0x6E, 0), 0x17, 1) == 0) {
                editValue = 0;
            }
            pokemonSetTokuseiFlag(arg0, editValue);
            if (arg4 != 0) {
                *arg4 = 1;
            }
            break;
        case 0x48:
            var_r0_9 = (u16)pokemonGetSoubiItemDataId(arg0);
            var_r0_9 += temp_r22;
            if (var_r0_9 < 0) {
                var_r0_9 = 0;
            }
            temp_r3_19 = *item_data_index_number;
            if ((u32) var_r0_9 >= temp_r3_19) {
                var_r0_9 = temp_r3_19 - 1;
            }
            pokemonDoItemSoubi(arg0, (u16) var_r0_9, 1);
            if (arg5 != 0) {
                *arg5 = 1;
            }
            break;
        case 0x4A:
            temp_r3_20 = pokemonGetStatus(arg0, 0, 0x6F, 0);
            if ((u32) (temp_r22 + 0x10000) == 1U) {
                editValue = 0;
                goto block_272;
            }
            if (temp_r22 == 65535) {
                editValue = -1;
                goto block_272;
            }
            if (menuSubOpenNumberInput(temp_r3_20, &number, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
            } else {
                editValue = number;
                menuSubCloseNumberInput();
block_272:
                pokemonSetStatus(arg0, 0, 0x6F, 0, editValue);
                var_r29 = 1;
                if (arg2 != 0) {
                    *arg2 = 1;
                }
                if (arg3 != 0) {
                    *arg3 = 1;
                }
            }
            break;
        case 0x4B:
            editValue = pokemonGetStatus(arg0, 0, 0xBA, 0);
            editValue += temp_r22;
            if (editValue < 0) {
                editValue = 0;
            }
            if ((u32) editValue >= (u32) sex_data_number) {
                editValue = sex_data_number - 1;
            }
            personality = pokemonCreateRndFit(arg0, editValue, pokemonGetStatus(arg0, 0, 0xBF, 0), pokemonCheckRare(arg0), pokemonGetStatus(arg0, 0, 0x75, 0));
            pokemonSetStatus(arg0, 0, 0x6F, 0, personality);
            var_r29 = 1;
            if (arg2 != 0) {
                *arg2 = 1;
            }
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x4C:
            editValue = (u8)pokemonGetStatus(arg0, 0, 0xBF, 0);
            editValue += temp_r22;
            if (editValue < 0) {
                editValue = 0;
            }
            temp_r3_21 = *pokemon_seikaku_data_number;
            if ((u32) editValue >= temp_r3_21) {
                editValue = temp_r3_21 - 1;
            }
            pokemonSetStatus(arg0, 0, 0x6F, 0, pokemonCreateRndFit(arg0, pokemonGetStatus(arg0, 0, 0xBA, 0), editValue, pokemonCheckRare(arg0), pokemonGetStatus(arg0, 0, 0x75, 0)));
            var_r29 = 1;
            if (arg2 != 0) {
                *arg2 = 1;
            }
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x4D:
            if (temp_r22 > 0) {
                editValue = 1;
            } else {
                editValue = 0;
            }
            pokemonSetStatus(arg0, 0, 0x6F, 0, pokemonCreateRndFit(arg0, pokemonGetStatus(arg0, 0, 0xBA, 0), pokemonGetStatus(arg0, 0, 0xBF, 0), editValue, pokemonGetStatus(arg0, 0, 0x75, 0)));
            var_r29 = 1;
            if (arg2 != 0) {
                *arg2 = 1;
            }
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x4F:
            temp_r3_22 = pokemonGetStatus(arg0, 0, 0x75, 0);
            if ((u32) (temp_r22 + 0x10000) == 1U) {
                editValue = 0;
                goto block_306;
            }
            if (temp_r22 == 65535) {
                editValue = -1;
                goto block_306;
            }
            if (menuSubOpenNumberInput(temp_r3_22, &number, 1, 0x32, 0x32, 0) == 0) {
                menuSubCloseNumberInput();
            } else {
                editValue = number;
                menuSubCloseNumberInput();
block_306:
                pokemonSetStatus(arg0, 0, 0x75, 0, editValue);
                if (arg2 != 0) {
                    *arg2 = 1;
                }
                if (arg3 != 0) {
                    *arg3 = 1;
                }
            }
            break;
        case 0x51:
            var_r7_19 = pokemonGetStatus(arg0, 0, 0x99, 0);
            var_r7_19 += temp_r22;
            if (var_r7_19 < 0) {
                var_r7_19 = 0;
            }
            if (var_r7_19 > 0xFF) {
                var_r7_19 = 0xFF;
            }
            pokemonSetStatus(arg0, 0, 0x99, 0, var_r7_19);
            break;
        case 0x53:
            var_r7_20 = pokemonGetStatus(arg0, 0, 0xB5, 0);
            var_r7_20 += temp_r22;
            if (var_r7_20 < 0) {
                var_r7_20 = 0;
            }
            if (var_r7_20 > 0xFF) {
                var_r7_20 = 0xFF;
            }
            pokemonSetStatus(arg0, 0, 0xB5, 0, var_r7_20);
            break;
        case 0x55:
            editValue = pokemonGetJoutaiDataId(arg0);
            if (editValue == 0) {
                editValue = temp_r22 + 2;
            } else {
                editValue += temp_r22;
            }
            if (editValue < 3) {
                editValue = 0;
            }
            if (editValue > 8) {
                editValue = 8;
            }
            pokemonInitJoutai(arg0);
            if ((editValue != 0) && (pokemonCheckWriteJoutaiDataId(arg0, (u16) editValue) == 2)) {
                pokemonWriteJoutaiDataId(arg0, (u16) editValue, 0);
            }
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x56:
            editValue = pokemonGetJoutaiDataId(arg0);
            if (editValue != 0) {
                count = pokemonGetKaisuuJoutaiDataId(arg0, editValue);
                if (editValue != 4) {
                    if (count >= 0) {
                        count += temp_r22;
                        if (count < 0) {
                            count = 0;
                        }
                        if (count > 0x10) {
                            count = 0x10;
                        }
                        pokemonSetKaisuuJoutaiDataId(arg0, editValue, count);
                        if (pokemonGetNowKaisuuJoutaiDataId(arg0, editValue) > count) {
                            pokemonSetNowKaisuuJoutaiDataId(arg0, editValue, count);
                        }
                        goto block_346;
                    }
                } else {
                    count = pokemonGetCountAsJoutaiDataId(arg0, editValue);
                    count += temp_r22;
                    if (count < 0) {
                        count = 0;
                    }
                    if (count > joutaiDataBiosGetMaxCount(editValue)) {
                        count = joutaiDataBiosGetMaxCount(editValue);
                    }
                    pokemonSetCountAsJoutaiDataId(arg0, editValue, count);
block_346:
                    if (arg3 != 0) {
                        *arg3 = 1;
                    }
                }
            }
            break;
        case 0x57:
            editValue = pokemonGetJoutaiDataId(arg0);
            if (editValue != 0) {
                temp_r0 = pokemonGetKaisuuJoutaiDataId(arg0, editValue);
                if ((editValue != 4) && (temp_r0 >= 0)) {
                    i = pokemonGetNowKaisuuJoutaiDataId(arg0, editValue);
                    i += temp_r22;
                    if (i < 0) {
                        i = 0;
                    }
                    if (i > pokemonGetKaisuuJoutaiDataId(arg0, editValue)) {
                        i = pokemonGetKaisuuJoutaiDataId(arg0, editValue);
                    }
                    pokemonSetNowKaisuuJoutaiDataId(arg0, editValue, i);
                    if (arg3 != 0) {
                        *arg3 = 1;
                    }
                }
            }
            break;
        case 0x59:
            editValue = pokemonGetStatus(arg0, 0, 0xC3, 0);
            editValue += temp_r22;
            if (editValue < 0) {
                editValue = 0;
            }
            if ((u32) editValue >= (u32) darkPokemonList_number) {
                editValue = darkPokemonList_number - 1;
            }
            if (editValue == 0) {
                pokemonInitDarkPokemon(arg0);
            } else {
                pokemonSetStatus(arg0, 0, 0xC3, 0, editValue);
                pokemonSetDarkPokemonStatus(arg0, (u16) editValue);
            }
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x5B:
            if ((u16)pokemonGetStatus(arg0, 0, 0xC3, 0) != 0) {
                temp_r3_26 = pokemonGetStatus(arg0, 0, 0xC5, 0);
                if ((u32) (temp_r22 + 0x10000) == 1U) {
                    editValue = -1;
                    goto block_377;
                }
                if (temp_r22 == 65535) {
                    editValue = 0xFFFF;
                    goto block_377;
                }
                if (menuSubOpenNumberInput(temp_r3_26, &number, 0, 0x32, 0x32, 0) == 0) {
                    menuSubCloseNumberInput();
                } else {
                    editValue = number;
                    menuSubCloseNumberInput();
                    if (editValue < -1) {
                        editValue = -1;
                    }
                    if ((f32) editValue > 65535.0f) {
                        editValue = 0xFFFF;
                    }
block_377:
                    pokemonSetStatus(arg0, 0, 0xC5, 0, editValue);
                    if (arg3 != 0) {
                        *arg3 = 1;
                    }
                }
            }
            break;
        case 0x5D:
            if (pokemonIsDarkPokemon(arg0) != 0) {
                if (temp_r22 > 0) {
                    pokemonWriteJoutaiDataId(arg0, 0x3EU, 0);
                } else {
                    pokemonInitJoutaiDataId(arg0, 0x3E);
                }
                if (arg3 != 0) {
                    *arg3 = 1;
                }
            }
            break;
        case 0x5F:
            if ((u16)pokemonGetStatus(arg0, 0, 0xC3, 0) != 0) {
                temp_r3_27 = pokemonGetStatus(arg0, 0, 0xC6, 0);
                if ((u32) (temp_r22 + 0x10000) == 1U) {
                    editValue = 0;
                    goto block_396;
                }
                if (temp_r22 == 65535) {
                    editValue = 0x1E8480;
                    goto block_396;
                }
                if (menuSubOpenNumberInput(temp_r3_27, &number, 1, 0x32, 0x32, 0) == 0) {
                    menuSubCloseNumberInput();
                } else {
                    editValue = number;
                    menuSubCloseNumberInput();
                    if (editValue < 0) {
                        editValue = 0;
                    }
                    if (editValue > 0x1E8480) {
                        editValue = 0x1E8480;
                    }
block_396:
                    pokemonSetStatus(arg0, 0, 0xC6, 0, editValue);
                }
            }
            break;
        case 0x61:
            if ((u16)pokemonGetStatus(arg0, 0, 0xC3, 0) != 0) {
                var_r7_21 = pokemonGetStatus(arg0, 0, 0xC7, 0);
                var_r7_21 += temp_r22;
                if (var_r7_21 < 0) {
                    var_r7_21 = 0;
                }
                if (var_r7_21 > 0xFF) {
                    var_r7_21 = 0xFF;
                }
                pokemonSetStatus(arg0, 0, 0xC7, 0, var_r7_21);
            }
            break;
        case 0x69:
            if ((temp_r27 != 0) && (arg1 == 1)) {
                var_r0_10 = (u8)fightTrainerGetStatus(0, temp_r27, 0x1C, 0);
                var_r0_10 += temp_r22;
                if (var_r0_10 < 0) {
                    var_r0_10 = 0;
                }
                if (var_r0_10 > 3) {
                    var_r0_10 = 3;
                }
                fightTrainerSetStatus(0, temp_r27, 0x1C, 0U, (s32) (u8) var_r0_10);
            }
            break;
        case 0x6B:
            if ((temp_r27 != 0) && (arg1 == 1)) {
                var_r0_11 = (u16)fightTrainerGetStatus(0, temp_r27, 0x1D, 0);
                var_r0_11 += temp_r22;
                if (var_r0_11 < 0) {
                    var_r0_11 = 0;
                }
                temp_r3_28 = *fight_trainer_pokemon_part_data_number;
                if ((u32) var_r0_11 >= temp_r3_28) {
                    var_r0_11 = temp_r3_28 - 1;
                }
                fightTrainerSetStatus(0, temp_r27, 0x1D, 0U, (s32) (u16) var_r0_11);
            }
            break;
        case 0x70:
            var_r7_22 = pokemonGetStatus(arg0, 0, 0x73, 0);
            var_r7_22 += temp_r22;
            if (var_r7_22 < 0) {
                var_r7_22 = 0;
            }
            if (var_r7_22 > 0xC) {
                var_r7_22 = 0xC;
            }
            pokemonSetStatus(arg0, 0, 0x73, 0, var_r7_22);
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x6E:
            var_r7_23 = pokemonGetStatus(arg0, 0, gRibbonStat[gRibbonNum], 0);
            var_r7_23 += temp_r22;
            if (var_r7_23 < 0) {
                var_r7_23 = 0;
            }
            if (var_r7_23 > 4) {
                var_r7_23 = 4;
            }
            pokemonSetStatus(arg0, 0, (s32) gRibbonStat[gRibbonNum], 0, var_r7_23);
            if (arg3 != 0) {
                *arg3 = 1;
            }
            break;
        case 0x6D:
            temp_r0_2 = gRibbonNum + temp_r22;
            gRibbonNum = temp_r0_2;
            if (temp_r0_2 < 0) {
                gRibbonNum = 0;
            }
            if ((s32) gRibbonNum > 0x11) {
                gRibbonNum = 0x11;
            }
            break;
        }
        if (var_r29 == 1) {
            pokemonSetTokuseiFlag(arg0, (u8)pokemonGetStatus(arg0, 0, 0xB7, 0));
            if (temp_r3 == 0x18) {
                var_r4 = pokemonGetNowLevelToExp(arg0);
            } else {
                var_r4 = pokemonGetStatus(arg0, 0, 0x79, 0);
            }
            pokemonGrowBasisStatus(arg0, var_r4);
        }
    }
    goto loop_11;
finish:
        menuCloseCustom(0x55, 0, 1);
        menuCloseCustom(0xD, 0, 1);
        switch (pokemonBiosGetPokemonDataId(arg0)) {
        case 0x97:
        case 0x19A:
            temp_r3_3 = pokemonGetStatus(arg0, 0, 0x73, 0);
            if ((temp_r3_3 == 4) || (temp_r3_3 == 0)) {
                pokemonBiosSetEventGetFlag(arg0, 1);
            } else {
                pokemonBiosSetEventGetFlag(arg0, 0);
            }
            break;
        }
        if (pokemonCheckValid(arg0) == 0) {
            pokemonInit(arg0);
        } else {
            if (itemDataCheckValid(pokemonGetSoubiItemDataId(arg0)) == 0) {
                pokemonDoItemSoubi(arg0, 0U, 0);
            }
            if ((temp_r27 != 0) && (arg1 == 1)) {
                editValue = pokemonGetStatus(arg0, 0, 0x6E, 0);
                fightTrainerSetStatus(0, temp_r27, 0x15, 0U, editValue);
                fightTrainerSetStatus(0, temp_r27, 0xE, 0U, pokemonGetStatus(0, (s32) (u16) editValue, 1, 0));
                fightTrainerSetStatus(0, temp_r27, 0x11, 0U, pokemonGetStatus(arg0, 0, 0x7A, 0));
                for (i = 0; i < 6; i++) {
                    fightTrainerSetStatus(0, temp_r27, 0xF, i, pokemonGetStatus(arg0, 0, individual[i], 0));
                }
                for (i = 0; i < 6; i++) {
                    fightTrainerSetStatus(0, temp_r27, 0x10, i, pokemonGetStatus(arg0, 0, effort[i], 0));
                }
                fightTrainerSetStatus(0, temp_r27, 0x14, 0U, (u8) pokemonGetStatus(arg0, 0, 0xB7, 0));
                fightTrainerSetStatus(0, temp_r27, 0x16, 0U, (s32) pokemonGetSoubiItemDataId(arg0));
                fightTrainerSetStatus(0, temp_r27, 0x19, 0U, pokemonGetStatus(arg0, 0, 0x99, 0));
                fightTrainerSetStatus(0, temp_r27, 0x1A, 0U, pokemonGetStatus(arg0, 0, 0xBA, 0));
                fightTrainerSetStatus(0, temp_r27, 0x1B, 0U, pokemonGetStatus(arg0, 0, 0xBF, 0));
                for (i = 0; i < 4; i++) {
                    fightTrainerSetStatus(0, temp_r27, 0x17, i, pokemonGetStatus(arg0, 0, 0x7F, i));
                    fightTrainerSetStatus(0, temp_r27, 0x18, i, pokemonGetStatus(arg0, 0, 0x81, i));
                }
                fightTrainerSetStatus(0, temp_r27, 0x13, 0U, pokemonGetStatus(arg0, 0, 0xC3, 0));
            }
        }
        return 1;

}

#pragma opt_loop_invariants reset
#pragma opt_common_subs reset
static s32 dbgMenuPokemonEditSubGetTotalEffort(s32 pokemon) {
    s32 total = pokemonGetStatus(pokemon, 0, 0x8D, 0);
    total += pokemonGetStatus(pokemon, 0, 0x8E, 0);
    total += pokemonGetStatus(pokemon, 0, 0x8F, 0);
    total += pokemonGetStatus(pokemon, 0, 0x90, 0);
    total += pokemonGetStatus(pokemon, 0, 0x91, 0);
    total += pokemonGetStatus(pokemon, 0, 0x92, 0);
    return total;
}

#ifdef __cplusplus
}
#endif

#pragma force_active reset
