#pragma peephole off
#pragma pool_strings off
#include <dolphin/types.h>

struct Hero {
    u8 data[0x978];
};

enum _MENU_GBAC_TYPE {};
enum _GBA_PHASE {};
enum _GBA_WAIT_FLAG {};

struct Quad {
    s32 v[4];
};

struct _GBA_Connect_WORK {
    Quad phase;
    Quad saved;
    u8 pad20;
    s8 channel;
    u8 pad22[2];
    u32 flags;
    u32 state;
    s32 type;
    u8 timeout[4];
    u8 pad34[0x14];
    u8 f48[4];
};

struct GBAInfo {
    u32 pad : 17;
    u32 f14 : 1;
    u32 ver : 4;
    u32 err : 2;
    u32 lang : 4;
    u32 b3 : 1;
    u32 b2 : 1;
    u32 b1 : 1;
    u32 b0 : 1;
};

struct KeyInfo2 {
    u8 pad0[4];
    u16 buttons;
};

struct CBTail {
    u8 pad[0xB168];
    s32 a;
    s32 b;
};

extern "C" {
extern CBTail _CB;
void AGB_Terminate_init(void);
long AGB_Prepare(const char* name);
long AGB_Upload(long ch, long type);
long AGB_GetPokemon(long ch, Hero* hero, u32* out);
long AGB_GetStatus(long ch);
long AGB_IsComplete(long ch);
long AGB_Terminate(long ch);
void AGB_FileBuffAlloc(void);
void AGB_FileBuffFree(void);
bool gbaCommandIsConnected(s32 gba);
void gbaCommandSetKeyState(s32 chan, s32 state);
u32 gba_SIProbe(s32 chan);
void GSthreadSwitch(void);
u8 GSsndPlayNow(u32 id);
u8 GSinputIsConnected(s32 port);
u8 GSgfxVideoGetVsyncRate(void);
f32 GSgfxVideoGetLastRenderTime(void);
s32 pokecoloGetCountryCode(void);
void* savedataBiosGetNowSavedataPtr(void);
void* savedataBiosGetGamedataPtr(void* savedata);
void* gamedataBiosGetGamedataAtttestPtr(void* gamedata);
u8 gamedataAttestBiosGetLangareaId(void* attest);
void* savedataGetStatus(void* save, s32 kind);
void heroInit(Hero* hero);
void heroBiosCopy(Hero* dst, Hero* src);
u8 menuCBRule_CheckHero(Hero* hero);
void menuCBRule_ErrorFlagSet(Hero* hero, u16 id);
void menuCB_Pokemon_ErrorDisp(Hero* hero, u16 id);
u8 menuGetEnablePort(void);
u8 menuSetEnablePort(u8 ports);
bool menuIsCheck(s32 menuID);
s32 menuOpen(s32 menuID, s32);
void menuCloseCustom(s32 menuID, s32, s32);
void menuCB_MessageDispOn(s32 msgID, s32 arg1);
void menuCB_MessageDispOff(void);
s8 menuCB_MessageDispCheck(void);
void menuCB_SE_Play(s32 id);
void winMsgClose(bool flag);
void msgctrlSetValue(s32 id, u32 value);
KeyInfo2* windowGetKeyInfo(void);
void menuGBACSetRomVer(u16 ver, u16 idx);
}

static u8 _menu_ports[4] = {1, 2, 4, 8};
static s8 chans[4] = {1, 2, 3, 0};
static u16 gba_player_number[4] = {1, 2, 3, 0};

static const s32 _initial_phase[4][4] = {
    {8, 1, 0, 0},
    {8, 1, 1, 0},
    {8, 1, 1, 1},
    {1, 1, 1, 1},
};

static s8 _mes_flag_type;
extern "C" {
_GBA_Connect_WORK gbaConectGBA_Connect_WORK;
}

extern "C" {
const char* lbl_8032EBD8[12] = {
    "maxbtl.bin",
    "maxcng.bin",
    "maxbtl_english.bin",
    "maxcng_english.bin",
    "maxbtl_france.bin",
    "maxcng_france.bin",
    "maxbtl_germany.bin",
    "maxcng_germany.bin",
    "maxbtl_italy.bin",
    "maxcng_italy.bin",
    "maxbtl_spain.bin",
    "maxcng_spain.bin",
};

u8 fn_8004FB00(void)
{
    u8 id = 0xff;
    void* s = savedataBiosGetNowSavedataPtr();
    if (s != 0) {
        void* g = savedataBiosGetGamedataPtr(s);
        if (g != 0) {
            void* a = gamedataBiosGetGamedataAtttestPtr(g);
            if (a != 0) {
                id = gamedataAttestBiosGetLangareaId(a);
                if (id == 8) {
                    id = 2;
                }
            }
        }
    }
    return id;
}
}

static void _message(u32 msg, long port)
{
    msgctrlSetValue(0x2f, port + 1);
    menuCB_MessageDispOn(msg, 0);
}

static void _message_type2(u32 msg, long port)
{
    msgctrlSetValue(0x2f, port + 1);
    menuCB_MessageDispOn(msg, 1);
}

static void _menuWait(f32 time)
{
    f32 elapsed = 0.0f;
    while (elapsed < time) {
        GSthreadSwitch();
        elapsed += GSgfxVideoGetLastRenderTime() / (f32)GSgfxVideoGetVsyncRate();
    }
}

static u8 _waitAction(_GBA_Connect_WORK* work, _GBA_WAIT_FLAG flag)
{
    s32 f2;
    s32 f1;
    s32 f4;
    u8 connected = 1;
    work->state = 0;
    s8 ch = work->channel;
    if (ch >= 0) {
        if (gba_SIProbe(ch) == 0x40000) {
            connected = 0;
        }
    }
    f2 = (u32)flag & 2;
    f1 = (u32)flag & 1;
    f4 = (u32)flag & 4;
    while (1) {
        if (menuIsCheck(0x2a)) {
            GSthreadSwitch();
            continue;
        }
        if (f2 != 0) {
            if (windowGetKeyInfo()->buttons & 0x20) {
                work->state = 2;
                return 0;
            }
        }
        if (work->state == 8) {
            return 0;
        }
        if (work->phase.v[0] == 7) {
            return 0;
        }
        if (work->phase.v[1] == 7) {
            return 0;
        }
        if (work->phase.v[2] == 7) {
            return 0;
        }
        if (work->phase.v[3] == 7) {
            return 0;
        }
        if (f1 != 0) {
            s8 r = menuCB_MessageDispCheck();
            if (r == 0) {
                work->state = 1;
                return 1;
            }
            if (windowGetKeyInfo()->buttons & 0x10) {
                if (r == -1) {
                    work->state = 1;
                    return 1;
                }
            }
        }
        if (f4 != 0) {
            u32 st = gba_SIProbe(work->channel);
            if (st != 0x80) {
                if (connected) {
                    if (st == 0x40000) {
                        work->state = 4;
                        return 1;
                    }
                } else {
                    if (st != 0x40000) {
                        connected = 1;
                    }
                }
            }
        }
        GSthreadSwitch();
    }
}

static s32 _waitComplete(_GBA_Connect_WORK* work)
{
    work->state = 0;
    while (!AGB_IsComplete(work->channel)) {
        if (menuIsCheck(0x2a)) {
            GSthreadSwitch();
            continue;
        }
        if (windowGetKeyInfo()->buttons & 0x20) {
            work->state = 2;
            AGB_Terminate(work->channel);
            return 4;
        }
        if (work->state == 8) {
            return 4;
        }
        GSthreadSwitch();
    }
    work->state = 0;
    return AGB_GetStatus(work->channel);
}

static u8 _checkDisconnect(_GBA_Connect_WORK* work)
{
    s32* p;
    u8* port;
    s32 i;
    u8 result = 0;
    for (i = 0, p = work->phase.v, port = _menu_ports; i <= 3; p++, port++, i++) {
        if (*p == 5 || *p == 4) {
            if (!gbaCommandIsConnected(i + 1)) {
                menuSetEnablePort(menuGetEnablePort() & ~*port);
                *p = 7;
                work->state = 8;
            }
        }
        if (*p == 7) {
            result = 1;
        }
    }
    return result;
}

static u8 _showDisconnected(_GBA_Connect_WORK* work)
{
    s32 i;
    u32 msg;
    _mes_flag_type = 0;
    for (i = 0; i < 15; i++) {
        if (_checkDisconnect(work)) {
            break;
        }
        GSthreadSwitch();
    }
    GSsndPlayNow(0x13);
    for (i = 0; i < 4; i++) {
        if (work->phase.v[i] == 7) {
            break;
        }
    }
    if (i > 3) {
        if (!(work->state & 8)) {
            return 0;
        }
    }
    menuSetEnablePort(menuGetEnablePort() | 1);
    if (i == 0) {
        msg = 0x4438;
    } else if (work->type == 3) {
        if (GSinputIsConnected(1)) {
            msg = 0x442b;
        } else {
            msg = 0x442d;
        }
    } else {
        msg = 0x442b;
    }
    _mes_flag_type = 1;
    msgctrlSetValue(0x2f, i + 1);
    menuCB_MessageDispOn(msg, 1);
    if (msg == 0x4438 || msg == 0x442d) {
        do {
            GSthreadSwitch();
        } while (!GSinputIsConnected(1));
    }
    work->state = 8;
    return 1;
}

static u8 _error(_GBA_Connect_WORK* work, u32 msg, _GBA_PHASE phase)
{
    if (_showDisconnected(work)) {
        return (work->flags & 8) != 0;
    }
    work->phase.v[work->channel] = (s32)phase;
    _message(msg, work->channel);
    if ((work->flags & 8) == 0) {
        _waitAction(work, (_GBA_WAIT_FLAG)1);
    } else {
        if (_waitAction(work, (_GBA_WAIT_FLAG)7)) {
            return 1;
        }
    }
    AGB_Terminate(work->channel);
    return 0;
}

static u8 _poweroff(_GBA_Connect_WORK* work, _GBA_PHASE phase)
{
    u32 msg;
    menuSetEnablePort(menuGetEnablePort() | 1);
    if (!_showDisconnected(work)) {
        work->phase.v[work->channel] = (s32)phase;
    }
    if (_mes_flag_type == 1) {
        AGB_Terminate(work->channel);
        return 0;
    }
    if (work->type == 3) {
        if (GSinputIsConnected(1)) {
            msg = 0x442c;
        } else {
            msg = 0x442d;
        }
    } else {
        msg = 0x442c;
    }
    menuCB_MessageDispOn(msg, 1);
    if (msg == 0x442d) {
        do {
            GSthreadSwitch();
        } while (!GSinputIsConnected(1));
    }
    AGB_Terminate(work->channel);
    return 0;
}

static _GBA_Connect_WORK* _open_menu(_MENU_GBAC_TYPE type, u32 flags, long ch)
{
    _GBA_Connect_WORK* w = &gbaConectGBA_Connect_WORK;
    w->flags = flags;
    w->type = type;
    w->channel = chans[ch];
    switch (type) {
    case 0:
        w->timeout[0] = 1;
        w->timeout[1] = 2;
        w->timeout[2] = 0;
        w->timeout[3] = 0;
        break;
    case 1:
        w->timeout[0] = 4;
        w->timeout[1] = 2;
        w->timeout[2] = 2;
        w->timeout[3] = 0;
        break;
    case 2:
        w->timeout[0] = 1;
        w->timeout[1] = 2;
        w->timeout[2] = 2;
        w->timeout[3] = 2;
        break;
    case 3:
        w->timeout[0] = 4;
        w->timeout[1] = 2;
        w->timeout[2] = 2;
        w->timeout[3] = 2;
        break;
    }
    s32 i;

    for (i = 0; i < 4; i++) {
        const s32 * init = _initial_phase[type];
        s8 c = chans[i];
        w->phase.v[c] = init[c];
        if ((i < ch) && (w->phase.v[c] == 1)) {
            w->phase.v[c] = 5;
        }
        w->f48[i] = 1;
    }
    menuCB_SE_Play(0x14);
    menuOpen(0xb0, 0);
    menuCB_MessageDispOn(1, 0);
    _CB.b = -1;
    _CB.a = 2;
    return w;
}

static u8 _check_langarea(u8 lang)
{
    switch (pokecoloGetCountryCode()) {
    case 0:
        switch (lang) {
        case 1:
            lang = 1;
            break;
        case 2:
            lang = 2;
            break;
        case 3:
            lang = 4;
            break;
        case 4:
            lang = 5;
            break;
        case 5:
            lang = 3;
            break;
        case 7:
            lang = 6;
            break;
        default:
            return 0;
        }
        {
            void* s = savedataBiosGetNowSavedataPtr();
            if (s != 0) {
                void* g = savedataBiosGetGamedataPtr(s);
                if (g != 0) {
                    void* a = gamedataBiosGetGamedataAtttestPtr(g);
                    if (a != 0) {
                        u8 area = gamedataAttestBiosGetLangareaId(a);
                        if (area == lang) {
                            return 1;
                        }
                    }
                }
            }
        }
        break;
    case 1:
    case 2:
        switch (lang) {
        case 1:
            lang = 1;
            break;
        case 2:
            lang = 2;
            break;
        case 3:
            lang = 4;
            break;
        case 4:
            lang = 5;
            break;
        case 5:
            lang = 3;
            break;
        case 7:
            lang = 6;
            break;
        default:
            return 0;
        }
        if (lang == fn_8004FB00()) {
            return 1;
        }
        break;
    }
    return 0;
}

static u8 _mainFlow(_MENU_GBAC_TYPE type, u32 flags, Hero** heroes)
{
    Hero localHero;
    static const char* gba_bin_name[2] = {"maxbtl.bin", "maxcng.bin"};
    s32 nameIdx = 0;
    s32 i;
    bool first = false;
    _GBA_Connect_WORK* work;
    s8 ch;
    Hero* hero;
    s32 k;
    s32 j;
    s32 res;
    Hero* status;
    u32 info;
    bool ok;

    AGB_Terminate_init();
    if ((flags & 1) == 1) {
        nameIdx = 1;
    }
    if ((flags & 2) == 2) {
        nameIdx = 0;
    }
    switch (pokecoloGetCountryCode()) {
    case 0:
        while (!AGB_Prepare(gba_bin_name[nameIdx])) {
            GSthreadSwitch();
        }
        break;
    case 1: {
        const char** p = &lbl_8032EBD8[nameIdx] + 2;
        while (!AGB_Prepare(*p)) {
            GSthreadSwitch();
        }
        break;
    }
    }
    work = _open_menu(type, flags, 0);
    if (flags & 0x10) {
        if (type == 0 || type == 2) {
            status = (Hero*)savedataGetStatus(0, 2);
            work->channel = 0;
            work->phase.v[0] = 8;
            if (flags & 2) {
                _message(0x4437, 0);
                _menuWait(1.0f);
                if (!menuCBRule_CheckHero(status)) {
                    menuCBRule_ErrorFlagSet(status, 0);
                    menuCB_MessageDispOff();
                    menuCB_SE_Play(0x15);
                    menuCloseCustom(0xb0, 0, 1);
                    menuCB_Pokemon_ErrorDisp(status, 0);
                    return 0;
                }
            }
            if (heroes != 0 && heroes[0] != 0) {
                heroBiosCopy(heroes[0], status);
            }
            work->phase.v[0] = 10;
        }
    }
    menuGBACSetRomVer(0, 0xFFFF);
    for (i = 0; i < sizeof(chans); i++) {
        ch = chans[i];
        work->channel = ch;
        if (heroes != 0 && heroes[ch] != 0) {
            hero = heroes[ch];
        } else {
            hero = &localHero;
        }
        if (ch == 0) {
            nameIdx = 4;
            work->timeout[0] = nameIdx;
            if (nameIdx != 0) {
                work->timeout[0] = 3;
                work->f48[0] = 1;
            }
        }
        for (;;) {
            menuSetEnablePort(menuGetEnablePort() & ~_menu_ports[ch]);
            if (work->state != 4) {
                work->phase.v[ch] = 2;
                _message(0x441e, ch);
                if (!_waitAction(work, (_GBA_WAIT_FLAG)6)) {
                    return _poweroff(work, (_GBA_PHASE)6);
                }
            }
            _message(0x441f, ch);
            work->phase.v[ch] = 3;
            _CB.b = ch;
            _CB.a = 2;
            if (!first) {
                if (_waitComplete(work) == 4) {
                    return _poweroff(work, (_GBA_PHASE)6);
                }
                first = true;
            }
            AGB_Upload(ch, 0);
            switch (_waitComplete(work)) {
            case 0:
                break;
            case 4:
                return _poweroff(work, (_GBA_PHASE)6);
            case 2:
            default:
                if (_error(work, 0x4421, (_GBA_PHASE)6)) {
                    continue;
                }
                return 0;
            }
            work->phase.v[ch] = 4;
            for (j = 0; j < 300; j++) {
                if (gbaCommandIsConnected(ch + 1)) {
                    menuSetEnablePort(menuGetEnablePort() | _menu_ports[ch]);
                    break;
                }
                GSthreadSwitch();
            }
            if ((flags & 0x40) == 0) {
                _message(0x4435, ch);
                _menuWait(1.0f);
            }
            heroInit(hero);
            info = 0;
            AGB_GetPokemon(ch, hero, &info);
            res = _waitComplete(work);
            switch (res) {
            case 4:
                return _poweroff(work, (_GBA_PHASE)6);
            }
            menuGBACSetRomVer(((info >> 10) & 0xF), gba_player_number[i]);
            if (((info >> 8) & 3) != 0) {
                if (_error(work, 0x4422, (_GBA_PHASE)6)) {
                    continue;
                }
                return 0;
            }
            if (!_check_langarea(((info >> 4) & 0xF))) {
                if (_error(work, 0x4423, (_GBA_PHASE)6)) {
                    continue;
                }
                return 0;
            }
            switch (res) {
            case 0:
                if (info & 2) {
                    break;
                }
            default:
                if (_error(work, 0x4422, (_GBA_PHASE)6)) {
                    continue;
                }
                return 0;
            }
            if (flags & 1) {
                ok = true;
                switch (((info >> 10) & 0xF)) {
                case 1:
                case 2:
                    if (!(info & 0x4000)) {
                        ok = false;
                    }
                    if (!ok) {
                        if (_error(work, 0x4445, (_GBA_PHASE)6)) {
                            continue;
                        }
                        return 0;
                    }
                    break;
                case 3:
                case 4:
                    if (!(info & 8)) {
                        ok = false;
                    }
                    if (!ok) {
                        if (_error(work, 0x4446, (_GBA_PHASE)6)) {
                            continue;
                        }
                        return 0;
                    }
                    break;
                case 5:
                    if (!(info & 0x4000)) {
                        ok = false;
                    }
                    if (!ok) {
                        if (_error(work, 0x4447, (_GBA_PHASE)6)) {
                            continue;
                        }
                        return 0;
                    }
                    break;
                default:
                    if (_error(work, 0x4421, (_GBA_PHASE)6)) {
                        continue;
                    }
                    return 0;
                }
            }
            if (flags & 2) {
                if (!(info & 1)) {
                    if (_error(work, 0x4424, (_GBA_PHASE)6)) {
                        continue;
                    }
                    return 0;
                }
                if (!menuCBRule_CheckHero(hero)) {
                    menuCBRule_ErrorFlagSet(hero, gba_player_number[i]);
                    menuCB_MessageDispOff();
                    menuCB_SE_Play(0x15);
                    menuCloseCustom(0xb0, 0, 1);
                    menuCB_Pokemon_ErrorDisp(hero, gba_player_number[i]);
                    if ((flags & 8) == 0) {
                        return 0;
                    }
                    work->saved.v[0] = work->phase.v[0];
                    work->saved.v[1] = work->phase.v[1];
                    work->saved.v[2] = work->phase.v[2];
                    work->saved.v[3] = work->phase.v[3];
                    work = _open_menu(type, flags, i);
                    if (ch == 0) {
                        nameIdx = 4;
                        work->timeout[0] = nameIdx;
                        if (nameIdx != 0) {
                            work->timeout[0] = 3;
                            work->f48[0] = 1;
                        }
                    }
                    work->phase.v[0] = work->saved.v[0];
                    work->phase.v[1] = work->saved.v[1];
                    work->phase.v[2] = work->saved.v[2];
                    work->phase.v[3] = work->saved.v[3];
                    work->phase.v[ch] = 6;
                    GSthreadSwitch();
                    for (k = 0; k < i; k++) {
                        if (work->phase.v[chans[k]] == 7) {
                            return _poweroff(work, (_GBA_PHASE)6);
                        }
                    }
                    _message_type2(0x4425, ch);
                    continue;
                }
            }
            break;
        }
        AGB_Terminate(ch);
        GSsndPlayNow(0x1b);
        work->phase.v[ch] = 5;
        menuSetEnablePort(menuGetEnablePort() | _menu_ports[ch]);
        _message(0x4420, ch);
        switch (type) {
        case 0:
            if (_waitAction(work, (_GBA_WAIT_FLAG)3)) {
                return 1;
            }
            return _poweroff(work, (_GBA_PHASE)6);
        case 1:
            if (ch == 2) {
                if (_waitAction(work, (_GBA_WAIT_FLAG)3)) {
                    return 1;
                }
                return _poweroff(work, (_GBA_PHASE)6);
            }
            break;
        case 2:
            if (ch == 3) {
                if (_waitAction(work, (_GBA_WAIT_FLAG)3)) {
                    return 1;
                }
                return _poweroff(work, (_GBA_PHASE)6);
            }
            break;
        case 3:
            if (ch == 0) {
                if (_waitAction(work, (_GBA_WAIT_FLAG)3)) {
                    return 1;
                }
                return _poweroff(work, (_GBA_PHASE)6);
            }
            break;
        }
        work->channel = chans[i + 1];
        if (!_waitAction(work, (_GBA_WAIT_FLAG)7)) {
            return _poweroff(work, (_GBA_PHASE)6);
        }
    }
    return 1;
}

extern "C" {
s32 openMenuGBA(_MENU_GBAC_TYPE type, u32 flags, Hero** heroes)
{
    u8 oldPorts = menuSetEnablePort(1);
    s32 i;
    AGB_FileBuffAlloc();
    u8 ok = _mainFlow(type, flags, heroes);
    winMsgClose(0);
    if (menuIsCheck(0xb0)) {
        menuCB_MessageDispOff();
        menuCB_SE_Play(0x15);
        menuCloseCustom(0xb0, 0, 1);
    }
    menuSetEnablePort(oldPorts);
    for (i = 0; i < 3; i++) {
        AGB_Terminate(i);
    }
    AGB_FileBuffFree();
    return ok ? 0 : -1;
}

static u16 GBA_ROM_VERSION_FLAG[4] = {0, 0, 0, 0};

void menuGBACSetRomVer(u16 ver, u16 idx)
{
    switch (idx) {
    case 0:
    case 1:
    case 2:
    case 3:
        GBA_ROM_VERSION_FLAG[idx] = ver;
        break;
    default:
        GBA_ROM_VERSION_FLAG[0] = GBA_ROM_VERSION_FLAG[1] = GBA_ROM_VERSION_FLAG[2] = GBA_ROM_VERSION_FLAG[3] = 0;
        break;
    }
    if (idx == 0xFFFF) {
        gbaCommandSetKeyState(1, 0);
        gbaCommandSetKeyState(2, 0);
        gbaCommandSetKeyState(3, 0);
        gbaCommandSetKeyState(4, 0);
    }
}

u16 menuGBACGetRomVer(u16 idx)
{
    if (idx > 3) {
        return 0;
    }
    return GBA_ROM_VERSION_FLAG[idx];
}
}
