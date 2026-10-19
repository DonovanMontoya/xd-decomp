#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <dolphin/mtx.h>
#include <dolphin/os/OSFastCast.h>
extern "C" {
extern GSmodel* _modelTopPtr;
u32 GSgfxPerfbarCPUEntry(u32);
void GSparticleDestroyAllGenerators(GSparticleBank*, u8);
void GSparticleSetBankVisibility(GSparticleBank*, u8);
}
extern "C" void GSmodelIterateList(void (*callback)(GSmodel*, void*), void* context) {
    for (GSmodel* model = _modelTopPtr; model; model = model->next) callback(model, context);
}
extern "C" GSmodel* GSmodelSearchModelList(HSD_JObj* joint) {
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        HSD_JObj* render = (model->flags & 0x80) ? model->blendJoint : model->joint;
        if (render == joint) return model;
    }
    return 0;
}
extern "C" void GSmodelSetRenderCamera(GSmodel* model, GScamera* camera) { model->camera = camera; }
extern "C" void GSmodelSetRenderLayer(GSmodel* model, s32 count, const s32* layers) {
    for (s32 i = 0; i < 8; ++i) { if (i < count) model->renderLayers[i] = layers[i]; else model->renderLayers[i] = 255; }
}
extern "C" void GSmodelDestroyLinkedParticles(GSmodel* model) { if (model->particleBank) GSparticleDestroyAllGenerators(model->particleBank, 1); }
extern "C" s32 GSmodelGetGSparticleLinkAttachMode(GSmodel* model) { return model->particleAttachMode; }
extern "C" GSparticleBank* GSmodelGetLinkedGSparticleBank(GSmodel* model) { return model->particleBank; }
extern "C" void GSmodelSetGSparticleLinkAttachMode(GSmodel* model, s32 mode) { model->particleAttachMode = mode; }
extern "C" void GSmodelLinkToGSparticleBank(GSmodel* model, GSparticleBank* bank) {
    if (model->particleBank != bank) {
        model->particleBank = bank;
        if (model->particleBank) {
            model->animationFlags |= 8;
            GSmodelSetAnimFrame(model, model->animationFrame);
            GSmodelForceAnimTransformUpdate(model);
        } else model->animationFlags &= ~8;
    }
}
extern "C" GSbound* GSmodelGetBound(GSmodel* model) { return (GSbound*)model->boundStorage; }
extern "C" void GSmodelSetBoundCheck(GSmodel* model, u8 enable) { if (enable) model->flags |= 0x100000; else model->flags &= ~0x100000; }
extern "C" void GSmodelSetFogState(GSmodel* model, u8 first, u8 second) {
    if (first) model->flags |= 0x1000000; else model->flags &= ~0x1000000;
    if (second) model->flags |= 0x2000000; else model->flags &= ~0x2000000;
}
extern "C" void GSmodelUpdate(GSmodel* model) {
    u32 perf = GSgfxPerfbarCPUEntry(0xff0000);
    modelUpdateAttachments__FP8_GSmodel(model); modelUpdateTransform__FP8_GSmodel(model);
    GSgfxPerfbarCPUEntry(perf);
}
extern "C" u8 GSmodelGetVisibility(GSmodel* model) { return (model->flags >> 1) & 1; }
extern "C" void GSmodelSetVisibility(GSmodel* model, u8 visible) {
    if (visible) { model->flags |= 2; if (model->particleBank) GSparticleSetBankVisibility(model->particleBank, 1); }
    else { model->flags &= ~2; if (model->particleBank) GSparticleSetBankVisibility(model->particleBank, 0); }
}
extern "C" GSvec* GSmodelGetScalePtr(GSmodel* model) { return &model->scale; }
extern "C" void GSmodelGetScale(GSmodel* model, GSvec* out) { out->param1 = model->scale.param1; out->param2 = model->scale.param2; out->param3 = model->scale.param3; }
extern "C" void GSmodelSetScale(GSmodel* model, GSvec* value) {
    if (model->attachmentMode == 0) {
        if (!(model->flags & 0x400)) { model->scale.param1 = value->param1; model->scale.param2 = value->param2; model->scale.param3 = value->param3; }
    } else { model->attachmentScale.param1 = value->param1; model->attachmentScale.param2 = value->param2; model->attachmentScale.param3 = value->param3; }
    model->flags &= ~0x200;
}
extern "C" GSvec* GSmodelGetRotationPtr(GSmodel* model) { return &model->rotation; }
extern "C" void GSmodelGetRotation(GSmodel* model, GSvec* out) { out->param1 = model->rotation.param1; out->param2 = model->rotation.param2; out->param3 = model->rotation.param3; }
extern "C" void GSmodelSetRotation(GSmodel* model, GSvec* value) {
    if (model->attachmentMode == 0) {
        if (!(model->flags & 0x400)) { model->rotation.param1 = value->param1; model->rotation.param2 = value->param2; model->rotation.param3 = value->param3; }
    } else { model->attachmentRotation.param1 = value->param1; model->attachmentRotation.param2 = value->param2; model->attachmentRotation.param3 = value->param3; }
    model->flags &= ~0x200;
}
extern "C" GSvec* GSmodelGetPositionPtr(GSmodel* model) { return &model->position; }
extern "C" void GSmodelGetPosition(GSmodel* model, GSvec* out) { out->param1 = model->position.param1; out->param2 = model->position.param2; out->param3 = model->position.param3; }
extern "C" void GSmodelSetPosition(GSmodel* model, GSvec* value) {
    if (model->attachmentMode == 0) {
        if (!(model->flags & 0x400)) { model->position.param1 = value->param1; model->position.param2 = value->param2; model->position.param3 = value->param3; }
    } else { model->attachmentPosition.param1 = value->param1; model->attachmentPosition.param2 = value->param2; model->attachmentPosition.param3 = value->param3; }
    model->flags &= ~0x200;
}
extern "C" void GSmodelAddPosition(GSmodel* model, GSvec* delta) {
    GSvec value;
    if (model->attachmentMode == 0) { value.param1 = model->position.param1; value.param2 = model->position.param2; value.param3 = model->position.param3; }
    else { value.param1 = model->attachmentPosition.param1; value.param2 = model->attachmentPosition.param2; value.param3 = model->attachmentPosition.param3; }
    PSVECAdd((const Vec*)&value, (const Vec*)delta, (Vec*)&value);
    GSmodelSetPosition(model, &value);
}
extern "C" HSD_JObj* modelGetRenderJObj__FP8_GSmodel(GSmodel* model) { if (model->flags & 0x80) return model->blendJoint; return model->joint; }
extern "C" void modelSetScl__FP8_GSmodelP5GSvec(GSmodel* model, GSvec* v) { if (model->flags & 0x400) return; model->scale.param1 = v->param1; model->scale.param2 = v->param2; model->scale.param3 = v->param3; }
extern "C" void modelSetRot__FP8_GSmodelP5GSvec(GSmodel* model, GSvec* v) { if (model->flags & 0x400) return; model->rotation.param1 = v->param1; model->rotation.param2 = v->param2; model->rotation.param3 = v->param3; }
extern "C" void modelSetPos__FP8_GSmodelP5GSvec(GSmodel* model, GSvec* v) { if (model->flags & 0x400) return; model->position.param1 = v->param1; model->position.param2 = v->param2; model->position.param3 = v->param3; }

extern "C" {
static u32 _modelInUseCount;
void GSgfxRenderWaitForDrawComplete__Fv();
void modelShadowFreeModelList__FP8_GSmodel(GSmodel*);
void modelMaterialFree__FP10GSmaterial(GSmaterial*);
void GSmodelRemoveNull(GSmodel*);
void modelRemoveCenterNull__FP8_GSmodel(GSmodel*);
void GSmodelDisableAnimBlend(GSmodel*);
void HSD_JObjUnref(HSD_JObj*);
void GSmodelFreeDistortion(GSmodel*);
void GSboundFree(GSbound*);
void modelBankReleaseModel__FP8_GSmodel(GSmodel*);
void GSmemFree(void*);
void HSD_JObjSetupMatrixSub(HSD_JObj*);
void HSD_JObjSetMtxDirtySub(HSD_JObj*);
void __assert(const char*, int, const char*);
}
// Matches the SDK's lazy matrix setup and assertion contract.
static inline u8 modelJointMatrixDirty(HSD_JObj* joint) {
    if (!joint) __assert("jobj.h", 605, "jobj");
    u8 dirty = 0;
    if (!(joint->flags & 0x800000) && (joint->flags & 0x40)) dirty = 1;
    return dirty;
}
extern "C" f32 (*GSmodelGetMatrixPtr(GSmodel* model))[4] {
    HSD_JObj* joint = model->joint;
    if (joint && modelJointMatrixDirty(joint)) HSD_JObjSetupMatrixSub(joint);
    return model->joint->mtx;
}
extern "C" void GSmodelSetMatrix(GSmodel* model, Mtx matrix) {
    HSD_JObj* joint = model->joint;
    if (!joint) __assert("jobj.h", 1173, "jobj");
    if (!matrix) __assert("jobj.h", 1174, "mtx");
    PSMTXCopy(matrix, joint->mtx);
    joint->flags |= 0x3800000;
    if (joint && !modelJointMatrixDirty(joint)) HSD_JObjSetMtxDirtySub(joint);
}
extern "C" void GSmodelFree(GSmodel* model) {
    GSgfxRenderWaitForDrawComplete__Fv();
    modelShadowFreeModelList__FP8_GSmodel(model);
    GSmaterial* material;
    u32 count;
    count = model->materialCount;
    material = model->materials;
    if (count && material) {
        for (u32 i = 0; i < count; ++i, ++material) modelMaterialFree__FP10GSmaterial(material);
        GSmemFree(model->materials);
        model->materialCount = 0; model->materials = 0;
    }
    GSmodelRemoveNull(model); modelRemoveCenterNull__FP8_GSmodel(model);
    GSmodelDisableAnimBlend(model); HSD_JObjUnref(model->joint);
    if (model->particleBank) GSparticleDestroyAllGenerators(model->particleBank, 1);
    GSmodelFreeDistortion(model); GSboundFree((GSbound*)model->boundStorage);
    --_modelInUseCount;
    modelBankReleaseModel__FP8_GSmodel(model);
}

#include <game/pxdvs/GSAPI/GScamera/GScamera.hpp>
extern "C" {
void GSboundGetWorldPosition(GSbound*, Vec*);
s32 GSboundIsInViewFast(GSbound*);
void GSgfxProjectSetupParameters();
void modelDustUpdate__FP8_GSmodel(GSmodel*);
void modelShadowUpdate__Fv();
}
extern "C" f32 GSmodelGetDistanceFromCamera(GSmodel* model) {
    GScamera* camera = model->camera;
    if (!camera) camera = GScameraGetActiveCamera();
    if (!camera) return 0.0f;
    Vec position;
    GSboundGetWorldPosition((GSbound*)model->boundStorage, &position);
    return PSVECDistance(&position, &camera->position);
}
// These callbacks are retained while the render-module registration is recovered.
#pragma push
#pragma force_active on
extern "C" {
static void _modelPostUpdate60fps__Fv() {
    u32 perf = GSgfxPerfbarCPUEntry(0x80);
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        if (modelProcessAt60fps__FP8_GSmodel(model) == 1) GSmodelAdvanceAnimation(model, 1.0f);
    }
    GSgfxPerfbarCPUEntry(perf);
}
static void _modelPostUpdate__Ff(f32 delta) {
    u32 perf = GSgfxPerfbarCPUEntry(0x80);
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        if (!modelProcessAt60fps__FP8_GSmodel(model)) GSmodelAdvanceAnimation(model, delta);
        modelDustUpdate__FP8_GSmodel(model);
    }
    GSgfxPerfbarCPUEntry(perf);
}
static void _modelPreUpdate__Ff(f32) {
    GSgfxProjectSetupParameters();
    u32 perf = GSgfxPerfbarCPUEntry(0x80);
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        model->flags &= 0xfbbffdff;
        if (model->flags & 2) {
            if (!model->camera && (model->flags & 0x100000)) {
                if (GSboundIsInViewFast((GSbound*)model->boundStorage)) model->flags |= 0x4000000;
            } else model->flags |= 0x4000000;
            if ((model->flags & 0x4000000) || (model->animationFlags & 8)) modelApplyAnimation__FP8_GSmodel(model);
        }
    }
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        if (model->flags & 2) { modelUpdateAttachments__FP8_GSmodel(model); modelUpdateTransform__FP8_GSmodel(model); }
    }
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        if (model->flags & 0x4000000) modelApplyPartAnimMixes__FP8_GSmodel(model);
    }
    modelShadowUpdate__Fv();
    GSgfxPerfbarCPUEntry(perf);
}
}
#pragma pop

#include <game/pxdvs/GSAPI/GSpart/GSpart.hpp>
#include <game/maximum/GSAPI/baselib/quatlib.h>
extern "C" void GSvecTransformQuat(GSvec*, HSD_Quaternion*, GSvec*);
extern "C" void GSmodelDetachFromGSpart(GSmodel* model, u8 keepTransform) {
    if (model->attachmentMode != 0) {
        HSD_JObj* joint = model->joint;
        if (!joint) __assert("jobj.h", 1199, "jobj");
        joint->flags &= ~0x3800000;
        if (joint && !modelJointMatrixDirty(joint)) HSD_JObjSetMtxDirtySub(joint);
        model->attachmentModel = 0;
        model->attachmentPart = 0;
        model->flags &= ~0x40000;
        model->attachmentMode = 0;
        if (keepTransform) {
            GSmodelSetPosition(model, &model->attachmentPosition);
            GSmodelSetRotation(model, &model->attachmentRotation);
            GSmodelSetScale(model, &model->attachmentScale);
        }
    }
}
extern "C" void GSmodelAttachToGSpart(GSmodel* model, GSpart* part, s32 mode, u8 once, u8 reset) {
    if (model->attachmentMode == 0 && mode != 0) {
        model->attachmentModel = part->model;
        model->attachmentPart = part->index;
        if (reset == 1) {
            model->attachmentPosition.param1 = 0.0f; model->attachmentPosition.param2 = 0.0f; model->attachmentPosition.param3 = 0.0f;
            model->attachmentRotation.param1 = 0.0f; model->attachmentRotation.param2 = 0.0f; model->attachmentRotation.param3 = 0.0f;
            model->attachmentScale.param1 = 1.0f; model->attachmentScale.param2 = 1.0f; model->attachmentScale.param3 = 1.0f;
        } else {
            Vec position, rotation, scale, offset, inverseRotation;
            HSD_Quaternion quaternion;
            GSpartGetTransform(part, &position, &rotation, &scale);
            PSVECSubtract((Vec*)&model->position, &position, &offset);
            PSVECScale(&rotation, &inverseRotation, -1.0f);
            EulerToQuat((HSD_Vec3*)&inverseRotation, &quaternion);
            GSvecTransformQuat(&model->attachmentPosition, &quaternion, (GSvec*)&offset);
            PSVECSubtract((Vec*)&model->rotation, &rotation, (Vec*)&model->attachmentRotation);
            model->attachmentScale.param1 = model->scale.param1 * scale.x;
            model->attachmentScale.param2 = model->scale.param2 * scale.y;
            model->attachmentScale.param3 = model->scale.param3 * scale.z;
        }
        model->attachmentMode = mode;
        if (once) model->flags |= 0x40000;
        model->flags &= ~0x400000;
        model->flags &= ~0x200;
    }
}

static inline void copyModelVector(GSvec* destination, f32 x, f32 y, f32 z) {
    destination->param1 = x; destination->param2 = y; destination->param3 = z;
}

struct ModelJointDescriptor {
    void* className;
    u32 flags;
    HSD_Joint *child, *next;
    void* data;
    GSvec rotation, scale, position;
    void *inverseMatrix, *references;
};
struct ModelLoadState : GSmodel {
    u32 reserved5E8, reserved5EC, reserved5F0;
    f32 reserved5F4;
    u32 reserved5F8;
    f32 reserved5FC;
    u8 reserved600[4];
    f32 reserved604;
    u8 reserved608[4];
    f32 reserved60C;
    u16 reserved610;
    u8 reserved612, reserved613;
    void *reserved614, *reserved618, *reserved61C;
    u32 vertexCount, normalCount;
};
extern "C" {
static u8 _invalidateVtxTex;
static s32 _modelMaxUsedCount;
GSmodel* modelBankGetFreeModel__Fv();
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint*);
void GSboundCreate(GSbound*, void*);
void GSboundSetDataPtr(GSbound*, s32, void*);
u8 GSboundHasAnimData(GSbound*);
void GSmodelRecalculateBound(GSmodel*);
u32 GSmodelGetPartCount(GSmodel*);
void GSmodelSetAnimIndex(GSmodel*, u32);
void GSmodelSetAnimType(GSmodel*, s32);
void HSD_JObjCountVertices(HSD_JObj*, u32*, u32*);
void* GSmemAlloc(u32);
static GSmodel* _modelLoad__FP18_HSD_SceneModelSetP10_HSD_JointP17GSboundAnimHeader(GSmodelScene*, HSD_Joint*, void*);
#pragma dont_inline on
GSmodel* GSmodelLoad(GSmodelScene* scene, void* bound) {
    _invalidateVtxTex = 1;
    return _modelLoad__FP18_HSD_SceneModelSetP10_HSD_JointP17GSboundAnimHeader(scene, scene->joint, bound);
}
GSmodel* GSmodelClone(GSmodel* model) {
    ModelJointDescriptor joint;
    joint.className = 0;
    HSD_Joint* root = model->scene->joint;
    joint.flags = ((ModelJointDescriptor*)root)->flags | 0x1000;
    joint.child = root;
    joint.next = 0;
    joint.data = 0;
    joint.rotation.param1 = 0.0f; joint.rotation.param2 = 0.0f; joint.rotation.param3 = 0.0f;
    joint.scale.param1 = 1.0f; joint.scale.param2 = 1.0f; joint.scale.param3 = 1.0f;
    joint.position.param1 = 0.0f; joint.position.param2 = 0.0f; joint.position.param3 = 0.0f;
    joint.inverseMatrix = 0;
    joint.references = 0;
    if (GSboundHasAnimData((GSbound*)model->boundStorage) == 0) {
        return _modelLoad__FP18_HSD_SceneModelSetP10_HSD_JointP17GSboundAnimHeader(model->scene, (HSD_Joint*)&joint, 0);
    } else {
        return _modelLoad__FP18_HSD_SceneModelSetP10_HSD_JointP17GSboundAnimHeader(model->scene, (HSD_Joint*)&joint, *(void**)(model->boundStorage + 0x10));
    }
}
static GSmodel* _modelLoad__FP18_HSD_SceneModelSetP10_HSD_JointP17GSboundAnimHeader(GSmodelScene* scene, HSD_Joint* joint, void* bound) {
    ModelLoadState* model = (ModelLoadState*)modelBankGetFreeModel__Fv();
    if (!model) return 0;
    model->flags |= 0x2000;
    model->camera = 0;
    model->animationCount = 0;
    model->textureAnimationCount = 0;
    model->endedCallback = 0;
    model->materialCount = 0;
    model->materials = 0;
    for (s32 i=0; i<8; ++i) model->renderLayers[i] = 255;
    model->renderLayers[0] = 2;
    model->reserved5F8 = 0;
    model->reserved60C = 1.0f;
    model->reserved5FC = 0.0f;
    model->reserved600[1] = 0; model->reserved600[0] = 0; model->reserved600[2] = 0; model->reserved600[3] = 0;
    model->reserved604 = 0.0f;
    model->reserved608[1] = 0; model->reserved608[0] = 0; model->reserved608[2] = 0; model->reserved608[3] = 0;
    model->reserved613 = 0;
    model->reserved610 = 0;
    model->reserved612 = 0;
    model->reserved614 = 0; model->reserved618 = 0; model->reserved61C = 0;
    model->reserved5E8 = 0; model->reserved5EC = 0; model->reserved5F0 = 0;
    model->reserved5F4 = 0.0f;
    model->attachmentMode = 0;
    model->attachmentModel = 0;
    model->attachmentPart = 0;
    model->particleBank = 0;
    model->particleAttachMode = 1;
    model->scene = scene;
    model->joint = HSD_JObjLoadJoint(joint);
    model->animationBlendJoint = 0;
    model->blendJoint = 0;
    copyModelVector(&model->position, model->joint->translate.x, model->joint->translate.y, model->joint->translate.z);
    copyModelVector(&model->rotation, model->joint->rotate.x, model->joint->rotate.y, model->joint->rotate.z);
    copyModelVector(&model->scale, model->joint->scale.x, model->joint->scale.y, model->joint->scale.z);
    model->partAnimMixes[0].identifier = 0;
    model->partAnimMixes[1].identifier = 0;
    model->partAnimMixes[2].identifier = 0;
    model->partAnimMixes[3].identifier = 0;
    model->partAnimMixes[4].identifier = 0;
    model->partAnimMixes[5].identifier = 0;
    model->partAnimMixes[6].identifier = 0;
    model->partAnimMixes[7].identifier = 0;
    model->partAnimMixes[8].identifier = 0;
    model->partAnimMixes[9].identifier = 0;
    model->partAnimMixes[10].identifier = 0;
    model->partAnimMixes[11].identifier = 0;
    model->partAnimMixes[12].identifier = 0;
    model->partAnimMixes[13].identifier = 0;
    model->partAnimMixes[14].identifier = 0;
    model->partAnimMixes[15].identifier = 0;
    for (s32 i=0; i<8; ++i) model->partAnimations[i].animation = 0;
    for (s32 i=0; i<4; ++i) model->partTextureAnimations[i].animation = 0;
    model->partAnimationChanged = 0;
    model->partTextureAnimationChanged = 0;
    if (model->scene->shapeAnimations) model->flags |= 0x10;
    if (model->scene->animations) {
        model->flags |= 4;
        model->animationIndex = -1;
        while (model->scene->animations[model->animationCount]) ++model->animationCount;
        GSmodelSetAnimIndex(model, 0);
        GSmodelSetAnimRate(model, 0.5f);
        GSmodelSetAnimType(model, 1);
    }
    if (model->scene->materialAnimations) {
        model->flags |= 8;
        model->textureAnimationIndex = -1;
        while (model->scene->materialAnimations[model->textureAnimationCount]) ++model->textureAnimationCount;
        GSmodelSetTexAnimIndex(model, 0);
        GSmodelSetTexAnimRate(model, 0.5f);
        GSmodelSetTexAnimType(model, 1);
    }
    GSboundCreate((GSbound*)model->boundStorage, bound);
    GSboundSetDataPtr((GSbound*)model->boundStorage, 1, model);
    GSmodelRecalculateBound(model);
    u32 i;
    u32 partCount;
    GSpart* part;
    u32 materialCount = 0;
    GSmaterial* material;
    partCount = GSmodelGetPartCount(model);
    for (i=0; i<partCount; ++i) {
        part = GSmodelGetPart(model, i);
        materialCount += GSpartGetMaterialCount(part);
        GSpartFree(part);
    }
    if (materialCount) {
        material = (GSmaterial*)GSmemAlloc(materialCount*sizeof(GSmaterial));
        if (material) {
            model->materials = material;
            model->materialCount = materialCount;
            for (u32 i=0; i<partCount; ++i) {
                GSpart* part = GSmodelGetPart(model, i);
                u32 count = GSpartGetMaterialCount(part);
                for (u32 n=0; n<count; ++n, ++material) {
                    modelMaterialInit__FP10GSmaterial(material);
                    GSpartInitMaterial(material, part, n);
                }
                GSpartFree(part);
            }
        }
    }
    HSD_JObjCountVertices(model->joint, &model->vertexCount, &model->normalCount);
    ++_modelInUseCount;
    if ((s32)_modelInUseCount > _modelMaxUsedCount) _modelMaxUsedCount = _modelInUseCount;
    return model;
}
#pragma dont_inline reset
}

struct ModelRenderModule {
    void* context;
    void (*preUpdate)(f32);
    void (*render)(void*, s32);
    void (*fastRender)();
    void (*postUpdate)(f32);
    void (*update60)();
    u32 identifier;
};
extern "C" {
extern u8 _modelShadowShowDebug;
void modelShadowRenderDebug__Fv();
void modelDistortionRender__Fv();
void modelBankInit__Fv();
void modelShadowInit__Fv();
void GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(u8, ModelRenderModule*, void*);
void HSD_SetVertexBuffer(void*, u32);
void HSD_SetNormalBuffer(void*, u32);
void HSD_SetExpArgBuffer(void*, u32);
static void _modelRender__FP10GSgfxLayer14GSgfxLayerPass(GSgfxLayer*, s32);
#pragma dont_inline on
static void _modelFastRender__Fv() {
    if (_modelShadowShowDebug == 1) modelShadowRenderDebug__Fv();
    modelDistortionRender__Fv();
}
void GSmodelInit() {
    ModelRenderModule module = {0, _modelPreUpdate__Ff, (void (*)(void*, s32))_modelRender__FP10GSgfxLayer14GSgfxLayerPass, _modelFastRender__Fv, _modelPostUpdate__Ff, _modelPostUpdate60fps__Fv, 0xB29A48E1};
    modelBankInit__Fv();
    modelShadowInit__Fv();
    GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(0x20, &module, 0);
    HSD_SetVertexBuffer(GSmemAlloc(0x5DC0), 0x7D0);
    HSD_SetNormalBuffer(GSmemAlloc(0x5DC0), 0x7D0);
    HSD_SetExpArgBuffer(GSmemAlloc(0x190), 0x64);
}
#pragma dont_inline reset
}

#include <game/pxdvs/GSAPI/GScamera/GScameraLayer.hpp>
struct ModelRenderLayer {
    u32 reserved00, flags;
    u8 reserved08[0x20];
    s32 id, kind;
    u8 reserved30[0xD90-0x30];
    u32 projectionFlag;
    u8 reservedD94[0x16A6-0xD94];
    u8 lightingEnabled, fogEnabled;
    GSgfxCameraRenderState renderState[2];
};
static inline void modelSetLayerFog(ModelRenderLayer* layer, u8 enabled) {
    layer->fogEnabled = enabled;
    layer->renderState[0].lighting |= 0x40;
    layer->renderState[1].lighting |= 0x40;
    if (enabled) {
        layer->renderState[0].lighting |= 0x200;
        layer->renderState[1].lighting |= 0x200;
        if (layer->lightingEnabled) {
            layer->renderState[0].lighting |= 0x100;
            layer->renderState[1].lighting |= 0x100;
        }
    }
    layer->renderState[0].dirty |= 0x40;
    layer->renderState[1].dirty |= 0x40;
}
extern "C" {
void HSD_InitColorSwapTable(u32, u32, u32, u32, u32);
void HSD_ResetColorSwapTables();
void GScameraLoadProjection(GScamera*, GSgfxLayer*);
void FlushState__10GSgfxLayerFv(GSgfxLayer*);
void InvalidateState__10GSgfxLayerFv(GSgfxLayer*);
u16 tokenMark__10GSgfxLayerFv(GSgfxLayer*);
void HSD_StateInvalidate(u32);
void GSlightSetupLights(HSD_CObj*);
void modelShadowPrepare__FP8_GSmodelb(GSmodel*, bool);
void HSD_JObjDispAll(HSD_JObj*, Mtx, u32, u32);
void modelShadowRenderMarukage__FP8_GSmodelP10GSgfxLayer(GSmodel*, GSgfxLayer*);
void GSboundDraw__FP7GSboundP10GSgfxLayer(GSbound*, GSgfxLayer*);
static void _modelRenderModelSub__FP10GSgfxLayer14GSgfxLayerPassP8_GSmodel(GSgfxLayer*, s32, GSmodel*);
#pragma dont_inline on
void GSmodelDrawModel(GSmodel* model, GSgfxLayer* layerPtr, s32 pass) {
    ModelRenderLayer* layer = (ModelRenderLayer*)layerPtr;
    if (model && (model->flags & 1)) {
        u8 fog = layer->fogEnabled != 0;
        if (layer->kind == 1) HSD_InitColorSwapTable(0, 2, 2, 2, 3);
        else HSD_InitColorSwapTable(0, 0, 1, 2, 3);
        HSD_InitColorSwapTable(1, 0, 1, 2, 3);
        HSD_InitColorSwapTable(2, 0, 1, 2, 3);
        HSD_InitColorSwapTable(3, 0, 1, 2, 3);
        _modelRenderModelSub__FP10GSgfxLayer14GSgfxLayerPassP8_GSmodel(layerPtr, pass, model);
        HSD_ResetColorSwapTables();
        modelSetLayerFog(layer, fog);
    }
}
extern "C" {
void GSgfxTokenIfClearedReset(void*);
void modelShadowRender__FP10GSgfxLayer(GSgfxLayer*);
void GScameraLoadActiveCameraMatrix(s32);
void GSgfxVideoGetEFBSize(u16*, u16*);
extern u8 _invalidateVtxTex;
extern s32 modelShadowLayerID;
}
template <class T> static inline T& modelLayerField(void* base, u32 offset) { return *(T*)((u8*)base + offset); }
static void _modelRender__FP10GSgfxLayer14GSgfxLayerPass(GSgfxLayer* layer, s32 pass) {
    s32 perf;
    u8 layerId;
    u16 height;
    u16 width;
    u16 halfWidth;
    u16 halfHeight;
    f32 right;
    f32 bottom;
    u8 fogWasOn;
    GSmodel* model;
    u8 rendered;
    layerId = modelLayerField<s32>(layer, 0x28);
    if (_invalidateVtxTex == 1) {
        modelLayerField<u32>(layer, 4) |= 0x08000000;
        modelLayerField<u32>(layer, 4) |= 0x10000000;
        _invalidateVtxTex = 0;
    }
    if (layerId == modelShadowLayerID) {
        perf = GSgfxPerfbarCPUEntry(0xFF8000);
        modelShadowRender__FP10GSgfxLayer(layer);
        bottom = 240.0f;
        right = 320.0f;
        if (pass == 0) {
            GSgfxVideoGetEFBSize(&width, &height);
            halfWidth = width >> 1;
            right = __OSu16tof32(&halfWidth);
            halfHeight = height >> 1;
            bottom = __OSu16tof32(&halfHeight);
        }
        modelLayerField<f32>(layer, 0xD78) = 0.0f;
        modelLayerField<f32>(layer, 0xD7C) = 0.0f;
        modelLayerField<f32>(layer, 0xD80) = right;
        modelLayerField<f32>(layer, 0xD84) = bottom;
        modelLayerField<u32>(layer, 0x16B8) |= 0x10;
        modelLayerField<u32>(layer, 0x16A8) |= 2;
        modelLayerField<u32>(layer, 0x1770) |= 0x10;
        modelLayerField<u32>(layer, 0x1760) |= 2;
        modelLayerField<u16>(layer, 0xD70) = 0;
        modelLayerField<u16>(layer, 0xD72) = 0;
        GSgfxVideoGetEFBSize(&modelLayerField<u16>(layer, 0xD74), &modelLayerField<u16>(layer, 0xD76));
        modelLayerField<u32>(layer, 0x16B8) |= 1;
        modelLayerField<u32>(layer, 0x16A8) |= 2;
        modelLayerField<u32>(layer, 0x1770) |= 1;
        modelLayerField<u32>(layer, 0x1760) |= 2;
        FlushState__10GSgfxLayerFv(layer);
    } else {
        rendered = 0;
        perf = GSgfxPerfbarCPUEntry(0xFF);
        if (modelLayerField<s32>(layer, 0x2C) == 1) HSD_InitColorSwapTable(0, 2, 2, 2, 3);
        else HSD_InitColorSwapTable(0, 0, 1, 2, 3);
        HSD_InitColorSwapTable(1, 0, 1, 2, 3);
        HSD_InitColorSwapTable(2, 0, 1, 2, 3);
        HSD_InitColorSwapTable(3, 0, 1, 2, 3);
        model = _modelTopPtr;
        fogWasOn = modelLayerField<u8>(layer, 0x16A7) != 0;
        while (model) {
            GSgfxTokenIfClearedReset((u8*)model + 0x62);
            if (model->flags & 0x04000000) {
                for (s32 i = 0; i < 8; i++) {
                    if (*((u8*)model + (i + 0x64)) == layerId) {
                        _modelRenderModelSub__FP10GSgfxLayer14GSgfxLayerPassP8_GSmodel(layer, pass, model);
                        rendered = 1;
                        break;
                    }
                }
            }
            model = model->next;
        }
        if (rendered) {
            HSD_ResetColorSwapTables();
            GScameraLoadActiveCameraMatrix(modelLayerField<s32>(layer, 0x28));
        }
        modelLayerField<u8>(layer, 0x16A7) = fogWasOn;
        modelLayerField<u32>(layer, 0x170C) |= 0x40;
        modelLayerField<u32>(layer, 0x17C4) |= 0x40;
        if (fogWasOn) {
            modelLayerField<u32>(layer, 0x170C) |= 0x200;
            modelLayerField<u32>(layer, 0x17C4) |= 0x200;
            if (modelLayerField<u8>(layer, 0x16A6) != 0) {
                modelLayerField<u32>(layer, 0x170C) |= 0x100;
                modelLayerField<u32>(layer, 0x17C4) |= 0x100;
            }
        }
        modelLayerField<u32>(layer, 0x16A8) |= 0x40;
        modelLayerField<u32>(layer, 0x1760) |= 0x40;
    }
    GSgfxPerfbarCPUEntry(perf);
}
static void _modelRenderModelSub__FP10GSgfxLayer14GSgfxLayerPassP8_GSmodel(GSgfxLayer* layerPtr, s32 pass, GSmodel* model) {
    ModelRenderLayer* layer = (ModelRenderLayer*)layerPtr;
    modelUpdateTransform__FP8_GSmodel(model);
    u32 fog = layer->fogEnabled != 0;
    if (layer->kind == 0) {
        switch (pass) {
        case 0:
            { u32 bit = model->flags & 0x1000000;
            if (fog != ((model->flags >> 24) & 1)) modelSetLayerFog(layer, bit == 0x1000000); }
            break;
        case 1:
            { u32 bit = model->flags & 0x2000000;
            if (fog != ((model->flags >> 25) & 1)) modelSetLayerFog(layer, bit == 0x2000000); }
            break;
        }
        GScamera* camera = model->camera;
        if (!camera) camera = GScameraGetActiveCamera();
        if (camera && camera->object) {
            GScameraLoadProjection(camera, layerPtr);
            layer->projectionFlag = 0;
            layer->renderState[0].clipping |= 4;
            layer->renderState[0].dirty |= 2;
            layer->renderState[1].clipping |= 4;
            layer->renderState[1].dirty |= 2;
            FlushState__10GSgfxLayerFv(layerPtr);
            HSD_StateInvalidate(-1);
            GSlightSetupLights(camera->object);
            modelShadowPrepare__FP8_GSmodelb(model, true);
            HSD_JObj* joint = modelGetRenderJObj__FP8_GSmodel(model);
            switch (pass) {
            case 0: HSD_JObjDispAll(joint, 0, 1, 0); break;
            case 1: HSD_JObjDispAll(joint, 0, 6, 0); break;
            }
            *(volatile u8*)0xCC008000 = 0x10;
            *(volatile u16*)0xCC008000 = 0;
            *(volatile u16*)0xCC008000 = 0x1005;
            *(volatile u32*)0xCC008000 = 0;
            modelShadowPrepare__FP8_GSmodelb(model, false);
            InvalidateState__10GSgfxLayerFv(layerPtr);
            model->renderToken = tokenMark__10GSgfxLayerFv(layerPtr);
        }
        if (pass == 1) {
            if (model->flags & 0x8000000) modelShadowRenderMarukage__FP8_GSmodelP10GSgfxLayer(model, layerPtr);
            if (model->flags & 0x200000) GSboundDraw__FP7GSboundP10GSgfxLayer((GSbound*)model->boundStorage, layerPtr);
        }
    }
}
#pragma dont_inline reset
}
