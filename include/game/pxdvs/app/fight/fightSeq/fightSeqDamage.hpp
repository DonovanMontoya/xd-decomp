#ifndef FIGHT_SEQ_DAMAGE_HPP
#define FIGHT_SEQ_DAMAGE_HPP

#include <dolphin/types.h>

struct FIGHT_TRAINER;
struct FightOutPokemon;
struct FightPokemon;
struct FightSide;

typedef void (*FightSeqDamageFunc)(FIGHT_TRAINER*, u16, FightOutPokemon*, FightOutPokemon*);
typedef void (*FightSeqHikaeDamageFunc)(FIGHT_TRAINER*, u16, FightOutPokemon*, FightPokemon*);

extern "C" {
s32 fightSeqGetNromalWazaDamage(FIGHT_TRAINER* trainer, u16 wazaId, FightOutPokemon* attacker,
                                FightOutPokemon* defender, u8 critical, u8 loss,
                                FightSeqDamageFunc before, FightSeqDamageFunc after);
s32 fightSeqGetWazaDamageHikaePokemon(FIGHT_TRAINER* trainer, u16 wazaId, FightOutPokemon* attacker,
                                      FightPokemon* defender, u8 critical,
                                      FightSeqHikaeDamageFunc before, FightSeqHikaeDamageFunc after);
s32 fightSeqWazaDamageCalcHikaePokemon(FightOutPokemon* attacker, FightPokemon* defender, FightSide* side,
                                      u16 wazaId, u16 power, s32 moveType);
}

#endif
