.include "macros.inc"
.file "e_asin.c"

# 0x800E35CC..0x800E3804 | size: 0x238
.text
.balign 4

# .text:0x0 | 0x800E35CC | size: 0x238
.fn __ieee754_asin, global
/* 800E35CC 000E052C  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 800E35D0 000E0530  7C 08 02 A6 */	mflr r0
/* 800E35D4 000E0534  90 01 00 54 */	stw r0, 0x54(r1)
/* 800E35D8 000E0538  DB E1 00 40 */	stfd f31, 0x40(r1)
/* 800E35DC 000E053C  F3 E1 00 48 */	psq_st f31, 0x48(r1), 0, qr0
/* 800E35E0 000E0540  DB C1 00 30 */	stfd f30, 0x30(r1)
/* 800E35E4 000E0544  F3 C1 00 38 */	psq_st f30, 0x38(r1), 0, qr0
/* 800E35E8 000E0548  DB A1 00 20 */	stfd f29, 0x20(r1)
/* 800E35EC 000E054C  F3 A1 00 28 */	psq_st f29, 0x28(r1), 0, qr0
/* 800E35F0 000E0550  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800E35F4 000E0554  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800E35F8 000E0558  D8 21 00 08 */	stfd f1, 0x8(r1)
/* 800E35FC 000E055C  3C 00 3F F0 */	lis r0, 0x3ff0
/* 800E3600 000E0560  83 E1 00 08 */	lwz r31, 0x8(r1)
/* 800E3604 000E0564  57 FE 00 7E */	clrlwi r30, r31, 1
/* 800E3608 000E0568  7C 1E 00 00 */	cmpw r30, r0
/* 800E360C 000E056C  41 80 00 34 */	blt .L_800E3640
/* 800E3610 000E0570  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800E3614 000E0574  3C 7E C0 10 */	subis r3, r30, 0x3ff0
/* 800E3618 000E0578  7C 60 03 79 */	or. r0, r3, r0
/* 800E361C 000E057C  40 82 00 18 */	bne .L_800E3634
/* 800E3620 000E0580  C8 02 90 48 */	lfd f0, "@95"@sda21(r0)
/* 800E3624 000E0584  C8 42 90 40 */	lfd f2, "@94"@sda21(r0)
/* 800E3628 000E0588  FC 00 00 72 */	fmul f0, f0, f1
/* 800E362C 000E058C  FC 22 00 7A */	fmadd f1, f2, f1, f0
/* 800E3630 000E0590  48 00 01 A4 */	b .L_800E37D4
.L_800E3634:
/* 800E3634 000E0594  3C 60 80 4F */	lis r3, __float_nan@ha
/* 800E3638 000E0598  C0 23 82 E0 */	lfs f1, __float_nan@l(r3)
/* 800E363C 000E059C  48 00 01 98 */	b .L_800E37D4
.L_800E3640:
/* 800E3640 000E05A0  3C 00 3F E0 */	lis r0, 0x3fe0
/* 800E3644 000E05A4  7C 1E 00 00 */	cmpw r30, r0
/* 800E3648 000E05A8  40 80 00 94 */	bge .L_800E36DC
/* 800E364C 000E05AC  3C 00 3E 40 */	lis r0, 0x3e40
/* 800E3650 000E05B0  7C 1E 00 00 */	cmpw r30, r0
/* 800E3654 000E05B4  40 80 00 1C */	bge .L_800E3670
/* 800E3658 000E05B8  C8 42 90 50 */	lfd f2, "@96"@sda21(r0)
/* 800E365C 000E05BC  C8 02 90 58 */	lfd f0, "@97"@sda21(r0)
/* 800E3660 000E05C0  FC 42 08 2A */	fadd f2, f2, f1
/* 800E3664 000E05C4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800E3668 000E05C8  40 81 00 0C */	ble .L_800E3674
/* 800E366C 000E05CC  48 00 01 68 */	b .L_800E37D4
.L_800E3670:
/* 800E3670 000E05D0  FF E1 00 72 */	fmul f31, f1, f1
.L_800E3674:
/* 800E3674 000E05D4  C8 22 90 88 */	lfd f1, "@103"@sda21(r0)
/* 800E3678 000E05D8  C8 02 90 80 */	lfd f0, "@102"@sda21(r0)
/* 800E367C 000E05DC  C8 42 90 78 */	lfd f2, "@101"@sda21(r0)
/* 800E3680 000E05E0  FC 61 07 FA */	fmadd f3, f1, f31, f0
/* 800E3684 000E05E4  C8 C2 90 70 */	lfd f6, "@100"@sda21(r0)
/* 800E3688 000E05E8  C8 22 90 A8 */	lfd f1, "@107"@sda21(r0)
/* 800E368C 000E05EC  C8 02 90 A0 */	lfd f0, "@106"@sda21(r0)
/* 800E3690 000E05F0  C8 A2 90 68 */	lfd f5, "@99"@sda21(r0)
/* 800E3694 000E05F4  FC FF 10 FA */	fmadd f7, f31, f3, f2
/* 800E3698 000E05F8  C8 42 90 98 */	lfd f2, "@105"@sda21(r0)
/* 800E369C 000E05FC  FC 61 07 FA */	fmadd f3, f1, f31, f0
/* 800E36A0 000E0600  C8 82 90 60 */	lfd f4, "@98"@sda21(r0)
/* 800E36A4 000E0604  C8 22 90 90 */	lfd f1, "@104"@sda21(r0)
/* 800E36A8 000E0608  FC DF 31 FA */	fmadd f6, f31, f7, f6
/* 800E36AC 000E060C  C8 02 90 58 */	lfd f0, "@97"@sda21(r0)
/* 800E36B0 000E0610  FC 5F 10 FA */	fmadd f2, f31, f3, f2
/* 800E36B4 000E0614  C8 E1 00 08 */	lfd f7, 0x8(r1)
/* 800E36B8 000E0618  FC 7F 29 BA */	fmadd f3, f31, f6, f5
/* 800E36BC 000E061C  FC 3F 08 BA */	fmadd f1, f31, f2, f1
/* 800E36C0 000E0620  FC 5F 20 FA */	fmadd f2, f31, f3, f4
/* 800E36C4 000E0624  FC 1F 00 7A */	fmadd f0, f31, f1, f0
/* 800E36C8 000E0628  FC 3F 00 B2 */	fmul f1, f31, f2
/* 800E36CC 000E062C  FC 01 00 24 */	fdiv f0, f1, f0
/* 800E36D0 000E0630  FC 27 38 3A */	fmadd f1, f7, f0, f7
/* 800E36D4 000E0634  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 800E36D8 000E0638  48 00 00 FC */	b .L_800E37D4
.L_800E36DC:
/* 800E36DC 000E063C  FC 20 0A 10 */	fabs f1, f1
/* 800E36E0 000E0640  C9 22 90 58 */	lfd f9, "@97"@sda21(r0)
/* 800E36E4 000E0644  C8 02 90 B0 */	lfd f0, "@108"@sda21(r0)
/* 800E36E8 000E0648  C8 E2 90 88 */	lfd f7, "@103"@sda21(r0)
/* 800E36EC 000E064C  FD 09 08 28 */	fsub f8, f9, f1
/* 800E36F0 000E0650  C8 62 90 80 */	lfd f3, "@102"@sda21(r0)
/* 800E36F4 000E0654  C8 C2 90 78 */	lfd f6, "@101"@sda21(r0)
/* 800E36F8 000E0658  C8 A2 90 70 */	lfd f5, "@100"@sda21(r0)
/* 800E36FC 000E065C  FF E0 02 32 */	fmul f31, f0, f8
/* 800E3700 000E0660  C8 42 90 A8 */	lfd f2, "@107"@sda21(r0)
/* 800E3704 000E0664  C8 02 90 A0 */	lfd f0, "@106"@sda21(r0)
/* 800E3708 000E0668  C8 82 90 68 */	lfd f4, "@99"@sda21(r0)
/* 800E370C 000E066C  C8 22 90 98 */	lfd f1, "@105"@sda21(r0)
/* 800E3710 000E0670  FC E7 1F FA */	fmadd f7, f7, f31, f3
/* 800E3714 000E0674  C8 62 90 60 */	lfd f3, "@98"@sda21(r0)
/* 800E3718 000E0678  FC 42 07 FA */	fmadd f2, f2, f31, f0
/* 800E371C 000E067C  C8 02 90 90 */	lfd f0, "@104"@sda21(r0)
/* 800E3720 000E0680  D9 01 00 10 */	stfd f8, 0x10(r1)
/* 800E3724 000E0684  FC DF 31 FA */	fmadd f6, f31, f7, f6
/* 800E3728 000E0688  FC 3F 08 BA */	fmadd f1, f31, f2, f1
/* 800E372C 000E068C  FC 5F 29 BA */	fmadd f2, f31, f6, f5
/* 800E3730 000E0690  FC 1F 00 7A */	fmadd f0, f31, f1, f0
/* 800E3734 000E0694  FC 3F 20 BA */	fmadd f1, f31, f2, f4
/* 800E3738 000E0698  FF BF 48 3A */	fmadd f29, f31, f0, f9
/* 800E373C 000E069C  FC 1F 18 7A */	fmadd f0, f31, f1, f3
/* 800E3740 000E06A0  FC 20 F8 90 */	fmr f1, f31
/* 800E3744 000E06A4  FF DF 00 32 */	fmul f30, f31, f0
/* 800E3748 000E06A8  48 00 38 15 */	bl sqrt
/* 800E374C 000E06AC  3C 60 3F EF */	lis r3, 0x3fef
/* 800E3750 000E06B0  38 03 33 33 */	addi r0, r3, 0x3333
/* 800E3754 000E06B4  7C 1E 00 00 */	cmpw r30, r0
/* 800E3758 000E06B8  41 80 00 28 */	blt .L_800E3780
/* 800E375C 000E06BC  FC 9E E8 24 */	fdiv f4, f30, f29
/* 800E3760 000E06C0  C8 42 90 B8 */	lfd f2, "@109"@sda21(r0)
/* 800E3764 000E06C4  C8 02 90 48 */	lfd f0, "@95"@sda21(r0)
/* 800E3768 000E06C8  C8 62 90 40 */	lfd f3, "@94"@sda21(r0)
/* 800E376C 000E06CC  FC 21 09 3A */	fmadd f1, f1, f4, f1
/* 800E3770 000E06D0  D8 81 00 10 */	stfd f4, 0x10(r1)
/* 800E3774 000E06D4  FC 02 00 78 */	fmsub f0, f2, f1, f0
/* 800E3778 000E06D8  FC 23 00 28 */	fsub f1, f3, f0
/* 800E377C 000E06DC  48 00 00 48 */	b .L_800E37C4
.L_800E3780:
/* 800E3780 000E06E0  D8 21 00 10 */	stfd f1, 0x10(r1)
/* 800E3784 000E06E4  38 00 00 00 */	li r0, 0x0
/* 800E3788 000E06E8  C8 E2 90 B8 */	lfd f7, "@109"@sda21(r0)
/* 800E378C 000E06EC  FC BE E8 24 */	fdiv f5, f30, f29
/* 800E3790 000E06F0  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E3794 000E06F4  C8 02 90 48 */	lfd f0, "@95"@sda21(r0)
/* 800E3798 000E06F8  C9 01 00 10 */	lfd f8, 0x10(r1)
/* 800E379C 000E06FC  C8 42 90 C0 */	lfd f2, "@110"@sda21(r0)
/* 800E37A0 000E0700  FC 88 FA 3C */	fnmsub f4, f8, f8, f31
/* 800E37A4 000E0704  FC 61 40 2A */	fadd f3, f1, f8
/* 800E37A8 000E0708  FC C7 00 72 */	fmul f6, f7, f1
/* 800E37AC 000E070C  FC 24 18 24 */	fdiv f1, f4, f3
/* 800E37B0 000E0710  FC 27 00 7C */	fnmsub f1, f7, f1, f0
/* 800E37B4 000E0714  FC 07 12 3C */	fnmsub f0, f7, f8, f2
/* 800E37B8 000E0718  FC 26 09 78 */	fmsub f1, f6, f5, f1
/* 800E37BC 000E071C  FC 01 00 28 */	fsub f0, f1, f0
/* 800E37C0 000E0720  FC 22 00 28 */	fsub f1, f2, f0
.L_800E37C4:
/* 800E37C4 000E0724  2C 1F 00 00 */	cmpwi r31, 0x0
/* 800E37C8 000E0728  40 81 00 08 */	ble .L_800E37D0
/* 800E37CC 000E072C  48 00 00 08 */	b .L_800E37D4
.L_800E37D0:
/* 800E37D0 000E0730  FC 20 08 50 */	fneg f1, f1
.L_800E37D4:
/* 800E37D4 000E0734  E3 E1 00 48 */	psq_l f31, 0x48(r1), 0, qr0
/* 800E37D8 000E0738  CB E1 00 40 */	lfd f31, 0x40(r1)
/* 800E37DC 000E073C  E3 C1 00 38 */	psq_l f30, 0x38(r1), 0, qr0
/* 800E37E0 000E0740  CB C1 00 30 */	lfd f30, 0x30(r1)
/* 800E37E4 000E0744  E3 A1 00 28 */	psq_l f29, 0x28(r1), 0, qr0
/* 800E37E8 000E0748  CB A1 00 20 */	lfd f29, 0x20(r1)
/* 800E37EC 000E074C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800E37F0 000E0750  80 01 00 54 */	lwz r0, 0x54(r1)
/* 800E37F4 000E0754  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800E37F8 000E0758  7C 08 03 A6 */	mtlr r0
/* 800E37FC 000E075C  38 21 00 50 */	addi r1, r1, 0x50
/* 800E3800 000E0760  4E 80 00 20 */	blr
.endfn __ieee754_asin

.section .sdata2, "a"
.balign 8
.obj "@94", local
	.double 1.5707963267948966
.endobj "@94"
.obj "@95", local
	.double 0.00000000000000006123233995736766
.endobj "@95"
.obj "@96", local
	.4byte 0x7E37E43C
	.4byte 0x8800759C
.endobj "@96"
.obj "@97", local
	.double 1
.endobj "@97"
.obj "@98", local
	.double 0.16666666666666666
.endobj "@98"
.obj "@99", local
	.double -0.3255658186224009
.endobj "@99"
.obj "@100", local
	.double 0.20121253213486293
.endobj "@100"
.obj "@101", local
	.double -0.04005553450067941
.endobj "@101"
.obj "@102", local
	.double 0.0007915349942898145
.endobj "@102"
.obj "@103", local
	.double 0.00003479331075960212
.endobj "@103"
.obj "@104", local
	.double -2.403394911734414
.endobj "@104"
.obj "@105", local
	.double 2.0209457602335057
.endobj "@105"
.obj "@106", local
	.double -0.6882839716054533
.endobj "@106"
.obj "@107", local
	.double 0.07703815055590194
.endobj "@107"
.obj "@108", local
	.double 0.5
.endobj "@108"
.obj "@109", local
	.double 2
.endobj "@109"
.obj "@110", local
	.double 0.7853981633974483
.endobj "@110"
