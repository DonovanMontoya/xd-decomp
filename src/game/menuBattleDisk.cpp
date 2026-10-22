#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/menuBattleDiskLayout.hpp>

BDisk gBDisk;

Hero::Hero() {}

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

static s16 sRect[14][4] = {
    {216, 6, 42, 42},
    {0, 0, -264, 54},
    {19, 7, 133, 18},
    {30, 29, 95, 18},
    {126, 29, 80, 18},
    {154, 7, 19, 18},
    {9, 29, 20, 15},
    {6, 6, 42, 42},
    {0, 0, 264, 54},
    {64, 7, 133, 18},
    {75, 29, 95, 18},
    {171, 29, 80, 18},
    {199, 7, 19, 18},
    {54, 29, 20, 15}
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

s32 fn_8009E664(tagWINDOW_WORK* win) {
    if (winSeqCheckMove(0xEC) != 0) {
        return 0;
    }
    fn_8009E6B8(win, 1);
    return 0;
}

void fn_8009E6B8(tagWINDOW_WORK* win, u8 useKey2) {
    BDiskMenuData* data;
    BDiskMenuItem* cur;
    BDiskMenuItem* item;
    s32 limX;
    s32 limY;
    s32 best;
    s32 diff;
    s32 d;
    s8 idx;
    u16 key;
    u16 hold;
    if (win == 0) {
        return;
    }
    data = menuDataBiosGetPtr(win->menu);
    cur = windowGetCursorToItem(win);
    if (cur == 0) {
        win->cursor = 0;
        return;
    }
    limX = 0x10;
    limY = 0xC;
    key = windowGetKeyInfo()[3];
    hold = windowGetKeyInfo()[0];
    if (useKey2 != 0) {
        if ((hold & 0xF) != 0) {
            hold = 0;
        } else {
            hold = windowGetKeyInfo2()[3];
        }
    } else {
        hold = 0;
    }
    key |= hold;
    for (;;) {
        idx = 0;
        item = menuItemBiosGetPtr(win->menu, data->first);
        if (key & 1) {
            best = 0x1E0;
            for (;;) {
                if (item->enable) {
                    diff = cur->y - item->y;
                    if (diff > 0) {
                        d = cur->x - item->x;
                        if (d < 0) d = -d;
                        if (d < limX && best > diff) {
                            best = diff;
                            win->cursor = idx;
                        }
                    }
                    idx++;
                }
                if (item->last) break;
                item = menuItemBiosGetPtr(win->menu, item->next);
            }
        } else if (key & 2) {
            best = 0x1E0;
            for (;;) {
                if (item->enable) {
                    diff = item->y - cur->y;
                    if (diff > 0) {
                        d = cur->x - item->x;
                        if (d < 0) d = -d;
                        if (d < limX && best > diff) {
                            best = diff;
                            win->cursor = idx;
                        }
                    }
                    idx++;
                }
                if (item->last) break;
                item = menuItemBiosGetPtr(win->menu, item->next);
            }
        } else if (key & 4) {
            best = 0x280;
            for (;;) {
                if (item->enable) {
                    diff = cur->x - item->x;
                    if (diff > 0x1E) {
                        d = cur->y - item->y;
                        if (d < 0) d = -d;
                        if (d < limY && best > diff) {
                            best = diff;
                            win->cursor = idx;
                        }
                    }
                    idx++;
                }
                if (item->last) break;
                item = menuItemBiosGetPtr(win->menu, item->next);
            }
        } else if (key & 8) {
            best = 0x280;
            for (;;) {
                if (item->enable) {
                    diff = item->x - cur->x;
                    if (diff > 0x1E) {
                        d = cur->y - item->y;
                        if (d < 0) d = -d;
                        if (d < limY && best > diff) {
                            best = diff;
                            win->cursor = idx;
                        }
                    }
                    idx++;
                }
                if (item->last) break;
                item = menuItemBiosGetPtr(win->menu, item->next);
            }
        }
        if (win->prevCursor != win->cursor) break;
        limX += 0x10;
        limY += 0xC;
        if (limX >= 0x280) limX = 0x280;
        if (limY >= 0x1E0) limY = 0x1E0;
        if (limX == 0x280 && limY == 0x1E0) break;
    }
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

s32 BattleDiskContentsDraw(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    u32 idx = 0;
    switch (sprite->id) {
    case 0x751:
        break;
    case 0x753:
        if (gBDisk.unk16 == 1) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x754:
    case 0x755:
        if (gBDisk.unk16 == 2) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x756:
        if (gBDisk.unk16 == 2) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x76E:
        idx = 1;
    case 0x76D:
        idx += 1;
    case 0x76C:
        idx += 1;
    case 0x76B:
        idx += 1;
    case 0x76A:
        idx += 1;
    case 0x769:
        idx += 1;
    case 0x768:
        idx += 1;
    case 0x767:
        idx += 1;
    case 0x766:
        idx += 1;
    case 0x765:
        idx += 1;
    case 0x764:
        idx += 1;
    case 0x763:
        idx += 1;
    case 0x762:
        idx += 1;
    case 0x761:
        idx += 1;
    case 0x760:
        if (getPanelIdx(idx, gBDisk.unk16) >= 0) {
            drawPkmPanel(getPanelIdx(idx, gBDisk.unk16), win, sprite);
        }
        break;
    case 0x7BB:
        sprite->value4C = deckDataVirtualDB_GetExplanetion2(gBDisk.selectedID);
        break;
    case 0x7BC:
        if (win->menu != windowGetActiveID()) {
            sprite->value4C = 0xE2E2;
        } else {
            sprite->value4C = 0xE300;
        }
        break;
    case 0x7BD:
        if (win->menu == windowGetActiveID()) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x7BE:
        if (win->menu != windowGetActiveID()) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    return 0;
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

static void drawPkmPanel(u32 id, tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s32 layer = winSpriteGetLayerID(win, sprite);
    u32 index = id;
    Hero* hero;
    s32 base;
    s16 slide;
    if (id < 6) {
        base = 0;
        hero = &gBDisk.heroes[0];
        if (gBDisk.slide < 0.2f) {
            slide = (s16)(1280.0f * gBDisk.slide + -256.0f);
        } else {
            slide = 0;
        }
    } else {
        index = id - 6;
        hero = &gBDisk.heroes[1];
        base = 7;
        if (gBDisk.slide < 0.2f) {
            slide = (s16)-(1280.0f * gBDisk.slide - 256.0f);
        } else {
            slide = 0;
        }
    }
    if (heroGetPokeomCount(hero) > index) {
        s32 shift = slide;
        GSvec2 pos;
        Pokemon* pokemon;
        s32 sex;
        s32 level;
        s32 hp;
        pos.x = (f32)(shift + sRect[base][0]);
        pos.y = (f32)sRect[base][1];
        pokemon = heroBiosGetPokemonPtr(hero, index);
        if (pokemon != 0) {
            sex = pokemonGetStatus(pokemon, 0, 0x77, 0);
            level = pokemonGetStatus(pokemon, 0, 0x83, 0);
            hp = pokemonGetStatus(pokemon, 0, 0x7A, 0);
            dispFace(id, &pos, win, sprite, pokemon);
            windowDrawSprite2(shift + sRect[base + 1][0], sRect[base + 1][1], sRect[base + 1][2], sRect[base + 1][3],
                              win->alpha | ~0xFF, win, 0x2FC, 0, layer);
            msgctrlSetValue(0x37, sex);
            GSmsgPrintRect(layer, shift + sRect[base + 2][0], sRect[base + 2][1], sprite->x, sprite->y,
                           win->alpha | ~0xFF, 0x4277);
            msgctrlSetValue(0x37, GSmsgGetGSchar(0x42D4));
            GSmsgPrintRect(layer, shift + sRect[base + 3][0], sRect[base + 3][1], sprite->x, sprite->y,
                           win->alpha | ~0xFF, 0x4276);
            msgctrlSetValue(0x34, hp);
            GSmsgPrintRect(layer, shift + (sRect[base + 3][0] + 0x18), sRect[base + 3][1], sprite->x, sprite->y,
                           win->alpha | ~0xFF, 0x426F);
            msgctrlSetValue(0x37, GSmsgGetGSchar(0x42D5));
            GSmsgPrintRect(layer, shift + sRect[base + 4][0], sRect[base + 4][1], sprite->x, sprite->y,
                           win->alpha | ~0xFF, 0x4276);
            msgctrlSetValue(0x34, level);
            GSmsgPrintRect(layer, shift + (sRect[base + 4][0] + 0x1C), sRect[base + 4][1], sprite->x, sprite->y,
                           win->alpha | ~0xFF, 0x426F);
            {
                s32 msg;
                switch (menuSubGetPokemonSexForDisp(pokemon)) {
                case 0:
                    msg = 0x9C5;
                    break;
                case 1:
                    msg = 0x9C6;
                    break;
                default:
                    msg = 0;
                    break;
                }
                if (msg != 0) {
                    msgctrlSetValue(0x37, GSmsgGetGSchar(msg));
                    GSmsgPrint2(layer, shift + sRect[base + 5][0], sRect[base + 5][1], win->alpha | ~0xFF, 0x4276);
                }
            }
            if (pokemonGetSoubiItemDataId(pokemon) != 0) {
                windowDrawSprite2(shift + sRect[base + 6][0], sRect[base + 6][1], sRect[base + 6][2],
                                  sRect[base + 6][3], win->alpha | ~0xFF, win, 0x14B, 0, layer);
            }
        }
    }
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

static Pokemon* loadPkmFace(void* arg) {
    Pokemon *result;
    u32 *cursor;
    cursor = (u32 *)arg;
    result = 0;
    if (*cursor < 12) {
        if (*cursor < 6) {
            Hero* hero = &gBDisk.heroes[0];
            if (*cursor < heroGetPokeomCount(hero)) {
                result = heroBiosGetPokemonPtr(hero, *cursor);
            } else {
                *cursor = 6;
            }
        }
        if (*cursor >= 6) {
            u16 slot = *cursor % 6;
            Hero* hero = &gBDisk.heroes[1];
            if (slot < heroGetPokeomCount(hero)) {
                result = heroBiosGetPokemonPtr(hero, slot);
            }
        }
    }
    *cursor = *cursor + 1;
    return result;
}

extern "C" {

s32 menuBdisk_selectL_Btn(tagWINDOW_WORK* win) {
    s16 scroll;
    u16 key;
    key = windowGetKeyRepeat();
    gBDisk.unk12 = win->cursor;
    scroll = gBDisk.scroll;
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

s32 menuBattleDiskCtrl(void) {
    return 0;
}

void menuBattleDiskExit(void) {
    fightFreeResourceID(0x842, 0x18513400);
}

extern "C" {
s32 menuOpen(s32,s32);
void GSfloorPop();
void GSthreadSwitch();
void *fightEncountDataBiosGetPtr(s32);
void fightEncountDataBiosSetDiskId(void *,u8);
void fightTrainerCreateFightTrainerDataIdToHero(u16,s32,Hero *,u16);
void menuFaceLoad(s32,Pokemon *(*)(void *),void *);
u8 menuFaceCheckLoading();
u8 menuItemBiosGetSelectFlag(s32,s32);
f32 timeGetLastFrameSec();
tagWINDOW_WORK *windowSearchID(s32);
void windowCreateCursorSprite(tagWINDOW_WORK *);
void menuCloseSync(s32,s32);
void winMsgOpen(s32,s32,s32,s32);
void winMsgClose(s32);
s32 fightEncount(u32);
void menuCloseCustom(s32,s32,s32);
}
u8 deckDataVirtualDB_GetAllyDeck(u16);
u8 deckDataVirtualDB_GetEnemyDeck(u16);
u8 deckDataVirtualDB_GetPokemonNum(u16);

extern "C" void menuBattleDiskMain()
{
    s32 cursor=0;
    u8 running=1;
    switch(gBDisk.mode) {
    case 0:
        while(running) {
            cursor=gBDisk.unk12;
            s32 selected=menuOpenCustom(0xE7,0,&cursor,0,1,0,0);
            if(selected==-1) {
                menuClose(0xE7);
                running=0;
                gBDisk.selectedID=0;
                gBDisk.result=0;
            } else {
                gBDisk.unk12=selected;
                s32 frames=0;
                do {GSthreadSwitch();frames++;} while(frames<6);
                s32 index=selected+gBDisk.scroll;
                s32 action=menuOpen(0xE8,1);
                s32 faceIndex=0;
                u8 id=bdiskEntry(index)->id;
                fightEncountDataBiosSetDiskId(fightEncountDataBiosGetPtr(0xE),id);
                fightTrainerCreateFightTrainerDataIdToHero(deckDataVirtualDB_GetAllyDeck(id),0,&gBDisk.heroes[0],0xE);
                fightTrainerCreateFightTrainerDataIdToHero(deckDataVirtualDB_GetEnemyDeck(id),0,&gBDisk.heroes[1],0xE);
                menuFaceLoad(0,loadPkmFace,&faceIndex);
                gBDisk.unk16=deckDataVirtualDB_GetPokemonNum(id);
                gBDisk.selectedID=id;
                s32 *item=cBattleDisk::mContentsCurIdx;
                s32 i=0;
                do {menuItemBiosSetSelectFlag(0x109,*item,0);item++;i++;} while(i<15);
                while(menuFaceCheckLoading()!=0) GSthreadSwitch();
                menuClose(0xE7);
                menuClose(0xE8);
                switch(action) {
                case 0:
                    running=0;
                    break;
                case 1: {
                    gBDisk.slide=0.0f;
                    menuOpen(0xEB,0);
                    while(gBDisk.slide<0.2f) {
                        GSthreadSwitch();
                        gBDisk.slide+=timeGetLastFrameSec();
                    }
                    menuClose(0xEB);
                    u32 panel=0;
                    s32 *item=cBattleDisk::mContentsCurIdx;
                    do {
                        u8 enabled=1;
                        if(getPanelIdx(panel,gBDisk.unk16)==-1) {
                            enabled=0;
                        } else {
                            u32 pokemonIndex=getPanelIdx(panel,gBDisk.unk16);
                            if(pokemonIndex<6) {
                                if(heroGetPokeomCount(&gBDisk.heroes[0])<=pokemonIndex) enabled=0;
                            } else if(heroGetPokeomCount(&gBDisk.heroes[1])<=pokemonIndex-6) enabled=0;
                        }
                        if(enabled) {
                            switch(panel) {
                            case 1:if(gBDisk.unk16!=2)enabled=0;break;
                            case 2:if(gBDisk.unk16!=1)enabled=0;break;
                            case 7:
                                if(gBDisk.unk16==2 && heroGetPokeomCount(&gBDisk.heroes[1])==1)enabled=0;
                                break;
                            case 8:
                                if(gBDisk.unk16!=2 || heroGetPokeomCount(&gBDisk.heroes[1])!=1)enabled=0;
                                break;
                            case 9:
                                if(menuItemBiosGetSelectFlag(0x109,cBattleDisk::mContentsCurIdx[8]))enabled=0;
                                else if(gBDisk.unk16!=2)enabled=0;
                                break;
                            case 10:
                                if(menuItemBiosGetSelectFlag(0x109,cBattleDisk::mContentsCurIdx[8]))enabled=0;
                                else if(gBDisk.unk16!=1)enabled=0;
                                break;
                            }
                        }
                        menuItemBiosSetSelectFlag(0x109,*item,enabled);
                        item++;
                        panel++;
                    } while((s32)panel<15);
                    menuOpen(0x109,0);
                    s32 browsing=1;
                    while(browsing) {
                        GSthreadSwitch();
                        if(windowGetKeyInfo()[2]&0x10) {
                            gBDisk.unk14=windowSearchID(0x109)->cursor;
                            menuOpen(0xEC,0);
                            do {
                                s16 selected=gBDisk.unk14;
                                if((u32)selected<heroGetPokeomCount(&gBDisk.heroes[0])) {
                                    gBDisk.unk4=0x131;
                                    gBDisk.unk6=0;
                                } else {
                                    gBDisk.unk4=0;
                                    gBDisk.unk6=0;
                                }
                                menuSetPosition(0xEC,gBDisk.unk0,gBDisk.unk2);
                                GSthreadSwitch();
                                if((windowGetKeyInfo()[2]&0x10)==0) fn_8009E6B8(windowSearchID(0x109),1);
                                if(gBDisk.unk14!=windowSearchID(0x109)->cursor) {
                                    windowCreateCursorSprite(windowSearchID(0x109));
                                    s16 selected=windowSearchID(0x109)->cursor;
                                    windowSearchID(0x109)->prevCursor=selected;
                                    gBDisk.unk14=selected;
                                    menuPlaySe(0x109,1);
                                }
                            } while((windowGetKeyInfo()[2]&0x20)==0);
                            menuPlaySe(0x109,3);
                            menuClose(0xEC);
                            menuCloseSync(0xEC,1);
                            menuOpen(0x109,0);
                        } else if(windowGetKeyInfo()[2]&0x20) browsing=0;
                    }
                    menuClose(0x109);
                    menuCloseSync(0x109,1);
                    break;
                }
                }
            }
        }
        break;
    case 1:
        gBDisk.result=0;
        menuOpen(0xEA,0);
        for (;;) {
            GSthreadSwitch();
            if(windowGetKeyInfo()[2]==0x40) {
                winMsgOpen(2,deckDataVirtualDB_GetExplanetion1(gBDisk.selectedID),1,1);
                do {GSthreadSwitch();} while((windowGetKeyInfo()[2]&0x60)==0);
                winMsgClose(1);
                continue;
            }
            if(windowGetKeyInfo()[2]==0x10) break;
        }
        gBDisk.result=fightEncount(0xE);
        menuOpen(0xEA,0);
        GSthreadSwitch();
        while(gBDisk.currentFrame<gBDisk.endFrame)GSthreadSwitch();
        while((windowGetKeyInfo()[2]&0x30)==0)GSthreadSwitch();
        menuClose(0xEA);
        break;
    case 2: {
        s32 selection=0;
        menuOpenCustom(0xE9,windowGetActiveID(),0,2,0,0);
        gBDisk.field24=menuOpenCustom(0x8F,0,&selection,0,1,0);
        menuCloseCustom(0x8F,0,1);
        menuClose(0xE9);
        menuCloseSync(0xE9,1);
        menuOffScreenSetPriority(1);
        break;
    }
    }
    GSfloorPop();
    if(gBDisk.mode==0 || gBDisk.mode==2) floorSetFadeScript(0,0);
}

void menuBattleDiskInit(void) {
    u16 count;
    s32* item;
    u16 n;
    s32 i;
    item = (s32*)heroItemGetItemKindToItemAryPtr(Hero::getHeroPtr(), 7, &count, 0, 0, 0);
    n = 0;
    fightReadResourceID(0x842, 0x18513400);
    for (i = 0; i < count; i++) {
        if (itemCheckValid(item)) {
            bdiskEntry(n)->itemID = itemBiosGetItemDataId(item);
            bdiskEntry(n)->name = itemDataBiosGetName(itemDataBiosGetPtr(bdiskEntry(n)->itemID));
            bdiskEntry(n)->doc = itemDataBiosGetDoc(itemDataBiosGetPtr(bdiskEntry(n)->itemID));
            bdiskEntry(n)->id = bdiskEntry(n)->itemID - 0x215;
            bdiskEntry(n)->explain1 = deckDataVirtualDB_GetExplanetion1(bdiskEntry(n)->id);
            bdiskEntry(n)->explain2 = deckDataVirtualDB_GetExplanetion2(bdiskEntry(n)->id);
            bdiskEntry(n)->title = deckDataVirtualDB_GetTitle(bdiskEntry(n)->id);
            n++;
        }
        item++;
    }
    gBDisk.count = n;
    {
        s32 j;
        for (j = 0; j < 8; j++) {
            if (j < gBDisk.count) {
                menuItemBiosSetSelectFlag(0xE8, cBattleDisk::mItemCurIdx[j], 1);
            } else {
                menuItemBiosSetSelectFlag(0xE8, cBattleDisk::mItemCurIdx[j], 0);
            }
        }
    }
}

void menuBattleDiskCloseDoc(void) {
    menuClose(0xE9);
}

void menuBattleDiskOpenDoc(u8 id) {
    gBDisk.selectedID = id;
    menuOpenCustom(0xE9, windowGetActiveID(), 0, 2, 0, 0);
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

u16 menuBattleDiskGetResult(void) {
    return gBDisk.result;
}

u8 menuBattleDiskGetSelectID(void) {
    return gBDisk.selectedID;
}

void menuBattleDiskOpenFight(void) {
    if (gBDisk.selectedID != 0) {
        gBDisk.mode = 1;
        GSfloorPush(0x389);
    }
}

void menuBattleDiskOpen(void) {
    gBDisk.mode = 0;
    menuCreateOffScreen(20.0f / GSgfxVideoGetVsyncRate(), 50.0f);
    GSfloorPush(0x389);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    menuReleaseOffScreen(20.0f / GSgfxVideoGetVsyncRate());
}

void spriteSetScissor(s32,s32,s32,s16,s16);
void spriteClearScissor(s32);
void menuPdaSubScrollBar(tagWINDOW_WORK*,tagSPRITE_WORK*,s32,s32,u32,s32,s32,s16*);
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

u16 wazaGetStatus(s32,u16,s32,s32);
u16 zokuseiBiosGetSpriteID(u16);
u16 zokuseiGetPokemonSpriteID(void*,u16);
u8 pokemonDataBiosGetZokuseiDataId(void*,u16);
void windowDrawSprite(s32,s32,tagWINDOW_WORK*,s32,s32,s32);
s32 BattleDiskStatus(tagWINDOW_WORK *win,tagSPRITE_WORK *spr) {
    u16 index=0;
    s32 layer=winSpriteGetLayerID(win,spr);
    Hero *hero=&gBDisk.heroes[0];
    u32 count=heroGetPokeomCount(hero);
    s16 slot=gBDisk.unk14;
    if((u32)slot>=count){hero=&gBDisk.heroes[1];slot-=count;}
    s16 id=spr->id;
    Pokemon *pokemon=hero->getPokemon(slot);
    switch(id) {
    case 0x791:
        msgctrlSetValue(0x37,pokemonGetStatus(pokemon,0,0x77,0));
        GSmsgPrintRect(layer,0,0,spr->x,spr->y,win->alpha|~0xFF,0x4277);break;
    case 0x792:{
        u32 msg;
        switch(menuSubGetPokemonSexForDisp(pokemon)){case 0:msg=0x9C5;break;case 1:msg=0x9C6;break;default:msg=0;break;}
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
        if(type!=pokemonDataBiosGetZokuseiDataId(pokemon->getPokemonDataPtr(),1)){
            u16 sprite=zokuseiGetPokemonSpriteID(pokemon->getPokemonDataPtr(),1);
            windowDrawSprite(0,0,win,sprite,0,winSpriteGetLayerID(win,spr));
        }break;
    }
    case 0x790:index=1;
    case 0x78F:index++;
    case 0x78E:index++;
    case 0x78D:{
        s32 move=pokemonGetStatus(pokemon,0,0x7F,index);
        switch(move){case 0:break;case 0x176:windowDrawSprite(0,0,win,0x7B,0,winSpriteGetLayerID(win,spr));break;
        default:{s32 moveLayer=winSpriteGetLayerID(win,spr);windowDrawSprite(0,0,win,zokuseiBiosGetSpriteID(wazaGetStatus(0,move,3,0)),0,moveLayer);break;}}
        break;
    }
    case 0x797:index=1;
    case 0x796:index++;
    case 0x795:index++;
    case 0x794:{
        u16 move=pokemonGetStatus(pokemon,0,0x7F,index);
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

s32 heroBiosGetNamePtr(Hero*);
u16 FlashSystemGetNowFrame(u32);
u16 FlashSystemGetEndFrame(u32,void*);
s32 BattleDiskBorADraw(tagWINDOW_WORK *win,tagSPRITE_WORK *spr) {
    u16 index=0;
    GSvec2 pos;pos.x=0.0f;pos.y=0.0f;
    switch(spr->id) {
    case 0x738:index=1;
    case 0x737:index++;
    case 0x736:index++;
    case 0x735:index++;
    case 0x734:index++;
    case 0x733:{
        Hero *hero=&gBDisk.heroes[0];
        if(heroGetPokeomCount(hero)>index)dispFace(index,&pos,win,spr,heroBiosGetPokemonPtr(hero,index));break;
    }
    case 0x744:index=1;
    case 0x743:index++;
    case 0x742:index++;
    case 0x741:index++;
    case 0x740:index++;
    case 0x73F:{
        Hero *hero=&gBDisk.heroes[1];
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
        switch(gBDisk.result){case 0:case 1:break;case 2:case 3:spr->value4C=deckDataVirtualDB_GetExplanetion2(gBDisk.selectedID);break;}break;
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
            gBDisk.endFrame=FlashSystemGetEndFrame(0x1F333000,&gBDisk);break;
        case 3:case 4:case 7:
            windowDrawSprite(0,0,win,0x315,0,winSpriteGetLayerID(win,spr));
            gBDisk.currentFrame=FlashSystemGetNowFrame(0x1F343000);
            gBDisk.endFrame=FlashSystemGetEndFrame(0x1F343000,&gBDisk);break;
        default:
            windowDrawSprite(0,0,win,0x316,0,winSpriteGetLayerID(win,spr));
            gBDisk.currentFrame=FlashSystemGetNowFrame(0x1F353000);
            gBDisk.endFrame=FlashSystemGetEndFrame(0x1F353000,&gBDisk);break;
        }
    default:
        switch(gBDisk.result){case 2:case 3:case 4:case 7:winSpriteSetDisp(spr,0);break;default:winSpriteSetDisp(spr,1);break;}break;
    }
    return 0;
}

}
