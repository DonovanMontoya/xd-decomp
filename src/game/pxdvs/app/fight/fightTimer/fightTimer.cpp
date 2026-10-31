#pragma force_active on
#include <global.h>
// Limits use seconds; the worker accumulates 60 Hz render frames.
static const f32 sTimerZero[] = {0.0f};
static const f32 sTimerFramesPerSecond[] = {60.0f};
struct FightTimer { u8 over; u8 special; u8 pad[2]; f32 elapsed; f32 limit; u32 thread; };
extern "C" {
extern s32 GSfloorGetCurrentFloorGroupID(void);
extern f32 GSgfxVideoGetLastRenderTime(void);
extern u8 GSgfxVideoGetVsyncRate(void);
extern void GSthreadBlock(u32);
extern u32 GSthreadCreate(u32,s32,u32,u32,u32,void (*)(void*));
extern void GSthreadSetArgs(u32,s32,...);
extern void GSthreadSwitch(void);
extern void GSthreadTerminate(u32);
extern s32 menuCBRule_GetBattleTimeLimit(void);
extern s32 menuCBRule_GetCommandTimeLimit(void);
void fightTimerThreadFunc(void*);
static FightTimer gCommandTimer;
static FightTimer gBattleTimer;
u8 fightTimerIsOver(FightTimer* p);
f32 fightTimerGetNokoriTime(FightTimer* p);
u8 fightTimerBlock(FightTimer* p);
void fightTimerStart(FightTimer* p);
void fightTimerTerminate(FightTimer* p);
void fightTimerInit(FightTimer* p,f32 t);
void fightTimerThreadFunc(void* arg);
void fightTimerCommandTerminate();
u8 fightTimerCommandIsOver();
f32 fightTimerCommandGetNokoriTime();
u8 fightTimerCommandBlock();
void fightTimerCommandStart();
void fightTimerCommandInit();
u8 fightTimerAllIsOver();
f32 fightTimerAllGetNokoriTime();
u8 fightTimerAllBlock();
void fightTimerAllStart();
void fightTimerAllInit();
void fightTimerAllTerminate();
}

extern "C" {
void fightTimerCommandTerminate(){fightTimerTerminate(&gCommandTimer);}
u8 fightTimerCommandIsOver(){return fightTimerIsOver(&gCommandTimer);}
f32 fightTimerCommandGetNokoriTime(){return fightTimerGetNokoriTime(&gCommandTimer);}
u8 fightTimerCommandBlock(){return fightTimerBlock(&gCommandTimer);}
void fightTimerCommandStart(){fightTimerStart(&gCommandTimer);}
void fightTimerCommandInit(){fightTimerInit(&gCommandTimer,(f32)menuCBRule_GetCommandTimeLimit());}
u8 fightTimerAllIsOver(){return fightTimerIsOver(&gBattleTimer);}
f32 fightTimerAllGetNokoriTime(){return fightTimerGetNokoriTime(&gBattleTimer);}
u8 fightTimerAllBlock(){return fightTimerBlock(&gBattleTimer);}
void fightTimerAllStart(){fightTimerStart(&gBattleTimer);}
void fightTimerAllInit(){fightTimerInit(&gBattleTimer,(f32)menuCBRule_GetBattleTimeLimit());}
void fightTimerAllTerminate(){fightTimerTerminate(&gBattleTimer);}
u8 fightTimerIsOver(FightTimer* p){if(p->special==1)return 0;if(p->thread==0)return 1;return p->over;}
f32 fightTimerGetNokoriTime(FightTimer* p){if(p->special==1)return -3600.0f;if(p->thread==0)return sTimerZero[0];return p->limit-(p->elapsed/(f32)GSgfxVideoGetVsyncRate());}
u8 fightTimerBlock(FightTimer* p){if(p->special==1)return 0;if(p->thread==0)return 0;GSthreadBlock(p->thread);return 1;}
void fightTimerStart(FightTimer* p){if(p->special!=1){u32 t=GSthreadCreate(1,GSfloorGetCurrentFloorGroupID(),0x4000,1,0,fightTimerThreadFunc);if(t!=0){p->thread=t;GSthreadSetArgs(t,1,p);}}}
void fightTimerTerminate(FightTimer* p){if(p->thread!=0)GSthreadTerminate(p->thread);p->over=0;p->elapsed=sTimerZero[0];p->limit=sTimerZero[0];p->thread=0;p->special=0;}
void fightTimerInit(FightTimer* p,f32 t){if(p->thread!=0)fightTimerTerminate(p);p->over=0;p->elapsed=sTimerZero[0];if(t<sTimerZero[0]){p->special=1;p->limit=-3600.0f;}else{p->special=0;p->limit=t;}p->thread=0;}
void fightTimerThreadFunc(void* arg){FightTimer* p=(FightTimer*)arg;p->elapsed=sTimerZero[0];while(p->elapsed<sTimerFramesPerSecond[0]*p->limit){GSthreadSwitch();p->elapsed=p->elapsed+GSgfxVideoGetLastRenderTime();}p->over=1;for(;;)GSthreadSwitch();}
}
#pragma force_active reset
