#ifndef GSCOLSYS2_WALK_HPP
#define GSCOLSYS2_WALK_HPP

#include <dolphin/types.h>

struct GSvec;

struct GSwalkHit {
    f32 height;
    u16 attrHi;
    u16 attrLo;
    u8 layer;
    u8 subLayer;
};

extern "C" s32 GScolsys2WalkGetHeight(GSvec* pos, GSwalkHit* hits);

#endif
