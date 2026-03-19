.include "macros.inc"
.file "Gecko_ExceptionPPC.cp"

# 0x800DA8FC..0x800DA964 | size: 0x68
.text
.balign 4

# .text:0x0 | 0x800DA8FC | size: 0x34
.fn __unregister_fragment, global
/* 800DA8FC 00000040  2C 03 00 00 */	cmpwi r3, 0x0
/* 800DA900 00000044  4D 80 00 20 */	bltlr
/* 800DA904 00000048  2C 03 00 01 */	cmpwi r3, 0x1
/* 800DA908 0000004C  4C 80 00 20 */	bgelr
/* 800DA90C 00000050  1C 83 00 0C */	mulli r4, r3, 0xc
/* 800DA910 00000054  3C 60 00 00 */	lis r3, fragmentinfo@ha
/* 800DA914 00000058  38 00 00 00 */	li r0, 0x0
/* 800DA918 0000005C  38 63 00 00 */	addi r3, r3, fragmentinfo@l
/* 800DA91C 00000060  7C 63 22 14 */	add r3, r3, r4
/* 800DA920 00000064  90 03 00 00 */	stw r0, 0x0(r3)
/* 800DA924 00000068  90 03 00 04 */	stw r0, 0x4(r3)
/* 800DA928 0000006C  90 03 00 08 */	stw r0, 0x8(r3)
/* 800DA92C 00000070  4E 80 00 20 */	blr
.endfn __unregister_fragment

# .text:0x34 | 0x800DA930 | size: 0x34
.fn __register_fragment, global
/* 800DA930 00000074  3C A0 00 00 */	lis r5, fragmentinfo@ha
/* 800DA934 00000078  38 A5 00 00 */	addi r5, r5, fragmentinfo@l
/* 800DA938 0000007C  80 05 00 08 */	lwz r0, 0x8(r5)
/* 800DA93C 00000080  2C 00 00 00 */	cmpwi r0, 0x0
/* 800DA940 00000084  40 82 00 1C */	bne .L_800DA95C
/* 800DA944 00000088  90 65 00 00 */	stw r3, 0x0(r5)
/* 800DA948 0000008C  38 00 00 01 */	li r0, 0x1
/* 800DA94C 00000090  38 60 00 00 */	li r3, 0x0
/* 800DA950 00000094  90 85 00 04 */	stw r4, 0x4(r5)
/* 800DA954 00000098  90 05 00 08 */	stw r0, 0x8(r5)
/* 800DA958 0000009C  4E 80 00 20 */	blr
.L_800DA95C:
/* 800DA95C 000000A0  38 60 FF FF */	li r3, -0x1
/* 800DA960 000000A4  4E 80 00 20 */	blr
.endfn __register_fragment

# 0x804426A8..0x804426B8 | size: 0x10
.section .bss, "wa", @nobits
.balign 8

# .bss:0x0 | 0x804426A8 | size: 0xC
.obj fragmentinfo, local
	.skip 0xC
.endobj fragmentinfo

# .bss:0xC | 0x804426B4 | size: 0x4
.obj gap_08_804426B4_bss, global
.hidden gap_08_804426B4_bss
	.skip 0x4
.endobj gap_08_804426B4_bss
