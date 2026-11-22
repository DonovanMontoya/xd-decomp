#ifndef GAME_MENUCBRULE_HPP
#define GAME_MENUCBRULE_HPP

#include <dolphin/types.h>

typedef struct MenuCBRule {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    s16 unk14;
    s16 unk16;
    u8 unk18;
    u8 unk19;
    s16 unk1A;
    s16 unk1C;
    u16 name[21];
    u8 unk48[8];
    u16 unk50;
    u8 itemFlags[62];
} MenuCBRule;

typedef struct _TOOL_SAVEDATA {
    MenuCBRule rules[6];
    s8 currentlyWorkingToolBattle;
} _TOOL_SAVEDATA;

typedef char ToolSaveDataSize[sizeof(_TOOL_SAVEDATA) == 0x364 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

MenuCBRule *menuCBBios_CurrentRule(void);
MenuCBRule *menuCBBios_GetRule(s32 index);
MenuCBRule *menuCB_OreRule(void);
MenuCBRule *menuCBRule_ConstantRule(s32 index);
MenuCBRule *menuCBRule_ConstantRule2(s32 index);
void menuCBRule_Copy(MenuCBRule *dst, const MenuCBRule *src);

#ifdef __cplusplus
bool menuCBRule_IsEquals(const MenuCBRule *a, const MenuCBRule *b);
}
#endif

#endif
