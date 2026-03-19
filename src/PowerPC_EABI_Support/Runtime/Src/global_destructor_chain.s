.include "macros.inc"
.file "global_destructor_chain.c"

# 0x8000E74C..0x8000E794 | size: 0x48
.text
.balign 4

# .text:0x0 | 0x8000E74C | size: 0x48
.fn __destroy_global_chain, global
/* 8000E74C 0000B6AC  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8000E750 0000B6B0  7C 08 02 A6 */	mflr r0
/* 8000E754 0000B6B4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8000E758 0000B6B8  48 00 00 20 */	b .L_8000E778
.L_8000E75C:
/* 8000E75C 0000B6BC  80 03 00 00 */	lwz r0, 0x0(r3)
/* 8000E760 0000B6C0  38 80 FF FF */	li r4, -0x1
/* 8000E764 0000B6C4  90 0D A8 A8 */	stw r0, __global_destructor_chain@sda21(r0)
/* 8000E768 0000B6C8  81 83 00 04 */	lwz r12, 0x4(r3)
/* 8000E76C 0000B6CC  80 63 00 08 */	lwz r3, 0x8(r3)
/* 8000E770 0000B6D0  7D 89 03 A6 */	mtctr r12
/* 8000E774 0000B6D4  4E 80 04 21 */	bctrl
.L_8000E778:
/* 8000E778 0000B6D8  80 6D A8 A8 */	lwz r3, __global_destructor_chain@sda21(r0)
/* 8000E77C 0000B6DC  28 03 00 00 */	cmplwi r3, 0x0
/* 8000E780 0000B6E0  40 82 FF DC */	bne .L_8000E75C
/* 8000E784 0000B6E4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8000E788 0000B6E8  7C 08 03 A6 */	mtlr r0
/* 8000E78C 0000B6EC  38 21 00 10 */	addi r1, r1, 0x10
/* 8000E790 0000B6F0  4E 80 00 20 */	blr
.endfn __destroy_global_chain

# 0x804EA6C8..0x804EA6D0 | size: 0x8
.section .sbss, "wa", @nobits
.balign 8

# .sbss:0x0 | 0x804EA6C8 | size: 0x4
.obj __global_destructor_chain, global
	.skip 0x4
.endobj __global_destructor_chain

# .sbss:0x4 | 0x804EA6CC | size: 0x4
.obj gap_10_804EA6CC_sbss, global
.hidden gap_10_804EA6CC_sbss
	.skip 0x4
.endobj gap_10_804EA6CC_sbss
