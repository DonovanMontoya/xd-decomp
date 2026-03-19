.include "macros.inc"
.file "w_acos.c"

# 0x800E6A78..0x800E6A98 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800E6A78 | size: 0x20
.fn acos, global
/* 800E6A78 000E39D8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E6A7C 000E39DC  7C 08 02 A6 */	mflr r0
/* 800E6A80 000E39E0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E6A84 000E39E4  4B FF C9 0D */	bl __ieee754_acos
/* 800E6A88 000E39E8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E6A8C 000E39EC  7C 08 03 A6 */	mtlr r0
/* 800E6A90 000E39F0  38 21 00 10 */	addi r1, r1, 0x10
/* 800E6A94 000E39F4  4E 80 00 20 */	blr
.endfn acos
