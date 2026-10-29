#include <game/pxdvs/app/fight/fightSeq/fightSeqWazaseqPrivate.hpp>

extern "C" {
extern u8* UserWork;
extern s32 ServerStatusFlag;
extern u16 PushWazaNo;
extern u8 fight_seq_banme_buff;
extern u8 fight_seq_banme_max;
extern s8 fight_seq_renzoku_count;
extern s32 WazaDamage;
extern u8 JitabataTbl[]; extern u16 KetaguriTbl[]; extern u32 AbiCntMsgTbl[]; extern u16 YubihuriNGTbl[]; extern u8* WazaEffectTbl[];
extern u8 WAZA_ClearBody[];
extern u8 WAZA_Donkan[];
extern u8 WAZA_Ganzyou[];
extern u8 WAZA_HitCalcOnly[];
extern u8 WAZA_Hukitobashi[];
extern u8 WAZA_HukitobashiFightEnd[];
extern u8 WAZA_IkakuLoop[];
extern u8 WAZA_Kaifuku[];
extern u8 WAZA_Kairikibasami[];
extern u8 WAZA_MakibishiEscape[];
extern u8 WAZA_Mantan[];
extern u8 WAZA_Nekonikoban[];
extern u8 WAZA_Nentyaku[];
extern u8 WAZA_NormalNohitWait[];
extern u8 WAZA_ShimeEscape[];
extern u8 WAZA_Shimerike[];
extern u8 WAZA_Shiroikiri[];
extern u8 WAZA_ShizennochikaraHitMsg[];
extern u8 WAZA_Umakukimaran[];
extern u8 WAZA_YadorigiEscape[];
}

extern "C" {
u8 fightSeqCheckYubiwohuruWazaDataId(u16);
u8 fightSeqCondChgAct(u8, u8, u8, u8*);
s8 fightSeqCondChgActParaIdToValue(u8);
u16 fightSeqCondChgActTypeToPokemonStatusId(u8);
u32 fightSeqGetHukuroDatakiDamage(u16, u16, u16, u32, u16);
u8 fightSeqGetJitabataIryoku(u16, u16);
u16 fightSeqGetKetaguriIryoku(u32);
u16 fightSeqGetOngaesiIryoku(u32);
s32 fightSeqGetTemotiPokemonNekonoteWazaDataAry(void*, u16*, u16, void*);
u8 fightSeqGetTextureZokuseiAry(void*, s32*);
u16 fightSeqGetYatuatariIryoku(u32);
u8 fightSeqIsDoItemGetWaza(void*);
u8 fightSeqIsEncoreNgWazaDataId(u16);
u8 fightSeqIsSketchNgWazaDataId(u16);
void fightSeqMichidureCheckAct();
u8 fightSeqMonomaneNGCheck(u16);
u8 fightSeqRendouWazaCheck(u16);
bool fightSeqSawaguCheck(void*);
u8 fightSeqTameWazaCheck(u16);
s32 fightSeqTameWazaTurnCheck(u16, u16);
}
static s32 _WsHuuinSub(void*, u16, void*);
static s32 _fightSeqWsIkakuSub(void*, u16, void*);
static s32 _fightSeqWsHorobinoutaSub(void*, u16, void*);
static s32 _fightSeqSawaguCheckSub(void*, u16, void*);
static s32 _fightSeqWsKuroikiriSub(void*, u16, void*);
static u8 _fightSeq_IsTrickCheck(FightOutPokemon*, FightOutPokemon*);
static void _fightSeqDamageHanekaesi(u16, u16, u8, u32);
static u8 _fightSeqHukitobashiCheck(FightOutPokemon*, FightOutPokemon*, u32);
static u8 fightSeqGetNumDotto(u16, u16, u8);
s32 _fightOutPokemonGetFightOutPokemonAllyOumuWazaDataIdAry(FightOutPokemon*);
typedef u32 (*WideGetHpFn)(void*);
typedef u32 (*WideGetLevelFn)(void*);
#define WIDE_GET_HP ((WideGetHpFn)pokemon_GetHp)
#define WIDE_GET_LEVEL ((WideGetLevelFn)figthOutPokemonGetLevel)

extern "C" {
void WS_TELEPORT(void) {
    u8* seq;
    void* encount;
    encount = fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0));
    seq = fightSeq_GetWazaSeq();
    if (fightEncountDataBiosGetFightKind(encount) != 0xc) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    fightFloorSetFightResultId(0, 2);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_DARKREMOVE(void) {
    FightSide* side;
    u8 count;
    char* name;
    FightOutPokemon* attacker;
    count = 0;
    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    side = (FightSide*)fightTargetGetPtrAsNowFightType(3, attacker);
    if (fightSideIsJoutaiDataId(side, 0x49) == 1) {
        name = GSmsgGetGSchar(wazaGetStatus(0, 0x71, 1, 0));
        fightMsgctrlSetValue(0x28, (u32)name);
        count = 1;
    }
    if (fightSideIsJoutaiDataId(side, 0x48) == 1) {
        name = GSmsgGetGSchar(wazaGetStatus(0, 0x73, 1, 0));
        switch (count) {
        case 0:
            fightMsgctrlSetValue(0x28, (u32)name);
            break;
        case 1:
            fightMsgctrlSetValue(0xd, (u32)name);
            break;
        }
        count += 1;
    }
    if (fightSideIsJoutaiDataId(side, 0x4b) == 1) {
        name = GSmsgGetGSchar(wazaGetStatus(0, 0xdb, 1, 0));
        switch (count) {
        case 0:
            fightMsgctrlSetValue(0x28, (u32)name);
            break;
        case 1:
            fightMsgctrlSetValue(0xd, (u32)name);
            break;
        case 2:
            fightMsgctrlSetValue(0xe, (u32)name);
            break;
        }
        count += 1;
    }
    if (count == 0) {
        fightSeq_JumpWazaSeq(WAZA_Umakukimaran);
        return;
    }
    switch (count) {
    case 1:
        ServerWork.flags[5] = 0;
        break;
    case 2:
        ServerWork.flags[5] = 1;
        break;
    case 3:
        ServerWork.flags[5] = 2;
        break;
    }
    fightSideInitJoutaiDataId((u8*)side, 0x49);
    fightSideInitJoutaiDataId((u8*)side, 0x48);
    fightSideInitJoutaiDataId((u8*)side, 0x4b);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KAWARAWARI(void) {
    FightSide* side;
    FightOutPokemon* attacker;
    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    side = (FightSide*)fightTargetGetPtrAsNowFightType(3, attacker);
    if (fightSideIsJoutaiDataId(side, 0x49) == 1 || fightSideIsJoutaiDataId(side, 0x48) == 1) {
        if (fightSideIsJoutaiDataId(side, 0x49) == 1 && fightSideIsJoutaiDataId(side, 0x48) == 1) {
            fightSideInitJoutaiDataId((u8*)side, 0x49);
            fightSideInitJoutaiDataId((u8*)side, 0x48);
            UserWork[0x16002] = 3;
            UserWork[0x160a1] = 3;
        } else if (fightSideIsJoutaiDataId(side, 0x49) == 1) {
            fightSideInitJoutaiDataId((u8*)side, 0x49);
            UserWork[0x16002] = 1;
            UserWork[0x160a1] = 1;
        } else if (fightSideIsJoutaiDataId(side, 0x48) == 1) {
            fightSideInitJoutaiDataId((u8*)side, 0x48);
            UserWork[0x16002] = 2;
            UserWork[0x160a1] = 2;
        }
    } else {
        UserWork[0x16002] = 0;
        UserWork[0x160a1] = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_YOKODORI_CLIENT_SET(void) {
    FightOutPokemon* def;
    FightOutPokemon* second;
    FightOutPokemon* first;
    FightOutPokemon* tuika;
    FightOutPokemon* other;
    bool same;
    fightSeq_GetWazaSeq();
    first = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    def = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    other = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x19, 0);
    tuika = first;
    fightFloor_SetTuikakoukaPokemonPtr(0, first);
    same = first == def;
    if (same != 0) {
        second = other;
        first = other;
    }
    if (same == 0) {
        second = other;
    }
    fightFloor_SetAppointPokemonPtr(0, tuika);
    fightFloor_SetAttackPokemonPtr(0, first);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, second);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HUKITOBASHI_OIUCHI(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_HOGOSYOKU(void) {
    u8 zokusei;
    u8* seq;
    u8 i;
    FightOutPokemon* pokemon;
    u32 t;
    zokusei = fightFloor_GetTikeiDataId(0);
    seq = fightSeq_GetWazaSeq();
    pokemon = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    t = tikeiDataBiosGetZokuseiDataId(zokusei);
    zokusei = t;
    if (fightOutPokemonIsZokuseiDataId(pokemon, zokusei) == 0) {
        for (i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(pokemon, i, zokusei);
        }
        fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(zokuseiBiosGetName(zokusei)));
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
}
}

extern "C" {
void WS_RECYCLE(void) {
    u8* seq;
    FightOutPokemon* pokemon;
    u16 soubi;
    u16 used;
    seq = fightSeq_GetWazaSeq();
    pokemon = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    soubi = fightOutPokemonGetSoubiItemDataId(pokemon);
    used = fightOutPokemon_GetUsedItemDataId(pokemon);
    if (used != 0 && soubi == 0) {
        fightFloor_SetAppointItemDataId(0, used);
        fightOutPokemonDoItemSoubi(pokemon, used, 1, 1);
        fightSeqCheckSetHensinBuffToMotoPokemon(pokemon, 0x82);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
}
}

extern "C" {
void WS_WEATHER_BALL(void) {
    FightWaza* waza;
    u8 weather;
    FightWaza* wazaCopy;
    fightSeq_GetWazaSeq();
    weather = fightFloorGetNowTenkouDataId(0, 1);
    waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    wazaCopy = waza;
    if (weather == 2) {
        fightWaza_SetZokusei(waza, 0xb);
        fightWaza_SetDamageValue(wazaCopy, 2);
    } else if (weather == 3) {
        fightWaza_SetZokusei(waza, 5);
        fightWaza_SetDamageValue(wazaCopy, 2);
    } else if (weather == 1) {
        fightWaza_SetZokusei(waza, 0xa);
        fightWaza_SetDamageValue(wazaCopy, 2);
    } else if (weather == 4) {
        fightWaza_SetZokusei(waza, 0xf);
        fightWaza_SetDamageValue(wazaCopy, 2);
    } else if (weather == 5) {
        fightWaza_SetZokusei(waza, 0);
        fightWaza_SetDamageValue(wazaCopy, 2);
    } else {
        fightWaza_SetZokusei(waza, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_ASOBI(void) {
    u8* seq;
    u16 seqId;
    FightOutPokemon* pokemon;
    u8 ok;
    pokemon = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemonGetTokuseiDataId(pokemon);
    seqId = wazaDB_GetSeqId(fightOutPokemon_GetUseWazaDataId(pokemon));
    ok = 0;
    seq = fightSeq_GetWazaSeq();
    if (seqId == 0xc9) {
        if (fightOutPokemonCheckWriteJoutaiDataId(pokemon, 0x38) == 2) {
            fightOutPokemonWriteJoutaiDataId(pokemon, 0x38, 0);
            ServerWork.flags[5] = 0;
            ok = 1;
        }
    } else if (fightOutPokemonCheckWriteJoutaiDataId(pokemon, 0x39) == 2) {
        fightOutPokemonWriteJoutaiDataId(pokemon, 0x39, 0);
        ServerWork.flags[5] = 1;
        ok = 1;
    }
    if (ok != 0) {
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
}
}

extern "C" {
void WS_TENKIYA_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeqFightOutPokemonTokuseiCheckTenkiya();
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_TENKIYA(void) {
    fightSeq_GetWazaSeq();
    if (fightOutPokemonIsJoutaiDataId(fightTargetGetPtrAsNowFightType(0x19, 0), 0x14) == 0) {
        UserWork[0x1609b] = UserWork[0x1609b] | 0x80;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_MONOHIROI(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HIMITUNOTIKARA(void) {
    u8 tikei;
    tikei = fightFloor_GetTikeiDataId(0);
    fightSeq_GetWazaSeq();
    ServerWork.flags[3] = tikeiDataBiosGetFightKoukaId(tikei);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HP_CHECK(void) {
    u8* seq;
    seq = fightSeq_GetWazaSeq();
    if (fightOutPokemonCheckFightOut(fightTargetGetPtrAsNowFightType(seq[1], 0)) == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 2));
        return;
    }
    fightSeq_NextWazaSeq(6);
}
}

extern "C" {
void WS_SIZENKAIHUKU(void) {
    FightOutPokemon* pokemon;
    Pokemon* poke;
    pokemon = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    poke = fightOutPokemonGetPokemonPtr(pokemon);
    if (fightOutPokemonGetTokuseiDataId(pokemon) == 0x1e) {
        pokemonInitJoutai(poke);
        fightOutPokemonResetSeqStatus(pokemon, 0);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x17);
        fightSeqCheckSetHensinBuffToMotoPokemon(pokemon, 0x7c);
    }
    fightSeq_NextWazaSeq(2);
}
}

extern "C" {
void WS_IKAKU(void) {
    void *temp_r31;

    temp_r31 = fightTargetGetPtrAsNowFightType(0x19, 0);
    fightSeq_GetWazaSeq();
    fightFloorLoopValidFightOutPokemon(0, _fightSeqWsIkakuSub, temp_r31, 0);
    fightSeq_NextWazaSeq(5);
}
}

static s32 _fightSeqWsIkakuSub(void* arg0, u16, void* arg2) {
    FightOutPokemon* pokemon = (FightOutPokemon*)arg0;
    FightOutPokemon* other = (FightOutPokemon*)arg2;
    u16 tokusei = fightOutPokemonGetTokuseiDataId(other);
    if (fightOutPokemonCheckFightOut(pokemon) == 0) {
        return 1;
    }
    if (fightOutPokemonIsAlly(pokemon, other) == 0) {
        fightFloor_SetDefensePokemonPtr(0, pokemon);
        fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(tokusei))));
        fightSeq_CallWazaSeq(WAZA_IkakuLoop);
    }
    return 1;
}

extern "C" {
void WS_YOKODORI(void) {
    u8* seq;
    FightOutPokemon* pokemon;
    seq = fightSeq_GetWazaSeq();
    pokemon = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemon_SetNoPressureFlag(pokemon, 1);
    if (fightFloorIsLastActionFightOutPokemon(0) == 1) {
jump:
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    if (fightOutPokemonCheckWriteJoutaiDataId(pokemon, 0x33) != 2) {
        goto jump;
    }
    fightOutPokemonWriteJoutaiDataId(pokemon, 0x33, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_MAGICCORT(void) {
    u8* seq;
    FightOutPokemon* pokemon;
    seq = fightSeq_GetWazaSeq();
    pokemon = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, pokemon);
    fightOutPokemon_SetNoPressureFlag(pokemon, 1);
    if (fightFloorIsLastActionFightOutPokemon(0) == 1) {
jump:
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    if (fightOutPokemonCheckWriteJoutaiDataId(pokemon, 0x37) != 2) {
        goto jump;
    }
    fightOutPokemonWriteJoutaiDataId(pokemon, 0x37, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
#pragma opt_dead_assignments off
void WS_NEKONOTE(void) {
    u16 buf[0x18];
    s32 count;
    u8* seq;
    FightOutPokemon* attacker;
    u8 fightType;
    u16 rnd;
    s32 quot;
    u16 wazaId;
    FightOutPokemon* defender;

    fightType = fightFloor_GetFightType(0);
    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    count = fightSeqGetTemotiPokemonNekonoteWazaDataAry(fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attacker), buf, 0x18, attacker);
    if (count != 0) {
        rnd = HSD_Rand();
        ServerStatusFlag &= 0xfffffbff;
        quot = rnd / count;
        wazaId = buf[rnd - quot * count];
        PushWazaNo = wazaId;
        defender = fightSeqSelectDefensePokemonPtr(attacker, wazaId, fightType, 0, 1, 1, -1);
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, defender);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
}
#pragma opt_dead_assignments reset
}

extern "C" {
s32 fightSeqGetTemotiPokemonNekonoteWazaDataAry(void* trainer, u16* out, u16 maxCount, void* pokemon) {
    u32 moto;
    u16 t;
    s32 j;
    Pokemon* entryPokemon;
    u32 entry;
    void* hero;
    s32 idx;
    s32 count;
    s32 i;
    u16 wazaId;
    s32 k;

    hero = fightTrainer_GetHeroPtr(trainer);
    moto = (u32)fightOutPokemon_GetMotoFightPokemonPtr(pokemon);
    for (i = 0; i < maxCount; i++) {
        out[i] = 0;
    }
    count = 0;
    j = 0;
    do {
        entry = heroGetStatus(hero, 3, j);
        entry = (u32)fightTrainerCheckTemotiPokemonFightEntry(trainer, entry);
        if (entry != 0 && moto != entry) {
            entryPokemon = fightPokemonGetPokemonPtr((void*)entry);
            k = 0;
            do {
                if (pokemonWazaCheckValid(entryPokemon, k) != 0) {
                    wazaId = pokemon_GetPokemonWazaDataId(entryPokemon, k);
                    if (fightSeqRendouWazaCheck(wazaId) == 0) {
                        for (idx = 0; (t = YubihuriNGTbl[idx]) != 0xffff; idx++) {
                            if (wazaId == t) {
                                break;
                            }
                        }
                        if (t == 0xffff && wazaId != 0 && wazaId != 0x176 && count < maxCount) {
                            out[count] = wazaId;
                            count++;
                        }
                    }
                }
                k++;
            } while (k < 4);
        }
        j++;
    } while (j < 6);
    return count;
}
}

extern "C" {
void WS_KETAGURI(void) {
    FightWaza* waza;
    u32 weight;
    u16 power;
    fightSeq_GetWazaSeq();
    waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    weight = pokemonDB_GetWeight(figthOutPokemonGetPokemonDataId(fightTargetGetPtrAsNowFightType(0x12, 0)));
    power = fightSeqGetKetaguriIryoku(weight);
    fightWaza_SetIryoku(waza, power);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
u16 fightSeqGetKetaguriIryoku(u32 weightArg) {
    u16 turn = weightArg;
    u16 i;
    u16 cur;
    i = 0;
    while ((cur = KetaguriTbl[i]) != 0xffff) {
        if (cur > turn) break;
        i += 2;
    }
    if (cur != 0xffff) return KetaguriTbl[i + 1];
    return 0x78;
}
}

extern "C" {
void WS_ONNEN(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x28) == 2) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x28, 0);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
}
}

extern "C" {
void WS_HUUIN(void) {
    struct { FightOutPokemon* pokemon; s32 flag; } work;
    u8* seq;
    FightOutPokemon* attacker;

    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(attacker, 0x27) != 2) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    fightSeqPressurePpdecCheckHuuin(attacker);
    work.pokemon = attacker;
    work.flag = 0;
    fightFloorLoopValidFightOutPokemon(0, _WsHuuinSub, &work, 0);
    if (work.flag == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(attacker, 0x27, 0);
    fightSeq_NextWazaSeq(5);
}
}

static s32 _WsHuuinSub(void* arg0, u16, void* arg) {
    FightOutPokemon* pokemon = (FightOutPokemon*)arg0;
    FightOutPokemon* attacker = *(FightOutPokemon**)arg;
    if (fightOutPokemonCheckFightOut(pokemon) == 0) {
        return 1;
    }
    if (fightOutPokemonIsAlly(pokemon, attacker) == 1) {
        return 1;
    }
    Pokemon* attackerPokemon = fightOutPokemonGetPokemonPtr(attacker);
    Pokemon* myPokemon = fightOutPokemonGetPokemonPtr(pokemon);
    s8 i;
    u16 waza;
    for (i = 0; i < 4; i++) {
        if (pokemonWazaCheckValid(attackerPokemon, i) != 0 && (waza = pokemon_GetPokemonWazaDataId(attackerPokemon, i), pokemonSearchWazaDataId(myPokemon, waza) >= 0)) {
            *(s32*)((u8*)arg + 4) = 1;
            return 0;
        }
    }
    return 1;
}

extern "C" {
void WS_SKILLSWAP(void) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r29;
    FightOutPokemon *temp_r3_2;
    u16 temp_r27;
    u16 temp_r26;
    u16 temp_r25;
    u8 *temp_r31;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r29 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r27 = fightOutPokemonGetTokuseiDataId(temp_r3);
    temp_r25 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r26 = fightOutPokemonGetTokuseiDataId(temp_r3_2);
    if (((temp_r27 == 0) && (temp_r26 == 0)) || (temp_r27 == 0x19) || (temp_r26 == 0x19) || (fightWazaIsHit(temp_r29) == 0) || (fightSeqRegulationCheck(temp_r25, temp_r3, temp_r3_2) == 1)) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    fightOutPokemonSetTokuseiDataId(temp_r3, temp_r26);
    fightOutPokemonSetTokuseiDataId(temp_r3_2, temp_r27);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_HUNKA(void) {
    u16 var_r4;
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    u16 temp_r30;
    FightWaza *temp_r28;

    fightSeq_GetWazaSeq();
    if (!(ServerStatusFlag & 0x200)) {
        temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
        temp_r28 = fightOutPokemon_GetFightWazaPtr(temp_r3);
        fightOutPokemon_GetUseWazaDataId(temp_r3);
        temp_r30 = fightWaza_GetIryoku(temp_r28);
        temp_r31 = pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r3));
        u16 maxHp = pokemon_GetMaxHp(fightOutPokemonGetPokemonPtr(temp_r3));
        var_r4 = (u16) ((s32) (temp_r30 * temp_r31) / (s32) maxHp);
        if (var_r4 == 0) {
            var_r4 = 1;
        }
        fightWaza_SetIryoku(temp_r28, var_r4);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_GAMUSYARA(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    FightWaza *temp_r30;
    u16 temp_r3_2;
    u16 temp_r29;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r29 = WIDE_GET_HP(fightOutPokemonGetPokemonPtr(temp_r3));
    temp_r3_2 = WIDE_GET_HP(fightOutPokemonGetPokemonPtr(fightTargetGetPtrAsNowFightType(0x12, 0)));
    if ((s32) temp_r3_2 <= (s32) temp_r29) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    fightWaza_SetDamage(temp_r30, temp_r3_2 - temp_r29);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_AKUBI(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if ((fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x26) != 2) || (fightOutPokemonIsJoutaiNormal(temp_r3) == 0)) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r3, 0x26, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_REVENGE(void) {
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    s32 temp_r30;
    u32 temp_r3_2;
    u16 temp_r29;
    s32 temp_r28;
    FightWaza *temp_r27;
    u8 temp_r26;

    temp_r26 = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r27 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r28 = fightOutPokemon_GetDamageAtkValue(temp_r3);
    temp_r29 = fightOutPokemon_GetDamageAtkTargetId(temp_r3);
    temp_r30 = fightOutPokemon_GetDamageSpeValue(temp_r3);
    temp_r31 = fightOutPokemon_GetDamageSpeTargetId(temp_r3);
    temp_r3_2 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(fightTargetGetPtrAsNowFightType(0x12, 0), temp_r26);
    if ((((s16) temp_r28 != 0) && (temp_r29 == (u16) temp_r3_2)) || (((s16) temp_r30 != 0) && (temp_r31 == (u16) temp_r3_2))) {
        fightWaza_SetDamageValue(temp_r27, 2);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_NEWOHARU(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x25) != 2) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r3, 0x25, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_NEGAIGOTO(void) {
    u8 *temp_r3;
    FightOutPokemon *temp_r3_2;
    FightOutPokemon *temp_r3_3;
    u16 *temp_r29;
    FightWaza *temp_r29_2;
    u8 temp_r0;

    temp_r3 = fightSeq_GetWazaSeq();
    temp_r0 = *(u8*)(temp_r3 + 1);
    switch ((s32) temp_r0) {
    case 0:
        temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
        temp_r29 = pokemon_GetNicknamePtr(fightPokemon_GetMotoPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(temp_r3_2)));
        if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3_2, 0x35) != 2) {
            fightSeq_JumpWazaSeq(*(u8**)(temp_r3 + 2));
            return;
        }
        fightOutPokemonWriteJoutaiDataId(temp_r3_2, 0x35, 0);
        fightOutPokemonSetBuffJoutaiDataId(temp_r3_2, 0x35, (u32) temp_r29);
        fightSeq_NextWazaSeq(6);
        return;
    case 1:
        temp_r29_2 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
        temp_r3_3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
        fightMsgctrlSetValue(0xD, fightOutPokemonGetBuffJoutaiDataId(temp_r3_3, 0x35));
        fightWaza_SetDamage(temp_r29_2, (u32) -(s32) fightOutPokemonMaxHpWaruValue(temp_r3_3, 2));
        if (fightOutPokemonIsHpMantan(temp_r3_3) == 1) {
            fightSeq_JumpWazaSeq(*(u8**)(temp_r3 + 2));
            return;
        }
        fightSeq_NextWazaSeq(6);
        return;
    }
}
}

extern "C" {
void WS_NARIKIRI(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    u16 temp_r3_2;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemonGetTokuseiDataId(temp_r3);
    temp_r3_2 = fightOutPokemonGetTokuseiDataId(fightTargetGetPtrAsNowFightType(0x12, 0));
    if ((temp_r3_2 != 0) && (temp_r3_2 != 0x19)) {
        fightOutPokemonSetTokuseiDataId(temp_r3, temp_r3_2);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
}
}

extern "C" {
void WS_TRICK(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    FightOutPokemon *temp_r3_2;
    u16 temp_r28;
    u16 temp_r27;
    u16 temp_r26;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r28 = fightOutPokemonGetSoubiItemDataId(temp_r3);
    temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r26 = fightOutPokemonGetTokuseiDataId(temp_r3_2);
    temp_r27 = fightOutPokemonGetSoubiItemDataId(temp_r3_2);
    if (fightSeqIsDoItemGetWaza(temp_r3) == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    if (_fightSeq_IsTrickCheck(temp_r3, temp_r3_2) == 0) {
        fightSeq_JumpWazaSeq(fightSeq_GetWazaSeqAdr(1));
        return;
    }
    if (((temp_r28 == 0) && (temp_r27 == 0)) || (temp_r28 == 0xAF) || (temp_r27 == 0xAF) || ((temp_r28 != 0) && (itemDataCheckValid(temp_r28) == 0)) || ((temp_r27 != 0) && (itemDataCheckValid(temp_r27) == 0))) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    if (temp_r26 == 0x3C) {
        fightSeq_JumpWazaSeq(WAZA_Nentyaku);
        return;
    }
    if (temp_r28 != 0) {
        fightOutPokemonDoItemSoubi(temp_r3, 0, 0, 0);
    }
    if (temp_r27 != 0) {
        fightOutPokemonDoItemSoubi(temp_r3_2, 0, 0, 0);
    }
    if (temp_r28 != 0) {
        fightOutPokemonDoItemSoubi(temp_r3_2, temp_r28, 1, 0);
    }
    if (temp_r27 != 0) {
        fightOutPokemon_SetStockItemDataId(temp_r3, temp_r27);
    }
    fightSeqCheckSetHensinBuffToMotoPokemon(temp_r3, 0x82);
    fightSeqCheckSetHensinBuffToMotoPokemon(temp_r3_2, 0x82);
    fightOutPokemonInitJoutaiDataId(temp_r3, 0x36);
    fightOutPokemonInitJoutaiDataId(temp_r3_2, 0x36);
    fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(itemDB_GetName(temp_r27)));
    fightMsgctrlSetValue(0xE, (u32)GSmsgGetGSchar(itemDB_GetName(temp_r28)));
    if ((temp_r28 != 0) && (temp_r27 != 0)) {
        ServerWork.flags[5] = 2;
    } else if (temp_r27 != 0) {
        ServerWork.flags[5] = 0;
    } else {
        ServerWork.flags[5] = 1;
    }
    fightSeq_NextWazaSeq(5);
}
}

static u8 _fightSeq_IsTrickCheck(FightOutPokemon* arg0, FightOutPokemon* arg1) {
    if (fightFloorGetStatus(0, 0, 0x2f, 0) != 0 && (fightOutPokemonIsJoutaiDataId(arg0, 0x3d) != 0 || fightOutPokemonIsJoutaiDataId(arg1, 0x3d) != 0)) {
        return 0;
    }
    return 1;
}

extern "C" {
u8 fightSeqIsDoItemGetWaza(void* pokemon) {
    if (fightFloor_GetFightKindDorobouFlag(0) == 1) {
        return 0;
    }
    if (fightFloor_GetFightKindDorobouFlag(0) == 0 && fightOutPokemonIsJoutaiDataId(pokemon, 0x3d) == 1) {
        return 0;
    }
    return 1;
}
}

extern "C" {
void WS_TEDASUKE(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    FightOutPokemon *temp_r3_2;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0xE, temp_r3);
    if ((temp_r3_2 != 0) && (fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2) && (fightOutPokemonCheckFightOut(temp_r3_2) == 1) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x32) == 0) && (fightOutPokemonIsJoutaiDataId(temp_r3_2, 0x32) == 0)) {
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, temp_r3_2);
        if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3_2, 0x32) == 2) {
            fightOutPokemonWriteJoutaiDataId(temp_r3_2, 0x32, 0);
        }
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
}
}

extern "C" {
void WS_CHOUHATSU(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x30) != 2) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r3, 0x30, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_KIAIPUNCH(void) {
    FightOutPokemon *temp_r3;
    s32 temp_r31;
    u8 *temp_r30;
    s32 temp_r3_2;

    temp_r30 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r31 = fightOutPokemon_GetDamageAtkValue(temp_r3);
    temp_r3_2 = fightOutPokemon_GetDamageSpeValue(temp_r3);
    if (((s16) temp_r31 != 0) || ((s16) temp_r3_2 != 0)) {
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r30 + 1));
}
}

extern "C" {
void WS_ICHAMON(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x1B) != 2) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r3, 0x1B, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_REFLESH(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    Pokemon *temp_r29;

    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r29 = fightOutPokemonGetPokemonPtr(temp_r3);
    temp_r31 = fightSeq_GetWazaSeq();
    if (fightOutPokemonIsJoutaiKaragenki(temp_r3) == 1) {
        pokemonInitJoutai(temp_r29);
        fightOutPokemonResetSeqStatus(temp_r3, 0);
        fightSeq_NextWazaSeq(5);
        fightSeqCheckSetHensinBuffToMotoPokemon(temp_r3, 0x7C);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
}
}

extern "C" {
void WS_SHIZENNOCHIKARA(void) {
    u16 temp_r31;
    u8 temp_r30;
    FightOutPokemon *temp_r3;
    FightWaza *temp_r28;
    u16 temp_r3_2;
    void *defender;

    temp_r30 = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r28 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r3_2 = tikeiDataBiosGetWazaId(fightFloor_GetTikeiDataId(0));
    temp_r31 = wazaDB_GetSeqId(temp_r3_2);
    fightWazaSetUseWazaStatus(temp_r28, temp_r3_2);
    fightMsgctrlSetValue(0x28, (u32)GSmsgGetGSchar(wazaDB_GetName(temp_r3_2)));
    defender = fightSeqSelectDefensePokemonPtr(temp_r3, temp_r3_2, temp_r30, 0, 1, 1, -1);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, defender);
    ServerStatusFlag &= 0xFFFFFBFF;
    fightSeq_CallWazaSeq(WAZA_ShizennochikaraHitMsg);
    fightSeq_JumpWazaSeq(WazaEffectTbl[temp_r31]);
}
}

extern "C" {
void WS_JUUDEN(void) {
    FightOutPokemon *temp_r3;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x24) == 2) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x24, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KONOYUBITOMARE(void) {
    FightOutPokemon *temp_r3;
    FightSide *temp_r3_2;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r3_2 = (FightSide*)fightTargetGetPtrAsNowFightType(2, temp_r3);
    if (fightSideCheckWriteJoutaiDataId(temp_r3_2, 0x4D) == 2) {
        u32 relativeId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(temp_r3, fightFloor_GetFightType(0));
        fightSideWriteJoutaiDataId(temp_r3_2, 0x4D, relativeId);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_OKIMIYAGE(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    FightWaza *temp_r29;
    Pokemon *temp_r28;
    u8 temp_r27;
    s32 temp_r26_2;
    u8 temp_r26;
    u8 temp_r0;

    temp_r26 = fightFloor_GetFightType(0);
    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r29 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r26_2 = fightMenuGetFightOutPokemonPtrToStatusMenuId(temp_r3, temp_r26, 1);
    temp_r28 = (Pokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r27 = pokemonGetStatus(temp_r28, 0, fightSeqCondChgActTypeToPokemonStatusId(1), 0);
    temp_r0 = pokemonGetStatus(temp_r28, 0, fightSeqCondChgActTypeToPokemonStatusId(4), 0);
    if ((temp_r27 == 0) && (temp_r0 == 0) && ((u8) ServerWork.flags[6] != 1)) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    fightWaza_SetDamage(temp_r29, (u32) pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r3)));
    menuFightStatusSetHP(temp_r26_2, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_CHIISAKUNARU(void) {
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r31;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r31 = temp_r3;
    if ((ServerStatusFlag & 0x02000000) && (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x23) == 2)) {
        fightOutPokemonWriteJoutaiDataId(temp_r31, 0x23, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KIERUTAME_AFTAR(void) {
    FightOutPokemon *temp_r3;
    u16 temp_r3_2;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r3_2 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    switch ((s32) temp_r3_2) {
    case 0x154:
    case 0x13:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x1F) == 1) {
            fightOutPokemonInitJoutaiDataId(temp_r3, 0x1F);
        }
        break;
    case 0x5B:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x20) == 1) {
            fightOutPokemonInitJoutaiDataId(temp_r3, 0x20);
        }
        break;
    case 0x123:
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x21) == 1) {
            fightOutPokemonInitJoutaiDataId(temp_r3, 0x21);
        }
        break;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KIERUTAME(void) {
    FightOutPokemon *temp_r3;
    u16 temp_r3_2;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r3_2 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    switch ((s32) temp_r3_2) {
    case 0x154:
    case 0x13:
        if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x1F) == 2) {
            fightOutPokemonWriteJoutaiDataId(temp_r3, 0x1F, 0);
        }
        break;
    case 0x5B:
        if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x20) == 2) {
            fightOutPokemonWriteJoutaiDataId(temp_r3, 0x20, 0);
        }
        break;
    case 0x123:
        if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x21) == 2) {
            fightOutPokemonWriteJoutaiDataId(temp_r3, 0x21, 0);
        }
        break;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" void WS_HUKURODATAKI(void) {
    u8* seq;
    FightOutPokemon* attacker;
    FightOutPokemon* defender;
    FIGHT_TRAINER* trainer;
    Pokemon* pokemon;
    Hero* hero;
    u16 wazaId;
    u32 first;
    FightWaza* waza;
    FightPokemon* entry;
    u16 attackerId;
    u8 attackerLevel;
    u32 defenderId;
    u8 defenderLevel;
    s32 damage;
    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    wazaId = fightOutPokemon_GetUseWazaDataId(attacker);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, attacker);
    hero = fightTrainer_GetHeroPtr(trainer);
    defender = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if (!fightOutPokemonCheckFightOut(defender)) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    first = ServerWork.flags[0];
    pokemon = 0;
    while (ServerWork.flags[0] < 6) {
        pokemon = (Pokemon*)heroGetStatus(hero, 3, ServerWork.flags[0]);
        entry = fightTrainerCheckTemotiPokemonFightEntry(trainer, (u32)pokemon);
        if (entry && fightPokemonCheckValid(entry)) {
            pokemon = fightPokemonGetPokemonPtr(entry);
            if (pokemonCheckFightOut(pokemon) == 1 && pokemonIsJoutaiNormal(pokemon) == 1) break;
        }
        ++ServerWork.flags[0];
    }
    if (ServerWork.flags[0] < 6) {
        attackerId = pokemon_GetPokemonDataId(pokemon);
        attackerLevel = pokemon_GetLevel(pokemon);
        defenderId = figthOutPokemonGetPokemonDataId(defender);
        defenderLevel = figthOutPokemonGetLevel(defender);
        fightMsgctrlSetValue(0xd, (u32)pokemon_GetNicknamePtr(pokemon));
        damage = fightSeqGetHukuroDatakiDamage(wazaId, attackerId, attackerLevel, defenderId, defenderLevel);
        if (fightOutPokemonIsJoutaiDataId(attacker, 0x32) == 1) damage = (damage * 15) / 10;
        fightWaza_SetDamage(waza, damage);
        ++ServerWork.flags[0];
        fightSeq_NextWazaSeq(9);
    } else if (first != 0) fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
    else fightSeq_JumpWazaSeq(*(u8**)(seq + 5));
}

extern "C" {
u32 fightSeqGetHukuroDatakiDamage(u16 wazaId, u16 atkPokemonId, u16 level, u32 defPokemonId, u16 defLevel) {
    s32 damage;
    s32 base;
    s32 def;
    damage = pokemonDB_GetBasisPhyAtk(atkPokemonId);
    damage *= (u16)wazaDB_GetIryoku(wazaId);
    base = (level * 2) / 5;
    damage *= base + 2;
    def = (u16)pokemonDB_GetBasisPhyDef(defPokemonId);
    if (def <= 0) {
        def = 1;
    }
    damage /= def;
    return damage / 50 + 2;
}
}

extern "C" {
void WS_MIRAIYOCHI(void) {
    u32 temp_r31;
    u8 *temp_r30;
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r3_2;
    u32 temp_r27;
    u16 temp_r26;
    u16 temp_r25;
    s32 var_r25;
    void *temp_r24;

    temp_r31 = (u8)fightFloor_GetFightType(0);
    temp_r30 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r27 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(temp_r3, temp_r31);
    temp_r3_2 = (FightOutPokemon*)fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r26 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r25 = fightWaza_GetIryoku((FightWaza*)temp_r3_2);
    temp_r31 = fightWaza_GetZokusei((FightWaza*)temp_r3_2);
    temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r24 = fightTargetGetPtrAsNowFightType(2, temp_r3_2);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3_2, 0x34) != 2) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r30 + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r3_2, 0x34, (u16) temp_r27);
    fightOutPokemonSetIdBuffJoutaiDataId(temp_r3_2, 0x34, temp_r26);
    var_r25 = ((s32 (*)(void*, void*, void*, u16, u16, u16))fightSeqWazaDamageCalc)(temp_r3, temp_r3_2, temp_r24, temp_r26, temp_r25, temp_r31);
    if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x32) == 1) {
        var_r25 = (var_r25 * 0xF) / 10;
    }
    fightOutPokemonSetBuffJoutaiDataId(temp_r3_2, 0x34, var_r25);
    if (temp_r26 == 0x161) {
        ServerWork.flags[5] = 1;
    } else {
        ServerWork.flags[5] = 0;
    }
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_JISIN(void) {
    FightOutPokemon* attacker;
    FightOutPokemon* candidate;
    FightOutPokemon* found;
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightSeq_GetWazaSeq();
    fight_seq_banme_max = 8;
    found = 0;
    fight_seq_banme_buff = 0;
    while (fight_seq_banme_buff < fight_seq_banme_max) {
        candidate = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData();
        if (candidate != 0 && fightOutPokemonCheckFightOut(candidate) != 0 && attacker != candidate) {
            found = candidate;
            break;
        }
        fight_seq_banme_buff++;
    }
    if (found != 0) {
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, found);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_MEZAMERUPOWER(void) {
    u16 power;
    u16 type;
    FightOutPokemon* pokemon;
    FightWaza* waza;
    fightSeq_GetWazaSeq();
    pokemon = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(pokemon);
    pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(pokemon), &power, &type);
    fightWaza_SetIryoku(waza, power);
    fightWaza_SetZokusei(waza, type);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_WEATHERKAIFUKU(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    FightWaza *temp_r29;
    u8 temp_r28;
    s32 var_r0;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r29 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, temp_r3);
    temp_r28 = fightFloorGetNowTenkouDataId(0, 1);
    if (fightOutPokemonIsHpMantan(temp_r3) == 0) {
        if (temp_r28 == 0) {
            var_r0 = (u16)((u32 (*)(void*, u16))fightOutPokemonMaxHpWaruValue)(temp_r3, 2);
        } else if (temp_r28 == 1) {
            var_r0 = ((s32) (fightOutPokemonMaxHpWaruValue(temp_r3, 1) * 0x14) / 30);
        } else {
            var_r0 = (u16)((u32 (*)(void*, u16))fightOutPokemonMaxHpWaruValue)(temp_r3, 4);
        }
        fightWaza_SetDamage(temp_r29, (u32) -var_r0);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
}
}

extern "C" {
void WS_MARUKUNARU(void) {
    FightOutPokemon *temp_r3;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x1A) == 2) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x1A, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KOUSOKUSPIN(void) {
    u8 fightType;
    FightOutPokemon* attacker;
    FightSide* side;
    FightOutPokemon* target;
    FightOutPokemon* binder;
    u32 binderId;

    fightType = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    side = (FightSide*)fightTargetGetPtrAsNowFightType(2, attacker);
    target = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0xe) == 1) {
        binderId = ((u32 (*)(void*, u16))fightOutPokemonGetUserFightTargetIdJoutaiDataId)(attacker, 0xe);
        if ((u16)binderId != 0) {
            binder = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(binderId, fightType);
            if (binder != 0) {
                fightFloor_SetDefensePokemonPtr(0, binder);
                fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(wazaDB_GetName(fightOutPokemonGetIdBuffJoutaiDataId(attacker, 0xe))));
                fightOutPokemonInitJoutaiDataId(attacker, 0xe);
                fightSeq_CallWazaSeq(WAZA_ShimeEscape);
                fightFloor_SetDefensePokemonPtr(0, target);
            }
        }
    }
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x1c) == 1) {
        fightOutPokemonInitJoutaiDataId(attacker, 0x1c);
        fightSeq_CallWazaSeq(WAZA_YadorigiEscape);
    }
    if (fightSideIsJoutaiDataId(side, 0x4a) == 1) {
        fightSideInitJoutaiDataId((u8*)side, 0x4a);
        fightSeq_CallWazaSeq(WAZA_MakibishiEscape);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_JIKOANJI(void) {
    FightOutPokemon *temp_r31;

    FightOutPokemon *temp_r30;
    fightSeq_GetWazaSeq();
    temp_r31 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    fightOutPokemonCopyAllAbiCnt(temp_r31, temp_r30);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_HARADAIKO(void) {
    u8 *temp_r29;
    FightOutPokemon *temp_r3;
    FightWaza *temp_r27;
    u16 temp_r3_2;
    u16 temp_r31;
    u16 temp_r30;

    temp_r29 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r27 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r30 = pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r3));
    temp_r31 = fightOutPokemonMaxHpWaruValue(temp_r3, 2);
    temp_r3_2 = fightSeqCondChgActTypeToPokemonStatusId(1);
    if (((s8)pokemonGetStatus((Pokemon *) temp_r3, 0, temp_r3_2, 0) < 0xC) && (temp_r30 > temp_r31)) {
        pokemonSetStatus((Pokemon *) temp_r3, 0, temp_r3_2, 0, 0xC);
        fightWaza_SetDamage(temp_r27, (u32) temp_r31);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r29 + 1));
}
}

extern "C" {
void WS_OIUCHI_CHECK(void) {
    u32 targetId;
    u8* seq;
    FightOutPokemon* target;
    FightOutPokemon* cur;
    FightOutPokemon* found;
    FightWaza* waza;
    FightActionBuff* action;

    seq = fightSeq_GetWazaSeq();
    target = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x14, 0);
    targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, fightFloor_GetFightType(0));
    if (fightOutPokemonCheckFightOut(target) == 0) {
        fight_seq_banme_buff = fight_seq_banme_max;
    } else {
        cur = 0;
        found = 0;
        while (fight_seq_banme_buff < fight_seq_banme_max) {
            cur = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData();
            if (cur != 0 && fightOutPokemonCheckFightOut(cur) != 0 && target != cur && fightOutPokemonIsAlly(target, cur) != 1 && (action = fightOutPokemon_GetFightActionBuffPtr(cur)) != 0 && fightActionCheckValid(action) != 0 && fightActionGetKindDataId(action) == 0x13 && (waza = fightOutPokemon_GetFightWazaPtr(cur), fightOutPokemon_GetUseWazaDataId(cur) == 0xe4) && (u16)targetId == (u16)fightWaza_GetTargetDataId(waza) && fightOutPokemonIsJoutaiDataId(cur, 8) != 1 && fightOutPokemonIsJoutaiDataId(cur, 7) != 1 && fightOutPokemon_GetNamakeFlag(cur) != 1) {
                found = cur;
                break;
            }
            fight_seq_banme_buff++;
        }
        if (found != 0) {
            fightFloor_SetDefensePokemonPtr(0, found);
            UserWork[0x16002] = 1;
            ServerStatusFlag &= 0xfffffbff;
            fightOutPokemon_SetFightActionFlag(cur, 1);
            fightSeq_NextWazaSeq(5);
            return;
        }
    }
    fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
}
}

extern "C" {
void WS_MAGNITUDE(void) {
    u16 var_r4;
    u8 var_r31;
    FightWaza *temp_r30;
    u8 temp_r0;

    fightSeq_GetWazaSeq();
    temp_r30 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    temp_r0 = HSD_Rand() % 100;
    if (temp_r0 < 5) {
        var_r4 = 0xA;
        var_r31 = 4;
    } else if (temp_r0 < 0xF) {
        var_r4 = 0x1E;
        var_r31 = 5;
    } else if (temp_r0 < 0x23) {
        var_r4 = 0x32;
        var_r31 = 6;
    } else if (temp_r0 < 0x41) {
        var_r4 = 0x46;
        var_r31 = 7;
    } else if (temp_r0 < 0x55) {
        var_r4 = 0x5A;
        var_r31 = 8;
    } else if (temp_r0 < 0x5F) {
        var_r4 = 0x6E;
        var_r31 = 9;
    } else {
        var_r4 = 0x96;
        var_r31 = 0xA;
    }
    fightWaza_SetIryoku(temp_r30, var_r4);
    fightMsgctrlSetValue(0x2F, (u32) var_r31);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_SHINPINOMAMORI(void) {
    FightSide *temp_r3;
    void *attacker;

    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r3 = (FightSide*)fightTargetGetPtrAsNowFightType(2, attacker);
    if (fightSideCheckWriteJoutaiDataId(temp_r3, 0x4B) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork.flags[5] = 0;
    } else {
        fightSideWriteJoutaiDataId(temp_r3, 0x4B, 0);
        ServerWork.flags[5] = 5;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_PRESENT(void) {
    FightOutPokemon *temp_r31;
    FightWaza *temp_r30;
    u8 temp_r3;

    fightSeq_GetWazaSeq();
    temp_r30 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    temp_r31 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r3 = HSD_Rand();
    if (temp_r3 < 0x66) {
        fightWaza_SetIryoku(temp_r30, 0x28);
    } else if (temp_r3 < 0xB2) {
        fightWaza_SetIryoku(temp_r30, 0x50);
    } else if (temp_r3 < 0xCC) {
        fightWaza_SetIryoku(temp_r30, 0x78);
    } else {
        fightWaza_SetDamage(temp_r30, (u32) -(s32) fightOutPokemonMaxHpWaruValue(temp_r31, 4));
    }
    if (temp_r3 < 0xCC) {
        fightSeq_JumpWazaSeq(WAZA_HitCalcOnly);
        return;
    }
    if (fightOutPokemonIsHpMantan(temp_r31) == 1) {
        fightSeq_JumpWazaSeq(WAZA_Mantan);
        return;
    }
    fightWazaInitJoutaiDataId(temp_r30, 0x43);
    fightSeq_JumpWazaSeq(WAZA_Kaifuku);
}
}

extern "C" {
void WS_NATSUKI(void) {
    FightOutPokemon* pokemon;
    u16 seqId;
    FightWaza* waza;
    Pokemon* poke;
    u16 power;
    u32 friendship;
    fightSeq_GetWazaSeq();
    pokemon = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    poke = fightOutPokemonGetPokemonPtr(pokemon);
    waza = fightOutPokemon_GetFightWazaPtr(pokemon);
    seqId = wazaDB_GetSeqId(fightOutPokemon_GetUseWazaDataId(pokemon));
    friendship = pokemon_GetFriend(poke);
    if (seqId == 0x79) {
        power = fightSeqGetOngaesiIryoku(friendship);
    } else {
        power = fightSeqGetYatuatariIryoku(friendship);
    }
    fightWaza_SetIryoku(waza, power);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
u16 fightSeqGetYatuatariIryoku(u32 power) {
    return (255 - (u16)power) * 10 / 25;
}
}

extern "C" {
u16 fightSeqGetOngaesiIryoku(u32 friendship) {
    return (u16)friendship * 10 / 25;
}
}

extern "C" {
void WS_RENZOKUGIRI(void) {
    u32 var_r5;
    FightOutPokemon *temp_r3;
    s16 temp_r31;
    FightWaza *temp_r30;
    u16 temp_r29;
    s32 n;



    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r29 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    if (fightWazaIsHit(temp_r30) == 0) {
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x2E) == 1) {
            fightOutPokemonInitJoutaiDataId(temp_r3, 0x2E);
        }
        fightSeq_JumpWazaSeq(WAZA_NormalNohitWait);
        return;
    }
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x2E) == 2) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x2E, 0);
    }
    temp_r31 = fightOutPokemonGetCountAsJoutaiDataId(temp_r3, 0x2E);
    var_r5 = (u16) wazaDB_GetIryoku(temp_r29);
    for (n = 1; n < (s16) temp_r31; n++) {
        var_r5 *= 2;
    }
    fightWaza_SetIryoku(temp_r30, (u16) var_r5);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_IBARU(void) {
    u8 *temp_r31;
    u8 temp_r30;
    Pokemon *temp_r30_2;
    s8 temp_r29;
    u16 statusId;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r30 = *(u8*)(temp_r31 + 1);
    temp_r30_2 = (Pokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    statusId = fightSeqCondChgActTypeToPokemonStatusId(temp_r30);
    temp_r29 = pokemonGetStatus(temp_r30_2, 0, statusId, 0);
    if ((fightOutPokemonIsJoutaiDataId((FightOutPokemon *) temp_r30_2, 9) == 1) && (temp_r29 >= 0xC)) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 2));
        return;
    }
    fightSeq_NextWazaSeq(6);
}
}

extern "C" {
void WS_KOROGARU(void) {
    FightWaza* keep;
    FightOutPokemon* attacker;
    FightWaza* waza;
    u16 useWaza;
    s32 maxCount;
    s16 count;
    u16 power;
    u16 n;




    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    keep = fightOutPokemon_GetKeepFightWazaPtr(attacker);
    useWaza = fightOutPokemon_GetUseWazaDataId(attacker);
    if (fightWazaIsHit(waza) == 0) {
        fightOutPokemonInitJoutaiKeep(attacker);
        fightSeq_JumpWazaSeq(WAZA_NormalNohitWait);
        return;
    }
    if (fightOutPokemonCheckWriteJoutaiDataId(attacker, 0x2f) == 2) {
        fightOutPokemonWriteJoutaiDataId(attacker, 0x2f, 0);
        if (fightOutPokemonIsJoutaiDataId(attacker, 0x22) == 0) {
            fightOutPokemonWriteJoutaiDataId(attacker, 0x22, 0);
            fightWazaBiosCopy(keep, waza);
        }
    }
    count = 1;
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x2f) == 1) {
        maxCount = joutaiDataBiosGetMaxCount(0x2f);
        count = fightOutPokemonGetCountAsJoutaiDataId(attacker, 0x2f);
        if ((s16)count == maxCount) {
            fightOutPokemonInitJoutaiDataId(attacker, 0x2f);
            fightOutPokemonInitJoutaiDataId(attacker, 0x22);
        }
    }
    power = wazaDB_GetIryoku(useWaza);
    for (n = 1; n < (s16)count; n++) {
        power = power * 2;
    }
    fightWaza_SetIryoku(waza, power);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x1a) == 1) {
        power = fightWaza_GetIryoku(waza);
        fightWaza_SetIryoku(waza, power * 2);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_HOROBINOUTA(void) {
    s32 count;
    u8* seq;
    FightOutPokemon* attacker;
    u16 useWaza;
    FightOutPokemon* defender;

    count = 0;
    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    useWaza = fightOutPokemon_GetUseWazaDataId(attacker);
    defender = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightSeqRegulationCheck(useWaza, attacker, defender) == 1) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    fightFloorLoopValidFightOutPokemon(0, _fightSeqWsHorobinoutaSub, &count, 0);
    fightSeqPressurePpdecCheckHorobinouta(attacker);
    if (count == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    fightSeq_NextWazaSeq(5);
}
}

static s32 _fightSeqWsHorobinoutaSub(void* arg0, u16 id, void* arg) {
    FightOutPokemon* pokemon = (FightOutPokemon*)arg0;
    s32* count = (s32*)arg;
    u16 tokusei;
    if (fightOutPokemonCheckFightOut(pokemon) == 0) {
        return 1;
    }
    tokusei = fightOutPokemonGetTokuseiDataId(pokemon);
    if (fightOutPokemonCheckWriteJoutaiDataId(pokemon, 0x1e) != 2 || tokusei == 0x2b) {
        return 1;
    }
    fightOutPokemonWriteJoutaiDataId(pokemon, 0x1e, 0);
    (*count)++;
    return 1;
}

extern "C" {
void WS_MIYABURU(void) {
    FightOutPokemon *temp_r3;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x19) == 2) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x19, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_MAKIBISHI(void) {
    u8* seq;
    FightOutPokemon* attacker;
    FightSide* side;
    s32 count;

    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    side = (FightSide*)fightTargetGetPtrAsNowFightType(3, attacker);
    if (fightSideCheckWriteJoutaiDataId(side, 0x4a) == 2) {
        if (fightSideIsJoutaiDataId(side, 0x4a) == 1) {
            count = fightSideGetCountAsJoutaiDataId(side, 0x4a);
        } else {
            count = 0;
        }
        if ((s16)count != joutaiDataBiosGetMaxCount(0x4a)) {
            goto write;
        }
    }
    fightOutPokemon_SetNoPressureFlag(attacker, 1);
    fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
    return;
write:
    fightSideWriteJoutaiDataId(side, 0x4a, 0);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_NOROI(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    FightOutPokemon *temp_r3_2;
    FightWaza *temp_r28;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r28 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3_2, 0x18) != 2) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r3_2, 0x18, 0);
    fightWaza_SetDamage(temp_r28, (u32) fightOutPokemonMaxHpWaruValue(temp_r3, 2));
    fightSeq_NextWazaSeq(5);
}
}

extern "C" void WS_IYASHINOSUZU(void) {
    u16 waza;
    Hero* healHero;
    u32 i2;
    Hero* hero;
    FightOutPokemon* ally;
    u32 i, j2;
    FightPokemon* entry;
    Pokemon* pokemon;
    FIGHT_TRAINER* trainer;
    u32 j;
    FightOutPokemon* attacker;
    u32 trainerCount;
    FightSide* side;
    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetUseWazaDataId(attacker);
    ally = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0xe, attacker);
    side = (FightSide*)fightTargetGetPtrAsNowFightType(2, attacker);
    trainerCount = fightFloor_GetFightTypeTrainerNum(0);
    if ((u16)waza == 0xd7) {
        ServerWork.flags[5] = 0;
        if (fightOutPokemonGetTokuseiDataId(attacker) != 0x2b) {
            pokemonInitJoutai(fightOutPokemonGetPokemonPtr(attacker));
            fightOutPokemonResetSeqStatus(attacker, 0);
            fightOutPokemonInitJoutaiDataId(attacker, 0x17);
            fightSeqCheckSetHensinBuffToMotoPokemon(attacker, 0x7c);
        } else ServerWork.flags[5] |= 1;
        if (ally && fightOutPokemonCheckValid(ally) == 1) {
            fightFloor_SetAppointPokemonPtr(0, ally);
            if (fightOutPokemonGetTokuseiDataId(ally) != 0x2b) {
                pokemonInitJoutai(fightOutPokemonGetPokemonPtr(ally));
                fightOutPokemonResetSeqStatus(ally, 0);
                fightOutPokemonInitJoutaiDataId(ally, 0x17);
                fightSeqCheckSetHensinBuffToMotoPokemon(ally, 0x7c);
            } else ServerWork.flags[5] |= 2;
        }
        for (i = 0; i < trainerCount; ++i) {
            trainer = fightSideGetValidFightTrainerPtr(side, (u16)i);
            if (trainer) {
                healHero = fightTrainer_GetHeroPtr(trainer);
                for (j = 0; j < 6; ++j) {
                    entry = fightTrainerCheckTemotiPokemonFightEntry(trainer, heroGetStatus(healHero, 3, (u16)j));
                    if (entry && fightPokemonCheckValid(entry)) {
                        pokemon = fightPokemonGetPokemonPtr(entry);
                        if (pokemonGetTokuseiDataId(pokemon) != 0x2b) pokemonInitJoutai(pokemon);
                    }
                }
            }
        }
    } else {
        ServerWork.flags[5] = 4;
        pokemonInitJoutai(fightOutPokemonGetPokemonPtr(attacker));
        fightOutPokemonInitJoutaiDataId(attacker, 0x17);
        fightSeqCheckSetHensinBuffToMotoPokemon(attacker, 0x7c);
        if (ally && fightOutPokemonCheckValid(ally) == 1) {
            fightFloor_SetAppointPokemonPtr(0, ally);
            pokemonInitJoutai(fightOutPokemonGetPokemonPtr(ally));
            fightOutPokemonResetSeqStatus(ally, 0);
            fightOutPokemonInitJoutaiDataId(ally, 0x17);
            fightSeqCheckSetHensinBuffToMotoPokemon(ally, 0x7c);
        }
        for (i2 = 0; i2 < trainerCount; ++i2) {
            trainer = fightSideGetValidFightTrainerPtr(side, (u16)i2);
            if (trainer) {
                hero = fightTrainer_GetHeroPtr(trainer);
                for (j2 = 0; j2 < 6; ++j2) {
                    entry = fightTrainerCheckTemotiPokemonFightEntry(trainer, heroGetStatus(hero, 3, (u16)j2));
                    if (entry && fightPokemonCheckValid(entry))
                        pokemonInitJoutai(fightPokemonGetPokemonPtr(entry));
                }
            }
        }
    }
    fightSeq_NextWazaSeq(1);
}

extern "C" {
void WS_URAMI(void) {
    FightOutPokemon* target;
    Pokemon* pokemon;
    u16 lastWaza;
    u8 i;
    u8 pp;
    u8* seq;
    u8 dec;

    seq = fightSeq_GetWazaSeq();
    fightTargetGetPtrAsNowFightType(0x11, 0);
    target = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    pokemon = fightOutPokemonGetPokemonPtr(target);
    lastWaza = fightOutPokemon_GetLastSelectWazaDataId(target);
    if (lastWaza != 0 && lastWaza != 0x176 && lastWaza != 0xffff && wazaCheckDarkWaza(lastWaza) == 0) {
        pp = 0;
        for (i = 0; i < 4; i++) {
            if (pokemonWazaCheckValid(pokemon, i) != 0 && lastWaza == pokemon_GetPokemonWazaDataId(pokemon, i)) {
                pp = ((u8 (*)(void *, u16))pokemon_GetPokemonWazaPp)(pokemon, i);
                break;
            }
        }
        if (i >= 4) {
            fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
            return;
        }
        if (pp < 2) {
            fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
            return;
        }
        dec = HSD_Rand() % 4 + 2;
        if (pp < dec) {
            dec = pp;
        }
        fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(wazaDB_GetName(lastWaza)));
        fightMsgctrlSetValue(0x2f, dec);
        pp -= dec;
        ((void (*)(void *, u16, u8))pokemon_SetPokemonWazaPp)(pokemon, i, pp);
        fightSeqPpdecMonomane(target, i, 0);
        if (pp == 0) {
            fightOutPokemonInitJoutaiKeep(target);
        }
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
}
}

extern "C" {
void WS_JITABATA(void) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r31;
    u16 temp_r30;
    Pokemon *temp_r3_2;
    u8 power;
    u16 maxHp;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r31 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r3_2 = fightOutPokemonGetPokemonPtr(temp_r3);
    temp_r30 = pokemon_GetHp(temp_r3_2);
    maxHp = pokemon_GetMaxHp(temp_r3_2);
    power = fightSeqGetJitabataIryoku(temp_r30, maxHp);
    fightWaza_SetIryoku(temp_r31, power);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
u8 fightSeqGetJitabataIryoku(u16 hp, u16 maxHp) {
    u8 n;
    u8* p;
    s32 i;
    n = fightSeqGetNumDotto(hp, maxHp, 0x30);
    for (i = 0, p = JitabataTbl; i < 12; i += 2, p += 2) {
        if (n <= *p) {
            break;
        }
    }
    return JitabataTbl[i + 1];
}
}

static u8 fightSeqGetNumDotto(u16 arg0, u16 arg1, u8 arg2) {
    u8 r = (s32)(arg0 * arg2) / (s32)arg1;
    if (r == 0 && arg0 != 0) {
        return 1;
    }
    return r;
}

extern "C" {
void WS_MICHIDURE_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeqMichidureCheckAct();
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void fightSeqMichidureCheckAct(void) {
    FightOutPokemon *temp_r3;
    void *temp_r31;
    void *temp_r30;
    void *attacker;

    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightTargetGetPtrAsNowFightType(2, attacker);
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r31 = fightTargetGetPtrAsNowFightType(2, temp_r3);
    if ((fightOutPokemonIsJoutaiDataId(temp_r3, 0x15) == 1) && (temp_r30 != temp_r31) && !(ServerStatusFlag & 0x01000000)) {
        ServerStatusFlag |= 0x40;
    }
}
}

extern "C" {
void WS_MICHIDURE(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    u16 temp_r29;
    void *defender;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r29 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    defender = fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightSeqRegulationCheck(temp_r29, temp_r3, defender) == 1) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x15) == 2) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x15, 0);
    }
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_NEGOTO(void) {
    u8* seq;
    u8 fightType;
    FightOutPokemon* attacker;
    u8 count;
    s16 j;
    FightWaza* fightWaza;
    Pokemon* pokemon;
    s16 selected;
    s16 wazaIdx[4];
    u16 wazaId;
    u8 i;
    FightOutPokemon* defender;

    fightType = fightFloor_GetFightType(0);
    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    pokemon = fightOutPokemonGetPokemonPtr(attacker);
    fightWaza = fightOutPokemon_GetFightWazaPtr(attacker);
    for (i = 0; i < 4; i++) {
        wazaIdx[i] = -1;
    }
    count = 0;
    for (j = 0; j < 4; j++) {
        if (pokemonWazaCheckValid(pokemon, j) != 0) {
            u8 r = fightOutPokemonCheckCanOutOkWazaBanme(attacker, j, 0, 0);
            if (r == 0 || r == 6) {
                wazaId = pokemon_GetPokemonWazaDataId(pokemon, j);
                if (wazaId != 0 && wazaId != 0x176 && wazaId != 0x163 && fightSeqRendouWazaCheck(wazaId) == 0 && wazaId != 0x108 && wazaId != 0xfd && fightSeqTameWazaCheck(wazaId) == 0) {
                    wazaIdx[count] = j;
                    count++;
                }
            }
        }
    }
    if (count == 0) {
fail:
        fightSeq_NextWazaSeq(5);
        return;
    }
    selected = wazaIdx[(u8)(HSD_Rand() % count)];
    if (selected >= 0) {
        wazaId = pokemon_GetPokemonWazaDataId(pokemon, selected);
        if (wazaId != 0 && wazaId != 0x176 && wazaId != 0x163) {
            PushWazaNo = wazaId;
            fightWaza_SetWazaBanme(fightWaza, selected);
            ServerStatusFlag &= 0xfffffbff;
            defender = fightSeqSelectDefensePokemonPtr(attacker, PushWazaNo, fightType, 0, 1, 1, -1);
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, defender);
            fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
            return;
        }
    }
    goto fail;
}
}

extern "C" {
s32 fightSeqTameWazaTurnCheck(u16 unused, u16 wazaId) {
    u16 seq = wazaDB_GetSeqId(wazaId);
    if (seq == 0x97 && (u8) fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 2;
    }
    if (seq == 0x91 || seq == 0x27 || seq == 0x4b || seq == 0x97 || seq == 0x9b || seq == 0x1a) {
        return (ServerStatusFlag & 0x8000000) ? 1 : 2;
    }
    return 2;
}
}

extern "C" {
u8 fightSeqRendouWazaCheck(u16 wazaId) {
    if (wazaId == 0 || wazaId == 0x176 || wazaId == 0xd6 || wazaId == 0x112 || wazaId == 0x77 || wazaId == 0x76) {
        return 1;
    }
    return 0;
}
}

extern "C" {
u8 fightSeqTameWazaCheck(u16 wazaId) {
    u16 seq = wazaDB_GetSeqId(wazaId);
    if (seq == 0x91 || seq == 0x27 || seq == 0x4b || seq == 0x97 || seq == 0x9b || seq == 0x1a) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void WS_SKETCH(void) {
    s32 banme;
    u8* seq;
    FightOutPokemon* attacker;
    FightWaza* waza;
    u32 motoFight;
    u32 curFight;
    Pokemon* motoPokemon;
    Pokemon* curPokemon;
    u16 sketchId;
    s32 slot;

    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    sketchId = fightOutPokemon_GetSketchWazaDataId(fightTargetGetPtrAsNowFightType(0x12, 0));
    fightWaza_SetMotoWazaDataId(waza, 0xffff);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x10) == 1 || fightSeqIsSketchNgWazaDataId(sketchId) == 1) {
jump:
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    motoFight = (u32)fightOutPokemon_GetMotoFightPokemonPtr(attacker);
    curFight = (u32)fightOutPokemon_GetFightPokemonPtr(attacker);
    motoPokemon = fightPokemonGetPokemonPtr((void*)motoFight);
    curPokemon = fightPokemonGetPokemonPtr((void*)curFight);
    if (pokemonSearchWazaDataId(motoPokemon, sketchId) >= 0) {
        goto jump;
    }
    banme = fightWaza_GetWazaBanme(waza);
    if ((s8)banme < 0) {
        goto jump;
    }
    slot = (s8)banme;
    pokemonWazaCreate(motoPokemon, slot, sketchId);
    if (fightOutPokemonIsUseHensinBuff(attacker) == 1) {
        pokemonWazaCreate(curPokemon, slot, sketchId);
    }
    fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(wazaDB_GetName(sketchId)));
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
u8 fightSeqIsSketchNgWazaDataId(u16 wazaId) {
    if (wazaId == 0xa5 || wazaCheckDarkWaza(wazaId) == 1 || wazaId == 0xa6 || wazaId == 0xffff || wazaId == 0 || wazaId == 0x176) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void WS_LOCKON(void) {
    FightOutPokemon *temp_r31;
    FightOutPokemon *temp_r3;
    u32 temp_r30;

    fightSeq_GetWazaSeq();
    temp_r31 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(temp_r31, fightFloor_GetFightType(0));
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x1D) == 2) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x1D, temp_r30);
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_TEXTURE2(void) {
    s32 buf[0x14];
    u8* seq;
    FightOutPokemon* attacker;
    u8 fightType;
    u16 hitWaza;
    u32 hitZokusei;
    u32 relative;
    u16 count;
    s32 value;
    u16 z;
    u16 i;




    fightType = fightFloor_GetFightType(0);
    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemon_GetFightWazaPtr(attacker);
    hitWaza = fightOutPokemon_GetHitWazaDataId(attacker);
    fightOutPokemon_GetDamageAtkValue(attacker);
    fightOutPokemon_GetDamageSpeValue(attacker);
    hitZokusei = ((u32 (*)(void*))fightOutPokemon_GetHitWazaZokuseiDataId)(attacker);
    relative = (u32)fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(fightOutPokemon_GetLastReceiveWazaTargetDataId(attacker), fightType);
    if (hitWaza == 0 || hitWaza == 0x176 || hitWaza == 0xffff || wazaCheckDarkWaza(hitWaza) == 1) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    if (relative != 0 && fightSeqTameWazaCheck(hitWaza) != 0 && fightOutPokemonIsJoutaiDataId((void*)relative, 0x22) == 1) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    count = fightOutPokemonGetTeikouZokuseiDataIdAry(attacker, hitZokusei, buf);
    if (count == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    value = buf[(u16)(HSD_Rand() % count)];
    if (value < 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    z = value;
    for (i = 0; i < 2; i++) {
        fightOutPokemonSetZokuseiDataId(attacker, (u8)i, z);
    }
    fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(zokuseiBiosGetName(z)));
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_ITAMIWAKE(void) {
    s32 temp_r4;
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    FightOutPokemon *temp_r3_2;
    FightWaza *temp_r29;
    u16 temp_r28;
    u16 temp_r27;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r29 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r28 = WIDE_GET_HP(fightOutPokemonGetPokemonPtr(temp_r3));
    temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r27 = WIDE_GET_HP(fightOutPokemonGetPokemonPtr(temp_r3_2));
    if (fightOutPokemonIsJoutaiDataId(temp_r3_2, 0x14) == 0) {
        temp_r4 = (s32) (temp_r28 + temp_r27) / 2;
        WazaDamage = temp_r27 - temp_r4;
        fightWaza_SetDamage(temp_r29, temp_r28 - temp_r4);
        fightOutPokemon_SetKaigaraDamageValue(temp_r3_2, 0xFFFF);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
}
}

extern "C" {
void WS_ENCORE(void) {
    u8 *temp_r31;
    FightOutPokemon *temp_r3;
    Pokemon *temp_r29;
    u16 temp_r3_2;
    s8 var_r27;
    u32 var_r26;
    u32 var_r3;
    u16 encoreId;


    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r29 = fightOutPokemonGetPokemonPtr(temp_r3);
    temp_r3_2 = fightOutPokemon_GetLastSelectWazaDataId(temp_r3);
    var_r27 = pokemonSearchWazaDataId(temp_r29, temp_r3_2);
    if (var_r27 < 0) {
        var_r3 = 0;
    } else {
        var_r3 = pokemon_GetPokemonWazaPp(temp_r29, (u16) var_r27);
    }
    var_r26 = var_r3;
    if (fightSeqIsEncoreNgWazaDataId(temp_r3_2) == 1) {
        var_r26 = 0;
        var_r27 = -1;
    }
    if ((fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x2A) == 2) && (var_r27 >= 0) && ((u8) var_r26 != 0)) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x2A, 0);
        encoreId = pokemon_GetPokemonWazaDataId(temp_r29, var_r27);
        fightOutPokemonSetIdBuffJoutaiDataId(temp_r3, 0x2A, encoreId);
        fightOutPokemonSetBuffJoutaiDataId(temp_r3, 0x2A, (u32) var_r27);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
}
}

extern "C" {
u8 fightSeqIsEncoreNgWazaDataId(u16 wazaId) {
    if (wazaId == 0xa5 || wazaId == 0xe3 || wazaId == 0x77 || wazaId == 0xffff) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void WS_KANASHIBARI(void) {
    FightOutPokemon *temp_r3;
    u32 var_r31;
    s8 temp_r3_2;
    u8 *temp_r29;
    Pokemon *temp_r27;
    u16 lastWaza;
    u16 temp_r3_3;


    temp_r29 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r27 = fightOutPokemonGetPokemonPtr(temp_r3);
    lastWaza = fightOutPokemon_GetLastSelectWazaDataId(temp_r3);
    temp_r3_2 = pokemonSearchWazaDataId(temp_r27, lastWaza);
    if (temp_r3_2 < 0) {
        var_r31 = 0;
    } else {
        var_r31 = pokemon_GetPokemonWazaPp(temp_r27, (u16) temp_r3_2);
    }
    if ((fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x29) == 2) && (temp_r3_2 >= 0) && ((u8) var_r31 != 0)) {
        temp_r3_3 = pokemon_GetPokemonWazaDataId(temp_r27, temp_r3_2);
        fightMsgctrlSetValue(0xD, (u32)GSmsgGetGSchar(wazaDB_GetName(temp_r3_3)));
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x29, 0);
        fightOutPokemonSetIdBuffJoutaiDataId(temp_r3, 0x29, temp_r3_3);
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r29 + 1));
}
}

extern "C" {
void WS_MIRRORCOAT(void) {
    _fightSeqDamageHanekaesi(0x105, 0x104, 5, *(u32*)(fightSeq_GetWazaSeq() + 1));
}
}

extern "C" {
void WS_COUNTER(void) {
    _fightSeqDamageHanekaesi(0x103, 0x102, 5, *(u32*)(fightSeq_GetWazaSeq() + 1));
}
}

static void _fightSeqDamageHanekaesi(u16 status1, u16 status2, u8 nextArg, u32 jump) {
    FightOutPokemon* attacker;
    FightOutPokemon* target;
    FightWaza* waza;
    s16 value2;
    u16 value1;
    u8 fightType;

    fightType = fightFloor_GetFightType(0);
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    value1 = pokemonGetStatus(attacker, 0, status1, 0);
    value2 = pokemonGetStatus(attacker, 0, status2, 0);
    if (value1 != 0 && value2 != 0) {
        target = fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(value1, fightType);
        if (target != 0 && fightOutPokemonIsAlly(attacker, target) == 0 && fightOutPokemonCheckFightOut(target) == 1) {
            FightOutPokemon* enemy;
            fightWaza_SetDamage(waza, value2 * 2);
            enemy = fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(attacker);
            if (enemy != 0) {
                target = enemy;
            }
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, target);
            fightSeq_NextWazaSeq(nextArg);
            return;
        }
    }
    fightOutPokemon_SetNoPressureFlag(attacker, 1);
    fightSeq_JumpWazaSeq((u8*)jump);
}

extern "C" {
void WS_PSYCHOWAVE(void) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r31;
    u8 temp_r30;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r31 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r30 = WIDE_GET_LEVEL(temp_r3);
    fightWaza_SetDamage(temp_r31, (u32) ((s32) (temp_r30 * (((HSD_Rand() % 11) * 0xA) + 0x32)) / 100));
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_CHIKYUUNAGE(void) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r31;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r31 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    fightWaza_SetDamage(temp_r31, (u32) figthOutPokemonGetLevel(temp_r3));
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_YUBIWOHURU(void) {
    u16 buf[400];
    u8 fightType;
    FightOutPokemon* attacker;
    FightWaza* waza;
    u32 id;
    u16 rnd;
    u16 dbg;
    u16 sel;
    u32 count;
    s32 i;
    FightOutPokemon* defender;

    fightType = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    for (i = 0; i < 400; i++) {
        buf[i] = 0;
    }
    count = 0;
    id = 0;
    do {
        if (id != 0 && fightSeqCheckYubiwohuruWazaDataId(id) != 0) {
            buf[count] = id;
            count++;
        }
        id++;
    } while (id < 0x163);
    rnd = HSD_Rand();
    sel = buf[rnd % count];
    dbg = dbgMenuFightGetYubiwohuruWazaDataId();
    if (dbg != 0) {
        sel = dbg;
    }
    ServerStatusFlag &= 0xfffffbff;
    fightWazaSetUseWazaStatus(waza, sel);
    defender = fightSeqSelectDefensePokemonPtr(attacker, sel, fightType, 0, 1, 1, -1);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, defender);
    fightSeq_JumpWazaSeq(WazaEffectTbl[(u16)wazaDB_GetSeqId(sel)]);
}
}

extern "C" {
u8 fightSeqCheckYubiwohuruWazaDataId(u16 wazaId) {
    s32 i;
    u16 t;
    if (wazaId == 0) {
        return 0;
    }
    if (wazaId == 0x176) {
        return 0;
    }
    if (wazaId == 0x163) {
        return 0;
    }
    i = 0;
    for (;;) {
        t = YubihuriNGTbl[i];
        if (t == 0xffff) {
            break;
        }
        if (wazaId == t) {
            break;
        }
        i++;
    }
    if (t != 0xffff) {
        return 0;
    }
    return 1;
}
}

extern "C" {
void WS_MONOMANE(void) {
    s8 slot;
    Pokemon* pokemon;
    u32 pp;
    u32 buff;
    FightWaza* waza;
    u8* seq;
    s32 banme;
    FightOutPokemon* attacker;
    u16 lastWaza;





    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    lastWaza = fightOutPokemon_GetLastSelectWazaDataId(fightTargetGetPtrAsNowFightType(0x12, 0));
    fightWaza_SetMotoWazaDataId(waza, 0xffff);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x10) == 1 || fightSeqMonomaneNGCheck(lastWaza) != 0 || lastWaza == 0 || lastWaza == 0xffff || lastWaza == 0x176 || lastWaza == 0x163) {
jump:
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    if (pokemonSearchWazaDataId(fightOutPokemonGetPokemonPtr(attacker), lastWaza) >= 0) {
        goto jump;
    }
    banme = fightWaza_GetWazaBanme(waza);
    if ((s8)banme < 0) {
        goto jump;
    }
    if (fightOutPokemonIsUseHensinBuff(attacker) == 0 && fightOutPokemonUseHensinBuff(attacker) == 0) {
        goto jump;
    }
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x31) == 0) {
        fightOutPokemonWriteJoutaiDataId(attacker, 0x31, 0);
    }
    pokemon = fightOutPokemonGetPokemonPtr(attacker);
    slot = (s8)banme;
    pokemonWazaCreate(pokemon, slot, lastWaza);
    pp = wazaDB_GetPp(lastWaza);
    if ((u8)pp > 5) {
        pp = 5;
    }
    pokemon_SetPokemonWazaPp(pokemon, slot, pp);
    fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(wazaDB_GetName(lastWaza)));
    buff = fightOutPokemonGetBuffJoutaiDataId(attacker, 0x31);
    buff |= 1 << (s8)banme;
    fightOutPokemonSetBuffJoutaiDataId(attacker, 0x31, buff);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
u8 fightSeqMonomaneNGCheck(u16 wazaId) {
    s32 i;
    u16 t;
    if (wazaId == 0) {
        return 1;
    }
    if (wazaId == 0x176) {
        return 1;
    }
    if (wazaId == 0x163) {
        return 1;
    }
    for (i = 0; (t = YubihuriNGTbl[i]) != 0xfffe; i++) {
        if (wazaId == t) {
            break;
        }
    }
    return t != 0xfffe;
}
}

extern "C" {
void WS_MIGAWARI(void) {
    u16 temp_r31;
    FightOutPokemon *temp_r30;
    FightWaza *temp_r29;
    s32 temp_r3;

    fightSeq_GetWazaSeq();
    temp_r30 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r31 = pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r30));
    temp_r29 = fightOutPokemon_GetFightWazaPtr(temp_r30);
    temp_r3 = fightOutPokemonMaxHpWaruValue(temp_r30, 4);
    if ((s32) temp_r31 <= temp_r3) {
block_1:
        fightWaza_SetDamage(temp_r29, 0U);
        ServerWork.flags[5] = 1;
    } else {
        if (fightOutPokemonCheckWriteJoutaiDataId(temp_r30, 0x14) != 2) {
            goto block_1;
        }
        fightWaza_SetDamage(temp_r29, temp_r3);
        fightOutPokemonWriteJoutaiDataId(temp_r30, 0x14, 0);
        fightOutPokemonSetBuffJoutaiDataId(temp_r30, 0x14, temp_r3);
        if (fightOutPokemonIsJoutaiDataId(temp_r30, 0xE) == 1) {
            fightOutPokemonInitJoutaiDataId(temp_r30, 0xE);
        }
        ServerWork.flags[5] = 0;
        ServerStatusFlag |= 0x100;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" void WS_HENSHIN(void) {
    FightOutPokemon* attacker;
    FightOutPokemon* defender;
    u32 trainerRnd;
    FightWaza* waza;
    u32 pokemonRnd;
    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    defender = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    pokemonRnd = pokemon_GetRnd(fightOutPokemonGetPokemonPtr(defender));
    trainerRnd = pokemon_GetCatchTrainerRnd(fightOutPokemonGetPokemonPtr(defender));
    fightWaza_SetMotoWazaDataId(waza, 0xffff);
    if (fightOutPokemonIsJoutaiDataId(defender, 0x10) == 1 ||
        (u16)fightOutPokemonIsJoutaiKie(defender) != 0 ||
        pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(defender)) == 1) {
    failure:
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x45);
        ServerWork.flags[5] = 1;
        fightSeq_NextWazaSeq(1);
        return;
    }
    if (!fightOutPokemonIsUseHensinBuff(attacker) && !fightOutPokemonUseHensinBuff(attacker)) goto failure;
    if (!fightOutPokemonIsJoutaiDataId(attacker, 0x10))
        fightOutPokemonWriteJoutaiDataId(attacker, 0x10, 0);
    fightOutPokemonSetBuffJoutaiDataId(attacker, 0x10, pokemonRnd);
    fightOutPokemonSetKaisuuJoutaiDataId(attacker, 0x10, (s8)(u8)trainerRnd);
    fightOutPokemonSetNowKaisuuJoutaiDataId(attacker, 0x10, (s8)(u8)(trainerRnd >> 8));
    fightOutPokemonSetIdBuffJoutaiDataId(attacker, 0x10, trainerRnd >> 16);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x29) == 1)
        fightOutPokemonInitJoutaiDataId(attacker, 0x29);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x31) == 1)
        fightOutPokemonInitJoutaiDataId(attacker, 0x31);
    fightMsgctrlSetValue(0xd, (u32)fightOutPokemonGetNamePtr(defender));
    ServerWork.flags[5] = 0;
    fightOutPokemonCopyHensinStatus(defender, attacker);
    u32* cursor = fightOutPokemon_GetWazaMenuCurPtr(attacker);
    if (cursor) *cursor = 0;
    fightSeq_NextWazaSeq(1);
}

extern "C" {
void WS_KIAIDAME(void) {
    FightOutPokemon *temp_r3;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0xF) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x45);
        ServerWork.flags[5] = 1;
    } else {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0xF, 0);
        ServerWork.flags[5] = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_SHIROIKIRI(void) {
    FightSide *temp_r3;
    void *attacker;

    fightSeq_GetWazaSeq();
    attacker = fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r3 = (FightSide*)fightTargetGetPtrAsNowFightType(2, attacker);
    if (fightSideCheckWriteJoutaiDataId(temp_r3, 0x4C) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x45);
        ServerWork.flags[5] = 1;
    } else {
        fightSideWriteJoutaiDataId(temp_r3, 0x4C, 0);
        ServerWork.flags[5] = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_CONDITION_GAUGE(void) {
    FightOutPokemon *temp_r3;
    u8 temp_r31;

    temp_r31 = fightFloor_GetFightType(0);
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    if (temp_r3 != 0) {
        fightMenuFightOutPokemonRenewStatusMenu(temp_r3, temp_r31, 1);
    }
    fightSeq_NextWazaSeq(2);
}
}

extern "C" {
void WS_MEROMERO(void) {
    FightOutPokemon *temp_r3;
    u8 temp_r31;
    u8 temp_r30;
    FightOutPokemon *temp_r3_2;
    u8 *temp_r29;
    u32 temp_r27;

    temp_r29 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightOutPokemonGetSex(temp_r3);
    temp_r27 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(temp_r3, fightFloor_GetFightType(0));
    temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r31 = fightOutPokemonGetSex(temp_r3_2);
    if (fightOutPokemonGetTokuseiDataId(temp_r3_2) == 0xC) {
        fightSeq_JumpWazaSeq(WAZA_Donkan);
        return;
    }
    if ((temp_r30 == temp_r31) || (fightOutPokemonCheckWriteJoutaiDataId(temp_r3_2, 0xA) != 2) || (temp_r30 == 2) || (temp_r31 == 2)) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r29 + 1));
        return;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r3_2, 0xA, temp_r27);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_WEATHER_KEEP(void) {
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    FightWaza *temp_r29;
    u32 var_r28;
    u8 temp_r27;
    Pokemon *temp_r26;

    var_r28 = 0;
    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r29 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r31 = fightOutPokemonGetTokuseiDataId(temp_r3);
    temp_r26 = fightOutPokemonGetPokemonPtr(temp_r3);
    temp_r27 = fightFloorGetNowTenkouDataId(0, 1);
    if (fightOutPokemonCheckFightOut(temp_r3) == 0) {
        var_r28 = 0;
    } else {
        if (temp_r27 == 3) {
            if ((fightOutPokemonIsZokuseiDataId(temp_r3, 5) == 0) && (fightOutPokemonIsZokuseiDataId(temp_r3, 8) == 0) && (fightOutPokemonIsZokuseiDataId(temp_r3, 4) == 0) && (temp_r31 != 8) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x20) == 0) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x21) == 0)) {
                var_r28 = fightOutPokemonMaxHpWaruValue(temp_r3, 0x10);
            } else {
                var_r28 = 0;
            }
        }
        if (temp_r27 == 4) {
            if ((fightOutPokemonIsZokuseiDataId(temp_r3, 0xF) == 0) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x20) == 0) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x21) == 0)) {
                var_r28 = fightOutPokemonMaxHpWaruValue(temp_r3, 0x10);
            } else {
                var_r28 = 0;
            }
        }
        if (temp_r27 == 5) {
            if ((pokemonIsDarkPokemon(temp_r26) == 0) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x20) == 0) && (fightOutPokemonIsJoutaiDataId(temp_r3, 0x21) == 0)) {
                var_r28 = fightOutPokemonMaxHpWaruValue(temp_r3, 0x10);
            } else {
                var_r28 = 0;
            }
        }
    }
    fightWaza_SetDamage(temp_r29, (u32) var_r28);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_WEATHER_CHANGE(void) {
    u8 *temp_r3;

    temp_r3 = fightSeq_GetWazaSeq();
    if (fightFloorCheckWriteJoutaiDataId(0, *(u8*)(temp_r3 + 1)) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork.flags[5] = 2;
    } else {
        fightFloorWriteJoutaiDataId(0, *(u8*)(temp_r3 + 1), 0);
        ServerWork.flags[5] = *(u8*)(temp_r3 + 2);
    }
    fightSeq_NextWazaSeq(3);
}
}

extern "C" {
void WS_HPHALF(void) {
    u16 var_r4;
    FightOutPokemon *temp_r3;
    u32 temp_r31;
    u16 temp_r30;
    FightOutPokemon *temp_r3_2;
    FightWaza *temp_r28;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightOutPokemon_GetUseWazaDataId(temp_r3);
    temp_r28 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r3_2 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r31 = fightOutPokemonNowHpWaruValue(temp_r3_2, 1);
    var_r4 = (u16)fightOutPokemonNowHpWaruValue(temp_r3_2, 2);
    if ((temp_r30 == 0x175) && ((s32) (u16) temp_r31 == (s32) var_r4)) {
        var_r4 = 0;
    }
    ((void (*)(void*, u16))fightWaza_SetDamage)(temp_r28, var_r4);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_ICHIGEKI(void) {
    FightOutPokemon *temp_r3;
    u8 temp_r31;
    u16 temp_r30;
    u8 temp_r29;
    u32 temp_r28;
    u8 *temp_r27;
    u16 temp_r25;
    u16 temp_r24;
    FightWaza *temp_r23;
    u16 temp_r22;
    u32 temp_r21;
    FightOutPokemon *temp_r20;
    u32 temp_r20_2;
    u16 temp_r20_3;
    u16 var_r0;

    temp_r27 = fightSeq_GetWazaSeq();
    temp_r20 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r28 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(temp_r20, fightFloor_GetFightType(0));
    temp_r25 = fightOutPokemon_GetUseWazaDataId(temp_r20);
    temp_r23 = fightOutPokemon_GetFightWazaPtr(temp_r20);
    temp_r29 = figthOutPokemonGetLevel(temp_r20);
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r24 = fightOutPokemonGetSoubiItemDataId(temp_r3);
    temp_r20_2 = fightOutPokemonGetSoubiItemSoubiDataId(temp_r3);
    temp_r21 = figthOutPokemonGetSoubiItemBuff(temp_r3);
    temp_r30 = pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r3));
    temp_r22 = fightOutPokemonGetTokuseiDataId(temp_r3);
    temp_r31 = figthOutPokemonGetLevel(temp_r3);
    fightFloor_SetItemPokemonPtr(0, temp_r3);
    if (((u16) temp_r20_2 == 0x27) && ((s32) (HSD_Rand() % 100) < (s32) temp_r21)) {
        fightOutPokemon_SetItemKoraetaFlag(temp_r3, 1);
    }
    if (temp_r22 == 5) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        fightSeq_JumpWazaSeq(WAZA_Ganzyou);
        return;
    }
    if ((fightOutPokemonIsJoutaiDataId(temp_r3, 0x1D) == 1) && ((u16) temp_r28 == fightOutPokemonGetUserFightTargetIdJoutaiDataId(temp_r3, 0x1D))) {
        if (temp_r29 >= temp_r31) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
    } else {
        temp_r20_3 = (temp_r29 - temp_r31) + wazaDB_GetAvg(temp_r25);
        if (((s32) ((HSD_Rand() % 100) + 1) < (s32) temp_r20_3) && (temp_r29 >= temp_r31)) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
    }
    if (var_r0 != 0) {
        if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x2C) != 0) {
            fightWaza_SetDamage(temp_r23, temp_r30 - 1);
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x46);
        } else if (fightOutPokemon_GetItemKoraetaFlag(temp_r3) != 0) {
            fightWaza_SetDamage(temp_r23, temp_r30 - 1);
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x47);
            fightFloor_SetAppointItemDataId(0, temp_r24);
        } else {
            fightWaza_SetDamage(temp_r23, (u32) temp_r30);
            fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x44);
        }
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
    if (temp_r29 >= temp_r31) {
        ServerWork.flags[5] = 0;
    } else {
        ServerWork.flags[5] = 1;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r27 + 1));
}
}

extern "C" {
void WS_HIKARINOKABE(void) {
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    FightSide *temp_r30;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = (FightSide*)fightTargetGetPtrAsNowFightType(2, temp_r3);
    temp_r31 = fightFloorGetValidFightOutPokemonCount(0, 1, temp_r3, 1);
    if (fightSideCheckWriteJoutaiDataId(temp_r30, 0x49) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork.flags[5] = 0;
    } else {
        fightSideWriteJoutaiDataId(temp_r30, 0x49, 0);
        if ((fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2) && (temp_r31 >= 2)) {
            ServerWork.flags[5] = 4;
        } else {
            ServerWork.flags[5] = 3;
        }
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KOBAN_CHECK(void) {
    s32 temp_r31;
    u32 temp_r3_2;
    Hero *temp_r3_3;
    FIGHT_TRAINER *temp_r3;

    fightSeq_GetWazaSeq();
    if (fightFloor_GetFightKindGetNekoniKobanFlag(0) == 1) {
        temp_r3 = fightFloorGetGcHeroFightTrainerPtr(0);
        if (temp_r3 != 0) {
            temp_r3_2 = fightTrainer_GetKoban(temp_r3);
            if (temp_r3_2 != 0) {
                temp_r31 = temp_r3_2 * (u8)fightTrainer_GetOkaneBai(temp_r3);
                temp_r3_3 = fightTrainer_GetHeroPtr(temp_r3);
                if (temp_r3_3 != 0) {
                    heroAddPokedoru((u32) temp_r3_3, temp_r31);
                    fightMsgctrlSetValue(0x2F, (u32) temp_r31);
                    fightMsgctrlSetValue(0x13, heroGetStatus(temp_r3_3, 1, 0));
                    fightSeq_CallWazaSeq(WAZA_Nekonikoban);
                }
            }
        }
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_TEXTURE(void) {
    u8* seq;
    u16 rnd;
    u16 z;
    u8 count;
    s32 zokusei;
    u8 idx;
    s32 buf[4];
    FightOutPokemon* attacker;
    u8 i;

    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    count = fightSeqGetTextureZokuseiAry(attacker, buf);
    if (count == 0) {
jump:
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    rnd = HSD_Rand();
    zokusei = buf[(u8)(rnd % count)];
    if (zokusei < 0) {
        goto jump;
    }
    z = (u16)zokusei;
    for (i = 0; i < 2; i++) {
        fightOutPokemonSetZokuseiDataId(attacker, i, z);
    }
    fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(zokuseiBiosGetName(z)));
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
u8 fightSeqGetTextureZokuseiAry(void* pokemon, s32* out) {
    u8 j;
    u16 wazaId;
    u8 count;
    Pokemon* pokemonPtr;
    u16 zokusei;
    u8 i;

    pokemonPtr = fightOutPokemonGetPokemonPtr(pokemon);
    for (i = 0; i < 4; i++) {
        out[i] = -1;
    }
    count = 0;
    for (j = 0; j < 4; j++) {
        if (pokemonWazaCheckValid(pokemonPtr, j) == 1) {
            wazaId = pokemon_GetPokemonWazaDataId(pokemonPtr, j);
            if (wazaId != 0xa5 && wazaCheckDarkWaza(wazaId) != 1) {
                zokusei = wazaDB_GetZokuseiDataId(wazaId);
                if (zokusei == 9) {
                    if (fightOutPokemonIsZokuseiDataId(pokemon, 7) == 1) {
                        zokusei = 7;
                    } else {
                        zokusei = 0;
                    }
                }
                if (fightOutPokemonIsZokuseiDataId(pokemon, zokusei) == 0) {
                    out[count] = (u16)zokusei;
                    count++;
                }
            }
        }
    }
    return count;
}
}

extern "C" {
void WS_HUKITOBASHI(void) {
    void* buf[6];
    u16 count;
    u8* seq;
    FightOutPokemon* attacker;
    FightOutPokemon* defender;
    s16 entryId;
    void* encount;
    void* fightPokemon;




    encount = fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0));
    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    defender = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    count = fightTrainerGetIrekaeFightPokemonAry(fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, defender), buf);
    if (fightEncountDataBiosGetFightKind(encount) == 0xc) {
        fightFloorSetFightResultId(0, 2);
        fightSeq_JumpWazaSeq(WAZA_HukitobashiFightEnd);
        return;
    }
    if (count == 0) {
jump:
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    if (_fightSeqHukitobashiCheck(attacker, defender, *(u32*)(seq + 1)) != 0) {
        fightPokemon = buf[(u16)(HSD_Rand() % count)];
        if (fightPokemon == 0) {
            goto jump;
        }
        entryId = fightPokemon_GetEntryId(fightPokemon);
        if (entryId < 0) {
            goto jump;
        }
        fightFloor_SetIrekaePokemonPtr(0, defender);
        fightOutPokemon_SetIrekaeTargetEntryId(defender, entryId);
        fightOutPokemon_SetIrekaetaFlag(defender, 1);
    }
}
}

static u8 _fightSeqHukitobashiCheck(FightOutPokemon* attacker, FightOutPokemon* defender, u32 jump) {
    u32 atkLevel;
    u32 defLevel;
    u32 r;
    s32 sum;
    atkLevel = WIDE_GET_LEVEL(attacker);
    defLevel = WIDE_GET_LEVEL(defender);
    if ((u8)atkLevel >= (u8)defLevel) {
fail:
        fightSeq_JumpWazaSeq(WAZA_Hukitobashi);
        return 1;
    }
    r = HSD_Rand();
    sum = (u8)atkLevel + (u8)defLevel;
    if ((u16)(((sum * (u8)r) >> 8) + 1) > (s32)((defLevel >> 2) & 0x3f)) {
        goto fail;
    }
    fightSeq_JumpWazaSeq((u8*)jump);
    return 0;
}

extern "C" {
void WS_RENZOKU_NUM_INIT(void) {
    fightSeq_GetWazaSeq();
    fight_seq_renzoku_count = 0;
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
#pragma opt_lifetimes off
void WS_RENZOKU(void) {
    u8 count;
    FightWaza *waza;

    waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    count = fightSeq_GetWazaSeq()[1];
    if (count != 0) {
        fightWaza_SetKaisuu(waza, count);
    } else {
        count = HSD_Rand() % 4;
        if (count < 2) {
            count = count + 2;
        } else {
            count = HSD_Rand() % 4 + 2;
        }
        fightWaza_SetKaisuu(waza, count);
    }
    fightSeq_NextWazaSeq(2);
}
#pragma opt_lifetimes reset
}

extern "C" {
void WS_ABARERU(void) {
    fightSeq_GetWazaSeq();
    if (fightOutPokemonCheckWriteJoutaiDataId(fightTargetGetPtrAsNowFightType(0x11, 0), 0xD) == 2) {
        ServerWork.flags[3] = 0x75;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_GAMAN(void) {
    FightOutPokemon *temp_r3;
    FightWaza *temp_r30;
    FightWaza *temp_r29;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r29 = fightOutPokemon_GetKeepFightWazaPtr(temp_r3);
    if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0xC) == 2) {
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0xC, 0);
        fightOutPokemonWriteJoutaiDataId(temp_r3, 0x22, 0);
    }
    fightWazaBiosCopy(temp_r29, temp_r30);
    fightOutPokemon_SetGamanDamageValue(temp_r3, 0);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_KUROIKIRI(void) {
    fightSeq_GetWazaSeq();
    fightFloorLoopValidFightOutPokemon(0, _fightSeqWsKuroikiriSub, 0, 0);
    fightSeq_NextWazaSeq(1);
}
}

static s32 _fightSeqWsKuroikiriSub(void* pokemon, u16, void*) {
    if (fightOutPokemonCheckFightOut(pokemon) == 0) {
        return 0;
    }
    fightOutPokemonInitAbiCntAll(pokemon);
    return 1;
}

extern "C" {
void WS_CONDCHG(void) {
    u8* seq;
    u8 v;
    seq = fightSeq_GetWazaSeq();
    v = UserWork[0x1601e];
    if (fightSeqCondChgAct(v & 0xf0, v & 0xf, seq[1], *(u8**)(seq + 2)) == 0) {
        fightSeq_NextWazaSeq(6);
    }
}
}

extern "C" u8 fightSeqCondChgAct(u8 para, u8 type, u8 flags, u8* failure) {
    u16 ability;
    FightOutPokemon* target;
    FightSide* side;
    s8 delta;
    u16 status;
    u16 waza;
    u8 bypass;
    struct { u8 value; } modeState;
    u8 skipGuard;
    s8 value;
    u8 targetKind;
    bypass = 0;
    skipGuard = 0;
    if (flags & 0x40) {
        target = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
        targetKind = 0;
    } else {
        target = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
        targetKind = 1;
    }
    side = (FightSide*)fightTargetGetPtrAsNowFightType(2, target);
    ability = fightOutPokemonGetTokuseiDataId(target);
    waza = fightOutPokemon_GetUseWazaDataId(target);
    modeState.value = (u8)flags;
    flags = (u8)modeState.value & 0xbf;
    if (flags & 0x80) bypass = 1;
    if (modeState.value & 0x20) skipGuard = 1;
    status = fightSeqCondChgActTypeToPokemonStatusId(type);
    value = (s8)pokemonGetStatus(target, 0, status, 0);
    fightMsgctrlSetValue(0xd, (u32)GSmsgGetGSchar(AbiCntMsgTbl[type]));
    delta = fightSeqCondChgActParaIdToValue(para);
    if (delta < 0) {
        if (fightSideIsJoutaiDataId(side, 0x4c) == 1 && !bypass && waza != 0xae) {
            if ((u32)(modeState.value & 0x1f) == 1) {
                if (fightOutPokemon_GetDoClearbodyFlag(target)) fightSeq_JumpWazaSeq(failure);
                else {
                    fightFloor_SetAppointPokemonPtr(0, target);
                    fightOutPokemon_SetDoClearbodyFlag(target, 1);
                    fightSeq_CallWazaSeq(WAZA_Shiroikiri);
                    fightSeq_JumpWazaSeq(failure);
                }
            }
            return 1;
        }
        if (waza != 0xae && skipGuard != 1 && fightSeqGuardCheck(0, 0)) {
            fightSeq_JumpWazaSeq(WAZA_Umakukimaran);
            return 1;
        }
        if ((ability == 0x1d || ability == 0x49) && !bypass && waza != 0xae) {
            if ((u32)(modeState.value & 0x1f) == 1) {
                if (fightOutPokemon_GetDoClearbodyFlag(target)) fightSeq_JumpWazaSeq(failure);
                else {
                    fightFloor_SetAppointPokemonPtr(0, target);
                    fightOutPokemon_SetDoClearbodyFlag(target, 1);
                    if (!fightFloorIsNowEncountOpeningVirtualBattle(0)) {
                        fightSeq_CallWazaSeq(WAZA_ClearBody);
                        fightSeq_JumpWazaSeq(failure);
                    }
                }
            }
            return 1;
        }
        if (ability == 0x33 && !bypass && status == 0xeb) {
            if ((u32)(modeState.value & 0x1f) == 1) {
                fightFloor_SetAppointPokemonPtr(0, target);
                fightSeq_CallWazaSeq(WAZA_Kairikibasami);
                fightSeq_JumpWazaSeq(failure);
            }
            return 1;
        }
        if (ability == 0x34 && !bypass && status == 0xe6) {
            if ((u32)(modeState.value & 0x1f) == 1) {
                fightFloor_SetAppointPokemonPtr(0, target);
                fightSeq_CallWazaSeq(WAZA_Kairikibasami);
                fightSeq_JumpWazaSeq(failure);
            }
            return 1;
        }
        if (ability == 0x13 && !(modeState.value & 0x1f)) return 1;
        if (delta <= -2) fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar(0x4f11));
        else fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar(0x4f9c));
        fightMsgctrlSetValue(0x41, (u32)GSmsgGetGSchar(0x4f12));
        if (value <= 0) ServerWork.flags[5] = 2;
        else ServerWork.flags[5] = targetKind;
    } else {
        if (delta >= 2) fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar(0x4f0f));
        else fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar(0x4f9c));
        fightMsgctrlSetValue(0x41, (u32)GSmsgGetGSchar(0x4f10));
        if (value >= 12) ServerWork.flags[5] = 2;
        else ServerWork.flags[5] = targetKind;
    }
    value += delta;
    if (value < 0) value = 0;
    if (value > 12) value = 12;
    pokemonSetStatus(target, 0, status, 0, value);
    if (ServerWork.flags[5] == 2 && (modeState.value & 1))
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
    if (ServerWork.flags[5] == 2 && !(modeState.value & 1)) return 1;
    return 0;
}

extern "C" {
s8 fightSeqCondChgActParaIdToValue(u8 para) {
    switch (para) {
    case 0x10: return 1;
    case 0x20: return 2;
    case 0x90: return -1;
    case 0xa0: return -2;
    }
    return 0;
}
}

extern "C" {
void WS_SUITORI(void) {
    s32 var_r4;
    FightWaza *temp_r3;

    fightSeq_GetWazaSeq();
    temp_r3 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    fightWaza_GetDamage(temp_r3);
    var_r4 = -(fightWaza_GetHitDamage(temp_r3) / 2);
    if (var_r4 == 0) {
        var_r4 = -1;
    }
    fightWaza_SetDamage(temp_r3, (u32) var_r4);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" void WS_NOMIKOMU(void) {
    s16 count;
    FightOutPokemon* attacker;
    FightWaza* waza;
    u8* failure;
    failure = *(u8**)(fightSeq_GetWazaSeq() + 1);
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x2d) == 0) {
        count = 0;
    } else {
        count = fightOutPokemonGetCountAsJoutaiDataId(attacker, 0x2d);
    }
    if ((s16)count <= 0) {
        ServerWork.flags[5] = 0;
        fightSeq_JumpWazaSeq(failure);
        return;
    }
    if (fightOutPokemonIsHpMantan(attacker) == 1) {
        fightOutPokemonInitJoutaiDataId(attacker, 0x2d);
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, attacker);
        ServerWork.flags[5] = 1;
        fightSeq_JumpWazaSeq(failure);
        return;
    }
    s16 remaining = joutaiDataBiosGetMaxCount(0x2d) - count;
    if (remaining < 0) remaining = 0;
    fightWaza_SetDamage(waza, -(s32)fightOutPokemonMaxHpWaruValue(attacker, 1 << remaining));
    UserWork[0x16002] = count;
    fightOutPokemonInitJoutaiDataId(attacker, 0x2d);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, attacker);
    fightSeq_NextWazaSeq(5);
}

extern "C" {
void WS_HAKIDASU(void) {
    FightOutPokemon *temp_r27;
    FightOutPokemon *temp_r31;
    s16 var_r29;
    s32 var_r27;
    u8 *temp_r26;
    u16 temp_r25;
    u16 temp_r24;
    void *temp_r5;
    FightWaza *temp_r30;
    u32 temp_r28;

    temp_r26 = *(u8**)(fightSeq_GetWazaSeq() + 1);
    temp_r31 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(temp_r31);
    temp_r25 = fightOutPokemon_GetUseWazaDataId(temp_r31);
    temp_r24 = fightWaza_GetIryoku(temp_r30);
    temp_r28 = fightWaza_GetZokusei(temp_r30);
    if (fightOutPokemonIsJoutaiDataId(temp_r31, 0x2D) == 0) {
        var_r29 = 0;
    } else {
        var_r29 = fightOutPokemonGetCountAsJoutaiDataId(temp_r31, 0x2D);
    }
    temp_r27 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r5 = fightTargetGetPtrAsNowFightType(2, temp_r27);
    if (var_r29 <= 0) {
        fightSeq_JumpWazaSeq(temp_r26);
        return;
    }
    if (ServerWork.flags[6] != 1) {
        var_r27 = var_r29 * ((s32 (*)(void*, void*, void*, u16, u16, u16))fightSeqWazaDamageCalc)(temp_r31, temp_r27, temp_r5, temp_r25, temp_r24, temp_r28);
        UserWork[0x16002] = var_r29;
        if (fightOutPokemonIsJoutaiDataId(temp_r31, 0x32) == 1) {
            var_r27 = (var_r27 * 0xF) / 10;
        }
        fightWaza_SetDamage(temp_r30, var_r27);
    }
    fightOutPokemonInitJoutaiDataId(temp_r31, 0x2D);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_TAKUWAERU(void) {
    FightOutPokemon *temp_r3;
    s16 var_r31;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    if (fightOutPokemonIsJoutaiDataId(temp_r3, 0x2D) == 0) {
        var_r31 = 0;
    } else {
        var_r31 = fightOutPokemonGetCountAsJoutaiDataId(temp_r3, 0x2D);
    }
    if ((s16) var_r31 == (s32) joutaiDataBiosGetMaxCount(0x2D)) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork.flags[5] = 1;
    } else {
        if (fightOutPokemonCheckWriteJoutaiDataId(temp_r3, 0x2D) == 2) {
            fightOutPokemonWriteJoutaiDataId(temp_r3, 0x2D, 0);
        }
        var_r31 = fightOutPokemonGetCountAsJoutaiDataId(temp_r3, 0x2D);
        fightMsgctrlSetValue(0x2F, (u32) (s16) var_r31);
        ServerWork.flags[5] = 0;
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_SAWAGU_CHECK(void) {
    FightOutPokemon *pokemon=(FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12,0);
    u16 ability=fightOutPokemonGetTokuseiDataId(pokemon);
    u8 *jump=*(u8**)(fightSeq_GetWazaSeq()+1);
    if(fightSeqSawaguCheck(pokemon)!=0){fightSeq_JumpWazaSeq(jump);return;}
    if(ability==0xF || ability==0x48){ServerWork.flags[5]=2;fightSeq_JumpWazaSeq(jump);return;}
    fightSeq_NextWazaSeq(5);
}
bool fightSeqSawaguCheck(void* pokemon) {
    return fightFloorLoopValidFightOutPokemon(0,_fightSeqSawaguCheckSub,pokemon,1)!=1;
}
}
static s32 _fightSeqSawaguCheckSub(void* arg0,u16,void* arg2) {
    FightOutPokemon* pokemon=(FightOutPokemon*)arg0;
    FightOutPokemon* other=(FightOutPokemon*)arg2;
    u16 ability=fightOutPokemonGetTokuseiDataId(other);
    if(fightOutPokemonCheckFightOut(pokemon)==0)return 1;
    if(fightOutPokemonIsJoutaiDataId(pokemon,0xB)==1 && ability!=0x2B){
        fightFloor_SetAppointPokemonPtr(0,pokemon);
        if(pokemon==other)ServerWork.flags[5]=0;else ServerWork.flags[5]=1;
        return 0;
    }
    return 1;
}

extern "C" {
void WS_SAWAGU(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_NEKODAMASHI(void) {
    u8 *temp_r31;

    temp_r31 = fightSeq_GetWazaSeq();
    if (fightOutPokemon_GetFightoutTurnCount(fightTargetGetPtrAsNowFightType(0x11, 0)) != 0) {
        fightSeq_NextWazaSeq(5);
        return;
    }
    fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
}
}

extern "C" {
void WS_NEMURU(void) {
    FightOutPokemon *temp_r3;
    u8 *temp_r31;
    FightWaza *temp_r29;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r29 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    fightTargetGetPtrAsNowFightType(0x12, 0);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, temp_r3);
    fightWaza_SetDamage(temp_r29, (u32) -(s32) fightOutPokemonMaxHpWaruValue(temp_r3, 1));
    if (fightOutPokemonIsHpMantan(temp_r3) == 1) {
        fightSeq_JumpWazaSeq(*(u8**)(temp_r31 + 1));
        return;
    }
    if ((fightOutPokemonIsJoutaiDataId(temp_r3, 3) == 1) || (fightOutPokemonIsJoutaiDataId(temp_r3, 4) == 1) || (fightOutPokemonIsJoutaiDataId(temp_r3, 5) == 1) || (fightOutPokemonIsJoutaiDataId(temp_r3, 6) == 1) || (fightOutPokemonIsJoutaiDataId(temp_r3, 7) == 1)) {
        ServerWork.flags[5] = 1;
    } else {
        ServerWork.flags[5] = 0;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r3, 8, 0);
    fightOutPokemonSetKaisuuJoutaiDataId(temp_r3, 8, 3);
    fightSeqCheckSetHensinBuffToMotoPokemon(temp_r3, 0x7C);
    fightSeq_NextWazaSeq(5);
}
}

extern "C" {
void WS_DAMAGE_CHG(void) {
    FightWaza *temp_r3;
    u8 *temp_r31;
    s32 temp_r3_2;
    s32 var_r29;
    s32 temp_r0_2;

    temp_r31 = fightSeq_GetWazaSeq();
    temp_r3 = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    var_r29 = fightWaza_GetDamage(temp_r3);
    temp_r3_2 = (u16)((u32 (*)(void*))pokemon_GetMaxHp)(fightOutPokemonGetPokemonPtr(fightTargetGetPtrAsNowFightType(0x12, 0)));
    switch (temp_r31[1]) {
    case 0:
        var_r29 *= -1;
        break;
    case 1:
        var_r29 = var_r29 / 2;
        if (var_r29 == 0) {
            var_r29 = 1;
        }
        temp_r0_2 = (s32) temp_r3_2 / 2;
        if (temp_r0_2 < var_r29) {
            var_r29 = temp_r0_2;
        }
        break;
    case 2:
        var_r29 *= 2;
        break;
    }
    fightWaza_SetDamage(temp_r3, var_r29);
    fightSeq_NextWazaSeq(2);
}
}

extern "C" {
void WS_YADORIGI(void) {
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r31;
    FightWaza *temp_r30;
    u32 temp_r29;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = fightOutPokemon_GetFightWazaPtr(temp_r3);
    temp_r29 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(temp_r3, fightFloor_GetFightType(0));
    temp_r31 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    if ((fightWazaIsHit(temp_r30) == 0) || (fightOutPokemonCheckWriteJoutaiDataId(temp_r31, 0x1C) != 2)) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork.flags[5] = 1;
        fightSeq_NextWazaSeq(1);
        return;
    }
    if (fightOutPokemonIsZokuseiDataId(temp_r31, 0xC) == 1) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork.flags[5] = 2;
        fightSeq_NextWazaSeq(1);
        return;
    }
    fightOutPokemonWriteJoutaiDataId(temp_r31, 0x1C, temp_r29);
    ServerWork.flags[5] = 0;
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_REFLEC(void) {
    FightOutPokemon *temp_r3;
    u16 temp_r31;
    FightSide *temp_r30;

    fightSeq_GetWazaSeq();
    temp_r3 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r30 = (FightSide*)fightTargetGetPtrAsNowFightType(2, temp_r3);
    temp_r31 = fightFloorGetValidFightOutPokemonCount(0, 1, temp_r3, 1);
    if (fightSideCheckWriteJoutaiDataId(temp_r30, 0x48) != 2) {
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
        ServerWork.flags[5] = 0;
    } else {
        fightSideWriteJoutaiDataId(temp_r30, 0x48, 0);
        if ((fightFloor_GetFightSideFightOutPokemonSideMax(0) >= 2) && (temp_r31 >= 2)) {
            ServerWork.flags[5] = 2;
        } else {
            ServerWork.flags[5] = 1;
        }
    }
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_OUMU_CHECK(void) {
    u16 buf[4];
    u8 fightType;
    FightOutPokemon* attacker;
    FightWaza* waza;
    u16 oumu;
    s32 n;
    FightOutPokemon* defender;

    fightType = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    oumu = fightOutPokemon_GetOumuWazaDataId(attacker);
    if (oumu != 0 && oumu != 0x176 && oumu != 0xffff) {
success:
        fightOutPokemonLoadWazaEffect(attacker, 0x77, 1, 0);
        fightOutPokemonWazaEffect(attacker, 0x77, 1, 1, fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(0x11)));
        fightOutPokemonFreeWazaEffect(attacker, 0x77, 1);
        ServerStatusFlag &= 0xfffffbff;
        fightWazaSetUseWazaStatus(waza, oumu);
        defender = fightSeqSelectDefensePokemonPtr(attacker, oumu, fightType, 0, 1, 1, -1);
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, defender);
        fightSeq_JumpWazaSeq(WazaEffectTbl[(u16)wazaDB_GetSeqId(oumu)]);
        return;
    }
    n = fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(attacker, buf);
    n += _fightOutPokemonGetFightOutPokemonAllyOumuWazaDataIdAry(attacker);
    if ((u8)n != 0) {
        oumu = buf[(u8)(HSD_Rand() % (u8)n)];
        if (oumu != 0 && oumu != 0x176) {
            goto success;
        }
        oumu = fightOutPokemon_GetOumuWazaAllyDataId(attacker);
        if (oumu != 0 && oumu != 0x176) {
            goto success;
        }
    }
    fightOutPokemon_SetNoPressureFlag(attacker, 1);
    fightSeq_NextWazaSeq(1);
}
}

s32 _fightOutPokemonGetFightOutPokemonAllyOumuWazaDataIdAry(FightOutPokemon* pokemon) {
    u16 waza = fightOutPokemon_GetOumuWazaAllyDataId(pokemon);
    if (waza != 0 && waza != 0x176) {
        return 1;
    }
    return 0;
}

extern "C" {
void WS_KAIFUKU(void) {
    u8* seq;
    FightOutPokemon* attacker;
    FightWaza* waza;
    FightOutPokemon* target;
    u8* jump;

    seq = fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    target = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x12, 0);
    jump = *(u8**)(seq + 1);
    if (seq[5] == 0x11) {
        target = attacker;
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, attacker);
    }
    fightWaza_SetDamage(waza, -(u16)fightOutPokemonMaxHpWaruValue(target, 2));
    if (fightOutPokemonIsHpMantan(target) == 1) {
        fightSeq_JumpWazaSeq(jump);
        return;
    }
    fightSeq_NextWazaSeq(6);
}
}

extern "C" {
void WS_JIBAKU_LOOP(void) {
    FightOutPokemon* attacker;
    FightOutPokemon* cur;
    FightOutPokemon* found;
    u8* jump;
    u8 mode;
    u8* seq;


    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    seq = fightSeq_GetWazaSeq();
    found = 0;
    mode = seq[5];
    jump = *(u8**)(seq + 1);
    fight_seq_banme_buff++;
    while (fight_seq_banme_buff < fight_seq_banme_max) {
        cur = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData();
        if (cur != 0 && fightOutPokemonCheckFightOut(cur) != 0 && (mode != 1 || attacker != cur)) {
            found = cur;
            break;
        }
        fight_seq_banme_buff++;
    }
    if (found != 0) {
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, found);
        fightSeq_JumpWazaSeq(jump);
        return;
    }
    fightSeq_NextWazaSeq(6);
}
}

extern "C" {
void WS_JIBAKU(void) {
    FightOutPokemon *temp_r31;

    temp_r31 = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightSeq_GetWazaSeq();
    pokemon_SetHp(fightOutPokemonGetPokemonPtr(temp_r31), 0);
    fightSeqCheckSetHensinBuffToMotoPokemon(temp_r31, 0x83);
    fightSeq_NextWazaSeq(1);
}
}

extern "C" {
void WS_JIBAKU_INIT(void) {
    u8 fightType;
    FightWaza* waza;
    FightOutPokemon* attacker;
    s32 menuId;
    FightOutPokemon* found;
    FightOutPokemon* cur;
    FightOutPokemon* tokusei;
    u8* seq;


    fightType = fightFloor_GetFightType(0);
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(attacker, fightType, 1);
    seq = fightSeq_GetWazaSeq();
    if (seq[1] == 1) {
        tokusei = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(0, 6, 0, 0, 0);
        if (tokusei == 0) {
            fightWaza_SetDamage(waza, (u16)pokemon_GetHp(fightOutPokemonGetPokemonPtr(attacker)));
            menuFightStatusSetHP(menuId, 0);
            fight_seq_banme_max = 8;
            found = 0;
            fight_seq_banme_buff = 0;
            while (fight_seq_banme_buff < fight_seq_banme_max) {
                cur = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData();
                if (cur != 0 && fightOutPokemonCheckFightOut(cur) != 0 && attacker != cur) {
                    found = cur;
                    break;
                }
                fight_seq_banme_buff++;
            }
            if (found != 0) {
                fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, found);
            }
            fightSeq_NextWazaSeq(2);
        } else {
            fightFloor_SetDefensePokemonPtr(0, tokusei);
            fightSeq_JumpWazaSeq(WAZA_Shimerike);
        }
    } else if (seq[1] == 0) {
        fight_seq_banme_max = 8;
        cur = 0;
        fight_seq_banme_buff = 0;
        while (fight_seq_banme_buff < fight_seq_banme_max) {
            found = (FightOutPokemon*)fightFloor_GetFightOutPokemonFromDefaultSortData();
            if (found != 0 && fightOutPokemonCheckFightOut(found) != 0) {
                cur = found;
                break;
            }
            fight_seq_banme_buff++;
        }
        if (cur != 0) {
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, cur);
        }
        fightSeq_NextWazaSeq(2);
    }
}
}

extern "C" const u16 KakuritsuTable[4];
extern "C" void WS_GUARD_SUCCESS_CHECK(void) {
    FightOutPokemon* attacker;
    u16 last;
    u16 sequence;
    u8 allowed;
    allowed = 1;
    fightSeq_GetWazaSeq();
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    sequence = wazaDB_GetSeqId(fightOutPokemon_GetUseWazaDataId(attacker));
    last = fightOutPokemon_GetLastUseWazaDataId(attacker);
    u8 count = fightOutPokemon_GetSuccessCnt(attacker);
    if (last != 0xb6 && last != 0xc5 && last != 0xcb) {
        count = 0;
        fightOutPokemon_SetSuccessCnt(attacker, 0);
    }
    if (fightFloorIsLastActionFightOutPokemon(0) == 1) allowed = 0;
    if (KakuritsuTable[count] > HSD_Rand() && allowed) {
        if (sequence == 0x6f) {
            if (fightOutPokemonCheckWriteJoutaiDataId(attacker, 0x2b) == 2)
                fightOutPokemonWriteJoutaiDataId(attacker, 0x2b, 0);
            ServerWork.flags[5] = 0;
        }
        if (sequence == 0x74) {
            if (fightOutPokemonCheckWriteJoutaiDataId(attacker, 0x2c) == 2)
                fightOutPokemonWriteJoutaiDataId(attacker, 0x2c, 0);
            ServerWork.flags[5] = 1;
        }
        ++count;
        if (count > 3) count = 3;
        fightOutPokemon_SetSuccessCnt(attacker, count);
    } else {
        fightOutPokemon_SetSuccessCnt(attacker, 0);
        ServerWork.flags[5] = 2;
        fightFloor_SetAttackPokemonFightWazaJoutaiDataId(0, 0x40);
    }
    fightSeq_NextWazaSeq(1);
}

extern "C" u16 fightSeqCondChgActTypeToPokemonStatusId(u8 type) {
    switch(type){
    case 0:break;
    case 1:return 0xE6;
    case 2:return 0xE7;
    case 3:return 0xEA;
    case 4:return 0xE8;
    case 5:return 0xE9;
    case 6:return 0xEB;
    case 7:return 0xEC;
    }
    return 0;
}
