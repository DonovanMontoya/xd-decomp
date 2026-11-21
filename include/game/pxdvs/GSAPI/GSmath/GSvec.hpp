#ifndef GS_VEC_H
#define GS_VEC_H

#include <global.h>

struct GSvecData {
  f32 param1; // 0x0
  f32 param2; // 0x4
  f32 param3; // 0x8
};

struct GSvec : GSvecData {
  GSvec() {}

  void set(f32 x, f32 y, f32 z) {
    param1 = x;
    param2 = y;
    param3 = z;
  }
};

#endif
