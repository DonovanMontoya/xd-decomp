.include "macros.inc"
.file "s_copysign.c"

# 0x800E6398..0x800E63C0 | size: 0x28
.text
.balign 4

# .text:0x0 | 0x800E6398 | size: 0x28
.fn copysign, global
/* 800E6398 000E32F8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E639C 000E32FC  D8 21 00 08 */	stfd f1, 0x8(r1)
/* 800E63A0 000E3300  D8 41 00 10 */	stfd f2, 0x10(r1)
/* 800E63A4 000E3304  80 61 00 08 */	lwz r3, 0x8(r1)
/* 800E63A8 000E3308  80 01 00 10 */	lwz r0, 0x10(r1)
/* 800E63AC 000E330C  50 60 00 7E */	rlwimi r0, r3, 0, 1, 31
/* 800E63B0 000E3310  90 01 00 08 */	stw r0, 0x8(r1)
/* 800E63B4 000E3314  C8 21 00 08 */	lfd f1, 0x8(r1)
/* 800E63B8 000E3318  38 21 00 20 */	addi r1, r1, 0x20
/* 800E63BC 000E331C  4E 80 00 20 */	blr
.endfn copysign
