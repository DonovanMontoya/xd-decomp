#ifndef GAME_MENUBINGO_LAYOUT_HPP
#define GAME_MENUBINGO_LAYOUT_HPP
#include <dolphin/types.h>

struct tagSPRITE_WORK;
struct tagSEQ_WORK;

struct tagWINDOW_WORK {
    u8 used;
    s8 state;
    s8 seqSet;
    u8 pad3;
    s32 menuID;
    u8 pad8;
    s8 priority;
    u8 closeFlag;
    u8 enablePort;
    tagWINDOW_WORK* parent;
    tagWINDOW_WORK* next;
    tagWINDOW_WORK* prev;
    u8 flag18;
    u8 itemNum;
    u8 flags1a;
    u8 closeFlags;
    s32 layer;
    u8 flags20;
    u8 pad21[3];
    tagSPRITE_WORK* itemSprites;
    tagSPRITE_WORK* cursorSprites;
    u8 seq[0x3C];
    u32 params[8];
    s32 cursor88;
    s16 x;
    s16 y;
    u8 color[3];
    u8 alpha;
    f32 f94;
    f32 f98;
    s16 top;
    s16 cursor;
    s16 unkA0;
    s16 prevCursor;
    u8 done;
    u8 cancel;
    u8 padA6[2];
    u8 freeWork[0x10];
    void* alloc;
};

struct tagSPRITE_WORK {
    tagSPRITE_WORK* next;
    s8 kind;
    u8 flags;
    s16 id;
    u8 pad8[0x14];
    s32 layer;
    u8 pad20[0x28];
    void* hook;
    s32 msgID;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s32 unk58;
    s16 sx;
    s16 sy;
    s16 sw;
    s16 sh;
    u8 r;
    u8 g;
    u8 b;
    u8 alpha;
};

#endif
