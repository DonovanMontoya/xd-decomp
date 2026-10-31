#pragma defer_codegen on
#pragma force_active on
#pragma dollar_identifiers on
#include <game/menuPokemonLayout.hpp>

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_NONE,
    MENU_POKEMON_CB_PREV,
    MENU_POKEMON_CB_NEXT
};

struct MENU_POKEMON_STATUS_TBL;

extern "C" {
s32 heroItemCheckAddItemDataId(Hero*,u16);
void heroItemAddItemDataId(Hero*,u16,s32,s32);
s32 heroItemDecItemDataId(Hero*,u16,s32,s16);
u16 pokemonDoItemSoubi(Pokemon*,u16,s32);
u16 pokemonGetSoubiItemDataId(Pokemon*);
s8 menuSubOpenYesNo(s32,s32,s32,s32);
void winMsgClose(s32);
void winMsgOpen(s32,s32,s32,s32);

s32 menuSubCalcColor(tagWINDOW_WORK*,tagSPRITE_WORK*);
u8 itemDataBiosGetWazaMachineNo(s32);
u16 itemDataBiosGetWazaIDByWazaMachineNo(u8);
u8 pokemonIsDarkPokemon(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
void* pokemonDataBiosGetPtr(u16);
u8 pokemonDataBiosGetWazaMcn(void*,u8);
u8 pokemonDB_GetTeachWaza(u16,u16);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon*,u16);
void GSmsgPrintRect(s32,s32,s32,s16,s32,u32,u32);
u32 GSmsgGetRect(u32);
u16* GSmsgGetGSchar(u32);
void menuFaceDispFromID(tagWINDOW_WORK*,tagSPRITE_WORK*,u16);
void windowDrawSprite2(s32,s32,s16,s16,s32,tagWINDOW_WORK*,u16,s32,s32);
double sin(double);
struct TeachMove {u16 move;u8 reserved[10];};
extern TeachMove* wazaoshie_data;

void* memset(void *, int, u32);
u32 GSflagGet(s32);
void GSfloorPop(void);
void GSfloorPush(s32);
u8 GSgfxVideoGetVsyncRate(void);
void GSthreadSwitch(void);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
Pokemon* fightFloorGetGcHeroFightTrainerPtr(s32);
Hero* fightTrainerGetStatus(FIGHT_TRAINER *, s32, s32, s32);
Pokemon* fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER *, u16);
Pokemon* heroBiosGetPokemonPtr(Hero *, u16);
Hero* menuCBBios_GetRegisteredHero(void);
void menuCloseCustom(s32, s32, s32);
void menuCreateOffScreen(f32, f32);
u8 menuGetOffScreenFlag(void);
void menuOffScreenSetPriority(s32);
void menuReleaseOffScreen(f32);
u8 pokemonCheckValid(Pokemon *);
void msgctrlSetValue(s32, void *);
s32 itemDataBiosGetPtr(u16);
u8 itemDataBiosGetKind(void);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSmsgPrint2(s32, s32, s32, u32, u32);
u8 winSeqCheckMove(s32);
u16 windowGetKeyTrg(void);
u16 menuGetCursorItemID(s32);
void GSsndPlayNow(s32);
void menuButtonNormal(tagWINDOW_WORK *);
s32 menuOpenCustom(s32, s32, s32 *, s32, bool, s32, ...);
void* windowSearchID(s32);
void menuDataBiosGetXY(s16, s16 *, s16 *);
void winSeqSetMenu(s32, s32);
void fadeSet(s32, f32);
void fadeCheck(s32);
void menuPokemonStatusOpenFieldMenu(Pokemon *, Pokemon *(*)(Pokemon *, MENU_POKEMON_CB_TYPE, long), s32);
void menuPokemonStatusOpenFightMenu(FIGHT_TRAINER *, Pokemon *, Pokemon *(*)(Pokemon *, MENU_POKEMON_CB_TYPE, long), s32);
s32 menuOpen(s32, s32);
void menuClose(s32);
u8 menuPokemonCheckPokemonChange(void *, FIGHT_TRAINER *, s32);
void pokemonToMenuPokemonStatus(Pokemon *, s32, MENU_POKEMON_STATUS_TBL *, s32);
u16 pokemonGetJoutaiMenuSpriteId(Pokemon *);
u16 menuPocket2Call(s32, s32, s32);
u32 wazaGetStatus(void*,u32,u16,u16);
struct PokemonMenuWazaStatus;
void pokemonToMenuWazaStatus(Pokemon*,PokemonMenuWazaStatus*);
s32 menuSubOpenSelect2(s32, s32 *, s32, s32, s32, s32, s32, s32);
MENU_POKEMON_STATUS_TBL* windowGetParam(tagWINDOW_WORK *, s32);
void menuItemBiosSetXY(s32, s16, s16, s16);
void menuDataBiosSetXY(s16, s16, s16);
f32 timeGetLastFrameSec(void);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
s32 menuGetCursor(s32);
void pokemonReplace(Pokemon *, Pokemon *);
void menuSubSleep(f32);
u16 windowGetKeyRepeat(u8 *);
u8 menuDataBiosGetDispMax(s32);
extern s32 lbl_804E7EB8;
extern s32 lbl_804E7EBC;
u8 menuPocket2GetLastSlotID(void);
s32 pokemonGetStatus(Pokemon *, s32, s32, s32);
Hero* savedataGetStatus(s32, s32);
}

struct MenuInfoEntry {
    s16 id;
    s16 a;
    s16 b;
    s16 c;
};
struct MenuInfo {
    MenuInfoEntry e[6];
};

// Status identifiers and their menu sprites retained by the original unit.
extern "C" const u16 spriteTbl[7][2] = {
    {3, 0x83}, {4, 0x83}, {5, 0x80}, {6, 0x81}, {7, 0x82}, {8, 0x85}, {0, 0}
};

static MenuInfo menu_info[2] = {
    { { { 0x4B, 0x15F, 0x12, 0x52 }, { 0x49, 0x15D, 0x113, 0x26 }, { 0x48, 0x15C, 0x113, 0x69 }, { 0x47, 0x15B, 0x113, 0xAC },
        { 0x46, 0x15A, 0x113, 0xEF }, { 0x4D, 0x15A, 0x113, 0x132 } } },
    { { { 0x4B, 0x15F, 0x12, 0x44 }, { 0x4A, 0x15E, 0x12, 0xEA }, { 0x49, 0x15D, 0x113, 0x31 }, { 0x48, 0x15C, 0x113, 0x83 },
        { 0x47, 0x15B, 0x113, 0xD7 }, { 0x46, 0x15A, 0x113, 0x129 } } },
};
static MENU_POKEMON_WORK _menuPokemon;
static s16 _menuPokemonTimer;
static MENU_POKEMON_STATUS_TBL _menuPokemonStatusAll[6];

static Pokemon* _menuPokemonGetPokemonPtr(u16 index);
static int _menuPokemonCheckItem(tagSPRITE_WORK*,s8);
static Hero* _menuPokemonGetHeroPtr(void);
static void _menuPokemonMakeStatus(MENU_POKEMON_STATUS_TBL *tbl);
static s32 _menuPokemonSub(u8 mode, u32 a, FIGHT_TRAINER *trainer);
static s32 _menuPokemonActionGive(s8 index, short slot, u16 item, u16 *out);
static s32 _menuPokemonActionField(s8 index);
static s32 _menuPokemonActionFieldItem(s8 index);
static s8 _menuPokemonOpenList(bool flag);
static s8 _menuPokemonActionStatus(s8 index, bool flag);
static u8 _menuPokemonMovePanel(long index, u8 mode);
extern "C" u16 menuPokemonGetJoutaiSpriteID(Pokemon *p, u8 mode);

extern "C" {
void menuPokemonInitWork(void);

s32 menuPokemonCtrlWaza(void);

void menuPokemonCloseWazaLight(void);
}

static Pokemon* _menuPokemonStatusCB(Pokemon *pokemon, MENU_POKEMON_CB_TYPE type, long arg);

extern "C" {
void menuPokemonClose(void);
}

static s32 _menuPokemonOpen(u8 mode, u8 a, u8 b, u16 c, FIGHT_TRAINER *trainer, bool flag);

extern "C" {
void menuPokemonOpenItemGive(u8 a, u8 b, u16 c, FIGHT_TRAINER *t);

void menuPokemonOpenItemUse(u8 mode, bool flag, u16 c, FIGHT_TRAINER *t);

void menuPokemonOpenFight(u8 flag, u8 b, FIGHT_TRAINER *c, void *d);

void menuPokemonOpen(u8 mode, u16 c, FIGHT_TRAINER *t);

s32 menuPokemonMain(void);
}

static Pokemon* _menuPokemonCbLoadPokemonList(void *arg);

extern "C" {
void menuPokemonUpdate(void);
}

static Hero* _menuPokemonGetHeroPtr(void);

static Pokemon* _menuPokemonGetPokemonPtr(u16 index);

extern "C" {
void menuPokemonDrawHelp(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite);

void menuPokemonButton(tagWINDOW_WORK *window);
}

static s8 _menuPokemonOpenList(bool flag);

static s8 _menuPokemonActionStatus(s8 index, bool flag);

static s32 _menuPokemonActionFight(s8 index);

static inline s32 fieldMenuOpenClose(s32 id)
{
    s32 sel = menuOpen(id, 1);
    menuClose(id);
    return sel;
}
static s32 _menuPokemonActionField(signed char index);

static s32 _menuPokemonActionFieldItem(s8 index);

static u8 _menuPokemonMovePanel(long index, u8 mode);

static void _menuPokemonMakeStatus(MENU_POKEMON_STATUS_TBL *tbl);

extern "C" u16 menuPokemonGetJoutaiSpriteID(Pokemon *p, u8 mode);

extern "C" {
static u8 wazaStatus$2693[0x48];
s32 menuPokemonOpenWazaLight(s8 index);

s32 menuPokemonCtrl(tagWINDOW_WORK *window);
}

extern "C" {
void menuPokemonCursor(tagWINDOW_WORK *window);
}

extern "C" {
void menuPokemonDrawCur(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite);
}

static int _menuPokemonCheckItem(tagSPRITE_WORK *sprite, s8 kind);

extern "C" void menuPokemonDrawItem(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);

static s32 _menuPokemonActionGive(s8 index, short slot, u16 item, u16* out);

#pragma dollar_identifiers on
extern "C" {
static u16 pokemonFaceLoadCnt$2268;
void menuFaceLoad(s32,Pokemon*(*)(void*),void*);
u8 menuFaceCheckLoading();
f32 pokemonGetDp(Pokemon*);
}
static s32 _menuPokemonSub(u8 mode,u32 a,FIGHT_TRAINER* trainer);


static Hero* _menuPokemonGetHeroPtr(void)
{
    FIGHT_TRAINER *trainer = _menuPokemon.unk10;
    switch (_menuPokemon.unkC) {
    case 0:
        if (GSflagGet(0x30D) == 0) {
            return savedataGetStatus(0, 2);
        }
        return menuCBBios_GetRegisteredHero();
    case 1:
        if (trainer == 0) {
            fightFloorGetGcHeroFightTrainerPtr(0);
            return 0;
        }
        return fightTrainerGetStatus(trainer, 0, 0x44, 0);
    default:
        return 0;
    }
}

static Pokemon* _menuPokemonGetPokemonPtr(u16 index)
{
    Pokemon *p = 0;
    FIGHT_TRAINER *trainer = _menuPokemon.unk10;
    switch (_menuPokemon.unkC) {
    case 0: {
        Hero *hero;
        if (index >= 6) {
            return 0;
        }
        hero = _menuPokemonGetHeroPtr();
        if (hero == 0) {
            return 0;
        }
        p = heroBiosGetPokemonPtr(hero, index);
        break;
    }
    case 1: {
        Pokemon *fp;
        if (index >= 6) {
            return 0;
        }
        if (trainer == 0) {
            fightFloorGetGcHeroFightTrainerPtr(0);
            return 0;
        }
        fp = fightTrainerGetValidFightPokemonPtr(trainer, index);
        if (fp == 0) {
            return 0;
        }
        p = (Pokemon *)pokemonGetStatus(fp, 0, 0xCC, 0);
        break;
    }
    case 2:
        if (index >= 30) {
            return 0;
        }
        p = 0;
        break;
    }
    if (pokemonCheckValid(p) == 0) {
        return 0;
    }
    return p;
}

extern "C" u16 menuPokemonGetJoutaiSpriteID(Pokemon *p, u8 mode)
{
    static u16 top_joutai_tbl[8] = { 0, 0x142, 0x146, 0x143, 0x144, 0x145, 0x148, 0 };
    static u16 status_joutai_tbl[7] = { 0, 0x7E, 0x83, 0x80, 0x81, 0x82, 0x85 };
    u16 id;
    if ((u32)(pokemonGetStatus(p, 0, 0x7B, 0) != 0) == 1) {
        id = 1;
    } else {
        switch (pokemonGetJoutaiMenuSpriteId(p)) {
        case 0x83:
            id = 2;
            break;
        case 0x80:
            id = 3;
            break;
        case 0x81:
            id = 4;
            break;
        case 0x82:
            id = 5;
            break;
        case 0x85:
            id = 6;
            break;
        default:
            id = 0;
            break;
        }
    }
    if (mode == 0) {
        return top_joutai_tbl[id];
    }
    return status_joutai_tbl[id];
}

void menuPokemonUpdate(void)
{
    _menuPokemonMakeStatus(_menuPokemonStatusAll);
}

static void _menuPokemonMakeStatus(MENU_POKEMON_STATUS_TBL *tbl)
{
    MENU_POKEMON_STATUS_TBL *e;
    Pokemon *p;
    u16 i;
    memset(tbl, 0, 0x120);
    for (i = 0; i < 6; i++) {
        e = &tbl[i];
        p = _menuPokemonGetPokemonPtr(i);
        if (p == 0) {
            e->unk0 = 0;
        } else {
            pokemonToMenuPokemonStatus(p, 0, e, -1);
            if ((u32)(pokemonGetStatus(p, 0, 0x7B, 0) != 0) == 1) {
                e->unk1A = 0;
            }
            e->unk24 = menuPokemonGetJoutaiSpriteID(p, 0);
        }
    }
}

static s8 _menuPokemonOpenList(bool flag)
{
    s32 sel = (s8)_menuPokemon.unk6;
    s8 r = menuOpenCustom(0x4C, 0, &sel, 0, flag, 1, _menuPokemonStatusAll);
    if (flag == 0) {
        tagWINDOW_WORK *w = (tagWINDOW_WORK *)windowSearchID(0x4C);
        if (w != 0) {
            w->unkA4 = 1;
        }
        r = (s8)sel;
    }
    if (_menuPokemon.unk1 == 0) {
        r = -2;
    }
    return r;
}

static s8 _menuPokemonActionStatus(s8 index, bool flag)
{
    Pokemon *p;
    menuCloseCustom(0x4C, 0, 1);
    p = _menuPokemonGetPokemonPtr(index);
    fadeSet(3, 0.25f);
    fadeCheck(1);
    menuOffScreenSetPriority(0);
    if (flag) {
        menuPokemonStatusOpenFieldMenu(p, _menuPokemonStatusCB, 0);
    } else {
        menuPokemonStatusOpenFightMenu(_menuPokemon.unk10, p, _menuPokemonStatusCB, 0);
    }
    menuOffScreenSetPriority(1);
    _menuPokemonOpenList(0);
    fadeSet(2, 0.25f);
    fadeCheck(1);
    return _menuPokemon.unk6;
}

static s32 _menuPokemonActionFieldItem(s8 index)
{
    u16 out;
    s32 result;
    _menuPokemon.unk18 = 3;
    result = menuOpen(0x5D, 1);
    menuClose(0x5D);
    switch (result) {
    case 0: {
        u16 item;
        u8 slot;
        menuClose(0x4C);
        item = menuPocket2Call(2, 0, 0);
        slot = menuPocket2GetLastSlotID();
        _menuPokemonOpenList(0);
        if (item == 0) {
            return -1;
        }
        _menuPokemonActionGive(index, slot, item, &out);
        result = 0;
        break;
    }
    case 1:
        _menuPokemonActionGive(index, -1, 0, &out);
        result = 0;
        break;
    case 2:
    case -1:
        result = -1;
        break;
    }
    return result;
}

static u8 _menuPokemonMovePanel(long index, u8 mode)
{
    s16 x;
    s16 y;
    s16 id = menu_info[(s8)_menuPokemon.unk4].e[index].id;
    menuDataBiosGetXY(id, &x, &y);
    switch (mode) {
    case 0:
        winSeqSetMenu(id, x > 250 ? 0x98 : 0xA0);
        break;
    case 1:
        winSeqSetMenu(id, x > 250 ? 0x9C : 0xA4);
        break;
    case 2:
        return winSeqCheckMove(id);
    }
    return 1;
}

static s32 _menuPokemonActionField(signed char index)
{
    s32 command;
    long target;
    Pokemon *from;
    Pokemon *to;

    for (;;) {
        _menuPokemon.unk18 = 1;

        command = GSflagGet(0x30D) == 0 ? fieldMenuOpenClose(79)
                                            : fieldMenuOpenClose(90);

        switch (command) {
        case 367:
        case 429:
            index = _menuPokemonActionStatus(index, 1);
            command = 0;
            break;

        case 369:
        case 431: {
            _menuPokemon.unk8 = index;
            _menuPokemon.unk18 = 2;
            target = _menuPokemonOpenList(1);
            _menuPokemon.unk8 = -1;

            if (((s32 (*)(s32))menuGetCursorItemID)(76) != 355 && target != -1) {
                from = _menuPokemonGetPokemonPtr((u16)index);
                to = _menuPokemonGetPokemonPtr((u16)target);

                if (from != 0 && from != 0) {
                    _menuPokemonMovePanel(index, 1);
                    _menuPokemonMovePanel(target, 1);

                    while (_menuPokemonMovePanel(index, 2) != 0)
                        GSthreadSwitch();

                    pokemonReplace(from, to);
                    menuPokemonUpdate();
                    menuSubSleep(0.25f);

                    _menuPokemonMovePanel(index, 0);
                    _menuPokemonMovePanel(target, 0);

                    while (_menuPokemonMovePanel(index, 2) != 0)
                        GSthreadSwitch();
                }
            }

            command = -1;
            break;
        }

        case 371:
            command = _menuPokemonActionFieldItem(index);
            command = command == -1 ? 0 : -1;
            break;

        case -1:
        case 373:
        case 433:
            command = -1;
            break;
        }

        if (command == -1)
            break;
    }

    return 0;
}

static s32 _menuPokemonActionFight(s8 index)
{
    s32 result;
    _menuPokemon.unk18 = 1;
loop:
    if (_menuPokemon.unk19 != 0) {
        result = menuOpen(0x50, 1);
        menuClose(0x50);
    } else {
        result = menuOpen(0x51, 1);
        menuClose(0x51);
    }
    switch (result) {
    case 0:
        if (menuPokemonCheckPokemonChange(_menuPokemon.unk1C, _menuPokemon.unk10, index) != 0) {
            result = -1;
        } else {
            result = 1;
        }
        break;
    case 1:
        index = _menuPokemonActionStatus(index, 0);
        goto loop;
    case -1:
    case 2:
        result = 1;
        break;
    }
    return result;
}

static s32 _menuPokemonActionGive(s8 index, short slot, u16 item, u16* out)
{
    s32 answer;
    u16 held;
    Pokemon* pokemon=_menuPokemonGetPokemonPtr(index);
    msgctrlSetValue(0x32,&_menuPokemonStatusAll[(s8)_menuPokemon.unk6]);
    held=pokemonGetSoubiItemDataId(pokemon);
    Hero* hero=_menuPokemonGetHeroPtr();
    if(hero==0) return -1;
    if(item==0) {
        if(held!=0) {
            if(heroItemCheckAddItemDataId(hero,held)<=0) winMsgOpen(2,0x3ACF,1,1);
            else {
                heroItemAddItemDataId(hero,held,1,-1);
                u16 removed=pokemonDoItemSoubi(pokemon,0,0);
                if(out) *out=removed;
                msgctrlSetValue(0x2D,(void*)removed);
                winMsgOpen(2,0x3ACD,1,1);
            }
        } else winMsgOpen(2,0x3ACE,1,1);
    } else if(held!=0) {
        msgctrlSetValue(0x2D,(void*)held);
        winMsgOpen(2,0x3ACA,1,0);
        answer=menuSubOpenYesNo(0,-1,-1,0);
        winMsgClose(1);
        if(answer!=0) return -1;
        if(heroItemDecItemDataId(hero,item,1,slot)!=0) winMsgOpen(2,0x3ACF,1,1);
        else if(heroItemCheckAddItemDataId(hero,held)<=0) {
            heroItemAddItemDataId(hero,item,1,-1);
            winMsgOpen(2,0x3ACF,1,1);
        } else {
            heroItemAddItemDataId(hero,held,1,-1);
            u16 removed=pokemonDoItemSoubi(pokemon,0,0);
            if(out) *out=removed;
            pokemonDoItemSoubi(pokemon,item,1);
            msgctrlSetValue(0x2D,(void*)removed);
            msgctrlSetValue(0x2E,(void*)item);
            winMsgOpen(2,0x3ACB,1,0);
        }
    } else if(heroItemDecItemDataId(hero,item,1,slot)==0) {
        pokemonDoItemSoubi(pokemon,item,1);
        msgctrlSetValue(0x2D,(void*)item);
        winMsgOpen(2,0x3ACC,1,0);
    }
    winMsgClose(1);
    menuPokemonUpdate();
    return -1;
}

static Pokemon* _menuPokemonCbLoadPokemonList(void *arg)
{
    u16 *counter = (u16 *)arg;
    Pokemon *p = _menuPokemonGetPokemonPtr(*counter);
    *counter += 1;
    return p;
}

s32 menuPokemonMain(void)
{
    menuOffScreenSetPriority(0);
    _menuPokemonSub(_menuPokemon.unk0, _menuPokemon.unk16, _menuPokemon.unk10);
    menuPokemonClose();
    menuOffScreenSetPriority(1);
    return 0;
}

void menuPokemonOpen(u8 mode, u16 c, FIGHT_TRAINER *t)
{
    _menuPokemon.unk4 = 1;
    _menuPokemonOpen(mode, 0, 0, c, t, 1);
}

void menuPokemonOpenFight(u8 flag, u8 b, FIGHT_TRAINER *c, void *d)
{
    if (flag == 1) {
        _menuPokemon.unk4 = 0;
    } else {
        _menuPokemon.unk4 = 1;
    }
    _menuPokemon.unk1C = d;
    _menuPokemonOpen(2, 0, 0, b, c, 1);
}

void menuPokemonOpenItemUse(u8 mode, bool flag, u16 c, FIGHT_TRAINER *t)
{
    _menuPokemon.unk4 = 1;
    _menuPokemonOpen(mode, 0, 0, c, t, flag);
}

void menuPokemonOpenItemGive(u8 a, u8 b, u16 c, FIGHT_TRAINER *t)
{
    _menuPokemon.unk4 = 1;
    _menuPokemonOpen(5, a, b, c, t, 1);
}

static s32 _menuPokemonOpen(u8 mode, u8 a, u8 b, u16 c, FIGHT_TRAINER *trainer, bool flag)
{
    _menuPokemon.unk0 = mode;
    _menuPokemon.unk14 = a;
    _menuPokemon.unk15 = b;
    _menuPokemon.unk16 = c;
    _menuPokemon.unk10 = trainer;
    _menuPokemon.unk1 = flag;
    _menuPokemon.unk20 = 0;
    _menuPokemon.unk19 = 1;
    _menuPokemon.unk24 = 0;
    switch (mode) {
    case 2:
    case 4:
        _menuPokemon.unkC = 1;
        break;
    case 3:
    default:
        _menuPokemon.unkC = 0;
        break;
    }
    switch (_menuPokemon.unk0) {
    case 3:
    case 4:
    case 5:
        menuOffScreenSetPriority(0);
        _menuPokemon.unk2 = 0;
        _menuPokemon.unk3 = 0;
        break;
    case 1:
        _menuPokemon.unk2 = 1;
        _menuPokemon.unk3 = 0;
        break;
    case 2:
        _menuPokemon.unk2 = 1;
        _menuPokemon.unk3 = 1;
        if (c == 0) {
            _menuPokemon.unk19 = 0;
        }
    case 6:
    case 7:
    case 8:
    default: {
        menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
        while (menuGetOffScreenFlag() == 0) {
            GSthreadSwitch();
        }
        _menuPokemon.unk2 = 1;
        _menuPokemon.unk3 = 2;
        break;
    }
    }
    if (_menuPokemon.unk2 == 1) {
        GSfloorPush(0x3A5);
        if (_menuPokemon.unk3 != 1) {
            floorSetFadeScript(0, 0);
        }
        floorWaitForChange();
        if (_menuPokemon.unk3 == 2) {
            menuReleaseOffScreen(20.0f / GSgfxVideoGetVsyncRate());
        }
    } else {
        _menuPokemonSub(mode, c, trainer);
    }
    switch (_menuPokemon.unk0) {
    case 3:
    case 4:
    case 5:
        menuOffScreenSetPriority(1);
        break;
    }
    _menuPokemon.unk4 = 1;
    return _menuPokemon.unk20;
}

static s32 _menuPokemonSub(u8 mode,u32 a,FIGHT_TRAINER* trainer) {
    s32 result;
    (*(s8*)&_menuPokemon.unk6)=_menuPokemon.unk7;
    if((s8)(*(s8*)&_menuPokemon.unk6)<0)(*(s8*)&_menuPokemon.unk6)=0;
    _menuPokemon.unk8=-1;
    if(!_menuPokemon.unk1)(*(s8*)&_menuPokemon.unk6)=-1;
    menuPokemonUpdate();
    pokemonFaceLoadCnt$2268=0;
    menuFaceLoad(0,_menuPokemonCbLoadPokemonList,&pokemonFaceLoadCnt$2268);
    u16 quantity=0;
    for(;quantity<6;quantity++) {if(!_menuPokemonGetPokemonPtr(quantity))break;}
    if(quantity<=(s8)(*(s8*)&_menuPokemon.unk6))(*(s8*)&_menuPokemon.unk6)=(s8)(quantity-1);
    for(;;) {
        _menuPokemon.unk18=0;
        s8 selected=_menuPokemonOpenList(true);
        (*(s8*)&_menuPokemon.unk6)=selected;
        if(selected==-2)break;
        if(((s32 (*)(s32))menuGetCursorItemID)(0x4C)==0x163 || selected==-1) {(*(s8*)&_menuPokemon.unk6)=-1;break;}
        switch(_menuPokemon.unk0) {
        case 1:result=_menuPokemonActionField(selected);break;
        case 2:result=_menuPokemonActionFight(selected);break;
        case 3:case 4:case 8:result=-1;break;
        case 5: {u16 item;result=_menuPokemonActionGive(selected,_menuPokemon.unk15,_menuPokemon.unk16,&item);break;}
        case 6:result=-1;break;
        case 7: {
            Pokemon* pokemon=_menuPokemonGetPokemonPtr(selected);
            if(!pokemon)continue;
            if(!pokemonIsDarkPokemon(pokemon)) {winMsgOpen(2,0xC54C,1,0);winMsgClose(1);continue;}
            if(0.0f!=pokemonGetDp(pokemon)) {winMsgOpen(2,0xC54D,1,0);winMsgClose(1);continue;}
            result=-1;break;
        }
        default:break;
        }
        if(result<0)break;
    }
    while(menuFaceCheckLoading())GSthreadSwitch();
    _menuPokemon.unk20=(s8)(*(s8*)&_menuPokemon.unk6);
    return result;
}

void menuPokemonClose(void)
{
    menuCloseCustom(0x4C, 0, 1);
    if (_menuPokemon.unk2 != 0) {
        menuOffScreenSetPriority(1);
        GSfloorPop();
        if (_menuPokemon.unk3 != 1) {
            floorSetFadeScript(0, 0);
        }
        floorWaitForChange();
    }
}

s32 menuPokemonCtrl(tagWINDOW_WORK *window)
{
    MENU_POKEMON_STATUS_TBL *tbl = windowGetParam(window, 0);
    if (tbl == 0) {
        return 0;
    }
    menuOffScreenSetPriority(0);
    if (window->unk1 == 0) {
        window->unkA2 = -1;
        if (window->unk2 == 0) {
            s32 off;
            MENU_POKEMON_STATUS_TBL *entry = tbl;
            s32 k;
            for (k = 0, off = 0; k < 6; off += 8, entry++, k++) {
                MenuInfoEntry *e = (MenuInfoEntry *)((u8 *)&menu_info[(s8)_menuPokemon.unk4] + off);
                menuItemBiosSetXY(window->unk4, e->a, e->b, e->c);
                e = (MenuInfoEntry *)((u8 *)&menu_info[(s8)_menuPokemon.unk4] + off);
                menuDataBiosSetXY(e->id, e->b, e->c);
                menuOpenCustom(*(s16 *)((u8 *)&menu_info[(s8)_menuPokemon.unk4] + off), 0x4C, 0, 0, 0, 2, entry, k);
                _menuPokemonMovePanel(k, 0);
            }

            winSeqSetMenu(window->unk4, 1);
            window->unk2 = 1;
        }
        menuOffScreenSetPriority(0);
    } else if (window->unk1 == 3 && window->unk2 == 0) {
        s32 k = 0;
        do {
            _menuPokemonMovePanel(k, 1);
            k++;
        } while (k < 6);
        winSeqSetMenu(window->unk4, 7);
        window->unk2 = 1;
    }
    _menuPokemonTimer = (s32)(60.0f * timeGetLastFrameSec() + (f32)_menuPokemonTimer) % 1000;
    return 0;
}

void menuPokemonCursor(tagWINDOW_WORK *window)
{
    u8 enabled[8];
    u8 *p;
    s8 cur;
    s8 dir;
    int i;
    u16 keys;
    dir = 0;
    cur = window->unk9E;
    for (p = enabled, i = 0; i < 6; p++, i++) {
        if (_menuPokemonGetPokemonPtr(i) != 0) {
            *p = 1;
        } else {
            *p = 0;
        }
    }
    enabled[i] = 1;
    keys = windowGetKeyRepeat(enabled);
    if ((keys & 8) != 0) {
        dir = 1;
        if (_menuPokemon.unk4 == 0) {
            if (cur == 0) {
                if (_menuPokemon.unk5 == 3) {
                    cur = _menuPokemon.unk5;
                } else {
                    cur = 2;
                }
            }
        } else if (cur == 0) {
            if (_menuPokemon.unk5 == 3) {
                cur = _menuPokemon.unk5;
            } else {
                cur = 2;
            }
        } else if (cur == 1) {
            if (_menuPokemon.unk5 == 5) {
                cur = _menuPokemon.unk5;
            } else {
                cur = 4;
            }
        }
    } else if ((keys & 4) != 0) {
        dir = -1;
        if (_menuPokemon.unk4 == 0) {
            switch (cur) {
            case 1: case 2: case 3: case 4: case 5:
                cur = 0;
                break;
            }
        } else if (_menuPokemon.unk4 == 1) {
            switch (cur) {
            case 2: case 3:
                cur = 0;
                break;
            case 4: case 5:
                cur = 1;
                break;
            }
        }
    }
    if ((keys & 1) != 0) {
        cur -= 1;
        dir = -1;
        if (cur < 0) {
            cur = 6;
        }
    } else if ((keys & 2) != 0) {
        dir = 1;
        if (++cur >= menuDataBiosGetDispMax(window->unk4)) {
            cur = 0;
        }
    }
    if (dir != 0) {
        u8 *q = &enabled[cur];
        while (*q == 0) {
            cur += dir;
            q += dir;
            if (cur < 0 || cur >= 7) {
                cur = 7;
                break;
            }
        }
    }
    if (window->unk9E != cur) {
        _menuPokemon.unk5 = (s8)window->unk9E;
        _menuPokemon.unk6 = cur;
        _menuPokemon.unk7 = cur;
        window->unk9E = cur;
    }
}

void menuPokemonButton(tagWINDOW_WORK *window)
{
    u8 flag = 0;
    if (_menuPokemon.unk1 == 0) {
        window->unkA4 = 1;
        return;
    }
    if (winSeqCheckMove(0x4B) == 0) {
        u16 key = windowGetKeyTrg();
        if ((key & 0x10) != 0) {
            if (menuGetCursorItemID(window->unk4) == 0x162) {
                flag = 1;
            }
        } else if ((key & 0x20) != 0) {
            flag = 1;
        }
        if (flag != 0) {
            if (_menuPokemon.unk19 == 0) {
                GSsndPlayNow(0x13);
                return;
            }
            window->unkA4 = 1;
            window->unkA5 = 1;
            return;
        }
        menuButtonNormal(window);
    }
}

void menuPokemonDrawHelp(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    u32 msg = 0;
    switch (_menuPokemon.unk18) {
    case 0:
        switch (_menuPokemon.unk0) {
        case 8:
            msg = 0x3AC7;
            break;
        case 3:
        case 4:
            itemDataBiosGetPtr(_menuPokemon.unk16);
            if (itemDataBiosGetKind() == 4) {
                msg = 0x3AC7;
            } else if (_menuPokemon.unk24 != 0) {
                msg = 0x3C3A;
            } else {
                msg = 0x3AC5;
            }
            break;
        case 5:
            msg = 0x3AC6;
            break;
        case 1:
        case 2:
        default:
            msg = 0x3AC1;
            break;
        }
        break;
    case 1:
        msgctrlSetValue(0x32, &_menuPokemonStatusAll[(s8)_menuPokemon.unk6]);
        msg = 0x3AC2;
        break;
    case 2:
        msg = 0x3AC3;
        break;
    case 3:
        msg = 0x3AC4;
        break;
    }
    if (msg != 0) {
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, window->unk93 | 0xFFFFFF00, msg);
    }
}

static int _menuPokemonCheckItem(tagSPRITE_WORK *sprite, s8 kind)
{
    int enable = 1;
    s32 color = -1;
    if (kind == -1) {
        switch (sprite->unk6) {
        case 0x131:
        case 0x133:
        case 0x135:
        case 0x136:
        case 0x137:
        case 0x138:
        case 0x139:
        case 0x13A:
        case 0x13B:
        case 0x13E:
        case 0x140:
        case 0x141:
        case 0x142:
        case 0x143:
        case 0x144:
        case 0x145:
        case 0x146:
        case 0x2DD:
            enable = 0;
            break;
        }
    } else if (kind == 1) {
        switch (sprite->unk6) {
        case 0x131:
        case 0x132:
        case 0x13C:
        case 0x13D:
        case 0x1C4:
        case 0x2CF:
        case 0x2D0:
        case 0x2DD:
            color = 0x808080FF;
            break;
        }
    }
    winSpriteSetDisp(sprite, enable);
    sprite->unk64 = color;
    return enable;
}

void menuPokemonDrawCur(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    winSpriteSetDisp(sprite, 0);
    switch (menuGetCursor(window->unk4)) {
    case 0:
        switch (sprite->unk6) {
        case 0x16E:
        case 0x191:
        case 0x1A8:
        case 0x1AC:
        case 0x1BB:
            winSpriteSetDisp(sprite, 1);
            return;
        }
        break;
    case 1:
        switch (sprite->unk6) {
        case 0x170:
        case 0x183:
        case 0x193:
        case 0x1AE:
        case 0x1BD:
            winSpriteSetDisp(sprite, 1);
            return;
        }
        break;
    case 2:
        switch (sprite->unk6) {
        case 0x172:
        case 0x195:
        case 0x1AA:
        case 0x1B0:
        case 0x1BF:
            winSpriteSetDisp(sprite, 1);
            return;
        }
        break;
    case 3:
        switch (sprite->unk6) {
        case 0x174:
            winSpriteSetDisp(sprite, 1);
            return;
        }
        break;
    }
}

extern "C" void menuPokemonDrawItem(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite)
{
    Pokemon *pokemon;
    s16 loopIndex;
    s16 width;
    s16 gaugeWidth;
    s16 tutorIndex;
    u16 gauge;
    u32 moveId;
    u32 sexId;
    MENU_POKEMON_STATUS_TBL *info = (MENU_POKEMON_STATUS_TBL *)windowGetParam(win, 0);
    sexId = 0;
    u32 color;
    s32 item;
    u32 msgId;
    u16 partyIndex;
    s8 panelState;
    u8 machineNo;

    pokemon = 0;
    panelState = 0;

    if (info == 0)
        return;

    if (info->unk0 == 0)
        panelState = -1;
    else if (info->unk1A == 0)
        panelState = 1;

    if ((u8)_menuPokemonCheckItem(sprite, panelState) == 0)
        return;

    color = menuSubCalcColor(win, sprite);
    partyIndex = (u16)windowGetParam(win, 1);

    if (_menuPokemon.unk0 == 3 || _menuPokemon.unk0 == 4) {
        item = itemDataBiosGetPtr(_menuPokemon.unk16);

        if (((u8 (*)(s32))itemDataBiosGetKind)(item) == 4) {
            switch (sprite->unk6) {
            case 311:
            case 322: {
                machineNo = itemDataBiosGetWazaMachineNo(item);

                pokemon = _menuPokemonGetPokemonPtr(partyIndex);

                if (pokemonIsDarkPokemon(pokemon) != 0) {
                    msgId = 15049;
                } else {
                    void *stats = pokemonDataBiosGetPtr(
                        pokemonBiosGetPokemonDataId(pokemon));

                    if (((u8 (*)(void*,u16))pokemonDataBiosGetWazaMcn)(stats, machineNo) == 0) {
                        msgId = 15049;
                    } else {
                        u16 wazaId = itemDataBiosGetWazaIDByWazaMachineNo(machineNo);

                        for (loopIndex = 0; loopIndex < 4; loopIndex++) {
                            if ((u16)pokemonBiosGetPokemonWazaDataId(pokemon, loopIndex) == wazaId)
                                break;
                        }

                        if (loopIndex < 4)
                            msgId = 15420;
                        else
                            msgId = 15048;
                    }
                }

                GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, -4, color, msgId);
            }
            case 312:
            case 323:
                winSpriteSetDisp(sprite, 0);
                return;
            }

            /* the remaining sprites draw their panel element below */
        }
    } else if (_menuPokemon.unk0 == 8) {
        switch (sprite->unk6) {
        case 311:
        case 322: {
            pokemon = _menuPokemonGetPokemonPtr(partyIndex);

            if (pokemonIsDarkPokemon(pokemon) != 0) {
                msgId = 15049;
            } else if (pokemonDB_GetTeachWaza(
                           pokemonBiosGetPokemonDataId(pokemon), _menuPokemon.unk16) == 0) {
                msgId = 15049;
            } else {
                u8 order[12] = {7, 10, 2, 0, 5, 1, 4, 3, 6, 9, 11, 8};
                moveId = wazaoshie_data[order[_menuPokemon.unk16]].move;
                for (tutorIndex = 0; tutorIndex < 4; tutorIndex++) {
                    if ((u16)pokemonBiosGetPokemonWazaDataId(pokemon, tutorIndex) == moveId)
                        break;
                }

                if (tutorIndex < 4)
                    msgId = 15420;
                else
                    msgId = 15048;
            }

            GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, -4, color, msgId);
        }
        case 312:
        case 323:
            winSpriteSetDisp(sprite, 0);
            return;
        }
    }

    switch (sprite->unk6) {
    case 306:
    case 316:
        if (info->state == 0)
            winSpriteSetDisp(sprite, 1);
        else
            winSpriteSetDisp(sprite, 0);
        return;

    case 317:
    case 452:
        if (info->state == 1)
            winSpriteSetDisp(sprite, 1);
        else
            winSpriteSetDisp(sprite, 0);
        return;

    case 719:
    case 720:
        if (info->state == 2)
            winSpriteSetDisp(sprite, 1);
        else
            winSpriteSetDisp(sprite, 0);
        return;

    case 315:
    case 326:
        if (info->unk24 != 0)
            windowDrawSprite2(0, 0, sprite->width, sprite->height, color, win,
                                    info->unk24, 0, winSpriteGetLayerID(win, sprite));
        return;

    case 314:
    case 325:
        if (info->item != 0)
            winSpriteSetDisp(sprite, 1);
        else
            winSpriteSetDisp(sprite, 0);
        return;

    case 310:
    case 321:
        GSmsgPrint2(winSpriteGetLayerID(win, sprite), 44, 0, color, 15080);
        ((void (*)(s32,u32))msgctrlSetValue)(0x5F, info->unk1A);
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, 42, sprite->height, color,
                    17239);
        ((void (*)(s32,u32))msgctrlSetValue)(0x5F, info->hpMax);
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->width - 2, sprite->height,
                    color, 17239);
        return;

    case 309:
    case 320:
        ((void (*)(s32,u32))msgctrlSetValue)(0x5F, info->level);
        GSmsgPrintRect(winSpriteGetLayerID(win, sprite), 0, 0, sprite->width, sprite->height, color,
                    0x4351);
        return;

    case 307:
    case 318: {
        ((void (*)(s32,u32))msgctrlSetValue)(0x37, (u32)info);
        GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, 0, color, 0x4277);
        width = (s16)((GSmsgGetRect(0x4277) >> 16) + 4);

        switch (info->sex) {
        case 0:
            sexId = 0x9C5;
            break;
        case 1:
            sexId = 0x9C6;
            break;
        case 2:
            sexId = 0;
            break;
        }

        if (sexId != 0) {
            ((void (*)(s32,u32))msgctrlSetValue)(0x37, (u32)GSmsgGetGSchar(sexId));
            GSmsgPrint2(winSpriteGetLayerID(win, sprite), width - 2, 0, color, 0x4276);
        }
        return;
    }

    case 305:
    case 733:
        menuFaceDispFromID(win, sprite, info->faceId);
        return;

    case 312:
    case 323: {
        s16 maxHp = info->hpMax;

        if (info->unk1A <= 0)
            gauge = 0;
        else if (info->unk1A <= (maxHp * 20) / 100)
            gauge = 245;
        else if (info->unk1A <= (maxHp * 50) / 100)
            gauge = 244;
        else
            gauge = 243;

        {
            gaugeWidth = (info->unk1A * sprite->width + (maxHp - 1)) / maxHp;

            if (gauge == 0)
                return;

            windowDrawSprite2(0, 0, gaugeWidth, sprite->height, color, win, gauge, 0,
                                    winSpriteGetLayerID(win, sprite));
        }
        return;
    }

    case 352:
    case 353: {
        s32 windowId;
        s32 slot = _menuPokemon.unk8;

        if (slot >= 0 && slot < 6)
            windowId = menu_info[_menuPokemon.unk4].e[slot].id;
        else
            windowId = 0;

        if (windowId == win->unk4) {
            s32 phase = _menuPokemonTimer % 60;

            sprite->unk64 = 0xFFFF00FF;
            if (phase < 30) {
                f32 t = sin(3.14f * ((f32)phase / 30.0f));

                sprite->channels.a -= (u8)(128.0f * t);
            }
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        return;
    }

    case 342:
    case 343: {
        s32 windowId;
        s32 cursor = _menuPokemon.unk6;

        if (cursor >= 0 && cursor < 6)
            windowId = menu_info[_menuPokemon.unk4].e[cursor].id;
        else
            windowId = 0;

        if (windowId == win->unk4) {
            s32 phase = _menuPokemonTimer % 60;

            sprite->unk64 = -1;
            if (phase < 30) {
                f32 t = sin(3.14f * ((f32)phase / 30.0f));

                sprite->channels.a -= (u8)(128.0f * t);
            }
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        return;
    }

    case 354:
        if (_menuPokemon.unk6 == 6)
            winSpriteSetDisp(sprite, 1);
        else
            winSpriteSetDisp(sprite, 0);
        return;

    case 355:
    case 356:
        switch (_menuPokemon.unk18) {
        case 0:
        case 2:
            winSpriteSetDisp(sprite, 1);

            if (sprite->unk6 == 356) {
                s32 msgId;
                s32 msgSize;

                if (_menuPokemon.unk0 == 7 || _menuPokemon.unk0 == 6)
                    msgId = 15284;
                else
                    msgId = 15422;

                msgSize = GSmsgGetRect(msgId) >> 16;
                GSmsgPrint2(winSpriteGetLayerID(win, sprite), (sprite->width - msgSize) / 2, 0,
                            win->unk93 | 0xFFFFFF00, msgId);
            }
            break;

        case 1:
        case 3:
            winSpriteSetDisp(sprite, 0);
            break;
        }
        return;
    }
}

static Pokemon* _menuPokemonStatusCB(Pokemon *pokemon, MENU_POKEMON_CB_TYPE type, long arg)
{
    s8 next = _menuPokemon.unk6;
    u8 cur = _menuPokemon.unk6;
    switch (type) {
    case MENU_POKEMON_CB_PREV:
        next--;
        break;
    case MENU_POKEMON_CB_NEXT:
        next++;
        break;
    default:
        return pokemon;
    }
    if ((s8)next >= 6) {
        next = 5;
    }
    if ((s8)next < 0) {
        next = 0;
    }
    if ((s8)next != (s8)cur) {
        Pokemon *p = _menuPokemonGetPokemonPtr((s8)next);
        if (p != 0) {
            pokemon = p;
            _menuPokemon.unk6 = next;
        }
    }
    return pokemon;
}

s32 menuPokemonOpenWazaLight(s8 index)
{

    s32 selected;
    u32 moveIds[4];
    u32 *dst;
    s32 count;
    Pokemon *pokemon = _menuPokemonGetPokemonPtr((u16)index);
    s32 i;

    if (pokemon == 0)
        return -1;

    pokemonToMenuWazaStatus(pokemon, (PokemonMenuWazaStatus*)wazaStatus$2693);

    i = count = 0;
    dst = moveIds + i;
    while (i < 4) {
        s32 id = ((s32 (*)(Pokemon*,u16,s32,u16))pokemonGetStatus)(pokemon, 0, 127, i);

        if ((u16)id != 0) {
            *dst = wazaGetStatus(0, (u16)id, 1, 0);
            count++;
        }

        dst++;
        i++;
    }

    menuOffScreenSetPriority(0);
    _menuPokemon.unk24 = 1;
    selected = menuSubOpenSelect2(0, (s32*)moveIds, count, 445 - lbl_804E7EB8, lbl_804E7EBC + 300,
                                  0, count, 0);
    _menuPokemon.unk24 = 0;
    menuOffScreenSetPriority(1);
    return selected;
}

void menuPokemonCloseWazaLight(void)
{
    menuCloseCustom(0x12, 0, 1);
}

s32 menuPokemonCtrlWaza(void)
{
    return 0;
}

void menuPokemonInitWork(void)
{
    memset(&_menuPokemon, 0, 0x28);
}
