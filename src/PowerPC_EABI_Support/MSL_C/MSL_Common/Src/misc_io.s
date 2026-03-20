.include "macros.inc"
.file "misc_io.c"

# 0x800DF780..0x800DF790 | size: 0x10
.text
.balign 4

# .text:0x0 | 0x800DF780 | size: 0x10
.fn __stdio_atexit, global
/* 800DF780 000DC6E0  3C 60 80 0E */	lis r3, __close_all@ha
/* 800DF784 000DC6E4  38 03 B0 30 */	addi r0, r3, __close_all@l
/* 800DF788 000DC6E8  90 0D B0 48 */	stw r0, __stdio_exit@sda21(r0)
/* 800DF78C 000DC6EC  4E 80 00 20 */	blr
.endfn __stdio_atexit
