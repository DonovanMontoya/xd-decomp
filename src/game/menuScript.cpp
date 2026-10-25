#include <game/menuScriptLayout.hpp>

struct FLAGETC;
extern "C" {
void GSgfxVideoSetLockFrameRate(s32);
void menuOffScreenSetPriority(s32);
void menuPdaSetModelPointer(void);
void menuPdaModelVisibility(u32, bool);
void menuPdaAddFunc(void);
void menuPdaScript(u8);
void menuPdaReleaseModelPointer(void);
void GSmodelAllPauseAnimation(void);
void GSmodelAllUnpauseAnimation(void);
void GSfloorPop(void);
void GSfloorPush(s32);
void GSsndPlayNow(u32);
void cameraPlayAnime(s32, u32, s32, f32);
u8 pokemonCheckValid(Pokemon *);
u16 pokemonBiosGetDarkpokemonDataId(Pokemon *);
u8 darkPokemonBiosGetReliveFlag(u16);
void *savedataGetStatus(s32, s32);
Pokemon *heroBiosGetPokemonPtr(void *, u16);
void menuClose(s32);
s32 menuOpen(s32, s32);
void menuCloseSync(s32, s32);
void menuSetPosition(s32, s32, s32);
void GSflagOn(void *);
void GSfsysReadWait(s32);
void GSresFreeGroup(s32);
void GSthreadSwitch(void);
void floorWaitForChange(void);
void menuPdaMailListSortExit(void);
s32 menuPdaMailListSortInit(s32);
void menuPdaMailXDScript(void);
void menuPdaZoomIn(void);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
void menuCloseCustom(s32, s32, s32);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
void __dla__FPv(void *);
extern s32 *wazaoshie_data_number;
extern s32 *tutorialdata_number;
extern u16 *tutorialdata;
struct FLAGETC {
    u8 pad0[8];
    u32 value;
    u8 pad[0x14];
};
extern FLAGETC *flag_etc;
u32 GSfloorGetCurrent(void);
u16 *floorGetPlaceName(s32);
void msgctrlSetValue(s32, u32);
void GSresFreeGroup(s32);
void *fightEncountDataBiosGetPtr(s32);
void fightEncountDataBiosSetDiskId(void *, u16);
u8 GSgfxVideoGetVsyncRate(void);
void menuCreateOffScreen(f32, f32);
void menuOffScreenCheckEnable(s32);
void menuReleaseOffScreen(f32);
void *mailGetOpenFlag(s32);
void GSflagSet(void *, s32);
void floorSetFadeScript(s32, s32);
void *pokemonBiosGetNicknamePtr(void *);
void darkPokemonBiosSetInformationFlag(u16, s32);
void *__nwa__FUl(u32);
u32 pokemonBiosGetPokemonDataId(Pokemon *);
void *pokemonDataBiosGetPtr(u32);
void *memset(void *, int, u32);
u8 pokemonDataBiosGetGetWazaLevel(void *, u16);
u16 pokemonDataBiosGetGetWazaDataId(void *, u16);
u8 pokemonBiosGetLevel(Pokemon *);
void *wazaDataBiosGetPtr(u16);
s32 wazaDataBiosGetName(void *);
u8 wazaDataBiosGetPp(void *);
u8 wazaDataBiosGetZokuseiDataId(void *);
s16 wazaDataBiosGetIryoku(void *);
u8 wazaDataBiosGetAvg(void *);
s32 wazaDataBiosGetDoc(void *);
u32 GSflagGet(s32);
u8 GSflagTest(void *, u16);
void winSeqSetMenu(s32, s32);
void menuSetStatus(s32, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void windowDrawSprite(s32, s32, tagWINDOW_WORK *, s32, s32, s32);
void windowDrawSprite2(s32, s32, s16, s16, u32, tagWINDOW_WORK *, s32, s32, s32);
void *heroGetStatus(s32, s32, s32);
u32 GSmsgGetRect(u32);
void *windowGetKeyInfo(void);
u32 zokuseiGetPokemonSpriteID(void *, s32);
u8 pokemonDataBiosGetTokuseiDataId(void *, s32);
void *pokemonTokuseiDataBiosGetPtr(u8);
u32 pokemonTokuseiDataBiosGetName(void *);
u32 pokemonDataBiosGetName(void *);
void winSpriteSetDisp(tagSPRITE_WORK *, bool);
u16 windowGetKeyRepeat(void);
u16 *GSmsgGetGSchar(s32);
void GSmsgPrint2(s32, s32, s32, s32, u32);
void *menuDataBiosGetPtr(s32);
}

extern "C" CURSOR cursorBiosGetPos(s32);
extern "C" void cursorBiosSetPos(s32, CURSOR *);


struct WAZAOSHIE_ENTRY {
    u16 id;
    u16 pad;
    s32 floorIndex;
    void *flag;
};
extern WAZAOSHIE_ENTRY *wazaoshie_data;

enum pdaAddFuncDef { PDA_ADD_FUNC_0 };

struct WAZAOSHIEDEF {
    u16 id;
    u32 name;
    u8 pp;
    u8 type;
    s16 power;
    u8 accuracy;
    u32 doc;
    u8 released;
};
static WAZAOSHIEDEF _wazawork;
static u16 _tempwazaid[0x15];


static u16 _WazaNum = 3;
static s32 _tutorialSelect = -1;

static WAZAOSHIEDEF *_wazalist;
static s32 _menuScriptWork;
static s32 _PdaAddFunc;
static s32 _menuScriptMailID;
static u8 _menuPdaMailOpenFlag;
static u16 _worldmapnum;
static u8 _mapFlag;
static u8 _wazaFlag;


extern "C" void menuScriptSetMailOpen(u8);

#define WIN_ALPHA(w) (((u8 *)&(w)->color90)[3])

extern "C" void fn_8005DE84(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    const u16 ids[5] = {0x4EF, 0x4F2, 0x4F3, 0x4F4, 0x4F5};
    const s32 msgs[5] = {0x13D6, 0x13D5, 0x13D4, 0x1492, 0x1491};
    s16 i;
    for (i = 0; i < 5; i++) {
        if ((u16)sprite->id == ids[i]) {
            u16 *str = GSmsgGetGSchar(msgs[i]);
            msgctrlSetValue(0x37, (u32)str);
            GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, 0, WIN_ALPHA(win) | ~0xFF, 0x4277);
            break;
        }
    }
}

struct POKEMON_DATA_dd_;
static void _menuScriptTokuseiSetumei(tagWINDOW_WORK *, tagSPRITE_WORK *, CURSOR *, POKEMON_DATA_dd_ *);

struct MENU_ITEM_dd_ {
    u8 reserved[6];
    s16 x,y,width,height;
};
extern "C" MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, s16);
extern "C" u32 GSmsgGetCharLength(u16 *);
extern "C" void *pokemonTokuseiDataBiosGetDoc(void *);


extern "C" void menuScriptEeveeHook(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    CURSOR c;
    u16 evo[5] = {0x86, 0x87, 0x88, 0xC5, 0xC4};
    void *data;
    *(s32 *)&c = *(s32 *)&win->pos;
    data = pokemonDataBiosGetPtr(evo[c.selected]);
    switch (sprite->id) {
    case 0x4EE:
        if (c.selected >= 3) {
            winSpriteSetDisp(sprite, true);
            msgctrlSetValue(0x2D, c.selected == 3 ? 0x205 : 0x204);
            msgctrlSetValue(0x4E, 0x85);
            sprite->message = 0xA0D4;
        } else {
            winSpriteSetDisp(sprite, false);
            sprite->message = 0;
        }
        break;
    case 0x4E8:
    case 0x4E9:
    case 0x4EA:
        if (c.selected >= 3) {
            winSpriteSetDisp(sprite, true);
        } else {
            winSpriteSetDisp(sprite, false);
        }
        break;
    case 0x4EB: {
        u16 icons[5] = {0x220, 0x21E, 0x21F, 0x21C, 0x21D};
        windowDrawSprite(0, 0, win, icons[c.selected], 0, winSpriteGetLayerID(win, sprite));
        break;
    }
    case 0x4FE:
        if (pokemonDataBiosGetTokuseiDataId(data, 0) != 0) {
            u16 *str = GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(0)));
            msgctrlSetValue(0x37, (u32)str);
            GSmsgPrint2(win->layer, 0, 0, WIN_ALPHA(win) | ~0xFF, 0x4276);
        }
        break;
    case 0x4F0:
        sprite->color.channels.red = 0xD5;
        sprite->color.channels.green = 0xAA;
        sprite->color.channels.blue = 0x33;
        break;
    case 0x4F1: {
        u16 *str = GSmsgGetGSchar(pokemonDataBiosGetName(data));
        msgctrlSetValue(0x37, (u32)str);
        GSmsgPrint2(win->layer, 0, 0, WIN_ALPHA(win) | ~0xFF, 0x4276);
        break;
    }
    case 0x4EC:
    case 0x4FA:
    case 0x4FB:
    case 0x4FC:
    case 0x4FD: {
        s32 slots[5] = {0x4EC, 0x4FA, 0x4FB, 0x4FC, 0x4FD};
        s16 i;
        for (i = 0; i < 5; i++) {
            if (sprite->id == slots[i]) {
                break;
            }
        }
        if (i == c.selected) {
            winSpriteSetDisp(sprite, true);
        } else {
            winSpriteSetDisp(sprite, false);
        }
        break;
    }
    case 0x4E7:
        windowDrawSprite(0, 0, win, zokuseiGetPokemonSpriteID(data, 0), 0, win->layer);
        break;
    case 0x4EF:
    case 0x4F2:
    case 0x4F3:
    case 0x4F4:
    case 0x4F5:
        fn_8005DE84(win, sprite);
        break;
    }
}


extern "C" void menuScriptPdaAddFuncExit(void) {
}

extern "C" void menuScriptPdaAddFuncMain(void) {
    GSgfxVideoSetLockFrameRate(0);
    menuOffScreenSetPriority(0);
    menuPdaSetModelPointer();
    menuPdaModelVisibility(0x17CF1000, true);
    menuPdaAddFunc();
    menuPdaScript(_PdaAddFunc);
    GSgfxVideoSetLockFrameRate(1);
    menuPdaReleaseModelPointer();
    GSmodelAllPauseAnimation();
    GSfloorPop();
}

extern "C" void menuScriptPdaAddFuncInit(void) {
    GSsndPlayNow(0x454);
    cameraPlayAnime(0x17, 0x17CF1800, 0, 0.0f);
    menuPdaModelVisibility(0x17CF1000, false);
}

static u16 _wazaOshieWazaNum(tagWINDOW_WORK *win) {
    if (win->menu == 0xE4) {
        return _WazaNum;
    }
    return _WazaNum;
}

static WAZAOSHIEDEF *_getWaza2Pointer(long index) {
    if (_wazalist == 0) {
        return 0;
    }
    return _wazalist + index;
}

static void _checkWaza2Release(void) {
    if (_wazalist != 0) {
        __dla__FPv(_wazalist);
        _wazalist = 0;
    }
}

static void _checkWazaRelease(void) {
    if (_wazalist != 0) {
        __dla__FPv(_wazalist);
        _wazalist = 0;
    }
}

static bool _checkWazaOverlap(u16 *list, u16 id, u16 count) {
    u16 i;
    for (i = 0; i < count; i++) {
        if (id == list[i]) {
            return true;
        }
    }
    list[count] = id;
    return false;
}

static bool _checkRelive(Pokemon *p) {
    if (!pokemonCheckValid(p)) {
        return false;
    }
    u16 dark = pokemonBiosGetDarkpokemonDataId(p);
    if (dark != 0) {
        return darkPokemonBiosGetReliveFlag(dark) != 0;
    }
    return true;
}

static Pokemon *_getPokemonPtr(long index) {
    Pokemon *p = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), index);
    if (pokemonCheckValid(p)) {
        return p;
    }
    return 0;
}

extern "C" void menuScriptCouponClose(void) {
    menuClose(0x102);
}

extern "C" void menuScriptCouponOpen(s32 x, s32 y) {
    menuOpen(0x102, 0);
    menuSetPosition(0x102, x, y);
}

extern "C" void menuScriptMoneyClose(void) {
    menuClose(0xD8);
}

extern "C" void menuScriptMoneyOpen(s32 x, s32 y) {
    menuOpen(0xD8, 0);
    menuSetPosition(0xD8, x, y);
}

extern "C" void menuScriptSetWazaOboetaFlag(u16 id) {
    u16 i;
    for (i = 0; i < *wazaoshie_data_number; i++) {
        WAZAOSHIE_ENTRY *e = &wazaoshie_data[i];
        if (id == e->id) {
            GSflagOn(e->flag);
        }
    }
}

extern "C" u8 menuScriptWazaBasanCheck(void) {
    return _wazaFlag;
}

extern "C" void menuScriptUsohachi2(void) {
    GSfsysReadWait(0x923);
    menuOpen(0x101, 1);
    menuClose(0x101);
    menuCloseSync(0x101, 1);
    GSresFreeGroup(0x923);
}

extern "C" void menuScriptUsohachi(void) {
    GSfsysReadWait(0x923);
    menuOpen(0xD9, 1);
    menuClose(0xD9);
    menuCloseSync(0xD9, 1);
    GSresFreeGroup(0x923);
}

extern "C" void menuScriptSetOpenWorldMapFlag(u8 flag) {
    _mapFlag = flag;
}

extern "C" u8 menuScriptGetOpenWorldMapFlag(void) {
    return _mapFlag;
}

extern "C" u16 menuScriptOpenWorldMapGetMapNumber(void) {
    return _worldmapnum;
}

extern "C" void menuScriptOpenWorldMap(u16 num) {
    _worldmapnum = num;
    GSthreadSwitch();
    menuScriptSetOpenWorldMapFlag(1);
    GSfloorPush(0x3A8);
    floorWaitForChange();
}

extern "C" void menuScriptMailOpenExit(void) {
    menuPdaMailListSortExit();
}

extern "C" void menuScriptMailOpenMain(void) {
    GSgfxVideoSetLockFrameRate(0);
    if (menuPdaMailListSortInit(_menuScriptMailID) >= 0) {
        menuPdaMailXDScript();
    }
    GSgfxVideoSetLockFrameRate(1);
    menuPdaReleaseModelPointer();
    GSmodelAllPauseAnimation();
    menuScriptSetMailOpen(0);
    GSfloorPop();
}

void menuScriptSetMailOpen(u8 flag) {
    _menuPdaMailOpenFlag = flag;
}

extern "C" u8 menuScriptCheckMailOpen(void) {
    return _menuPdaMailOpenFlag;
}

extern "C" void menuScriptMailOpenInit(void) {
    cameraPlayAnime(0x17, 0x17CF1800, 0, 0.0f);
    GSsndPlayNow(0x44F);
    menuOffScreenSetPriority(0);
    menuScriptSetMailOpen(1);
    menuPdaSetModelPointer();
    menuPdaZoomIn();
}

extern "C" void menuScriptInfoEsa(void) {
    _menuScriptWork = 1;
    menuOpenCustom(0x97, windowGetActiveID(), 0, 0, 1, 1, &_menuScriptWork);
    menuCloseCustom(0x97, 0, 1);
    winMsgOpen(3, 0x3E83, 1, 1);
    winMsgClose(1);
}

extern "C" void menuScriptReciveMail(void) {
    _menuScriptWork = 0;
    menuOpenCustom(0x97, windowGetActiveID(), 0, 0, 1, 1, &_menuScriptWork);
    menuCloseCustom(0x97, 0, 1);
}

extern "C" void menuScriptUsohachiCtrl(tagWINDOW_WORK *);
extern "C" void menuScriptEeveeCtrl(tagWINDOW_WORK *);

extern "C" void menuScriptPdaAddFunc(void);
static void _menuScriptPdaAddFunc(pdaAddFuncDef);
static void _menuScriptReadMail(long);
static void _getWazaData(u16, WAZAOSHIEDEF *);
static u16 _checkWazaSub(Pokemon *);
static u16 _checkWaza(long);
static u16 _checkWaza2(void);

static void _menuScriptPdaAddFunc(pdaAddFuncDef def) {
    u8 rate;
    GSmodelAllPauseAnimation();
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    menuOffScreenCheckEnable(1);
    _PdaAddFunc = def;
    GSfloorPush(0x38C);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(0.0f / GSgfxVideoGetVsyncRate());
    GSmodelAllUnpauseAnimation();
}

extern "C" void menuScriptPdaAddFunc(void) {
    ((void (*)(void))_menuScriptPdaAddFunc)();
}

static void _menuScriptReadMail(long id) {
    u8 rate;
    GSmodelAllPauseAnimation();
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    menuOffScreenCheckEnable(1);
    _menuScriptMailID = id;
    GSfloorPush(0x393);
    void *flag = mailGetOpenFlag(id);
    if (flag != 0) {
        GSflagSet(flag, 1);
    }
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(0.0f / GSgfxVideoGetVsyncRate());
    GSmodelAllUnpauseAnimation();
}

extern "C" void menuScriptReadMail(void) {
    ((void (*)(void))_menuScriptReadMail)();
}

extern "C" void menuScriptInfoRelive(void *arg, u8 first) {
    Pokemon *p = (Pokemon *)arg;
    u16 dark = pokemonBiosGetDarkpokemonDataId(p);
    _menuScriptWork = 2;
    menuOpenCustom(0x97, windowGetActiveID(), 0, 0, 1, 1, &_menuScriptWork);
    menuCloseCustom(0x97, 0, 1);
    if (p != 0) {
        void *name = pokemonBiosGetNicknamePtr(p);
        msgctrlSetValue(0x32, (u32)name);
        if (first != 0) {
            winMsgOpen(3, 0x3E81, 1, 1);
        } else {
            winMsgOpen(3, 0x3E82, 1, 1);
        }
        winMsgClose(1);
        darkPokemonBiosSetInformationFlag(dark, 1);
    }
}

extern "C" s32 menuScriptEevee(void) {
    s32 ret;
    if (GSfloorGetCurrent() != 0x97) {
        u16 *name = floorGetPlaceName(0x97);
        msgctrlSetValue(0x31, (u32)name);
        winMsgOpen(3, 0xEFF7, 1, 1);
        winMsgClose(1);
        return -1;
    }
    GSfsysReadWait(0x8CA);
    winMsgOpen(3, 0xA0CF, 0, 1);
    ret = menuOpen(0xAF, 1);
    menuClose(0xAF);
    winMsgClose(1);
    menuCloseSync(0xAF, 1);
    GSresFreeGroup(0x8CA);
    return ret;
}

extern "C" s32 menuScriptTutorial(void) {
    s32 args = 0;
    s32 ret;
    if (GSfloorGetCurrent() != 0x8D) {
        u16 *name = floorGetPlaceName(0x8D);
        msgctrlSetValue(0x31, (u32)name);
        winMsgOpen(3, 0xEFF7, 1, 1);
        winMsgClose(1);
        return -1;
    }
    GSfsysReadWait(0x8D1);
    CURSOR c = cursorBiosGetPos(0xE);
    c.selected = 0;
    c.first = 0;
    CURSOR tmp = c;
    cursorBiosSetPos(0xE, &tmp);
    ret = menuOpenCustom(0xB8, windowGetActiveID(), &args, 0, 1, 0);
    if (ret < 0) {
        _tutorialSelect = ret;
    } else {
        fightEncountDataBiosSetDiskId(fightEncountDataBiosGetPtr(0xD), tutorialdata[ret]);
    }
    menuClose(0xB8);
    menuCloseSync(0xB8, 1);
    GSresFreeGroup(0x8D1);
    if ((u32)*tutorialdata_number == (u32)(_tutorialSelect + 1)) {
        _tutorialSelect = -1;
    }
    return _tutorialSelect;
}

extern "C" s32 menuScriptWazaBasan(s8 *flag) {
    s32 ret;
    *flag = 0;
    _wazaFlag = 0;
    _WazaNum = _checkWaza2();
    if (_WazaNum == 0) {
        ret = 0;
    } else {
        CURSOR c = cursorBiosGetPos(0xF);
        s32 sel = c.selected;
        ret = menuOpenCustom(0xE5, windowGetActiveID(), &sel, 0, 1, 0);
        if (ret >= 0) {
            if (_WazaNum == ret + 1) {
                ret = -1;
            } else {
                if (_wazalist[ret].released != 0) {
                    if (flag != 0) {
                        *flag = 1;
                    }
                    _wazaFlag = 1;
                }
                ret = wazaoshie_data[(u16)ret].id;
            }
        }
        menuClose(0xE5);
        menuCloseSync(0xE5, 1);
    }
    _checkWaza2Release();
    return ret;
}

extern "C" s32 menuScriptWazaMeijin(void) {
    s32 ret;
    _WazaNum = ((u16 (*)(void))_checkWaza)();
    if (_WazaNum == 0) {
        ret = -1;
    } else {
        ret = menuOpen(0xE4, 1);
        if (ret >= 0) {
            if (_WazaNum == ret + 1) {
                ret = -1;
            } else {
                ret = _wazalist[ret].id;
            }
        }
        menuClose(0xE4);
        menuCloseSync(0xE4, 1);
    }
    _checkWazaRelease();
    return ret;
}

static void _getWazaData(u16 id, WAZAOSHIEDEF *out) {
    void *data;
    WAZAOSHIEDEF *w;
    data = wazaDataBiosGetPtr(id);
    if (out != 0) w = out; else w = &_wazawork;
    w->id = id;
    w->name = wazaDataBiosGetName(data);
    w->pp = wazaDataBiosGetPp(data);
    w->type = wazaDataBiosGetZokuseiDataId(data);
    w->power = wazaDataBiosGetIryoku(data);
    w->accuracy = wazaDataBiosGetAvg(data);
    w->doc = wazaDataBiosGetDoc(data);
    w->released = 0;
}

static u16 _checkWazaSub(Pokemon *p) {
    void *data;
    u16 count;
    u16 i;
    u32 did = pokemonBiosGetPokemonDataId(p);
    data = pokemonDataBiosGetPtr(did);
    count = 0;
    memset(_tempwazaid, 0, 0x2A);
    if (data != 0) {
        for (i = 0; i < 0x14; i++) {
            u8 lv = pokemonDataBiosGetGetWazaLevel(data, i);
            if (lv == 0) {
                break;
            }
            if (pokemonBiosGetLevel(p) >= lv && !_checkWazaOverlap(_tempwazaid, pokemonDataBiosGetGetWazaDataId(data, i), count)) {
                count++;
            }
        }
    }
    return count;
}

static u16 _checkWaza(long index) {
    Pokemon *p;
    u16 count = 0;
    u16 i;
    p = _getPokemonPtr(index);
    if (p != 0 && _checkRelive(p)) {
        count = _checkWazaSub(p);
    }
    if (count != 0) {
        count++;
        _wazalist = (WAZAOSHIEDEF *)__nwa__FUl(count * 0x18);
        for (i = 0; i < (u16)count - 1; i++) {
            _getWazaData(_tempwazaid[i], &_wazalist[i]);
        }
        _wazalist[i].id = 0;
    }
    return count;
}

extern "C" void menuScriptWazaOshieCtrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x24);
            win->step = 1;
            if (win->menu == 0xE5) {
                win->pos = cursorBiosGetPos(0xF);
            }
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x17B);
            win->step = 1;
        }
        break;
    }
}

extern "C" void menuScriptUsohachiCtrl(tagWINDOW_WORK *win) {
    menuScriptEeveeCtrl(win);
}

extern "C" void menuScriptTutorialCtrl(tagWINDOW_WORK *win) {
    menuDataBiosGetPtr(win->menu);
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x24);
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x17B);
            win->step = 1;
        }
        break;
    }
}

extern "C" void menuScriptEeveeCtrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x24);
            win->step = 1;
            switch (win->menu) {
            case 0xD9:
                break;
            case 0xAF:
                menuSetStatus(win->menu, 8);
                break;
            }
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x17B);
            win->step = 1;
        }
        break;
    }
}

extern "C" void menuUsohachiHook(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    switch (sprite->id) {
    case 0x661:
        if (win->menu == 0xD9) {
            windowDrawSprite(0, 0, win, 0x2D8, 0, winSpriteGetLayerID(win, sprite));
        } else {
            windowDrawSprite(0, 0, win, 0x341, 0, winSpriteGetLayerID(win, sprite));
        }
        break;
    }
}

extern "C" s32 menuScriptMoneyDraw(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    if (win->menu == 0xD8) {
        switch (sprite->id) {
        case 0x65B:
            msgctrlSetValue(0x50, (u32)heroGetStatus(0, 0xC, 0));
            GSmsgPrint2(win->layer, (s16)(sprite->width - (s16)(GSmsgGetRect(0x434E) >> 16)), 0, -1, 0x434E);
            break;
        case 0x65A:
            windowDrawSprite2(0, 0, sprite->width, sprite->height, win->color90, win, 0x2D3, 0, winSpriteGetLayerID(win, sprite));
            break;
        }
    } else {
        switch (sprite->id) {
        case 0x65B:
            msgctrlSetValue(0x50, (u32)heroGetStatus(0, 0xD, 0));
            GSmsgPrint2(win->layer, (s16)(sprite->width - (s16)(GSmsgGetRect(0x434E) >> 16)), 0, -1, 0x434E);
            break;
        case 0x65A:
            windowDrawSprite2(0, 0, sprite->width, sprite->height, win->color90, win, 0x2F9, 0, winSpriteGetLayerID(win, sprite));
            break;
        }
    }
    return 0;
}

static u16 _checkWaza2(void) {
    s32 i;
    u16 count = 0;
    u16 released = 0;
    u16 *ids = (u16 *)__nwa__FUl(*wazaoshie_data_number * 2);
    u8 *rel = (u8 *)__nwa__FUl(*wazaoshie_data_number);
    for (i = 0; i < *wazaoshie_data_number; i++) {
        s32 idx = wazaoshie_data[i].floorIndex;
        if (GSflagGet(0x3C4) >= flag_etc[idx].value) {
            u16 id = wazaoshie_data[i].id;
            ids[count] = id;
            rel[count] = GSflagTest(wazaoshie_data[i].flag, id);
            if (rel[count] != 0) {
                released++;
            }
            count++;
        }
    }
    if (released == count) {
        count = 0;
    } else if (count != 0) {
        count++;
        _wazalist = (WAZAOSHIEDEF *)__nwa__FUl(count * 0x18);
        for (i = 0; i < (u16)count - 1; i++) {
            _getWazaData(ids[i], &_wazalist[i]);
            _wazalist[i].released = rel[i];
        }
        _wazalist[i].id = 0;
    }
    __dla__FPv(ids);
    __dla__FPv(rel);
    return count;
}

extern "C" s32 menuScriptWazaOshieCursor(tagWINDOW_WORK *win) {
    CURSOR c;
    s16 sel;
    u16 key;
    s32 num;
    s32 vis;
    windowGetKeyInfo();
    key = windowGetKeyRepeat();
    *(s32 *)&c = *(s32 *)&win->pos;
    num = _wazaOshieWazaNum(win);
    vis = 9;
    if (num < 9) {
        vis = num;
    }
    if (vis != 0) {
        if ((key & 1) != 0) {
            c.selected -= 1;
        } else if ((key & 2) != 0) {
            c.selected += 1;
        }
        sel = c.selected;
        if (sel < 0) {
            c.first += sel;
            c.selected = 0;
            if (c.first < 0) {
                c.first = 0;
                c.selected = 0;
            }
        } else if (sel >= vis) {
            s8 last;
            s16 nf = c.first + (sel - (vis - 1));
            last = vis - 1;
            c.selected = last;
            c.first = nf;
            if (nf + last >= num) {
                c.selected = last;
                c.first = (s8)(num - vis);
            }
        }
    }
    win->pos.first = c.first;
    win->pos.selected = c.selected;
    if (win->menu == 0xE5) {
        CURSOR pos;
        *(s32 *)&pos = *(s32 *)&c;
        cursorBiosSetPos(0xF, &pos);
    }
    return 0;
}

static void _wazaOshieCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    s32 i = 0;
    CURSOR c = win->pos;
    const s32 ids[9] = {0x6BB, 0x6BC, 0x6BD, 0x6BE, 0x6BF, 0x6C0, 0x6C1, 0x6C2, 0x6C3};
    for (i = 0; i < 9; i++) {
        if (sprite->id == ids[i]) {
            break;
        }
    }
    if (i == c.selected) {
        winSpriteSetDisp(sprite, true);
        return;
    }
    winSpriteSetDisp(sprite, false);
}

extern "C" void menuScriptTutorialCursor(tagWINDOW_WORK *win) {
    s16 sel;
    s32 vis;
    s32 num;
    u16 key;
windowGetKeyInfo();
    num = *tutorialdata_number;
    vis = 8;
    if (num < 8) {
        vis = num;
    }
    key = windowGetKeyRepeat();
    CURSOR c = cursorBiosGetPos(0xE);
    if (vis != 0) {
        if ((key & 1) != 0) {
            c.selected -= 1;
        } else if ((key & 2) != 0) {
            c.selected += 1;
        }
        sel = c.selected;
        if (sel < 0) {
            c.selected = 0;
            c.first += sel;
            if (c.first < 0) {
                c.first = 0;
                c.selected = 0;
            }
        } else if (sel >= vis) {
            s8 last;
            s16 nf = c.first + (sel - (vis - 1));
            last = vis - 1;
            c.selected = last;
            c.first = nf;
            if (nf + last >= num) {
                c.selected = last;
                c.first = (s8)(num - vis);
            }
        }
    }
    s32 select;
    s16 curSelected = c.selected;
    if (curSelected == (s8)(*tutorialdata_number - 1)) {
        select = -1;
    } else {
        select = curSelected + c.first;
    }
    _tutorialSelect = select;
    win->pos.first = c.first;
    win->pos.selected = curSelected;
    CURSOR tmp;
    *(s32 *)&tmp = *(s32 *)&c;
    cursorBiosSetPos(0xE, &tmp);
}


static void _menuScriptTokuseiSetumei(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, CURSOR *cursor, POKEMON_DATA_dd_ *pdata) {
    MENU_ITEM_dd_ *item = menuItemBiosGetPtr(0xAF, sprite->id);
    if (u8 tokusei = pokemonDataBiosGetTokuseiDataId(pdata, 0)) {
        u16 *text = GSmsgGetGSchar((s32)pokemonTokuseiDataBiosGetDoc(pokemonTokuseiDataBiosGetPtr(tokusei)));
        u32 len = GSmsgGetCharLength(text);
        u32 size = (len + 2) * 2;
        u16 *buf1 = (u16 *)__nwa__FUl(size);
        u16 *buf2 = (u16 *)__nwa__FUl(size);
        u16 *printBuf = buf1;
        s32 line = 0;
        s32 fitLine = 0;
        u8 overflow = 0;
        for (;;) {
            s32 spaces = 0;
            s32 out = 0;
            s32 limit = line;
            u16 *src = text;
            u16 *dst = buf1;
            line++;
            for (;;) {
                u16 ch = *src;
                if (ch == 0x20 || ch == 0x3000) {
                    if (spaces == limit) {
                        break;
                    }
                    *dst = ch;
                    spaces++;
                } else {
                    if (ch == 0) {
                        break;
                    }
                    *dst = ch;
                }
                src++;
                dst++;
                out++;
            }
            buf1[out] = 0;
            out++;
            msgctrlSetValue(0x37, (u32)printBuf);
            u32 rect = GSmsgGetRect(0x4276);
            if ((rect >> 16) <= (u32)item->width) {
                fitLine = line;
            }
            if (!((rect >> 16) <= (u32)item->width)) {
                overflow = 1;
            }
            if (!((u32)out < len)) {
                break;
            }
        }
        if (overflow != 0) {
            s32 spaceIdx = 0;
            s32 count1 = 0;
            s32 count2 = 0;
            u8 second = 0;
            u32 total = GSmsgGetCharLength(text);
            u32 idx = 0;
            u16 *src = text;
            for (;; src++, idx++) {
                u16 ch = *src;
                if (ch == 0xFFFF) {
                    continue;
                }
                if (ch == 0x20 || ch == 0x3000) {
                    if (spaceIdx == fitLine - 1) {
                        second = 1;
                    } else if (second != 0) {
                        buf2[count2++] = ch;
                    } else {
                        buf1[count1++] = ch;
                    }
                    spaceIdx++;
                    continue;
                }
                if (ch == 0) {
                    if (total > idx) {
                        continue;
                    }
                    break;
                }
                if (second != 0) {
                    buf2[count2++] = ch;
                } else {
                    buf1[count1++] = ch;
                }
            }
            buf1[count1] = 0;
            buf2[count2] = 0;
            msgctrlSetValue(0x37, (u32)buf1);
            GSmsgPrint2(win->layer, 0, 0, WIN_ALPHA(win) | ~0xFF, 0x4276);
            msgctrlSetValue(0x37, (u32)buf2);
            GSmsgPrint2(win->layer, 0, 0x12, WIN_ALPHA(win) | ~0xFF, 0x4276);
        } else {
            msgctrlSetValue(0x37, (u32)text);
            GSmsgPrint2(win->layer, 0, 0, WIN_ALPHA(win) | ~0xFF, 0x4276);
        }
        __dla__FPv(buf1);
        __dla__FPv(buf2);
    }
}

extern "C" {
void menuPdaSubCheckUpDownCursor(tagWINDOW_WORK*,tagSPRITE_WORK*,CURSOR*,u32,s32,s32);
void spriteSetScissor(s32,s32,s32,s32,s32);
void spriteClearScissor(s32);
void GSmsgPrintRect(s32,s32,s32,s32,s32,u32,u32);
void GSmsgPrintRight(s32,s32,s32,s32,s32,u32,u32);
void* menuSpriteBiosGetPtr(s16);
void* menuSpriteBiosGetValPtr(void*);
u32 heroBiosGetPokecoupon(void*);
s32 zokuseiBiosGetSpriteID(u8);
}
struct ScriptSpriteValue {s16 x,y,width,height;};
extern "C" void menuScriptWazaOshieHook(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite) {
    CURSOR cursor;
    *(u32*)&cursor=*(u32*)&window->pos;
    u32 count=_wazaOshieWazaNum(window);
    WAZAOSHIEDEF* selected=_getWaza2Pointer(cursor.selected+cursor.first);
    u32 color;
    s32 layer=winSpriteGetLayerID(window,sprite);
    color=WIN_ALPHA(window)|~255;
    switch(sprite->id) {
    case 0x6bb:case 0x6bc:case 0x6bd:case 0x6be:case 0x6bf:case 0x6c0:case 0x6c1:case 0x6c2:case 0x6c3:
        _wazaOshieCursor(window,sprite);return;
    case 0x6b6:case 0x6b7:case 0x6b8:
        if(window->menu==0xe4)winSpriteSetDisp(sprite,true);else winSpriteSetDisp(sprite,false);return;
    case 0x6b9:menuPdaSubCheckUpDownCursor(window,sprite,&cursor,(u16)count,9,0);return;
    case 0x6ba:menuPdaSubCheckUpDownCursor(window,sprite,&cursor,(u16)count,9,1);return;
    case 0x6d5:
        if(count) {
            MENU_ITEM_dd_* clip=menuItemBiosGetPtr(window->menu,0x6d5);
            MENU_ITEM_dd_* item=menuItemBiosGetPtr(window->menu,sprite->id);
            spriteSetScissor(layer,clip->x-item->x,clip->y-item->y,clip->width,clip->height);
            u16 index=0;s16 y=-cursor.first*31;
            for(;index<count;index++,y+=31) {
                if(index>=cursor.first-1 && index<cursor.first+10) {
                    WAZAOSHIEDEF* entry=_getWaza2Pointer(index);
                    if(entry->id) {
                        GSmsgPrint2(layer,0,y,color,entry->name);
                        if(window->menu==0xe4) {
                            msgctrlSetValue(0x50,1000);
                            GSmsgPrint2(layer,(s16)(sprite->width-(GSmsgGetRect(0x4359)>>16)),y,color,0x4359);
                        }else if(entry->released) {
                            ScriptSpriteValue* value=(ScriptSpriteValue*)menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x241));
                            windowDrawSprite((s16)(item->width-value->width),(s16)(y+(18-value->height)/2),window,0x241,0,layer);
                        }
                    }else if(window->menu==0xe4)GSmsgPrint2(layer,0,y,color,0x4295);
                    else GSmsgPrint2(layer,0,y,color,0xc753);
                }
            }
            spriteClearScissor(layer);
        }
        return;
    case 0x6d4:
        if(selected) {
            if(selected->id)GSmsgPrint2(layer,0,0,color,selected->doc);
            else {u32 message;if(window->menu==0xe4)message=0xc6da;else message=0xc73b;GSmsgPrint2(layer,0,0,color,message);}
        }
        return;
    case 0x6d6:
        if(window->menu==0xe4) {
            msgctrlSetValue(0x50,heroBiosGetPokecoupon(savedataGetStatus(0,2)));
            GSmsgPrint2(layer,(s16)(sprite->width-(GSmsgGetRect(0x434e)>>16)),0,color,0x434e);
        }
        return;
    case 0x6cf:
        if(selected && selected->id) {msgctrlSetValue(0x5f,selected->pp);GSmsgPrintRect(layer,0,0,sprite->width,sprite->height,color,0x4287);}
        return;
    case 0x6cd:
        if(selected && selected->id) {
            if((u8)selected->accuracy<=1)GSmsgPrintRight(layer,0,0,sprite->width,sprite->height,color,0x3af6);
            else {msgctrlSetValue(0x34,(u8)selected->accuracy);GSmsgPrintRect(layer,0,0,sprite->width,sprite->height,color,0x4287);}
        }
        return;
    case 0x6ce:
        if(selected && selected->id) {
            if(selected->power<=1)GSmsgPrintRight(layer,0,0,sprite->width,sprite->height,color,0x3af6);
            else {msgctrlSetValue(0x34,selected->power);GSmsgPrintRect(layer,0,0,sprite->width,sprite->height,color,0x4287);}
        }
        return;
    case 0x6b5:
        if(selected && selected->id) {
            MENU_ITEM_dd_* item=menuItemBiosGetPtr(window->menu,0x6b5);
            s32 spriteID=zokuseiBiosGetSpriteID(selected->type);
            windowDrawSprite2(0,0,item->width,item->height,color,window,spriteID,0,layer);
        }
        return;
    }
}

u32 deckDataVirtualDB_GetTitle(u16);
u32 deckDataVirtualDB_GetFlag(u16);
u32 deckDataVirtualDB_GetExplanetion2(u16);
extern "C" void menuScriptTutorialHook(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite) {
    CURSOR cursor=cursorBiosGetPos(14);
    switch(sprite->id) {
    case 0x7e6:case 0x7e7:case 0x7e8:case 0x7e9:case 0x7ea:case 0x7eb:case 0x7ec:case 0x7ed: {
        const s32 ids[8]={0x7e6,0x7e7,0x7e8,0x7e9,0x7ea,0x7eb,0x7ec,0x7ed};
        s32* entry=(s32*)ids;s16 index=0;
        while(index<8) {if(sprite->id==*entry)break;entry++;index++;}
        if((u32)*tutorialdata_number>(u32)index) {
            u16 id=tutorialdata[index+cursor.first];
            sprite->message=id?deckDataVirtualDB_GetTitle(id):0xdece;
        }else sprite->message=0;
        return;
    }
    case 0x7cf:case 0x7d1:case 0x7d3:case 0x7d5:case 0x7d7:case 0x7d9:case 0x7db:case 0x7dd: {
        const s32 ids[8]={0x7cf,0x7d1,0x7d3,0x7d5,0x7d7,0x7d9,0x7db,0x7dd};
        s32* entry=(s32*)ids;s16 index=0;
        while(index<8) {if(sprite->id==*entry)break;entry++;index++;}
        if(index==cursor.selected)winSpriteSetDisp(sprite,true);else winSpriteSetDisp(sprite,false);
        return;
    }
    case 0x7ce:case 0x7d0:case 0x7d2:case 0x7d4:case 0x7d6:case 0x7d8:case 0x7da:case 0x7dc: {
        const s32 ids[8]={0x7ce,0x7d0,0x7d2,0x7d4,0x7d6,0x7d8,0x7da,0x7dc};
        s32* entry=(s32*)ids;s16 index=0;
        while(index<8) {if(sprite->id==*entry)break;entry++;index++;}
        if(index==cursor.selected)winSpriteSetDisp(sprite,true);else winSpriteSetDisp(sprite,false);
        return;
    }
    case 0x7de:case 0x7df:case 0x7e0:case 0x7e1:case 0x7e2:case 0x7e3:case 0x7e4:case 0x7e5: {
        const s32 ids[8]={0x7de,0x7df,0x7e0,0x7e1,0x7e2,0x7e3,0x7e4,0x7e5};
        s32* entry=(s32*)ids;s16 index=0;
        while(index<8) {if(sprite->id==*entry)break;entry++;index++;}
        u16 id=tutorialdata[index+cursor.first];
        u32 flag=id?deckDataVirtualDB_GetFlag(id):0;
        if(((u8(*)(void*))GSflagTest)((void*)flag) && flag)winSpriteSetDisp(sprite,true);else winSpriteSetDisp(sprite,false);
        return;
    }
    case 0x7ee: {
        u16 id=tutorialdata[cursor.selected+cursor.first];sprite->message=id?deckDataVirtualDB_GetExplanetion2(id):0;
        return;
    }
    case 0x7f0:menuPdaSubCheckUpDownCursor(window,sprite,&cursor,*tutorialdata_number,8,0);return;
    case 0x7f1:menuPdaSubCheckUpDownCursor(window,sprite,&cursor,*tutorialdata_number,8,1);return;
    }
}
