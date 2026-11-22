#pragma force_active on
#include <game/pxdvs/app/gamedata/gamedatasaveBiosLayout.hpp>
#pragma dont_inline on
extern "C" {
void gamedataBiosSetZukanFLag(u16* flags,u16 index,u16 value){if(flags==0)return;if(index>0x10)return;u16 bit=(u16)(1u<<index);if(value==1){*flags|=bit;}else{*flags=*flags&~bit;}}
u32 gamedataBiosGetZukanFlag(const u16* flags,u16 index){if(flags){if(index>0x10)return 0;u16 bit=(u16)(1u<<index);bit&=*flags;return bit!=0;}return 0;}

u16* gamedatasaveBiosGetplaydata(GamedataSaveRecord* record) {
    if (record == 0) return 0;
    return &record->zukanFlags;
}

void gamedatasaveBiosSetSysHeadChecksum(GamedataSavePayload* payload, u32 value) {
    if (payload) payload->sysHeadChecksum = value;
}

u32 gamedatasaveBiosGetSysHeadChecksum(GamedataSavePayload* payload) {
    if (payload) return payload->sysHeadChecksum;
    return 0;
}

void fn_801577B4(GamedataSavePayload* payload, u8 value) {
    if (payload) payload->language = value;
}

u8 fn_801577C4(GamedataSavePayload* payload) {
    if (payload) return payload->language;
    return 0;
}

void gamedatasaveBiosSetParChecksum(GamedataSavePayload* payload, u32 value) {
    if (payload) payload->parChecksum = value;
}

u32 gamedatasaveBiosGetParChecksum(GamedataSavePayload* payload) {
    if (payload) return payload->parChecksum;
    return 0;
}

void gamedatasaveBiosSetOptionAudio(GamedataSavePayload* payload, u8 value) {
    if (payload) payload->audioOption = value;
}

void gamedatasaveBiosSetOptionNoVibration(GamedataSavePayload* payload, u8 value) {
    if (payload) payload->noVibration = value;
}

void gamedatasaveBiosSetFloorposindex(GamedataSavePayload* payload, u8 value) {
    if (payload) payload->floorPositionIndex = value;
}

void gamedatasaveBiosSetPrevfloorid(GamedataSavePayload* payload, u32 value) {
    if (payload) payload->previousFloorId = value;
}

void gamedatasaveBiosSetPlaytime(GamedataSavePayload* payload, f64 value) {
    if (payload) payload->playtime = value;
}

void gamedatasaveBiosSetFloorid(GamedataSavePayload* payload, u32 value) {
    if (payload) payload->floorId = value;
}

void gamedatasaveBiosSetSavecount(GamedataSavePayload* payload, u32 value) {
    if (payload) payload->saveCount = value;
}

void gamedatasaveBiosSetMemcardID(GamedataSavePayload* payload, u64 value) {
    if (payload) payload->memcardId = value;
}

void gamedatasaveBiosSetSavernd(GamedataSavePayload* payload, u32 value) {
    if (payload) payload->saveRandom = value;
}

u8 gamedatasaveBiosGetOptionAudio(GamedataSavePayload* payload) {
    if (payload) return payload->audioOption;
    return 0;
}

u8 gamedatasaveBiosGetOptionNoVibration(GamedataSavePayload* payload) {
    if (payload) return payload->noVibration;
    return 0;
}

u8 gamedatasaveBiosGetFloorposindex(GamedataSavePayload* payload) {
    if (payload) return payload->floorPositionIndex;
    return 0;
}

u32 gamedatasaveBiosGetPrevfloorid(GamedataSavePayload* payload) {
    if (payload) return payload->previousFloorId;
    return 0;
}

f64 gamedatasaveBiosGetPlaytime(GamedataSavePayload* payload) {
    if (payload) return payload->playtime;
    return 0.0;
}

u32 gamedatasaveBiosGetFloorid(GamedataSavePayload* payload) {
    if (payload) return payload->floorId;
    return 0;
}

u32 gamedatasaveBiosGetSavecount(GamedataSavePayload* payload) {
    if (payload) return payload->saveCount;
    return 0;
}

u64 gamedatasaveBiosGetMemcardID(GamedataSavePayload* payload) {
    if (payload) return payload->memcardId;
    return 0;
}

u32 gamedatasaveBiosGetSavernd(GamedataSavePayload* payload) {
    if (payload) return payload->saveRandom;
    return 0;
}

void gamedatasaveBiosSetPtr(GamedataSaveRecord* dst, const GamedataSavePayload* src) {
    if (dst == 0 || src == 0) return;
    dst->payload.memcardId = src->memcardId;
    dst->payload.saveCount = src->saveCount;
    dst->payload.saveRandom = src->saveRandom;
    dst->payload.parChecksum = src->parChecksum;
    dst->payload.floorId = src->floorId;
    dst->payload.field18 = src->field18;
    dst->payload.previousFloorId = src->previousFloorId;
    dst->payload.floorPositionIndex = src->floorPositionIndex;
    dst->payload.noVibration = src->noVibration;
    dst->payload.audioOption = src->audioOption;
    dst->payload.language = src->language;
    dst->payload.playtime = src->playtime;
    dst->payload.sysHeadChecksum = src->sysHeadChecksum;
}

GamedataSavePayload* gamedatasaveBiosGetPtr(GamedataSaveRecord* record) {
    if (record == 0) return 0;
    return &record->payload;
}

void gamedatasaveInit(GamedataSaveRecord* record) {
    GamedataSavePayload* payload;
    if (record == 0) payload = 0;
    else payload = &record->payload;
    if (payload) payload->saveCount = 0;
}
}
#pragma force_active reset
