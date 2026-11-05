#include <dolphin/types.h>
#include <libc/stddef.h>

#pragma force_active on
#pragma pack(1)

/* Packed battle commands consumed by WazaSequenceTbl in fightSeqWSWaza.cpp.
 * Operand widths follow the WS_* handlers. 0xFF addresses select UserWork. */
#define SEQ_USER_WORK(offset) ((void*)(0xFF000000UL | (offset)))

enum {
    WS_EFFECT_WAIT = 0x0B,
    WS_HP_DEC = 0x0C,
    WS_HP_DEC_WAIT = 0x0D,
    WS_MESSAGE = 0x11,
    WS_MESSAGE_WAIT = 0x13,
    WS_MESSAGE_TBL = 0x14,
    WS_SETVALUE = 0x2F,
    WS_SET32BIT = 0x36,
    WS_WAIT = 0x3A,
    WS_WAZAEND = 0x3E,
    WS_FIGHT_EFFECT = 0x46,
    WS_WKC_ACT = 0x4A,
    WS_STATUS_RECOVER = 0x76,
    WS_CONDITION_GAUGE = 0x99,
    WS_BALL_THROW = 0xF0,
    WS_ADD_POKE = 0xF1,
    WS_ITEMEND = 0xF7,
    WS_GETEND = 0xF8,
};

typedef struct Seq_EFFECT_WAIT { u8 opcode; u8 operand01; } Seq_EFFECT_WAIT;
typedef struct Seq_HP_DEC { u8 opcode; u8 operand01; } Seq_HP_DEC;
typedef struct Seq_HP_DEC_WAIT { u8 opcode; u8 operand01; } Seq_HP_DEC_WAIT;
typedef struct Seq_MESSAGE { u8 opcode; u32 operand01; } Seq_MESSAGE;
typedef struct Seq_MESSAGE_WAIT { u8 opcode; u16 operand01; } Seq_MESSAGE_WAIT;
typedef struct Seq_MESSAGE_TBL { u8 opcode; void* operand01; } Seq_MESSAGE_TBL;
typedef struct Seq_SETVALUE { u8 opcode; void* operand01; u8 operand05; } Seq_SETVALUE;
typedef struct Seq_SET32BIT { u8 opcode; void* operand01; u32 operand05; } Seq_SET32BIT;
typedef struct Seq_WAIT { u8 opcode; u16 operand01; } Seq_WAIT;
typedef struct Seq_WAZAEND { u8 opcode; } Seq_WAZAEND;
typedef struct Seq_FIGHT_EFFECT { u8 opcode; u8 operand01; u8 operand02; u32 operand03; } Seq_FIGHT_EFFECT;
typedef struct Seq_WKC_ACT { u8 opcode; u8 operand01; u8 operand02; } Seq_WKC_ACT;
typedef struct Seq_STATUS_RECOVER { u8 opcode; } Seq_STATUS_RECOVER;
typedef struct Seq_CONDITION_GAUGE { u8 opcode; u8 operand01; } Seq_CONDITION_GAUGE;
typedef struct Seq_BALL_THROW { u8 opcode; } Seq_BALL_THROW;
typedef struct Seq_ADD_POKE { u8 opcode; void* operand01; } Seq_ADD_POKE;
typedef struct Seq_ITEMEND { u8 opcode; } Seq_ITEMEND;
typedef struct Seq_GETEND { u8 opcode; } Seq_GETEND;

typedef struct ItemBallTbl_Stream {
    u8* entries[13];
} ItemBallTbl_Stream;
extern ItemBallTbl_Stream ItemBallTbl;

typedef struct ItemNormalTbl_Stream {
    u8* entries[8];
} ItemNormalTbl_Stream;
extern ItemNormalTbl_Stream ItemNormalTbl;

typedef struct ItemFightTbl_Stream {
    u8* entries[1];
} ItemFightTbl_Stream;
extern ItemFightTbl_Stream ItemFightTbl;

typedef struct ITEM_MonsterBall_Stream {
    Seq_BALL_THROW command000;
} ITEM_MonsterBall_Stream;
extern ITEM_MonsterBall_Stream ITEM_MonsterBall;

typedef struct ITEM_MonsGetSuccess_Stream {
    Seq_ADD_POKE command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_GETEND command003;
} ITEM_MonsGetSuccess_Stream;
extern ITEM_MonsGetSuccess_Stream ITEM_MonsGetSuccess;

typedef struct ITEM_MonsGetFail_Stream {
    Seq_ITEMEND command000;
} ITEM_MonsGetFail_Stream;
extern ITEM_MonsGetFail_Stream ITEM_MonsGetFail;

typedef struct ITEM_Normal_Stream {
    Seq_SETVALUE command000;
    Seq_WKC_ACT command001;
    Seq_WAZAEND command002;
} ITEM_Normal_Stream;
extern ITEM_Normal_Stream ITEM_Normal;

typedef struct ITEM_HPKaifuku_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_STATUS_RECOVER command002;
    Seq_SET32BIT command003;
    Seq_FIGHT_EFFECT command004;
    Seq_EFFECT_WAIT command005;
    Seq_CONDITION_GAUGE command006;
    Seq_HP_DEC command007;
    Seq_MESSAGE command008;
    Seq_MESSAGE_WAIT command009;
    Seq_HP_DEC_WAIT command010;
    Seq_EFFECT_WAIT command011;
    Seq_SETVALUE command012;
    Seq_WKC_ACT command013;
    Seq_ITEMEND command014;
} ITEM_HPKaifuku_Stream;
extern ITEM_HPKaifuku_Stream ITEM_HPKaifuku;

typedef struct ITEM_ConditionKaifuku_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_STATUS_RECOVER command002;
    Seq_FIGHT_EFFECT command003;
    Seq_EFFECT_WAIT command004;
    Seq_CONDITION_GAUGE command005;
    Seq_MESSAGE_TBL command006;
    Seq_MESSAGE_WAIT command007;
    Seq_EFFECT_WAIT command008;
    Seq_SETVALUE command009;
    Seq_WKC_ACT command010;
    Seq_ITEMEND command011;
} ITEM_ConditionKaifuku_Stream;
extern ITEM_ConditionKaifuku_Stream ITEM_ConditionKaifuku;

typedef struct ITEM_CriticalUp_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_STATUS_RECOVER command002;
    Seq_FIGHT_EFFECT command003;
    Seq_EFFECT_WAIT command004;
    Seq_MESSAGE_TBL command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SETVALUE command008;
    Seq_WKC_ACT command009;
    Seq_ITEMEND command010;
} ITEM_CriticalUp_Stream;
extern ITEM_CriticalUp_Stream ITEM_CriticalUp;

typedef struct ITEM_AbirityUp_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_STATUS_RECOVER command002;
    Seq_FIGHT_EFFECT command003;
    Seq_EFFECT_WAIT command004;
    Seq_MESSAGE_TBL command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SETVALUE command008;
    Seq_WKC_ACT command009;
    Seq_ITEMEND command010;
} ITEM_AbirityUp_Stream;
extern ITEM_AbirityUp_Stream ITEM_AbirityUp;

typedef struct ITEM_EffectGuard_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_STATUS_RECOVER command002;
    Seq_FIGHT_EFFECT command003;
    Seq_EFFECT_WAIT command004;
    Seq_MESSAGE_TBL command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SETVALUE command008;
    Seq_WKC_ACT command009;
    Seq_ITEMEND command010;
} ITEM_EffectGuard_Stream;
extern ITEM_EffectGuard_Stream ITEM_EffectGuard;

typedef struct ITEM_PippiNingyou_Stream {
    Seq_WAIT command000;
    Seq_GETEND command001;
} ITEM_PippiNingyou_Stream;
extern ITEM_PippiNingyou_Stream ITEM_PippiNingyou;

extern u8 CondUpMsgTbl[];
extern u8 ItemRecoverTbl[];
extern u8 ServerStatusFlag[];
extern u8 ShiroikiriMsgTbl[];

/* The retail labels below are source-relative aliases supplied by the LCF. */
typedef struct FightItemCommandStreams {
    ItemBallTbl_Stream ItemBallTbl;
    ItemNormalTbl_Stream ItemNormalTbl;
    ItemFightTbl_Stream ItemFightTbl;
    ITEM_MonsterBall_Stream ITEM_MonsterBall;
    ITEM_MonsGetSuccess_Stream ITEM_MonsGetSuccess;
    ITEM_MonsGetFail_Stream ITEM_MonsGetFail;
    ITEM_Normal_Stream ITEM_Normal;
    ITEM_HPKaifuku_Stream ITEM_HPKaifuku;
    ITEM_ConditionKaifuku_Stream ITEM_ConditionKaifuku;
    ITEM_CriticalUp_Stream ITEM_CriticalUp;
    ITEM_AbirityUp_Stream ITEM_AbirityUp;
    ITEM_EffectGuard_Stream ITEM_EffectGuard;
    ITEM_PippiNingyou_Stream ITEM_PippiNingyou;
} FightItemCommandStreams;

typedef char ItemOffset_ItemBallTbl[(offsetof(FightItemCommandStreams, ItemBallTbl) == 0x0) ? 1 : -1];
typedef char ItemSize_ItemBallTbl[(sizeof(ItemBallTbl_Stream) == 0x34) ? 1 : -1];
typedef char ItemOffset_ItemNormalTbl[(offsetof(FightItemCommandStreams, ItemNormalTbl) == 0x34) ? 1 : -1];
typedef char ItemSize_ItemNormalTbl[(sizeof(ItemNormalTbl_Stream) == 0x20) ? 1 : -1];
typedef char ItemOffset_ItemFightTbl[(offsetof(FightItemCommandStreams, ItemFightTbl) == 0x54) ? 1 : -1];
typedef char ItemSize_ItemFightTbl[(sizeof(ItemFightTbl_Stream) == 0x4) ? 1 : -1];
typedef char ItemOffset_ITEM_MonsterBall[(offsetof(FightItemCommandStreams, ITEM_MonsterBall) == 0x58) ? 1 : -1];
typedef char ItemSize_ITEM_MonsterBall[(sizeof(ITEM_MonsterBall_Stream) == 0x1) ? 1 : -1];
typedef char ItemOffset_ITEM_MonsGetSuccess[(offsetof(FightItemCommandStreams, ITEM_MonsGetSuccess) == 0x59) ? 1 : -1];
typedef char ItemSize_ITEM_MonsGetSuccess[(sizeof(ITEM_MonsGetSuccess_Stream) == 0xE) ? 1 : -1];
typedef char ItemOffset_ITEM_MonsGetFail[(offsetof(FightItemCommandStreams, ITEM_MonsGetFail) == 0x67) ? 1 : -1];
typedef char ItemSize_ITEM_MonsGetFail[(sizeof(ITEM_MonsGetFail_Stream) == 0x1) ? 1 : -1];
typedef char ItemOffset_ITEM_Normal[(offsetof(FightItemCommandStreams, ITEM_Normal) == 0x68) ? 1 : -1];
typedef char ItemSize_ITEM_Normal[(sizeof(ITEM_Normal_Stream) == 0xA) ? 1 : -1];
typedef char ItemOffset_ITEM_HPKaifuku[(offsetof(FightItemCommandStreams, ITEM_HPKaifuku) == 0x72) ? 1 : -1];
typedef char ItemSize_ITEM_HPKaifuku[(sizeof(ITEM_HPKaifuku_Stream) == 0x35) ? 1 : -1];
typedef char ItemOffset_ITEM_ConditionKaifuku[(offsetof(FightItemCommandStreams, ITEM_ConditionKaifuku) == 0xA7) ? 1 : -1];
typedef char ItemSize_ITEM_ConditionKaifuku[(sizeof(ITEM_ConditionKaifuku_Stream) == 0x28) ? 1 : -1];
typedef char ItemOffset_ITEM_CriticalUp[(offsetof(FightItemCommandStreams, ITEM_CriticalUp) == 0xCF) ? 1 : -1];
typedef char ItemSize_ITEM_CriticalUp[(sizeof(ITEM_CriticalUp_Stream) == 0x26) ? 1 : -1];
typedef char ItemOffset_ITEM_AbirityUp[(offsetof(FightItemCommandStreams, ITEM_AbirityUp) == 0xF5) ? 1 : -1];
typedef char ItemSize_ITEM_AbirityUp[(sizeof(ITEM_AbirityUp_Stream) == 0x26) ? 1 : -1];
typedef char ItemOffset_ITEM_EffectGuard[(offsetof(FightItemCommandStreams, ITEM_EffectGuard) == 0x11B) ? 1 : -1];
typedef char ItemSize_ITEM_EffectGuard[(sizeof(ITEM_EffectGuard_Stream) == 0x26) ? 1 : -1];
typedef char ItemOffset_ITEM_PippiNingyou[(offsetof(FightItemCommandStreams, ITEM_PippiNingyou) == 0x141) ? 1 : -1];
typedef char ItemSize_ITEM_PippiNingyou[(sizeof(ITEM_PippiNingyou_Stream) == 0x4) ? 1 : -1];
typedef char ItemStorageSize[(sizeof(FightItemCommandStreams) == 0x145) ? 1 : -1];

/* Sixteen-byte input alignment reproduces both versions' retail boundaries.
 * The final gap belongs to the next contribution's alignment. */
__declspec(section ".data") FightItemCommandStreams FightItemCommandStorage __attribute__((aligned(16))) = {
    { /* ItemBallTbl */
        {(u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall, (u8*)&ITEM_MonsterBall},
    },
    { /* ItemNormalTbl */
        {(u8*)&ITEM_Normal, (u8*)&ITEM_HPKaifuku, (u8*)&ITEM_HPKaifuku, (u8*)&ITEM_ConditionKaifuku, (u8*)&ITEM_CriticalUp, (u8*)&ITEM_AbirityUp, (u8*)&ITEM_EffectGuard, (u8*)&ITEM_Normal},
    },
    { /* ItemFightTbl */
        {(u8*)&ITEM_PippiNingyou},
    },
    { /* ITEM_MonsterBall */
        {WS_BALL_THROW},
    },
    { /* ITEM_MonsGetSuccess */
        {WS_ADD_POKE, (u8*)&ITEM_MonsGetSuccess + 0xD},
        {WS_MESSAGE, 0x4F86},
        {WS_MESSAGE_WAIT, 64},
        {WS_GETEND},
    },
    { /* ITEM_MonsGetFail */
        {WS_ITEMEND},
    },
    { /* ITEM_Normal */
        {WS_SETVALUE, SEQ_USER_WORK(0x1600C), 15},
        {WS_WKC_ACT, 1, 0},
        {WS_WAZAEND},
    },
    { /* ITEM_HPKaifuku */
        {WS_MESSAGE, 0x4F7C},
        {WS_MESSAGE_WAIT, 64},
        {WS_STATUS_RECOVER},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 17},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4F96},
        {WS_MESSAGE_WAIT, 64},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x1600C), 15},
        {WS_WKC_ACT, 1, 0},
        {WS_ITEMEND},
    },
    { /* ITEM_ConditionKaifuku */
        {WS_MESSAGE, 0x4F7C},
        {WS_MESSAGE_WAIT, 64},
        {WS_STATUS_RECOVER},
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 17},
        {WS_MESSAGE_TBL, (u8*)&ItemRecoverTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x1600C), 15},
        {WS_WKC_ACT, 1, 0},
        {WS_ITEMEND},
    },
    { /* ITEM_CriticalUp */
        {WS_MESSAGE, 0x4F7C},
        {WS_MESSAGE_WAIT, 64},
        {WS_STATUS_RECOVER},
        {WS_FIGHT_EFFECT, 17, 29, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x1600C), 15},
        {WS_WKC_ACT, 1, 0},
        {WS_ITEMEND},
    },
    { /* ITEM_AbirityUp */
        {WS_MESSAGE, 0x4F7C},
        {WS_MESSAGE_WAIT, 64},
        {WS_STATUS_RECOVER},
        {WS_FIGHT_EFFECT, 17, 1, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x1600C), 15},
        {WS_WKC_ACT, 1, 0},
        {WS_ITEMEND},
    },
    { /* ITEM_EffectGuard */
        {WS_MESSAGE, 0x4F7C},
        {WS_MESSAGE_WAIT, 64},
        {WS_STATUS_RECOVER},
        {WS_FIGHT_EFFECT, 17, 28, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&ShiroikiriMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x1600C), 15},
        {WS_WKC_ACT, 1, 0},
        {WS_ITEMEND},
    },
    { /* ITEM_PippiNingyou */
        {WS_WAIT, 32},
        {WS_GETEND},
    },
};

#pragma pack()
#pragma force_active reset
