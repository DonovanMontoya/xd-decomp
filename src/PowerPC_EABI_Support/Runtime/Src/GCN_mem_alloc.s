.include "macros.inc"
.file "GCN_mem_alloc.c"

# 0x800DA964..0x800DAA1C | size: 0xB8
.text
.balign 4

# .text:0x0 | 0x800DA964 | size: 0xB8
.fn __sys_free, weak
/* 800DA964 000D78C4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800DA968 000D78C8  7C 08 02 A6 */	mflr r0
/* 800DA96C 000D78CC  90 01 00 24 */	stw r0, 0x24(r1)
/* 800DA970 000D78D0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800DA974 000D78D4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800DA978 000D78D8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800DA97C 000D78DC  7C 7D 1B 78 */	mr r29, r3
/* 800DA980 000D78E0  80 0D 82 D8 */	lwz r0, __OSCurrHeap@sda21(r0)
/* 800DA984 000D78E4  2C 00 FF FF */	cmpwi r0, -0x1
/* 800DA988 000D78E8  40 82 00 6C */	bne .L_800DA9F4
/* 800DA98C 000D78EC  3C 60 80 2F */	lis r3, "@55"@ha
/* 800DA990 000D78F0  38 63 CA 30 */	addi r3, r3, "@55"@l
/* 800DA994 000D78F4  4C C6 31 82 */	crclr cr1eq
/* 800DA998 000D78F8  4B FD 12 E9 */	bl OSReport
/* 800DA99C 000D78FC  3C 60 80 2F */	lis r3, "@56"@ha
/* 800DA9A0 000D7900  38 63 CA 68 */	addi r3, r3, "@56"@l
/* 800DA9A4 000D7904  4C C6 31 82 */	crclr cr1eq
/* 800DA9A8 000D7908  4B FD 12 D9 */	bl OSReport
/* 800DA9AC 000D790C  4B FC FF AD */	bl OSGetArenaLo
/* 800DA9B0 000D7910  7C 7F 1B 78 */	mr r31, r3
/* 800DA9B4 000D7914  4B FC FF 9D */	bl OSGetArenaHi
/* 800DA9B8 000D7918  7C 7E 1B 78 */	mr r30, r3
/* 800DA9BC 000D791C  7F E3 FB 78 */	mr r3, r31
/* 800DA9C0 000D7920  38 A0 00 01 */	li r5, 0x1
/* 800DA9C4 000D7924  7F C4 F3 78 */	mr r4, r30
/* 800DA9C8 000D7928  4B FC DB 4D */	bl OSInitAlloc
/* 800DA9CC 000D792C  7C 7F 1B 78 */	mr r31, r3
/* 800DA9D0 000D7930  4B FC FF 99 */	bl OSSetArenaLo
/* 800DA9D4 000D7934  38 1F 00 1F */	addi r0, r31, 0x1f
/* 800DA9D8 000D7938  57 DE 00 34 */	clrrwi r30, r30, 5
/* 800DA9DC 000D793C  54 03 00 34 */	clrrwi r3, r0, 5
/* 800DA9E0 000D7940  7F C4 F3 78 */	mr r4, r30
/* 800DA9E4 000D7944  4B FC DA 75 */	bl OSCreateHeap
/* 800DA9E8 000D7948  4B FC DC 25 */	bl OSSetCurrentHeap
/* 800DA9EC 000D794C  7F C3 F3 78 */	mr r3, r30
/* 800DA9F0 000D7950  4B FC FF 79 */	bl OSSetArenaLo
.L_800DA9F4:
/* 800DA9F4 000D7954  80 6D 82 D8 */	lwz r3, __OSCurrHeap@sda21(r0)
/* 800DA9F8 000D7958  7F A4 EB 78 */	mr r4, r29
/* 800DA9FC 000D795C  4B FC DD 5D */	bl OSFreeToHeap
/* 800DAA00 000D7960  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800DAA04 000D7964  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800DAA08 000D7968  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800DAA0C 000D796C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800DAA10 000D7970  7C 08 03 A6 */	mtlr r0
/* 800DAA14 000D7974  38 21 00 20 */	addi r1, r1, 0x20
/* 800DAA18 000D7978  4E 80 00 20 */	blr
.endfn __sys_free

# 0x802ECA30..0x802ECAA8 | size: 0x78
.rodata
.balign 8

# .rodata:0x0 | 0x802ECA30 | size: 0x36
.obj "@55", local
	.string "GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n"
.endobj "@55"

# .rodata:0x36 | 0x802ECA66 | size: 0x2
.obj gap_06_802ECA66_rodata, global
.hidden gap_06_802ECA66_rodata
	.2byte 0x0000
.endobj gap_06_802ECA66_rodata

# .rodata:0x38 | 0x802ECA68 | size: 0x39
.obj "@56", local
	.string "Metrowerks CW runtime library initializing default heap\n"
.endobj "@56"

# .rodata:0x71 | 0x802ECAA1 | size: 0x7
.obj gap_06_802ECAA1_rodata, global
.hidden gap_06_802ECAA1_rodata
	.4byte 0x00000000
	.byte 0x00, 0x00, 0x00
.endobj gap_06_802ECAA1_rodata
