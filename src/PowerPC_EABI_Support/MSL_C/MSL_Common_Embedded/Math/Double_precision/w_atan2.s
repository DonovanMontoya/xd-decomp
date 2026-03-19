.include "macros.inc"
.file "w_atan2.c"

# 0x800E6AB8..0x800E6AD8 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800E6AB8 | size: 0x20
.fn atan2, global
/* 800E6AB8 000E3A18  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E6ABC 000E3A1C  7C 08 02 A6 */	mflr r0
/* 800E6AC0 000E3A20  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E6AC4 000E3A24  4B FF CD 41 */	bl __ieee754_atan2
/* 800E6AC8 000E3A28  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E6ACC 000E3A2C  7C 08 03 A6 */	mtlr r0
/* 800E6AD0 000E3A30  38 21 00 10 */	addi r1, r1, 0x10
/* 800E6AD4 000E3A34  4E 80 00 20 */	blr
.endfn atan2
