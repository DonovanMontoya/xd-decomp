#pragma dollar_identifiers on
#include <game/menuFightLayout.hpp>

extern "C" {
void *memcpy(void *, const void *, u32);
u8 fightKind_CheckFightKind(s32);
u8 fightFloorIsNowEncountTuusinTaisen(s32);
u8 fightFloorIsUseFightTimerCommand(s32);
u8 fightTimerCommandIsOver(void);
u16 fightGetFightResultId(void);
u32 fightMenuGetFightTrainerPtrToStatusMenuId(FIGHT_TRAINER *, u16);
void gbaCommandRequestAction(s32, s32, s32, s32);
u8 menuIsCheck(s32);
s32 menuOpen(s32, s32);
s32 menuOpenCustom(s32, s32, s32 *, s32, s32, s32, ...);
void menuCloseCustom(s32, s32, s32);
void menuButtonNormal(tagWINDOW_WORK *);
void winSeqSetMenu(s32, s32);
u8 winSeqCheckMove(s32);
s32 windowGetParam(tagWINDOW_WORK *, s32);
void *windowGetAllocPtr(tagWINDOW_WORK *);
struct FightWazaWork {
    u8 mode;
    u8 reserved1;
    s8 saved;
};
FightWazaWork *windowGetFreeWork(tagWINDOW_WORK *);
void *windowAllocMemory(tagWINDOW_WORK *, s32);
MenuFightKey *windowGetKeyInfo(void);
u8 menuItemBiosGetSelectFlag(s32, s16);
s32 menuGetCursorItemID(s32);
FIGHT_TRAINER *fightFloorGetGcHeroFightTrainerPtr(s32);
void *fightTrainerGetValidFightPokemonPtr(FIGHT_TRAINER *, u16);
s32 pokemonGetStatus(void *, s32, s32, u16);
u8 pokemonCheckValid(Pokemon *);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
void GSthreadSwitch(void);
f32 timeGetLastFrameSec(void);
MenuCursor windowGetCursor(s32);
Pokemon *fightOutPokemonGetPokemonPtr(s32);
u8 fightOutPokemonCheckCanOutOkWazaBanme(s32, u16, s32, u16 *);
void *wazaGetStatus(s32, u16, s32, s32);
u32 GSmsgGetGSchar(void *);
void fightFloorSetStatus(s32, s32, s32, s32, s32);
s32 fightOutPokemonGetSoubiItemDataId(s32);
u8 pokemonWazaCheckValid(void *, u16);
void windowDrawSprite(s32, s32, tagWINDOW_WORK *, s32, s32, s32);
s32 zokuseiBiosGetSpriteID(u16);
void winMsgOpen(s32, u32, s32, s32);
void winMsgClose(s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
f64 atan2(f64, f64);
s32 menuSetDisp(s32, s32);
void menuClose(s32);
void GSsndPlayNow(s32);
void windowCreateCursorSprite(tagWINDOW_WORK *);
s32 menuGetSelectItemNum(s32);
void pokemonWazaReplace(void *, s32, s32);
void pokemonToMenuWazaStatus(void *, MENU_WAZA_STATUS *);
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(s32, s32 *, s32 **);
s32 fightOutPokemonGetNicknamePtr(s32 *);
u16 fightOutPokemonGetTokuseiDataId(s32 *);
u32 fightPokemonGetNicknamePtr(u32);
u8 fightTrainerCheckCanIrekaeFightPokemon(FIGHT_TRAINER *, u32);
void GSlogWrite(const char *, ...);
s32 fightFloorGetStatus(s32, s32, s32, s32);
void msgctrlSetValue(s32, u32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSmsgPrintRect(s32, s32, s32, s16, s32, u32, u32);
void GSmsgPrintRight(s32, s32, s32, s32, s32, u32, u32);
u32 GSmsgGetRect(u32);
void menuSubDrawCursorBack(s32, s32, s32, s32, s32, s32, s32);
s32 menuSubCalcColor(tagWINDOW_WORK *, tagSPRITE_WORK *);
void windowSetParam(tagWINDOW_WORK *, s32, s32);
tagWINDOW_WORK *windowSearchID(s32);
void GSsndPlayNow(s32);
s32 heroGetStatus(s32, s32, s32);
u16 fightFloor_GetTurnCount(s32);
u32 fightFloor_GetFightTypeFightoutPokemonNum(s32);
u8 fightFloor_GetFightKindGetOkaneFlag(s32);
u8 fightFloor_GetFightKindOkanePoolFlag(s32);
void *fightTrainer_GetHeroPtr(FIGHT_TRAINER *);
u8 fightTrainer_GetOkaneBai(FIGHT_TRAINER *);
FIGHT_TRAINER *fightTargetGetPtrAsNowFightType(s32, FIGHT_TRAINER *);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER *);
s32 fightTrainerDB_GetKindDataId(u16);
u16 *fightTrainerKindDataBiosGetPtr(u16);
u16 fightTrainerKindDataBiosGetSyoukinBairitu(u16 *);
void *fightTrainer_GetFightPokemonPtr(FIGHT_TRAINER *, u16);
bool fightPokemonCheckValid(void *);
u8 figthPokemonGetLevel(void *);
u8 fightPokemon_GetCatchEntryFlag(void *);
f32 menuGetTotalTime(void);
f32 fightTimerAllGetNokoriTime(void);
f32 fightTimerCommandGetNokoriTime(void);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
}

static s32 menuFightStatus;
static u16 oldKeyInfo[2] = { 0, 0 };
static u8 _menuFightCheckTimeOut(void);
static u8 isImasugu(void);
static Pokemon *_menuFightGetPokemonPtr(FIGHT_TRAINER *, u32);
static void _menuFightKeyWait(GSinputDevice);
static u16 _menuFightGetLeftKeyInfo(long);
static u16 _menuFightGetRightStickInfo(long, bool);


static s32 getKane(void) {
    u16 bairitu;
    u8 okaneBai;
    FIGHT_TRAINER *hero;
    u8 maxLevel;
    u8 fightOutNum = fightFloor_GetFightTypeFightoutPokemonNum(0);
    int j;
    void *p;
    void *p2;
    FIGHT_TRAINER *target;
    int i;
    s32 mult;
    if (fightFloor_GetFightKindGetOkaneFlag(0) == 0) {
        return -1;
    }
    hero = fightFloorGetGcHeroFightTrainerPtr(0);
    if (hero == 0) {
        return -1;
    }
    if (fightTrainer_GetHeroPtr(hero) == 0) {
        return -1;
    }
    okaneBai = fightTrainer_GetOkaneBai(hero);
    target = fightTargetGetPtrAsNowFightType(9, hero);
    bairitu = fightTrainerKindDataBiosGetSyoukinBairitu(
        fightTrainerKindDataBiosGetPtr((u8)fightTrainerDB_GetKindDataId(
            fightTrainer_GetFightTrainerDataId(target))));
    maxLevel = 0;
    {
        for (i = 0; i < 6; i++) {
            p = fightTrainer_GetFightPokemonPtr(target, i);
            if (fightPokemonCheckValid(p)) {
                u8 level = figthPokemonGetLevel(p);
                if (maxLevel < level) {
                    maxLevel = level;
                }
            }
        }
    }
    {
        for (j = 0; j < 6; j++) {
            p2 = fightTrainer_GetFightPokemonPtr(hero, j);
            if (fightPokemonCheckValid(p2) && fightPokemon_GetCatchEntryFlag(p2) == 1) {
                u8 level = figthPokemonGetLevel(p2);
                if (maxLevel < level) {
                    maxLevel = level;
                }
            }
        }
    }
    if (fightFloor_GetFightKindOkanePoolFlag(0) == 0) {
        if (fightOutNum <= 1) {
            mult = 1;
        } else {
            mult = 2;
        }
    } else {
        mult = 4;
    }
    return (u16)mult * (bairitu * (maxLevel * okaneBai));
}


#define WZ(T, w, i, off) (*(T *)((u8 *)(w) + (i) + (off)))
#define WZ_SLOT(w) (*(s32 *)((u8 *)(w) + 0x40))

static void menuFightDrawIwaitStatusWaza(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite, Pokemon *pokemon, u8 index, u32 color) {
    if (pokemon != 0) {
        u32 slot = index;
        if (pokemonWazaCheckValid(pokemon, slot)) {
        void *waza = wazaGetStatus(0, pokemonGetStatus(pokemon, 0, 0x7F, slot), 1, 0);
        if (waza != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(waza));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4279);
        }
        }
    }
}

static s32 chkWazaNew(MENU_WAZA_STATUS *status, u8 index) {
    Pokemon *pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
    if (index == 0) {
        return -1;
    }
    if (pokemon != 0 && pokemon->isDarkPokemon()) {
        DarkPokemon *dark = pokemon->getDarkPokemon();
        if (dark != 0) {
            s32 waza = (u16)pokemonGetStatus(pokemon, 0, 0x7F, index);
            switch (waza) {
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
                goto fail;
            }
            return dark->isWazaNew(index - 1);
        }
    }
fail:
    return -1;
}

static u32 _menuFightIsUse(MENU_WAZA_STATUS *status, u16 index) {
    u16 sp8;
    s32 slot = WZ_SLOT(status);
    Pokemon *pokemon = fightOutPokemonGetPokemonPtr(slot);
    u8 result = fightOutPokemonCheckCanOutOkWazaBanme(slot, index, 1, &sp8);
    u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, index);
    u32 msg;
    void *data;
    if (result != 0) {
        msgctrlSetValue(0x11, slot);
        msg = (u32)wazaGetStatus(0, waza, 1, 0);
        msgctrlSetValue(0x28, GSmsgGetGSchar((void *)msg));
        s32 item = fightOutPokemonGetSoubiItemDataId(slot);
        fightFloorSetStatus(0, 0, 0x56, 0, (u16)item);
    }
    if (result == 6) msg = 0x4F42;
    else if (result == 5) {
        msgctrlSetValue(0x28, GSmsgGetGSchar(wazaGetStatus(0, sp8, 1, 0)));
        msg = 0x4F9A;
    } else if (result == 4) msg = 0x4EE9;
    else if (result == 3) msg = 0x4EE8;
    else if (result == 2) msg = 0x4EE7;
    else if (result == 1) msg = 0x4EE6;
    if (result != 0) return msg;
    return 0;
}

static u16 _menuFightGetLeftKeyInfo(long player) {
    u16 key = 0;
    int idx;
    u32 pressed;
    if (player != 0) {
        idx = 1;
    } else {
        idx = 0;
    }
    if (idx != 0) {
        pressed = GSinputButtonsPressed(2);
    } else {
        pressed = GSinputButtonsPressed(1);
    }
    if (pressed & 8) {
        key |= 1;
    }
    if (pressed & 4) {
        key |= 2;
    }
    if (pressed & 1) {
        key |= 4;
    }
    if (pressed & 2) {
        key |= 8;
    }
    if (key == oldKeyInfo[idx]) {
        key = 0;
    } else {
        oldKeyInfo[idx] = key;
    }
    return key;
}

#define ABSI(v) ((v) < 0 ? -(v) : (v))
#define FABSF(v) ((v) > 0.0f ? (v) : -(v))

static u16 _menuFightGetRightStickInfo(long player, bool edge) {
    u16 key = 0;
    s8 y;
    s8 x;
    f32 ang;
    if (player != 0) {
        player = 1;
    } else {
        player = 0;
    }
    if (player == 0) {
        y = GSinputGetRightStickYData(1, 0);
        x = GSinputGetRightStickXData(1, 0);
    } else {
        y = GSinputGetRightStickYData(2, 0);
        x = GSinputGetRightStickXData(2, 0);
    }
    if (ABSI(x) > 0x20 || ABSI(y) > 0x20) {
        ang = (f32)atan2((f64)x, (f64)y);
        if (FABSF(ang) < 0.7853982f) {
            key |= 2;
        } else if (FABSF(ang) > 2.3561945f) {
            key |= 1;
        }
        if (0.7853982f < FABSF(ang) && FABSF(ang) < 2.3561945f) {
            if (ang < 0.0f) {
                key |= 4;
            } else {
                key |= 8;
            }
        }
        if (edge) {
            if (key == oldKeyInfo[player]) {
                key = 0;
            } else {
                oldKeyInfo[player] = key;
            }
        }
    } else {
        oldKeyInfo[player] = 0;
    }
    return key;
}

extern "C" {
void menuFightDrawTurn(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    switch (sprite->id) {
    case 2:
        msgctrlSetValue(0x5F, fightFloor_GetTurnCount(0));
        if (fightFloor_GetTurnCount(0) > 9) {
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, -1, 0x4351);
        } else {
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 8, 0, -1, 0x4351);
        }
        break;
    case 0x27C:
    case 0x295:
    case 0x2D3:
        if (window->selected == 0) {
            menuSubDrawCursorBack(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, 0xFF, 1);
        }
        break;
    case 0x27D:
    case 0x296:
    case 0x2D4:
        if (window->selected == 1) {
            menuSubDrawCursorBack(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, 0xFF, 1);
        }
        break;
    }
}

void menuFightDrawKane(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    s32 kane = getKane();
    winSpriteSetDisp(sprite, 0);
    if (kane != -1) {
        if (sprite->id == 6) {
            s16 w;
            msgctrlSetValue(0x50, kane + heroGetStatus(0, 0xC, 0));
            w = GSmsgGetRect(0x434E) >> 16;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), sprite->width - w, 0, -1, 0x434E);
        }
        winSpriteSetDisp(sprite, 1);
    }
}

void menuFightDrawTimer(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    static u16 buff[8];
    static u16 half_digit_code[16] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                                       0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46 };
    s32 color;
    switch (sprite->id) {
    case 0xA7:
    case 0xA8:
    case 0xA9:
    case 0xAA:
        winSpriteSetDisp(sprite, 0);
        if (0.5f <= menuGetTotalTime()) {
            winSpriteSetDisp(sprite, 1);
        }
        break;
    case 0xAB:
        break;
    case 0xAC: {
        s32 t = windowGetParam(window, 0);
        s32 v = t / 60;
        buff[0] = half_digit_code[v / 10];
        buff[1] = half_digit_code[v % 10];
        buff[2] = 0;
        msgctrlSetValue(0x37, (u32)buff);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, menuSubCalcColor(window, sprite), 0x4276);
        break;
    }
    case 0xAD: {
        s32 t = windowGetParam(window, 0);
        s32 v = t - t / 60 * 60;
        buff[0] = half_digit_code[v / 10];
        buff[1] = half_digit_code[v % 10];
        buff[2] = 0;
        msgctrlSetValue(0x37, (u32)buff);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, menuSubCalcColor(window, sprite), 0x4276);
        break;
    }
    case 0xAF: {
        msgctrlSetValue(0x5F, windowGetParam(window, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, menuSubCalcColor(window, sprite), 0x4357);
        break;
    }
    }
}

s32 menuFightCtrlTimer(tagWINDOW_WORK *window) {
    static s32 oldTime = 0;
    if (window->phase == 0) {
        oldTime = 0;
        if (window->menu == 0x9C) {
            windowSetParam(window, 0, (s32)fightTimerAllGetNokoriTime());
        }
    }
    switch (window->menu) {
    case 0x9C:
        if (menuIsCheck(0x9D) == 0) {
            windowSetParam(window, 0, (s32)fightTimerAllGetNokoriTime());
        }
        break;
    case 0x9D: {
        s32 t = (s32)fightTimerCommandGetNokoriTime();
        windowSetParam(window, 0, t);
        if (oldTime != t) {
            if (t <= 5) {
                if (t != 0) {
                    GSsndPlayNow(0x441);
                } else if (oldTime == 1) {
                    GSsndPlayNow(0x13);
                }
            }
            oldTime = t;
            if (menuIsCheck(0x9C)) {
                s32 total = (s32)fightTimerAllGetNokoriTime();
                windowSetParam(windowSearchID(0x9C), 0, total);
            }
        }
        break;
    }
    }
    return 0;
}
}

extern "C" {
void menuFightButtonTimeOutCheck(tagWINDOW_WORK *);
void menuFightButtonSecretKousan(tagWINDOW_WORK *window) {
    menuButtonNormal(window);
    menuFightButtonTimeOutCheck(window);
}

void menuFightDrawPP(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    u32 color;
    MENU_WAZA_STATUS *status;
    MenuCursor cursor;
    s16 x;
    status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    color = menuSubCalcColor(window, sprite);
    cursor = windowGetCursor(window->menu);
    x = sprite->width - (s16)(GSmsgGetRect(0x42C4) >> 16) * 5;
    GSmsgPrint2(winSpriteGetLayerID(window, sprite), x, 0, color, 0x42C4);
    if (cursor.y >= 0 && cursor.y < 4) {
        s32 off = cursor.y * 0xC;
        if (((MenuFightWazaEntry *)&status->raw[4])[cursor.y].name != 0) {
            s32 waza;
            Pokemon *pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
            if (pokemon != 0) {
                waza = (u16)pokemonGetStatus(pokemon, 0, 0x7F, window->selected);
            } else {
                waza = 0;
            }
            waza = (u16)waza;
            switch (waza) {
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
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->height, color, 0x3AF5);
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x3AF5);
                break;
            case 0x176:
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->height, color, 0x3AD1);
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x3AD1);
                break;
            default:
                msgctrlSetValue(0x5F, status->raw[off + 0xF]);
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->height, color, 0x4351);
                msgctrlSetValue(0x5F, status->raw[off + 0xE]);
                GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4351);
                break;
            }
        }
    }
}

struct WazaRowB {
    u16 type;
    u16 pad;
    u32 pad2[2];
};

void menuFightDrawType(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    MenuFightWazaLayout *status = (MenuFightWazaLayout *)windowGetAllocPtr(window);
    s16 cursorIndex = windowGetCursor(window->menu).y;
    if (cursorIndex >= 0 && cursorIndex < 4) {
        s32 off = cursorIndex * 0xC;
        if (status->entries[cursorIndex].name != 0) {
            s32 waza;
            Pokemon *pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
            if (pokemon != 0) {
                waza = (u16)pokemonGetStatus(pokemon, 0, 0x7F, window->selected);
            } else {
                waza = 0;
            }
            waza = (u16)waza;
            switch (waza) {
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
                return;
            }
            {
                u16 type = status->entries[cursorIndex].type;
                windowDrawSprite(0, 2, window, zokuseiBiosGetSpriteID(type), 0, winSpriteGetLayerID(window, sprite));
            }
        }
    }
}

void menuFightDrawNew(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    u8 index;
    s32 r;
    winSpriteSetDisp(sprite, 0);
    index = 0;
    switch (sprite->id) {
    case 0x10B:
        break;
    case 0x10E:
        index = 1;
    case 0x10C:
        index += 1;
    case 0x10D:
        index += 1;
        break;
    }
    r = chkWazaNew(status, index);
    if (r != -1 && r == 0) {
        winSpriteSetDisp(sprite, 1);
    }
}

u8 menuPokemonCheckPokemonChange(s32 *outInfo, FIGHT_TRAINER *trainer, u32 index) {
    s32 *other;
    u8 result;
    u32 target;
    u8 check;
    result = fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, outInfo, &other);
    if (result == 1) {
        msgctrlSetValue(0xD, fightOutPokemonGetNicknamePtr(outInfo));
        winMsgOpen(1, 0x4FC8, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    }
    if (result == 2) {
        fightFloorSetStatus(0, 0, 0x57, 0, fightOutPokemonGetTokuseiDataId(other));
        msgctrlSetValue(0xD, fightOutPokemonGetNicknamePtr(other));
        msgctrlSetValue(0xE, fightOutPokemonGetNicknamePtr(outInfo));
        winMsgOpen(1, 0x4F08, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    }
    if (trainer == 0) {
        trainer = fightFloorGetGcHeroFightTrainerPtr(0);
    }
    if (trainer == 0) {
        return 0;
    }
    target = (u32)fightTrainerGetValidFightPokemonPtr(trainer, index);
    if (target == 0) {
        return 0;
    }
    check = fightTrainerCheckCanIrekaeFightPokemon(trainer, target);
    if (check == 1) {
        msgctrlSetValue(0xD, fightPokemonGetNicknamePtr(target));
        winMsgOpen(1, 0x4FCB, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    } else if (check == 2) {
        msgctrlSetValue(0xD, fightPokemonGetNicknamePtr(target));
        winMsgOpen(1, 0x4FC9, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    } else if (check == 3) {
        msgctrlSetValue(0xD, fightPokemonGetNicknamePtr(target));
        winMsgOpen(1, 0x4FCA, 1, 0);
        _menuFightKeyWait(GSINPUT_DEVICE_1);
        winMsgClose(1);
        return 0;
    } else if (check == 0) {
        return 1;
    } else {
        GSlogWrite("%s: \x97\x5c\x92\xe8\x8a\x4f\x82\xcc\x8f\xf0\x8c\x8f\x82\xaa\x8b\x41\x82\xc1\x82\xc4\x82\xab\x82\xc4\x82\xa2\x82\xdc\x82\xb7\n", __FUNCTION__);
        return 0;
    }
}

s32 menuFightWazaButton(tagWINDOW_WORK *window) {
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    FightWazaWork *work = windowGetFreeWork(window);
    Pokemon *pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
    u16 key = windowGetKeyInfo()->unk4;
    switch ((s32)work->mode) {
    case 0:
        if (key & 0xC0) {
            if (pokemonGetStatus(pokemon, 0, 0xC2, 0) != 0 || fightKind_CheckFightKind(0xD) != 0) {
                GSsndPlayNow(0x13);
            } else if (fightFloorGetStatus(0, 0, 0x32, 0) != 0 || fightKind_CheckFightKind(0xF) != 0) {
                work->saved = window->selected;
                if (work->saved == 0) {
                    window->selected = 1;
                } else {
                    window->selected = 0;
                }
                if (menuGetSelectItemNum(window->menu) <= 1) {
                    window->selected = 0;
                }
                windowCreateCursorSprite(window);
                work->mode = 1;
            }
        } else if (pokemon != 0 && (u16)pokemonGetStatus(pokemon, 0, 0x7F, (u16)window->selected) == 0x176) {
            if (windowGetKeyInfo()->unk4 & 0x20) {
                window->finished = 1;
                window->cancelled = 1;
            }
        } else {
            menuButtonNormal(window);
        }
        break;
    case 1:
        if (key & 0xD0) {
            if (pokemon != 0) {
                s32 saved;
                pokemonWazaReplace(pokemon, (s8)work->saved, (u16)window->selected);
                saved = WZ_SLOT(status);
                pokemonToMenuWazaStatus(pokemon, status);
                WZ_SLOT(status) = saved;
            }
            work->saved = -1;
            work->mode = 0;
        } else if (key & 0x20) {
            work->saved = -1;
            work->mode = 0;
        }
        break;
    }
    return 0;
}

void menuFightCtrlTarget(void) {
}

s32 menuFightGetStatus(void) {
    return menuFightStatus;
}

void menuFightSetStatus(s32 status) {
    menuFightStatus = status;
}

void menuFightCloseCheckCountDown(void) {
    menuIsCheck(0x9D);
}

void menuFightCloseCheckTotalTimer(void) {
    menuIsCheck(0x9C);
}

void menuFightOpenGBAIrekae(s32 a, s32 b, s32 c) {
    gbaCommandRequestAction(a, b, c, 1);
}

void menuFightOpenGBAMain(s32 a, s32 b, s32 c) {
    gbaCommandRequestAction(a, b, c, 0);
}

void menuFightOpenTimeup(void) {
    menuOpen(0x10B, 0);
}

void menuFightCloseCountDown(void) {
    menuCloseCustom(0x9D, 0, 0);
}

void menuFightCloseTotalTimer(void) {
    menuCloseCustom(0x9C, 0, 0);
}

void menuFightOpenCountDown(void) {
    menuOpenCustom(0x9D, -1, 0, 0, 0, 0);
}

void menuFightOpenTotalTimer(void) {
    menuOpenCustom(0x9C, -1, 0, 0, 0, 0);
}

s32 menuFightChkOpenBall(s32 id) {
    if ((id == 0x44 || id == 0x45) && fightKind_CheckFightKind(0xC)) {
        return 0;
    }
    return 1;
}

s32 menuFightCtrlSecretPokemonTop(tagWINDOW_WORK *window) {
    windowGetParam(window, 0);
    windowGetParam(window, 1);
    windowGetParam(window, 2);
    return 0;
}

void menuFightSetSeq(void) {
    winSeqSetMenu(0x37, 0x1A5);
    winSeqSetMenu(0x40, 0x1A5);
    winSeqSetMenu(0x38, 0x1A9);
    winSeqSetMenu(0x41, 0x1A9);
}

s32 menuFightCtrlSecretMain(tagWINDOW_WORK *window) {
    void *dst;
    if (window->phase == 0 && (dst = windowAllocMemory(window, 0x18)) != 0) {
        memcpy(dst, (void *)window->parameters[0], 0x18);
    }
    return 0;
}

s32 menuFightCtrlSecretWazaTop(tagWINDOW_WORK *window) {
    void *dst;
    if (window->phase == 0 && (dst = windowAllocMemory(window, 0x48)) != 0) {
        memcpy(dst, (void *)window->parameters[0], 0x48);
    }
    windowGetAllocPtr(window);
    return 0;
}

s32 menuFightCtrlBall(tagWINDOW_WORK *window) {
    FightWazaWork *work = windowGetFreeWork(window);
    if (window->phase == 0) {
        memcpy(work, (void *)windowGetParam(window, 0), 6);
    }
    return 0;
}

s32 menuFightChkSeq(void) {
    if (winSeqCheckMove(0x37)) {
        return 1;
    }
    if (winSeqCheckMove(0x40)) {
        return 1;
    }
    if (winSeqCheckMove(0x38)) {
        return 1;
    }
    return winSeqCheckMove(0x41) != 0;
}

s32 menuFightCloseTarget(s32 arg) {
    if (menuIsCheck(0x5C)) {
        menuCloseCustom(0x5C, 0, arg);
    }
    if (menuIsCheck(0x91)) {
        menuCloseCustom(0x91, 0, arg);
    }
    return 0;
}

s32 menuFightGetKeyWaitMenuId(FIGHT_TRAINER *trainer, u16 index) {
    s32 id = 0x98;
    switch (fightMenuGetFightTrainerPtrToStatusMenuId(trainer, index)) {
    case 0x42:
        id = 0x98;
        break;
    case 0x43:
        id = 0x99;
        break;
    case 0x44:
        id = 0x9A;
        break;
    case 0x45:
        id = 0x9B;
        break;
    }
    return id;
}

s32 menuFightCloseTop(s32 arg) {
    if (menuIsCheck(0x3A)) {
        menuCloseCustom(0x3A, 0, arg);
    }
    if (menuIsCheck(0x8E)) {
        menuCloseCustom(0x8E, 0, arg);
    }
    return 0;
}

s32 menuFightCloseWaza(s32 arg) {
    if (menuIsCheck(0x39)) {
        menuCloseCustom(0x39, 0, arg);
    }
    if (menuIsCheck(0x94)) {
        menuCloseCustom(0x94, 0, arg);
    }
    if (menuIsCheck(0x93)) {
        menuCloseCustom(0x93, 0, arg);
    }
    if (menuIsCheck(0x90)) {
        menuCloseCustom(0x90, 0, arg);
    }
    return 0;
}

void menuFightCloseAll(void) {
    s32 ids[28] = { 0x37, 0x40, 0x38, 0x41, 0x69, 0x6A, 0x39, 0x3A, 0x42, 0x43, 0x44, 0x45, 0x98, 0x99,
                    0x9A, 0x9B, 0x9D, 0xB5, 0x9C, 0x10B, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0x11C, 0x11D };
    s32 id;
    u8 i;
    for (i = 0; i < 0x1C; i++) {
        id = ids[i];
        if (menuIsCheck(id) == 1) {
            menuCloseCustom(id, 0, 0);
        }
    }
}

void menuFightButtonSecretMain(tagWINDOW_WORK *window) {
    s32 sel;
    u16 key = windowGetKeyInfo()->unk4;
    sel = -1;
    if (key & 0x10) {
        sel = 0;
    } else if (key & 0x20) {
        sel = 2;
    } else if (key & 0x800) {
        sel = 3;
    } else if (key & 0x200) {
        window->finished = 1;
        window->cancelled = 1;
        window->value = -1;
    }
    if (sel >= 0) {
        window->finished = 1;
        window->value = sel;
    }
    menuFightButtonTimeOutCheck(window);
}

void menuFightDrawSecretSelect(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    s32 show = 1;
    if (window->menu == 0x92) {
        u8 has = (u8)(s32)(windowGetParam(window, 2) != 0);
        if (has == 0) {
            show = 0;
        }
    }
    switch (sprite->id) {
    case 33:
    case 35:
        winSpriteSetDisp(sprite, show);
    case 34:
        return;
    }
}

void menuFightDrawTargetCursor(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    if (menuItemBiosGetSelectFlag(window->menu, sprite->id)) {
        if (sprite->id == menuGetCursorItemID(window->menu)) {
            winSpriteSetDisp(sprite, 1);
            return;
        }
        winSpriteSetDisp(sprite, 0);
        return;
    }
    winSpriteSetDisp(sprite, 0);
}
}

static Pokemon *_menuFightGetPokemonPtr(FIGHT_TRAINER *trainer, u32 index) {
    Pokemon *pokemon;
    void *valid;
    if (index >= 6) {
        return 0;
    }
    if (trainer == 0) {
        trainer = fightFloorGetGcHeroFightTrainerPtr(0);
    }
    if (trainer == 0) {
        return 0;
    }
    valid = fightTrainerGetValidFightPokemonPtr(trainer, index);
    if (valid == 0) {
        return 0;
    }
    pokemon = (Pokemon *)pokemonGetStatus(valid, 0, 0xCC, 0);
    if (pokemonCheckValid(pokemon) == 0) {
        return 0;
    }
    return pokemon;
}

static void _menuFightKeyWait(GSinputDevice device) {
    f32 timer = 0.0f;
    u32 changed;
    u32 pressed;
    if (isImasugu()) {
        while (timer < 2.5f) {
            timer += timeGetLastFrameSec();
            GSthreadSwitch();
        }
        return;
    }
    while (changed = GSinputButtonsChanged(device), pressed = GSinputButtonsPressed(device), (pressed & changed & 0x300) == 0) {
        if (_menuFightCheckTimeOut()) {
            break;
        }
        GSthreadSwitch();
    }
}

extern "C" void menuFightButtonTimeOutCheck(tagWINDOW_WORK *window) {
    if (_menuFightCheckTimeOut()) {
        window->finished = 1;
        window->cancelled = 1;
    }
}

static u8 isImasugu(void) {
    if (fightKind_CheckFightKind(0xA)) {
        return 1;
    }
    return fightKind_CheckFightKind(0x11) != 0;
}

static u8 _menuFightCheckTimeOut(void) {
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
            return 1;
        }
        if (fightGetFightResultId() == 1) {
            return 1;
        }
    }
    return 0;
}

static void menuFightSetSeqOut(void) {
    winSeqSetMenu(0x37, 0x19D);
    winSeqSetMenu(0x40, 0x19D);
    winSeqSetMenu(0x38, 0x1A1);
    winSeqSetMenu(0x41, 0x1A1);
    menuFightSetStatus(1);
}

static inline s32 targetSecretSprite(s32 id) {
    switch (id) {
    case 0x37:
        return 0x42;
    case 0x40:
        return 0x41;
    case 0x38:
        return 0x40;
    case 0x41:
        return 0x3F;
    default:
        return 0;
    }
}

extern "C" void menuFightDrawTargetSecret(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    FightTargetEntry *entries = (FightTargetEntry *)windowGetParam(window, 0);
    s32 item;
    for (s32 i = 0; i < 4; entries++, i++) {
        switch (entries->id) {
        case 0x37: item = 0x42; break;
        case 0x40: item = 0x41; break;
        case 0x38: item = 0x40; break;
        case 0x41: item = 0x3F; break;
        default: item = 0; break;
        }
        if (item == sprite->id) {
            winSpriteSetDisp(sprite, 1);
            return;
        }
    }
    winSpriteSetDisp(sprite, 0);
}

extern "C" void menuFightDrawTargetI(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    FightTargetEntry *entries = (FightTargetEntry *)windowGetParam(window, 0);
    s32 item;
    s32 color = menuSubCalcColor(window, sprite);
    for (s32 i = 0; i < 4; ++i) {
        switch (entries[i].id) {
        case 0x37:
            switch (window->menu) {
            case 0xA0: item = 0x210; break;
            case 0xA3: item = 0x233; break;
            }
            switch (sprite->id) {
            case 0x215:
            case 0x238:
                msgctrlSetValue(0x37, entries[i].value);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
                return;
            }
            break;
        case 0x40:
            switch (window->menu) {
            case 0xA0: item = 0x212; break;
            case 0xA3: item = 0x235; break;
            }
            switch (sprite->id) {
            case 0x217:
            case 0x23a:
                msgctrlSetValue(0x37, entries[i].value);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
                return;
            }
            break;
        case 0x38:
            switch (window->menu) {
            case 0xA0: item = 0x211; break;
            case 0xA3: item = 0x234; break;
            }
            switch (sprite->id) {
            case 0x216:
            case 0x239:
                msgctrlSetValue(0x37, entries[i].value);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
                return;
            }
            break;
        case 0x41:
            switch (window->menu) {
            case 0xA0: item = 0x213; break;
            case 0xA3: item = 0x236; break;
            }
            switch (sprite->id) {
            case 0x218:
            case 0x23b:
                msgctrlSetValue(0x37, entries[i].value);
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
                return;
            }
            break;
        default: item = 0; break;
        }
        if (item == sprite->id) {
            winSpriteSetDisp(sprite, 1);
            return;
        }
    }
    winSpriteSetDisp(sprite, 0);
}

struct FightTargetWork {
    FightTargetEntry entries[4];
    u8 reserved30;
    u8 mode;
    u8 reserved32[2];
    s32 pokemon;
};
extern "C" {
void *fightFloorGetNowPtr(void);
void *fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void *, s32);
void menuItemBiosSetSelectFlag(s32, s32, s32);
s32 menuGetCursorFromItemID(s32, s32);

s32 menuFightOpenTarget(FightTargetWork *work, s32 *cursor, s32 wait) {
    s32 result;
    s32 menu;
    s32 other;
    FightTargetEntry *entry;
    s32 item;
    s32 i;
    s32 selected;
    s32 opened;
    if (work->mode == 0) {
        if (fightKind_CheckFightKind(13)) {
            result = 0;
        } else if (isImasugu()) {
            result = fightFloorGetStatus(0, 0, 0x35, 0);
            if (fightFloorGetFightOutPokemonPtrToFightTrainerPtr(fightFloorGetNowPtr(), work->pokemon) == (void *)(result + 0x64)) {
                menu = 0xA0;
                other = 0xA2;
            } else {
                menu = 0xA3;
                other = 0x9F;
            }
            result = menuOpenCustom(menu, 0, cursor, 0, wait, 1, work);
            menuCloseCustom(menu, 2, wait);
            if (menuIsCheck(other)) menuClose(other);
        } else {
            menuItemBiosSetSelectFlag(0x5C, 0x138, 0);
            menuItemBiosSetSelectFlag(0x5C, 0x139, 0);
            menuItemBiosSetSelectFlag(0x5C, 0x13A, 0);
            menuItemBiosSetSelectFlag(0x5C, 0x13B, 0);
            result = (s32)work->entries;
            for (menu = 0; menu < 4; result += 12, menu++) {
                switch (((FightTargetEntry *)result)->id) {
                case 0x37: item = 0x138; break;
                case 0x40: item = 0x139; break;
                case 0x38: item = 0x13A; break;
                case 0x41: item = 0x13B; break;
                default: item = 0; break;
                }
                if (item) menuItemBiosSetSelectFlag(0x5C, item, 1);
            }
            selected = menuGetCursorFromItemID(0x5C, 0x13A);
            if (selected == -1) {
                selected = menuGetCursorFromItemID(0x5C, 0x13B);
                if (selected == -1) selected = 0;
            }
            opened = menuOpenCustom(0x5C, 0, &selected, 0, wait, 1, work);
            switch (opened) {
            case 0x13A: item = 0x38; break;
            case 0x13B: item = 0x41; break;
            case 0x138: item = 0x37; break;
            case 0x139: item = 0x40; break;
            default: item = -1; break;
            }
            result = -1;
            entry = work->entries;
            for (i = 0; i < 4; entry++, i++) {
                if (item == entry->id) {
                    result = i;
                    if (fightKind_CheckFightKind(15)) menuClose(0xB5);
                    break;
                }
            }
        }
    } else if (work->mode == 1) {
        if (menuIsCheck(0x92)) menuCloseCustom(0x92, 0, 1);
        result = menuOpenCustom(0x91, 0, cursor, 0, wait, 1, work);
    }
    return result;
}
}

extern "C" s32 menuPokemonGetJoutaiSpriteID(Pokemon *, s32);
extern "C" u8 menuSubGetPokemonSexForFightDisp(Pokemon *);
extern "C" void menuFightDrawSecretPokemon(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    s32 index = -1;
    FIGHT_TRAINER *trainer = (FIGHT_TRAINER *)windowGetParam(window, 0);
    switch (sprite->id) {
    case 0x8D: case 0x94: case 0x9A: index = 0; break;
    case 0x8E: case 0x95: case 0x9B: index = 1; break;
    case 0x8F: case 0x96: case 0x9C: index = 2; break;
    case 0x90: case 0x97: case 0x9D: index = 3; break;
    case 0x91: case 0x98: case 0x9E: index = 4; break;
    case 0x92: case 0x99: case 0x9F: index = 5; break;
    }
    if (index < 0) return;
    Pokemon *pokemon = _menuFightGetPokemonPtr(trainer, (u16)index);
    if (pokemon == 0) return;
    u32 color = menuSubCalcColor(window, sprite);
    switch (sprite->id) {
    case 0x9A: case 0x9B: case 0x9C: case 0x9D: case 0x9E: case 0x9F: {
        s32 icon = menuPokemonGetJoutaiSpriteID(pokemon, 1);
        windowDrawSprite(0, 0, window, icon, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0x94: case 0x95: case 0x96: case 0x97: case 0x98: case 0x99: {
        s16 labelWidth = (GSmsgGetRect(0x42D5) >> 16) + 2;
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x42D5);
        index = (s16)((sprite->width - labelWidth - (s16)(GSmsgGetRect(0x42C4) >> 16)) / 2);
        s32 layer = winSpriteGetLayerID(window, sprite);
        index = labelWidth + index;
        GSmsgPrint2(layer, index, 0, color, 0x42C4);
        msgctrlSetValue(0x5F, (s16)pokemonGetStatus(pokemon, 0, 0x83, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, index, sprite->height, color, 0x4357);
        msgctrlSetValue(0x5F, (s16)pokemonGetStatus(pokemon, 0, 0x87, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4357);
        break;
    }
    case 0x8D: case 0x8E: case 0x8F: case 0x90: case 0x91: case 0x92: {
        s32 name = pokemonGetStatus(pokemon, 0, 0x77, 0);
        msgctrlSetValue(0x37, name);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
        u32 sex;
        switch (menuSubGetPokemonSexForFightDisp(pokemon)) {
        case 0: sex = 0x9C5; break;
        case 1: sex = 0x9C6; break;
        case 2: default: sex = 0; break;
        }
        if (sex != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar((void *)sex));
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0x7E, 0, color, 0x4276);
        }
        break;
    }
    }
}

extern "C" void menuFightDrawSecretWazaDoc(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    Pokemon *pokemon;
    s32 item;
    s16 half;
    u32 color;
    u16 waza;
    tagWINDOW_WORK *source;
    s32 *selected;
    s16 label;
    MENU_WAZA_STATUS *status;
    item = -1;
    source = windowSearchID(windowGetParam(window, 0));
    if (source == 0) return;
    status = (MENU_WAZA_STATUS *)windowGetAllocPtr(source);
    if (status == 0) return;
    selected = (s32 *)windowGetParam(window, 1);
    if (*selected < 0) return;
    pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
    if (pokemon == 0) return;
    waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)*selected);
    color = menuSubCalcColor(window, sprite);
    switch (sprite->id) {
    case 0x7A: case 0x7B: case 0x7D: case 0x7C:
        switch (sprite->id) {
        case 0x7A: item = 0; break;
        case 0x7B: item = 1; break;
        case 0x7D: item = 2; break;
        case 0x7C: item = 3; break;
        }
        if (item == *selected) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    case 0x253: case 0x254: case 0x256: case 0x255:
        switch (sprite->id) {
        case 0x253: item = 0; break;
        case 0x254: item = 1; break;
        case 0x256: item = 2; break;
        case 0x255: item = 3; break;
        }
        if (item == *selected) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    case 0x269: case 0x26A: case 0x26C: case 0x26B:
        switch (sprite->id) {
        case 0x269: item = 0; break;
        case 0x26A: item = 1; break;
        case 0x26C: item = 2; break;
        case 0x26B: item = 3; break;
        }
        if (item == *selected) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    case 0x79: case 0x252: case 0x268: {
        u16 type = ((MenuFightWazaEntry *)(status->raw + 4))[*selected].type;
        windowDrawSprite(0, 0, window, zokuseiBiosGetSpriteID(type), 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0x81: case 0x25B: case 0x271: {
        u32 message = (u32)wazaGetStatus(0, waza, 0x22, 0);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, message);
        break;
    }
    case 0x7F: case 0x25A: case 0x270: {
        u32 power = (u32)wazaGetStatus(0, waza, 6, 0);
        if (power <= 1) {
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x3AF6);
        } else {
            msgctrlSetValue(0x5F, power);
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4351);
        }
        break;
    }
    case 0x7E: case 0x259: case 0x26F: {
        u32 accuracy = (u32)wazaGetStatus(0, waza, 7, 0);
        if (accuracy <= 1) {
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x3AF6);
        } else {
            msgctrlSetValue(0x5F, accuracy);
            GSmsgPrintRight(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4351);
        }
        break;
    }
    case 0x80: case 0x257: case 0x26D:
        msgctrlSetValue(0x37, ((MenuFightWazaEntry *)(status->raw + 4))[*selected].name);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4276);
        break;
    case 0x82: case 0x258: case 0x26E: {
        label = GSmsgGetRect(0x42D1) >> 16;
        s16 width = sprite->width - label;
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x42D1);
        half = (s16)((width - (s16)(GSmsgGetRect(0x42C4) >> 16)) / 2);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), label + half, 0, color, 0x42C4);
        msgctrlSetValue(0x5F, ((MenuFightWazaEntry *)(status->raw + 4))[*selected].maxPP);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), label, 0, half, sprite->height, color, 0x4357);
        msgctrlSetValue(0x5F, ((MenuFightWazaEntry *)(status->raw + 4))[*selected].currentPP);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), label, 0, width, sprite->height, color, 0x4357);
        break;
    }
    }
}

extern "C" tagSPRITE_WORK *windowSearchItemID(tagWINDOW_WORK *, s32);
extern "C" s32 menuFightMainCtrl(tagWINDOW_WORK *window) {
    u8 *work;
    tagSPRITE_WORK *sprite;
    if (window->phase == 0) {
        work = (u8 *)windowAllocMemory(window, 0x18);
        if (work) memcpy(work, (void *)window->parameters[0], 0x18);
        if (fightKind_CheckFightKind(15) || fightKind_CheckFightKind(14)) {
            sprite = windowSearchItemID(window, 0x136);
            sprite->message = 0x429F;
            menuItemBiosSetSelectFlag(window->menu, 0x132, 1);
        } else if (fightKind_CheckFightKind(13)) {
            sprite = windowSearchItemID(window, 0x135);
            sprite->message = 0x429F;
            sprite = windowSearchItemID(window, 0x134);
            sprite->message = 0x1389;
            sprite = windowSearchItemID(window, 0x136);
            sprite->message = 0x443C;
            menuItemBiosSetSelectFlag(window->menu, 0x132, 1);
        } else if (fightKind_CheckFightKind(6) || fightKind_CheckFightKind(7)) {
            sprite = windowSearchItemID(window, 0x135);
            sprite->message = 0x429F;
            sprite = windowSearchItemID(window, 0x136);
            sprite->message = 0;
            menuItemBiosSetSelectFlag(window->menu, 0x132, 0);
        } else if (work[0x16]) {
            sprite = windowSearchItemID(window, 0x135);
            sprite->message = 0x429D;
            sprite = windowSearchItemID(window, 0x136);
            sprite->message = 0x42A0;
            menuItemBiosSetSelectFlag(window->menu, 0x132, 1);
        } else {
            sprite = windowSearchItemID(window, 0x135);
            sprite->message = 0x429F;
            sprite = windowSearchItemID(window, 0x136);
            sprite->message = 0;
            menuItemBiosSetSelectFlag(window->menu, 0x132, 0);
        }
    }
    work = (u8 *)windowGetAllocPtr(window);
    switch (menuGetCursorItemID(window->menu)) {
    case 0x12C: window->value = 0; break;
    case 0x12E:
        if ((fightKind_CheckFightKind(13) || !work[0x16]) && !fightKind_CheckFightKind(15) && !fightKind_CheckFightKind(14)) window->value = 3;
        else window->value = 1;
        break;
    case 0x130:
        if (fightKind_CheckFightKind(13)) window->value = 1;
        else window->value = 2;
        break;
    case 0x132:
        window->value = 3;
        if (fightKind_CheckFightKind(13)) window->value = 0x7F;
        break;
    default: window->value = -1; break;
    }
    return 0;
}

class bingo_bios {
public:
    static u8 getStaticBall();
};
extern "C" {
void fightMenuCloseInfoMenu(s32);
void fightMenuOpenInfoMenu(s32);
void *fightEncountDataBiosGetPtr(s32);
u8 fightEncountDataBiosGetDiskId(void *);
s32 menuBattleDiskOpenDocPush(s32);
u8 GSgfxVideoGetVsyncRate();
void menuCreateOffScreen(f32, f32);
void menuReleaseOffScreen(f32);
void menuOffScreenSetPriority(s32);
void menuOffScreenFadeSync(s32);
void GSfloorPush(s32);
void floorSetFadeScript(s32, s32);
void floorWaitForChange();
u8 fightFloorIsNowEncountSnatchOnly(s32);
void fightSeqEventKurein(s32);
s32 menuFightOpenTop(s32, u8 *work, s32 *cursor, s32 wait) {
    s32 result;
    s32 response;
    menuFightSetStatus(0);
    if (isImasugu()) return 0;
    if (fightKind_CheckFightKind(15)) menuOpen(0xB5, 0);
    for (;;) {
        switch (work[0x17]) {
        case 0: result = menuOpenCustom(0x3A, 0, cursor, 0, wait, 1, work); break;
        case 1: result = menuOpenCustom(0x8E, 0, cursor, 0, wait, 1, work); break;
        }
        if (!work[0x16] || fightKind_CheckFightKind(13) || fightKind_CheckFightKind(15) || fightKind_CheckFightKind(14) || fightKind_CheckFightKind(6) || fightKind_CheckFightKind(7)) {
            if (result == 3) {
                s32 selected = 0;
                menuFightSetSeqOut();
                menuFightCloseTop(1);
                if (fightKind_CheckFightKind(15)) menuClose(0xB5);
                fightMenuCloseInfoMenu(1);
                if (fightKind_CheckFightKind(15)) {
                    response = menuBattleDiskOpenDocPush(fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(14)));
                } else if (fightKind_CheckFightKind(14)) {
                    response = menuBattleDiskOpenDocPush(fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(13)));
                } else {
                    response = menuOpenCustom(0x8F, 0, &selected, 0, 1, 0);
                    menuCloseCustom(0x8F, 0, 1);
                }
                if (response != 0x31) {
                    fightMenuOpenInfoMenu(-1);
                    if (fightKind_CheckFightKind(15)) menuOpen(0xB5, 0);
                    continue;
                }
            }
        } else if (work[0x16] && (result == 1 || result == 2)) {
            menuFightSetSeqOut();
        }
        if (fightKind_CheckFightKind(15) && (result == 1 || result == 2)) menuClose(0xB5);
        if (fightKind_CheckFightKind(13)) {
            if (!bingo_bios::getStaticBall() && result == 1) {
                menuFightCloseTop(1);
                winMsgOpen(4, 0x5012, 1, 0);
                winMsgClose(1);
                continue;
            }
            if (result == 0x7F) {
                menuFightSetSeqOut();
                menuFightCloseTop(1);
                fightMenuCloseInfoMenu(1);
                menuCreateOffScreen(8.0f / GSgfxVideoGetVsyncRate(), 50.0f);
                menuOffScreenSetPriority(0);
                menuOffScreenFadeSync(1);
                GSfloorPush(0x38B);
                floorSetFadeScript(0, 0);
                floorWaitForChange();
                menuReleaseOffScreen(8.0f / GSgfxVideoGetVsyncRate());
                fightMenuOpenInfoMenu(-1);
            }
        }
        if (fightFloorIsNowEncountSnatchOnly(0) && (result == 0 || result == 3)) {
            menuFightCloseTop(1);
            fightSeqEventKurein(6);
            winMsgOpen(2, 0x5005, 1, 1);
            winMsgClose(1);
            fightSeqEventKurein(7);
            continue;
        }
        return result;
    }
}
}

extern "C" {
void *fightFloorGetNowPtr();
void *fightFloorGetValidFightSidePtr(void *, s32);
FIGHT_TRAINER *fightSideGetValidFightTrainerPtr(void *, s32);
s32 fightTrainerGetValidFightOutPokemonPtr(FIGHT_TRAINER *, s32);
u32 fightOutPokemon_GetTokuseiDataId(s32);
void *pokemonTokuseiDataBiosGetPtr(u16);
void *pokemonTokuseiDataBiosGetName(void *);
u16 pokemonGetSoubiItemDataId(Pokemon *);
void *itemDataBiosGetPtr(u16);
void *itemDataBiosGetName(void *);
u8 pokemonDataBiosGetZokuseiDataId(void *, s32);
u32 zokuseiGetPokemonSpriteID(void *, s32);
void windowDrawSprite2(s32, s32, s16, s16, s32, tagWINDOW_WORK *, u16, s32, s32);
}

extern "C" void menuFightDrawIwaitStatus(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    FIGHT_TRAINER *trainer;
    FIGHT_TRAINER *secondTrainer;
    if (window->menu == 0xA2) trainer = fightSideGetValidFightTrainerPtr(fightFloorGetValidFightSidePtr(fightFloorGetNowPtr(), 1), 0);
    else trainer = fightSideGetValidFightTrainerPtr(fightFloorGetValidFightSidePtr(fightFloorGetNowPtr(), 0), 0);
    secondTrainer = trainer;
    u32 first = fightTrainerGetValidFightOutPokemonPtr(trainer, 0);
    u32 second = fightTrainerGetValidFightOutPokemonPtr(trainer, 1);
    Pokemon *pokemon1;
    Pokemon *pokemon2;
    if (first) pokemon1 = fightOutPokemonGetPokemonPtr(fightTrainerGetValidFightOutPokemonPtr(trainer, 0)); else pokemon1 = 0;
    if (second) pokemon2 = fightOutPokemonGetPokemonPtr(fightTrainerGetValidFightOutPokemonPtr(secondTrainer, 1)); else pokemon2 = 0;
    u32 color = menuSubCalcColor(window, sprite);
    switch (sprite->id) {
    case 0x1D3:
        if (fightKind_CheckFightKind(0x11)) windowDrawSprite2(0, 0, sprite->width, sprite->height, window->color, window, 0x3F7, 0, winSpriteGetLayerID(window, sprite));
        else windowDrawSprite2(0, 0, sprite->width, sprite->height, window->color, window, 0x1EA, 0, winSpriteGetLayerID(window, sprite));
        break;
    case 0x1bf: case 0x1ec:
        if (pokemon1) {
            u16 icon = zokuseiGetPokemonSpriteID(pokemon1->getPokemonDataPtr(), 0);
            if (icon) windowDrawSprite2(0, 0, sprite->width, sprite->height, window->color, window, icon, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    case 0x1c0: case 0x1ed:
        if (pokemon1) {
            u32 type = pokemonDataBiosGetZokuseiDataId(pokemon1->getPokemonDataPtr(), 0);
            if (type != pokemonDataBiosGetZokuseiDataId(pokemon1->getPokemonDataPtr(), 1)) {
                u16 icon = zokuseiGetPokemonSpriteID(pokemon1->getPokemonDataPtr(), 1);
                windowDrawSprite2(0, 0, sprite->width, sprite->height, window->color, window, icon, 0, winSpriteGetLayerID(window, sprite));
            }
        }
        break;
    case 0x1c2: case 0x1ef:
        if (pokemon1) {
            msgctrlSetValue(0x37, pokemonGetStatus(pokemon1, 0, 0x77, 0));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
        }
        break;
    case 0x1c3: case 0x1f0:
        if (pokemon1) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr((u16)fightOutPokemon_GetTokuseiDataId(first)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4279);
        }
        break;
    case 0x1c5: case 0x1f2:
        menuFightDrawIwaitStatusWaza(window, sprite, pokemon1, 0, color);
        break;
    case 0x1c6: case 0x1f3:
        menuFightDrawIwaitStatusWaza(window, sprite, pokemon1, 1, color);
        break;
    case 0x1c7: case 0x1f4:
        menuFightDrawIwaitStatusWaza(window, sprite, pokemon1, 2, color);
        break;
    case 0x1c8: case 0x1f5:
        menuFightDrawIwaitStatusWaza(window, sprite, pokemon1, 3, color);
        break;
    case 0x1c9: case 0x1f6:
        if (pokemon2) {
            u16 icon = zokuseiGetPokemonSpriteID(pokemon2->getPokemonDataPtr(), 0);
            if (icon) windowDrawSprite2(0, 0, sprite->width, sprite->height, color, window, icon, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    case 0x1ca: case 0x1f7:
        if (pokemon2) {
            u32 type = pokemonDataBiosGetZokuseiDataId(pokemon2->getPokemonDataPtr(), 0);
            if (type != pokemonDataBiosGetZokuseiDataId(pokemon2->getPokemonDataPtr(), 1)) {
                u16 icon = zokuseiGetPokemonSpriteID(pokemon2->getPokemonDataPtr(), 1);
                windowDrawSprite2(0, 0, sprite->width, sprite->height, color, window, icon, 0, winSpriteGetLayerID(window, sprite));
            }
        }
        break;
    case 0x1cc: case 0x1f9:
        if (pokemon2) {
            msgctrlSetValue(0x37, pokemonGetStatus(pokemon2, 0, 0x77, 0));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
        }
        break;
    case 0x1cd: case 0x1fa:
        if (pokemon2) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr((u16)fightOutPokemon_GetTokuseiDataId(second)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4279);
        }
        break;
    case 0x1cf: case 0x1fc:
        if (pokemon2) menuFightDrawIwaitStatusWaza(window, sprite, pokemon2, 0, color);
        break;
    case 0x1d0: case 0x1fd:
        if (pokemon2) menuFightDrawIwaitStatusWaza(window, sprite, pokemon2, 1, color);
        break;
    case 0x1d1: case 0x1fe:
        if (pokemon2) menuFightDrawIwaitStatusWaza(window, sprite, pokemon2, 2, color);
        break;
    case 0x1d2: case 0x1ff:
        if (pokemon2) menuFightDrawIwaitStatusWaza(window, sprite, pokemon2, 3, color);
        break;
    case 0x1c1: case 0x1ee:
        winSpriteSetDisp(sprite, 0);
        if (pokemon1 && pokemonGetSoubiItemDataId(pokemon1) != 0) winSpriteSetDisp(sprite, 1);
        break;
    case 0x1cb: case 0x1f8:
        winSpriteSetDisp(sprite, 0);
        if (pokemon2 && pokemonGetSoubiItemDataId(pokemon2) != 0) winSpriteSetDisp(sprite, 1);
        break;
    case 0x1c4: case 0x1f1:
        if (pokemon1 && pokemonGetSoubiItemDataId(pokemon1) != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(pokemonGetSoubiItemDataId(pokemon1)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4279);
        }
        break;
    case 0x1ce: case 0x1fb:
        if (pokemon2 && pokemonGetSoubiItemDataId(pokemon2) != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(pokemonGetSoubiItemDataId(pokemon2)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4279);
        }
        break;
    }
}

extern "C" {
void *fightTypeDataBiosGetPtr(u32);
u8 fightTypeDataBiosGetFightoutPokemonNum(void *);
u8 fightTypeDataBiosGetTrainerNum(void *);
s32 menuPokemonOpenFight(u8, u8, FIGHT_TRAINER *, s32 *);
s32 *fightTargetGetPtr(s32, s32 *, u32);
u8 fightOutPokemonCheckFightOut(s32 *);
s32 fightMenuGetFightOutPokemonPtrToStatusMenuId(s32 *, u32, s32);
s32 menuFightOpenPokemon(FIGHT_TRAINER *trainer, s32 *outInfo, u32 type, u8 chooseTarget, u8 mode) {
    u8 count;
    s32 result;
    s32 *target;
    s32 selection;
    FightTargetWork work;
    count = fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(type));
    if (mode == 0) {
        if (fightKind_CheckFightKind(15)) menuClose(0xB5);
        s32 opened = menuPokemonOpenFight(count, chooseTarget, trainer, outInfo);
        result = opened;
        if (fightKind_CheckFightKind(15)) menuOpen(0xB5, 0);
    } else {
        for (;;) {
            winSeqSetMenu(0x92, 0x20);
            result = menuOpenCustom(0x92, 0, 0, 0, 1, 3, trainer, outInfo, chooseTarget);
            winSeqSetMenu(0x92, 0x22);
            if (result == -1) {
                menuCloseCustom(0x92, 0, 1);
                GSthreadSwitch(); GSthreadSwitch(); GSthreadSwitch(); GSthreadSwitch();
                GSthreadSwitch(); GSthreadSwitch(); GSthreadSwitch(); GSthreadSwitch();
                return -1;
            }
            if (!menuPokemonCheckPokemonChange(outInfo, trainer, result)) continue;
            if (chooseTarget && (count >= 2 || fightTypeDataBiosGetTrainerNum(fightTypeDataBiosGetPtr(type)) == 2)) {
                target = fightTargetGetPtr(15, outInfo, type);
                work.entries[0].id = fightOutPokemonCheckFightOut(target) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(target, type, 0) : 0;
                target = fightTargetGetPtr(16, outInfo, type);
                work.entries[1].id = fightOutPokemonCheckFightOut(target) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(target, type, 0) : 0;
                target = fightTargetGetPtr(14, outInfo, type);
                work.entries[2].id = fightOutPokemonCheckFightOut(target) == 1 ? fightMenuGetFightOutPokemonPtrToStatusMenuId(target, type, 0) : 0;
                work.entries[3].id = 0;
                work.mode = mode;
                selection = menuFightOpenTarget(&work, 0, 1);
                menuFightCloseTarget(1);
                if (selection == -1) continue;
            }
            menuCloseCustom(0x92, 0, 1);
            break;
        }
    }
    return result;
}
}

extern "C" {
s32 menuCB_GetBattleController2P();
u8 fightFloor_GetFightType(s32);
u8 fightTargetIsHostSide(s32, s32);
void winMsgOpenFight(u32, s32, s32);
void winMsgCloseFight(s32);
s32 menuFightOpenWaza(s32 pokemon, MENU_WAZA_STATUS *status, s32 *cursor, s32 wait) {
    u32 repeat;
    s32 response;
    s32 menu;
    s32 confirm;
    s32 other;
    s32 i;
    repeat = 1;
    confirm = 0;
    other = 0;
    switch (((u8 *)status)[0x44]) {
    case 0:
        if (isImasugu()) {
            response = menuCB_GetBattleController2P();
            if (fightTargetIsHostSide(pokemon, fightFloor_GetFightType(0))) {
                menu = 0x9E; confirm = 0x11C; other = 0xA2;
            } else {
                menu = 0xA1; confirm = 0x11D; other = 0x9F;
            }
        } else menu = 0x39;
        break;
    case 1: menu = 0x90; break;
    }
    for (;;) {
        winSeqSetMenu(menu, 0x20);
        if (isImasugu()) {
            if (other) menuOpen(other, 0);
            while ((u8)repeat) {
                response = menuOpenCustom(menu, 0, cursor, 0, wait, 1, status);
                if (response != -1) menuCloseCustom(menu, 2, wait);
                if (response == 5) {
                    if (menuOpen(confirm, 1) == 1) repeat = 0;
                    menuCloseCustom(confirm, 2, 1);
                } else repeat = 0;
            }
            if (response == 5) break;
        } else {
            response = menuOpenCustom(menu, 0, cursor, 0, wait, 1, status);
            if (menu == 0x90) menuClose(menu);
        }
        if (response >= 0) {
            repeat = _menuFightIsUse(status, response);
            if (repeat) {
                menuFightCloseWaza(1);
                if (isImasugu() && other) menuClose(other);
                winMsgOpenFight(repeat, 1, 1);
                _menuFightKeyWait(GSINPUT_DEVICE_1);
                winMsgCloseFight(1);
                repeat = 1;
                continue;
            }
        }
        break;
    }
    winSeqSetMenu(menu, 0x22);
    for (i = 0; i < 4; i++) {
        if (chkWazaNew(status, i) != -1) {
            fightOutPokemonGetPokemonPtr(WZ_SLOT(status))->getDarkPokemon()->setWazaNew(i - 1, true);
        }
    }
    return response;
}
}

extern "C" MenuFightKey *windowGetPortKeyInfo(s32);
extern "C" void menuPlaySe(s32, s32);
extern "C" u8 menuCursorCmp(MenuCursor *, MenuCursor *);
extern "C" void menuFightCurIkousan(void) {
    tagWINDOW_WORK *window;
    MenuFightKey *key;
    if (menuIsCheck(0x11D)) {
        window = windowSearchID(0x11D);
        if (menuCB_GetBattleController2P() == 1) key = windowGetPortKeyInfo(1);
        else key = windowGetPortKeyInfo(2);
        if (key->unk4 & 1) {
            if (window->selected != 0) {
                window->selected--;
                menuPlaySe(window->menu, 1);
            }
        } else if (key->unk4 & 2) {
            if (window->selected == 0) {
                window->selected++;
                menuPlaySe(window->menu, 1);
            }
        }
        MenuCursor previous;
        MenuCursor current;
        *(u32 *)&current = *(u32 *)&window->first;
        *(u32 *)&previous = *(u32 *)window->reservedA0;
        if (menuCursorCmp(&previous, &current)) {
            windowCreateCursorSprite(window);
            menuPlaySe(window->menu, 1);
        }
        *(s16 *)&window->reservedA0[0] = window->first;
        *(s16 *)&window->reservedA0[2] = window->selected;
    }
    if (menuIsCheck(0x11C)) {
        window = windowSearchID(0x11C);
        key = windowGetPortKeyInfo(1);
        if (key->unk4 & 1) {
            if (window->selected != 0) {
                window->selected--;
                menuPlaySe(window->menu, 1);
            }
        } else if (key->unk4 & 2) {
            if (window->selected == 0) {
                window->selected++;
                menuPlaySe(window->menu, 1);
            }
        }
        MenuCursor previous;
        MenuCursor current;
        *(u32 *)&current = *(u32 *)&window->first;
        *(u32 *)&previous = *(u32 *)window->reservedA0;
        if (menuCursorCmp(&previous, &current)) {
            windowCreateCursorSprite(window);
            menuPlaySe(window->menu, 1);
        }
        *(s16 *)&window->reservedA0[0] = window->first;
        *(s16 *)&window->reservedA0[2] = window->selected;
    }
}

extern "C" {
void *pokemonDataBiosGetPtr(u16);
void *pokemonDataBiosGetName(void *);
u32 pokemonGetTokuseiDataId(Pokemon *);
u8 pokemonWazaGetMaxPP(Pokemon *, u16);
u8 fightFloor_GetFightType(s32);
u8 menuSubGetPokemonSexForDisp(Pokemon *);
}
extern "C" void menuFightDrawIPokemonStatus(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    u32 color;
    Pokemon *pokemon;
    s32 index = 0;
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    pokemon = fightOutPokemonGetPokemonPtr(WZ_SLOT(status));
    color = menuSubCalcColor(window, sprite);
    switch (sprite->id) {
    case 0x14C: case 0x181: {
        s32 name = pokemonGetStatus(pokemon, 0, 0x77, 0);
        msgctrlSetValue(0x37, name);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
        break;
    }
    case 0x15F: case 0x194: {
        u16 icon = zokuseiBiosGetSpriteID(pokemonDataBiosGetZokuseiDataId(pokemonDataBiosGetPtr((u16)pokemonGetStatus(pokemon, 0, 0x6E, 0)), 0));
        windowDrawSprite(0, 0, window, icon, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0x160: case 0x195: {
        u32 type;
        u32 secondType;
        void *data = pokemonDataBiosGetPtr((u16)pokemonGetStatus(pokemon, 0, 0x6E, 0));
        type = pokemonDataBiosGetZokuseiDataId(data, 0);
        secondType = pokemonDataBiosGetZokuseiDataId(data, 1);
        if (type != secondType) {
            u16 icon = zokuseiBiosGetSpriteID(secondType);
            windowDrawSprite(0, 0, window, icon, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0x14D: case 0x182: {
        msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr((u16)fightOutPokemon_GetTokuseiDataId(WZ_SLOT(status))))));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), (s16)(GSmsgGetRect(0x435A) >> 16), 0, sprite->width, sprite->height, color, 0x4277);
        break;
    }
    case 0x164: index = 1;
    case 0x163: ++index;
    case 0x162: ++index;
    case 0x161: {
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            u16 icon = zokuseiBiosGetSpriteID((u16)(u32)wazaGetStatus(0, waza, 3, 0));
            windowDrawSprite(0, 0, window, icon, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0x156: index = 1;
    case 0x154: ++index;
    case 0x152: ++index;
    case 0x150: {
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            s16 half = (sprite->width - (s16)(GSmsgGetRect(0x42C2) >> 16)) / 2;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), half, 0, color, 0x42C2);
            msgctrlSetValue(0x5F, pokemonGetStatus(pokemon, 0, 0x80, (u16)index));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, half, sprite->height, color, 0x4358);
            msgctrlSetValue(0x5F, pokemonWazaGetMaxPP(pokemon, (u16)index));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4358);
        }
        break;
    }
    case 0x155: index = 1;
    case 0x153: ++index;
    case 0x151: ++index;
    case 0x14f: {
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            void *name = wazaGetStatus(0, waza, 1, 0);
            if (name != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                s16 height;
                s16 textHeight;
                textHeight = (u16)GSmsgGetRect(0x4277);
                height = sprite->height;
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, (s16)(height / 2 - textHeight / 2), sprite->width, height, color, 0x4277);
            }
        }
        break;
    }
    case 0x199: index = 1;
    case 0x198: ++index;
    case 0x197: ++index;
    case 0x196: {
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            u16 icon = zokuseiBiosGetSpriteID((u16)(u32)wazaGetStatus(0, waza, 3, 0));
            windowDrawSprite(0, 0, window, icon, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0x18b: index = 1;
    case 0x189: ++index;
    case 0x187: ++index;
    case 0x185: {
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            s16 half = (sprite->width - (s16)(GSmsgGetRect(0x42C2) >> 16)) / 2;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), half, 0, color, 0x42C2);
            msgctrlSetValue(0x5F, pokemonGetStatus(pokemon, 0, 0x80, (u16)index));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, half, sprite->height, color, 0x4358);
            msgctrlSetValue(0x5F, pokemonWazaGetMaxPP(pokemon, (u16)index));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4358);
        }
        break;
    }
    case 0x18a: index = 1;
    case 0x188: ++index;
    case 0x186: ++index;
    case 0x184: {
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            void *name = wazaGetStatus(0, waza, 1, 0);
            if (name != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                s16 height;
                s16 textHeight;
                textHeight = (u16)GSmsgGetRect(0x4277);
                height = sprite->height;
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, (s16)(height / 2 - textHeight / 2), sprite->width, height, color, 0x4277);
            }
        }
        break;
    }
    case 0x14E: case 0x183:
        if (pokemonGetSoubiItemDataId(pokemon) != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(pokemonGetSoubiItemDataId(pokemon)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
        }
        break;
    case 0x15E: case 0x193:
        if (pokemonGetSoubiItemDataId(pokemon) != 0) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    case 0x158: case 0x15D: case 0x18D: case 0x192:
        if ((s32 *)WZ_SLOT(status) != fightTargetGetPtr(0xC, (s32 *)WZ_SLOT(status), fightFloor_GetFightType(0))) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    }
}

struct MenuFightItemSize {
    u8 reserved[0xA];
    s16 width;
    s16 height;
};
extern "C" MenuFightItemSize *menuItemBiosGetPtr(s32, s32);
extern "C" void menuSubDrawCursorBack2(s32, s32, s32, s32, s32, s32, s32, s32);
extern "C" void menuFightDrawWaza(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    s32 color;
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(window);
    FightWazaWork *work = windowGetFreeWork(window);
    s32 index = 0;
    switch (sprite->id) {
    case 0x110: index = 0; break;
    case 0x112: index = 1; break;
    case 0x114: index = 2; break;
    case 0x116: index = 3; break;
    case 0x10F: index = 4; break;
    case 0x111: index = 5; break;
    case 0x113: index = 6; break;
    case 0x115: index = 7; break;
    }
    if (index < 4) {
        status = (MENU_WAZA_STATUS *)((u8 *)status + index * 12);
        u32 name = ((FightTargetEntry *)status)->id;
        if (name) {
            msgctrlSetValue(0x37, name);
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0x17, 0, menuSubCalcColor(window, sprite), 0x4277);
        }
    } else {
        if (window->selected == index - 4) {
            winSpriteSetDisp(sprite, 1);
            menuSubDrawCursorBack(winSpriteGetLayerID(window, sprite), sprite->x, sprite->y, sprite->width, sprite->height, 0xFF, 1);
        } else if (work->saved == index - 4) {
            winSpriteSetDisp(sprite, 0);
            MenuFightItemSize *item = menuItemBiosGetPtr(window->menu, sprite->id);
            menuSubDrawCursorBack2(winSpriteGetLayerID(window, sprite), 0, 0, item->width, item->height, 0xFF, 1, 1);
        } else winSpriteSetDisp(sprite, 0);
    }
}

extern "C" void menuFightDrawSecretPokemonStatus(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    Pokemon *pokemon;
    u8 type;
    void *data;
    s32 index = -1;
    FIGHT_TRAINER *trainer = (FIGHT_TRAINER *)windowGetParam(window, 0);
    s32 *selected = (s32 *)windowGetParam(window, 1);
    if (*selected < 0) return;
    pokemon = _menuFightGetPokemonPtr(trainer, (u16)*selected);
    if (pokemon == 0) return;
    u32 color = menuSubCalcColor(window, sprite);
    switch (sprite->id) {
    case 0x2CD:
        if (pokemonGetSoubiItemDataId(pokemon) != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(pokemonGetSoubiItemDataId(pokemon)))));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4276);
        }
        break;
    case 0x2CE:
        winSpriteSetDisp(sprite, 0);
        if (pokemonGetSoubiItemDataId(pokemon) != 0) winSpriteSetDisp(sprite, 1);
        break;
    case 0x2CA: {
        u32 label = GSmsgGetGSchar((void *)0x435A);
        msgctrlSetValue(0x37, label);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4276);
        u16 width = GSmsgGetRect(0x4276) >> 16;
        msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr((u16)pokemonGetTokuseiDataId(pokemon)))));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), width, 0, sprite->width, sprite->height, color, 0x4276);
        break;
    }
    case 0x2C2: case 0x2C3: case 0x2C4: case 0x2C5: case 0x2C6: case 0x2C7:
        switch (sprite->id) {
        case 0x2C2: index = 0; break;
        case 0x2C3: index = 1; break;
        case 0x2C4: index = 3; break;
        case 0x2C5: index = 2; break;
        case 0x2C7: index = 4; break;
        case 0x2C6: index = 5; break;
        }
        if (index == *selected) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    case 0x2C0: {
        u16 icon = zokuseiBiosGetSpriteID(pokemonDataBiosGetZokuseiDataId(pokemonDataBiosGetPtr((u16)pokemonGetStatus(pokemon, 0, 0x6E, 0)), 0));
        windowDrawSprite(0, 0, window, icon, 0, winSpriteGetLayerID(window, sprite));
        break;
    }
    case 0x2C1: {
        data = pokemonDataBiosGetPtr((u16)pokemonGetStatus(pokemon, 0, 0x6E, 0));
        type = (u8)pokemonDataBiosGetZokuseiDataId(data, 0);
        u32 secondType = (u8)pokemonDataBiosGetZokuseiDataId(data, 1);
        if (type != secondType) {
            u16 icon = zokuseiBiosGetSpriteID(secondType);
            windowDrawSprite(0, 0, window, icon, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0x2b8: case 0x2b9: case 0x2ba: case 0x2bb: {
        switch (sprite->id) {
        case 0x2bb: index = 3; break;
        case 0x2ba: index = 2; break;
        case 0x2b9: index = 1; break;
        case 0x2b8: index = 0; break;
        }
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            u16 icon = zokuseiBiosGetSpriteID((u16)(u32)wazaGetStatus(0, waza, 3, 0));
            windowDrawSprite(0, 0, window, icon, 0, winSpriteGetLayerID(window, sprite));
        }
        break;
    }
    case 0x2cf: case 0x2d0: case 0x2d1: case 0x2d2: {
        switch (sprite->id) {
        case 0x2d2: index = 3; break;
        case 0x2d1: index = 2; break;
        case 0x2d0: index = 1; break;
        case 0x2cf: index = 0; break;
        }
        winSpriteSetDisp(sprite, 0);
        if ((u16)pokemonGetStatus(pokemon, 0, 0x7F, (u16)index) != 0) winSpriteSetDisp(sprite, 1);
        break;
    }
    case 0x2bc: case 0x2bd: case 0x2be: case 0x2bf: {
        switch (sprite->id) {
        case 0x2bf: index = 3; break;
        case 0x2be: index = 2; break;
        case 0x2bd: index = 1; break;
        case 0x2bc: index = 0; break;
        }
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            s16 half = (sprite->width - (s16)(GSmsgGetRect(0x42C4) >> 16)) / 2;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), half, 0, color, 0x42C4);
            msgctrlSetValue(0x5F, pokemonGetStatus(pokemon, 0, 0x80, (u16)index));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, half, sprite->height, color, 0x4357);
            msgctrlSetValue(0x5F, (u16)pokemonWazaGetMaxPP(pokemon, (u16)index));
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4357);
        }
        break;
    }
    case 0x2b4: case 0x2b5: case 0x2b6: case 0x2b7: {
        switch (sprite->id) {
        case 0x2b7: index = 3; break;
        case 0x2b6: index = 2; break;
        case 0x2b5: index = 1; break;
        case 0x2b4: index = 0; break;
        }
        u16 waza = pokemonGetStatus(pokemon, 0, 0x7F, (u16)index);
        if (waza != 0) {
            void *name = wazaGetStatus(0, waza, 1, 0);
            if (name != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
            }
        }
        break;
    }
    case 0x2CB: {
        index = (s16)((GSmsgGetRect(0x42D5) >> 16) + 2);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x42D5);
        s16 gap = (sprite->width - index - (s16)(GSmsgGetRect(0x42C4) >> 16)) / 2;
        s32 layer = winSpriteGetLayerID(window, sprite);
        s32 x = index + gap;
        GSmsgPrint2(layer, x, 0, color, 0x42C4);
        msgctrlSetValue(0x5F, (s16)pokemonGetStatus(pokemon, 0, 0x83, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, x, sprite->height, color, 0x4357);
        msgctrlSetValue(0x5F, (s16)pokemonGetStatus(pokemon, 0, 0x87, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4357);
        break;
    }
    case 0x2CC: {
        s16 width = GSmsgGetRect(0x42D4) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x42D4);
        msgctrlSetValue(0x5F, (u8)pokemonGetStatus(pokemon, 0, 0x7A, 0));
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), width, 0, sprite->width, sprite->height, color, 0x4351);
        break;
    }
    case 0x2C9: {
        s16 width = 0;
        data = pokemonDataBiosGetPtr((u16)pokemonGetStatus(pokemon, 0, 0x6E, 0));
        if (data != 0) {
            void *name = pokemonDataBiosGetName(data);
            if (name != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4277);
                width = GSmsgGetRect(0x4277) >> 16;
            }
            u32 sex;
            switch (menuSubGetPokemonSexForDisp(pokemon)) {
            case 0: sex = 0x9C5; break;
            case 1: sex = 0x9C6; break;
            case 2: default: sex = 0; break;
            }
            if (sex != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar((void *)sex));
                GSmsgPrint2(winSpriteGetLayerID(window, sprite), width, 0, color, 0x4276);
            }
        }
        break;
    }
    case 0x2C8: {
        s32 name = pokemonGetStatus(pokemon, 0, 0x77, 0);
        msgctrlSetValue(0x37, name);
        GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4277);
        break;
    }
    }
}

extern "C" s32 menuGetCursor(s32);
extern "C" void menuFightDrawCmdMsg(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    u32 message = 0;
    s32 color;
    void *allocation;
    switch (sprite->id) {
    case 0x137:
        allocation = windowGetAllocPtr(window);
        msgctrlSetValue(0x36, (u32)allocation);
        message = 0x42C3;
        break;
    case 0x11D: {
        u32 *status = (u32 *)windowGetAllocPtr(window);
        FightWazaWork *work = windowGetFreeWork(window);
        switch (work->mode) {
        case 0: msgctrlSetValue(0x36, *status); message = 0x42C3; break;
        case 1: message = 0x42C6; break;
        }
        break;
    }
    case 0x12B:
        if (menuGetCursor(0x3A) == 0) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    case 0x12D:
        if (menuGetCursor(0x3A) == 1) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    case 0x12F:
        if (menuGetCursor(0x3A) == 2) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    case 0x131:
        if (menuGetCursor(0x3A) == 3) winSpriteSetDisp(sprite, 1);
        else winSpriteSetDisp(sprite, 0);
        break;
    default: break;
    }
    if (message) {
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, -2, menuSubCalcColor(window, sprite), message);
    }
}

extern "C" u8 fightFloor_GetStockPokemonNum(s32);
extern "C" void menuFightDrawBall(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    u32 image = 0;
    s32 index = -1;
    u8 *work = (u8 *)windowGetFreeWork(window);
    switch (sprite->id) {
    case 0xB1: case 0xBE: case 0xC4: case 0xCA: index = 0; break;
    case 0xB2: case 0xBF: case 0xC5: case 0xCB: index = 1; break;
    case 0xB3: case 0xC0: case 0xC6: case 0xCC: index = 2; break;
    case 0xB4: case 0xC1: case 0xC7: case 0xCD: index = 3; break;
    case 0xB5: case 0xC2: case 0xC8: case 0xCE: index = 4; break;
    case 0xB6: case 0xC3: case 0xC9: case 0xCF: index = 5; break;
    case 0xB7:
        winSpriteSetDisp(sprite, 0);
        if (fightFloor_GetStockPokemonNum(0)) winSpriteSetDisp(sprite, 1);
        return;
    case 0xBD: index = 0;
    case 0xBC: index++;
    case 0xBB: index++;
    case 0xBA: index++;
    case 0xB9: index++;
    case 0xB8:
        winSpriteSetDisp(sprite, 0);
        if (index + 2 <= fightFloor_GetStockPokemonNum(0)) winSpriteSetDisp(sprite, 1);
        return;
    }
    if (index >= 0) {
        switch (work[index]) {
        case 0: image = 0x8C; break;
        case 1: image = 0x8D; break;
        case 2: image = 0x8E; break;
        case 3: image = 0x8F; break;
        }
        if ((u16)image) windowDrawSprite(0, 0, window, image, 0, winSpriteGetLayerID(window, sprite));
    }
}

extern "C" void menuFightButtonTargetSecret(tagWINDOW_WORK *window) {
    MenuFightKey *key;
    s32 selected;
    FightTargetEntry *entries;
    key = windowGetKeyInfo();
    selected = -1;
    entries = (FightTargetEntry *)windowGetParam(window, 0);
    if (key->unk4 & 1) selected = 0;
    else if (key->unk4 & 8) selected = 1;
    else if (key->unk4 & 4) selected = 2;
    else if (key->unk4 & 2) selected = 3;
    else if (key->unk4 & 0x200) {
        window->finished = 1;
        window->cancelled = 1;
        window->value = -1;
    }
    if (selected >= 0) {
        for (s32 i = 0; i < 4; i++) {
            s32 target;
            switch (entries[i].id) {
            case 0x37: target = 2; break;
            case 0x40: target = 3; break;
            case 0x38: target = 0; break;
            case 0x41: target = 1; break;
            default: target = -1; break;
            }
            if (selected == target) {
                if (selected > 2) selected = 2;
                window->finished = 1;
                window->value = selected;
                return;
            }
        }
    }
    menuFightButtonTimeOutCheck(window);
}

extern "C" void menuFightDrawSecretWazaSelect(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    s32 offset;
    MenuFightWazaLayout *entry;
    s32 index = -1;
    tagWINDOW_WORK *source = windowSearchID(windowGetParam(window, 0));
    if (source == 0) return;
    MENU_WAZA_STATUS *status = (MENU_WAZA_STATUS *)windowGetAllocPtr(source);
    if (status == 0) return;
    u32 color = menuSubCalcColor(window, sprite);
    switch (sprite->id) {
    case 0x57: case 0x5C: case 0x60: case 0x64: index = 0; break;
    case 0x58: case 0x5D: case 0x61: case 0x65: index = 1; break;
    case 0x59: case 0x5E: case 0x62: case 0x66: index = 2; break;
    case 0x5A: case 0x5F: case 0x63: case 0x67: index = 3; break;
    }
    if (index < 0) return;
    offset = index * 12;
    entry = (MenuFightWazaLayout *)((u8 *)status + offset);
    if (entry->entries[0].name != 0) winSpriteSetDisp(sprite, 1);
    else { winSpriteSetDisp(sprite, 0); return; }
    switch (sprite->id) {
        case 0x5C: case 0x5D: case 0x5E: case 0x5F: {
            u16 type = ((MenuFightWazaEntry *)&status->raw[offset + 4])->type;
            windowDrawSprite(0, 0, window, zokuseiBiosGetSpriteID(type), 0, winSpriteGetLayerID(window, sprite));
            break;
        }
        case 0x60: case 0x61: case 0x62: case 0x63: {
            s16 half = (sprite->width - (s16)(GSmsgGetRect(0x42C4) >> 16)) / 2;
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), half, 0, color, 0x42C4);
            msgctrlSetValue(0x5F, status->raw[offset + 0xF]);
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, half, sprite->height, color, 0x4357);
            msgctrlSetValue(0x5F, status->raw[offset + 0xE]);
            GSmsgPrintRect(winSpriteGetLayerID(window, sprite), 0, 0, sprite->width, sprite->height, color, 0x4357);
            break;
        }
        case 0x57: case 0x58: case 0x59: case 0x5A:
            msgctrlSetValue(0x37, entry->entries[0].name);
            GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, color, 0x4277);
            break;
        case 0x64: case 0x65: case 0x66: case 0x67:
            break;
        }
}

extern "C" { static s32 waza_no$2832[2] = {-1,-1}; }
extern "C" void menuFightButtonIwaza1p(void) {
    s32 i;
    MenuFightWazaLayout* work;
    s32 target1;
    FightTargetEntry* targets;
    u16 direction;
    s32 parent;
    s32 target0;
    s32 selected0;
    u16 edge;
    s32 selected1;
    u16 held;
    tagWINDOW_WORK* win;
    u16 trigger;
    Pokemon* pokemon;
    MenuFightKey* key;
    s32 slot;

    if(menuIsCheck(0x11D)) {
        if(menuIsCheck(0x115)) menuClose(0x115);
        if(menuIsCheck(0xA2)) menuClose(0xA2);
        win=windowSearchID(0x11D);
        if(menuCB_GetBattleController2P()==1) key=windowGetPortKeyInfo(1);else key=windowGetPortKeyInfo(2);
        trigger=key->unk4;
        if(trigger & 0x10) {win->finished=1;win->value=win->selected;menuPlaySe(win->menu,2);return;}
        else if(trigger & 0x20) {win->cancelled=1;win->value=-1;menuPlaySe(win->menu,3);return;}
        menuFightButtonTimeOutCheck(win);
    }
    if(menuIsCheck(0x11C)) {
        if(menuIsCheck(0x114)) menuClose(0x114);
        if(menuIsCheck(0x9F)) menuClose(0x9F);
        win=windowSearchID(0x11C);
        key=windowGetPortKeyInfo(1);
        trigger=key->unk4;
        if(trigger & 0x10) {win->finished=1;win->value=win->selected;menuPlaySe(win->menu,2);}
        else if(trigger & 0x20) {win->cancelled=1;win->value=-1;menuPlaySe(win->menu,3);}
        menuFightButtonTimeOutCheck(win);
    }
    selected1=-1;
    if(menuIsCheck(0xA1)) {
        win=windowSearchID(0xA1);
        work=(MenuFightWazaLayout*)windowGetAllocPtr(win);
        pokemon=fightOutPokemonGetPokemonPtr(work->slot);
        if(menuCB_GetBattleController2P()==1) {
            key=windowGetPortKeyInfo(1);edge=_menuFightGetRightStickInfo(0,true);held=_menuFightGetRightStickInfo(0,false);
        } else {
            key=windowGetPortKeyInfo(2);edge=_menuFightGetRightStickInfo(1,true);held=_menuFightGetRightStickInfo(1,false);
        }
        if(menuIsCheck(0xA2)) {
            if(!(key->unk0 & 0x40)) {menuClose(0xA2);menuSetDisp(0xA1,1);}
        } else if(edge!=0) {
            if(edge & 1) selected1=0;
            else if(edge & 8) selected1=1;
            else if(edge & 2) selected1=2;
            else if(edge & 4) selected1=3;
            else if(edge & 0x200) selected1=-1;
            if(key->unk0 & 0x400) {
                waza_no$2832[1]=selected1;
                if(menuIsCheck(0x115)) menuClose(0x115);
                if(work->entries[waza_no$2832[1]].name) {
                    parent=win->menu;
                    menuOpenCustom(0x115,parent,0,0,0,2,parent,&waza_no$2832[1]);
                }
            } else {
                if(menuIsCheck(0x115)) menuClose(0x115);
                if(!pokemonWazaCheckValid(pokemon,selected1)) selected1=-1;
                if(selected1>=0) {win->finished=1;win->value=selected1;}
            }
        } else if(menuIsCheck(0x115)) {
            if(!(key->unk0 & 0x400) || held==0) menuClose(0x115);
        } else if(key->unk0 & 0x40) {menuSetDisp(0xA1,0);menuOpen(0xA2,0);}
        else {
            trigger=key->unk4;
            if(trigger & 0x200) {win->cancelled=1;win->value=-1;}
            else if(trigger & 0x800) {win->finished=1;win->value=5;}
        }
        menuFightButtonTimeOutCheck(win);
    }
    selected0=-1;
    if(menuIsCheck(0x9E)) {
        win=windowSearchID(0x9E);
        work=(MenuFightWazaLayout*)windowGetAllocPtr(win);
        pokemon=fightOutPokemonGetPokemonPtr(work->slot);
        key=windowGetPortKeyInfo(1);edge=_menuFightGetRightStickInfo(0,true);held=_menuFightGetRightStickInfo(0,false);
        if(menuIsCheck(0x9F)) {
            if(!(key->unk0 & 0x40)) {menuClose(0x9F);menuSetDisp(0x9E,1);}
        } else if(edge!=0) {
            if(edge & 1) selected0=0;
            else if(edge & 8) selected0=1;
            else if(edge & 2) selected0=2;
            else if(edge & 4) selected0=3;
            if(key->unk0 & 0x400) {
                waza_no$2832[0]=selected0;
                if(menuIsCheck(0x114)) menuClose(0x114);
                if(work->entries[waza_no$2832[0]].name) {
                    parent=win->menu;
                    menuOpenCustom(0x114,parent,0,0,0,2,parent,&waza_no$2832[0]);
                }
            } else {
                if(menuIsCheck(0x114)) menuClose(0x114);
                if(!pokemonWazaCheckValid(pokemon,selected0)) selected0=-1;
                if(selected0>=0) {win->finished=1;win->value=selected0;}
            }
        } else if(menuIsCheck(0x114)) {
            if(!(key->unk0 & 0x400) || held==0) menuClose(0x114);
        } else if(key->unk0 & 0x40) {menuSetDisp(0x9E,0);menuOpen(0x9F,0);}
        else {
            trigger=key->unk4;
            if(trigger & 0x200) {win->cancelled=1;win->value=-1;}
            else if(trigger & 0x800) {win->finished=1;win->value=5;}
        }
        menuFightButtonTimeOutCheck(win);
    }
    target1=-1;
    if(menuIsCheck(0xA3)) {
        win=windowSearchID(0xA3);
        targets=(FightTargetEntry*)windowGetParam(win,0);
        if(menuCB_GetBattleController2P()==1) {key=windowGetPortKeyInfo(1);direction=_menuFightGetLeftKeyInfo(0);}
        else {key=windowGetPortKeyInfo(2);direction=_menuFightGetLeftKeyInfo(1);}
        targets=(FightTargetEntry*)windowGetParam(win,0);
        trigger=key->unk4;
        if(trigger!=0) {
            if(direction & 1) target1=2;
            else if(direction & 8) target1=3;
            else if(direction & 4) target1=0;
            else if(direction & 2) target1=1;
            else if(trigger & 0x200) {win->finished=1;win->cancelled=1;win->value=-1;}
        }
        if(target1>=0) {
            for(i=0;i<4;++i) {
                switch(targets[i].id) {
                case 0x37:slot=0;break;
                case 0x40:slot=1;break;
                case 0x38:slot=2;break;
                case 0x41:slot=3;break;
                default:slot=-1;break;
                }
                if(target1==slot) {
                    if(target1>2) target1=2;
                    win->finished=1;win->value=target1;return;
                }
            }
        }
        menuFightButtonTimeOutCheck(win);
    }
    target0=-1;
    if(menuIsCheck(0xA0)) {
        win=windowSearchID(0xA0);
        targets=(FightTargetEntry*)windowGetParam(win,0);
        _menuFightGetRightStickInfo(0,true);
        direction=_menuFightGetLeftKeyInfo(0);
        key=windowGetPortKeyInfo(1);
        trigger=key->unk4;
        if(trigger!=0) {
            if(direction & 1) target0=0;
            else if(direction & 8) target0=1;
            else if(direction & 2) target0=2;
            else if(direction & 4) target0=3;
            else if(trigger & 0x200) {win->finished=1;win->cancelled=1;win->value=-1;}
        }
        if(target0>=0) {
            for(i=0;i<4;++i) {
                switch(targets[i].id) {
                case 0x37:slot=3;break;
                case 0x40:slot=2;break;
                case 0x38:slot=0;break;
                case 0x41:slot=1;break;
                default:slot=-1;break;
                }
                if(target0==slot) {
                    if(target0>2) target0=2;
                    win->finished=1;win->value=target0;return;
                }
            }
        }
        menuFightButtonTimeOutCheck(win);
    }
}

extern "C" {
static s32 pokemon_no$3245;
static u8 init$3246;
static s32 waza_no$3039;
static u8 init$3040;
void menuFightButtonSecretPokemonTop(tagWINDOW_WORK *arg0) {
    MenuFightKey *temp_r30;
    u8 temp_r31;
    u16 temp_r3_3;
    u16 temp_r3_2;
    u16 temp_r3;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 temp_r26;

    if ((s8) init$3246 == 0) {
        pokemon_no$3245 = -1;
        init$3246 = 1;
    }
    temp_r30 = windowGetKeyInfo();
    var_r29 = -1;
    var_r28 = 0;
    var_r27 = 0;
    temp_r26 = windowGetParam(arg0, 0);
    windowGetParam(arg0, 1);
    temp_r31 = windowGetParam(arg0, 2) != 0;
    menuSetDisp(arg0->menu, 1);
    if (menuIsCheck(0x95) != 0) {
        var_r28 = 0x95;
    } else if (menuIsCheck(0x96) != 0) {
        var_r28 = 0x96;
    }
    temp_r3 = _menuFightGetRightStickInfo(0, 1);
    if ((s32) (temp_r3 & 1) != 0) {
        var_r29 = 0;
    } else if ((s32) (temp_r3 & 8) != 0) {
        var_r29 = 1;
    } else if ((s32) (temp_r3 & 2) != 0) {
        var_r29 = 2;
    } else if ((s32) (temp_r3 & 4) != 0) {
        var_r29 = 3;
    } else {
        temp_r3_2 = temp_r30->unk4;
        if ((s32) (temp_r3_2 & 0x80) != 0) {
            var_r29 = 4;
        } else if ((s32) (temp_r3_2 & 0x40) != 0) {
            var_r29 = 5;
        }
    }
    if (var_r29 >= 0) {
        if (_menuFightGetPokemonPtr((FIGHT_TRAINER*)temp_r26, (u16) var_r29) == 0) {
            var_r29 = -1;
        }
        if (var_r29 >= 0) {
            arg0->finished = 1U;
            arg0->value = var_r29;
        }
    }
    if (var_r29 < 0) {
        if ((s32) (temp_r30->unk4 & 0x200) != 0) {
            if (temp_r31 != 0) {
                arg0->finished = 1U;
                arg0->cancelled = 1;
                arg0->value = -1;
            }
        } else if ((s32) (temp_r30->unk0 & 0x400) != 0) {
            menuSetDisp(arg0->menu, 0);
            pokemon_no$3245 = -1;
            temp_r3_3 = temp_r30->unk0;
            if ((s32) (temp_r3_3 & 1) != 0) {
                if ((s32) (temp_r3_3 & 8) != 0) {
                    pokemon_no$3245 = 5;
                } else if ((s32) (temp_r3_3 & 4) != 0) {
                    pokemon_no$3245 = 4;
                } else {
                    pokemon_no$3245 = 0;
                }
            } else if ((s32) (temp_r3_3 & 2) != 0) {
                pokemon_no$3245 = 2;
            } else if ((s32) (temp_r3_3 & 8) != 0) {
                pokemon_no$3245 = 1;
            } else if ((s32) (temp_r3_3 & 4) != 0) {
                pokemon_no$3245 = 3;
            }
            if (((s32) pokemon_no$3245 >= 0) && (_menuFightGetPokemonPtr((FIGHT_TRAINER*)temp_r26, (u16) pokemon_no$3245) == 0)) {
                pokemon_no$3245 = -1;
            }
            if ((s32) pokemon_no$3245 < 0) {
                var_r27 = 0x95;
            } else {
                var_r27 = 0x96;
            }
        }
    }
    menuFightButtonTimeOutCheck(arg0);
    if (var_r28 != var_r27) {
        if (var_r28 != 0) {
            menuClose(var_r28);
        }
        if ((u8) arg0->finished == 0) {
            if (var_r27 == 0x95) {
                menuOpenCustom(0x95, arg0->menu, 0, 0, 0, 1, temp_r26);
                menuSetDisp(0x95, 1);
                menuSetDisp(0x96, 0);
                return;
            } else if (var_r27 == 0x96) {
                menuOpenCustom(0x96, arg0->menu, 0, 0, 0, 2, temp_r26, &pokemon_no$3245);
                menuSetDisp(0x96, 1);
                menuSetDisp(0x95, 0);
            }
        }
    }
}

void menuFightButtonSecretWazaTop(tagWINDOW_WORK *arg0) {
    MenuFightKey *temp_r27;
    u16 temp_r3_2;
    u16 temp_r3;
    s32 var_r30;
    s32 var_r29;
    s32 var_r26;
    s32 temp_r4_2;
    s32 temp_r4;
    MenuFightWazaLayout *temp_r31;

    if ((s8) init$3040 == 0) {
        waza_no$3039 = -1;
        init$3040 = 1;
    }
    temp_r27 = windowGetKeyInfo();
    temp_r31 = (MenuFightWazaLayout*)windowGetAllocPtr(arg0);
    var_r26 = -1;
    var_r30 = 0;
    var_r29 = 0;
    menuSetDisp(arg0->menu, 1);
    if (menuIsCheck(0x94) != 0) {
        var_r30 = 0x94;
    } else if (menuIsCheck(0x93) != 0) {
        var_r30 = 0x93;
    }
    temp_r3 = _menuFightGetRightStickInfo(0, 1);
    if (temp_r3 != 0) {
        if ((s32) (temp_r3 & 1) != 0) {
            var_r26 = 0;
        } else if ((s32) (temp_r3 & 8) != 0) {
            var_r26 = 1;
        } else if ((s32) (temp_r3 & 2) != 0) {
            var_r26 = 2;
        } else if ((s32) (temp_r3 & 4) != 0) {
            var_r26 = 3;
        }
        if (temp_r31->entries[var_r26].name == 0) {
            var_r26 = -1;
        }
        if (var_r26 >= 0) {
            arg0->finished = 1U;
            arg0->value = var_r26;
        }
    } else if ((s32) (temp_r27->unk4 & 0x200) != 0) {
        arg0->finished = 1U;
        arg0->cancelled = 1;
        arg0->value = -1;
    } else if ((s32) (temp_r27->unk0 & 0x400) != 0) {
        menuSetDisp(arg0->menu, 0);
        temp_r3_2 = temp_r27->unk0;
        if ((s32) (temp_r3_2 & 1) != 0) {
            waza_no$3039 = 0;
        } else if ((s32) (temp_r3_2 & 8) != 0) {
            waza_no$3039 = 1;
        } else if ((s32) (temp_r3_2 & 2) != 0) {
            waza_no$3039 = 2;
        } else if ((s32) (temp_r3_2 & 4) != 0) {
            waza_no$3039 = 3;
        } else {
            waza_no$3039 = -1;
        }
        if (temp_r31->entries[waza_no$3039].name == 0) {
            waza_no$3039 = -1;
        }
        if ((s32) waza_no$3039 < 0) {
            var_r29 = 0x94;
        } else {
            var_r29 = 0x93;
        }
    }
    menuFightButtonTimeOutCheck(arg0);
    if (var_r30 != var_r29) {
        if (var_r30 != 0) {
            menuClose(var_r30);
        }
        if ((u8) arg0->finished == 0) {
            if (var_r29 == 0x94) {
                temp_r4 = arg0->menu;
                menuOpenCustom(0x94, temp_r4, 0, 0, 0, 1, temp_r4);
                menuSetDisp(0x94, 1);
                menuSetDisp(0x93, 0);
                return;
            } else if (var_r29 == 0x93) {
                temp_r4_2 = arg0->menu;
                menuOpenCustom(0x93, temp_r4_2, 0, 0, 0, 2, temp_r4_2, &waza_no$3039);
                menuSetDisp(0x93, 1);
                menuSetDisp(0x94, 0);
            }
        }
    }
}

}

extern "C" {
static u16 menu_item_waza_tbl$2480[4] = {0x110,0x112,0x114,0x116};
s32 menuFightWazaCtrl(tagWINDOW_WORK *arg0) {
    s32 temp_r3_5;
    s32 i;
    u8 temp_r0;
    void *temp_r3;
    FightWazaWork *temp_r3_2;
    void *temp_r3_4;

    temp_r0 = arg0->phase;
    if ((s8) temp_r0 == 0) {
        temp_r3 = windowAllocMemory(arg0, 0x48);
        if (temp_r3 != NULL) {
            memcpy(temp_r3, (void*)windowGetParam(arg0, 0), 0x48);
        }
        temp_r3_2 = windowGetFreeWork(arg0);
        temp_r3_2->mode = 0;
        temp_r3_2->reserved1 = 0;
        temp_r3_2->saved = -1;
    } else if ((s8) temp_r0 == 3) {
        temp_r3 = windowGetAllocPtr(arg0);
        if (temp_r3 != NULL) {
            memcpy((void*)windowGetParam(arg0, 0), temp_r3, 0x48);
        }
    }
    temp_r3_4 = windowGetAllocPtr(arg0);
    if ((s8) arg0->phase == 5) {
        for (i = 0; i < 4; i++) {
            menuItemBiosSetSelectFlag(arg0->menu, menu_item_waza_tbl$2480[i], 1);
        }
    } else {
        u8 *entries = (u8 *)temp_r3_4;
        for (i = 0; i < 4; i++) {
            if (*(u32 *)(entries + i * 12 + 4) != 0U) {
                menuItemBiosSetSelectFlag(arg0->menu, menu_item_waza_tbl$2480[i], 1);
            } else {
                menuItemBiosSetSelectFlag(arg0->menu, menu_item_waza_tbl$2480[i], 0);
            }
        }
    }
    temp_r3_5 = menuGetCursorItemID(arg0->menu);
    switch (temp_r3_5) {
    case 0x110:
        arg0->value = 0;
        break;
    case 0x112:
        arg0->value = 1;
        break;
    case 0x114:
        arg0->value = 2;
        break;
    case 0x116:
        arg0->value = 3;
        break;
    default:
        arg0->value = -1;
        break;
    }
    return 0;
}
}
