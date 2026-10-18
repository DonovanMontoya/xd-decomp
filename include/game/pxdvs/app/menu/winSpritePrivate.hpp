#ifndef PXDVS_APP_MENU_WINSPRITE_PRIVATE_HPP
#define PXDVS_APP_MENU_WINSPRITE_PRIVATE_HPP

#include <game/pxdvs/app/menu/windowPrivate.hpp>

struct tagSPRITE_WORK {
    tagSPRITE_WORK *next;
    s8 type;
    u8 flags;
    s16 itemID;
    u32 texture;
    u8 sequence[0x3C];
    u32 callback, message;
    s16 x, y, width, height;
    u32 resource;
    s16 sourceX, sourceY, sourceWidth, sourceHeight;
    u32 color;
    f32 scaleX, scaleY;
    u8 reserved70[4];
    u8 drawType, blendType, mode, reserved77;
};

struct SEQ_WORK_COMMON {
    s16 x, y;
    s32 color;
    s16 baseX, baseY;
    f32 scaleX, scaleY;
    u32 resource;
    s16 sourceX, sourceY, sourceWidth, sourceHeight;
    u8 type;
    u8 pad[3];
};

typedef char SeqWorkCommonSize[sizeof(SEQ_WORK_COMMON) == 0x24 ? 1 : -1];
typedef char SpriteWorkSize[sizeof(tagSPRITE_WORK) == 0x78 ? 1 : -1];

struct WindowSequenceCommand {
    union {
        u8 flags;
        struct { u8 relative:1; u8 easing:2; u8 axes:2; u8 reserved:3; } bits;
    };
    u8 command;
    s16 duration;
    s32 x, y;
};
struct tagSEQ_WORK {
    WindowSequenceCommand *commands;
    s16 index, wait;
    u8 moveMode, colorMode, scaleMode, loopActive;
    s16 startX, startY, endX, endY, moveFrame, moveDuration;
    u8 startColor[4], endColor[4];
    s16 colorFrame, colorDuration;
    f32 startScaleX, startScaleY, endScaleX, endScaleY;
    s16 scaleFrame, scaleDuration, loopCount;
    u8 loopFlag, pad3B;
};
struct WindowSpriteValue {
    s16 x, y, width, height;
    u32 resource;
};

#endif
