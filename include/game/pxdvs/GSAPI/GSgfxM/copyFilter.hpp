#ifndef GSGFX_COPY_FILTER_HPP
#define GSGFX_COPY_FILTER_HPP

#include <dolphin/types.h>

extern "C" {
u8* GSgfx_GCWriteCopyFilterDirect(u8* destination, u8 antialias, const u8 samples[12][2], u8 verticalFilter, const u8 filter[7]);
void GSgfx_GCWriteCopyFilter(u8 antialias, const u8 samples[12][2], u8 verticalFilter, const u8 filter[7]);
}

#endif
