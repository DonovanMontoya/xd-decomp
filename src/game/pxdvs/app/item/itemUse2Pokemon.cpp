#include <dolphin/types.h>

class Pokemon;
class FightPokemon;
class FightOutPokemon;
class FightTrainer;
class FIGHT_FLOOR;
class FIGHT_SIDE;
class PokemonData;
class PokemonGrowDataBios;

struct ITEMUSE2POKEMON_LOG1 {
    s32 type;
    u16 value;
    u16 extra;
};

extern "C" {
FIGHT_FLOOR* fightFloorGetNowPtr(void);
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void* memcpy(void* dst, const void* src, u32 n);
FightTrainer* fightFloorGetFightPokemonPtrToFightTrainerPtr(FIGHT_FLOOR* floor, FightPokemon* pokemon);
FightOutPokemon* fightTrainerCheckFightPokemonFightOut(FightTrainer* trainer, FightPokemon* fp);
void fightSeqCheckSetMotoPokemonToHensinBuff(FightOutPokemon* p, u16 id);
u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon* fop, u16 id);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon* fop, u16 id);
void fightOutPokemonWriteJoutaiDataId(FightOutPokemon* fop, u16 id, u32 value);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon* fp);
u32 fightPokemonBiosGetMotoPokemonPtr(FightPokemon* p);
u8 fightSideCheckWriteJoutaiDataId(FIGHT_SIDE* side, u16 id);
void fightSideWriteJoutaiDataId(FIGHT_SIDE* side, u16 id, u16 value);
void* fightTargetGetPtrAsNowFightType(u16 slotType, void* ptr);
u32 itemDataBiosGetItemEffectParam(u8* p);
u32 itemDataBiosGetItemSoubiDataId(u8* p);
u8* itemDataBiosGetPtr(u16 index);
void itemParamConvertOrigFormat(u8* dst, u8* src);
u8* itemParamGetPtr(u32 idx);
u8 itemParamGetMeromeroFlag(u8* p);
u8 itemParamGetCriticalFlag(u8* p);
u8 itemParamGetAttackUp(u8* p);
u8 itemParamGetDefenceUp(u8* p);
u8 itemParamGetQuickUp(u8* p);
u8 itemParamGetHitUp(u8* p);
u8 itemParamGetSpAttackUp(u8* p);
u8 itemParamGetGuardFlag(u8* p);
u8 itemParamGetLevelUpFlag(u8* p);
u8 itemParamGetSleepFlag(u8* p);
u8 itemParamGetPoisonFlag(u8* p);
u8 itemParamGetBurnFlag(u8* p);
u8 itemParamGetFreezeFlag(u8* p);
u8 itemParamGetParalyzeFlag(u8* p);
u8 itemParamGetConfuseFlag(u8* p);
u8 itemParamGetPPMaxUpFlag(u8* p);
u8 itemParamGetPPMaxFullFlag(u8* p);
u8 itemParamGetHPEffortUp(u8* p);
u8 itemParamGetAttackEffortUp(u8* p);
u8 itemParamGetDefenceEffortUp(u8* p);
u8 itemParamGetQuickEffortUp(u8* p);
u8 itemParamGetSpDefenceEffortUp(u8* p);
u8 itemParamGetSpAttackEffortUp(u8* p);
u8 itemParamGetHPUp(u8* p);
bool itemParamGetReviveFlag(u8* p);
u8 itemParamGetPPUp(u8* p);
u8 itemParamGetPPSelectFlag(u8* p);
u8 itemParamGetEvolutionFlag(u8* p);
s8 itemParamGetFriend1Up(u8* p);
s8 itemParamGetFriend2Up(u8* p);
s8 itemParamGetFriend3Up(u8* p);
u8 pokemonBiosGetCatchBallId(Pokemon* poke);
u16 pokemonBiosGetFriend(Pokemon* poke);
u16 pokemonBiosGetHp(Pokemon* poke);
u16 pokemonBiosGetItemDataId(Pokemon* poke);
u8 pokemonBiosGetLevel(Pokemon* poke);
u16 pokemonBiosGetMaxHp(Pokemon* poke);
u16 pokemonBiosGetMaxHpEffort(Pokemon* poke);
u16 pokemonBiosGetNimblenessEffort(Pokemon* poke);
u16 pokemonBiosGetPhyAtkEffort(Pokemon* poke);
u16 pokemonBiosGetPhyDefEffort(Pokemon* poke);
u16 pokemonBiosGetPokemonDataId(Pokemon* poke);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u32 wazaNum);
u8 pokemonBiosGetPokemonWazaPp(Pokemon* poke, u32 wazaNum);
u8 pokemonBiosGetPokemonWazaPpCount(Pokemon* poke, u32 wazaNum);
u16 pokemonBiosGetSpeAtkEffort(Pokemon* poke);
u16 pokemonBiosGetSpeDefEffort(Pokemon* poke);
void pokemonBiosSetExp(Pokemon* poke, u32 data);
void pokemonBiosSetFriend(Pokemon* poke, u16 data);
void pokemonBiosSetHp(Pokemon* poke, u16 data);
void pokemonBiosSetPokemonWazaPp(Pokemon* poke, u32 wazaNum, u8 data);
void pokemonBiosSetPokemonWazaPpCount(Pokemon* poke, u32 wazaNum, u8 count);
u8 pokemonDataBiosGetGrowDataId(PokemonData* pdata);
PokemonData* pokemonDataBiosGetPtr(u16 pokeNum);
u8 pokemonGetDarkPokemonLevel(Pokemon* pokemon);
u32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index);
int pokemonGrowDataBiosGetExp(PokemonGrowDataBios* data, u8 level);
PokemonGrowDataBios* pokemonGrowDataBiosGetPtr(u8 index);
void pokemonInitJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
u8 pokemonIsDarkPokemon(Pokemon* pokemon);
bool pokemonIsJoutaiDataId(Pokemon* pokemon, u16 joutaiDataId);
void pokemonResetBasisStatus(Pokemon* pokemon);
void pokemonSetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index, u32 value);
bool pokemonWazaCheckValid(Pokemon* pokemon, u32 wazaNum);
u8 pokemonWazaGetMaxPP(Pokemon* pokemon, u32 wazaNum);
u32 pokemon_GetPoolFriend(Pokemon* poke);
u8 wazaCheckDarkWaza(u16 wazaID);
u8 wazaDB_GetPp(u16 id);
}

struct POKEMON_EVOLUTION_INFO {
    u8 kind;
    u8 reserved;
    u16 parameter;
};
extern "C" u16 pokemonEvolutionCheck(Pokemon*, s32, u16, u16*, POKEMON_EVOLUTION_INFO*);

extern "C" s32 itemUse2Pokemon(ITEMUSE2POKEMON_LOG1* log, Pokemon* pokemon, FightPokemon* fightPokemon, u16 itemDataId, u8 moveSlot);

extern "C" {

s32 itemUse2PokemonSimulation(ITEMUSE2POKEMON_LOG1* a, Pokemon* b, FightPokemon* c, u16 d, u8 e) {
    void* saved;
    FIGHT_FLOOR* floor;
    s32 result;
    floor = fightFloorGetNowPtr();
    if (floor == 0) {
        return 0;
    }
    saved = GSmemAlloc(0xE318);
    memcpy(saved, floor, 0xE318);
    result = itemUse2Pokemon(a, b, c, d, e);
    memcpy(floor, saved, 0xE318);
    GSmemFree(saved);
    return result;
}

}

static s16 friendXUp(Pokemon* pokemon, FightPokemon* fightPokemon, s8 change, u16 lower, u16 upper) {
    FightOutPokemon* trainer;
    s32 adjusted;
    s32 newFriend;
    s32 oldFriend;
    s32 effective;

    if (pokemonIsDarkPokemon(pokemon) && pokemonGetDarkPokemonLevel(pokemon) < 3) {
        return 0;
    }

    if (pokemonIsDarkPokemon(pokemon)) {
        oldFriend = (u16)pokemon_GetPoolFriend(pokemon);
    } else {
        oldFriend = pokemonBiosGetFriend(pokemon);
    }
    if (pokemonIsDarkPokemon(pokemon)) {
        effective = (u16)pokemon_GetPoolFriend(pokemon);
    } else {
        effective = 0;
    }
    effective += pokemonBiosGetFriend(pokemon);
    if (effective < lower || effective >= upper) {
        return 0;
    }

    adjusted = change;
    if (adjusted > 0) {
        u8* item = itemDataBiosGetPtr(pokemonBiosGetItemDataId(pokemon));
        if ((u16)(item == 0 ? 0 : itemDataBiosGetItemSoubiDataId(item)) == 0x1B) {
            adjusted = adjusted * 150 / 100;
        }
        if (pokemonBiosGetCatchBallId(pokemon) == 0xB) {
            adjusted++;
        }
    }
    if (pokemonIsDarkPokemon(pokemon)) {
        adjusted = adjusted * 80 / 100;
    }

    newFriend = oldFriend + adjusted;
    if (newFriend > 0xFF) {
        newFriend = 0xFF;
    }
    if (newFriend < 0) {
        newFriend = 0;
    }

    if (pokemonIsDarkPokemon(pokemon)) {
        pokemonSetStatus(pokemon, 0, 0xC7, 0, newFriend);
        if (fightPokemon == 0) {
            trainer = 0;
        } else {
            trainer = fightTrainerCheckFightPokemonFightOut(
                fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon), fightPokemon);
        }
        if (trainer != 0) {
            fightSeqCheckSetMotoPokemonToHensinBuff(trainer, 0xC7);
        }
    } else {
        pokemonBiosSetFriend(pokemon, newFriend);
        if (fightPokemon == 0) {
            trainer = 0;
        } else {
            trainer = fightTrainerCheckFightPokemonFightOut(
                fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon), fightPokemon);
        }
        if (trainer != 0) {
            fightSeqCheckSetMotoPokemonToHensinBuff(trainer, 0x99);
        }
    }
    return newFriend - oldFriend;
}

static inline void peopleItemUseLogAdd(ITEMUSE2POKEMON_LOG1* log, s16* logCount, s32 type, u16 value) {
    s16 count = *logCount;

    if (count < 0x20) {
        log[count].type = type;
        log[count].value = value;
        log[count].extra = 0;
        *logCount = count + 1;
    }
}

static void hpRecover(ITEMUSE2POKEMON_LOG1* log, s16* logCount, Pokemon* pokemon, u8 recovery, bool revive,
                      u16 amount, FightPokemon* fightPokemon) {
    u16 oldHp;
    u16 maxHp;
    u16 newHp;
    u16 recoveryAmount;
    u8 revived;
    FightOutPokemon* trainer;
    u16 value;

    revived = 0;
    oldHp = pokemonBiosGetHp(pokemon);
    maxHp = pokemonBiosGetMaxHp(pokemon);
    if (oldHp >= maxHp) {
        return;
    }

    switch (recovery) {
    case 0xFF:
        recoveryAmount = maxHp;
        break;
    case 0xFE:
        recoveryAmount = maxHp / 2;
        if (recoveryAmount == 0) {
            recoveryAmount = 1;
        }
        break;
    case 0xFD:
        recoveryAmount = amount;
        break;
    default:
        recoveryAmount = recovery;
        break;
    }
    if (recoveryAmount == 0) {
        return;
    }

    if (oldHp == 0) {
        if (revive == 0) {
            return;
        }
        revived = 1;
    } else if (revive != 0) {
        return;
    }

    newHp = oldHp + recoveryAmount;
    if (newHp > maxHp) {
        newHp = maxHp;
    }
    pokemonBiosSetHp(pokemon, newHp);

    if (fightPokemon == 0) {
        trainer = 0;
    } else {
        trainer = fightTrainerCheckFightPokemonFightOut(
            fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon), fightPokemon);
    }
    if (trainer != 0) {
        fightSeqCheckSetMotoPokemonToHensinBuff(trainer, 0x83);
    }

    if (revived != 0) {
        peopleItemUseLogAdd(log, logCount, 0x16, 0);
    }
    value = newHp - oldHp;
    peopleItemUseLogAdd(log, logCount, 0x15, value);
}

static inline u8* itemUseGetParam(u16 itemDataId) {
    u8* item;
    u32 effect;

    item = itemDataBiosGetPtr(itemDataId);
    if (item == 0) {
        return 0;
    }
    effect = itemDataBiosGetItemEffectParam(item);
    if ((u8)effect == 0) {
        return 0;
    }
    return itemParamGetPtr(effect);
}

static inline Pokemon* itemUseGetPokemon(FightPokemon* fightPokemon) {
    if (fightPokemon == 0) {
        return 0;
    }
    return fightPokemonGetPokemonPtr(fightPokemon);
}

static inline FightOutPokemon* itemUseGetFightOut(FightPokemon* fightPokemon) {
    FightTrainer* trainer;

    if (fightPokemon == 0) {
        return 0;
    }
    trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon);
    return fightTrainerCheckFightPokemonFightOut(trainer, fightPokemon);
}

static inline void itemUseNotify(FightPokemon* fightPokemon, s32 id) {
    FightOutPokemon* fightOut;

    fightOut = itemUseGetFightOut(fightPokemon);
    if (fightOut != 0) {
        fightSeqCheckSetMotoPokemonToHensinBuff(fightOut, id);
    }
}

static inline void itemUseAddLog(ITEMUSE2POKEMON_LOG1* log, s16* count, s32 type, s16 value, s16 extra) {
    s16 n;

    n = *count;
    if (n < 0x20) {
        log[n].type = type;
        log[n].value = value;
        log[n].extra = extra;
        *count = n + 1;
    }
}

#define ITEMUSE_ADD_LOG(log, count, logType, logValue, logExtra) \
    do {                                                         \
        s16 n_ = *(count);                                       \
        if (n_ < 0x20) {                                         \
            (log)[n_].type = (logType);                          \
            (log)[n_].value = (logValue);                        \
            (log)[n_].extra = (logExtra);                        \
            *(count) = n_ + 1;                                   \
        }                                                        \
    } while (0)

static inline u8 itemUseStatUp(FightPokemon* fightPokemon, u32 statusId, u8 boost) {
    u8 oldStage;
    u8 newStage;
    FightOutPokemon* fightOut;

    fightOut = itemUseGetFightOut(fightPokemon);
    if (fightOut == 0) {
        return 0;
    }
    oldStage = pokemonGetStatus(fightOut, 0, statusId, 0);
    if (oldStage >= 0xC) {
        return 0;
    }
    newStage = oldStage + boost;
    if (newStage > 0xC) {
        newStage = 0xC;
    }
    pokemonSetStatus(fightOut, 0, statusId, 0, newStage);
    itemUseNotify(fightPokemon, 0x99);
    return newStage - oldStage;
}

static inline void itemUseStatUpLog(ITEMUSE2POKEMON_LOG1* log, s16* count, FightPokemon* fightPokemon, u32 statusId,
                                    u8 boost, s32 type) {
    u8 delta;

    if ((delta = itemUseStatUp(fightPokemon, statusId, boost)) != 0) {
        itemUseAddLog(log, count, type, delta, 0);
    }
}

static inline u16 itemUseEffortTotal(Pokemon* pokemon) {
    u16 total;

    total = pokemonBiosGetMaxHpEffort(pokemon);
    total += pokemonBiosGetPhyAtkEffort(pokemon);
    total += pokemonBiosGetPhyDefEffort(pokemon);
    total += pokemonBiosGetSpeAtkEffort(pokemon);
    total += pokemonBiosGetSpeDefEffort(pokemon);
    total += pokemonBiosGetNimblenessEffort(pokemon);
    return total;
}

static inline s16 itemUseEffortUp(Pokemon* pokemon, FightPokemon* fightPokemon, u32 statusId, u8 boost) {
    u16 total;
    u16 oldEffort;
    u16 newEffort;
    u16 newTotal;

    total = itemUseEffortTotal(pokemon);
    if (total >= 0x1FE) {
        return -1;
    }
    oldEffort = pokemonGetStatus(pokemon, 0, statusId, 0);
    if (oldEffort >= 0x64) {
        return 0;
    }
    newEffort = oldEffort + boost;
    if (newEffort > 0x64) {
        newEffort = 0x64;
    }
    newTotal = total - oldEffort;
    newTotal = newTotal + newEffort;
    if (newTotal > 0x1FE) {
        newEffort -= newTotal - 0x1FE;
    }
    pokemonSetStatus(pokemon, 0, statusId, 0, newEffort);
    pokemonResetBasisStatus(pokemon);
    itemUseNotify(fightPokemon, statusId);
    return (u16)(newEffort - oldEffort);
}

static inline u8 itemUseEffortUpLog(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon,
                                    FightPokemon* fightPokemon, u32 statusId, u8 boost, s32 type) {
    s16 gained;

    gained = itemUseEffortUp(pokemon, fightPokemon, statusId, boost);
    if (gained < 0) {
        return false;
    }
    if (gained == 0) {
        return true;
    }
    itemUseAddLog(log, count, type, gained, 0);
    return true;
}

static inline u8 itemUsePPUp(Pokemon* pokemon, s32 slot, u8 boost) {
    u16 wazaDataId;
    u8 maxPp;
    u8 oldPp;
    u8 newPp;

    wazaDataId = pokemonBiosGetPokemonWazaDataId(pokemon, slot);
    if (wazaDataId == 0x176) {
        return 0;
    }
    if (wazaCheckDarkWaza(wazaDataId)) {
        return 0;
    }
    maxPp = pokemonWazaGetMaxPP(pokemon, slot);
    oldPp = pokemonBiosGetPokemonWazaPp(pokemon, slot);
    if (oldPp >= maxPp) {
        return 0;
    }
    newPp = oldPp + boost;
    if (newPp > maxPp) {
        newPp = maxPp;
    }
    pokemonBiosSetPokemonWazaPp(pokemon, slot, newPp);
    return newPp - oldPp;
}

static inline void itemUsePPRecover(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon,
                                    FightPokemon* fightPokemon, u8* itemParam, u8 moveSlot, u8 boost) {
    Pokemon* target;
    u8 slot;
    u8 i;
    u8 delta;

    if (itemParamGetPPSelectFlag(itemParam)) {
        slot = moveSlot;
    } else {
        slot = 0xFF;
    }
    target = pokemon;
    if (pokemonIsJoutaiDataId(pokemon, 0x10) || pokemonIsJoutaiDataId(pokemon, 0x31)) {
        target = (Pokemon*)fightPokemonBiosGetMotoPokemonPtr(fightPokemon);
    }
    if (slot != 0xFF) {
        if ((delta = itemUsePPUp(target, slot, boost)) != 0) {
            ITEMUSE_ADD_LOG(log, count, 0x17, delta, slot);
        }
    } else {
        for (i = 0; i < 4; i++) {
            if ((delta = itemUsePPUp(target, i, boost)) != 0) {
                ITEMUSE_ADD_LOG(log, count, 0x17, delta, i);
            }
        }
    }
}

static inline void itemUsePPMaxUp(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon, u8 slot) {
    u16 wazaDataId;
    u8 ppCount;
    u8 maxPp;
    u8 delta;
    u8 pp;

    wazaDataId = pokemonBiosGetPokemonWazaDataId(pokemon, slot);
    if (wazaDataId != 0x176 && !wazaCheckDarkWaza(wazaDataId) && pokemonWazaCheckValid(pokemon, slot) &&
        wazaDB_GetPp(wazaDataId) >= 5) {
        ppCount = pokemonBiosGetPokemonWazaPpCount(pokemon, slot);
        if (ppCount < 3) {
            maxPp = pokemonWazaGetMaxPP(pokemon, slot);
            pokemonBiosSetPokemonWazaPpCount(pokemon, slot, ppCount + 1);
            delta = pokemonWazaGetMaxPP(pokemon, slot) - maxPp;
            pp = pokemonBiosGetPokemonWazaPp(pokemon, slot);
            pp += delta;
            pokemonBiosSetPokemonWazaPp(pokemon, slot, pp);
            itemUseAddLog(log, count, 0x12, delta, slot);
        }
    }
}

static inline void itemUsePPMaxFull(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon, u8 slot) {
    u16 wazaDataId;
    u8 maxPp;
    u8 delta;
    u8 pp;

    wazaDataId = pokemonBiosGetPokemonWazaDataId(pokemon, slot);
    if (wazaDataId != 0x176 && !wazaCheckDarkWaza(wazaDataId) && wazaDB_GetPp(wazaDataId) >= 5 &&
        pokemonBiosGetPokemonWazaPpCount(pokemon, slot) < 3) {
        maxPp = pokemonWazaGetMaxPP(pokemon, slot);
        pokemonBiosSetPokemonWazaPpCount(pokemon, slot, 3);
        delta = pokemonWazaGetMaxPP(pokemon, slot) - maxPp;
        if (delta != 0) {
            pp = pokemonBiosGetPokemonWazaPp(pokemon, slot);
            pp += delta;
            pokemonBiosSetPokemonWazaPp(pokemon, slot, pp);
        }
        itemUseAddLog(log, count, 0x1D, delta, slot);
    }
}

static inline void itemUseCureSleep(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon,
                                    FightPokemon* fightPokemon) {
    u8 wokeUp = 0;
    FightOutPokemon* fightOut;

    if (pokemonIsJoutaiDataId(pokemon, 8)) {
        pokemonInitJoutaiDataId(pokemon, 8);
        fightOut = itemUseGetFightOut(fightPokemon);
        if (fightOut != 0) {
            fightOutPokemonInitJoutaiDataId(fightOut, 0x17);
            wokeUp = 1;
        }
        itemUseNotify(fightPokemon, 0x7C);
        itemUseAddLog(log, count, 9, 0, 0);
        if (wokeUp) {
            itemUseAddLog(log, count, 0xA, 0, 0);
        }
    }
}

static inline void itemUseCurePoison(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon,
                                     FightPokemon* fightPokemon) {
    u8 poisonCleared = 0;
    u8 badPoisonCleared = 0;

    if (pokemonIsJoutaiDataId(pokemon, 3)) {
        pokemonInitJoutaiDataId(pokemon, 3);
        poisonCleared = 1;
    }
    if (pokemonIsJoutaiDataId(pokemon, 4)) {
        pokemonInitJoutaiDataId(pokemon, 4);
        badPoisonCleared = 1;
    }
    itemUseNotify(fightPokemon, 0x7C);
    if (poisonCleared) {
        itemUseAddLog(log, count, 0xB, 0, 0);
    }
    if (badPoisonCleared) {
        itemUseAddLog(log, count, 0xC, 0, 0);
    }
}

static inline void itemUseGuardSpec(ITEMUSE2POKEMON_LOG1* log, s16* count, FightPokemon* fightPokemon) {
    FightOutPokemon* fightOut;
    FIGHT_SIDE* side;

    fightOut = itemUseGetFightOut(fightPokemon);
    if (fightOut != 0) {
        side = (FIGHT_SIDE*)fightTargetGetPtrAsNowFightType(2, fightOut);
        if (fightSideCheckWriteJoutaiDataId(side, 0x4C) == 2) {
            fightSideWriteJoutaiDataId(side, 0x4C, 0);
            itemUseNotify(fightPokemon, 0x99);
            itemUseAddLog(log, count, 7, 5, 0);
        }
    }
}

static inline void itemUseEvolve(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon, u16 itemDataId,
                                 POKEMON_EVOLUTION_INFO* evolutionMode) {
    u16 evolutionSpecies;
    u16 evolution;

    evolution = pokemonEvolutionCheck(pokemon, 1, itemDataId, &evolutionSpecies, evolutionMode);
    if (evolution != 0 || evolutionSpecies != 0) {
        itemUseAddLog(log, count, 0x18, evolution, evolutionSpecies);
    }
}

static inline u16 itemUseLevelUp(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon) {
    u8 level;
    u16 oldMaxHp;
    u16 newMaxHp;

    if (pokemonIsDarkPokemon(pokemon)) {
        return 0;
    }
    level = pokemonBiosGetLevel(pokemon);
    if (level >= 100) {
        return 0;
    }
    oldMaxHp = pokemonBiosGetMaxHp(pokemon);
    pokemonBiosSetExp(pokemon, pokemonGrowDataBiosGetExp(
                                   pokemonGrowDataBiosGetPtr(pokemonDataBiosGetGrowDataId(
                                       pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(pokemon)))),
                                   level + 1));
    pokemonResetBasisStatus(pokemon);
    newMaxHp = pokemonBiosGetMaxHp(pokemon);
    itemUseAddLog(log, count, 8, 0, 0);
    return newMaxHp - oldMaxHp;
}

static inline s16 itemUseFriendUp(ITEMUSE2POKEMON_LOG1* log, s16* count, Pokemon* pokemon,
                                  FightPokemon* fightPokemon, s8 delta, u16 minFriend, u16 maxFriend) {
    s16 gained;

    if (*count <= 0) {
        return 0;
    }
    gained = friendXUp(pokemon, fightPokemon, delta, minFriend, maxFriend);
    if (gained == 0) {
        return 0;
    }
    itemUseAddLog(log, count, 0x1E, gained, 0);
    return gained;
}

extern "C" s32 itemUse2Pokemon(ITEMUSE2POKEMON_LOG1* log, Pokemon* pokemon, FightPokemon* fightPokemon, u16 itemDataId, u8 moveSlot) {
    static u8 origRamSeedParam[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    POKEMON_EVOLUTION_INFO evolutionMode;
    s16 logCount;
    u8 convertedParam[0x18];
    u8* itemParam;
    FightOutPokemon* fightOut;
    u16 hpAmount;
    u8 boost;
    s8 friendBoost;
    s16 friendDelta;
    u8 ok;

    hpAmount = 0;
    logCount = 0;

    if (itemDataId != 0xAF) {
        itemParam = itemUseGetParam(itemDataId);
    } else {
        itemParamConvertOrigFormat(convertedParam, origRamSeedParam);
        itemParam = convertedParam;
    }
    if (itemParam == 0) {
        return 0;
    }

    if (fightPokemon != 0) {
        pokemon = itemUseGetPokemon(fightPokemon);
    }

    if (itemParamGetMeromeroFlag(itemParam)) {
        fightOut = itemUseGetFightOut(fightPokemon);
        if (fightOut != 0 && fightOutPokemonIsJoutaiDataId(fightOut, 0xA)) {
            fightOutPokemonInitJoutaiDataId(fightOut, 0xA);
            itemUseNotify(fightPokemon, 0x7C);
            itemUseAddLog(log, &logCount, 0, 0, 0);
        }
    }

    if (itemParamGetCriticalFlag(itemParam)) {
        fightOut = itemUseGetFightOut(fightPokemon);
        if (fightOut != 0 && fightOutPokemonCheckWriteJoutaiDataId(fightOut, 0xF) == 2) {
            fightOutPokemonWriteJoutaiDataId(fightOut, 0xF, 0);
            itemUseNotify(fightPokemon, 0x7C);
            itemUseNotify(fightPokemon, 0x99);
            itemUseAddLog(log, &logCount, 1, 0, 0);
        }
    }

    if ((boost = itemParamGetAttackUp(itemParam)) != 0) {
        itemUseStatUpLog(log, &logCount, fightPokemon, 0xE6, boost, 2);
    }
    if ((boost = itemParamGetDefenceUp(itemParam)) != 0) {
        itemUseStatUpLog(log, &logCount, fightPokemon, 0xE7, boost, 3);
    }
    if ((boost = itemParamGetQuickUp(itemParam)) != 0) {
        itemUseStatUpLog(log, &logCount, fightPokemon, 0xEA, boost, 4);
    }
    if ((boost = itemParamGetHitUp(itemParam)) != 0) {
        itemUseStatUpLog(log, &logCount, fightPokemon, 0xEB, boost, 5);
    }
    if ((boost = itemParamGetSpAttackUp(itemParam)) != 0) {
        itemUseStatUpLog(log, &logCount, fightPokemon, 0xE8, boost, 6);
    }

    if (itemParamGetGuardFlag(itemParam)) {
        itemUseGuardSpec(log, &logCount, fightPokemon);
    }

    if (itemParamGetLevelUpFlag(itemParam)) {
        hpAmount = itemUseLevelUp(log, &logCount, pokemon);
    }

    if (itemParamGetSleepFlag(itemParam)) {
        itemUseCureSleep(log, &logCount, pokemon, fightPokemon);
    }

    if (itemParamGetPoisonFlag(itemParam)) {
        itemUseCurePoison(log, &logCount, pokemon, fightPokemon);
    }

    if (itemParamGetBurnFlag(itemParam) && pokemonIsJoutaiDataId(pokemon, 6)) {
        pokemonInitJoutaiDataId(pokemon, 6);
        itemUseNotify(fightPokemon, 0x7C);
        itemUseAddLog(log, &logCount, 0xE, 0, 0);
    }
    if (itemParamGetFreezeFlag(itemParam) && pokemonIsJoutaiDataId(pokemon, 7)) {
        pokemonInitJoutaiDataId(pokemon, 7);
        itemUseNotify(fightPokemon, 0x7C);
        itemUseAddLog(log, &logCount, 0xF, 0, 0);
    }
    if (itemParamGetParalyzeFlag(itemParam) && pokemonIsJoutaiDataId(pokemon, 5)) {
        pokemonInitJoutaiDataId(pokemon, 5);
        itemUseNotify(fightPokemon, 0x7C);
        itemUseAddLog(log, &logCount, 0x10, 0, 0);
    }

    if (itemParamGetConfuseFlag(itemParam)) {
        fightOut = itemUseGetFightOut(fightPokemon);
        if (fightOut != 0 && fightOutPokemonIsJoutaiDataId(fightOut, 9)) {
            fightOutPokemonInitJoutaiDataId(fightOut, 9);
            itemUseNotify(fightPokemon, 0x7C);
            itemUseAddLog(log, &logCount, 0x11, 0, 0);
        }
    }

    if (itemParamGetPPMaxUpFlag(itemParam)) {
        itemUsePPMaxUp(log, &logCount, pokemon, moveSlot);
    }

    if ((boost = itemParamGetHPEffortUp(itemParam)) != 0) {
        if (pokemonBiosGetPokemonDataId(pokemon) == 0x12F) {
            ok = true;
        } else {
            ok = itemUseEffortUpLog(log, &logCount, pokemon, fightPokemon, 0x8D, boost, 0x13);
        }
        if (!ok) {
            return 0;
        }
    }
    if ((boost = itemParamGetAttackEffortUp(itemParam)) != 0) {
        if (!itemUseEffortUpLog(log, &logCount, pokemon, fightPokemon, 0x8E, boost, 0x14)) {
            return 0;
        }
    }

    if ((boost = itemParamGetHPUp(itemParam)) != 0) {
        bool revive = itemParamGetReviveFlag(itemParam);
        hpRecover(log, &logCount, pokemon, boost, revive, hpAmount, fightPokemon);
    }

    if ((boost = itemParamGetPPUp(itemParam)) != 0) {
        itemUsePPRecover(log, &logCount, pokemon, fightPokemon, itemParam, moveSlot, boost);
    }

    if (itemParamGetEvolutionFlag(itemParam) && !pokemonIsDarkPokemon(pokemon)) {
        itemUseEvolve(log, &logCount, pokemon, itemDataId, &evolutionMode);
    }

    if ((boost = itemParamGetDefenceEffortUp(itemParam)) != 0) {
        if (!itemUseEffortUpLog(log, &logCount, pokemon, fightPokemon, 0x8F, boost, 0x19)) {
            return 0;
        }
    }
    if ((boost = itemParamGetQuickEffortUp(itemParam)) != 0) {
        if (!itemUseEffortUpLog(log, &logCount, pokemon, fightPokemon, 0x92, boost, 0x1A)) {
            return 0;
        }
    }
    if ((boost = itemParamGetSpDefenceEffortUp(itemParam)) != 0) {
        if (!itemUseEffortUpLog(log, &logCount, pokemon, fightPokemon, 0x91, boost, 0x1B)) {
            return 0;
        }
    }
    if ((boost = itemParamGetSpAttackEffortUp(itemParam)) != 0) {
        if (!itemUseEffortUpLog(log, &logCount, pokemon, fightPokemon, 0x90, boost, 0x1C)) {
            return 0;
        }
    }

    if (itemParamGetPPMaxFullFlag(itemParam)) {
        itemUsePPMaxFull(log, &logCount, pokemon, moveSlot);
    }

    friendDelta = 0;
    if ((friendBoost = itemParamGetFriend1Up(itemParam)) != 0) {
        friendDelta = itemUseFriendUp(log, &logCount, pokemon, fightPokemon, friendBoost, 0, 100);
    }
    if (friendDelta == 0) {
        if ((friendBoost = itemParamGetFriend2Up(itemParam)) != 0) {
            friendDelta = itemUseFriendUp(log, &logCount, pokemon, fightPokemon, friendBoost, 100, 200);
        }
    }
    if (friendDelta == 0) {
        if ((friendBoost = itemParamGetFriend3Up(itemParam)) != 0) {
            itemUseFriendUp(log, &logCount, pokemon, fightPokemon, friendBoost, 200, 0xFFFF);
        }
    }

    return logCount;
}
