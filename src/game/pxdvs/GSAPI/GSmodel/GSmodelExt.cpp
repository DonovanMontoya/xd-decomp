#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>

struct GSgfxLayer;
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32);
void SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(GSgfxLayer*, GStexture*, bool, u8*);
GStexture* GetTextureCopy__10GSgfxLayerFv(GSgfxLayer*);
static u8 g_envmap_tex_ref_count;
}

extern "C" {
HSD_JObj* HSD_JObjRemove(HSD_JObj*);
HSD_JObj* HSD_JObjAlloc();
void HSD_JObjAddChild(HSD_JObj*, HSD_JObj*);
void HSD_JObjAddNext(HSD_JObj*, HSD_JObj*);
u32 HSD_JObjGetFlags(HSD_JObj*);
void HSD_JObjSetFlags(HSD_JObj*, u32);
u16 GSmodelGetPartCount(GSmodel*);
void modelUpdateCenterNull__FP8_GSmodel(GSmodel*);
void __assert(const char*, int, const char*);
}
static inline HSD_JObj* centerChild(HSD_JObj* joint) { return joint == 0 ? 0 : joint->child; }
static inline HSD_JObj* centerNext(HSD_JObj* joint) { return joint == 0 ? 0 : joint->next; }

extern "C" {
void GSboundGetMinMax(GSbound*, Vec*, Vec*, u8,u8,u8,u8);
void GSlerpGetLinearInterpolationVector(Vec*,const Vec*,const Vec*,f32);
void HSD_JObjSetMtxDirtySub(HSD_JObj*);
void HSD_JObjSetupMatrixSub(HSD_JObj*);
extern Vec unitScaleVector;
}
static inline u8 centerMtxIsDirty(HSD_JObj* joint) {
    if(!joint) __assert("jobj.h",605,"jobj");
    u32 flags;
    int result;
    result=0;
    flags=joint->flags;
    if(!(flags&0x800000) && (flags&0x40)) result=1;
    return result;
}
static inline void centerMtxDirty(HSD_JObj* joint) {
    if(joint && !centerMtxIsDirty(joint)) HSD_JObjSetMtxDirtySub(joint);
}
static inline void centerSetTranslate(HSD_JObj* joint,GSvec* value) {
    if(!joint) __assert("jobj.h",937,"jobj");
    if(!value) __assert("jobj.h",938,"translate");
    joint->translate.x=value->param1;
    joint->translate.y=value->param2;
    joint->translate.z=value->param3;
    if(!(joint->flags&0x2000000)) centerMtxDirty(joint);
}
static inline void centerSetRotationX(HSD_JObj* joint,f32 value) {
    if(!joint) __assert("jobj.h",676,"jobj");
    if(joint->flags&0x20000) __assert("jobj.h",677,"!(jobj->flags & JOBJ_USE_QUATERNION)");
    joint->rotate.x=value;
    if(!(joint->flags&0x2000000)) centerMtxDirty(joint);
}
static inline void centerSetRotationY(HSD_JObj* joint,f32 value) {
    if(!joint) __assert("jobj.h",696,"jobj");
    if(joint->flags&0x20000) __assert("jobj.h",697,"!(jobj->flags & JOBJ_USE_QUATERNION)");
    joint->rotate.y=value;
    if(!(joint->flags&0x2000000)) centerMtxDirty(joint);
}
static inline void centerSetRotationZ(HSD_JObj* joint,f32 value) {
    if(!joint) __assert("jobj.h",716,"jobj");
    if(joint->flags&0x20000) __assert("jobj.h",717,"!(jobj->flags & JOBJ_USE_QUATERNION)");
    joint->rotate.z=value;
    if(!(joint->flags&0x2000000)) centerMtxDirty(joint);
}
static inline void centerSetScale(HSD_JObj* joint,GSvec* value) {
    if(!joint) __assert("jobj.h",790,"jobj");
    if(!value) __assert("jobj.h",791,"scale");
    joint->scale.x=value->param1;
    joint->scale.y=value->param2;
    joint->scale.z=value->param3;
    if(!(joint->flags&0x2000000)) centerMtxDirty(joint);
}

static inline void centerGetTranslate(HSD_JObj* joint, GSvec* value) {
    if(!joint) __assert("jobj.h",996,"jobj");
    if(!value) __assert("jobj.h",997,"translate");
    value->param1=joint->translate.x;
    value->param2=joint->translate.y;
    value->param3=joint->translate.z;
}
static inline void centerGetScale(HSD_JObj* joint, GSvec* value) {
    if(!joint) __assert("jobj.h",849,"jobj");
    if(!value) __assert("jobj.h",850,"scale");
    value->param1=joint->scale.x;
    value->param2=joint->scale.y;
    value->param3=joint->scale.z;
}
static inline f32 centerGetRotationX(HSD_JObj* joint) {
    if(!joint) __assert("jobj.h",748,"jobj");
    return joint->rotate.x;
}
static inline f32 centerGetRotationY(HSD_JObj* joint) {
    if(!joint) __assert("jobj.h",762,"jobj");
    return joint->rotate.y;
}
static inline f32 centerGetRotationZ(HSD_JObj* joint) {
    if(!joint) __assert("jobj.h",776,"jobj");
    return joint->rotate.z;
}

extern "C" {
void GSmodelSetAnimIndex(GSmodel*,u32);
void GSmodelSetAnimType(GSmodel*,s32);
}



extern "C" void modelMaterialInit__FP10GSmaterial(GSmaterial* material) {
    if (material) {
        material->savedPE = (void*)0xfefefefe;
        material->extensions = 0;
        material->channels[0] = 0; material->channels[1] = 1; material->channels[2] = 2; material->channels[3] = 3;
        material->environmentTexture = 0; material->environment = 0; material->environmentImage = 0;
        material->savedImage = (GSimageDesc*)0xfefefefe;
    }
}

extern "C" void modelMaterialFree__FP10GSmaterial(GSmaterial* material) {
    GSmaterialResetPEdescr(material); GSmaterialResetTexture(material); GSmaterialDisableExtension(material, 0xffff);
}

extern "C" void GSmodelAddNull(GSmodel* model,GSvec* position,GSvec* rotation,GSvec* scale) {
    Vec scratch,oldPosition,oldScale;
    f32 x,y,z;
    HSD_JObj* joint;
    HSD_JObj* root=model->joint;
    if(!(model->flags&0x80)) {
        if((model->flags&0x20000)!=0x20000) {
            joint=HSD_JObjAlloc();
            if(joint) {
                centerGetTranslate(root,(GSvec*)&oldPosition);
                x=centerGetRotationX(root);
                y=centerGetRotationY(root);
                z=centerGetRotationZ(root);
                centerGetScale(root,(GSvec*)&oldScale);
                if(position) centerSetTranslate(root,position);
                else {
                    scratch.x=0.0f; scratch.y=0.0f; scratch.z=0.0f;
                    centerSetTranslate(root,(GSvec*)&scratch);
                }
                if(rotation) {
                    centerSetRotationX(root,rotation->param1);
                    centerSetRotationY(root,rotation->param2);
                    centerSetRotationZ(root,rotation->param3);
                } else {
                    centerSetRotationX(root,0.0f);
                    centerSetRotationY(root,0.0f);
                    centerSetRotationZ(root,0.0f);
                }
                if(scale) centerSetScale(root,scale);
                else {
                    scratch.x=1.0f; scratch.y=1.0f; scratch.z=1.0f;
                    centerSetScale(root,(GSvec*)&scratch);
                }
                if(root && centerMtxIsDirty(root)) HSD_JObjSetupMatrixSub(root);
                HSD_JObjAddChild(joint,model->joint);
                model->flags|=0x20000;
                model->joint=joint;
                HSD_JObjSetFlags(joint,HSD_JObjGetFlags(root));
                centerSetTranslate(joint,(GSvec*)&oldPosition);
                centerSetRotationX(joint,x);
                centerSetRotationY(joint,y);
                centerSetRotationZ(joint,z);
                centerSetScale(joint,(GSvec*)&oldScale);
                centerMtxDirty(root);
                if(root && centerMtxIsDirty(root)) HSD_JObjSetupMatrixSub(root);
                if(joint && centerMtxIsDirty(joint)) HSD_JObjSetupMatrixSub(joint);
                GSmodelSetAnimIndex(model,model->animationIndex);
                GSmodelSetAnimType(model,model->animationType);
                GSmodelStartAnimation(model);
            }
        } else {
            if(root==0) joint=0; else joint=root->child;
                if(position) centerSetTranslate(joint,position);
                else {
                    scratch.x=0.0f; scratch.y=0.0f; scratch.z=0.0f;
                    centerSetTranslate(joint,(GSvec*)&scratch);
                }
                if(rotation) {
                    centerSetRotationX(joint,rotation->param1);
                    centerSetRotationY(joint,rotation->param2);
                    centerSetRotationZ(joint,rotation->param3);
                } else {
                    centerSetRotationX(joint,0.0f);
                    centerSetRotationY(joint,0.0f);
                    centerSetRotationZ(joint,0.0f);
                }
                if(scale) centerSetScale(joint,scale);
                else {
                    scratch.x=1.0f; scratch.y=1.0f; scratch.z=1.0f;
                    centerSetScale(joint,(GSvec*)&scratch);
                }
                if(joint && centerMtxIsDirty(joint)) HSD_JObjSetupMatrixSub(joint);
            GSmodelSetAnimIndex(model,model->animationIndex);
            GSmodelSetAnimType(model,model->animationType);
            GSmodelStartAnimation(model);
        }
    }
}

extern "C" void GSmodelGetRootPosition(GSmodel* model, GSvec* out) {
    HSD_JObj* joint = model->joint;
    if ((model->flags & 0x20000) == 0x20000) {
        joint = joint->child;
        if (!joint) __assert("jobj.h", 996, "jobj");
        if (!out) __assert("jobj.h", 997, "translate");
        out->param1 = joint->translate.x; out->param2 = joint->translate.y; out->param3 = joint->translate.z;
    } else { out->param1 = 0.0f; out->param2 = 0.0f; out->param3 = 0.0f; }
}

extern "C" void GSmodelGetRootRotation(GSmodel* model, GSvec* out) {
    HSD_JObj* joint = model->joint;
    if ((model->flags & 0x20000) == 0x20000) {
        joint = joint->child;
        if (!joint) __assert("jobj.h", 748, "jobj");
        out->param1 = joint->rotate.x;
        if (!joint) __assert("jobj.h", 762, "jobj");
        out->param2 = joint->rotate.y;
        if (!joint) __assert("jobj.h", 776, "jobj");
        out->param3 = joint->rotate.z;
    } else { out->param1 = 0.0f; out->param2 = 0.0f; out->param3 = 0.0f; }
}

extern "C" void GSmodelGetRootScale(GSmodel* model, GSvec* out) {
    HSD_JObj* joint = model->joint;
    if ((model->flags & 0x20000) == 0x20000) {
        joint = joint->child;
        if (!joint) __assert("jobj.h", 849, "jobj");
        if (!out) __assert("jobj.h", 850, "scale");
        out->param1 = joint->scale.x; out->param2 = joint->scale.y; out->param3 = joint->scale.z;
    } else { out->param1 = 1.0f; out->param2 = 1.0f; out->param3 = 1.0f; }
}

extern "C" void GSmodelRemoveNull(GSmodel* model) {
    Vec translate,scale;
    f32 x,y,z;
    if((model->flags&0x20000)==0x20000) {
        HSD_JObj* child;
        HSD_JObj* root=model->joint;
        if(root==0) child=0; else child=root->child;
        centerGetTranslate(root,(GSvec*)&translate);
        x=centerGetRotationX(root);
        y=centerGetRotationY(root);
        z=centerGetRotationZ(root);
        centerGetScale(root,(GSvec*)&scale);
        centerSetTranslate(child,(GSvec*)&translate);
        centerSetRotationX(child,x);
        centerSetRotationY(child,y);
        centerSetRotationZ(child,z);
        centerSetScale(child,(GSvec*)&scale);
        root=HSD_JObjRemove(root);
        if(child && centerMtxIsDirty(child)) HSD_JObjSetupMatrixSub(child);
        model->flags&=~0x20000;
        model->joint=root;
    }
}

extern "C" u8 GSmodelIsRootNullAdded(GSmodel* model) { return (model->flags >> 17) & 1; }

extern "C" void modelUpdateCenterNull__FP8_GSmodel(GSmodel* model) {
    Vec center,minimum,maximum;
    GSbound* bound=(GSbound*)model->boundStorage;
    if((model->flags&0x10000)==0x10000) {
        HSD_JObj* root=model->joint;
        if((model->flags&0x20000)==0x20000) root=root->child;
        HSD_JObj* joint;
        if(root == 0) joint=0; else joint=root->child;
        while(centerNext(joint)) {
            if(joint == 0) joint=0; else joint=joint->next;
        }
        GSboundGetMinMax(bound,&minimum,&maximum,0,0,0,1);
        GSlerpGetLinearInterpolationVector(&center,&minimum,&maximum,0.5f);
        centerSetTranslate(joint,(GSvec*)&center);
        centerSetRotationX(joint,0.0f);
        centerSetRotationY(joint,0.0f);
        centerSetRotationZ(joint,0.0f);
        centerSetScale(joint,(GSvec*)&unitScaleVector);
        if(joint && centerMtxIsDirty(joint)) HSD_JObjSetupMatrixSub(joint);
    }
}

extern "C" u16 GSmodelCenterNull(GSmodel* model) {
    if ((model->flags & 0x10000) == 0x10000) return GSmodelGetPartCount(model) - 1;
    HSD_JObj* joint = HSD_JObjAlloc();
    if (!joint) return 0;
    HSD_JObj* root = model->joint;
    if ((model->flags & 0x20000) == 0x20000) root = root->child;
    HSD_JObj* child = centerChild(root);
    if (!child) HSD_JObjAddChild(root, joint);
    else {
        while(centerNext(child)) {
            if(child == 0) child=0; else child=child->next;
        }
        HSD_JObjAddNext(child, joint);
    }
    HSD_JObjSetFlags(joint, HSD_JObjGetFlags(root));
    model->flags |= 0x10000;
    modelUpdateCenterNull__FP8_GSmodel(model);
    return GSmodelGetPartCount(model) - 1;
}

extern "C" void modelRemoveCenterNull__FP8_GSmodel(GSmodel* model) {
    if ((model->flags & 0x10000) == 0x10000) {
        HSD_JObj* root = model->joint;
        if ((model->flags & 0x20000) == 0x20000) root = root->child;
        HSD_JObj* joint;
        if(root == 0) joint=0; else joint=root->child;
        while(centerNext(joint)) {
            if(joint == 0) joint=0; else joint=joint->next;
        }
        HSD_JObjRemove(joint);
        model->flags &= ~0x10000;
    }
}

extern "C" void GSmodelSetRenderFlags(GSmodel* model, u32 value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetFlags(material, value | GSmaterialGetFlags(material)); }
}

extern "C" void GSmodelResetRenderFlags(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialResetFlags(material);
}

extern "C" void GSmodelSetMaterialAlpha(GSmodel* model, f32 alpha) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) GSmaterialSetAlpha(material, (f32)material->alpha * alpha / 255.0f);
}

extern "C" void GSmodelInitMaterialAlpha(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) GSmaterialStoreAlpha(material);
}

extern "C" void GSmodelResetMaterialAlpha(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialResetAlpha(material);
}

extern "C" void GSmodelSetPEdescr(GSmodel* model, void* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetPEdescr(material, value); }
}

extern "C" void GSmodelResetPEdescr(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialResetPEdescr(material);
}

extern "C" void GSmodelEnableEnvMap(GSmodel* model, s32 source, s32 mode, f32 blend) {
    u32 i;
    u32 count;
    GSmaterial* material;
    GSgfxLayer* layer;
    GStexture* texture;
    if (!GSmodelIsEnvMapEnabled(model)) {
        layer = GSgfxLayerFindByID(0);
        if (layer) {
            ++g_envmap_tex_ref_count;
            SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(layer, (GStexture*)0xfefefefe, false, 0);
            texture = GetTextureCopy__10GSgfxLayerFv(layer);
            if (texture) {
                i = 0;
                count = model->materialCount;
                material = model->materials;
                for (; i < count; ++i, ++material) {
                    GSmaterialSetEnvMapParams(material, source, mode, blend, texture);
                    GSmaterialEnableExtension(material, 4);
                }
            }
        }
    }
}

extern "C" void GSmodelSetEnvMapBlendValue(GSmodel* model, f32 value) {
    if (GSmodelIsEnvMapEnabled(model)) {
        u32 i = 0;
        u32 count = model->materialCount;
        GSmaterial* material = model->materials;
        for (; i < count; ++i, ++material) GSmaterialSetEnvMapBlendValue(material, value);
    }
}

extern "C" void GSmodelDisableEnvMap(GSmodel* model) {
    if (GSmodelIsEnvMapEnabled(model)) {
        u32 i = 0;
        u32 count;
        GSmaterial* material;
        material = model->materials; count = model->materialCount;
        for (; i < count; ++i, ++material) GSmaterialDisableExtension(material, 4);
        GSgfxLayer* layer = GSgfxLayerFindByID(0);
        if (layer && --g_envmap_tex_ref_count == 0) SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(layer, 0, false, 0);
    }
}

extern "C" u8 GSmodelIsEnvMapEnabled(GSmodel* model) {
    if (!model->materialCount) return 0;
    GSmaterial* material = model->materials;
    if (!material) return 0;
    if (GSmaterialGetEnabledExtensions(material) & 4) return 1;
    return 0;
}

extern "C" void GSmodelEnableColorSwap(GSmodel* model, u8* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetColorChannels(material, value); GSmaterialEnableExtension(material, 2); }
}

extern "C" void GSmodelDisableColorSwap(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialDisableExtension(material, 2);
}

extern "C" void GSmodelEnableModulation(GSmodel* model, GXColor* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetModulate(material, value); GSmaterialEnableExtension(material, 1); }
}

extern "C" void GSmodelSetModulationColor(GSmodel* model, GXColor* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetModulate(material, value); }
}

extern "C" void GSmodelDisableModulation(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialDisableExtension(material, 1);
}

extern "C" void GSmodelGetModulationColor(GSmodel* model, GXColor* color) {
    if (GSmodelIsModulationEnabled(model)) GSmaterialGetModulate(model->materials, color);
    else { color->r = color->g = color->b = 127; color->a = 255; }
}

extern "C" u8 GSmodelIsModulationEnabled(GSmodel* model) {
    if (!model->materialCount) return 0;
    GSmaterial* material = model->materials;
    if (!material) return 0;
    if (GSmaterialGetEnabledExtensions(material) & 1) return 1;
    return 0;
}

extern "C" void GSmodelSetTextureChange(GSmodel* model, GStexture* value) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    count = model->materialCount;
    material = model->materials;
    for (; i < count; ++i, ++material) { GSmaterialSetTexture(material, value); }
}

extern "C" void GSmodelResetTextureChange(GSmodel* model) {
    u32 i = 0;
    u32 count;
    GSmaterial* material;
    material = model->materials;
    count = model->materialCount;
    for (; i < count; ++i, ++material) GSmaterialResetTexture(material);
}
