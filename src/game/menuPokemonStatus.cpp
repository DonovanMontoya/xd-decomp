#pragma defer_codegen on
#pragma force_active on
#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/menuPokemonStatusLayout.hpp>

extern "C" {
s32 GScharCmp(u8*, u8*);
u32 GSflagGet(s32);
u8* GSmsgGetGSchar(s32);
u32 fightFloorGetGcHeroFightTrainerPtr(s32);
Hero* fightTrainerBiosGetHeroPtr(FIGHT_TRAINER*);
u32 gamedataGetStatus(s32, s32);
u8* heroBiosGetNamePtr(Hero*);
u32 heroBiosGetRnd(Hero*);
Hero* menuCBBios_GetRegisteredHero(void);
s32 pokemonGetStatus(Pokemon*, u16, u16, u16);
bool pokemonCheckValid(Pokemon*);
u32 windowGetKeyTrg(void);
void pokemonWazaReplace(Pokemon*, s32, s32);
s32 menuIsCheck(s32);
void menuSetDisp(s32, s32);
bool menuFaceCheckLoading(void);
void GSthreadSwitch(void);
void GSfloorPush(s32);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void menuOpen(s32, s32);
void menuClose(s32);
void* memset(void*, int, u32);
void menuDrawReliveUpdate(void);
Pokemon* heroBiosGetPokemonPtr(Hero*, u16);
void fadeCheck(s32);
void fadeSet(s32, f32);
void GSfloorPop(void);
void GSsndPlayNow(s32);
void menuModelInit(void*, s16, s16);
void menuModelFree(void*);
void menuModelTerm(void*);
void menuModelLoadPokemon(void*, Pokemon*);
void menuOffScreenSetPriority(s32);
s32 menuOpenCustom(s32, s32, ...);
void menuCloseCustom(s32, s32, s32);
s32 wazaGetStatus(s32, u16, s32, s32);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
struct MenuItemRect {
    u8 reserved0[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};
MenuItemRect* menuItemBiosGetPtr(s32, s32);
bool pokemonWazaCheckValid(Pokemon*, u16);
void* savedataGetStatus(s32, s32);
u16 zokuseiBiosGetSpriteID(u16);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
tagWINDOW_WORK* windowSearchID(s32);
u32 getRibbonCnt(void);
u8 exribbonGetNo(s32);
u32 getRibbonMsgID(s32);
void msgctrlSetValue(s32, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
void windowDrawSprite(s16, s16, tagWINDOW_WORK*, s32, s32, s32);
u16 windowGetKeyRepeat(void);
void* pokemonDataBiosGetPtr(u16);
u8 pokemonIsDarkPokemon(Pokemon*);
void menuModelSetSize(void*, s16, s16, s16, s16);
bool menuModelCheck(void*, s32);
void menuModelAdjustCamera(void*);
void menuModelSetAngle(void*, f32*);
void menuModelRender(void*);
u8 pokemonBiosGetCatchBallId(Pokemon*);
u16 mballBiosGetSpriteID(u16);
void windowDrawSprite2(s16, s16, s16, s16, s32, tagWINDOW_WORK*, u16, u32, s32);
s32 menuPokemonGetJoutaiSpriteID(Pokemon*, s32);
u16 pokemonGetSoubiItemDataId(Pokemon*);
u32 pokemonCheckRare(Pokemon*);
s32 menuSubGetPokemonSexForDisp(Pokemon*);
u32 GSmsgGetRect(u32);
u8 wazaDB_GetCompatible(u32);
u16 zokuseiBiosGetWazaJoutai(u16, u16);
u8 pokemonWazaGetMaxPP(Pokemon*, u16);
void GSmsgPrintRight(s32, s32, s32, s32, s32, u32, u32);
u8 pokemonGetDarkPokemonLevel(Pokemon*);
void* pokemonSeikakuDataBiosGetPtr(u32);
u32 pokemonSeikakuDataBiosGetName(void*);
u32 floorGetPlaceName(u32);
u8 fightKind_CheckFightKind(s32);
u32 pokemonGetLevelToExp(Pokemon*, u8);
u32 pokemonGetTokuseiDataId(Pokemon*);
void* pokemonTokuseiDataBiosGetPtr(u16);
void* pokemonTokuseiDataBiosGetDoc(void*);
void* pokemonTokuseiDataBiosGetName(void*);
void menuDrawReliveMeter(Pokemon*, s32, s32, s32);
u8 pokemonDataBiosGetZokuseiDataId(void*, s32);
u32 zokuseiGetPokemonSpriteID(void*, u16);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void menuPlaySe(s32, s32);
u8 menuModelComparePokemon(void*, Pokemon*);
}

static MenuPokemonStatus _menuStatus;
static u8 _menuModel[0xEC];

void _menuPokemonStatusMakeRibbon(Pokemon*, RIBBON_WORK*);
static s32 _menuPokemonStatusSub(u8, FIGHT_TRAINER*, Pokemon*, u16, MenuPokemonStatusCb, long);
static s32 _menuPokemonStatusChangeSubMenu(CURSOR);
static s32 _menuPokemonStatusOpen(u8, FIGHT_TRAINER*, Pokemon*, u16, MenuPokemonStatusCb, long);
extern "C" void menuPokemonStatusClose(void);

static s32 NotDarkWaza(long id);

static u16 _menuPokemonStatusGetZokuseiSpriteID(u16 id);

extern "C" void menuPokemonStatusChangeColor(void);

u16 _menuPokemonStatusGetWazaDataID(Pokemon* pokemon, u16 index);

u8 _menuPokemonStatusCheckDanny(Pokemon* pokemon);

u8 _menuPokemonStatusCheckGinzaru(Pokemon* pokemon);

s32 _menuPokemonStatusCheckWazaItem(tagWINDOW_WORK*, tagSPRITE_WORK* spr);

u8 _menuPokemonStatusCheckOya(Pokemon* pokemon);

extern "C" {

void menuPokemonStatusCtrlRibbon(void);

}

static s32 ribbon_id_tbl[32] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6
};
static u32 ex_ribbon_id[64] = {
11026, 11027, 11028, 11029, 11030, 11031, 11032, 11033, 11034, 11035, 11036, 11037, 11038, 11039, 11040, 11041, 11042, 11043, 11044, 11045, 11046, 11047, 11048, 11049, 11050, 11051, 11052, 11053, 11054, 11055, 11056, 11057, 11058, 11059, 11060, 11061, 11062, 11063, 11064, 11065, 11066, 11067, 11068, 11069, 11070, 11071, 11072, 11073, 11074, 11075, 11076, 11077, 11078, 11079, 11080, 11081, 11082, 11083, 11084, 11085, 11086, 11087, 11088, 11089
};

extern "C" void menuPokemonStatusDrawRibbon(tagWINDOW_WORK* win, tagSPRITE_WORK* spr);

struct RibbonMap {
    u16 id;
    u8 base;
    u8 max;
};

void _menuPokemonStatusMakeRibbon(Pokemon *pokemon, RIBBON_WORK *work);

static s32 _menuPokemonStatusSub(u8, FIGHT_TRAINER*, Pokemon* pokemon, u16, MenuPokemonStatusCb, long);

extern "C" void menuPokemonStatusClose(void);

static s32 _menuPokemonStatusChangeSubMenu(CURSOR cursor);

extern "C" s32 menuPokemonStatusCtrl(tagWINDOW_WORK* win);

static s32 _menuPokemonStatusOpen(u8 flags, FIGHT_TRAINER* trainer, Pokemon* pokemon, u16 wazaId, MenuPokemonStatusCb callback, long arg);

extern "C" {

s32 menuPokemonStatusOpenWazaLearn(Pokemon* pokemon, u16 wazaId);

s32 menuPokemonStatusOpenWazaLearnList(Pokemon* pokemon, u16 wazaId);

s32 menuPokemonStatusOpenWazaMachine(Pokemon* pokemon, u16 wazaId);

s32 menuPokemonStatusOpenFromPokemonChange(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg);

s32 menuPokemonStatusOpenFromPcBox(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg);

s32 menuPokemonStatusOpenFieldMenu(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg);

s32 menuPokemonStatusOpenFightMenu(FIGHT_TRAINER* trainer, Pokemon* pokemon, MenuPokemonStatusCb callback, long arg);

void menuPokemonStatus(void);

s32 menuPokemonStatusOpenWazaList(u8 index);

}

static inline void _drawWazaSprite(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, s32 id) {
    windowDrawSprite(0, 0, win, id, 0, winSpriteGetLayerID(win, spr));
}

static inline u16 menuPokemonStatusGetWazaId(Pokemon *pokemon, u16 slot)
{
    return _menuPokemonStatusGetWazaDataID(pokemon, slot);
}

// Message id of the type icon the waza page draws for the move in `slot`, or 0
// when the move is one a dark pokemon hides. A move the pokemon has not seen
// yet is flagged as it draws.
static inline u32 menuPokemonStatusGetSlotIcon(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite,
                                               Pokemon *pokemon, u16 slot)
{
    u16 waza = menuPokemonStatusGetWazaId(pokemon, slot);
    u32 icon;

    switch ((s32)NotDarkWaza((u16)waza)) {
    case 0:
        return 0;
    case 374:
        return 123;
    default:
        break;
    }
    icon = _menuPokemonStatusGetZokuseiSpriteID((u16)((s32 (*)(s32,u16,u16,s32))wazaGetStatus)(0, waza, 3, 0));
    if (_menuStatus.wazaNew[slot] != 0 && slot != 0) {
        ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(7, 0x14, window, 0xF8, 0, winSpriteGetLayerID(window, sprite));
        pokemon->getDarkPokemon()->setWazaNew(slot - 1, 1);
    }
    return icon;
}

// Waza page of the status menu: draws the waza row of the grid and the waza
// slot the cursor stands on. Every sprite of the waza page runs through this
// hook, selected by the item id of the sprite.
extern "C" void menuPokemonStatusDrawWaza(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite);

inline u32 dispSummaryPlaceName(u32 place)
{
    return floorGetPlaceName(place);
}
extern "C" void menuPokemonStatusDrawStatus(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite);

extern "C" void menuPokemonStatusDrawTitle(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite);

extern "C" void menuPokemonStatusCursor(tagWINDOW_WORK* win);

extern "C" void menuPokemonStatusButton(tagWINDOW_WORK* win);


s32 menuPokemonStatusOpenFieldMenu(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg) {
    return _menuPokemonStatusOpen(0x8E, 0, pokemon, 0, callback, arg);
}

s32 menuPokemonStatusOpenFightMenu(FIGHT_TRAINER* trainer, Pokemon* pokemon, MenuPokemonStatusCb callback, long arg) {
    return _menuPokemonStatusOpen(0xAC, trainer, pokemon, 0, callback, arg);
}

s32 menuPokemonStatusOpenFromPcBox(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg) {
    return _menuPokemonStatusOpen(0xE, 0, pokemon, 0, callback, arg);
}

s32 menuPokemonStatusOpenFromPokemonChange(Pokemon* pokemon, MenuPokemonStatusCb callback, long arg) {
    return _menuPokemonStatusOpen(0xC, 0, pokemon, 0, callback, arg);
}

s32 menuPokemonStatusOpenWazaList(u8 index) {
    Pokemon* pokemon = 0;
    Hero* hero;
    if (index < 6) {
        hero = (Hero*)savedataGetStatus(0, 2);
        if (hero != 0) {
            pokemon = heroBiosGetPokemonPtr(hero, index);
            if (!pokemonCheckValid(pokemon)) {
                pokemon = 0;
            }
        }
    }
    if (pokemon == 0) {
        return -1;
    }
    return _menuPokemonStatusOpen(0x11, 0, pokemon, 0, 0, 0);
}

s32 menuPokemonStatusOpenWazaMachine(Pokemon* pokemon, u16 wazaId) {
    return _menuPokemonStatusOpen(0x58, 0, pokemon, wazaId, 0, 0);
}

s32 menuPokemonStatusOpenWazaLearn(Pokemon* pokemon, u16 wazaId) {
    s32 ids[4] = {0x37, 0x40, 0x38, 0x41};
    s32 result;
    s32 i;
    for (i = 0; i < 4; i++) {
        if ((u8)menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 0);
        }
    }
    result = _menuPokemonStatusOpen(0x59, 0, pokemon, wazaId, 0, 0);
    for (i = 0; i < 4; i++) {
        if ((u8)menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 1);
        }
    }
    return result;
}

s32 menuPokemonStatusOpenWazaLearnList(Pokemon* pokemon, u16 wazaId) {
    s32 ids[4] = {0x37, 0x40, 0x38, 0x41};
    s32 result;
    s32 i;
    for (i = 0; i < 4; i++) {
        if ((u8)menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 0);
        }
    }
    result = _menuPokemonStatusOpen(0x19, 0, pokemon, wazaId, 0, 0);
    for (i = 0; i < 4; i++) {
        if ((u8)menuIsCheck(ids[i])) {
            menuSetDisp(ids[i], 1);
        }
    }
    return result;
}

void menuPokemonStatus(void) {
    _menuStatus.result = _menuPokemonStatusSub(_menuStatus.flags, _menuStatus.trainer, _menuStatus.pokemon,
                                               _menuStatus.wazaId, _menuStatus.callback, _menuStatus.callbackArg);
}

extern "C" void menuPokemonStatusClose(void) {
    u8 flags = _menuStatus.flags;
    if (flags & 1) {
        if (!(flags & 8)) {
            fadeCheck(1);
            fadeSet(3, 0.5f);
            fadeCheck(1);
        }
    }
    if ((u8)menuIsCheck(0x5F)) {
        menuCloseCustom(0x5F, 0, 0);
    }
    if ((u8)menuIsCheck(0x60)) {
        menuCloseCustom(0x60, 0, 0);
    }
    if ((u8)menuIsCheck(0x62)) {
        menuCloseCustom(0x62, 0, 0);
    }
    if ((u8)menuIsCheck(0x63)) {
        menuCloseCustom(0x63, 0, 0);
    }
    menuCloseCustom(0x5E, 0, 1);
    if (_menuStatus.flags & 1) {
        GSfloorPop();
        if (_menuStatus.flags & 8) {
            floorSetFadeScript(0, 0);
        }
    }
}

static s32 _menuPokemonStatusOpen(u8 flags, FIGHT_TRAINER* trainer, Pokemon* pokemon, u16 wazaId, MenuPokemonStatusCb callback, long arg) {
    s32 i;
    DarkPokemon* dark;
    while (menuFaceCheckLoading()) {
        GSthreadSwitch();
    }
    memset(&_menuStatus, 0, 0x48);
    _menuStatus.flags = flags;
    _menuStatus.trainer = trainer;
    _menuStatus.pokemon = pokemon;
    _menuStatus.wazaId = wazaId;
    _menuStatus.callback = callback;
    _menuStatus.callbackArg = arg;
    _menuStatus.result = -1;
    for (i = 0; i < 4; i++) {
        _menuStatus.wazaNew[i] = 0;
        if (pokemon->isDarkPokemon()) {
            dark = pokemon->getDarkPokemon();
            if (dark != 0) {
                wazaId = (u16)pokemonGetStatus(pokemon, 0, 0x7F, (u8)i);
                switch ((s32)wazaId) {
                case 0:
                case 0x164:
                case 0x165:
                case 0x166:
                case 0x167:
                case 0x168:
                case 0x169:
                case 0x16A:
                case 0x16B:
                case 0x16C:
                case 0x16D:
                case 0x16E:
                case 0x16F:
                case 0x170:
                case 0x171:
                case 0x172:
                case 0x173:
                case 0x174:
                case 0x175:
                case 0x176:
                    continue;
                }
                if (i != 0) {
                    if (!dark->isWazaNew(i - 1)) {
                        _menuStatus.wazaNew[i] = 1;
                    }
                }
            }
        }
    }
    if (flags & 1) {
        GSfloorPush(0x39D);
        if (_menuStatus.flags & 8) {
            floorSetFadeScript(0, 0);
        }
        floorWaitForChange();
    } else {
        _menuPokemonStatusSub(flags, trainer, pokemon, wazaId, callback, arg);
    }
    return _menuStatus.result;
}

static s32 _menuPokemonStatusSub(u8, FIGHT_TRAINER*, Pokemon* pokemon, u16, MenuPokemonStatusCb, long) {
    s32 sp8;
    s32 res;
    u16 wazaId;
    MenuItemRect* item = menuItemBiosGetPtr(0x5E, 0x81F);
    menuModelInit(_menuModel, item->width, item->height);
    menuModelFree(_menuModel);
    menuModelLoadPokemon(_menuModel, pokemon);
    if (_menuStatus.flags & 8) {
        fadeCheck(1);
        if (_menuStatus.flags & 0x80) {
            fadeSet(2, 0.25f);
        } else {
            fadeSet(2, 0.5f);
        }
    }
    sp8 = 0;
    menuOffScreenSetPriority(0);
    for (;;) {
        res = menuOpenCustom(0x5E, 0, &sp8, 0, 1, 0);
        if (res == -1) {
            _menuStatus.result = res;
            break;
        }
        _menuStatus.result = _menuStatus.page;
        if (_menuStatus.flags & 0x40) {
            wazaId = _menuPokemonStatusGetWazaDataID(_menuStatus.pokemon, _menuStatus.page);
            if (wazaGetStatus(0, wazaId, 0x19, 0) != 0) {
                GSsndPlayNow(0x13);
                winMsgOpen(2, 0x3AFC, 1, 0);
                winMsgClose(1);
                sp8 = _menuStatus.page;
                continue;
            }
        }
        break;
    }
    if (_menuStatus.flags & 8) {
        fadeCheck(1);
        if (_menuStatus.flags & 0x80) {
            fadeSet(3, 0.25f);
        } else {
            fadeSet(3, 0.5f);
        }
        fadeCheck(1);
    }
    menuPokemonStatusClose();
    menuModelTerm(_menuModel);
    menuOffScreenSetPriority(1);
    GSthreadSwitch();
    return _menuStatus.result;
}

static s32 _menuPokemonStatusChangeSubMenu(CURSOR cursor) {
    static s32 sub_menu_id[4] = {0x5F, 0x60, 0x62, 0x63};
    u32 i;
    s32 id = 0;
    if (_menuStatus.pokemon == 0) {
        return -1;
    }
    switch (cursor.selected) {
    case 0:
        id = 0x5F;
        break;
    case 1:
        id = 0x60;
        break;
    case 2:
        id = 0x62;
        break;
    case 3:
        id = 0x63;
        break;
    }
    for (i = 0; i < 4; i++) {
        if (id == sub_menu_id[i]) {
            if (!(u8)menuIsCheck(id)) {
                menuOpen(id, 0);
            }
        } else if ((u8)menuIsCheck(sub_menu_id[i])) {
            menuClose(sub_menu_id[i]);
        }
    }
    return -1;
}

extern "C" s32 menuPokemonStatusCtrl(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
        win->prevCursor = -1;
        _menuStatus.mode = 0;
        _menuStatus.page = win->pos.selected;
        _menuStatus.prevPage = -1;
        _menuStatus.unk1A = -1;
        if (_menuStatus.flags & 4) {
            win->pos.selected = 0;
            _menuStatus.mode = 8;
        } else {
            win->pos.selected = 2;
            _menuStatus.mode = 7;
        }
        _menuPokemonStatusChangeSubMenu(win->pos);
        break;
    case 1:
        break;
    case 2:
        _menuPokemonStatusChangeSubMenu(win->pos);
        menuDrawReliveUpdate();
        break;
    }
    return 0;
}

extern "C" void menuPokemonStatusCursor(tagWINDOW_WORK* win) {
    s32 dir = 0;
    s8 maxPage;
    u16 key;
    if (_menuStatus.wazaId != 0) {
        maxPage = 5;
    } else {
        maxPage = 4;
    }
    key = windowGetKeyRepeat();
    switch (_menuStatus.mode) {
    case 0:
    case 9:
        break;
    case 1:
    case 2:
    case 5:
    case 8: {
        s8 page = win->pos.selected;
        if (key & 8) {
            page++;
        } else if (key & 4) {
            page--;
        }
        if (page > 3) {
            page = 3;
        }
        if (page < 0) {
            page = 0;
        }
        win->pos.selected = page;
        switch (page) {
        case 0:
            _menuStatus.mode = 8;
            break;
        case 1:
            _menuStatus.mode = 1;
            break;
        case 2:
            _menuStatus.mode = 2;
            break;
        case 3:
            _menuStatus.mode = 5;
            break;
        }
        if (key & 1) {
            dir = 1;
        } else if (key & 2) {
            dir = 2;
        }
        if (dir != 0) {
            if (_menuStatus.callback != 0) {
                Pokemon* p = _menuStatus.callback(_menuStatus.pokemon, (MENU_POKEMON_CB_TYPE)dir, _menuStatus.callbackArg);
                if (_menuStatus.pokemon != p) {
                    s32 i;
                    if (p != 0) {
                        menuPlaySe(win->menu, 1);
                        if (menuModelComparePokemon(_menuModel, p) == 0) {
                            menuModelLoadPokemon(_menuModel, p);
                        }
                    }
                    _menuStatus.pokemon = p;
                    for (i = 0; i < 4; i++) {
                        _menuStatus.wazaNew[i] = 0;
                        if (p->isDarkPokemon()) {
                            DarkPokemon* dark = p->getDarkPokemon();
                            if (dark != 0) {
                                s32 id = (u16)pokemonGetStatus(p, 0, 0x7F, (u8)i);
                                switch (id) {
                                case 0:
                                case 0x164:
                                case 0x165:
                                case 0x166:
                                case 0x167:
                                case 0x168:
                                case 0x169:
                                case 0x16A:
                                case 0x16B:
                                case 0x16C:
                                case 0x16D:
                                case 0x16E:
                                case 0x16F:
                                case 0x170:
                                case 0x171:
                                case 0x172:
                                case 0x173:
                                case 0x174:
                                case 0x175:
                                case 0x176:
                                    continue;
                                }
                                if (!dark->isWazaNew(i - 1)) {
                                    _menuStatus.wazaNew[i] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    case 3:
    case 4:
    case 7: {
        s8 page = _menuStatus.page;
        if (key & 1) {
            page--;
        } else if (key & 2) {
            page++;
        }
        if (page >= maxPage) {
            page = maxPage - 1;
        }
        if (page < 0) {
            page = 0;
        }
        if (_menuPokemonStatusGetWazaDataID(_menuStatus.pokemon, page) != 0) {
            if (page != _menuStatus.page) {
                menuPlaySe(win->menu, 1);
                _menuStatus.page = page;
            }
        }
        break;
    }
    case 6: {
        s8 old = _menuStatus.unk1A;
        s32 col = old % 9;
        s32 row = old / 9;
        s32 r;
        s32 c;
        if (key & 1) {
            s32 c;
            s32 r;
            r = row;
            while (r-- > 0) {
                c = col;
                do {
                    if (_menuStatus.ribbon.slots[c][r] >= 0) {
                        row = r;
                        col = c;
                        r = -1;
                        break;
                    }
                } while (c-- > 0);
            }
        } else if (key & 2) {
            r = row;
            while (++r < 4) {
                c = col;
                do {
                    if (_menuStatus.ribbon.slots[c][r] >= 0) {
                        row = r;
                        col = c;
                        r = 5;
                        break;
                    }
                } while (c-- > 0);
            }
        } else if (key & 8) {
            s32 found = 0;
            for (r = row; r < 4; r++) {
                c = (r == row) ? col + 1 : 0;
                for (; c < 9; c++) {
                    if (_menuStatus.ribbon.slots[c][r] >= 0) {
                        col = c;
                        row = r;
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        } else if (key & 4) {
            s32 found = 0;
            for (r = row; r >= 0; r--) {
                c = (r == row) ? col - 1 : 8;
                for (; c >= 0; c--) {
                    if (_menuStatus.ribbon.slots[c][r] >= 0) {
                        col = c;
                        row = r;
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
        maxPage = row * 9 + col;
        if (maxPage != old) {
            menuPlaySe(win->menu, 1);
            _menuStatus.unk1A = maxPage;
        }
        break;
    }
    }
    return;
}

extern "C" void menuPokemonStatusButton(tagWINDOW_WORK* win) {
    u16 key = windowGetKeyTrg();
    if (key & 0x10) {
        switch (_menuStatus.mode) {
        case 0:
        case 1:
        case 6:
        case 8:
        case 9:
            break;
        case 2:
            _menuStatus.page = 0;
            _menuStatus.mode = 3;
            GSsndPlayNow(0x11);
            break;
        case 3:
            if (_menuStatus.pokemon != 0) {
                if (pokemonGetStatus(_menuStatus.pokemon, 0, 0xC2, 0) != 0) {
                    GSsndPlayNow(0x13);
                } else if (_menuStatus.flags & 2) {
                    _menuStatus.mode = 4;
                    _menuStatus.prevPage = _menuStatus.page;
                    GSsndPlayNow(0x11);
                } else {
                    GSsndPlayNow(0x13);
                }
            }
            break;
        case 4:
            if (_menuStatus.prevPage != _menuStatus.page) {
                if (_menuStatus.pokemon != 0) {
                    pokemonWazaReplace(_menuStatus.pokemon, _menuStatus.prevPage, _menuStatus.page);
                }
                _menuStatus.prevPage = -1;
                _menuStatus.mode = 3;
                GSsndPlayNow(0x11);
            }
            break;
        case 5:
            if (_menuStatus.ribbon.count > 0) {
                s8 i;
                for (i = 0; i < 36; i++) {
                    if (_menuStatus.ribbon.slots[i % 9][i / 9] >= 0) {
                        break;
                    }
                }
                _menuStatus.mode = 6;
                _menuStatus.unk1A = i;
                GSsndPlayNow(0x11);
            }
            break;
        case 7:
            if (_menuStatus.flags & 0x10) {
                win->finished = 1;
                _menuStatus.result = _menuStatus.page;
            }
            break;
        }
    } else if (key & 0x20) {
        switch (_menuStatus.mode) {
        case 0:
        case 9:
            break;
        case 1:
        case 2:
        case 5:
        case 7:
        case 8:
            win->finished = 1;
            win->cancelled = 1;
            _menuStatus.mode = 9;
            break;
        case 3:
            _menuStatus.mode = 2;
            GSsndPlayNow(0x12);
            break;
        case 4:
            _menuStatus.mode = 3;
            GSsndPlayNow(0x12);
            break;
        case 6:
            _menuStatus.unk1A = -1;
            _menuStatus.mode = 5;
            GSsndPlayNow(0x12);
            break;
        }
    }
}

static u16 _menuPokemonStatusGetZokuseiSpriteID(u16 id) {
    return zokuseiBiosGetSpriteID(id);
}

extern "C" void menuPokemonStatusChangeColor(void) {}

extern "C" void menuPokemonStatusDrawTitle(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    Pokemon *pokemon = _menuStatus.pokemon;
    Pokemon *statusPokemon;
    MenuItemRect *item;
    unsigned long messageParameter;
    u32 color;
    u16 textureID;
    u8 ball;

    if (pokemon == 0)
        return;
    statusPokemon = _menuStatus.pokemon;
    if (pokemonDataBiosGetPtr(
            (u16)pokemonGetStatus(pokemon, 0, 110, 0)) == 0)
        return;

    color = window->alpha | 0xFFFFFF00;

    switch (sprite->id) {
    case 0x80F: {
        if (window->pos.selected == 0)
            sprite->color = -1;
        else
            sprite->color = 0x808080FF;
        return;
    }
    case 0x80E: {
        if (window->pos.selected == 1)
            sprite->color = -1;
        else
            sprite->color = 0x808080FF;
        return;
    }
    case 0x80D: {
        if (window->pos.selected == 2)
            sprite->color = -1;
        else
            sprite->color = 0x808080FF;
        return;
    }
    case 0x80C: {
        if (window->pos.selected == 3)
            sprite->color = -1;
        else
            sprite->color = 0x808080FF;
        return;
    }

    case 0x81C:
        winSpriteSetDisp(sprite, 1);
        switch (window->pos.selected) {
        case 2:
            switch (_menuStatus.mode) {
            case 3:
            case 4:
                if (_menuStatus.flags & 0x2)
                    sprite->message = 0x3AE4;
                else
                    sprite->message = 0x3AE3;
                break;
            case 7:
                sprite->message = 0x3C3B;
                break;
            case 9:
                break;
            default:
                sprite->message = 0x3AE3;
                break;
            }
            if (_menuStatus.mode == 3 &&
                (pokemonIsDarkPokemon(pokemon) ||
                 (_menuStatus.flags & 0x2) == 0))
                winSpriteSetDisp(sprite, 0);
            break;
        case 3:
            if (_menuStatus.ribbon.count != 0) {
                if (_menuStatus.mode == 6)
                    winSpriteSetDisp(sprite, 0);
                else
                    sprite->message = 0x3AE6;
            } else {
                winSpriteSetDisp(sprite, 0);
            }
            break;
        default:
            winSpriteSetDisp(sprite, 0);
            break;
        }
        return;

    case 0x811:
    case 0x812:
    case 0x815:
        winSpriteSetDisp(sprite, 0);
        switch (window->pos.selected) {
        case 2:
            winSpriteSetDisp(sprite, 1);
            if (_menuStatus.mode == 3 &&
                (pokemonIsDarkPokemon(pokemon) ||
                 (_menuStatus.flags & 0x2) == 0))
                winSpriteSetDisp(sprite, 0);
            break;
        case 3:
            if (_menuStatus.ribbon.count != 0 && _menuStatus.mode != 6)
                winSpriteSetDisp(sprite, 1);
            break;
        default:
            break;
        }
        return;

    case 0x81F: {
        MenuItemRect *item = menuItemBiosGetPtr(0x5E,
                                                     0x81F);
        f32 angle[3];

        menuModelSetSize(&_menuModel, item->x, item->y,
                         item->width, item->height);
        if (menuModelComparePokemon(&_menuModel, pokemon) != 1)
            return;
        if (menuModelCheck(&_menuModel, 0) == 0)
            menuModelAdjustCamera(&_menuModel);
        angle[0] = -0.1f;
        angle[1] = 0.3f;
        angle[2] = 0.0f;
        menuModelSetAngle(&_menuModel, angle);
        menuModelRender(&_menuModel);
        return;
    }

    case 0x817:
    case 0x818:
    case 0x819:
    case 0x81A: {
        u8 id = 0;
        u8 markings = (u8)pokemonGetStatus(pokemon, 0, 187, 0);

        switch (sprite->id) {
        case 0x817: id = 8; break;
        case 0x818: id = 4; break;
        case 0x819: id = 2; break;
        case 0x81A: id = 1; break;
        default: break;
        }
        winSpriteSetDisp(sprite, (markings & id) != 0);
        return;
    }

    case 0x816: {
        ball = pokemonBiosGetCatchBallId(pokemon);

        if (ball == 0)
            return;
        item = menuItemBiosGetPtr(0x5E, 0x816);
        windowDrawSprite2(0, 0, item->width, item->height, 0xFFFFFFFF, window,
                                      ((u16 (*)(u8))mballBiosGetSpriteID)((u8)ball), 0,
                                      winSpriteGetLayerID(window, sprite));
        return;
    }

    case 0x804: {
        u8 pokerus = (u8)pokemonGetStatus(pokemon, 0, 181, 0);

        if ((pokerus & 0xF) != 0)
            textureID = 0x84;
        else if (pokerus != 0)
            textureID = 0x1F8;
        else
            textureID = 0;
        ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, textureID, 0, winSpriteGetLayerID(window, sprite));
        return;
    }

    case 0x805: {
        u16 statusSpriteID = ((u16 (*)(Pokemon*,bool))menuPokemonGetJoutaiSpriteID)(pokemon, 1);

        ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, statusSpriteID, 0, winSpriteGetLayerID(window, sprite));
        return;
    }

    case 0x25D: {
        messageParameter = (u16)pokemonGetSoubiItemDataId(pokemon);

        if (messageParameter != 0) {
            msgctrlSetValue(0x2D, (unsigned long)messageParameter);
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x3AE7);
        } else {
            msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(0x3C1A));
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4277);
        }
        return;
    }

    case 0x81D: {
        s32 width = (s16)(GSmsgGetRect(sprite->message) >> 16);

        msgctrlSetValue(0x5F, (unsigned long)(u8)pokemonGetStatus(pokemon, 0, 122, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), width + 3, 0, sprite->x, sprite->y, color, 0x4351);
        return;
    }

    case 0x264:
    case 0x81E: {
        u32 sex;

        if (sprite->id == 0x264) {
            messageParameter = (unsigned long)GSmsgGetGSchar(
                pokemonGetStatus(0, (u16)pokemonGetStatus(statusPokemon, 0, 110, 0), 1, 0));
        } else {
            messageParameter = (unsigned long)pokemonGetStatus(statusPokemon, 0, 119, 0);
            if (((u8 (*)(Pokemon*))pokemonCheckRare)(pokemon))
                color = window->alpha | 0xFFDC0000;
        }
        msgctrlSetValue(0x37, (unsigned long)messageParameter);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4277);
        GSmsgGetRect(0x4277);
        sex = ((u8 (*)(Pokemon*))menuSubGetPokemonSexForDisp)(statusPokemon);
        switch (sex) {
        case 0: sex = 0x9C5; break;
        case 1: sex = 0x9C6; break;
        case 2:
        default: sex = 0; break;
        }
        if (sex != 0) {
            msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(sex));
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0x78, 0, color, 0x4276);
        }
        return;
    }

    default:
        return;
    }
}

u8 _menuPokemonStatusCheckOya(Pokemon* pokemon) {
    FIGHT_TRAINER* trainer = _menuStatus.trainer;
    Hero* hero;
    u8* name;
    u32 rnd;
    if (pokemon == 0) {
        return 0;
    }
    if ((u8)gamedataGetStatus(pokemonGetStatus(pokemon, 0, 0x70, 0), 2) != 0xB) {
        return 0;
    }
    if (_menuStatus.flags & 0x20) {
        if (trainer == 0) {
            trainer = (FIGHT_TRAINER*)fightFloorGetGcHeroFightTrainerPtr(0);
        }
        if (trainer == 0) {
            return 0;
        }
        hero = fightTrainerBiosGetHeroPtr(trainer);
    } else if (GSflagGet(0x30D) == 0) {
        hero = (Hero*)savedataGetStatus(0, 2);
    } else {
        hero = menuCBBios_GetRegisteredHero();
    }
    name = heroBiosGetNamePtr(hero);
    rnd = heroBiosGetRnd(hero);
    if (rnd == pokemonGetStatus(pokemon, 0, 0x75, 0)) {
        if (GScharCmp(name, (u8*)pokemonGetStatus(pokemon, 0, 0x76, 0)) == 0) {
            return 1;
        }
    }
    return 0;
}

u8 _menuPokemonStatusCheckGinzaru(Pokemon* pokemon) {
    s32 id = pokemonGetStatus(pokemon, 0, 0x75, 0) & 0xFFFF;
    if (id == 0x911D) {
        if (GScharCmp((u8*)pokemonGetStatus(pokemon, 0, 0x76, 0), GSmsgGetGSchar(0x17B9)) == 0) {
            return 1;
        }
    }
    return 0;
}

u8 _menuPokemonStatusCheckDanny(Pokemon* pokemon) {
    s32 id = pokemonGetStatus(pokemon, 0, 0x75, 0) & 0xFFFF;
    if (id == 0xA1B8) {
        if (GScharCmp((u8*)pokemonGetStatus(pokemon, 0, 0x76, 0), GSmsgGetGSchar(0x1828)) == 0) {
            return 1;
        }
    }
    return 0;
}

extern "C" void menuPokemonStatusDrawStatus(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 x;
    s32 digit;
    u32 div;
    Pokemon *pokemon = _menuStatus.pokemon;
    u32 color;
    s32 value;
    u32 placeName;
    u32 place;
    u32 next;
    u8 level;
    u16 icon;
    void *stats;

    if (pokemon == 0)
        return;
    stats = pokemonDataBiosGetPtr(
        (u16)pokemonGetStatus(pokemon, 0, 110, 0));
    if (stats == 0)
        return;
    if ((u8)_menuPokemonStatusCheckWazaItem(window, sprite) == 0)
        return;

    color = window->alpha | 0xFFFFFF00;

    switch (sprite->id) {
    case 0x845:
        if (pokemonGetStatus(_menuStatus.pokemon, 0, 194, 0) != 0)
            sprite->message = 0x3C11;
        else
            sprite->message = 0x3C10;
        return;

    case 0x21D: {
        icon = zokuseiGetPokemonSpriteID(stats, 0);

        if (icon == 0)
            return;
        ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, (s32)icon, 0, winSpriteGetLayerID(window, sprite));
        return;
    }

    case 0x21C: {
        u8 type0 = (u8)pokemonDataBiosGetZokuseiDataId(stats, 0);

        if (type0 == (u8)pokemonDataBiosGetZokuseiDataId(stats, 1))
            return;
        icon = zokuseiGetPokemonSpriteID(stats, 1);
        ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, (s32)icon, 0, winSpriteGetLayerID(window, sprite));
        return;
    }

    case 0x25C: {

        if ((u8)pokemonGetDarkPokemonLevel(pokemon) < 3) {
            value = 0x945;
        } else {
            s32 natureMessageId = pokemonSeikakuDataBiosGetName(
                pokemonSeikakuDataBiosGetPtr((u8)pokemonGetStatus(pokemon, 0, 191, 0)));

            value = natureMessageId;
        }
        msgctrlSetValue(0x55, (unsigned long)value);
        switch (value) {
        case 0xC86:
        case 0xC96:
            msgctrlSetValue(0x56, 1);
            break;
        default:
            msgctrlSetValue(0x56, 0x3AEC);
            break;
        }

        value = (u8)pokemonGetStatus(pokemon, 0, 114, 0);
        if ((u32)value == 0)
            value = 5;
        msgctrlSetValue(0x34, (unsigned long)value);

        if (_menuPokemonStatusCheckOya(pokemon)) {
            s32 species = (u16)pokemonGetStatus(pokemon, 0, 110, 0);

            switch (species) {
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0xC4:
            case 0xC5:
                value = 0x3AF7;
                break;
            default:
                value = 0x3AE1;
                break;
            }
        } else {
            value = 0x3AE1;
        }
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, value);

        value = 0x3AFA;
        place = pokemonGetStatus(pokemon, 0, 113, 0);
        placeName = dispSummaryPlaceName(place);
        if (_menuPokemonStatusCheckOya(pokemon)) {
            s32 species = (u16)pokemonGetStatus(pokemon, 0, 110, 0);

            switch (species) {
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0xC4:
            case 0xC5:
                if (fightKind_CheckFightKind(0xE) == 0)
                    value = 0x3AF8;
                break;
            default:
                if (placeName != 0) {
                    msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(placeName));
                    value = 0x3AEB;
                }
                break;
            }
        } else {
            u8 origin = (u8)(u32)((void* (*)(void*,s32))gamedataGetStatus)((void *)pokemonGetStatus(pokemon, 0, 112, 0), 2);

            switch (origin) {
            case 0xB: {
                if (_menuPokemonStatusCheckGinzaru(pokemon)) {
                    if (placeName != 0) {
                        msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(placeName));
                        value = 0x3AEB;
                    }
                } else if (_menuPokemonStatusCheckDanny(pokemon)) {
                    if (placeName != 0) {
                        msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(placeName));
                        value = 0x3AEB;
                    }
                } else if (place == 0xFF) {
                    value = 0x3AF9;
                }
                break;
            }
            case 8:
            case 9:
            case 0xA: {
                if (place == 0xFF)
                    value = 0x3AF9;
                break;
            }
            default:
                break;
            }
        }
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0x20, sprite->x, sprite->y, color, value);
        return;
    }

    case 0x849: {
        u8 level;

        if (pokemonIsDarkPokemon(pokemon) == 1) {
            level = pokemonGetDarkPokemonLevel(pokemon);
            switch (level) {
            case 0: sprite->message = 0x3AED; break;
            case 1: sprite->message = 0x3AEE; break;
            case 2: sprite->message = 0x3AEF; break;
            case 3: sprite->message = 0x3AF0; break;
            case 4: sprite->message = 0x3AF1; break;
            case 5: sprite->message = 0x3AF2; break;
            case 6: sprite->message = 0x3AF3; break;
            default: break;
            }
        } else {
            sprite->message = 0x3ADF;
        }
        return;
    }

    case 0x846: {
        // Exp bar of the level the pokemon is on.
        u8 level = (u8)pokemonGetStatus(pokemon, 0, 122, 0);
        u32 next = pokemonGetLevelToExp(pokemon, (u8)(level + 1));

        if (next == 0)
            value = 0;
        else
            value = next - pokemonGetStatus(pokemon, 0, 121, 0);
        msgctrlSetValue(0x34, value);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4287);
        return;
    }

    case 0x848:
        msgctrlSetValue(0x34, pokemonGetStatus(pokemon, 0, 121, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4287);
        return;

    case 0x84A:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 140, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4287);
        return;

    case 0x84C:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 139, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4287);
        return;

    case 0x84E:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 138, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4287);
        return;

    case 0x850:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 137, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4287);
        return;

    case 0x852:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 136, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4287);
        return;

    case 0x854:
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 131, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, 0x37, sprite->y, color, 0x4287);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0x37, 0, color, 0x3AE8);
        msgctrlSetValue(0x34, (s16)pokemonGetStatus(pokemon, 0, 135, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4287);
        return;

    case 0x843:
        msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(
            ((u32 (*)(void*))pokemonTokuseiDataBiosGetDoc)(
                pokemonTokuseiDataBiosGetPtr((u16)pokemonGetTokuseiDataId(pokemon)))));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4276);
        return;

    case 0x844:
        msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(
            ((u32 (*)(void*))pokemonTokuseiDataBiosGetName)(
                pokemonTokuseiDataBiosGetPtr((u16)pokemonGetTokuseiDataId(pokemon)))));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4276);
        return;


    case 0x25F: {
        // The trainer id of the pokemon, one digit at a time.
        x = (s16)(GSmsgGetRect(sprite->message) >> 16);
        if (pokemonIsDarkPokemon(pokemon) == 1) {
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x3AD4);
            return;
        }
        value = (u16)pokemonGetStatus(pokemon, 0, 117, 0);
        {
            // Each digit is printed at its own position to the right of the
            // previous one.
            s32 px = x;
            u32 div = 10000;

            for (digit = 0; digit < 5; digit++) {
                s32 cur = value / div;

                value -= cur * div;
                div /= 10;
                msgctrlSetValue(0x34, (unsigned long)cur);
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), px, 0, color, 0x426F);
                px += 13;
            }
        }
        return;
    }

    case 0x261: {

        if (pokemonIsDarkPokemon(pokemon) == 1)
            msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(0x3AD4));
        else
            msgctrlSetValue(0x37, (unsigned long)pokemonGetStatus(pokemon, 0, 118, 0));
        x = (s16)(GSmsgGetRect(sprite->message) >> 16);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x4276);
        return;
    }

    case 0x83B: {
        u16 spriteID;

        // HP bar: the texture shows how full the bar is, and the bar is drawn
        // as wide as the HP ratio.
        s16 hp = (s16)pokemonGetStatus(pokemon, 0, 131, 0);
        s16 hpMax = (s16)pokemonGetStatus(pokemon, 0, 135, 0);
        f32 ratio = (f32)hp / (f32)hpMax;

        if (ratio < 0.2)
            spriteID = 0xF5;
        else if (ratio < 0.5)
            spriteID = 0xF4;
        else
            spriteID = 0xF3;
        // The bar is as wide as the ratio of the window.
        windowDrawSprite2(0, 0, (s16)((f32)sprite->x * ratio), sprite->y,
                                      color, window, spriteID, 0,
                                      winSpriteGetLayerID(window, sprite));
        return;
    }

    case 0x83C: {
        s32 base;
        s32 span;

        // Exp bar: as wide as the exp of the current level is complete.
        u8 level = (u8)pokemonGetStatus(pokemon, 0, 122, 0);
        u32 next = pokemonGetLevelToExp(pokemon, (u8)(level + 1));

        if (next == 0)
            return;
        base = pokemonGetLevelToExp(pokemon, level);
        span = next - base;
        {
            s32 progress = pokemonGetStatus(pokemon, 0, 121, 0) - base;
            s32 total = span - 1 + progress * sprite->x;
            s32 width = (s16)((u32)total / span);

            windowDrawSprite2(0, 0, width, sprite->y, color, window, 0xF6, 0,
                                          winSpriteGetLayerID(window, sprite));
        }
        return;
    }

    case 0x83E: {
        MenuItemRect *item = menuItemBiosGetPtr(0x60,
                                                     0x83E);

        menuDrawReliveMeter(pokemon, item->width, item->height,
                            winSpriteGetLayerID(window, sprite));
        return;
    }

    default:
        return;
    }
}

s32 _menuPokemonStatusCheckWazaItem(tagWINDOW_WORK*, tagSPRITE_WORK* spr) {
    s32 r = 1;
    switch (spr->id) {
    case 0x1E1:
    case 0x1E2:
    case 0x1E3:
    case 0x1E4:
    case 0x1E5:
    case 0x1E6:
    case 0x1E7:
    case 0x1E8:
    case 0x1E9:
    case 0x1EA:
    case 0x1EB:
    case 0x1EC:
    case 0x1ED:
    case 0x1EE:
    case 0x1EF:
    case 0x1F0:
    case 0x1F1:
    case 0x1F2:
    case 0x1F3:
    case 0x1F4:
    case 0x1F5:
    case 0x1F6:
    case 0x1F7:
    case 0x1F8:
    case 0x24C:
        switch (_menuStatus.mode) {
        case 3:
        case 4:
        case 7:
            if (_menuStatus.page >= 0 && _menuStatus.page <= 4) {
                r = 1;
            } else {
                r = 0;
            }
            break;
        default:
            r = 0;
            break;
        }
        winSpriteSetDisp(spr, r);
        break;
    case 0x83D:
    case 0x83E:
    case 0x83F:
    case 0x840:
    case 0x841:
    case 0x842:
        winSpriteSetDisp(spr, 0);
        break;
    case 0x837:
    case 0x83C:
    case 0x846:
    case 0x847:
    case 0x848:
        if (pokemonGetStatus(_menuStatus.pokemon, 0, 0xC2, 0) != 0) {
            r = 0;
        } else {
            r = 1;
        }
        winSpriteSetDisp(spr, r);
        break;
    }
    return r;
}

u16 _menuPokemonStatusGetWazaDataID(Pokemon* pokemon, u16 index) {
    u16 id;
    if (index == 4) {
        id = _menuStatus.wazaId;
    } else {
        id = pokemonGetStatus(pokemon, 0, 0x7F, index);
        if (pokemonWazaCheckValid(pokemon, index) == 0) {
            return 0;
        }
    }
    return id;
}

static s32 NotDarkWaza(long id) {
    if (id < 0x176 && id >= 0x164) {
        return 0;
    }
    return id;
}

extern "C" void menuPokemonStatusDrawWaza(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s32 color;
    Pokemon *pokemon = _menuStatus.pokemon;
    s16 x;
    u16 waza;
    u16 slot;
    u16 selectedMoveID;
    u32 msg = 0;
    s32 i = 0;

    if (pokemon == 0)
        return;
    if ((u8)_menuPokemonStatusCheckWazaItem(window, sprite) == 0)
        return;

    color = window->alpha | 0xFFFFFF00;

    switch (sprite->id) {
    case 0x205:
        winSpriteSetDisp(sprite, 0);
        switch (_menuStatus.mode) {
        case 4:
            if (_menuStatus.wazaId != 0) {
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, (s16)((s8)_menuStatus.prevPage * 44), window, 0xF7, 0,
                            winSpriteGetLayerID(window, sprite));
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, (s16)((s8)_menuStatus.page * 44), window, 0xF2, 0,
                            winSpriteGetLayerID(window, sprite));
            } else {
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, (s16)(((s8)_menuStatus.prevPage + 1) * 44), window, 0xF7, 0,
                            winSpriteGetLayerID(window, sprite));
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, (s16)(((s8)_menuStatus.page + 1) * 44), window, 0xF2, 0,
                            winSpriteGetLayerID(window, sprite));
            }
            break;

        case 3:
        case 7:
            if (_menuStatus.wazaId != 0)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, (s16)((s8)_menuStatus.page * 44), window, 0xF2, 0,
                            winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, (s16)(((s8)_menuStatus.page + 1) * 44), window, 0xF2, 0,
                            winSpriteGetLayerID(window, sprite));
            break;
        }
        return;

    case 0x200:
    case 0x201:
    case 0x202:
    case 0x203:
    case 0x204: {
        // The cell draws the type icon of the move it stands on; a move the
        // pokemon has not seen yet is flagged on the way.
        if (_menuStatus.wazaId == 0) {
            if (sprite->id == 0x204)
                return;
            switch (sprite->id) {
            case 0x203: slot = 0; break;
            case 0x202: slot = 1; break;
            case 0x201: slot = 2; break;
            case 0x200: slot = 3; break;
            }
        } else {
            if (sprite->id == 0x200)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(7, 0x14, window, 0xF8, 0, winSpriteGetLayerID(window, sprite));
            switch (sprite->id) {
            case 0x204: slot = 0; break;
            case 0x203: slot = 1; break;
            case 0x202: slot = 2; break;
            case 0x201: slot = 3; break;
            case 0x200: slot = 4; break;
            }
        }
        msg = menuPokemonStatusGetSlotIcon(window, sprite, pokemon, slot);
        if (msg == 0)
            return;
        ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, (u16)msg, 0, winSpriteGetLayerID(window, sprite));
        return;
    }

    case 0x24F:
    case 0x250:
    case 0x251:
    case 0x252:
    case 0x253:
        if (_menuStatus.wazaId == 0) {
            if (sprite->id == 0x253)
                return;
            switch (sprite->id) {
            case 0x252: slot = 0; break;
            case 0x251: slot = 1; break;
            case 0x250: slot = 2; break;
            case 0x24F: slot = 3; break;
            }
        } else {
            switch (sprite->id) {
            case 0x253: slot = 0; break;
            case 0x252: slot = 1; break;
            case 0x251: slot = 2; break;
            case 0x250: slot = 3; break;
            case 0x24F: slot = 4; break;
            }
        }
        waza = menuPokemonStatusGetWazaId(pokemon, slot);
        if ((u16)waza == 0) {
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x3AF4);
            return;
        }
        u32 nameID = ((s32 (*)(s32,u16,u16,s32))wazaGetStatus)(0, waza, 1, 0);
        if (nameID == 0)
            return;
        msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar((s32)nameID));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4277);
        return;

    case 0x254:
    case 0x255:
    case 0x256:
    case 0x257:
    case 0x258:
        if (_menuStatus.wazaId == 0) {
            if (sprite->id == 0x258)
                return;
            switch (sprite->id) {
            case 0x257: slot = 0; break;
            case 0x256: slot = 1; break;
            case 0x255: slot = 2; break;
            case 0x254: slot = 3; break;
            }
        } else {
            switch (sprite->id) {
            case 0x258: slot = 0; break;
            case 0x257: slot = 1; break;
            case 0x256: slot = 2; break;
            case 0x255: slot = 3; break;
            case 0x254: slot = 4; break;
            }
        }
        waza = menuPokemonStatusGetWazaId(pokemon, slot);
        x = (s16)(((s16)sprite->x - (s16)(GSmsgGetRect(0x3AE8) >> 16)) / 2);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x3AE8);
        msg = (s32)NotDarkWaza(waza);
        switch (msg) {
        case 0:
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->y, color, 0x3AF5);
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x3AF5);
            return;
        case 374:
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->y, color, 0x3AD1);
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x3AD1);
            return;
        default:
            break;
        }
        if (slot == 4)
            msg = ((s32 (*)(s32,u16,u16,s32))wazaGetStatus)(0, waza, 2, 0);
        else
            msg = pokemonGetStatus(pokemon, 0, 128, slot);
        msgctrlSetValue(0x34, msg);
        GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->y, color, 0x427B);
        if (slot == 4)
            msg = ((s32 (*)(s32,u16,u16,s32))wazaGetStatus)(0, waza, 2, 0);
        else
            msg = pokemonWazaGetMaxPP(pokemon, slot);
        msgctrlSetValue(0x34, msg);
        GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x427B);
        return;

    case 0x24C:
        waza = menuPokemonStatusGetWazaId(pokemon, (u16)_menuStatus.page);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color,
                    ((s32 (*)(s32,u16,u16,s32))wazaGetStatus)(0, waza, 34, 0));
        return;

    case 0x24D:
        switch (_menuStatus.mode) {
        case 3:
        case 4:
        case 7:
            u32 accuracy = ((s32 (*)(s32,u16,u16,s32))wazaGetStatus)(0, menuPokemonStatusGetWazaId(pokemon, (u16)_menuStatus.page), 6, 0);
            if (accuracy <= 1) {
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x3AF6);
            } else {
                msgctrlSetValue(0x34, accuracy);
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4270);
            }
            winSpriteSetDisp(sprite, 1);
            break;

        default:
            winSpriteSetDisp(sprite, 0);
            break;
        }
        return;

    case 0x24E:
        switch (_menuStatus.mode) {
        case 3:
        case 4:
        case 7:
            u32 power = ((s32 (*)(s32,u16,u16,s32))wazaGetStatus)(0, menuPokemonStatusGetWazaId(pokemon, (u16)_menuStatus.page), 7, 0);
            if (power <= 1) {
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x3AF6);
            } else {
                msgctrlSetValue(0x34, power);
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->x, sprite->y, color, 0x4270);
            }
            winSpriteSetDisp(sprite, 1);
            break;

        default:
            winSpriteSetDisp(sprite, 0);
            break;
        }
        return;

    case 0x1FD:
        if (_menuStatus.wazaId == 0)
            winSpriteSetDisp(sprite, 0);
        else
            winSpriteSetDisp(sprite, 1);
        return;

    case 0x388:
    case 0x389:
    case 0x38A:
    case 0x38B:
        if (_menuStatus.wazaId == 0)
            winSpriteSetDisp(sprite, 1);
        else
            winSpriteSetDisp(sprite, 0);
        return;

    case 0x1E8: i = 1;
    case 0x1E9: i++;
    case 0x1EB: i++;
    case 0x1EA: i++;
    case 0x1ED: i++;
    case 0x1EC: i++;
    case 0x1EE: i++;
    case 0x1EF: i += 2;
    case 0x1F0: i++;
    case 0x1F1: i++;
    case 0x1F3: i++;
    case 0x1F2: i++;
    case 0x1F5: i++;
    case 0x1F6: i++;
    case 0x1F4: i++;
    case 0x1F7: i++;
    case 0x1F8:
        selectedMoveID = menuPokemonStatusGetWazaId(pokemon, (u16)_menuStatus.page);
        switch (((u8 (*)(u16))wazaDB_GetCompatible)(selectedMoveID)) {
        case 0:
        case 2:
        case 3:
            break;
        case 1: {
            s32 state = zokuseiBiosGetWazaJoutai(((s32 (*)(s32,u16,u16,s32))wazaGetStatus)(0, selectedMoveID, 3, 0), i);

            switch (state) {
            case 0x3F: color = 0x35D; break;
            case 0x41: color = 0x35F; break;
            case 0x42: color = 0x360; break;
            case 0x43: color = 0x35E; break;
            default: break;
            }
            ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, (u16)color, 0, winSpriteGetLayerID(window, sprite));
            return;
        }
        case 4:
            if (i == 7)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35E, 0, winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 5:
            if (i == 0xC)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35E, 0, winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 6:
            if (i == 3 || i == 8)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35E, 0, winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 7:
            if (i == 4)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35E, 0, winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 8:
            if (i == 2)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35E, 0, winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 9:
            if (i == 0)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35E, 0, winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 10:
        case 11:
        case 14:
            ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x376, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 12:
            if (i == 0x11)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35E, 0, winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 13:
            if (i == 0xA)
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35E, 0, winSpriteGetLayerID(window, sprite));
            else
                ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        case 15:
            ((void (*)(s16,s16,tagWINDOW_WORK*,u16,s32,s32))windowDrawSprite)(0, 0, window, 0x35D, 0, winSpriteGetLayerID(window, sprite));
            return;
        default:
            return;
        }

    default:
        return;
    }
}

void _menuPokemonStatusMakeRibbon(Pokemon *pokemon, RIBBON_WORK *work)
{
    static RibbonMap ribbon_mapping_tbl[10] = {
        {0xA3, 0x00, 1}, {0xB0, 0x01, 4}, {0xB1, 0x05, 4}, {0xB2, 0x09, 4}, {0xB3, 0x0D, 4},
        {0xB4, 0x11, 4}, {0xA4, 0x15, 1}, {0xA5, 0x16, 1}, {0xA6, 0x17, 1}, {0xA7, 0x18, 1},
    };
    static RibbonMap exribbon_mapping_tbl[7] = {
        {0xA8, 0x19, 1}, {0xA9, 0x1A, 1}, {0xAA, 0x1B, 1}, {0xAB, 0x1C, 1},
        {0xAC, 0x1D, 1}, {0xAD, 0x1E, 1}, {0xAE, 0x1F, 1},
    };

    long column;
    unsigned long kind;
    long count;
    long index;
    long i;
    long row;
    for (row = 0; row < 4; row++)
        for (column = 0; column < 9; column++)
            work->slots[column][row] = -1;

    index = 0;
    for (kind = 0; kind < 10; kind++) {
        count = pokemonGetStatus(pokemon, 0, ribbon_mapping_tbl[kind].id, 0);
        if (count > ribbon_mapping_tbl[kind].max)
            count = ribbon_mapping_tbl[kind].max;
        if (count != 0) {
            for (i = 0; i < count; i++) {
                column = index % 9;
                row = index / 9;
                work->slots[column][row] = (s8)(ribbon_mapping_tbl[kind].base + i);
                index++;
            }
        } else {
            index += ribbon_mapping_tbl[kind].max;
        }
    }

    index = 0;
    for (kind = 0; kind < 7; kind++) {
        count = pokemonGetStatus(pokemon, 0, exribbon_mapping_tbl[kind].id, 0);
        if (count > exribbon_mapping_tbl[kind].max)
            count = exribbon_mapping_tbl[kind].max;
        if (count != 0) {
            for (i = 0; i < count; i++) {
                work->slots[index][3] = (s8)(i + exribbon_mapping_tbl[kind].base);
                index++;
            }
        } else {
            index += exribbon_mapping_tbl[kind].max;
        }
    }

    count = 0;
    for (kind = 0; kind < 4; kind++)
        for (column = 0; column < 9; column++)
            if (work->slots[column][kind] >= 0)
                count++;
    work->count = count;
}

void menuPokemonStatusCtrlRibbon(void) {
    if (_menuStatus.pokemon != 0) {
        _menuPokemonStatusMakeRibbon(_menuStatus.pokemon, &_menuStatus.ribbon);
    }
}

extern "C" void menuPokemonStatusDrawRibbon(tagWINDOW_WORK* win, tagSPRITE_WORK* spr) {
    u32 color;
    u32 msg;
    s32 id;
    s32 i = 0;
    if (windowSearchID(0x5E) == 0) {
        return;
    }
    if (_menuStatus.pokemon == 0) {
        return;
    }
    color = win->alpha | ~0xFF;
    switch (spr->id) {
    case 0x25B:
        msgctrlSetValue(0x34, _menuStatus.ribbon.count);
        GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, 0x4287);
        break;
    case 0x25A:
        if (_menuStatus.mode == 6) {
            s8 cursor = _menuStatus.unk1A;
            i = _menuStatus.ribbon.slots[cursor % 9][cursor / 9];
            if (i < 0 && getRibbonCnt() <= i) {
                break;
            }
            id = ribbon_id_tbl[i];
            switch (id) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6: {
                u32 no = exribbonGetNo(id);
                if (no != 0) {
                    s32 k = no - 1;
                    msg = ex_ribbon_id[k];
                } else {
                    msg = 0;
                }
                break;
            }
            case -1:
                msg = getRibbonMsgID(i);
                break;
            }
            if (msg != 0) {
                GSmsgPrintRect(winSpriteGetLayerID(win, spr), 0, 0, spr->x, spr->y, color, msg);
            }
        }
        break;
    case 0x22A:
        i = 1;
    case 0x22B: i++;
    case 0x22C: i++;
    case 0x22D: i++;
    case 0x22E: i++;
    case 0x22F: i++;
    case 0x230: i++;
    case 0x231: i++;
    case 0x232: i++;
    case 0x233: i++;
    case 0x234: i++;
    case 0x235: i++;
    case 0x236: i++;
    case 0x237: i++;
    case 0x238: i++;
    case 0x239: i++;
    case 0x23A: i++;
    case 0x23B: i++;
    case 0x23C: i++;
    case 0x23D: i++;
    case 0x23E: i++;
    case 0x23F: i++;
    case 0x240: i++;
    case 0x241: i++;
    case 0x242: i++;
    case 0x243: i++;
    case 0x244: i++;
    case 0x245: i++;
    case 0x246: i++;
    case 0x247: i++;
    case 0x248: i++;
    case 0x249:
        {
        s32 n = 32 - (i + 1);
        if (n > 0x18) {
            n += 2;
        }
        if (_menuStatus.ribbon.slots[n % 9][n / 9] >= 0) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        }
        break;
    case 0x229: {
        s8 cursor = _menuStatus.unk1A;
        if (cursor >= 0) {
            id = cursor % 9;
            windowDrawSprite(id * 30, (cursor / 9) * 52, win, 0x366, 0, winSpriteGetLayerID(win, spr));
        }
        break;
    }
    case 0x21E:
    case 0x220:
        if (_menuStatus.mode == 6) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    }
}
