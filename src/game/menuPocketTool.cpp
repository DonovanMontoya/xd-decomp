#pragma defer_codegen on
#pragma force_active on
#include <game/menuPocketToolLayout.hpp>

extern "C" {
u32 soundGetBGMID(void);
u32 soundGetEnvID(void);
s32 soundGetVolume(void);
void soundOpenPlayEnv(u32, s32, u8);
void GSthreadSwitch(void);
u16 windowGetKeyTrg(void);
void* memset(void *, int, u32);
void* memcpy(void *, const void *, u32);
void pokemonInit(Pokemon *);
f32 timeGetLastFrameSec(void);
DarkPokemon* darkPokemonGetDarkPokemon(u32);
s32 gamedataGetStatus(s32, s32);
void pokemonCreate(Pokemon *, u16, s32, s32);
u16 pokemonBiosGetInitDp(Pokemon *);
void pokemonSetDarkPokemonStatus(Pokemon *, u16);
extern u32 darkPokemonList_number;
s32 GSmsgIsCheck(u32);
void GSmsgExec(u32, s32, s32);
void GSmsgKill(u32);
tagWINDOW_WORK* windowSearchID(s32);
void winMsgDraw(void);
void GSgfxLayerSetActive(s32);
s32 floorGetMenuLayerID(void);
void spriteSetOffset(s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void spriteClearEnv(s32);
u32 timeGetLastFrameTime(void);
s8 fadeCheck(s32);
void fadeSetToBlackOutIfNotBlack(f32);
void fadeSetToBlackInIfBlack(f32);
void fadeSet(s32, f32);
void GSprimSetQuadVertexOrder(s32);
void GSprimDraw2DQuad4V(const f32 (*)[2], GSgfxColAu8);
u8 GSgfxVideoGetVsyncRate(void);
s32 windowGetActiveID(void);
u16 windowGetKeyOn(void);
void windowCloseMain(tagWINDOW_WORK *);
void menuSetDisp(s32, s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
s32 menuSubOpenSelect(s32, u32 *, s32, long, long, long);
void* menuDataBiosGetPtr(s32);
void soundOpenPlay(u32, s32, u8);
void GSsndPlayNow(u32);
void winSpriteDraw(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSgfxBlendMode(s32, s32, s32);
MENU_SPRITE_dd_* menuSpriteBiosGetPtr(u32);
MenuSpriteValue* menuSpriteBiosGetValPtr(MENU_SPRITE_dd_ *);
MENU_ITEM_dd_* menuItemBiosGetPtr(s32, u32);
void winSpriteSetDisp(tagSPRITE_WORK *, bool);
void windowDrawSprite2(s16, s16, s16, s16, u32, s32, u16, s32, s32);
void windowDrawSprite(s16, s16, s32, u16, s32, s32);
double atan2(double, double);
}


extern const GSgfxColAu8 GSgfxColAu8_Black = {0, 0, 0, 255};
template<> PocketVec<short> PocketVec<short>::zero = {0, 0};
unsigned short menuRelivehallPcBoxDefaultPokemonSprite = 0x2DF;
long CMetaMenu::defautlLocalWindowOpenTable[] = {0};
static u32 _darkPokemonIndex = 12;

void menuPtRestoreSound(MenuPtWorkSound *work);

void menuPtSaveSound(MenuPtWorkSound *work);

void menuPtStopSound(MenuPtWorkSound *work);

void menuPocketButtonWait(void);

void menuPocketDebugMakeDarkPokemonByID(Pokemon &pokemon, u16 id, f32 rate);
void menuPocketSetDarkPokemon(Pokemon &pokemon, f32 rate, u16 id);
void menuPocketDebugMakePokemonByID(Pokemon &pokemon, u16 id, bool dark, f32 rate);
static u16 pokemonindex(int index);

void menuPocketDebugMakeDarkPokemonByID(Pokemon &pokemon, u16 id, f32 rate);

void menuPocketDebugMakePokemonByID(Pokemon &pokemon, u16 id, bool dark, f32 rate);

void makePocketDeubugMakeDarkPokemonReset(void);

void menuPocketDebugMakePokemonBySN(Pokemon &pokemon, u16 sn, bool dark, f32 rate);

void menuPocketSetDarkPokemon(Pokemon &pokemon, f32 rate, u16 id);

static u16 pokemonindex(int index);

void CMenuGlobalState::init();

bool CMenuPokemonCursor::isCatchPokemon();

void CMenuPokemonCursor::deletePokemon();

void CMenuPokemonCursor::setBeforAnt(CAnt &src);

void CMenuPokemonCursor::setPokemon(Pokemon *src);

void CMenuPokemonCursor::setPositionTableDummy();

void CMenuPokemonCursor::setPositionIndex(long newIndex);

void CMenuPokemonCursor::setPositionTable(PocketVec<short> *newTable, long newIndex);

void CMenuPokemonCursor::setAnimationOff();

void CMenuPokemonCursor::init();

void CState::update();

void CState::addTime();

void CState::init();

void CInfoWindow::exec(CMetaMenu &menu, u32 message, bool close_);

void CInfoWindow::setMsgCtrlValue(u32 id, u32 value);

bool CInfoWindow::isMsgEnd();

void CInfoWindow::open(u32 message, bool waitFlag);

void CInfoWindow::close();

void CInfoWindow::initTutorialTalk();

void CInfoWindow::init(long menu, u32 value);

void CMetaMenu::waitAtTime(f32 seconds);

long CMetaMenu::calcAnimationTimeRate0toX(float time, long count);

f32 CMetaMenu::calcAnimationTimeRate0to1to0(f32 rate);

f32 CMetaMenu::calcAnimationTimeRate0to1(f32 rate);

void CMetaMenu::drawHook();

bool CMetaMenu::isAnimationStateNone();

void CMetaMenu::updateAll();

void CMetaMenu::vsyncUpdate();

void CMetaMenu::systemFadeWaitToEnd();

void CMetaMenu::systemFadeOutSetAndWait(f32 seconds);

void CMetaMenu::systemFadeOutKick(f32 seconds);

void CMetaMenu::systemFadeInKick();

void CMetaMenu::systemFadeOutKeepAfterFloorPush();

void CMetaMenu::tutorialExitKick();

CMetaMenu *CMetaMenu::pCurrentMenu;
static CMetaMenu *_pThis;
static s32 _selectItemQuantity;
PocketVec<short> CMenuPokemonCursor::defaultPositionTbl;

void CMetaMenu::alphaFadeDraw();

u8 CMetaMenu::getAlphaFadeAlpha() const;

void CMetaMenu::alphaFadeOutAndWait();

void CMetaMenu::alphaFadeUpdate();

void CMetaMenu::alphaFadeOutKick();

void CMetaMenu::alphaFadeInKick();

MetaKeyInfo* CMetaMenu::getKeyInfo();

void CMetaMenu::aButtonWait();

static void _tutorialWindowCursorFunc(tagWINDOW_WORK *win);

static void _tutorialWindowButtonFunc(tagWINDOW_WORK *win);

void CMetaMenu::localWindowRemove(long id);

void CMetaMenu::localWindowDrawAll(long first, long last);

void CMetaMenu::localWindowDrawAll();

void CMetaMenu::localWindowEntry(long id, long index, void (*func)(CMetaMenu *, long));

int CMetaMenu::localWindowSearch(long id);

void CMetaMenu::localWindowDeleteAll();

void CMetaMenu::localWindowCreateAll();

void CMetaMenu::localWindowSetTable(long *table);

extern "C" long menuPocketToolCMetaButton(tagWINDOW_WORK *);

extern "C" long menuPocketToolCMetaDraw(tagWINDOW_WORK *);

extern "C" long menuPocketToolCMetaCtrl(tagWINDOW_WORK *);

void menuPtPlayBgm(u32 id);

void menuPtPlaySe(u32 id);

void menuPtWindowWorkDraw(long id);

void menuPtWindowWorkDraw(tagWINDOW_WORK *win);

void menuPtWindowWorkDrawPrime(tagWINDOW_WORK *win);

void menuPtMenuLoad(long menu);

void menuPtSpriteDrawCenterColor(u16 id, long x, long y, u32 color);

void menuPtSpriteDrawColor(u16 id, long x, long y, long width, long height, u32 color);

void menuPtSpriteDrawColor(u16 id, long x, long y, u32 color);

void menuPtSpriteDraw(u16 id, long x, long y);

void menuPtItemDrawOffsetXWColor(MENU_ITEM_dd_ *item, long x, long width, u32 color);

void menuPtItemDrawOffset(MENU_ITEM_dd_ *item, long x, long y);

void menuPtItemDrawAlpha(MENU_ITEM_dd_ *item, u8 alpha);

void menuPtSpriteWorkSetWidthRateColor(tagWINDOW_WORK *win, u32 id, long n, f32 rate, GSgfxColAu8 color);

void menuPtSpriteWorkSetSw(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, bool on);

void menuPtSpriteWorkSetSw(tagWINDOW_WORK *win, u32 id, long n, bool on);

void menuPtSpriteWorkSetSpriteId(tagSPRITE_WORK *sprite, u32 id);

void menuPtSpriteWorkSetMenuSprite(tagSPRITE_WORK *sprite, MENU_SPRITE_dd_ *menuSprite);

void menuPtSpriteWorkSetMenuItem(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, u32 itemId);

tagSPRITE_WORK* menuPtGetSpriteWorkByHookFunction(tagWINDOW_WORK *win, void *func, u32 index, long n);

MENU_ITEM_dd_* menuPtItemGetBySpriteWork(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);

long menuPtSpriteWorkGetIndexFromId(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, u32 id);

tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(tagWINDOW_WORK *win, u32 id, long n);

tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(long menu, u32 id, long n);

void menuPtSpriteWorkSetMsgId(long menu, u32 id, long n, u32 msg);

MENU_ITEM_dd_* menuPtItemGetByMenuIdAndItemId(long menu, u32 itemId, long n);

u32 GSgfxColAu8To32(GSgfxColAu8 color);

bool isDirRegionIn(f32 a, f32 b, f32 c);
f32 dirSubOne(f32 a, f32 b);
f32 dirRefresh2PI(f32 dir);
f32 dirRefreshPI(f32 dir);
long degreeRefresh180(long degree);

bool isDirRegionIn(f32 a, f32 b, f32 c);

f32 xy2dir(f32 x, f32 y);

f32 xyxy2dir(const PocketVec<short> &a, const PocketVec<short> &b);

long xyxy2dirDegree(const PocketVec<short> &a, const PocketVec<short> &b);

f32 dirSubOne(f32 a, f32 b);

f32 dirSubHalf(f32 a, f32 b);

long degreeSubHalf(long a, long b);

long degreeRefresh180(long degree);

long degreeRefresh360(long degree);

f32 dirRefresh2PI(f32 dir);

f32 dirRefreshPI(f32 dir);

void menuPocketToolFloatToZero(f32 &value, f32 step);

void setBitTable(u32 *table, long bit, bool on);

bool getBitTable(u32 *table, long bit);

extern "C" {
void msgctrlSetValue(u32,u32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*,tagSPRITE_WORK*);
void GSmsgMain(s32,u32,u16,bool);
void GSmsgPrint2(s32,s32,s32,u32,u32);
}
void CInfoWindow::draw();

extern "C" f32 __float_nan[];
static inline f32 pocketDistanceSqrt(s32 sum) {
    if((f32)sum>0.0f) {
        f32 value=sum;
        f64 guess=__frsqrte((f64)value);
        guess=0.5*guess*(3.0-guess*guess*value);
        guess=0.5*guess*(3.0-guess*guess*value);
        guess=0.5*guess*(3.0-guess*guess*value);
        return (f32)(value*guess);
    } else if((f32)sum<0.0)return __float_nan[0];
    else {
        f32 value=sum;
        int classification;
        switch(*(int*)&value & 0x7F800000) {
        case 0x7F800000:if(*(int*)&value & 0x7FFFFF)classification=1;else classification=2;break;
        case 0:if(*(int*)&value & 0x7FFFFF)classification=5;else classification=3;break;
        default:classification=4;break;
        }
        if(classification==1)return __float_nan[0];
    }
    return (f32)sum;
}

f32 xyxy2distance(const PocketVec<short>& a,const PocketVec<short>& b);

extern "C" {f64 sin(f64);f64 fmod(f64,f64);}
static inline f32 cursorSin(f32 angle) { return (f32)sin((f64)angle); }
void CMenuPokemonCursor::draw();

extern "C" {
void* GSresGetResourceAllGroup(u32);
u16 GStextureGetXsize(void*);
u16 GStextureGetYsize(void*);
void GSprimDraw2DTexQuad4V(const PocketVec<f32>*,const PocketVec<f32>*,void*,const GSgfxColAu8*);
double sin(double);
double cos(double);
}
#pragma dollar_identifiers on
extern "C" {static PocketVec<f32> xy$2179[4],st$2180[4];}
void menuPtSpriteDrawAndRollScale(u16 id,u32 packedColor,f32 x,f32 y,f32 rotation,f32 scale);

struct PocketSelectData {
    u8 flags;
    union {u8 type;struct {u8 high:4,mode:3,low:1;} typeBits;};
    union {u8 button;struct {u8 mode:3,low:5;} buttonBits;};
    u8 byte3,byte4;
    s16 half6,half8,halfA;
    void (*cursor)(tagWINDOW_WORK*);
    void (*key)(tagWINDOW_WORK*);
    s32 word14,word18;
};
extern "C" long actionMenu__9CMetaMenuFPUlill(CMetaMenu* self,u32* entries,int quantity,long x,long y,long mode);

extern "C" {
void* Sequence_GetGSmodel(u32);
s32 Sequence_GetModelSize(u32);
void memoGetScaleAngle(u16,f32*,f32*);
void* GSmodelGetBound(void*);
void GSboundGetSize(void*,f32*,u8,u8);
}
extern "C" {static f32 multi$2677;static u8 init$2678;}
f32 menuGetPokemonScale(u32 sequence,int pokemon);


void CMetaMenu::tutorialExitKick() {
}

bool CMetaMenu::isAnimationStateNone() {
    return true;
}

bool getBitTable(u32 *table, long bit) {
    return (table[bit / 32] & (1 << (bit % 32))) != 0;
}

void setBitTable(u32 *table, long bit, bool on) {
    long index = bit / 32;
    long shift = bit % 32;
    if (on) {
        table[index] |= 1 << shift;
    }
}

void menuPocketToolFloatToZero(f32 &value, f32 step) {
    if (value > 0.0f) {
        if ((value -= step) < 0.0f) {
            value = 0.0f;
        }
    } else if (value < 0.0f) {
        if ((value += step) > 0.0f) {
            value = 0.0f;
        }
    }
}

f32 dirRefreshPI(f32 dir) {
    dir -= 6.2831855f * (long)(0.15915494f * dir);
    if (dir > 3.1415927f) {
        dir -= 6.2831855f;
    } else if (dir < -3.1415927f) {
        dir += 6.2831855f;
    }
    return dir;
}

f32 dirRefresh2PI(f32 dir) {
    dir -= 6.2831855f * (long)(0.15915494f * dir);
    if (dir < 0.0f) {
        dir += 6.2831855f;
    }
    return dir;
}

long degreeRefresh360(long degree) {
    degree = degree % 360;
    if (degree < 0) {
        degree += 360;
    }
    return degree;
}

long degreeRefresh180(long degree) {
    degree = degree % 360;
    if (degree >= 180) {
        degree -= 360;
    } else if (degree <= -180) {
        degree += 360;
    }
    return degree;
}

long degreeSubHalf(long a, long b) {
    return degreeRefresh180(a - b);
}

f32 dirSubHalf(f32 a, f32 b) {
    return dirRefreshPI(a - b);
}

f32 dirSubOne(f32 a, f32 b) {
    return dirRefresh2PI(a - b);
}

long xyxy2dirDegree(const PocketVec<short> &a, const PocketVec<short> &b) {
    f32 dir = atan2((f32)(a.x - b.x), (f32)-(a.y - b.y));
    return degreeRefresh180((long)(0.5f + 180.0f * dir / 3.1415927f));
}

f32 xyxy2dir(const PocketVec<short> &a, const PocketVec<short> &b) {
    return atan2((f32)(a.x - b.x), (f32)-(a.y - b.y));
}

f32 xy2dir(f32 x, f32 y) {
    return atan2(x, -y);
}

bool isDirRegionIn(f32 a, f32 b, f32 c) {
    f32 limit;
    if (c == b) {
        limit = 6.2831855f;
    } else {
        limit = dirSubOne(c, b);
    }
    return dirSubOne(a, b) <= limit;
}

f32 xyxy2distance(const PocketVec<short>& a,const PocketVec<short>& b) {
    return pocketDistanceSqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

u32 GSgfxColAu8To32(GSgfxColAu8 color) {
    u32 value;
    memcpy(&value, &color, 4);
    return value;
}

MENU_ITEM_dd_* menuPtItemGetByMenuIdAndItemId(long menu, u32 itemId, long n) {
    MENU_ITEM_dd_ *item = menuItemBiosGetPtr(menu, itemId);
    long i;
    for (i = 0; i < n; i++) {
        item = menuItemBiosGetPtr(menu, item->nextItem);
    }
    return item;
}

void menuPtSpriteWorkSetMsgId(long menu, u32 id, long n, u32 msg) {
    menuPtSpriteWorkGetByItemID(menu, id, n)->message = msg;
}

tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(long menu, u32 id, long n) {
    return menuPtSpriteWorkGetByItemID(windowSearchID(menu), id, n);
}

tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(tagWINDOW_WORK *win, u32 id, long n) {
    tagSPRITE_WORK *sprite = win->items;
    for (; sprite != 0; sprite = sprite->next) {
        if (sprite->id == id) {
            break;
        }
    }
    while (n > 0) {
        sprite = sprite->next;
        n--;
    }
    return sprite;
}

long menuPtSpriteWorkGetIndexFromId(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, u32 id) {
    tagSPRITE_WORK *s = menuPtSpriteWorkGetByItemID(win, id, 0);
    long i = 0;
    for (;;) {
        if (s == sprite) {
            break;
        }
        s = s->next;
        i++;
    }
    return i;
}

MENU_ITEM_dd_* menuPtItemGetBySpriteWork(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    return menuItemBiosGetPtr(win->menu, sprite->id);
}

tagSPRITE_WORK* menuPtGetSpriteWorkByHookFunction(tagWINDOW_WORK *win, void *func, u32 index, long n) {
    tagSPRITE_WORK *sprite = win->items;
    for (; sprite != 0; sprite = sprite->next) {
        if (sprite->callback == (u32)func) {
            if (index-- == 0) {
                break;
            }
        }
    }
    while (n != 0 && sprite != 0) {
        n--;
        sprite = sprite->next;
    }
    return sprite;
}

void menuPtSpriteWorkSetMenuItem(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, u32 itemId) {
    MENU_ITEM_dd_ *item = menuItemBiosGetPtr(win->menu, itemId);
    MenuSpriteValue *value = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(item->spriteID));
    sprite->resource = value->resource;
    sprite->sourceX = value->x;
    sprite->sourceY = value->y;
    sprite->sourceWidth = value->width;
    sprite->sourceHeight = value->height;
    sprite->x = item->x;
    sprite->y = item->y;
    sprite->width = item->width;
    sprite->height = item->height;
}

void menuPtSpriteWorkSetMenuSprite(tagSPRITE_WORK *sprite, MENU_SPRITE_dd_ *menuSprite) {
    MenuSpriteValue *value = menuSpriteBiosGetValPtr(menuSprite);
    sprite->resource = value->resource;
    sprite->sourceX = value->x;
    sprite->sourceY = value->y;
    sprite->sourceWidth = value->width;
    sprite->sourceHeight = value->height;
    sprite->width = value->width;
    sprite->height = value->height;
}

void menuPtSpriteWorkSetSpriteId(tagSPRITE_WORK *sprite, u32 id) {
    MENU_SPRITE_dd_ *menuSprite = menuSpriteBiosGetPtr(id);
    menuPtSpriteWorkSetMenuSprite(sprite, menuSprite);
}

void menuPtSpriteWorkSetSw(tagWINDOW_WORK *win, u32 id, long n, bool on) {
    winSpriteSetDisp(menuPtSpriteWorkGetByItemID(win, id, n), on);
}

void menuPtSpriteWorkSetSw(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, bool on) {
    winSpriteSetDisp(sprite, on);
}

void menuPtSpriteWorkSetWidthRateColor(tagWINDOW_WORK *win, u32 id, long n, f32 rate, GSgfxColAu8 color) {
    tagSPRITE_WORK *sprite = menuPtSpriteWorkGetByItemID(win, id, n);
    MENU_ITEM_dd_ *item = menuPtItemGetBySpriteWork(win, sprite);
    sprite->color.value = GSgfxColAu8To32(color);
    sprite->width = item->width * rate;
    winSpriteSetDisp(sprite, rate != 0.0f);
}

void menuPtItemDrawAlpha(MENU_ITEM_dd_ *item, u8 alpha) {
    u16 id = item->spriteID;
    windowDrawSprite2(item->x, item->y, item->width, item->height, alpha | 0xFFFFFF00, 0, id, 0, 7);
}

void menuPtItemDrawOffset(MENU_ITEM_dd_ *item, long x, long y) {
    windowDrawSprite2(item->x + x, item->y + y, item->width, item->height, 0xFFFFFFFF, 0, item->spriteID, 0, 7);
}

void menuPtItemDrawOffsetXWColor(MENU_ITEM_dd_ *item, long x, long width, u32 color) {
    windowDrawSprite2(item->x + x, item->y, width, item->height, color, 0, item->spriteID, 0, 7);
}

void menuPtSpriteDraw(u16 id, long x, long y) {
    windowDrawSprite(x, y, 0, id, 0, 7);
}

void menuPtSpriteDrawColor(u16 id, long x, long y, u32 color) {
    MenuSpriteValue *value = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    windowDrawSprite2(x, y, value->width, value->height, color, 0, id, 0, 7);
}

void menuPtSpriteDrawColor(u16 id, long x, long y, long width, long height, u32 color) {
    windowDrawSprite2(x, y, width, height, color, 0, id, 0, 7);
}

void menuPtSpriteDrawCenterColor(u16 id, long x, long y, u32 color) {
    MenuSpriteValue *value = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    x -= value->width / 2;
    y -= value->height / 2;
    windowDrawSprite2(x, y, value->width, value->height, color, 0, id, 0, 7);
}

void menuPtSpriteDrawAndRollScale(u16 id,u32 packedColor,f32 x,f32 y,f32 rotation,f32 scale) {
    MenuSpriteValue* data=menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(id));
    void* texture=GSresGetResourceAllGroup(data->resource);
    GSgfxColAu8 color={0,0,0,0};
    color.r=packedColor>>24;color.g=packedColor>>16;color.b=packedColor>>8;color.a=packedColor;
    f32 left=data->x,top=data->y,width=data->width,height=data->height;
    st$2180[0].x=st$2180[1].x=left/GStextureGetXsize(texture);
    st$2180[2].x=st$2180[3].x=(left+width)/GStextureGetXsize(texture);
    st$2180[1].y=st$2180[2].y=top/GStextureGetYsize(texture);
    st$2180[0].y=st$2180[3].y=(top+height)/GStextureGetYsize(texture);
    xy$2179[0].x=xy$2179[1].x=0;xy$2179[2].x=xy$2179[3].x=width;
    xy$2179[1].y=xy$2179[2].y=0;xy$2179[0].y=xy$2179[3].y=height;
    for(s32 i=0;i<4;i++) {xy$2179[i].y-=height/2.0f;xy$2179[i].x-=width/2.0f;}
    f32 angle=-rotation;
    for(s32 i=0;i<4;i++) {
        f32 oldX=xy$2179[i].x,oldY=xy$2179[i].y;
        f32 t=(f32)cos(angle);f32 v=(f32)sin(angle);
        xy$2179[i].x=oldY*v+oldX*t;
        t=(f32)sin(angle);v=(f32)cos(angle);
        xy$2179[i].y=oldY*v-oldX*t;
    }
    for(s32 i=0;i<4;i++){xy$2179[i].x*=scale;xy$2179[i].y*=scale;}
    for(s32 i=0;i<4;i++){xy$2179[i].x+=x;xy$2179[i].y+=y;}
    GSprimSetQuadVertexOrder(1);
    GSgfxColAu8 drawColor=color;
    GSprimDraw2DTexQuad4V(xy$2179,st$2180,texture,&drawColor);
}

void menuPtMenuLoad(long menu) {
    menuOpenCustom(menu, windowGetActiveID(), 0, 4, 0, 0);
}

void menuPtWindowWorkDrawPrime(tagWINDOW_WORK *win) {
    tagSPRITE_WORK *sprite = win->items;
    while (sprite != 0) {
        winSpriteDraw(win, sprite);
        sprite = sprite->next;
    }
    GSgfxBlendMode(1, 4, 5);
}

void menuPtWindowWorkDraw(tagWINDOW_WORK *win) {
    s32 layer;
    s32 menuLayer;
    if (win != 0) {
        menuLayer = floorGetMenuLayerID();
        layer = win->layer;
        spriteSetOffset(win->layer, win->x, win->y);
        spriteClearScissor(layer);
        spriteSetEnv(layer);
        spriteSetOffset(menuLayer, win->x, win->y);
        spriteClearScissor(menuLayer);
        spriteSetEnv(menuLayer);
        menuPtWindowWorkDrawPrime(win);
        spriteSetOffset(win->layer, 0, 0);
        spriteClearScissor(win->layer);
        spriteSetEnv(win->layer);
    }
}

void menuPtWindowWorkDraw(long id) {
    menuPtWindowWorkDraw(windowSearchID(id));
}

void menuPtPlaySe(u32 id) {
    GSsndPlayNow(id);
}

void menuPtPlayBgm(u32 id) {
    soundOpenPlay(id, 0x32, 0xFF);
}

void CState::init() {
    memset(this, 0, 0xA8);
    unk8 = -1;
    lastFrame = timeGetLastFrameSec();
}

void CState::addTime() {
    frames++;
    lastFrame = timeGetLastFrameSec();
    time = time + lastFrame;
}

void CState::update() {
    if (unk4 != -1) {
        unk8 = unk0;
        unk0 = unk4;
        unk4 = -1;
        time = 0.0f;
        frames = 0;
        unk98 = 0;
        unk9C = 0;
        unkA0 = 0;
        memcpy(saved2, saved, 0x40);
    } else {
        addTime();
    }
}

extern "C" long menuPocketToolCMetaCtrl(tagWINDOW_WORK *) {
    return 0;
}

extern "C" long menuPocketToolCMetaDraw(tagWINDOW_WORK *) {
    if (CMetaMenu::pCurrentMenu != 0) {
        CMetaMenu::pCurrentMenu->drawHook();
    }
    return 0;
}

extern "C" long menuPocketToolCMetaButton(tagWINDOW_WORK *) {
    return 0;
}

void CMetaMenu::localWindowSetTable(long *table) {
    windowTable = table;
}

void CMetaMenu::localWindowCreateAll() {
    int i;
    long id;
    menuOpenCustom(0xDA, windowGetActiveID(), 0, 0, 0, 0);
    i = 0;
    for (;;) {
        id = windowTable[i];
        if (id == 0) {
            break;
        }
        menuPtMenuLoad(id);
        menuSetDisp(id, 0);
        i++;
    }
    pCurrentMenu = this;
}

void CMetaMenu::localWindowDeleteAll() {
    int i;
    windowCloseMain(windowSearchID(0xDA));
    pCurrentMenu = 0;
    i = 0;
    for (;;) {
        if (windowTable[i] == 0) {
            break;
        }
        windowCloseMain(windowSearchID(windowTable[i]));
        i++;
    }
}

int CMetaMenu::localWindowSearch(long id) {
    int i;
    for (i = 0; i < 64; i++) {
        if (windows[i] == id) {
            return i;
        }
    }
    return -1;
}

void CMetaMenu::localWindowEntry(long id, long index, void (*func)(CMetaMenu *, long)) {
    windows[index] = id;
    windowFuncs[index] = func;
}

void CMetaMenu::localWindowDrawAll() {
    localWindowDrawAll(0, 63);
}

void CMetaMenu::localWindowDrawAll(long first, long last) {
    u32 i = first;
    for (; (long)i <= last; i++) {
        if (windows[i] != 0) {
            if (windowFuncs[i] != 0) {
                windowFuncs[i](this, windows[i]);
            } else {
                menuPtWindowWorkDraw(windows[i]);
            }
        }
    }
}

void CMetaMenu::localWindowRemove(long id) {
    int index = localWindowSearch(id);
    if (index != -1) {
        windows[index] = 0;
    }
}

static void _tutorialWindowButtonFunc(tagWINDOW_WORK *win) {
    u16 key;
    if (win != 0) {
        key = _pThis->tutorialManage();
        if (key & 0x10) {
            win->finished = 1;
        }
        if (key & 0x20) {
            win->finished = 1;
            win->cancelled = 1;
        }
    }
}

static void _tutorialWindowCursorFunc(tagWINDOW_WORK *win) {
    u16 key;
    if (win != 0) {
        menuDataBiosGetPtr(win->menu);
        key = _pThis->tutorialManage();
        if (key & 1) {
            win->value--;
            if (win->value < 0) {
                win->value = (s16)(_selectItemQuantity - 1);
            }
        } else if (key & 2) {
            win->value++;
            if (win->value >= _selectItemQuantity) {
                win->value = 0;
            }
        }
        win->selected = (s16)win->value;
    }
}

extern "C" long actionMenu__9CMetaMenuFPUlill(CMetaMenu* self,u32* entries,int quantity,long x,long y,long mode) {
    PocketSelectData *data = (PocketSelectData*)menuDataBiosGetPtr(0x59);
    PocketSelectData saved;
    if (self->tutorialActive) {
        _selectItemQuantity = quantity;
        _pThis = self;
        saved = *data;
        data->typeBits.mode = 4;
        data->cursor = _tutorialWindowCursorFunc;
        data->buttonBits.mode = 4;
        data->key = _tutorialWindowButtonFunc;
    }
    long result = menuSubOpenSelect(0, entries, quantity, x, y, mode);
    if (result == -1) result = quantity - 1;
    if (self->tutorialActive) *data = saved;
    return result;
}

void CMetaMenu::aButtonWait() {
    bool done = false;
    while (!done) {
        switch (getKeyInfo()->trigger) {
        case 0x10:
            done = true;
            menuPtPlaySe(seId);
            break;
        }
        updateAll();
    }
}

MetaKeyInfo* CMetaMenu::getKeyInfo() {
    u16 repeat;
    u16 trigger;
    u16 on;
    bool counting;
    u16 tutorialKey;
    if (tutorialActive) {
        memset(&keyInfo, 0, 0x1A);
        tutorialKey = tutorialManage();
        keyInfo.trigger = tutorialKey;
        keyInfo.repeat = tutorialKey;
        return &keyInfo;
    }
    memset(&keyInfo, 0, 0x1A);
    if (windowGetActiveID() != 0xDA) {
        return &keyInfo;
    }
    repeat = 0;
    trigger = windowGetKeyTrg();
    on = windowGetKeyOn();
    counting = false;
    if (trigger != 0) {
        repeat = trigger;
    } else if (on != 0 && on == lastKey) {
        if (repeatCount >= 12) {
            repeat = on;
        } else {
            counting = true;
        }
    }
    if (counting) {
        repeatCount++;
    } else {
        repeatCount = 0;
    }
    lastKey = on;
    keyInfo.repeat = repeat;
    keyInfo.trigger = trigger;
    return &keyInfo;
}

void CMetaMenu::alphaFadeInKick() {
    fadeTime = (u32)(0.5f * GSgfxVideoGetVsyncRate());
    fadeState = 3;
}

void CMetaMenu::alphaFadeOutKick() {
    fadeTime = (u32)(0.5f * GSgfxVideoGetVsyncRate());
    fadeState = 1;
}

void CMetaMenu::alphaFadeUpdate() {
    if (fadeTime != 0) {
        fadeTime -= timeGetLastFrameTime();
        if (fadeTime <= 0) {
            if (fadeState == 3) {
                fadeState = 0;
            } else if (fadeState == 1) {
                fadeState = 2;
            }
        }
    }
}

void CMetaMenu::alphaFadeOutAndWait() {
    bool end;
    s32 state;
    alphaFadeOutKick();
    do {
        updateAll();
        state = fadeState;
        end = false;
        if (state == 0 || state == 2) {
            end = true;
        }
    } while (!end);
    updateAll();
}

u8 CMetaMenu::getAlphaFadeAlpha() const {
    s32 total;
    switch (fadeState) {
    case 0:
        return 0xFF;
    case 3:
        total = (u32)(0.5f * GSgfxVideoGetVsyncRate());
        return ((s32)((u32)(0.5f * GSgfxVideoGetVsyncRate()) - fadeTime) * 255) / total;
    case 1:
        return (fadeTime * 255) / (s32)(u32)(0.5f * GSgfxVideoGetVsyncRate());
    case 2:
        return 0;
    default:
        return 0;
    }
}

void CMetaMenu::alphaFadeDraw() {
    static f32 xy[4][2] = { { 0.0f, 0.0f }, { 640.0f, 0.0f }, { 640.0f, 480.0f }, { 0.0f, 480.0f } };
    GSgfxColAu8 color = { 0, 0, 0, 0xFF };
    GSprimSetQuadVertexOrder(1);
    color.a = 255 - getAlphaFadeAlpha();
    if (color.a != 0) {
        GSprimDraw2DQuad4V(xy, color);
    }
}

void CMetaMenu::systemFadeOutKeepAfterFloorPush() {
    GSthreadSwitch();
    fadeSet(3, 0.0f);
}

void CMetaMenu::systemFadeInKick() {
    fadeSetToBlackInIfBlack(0.5f);
}

void CMetaMenu::systemFadeOutKick(f32 seconds) {
    if (seconds == -1.0f) {
        seconds = 0.5f;
    }
    fadeSetToBlackOutIfNotBlack(seconds);
}

void CMetaMenu::systemFadeOutSetAndWait(f32 seconds) {
    systemFadeOutKick(seconds);
    systemFadeWaitToEnd();
}

void CMetaMenu::systemFadeWaitToEnd() {
    while (fadeCheck(0) != 0) {
        updateAll();
    }
}

void CMetaMenu::vsyncUpdate() {
    GSthreadSwitch();
}

void CMetaMenu::updateAll() {
    vsyncUpdate();
}

void CMetaMenu::drawHook() {
    s32 layer;
    GSgfxLayerSetActive(7);
    layer = floorGetMenuLayerID();
    spriteSetOffset(7, 0, 0);
    spriteClearScissor(7);
    spriteSetEnv(7);
    spriteSetOffset(layer, 0, 0);
    spriteClearScissor(layer);
    spriteSetEnv(layer);
    drawMain();
    time += timeGetLastFrameTime();
    alphaFadeUpdate();
    tutorialManageUpdate();
    spriteSetOffset(7, 0, 0);
    spriteClearScissor(7);
    spriteClearEnv(7);
    spriteSetOffset(layer, 0, 0);
    spriteClearScissor(layer);
    spriteClearEnv(layer);
    GSgfxLayerSetActive(2);
}

f32 CMetaMenu::calcAnimationTimeRate0to1(f32 rate) {
    u32 period = (u32)(rate * GSgfxVideoGetVsyncRate());
    u32 pos = (u32)(time % period);
    return (f32)pos / (f32)period;
}

f32 CMetaMenu::calcAnimationTimeRate0to1to0(f32 rate) {
    f32 r = calcAnimationTimeRate0to1(rate);
    if (r > 0.5f) {
        r = 1.0f - r;
    }
    r *= 2.0f;
    return r;
}

long CMetaMenu::calcAnimationTimeRate0toX(float time, long count)
{
    float rate = calcAnimationTimeRate0to1(time);
    rate = count < ((count + 1) * rate) ? count : ((count + 1) * rate);
    return (long)rate;
}

void CMetaMenu::waitAtTime(f32 seconds) {
    f32 elapsed = 0.0f;
    for (;;) {
        updateAll();
        if (elapsed > seconds) {
            break;
        }
        elapsed += timeGetLastFrameSec();
    }
}

void CInfoWindow::init(long menu, u32 value) {
    unk4 = 0;
    key = 0;
    open_ = 0;
    wait = 0;
    msg = 0;
    memset(keys, 0, 0x20);
    unk0 = menu;
    unk4 = value;
    close();
}

void CInfoWindow::initTutorialTalk() {
    tagSPRITE_WORK *sprite;
    unk4 = 0;
    key = 0;
    open_ = 0;
    wait = 0;
    msg = 0;
    memset(keys, 0, 0x20);
    unk0 = 0xE3;
    sprite = menuPtGetSpriteWorkByHookFunction(windowSearchID(unk0), (void *)winMsgDraw, 0, 0);
    sprite->callback = 0;
    sprite->flags = 0;
    unk4 = sprite->id;
    close();
}

void CInfoWindow::close() {
    if (wait) {
        GSmsgKill(msg);
    }
    open_ = 0;
    wait = 0;
    msg = 0;
    memset(keys, 0, 0x20);
}

void CInfoWindow::open(u32 message, bool waitFlag) {
    wait = waitFlag;
    if (message != 0) {
        msg = message;
        if (wait) {
            GSmsgExec(msg, 0, 0);
        }
    }
    open_ = 1;
}

bool CInfoWindow::isMsgEnd() {
    return !GSmsgIsCheck(msg);
}

void CInfoWindow::setMsgCtrlValue(u32 id, u32 value) {
    int i = 0;
    while (keys[i][0] != 0) {
        i++;
    }
    keys[i][0] = id;
    keys[i][1] = value;
}

void CInfoWindow::draw()
{
    if (open_) {
        menuPtWindowWorkDraw(unk0);
        CInfoWindow* p = this;
        while (p->keys[0][0] != 0) {
            msgctrlSetValue(p->keys[0][0], p->keys[0][1]);
            p = (CInfoWindow*)((u8*)p + 8);
        }
        tagWINDOW_WORK* win = (tagWINDOW_WORK*)windowSearchID(unk0);
        tagSPRITE_WORK* spr = menuPtSpriteWorkGetByItemID(win, unk4, 0);
        int layer = winSpriteGetLayerID(win, spr);
        if (wait) {
            spriteSetOffset(layer, win->x + spr->x, win->y + spr->y);
            spriteClearScissor(layer);
            spriteSetEnv(layer);
            GSmsgMain((s32)layer, msg, key, ((s8)win->flags & 4) == 0);
            spriteSetOffset(layer, 0, 0);
            spriteClearScissor(layer);
            spriteSetEnv(layer);
        } else {
            GSmsgPrint2(layer, win->x + spr->x, win->y + spr->y, -1, msg);
        }
    }
}

void CInfoWindow::exec(CMetaMenu &menu, u32 message, bool close_) {
    open(message, true);
    do {
        key = windowGetKeyTrg();
        menu.updateAll();
    } while (!isMsgEnd());
    if (close_) {
        close();
    }
}

void CMenuPokemonCursor::init() {
    memset(this, 0, 0x150);
    unk0 = 1;
    pokemonInit(&pokemon);
    ant.init();
    beforeAnt.init();
    unk14C = 0;
    defaultPositionTbl.x = 0;
    defaultPositionTbl.y = 0;
    x = 0;
    y = 0;
    table = &defaultPositionTbl;
}

void CMenuPokemonCursor::setAnimationOff() {
    unk4 = 0;
    unk8 = 0.0f;
    beforeAnt.init();
}

void CMenuPokemonCursor::setPositionTable(PocketVec<short> *newTable, long newIndex) {
    setPositionIndex(newIndex);
    prevIndex = 0;
    table = newTable;
}

void CMenuPokemonCursor::setPositionIndex(long newIndex) {
    PocketVec<short> v = table[index];
    x = v.x;
    y = v.y;
    prevIndex = index;
    index = newIndex;
}

void CMenuPokemonCursor::setPositionTableDummy() {
    PocketVec<short> v = table[index];
    defaultPositionTbl.x = v.x;
    defaultPositionTbl.y = v.y;
    table = &defaultPositionTbl;
    index = 0;
    prevIndex = 0;
}

void CMenuPokemonCursor::setPokemon(Pokemon *src) {
    beforeAnt = ant;
    if (src == 0) {
        pokemonInit(&pokemon);
        ant.init();
    } else {
        memcpy(&pokemon, src, 0xC4);
        ant.initByPokemonAndSetColorAnimationInAny(&pokemon);
        ant.setAnimation(0);
    }
}

void CMenuPokemonCursor::setBeforAnt(CAnt &src) {
    beforeAnt = src;
}

void CMenuPokemonCursor::deletePokemon() {
    pokemonInit(&pokemon);
    beforeAnt = ant;
    ant.init();
}

bool CMenuPokemonCursor::isCatchPokemon() {
    return pokemon.checkValid();
}

void CMenuPokemonCursor::draw()
{
    if (!unk0) return;
    PocketVec<short> position;
    if (unk4 == 3) {
        const PocketVec<short> &target = table[index];
        position.x = x + unk8 * (target.x - x);
        position.y = y + unk8 * (target.y - y);
    } else position = table[index];
    if (isCatchPokemon()) {
        position.x += 8;
        position.y -= 8;
        if (unk4 == 1) {
            float wave = cursorSin(3.1415927f * unk8);
            short side = 20.0f * wave;
            short lift = -8.0f * unk8;
            PocketVec<short> previous = position, current = position;
            previous.x += side;
            current.x -= side;
            previous.y -= lift;
            current.y -= -8 - lift;
            if (unk8 < 0.5f) {
                ant.drawAndUpdate(current);
                beforeAnt.drawAndUpdate(previous);
            } else {
                beforeAnt.drawAndUpdate(previous);
                ant.drawAndUpdate(current);
            }
        } else {
            ant.drawAndUpdate(position);
        }
    } else if (unk4 == 2) {
        beforeAnt.unkC = 1.0f - unk8;
        beforeAnt.drawAndUpdate();
    }
    float pulse = pulseTime / 0.5f;
    if (pulse > 0.5f) pulse = 1.0f - pulse;
    pulse = 2.0f * pulse;
    pulseTime += timeGetLastFrameSec();
    if (pulseTime >= 0.5f) pulseTime = fmod(pulseTime, 0.5);
    position.x -= 45;
    position.y -= 45;
    unsigned long color = unk14C ? 0xffc800ff : 0xffffffff;
    if (!isCatchPokemon()) {
        MenuSpriteValue *sprite = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x216));
        long width = sprite->width, height = sprite->height;
        long offset = (short)(5.0f * pulse);
        long top, left;
        if (offset > 4) offset = 4;
        left = position.x + offset;
        top = position.y + offset;
        menuPtSpriteDrawColor(0x216, (short)(left + 4), (short)(top + 4), width, height, color);
        menuPtSpriteDrawColor(0x216, (short)(position.x + 50 - offset), (short)(top + 4), -width, height, color);
        menuPtSpriteDrawColor(0x216, (short)(left + 4), (short)(position.y + 50 - offset), width, -height, color);
        menuPtSpriteDrawColor(0x216, (short)(position.x + 50 - offset), (short)(position.y + 50 - offset), -width, -height, color);
    } else {
        short alpha = 155.0f * pulse + 100.0f;
        menuPtSpriteDrawColor(0x215, (short)(position.x + 14), (short)(position.y + 14), (color & 0xffffff00) | alpha);
    }
    menuPtSpriteDrawColor(0x214, (short)(position.x + 7), (short)(position.y + 35), color);
}

void CMenuGlobalState::init() {
    memset(this, 0, 0x208);
    cursor.init();
    state.init();
}

static u16 pokemonindex(int index) {
    index++;
    if (index > 0xFB) {
        index += 0x19;
    }
    return index;
}

void menuPocketSetDarkPokemon(Pokemon &pokemon, f32 rate, u16 id) {
    DarkPokemon *dark;
    u16 dp;
    pokemonSetDarkPokemonStatus(&pokemon, id);
    dp = pokemonBiosGetInitDp(&pokemon);
    pokemon.setDarkPoint(dp * rate);
    dark = darkPokemonGetDarkPokemon(id);
    dark->setStatus(darkStatus3);
    dark->setSnatchIndex(id);
}

void menuPocketDebugMakePokemonBySN(Pokemon &pokemon, u16 sn, bool dark, f32 rate) {
    menuPocketDebugMakePokemonByID(pokemon, pokemonindex(sn % 386), dark, rate);
}

void makePocketDeubugMakeDarkPokemonReset(void) {
    _darkPokemonIndex = 12;
}

void menuPocketDebugMakePokemonByID(Pokemon &pokemon, u16 id, bool dark, f32 rate) {
    int i;
    pokemonCreate(&pokemon, id, 0x19, gamedataGetStatus(0, 1));
    if (dark) {
        for (i = 0; i < 10; i++) {
            _darkPokemonIndex++;
            if (_darkPokemonIndex >= darkPokemonList_number) {
                _darkPokemonIndex = 1;
            }
            menuPocketSetDarkPokemon(pokemon, rate, _darkPokemonIndex);
            if (pokemonBiosGetInitDp(&pokemon) != 0) {
                break;
            }
        }
    }
}

void menuPocketDebugMakeDarkPokemonByID(Pokemon &pokemon, u16 id, f32 rate) {
    u16 pokemonId = darkPokemonGetDarkPokemon(id)->getPokemonID();
    pokemonCreate(&pokemon, pokemonId, 0x19, gamedataGetStatus(0, 1));
    menuPocketSetDarkPokemon(pokemon, rate, id);
    pokemonBiosGetInitDp(&pokemon);
}

f32 menuGetPokemonScale(u32 sequence,int pokemon) {
    f32 size[3],scale,angle;
    void* model=Sequence_GetGSmodel(sequence);
    f32 factor;
    switch(Sequence_GetModelSize(sequence)) {
    case -2:factor=0.6f;break;
    case -1:factor=0.75f;break;
    case 0:factor=1.0f;break;
    case 1:factor=1.15f;break;
    case 2:factor=1.25f;break;
    case 3:factor=1.4f;break;
    default:factor=1.0f;break;
    }
    memoGetScaleAngle(pokemon,&scale,&angle);
    GSboundGetSize(GSmodelGetBound(model),size,0,0);
    f32 largest=size[0]>size[1]?size[0]:size[1];
    f32 result=11.0f/(scale*(largest/factor));
    if((s8)init$2678==0) {init$2678=1;multi$2677=2.0f;}
    return result*multi$2677;
}

void menuPocketButtonWait(void) {
    do {
        GSthreadSwitch();
    } while ((windowGetKeyTrg() & 0x30) == 0);
}

void menuPtStopSound(MenuPtWorkSound *work) {
    u32 bgm;
    u8 bgmVolume;
    u32 env;
    u8 envVolume;
    bgm = soundGetBGMID();
    if (bgm != 0) {
        bgmVolume = soundGetVolume();
        soundOpenPlay(8, 0x32, 0xFF);
    } else {
        bgmVolume = 0;
    }
    env = soundGetEnvID();
    if (env != 0) {
        envVolume = soundGetVolume();
    } else {
        envVolume = 0;
    }
    work->bgm = bgm;
    work->env = env;
    work->bgmVolume = bgmVolume;
    work->envVolume = envVolume;
}

void menuPtSaveSound(MenuPtWorkSound *work) {
    u32 bgm;
    u8 bgmVolume;
    u32 env;
    u8 envVolume;
    bgm = soundGetBGMID();
    if (bgm != 0) {
        bgmVolume = soundGetVolume();
    } else {
        bgmVolume = 0;
    }
    env = soundGetEnvID();
    if (env != 0) {
        envVolume = soundGetVolume();
    } else {
        envVolume = 0;
    }
    work->bgm = bgm;
    work->env = env;
    work->bgmVolume = bgmVolume;
    work->envVolume = envVolume;
}

void menuPtRestoreSound(MenuPtWorkSound *work) {
    if (work->bgm != 0 && work->bgm != soundGetBGMID()) {
        soundOpenPlay(work->bgm, 0x32, work->bgmVolume);
    }
    if (work->env != 0 && work->env != soundGetEnvID()) {
        soundOpenPlayEnv(work->env, 0x32, work->envVolume);
    }
}
