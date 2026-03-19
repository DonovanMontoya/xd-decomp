.include "macros.inc"
.file "CPlusLibPPC.cp"

# 0x800D9CF8..0x800D9D28 | size: 0x30
.text
.balign 4

# .text:0x0 | 0x800D9CF8 | size: 0x30
.fn __copy, global
/* 800D9CF8 000D6C58  28 03 00 00 */	cmplwi r3, 0x0
/* 800D9CFC 000D6C5C  4D 82 00 20 */	beqlr
/* 800D9D00 000D6C60  28 05 00 00 */	cmplwi r5, 0x0
/* 800D9D04 000D6C64  4D 82 00 20 */	beqlr
/* 800D9D08 000D6C68  7C 66 1B 78 */	mr r6, r3
.L_800D9D0C:
/* 800D9D0C 000D6C6C  88 04 00 00 */	lbz r0, 0x0(r4)
/* 800D9D10 000D6C70  34 A5 FF FF */	subic. r5, r5, 0x1
/* 800D9D14 000D6C74  38 84 00 01 */	addi r4, r4, 0x1
/* 800D9D18 000D6C78  98 06 00 00 */	stb r0, 0x0(r6)
/* 800D9D1C 000D6C7C  38 C6 00 01 */	addi r6, r6, 0x1
/* 800D9D20 000D6C80  40 82 FF EC */	bne .L_800D9D0C
/* 800D9D24 000D6C84  4E 80 00 20 */	blr
.endfn __copy
