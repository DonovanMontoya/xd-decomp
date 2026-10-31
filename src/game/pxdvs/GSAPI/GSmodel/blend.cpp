
#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
};

struct Quaternion {
    f32 x, y, z, w;
};

struct _HSD_AObj;
typedef _HSD_AObj HSD_AObj;

typedef struct _HSD_JObj HSD_JObj;

struct _HSD_JObj {
    u8 unk0[0x8];
    HSD_JObj* next;
    HSD_JObj* parent;
    HSD_JObj* child;
    u32 flags;
    u8 unk18[0x4];
    Quaternion rotate;
    GSvec scale;
    GSvec translate;
    u8 unk44[0x38];
    HSD_AObj* aobj;
};

#define JOBJ_MTX_DIRTY (1 << 6)
#define JOBJ_INSTANCE (1 << 12)
#define JOBJ_USE_QUATERNION (1 << 17)
#define JOBJ_USER_DEF_MTX (1 << 23)
#define JOBJ_MTX_INDEP_SRT (1 << 25)

struct _HSD_Joint;

struct _HSD_SceneModelSet {
    _HSD_Joint* joint;
};

struct _GSmodel {
    u32 flags;
    _GSmodel* next;
    _HSD_SceneModelSet* set;
    HSD_JObj* jobj;
    HSD_JObj* blendJObj;
    HSD_JObj* blendDest;
    u8 unk18[0xB0];
    struct {
        u8 unk0[0x18];
        HSD_AObj* aobj;
    } partMix[12];
    f32 blendFactor;
};

extern "C" {
void __assert(const char* file, s32 line, const char* expr);
f32 GSmodelGetAnimRate(_GSmodel* model);
void GSmodelSetAnimRate(_GSmodel* model, f32 rate);
void HSD_JObjUnref(HSD_JObj* jobj);
HSD_JObj* HSD_JObjLoadJoint(_HSD_Joint* joint);
void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj);
void HSD_JObjSetFlags(HSD_JObj* jobj, u32 flags);
void HSD_JObjClearFlags(HSD_JObj* jobj, u32 flags);
void HSD_JObjAnim(HSD_JObj* jobj);
void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate);
void EulerToQuat(GSvec* euler, Quaternion* quat);
void QuatSlerp(Quaternion* a, Quaternion* b, Quaternion* out, f32 t);
}

void GSgfxRenderWaitForDrawComplete();
void modelCalculatePartMix(GSvec* value, GSvec* mix, u32 flags);

static void _modelIntpJObjAll(_GSmodel* model, HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, f32 rate);
static void _modelIntpJObj(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t);
void modelIntpJObjRotate(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags);
static void _modelSetRotateEulerToQuatAll(HSD_JObj* jobj);


static inline bool HSD_JObjMtxIsDirty(HSD_JObj* jobj) {
    bool result;
    if (!jobj) {
        __assert("jobj.h", 605, "jobj");
    }
    result = false;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY)) {
        result = true;
    }
    return result;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj* jobj) {
    if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetRotation(HSD_JObj* jobj, Quaternion* quat) {
    if (!jobj) {
        __assert("jobj.h", 656, "jobj");
    }
    jobj->rotate = *quat;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetRotation(HSD_JObj* jobj, Quaternion* quat) {
    if (!jobj) {
        __assert("jobj.h", 733, "jobj");
    }
    *quat = jobj->rotate;
}

static inline void HSD_JObjSetScale(HSD_JObj* jobj, GSvec* scale) {
    if (!jobj) {
        __assert("jobj.h", 790, "jobj");
    }
    jobj->scale = *scale;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetScale(HSD_JObj* jobj, GSvec* scale) {
    if (!jobj) {
        __assert("jobj.h", 849, "jobj");
    }
    *scale = jobj->scale;
}

static inline void HSD_JObjSetTranslate(HSD_JObj* jobj, GSvec* translate) {
    if (!jobj) {
        __assert("jobj.h", 937, "jobj");
    }
    jobj->translate = *translate;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetTranslate(HSD_JObj* jobj, GSvec* translate) {
    if (!jobj) {
        __assert("jobj.h", 996, "jobj");
    }
    *translate = jobj->translate;
}

static inline void _modelIntpScale(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags) {
    f32 s = 1.0f - t;
    GSvec va;
    GSvec vb;
    GSvec scale;

    HSD_JObjGetScale(a, &va);
    HSD_JObjGetScale(b, &vb);
    scale.x = va.x * s + vb.x * t;
    scale.y = va.y * s + vb.y * t;
    scale.z = va.z * s + vb.z * t;
    if (mix != 0) {
        modelCalculatePartMix(&scale, mix, mixFlags);
    }
    HSD_JObjSetScale(dst, &scale);
}

static inline void _modelIntpTrans(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags) {
    f32 s = 1.0f - t;
    GSvec va;
    GSvec vb;
    GSvec translate;

    HSD_JObjGetTranslate(a, &va);
    HSD_JObjGetTranslate(b, &vb);
    translate.x = va.x * s + vb.x * t;
    translate.y = va.y * s + vb.y * t;
    translate.z = va.z * s + vb.z * t;
    if (mix != 0) {
        modelCalculatePartMix(&translate, mix, mixFlags);
    }
    HSD_JObjSetTranslate(dst, &translate);
}

extern "C" {

void GSmodelDisableAnimBlend(_GSmodel* model) {
    f32 rate = GSmodelGetAnimRate(model);
    model->flags &= ~0x80;
    if (model->blendDest != 0) {
        GSmodelSetAnimRate(model, rate);
        GSgfxRenderWaitForDrawComplete();
        HSD_JObjUnref(model->blendJObj);
        HSD_JObjUnref(model->blendDest);
        model->blendJObj = 0;
        model->blendDest = 0;
    }
}

void GSmodelEnableAnimBlend(_GSmodel* model) {
    if (model->blendDest == 0) {
        model->blendJObj = HSD_JObjLoadJoint(model->set->joint);
        model->blendDest = HSD_JObjLoadJoint(model->set->joint);
        _modelSetRotateEulerToQuatAll(model->blendDest);
    }
}

}

void modelCalculateBlendModel(_GSmodel* model, f32 rate) {
    if (model->blendDest != 0) {
        _modelIntpJObjAll(model, model->jobj, model->blendJObj, model->blendDest, model->blendFactor, rate);
        model->flags &= ~0x200;
    }
}

#pragma dont_inline on
static void _modelIntpJObjAll(_GSmodel* model, HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, f32 rate) {
    HSD_AObj* aobj;
    u8 animated;

    if (a == 0 || b == 0 || dst == 0) {
        return;
    }
    aobj = dst->aobj;
    animated = 0;
    if (aobj != 0) {
        for (int i = 0; i < 8; i++) {
            if (model->partMix[i].aobj == aobj) {
                animated = 1;
                break;
            }
        }
    }
    if (animated) {
        HSD_JObjClearFlags(dst, JOBJ_USE_QUATERNION);
        HSD_AObjSetRate(dst->aobj, rate);
        HSD_JObjAnim(dst);
    } else {
        _modelIntpJObj(a, b, dst, t);
    }
    if (!(a->flags & JOBJ_INSTANCE)) {
        HSD_JObj* ca;
        HSD_JObj* cb;
        HSD_JObj* cd;
        for (ca = a->child, cb = b->child, cd = dst->child; ca != 0; ca = ca->next, cb = cb->next, cd = cd->next) {
            _modelIntpJObjAll(model, ca, cb, cd, t, rate);
        }
    }
}

#pragma dont_inline reset

static void _modelIntpJObj(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t) {
    _modelIntpTrans(a, b, dst, t, 0, 0);
    _modelIntpScale(a, b, dst, t, 0, 0);
    modelIntpJObjRotate(a, b, dst, t, 0, 0);
}

void modelIntpJObjRotate(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags) {
    GSvec ea;
    GSvec eb;
    Quaternion result;
    Quaternion qa;
    Quaternion qb;

    HSD_JObjGetRotation(a, &qa);
    HSD_JObjGetRotation(b, &qb);
    ea.x = qa.x;
    ea.y = qa.y;
    ea.z = qa.z;
    eb.x = qb.x;
    eb.y = qb.y;
    eb.z = qb.z;
    if (mix != 0) {
        modelCalculatePartMix(&ea, mix, mixFlags);
        modelCalculatePartMix(&eb, mix, mixFlags);
    }
    EulerToQuat(&ea, &qa);
    EulerToQuat(&eb, &qb);
    if ((qa.x - qb.x) * (qa.x - qb.x) + (qa.y - qb.y) * (qa.y - qb.y) + (qa.z - qb.z) * (qa.z - qb.z) + (qa.w - qb.w) * (qa.w - qb.w) >
        (qa.x + qb.x) * (qa.x + qb.x) + (qa.y + qb.y) * (qa.y + qb.y) + (qa.z + qb.z) * (qa.z + qb.z) + (qa.w + qb.w) * (qa.w + qb.w)) {
        qb.x = -qb.x;
        qb.y = -qb.y;
        qb.z = -qb.z;
        qb.w = -qb.w;
    }
    QuatSlerp(&qa, &qb, &result, t);
    HSD_JObjSetRotation(dst, &result);
}

void modelIntpJObjScale(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags) {
    f32 s = 1.0f - t;
    GSvec va;
    GSvec vb;
    GSvec scale;

    HSD_JObjGetScale(a, &va);
    HSD_JObjGetScale(b, &vb);
    scale.x = va.x * s + vb.x * t;
    scale.y = va.y * s + vb.y * t;
    scale.z = va.z * s + vb.z * t;
    if (mix != 0) {
        modelCalculatePartMix(&scale, mix, mixFlags);
    }
    HSD_JObjSetScale(dst, &scale);
}

void modelIntpJObjTrans(HSD_JObj* a, HSD_JObj* b, HSD_JObj* dst, f32 t, GSvec* mix, u32 mixFlags) {
    f32 s = 1.0f - t;
    GSvec va;
    GSvec vb;
    GSvec translate;

    HSD_JObjGetTranslate(a, &va);
    HSD_JObjGetTranslate(b, &vb);
    translate.x = va.x * s + vb.x * t;
    translate.y = va.y * s + vb.y * t;
    translate.z = va.z * s + vb.z * t;
    if (mix != 0) {
        modelCalculatePartMix(&translate, mix, mixFlags);
    }
    HSD_JObjSetTranslate(dst, &translate);
}

static void _modelSetRotateEulerToQuatAll(HSD_JObj* jobj) {
    HSD_JObj* child;

    if (jobj == 0) {
        return;
    }
    HSD_JObjSetFlags(jobj, JOBJ_USE_QUATERNION);
    if (jobj->flags & JOBJ_INSTANCE) {
        return;
    }
    for (child = jobj->child; child != 0; child = child->next) {
        _modelSetRotateEulerToQuatAll(child);
    }
}
