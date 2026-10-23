#include <game/menuPdaLayout.hpp>
#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/hero/hero.hpp>

struct GSgfxVF;
struct GStexture;
struct GSgfxMatrixStack;
struct GSgfxShader { u8 state[0xBC]; };
struct GXColorS10 { s16 r,g,b,a; };
struct GSgfxLayer {
    u8 reserved00[0x28];
    u32 id;
    u8 reserved2c[0xd34 - 0x2c];
    u8 lineWidth;
    u8 reservedD35[3];
    u32 lineTexOffset;
    u8 pointSize;
    u8 reservedD3d[3];
    u32 pointTexOffset;
    u8 reservedD44[0xd54 - 0xd44];
    u32 projectionType;
    f32 projection[6];
    u8 reservedD70[0xd8c - 0xd70];
    u32 cullMode;
    u8 reservedD90[0xf70 - 0xd90];
    u32 tevColorInputs[4];
    u8 reservedF80[0x1070 - 0xf80];
    u32 tevAlphaInputs[4];
    u8 reserved1080[0x1170 - 0x1080];
    u32 tevColorOperation, tevColorBias, tevColorScale;
    u8 tevColorClamp;
    u8 reserved117d[3];
    u32 tevColorOutput;
    u8 reserved1184[0x12b0 - 0x1184];
    u32 tevAlphaOperation, tevAlphaBias, tevAlphaScale;
    u8 tevAlphaClamp;
    u8 reserved12bd[3];
    u32 tevAlphaOutput;
    u8 reserved12c4[0x13fc - 0x12c4];
    u32 tevConstantIndex;
    GXColorS10 tevConstant;
    u8 reserved1408[0x1644 - 0x1408];
    u32 blendMode, blendSource, blendDestination, blendLogic;
    u8 reserved1654[2];
    u8 colorUpdate, alphaUpdate, destinationAlpha;
    u8 reserved1659[3];
    u8 depthEnable;
    u8 reserved165d[3];
    u32 depthFunction;
    u32 alphaFunction0, alphaOperation, alphaFunction1;
    u8 alphaReference0, alphaReference1, depthBeforeTexture;
    u8 reserved1673[0x1684 - 0x1673];
    f32 depthNear, depthFar;
    u8 reserved168c[0x16a6 - 0x168c];
    u8 fogRangeAdjust, fogEnable;
    u32 dirty, rasterDirty;
    u8 reserved16b0[8];
    u32 transformDirty;
    u8 reserved16bc[0x16d4 - 0x16bc];
    u32 tevColorInputDirty, tevAlphaInputDirty, tevColorOperationDirty, tevAlphaOperationDirty, tevConstantDirty;
    u8 reserved16e8[0x170c - 0x16e8];
    u32 pixelDirty;
    u8 reserved1710[0x173c - 0x1710];
    u32 textureDirty;
    GStexture* texture;
    u8 reserved1744[0x1760 - 0x1744];
    u32 savedDirty, savedRasterDirty;
    u8 reserved1768[8];
    u32 savedTransformDirty;
    u8 reserved1774[0x178c - 0x1774];
    u32 savedTevColorInputDirty, savedTevAlphaInputDirty, savedTevColorOperationDirty, savedTevAlphaOperationDirty, savedTevConstantDirty;
    u8 reserved17a0[0x17c4 - 0x17a0];
    u32 savedPixelDirty;
    u8 reserved17c8[0x17f4 - 0x17c8];
    u32 savedTextureDirty;
    GStexture* savedTexture;
    u8 reserved17fc[0x1818 - 0x17fc];
    GSgfxShader shaders[2];
    GSgfxShader* shader;
    s32 shaderIndex;
    u32 primitive;
    u8 reserved199c[4];
    GSgfxMatrixStack* matrixStack;

    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};
extern "C" GSgfxLayer *GSgfxLayerFindByID(u32);

enum PDATOP_MENU_RES { PDATOP_MENU_RES_0 };


extern "C" {
void *GSresGetResourceAllGroup(u32);
u32 floorGetCurrent(void);
void menuButtonNormal(tagWINDOW_WORK *);
void GSthreadSwitch(void);
void menuClose(s32);
void menuCloseSync(s32, s32);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
void *heroGetStatus(s32, s32, s32);
void GSmemFree(void *);
void GSfloorPush(s32);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void fadeSet(s32, f32);
s8 fadeCheck(s32);
void GSsndPlayNow(u32);
void GSmodelSetAnimIndex(void *, s32);
void GSmodelSetAnimFrame(void *, f32);
void GSmodelSetAnimRate(void *, f32);
void GSmodelSetAnimType(void *, s32);
void GSmodelStartAnimation(void *);
void GSmodelStopAnimation(void *);
void GSmodelSetVisibility(void *, bool);
u8 GSmodelIsAnimating(void *);
void GSmodelGetAnimIndex(void *, s32 *, s32 *);
void GSmodelSetRenderLayer(void *, s32, void *);
void GSmodelSetRenderCamera(void *, void *);
void GSmodelSetBoundCheck(void *, s32);
void *GSresGetResource(s32, u32);
void cameraPlayAnime(s32, u32, s32, f32);
void menuOffScreenSetPriority(s32);
void FlashSystemSetPlayFrameLabel(u32, const char *, const char *);
void FlashSystemSetNowFrameLabel(u32, const char *);
void winSeqSetMenu(s32, s32);
u32 windowGetCursorToItem(tagWINDOW_WORK *);
void *menuDataBiosGetPtr(s32);
u16 windowGetKeyRepeat(void);
u32 FlashSystemGetFrameFromLabel(u32, const char *);
void FlashSystemSetLoopFlag(u32, s32);
u32 FlashSystemGetNowFrame(u32);
void GSfloorPop(void);
s32 menuOpen(s32, s32);
f32 timeGetLastFrameSec(void);
double acos(double);
double sin(double);
double cos(double);
double __fabs(double);
void *menuItemBiosGetPtr(s32, s32);
void menuItemBiosSetSelectFlag(s32, s32, s32);
u32 GSflagGet(s32);
u16 menuGetCursorItemID(s32);
Hero *savedataGetStatus(s32, s32);
void windowDrawSprite(s32, s32, tagWINDOW_WORK *, s32, s32, s32);
}

extern "C" int sprintf(char *, const char *, ...);


struct PdaStatus {
    s32 res;
    s32 subres;
    s32 unk8;
    u8 pad0C[8];
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
    u8 pad42[2];
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    u8 unk68;
    u8 pad69[3];
};

struct PdaItem {
    s32 flag;
    s32 item;
};
static PdaItem pdaitemtable[5] = {{0x3F2, 2}, {0, 3}, {0, 4}, {0x3F3, 5}, {0, 6}};
static s32 _SelectLabel[5] = {2, 3, 4, 5, 6};
static s16 _cursor_index[5];
static PdaStatus _menuPdaStatus;
static u8 _menuPdaInitFlag = 1;
static u8 _seon = 1;
static f32 _pdaScriptTime = 1.5f;
static GSvec2 _center1 = {206.0f, 238.0f};
static f32 _r1 = 180.0f;
static GSvec2 _center2 = {459.0f, 238.0f};
static f32 _r2 = 150.0f;
static f32 _next_height = 36.0f;
static void *_menuPdaFlashBuffer;
static void *_menuPdaTextureBuffer;
static u8 _addfunc;
static u8 _pdaSelectAnimeFlag;
static s16 _cursor_index_max;
void *_pModel;
static s32 TitleMsgID;
static s32 LineAnimTime;
static f32 _pdaScriptAddFrame;

static void _menuPdaFree(void *);
static void _menuPdaSetMotion(u32, s16, f32, bool);
static void _menuPdaWaitMotion(u32);
static void _menuPdaModelVisibility(u32, bool);
static void _menuPdaAddFunc(void);
static void _menuPdaZoomIn(void);
static s32 _getMenuIndex(PDATOP_MENU_RES);
static void _SelectCursorCalcAngle(s8);
static s32 _SelectCursorCalcPositon(GSvec2 *);

static s32 _menuPdaScriptGetAlpha(void) {
    if (_pdaScriptAddFrame >= _pdaScriptTime) {
        return 255;
    }
    f32 a = 255.0f * _pdaScriptAddFrame / _pdaScriptTime;
    if (a > 255.0f) {
        a = 255.0f;
    }
    return (s32)a;
}

static void _menuPdaScriptCalcAlpha(f32 delta) {
    _pdaScriptAddFrame += delta;
}

static void _menuPdaScriptCalcAlphaInit(void) {
    _pdaScriptAddFrame = 0.0f;
}

extern "C" void menuPdaDrawDirectModel(void) {
}

extern "C" void menuPdaReleaseModelPointer(void) {
    _pModel = GSresGetResourceAllGroup(0x17CF1000);
}

extern "C" void menuPdaSetModelPointer(void) {
    _pModel = GSresGetResourceAllGroup(0x17CF1000);
}

extern "C" void menuPdaButton(tagWINDOW_WORK *win) {
    if (floorGetCurrent() != 0x38C) {
        menuButtonNormal(win);
    }
}

extern "C" s32 menuPdaBackDrawBackXD(void) {
    return 0;
}

extern "C" void menuPdaMain(void) {
    for (;;) {
        GSthreadSwitch();
    }
}

static void _menuPdaTopClose(void) {
    menuClose(0x6B);
    menuCloseSync(0x6B, 1);
}

static s32 topMenu(PDATOP_MENU_RES res) {
    s32 index = _getMenuIndex(res);
    s32 ret = menuOpenCustom(0x6B, windowGetActiveID(), &index, 0, 1, 0);
    if (ret == -1) {
        return -1;
    }
    return _menuPdaStatus.res;
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

static bool _checkAddFunc(tagWINDOW_WORK *win) {
    return win->menu == 0x107;
}

static s32 _SelectCursorSub(s8 dir, GSvec2 *pos) {
    _SelectCursorCalcAngle(dir);
    return _SelectCursorCalcPositon(pos);
}

extern "C" s32 menuPdaDummyCtrl(void) {
    menuPdaDrawDirectModel();
    return 0;
}

extern "C" void menuPdaModelVisibility(u32 id, bool visible) {
    _menuPdaModelVisibility(id, visible);
}

extern "C" void menuPdaAddFunc(void) {
    _menuPdaAddFunc();
}

extern "C" void menuPdaZoomIn(void) {
    _menuPdaZoomIn();
}

static void _menuPdaZoomOut(void) {
    _menuPdaSetMotion(0x17CF1000, 7, 0.0f, false);
    _menuPdaWaitMotion(0x17CF1000);
    _menuPdaSetMotion(0x17CF1000, 1, 0.0f, true);
}

static void _menPdaFadeOutSet(void) {
    fadeSet(3, 0.8f);
}

static void *_menuPdaGetMoney(void) {
    return heroGetStatus(0, 0xC, 0);
}

static void *_menuPdaGetPokecoupon(void) {
    return heroGetStatus(0, 0xD, 0);
}

extern "C" void menuPdaSetSubres(s32 res, s32 subres) {
    if (res >= 0) {
        _menuPdaStatus.res = res;
    }
    if (subres >= 0) {
        _menuPdaStatus.subres = subres;
    }
}

extern "C" s32 menuPdaGetRes(void) {
    return _menuPdaStatus.res;
}

extern "C" s32 menuPdaGetSubres(void) {
    return _menuPdaStatus.subres;
}

static u8 _menuPdaWaitMotion2(u32 id) {
    void *model = GSresGetResourceAllGroup(id);
    if (model == 0) {
        return 0;
    }
    return GSmodelIsAnimating(model);
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

static void _menuPdaModelVisibility(u32 id, bool visible) {
    void *model = GSresGetResourceAllGroup(id);
    if (model != 0) {
        GSmodelSetVisibility(model, visible);
    }
}

static void _menuPdaStopMotion(u32 id) {
    void *model = GSresGetResourceAllGroup(id);
    if (model != 0) {
        GSmodelStopAnimation(model);
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

static void _menuPdaFree(void *p) {
    GSmemFree(p);
}

extern "C" void menuPdaOpen(void) {
    GSfloorPush(0x392);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
}

static void _menuPdaSetMotion(u32 id, s16 anim, f32 frame, bool loop) {
    void *model = GSresGetResourceAllGroup(id);
    if (model != 0) {
        GSmodelSetAnimIndex(model, anim);
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

static s32 _menPdaFadeOutWait(void) {
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
    } while (run != 0);
    return 1;
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

extern "C" s32 menuPdaTopCtrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x132);
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x136);
            win->step = 1;
        }
        break;
    }
    return 0;
}

static void _menuPdaInit(void) {
    PdaStatus *st = &_menuPdaStatus;
    s32 zero = 0;
    st->res = zero;
    st->unk8 = zero;
    st->subres = zero;
    st->unk1C = 0.0f;
    st->unk18 = 0.0f;
    st->unk14 = 0.0f;
    st->unk24 = 1.0f;
    st->unk20 = 1.0f;
    st->unk28 = 300.0f;
    st->unk2C = -100.0f;
    st->unk30 = 0.0f;
    st->unk34 = 0.0f;
    st->unk38 = 0.0f;
    st->unk3C = zero;
    st->unk40 = 1;
    st->unk41 = zero;
    st->unk68 = zero;
    _SelectCursorCalcAngle(0);
    _menuPdaInitFlag = 1;
    _menuPdaStatus.unk5C = _menuPdaStatus.unk60;
}

static void _menuPdaStartEvent(void) {
    u32 layer[1] = {0};
    void *model = GSresGetResourceAllGroup(0x17CF1000);
    GSmodelSetRenderLayer(model, 1, layer);
    cameraPlayAnime(0x17, 0x17CF1800, 0, 0.0f);
    GSmodelSetRenderCamera(model, GSresGetResource(0x17, 0x17CF1800));
    GSmodelSetVisibility(model, true);
    GSmodelSetBoundCheck(model, false);
    _menuPdaSetMotion(0x17CF1000, 0, 0.0f, false);
    menuOffScreenSetPriority(0);
    GSthreadSwitch();
    _menuPdaWaitMotion(0x17CF1000);
    _menuPdaStopMotion(0x17CF1000);
    _menuPdaSetMotion(0x17CF1000, 1, 0.0f, true);
}

static void _menuPdaDrawFace(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    s32 id = 0;
    switch (savedataGetStatus(0, 2)->getHeroStyle()) {
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
    windowDrawSprite(0, 0, win, id, 0, win->layer);
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

static void _menuPdaSetMenuItem(void) {
    PdaItem *item = pdaitemtable;
    s16 count = 0;
    s16 i;
    for (i = 0; (u32)i < 5; item++, i++) {
        if (item->flag == 0) {
            menuItemBiosSetSelectFlag(0x6B, item->item, 1);
            _cursor_index[count++] = i;
        } else if (GSflagGet(item->flag) != 0) {
            menuItemBiosSetSelectFlag(0x6B, item->item, 1);
            _cursor_index[count++] = i;
        } else {
            menuItemBiosSetSelectFlag(0x6B, item->item, 0);
        }
    }
    _cursor_index_max = count;
}

static s8 _menuPdaGetCurrentID(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    s32 id;
    if (_checkAddFunc(win)) {
        return 0;
    }
    id = menuGetCursorItemID(win->menu);
    if (win->prevSelected != win->pos.selected || _menuPdaInitFlag != 0) {
        _menuPdaSelectAnimeSet(_cursor_index[win->pos.selected]);
        _menuPdaInitFlag = 0;
    }
    switch (id) {
    case 2:
        _menuPdaStatus.res = 0;
        break;
    case 3:
        _menuPdaStatus.res = 1;
        break;
    case 4:
        _menuPdaStatus.res = 2;
        break;
    case 5:
        _menuPdaStatus.res = 3;
        break;
    case 6:
        _menuPdaStatus.res = 4;
        break;
    }
    return _menuPdaStatus.res;
}

static void _menuPdaModelCursorAnime(void) {
    if (_menuPdaStatus.res != _menuPdaStatus.unk8) {
        if (_menuPdaStatus.res > _menuPdaStatus.unk8) {
            _menuPdaSetMotion(0x17CF1000, 2, 0.0f, false);
        } else {
            _menuPdaSetMotion(0x17CF1000, 3, 0.0f, false);
        }
    }
    if (_menuPdaModelGetIndex(0x17CF1000) == 3) {
        if (!_menuPdaWaitMotion2(0x17CF1000)) {
            _menuPdaSetMotion(0x17CF1000, 1, 0.0f, true);
        }
    }
    if (_menuPdaModelGetIndex(0x17CF1000) == 2) {
        if (!_menuPdaWaitMotion2(0x17CF1000)) {
            _menuPdaSetMotion(0x17CF1000, 1, 0.0f, true);
        }
    }
}

struct PdaMenuItem {
    u8 pad[8];
    s16 y;
};

static void _SelectCursorCalcAngle(s8 sel) {
    PdaMenuItem *item = (PdaMenuItem *)menuItemBiosGetPtr(0x6B, _SelectLabel[sel]);
    _menuPdaStatus.unk60 = (f32)(s16)(item->y - 5);
    _menuPdaStatus.unk44 = (f32)acos((_menuPdaStatus.unk5C - _center1.y) / _r1);
    _menuPdaStatus.unk48 = (f32)acos((_menuPdaStatus.unk5C + 30.0f - _center1.y) / _r1);
    _menuPdaStatus.unk4C = (f32)acos((_menuPdaStatus.unk5C - _center2.y) / _r2);
    _menuPdaStatus.unk50 = (f32)acos((_menuPdaStatus.unk5C + 30.0f - _center2.y) / _r2);
    _menuPdaStatus.unk54 = _menuPdaStatus.unk48 - _menuPdaStatus.unk44;
    _menuPdaStatus.unk58 = _menuPdaStatus.unk50 - _menuPdaStatus.unk4C;
}

static s32 _SelectCursorPositionCheck(void) {
    f32 dt = timeGetLastFrameSec();
    s32 ret = 0;
    if (_menuPdaStatus.unk68 == 1) {
        _menuPdaStatus.unk5C = _menuPdaStatus.unk60;
        return 1;
    }
    if (_menuPdaStatus.unk60 != _menuPdaStatus.unk5C) {
        f32 diff = _menuPdaStatus.unk60 - _menuPdaStatus.unk5C;
        f32 step;
        _menuPdaStatus.unk64 = diff;
        step = diff * dt / 0.1f;
        if (dt == 0.0f) {
            step = 0.0f;
        } else if ((f32)__fabs(step) <= 0.2f) {
            if (step >= 0.0f) {
                step = 0.2f;
            } else {
                step = -0.2f;
            }
        }
        f32 aStep = __fabs(step);
        f32 t2 = _menuPdaStatus.unk60;
        f32 n = _menuPdaStatus.unk5C + step;
        _menuPdaStatus.unk5C = n;
        if ((f32)__fabs(t2 - n) < aStep) {
            _menuPdaStatus.unk5C = t2;
            _menuPdaStatus.unk64 = 0.0f;
            ret = 1;
        }
    } else {
        ret = 1;
    }
    return ret;
}

static s32 _SelectCursorCalcPositon(GSvec2 *out) {
    f32 stepA = (_menuPdaStatus.unk48 - _menuPdaStatus.unk44) * 0.0625f;
    f32 stepB = (_menuPdaStatus.unk50 - _menuPdaStatus.unk4C) * 0.0625f;
    s32 n;
    s32 i;
    GSvec2 *p;
    out->x = _r1 * (f32)sin(_menuPdaStatus.unk44) + _center1.x;
    out->y = _r1 * (f32)cos(_menuPdaStatus.unk44) + _center1.y;
    n = 1;
    p = out + n;
    for (i = 0; i < 16; i++) {
        f32 ang = (f32)i * stepB + _menuPdaStatus.unk4C;
        p->x = _r2 * (f32)sin(ang) + _center2.x;
        n++;
        p->y = _r2 * (f32)cos(ang) + _center2.y;
        p++;
    }
    GSvec2 *q = out + n;
    s32 lastY = (n - 1) * 8 + 4;
    for (i = 0; i < 16; i++) {
        f32 ang = stepA * (f32)(15 - i) + _menuPdaStatus.unk44;
        q->x = _r1 * (f32)sin(ang) + _center1.x;
        if (i == 0) {
            q->y = *(f32 *)((u8 *)out + lastY);
        } else {
            q->y = _r1 * (f32)cos(ang) + _center1.y;
        }
        q++;
        n++;
    }
    return n;
}

struct PdaTitleParams {
    u8 field0, field1, field2;
    s32 *title, *time;
};

extern "C" void menuPdaScript(u8 mode) {
    PdaTitleParams titleParams;
    s32 sp08;
    f32 remain;
    u32 endFrame;
    sp08 = 0;
    _addfunc = mode;
    if (mode == 0) {
        _menuPdaStatus.res = 1;
        _menuPdaStatus.unk8 = 1;
        FlashSystemSetPlayFrameLabel(0x1FBD3000, "1_start", "1_end");
        FlashSystemSetNowFrameLabel(0x1FBD3000, "1_start");
        endFrame = FlashSystemGetFrameFromLabel(0x1FBD3000, "1_end");
    } else {
        _menuPdaStatus.res = 0;
        _menuPdaStatus.unk8 = 0;
        FlashSystemSetPlayFrameLabel(0x1FBD3000, "2_start", "2_end");
        FlashSystemSetNowFrameLabel(0x1FBD3000, "2_start");
        endFrame = FlashSystemGetFrameFromLabel(0x1FBD3000, "2_end");
    }
    _SelectCursorCalcAngle(_menuPdaStatus.res);
    _menuPdaStatus.unk5C = _menuPdaStatus.unk60;
    FlashSystemSetLoopFlag(0x1FBD3000, 0);
    _menuPdaStatus.subres = 0;
    _menuPdaSetMenuItemScript(mode);
    menuOpen(0xA8, 0);
    menuOpenCustom(0x6C, windowGetActiveID(), 0, 0, 0, 1, &titleParams);
    menuOpenCustom(0x107, windowGetActiveID(), &sp08, 0, 0, 0);
    while (FlashSystemGetNowFrame(0x1FBD3000) < endFrame) {
        GSthreadSwitch();
    }
    _menuPdaScriptCalcAlphaInit();
    GSthreadSwitch();
    if (mode == 0) {
        menuItemBiosSetSelectFlag(0x107, 2, 1);
    } else {
        menuItemBiosSetSelectFlag(0x107, 5, 1);
    }
    remain = 2.0f;
    do {
        f32 dt = timeGetLastFrameSec();
        _menuPdaScriptCalcAlpha(dt);
        remain -= dt;
        GSthreadSwitch();
    } while (remain >= 0.0f);
    menuClose(0x107);
    menuCloseSync(0x107, 1);
    menuClose(0xA8);
    menuClose(0x6C);
    menuCloseSync(0x6C, 1);
    menuOffScreenSetPriority(1);
    GSfloorPop();
}

struct PdaMenuData {
    u8 pad[6];
    s16 first;
};

struct PdaCursorItem {
    u8 selectable : 1;
    u8 last : 1;
    u8 rest : 6;
    u8 pad[0x17];
    s16 next;
};

extern "C" s32 menuPdaCursorCtrl(tagWINDOW_WORK *win) {
    PdaMenuData *data;
    PdaCursorItem *item;
    s32 left;
    s32 right;
    s16 count;
    s32 stepX;
    s32 stepY;
    u16 key;
    if (win == 0) {
        return 0;
    }
    if (_checkAddFunc(win)) {
        return 0;
    }
    data = (PdaMenuData *)menuDataBiosGetPtr(win->menu);
    if (windowGetCursorToItem(win) == 0) {
        win->pos.selected = 0;
        return 0;
    }
    stepX = 0x10;
    stepY = 0xC;
    key = windowGetKeyRepeat();
    left = key & 1;
    right = key & 2;
    for (;;) {
        count = 0;
        item = (PdaCursorItem *)menuItemBiosGetPtr(win->menu, data->first);
        if (left != 0) {
            for (;;) {
                if (item->selectable != 0) {
                    count++;
                }
                if (item->last != 0) {
                    break;
                }
                item = (PdaCursorItem *)menuItemBiosGetPtr(win->menu, item->next);
            }
            if (win->pos.selected > 0) {
                win->pos.selected--;
                _menuPdaStatus.unk68 = 0;
            } else {
                win->pos.selected = count - 1;
                _menuPdaStatus.unk68 = 1;
            }
        } else if (right != 0) {
            for (;;) {
                if (item->selectable != 0) {
                    count++;
                }
                if (item->last != 0) {
                    break;
                }
                item = (PdaCursorItem *)menuItemBiosGetPtr(win->menu, item->next);
            }
            if (win->pos.selected < count - 1) {
                win->pos.selected++;
                _menuPdaStatus.unk68 = 0;
            } else {
                win->pos.selected = 0;
                _menuPdaStatus.unk68 = 1;
            }
        }
        if (win->prevSelected == win->pos.selected) {
            stepX += 0x10;
            stepY += 0xC;
            if (stepX >= 0x280) {
                stepX = 0x280;
            }
            if (stepY >= 0x1E0) {
                stepY = 0x1E0;
            }
            if (stepX != 0x280 || stepY != 0x1E0) {
                continue;
            }
        }
        break;
    }
    return 0;
}

extern "C" { s32 menuPdaMemoXDGetItem(); void winSpriteSetDisp(tagSPRITE_WORK *, u8); }

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

extern "C" {
void scriptLightSetDisp(u32,s32);
s32 pokecoloGetRomVersion();
void GSflagOn(s32);
void menuPdaDPMonList();
void menuPdaMemoList();
void menuPdaMailListXD();
void menuPdaSearcher();
void menuOffScreenSetDisp(s32);
void menuPda()
{
    PdaTitleParams args;
    s32 selected = 0;
    scriptLightSetDisp(0x17CF1600,0);
    scriptLightSetDisp(0x17CF1601,0);
    if (pokecoloGetRomVersion() == 1) GSflagOn(0x3F2);
    FlashSystemSetLoopFlag(0x1FBD3000,1);
    FlashSystemSetLoopFlag(0x20543000,0);
    menuOpen(0xA8,0);
    _pModel = GSresGetResourceAllGroup(0x17CF1000);
    GSmodelSetVisibility(_pModel,false);
    GSthreadSwitch();
    _menuPdaStatus.unk41 = 0;
    _menuPdaInit();
    _menuPdaStartEvent();
    _menuPdaSetMenuItem();
    _SelectCursorCalcAngle(_cursor_index[0]);
    _menuPdaStatus.unk5C = _menuPdaStatus.unk60;
    args.title = &TitleMsgID;
    args.field0 = 0; args.field1 = -1; args.field2 = 0;
    args.time = &LineAnimTime;
    menuOpenCustom(0x6C,windowGetActiveID(),0,0,0,1,&args);
    while (_menuPdaStatus.unk41 == 0) {
        _menuPdaSetMenuItem();
        selected = topMenu((PDATOP_MENU_RES)selected);
        _menuPdaStatus.subres = 1;
        _menuPdaStatus.res = selected;
        switch (selected) {
        case 0:
            _menuPdaTopClose(); _menuPdaZoomIn(); menuPdaDPMonList();
            _menuPdaStatus.subres = 0; _menuPdaZoomOut(); break;
        case 1:
            _menuPdaTopClose(); _menuPdaZoomIn(); menuPdaMemoList();
            _menuPdaStatus.subres = 0; _menuPdaZoomOut(); break;
        case 2:
            _menuPdaTopClose(); _menuPdaZoomIn(); menuPdaMailListXD();
            _menuPdaStatus.subres = 0; _menuPdaZoomOut(); break;
        case 3:
            _menuPdaTopClose(); _menuPdaZoomIn(); menuPdaSearcher();
            _menuPdaStatus.subres = 0; _menuPdaZoomOut(); break;
        default:
            _menPdaFadeOutSet(); _menuPdaExit(); _menuPdaStatus.unk41 = 1; break;
        }
    }
    _menPdaFadeOutWait();
    if (_menuPdaStatus.unk40 != 1) {
        menuOffScreenSetDisp(1); _menuPdaStatus.unk40 = 1;
    }
    _menuPdaTopClose();
    menuClose(0x6C); menuCloseSync(0x6C,1);
    menuClose(0xA8); menuCloseSync(0xA8,1);
    _menuPdaModelVisibility(0x17CF1000,false);
    _menPdaFadeInWait(); menuOffScreenSetPriority(1); GSfloorPop(); floorSetFadeScript(0,0);
}
}

extern "C" {
u8 menuItemBiosGetSelectFlag(s32,s16);
GSgfxVF *GSgfxVFGetPredef(s32);
void msgctrlSetValue(s32,void *);
u32 GSmsgGetRect(s32);
void GSmsgPrint2(s32,s32,s32,u32,s32);
s32 pokecoloGetPlayTimeValue();
}
static void _SelectCursor(tagWINDOW_WORK *window,tagSPRITE_WORK *sprite,s8 index)
{
    GSvec2 vertices[72];
    s32 alpha;
    _checkAddFunc(window);
    f32 height = _next_height;
    f32 half = height / 2.0f;
    if (menuItemBiosGetSelectFlag(0x6B,sprite->id)) winSpriteSetDisp(sprite,1);
    else winSpriteSetDisp(sprite,0);
    if (_menuPdaStatus.res == index) {
        GSgfxLayer *layer = GSgfxLayerFindByID(window->layer);
        if (layer) {
            f32 delta = __fabs(_menuPdaStatus.unk60 - _menuPdaStatus.unk5C);
            if (delta > _next_height) delta = _next_height;
            alpha = 255.0f * ((f32)__fabs(delta - half) / half);
            s32 count = _SelectCursorSub(index,vertices);
            struct Item { u8 pad[6]; s16 x,y; };
            Item *item = (Item *)menuItemBiosGetPtr(0x6B,sprite->id);
            for (s32 i=0;i<count;i++) {
                vertices[i].x -= item->x; vertices[i].y -= item->y;
            }
            if (layer->shaderIndex != 1) {
                layer->shaderIndex = 1;
                layer->shader = &layer->shaders[layer->shaderIndex];
            }
            u32 one=1; u32 four=4;
            layer->blendMode=one;layer->blendSource=four;layer->blendDestination=one;layer->blendLogic=5;
            layer->pixelDirty|=1;layer->dirty|=0x40;layer->savedPixelDirty|=1;layer->savedDirty|=0x40;
            GSgfxVF *format = GSgfxVFGetPredef(3);
            layer->primitive=0xA0;
            layer->setRenderStateAndSelect(format);
            layer->beginSurface(count);
            for (s32 i=0;i<count;i++) {
                *(volatile s16 *)0xCC008000 = vertices[i].x;
                *(volatile s16 *)0xCC008000 = vertices[i].y;
                *(volatile u32 *)0xCC008000 = (u8)alpha | 0x405A2600;
            }
            layer->endSurface();
            if (layer->shaderIndex != 1) {
                layer->shaderIndex = 1;
                layer->shader = &layer->shaders[layer->shaderIndex];
            }
            layer->blendMode=1;layer->blendSource=4;layer->blendDestination=5;layer->blendLogic=5;
            layer->pixelDirty|=1;layer->dirty|=0x40;layer->savedPixelDirty|=1;layer->savedDirty|=0x40;
        }
    }
}

extern "C" s32 menuPdaBackDrawTitleText(tagWINDOW_WORK *window,tagSPRITE_WORK *sprite)
{
    bool add = _checkAddFunc(window);
    u32 value;
    s32 i;
    s32 x;
    switch (sprite->id) {
    case 7: { s32 value = pokecoloGetPlayTimeValue(); msgctrlSetValue(0x4C,(void *)value);break; }
    case 14:case 15:break;
    case 9:msgctrlSetValue(0x69,_menuPdaGetPokecoupon());break;
    case 11:msgctrlSetValue(0x69,_menuPdaGetMoney());break;
    case 13: {
        value=(u16)(u32)heroGetStatus(0,2,0);
        i=0;
        x=sprite->width-18;
        do {
            s32 digit=value%10U;
            value/=10U;
            msgctrlSetValue(0x34,(void *)digit);
            GSmsgPrint2(window->layer,x,0,WIN_ALPHA(window)|0xFFFFFF00,0x426F);
            u32 width=GSmsgGetRect(0x426F)>>16;
            i++;
            x-=width;
        } while(i<5);
        break;
    }
    case 2:
        if(add && _addfunc==0) { s32 alpha=_menuPdaScriptGetAlpha(); sprite->color.channels.alpha=alpha; }
        _SelectCursor(window,sprite,0);break;
    case 3:_SelectCursor(window,sprite,1);break;
    case 4:_SelectCursor(window,sprite,2);break;
    case 5:
        if(add && _addfunc==1) { s32 alpha=_menuPdaScriptGetAlpha(); sprite->color.channels.alpha=alpha; }
        _SelectCursor(window,sprite,3);break;
    case 6:_SelectCursor(window,sprite,4);break;
    case 1:
        _menuPdaDrawFace(window,sprite);_menuPdaGetCurrentID(window,sprite);
        _menuPdaModelCursorAnime();_SelectCursorPositionCheck();
        if(_menuPdaStatus.res>=0)_menuPdaStatus.unk8=_menuPdaStatus.res;
        break;
    case 0x173: {
        s32 messages[5]={0x3B53,0x3B54,0x3B55,0x3C03,0x3B56};
        sprite->message=messages[menuPdaGetRes()];break;
    }
    case 0x1C6: {
        u32 flag=GSflagGet(0x6C2);
        s32 messages[7]={0x3B72,0x3B73,0x3B74,0x3B75,0x3B76,0x3B77,0x3C2E};
        if(flag && flag<=8)sprite->message=messages[flag-1];
        else sprite->message=0;
        break;
    }
    case 0x1C8:winSpriteSetDisp(sprite,add);break;
    case 0x1C9:winSpriteSetDisp(sprite,_pdaSelectAnimeFlag);break;
    }
    return 0;
}
