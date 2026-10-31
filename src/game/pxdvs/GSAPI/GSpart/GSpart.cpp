
#include <dolphin/types.h>

#pragma pool_strings off

struct GSvec {
    f32 x, y, z;
};

struct Quaternion {
    f32 x, y, z, w;
};

typedef f32 Mtx[3][4];

struct _HSD_AObj {
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;
};
typedef _HSD_AObj HSD_AObj;

struct _HSD_AObjDesc {
    u32 flags;
    f32 end_frame;
};

struct _HSD_AnimJoint {
    _HSD_AnimJoint* child;
    _HSD_AnimJoint* next;
    _HSD_AObjDesc* aobjdesc;
};

struct _HSD_MatAnimJoint {
    _HSD_MatAnimJoint* child;
    _HSD_MatAnimJoint* next;
    void* matanim;
};

struct _HSD_ShapeAnimJoint {
    _HSD_ShapeAnimJoint* child;
    _HSD_ShapeAnimJoint* next;
};

struct _HSD_MObj;
struct _HSD_TObj;

struct _HSD_MatAnim {
    _HSD_MatAnim* next;
    void* aobjdesc;
    void* texanim;
};

struct _HSD_DObj {
    u8 unk0[4];
    _HSD_DObj* next;
    _HSD_MObj* mobj;
};

struct _HSD_MObj {
    u8 unk0[8];
    _HSD_TObj* tobj;
};

struct _HSD_TObj {
    u8 unk0[0x64];
    HSD_AObj* aobj;
};

struct _HSD_JObj {
    u8 unk0[8];
    _HSD_JObj* next;
    _HSD_JObj* parent;
    _HSD_JObj* child;
    u32 flags;
    _HSD_DObj* dobj;
    GSvec rotate;
    f32 rotateW;
    GSvec scale;
    GSvec translate;
    Mtx mtx;
    u8 unk74[8];
    HSD_AObj* aobj;
};
typedef _HSD_JObj HSD_JObj;
typedef _HSD_DObj HSD_DObj;
typedef _HSD_MObj HSD_MObj;
typedef _HSD_TObj HSD_TObj;
typedef _HSD_MatAnim HSD_MatAnim;
typedef _HSD_AnimJoint HSD_AnimJoint;
typedef _HSD_MatAnimJoint HSD_MatAnimJoint;
typedef _HSD_ShapeAnimJoint HSD_ShapeAnimJoint;

#define JOBJ_MTX_DIRTY (1 << 6)
#define JOBJ_USER_DEF_MTX (1 << 23)

struct _HSD_SceneModelSet {
    void* joint;
    HSD_AnimJoint** animjoint;
    HSD_MatAnimJoint** matanim_joint;
    HSD_ShapeAnimJoint** shapeanim_joint;
};

struct GSmaterial {
    u8 unk0[8];
    HSD_MObj* mobj;
    u8 unkC[0x28];
};

struct GSmodelPartMix {
    s32 type;
    u32 index;
    f32 rate;
    f32 frame;
    f32 reqFrame;
    f32 endFrame;
    HSD_AObj* aobj;
};

struct GSmodelPartAnim {
    s32 type;
    u32 partIndex;
    void* callback;
    void* arg;
    u32 mixFlags;
    GSvec baseTranslate;
    GSvec baseRotate;
    GSvec baseScale;
};

struct _GSmodel {
    u32 flags;
    u8 unk4[4];
    _HSD_SceneModelSet* set;
    u8 unkC[0x70];
    f32 animRate;
    u8 unk80[0x34];
    f32 texAnimRate;
    u8 unkB8[0x10];
    GSmodelPartMix partMix[8];
    GSmodelPartMix texPartMix[4];
    u8 unk218[4];
    u8 animDirty;
    u8 texAnimDirty;
    u8 unk21E[10];
    GSmodelPartAnim partAnim[16];
    u8 unk5A8[0x38];
    GSmaterial* materials;
    u32 materialCount;
};

struct GSpart {
    u8 inUse;
    u8 pad;
    u16 index;
    _GSmodel* model;
    HSD_JObj* jobj;
};

extern "C" {
void __assert(const char* file, u32 line, const char* expr);
void GSlogWrite(const char*, ...);
void* GSmemAlloc(u32 size);
bool GSmodelCanAnimate(_GSmodel* model);
u32 GSmodelGetMaxAnimIndex(_GSmodel* model);
bool GSmodelCanShapeAnimate(_GSmodel* model);
bool GSmodelCanTexAnimate(_GSmodel* model);
u32 GSmodelGetMaxTexAnimIndex(_GSmodel* model);
void GSmodelUpdate(_GSmodel* model);
bool GSmodelIsBlending(_GSmodel* model);
void HSD_TObjRemoveAnim(HSD_TObj* tobj);
void HSD_TObjAddAnim(HSD_TObj* tobj, void* texanim);
void HSD_TObjReqAnim(HSD_TObj* tobj, f32 frame);
void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags);
void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags);
void HSD_JObjRemoveAnim(HSD_JObj* jobj);
void HSD_JObjAddAnim(HSD_JObj* jobj, HSD_AnimJoint* animjoint, HSD_MatAnimJoint* matanim, HSD_ShapeAnimJoint* shapeanim);
void HSD_JObjReqAnim(HSD_JObj* jobj, f32 frame);
void HSD_JObjSetupMatrixSub(HSD_JObj* jobj);
void HSD_JObjWalkTree(HSD_JObj* jobj, void (*callback)(HSD_JObj*, void**, int), void** arg);
void PSVECAdd(const GSvec* a, const GSvec* b, GSvec* ab);
void PSMTXCopy(const Mtx src, Mtx dst);
}

static GSpart* _partStructList;
static u32 _partStructCount;
static u8 _partFound;
static u32 _partFindCurIdx;
static u32 _partToFindIdx;
static s32 _partFoundIndex;
static HSD_JObj* _partToFindJObj;
static HSD_JObj* _partFoundJObj;
static HSD_AnimJoint* _partFoundAnim;
static HSD_MatAnimJoint* _partFoundMatAnim;
static HSD_ShapeAnimJoint* _partFoundShapeAnim;

static void _partShapeAnimWalkTree0(HSD_ShapeAnimJoint* joint, void (*cb)(HSD_ShapeAnimJoint*, void**, int), void** args);
static void _partMatAnimWalkTree0(HSD_MatAnimJoint* joint, void (*cb)(HSD_MatAnimJoint*, void**, int), void** args);
static void _partAnimWalkTree0(HSD_AnimJoint* joint, void (*cb)(HSD_AnimJoint*, void**, int), void** args);
static void _partFindShapeAnimCB(HSD_ShapeAnimJoint* joint, void** args, int);
static void _partFindMatAnimCB(HSD_MatAnimJoint* joint, void** args, int);
static void _partFindAnimCB(HSD_AnimJoint* joint, void** args, int);
static void _partFindJObjCB(HSD_JObj* jobj, void** args, int);
static void _partFindIndexCB(HSD_JObj* jobj, void** args, int);
















extern "C" {
void GSpartShapeAnimWalkTree(HSD_ShapeAnimJoint* joint, void (*cb)(HSD_ShapeAnimJoint*, void**, int), void** args);
void GSpartMatAnimWalkTree(HSD_MatAnimJoint* joint, void (*cb)(HSD_MatAnimJoint*, void**, int), void** args);
void GSpartAnimWalkTree(HSD_AnimJoint* joint, void (*cb)(HSD_AnimJoint*, void**, int), void** args);
HSD_ShapeAnimJoint* GSpartGetShapeAnimPtr(HSD_ShapeAnimJoint* root, u32 index);
HSD_MatAnimJoint* GSpartGetMatAnimPtr(HSD_MatAnimJoint* root, u32 index);
HSD_AnimJoint* GSpartGetAnimPtr(HSD_AnimJoint* root, u32 index);
HSD_JObj* GSpartGetJObjPtr(HSD_JObj* root, u32 index);
u32 GSpartGetJObjIndex(HSD_JObj* jobj, HSD_JObj* root);
s32 GSpartSetAnimIndex(GSpart* part, int anim, s32 type, f32 frame);
GSpart* GSpartCreate();
void GSpartInit(u32 count);
void GSpartStopAnimIndex(GSpart* part, s32 anim);
s32 GSpartSetTexAnimIndex(GSpart* part, int anim, int index, s32 type, f32 frame);
void GSpartUnregisterAnimMix(GSpart* part, int type);
void GSpartRegisterAnimMix(GSpart* part, int type, u32 mixFlags, void* callback, void* arg);
void GSpartGetMatrix(GSpart* part, Mtx out);
void GSpartGetTransform(GSpart* part, GSvec* position, GSvec* rotation, GSvec* scale);
void GSpartInitMaterial(GSmaterial* material, GSpart* part, u32 index);
GSmaterial* GSpartGetMaterial(GSpart* part, u32 index);
u32 GSpartGetMaterialCount(GSpart* part);
void GSpartFree(GSpart* part);
}




















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

static inline void HSD_JObjSetupMatrix(HSD_JObj* jobj) {
    if (!jobj || !HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetupMatrixSub(jobj);
}

static inline f32 HSD_JObjGetRotationX(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 748, "jobj");
    }
    return jobj->rotate.x;
}

static inline f32 HSD_JObjGetRotationY(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 762, "jobj");
    }
    return jobj->rotate.y;
}

static inline f32 HSD_JObjGetRotationZ(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 776, "jobj");
    }
    return jobj->rotate.z;
}

static inline f32 HSD_JObjGetScaleX(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 899, "jobj");
    }
    return jobj->scale.x;
}

static inline f32 HSD_JObjGetScaleY(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 911, "jobj");
    }
    return jobj->scale.y;
}

static inline f32 HSD_JObjGetScaleZ(HSD_JObj* jobj) {
    if (!jobj) {
        __assert("jobj.h", 923, "jobj");
    }
    return jobj->scale.z;
}

static inline void HSD_JObjGetRotation(HSD_JObj* jobj, Quaternion* quat) {
    if (!jobj) {
        __assert("jobj.h", 733, "jobj");
    }
    if (!quat) {
        __assert("jobj.h", 734, "rotate");
    }
    *quat = *(Quaternion*)&jobj->rotate;
}

static inline void HSD_JObjGetScale(HSD_JObj* jobj, GSvec* scale) {
    if (!jobj) {
        __assert("jobj.h", 849, "jobj");
    }
    if (!scale) {
        __assert("jobj.h", 850, "scale");
    }
    *scale = jobj->scale;
}

static inline void HSD_JObjGetTranslate(HSD_JObj* jobj, GSvec* translate) {
    if (!jobj) {
        __assert("jobj.h", 996, "jobj");
    }
    if (!translate) {
        __assert("jobj.h", 997, "translate");
    }
    *translate = jobj->translate;
}

static inline HSD_JObj* HSD_JObjGetParent(HSD_JObj* jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->parent;
}

#define union_type_dobj(o) ((o)->flags & 0x4020 ? 0 : 1)

static inline HSD_DObj* partGetDObj(GSpart* part) {
    HSD_JObj* jobj = part->jobj;
    if (union_type_dobj(jobj)) {
        return jobj->dobj;
    }
    return 0;
}


static inline HSD_MObj* partFindMaterial(HSD_DObj* dobj, u32 index, u32* count) {
    u32 i = 0;

    while (dobj != 0) {
        if (i++ == index) {
            if (count != 0) {
                *count = index;
            }
            return dobj->mobj;
        }
        dobj = dobj->next;
    }
    if (count != 0) {
        *count = i;
    }
    return 0;
}

static inline GSmaterial* partFindModelMaterial(_GSmodel* model, HSD_MObj* mobj) {
    GSmaterial* mat = (GSmaterial*)(model ? (void*)model->materials : 0);
    u32 count = model ? model->materialCount : 0;
    u32 i;

    if (mat == 0 || count == 0) {
        return 0;
    }
    for (i = 0; i < count; i++, mat++) {
        if (mat->mobj == mobj) {
            return mat;
        }
    }
    return 0;
}













static void _partFindIndexCB(HSD_JObj* jobj, void** args, int) {
    if (_partFound == 1) {
        return;
    }
    if (_partToFindJObj == jobj) {
        _partFoundIndex = _partFindCurIdx;
        _partFound = 1;
    }
    _partFindCurIdx++;
}

static void _partFindJObjCB(HSD_JObj* jobj, void** args, int) {
    if (_partFound == 1) {
        return;
    }
    if (_partFindCurIdx == _partToFindIdx) {
        _partFoundJObj = jobj;
        _partFound = 1;
    }
    _partFindCurIdx++;
}

static void _partFindAnimCB(HSD_AnimJoint* joint, void** args, int) {
    if (_partFound == 1) {
        return;
    }
    if (_partFindCurIdx == _partToFindIdx) {
        _partFoundAnim = joint;
        _partFound = 1;
    }
    _partFindCurIdx++;
}

static void _partFindMatAnimCB(HSD_MatAnimJoint* joint, void** args, int) {
    if (_partFound == 1) {
        return;
    }
    if (_partFindCurIdx == _partToFindIdx) {
        _partFoundMatAnim = joint;
        _partFound = 1;
    }
    _partFindCurIdx++;
}

static void _partFindShapeAnimCB(HSD_ShapeAnimJoint* joint, void** args, int) {
    if (_partFound == 1) {
        return;
    }
    if (_partFindCurIdx == _partToFindIdx) {
        _partFoundShapeAnim = joint;
        _partFound = 1;
    }
    _partFindCurIdx++;
}

static void _partAnimWalkTree0(HSD_AnimJoint* joint, void (*cb)(HSD_AnimJoint*, void**, int), void** args) {
    HSD_AnimJoint* child;

    if (joint == 0) {
        return;
    }
    if (cb != 0) {
        cb(joint, args, 1);
    }
    for (child = joint->child; child != 0; child = child->next) {
        _partAnimWalkTree0(child, cb, args);
    }
}

static void _partMatAnimWalkTree0(HSD_MatAnimJoint* joint, void (*cb)(HSD_MatAnimJoint*, void**, int), void** args) {
    HSD_MatAnimJoint* child;

    if (joint == 0) {
        return;
    }
    if (cb != 0) {
        cb(joint, args, 1);
    }
    for (child = joint->child; child != 0; child = child->next) {
        _partMatAnimWalkTree0(child, cb, args);
    }
}

static void _partShapeAnimWalkTree0(HSD_ShapeAnimJoint* joint, void (*cb)(HSD_ShapeAnimJoint*, void**, int), void** args) {
    HSD_ShapeAnimJoint* child;

    if (joint == 0) {
        return;
    }
    if (cb != 0) {
        cb(joint, args, 1);
    }
    for (child = joint->child; child != 0; child = child->next) {
        _partShapeAnimWalkTree0(child, cb, args);
    }
}

void GSpartInit(u32 count) {
    u32 i;

    _partStructCount = count;
    _partStructList = (GSpart*)GSmemAlloc(count * sizeof(GSpart));
    if (_partStructList != 0) {
        for (i = 0; i < _partStructCount; i++) {
            _partStructList[i].inUse = 0;
        }
    }
}

static inline GSpart* GSpartFindFree() {
    GSpart* part = _partStructList;
    u32 i;

    for (i = 0; i < _partStructCount; i++, part++) {
        if (part->inUse == 0) {
            return part;
        }
    }
    return 0;
}

GSpart* GSpartCreate() {
    GSpart* part = GSpartFindFree();

    if (part == 0) {
        return 0;
    }
    part->inUse = 1;
    return part;
}

void GSpartFree(GSpart* part) {
    part->inUse = 0;
}

u32 GSpartGetMaterialCount(GSpart* part) {
    HSD_DObj* dobj = partGetDObj(part);
    u32 count;

    if (dobj == 0) {
        return 0;
    }
    partFindMaterial(dobj, -1, &count);
    return count;
}

GSmaterial* GSpartGetMaterial(GSpart* part, u32 index) {
    HSD_DObj* dobj = partGetDObj(part);
    if (!dobj) return 0;
    HSD_MObj* object = partFindMaterial(dobj, index, 0);
    if (!object) return 0;
    GSmaterial* list = (part->model ? part->model->materials : 0);
    u32 count = (part->model ? part->model->materialCount : 0);
    if (!list || !count) return 0;
    for (u32 i = 0; i < count; ++i, ++list) {
        if (list->mobj == object) return list;
    }
    return 0;
}

void GSpartInitMaterial(GSmaterial* material, GSpart* part, u32 index) {
    HSD_DObj* dobj;

    material->mobj = 0;
    dobj = partGetDObj(part);
    if (dobj == 0) {
        return;
    }
    material->mobj = partFindMaterial(dobj, index, 0);
}

void GSpartGetTransform(GSpart* part, GSvec* position, GSvec* rotation, GSvec* scale) {
    static HSD_JObj* parentList[24];
    u32 count = 0;
    HSD_JObj* jobj = part->jobj;
    f32 px, py, pz;
    f32 sx, sy, sz;
    GSvec rot;
    GSvec tmp;
    HSD_JObj* rotNode;
    u32 rotIndex;
    HSD_JObj* scaleNode;
    u32 scaleIndex;

    GSmodelUpdate(part->model);
    if (!GSmodelIsBlending(part->model)) {
        HSD_JObjSetupMatrix(jobj);
        px = jobj->mtx[0][3];
        py = jobj->mtx[1][3];
        pz = jobj->mtx[2][3];
    } else if (jobj->flags & 0x600000) {
        px = jobj->translate.x;
        py = jobj->translate.y;
        pz = jobj->translate.z;
    } else {
        px = jobj->mtx[0][3];
        py = jobj->mtx[1][3];
        pz = jobj->mtx[2][3];
    }
    if (rotation != 0 || scale != 0) {
        while (jobj != 0) {
            parentList[count++] = jobj;
            jobj = HSD_JObjGetParent(jobj);
            if (count >= 24) {
                GSlogWrite("GSpart: child node too deep\n");
                jobj = 0;
            }
        }
        if (rotation != 0) {
            rot.x = 0.0f;
            rot.y = 0.0f;
            rot.z = 0.0f;
            for (rotIndex = count; rotIndex != 0; rotIndex--) {
                rotNode = parentList[rotIndex - 1];
                tmp.x = HSD_JObjGetRotationX(rotNode);
                tmp.y = HSD_JObjGetRotationY(rotNode);
                tmp.z = HSD_JObjGetRotationZ(rotNode);
                PSVECAdd(&rot, &tmp, &rot);
            }
        }
        if (scale != 0) {
            sx = 1.0f;
            sy = 1.0f;
            sz = 1.0f;
            for (scaleIndex = count; scaleIndex != 0; scaleIndex--) {
                scaleNode = parentList[scaleIndex - 1];
                f32 x = HSD_JObjGetScaleX(scaleNode);
                f32 y = HSD_JObjGetScaleY(scaleNode);
                f32 z = HSD_JObjGetScaleZ(scaleNode);
                sx *= x;
                sy *= y;
                sz *= z;
            }
        }
    }
    if (position != 0) {
        position->x = px;
        position->y = py;
        position->z = pz;
    }
    if (rotation != 0) {
        rotation->x = rot.x;
        rotation->y = rot.y;
        rotation->z = rot.z;
    }
    if (scale != 0) {
        scale->x = sx;
        scale->y = sy;
        scale->z = sz;
    }
}

void GSpartGetMatrix(GSpart* part, Mtx out) {
    HSD_JObj* jobj = part->jobj;

    if (out != 0) {
        GSmodelUpdate(part->model);
        if (!jobj) {
            __assert("jobj.h", 1148, "jobj");
        }
        HSD_JObjSetupMatrix(jobj);
        PSMTXCopy(jobj->mtx, out);
    }
}

static inline GSmodelPartAnim* partAllocAnimMix(GSpart* part, int type) {
    _GSmodel* model = part->model;
    int i;
    GSmodelPartAnim* anim;

    for (i = 0; i < 16; i++) {
        anim = &model->partAnim[i];
        if (anim->type != 0 && anim->type == type && anim->partIndex == part->index) {
            return 0;
        }
    }
    for (i = 0; i < 16; i++) {
        anim = &model->partAnim[i];
        if (anim->type == 0) {
            return anim;
        }
    }
    return 0;
}

void GSpartRegisterAnimMix(GSpart* part, int type, u32 mixFlags, void* callback, void* arg) {
    GSmodelPartAnim* slot;
    f32 rot[4];

    if (type != 0 && callback != 0) {
        slot = partAllocAnimMix(part, type);
        if (slot != 0) {
            slot->type = type;
            slot->partIndex = part->index;
            slot->callback = callback;
            slot->arg = arg;
            slot->mixFlags = mixFlags;
            HSD_JObjGetTranslate(part->jobj, &slot->baseTranslate);
            HSD_JObjGetRotation(part->jobj, (Quaternion*)rot);
            HSD_JObjGetScale(part->jobj, &slot->baseScale);
            slot->baseRotate.x = rot[0];
            slot->baseRotate.y = rot[1];
            slot->baseRotate.z = rot[2];
        }
    }
}

void GSpartUnregisterAnimMix(GSpart* part, int type) {
    _GSmodel* model = part->model;
    int i;

    for (i = 0; i < 16; i++) {
        GSmodelPartAnim* anim = &model->partAnim[i];
        if (anim->type != 0 && anim->type == type && anim->partIndex == part->index) {
            anim->type = 0;
            return;
        }
    }
}

s32 GSpartSetAnimIndex(GSpart* part, int anim, s32 type, f32 frame) {
    _GSmodel* model = part->model;
    HSD_JObj* jobj = part->jobj;
    GSmodelPartMix* slot;
    int i;
    HSD_AnimJoint* animJoint;
    HSD_ShapeAnimJoint* shapeJoint;
    HSD_AObj* aobj;

    if (anim < 0) {
        return -1;
    }
    if (!GSmodelCanAnimate(model)) {
        return -1;
    }
    if ((u32)anim >= GSmodelGetMaxAnimIndex(model)) {
        return -1;
    }
    for (i = 0; i < 8; i++) {
        slot = &model->partMix[i];
        if (slot->aobj == 0) {
            break;
        }
    }
    if (i >= 8) {
        return -1;
    }
    animJoint = GSpartGetAnimPtr(model->set->animjoint[anim], part->index);
    if (GSmodelCanShapeAnimate(model)) {
        shapeJoint = GSpartGetShapeAnimPtr(model->set->shapeanim_joint[anim], part->index);
    } else {
        shapeJoint = 0;
    }
    if (animJoint == 0 && shapeJoint == 0) {
        return -1;
    }
    if (shapeJoint == 0 && animJoint->aobjdesc == 0) {
        return -1;
    }
    HSD_JObjRemoveAnim(jobj);
    HSD_JObjAddAnim(jobj, animJoint, 0, shapeJoint);
    HSD_JObjReqAnim(jobj, frame);
    aobj = jobj->aobj;
    if (aobj == 0) {
        return -1;
    }
    slot->aobj = aobj;
    slot->type = type;
    slot->index = anim;
    slot->rate = model->animRate;
    slot->frame = frame;
    slot->reqFrame = slot->frame;
    slot->endFrame = aobj->end_frame;
    switch (slot->type) {
    case 0:
        HSD_AObjClearFlags(aobj, 0x20000000);
        break;
    case 1:
        HSD_AObjSetFlags(aobj, 0x20000000);
        break;
    }
    model->animDirty = 1;
    return i;
}

s32 GSpartSetTexAnimIndex(GSpart* part, int anim, int index, s32 type, f32 frame) {
    _GSmodel* model = part->model;
    GSmodelPartMix* slot;
    HSD_MatAnim* matAnim;
    int i;
    HSD_MatAnimJoint* matJoint;
    HSD_TObj* tobj;
    GSmaterial* mat;
    int n;
    HSD_AObj* aobj;

    if (anim < 0 || index < 0) {
        return -1;
    }
    if (!GSmodelCanTexAnimate(model)) {
        return -1;
    }
    if ((u32)index >= GSmodelGetMaxTexAnimIndex(model)) {
        return -1;
    }
    for (i = 0; i < 4; i++) {
        slot = &model->texPartMix[i];
        if (slot->aobj == 0) {
            break;
        }
    }
    if (i >= 4) {
        return -1;
    }
    matJoint = GSpartGetMatAnimPtr(model->set->matanim_joint[index], part->index);
    if (matJoint == 0) {
        return -1;
    }
    matAnim = (HSD_MatAnim*)matJoint->matanim;
    n = anim;
    while (n-- != 0) {
        matAnim = matAnim->next;
        if (matAnim == 0) {
            return -1;
        }
    }
    mat = GSpartGetMaterial(part, anim);
    if (mat == 0) {
        return -1;
    }
    tobj = mat->mobj->tobj;
    if (tobj == 0) {
        return -1;
    }
    HSD_TObjRemoveAnim(tobj);
    HSD_TObjAddAnim(tobj, matAnim->texanim);
    HSD_TObjReqAnim(tobj, frame);
    aobj = tobj->aobj;
    slot->aobj = aobj;
    slot->type = type;
    slot->index = index;
    slot->rate = model->texAnimRate;
    slot->frame = frame;
    slot->reqFrame = slot->frame;
    slot->endFrame = aobj->end_frame;
    switch (slot->type) {
    case 0:
        HSD_AObjClearFlags(aobj, 0x20000000);
        break;
    case 1:
        HSD_AObjSetFlags(aobj, 0x20000000);
        break;
    }
    model->texAnimDirty = 1;
    return i;
}

void GSpartStopAnimIndex(GSpart* part, s32 anim) {
    _GSmodel* model = part->model;
    int i;

    if (anim < 0 || anim >= 8) {
        return;
    }
    if (model->partMix[anim].aobj != 0) {
        model->partMix[anim].aobj = 0;
        i = GSpartSetAnimIndex(part, 0, 1, 0.0f);
        model->partMix[i].aobj = 0;
    }
}

u32 GSpartGetJObjIndex(HSD_JObj* jobj, HSD_JObj* root) {
    if (jobj == root) {
        return 0;
    }
    _partFound = 0;
    _partToFindJObj = root;
    _partFindCurIdx = 0;
    _partFoundIndex = -1;
    HSD_JObjWalkTree(jobj, _partFindIndexCB, 0);
    return _partFoundIndex;
}

HSD_JObj* GSpartGetJObjPtr(HSD_JObj* root, u32 index) {
    if (index == 0) {
        return root;
    }
    _partFound = 0;
    _partToFindIdx = index;
    _partFindCurIdx = 0;
    _partFoundJObj = 0;
    HSD_JObjWalkTree(root, _partFindJObjCB, 0);
    return _partFoundJObj;
}

HSD_AnimJoint* GSpartGetAnimPtr(HSD_AnimJoint* root, u32 index) {
    if (index == 0) {
        return root;
    }
    _partFound = 0;
    _partToFindIdx = index;
    _partFindCurIdx = 0;
    _partFoundAnim = 0;
    GSpartAnimWalkTree(root, _partFindAnimCB, 0);
    return _partFoundAnim;
}

HSD_MatAnimJoint* GSpartGetMatAnimPtr(HSD_MatAnimJoint* root, u32 index) {
    if (index == 0) {
        return root;
    }
    _partFound = 0;
    _partToFindIdx = index;
    _partFindCurIdx = 0;
    _partFoundMatAnim = 0;
    GSpartMatAnimWalkTree(root, _partFindMatAnimCB, 0);
    return _partFoundMatAnim;
}

HSD_ShapeAnimJoint* GSpartGetShapeAnimPtr(HSD_ShapeAnimJoint* root, u32 index) {
    if (index == 0) {
        return root;
    }
    _partFound = 0;
    _partToFindIdx = index;
    _partFindCurIdx = 0;
    _partFoundShapeAnim = 0;
    GSpartShapeAnimWalkTree(root, _partFindShapeAnimCB, 0);
    return _partFoundShapeAnim;
}

void GSpartAnimWalkTree(HSD_AnimJoint* joint, void (*cb)(HSD_AnimJoint*, void**, int), void** args) {
    HSD_AnimJoint* child;

    if (joint == 0) {
        return;
    }
    if (cb != 0) {
        cb(joint, args, 0);
    }
    for (child = joint->child; child != 0; child = child->next) {
        _partAnimWalkTree0(child, cb, args);
    }
}

void GSpartMatAnimWalkTree(HSD_MatAnimJoint* joint, void (*cb)(HSD_MatAnimJoint*, void**, int), void** args) {
    HSD_MatAnimJoint* child;

    if (joint == 0) {
        return;
    }
    if (cb != 0) {
        cb(joint, args, 0);
    }
    for (child = joint->child; child != 0; child = child->next) {
        _partMatAnimWalkTree0(child, cb, args);
    }
}

void GSpartShapeAnimWalkTree(HSD_ShapeAnimJoint* joint, void (*cb)(HSD_ShapeAnimJoint*, void**, int), void** args) {
    HSD_ShapeAnimJoint* child;

    if (joint == 0) {
        return;
    }
    if (cb != 0) {
        cb(joint, args, 0);
    }
    for (child = joint->child; child != 0; child = child->next) {
        _partShapeAnimWalkTree0(child, cb, args);
    }
}
