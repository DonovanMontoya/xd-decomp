.include "macros.inc"
.file "w_sqrt.c"

# 0x800E6F5C..0x800E6F7C | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800E6F5C | size: 0x20
.fn sqrt, global
/* 800E6F5C 000E3EBC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E6F60 000E3EC0  7C 08 02 A6 */	mflr r0
/* 800E6F64 000E3EC4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E6F68 000E3EC8  4B FF FB F1 */	bl __ieee754_sqrt
/* 800E6F6C 000E3ECC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E6F70 000E3ED0  7C 08 03 A6 */	mtlr r0
/* 800E6F74 000E3ED4  38 21 00 10 */	addi r1, r1, 0x10
/* 800E6F78 000E3ED8  4E 80 00 20 */	blr
.endfn sqrt
