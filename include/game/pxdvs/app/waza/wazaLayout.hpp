#ifndef WAZA_LAYOUT_HPP
#define WAZA_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
#include <game/pxdvs/app/fight/fightWaza.hpp>
struct WazaDataRecord {
    u8 pri;
    u8 pp;
    u8 zokuseiDataId;
    u8 rangeId;
    u8 avg;
    u8 addFightKoukaAvg;
    u8 dageki;
    u8 mamoru;
    u8 majikku;
    u8 yokodori;
    u8 oumugaesi;
    u8 oujanosirusi;
    u8 yubiwohuru;
    u8 monomane;
    u8 nekonote;
    u8 negoto;
    u8 bouon;
    u8 pressure;
    u8 hidenFlag;
    u8 darkKind;
    u8 riskFlag;
    u8 compatible;
    u8 reserved16[0x2];
    s16 iryoku;
    u16 fightKoukaDataId;
    u16 seqId;
    u16 wazaFuncDataId;
    u32 name;
    u32 fightAttackTunagiMsgId;
    u32 fightAttackMsgId;
    u32 doc;
    u32 wazawzxdataId;
    u8 typeId[3];
    u8 reserved37[0x1];
};
typedef char WazaDataRecord_darkKindOffset[offsetof(WazaDataRecord, darkKind) == 0x13 ? 1 : -1];
typedef char WazaDataRecordSize[sizeof(WazaDataRecord) == 0x38 ? 1 : -1];
typedef char WazaDataRecord_priOffset[offsetof(WazaDataRecord, pri) == 0x0 ? 1 : -1];
typedef char WazaDataRecord_ppOffset[offsetof(WazaDataRecord, pp) == 0x1 ? 1 : -1];
typedef char WazaDataRecord_zokuseiDataIdOffset[offsetof(WazaDataRecord, zokuseiDataId) == 0x2 ? 1 : -1];
typedef char WazaDataRecord_rangeIdOffset[offsetof(WazaDataRecord, rangeId) == 0x3 ? 1 : -1];
typedef char WazaDataRecord_avgOffset[offsetof(WazaDataRecord, avg) == 0x4 ? 1 : -1];
typedef char WazaDataRecord_addFightKoukaAvgOffset[offsetof(WazaDataRecord, addFightKoukaAvg) == 0x5 ? 1 : -1];
typedef char WazaDataRecord_dagekiOffset[offsetof(WazaDataRecord, dageki) == 0x6 ? 1 : -1];
typedef char WazaDataRecord_mamoruOffset[offsetof(WazaDataRecord, mamoru) == 0x7 ? 1 : -1];
typedef char WazaDataRecord_majikkuOffset[offsetof(WazaDataRecord, majikku) == 0x8 ? 1 : -1];
typedef char WazaDataRecord_yokodoriOffset[offsetof(WazaDataRecord, yokodori) == 0x9 ? 1 : -1];
typedef char WazaDataRecord_oumugaesiOffset[offsetof(WazaDataRecord, oumugaesi) == 0xa ? 1 : -1];
typedef char WazaDataRecord_oujanosirusiOffset[offsetof(WazaDataRecord, oujanosirusi) == 0xb ? 1 : -1];
typedef char WazaDataRecord_yubiwohuruOffset[offsetof(WazaDataRecord, yubiwohuru) == 0xc ? 1 : -1];
typedef char WazaDataRecord_monomaneOffset[offsetof(WazaDataRecord, monomane) == 0xd ? 1 : -1];
typedef char WazaDataRecord_nekonoteOffset[offsetof(WazaDataRecord, nekonote) == 0xe ? 1 : -1];
typedef char WazaDataRecord_negotoOffset[offsetof(WazaDataRecord, negoto) == 0xf ? 1 : -1];
typedef char WazaDataRecord_bouonOffset[offsetof(WazaDataRecord, bouon) == 0x10 ? 1 : -1];
typedef char WazaDataRecord_pressureOffset[offsetof(WazaDataRecord, pressure) == 0x11 ? 1 : -1];
typedef char WazaDataRecord_hidenFlagOffset[offsetof(WazaDataRecord, hidenFlag) == 0x12 ? 1 : -1];
typedef char WazaDataRecord_riskFlagOffset[offsetof(WazaDataRecord, riskFlag) == 0x14 ? 1 : -1];
typedef char WazaDataRecord_compatibleOffset[offsetof(WazaDataRecord, compatible) == 0x15 ? 1 : -1];
typedef char WazaDataRecord_iryokuOffset[offsetof(WazaDataRecord, iryoku) == 0x18 ? 1 : -1];
typedef char WazaDataRecord_fightKoukaDataIdOffset[offsetof(WazaDataRecord, fightKoukaDataId) == 0x1a ? 1 : -1];
typedef char WazaDataRecord_seqIdOffset[offsetof(WazaDataRecord, seqId) == 0x1c ? 1 : -1];
typedef char WazaDataRecord_wazaFuncDataIdOffset[offsetof(WazaDataRecord, wazaFuncDataId) == 0x1e ? 1 : -1];
typedef char WazaDataRecord_nameOffset[offsetof(WazaDataRecord, name) == 0x20 ? 1 : -1];
typedef char WazaDataRecord_fightAttackTunagiMsgIdOffset[offsetof(WazaDataRecord, fightAttackTunagiMsgId) == 0x24 ? 1 : -1];
typedef char WazaDataRecord_fightAttackMsgIdOffset[offsetof(WazaDataRecord, fightAttackMsgId) == 0x28 ? 1 : -1];
typedef char WazaDataRecord_docOffset[offsetof(WazaDataRecord, doc) == 0x2c ? 1 : -1];
typedef char WazaDataRecord_wazawzxdataIdOffset[offsetof(WazaDataRecord, wazawzxdataId) == 0x30 ? 1 : -1];
typedef char WazaDataRecord_typeIdOffset[offsetof(WazaDataRecord, typeId) == 0x34 ? 1 : -1];
// Type (zokusei) DB record, 0x30 bytes each. Table pointer: zokusei_data (0x804E87CC), count zokusei_data_number.
// matchup[defendingType] is the damage-multiplier code for this attacking type: 0x3F 1x, 0x41 2x, 0x42 0.5x, 0x43 0x.
struct TypeRecord {
    u8 kind;           // 0x0 (waza kind: physical/special group)
    u8 reserved1;      // 0x1
    u16 sprite;        // 0x2
    u16 smallSprite;   // 0x4
    u16 reserved6;     // 0x6
    u32 name;          // 0x8, message id
    u16 matchup[18];   // 0xC
};
typedef char TypeRecordSize[sizeof(TypeRecord) == 0x30 ? 1 : -1];
typedef char TypeRecord_nameOffset[offsetof(TypeRecord, name) == 0x8 ? 1 : -1];
typedef char TypeRecord_matchupOffset[offsetof(TypeRecord, matchup) == 0xC ? 1 : -1];
typedef FightWaza FightWazaRecord;
struct WazaFunctionRecord {
    void* fightTrainerAiWazaValue;
    void* fightTrainerAiWazaHit;
    void* fightTrainerAiWazaDamage;
    void* fightTrainerAiWazaDamageFightPokemon;
    void* fightWazaWzxType;
    void* fightWazaWzxVariation;
};
typedef char WazaFunctionRecordSize[sizeof(WazaFunctionRecord) == 0x18 ? 1 : -1];
extern "C" {
extern WazaDataRecord* waza_data;
extern u32* waza_data_number;
extern WazaFunctionRecord waza_func_data[];
extern TypeRecord* zokusei_data;
extern u32* zokusei_data_number;
extern u32 waza_func_data_number;
WazaDataRecord* wazaDataBiosGetPtr(u32);
WazaFunctionRecord* wazaFuncDataBiosGetPtr(u16);
u16 wazaDataBiosGetWazaFuncDataId(WazaDataRecord*);
u8 wazaCheckDarkWaza(u32);
u8 zokuseiBiosGetWazaKind(u16);
}
#endif
