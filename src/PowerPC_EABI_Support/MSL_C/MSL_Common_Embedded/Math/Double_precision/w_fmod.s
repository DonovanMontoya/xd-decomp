.include "macros.inc"
.file "w_fmod.c"

# 0x800E6AF8..0x800E6B18 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800E6AF8 | size: 0x20
.fn fmod, global
/* 800E6AF8 000E3A58  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E6AFC 000E3A5C  7C 08 02 A6 */	mflr r0
/* 800E6B00 000E3A60  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E6B04 000E3A64  4B FF D1 B5 */	bl __ieee754_fmod
/* 800E6B08 000E3A68  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E6B0C 000E3A6C  7C 08 03 A6 */	mtlr r0
/* 800E6B10 000E3A70  38 21 00 10 */	addi r1, r1, 0x10
/* 800E6B14 000E3A74  4E 80 00 20 */	blr
.endfn fmod
