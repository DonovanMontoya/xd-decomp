#ifndef GAME_BINGO_BIOS_HPP
#define GAME_BINGO_BIOS_HPP

#include <dolphin/types.h>

struct BingoSaveFlags {
    u32 sheetFlags;  // Two bits per sheet for clear and select.
    u32 clearPlus;
};

struct BINGO_PANEL_dd_ {
    u8 type;
    u8 tokusei;
    u8 seikaku;
    u8 sex;
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
    u8 isClearPlus(u32 index);
    void setClear(u32 index);
    static void setSelect(u32 index);
    u8 isSelect(u32 index);
    u8 isClear(u32 index);
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

private:
    static u8 mStaticNo;
    static u8 mStaticBall;
    static u8 mStaticIdx[2];
    static u8 mStaticResult;
};

typedef char BingoSheetSizeCheck[sizeof(BINGO_DATA_dd_) == 0xb8 ? 1 : -1];

#endif
