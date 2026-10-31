#pragma defer_codegen on
extern "C" {
#include <libc/stdio.h>
}
#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>

#pragma force_active on

#pragma peephole off
#pragma pool_strings off

struct tagWINDOW_WORK {
    u8 unk0;
    s8 state;
    s8 seqSet;
    u8 unk3;
    s32 seq;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x73];
    u8 alpha;
    u8 unk94[0xA];
    s16 cursor;
    s16 unkA0;
    s16 prevCursor;
};

struct tagSPRITE_WORK {
    u8 unk0[4];
    s8 flags;
    u8 unk5;
    s16 id;
    u8 unk8[0x44];
    s32 msgID;
    u8 unk50[4];
    s16 x;
    u8 unk56[0x11];
    u8 alpha;
};

struct MenuData {
    u8 unk0[6];
    s16 firstItem;
};

struct MenuItem {
    u8 flagA : 1;
    u8 flagB : 1;
    u8 unk0b : 6;
    u8 unk1[5];
    s16 x;
    s16 y;
    u8 unkA[0xE];
    s16 next;
};

struct GSvec2 {
    f32 x;
    f32 y;
};

enum PDATOP_MENU_RES {
    PDATOP_NONE = -1,
    PDATOP_DPMON = 0,
    PDATOP_MEMO = 1,
    PDATOP_MAIL = 2,
    PDATOP_SEARCH = 3,
    PDATOP_END = 4
};

struct PdaStatus {
    s32 cur;
    s32 sub;
    s32 prev;
    u8 unkC[8];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    s32 unk3C;
    u8 unk40;
    u8 unk41;
    u8 unk42[2];
    f32 ang0;
    f32 ang1;
    f32 ang2;
    f32 ang3;
    f32 angD0;
    f32 angD1;
    f32 pos;
    f32 target;
    f32 speed;
    u8 arrived;
    u8 unk69[3];
};

struct TitleParam {
    u8 flag0;
    u8 alpha;
    u8 flag2;
    s32* titleMsg;
    s32* lineAnim;
};

struct GSgfxVF;

class GSgfxLayer {
public:
    void setRenderStateAndSelect(GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

    u8 unk0[0x1644];
    s32 unk1644;
    s32 unk1648;
    s32 unk164C;
    s32 unk1650;
    u8 unk1654[0x16A8 - 0x1654];
    u32 unk16A8;
    u8 unk16AC[0x170C - 0x16AC];
    u32 unk170C;
    u8 unk1710[0x1760 - 0x1710];
    u32 unk1760;
    u8 unk1764[0x17C4 - 0x1764];
    u32 unk17C4;
    u8 unk17C8[0x1818 - 0x17C8];
    u8 surfaces[2][0xBC];
    void* curSurface;
    s32 curSurfaceIdx;
    u32 unk1998;
};

class Hero {
public:
    u8 getHeroStyle() const;
};

double __fabs(double x);
#define fabs(x) __fabs(x)

extern "C" {
double sin(double x);
double cos(double x);
double acos(double x);
void FlashSystemSetPlayFrameLabel(u32 id, const char* start, const char* end);
void FlashSystemSetNowFrameLabel(u32 id, const char* label);
u32 FlashSystemGetFrameFromLabel(u32 id, const char* label);
void FlashSystemSetLoopFlag(u32 id, bool flag);
u32 FlashSystemGetNowFrame(u32 id);
void menuOpen(s32 id, s32);
s32 menuOpenCustom(s32 id, ...);
s32 windowGetActiveID(void);
void GSthreadSwitch(void);
f32 timeGetLastFrameSec(void);
void menuItemBiosSetSelectFlag(s32 menu, s32 item, bool flag);
u8 menuItemBiosGetSelectFlag(s32 menu, s32 item);
void menuClose(s32 id);
void menuCloseSync(s32 id, bool sync);
void menuOffScreenSetPriority(s32 p);
void menuOffScreenSetDisp(s32 d);
void GSfloorPop(void);
void GSfloorPush(s32 id);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
u32 floorGetCurrent(void);
void* GSresGetResourceAllGroup(u32 id);
void* GSresGetResource(s32 type, u32 id);
void GSmodelSetVisibility(void* model, bool vis);
void GSmodelSetBoundCheck(void* model, bool on);
void GSmodelSetRenderLayer(void* model, s32 count, s32* layers);
void GSmodelSetRenderCamera(void* model, void* camera);
void GSmodelStopAnimation(void* model);
void GSmodelStartAnimation(void* model);
u8 GSmodelIsAnimating(void* model);
void GSmodelGetAnimIndex(void* model, s32* index, s32* other);
void GSmodelSetAnimIndex(void* model, s16 index);
void GSmodelSetAnimFrame(void* model, f32 frame);
void GSmodelSetAnimRate(void* model, f32 rate);
void GSmodelSetAnimType(void* model, s32 type);
void cameraPlayAnime(s32 id, u32 res, f32 frame, s32);
void scriptLightSetDisp(s32 id, bool disp);
s32 pokecoloGetRomVersion(void);
u32 pokecoloGetPlayTimeValue(void);
void GSflagOn(s32 flag);
u32 GSflagGet(s32 flag);
void GSsndPlayNow(u32 id);
void winSpriteSetDisp(tagSPRITE_WORK* sprite, bool disp);
void menuButtonNormal(tagWINDOW_WORK* window);
s32 menuPdaMemoXDGetItem(void);
void menuPdaDPMonList(void);
void menuPdaMemoList(void);
void menuPdaMailListXD(void);
void menuPdaSearcher(void);
MenuData* menuDataBiosGetPtr(s32 id);
MenuItem* menuItemBiosGetPtr(s32 menu, s32 item);
u32 windowGetCursorToItem(tagWINDOW_WORK* window);
u32 windowGetKeyRepeat(void);

void msgctrlSetValue(s32 id, u32 value);
s32 heroGetStatus(void* hero, s32 kind, s32 arg);
void GSmsgPrint2(s32 layer, s32 x, s32 y, u32 color, u32 msg);
u32 GSmsgGetRect(u32 msg);
void winSeqSetMenu(s32 seq, s32 menu);
void fadeSet(s32 mode, f32 time);
s8 fadeCheck(s32 mode);
u32 menuGetCursorItemID(s32 menu);
void* savedataGetStatus(s32, s32);
void windowDrawSprite(s32, s32, tagWINDOW_WORK*, s32, s32, s32);
GSgfxLayer* GSgfxLayerFindByID(s32 id);
GSgfxVF* GSgfxVFGetPredef(s32 id);
void GSmemFree(void* p);
s32 menuPdaGetRes(void);
s32 menuPdaGetSubres(void);
void menuPdaDrawDirectModel(void);
}

static bool _checkAddFunc(tagWINDOW_WORK* window);
static void _SelectCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s8 idx);
static void _menuPdaDrawFace(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static s32 _SelectCursorSub(s8 idx, GSvec2* out);
static s32 _SelectCursorCalcPositon(GSvec2* out);
static void _SelectCursorCalcAngle(s8 idx);
static bool _SelectCursorPositionCheck(void);
static void _menuPdaSetMenuItem(void);
static s8 _menuPdaGetCurrentID(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
static void _menuPdaModelCursorAnime(void);
static void _menuPdaZoomOut(void);
static void _menuPdaZoomIn(void);
static void _menuPdaAddFunc(void);
static void _menPdaFadeInWait(void);
static bool _menPdaFadeOutWait(void);
static void _menPdaFadeOutSet(void);
static s32 _menuPdaGetMoney(void);
static s32 _menuPdaGetPokecoupon(void);
static u8 _menuPdaWaitMotion2(u32 id);
static s32 _menuPdaModelGetIndex(u32 id);
static void _menuPdaModelVisibility(u32 id, bool vis);
static void _menuPdaStopMotion(u32 id);
static void _menuPdaWaitMotion(u32 id);
static void _menuPdaSetMotion(u32 id, s16 index, f32 frame, bool loop);
static void _menuPdaExit(void);
static void _menuPdaInit(void);
static void _menuPdaFree(void* p);
static void _menuPdaSelectAnimeSet(long idx);
static void _menuPdaStartEvent(void);
static void _menuPdaTopClose(void);
static PDATOP_MENU_RES topMenu(PDATOP_MENU_RES res);
static s32 _getMenuIndex(PDATOP_MENU_RES res);
static u8 _menuPdaScriptGetAlpha(void);
static void _menuPdaScriptCalcAlpha(f32 d);
static void _menuPdaScriptCalcAlphaInit(void);
static void _menuPdaSetMenuItemScript(u8 flag);

static s32 pdaitemtable[5][2] = {{0x3F2, 2}, {0, 3}, {0, 4}, {0x3F3, 5}, {0, 6}};
static s32 _SelectLabel[5] = {2, 3, 4, 5, 6};
static s16 _cursor_index[5];
static PdaStatus _menuPdaStatus;
static u8 _menuPdaInitFlag = 1;
static f32 _center1[2] = {206.0f, 238.0f};
static f32 _r1 = 180.0f;
static f32 _center2[2] = {459.0f, 238.0f};
static f32 _r2 = 150.0f;
static f32 _next_height = 36.0f;
static u8 _seon = 1;
static f32 _pdaScriptTime = 1.5f;
static void* _menuPdaFlashBuffer;
static void* _menuPdaTextureBuffer;
static u8 _addfunc;
static bool _pdaSelectAnimeFlag;
static s16 _cursor_index_max;
void* _pModel;
static s32 TitleMsgID;
static s32 LineAnimTime;
static f32 _pdaScriptAddFrame;

#define PDA_MODEL 0x17CF1000

extern "C" {

extern "C" void menuPdaOpen(void);

}

static void _menuPdaFree(void *p);

static void _menuPdaInit(void);

static void _menuPdaExit(void);

static void _menuPdaSetMotion(u32 id, s16 index, f32 frame, bool loop);

static void _menuPdaWaitMotion(u32 id);

static void _menuPdaStopMotion(u32 id);

static void _menuPdaModelVisibility(u32 id, bool visible);

static s32 _menuPdaModelGetIndex(u32 id);

static u8 _menuPdaWaitMotion2(u32 id);

extern "C" {

s32 menuPdaGetSubres(void);

}

extern "C" {

s32 menuPdaGetRes(void);

}

extern "C" {

void menuPdaSetSubres(s32 res, s32 sub);

}

static s32 _menuPdaGetPokecoupon(void);

static s32 _menuPdaGetMoney(void);

static void _menPdaFadeOutSet(void);

static bool _menPdaFadeOutWait(void);

static void _menPdaFadeInWait(void);

static void _menuPdaAddFunc(void);

static void _menuPdaZoomIn(void);

static void _menuPdaZoomOut(void);

extern "C" {

extern "C" void menuPdaZoomIn(void);

}

extern "C" {

extern "C" void menuPdaAddFunc(void);

}

extern "C" {

extern "C" void menuPdaModelVisibility(u32 id, bool visible);

}

extern "C" {

s32 menuPdaTopCtrl(tagWINDOW_WORK* window);

}

extern "C" {

extern "C" s32 menuPdaDummyCtrl(void);

}

static void _menuPdaModelCursorAnime(void);

static s8 _menuPdaGetCurrentID(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);

static void _menuPdaSetMenuItem(void);

static bool _SelectCursorPositionCheck(void);

static void _SelectCursorCalcAngle(s8 idx);

static s32 _SelectCursorCalcPositon(GSvec2* out);

static s32 _SelectCursorSub(s8 dir, GSvec2 *pos);

static void _menuPdaDrawFace(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);

static void _SelectCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s8 idx);



static bool _checkAddFunc(tagWINDOW_WORK* window);

extern "C" {

s32 menuPdaBackDrawTitleText(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);

}

static s32 _getMenuIndex(PDATOP_MENU_RES res);

static PDATOP_MENU_RES topMenu(PDATOP_MENU_RES res);

static void _menuPdaTopClose(void);

static void _menuPdaStartEvent(void);

extern "C" {

extern "C" void menuPdaInit(void);

}

extern "C" {

extern "C" void menuPdaMain(void);

}

static void _menuPdaSelectAnimeSet(long n);

extern "C" {

void menuPda(void);

}

extern "C" {

extern "C" s32 menuPdaBackDrawBackXD(void);

}

extern "C" {

extern "C" s32 menuPdaDrawTitle(tagWINDOW_WORK *window, tagSPRITE_WORK *arg1);

}

extern "C" {

extern "C" void menuPdaButton(tagWINDOW_WORK *win);

}

extern "C" {

s32 menuPdaCursorCtrl(tagWINDOW_WORK* window);

}

extern "C" {

extern "C" void menuPdaSetModelPointer(void);

}

extern "C" {

extern "C" void menuPdaReleaseModelPointer(void);

}

extern "C" {

extern "C" void menuPdaDrawDirectModel(void);

}

static void _menuPdaSetMenuItemScript(u8 enable);

static void _menuPdaScriptCalcAlphaInit(void);

static void _menuPdaScriptCalcAlpha(f32 delta);

static u8 _menuPdaScriptGetAlpha(void);

extern "C" {

void menuPdaScript(u8 flag);

}




static bool _checkAddFunc(tagWINDOW_WORK* window) {
    return window->seq == 0x107;
}

s32 menuPdaBackDrawTitleText(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    bool add = _checkAddFunc(window);
    switch (sprite->id) {
    case 7: {
        u32 time = pokecoloGetPlayTimeValue();
        msgctrlSetValue(0x4C, time);
        break;
    }
    case 9:
        msgctrlSetValue(0x69, _menuPdaGetPokecoupon());
        break;
    case 0xB:
        msgctrlSetValue(0x69, _menuPdaGetMoney());
        break;
    case 0xD: {
        u32 value = heroGetStatus(0, 2, 0) & 0xFFFF;
        s32 i = 0;
        s32 x = sprite->x;
        u32 digit;
        x -= 0x12;
        for (; i < 5; i++) {
            digit = value % 10;
            value /= 10;
            msgctrlSetValue(0x34, digit);
            GSmsgPrint2(window->layer, x, 0, (u8)window->alpha | 0xFFFFFF00, 0x426F);
            x -= GSmsgGetRect(0x426F) >> 16;
        }
        break;
    }
    case 0xE:
    case 0xF:
        break;
    case 2:
        if (add && !_addfunc) {
            sprite->alpha = _menuPdaScriptGetAlpha();
        }
        _SelectCursor(window, sprite, 0);
        break;
    case 3:
        _SelectCursor(window, sprite, 1);
        break;
    case 4:
        _SelectCursor(window, sprite, 2);
        break;
    case 5:
        if (add && _addfunc == 1) {
            sprite->alpha = _menuPdaScriptGetAlpha();
        }
        _SelectCursor(window, sprite, 3);
        break;
    case 6:
        _SelectCursor(window, sprite, 4);
        break;
    case 1:
        _menuPdaDrawFace(window, sprite);
        _menuPdaGetCurrentID(window, sprite);
        _menuPdaModelCursorAnime();
        _SelectCursorPositionCheck();
        if (_menuPdaStatus.cur >= 0) {
            _menuPdaStatus.prev = _menuPdaStatus.cur;
        }
        break;
    case 0x173: {
        s32 table[5] = {0x3B53, 0x3B54, 0x3B55, 0x3C03, 0x3B56};
        sprite->msgID = table[menuPdaGetRes()];
        break;
    }
    case 0x1C6: {
        u32 flag = GSflagGet(0x6C2);
        s32 table[7] = {0x3B72, 0x3B73, 0x3B74, 0x3B75, 0x3B76, 0x3B77, 0x3C2E};
        if (flag != 0 && flag <= 8) {
            sprite->msgID = table[flag - 1];
        } else {
            sprite->msgID = 0;
        }
        break;
    }
    case 0x1C8:
        winSpriteSetDisp(sprite, add);
        break;
    case 0x1C9:
        winSpriteSetDisp(sprite, _pdaSelectAnimeFlag);
        break;
    }
    return 0;
}

static s32 _getMenuIndex(PDATOP_MENU_RES res) {
    s16 i;
    for (i = 0; i < _cursor_index_max; i++) {
        if (res == _cursor_index[i]) {
            return i;
        }
    }
    return 0;
}

static PDATOP_MENU_RES topMenu(PDATOP_MENU_RES res) {
    s32 index = _getMenuIndex(res);
    if (menuOpenCustom(0x6B, windowGetActiveID(), &index, 0, 1, 0) == -1) {
        return PDATOP_NONE;
    }
    return (PDATOP_MENU_RES)_menuPdaStatus.cur;
}

static void _menuPdaTopClose(void) {
    menuClose(0x6B);
    menuCloseSync(0x6B, 1);
}

static void _menuPdaStartEvent(void) {
    s32 layers[1] = {0};
    void* model;
    model = GSresGetResourceAllGroup(PDA_MODEL);
    GSmodelSetRenderLayer(model, 1, layers);
    cameraPlayAnime(0x17, 0x17CF1800, 0.0f, 0);
    GSmodelSetRenderCamera(model, GSresGetResource(0x17, 0x17CF1800));
    GSmodelSetVisibility(model, true);
    GSmodelSetBoundCheck(model, false);
    _menuPdaSetMotion(PDA_MODEL, 0, 0.0f, false);
    menuOffScreenSetPriority(0);
    GSthreadSwitch();
    _menuPdaWaitMotion(PDA_MODEL);
    _menuPdaStopMotion(PDA_MODEL);
    _menuPdaSetMotion(PDA_MODEL, 1, 0.0f, true);
}

extern "C" void menuPdaInit(void) {
    void *model = GSresGetResourceAllGroup(0x17CF1000);
    _pModel = model;
    if (model != 0) {
        GSmodelSetVisibility(model, false);
        _menuPdaSetMotion(0x17CF1000, 0, 0.0f, false);
    }
    if (_seon != 0) {
        GSsndPlayNow(0x44E);
    }
}

extern "C" void menuPdaMain(void) {
    for (;;) {
        GSthreadSwitch();
    }
}

static void _menuPdaSelectAnimeSet(long n) {
    char start[0x40];
    char end[0x40];
    if (n >= 4) {
        _pdaSelectAnimeFlag = 0;
    } else {
        _pdaSelectAnimeFlag = 1;
        sprintf(start, "%d_start", n + 1);
        sprintf(end, "%d_end", n + 1);
        FlashSystemSetPlayFrameLabel(0x20543000, start, end);
        FlashSystemSetNowFrameLabel(0x20543000, start);
    }
}

void menuPda(void) {
    s32 res = 0;
    void* model;
    TitleParam param;
    scriptLightSetDisp(0x17CF1600, false);
    scriptLightSetDisp(0x17CF1601, false);
    if (pokecoloGetRomVersion() == 1) {
        GSflagOn(0x3F2);
    }
    FlashSystemSetLoopFlag(0x1FBD3000, true);
    FlashSystemSetLoopFlag(0x20543000, false);
    menuOpen(0xA8, 0);
    model = GSresGetResourceAllGroup(PDA_MODEL);
    _pModel = model;
    GSmodelSetVisibility(model, false);
    GSthreadSwitch();
    _menuPdaStatus.unk41 = 0;
    _menuPdaInit();
    _menuPdaStartEvent();
    _menuPdaSetMenuItem();
    _SelectCursorCalcAngle(_cursor_index[0]);
    _menuPdaStatus.pos = _menuPdaStatus.target;
    param.titleMsg = &TitleMsgID;
    param.flag0 = 0;
    param.alpha = 0xFF;
    param.flag2 = 0;
    param.lineAnim = &LineAnimTime;
    menuOpenCustom(0x6C, windowGetActiveID(), 0, 0, 0, 1, &param);
    while (!_menuPdaStatus.unk41) {
        _menuPdaSetMenuItem();
        res = topMenu((PDATOP_MENU_RES)res);
        _menuPdaStatus.sub = 1;
        _menuPdaStatus.cur = res;
        switch (res) {
        case 0:
            _menuPdaTopClose();
            _menuPdaZoomIn();
            menuPdaDPMonList();
            _menuPdaStatus.sub = 0;
            _menuPdaZoomOut();
            break;
        case 1:
            _menuPdaTopClose();
            _menuPdaZoomIn();
            menuPdaMemoList();
            _menuPdaStatus.sub = 0;
            _menuPdaZoomOut();
            break;
        case 2:
            _menuPdaTopClose();
            _menuPdaZoomIn();
            menuPdaMailListXD();
            _menuPdaStatus.sub = 0;
            _menuPdaZoomOut();
            break;
        case 3:
            _menuPdaTopClose();
            _menuPdaZoomIn();
            menuPdaSearcher();
            _menuPdaStatus.sub = 0;
            _menuPdaZoomOut();
            break;
        default:
            _menPdaFadeOutSet();
            _menuPdaExit();
            _menuPdaStatus.unk41 = 1;
            break;
        }
    }
    _menPdaFadeOutWait();
    if (_menuPdaStatus.unk40 != 1) {
        menuOffScreenSetDisp(1);
        _menuPdaStatus.unk40 = 1;
    }
    _menuPdaTopClose();
    menuClose(0x6C);
    menuCloseSync(0x6C, true);
    menuClose(0xA8);
    menuCloseSync(0xA8, true);
    _menuPdaModelVisibility(PDA_MODEL, false);
    _menPdaFadeInWait();
    menuOffScreenSetPriority(1);
    GSfloorPop();
    floorSetFadeScript(0, 0);
}

extern "C" s32 menuPdaBackDrawBackXD(void) {
    return 0;
}

extern "C" s32 menuPdaDrawTitle(tagWINDOW_WORK *window, tagSPRITE_WORK *arg1) {
    s16 temp_r0;
    s32 temp_r31;
    s32 temp_r3;

    temp_r31 = menuPdaGetRes();
    temp_r3 = menuPdaGetSubres();
    temp_r0 = arg1->id;
    switch (temp_r0) {                              /* irregular */
    case 0x1CA: case 0x1CB: case 0x1CC:
        if ((temp_r31 == 0) && (temp_r3 == 1)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 22:
        if (temp_r31 == 0) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 23:
        if (temp_r31 == 2) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 24:
        if ((temp_r31 == 1) && (temp_r3 == 1)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 26:
        if ((temp_r31 == 1) && (temp_r3 > 1)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 27:
        if ((temp_r31 == 1) && (temp_r3 > 1)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 28:
        if ((temp_r31 == 1) && (temp_r3 > 1)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 29:
        if ((temp_r31 == 1) && (temp_r3 > 1)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 30:
        if ((temp_r31 == 1) && (temp_r3 > 1) && (menuPdaMemoXDGetItem() == 0)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 31:
        if ((temp_r31 == 1) && (temp_r3 > 1) && (menuPdaMemoXDGetItem() == 1)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 32:
        if ((temp_r31 == 1) && (temp_r3 > 1) && (menuPdaMemoXDGetItem() == 2)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 33:
        if ((temp_r31 == 1) && (temp_r3 > 1) && (menuPdaMemoXDGetItem() == 3)) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    case 25:
        if (temp_r31 == 3) {
            winSpriteSetDisp(arg1, 1);
        } else {
            winSpriteSetDisp(arg1, 0);
        }
        break;
    }
    return 0;
}

extern "C" void menuPdaButton(tagWINDOW_WORK *win) {
    if (floorGetCurrent() != 0x38C) {
        menuButtonNormal(win);
    }
}

s32 menuPdaCursorCtrl(tagWINDOW_WORK* window) {
    MenuData* data;
    s32 up;
    s32 down;
    s16 count;
    s32 w;
    s32 h;
    MenuItem* item;
    u16 repeat;
    if (window == 0) {
        return 0;
    }
    if (_checkAddFunc(window)) {
        return 0;
    }
    data = menuDataBiosGetPtr(window->seq);
    if (windowGetCursorToItem(window) == 0) {
        window->cursor = 0;
        return 0;
    }
    w = 0x10;
    h = 0xC;
    repeat = windowGetKeyRepeat();
    up = repeat & 1;
    PdaStatus* status = &_menuPdaStatus;
    down = repeat & 2;
    do {
        count = 0;
        item = menuItemBiosGetPtr(window->seq, data->firstItem);
        if (up) {
            for (;;) {
                if (item->flagA) {
                    count++;
                }
                if (item->flagB) {
                    break;
                }
                item = menuItemBiosGetPtr(window->seq, item->next);
            }
            if (window->cursor > 0) {
                window->cursor--;
                status->arrived = 0;
            } else {
                window->cursor = count - 1;
                status->arrived = 1;
            }
        } else if (down) {
            for (;;) {
                if (item->flagA) {
                    count++;
                }
                if (item->flagB) {
                    break;
                }
                item = menuItemBiosGetPtr(window->seq, item->next);
            }
            if (window->cursor < (s16)count - 1) {
                window->cursor++;
                status->arrived = 0;
            } else {
                window->cursor = 0;
                status->arrived = 1;
            }
        }
        if (window->prevCursor != window->cursor) {
            break;
        }
        w += 0x10;
        h += 0xC;
        if (w >= 0x280) {
            w = 0x280;
        }
        if (h >= 0x1E0) {
            h = 0x1E0;
        }
    } while (w != 0x280 || h != 0x1E0);
    return 0;
}

extern "C" void menuPdaSetModelPointer(void) {
    _pModel = GSresGetResourceAllGroup(0x17CF1000);
}

extern "C" void menuPdaReleaseModelPointer(void) {
    _pModel = GSresGetResourceAllGroup(0x17CF1000);
}

extern "C" void menuPdaDrawDirectModel(void) {
}

static void _menuPdaSetMenuItemScript(u8 enable) {
    if (enable == 0) {
        menuItemBiosSetSelectFlag(0x107, 2, 0);
        menuItemBiosSetSelectFlag(0x107, 5, 0);
    } else {
        menuItemBiosSetSelectFlag(0x107, 2, 1);
        menuItemBiosSetSelectFlag(0x107, 5, 0);
    }
    menuItemBiosSetSelectFlag(0x107, 3, 1);
    menuItemBiosSetSelectFlag(0x107, 4, 1);
    menuItemBiosSetSelectFlag(0x107, 6, 1);
}

static void _menuPdaScriptCalcAlphaInit(void) {
    _pdaScriptAddFrame = 0.0f;
}

static void _menuPdaScriptCalcAlpha(f32 delta) {
    _pdaScriptAddFrame += delta;
}

static u8 _menuPdaScriptGetAlpha(void) {
    f32 a;
    if (_pdaScriptAddFrame >= _pdaScriptTime) {
        return 255;
    }
    a = 255.0f * _pdaScriptAddFrame / _pdaScriptTime;
    if (a > 255.0f) {
        a = 255.0f;
    }
    return a;
}

void menuPdaScript(u8 flag) {
    u32 endFrame;
    TitleParam param2;
    s32 param1 = 0;
    _addfunc = flag;
    if (flag == 0) {
        _menuPdaStatus.cur = 1;
        _menuPdaStatus.prev = 1;
        FlashSystemSetPlayFrameLabel(0x1FBD3000, "1_start", "1_end");
        FlashSystemSetNowFrameLabel(0x1FBD3000, "1_start");
        endFrame = FlashSystemGetFrameFromLabel(0x1FBD3000, "1_end");
    } else {
        _menuPdaStatus.cur = 0;
        _menuPdaStatus.prev = 0;
        FlashSystemSetPlayFrameLabel(0x1FBD3000, "2_start", "2_end");
        FlashSystemSetNowFrameLabel(0x1FBD3000, "2_start");
        endFrame = FlashSystemGetFrameFromLabel(0x1FBD3000, "2_end");
    }
    _SelectCursorCalcAngle(_menuPdaStatus.cur);
    _menuPdaStatus.pos = _menuPdaStatus.target;
    FlashSystemSetLoopFlag(0x1FBD3000, false);
    _menuPdaStatus.sub = 0;
    _menuPdaSetMenuItemScript(flag);
    menuOpen(0xA8, 0);
    menuOpenCustom(0x6C, windowGetActiveID(), 0, 0, 0, 1, &param2);
    menuOpenCustom(0x107, windowGetActiveID(), &param1, 0, 0, 0);
    while (FlashSystemGetNowFrame(0x1FBD3000) < endFrame) {
        GSthreadSwitch();
    }
    _menuPdaScriptCalcAlphaInit();
    GSthreadSwitch();
    if (flag == 0) {
        menuItemBiosSetSelectFlag(0x107, 2, true);
    } else {
        menuItemBiosSetSelectFlag(0x107, 5, true);
    }
    {
        f32 t = 2.0f;
        do {
            f32 dt = timeGetLastFrameSec();
            _menuPdaScriptCalcAlpha(dt);
            t -= dt;
            GSthreadSwitch();
        } while (t >= 0.0f);
    }
    menuClose(0x107);
    menuCloseSync(0x107, true);
    menuClose(0xA8);
    menuClose(0x6C);
    menuCloseSync(0x6C, true);
    menuOffScreenSetPriority(1);
    GSfloorPop();
}

#pragma defer_codegen off
// The model initialization shares this retained full-scale value.
static const struct { f32 value; } pdaModelScale = {1.0f};
#pragma defer_codegen on

extern "C" void menuPdaOpen(void) {
    GSfloorPush(0x392);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
}

static void _menuPdaFree(void *p) {
    GSmemFree(p);
}

static void _menuPdaInit(void) {
    _menuPdaStatus.sub = _menuPdaStatus.prev = _menuPdaStatus.cur = 0;
    _menuPdaStatus.unk14 = _menuPdaStatus.unk18 = _menuPdaStatus.unk1C = 0.0f;
    _menuPdaStatus.unk20 = _menuPdaStatus.unk24 = pdaModelScale.value;
    _menuPdaStatus.unk28 = 300.0f;
    _menuPdaStatus.unk2C = -100.0f;
    _menuPdaStatus.unk38 = _menuPdaStatus.unk34 = _menuPdaStatus.unk30 = 0.0f;
    _menuPdaStatus.unk3C = 0;
    _menuPdaStatus.unk40 = 1;
    _menuPdaStatus.unk41 = 0;
    _menuPdaStatus.arrived = 0;
    _SelectCursorCalcAngle(0);
    _menuPdaInitFlag = 1;
    _menuPdaStatus.pos = _menuPdaStatus.target;
}

static void _menuPdaExit(void) {
    PdaStatus *st = &_menuPdaStatus;
    st->unk30 = 400.0f;
    st->unk34 = -100.0f;
    if (_menuPdaFlashBuffer != 0) {
        _menuPdaFlashBuffer = 0;
    }
    if (_menuPdaTextureBuffer != 0) {
        _menuPdaFree(_menuPdaTextureBuffer);
        _menuPdaTextureBuffer = 0;
    }
}

static void _menuPdaSetMotion(u32 id, s16 index, f32 frame, bool loop) {
    void* model = GSresGetResourceAllGroup(id);
    if (model != 0) {
        GSmodelSetAnimIndex(model, (s32)index);
        GSmodelSetAnimFrame(model, frame);
        GSmodelSetAnimRate(model, 0.5f);
        if (loop) {
            GSmodelSetAnimType(model, 1);
        } else {
            GSmodelSetAnimType(model, 0);
        }
        GSmodelStartAnimation(model);
    }
}

static void _menuPdaWaitMotion(u32 id) {
    void *model = GSresGetResourceAllGroup(id);
    if (model == 0) {
        return;
    }
    while (GSmodelIsAnimating(model)) {
        menuPdaDrawDirectModel();
        GSthreadSwitch();
    }
}

static void _menuPdaStopMotion(u32 id) {
    void *model = GSresGetResourceAllGroup(id);
    if (model != 0) {
        GSmodelStopAnimation(model);
    }
}

static void _menuPdaModelVisibility(u32 id, bool visible) {
    void *model = GSresGetResourceAllGroup(id);
    if (model != 0) {
        GSmodelSetVisibility(model, visible);
    }
}

static s32 _menuPdaModelGetIndex(u32 id) {
    void *model = GSresGetResourceAllGroup(id);
    s32 a;
    s32 b;
    if (model == 0) {
        return -1;
    }
    GSmodelGetAnimIndex(model, &a, &b);
    return a;
}

static u8 _menuPdaWaitMotion2(u32 id) {
    void *model = GSresGetResourceAllGroup(id);
    if (model == 0) {
        return 0;
    }
    return GSmodelIsAnimating(model);
}

s32 menuPdaGetSubres(void) {
    return _menuPdaStatus.sub;
}

s32 menuPdaGetRes(void) {
    return _menuPdaStatus.cur;
}

void menuPdaSetSubres(s32 res, s32 sub) {
    if (res >= 0) {
        _menuPdaStatus.cur = res;
    }
    if (sub >= 0) {
        _menuPdaStatus.sub = sub;
    }
}

static s32 _menuPdaGetPokecoupon(void) {
    return heroGetStatus(0, 0xD, 0);
}

static s32 _menuPdaGetMoney(void) {
    return heroGetStatus(0, 0xC, 0);
}

static void _menPdaFadeOutSet(void) {
    fadeSet(3, 0.8f);
}

static bool _menPdaFadeOutWait(void) {
    s32 state = 0;
    s32 run = 1;
    do {
        switch (state) {
        case 0:
            if (fadeCheck(0) == 0) {
                state = 100;
            } else {
                GSthreadSwitch();
            }
            break;
        case 100:
            run = 0;
            break;
        }
    } while (run);
    return true;
}

static void _menPdaFadeInWait(void) {
    s32 state = 0;
    s32 run = 1;
    do {
        switch (state) {
        case 0:
            fadeSet(2, 0.5f);
            state = 1;
            break;
        case 1:
            if (fadeCheck(0) == 0) {
                state = 100;
            } else {
                GSthreadSwitch();
            }
            break;
        case 100:
            run = 0;
            break;
        }
    } while (run != 0);
}

static void _menuPdaAddFunc(void) {
    _menuPdaSetMotion(0x17CF1000, 8, 0.0f, false);
    _menuPdaWaitMotion(0x17CF1000);
    GSsndPlayNow(0x44E);
    _menuPdaSetMotion(0x17CF1000, 0, 0.0f, false);
    _menuPdaWaitMotion(0x17CF1000);
    _menuPdaSetMotion(0x17CF1000, 1, 0.0f, true);
}

static void _menuPdaZoomIn(void) {
    _menuPdaSetMotion(0x17CF1000, 4, 0.0f, false);
    _menuPdaWaitMotion(0x17CF1000);
    _menuPdaSetMotion(0x17CF1000, 5, 0.0f, false);
    _menuPdaWaitMotion(0x17CF1000);
    _menuPdaSetMotion(0x17CF1000, 6, 0.0f, true);
}

static void _menuPdaZoomOut(void) {
    _menuPdaSetMotion(0x17CF1000, 7, 0.0f, false);
    _menuPdaWaitMotion(0x17CF1000);
    _menuPdaSetMotion(0x17CF1000, 1, 0.0f, true);
}

extern "C" void menuPdaZoomIn(void) {
    _menuPdaZoomIn();
}

extern "C" void menuPdaAddFunc(void) {
    _menuPdaAddFunc();
}

extern "C" void menuPdaModelVisibility(u32 id, bool visible) {
    _menuPdaModelVisibility(id, visible);
}

s32 menuPdaTopCtrl(tagWINDOW_WORK* window) {
    switch (window->state) {
    case 0:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x132);
            window->seqSet = 1;
        }
        break;
    case 3:
        if (window->seqSet == 0) {
            winSeqSetMenu(window->seq, 0x136);
            window->seqSet = 1;
        }
        break;
    }
    return 0;
}

extern "C" s32 menuPdaDummyCtrl(void) {
    menuPdaDrawDirectModel();
    return 0;
}

static void _menuPdaModelCursorAnime(void) {
    if (_menuPdaStatus.cur != _menuPdaStatus.prev) {
        if (_menuPdaStatus.cur > _menuPdaStatus.prev) {
            _menuPdaSetMotion(PDA_MODEL, 2, 0.0f, false);
        } else {
            _menuPdaSetMotion(PDA_MODEL, 3, 0.0f, false);
        }
    }
    if (_menuPdaModelGetIndex(PDA_MODEL) == 3) {
        if (!_menuPdaWaitMotion2(PDA_MODEL)) {
            _menuPdaSetMotion(PDA_MODEL, 1, 0.0f, true);
        }
    }
    if (_menuPdaModelGetIndex(PDA_MODEL) == 2) {
        if (!_menuPdaWaitMotion2(PDA_MODEL)) {
            _menuPdaSetMotion(PDA_MODEL, 1, 0.0f, true);
        }
    }
}

static s8 _menuPdaGetCurrentID(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    u16 id;
    if (_checkAddFunc(window)) {
        return 0;
    }
    id = menuGetCursorItemID(window->seq);
    if (window->prevCursor != window->cursor || _menuPdaInitFlag) {
        _menuPdaSelectAnimeSet(_cursor_index[window->cursor]);
        _menuPdaInitFlag = 0;
    }
    switch (id) {
    case 2:
        _menuPdaStatus.cur = 0;
        break;
    case 3:
        _menuPdaStatus.cur = 1;
        break;
    case 4:
        _menuPdaStatus.cur = 2;
        break;
    case 5:
        _menuPdaStatus.cur = 3;
        break;
    case 6:
        _menuPdaStatus.cur = 4;
        break;
    }
    return _menuPdaStatus.cur;
}

static void _menuPdaSetMenuItem(void) {
    s32 (*t)[2] = pdaitemtable;
    s16 n = 0;
    s16 i = 0;
    for (; i < 5U; t++, i++) {
        if ((*t)[0] == 0) {
            menuItemBiosSetSelectFlag(0x6B, (*t)[1], true);
            _cursor_index[n++] = i;
        } else if (GSflagGet((*t)[0])) {
            menuItemBiosSetSelectFlag(0x6B, (*t)[1], true);
            _cursor_index[n++] = i;
        } else {
            menuItemBiosSetSelectFlag(0x6B, (*t)[1], false);
        }
    }
    _cursor_index_max = n;
}

static bool _SelectCursorPositionCheck(void) {
    f32 dt = timeGetLastFrameSec();
    bool ret = false;
    if (_menuPdaStatus.arrived == 1) {
        _menuPdaStatus.pos = _menuPdaStatus.target;
        ret = true;
    } else if (_menuPdaStatus.target != _menuPdaStatus.pos) {
        f32 diff = _menuPdaStatus.target - _menuPdaStatus.pos;
        f32 step;
        double ab;
        f32 absStep;
        _menuPdaStatus.speed = diff;
        step = diff * dt / 0.1f;
        if (dt == 0.0f) {
            step = 0.0f;
        } else if ((absStep = fabs(step)) <= 0.2f) {
            if (step >= 0.0f) {
                step = 0.2f;
            } else {
                step = -0.2f;
            }
        }
        ab = fabs(step);
        _menuPdaStatus.pos += step;
        if ((f32)fabs(_menuPdaStatus.target - _menuPdaStatus.pos) < (f32)ab) {
            _menuPdaStatus.pos = _menuPdaStatus.target;
            _menuPdaStatus.speed = 0.0f;
            ret = true;
        }
    } else {
        ret = true;
    }
    return ret;
}

static void _SelectCursorCalcAngle(s8 idx) {
    float new_var;
    MenuItem* item = menuItemBiosGetPtr(0x6B, _SelectLabel[idx]);
    new_var = 30.0f;
    _menuPdaStatus.target = (s16)(item->y - 5);
    _menuPdaStatus.ang0 = acos((_menuPdaStatus.pos - _center1[1]) / _r1);
    _menuPdaStatus.ang1 = acos(((_menuPdaStatus.pos + new_var) - _center1[1]) / _r1);
    _menuPdaStatus.ang2 = acos((_menuPdaStatus.pos - _center2[1]) / _r2);
    new_var = 30.0f;
    _menuPdaStatus.ang3 = acos(((_menuPdaStatus.pos + new_var) - _center2[1]) / _r2);
    _menuPdaStatus.angD0 = _menuPdaStatus.ang1 - _menuPdaStatus.ang0;
    _menuPdaStatus.angD1 = _menuPdaStatus.ang3 - _menuPdaStatus.ang2;
}

static s32 _SelectCursorCalcPositon(GSvec2* out) {
    f32 d1 = (_menuPdaStatus.ang1 - _menuPdaStatus.ang0) / 16.0f;
    f32 d2 = (_menuPdaStatus.ang3 - _menuPdaStatus.ang2) / 16.0f;
    s32 n;
    s32 i;
    s32 prev;
    f32 a;
    n = 0;
    out[n].x = _r1 * (f32)sin(_menuPdaStatus.ang0) + _center1[0];
    out[n].y = _r1 * (f32)cos(_menuPdaStatus.ang0) + _center1[1];
    n++;
    for (i = 0; i < 16; i++) {
        a = (f32)i * d2 + _menuPdaStatus.ang2;
        out[n].x = _r2 * (f32)sin(a) + _center2[0];
        out[n].y = _r2 * (f32)cos(a) + _center2[1];
        n++;
    }
    prev = n - 1;
    for (i = 0; i < 16; i++) {
        a = d1 * (f32)(15 - i) + _menuPdaStatus.ang0;
        out[n].x = _r1 * (f32)sin(a) + _center1[0];
        if (i == 0) {
            out[n].y = out[prev].y;
        } else {
            out[n].y = _r1 * (f32)cos(a) + _center1[1];
        }
        n++;
    }
    return n;
}

static s32 _SelectCursorSub(s8 dir, GSvec2 *pos) {
    _SelectCursorCalcAngle(dir);
    return _SelectCursorCalcPositon(pos);
}

static void _menuPdaDrawFace(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s32 id = 0;
    Hero* hero = (Hero*)savedataGetStatus(0, 2);
    switch (hero->getHeroStyle()) {
    case 0:
        id = 0x123;
        break;
    case 2:
        id = 0x3A1;
        break;
    case 1:
        id = 0x3A2;
        break;
    }
    windowDrawSprite(0, 0, window, id, 0, window->layer);
}

static void _SelectCursor(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, s8 idx) {
    s32 alpha;
    f32 half;
    GSgfxLayer* layer;
    GSvec2 buf[72];
    s32 n;
    s32 i;
    MenuItem* item;
    f32 d;
    GSgfxVF* vf;
    _checkAddFunc(window);
    half = _next_height / 2.0f;
    if (menuItemBiosGetSelectFlag(0x6B, sprite->id)) {
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
    if (_menuPdaStatus.cur == idx) {
        layer = GSgfxLayerFindByID(window->layer);
        if (layer != 0) {
            d = fabs(_menuPdaStatus.target - _menuPdaStatus.pos);
            if (d > _next_height) {
                d = _next_height;
            }
            d = fabs(d - half);
            alpha = (s32)(255.0f * (d / half));
            n = _SelectCursorSub(idx, buf);
            item = menuItemBiosGetPtr(0x6B, sprite->id);
            for (i = 0; i < n; i++) {
                buf[i].x -= item->x;
                buf[i].y -= item->y;
            }
            if (layer->curSurfaceIdx != 1) {
                layer->curSurfaceIdx = 1;
                layer->curSurface = layer->surfaces[layer->curSurfaceIdx];
            }
            layer->unk1644 = 1;
            layer->unk1648 = 4;
            layer->unk164C = 1;
            layer->unk1650 = 5;
            layer->unk170C |= 1;
            layer->unk16A8 |= 0x40;
            layer->unk17C4 |= 1;
            layer->unk1760 |= 0x40;
            vf = GSgfxVFGetPredef(3);
            layer->unk1998 = 0xA0;
            layer->setRenderStateAndSelect(vf);
            layer->beginSurface(n);
            for (i = 0; i < n; i++) {
                GXWGFifo.s16 = (s16)buf[i].x;
                GXWGFifo.s16 = (s16)buf[i].y;
                GXWGFifo.u32 = 0x405A2600 | (u8)alpha;
            }
            layer->endSurface();
            if (layer->curSurfaceIdx != 1) {
                layer->curSurfaceIdx = 1;
                layer->curSurface = layer->surfaces[layer->curSurfaceIdx];
            }
            layer->unk1644 = 1;
            layer->unk1648 = 4;
            layer->unk164C = 5;
            layer->unk1650 = 5;
            layer->unk170C |= 1;
            layer->unk16A8 |= 0x40;
            layer->unk17C4 |= 1;
            layer->unk1760 |= 0x40;
        }
    }
}
