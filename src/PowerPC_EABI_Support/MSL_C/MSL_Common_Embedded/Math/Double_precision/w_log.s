.include "macros.inc"
.file "w_log.c"

# 0x800E6B18..0x800E6B38 | size: 0x20
.text
.balign 4

# .text:0x0 | 0x800E6B18 | size: 0x20
.fn log, global
/* 800E6B18 000E3A78  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800E6B1C 000E3A7C  7C 08 02 A6 */	mflr r0
/* 800E6B20 000E3A80  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E6B24 000E3A84  4B FF D4 D1 */	bl __ieee754_log
/* 800E6B28 000E3A88  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E6B2C 000E3A8C  7C 08 03 A6 */	mtlr r0
/* 800E6B30 000E3A90  38 21 00 10 */	addi r1, r1, 0x10
/* 800E6B34 000E3A94  4E 80 00 20 */	blr
.endfn log
