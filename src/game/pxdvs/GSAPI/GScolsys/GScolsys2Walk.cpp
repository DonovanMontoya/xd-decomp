#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

typedef f32 GSmtx[3][4];

struct CCD_TRI {
    GSvec verts[3];
    GSvec normal;
    u8 surface : 4;
    u8 attr : 4;
    u8 layer : 4;
    u8 subLayer : 4;
    u16 id;
};

struct CCD_GRID_CELL {
    u32 first;
    u32 count;
};

struct CCD_GRID {
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

struct CCD_TRILIST {
    CCD_TRI* tris;
    u32 count;
};

struct CCD_OBJ {
    u8 unk0[0x24];
    void* walk;
    u8 unk28[0x14];
    u16 flags;
    u8 unk3E[2];
};

struct CCD_FILEHEAD {
    CCD_OBJ* objs;
    u32 numObjs;
};

struct GSwalkHit {
    f32 height;
    u16 attrHi;
    u16 attrLo;
    u8 layer;
    u8 subLayer;
};

extern "C" {
void PSMTXMultVec(const GSmtx m, const GSvec* src, GSvec* dst);
CCD_FILEHEAD* GScolsys2GetCCDFileHead(void);
void GScolsys2GetObjEnable(u32 index, bool* enable);
void GScolsys2GetObjMatrix(GSmtx m, u32 index);
void GScolsys2GetObjRotMatrix(GSmtx m, u32 index);
s32 GScolsys2WalkGetHeight(GSvec* pos, GSwalkHit* hits);
}

static bool getCpPolyVec(GSvec* out, GSvec* point, GSvec* vertices, GSvec* plane);

#define COL_ABS(x) ((x) > 0.0f ? (x) : -(x))

static inline f32 colEdgeSide(f32 ez, f32 ex, f32 z, f32 x, f32 pz, f32 px)
{
    ez -= z;
    ex -= x;
    return ex * (pz - z) - ez * (px - x);
}

static inline bool addHit(GSwalkHit* list, s32 count, GSvec* cp, CCD_TRI* tri) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (cp->y == list[i].height) {
            break;
        }
    }
    if (i < count) {
        return false;
    }

    list[count].height = cp->y;
    if (tri->surface == 15) {
        list[count].attrHi = 0xFFFF;
    } else {
        list[count].attrHi = tri->surface;
    }
    if (tri->attr == 15) {
        list[count].attrLo = 0xFFFF;
    } else {
        list[count].attrLo = tri->attr;
    }
    list[count].layer = tri->layer;
    list[count].subLayer = tri->subLayer;
    return true;
}

static inline s32 collectList(GSwalkHit* list, GSvec* point, CCD_TRILIST* tris, GSmtx matrix, GSmtx normalMatrix) {
    GSvec verts[3];
    GSvec normal;
    GSvec cp;
    CCD_TRI* tri;
    u32 j;
    s32 v;
    s32 count;

    count = 0;
    tri = tris->tris;
    for (j = 0; j < tris->count && count < 8; j++, tri++) {
        for (v = 0; v < 3; v++) {
            PSMTXMultVec(matrix, &tri->verts[v], &verts[v]);
        }
        PSMTXMultVec(normalMatrix, &tri->normal, &normal);
        if (getCpPolyVec(&cp, point, verts, &normal) != 0) {
            if (addHit(list, count, &cp, tri)) {
                count++;
            }
        }
    }
    return count;
}

static inline s32 collectGrid(GSwalkHit* list, GSvec* point, CCD_GRID* grid) {
    GSvec cp;
    CCD_TRI* tri;
    CCD_GRID_CELL* cell;
    u32* index;
    u32 j;
    s32 z;
    s32 x;
    s32 count;

    count = 0;
    x = (point->x - grid->minX) / grid->cellWidth;
    if (x < 0 || x >= grid->cellsX) {
        return 0;
    }
    z = (point->z - grid->minZ) / grid->cellDepth;
    if (z < 0 || z >= grid->cellsZ) {
        return 0;
    }

    cell = grid->cells;
    index = grid->indices;
    cell += x + z * grid->cellsX;
    index += cell->first;
    for (j = 0; j < cell->count && count < 8; j++, index++) {
        tri = grid->tris;
        tri += *index;
        if (getCpPolyVec(&cp, point, tri->verts, &tri->normal) != 0) {
            if (addHit(list, count, &cp, tri)) {
                count++;
            }
        }
    }
    return count;
}

extern "C" {
BOOL GScolsys2WalkGetLayer(GSvec* pos, u8* layer, u8* subLayer) {
    GSwalkHit hits[8];
    s32 count;
    s32 i;
    s32 closest;
    f32 distance;
    f32 closestDistance;

    count = GScolsys2WalkGetHeight(pos, hits);
    if (count <= 0) {
        return FALSE;
    }

    closestDistance = COL_ABS(pos->y - hits[0].height);
    closest = 0;
    for (i = 1; i < count; i++) {
        distance = COL_ABS(pos->y - hits[i].height);
        if (closestDistance > distance) {
            closest = i;
            closestDistance = distance;
        }
    }

    *layer = hits[closest].layer;
    *subLayer = hits[closest].subLayer;
    return TRUE;
}
}

static bool getCpPolyVec(GSvec* out, GSvec* point, GSvec* vertices, GSvec* plane) {
    f32 minZ;
    f32 minX;
    f32 maxZ;
    f32 maxX;
    f32 height;
    s32 i;
    s32 next;

    minX = minZ = 1000000.0f;
    maxX = maxZ = -1000000.0f;
    for (i = 0; i < 3; i++) {
        f32 x;
        f32 z;

        x = vertices[i].x;
        if (minX > x) {
            minX = x;
        }
        z = vertices[i].z;
        if (minZ > z) {
            minZ = z;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxZ < z) {
            maxZ = z;
        }
    }
    if (minX > point->x || minZ > point->z || maxX < point->x || maxZ < point->z) {
        return false;
    }

    for (i = 0; i < 3; i++) {
        f32 x;
        f32 z;

        next = i + 1;
        if (next >= 3) {
            next = 0;
        }
        x = vertices[i].x;
        z = vertices[i].z;
        if (colEdgeSide(vertices[next].z, vertices[next].x, z, x, point->z, point->x) > 0.0f) {
            return false;
        }
    }

    if (0.0f == plane->y) {
        return false;
    }
    height = -(plane->x * (point->x - vertices[0].x) + plane->y * (point->y - vertices[0].y) +
               plane->z * (point->z - vertices[0].z)) /
             plane->y;
    out->x = point->x;
    out->y = point->y + height;
    out->z = point->z;
    return true;
}

extern "C" {
s32 GScolsys2WalkGetHeight(GSvec* pos, GSwalkHit* outHits) {
    GSwalkHit temp[8];
    GSmtx matrix;
    GSmtx normalMatrix;
    CCD_FILEHEAD* head;
    CCD_OBJ* obj;
    void* walk;
    u32 i;
    s32 total;
    bool enable;
    s32 k;
    s32 count;
    CCD_TRILIST* list;

    total = 0;
    head = GScolsys2GetCCDFileHead();
    if (head == 0) {
        return 0;
    }

    obj = head->objs;
    for (i = 0; i < head->numObjs && total < 8; i++, obj++) {
        GScolsys2GetObjEnable(i, &enable);
        if (!enable) {
            continue;
        }
        walk = obj->walk;
        if (walk == 0) {
            continue;
        }

        if (obj->flags & 1) {
            GScolsys2GetObjMatrix(matrix, i);
            GScolsys2GetObjRotMatrix(normalMatrix, i);
            list = (CCD_TRILIST*) walk;
            count = collectList(temp, pos, list, matrix, normalMatrix);
        } else {
            count = collectGrid(temp, pos, (CCD_GRID*) walk);
        }

        for (k = 0; k < count && total < 8; k++, total++) {
            outHits[total] = temp[k];
        }
    }

    return total;
}
}
