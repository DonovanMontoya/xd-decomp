#pragma defer_codegen on
#pragma force_active on
enum GSgfxLayerID { GSGFX_LAYER_INVALID = -1, GSGFX_LAYER_DEFAULT = 2, GSGFX_LAYER_MENU = 7 };
#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/menuBattleDiskLayout.hpp>

BDisk gBDisk;



s32 deckDataVirtualDB_GetExplanetion1(u16);
s32 deckDataVirtualDB_GetExplanetion2(u16);
s32 deckDataVirtualDB_GetTitle(u16);
u8 deckDataVirtualDB_GetFlagData(u16);
static void drawPkmPanel(u32, tagWINDOW_WORK*, tagSPRITE_WORK*);

struct GSvec2 {
    f32 x;
    f32 y;
};
s32 cBattleDisk::mItemCurIdx[8] = {0x6F9, 0x6FB, 0x6FD, 0x6FF, 0x701, 0x703, 0x705, 0x707};
s32 cBattleDisk::mContentsCurIdx[15] = {0x76F, 0x770, 0x771, 0x772, 0x773, 0x774, 0x775, 0x776,
                                        0x777, 0x778, 0x7B6, 0x7B7, 0x7B8, 0x7B9, 0x7BA};

static s16 sRect[56] = {
    216, 6, 42, 42,
    0, 0, -264, 54,
    19, 7, 133, 18,
    30, 29, 95, 18,
    126, 29, 80, 18,
    154, 7, 19, 18,
    9, 29, 20, 15,
    6, 6, 42, 42,
    0, 0, 264, 54,
    64, 7, 133, 18,
    75, 29, 95, 18,
    171, 29, 80, 18,
    199, 7, 19, 18,
    54, 29, 20, 15
};

extern "C" {
Pokemon* heroBiosGetPokemonPtr(Hero*, u16);
s32 pokemonDataBiosGetStatusFaceMenuSpriteId(void*, s32);
void menuFaceDispFromID2(tagWINDOW_WORK*, tagSPRITE_WORK*, u16, GSvec2*);
void* memcpy(void*, const void*, u32);
u16 itemBiosGetItemDataId(void*);
u8 itemCheckValid(void*);
void* itemDataBiosGetPtr(u16);
s32 itemDataBiosGetName(void*);
s32 itemDataBiosGetDoc(void*);
void* heroItemGetItemKindToItemAryPtr(Hero*, s32, u16*, s32, s32, s32);
void fightReadResourceID(s32, s32);
void menuItemBiosSetSelectFlag(s32, s32, s32);
void menuPlaySe(s32, s32);
void menuCursorNormal(tagWINDOW_WORK*, s32);
u16 windowGetKeyRepeat(void);
void GSfloorPush(s32);
BDiskMenuData* menuDataBiosGetPtr(s32);
BDiskMenuItem* menuItemBiosGetPtr(s32, s16);
BDiskMenuItem* windowGetCursorToItem(tagWINDOW_WORK*);
u16* windowGetKeyInfo(void);
u16* windowGetKeyInfo2(void);
void fn_8009E6B8(tagWINDOW_WORK*, u8);
u32 heroGetPokeomCount(Hero*);
void menuSetPosition(s32, s16, s16);
void winSeqSetMenu(s32, s32);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
s32 pokemonGetStatus(Pokemon*, u16, u16, u16);
u8 menuSubGetPokemonSexForDisp(Pokemon*);
u16 pokemonGetSoubiItemDataId(Pokemon*);
void msgctrlSetValue(s32, s32);
s32 GSmsgGetGSchar(s32);
void GSmsgPrintRect(s32, s32, s32, s16, s16, u32, s32);
void GSmsgPrint2(s32, s32, s32, u32, s32);
void windowDrawSprite2(s16, s16, s16, s16, u32, tagWINDOW_WORK*, s32, s32, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
u8 winSeqCheckMove(s32);
u8 GSgfxVideoGetVsyncRate(void);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void fightFreeResourceID(s32, s32);
void menuClose(s32);
void menuCreateOffScreen(f32, f32);
void menuOffScreenFadeSync(s32);
void menuOffScreenSetPriority(s32);
s32 menuOpenCustom(s32, s32, ...);
void menuReleaseOffScreen(f32);
s32 windowGetActiveID(void);
}

static s32 getPanelIdx(u32, u8);
static void dispFace(u32, GSvec2*, tagWINDOW_WORK*, tagSPRITE_WORK*, Pokemon*);

extern "C" {

s32 fn_8009E664(tagWINDOW_WORK* win);

void fn_8009E6B8(tagWINDOW_WORK* window, u8 move);

s32 fn_8009E9FC(tagWINDOW_WORK* win);

s32 fn_8009EA68(tagWINDOW_WORK* win);

s32 BattleDiskContentsDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);

}

static s32 getPanelIdx(u32 id, u8 mode);

static void drawPkmPanel(unsigned long panel, tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);

static void dispFace(u32 index, GSvec2* pos, tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, Pokemon* pokemon);

static Pokemon* loadPkmFace(void* arg);

extern "C" {

s32 menuBdisk_selectL_Btn(tagWINDOW_WORK* win);

s32 fn_800A08C0(tagWINDOW_WORK* win);

s32 menuBattleDiskCtrl(void);

void menuBattleDiskExit(void);

extern "C" {
s32 menuOpen(s32,s32);
void GSfloorPop();
void GSthreadSwitch();
void* fightEncountDataBiosGetPtr(s32);
void fightEncountDataBiosSetDiskId(void *,u8);
void fightTrainerCreateFightTrainerDataIdToHero(u16,s32,Hero *,u16);
void menuFaceLoad(s32,Pokemon *(*)(void *),void *);
u8 menuFaceCheckLoading();
u8 menuItemBiosGetSelectFlag(s32,s32);
f32 timeGetLastFrameSec();
tagWINDOW_WORK* windowSearchID(s32);
void windowCreateCursorSprite(tagWINDOW_WORK *);
void menuCloseSync(s32,s32);
void winMsgOpen(s32,s32,s32,s32);
void winMsgClose(s32);
u16 fightEncount(u16);
void menuCloseCustom(s32,s32,s32);
}
extern "C++" {
u32 deckDataVirtualDB_GetAllyDeck(u16);
u32 deckDataVirtualDB_GetEnemyDeck(u16);
u8 deckDataVirtualDB_GetPokemonNum(u16);
}

static inline void clearBattleDiskPokemonPanels(void)
{
    for (s32 panel = 0; panel < 15; ++panel) {
        ((void (*)(s32,s32,bool))menuItemBiosSetSelectFlag)(0x109, cBattleDisk::mContentsCurIdx[panel], 0);
    }
}
static inline void setBattleDiskPokemonPanelFlags(void)
{
    bool selectable;
    for (s32 panel = 0; panel < 15; ++panel) {
        selectable = true;
        if (getPanelIdx(panel, gBDisk.unk16) == -1) {
            selectable = false;
        } else {
            unsigned long slot = getPanelIdx(panel, gBDisk.unk16);
            if (slot < 6) {
                if (heroGetPokeomCount(&gBDisk.heroes[0]) <= slot) {
                    selectable = false;
                }
            } else if (heroGetPokeomCount(&gBDisk.heroes[1]) <= slot - 6) {
                selectable = false;
            }
        }
        if (selectable) {
            switch (panel) {
            case 1:
                if (gBDisk.unk16 != 2) selectable = false;
                break;
            case 2:
                if (gBDisk.unk16 != 1) selectable = false;
                break;
            case 7:
                if (gBDisk.unk16 == 2) {
                    long pokemonCount = heroGetPokeomCount(&gBDisk.heroes[1]);
                    if (pokemonCount == 1) selectable = false;
                }
                break;
            case 8: {
                long pokemonCount;
                if (gBDisk.unk16 != 2 ||
                    (pokemonCount = heroGetPokeomCount(&gBDisk.heroes[1])) != 1) selectable = false;
                break;
            }
            case 9:
                if (menuItemBiosGetSelectFlag(0x109, cBattleDisk::mContentsCurIdx[8])) selectable = false;
                else if (gBDisk.unk16 != 2) selectable = false;
                break;
            case 10:
                if (menuItemBiosGetSelectFlag(0x109, cBattleDisk::mContentsCurIdx[8])) selectable = false;
                else if (gBDisk.unk16 != 1) selectable = false;
                break;
            }
        }
        ((void (*)(s32,s32,bool))menuItemBiosSetSelectFlag)(0x109, cBattleDisk::mContentsCurIdx[panel], selectable);
    }
}
extern "C" void menuBattleDiskMain(void);

static inline void updateDiskListFlags()
{
    for (s32 diskIndex = 0; diskIndex < 8; diskIndex++) {
        if (diskIndex < gBDisk.count) {
            ((void (*)(s32,s32,bool))menuItemBiosSetSelectFlag)(0xE8, cBattleDisk::mItemCurIdx[diskIndex], 1);
        } else {
            ((void (*)(s32,s32,bool))menuItemBiosSetSelectFlag)(0xE8, cBattleDisk::mItemCurIdx[diskIndex], 0);
        }
    }
}
void menuBattleDiskInit(void);

void menuBattleDiskCloseDoc(void);

void menuBattleDiskOpenDoc(u8 id);

s32 menuBattleDiskOpenDocPush(u8 id);

u16 menuBattleDiskGetResult(void);

u8 menuBattleDiskGetSelectID(void);

void menuBattleDiskOpenFight(void);

void menuBattleDiskOpen(void);

void spriteSetScissor(s32,s32,s32,s16,s16);
void spriteClearScissor(s32);
void menuPdaSubScrollBar(tagWINDOW_WORK*,tagSPRITE_WORK*,s32,s32,u32,s32,s32,s16*);
s32 BattleDiskItemDraw(tagWINDOW_WORK *win,tagSPRITE_WORK *spr);

s32 wazaGetStatus(s32,u16,s32,s32);
s32 zokuseiBiosGetSpriteID(u16);
s32 zokuseiGetPokemonSpriteID(void*,u16);
s32 pokemonDataBiosGetZokuseiDataId(void*,u16);
void windowDrawSprite(s32,s32,tagWINDOW_WORK*,s32,s32,s32);
s32 BattleDiskStatus(tagWINDOW_WORK *win,tagSPRITE_WORK *spr);

s32 heroBiosGetNamePtr(Hero*);
u32 FlashSystemGetNowFrame(u32);
u32 FlashSystemGetEndFrame(u32);
s32 BattleDiskBorADraw(tagWINDOW_WORK *win,tagSPRITE_WORK *spr);

}




void menuBattleDiskOpen(void) {
    gBDisk.mode = 0;
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    GSfloorPush(0x389);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(20.0f / GSgfxVideoGetVsyncRate());
}

void menuBattleDiskOpenFight(void) {
    if (gBDisk.selectedID != 0) {
        gBDisk.mode = 1;
        GSfloorPush(0x389);
    }
}

u8 menuBattleDiskGetSelectID(void) {
    return gBDisk.selectedID;
}

u16 menuBattleDiskGetResult(void) {
    return gBDisk.result;
}

s32 menuBattleDiskOpenDocPush(u8 id) {
    gBDisk.selectedID = id;
    gBDisk.mode = 2;
    menuCreateOffScreen(8.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    menuOffScreenSetPriority(0);
    menuOffScreenFadeSync(1);
    GSfloorPush(0x38D);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(8.0f / GSgfxVideoGetVsyncRate());
    gBDisk.mode = 1;
    return gBDisk.field24;
}

void menuBattleDiskOpenDoc(u8 id) {
    gBDisk.selectedID = id;
    menuOpenCustom(0xE9, windowGetActiveID(), 0, 2, 0, 0);
}

void menuBattleDiskCloseDoc(void) {
    menuClose(0xE9);
}

void menuBattleDiskInit(void)
{
    u16 itemCount;
    s32* items = (s32*)heroItemGetItemKindToItemAryPtr(
        Hero::getHeroPtr(), 7, &itemCount, 0, 0, 0);
    u16 diskCount = 0;
    fightReadResourceID(0x842, 0x18513400);
    for (s32 itemIndex = 0; itemIndex < itemCount; ++itemIndex, ++items) {
        s32* item = items;
        if (itemCheckValid(item)) {
            (*bdiskEntry(diskCount)).itemID = itemBiosGetItemDataId(item);
            (*bdiskEntry(diskCount)).name = itemDataBiosGetName(itemDataBiosGetPtr((*bdiskEntry(diskCount)).itemID));
            (*bdiskEntry(diskCount)).doc = itemDataBiosGetDoc(itemDataBiosGetPtr((*bdiskEntry(diskCount)).itemID));
            (*bdiskEntry(diskCount)).id = (u8)((*bdiskEntry(diskCount)).itemID - 0x215);
            (*bdiskEntry(diskCount)).explain1 = deckDataVirtualDB_GetExplanetion1((*bdiskEntry(diskCount)).id);
            (*bdiskEntry(diskCount)).explain2 = deckDataVirtualDB_GetExplanetion2((*bdiskEntry(diskCount)).id);
            (*bdiskEntry(diskCount)).title = deckDataVirtualDB_GetTitle((*bdiskEntry(diskCount)).id);
            ++diskCount;
        }
    }
    gBDisk.count = (s16)diskCount;
    updateDiskListFlags();
}

extern "C" void menuBattleDiskMain(void)
{
    s32 listCursor = 0;
    s32 documentChoice;
    u8 browsing = 1;
    switch (gBDisk.mode) {
    case 0:
        while (browsing) {
            listCursor = gBDisk.unk12;
            s32 selection = menuOpenCustom(0xE7, 0, &listCursor, 0, 1, 0, 0);
            if (selection == -1) {
                menuClose(0xE7);
                browsing = 0;
                gBDisk.selectedID = 0;
                gBDisk.result = 0;
                continue;
            }
            gBDisk.unk12 = selection;
            for (s32 frame = 0; frame < 6; ++frame) {
                GSthreadSwitch();
            }
            selection += gBDisk.scroll;
            s32 choice = menuOpen(0xE8, 1);
            u8 disk = (*bdiskEntry(selection)).id;
            s32 faceWork = 0;
            fightEncountDataBiosSetDiskId(fightEncountDataBiosGetPtr(14), disk);
            fightTrainerCreateFightTrainerDataIdToHero(
                (u8)deckDataVirtualDB_GetAllyDeck(disk), 0, &gBDisk.heroes[0], 14);
            fightTrainerCreateFightTrainerDataIdToHero(
                (u8)deckDataVirtualDB_GetEnemyDeck(disk), 0, &gBDisk.heroes[1], 14);
            menuFaceLoad(0, loadPkmFace, &faceWork);
            gBDisk.unk16 = deckDataVirtualDB_GetPokemonNum(disk);
            gBDisk.selectedID = disk;
            clearBattleDiskPokemonPanels();
            while (menuFaceCheckLoading()) {
                GSthreadSwitch();
            }
            menuClose(0xE7);
            menuClose(0xE8);
            switch (choice) {
            case 0:
                browsing = 0;
                break;
            case 1:
                gBDisk.slide = 0.0f;
                menuOpen(0xEB, 0);
                while (gBDisk.slide < 0.2f) {
                    GSthreadSwitch();
                    gBDisk.slide += timeGetLastFrameSec();
                }
                menuClose(0xEB);
                setBattleDiskPokemonPanelFlags();
                menuOpen(0x109, 0);
                s32 preview = 1;
                while (preview) {
                    GSthreadSwitch();
                    if (windowGetKeyInfo()[2] & 0x10) {
                        gBDisk.unk14 = windowSearchID(0x109)->cursor;
                        menuOpen(0xEC, 0);
                        for (;;) {
                            s32 selectedPokemon = gBDisk.unk14;
                            if ((unsigned long)selectedPokemon < heroGetPokeomCount(&gBDisk.heroes[0])) {
                                gBDisk.unk4 = 0x131;
                                gBDisk.unk6 = 0;
                            } else {
                                gBDisk.unk4 = 0;
                                gBDisk.unk6 = 0;
                            }
                            const s16 currentX = gBDisk.unk0;
                            menuSetPosition(0xEC, currentX, gBDisk.unk2);
                            GSthreadSwitch();
                            if (!(windowGetKeyInfo()[2] & 0x10)) {
                                fn_8009E6B8(windowSearchID(0x109), 1);
                            }
                            if (gBDisk.unk14 != windowSearchID(0x109)->cursor) {
                                windowCreateCursorSprite(windowSearchID(0x109));
                                const s16 cursor = windowSearchID(0x109)->cursor;
                                windowSearchID(0x109)->prevCursor = cursor;
                                gBDisk.unk14 = cursor;
                                menuPlaySe(0x109, 1);
                            }
                            if (windowGetKeyInfo()[2] & 0x20) break;
                        }
                        menuPlaySe(0x109, 3);
                        menuClose(0xEC);
                        menuCloseSync(0xEC, 1);
                        menuOpen(0x109, 0);
                    } else if (windowGetKeyInfo()[2] & 0x20) {
                        preview = 0;
                    }
                }
                menuClose(0x109);
                menuCloseSync(0x109, 1);
                break;
            case 2:
                break;
            }
        }
        break;
    case 1:
        gBDisk.result = 0;
        menuOpen(0xEA, 0);
        for (;;) {
            GSthreadSwitch();
            if (windowGetKeyInfo()[2] == 0x40) {
                winMsgOpen(2, deckDataVirtualDB_GetExplanetion1(gBDisk.selectedID), 1, 1);
                do {
                    GSthreadSwitch();
                } while (!(windowGetKeyInfo()[2] & 0x60));
                winMsgClose(1);
            } else if (windowGetKeyInfo()[2] == 0x10) {
                break;
            }
        }
        gBDisk.result = fightEncount(14);
        menuOpen(0xEA, 0);
        GSthreadSwitch();
        while (gBDisk.currentFrame < gBDisk.endFrame) {
            GSthreadSwitch();
        }
        while (!(windowGetKeyInfo()[2] & 0x30)) {
            GSthreadSwitch();
        }
        menuClose(0xEA);
        break;
    case 2: {
        documentChoice = 0;
        menuOpenCustom(0xE9, windowGetActiveID(), 0, 2, 0, 0);
        gBDisk.field24 = menuOpenCustom(0x8F, 0, &documentChoice, 0, 1, 0);
        menuCloseCustom(0x8F, 0, 1);
        menuClose(0xE9);
        menuCloseSync(0xE9, 1);
        menuOffScreenSetPriority(1);
        break;
    }
    }
    GSfloorPop();
    if (gBDisk.mode == 0 || gBDisk.mode == 2) {
        floorSetFadeScript(0, 0);
    }
}

void menuBattleDiskExit(void) {
    fightFreeResourceID(0x842, 0x18513400);
}

s32 menuBattleDiskCtrl(void) {
    return 0;
}

s32 fn_800A08C0(tagWINDOW_WORK* win) {
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
    return 0;
}

s32 menuBdisk_selectL_Btn(tagWINDOW_WORK* win) {
    s16 scroll;
    u16 key;
    key = windowGetKeyRepeat();
    scroll = gBDisk.scroll;
    gBDisk.unk12 = win->cursor;
    if (key & 2) {
        if (gBDisk.unk10 == gBDisk.unkE && win->cursor == 7 && gBDisk.scroll < gBDisk.count - 8) {
            gBDisk.scroll++;
            gBDisk.unkE = gBDisk.scroll * -0x1E;
            menuPlaySe(win->menu, 1);
        }
    } else if (key & 1) {
        if (gBDisk.unk10 == gBDisk.unkE && win->cursor == 0 && gBDisk.scroll != 0) {
            gBDisk.scroll--;
            gBDisk.unkE = gBDisk.scroll * -0x1E;
            menuPlaySe(win->menu, 1);
        }
    } else if (key & 4) {
        s16 pos;
        gBDisk.scroll -= 8;
        if (gBDisk.scroll < 0) {
            win->cursor = 0;
            gBDisk.unk12 = 0;
            gBDisk.scroll = 0;
        }
        if (scroll != gBDisk.scroll) {
            menuPlaySe(win->menu, 6);
        }
        pos = gBDisk.scroll * -0x1E;
        gBDisk.unkE = pos;
        gBDisk.unk10 = pos;
    } else if (key & 8) {
        s16 pos;
        if (gBDisk.count < 8) {
            s16 last;
            gBDisk.scroll = 0;
            last = gBDisk.count - 1;
            win->cursor = last;
            gBDisk.unk12 = last;
        } else {
            gBDisk.scroll += 8;
            if (gBDisk.count - 8 < gBDisk.scroll) {
                gBDisk.scroll = gBDisk.count - 8;
                win->cursor = 7;
                gBDisk.unk12 = 7;
            }
        }
        if (scroll != gBDisk.scroll) {
            menuPlaySe(win->menu, 6);
        }
        pos = gBDisk.scroll * -0x1E;
        gBDisk.unkE = pos;
        gBDisk.unk10 = pos;
    }
    menuCursorNormal(win, 1);
    return 0;
}

s32 BattleDiskItemDraw(tagWINDOW_WORK *win,tagSPRITE_WORK *spr) {
    s32 offset;
    BDiskEntry *entry;
    s32 i;
    s16 index=0;
    switch(spr->id) {
    case 0x6F9:case 0x6FB:case 0x6FD:case 0x6FF:case 0x701:case 0x703:case 0x705:
    case 0x70A:case 0x715:case 0x717:break;
    case 0x6EF:if(gBDisk.scroll!=0)winSpriteSetDisp(spr,1);else winSpriteSetDisp(spr,0);break;
    case 0x6EE:if(gBDisk.scroll<gBDisk.count-8)winSpriteSetDisp(spr,1);else winSpriteSetDisp(spr,0);break;
    case 0x708: {
        if(gBDisk.unkE<gBDisk.unk10)gBDisk.unk10-=6;
        else if(gBDisk.unkE>gBDisk.unk10)gBDisk.unk10+=6;
        BDiskMenuItem *rect=menuItemBiosGetPtr(win->menu,0x7B5);
        spriteSetScissor(winSpriteGetLayerID(win,spr),rect->x-spr->baseX,rect->y-spr->baseY,rect->width,rect->height);
        i=0;offset=0;entry=bdiskEntry(0);
        for(;i<gBDisk.count;offset+=30,entry=(BDiskEntry*)((u8*)entry+24),i++) {
            s16 y=gBDisk.unk10+offset;
            if(y>-64&&y<480) {
                GSmsgPrint2(winSpriteGetLayerID(win,spr),0,y,win->alpha|~0xFF,entry->name);
                if(deckDataVirtualDB_GetFlagData(entry->itemID-0x215)!=0)windowDrawSprite2(178,y+3,22,13,win->alpha|~0xFF,win,0x300,0,winSpriteGetLayerID(win,spr));
            }
        }
        spriteClearScissor(winSpriteGetLayerID(win,spr));
        break;
    }
    case 0x709:spr->value4C=bdiskEntry(gBDisk.unk12+gBDisk.scroll)->title;break;
    case 0x706:index=1;
    case 0x704:index++;
    case 0x702:index++;
    case 0x700:index++;
    case 0x6FE:index++;
    case 0x6FC:index++;
    case 0x6FA:index++;
    case 0x6F8:if(gBDisk.unk12==index)winSpriteSetDisp(spr,1);else winSpriteSetDisp(spr,0);break;
    case 0x718:index=1;
    case 0x716:index++;
    case 0x714:if(win->cursor==index)winSpriteSetDisp(spr,1);else winSpriteSetDisp(spr,0);break;
    case 0x727:spr->value4C=deckDataVirtualDB_GetTitle(gBDisk.selectedID);break;
    case 0x729:spr->value4C=deckDataVirtualDB_GetExplanetion1(gBDisk.selectedID);break;
    case 0x856: {
        s16 cursor[2];cursor[0]=*(s16*)((u8*)win+0x9C);cursor[1]=win->cursor;
        cursor[0]=gBDisk.scroll;
        menuPdaSubScrollBar(win,spr,win->menu,0x856,0xF06422FF,gBDisk.count,8,cursor);
        break;
    }
    }
    return 0;
}

static Pokemon* loadPkmFace(void* arg)
{
    Pokemon* pokemon=0;
    unsigned long* index=(unsigned long*)arg;
    if(*index<12) {
        if(*index<6) {
            if(*index<heroGetPokeomCount(&gBDisk.heroes[0]))
                pokemon=heroBiosGetPokemonPtr(&gBDisk.heroes[0],*index);
            else *index=6;
        }
        if(*index>=6) {
            unsigned long slot=(u16)(*index%6);
            if(slot<heroGetPokeomCount(&gBDisk.heroes[1]))
                pokemon=heroBiosGetPokemonPtr(&gBDisk.heroes[1],slot);
        }
    }
    (*index)++;
    return pokemon;
}

static void dispFace(u32 index, GSvec2* pos, tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, Pokemon* pokemon) {
    u8 backup[0x78];
    s32 face = pokemonDataBiosGetStatusFaceMenuSpriteId(pokemon->getPokemonDataPtr(), 0);
    memcpy(backup, sprite, 0x78);
    sprite->y = 0x2A;
    sprite->x = 0x2A;
    if (index < 6) {
        sprite->x *= -1;
    }
    menuFaceDispFromID2(win, sprite, face, pos);
    memcpy(sprite, backup, 0x78);
}

static void drawPkmPanel(unsigned long panel, tagWINDOW_WORK* window, tagSPRITE_WORK* sprite)
{
    Hero* hero;
    s16 slideX;
    Pokemon* pokemon;
    s32 rect;
    unsigned long slot;
    GSgfxLayerID layer;
    GSvec2 pos;
    layer = ((GSgfxLayerID (*)(tagWINDOW_WORK*,tagSPRITE_WORK*))winSpriteGetLayerID)(window, sprite);
    slot = panel;
    if (panel < 6) {
        hero = &gBDisk.heroes[0];
        rect = 0;
        if (gBDisk.slide < 0.2f) {
            slideX = -256.0f + 1280.0f * gBDisk.slide;
        } else {
            slideX = 0;
        }
    } else {
        slot = panel - 6;
        hero = &gBDisk.heroes[1];
        rect = 7;
        if (gBDisk.slide < 0.2f) {
            slideX = 256.0f - 1280.0f * gBDisk.slide;
        } else {
            slideX = 0;
        }
    }
    if (heroGetPokeomCount(hero) > slot) {
        pos.x = slideX + sRect[(rect + 0) * 4 + 0];
        pos.y = sRect[(rect + 0) * 4 + 1];
        pokemon = heroBiosGetPokemonPtr(hero, slot);
        if (pokemon) {
            u32 nickname = pokemonGetStatus(pokemon, 0, 0x77, 0);
            u32 hp = pokemonGetStatus(pokemon, 0, 0x83, 0);
            u32 level = pokemonGetStatus(pokemon, 0, 0x7A, 0);
            dispFace(panel, &pos, window, sprite, pokemon);
            windowDrawSprite2(
                slideX + sRect[(rect + 1) * 4 + 0],
                sRect[(rect + 1) * 4 + 1],
                sRect[(rect + 1) * 4 + 2],
                sRect[(rect + 1) * 4 + 3],
                window->alpha | 0xFFFFFF00, window, 0x2FC, 0, layer);
            msgctrlSetValue(0x37, nickname);
            GSgfxLayerID textLayer = layer;
            ((s32 (*)(GSgfxLayerID,s32,s32,s16,s16,u32,s32))GSmsgPrintRect)(textLayer, slideX + sRect[(rect + 2) * 4 + 0],
                           sRect[(rect + 2) * 4 + 1],
                           sprite->x, sprite->y,
                           window->alpha | 0xFFFFFF00, 0x4277);
            msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(0x42D4));
            ((s32 (*)(GSgfxLayerID,s32,s32,s16,s16,u32,s32))GSmsgPrintRect)(textLayer, slideX + sRect[(rect + 3) * 4 + 0],
                           sRect[(rect + 3) * 4 + 1],
                           sprite->x, sprite->y,
                           window->alpha | 0xFFFFFF00, 0x4276);
            msgctrlSetValue(0x34, level);
            ((s32 (*)(GSgfxLayerID,s32,s32,s16,s16,u32,s32))GSmsgPrintRect)(textLayer, slideX + sRect[(rect + 3) * 4 + 0] + 24,
                           sRect[(rect + 3) * 4 + 1],
                           sprite->x, sprite->y,
                           window->alpha | 0xFFFFFF00, 0x426F);
            msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(0x42D5));
            ((s32 (*)(GSgfxLayerID,s32,s32,s16,s16,u32,s32))GSmsgPrintRect)(textLayer, slideX + sRect[(rect + 4) * 4 + 0],
                           sRect[(rect + 4) * 4 + 1],
                           sprite->x, sprite->y,
                           window->alpha | 0xFFFFFF00, 0x4276);
            msgctrlSetValue(0x34, hp);
            ((s32 (*)(GSgfxLayerID,s32,s32,s16,s16,u32,s32))GSmsgPrintRect)(textLayer, slideX + sRect[(rect + 4) * 4 + 0] + 28,
                           sRect[(rect + 4) * 4 + 1],
                           sprite->x, sprite->y,
                           window->alpha | 0xFFFFFF00, 0x426F);
            u8 sex = menuSubGetPokemonSexForDisp(pokemon);
            u32 sexMessage;
            switch (sex) {
            case 0: sexMessage = 0x9C5; break;
            case 1: sexMessage = 0x9C6; break;
            case 2:
            default: sexMessage = 0; break;
            }
            if (sexMessage) {
                msgctrlSetValue(0x37, (unsigned long)GSmsgGetGSchar(sexMessage));
                GSmsgPrint2(textLayer, slideX + sRect[(rect + 5) * 4 + 0],
                            sRect[(rect + 5) * 4 + 1],
                            window->alpha | 0xFFFFFF00, 0x4276);
            }
            if (pokemonGetSoubiItemDataId(pokemon)) {
                windowDrawSprite2(
                    slideX + sRect[(rect + 6) * 4 + 0],
                    sRect[(rect + 6) * 4 + 1],
                    sRect[(rect + 6) * 4 + 2],
                    sRect[(rect + 6) * 4 + 3],
                    window->alpha | 0xFFFFFF00, window, 0x14B, 0, layer);
            }
        }
    }
}

static s32 getPanelIdx(u32 id, u8 mode) {
    s32 idx = -1;
    switch (id) {
    case 0:
        idx = 0;
        break;
    case 1:
        if (mode == 2) idx = 1;
        break;
    case 2:
        if (mode == 1) idx = 1;
        break;
    case 3:
        idx = 2;
        break;
    case 4:
        idx = 3;
        break;
    case 5:
        idx = 4;
        break;
    case 6:
        idx = 5;
        break;
    case 7:
        if (mode != 2 || (s32)heroGetPokeomCount(&gBDisk.heroes[1]) != 1) idx = 6;
        break;
    case 8:
        if (mode == 2 && (s32)heroGetPokeomCount(&gBDisk.heroes[1]) == 1) idx = 6;
        break;
    case 9:
        if (mode == 2 && (s32)heroGetPokeomCount(&gBDisk.heroes[1]) != 1) idx = 7;
        break;
    case 10:
        if (mode == 1) idx = 7;
        break;
    case 11:
        idx = 8;
        break;
    case 12:
        idx = 9;
        break;
    case 13:
        idx = 10;
        break;
    case 14:
        idx = 11;
        break;
    }
    return idx;
}

s32 BattleDiskContentsDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    u32 slot = 0;
    switch (sp->id) {
    case 0x751:
    case 0x752:
        break;
    case 0x753:
        if (gBDisk.unk16 == 1) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x754:
    case 0x755:
        if (gBDisk.unk16 == 2) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x756:
        if (gBDisk.unk16 == 2) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x76E:
        slot = 1;
    case 0x76D:
        slot++;
    case 0x76C:
        slot++;
    case 0x76B:
        slot++;
    case 0x76A:
        slot++;
    case 0x769:
        slot++;
    case 0x768:
        slot++;
    case 0x767:
        slot++;
    case 0x766:
        slot++;
    case 0x765:
        slot++;
    case 0x764:
        slot++;
    case 0x763:
        slot++;
    case 0x762:
        slot++;
    case 0x761:
        slot++;
    case 0x760: {
        BDisk* d = &gBDisk;
        if (getPanelIdx(slot, d->unk16) >= 0) {
            drawPkmPanel(getPanelIdx(slot, d->unk16), w, sp);
        }
        break;
    }
    case 0x779:
    case 0x77A:
    case 0x77B:
    case 0x77C:
    case 0x77D:
    case 0x77E:
    case 0x77F:
    case 0x780:
    case 0x781:
    case 0x782:
    case 0x783:
    case 0x784:
    case 0x785:
    case 0x786:
    case 0x787:
    case 0x788:
    case 0x789:
    case 0x78A:
    case 0x78B:
    case 0x78C:
    case 0x78D:
    case 0x78E:
    case 0x78F:
    case 0x790:
    case 0x791:
    case 0x792:
    case 0x793:
    case 0x794:
    case 0x795:
    case 0x796:
    case 0x797:
    case 0x798:
    case 0x799:
    case 0x79A:
    case 0x79B:
    case 0x79C:
    case 0x79D:
    case 0x79E:
    case 0x79F:
    case 0x7A0:
    case 0x7A1:
    case 0x7A2:
    case 0x7A3:
    case 0x7A4:
    case 0x7A5:
    case 0x7A6:
    case 0x7A7:
    case 0x7A8:
    case 0x7A9:
    case 0x7AA:
    case 0x7AB:
    case 0x7AC:
    case 0x7AD:
    case 0x7AE:
    case 0x7AF:
    case 0x7B0:
    case 0x7B1:
    case 0x7B2:
    case 0x7B3:
    case 0x7B4:
    case 0x7B5:
        break;
    case 0x7BB:
        sp->value4C = deckDataVirtualDB_GetExplanetion2(gBDisk.selectedID);
        break;
    case 0x7BC:
        if (w->menu != windowGetActiveID()) {
            sp->value4C = 0xE2E2;
        } else {
            sp->value4C = 0xE300;
        }
        break;
    case 0x7BD:
        if (w->menu == windowGetActiveID()) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    case 0x7BE:
        if (w->menu != windowGetActiveID()) {
            winSpriteSetDisp(sp, 1);
        } else {
            winSpriteSetDisp(sp, 0);
        }
        break;
    }
    return 0;
}

s32 BattleDiskBorADraw(tagWINDOW_WORK *win,tagSPRITE_WORK *spr) {
    u32 index=0;
    Hero *hero;
    GSvec2 pos;pos.x=0.0f;pos.y=0.0f;
    switch(spr->id) {
    case 0x738:index=1;
    case 0x737:index++;
    case 0x736:index++;
    case 0x735:index++;
    case 0x734:index++;
    case 0x733:{
        hero=&gBDisk.heroes[0];
        if(heroGetPokeomCount(hero)>index)dispFace(index,&pos,win,spr,heroBiosGetPokemonPtr(hero,index));break;
    }
    case 0x744:index=1;
    case 0x743:index++;
    case 0x742:index++;
    case 0x741:index++;
    case 0x740:index++;
    case 0x73F:{
        hero=&gBDisk.heroes[1];
        if(heroGetPokeomCount(hero)>index)dispFace(index,&pos,win,spr,heroBiosGetPokemonPtr(hero,index));break;
    }
    case 0x73E:index=1;
    case 0x73D:index++;
    case 0x73C:index++;
    case 0x73B:index++;
    case 0x73A:index++;
    case 0x739:
        winSpriteSetDisp(spr,0);
        if(index<heroGetPokeomCount(&gBDisk.heroes[0]))winSpriteSetDisp(spr,1);break;
    case 0x74A:index=1;
    case 0x749:index++;
    case 0x748:index++;
    case 0x747:index++;
    case 0x746:index++;
    case 0x745:
        winSpriteSetDisp(spr,0);
        if(index<heroGetPokeomCount(&gBDisk.heroes[1]))winSpriteSetDisp(spr,1);break;
    case 0x74B:
        spr->value4C=0;
        switch(gBDisk.result){case 2:case 3:spr->value4C=deckDataVirtualDB_GetExplanetion2(gBDisk.selectedID);break;}break;
    case 0x74C:
        spr->value4C=0;
        switch(gBDisk.result){case 2:case 3:spr->value4C=itemDataBiosGetName(itemDataBiosGetPtr(gBDisk.selectedID+0x215));break;default:spr->value4C=deckDataVirtualDB_GetTitle(gBDisk.selectedID);break;}break;
    case 0x74D:
        msgctrlSetValue(0x37,heroBiosGetNamePtr(&gBDisk.heroes[1]));
        GSmsgPrint2(winSpriteGetLayerID(win,spr),0,0,win->alpha|~0xFF,0x4276);break;
    case 0x74E:
        msgctrlSetValue(0x37,heroBiosGetNamePtr(&gBDisk.heroes[0]));
        GSmsgPrint2(winSpriteGetLayerID(win,spr),0,0,win->alpha|~0xFF,0x4276);break;
    case 0x7F2:
        switch(gBDisk.result){case 2:case 3:windowDrawSprite(0,0,win,0x303,0,winSpriteGetLayerID(win,spr));break;default:windowDrawSprite(0,0,win,0x305,0,winSpriteGetLayerID(win,spr));break;}break;
    case 0x7F3:
        switch(gBDisk.result){
        case 2:
            windowDrawSprite(0,0,win,0x314,0,winSpriteGetLayerID(win,spr));
            gBDisk.currentFrame=FlashSystemGetNowFrame(0x1F333000);
            gBDisk.endFrame=FlashSystemGetEndFrame(0x1F333000);break;
        case 3:case 4:case 7:
            windowDrawSprite(0,0,win,0x315,0,winSpriteGetLayerID(win,spr));
            gBDisk.currentFrame=FlashSystemGetNowFrame(0x1F343000);
            gBDisk.endFrame=FlashSystemGetEndFrame(0x1F343000);break;
        default:
            windowDrawSprite(0,0,win,0x316,0,winSpriteGetLayerID(win,spr));
            gBDisk.currentFrame=FlashSystemGetNowFrame(0x1F353000);
            gBDisk.endFrame=FlashSystemGetEndFrame(0x1F353000);break;
        }
    case 0x877:case 0x878:case 0x879:case 0x87A:case 0x87B:case 0x87C:case 0x87D:case 0x87E:
        switch(gBDisk.result){case 2:case 3:case 4:case 7:winSpriteSetDisp(spr,0);break;default:winSpriteSetDisp(spr,1);break;}break;
    }
    return 0;
}

s32 BattleDiskStatus(tagWINDOW_WORK *win,tagSPRITE_WORK *spr) {
    s32 moveLayer;
    Hero *hero;
    s32 index;
    s32 layer;
    u32 count;
    Hero *h;
    s32 slot;
    Pokemon *pokemon;
    index=0;
    layer=winSpriteGetLayerID(win,spr);
    hero=&gBDisk.heroes[0];
    count=heroGetPokeomCount(hero);
    slot=gBDisk.unk14;
    if((u32)slot<count){h=hero;}else{h=&gBDisk.heroes[1];slot-=count;}
    pokemon=h->getPokemon(slot);
    switch(spr->id) {
    case 0x791:
        msgctrlSetValue(0x37,pokemonGetStatus(pokemon,0,0x77,0));
        GSmsgPrintRect(layer,0,0,spr->x,spr->y,win->alpha|~0xFF,0x4277);break;
    case 0x792:{
        u32 msg;
        switch(menuSubGetPokemonSexForDisp(pokemon)){case 0:msg=0x9C5;break;case 1:msg=0x9C6;break;case 2:default:msg=0;break;}
        if(msg){msgctrlSetValue(0x37,GSmsgGetGSchar(msg));GSmsgPrint2(layer,0,0,win->alpha|~0xFF,0x4276);}break;
    }
    case 0x793:
        msgctrlSetValue(0x34,pokemonGetStatus(pokemon,0,0x7A,0));
        GSmsgPrintRect(layer,36,0,spr->x,spr->y,win->alpha|~0xFF,0x426F);break;
    case 0x7FA:
        msgctrlSetValue(0x34,pokemonGetStatus(pokemon,0,0x83,0));
        GSmsgPrintRect(layer,36,0,spr->x,spr->y,win->alpha|~0xFF,0x426F);break;
    case 0x78B:{
        u16 sprite=zokuseiGetPokemonSpriteID(pokemon->getPokemonDataPtr(),0);
        if(sprite)windowDrawSprite(0,0,win,sprite,0,winSpriteGetLayerID(win,spr));break;
    }
    case 0x78C:{
        u8 type=pokemonDataBiosGetZokuseiDataId(pokemon->getPokemonDataPtr(),0);
        if(type!=(u8)pokemonDataBiosGetZokuseiDataId(pokemon->getPokemonDataPtr(),1)){
            u16 sprite=zokuseiGetPokemonSpriteID(pokemon->getPokemonDataPtr(),1);
            windowDrawSprite(0,0,win,sprite,0,winSpriteGetLayerID(win,spr));
        }break;
    }
    case 0x790:index=1;
    case 0x78F:index++;
    case 0x78E:index++;
    case 0x78D:{
        s32 move=pokemonGetStatus(pokemon,0,0x7F,index);
        switch(move){case 0:case 0x164:case 0x165:case 0x166:case 0x167:case 0x168:case 0x169:case 0x16A:case 0x16B:case 0x16C:case 0x16D:case 0x16E:case 0x16F:case 0x170:case 0x171:case 0x172:case 0x173:case 0x174:case 0x175:break;case 0x176:windowDrawSprite(0,0,win,0x7B,0,winSpriteGetLayerID(win,spr));break;
        default:{moveLayer=winSpriteGetLayerID(win,spr);windowDrawSprite(0,0,win,zokuseiBiosGetSpriteID(wazaGetStatus(0,move,3,0)),0,moveLayer);break;}}
        break;
    }
    case 0x797:index=1;
    case 0x796:index++;
    case 0x795:index++;
    case 0x794:{
        u32 move=pokemonGetStatus(pokemon,0,0x7F,index);
        if(move&&wazaGetStatus(0,move,1,0)){
            msgctrlSetValue(0x37,GSmsgGetGSchar(wazaGetStatus(0,move,1,0)));
            GSmsgPrintRect(winSpriteGetLayerID(win,spr),0,0,spr->x,spr->y,win->alpha|~0xFF,0x4277);
        }break;
    }
    case 0x79D:
        msgctrlSetValue(0x34,pokemonGetStatus(pokemon,0,0x88,0));
        GSmsgPrintRect(winSpriteGetLayerID(win,spr),0,0,spr->x,spr->y,win->alpha|~0xFF,0x4287);break;
    case 0x79E:
        msgctrlSetValue(0x34,pokemonGetStatus(pokemon,0,0x89,0));
        GSmsgPrintRect(winSpriteGetLayerID(win,spr),0,0,spr->x,spr->y,win->alpha|~0xFF,0x4287);break;
    case 0x79F:
        msgctrlSetValue(0x34,pokemonGetStatus(pokemon,0,0x8A,0));
        GSmsgPrintRect(winSpriteGetLayerID(win,spr),0,0,spr->x,spr->y,win->alpha|~0xFF,0x4287);break;
    case 0x7A0:
        msgctrlSetValue(0x34,pokemonGetStatus(pokemon,0,0x8B,0));
        GSmsgPrintRect(winSpriteGetLayerID(win,spr),0,0,spr->x,spr->y,win->alpha|~0xFF,0x4287);break;
    case 0x7A1:
        msgctrlSetValue(0x34,pokemonGetStatus(pokemon,0,0x8C,0));
        GSmsgPrintRect(winSpriteGetLayerID(win,spr),0,0,spr->x,spr->y,win->alpha|~0xFF,0x4287);break;
    case 0x7A3:
        if(pokemonGetSoubiItemDataId(pokemon)){
            msgctrlSetValue(0x2D,pokemonGetSoubiItemDataId(pokemon));
            GSmsgPrintRect(winSpriteGetLayerID(win,spr),0,0,spr->x,spr->y,win->alpha|~0xFF,0x3AE7);
        }else{
            msgctrlSetValue(0x37,GSmsgGetGSchar(0x3C1A));
            GSmsgPrintRect(winSpriteGetLayerID(win,spr),0,0,spr->x,spr->y,win->alpha|~0xFF,0x4277);
        }break;
    }
    return 0;
}

s32 fn_8009EA68(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            s16 idx = gBDisk.unk14;
            if (idx < heroGetPokeomCount(&gBDisk.heroes[0])) {
                winSeqSetMenu(win->menu, 0x1EE);
            } else {
                winSeqSetMenu(win->menu, 0x1E6);
            }
            win->step = 1;
        }
        break;
    case 2:
        if (gBDisk.unk0 != gBDisk.unk4) {
            gBDisk.unk0 = gBDisk.unk4;
        }
        if (gBDisk.unk2 != gBDisk.unk6) {
            gBDisk.unk2 = gBDisk.unk6;
        }
        if (winSeqCheckMove(0xEC) == 0) {
            s16 idx = gBDisk.unk14;
            if (idx < heroGetPokeomCount(&gBDisk.heroes[0])) {
                gBDisk.unk4 = 0x131;
                gBDisk.unk6 = 0;
            } else {
                gBDisk.unk4 = 0;
                gBDisk.unk6 = 0;
            }
            menuSetPosition(0xEC, gBDisk.unk0, gBDisk.unk2);
        }
        break;
    case 3:
        if (win->step == 0) {
            s16 idx = gBDisk.unk14;
            if (idx < heroGetPokeomCount(&gBDisk.heroes[0])) {
                winSeqSetMenu(win->menu, 0x1F2);
            } else {
                winSeqSetMenu(win->menu, 0x1EA);
            }
            win->step = 1;
        }
        break;
    }
    return 0;
}

s32 fn_8009E9FC(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x17B);
            win->step = 1;
        }
        break;
    }
    return 0;
}

void fn_8009E6B8(tagWINDOW_WORK* window, u8 move)
{
    enum {
        kDirectionUp = 1,
        kDirectionDown = 2,
        kDirectionLeft = 4,
        kDirectionRight = 8,
        kDirectionMask = 15,
        kMenuFirstItemOffset = 6,
        kHorizontalRadiusStep = 16,
        kVerticalRadiusStep = 12,
        kMinimumHorizontalSeparation = 30
    };

    struct CursorTraversal {
        BDiskMenuItem* current;
        BDiskMenuItem* origin;
    };

    CursorTraversal traversal;
    u32 repeatKeys;
    u16 heldKeys;
    char* menuData;
    s32 searchUp;
    s32 searchDown;
    s32 searchLeft;
    s32 searchRight;
    signed char selectableIndex;
    s32 closestDistance;
    s32 horizontalRadius;
    s32 verticalRadius;

    if (window == 0) {
        return;
    }
    menuData = (char*)menuDataBiosGetPtr(window->menu);
    traversal.current = windowGetCursorToItem(window);
    if (traversal.current == 0) {
        window->cursor = 0;
        return;
    }
    horizontalRadius = kHorizontalRadiusStep;
    verticalRadius = kVerticalRadiusStep;
    repeatKeys = windowGetKeyInfo()[3];
    heldKeys = windowGetKeyInfo()[0];
    repeatKeys |= move != 0 ? ((heldKeys & kDirectionMask) != 0 ? 0 : windowGetKeyInfo2()[3]) : 0;
    searchUp = (u16)repeatKeys & kDirectionUp;
    searchDown = (u16)repeatKeys & kDirectionDown;
    searchLeft = (u16)repeatKeys & kDirectionLeft;
    searchRight = (u16)repeatKeys & kDirectionRight;
    for (;;) {
        traversal.origin = traversal.current;
        selectableIndex = 0;
        traversal.current = menuItemBiosGetPtr(window->menu, *(s16*)(menuData + kMenuFirstItemOffset));
        if (searchUp) {
            closestDistance = 480;
            for (;;) {
                if (traversal.current->enable) {
                    s32 dy = traversal.origin->y - traversal.current->y;
                    if (dy > 0) {
                        s32 dx = traversal.origin->x - traversal.current->x;
                        if (dx < 0) {
                            dx = -dx;
                        }
                        if (dx < horizontalRadius && closestDistance > dy) {
                            window->cursor = selectableIndex;
                            closestDistance = dy;
                        }
                    }
                    selectableIndex++;
                }
                if (traversal.current->last) {
                    break;
                }
                traversal.current = menuItemBiosGetPtr(window->menu, traversal.current->next);
            }
        } else if (searchDown) {
            closestDistance = 480;
            for (;;) {
                if (traversal.current->enable) {
                    s32 dy = traversal.current->y - traversal.origin->y;
                    if (dy > 0) {
                        s32 dx = traversal.origin->x - traversal.current->x;
                        if (dx < 0) {
                            dx = -dx;
                        }
                        if (dx < horizontalRadius && closestDistance > dy) {
                            window->cursor = selectableIndex;
                            closestDistance = dy;
                        }
                    }
                    selectableIndex++;
                }
                if (traversal.current->last) {
                    break;
                }
                traversal.current = menuItemBiosGetPtr(window->menu, traversal.current->next);
            }
        } else if (searchLeft) {
            closestDistance = 640;
            for (;;) {
                if (traversal.current->enable) {
                    s32 dx = traversal.origin->x - traversal.current->x;
                    if (dx > kMinimumHorizontalSeparation) {
                        s32 dy = traversal.origin->y - traversal.current->y;
                        if (dy < 0) {
                            dy = -dy;
                        }
                        if (dy < verticalRadius && closestDistance > dx) {
                            window->cursor = selectableIndex;
                            closestDistance = dx;
                        }
                    }
                    selectableIndex++;
                }
                if (traversal.current->last) {
                    break;
                }
                traversal.current = menuItemBiosGetPtr(window->menu, traversal.current->next);
            }
        } else if (searchRight) {
            closestDistance = 640;
            for (;;) {
                if (traversal.current->enable) {
                    s32 dx = traversal.current->x - traversal.origin->x;
                    if (dx > kMinimumHorizontalSeparation) {
                        s32 dy = traversal.origin->y - traversal.current->y;
                        if (dy < 0) {
                            dy = -dy;
                        }
                        if (dy < verticalRadius && closestDistance > dx) {
                            window->cursor = selectableIndex;
                            closestDistance = dx;
                        }
                    }
                    selectableIndex++;
                }
                if (traversal.current->last) {
                    break;
                }
                traversal.current = menuItemBiosGetPtr(window->menu, traversal.current->next);
            }
        }
        if (window->prevCursor != window->cursor) {
            break;
        }
        traversal.current = traversal.origin;
        horizontalRadius += kHorizontalRadiusStep;
        verticalRadius += kVerticalRadiusStep;
        if (horizontalRadius >= 640) {
            horizontalRadius = 640;
        }
        if (verticalRadius >= 480) {
            verticalRadius = 480;
        }
        if (horizontalRadius == 640 && verticalRadius == 480) {
            break;
        }
    }
}

s32 fn_8009E664(tagWINDOW_WORK* win) {
    if (winSeqCheckMove(0xEC) != 0) {
        return 0;
    }
    fn_8009E6B8(win, 1);
    return 0;
}
