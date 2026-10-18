#include <global.h>
extern "C" {
extern s32* savedataGetStatus(u32,u32);
extern s32 bingo_data; extern u32* bingo_data_number;
}
struct BingoPanelEntry {u8 type,tokusei,pad[2];u16 number,waza,hosei;};
struct BINGO_DATA_dd_ { union { u8 raw[0xb8]; struct {u8 pad[0x10];u16 scores[10];} scoreLayout; struct {u8 pad[0x24];BingoPanelEntry panels[14];} layout; }; };
class bingo_bios {
public:
 static u8 mStaticBall; static u8 mStaticIdx[2]; static u8 mStaticNo; static u8 mStaticResult;
 s32 getClearLv();
 u8 isClearPlus(u32); void setClear(u32); static void setSelect(u32); u8 isSelect(u32); u8 isClear(u32);
 u16 getScore(BINGO_DATA_dd_*,u8); u8 getGridPos(BINGO_DATA_dd_*,u32); u8 getGridGrid(BINGO_DATA_dd_*,u32);
 static u8 getPanelHoseiVal(BINGO_DATA_dd_*,u32); static s32 getPanelHoseiKind(BINGO_DATA_dd_*,u32); u16 getPanelWaza(BINGO_DATA_dd_*,u32); u16 getPanelNo(BINGO_DATA_dd_*,u32); u8 getPanelTokusei(BINGO_DATA_dd_*,u32); u8 getPanelType(BINGO_DATA_dd_*,u32);
 u8 getBall(BINGO_DATA_dd_*); u8 getLevel(BINGO_DATA_dd_*); u8 getNo(BINGO_DATA_dd_*);
 static u8 getStaticIdx(u8); static void setStaticIdx(u8,u8); static u8 getStaticResult(); static void setStaticResult(u8); static void decStaticBall(); static u8 getStaticBall(); static void setStaticBall(u8); static s32 getStaticSheet(); static void setStaticNo(u8);
};
u8 bingo_bios::mStaticBall; u8 bingo_bios::mStaticIdx[2]; u8 bingo_bios::mStaticNo; u8 bingo_bios::mStaticResult;
u8 bingo_bios::isClearPlus(u32 i){if(i>=*bingo_data_number)return 0;s32* p=savedataGetStatus(0,0x1b);return (u8)((p[1]&(1<<i))!=0);}
void bingo_bios::setClear(u32 i){if(i<*bingo_data_number){s32* p=savedataGetStatus(0,0x1b);*p|=1<<(i*2);}}
void bingo_bios::setSelect(u32 i){s32* p=savedataGetStatus(0,0x1b);*p|=2<<(i*2);}
u8 bingo_bios::isSelect(u32 i){if(i>=*bingo_data_number)return 0;return (u8)((*savedataGetStatus(0,0x1b)&(2<<(i*2)))!=0);}
u8 bingo_bios::isClear(u32 i){if(i>=*bingo_data_number)return 0;return (u8)((*savedataGetStatus(0,0x1b)&(1<<(i*2)))!=0);}
u16 bingo_bios::getScore(BINGO_DATA_dd_* p,u8 i){if(i>=10)return 0;return p->scoreLayout.scores[i];}
u8 bingo_bios::getGridPos(BINGO_DATA_dd_* p,u32 i){if(i>=3)return 0;return p->raw[0xb1+i*2];}
u8 bingo_bios::getGridGrid(BINGO_DATA_dd_* p,u32 i){if(i>=3)return 0;return p->raw[0xb0+i*2];}
u8 bingo_bios::getPanelHoseiVal(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return (u8)p->layout.panels[i].hosei;}
s32 bingo_bios::getPanelHoseiKind(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return (p->layout.panels[i].hosei>>12)&15;}
u16 bingo_bios::getPanelWaza(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return p->layout.panels[i].waza;}
u16 bingo_bios::getPanelNo(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return p->layout.panels[i].number;}
u8 bingo_bios::getPanelTokusei(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return p->raw[0x25+i*0xa];}
u8 bingo_bios::getPanelType(BINGO_DATA_dd_* p,u32 i){if(i>=14)return 0;return p->raw[0x24+i*0xa];}
u8 bingo_bios::getBall(BINGO_DATA_dd_* p){if(p)return p->raw[5];return 0;}
u8 bingo_bios::getLevel(BINGO_DATA_dd_* p){if(p)return p->raw[3];return 0;}
u8 bingo_bios::getNo(BINGO_DATA_dd_* p){if(p)return p->raw[0];return 0;}
u8 bingo_bios::getStaticIdx(u8 i){if(i>=2)return 0;return mStaticIdx[i];}
void bingo_bios::setStaticIdx(u8 a,u8 b){mStaticIdx[0]=a;mStaticIdx[1]=b;}
u8 bingo_bios::getStaticResult(){return mStaticResult;}
void bingo_bios::setStaticResult(u8 v){mStaticResult=v;}
void bingo_bios::decStaticBall(){if(mStaticBall!=0)mStaticBall-=1;}
u8 bingo_bios::getStaticBall(){return mStaticBall;}
void bingo_bios::setStaticBall(u8 v){mStaticBall=v;}
s32 bingo_bios::getStaticSheet(){if(*bingo_data_number<=mStaticNo)return 0;return bingo_data+mStaticNo*0xb8;}
void bingo_bios::setStaticNo(u8 v){mStaticNo=v;}

extern "C" void fn_802967E4(bingo_bios*,u32 index){if(index<*bingo_data_number){s32* state=savedataGetStatus(0,0x1b);state[1]|=1<<index;}}
s32 bingo_bios::getClearLv(){
    s32* state=savedataGetStatus(0,0x1b);
    s32 index=0;
    s32 highest=0;
    u32 cleared=0;
    s32 advance=0;
    s32 levels[4]={0,1,2,3};
    u32 counts[4]={3,6,9,0};
    counts[3]=*bingo_data_number;
    for(;(u32)index<counts[3];index++){
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
    s32 result=tier+advance;
    for(u32 i=0;i<counts[result];i++){
        if(i!=10)*state|=2<<(i*2);
    }
    return levels[result];
}
