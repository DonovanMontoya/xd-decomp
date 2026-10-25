#include <game/pxdvs/app/fight/fightSeq/fightSeqWSWazaPrivate.hpp>

extern "C" {
void DamageCalcHikaePokemon(void* defPokemon) {
    FightSide* side;
    u32 zokusei;
    FightOutPokemon* attacker;
    u16 useWaza;
    u16 iryoku;
    FightWaza* waza;
    void* arg;
    s32 damage;


    arg = defPokemon;
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    side = (FightSide*)fightTargetGetPtrAsNowFightType(3, attacker);
    useWaza = fightOutPokemon_GetUseWazaDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    iryoku = fightWaza_GetIryoku(waza);
    zokusei = fightWaza_GetZokusei(waza);
    side = (FightSide*)(u32)fightSeqWazaDamageCalcHikaePokemon(attacker, arg, side, useWaza, iryoku, zokusei);
    damage = (s32)side * fightWaza_GetCritical(waza);
    damage = damage * fightWaza_GetDamageValue(waza);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x24) == 1 && (u16)zokusei == 0xd) {
        damage *= 2;
    }
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x32) == 1) {
        damage = damage * 15 / 10;
    }
    fightWaza_SetDamage(waza, damage);
}

void CriticalCheckHikaePokemon(void* arg) {
    FightOutPokemon* attacker;
    u32 item;
    FightWaza* waza;
    u16 useWaza;
    u16 defId;
    u32 tokuseiFlag;
    u32 pokeId;
    u8 var30;
    u8 var29;
    s32 sum;
    u8 seqFlag;
    u16 level;
    u32 maxIdx;
    s32 rnd;



    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemonGetTokuseiDataId(attacker);
    item = fightOutPokemonGetSoubiItemSoubiDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    useWaza = fightOutPokemon_GetUseWazaDataId(attacker);
    pokeId = figthOutPokemonGetPokemonDataId(attacker);
    defId = pokemon_GetPokemonDataId(fightPokemon_GetPokemonBuffPtr(arg));
    tokuseiFlag = (u8)pokemon_GetTokuseiFlag(fightPokemon_GetPokemonBuffPtr(arg));
    var29 = 0;
    if ((u16)item == 0x3f && (u16)pokeId == 0x71) {
        var29 = 1;
    }
    var30 = 0;
    if ((u16)item == 0x42 && (u16)pokeId == 0x53) {
        var30 = 1;
    }
    sum = (fightOutPokemonIsJoutaiDataId(attacker, 0xf) == 1) * 2;
    seqFlag = wazaDB_GetSeqId(useWaza) == 0x2b;
    sum = sum + (u8)(wazaDB_GetSeqId(useWaza) == 0x4b);
    sum = sum + (u8)(wazaDB_GetSeqId(useWaza) == 0xc8);
    level = (sum + (u8)(wazaDB_GetSeqId(useWaza) == 0xd1) + (u8)((u16)item == 0x29) + var29 * 2 + var30 * 2) + seqFlag;
    maxIdx = fight_waza_critical_data_number - 1;
    if (level > maxIdx) {
        level = maxIdx;
    }
    if (pokemonDB_GetTokuseiDataId(defId, tokuseiFlag) != 4 && pokemonDB_GetTokuseiDataId(defId, tokuseiFlag) != 0x4b && fightFloor_GetFightKindDoCriticalAttackFlag(0) == 1) {
        rnd = (u16)HSD_Rand();
        if (rnd % fightWazaCriticalDataBiosGetBunbo(fightWazaCriticalDataBiosGetPtr(level)) == 0) {
            fightWaza_SetCritical(waza, 2);
        } else {
            fightWaza_SetCritical(waza, 1);
        }
    } else {
        fightWaza_SetCritical(waza, 1);
    }
}
}

extern "C" {
bool fightSeqGetEffectAminFlag(void) {
    return !(ServerStatusFlag & 0x80);
}

void fightSeqSetEffectAminFlag(u8 on) {
    if (on == 1) {
        ServerStatusFlag &= ~0x80;
    } else {
        ServerStatusFlag |= 0x80;
    }
}
}

static s32 _fightSeqInitSubFightOutPokemon(void* pokemon, u16, void*) {
    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    fightOutPokemonInitJoutaiDataId(pokemon, 0x11);
    return 1;
}

extern "C" {
u8 fightSeqFightActionCreateAndFlowFifo(void* a, void* b, u16 c, s32 d, void* e, void* f) {
    WSFightAction action;
    u8 r = fightSeqFightActionCreate(&action, a, b, c, d, e, f);
    if (r != 1) {
        return r;
    }
    return fightActionFlowFifo(&action);
}

u8 fightSeqFightActionCreate(void* out, void* a, void* b, u16 c, s32 d, void* e, void* f) {
    u8 r = fightActionCreate(out, a, b, c, d, e);
    if (r != 1) {
        return r;
    }
    fightActionBiosSetBuffDataPtr(out, f);
    return 1;
}
}

extern "C" {
void fightSeqPost(void) {
    ServerStatusFlag &= 0xFFEFFFFF;
    fightSeqTurnCheck();
}
}

static s32 _fightSeqPreSub(void* pokemon, u16, void*) {
    if (fightOutPokemonCheckFightOut(pokemon) == 0) {
        return 1;
    }
    void* action = fightOutPokemon_GetFightActionBuffPtr(pokemon);
    if (action == 0) {
        return 1;
    }
    if (fightActionCheckValid(action) == 0) {
        return 1;
    }
    if ((u16)fightOutPokemon_GetMotoWazaDataId(pokemon) == 0x108 && fightOutPokemonIsJoutaiDataId(pokemon, 8) == 0 && fightOutPokemon_GetNamakeFlag(pokemon) == 0) {
        fightSeqFightActionCreateAndFlowFifo(fightActionBiosGetFightActionDataPtr(fight_seq_now_fight_action_ptr), pokemon, 0xc, 0, fight_action_data_turn, WAZA_KiaiPunch);
    }
    return 1;
}

extern "C" {
void WS_BADGECHECK(void);
void WS_HITCHECK(void);
void WS_ATTACK_MESSAGE(void);
void WS_ATTACK_MESSAGE2(void);
void WS_PP_DEC(void);
void WS_DAMAGE_LOSS_ONLY(void);
void WS_WAZA_EFFECT(void);
void WS_EFFECT_WAIT(void);
void WS_HP_DEC(void);
void WS_HP_DEC_WAIT(void);
void WS_CRITICAL_MESSAGE(void);
void WS_WAZAKOUKA_SE(void);
void WS_WAZAKOUKA_MESSAGE(void);
void WS_MESSAGE(void);
void WS_ALERT_MESSAGE(void);
void WS_MESSAGE_WAIT(void);
void WS_MESSAGE_TBL(void);
void WS_ALERT_MESSAGE_TBL(void);
void WS_TSUIKA_CHECK(void);
void WS_TSUIKA_DIRECT_ACT(void);
void WS_TSUIKA_INDIRECT_ACT(void);
void WS_SAKUJO(void);
void WS_KIZETSU_CHECK(void);
void WS_KIZETSU(void);
void WS_KIZETSU_WAIT(void);
void WS_CONDITION_CHECK(void);
void WS_CONDITION2_CHECK(void);
void WS_SPEABI_CHECK(void);
void WS_SIDECONDITION_CHECK(void);
void WS_CONDCHG_CHECK(void);
void WS_WAZAKOUKA_CHECK(void);
void WS_CHECK_TYPE(void);
void WS_GET_EXP(void);
void WS_ZENMETSU_CHECK(void);
void WS_LOOP_INIT(void);
void WS_LOOPCNT(void);
void WS_LOOP(void);
void WS_JUMP(void);
void WS_IF8(void);
void WS_IF16(void);
void WS_IF32(void);
void WS_IFWEQ(void);
void WS_IFWNE(void);
void WS_SETVALUE(void);
void WS_ADDVALUE(void);
void WS_SUBVALUE(void);
void WS_SETWORK(void);
void WS_SETWORKOFS(void);
void WS_SET8BIT(void);
void WS_SET16BIT(void);
void WS_SET32BIT(void);
void WS_RESET8BIT(void);
void WS_RESET16BIT(void);
void WS_RESET32BIT(void);
void WS_WAIT(void);
void WS_CLIENT_BIT_WAIT(void);
void WS_HP_GAUGE_REDRAW(void);
void WS_SEQRET(void);
void WS_WAZAEND(void);
void WS_SEQEND(void);
void WS_SPEABIEND(void);
void WS_GUARDCHECK(void);
void WS_GOSUB(void);
void WS_MONS_TYPE(void);
void WS_SPEABI_HAVE_CHECK(void);
void WS_ALERTEND(void);
void WS_FIGHT_EFFECT(void);
void WS_FIGHT_EFFECT2(void);
void WS_COND_CHG_WORK_SET(void);
void WS_COND_CHG_BIT_CHECK(void);
void WS_WKC_ACT(void);
void WS_TYPE_CHECK_NO_HIT(void);
void WS_MODOSU_EFFECT(void);
void WS_APPEAR_EFFECT_INIT(void);
void WS_APPEAR_EFFECT(void);
void WS_APPEAR_EFFECT_WAIT(void);
void WS_RESHUFFLE_CHECK(void);
void WS_POKE_RESHUFFLE(void);
void WS_POKE_RESHUFFLE_WAIT(void);
void WS_POKE_RESHUFFLE_END(void);
void WS_TRAINER_APPEAR(void);
void WS_SE_PLAY(void);
void WS_ME_PLAY(void);
void WS_VOICE(void);
void WS_END_FIGHT(void);
void WS_POKEDELACTOR(void);
void WS_WAZAOBOE_CHECK(void);
void WS_WAZAWASURE_CHECK(void);
void WS_WAZAAKIRAME_CHECK(void);
void WS_POKE_BLINK(void);
void WS_OKODUKAI_CALC(void);
void WS_WAZA_GET(void);
void WS_SWITCH_A_D(void);
void WS_INC_RECORD(void);
void WS_BALL_GAUGE_SET(void);
void WS_BALL_GAUGE_OFF(void);
void WS_WAZASEQADRS(void);
void WS_STATUS_EFFECT(void);
void WS_STATUS_EFFECT2(void);
void WS_STATUS_EFFECT_DIRECT(void);
void WS_YES_NO_WINDOW(void);
void WS_SCA_END_SET(void);
void WS_KORAERU_CHECK(void);
void WS_KILLITEM(void);
void WS_RESHUFFLE_NICKNAME(void);
void WS_STATUS_WINDOW(void);
void WS_EXPFLAG_CLEAR(void);
void WS_GET_RESHUFFLE_CLIENT(void);
void WS_VANISH_OFF(void);
void WS_TOKUSYUNO_SET(void);
void WS_OBOEWAZANO_SET(void);
void WS_ESCAPE_CHECK(void);
void WS_POKE_HPMAX_RATE(void);
void WS_POKE_HPDEC_RATE(void);
void WS_STATUS_RECOVER(void);
void WS_SUBROUTINE_CALL(void);
void WS_TOKUSEI_SET(void);
void WS_GUARD_SUCCESS_CHECK(void);
void WS_JIBAKU_INIT(void);
void WS_JIBAKU(void);
void WS_JIBAKU_LOOP(void);
void WS_KAIFUKU(void);
void WS_OUMU_CHECK(void);
void WS_REFLEC(void);
void WS_YADORIGI(void);
void WS_DAMAGE_CHG(void);
void WS_NEMURU(void);
void WS_NEKODAMASHI(void);
void WS_SAWAGU(void);
void WS_SAWAGU_CHECK(void);
void WS_TAKUWAERU(void);
void WS_HAKIDASU(void);
void WS_NOMIKOMU(void);
void WS_SUITORI(void);
void WS_CONDCHG(void);
void WS_KUROIKIRI(void);
void WS_GAMAN(void);
void WS_ABARERU(void);
void WS_RENZOKU(void);
void WS_RENZOKU_NUM_INIT(void);
void WS_HUKITOBASHI(void);
void WS_TEXTURE(void);
void WS_KOBAN_CHECK(void);
void WS_HIKARINOKABE(void);
void WS_ICHIGEKI(void);
void WS_HPHALF(void);
void WS_WEATHER_CHANGE(void);
void WS_WEATHER_KEEP(void);
void WS_MEROMERO(void);
void WS_CONDITION_GAUGE(void);
void WS_SHIROIKIRI(void);
void WS_KIAIDAME(void);
void WS_HENSHIN(void);
void WS_MIGAWARI(void);
void WS_MONOMANE(void);
void WS_YUBIWOHURU(void);
void WS_CHIKYUUNAGE(void);
void WS_PSYCHOWAVE(void);
void WS_COUNTER(void);
void WS_MIRRORCOAT(void);
void WS_KANASHIBARI(void);
void WS_ENCORE(void);
void WS_ITAMIWAKE(void);
void WS_TEXTURE2(void);
void WS_LOCKON(void);
void WS_SKETCH(void);
void WS_NEGOTO(void);
void WS_MICHIDURE(void);
void WS_MICHIDURE_CHECK(void);
void WS_JITABATA(void);
void WS_URAMI(void);
void WS_IYASHINOSUZU(void);
void WS_NOROI(void);
void WS_MAKIBISHI(void);
void WS_MIYABURU(void);
void WS_HOROBINOUTA(void);
void WS_KOROGARU(void);
void WS_IBARU(void);
void WS_RENZOKUGIRI(void);
void WS_NATSUKI(void);
void WS_PRESENT(void);
void WS_SHINPINOMAMORI(void);
void WS_MAGNITUDE(void);
void WS_OIUCHI_CHECK(void);
void WS_HARADAIKO(void);
void WS_JIKOANJI(void);
void WS_KOUSOKUSPIN(void);
void WS_MARUKUNARU(void);
void WS_WEATHERKAIFUKU(void);
void WS_MEZAMERUPOWER(void);
void WS_JISIN(void);
void WS_MIRAIYOCHI(void);
void WS_HUKURODATAKI(void);
void WS_KIERUTAME(void);
void WS_KIERUTAME_AFTAR(void);
void WS_CHIISAKUNARU(void);
void WS_OKIMIYAGE(void);
void WS_KONOYUBITOMARE(void);
void WS_JUUDEN(void);
void WS_SHIZENNOCHIKARA(void);
void WS_REFLESH(void);
void WS_ICHAMON(void);
void WS_KIAIPUNCH(void);
void WS_CHOUHATSU(void);
void WS_TEDASUKE(void);
void WS_TRICK(void);
void WS_NARIKIRI(void);
void WS_NEGAIGOTO(void);
void WS_NEWOHARU(void);
void WS_REVENGE(void);
void WS_AKUBI(void);
void WS_GAMUSYARA(void);
void WS_HUNKA(void);
void WS_SKILLSWAP(void);
void WS_HUUIN(void);
void WS_ONNEN(void);
void WS_KETAGURI(void);
void WS_NEKONOTE(void);
void WS_MAGICCORT(void);
void WS_YOKODORI(void);
void WS_IKAKU(void);
void WS_SIZENKAIHUKU(void);
void WS_HP_CHECK(void);
void WS_HIMITUNOTIKARA(void);
void WS_MONOHIROI(void);
void WS_TENKIYA(void);
void WS_TENKIYA_CHECK(void);
void WS_ASOBI(void);
void WS_WEATHER_BALL(void);
void WS_RECYCLE(void);
void WS_HOGOSYOKU(void);
void WS_HUKITOBASHI_OIUCHI(void);
void WS_YOKODORI_CLIENT_SET(void);
void WS_KAWARAWARI(void);
void WS_DARKREMOVE(void);
void WS_TELEPORT(void);
void WS_BALL_THROW(void);
void WS_ADD_POKE(void);
void WS_ZUKAN_CHECK(void);
void WS_ZUKAN(void);
void WS_NICKNAME(void);
void WS_ITEM_HP_KAIFUKU(void);
void WS_ITEM_CONDITION_RECOVER(void);
void WS_ITEMEND(void);
void WS_GETEND(void);
void WS_STATUS_GET8(void);
void WS_STATUS_GET16(void);
void WS_STATUS_GET32(void);
void WS_STATUS_SET8(void);
void WS_STATUS_SET16(void);
void WS_STATUS_SET32(void);
}

static void (*const WazaSequenceTbl[])(void) = {
    WS_BADGECHECK,
    WS_HITCHECK,
    WS_ATTACK_MESSAGE,
    WS_ATTACK_MESSAGE2,
    WS_PP_DEC,
    WS_CRITICAL_CHECK,
    WS_DAMAGE_CALC,
    WS_TYPE_CHECK,
    WS_DAMAGE_LOSS,
    WS_DAMAGE_LOSS_ONLY,
    WS_WAZA_EFFECT,
    WS_EFFECT_WAIT,
    WS_HP_DEC,
    WS_HP_DEC_WAIT,
    WS_CRITICAL_MESSAGE,
    WS_WAZAKOUKA_SE,
    WS_WAZAKOUKA_MESSAGE,
    WS_MESSAGE,
    WS_ALERT_MESSAGE,
    WS_MESSAGE_WAIT,
    WS_MESSAGE_TBL,
    WS_ALERT_MESSAGE_TBL,
    WS_TSUIKA_CHECK,
    WS_TSUIKA_DIRECT_ACT,
    WS_TSUIKA_INDIRECT_ACT,
    WS_SAKUJO,
    WS_KIZETSU_CHECK,
    WS_KIZETSU,
    WS_KIZETSU_WAIT,
    WS_CONDITION_CHECK,
    WS_CONDITION2_CHECK,
    WS_SPEABI_CHECK,
    WS_SIDECONDITION_CHECK,
    WS_CONDCHG_CHECK,
    WS_WAZAKOUKA_CHECK,
    WS_CHECK_TYPE,
    WS_GET_EXP,
    WS_ZENMETSU_CHECK,
    WS_LOOP_INIT,
    WS_LOOPCNT,
    WS_LOOP,
    WS_JUMP,
    WS_IF8,
    WS_IF16,
    WS_IF32,
    WS_IFWEQ,
    WS_IFWNE,
    WS_SETVALUE,
    WS_ADDVALUE,
    WS_SUBVALUE,
    WS_SETWORK,
    WS_SETWORKOFS,
    WS_SET8BIT,
    WS_SET16BIT,
    WS_SET32BIT,
    WS_RESET8BIT,
    WS_RESET16BIT,
    WS_RESET32BIT,
    WS_WAIT,
    WS_CLIENT_BIT_WAIT,
    WS_HP_GAUGE_REDRAW,
    WS_SEQRET,
    WS_WAZAEND,
    WS_SEQEND,
    WS_SPEABIEND,
    WS_GUARDCHECK,
    WS_GOSUB,
    WS_MONS_TYPE,
    WS_SPEABI_HAVE_CHECK,
    WS_ALERTEND,
    WS_FIGHT_EFFECT,
    WS_FIGHT_EFFECT2,
    WS_COND_CHG_WORK_SET,
    WS_COND_CHG_BIT_CHECK,
    WS_WKC_ACT,
    WS_TYPE_CHECK_NO_HIT,
    WS_MODOSU_EFFECT,
    WS_APPEAR_EFFECT_INIT,
    WS_APPEAR_EFFECT,
    WS_APPEAR_EFFECT_WAIT,
    WS_RESHUFFLE_CHECK,
    WS_POKE_RESHUFFLE,
    WS_POKE_RESHUFFLE_WAIT,
    WS_POKE_RESHUFFLE_END,
    WS_TRAINER_APPEAR,
    WS_SE_PLAY,
    WS_ME_PLAY,
    WS_VOICE,
    WS_END_FIGHT,
    WS_POKEDELACTOR,
    WS_WAZAOBOE_CHECK,
    WS_WAZAWASURE_CHECK,
    WS_WAZAAKIRAME_CHECK,
    WS_POKE_BLINK,
    WS_OKODUKAI_CALC,
    WS_WAZA_GET,
    WS_SWITCH_A_D,
    WS_INC_RECORD,
    WS_BALL_GAUGE_SET,
    WS_BALL_GAUGE_OFF,
    WS_WAZASEQADRS,
    WS_STATUS_EFFECT,
    WS_STATUS_EFFECT2,
    WS_STATUS_EFFECT_DIRECT,
    WS_YES_NO_WINDOW,
    WS_SCA_END_SET,
    WS_KORAERU_CHECK,
    WS_KILLITEM,
    WS_RESHUFFLE_NICKNAME,
    WS_STATUS_WINDOW,
    WS_EXPFLAG_CLEAR,
    WS_GET_RESHUFFLE_CLIENT,
    WS_VANISH_OFF,
    WS_TOKUSYUNO_SET,
    WS_OBOEWAZANO_SET,
    WS_ESCAPE_CHECK,
    WS_POKE_HPMAX_RATE,
    WS_POKE_HPDEC_RATE,
    WS_STATUS_RECOVER,
    WS_SUBROUTINE_CALL,
    WS_TOKUSEI_SET,
    WS_GUARD_SUCCESS_CHECK,
    WS_JIBAKU_INIT,
    WS_JIBAKU,
    WS_JIBAKU_LOOP,
    WS_KAIFUKU,
    WS_OUMU_CHECK,
    WS_REFLEC,
    WS_YADORIGI,
    WS_DAMAGE_CHG,
    WS_NEMURU,
    WS_NEKODAMASHI,
    WS_SAWAGU,
    WS_SAWAGU_CHECK,
    WS_TAKUWAERU,
    WS_HAKIDASU,
    WS_NOMIKOMU,
    WS_SUITORI,
    WS_CONDCHG,
    WS_KUROIKIRI,
    WS_GAMAN,
    WS_ABARERU,
    WS_RENZOKU,
    WS_RENZOKU_NUM_INIT,
    WS_HUKITOBASHI,
    WS_TEXTURE,
    WS_KOBAN_CHECK,
    WS_HIKARINOKABE,
    WS_ICHIGEKI,
    WS_HPHALF,
    WS_WEATHER_CHANGE,
    WS_WEATHER_KEEP,
    WS_MEROMERO,
    WS_CONDITION_GAUGE,
    WS_SHIROIKIRI,
    WS_KIAIDAME,
    WS_HENSHIN,
    WS_MIGAWARI,
    WS_MONOMANE,
    WS_YUBIWOHURU,
    WS_CHIKYUUNAGE,
    WS_PSYCHOWAVE,
    WS_COUNTER,
    WS_MIRRORCOAT,
    WS_KANASHIBARI,
    WS_ENCORE,
    WS_ITAMIWAKE,
    WS_TEXTURE2,
    WS_LOCKON,
    WS_SKETCH,
    WS_NEGOTO,
    WS_MICHIDURE,
    WS_MICHIDURE_CHECK,
    WS_JITABATA,
    WS_URAMI,
    WS_IYASHINOSUZU,
    WS_NOROI,
    WS_MAKIBISHI,
    WS_MIYABURU,
    WS_HOROBINOUTA,
    WS_KOROGARU,
    WS_IBARU,
    WS_RENZOKUGIRI,
    WS_NATSUKI,
    WS_PRESENT,
    WS_SHINPINOMAMORI,
    WS_MAGNITUDE,
    WS_OIUCHI_CHECK,
    WS_HARADAIKO,
    WS_JIKOANJI,
    WS_KOUSOKUSPIN,
    WS_MARUKUNARU,
    WS_WEATHERKAIFUKU,
    WS_MEZAMERUPOWER,
    WS_JISIN,
    WS_MIRAIYOCHI,
    WS_HUKURODATAKI,
    WS_KIERUTAME,
    WS_KIERUTAME_AFTAR,
    WS_CHIISAKUNARU,
    WS_OKIMIYAGE,
    WS_KONOYUBITOMARE,
    WS_JUUDEN,
    WS_SHIZENNOCHIKARA,
    WS_REFLESH,
    WS_ICHAMON,
    WS_KIAIPUNCH,
    WS_CHOUHATSU,
    WS_TEDASUKE,
    WS_TRICK,
    WS_NARIKIRI,
    WS_NEGAIGOTO,
    WS_NEWOHARU,
    WS_REVENGE,
    WS_AKUBI,
    WS_GAMUSYARA,
    WS_HUNKA,
    WS_SKILLSWAP,
    WS_HUUIN,
    WS_ONNEN,
    WS_KETAGURI,
    WS_NEKONOTE,
    WS_MAGICCORT,
    WS_YOKODORI,
    WS_IKAKU,
    WS_SIZENKAIHUKU,
    WS_HP_CHECK,
    WS_HIMITUNOTIKARA,
    WS_MONOHIROI,
    WS_TENKIYA,
    WS_TENKIYA_CHECK,
    WS_ASOBI,
    WS_WEATHER_BALL,
    WS_RECYCLE,
    WS_HOGOSYOKU,
    WS_HUKITOBASHI_OIUCHI,
    WS_YOKODORI_CLIENT_SET,
    WS_KAWARAWARI,
    WS_DARKREMOVE,
    WS_TELEPORT,
    WS_BALL_THROW,
    WS_ADD_POKE,
    WS_ZUKAN_CHECK,
    WS_ZUKAN,
    WS_NICKNAME,
    WS_ITEM_HP_KAIFUKU,
    WS_ITEM_CONDITION_RECOVER,
    WS_ITEMEND,
    WS_GETEND,
    WS_STATUS_GET8,
    WS_STATUS_GET16,
    WS_STATUS_GET32,
    WS_STATUS_SET8,
    WS_STATUS_SET16,
    WS_STATUS_SET32,
};

extern "C" {
void fightSeqExec(void* actionPtr, u8* seq, u8 flag) {
    void* savedAction;
    u8 savedSeqNo;
    u8* savedSeq;

    savedAction = fight_seq_now_fight_action_ptr;
    savedSeqNo = ActionSeqNo;
    savedSeq = fightSeq_GetWazaSeq();
    fightSeq_JumpWazaSeq(seq);
    if (flag == 0) {
        ActionSeqNo = 0;
    }
    fight_seq_now_fight_action_ptr = actionPtr;
    for (;;) {
        WazaSequenceTbl[(u16)*fightSeq_GetWazaSeq()]();
        if (flag != 0) {
            if (ActionSeqNo == 1) {
                SCA_EndCheck();
            }
            if (ActionSeqNo == 2) {
                SCA_End();
                break;
            }
        } else if (ActionSeqNo == 1 || ActionSeqNo == 2) {
            break;
        }
    }
    if (flag != 0) {
        ServerStatusFlag &= 0xFFFFFDFF;
        ServerStatusFlag &= 0xFFF7FFFF;
    }
    fight_seq_now_fight_action_ptr = savedAction;
    ActionSeqNo = savedSeqNo;
    fightSeq_JumpWazaSeq(savedSeq);
}
}

static s32 _fightSeqClearOneSelfTurnCountSub(void* pokemon, u16, void*) {
    fightOutPokemonInitOneSelfTurn(pokemon);
    return 1;
}

extern "C" {
void SCA_EndCheck(void) {
    fightSeqGetExpCheck();
    ActionSeqNo = 2;
}

void fightSeqClearOneSelfTurnCount(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqClearOneSelfTurnCountSub, 0, 0);
}

void fightSeqSpecificationActionCounterInit(void* pokemon) {
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x2E) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2E);
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x15) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x15);
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x28) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x28);
    }
}

void fightSeqIrekaeExec(void* arg) {
    void* pokemon = fightFloor_GetIrekaePokemonPtr(0);
    fightFloor_SetAttackPokemonPtr(0, pokemon);
    fightMsgctrlSetValue(0xD, (u32)fightOutPokemonGetNicknamePtr(pokemon));
    ActionSeqNo = 0;
    fightSeqSpecificationActionCounterInit(pokemon);
    fightSeq_CallWazaSeqCustom(arg, WAZA_PokeReshuffle, 1);
    wazaSequenceSysFreeAllWaza();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
}

u8 fightSeqGetItemType(u16 item, void *pokemon) {
    void* param = itemParamGetPtr(itemDataBiosGetItemEffectParam(itemDataBiosGetPtr(item)));
    if (param == 0) {
        return 7;
    }
    if (item == 0x13) {
        return 1;
    }
    if (itemParamGetHPUp(param) != 0) {
        return 2;
    }
    if (itemParamGetSleepFlag(param) == 1 || itemParamGetPoisonFlag(param) == 1 || itemParamGetBurnFlag(param) == 1 ||
        itemParamGetFreezeFlag(param) == 1 || itemParamGetParalyzeFlag(param) == 1 ||
        itemParamGetConfuseFlag(param) == 1) {
        return 3;
    }
    if (itemParamGetCriticalFlag(param) == 1) {
        return 4;
    }
    if ((u8)itemParamGetAttackUp(param) != 0 || (u8)itemParamGetDefenceUp(param) != 0 || (u8)itemParamGetQuickUp(param) != 0 ||
        (u8)itemParamGetHitUp(param) != 0 || (u8)itemParamGetSpAttackUp(param) != 0) {
        return 5;
    }
    if (itemParamGetGuardFlag(param) == 1) {
        return 6;
    }
    return 7;
}
}

static s32 _fightSeqClearOneTurnCountSub(void* pokemon, u16, void* data) {
    u8 count;
    s8 next;
    u16 turn;
    if (*(u8*)data == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2B);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2C);
    } else {
        fightOutPokemonInitOneTurn(pokemon);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x32);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x37);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x33);
        turn = fightOutPokemon_GetFightoutTurnCount(pokemon);
        if (turn != 0) {
            fightOutPokemon_SetFightoutTurnCount(pokemon, turn - 1);
        }
        if (fightOutPokemonIsJoutaiDataId(pokemon, 0x12) == 1) {
            count = fightOutPokemonGetNowKaisuuJoutaiDataId(pokemon, 0x12);
            s32 limit = (s8)fightOutPokemonGetKaisuuJoutaiDataId(pokemon, 0x12);
            next = (s8)count + 1;
            if (next >= limit) {
                fightOutPokemonInitJoutaiDataId(pokemon, 0x12);
            } else {
                fightOutPokemonSetNowKaisuuJoutaiDataId(pokemon, 0x12, next);
            }
        }
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(pokemon) <= 0) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x14);
    }
    return 1;
}

extern "C" {
void fightSeqClearOneTurnCount(s8 flag) {
    u16 i;
    void* side;
    fightFloorLoopValidFightOutPokemon(0, _fightSeqClearOneTurnCountSub, &flag, 0);
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(0, i);
        if (side != 0) {
            fightSideInitJoutaiDataId((u8*)side, 0x4D);
        }
    }
}
}

static s32 _fightSeqTurnCheckSubFightOutPokemon(void* pokemon, u16, void*) {
    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    fightOutPokemonInitJoutaiDataId(pokemon, 0x11);
    if (fightOutPokemonIsJoutaiDataId(pokemon, 8) == 1 && fightOutPokemonIsJoutaiDataId(pokemon, 0x22) == 1) {
        fightOutPokemonInitJoutaiKeep(pokemon);
    }
    return 1;
}

extern "C" {
void fightSeqInit(void){
    s32 count;
    fightSeqClearOneTurnCount(0);
    fightSeqClearOneSelfTurnCount();
    for(count=0;count<8;count++)ServerWork.flags[count]=0;
    fight_seq_now_fight_action_ptr=0;
    fightFloorLoopValidFightOutPokemon(0,_fightSeqInitSubFightOutPokemon,0,0);
}
void fightSeqPre(void){
    fightFloorLoopValidFightOutPokemon(0,_fightSeqPreSub,0,1);
    fightFloorLoopValidFightOutPokemon(0,fightSeqWazaOutBeforeCheckSub,0,1);
    fight_seq_server_work3_temp=0;
    ServerWork.flags[3]=0;ServerWork.flags[4]=0;
    UserWork[0x16002]=0;UserWork[0x160A1]=0;
    wazaSequenceSysFreeAllWaza();
}
u8 fightSeqOpenMsg(u32 message){
    u8 result=fightMenuOpenMsg(message);
    if(result==1)ServerWork.flags[7]=1;
    return result;
}
void SCA_End(void){
    FightOutPokemon *attacker=(FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11,0);
    FightWaza *attackWaza=fightOutPokemon_GetFightWazaPtr(attacker);
    FightWaza *defenseWaza;
    void *defender=fightTargetGetPtrAsNowFightType(0x12,0);
    defenseWaza=0;
    if(defender)defenseWaza=fightOutPokemon_GetFightWazaPtr(defender);
    fightSeqClearOneSelfTurnCount();
    ServerStatusFlag&=0xF1E892AF;
    ServerWork.flags[3]=0;fight_seq_server_work3_temp=0;ServerWork.flags[4]=0;
    UserWork[0x16002]=0;UserWork[0x160A1]=0;
    fightOutPokemon_SetHitWazaDataId(attacker,0);
    fightOutPokemon_SetHitWazaZokuseiDataId(attacker,9);
    fightWaza_SetDamage(attackWaza,0);
    for(u8 condition=0x3F;condition<=0x47;condition++){
        fightWazaInitJoutaiDataId(attackWaza,condition);
        if(defenseWaza)fightWazaInitJoutaiDataId(defenseWaza,condition);
    }
}
void fightSeqTurnCheck(void){
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
    u8 i;
    for(i=0;i<8;i++)ServerWork.flags[i]=0;
    fightFloorLoopValidFightOutPokemon(0,_fightSeqTurnCheckSubFightOutPokemon,0,0);
    fightFloorInitFightOutPokemonPtrAryFightWazaJoutai(0);
    fightSeqClearOneTurnCount(1);
    fightSeqFloorJoutaiCheck();fightSeqSideJoutaiCheck();fightSeqGetExpCheck();fightSeqSideJoutaiCheck2();
    fightSeqClearOneTurnCount(0);
    ServerStatusFlag&=0xFFFFFDFF;
    ServerStatusFlag&=0xFFF7FFFF;
    ServerStatusFlag&=0xFFBFFFFF;
    ServerStatusFlag&=0xFFEFFFFF;
    UserWork[0x16002]=0;UserWork[0x160A1]=0;
    for(i=0;i<5;i++)ServerWork.flags[i]=0;
    if(fightGetFightResultId()==0){
        u32 turn=fightFloor_GetTurnCount(0)+1;
        if((u16)turn>0xFF)turn=0xFF;
        fightFloor_SetTurnCount(0,turn);
        fightFloor_SetFisstAttackRnd(0,(u32)HSD_Rand());
        wazaSequenceSysFreeAllWaza();
        fightMenuAllFightTrainerCloseStatusMenu(0);
        fightMenuAllFightOutPokemonCloseStatusMenu(0);
        fightMenuCloseMsg();
    }
}
}

extern "C" {
s32 fightSeqGetWazaDamageHikaePokemon(void *trainer,u16 move,void *attacker,void *defender,u8 critical,WSDamageCallback pre,WSDamageCallback post){
    WSOutPokemonSnapshot attackerSave;
    WSPokemonSnapshot defenderSave;
    WSWazaSnapshot wazaSave;
    u8 workSave[8];
    void *oldAttacker=fightFloor_GetAttackPokemonPtr(0);
    u8 *oldSequence=fightSeq_GetWazaSeq();
    s32 oldStatus=ServerStatusFlag;
    u8 *source=ServerWork.flags,*destination=workSave;
    for(s32 i=0;i<8;i++)*destination++=*source++;
    fightOutPokemonBiosCopy(&attackerSave,attacker);
    pokemonBiosCopy(&defenderSave,fightPokemon_GetPokemonBuffPtr(defender));
    fightFloor_SetAttackPokemonPtr(0,attacker);
    FightWaza *waza=fightOutPokemon_GetFightWazaPtr(attacker);
    fightWazaBiosCopy(&wazaSave,waza);
    fightWazaInit(waza);fightWazaCreate(waza,0,move,0,0);
    ServerStatusFlag=0;
    destination=ServerWork.flags;for(s32 i=0;i<8;i++)*destination++=0;
    if(pre)pre(trainer,move,attacker,defender);
    if(critical==1)CriticalCheckHikaePokemon(defender);
    DamageCalcHikaePokemon(defender);
    fightSeqTypeCheckHikaePokemon(defender,1,1,0);
    if(post)post(trainer,move,attacker,defender);
    s32 damage;
    if(fightWazaIsHit(waza)==1)damage=fightWaza_GetDamage(waza);else damage=0;
    fightFloor_SetAttackPokemonPtr(0,oldAttacker);
    fightWazaBiosCopy(waza,&wazaSave);
    fightSeq_JumpWazaSeq(oldSequence);
    ServerStatusFlag=oldStatus;
    destination=ServerWork.flags;source=workSave;for(s32 i=0;i<8;i++)*destination++=*source++;
    fightOutPokemonBiosCopy(attacker,&attackerSave);
    pokemonBiosCopy(fightPokemon_GetPokemonBuffPtr(defender),&defenderSave);
    return damage;
}
s32 fightSeqGetNromalWazaDamage(void *trainer,u16 move,void *attacker,void *defender,u8 critical,u8 loss,WSDamageCallback pre,WSDamageCallback post){
    WSOutPokemonSnapshot attackerSave,defenderSave;
    WSWazaSnapshot wazaSave;
    u8 workSave[8];
    void *oldAttacker=fightFloor_GetAttackPokemonPtr(0);
    void *oldDefender=fightFloor_GetDefensePokemonPtr(0);
    u8 *oldSequence=fightSeq_GetWazaSeq();
    s32 oldStatus=ServerStatusFlag;
    u8 *source=ServerWork.flags,*destination=workSave;
    for(s32 i=0;i<8;i++)*destination++=*source++;
    fightOutPokemonBiosCopy(&attackerSave,attacker);
    fightOutPokemonBiosCopy(&defenderSave,defender);
    fightFloor_SetAttackPokemonPtr(0,attacker);fightFloor_SetDefensePokemonPtr(0,defender);
    FightWaza *waza=fightOutPokemon_GetFightWazaPtr(attacker);
    fightWazaBiosCopy(&wazaSave,waza);fightWazaInit(waza);fightWazaCreate(waza,0,move,0,0);
    ServerStatusFlag=0;destination=ServerWork.flags;for(s32 i=0;i<8;i++)*destination++=0;
    if(pre)pre(trainer,move,attacker,defender);
    if(critical==1)WS_CRITICAL_CHECK();
    WS_DAMAGE_CALC();WS_TYPE_CHECK();if(loss==1)WS_DAMAGE_LOSS();
    if(post)post(trainer,move,attacker,defender);
    s32 damage;
    if(fightWazaIsHit(waza)==1)damage=fightWaza_GetDamage(waza);else damage=0;
    fightFloor_SetAttackPokemonPtr(0,oldAttacker);fightFloor_SetDefensePokemonPtr(0,oldDefender);
    fightWazaBiosCopy(waza,&wazaSave);fightSeq_JumpWazaSeq(oldSequence);ServerStatusFlag=oldStatus;
    destination=ServerWork.flags;source=workSave;for(s32 i=0;i<8;i++)*destination++=*source++;
    fightOutPokemonBiosCopy(attacker,&attackerSave);fightOutPokemonBiosCopy(defender,&defenderSave);
    return damage;
}
}

extern "C" void fightSeqWazaExec(void *action,u16 move){
    u8 fightType=fightFloor_GetFightType(0);
    u16 sequence=wazaDB_GetSeqId(move);
    void *attacker=fightTargetGetPtrAsNowFightType(0x11,0);
    void *attackSide=fightTargetGetPtrAsNowFightType(2,attacker);
    void *defender=fightTargetGetPtrAsNowFightType(0x12,0);
    void *defenseSide=fightTargetGetPtrAsNowFightType(2,defender);
    if(fightOutPokemonCheckFightOut(attacker)!=0 && fightActionCheckValid(fightOutPokemon_GetFightActionBuffPtr(attacker))!=0){
        fightFloor_SetAttackMsgId(0,0);fightFloor_SetCriticakMsgId(0,0);fightFloor_SetWazakoukaMsgId(0,0);
        ServerWork.flags[6]=0;lbl_804EB918=0;fightseq_attack_pokemon_joutai_check_buff=0;
        if(fightOutPokemonIsJoutaiDataId(attacker,0x2A)==1 && move!=0xA5){
            u16 savedMove=fightOutPokemonGetIdBuffJoutaiDataId(attacker,0x2A);
            u16 slot=fightOutPokemonGetBuffJoutaiDataId(attacker,0x2A);
            u16 actualMove=pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(attacker),slot);
            if(savedMove!=actualMove)fightOutPokemonInitJoutaiDataId(attacker,0x2A);
            void *selected=fightSeqSelectDefensePokemonPtr(attacker,actualMove,fightType,0,1,1,-1);
            u32 relative=fightTargetGetTragetPtrToRelativeHostSideFightTargetId(selected,fightType);
            fightOutPokemonCreateFightActionAttackWaza(attacker,0,0x13,0,fight_action_data_waza,actualMove,relative,(s8)slot,1);
            move=actualMove;fightFloor_SetDefensePokemonPtr(0,selected);
            defender=fightTargetGetPtrAsNowFightType(0x12,0);defenseSide=fightTargetGetPtrAsNowFightType(2,defender);
        }
        if(move==0xA5 || wazaCheckDarkWaza(move)==1)ServerStatusFlag|=0x800;
        if(fightSeqTameWazaCheck(move)==1 && fightOutPokemonIsJoutaiDataId(attacker,0x22)==0){
            if(sequence==0x97 && fightFloorGetNowTenkouDataId(0,1)==1){
                void *selected=fightSeqSelectDefensePokemonPtr(attacker,move,fightType,0,0,1,-1);
                if(selected){defender=selected;fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0,selected);defenseSide=fightTargetGetPtrAsNowFightType(2,selected);}
            }
        }else{
            void *selected=fightSeqSelectDefensePokemonPtr(attacker,move,fightType,0,0,1,-1);
            if(selected){defender=selected;fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0,selected);defenseSide=fightTargetGetPtrAsNowFightType(2,selected);}
        }
        if(fightOutPokemonCheckFightOut(defender)==0){
            if(attackSide!=defenseSide || (defender=fightTargetGetPtrAsNowFightType(0xF,attacker),fightOutPokemonCheckFightOut(defender)==0)){
                defender=fightTargetGetPtrAsNowFightType(0xE,defender);
                if(!defender || fightOutPokemonCheckFightOut(defender)==0)return;
            }
            fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0,defender);
            fightTargetGetPtrAsNowFightType(2,defender);
        }
        u16 effect=wazaDB_GetSeqId(move);
        ActionSeqNo=0;
        fightMsgctrlSetValue(0x28,(u32)GSmsgGetGSchar(wazaDB_GetName(move)));
        fightSeq_CallWazaSeqCustom(action,WazaEffectTbl[effect],1);
        wazaSequenceSysFreeAllWaza();fightMenuAllFightTrainerCloseStatusMenu(0);fightMenuAllFightOutPokemonCloseStatusMenu(0);fightMenuCloseMsg();
    }
}

extern "C" s32 EscapeNGCheck(void *pokemon){
    void *enemies[2];
    void *data=fightOutPokemonGetPokemonPtr(pokemon);
    void *encounter=fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(0));
    u16 item=pokemonGetSoubiItemDataId(data);
    u16 ability=pokemonGetTokuseiDataId(data);
    u32 count=(u8)fightFloorGetFightTrainerFightOutPokemonPtrAry(0,fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,pokemon),enemies,0,1);
    u16 itemEffect=pokemonGetSoubiItemSoubiDataId(data);
    fightMsgctrlSetValue(0x29,(u32)GSmsgGetGSchar(itemDB_GetName(item)));
    if(fightEncountDataBiosGetFightKind(encounter)!=0xC){ServerWork.flags[5]=0;return 1;}
    if(itemEffect==0x25 || fightFloorIsNowEncountTuusinTaisen(0)==1 || ability==0x32)return 0;
    for(s32 i=0;i<(s32)count;i++){
        u16 enemyAbility=fightOutPokemon_GetTokuseiDataId(enemies[i]);
        if(enemyAbility==0x17){
            UserWork[0x16003]=i;
            fightMsgctrlSetValue(0x1C,(u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(enemyAbility))));
            fightMsgctrlSetValue(0x1E,(u32)enemies[i]);ServerWork.flags[5]=2;return 2;
        }
        if(enemyAbility==0x47 && ability!=0x1A && fightOutPokemonIsZokuseiDataId(pokemon,2)==0){
            UserWork[0x16003]=i;
            fightMsgctrlSetValue(0x1C,(u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(enemyAbility))));
            fightMsgctrlSetValue(0x1E,(u32)enemies[i]);ServerWork.flags[5]=2;return 2;
        }
        if(enemyAbility==0x2A && fightOutPokemonIsZokuseiDataId(pokemon,8)==1){
            UserWork[0x16003]=i-1;
            fightMsgctrlSetValue(0x1C,(u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(enemyAbility))));
            fightMsgctrlSetValue(0x1E,(u32)enemies[i]);ServerWork.flags[5]=2;return 2;
        }
    }
    if(fightOutPokemonIsJoutaiDataId(pokemon,0xE)==1 || fightOutPokemonIsJoutaiDataId(pokemon,0x16)==1 || fightOutPokemonIsJoutaiDataId(pokemon,0x25)==1){ServerWork.flags[5]=0;return 1;}
    return 0;
}

extern "C" void fightSeqCallExec(void){
    u8 wake=0,calm=0,boost=0;
    u32 message;
    u8 fightType=fightFloor_GetFightType(0);
    void *pokemon=fightFloor_GetAttackPokemonPtr(0);
    void *trainer=fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,pokemon);
    fightSeqSpecificationActionCounterInit(pokemon);
    if(pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(pokemon))==1){
        u8 probability=pokemonGetDarkPokemonCallKakuritu(fightOutPokemonGetPokemonPtr(pokemon));
        if(fightOutPokemonIsJoutaiDataId(pokemon,0x3E)==1){
            if(HSD_Rand()%100<probability){message=0x4FD3;calm=1;if(fightOutPokemonIsJoutaiDataId(pokemon,8)==1)wake=1;}
            else{message=0x4FD4;if(fightOutPokemonIsJoutaiDataId(pokemon,8)==1 && HSD_Rand()%100<((u8)probability>>1))wake=1;}
        }else if(fightOutPokemonIsJoutaiDataId(pokemon,8)==1){message=0x4FD2;wake=1;}
        else boost=1;
    }else if(fightOutPokemonIsJoutaiDataId(pokemon,8)==1){message=0x4FD2;wake=1;}
    else boost=1;
    if(boost==1){
        u8 accuracy=fightOutPokemon_GetAbicntAverage(pokemon);
        if(accuracy<12){
            message=0x4F13;
            GSmsgGetGSchar(wazaGetStatus(0,0xDB,1,0));
            fightMsgctrlSetValue(0xD,(u32)GSmsgGetGSchar(0x4F79));
            fightMsgctrlSetValue(0xE,(u32)GSmsgGetGSchar(0x4F9C));
            fightMsgctrlSetValue(0x41,(u32)GSmsgGetGSchar(0x4F10));
            boost=1;fightOutPokemon_SetAbicntAverage(pokemon,accuracy+1);
        }else{message=0x4F18;boost=0;}
    }
    fightTrainerCallEffect(trainer,0);
    fightOutPokemonDarkPokemonKaijoEffect(pokemon,wake,calm,boost,0,0);
    fightMsgctrlSetValue(0x13,(u32)fightTrainerGetNamePtr(trainer));
    fightMainAllCamera(1,0);fightMenuOpenMsg(0x4FD0);fightMainWaitFrame(0x40);fightMenuCloseMsg();
    fightTrainerCallEffect(trainer,1);
    fightMenuFightOutPokemonOpenStatusMenu(pokemon,fightType,1);
    fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0,pokemon,fightType,0,1);
    fightMenuOpenMsg(0x4FD1);fightTrainerCallEffect(trainer,2);fightMenuCloseMsg();
    if(wake==1){fightOutPokemonInitJoutaiDataId(pokemon,8);fightOutPokemonInitJoutaiDataId(pokemon,0x17);fightSeqCheckSetHensinBuffToMotoPokemon(pokemon,0x7C);}
    if(calm==1){
        fightOutPokemonInitJoutaiDataId(pokemon,0x3E);fightSeqCheckSetHensinBuffToMotoPokemon(pokemon,0xC8);
        if(fightOutPokemonIsGcHeroFightOutPokemon(pokemon)==1 && pokemon_GetPokemonDataId(fightOutPokemonGetPokemonPtr(pokemon))!=0xF9){
            pokemonAddDpFormPokemonDpFilterId(fightOutPokemonGetPokemonPtr(pokemon),0,2);fightSeqCheckSetHensinBuffToMotoPokemon(pokemon,0xC5);
        }
    }
    fightOutPokemonDarkPokemonKaijoEffect(pokemon,wake,calm,boost,message,1);
    fightOutPokemonDarkPokemonKaijoEffect(pokemon,wake,calm,boost,0,2);
    fightMenuCloseMsg();fightMenuFightOutPokemonCloseStatusMenu(pokemon,fightType,0);
    fightTrainerCallEffect(trainer,3);fightOutPokemonDarkPokemonKaijoEffect(pokemon,wake,calm,boost,0,3);
    wazaSequenceSysFreeAllWaza();fightMenuAllFightTrainerCloseStatusMenu(0);fightMenuAllFightOutPokemonCloseStatusMenu(0);fightMenuCloseMsg();
}

extern "C" void fightSeqItemExec(void *action,u16 item){
    u8 fightType=fightFloor_GetFightType(0);
    void *attacker=fightTargetGetPtrAsNowFightType(0x11,0);
    void *defender=fightTargetGetPtrAsNowFightType(0x12,0);
    void *trainer=fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,attacker);
    void *hero=fightTrainer_GetHeroPtr(trainer);
    void *fightItem=fightOutPokemon_GetFightItemPtr(attacker);
    if(fightItem){
        fightItem_GetTargetDataId(fightItem);
        s32 count=fightItem_GetCount(fightItem);
        u8 stocked=fightItem_GetBuff(fightItem)!=0;
        void *param=itemParamGetPtr(itemDataBiosGetItemEffectParam(itemDataBiosGetPtr(item)));
        u8 oldStat=UserWork[0x1601E],oldEffect=UserWork[0x160A4];
        fightSeqSpecificationActionCounterInit(attacker);
        void *sequence;
        if(stocked==1)sequence=ItemNormalTbl[0];
        else if(itemDB_GetKind(item)==1)sequence=ItemBallTbl[item];
        else if(item==0x50||item==0x51)sequence=ItemFightTbl[0];
        else{
            u8 type=fightSeqGetItemType(item,attacker);
            if(type==7)sequence=ItemNormalTbl[0];
            else{
                fightFloor_SetAppointPokemonPtr(0,attacker);ServerWork.flags[5]=0;
                switch(type){
                case 1:
                case 2:break;
                case 3:
                    if(itemParamGetSleepFlag(param)==1 && itemParamGetPoisonFlag(param)==1 && itemParamGetBurnFlag(param)==1 && itemParamGetFreezeFlag(param)==1 && itemParamGetParalyzeFlag(param)==1){
                        if(fightOutPokemonIsJoutaiDataId(attacker,8)==1)ServerWork.flags[5]=5;
                        else if(fightOutPokemonIsJoutaiDataId(attacker,3)==1)ServerWork.flags[5]=4;
                        else if(fightOutPokemonIsJoutaiDataId(attacker,4)==1)ServerWork.flags[5]=4;
                        else if(fightOutPokemonIsJoutaiDataId(attacker,6)==1)ServerWork.flags[5]=3;
                        else if(fightOutPokemonIsJoutaiDataId(attacker,7)==1)ServerWork.flags[5]=2;
                        else if(fightOutPokemonIsJoutaiDataId(attacker,5)==1)ServerWork.flags[5]=1;
                    }else if(itemParamGetSleepFlag(param)==1)ServerWork.flags[5]=5;
                    else if(itemParamGetPoisonFlag(param)==1)ServerWork.flags[5]=4;
                    else if(itemParamGetBurnFlag(param)==1)ServerWork.flags[5]=3;
                    else if(itemParamGetFreezeFlag(param)==1)ServerWork.flags[5]=2;
                    else if(itemParamGetParalyzeFlag(param)==1)ServerWork.flags[5]=1;
                    else if(itemParamGetConfuseFlag(param)==1)ServerWork.flags[5]=0;
                    break;
                case 4:ServerWork.flags[5]=5;break;
                case 5:{
                    ServerWork.flags[5]=4;
                    s32 amount=itemParamGetAttackUp(param);
                    if(amount>0){fightMsgctrlSetValue(0xD,(u32)GSmsgGetGSchar(AbiCntMsgTbl[1]));UserWork[0x1601E]=1;}
                    else if((amount=itemParamGetDefenceUp(param))>0){fightMsgctrlSetValue(0xD,(u32)GSmsgGetGSchar(AbiCntMsgTbl[2]));UserWork[0x1601E]=2;}
                    else if((amount=itemParamGetQuickUp(param))>0){fightMsgctrlSetValue(0xD,(u32)GSmsgGetGSchar(AbiCntMsgTbl[3]));UserWork[0x1601E]=3;}
                    else if((amount=itemParamGetHitUp(param))>0){fightMsgctrlSetValue(0xD,(u32)GSmsgGetGSchar(AbiCntMsgTbl[6]));UserWork[0x1601E]=6;}
                    else if((amount=itemParamGetSpAttackUp(param))>0){fightMsgctrlSetValue(0xD,(u32)GSmsgGetGSchar(AbiCntMsgTbl[4]));UserWork[0x1601E]=4;}
                    if((s16)amount<0){
                        if((s16)amount==1||(s16)amount==-1){fightMsgctrlSetValue(0xE,(u32)GSmsgGetGSchar(0x4F9C));UserWork[0x1601E]=(UserWork[0x1601E]&0xF)+0x15;}
                        else{fightMsgctrlSetValue(0xE,(u32)GSmsgGetGSchar(0x4F11));UserWork[0x160A4]=(UserWork[0x1601E]&0xF)+0x2D;}
                        fightMsgctrlSetValue(0x41,(u32)GSmsgGetGSchar(0x4F12));
                    }else{
                        if((s16)amount==1||(s16)amount==-1){fightMsgctrlSetValue(0xE,(u32)GSmsgGetGSchar(0x4F9C));UserWork[0x160A4]=(UserWork[0x1601E]&0xF)+0xE;}
                        else{fightMsgctrlSetValue(0xE,(u32)GSmsgGetGSchar(0x4F0F));UserWork[0x160A4]=(UserWork[0x1601E]&0xF)+0x26;}
                        fightMsgctrlSetValue(0x41,(u32)GSmsgGetGSchar(0x4F10));
                    }
                    break;
                }
                case 6:break;
                }
                sequence=ItemNormalTbl[type];
            }
        }
        ActionSeqNo=0;
        fightMsgctrlSetValue(0x22,(u32)fightTrainerGetPrefixNamePtr(trainer));
        fightMsgctrlSetValue(0x23,(u32)fightTrainerGetNamePtr(trainer));
        fightMsgctrlSetValue(0x13,(u32)fightTrainerGetNamePtr(trainer));
        fightMsgctrlSetValue(0x29,(u32)GSmsgGetGSchar(itemDB_GetName(item)));
        fightMainAllCamera(1,0);
        if(stocked==0){fightMenuFightOutPokemonOpenStatusMenu(defender,fightType,1);fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0,defender,fightType,0,1);}
        fightSeq_CallWazaSeqCustom(action,sequence,1);
        if(stocked==0 && heroItemDecItemDataId(hero,item,1,count)<0)heroItemDecItemDataId(hero,item,1,-1);
        UserWork[0x1601E]=oldStat;UserWork[0x160A4]=oldEffect;
        wazaSequenceSysFreeAllWaza();fightMenuAllFightTrainerCloseStatusMenu(0);fightMenuAllFightOutPokemonCloseStatusMenu(0);fightMenuCloseMsg();
    }
}
