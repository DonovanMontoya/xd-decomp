#include <global.h>
#include <game/pxdvs/app/fight/fightAction.hpp>
static FIGHT_ACTION fight_action;
static u8 _fightSoundOpenPlayStart;
static u8 _fightSoundOpenPlayEnvStart;
static u16 _fight_reg_wzx_generic_data_id_ary[] = {87,0,158,0,38,0,39,0,40,0,41,0,42,0,43,0,44,0,45,0,60,0,46,3,47,3,48,3,49,3,50,3,51,3,52,3,55,3,57,3,88,3};
static u16 _fight_reg_wzx_generic_data_id_ary_num=42;
extern "C" {
u16 fightGetFightEncountDataId(); u32 fightEncountGetEnvSndDataId();u32 fightEncountGetBgmSndDataId(); void soundOpenPlayEnv(u32,s32,s32);void soundOpenPlay(u32,s32,s32);
s32 wazaSequenceSysGetWazaGroupID(u16,s32);u8 GSfsysPreReadKeepCache(s32);s32 GSfsysGetStatus(s32);void GSthreadSwitch();f32 GSgfxVideoGetLastRenderTime();
s32 battleCameraIsSimple();void battleCameraDoSimple();void battleCameraDoFull();void battleCameraStop();void battleCameraStartRandom(s32);
s32 dbgMenuGetEnable();void dbgMenuSetEnable(s32);u8 dbgMenuFightGetFightDebugMenuOpenFlag();void dbgMenuMain(s32);void menuGetKeyInfo(u16*,s32);u32 dbgMenuFightGetMsgSpeedToFrame(u32);
u8 fightFloor_GetFightType(void*);u8 fightFloor_GetFightTypeTrainerNum(void*);u8 fightFloor_GetFightTypeFightoutPokemonNum(void*);void *fightFloorGetValidFightSidePtr(void*,u16);void *fightSideGetValidFightTrainerPtr(void*,u16);void *fightTrainer_GetSequencePtr(void*);void *fightTrainerGetValidFightOutPokemonPtr(void*,u16);void *fightOutPokemon_GetSequencePtr(void*);void Sequence_SetVisibility(void*,s32);void battleGridStoreModelVisibilityFlags();
static void _fightMainWaitFrameSub__FUl(u32);
void fightMainWaitFrame(u32);

s32 fightRegWzxLoadGenric(u16);
void fightRegWzxLoadAll(s8 category){for(u16 i=0;i<_fight_reg_wzx_generic_data_id_ary_num;i+=2){if(category<0 || category==_fight_reg_wzx_generic_data_id_ary[i+1])fightRegWzxLoadGenric(_fight_reg_wzx_generic_data_id_ary[i]);}}
s32 fightRegWzxLoadGenric(u16 id){s32 group=wazaSequenceSysGetWazaGroupID(id,4);if(GSfsysPreReadKeepCache(group)==0)return 0;for(;;){s32 status=GSfsysGetStatus(group);if(status==0 || status<0)break;GSthreadSwitch();}return 1;}
void fightSoundOpenPlayEnv(u8 start){if(_fightSoundOpenPlayEnvStart!=1 && start!=0 && fightGetFightEncountDataId()!=0){u32 id=fightEncountGetEnvSndDataId();if(id)soundOpenPlayEnv(id,1000,255);_fightSoundOpenPlayEnvStart=1;}}
void fightSoundOpenPlay(u8 start){if(_fightSoundOpenPlayStart!=1 && start!=0 && fightGetFightEncountDataId()!=0){u32 id=fightEncountGetBgmSndDataId();if(id)soundOpenPlay(id,0,255);_fightSoundOpenPlayStart=1;}}
void fightSoundOpenPlayInit(){_fightSoundOpenPlayStart=0;_fightSoundOpenPlayEnvStart=0;}
void fightMainSetAllDispFlag(s32 visible){
 void *side;u16 j,k,i;u32 trainers,pokemon;void *trainer;
 fightFloor_GetFightType(0);trainers=fightFloor_GetFightTypeTrainerNum(0);pokemon=fightFloor_GetFightTypeFightoutPokemonNum(0);
 for(i=0;i<2;i++){side=fightFloorGetValidFightSidePtr(0,i);if(side){for(j=0;j<trainers;j++){trainer=fightSideGetValidFightTrainerPtr(side,j);if(trainer){void *seq=fightTrainer_GetSequencePtr(trainer);if(seq){Sequence_SetVisibility(seq,visible);for(k=0;k<pokemon;k++){void *poke=fightTrainerGetValidFightOutPokemonPtr(trainer,k);if(poke){seq=fightOutPokemon_GetSequencePtr(poke);if(seq)Sequence_SetVisibility(seq,visible);}}}}}}}
 battleGridStoreModelVisibilityFlags();
}
s32 fightMainAllCamera(u8 simple,u8 stop){s32 previous=battleCameraIsSimple();if(simple==1)battleCameraDoSimple();else battleCameraDoFull();if(stop)battleCameraStop();battleCameraStartRandom(1);return previous;}
void fightMainDebugMenu(){u16 keys[16];s32 frames;s32 previous=dbgMenuGetEnable();dbgMenuSetEnable(1);if(dbgMenuFightGetFightDebugMenuOpenFlag()==1)dbgMenuMain(1);else {frames=0;while((u8)frames<4){menuGetKeyInfo(keys,1);if(keys[0]&0x800)break;GSthreadSwitch();frames=(s32)((f32)(u8)frames+GSgfxVideoGetLastRenderTime());}if((u8)frames<4)dbgMenuMain(1);}dbgMenuSetEnable(previous);}



}

extern "C" {
void *fightEncountDataBiosGetPtr(u16);u16 fightEncountDataBiosGetDiskId(void*);
u32 fightFloor_GetEnvSndId(void*);void fightActionFlowKaisiPreSubLoad();
u8 fightFloorIsNowEncountOpeningVirtualBattle(void*);void fadeSet(u16,f32);s32 fadeCheck(u8);
u16 fightGetFightResultId();u8 fightFloorIsNowEncountSnatchOnly(void*);void fightSeqEventKurein(u16);
u8 fightFloorIsNowEncountHostEnemyPokemonKime(void*);u8 fightFloorIsNowEncountHostPokemonKime(void*);
void fightActionDispFifoAll();u8 fightFloorIsUseFightTimerAll(void*);void fightTimerAllInit();void fightTimerAllStart();u8 fightTimerAllIsOver();
void menuFightOpenTimeup();u16 fightFloor_GetEncountDataId(void*);void fightMenuOpenInfoMenu(s32);void fightFloorSetTimeOutAllFightResult(void*);
}
u8 deckDataVirtualDB_GetTurnLimit(u16);
extern "C" {
void fightSetFightResultId(u16);u16 fightFloor_GetTurnCount(void*);u8 fightFloorIsUseFightTimerCommand(void*);void fightTimerCommandInit();void fightTimerCommandStart();void battleGridUpdate();u8 dbgMenuFightGetFightPokeStMenuOpenFlag();s32 menuFightChkSeq();void fightMenuCloseInfoMenu(s32);void fightTimerCommandBlock();void fightTimerCommandTerminate();void fightSeqCheckZenmetu();void fightCloseAllMenu();void fightTimerAllBlock();void fightTimerAllTerminate();void winMsgOpen(s32,u32,s32,s32);void winMsgClose(s32);void soundStop(u32,s32);void soundOpenPlayFadeOutIn(u32,s32,s32,s32);void battleCameraDisable();u8 fightFloorIsNowEncountVirtualBattle(void*);s32 fadeSetEX(u16,void(*)(),u8,f32,f32);void fadeEffectHookFunction_virtual_end_Init();void fightEncountCheckZenmetu();void GSfloorPop();void floorSetFadeScript(u16,u16);
extern FIGHT_ACTION_DATA_dd_ fight_action_data_kaisi[],fight_action_data_turn[],fight_action_data_syuuryou[];
}

extern "C" void fightMain(void) {
    u16 diskId;
    u32 turnLimit;
    u32 env;

    diskId = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));
    if ((env = fightFloor_GetEnvSndId(0)) != 0U) {
        soundOpenPlayEnv(env, 0x3E8, 0xFF);
    }
    fightActionFlowKaisiPreSubLoad();
    if (fightFloorIsNowEncountOpeningVirtualBattle(0) == 0) {
        fadeSet(8, 1.0f);
    }
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 2, 0U, fight_action_data_kaisi);
    if (fightFloorIsNowEncountOpeningVirtualBattle(0) == 0) {
        fadeCheck(1);
    }
    fightMainDebugMenu();
    if (fightGetFightResultId() == 0) {
        if (fightFloorIsNowEncountSnatchOnly(0) == 1) {
            fightSeqEventKurein(3);
            fightSeqEventKurein(4);
        }
        if (fightFloorIsNowEncountHostEnemyPokemonKime(0) == 0) {
            fightActionCreateAndFlowFifo(&fight_action, 0, 0, 4, 5U, fight_action_data_kaisi);
        }
        if (fightFloorIsNowEncountHostPokemonKime(0) == 0) {
            fightActionCreateAndFlowFifo(&fight_action, 0, 0, 4, 4U, fight_action_data_kaisi);
        }
        if (fightFloorIsNowEncountOpeningVirtualBattle(0) == 1) {
            fadeSet(2, 0.5f);
            fadeCheck(1);
            fightMainWaitFrame(0x64);
        }
        fightActionCreateAndFlowFifo(&fight_action, 0, 0, 5, 0U, fight_action_data_kaisi);
        if (fightFloorIsNowEncountSnatchOnly(0) == 1) {
            fightSeqEventKurein(5);
        }
        fightActionDispFifoAll();
        if (fightFloorIsUseFightTimerAll(0) == 1) {
            fightTimerAllInit();
            fightTimerAllStart();
        }
        goto checkResult;
turnLoop:
            fightMainDebugMenu();
            if (fightGetFightResultId() == 0) {
                if ((fightFloorIsUseFightTimerAll(0) == 1) && (fightTimerAllIsOver() == 1)) {
                    menuFightOpenTimeup();
                    if ((fightFloorIsNowEncountHostEnemyPokemonKime(0) == 0) && (fightFloorIsNowEncountOpeningVirtualBattle(0) == 0)) {
                        fightMainAllCamera(1, 0);
                    }
                    if (fightFloor_GetEncountDataId(0) != 0xD9) {
                        fightMenuOpenInfoMenu(0);
                    }
                    fightFloorSetTimeOutAllFightResult(0);
                    fightMainWaitFrame(0xB4);
                } else if ((deckDataVirtualDB_GetTurnLimit(diskId) != 0) && (turnLimit = deckDataVirtualDB_GetTurnLimit(diskId), ((s32) fightFloor_GetTurnCount(0) > (s32) turnLimit))) {
                    fightMainAllCamera(1, 0);
                    fightMenuOpenInfoMenu(0);
                    fightSetFightResultId(7);
                    fightMainWaitFrame(0x64);
                } else {
                    if (fightFloorIsUseFightTimerCommand(0) == 1) {
                        fightTimerCommandInit();
                        fightTimerCommandStart();
                    }
                    battleGridUpdate();
                    fightMainAllCamera(0, 1);
                    if (fightFloor_GetEncountDataId(0) != 0xD9) {
                        fightMenuOpenInfoMenu(-1);
                    }
                    if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 0) {
                        fightMainWaitFrame(0x258);
                    }
                    fightActionDispFifoAll();
                    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 7, 0U, fight_action_data_turn);
waitForMenu:
                    if (menuFightChkSeq() != 0) {
                        GSthreadSwitch();
                        goto waitForMenu;
                    }
                    GSthreadSwitch();
                    GSthreadSwitch();
                    fightActionDispFifoAll();
                    fightMenuCloseInfoMenu(0);
                    battleCameraDoSimple();
                    if (fightFloorIsUseFightTimerCommand(0) == 1) {
                        fightTimerCommandBlock();
                        fightTimerCommandTerminate();
                    }
                    fightSeqCheckZenmetu();
                    if (fightGetFightResultId() == 0) {
                        fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0xB, 0U, fight_action_data_turn);
                        if (fightGetFightResultId() == 0) {
                            fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0xD, 0U, fight_action_data_turn);
                            if (fightGetFightResultId() != 0) goto endTurns;
checkResult:
                            if (fightGetFightResultId() == 0) {
                                goto turnLoop;
                            }
                        }
                    }
                }
            }
endTurns:
        fightActionDispFifoAll();
    }
    fightMainAllCamera(1, 0);
    fightCloseAllMenu();
    if (fightFloorIsUseFightTimerAll(0) == 1) {
        fightTimerAllBlock();
        fightTimerAllTerminate();
    }
    if (fightGetFightResultId() == 1) {
        winMsgOpen(2, 0x5011, 1, 1);
        fightMainWaitFrame(0x64);
        winMsgClose(1);
    }
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0xE, 0U, fight_action_data_syuuryou);
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0xF, fightGetFightResultId(), fight_action_data_syuuryou);
    fightActionDispFifoAll();
    if ((env = fightFloor_GetEnvSndId(0)) != 0U) {
        soundStop(env, 0x3E8);
    }
    if (fightFloor_GetEnvSndId(0) == 0U) {
        soundOpenPlayFadeOutIn(8, 0x3E8, 0x3E8, 0xFF);
    }
    battleCameraDisable();
    if ((fightFloorIsNowEncountVirtualBattle(0) == 1) || (fightFloorIsNowEncountOpeningVirtualBattle(0) == 1)) {
        fadeSetEX(0x18, &fadeEffectHookFunction_virtual_end_Init, 1, 2.5f, 2.5f);
    } else {
        fadeSet(3, 1.0f);
    }
    fadeCheck(1);
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0x10, 0U, fight_action_data_syuuryou);
    fightActionCreateAndFlowFifo(&fight_action, 0, 0, 0x11, 0U, fight_action_data_syuuryou);
    fightEncountCheckZenmetu();
    GSfloorPop();
    floorSetFadeScript(0, 0);
}

extern "C" {
void fightMainWaitFrameEffect(u32 frames){_fightMainWaitFrameSub__FUl(frames);}
void fightMainWaitFrame(u32 frames){_fightMainWaitFrameSub__FUl(dbgMenuFightGetMsgSpeedToFrame(frames));}
static void _fightMainWaitFrameSub__FUl(u32 frames){if(frames){for(u32 elapsed=0;elapsed<frames;) {GSthreadSwitch();elapsed=(f32)elapsed+GSgfxVideoGetLastRenderTime();}}}
}
