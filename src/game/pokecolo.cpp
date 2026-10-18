#include <global.h>
#pragma dont_inline on
#pragma force_active on
static u8 __pokecolo_CountPlayTime;
static u8 pokecolo_DVDETHMode;
static s32 _RomVer;
static u64 _frameTime;
static f32 _resettimer;
static s32 _pokecoloCurrentLanguage;
static void* _getSaveSystemDataPtr();
extern "C" {
void* savedataBiosGetNowSavedataPtr();
void* savedataBiosGetGamedataPtr(void*);
void* gamedatasaveBiosGetPtr(void*);
f64 gamedatasaveBiosGetPlaytime(void*);
void gamedatasaveBiosSetPlaytime(void*,f64);
u32 GSflagGet(u32);
s32 GSfsysGetDriveStatus();
u8 menuIsCheck(u32);
u8 pauseIsPause();
void pauseOn();
void pauseOff();
void GSsndQuit();
void GSfsysReadWait(u32);
void GSgfxRender();
void fn_8005C8EC();
void GSinputReadStart();
void GSinputReadEnd();
void GSinputRead(s32);
u8 GSinputIsConnected(s32);
u8 gbaCommandIsConnected(s32);
void gbaCommandKeyRead(s32);
void dbgMenuGSvtrCaptureUpdate();
u8 GSvtrIsActive();
u8 dbgMenuIsOpen();
u32 GSinputButtonsChanged(u32);
u32 GSinputButtonsPressed(u32);
s32 GSvtrGetState();
void GSvtrSlowPlay();
void GSvtrPause();
void GSvtrPlay();
void GSvtrSingleStep();
u8 GSvtrGetInfoDisp();
void GSvtrSetInfoDisp(bool,u32);
void menuDaemon();
void GSmsgDaemon();
u8 GSgfxResetGetStatus();
f32 timeGetLastFrameSec();
void GSgfxReset(u32);
void GSthreadExecuteAll();
u8 menuFieldIsOpen();
u8 peopleIsBlock();
void peopleDaemon(unsigned long,unsigned long);
void peopleUpdateShadow();
u8 pokecoloIsDVDETHMode(){return pokecolo_DVDETHMode;}
void fn_8005C068(s32 language){_pokecoloCurrentLanguage=language;}
s32 pokecoloGetLanguage(){if(_pokecoloCurrentLanguage==0)return 2;return _pokecoloCurrentLanguage;}
void pokecoloStartCountPlayTime(u8 active){__pokecolo_CountPlayTime=active;}
void pokecoloSetPlayTime(f64 value){void* save=_getSaveSystemDataPtr();if(save)gamedatasaveBiosSetPlaytime(save,value);}
f64 pokecoloGetPlayTime(){void* save=_getSaveSystemDataPtr();if(save)return gamedatasaveBiosGetPlaytime(save);return 0.0;}
u32 pokecoloGetPlayTimeValue(){return (u32)pokecoloGetPlayTime();}
s32 pokecoloGetCountryCode(){return 1;}
s32 pokecoloGetRomVersion(){return _RomVer;}
void pokecoloInitRomVersion(){_RomVer=0;}
f64 pokecoloGetFrameTime(){return ((f32)_frameTime/1000.0f)/1000.0f;}
void pokecoloCheckDiskTray(){
    if(menuIsCheck(0x2a)){
        if(!pauseIsPause())pauseOn();
    }else{
        switch(GSfsysGetDriveStatus()){
        case 3:case 4:case 5:case 6:case 11:
            if(!pauseIsPause())pauseOn();
            break;
        default:
            if(pauseIsPause())pauseOff();
            break;
        }
    }
}
}
static void _countPlayTime(){
    void* save=_getSaveSystemDataPtr();
    if(save && __pokecolo_CountPlayTime==1 && GSflagGet(0x30d)==0){
        f64 time=gamedatasaveBiosGetPlaytime(save);
        f64 elapsed=pokecoloGetFrameTime();
        time+=elapsed;
        if(time>=3599940.0)time=3599940.0;
        gamedatasaveBiosSetPlaytime(save,time);
    }
}
static void* _getSaveSystemDataPtr(){
    void* save=savedataBiosGetNowSavedataPtr();
    if(save){
        void* data=savedataBiosGetGamedataPtr(save);
        if(data)return gamedatasaveBiosGetPtr(data);
    }
    return 0;
}
s32 _pokecoloCheckExDisc(){if(pokecoloGetRomVersion()==4)return 1;return 0;}
static void _pokecoloShutdown(){GSsndQuit();}
extern "C" s32 fn_8005C8C4(){return 2;}
extern "C" void fn_8005C8CC(){fn_8005C8EC();}
extern "C" void fn_8005C8EC(){GSfsysReadWait(10);}
static void _setSystemVars(){}
static void _mainRender(unsigned long,unsigned long){
    static s32 frame=0;
    GSgfxRender();
}
static void _mainDaemon(unsigned long,unsigned long){
    dbgMenuGSvtrCaptureUpdate();
    if(GSvtrIsActive() && !dbgMenuIsOpen()){
        u32 changed=GSinputButtonsChanged(1);
        u32 pressed=GSinputButtonsPressed(1);
        if((pressed&changed&0x40)!=0){
            if(GSvtrGetState()==2)GSvtrSlowPlay();
            else if(GSvtrGetState()==4)GSvtrPause();
            else GSvtrPlay();
        }
        changed=GSinputButtonsChanged(1);
        pressed=GSinputButtonsPressed(1);
        if((pressed&changed&0x10)!=0)GSvtrSingleStep();
        changed=GSinputButtonsChanged(1);
        pressed=GSinputButtonsPressed(1);
        if((pressed&changed&8)!=0)GSvtrSetInfoDisp(!GSvtrGetInfoDisp(),0);
    }
    menuDaemon();GSmsgDaemon();_countPlayTime();
}
static void _mainThreadExec(unsigned long first,unsigned long second){
    u8 reset=GSgfxResetGetStatus();
    if((GSinputButtonsPressed(1)&0x1600)==0x1600 && reset!=0){
        _resettimer+=timeGetLastFrameSec();
        if(_resettimer>=0.5f)GSgfxReset(0);
    }else _resettimer=0.0f;
    GSthreadExecuteAll();
    if(!menuFieldIsOpen() && !peopleIsBlock())peopleDaemon(first,second);
    else peopleUpdateShadow();
}
static void _mainGBARead(unsigned long,unsigned long){
    s32 channel=1;
    do{if(!GSinputIsConnected(channel))gbaCommandKeyRead(channel);++channel;}while(channel<=4);
}
static void _mainPadRead(unsigned long,unsigned long){
    GSinputReadStart();
    s32 channel=1;
    do{if(!gbaCommandIsConnected(channel))GSinputRead(channel);++channel;}while(channel<=4);
    GSinputReadEnd();
}
#pragma force_active reset

#include <libc/string.h>
extern "C" {
u8 pokecoloWaitVSync;
u32 pokecoloFrameCounter;
void *pokecoloGappThreadHandle,*pokecoloGappPadReadHandle,*pokecoloGappGBAReadHandle,*pokecoloGappMainDeamonHandle,*pokecoloGappRenderHandle,*pokecoloGappAntiActionReplayHandle;
void floorLayerConfig(u32,u32);
void menuNintendo();
void floorLayerConfigLoad();
extern u32 *floordata_number;
extern void *floordata;
void GSfloorSetData(void *,u32);
u8 *GSresAllocResource(u32,u32,u32,u32);
void *tableResBiosGetResPtr(u32);
void GSmsgFontOpen(void *);
void GSmsgOpen(void *);
void GSdvdSetErrorMsg(u32,u32,u32,u32,u32);
void floorMappingCommonScript();
u64 OSGetTime();
u8 *savedataBiosGetSavedataBufferPtr();
void savedataBiosSetNowSavedataPtr(void *);
void savedataCreate(void *,u32);
void fightInit();
u32 savedataGetStatus(void *,u32);
void GSflagInit(u32,u32,u32,u32,u32,u32);
void GSvtrLoadTexture();
void menuFaceAllocMemory();
void *GSresGetResourceAllGroup(u32);
void GSmodelSetMarukageTexture(void *);
void characterInit();
void cameraInit();
void lightInit();
void heroMoveAllInit();
void peopleInit(u32);
void floorFieldCameraInit();
void sodateyaHeroCallBackInit();
void reliveHallCallBackInit();
void esabaHeroCallBackInit();
void memcardInitialize();
void floorInit();
}
static const u32 _clearAddress[32]={
    0x17EB,0x2FEA,0x183,0x1EA,0x283,0x2EA,0x383,0x3EA,
    0x483,0x4EA,0x583,0x5EA,0x683,0x6EA,0x783,0x7EA,
    0x883,0x8EA,0x983,0xBEA,0xC83,0xCEA,0xD83,0xEEA,
    0xF83,0x12EA,0x1383,0x13EA,0x1483,0x16EA,0x1783,0x17EA
};
static s32 _AntiActionReplayTimer;
extern "C" void mainAntiActionReplay(unsigned long,unsigned long) {
    if(_AntiActionReplayTimer==0) {
        for(u32 i=0;i<32;i+=2) {
            memset((void *)(0x80000000+_clearAddress[i]+0x15),0,(_clearAddress[i+1]+0x16)-(_clearAddress[i]+0x15));
        }
        memset((void *)0x80001801,0,0x17FF);
        _AntiActionReplayTimer=100;
    }
    --_AntiActionReplayTimer;
}
static void _pokecoloInit() {
    floorLayerConfig(0,5);menuNintendo();floorLayerConfigLoad();
    GSfloorSetData(floordata,*floordata_number);
    u8 *resource=GSresAllocResource(2,0,2,0);
    resource[0]=0;resource[1]=0;pokecoloWaitVSync=0;
    pokecoloSetPlayTime(0.0);pokecoloStartCountPlayTime(0);
    GSmsgFontOpen(tableResBiosGetResPtr(0));
    GSmsgOpen(tableResBiosGetResPtr(1));
    GSdvdSetErrorMsg(0x65,0x66,0x67,0x68,0x69);
    floorMappingCommonScript();
    u32 offset=(u32)OSGetTime()&0x7E0;
    savedataBiosSetNowSavedataPtr(savedataBiosGetSavedataBufferPtr()+offset);
    savedataCreate(0,0);fightInit();
    GSflagInit(savedataGetStatus(0,4),savedataGetStatus(0,7),savedataGetStatus(0,5),savedataGetStatus(0,8),savedataGetStatus(0,6),savedataGetStatus(0,9));
    GSvtrLoadTexture();menuFaceAllocMemory();
    GSmodelSetMarukageTexture(GSresGetResourceAllGroup(0x1F3A1200));
    characterInit();cameraInit();lightInit();heroMoveAllInit();peopleInit(0x30);
    floorFieldCameraInit();sodateyaHeroCallBackInit();reliveHallCallBackInit();esabaHeroCallBackInit();
    memcardInitialize();floorInit();_setSystemVars();
    memset((void *)0x80001803,0,0x17FD);
}

#include <game/sysvarsPrivate.hpp>
extern "C" {
extern SystemVars systemVars;
void GSgfxRelocToScratch();
void GSgfxPerfbarSetRenderMode(s32);
void GSthreadInit(u32);
u32 OSGetProgressiveMode();
u32 OSGetResetCode();
void GSgfxVideoSetMode(u32,u32,u32,u32,u32);
void pauseInit();
void GStextureInit(u32);
void GSmodelInit();
void GSpartInit(u32);
void GSmaterialInit();
void GScameraInit(u32);
void GSlightInit(u32);
void shapeInit(u32);
void GSparticleInit(u32);
void GSinputInit();
void GSinputOpen(s32);
void GSinputSetClamping(s32,u32);
void GSinputSetSmoothingRate(s32,u32);
void GSinputSetSmoothingFunc(s32,u32);
void GSgappInit(u32,u32);
void GSresInit(u32);
void GSfloorInit(u32,u32,u32,u32);
void GScolsys2Init();
void GSmsgInit(u32,u32);
extern u8 msgctrlcode[];
void GSmsgSetCtrlFunc(void *);
void GSnetworkInit();
extern u8 resident_fnt[];
extern u8 common_fnt[];
extern u8 common_tbl[];
extern u8 system_error_fnt[8];
extern u8 system_error_tbl[];
extern u8 debug_menu_fnt[];
extern u8 lbl_8038FBE0[];
void GSvtrInit();
void GSlensFlareInit();
void GSmovieInit();
void menuInit(u32);
void GSgfxVideoSetLockFrameRate(u32);
void GSgfxVideoSetLockFrameActive(u32);
void *GSgappCreate(u32,u32,u32,void (*)(unsigned long,unsigned long));
void GSgappSetName(void *,const char *);
void GSgappSetPauseLevel(void *,u32);
void GSvtrRegisterGSgapp(void *);
void GSgfxResetEnable();
void GSgfxResetSetShutdownCallback(void (*)());
void fadeInit();
void GSfilterInitialise(u32);
void GSeffectInitSystem();
void deckInit();
void *GSthreadCreate(u32,u32,u32,u32,u32,void (*)());
void GSgappUpdate();
void pokecoloMain() {
    GSgfxRelocToScratch();
    pokecoloFrameCounter=0;
    switch(systemVars.perfbar) {
    case 0:GSgfxPerfbarSetRenderMode(0);break;
    case 1:GSgfxPerfbarSetRenderMode(1);break;
    case 2:GSgfxPerfbarSetRenderMode(2);break;
    }
    GSthreadInit(20);fn_8005C068(2);
    {
    u8 progressive=0;
    if(_pokecoloCheckExDisc()==1) {
        if(OSGetProgressiveMode()==1)progressive=1;
    } else if(OSGetProgressiveMode()==1) {
        s32 reset=(OSGetResetCode()&0x80000000)?1:0;
        if(reset==1)progressive=1;
    }
    if(progressive!=0)GSgfxVideoSetMode(0,1,0,0,1);
    pauseInit();GStextureInit(16);GSmodelInit();GSpartInit(8);GSmaterialInit();
    GScameraInit(32);GSlightInit(32);shapeInit(32);GSparticleInit(32);GSinputInit();
    for(s32 i=1;i<=4;++i) {
        GSinputOpen(i);GSinputSetClamping(i,2);GSinputSetSmoothingRate(i,7);GSinputSetSmoothingFunc(i,1);
    }
    }
    GSgappInit(20,4);GSresInit(0x15E);GSfloorInit(4,16,16,16);GScolsys2Init();GSmsgInit(2,5);
    GSmsgSetCtrlFunc(msgctrlcode);GSnetworkInit();
    GSmsgFontOpen(resident_fnt);GSmsgFontOpen(common_fnt);GSmsgOpen(common_tbl);
    GSmsgFontOpen(system_error_fnt);GSmsgOpen(system_error_tbl);GSmsgFontOpen(debug_menu_fnt);GSmsgOpen(lbl_8038FBE0);
    GSdvdSetErrorMsg(0x65,0x66,0x67,0x68,0x69);GSvtrInit();GSlensFlareInit();GSmovieInit();menuInit(24);
    GSgfxVideoSetLockFrameRate(0);GSgfxVideoSetLockFrameActive(1);
    pokecoloGappRenderHandle=GSgappCreate(1,255,0,_mainRender);GSgappSetName(pokecoloGappRenderHandle,"Render");
    pokecoloGappPadReadHandle=GSgappCreate(1,0,0,_mainPadRead);GSgappSetName(pokecoloGappPadReadHandle,"PADRead");
    pokecoloGappGBAReadHandle=GSgappCreate(1,1,0,_mainGBARead);GSgappSetName(pokecoloGappGBAReadHandle,"GBARead");
    pokecoloGappThreadHandle=GSgappCreate(1,10,0,_mainThreadExec);GSgappSetName(pokecoloGappThreadHandle,"mainThread");
    GSgappSetPauseLevel(pokecoloGappThreadHandle,1);GSvtrRegisterGSgapp(pokecoloGappThreadHandle);
    pokecoloGappAntiActionReplayHandle=GSgappCreate(1,253,0,mainAntiActionReplay);GSgappSetName(pokecoloGappAntiActionReplayHandle,"AntiActionReplay");
    pokecoloGappMainDeamonHandle=GSgappCreate(1,254,0,_mainDaemon);GSgappSetName(pokecoloGappMainDeamonHandle,"mainDeamon");
    GSgfxResetEnable();GSgfxResetSetShutdownCallback(_pokecoloShutdown);fadeInit();GSfilterInitialise(8);GSeffectInitSystem();deckInit();
    GSthreadCreate(0,1000,0x4000,1,1,_pokecoloInit);
    u64 lastTime=OSGetTime();
    for(;;) {
        GSgappUpdate();pokecoloCheckDiskTray();
        _frameTime=((OSGetTime()-lastTime)*8)/((*(u32 *)0x800000F8/4)/125000);
        lastTime=OSGetTime();++pokecoloFrameCounter;
    }
}
}
