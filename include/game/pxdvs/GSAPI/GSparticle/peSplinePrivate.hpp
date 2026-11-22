#ifndef PE_SPLINE_PRIVATE_HPP
#define PE_SPLINE_PRIVATE_HPP
#include <global.h>
#include <libc/stddef.h>
#include <game/pxdvs/GSAPI/GSgfxM/GSgfxColAu8.hpp>
struct PeColorSpline {
    u8 count, interval;
    u8 reserved[2];
    GSgfxColAu8 value;
    f32 time;
    GSgfxColAu8 points[1];
};
struct PeSpline {
    u8 flags, count;
    u8 reserved[2];
    f32 value, time;
    f32 points[1];
};
typedef char PeColorSplinePointsOffset[offsetof(PeColorSpline, points)==12 ? 1 : -1];
extern "C" f32 peSplineGetValue(PeSpline* spline, f32 time);
extern "C" void peColorSplineGetValue(GSgfxColAu8* result, PeColorSpline* spline, f32 time);
#endif
