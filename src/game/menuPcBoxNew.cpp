#include <game/menuPcBoxNewPrivate.hpp>
#include <libc/string.h>
extern "C" {void *memcardMemAllocForSavedata();void *memcardMemFreeForSavedata(void*);void *savedataGetStatus(void*,s32);s32 gamedataGetStatus(void*,s32);void pokemonCreate(Pokemon*,u16,u32,s32);void winSeqSetMenu(s32,s32);s32 windowGetValue(s32);void winSpriteSetDisp(tagSPRITE_WORK*,bool);}
void menuPocketSetDarkPokemon(Pokemon&,f32,u16);
void menuPtSpriteWorkSetMenuItem(tagWINDOW_WORK*,tagSPRITE_WORK*,u32);
enum MENU_PCBOX_DOUGU_HIKIDASHI_MODE { PCBOX_WITHDRAW_0 };
void menuPcBoxDouguHikidashi(MENU_PCBOX_DOUGU_HIKIDASHI_MODE);
long menuPcBoxGetLastViewBox();
void menuPcBoxSetLastViewBox(long);
long relivehallGetLastViewStage();
void relivehallSetLastViewStage(long);
void menuPtPlaySe(u32);
void menuPtPlayBgm(u32);
void menuPtSaveSound(MenuPtWorkSound *);
void menuPtRestoreSound(MenuPtWorkSound *);
void menuPcBoxPokemon(CMenuGlobalState &);
void menuReliveHallExecFromPcBox(CMenuGlobalState &);
void menuHologramExecFromPcBox(CMenuGlobalState &);
class CAnt {public:static void systemInit();static void systemFree();};
extern "C" {
void GSfsysFree(u32);
void GSresFreeGroup(u32);
void GSfsysReadWait(u32);
void GSfloorPop();
void menuOpen(s32,s32);
void menuClose(s32);
void menuCloseSync(s32,s32);
void menuOpenCustom(s32,s32,...);
s32 windowGetActiveID();
u32 windowSearchID(s32);
void menuPocket2Call(s32,s32,s32);
extern u8 pcBoxSoundTbl[];
}
inline void CState::change(s32 value) {next=value;memset(work,0,0x40);}
namespace {
struct PcBoxConfig {u32 kind,title,info,items[6];};
class CmenuPcBox:public CMetaMenu {public:PcBoxConfig *config;u8 reliveLoaded,boxLoaded;u8 pad33E[2];void *backup;u32 field344,field348;MenuPtWorkSound sound;void main(CMenuGlobalState::enumCallFrom);void loop();void ctrl(tagWINDOW_WORK*);void drawItemText(tagWINDOW_WORK*,tagSPRITE_WORK*,long);void drawInfo(tagWINDOW_WORK*,tagSPRITE_WORK*);void drawTitle(tagWINDOW_WORK*,tagSPRITE_WORK*);void drawRedBar(tagWINDOW_WORK*,tagSPRITE_WORK*,long);void tutorialPokemonSetup();void tutorialPokemonRecover();virtual void drawAll() {}};
typedef char PcBoxObjectSize[sizeof(CmenuPcBox)==0x358?1:-1];
typedef char MenuGlobalStateSize[sizeof(CMenuGlobalState)==0x208?1:-1];
static CMenuGlobalState _menuGlobalState;
static CmenuPcBox _menuPcBox;
static long localWindowTable[]={0};
static PcBoxConfig _selectMenuTbl[3] = {
    {0x7A,0x353,0x3BB0,{0x3BB1,0x3BB2,0x3BB4,0,0,0}},
    {0x7B,0x353,0x3BB0,{0x3BB1,0x3BB2,0x3B70,0x3BB4,0,0}},
    {0x7B,0x37E,0x3BB6,{0x3BB7,0x3BB8,0x3BB9,0x3BBA,0,0}}
};

}

// Retail retains these entry points, including menus with no direct callers.
#pragma force_active on
u8 menuReliveHallTutorialGetIsCancelExit(){return ((u8*)&_menuGlobalState)[0x15E];}
extern "C" {
void menuReliveHallTutorialExit(){}void menuReliveHallTutorialMain(){_menuPcBox.main(CMenuGlobalState::Tutorial);}void menuReliveHallTutorialInit(){}
void menuHologramExit(){}void menuHologramMain(){_menuPcBox.main(CMenuGlobalState::Hologram);}void menuHologramInit(){}
void menuReliveHallExit(){}void menuReliveHallMain(){_menuPcBox.main(CMenuGlobalState::Relive);}void menuReliveHallInit(){}
void menuPcBoxExit(){}void menuPcBoxMain(){_menuPcBox.main(CMenuGlobalState::Pc);}void menuPcBoxInit(){}
s32 menuPcBoxSelectMenuItem(){return 0;}
s32 menuPcBoxCtrl(tagWINDOW_WORK *w){_menuPcBox.ctrl(w);return 0;}
s32 menuPcBoxItem3(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawItemText(w,s,3);return 0;}
s32 menuPcBoxItem2(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawItemText(w,s,2);return 0;}
s32 menuPcBoxItem1(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawItemText(w,s,1);return 0;}
s32 menuPcBoxItem0(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawItemText(w,s,0);return 0;}
s32 menuPcBoxInfo(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawInfo(w,s);return 0;}
s32 menuPcBoxTitle(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawTitle(w,s);return 0;}
s32 menuPcBoxBarRed3(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawRedBar(w,s,3);return 0;}
s32 menuPcBoxBarRed2(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawRedBar(w,s,2);return 0;}
s32 menuPcBoxBarRed1(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawRedBar(w,s,1);return 0;}
s32 menuPcBoxBarRed0(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawRedBar(w,s,0);return 0;}
}

#pragma force_active reset
namespace {
void CmenuPcBox::tutorialPokemonRecover(){memcpy(savedataGetStatus(0,0),backup,0x27FD0);backup=memcardMemFreeForSavedata(backup);}
void CmenuPcBox::tutorialPokemonSetup() {
    static u16 _darkPokemonTbl[] = {10, 1};
    static u16 _pokemonTbl[] = {
        0x14A, 0x173, 0x141, 0x148, 0x132, 0x151, 0x15A, 0x14F, 0x16F,
        0x14C, 0x130, 0x15F, 0x122, 0x140, 0x169, 0x18B, 0x178, 0x163
    };
    Pokemon p;
    backup = memcardMemAllocForSavedata();
    memcpy(backup, savedataGetStatus(0, 0), 0x27FD0);
    PCBOX::getPointer()->init();
    CReliveHall::getPointer()->init();
    for (u32 i = 0; i < 18; i++) {
        pokemonCreate(&p, _pokemonTbl[i], 25, gamedataGetStatus(0, 1));
        if (i < 2) {
            menuPocketSetDarkPokemon(p, 0.5f, _darkPokemonTbl[i]);
        }
        PCBOX::getPointer()->setPokemon(&p, 0, i);
    }
}

void CmenuPcBox::ctrl(tagWINDOW_WORK *w){switch(w->mode){case 0:if(!w->sub){winSeqSetMenu(w->id,0x1C4);w->sub=1;}break;case 3:if(!w->sub){winSeqSetMenu(w->id,0x1C8);w->sub=1;}break;}}
void CmenuPcBox::drawItemText(tagWINDOW_WORK*,tagSPRITE_WORK *s,long index){s->message=config->items[index];}
void CmenuPcBox::drawInfo(tagWINDOW_WORK*,tagSPRITE_WORK *s){s->message=config->info;}
void CmenuPcBox::drawTitle(tagWINDOW_WORK *w,tagSPRITE_WORK *s){menuPtSpriteWorkSetMenuItem(w,s,config->title);}
void CmenuPcBox::drawRedBar(tagWINDOW_WORK *w,tagSPRITE_WORK *s,long index){s32 value=windowGetValue(w->id);winSpriteSetDisp(s,index==value);}



void CmenuPcBox::loop()
{
    s32 *selected;
    s32 selectedItem,selectedMessage,toolItem,toolMessage,previousState;
    for (;;) {
    base.state.update();
    switch (base.state.current) {
    case 0:
        base.state.change(1);
        menuOpen(0x79, 0);
        break;
    case 1:
        if (CReliveHall::isOpen() != 0) {
            config = &_selectMenuTbl[1];
        } else {
            config = _selectMenuTbl;
        }
        base.state.change(4);
        break;
    case 2:
        field348 = 0;
        config = &_selectMenuTbl[2];
        base.state.change(4);
        break;
    case 3:
        config = &_selectMenuTbl[2];
        base.state.change(4);
        break;
    case 4:
        if ((s32) base.state.previous == 1) {
            selected = (s32 *)&field344;
        } else {
            selected = (s32 *)&field348;
        }
        menuOpenCustom(config->kind, windowGetActiveID(), selected, 0, 1, 0);
        *selected = windowGetValue(config->kind);
        menuClose(config->kind);
        menuCloseSync(config->kind, 1);
        if ((s32) base.state.previous == 1) {
            selectedItem = *selected;
            if (selectedItem != -1) {
                selectedMessage = config->items[selectedItem];
                switch (selectedMessage) {
                case 0x3BB1:
                    systemFadeOutSetAndWait(-1.0f);
                    base.state.change(5);
                    break;
                case 0x3BB2:
                    base.state.change(2);
                    break;
                case 0x3B70:
                    systemFadeOutSetAndWait(-1.0f);
                    base.state.change(6);
                    break;
                case 0x3BB4:
                    base.state.change(0xB);
                    break;
                }
            } else {
                base.state.change(0xB);
            }
        } else {
            toolItem = *selected;
            if (toolItem != -1) {
                toolMessage = config->items[toolItem];
                switch (toolMessage) {
                case 0x3BB7:
                    base.state.change(8);
                    break;
                case 0x3BB8:
                    base.state.change(9);
                    break;
                case 0x3BB9:
                    base.state.change(0xA);
                    break;
                case 0x3BBA:
                    base.state.change(1);
                    break;
                }
            } else {
                base.state.change(1);
            }
        }
        break;
    case 5:
        if ((s32) base.state.previous == 6) {
            _menuGlobalState.previous = 2;
        } else {
            _menuGlobalState.previous = 0;
        }
        if ((u8) boxLoaded == 0) {
            GSfsysReadWait(0x16);
            boxLoaded = 1U;
        }
        localWindowDeleteAll();
        if (windowSearchID(0x79) != 0U) {
            menuClose(0x79);
        }
        menuPcBoxPokemon(_menuGlobalState);
        localWindowCreateAll();
        if ((u8) _menuGlobalState.tutorialExit != 0) {
            base.state.change(0xB);
        } else if ((s32) _menuGlobalState.current == 2) {
            base.state.change(6);
        } else {
            systemFadeInKick();
            base.state.change(0);
        }
        break;
    case 6:
        previousState = base.state.previous;
        if (previousState == 5) {
            _menuGlobalState.previous = 1;
        } else if (previousState == 7) {
            _menuGlobalState.previous = 3;
        } else {
            _menuGlobalState.previous = 0;
        }
        if ((u8) reliveLoaded == 0) {
            GSfsysReadWait(0x824);
            reliveLoaded = 1U;
        }
        localWindowDeleteAll();
        if (windowSearchID(0x79) != 0U) {
            menuClose(0x79);
        }
        menuPtPlayBgm(0x469);
        menuReliveHallExecFromPcBox(_menuGlobalState);
        localWindowCreateAll();
        if ((u8) _menuGlobalState.tutorialExit != 0) {
            base.state.change(0xB);
        } else if ((s32) _menuGlobalState.current == 1) {
            base.state.change(5);
        } else if ((s32) _menuGlobalState.current == 4) {
            base.state.change(0xB);
        } else if ((s32) _menuGlobalState.from == 1) {
            base.state.change(0xB);
        } else if ((s32) _menuGlobalState.from == 2) {
            base.state.change(7);
        } else {
            menuPtRestoreSound(&sound);
            systemFadeInKick();
            base.state.change(0);
        }
        break;
    case 7:
        _menuGlobalState.previous = 0;
        localWindowDeleteAll();
        menuHologramExecFromPcBox(_menuGlobalState);
        localWindowCreateAll();
        if ((s32) _menuGlobalState.current == 2) {
            base.state.change(6);
        } else {
            base.state.change(0xB);
        }
        break;
    case 8:
        systemFadeOutSetAndWait(-1.0f);
        localWindowDeleteAll();
        menuClose(0x79);
        menuPcBoxDouguHikidashi((MENU_PCBOX_DOUGU_HIKIDASHI_MODE)0);
        menuOpen(0x79, 0);
        localWindowCreateAll();
        systemFadeInKick();
        base.state.change(3);
        break;
    case 10:
        systemFadeOutSetAndWait(-1.0f);
        localWindowDeleteAll();
        menuClose(0x79);
        menuPcBoxDouguHikidashi((MENU_PCBOX_DOUGU_HIKIDASHI_MODE)1);
        menuOpen(0x79, 0);
        localWindowCreateAll();
        systemFadeInKick();
        base.state.change(3);
        break;
    case 9:
        systemFadeOutSetAndWait(-1.0f);
        GSfsysReadWait(0x66F);
        localWindowDeleteAll();
        menuClose(0x79);
        menuOpen(0x8A, 0);
        systemFadeInKick();
        systemFadeWaitToEnd();
        menuPocket2Call(4, 0, 0);
        menuClose(0x8A);
        menuOpen(0x79, 0);
        localWindowCreateAll();
        GSfsysFree(0x66F);
        GSresFreeGroup(0x66F);
        systemFadeInKick();
        base.state.change(3);
        break;
    case 11:
        systemFadeOutSetAndWait(-1.0f);
        if(windowSearchID(0x79)!=0) menuClose(0x79);
        return;
    }
    }
}

void CmenuPcBox::main(CMenuGlobalState::enumCallFrom from)
{
    CAnt::systemInit();
    base.time1=0;
    base.time0=0;
    base.state.init();
    base.fadeTime=0;
    base.fadeState=0;
    memset(base.windows,0,0x100);
    memset(base.windowFuncs,0,0x100);
    base.windowTable=defautlLocalWindowOpenTable;
    if(pcBoxSoundTbl!=0) memcpy(base.sound,pcBoxSoundTbl,0x14);
    base.tutorialActive=0;
    base.unk32C=0;
    base.unk32E=0;
    memset(base.keyInfo,0,0x1A);
    base.repeatCount=0;
    base.lastKey=0;
    config=0;
    reliveLoaded=0;
    boxLoaded=0;
    field344=0;
    field348=0;
    memset(&sound,0,0xC);
    menuPtSaveSound(&sound);
    localWindowSetTable(localWindowTable);
    localWindowCreateAll();
    _menuGlobalState.init();
    _menuGlobalState.from=from;
    CReliveHall *hall=CReliveHall::getPointer();
    hall->allocMakeBackup();
    switch(_menuGlobalState.from) {
    case CMenuGlobalState::Pc:
        menuPtPlaySe(0x447);
        boxLoaded=1;
        base.state.change(0);
        loop();
        localWindowDeleteAll();
        if(reliveLoaded){GSfsysFree(0x824);GSresFreeGroup(0x824);}
        break;
    case CMenuGlobalState::Relive:
        reliveLoaded=1;
        base.state.change(6);
        loop();
        localWindowDeleteAll();
        if(boxLoaded){GSfsysFree(0x16);GSresFreeGroup(0x16);}
        menuPtRestoreSound(&sound);
        break;
    case CMenuGlobalState::Tutorial: {
        long stage=relivehallGetLastViewStage();
        long box=menuPcBoxGetLastViewBox();
        menuPcBoxSetLastViewBox(0);
        relivehallSetLastViewStage(0);
        tutorialPokemonSetup();
        _menuGlobalState.tutorial=1;
        reliveLoaded=1;
        base.state.change(6);
        loop();
        localWindowDeleteAll();
        if(boxLoaded){GSfsysFree(0x16);GSresFreeGroup(0x16);}
        tutorialPokemonRecover();
        menuPcBoxSetLastViewBox(box);
        relivehallSetLastViewStage(stage);
        menuPtRestoreSound(&sound);
        break;
    }
    case CMenuGlobalState::Hologram:
        base.state.change(7);
        loop();
        localWindowDeleteAll();
        if(reliveLoaded){GSfsysFree(0x824);GSresFreeGroup(0x824);}
        if(boxLoaded){GSfsysFree(0x16);GSresFreeGroup(0x16);}
        break;
    }
    hall->checkWithBackupSet();
    CAnt::systemFree();
    GSfloorPop();
}
}
