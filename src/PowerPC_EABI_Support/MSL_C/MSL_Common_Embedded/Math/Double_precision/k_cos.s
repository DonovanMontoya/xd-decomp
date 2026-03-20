.include "macros.inc"
.file "k_cos.c"

# 0x800E4E40..0x800E4F34 | size: 0xF4
.text
.balign 4

# .text:0x0 | 0x800E4E40 | size: 0xF4
.fn __kernel_cos, global
/* 800E4E40 000E1DA0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E4E44 000E1DA4  3C 00 3E 40 */	lis r0, 0x3e40
/* 800E4E48 000E1DA8  D8 21 00 08 */	stfd f1, 0x8(r1)
/* 800E4E4C 000E1DAC  80 61 00 08 */	lwz r3, 0x8(r1)
/* 800E4E50 000E1DB0  54 64 00 7E */	clrlwi r4, r3, 1
/* 800E4E54 000E1DB4  7C 04 00 00 */	cmpw r4, r0
/* 800E4E58 000E1DB8  40 80 00 20 */	bge .L_800E4E78
/* 800E4E5C 000E1DBC  FC 00 08 1E */	fctiwz f0, f1
/* 800E4E60 000E1DC0  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 800E4E64 000E1DC4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800E4E68 000E1DC8  2C 00 00 00 */	cmpwi r0, 0x0
/* 800E4E6C 000E1DCC  40 82 00 0C */	bne .L_800E4E78
/* 800E4E70 000E1DD0  C8 22 93 80 */	lfd f1, "@65"@sda21(r0)
/* 800E4E74 000E1DD4  48 00 00 B8 */	b .L_800E4F2C
.L_800E4E78:
/* 800E4E78 000E1DD8  C8 C1 00 08 */	lfd f6, 0x8(r1)
/* 800E4E7C 000E1DDC  3C 60 3F D3 */	lis r3, 0x3fd3
/* 800E4E80 000E1DE0  38 03 33 33 */	addi r0, r3, 0x3333
/* 800E4E84 000E1DE4  C8 A2 93 B0 */	lfd f5, "@71"@sda21(r0)
/* 800E4E88 000E1DE8  FC E6 01 B2 */	fmul f7, f6, f6
/* 800E4E8C 000E1DEC  C8 02 93 A8 */	lfd f0, "@70"@sda21(r0)
/* 800E4E90 000E1DF0  C8 82 93 A0 */	lfd f4, "@69"@sda21(r0)
/* 800E4E94 000E1DF4  7C 04 00 00 */	cmpw r4, r0
/* 800E4E98 000E1DF8  C8 62 93 98 */	lfd f3, "@68"@sda21(r0)
/* 800E4E9C 000E1DFC  C8 22 93 90 */	lfd f1, "@67"@sda21(r0)
/* 800E4EA0 000E1E00  FC A5 01 FA */	fmadd f5, f5, f7, f0
/* 800E4EA4 000E1E04  C8 02 93 88 */	lfd f0, "@66"@sda21(r0)
/* 800E4EA8 000E1E08  FC 87 21 7A */	fmadd f4, f7, f5, f4
/* 800E4EAC 000E1E0C  FC 67 19 3A */	fmadd f3, f7, f4, f3
/* 800E4EB0 000E1E10  FC 27 08 FA */	fmadd f1, f7, f3, f1
/* 800E4EB4 000E1E14  FC 07 00 7A */	fmadd f0, f7, f1, f0
/* 800E4EB8 000E1E18  FC 87 00 32 */	fmul f4, f7, f0
/* 800E4EBC 000E1E1C  40 80 00 20 */	bge .L_800E4EDC
/* 800E4EC0 000E1E20  FC 06 00 B2 */	fmul f0, f6, f2
/* 800E4EC4 000E1E24  C8 22 93 B8 */	lfd f1, "@72"@sda21(r0)
/* 800E4EC8 000E1E28  C8 42 93 80 */	lfd f2, "@65"@sda21(r0)
/* 800E4ECC 000E1E2C  FC 07 01 38 */	fmsub f0, f7, f4, f0
/* 800E4ED0 000E1E30  FC 01 01 F8 */	fmsub f0, f1, f7, f0
/* 800E4ED4 000E1E34  FC 22 00 28 */	fsub f1, f2, f0
/* 800E4ED8 000E1E38  48 00 00 54 */	b .L_800E4F2C
.L_800E4EDC:
/* 800E4EDC 000E1E3C  3C 00 3F E9 */	lis r0, 0x3fe9
/* 800E4EE0 000E1E40  7C 04 00 00 */	cmpw r4, r0
/* 800E4EE4 000E1E44  40 81 00 10 */	ble .L_800E4EF4
/* 800E4EE8 000E1E48  C8 02 93 C0 */	lfd f0, "@73"@sda21(r0)
/* 800E4EEC 000E1E4C  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 800E4EF0 000E1E50  48 00 00 14 */	b .L_800E4F04
.L_800E4EF4:
/* 800E4EF4 000E1E54  3C 64 FF E0 */	subis r3, r4, 0x20
/* 800E4EF8 000E1E58  38 00 00 00 */	li r0, 0x0
/* 800E4EFC 000E1E5C  90 61 00 10 */	stw r3, 0x10(r1)
/* 800E4F00 000E1E60  90 01 00 14 */	stw r0, 0x14(r1)
.L_800E4F04:
/* 800E4F04 000E1E64  C8 01 00 08 */	lfd f0, 0x8(r1)
/* 800E4F08 000E1E68  C8 61 00 10 */	lfd f3, 0x10(r1)
/* 800E4F0C 000E1E6C  FC 00 00 B2 */	fmul f0, f0, f2
/* 800E4F10 000E1E70  C8 22 93 B8 */	lfd f1, "@72"@sda21(r0)
/* 800E4F14 000E1E74  C8 42 93 80 */	lfd f2, "@65"@sda21(r0)
/* 800E4F18 000E1E78  FC 21 19 F8 */	fmsub f1, f1, f7, f3
/* 800E4F1C 000E1E7C  FC 07 01 38 */	fmsub f0, f7, f4, f0
/* 800E4F20 000E1E80  FC 42 18 28 */	fsub f2, f2, f3
/* 800E4F24 000E1E84  FC 01 00 28 */	fsub f0, f1, f0
/* 800E4F28 000E1E88  FC 22 00 28 */	fsub f1, f2, f0
.L_800E4F2C:
/* 800E4F2C 000E1E8C  38 21 00 20 */	addi r1, r1, 0x20
/* 800E4F30 000E1E90  4E 80 00 20 */	blr
.endfn __kernel_cos

# 0x804ED140..0x804ED188 | size: 0x48
.section .sdata2, "a"
.balign 8

# .sdata2:0x0 | 0x804ED140 | size: 0x8
.obj "@65", local
	.double 1
.endobj "@65"

# .sdata2:0x8 | 0x804ED148 | size: 0x8
.obj "@66", local
	.double 0.0416666666666666
.endobj "@66"

# .sdata2:0x10 | 0x804ED150 | size: 0x8
.obj "@67", local
	.double -0.001388888888887411
.endobj "@67"

# .sdata2:0x18 | 0x804ED158 | size: 0x8
.obj "@68", local
	.double 0.00002480158728947673
.endobj "@68"

# .sdata2:0x20 | 0x804ED160 | size: 0x8
.obj "@69", local
	.double -0.00000027557314351390663
.endobj "@69"

# .sdata2:0x28 | 0x804ED168 | size: 0x8
.obj "@70", local
	.double 0.000000002087572321298175
.endobj "@70"

# .sdata2:0x30 | 0x804ED170 | size: 0x8
.obj "@71", local
	.double -0.000000000011359647557788195
.endobj "@71"

# .sdata2:0x38 | 0x804ED178 | size: 0x8
.obj "@72", local
	.double 0.5
.endobj "@72"

# .sdata2:0x40 | 0x804ED180 | size: 0x8
.obj "@73", local
	.double 0.28125
.endobj "@73"
