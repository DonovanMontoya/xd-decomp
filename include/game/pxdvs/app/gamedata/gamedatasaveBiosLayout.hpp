#ifndef GAMEDATASAVE_BIOS_LAYOUT_HPP
#define GAMEDATASAVE_BIOS_LAYOUT_HPP

#include <dolphin/types.h>
#include <libc/stddef.h>

struct GamedataAttest {
    u8 ver, gen, area, langarea;
};

struct GamedataSavePayload {
    u64 memcardId;
    u32 saveCount;
    u32 saveRandom;
    u32 parChecksum;
    u32 floorId;
    f32 field18;
    u32 previousFloorId;
    u8 floorPositionIndex;
    u8 noVibration;
    u8 audioOption;
    u8 language;
    f64 playtime;
    u32 sysHeadChecksum;
};

struct GamedataSaveRecord {
    GamedataAttest attest;
    GamedataSavePayload payload;
    u16 zukanFlags;
    u32 playDataWords[16];
};

typedef char GamedataSavePayloadSize[sizeof(GamedataSavePayload) == 0x38 ? 1 : -1];
typedef char GamedataSavePayloadOffset[offsetof(GamedataSaveRecord, payload) == 8 ? 1 : -1];
typedef char GamedataPlayDataOffset[offsetof(GamedataSaveRecord, zukanFlags) == 0x40 ? 1 : -1];
typedef char GamedataSaveRecordSize[sizeof(GamedataSaveRecord) == 0x88 ? 1 : -1];

typedef char GamedataSaveOffset_memcardId[offsetof(GamedataSavePayload, memcardId) == 0x0 ? 1 : -1];
typedef char GamedataSaveOffset_saveCount[offsetof(GamedataSavePayload, saveCount) == 0x8 ? 1 : -1];
typedef char GamedataSaveOffset_saveRandom[offsetof(GamedataSavePayload, saveRandom) == 0xc ? 1 : -1];
typedef char GamedataSaveOffset_parChecksum[offsetof(GamedataSavePayload, parChecksum) == 0x10 ? 1 : -1];
typedef char GamedataSaveOffset_floorId[offsetof(GamedataSavePayload, floorId) == 0x14 ? 1 : -1];
typedef char GamedataSaveOffset_field18[offsetof(GamedataSavePayload, field18) == 0x18 ? 1 : -1];
typedef char GamedataSaveOffset_previousFloorId[offsetof(GamedataSavePayload, previousFloorId) == 0x1c ? 1 : -1];
typedef char GamedataSaveOffset_floorPositionIndex[offsetof(GamedataSavePayload, floorPositionIndex) == 0x20 ? 1 : -1];
typedef char GamedataSaveOffset_noVibration[offsetof(GamedataSavePayload, noVibration) == 0x21 ? 1 : -1];
typedef char GamedataSaveOffset_audioOption[offsetof(GamedataSavePayload, audioOption) == 0x22 ? 1 : -1];
typedef char GamedataSaveOffset_language[offsetof(GamedataSavePayload, language) == 0x23 ? 1 : -1];
typedef char GamedataSaveOffset_playtime[offsetof(GamedataSavePayload, playtime) == 0x28 ? 1 : -1];
typedef char GamedataSaveOffset_sysHeadChecksum[offsetof(GamedataSavePayload, sysHeadChecksum) == 0x30 ? 1 : -1];

extern "C" {
GamedataSavePayload* gamedatasaveBiosGetPtr(GamedataSaveRecord*);
void gamedatasaveBiosSetPtr(GamedataSaveRecord*, const GamedataSavePayload*);
u64 gamedatasaveBiosGetMemcardID(GamedataSavePayload*);
void gamedatasaveBiosSetMemcardID(GamedataSavePayload*, u64);
f64 gamedatasaveBiosGetPlaytime(GamedataSavePayload*);
void gamedatasaveBiosSetPlaytime(GamedataSavePayload*, f64);

void gamedatasaveBiosSetSysHeadChecksum(GamedataSavePayload*, u32);
u32 gamedatasaveBiosGetSysHeadChecksum(GamedataSavePayload*);
void fn_801577B4(GamedataSavePayload*, u8);
u8 fn_801577C4(GamedataSavePayload*);
void gamedatasaveBiosSetParChecksum(GamedataSavePayload*, u32);
u32 gamedatasaveBiosGetParChecksum(GamedataSavePayload*);
void gamedatasaveBiosSetOptionAudio(GamedataSavePayload*, u8);
void gamedatasaveBiosSetOptionNoVibration(GamedataSavePayload*, u8);
void gamedatasaveBiosSetFloorposindex(GamedataSavePayload*, u8);
void gamedatasaveBiosSetPrevfloorid(GamedataSavePayload*, u32);
void gamedatasaveBiosSetFloorid(GamedataSavePayload*, u32);
void gamedatasaveBiosSetSavecount(GamedataSavePayload*, u32);
void gamedatasaveBiosSetSavernd(GamedataSavePayload*, u32);
u8 gamedatasaveBiosGetOptionAudio(GamedataSavePayload*);
u8 gamedatasaveBiosGetOptionNoVibration(GamedataSavePayload*);
u8 gamedatasaveBiosGetFloorposindex(GamedataSavePayload*);
u32 gamedatasaveBiosGetPrevfloorid(GamedataSavePayload*);
u32 gamedatasaveBiosGetFloorid(GamedataSavePayload*);
u32 gamedatasaveBiosGetSavecount(GamedataSavePayload*);
u32 gamedatasaveBiosGetSavernd(GamedataSavePayload*);

u16* gamedatasaveBiosGetplaydata(GamedataSaveRecord*);
void gamedatasaveInit(GamedataSaveRecord*);
}

#endif
