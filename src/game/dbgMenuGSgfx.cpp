#include <global.h>

extern "C" {

u8 menuIsCheck(s32 menuId);
void menuClose(s32 menuId);
void menuOpenCustom(s32 menuId, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, ...);
void menuSetPosition(s32 menuId, s32 x, s32 y);
u8 GSgfxLayerGetStatsRenderMode(void);
void GSgfxLayerSetStatsRenderMode(u8 mode);

asm s32 dbgMenuGSgfxChangeDisp(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  li r3, 0x8
  bl menuIsCheck
  clrlwi r0, r3, 24
  cmplwi r0, 0x0
  beq lbl_8000B370
  li r3, 0x8
  bl menuClose
  b lbl_8000B3A0
lbl_8000B370:
  li r3, 0x8
  li r4, 0x0
  li r5, 0x0
  li r6, 0x0
  li r7, 0x1
  li r8, 0x0
  crclr 4*cr1+eq
  bl menuOpenCustom
  li r3, 0x8
  li r4, 0x17c
  li r5, 0x20
  bl menuSetPosition
lbl_8000B3A0:
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuLayerFifoDisp(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  bl GSgfxLayerGetStatsRenderMode
  clrlwi r0, r3, 24
  cmplwi r0, 0x0
  bne lbl_8000B3DC
  li r3, 0x1
  bl GSgfxLayerSetStatsRenderMode
  b lbl_8000B3E4
lbl_8000B3DC:
  li r3, 0x0
  bl GSgfxLayerSetStatsRenderMode
lbl_8000B3E4:
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

} // extern "C"
