.include "macros.inc"
.file "w_asin.c"

# 0x800E6A98..0x800E6AB8 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800E6A98 | size: 0x20
.fn asin, global
/* 800E6A98 000E39F8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E6A9C 000E39FC  7C 08 02 A6 */	mflr r0
/* 800E6AA0 000E3A00  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E6AA4 000E3A04  4B FF CB 29 */	bl __ieee754_asin
/* 800E6AA8 000E3A08  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E6AAC 000E3A0C  7C 08 03 A6 */	mtlr r0
/* 800E6AB0 000E3A10  38 21 00 10 */	addi r1, r1, 0x10
/* 800E6AB4 000E3A14  4E 80 00 20 */	blr
.endfn asin
