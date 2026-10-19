#include <game/pxdvs/GSAPI/GSparticle/peSplinePrivate.hpp>
#include <dolphin/os/OSFastCast.h>

static inline f32 byteToFloat(u8 value) { return __OSu8tof32(&value); }
static inline void lerpColor(PeColor *destination, PeColor *start, PeColor *end, f32 weight) {
    f32 fsr = byteToFloat(start->r);
    f32 fsg = byteToFloat(start->g);
    f32 fsb = byteToFloat(start->b);
    f32 fer = byteToFloat(end->r);
    f32 feg = byteToFloat(end->g);
    f32 feb = byteToFloat(end->b);
    destination->r = __OSf32tou8(weight * (fer - fsr) + fsr);
    destination->g = __OSf32tou8(weight * (feg - fsg) + fsg);
    destination->b = __OSf32tou8(weight * (feb - fsb) + fsb);
}
static inline void copyColor(PeColor *destination, const PeColor *source) {
    destination->r = source->r;
    destination->g = source->g;
    destination->b = source->b;
}
extern "C" void peColorSplineGetValue(PeColor *result, PeColorSpline *spline, f32 time) {
    u8 count = spline->count;
    u8 interval;
    if (count < 2) return;
    PeColor *points = spline->points;
    if (time <= 0.0f) { copyColor(result, points); return; }
    if (time >= 1.0f) { points += (s32)count - 1; copyColor(result, points); return; }
    f32 difference = spline->time - time;
    if (difference < 0.0f) difference = -difference;
    if (difference <= 0.00001f) { copyColor(result, &spline->value); return; }
    spline->time = time;
    if (count == 2) {
        lerpColor(&spline->value, &points[0], &points[1], time);
        copyColor(result, &spline->value);
        return;
    } else {
        interval = spline->interval;
        f32 *times = (f32 *)(points + count);
        f32 *scales = times + count;
        if (time < times[interval]) {
            interval = 0;
            spline->interval = 0;
        }
        while (times[interval + 1] < time) {
            interval++;
            spline->interval = interval;
            if (interval >= count) return;
        }
        f32 weight = (time - times[interval]) * scales[interval];
        points += interval;
        lerpColor(&spline->value, &points[0], &points[1], weight);
    }
    copyColor(result, &spline->value);
}

extern "C" f32 peSplineGetValue(PeSpline *spline, f32 time) {
    s32 type = spline->flags & 3;
    if (type == 0) return 1.0f;
    u8 last = spline->count - 1;
    if (last < 1) return 1.0f;
    u8 interval;
    f32 *points = spline->points;
    if (time <= 0.0f) return points[0];
    if (time >= 1.0f) return points[last];
    spline->time = time;
    if (last == 1) {
        switch (type) {
        case 1:
        case 3: spline->value = points[4] * time + points[0]; break;
        case 2: spline->value = points[1]; break;
        }
        return spline->value;
    }
    interval = 0;
    f32 *duration = points + (last + 1);
    f32 length;
    while ((length = *duration) < time) {
        interval++;
        time -= length;
        duration++;
        if (interval >= last) return 1.0f;
    }
    {
        f32 *inverse = duration + last;
        f32 *point = points + interval;
        f32 *tangent = inverse + last;
        time *= *inverse;
        switch (type) {
        case 3: {
            f32 t3;
            f32 t2 = time * time;
            t3 = t2 * time;
            f32 h11 = t3 - t2;
            f32 q = (t2 + t2) - t3;
            f32 h10 = time + (h11 - t2);
            f32 h01 = q - h11;
            f32 h00 = 1.0f - h01;
            f32 minimum;
            if (spline->flags & 4) minimum = -1.0f;
            else minimum = 0.0f;
            f32 value = length * (h10 * *tangent + h11 * tangent[last])
                + (h01 * point[1] + h00 * point[0]);
            if (value < minimum) value = minimum;
            else if (value > 1.0f) value = 1.0f;
            spline->value = value;
            break;
        }
        case 1: spline->value = *tangent * time + point[0]; break;
        case 2: spline->value = point[1]; break;
        }
        return spline->value;
    }
}
