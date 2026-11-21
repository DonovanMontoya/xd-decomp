#pragma defer_codegen off
#pragma force_active on
#include <global.h>
#include <game/maximum/app/bingo/bingoBios.hpp>
extern "C" {
extern s32* savedataGetStatus(u32,u32);
extern BINGO_DATA_dd_* bingo_data;
extern u32* bingo_data_number;
}
u8 bingo_bios::mStaticNo; u8 bingo_bios::mStaticBall; u8 bingo_bios::mStaticIdx[2]; u8 bingo_bios::mStaticResult;
u8 bingo_bios::isClearPlus(u32 i){if(i>=*bingo_data_number)return 0;s32* p=savedataGetStatus(0,0x1b);return ((p[1]&(1<<i))!=0);}
extern "C" void fn_802967E4(bingo_bios*,u32 index){if(index<*bingo_data_number){s32* state=savedataGetStatus(0,0x1b);state[1]|=1<<index;}}
void bingo_bios::setClear(u32 i){if(i<*bingo_data_number){s32* p=savedataGetStatus(0,0x1b);*p|=1<<(i*2);}}
void bingo_bios::setSelect(u32 i){s32* p=savedataGetStatus(0,0x1b);*p|=2<<(i*2);}
u8 bingo_bios::isSelect(u32 i){if(i>=*bingo_data_number)return 0;s32* p=savedataGetStatus(0,0x1b);return ((*p&(2<<(i*2)))!=0);}
u8 bingo_bios::isClear(u32 i){if(i>=*bingo_data_number)return 0;s32* p=savedataGetStatus(0,0x1b);return ((*p&(1<<(i*2)))!=0);}
u32 bingo_bios::getClearLv(){
    s32* state=savedataGetStatus(0,0x1b);
    s32 index=0;
    s32 highest=0;
    u32 cleared=0;
    s32 advance=0;
    s32 levels[4]={0,1,2,3};
    u32 counts[4]={3,6,9,0};
    counts[3]=*bingo_data_number;
    for(index=0;(u32)index<counts[3];index++){
        if((*state & (1<<(index*2))) && index!=10){
            if(highest<index)highest=index;
            cleared++;
        }
    }
    s32 tier;
    if(highest<3)tier=0;
    else if(highest<6)tier=1;
    else if(highest<9)tier=2;
    else tier=3;
    if(cleared==counts[tier])advance=1;
    tier+=advance;
    for(s32 i=0;(u32)i<counts[tier];i++){
        if(i!=10)*state|=2<<(i*2);
    }
    return levels[tier];
}
u16 bingo_bios::getScore(BINGO_DATA_dd_* sheet, u8 index) {
    if (index >= 10) return 0;
    return sheet->score[index];
}

u8 bingo_bios::getGridPos(BINGO_DATA_dd_* sheet, u32 index) {
    if (index >= 3) return 0;
    return sheet->grid[index].pos;
}

u8 bingo_bios::getGridGrid(BINGO_DATA_dd_* sheet, u32 index) {
    if (index >= 3) return 0;
    return sheet->grid[index].grid;
}

u8 bingo_bios::getPanelHoseiVal(BINGO_DATA_dd_* sheet, u32 index) {
    if (index >= 14) return 0;
    return (u8)sheet->panel[index].hosei;
}

u8 bingo_bios::getPanelHoseiKind(BINGO_DATA_dd_* sheet, u32 index) {
    if (index >= 14) return 0;
    return (sheet->panel[index].hosei >> 12) & 15;
}

u16 bingo_bios::getPanelWaza(BINGO_DATA_dd_* sheet, u32 index) {
    if (index >= 14) return 0;
    return sheet->panel[index].waza;
}

u16 bingo_bios::getPanelNo(BINGO_DATA_dd_* sheet, u32 index) {
    if (index >= 14) return 0;
    return sheet->panel[index].no;
}

u8 bingo_bios::getPanelTokusei(BINGO_DATA_dd_* sheet, u32 index) {
    if (index >= 14) return 0;
    return sheet->panel[index].tokusei;
}

u8 bingo_bios::getPanelType(BINGO_DATA_dd_* sheet, u32 index) {
    if (index >= 14) return 0;
    return sheet->panel[index].type;
}

u8 bingo_bios::getBall(BINGO_DATA_dd_* sheet) {
    if (sheet) return sheet->ball;
    return 0;
}

u8 bingo_bios::getLevel(BINGO_DATA_dd_* sheet) {
    if (sheet) return sheet->level;
    return 0;
}

u8 bingo_bios::getNo(BINGO_DATA_dd_* sheet) {
    if (sheet) return sheet->no;
    return 0;
}

u8 bingo_bios::getStaticIdx(u8 i){if(i>=2)return 0;return mStaticIdx[i];}
void bingo_bios::setStaticIdx(u8 a,u8 b){mStaticIdx[0]=a;mStaticIdx[1]=b;}
u8 bingo_bios::getStaticResult(){return mStaticResult;}
void bingo_bios::setStaticResult(u8 v){mStaticResult=v;}
void bingo_bios::decStaticBall(){if(mStaticBall!=0)mStaticBall-=1;}
u8 bingo_bios::getStaticBall(){return mStaticBall;}
void bingo_bios::setStaticBall(u8 v){mStaticBall=v;}
BINGO_DATA_dd_* bingo_bios::getStaticSheet() {
    if (*bingo_data_number <= mStaticNo) return 0;
    return &bingo_data[mStaticNo];
}
void bingo_bios::setStaticNo(u8 v){mStaticNo=v;}
