#pragma defer_codegen on
#include <dolphin/types.h>
#include <game/maximum/GSAPI/baselib/math_support.h>
#include "game/maximum/GSAPI/baselib/quatlib.h"
#ifdef __cplusplus
extern "C" {
#endif
double sin(double);
double cos(double);
double acos(double);
static inline float quatSin(float x) { return (float)sin(x); }
static inline float quatAcos(float x) { return (float)acos(x); }




int EulerToQuat(HSD_Vec3* euler, HSD_Quaternion* q)
{
    float cx;
    float cy;
    float cz;
    float sx;
    float sy;
    float sz;
    float cc;
    float ss;

    cx = (float) cos(0.5F * euler->x);
    cy = (float) cos(0.5F * euler->y);
    cz = (float) cos(0.5F * euler->z);
    sx = quatSin(0.5F * euler->x);
    sy = quatSin(0.5F * euler->y);
    sz = quatSin(0.5F * euler->z);

    ss = sy * sz;
    cc = cy * cz;
    q->w = cx * cc + sx * ss;
    q->x = sx * cc - cx * ss;
    q->y = cz * (cx * sy) + sz * (sx * cy);
    q->z = sz * (cx * cy) - cz * (sx * sy);

    return 1;
}

int QuatSlerp(HSD_Quaternion* p, HSD_Quaternion* q, HSD_Quaternion* out, float t)
{
    float cosom;
    float t2;
    float theta;
    float sinom;
    float sp;
    float sq;

    cosom = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;

    if ((1.0F + cosom) > 1e-10F) {
        if ((1.0F - cosom) > 1e-10F) {
            theta = quatAcos(cosom);
            sinom = quatSin(theta);
            sp = quatSin((1.0F - t) * theta) / sinom;
            sq = quatSin(t * theta) / sinom;
        } else {
            sq = t;
            sp = (float) (1.0 - (double) t);
        }
        out->x = sp * p->x + sq * q->x;
        out->y = sp * p->y + sq * q->y;
        out->z = sp * p->z + sq * q->z;
        out->w = sp * p->w + sq * q->w;
    } else {
        out->x = -p->y;
        out->y = p->x;
        out->z = -p->w;
        out->w = p->z;

        if (t < 0.5F) {
            sp = quatSin((float) (1.5707963267948966 * (1.0F - (2.0F * t))));
            sq = quatSin((float) (1.5707963267948966 * (2.0F * t)));
            out->x = sp * p->x + sq * q->x;
            out->y = sp * p->y + sq * q->y;
            out->z = sp * p->z + sq * q->z;
            out->w = sp * p->w + sq * q->w;
        } else {
            t -= 0.5F;
            t2 = 2.0F * t;
            sp = quatSin((float) (1.5707963267948966 * (1.0F - t2)));
            sq = quatSin((float) (1.5707963267948966 * t2));
            out->x = sp * p->x + sq * q->x;
            out->y = sp * p->y + sq * q->y;
            out->z = sp * p->z + sq * q->z;
            out->w = sp * p->w + sq * q->w;
        }
    }

    return 1;
}

// Stripped quaternion helper; its shared constants remain in the retail pool.
s32 QuatFromAxisAngle(HSD_Vec3* axis, HSD_Quaternion* q, f32 angle)
{
    f32 len;
    f32 half_angle;
    f32 inv_len;
    f32 s;

    len = hsdSqrt(axis->x * axis->x + axis->y * axis->y + axis->z * axis->z);
    if (__fabsf(len) < 1.1754944E-38F) {
        return -1;
    }
    inv_len = 1.0F / len;
    half_angle = 0.5F * angle;
    q->w = (f32)cos(half_angle);
    s = quatSin(half_angle);
    q->x = s * (inv_len * axis->x);
    q->y = s * (inv_len * axis->y);
    q->z = s * (inv_len * axis->z);

    return 0;
}

#ifdef __cplusplus
}
#endif
