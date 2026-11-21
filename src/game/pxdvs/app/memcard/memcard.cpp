#include <dolphin/os.h>
#include <game/pxdvs/app/gamedata/gamedatasaveBiosLayout.hpp>
#include <game/pxdvs/app/memcard/memcardPrivate.hpp>
#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/pcbox/pcbox.hpp>
#include <game/pxdvs/app/sodateya/sodateya.hpp>
#include <game/pxdvs/app/mail/mailbox.hpp>
#include <game/pxdvs/app/memo/memo.hpp>
#include <game/pxdvs/app/reliveHall/reliveHall.hpp>
#include <game/pxdvs/app/hero/hero.hpp>

#if defined(VERSION_GXXE01)
static const u8 _memcardBannerImage[] = {
#include <game/memcard/_memcardBannerImage.inc>
};
static const u8 _memcardIconImage[] = {
#include <game/memcard/_memcardIconImage.inc>
};
#else
extern "C" const u8 _memcardBannerImage[0x1800];
extern "C" const u8 _memcardIconImage[0x2200];
#endif

static u16 _memcard_encrypt_key[4];
static u8 _memcardInitializeFlag;
static u8 _memcard_new_saveDataCrateFlag;
static MemcardStatus* _memcardStatusPtr;
static u8 _memcard_anySaveOFF_Flag;
static u8 _memcard_gba2mode;
static u8 _memcardStatusBuf[0x210] __attribute__((aligned(8)));

static u8 _memcardMsgOpen(MEMCARD_MSGTYPE msg);

// Save task and data helper entry points.
static void _memcardJobMain(u32, u32);
static u8 _memcard_Decryption(void*);
static void _memcard_Encryption(void*);
static void _memcardStoreSaveData_multi(void*);
static void _memcardDuplicateSaveData_multi(void*);
static void* _memcardGetMultiSaveDataToSTRUCT(void*, long);

static s32 _memcardMergeDataPack();
static s32 _memcardExamineDataPack();
static s32 _memcardExamineHeader();
static s32 _memcardCardOpen();
static void _memcardCallback(long, long);
extern "C" s32 fn_801CC508();

static inline void advanceMemcardKey() {
    u16 key[4];
    u32 increments[4] = {0x43, 0x29, 0x17, 0x13};
    s32 i;
    for (i = 0; i < 4; i++) {
        key[i] = _memcard_encrypt_key[i];
        key[i] += increments[i];
    }
    _memcard_encrypt_key[0] = (key[0]&0xF) | ((key[1]&0xF)<<4) | ((key[2]&0xF)<<8) | ((key[3]&0xF)<<12);
    _memcard_encrypt_key[1] = ((key[0]&0xF0)>>4) | (key[1]&0xF0) | ((key[2]&0xF0)<<4) | ((key[3]&0xF0)<<8);
    _memcard_encrypt_key[2] = ((key[0]&0xF00)>>8) | ((key[1]&0xF00)>>4) | (key[2]&0xF00) | ((key[3]&0xF00)<<4);
    _memcard_encrypt_key[3] = ((key[0]&0xF000)>>12) | ((key[1]&0xF000)>>8) | ((key[2]&0xF000)>>4) | (key[3]&0xF000);
}

static inline s32 _memcardPollTask(void) {
    if (_memcardStatusPtr->task == 0x30) {
        _memcardStatusPtr->msg = _memcardMsgOpen((MEMCARD_MSGTYPE)_memcardStatusPtr->msg);
        _memcardStatusPtr->task = _memcardStatusPtr->nextTask;
    }
    if (_memcardStatusPtr->task != 0x32) {
        return 0;
    }
    return _memcardStatusPtr->result;
}

static inline void _memcardFinish(void) {
    if (_memcardStatusPtr->state != 0) {
        if (_memcardStatusPtr->state != 8) {
            winMsgClose(1);
        }
        GSgappTerminate(_memcardStatusPtr->gapp);
        GSmemFree(_memcardStatusPtr->buf54);
        _memcardStatusPtr->buf54 = 0;
        GSmemFree(_memcardStatusPtr->buf50);
        _memcardStatusPtr->buf50 = 0;
    }
    _memcardStatusPtr->state = 0;
}

static inline void _memcardStart(s32 state, s32 priority, s32 param) {
    if (_memcardStatusPtr->state != 0) {
        do {
            GSthreadSwitch();
        } while (_memcardPollTask() == 0);
        _memcardFinish();
    }
    if (priority == 0) {
        priority = 2;
    }
    _memcardStatusPtr->state = state;
    _memcardStatusPtr->param = param;
    _memcardStatusPtr->priority = priority;
    _memcardStatusPtr->result = 0;
    _memcardStatusPtr->task = 0;
    _memcardStatusPtr->msg = 0;
    _memcardStatusPtr->unk3E = 0;
    _memcardStatusPtr->buf50 = (u8*)GSmemAllocAlign(0x28400, 0x20);
    _memcardStatusPtr->buf54 = (u8*)GSmemAllocAlign(0xA000, 0x20);
    _memcardStatusPtr->gapp = GSgappCreate(1, 0x17, 0, _memcardJobMain);
    _memcardStatusPtr->saveData = savedataGetStatus(0, 0);
}

extern "C" {

void memcard_debug_Load2(void) {
    _memcardStatusPtr->valid = 1;
}

void memcard_debug_Load(void* data) {
    s32* save;
    _memcardStart(2, 2, 0);
    _memcard_Decryption(data);
    _memcardStoreSaveData_multi(data);
    _memcardStatusPtr->valid = 1;
    _memcardFinish();
    save = (s32*)savedataGetStatus(0, 1);
    if (save[4] == 0) {
        save[4] = save[4] + 1;
    }
}

void memcard_debug_Save(void* data) {
    _memcardStart(0xB, 2, 0);
    _memcardDuplicateSaveData_multi(data);
    _memcard_Encryption(data);
    _memcardFinish();
}

}

u8 _memcard_Decryption(void* buffer) {
    s32 word;
    s32 i;
    u32 check[4];
    u32 sums[4];
    u16* data;
    data = (u16*)buffer;
    _memcard_encrypt_key[0] = data[0];
    _memcard_encrypt_key[1] = data[1];
    _memcard_encrypt_key[2] = data[2];
    _memcard_encrypt_key[3] = data[3];
    sums[0]=0; sums[1]=0; sums[2]=0; sums[3]=0;
    for (word=4; word<0x13FE8; word+=4) {
        for (i = 0; i < 4; i++) {
            data[word+i] -= _memcard_encrypt_key[i];
        }
        advanceMemcardKey();
    }
    check[0] = (data[11]<<16) | data[10];
    check[1] = data[8] | (data[9]<<16);
    check[2] = data[6] | (data[7]<<16);
    check[3] = data[4] | (data[5]<<16);
    data[10]=0; data[11]=0; data[8]=0; data[9]=0;
    data[6]=0; data[7]=0; data[4]=0; data[5]=0;
    for (i = 0; i < 4; i++) {
        for (word = i*0x4FFA; word < (i+1)*0x4FFA; word++) sums[i] += data[word];
    }
    if (sums[0]==check[0] && sums[1]==check[1] && sums[2]==check[2] && sums[3]==check[3]) return 1;
    return 0;
}

void _memcard_Encryption(void* buffer) {
    s32 word;
    s32 i;
    u32 sums[4];
    sums[0]=0; sums[1]=0; sums[2]=0; sums[3]=0;
    u16* data = (u16*)buffer;
    _memcard_encrypt_key[0] = data[0];
    _memcard_encrypt_key[1] = data[1];
    _memcard_encrypt_key[2] = data[2];
    _memcard_encrypt_key[3] = data[3];
    data[10]=0; data[11]=0; data[8]=0; data[9]=0;
    data[6]=0; data[7]=0; data[4]=0; data[5]=0;
    for (i = 0; i < 4; i++) {
        for (word = i*0x4FFA; word < (i+1)*0x4FFA; word++) sums[i] += data[word];
    }
    data[10]=sums[0]; data[11]=sums[0]>>16;
    data[8]=sums[1]; data[9]=sums[1]>>16;
    data[6]=sums[2]; data[7]=sums[2]>>16;
    data[4]=sums[3]; data[5]=sums[3]>>16;
    for (word=4; word<0x13FE8; word+=4) {
        for (i = 0; i < 4; i++) {
            data[word+i] += _memcard_encrypt_key[i];
        }
        advanceMemcardKey();
    }
}

enum MemcardSection {
    SectionSystem,
    SectionHero,
    SectionPcBox,
    SectionMailbox,
    SectionSodateya,
    SectionMemo,
    SectionTool,
    SectionDarkPokemon,
    SectionFlags,
    SectionExRibbon,
    SectionYobi1,
    SectionYobi2,
    SectionYobi3,
    SectionYobi4,
    SectionRelive,
    SectionFloor,
    SectionCount
};

struct MemcardHalfWords {
    u16 low;
    u16 high;
};

struct MemcardPackHeader {
    u16 key[4];
    MemcardHalfWords checksums[4];
    u16 sizes[SectionCount];
    MemcardHalfWords offsets[SectionCount];
    u16 flagLevel0Size;
    u16 flagLevel1Size;
    u16 flagLevel2Size;
    u16 battleDiskFlagsSize;
    u16 pcBoxSizeHigh;
    u16 bingoFlagsSize;
    u8 reserved84[0x1C];
};

struct MemcardSavePack {
    MemcardPackHeader header;
    u8 payload[0x27FD0 - sizeof(MemcardPackHeader)];

    u8* setSectionOffset(MemcardSection section, u32 offset) {
        header.offsets[section].low = offset;
        header.offsets[section].high = offset >> 16;
        return &payload[offset];
    }
};

typedef char MemcardSavePackSize[sizeof(MemcardSavePack) == 0x27FD0 ? 1 : -1];
typedef char MemcardPackHeaderSize[sizeof(MemcardPackHeader) == 0xA0 ? 1 : -1];
typedef char MemcardSectionSizesOffset[offsetof(MemcardPackHeader, sizes) == 0x18 ? 1 : -1];
typedef char MemcardSectionOffsetsOffset[offsetof(MemcardPackHeader, offsets) == 0x38 ? 1 : -1];

extern "C" {
s32 CARDFreeBlocks(s32, s32*, s32*);
s32 CARDFastOpen(s32, s32, void*);
s32 CARDGetStatus(s32, s32, MemcardCardStat*);
s32 pokecoloGetCountryCode(void);
int strcmp(const char*, const char*);
}

static inline u8 _memcardIsXDSave(MemcardCardStat* stat,s32 result) {
    if(result==0) switch (pokecoloGetCountryCode()) {
    case 0:
        if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXJ" && *(u16*)stat->company == *(u16*)"01") return 1;
        break;
    case 1:
        if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXE" && *(u16*)stat->company == *(u16*)"01") return 1;
        break;
    case 2:
        if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXP" && *(u16*)stat->company == *(u16*)"01") return 1;
        break;
    }
    return 0;
}

static inline s32 _memcardFindSave() {
        s32 i;
        s32 result;
        s32 chan;
        void* info;
        MemcardCardStat stat;
        chan = *(s32*)((u8*)_memcardStatusPtr + 0x14);
        info = (u8*)_memcardStatusPtr + 0x8C;
        i = 0;
            for (;;) {
                result = CARDFastOpen(chan, i, info);
                if (result == 0) {
                    result = CARDGetStatus(chan, i, &stat);
                    u8 found;
                    found = _memcardIsXDSave(&stat,result);
                    if (found) {
                        result = 0;
                        break;
                    }
                }
                ++i;
                if (i >= 0x7F) {
                    if (result == 0) result = -4;
                    break;
                }
            }
        return result;
}

inline u64 memcardCurrentID(void *pack)
{
    if (pack == 0) {
        return gamedatasaveBiosGetMemcardID(
            gamedatasaveBiosGetPtr((GamedataSaveRecord*)savedataGetStatus(pack, 1)));
    }
    return gamedatasaveBiosGetMemcardID(
        &((GamedataSaveRecord*)_memcardGetMultiSaveDataToSTRUCT(pack, 1))->payload);
}

inline void decryptMemcardHeader(void *buffer)
{
    u16 *data=(u16 *)buffer;
    _memcard_encrypt_key[0]=data[0];
    _memcard_encrypt_key[1]=data[1];
    _memcard_encrypt_key[2]=data[2];
    _memcard_encrypt_key[3]=data[3];
    for(s32 word=4;word<0xFC;word+=4) {
        for(s32 i=0;i<4;i++) {
            data[word+i]-=_memcard_encrypt_key[i];
        }
        advanceMemcardKey();
    }
}

struct MemcardSaveHeader {
    u8 valid[3];
    u8 reserved3;
    s32 sequence;
    u8 payload[0x1F8];
};

static inline u8 _memcardHeaderValid(MemcardSaveHeader *header)
{
    u8 valid=0;
    if(header->valid[0]==1 && header->valid[1]==1 && header->valid[2]==1) valid=1;
    return valid;
}

static inline MemcardSaveHeader *_memcardGetHeader(s32 offset)
{
    return (MemcardSaveHeader *)((u8 *)_memcardStatusPtr->buf50+offset);
}

// Card operations advance until an asynchronous request needs another frame.
extern "C" {
typedef void (*MemcardCallback)(s32,s32);
void CARDCancel(MemcardFileInfo*);s32 CARDCheckAsync(s32,MemcardCallback);void CARDClose(MemcardFileInfo*);
s32 CARDCreateAsync(s32,const char*,u32,MemcardFileInfo*,MemcardCallback);s32 CARDDeleteAsync(s32,const char*,MemcardCallback);s32 CARDFormatAsync(s32,MemcardCallback);
s32 CARDGetAttributes(s32,s32,u8*);s32 CARDGetResultCode(s32);s32 CARDGetSerialNo(s32,u64*);
s32 CARDMountAsync(s32,void*,MemcardCallback,MemcardCallback);s32 CARDProbeEx(s32,s32*,s32*);
s32 CARDReadAsync(MemcardFileInfo*,void*,s32,s32,MemcardCallback);s32 CARDSetAttributesAsync(s32,s32,u8,MemcardCallback);s32 CARDSetStatusAsync(s32,s32,MemcardCardStat*,MemcardCallback);s32 CARDUnmount(s32);
s32 CARDWriteAsync(MemcardFileInfo*,void*,s32,s32,MemcardCallback);
u8 GSgfxResetDisable();u8 GSgfxResetRestore(u8);void PKJB_ReturnTitle(u8);void floorMemoryCardSaveCallback();
s32 gbaCommandChangePokemonEnd(s32);u8 gbaCommandIsConnected(s32);
}
#pragma push
#pragma dont_inline on
// SDK accessors for the recovered card-stat layout.
#define CARD_STAT_BANNER_MASK 3
#define CARD_STAT_ANIM_MASK 4
#define CARD_STAT_ICON_MASK 3
#define CARD_STAT_SPEED_MASK 3
#define CARDSetBannerFormat(stat, f) \
    ((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~CARD_STAT_BANNER_MASK) | (f)))
#define CARDSetIconAnim(stat, f) \
    ((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~CARD_STAT_ANIM_MASK) | (f)))
#define CARDSetIconFormat(stat, n, f) \
    ((stat)->iconFormat = (u16)(((stat)->iconFormat & ~(CARD_STAT_ICON_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconSpeed(stat, n, f) \
    ((stat)->iconSpeed = (u16)(((stat)->iconSpeed & ~(CARD_STAT_SPEED_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconAddress(stat, addr) ((stat)->iconAddr = (u32)(addr))
#define CARDSetCommentAddress(stat, addr) ((stat)->commentAddr = (u32)(addr))


#pragma push
#pragma dont_inline off
static inline s32 _memcardPollResult(void)
{
    s32 result = _memcardStatusPtr->cardResult;

    if (result != -1) {
        return result;
    }
    result = CARDGetResultCode(_memcardStatusPtr->param);
    _memcardStatusPtr->cardResult = result;
    return result;
}

static inline void _memcardSetRequestResult(s32 result)
{
    if (result == 0) {
        result = CARDGetResultCode(_memcardStatusPtr->param);
    }
    _memcardStatusPtr->cardResult = result;
}

static inline s32 _memcardAsk(s32 msg, s32 resume)
{
    _memcardStatusPtr->msg = msg;
    _memcardStatusPtr->nextTask = resume;
    return 0x30;
}

static inline s32 _memcardSaveOffset(s32 slot)
{
    return slot * 0x28000 + 0x6000;
}

static inline s32 _memcardCheckCard(void)
{
    u64 serial;
    s32 result = _memcardPollResult();

    if (_memcardStatusPtr->sectorSize != 0x2000) {
        result = -6;
    }
    switch (result) {
    case -1:
        return 5;
    case 0:
        switch (_memcardStatusPtr->state) {
        case 3:
        case 9:
        case 11:
            break;
        default:
            if (_memcardStatusPtr->valid) {
                CARDGetSerialNo(_memcardStatusPtr->param, &serial);
                if (serial != _memcardStatusPtr->serial) {
                    _memcardStatusPtr->msg = 0x10;
                    return 0x2B;
                }
            }
            break;
        }
        return 9;
    case -6:
    case -13:
        switch (_memcardStatusPtr->state) {
        case 1:
        case 9:
            return _memcardAsk(7, 6);
        }
        break;
    }
    _memcardStatusPtr->msg = result;
    return 0x2B;
}

static inline s32 _memcardCheckIconFile(void)
{
    u32 checksum = 0;
    u8* file;
    u32 i;
    s32 result = _memcardPollResult();

    switch (result) {
    case -1:
        return 0x1B;
    case 0:
        file = (u8*)_memcardStatusPtr->buf50;
        for (i = 0; i < 0xE90; i++) {
            checksum += ((u32*)file)[i];
        }
        if (checksum != *(u32*)(file + 0x3A40)) {
            _memcardStatusPtr->unk40 = 1;
        }
        return 0x1C;
    }
    _memcardStatusPtr->msg = result;
    return 0x2B;
}

static inline s32 _memcardBeginHeaderRead(void)
{
    _memcardStatusPtr->limit = 0;
    _memcardStatusPtr->index = 0;
    switch (_memcardStatusPtr->state) {
    case 1:
    case 2:
        if (_memcardStatusPtr->unk40 != 0) {
            _memcardStatusPtr->msg = 5;
            break;
        }
    case 3:
    case 8:
        return 0x1D;
    default:
        _memcardStatusPtr->msg = 2;
        break;
    }
    _memcardStatusPtr->nextTask = 0x1D;
    return 0x30;
}

static inline void _memcardSetSaveId(void* data, u64 serial)
{
    if (data == 0) {
        gamedatasaveBiosSetMemcardID(
            gamedatasaveBiosGetPtr((GamedataSaveRecord*)savedataGetStatus(data, 1)), serial);
    } else {
        gamedatasaveBiosSetMemcardID(
            &((GamedataSaveRecord*)_memcardGetMultiSaveDataToSTRUCT(data, 1))->payload, serial);
    }
}

static inline void _memcardCountSave(void* data)
{
    if (data == 0) {
        gamedatasaveSetStatus(savedataGetStatus(data, 1), 4, gamedatasaveGetStatus(savedataGetStatus(data, 1), 4) + 1);
    } else {
        void* gamedata = _memcardGetMultiSaveDataToSTRUCT(data, 1);
        gamedatasaveSetStatus(gamedata, 4, gamedatasaveGetStatus(gamedata, 4) + 1);
    }
}

static inline void _memcardFillRandom(u8* random, s32 count)
{
    while (count-- != 0) {
        *random++ = HSD_Rand();
    }
}

static inline s32 _memcardSaveSetup(void)
{
    u64 serial;
    u8* pack;

    CARDGetSerialNo(_memcardStatusPtr->param, &serial);
    _memcardSetSaveId(0, serial);
    _memcardStatusPtr->unk2C++;
    _memcardStatusPtr->index = (_memcardStatusPtr->index + 1) % 2;
    pack = (u8*)_memcardStatusPtr->buf50;
    pack[0] = 1;
    pack[1] = 1;
    pack[2] = 1;
    pack[3] = 0;
    *(s32*)(pack + 4) = _memcardStatusPtr->unk2C;
    _memcardSetSaveId(pack + 8, serial);
    switch (_memcardStatusPtr->state) {
    case 4:
    case 8:
    case 9:
    case 10:
    case 11:
        _memcardCountSave(pack + 8);
        break;
    }
    {
        void* gamedata = _memcardGetMultiSaveDataToSTRUCT(pack + 8, 1);
        u32 sum = 0;
        u32 i;

        for (i = 0; i < 0x600; i++) {
            sum += ((u32*)0x80001800)[i];
        }
        gamedatasaveSetStatus(gamedata, 0xC, sum);
    }
    {
        void* gamedata = _memcardGetMultiSaveDataToSTRUCT(pack + 8, 1);
        u32 sum = 0;
        s32 i;

        for (i = 0; i < 8; i++) {
            sum += pack[i];
        }
        gamedatasaveSetStatus(gamedata, 0xD, sum);
    }
    _memcard_Encryption(pack + 8);
    _memcardFillRandom(pack + 0x27FD8, 0x28);
    return 0x26;
}

static inline s32 _memcardCheckWrite(void)
{
    s32 result = _memcardPollResult();

    _memcardStatusPtr->busyCount++;
    switch (result) {
    case -1:
        return 0x27;
    case 0:
        _memcard_gba2mode = 0;
        switch (_memcardStatusPtr->state) {
        case 8:
            _memcardStatusPtr->nextTask = 0x28;
            _memcard_gba2mode = 1;
            return 0x31;
        case 1:
        case 2:
        case 3:
            _memcardStatusPtr->msg = 0x12;
            _memcardStatusPtr->result = 3;
            break;
        case 4:
        case 9:
        case 10:
        case 11:
            _memcardCountSave(0);
        default:
            _memcardStatusPtr->msg = 10;
            _memcardStatusPtr->result = 4;
            break;
        }
        _memcardStatusPtr->unk40 = 1;
        if (_memcardStatusPtr->unk40 != 0) {
            return 0x11;
        }
        return 0x2C;
    }
    _memcardStatusPtr->msg = result;
    return 0x2B;
}

static inline s32 _memcardPollResultInto(s32* result)
{
    *result = _memcardStatusPtr->cardResult;
    if (*result != -1) {
        return *result;
    }
    *result = CARDGetResultCode(_memcardStatusPtr->param);
    _memcardStatusPtr->cardResult = *result;
    return *result;
}

static inline s32 _memcardCheckLastWrite(void)
{
    s32 result;

    switch (_memcardPollResultInto(&result)) {
    case -1:
        _memcardStatusPtr->busyCount--;
        if (_memcardStatusPtr->mounted == 0) {
            if (gbaCommandIsConnected(2) == 0) {
                CARDCancel(&_memcardStatusPtr->file);
                return 0x2B;
            }
            if ((s32)_memcardStatusPtr->busyCount < 3) {
                if (gbaCommandChangePokemonEnd(2) != 0) {
                    CARDCancel(&_memcardStatusPtr->file);
                    return 0x2B;
                }
                _memcardStatusPtr->mounted = 1;
            }
        }
        return 0x2A;
    case 0:
        if (_memcardStatusPtr->mounted == 0) {
            gbaCommandChangePokemonEnd(2);
        }
        _memcardCountSave(0);
        _memcardStatusPtr->msg = 0;
        _memcardStatusPtr->result = 4;
        return 0x2C;
    }
    PKJB_ReturnTitle(1);
    _memcardStatusPtr->msg = result;
    return 0x2B;
}

static inline s32 _memcardEndAccess(void)
{
    u64 serial;

    if (_memcardStatusPtr->unk3E != 0) {
        CARDGetSerialNo(_memcardStatusPtr->param, &serial);
        CARDClose(&_memcardStatusPtr->file);
        _memcardStatusPtr->unk3E = 0;
    }
    CARDUnmount(_memcardStatusPtr->param);
    GSgfxResetRestore(_memcardStatusPtr->resetEnabled);
    if (_memcardStatusPtr->callbackDone != 0 && _memcard_gba2mode == 0) {
        return 0;
    }
    switch (_memcardStatusPtr->state) {
    case 3:
    case 8:
        return 0x32;
    }
    switch (_memcardStatusPtr->result) {
    case 1:
    case 2:
    case 3:
    case 4:
        _memcardStatusPtr->serial = serial;
        _memcardStatusPtr->valid = 1;
        break;
    }
    _memcardStatusPtr->msg = _memcardStatusPtr->msg;
    _memcardStatusPtr->nextTask = 0x2D;
    return 0x30;
}

static inline s32 _memcardFinishTask(void)
{
    switch (_memcardStatusPtr->state) {
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 13:
        if (_memcardStatusPtr->result != 4) {
            return _memcardAsk(0xF, 0x32);
        }
        break;
    case 1:
        if (_memcardStatusPtr->result == -1) {
            switch (_memcardStatusPtr->unk60) {
            case 7:
                _memcardStatusPtr->msg = 13;
                break;
            case 13:
                _memcardStatusPtr->msg = 14;
                break;
            default:
                return 0x2E;
            }
            _memcardStatusPtr->nextTask = 0x2E;
            return 0x30;
        }
        break;
    }
    return 0x32;
}

#pragma pop
#pragma dont_inline off
void _memcardJobMain(u32, u32)
{
    s32 next;
    s32 result;
    s32 status;

    _memcard_new_saveDataCrateFlag = 1;
    do {
        switch (_memcardStatusPtr->task) {
        case 0:
            _memcardStatusPtr->cardResult = 0;
            _memcardStatusPtr->unk60 = 0x32;
            _memcardStatusPtr->unk40 = 0;
            _memcardStatusPtr->resetEnabled = GSgfxResetDisable();
            _memcardStatusPtr->callbackDone = 0;
            _memcard_gba2mode = 0;
            GSgfxResetRestore(_memcardStatusPtr->resetEnabled);
            switch (_memcardStatusPtr->state) {
            case 1:
            case 2:
                _memcardStatusPtr->valid = 0;
                break;
            case 4:
                if ((u32)gamedatasaveGetStatus(0, 4) == 0) {
                    _memcardStatusPtr->state = 9;
                }
                floorMemoryCardSaveCallback();
                break;
            case 8:
                break;
            }
            _memcardStatusPtr->retryCount = 0;
            _memcardStatusPtr->task = 1;
            break;

        case 1:
            status = CARDProbeEx(_memcardStatusPtr->param, &_memcardStatusPtr->cardSize,
                                 &_memcardStatusPtr->sectorSize);
            _memcardSetRequestResult(status);
            switch (status) {
            case -1:
                next = 1;
                break;
            case 0:
                next = 2;
                break;
            default:
                if (_memcardStatusPtr->retryCount++ < 6) {
                    _memcardStatusPtr->cardResult = -1;
                    next = 1;
                } else {
                    _memcardStatusPtr->msg = status;
                    next = 0x2B;
                }
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 2:
            _memcardSetRequestResult(CARDMountAsync(_memcardStatusPtr->param, _memcardStatusPtr->buf54,
                                                    _memcardCallback, 0));
            _memcardStatusPtr->task = 3;
            break;

        case 3:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 3;
                break;
            case 0:
            case -6:
            case -13:
                next = 4;
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 4:
            _memcardSetRequestResult(CARDCheckAsync(_memcardStatusPtr->param, 0));
            _memcardStatusPtr->task = 5;
            break;

        case 5:
            _memcardStatusPtr->task = _memcardCheckCard();
            break;

        case 6:
            if (_memcardStatusPtr->msg != 0) {
                CARDFormatAsync(_memcardStatusPtr->param, 0);
                if (_memcardStatusPtr->callbackDone != 0) {
                    _memcardStatusPtr->msg = 0;
                    next = 0x2B;
                } else {
                    _memcardStatusPtr->unk60 = 7;
                    next = _memcardAsk(4, 7);
                }
            } else {
                _memcardStatusPtr->msg = 0;
                next = 0x2B;
            }
            _memcardStatusPtr->task = next;
            break;

        case 7:
            GSgfxResetDisable();
            result = CARDFormatAsync(_memcardStatusPtr->param, 0);
            if (_memcardStatusPtr->callbackDone != 0) {
                _memcardStatusPtr->msg = result;
                next = 0x2B;
            } else {
                _memcardSetRequestResult(result);
                next = 8;
            }
            _memcardStatusPtr->task = next;
            break;

        case 8:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 8;
                break;
            case 0:
                GSgfxResetRestore(_memcardStatusPtr->resetEnabled);
                _memcardStatusPtr->unk60 = 0x32;
                next = _memcardAsk(9, 9);
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 9:
            _memcardStatusPtr->task = _memcardCardOpen();
            break;

        case 10:
            if (_memcardStatusPtr->msg == 0) {
                _memcardStatusPtr->msg = 0;
                next = 0x2B;
            } else {
                _memcardStatusPtr->msg = 3;
                _memcardStatusPtr->unk60 = 13;
                _memcardStatusPtr->nextTask = 11;
                next = 0x30;
            }
            _memcardStatusPtr->task = next;
            break;

        case 11: {
            s32 deleted;

            GSgfxResetDisable();
            switch (pokecoloGetCountryCode()) {
            case 0:
                deleted = CARDDeleteAsync(_memcardStatusPtr->param, "PokemonXD", 0);
                break;
            case 1:
            case 2:
                deleted = CARDDeleteAsync(_memcardStatusPtr->param, "PokemonXD", 0);
                break;
            }
            _memcardSetRequestResult(deleted);
            _memcardStatusPtr->task = 12;
            break;
        }

        case 12:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 12;
                break;
            case 0:
            case -4:
                if (_memcardStatusPtr->state == 12) {
                    _memcardStatusPtr->msg = 10;
                    next = 0x2B;
                } else {
                    next = 13;
                }
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 13: {
            s32 created;

            switch (pokecoloGetCountryCode()) {
            case 0:
                created = CARDCreateAsync(_memcardStatusPtr->param, "PokemonXD", 0x56000,
                                          &_memcardStatusPtr->file, 0);
                break;
            case 1:
            case 2:
                created = CARDCreateAsync(_memcardStatusPtr->param, "PokemonXD", 0x56000,
                                          &_memcardStatusPtr->file, 0);
                break;
            }
            _memcardSetRequestResult(created);
            _memcardStatusPtr->task = 14;
            break;
        }

        case 14:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 14;
                break;
            case 0:
                _memcardStatusPtr->unk3E = 1;
                next = 15;
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 15: {
            u8 attributes;

            CARDGetAttributes(_memcardStatusPtr->param, _memcardStatusPtr->file.fileNo, &attributes);
            attributes |= 0x18;
            _memcardSetRequestResult(CARDSetAttributesAsync(_memcardStatusPtr->param,
                                                            _memcardStatusPtr->file.fileNo, attributes,
                                                            0));
            _memcardStatusPtr->task = 16;
            break;
        }

        case 16:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 16;
                break;
            case 0:
                next = 17;
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 17:
            _memcardStatusPtr->task = fn_801CC508();
            break;

        case 18:
            _memcardSetRequestResult(CARDWriteAsync(&_memcardStatusPtr->file, _memcardStatusPtr->buf50,
                                                    _memcardStatusPtr->unk40 != 0 ? 0x4000 : 0x6000, 0, 0));
            _memcardStatusPtr->task = 19;
            break;

        case 19:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 19;
                break;
            case 0:
                if (_memcardStatusPtr->unk40 != 0) {
                    next = 0x2C;
                } else {
                    next = 20;
                }
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 20: {
            u8* header = (u8*)_memcardStatusPtr->buf50;

            memset(header, 0, 0x2000);
            header[0] = 1;
            header[1] = 1;
            header[2] = 1;
            header[3] = 0;
            _memcardStatusPtr->index = 0;
            _memcardStatusPtr->task = 21;
            break;
        }

        case 21:
            _memcardSetRequestResult(CARDWriteAsync(&_memcardStatusPtr->file, _memcardStatusPtr->buf50, 0x2000,
                                                    _memcardSaveOffset(_memcardStatusPtr->index), 0));
            _memcardStatusPtr->task = 22;
            break;

        case 22:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 22;
                break;
            case 0:
                if ((u32)++_memcardStatusPtr->index < 2) {
                    next = 21;
                } else {
                    next = 23;
                }
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 23: {
            s32 i;

            result = CARDGetStatus(_memcardStatusPtr->param, _memcardStatusPtr->file.fileNo,
                                   &_memcardStatusPtr->stat);
            if (result == 0) {
                CARDSetCommentAddress(&_memcardStatusPtr->stat, 0);
                CARDSetIconAddress(&_memcardStatusPtr->stat, 0x40);
                CARDSetBannerFormat(&_memcardStatusPtr->stat, 2);
                CARDSetIconAnim(&_memcardStatusPtr->stat, 0);
                for (i = 0; i < 8; i++) {
                    CARDSetIconFormat(&_memcardStatusPtr->stat, i, 1);
                    CARDSetIconSpeed(&_memcardStatusPtr->stat, i, 1);
                }
                _memcardSetRequestResult(CARDSetStatusAsync(_memcardStatusPtr->param,
                                                            _memcardStatusPtr->file.fileNo,
                                                            &_memcardStatusPtr->stat, 0));
                next = 24;
            } else {
                _memcardStatusPtr->msg = result;
                next = 0x2B;
            }
            _memcardStatusPtr->task = next;
            break;
        }

        case 24:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 24;
                break;
            case 0:
                if (_memcardStatusPtr->state == 9) {
                    _memcardDuplicateSaveData_multi((u8*)_memcardStatusPtr->buf50 + 8);
                    _memcardStatusPtr->unk2C = 0;
                    _memcardStatusPtr->index = -1;
                    next = 0x25;
                } else {
                    _memcardStatusPtr->msg = 11;
                    _memcardStatusPtr->result = 2;
                    next = 0x2C;
                }
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 25:
            _memcardStatusPtr->task = 26;
            break;

        case 26:
            _memcardSetRequestResult(CARDReadAsync(&_memcardStatusPtr->file, _memcardStatusPtr->buf50, 0x4000, 0,
                                                   0));
            _memcardStatusPtr->task = 27;
            break;

        case 27:
            _memcardStatusPtr->task = _memcardCheckIconFile();
            break;

        case 28:
            _memcardStatusPtr->task = _memcardBeginHeaderRead();
            break;

        case 29:
            _memcardSetRequestResult(CARDReadAsync(&_memcardStatusPtr->file,
                                                   (u8*)_memcardStatusPtr->buf50 +
                                                       (_memcardStatusPtr->index * 0x200 + 0x28000),
                                                   0x200, _memcardSaveOffset(_memcardStatusPtr->index), 0));
            _memcardStatusPtr->task = 30;
            break;

        case 30:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 30;
                break;
            case 0:
                if ((u32)++_memcardStatusPtr->index < 2) {
                    next = 29;
                } else {
                    next = 31;
                }
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 31:
            _memcardStatusPtr->task = _memcardExamineHeader();
            break;

        case 32:
            _memcardStatusPtr->task = 33;
            break;

        case 33:
            _memcardSetRequestResult(CARDReadAsync(&_memcardStatusPtr->file, _memcardStatusPtr->buf50, 0x28000,
                                                   _memcardSaveOffset(_memcardStatusPtr->index), 0));
            _memcardStatusPtr->task = 34;
            break;

        case 34:
            result = _memcardPollResult();
            switch (result) {
            case -1:
                next = 34;
                break;
            case 0:
                next = 35;
                break;
            default:
                _memcardStatusPtr->msg = result;
                next = 0x2B;
                break;
            }
            _memcardStatusPtr->task = next;
            break;

        case 35:
            _memcardStatusPtr->task = _memcardExamineDataPack();
            break;

        case 36:
            _memcardStatusPtr->task = _memcardMergeDataPack();
            break;

        case 37:
            _memcardStatusPtr->task = _memcardSaveSetup();
            break;

        case 38: {
            s32 length = _memcardStatusPtr->state == 8 ? 0x26000 : 0x28000;

            GSgfxResetDisable();
            _memcardSetRequestResult(CARDWriteAsync(&_memcardStatusPtr->file, _memcardStatusPtr->buf50, length,
                                                    _memcardSaveOffset(_memcardStatusPtr->index), 0));
            _memcardStatusPtr->busyCount = 0;
            _memcardStatusPtr->task = 0x27;
            break;
        }

        case 39:
            _memcardStatusPtr->task = _memcardCheckWrite();
            break;

        case 40:
            if (_memcardStatusPtr->timer-- != 0) {
                _memcardStatusPtr->cardResult = -1;
                next = 0x28;
            } else {
                _memcardStatusPtr->cardResult = 0;
                next = 0x29;
            }
            _memcardStatusPtr->task = next;
            break;

        case 41:
            if (gbaCommandIsConnected(2) == 0) {
                next = 0x2B;
            } else {
                _memcardSetRequestResult(CARDWriteAsync(&_memcardStatusPtr->file,
                                                        (u8*)_memcardStatusPtr->buf50 + 0x26000, 0x2000,
                                                        _memcardSaveOffset(_memcardStatusPtr->index) + 0x26000,
                                                        0));
                _memcardStatusPtr->busyCount /= 19;
                _memcardStatusPtr->busyCount++;
                _memcardStatusPtr->mounted = 0;
                next = 0x2A;
            }
            _memcardStatusPtr->task = next;
            break;

        case 42:
            _memcardStatusPtr->task = _memcardCheckLastWrite();
            break;

        case 43:
            _memcardStatusPtr->result = -1;
            _memcardStatusPtr->task = 0x2C;
            break;

        case 44:
            _memcardStatusPtr->task = _memcardEndAccess();
            break;

        case 45:
            _memcardStatusPtr->task = _memcardFinishTask();
            break;

        case 46:
            _memcardStatusPtr->task = _memcardAsk(8, 0x2F);
            break;

        case 47:
            if (_memcardStatusPtr->msg != 0) {
                _memcardStatusPtr->result = 5;
            }
            _memcardStatusPtr->task = 0x32;
            break;

        case 48:
        case 49:
        case 50:
            return;
        }
    } while (_memcardStatusPtr->cardResult != -1);
}

#pragma pop

#pragma push
#pragma dont_inline on
static s32 _memcardMergeDataPack(void) {
    void* data;
    u8* pack = (u8*)_memcardStatusPtr->buf50 + 8;
    data = _memcardGetMultiSaveDataToSTRUCT(pack, 1);
    switch (_memcardStatusPtr->state) {
    case 9:
        _memcardDuplicateSaveData_multi(pack);
        _memcardStoreSaveData_multi(pack);
        break;
    case 13: {
        void* save = savedataGetStatus(0, 0xE);
        memcpy(_memcardGetMultiSaveDataToSTRUCT(pack, 0xE), save, 0x364);
        break;
    }
    }
    gamedatasaveSetStatus(data, 9, (u8)gamedatasaveGetStatus(0, 9));
    gamedatasaveSetStatus(data, 0xA, (u8)gamedatasaveGetStatus(0, 0xA));
    gamedatasaveSetStatus(data, 0xB, (u8)gamedatasaveGetStatus(0, 0xB));
    return 0x25;
}
#pragma pop

#pragma push
#pragma opt_propagation off
static s32 _memcardExamineDataPack(void) {
    u8 valid;
    u8* pack = (u8*)_memcardStatusPtr->buf50;
    s32 sum;
    valid = _memcard_Decryption(pack + 8);
    if (valid) {
        void* data = pack + 8;
        sum = pack[0] + pack[1];
        sum += pack[2];
        sum += pack[3];
        sum += pack[4];
        sum += pack[5];
        sum += pack[6];
        sum += pack[7];
        u8 checked;
        if (((MemcardPackHeader*)data)->sizes[SectionSystem] == sizeof(GamedataSaveRecord)) {
            if (sum == gamedatasaveGetStatus(_memcardGetMultiSaveDataToSTRUCT(data, 1), 0xD)) {
                checked = 1;
            } else {
                checked = 0;
            }
        } else {
            checked = 1;
        }
        valid = checked;
    }
    if (valid) {
        _memcardGetMultiSaveDataToSTRUCT(pack + 8, 1);
    }
    if (valid) {
        if (_memcardStatusPtr->state != 3) {
            _memcardStatusPtr->unk2C = *(s32*)(pack + 4);
            if (_memcardStatusPtr->limit > _memcardStatusPtr->unk2C) {
                _memcardStatusPtr->unk2C = _memcardStatusPtr->limit;
                _memcardStatusPtr->msg = 5;
                switch (_memcardStatusPtr->state) {
                case 1: case 2:
                    _memcardStoreSaveData_multi(pack + 8);
                    _memcardStatusPtr->nextTask = 0x25;
                    break;
                default:
                    _memcardStatusPtr->nextTask = 0x24;
                }
                return 0x30;
            }
        }
        switch (_memcardStatusPtr->state) {
        case 1: case 2: case 3: {
            s32 next;
            _memcardStoreSaveData_multi(pack + 8);
            _memcardStatusPtr->msg = 0xC;
            _memcardStatusPtr->result = 3;
            next = 0x2C;
            if (_memcardStatusPtr->unk40 != 0) {
                next = 0x11;
            }
            return next;
        }
        }
        return 0x24;
    }
    s32* block = (s32*)(_memcardStatusPtr->index * 0x200 + 0x28000 + _memcardStatusPtr->buf50);
    block[1] = 0;
    return 0x1F;
}
#pragma pop

#pragma push
static s32 _memcardExamineHeader()
{
    s32 i;
    s32 selected;
    MemcardSaveHeader *header;
    s32 sequence;
    sequence=0;
    selected=-1;
    for(i=0;i<2;i++) {
        header=_memcardGetHeader(0x28000+i*0x200);
        if(_memcardHeaderValid(header)==0) {
            _memcardStatusPtr->msg=0x13;
            return 0x2B;
        }
        if(header->sequence>sequence) {
            sequence=header->sequence;
            selected=i;
            if(header->sequence>_memcardStatusPtr->limit) _memcardStatusPtr->limit=header->sequence;
        }
    }
    _memcardStatusPtr->index=selected;
    switch(_memcardStatusPtr->state) {
    case 10:
    case 11:
        _memcardDuplicateSaveData_multi((u8 *)_memcardStatusPtr->buf50+8);
        _memcardStatusPtr->unk2C=_memcardStatusPtr->limit;
        return 0x25;
    case 1:case 2:case 3:case 5:case 7:case 9:case 13:
        if(selected==-1) {
            if(_memcardStatusPtr->limit>0) {
                switch(_memcardStatusPtr->state) {
                case 9:return 0xB;
                case 3:break;
                default:
                    _memcardStatusPtr->msg=0x11;
                    return 0x2B;
                }
            }
            switch(_memcardStatusPtr->state) {
            case 1:case 2:case 3:
                _memcardStatusPtr->msg=0xC;
                _memcardStatusPtr->result=1;
                if(_memcardStatusPtr->unk40) return 0x11;
                return 0x2C;
            }
            memset(_memcardStatusPtr->buf50,0,0x28000);
            {
                u8 *dst=(u8 *)_memcardStatusPtr->buf50+8;
                _memcard_new_saveDataCrateFlag=0;
                _memcardDuplicateSaveData_multi(dst);
            }
            _memcard_new_saveDataCrateFlag=1;
            _memcardStatusPtr->unk2C=0;
            _memcardStatusPtr->index=-1;
            return 0x24;
        }
        return 0x20;
    case 4:case 6:case 8:
        if(selected!=-1 && sequence<=_memcardStatusPtr->unk2C) {
            header=(MemcardSaveHeader *)((u8 *)_memcardStatusPtr->buf50+(selected*0x200+0x28000));
            u64 id=memcardCurrentID(0);
            decryptMemcardHeader(header->payload);
            if(id==memcardCurrentID(header->payload)) {
                if(_memcardStatusPtr->state==6) {
                    _memcardStatusPtr->index=selected;
                    return 0x20;
                }
                _memcardDuplicateSaveData_multi((u8 *)_memcardStatusPtr->buf50+8);
                return 0x25;
            }
        }
        break;
    }
    _memcardStatusPtr->msg=0x13;
    return 0x2B;
}

#pragma pop

extern "C" {
char* strcpy(char*, const char*);
s32 fn_801CC508() {
    OSCalendarTime calendar;
    OSTicksToCalendarTime(OSGetTime(), &calendar);
    char* buffer = (char*)_memcardStatusPtr->buf50;
    memset(buffer, 0, 0x6000);
    switch (pokecoloGetCountryCode()) {
    case 0:
        strcpy(buffer, "ポケモンＸＤ");
        strcpy(buffer + 0x20, "セーブファイル Yy/Mm/Dd");
        buffer[0x2F] = (calendar.year / 10) % 10 + '0';
        buffer[0x30] = calendar.year % 10 + '0';
        buffer[0x32] = ((calendar.mon + 1) / 10) % 10 + '0';
        buffer[0x33] = (calendar.mon + 1) % 10 + '0';
        buffer[0x35] = (calendar.mday / 10) % 10 + '0';
        buffer[0x36] = calendar.mday % 10 + '0';
        break;
    case 1:
    case 2:
        strcpy(buffer, "POKeMON XD");
        strcpy(buffer + 0x20, "SAVE FILE Mm/Dd/20Yy");
        buffer[3] = 0xE9;
        buffer[0x32] = (calendar.year / 10) % 10 + '0';
        buffer[0x33] = calendar.year % 10 + '0';
        buffer[0x2A] = ((calendar.mon + 1) / 10) % 10 + '0';
        buffer[0x2B] = (calendar.mon + 1) % 10 + '0';
        buffer[0x2D] = (calendar.mday / 10) % 10 + '0';
        buffer[0x2E] = calendar.mday % 10 + '0';
        break;
    }
    memcpy(buffer + 0x40, _memcardBannerImage, sizeof(_memcardBannerImage));
    memcpy(buffer + 0x1840, _memcardIconImage, sizeof(_memcardIconImage));
    for (u32 i=0; i<0xE90; ++i) *(u32*)(buffer + 0x3A40) += ((u32*)buffer)[i];
    return 0x12;
}
}

static s32 _memcardCardOpen(void) {
    s32 freeBytes;
    s32 freeFiles;
    MemcardCardStat stat2;
    s32 status;
    CARDFreeBlocks(*(s32*)((u8*)_memcardStatusPtr + 0x14), &freeBytes, &freeFiles);
    switch (pokecoloGetCountryCode()) {
    case 0: {
        void* info;
        s32 chan;
        s32 result;
        s32 i;
        MemcardCardStat stat;
        chan = *(s32*)((u8*)_memcardStatusPtr + 0x14);
        info = (u8*)_memcardStatusPtr + 0x8C;
        i = 0;
            for (;;) {
                result = CARDFastOpen(chan, i, info);
                if (result == 0) {
                    result = CARDGetStatus(chan, i, &stat);
                    u8 found;
                    found = _memcardIsXDSave(&stat,result);
                    if (found) {
                        result = 0;
                        break;
                    }
                }
                ++i;
                if (i >= 0x7F) {
                    if (result == 0) result = -4;
                    break;
                }
            }
        status = result;
        break;
    }
    case 1:
    case 2: {
        status = _memcardFindSave();
        break;
    }
    }
    switch (status) {
    case 0: {
        _memcardStatusPtr->unk3E = 1;
        status = CARDGetStatus(*(s32*)((u8*)_memcardStatusPtr + 0x14), *(s32*)((u8*)_memcardStatusPtr + 0x90), &stat2);
        if (status != 0) goto fail;
        if (stat2.commentAddr + 0x10000 != 0xFFFF) {
            if (_memcardStatusPtr->state == 0xC) {
                _memcardStatusPtr->msg = 2;
                _memcardStatusPtr->nextTask = 0xB;
                return 0x30;
            }
            s32 ret = 0x19;
            if (_memcardStatusPtr->state == 3) ret = 0x1C;
            return ret;
        }
        status = -4;
        freeBytes += 0x56000;
        freeFiles += 1;
    }
    // fall through
    case -4:
        switch (_memcardStatusPtr->state) {
        case 1:
            if (freeBytes < 0x56000) { status = -9; goto fail; }
            if (freeFiles < 1) { status = -8; goto fail; }
            _memcardStatusPtr->msg = 6;
            _memcardStatusPtr->nextTask = 0xA;
            return 0x30;
        case 9:
            _memcardStatusPtr->msg = 2;
            _memcardStatusPtr->nextTask = 0xB;
            return 0x30;
        }
        // fall through
    default:
    fail:
        _memcardStatusPtr->msg = status;
        return 0x2B;
    }
}

static void _memcardCallback(long, long) {
    _memcardStatusPtr->callbackDone = 1;
}

#define MEMCARD_STORE(idx, section, max)                                     \
    dst = _memcardGetMultiSaveDataToSTRUCT(arg, idx);                        \
    src = savedataGetStatus(_memcardStatusPtr->saveData, idx);               \
    size = header->sizes[section];                                           \
    if (size > (max)) {                                                      \
        size = (max);                                                        \
    }                                                                        \
    memcpy(src, dst, size)

#define MEMCARD_STORE2(dst3, idx, section, max)                              \
    dst3 = (u8*)_memcardGetMultiSaveDataToSTRUCT(arg, idx);                  \
    src = savedataGetStatus(_memcardStatusPtr->saveData, idx);               \
    size = header->sizes[section];                                           \
    if (size > (max)) {                                                      \
        size = (max);                                                        \
    }                                                                        \
    memcpy(src, dst3, size)

void _memcardStoreSaveData_multi(void* arg) {
    const MemcardPackHeader* header = (const MemcardPackHeader*)arg;
    void* dst;
    u8* dst2;
    u8* dst3;
    u8* dst4;
    u8* dst5;
    void* src;
    u32 size;
    MEMCARD_STORE(1, SectionSystem, sizeof(GamedataSaveRecord));
    MEMCARD_STORE(2, SectionHero, sizeof(Hero));
    dst = _memcardGetMultiSaveDataToSTRUCT(arg, 3);
    src = savedataGetStatus(_memcardStatusPtr->saveData, 3);
    size = (u32)header->pcBoxSizeHigh << 16;
    size += header->sizes[SectionPcBox];
    if (size > sizeof(PCBOX)) {
        size = sizeof(PCBOX);
    }
    memcpy(src, dst, size);
    MEMCARD_STORE(0xA, SectionMailbox, sizeof(Mailbox));
    MEMCARD_STORE(0xB, SectionSodateya, sizeof(Sodateya));
    MEMCARD_STORE(0xC, SectionMemo, sizeof(Memo));
    MEMCARD_STORE(0xE, SectionTool, 0x364);
    MEMCARD_STORE(0xF, SectionDarkPokemon, 0x2400);
    dst2 = (u8*)_memcardGetMultiSaveDataToSTRUCT(arg, 0x17);
    size = header->sizes[SectionFlags];
    if (size == 0x6B4) {
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 4), dst2, header->flagLevel0Size);
        dst2 += header->flagLevel0Size;
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 5), dst2, header->flagLevel1Size);
        dst2 += header->flagLevel1Size;
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 6), dst2, header->flagLevel2Size);
        dst2 += header->flagLevel2Size;
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 0x18), dst2, header->battleDiskFlagsSize);
        dst2 += header->battleDiskFlagsSize;
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 0x1B), dst2, header->bingoFlagsSize);
    } else {
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 0x17), dst2, size);
    }
    MEMCARD_STORE2(dst3, 0x10, SectionExRibbon, 0xB);
    MEMCARD_STORE2(dst4, 0x16, SectionFloor, 0xC800);
    MEMCARD_STORE2(dst5, 0x15, SectionRelive, sizeof(CReliveHall));
    _memcardGetMultiSaveDataToSTRUCT(arg, 0x11);
    _memcardGetMultiSaveDataToSTRUCT(arg, 0x12);
    _memcardGetMultiSaveDataToSTRUCT(arg, 0x13);
    _memcardGetMultiSaveDataToSTRUCT(arg, 0x14);
}

extern "C" {
u32 floorGetNextFloorID();
s32 floorMakeSaveData(void**, u32*);
void* __copy(void*,const void*,u32);
}

template <unsigned N> struct MemcardWords { u32 words[N]; };

#pragma push
#pragma peephole off
void _memcardDuplicateSaveData_multi(void* buffer) {
    u32 floorSize;
    void* floorData;
    s8 order[SectionCount];
    MemcardSavePack* pack = (MemcardSavePack*)buffer;
    MemcardPackHeader* header = &pack->header;
    u16* words = (u16*)buffer;
    if (_memcardStatusPtr->state == 11) {
        u32 next = floorGetNextFloorID();
        gamedatasaveSetStatus(0, 5, next);
    }

    s32 i, word;
    for (i = 0; i < 4; i++) {
        _memcard_encrypt_key[i] = HSD_Rand();
    }
    for (word = 0; word < (s32)(sizeof(MemcardSavePack) / sizeof(u16)); word += 4) {
        for (i = 0; i < 4; ++i) {
            words[word + i] += _memcard_encrypt_key[i];
        }
        advanceMemcardKey();
    }

    header->sizes[SectionSystem] = sizeof(GamedataSaveRecord);
    header->sizes[SectionHero] = sizeof(Hero);
    header->sizes[SectionPcBox] = sizeof(PCBOX);
    header->pcBoxSizeHigh = 0;
    header->sizes[SectionMailbox] = sizeof(Mailbox);
    header->sizes[SectionSodateya] = sizeof(Sodateya);
    header->sizes[SectionMemo] = sizeof(Memo);
    header->sizes[SectionTool] = 0x364;
    header->sizes[SectionDarkPokemon] = 0x2400;
    header->sizes[SectionFlags] = 0x6B4;
    header->sizes[SectionExRibbon] = 0xB;
    header->sizes[SectionFloor] = 0xC800;
    header->sizes[SectionYobi1] = 0x400;
    header->sizes[SectionYobi2] = 0x800;
    header->sizes[SectionYobi3] = 0x1000;
    header->sizes[SectionYobi4] = 0x2000;
    header->sizes[SectionRelive] = sizeof(CReliveHall);
    header->key[0] = HSD_Rand();
    header->key[1] = HSD_Rand();
    header->key[2] = HSD_Rand();
    header->key[3] = HSD_Rand();
    for (s16 i = 0; i < SectionCount - 1; ++i) {
        order[i] = i + 1;
    }
    header->offsets[SectionSystem].low = 0;
    order[SectionCount - 1] = -1;
    header->offsets[SectionSystem].high = 0;
    *(GamedataSaveRecord*)pack->payload = *(const GamedataSaveRecord*)savedataGetStatus(0, 1);

    u32 offset = 0xA0;
    s16 count = SectionCount - 1;
    while (count != 0) {
        s16 selected = (s32)(u16)HSD_Rand() % count;
        s8 section = order[selected];
        switch (section) {
        case SectionSystem:
            break;
        case SectionHero: {
            if (_memcardStatusPtr->state != 8 && _memcardStatusPtr->state != 13 &&
                _memcardStatusPtr->state != 7 && _memcard_anySaveOFF_Flag == 0) {
                Hero::getHeroPtr()->setRestertPos();
            }
            u8* dst = pack->setSectionOffset(SectionHero, offset);
            memcpy(dst, savedataGetStatus(0, 2), sizeof(Hero));
            offset += 0x990;
            break;
        }
        case SectionPcBox: {
            PCBOX* dst = (PCBOX*)pack->setSectionOffset(SectionPcBox, offset);
            *dst = *(const PCBOX*)savedataGetStatus(0, 3);
            offset += 0xBC60;
            break;
        }
        case SectionMailbox: {
            Mailbox* dst = (Mailbox*)pack->setSectionOffset(SectionMailbox, offset);
            *dst = *(const Mailbox*)savedataGetStatus(0, 10);
            offset += 0x60;
            break;
        }
        case SectionSodateya: {
            u8* dst = pack->setSectionOffset(SectionSodateya, offset);
            *(Sodateya*)dst = *(const Sodateya*)savedataGetStatus(0, 11);
            offset += 0xE0;
            break;
        }
        case SectionMemo: {
            Memo* dst = (Memo*)pack->setSectionOffset(SectionMemo, offset);
            *dst = *(const Memo*)savedataGetStatus(0, 12);
            offset += 0x1790;
            break;
        }
        case SectionTool: {
            u8* dst = pack->setSectionOffset(SectionTool, offset);
            u8* src = (u8*)savedataGetStatus(0, 14);
            *(MemcardWords<216>*)dst = *(MemcardWords<216>*)src;
            offset += 0x380;
            dst[0x360] = src[0x360];
            break;
        }
        case SectionDarkPokemon: {
            u8* dst = pack->setSectionOffset(SectionDarkPokemon, offset);
            *(MemcardWords<2304>*)dst = *(MemcardWords<2304>*)savedataGetStatus(0, 15);
            offset += 0x2410;
            break;
        }
        case SectionFlags: {
            u8* dst = pack->setSectionOffset(SectionFlags, offset);
            header->flagLevel0Size = (u32)savedataGetStatus(0, 7) * 4;
            header->flagLevel1Size = (u32)savedataGetStatus(0, 8) * 4;
            header->flagLevel2Size = (u32)savedataGetStatus(0, 9) * 4;
            header->battleDiskFlagsSize = (u32)savedataGetStatus(0, 25) * 4;
            header->bingoFlagsSize = (u32)savedataGetStatus(0, 28) * 4;
            u8* src = (u8*)savedataGetStatus(0, 23);
            *(MemcardWords<8>*)dst = *(MemcardWords<8>*)src;
            *(MemcardWords<32>*)(dst + 0x20) = *(MemcardWords<32>*)(src + 0x20);
            *(MemcardWords<384>*)(dst + 0xA0) = *(MemcardWords<384>*)(src + 0xA0);
            offset += 0x6D0;
            *(MemcardWords<5>*)(dst + 0x6A0) = *(MemcardWords<5>*)(src + 0x6A0);
            break;
        }
        case SectionExRibbon: {
            u8* dst = pack->setSectionOffset(SectionExRibbon, offset);
            __copy(dst, savedataGetStatus(0, 16), 11);
            offset += 0x20;
            break;
        }
        case SectionFloor: {
            if (_memcardStatusPtr->state != 8 && _memcardStatusPtr->state != 13 &&
                _memcardStatusPtr->state != 7 && _memcard_anySaveOFF_Flag == 0) {
                floorMakeSaveData(&floorData, &floorSize);
            }
            void* dst = pack->setSectionOffset(SectionFloor, offset);
            void* src = savedataGetStatus(0, 22);
            if (_memcardStatusPtr->state != 8 && _memcardStatusPtr->state != 13 &&
                _memcardStatusPtr->state != 7 && _memcard_anySaveOFF_Flag == 0) {
                memcpy(src, floorData, floorSize);
                GSmemFree(floorData);
            }
            if (_memcard_anySaveOFF_Flag == 0) {
                memcpy(dst, src, 0xC800);
            } else {
                memset(dst, 0, 0xC800);
            }
            offset += 0xC810;
            break;
        }
        case SectionYobi1:
            pack->setSectionOffset(SectionYobi1, offset);
            offset += 0x410;
            break;
        case SectionYobi2:
            pack->setSectionOffset(SectionYobi2, offset);
            offset += 0x810;
            break;
        case SectionYobi3:
            pack->setSectionOffset(SectionYobi3, offset);
            offset += 0x1010;
            break;
        case SectionYobi4:
            pack->setSectionOffset(SectionYobi4, offset);
            offset += 0x2010;
            break;
        case SectionRelive: {
            CReliveHall* dst = (CReliveHall*)pack->setSectionOffset(SectionRelive, offset);
            *dst = *(const CReliveHall*)savedataGetStatus(0, 21);
            offset += 0x22B0;
            break;
        }
        }
        for (; selected < count; ++selected) {
            order[selected] = order[selected + 1];
        }
        --count;
    }
}

#pragma pop

#define MEMCARD_MULTI_ADD(section)                                           \
    {                                                                        \
        u32 hi = header->offsets[section].high;                              \
        u32 lo = header->offsets[section].low;                               \
        data = (hi << 16) + data;                                            \
        data = lo + data;                                                    \
    }

#pragma opt_dead_assignments off
static void* _memcardGetMultiSaveDataToSTRUCT(void* base, long index) {
    const MemcardSavePack* pack = (const MemcardSavePack*)base;
    const MemcardPackHeader* header = &pack->header;
    u32 data = (u32)pack->payload;
    switch (index) {
    case 1:
        MEMCARD_MULTI_ADD(SectionSystem)
        break;
    case 2:
        MEMCARD_MULTI_ADD(SectionHero)
        break;
    case 3:
        MEMCARD_MULTI_ADD(SectionPcBox)
        break;
    case 0x17:
        MEMCARD_MULTI_ADD(SectionFlags)
        break;
    case 0xA:
        MEMCARD_MULTI_ADD(SectionMailbox)
        break;
    case 0xB:
        MEMCARD_MULTI_ADD(SectionSodateya)
        break;
    case 0xC:
        MEMCARD_MULTI_ADD(SectionMemo)
        break;
    case 0xE:
        MEMCARD_MULTI_ADD(SectionTool)
        break;
    case 0xF:
        MEMCARD_MULTI_ADD(SectionDarkPokemon)
        break;
    case 0x10:
        MEMCARD_MULTI_ADD(SectionExRibbon)
        break;
    case 0x16:
        MEMCARD_MULTI_ADD(SectionFloor)
        break;
    case 0x11:
        MEMCARD_MULTI_ADD(SectionYobi1)
        break;
    case 0x12:
        MEMCARD_MULTI_ADD(SectionYobi2)
        break;
    case 0x13:
        MEMCARD_MULTI_ADD(SectionYobi3)
        break;
    case 0x14:
        MEMCARD_MULTI_ADD(SectionYobi4)
        break;
    case 0x15:
        MEMCARD_MULTI_ADD(SectionRelive)
        break;
    case 0:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xD:
        break;
    }
    return (void*)data;
}
#pragma opt_dead_assignments reset

static u8 _memcardMsgOpen(MEMCARD_MSGTYPE msg) {
    u8 retry = 0;
    u8 confirm = 0;
    s32 yes;
    s32 id;
    switch (msg) {
    case 0:
        return 0;
    case 1:
        id = 0x6A;
        break;
    case 2:
        switch (_memcardStatusPtr->state) {
        case 5:
        case 6:
        case 7:
        case 0xD:
            id = 0x6C;
            break;
        default:
            id = 0x90;
            break;
        }
        break;
    case 3:
        id = 0x84;
        break;
    case 4:
        id = 0x73;
        break;
    case 5:
        id = 0x7B;
        break;
    case 6:
        id = 0x83;
        retry = 1;
        yes = 0;
        break;
    case 7:
        id = 0x71;
        retry = 1;
        yes = 0;
        confirm = 1;
        break;
    case 8:
        id = 0x7A;
        retry = 1;
        yes = 1;
        break;
    case 9:
        id = 0x74;
        break;
    case 10:
        switch (_memcardStatusPtr->state) {
        case 5:
        case 6:
        case 7:
        case 0xD:
            id = 0x6D;
            break;
        default:
            id = 0x91;
            break;
        }
        GSsndPlay(0x1D, 0, 0);
        break;
    case 11:
        id = 0x85;
        break;
    case 12:
        id = 0x81;
        GSsndPlay(0x1D, 0, 0);
        break;
    case 13:
        id = 0x79;
        break;
    case 14:
        id = 0x9B;
        break;
    case 15:
        switch (_memcardStatusPtr->state) {
        case 5:
        case 6:
        case 7:
        case 0xD:
            id = 0x9B;
            break;
        default:
            id = 0x97;
            break;
        }
        break;
    case 16:
        id = 0x72;
        break;
    case 17:
        id = 0x7C;
        if (_memcardStatusPtr->state != 2) {
            winMsgOpen(_memcardStatusPtr->priority, 0x7C, 1, 1);
            id = 0x80;
        }
        break;
    case 18:
        id = 0x7D;
        break;
    case -2:
        id = 0x77;
        break;
    case -3:
        id = 0x70;
        break;
    case -4:
        id = 0x6F;
        break;
    case -5:
        id = 0x76;
        break;
    case -13:
    case -6:
        switch (_memcardStatusPtr->state) {
        case 1:
        case 2:
            id = 0x7E;
            if (_memcardStatusPtr->unk60 == 0x32) {
                break;
            }
        default:
            id = 0x6E;
            break;
        }
        break;
    case -9:
    case -8:
        id = 0x78;
        msgctrlSetValue(0x2F, 0x2B);
        break;
    case 19:
        winMsgOpen(_memcardStatusPtr->priority, 0x7C, 1, 1);
        id = 0x80;
        break;
    default:
        id = 0x6E;
        break;
    }
    winMsgOpen(_memcardStatusPtr->priority, id, 1, 1);
    if (retry) {
        if (menuSubOpenYesNo(0, 0x3C, 0xAA, yes)) {
            retry = 0;
        } else {
            retry = 1;
            if (confirm) {
                winMsgOpen(_memcardStatusPtr->priority, 0xF3, 1, 1);
                if (menuSubOpenYesNo(0, 0x3C, 0xAA, 1)) {
                    retry = 0;
                } else {
                    retry = 1;
                }
            }
        }
    }
    return retry;
}

extern "C" {

void* memcardMemFreeForSavedata(void* p) {
    GSmemFree(p);
    return 0;
}

void* memcardMemAllocForSavedata(void) {
    return GSmemAllocAlign(sizeof(MemcardSavePack), 0x20);
}

void memcardFinalizeTask(void) {
    _memcardFinish();
}

void memcardUnlockWaitGBA(u8 flag) {
    if (_memcardStatusPtr->task == 0x31 && flag != 0) {
        _memcardStatusPtr->task = _memcardStatusPtr->nextTask;
        _memcardStatusPtr->timer = ((HSD_Rand() << 16) | HSD_Rand()) % 0x3C;
        _memcardStatusPtr->timer = _memcardStatusPtr->timer + 1;
        s32 rnd = (u16)HSD_Rand();
        _memcardStatusPtr->timer = _memcardStatusPtr->timer + rnd % 0x3C;
    } else {
        _memcardStatusPtr->msg = 0xF;
        _memcardStatusPtr->task = 0x2B;
    }
}

s32 memcardCheckTaskWaitGBA(void) {
    return _memcardStatusPtr->task == 0x31 ? 1 : 0;
}

u8 memcardIsMemCardValid(void) {
    return _memcardStatusPtr->valid;
}

s32 memcardGetTaskResult(void) {
    if (_memcardStatusPtr->task == 0x30) {
        _memcardStatusPtr->msg = _memcardMsgOpen((MEMCARD_MSGTYPE)_memcardStatusPtr->msg);
        _memcardStatusPtr->task = _memcardStatusPtr->nextTask;
    }
    if (_memcardStatusPtr->task != 0x32) {
        return 0;
    }
    return _memcardStatusPtr->result;
}

void memcardSetupTask(s32 state, s32 priority, s32 param) {
    if (_memcardStatusPtr->state != 0) {
        do {
            GSthreadSwitch();
        } while (_memcardPollTask() == 0);
        _memcardFinish();
    }
    if (priority == 0) {
        priority = 2;
    }
    _memcardStatusPtr->state = state;
    _memcardStatusPtr->param = param;
    _memcardStatusPtr->priority = priority;
    _memcardStatusPtr->result = 0;
    _memcardStatusPtr->task = 0;
    _memcardStatusPtr->msg = 0;
    _memcardStatusPtr->unk3E = 0;
    _memcardStatusPtr->buf50 = (u8*)GSmemAllocAlign(0x28400, 0x20);
    _memcardStatusPtr->buf54 = (u8*)GSmemAllocAlign(0xA000, 0x20);
    _memcardStatusPtr->gapp = GSgappCreate(1, 0x17, 0, _memcardJobMain);
    _memcardStatusPtr->saveData = savedataGetStatus(0, 0);
}

s32 memcardTaskCall(s32 state, s32 priority, s32 param) {
    s32 result;
    if (state == 1) {
        memset(savedataGetStatus(0, 0), 0, 0x27FD0);
        menuCBBios_RuleEditSaveON(0);
    }
    if (state == 0xE) {
        state = 4;
        _memcard_anySaveOFF_Flag = 1;
    } else {
        _memcard_anySaveOFF_Flag = 0;
    }
    _memcardStart(state, priority, param);
    do {
        GSthreadSwitch();
        result = _memcardPollTask();
    } while (result == 0);
    _memcardFinish();
    return result;
}

void memcardInitialize(void)
{
    if (!_memcardInitializeFlag) {
        u32 lo;
        u16 hi;
        CARDInit();
        lo = HSD_Rand();
        hi = HSD_Rand();
        _memcardStatusPtr = (MemcardStatus*)(_memcardStatusBuf + (((hi << 16) | lo) & 0xf8));
        _memcardStatusPtr->state = 0;
        _memcardStatusPtr->buf50 = 0;
        _memcardStatusPtr->buf54 = 0;
        _memcardStatusPtr->unk2C = 0;
        _memcardInitializeFlag = 1;
    }
}

}
