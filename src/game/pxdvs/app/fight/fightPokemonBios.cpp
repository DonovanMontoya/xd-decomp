#include <dolphin/types.h>

extern "C" void* memcpy(void*, const void*, u32);
struct Pokemon {
    u8 data[0xC4];
    Pokemon& operator=(const Pokemon& o) {
        memcpy(this, &o, 0xC4);
        return *this;
    }
};
struct u64x { u32 a, b; };
struct Joutai16 { u32 w[4]; };
struct ArrA { u64x v[4]; };
struct ArrB { Joutai16 v[32]; };
struct ArrJ { Joutai16 v[0x34]; };
struct FightWazaBuf { u32 w[43]; };
struct FightItemBuf { u32 w[2]; };
struct ActionBuf { u32 w[12]; };
struct EnemySlot { u32 target; u16 oumuWaza; u16 initHp; u16 damage; u16 pad; };

struct FightPokemon {
    u32 moto;
    Pokemon buff;
    Joutai16 joutai[1];
    s16 entryId;
    u8 darkOut0;
    u8 darkOut1;
    u8 darkOut2;
    u8 darkOut3;
    u16 pad;
};

struct FightOutPokemon {
    u32 moto;
    u32 fightPokemon;
    FightPokemon hensin;
    ArrA a;
    ArrB b;
    ArrJ joutai;
    FightWazaBuf waza;
    FightWazaBuf keepWaza;
    FightItemBuf item;
    u32 x7a8;
    u32 sequence;
    u8 abi0, abi1, abi2, abi3, abi4, abi5, abi6, abi7;
    u16 hensinMotoPkxId;
    u16 s7ba;
    u16 turnCount;
    s16 meet[12];
    ActionBuf action;
    u16 zokusei[2];
    u16 tokusei;
    u32 wazaMenuCur;
    u8 g0, g1, g2, g3;
    u16 sketch, lastSelect, lastUse, lastRecv, hitWaza, hitZ;
    s16 gamanValue;
    u16 gamanTarget, oumu, s82a;
    u8 namake, successCnt;
    u16 usedItem, stockItem, s832;
    s16 damageAtkValue;
    u16 damageAtkTarget;
    s16 damageSpeValue;
    u16 damageSpeTarget;
    u8 flag0; u8 flag1; u8 flag2; u8 flag3; u8 flag4; u8 flag5; u8 flag6; u8 flag7; u8 flag8; u8 flag9; u8 flag10; u8 flag11; u8 flag12; u8 flag13; u8 flag14; u8 flag15; u8 flag16; u8 flag17; u8 flag18; u8 flag19; u8 flag20;
    u32 kaigara;
    s16 myAtkValue;
    u16 myAtkTarget;
    s16 mySpeValue;
    u16 mySpeTarget;
    u8 kizetu, u861;
    s16 irekaeTarget;
    EnemySlot enemy[4];
};

#pragma optimize_for_size on
extern "C" {

void fightOutPokemonBiosCopy(FightOutPokemon* dst, const FightOutPokemon* src) {
    if (dst == 0) { return; }
    if (src == 0) { return; }
    *dst = *src;
}

void fightOutPokemonBiosSetOumuWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x828) = v;
}

void fightOutPokemonBiosSetGamanDamageTargetId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x826) = v;
}

void fightOutPokemonBiosSetGamanDamageValue(u8* p, s16 v) {
    if (p == 0) return;
    *(s16*)(p + 0x824) = v;
}

void fightOutPokemonBiosSetHitWazaZokuseiDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x822) = v;
}

void fightOutPokemonBiosSetHitWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x820) = v;
}

void fightOutPokemonBiosSetLastReceiveWazaTargetDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x81e) = v;
}

void fightOutPokemonBiosSetLastUseWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x81c) = v;
}

void fightOutPokemonBiosSetLastSelectWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x81a) = v;
}

void fightOutPokemonBiosSetSketchWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x818) = v;
}

void* fightOutPokemonBiosGetKeepFightWazaPtr(u8* p) {
    if (p == 0) return 0;
    return p + 0x6f4;
}

u16 fightOutPokemonBiosGetOumuWazaDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x828);
}

u16 fightOutPokemonBiosGetGamanDamageTargetId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x826);
}

s16 fightOutPokemonBiosGetGamanDamageValue(u8* p) {
    if (p == 0) return 0;
    return *(s16*)(p + 0x824);
}

u16 fightOutPokemonBiosGetHitWazaZokuseiDataId(u8* p) {
    if (p == 0) return 9;
    return *(u16*)(p + 0x822);
}

u16 fightOutPokemonBiosGetHitWazaDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x820);
}

u16 fightOutPokemonBiosGetLastReceiveWazaTargetDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x81e);
}

u16 fightOutPokemonBiosGetLastUseWazaDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x81c);
}

u16 fightOutPokemonBiosGetLastSelectWazaDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x81a);
}

u16 fightOutPokemonBiosGetSketchWazaDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x818);
}

void fightOutPokemonEnemyBiosSetDamage(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x8) = v;
}

void fightOutPokemonEnemyBiosSetInitHp(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x6) = v;
}

void fightOutPokemonEnemyBiosSetOumuWazaDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x4) = v;
}

void fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(u8* p, u32 v) {
    if (p == 0) return;
    *(u32*)(p + 0x0) = v;
}

u16 fightOutPokemonEnemyBiosGetDamage(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x8);
}

u16 fightOutPokemonEnemyBiosGetInitHp(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x6);
}

u16 fightOutPokemonEnemyBiosGetOumuWazaDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x4);
}

u32 fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(u8* p) {
    if (p == 0) return 0;
    return *(u32*)(p + 0x0);
}

void* fightOutPokemonBiosGetFightOutPokemonEnemyPtr(u8* p, u16 i) {
    if (p == 0) return 0;
    if (i >= 4) return 0;
    return p + 0x864 + i * 12;
}

void fightOutPokemonBiosSetIrekaeTargetEntryId(u8* p, s16 v) {
    if (p == 0) return;
    *(s16*)(p + 0x862) = v;
}

s16 fightOutPokemonBiosGetIrekaeTargetEntryId(u8* p) {
    if (p == 0) return -1;
    return *(s16*)(p + 0x862);
}

void fightOutPokemonBiosSetKizetuFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x860) = v;
}

u8 fightOutPokemonBiosGetKizetuFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x860);
}

void fightOutPokemonBiosSetMyselfDamageSpeTargetId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x85e) = v;
}

void fightOutPokemonBiosSetMyselfDamageSpeValue(u8* p, s16 v) {
    if (p == 0) return;
    *(s16*)(p + 0x85c) = v;
}

void fightOutPokemonBiosSetMyselfDamageAtkTargetId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x85a) = v;
}

void fightOutPokemonBiosSetMyselfDamageAtkValue(u8* p, s16 v) {
    if (p == 0) return;
    *(s16*)(p + 0x858) = v;
}

void fightOutPokemonBiosSetKaigaraDamageValue(u8* p, u32 v) {
    if (p == 0) return;
    *(u32*)(p + 0x854) = v;
}

void fightOutPokemonBiosSetItemKoraetaFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x850) = v;
}

void fightOutPokemonBiosSetIrekaetaFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x84f) = v;
}

void fightOutPokemonBiosSetNoPressureFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x84e) = v;
}

void fightOutPokemonBiosSetDoTraceFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x84d) = v;
}

void fightOutPokemonBiosSetDoIkakuFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x84c) = v;
}

void fightOutPokemonBiosSetVanishoffFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x84b) = v;
}

void fightOutPokemonBiosSetReceivesWazaHiraishinFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x84a) = v;
}

void fightOutPokemonBiosSetDoClearbodyFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x849) = v;
}

void fightOutPokemonBiosSetFightActionFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x848) = v;
}

void fightOutPokemonBiosSetPassPpdecFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x847) = v;
}

void fightOutPokemonBiosSetHirumuNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x846) = v;
}

void fightOutPokemonBiosSetIchamonNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x845) = v;
}

void fightOutPokemonBiosSetChouhatsuNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x844) = v;
}

void fightOutPokemonBiosSetKanashibariNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x843) = v;
}

void fightOutPokemonBiosSetMeroMeroNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x842) = v;
}

void fightOutPokemonBiosSetHuuinNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x841) = v;
}

void fightOutPokemonBiosSetItemNigeruFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x840) = v;
}

void fightOutPokemonBiosSetTameWazaFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x83f) = v;
}

void fightOutPokemonBiosSetOutWazaKoukanaiFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x83e) = v;
}

void fightOutPokemonBiosSetKonranMyselfAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x83d) = v;
}

void fightOutPokemonBiosSetMahiNoAttackFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x83c) = v;
}

u16 fightOutPokemonBiosGetMyselfDamageSpeTargetId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x85e);
}

s16 fightOutPokemonBiosGetMyselfDamageSpeValue(u8* p) {
    if (p == 0) return 0;
    return *(s16*)(p + 0x85c);
}

u16 fightOutPokemonBiosGetMyselfDamageAtkTargetId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x85a);
}

s16 fightOutPokemonBiosGetMyselfDamageAtkValue(u8* p) {
    if (p == 0) return 0;
    return *(s16*)(p + 0x858);
}

u32 fightOutPokemonBiosGetKaigaraDamageValue(u8* p) {
    if (p == 0) return 0;
    return *(u32*)(p + 0x854);
}

u8 fightOutPokemonBiosGetItemKoraetaFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x850);
}

u8 fightOutPokemonBiosGetIrekaetaFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x84f);
}

u8 fightOutPokemonBiosGetNoPressureFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x84e);
}

u8 fightOutPokemonBiosGetDoTraceFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x84d);
}

u8 fightOutPokemonBiosGetDoIkakuFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x84c);
}

u8 fightOutPokemonBiosGetVanishoffFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x84b);
}

u8 fightOutPokemonBiosGetReceivesWazaHiraishinFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x84a);
}

u8 fightOutPokemonBiosGetDoClearbodyFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x849);
}

u8 fightOutPokemonBiosGetFightActionFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x848);
}

u8 fightOutPokemonBiosGetPassPpdecFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x847);
}

u8 fightOutPokemonBiosGetHirumuNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x846);
}

u8 fightOutPokemonBiosGetIchamonNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x845);
}

u8 fightOutPokemonBiosGetChouhatsuNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x844);
}

u8 fightOutPokemonBiosGetKanashibariNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x843);
}

u8 fightOutPokemonBiosGetMeroMeroNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x842);
}

u8 fightOutPokemonBiosGetHuuinNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x841);
}

u8 fightOutPokemonBiosGetItemNigeruFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x840);
}

u8 fightOutPokemonBiosGetTameWazaFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x83f);
}

u8 fightOutPokemonBiosGetOutWazaKoukanaiFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x83e);
}

u8 fightOutPokemonBiosGetKonranMyselfAttackFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x83d);
}

u8 fightOutPokemonBiosGetMahiNoAttackFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x83c);
}

void* fightOutPokemonBiosGetWazaMenuCurPtr(u8* p) {
    if (p == 0) return 0;
    return p + 0x810;
}

void fightOutPokemonBiosSetTokuseiDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x80c) = v;
}

u16 fightOutPokemonBiosGetTokuseiDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x80c);
}

void fightOutPokemonBiosSetZokuseiDataId(u8* p, u8 i, u16 v) {
    if (p == 0) return;
    if (i >= 2) return;
    ((u16*)(p + 0x808))[i] = v;
}

u16 fightOutPokemonBiosGetZokuseiDataId(u8* p, u8 i) {
    if (p == 0) return 0;
    if (i >= 2) return 0;
    return ((u16*)(p + 0x808))[i];
}

void* fightOutPokemonBiosGetFightActionBuffPtr(u8* p) {
    if (p == 0) return 0;
    return p + 0x7d8;
}

void fightOutPokemonBiosSetMeetEnemyFightPokemonEntryId(u8* p, u8 i, s16 v) {
    if (p == 0) return;
    if (i >= 12) return;
    ((s16*)(p + 0x7be))[i] = v;
}

s16 fightOutPokemonBiosGetMeetEnemyFightPokemonEntryId(u8* p, u8 i) {
    if (p == 0) return -1;
    if (i >= 12) return -1;
    return ((s16*)(p + 0x7be))[i];
}

void fightOutPokemonBiosSetDamageSpeTargetId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x83a) = v;
}

void fightOutPokemonBiosSetDamageSpeValue(u8* p, s16 v) {
    if (p == 0) return;
    *(s16*)(p + 0x838) = v;
}

void fightOutPokemonBiosSetDamageAtkTargetId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x836) = v;
}

void fightOutPokemonBiosSetDamageAtkValue(u8* p, s16 v) {
    if (p == 0) return;
    *(s16*)(p + 0x834) = v;
}

void fightOutPokemonBiosSetSuccessCnt(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x82d) = v;
}

void fightOutPokemonBiosSetStockItemDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x830) = v;
}

void fightOutPokemonBiosSetUsedItemDataId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x82e) = v;
}

void fightOutPokemonBiosSetNamakeFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x82c) = v;
}

u16 fightOutPokemonBiosGetDamageSpeTargetId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x83a);
}

s16 fightOutPokemonBiosGetDamageSpeValue(u8* p) {
    if (p == 0) return 0;
    return *(s16*)(p + 0x838);
}

u16 fightOutPokemonBiosGetDamageAtkTargetId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x836);
}

s16 fightOutPokemonBiosGetDamageAtkValue(u8* p) {
    if (p == 0) return 0;
    return *(s16*)(p + 0x834);
}

u8 fightOutPokemonBiosGetSuccessCnt(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x82d);
}

u16 fightOutPokemonBiosGetStockItemDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x830);
}

u16 fightOutPokemonBiosGetUsedItemDataId(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x82e);
}

u8 fightOutPokemonBiosGetNamakeFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x82c);
}

void fightOutPokemonBiosSetSequencePtr(u8* p, u32 v) {
    if (p == 0) return;
    *(u32*)(p + 0x7ac) = v;
}

u32 fightOutPokemonBiosGetSequencePtr(u8* p) {
    if (p == 0) return 0;
    return *(u32*)(p + 0x7ac);
}

void fightOutPokemonBiosSetFightoutTurnCount(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x7bc) = v;
}

void fightOutPokemonBiosSetHensinMotoPkxId(u8* p, u16 v) {
    if (p == 0) return;
    *(u16*)(p + 0x7b8) = v;
}

void fightOutPokemonBiosSetAbicntAvoid(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x7b6) = v;
}

void fightOutPokemonBiosSetAbicntAverage(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x7b5) = v;
}

void fightOutPokemonBiosSetAbicntNimbleness(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x7b4) = v;
}

void fightOutPokemonBiosSetAbicntSpeDef(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x7b3) = v;
}

void fightOutPokemonBiosSetAbicntSpeAtk(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x7b2) = v;
}

void fightOutPokemonBiosSetAbicntPhyDef(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x7b1) = v;
}

void fightOutPokemonBiosSetAbicntPhyAtk(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0x7b0) = v;
}

void fightOutPokemonBiosSetFightPokemonPtr(u8* p, u32 v) {
    if (p == 0) return;
    *(u32*)(p + 0x4) = v;
}

void fightOutPokemonBiosSetMotoFightPokemonPtr(u8* p, u32 v) {
    if (p == 0) return;
    *(u32*)(p + 0x0) = v;
}

void fightPokemonBiosSetHokakuFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0xdd) = v;
}

u8 fightPokemonBiosGetHokakuFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0xdd);
}

void fightPokemonBiosSetDarkOutFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0xdc) = v;
}

void fightPokemonBiosSetLevelUpFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0xdb) = v;
}

void fightPokemonBiosSetCatchEntryFlag(u8* p, u8 v) {
    if (p == 0) return;
    *(u8*)(p + 0xda) = v;
}

void fightPokemonBiosSetEntryId(u8* p, s16 v) {
    if (p == 0) return;
    *(s16*)(p + 0xd8) = v;
}

void fightPokemonBiosSetMotoPokemonPtr(u8* p, u32 v) {
    if (p == 0) return;
    *(u32*)(p + 0x0) = v;
}

u16 fightOutPokemonBiosGetFightoutTurnCount(u8* p) {
    if (p == 0) return 0;
    return *(u16*)(p + 0x7bc);
}

u8 fightOutPokemonBiosGetAbicntAvoid(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x7b6);
}

u8 fightOutPokemonBiosGetAbicntAverage(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x7b5);
}

u8 fightOutPokemonBiosGetAbicntNimbleness(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x7b4);
}

u8 fightOutPokemonBiosGetAbicntSpeDef(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x7b3);
}

u8 fightOutPokemonBiosGetAbicntSpeAtk(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x7b2);
}

u8 fightOutPokemonBiosGetAbicntPhyDef(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x7b1);
}

u8 fightOutPokemonBiosGetAbicntPhyAtk(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0x7b0);
}

void* fightOutPokemonBiosGetFightItemPtr(u8* p) {
    if (p == 0) return 0;
    return p + 0x7a0;
}

void* fightOutPokemonBiosGetFightWazaPtr(u8* p) {
    if (p == 0) return 0;
    return p + 0x648;
}

void* fightOutPokemonBiosGetFightoutJoutaiPtr(u8* p, u16 i) {
    if (p == 0) return 0;
    if (i >= 0x34) return 0;
    return p + 0x308 + i * 16;
}

void* fightOutPokemonBiosGetFightPokemonHensinBuffPtr(u8* p) {
    if (p == 0) return 0;
    return p + 0x8;
}

u32 fightOutPokemonBiosGetFightPokemonPtr(u8* p) {
    if (p == 0) return 0;
    return *(u32*)(p + 0x4);
}

u32 fightOutPokemonBiosGetMotoFightPokemonPtr(u8* p) {
    if (p == 0) return 0;
    return *(u32*)(p + 0x0);
}

u8 fightPokemonBiosGetDarkOutFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0xdc);
}

u8 fightPokemonBiosGetLevelUpFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0xdb);
}

u8 fightPokemonBiosGetCatchEntryFlag(u8* p) {
    if (p == 0) return 0;
    return *(u8*)(p + 0xda);
}

s16 fightPokemonBiosGetEntryId(u8* p) {
    if (p == 0) return -1;
    return *(s16*)(p + 0xd8);
}

void* fightPokemonBiosGetFightJoutaiPtr(u8* p, u16 i) {
    if (p == 0) return 0;
    if (i >= 1) return 0;
    return p + 0xc8 + i * 16;
}

void* fightPokemonBiosGetPokemonBuffPtr(u8* p) {
    if (p == 0) return 0;
    return p + 0x4;
}

u32 fightPokemonBiosGetMotoPokemonPtr(u8* p) {
    if (p == 0) return 0;
    return *(u32*)(p + 0x0);
}

}
