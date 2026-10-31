#pragma defer_codegen on
#pragma force_active on
#include <dolphin/types.h>
static bool _menuMainExec;
extern "C" void menuColosseumBattleConnectionExit();
#pragma peephole off
#pragma opt_dead_assignments off
extern "C" void menuColosseumBattleConnectionMain(void);
#pragma opt_dead_assignments reset
#pragma peephole reset

extern "C" void menuColosseumBattleConnectionInit();


extern "C" void menuColosseumBattleConnectionInit(){_menuMainExec=false;}

#pragma opt_dead_assignments off
extern "C" void menuColosseumBattleConnectionMain(void)
{
    u8 prev = (*(volatile u8*)&_menuMainExec);
    u8 prevInverted;

    (*(volatile u8*)&_menuMainExec) = 1;
    prevInverted = (u8)(1 - prev);

}
#pragma opt_dead_assignments reset

extern "C" void menuColosseumBattleConnectionExit(){}
