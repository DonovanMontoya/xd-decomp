#ifndef HSD_ANIMATION_OBJECTS_H
#define HSD_ANIMATION_OBJECTS_H
#include "game/maximum/GSAPI/baselib/quatlib.h"
#include "game/maximum/GSAPI/baselib/animation.h"
typedef struct HSD_SList { struct HSD_SList* next; void* data; } HSD_SList;
typedef struct HSD_Obj { void* class_info; unsigned short ref_count, ref_count_individual; } HSD_Obj;
typedef struct HSD_JObj HSD_JObj;
typedef struct HSD_DObj HSD_DObj;
typedef struct HSD_MObj HSD_MObj;
typedef struct HSD_PObj HSD_PObj;
typedef struct HSD_TObj HSD_TObj;
typedef struct HSD_RObj HSD_RObj;
typedef struct HSD_WObj HSD_WObj;
typedef struct HSD_CObj HSD_CObj;
typedef struct HSD_LObj HSD_LObj;
typedef struct HSD_Fog HSD_Fog;
typedef struct HSD_Joint HSD_Joint;
typedef struct HSD_RObjAnimJoint HSD_RObjAnimJoint;
typedef struct HSD_ShapeSet HSD_ShapeSet;
typedef unsigned int HSD_IDKey;
typedef void (*Event)(void);

/* Layouts used by animation traversal. Opaque members preserve fields whose
 * detailed descriptors are reconstructed with their owning modules. */
struct HSD_Fog { HSD_Obj parent; unsigned int type; void* fog_adj; float start, end; unsigned int color; HSD_AObj* aobj; };
struct HSD_RObj { HSD_RObj* next; unsigned int flags; unsigned char expression[16]; HSD_AObj* aobj; };
struct HSD_WObj { HSD_Obj parent; unsigned int flags; HSD_Vec3 pos; HSD_AObj* aobj; HSD_RObj* robj; };
struct HSD_CObj {
    HSD_Obj parent; unsigned int flags; float viewport[4]; unsigned short scissor[4];
    HSD_WObj *eyepos, *interest;
    union { float roll; HSD_Vec3 up; } u;
    float near, far, projection_param[4]; unsigned char projection_type;
    float view_mtx[3][4]; HSD_AObj* aobj; void* proj_mtx;
};
struct HSD_LObj {
    HSD_Obj parent; unsigned short flags, priority; HSD_LObj* next;
    unsigned int color, hw_color; HSD_WObj *position, *interest;
    float attenuation[6], shininess; HSD_Vec3 lvec; HSD_AObj* aobj;
};
struct HSD_TObj {
    HSD_Obj parent; HSD_TObj* next; int id, src; unsigned int mtxid;
    HSD_Quaternion rotate; HSD_Vec3 scale, translate; int wrap_s, wrap_t;
    unsigned char repeat_s, repeat_t; unsigned int flags; float blending;
    int magFilt; void *imagedesc, *tlut, *lod; HSD_AObj* aobj;
};
struct HSD_ShapeSet {
    unsigned short flags, nb_shape; int nb_vertex_index; void* vertex_desc;
    unsigned char** vertex_idx_list; int nb_normal_index; void* normal_desc;
    unsigned char** normal_idx_list; union { float* bp; float bl; } blend;
    HSD_AObj* aobj;
};
struct HSD_PObj {
    void* class_info; HSD_PObj* next; void* verts;
    unsigned short flags, n_display; unsigned char* display;
    union { HSD_JObj* jobj; HSD_ShapeSet* shape_set; HSD_SList* envelope_list; } u;
    HSD_AObj* aobj;
};
struct HSD_MObj { void* class_info; unsigned int rendermode; HSD_TObj* tobj; void *mat, *pe; HSD_AObj* aobj; void *tevdesc, *texp; };
struct HSD_DObj { void* class_info; HSD_DObj* next; HSD_MObj* mobj; HSD_PObj* pobj; HSD_AObj* aobj; unsigned int flags; };
struct HSD_JObj {
    HSD_Obj object; HSD_JObj *next, *parent, *child; unsigned int flags;
    union { HSD_SList* ptcl; HSD_DObj* dobj; void* spline; } u;
    HSD_Quaternion rotate; HSD_Vec3 scale, translate; float mtx[3][4];
    HSD_Vec3* scl; void* envelopemtx; HSD_AObj* aobj; HSD_RObj* robj; HSD_IDKey id;
};
#define JOBJ_PTCL (1 << 5)
#define JOBJ_INSTANCE (1 << 12)
#define JOBJ_SPLINE (1 << 14)
#define union_type_dobj(o) ((o)->flags & (JOBJ_PTCL | JOBJ_SPLINE) ? 0 : 1)
#define POBJ_SHAPEANIM (1 << 12)
#define pobj_type(p) ((p)->flags & 0x3000)
#endif
