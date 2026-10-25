#include <game/pxdvs/app/item/itemUse2PokemonPrivate.hpp>

extern "C" {

s16 itemUse2PokemonSimulation(ITEMUSE2POKEMON_LOG1 *arg0, void *arg1, void *arg2, u16 arg3, u8 arg4) {
    void *temp_r3_2;
    void *temp_r3;
    s16 temp_r29;

    temp_r3 = fightFloorGetNowPtr();
    if (temp_r3 == 0) {
        return 0;
    }
    temp_r3_2 = GSmemAlloc(0xE318U);
    memcpy(temp_r3_2, temp_r3, 0xE318U);
    temp_r29 = itemUse2Pokemon(arg0, arg1, arg2, arg3, arg4);
    memcpy(temp_r3, temp_r3_2, 0xE318U);
    GSmemFree(temp_r3_2);
    return temp_r29;
}

static s16 friendXUp__FP7PokemonP12FightPokemonScUsUs(void* pokemon, void* fightPokemon, s8 adjustment, u16 minimum, u16 maximum) {
    s32 value;
    u32 original;
    if (pokemonIsDarkPokemon(pokemon) && pokemonGetDarkPokemonLevel(pokemon) < 3) return 0;
    if (pokemonIsDarkPokemon(pokemon)) original = (u16)pokemon_GetPoolFriend(pokemon);
    else original = (u16)pokemonBiosGetFriend(pokemon);
    if (pokemonIsDarkPokemon(pokemon)) value = (u16)pokemon_GetPoolFriend(pokemon);
    else value = 0;
    s32 total = value + (u16)pokemonBiosGetFriend(pokemon);
    if (total < minimum || total >= maximum) return 0;
    value = adjustment;
    if (value > 0) {
        void* data = itemDataBiosGetPtr(pokemonBiosGetItemDataId(pokemon));
        u16 held;
        if (data == 0) held = 0;
        else held = itemDataBiosGetItemSoubiDataId(data);
        if (held == 0x1b) value = value * 150 / 100;
        if (pokemonBiosGetCatchBallId(pokemon) == 11) value++;
    }
    if (pokemonIsDarkPokemon(pokemon)) value = value * 80 / 100;
    value = original + value;
    if (value > 255) value = 255;
    if (value < 0) value = 0;
    if (pokemonIsDarkPokemon(pokemon)) {
        pokemonSetStatus(pokemon,0,0xc7,0,value);
        void* out;
        if (fightPokemon == 0) out = 0;
        else out = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0,fightPokemon),fightPokemon);
        if (out) fightSeqCheckSetMotoPokemonToHensinBuff(out,0xc7);
    } else {
        pokemonBiosSetFriend(pokemon,(u16)value);
        void* out;
        if (fightPokemon == 0) out = 0;
        else out = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0,fightPokemon),fightPokemon);
        if (out) fightSeqCheckSetMotoPokemonToHensinBuff(out,0x99);
    }
    return (s16)(value-original);
}


static inline void* getFightOutPokemon(void* fightPokemon) {
    void* out;
    if (fightPokemon == 0) out = 0;
    else {
        void* trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon);
        out = fightTrainerCheckFightPokemonFightOut(trainer, fightPokemon);
    }
    return out;
}

static inline void setHensinBuff(void* fightPokemon, u16 id) {
    void* out = getFightOutPokemon(fightPokemon);
    if (out) fightSeqCheckSetMotoPokemonToHensinBuff(out, id);
}

static inline void addLog(ITEMUSE2POKEMON_LOG1* log, s16* count, s32 key, s16 a, s16 b) {
    s16 n = *count;
    if (n < 0x20) {
        log->e[n].key = key;
        log->e[n].a = a;
        log->e[n].b = b;
        *count = n + 1;
    }
}

static inline u8 rankUp(void* fightPokemon, u16 id, u8 amount) {
    void* out = getFightOutPokemon(fightPokemon);
    u8 now;
    u8 value;
    if (out == 0) return 0;
    now = pokemonGetStatus(out, 0, id, 0);
    if (now >= 12) return 0;
    value = now + amount;
    if (value > 12) value = 12;
    pokemonSetStatus(out, 0, id, 0, value);
    setHensinBuff(fightPokemon, 0x99);
    return value - now;
}

static inline u16 levelUp(ITEMUSE2POKEMON_LOG1* log, s16* count, void* pokemon) {
    u8 level;
    u16 oldMaxHp;
    u16 newMaxHp;
    if (pokemonIsDarkPokemon(pokemon)) return 0;
    level = pokemonBiosGetLevel(pokemon);
    if (level >= 100) return 0;
    oldMaxHp = pokemonBiosGetMaxHp(pokemon);
    pokemonBiosSetExp(pokemon, pokemonGrowDataBiosGetExp(pokemonGrowDataBiosGetPtr(pokemonDataBiosGetGrowDataId(pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(pokemon)))), level + 1));
    pokemonResetBasisStatus(pokemon);
    newMaxHp = pokemonBiosGetMaxHp(pokemon);
    addLog(log, count, 8, 0, 0);
    return newMaxHp - oldMaxHp;
}

static inline u16 getEffortTotal(void* pokemon) {
    s32 total = pokemonBiosGetMaxHpEffort(pokemon);
    total += pokemonBiosGetPhyAtkEffort(pokemon);
    total += pokemonBiosGetPhyDefEffort(pokemon);
    total += pokemonBiosGetSpeAtkEffort(pokemon);
    total += pokemonBiosGetSpeDefEffort(pokemon);
    total += pokemonBiosGetNimblenessEffort(pokemon);
    return total;
}

static inline s16 effortUp(void* pokemon, void* fightPokemon, u16 id, u8 amount) {
    u16 total;
    u16 now;
    u16 value;
    u16 sum;
    total = getEffortTotal(pokemon);
    if (total >= 510) return -1;
    now = pokemonGetStatus(pokemon, 0, id, 0);
    if (now >= 100) return 0;
    value = now + amount;
    if (value > 100) value = 100;
    sum = (u16)(total - now) + value;
    if (sum > 510) value -= sum - 510;
    pokemonSetStatus(pokemon, 0, id, 0, value);
    pokemonResetBasisStatus(pokemon);
    setHensinBuff(fightPokemon, id);
    return (u16)(value - now);
}

static inline u8 effortItem(ITEMUSE2POKEMON_LOG1* log, s16* count, void* pokemon, void* fightPokemon, u16 id, u8 amount, s32 key) {
    s16 result = effortUp(pokemon, fightPokemon, id, amount);
    if (result < 0) return 0;
    if (result == 0) return 1;
    addLog(log, count, key, result, 0);
    return 1;
}

static inline u8 ppRecover(void* pokemon, u8 slot, u8 amount) {
    u16 waza;
    u8 max;
    u8 now;
    u8 value;
    waza = pokemonBiosGetPokemonWazaDataId(pokemon, slot);
    if (waza == 0x176) return 0;
    if (wazaCheckDarkWaza(waza)) return 0;
    max = pokemonWazaGetMaxPP(pokemon, slot);
    now = pokemonBiosGetPokemonWazaPp(pokemon, slot);
    if (now >= max) return 0;
    value = now + amount;
    if (value > max) value = max;
    pokemonBiosSetPokemonWazaPp(pokemon, slot, value);
    return value - now;
}

static inline void ppMaxUp(ITEMUSE2POKEMON_LOG1* log, s16* count, void* pokemon, u8 slot) {
    u16 waza = pokemonBiosGetPokemonWazaDataId(pokemon, slot);
    if (waza != 0x176 && !wazaCheckDarkWaza(waza) && pokemonWazaCheckValid(pokemon, slot) && wazaDB_GetPp(waza) >= 5) {
        u8 ppCount = pokemonBiosGetPokemonWazaPpCount(pokemon, slot);
        if (ppCount < 3) {
            u8 oldMax = pokemonWazaGetMaxPP(pokemon, slot);
            u8 diff;
            pokemonBiosSetPokemonWazaPpCount(pokemon, slot, ppCount + 1);
            diff = pokemonWazaGetMaxPP(pokemon, slot) - oldMax;
            pokemonBiosSetPokemonWazaPp(pokemon, slot, pokemonBiosGetPokemonWazaPp(pokemon, slot) + diff);
            addLog(log, count, 0x12, diff, slot);
        }
    }
}

static inline void ppMaxFull(ITEMUSE2POKEMON_LOG1* log, s16* count, void* pokemon, u8 slot) {
    u16 waza = pokemonBiosGetPokemonWazaDataId(pokemon, slot);
    if (waza != 0x176 && !wazaCheckDarkWaza(waza) && wazaDB_GetPp(waza) >= 5 && pokemonBiosGetPokemonWazaPpCount(pokemon, slot) < 3) {
        u8 oldMax = pokemonWazaGetMaxPP(pokemon, slot);
        u8 diff;
        pokemonBiosSetPokemonWazaPpCount(pokemon, slot, 3);
        diff = pokemonWazaGetMaxPP(pokemon, slot) - oldMax;
        if (diff) {
            pokemonBiosSetPokemonWazaPp(pokemon, slot, pokemonBiosGetPokemonWazaPp(pokemon, slot) + diff);
        }
        addLog(log, count, 0x1D, diff, slot);
    }
}

static inline s16 friendUp(ITEMUSE2POKEMON_LOG1* log, s16* count, void* pokemon, void* fightPokemon, s8 amount, u16 minimum, u16 maximum) {
    s16 result;
    if (*count <= 0) return 0;
    result = friendXUp__FP7PokemonP12FightPokemonScUsUs(pokemon, fightPokemon, amount, minimum, maximum);
    if (result == 0) return 0;
    addLog(log, count, 0x1E, result, 0);
    return result;
}

static inline ItemParam* getItemParam(u16 itemId) {
    void* data = itemDataBiosGetPtr(itemId);
    u8 paramId;
    if (data == 0) return 0;
    paramId = itemDataBiosGetItemEffectParam(data);
    if (paramId == 0) return 0;
    return itemParamGetPtr(paramId);
}

static void hpRecover__FP20ITEMUSE2POKEMON_LOG1PsP7PokemonUcbUsP12FightPokemon(ITEMUSE2POKEMON_LOG1 *log, s16 *count, void *pokemon, u8 amount, u8 revive, u16 bonus, void *fightPokemon) {
    u16 hp;
    u16 max;
    u16 value;
    int old;
    u8 revived;
    revived = 0;
    hp = pokemonBiosGetHp(pokemon);
    max = pokemonBiosGetMaxHp(pokemon);
    if (hp >= max) return;
    switch (amount) {
    case 0xFF:
        value = max;
        break;
    case 0xFE:
        value = max / 2;
        if (value == 0) value = 1;
        break;
    case 0xFD:
        value = bonus;
        break;
    default:
        value = amount;
        break;
    }
    if (value == 0) return;
    if (hp == 0) {
        if (revive == 0) return;
        revived = 1;
    } else if (revive != 0) {
        return;
    }
    old = hp;
    hp = hp + value;
    if (hp > max) hp = max;
    pokemonBiosSetHp(pokemon, hp);
    setHensinBuff(fightPokemon, 0x83);
    if (revived) addLog(log, count, 0x16, 0, 0);
    {
        u16 recovered = hp - old;
        addLog(log, count, 0x15, recovered, 0);
    }
}

s16 itemUse2Pokemon(ITEMUSE2POKEMON_LOG1 *log, void *pokemon, void *fightPokemon, u16 itemId, u8 slot) {
    static u32 origRamSeedParam[2] = { 0, 0 };
    ItemParam seedParam;
    EvolutionInfo evoInfo;
    s16 count;
    u16 evoId;
    ItemParam *param;
    u16 hpBonus;
    u8 amount;
    s8 friendAmount;
    s16 friendResult;
    void *out;
    u8 poison;
    u8 fightOutCured;

    hpBonus = 0;
    count = 0;
    if (itemId != 0xAF) {
        param = getItemParam(itemId);
    } else {
        itemParamConvertOrigFormat(&seedParam, origRamSeedParam);
        param = &seedParam;
    }
    if (param == 0) {
        return 0;
    }
    if (fightPokemon != 0) {
        pokemon = fightPokemon == 0 ? 0 : fightPokemonGetPokemonPtr(fightPokemon);
    }
    if (itemParamGetMeromeroFlag(param)) {
        out = getFightOutPokemon(fightPokemon);
        if (out && fightOutPokemonIsJoutaiDataId(out, 0xA)) {
            fightOutPokemonInitJoutaiDataId(out, 0xA);
            setHensinBuff(fightPokemon, 0x7C);
            addLog(log, &count, 0, 0, 0);
        }
    }
    if (itemParamGetCriticalFlag(param)) {
        out = getFightOutPokemon(fightPokemon);
        if (out && fightOutPokemonCheckWriteJoutaiDataId(out, 0xF) == 2) {
            fightOutPokemonWriteJoutaiDataId(out, 0xF, 0);
            setHensinBuff(fightPokemon, 0x7C);
            setHensinBuff(fightPokemon, 0x99);
            addLog(log, &count, 1, 0, 0);
        }
    }
    if ((amount = itemParamGetAttackUp(param))) {
        u8 up = rankUp(fightPokemon, 0xE6, amount);
        if (up) addLog(log, &count, 2, up, 0);
    }
    if ((amount = itemParamGetDefenceUp(param))) {
        u8 up = rankUp(fightPokemon, 0xE7, amount);
        if (up) addLog(log, &count, 3, up, 0);
    }
    if ((amount = itemParamGetQuickUp(param))) {
        u8 up = rankUp(fightPokemon, 0xEA, amount);
        if (up) addLog(log, &count, 4, up, 0);
    }
    if ((amount = itemParamGetHitUp(param))) {
        u8 up = rankUp(fightPokemon, 0xEB, amount);
        if (up) addLog(log, &count, 5, up, 0);
    }
    if ((amount = itemParamGetSpAttackUp(param))) {
        u8 up = rankUp(fightPokemon, 0xE8, amount);
        if (up) addLog(log, &count, 6, up, 0);
    }
    if (itemParamGetGuardFlag(param)) {
        out = getFightOutPokemon(fightPokemon);
        if (out) {
            void* side = fightTargetGetPtrAsNowFightType(2, out);
            if (fightSideCheckWriteJoutaiDataId(side, 0x4C) == 2) {
                fightSideWriteJoutaiDataId(side, 0x4C, 0);
                setHensinBuff(fightPokemon, 0x99);
                addLog(log, &count, 7, 5, 0);
            }
        }
    }
    if (itemParamGetLevelUpFlag(param)) {
        hpBonus = levelUp(log, &count, pokemon);
    }
    if (itemParamGetSleepFlag(param)) {
        fightOutCured = 0;
        if (pokemonIsJoutaiDataId(pokemon, 8)) {
            pokemonInitJoutaiDataId(pokemon, 8);
            out = getFightOutPokemon(fightPokemon);
            if (out) {
                fightOutPokemonInitJoutaiDataId(out, 0x17);
                fightOutCured = 1;
            }
            setHensinBuff(fightPokemon, 0x7C);
            addLog(log, &count, 9, 0, 0);
            if (fightOutCured) addLog(log, &count, 0xA, 0, 0);
        }
    }
    if (itemParamGetPoisonFlag(param)) {
        poison = 0;
        fightOutCured = 0;
        if (pokemonIsJoutaiDataId(pokemon, 3)) {
            pokemonInitJoutaiDataId(pokemon, 3);
            poison = 1;
        }
        if (pokemonIsJoutaiDataId(pokemon, 4)) {
            pokemonInitJoutaiDataId(pokemon, 4);
            fightOutCured = 1;
        }
        setHensinBuff(fightPokemon, 0x7C);
        if (poison) addLog(log, &count, 0xB, 0, 0);
        if (fightOutCured) addLog(log, &count, 0xC, 0, 0);
    }
    if (itemParamGetBurnFlag(param) && pokemonIsJoutaiDataId(pokemon, 6)) {
        pokemonInitJoutaiDataId(pokemon, 6);
        setHensinBuff(fightPokemon, 0x7C);
        addLog(log, &count, 0xE, 0, 0);
    }
    if (itemParamGetFreezeFlag(param) && pokemonIsJoutaiDataId(pokemon, 7)) {
        pokemonInitJoutaiDataId(pokemon, 7);
        setHensinBuff(fightPokemon, 0x7C);
        addLog(log, &count, 0xF, 0, 0);
    }
    if (itemParamGetParalyzeFlag(param) && pokemonIsJoutaiDataId(pokemon, 5)) {
        pokemonInitJoutaiDataId(pokemon, 5);
        setHensinBuff(fightPokemon, 0x7C);
        addLog(log, &count, 0x10, 0, 0);
    }
    if (itemParamGetConfuseFlag(param)) {
        out = getFightOutPokemon(fightPokemon);
        if (out && fightOutPokemonIsJoutaiDataId(out, 9)) {
            fightOutPokemonInitJoutaiDataId(out, 9);
            setHensinBuff(fightPokemon, 0x7C);
            addLog(log, &count, 0x11, 0, 0);
        }
    }
    if (itemParamGetPPMaxUpFlag(param)) {
        ppMaxUp(log, &count, pokemon, slot);
    }
    if ((amount = itemParamGetHPEffortUp(param))) {
        u8 ok;
        if (pokemonBiosGetPokemonDataId(pokemon) == 0x12F) {
            ok = 1;
        } else {
            ok = effortItem(log, &count, pokemon, fightPokemon, 0x8D, amount, 0x13);
        }
        if (!ok) return 0;
    }
    if ((amount = itemParamGetAttackEffortUp(param))) {
        if (!effortItem(log, &count, pokemon, fightPokemon, 0x8E, amount, 0x14)) return 0;
    }
    if ((amount = itemParamGetHPUp(param))) {
        u8 revive = itemParamGetReviveFlag(param);
        hpRecover__FP20ITEMUSE2POKEMON_LOG1PsP7PokemonUcbUsP12FightPokemon(log, &count, pokemon, amount, revive, hpBonus, fightPokemon);
    }
    if ((amount = itemParamGetPPUp(param))) {
        u8 select;
        void* target;
        if (itemParamGetPPSelectFlag(param)) select = slot;
        else select = 0xFF;
        target = pokemon;
        if (pokemonIsJoutaiDataId(pokemon, 0x10) || pokemonIsJoutaiDataId(pokemon, 0x31)) {
            target = fightPokemonBiosGetMotoPokemonPtr(fightPokemon);
        }
        if (select != 0xFF) {
            u8 up = ppRecover(target, select, amount);
            if (up) addLog(log, &count, 0x17, up, select);
        } else {
            u8 i;
            for (i = 0; i < 4; i++) {
                u8 up = ppRecover(target, i, amount);
                if (up) addLog(log, &count, 0x17, up, i);
            }
        }
    }
    if (itemParamGetEvolutionFlag(param) && !pokemonIsDarkPokemon(pokemon)) {
        u16 evo = pokemonEvolutionCheck(pokemon, 1, itemId, &evoId, &evoInfo);
        if (evo || evoId) addLog(log, &count, 0x18, evo, evoId);
    }
    if ((amount = itemParamGetDefenceEffortUp(param))) {
        if (!effortItem(log, &count, pokemon, fightPokemon, 0x8F, amount, 0x19)) return 0;
    }
    if ((amount = itemParamGetQuickEffortUp(param))) {
        if (!effortItem(log, &count, pokemon, fightPokemon, 0x92, amount, 0x1A)) return 0;
    }
    if ((amount = itemParamGetSpDefenceEffortUp(param))) {
        if (!effortItem(log, &count, pokemon, fightPokemon, 0x91, amount, 0x1B)) return 0;
    }
    if ((amount = itemParamGetSpAttackEffortUp(param))) {
        if (!effortItem(log, &count, pokemon, fightPokemon, 0x90, amount, 0x1C)) return 0;
    }
    if (itemParamGetPPMaxFullFlag(param)) {
        ppMaxFull(log, &count, pokemon, slot);
    }
    friendResult = 0;
    if ((friendAmount = itemParamGetFriend1Up(param))) {
        friendResult = friendUp(log, &count, pokemon, fightPokemon, friendAmount, 0, 100);
    }
    if (friendResult == 0 && (friendAmount = itemParamGetFriend2Up(param))) {
        friendResult = friendUp(log, &count, pokemon, fightPokemon, friendAmount, 100, 200);
    }
    if (friendResult == 0 && (friendAmount = itemParamGetFriend3Up(param))) {
        friendUp(log, &count, pokemon, fightPokemon, friendAmount, 200, 0xFFFF);
    }
    return count;
}
}
