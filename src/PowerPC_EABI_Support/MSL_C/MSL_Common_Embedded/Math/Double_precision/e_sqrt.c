extern int errno;
extern float __float_nan[];

#ifndef EDOM
#define EDOM 33
#endif

typedef union {
    double d;
    struct {
        unsigned int msw;
        unsigned int lsw;
    } words;
} ieee_double_shape_type;

double __ieee754_sqrt(double x)
{
    unsigned int* px = (unsigned int*)&x;
    ieee_double_shape_type result;
    int ix0, s0, m, t, i, q;
    unsigned int ix1, s1, r, q1;
    int sign;
    volatile double z;
    static const double one = 1.0;

    ix0 = (int)px[0];
    ix1 = px[1];

    sign = (int)0x80000000;

    if ((ix0 & 0x7ff00000) == 0x7ff00000) {
        errno = EDOM;
        return x * x + x;
    }

    if (ix0 <= 0) {
        if (((ix0 & ~sign) | ix1) == 0) {
            return x;
        }
        if (ix0 < 0) {
            errno = EDOM;
            return __float_nan[0];
        }
    }

    m = ix0 >> 20;
    if (m == 0) {
        while (ix0 == 0) {
            m -= 21;
            ix0 |= ix1 >> 11;
            ix1 <<= 21;
        }
        for (i = 0; (ix0 & 0x00100000) == 0; i++) {
            ix0 <<= 1;
        }
        m -= i - 1;
        ix0 |= ix1 >> (32 - i);
        ix1 <<= i;
    }

    m -= 1023;
    ix0 = (ix0 & 0x000fffff) | 0x00100000;
    if (m & 1) {
        ix0 += ix0 + (ix1 >> 31);
        ix1 += ix1;
    }
    m >>= 1;

    ix0 += ix0 + (ix1 >> 31);
    ix1 += ix1;

    q = 0;
    q1 = 0;
    s0 = 0;
    s1 = 0;
    r = 0x00200000;

    while (r != 0) {
        t = s0 + r;
        if (t <= ix0) {
            s0 = t + r;
            ix0 -= t;
            q += r;
        }
        ix0 += ix0 + (ix1 >> 31);
        ix1 += ix1;
        r >>= 1;
    }

    r = sign;
    while (r != 0) {
        t = s1 + r;
        if ((s0 < ix0) || ((s0 == ix0) && (t <= ix1))) {
            s1 = t + r;
            if ((t & sign) == sign && (s1 & sign) == 0) {
                s0 += 1;
            }
            if (ix1 < t) {
                ix0 -= 1;
            }
            ix1 -= t;
            q1 += r;
        }
        ix0 += ix0 + (ix1 >> 31);
        ix1 += ix1;
        r >>= 1;
    }

    if ((ix0 | ix1) != 0) {
        register double w = one;

        z = w;
        z = w;
        if (q1 == 0xffffffff) {
            q1 = 0;
            q += 1;
        } else {
            q1 += q1 & 1;
        }
    }

    ix0 = (q >> 1) + 0x3fe00000;
    ix1 = q1 >> 1;
    if ((q & 1) == 1) {
        ix1 |= sign;
    }
    ix0 += m << 20;

    result.words.msw = (unsigned int)ix0;
    result.words.lsw = ix1;
    return result.d;
}
