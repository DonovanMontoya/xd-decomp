.include "macros.inc"
.file "e_acos.c"

# 0x800E3390..0x800E35CC | size: 0x23C
.text
.balign 4

# .text:0x0 | 0x800E3390 | size: 0x23C
.fn __ieee754_acos, global
/* 800E3390 000E02F0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800E3394 000E02F4  7C 08 02 A6 */	mflr r0
/* 800E3398 000E02F8  90 01 00 34 */	stw r0, 0x34(r1)
/* 800E339C 000E02FC  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 800E33A0 000E0300  F3 E1 00 28 */	psq_st f31, 0x28(r1), 0, qr0
/* 800E33A4 000E0304  D8 21 00 08 */	stfd f1, 0x8(r1)
/* 800E33A8 000E0308  3C 00 3F F0 */	lis r0, 0x3ff0
/* 800E33AC 000E030C  80 81 00 08 */	lwz r4, 0x8(r1)
/* 800E33B0 000E0310  54 83 00 7E */	clrlwi r3, r4, 1
/* 800E33B4 000E0314  7C 03 00 00 */	cmpw r3, r0
/* 800E33B8 000E0318  41 80 00 38 */	blt .L_800E33F0
/* 800E33BC 000E031C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800E33C0 000E0320  3C 63 C0 10 */	subis r3, r3, 0x3ff0
/* 800E33C4 000E0324  7C 60 03 79 */	or. r0, r3, r0
/* 800E33C8 000E0328  40 82 00 1C */	bne .L_800E33E4
/* 800E33CC 000E032C  2C 04 00 00 */	cmpwi r4, 0x0
/* 800E33D0 000E0330  40 81 00 0C */	ble .L_800E33DC
/* 800E33D4 000E0334  C8 22 8F B8 */	lfd f1, "@83"@sda21(r0)
/* 800E33D8 000E0338  48 00 01 DC */	b .L_800E35B4
.L_800E33DC:
/* 800E33DC 000E033C  C8 22 8F C0 */	lfd f1, "@84"@sda21(r0)
/* 800E33E0 000E0340  48 00 01 D4 */	b .L_800E35B4
.L_800E33E4:
/* 800E33E4 000E0344  3C 60 80 4F */	lis r3, __float_nan@ha
/* 800E33E8 000E0348  C0 23 82 E0 */	lfs f1, __float_nan@l(r3)
/* 800E33EC 000E034C  48 00 01 C8 */	b .L_800E35B4
.L_800E33F0:
/* 800E33F0 000E0350  3C 00 3F E0 */	lis r0, 0x3fe0
/* 800E33F4 000E0354  7C 03 00 00 */	cmpw r3, r0
/* 800E33F8 000E0358  40 80 00 8C */	bge .L_800E3484
/* 800E33FC 000E035C  3C 00 3C 60 */	lis r0, 0x3c60
/* 800E3400 000E0360  7C 03 00 00 */	cmpw r3, r0
/* 800E3404 000E0364  41 81 00 0C */	bgt .L_800E3410
/* 800E3408 000E0368  C8 22 8F C8 */	lfd f1, "@85"@sda21(r0)
/* 800E340C 000E036C  48 00 01 A8 */	b .L_800E35B4
.L_800E3410:
/* 800E3410 000E0370  FD 41 00 72 */	fmul f10, f1, f1
/* 800E3414 000E0374  C8 42 90 00 */	lfd f2, "@92"@sda21(r0)
/* 800E3418 000E0378  C8 02 8F F8 */	lfd f0, "@91"@sda21(r0)
/* 800E341C 000E037C  C8 62 8F F0 */	lfd f3, "@90"@sda21(r0)
/* 800E3420 000E0380  C9 02 8F E8 */	lfd f8, "@89"@sda21(r0)
/* 800E3424 000E0384  FC 82 02 BA */	fmadd f4, f2, f10, f0
/* 800E3428 000E0388  C8 42 90 28 */	lfd f2, "@97"@sda21(r0)
/* 800E342C 000E038C  C8 02 90 20 */	lfd f0, "@96"@sda21(r0)
/* 800E3430 000E0390  C8 E2 8F E0 */	lfd f7, "@88"@sda21(r0)
/* 800E3434 000E0394  FD 2A 19 3A */	fmadd f9, f10, f4, f3
/* 800E3438 000E0398  C8 82 90 18 */	lfd f4, "@95"@sda21(r0)
/* 800E343C 000E039C  C8 C2 8F D8 */	lfd f6, "@87"@sda21(r0)
/* 800E3440 000E03A0  FC A2 02 BA */	fmadd f5, f2, f10, f0
/* 800E3444 000E03A4  C8 62 90 10 */	lfd f3, "@94"@sda21(r0)
/* 800E3448 000E03A8  C8 42 90 08 */	lfd f2, "@93"@sda21(r0)
/* 800E344C 000E03AC  FD 0A 42 7A */	fmadd f8, f10, f9, f8
/* 800E3450 000E03B0  C8 02 8F D0 */	lfd f0, "@86"@sda21(r0)
/* 800E3454 000E03B4  C9 22 8F C8 */	lfd f9, "@85"@sda21(r0)
/* 800E3458 000E03B8  FC 8A 21 7A */	fmadd f4, f10, f5, f4
/* 800E345C 000E03BC  FC AA 3A 3A */	fmadd f5, f10, f8, f7
/* 800E3460 000E03C0  FC 6A 19 3A */	fmadd f3, f10, f4, f3
/* 800E3464 000E03C4  FC 8A 31 7A */	fmadd f4, f10, f5, f6
/* 800E3468 000E03C8  FC 4A 10 FA */	fmadd f2, f10, f3, f2
/* 800E346C 000E03CC  FC 6A 01 32 */	fmul f3, f10, f4
/* 800E3470 000E03D0  FC 43 10 24 */	fdiv f2, f3, f2
/* 800E3474 000E03D4  FC 01 00 BC */	fnmsub f0, f1, f2, f0
/* 800E3478 000E03D8  FC 01 00 28 */	fsub f0, f1, f0
/* 800E347C 000E03DC  FC 29 00 28 */	fsub f1, f9, f0
/* 800E3480 000E03E0  48 00 01 34 */	b .L_800E35B4
.L_800E3484:
/* 800E3484 000E03E4  2C 04 00 00 */	cmpwi r4, 0x0
/* 800E3488 000E03E8  40 80 00 90 */	bge .L_800E3518
/* 800E348C 000E03EC  C8 02 90 08 */	lfd f0, "@93"@sda21(r0)
/* 800E3490 000E03F0  C8 42 90 30 */	lfd f2, "@98"@sda21(r0)
/* 800E3494 000E03F4  FC 00 08 2A */	fadd f0, f0, f1
/* 800E3498 000E03F8  FF E2 00 32 */	fmul f31, f2, f0
/* 800E349C 000E03FC  FC 20 F8 90 */	fmr f1, f31
/* 800E34A0 000E0400  48 00 3A BD */	bl sqrt
/* 800E34A4 000E0404  C8 62 90 00 */	lfd f3, "@92"@sda21(r0)
/* 800E34A8 000E0408  C8 42 8F F8 */	lfd f2, "@91"@sda21(r0)
/* 800E34AC 000E040C  C8 02 8F F0 */	lfd f0, "@90"@sda21(r0)
/* 800E34B0 000E0410  FC 83 17 FA */	fmadd f4, f3, f31, f2
/* 800E34B4 000E0414  C8 A2 8F E8 */	lfd f5, "@89"@sda21(r0)
/* 800E34B8 000E0418  C8 62 90 28 */	lfd f3, "@97"@sda21(r0)
/* 800E34BC 000E041C  C8 42 90 20 */	lfd f2, "@96"@sda21(r0)
/* 800E34C0 000E0420  C8 E2 8F E0 */	lfd f7, "@88"@sda21(r0)
/* 800E34C4 000E0424  FD 1F 01 3A */	fmadd f8, f31, f4, f0
/* 800E34C8 000E0428  C8 02 90 18 */	lfd f0, "@95"@sda21(r0)
/* 800E34CC 000E042C  FC 43 17 FA */	fmadd f2, f3, f31, f2
/* 800E34D0 000E0430  C8 C2 8F D8 */	lfd f6, "@87"@sda21(r0)
/* 800E34D4 000E0434  C8 82 90 10 */	lfd f4, "@94"@sda21(r0)
/* 800E34D8 000E0438  FD 1F 2A 3A */	fmadd f8, f31, f8, f5
/* 800E34DC 000E043C  C8 62 90 08 */	lfd f3, "@93"@sda21(r0)
/* 800E34E0 000E0440  FC BF 00 BA */	fmadd f5, f31, f2, f0
/* 800E34E4 000E0444  C8 42 8F D0 */	lfd f2, "@86"@sda21(r0)
/* 800E34E8 000E0448  FC FF 3A 3A */	fmadd f7, f31, f8, f7
/* 800E34EC 000E044C  C9 02 90 38 */	lfd f8, "@99"@sda21(r0)
/* 800E34F0 000E0450  C8 02 8F C0 */	lfd f0, "@84"@sda21(r0)
/* 800E34F4 000E0454  FC 9F 21 7A */	fmadd f4, f31, f5, f4
/* 800E34F8 000E0458  FC BF 31 FA */	fmadd f5, f31, f7, f6
/* 800E34FC 000E045C  FC 7F 19 3A */	fmadd f3, f31, f4, f3
/* 800E3500 000E0460  FC 9F 01 72 */	fmul f4, f31, f5
/* 800E3504 000E0464  FC 64 18 24 */	fdiv f3, f4, f3
/* 800E3508 000E0468  FC 43 10 78 */	fmsub f2, f3, f1, f2
/* 800E350C 000E046C  FC 21 10 2A */	fadd f1, f1, f2
/* 800E3510 000E0470  FC 28 00 7C */	fnmsub f1, f8, f1, f0
/* 800E3514 000E0474  48 00 00 A0 */	b .L_800E35B4
.L_800E3518:
/* 800E3518 000E0478  C8 02 90 08 */	lfd f0, "@93"@sda21(r0)
/* 800E351C 000E047C  C8 42 90 30 */	lfd f2, "@98"@sda21(r0)
/* 800E3520 000E0480  FC 00 08 28 */	fsub f0, f0, f1
/* 800E3524 000E0484  FF E2 00 32 */	fmul f31, f2, f0
/* 800E3528 000E0488  FC 20 F8 90 */	fmr f1, f31
/* 800E352C 000E048C  48 00 3A 31 */	bl sqrt
/* 800E3530 000E0490  C8 42 90 00 */	lfd f2, "@92"@sda21(r0)
/* 800E3534 000E0494  38 00 00 00 */	li r0, 0x0
/* 800E3538 000E0498  C8 02 8F F8 */	lfd f0, "@91"@sda21(r0)
/* 800E353C 000E049C  D8 21 00 10 */	stfd f1, 0x10(r1)
/* 800E3540 000E04A0  FC 62 07 FA */	fmadd f3, f2, f31, f0
/* 800E3544 000E04A4  C8 02 8F F0 */	lfd f0, "@90"@sda21(r0)
/* 800E3548 000E04A8  90 01 00 14 */	stw r0, 0x14(r1)
/* 800E354C 000E04AC  C8 42 8F E8 */	lfd f2, "@89"@sda21(r0)
/* 800E3550 000E04B0  C9 21 00 10 */	lfd f9, 0x10(r1)
/* 800E3554 000E04B4  FC BF 00 FA */	fmadd f5, f31, f3, f0
/* 800E3558 000E04B8  C8 82 90 28 */	lfd f4, "@97"@sda21(r0)
/* 800E355C 000E04BC  C8 02 90 20 */	lfd f0, "@96"@sda21(r0)
/* 800E3560 000E04C0  FC 69 FA 7C */	fnmsub f3, f9, f9, f31
/* 800E3564 000E04C4  C8 E2 8F E0 */	lfd f7, "@88"@sda21(r0)
/* 800E3568 000E04C8  FD 1F 11 7A */	fmadd f8, f31, f5, f2
/* 800E356C 000E04CC  C8 42 90 18 */	lfd f2, "@95"@sda21(r0)
/* 800E3570 000E04D0  FC A4 07 FA */	fmadd f5, f4, f31, f0
/* 800E3574 000E04D4  C8 C2 8F D8 */	lfd f6, "@87"@sda21(r0)
/* 800E3578 000E04D8  C8 02 90 10 */	lfd f0, "@94"@sda21(r0)
/* 800E357C 000E04DC  FC FF 3A 3A */	fmadd f7, f31, f8, f7
/* 800E3580 000E04E0  C8 82 90 08 */	lfd f4, "@93"@sda21(r0)
/* 800E3584 000E04E4  FC BF 11 7A */	fmadd f5, f31, f5, f2
/* 800E3588 000E04E8  C8 42 90 38 */	lfd f2, "@99"@sda21(r0)
/* 800E358C 000E04EC  FC DF 31 FA */	fmadd f6, f31, f7, f6
/* 800E3590 000E04F0  FC BF 01 7A */	fmadd f5, f31, f5, f0
/* 800E3594 000E04F4  FC 01 48 2A */	fadd f0, f1, f9
/* 800E3598 000E04F8  FC DF 01 B2 */	fmul f6, f31, f6
/* 800E359C 000E04FC  FC 9F 21 7A */	fmadd f4, f31, f5, f4
/* 800E35A0 000E0500  FC 03 00 24 */	fdiv f0, f3, f0
/* 800E35A4 000E0504  FC 66 20 24 */	fdiv f3, f6, f4
/* 800E35A8 000E0508  FC 03 00 7A */	fmadd f0, f3, f1, f0
/* 800E35AC 000E050C  FC 09 00 2A */	fadd f0, f9, f0
/* 800E35B0 000E0510  FC 22 00 32 */	fmul f1, f2, f0
.L_800E35B4:
/* 800E35B4 000E0514  E3 E1 00 28 */	psq_l f31, 0x28(r1), 0, qr0
/* 800E35B8 000E0518  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800E35BC 000E051C  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 800E35C0 000E0520  7C 08 03 A6 */	mtlr r0
/* 800E35C4 000E0524  38 21 00 30 */	addi r1, r1, 0x30
/* 800E35C8 000E0528  4E 80 00 20 */	blr
.endfn __ieee754_acos

# 0x804ECD78..0x804ECE00 | size: 0x88
.section .sdata2, "a"
.balign 8
.obj "@83", local
	.double 0
.endobj "@83"
.obj "@84", local
	.double 3.141592653589793
.endobj "@84"
.obj "@85", local
	.double 1.5707963267948966
.endobj "@85"
.obj "@86", local
	.double 0.00000000000000006123233995736766
.endobj "@86"
.obj "@87", local
	.double 0.16666666666666666
.endobj "@87"
.obj "@88", local
	.double -0.3255658186224009
.endobj "@88"
.obj "@89", local
	.double 0.20121253213486293
.endobj "@89"
.obj "@90", local
	.double -0.04005553450067941
.endobj "@90"
.obj "@91", local
	.double 0.0007915349942898145
.endobj "@91"
.obj "@92", local
	.double 0.00003479331075960212
.endobj "@92"
.obj "@93", local
	.double 1
.endobj "@93"
.obj "@94", local
	.double -2.403394911734414
.endobj "@94"
.obj "@95", local
	.double 2.0209457602335057
.endobj "@95"
.obj "@96", local
	.double -0.6882839716054533
.endobj "@96"
.obj "@97", local
	.double 0.07703815055590194
.endobj "@97"
.obj "@98", local
	.double 0.5
.endobj "@98"
.obj "@99", local
	.double 2
.endobj "@99"
