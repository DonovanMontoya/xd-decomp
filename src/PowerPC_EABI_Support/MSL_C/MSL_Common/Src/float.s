.include "macros.inc"
.file "float.c"

# 0x804E82E0..0x804E8318 | size: 0x38
.section .sdata, "wa"
.balign 8

# .sdata:0x0 | 0x804E82E0 | size: 0x4
.obj __float_nan, global
	.4byte 0x7FFFFFFF
.endobj __float_nan

# .sdata:0x4 | 0x804E82E4 | size: 0x4
.obj __float_huge, global
	.float inf
.endobj __float_huge

# .sdata:0x8 | 0x804E82E8 | size: 0x8
.obj __double_min, global
	.4byte 0x00100000
	.4byte 0x00000000
.endobj __double_min

# .sdata:0x10 | 0x804E82F0 | size: 0x8
.obj __double_max, global
	.4byte 0x7FEFFFFF
	.4byte 0xFFFFFFFF
.endobj __double_max

# .sdata:0x18 | 0x804E82F8 | size: 0x8
.obj __double_huge, global
	.4byte 0x7FF00000
	.4byte 0x00000000
.endobj __double_huge

# .sdata:0x20 | 0x804E8300 | size: 0x8
.obj __extended_min, global
	.4byte 0x00100000
	.4byte 0x00000000
.endobj __extended_min

# .sdata:0x28 | 0x804E8308 | size: 0x8
.obj __extended_max, global
	.4byte 0x7FEFFFFF
	.4byte 0xFFFFFFFF
.endobj __extended_max

# .sdata:0x30 | 0x804E8310 | size: 0x4
.obj __float_min, global
	.float 0.000000000000000000000000000000000000011754944
.endobj __float_min

# .sdata:0x34 | 0x804E8314 | size: 0x4
.obj __float_epsilon, global
	.float 0.00000011920929
.endobj __float_epsilon
