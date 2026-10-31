#pragma peephole off
#pragma pool_strings off
#include <dolphin/types.h>
#include <game/menuBingoLayout.hpp>

struct BINGO_PANEL_dd_ {
    u8 type;
    u8 tokusei;
    u8 unk2[2];
    u16 no;
    u16 waza;
    u16 hosei;
};

struct BINGO_GRID_dd_ {
    u8 grid;
    u8 pos;
};

struct BINGO_DATA_dd_ {
    u8 no;
    u8 unk1[2];
    u8 level;
    u8 unk4;
    u8 ball;
    u8 unk6[0x10 - 6];
    u16 score[10];
    BINGO_PANEL_dd_ panel[14];
    BINGO_GRID_dd_ grid[3];
    u8 unkB6[2];
};

class bingo_bios {
public:
    bool isClearPlus(u32 index);
    void setClearPlus(u32 index);
    void setClear(u32 index);
    static void setSelect(u32 index);
    bool isSelect(u32 index);
    bool isClear(u32 index);
    u32 getClearLv();
    u16 getScore(BINGO_DATA_dd_* data, u8 index);
    u8 getGridPos(BINGO_DATA_dd_* data, u32 index);
    u8 getGridGrid(BINGO_DATA_dd_* data, u32 index);
    static u8 getPanelHoseiVal(BINGO_DATA_dd_* data, u32 index);
    static u8 getPanelHoseiKind(BINGO_DATA_dd_* data, u32 index);
    u16 getPanelWaza(BINGO_DATA_dd_* data, u32 index);
    u16 getPanelNo(BINGO_DATA_dd_* data, u32 index);
    u8 getPanelTokusei(BINGO_DATA_dd_* data, u32 index);
    u8 getPanelType(BINGO_DATA_dd_* data, u32 index);
    u8 getBall(BINGO_DATA_dd_* data);
    u8 getLevel(BINGO_DATA_dd_* data);
    u8 getNo(BINGO_DATA_dd_* data);
    static u8 getStaticIdx(u8 index);
    static void setStaticIdx(u8 idx0, u8 idx1);
    static u8 getStaticResult();
    static void setStaticResult(u8 result);
    static void decStaticBall();
    static u8 getStaticBall();
    static void setStaticBall(u8 ball);
    static BINGO_DATA_dd_* getStaticSheet();
    static void setStaticNo(u8 no);
};

class Pokemon {
public:
    void* getPokemonDataPtr() const;
    u8 data[0xC4];
    char* getNicknamePtr();
};

struct BingoPokemon {
    Pokemon pkm;
    u8 point;
    u8 order;
    u8 flag;
    u8 pad;
};

struct BingoPanel {
    u8 state;
    u8 idx;
    u8 flag;
    u8 pad;
    f32 scale;
};

class cBingo {
public:
    u32 save;
    BINGO_DATA_dd_* sheet;
    BingoPanel panel[16];
    BingoPanel shuf[16];
    s32 f108;
    u8 f10c;
    bool lineState[10];
    u8 lineFlag[10];
    u8 f121;
    u8 mode;
    u8 pad123;
    s32 f124;
    u8 f128;
    u8 ball;
    u8 epoint;
    u8 f12b;
    u8 f12c;
    u8 f12d;
    u8 f12e;
    u8 f12f;
    u8 f130;
    u8 pad131[3];
    s32 f134;
    s32 f138;
    u32 f13c;
    f32 f140;
    s32 f144;
    u8 f148;
    u8 pad149[3];
    u32 color;

    void setStepMessage();
    void dispPanel(u32 n, tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
    void dispOpenPanel(u32 n, tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
    void dispShufflePanel(u32 n, tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
    void dispPkmPanel(u32 n, tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
    bool isChgBingoLine(s32 n);
    int getF12e() const { return f12e; }
    bool lineDone(int line);
    bool noPanelFlagged();
    u32 countLines();
    void playLineSe();
    int newLines();
    u8 pkmState();
    u8 flagAt(u32 i);
    u8 stateAt(u32 i);
    void setFlagAt(int i, u8 v);
    u8 flagAtP(u32 i);
    bool canMove(int pos);
    void makeRandomSheet();
    void SetupSheet(u32 n);
    void ResetSheet(u32 n);
    static void* loadPkmFace(void* arg);

    static BingoPokemon mPokemon[14];
    static u32 MenuEpMsgIdx[2];
    static u32 MenuBingoMsgIdx[2];
    static const u32 TopCurIdx[11];
    static const u16 ClosePanelIdx[18];
    static const u16 OpenPanelType[18];
    static u32 SheetDocMsgIdx[11][3];
    static u32 MenuPkmMsgIdx[3];
};

const u32 cBingo::TopCurIdx[11] = {0x521, 0x522, 0x523, 0x524, 0x525, 0x526, 0x527, 0x528, 0x529, 0x52A, 0x693};
const u16 cBingo::ClosePanelIdx[18] = {0x292, 0x28E, 0x28A, 0x284, 0x28D, 0x28C, 0x291, 0x289, 0x286,
                                       0x29E, 0x28B, 0x290, 0x28F, 0x283, 0x288, 0x293, 0x285, 0x287};
const u16 cBingo::OpenPanelType[18] = {0x19E, 0x1A0, 0x19C, 0x194, 0x1A2, 0x199, 0x19D, 0x19A, 0x198,
                                       0x193, 0x1A1, 0x1A3, 0x1A4, 0x197, 0x19B, 0x195, 0x196, 0x19F};
struct Ord16 {
    u8 v[16];
};
static const Ord16 kOrder = {{0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10, 9}};
u32 cBingo::SheetDocMsgIdx[11][3] = {
    {0xDB25, 0xDB0B, 0xDAC1}, {0xDB26, 0xDB0D, 0xDAC1}, {0xDB27, 0xDB0F, 0xDAC1}, {0xDB28, 0xDB11, 0xDAC2},
    {0xDB29, 0xDB13, 0xDAC2}, {0xDB2A, 0xDB15, 0xDAC2}, {0xDB2B, 0xDB17, 0xDAC3}, {0xDB2C, 0xDB19, 0xDAC3},
    {0xDB2D, 0xDB1B, 0xDAC3}, {0xDB2E, 0xDB1D, 0xDAC4}, {0xDB2F, 0xDB1F, 0xDB21}};
u32 cBingo::MenuPkmMsgIdx[3] = {0xDAE3, 0xDAE4, 0xDAE5};
u32 cBingo::MenuEpMsgIdx[2] = {0xDAEF, 0xDAF0};
u32 cBingo::MenuBingoMsgIdx[2] = {0xDB34, 0xDB35};

BingoPokemon cBingo::mPokemon[14];
inline u8 cBingo::flagAtP(u32 i) {
    u32 off = i << 3;
    u8* p = (u8*)this;
    return p[off + 10];
}

inline void cBingo::setFlagAt(int i, u8 v) {
    ((u8*)this)[(i << 3) + 10] = v;
}

inline u8 cBingo::stateAt(u32 i) {
    u32 off = i << 3;
    return ((u8*)this)[off + 8];
}

inline u8 cBingo::flagAt(u32 i) {
    u32 off = i << 3;
    return ((u8*)this)[off + 10];
}

inline bool cBingo::lineDone(int line) {
    u32 k;
    switch (line) {
    case 0:
    case 1:
    case 2:
    case 3:
        for (k = 0; k < 4; k++) {
            if (panel[line + k * 4].flag == 0) break;
            if (k == 3) return true;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        for (k = 0; k < 4; k++) {
            if (panel[(7 - line) * 4 + k].flag == 0) break;
            if (k == 3) return true;
        }
        break;
    case 8:
        for (k = 0; k < 4; k++) {
            if (panel[(3 - k) + k * 4].flag == 0) break;
            if (k == 3) return true;
        }
        break;
    case 9:
        for (k = 0; k < 4; k++) {
            if (flagAt((u8)(k * 5)) == 0) break;
            if (k == 3) return true;
        }
        break;
    }
    return false;
}

inline bool cBingo::noPanelFlagged() {
    int i;
    u32 count = 0;
    for (i = 0; i < 16; i++) {
        if (panel[i].flag != 0) count++;
    }
    if (count) {
        return false;
    } else {
        return true;
    }
}

inline u32 cBingo::countLines() {
    int i;
    u32 n;
    for (i = n = 0; i < 10; i++) {
        if (lineDone(i)) n++;
    }
    return n;
}

inline u8 cBingo::pkmState() {
    if (f108 != 0) return 0;
    switch (f144) {
    case 7:
        return 1;
    case 5:
    case 8:
        return 2;
    default:
        return 0;
    }
}

inline bool cBingo::canMove(int pos) {
    if (mode != 0) {
        s32 v = f134;
        int col = v % 4;
        int row = v / 4;
        if ((u32)(v - 4) == pos && row - 1 >= 0) {
            return flagAtP(pos) == 0;
        }
        if ((u32)(v + 4) == pos && row + 1 <= 3) {
            return flagAtP(pos) == 0;
        }
        if ((u32)(v - 1) == pos && col - 1 >= 0) {
            return flagAtP(pos) == 0;
        }
        if ((u32)(v + 1) == pos && col + 1 <= 3) {
            return flagAtP(pos) == 0;
        }
    } else {
        int col = pos % 4;
        int row = pos / 4;
        if (row - 1 >= 0 && flagAtP(pos - 4) != 0) {
            return true;
        }
        if (row + 1 <= 3 && flagAtP(pos + 4) != 0) {
            return true;
        }
        if (col - 1 >= 0 && flagAtP(pos - 1) != 0) {
            return true;
        }
        if (col + 1 <= 3 && flagAtP(pos + 1) != 0) {
            return true;
        }
    }
    return noPanelFlagged();
}

struct GSvec2 {
    f32 x;
    f32 y;
};

struct MenuSpriteVal {
    u8 pad0[4];
    s16 w;
    s16 h;
};

extern "C" {
s16 lbl_804EAA00;
}

static cBingo gBingo;
#define mPokemon cBingo::mPokemon

extern "C" {
void* savedataGetStatus(void* save, s32 kind);
s32 GSfloorGetCurrent(void);
void GSthreadSwitch(void);
u32 HSD_Rand(void);
void* memset(void* dst, int val, u32 n);
u32 gamedataGetStatus(void* ptr, u32 kind);
void pokemonCreate(void* pokemon, u16 id, u8 level, u32 attest);
void menuFaceLoad(s32, void* (*)(void*), void*);
u8 GSfloorPush(u32 id);
void winSeqSetMenu(s32 menuID, u32 id);
void winSpriteSetDisp(tagSPRITE_WORK* sp, bool on);
void* memcpy(void* dst, const void* src, u32 n);
void menuFaceDispFromID2(tagWINDOW_WORK*, tagSPRITE_WORK*, u16, GSvec2*);
u16 pokemonDataBiosGetStatusFaceMenuSpriteId(void* pdata, u16 unk);
void GSmsgPrint2(s32, s32, s32, u32, s32);
u32 GSmsgGetRect(u32 msg);
char* GSmsgGetGSchar(u32 msg);
u32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index);
s32 menuSubGetPokemonSexForDisp(void* pokemon);
u16 zokuseiGetPokemonSpriteID(void* pokemon, u16 idx);
MenuSpriteVal* menuSpriteBiosGetValPtr(void);
void FlashSystemSetNowFrame(u32 id, u32 frame);
void windowDrawSprite2(s16 x, s16 y, s16 w, s16 h, u32 color, void* ctx, u16 key, u32 flags, s32 layer);
f32 timeGetLastFrameSec(void);
u8 pokemonDataBiosGetZokuseiDataId(void* pdata, u16 index);
double cos(double x);
double __fabs(double x);
s32 winSpriteGetLayerID(tagWINDOW_WORK* w, tagSPRITE_WORK* sp);
void windowDrawSprite(s16 x, s16 y, void* ctx, u16 key, u32 flags, s32 layer);
u32 FlashSystemGetNowFrame(u32);
u32 FlashSystemGetEndFrame(u32);
void msgctrlSetValue(s32 id, u32 value);
void GSmsgPrintRect(s32, s32, s32, s32, s32, u32, u32);
double sin(double x);
s32 pokecoloGetLanguage(void);
u32 floorGetCurrentGroupID(void);
s8 fadeCheck(s32);
u16 fadeGetType(void);
void fadeSet(s32 type, f32 time);
void* menuSpriteBiosGetPtr(u32 id);
u16 windowGetKeyRepeat(void);
u16 windowGetKeyTrg(void);
void menuPlaySe(s32 menu, s32 se);
u8 winSeqCheckMove(s32 menuID);
u8 GSsndPlayNow(u32 id);
void menuCursorNormal(tagWINDOW_WORK* w, s32 flag);
u8 menuIsCheck(s32 menuID);
void menuClose(s32 menuID);
tagWINDOW_WORK* windowSearchID(s32 id);
u32* windowGetAllocPtr(tagWINDOW_WORK* w);
s8 windowGetParam(tagWINDOW_WORK* w, u32 idx);
}

struct CursorPos {
    s16 top;
    s16 pos;
};

extern "C" s32 fn_80091B98(void);

struct MenuItemX {
    u8 pad[8];
    s16 x;
};

struct KeyInfoB {
    u16 on;
    u16 up;
    u16 trg;
    u16 rep;
    u16 rel;
    u8 pad[0x10];
};

extern u32* bingo_data_number;

extern "C" {
s32 menuOpenCustom(s32 menuID, ...);
KeyInfoB* windowGetKeyInfo(void);
void menuCloseSync(s32 menuID, s32 wait);
u8 menuOffScreenSetPriority(u8 val);
u8 GSfloorPop(void);
void floorSetFadeScript(u32 out, u32 in);
u32 GSflagGet(u32 id);
void menuItemBiosSetSelectFlag(s32 menuID, u32 index, bool flag);
void* menuItemBiosGetPtr(s32 menuID, u32 index);
void FlashSystemSetNowFrameLabel(u32 id, const char* label);
void FlashSystemSetPlayFrameLabel(u32 id, const char* from, const char* to);
u32 FlashSystemGetFrameFromLabel(u32 id, const char* label);
s32 menuOpen(s32 menuID, s32 arg);
u8 menuFaceCheckLoading(void);
s8 menuSubOpenYesNo(u8 type, s16 x, s16 y, s32 initial);
s32 menuSubOpenSelect3(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags, s32 a6, u8 a7, u8 a8);
void menuSetPosition(s32 menuID, s32 x, s32 y);
void spriteSetOffset(s32 layer, s16 x, s16 y);
void spriteClearScissor(s32 layer);
void spriteSetEnv(s32 layer);
u16 fightEncount(u16 id);
u32 menuSubOpenSelect2(u8 selection, s32* values, s32 a2, s32 x, s32 y, s32 flags, s32 a6, u8 a7);
s32 windowCheckCursor(s32 id, u8 wait);
void menuCloseCustom(s32 menuID, s32 a, s32 b);
}

extern "C" {
void menuSubCalcColor(void);
u16 pokemon_GetPokemonDataId(void* poke);
u8 pokemonDB_GetTokuseiDataId(u16 id, u16 idx);
u32 pokemonTokuseiDataBiosGetPtr(u16 index);
u32 pokemonTokuseiDataBiosGetName(u32* data);
u8 wazaDB_GetZokuseiDataId(u16 id);
u16 zokuseiBiosGetSpriteID(u16 id);
u32 wazaGetStatus(void* ptr, u16 dataID, u16 status, u32 index);
}

static inline int findPokemonOrder(u32 n) {
    for (int j = 0; j < 14; j++) {
        if (mPokemon[j].order == n) return j;
    }
    return -1;
}

static inline int findPokemonNo(u32 i) {
    for (int j = 0; j < 14; j++) {
        if (mPokemon[j].order == i + 1) return j;
    }
    return -1;
}

static inline BingoPokemon* pokemonNo(u32 i) {
    return &mPokemon[findPokemonNo(i)];
}

static inline int countPokemon() {
    int i;
    for (i = 0; i < 4; i++) {
        if (findPokemonNo(i) == -1) break;
    }
    return i;
}

static inline int sumPoints() {
    int i;
    int sum;
    for (i = sum = 0; i < 4; i++) {
        int j = findPokemonNo(i);
        if (j == -1) break;
        sum += mPokemon[j].point;
    }
    return sum;
}

#define BIOS ((bingo_bios*)&gBingo)

static inline u32 clearCount() {
    u32 n = 0;
    for (u32 i = 0; i < 10; i++) {
        if (BIOS->isClear(i)) n++;
    }
    return n;
}

static inline bool sheetCleared(BINGO_DATA_dd_* s) {
    u8 no = BIOS->getNo(s);
    return BIOS->isClear(no - 1);
}

static inline bool sheetClearedPlus(BINGO_DATA_dd_* s) {
    u8 no = BIOS->getNo(s);
    return BIOS->isClearPlus(no - 1);
}

inline double fabsInline(double x) {
    return __fabs(x);
}

static inline f32 cosfInline(f32 x) {
    return (f32)cos(x);
}

static inline f32 sinfInline(f32 x) {
    return (f32)sin(x);
}

static inline u8 selectRank() {
    if (BIOS->isSelect(8)) return 2;
    if (BIOS->isSelect(5)) return 1;
    return 0;
}

static inline bool hasGrid1() {
    for (u32 i = 0; i < 16; i++) {
        if (gBingo.panel[i].flag != 0 && gBingo.panel[i].state != 0 &&
            ((bingo_bios*)&gBingo)->getGridGrid(gBingo.sheet, gBingo.panel[i].idx) == 1) {
            return true;
        }
    }
    return false;
}

static inline u16 faceKey(cBingo* self, BingoPanel* p, u32 n) {
    void* pdata = mPokemon[p->idx].pkm.getPokemonDataPtr();
    u8 type = ((bingo_bios*)self)->getPanelType(self->sheet, self->panel[(u16)n].idx);
    return cBingo::ClosePanelIdx[pokemonDataBiosGetZokuseiDataId(pdata, (u16)(type % 18))];
}

static inline u16 faceKeyShuf(cBingo* self, BingoPanel* q) {
    void* pdata = mPokemon[q->idx].pkm.getPokemonDataPtr();
    u8 type = ((bingo_bios*)self)->getPanelType(self->sheet, q->idx);
    return cBingo::ClosePanelIdx[pokemonDataBiosGetZokuseiDataId(pdata, (u16)(type % 18))];
}

extern "C" {

u8 menuBattleDeBingoGetMode(void) {
    return gBingo.mode;
}

u8 menuBattleDeBingoGetMball(void) {
    return gBingo.ball;
}

u8 menuBattleDeBingoGetEpoint(void) {
    int sum = sumPoints();
    return sum + gBingo.epoint;
}

u8 menuBattleDeBingoGetNum(void) {
    if (bingo_bios::getStaticSheet()) {
        return ((bingo_bios*)&gBingo)->getNo(bingo_bios::getStaticSheet());
    }
    return 0;
}

u8 menuBattleDeBingoGetLine(void) {
    return bingo_bios::getStaticResult() & 0xF;
}

u8 menuBattleDeBingoGetResult(void) {
    u8 r = bingo_bios::getStaticResult();
    return (r >> 4) & 0xF;
}

void menuBattleDeBingo(void) {
    GSfloorPush(0x388);
}

s32 menuBingoPokemonDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    u16 tok;
    BingoPokemon* q;
    u32 n = 0;
    menuSubCalcColor();
    u32 rf_t = gBingo.f12c;
    int cur = findPokemonOrder(rf_t + 1);
    BingoPokemon* p = &mPokemon[cur];
    s32 layer = winSpriteGetLayerID(w, sp);
    switch (sp->id) {
    case 0x5EE: {
        u32 rf_t = gBingo.f12c;
        int i = findPokemonOrder(rf_t + 1);
        u32 waza = wazaGetStatus(0, BIOS->getPanelWaza(gBingo.sheet, i), 1, 0);
        if (waza != 0) {
            sp->msgID = 0xDB39;
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDB44));
            msgctrlSetValue(0x4D, (u32)GSmsgGetGSchar(waza));
            GSmsgPrint2(winSpriteGetLayerID(w, sp), 0x5A, 0, w->alpha | 0xFFFFFF00, 0x4277);
        }
        break;
    }
    case 0x5ED: {
        u32 rf_t = gBingo.f12c;
        int i = findPokemonOrder(rf_t + 1);
        u32 key = zokuseiBiosGetSpriteID(wazaDB_GetZokuseiDataId(BIOS->getPanelWaza(gBingo.sheet, i)));
        if (key != 0) {
            windowDrawSprite(0, 0, w, key, 0, layer);
        }
        break;
    }
    case 0x5EB: {
        u32 rf_t = gBingo.f12c;
        int i = findPokemonOrder(rf_t + 1);
        u32 tok = BIOS->getPanelTokusei(gBingo.sheet, i);
        u32 id = pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(p), tok);
        if (id != 0) {
            sp->msgID = 0xDB3A;
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDB45));
            msgctrlSetValue(0x4D, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName((u32*)pokemonTokuseiDataBiosGetPtr(id))));
            GSmsgPrint2(winSpriteGetLayerID(w, sp), 0x5A, 0, w->alpha | 0xFFFFFF00, 0x4277);
        }
        break;
    }
    case 0x8B5:
        n++;
    case 0x8A7:
        n++;
    case 0x899:
        n++;
    case 0x88B: {
        u32 cnt = countPokemon();
        if (n < cnt) {
            int i = findPokemonOrder(n + 1);
            u32 waza = wazaGetStatus(0, BIOS->getPanelWaza(gBingo.sheet, i), 1, 0);
            if (waza != 0) {
                msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDB44));
                msgctrlSetValue(0x4D, (u32)GSmsgGetGSchar(waza));
                sp->msgID = 0xDB39;
                GSmsgPrint2(winSpriteGetLayerID(w, sp), 0x5A, 0, w->alpha | 0xFFFFFF00, 0x4277);
            }
        }
        break;
    }
    case 0x8B4:
        n++;
    case 0x8A6:
        n++;
    case 0x898:
        n++;
    case 0x88A: {
        u32 cnt = countPokemon();
        if (n < cnt) {
            findPokemonOrder(n + 1);
            int i = findPokemonOrder(n + 1);
            u32 key = zokuseiBiosGetSpriteID(wazaDB_GetZokuseiDataId(BIOS->getPanelWaza(gBingo.sheet, i)));
            if (key != 0) {
                windowDrawSprite(0, 0, w, key, 0, layer);
            }
        }
        break;
    }
    case 0x8B2:
        n++;
    case 0x8A4:
        n++;
    case 0x896:
        n++;
    case 0x888: {
        u32 cnt = countPokemon();
        if (n < cnt) {
            int j = findPokemonOrder(n + 1);
            q = &mPokemon[j];
            if ((s16)n < 0) {
                tok = BIOS->getPanelTokusei(gBingo.sheet, findPokemonNo(gBingo.f12c));
            } else {
                tok = BIOS->getPanelTokusei(gBingo.sheet, findPokemonOrder((s16)n + 1));
            }
            u32 id = pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(q), tok);
            if (id != 0) {
                msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDB45));
                msgctrlSetValue(0x4D, (u32)GSmsgGetGSchar(pokemonTokuseiDataBiosGetName((u32*)pokemonTokuseiDataBiosGetPtr(id))));
                sp->msgID = 0xDB3A;
                GSmsgPrint2(winSpriteGetLayerID(w, sp), 0x5A, 0, w->alpha | 0xFFFFFF00, 0x4277);
            }
        }
        break;
    }
    case 0x8A9: case 0x8AA: case 0x8AB: case 0x8AC: case 0x8AD: case 0x8AE: case 0x8AF: case 0x8B0: case 0x8B1:
        n++;
    case 0x89B: case 0x89C: case 0x89D: case 0x89E: case 0x89F: case 0x8A0: case 0x8A1: case 0x8A2: case 0x8A3:
        n++;
    case 0x88D: case 0x88E: case 0x88F: case 0x890: case 0x891: case 0x892: case 0x893: case 0x894: case 0x895:
        n++;
    case 0x87F: case 0x880: case 0x881: case 0x882: case 0x883: case 0x884: case 0x885: case 0x886: case 0x887: {
        winSpriteSetDisp(sp, false);
        u32 cnt = countPokemon();
        if (n < cnt) {
            winSpriteSetDisp(sp, true);
        }
        break;
    }
    case 0x88C:
    case 0x89A:
    case 0x8A8:
        break;
    }
    return 0;
}

static inline BingoPokemon* panelPokemon(int i) {
    if (gBingo.panel[i].state != 0) return 0;
    return &mPokemon[gBingo.panel[i].idx];
}

s32 menuBingoMessageDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    enum TsE { TsE0 };
    s16 b;
    u32 msg = gBingo.f13c;
    char* nick;
    switch (sp->id) {
    case 0x8D8: {
        gBingo.f140 += timeGetLastFrameSec();
        u32 count = 0;
        sp->msgID = 0;
        switch (msg) {
        case 0xDB0A: {
            s32 a;
            s32 layer;
            layer = winSpriteGetLayerID(w, sp);
            a = (s16)(u8)GSmsgGetRect(0xDAD8);
            b = (u16)(GSmsgGetRect(0xDAD8) >> 16) / 4;
            u8 no = BIOS->getNo(gBingo.sheet);
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDAD8));
            GSmsgPrint2(layer, 0, 0, -1, 0x4276);
            u32 row = (u8)(no - 1);
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(cBingo::SheetDocMsgIdx[row][0]));
            GSmsgPrint2(layer, (s16)(b * 11), 0, -1, 0x4277);
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(cBingo::SheetDocMsgIdx[row][1]));
            GSmsgPrint2(layer, 0, a, -1, 0x4276);
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(cBingo::SheetDocMsgIdx[row][2]));
            GSmsgPrint2(layer, b * 4, 0, -1, 0x4277);
            break;
        }
        case 0xDAEE: {
            int ep = gBingo.epoint;
            if (ep < 0) break;
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            msgctrlSetValue(0x2F, ep);
            sp->msgID = 0x4276;
            break;
        }
        case 0xDAF2:
        case 0xDAF3:
        case 0xDB22:
            if (panelPokemon(gBingo.f134) == 0) break;
            nick = panelPokemon(gBingo.f134)->pkm.getNicknamePtr();
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            msgctrlSetValue(0x32, (u32)nick);
            sp->msgID = 0x4276;
            break;
        case 0xDAF4: {
            if (panelPokemon(gBingo.f138) == 0) break;
            nick = panelPokemon(gBingo.f138)->pkm.getNicknamePtr();
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            msgctrlSetValue(0x32, (u32)nick);
            sp->msgID = 0x4276;
            break;
        }
        case 0xDAE7: {
            if (pokemonNo(gBingo.f12c) == 0) break;
            int j = findPokemonNo(gBingo.f12c);
            nick = mPokemon[j].pkm.getNicknamePtr();
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            msgctrlSetValue(0x32, (u32)nick);
            sp->msgID = 0x4276;
            break;
        }
        case 0xDAEA: {
            BingoPanel* panels = gBingo.panel;
            if (panels[gBingo.f134].state == 0) break;
            int m = -1;
            int g = m;
            if (panels[gBingo.f134].state != 0) {
                g = BIOS->getGridGrid(gBingo.sheet, panels[gBingo.f134].idx);
            }
            switch (g) {
            case 1:
                m = 0xDAED;
                break;
            case 2:
                m = 0xDAEB;
                break;
            case 3:
                m = 0xDAEC;
                break;
            }
            if (m < 0) break;
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            msgctrlSetValue(0x4D, (u32)GSmsgGetGSchar(m));
            sp->msgID = 0x4276;
            break;
        }
        case 0xDAF6: {
            u8 base = gBingo.f12d;
            count = gBingo.countLines();
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            msgctrlSetValue(0x2F, count - base);
            sp->msgID = 0x4276;
            break;
        }
        case 0xDAF7: {
            u8 base = gBingo.f12d;
            count = gBingo.countLines();
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            u32 d = count - base;
            msgctrlSetValue(0x2F, d);
            msgctrlSetValue(0x2F, d);
            sp->msgID = 0x4276;
            break;
        }
        case 0xDADE:
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            sp->msgID = 0x4276;
            break;
        case 0xDB3B:
            count = gBingo.countLines();
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            msgctrlSetValue(0x2F, count);
            sp->msgID = 0x4276;
            break;
        case 0xDADF:
        case 0xDAE0:
        case 0xDAE1:
        case 0xDAE2:
        case 0xDAE6:
        case 0xDAF1:
        case 0xDAF5:
        case 0xDAF8:
        case 0xDAF9:
        case 0xDAFA:
        case 0xDB23:
        case 0xDB33:
        case 0xDB37:
        case 0xDB43:
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(msg));
            sp->msgID = 0x4276;
            break;
        }
        break;
    }
    case 0x8DA:
        winSpriteSetDisp(sp, false);
        if (gBingo.getF12e() != 0) winSpriteSetDisp(sp, true);
        break;
    case 0x8DC: {
        winSpriteSetDisp(sp, false);
        cBingo* self = &gBingo;
        if (self->f144 == 13) {
            if (sheetClearedPlus(self->sheet)) {
                winSpriteSetDisp(sp, true);
                msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDB32));
                sp->msgID = 0x4277;
            } else if (sheetCleared(self->sheet)) {
                winSpriteSetDisp(sp, true);
                msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDADB));
                sp->msgID = 0x4277;
            }
        } else {
            u32 cnt = clearCount();
            if (cnt == 10 && self->f144 == 7 && gBingo.f108 == 0) {
                winSpriteSetDisp(sp, true);
                if (gBingo.mode != 0) {
                    msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDB35));
                } else {
                    msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDB34));
                }
                sp->msgID = 0x4277;
            }
        }
        break;
    }
    case 0x8DD: case 0x8DE: case 0x8DF: case 0x8E0: case 0x8E1: case 0x8E2: case 0x8E3: case 0x8E4:
        winSpriteSetDisp(sp, false);
        if (gBingo.f144 == 7 && gBingo.f108 == 0 && gBingo.getF12e() == 0 && !menuIsCheck(0xF6) &&
            !menuIsCheck(0x100) && gBingo.f13c == 0xDAE0) {
            winSpriteSetDisp(sp, true);
        }
        break;
    case 0x8E5: case 0x8E6: case 0x8E7: case 0x8E8:
        winSpriteSetDisp(sp, false);
        if (gBingo.f144 == 13 && gBingo.f13c == 0xDB0A) {
            winSpriteSetDisp(sp, true);
        }
        break;
    }
    return 0;
}

s32 menuBingoPanelDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    u32 n = 0;
    u32 first = 0;
    switch (sp->id) {
    case 0x544: case 0x545: case 0x546: case 0x547: case 0x548: case 0x549: case 0x54A: case 0x54B: case 0x54C:
        winSpriteSetDisp(sp, false);
        if (!sheetCleared(gBingo.sheet)) {
            winSpriteSetDisp(sp, true);
        }
        break;
    case 0x862: case 0x863: case 0x864: case 0x865: case 0x866: case 0x867: case 0x868: case 0x869: case 0x86A: {
        winSpriteSetDisp(sp, false);
        cBingo* self = &gBingo;
        if (sheetCleared(self->sheet)) {
            if (!sheetClearedPlus(self->sheet)) {
                winSpriteSetDisp(sp, true);
            }
        }
        break;
    }
    case 0x86B: case 0x86C: case 0x86D: case 0x86E: case 0x86F: case 0x870: case 0x871: case 0x872: case 0x873: {
        winSpriteSetDisp(sp, false);
        cBingo* self = &gBingo;
        if (sheetCleared(self->sheet)) {
            if (sheetClearedPlus(self->sheet)) {
                winSpriteSetDisp(sp, true);
            }
        }
        break;
    }
    case 0x55E:
        if (gBingo.pkmState() == 1 && gBingo.getF12e() == 0) {
            f32 a = 128.0f * (1.0f + sinfInline(9.424778f * gBingo.f140));
            if (a > 255.0f) a = 255.0f;
            if (a < 0.0f) a = 0.0f;
            w->cursorSprites->alpha = (u8)a;
        } else {
            w->cursorSprites->alpha = 0;
        }
        break;
    case 0x58F: case 0x590: case 0x591:
        n++;
    case 0x592: case 0x593: case 0x594:
        n++;
    case 0x595: case 0x596: case 0x597:
        n++;
    case 0x598: case 0x599: case 0x59A:
        n++;
    case 0x59B: case 0x59C: case 0x59D:
        n++;
    case 0x59E: case 0x59F: case 0x5A0:
        n++;
    case 0x5A1: case 0x5A2: case 0x5A3:
        n++;
    case 0x5A4: case 0x5A5: case 0x5A6:
        n++;
    case 0x5A7: case 0x5A8: case 0x5A9:
        n++;
    case 0x5AA: case 0x5AB: case 0x5AC:
        winSpriteSetDisp(sp, false);
        if (gBingo.lineDone(n)) {
            if (gBingo.isChgBingoLine(n)) {
                switch (sp->id) {
                case 0x58F: case 0x592: case 0x595: case 0x598: case 0x59B:
                case 0x59E: case 0x5A1: case 0x5A4: case 0x5A7: case 0x5AA:
                    first = 1;
                }
                if (n < 4) {
                    if (first != 0) {
                        u32 now = FlashSystemGetNowFrame(0x1ECC3000);
                        s32 cmpv = FlashSystemGetEndFrame(0x1ECC3000);
                        if (cmpv != now) {
                            windowDrawSprite((s16)(n * 0x47), 0, w, 0x2E2, 0, winSpriteGetLayerID(w, sp));
                        }
                    }
                    u32 now2 = FlashSystemGetNowFrame(0x1ECC3000);
                    if (FlashSystemGetEndFrame(0x1ECC3000) - 0x23 <= now2) winSpriteSetDisp(sp, true);
                } else if (n < 8) {
                    if (first != 0) {
                        u32 now = FlashSystemGetNowFrame(0x1ECB3000);
                        u32 cmpv = FlashSystemGetEndFrame(0x1ECB3000);
                        if (cmpv != now) {
                            windowDrawSprite(0, (s16)((7 - n) * 0x44), w, 0x2E1, 0, winSpriteGetLayerID(w, sp));
                        }
                    }
                    u32 now2 = FlashSystemGetNowFrame(0x1ECB3000);
                    if (FlashSystemGetEndFrame(0x1ECB3000) - 0x23 <= now2) winSpriteSetDisp(sp, true);
                } else if (n == 8) {
                    if (first != 0) {
                        u32 now = FlashSystemGetNowFrame(0x1ECE3000);
                        s32 cmpv = FlashSystemGetEndFrame(0x1ECE3000);
                        if (cmpv != now) {
                            windowDrawSprite(0, 0, w, 0x2E4, 0, winSpriteGetLayerID(w, sp));
                        }
                    }
                    u32 now2 = FlashSystemGetNowFrame(0x1ECE3000);
                    if (FlashSystemGetEndFrame(0x1ECE3000) - 0x23 <= now2) winSpriteSetDisp(sp, true);
                } else if (n == 9) {
                    if (first != 0) {
                        u32 now = FlashSystemGetNowFrame(0x1ECD3000);
                        s32 cmpv = FlashSystemGetEndFrame(0x1ECD3000);
                        if (cmpv != now) {
                            windowDrawSprite(0, 0, w, 0x2E3, 0, winSpriteGetLayerID(w, sp));
                        }
                    }
                    u32 now2 = FlashSystemGetNowFrame(0x1ECD3000);
                    if (FlashSystemGetEndFrame(0x1ECD3000) - 0x23 <= now2) winSpriteSetDisp(sp, true);
                }
            } else {
                winSpriteSetDisp(sp, true);
            }
        } else {
            winSpriteSetDisp(sp, false);
        }
        break;
    case 0x55C:
        n++;
    case 0x55B:
        n++;
    case 0x55A:
        n++;
    case 0x559:
        n++;
    case 0x558:
        n++;
    case 0x557:
        n++;
    case 0x556:
        n++;
    case 0x555:
        n++;
    case 0x554:
        n++;
    case 0x553:
        n++;
    case 0x552:
        n++;
    case 0x551:
        n++;
    case 0x550:
        n++;
    case 0x54F:
        n++;
    case 0x54E:
        n++;
    case 0x54D:
        gBingo.dispPanel(n, w, sp);
        break;
    case 0x55D: {
        s32 layer = winSpriteGetLayerID(w, sp);
        msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(cBingo::SheetDocMsgIdx[(u8)(BIOS->getNo(gBingo.sheet) - 1)][0]));
        u16 hi = GSmsgGetRect(0x4276) >> 16;
        GSmsgPrint2(layer, (s16)((sp->w - hi) / 2), 0, -1, 0x4276);
        break;
    }
    }
    return 0;
}

s32 menuBingoScoreDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    u32 n = 0;
    switch (sp->id) {
    case 0x57B:
        n++;
    case 0x57C:
        n++;
    case 0x57D:
        n++;
    case 0x57E:
        n++;
    case 0x57F:
        n++;
    case 0x580:
        n++;
    case 0x581:
        n++;
    case 0x582:
        n++;
    case 0x583:
        n++;
    case 0x584:
        winSpriteSetDisp(sp, false);
        {
            u32 lines = gBingo.countLines();
            if (n + 1 == lines) {
                if (gBingo.isChgBingoLine(-1)) {
                    if (FlashSystemGetEndFrame(0x1F583000) != (u32)(FlashSystemGetNowFrame(0x1F583000))) {
                        windowDrawSprite(0, (10 - (n + 1)) * 0x17 + 8, w, 0x324, 0, winSpriteGetLayerID(w, sp));
                    } else {
                        winSpriteSetDisp(sp, true);
                    }
                } else {
                    winSpriteSetDisp(sp, true);
                }
            }
        }
        break;
    case 0x585:
        n++;
    case 0x586:
        n++;
    case 0x587:
        n++;
    case 0x588:
        n++;
    case 0x589:
        n++;
    case 0x58A:
        n++;
    case 0x58B:
        n++;
    case 0x58C:
        n++;
    case 0x58D:
        n++;
    case 0x58E: {
        u32 score = ((bingo_bios*)&gBingo)->getScore(gBingo.sheet, n);
        s32 layer = winSpriteGetLayerID(w, sp);
        if (gBingo.mode != 0) {
            f32 kc1436 = 1.5f;
            score = (u32)((f32)score * kc1436);
        }
        msgctrlSetValue(0x34, score);
        u32 lines = gBingo.countLines();
        if (n == lines - 1) {
            GSmsgPrintRect(layer, 0, 0, sp->w, sp->h, 0xFF, 0x4287);
        } else {
            GSmsgPrintRect(layer, 0, 0, sp->w, sp->h, -1, 0x4287);
        }
        break;
    }
    }
    return 0;
}

s32 menuBingoPkmDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    u32 k = 0;
    switch (sp->id) {
    case 0x53C:
        k++;
    case 0x53B:
        k++;
    case 0x53A:
        k++;
    case 0x539:
        gBingo.dispPkmPanel(k, w, sp);
        break;
    case 0x53F:
        k++;
    case 0x53E:
        k++;
    case 0x53D: {
        int j = findPokemonOrder(k + 2);
        winSpriteSetDisp(sp, false);
        if (j < 0) {
            int limit = hasGrid1() ? 4 : 3;
            u32 next = k;
            next += 1;
            if (next < limit) {
                if (next == 3 && limit == 4) {
                    if (gBingo.f121 != 0) {
                        winSpriteSetDisp(sp, true);
                    }
                } else {
                    winSpriteSetDisp(sp, true);
                }
            }
        }
        break;
    }
    case 0x543:
        k++;
    case 0x542:
        k++;
    case 0x541:
        k++;
    case 0x540: {
        winSpriteSetDisp(sp, false);
        int cnt = countPokemon();
        if (cnt > 1 && (u32)k == gBingo.f12c) {
            if (gBingo.pkmState() == 2) {
                f32 a = 128.0f * (1.0f + sinfInline(9.424778f * gBingo.f140));
                if (a > 255.0f) a = 255.0f;
                if (a < 0.0f) a = 0.0f;
                sp->alpha = (u8)a;
                winSpriteSetDisp(sp, true);
            }
        }
        break;
    }
    }
    return 0;
}

s32 menuBingoTopDraw(tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    static int debug = 0;
    u32 n = 0;
    winSpriteSetDisp(sp, false);
    switch (sp->id) {
    case 0x5DD:
        debug = 0;
        if (BIOS->isSelect(10)) {
            winSpriteSetDisp(sp, true);
            u8 rank = selectRank();
            sp->y = rank * 0x65 + 0x89;
        }
        break;
    case 0x5DF:
        n = 1;
    case 0x5DE:
        n += 1;
    case 0x5DC:
        n += 1;
    case 0x5DB:
        if (n <= gBingo.f128) {
            winSpriteSetDisp(sp, true);
        }
        break;
    case 0x5E0:
        if (BIOS->isSelect(10)) {
            winSpriteSetDisp(sp, true);
            u8 rank = selectRank();
            sp->y = rank * 0x65 + 0x8C;
        }
        break;
    case 0x516:
        n = 1;
    case 0x515:
        n += 1;
    case 0x514:
        n += 1;
    case 0x513:
        if (n <= gBingo.f128) {
            winSpriteSetDisp(sp, true);
        }
        break;
    case 0x694:
        n = 1;
    case 0x517:
        n += 1;
    case 0x518:
        n += 1;
    case 0x519:
        n += 1;
    case 0x51A:
        n += 1;
    case 0x51B:
        n += 1;
    case 0x51C:
        n += 1;
    case 0x51D:
        n += 1;
    case 0x51E:
        n += 1;
    case 0x51F:
        n += 1;
    case 0x520:
        if ((s32)n == 10) {
            if (BIOS->isSelect(10)) {
                winSpriteSetDisp(sp, true);
                u8 rank = selectRank();
                sp->y = rank * 0x65 + 0xA1;
            } else {
                winSpriteSetDisp(sp, false);
            }
        } else if (BIOS->isSelect(n)) {
            winSpriteSetDisp(sp, true);
        }
        break;
    case 0x695:
        n = 1;
    case 0x534:
        n += 1;
    case 0x533:
        n += 1;
    case 0x532:
        n += 1;
    case 0x531:
        n += 1;
    case 0x530:
        n += 1;
    case 0x52F:
        n += 1;
    case 0x52E:
        n += 1;
    case 0x52D:
        n += 1;
    case 0x52C:
        n += 1;
    case 0x52B:
        if (BIOS->isClear(n)) {
            winSpriteSetDisp(sp, true);
        }
        if ((s32)n == 10 && BIOS->isSelect(10)) {
            if (gBingo.f128 == 3) {
                sp->y = 0x16A;
            } else {
                sp->y = gBingo.f128 * 0x65 + 0xA0;
            }
        }
        break;
    case 0x861:
        n = 1;
    case 0x860:
        n += 1;
    case 0x85F:
        n += 1;
    case 0x85E:
        n += 1;
    case 0x85D:
        n += 1;
    case 0x85C:
        n += 1;
    case 0x85B:
        n += 1;
    case 0x85A:
        n += 1;
    case 0x859:
        n += 1;
    case 0x858:
        n += 1;
    case 0x857:
        if (BIOS->isClearPlus(n)) {
            winSpriteSetDisp(sp, true);
        }
        if ((s32)n == 10 && BIOS->isSelect(10)) {
            if (gBingo.f128 == 3) {
                sp->y = 0x16A;
            } else {
                sp->y = gBingo.f128 * 0x65 + 0xA0;
            }
        }
        break;
    }
    return 0;
}

static inline void stepAdvance() {
    gBingo.f144 += 1;
    if (gBingo.f144 >= 12) gBingo.f144 = 0;
    gBingo.f124 = -1;
}

static inline void stepAdvanceSe(tagWINDOW_WORK* w) {
    gBingo.f144 += 1;
    if (gBingo.f144 >= 12) gBingo.f144 = 0;
    gBingo.f124 = -1;
    if (w) menuPlaySe(w->menuID, 2);
}

static inline bool isOpenPanel(int i) {
    return gBingo.panel[i].flag != 0 ? true : false;
}

static inline bool canMoveAt(int pos) {
    if (gBingo.mode != 0) {
        int col = gBingo.f134 % 4;
        int row = gBingo.f134 / 4;
        if ((u32)(gBingo.f134 - 4) == pos && row - 1 >= 0) {
            return gBingo.flagAt(pos) == 0;
        }
        if ((u32)(gBingo.f134 + 4) == pos && row + 1 <= 3) {
            return gBingo.flagAt(pos) == 0;
        }
        if ((u32)(gBingo.f134 - 1) == pos && col - 1 >= 0) {
            return gBingo.flagAt(pos) == 0;
        }
        if ((u32)(gBingo.f134 + 1) == pos && col + 1 <= 3) {
            return gBingo.flagAt(pos) == 0;
        }
    } else {
        int pcol = pos % 4;
        int prow = pos / 4;
        if (prow - 1 >= 0 && gBingo.flagAt(pos - 4) != 0) {
            return true;
        }
        if (prow + 1 <= 3 && gBingo.flagAt(pos + 4) != 0) {
            return true;
        }
        if (pcol - 1 >= 0 && gBingo.flagAt(pos - 1) != 0) {
            return true;
        }
        if (pcol + 1 <= 3 && gBingo.flagAt(pos + 1) != 0) {
            return true;
        }
    }
    return gBingo.noPanelFlagged();
}

static inline void applyFlags() {
    for (u32 a = 0; a < countPokemon(); a++) {
        BingoPokemon* p1 = &mPokemon[findPokemonNo(a)];
        p1->point += mPokemon[findPokemonNo(a)].flag;
        mPokemon[findPokemonNo(a)].flag = 0;
    }
}

static inline void clearFlags() {
    for (u32 a = 0; a < countPokemon(); a++) {
        mPokemon[findPokemonNo(a)].flag = 0;
    }
}

static inline void setPos(int c) {
    gBingo.f138 = gBingo.f134;
    gBingo.f134 = (u8)c;
}

static inline void refreshLines() {
    int i;
    u32 cnt;
    for (i = cnt = 0; i < 10; i++) {
        bool d = gBingo.lineDone(i);
        if (d) cnt++;
        gBingo.lineState[i] = d;
        gBingo.lineFlag[i] = 0;
    }
    gBingo.f12d = cnt;
}

static inline bool canMoveAny() {
    s32 i;
    if (gBingo.mode == 0) return true;
    for (i = 0; i < 16; i++) {
        if (canMoveAt(i)) return true;
    }
    return false;
}

inline int cBingo::newLines() {
    int base = f12d;
    int cnt = countLines();
    return cnt - base;
}

inline void cBingo::playLineSe() {
    if (newLines() != 0) {
        GSsndPlayNow(0x575);
    } else {
        GSsndPlayNow(0x574);
    }
}

static inline int openPanel(BingoPanel* panels, int c) {
    if (isOpenPanel(c)) return -1;
    if (panels[c].state != 0) {
        switch (BIOS->getGridGrid(gBingo.sheet, gBingo.panel[c].idx)) {
        case 0:
            break;
        case 1:
            gBingo.ball++;
            bingo_bios::setStaticBall(gBingo.ball);
            break;
        case 2:
            gBingo.epoint += 1;
            break;
        case 3:
            gBingo.epoint += 2;
            break;
        }
        return 1;
    }
    return 0;
}

s32 menuBingoSheetBtn(tagWINDOW_WORK* w) {
    u16 rep = windowGetKeyRepeat();
    u16 trg = windowGetKeyTrg();
    if (gBingo.f108 != 0) return 0;
    switch (gBingo.f144) {
    case 0: {
        gBingo.f130 = 0;
        int pos = gBingo.f134;
        if (gBingo.panel[pos].state == 0) {
            gBingo.f10c = 1;
            u8 pidx = gBingo.panel[pos].idx;
            u32 sel = gBingo.f12c;
            bingo_bios::setStaticIdx(findPokemonOrder(sel + 1), pidx);
            bingo_bios::setStaticBall(gBingo.ball);
        }
        stepAdvanceSe(w);
        break;
    }
    case 1: {
        if (gBingo.f10c != 0) break;
        if (winSeqCheckMove(0xC8)) break;
        cBingo* self = &gBingo;
        BingoPanel* panels = self->panel;
        if (panels[self->f134].state != 0 && self->f130 != 3 && self->f130 != 4) {
            switch (openPanel(panels, w->cursor)) {
            case 0:
                gBingo.f10c = 1;
                u8 pidx = gBingo.panel[self->f134].idx;
                u32 sel = gBingo.f12c;
                bingo_bios::setStaticIdx(findPokemonOrder(sel + 1), pidx);
                bingo_bios::setStaticBall(gBingo.ball);
                stepAdvanceSe(w);
                break;
            case 1:
                gBingo.setFlagAt(self->f134, 1);
                gBingo.f144 = gBingo.f144 + 1;
                if (gBingo.f144 >= 12) gBingo.f144 = 0;
                gBingo.f124 = -1;
                break;
            case -1:
                stepAdvanceSe(w);
                break;
            default:
                menuPlaySe(w->menuID, 3);
                break;
            }
            gBingo.playLineSe();
        } else {
            if (gBingo.f130 == 0) break;
            if (gBingo.f130 == 2) {
                u8 b = gBingo.ball;
                if (b == bingo_bios::getStaticBall()) {
                    gBingo.setFlagAt(self->f134, 1);
                } else {
                    gBingo.setFlagAt(self->f134, 1);
                    u8 idx = gBingo.panel[self->f134].idx;
                    mPokemon[gBingo.panel[self->f134].idx].order = countPokemon() + 1;
                    mPokemon[idx].point = 2;
                    mPokemon[idx].flag = 0;
                }
                gBingo.playLineSe();
                stepAdvance();
            } else {
                stepAdvanceSe(w);
            }
        }
        break;
    }
    case 2: {
        if (!(trg & 0x10)) break;
        int n = (u8)gBingo.countLines();
        gBingo.ball = bingo_bios::getStaticBall();
        if (n == 10) {
            int d = n - gBingo.f12d;
            gBingo.f108 = 2;
            gBingo.epoint += (u8)d;
            break;
        }
        stepAdvanceSe(w);
        break;
    }
    case 3: {
        u32 cnt = gBingo.countLines();
        int n = (u8)cnt;
        if (n == 10) {
            gBingo.f108 = 2;
            n -= gBingo.f12d;
            gBingo.epoint += (u8)n;
            break;
        }
        n -= gBingo.f12d;
        gBingo.f12f = gBingo.epoint;
        if (n == 0) {
            stepAdvance();
            break;
        }
        if (!(trg & 0x10)) break;
        gBingo.epoint += (u8)n;
        gBingo.f12f = gBingo.epoint;
        stepAdvanceSe(w);
        break;
    }
    case 4: {
        u16 rf_t = gBingo.f12d;
        int base = rf_t;
        int cnt = gBingo.countLines();
        if (cnt - base == 0) {
            if (gBingo.epoint != 0) {
                stepAdvance();
            } else {
                gBingo.f144 = 7;
                gBingo.f124 = -1;
            }
        }
        if (!(trg & 0x10)) break;
        stepAdvanceSe(w);
        break;
    }
    case 5: {
        if (gBingo.epoint == 0) {
            stepAdvance();
            break;
        }
        int cnt = countPokemon();
        if (trg & 0x10) {
            gBingo.f124 = -2;
        } else if (rep & 1) {
            if (gBingo.f12c != 0) {
                gBingo.f12c = gBingo.f12c - 1;
                menuPlaySe(w->menuID, 1);
            }
        } else if (rep & 2) {
            if (gBingo.f12c < cnt - 1) {
                gBingo.f12c = gBingo.f12c + 1;
                menuPlaySe(w->menuID, 1);
            }
        }
        switch (gBingo.f124 - 1) {
        case 0: {
            int j = findPokemonNo(gBingo.f12c);
            if (j >= 0) {
                mPokemon[j].flag += 1;
                if (gBingo.epoint != 0) gBingo.epoint -= 1;
            }
            gBingo.f124 = -1;
            if (gBingo.epoint == 0) {
                stepAdvance();
            }
            break;
        }
        case -1:
        case 1:
            gBingo.f124 = -1;
            break;
        }
        break;
    }
    case 6: {
        u8 t = gBingo.f12f;
        if (t != 0) {
            switch (gBingo.f124 - 1) {
            case 0: {
                applyFlags();
                stepAdvance();
                break;
            }
            case -1:
            case 1:
                gBingo.epoint = t;
                clearFlags();
                gBingo.f144 = 5;
                gBingo.f124 = -1;
                break;
            }
        } else {
            stepAdvance();
        }
        break;
    }
    case 7: {
        if (sumPoints() == 0 || !canMoveAny()) {
            gBingo.f13c = 0;
            gBingo.f108 = 1;
            break;
        }
        if (trg & 0x10) {
            int c = w->cursor;
            if (gBingo.canMove(c)) {
                if (gBingo.panel[c].flag == 0) {
                    stepAdvanceSe(w);
                }
            }
        } else if (trg & 0x20) {
            menuPlaySe(w->menuID, 3);
            gBingo.f12e = 1;
        }
        break;
    }
    case 8: {
        int cnt = countPokemon();
        if (cnt < 2 || (trg & 0x10)) {
            stepAdvance();
            if (cnt >= 2) menuPlaySe(w->menuID, 2);
        } else if (trg & 0x20) {
            gBingo.f144 = 7;
            gBingo.f124 = -1;
        } else if (rep & 1) {
            if (gBingo.f12c != 0) {
                menuPlaySe(w->menuID, 1);
                gBingo.f12c = gBingo.f12c - 1;
            }
        } else if (rep & 2) {
            if (gBingo.f12c < cnt - 1) {
                menuPlaySe(w->menuID, 1);
                gBingo.f12c = gBingo.f12c + 1;
            }
        }
        break;
    }
    case 9:
        switch (gBingo.f124 - 1) {
        case 0:
            stepAdvance();
            break;
        case 1:
            gBingo.f144 = 11;
            gBingo.f124 = -1;
            break;
        case -1:
        case 2:
            gBingo.f144 = 7;
            gBingo.f124 = -1;
            break;
        }
        break;
    case 10: {
        if (pokemonNo(gBingo.f12c)->point != 0) {
            switch (gBingo.f124 - 1) {
            case 0: {
                int j = findPokemonNo(gBingo.f12c);
                if (j >= 0) {
                    if (mPokemon[j].point != 0) mPokemon[j].point--;
                }
                setPos(w->cursor);
                refreshLines();
                gBingo.f144 = 0;
                gBingo.f124 = -1;
                break;
            }
            case -1:
            case 1:
                gBingo.f144 = 7;
                gBingo.f124 = -1;
                break;
            }
        } else if (trg & 0x30) {
            gBingo.f144 = 7;
            gBingo.f124 = -1;
        }
        break;
    }
    case 11:
    case 12:
        break;
    }
    return 0;
}

s32 menuBingoSheetCur(tagWINDOW_WORK* w) {
    menuSpriteBiosGetPtr(0x27F);
    if (gBingo.f144 != 7 || gBingo.getF12e() != 0) {
        return 0;
    }
    if (gBingo.f108 != 0) {
        return 0;
    }
    int pos = w->cursor;
    u16 rep = windowGetKeyRepeat();
    if (rep & 1) {
        pos -= 4;
    } else if (rep & 2) {
        pos += 4;
    } else if (rep & 4) {
        pos -= 1;
    } else if (rep & 8) {
        pos += 1;
    }
    if (gBingo.canMove(pos) || gBingo.flagAt(pos) != 0 || gBingo.noPanelFlagged()) {
        menuCursorNormal(w, 1);
    }
    return 0;
}

s32 menuBingoSheetCtrl(tagWINDOW_WORK* w) {
    u32 group = floorGetCurrentGroupID();
    if (group == (u32)fn_80091B98()) {
        switch (w->state) {
        case 2:
            if (fadeCheck(0)) {
                if (fadeGetType() != 3 && gBingo.f10c != 0 && menuIsCheck(0xC8)) {
                    menuClose(0xC8);
                }
            } else {
                tagWINDOW_WORK* sub = windowSearchID(0xAE);
                if (sub) {
                    u32* alloc = windowGetAllocPtr(sub);
                    s32 n = windowGetParam(sub, 2);
                    u8 same = 1;
                    for (s8 i = 0; i < n; i++) {
                        if (alloc[i] != cBingo::MenuBingoMsgIdx[i]) {
                            same = 0;
                            break;
                        }
                    }
                    if (same == 1) {
                        CursorPos c = *(CursorPos*)&sub->top;
                        if (c.pos == 0) {
                            gBingo.mode = 0;
                        } else {
                            gBingo.mode = 1;
                        }
                    }
                }
            }
            break;
        }
    } else {
        switch (w->state) {
        case 0:
            if (w->seqSet == 0) {
                winSeqSetMenu(w->menuID, 0x1B1);
                w->seqSet = 1;
            }
            break;
        case 3:
            if (w->seqSet == 0) {
                winSeqSetMenu(w->menuID, 0x1B7);
                w->seqSet = 1;
            }
            break;
        }
    }
    return 0;
}

s32 fn_80091B98(void) {
    switch (pokecoloGetLanguage()) {
    case 2:
        return 0x8CF;
    case 3:
        return 0xA9E;
    case 4:
        return 0xA9F;
    case 5:
        return 0xAA0;
    case 6:
        return 0xAA1;
    default:
        return 0x8CF;
    }
}

s32 fn_80091C10(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x132);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x136);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 fn_80091CA8(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x132);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x136);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 fn_80091D40(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x132);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x136);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

s32 fn_80091DD8(tagWINDOW_WORK* w) {
    switch (w->state) {
    case 0:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x132);
            w->seqSet = 1;
        }
        break;
    case 3:
        if (w->seqSet == 0) {
            winSeqSetMenu(w->menuID, 0x136);
            w->seqSet = 1;
        }
        break;
    }
    return 0;
}

void menuBingoExit(void) {}

static inline void waitFlash(const char* s, const char* e) {
    u32 a = FlashSystemGetFrameFromLabel(0x1F573000, s);
    u32 b = FlashSystemGetFrameFromLabel(0x1F573000, e);
    while (a != b) {
        GSthreadSwitch();
        a = FlashSystemGetNowFrame(0x1F573000);
    }
}

void menuBingoMain(void) {
    u32 again = 1;
    int ok = 0;
    int res;
    int st;
    u32 cmpv = GSfloorGetCurrent();
    if (cmpv != 0x388) {
        res = gBingo.f134;
        menuOpenCustom(0xC8, 0, &res, 2, 0, 0);
        while (windowGetKeyInfo()->trg != 0x20) {
            GSthreadSwitch();
        }
        menuClose(0xC8);
        menuCloseSync(0xC8, 1);
        menuOffScreenSetPriority(1);
        GSfloorPop();
        floorSetFadeScript(0, 0);
        return;
    }
    res = 0;
    s32* pos = &gBingo.f134;
    while ((u8)again) {
        gBingo.f138 = 0;
        gBingo.f134 = 0;
        gBingo.f12c = 0;
        gBingo.f12b = 0;
        gBingo.ball = 0;
        gBingo.f12f = 0;
        gBingo.epoint = 0;
        gBingo.f12e = 0;
        gBingo.f124 = -1;
        gBingo.f10c = 0;
        gBingo.f108 = 0;
        gBingo.f144 = 13;
        gBingo.f140 = 0.0f;
        gBingo.f128 = BIOS->getClearLv();
        if (GSflagGet(0x4F2) >= 6) {
            bingo_bios::setSelect(10);
        }
        for (int i = 0; i < *bingo_data_number; i++) {
            if (BIOS->isSelect(i)) {
                menuItemBiosSetSelectFlag(0xC3, cBingo::TopCurIdx[i], 1);
            } else {
                menuItemBiosSetSelectFlag(0xC3, cBingo::TopCurIdx[i], 0);
            }
            if (cBingo::TopCurIdx[i] == 0x693) {
                if (BIOS->isSelect(10)) {
                    MenuItemX* m = (MenuItemX*)menuItemBiosGetPtr(0xC3, cBingo::TopCurIdx[i]);
                    u8 k;
                    if (BIOS->isSelect(8)) {
                        k = 2;
                    } else if (BIOS->isSelect(5)) {
                        k = 1;
                    } else {
                        k = 0;
                    }
                    m->x = k * 0x65 + 0x9C;
                }
            }
        }
        fadeSet(2, 0.25f);
        FlashSystemSetNowFrameLabel(0x1EC93000, "start");
        FlashSystemSetPlayFrameLabel(0x1EC93000, "start", "select");
        menuOpen(0xDC, 0);
        res = menuOpenCustom(0xC3, 0, &res, 0, 1, 0);
        FlashSystemSetPlayFrameLabel(0x1EC93000, "select", "panel");
        if (res < 0) {
            gBingo.ball = 0;
            gBingo.epoint = 0;
            bingo_bios::setStaticNo(0xFF);
            bingo_bios::setStaticBall(0);
            bingo_bios::setStaticResult(0);
            bingo_bios::setStaticIdx(0, 0);
            GSfloorPop();
            return;
        }
        gBingo.SetupSheet(res);
        fadeCheck(1);
        while (FlashSystemGetNowFrame(0x1EC93000) != FlashSystemGetFrameFromLabel(0x1EC93000, "panel")) {
            GSthreadSwitch();
        }
        menuClose(0xC3);
        menuCloseSync(0xC3, 1);
        while (menuFaceCheckLoading()) {
            GSthreadSwitch();
        }
        menuOpen(0xDC, 0);
        menuOpen(0xC7, 0);
        menuOpen(0xC9, 0);
        menuOpen(0xCA, 0);
        menuOpenCustom(0xC8, 0, &gBingo.f134, 0, 0, 0);
        winSeqSetMenu(0xC7, 0x1A5);
        winSeqSetMenu(0xC9, 0x1A9);
        winSeqSetMenu(0xC8, 0x1AD);
        FlashSystemSetNowFrameLabel(0x1EC93000, "panel");
        GSthreadSwitch();
        while (winSeqCheckMove(0xC8)) {
            GSthreadSwitch();
        }
        for (;;) {
            gBingo.f13c = 0xDB0A;
            GSthreadSwitch();
            ok = 0;
            if (windowGetKeyInfo()->trg & 0x10) {
                ok = 1;
                break;
            } else if (windowGetKeyInfo()->trg & 0x20) {
                ok = 0;
                break;
            } else if (windowGetKeyInfo()->trg & 0x200) {
                ok = -1;
            } else if (windowGetKeyInfo()->trg & 0x400) {
                ok = 1;
            }
            if (ok == 0) continue;
            fadeSet(3, 0.125f);
            fadeCheck(1);
            menuClose(0xDC);
            menuClose(0xC7);
            menuClose(0xC9);
            menuClose(0xCA);
            menuCloseCustom(0xC8, 0, 0);
            if (ok < 0) {
                u8 cur = BIOS->getNo(gBingo.sheet);
                cur -= 1;
                u32 idx;
                do {
                    if (cur != 0) {
                        --cur;
                    } else {
                        cur = 10;
                    }
                    idx = cur;
                } while (!BIOS->isSelect(idx));
                gBingo.SetupSheet(idx);
            } else {
                u8 cur = BIOS->getNo(gBingo.sheet);
                cur -= 1;
                u32 idx;
                do {
                    if (cur < 10) {
                        ++cur;
                    } else {
                        cur = 0;
                    }
                    idx = cur;
                } while (!BIOS->isSelect(idx));
                gBingo.SetupSheet(idx);
            }
            menuOpen(0xDC, 0);
            menuOpen(0xC7, 0);
            menuOpen(0xC9, 0);
            menuOpen(0xCA, 0);
            menuOpenCustom(0xC8, 0, (s32)pos, 0, 0, 0);
            winSeqSetMenu(0xC7, 0x1A5);
            winSeqSetMenu(0xC9, 0x1A9);
            winSeqSetMenu(0xC8, 0x1AD);
            FlashSystemSetNowFrameLabel(0x1EC93000, "panel");
            GSthreadSwitch();
            while (winSeqCheckMove(0xC8)) {
                GSthreadSwitch();
            }
            fadeSet(2, 0.125f);
            fadeCheck(1);
        }
        if (ok != 0) {
            gBingo.f144 = 14;
            gBingo.f124 = -1;
            gBingo.f13c = 0xDADE;
            if ((s8)menuSubOpenYesNo(0, 0x1BD, 0x104, 0) == 0) {
                if (sheetCleared(gBingo.sheet)) {
                    u32 msg = 0xDADF;
                    while (windowGetKeyInfo()->trg != 0x10) {
                        gBingo.f13c = msg;
                        GSthreadSwitch();
                    }
                    gBingo.makeRandomSheet();
                }
                gBingo.mode = 0;
                again = clearCount();
                if (again == 10) {
                    gBingo.f13c = 0xDB33;
                    if (menuSubOpenSelect3(0, (s32*)cBingo::MenuBingoMsgIdx, 2, 0x28, 0x12C, 0, 2, 0, 0) == 1) {
                        gBingo.mode = 1;
                    }
                }
                again = 0;
            } else {
                ok = 0;
            }
        }
        if (ok == 0) {
            menuClose(0xDC);
            menuClose(0xC7);
            menuClose(0xC9);
            menuClose(0xCA);
            menuCloseCustom(0xC8, 0, 0);
        }
    }
    if (ok != 0) {
        ok = 1;
        while ((u8)ok) {
            gBingo.f144 = 7;
            gBingo.f124 = -1;
            do {
                GSthreadSwitch();
                gBingo.setStepMessage();
                if (windowGetKeyInfo()->trg & 0x40) {
                    GSthreadSwitch();
                    menuOpen(0xF6, 0);
                    while (!(windowGetKeyInfo()->trg & 0xF0)) {
                        GSthreadSwitch();
                    }
                    menuClose(0xF6);
                    menuCloseSync(0xF6, 1);
                } else if (windowGetKeyInfo()->trg & 0x80) {
                    GSthreadSwitch();
                    menuOpen(0x100, 0);
                    while (!(windowGetKeyInfo()->trg & 0xF0)) {
                        GSthreadSwitch();
                    }
                    menuClose(0x100);
                    menuCloseSync(0x100, 1);
                }
                st = gBingo.f108;
            } while (st == 0);
            gBingo.f13c = 0;
            gBingo.f144 = 14;
            gBingo.f124 = -1;
            switch (st) {
            case 3:
                if (sheetCleared(gBingo.sheet)) {
                    if ((int)gBingo.countLines() < 2) {
                        gBingo.f13c = 0xDAFA;
                    } else {
                        gBingo.f13c = 0xDB3B;
                    }
                    GSthreadSwitch();
                    if ((s8)menuSubOpenYesNo(0, 0x1BD, 0x104, 0) != 0) {
                        ok = 0;
                    } else {
                        ok = 1;
                        { u8 no = BIOS->getNo(gBingo.sheet); gBingo.ResetSheet(no); }
                    }
                } else {
                    ok = 0;
                }
                break;
            case 2:
                GSsndPlayNow(0x5B6);
                FlashSystemSetNowFrameLabel(0x1F573000, "clear_start");
                FlashSystemSetPlayFrameLabel(0x1F573000, "clear_start", "clear_end");
                FlashSystemSetNowFrameLabel(0x1F573000, "clear_start");
                FlashSystemSetPlayFrameLabel(0x1F573000, "clear_start", "clear_end");
                menuOpen(0xF8, 0);
                menuSetPosition(0xF8, 0, 0);
                waitFlash("clear_start", "clear_end");
                menuClose(0xF8);
                {
                    u32 msg = 0xDAF8;
                    while (windowGetKeyInfo()->trg != 0x10) {
                        gBingo.f13c = msg;
                        GSthreadSwitch();
                    }
                }
                if (gBingo.mode != 0) {
                    u8 no = BIOS->getNo(gBingo.sheet);
                    BIOS->setClearPlus(no - 1);
                } else {
                    u8 no = BIOS->getNo(gBingo.sheet);
                    BIOS->setClear(no - 1);
                }
                ok = 0;
                break;
            case 1:
                while (windowGetKeyInfo()->trg != 0x10) {
                    if (gBingo.mode != 0) {
                        if (!canMoveAny()) {
                            gBingo.f13c = 0xDB37;
                        } else {
                            gBingo.f13c = 0xDAF9;
                        }
                    } else {
                        gBingo.f13c = 0xDAF9;
                    }
                    GSthreadSwitch();
                }
                if (sheetCleared(gBingo.sheet)) {
                    if ((int)gBingo.countLines() < 2) {
                        gBingo.f13c = 0xDAFA;
                    } else {
                        gBingo.f13c = 0xDB3B;
                    }
                    GSthreadSwitch();
                    if ((s8)menuSubOpenYesNo(0, 0x1BD, 0x104, 0) != 0) {
                        ok = 0;
                    } else {
                        ok = 1;
                        { u8 no = BIOS->getNo(gBingo.sheet); gBingo.ResetSheet(no); }
                    }
                } else {
                    ok = 0;
                }
                break;
            }
        }
        fadeSet(3, 0.125f);
        fadeCheck(1);
        menuClose(0xDC);
        menuClose(0xC7);
        menuClose(0xC9);
        menuClose(0xCA);
        menuCloseCustom(0xC8, 0, 0);
        menuClose(0xDC);
    }
    {
        u8 n = gBingo.countLines();
        switch (st) {
        case 1:
            break;
        case 2:
            n |= (u8)0x10;
            break;
        case 3:
            n |= (u8)0x20;
            break;
        }
        bingo_bios::setStaticResult(n);
    }
    GSfloorPop();
}

void menuBingoInit(void) {
    if ((u32)GSfloorGetCurrent() == 0x388) {
        gBingo.save = (u32)savedataGetStatus(0, 0x1B);
    }
}

}

static inline bool pkmSame(u8 prev) {
    int c = countPokemon();
    return c == prev;
}

void cBingo::setStepMessage() {
    f13c = 0;
    if (f108 != 0) return;
    switch (f144) {
    case 1: {
        f148 = countPokemon();
        if (panel[f134].state != 0) {
            int g = -1;
            if (panel[f134].state != 0) g = ((bingo_bios*)this)->getGridGrid(sheet, panel[f134].idx);
            if (g != 1) break;
            if (f124 == 0) break;
            f13c = 0xDAEA;
            f130 = 0;
            bool open = panel[f134].flag != 0 ? true : false;
            if (!open && panel[f134].state != 0) {
                switch (((bingo_bios*)this)->getGridGrid(sheet, panel[f134].idx)) {
                case 0:
                    break;
                case 1:
                    ball++;
                    bingo_bios::setStaticBall(ball);
                    break;
                case 2:
                    epoint += 1;
                    break;
                case 3:
                    epoint += 2;
                    break;
                }
            }
            setFlagAt(f134, 1);
            playLineSe();
            while (0.0 < panel[f134].scale) {
                GSthreadSwitch();
            }
            FlashSystemSetNowFrameLabel(0x1F573000, "ball_start");
            FlashSystemSetPlayFrameLabel(0x1F573000, "ball_start", "ball_end");
            menuOpen(0xFB, 0);
            menuSetPosition(0xFB, 0, 0);
            waitFlash("ball_start", "ball_end");
            menuClose(0xFB);
            f121 = 1;
        } else {
            if (f10c == 0) break;
            int r = fightEncount(0xC);
            f130 = r;
            switch (r) {
            case 3:
            case 4:
                menuOpen(0xDC, 0);
                menuOpen(0xC7, 0);
                menuOpen(0xC9, 0);
                menuOpen(0xCA, 0);
                if (!noPanelFlagged()) {
                    s32 tmp = f138;
                    f138 = f134;
                    f134 = tmp;
                } else {
                    f138 = f134;
                }
                menuOpenCustom(0xC8, 0, &f134, 0, 0, 0);
                winSeqSetMenu(0xC7, 0x1A5);
                winSeqSetMenu(0xC9, 0x1A9);
                winSeqSetMenu(0xC8, 0x1AD);
                FlashSystemSetNowFrameLabel(0x1EC93000, "panel");
                GSthreadSwitch();
                while (winSeqCheckMove(0xC8)) {
                    GSthreadSwitch();
                }
                break;
            default:
                menuOpen(0xDC, 0);
                menuOpen(0xC7, 0);
                menuOpen(0xC9, 0);
                menuOpen(0xCA, 0);
                menuOpenCustom(0xC8, 0, &f134, 0, 0, 0);
                winSeqSetMenu(0xC7, 0x1A5);
                winSeqSetMenu(0xC9, 0x1A9);
                winSeqSetMenu(0xC8, 0x1AD);
                FlashSystemSetNowFrameLabel(0x1EC93000, "panel");
                GSthreadSwitch();
                while (winSeqCheckMove(0xC8)) {
                    GSthreadSwitch();
                }
                break;
            }
            f144 = 1;
            f10c = 0;
        }
        break;
    }
    case 2:
        if (panel[f134].state == 0) {
            switch (f130) {
            case 3:
            case 4:
                f13c = 0xDAF4;
                break;
            case 2: {
                u8 b = ball;
                if (b == bingo_bios::getStaticBall()) {
                    f13c = 0xDAF3;
                } else {
                    f13c = 0xDB22;
                }
                break;
            }
            }
        } else {
            switch (f130) {
            case 3:
            case 4:
                f13c = 0xDAF4;
                break;
            default:
                f13c = 0xDAEA;
                break;
            }
        }
        break;
    case 3: {
        int d = newLines();
        if (d != 0) {
            switch (d) {
            case 1:
                f13c = 0xDAF5;
                break;
            case 2:
            case 3:
                f13c = 0xDAF6;
                break;
            }
        }
        GSthreadSwitch();
        if (pkmSame(f148)) break;
        for (int i = 0; i < 16; i++) {
            if (panel[i].scale > 0.0f && stateAt(i) == 0 && flagAt(i) != 0) {
                while (panel[i].scale > 0.0f) {
                    GSthreadSwitch();
                }
                MenuItemX* m = (MenuItemX*)menuItemBiosGetPtr(0xFA, 0x7FF);
                int k = countPokemon();
                m->x = (k - 2) * 0x50;
                FlashSystemSetNowFrameLabel(0x1F573000, "poke2_start");
                FlashSystemSetPlayFrameLabel(0x1F573000, "poke2_start", "poke2_end");
                menuOpen(0xFA, 0);
                menuSetPosition(0xFA, 0, 0);
                waitFlash("poke2_start", "poke2_end");
                menuClose(0xFA);
            }
        }
        break;
    }
    case 4:
        if (newLines() != 0) f13c = 0xDAF7;
        break;
    case 5: {
        if (epoint == 0) break;
        f13c = 0xDAEE;
        if (f124 == -2) {
            GSthreadSwitch();
            int r = menuSubOpenSelect2(0, (s32*)MenuEpMsgIdx, 2, 0x1BD, 0x104, 0, 2, 0);
            if (r == 0) {
                MenuItemX* m = (MenuItemX*)menuItemBiosGetPtr(0xF9, 0x7FD);
                m->x = f12c * 0x50;
                FlashSystemSetNowFrameLabel(0x1F573000, "ep1_start");
                FlashSystemSetPlayFrameLabel(0x1F573000, "ep1_start", "ep1_end");
                menuOpen(0xF9, 0);
                menuSetPosition(0xF9, 0, 0);
                waitFlash("ep1_start", "ep1_end");
                menuClose(0xF9);
            }
            f124 = r + 1;
        }
        break;
    }
    case 6:
        if (f12f == 0) break;
        f13c = 0xDB23;
        if (f124 == -1) {
            GSthreadSwitch();
            f124 = (s8)menuSubOpenYesNo(0, 0x1BD, 0x104, 0) + 1;
        }
        break;
    case 7:
        if (f108 == 1) break;
        if (getF12e() == 1) {
            f13c = 0xDAE1;
            GSthreadSwitch();
            switch ((s8)menuSubOpenYesNo(0, 0x1BD, 0x104, 0)) {
            case 0:
                f12e = 0;
                f144 = 3;
                f124 = -1;
                f108 = 3;
                break;
            default:
                f12e = 0;
                break;
            }
        } else {
            f13c = 0xDAE0;
        }
        break;
    case 8: {
        int cnt = countPokemon();
        if (cnt > 1) {
            f13c = 0xDAE2;
        } else {
            f13c = 0xDB43;
        }
        break;
    }
    case 9:
        f13c = 0xDB43;
        GSthreadSwitch();
        f124 = menuSubOpenSelect2(0, (s32*)MenuPkmMsgIdx, 3, 0x1BD, 0x104, 0, 3, 0) + 1;
        break;
    case 10:
        if (pokemonNo(f12c)->point == 0) {
            f13c = 0xDAE6;
        } else {
            f13c = 0xDAE7;
            GSthreadSwitch();
            f124 = (s8)menuSubOpenYesNo(0, 0x1BD, 0x104, 0) + 1;
        }
        break;
    case 11:
        menuOpen(0xD1, 0);
        menuSetPosition(0xD1, 0, (s16)(f12c * 0x50));
        windowCheckCursor(0xD1, 1);
        menuClose(0xD1);
        menuCloseSync(0xD1, 1);
        f144 = 8;
        f124 = -1;
        break;
    }
}

void cBingo::dispPanel(u32 n, tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    winSpriteSetDisp(sp, false);
    if (f144 == 15) {
        dispShufflePanel(n, w, sp);
        return;
    }
    if (panel[n].flag != 0 ? true : false) {
        dispOpenPanel(n, w, sp);
    } else {
        s32 layer = winSpriteGetLayerID(w, sp);
        s16 x = 0;
        s16 y = 0;
        if (pkmState() != 1 && f144 != 13 && f144 != 14 && n == w->cursor) {
            y = -4;
            x = -4;
        }
        if (x != 0) {
            windowDrawSprite2(0, 0, 0x46, 0x43, 0x7F, w, 0x2D5, 0, layer);
        }
        if (panel[n].state != 0) {
            windowDrawSprite2(x, y, 0x46, 0x43, -1, w, 0x29E, 0, layer);
        } else {
            u16 key = faceKey(this, &panel[n], n);
            windowDrawSprite2(x, y, 0x46, 0x43, -1, w, key, 0, layer);
        }
        if (pkmState() != 1 && f144 != 13 && f144 != 14 && n != w->cursor) {
            windowDrawSprite2(x, y, 0x46, 0x43, 0x7F, w, 0x2D5, 0, layer);
        }
        panel[n].scale = 1.0f;
    }
    if (n == f134 && mode != 0 && f144 == 7) {
        if (!noPanelFlagged()) {
            spriteSetOffset(7, sp->x, sp->y);
            spriteClearScissor(7);
            spriteSetEnv(7);
            {
                int c = f134;
                if (canMove(c - 4)) {
                    windowDrawSprite(0x15, -0x10, w, 0x39A, 0, 7);
                }
            }
            {
                int c = f134;
                if (canMove(c + 4)) {
                    windowDrawSprite(0x15, 0x37, w, 0x39C, 0, 7);
                }
            }
            {
                int c = f134;
                if (canMove(c - 1)) {
                    windowDrawSprite(-0xF, 0x14, w, 0x39B, 0, 7);
                }
            }
            {
                int c = f134;
                if (canMove(c + 1)) {
                    windowDrawSprite(0x39, 0x14, w, 0x39D, 0, 7);
                }
            }
        }
    }
}

void cBingo::dispOpenPanel(u32 n, tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    s32 layer = winSpriteGetLayerID(w, sp);
    if (panel[n].scale > 0.0f) {
        f32 ang = 3.14f * panel[n].scale;
        if (panel[n].scale > 0.5f) {
            if (panel[n].state != 0) {
                f32 c = (f32)fabsInline(cosfInline(ang));
                f32 ka = -35.0f;
                s16 a = (s16)(c * ka);
                f32 kc304 = 35.0f;
                windowDrawSprite2(a + 0x23, 0, (s16)(c * kc304 - (f32)a), 0x43, -1, w, 0x29E, 0, layer);
            } else {
                int key = faceKey(this, &panel[n], n);
                f32 c = (f32)fabsInline(cosfInline(ang));
                f32 ka = -35.0f;
                s16 a = (s16)(c * ka);
                f32 kc613 = 35.0f;
                windowDrawSprite2(a + 0x23, 0, (s16)(c * kc613 - (f32)a), 0x43, -1, w, key, 0, layer);
            }
            panel[n].scale = panel[n].scale - 4.0f * timeGetLastFrameSec();
            return;
        }
        if (panel[n].state != 0) {
            u8 g = ((bingo_bios*)this)->getGridGrid(sheet, panel[n].idx);
            f32 c = (f32)fabsInline(cosfInline(ang));
            f32 ka = -35.0f;
            s16 a = (s16)(c * ka);
            f32 kpa = 35.0f;
            s16 wd = (s16)(c * kpa - (f32)a);
            switch (g) {
            case 0:
                break;
            case 1:
                windowDrawSprite2(a + 0x23, 0, wd, 0x43, -1, w, 0x281, 0, layer);
                {
                    f32 c2 = (f32)fabsInline(cosfInline(ang));
                    f32 ka2 = -19.0f;
                    s16 a2 = (s16)(c2 * ka2);
                    f32 kpa2 = 19.0f;
                    windowDrawSprite2(a2 + 0x23, 7, (s16)(c2 * kpa2 - (f32)a2), 0x26, -1, w, 0x27C, 0, layer);
                }
                break;
            case 2:
                windowDrawSprite2(a + 0x23, 0, wd, 0x43, -1, w, 0x281, 0, layer);
                {
                    f32 c2 = (f32)fabsInline(cosfInline(ang));
                    f32 ka2 = -19.0f;
                    s16 a2 = (s16)(c2 * ka2);
                    f32 kpa2 = 19.0f;
                    windowDrawSprite2(a2 + 0x23, 7, (s16)(c2 * kpa2 - (f32)a2), 0x26, -1, w, 0x27D, 0, layer);
                }
                break;
            case 3:
                windowDrawSprite2(a + 0x23, 0, wd, 0x43, -1, w, 0x282, 0, layer);
                {
                    f32 c2 = (f32)fabsInline(cosfInline(ang));
                    f32 ka2 = -19.0f;
                    s16 a2 = (s16)(c2 * ka2);
                    f32 kpa2 = 19.0f;
                    windowDrawSprite2(a2 + 0x23, 7, (s16)(c2 * kpa2 - (f32)a2), 0x26, -1, w, 0x27D, 0, layer);
                }
                break;
            }
            panel[n].scale = panel[n].scale - 4.0f * timeGetLastFrameSec();
            return;
        }
        {
            void* pd = mPokemon[panel[n].idx].pkm.getPokemonDataPtr();
            GSvec2 pos;
            pos.x = 14.0f;
            pos.y = 5.0f;
            u16 face = pokemonDataBiosGetStatusFaceMenuSpriteId(mPokemon[panel[n].idx].pkm.getPokemonDataPtr(), 0);
            u8 saved[0x78];
            memcpy(saved, sp, 0x78);
            sp->h = 0x2A;
            sp->w = 0x2A;
            if (ang > 0.0f) {
                int x0 = (int)pos.x;
                f32 c = (f32)fabsInline(cosfInline(ang));
                s16 a = x0 - 0x23;
                s16 b = a + sp->w;
                s16 xo = (s16)(c * a);
                sp->w = (s16)(c * b - xo);
                pos.x = (s16)(xo + 0x23);
            }
            menuFaceDispFromID2(w, sp, (u16)face, &pos);
            memcpy(sp, saved, 0x78);
            f32 c3 = (f32)fabsInline(cosfInline(ang));
            f32 ka3 = -35.0f;
            s16 a3 = (s16)(c3 * ka3);
            f32 kpa3 = 35.0f;
            windowDrawSprite2(a3 + 0x23, 0, (s16)(c3 * kpa3 - (f32)a3), 0x43, -1, w, 0x280, 0, layer);
            f32 c4 = (f32)fabsInline(cosfInline(ang));
            f32 ka4 = 10.0f;
            s16 a4 = (s16)(c4 * ka4);
            f32 kpa4 = 31.0f;
            windowDrawSprite2(a4 + 0x23, 0x2E, (s16)(c4 * kpa4 - (f32)a4), 0x12, -1, w,
                              OpenPanelType[wazaDB_GetZokuseiDataId(((bingo_bios*)this)->getPanelWaza(sheet, panel[n].idx))], 0, layer);
            panel[n].scale = panel[n].scale - 4.0f * timeGetLastFrameSec();
            if (panel[n].scale < 0.0f) {
                panel[n].scale = 0.0f;
                panel[n].pad = 1;
            }
        }
    } else {
        if (panel[n].state != 0) {
            switch (((bingo_bios*)this)->getGridGrid(sheet, panel[n].idx)) {
            case 0:
                break;
            case 1:
                windowDrawSprite2(0, 0, 0x46, 0x43, -1, w, 0x281, 0, layer);
                windowDrawSprite2(0x10, 7, 0x26, 0x26, -1, w, 0x27C, 0, layer);
                break;
            case 2:
                windowDrawSprite2(0, 0, 0x46, 0x43, -1, w, 0x281, 0, layer);
                windowDrawSprite2(0x10, 7, 0x26, 0x26, -1, w, 0x27D, 0, layer);
                break;
            case 3:
                windowDrawSprite2(0, 0, 0x46, 0x43, -1, w, 0x282, 0, layer);
                windowDrawSprite2(0x10, 7, 0x26, 0x26, -1, w, 0x27D, 0, layer);
                break;
            }
        } else {
            void* pd = mPokemon[panel[n].idx].pkm.getPokemonDataPtr();
            GSvec2 pos;
            pos.x = 14.0f;
            pos.y = 5.0f;
            u16 face = pokemonDataBiosGetStatusFaceMenuSpriteId(mPokemon[panel[n].idx].pkm.getPokemonDataPtr(), 0);
            u8 saved[0x78];
            memcpy(saved, sp, 0x78);
            sp->h = 0x2A;
            sp->w = 0x2A;
            menuFaceDispFromID2(w, sp, (u16)face, &pos);
            memcpy(sp, saved, 0x78);
            windowDrawSprite2(0, 0, 0x46, 0x43, -1, w, 0x280, 0, layer);
            windowDrawSprite2(0x2D, 0x2E, 0x15, 0x12, -1, w,
                              OpenPanelType[wazaDB_GetZokuseiDataId(((bingo_bios*)this)->getPanelWaza(sheet, panel[n].idx))], 0, layer);
        }
    }
}

void cBingo::dispShufflePanel(u32 n, tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    u32 off = n * 8;
    BingoPanel* q = &shuf[n];
    BingoPanel* p = &panel[n];
    f32 ang = 3.14f * shuf[n].scale;
    s32 layer = winSpriteGetLayerID(w, sp);
    if (shuf[n].scale <= 0.0f) {
        if (panel[n].state != 0) {
            windowDrawSprite2(0, 0, 0x46, 0x43, -1, w, 0x29E, 0, layer);
        } else {
            int key = faceKey(this, p, n);
            windowDrawSprite2(0, 0, 0x46, 0x43, -1, w, key, 0, layer);
        }
        panel[n].scale -= 8.0f * timeGetLastFrameSec();
        return;
    }
    if (shuf[n].scale > 0.5f) {
        if (panel[n].state != 0) {
            f32 c = (f32)fabsInline(cosfInline(ang));
            f32 ka = -35.0f;
            s16 a = (s16)(c * ka);
            f32 kc658 = 35.0f;
            windowDrawSprite2(a + 0x23, 0, (s16)(c * kc658 - (f32)a), 0x43, -1, w, 0x29E, 0, layer);
        } else {
            int key = faceKey(this, p, n);
            f32 c = (f32)fabsInline(cosfInline(ang));
            f32 ka = -35.0f;
            s16 a = (s16)(c * ka);
            f32 kc943 = 35.0f;
            windowDrawSprite2(a + 0x23, 0, (s16)(c * kc943 - (f32)a), 0x43, -1, w, key, 0, layer);
        }
        shuf[n].scale -= 8.0f * timeGetLastFrameSec();
        return;
    }
    if (shuf[n].state != 0) {
        f32 c = (f32)fabsInline(cosfInline(ang));
        f32 ka = -35.0f;
        s16 a = (s16)(c * ka);
        f32 kc1320 = 35.0f;
        windowDrawSprite2(a + 0x23, 0, (s16)(c * kc1320 - (f32)a), 0x43, -1, w, 0x29E, 0, layer);
    } else {
        int key = faceKeyShuf(this, q);
        f32 c = (f32)fabsInline(cosfInline(ang));
        f32 ka = -35.0f;
        s16 a = (s16)(c * ka);
        f32 kc1584 = 35.0f;
        windowDrawSprite2(a + 0x23, 0, (s16)(c * kc1584 - (f32)a), 0x43, -1, w, key, 0, layer);
    }
    shuf[n].scale -= 8.0f * timeGetLastFrameSec();
    if (shuf[n].scale < 0.0f) {
        panel[n] = shuf[n];
    }
}

void cBingo::dispPkmPanel(u32 n, tagWINDOW_WORK* w, tagSPRITE_WORK* sp) {
    int idx;
    s32 layer;
    int xoff = 0;
    layer = winSpriteGetLayerID(w, sp);
    idx = findPokemonOrder(n + 1);
    if (idx >= 0) {
        int cnt = countPokemon();
        lbl_804EAA00 = 0;
        switch (f144) {
        default:
            color = 0xFFFFFF00;
            break;
        case 0:
        case 1:
        case 9:
        case 10:
        case 11:
            if (n == f12c) {
                color = 0xFFFFFF00;
                lbl_804EAA00 = 6;
            } else {
                color = 0xA0A0A000;
            }
            break;
        }
        *(u32*)&sp->r = color | w->alpha;
        cnt = countPokemon();
        if (n == cnt - 1) {
            for (int i = 0; i < 16; i++) {
                if (idx == panel[i].idx && panel[i].state == 0) {
                    f32 s = panel[i].scale;
                    f32 f;
                    if (0.2f < s) {
                        f = 3.0f;
                    } else {
                        f = 5.0f * s;
                    }
                    if (f < 0.0f) f = 0.0f;
                    xoff = (s32)(-128.0f * f);
                    break;
                }
            }
        }
        xoff += lbl_804EAA00;
        GSvec2 pos;
        pos.y = 14.0f;
        pos.x = (f32)(xoff + 14);
        u16 face = pokemonDataBiosGetStatusFaceMenuSpriteId(mPokemon[idx].pkm.getPokemonDataPtr(), 0);
        u8 save[0x78];
        memcpy(save, sp, 0x78);
        sp->h = 0x2A;
        sp->w = 0x2A;
        menuFaceDispFromID2(w, sp, (u16)face, &pos);
        memcpy(sp, save, 0x78);
        windowDrawSprite2(xoff, 0, 0xB8, 0x46, color | w->alpha, w, 0x27A, 0, layer);
        u32 no = idx;
        msgctrlSetValue(0x34, mPokemon[no].point + mPokemon[no].flag);
        GSmsgPrint2(layer, xoff + 0x4F, 0x2D, color | w->alpha, 0x4271);
        msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(0xDAD6));
        GSmsgPrintRect(layer, xoff + 0x3F, 0x19, sp->w, sp->h, color | w->alpha, 0x4278);
        BingoPokemon* pk = &mPokemon[no];
        s32 tmp1 = pokemonGetStatus(pk, 0, 0x77, 0);
        msgctrlSetValue(0x37, tmp1);
        GSmsgPrintRect(layer, xoff + 0x40, 9, sp->w, sp->h, color | w->alpha, 0x4279);
        u32 sexMsg;
        u8 sex = menuSubGetPokemonSexForDisp(pk);
        switch (sex) {
        case 0:
            sexMsg = 0x9C5;
            break;
        case 1:
            sexMsg = 0x9C6;
            break;
        case 2:        default:
            sexMsg = 0;
            break;
        }
        if (sexMsg != 0) {
            msgctrlSetValue(0x37, (u32)GSmsgGetGSchar(sexMsg));
            GSmsgPrint2(layer, xoff + 0xA0, 9, color | w->alpha, 0x4278);
        }
        u32 spr = zokuseiGetPokemonSpriteID(pk->pkm.getPokemonDataPtr(), 0);
        menuSpriteBiosGetPtr(spr);
        MenuSpriteVal* val = menuSpriteBiosGetValPtr();
        if (spr != 0) {
            windowDrawSprite2((s16)(xoff + 0x66), 0x19, val->w, val->h, color | w->alpha, w, spr, 0, layer);
            if (spr != zokuseiGetPokemonSpriteID(pk->pkm.getPokemonDataPtr(), 1)) {
                menuSpriteBiosGetPtr(zokuseiGetPokemonSpriteID(pk->pkm.getPokemonDataPtr(), 1));
                MenuSpriteVal* val2 = menuSpriteBiosGetValPtr();
                windowDrawSprite2((s16)(xoff + 0x66), 0x2D, val2->w, val2->h, color | w->alpha, w,
                                  zokuseiGetPokemonSpriteID(pk->pkm.getPokemonDataPtr(), 1), 0, layer);
            }
        }
    }
}

bool cBingo::isChgBingoLine(s32 line) {
    if (line < 0) {
        for (int i = 0; i < 10; i++) {
            if (lineState[i] != lineDone(i)) {
                return 1;
            }
        }
    } else if (lineState[line] != lineDone(line)) {
        if (lineFlag[line] == 0) {
            lineFlag[line] = 1;
            FlashSystemSetNowFrame(0x1F583000, 0);
            if ((u32)line < 4) {
                FlashSystemSetNowFrame(0x1ECC3000, 0);
            } else if ((u32)line < 8) {
                FlashSystemSetNowFrame(0x1ECB3000, 0);
            } else if ((u32)line == 8) {
                FlashSystemSetNowFrame(0x1ECE3000, 0);
            } else if ((u32)line == 9) {
                FlashSystemSetNowFrame(0x1ECD3000, 0);
            }
        }
        return 1;
    }
    return 0;
}

static inline int randInt(int n) {
    return (u16)HSD_Rand() % n;
}

void cBingo::makeRandomSheet() {
    Ord16 order = kOrder;
    int i;
    for (i = 0; i < 16; i++) {
        shuf[i] = panel[i];
        shuf[i].scale = -1.0f;
    }
    for (i = 0; i < 16; i++) {
        int j = randInt(16);
        BingoPanel tmp;
        tmp = shuf[i];
        shuf[i] = shuf[j];
        shuf[j] = tmp;
    }
    f144 = 15;
    f124 = -1;
    for (i = 0; i < 16; i += 2) {
        shuf[order.v[i]].scale = 1.0f;
        while (0.0f < shuf[order.v[i]].scale) {
            f32 prev = shuf[order.v[i]].scale;
            GSthreadSwitch();
            if (0.5f < prev && shuf[order.v[i]].scale <= 0.5f) {
                shuf[order.v[i + 1]].scale = 1.0f;
            }
        }
    }
    while (0.0f < shuf[order.v[15]].scale) {
        GSthreadSwitch();
    }
    f144 = 14;
    f124 = -1;
}

static inline void setPanel(BingoPanel* p, u8 state, u8 idx, u8 flag) {
    p->state = state;
    p->idx = idx;
    p->flag = flag;
}

void cBingo::SetupSheet(u32 n) {
    u32 i = 0;
    int idx;
    switch (n) {
    case 9:
        i = 1;
    case 6:
        i += 1;
    case 3:
        if (((bingo_bios*)this)->getClearLv() < i + 1) {
            n = 10;
        }
        break;
    }
    bingo_bios::setStaticNo(n);
    sheet = bingo_bios::getStaticSheet();
    f130 = 0;
    ball = ((bingo_bios*)this)->getBall(sheet);
    f121 = 0;
    f148 = 1;
    bingo_bios::setStaticBall(ball);
    memset(&panel[0], 0, 0x80);
    for (i = 0; i < 3; i++) {
        idx = ((bingo_bios*)this)->getGridPos(sheet, i);
        setPanel(&panel[idx], 1, i, 0);
    }
    u8 level;
    u32 status;
    status = gamedataGetStatus(0, 1);
    level = ((bingo_bios*)this)->getLevel(sheet);
    pokemonCreate(&mPokemon[0], ((bingo_bios*)this)->getPanelNo(sheet, 0), level, status);
    mPokemon[0].point = 2;
    mPokemon[0].order = 1;
    mPokemon[0].flag = 0;
    for (i = idx = 0; i < 16; i++) {
        if (panel[i].state == 0) {
            idx++;
            setPanel(&panel[i], 0, idx, 0);
            ((bingo_bios*)this)->getPanelNo(sheet, idx);
            pokemonCreate(&mPokemon[idx], ((bingo_bios*)this)->getPanelNo(sheet, idx), ((bingo_bios*)this)->getLevel(sheet), gamedataGetStatus(0, 1));
            mPokemon[idx].order = mPokemon[idx].point = mPokemon[idx].flag = 0;
        }
    }
    idx = 0;
    mode = 0;
    menuFaceLoad(0, loadPkmFace, &idx);
}

void* cBingo::loadPkmFace(void* arg) {
    u32* counter = (u32*)arg;
    BingoPokemon* result = 0;
    if (*counter < 14) {
        result = &mPokemon[*counter];
    }
    (*counter)++;
    return result;
}

void cBingo::ResetSheet(u32 n) {
    s32 i;
    f108 = 0;
    f130 = 0;
    f12c = 0;
    ball = ((bingo_bios*)this)->getBall(sheet);
    f148 = 1;
    f121 = 0;
    bingo_bios::setStaticBall(ball);
    for (i = 0; i < 16; i++) {
        panel[i].flag = 0;
    }
    mPokemon[0].point = 2;
    mPokemon[0].order = 1;
    mPokemon[0].flag = 0;
    for (i = 1; i < 14; i++) {
        mPokemon[i].order = mPokemon[i].point = mPokemon[i].flag = 0;
    }
}
