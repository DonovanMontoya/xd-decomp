#define DIST_FIELD(layer, type, offset) (*(type*)((u8*)(layer) + (offset)))
#include <game/pxdvs/GSAPI/GSmodel/runtime.hpp>
#include <game/pxdvs/GSAPI/GSpart/GSpart.hpp>
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
struct GSgfxLayer { u8 reserved00[0x28]; s32 identifier; };
struct GSmodelVertexDescriptor { s32 attribute, type, components, format; u8 fractionalBits, reserved11; u16 stride; void* data; };
struct DistortionMatrix { Mtx matrix; };
struct GSparticleGenerator;
extern "C" {
GSgfxLayer* GSgfxLayerFindByName(char*);
GSgfxLayer* GSgfxLayerFindByID(s32);
void SetLayerVisibility__10GSgfxLayerFb(GSgfxLayer*, bool);
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(s32);
s32 Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(char*, u32, u32, u32, s32, bool, bool, bool, s32, s32);
void* GSmemAllocClr(u32);
void GSmemFree(void*);
void* __nw__FUl(u32);
void __dl__FPv(void*);
void GSgfxVFInit(GSgfxVF*);
void GSgfxVFCreate(GSgfxVF*);
void GSgfxVFFree(GSgfxVF*);
void GSgfxVFSetElement(GSgfxVF*, s32, s32, s32, u8);
void GSgfxVFSetArray(GSgfxVF*, s32, s32, void*, u8, u8);
GSpart* GSmodelGetPart(GSmodel*, u32);
GSparticleGenerator* GSparticleCreateGenerator(GSparticleBank*, s32, s32);
void GSparticleSetGeneratorPosition(GSparticleGenerator*, Vec*);
void GSparticleSetGeneratorRotation(GSparticleGenerator*, Vec*);
void GSparticleSetGeneratorScale(GSparticleGenerator*, Vec*, void*, void*);
s32 GScameraGetActiveCamera();
void GScameraGetPerspective(s32, f32*, f32*, f32*, f32*);
void GScameraGetPosition(s32, Vec*);
void GScameraLoadActiveCameraMatrix(s32);
s32 GSgfxPerfbarCPUEntry(s32);
void GSgfxVideoGetEFBSize(u16*, u16*);
GStexture* GetFBTexture__10GSgfxLayerFv();
u8 IsLayerVisible__10GSgfxLayerFv(GSgfxLayer*);
void tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(GSgfxLayer*, u8, s32);
void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(GSgfxLayer*, u8, s32, s32, void*, bool, void*);
void _modelDrawDistortionSub__FP8_GSmodelP10GSgfxLayerP5GSmtxP5GSvec(GSmodel*, GSgfxLayer*, Mtx, Vec*);
void* memset(void*, int, unsigned long);
void pushMult__16GSgfxMatrixStackFP5GSmtx(void*, Mtx);
void pop__16GSgfxMatrixStackFv(void*);
void tunitIndTexMtx__10GSgfxLayerF16GSgfxIndTexMtxIDPA3_fSc(GSgfxLayer*, s32, f32 (*)[3], s8);
void dlDrawExt__10GSgfxLayerFPUcUl(GSgfxLayer*, void*, u32);
char g_distortion_layer_name[] = "model distortion";
static u8 g_distortion_layer_ref_count;
void GSmodelFreeDistortion(GSmodel* model);
void GSmodelCreateDistortion(GSmodel* model, u16 partIndex, u8 materialIndex, u8 strength);
void GSmodelEnableDistortion(GSmodel* model);
void modelDustUpdate__FP8_GSmodel(GSmodel* model);
void modelDistortionRender__Fv(void);
void _modelDrawDistortionSub__FP8_GSmodelP10GSgfxLayerP5GSmtxP5GSvec(GSmodel* model, GSgfxLayer* layer, Mtx projection, Vec* cameraPosition);

void modelDustUpdate__FP8_GSmodel(GSmodel* model) {
    GSmodelRuntime* runtime;
    GSmodelDustPart* dust;
    GSpart* part;
    GSparticleGenerator* generator;
    s32 i;
    runtime = modelRuntime(model);
    if (runtime->dustBank) {
        GSvec modelPosition;
        Vec position;
        GSvec rotation;
        Vec scale;
        GSmodelGetPosition(model, &modelPosition); GSmodelGetRotation(model, &rotation);
        scale.x = runtime->dustScale; scale.y = runtime->dustScale; scale.z = runtime->dustScale;
        dust = runtime->dustParts;
        for (i = 0; i < 2; ++i, ++dust) {
            if (dust->enabled) {
                part = GSmodelGetPart(model, dust->trackingPart);
                if (part) {
                    GSpartGetTransform(part, &position, 0, 0); GSpartFree(part);
                    f32 height = position.y - modelPosition.param2;
                    if (height < dust->height - 0.00001f) dust->falling = 1;
                    else if (dust->falling) {
                        dust->falling = 0;
                        generator = GSparticleCreateGenerator(runtime->dustBank, 0, 0);
                        if (generator) {
                            part = GSmodelGetPart(model, dust->emissionPart);
                            if (!part) continue;
                            GSpartGetTransform(part, &position, 0, 0); GSpartFree(part);
                            GSparticleSetGeneratorPosition(generator, &position); GSparticleSetGeneratorRotation(generator, (Vec*)&rotation);
                            GSparticleSetGeneratorScale(generator, &scale, 0, 0);
                        }
                    }
                    dust->height = height;
                }
            }
        }
    }
}
void GSmodelEnableDistortion(GSmodel* model) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if ((model->flags & 0x80000) != 0x80000 && runtime->distortionPolygon && runtime->distortionTexture) {
        GSgfxLayer* layer = GSgfxLayerFindByName(g_distortion_layer_name);
        if (layer) { SetLayerVisibility__10GSgfxLayerFb(layer, true); model->flags |= 0x80000; }
    }
}
void GSmodelCreateDistortion(GSmodel* model, u16 partIndex, u8 materialIndex, u8 strength) {
    GSmodelRuntime* runtime = modelRuntime(model);
    GSgfxLayer* layer;
    if (!runtime->distortionTexture && partIndex) {
        GSpart* part = GSmodelGetPart(model, partIndex);
        if (part) {
            GSmaterial* material;
            HSD_JObj* joint;
            joint = part->joint;
            material = GSpartGetMaterial(part, materialIndex);
            GSpartFree(part);
            if (material && ((u32)__cntlzw(joint->flags & 0x4020) >> 5)) {
                HSD_DObj* object = joint->u.dobj;
                if (object) {
                    HSD_PObj* polygon = object->pobj;
                    if (polygon && polygon->verts && polygon->n_display && polygon->display && (polygon->flags & 0x3000) != 0x1000) {
                        runtime->distortionPart = partIndex; runtime->distortionMaterial = materialIndex; runtime->distortionPolygon = polygon;
                        runtime->distortionTexture = (GStexture*)GSmemAllocClr(0x80);
                        if (runtime->distortionTexture) {
                            if (!strength) strength = 1;
                            runtime->distortionStrength = strength;
                            GSmaterialGetTexture(material, runtime->distortionTexture);
                            GStextureSetWrap(runtime->distortionTexture, 0, 0); GStextureSetFilter(runtime->distortionTexture, 2, 2, 0);
                            layer = GSgfxLayerFindByName(g_distortion_layer_name);
                            if (!layer) {
                                s32 id = Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(g_distortion_layer_name, 0, 0x1400, 2, 4, false, false, false, 2, 2);
                                layer = GSgfxLayerFindByID(id);
                                if (layer) SetLayerVisibility__10GSgfxLayerFb(layer, false);
                            }
                            ++g_distortion_layer_ref_count;
                            if (!layer) { GStextureFree(runtime->distortionTexture); runtime->distortionTexture = 0; runtime->distortionPolygon = 0; }
                            runtime->distortionVertexFormat = (GSgfxVF*)__nw__FUl(0x440);
                            if (runtime->distortionVertexFormat) {
                                GSgfxVFInit(runtime->distortionVertexFormat); GSgfxVFCreate(runtime->distortionVertexFormat);
                                GSmodelVertexDescriptor* desc = (GSmodelVertexDescriptor*)polygon->verts;
                                s32 attribute;
                                while ((attribute = desc->attribute) != 255) {
                                    if (attribute >= 9 || attribute < 0) GSgfxVFSetElement(runtime->distortionVertexFormat, attribute, desc->components, desc->format, desc->fractionalBits);
                                    if (desc->type != 1) GSgfxVFSetArray(runtime->distortionVertexFormat, desc->attribute, desc->type, desc->data, (u8)desc->stride, 0);
                                    ++desc;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void GSmodelFreeDistortion(GSmodel* model) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if ((model->flags & 0x80000) == 0x80000) {
        model->flags &= ~0x80000;
        GSgfxLayer* layer = GSgfxLayerFindByName(g_distortion_layer_name);
        if (layer) SetLayerVisibility__10GSgfxLayerFb(layer, false);
    }
    runtime->distortionPart = 0; runtime->distortionMaterial = 0; runtime->distortionPolygon = 0;
    if (runtime->distortionTexture) {
        GSmemFree(runtime->distortionTexture); runtime->distortionTexture = 0;
        if (g_distortion_layer_ref_count && --g_distortion_layer_ref_count == 0) {
            GSgfxLayer* layer = GSgfxLayerFindByName(g_distortion_layer_name);
            if (layer) Remove__16GSgfxLayerConfigF12GSgfxLayerID(layer->identifier);
        }
    }
    if (runtime->distortionVertexFormat) {
        GSgfxVFFree(runtime->distortionVertexFormat); __dl__FPv(runtime->distortionVertexFormat); runtime->distortionVertexFormat = 0;
    }
}
}

// The render-state cache retains independent dirty masks for both contexts.
extern "C" {
extern GSmodel* _modelTopPtr;
void _modelDrawDistortionSub__FP8_GSmodelP10GSgfxLayerP5GSmtxP5GSvec(GSmodel* model, GSgfxLayer* layer, Mtx projection, Vec* cameraPosition) {
    DistortionMatrix modelMatrix;
    DistortionMatrix textureMatrix;
    DistortionMatrix combined;
    f32 indirect[2][3];
    Vec position;
    GSmodelRuntime* runtime = modelRuntime(model);
    if ((model->flags & 0x80000) == 0x80000 && runtime->distortionVertexFormat) {
        HSD_PObj* polygon = runtime->distortionPolygon;
        if (polygon) {
            GSpart* part = GSmodelGetPart(model, runtime->distortionPart);
            if (part) {
                GSpartGetMatrix(part, modelMatrix.matrix);
                position.x = modelMatrix.matrix[0][3];
                position.y = modelMatrix.matrix[1][3];
                position.z = modelMatrix.matrix[2][3];
                GSpartFree(part);
                f32 distance = PSVECDistance(&position, cameraPosition);
                if (distance < 1.0f) distance = 1.0f;
                f32 strength = 1.0f / distance;
                memset(indirect, 0, sizeof(indirect));
                if (runtime->distortionStrength & 1) {
                    if (runtime->distortionStrength & 4) indirect[0][1] = -0.5f * strength;
                    else indirect[0][1] = 0.5f * strength;
                }
                if (runtime->distortionStrength & 2) {
                    if (runtime->distortionStrength & 8) indirect[1][2] = -0.5f * strength;
                    else indirect[1][2] = 0.5f * strength;
                }
                GStexture* texture = runtime->distortionTexture;
                if (DIST_FIELD(layer, GStexture*, 0x1740) != texture || DIST_FIELD(layer, GStexture*, 0x17F8) != texture || DIST_FIELD(texture, u8, 7)) {
                    DIST_FIELD(layer, GStexture*, 0x1740) = texture;
                    DIST_FIELD(layer, u32, 0x173C) |= 1;
                    DIST_FIELD(layer, GStexture*, 0x17F8) = texture;
                    DIST_FIELD(layer, u32, 0x17F4) |= 1;
                }
                pushMult__16GSgfxMatrixStackFP5GSmtx(DIST_FIELD(layer, void*, 0x19A0), modelMatrix.matrix);
                void* stack = DIST_FIELD(layer, void*, 0x19A0);
                PSMTXConcat(projection, (f32(*)[4])((u8*)DIST_FIELD(stack, void*, 4) + 4), combined.matrix);
                textureMatrix = combined;
                PSMTXCopy(textureMatrix.matrix, modelMatrix.matrix);
                tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(layer, 1, 0, 0, modelMatrix.matrix, false, 0);
                tunitIndTexMtx__10GSgfxLayerF16GSgfxIndTexMtxIDPA3_fSc(layer, 1, indirect, 1);
                DIST_FIELD(layer, GSgfxVF*, 0x199C) = runtime->distortionVertexFormat;
                dlDrawExt__10GSgfxLayerFPUcUl(layer, polygon->display, polygon->n_display * 32);
                pop__16GSgfxMatrixStackFv(DIST_FIELD(layer, void*, 0x19A0));
            }
        }
    }
}

}


extern "C" {
#pragma opt_common_subs off
#pragma opt_propagation off
void modelDistortionRender__Fv(void) {
    Mtx sp20;
    Vec sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    s32 temp_cr0_eq;
    GSgfxLayer *temp_r29;
    s32 temp_r3;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    u8 temp_r31;
    u8 temp_r4;
    s32 temp_r27;
    GStexture *temp_r3_2;
    GSmodel *var_r28;
    GSmodel *var_r4;
    u8 var_r5;

    temp_r29 = GSgfxLayerFindByName(g_distortion_layer_name);
    temp_r3 = GScameraGetActiveCamera();
    if ((temp_r3 != 0) && (temp_r29 != NULL) && (IsLayerVisible__10GSgfxLayerFv(temp_r29) != 0)) {
        temp_r3_2 = GetFBTexture__10GSgfxLayerFv();
        if (temp_r3_2 != NULL) {
            var_r4 = _modelTopPtr;
            var_r5 = 0;
            while (var_r4 != NULL) {
                temp_r3_3 = var_r4->flags;
                if ((temp_r3_3 & 0x04000000) && ((u32)((temp_r3_3 & 0x80000) + 0xFFF80000) == 0U)) {
                    var_r5 = 1;
                    break;
                }
                var_r4 = var_r4->next;
            }
            if (var_r5 != 0) {
                temp_r27 = GSgfxPerfbarCPUEntry(0x8080FF);
                temp_r4 = DIST_FIELD(temp_r29, u8, 0x16A7);
                DIST_FIELD(temp_r29, u8, 0x16A7) = 0U;
                temp_r31 = temp_r4 != 0;
                DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x40);
                GScameraLoadActiveCameraMatrix(DIST_FIELD(temp_r29, s32, 0x28));
                GScameraGetPerspective(temp_r3, &sp10, &spC, &sp8, &sp8);
                GScameraGetPosition(temp_r3, &sp14);
                C_MTXLightPerspective(sp20, sp10, spC, 0.5f, -0.5f, 0.5f, 0.5f);
                DIST_FIELD(temp_r29, s32, 0xD8C) = 0;
                DIST_FIELD(temp_r29, s32, 0x16B8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16B8) | 2);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 2);
                DIST_FIELD(temp_r29, s32, 0x1770) = (s32) (DIST_FIELD(temp_r29, s32, 0x1770) | 2);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 2);
                DIST_FIELD(temp_r29, s32, 0xD90) = 0;
                DIST_FIELD(temp_r29, s32, 0x16B8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16B8) | 4);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 2);
                DIST_FIELD(temp_r29, s32, 0x1770) = (s32) (DIST_FIELD(temp_r29, s32, 0x1770) | 4);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 2);
                DIST_FIELD(temp_r29, u8, 0xD88) = 0;
                DIST_FIELD(temp_r29, s32, 0x16B8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16B8) | 8);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 2);
                DIST_FIELD(temp_r29, s32, 0x1770) = (s32) (DIST_FIELD(temp_r29, s32, 0x1770) | 8);
                temp_r5 = DIST_FIELD(temp_r29, s32, 0x1760) | 2;
                DIST_FIELD(temp_r29, s32, 0x1760) = temp_r5;
                DIST_FIELD(temp_r29, u16, 0xD70) = 0;
                DIST_FIELD(temp_r29, u16, 0xD72) = 0;
                GSgfxVideoGetEFBSize((u16*)((u8*)temp_r29 + 0xD74), (u16*)((u8*)temp_r29 + 0xD76));
                DIST_FIELD(temp_r29, s32, 0x16B8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16B8) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 2);
                DIST_FIELD(temp_r29, s32, 0x1770) = (s32) (DIST_FIELD(temp_r29, s32, 0x1770) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 2);
                DIST_FIELD(temp_r29, u8, 0x1656) = 1;
                DIST_FIELD(temp_r29, u8, 0x1657) = 0;
                DIST_FIELD(temp_r29, u8, 0x1658) = 0;
                DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 4);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 4);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x40);
                DIST_FIELD(temp_r29, u8, 0x165C) = 1;
                DIST_FIELD(temp_r29, s32, 0x1660) = 3;
                DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 8);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 8);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x1664) = 7;
                DIST_FIELD(temp_r29, u8, 0x1670) = 0;
                DIST_FIELD(temp_r29, s32, 0x1668) = 0;
                DIST_FIELD(temp_r29, s32, 0x166C) = 7;
                DIST_FIELD(temp_r29, u8, 0x1671) = 0;
                DIST_FIELD(temp_r29, u8, 0x1672) = 1;
                DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 0x10);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 0x10);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x40);
                DIST_FIELD(temp_r29, u8, 0x1654) = 0;
                DIST_FIELD(temp_r29, u8, 0x1655) = 0xFF;
                DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 2);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 2);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x40);
                DIST_FIELD(temp_r29, u8, 0x1674) = 1;
                DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 0x20);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 0x20);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x40);
                if ((s32) DIST_FIELD(temp_r29, s32, 0x1994) != 1) {
                    DIST_FIELD(temp_r29, s32, 0x1994) = 1;
                    s32 offset = DIST_FIELD(temp_r29, s32, 0x1994) * 0xBC;
                    s32 stateOffset = offset + 0x1818;
                    DIST_FIELD(temp_r29, void*, 0x1990) = (u8*)temp_r29 + stateOffset;
                }
                DIST_FIELD(temp_r29, s32, 0x1644) = 1;
                DIST_FIELD(temp_r29, s32, 0x1648) = 1;
                DIST_FIELD(temp_r29, s32, 0x164C) = 0;
                DIST_FIELD(temp_r29, s32, 0x1650) = 5;
                DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x40);
                DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x40);
                DIST_FIELD(temp_r29, u8, 0xEAC) = 1;
                DIST_FIELD(temp_r29, s32, 0x16CC) = (s32) (DIST_FIELD(temp_r29, s32, 0x16CC) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 8);
                DIST_FIELD(temp_r29, s32, 0x1784) = (s32) (DIST_FIELD(temp_r29, s32, 0x1784) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 8);
                DIST_FIELD(temp_r29, u8, 0x14B0) = 1;
                DIST_FIELD(temp_r29, s32, 0x16EC) = (s32) (DIST_FIELD(temp_r29, s32, 0x16EC) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x80);
                DIST_FIELD(temp_r29, s32, 0x17A4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17A4) | 1);
                temp_r7 = DIST_FIELD(temp_r29, s32, 0x1760) | 0x80;
                DIST_FIELD(temp_r29, s32, 0x1760) = temp_r7;
                DIST_FIELD(temp_r29, u8, 0xC70) = 2;
                DIST_FIELD(temp_r29, s32, 0x16AC) = (s32) (DIST_FIELD(temp_r29, s32, 0x16AC) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 1);
                DIST_FIELD(temp_r29, s32, 0x1764) = (s32) (DIST_FIELD(temp_r29, s32, 0x1764) | 1);
                temp_r6 = DIST_FIELD(temp_r29, s32, 0x1760) | 1;
                DIST_FIELD(temp_r29, s32, 0x1760) = temp_r6;
                DIST_FIELD(temp_r29, u8, 0xDB8) = 0;
                DIST_FIELD(temp_r29, s32, 0x16BC) = (s32) (DIST_FIELD(temp_r29, s32, 0x16BC) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 4);
                DIST_FIELD(temp_r29, s32, 0x1774) = (s32) (DIST_FIELD(temp_r29, s32, 0x1774) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 4);
                tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(temp_r29, 0, 3);
                DIST_FIELD(temp_r29, s32, 0xEB0) = 1;
                DIST_FIELD(temp_r29, s32, 0xEB4) = 1;
                DIST_FIELD(temp_r29, s32, 0xEB8) = 0xFF;
                DIST_FIELD(temp_r29, s32, 0x16D0) = (s32) (DIST_FIELD(temp_r29, s32, 0x16D0) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 8);
                DIST_FIELD(temp_r29, s32, 0x1788) = (s32) (DIST_FIELD(temp_r29, s32, 0x1788) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 8);
                if (((void *) DIST_FIELD(temp_r29, GStexture*, 0x1744) != temp_r3_2) || ((void *) DIST_FIELD(temp_r29, GStexture*, 0x17FC) != temp_r3_2) || ((u8) temp_r3_2->dirty != 0)) {
                    DIST_FIELD(temp_r29, GStexture*, 0x1744) = temp_r3_2;
                    DIST_FIELD(temp_r29, s32, 0x173C) = (s32) (DIST_FIELD(temp_r29, s32, 0x173C) | 2);
                    DIST_FIELD(temp_r29, GStexture*, 0x17FC) = temp_r3_2;
                    DIST_FIELD(temp_r29, s32, 0x17F4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17F4) | 2);
                }
                DIST_FIELD(temp_r29, s32, 0x14B4) = 0;
                DIST_FIELD(temp_r29, s32, 0x14B8) = 0;
                DIST_FIELD(temp_r29, s32, 0x16F0) = (s32) (DIST_FIELD(temp_r29, s32, 0x16F0) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x80);
                DIST_FIELD(temp_r29, s32, 0x17A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x17A8) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x80);
                DIST_FIELD(temp_r29, s32, 0x14D4) = 0;
                DIST_FIELD(temp_r29, s32, 0x14D8) = 0;
                DIST_FIELD(temp_r29, s32, 0x16F4) = (s32) (DIST_FIELD(temp_r29, s32, 0x16F4) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x80);
                DIST_FIELD(temp_r29, s32, 0x17AC) = (s32) (DIST_FIELD(temp_r29, s32, 0x17AC) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x80);
                DIST_FIELD(temp_r29, s32, 0x1420) = 2;
                DIST_FIELD(temp_r29, u8, 0x1424) = 0;
                DIST_FIELD(temp_r29, u8, 0x1425) = 1;
                DIST_FIELD(temp_r29, u8, 0x1426) = 0;
                DIST_FIELD(temp_r29, s32, 0x1428) = 1;
                DIST_FIELD(temp_r29, s32, 0x16E8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16E8) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 8);
                DIST_FIELD(temp_r29, s32, 0x17A0) = (s32) (DIST_FIELD(temp_r29, s32, 0x17A0) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 8);
                tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(temp_r29, 0, 1, 4, 0, false, 0);
                DIST_FIELD(temp_r29, u8, 0xD44) = 0;
                DIST_FIELD(temp_r29, u8, 0xD45) = 0;
                DIST_FIELD(temp_r29, s32, 0x16B4) = (s32) (DIST_FIELD(temp_r29, s32, 0x16B4) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 1);
                DIST_FIELD(temp_r29, s32, 0x176C) = (s32) (DIST_FIELD(temp_r29, s32, 0x176C) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 1);
                var_r28 = _modelTopPtr;
                while (var_r28 != NULL) {
                    temp_r3_4 = var_r28->flags;
                    if ((temp_r3_4 & 0x04000000) && ((u32)((temp_r3_4 & 0x80000) + 0xFFF80000) == 0U)) {
                        _modelDrawDistortionSub__FP8_GSmodelP10GSgfxLayerP5GSmtxP5GSvec(var_r28, temp_r29, sp20, &sp14);
                    }
                    var_r28 = var_r28->next;
                }

                DIST_FIELD(temp_r29, s32, 0x1420) = 0;
                DIST_FIELD(temp_r29, s32, 0x16E8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16E8) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 8);
                DIST_FIELD(temp_r29, s32, 0x17A0) = (s32) (DIST_FIELD(temp_r29, s32, 0x17A0) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 8);
                DIST_FIELD(temp_r29, u8, 0x14B0) = 0;
                DIST_FIELD(temp_r29, s32, 0x16EC) = (s32) (DIST_FIELD(temp_r29, s32, 0x16EC) | 1);
                DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x80);
                DIST_FIELD(temp_r29, s32, 0x17A4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17A4) | 1);
                DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x80);
                if (temp_r31 != 0) {
                    DIST_FIELD(temp_r29, u8, 0x16A7) = temp_r31;
                    DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 0x40);
                    DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 0x40);
                    if (temp_r31 != 0) {
                        DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 0x200);
                        DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 0x200);
                        if ((u8) DIST_FIELD(temp_r29, u8, 0x16A6) != 0) {
                            DIST_FIELD(temp_r29, s32, 0x170C) = (s32) (DIST_FIELD(temp_r29, s32, 0x170C) | 0x100);
                            DIST_FIELD(temp_r29, s32, 0x17C4) = (s32) (DIST_FIELD(temp_r29, s32, 0x17C4) | 0x100);
                        }
                    }
                    DIST_FIELD(temp_r29, s32, 0x16A8) = (s32) (DIST_FIELD(temp_r29, s32, 0x16A8) | 0x40);
                    DIST_FIELD(temp_r29, s32, 0x1760) = (s32) (DIST_FIELD(temp_r29, s32, 0x1760) | 0x40);
                }
                GSgfxPerfbarCPUEntry(temp_r27);
            }
        }
    }
}
#pragma opt_common_subs reset
#pragma opt_propagation reset

}

#undef DIST_FIELD
