#ifndef FIGHT_SEQ_BASIS_HPP
#define FIGHT_SEQ_BASIS_HPP
#include <dolphin/types.h>
struct FightOutPokemon;
// ServerWork is the eight-byte command-server record at 0x804e85c0.
// The original accesses its bytes through the fixed SDA base.
struct BasisServerWork { u8 flags[8]; };
struct BasisYokodoriWork {
    FightOutPokemon* attacker;
    FightOutPokemon* result;
};
typedef char BasisServerWorkSize[(sizeof(BasisServerWork) == 8) ? 1 : -1];
typedef char BasisYokodoriWorkSize[(sizeof(BasisYokodoriWork) == 8) ? 1 : -1];
typedef char BasisYokodoriWorkAttackerOffset[(((u32)&((BasisYokodoriWork*)0)->attacker) == 0) ? 1 : -1];
typedef char BasisYokodoriWorkResultOffset[(((u32)&((BasisYokodoriWork*)0)->result) == 4) ? 1 : -1];
extern "C" {
extern BasisServerWork ServerWork;
extern u16 TSUIKATbl[];
extern u8* TSUIKASeqTbl[];
extern u32 NoHitMsgTbl[];
extern u16 ShimeWazaNo[];
extern u8* WazaEffectTbl[];
}
#endif
