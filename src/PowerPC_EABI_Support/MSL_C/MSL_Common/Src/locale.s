.include "macros.inc"
.file "locale.c"

# 0x802ECBA0..0x802ECBA8 | size: 0x8
.section .rodata, "a"
.balign 8

# .rodata:0x0 | 0x802ECBA0 | size: 0x5
.obj "@stringBase0", local
	.string "."
.L_802ECBA2:
	.string ""
	.string "C"
.endobj "@stringBase0"
	.byte 0x00, 0x00, 0x00

# 0x803D4A08..0x803D4A40 | size: 0x38
.section .data, "wa"
.balign 8

# .data:0x0 | 0x803D4A08 | size: 0x38
.obj __lconv, global
	.4byte "@stringBase0"
	.rel "@stringBase0", .L_802ECBA2
	.rel "@stringBase0", .L_802ECBA2
	.rel "@stringBase0", .L_802ECBA2
	.rel "@stringBase0", .L_802ECBA2
	.rel "@stringBase0", .L_802ECBA2
	.rel "@stringBase0", .L_802ECBA2
	.rel "@stringBase0", .L_802ECBA2
	.rel "@stringBase0", .L_802ECBA2
	.4byte 0x7F7F7F7F
	.4byte 0x7F7F7F00
	.rel "@stringBase0", .L_802ECBA2
	.4byte 0x7F7F7F7F
	.4byte 0x7F7F7F00
.endobj __lconv
