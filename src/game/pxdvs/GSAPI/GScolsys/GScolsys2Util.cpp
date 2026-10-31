#include <dolphin/mtx.h>
static inline f32 colEdgeSide(f32 ez, f32 ex, f32 z, f32 x, f32 pz, f32 px)
{
    ez -= z;
    ex -= x;
    return ex * (pz - z) - ez * (px - x);
}
#define COL_ABS(x) ((x) > 0.0f ? (x) : -(x))
extern "C" {
u8 GScolsys2UtilGetCpPlaneLine(Vec *out, f32 *rate, Vec *normal, Vec *plane, Vec *start, Vec *end) {
    Vec delta;
    PSVECSubtract(end, start, &delta);
    f32 ny = normal->y;
    f32 nx = normal->x;
    f32 nz = normal->z;
    f32 dot;
    if (0.0f == (dot = nz * delta.z + (nx * delta.x + ny * delta.y))) return 0;
    f32 t = (normal->z * (plane->z - start->z) + (normal->x * (plane->x - start->x) + normal->y * (plane->y - start->y))) / dot;
    PSVECScale(&delta, &delta, t);
    PSVECAdd(&delta, start, out);
    *rate = t;
    return 1;
}
f32 GScolsys2UtilGetCpLinePoint(Vec *out, Vec *start, Vec *end, Vec *point) {
    Vec delta;
    PSVECSubtract(end, start, &delta);
    f32 dot = delta.z * delta.z + (delta.x * delta.x + delta.y * delta.y);
    if (dot == 0.0f) { *out = *start; return 0.0f; }
    f32 t = (delta.z * (point->z - start->z) + (delta.x * (point->x - start->x) + delta.y * (point->y - start->y))) / dot;
    PSVECScale(&delta, &delta, t);
    PSVECAdd(&delta, start, out);
    return t;
}
void GScolsy2UtilGetPointExtentionLine(Vec *out, Vec *start, Vec *end, f32 distance) {
    Vec delta;
    PSVECSubtract(end, start, &delta);
    f32 length = PSVECMag(&delta);
    if (length != 0.0f) {
        PSVECScale(&delta, &delta, distance / length);
        PSVECAdd(&delta, start, out);
    }
}
BOOL GScolsy2UtilChkInTri(Vec* point, Vec* verts, Vec* normal)
{
    Vec pts[3];
    f32 absX;
    f32 absY;
    f32 absZ;
    f32 facing;
    s32 u;
    s32 v;
    f32 minY;
    f32 minX;
    f32 maxY;
    f32 maxX;
    f32 px;
    f32 py;
    s32 i;
    s32 next;

    absX = COL_ABS(normal->x);
    absY = COL_ABS(normal->y);
    absZ = COL_ABS(normal->z);
    if (absX < absY) {
        if (absY < absZ) {
            facing = normal->z;
            u = 0;
            v = 1;
        } else {
            facing = normal->y;
            u = 2;
            v = 0;
        }
    } else if (absX > absZ) {
        facing = -normal->x;
        u = 2;
        v = 1;
    } else {
        facing = normal->z;
        u = 0;
        v = 1;
    }

    if (facing < 0.0f) {
        for (i = 0; i < 3; i++) {
            pts[i].x = (&verts[i].x)[u];
            pts[i].y = (&verts[i].x)[v];
        }
    } else {
        for (i = 0; i < 3; i++) {
            pts[i].x = (&verts[2 - i].x)[u];
            pts[i].y = (&verts[2 - i].x)[v];
        }
    }

    minX = minY = 1000000.0f;
    maxX = maxY = -1000000.0f;
    px = (&point->x)[u];
    py = (&point->x)[v];
    for (i = 0; i < 3; i++) {
        f32 x;
        f32 y;

        x = pts[i].x;
        if (minX > x) {
            minX = x;
        }
        y = pts[i].y;
        if (minY > y) {
            minY = y;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxY < y) {
            maxY = y;
        }
    }
    if (minX > px || minY > py || maxX < px || maxY < py) {
        return 0;
    }

    for (i = 0; i < 3; i++) {
        f32 x;
        f32 y;

        next = i + 1;
        if (next >= 3) {
            next = 0;
        }
        x = pts[i].x;
        y = pts[i].y;
        if (colEdgeSide(pts[next].y, pts[next].x, y, x, py, px) > 0.0f) {
            return 0;
        }
    }
    return 1;
}
void GScolsy2UtilGetCpPlanePoint(Vec *out, Vec *normal, Vec *plane, Vec *point) {
    f32 t = (normal->z*(plane->z-point->z) + (normal->x*(plane->x-point->x)+normal->y*(plane->y-point->y))) / (normal->z*normal->z+(normal->x*normal->x+normal->y*normal->y));
    PSVECScale(normal, out, t);
    PSVECAdd(out, point, out);
}
}
