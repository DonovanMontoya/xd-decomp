#pragma auto_inline on
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <game/maximum/GSAPI/baselib/mtx_base.h>
extern "C" void __assert(const char*, int, const char*);
extern "C" void HSD_JObjSetupMatrixSub(HSD_JObj*);
extern "C" {
extern Mtx mtxIdent;
void* memcpy(void*, const void*, unsigned long);
HSD_JObj* HSD_JObjGetCurrent();
void HSD_JObjSetCurrent(HSD_JObj*);
void HSD_DObjSetCurrent(HSD_DObj*);
void HSD_JObjMakePositionMtx(HSD_JObj*, Mtx, Mtx);
void HSD_PObjClearMtxMark(s32, s32);
void HSD_PObjGetMtxMark(s32, HSD_JObj**, u32*);
void HSD_PObjSetMtxMark(s32, HSD_JObj*, u32);
f32 (*_HSD_mkEnvelopeModelNodeMtx(HSD_JObj*, Mtx))[4];
}
extern "C" {
static inline s32 parseJointMtxIsDirty(HSD_JObj* joint) {
    if (!joint) __assert("jobj.h", 605, "jobj");
    u8 dirty = 0;
    if (!(joint->flags & 0x800000) && (joint->flags & 0x40)) dirty = 1;
    return dirty;
}
#pragma dont_inline on
static s32 HSD_JObjMtxIsDirty(HSD_JObj* joint) {return parseJointMtxIsDirty(joint);}
#pragma dont_inline reset
static inline void HSD_JObjSetupMatrix(HSD_JObj* joint) {
    if (!joint || !(u8)parseJointMtxIsDirty(joint)) return;
    HSD_JObjSetupMatrixSub(joint);
}
}
struct GSmtx { Mtx matrix; GSmtx() {} };
struct GSmodelEnvelope { GSmodelEnvelope* next; HSD_JObj* joint; f32 weight; };
extern "C" {
static void _modelParseJObjDispAll__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_JObj*, GSmtx*, s32, bool, GSmodelParseCallback, void*);
static void _modelParseSetupInstanceMtx__FP5GSmtxP9_HSD_JObjP5GSmtx(GSmtx*, HSD_JObj*, GSmtx*);
static void _modelParseJObjDisp__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_JObj*, GSmtx*, s32, bool, GSmodelParseCallback, void*);
static void _modelParseJObjDispDObj__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_JObj*, GSmtx*, s32, bool, GSmodelParseCallback, void*);
static void _modelParseJObjDispSub__FP9_HSD_JObjP5GSmtxP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_JObj*, GSmtx*, GSmtx*, s32, bool, GSmodelParseCallback, void*);
static inline void parseDisplayObject(HSD_DObj*, GSmtx*, GSmtx*, bool, GSmodelParseCallback, void*);
static void _modelParseLoadEnvelopeMatrix__FP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtx(HSD_PObj*, GSmtx*, GSmtx*, GSmtx*);
static void _modelParseDObjDisp__FP9_HSD_DObjP5GSmtxP5GSmtxbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_DObj*, GSmtx*, GSmtx*, bool, GSmodelParseCallback, void*);
// All display paths use the same identity matrix, including the separately
// emitted display entry point.
static inline GSmtx* parseIdentityMatrix() {
    static GSmtx identity;
    memcpy(identity.matrix, mtxIdent, sizeof(Mtx));
    return &identity;
}

// The traversal expands the display pass but retains the polygon display call.
// Keep these inline forms separate from the emitted entry points below, whose
// own inline boundaries differ.
static inline void parseJointDisplayPass(HSD_JObj* joint, GSmtx* view, GSmtx* position, s32 mask, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    HSD_JObjSetCurrent(joint);
    u32 objectMask = mask << 1;
    HSD_PObjClearMtxMark(0, 0);
    for (HSD_DObj* object = joint->u.dobj; object; object = object->next) {
        if (!(object->flags & 1) && (object->flags & objectMask)) {
            HSD_DObjSetCurrent(object);
            _modelParseDObjDisp__FP9_HSD_DObjP5GSmtxP5GSmtxbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(object, view, position, loadMatrices, callback, context);
        }
    }
    HSD_DObjSetCurrent(0);
    HSD_JObjSetCurrent(0);
}
static inline void parseJointDisplayObjects(HSD_JObj* joint, GSmtx* view, s32 mask, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    u32 flags = joint->flags;
    if (!(flags & 0x10)) {
        u32 transparency = flags & (mask << 18);
        if (transparency) {
            if (joint && HSD_JObjMtxIsDirty(joint)) HSD_JObjSetupMatrixSub(joint);
            if (!view) view = parseIdentityMatrix();
            GSmtx position;
            HSD_JObjMakePositionMtx(joint, view->matrix, position.matrix);
            if (transparency & 0x40000) parseJointDisplayPass(joint, view, &position, 1, loadMatrices, callback, context);
            if (transparency & 0x100000) parseJointDisplayPass(joint, view, &position, 4, loadMatrices, callback, context);
            if (transparency & 0x80000) parseJointDisplayPass(joint, view, &position, 2, loadMatrices, callback, context);
        }
    }
}
static inline void parseJointDisplay(HSD_JObj* joint, GSmtx* view, s32 mask, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    if (joint && ((joint->flags & 0x4020) ? 0 : 1)) parseJointDisplayObjects(joint, view, mask, loadMatrices, callback, context);
}
void GSmodelParse(GSmodel* model, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    _modelParseJObjDispAll__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(modelGetRenderJObj__FP8_GSmodel(model), 0, 7, loadMatrices, callback, context);
}
static void _modelParseJObjDispAll__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_JObj* joint, GSmtx* view, s32 mask, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    if (joint) {
        if (joint->flags & 0x1000) {
            if (!(joint->flags & 0x10)) {
                GSmtx instance;
                _modelParseSetupInstanceMtx__FP5GSmtxP9_HSD_JObjP5GSmtx(view, joint, &instance);
                _modelParseJObjDispAll__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(joint->child, &instance, mask, loadMatrices, callback, context);
            }
        } else {
            if (joint->flags & (mask << 18)) parseJointDisplay(joint, view, mask, loadMatrices, callback, context);
            if (joint->flags & (mask << 28)) {
                for (HSD_JObj* child = joint->child; child; child = child->next) _modelParseJObjDispAll__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(child, view, mask, loadMatrices, callback, context);
            }
        }
    }
}
static void _modelParseSetupInstanceMtx__FP5GSmtxP9_HSD_JObjP5GSmtx(GSmtx* view, HSD_JObj* joint, GSmtx* out) {
    HSD_JObjSetupMatrix(joint); HSD_JObjSetupMatrix(joint->child);
    PSMTXInverse(joint->child->mtx, out->matrix);
    PSMTXConcat(joint->mtx, out->matrix, out->matrix);
    if (view) PSMTXConcat(view->matrix, out->matrix, out->matrix);
}
static void _modelParseJObjDisp__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_JObj* joint, GSmtx* view, s32 mask, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    if (joint && ((joint->flags & 0x4020) ? 0 : 1)) _modelParseJObjDispDObj__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(joint, view, mask, loadMatrices, callback, context);
}
// Compile this helper before DispSub is defined so its standalone body keeps
// the calls, while the deferred tree traversal can inline the other helpers.
#pragma defer_codegen off
static void _modelParseJObjDispDObj__FP9_HSD_JObjP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_JObj* joint, GSmtx* view, s32 mask, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    u32 flags = joint->flags;
    if (!(flags & 0x10)) {
        u32 transparency = flags & (mask << 18);
        if (transparency) {
            HSD_JObjSetupMatrix(joint);
            if (!view) view = parseIdentityMatrix();
            GSmtx position;
            HSD_JObjMakePositionMtx(joint, view->matrix, position.matrix);
            if (transparency & 0x40000) _modelParseJObjDispSub__FP9_HSD_JObjP5GSmtxP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(joint, view, &position, 1, loadMatrices, callback, context);
            if (transparency & 0x100000) _modelParseJObjDispSub__FP9_HSD_JObjP5GSmtxP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(joint, view, &position, 4, loadMatrices, callback, context);
            if (transparency & 0x80000) _modelParseJObjDispSub__FP9_HSD_JObjP5GSmtxP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(joint, view, &position, 2, loadMatrices, callback, context);
        }
    }
}
#pragma defer_codegen on
static void _modelParseJObjDispSub__FP9_HSD_JObjP5GSmtxP5GSmtx12HSD_TrspMaskbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_JObj* joint, GSmtx* view, GSmtx* position, s32 mask, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    HSD_JObjSetCurrent(joint);
    u32 objectMask=mask<<1;
    HSD_PObjClearMtxMark(0, 0);
    for (HSD_DObj* object = joint->u.dobj; object; object = object->next) {
        if (!(object->flags & 1) && (object->flags & objectMask)) {
            HSD_DObjSetCurrent(object);
            parseDisplayObject(object, view, position, loadMatrices, callback, context);
        }
    }
    HSD_DObjSetCurrent(0); HSD_JObjSetCurrent(0);
}
static inline void parseDisplayObject(HSD_DObj* object, GSmtx* view, GSmtx* position, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    HSD_JObj* rigidJoint;
    HSD_JObj* blendJoint;
    u8 updateCurrent;
    u8 updateOther;
    HSD_JObj* currentJoint;
    HSD_JObj* rigidMark; u32 rigidKind;
    HSD_JObj* blendMark; u32 blendKind;
    HSD_JObj* currentMark; u32 currentKind;
    for (HSD_PObj* polygon = object->pobj; polygon; polygon = polygon->next) {
        static GSmtx mtxStack[10];
        if (!(polygon->flags & 0x800)) {
            if (loadMatrices) {
                switch (polygon->flags & 0x3000) {
                case 0:
                    if (!polygon->u.jobj) {
                        currentJoint=HSD_JObjGetCurrent();
                        HSD_PObjGetMtxMark(0, &currentMark, &currentKind);
                        if (currentMark != currentJoint || currentKind != 1) { HSD_PObjSetMtxMark(0, currentJoint, 1); PSMTXCopy(position->matrix, mtxStack[0].matrix); }
                    } else {
                        updateCurrent=0;updateOther=updateCurrent;
                        blendJoint=HSD_JObjGetCurrent();
                        HSD_PObjGetMtxMark(0, &blendMark, &blendKind);
                        if (blendMark != blendJoint && blendKind != 1) updateCurrent = 1;
                        HSD_PObjSetMtxMark(0, blendJoint, 1);
                        HSD_PObjGetMtxMark(1, &blendMark, &blendKind);
                        if (blendMark != polygon->u.jobj && blendKind != 1) updateOther = 1;
                        HSD_PObjSetMtxMark(1, polygon->u.jobj, 1);
                        if (updateCurrent || updateOther) {
                            if (updateCurrent) PSMTXCopy(position->matrix, mtxStack[0].matrix);
                            if (updateOther) {
                                blendJoint=polygon->u.jobj;
                                HSD_JObjSetupMatrix(blendJoint);
                                GSmtx matrix;
                                PSMTXConcat(view->matrix, polygon->u.jobj->mtx, matrix.matrix); PSMTXCopy(matrix.matrix, mtxStack[1].matrix);
                            }
                        }
                    }
                    break;
                case 0x1000: {
                    rigidJoint=HSD_JObjGetCurrent();
                    HSD_PObjGetMtxMark(0, &rigidMark, &rigidKind);
                    if (rigidMark != rigidJoint || rigidKind != 1) { HSD_PObjSetMtxMark(0, rigidJoint, 1); PSMTXCopy(position->matrix, mtxStack[0].matrix); }
                    break;
                }
                case 0x2000: _modelParseLoadEnvelopeMatrix__FP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtx(polygon, view, position, mtxStack); break;
                }
            }
            if ((polygon->flags & 0x3000) == 0x1000) callback(polygon, view, position, 0, context);
            else if (callback) {if(loadMatrices)callback(polygon,view,position,mtxStack,context);else callback(polygon,view,position,0,context);}
        }
    }
}
#pragma dont_inline on
static void _modelParseDObjDisp__FP9_HSD_DObjP5GSmtxP5GSmtxbPFP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv_vPv(HSD_DObj* object, GSmtx* view, GSmtx* position, bool loadMatrices, GSmodelParseCallback callback, void* context) {
    parseDisplayObject(object,view,position,loadMatrices,callback,context);
}
#pragma dont_inline reset
static void _modelParseLoadEnvelopeMatrix__FP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtx(HSD_PObj* polygon, GSmtx* view, GSmtx*, GSmtx* matrices) {
    Mtx modelNode,weighted,temporary;
    GSmtx* output;HSD_SList* list;s32 i;f32(*modelMatrix)[4];
    HSD_JObj* current = HSD_JObjGetCurrent(); HSD_PObjClearMtxMark(0, 2);
    modelMatrix = _HSD_mkEnvelopeModelNodeMtx(current, modelNode);
    list = polygon->u.envelope_list;
    output=matrices;
    for (i = 0; i < 10 && list; ++i, list = list->next, ++output) {
        GSmodelEnvelope* envelope = (GSmodelEnvelope*)list->data;
        if (!envelope) __assert("parse.cpp", 108, "envelope");
        f32 (*matrix)[4];
        if (envelope->weight >= 1.0f) {
            HSD_JObjSetupMatrix(envelope->joint);
            if (modelMatrix) { PSMTXConcat(envelope->joint->mtx, (f32 (*)[4])envelope->joint->envelopemtx, weighted); matrix = weighted; }
            else matrix = envelope->joint->mtx;
        } else {
            weighted[0][0]=weighted[0][1]=weighted[0][2]=weighted[0][3]=weighted[1][0]=weighted[1][1]=weighted[1][2]=weighted[1][3]=weighted[2][0]=weighted[2][1]=weighted[2][2]=weighted[2][3]=0.0f;
            for (; envelope; envelope = envelope->next) {
                if (!envelope->joint) __assert("parse.cpp", 133, "envelope->jobj");
                HSD_JObj* joint = envelope->joint; HSD_JObjSetupMatrix(joint);
                if (!joint->mtx) __assert("parse.cpp", 136, "jp->mtx");
                if (!joint->envelopemtx) __assert("parse.cpp", 137, "jp->envelopemtx");
                PSMTXConcat(joint->mtx, (f32 (*)[4])joint->envelopemtx, temporary);
                HSD_MtxScaledAdd(temporary, weighted, weighted, envelope->weight);
            }
            matrix = weighted;
        }
        if (modelMatrix) PSMTXConcat(matrix, modelMatrix, weighted);
        PSMTXConcat(view->matrix, matrix, temporary); PSMTXCopy(temporary, output->matrix);
    }
}
}

#pragma auto_inline reset
