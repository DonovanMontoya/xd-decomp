.include "macros.inc"
.file "w_pow.c"

# 0x800E6B38..0x800E6B58 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800E6B38 | size: 0x20
.fn pow, global
/* 800E6B38 000E3A98  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E6B3C 000E3A9C  7C 08 02 A6 */	mflr r0
/* 800E6B40 000E3AA0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E6B44 000E3AA4  4B FF D7 2D */	bl __ieee754_pow
/* 800E6B48 000E3AA8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E6B4C 000E3AAC  7C 08 03 A6 */	mtlr r0
/* 800E6B50 000E3AB0  38 21 00 10 */	addi r1, r1, 0x10
/* 800E6B54 000E3AB4  4E 80 00 20 */	blr
.endfn pow
