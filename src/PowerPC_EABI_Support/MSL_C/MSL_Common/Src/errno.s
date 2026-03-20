.include "macros.inc"
.file "errno.c"

# 0x804EAE78..0x804EAE80 | size: 0x8
.section .sbss, "wa", @nobits
.balign 8

# .sbss:0x0 | 0x804EAE78 | size: 0x4
.obj errno, global
	.skip 0x4
.endobj errno

# .sbss:0x4 | 0x804EAE7C | size: 0x4
.obj gap_10_804EAE7C_sbss, global
.hidden gap_10_804EAE7C_sbss
	.skip 0x4
.endobj gap_10_804EAE7C_sbss
