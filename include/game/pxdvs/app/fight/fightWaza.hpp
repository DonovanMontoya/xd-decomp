#ifndef GAME_FIGHT_WAZA_HPP
#define GAME_FIGHT_WAZA_HPP

#include <dolphin/types.h>
#include <libc/stddef.h>

struct FightJoutai {
    u16 dataId;
    u16 userFightTargetId;
    u8 kaisuu;
    u8 nowKaisuu;
    u8 count;
    u8 reserved07;
    u32 buff;
    u16 idBuff;
};
typedef char FightJoutaiSize[sizeof(FightJoutai) == 0x10 ? 1 : -1];

struct FightWaza {
    u8 wazaBanme;
    u16 motoWazaDataId;
    u16 useWazaDataId;
    u16 targetDataId;
    FightJoutai statuses[9];
    u8 critical;
    u8 damageValue;
    u32 damage;
    u32 hitDamage;
    u16 iryoku;
    u16 zokusei;
    u8 kaisuu;
    u8 autoMakeFlag;
};
typedef char FightWazaRecordSize[sizeof(FightWaza) == 0xac ? 1 : -1];
typedef char FightWazaRecord_wazaBanmeOffset[offsetof(FightWaza, wazaBanme) == 0x0 ? 1 : -1];
typedef char FightWazaRecord_motoWazaDataIdOffset[offsetof(FightWaza, motoWazaDataId) == 0x2 ? 1 : -1];
typedef char FightWazaRecord_useWazaDataIdOffset[offsetof(FightWaza, useWazaDataId) == 0x4 ? 1 : -1];
typedef char FightWazaRecord_targetDataIdOffset[offsetof(FightWaza, targetDataId) == 0x6 ? 1 : -1];
typedef char FightWazaRecord_statusesOffset[offsetof(FightWaza, statuses) == 0x8 ? 1 : -1];
typedef char FightWazaRecord_criticalOffset[offsetof(FightWaza, critical) == 0x98 ? 1 : -1];
typedef char FightWazaRecord_damageValueOffset[offsetof(FightWaza, damageValue) == 0x99 ? 1 : -1];
typedef char FightWazaRecord_damageOffset[offsetof(FightWaza, damage) == 0x9c ? 1 : -1];
typedef char FightWazaRecord_hitDamageOffset[offsetof(FightWaza, hitDamage) == 0xa0 ? 1 : -1];
typedef char FightWazaRecord_iryokuOffset[offsetof(FightWaza, iryoku) == 0xa4 ? 1 : -1];
typedef char FightWazaRecord_zokuseiOffset[offsetof(FightWaza, zokusei) == 0xa6 ? 1 : -1];
typedef char FightWazaRecord_kaisuuOffset[offsetof(FightWaza, kaisuu) == 0xa8 ? 1 : -1];
typedef char FightWazaRecord_autoMakeFlagOffset[offsetof(FightWaza, autoMakeFlag) == 0xa9 ? 1 : -1];

extern "C" void fightWazaBiosCopy(FightWaza* dst, const FightWaza* src);
extern "C" s32 fightWaza_GetWazaBanme(FightWaza* data);

#endif
