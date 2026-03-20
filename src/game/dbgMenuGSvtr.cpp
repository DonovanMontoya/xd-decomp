#include <global.h>

extern "C" {

u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
void soundOpenPlay(s32, s32, s32);
void GSgfxCaptureMovieStart(s32);
void GSgfxCaptureMovieStop(void);
void GSgfxCaptureSetTarget(s32);
u8 GSvtrGetInfoDisp(void);
void GSvtrSetInfoDisp(u8, u8);
u8 GSvtrIsActive(void);
void GSvtrEnable(void);
void GSvtrDisable(void);
void GSvtrSlowPlay(void);
void GSvtrSingleStep(void);
void GSvtrPause(void);
void GSvtrPlay(void);

static u8 _vtrWantCapture;
static u8 _vtrIsCapturing;

asm s32 dbgMenuGSvtrCaptureUpdate(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  stw r31, 0xc(r1)
  li r3, 0x1
  bl GSinputButtonsChanged
  mr r31, r3
  li r3, 0x1
  bl GSinputButtonsPressed
  and r0, r3, r31
  rlwinm r0, r0, 0, 27, 27
  cmplwi r0, 0x0
  beq lbl_8000B48C
  lbz r0, _vtrIsCapturing(r13)
  cmpwi r0, 0x1
  beq lbl_8000B480
  bge lbl_8000B48C
  cmpwi r0, 0x0
  bge lbl_8000B448
  b lbl_8000B48C
lbl_8000B448:
  lbz r0, _vtrWantCapture(r13)
  cmplwi r0, 0x0
  beq lbl_8000B48C
  li r3, 0x8
  li r4, 0x0
  li r5, 0x0
  bl soundOpenPlay
  li r3, 0x4650
  bl GSgfxCaptureMovieStart
  li r3, 0x0
  li r0, 0x1
  stb r3, _vtrWantCapture(r13)
  stb r0, _vtrIsCapturing(r13)
  b lbl_8000B48C
lbl_8000B480:
  bl GSgfxCaptureMovieStop
  li r0, 0x0
  stb r0, _vtrIsCapturing(r13)
lbl_8000B48C:
  lwz r0, 0x14(r1)
  lwz r31, 0xc(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuGSvtrCaptureSD(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  li r3, 0x1
  bl GSgfxCaptureSetTarget
  li r0, 0x1
  stb r0, _vtrWantCapture(r13)
  bl GSvtrGetInfoDisp
  li r4, 0x1
  bl GSvtrSetInfoDisp
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuGSvtrCaptureBBA(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  li r3, 0x0
  bl GSgfxCaptureSetTarget
  li r0, 0x1
  stb r0, _vtrWantCapture(r13)
  bl GSvtrGetInfoDisp
  li r4, 0x1
  bl GSvtrSetInfoDisp
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuGSvtrSlow(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  bl GSvtrSlowPlay
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuGSvtrStep(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  bl GSvtrSingleStep
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuGSvtrPause(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  bl GSvtrPause
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuGSvtrPlay(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  bl GSvtrPlay
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuGSvtrChangeDisp(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  bl GSvtrGetInfoDisp
  clrlwi r0, r3, 24
  lbz r4, _vtrWantCapture(r13)
  cntlzw r0, r0
  srwi r0, r0, 5
  clrlwi r3, r0, 24
  bl GSvtrSetInfoDisp
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

asm s32 dbgMenuGSvtrChangeActive(void) {
  nofralloc
  stwu r1, -0x10(r1)
  mflr r0
  stw r0, 0x14(r1)
  bl GSvtrIsActive
  clrlwi r0, r3, 24
  cmplwi r0, 0x0
  bne lbl_8000B608
  bl GSvtrEnable
  b lbl_8000B60C
lbl_8000B608:
  bl GSvtrDisable
lbl_8000B60C:
  li r3, 0x0
  lwz r0, 0x14(r1)
  mtlr r0
  addi r1, r1, 0x10
  blr
}

} // extern "C"
