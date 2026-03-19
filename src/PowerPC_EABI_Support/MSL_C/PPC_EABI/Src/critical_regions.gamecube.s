.include "macros.inc"
.file "critical_regions.gamecube.c"

# 0x800DE7BC..0x800DE7C8 | size: 0xC
.text
.balign 4

# .text:0x0 | 0x800DE7BC | size: 0x4
.fn __end_critical_region, global
/* 800DE7BC 000DB71C  4E 80 00 20 */	blr
.endfn __end_critical_region

# .text:0x4 | 0x800DE7C0 | size: 0x4
.fn __begin_critical_region, global
/* 800DE7C0 000DB720  4E 80 00 20 */	blr
.endfn __begin_critical_region

# .text:0x8 | 0x800DE7C4 | size: 0x4
.fn __kill_critical_regions, global
/* 800DE7C4 000DB724  4E 80 00 20 */	blr
.endfn __kill_critical_regions
