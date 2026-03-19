.include "macros.inc"
.file "w_exp.c"

# 0x800E6AD8..0x800E6AF8 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800E6AD8 | size: 0x20
.fn exp, global
/* 800E6AD8 000E3A38  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E6ADC 000E3A3C  7C 08 02 A6 */	mflr r0
/* 800E6AE0 000E3A40  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E6AE4 000E3A44  4B FF CF B1 */	bl __ieee754_exp
/* 800E6AE8 000E3A48  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E6AEC 000E3A4C  7C 08 03 A6 */	mtlr r0
/* 800E6AF0 000E3A50  38 21 00 10 */	addi r1, r1, 0x10
/* 800E6AF4 000E3A54  4E 80 00 20 */	blr
.endfn exp
