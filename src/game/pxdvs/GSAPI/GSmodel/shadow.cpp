#include <game/pxdvs/GSAPI/GSmodel/runtime.hpp>
#include <game/pxdvs/GSAPI/GSlight/GSlight.hpp>
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
#include <game/pxdvs/GSAPI/GSbound/GSbound.hpp>
#include <dolphin/mtx.h>
#include <game/maximum/GSAPI/baselib/cobj.h>
#include <game/pxdvs/app/menu/menuOffScreenPrivate.hpp>
struct HSD_Shadow { HSD_SList* objects; HSD_CObj* camera; HSD_TObj* texture; f32 scaleS,scaleT,transS,transT; s32 active;u8 intensity;void* userData; };
struct HSD_ViewingRect {HSD_Vec3 origin,up,right,eye,eyeNormal;f32 distance,top,bottom,left,rightEdge;s8 perspective:1,invalid:1;};
struct GSmodelShadowReceiver {
    GSmodel* model;
    GSlight* light;
    GSmodel* surfaces[16];
    u32 sizeMin, sizeMax;
    u8 active, reserved51;
    u16 token;
    HSD_Shadow* shadow;
};
extern "C" {
extern f32 __float_epsilon[];
static GSmodelShadowReceiver _modelShadowReceiveList[5];
static f32 _modelShadowMarukageDist = 350.0f, _modelShadowOffDist = 400.0f;
s32 modelShadowLayerID = -1;
static u8 _modelShadowIntensity;
static s32 _modelShadowXsize, _modelShadowYsize;
static f32 _modelShadowCutoffDist, _modelShadowBoundExpansion;
static u32 _modelShadowLayerUseCount, _modelShadowActiveCount;
static GStexture* _modelShadowMarukageTex;
static u8 _shadowCheckCameraHeight;
void GSgfxRenderWaitForDrawComplete__Fv();
void HSD_ShadowFreeTexture(HSD_Shadow*);
void HSD_ShadowSetActive(HSD_Shadow*, u8);
HSD_Shadow* HSD_ShadowAlloc();
void HSD_ShadowSetDebug(u8);
void* GSmemAlloc(u32);
void GSmemFree(void*);
void* memcpy(void*, const void*, unsigned long);
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(s32);
s32 Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(char*, u32, u32, u32, s32, bool, bool, bool, s32, s32);
void HSD_JObjWalkTree(HSD_JObj*, void (*)(HSD_JObj*, void**, s32), void**);
void GSmodelSetShadowToCameraHeightCheck(u8 enable) { _shadowCheckCameraHeight = enable; }
void GSmodelSetGroundPlane(GSmodel* model, f32 height, u8 enable) {
    modelRuntime(model)->groundPlane = height;
    if (enable) model->animationFlags |= 4;
    else model->animationFlags &= ~4;
}
void GSmodelSetMarukageTexture(GStexture* texture) { _modelShadowMarukageTex = texture; GStextureSetFilter(texture, 2, 2, 0); }
void GSmodelSetShadowDistLimits(f32 nearDistance, f32 farDistance) { _modelShadowMarukageDist = nearDistance; _modelShadowOffDist = farDistance; }
static inline u8 shadowHasTexture(HSD_Shadow* shadow) {
    if(!shadow)return 0;
    if(!shadow->texture)return 0;
    if(!shadow->texture->imagedesc)return 0;
    if(!*(void**)shadow->texture->imagedesc)return 0;
    return 1;
}
void GSmodelFreeAllShadowTextures() {
    for (u32 i = 0; i < 5; ++i) {
        GSmodelShadowReceiver* receiver = &_modelShadowReceiveList[i];
        if (shadowHasTexture(receiver->shadow)) { GSgfxRenderWaitForDrawComplete__Fv(); HSD_ShadowFreeTexture(receiver->shadow); }
        HSD_ShadowSetActive(receiver->shadow, 0); receiver->active = 0;
    }
}
void GSmodelSetShadowBoundExpansion(f32 value) { _modelShadowBoundExpansion = value; }
void GSmodelSetShadowCutoffDist(f32 value) { _modelShadowCutoffDist = value * value; }
void GSmodelSetShadowDebug(u8 enable) { HSD_ShadowSetDebug(enable & 0xff); }
void GSmodelSetShadowTextureSize(s32 width, s32 height) {
    if (width & 1) ++width;
    if (height & 1) ++height;
    if(width<2 || height<2)return;
    {
        if (width > 640) width = 640;
        if (height > 528) height = 528;
        _modelShadowXsize = width; _modelShadowYsize = height;
    }
}
void GSmodelSetShadowLight(GSmodel* model, GSlight* light) {
    if (light && !(light->object->flags & 3)) light = 0;
    modelRuntime(model)->shadowLight = light;
}
void GSmodelSetShadowSurface(GSmodel* model, s32 count, GSmodel** surfaces) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if(count < 0 || count > 8)return;
    {
        if (count == 0 || !surfaces) {
            if (runtime->shadowSurfaces) {
                GSmemFree(runtime->shadowSurfaces); runtime->shadowSurfaceCount = 0; runtime->shadowSurfaces = 0;
                if (--_modelShadowLayerUseCount == 0) { Remove__16GSgfxLayerConfigF12GSgfxLayerID(modelShadowLayerID); modelShadowLayerID = -1; }
            }
        } else {
            if (!runtime->shadowSurfaces) {
                runtime->shadowSurfaces = (GSmodel**)GSmemAlloc(0x20); runtime->shadowSurfaceCount = 0;
                if (!_modelShadowLayerUseCount) modelShadowLayerID = Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset("model shadow", 0, 0x40000, 4, 0, false, false, false, -1, 3);
                ++_modelShadowLayerUseCount;
            }
            runtime->shadowSurfaceCount = count;
            memcpy(runtime->shadowSurfaces, surfaces, runtime->shadowSurfaceCount * 4);
        }
    }
}
void GSmodelClearShadowFlags(GSmodel* model, u32 flags) {
    if (flags & 1) model->flags &= ~0x10000000;
    if (flags & 4) model->flags &= ~0x40000000;
}
void GSmodelSetShadowFlags(GSmodel* model, u32 flags) {
    if (flags & 1) model->flags |= 0x10000000;
    if (flags & 4) model->flags |= 0x40000000;
}
static inline bool _jointCanShadow(HSD_JObj* joint) {
    return !(joint->flags & 0x4020);
}
static inline u32 _modelShadowJointEnabled(HSD_JObj* j) { if (j->flags & 0x4020) return 0; return 1; }
static void _modelShadowSetShadowFlag__FP9_HSD_JObjPPvi(HSD_JObj* joint, void** context, s32) {
    bool on = context != 0;
    if (!_modelShadowJointEnabled(joint)) return;
    for (HSD_DObj* object = joint->u.dobj; object; object = object->next) {
        if (object->mobj) {
            if (on) object->mobj->rendermode |= 0x4000000;
            else object->mobj->rendermode &= ~0x4000000;
        }
    }
}
static inline u8 shadowHasReceiver(GSmodelShadowReceiver* receiver, GSmodel* model) {
    for (u32 i = 0; i < 5; ++i) if (receiver[i].model == model) return 1;
    return 0;
}
void modelShadowPrepare__FP8_GSmodelb(GSmodel* model, bool enable) {
    GSmodelShadowReceiver* receiver = _modelShadowReceiveList;
    if (shadowHasReceiver(receiver, model)) {
        HSD_JObj* joint = modelGetRenderJObj__FP8_GSmodel(model);
        if (!enable) HSD_JObjWalkTree(joint, _modelShadowSetShadowFlag__FP9_HSD_JObjPPvi, (void**)0);
        else HSD_JObjWalkTree(joint, _modelShadowSetShadowFlag__FP9_HSD_JObjPPvi, (void**)1);
        u8 flag = enable;
        for (u32 i = 0; i < 5; ++i, ++receiver) if (receiver->active && receiver->model == model) HSD_ShadowSetActive(receiver->shadow, flag);
    }
}
void modelShadowFreeModelList__FP8_GSmodel(GSmodel* model) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if (runtime->shadowSurfaces) {
        GSmemFree(runtime->shadowSurfaces); runtime->shadowSurfaceCount = 0; runtime->shadowSurfaces = 0;
        if (--_modelShadowLayerUseCount == 0) { Remove__16GSgfxLayerConfigF12GSgfxLayerID(modelShadowLayerID); modelShadowLayerID = -1; }
    }
}
void modelShadowInit__Fv() {
    _modelShadowIntensity = 128; _modelShadowXsize = 384; _modelShadowYsize = 384;
    _modelShadowCutoffDist = 0.0f; _modelShadowBoundExpansion = 0.0f;
    for (u32 i = 0; i < 5; ++i) {
        GSmodelShadowReceiver* receiver = &_modelShadowReceiveList[i];
        receiver->active = 0; receiver->shadow = HSD_ShadowAlloc(); HSD_ShadowSetActive(receiver->shadow, 0);
        receiver->model = 0; receiver->token = 0;
    }
}
double ceil(double);
static inline f32 shadowLargestExtent(const Vec& size) {
    f32 largest=size.x;
    if(size.y>largest)largest=size.y;
    if(size.z>largest)largest=size.z;
    return largest;
}
static GSmodelShadowReceiver* _modelShadowFindValidReceiveModel__FP8_GSmodelP8_GSmodelP7GSlightP7GSbound(GSmodel* model, GSmodel* surface, GSlight* light, GSbound* bound) {
    Vec surfacePos, otherPos, size;
    u32 i;
    for (i = 0; i < 5; ++i) {
        GSmodelShadowReceiver* receiver = &_modelShadowReceiveList[i];
        if (receiver->model == model && receiver->light == light) {
            if (bound) {
                GSboundGetSize(bound, &size, 1, 1);
                u32 extent;
                extent = (u32)(f32)ceil(shadowLargestExtent(size));
                if ((extent < receiver->sizeMin && extent < receiver->sizeMax / 3) ||
                    (extent > receiver->sizeMax && extent > receiver->sizeMin * 3)) continue;
            }
            if (_modelShadowCutoffDist > 0.0f) {
                u32 j;
                u8 ok = 1;
                GSboundGetWorldPosition((GSbound*)surface->boundStorage, &surfacePos);
                for (j = 0; j < 16; ++j) {
                    if (receiver->surfaces[j]) {
                        GSboundGetWorldPosition((GSbound*)receiver->surfaces[j]->boundStorage, &otherPos);
                        if (PSVECSquareDistance(&surfacePos, &otherPos) > _modelShadowCutoffDist) { ok = 0; j = 16; }
                    }
                }
                if (!ok) continue;
            }
            return receiver;
        }
    }
    return 0;
}
static u8 _modelShadowGetLightToGroundIntersect__FP8_GSmodelP5GSvec(GSmodel* model, GSvec* out) {
    Vec lightPos, boundPos, boundSize, scaled, lineDiff, lineDir, planeNormal, planePoint;
    Vec dir, diff, t2, t;
    GSlightGetPosition(modelRuntime(model)->shadowLight, (HSD_Vec3*)&lightPos);
    GSboundGetWorldPosition((GSbound*)model->boundStorage, &boundPos);
    GSboundGetSize((GSbound*)model->boundStorage, &boundSize, 1, 1);
    boundPos.y = 0.5f * boundSize.y + boundPos.y;
    { f32 y = model->position.param2; planePoint.x = 0.0f; planePoint.y = y; planePoint.z = 0.0f; }
    planeNormal.x = 0.0f; planeNormal.y = -1.0f; planeNormal.z = 0.0f;
    PSVECSubtract(&lightPos, &boundPos, &dir);
    lineDir.x = dir.x; lineDir.y = dir.y; lineDir.z = dir.z;
    PSVECSubtract(&boundPos, &planePoint, &diff);
    lineDiff.x = diff.x; lineDiff.y = diff.y; lineDiff.z = diff.z;
    f32 denom = PSVECDotProduct(&planeNormal, &lineDir);
    f32 numer = PSVECDotProduct(&planeNormal, &lineDiff);
    int result;
    f32 absDenom = denom > 0.0f ? denom : -denom;
    if (absDenom < __float_epsilon[0]) {
        if (numer == 0.0f) result = 2;
        else result = 1;
    } else {
        PSVECScale(&lineDir, &t, numer / denom);
        scaled.x = t.x; scaled.y = t.y; scaled.z = t.z;
        PSVECSubtract(&boundPos, &scaled, &t2);
        { Vec* o=(Vec*)out; f32 x=t2.x, y=t2.y, z=t2.z; result = 0; o->x = x; o->y = y; o->z = z; }
    }
    return result == 0;
}
}

#include <game/pxdvs/GSAPI/GScamera/GScamera.hpp>
extern "C" {
extern GSmodel* _modelTopPtr;
void GSgfxProjectSetupParameters();
void GSboundGetShadowVolume(GSbound*,GSbound*,Vec*,f32);
static u8 _modelShadowAddAsNewReceiver__FP8_GSmodelP8_GSmodelP7GSlightP7GSbound(GSmodel*,GSmodel*,GSlight*,GSbound*);
}
static inline s32 shadowFindSurface(GSmodelShadowReceiver* receiver,GSmodel* model) {
    s32 index;
    for(index=0;index<16;index++)if(receiver->surfaces[index]==model)return index;
    return -1;
}
static inline GSmodelShadowReceiver* shadowFindFreeReceiver(GSmodelShadowReceiver* receiver) {
    for(u32 i=0;i<5;i++,receiver++)if(!receiver->model)return receiver;
    return 0;
}
static inline u8 shadowAssignReceiver(GSmodel* surface,GSmodel* model,GSlight* light,GSbound* bound) {
    Vec size;
    if(!light)return 1;
    if((model->scale.param3+(model->scale.param1+model->scale.param2))/3.0f<0.01f)return 1;
    ++_modelShadowActiveCount;
    GSmodelShadowReceiver* receiver=_modelShadowFindValidReceiveModel__FP8_GSmodelP8_GSmodelP7GSlightP7GSbound(surface,model,light,bound);
    if(receiver) {
        s32 index;
        index=shadowFindSurface(receiver,model);
        if(index!=-1)return 1;
        index=shadowFindSurface(receiver,0);
        if(index==-1)return _modelShadowAddAsNewReceiver__FP8_GSmodelP8_GSmodelP7GSlightP7GSbound(surface,model,light,bound);
        if(index<0)return 0;
        receiver->surfaces[index]=model;
        GSboundGetSize(bound,&size,1,1);
        u32 extent=(u32)(f32)ceil(shadowLargestExtent(size));
        if(extent<receiver->sizeMin)receiver->sizeMin=extent;
        if(extent>receiver->sizeMax)receiver->sizeMax=extent;
        return 1;
    }
    return _modelShadowAddAsNewReceiver__FP8_GSmodelP8_GSmodelP7GSlightP7GSbound(surface,model,light,bound);
}
extern "C" void modelShadowUpdate__Fv() {
    GSbound shadowBound;
    Vec lightPosition,modelPosition;
    GSmodel* model;
    GSgfxProjectSetupParameters();
    for(s32 i=0;i<5;i++) {
        GSmodelShadowReceiver* receiver=&_modelShadowReceiveList[i];
        receiver->active=0;receiver->model=0;receiver->token=0;
        for(u32 j=0;j<16;j++)receiver->surfaces[j]=0;
    }
    _modelShadowActiveCount=0;
    for(model=_modelTopPtr;model;model=model->next) {
        GSmodelRuntime* runtime=modelRuntime(model);
        u32 surfaceCount=runtime->shadowSurfaceCount;
        if(surfaceCount) {
            model->flags&=~0x08000000;
            u32 flags=model->flags;
            if(flags&2) {
                u8 visible=0;
                if(flags&0x10000000) {
                    if(flags&0x04000000)visible=1;
                    else {
                        GSlightGetPosition(runtime->shadowLight,(HSD_Vec3*)&lightPosition);
                        f32 ground;
                        if(model->animationFlags&4) {GSmodelGetPosition(model,(GSvec*)&modelPosition);ground=modelPosition.y;}
                        else ground=runtime->groundPlane;
                        GSboundGetShadowVolume(&shadowBound,(GSbound*)model->boundStorage,&lightPosition,ground);
                        if(GSboundIsInViewFast(&shadowBound)) {
                            visible=1;modelApplyAnimation__FP8_GSmodel(model);modelUpdateAttachments__FP8_GSmodel(model);modelUpdateTransform__FP8_GSmodel(model);modelApplyPartAnimMixes__FP8_GSmodel(model);
                        }
                    }
                }
                if(visible) {
                    if(_shadowCheckCameraHeight==1) {
                        GScamera* camera=model->camera;
                        if(!camera)camera=GScameraGetActiveCamera();
                        f32 height;
                        if(camera==0){height=0.0f;}else{height=camera->position.y;}
                        if(height<20.0f+model->position.param2) {model->flags|=0x08000000;continue;}
                    }
                    f32 distance=GSmodelGetDistanceFromCamera(model);
                    if(distance<_modelShadowOffDist) {
                        if(_modelShadowMarukageTex && distance>=_modelShadowMarukageDist)model->flags|=0x08000000;
                        else {
                            u32 i=0;s32 offset=0;
                            for(;i<(u32)runtime->shadowSurfaceCount;i++,offset+=4) {
                                GSlight* light=runtime->shadowLight;
                                GSmodel* surface=*(GSmodel**)((u8*)runtime->shadowSurfaces+offset);
                                if(!shadowAssignReceiver(surface,model,light,(GSbound*)model->boundStorage))model->flags|=0x08000000;
                            }
                        }
                    }
                }
            }
        }
    }
}

extern "C" {
static u8 _modelShadowAddAsNewReceiver__FP8_GSmodelP8_GSmodelP7GSlightP7GSbound(GSmodel* surface,GSmodel* model,GSlight* light,GSbound* bound) {
    Vec newSize,existingSize;
    GSmodelShadowReceiver* list=_modelShadowReceiveList;
    GSmodelShadowReceiver* receiver=shadowFindFreeReceiver(list);
    if(!receiver) {
        receiver=_modelShadowFindValidReceiveModel__FP8_GSmodelP8_GSmodelP7GSlightP7GSbound(surface,model,light,0);
        if(receiver)for(s32 j=0;j<16;j++)if(receiver->surfaces[j] && (receiver->surfaces[j]->flags&0x40000000)) {receiver=0;break;}
        if(!receiver) {
            u32 index;
            GSmodel* candidate;
            u8 found;
            s32 j;
            found=0;
            for(index=0;index<5;index++,list++) {
                receiver=list;
                if(list->model==surface) {
                    found=1;
                    for(j=0;j<16;j++) {
                        candidate=list->surfaces[index];
                        if(candidate && (candidate->flags&0x40000000)) {found=0;break;}
                    }
                    if(found)break;
                }
            }
            if(!found)return 0;
        }
        s32 index;
        index=shadowFindSurface(receiver,model);
        if(index!=-1)return 1;
        index=shadowFindSurface(receiver,0);
        if(index<0)return 0;
        receiver->surfaces[index]=model;
        GSboundGetSize(bound,&existingSize,1,1);
        u32 extent=(u32)(f32)ceil(shadowLargestExtent(existingSize));
        if(extent<receiver->sizeMin)receiver->sizeMin=extent;
        if(extent>receiver->sizeMax)receiver->sizeMax=extent;
        return 1;
    }
    receiver->model=surface;receiver->light=light;
    GSboundGetSize(bound,&newSize,1,1);
    u32 extent=(u32)(f32)ceil(shadowLargestExtent(newSize));
    receiver->sizeMax=extent;receiver->sizeMin=extent;receiver->surfaces[0]=model;
    return 1;
}
}

extern "C" {
void GSgfxTokenWaitForClearAndReset(u16*);
void FlushState__10GSgfxLayerFv(GSgfxLayer*);
void InvalidateState__10GSgfxLayerFv(GSgfxLayer*);
u16 tokenMark__10GSgfxLayerFv(GSgfxLayer*);
void HSD_StateInvalidate(s32);
void HSD_ShadowAddObject(HSD_Shadow*,HSD_JObj*);
void HSD_ShadowDeleteObject(HSD_Shadow*,HSD_JObj*);
void HSD_ShadowCopyTex(HSD_Shadow*);
void HSD_ShadowRender(HSD_Shadow*);
void HSD_ShadowCopyLightPos(HSD_Shadow*,HSD_LObj*,f32);
void HSD_ShadowSetViewingRect(HSD_Shadow*,f32,f32,f32,f32);
void HSD_ShadowSetSize(HSD_Shadow*,u16,u16);
void HSD_ViewingRectInit(HSD_ViewingRect*,HSD_Vec3*,HSD_Vec3*,HSD_Vec3*,s32);
s32 HSD_ViewingRectCheck(HSD_ViewingRect*);
void HSD_ViewingRectAddRect(HSD_ViewingRect*,HSD_Vec3*,f32,f32,f32,f32);
void GSlogWrite(const char*,...);
void __assert(const char*,s32,const char*);
void GSboundGetShadowSize(Vec*,GSbound*,Vec*,Vec*,Vec*);
}
static inline void shadowSetClipping(GSgfxLayer* layer) {
    *(s32*)((u8*)layer+0xd90)=0;
    layer->cullDirty|=4;layer->dirty|=2;layer->savedCullDirty|=4;layer->savedDirty|=2;
}
static inline s32 shadowFloatClass(f32 value) {
    union {f32 value;u32 bits;} number;number.value=value;
    switch(number.bits&0x7f800000) {
    case 0x7f800000:
        if(number.bits&0x7fffff)return 1;
        return 2;
    case 0:
        if(number.bits&0x7fffff)return 5;
        return 3;
    default:return 4;
    }
}
extern "C" void modelShadowRender__FP10GSgfxLayer(GSgfxLayer* layer) {
    HSD_ViewingRect viewing;
    GSbound volume;
    Vec interest,eye,center,up,extent,size,position;
    GSmodelShadowReceiver* receiver=_modelShadowReceiveList;
    for(u32 i=0;i<5;i++) {
        GSmodelShadowReceiver* wait=&_modelShadowReceiveList[i];
        if(wait->model) {
            GSgfxTokenWaitForClearAndReset(&wait->token);
            GSmodel* model=wait->model;
            if(model)GSgfxTokenWaitForClearAndReset(&model->renderToken);
        }
    }
    if(_modelShadowActiveCount) {
        shadowSetClipping(layer);FlushState__10GSgfxLayerFv(layer);HSD_StateInvalidate(-1);
        for(u32 i=0;i<5;i++,receiver++) {
            GSmodel* model=receiver->model;
            if(!model) {
                if(shadowHasTexture(receiver->shadow)) {GSgfxRenderWaitForDrawComplete__Fv();HSD_ShadowFreeTexture(receiver->shadow);}
                receiver->active=0;
            }else if(model->flags&1) {
                u32 count=0;
                GSmodelShadowReceiver* current=receiver;
                interest.x=0;interest.y=0;interest.z=0;
                for(u32 j=0;j<16;j++) {
                    GSmodel* caster=current->surfaces[j];
                    if(caster && (caster->flags&1)) {
                        HSD_ShadowAddObject(receiver->shadow,modelGetRenderJObj__FP8_GSmodel(caster));
                        GSboundGetWorldPosition((GSbound*)caster->boundStorage,&center);
                        PSVECAdd(&interest,&center,&interest);count++;
                    }
                }
                if(count==0)receiver->active=0;
                else {
                    s32 type=receiver->light->object->flags&3;
                    switch(type) {
                    case 1:HSD_CObjSetProjectionType(receiver->shadow->camera,3);break;
                    case 2:case 3:HSD_CObjSetProjectionType(receiver->shadow->camera,2);break;
                    }
                    if((f32)count!=0.0f)PSVECScale(&interest,&interest,1.0f/count);
                    HSD_CObjSetInterest(receiver->shadow->camera,(HSD_Vec3*)&interest);
                    HSD_ShadowCopyLightPos(receiver->shadow,receiver->light->object,30.0f);
                    HSD_CObjSetNear(receiver->shadow->camera,0.1f);HSD_CObjSetFar(receiver->shadow->camera,3000.0f);
                    f32 distance=HSD_CObjGetEyeDistance(receiver->shadow->camera);
                    if(shadowFloatClass(distance)==1 || distance<0.1f)HSD_ShadowDeleteObject(receiver->shadow,0);
                    else {
                        HSD_CObjGetEyePosition(receiver->shadow->camera,(HSD_Vec3*)&eye);HSD_CObjGetUpVector(receiver->shadow->camera,(HSD_Vec3*)&up);
                        HSD_ViewingRectInit(&viewing,(HSD_Vec3*)&eye,(HSD_Vec3*)&interest,(HSD_Vec3*)&up,(receiver->light->object->flags&3)!=1);
                        for(HSD_SList* object=receiver->shadow->objects;object;object=object->next) {
                            GSmodel* caster=GSmodelSearchModelList((HSD_JObj*)object->data);
                            if(caster) {
                                GSboundGetWorldPosition((GSbound*)caster->boundStorage,&center);
                                if((u8)GSboundHasAnimData((GSbound*)caster->boundStorage)==0) {
                                    GSboundGetSize((GSbound*)caster->boundStorage,&size,1,1);
                                    f32 edge=_modelShadowBoundExpansion+(f32)(u32)(f32)ceil(shadowLargestExtent(size));
                                    if(edge>0.1f)HSD_ViewingRectAddRect(&viewing,(HSD_Vec3*)&center,-edge,-edge,edge,edge);
                                }else {
                                    f32 ground;
                                    if(caster->animationFlags&4) {GSmodelGetPosition(caster,(GSvec*)&position);ground=position.y;}
                                    else ground=modelRuntime(caster)->groundPlane;
                                    GSboundGetShadowVolume(&volume,(GSbound*)caster->boundStorage,&eye,ground);
                                    GSboundGetShadowSize(&extent,&volume,&eye,&interest,&up);PSVECScale(&extent,&extent,0.5f);
                                    HSD_ViewingRectAddRect(&viewing,(HSD_Vec3*)&center,extent.z,-extent.z,-extent.x,extent.x);
                                }
                            }
                        }
                        if(HSD_ViewingRectCheck(&viewing))HSD_ShadowSetViewingRect(receiver->shadow,viewing.top,viewing.bottom,viewing.left,viewing.rightEdge);
                        else {
                            f32 edge=(f32)receiver->sizeMax+_modelShadowBoundExpansion;
                            if(edge>0.1f)HSD_ShadowSetViewingRect(receiver->shadow,-edge,-edge,edge,edge);
                        }
                        HSD_Shadow* shadow=receiver->shadow;u8 intensity=255-_modelShadowIntensity;
                        if(!shadow)__assert("shadow.h",0x6c,"shadow");
                        shadow->intensity=intensity;
                        HSD_ShadowSetSize(receiver->shadow,_modelShadowXsize,_modelShadowYsize);
                        receiver->active=1;
                        if(!shadowHasTexture(receiver->shadow))GSlogWrite("*** GSmodel shadow texture memory unavailable, skipping rendering\n");
                        else {
                            shadowSetClipping(layer);FlushState__10GSgfxLayerFv(layer);HSD_ShadowRender(receiver->shadow);HSD_ShadowCopyTex(receiver->shadow);InvalidateState__10GSgfxLayerFv(layer);receiver->token=tokenMark__10GSgfxLayerFv(layer);
                        }
                        HSD_ShadowDeleteObject(receiver->shadow,0);
                    }
                }
            }
        }
        *(u32*)((u8*)layer+4)|=0x10000000;*(u32*)((u8*)layer+4)|=0x20000000;
    }
}

extern "C" GSgfxVF* GSgfxVFGetPredef(u32);
void GSprimSetup3DRender(GSgfxLayer*);
static inline void shadowPixelState(GSgfxLayer* layer,u32 bits) {
    layer->pixelDirty|=bits;layer->dirty|=0x40;layer->savedPixelDirty|=bits;layer->savedDirty|=0x40;
}
static inline void shadowDepthState(GSgfxLayer* layer,u8 enable,s32 compare) {
    *(u8*)&layer->depthEnable=enable;layer->depthCompare=compare;shadowPixelState(layer,8);
}
static inline void shadowAlphaState(GSgfxLayer* layer,s32 first,u8 ref0,s32 combine,s32 second,u8 ref1,u8 disabled) {
    layer->alphaCompare0=first;layer->alphaReference0=ref0;layer->alphaCombine=combine;layer->alphaCompare1=second;layer->alphaReference1=ref1;layer->alphaDisabled=disabled;shadowPixelState(layer,0x10);
}
static inline void shadowColorState(GSgfxLayer* layer,u8 color,u8 alpha,u8 before) {
    layer->colorUpdate=color;layer->alphaUpdate=alpha;layer->depthBeforeTexture=before;shadowPixelState(layer,4);
}
static inline void shadowVertexXYZ(f32 x,f32 y,f32 z,GXColor color,f32 s,f32 t) {
    *(f32*)0xcc008000=x;*(f32*)0xcc008000=y;*(f32*)0xcc008000=z;
    *(u32*)0xcc008000=*(const u32*)&color;
    *(f32*)0xcc008000=s;*(f32*)0xcc008000=t;
}
static inline void shadowVertex(Vec point,const GXColor& color,f32 s,f32 t) {
    shadowVertexXYZ(point.x,point.y,point.z,color,s,t);
}
extern "C" void modelShadowRenderMarukage__FP8_GSmodelP10GSgfxLayer(GSmodel* model,GSgfxLayer* layer) {
    Mtx rotation;
    Vec size,minimum,maximum;
    GXColor color;
    GSboundGetSize((GSbound*)model->boundStorage,&size,0,0);
    size.x*=0.5f;size.z*=0.5f;
    f32 radius=size.x;if(size.z<radius)radius=size.z;
    PSMTXRotRad(rotation,'Y',model->rotation.param2);PSMTXMultVec(rotation,&size,&size);
    size.x=size.x>0.0f?size.x:-size.x;size.z=size.z>0.0f?size.z:-size.z;
    if(size.x<radius)size.x=radius;if(size.z<radius)size.z=radius;
    GSboundGetWorldPosition((GSbound*)model->boundStorage,&minimum);
    maximum=minimum;
    minimum.x-=size.x;minimum.z-=size.z;maximum.x+=size.x;maximum.z+=size.z;
    maximum.y=minimum.y=0.2f+model->position.param2;
    color.r=color.g=color.b=color.a=_modelShadowIntensity-((s32)_modelShadowIntensity>>2);
    GSprimSetup3DRender(layer);
    if(layer->blendIndex!=1) {layer->blendIndex=1;layer->currentBlend=&layer->blendRecords[layer->blendIndex];}
    layer->blendMode=3;layer->blendSource=4;layer->blendDestination=5;layer->logicOperation=5;shadowPixelState(layer,1);
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(5));
    TextureRecord* texture=(TextureRecord*)_modelShadowMarukageTex;
    if(layer->textures[0]!=texture || layer->savedTextures[0]!=texture || texture->dirty) {
        layer->textures[0]=texture;layer->textureDirty|=1;layer->savedTextures[0]=texture;layer->savedTextureDirty|=1;
    }
    shadowDepthState(layer,1,3);
    shadowAlphaState(layer,7,0,0,7,0,1);
    shadowColorState(layer,1,0,0);
    layer->primitiveType=0x98;layer->beginSurface(4);
    shadowVertex(minimum,color,0,0);
    shadowVertexXYZ(minimum.x,minimum.y,maximum.z,color,0,1);
    shadowVertexXYZ(maximum.x,minimum.y,minimum.z,color,1,0);
    shadowVertex(maximum,color,1,1);
    layer->endSurface();
}

extern "C" GSgfxLayer* GSgfxLayerFindByID(u32);
static inline void shadowDebugVertex(Vec point,u8 r,u8 g,u8 b,u8 a) {
    *(f32*)0xcc008000=point.x;*(f32*)0xcc008000=point.y;*(f32*)0xcc008000=point.z;
    *(u8*)0xcc008000=r;*(u8*)0xcc008000=g;*(u8*)0xcc008000=b;*(u8*)0xcc008000=a;
}
static inline void shadowDebugCenter(GSmodel* model,Vec* center) {
    Vec size;
    GSboundGetSize((GSbound*)model->boundStorage,&size,1,1);
    center->y+=0.5f*size.y;
}
extern "C" void modelShadowRenderDebug__Fv() {
    Vec light,center,intersection;
    GSmodelShadowReceiver* receiver;
    u32 i,j;
    GSgfxLayer* layer;
    GSmodel* model;
    layer=GSgfxLayerFindByID(2);
    GSprimSetup3DRender(layer);
    if(layer->blendIndex!=0) {layer->blendIndex=0;layer->currentBlend=&layer->blendRecords[layer->blendIndex];}
    layer->blendMode=0;layer->blendSource=1;layer->blendDestination=1;layer->logicOperation=5;shadowPixelState(layer,1);
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
    i=0;
    shadowDepthState(layer,1,3);
    shadowAlphaState(layer,7,0,0,7,0,1);
    shadowColorState(layer,1,0,0);
    layer->primitiveType=0xa8;layer->lineWidth=9;layer->lineOffset=0;
    layer->lineDirty|=4;layer->dirty|=1;layer->savedLineDirty|=4;layer->savedDirty|=1;
    for(;i<5;i++) {
        receiver=&_modelShadowReceiveList[i];
        if(receiver->model && (receiver->model->flags&1)) {
            j=0;
            for(;j<16;j++) {
                model=receiver->surfaces[j];
                if(model && (model->flags&1)) {
                    GSlightGetPosition(modelRuntime(model)->shadowLight,(HSD_Vec3*)&light);
                    GSboundGetWorldPosition((GSbound*)model->boundStorage,&center);
                    shadowDebugCenter(model,&center);
                    _modelShadowGetLightToGroundIntersect__FP8_GSmodelP5GSvec(model,(GSvec*)&intersection);
                    layer->beginSurface(2);shadowDebugVertex(light,255,0,0,255);shadowDebugVertex(center,255,0,0,255);layer->endSurface();
                    layer->beginSurface(2);shadowDebugVertex(center,0,0,255,255);shadowDebugVertex(intersection,0,0,255,255);layer->endSurface();
                }
            }
        }
    }
}
