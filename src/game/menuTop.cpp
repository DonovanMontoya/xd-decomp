#include <game/menuPcBoxPokemonLayout.hpp>
extern "C" {
u32 FlashSystemGetFrameFromLabel(u32,const char*);u32 FlashSystemGetNowFrame(u32);void FlashSystemPlayAndWait(u32,const char*,const char*);void FlashSystemSetLoopFlag(u32,s32);void FlashSystemSetNowFrameLabel(u32,const char*);void FlashSystemSetPlayFrameLabel(u32,const char*,const char*);u32 GSmsgGetRect(u32);void GSmsgPrint2(s32,s32,s32,u32,u32);void GSthreadSwitch();s32 darkPokemonGetReliveNum();s32 darkPokemonGetSnatchSuccessNum();void fadeCheck(s32);void fadeSet(s32,f32);void floorClearReturnPoint();void floorReturnSavePoint();void floorSetContinueMode(s32);void fn_800A39E4();void fn_800A3A1C();s32 heroGetObjID(s32);void heroMoveSyncWithHero();void menuCloseCustom(s32,u32,s32);void menuColosseumBattle(s32);u8 menuIsCheck(s32);MENU_ITEM_dd_ *menuItemBiosGetPtr(s32,s16);void menuModelAdjustCamera(MENU_MODEL*);u8 menuModelCheck(MENU_MODEL*,s32);void menuModelInit(MENU_MODEL*,s16,s16);void menuModelLoad(MENU_MODEL*,s32);void menuModelRender(MENU_MODEL*);void menuModelSetAngle(MENU_MODEL*,f32*);void menuModelSetMotion(MENU_MODEL*,s32);void menuModelSetSize(MENU_MODEL*,s16,s16,s16,s16);void menuModelSetZoom(MENU_MODEL*,f32);void menuModelTerm(MENU_MODEL*);void menuOpen(s32,s32);s32 menuOpenCustom(s32,s32,void*,s32,s32,s32,...);s8 menuSubOpenYesNo(s32,s32,s32,s32);void menuTitleBattlePreReadCheck();void menuTitleCursorAnime(tagWINDOW_WORK*,tagSPRITE_WORK*);void menuTitleCursorAnimeMain();s16 menuTitleGetSelect(s32);void menuTitleOpenSelectAnime();void menuTitlePlayBGM();void msgctrlSetValue(s32,s32);void *peopleInfoBiosGetPtr(u32);void peopleInfoBiosGetMotion(void*,s32,s32*,s32*);u32 pokecoloGetPlayTimeValue();s32 pokecoloGetRomVersion();void pokecoloSetPlayTime(f64);void pokecoloStartCountPlayTime(s32);void savedataCreate(void*,u16*);void scriptModelClose(s32);u32 soundGetBGMID();void soundOpenPlay(u32,u32,u32);void winMsgClose(s32);void winMsgOpen(s32,u32,s32,s32);void winSeqSetMenu(s32,s32);void winSpriteSetDisp(tagSPRITE_WORK*,s32);s32 windowGetActiveID();tagWINDOW_WORK *windowSearchID(s32);s32 menuTop();
}
struct MenuTopWork{s32 selected;s32 state;u8 battle;u8 pad[3];s32 battleSelect;};
static MenuTopWork _menuTopWork;
static MENU_MODEL _menuTopMenuModel;
static s32 _menuTopSelectCursor;
s32 _menuTopResID;
static s32 _menuTopMsgTable[5]={0x42E2,0x42E1,0x444E,0x42E3,0x42E6};
static s32 _menuTopMsgTableBattleSelect[3]={0x42E4,0x42E5,0xAF};
static void _menuTopClose(s32 id){menuCloseCustom(id,0,1);}
static void _menuTopClose2(s32 id,u32 flags){if(menuIsCheck(id)==1)menuCloseCustom(id,flags,1);}
static void _menuTopInitPokemon(s16 x,s16 y){((void(*)(MENU_MODEL*,s32,s32))menuModelInit)(&_menuTopMenuModel,x,y);}
static void _menuTopExitPokemon(){menuModelTerm(&_menuTopMenuModel);}
static void _menuTopLoadPokemon(){s32 a,b;menuModelLoad(&_menuTopMenuModel,heroGetObjID(1));menuModelCheck(&_menuTopMenuModel,1);peopleInfoBiosGetMotion(peopleInfoBiosGetPtr(0x16C90400),1,&a,&b);menuModelSetMotion(&_menuTopMenuModel,a);}
static void _menuTopExit(){_menuTopClose2(0x116,2);scriptModelClose(_menuTopResID);}
static void _menuTopInit(){_menuTopWork.selected=_menuTopSelectCursor;_menuTopWork.state=0;_menuTopWork.battleSelect=0;}
static void _menuTopSetLastCursor(){s32 n=_menuTopWork.selected;if(n>=5 || n<0)n=0;_menuTopSelectCursor=n;}
static void _menuTopNewGame(u16 *name){savedataCreate(0,name);pokecoloStartCountPlayTime(1);pokecoloSetPlayTime(0.0);}
static s32 _menuTopLoadCheck(){s32 ret;s32 relive;s32 time;time=pokecoloGetPlayTimeValue();relive=darkPokemonGetReliveNum();ret=darkPokemonGetSnatchSuccessNum();FlashSystemSetPlayFrameLabel(0x22063000,"start","end");FlashSystemSetLoopFlag(0x22063000,0);FlashSystemSetNowFrameLabel(0x22063000,"start");msgctrlSetValue(0x4C,time);msgctrlSetValue(0x2F,ret);msgctrlSetValue(0x30,relive);menuOpen(0xDB,0);winMsgOpen(1,0x42EE,0,1);if(menuSubOpenYesNo(0,0x1C2,0xC0,1)==0){heroMoveSyncWithHero();floorSetContinueMode(1);floorClearReturnPoint();floorReturnSavePoint();ret=100;pokecoloStartCountPlayTime(1);}else{ret=1;pokecoloStartCountPlayTime(1);}fn_800A3A1C();_menuTopExitPokemon();_menuTopClose(0xDB);winMsgClose(1);fadeCheck(1);return ret;}
extern "C" {
void menuTopOpenFlashBack(){menuOpen(0x119,0);}
void menuTopSelectCtrl(tagWINDOW_WORK *w){u8 *data=(u8*)w->parameters[0];switch(w->phase){case 0:if(!w->step){if(*data)winSeqSetMenu(w->menu,0x24);w->step=1;}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x17B);w->step=1;}break;}}
void menuTopBattleSelectCtrl(tagWINDOW_WORK *w){menuTitleCursorAnimeMain();switch(w->phase){case 0:if(!w->step){winSeqSetMenu(w->menu,0x24);w->step=1;}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x17B);w->step=1;}break;}}
void menuTopPlayToolBGM(){if(soundGetBGMID()!=0x568)soundOpenPlay(0x568,0,255);}
void menuTopExit(){_menuTopExit();}
void menuTopMain(){menuTop();}
void menuTopInit(){_menuTopInit();}
u8 menuTopGetBattleMode(){return _menuTopWork.battle;}
s32 menuTopGetBattleSelectMode(){return _menuTopWork.battleSelect;}
void menuTopSetBattleSelectMode(s32 mode){_menuTopWork.battleSelect=mode;}
void menuTopSetInitCursor(s32 n){_menuTopSelectCursor=n;}
void menuTopHookMssageWindow(tagWINDOW_WORK *w){u32 value=*(u32*)&w->first;if(pokecoloGetRomVersion()!=1){s16 selected=((s16*)&value)[1];if(selected>=0){s16 sel=menuTitleGetSelect(selected);GSmsgPrint2(w->layer,0,-8,0xFFFFFF00|w->alpha,_menuTopMsgTable[sel]);}}}
void menuTopHookMssageBattleSelectWindow(tagWINDOW_WORK *w){u32 value=*(u32*)&w->first;s16 selected=((s16*)&value)[1];if(selected>=0)GSmsgPrint2(w->layer,0,-8,0xFFFFFF00|w->alpha,_menuTopMsgTableBattleSelect[selected]);}
void fn_8002F668(tagWINDOW_WORK *w,tagSPRITE_WORK *s,u32 msg){u32 rect=GSmsgGetRect(msg);MENU_ITEM_dd_ *p=menuItemBiosGetPtr(w->menu,s->id);s32 width=*(s16*)((u8*)p+0xA)-(s16)(rect>>16);s32 height=*(s16*)((u8*)p+0xC)-(s16)(u16)rect;GSmsgPrint2(w->layer,width/2,height/2,0xFFFFFF00|w->alpha,msg);}
void menuTopHook(tagWINDOW_WORK *w,tagSPRITE_WORK *s){u32 value=*(u32*)&w->first;switch(s->id){case 0x70:if(((s16*)&value)[1]==0){menuTitleCursorAnime(w,s);winSpriteSetDisp(s,1);}else winSpriteSetDisp(s,0);break;case 0x71:if(((s16*)&value)[1]==1){menuTitleCursorAnime(w,s);winSpriteSetDisp(s,1);}else winSpriteSetDisp(s,0);break;case 0x72:if(((s16*)&value)[1]==2){menuTitleCursorAnime(w,s);winSpriteSetDisp(s,1);}else winSpriteSetDisp(s,0);break;case 0x76:fn_8002F668(w,s,0x445A);break;case 0x77:fn_8002F668(w,s,0x4459);break;}}
void menuTopLoadHook(){struct Rect{s16 x,y;}a={250,30},b={320,400};f32 angle[3];angle[0]=0;angle[1]=-0.2f;angle[2]=0;if(!menuModelCheck(&_menuTopMenuModel,0)){menuModelSetSize(&_menuTopMenuModel,a.x,a.y,b.x,b.y);menuModelAdjustCamera(&_menuTopMenuModel);menuModelRender(&_menuTopMenuModel);menuModelSetAngle(&_menuTopMenuModel,angle);menuModelSetZoom(&_menuTopMenuModel,1.5f);}}
void __sinit_menuTop_cpp(){}
}

extern "C" {
void GScharMakeFromSJIS(u16 *,const char *);void cursorBiosInit();void floorLink(s32,s32);
u32 gamedatasaveGetStatus(s32,s32);u8 memcardIsMemCardValid();u8 menuItemBiosGetSelectFlag(s32,s32);
void menuItemBiosSetSelectFlag(s32,s16,s32);void menuNameEntryGetLastName(u16 *);void menuNameEntryOpen(s32,s32);
void menuPokemonInitWork();void menuTitleBattleSelectFree();void menuTitleCloseSelectAnime();
void menuTitleOpenMenu();void menuTitleOpenSelectAnime2();void menuTitleOption();void menuTitlePreReadWait();
void menuTitleSetSelect(s32,s16);void menuTitleSetStartStatus(s32);
}
static s32 _menuTopSelectBattle();

extern "C" s32 menuTop(void) {
    u16 sp48[20];
    u16 sp20[20];
    s8 sp8;
    u32 var_r4;
    s16 temp_r0;
    s32 *var_r27;
    s32 var_r27_3;
    s16 var_r26;
    s16 var_r26_2;
    s16 var_r27_2;
    s32 var_r5;
    s16 selection;
    s32 *var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r29 = 0;
    sp8 = 1;
    var_r28 = 1;
    menuTopInit();
    _menuTopWork.state = 1;
    _menuTopWork.battle = 0;
    do {
        switch (var_r29) {
        case 0x0:
            var_r29 = 1;
            break;
        case 0x1: {
            _menuTopWork.state = 1;
            s32 menuItems[5]={0x44,0x45,0x46,0x47,0x48};
            var_r30 = menuItems;
            var_r27 = var_r30;
            var_r26 = 0;
            while (var_r26 < 5) {
                menuItemBiosSetSelectFlag(0x116, (s16) *var_r27, 1);
                var_r27 += 1;
                var_r26 += 1;
            }
            if (pokecoloGetRomVersion() == 1) {
                menuItemBiosSetSelectFlag(0x116, 0x44, 0);
                menuItemBiosSetSelectFlag(0x116, 0x46, 0);
                menuItemBiosSetSelectFlag(0x116, 0x47, 0);
            }
            var_r26_2 = 0;
            var_r27_2 = 0;
            while (var_r27_2 < 5) {
                if (menuItemBiosGetSelectFlag(0x116, *var_r30) != 0) {
                    menuTitleSetSelect(var_r26_2++, var_r27_2);
                }
                var_r30 += 1;
                var_r27_2 += 1;
            }
            var_r5 = menuOpenCustom(0x116, windowGetActiveID(), &_menuTopWork, 0, 1, 1, &sp8);
            sp8 = 0;
            if (var_r5 >= 0) {
                selection = menuTitleGetSelect(var_r5);
                var_r5 = selection;
                _menuTopWork.selected = (s32) var_r5;
            }
            if (var_r5 < 0) {
                _menuTopWork.selected = -1;
            }
            if (var_r5 == 0) {
                var_r29 = 5;
                goto block_43;
            }
            switch ((s32) _menuTopWork.selected) {
            case 2:
                if (_menuTopSelectBattle() >= 0) {
                    var_r29 = 0x64;
                    _menuTopWork.battle = 1;
                } else {
                    _menuTopWork.battle = 0;
                }
                goto select_done;
            case 1:
                var_r29 = 2;
                break;
            case 0:
                break;
            case 3:
                var_r29 = 4;
                _menuTopWork.state = 4;
                break;
            default:
                menuTitleSetStartStatus(1);
                var_r29 = 0x64;
                break;
            }
block_43:
            fadeCheck(1);
select_done:
            break;
        }
        case 0x5:
            _menuTopClose(0x116);
            menuTitleCloseSelectAnime();
            if (pokecoloGetRomVersion() == 1) {
                var_r27_3 = 0;
            } else {
                if (gamedatasaveGetStatus(0, 4) != 0U) {
                    var_r4 = 0x8B;
                } else {
                    var_r4 = 0x42D9;
                }
                winMsgOpen(2, var_r4, 1, 1);
                _menuTopWork.state = 5;
                var_r27_3 = menuSubOpenYesNo(0, 0x3C, 0xA6, 1);
                winMsgClose(1);
            }
            if (var_r27_3 == 0) {
                menuTopExit();
                menuTitleBattlePreReadCheck();
                menuNameEntryOpen(0, 0);
                menuNameEntryGetLastName(sp48);
                if (sp48[0] != 0) {
                    cursorBiosInit();
                    _menuTopNewGame(sp48);
                    heroMoveSyncWithHero();
                    soundOpenPlay(8, 0x3E8, 0xFF);
                    floorLink(0xB6, 0);
                    var_r29 = 0x64;
                } else {
                    var_r29 = 1;
                    menuTitleOpenMenu();
                    menuTitleOpenSelectAnime2();
                }
            } else {
                var_r29 = 1;
                sp8 = 1;
                menuTitleOpenSelectAnime();
            }
            break;
        case 0x2:
            if (pokecoloGetRomVersion() == 1) {
                GScharMakeFromSJIS(sp20, "MICHAEL");
                cursorBiosInit();
                menuPokemonInitWork();
                _menuTopNewGame(sp20);
                soundOpenPlay(8, 0x3E8, 0xFF);
                floorLink(0x47, 0);
                var_r29 = 0x64;
            } else {
                pokecoloStartCountPlayTime(0);
                if (gamedatasaveGetStatus(0, 4) != 0U) {
                    var_r29 = 3;
                } else {
                    _menuTopClose(0x116);
                    menuTitleCloseSelectAnime();
                    if (memcardIsMemCardValid() == 0) {
                        winMsgOpen(2, 0x82, 1, 0);
                    } else {
                        winMsgOpen(2, 0x98, 1, 0);
                    }
                    winMsgClose(1);
                    var_r29 = 1;
                    menuTitleOpenMenu();
                    menuTitleOpenSelectAnime();
                }
            }
            break;
        case 0x3:
            _menuTopClose(0x116);
            menuTitleCloseSelectAnime();
            fadeSet(3, 0.5f);
            fadeCheck(1);
            _menuTopClose(0x11);
            _menuTopInitPokemon(0x280, 0x1E0);
            menuTitlePreReadWait();
            _menuTopLoadPokemon();
            if (_menuTopLoadCheck() == 0) {
                cursorBiosInit();
                menuTitleBattleSelectFree();
            } else {
                var_r29 = 1;
                menuTitleOpenMenu();
                menuTitleOpenSelectAnime2();
                fadeSet(2, 0.5f);
            }
            break;
        case 0x4:
            _menuTopClose(0x116);
            menuTitleCloseSelectAnime();
            fadeSet(3, 0.5f);
            fadeCheck(1);
            _menuTopClose(0x11);
            menuTitleOption();
            fadeCheck(1);
            var_r29 = 1;
            _menuTopWork.state = 1;
            menuTitleOpenMenu();
            menuTitleOpenSelectAnime2();
            fadeSet(2, 0.5f);
            break;
        case 0x64:
            _menuTopSetLastCursor();
            var_r28 = 0;
            break;
        }
    } while (var_r28 != 0);
    menuTopExit();
    return _menuTopWork.selected;
}

static s32 _menuTopSelectBattle(void) {
    s32 sp8;
    u8 var_r27;
    s32 var_r29;
    u32 temp_r29;
    u32 temp_r31;
    tagWINDOW_WORK *temp_r3;
    tagWINDOW_WORK *temp_r3_2;

    var_r27 = 1;
    menuTopSetBattleSelectMode(0);
    menuTopOpenFlashBack();
    FlashSystemSetLoopFlag(0x200A3000, 0);
    FlashSystemSetPlayFrameLabel(0x200A3000, "top_start", "top_end");
    FlashSystemSetNowFrameLabel(0x200A3000, "top_start");
    temp_r29 = FlashSystemGetFrameFromLabel(0x200A3000, "top_end");
    do {
        temp_r31 = FlashSystemGetNowFrame(0x200A3000);
        GSthreadSwitch();
    } while (temp_r31 < temp_r29);
    menuTopPlayToolBGM();
    do {
        sp8 = menuTopGetBattleSelectMode();
        var_r29 = menuOpenCustom(0x118, windowGetActiveID(), &sp8, 0, 1, 0);
        switch (var_r29) {
        case 0:
            _menuTopClose2(0x118, 2);
            _menuTopClose2(0x116, 2);
            _menuTopClose2(0x11, 2);
            menuTitleBattlePreReadCheck();
            menuColosseumBattle(1);
            temp_r3 = windowSearchID(0x119);
            if (temp_r3 != NULL) {
                *((s8 *)temp_r3+9) = 0;
            }
            FlashSystemPlayAndWait(0x200A3000, "1back_start", "1back_end");
            break;
        case 1:
            _menuTopClose2(0x118, 2);
            _menuTopClose2(0x116, 2);
            _menuTopClose2(0x11, 2);
            menuTitleBattlePreReadCheck();
            menuColosseumBattle(0);
            temp_r3_2 = windowSearchID(0x119);
            if (temp_r3_2 != NULL) {
                *((s8 *)temp_r3_2+9) = 0;
            }
            FlashSystemPlayAndWait(0x200A3000, "2back_start", "2back_end");
            break;
        default:
            var_r29 = -1;
            fadeSet(3, 0.5f);
            fadeCheck(1);
            _menuTopClose(0x119);
            _menuTopClose(0x118);
            fn_800A39E4();
            menuOpenCustom(0x11, windowGetActiveID(), NULL, 0, 0, 0);
            menuTitleOpenSelectAnime();
            menuTitlePlayBGM();
            fadeSet(2, 0.5f);
            var_r27 = 0;
            break;
        }
    } while (var_r27 != 0);
    return var_r29;
}
