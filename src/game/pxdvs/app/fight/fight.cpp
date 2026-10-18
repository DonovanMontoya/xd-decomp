#include <game/pxdvs/app/floor/floorPrivate.hpp>
#include <libc/string.h>
static void _fsysLoadCallbak(s32,void*,s32);
extern "C" {
s32 pokecoloGetCountryCode();
void GSresFreeResource(s32,u32);
void* GSresGetResource(s32,u32);
void GSfsysFreeCache(s32);
void GSfsysFree(s32);
void GSfsysReadIDEXWait(s32,u32,void (*)(s32,void*,s32),s32,u32);
u32 fightGSfloorGetPushDataSize();
void fightGSfloorPopData(void*,u32);
void fightGSfloorPushData(void*,u32);
void fightGSfloorFree();
void menuFightCloseAll();
static u8 fight_action[0x30];
static FloorModuleInterface _floorModuleFight;
static u8 _menuCtrlHero[0x978];
static u16 _fight_encount_data_id;
static u16 _fight_result_id;
static void* _gsthread_ptr_fight_main;
static u8 _is_fight_flag;
static u8 _old_fight_debug_menu_flag;
static u8 gOldCameraType;
u32 dbgEffLoadFsysGroupID;
extern void* UserWork;
u32 GSfloorGetCurrentFloorGroupID();
void GSthreadTerminateGroup(u32);
void cameraSetType(u8);
u8 cameraGetType();
u32 fightFloor_GetEnvSndId(u32);
void soundStop(u32,u32);
void soundOpenPlay(u32,u32,u32);
void GSmemFree(void*);
void* GSmemAlloc(u32);
void dbgMenuSetEnable(u8);
u8 dbgMenuGetEnable();
void dbgMenuClose();
void msgctrlSetValue(u32,u32);
void GSlogWrite(const char*,...);
u8 GSfloorIsPop();
void fightSeq_ClearUserWork();
void fightPokemonSetNonTrainerPokemonIsActiveFlag(u32);
void fightDataRewrite();
void battleCameraStartRandom(u32);
void fightActionFifoInit();
struct FightActionData;
extern FightActionData fight_action_data_kaisi;
void fightActionCreateAndFlowFifo(void*,u32,u32,u32,u32,FightActionData*);
u8 fightFloorIsNowEncountSnatchOnly(u32);
u8 fightFloorIsNowEncountHostEnemyPokemonKime(u32);
u8 fightFloorIsNowEncountHostPokemonKime(u32);
void fightSeqEventKurein(u32);
void fightActionDispFifoAll();
void fightMain();
void* GSthreadCreate(u32,u32,u32,u32,u32,void (*)());
void GSthreadSetName(void*,const char*);
void FloorModuleInterface_clear(FloorModuleInterface*);
void fightSetFightFlag(u8);
void fightSetFightResultId(u16);
void fightSetFightEncountDataId(u16);
u16 fightGetFightEncountDataId();
void fightSetGsthreadPtrFightMain(void*);
void fightFreeResourceID(s32 group,u32 resource);
void fightFreeResourceDeclArchive() {
    fightFreeResourceID(0x842,0x18503400);
    fightFreeResourceID(0x842,0x184e3400);
    fightFreeResourceID(0x842,0x184f3400);
    fightFreeResourceID(0x842,0x18513400);
    fightFreeResourceID(0x842,0x184b3400);
    fightFreeResourceID(0x842,0x184c3400);
    fightFreeResourceID(0x842,0x195f3400);
    fightFreeResourceID(0x842,0x184d3400);
}
void fightFreeResourceID(s32 group,u32 resource) {
    u32 localized;
    if(pokecoloGetCountryCode()==2) {
        switch(resource) {
        case 0x184b3400:localized=0x22523400;break;
        case 0x184c3400:localized=0x22533400;break;
        case 0x184d3400:localized=0x22543400;break;
        case 0x184e3400:localized=0x22553400;break;
        case 0x184f3400:localized=0x22563400;break;
        case 0x18503400:localized=0x22573400;break;
        case 0x18513400:localized=0x22583400;break;
        case 0x195f3400:localized=0x22593400;break;
        default:return;
        }
    } else localized=resource;
    GSresFreeResource(group,localized);
}
bool fightReadResourceID(s32 group,u32 resource) {
    if(group==0)group=0x842;
    if(pokecoloGetCountryCode()==2) {
        switch(resource) {
        case 0x184b3400:resource=0x22523400;break;
        case 0x184c3400:resource=0x22533400;break;
        case 0x184d3400:resource=0x22543400;break;
        case 0x184e3400:resource=0x22553400;break;
        case 0x184f3400:resource=0x22563400;break;
        case 0x18503400:resource=0x22573400;break;
        case 0x18513400:resource=0x22583400;break;
        case 0x195f3400:resource=0x22593400;break;
        default:return 0;
        }
        GSresFreeResource(group,0x22583400);
    } else GSresFreeResource(group,0x18513400);
    GSfsysFreeCache(group);
    if(GSresGetResource(group,resource))return 0;
    GSfsysReadIDEXWait(group,resource,_fsysLoadCallbak,0,resource);
    GSfsysFree(group);
    return GSresGetResource(group,resource)!=0;
}
void* fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetFightDeckGrpId(void*,u8);
void fightFreeDeck(u16 encounter) {
    void* data=fightEncountDataBiosGetPtr(encounter);
    for(u8 i=0;i<4;++i){
        switch(fightEncountDataBiosGetFightDeckGrpId(data,i)) {
        case 1:fightFreeResourceID(0x842,0x18503400);break;
        case 2:fightFreeResourceID(0x842,0x184e3400);break;
        case 3:fightFreeResourceID(0x842,0x184f3400);break;
        case 4:fightFreeResourceID(0x842,0x18513400);break;
        case 5:fightFreeResourceID(0x842,0x184b3400);break;
        case 6:fightFreeResourceID(0x842,0x184c3400);break;
        case 7:fightFreeResourceID(0x842,0x195f3400);break;
        }
    }
}
u8 fightReadDeck(u16 encounter) {
    void* data;
    u8 i;
    u8 loaded=0;
    data=fightEncountDataBiosGetPtr(encounter);
    // Unhandled deck groups retain the result from the previous iteration.
    bool result;
    for(i=0;i<4;++i){
        switch(fightEncountDataBiosGetFightDeckGrpId(data,i)) {
        case 1:result=fightReadResourceID(0x842,0x18503400);break;
        case 2:result=fightReadResourceID(0x842,0x184e3400);break;
        case 3:result=fightReadResourceID(0x842,0x184f3400);break;
        case 4:result=fightReadResourceID(0x842,0x18513400);break;
        case 5:result=fightReadResourceID(0x842,0x184b3400);break;
        case 6:result=fightReadResourceID(0x842,0x184c3400);break;
        case 7:result=fightReadResourceID(0x842,0x195f3400);break;
        }
        if(result==1)loaded=1;
    }
    return loaded;
}
void fightSetMenuCtrlHero(const void* hero){memcpy(_menuCtrlHero,hero,sizeof(_menuCtrlHero));}
void* fightGetMenuCtrlHero(){return _menuCtrlHero;}
}
static void _fsysLoadCallbak(s32,void*,s32){}
static const char* _fightGetModuleName(){return "fight";}
extern "C" FloorModuleInterface* fightGetFloorModule(){return &_floorModuleFight;}
static u32 _fightGetUID(){return 0x12;}
static u32 _fightGetStateSize(FloorStateMode mode){if(mode==2)return fightGSfloorGetPushDataSize();return 0;}
static void _fightRestoreStateData(FloorStateMode mode,void* data,u32 size){if(mode==2)fightGSfloorPopData(data,size);}
static void _fightMakeStateData(FloorStateMode mode,void* data,u32 size){if(mode==2)fightGSfloorPushData(data,size);}
extern "C" void fightCloseAllMenu(){menuFightCloseAll();}
static void _fightFree(unsigned int,FloorEnterMode mode){if(mode==1)fightGSfloorFree();}
static void _fightFinalize(unsigned int,FloorEnterMode mode){
    if(mode!=1){
        GSthreadTerminateGroup(GSfloorGetCurrentFloorGroupID());
        GSthreadTerminateGroup(GSfloorGetCurrentFloorGroupID());
        fightCloseAllMenu();
        cameraSetType(gOldCameraType);
        u32 sound=fightFloor_GetEnvSndId(0);
        if(sound)soundStop(sound,0);
        soundOpenPlay(8,0,0xff);
        if(UserWork){GSmemFree(UserWork);UserWork=0;}
        dbgMenuSetEnable(_old_fight_debug_menu_flag);
        fightSetFightFlag(0);
        fightFreeDeck(fightGetFightEncountDataId());
        fightSetFightEncountDataId(0);
        msgctrlSetValue(0x59,0x1772);
        GSlogWrite("---------- fight end !! ---------- \n");
    }
}
static void _fightInitialize(unsigned int,FloorEnterMode){
    if(GSfloorIsPop()){
        dbgMenuClose();dbgMenuSetEnable(0);return;
    }
    GSlogWrite("---------- fight start !! ---------- \n");
    fightSetFightFlag(1);
    fightReadDeck(fightGetFightEncountDataId());
    if(!UserWork){UserWork=GSmemAlloc(0x20000);fightSeq_ClearUserWork();}
    fightPokemonSetNonTrainerPokemonIsActiveFlag(1);
    fightDataRewrite();
    battleCameraStartRandom(1);
    _old_fight_debug_menu_flag=dbgMenuGetEnable();
    dbgMenuClose();dbgMenuSetEnable(0);
    fightActionFifoInit();
    gOldCameraType=cameraGetType();
    fightActionCreateAndFlowFifo(fight_action,0,0,1,0,&fight_action_data_kaisi);
    if(fightFloorIsNowEncountSnatchOnly(0)==1){fightSeqEventKurein(0);fightSeqEventKurein(1);}
    fightActionCreateAndFlowFifo(fight_action,0,0,3,5,&fight_action_data_kaisi);
    if(fightFloorIsNowEncountHostEnemyPokemonKime(0)==1)
        fightActionCreateAndFlowFifo(fight_action,0,0,4,5,&fight_action_data_kaisi);
    fightActionCreateAndFlowFifo(fight_action,0,0,3,4,&fight_action_data_kaisi);
    if(fightFloorIsNowEncountHostPokemonKime(0)==1)
        fightActionCreateAndFlowFifo(fight_action,0,0,4,4,&fight_action_data_kaisi);
    fightActionDispFifoAll();
    _gsthread_ptr_fight_main=GSthreadCreate(0x14,GSfloorGetCurrentFloorGroupID(),0x4000,1,0,fightMain);
    GSthreadSetName(_gsthread_ptr_fight_main,"fightMain");
}
extern "C" {
void fightSetFightEncountDataId(u16 id){_fight_encount_data_id=id;}
u16 fightGetFightEncountDataId(){return _fight_encount_data_id;}
void fightSetGsthreadPtrFightMain(void* thread){_gsthread_ptr_fight_main=thread;}
void fightSetFightResultId(u16 id){_fight_result_id=id;}
u16 fightGetFightResultId(){return _fight_result_id;}
void fightSetFightFlag(u8 flag){_is_fight_flag=flag;}
u8 fightIsFight(){return _is_fight_flag;}
}
struct FightVirtualDeckHeader { u8 reserved[4]; u16 floor; };
FightVirtualDeckHeader *deckDataVirtual_GetPtr(u16);
extern "C" {
FIGHT_ENCOUNT *fightEncountGetStrObj();
u16 getField__13FIGHT_ENCOUNTCFv(FIGHT_ENCOUNT *);
u8 getFightMode__13FIGHT_ENCOUNTCFv(FIGHT_ENCOUNT *);
u8 getDestroyFlag__13FIGHT_ENCOUNTCFv(FIGHT_ENCOUNT *);
u32 getRoundNo__13FIGHT_ENCOUNTCFv(FIGHT_ENCOUNT *);
u8 getTrainerKind__13FIGHT_ENCOUNTCFv(FIGHT_ENCOUNT *);
u16 getMsg__13FIGHT_ENCOUNTCFUc(FIGHT_ENCOUNT *,u8);
u8 fightEncountDataBiosGetFightKind(void *);
u16 fightEncountDataBiosGetDiskId(void *);
void fightEncountDataBiosSetFightFloorDataId(void *,u16);
u16 fightEncountDataBiosGetFightFloorDataId(void *);
s32 HSD_Rand();
void fightEncountDataBiosSetFightTrainerDataId(void *,u8,u32);
void fightEncountDataBiosSetFightKind(void *,u8);
void fightEncountDataBiosSetZenmetuFlag(void *,u8);
void fightEncountDataBiosSetSyoukaiWzxDataId(void *,u32);
u32 fightEncountDataBiosGetFightTrainerDataId(void *,u8);
void fightTrainerDB_SetSerihuMsgId(u32,u8,u16);
void fightTrainerDB_SetKindDataId(u32,u8);
extern s8 underTakerDeckRand;
void fightDataRewrite() {
    FIGHT_ENCOUNT *settings;
    void *data;
    u16 id;
    u32 trainer;
    u16 field;
    u32 mode,destroy,round;
    u8 trainerKind;
    u16 message;
    u8 messageIndex;
    u16 messages[4];
    FightVirtualDeckHeader *deck;
    u8 kind;
    settings = fightEncountGetStrObj();
    id = fightGetFightEncountDataId();
    data = fightEncountDataBiosGetPtr(id);
    kind = fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(id));
    deck = deckDataVirtual_GetPtr(fightEncountDataBiosGetDiskId(data));
    field = getField__13FIGHT_ENCOUNTCFv(settings);
    mode = getFightMode__13FIGHT_ENCOUNTCFv(settings);
    destroy = getDestroyFlag__13FIGHT_ENCOUNTCFv(settings);
    round = getRoundNo__13FIGHT_ENCOUNTCFv(settings);
    trainerKind = getTrainerKind__13FIGHT_ENCOUNTCFv(settings);
    for (u8 i=0;i<4;++i) messages[i]=getMsg__13FIGHT_ENCOUNTCFUc(settings,i);
    if ((kind==0xF || kind==0xE) && deck != 0 && deck->floor != 0) fightEncountDataBiosSetFightFloorDataId(data,deck->floor);
    if (id==0x73) {
        if (underTakerDeckRand==-1) underTakerDeckRand=(u16)HSD_Rand()%4;
        if (fightEncountDataBiosGetFightFloorDataId(data)==0x1F) {
            switch (underTakerDeckRand) {
            case 0: trainer=0x60001;break;
            case 1: trainer=0x60002;break;
            case 2: trainer=0x60003;break;
            case 3: trainer=0x60004;break;
            }
        } else if (fightEncountDataBiosGetFightFloorDataId(data)==0x21) {
            switch (underTakerDeckRand) {
            case 0: trainer=0x60005;break;
            case 1: trainer=0x60006;break;
            case 2: trainer=0x60007;break;
            case 3: trainer=0x60008;break;
            }
        }
        u16 trainerId=trainer;
        fightEncountDataBiosSetFightTrainerDataId(data,1,trainerId);
    }
    if (field!=0) fightEncountDataBiosSetFightFloorDataId(data,field);
    switch(mode) {
    case 2:fightEncountDataBiosSetFightKind(data,0x10);break;
    case 3:fightEncountDataBiosSetFightKind(data,0xC);break;
    }
    switch(destroy) {
    case 1:fightEncountDataBiosSetZenmetuFlag(data,1);break;
    case 2:fightEncountDataBiosSetZenmetuFlag(data,0);break;
    }
    if (round!=0) fightEncountDataBiosSetSyoukaiWzxDataId(data,round);
    for (messageIndex=0;messageIndex<4;++messageIndex) {
        message=messages[messageIndex];
        if (message!=0) fightTrainerDB_SetSerihuMsgId(fightEncountDataBiosGetFightTrainerDataId(data,1),messageIndex,message);
    }
    if (trainerKind!=0) fightTrainerDB_SetKindDataId(fightEncountDataBiosGetFightTrainerDataId(data,1),trainerKind);
}
}

extern "C" {
void *fightFloorGetNowPtr();
u8 fightFloor_GetFightType(u32);
s8 fightFloor_GetStatusMenuCnt(u8);
void fightFloor_SetStatusMenuCnt(u8,s8);
u8 menuIsCheck(u32);
void menuCloseCustom(u32,s32,s32);
void fightMenuCloseMsg();
struct FightServerWork { u8 reserved[7]; u8 messageState; };
extern FightServerWork ServerWork;
extern s16 msgFrame;
}
static void _fightUpdate(unsigned int,FloorEnterMode) {
    fightFloorGetNowPtr();
    fightFloor_GetFightType(0);
    u8 menuIds[4]={0x37,0x38,0x40,0x41};
    u8 menu;
    s32 next;
    for(u8 i=0;i<4;++i) {
        menu=menuIds[i];
        s8 count=fightFloor_GetStatusMenuCnt(menu);
        if(count>=0) {
            next=count-1;
            fightFloor_SetStatusMenuCnt(menu,next);
            if((s8)next<=0) {
                if(!menuIsCheck(menu)) return;
                menuCloseCustom(menu,2,0);
                fightFloor_SetStatusMenuCnt(menu,-1);
            }
        }
    }
    if(ServerWork.messageState==2) {
        if(msgFrame--<=0) {
            fightMenuCloseMsg();
            ServerWork.messageState=0;
        }
    }
}
extern "C" void fightInit() {
    fightSetFightFlag(0);
    fightSetFightResultId(0);
    fightSetFightEncountDataId(0);
    fightSetGsthreadPtrFightMain(0);
    FloorModuleInterface_clear(&_floorModuleFight);
    _floorModuleFight.pre=_fightInitialize;
    _floorModuleFight.normal=_fightUpdate;
    _floorModuleFight.post=_fightFinalize;
    _floorModuleFight.free=_fightFree;
    _floorModuleFight.saveState=_fightMakeStateData;
    _floorModuleFight.loadState=_fightRestoreStateData;
    _floorModuleFight.getStateSize=_fightGetStateSize;
    _floorModuleFight.getStateID=_fightGetUID;
    _floorModuleFight.getName=_fightGetModuleName;
}
