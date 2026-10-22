#include "game/pxdvs/app/fight/fightMenuPrivate.hpp"


static s32 _fightMenuAllFightTrainerCloseStatusMenuSubCloseCheck(void*, u16, void*);
static s32 _fightMenuAllFightTrainerCloseStatusMenuSub(void*, u16, void*);
static s32 _fightMenuAllFightTrainerOpenStatusMenuSub(void*, u16, void*);
static s32 _fightMenuAllFightOutPokemonCloseStatusMenuSubCloseCheck(void*, u16, void*);
static s32 _fightMenuAllFightOutPokemonCloseStatusMenuSub(void*, u16, void*);
static s32 _fightMenuAllFightOutPokemonOpenStatusMenuSub(void*, u16, void*);
static void _fightMenuFightOutPokemonCloseStatusMenuSub(FightOutPokemon*, u16, bool, bool);
static void _fightMenuFightOutPokemonOpenStatusMenuSub(FightOutPokemon*, u16, bool, bool, bool);
static FightOutPokemon* _fightMenuFightTrainerAgbHeroSelectDefensePokemon(FightOutPokemon*, u16, u16);
static u8 _fightMenuFightTrainerGcHeroOpenMenuSubMain(FIGHT_TRAINER*, FightOutPokemon*, u16, s32);
static u8 _fightMenuFightTrainerGcHeroOpenMenuSubIrekae(FIGHT_TRAINER*, FightOutPokemon*, u16);
static u8 _fightMenuFightTrainerGcHeroOpenMenuSubItem(FIGHT_TRAINER*, FightOutPokemon*, u16);
static FightOutPokemon* _fightMenuFightTrainerGcHeroOpenMenuSubBallSelectTargetPokemon(FightOutPokemon*, u16, u16);
static u8 _fightMenuFightTrainerGcHeroOpenMenuSubWaza(FIGHT_TRAINER*, FightOutPokemon*, u16);
static FightOutPokemon* _fightMenuFightTrainerGcHeroOpenMenuSubWazaSelectDefensePokemon(FightOutPokemon*, u16, u16);
static u8 bCharSkip;
static u8 _fightMenuGcHeroDefenseFlag;

u32 msgCtrlVal[4] = {0, 0, 0, 0};

extern "C" {

s32 fightMenuCloseCustom(u32 id) {
    if (fightFloor_GetStatusMenuCnt(id) == -1) {
        fightFloor_SetStatusMenuCnt(id, 0xf);
    }
    return 0;
}

void fightMenuCloseInfoMenu(u8 wait) {
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    if (fightFloorIsUseFightTimerCommand(0) == 1) {
        menuFightCloseCountDown();
    }
    if (fightFloorIsUseFightTimerAll(0) == 1) {
        menuFightCloseTotalTimer();
    }
    if (wait == 1) {
        fightMenuAllFightTrainerCloseStatusMenu(1);
        fightMenuAllFightOutPokemonCloseStatusMenu(1);
        if (fightFloorIsUseFightTimerCommand(0) == 1) {
            while (1) {
                if (!menuFightCloseCheckCountDown()) {
                    break;
                }
                GSthreadSwitch();
            }
        }
        if (fightFloorIsUseFightTimerAll(0) == 1) {
            while (1) {
                if (!menuFightCloseCheckTotalTimer()) {
                    break;
                }
                GSthreadSwitch();
            }
        }
    }
}

void fightMenuOpenInfoMenu(s8 flag) {
    fightMenuAllFightTrainerOpenStatusMenu();
    fightMenuAllFightOutPokemonOpenStatusMenu(1);
    if (flag < 0 && fightFloorIsUseFightTimerCommand(0) == 1) {
        menuFightOpenCountDown();
    }
    if (fightFloorIsUseFightTimerAll(0) == 1) {
        menuFightOpenTotalTimer();
    }
}

void fightMenuAllFightTrainerCloseStatusMenu(u8 wait) {
    u8 done;
    fightFloorLoopValidFightTrainer(0, _fightMenuAllFightTrainerCloseStatusMenuSub, 0, 0);
    if (wait == 1) {
        while (1) {
            done = 1;
            fightFloorLoopValidFightTrainer(0, _fightMenuAllFightTrainerCloseStatusMenuSubCloseCheck, &done, 0);
            if (done == 1) {
                break;
            }
            GSthreadSwitch();
        }
    }
}

}

static s32 _fightMenuAllFightTrainerCloseStatusMenuSubCloseCheck(void* trainer, u16 idx, void* out) {
    if (menuIsCheck(fightMenuGetFightTrainerPtrToStatusMenuId((FIGHT_TRAINER*)trainer, idx)) == 1 && out != 0) {
        *(u8*)out = 0;
    }
    return 1;
}

static s32 _fightMenuAllFightTrainerCloseStatusMenuSub(void* trainer, u16 idx, void*) {
    fightMenuFightTrainerCloseStatusMenu((FIGHT_TRAINER*)trainer, idx, 0);
    return 1;
}

extern "C" void fightMenuAllFightTrainerOpenStatusMenu() {
    fightFloorLoopValidFightTrainer(0, _fightMenuAllFightTrainerOpenStatusMenuSub, 0, 0);
}

static s32 _fightMenuAllFightTrainerOpenStatusMenuSub(void* trainer, u16 idx, void*) {
    fightMenuFightTrainerOpenStatusMenu((FIGHT_TRAINER*)trainer, idx);
    return 1;
}

extern "C" void fightMenuAllFightOutPokemonCloseStatusMenu(u8 wait) {
    fightFloorLoopValidFightOutPokemon(0, _fightMenuAllFightOutPokemonCloseStatusMenuSub, 0, 0);
    if (wait == 1) {
        while (1) {
            if (fightFloorLoopValidFightOutPokemon(0, _fightMenuAllFightOutPokemonCloseStatusMenuSubCloseCheck, 0, 0) == 1) {
                break;
            }
            GSthreadSwitch();
        }
    }
}

static s32 _fightMenuAllFightOutPokemonCloseStatusMenuSubCloseCheck(void* poke, u16 idx, void*) {
    if (menuIsCheck(fightMenuGetFightOutPokemonPtrToStatusMenuId((FightOutPokemon*)poke, idx, 0)) == 1) {
        return 0;
    }
    return 1;
}

static s32 _fightMenuAllFightOutPokemonCloseStatusMenuSub(void* poke, u16 idx, void*) {
    _fightMenuFightOutPokemonCloseStatusMenuSub((FightOutPokemon*)poke, idx, 0, 0);
    return 1;
}

extern "C" void fightMenuAllFightOutPokemonOpenStatusMenu(u8 flag) {
    u8 f;
    f = flag;
    fightFloorLoopValidFightOutPokemon(0, _fightMenuAllFightOutPokemonOpenStatusMenuSub, &f, 0);
}

static s32 _fightMenuAllFightOutPokemonOpenStatusMenuSub(void* poke, u16 idx, void* arg) {
    FightOutPokemon* p = (FightOutPokemon*)poke;
    bool v;
    if (arg == 0) {
        v = 1;
    } else {
        v = *(bool*)arg;
    }
    if (fightOutPokemonCheckFightOut(p) == 0) {
        return 1;
    }
    _fightMenuFightOutPokemonOpenStatusMenuSub(p, idx, v, 0, 0);
    return 1;
}

struct FightMenuLvupStatus {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xa;
    s16 xc;
};

extern "C" {

void fightMenuOpenLevelUpStatusMenu(s8* p, s8 v) {
    if (p != 0) {
        *p = v;
        winMsgOpenLevelUpStatus(p, 1);
    }
}

void fightMenuSubMenuLvupStatus(FightMenuLvupStatus* a, FightMenuLvupStatus* b, FightMenuLvupStatus* c) {
    if (a != 0 && b != 0 && c != 0) {
        c->x2 = a->x2 - b->x2;
        c->x4 = a->x4 - b->x4;
        c->x6 = a->x6 - b->x6;
        c->xa = a->xa - b->xa;
        c->xc = a->xc - b->xc;
        c->x8 = a->x8 - b->x8;
    }
}

s32 fightMenuWazaWasure(s32 a, s32 b) {
    s32 r;
    fadeSet(3, 0.5f);
    fadeCheck(1);
    r = menuPokemonStatusOpenWazaLearn(a, b);
    if (r == 4) {
        r = -1;
    }
    fadeSet(2, 0.5f);
    fadeCheck(1);
    return r;
}

void fightMenuCloseLevelUpStatusMenu() {
    winMsgCloseLevelUpStatus(1);
}

u8 fightMenuYesNo() {
    return menuSubOpenYesNoField() == 0;
}

void fightMenuWazaKoukaMsg(u32 msg, u32 val, u16 item) {
    fightMsgctrlSetValue(0x10, val);
    char* nm = GSmsgGetGSchar(itemGetStatus(0, item, 1, 0));
    fightMsgctrlSetValue(0x29, (u32)nm);
    fightMenuOpenMsg(msg);
}

void fightMenuWazaOutMsg(u32 val, u16 waza) {
    fightMsgctrlSetValue(0xf, val);
    char* nm = GSmsgGetGSchar(wazaGetStatus(0, waza, 0xa, 0));
    fightMsgctrlSetValue(0xd, (u32)nm);
    fightMsgctrlSetValue(0x28, (u32)GSmsgGetGSchar(wazaGetStatus(0, waza, 1, 0)));
    fightMsgctrlSetValue(0xe, (u32)GSmsgGetGSchar(wazaGetStatus(0, waza, 0xb, 0)));
    fightMenuOpenMsg(0x4f6d);
}

void fightMsgctrlSetValue(s32 id, u32 v) {
    if (ServerWork[7] == 2) {
        switch (id) {
        case 0xf:
            msgCtrlVal[0] = v;
            break;
        case 0xd:
            msgCtrlVal[1] = v;
            break;
        case 0x28:
            msgCtrlVal[2] = v;
            break;
        case 0xe:
            msgCtrlVal[3] = v;
            break;
        default:
            msgctrlSetValue(id, v);
            break;
        }
    } else {
        msgctrlSetValue(id, v);
    }
}

void fightMenuCloseMsg() {
    winMsgCloseFight(0);
}

s32 fightMenuOpenTrainerMsg(u32 msg) {
    if (msg != 0 && dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        winMsgOpenFightNoWait(msg, 1, 1);
        return 1;
    }
    return 0;
}

s32 fightMenuOpenMsg2(u32 msg, s32 arg) {
    if (msg != 0 && dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        winMsgOpenFight2(msg, 1, 1, arg);
        return 1;
    }
    return 0;
}

s32 fightMenuOpenMsg(u32 msg) {
    if (ServerWork[7] == 2) {
        fightMainWaitFrame(msgFrame);
        ServerWork[7] = 0;
        fightMenuCloseMsg();
    }
    if (msgCtrlVal[0] != 0) {
        msgctrlSetValue(0xf, msgCtrlVal[0]);
        msgCtrlVal[0] = 0;
    }
    if (msgCtrlVal[1] != 0) {
        msgctrlSetValue(0xd, msgCtrlVal[1]);
        msgCtrlVal[1] = 0;
    }
    if (msgCtrlVal[2] != 0) {
        msgctrlSetValue(0x28, msgCtrlVal[2]);
        msgCtrlVal[2] = 0;
    }
    if (msgCtrlVal[3] != 0) {
        msgctrlSetValue(0xe, msgCtrlVal[3]);
        msgCtrlVal[3] = 0;
    }
    if (msg != 0 && dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        winMsgOpenFight(msg, 1, 1);
        return 1;
    }
    return 0;
}

}

extern "C" s32 fightMenuFightTrainerAgbHeroOpenMenu(FIGHT_TRAINER* t, u16 type) {
    void* status;
    u16 cnt;
    u32 n;
    u16 last;
    u16 i;
    FightOutPokemon* poke;
    s32 gba;
    s32 act;
    s8 wi;
    u16 waza;
    FightOutPokemon* target;
    FightOutPokemon* sel;
    u16 tgt;
    u16 counter;
    u8 found;
    u16 s;
    void* side;
    u16 tr;
    void* ft;
    u16 k;
    s16 v;
    status = fightTrainerGetStatus(t, 0, 0x4b, 0);
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        menuOpenCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, type), 0, 0, 0, 0, 0);
    }
    cnt = fightFloorGetStatus(0, 0, 0x16, 0);
    n = fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(type));
    last = 0;
    for (i = 0; i < n; i++) {
    refetch:
        poke = fightTrainerGetValidFightOutPokemonPtr(t, i);
        if (poke == 0) {
            last = i;
            continue;
        }
        if (!fightOutPokemonCheckFightActionSelect(poke, 1)) {
            last = i;
            continue;
        }
    retry:
        fightOutPokemonInitFightActionBuff(poke);
        if (fightGetFightResultId() == 1) {
            goto abort;
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
            goto timeout;
        }
        gba = menuFightOpenGBAMain((u32)status, t, i, type);
        act = gbaCommandGetAction(gba);
        if (fightGetFightResultId() == 1) {
            goto abort;
        }
        if (act == 3) {
            fightOutPokemonCreateFightAction(poke, 0, 8, 0, fight_action_data_turn, 0);
            break;
        } else if (act == 1) {
            if (fightOutPokemonCheckFightActionWazaSelect(poke, 1)) {
                last = i;
                continue;
            }
            wi = gbaCommandGetWazaDataId(gba);
            if (wi < 0) {
                goto retry;
            }
            waza = pokemonGetStatus(fightOutPokemonGetPokemonPtr(poke), 0, 0x7f, wi);
            if (waza == 0) {
                goto retry;
            }
            if (waza >= *waza_data_number) {
                goto retry;
            }
            if (waza == 0x176) {
                goto retry;
            }
            target = 0;
            sel = fightSeqSelectDefensePokemonPtr(poke, waza, type, _fightMenuFightTrainerAgbHeroSelectDefensePokemon, 1, 0, -1);
            if (sel != 0) {
                target = sel;
            } else {
                tgt = gbaCommandGetWazaTarget(gba);
                counter = 0;
                found = 0;
                for (s = 0; s < 2; s++) {
                    side = fightFloorGetValidFightSidePtr(0, s);
                    if (side == 0) {
                        continue;
                    }
                    for (tr = 0; tr < cnt; tr++) {
                        ft = fightSideGetValidFightTrainerPtr(side, tr);
                        if (ft == 0) {
                            continue;
                        }
                        for (k = 0; k < n; k++) {
                            target = (FightOutPokemon*)fightTrainerGetStatus((FIGHT_TRAINER*)ft, 0, 0x46, k);
                            if (counter == tgt) {
                                found = 1;
                                break;
                            }
                            counter++;
                        }
                        if (found == 1) {
                            break;
                        }
                    }
                    if (found == 1) {
                        break;
                    }
                }
            }
            if (target == 0) {
                goto retry;
            }
            fightOutPokemonCreateFightActionAttackWaza(poke, 0, 0x13, 0, fight_action_data_waza, waza,
                fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, type), wi, 0);
            last = i;
        } else if (act == 2) {
            v = pokemonGetStatus(fightTrainerGetStatus(t, 0, 0x45, gbaCommandGetGBAChangePokemon(gba)), 0, 0xce, 0);
            if (v < 0) {
                goto retry;
            }
            fightOutPokemonCreateFightAction(poke, 0, 9, 0, fight_action_data_turn, v);
            last = i;
        } else if (act == 4) {
            goto timeout;
        } else if (act == 5) {
        abort:
            fightTrainerAllInitFightActionBuff(t);
            if (fightFloorIsNowEncountTuusinTaisen(0)) {
                if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, type))) {
                    menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, type), 0, 1);
                }
            }
            return 0;
        } else if (act == 0) {
            if (i != 0) {
                i = last;
            }
            goto refetch;
        } else {
        timeout:
            fightTrainerTimeOutSelectFightAction(t, poke, type);
            last = i;
        }
    }
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, type))) {
            menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, type), 0, 1);
        }
    }
    return 1;
}

static FightOutPokemon* _fightMenuFightTrainerAgbHeroSelectDefensePokemon(FightOutPokemon*, u16, u16) {
    return 0;
}

static u8 _fightMenuFightTrainerGcHeroOpenMenuSubMain(FIGHT_TRAINER* t, FightOutPokemon* p, u16 idx, s32 sel) {
    u8 ret;
    u8 r;
    ret = 0;
    switch (sel) {
    case 0:
        r = fightOutPokemonCheckFightActionWazaSelect(p, 1);
        if (r == 1) {
            fightMsgctrlSetValue(0x11, (u32)p);
            fightMenuOpenMsg(0x4ee5);
            fightMainWaitFrame(0x40);
            fightMenuCloseMsg();
        }
        if (r == 0) {
            if (_fightMenuFightTrainerGcHeroOpenMenuSubWaza(t, p, idx) == 0) {
                ret = 2;
                if (fightKind_CheckFightKind(0xa) != 0 || fightKind_CheckFightKind(0x11) != 0) {
                    ret = 1;
                }
            }
        }
        break;
    case 1:
        if (fightFloorGetStatus(0, 0, 0x20, 0) == 0) {
            fightMenuOpenMsg(0x4ede);
            fightMainWaitFrame(0x40);
            fightMenuCloseMsg();
            ret = 2;
        } else if (_fightMenuFightTrainerGcHeroOpenMenuSubItem(t, p, idx) == 0) {
            ret = 2;
        }
        break;
    case 2:
        if (_fightMenuFightTrainerGcHeroOpenMenuSubIrekae(t, p, idx) == 0) {
            ret = 2;
        }
        break;
    case 3:
        if ((u8)(fightFloorGetStatus(0, 0, 0x22, 0) != 0) == 1) {
            fightOutPokemonCreateFightAction(p, 0, 8, 0, fight_action_data_turn, 0);
        } else if ((u8)(fightFloorGetStatus(0, 0, 0x21, 0) != 0) == 1) {
            fightOutPokemonCreateFightAction(p, 0, 0xa, 0, fight_action_data_turn, 0);
        } else {
            ret = 2;
        }
        break;
    default:
        ret = 1;
        break;
    }
    return ret;
}

static u8 _fightMenuFightTrainerGcHeroOpenMenuSubIrekae(FIGHT_TRAINER* t, FightOutPokemon* p, u16 idx) {
    s16 r = fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(t, p, idx, 1, 1);
    if (r < 0) {
        return 0;
    }
    fightOutPokemonCreateFightAction(p, 0, 9, 0, fight_action_data_turn, r);
    return 1;
}

extern "C" s16 fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(FIGHT_TRAINER* t, FightOutPokemon* p, u16 idx, u8 a, u8 b) {
    s32 sel;
    void* pk;
    for (;;) {
        if (fightGetFightResultId() == 1) {
        retm2:
            return -2;
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
            goto timeout;
        }
        if (fightFloorIsNowEncountTuusinTaisen(0) && b == 0) {
            menuOpenCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, idx), 0, 0, 0, 0, 0);
        }
        if (!fightFloorIsNowEncountTuusinTaisen(0)) {
            menuFightSetSeqOut__Fv();
            fightMenuCloseInfoMenu(1);
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1) {
            menuFightOpenCountDown();
        }
        if (fightFloorIsUseFightTimerAll(0) == 1) {
            menuFightOpenTotalTimer();
        }
        sel = menuFightOpenPokemon(t, p, idx, a, fightFloorIsNowEncountTuusinTaisen(0));
        fightMainWaitFrameEffect(10);
        if (!fightFloorIsNowEncountTuusinTaisen(0) && b == 1) {
            fightMenuOpenInfoMenu(-1);
            if (p != 0) {
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(p, idx, 1);
            }
        }
        if (fightFloorIsNowEncountTuusinTaisen(0) && b == 0) {
            if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, idx))) {
                menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, idx), 0, 1);
            }
        }
        if (fightGetFightResultId() == 1) {
            goto retm2;
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1 && sel < 0) {
        timeout:
            if (b == 0) {
                return fightTrainerTimeOutSelectIrekaeFightPokemon(t, p, idx);
            }
            goto neg;
        }
        if (sel < 0) {
        neg:
            if (a != 0) {
                return -1;
            }
            continue;
        }
        pk = fightTrainerGetStatus(t, 0, 0x45, (u16)sel);
        if (!fightPokemonCheckValid(pk)) {
            continue;
        }
        if ((u8)(pokemonGetStatus(pk, 0, 0xd2, 0) != 0) == 1) {
            continue;
        }
        return pokemonGetStatus(pk, 0, 0xce, 0);
    }
}

extern "C" s16 fightMenuFightTrainerAgbHeroSelectIrekaeFightPokemon(FIGHT_TRAINER* t, u16 type, s32 arg2, FightOutPokemon* poke) {
    void* status;
    u32 n;
    u16 i;
    s32 act;
    s16 ret;
    status = fightTrainerGetStatus(t, 0, 0x4b, 0);
    n = fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(type));
    for (i = 0; i < n; i++) {
        if (fightTrainerGetStatus(t, 0, 0x46, i) == poke) {
            break;
        }
    }
    if (i >= n) {
        return fightTrainerAiSelectIrekaeDasuFightPokemon(t, type, arg2, (u32)poke);
    }
    if (fightGetFightResultId() == 1) {
        goto retm2;
    }
    if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
        goto timeout;
    }
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        menuOpenCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, type), 0, 0, 0, 0, 0);
    }
    if (fightFloorIsUseFightTimerCommand(0) == 1) {
        menuFightOpenCountDown();
    }
    if (fightFloorIsUseFightTimerAll(0) == 1) {
        menuFightOpenTotalTimer();
    }
    status = (void*)menuFightOpenGBAIrekae((u32)status, t, i, type);
    act = gbaCommandGetAction((s32)status);
    if (fightGetFightResultId() == 1) {
        goto retm2;
    }
    if (act == 2) {
        ret = pokemonGetStatus(fightTrainerGetStatus(t, 0, 0x45, gbaCommandGetGBAChangePokemon((s32)status)), 0, 0xce, 0);
    } else if (act == 4) {
        goto timeout;
    } else if (act == 5) {
    retm2:
        ret = -2;
    } else {
    timeout:
        ret = fightTrainerTimeOutSelectIrekaeFightPokemon(t, poke, type);
    }
    if (fightFloorIsNowEncountTuusinTaisen(0)) {
        if (menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, type))) {
            menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(t, type), 0, 1);
        }
    }
    return ret;
}

// @@MID2@@

struct FightMenuPokeStBuf {
    u8 pad00[0x29];
    u8 f29;
    u8 pad2a[3];
    u8 f2d;
    u8 pad2e[2];
};

struct FightMenuBallStBuf {
    u16 a[3];
};

extern "C" {

void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(u32 cur, FightOutPokemon* poke, u16 idx, s32 arg3, bool arg4) {
    u8 ids[4] = {0x37, 0x38, 0x40, 0x41};
    s32 id;
    u32 t;
    u8 i;
    if (cur != 0) {
        id = cur;
    } else {
        id = fightMenuGetFightOutPokemonPtrToStatusMenuId(poke, idx, arg4);
    }
    for (i = 0; i < 4; i++) {
        t = ids[i];
        if (id != (s32)t && menuIsCheck(t)) {
            if (fightFloor_GetStatusMenuCnt(t) == -1) {
                fightFloor_SetStatusMenuCnt(t, 0xf);
            }
            menuCloseCustom(t, 2, arg3);
        }
    }
}

void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon* poke, u16 idx, bool x) {
    _fightMenuFightOutPokemonCloseStatusMenuSub(poke, idx, x, 1);
}

}

static void _fightMenuFightOutPokemonCloseStatusMenuSub(FightOutPokemon* poke, u16 idx, bool, bool b) {
    u32 id = fightMenuGetFightOutPokemonPtrToStatusMenuId(poke, idx, b);
    if (menuIsCheck(id)) {
        if (fightFloor_GetStatusMenuCnt(id) == -1) {
            fightFloor_SetStatusMenuCnt(id, 0xf);
        }
    }
}

extern "C" {

void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon* poke, u16 idx, bool x) {
    u32 id = fightMenuGetFightOutPokemonPtrToStatusMenuId(poke, idx, 1);
    if (menuIsCheck(id)) {
        fightMenuFightOutPokemonOpenStatusMenu(poke, idx, x);
        fightFloor_SetStatusMenuCnt(id, -1);
    }
}

void fightMenuFightStatusStartAnimHP(s32 a, s32 b) {
    if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        menuFightStatusStartAnimHP(a, b);
    }
}

void fightMenuFightOutPokemonOpenStatusMenuStart(FightOutPokemon* poke, u16 idx, bool x) {
    _fightMenuFightOutPokemonOpenStatusMenuSub(poke, idx, x, 1, 1);
}

void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon* poke, u16 idx, bool x) {
    _fightMenuFightOutPokemonOpenStatusMenuSub(poke, idx, x, 1, 0);
}

}

static void _fightMenuFightOutPokemonOpenStatusMenuSub(FightOutPokemon* poke, u16 idx, bool a, bool b, bool c) {
    FightMenuPokeStBuf buf;
    u32 id = fightMenuGetFightOutPokemonPtrToStatusMenuId(poke, idx, b);
    fightOutPokemonToMenuPokemonStatus(poke, &buf);
    if (!a) {
        buf.f29 = 0;
    }
    if (c) {
        buf.f2d = 1;
    } else {
        buf.f2d = 0;
    }
    if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 1) {
        menuOpenCustom(id, -1, 0, 0, 0, 1, buf);
        fightFloor_SetStatusMenuCnt(id, -1);
    }
}

extern "C" {

void fightMenuFightOutPokemonSetStatusMenuActiveFlag(FightOutPokemon* poke, u16 idx, u32 flag) {
    if (fightFloorIsNowEncountTuusinTaisen(0) != 1) {
        menuFightStatusSetActive(fightMenuGetFightOutPokemonPtrToStatusMenuId(poke, idx, 1), flag);
    }
}

u32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon* poke, u16 idx, bool) {
    u16 side;
    u16 rel;
    s32 buf;
    void* p = fightTargetGetPtr(2, poke, idx);
    if (p == 0) {
        return 0;
    }
    side = fightSideGetStatus(p, 0, 5, 0);
    rel = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(poke, idx);
    if (rel == 0) {
        return 0;
    }
    buf = fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(rel));
    if (buf < 0) {
        return 0;
    }
    return fightSideGetStatus(0, side, 3, buf);
}

void fightMenuFightTrainerCloseStatusMenu(FIGHT_TRAINER* t, u16 idx, u32 x) {
    u32 id = fightMenuGetFightTrainerPtrToStatusMenuId(t, idx);
    if (menuIsCheck(id)) {
        menuCloseCustom(id, 0, x);
    }
}

void fightMenuFightTrainerRenewStatusMenu(FIGHT_TRAINER* t, u16 idx) {
    if (menuIsCheck(fightMenuGetFightTrainerPtrToStatusMenuId(t, idx))) {
        fightMenuFightTrainerOpenStatusMenu(t, idx);
    }
}

void fightMenuFightTrainerOpenStatusMenu(FIGHT_TRAINER* t, u16 idx) {
    FightMenuBallStBuf buf;
    u32 id = fightMenuGetFightTrainerPtrToStatusMenuId(t, idx);
    fightTrainerToMenuBallStatus(t, &buf);
    if (dbgMenuFightGetFightPokeStMenuOpenFlag() == 1 && menuFightChkOpenBall(id)) {
        menuOpenCustom(id, 0, 0, 0, 0, 1, buf);
    }
}

u32 fightMenuGetFightTrainerPtrToStatusMenuId(FIGHT_TRAINER* t, u16 idx) {
    u16 side;
    u16 rel;
    s32 buf;
    void* p = fightTargetGetPtr(2, (FightOutPokemon*)t, idx);
    if (p == 0) {
        return 0;
    }
    side = fightSideGetStatus(p, 0, 5, 0);
    rel = fightTargetGetTragetPtrToRelativeHostSideFightTargetId((FightOutPokemon*)t, idx);
    if (rel == 0) {
        return 0;
    }
    buf = fightTargetDataBiosGetBuff(fightTargetDataBiosGetPtr(rel));
    if (buf < 0) {
        return 0;
    }
    return fightSideGetStatus(0, side, 2, buf);
}

u32 fightMenuGetFightTrainerPtrToKeyWaitMenuId(FIGHT_TRAINER* t, u16 idx) {
    return menuFightGetKeyWaitMenuId(t, idx);
}

}

struct FightMenuTargetSlot { s32 reserved; u32 menu; s32 nickname; };
struct FightMenuTargetData {
    FightMenuTargetSlot targets[4];
    u8 count, online, reserved32[2];
    FightOutPokemon *attacker;
};

static FightOutPokemon* _fightMenuFightTrainerGcHeroOpenMenuSubBallSelectTargetPokemon(FightOutPokemon* attacker,u16,u16 type) {
    FightMenuTargetData data;
    for(;;) {
        FightOutPokemon* target=fightTargetGetPtr(15,attacker,type);
        data.targets[0].menu=fightOutPokemonCheckFightOut(target)==1?fightMenuGetFightOutPokemonPtrToStatusMenuId(target,type,false):0;
        data.targets[0].nickname=fightOutPokemonGetNicknamePtr(target);
        target=fightTargetGetPtr(16,attacker,type);
        data.targets[1].menu=fightOutPokemonCheckFightOut(target)==1?fightMenuGetFightOutPokemonPtrToStatusMenuId(target,type,false):0;
        data.targets[1].nickname=fightOutPokemonGetNicknamePtr(target);
        data.targets[2].menu=0;data.targets[3].menu=0;data.count=2;
        data.online=fightFloorIsNowEncountTuusinTaisen(0);data.attacker=attacker;
        s32 selected=menuFightOpenTarget(&data,0,1);
        if(selected<0){menuFightCloseTarget(1);return 0;}
        if(selected==0)target=fightTargetGetPtr(15,attacker,type);
        else if(selected==1)target=fightTargetGetPtr(16,attacker,type);
        else continue;
        if(fightOutPokemonCheckFightOut(target)!=0){
            if(pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(target))==0&&fightFloor_GetFightKind(0)!=12&&fightFloor_GetFightKind(0)!=13){fightMenuOpenMsg(0x5001);fightMenuCloseMsg();continue;}
            menuFightCloseTarget(1);return target;
        }
    }
}

static FightOutPokemon* _fightMenuFightTrainerGcHeroOpenMenuSubWazaSelectDefensePokemon(FightOutPokemon* attacker,u16,u16 type) {
    FightMenuTargetData data;
    for(;;) {
        FightOutPokemon* target=fightTargetGetPtr(15,attacker,type);
        data.targets[0].menu=fightOutPokemonCheckFightOut(target)==1?fightMenuGetFightOutPokemonPtrToStatusMenuId(target,type,false):0;
        data.targets[0].nickname=fightOutPokemonGetNicknamePtr(target);
        target=fightTargetGetPtr(16,attacker,type);
        data.targets[1].menu=fightOutPokemonCheckFightOut(target)==1?fightMenuGetFightOutPokemonPtrToStatusMenuId(target,type,false):0;
        data.targets[1].nickname=fightOutPokemonGetNicknamePtr(target);
        target=fightTargetGetPtr(14,attacker,type);
        data.targets[2].menu=fightOutPokemonCheckFightOut(target)==1?fightMenuGetFightOutPokemonPtrToStatusMenuId(target,type,false):0;
        data.targets[2].nickname=fightOutPokemonGetNicknamePtr(target);
        data.targets[3].menu=0;data.count=3;
        data.online=fightFloorIsNowEncountTuusinTaisen(0);data.attacker=attacker;
        s32 selected=menuFightOpenTarget(&data,0,1);
        _fightMenuGcHeroDefenseFlag=1;
        if(selected<0){menuFightCloseTarget(1);return 0;}
        if(selected==0)target=fightTargetGetPtr(15,attacker,type);
        else if(selected==1)target=fightTargetGetPtr(16,attacker,type);
        else if(selected==2)target=fightTargetGetPtr(14,attacker,type);
        else continue;
        if(fightOutPokemonCheckFightOut(target)!=0){menuFightCloseTarget(1);return target;}
    }
}

static u8 _fightMenuFightTrainerGcHeroOpenMenuSubWaza(FIGHT_TRAINER* trainer,FightOutPokemon* attacker,u16 type) {
    u8 status[0x48];
    u16 invalidMove;
    s32 selected;
    Pokemon *pokemon;
    u32 message;
    u32 outCount;
    u8 invalid;
    u16 failMove;
    u16 move;
    FightOutPokemon *target;
    s32 relative;
    s32 wazaStatus;
    outCount=(u8)fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(type));
    for(;;){
        fightOutPokemonToMenuWazaStatus(attacker,status);
        status[0x44]=fightFloorIsNowEncountTuusinTaisen(0);
        pokemon=fightOutPokemonGetPokemonPtr(attacker);
        wazaStatus=pokemonGetStatus(attacker,0,0x101,0);selected=menuFightOpenWaza(trainer,status,wazaStatus,1);
        if(selected<0){menuFightCloseWaza(1);return 0;}
        if(selected>4){
            if((u8)(fightFloorGetStatus(0,0,0x22,0)!=0)==1){
                fightOutPokemonCreateFightAction(attacker,0,8,0,fight_action_data_turn,0);bCharSkip=1;
                if(fightGetFightResultId()==0){if(fightTargetIsHostSide(attacker,type)==1)fightSetFightResultId(4);else fightSetFightResultId(5);}
            }
            return 0;
        }
        invalid=fightOutPokemonCheckCanOutOkWazaBanme(attacker,selected,1,&invalidMove);
        failMove=pokemonGetStatus(pokemon,0,0x7F,selected);
        if(invalid!=0){
            fightMsgctrlSetValue(0x11,(u32)attacker);
            fightMsgctrlSetValue(0x28,(u32)GSmsgGetGSchar(wazaGetStatus(0,failMove,1,0)));
            {u16 item=fightOutPokemonGetSoubiItemDataId(attacker);fightFloorSetStatus(0,0,0x56,0,item);}
        }
        if(invalid==6)message=0x4F42;
        else if(invalid==5){fightMsgctrlSetValue(0x28,(u32)GSmsgGetGSchar(wazaGetStatus(0,invalidMove,1,0)));message=0x4F9A;}
        else if(invalid==4)message=0x4EE9;
        else if(invalid==3)message=0x4EE8;
        else if(invalid==2)message=0x4EE7;
        else if(invalid==1)message=0x4EE6;
        if(invalid!=0){fightMenuOpenMsg(message);fightMainWaitFrame(0x40);fightMenuCloseMsg();continue;}
        move=pokemonGetStatus(pokemon,0,0x7F,(u16)selected);
        if(move!=0&&move<*waza_data_number&&move!=0x176){
            _fightMenuGcHeroDefenseFlag=0;
            target=fightSeqSelectDefensePokemonPtr(attacker,move,type,_fightMenuFightTrainerGcHeroOpenMenuSubWazaSelectDefensePokemon,1,0,-1);
            if((fightFloorIsNowEncountTuusinTaisen(0)!=1&&fightKind_CheckFightKind(10)==0&&fightKind_CheckFightKind(17)==0)||_fightMenuGcHeroDefenseFlag!=0||(outCount<2&&fightTypeDataBiosGetTrainerNum(fightTypeDataBiosGetPtr(type))!=2)||_fightMenuFightTrainerGcHeroOpenMenuSubWazaSelectDefensePokemon(attacker,move,type)!=0){
                if(target){
                    relative=((u32(*)(FightOutPokemon*,u16))fightTargetGetTragetPtrToRelativeHostSideFightTargetId)(target,type);
                    menuFightCloseWaza(1);
                    fightOutPokemonCreateFightActionAttackWaza(attacker,0,0x13,0,fight_action_data_waza,move,relative,(s8)selected,0);
                    return 1;
                }
            }
        }
    }
}

extern "C" s32 fightMenuFightTrainerGcHeroOpenMenu(FIGHT_TRAINER* trainer,u16 type,u8 canCancel) {
    u8 data[0x18];
    s32 selection;
    s32 choice;
    u8 result;
    FightOutPokemon *pokemon;
    u16 current,previous,i;
    u32 count=(u8)fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(type));
    if(fightFloorIsNowEncountTuusinTaisen(0)!=0)menuOpenCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer,type),0,0,0,0,0);
    current=0;previous=0;selection=current;bCharSkip=current;
    while(current<count){
nextPokemon:
    pokemon=fightTrainerGetValidFightOutPokemonPtr(trainer,current);
    if(pokemon==0){previous=current;goto advance;}
    if(fightOutPokemonCheckFightActionSelect(pokemon,1)==0){previous=current;goto advance;}
    if(fightGetFightResultId()==1){
clearActions:
        fightTrainerAllInitFightActionBuff(trainer);
        goto finish;
    }
    if(fightFloorIsUseFightTimerCommand(0)==1&&fightTimerCommandIsOver()==1){
timeout:
        fightOutPokemonInitFightActionBuff(pokemon);
        fightTrainerTimeOutSelectFightAction(trainer,pokemon,type);
        previous=current;
        goto advance;
    }
    fightMenuFightOutPokemonSetStatusMenuActiveFlag(pokemon,type,1);
    selection=0;
openTop:
    fightOutPokemonInitFightActionBuff(pokemon);
    fightFloorSetMenuFightAction(0,pokemon,data);
    data[0x17]=fightFloorIsNowEncountTuusinTaisen(0);
    choice=menuFightOpenTop(trainer,data,&selection,1);
    if(fightGetFightResultId()==1){fightMenuFightOutPokemonSetStatusMenuActiveFlag(pokemon,type,0);menuFightCloseTop(1);goto clearActions;}
    if(fightFloorIsUseFightTimerCommand(0)==1&&fightTimerCommandIsOver()==1&&choice<0){fightMenuFightOutPokemonSetStatusMenuActiveFlag(pokemon,type,0);menuFightCloseTop(1);goto timeout;}
    if(choice>=0)menuFightCloseTop(1);
    result=_fightMenuFightTrainerGcHeroOpenMenuSubMain(trainer,pokemon,type,choice);
    if(fightGetFightResultId()==1){fightMenuFightOutPokemonSetStatusMenuActiveFlag(pokemon,type,0);menuFightCloseTop(1);goto clearActions;}
    if(fightFloorIsUseFightTimerCommand(0)==1&&fightTimerCommandIsOver()==1&&result!=0){fightMenuFightOutPokemonSetStatusMenuActiveFlag(pokemon,type,0);menuFightCloseTop(1);goto timeout;}
    if(result==1){
        if(bCharSkip!=0){bCharSkip=0;goto finish;}
        if(fightTrainerIsUsedItem(trainer)!=1){
            if(current!=0){current=previous;fightMenuFightOutPokemonSetStatusMenuActiveFlag(pokemon,type,0);menuFightCloseTop(1);goto nextPokemon;}
            if(canCancel==1&&current==0){
                fightMenuFightOutPokemonSetStatusMenuActiveFlag(pokemon,type,0);menuFightCloseTop(1);
                for(i=0;i<count;i++){
                    pokemon=fightTrainerGetValidFightOutPokemonPtr(trainer,i);
                    if(pokemon)pokemonSetStatus((Pokemon*)pokemon,0,0x120,0,0);
                }
                return 0;
            }
        }
        goto openTop;
    }
    if(result==2)goto openTop;
    fightMenuFightOutPokemonSetStatusMenuActiveFlag(pokemon,type,0);
    previous=current;
    if(choice==3&&fightFloor_GetFightKindNigeruFlag(0)!=0)goto finish;
advance:
    current++;
    }
finish:
    if(fightFloorIsNowEncountTuusinTaisen(0)!=0){
        if(menuIsCheck(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer,type))!=0)menuCloseCustom(fightMenuGetFightTrainerPtrToKeyWaitMenuId(trainer,type),0,1);
    }
    for(i=0;i<count;i++){
        pokemon=fightTrainerGetValidFightOutPokemonPtr(trainer,i);
        if(pokemon)pokemonSetStatus((Pokemon*)pokemon,0,0x120,0,0);
    }
    return 1;
}

static u8 _fightMenuFightTrainerGcHeroOpenMenuSubItem(FIGHT_TRAINER* trainer,FightOutPokemon* attacker,u16 type) {
    u16 item;
    s32 selected=0;
    s32 lastSlot=-1;
    u8 wasOut[2],wasState8[2],wasState7[2];
    u16 i;
    FightOutPokemon *pokemonC;
    FightOutPokemon *pokemonD;
    FightOutPokemon *pokemonB;
    FightOutPokemon *pokemonA;
    for(i=0;i<2;i++){wasOut[i]=0;wasState8[i]=0;wasState7[i]=0;}
    for(i=0;i<2;i++){
        pokemonA=(FightOutPokemon*)fightTrainerGetStatus(trainer,0,0x46,i);
        if(pokemonA){
            u16 slot=fightTrainerGetFightOutPokemonToTemotiBanme(trainer,pokemonA);
            FightPokemon* party=(FightPokemon*)fightTrainerGetStatus(trainer,0,0x45,(u16)slot);
            wasOut[i]=fightPokemonCheckFightOut(party);
            wasState8[i]=fightOutPokemonIsJoutaiDataId(pokemonA,8);
            wasState7[i]=fightOutPokemonIsJoutaiDataId(pokemonA,7);
        }
    }
    if(fightTrainerGetStatus(trainer,0,0x44,0)==0)return 0;
    s32 party=pokemonGetStatus(attacker,0,0xD5,0);
    selected=fightTrainerGetFightPokemonToTemotiBanme(trainer,party);
    for(;;){
        if(fightKind_CheckFightKind(13)!=0){if(getStaticBall__10bingo_biosFv()!=0){item=1;decStaticBall__10bingo_biosFv();}}
        else{
            menuFightSetSeqOut__Fv();fightMenuCloseInfoMenu(1);
            u32 rate=GSgfxVideoGetVsyncRate();
            menuCreateOffScreen(rate,8.0f/(f32)rate,50.0f);
            menuOffScreenFadeSync(1);
            item=fightFloorIsNowEncountSnatchOnly(0)!=0?menuPocket2Open(6,&selected,trainer):menuPocket2Open(1,&selected,trainer);
            fightMainWaitFrameEffect(10);{u8 slot=menuPocket2GetLastSlotID();lastSlot=slot;}
        }
        if(item!=0&&(u8)itemGetStatus(0,item,2,0)==2){
            for(i=0;i<2;i++){
                pokemonB=(FightOutPokemon*)fightTrainerGetStatus(trainer,0,0x46,i);
                if(pokemonB){
                    void* sequence=(void*)pokemonGetStatus(pokemonB,0,0xEE,0);
                    if(sequence){
                        if(wasState8[i]==1&&fightOutPokemonIsJoutaiDataId(pokemonB,8)==0)Sequence_ResetStatus(sequence,1);
                        if(wasState7[i]==1&&fightOutPokemonIsJoutaiDataId(pokemonB,7)==0)Sequence_ResetStatus(sequence,2);
                    }
                }
            }
        }
        if(fightKind_CheckFightKind(13)==0){fightMenuOpenInfoMenu(-1);if(attacker)fightMenuFightOutPokemonSetStatusMenuActiveFlag(attacker,type,1);}
        menuReleaseOffScreen(8.0f/(f32)GSgfxVideoGetVsyncRate());fightMainWaitFrameEffect(10);
        if(item==0)return 0;
        s32 partyTarget;
        u16 target;
        if((u8)itemGetStatus(0,item,2,0)==1){
            if(fightTrainerIsSelectedItemBall(trainer)==1)continue;
            pokemonC=_fightMenuFightTrainerGcHeroOpenMenuSubBallSelectTargetPokemon(attacker,item,type);
            if(!pokemonC)continue;
            target=fightTargetGetTragetPtrToRelativeHostSideFightTargetId(pokemonC,type);partyTarget=0;
        }else{
            if((u8)itemGetStatus(0,item,2,0)==2){
                for(i=0;i<2;i++){
                    pokemonD=(FightOutPokemon*)fightTrainerGetStatus(trainer,0,0x46,i);
                    if(pokemonD&&wasOut[i]==0&&fightOutPokemonCheckFightOut(pokemonD)==1)pokemonSetStatus((Pokemon*)pokemonD,0,0x120,0,1);
                }
            }
            partyTarget=1;target=selected;
        }
        fightOutPokemonCreateFightActionUseItem(attacker,0,0x12,0,fight_action_data_item,item,target,lastSlot,partyTarget);
        return 1;
    }
}
