#pragma peephole off
#pragma pool_strings off
#include <dolphin/types.h>
#include <libc/stdarg.h>

struct MenuItem {
    u8 selectable : 1;
    u8 last : 1;
    u8 spriteType : 2;
    u8 low : 4;
    u8 top2 : 2;
    u8 rest1 : 6;
    u8 alpha;
    u8 pad3;
    s16 spriteID;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 cursorSprite;
    void* msg;
    void* callback;
    s16 next;
};

struct MenuWindow;
typedef void (*MenuWindowCallback)(MenuWindow*);

struct MenuData {
    u8 f0a : 3;
    u8 f0b : 2;
    u8 f0c : 1;
    u8 f0d : 1;
    u8 f0e : 1;
    u8 f1a : 4;
    u8 f1b : 3;
    u8 f1c : 1;
    u8 f2a : 3;
    u8 f2b : 5;
    u8 pad3;
    u8 cursorID;
    u8 pad5;
    s16 firstItem;
    s16 x;
    s16 y;
    MenuWindowCallback cursorCallback;
    MenuWindowCallback buttonCallback;
    MenuWindowCallback tickCallback;
    MenuWindowCallback drawCallback;
};

union MenuCursor {
    u32 raw;
    struct {
        s16 base;
        s16 offset;
    } p;
};

struct MenuSprite {
    MenuSprite* next;
    u8 pad4[2];
    s16 id;
    u8 pad8[4];
    u8 seq[0x3c];
};

struct MenuWindow {
    s8 flags;
    s8 phase;
    u8 phaseFrame;
    u8 pad3;
    s32 id;
    u8 pad8;
    s8 fadePriority;
    u8 transitionDone;
    u8 keyPort;
    u8 pad_0C[4];
    MenuWindow* next;
    u8 pad_14[5];
    s8 cursorCount;
    u8 cursorMode;
    u8 cursorFlags;
    s32 layerID;
    u8 pad_20[4];
    MenuSprite* sprites;
    MenuSprite* overlaySprites;
    u8 pad_2c[0x60];
    s16 x;
    s16 y;
    u8 pad_90[0xC];
    MenuCursor cursor;
    MenuCursor prev;
    u8 close;
    u8 back;
};

struct KeyInfo {
    u16 on;
    u16 up;
    u16 trg;
    u16 rep;
    u16 rel;
    s8 timer[16];
};

struct KeyInfoRaw {
    u8 data[26];
};

struct WINDOW_SYS_WORK {
    u16 count;
    u8 pad_2[6];
    s32 activeID;
    void* pool;
    MenuWindow* head;
    KeyInfo key;
    KeyInfo port[4];
    u8 enablePort;
    u8 pad_97;
    s32 lastError;
    s32 lastID;
};

struct GSgfxVF {
    u8 pad[0x440];
};

extern "C" {
MenuWindow* windowSearchID(s32 id);
s32 windowGetActiveID(void);
MenuData* menuDataBiosGetPtr(s32 id);
MenuItem* menuItemBiosGetPtr(s32 id, s16 index);
void* menuSeBiosGetPtr(u32 id);
u16 menuSeBiosGetSndId(void* se, s32 kind);
MenuItem* windowGetCursorToItem(MenuWindow* w);
KeyInfo* windowGetKeyInfo(void);
KeyInfo* windowGetKeyInfo2(void);
KeyInfo* windowGetPortKeyInfo(u8 ports);
KeyInfo* windowGetPortKeyInfo2(u8 ports);
s32 windowClose(MenuWindow* w, u32 flags);
void windowCloseMain(MenuWindow* w);
void windowInit(u16 count);
MenuWindow* windowOpen(s32* cursorOut, s32 menuID, s32 parentID, u32 closeFlags, s32 num, va_list args);
s32 windowCheckCursor(s32 id, u8 wait);
s32 windowGetValue(s32 id);
void windowCreateCursorSprite(MenuWindow* w);
u8 winSeqCheckMove(s32 id);
void winSeqMoveMenu(MenuWindow* w);
void winSetSequence(void* seq, u32 id);
void winSpriteDraw(MenuWindow* w, MenuSprite* sp);
void spriteSetOffset(s32 layer, s16 x, s16 y);
void spriteClearScissor(s32 layer);
void spriteSetEnv(s32 layer);
void spriteClearEnv(s32 layer);
void GSgfxLayerSetActive(int id);
s32 floorGetMenuLayerID(void);
u8 floorExecScriptIntegerByName(const char* name, s32 a, s32 b, s32 c, s32 d);
void fadeDaemon(void);
u8 pauseIsPause(void);
void cursorBiosInit(void);
void cursorBiosSetPos(u8 slot, MenuCursor* pos);
s32 menuFaceInit(s32 id);
void menuOffScreenCreate(u32 param);
void menuOffScreenInit(void);
void menuOffScreenRelease(void);
void menuOffScreenFadeSet(f32 a, f32 b);
void menuOffScreenFadeSync(u8 wait);
u8 menuOffScreenCheckEnable(u8 enable);
void menuOffScreenDraw(void);
u8 menuOffScreenSetDisp(u8 enable);
u8 menuOffScreenSetPriority(u8 priority);
void GSsndPlayNow(u32 id);
void GSlogWrite(const char* fmt, ...);
u32 GSthreadGetCurrentThread(void);
void GSthreadSwitch(void);
f32 timeGetLastFrameSec(void);
u32 timeGetLastFrameTime(void);
void FlashSystemInitAll(void);
void GSgfxVFCreate(GSgfxVF* vf);
void GSgfxVFInit(GSgfxVF* vf);
void GSgfxVFSetElement(GSgfxVF* vf, s32 a, s32 b, s32 c, s32 d);
void GSresRegisterResource(void* mem, u32 grp, u32 id, void* freeFunc);
void* GStextureLoad(void* tex);
u8 GSinputIsConnected(s32 pad);
u32 GSinputGetLeftStickXData(s32 pad, s32 mode);
u32 GSinputGetLeftStickYData(s32 pad, s32 mode);
u32 GSinputGetRightStickXData(s32 pad, s32 mode);
u32 GSinputGetRightStickYData(s32 pad, s32 mode);
u32 GSinputButtonsPressed(s32 pad);
u8 gbaCommandIsConnected(s32 gba);
u16 gbaCommandKeyPressed(s32 gba);
double atan2(double y, double x);
void* memset(void* dst, int val, u32 size);

extern WINDOW_SYS_WORK winSysWork;
extern WINDOW_SYS_WORK winSysWork2;
extern u8 uv_cmn_win_00[];
extern u8 tex_warning[];
extern u8 tex_warning_pstar[];
extern u8 uv_cmn_csr_00[];
extern u8 uv_common_icon_00[];
}

GSgfxVF menuHyperModeVf;

static u8 connect_bak[4];
static u8 connect[4];
static f32 _currentTime;
static f32 _currentAddTime;
static s32 _menuCount;

static f64 _gettLastTime(void);
static void _menuUpdateKeyInfo(WINDOW_SYS_WORK* a, WINDOW_SYS_WORK* b);
static u8 _menuGetAgbKeyInfo(s32 port, u16* keys);
static u8 _menuGetGcKeyInfo(s32 port, u16* keys, u16* keys2);

extern "C" {
s32 menuGetCursor(s32 id);
s32 menuCloseCustom(s32 id, u32 flags, u8 wait);
s32 menuCloseSync(s32 id, u8 wait);
s32 menuOpenCustom(s32 menu_id, s32 parent_id, s32* cursor_out, u32 close_flags, u8 check_cursor, s32 open_param, ...);
void menuPlaySe(s32 id, s32 event);
void menuButtonNormal(MenuWindow* window);
void menuCursorNormal(MenuWindow* window, u8 useSub);
u8 menuCursorCmp(MenuCursor* a, MenuCursor* b);
u8 menuSetEnablePort(u8 enable);

s32 menuGetLastError(void) {
    return winSysWork.lastError;
}

void menuGetOffScreenFlag(void) {
    menuOffScreenCheckEnable(0);
}

void menuReleaseOffScreen(f32 time) {
    menuOffScreenFadeSet(0.0f, time);
    menuOffScreenFadeSync(1);
    menuOffScreenRelease();
}

void menuCreateOffScreen(f32 arg0, f32 arg1) {
    menuOffScreenCreate(1);
    menuOffScreenSetDisp(1);
    menuOffScreenSetPriority(1);
    menuOffScreenFadeSet(arg1, arg0);
}

s32 menuGetSelectItemNum(s32 id) {
    s32 count = 0;
    const MenuData* data;
    const MenuItem* item;
    s32 index;

    data = menuDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }

    index = data->firstItem;
    for (;;) {
        item = menuItemBiosGetPtr(id, index);
        if (item->selectable) {
            count++;
        }
        if (item->last) {
            break;
        }
        index = item->next;
    }
    return count;
}

s32 menuGetCursorFromItemID(s32 id, u32 itemId) {
    const MenuData* data;
    const MenuItem* item;
    s32 index;
    s32 cursor;

    data = menuDataBiosGetPtr(id);
    if (data == 0) {
        return -3;
    }

    cursor = 0;
    index = data->firstItem;
    for (;;) {
        item = menuItemBiosGetPtr(id, index);
        if ((s16)index == itemId) {
            if (item->selectable) {
                return cursor;
            }
            return -1;
        }
        if (item->selectable) {
            cursor++;
        }
        if (item->last) {
            break;
        }
        index = item->next;
    }
    return -2;
}

bool menuGetDisp(s32 id) {
    MenuWindow* window = windowSearchID(id);
    if (window == 0) {
        return 0;
    }
    return (window->flags & 2) != 0;
}

void menuSetDisp(s32 id, u8 enable) {
    MenuWindow* window = windowSearchID(id);

    if (window == 0) {
        return;
    }
    if (enable) {
        window->flags |= 2;
    } else {
        window->flags &= ~2;
    }
}

s32 menuGetCursorItemID(s32 id) {
    const MenuData* data;
    const MenuItem* item;
    s32 cursor;
    s32 index;
    s32 count;

    cursor = menuGetCursor(id);
    if (cursor == -1) {
        return 0;
    }

    data = menuDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }

    count = 0;
    index = data->firstItem;
    for (;;) {
        item = menuItemBiosGetPtr(id, index);
        if (item->selectable) {
            if (count == cursor) {
                return (s16)index;
            }
            count++;
        }
        if (item->last) {
            break;
        }
        index = item->next;
    }
    return 0;
}

s32 menuSetCursor(s32 id, s8 cursor) {
    MenuWindow* window = windowSearchID(id);

    if (window != 0) {
        window->cursor.p.offset = cursor;
    } else {
        return -1;
    }
    return 0;
}

s32 menuGetCursor(s32 id) {
    MenuWindow* window = windowSearchID(id);
    if (window != 0) {
        return window->cursor.p.offset + window->cursor.p.base;
    }
    return -1;
}

s32 menuCloseSync(s32 id, u8 wait) {
    if (wait) {
        for (;;) {
            if (windowSearchID(id) == 0) {
                return 0;
            }
            if (GSthreadGetCurrentThread() == 0) {
                GSlogWrite("%s(0x%08x)  スレッドから呼ぶようにしてください\n", __FUNCTION__, id);
                break;
            }
            GSthreadSwitch();
        }
    } else {
        return windowSearchID(id) != 0;
    }
    return 0;
}

void menuCloseFloor(void) {
    windowClose(0, 4);
}

void menuClose(s32 id) {
    if (id == 0) {
        id = windowGetActiveID();
    }
    menuCloseCustom(id, 0, 0);
}

s32 menuCloseCustom(s32 id, u32 flags, u8 wait) {
    MenuWindow* window = windowSearchID(id);
    if (window == 0) {
        return 1;
    }
    windowClose(window, flags);
    menuCloseSync(id, wait);
    return 0;
}

s32 menuIsCheck(s32 id) {
    return windowSearchID(id) != 0;
}

void menuOpen(s32 menu_id, u8 check_cursor) {
    menuOpenCustom(menu_id, windowGetActiveID(), 0, 0, check_cursor, 0);
}

s32 menuOpenCustom(s32 menu_id, s32 parent_id, s32* cursor_out, u32 close_flags, u8 check_cursor, s32 open_param, ...) {
    va_list args;
    MenuWindow* window;
    const MenuData* data;
    MenuCursor cursor;
    s32 value = 0;

    va_start(args, open_param);
    window = windowOpen(cursor_out, menu_id, parent_id, close_flags, open_param, args);

    if (check_cursor) {
        windowCheckCursor(menu_id, check_cursor);
        value = windowGetValue(menu_id);
        data = menuDataBiosGetPtr(menu_id);
        if (data->cursorID != 0) {
            cursor = window->cursor;
            cursorBiosSetPos(data->cursorID, &cursor);
        }
        if (cursor_out != 0) {
            *cursor_out = menuGetCursor(menu_id);
        }
    }

    if (close_flags & 1) {
        menuCloseCustom(menu_id, 0, check_cursor);
    }
    return value;
}

void menuSetPosition(s32 id, s16 x, s16 y) {
    MenuWindow* window = windowSearchID(id);

    if (window == 0) {
        return;
    }
    window->x = x;
    window->y = y;
}

void menuDaemon(void) {
    MenuWindow* node;
    u8 doFade = 1;
    MenuSprite* sprite;
    s32 layer;
    MenuWindow* w;
    f64 dt;
    f32 total;
    MenuWindow* active;
    WINDOW_SYS_WORK* sys;
    s32 i;
    const MenuData* data;

    GSgfxLayerSetActive(7);
    active = windowSearchID(windowGetActiveID());
    _menuUpdateKeyInfo(&winSysWork, &winSysWork2);
    menuOffScreenDraw();
    dt = _gettLastTime();
    total = _currentAddTime + (f32)dt;
    _currentTime = dt;
    _menuCount++;
    _currentAddTime = total;
    if (total > 1.0f) {
        _currentAddTime = total - 1.0f;
    }

    sys = &winSysWork;
    for (node = sys->head; node != 0; node = node->next) {
        data = menuDataBiosGetPtr(node->id);
        switch (node->phase) {
        case 0:
            node->phase = 1;
            node->phaseFrame = 0;
            break;
        case 1:
            if (winSeqCheckMove(node->id) == 0) {
                if (data->f2a == 0) {
                    node->close = 1;
                }
                node->phase = 2;
                node->phaseFrame = 0;
            }
            break;
        case 2:
            if (node->transitionDone != 0) {
                menuPlaySe(node->id, 5);
                node->phase = 3;
                node->phaseFrame = 0;
            }
            break;
        case 3:
            if (winSeqCheckMove(node->id) == 0) {
                node->phase = 4;
                node->phaseFrame = 0;
            }
            break;
        case 4:
            break;
        }

        if (pauseIsPause() == 0 && active != 0 && node == active) {
            if (node->close == 0) {
                switch (node->phase) {
                case 2:
                    switch (data->f2a) {
                    case 0:
                        node->close = 1;
                        break;
                    case 1:
                        menuButtonNormal(node);
                        break;
                    case 2:
                        break;
                    case 3:
                        floorExecScriptIntegerByName("menu_button", 0, 0, 0, 0);
                        break;
                    case 4:
                        data->buttonCallback(node);
                        break;
                    }

                    if ((node->cursorFlags & 8) != 0 && node->back != 0) {
                        node->back = 0;
                        node->close = 0;
                    }

                    if (node->close != 0) {
                        sys->lastError = 0;
                        sys->lastID = node->id;
                    } else if ((windowGetKeyInfo()->on & 0x8000) != 0) {
                        sys->lastError = 1;
                        sys->lastID = node->id;
                        if ((node->cursorFlags & 0x10) == 0) {
                            node->close = 1;
                            node->back = 1;
                        }
                    }
                    break;
                case 3:
                    break;
                }

                if (node->back != 0) {
                    menuPlaySe(node->id, 3);
                } else if (node->close != 0) {
                    menuPlaySe(node->id, 2);
                }
            }

            if (node->close == 0) {
                switch (node->phase) {
                case 2:
                    node->prev.p.base = node->cursor.p.base;
                    node->prev.p.offset = node->cursor.p.offset;
                    if (node->cursorCount > 0) {
                        switch (node->cursorMode) {
                        case 1:
                        case 2:
                            menuCursorNormal(node, 1);
                            break;
                        case 3:
                            floorExecScriptIntegerByName("menu_cursor", 0, 0, 0, 0);
                            break;
                        case 4:
                            data->cursorCallback(node);
                            break;
                        }
                        {
                            MenuCursor oldPos;
                            MenuCursor newPos;
                            newPos = node->cursor;
                            oldPos = node->prev;
                            if (menuCursorCmp(&oldPos, &newPos) != 0) {
                                windowCreateCursorSprite(node);
                                menuPlaySe(node->id, 1);
                            }
                        }
                    }
                    break;
                }
            }
        }

        if ((node->flags & 4) != 0) {
            if (pauseIsPause() == 0) {
                winSeqMoveMenu(node);
            }
            if (data->tickCallback != 0) {
                data->tickCallback(node);
            }
        }
    }

    for (node = sys->head; node != 0; node = node->next) {
        if (node->phase == 4) {
            windowCloseMain(node);
        }
    }

    layer = floorGetMenuLayerID();
    for (w = sys->head; w != 0; w = w->next) {
        node = w;
        if (doFade != 0 && node->fadePriority >= 0x50) {
            doFade = 0;
            fadeDaemon();
        }
        if ((node->flags & 2) != 0) {
            s32 layerID = node->layerID;
            spriteSetOffset(layerID, node->x, node->y);
            spriteClearScissor(layerID);
            spriteSetEnv(layerID);
            spriteSetOffset(layer, node->x, node->y);
            spriteClearScissor(layer);
            spriteSetEnv(layer);
            for (sprite = node->sprites; sprite != 0; sprite = sprite->next) {
                winSpriteDraw(node, sprite);
            }
            i = 0;
            for (sprite = node->overlaySprites; sprite != 0; sprite = sprite->next) {
                menuItemBiosGetPtr(node->id, sprite->id);
                winSpriteDraw(node, sprite);
                if (i != 0 && node->phase == 3) {
                    winSetSequence(sprite->seq, 0);
                }
                i++;
            }
            data = menuDataBiosGetPtr(node->id);
            if (data->drawCallback != 0) {
                data->drawCallback(node);
            }
        }
    }

    spriteSetOffset(7, 0, 0);
    spriteClearScissor(7);
    spriteClearEnv(7);
    spriteSetOffset(layer, 0, 0);
    spriteClearScissor(layer);
    spriteClearEnv(layer);
    if (doFade != 0) {
        fadeDaemon();
    }
    GSgfxLayerSetActive(2);
}

f32 menuGetTotalTime(void) {
    return _currentAddTime;
}

f32 menuGetLastTime(void) {
    return _currentTime;
}

}

static f64 _gettLastTime(void) {
    return timeGetLastFrameSec();
}

extern "C" {

void menuButtonNormal(MenuWindow* node) {
    u16 keys;
    if (node != 0) {
        keys = windowGetKeyInfo()->trg;
        if (keys & 0x10) {
            node->close = 1;
        }
        if (keys & 0x20) {
            node->close = 1;
            node->back = 1;
        }
    }
}

static inline MenuItem* menuItemNext(MenuWindow* window, MenuItem* item) {
    return menuItemBiosGetPtr(window->id, item->next);
}

void menuCursorNormal(MenuWindow* window, u8 useSub) {
    s8 index;
    int cross;
    int best;
    int up;
    int down;
    u16 wrap;
    MenuData* data;
    int left;
    u16 keys;
    int xRange;
    MenuItem* current;
    MenuItem* item;
    int yRange;
    int delta;
    int right;

    wrap = 0;
    if (window == NULL) {
        return;
    }
    if (window->cursorMode == 2) {
        wrap = 1;
    }

    data = menuDataBiosGetPtr(window->id);
    current = windowGetCursorToItem(window);
    if (current == NULL) {
        window->cursor.p.offset = 0;
        return;
    }

    xRange = 16;
    yRange = 12;
    keys = windowGetKeyInfo()->rep;
    u16 on = windowGetKeyInfo()->on;
    u16 add;
    if (useSub) {
        if ((on & 0xF) != 0) {
            add = 0;
        } else {
            add = windowGetKeyInfo2()->rep;
        }
    } else {
        add = 0;
    }
    keys |= add;
    up = keys & 1;
    down = keys & 2;
    left = keys & 4;
    right = keys & 8;

    for (;;) {
        index = 0;
        item = menuItemBiosGetPtr(window->id, data->firstItem);
        if (up) {
            best = 480;
            for (;;) {
                if (item->selectable) {
                    delta = current->y - item->y;
                    if (delta > 0) {
                        cross = current->x - item->x;
                        if (cross < 0) {
                            cross = -cross;
                        }
                        if (cross < xRange && best > delta) {
                            best = delta;
                            window->cursor.p.offset = index;
                        }
                    }
                    index++;
                }
                if (item->last) {
                    break;
                }
                item = menuItemNext(window, item);
            }
        } else if (down) {
            best = 480;
            for (;;) {
                if (item->selectable) {
                    delta = item->y - current->y;
                    if (delta > 0) {
                        cross = current->x - item->x;
                        if (cross < 0) {
                            cross = -cross;
                        }
                        if (cross < xRange && best > delta) {
                            best = delta;
                            window->cursor.p.offset = index;
                        }
                    }
                    index++;
                }
                if (item->last) {
                    break;
                }
                item = menuItemNext(window, item);
            }
        } else if (left) {
            best = 640;
            for (;;) {
                if (item->selectable) {
                    delta = current->x - item->x;
                    if (delta > 0) {
                        cross = current->y - item->y;
                        if (cross < 0) {
                            cross = -cross;
                        }
                        if (cross < yRange && best > delta) {
                            best = delta;
                            window->cursor.p.offset = index;
                        }
                    }
                    index++;
                }
                if (item->last) {
                    break;
                }
                item = menuItemNext(window, item);
            }
        } else if (right) {
            best = 640;
            for (;;) {
                if (item->selectable) {
                    delta = item->x - current->x;
                    if (delta > 0) {
                        cross = current->y - item->y;
                        if (cross < 0) {
                            cross = -cross;
                        }
                        if (cross < yRange && best > delta) {
                            best = delta;
                            window->cursor.p.offset = index;
                        }
                    }
                    index++;
                }
                if (item->last) {
                    break;
                }
                item = menuItemNext(window, item);
            }
        }

        if (window->prev.p.offset != window->cursor.p.offset) {
            break;
        }
        xRange = xRange + 16;
        yRange = yRange + 12;
        if (xRange >= 640) {
            xRange = 640;
        }
        if (yRange >= 480) {
            yRange = 480;
        }
        if (xRange == 640 && yRange == 480) {
            break;
        }
    }

    if (wrap == 0) {
        return;
    }

    xRange = 16;
    yRange = 12;
    for (;;) {
        if (window->prev.p.offset != window->cursor.p.offset) {
            return;
        }
        item = menuItemBiosGetPtr(window->id, data->firstItem);
        index = 0;
        if (up) {
            best = 0;
            for (;;) {
                if (item->selectable) {
                    delta = item->y - current->y;
                    if (delta > 0) {
                        cross = current->x - item->x;
                        if (cross < 0) {
                            cross = -cross;
                        }
                        if (cross < xRange && best < delta) {
                            best = delta;
                            window->cursor.p.offset = index;
                        }
                    }
                    index++;
                }
                if (item->last) {
                    break;
                }
                item = menuItemNext(window, item);
            }
        } else if (down) {
            best = 0;
            for (;;) {
                if (item->selectable) {
                    delta = current->y - item->y;
                    if (delta > 0) {
                        cross = current->x - item->x;
                        if (cross < 0) {
                            cross = -cross;
                        }
                        if (cross < xRange && best < delta) {
                            best = delta;
                            window->cursor.p.offset = index;
                        }
                    }
                    index++;
                }
                if (item->last) {
                    break;
                }
                item = menuItemNext(window, item);
            }
        } else if (left) {
            best = 0;
            for (;;) {
                if (item->selectable) {
                    delta = item->x - current->x;
                    if (delta > 0) {
                        cross = current->y - item->y;
                        if (cross < 0) {
                            cross = -cross;
                        }
                        if (cross < yRange && best < delta) {
                            best = delta;
                            window->cursor.p.offset = index;
                        }
                    }
                    index++;
                }
                if (item->last) {
                    break;
                }
                item = menuItemNext(window, item);
            }
        } else if (right) {
            best = 0;
            for (;;) {
                if (item->selectable) {
                    delta = current->x - item->x;
                    if (delta > 0) {
                        cross = current->y - item->y;
                        if (cross < 0) {
                            cross = -cross;
                        }
                        if (cross < yRange && best < delta) {
                            best = delta;
                            window->cursor.p.offset = index;
                        }
                    }
                    index++;
                }
                if (item->last) {
                    break;
                }
                item = menuItemNext(window, item);
            }
        }

        xRange = xRange + 16;
        yRange = yRange + 12;
        if (xRange >= 640) {
            xRange = 640;
        }
        if (yRange >= 480) {
            yRange = 480;
        }
        if (xRange == 640 && yRange == 480) {
            break;
        }
    }
}

void menuPlaySe(s32 id, s32 event) {
    void* se;
    u16 snd;
    if (menuGetDisp(id) != 0) {
        se = menuSeBiosGetPtr(menuDataBiosGetPtr(id)->f1a);
        if (se != 0) {
            snd = menuSeBiosGetSndId(se, event);
            if (snd != 0) {
                GSsndPlayNow(snd);
            }
        }
    }
}

}

static u8 _menuGetAgbKeyInfo(s32 port, u16* keys) {
    s32 device;
    u16 buttons;
    u16 result;

    device = port + 1;
    result = 0;
    if (gbaCommandIsConnected(device) == 0) {
        return 0;
    }

    buttons = gbaCommandKeyPressed(device);
    if (buttons & 0x40) result |= 0x1;
    if (buttons & 0x80) result |= 0x2;
    if (buttons & 0x20) result |= 0x4;
    if (buttons & 0x10) result |= 0x8;
    if (buttons & 0x1) result |= 0x10;
    if (buttons & 0x2) result |= 0x20;
    if (buttons & 0x4) result |= 0x100;
    if (buttons & 0x200) result |= 0x200;
    if (buttons & 0x100) result |= 0x400;
    if (buttons & 0x8) result |= 0x800;

    *keys = result;
    return 1;
}

static u8 _menuGetGcKeyInfo(s32 port, u16* keys, u16* keys2) {
    s32 padIds[4] = { 1, 2, 3, 4 };
    u16 result = 0;
    u16 result2 = 0;
    s32 padId;
    u32 lx;
    u32 ly;
    u32 rx;
    u32 ry;
    u32 buttons;
    f32 angle;

    padId = padIds[port];
    if (GSinputIsConnected(padId) == 0) {
        return 0;
    }

    ly = GSinputGetLeftStickYData(padId, 0);
    lx = GSinputGetLeftStickXData(padId, 0);
    ry = GSinputGetRightStickYData(padId, 0);
    rx = GSinputGetRightStickXData(padId, 0);

    if (((s8)lx < 0 ? -(s8)lx : (s8)lx) > 0x20 || ((s8)ly < 0 ? -(s8)ly : (s8)ly) > 0x20) {
        angle = atan2((s8)lx, (s8)ly);
        if ((angle > 0.0f ? angle : -angle) < 0.9599311f) {
            result |= 2;
        } else if ((angle > 0.0f ? angle : -angle) > 2.1816616f) {
            result |= 1;
        }
        if (0.61086524f < (angle > 0.0f ? angle : -angle) &&
            (angle > 0.0f ? angle : -angle) < 2.5307274f) {
            if (angle < 0.0f) {
                result |= 4;
            } else {
                result |= 8;
            }
        }
    }

    if (((s8)rx < 0 ? -(s8)rx : (s8)rx) > 0x16 || ((s8)ry < 0 ? -(s8)ry : (s8)ry) > 0x16) {
        angle = atan2((s8)rx, (s8)ry);
        if ((angle > 0.0f ? angle : -angle) < 0.9599311f) {
            result2 |= 2;
        } else if ((angle > 0.0f ? angle : -angle) > 2.1816616f) {
            result2 |= 1;
        }
        if (0.61086524f < (angle > 0.0f ? angle : -angle) &&
            (angle > 0.0f ? angle : -angle) < 2.5307274f) {
            if (angle < 0.0f) {
                result2 |= 4;
            } else {
                result2 |= 8;
            }
        }
    }

    buttons = GSinputButtonsPressed(padId);
    if (buttons & 0x8) result |= 0x1;
    if (buttons & 0x4) result |= 0x2;
    if (buttons & 0x1) result |= 0x4;
    if (buttons & 0x2) result |= 0x8;
    if (buttons & 0x100) result |= 0x10;
    if (buttons & 0x200) result |= 0x20;
    if (buttons & 0x400) result |= 0x40;
    if (buttons & 0x800) result |= 0x80;
    if (buttons & 0x10) result |= 0x100;
    if (buttons & 0x40) result |= 0x200;
    if (buttons & 0x20) result |= 0x400;
    if (buttons & 0x1000) result |= 0x800;

    *keys = result;
    *keys2 = result2;
    return 1;
}

static void _menuUpdateKeyInfo(WINDOW_SYS_WORK* a, WINDOW_SYS_WORK* b) {
    KeyInfo* k1;
    u16 bit;
    s32 port;
    u16 keys;
    KeyInfo* k2;
    u16 keys2;
    s32 i;
    u16 repeat;
    u16 held;
    u16 pressed;
    MenuWindow* window;
    u16 repeat2;
    u8 type;
    u16 held2;

    for (port = 0; port < 4; port++) {
        k2 = &winSysWork2.port[port];
        k1 = &winSysWork.port[port];
        connect_bak[port] = connect[port];
        keys = 0;
        keys2 = 0;
        if (_menuGetGcKeyInfo(port, &keys, &keys2) == 0) {
            if (_menuGetAgbKeyInfo(port, &keys) == 0) {
                keys = 0;
                type = 0;
            } else {
                type = 2;
            }
        } else {
            type = 1;
        }

        switch (type) {
        case 0:
            switch (connect_bak[port]) {
            case 0:
            case 1:
            default:
                connect[port] = 0;
                break;
            case 2:
            case 3:
                connect[port] = 3;
                keys = 0x8000;
                break;
            }
            break;
        case 1:
            connect[port] = 1;
            break;
        case 2:
            switch (connect_bak[port]) {
            case 0:
            case 2:
            case 3:
            default:
                connect[port] = 2;
                break;
            case 1:
                connect[port] = 2;
                break;
            }
            break;
        default:
            connect[port] = type;
            break;
        }

        k1->up = k1->on;
        pressed = (k1->up ^ 0xFFFF) & keys;
        repeat = 0;
        held = 0;
        for (i = 0; i < 16; i++) {
            bit = 1 << i;
            if (bit & pressed) {
                k1->timer[i] = 15;
                repeat |= bit;
            } else if (keys & bit) {
                k1->timer[i] -= timeGetLastFrameTime();
                if (k1->timer[i] <= 0) {
                    k1->timer[i] = 5;
                    repeat |= bit;
                    held |= bit;
                } else {
                    held |= bit & k1->rel;
                }
            }
        }
        if (pressed & 0xF) {
            k1->timer[0] = 15;
            k1->timer[1] = 15;
            k1->timer[2] = 15;
            k1->timer[3] = 15;
        }
        k1->on = keys;
        k1->trg = pressed;
        k1->rep = repeat;
        k1->rel = held;

        k2->up = k2->on;
        pressed = (k2->up ^ 0xFFFF) & keys2;
        repeat2 = 0;
        held2 = 0;
        for (i = 0; i < 16; i++) {
            bit = 1 << i;
            if (pressed & bit) {
                k2->timer[i] = 15;
                repeat2 |= bit;
            } else if (keys2 & bit) {
                k2->timer[i] -= timeGetLastFrameTime();
                if (k2->timer[i] <= 0) {
                    k2->timer[i] = 5;
                    repeat2 |= bit;
                    held2 |= bit;
                } else {
                    held2 |= bit & k2->rel;
                }
            }
        }
        if (pressed & 0xF) {
            k2->timer[0] = 15;
            k2->timer[1] = 15;
            k2->timer[2] = 15;
            k2->timer[3] = 15;
        }
        k2->on = keys2;
        k2->trg = pressed;
        k2->rep = repeat2;
        k2->rel = held2;
    }

    window = windowSearchID(windowGetActiveID());
    if (window == 0) {
        type = 1;
    } else {
        type = window->keyPort;
    }
    winSysWork.key = *windowGetPortKeyInfo(type);
    winSysWork2.key = *windowGetPortKeyInfo2(type);
}

extern "C" {

void menuGetKeyInfo(KeyInfoRaw* out, s32 port) {
    KeyInfo info;
    u8 mask;

    switch (port) {
    case 1: mask = 1; break;
    case 2: mask = 2; break;
    case 3: mask = 4; break;
    case 4: mask = 8; break;
    default: mask = 0; break;
    }
    if (mask != 0) {
        info = *windowGetPortKeyInfo(mask);
    } else {
        memset(&info, 0, sizeof(info));
    }
    *out = *(KeyInfoRaw*)&info;
}

s32 menuSetStatus(s32 id, u8 status) {
    MenuWindow* window = windowSearchID(id);
    if (window == 0) {
        return 0;
    }
    window->cursorFlags = status;
    return 1;
}

u8 menuCursorCmp(MenuCursor* a, MenuCursor* b) {
    if ((a->p.base == b->p.base) && (a->p.offset == b->p.offset)) {
        return 0;
    }
    return 1;
}

u8 menuGetEnablePort(void) {
    return winSysWork.enablePort;
}

u8 menuSetEnablePort(u8 enable) {
    u8 old = winSysWork.enablePort;
    winSysWork.enablePort = enable;
    return old;
}

void menuInit(u16 windowCount) {
    s32 i;

    windowInit(windowCount);
    cursorBiosInit();
    menuOffScreenInit();
    menuFaceInit(0x19);
    menuSetEnablePort(1);
    for (i = 0; i < 4; i++) {
        connect[i] = 0;
        connect_bak[i] = 0;
    }
    GSgfxVFInit(&menuHyperModeVf);
    GSgfxVFCreate(&menuHyperModeVf);
    GSgfxVFSetElement(&menuHyperModeVf, 9, 0, 3, 0);
    GSgfxVFSetElement(&menuHyperModeVf, 0xb, 1, 5, 0);
    GSgfxVFSetElement(&menuHyperModeVf, 0xd, 1, 4, 0);
    GSgfxVFSetElement(&menuHyperModeVf, 0xe, 1, 4, 0);
    GSgfxVFSetElement(&menuHyperModeVf, 0xf, 1, 4, 0);
    GSresRegisterResource(GStextureLoad(uv_cmn_win_00), 0, 0x16BF1200, 0);
    GSresRegisterResource(GStextureLoad(uv_cmn_csr_00), 0, 0x16C11200, 0);
    GSresRegisterResource(GStextureLoad(uv_common_icon_00), 0, 0x21F41200, 0);
    GSresRegisterResource(GStextureLoad(tex_warning), 0, 0x21591200, 0);
    GSresRegisterResource(GStextureLoad(tex_warning_pstar), 0, 0x215A1200, 0);
    FlashSystemInitAll();
}

}
