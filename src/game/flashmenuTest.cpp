#include <game/pxdvs/app/menu/winSpritePrivate.hpp>

extern "C" {
void menuClose(s32);
void menuOpen(s32, s32);
void FlashSystemSetLoopFlag(void*, s32);
}

extern "C" void fn_8000FF78(void);

extern "C" void fn_8000FF9C(void);

extern "C" void menuFlashTestInit(void);

extern "C" {
void winSpriteSetDisp(tagSPRITE_WORK*, u8);
void windowDrawSprite(s16, s16, tagWINDOW_WORK*, u16, u32, s32);
}

extern "C" f32 lbl_804E7E68[2] = {0.0f, 0.0f};
extern "C" u16 lbl_804E7E70[4] = {0x2E1, 0x2E2, 0x2E3, 0x2E4};
extern "C" u8 lbl_804E7E78[4] = {1, 1, 1, 1};
extern "C" u8 lbl_804E7E7C = 1;
extern "C" u8 lbl_804EA6F0[8];
u8 lbl_804EA6F0[8];

extern "C" s32 fn_8000FDA8(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    s32 layer = winSpriteGetLayerID(window, (WindowSprite*)sprite);
    switch (sprite->itemID) {
    case 0x155:
        winSpriteSetDisp(sprite, lbl_804E7E7C);
        break;
    case 0x68F:
        winSpriteSetDisp(sprite, lbl_804E7E78[0]);
        break;
    case 0x690:
        winSpriteSetDisp(sprite, lbl_804E7E78[1]);
        break;
    case 0x691:
        winSpriteSetDisp(sprite, lbl_804E7E78[2]);
        break;
    case 0x692:
        winSpriteSetDisp(sprite, lbl_804E7E78[3]);
        break;
    case 0x698:
        if (lbl_804EA6F0[0]) {
            windowDrawSprite((s16)lbl_804E7E68[0], (s16)lbl_804E7E68[1], window, lbl_804E7E70[0], 0, layer);
            windowDrawSprite((s16)lbl_804E7E68[0], (s16)lbl_804E7E68[1], window, lbl_804E7E70[1], 0, layer);
            windowDrawSprite((s16)lbl_804E7E68[0], (s16)lbl_804E7E68[1], window, lbl_804E7E70[2], 0, layer);
            windowDrawSprite((s16)lbl_804E7E68[0], (s16)lbl_804E7E68[1], window, lbl_804E7E70[3], 0, layer);
        }
        break;
    }
    return 0;
}

#pragma force_active on
extern "C" void fn_8000FF78(void) {
    menuClose(0x4E);
}

extern "C" void fn_8000FF9C(void) {
    menuOpen(0x4E, 1);
}

extern "C" void menuFlashTestInit(void) {
    FlashSystemSetLoopFlag((void*)0x17883000, 1);
}

#pragma force_active reset
