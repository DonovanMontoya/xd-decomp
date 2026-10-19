#include <dolphin/types.h>
#include "game/pxdvs/app/item/itemBiosLayout.hpp"

extern u8 item_param[]; extern u32 item_param_number;
extern u8 taste_data[]; extern u32 taste_data_number;
extern u8 item_soubi_data[]; extern u32 item_soubi_data_number;
extern u8 item_ball_data[]; extern u32 item_ball_data_number;
extern u8 item_waza_machine_no[]; extern u32 item_waza_machine_no_number;
extern u16 *item_data_index; extern u32 *item_data_index_number;
extern u8 *item_data_prime; extern u32 *item_data_prime_number;
#define ITEM_FIELD(T, P, O) (*((T *)((u8 *)(P) + (O))))

extern "C" {
struct ItemParamFlags {
    u8 b0_0 : 1;
    u8 b0_1 : 1;
    u8 b0_2 : 1;
    u8 b0_3 : 4;
    u8 b0_4 : 1;
    u8 b1_0 : 4;
    u8 b1_1 : 4;
    u8 b2_0 : 4;
    u8 b2_1 : 4;
    u8 b3_0 : 1;
    u8 b3_1 : 1;
    u8 b3_2 : 1;
    u8 b3_3 : 1;
    u8 b3_4 : 1;
    u8 b3_5 : 1;
    u8 b3_6 : 1;
    u8 b3_7 : 1;
    u8 b4_0 : 1;
    u8 b4_1 : 1;
    u8 b4_2 : 1;
    u8 b4_3 : 1;
    u8 b4_4 : 1;
    u8 b4_5 : 1;
    u8 b4_6 : 1;
    u8 b4_7 : 1;
};
struct ItemParamConversion { u32 field; u32 offset; u8 mask; s32 type; };
#pragma peephole on
void itemParamConvertOrigFormat(ItemParamRecord* target, const u8* original) {
    ItemParamConversion table[32] = {
        {0, 0, 0x80, 0},
        {1, 0, 0x40, 0},
        {2, 0, 0x30, 0},
        {3, 0, 0x0F, 1},
        {4, 1, 0xF0, 1},
        {5, 1, 0x0F, 1},
        {6, 2, 0xF0, 1},
        {7, 2, 0x0F, 1},
        {8, 3, 0x80, 0},
        {9, 3, 0x40, 0},
        {10, 3, 0x20, 0},
        {11, 3, 0x10, 0},
        {12, 3, 0x08, 0},
        {13, 3, 0x04, 0},
        {14, 3, 0x02, 0},
        {15, 3, 0x01, 0},
        {16, 4, 0x20, 0},
        {17, 4, 0x01, 2},
        {18, 4, 0x02, 2},
        {19, 4, 0x40, 0},
        {20, 4, 0x04, 2},
        {21, 4, 0x10, 0},
        {22, 4, 0x08, 2},
        {23, 4, 0x80, 0},
        {24, 5, 0x01, 2},
        {25, 5, 0x02, 2},
        {26, 5, 0x04, 2},
        {27, 5, 0x08, 2},
        {28, 5, 0x10, 0},
        {29, 5, 0x20, 3},
        {30, 5, 0x40, 3},
        {31, 5, 0x80, 3},
    };
    ItemParamConversion* entry;
    s32 i;
    const u8* cursor = original + 6;
    u8 value;
    s8 signedValue;
    u8 flag;
    entry = table;
    for (i = 0; i < 32; ++i, ++entry) {
        s32 type = entry->type;
        s32 bits = original[entry->offset];
        if (type == 3 || type == 2) {
            if (bits & entry->mask) {
                value = *cursor++;
                if (type == 3) signedValue = (s8)value;
            } else if (type == 3) signedValue = 0;
        } else {
            s32 mask = entry->mask;
            bits &= mask;
            s32 shift = 0;
            for (; shift < 8 && !((mask >> shift) & 1); ++shift) {}
            value = (u8)((u8)bits >> shift);
            if (type == 0) {
                if (value == 0) flag = 0;
                else flag = 1;
            }
        }
        switch(entry->field) {
        case 0: ((ItemParamFlags*)target)->b0_0 = flag; break;
        case 2: ((ItemParamFlags*)target)->b0_2 = flag; break;
        case 3: ((ItemParamFlags*)target)->b0_3 = value; break;
        case 4: ((ItemParamFlags*)target)->b1_0 = value; break;
        case 5: ((ItemParamFlags*)target)->b1_1 = value; break;
        case 6: ((ItemParamFlags*)target)->b2_0 = value; break;
        case 7: ((ItemParamFlags*)target)->b2_1 = value; break;
        case 8: ((ItemParamFlags*)target)->b3_0 = flag; break;
        case 9: ((ItemParamFlags*)target)->b3_1 = flag; break;
        case 10: ((ItemParamFlags*)target)->b3_2 = flag; break;
        case 11: ((ItemParamFlags*)target)->b3_3 = flag; break;
        case 12: ((ItemParamFlags*)target)->b3_4 = flag; break;
        case 13: ((ItemParamFlags*)target)->b3_5 = flag; break;
        case 14: ((ItemParamFlags*)target)->b3_6 = flag; break;
        case 15: ((ItemParamFlags*)target)->b3_7 = flag; break;
        case 16: ((ItemParamFlags*)target)->b4_0 = flag; break;
        case 17: target->hpEffortUp = value; break;
        case 18: target->attackEffortUp = value; break;
        case 19: ((ItemParamFlags*)target)->b4_1 = flag; break;
        case 20: target->hpUp = value; break;
        case 21: ((ItemParamFlags*)target)->b4_2 = flag; break;
        case 22: target->ppUp = value; break;
        case 23: ((ItemParamFlags*)target)->b4_3 = flag; break;
        case 24: target->defenceEffortUp = value; break;
        case 25: target->quickEffortUp = value; break;
        case 26: target->spDefenceEffortUp = value; break;
        case 27: target->spAttackEffortUp = value; break;
        case 28: ((ItemParamFlags*)target)->b4_4 = flag; break;
        case 29: target->friend1Up = signedValue; break;
        case 30: target->friend2Up = signedValue; break;
        case 31: target->friend3Up = signedValue; break;
        }
    }
}

#pragma peephole reset
s8 itemParamGetFriend3Up(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (s8) ((ItemParamRecord *)arg0)->friend3Up;
}


s8 itemParamGetFriend2Up(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (s8) ((ItemParamRecord *)arg0)->friend2Up;
}


s8 itemParamGetFriend1Up(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (s8) ((ItemParamRecord *)arg0)->friend1Up;
}


s32 itemParamGetPPMaxFullFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 3U) & 1) != 0;
}


u8 itemParamGetSpAttackEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->spAttackEffortUp;
}


u8 itemParamGetSpDefenceEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->spDefenceEffortUp;
}


u8 itemParamGetQuickEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->quickEffortUp;
}


u8 itemParamGetDefenceEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->defenceEffortUp;
}


s32 itemParamGetEvolutionFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 4U) & 1) != 0;
}


u8 itemParamGetPPUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->ppUp;
}


s32 itemParamGetPPSelectFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 5U) & 1) != 0;
}


u8 itemParamGetHPUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->hpUp;
}


s32 itemParamGetReviveFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 6U) & 1) != 0;
}


u8 itemParamGetAttackEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->attackEffortUp;
}


u8 itemParamGetHPEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->hpEffortUp;
}


s32 itemParamGetPPMaxUpFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 7U) & 1) != 0;
}


s32 itemParamGetConfuseFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (ITEM_FIELD(u8, arg0, 0x3) & 1) != 0;
}


s32 itemParamGetParalyzeFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 1U) & 1) != 0;
}


s32 itemParamGetFreezeFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 2U) & 1) != 0;
}


s32 itemParamGetBurnFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 3U) & 1) != 0;
}


s32 itemParamGetPoisonFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 4U) & 1) != 0;
}


s32 itemParamGetSleepFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 5U) & 1) != 0;
}


s32 itemParamGetLevelUpFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 6U) & 1) != 0;
}


s32 itemParamGetGuardFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 7U) & 1) != 0;
}


s32 itemParamGetSpAttackUp(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ITEM_FIELD(u8, arg0, 0x2) & 0xF;
}


s32 itemParamGetHitUp(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((u8) ITEM_FIELD(u8, arg0, 0x2) >> 4U) & 0xF;
}


s32 itemParamGetQuickUp(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ITEM_FIELD(u8, arg0, 0x1) & 0xF;
}


s32 itemParamGetDefenceUp(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((u8) ITEM_FIELD(u8, arg0, 0x1) >> 4U) & 0xF;
}


s32 itemParamGetAttackUp(u8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((u8) *arg0 >> 1U) & 0xF;
}


s32 itemParamGetCriticalFlag(u8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) *arg0 >> 5U) & 1) != 0;
}


s32 itemParamGetMeromeroFlag(u8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) *arg0 >> 7U) & 1) != 0;
}

static inline u8 itemRecoveryFlag(void *data, u32 offset, u32 shift) {
    if (data == NULL) return 0;
    s32 bit = (((u8*)data)[offset] >> shift) & 1;
    return (u32)(-bit | bit) >> 31;
}
static inline u8 itemRecoveryNibble(void *data, u32 offset, u32 shift) {
    if (data == NULL) return 0;
    return (((u8*)data)[offset] >> shift) & 15;
}
static inline u8 itemRecoveryByte(void *data, u32 offset) {
    if (data == NULL) return 0;
    return ((u8*)data)[offset];
}
#pragma always_inline on
#pragma peephole on
s32 itemParamGetRecoverType(void *arg0) {
    if (arg0 == NULL) return 0x16;
    if (itemRecoveryFlag(arg0, 0, 5) ||
        itemRecoveryNibble(arg0, 0, 1) ||
        itemRecoveryNibble(arg0, 1, 4) || itemRecoveryNibble(arg0, 1, 0) ||
        itemRecoveryNibble(arg0, 2, 4) || itemRecoveryNibble(arg0, 2, 0) ||
        itemRecoveryFlag(arg0, 3, 7)) return 0;
    if (itemRecoveryFlag(arg0, 0, 6)) return 1;
    if (itemRecoveryFlag(arg0, 3, 6)) return 2;
    s32 count = 0;
    s32 type;
    if (itemRecoveryFlag(arg0, 3, 5)) { type = 3; ++count; }
    if (itemRecoveryFlag(arg0, 3, 4)) { type = 4; ++count; }
    if (itemRecoveryFlag(arg0, 3, 3)) { type = 5; ++count; }
    if (itemRecoveryFlag(arg0, 3, 2)) { type = 6; ++count; }
    if (itemRecoveryFlag(arg0, 3, 1)) { type = 7; ++count; }
    if (itemRecoveryFlag(arg0, 3, 0)) { type = 8; ++count; }
    if (itemRecoveryFlag(arg0, 0, 7)) { type = 9; ++count; }
    if (count > 0) {
        s32 r = type; if (count > 1) r = 0xA; return r;
    }
    if (itemRecoveryByte(arg0, 10)) return 11;
    if (itemRecoveryByte(arg0, 9)) return 12;
    if (itemRecoveryByte(arg0, 8)) return 13;
    if (itemRecoveryByte(arg0, 15)) return 14;
    if (itemRecoveryByte(arg0, 14)) return 15;
    if (itemRecoveryByte(arg0, 13)) return 16;
    if (itemRecoveryByte(arg0, 12)) return 17;
    if (itemRecoveryFlag(arg0, 4, 4)) return 18;
    if (itemRecoveryFlag(arg0, 4, 7)) return 19;
    if (itemRecoveryFlag(arg0, 4, 3)) return 20;
    if (itemRecoveryFlag(arg0, 4, 5) || itemRecoveryByte(arg0, 11)) return 0x15;
    return 0x16;
}
#pragma peephole reset
#pragma always_inline reset

void *itemParamGetPtr(u32 arg0) {
    u32 count = item_param_number;
    u8 *table = item_param;
    u32 index = (u8)arg0;
    void *result = table + ((arg0 * 16) & 0xff0);
    if (index < count) return result;
    return NULL;
}


struct TasteAisyouRec { u8 pad[4]; u8 a[25]; };
s8 tasteDataGetAisyou(TasteAisyouRec *arg0, u16 arg1) {
    if (arg0 == 0) {
        return 0;
    }
    if (arg1 >= 0x19U) {
        return 0;
    }
    return (s8)arg0->a[arg1];
}


s32 tasteDataGetNigateMsgDataId(s32 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *arg0;
}

void *tasteDataGetPtr(u32 arg0) {
    u32 count = taste_data_number;
    u8 *table = taste_data;
    u32 index = (u16)arg0;
    void *result = table + ((arg0 * 32) & 0x1fffe0);
    if (index < count) return result;
    return NULL;
}


u16 itemSoubiDataBiosGetFightKoukaDataId(u16 *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return *arg0;
}

void *itemSoubiDataBiosGetPtr(u32 arg0) {
    u32 count = item_soubi_data_number;
    u8 *table = item_soubi_data;
    u32 index = (u16)arg0;
    void *result = table + ((arg0 * 2) & 0x1fffe);
    if (index < count) return result;
    return NULL;
}


void itemBiosSetNum(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ITEM_FIELD(s16, arg0, 0x2) = arg1;
    }
}


void itemBiosSetItemDataId(s16 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *arg0 = arg1;
    }
}


void itemBallDataBiosSetFightKoukaDataId(s16 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *arg0 = arg1;
    }
}


void itemDataBiosSetBuff(void *arg0, s32 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->buff = arg1;
    }
}


void itemDataBiosSetUseFriend(ItemDataRecord *arg0, u16 arg1, s8 arg2) {
    if ((arg0 != 0) && (arg1 < 3U)) {
        arg0->useFriend[arg1] = arg2;
    }
}


void itemDataBiosSetFightUseKoukaDataId(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->fightKoukaDataId = arg1;
    }
}


void itemDataBiosSetItemSoubiDataId(void *arg0, u16 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->itemSoubiDataId = arg1;
    }
}


void itemDataBiosSetDoc(void *arg0, s32 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->doc = arg1;
    }
}


void itemDataBiosSetUseful(void *arg0, s8 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->useful = arg1;
    }
}


void itemDataBiosSetImportant(void *arg0, s8 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->important = arg1;
    }
}


void itemDataBiosSetPrice(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ITEM_FIELD(s16, arg0, 0x6) = arg1;
    }
}


void itemDataBiosSetKind(s8 *arg0, s8 arg1) {
    if (arg0 != NULL) {
        *arg0 = arg1;
    }
}


void itemDataBiosSetName(void *arg0, s32 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->name = arg1;
    }
}


u16 itemBiosGetNum(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ITEM_FIELD(u16, arg0, 0x2);
}


u16 itemBiosGetItemDataId(u16 *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return *arg0;
}


s32 itemBallDataBiosGetSnatchSnatchWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[10];
}


s32 itemBallDataBiosGetSnatchShakeWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[9];
}


s32 itemBallDataBiosGetSnatchPokeoutWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[8];
}


s32 itemBallDataBiosGetSnatchMissWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[7];
}


s32 itemBallDataBiosGetSnatchBalllandWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[6];
}


s32 itemBallDataBiosGetSnatchAttackWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[5];
}


s32 itemBallDataBiosGetThrowWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[4];
}


s32 itemBallDataBiosGetDowninWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[3];
}


s32 itemBallDataBiosGetOutWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[2];
}


s32 itemBallDataBiosGetOpenWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[1];
}


s32 itemBallDataBiosGetInWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[0];
}


u16 itemBallDataBiosGetFightKoukaDataId(u16 *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return *arg0;
}

void *itemBallDataBiosGetPtr(u32 arg0) {
    u8 *table = item_ball_data;
    void *result = table + ((arg0 * 64) & 0x3fffc0);
    if ((u16)arg0 < item_ball_data_number) return result;
    return NULL;
}


s32 itemDataBiosGetBattleUseFunc(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->battleUseFunc;
}


s32 itemDataBiosGetFieldUseFunc(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->fieldUseFunc;
}


u8 itemDataBiosGetItemEffectParam(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemDataRecord *)arg0)->effectParam;
}


s32 itemDataBiosGetBuff(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->buff;
}


s8 itemDataBiosGetUseFriend(ItemDataRecord *arg0, u16 arg1) {
    if (arg0 == 0) {
        return 0;
    }
    if (arg1 >= 3U) {
        return 0;
    }
    return (s8)(u8)arg0->useFriend[arg1];
}


u8 itemDataBiosGetKinomiNo(u16 arg0) {
    if ((arg0 < 0x85U) || (arg0 > 0xAFU)) {
        return 0xFFU;
    }
    return (u8) (arg0 - 0x85);
}


u8 itemDataBiosGetHidenMachineNo(void *arg0) {
    u8 var_r0;

    if (arg0 == NULL) {
        var_r0 = 0;
    } else if ((u8) ((ItemDataRecord *)arg0)->kind != 4) {
        var_r0 = 0xFF;
    } else {
        var_r0 = (u8)ITEM_FIELD(u32, arg0, 0x18);
    }
    if (var_r0 == 0xFF) {
        return 0xFFU;
    }
    if ((var_r0 < 0x32U) || (var_r0 >= (u32) item_waza_machine_no_number)) {
        return 0xFFU;
    }
    return (u8) (var_r0 - 0x32);
}


u16 itemDataBiosGetWazaIDByWazaMachineNo(u32 arg0) {
    if ((u8)arg0 >= (u32) item_waza_machine_no_number) {
        return 0U;
    }
    return (u16)ITEM_FIELD(u32, ((arg0 * 8) & 0x7F8) + item_waza_machine_no, 4);
}


u8 itemDataBiosGetWazaMachineNo(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    if ((u8) ((ItemDataRecord *)arg0)->kind != 4) {
        return 0xFFU;
    }
    return (u8) ((ItemDataRecord *)arg0)->buff;
}


u16 itemDataBiosGetFightUseKoukaDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ITEM_FIELD(u16, arg0, 0xC);
}


u16 itemDataBiosGetItemSoubiDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ITEM_FIELD(u16, arg0, 0xA);
}


s32 itemDataBiosGetDoc(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->doc;
}


s32 itemDataBiosGetDeposit(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->deposit != 0;
}


s32 itemDataBiosGetUseful(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (u8)((ItemDataRecord *)arg0)->useful != 0;
}


s32 itemDataBiosGetImportant(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (u8)((ItemDataRecord *)arg0)->important != 0;
}


u16 itemDataBiosGetCoupon(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemDataRecord *)arg0)->coupon;
}


u16 itemDataBiosGetPrice(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemDataRecord *)arg0)->price;
}


u8 itemDataBiosGetKind(u8 *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return *arg0;
}


#pragma peephole on
s32 itemDataBiosCheckExportable(void *arg0) {
    u8 var_r0;

    if (arg0 == NULL) {
        return 0;
    }
    if (arg0 == NULL) {
        var_r0 = 0;
    } else {
        var_r0 = (u8)((ItemDataRecord *)arg0)->important != 0;
    }
    if (var_r0 != 0) {
        return 0;
    }
    return 1;
}
#pragma peephole reset


s32 itemDataBiosCheckImportable(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->name != 0;
}


s32 itemDataBiosGetName(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->name;
}


s32 itemDataBiosGetPtr(u16 arg0) {
    u16 temp_r3;

    if (arg0 >= (u32) *item_data_index_number) {
        return 0;
    }
    temp_r3 = *(u16 *)((u8 *)item_data_index + ((arg0 * 2) & 0x1FFFE));
    if (temp_r3 >= (u32) *item_data_prime_number) {
        return 0;
    }
    return (s32)(item_data_prime + (temp_r3 * 0x28));
}

}
