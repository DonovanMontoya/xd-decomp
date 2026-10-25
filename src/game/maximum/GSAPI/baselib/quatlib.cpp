#include "game/maximum/GSAPI/baselib/quatlib.h"
#ifdef __cplusplus
extern "C" {
#endif
double sin(double);
double cos(double);
double acos(double);
static inline float sinf(float x) { return (float)sin(x); }
static inline float acosf(float x) { return (float)acos(x); }
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
            theta = acosf(cosom);
            sinom = sinf(theta);
            sp = sinf((1.0F - t) * theta) / sinom;
            sq = sinf(t * theta) / sinom;
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
            sp = sinf((float) (1.5707963267948966 * (1.0F - (2.0F * t))));
            sq = sinf((float) (1.5707963267948966 * (2.0F * t)));
            out->x = sp * p->x + sq * q->x;
            out->y = sp * p->y + sq * q->y;
            out->z = sp * p->z + sq * q->z;
            out->w = sp * p->w + sq * q->w;
        } else {
            t -= 0.5F;
            t2 = 2.0F * t;
            sp = sinf((float) (1.5707963267948966 * (1.0F - t2)));
            sq = sinf((float) (1.5707963267948966 * t2));
            out->x = sp * p->x + sq * q->x;
            out->y = sp * p->y + sq * q->y;
            out->z = sp * p->z + sq * q->z;
            out->w = sp * p->w + sq * q->w;
        }
    }

    return 1;
}
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
    sx = sinf(0.5F * euler->x);
    sy = sinf(0.5F * euler->y);
    sz = sinf(0.5F * euler->z);

    ss = sy * sz;
    cc = cy * cz;
    q->w = cx * cc + sx * ss;
    q->x = sx * cc - cx * ss;
    q->y = cz * (cx * sy) + sz * (sx * cy);
    q->z = sz * (cx * cy) - cz * (sx * sy);

    return 1;
}


#ifdef __cplusplus
}
#endif
