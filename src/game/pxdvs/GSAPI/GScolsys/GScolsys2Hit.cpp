#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

struct GSmtx {
    f32 m[3][4];
};

struct CCD_TRI {
    GSvec verts[3];
    GSvec normal;
    u16 flags;
    u8 pad32[2];
};

struct CCD_GRID_CELL {
    u32 first;
    u32 count;
};

struct CCD_HITMDL_HEAD {
    CCD_TRI* tris;
    u32 numTris;
    CCD_GRID_CELL* cells;
    u32* indices;
    u16 cellsX;
    u16 cellsZ;
    f32 cellWidth;
    f32 cellDepth;
    f32 minX;
    f32 minZ;
};

struct CCD_OBJ {
    u8 unk0[0x28];
    CCD_HITMDL_HEAD* hit;
    u8 unk2C[8];
    CCD_HITMDL_HEAD* hitAlt;
    u8 unk38[4];
    u16 flags;
    u8 pad3E[2];
};

struct CCD_FILEHEAD {
    CCD_OBJ* objs;
    u32 numObjs;
};

extern "C" {
void PSMTXMultVec(const GSmtx* m, const GSvec* src, GSvec* dst);
f32 PSVECSquareDistance(const GSvec* a, const GSvec* b);
f32 PSVECDistance(const GSvec* a, const GSvec* b);
void PSVECSubtract(const GSvec* a, const GSvec* b, GSvec* ab);
void PSVECScale(const GSvec* src, GSvec* dst, f32 scale);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
CCD_FILEHEAD* GScolsys2GetCCDFileHead(void);
void GScolsys2GetObjEnable(u32 index, bool* enable);
void GScolsys2GetObjMatrix(GSmtx* m, u32 index);
void GScolsys2GetObjRotMatrix(GSmtx* m, u32 index);
f32 GScolsy2UtilGetSidePlanePoint(GSvec* normal, GSvec* verts, GSvec* point);
void GScolsy2UtilGetCpPlanePoint(GSvec* out, GSvec* normal, GSvec* verts, GSvec* point);
bool GScolsy2UtilChkInTri(GSvec* point, GSvec* verts, GSvec* normal);
f32 GScolsys2UtilGetCpLinePoint(GSvec* out, GSvec* start, GSvec* end, GSvec* point);
void GScolsy2UtilGetPointExtentionLine(GSvec* out, GSvec* start, GSvec* end, f32 length);
}

static inline bool chkFace(GSvec* verts, GSvec* normal, GSvec* pos, f32 radiusSq, GSvec* hit) {
    GSvec cp;

    if (GScolsy2UtilGetSidePlanePoint(normal, verts, pos) < 0.0f) {
        return false;
    }
    GScolsy2UtilGetCpPlanePoint(&cp, normal, verts, pos);
    if (PSVECSquareDistance(&cp, pos) >= radiusSq) {
        return false;
    }
    if (GScolsy2UtilChkInTri(&cp, verts, normal) == 0) {
        return false;
    }
    *hit = cp;
    return true;
}

static inline bool chkEdges(GSvec* verts, GSvec* normal, GSvec* pos, f32 radiusSq, GSvec* hit, u16 flags) {
    u16 masks[3] = {1, 2, 4};
    GSvec cp;
    s32 i;
    s32 next;
    f32 t;

    if (GScolsy2UtilGetSidePlanePoint(normal, verts, pos) < 0.0f) {
        return false;
    }
    for (i = 0; i < 3; i++) {
        if (flags & masks[i]) {
            next = i + 1;
            if (next >= 3) {
                next = 0;
            }
            t = GScolsys2UtilGetCpLinePoint(&cp, &verts[i], &verts[next], pos);
            if (t < 0.0f || t > 1.0f) {
                continue;
            }
            if (PSVECSquareDistance(&cp, pos) < radiusSq) {
                *hit = cp;
                return true;
            }
        }
    }
    return false;
}

static inline bool chkVerts(GSvec* verts, GSvec* normal, GSvec* pos, f32 radiusSq, GSvec* hit, u16 flags) {
    u16 masks[3] = {1, 2, 4};
    s32 i;
    s32 prev;

    if (GScolsy2UtilGetSidePlanePoint(normal, verts, pos) < 0.0f) {
        return false;
    }
    for (i = 0; i < 3; i++) {
        prev = i + 2;
        if (prev >= 3) {
            prev -= 3;
        }
        if ((flags & masks[i]) && (flags & masks[prev])) {
            if (PSVECSquareDistance(&verts[i], pos) < radiusSq) {
                *hit = verts[i];
                return true;
            }
        }
    }
    return false;
}

static f32 unusedClampT(f32 t) {
    if (t < 0.0f) {
        return 0.0f;
    }
    if (t > 1.0f) {
        return 1.0f;
    }
    return t;
}

static bool checkHitFixedMdl(GSvec* pos, f32 radius, CCD_HITMDL_HEAD* head, GSvec* hitOut) {
    GSvec hit;
    CCD_GRID_CELL* cell;
    u32* index;
    CCD_TRI* tri;
    f32 radiusSq;
    GSvec min;
    GSvec max;
    s32 x0;
    s32 z0;
    s32 x1;
    s32 z1;
    u32 k;
    s32 x;
    s32 z;
    bool found;

    min.x = pos->x - radius;
    min.z = pos->z - radius;
    max.x = pos->x + radius;
    max.z = pos->z + radius;
    x0 = (min.x - head->minX) / head->cellWidth;
    if (x0 < 0) {
        x0 = 0;
    }
    z0 = (min.z - head->minZ) / head->cellDepth;
    if (z0 < 0) {
        z0 = 0;
    }
    x1 = (max.x - head->minX) / head->cellWidth;
    if (x1 > head->cellsX - 1) {
        x1 = head->cellsX - 1;
    }
    z1 = (max.z - head->minZ) / head->cellDepth;
    if (z1 > head->cellsZ - 1) {
        z1 = head->cellsZ - 1;
    }
    radiusSq = radius * radius;

    found = false;
    for (z = z0; z <= z1 && !found; z++) {
        cell = head->cells;
        cell += z * head->cellsX + x0;
        for (x = x0; x <= x1 && !found; x++, cell++) {
            index = head->indices;
            index += cell->first;
            for (k = 0; k < cell->count && !found; k++, index++) {
                tri = head->tris;
                tri += *index;
                found = chkFace(tri->verts, &tri->normal, pos, radiusSq, &hit);
            }
        }
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }

    found = false;
    for (z = z0; z <= z1 && !found; z++) {
        cell = head->cells;
        cell += z * head->cellsX + x0;
        for (x = x0; x <= x1 && !found; x++, cell++) {
            index = head->indices;
            index += cell->first;
            for (k = 0; k < cell->count && !found; k++, index++) {
                tri = head->tris;
                tri += *index;
                if (!(tri->flags & 7)) {
                    continue;
                }
                found = chkEdges(tri->verts, &tri->normal, pos, radiusSq, &hit, tri->flags);
            }
        }
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }

    found = false;
    for (z = z0; z <= z1 && !found; z++) {
        cell = head->cells;
        cell += z * head->cellsX + x0;
        for (x = x0; x <= x1 && !found; x++, cell++) {
            index = head->indices;
            index += cell->first;
            for (k = 0; k < cell->count && !found; k++, index++) {
                tri = head->tris;
                tri += *index;
                if (!(tri->flags & 7)) {
                    continue;
                }
                found = chkVerts(tri->verts, &tri->normal, pos, radiusSq, &hit, tri->flags);
            }
        }
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }
    return false;
}

static bool checkHitMdl(GSvec* pos, f32 radius, CCD_HITMDL_HEAD* head, GSmtx* mtx, GSmtx* rot, GSvec* hitOut) {
    GSvec verts[3];
    GSvec normal;
    GSvec hit;
    CCD_TRI* tri;
    f32 radiusSq;
    u32 i;
    s32 j;
    bool found;

    radiusSq = radius * radius;
    tri = head->tris;
    for (i = 0, found = false; i < head->numTris && !found; i++, tri++) {
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->verts[j], &verts[j]);
        }
        PSMTXMultVec(rot, &tri->normal, &normal);
        found = chkFace(verts, &normal, pos, radiusSq, &hit);
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }

    tri = head->tris;
    for (i = 0, found = false; i < head->numTris && !found; i++, tri++) {
        if (!(tri->flags & 7)) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->verts[j], &verts[j]);
        }
        PSMTXMultVec(rot, &tri->normal, &normal);
        found = chkEdges(verts, &normal, pos, radiusSq, &hit, tri->flags);
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }

    tri = head->tris;
    for (i = 0, found = false; i < head->numTris && !found; i++, tri++) {
        if (!(tri->flags & 7)) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            PSMTXMultVec(mtx, &tri->verts[j], &verts[j]);
        }
        PSMTXMultVec(rot, &tri->normal, &normal);
        found = chkVerts(verts, &normal, pos, radiusSq, &hit, tri->flags);
    }
    if (found) {
        if (hitOut == 0) {
            return true;
        }
        GScolsy2UtilGetPointExtentionLine(hitOut, &hit, pos, 0.0001f + radius);
        return true;
    }
    return false;
}

static bool checkHitCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hitOut, bool alt) {
    CCD_OBJ* obj;
    CCD_FILEHEAD* head;
    CCD_HITMDL_HEAD* group;
    s32 iter;
    s32 hitCount;
    u32 i;
    GSvec* tmpPtr;
    GSvec cur;
    GSvec tmp;
    GSmtx mtx;
    GSmtx rotMtx;
    bool enable;
    bool result;

    cur = *end;
    head = GScolsys2GetCCDFileHead();
    if (hitOut == 0) {
        tmpPtr = 0;
    } else {
        tmpPtr = &tmp;
    }

    for (iter = 0; iter < 10; iter++) {
        obj = head->objs;
        hitCount = 0;
        for (i = 0; i < head->numObjs; i++, obj++) {
            GScolsys2GetObjEnable(i, &enable);
            if (!enable) {
                continue;
            }
            if (alt) {
                group = obj->hitAlt;
                if (group == 0) {
                    continue;
                }
            } else {
                group = obj->hit;
                if (group == 0) {
                    continue;
                }
            }
            if (obj->flags & 1) {
                GScolsys2GetObjMatrix(&mtx, i);
                GScolsys2GetObjRotMatrix(&rotMtx, i);
                result = checkHitMdl(&cur, radius, group, &mtx, &rotMtx, tmpPtr);
            } else {
                result = checkHitFixedMdl(&cur, radius, group, tmpPtr);
            }
            if (result) {
                if (hitOut == 0) {
                    return true;
                }
                hitCount++;
                if (tmpPtr != 0) {
                    cur = *tmpPtr;
                }
            }
        }
        if (hitCount <= 0) {
            break;
        }
    }

    if (iter <= 0) {
        return false;
    }
    *hitOut = cur;
    return true;
}

extern "C" {
bool GScolsys2HitNpcCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hitOut) {
    GSvec p2;
    GSvec p1;
    GSvec dir;
    f32 step;
    f32 dist;
    f32 t2;
    f32 t;

    if (GScolsys2GetCCDFileHead() == 0) {
        return false;
    }
    dist = PSVECDistance(start, end);
    step = 0.0f;
    if (dist > step) {
        step = radius / dist;
        if (step > 1.0f) {
            step = 1.0f;
        }
    }
    PSVECSubtract(end, start, &dir);
    for (t = 0.0f; t < 1.0f; t += step) {
        t2 = t + step;
        if (t2 > 1.0f) {
            t2 = 1.0f;
        }
        PSVECScale(&dir, &p1, t);
        PSVECAdd(&p1, start, &p1);
        PSVECScale(&dir, &p2, t2);
        PSVECAdd(&p2, start, &p2);
        if (checkHitCollision(&p1, &p2, radius, hitOut, true)) {
            return true;
        }
        if (step <= 0.0f) {
            break;
        }
    }
    return false;
}

bool GScolsys2HitCollision(GSvec* start, GSvec* end, f32 radius, GSvec* hitOut) {
    GSvec p2;
    GSvec p1;
    GSvec dir;
    f32 step;
    f32 dist;
    f32 t2;
    f32 t;

    if (GScolsys2GetCCDFileHead() == 0) {
        return false;
    }
    dist = PSVECDistance(start, end);
    step = 0.0f;
    if (dist > step) {
        step = radius / dist;
        if (step > 1.0f) {
            step = 1.0f;
        }
    }
    PSVECSubtract(end, start, &dir);
    for (t = 0.0f; t < 1.0f; t += step) {
        t2 = t + step;
        if (t2 > 1.0f) {
            t2 = 1.0f;
        }
        PSVECScale(&dir, &p1, t);
        PSVECAdd(&p1, start, &p1);
        PSVECScale(&dir, &p2, t2);
        PSVECAdd(&p2, start, &p2);
        if (checkHitCollision(&p1, &p2, radius, hitOut, false)) {
            return true;
        }
        if (step <= 0.0f) {
            break;
        }
    }
    return false;
}
}
