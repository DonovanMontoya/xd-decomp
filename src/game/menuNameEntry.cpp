#include <game/menuNameEntryLayout.hpp>
#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>

struct Pokemon;
struct MENU_MODEL {
    u8 data[0xEC];
    MENU_MODEL() {}
};

extern "C" {
void GScharCpy(u16 *, u16 *);
u16 *GSmsgGetGSchar(s32);
void GSsndPlayNow(u32);
void msgctrlSetValue(s32, u16 *);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
u16 windowGetKeyTrg(void);
u16 windowGetKeyRepeat(void);
void winSeqSetMenu(s32, s32);
void GSfloorPush(s32);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
Pokemon *heroGetStatus(s32, s32, u16);
Pokemon *fightFloorGetDefPokemonPtr(s32);
u8 pokemonCheckValid(Pokemon *);
u8 pokemonGetSex(Pokemon *);
u16 pokemonBiosGetPokemonDataId(Pokemon *);
u8 menuIsCheck(s32);
void menuSetDisp(s32, s32);
void menuNameEntry(void);
s32 GSmsgGetLength(u32);
u32 GSmsgGetRect(s32);
void GSmsgPrint2(s32, s32, s32, u32, s32);
f32 HSD_Randf(void);
double sin(double);
void menuSpriteBiosGetPtr(s32);
struct MenuSpriteVal {
    u8 reserved0[4];
    s16 unk4;
    s16 unk6;
};
MenuSpriteVal *menuSpriteBiosGetValPtr(void);
void windowDrawSprite2(s32, s32, s32, s32, u32, tagWINDOW_WORK *, s32, s32, s32);
void heroSetStatus(s32, s32, u16 *);
u16 *pokemonBiosGetNicknamePtr(Pokemon *);
void pokemonBiosSetNicknamePtr(Pokemon *, u16 *);
u16 *pcboxGetPokemonBoxName(s32, s8);
void pcboxSetPokemonBoxName(s32, s8, u16 *);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
void menuClose(s32);
void menuCloseSync(s32, s32);
void FlashSystemSetPlayFrameLabel(u32, const char *, const char *);
void FlashSystemSetLoopFlag(u32, s32);
void FlashSystemSetNowFrameLabel(u32, const char *);
void fadeSet(s32, f32);
void fadeCheck(s32);
void menuModelTerm(MENU_MODEL *);
void menuModelAdjustCamera(MENU_MODEL *);
void menuModelSetSize(MENU_MODEL *, s16, s16, s16, s16);
void menuModelSetClip(MENU_MODEL *, u8);
void menuModelSetAngle(MENU_MODEL *, Vec *);
void menuModelSetOffset(MENU_MODEL *, Vec *);
void menuModelSetZoom(MENU_MODEL *, f32);
GStexture *menuModelRender(MENU_MODEL *);

GSgfxVF *GSgfxVFBuildTemp(u32,u32,u32,u32,u32,u32,u32,u32,u32);
s32 GScharCmp(u16 *, u16 *);
void menuTitleBattleSelectFree(void);
void dbgMenuSetEnable(u8);
void GSfloorPop(void);
struct MenuItemInfo {
    u8 reserved0[0xA];
    s16 a;
    s16 b;
};
MenuItemInfo *menuItemBiosGetPtr(s32, s32);
void menuModelInit(MENU_MODEL *, s16, s16);
void menuModelLoad(MENU_MODEL *, s32);
void *peopleInfoBiosGetPtr(s32);
void peopleInfoBiosGetMotion(void *, s32, s32 *, s32 *);
void menuModelSetMotion(MENU_MODEL *, s32);
void menuModelLoadPokemon(MENU_MODEL *, Pokemon *);
void menuModelCheck(MENU_MODEL *, s32);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void menuSubDrawCursorBackAnimeOnOffAuto(tagWINDOW_WORK *, s32, s32, s32, s16, s16, u8, s32);
void windowDrawSprite(s16, s16, tagWINDOW_WORK *, s32, s32, s32);
}

enum SHEET { SHEET_A, SHEET_B };
enum DAKUON_MODE { DAKUON_NONE, DAKUON_VOICED, DAKUON_HALF };
enum GSgfxLayerID { GSGFX_LAYER_DUMMY };

struct SheetDataT {
    u8 flags[4];
    u32 title;
    u32 rows[8];
    u32 pad;
};

static const SheetDataT SheetData[2] = {
    { { 0x0B, 0x57, 0x02, 0x00 }, 0x3B14, { 0x3AFD, 0x3AFE, 0x3AFF, 0x3B00, 0x3BF4, 0x3BF5, 0, 0 }, 0 },
    { { 0x02, 0x3C, 0x57, 0x00 }, 0x3B15, { 0x3B01, 0x3B02, 0x3B03, 0x3B04, 0x3BF6, 0x3BF7, 0, 0 }, 0 },
};

struct BALL_WORK {
    s32 active;
    f32 x;
    f32 y;
    f32 scale;
    f32 maxScale;
    s32 color;
    u8 alpha;
    u8 reserved19[3];
    f32 t;
    f32 life;
};

static BALL_WORK BallWork[30];
struct ModeDataT {
    u32 msg;
    s32 maxLen;
    const u32 *defNames;
    s32 defCount;
};

static const u32 DefKenName[3] = { 0x3B20, 0x3B21, 0x3B22 };
static const u32 DefHizukiName[3] = { 0x3B20, 0x3B21, 0x3B22 };

static const ModeDataT ModeData[7] = {
    { 0x3B11, 7, DefKenName, 3 },
    { 0x3B11, 7, DefHizukiName, 3 },
    { 0x3B12, 10, 0, 0 },
    { 0x3B13, 8, 0, 0 },
    { 0x3B12, 10, 0, 0 },
    { 0x3B12, 10, 0, 0 },
    { 0x3C33, 10, 0, 0 },
};
extern const u32 DakuHanTbl[2] = { 0, 0x3B1B };
static s32 Sheet;
static s32 SheetCurX;
static s32 SheetCurY;
static f32 SheetCurAnimTime;
static s32 NameCurX;
static s32 DefSheetCurPosX;
static s32 DefSheetCurPosY;
static s32 DefNamePokemonCurPosX;
static s32 DefNameBoxCurPosX;
static s32 DefNameTrainerCurPosX;
static NAME_ENTRY_WORK NameEntryWork;
static MENU_MODEL MenuModel;

static void ballMain1(BALL_WORK *ball);
static void generateBall(void);
static void ballMain(void);

static s32 getGScharLen(u16 *str);
static u16 getCharSheet(SHEET sheet, int index, int row);
static void putGScharL(GSgfxLayerID layer, int x, int y, u32 color, u16 ch);
static void drawControlCursor(NAME_ENTRY_ARG *arg, tagSPRITE_WORK *sprite);
static void setDefNameText(tagSPRITE_WORK *sprite, u32 id);
static s32 menuNameEntryDrawNameText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, int a, int b);
static s32 pushNameEntryFloor(int a, int b, int c);
static s32 menuNameEntryDrawNameCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, int a, int b);
static s32 chkParam(int mode, int index);
static s32 getName(u16 *dst, int mode, int arg);
static s32 setName(u16 *name, int mode, int arg);
static s32 selectName(u16 *dst, const u32 *list, int count);
static s32 selectLetter(NAME_ENTRY_ARG *arg);
static s32 inputName(u16 *dst, u16 *backup, int mode, int idx, int flag);
static void loadModel(long layer, MENU_MODEL *model, int mode, int idx);
static u16 exchangeDakuon(u16 ch, DAKUON_MODE mode);

static void drawTexture(GStexture *texture, tagSPRITE_WORK *sprite, GSgfxLayerID id)
{
    GSgfxLayer *layer = GSgfxLayerFindByID(id);
    if (layer) {
        layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0,3,0,0,1,5,1,1,4));
        if (layer->texture != texture || layer->savedTexture != texture || texture->dirty) {
            layer->texture = texture;
            layer->textureDirty |= 1;
            layer->savedTexture = texture;
            layer->savedTextureDirty |= 1;
        }
        layer->primitive = 0x98;
        layer->beginSurface(4);
        f32 zero = 0.0f;
        f32 one = 1.0f;
        *(volatile s16 *)0xCC008000 = 0;
        *(volatile s16 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile s16 *)0xCC008000 = sprite->unk54;
        *(volatile s16 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = one;
        *(volatile f32 *)0xCC008000 = zero;
        s16 height = sprite->unk56;
        *(volatile s16 *)0xCC008000 = 0;
        *(volatile s16 *)0xCC008000 = height;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = one;
        height = sprite->unk56;
        s16 width = sprite->unk54;
        *(volatile s16 *)0xCC008000 = width;
        *(volatile s16 *)0xCC008000 = height;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = one;
        *(volatile f32 *)0xCC008000 = one;
        layer->endSurface();
    }
}

extern "C" {
s32 menuNameEntryBackDrawPokemonModel(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 mode = *(s32 *)window->unk68;
    if (mode == 2 || mode == 4 || mode == 5) {
        Vec angle;
        Vec offset;
        s16 position[2] = {0,120};
        s16 size[2] = {300,300};
        f32 zoom = 1.2f;
        angle.x = 0.0f; angle.y = 0.3f; angle.z = 0.0f;
        offset.x = 0.0f; offset.y = 0.0f; offset.z = 0.0f;
        switch (*(u16 *)(MenuModel.data + 0x24)) {
        case 40: case 62: case 71: case 87: case 95: case 96: case 108:
        case 163: case 174: case 192: case 230: case 340: case 398:
            zoom = 1.0f; break;
        case 26: case 123: case 151: case 323: zoom = 0.9f; break;
        case 233: zoom = 0.8f; break;
        case 208: zoom = 0.95f; break;
        }
        menuItemBiosGetPtr(window->unk4, sprite->unk6);
        menuModelAdjustCamera(&MenuModel);
        menuModelSetSize(&MenuModel,position[0],position[1],size[0],size[1]);
        menuModelSetClip(&MenuModel,0);
        menuModelSetAngle(&MenuModel,&angle);
        menuModelSetZoom(&MenuModel,zoom);
        menuModelSetOffset(&MenuModel,&offset);
        GStexture *texture = menuModelRender(&MenuModel);
        if (texture) drawTexture(texture,sprite,(GSgfxLayerID)winSpriteGetLayerID(window,sprite));
    }
    return 0;
}

s32 menuNameEntryBackDrawHumanModel(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 mode = *(s32 *)window->unk68;
    if (mode == 0 || mode == 1) {
        Vec angle;
        Vec offset;
        angle.x = 0.0f; angle.y = 0.3f; angle.z = 0.0f;
        offset.x = -4.0f; offset.y = 0.0f; offset.z = 0.0f;
        s16 position[2] = {0,80};
        s16 size[2] = {520,300};
        menuItemBiosGetPtr(window->unk4, sprite->unk6);
        menuModelAdjustCamera(&MenuModel);
        menuModelSetSize(&MenuModel,position[0],position[1],size[0],size[1]);
        menuModelSetClip(&MenuModel,0);
        menuModelSetAngle(&MenuModel,&angle);
        menuModelSetZoom(&MenuModel,1.4f);
        menuModelSetOffset(&MenuModel,&offset);
        GStexture *texture = menuModelRender(&MenuModel);
        if (texture) drawTexture(texture,sprite,(GSgfxLayerID)winSpriteGetLayerID(window,sprite));
    }
    return 0;
}
}

extern "C" {
s32 menuNameEntryDrawTitle(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    if (window->unk4 == 0x65) {
        s32 width = GSmsgGetRect(0x3B11) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), (sprite->unk54 - width) / 2, 0,
                    window->unk93 | 0xFFFFFF00, 0x3B11);
    } else {
        NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
        Pokemon *pokemon;
        u16 id;
        switch (arg->unk1C) {
        case 2: {
            pokemon = heroGetStatus(0, 3, arg->unk20);
            if (pokemonCheckValid(pokemon)) id = pokemonBiosGetPokemonDataId(pokemon);
            else id = 1;
            msgctrlSetValue(0x4E, (u16 *)id);
            s32 width = GSmsgGetRect(ModeData[arg->unk1C].msg) >> 16;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), (sprite->unk54 - width) / 2, 0,
                        window->unk93 | 0xFFFFFF00, ModeData[arg->unk1C].msg);
            break;
        }
        case 5: {
            id = pokemonBiosGetPokemonDataId((Pokemon *)arg->unk20);
            msgctrlSetValue(0x4E, (u16 *)id);
            s32 width = GSmsgGetRect(ModeData[arg->unk1C].msg) >> 16;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), (sprite->unk54 - width) / 2, 0,
                        window->unk93 | 0xFFFFFF00, ModeData[arg->unk1C].msg);
            break;
        }
        case 4: {
            pokemon = fightFloorGetDefPokemonPtr(0);
            if (pokemonCheckValid(pokemon)) id = pokemonBiosGetPokemonDataId(pokemon);
            else id = 1;
            msgctrlSetValue(0x4E, (u16 *)id);
            s32 width = GSmsgGetRect(ModeData[arg->unk1C].msg) >> 16;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), (sprite->unk54 - width) / 2, 0,
                        window->unk93 | 0xFFFFFF00, ModeData[arg->unk1C].msg);
            break;
        }
        default: {
            s32 width = GSmsgGetRect(ModeData[arg->unk1C].msg) >> 16;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), (sprite->unk54 - width) / 2, 0,
                        window->unk93 | 0xFFFFFF00, ModeData[arg->unk1C].msg);
            break;
        }
        }
    }
    return 0;
}

s32 menuNameEntryDrawNamePokemonWaku(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    Pokemon *pokemon;
    s32 display;
    NAME_ENTRY_ARG *arg;
    s32 position;
    position = 0;
    arg = (NAME_ENTRY_ARG *)window->unk68;
    display = 0;
    switch (sprite->unk6) {
    case 0x675: case 0x676: case 0x677: case 0x678: case 0x679:
    case 0x8EA: case 0x8EB:
        if (arg->unk1C >= 7 || arg->unk1C < 2) display = 1;
        break;
    case 0x683: position = 1;
    case 0x682: position++;
    case 0x681: position++;
    case 0x680: position++;
    case 0x67F: position++;
    case 0x67E: position++;
    case 0x67D: position++;
    case 0x67C: position++;
    case 0x67B: position++;
    case 0x67A:
        switch (arg->unk1C) {
        case 2: case 4: case 5: case 6: display = 1; break;
        case 3: if (position != 0 && position != 9) display = 1; break;
        }
        break;
    case 0x876:
        pokemon = 0;
        switch (arg->unk1C) {
        case 2: pokemon = heroGetStatus(0, 3, arg->unk20); break;
        case 4: pokemon = fightFloorGetDefPokemonPtr(0); break;
        case 5: pokemon = (Pokemon *)arg->unk20; break;
        }
        if (pokemon) {
            if (pokemonGetSex(pokemon) == 0) display = 0x9C5;
            else if (pokemonGetSex(pokemon) == 1) display = 0x9C6;
            if (display) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(display));
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, *(u32 *)((u8 *)window + 0x90), 0x4275);
                display = 0;
            }
        }
        break;
    }
    winSpriteSetDisp(sprite, 0);
    if (display) winSpriteSetDisp(sprite, 1);
    return 0;
}

s32 menuNameEntryDrawBkCur(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s16 idx;
    winSpriteSetDisp(sprite, 0);
    idx = window->unk9E;
    if (idx >= 0) {
        menuSubDrawCursorBackAnimeOnOffAuto(window, winSpriteGetLayerID(window, sprite), 0, idx << 5, sprite->unk54,
                                            sprite->unk56, window->unk93, 1);
    }
    return 0;
}

s32 menuNameEntryDrawNameRuleText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    return menuNameEntryDrawNameText(window, sprite, 10, 6);
}

s32 menuNameEntryDrawNameTrainerText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    return menuNameEntryDrawNameText(window, sprite, 7, 0);
}

s32 menuNameEntryDrawNameBoxText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    return menuNameEntryDrawNameText(window, sprite, 8, 3);
}
}

static void drawControlCursor(NAME_ENTRY_ARG *arg, tagSPRITE_WORK *sprite)
{
    s32 x = *arg->unk28;
    s32 y = *arg->unk2C;
    winSpriteSetDisp(sprite, 0);
    if (y > 5 && x > 6) {
        s32 id;
        if (y == 6) {
            id = 0x305;
        } else {
            id = 0x304;
        }
        if (id == sprite->unk6) {
            winSpriteSetDisp(sprite, 1);
        }
    }
}

extern "C" {
s32 menuNameEntryDrawStartCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    drawControlCursor((NAME_ENTRY_ARG *)window->unk68, sprite);
    return 0;
}

s32 menuNameEntryDrawBCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    drawControlCursor((NAME_ENTRY_ARG *)window->unk68, sprite);
    return 0;
}

s32 menuNameEntryDraw50Cursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    winSpriteSetDisp(sprite, 0);
    if (*arg->unk2C < 6) {
        if (*arg->unk28 < 11) {
            windowDrawSprite(*arg->unk28 * 26, *arg->unk2C * 30, window, 0x153, 0, winSpriteGetLayerID(window, sprite));
        }
    } else if (*arg->unk28 < 7) {
        windowDrawSprite(*arg->unk28 * 26, *arg->unk2C * 30, window, 0x153, 0, winSpriteGetLayerID(window, sprite));
    }
    return 0;
}
}

static u16 getCharSheet(SHEET sheet, int index, int row)
{
    u32 id;
    s32 len;
    u16 *p;
    if (sheet < 0 || sheet >= 2) {
        return 0;
    }
    if (row < 0 || row >= 8) {
        return 0;
    }
    id = SheetData[sheet].rows[row];
    if (id == 0) {
        return 0;
    }
    len = GSmsgGetLength(id);
    if (index < 0 || index >= len) {
        return 0;
    }
    p = GSmsgGetGSchar(id);
    if (*p == 0xFFFF) {
        p += 2;
    }
    return p[index];
}

static s32 getGScharLen(u16 *str)
{
    s32 n = 0;
    while (*str != 0) {
        str++;
        n++;
    }
    return n;
}

static s32 confirmName(u16 *name)
{
    s32 answer;
    GSsndPlayNow(0x1D);
    msgctrlSetValue(0x4D, name);
    winMsgOpen(2, 0x3B1A, 1, 0);
    answer = menuSubOpenYesNo(0, 0x2C, 0xC0, 0);
    winMsgClose(1);
    if (answer == 1 || answer == -1) {
        return 0;
    }
    return 1;
}

static u8 backNameCursor(NAME_ENTRY_ARG *arg)
{
    s32 cur = *arg->unk34;
    if (cur <= 0) {
        return 0;
    }
    s32 prev;
    prev = cur - 1;
    arg->unk18[prev] = 0;
    *arg->unk34 = prev;
    return 1;
}

static s32 getSpchar(u16 c)
{
    u16 *p = GSmsgGetGSchar(0x3B1E);
    if (c == *p) {
        return 0;
    }
    return 6;
}

static void change50Sheet(NAME_ENTRY_ARG *arg)
{
    s32 *sheet = arg->unk24;
    s32 next = *sheet;
    next++;
    if (next >= 2) {
        next = 0;
    }
    *sheet = next;
}

extern "C" {
void menuNameEntryButton(void)
{
}
}

static s32 chkValidName(u16 *name)
{
    s32 len = getGScharLen(name);
    s32 count;
    s32 i;
    u16 *blank;
    if (len <= 0) {
        return 0;
    }
    blank = GSmsgGetGSchar(0x3B1D);
    count = 0;
    for (i = 0; i < len; i++) {
        if (*name != *blank) {
            break;
        }
        count++;
        name++;
    }
    if (count >= len) {
        return 0;
    }
    return 1;
}

static void setDefNameText(tagSPRITE_WORK *sprite, u32 id)
{
    msgctrlSetValue(0x37, GSmsgGetGSchar(id));
    sprite->unk4C = 0x4276;
}

extern "C" {
s32 menuNameEntrySelectDrawSelText3(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 **p = (s32 **)window->unk68;
    setDefNameText(sprite, (*p)[2]);
    return 0;
}

s32 menuNameEntrySelectDrawSelText2(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 **p = (s32 **)window->unk68;
    setDefNameText(sprite, (*p)[1]);
    return 0;
}

s32 menuNameEntrySelectDrawSelText1(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 **p = (s32 **)window->unk68;
    setDefNameText(sprite, (*p)[0]);
    return 0;
}

void menuNameEntrySelectButton(tagWINDOW_WORK *window)
{
    u16 key = windowGetKeyTrg();
    if ((key & 0x20) != 0) {
        window->unkA5 = 1;
        window->unkA4 = 1;
    }
    if ((key & 0x10) != 0) {
        window->unkA4 = 1;
    }
}

s32 menuNameEntrySelectCtrl(tagWINDOW_WORK *window)
{
    switch (window->unk1) {
    case 0:
        if (window->unk2 == 0) {
            winSeqSetMenu(window->unk4, 0x58);
            window->unk2 = 1;
        }
        break;
    case 3:
        if (window->unk2 == 0) {
            winSeqSetMenu(window->unk4, 0x5C);
            window->unk2 = 1;
        }
        break;
    }
    return 0;
}

void menuNameEntryGetLastName(u16 *dst)
{
    GScharCpy(dst, NameEntryWork.name);
}

s32 menuNameEntryOpenNoFade(int a, int b)
{
    return pushNameEntryFloor(a, b, 0);
}
}

static s32 chkParam(int mode, int index)
{
    s32 ok = 1;
    switch (mode) {
    case 0:
    case 1:
    case 5:
    case 6:
        break;
    case 2:
        if (pokemonCheckValid(heroGetStatus(0, 3, index)) == 0) {
            ok = 0;
        }
        break;
    case 3:
        if (index < 0 || index >= 8) {
            ok = 0;
        }
        break;
    case 4:
        if (pokemonCheckValid(fightFloorGetDefPokemonPtr(0)) == 0) {
            ok = 0;
        }
        break;
    default:
        ok = 0;
        break;
    }
    return ok;
}

extern "C" {
s32 menuNameEntryCall(int mode, int index)
{
    if (chkParam(mode, index) == 0) {
        return 0;
    }
    NameEntryWork.name[0] = 0;
    NameEntryWork.unk18 = mode;
    NameEntryWork.unk1C = index;
    NameEntryWork.unk20 = 0;
    NameEntryWork.unk28 = 0;
    menuNameEntry();
    return NameEntryWork.unk20;
}
}

static s32 pushNameEntryFloor(int mode, int index, int fade)
{
    if (chkParam(mode, index) == 0) {
        return 0;
    }
    NameEntryWork.name[0] = 0;
    NameEntryWork.unk18 = mode;
    NameEntryWork.unk1C = index;
    NameEntryWork.unk20 = 0;
    NameEntryWork.unk24 = fade;
    NameEntryWork.unk28 = 1;
    GSfloorPush(0x390);
    if (fade == 0) {
        floorSetFadeScript(0, 0x05960008);
    }
    floorWaitForChange();
    return NameEntryWork.unk20;
}

extern "C" {
s32 menuNameEntryOpen(s32 mode, s32 param) {
    int ids[4] = {0x37, 0x40, 0x38, 0x41};
    s32 result;
    int i;
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 0);
        }
    }
    result = pushNameEntryFloor(mode, param, 1);
    for (i = 0; i < 4; i++) {
        if (menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 1);
        }
    }
    return result;
}

s32 menuNameEntryCtrl(tagWINDOW_WORK *window)
{
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    switch (window->unk1) {
    case 0:
        if (window->unk2 == 0) {
            winSeqSetMenu(window->unk4, 0x58);
            *arg->unk30 = 0.0f;
            window->unk2 = 1;
        }
        break;
    case 2:
    {
        f32 *fp = arg->unk30;
        f32 v = 0.033333335f;
        v = *fp + v;
        *fp = v;
        if (v >= 1.0f) {
            fp = arg->unk30;
            *fp -= 1.0f;
        }
        break;
    }
    case 3:
        if (window->unk2 == 0) {
            winSeqSetMenu(window->unk4, 0x5C);
            window->unk2 = 1;
        }
        break;
    }
    return 0;
}
}

static void putGScharL(GSgfxLayerID layer, int x, int y, u32 color, u16 ch)
{
    u16 buf[2];
    buf[0] = ch;
    buf[1] = 0;
    msgctrlSetValue(0x37, buf);
    {
        s32 w = 0x1B - (s16)(GSmsgGetRect(0x4275) >> 16);
        GSmsgPrint2(layer, x + w / 2, y, color, 0x4275);
    }
}

extern "C" {
s32 menuNameEntryDrawXButtonText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 next = *((NAME_ENTRY_ARG *)window->unk68)->unk24 + 1;
    if (next >= 2) {
        next -= 2;
    }
    if (next >= 0 && next < 2) {
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, window->unk93 | 0xFFFFFF00, SheetData[next].title);
    }
    return 0;
}

s32 menuNameEntryDraw50Text(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int x;
    int y;
    int col;
    int row;
    SHEET sheet;
    u16 ch;
    sheet = (SHEET)*((NAME_ENTRY_ARG*)w->unk68)->unk24;
    for (row = 0, y = 0; row < 8; y += 0x1E, row++) {
        for (col = 0, x = -2; (ch = getCharSheet(sheet, col, row)) != 0; x += 0x1A, col++) {
            putGScharL((GSgfxLayerID)winSpriteGetLayerID(w, sp), x, y, w->unk93 | ~0xFF, ch);
        }
    }
    return 0;
}
}

static void ballMain1(BALL_WORK *ball)
{
    if (ball->active != 0) {
        f32 r;
        f32 t = ball->t;
        t += 1.0f;
        ball->t = t;
        if (t >= ball->life) {
            ball->active = 0;
        }
        r = ball->t / ball->life;
        ball->scale = ball->maxScale * r;
        ball->alpha = 128.0f * (1.0f - r);
    }
}

static void generateBall(void)
{
    if (!(HSD_Randf() > 0.1f)) {
        int i;
        for (i = 0; i < 30; i++) {
            if (BallWork[i].active == 0) {
                break;
            }
        }
        if (i < 30) {
            BallWork[i].active = 1;
            BallWork[i].x = 640.0f * HSD_Randf();
            BallWork[i].y = 480.0f * HSD_Randf();
            BallWork[i].scale = 0.001f;
            BallWork[i].maxScale = 1.999f * HSD_Randf() + 0.001f;
            BallWork[i].color = -256;
            BallWork[i].alpha = 0x80;
            BallWork[i].t = 0.0f;
            BallWork[i].life = 60.0f * HSD_Randf() + 120.0f;
        }
    }
}

static void ballMain(void)
{
    int i;
    generateBall();
    for (i = 0; i < 30; i++) {
        if (BallWork[i].active != 0) {
            ballMain1(&BallWork[i]);
        }
    }
}

extern "C" {
s32 menuNameEntryBackCtrl(tagWINDOW_WORK *window)
{
    int i;
    switch (window->unk1) {
    case 0:
        if (window->unk2 == 0) {
            for (i = 0; i < 30; i++) {
                BallWork[i].active = 0;
            }
            i = 0;
            do {
                ballMain();
                i++;
            } while (i < 600);
            window->unk2 = 1;
        }
        break;
    case 2:
        ballMain();
        break;
    case 3:
        if (window->unk2 == 0) {
            window->unk2 = 1;
        }
        break;
    }
    return 0;
}

s32 menuNameEntryBackDrawBall(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    int i;
    MenuSpriteVal *val;
    s16 w;
    s16 h;
    menuSpriteBiosGetPtr(0x1E);
    val = menuSpriteBiosGetValPtr();
    w = val->unk4;
    h = val->unk6;
    for (i = 0; i < 30; i++) {
        if (BallWork[i].active != 0) {
            f32 sx = (f32)w * BallWork[i].scale;
            f32 sy = (f32)h * BallWork[i].scale;
            f32 cx = BallWork[i].x - sx / 2.0f;
            f32 cy = BallWork[i].y - sy / 2.0f;
            u32 color = BallWork[i].color | BallWork[i].alpha;
            windowDrawSprite2((s32)(0.5f + cx), (s32)(0.5f + cy), (s32)(0.5f + sx), (s32)(0.5f + sy), color, window, 0x1E, 0,
                              winSpriteGetLayerID(window, sprite));
        }
    }
    return 0;
}
}

static s32 getName(u16 *dst, int mode, int arg)
{
    u16 *name;
    switch (mode) {
    case 0:
        name = GSmsgGetGSchar(DefKenName[0]);
        break;
    case 1:
        name = GSmsgGetGSchar(DefHizukiName[0]);
        break;
    case 2: {
        Pokemon *p = heroGetStatus(0, 3, arg);
        if (pokemonCheckValid(p) == 0) {
            name = 0;
        } else {
            name = pokemonBiosGetNicknamePtr(p);
        }
        break;
    }
    case 5:
        name = pokemonBiosGetNicknamePtr((Pokemon *)arg);
        break;
    case 3:
        name = pcboxGetPokemonBoxName(0, arg);
        break;
    case 4: {
        Pokemon *p = fightFloorGetDefPokemonPtr(0);
        if (pokemonCheckValid(p) == 0) {
            name = 0;
        } else {
            name = pokemonBiosGetNicknamePtr(p);
        }
        break;
    }
    case 6:
        name = (u16 *)arg;
        break;
    default:
        name = 0;
        break;
    }
    if (name == 0) {
        return 0;
    }
    GScharCpy(dst, name);
    return 1;
}

static s32 setName(u16 *name, int mode, int arg)
{
    Pokemon *p;
    s32 ok = 1;
    switch (mode) {
    case 0:
        break;
    case 1:
        heroSetStatus(0, 0x17, name);
        break;
    case 2: {
        p = heroGetStatus(0, 3, arg);
        if (pokemonCheckValid(p) == 0) {
            ok = 0;
        } else {
            pokemonBiosSetNicknamePtr(p, name);
        }
        break;
    }
    case 5:
        pokemonBiosSetNicknamePtr((Pokemon *)arg, name);
        break;
    case 3:
        pcboxSetPokemonBoxName(0, arg, name);
        break;
    case 4: {
        p = fightFloorGetDefPokemonPtr(0);
        if (pokemonCheckValid(p) == 0) {
            ok = 0;
        } else {
            pokemonBiosSetNicknamePtr(p, name);
        }
        break;
    }
    case 6:
        GScharCpy((u16 *)arg, name);
        break;
    default:
        ok = 0;
        break;
    }
    return ok;
}

static s32 selectName(u16 *dst, const u32 *list, int count)
{
    s32 sel;
    s32 ok;
    u16 *chosen;
    s32 args[2];
    s32 *pargs = args;
    for (;;) {
        args[0] = (s32)list;
        args[1] = count;
        sel = menuOpenCustom(0x65, windowGetActiveID(), 0, 0, 1, 1, pargs);
        if (sel == 0) {
            GSsndPlayNow(0x11);
            ok = 0;
            break;
        }
        if (sel == 4 || sel == -1) {
            GSsndPlayNow(0x11);
            ok = 0;
            break;
        }
        chosen = GSmsgGetGSchar(list[sel - 1]);
        if (confirmName(chosen) != 0) {
            ok = 1;
            break;
        }
    }
    menuClose(0x65);
    menuCloseSync(0x65, 1);
    if (ok != 0) {
        GScharCpy(dst, chosen);
        return 0;
    }
    if (sel != 0) {
        return 2;
    }
    return 1;
}

extern "C" {
s32 menuNameEntryCursor(tagWINDOW_WORK *window)
{
    u16 rep = windowGetKeyRepeat();
    u16 trg = windowGetKeyTrg();
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    if ((trg & 0x40) != 0) {
        change50Sheet(arg);
        GSsndPlayNow(0x14);
        return 0;
    }
    if ((trg & 0x10) != 0) {
        if (selectLetter(arg) != 0) {
            window->unkA4 = 1;
            return 0;
        }
        if (getGScharLen(arg->unk18) >= ModeData[arg->unk1C].maxLen) {
            *arg->unk28 = 10;
            *arg->unk2C = 7;
        }
        return 0;
    }
    if ((trg & 0x20) != 0) {
        if (backNameCursor(arg) != 0) {
            GSsndPlayNow(0x12);
        }
        return 0;
    }
    if ((trg & 0x400) != 0) {
        change50Sheet(arg);
        GSsndPlayNow(0x14);
        return 0;
    }
    if ((trg & 0x800) != 0) {
        window->unkA4 = 1;
        return 0;
    }
    if ((rep & 8) != 0) {
        s32 v = *arg->unk28 + 1;
        if (*arg->unk2C < 6) {
            if (v < 11) {
                GSsndPlayNow(0x10);
            } else {
                v = 10;
            }
        } else if (v > 7) {
            v = 7;
        } else {
            GSsndPlayNow(0x10);
        }
        *arg->unk28 = v;
    }
    if ((rep & 4) != 0) {
        s32 v = *arg->unk28 - 1;
        if (*arg->unk2C > 5 && v > 6) {
            v = 6;
        }
        if (v < 0) {
            v = 0;
        } else {
            GSsndPlayNow(0x10);
        }
        *arg->unk28 = v;
    }
    if ((rep & 2) != 0) {
        s32 v = *arg->unk2C;
        if (*arg->unk28 >= 11) {
            if (v == 1) {
                v = v + 2;
            } else {
                v = v + 1;
            }
        } else {
            v = v + 1;
        }
        if (v >= 8) {
            v = 7;
        } else {
            GSsndPlayNow(0x10);
        }
        *arg->unk2C = v;
    }
    if ((rep & 1) != 0) {
        s32 v = *arg->unk2C;
        if (*arg->unk28 >= 11) {
            if (v == 2) {
                v = v - 2;
            } else {
                v = v - 1;
            }
        } else {
            v = v - 1;
        }
        if (v < 0) {
            v = 0;
        } else {
            GSsndPlayNow(0x10);
        }
        *arg->unk2C = v;
    }
    return 0;
}
}

static u16 exchangeDakuon(u16 ch, DAKUON_MODE mode)
{
    int cur;
    const u32 *t;
    s32 len;
    u16 *p;
    int j;
    for (cur = 0, t = DakuHanTbl; cur < 2; t++, cur++) {
        if (*t != 0) {
            len = GSmsgGetLength(*t);
            p = GSmsgGetGSchar(*t) + 1;
            for (j = 1; j < len; j += 2, p += 2) {
                if (*p == ch) {
                    break;
                }
            }
            if (j < len) {
                break;
            }
        }
    }
    if (cur >= 2) {
        cur = 0;
    }
    if (cur == mode) {
        return ch;
    }
    if (cur == DAKUON_VOICED || cur == DAKUON_VOICED) {
        ch = p[-1];
    }
    if (mode == 0) {
        return ch;
    }
    len = GSmsgGetLength(DakuHanTbl[mode]);
    p = GSmsgGetGSchar(DakuHanTbl[mode]);
    for (j = 0; j < len; j += 2, p += 2) {
        if (*p == ch) {
            break;
        }
    }
    if (j >= len) {
        return 0;
    }
    return p[1];
}

static s32 selectLetter(NAME_ENTRY_ARG *arg)
{
    u16 ch;
    s32 done = 0;
    u32 snd = 0;
    s32 kind;
    s32 x = *arg->unk28;
    s32 y = *arg->unk2C;
    if (y > 5 && x > 6) {
        switch (y) {
        case 7:
            kind = 5;
            break;
        default:
            kind = 4;
            break;
        }
    } else {
        ch = getCharSheet((SHEET)*arg->unk24, x, y);
        if (ch == 0) {
            ch = *GSmsgGetGSchar(0x3B1D);
        }
        kind = getSpchar(ch);
    }
    switch (kind) {
    case 1:
    case 2: {
        DAKUON_MODE dm;
        s32 idx;
        if (kind == 1) {
            dm = (DAKUON_MODE)1;
        } else {
            dm = (DAKUON_MODE)1;
        }
        idx = *arg->unk34 - 1;
        if (idx >= 0) {
            u16 *buf = arg->unk18;
            s32 off = idx * 2;
            u16 r = exchangeDakuon(*(u16 *)((u8 *)buf + off), dm);
            if (r != 0) {
                *(u16 *)((u8 *)buf + off) = r;
            }
        }
        snd = 0x11;
        break;
    }
    case 4:
        if (backNameCursor(arg) != 0) {
            snd = 0x12;
        }
        break;
    case 5:
        done = 1;
        break;
    case 3:
        change50Sheet(arg);
        snd = 0x14;
        break;
    case 0:
        ch = *GSmsgGetGSchar(0x3B1D);
    default: {
        s32 cur;
        s32 maxLen;
        s32 next;
        maxLen = ModeData[arg->unk1C].maxLen;
        cur = *arg->unk34;
        u16 *p;
        if (cur >= maxLen) {
            cur = maxLen - 1;
        }
        next = cur + 1;
        p = (u16 *)((u8 *)arg->unk18 + cur * 2);
        p[0] = ch;
        p[1] = 0;
        if (next >= maxLen + 1) {
            next = maxLen;
        }
        snd = 0x11;
        *arg->unk34 = next;
        break;
    }
    }
    if (snd != 0) {
        GSsndPlayNow(snd);
    }
    return done;
}

extern "C" {
s32 menuNameEntryDrawNamePokemonText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 mode = ((NAME_ENTRY_ARG *)window->unk68)->unk1C;
    if (mode == 6) {
        return 0;
    }
    if (mode == 3) {
        return 0;
    }
    if (mode == 0) {
        return 0;
    }
    return menuNameEntryDrawNameText(window, sprite, 10, mode);
}

void menuNameEntryDrawNameTrainerCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 mode = ((NAME_ENTRY_ARG *)window->unk68)->unk1C;
    if (mode == 6) {
        menuNameEntryDrawNameCursor(window, sprite, 10, 6);
    } else if (mode == 3) {
        menuNameEntryDrawNameCursor(window, sprite, 8, 3);
    } else if (mode == 2) {
        menuNameEntryDrawNameCursor(window, sprite, 10, 2);
    } else if (mode == 4) {
        menuNameEntryDrawNameCursor(window, sprite, 10, 4);
    } else if (mode == 5) {
        menuNameEntryDrawNameCursor(window, sprite, 10, 5);
    } else {
        menuNameEntryDrawNameCursor(window, sprite, 7, 0);
    }
}
}

static s32 menuNameEntryDrawNameText(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, int a, int b)
{
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    s32 mode = arg->unk1C;
    if (mode == 1) {
        if (b == 0) {
            sprite->unk67 = 0xFF;
        } else {
            sprite->unk67 = 0;
        }
    } else if (mode != b) {
        sprite->unk67 = 0;
    } else {
        sprite->unk67 = 0xFF;
    }
    if (sprite->unk67 != 0) {
        int n = 0;
        int x = 0;
        u16 ch;
        u16 *p = arg->unk18;
        while ((ch = *p) != 0) {
            putGScharL((GSgfxLayerID)winSpriteGetLayerID(window, sprite), x, 0, window->unk93 | 0xFFFFFF00, ch);
            x += 26;
            n++;
            p++;
        }
        if (n < ModeData[arg->unk1C].maxLen && window->unkA4 == 0) {
            u16 ch2 = getCharSheet((SHEET)*arg->unk24, *arg->unk28, *arg->unk2C);
            if (ch2 != 0 && getSpchar(ch2) == 6) {
                f32 *fp = arg->unk30;
                f32 sv = sin(2.0f * (3.14f * *fp));
                putGScharL((GSgfxLayerID)winSpriteGetLayerID(window, sprite), n * 26, 0, (u8)(128.0f * (1.0f + sv)) | 0xFFFFFF00, ch2);
            }
        }
        sprite->unk67 = 0xFF;
    }
    return 0;
}

static s32 inputName(u16 *dst, u16 *backup, int mode, int idx, int flag)
{
    NAME_ENTRY_ARG arg;
    NAME_ENTRY_ARG *pargs;
    u16 *chosen;
    s32 ok;
    s32 done = 0;
    GScharCpy(arg.name, backup);
    *dst = 0;
    arg.unk18 = dst;
    arg.unk1C = mode;
    arg.unk20 = idx;
    Sheet = 0;
    arg.unk24 = &Sheet;
    SheetCurX = 0;
    arg.unk28 = &SheetCurX;
    SheetCurY = 0;
    arg.unk2C = &SheetCurY;
    SheetCurAnimTime = 0.0f;
    arg.unk30 = &SheetCurAnimTime;
    NameCurX = 0;
    arg.unk34 = &NameCurX;
    arg.unk38 = &DefSheetCurPosX;
    arg.unk3C = &DefSheetCurPosY;
    arg.unk40 = &DefNamePokemonCurPosX;
    arg.unk44 = &DefNameBoxCurPosX;
    arg.unk48 = &DefNameTrainerCurPosX;
    dbgMenuSetEnable(0);
    pargs = &arg;
    while (done == 0) {
        menuOpenCustom(0x66, windowGetActiveID(), 0, 0, 1, 1, pargs);
        if (chkValidName(arg.unk18) != 0) {
            chosen = arg.unk18;
        } else {
            chosen = arg.name;
        }
        ok = confirmName(chosen);
        if (flag == 0) {
            done = 1;
            if (ok == 0) {
                NameEntryWork.name[0] = 0;
            }
        } else if (ok != 0) {
            done = 1;
        }
    }
    dbgMenuSetEnable(1);
    menuClose(0x66);
    menuCloseSync(0x66, 1);
    if (ok != 0) {
        GScharCpy(NameEntryWork.name, chosen);
        return 1;
    }
    return 0;
}

extern "C" {
void menuNameEntry(void)
{
    u16 backup[12];
    s32 again;
    s32 args[2];
    if (getName(backup, NameEntryWork.unk18, NameEntryWork.unk1C) == 0) {
        backup[0] = 0;
    }
    loadModel(0x68, &MenuModel, NameEntryWork.unk18, NameEntryWork.unk1C);
    FlashSystemSetPlayFrameLabel(0x22063000, "start", "end");
    FlashSystemSetLoopFlag(0x22063000, 0);
    FlashSystemSetNowFrameLabel(0x22063000, "start");
    args[0] = NameEntryWork.unk18;
    args[1] = NameEntryWork.unk1C;
    menuOpenCustom(0x68, windowGetActiveID(), 0, 0, 1, 1, args);
    if (NameEntryWork.unk28 == 0) {
        fadeSet(2, 0.5f);
        fadeCheck(1);
    }
    if (ModeData[NameEntryWork.unk18].defCount > 0) {
        again = 1;
        while (again != 0) {
            const ModeDataT *md = &ModeData[NameEntryWork.unk18];
            switch (selectName(NameEntryWork.name, md->defNames, md->defCount)) {
            case 1:
                if (inputName(NameEntryWork.name, backup, NameEntryWork.unk18, NameEntryWork.unk1C, 0) != 0) {
                    again = 0;
                }
                break;
            case 2:
                again = 0;
                break;
            default:
                again = 0;
                break;
            }
        }
    } else {
        inputName(NameEntryWork.name, backup, NameEntryWork.unk18, NameEntryWork.unk1C, 1);
    }
    fadeSet(3, 0.5f);
    fadeCheck(1);
    menuModelTerm(&MenuModel);
    menuClose(0x68);
    menuCloseSync(0x68, 1);
    setName(NameEntryWork.name, NameEntryWork.unk18, NameEntryWork.unk1C);
    if (GScharCmp(NameEntryWork.name, backup) == 0) {
        NameEntryWork.unk20 = 0;
    } else {
        NameEntryWork.unk20 = 1;
    }
    if (NameEntryWork.unk18 == 0) {
        menuTitleBattleSelectFree();
    }
    if (NameEntryWork.unk28 != 0) {
        GSfloorPop();
        if (NameEntryWork.unk24 != 0) {
            floorSetFadeScript(0, 0x05960008);
        } else {
            floorSetFadeScript(0, 0);
        }
    }
}
}

static void loadModel(long layer, MENU_MODEL *model, int mode, int idx)
{
    s32 tbl[4] = { 0x16C90400, 0x16C70400, 0, 0x10560400 };
    s32 motion;
    s32 dummy;
    s32 itemId;
    MenuItemInfo *info;
    switch (mode) {
    case 2:
    case 4:
    case 5:
        itemId = 0x280;
        break;
    case 3:
    case 6:
    default:
        itemId = 0x27F;
        break;
    }
    info = menuItemBiosGetPtr(layer, itemId);
    menuModelInit(model, info->a, info->b);
    switch (mode) {
    case 0:
    case 1: {
        s32 id = tbl[mode];
        menuModelLoad(model, id);
        peopleInfoBiosGetMotion(peopleInfoBiosGetPtr(id), 1, &motion, &dummy);
        menuModelSetMotion(model, motion);
        break;
    }
    case 2: {
        Pokemon *p = heroGetStatus(0, 3, idx);
        if (pokemonCheckValid(p) != 0) {
            menuModelLoadPokemon(model, p);
        }
        break;
    }
    case 5:
        menuModelLoadPokemon(model, (Pokemon *)idx);
        break;
    case 3:
        menuModelLoad(model, tbl[mode]);
        break;
    case 4: {
        Pokemon *p = fightFloorGetDefPokemonPtr(0);
        if (pokemonCheckValid(p) != 0) {
            menuModelLoadPokemon(model, p);
        }
        break;
    }
    case 6:
        break;
    }
    menuModelCheck(model, 1);
}

static s32 menuNameEntryDrawNameCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, int count, int mode)
{
    NAME_ENTRY_ARG *arg = (NAME_ENTRY_ARG *)window->unk68;
    s32 position;
    s32 cursor;
    s32 display;
    cursor = 0;
    display = 0;
    s32 maxLen = ModeData[arg->unk1C].maxLen;
    position = *arg->unk34;
    if (position >= maxLen) position = maxLen - 1;
    winSpriteSetDisp(sprite, 0);
    switch (sprite->unk6) {
    case 0x8ED: cursor = 1;
    case 0x8EC: cursor++;
    case 0x30B: cursor++;
    case 0x30A: cursor++;
    case 0x309: cursor++;
    case 0x308: cursor++;
    case 0x307:
        if (arg->unk1C >= 7 || arg->unk1C < 2) display = 1;
        break;
    case 0x68D: cursor = 1;
    case 0x68C: cursor++;
    case 0x68B: cursor++;
    case 0x68A: cursor++;
    case 0x689: cursor++;
    case 0x688: cursor++;
    case 0x687: cursor++;
    case 0x686: cursor++;
    case 0x685: cursor++;
    case 0x684:
        switch (mode) {
        case 2: case 4: case 5: case 6: display = 1; break;
        case 3:
            if (cursor != 0 && cursor != 9) { display = 1; cursor--; }
            break;
        }
        break;
    }
    if (display) {
        if (cursor == position) {
            f32 sv = sin(2.0f * (3.14f * *arg->unk30));
            sprite->unk67 = 128.0f * (1.0f + sv);
            winSpriteSetDisp(sprite, 1);
        } else if (cursor < position) {
            sprite->unk67 = 255;
            winSpriteSetDisp(sprite, 1);
        }
    }
    return 0;
}
