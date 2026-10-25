#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>

struct GSaxisVector {
    f32 x;
    f32 y;
    f32 z;

    GSaxisVector(f32 xValue, f32 yValue, f32 zValue)
        : x(xValue), y(yValue), z(zValue) {}
};

GSaxisVector xAxisVector(1.0f, 0.0f, 0.0f);
GSaxisVector yAxisVector(0.0f, 1.0f, 0.0f);
GSaxisVector zAxisVector(0.0f, 0.0f, 1.0f);
GSaxisVector zeroVector(0.0f, 0.0f, 0.0f);
GSaxisVector unitScaleVector(1.0f, 1.0f, 1.0f);

extern "C" double asin(double);
extern "C" double atan(double);
#include <dolphin/mtx.h>


extern "C" void GSvecMakeFromQuat(Vec* result, const Quaternion* quat) {
    const f32 x = quat->x, y = quat->y, z = quat->z, w = quat->w;
    const f32 xx = x * x, yy = y * y, zz = z * z, ww = w * w;
    result->x = asin(-2.0f * (x * z - w * y));
    result->y = atan((2.0f * (x * y + w * z)) / (ww + xx - yy - zz));
    result->z = atan((2.0f * (w * x + y * z)) / (zz + (ww - xx - yy)));
}
extern "C" void GSvecTransformQuat(Vec* result, const Quaternion* quat, const Vec* vector) {
    f32 vx = vector->x;
    f32 dot;
    f32 z = quat->z;
    f32 w = quat->w;
    f32 vy = vector->y;
    f32 vz = vector->z;
    f32 x = quat->x;
    f32 y = quat->y;
    const f32 ix = vx * w + y * vz - vy * z;
    const f32 iy = vy * w + z * vx - vz * x;
    const f32 iz = vz * w + x * vy - vx * y;
    dot = vx * x + y * vy + vz * z;
    result->x = ix * w + x * dot + y * iz - iy * z;
    result->y = iy * w + y * dot + z * ix - iz * x;
    result->z = iz * w + z * dot + x * iy - ix * y;
}
