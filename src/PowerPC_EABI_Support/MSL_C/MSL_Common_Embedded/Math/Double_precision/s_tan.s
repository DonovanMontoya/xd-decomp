.include "macros.inc"
.file "s_tan.c"

# 0x800E6A00..0x800E6A78 | size: 0x78
.text
.balign 4

# .text:0x0 | 0x800E6A00 | size: 0x78
.fn tan, global
/* 800E6A00 000E3960  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E6A04 000E3964  7C 08 02 A6 */	mflr r0
/* 800E6A08 000E3968  3C 60 3F E9 */	lis r3, 0x3fe9
/* 800E6A0C 000E396C  D8 21 00 08 */	stfd f1, 0x8(r1)
/* 800E6A10 000E3970  90 01 00 24 */	stw r0, 0x24(r1)
/* 800E6A14 000E3974  38 03 21 FB */	addi r0, r3, 0x21fb
/* 800E6A18 000E3978  80 61 00 08 */	lwz r3, 0x8(r1)
/* 800E6A1C 000E397C  54 63 00 7E */	clrlwi r3, r3, 1
/* 800E6A20 000E3980  7C 03 00 00 */	cmpw r3, r0
/* 800E6A24 000E3984  41 81 00 14 */	bgt .L_800E6A38
/* 800E6A28 000E3988  C8 42 95 00 */	lfd f2, "@58"@sda21(r0)
/* 800E6A2C 000E398C  38 60 00 01 */	li r3, 0x1
/* 800E6A30 000E3990  4B FF F3 F9 */	bl __kernel_tan
/* 800E6A34 000E3994  48 00 00 34 */	b .L_800E6A68
.L_800E6A38:
/* 800E6A38 000E3998  3C 00 7F F0 */	lis r0, 0x7ff0
/* 800E6A3C 000E399C  7C 03 00 00 */	cmpw r3, r0
/* 800E6A40 000E39A0  41 80 00 0C */	blt .L_800E6A4C
/* 800E6A44 000E39A4  FC 21 08 28 */	fsub f1, f1, f1
/* 800E6A48 000E39A8  48 00 00 20 */	b .L_800E6A68
.L_800E6A4C:
/* 800E6A4C 000E39AC  38 61 00 10 */	addi r3, r1, 0x10
/* 800E6A50 000E39B0  4B FF E0 51 */	bl __ieee754_rem_pio2
/* 800E6A54 000E39B4  54 60 0F BC */	clrlslwi r0, r3, 31, 1
/* 800E6A58 000E39B8  C8 21 00 10 */	lfd f1, 0x10(r1)
/* 800E6A5C 000E39BC  C8 41 00 18 */	lfd f2, 0x18(r1)
/* 800E6A60 000E39C0  20 60 00 01 */	subfic r3, r0, 0x1
/* 800E6A64 000E39C4  4B FF F3 C5 */	bl __kernel_tan
.L_800E6A68:
/* 800E6A68 000E39C8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800E6A6C 000E39CC  7C 08 03 A6 */	mtlr r0
/* 800E6A70 000E39D0  38 21 00 20 */	addi r1, r1, 0x20
/* 800E6A74 000E39D4  4E 80 00 20 */	blr
.endfn tan

# 0x804ED2C0..0x804ED2C8 | size: 0x8
.section .sdata2, "a"
.balign 8

# .sdata2:0x0 | 0x804ED2C0 | size: 0x8
.obj "@58", local
	.double 0
.endobj "@58"
