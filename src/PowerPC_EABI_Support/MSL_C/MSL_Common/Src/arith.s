.include "macros.inc"
.file "arith.c"

# 0x800DE6B4..0x800DE6C4 | size: 0x10
.text
.balign 4

# .text:0x0 | 0x800DE6B4 | size: 0x10
.fn abs, global
/* 800DE6B4 000DB614  7C 64 FE 70 */	srawi r4, r3, 31
/* 800DE6B8 000DB618  7C 80 1A 78 */	xor r0, r4, r3
/* 800DE6BC 000DB61C  7C 64 00 50 */	subf r3, r4, r0
/* 800DE6C0 000DB620  4E 80 00 20 */	blr
.endfn abs
