#ifndef MEMCARD_PRIVATE_HPP
#define MEMCARD_PRIVATE_HPP
#include <global.h>

enum MEMCARD_MSGTYPE {
    MEMCARD_MSG_NONE = 0
};

struct MemcardFileInfo {s32 chan,fileNo,offset,length;u16 block,padding;};
struct MemcardCardStat {
    char fileName[32];
    u32 length;
    u32 time;
    u8 gameName[4];
    u8 company[2];
    u8 bannerFormat;
    u8 pad2F;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u32 commentAddr;
    u32 offsetBanner;
    u32 offsetBannerTlut;
    u32 offsetIcon[8];
    u32 offsetIconTlut;
    u32 offsetData;
};

struct MemcardStatus {
    volatile s32 state;     // 0x00
    volatile s32 msg;                // 0x04
    s32 result;             // 0x08
    s32 task;               // 0x0C
    s32 nextTask;           // 0x10
    s32 param;              // 0x14
    s32 cardSize,sectorSize;
    s32 index;              // 0x20
    s32 retryCount,cardResult;
    s32 unk2C;              // 0x2C
    s32 limit;              // 0x30
    s32 timer;              // 0x34
    u32 busyCount;
    u8 callbackDone;        // 0x3C
    u8 mounted;
    u8 unk3E;               // 0x3E
    u8 resetEnabled;
    u8 unk40;               // 0x40
    u8 valid;               // 0x41
    u8 reserved42[6];
    union { u64 serial; struct { u32 serialHigh,serialLow; }; };
    u8* buf50;            // 0x50
    u8* buf54;            // 0x54
    void* saveData;         // 0x58
    s32 priority;           // 0x5C
    s32 unk60;              // 0x60
    s32 gapp;               // 0x64
    u8 reserved68[0x24];
    MemcardFileInfo file;
    MemcardCardStat stat;
    u8 reserved10C[0x104];
};

extern "C" {
void CARDInit(void);
s32 GSgappCreate(s32, s32, s32, void (*)(u32, u32));
void GSgappTerminate(s32);
void* GSmemAllocAlign(u32, u32);
void GSmemFree(void*);
void GSthreadSwitch(void);
u32 HSD_Rand(void);
void* memset(void*, int, u32);
void menuCBBios_RuleEditSaveON(s32);
void* savedataGetStatus(void*, u16);
void winMsgClose(s32);
void* memcpy(void*, const void*, u32);
s32 gamedatasaveGetStatus(void*, s32);
void gamedatasaveSetStatus(void*, s32, s32);
void winMsgOpen(s8, s32, s32, s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
void msgctrlSetValue(s32, s32);
void GSsndPlay(s32, s32, s32);
}

typedef char MemcardStatusSize[sizeof(MemcardStatus)==0x210?1:-1];
#endif
