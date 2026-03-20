.include "macros.inc"
.file "k_sin.c"

# 0x800E5D88..0x800E5E28 | size: 0xA0
.text
.balign 4

# .text:0x0 | 0x800E5D88 | size: 0xA0
.fn __kernel_sin, global
/* 800E5D88 000E2CE8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E5D8C 000E2CEC  3C 00 3E 40 */	lis r0, 0x3e40
/* 800E5D90 000E2CF0  D8 21 00 08 */	stfd f1, 0x8(r1)
/* 800E5D94 000E2CF4  80 81 00 08 */	lwz r4, 0x8(r1)
/* 800E5D98 000E2CF8  54 84 00 7E */	clrlwi r4, r4, 1
/* 800E5D9C 000E2CFC  7C 04 00 00 */	cmpw r4, r0
/* 800E5DA0 000E2D00  40 80 00 1C */	bge .L_800E5DBC
/* 800E5DA4 000E2D04  FC 00 08 1E */	fctiwz f0, f1
/* 800E5DA8 000E2D08  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 800E5DAC 000E2D0C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800E5DB0 000E2D10  2C 00 00 00 */	cmpwi r0, 0x0
/* 800E5DB4 000E2D14  40 82 00 08 */	bne .L_800E5DBC
/* 800E5DB8 000E2D18  48 00 00 68 */	b .L_800E5E20
.L_800E5DBC:
/* 800E5DBC 000E2D1C  C8 C1 00 08 */	lfd f6, 0x8(r1)
/* 800E5DC0 000E2D20  2C 03 00 00 */	cmpwi r3, 0x0
/* 800E5DC4 000E2D24  C8 A2 94 28 */	lfd f5, "@64"@sda21(r0)
/* 800E5DC8 000E2D28  FC E6 01 B2 */	fmul f7, f6, f6
/* 800E5DCC 000E2D2C  C8 82 94 20 */	lfd f4, "@63"@sda21(r0)
/* 800E5DD0 000E2D30  C8 62 94 18 */	lfd f3, "@62"@sda21(r0)
/* 800E5DD4 000E2D34  C8 22 94 10 */	lfd f1, "@61"@sda21(r0)
/* 800E5DD8 000E2D38  C8 02 94 08 */	lfd f0, "@60"@sda21(r0)
/* 800E5DDC 000E2D3C  FC 85 21 FA */	fmadd f4, f5, f7, f4
/* 800E5DE0 000E2D40  FC A7 01 B2 */	fmul f5, f7, f6
/* 800E5DE4 000E2D44  FC 67 19 3A */	fmadd f3, f7, f4, f3
/* 800E5DE8 000E2D48  FC 27 08 FA */	fmadd f1, f7, f3, f1
/* 800E5DEC 000E2D4C  FC 27 00 7A */	fmadd f1, f7, f1, f0
/* 800E5DF0 000E2D50  40 82 00 14 */	bne .L_800E5E04
/* 800E5DF4 000E2D54  C8 02 94 30 */	lfd f0, "@65"@sda21(r0)
/* 800E5DF8 000E2D58  FC 07 00 7A */	fmadd f0, f7, f1, f0
/* 800E5DFC 000E2D5C  FC 25 30 3A */	fmadd f1, f5, f0, f6
/* 800E5E00 000E2D60  48 00 00 20 */	b .L_800E5E20
.L_800E5E04:
/* 800E5E04 000E2D64  FC 05 00 72 */	fmul f0, f5, f1
/* 800E5E08 000E2D68  C8 22 94 38 */	lfd f1, "@66"@sda21(r0)
/* 800E5E0C 000E2D6C  C8 62 94 30 */	lfd f3, "@65"@sda21(r0)
/* 800E5E10 000E2D70  FC 01 00 B8 */	fmsub f0, f1, f2, f0
/* 800E5E14 000E2D74  FC 07 10 38 */	fmsub f0, f7, f0, f2
/* 800E5E18 000E2D78  FC 03 01 7C */	fnmsub f0, f3, f5, f0
/* 800E5E1C 000E2D7C  FC 26 00 28 */	fsub f1, f6, f0
.L_800E5E20:
/* 800E5E20 000E2D80  38 21 00 20 */	addi r1, r1, 0x20
/* 800E5E24 000E2D84  4E 80 00 20 */	blr
.endfn __kernel_sin

# 0x804ED1C8..0x804ED200 | size: 0x38
.section .sdata2, "a"
.balign 8

# .sdata2:0x0 | 0x804ED1C8 | size: 0x8
.obj "@60", local
	.double 0.00833333333332249
.endobj "@60"

# .sdata2:0x8 | 0x804ED1D0 | size: 0x8
.obj "@61", local
	.double -0.0001984126982985795
.endobj "@61"

# .sdata2:0x10 | 0x804ED1D8 | size: 0x8
.obj "@62", local
	.double 0.0000027557313707070068
.endobj "@62"

# .sdata2:0x18 | 0x804ED1E0 | size: 0x8
.obj "@63", local
	.double -0.000000025050760253406863
.endobj "@63"

# .sdata2:0x20 | 0x804ED1E8 | size: 0x8
.obj "@64", local
	.double 0.000000000158969099521155
.endobj "@64"

# .sdata2:0x28 | 0x804ED1F0 | size: 0x8
.obj "@65", local
	.double -0.16666666666666632
.endobj "@65"

# .sdata2:0x30 | 0x804ED1F8 | size: 0x8
.obj "@66", local
	.double 0.5
.endobj "@66"
