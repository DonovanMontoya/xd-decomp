#ifndef FIGHT_WAZA_BIOS_LAYOUT_HPP
#define FIGHT_WAZA_BIOS_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct FightWazaHitKakurituBiosRecord { u8 kake; u8 waru; };
struct FightWazaCriticalBiosRecord { u8 bunbo; };
typedef char FightWazaHitKakurituBiosRecordSize[sizeof(FightWazaHitKakurituBiosRecord)==2?1:-1];
typedef char FightWazaCriticalBiosRecordSize[sizeof(FightWazaCriticalBiosRecord)==1?1:-1];
struct ComboStatusMove {u16 move,stat,amount;};
#endif
