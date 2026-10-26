#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
u32 g_instancedMemorySizeAll;

void GsShapeRender::SwapBuffers() {
    currentBuffer=!currentBuffer;
    ExecuteFreeInstance();
}
GSgfxLayerID GsShapeRender::GetLayerId() const { return layer; }
u32 GsShapeRender::GetInstancedMemorySizeAll() { return instancedMemory; }
u32 GsShapeRender::GetUsedMemorySizeAll() { return usedMemory; }

void GsShapeRender::InitShapeRender() {
    active=0; frame=0; instance=-1; animation=0;
    keyCount=0; keys=0; objectCount=0; objects=0; textureCount=0; textures=0;
    deformCountU=0; deformU=0; deformCountV=0; deformV=0;
    twistCount=0; twist=0; gradationCount=0; gradation=0;
    refractTexture=0; flags=0; instanceCount=0; nextInstance=0;
    memset(instances,0,256);
    lastBuffer=255; currentBuffer=0;
    for(int buffer=0;buffer<2;buffer++)
        for(int i=0;i<256;i++) tokens[buffer][i]=0;
    polygonCount=0; usedMemory=0; instancedMemory=0; freeCount[0]=0; freeCount[1]=0;
}
void GsShapeRender::FreeShapeRender() {
    int i,j;
    active=0; frame=0; instance=-1; animation=0;
    for(j=0;j<2;j++) {
        for(i=0;i<256;i++) {
            if(tokens[j][i]) { GSgfxTokenWaitForClear(tokens[j][i]); tokens[j][i]=0; }
        }
    }
    for(i=0;i<objectCount;i++) {
        GsShapeObject* object=&objects[i];
        GSgfxVFFree(object->vertexFormat);
        object->vertexArrays[0]=0; object->vertexArrays[1]=0; object->vertexArrays[2]=0;
        object->vertexArrays[3]=0; object->vertexArrays[4]=0; object->vertexArrays[5]=0;
        object->FreeDisplayListShape();
    }
    for(j=0;j<256;j++) {
        if(instances[j]==1) {
            for(i=0;i<objectCount;i++) {
                if(objects[i].FreeShapeDrawBuffer(j)==1) {
                    u32 size=objects[0].entry->vertexCount*(objects[0].entry->textureCount*8+16)*2;
                    instancedMemory-=size; g_instancedMemorySizeAll-=size;
                }
                instances[j]=0;
            }
        }
        instanceCount=0;
    }
    if(keys) { GSmemFree(keys); keyCount=0; keys=0; }
    if(objects) { GSmemFree(objects); objectCount=0; objects=0; }
    if(textures) { GSmemFree(textures); textureCount=0; textures=0; }
    if(deformU) { GSmemFree(deformU); deformCountU=0; deformU=0; }
    if(deformV) { GSmemFree(deformV); deformCountV=0; deformV=0; }
    if(twist) { GSmemFree(twist); twistCount=0; twist=0; }
    if(gradation) { GSmemFree(gradation); gradationCount=0; gradation=0; }
    if(refractTexture) { GStextureFree(refractTexture); refractTexture=0; }
    polygonCount=0; usedMemory=0; instancedMemory=0; freeCount[0]=0; freeCount[1]=0;
}

static inline void shapeFreeQueuedInstances(GsShapeRender* render) {
    for(s16 i=0;i<render->freeCount[render->currentBuffer];i++) {
        s16 id=render->freeInstances[render->currentBuffer][i];
        if(render->tokens[!render->currentBuffer][id]) GSgfxTokenWaitForClear(render->tokens[!render->currentBuffer][id]);
        if(render->tokens[render->currentBuffer][id]) GSgfxTokenWaitForClear(render->tokens[render->currentBuffer][id]);
        render->tokens[0][id]=0; render->tokens[1][id]=0;
        for(u16 j=0;j<render->objectCount;j++) {
            if(render->objects[j].FreeShapeDrawBuffer(id)==1) {
                u32 size=render->objects[0].entry->vertexCount*(render->objects[0].entry->textureCount*8+16)*2;
                render->instancedMemory-=size; g_instancedMemorySizeAll-=size;
            }
        }
        render->instanceCount--; render->instances[id]=0;
    }
    render->freeCount[render->currentBuffer]=0;
}
void GsShapeRender::ExecuteFreeInstance() {
    if(lastBuffer==currentBuffer) {
        currentBuffer=!currentBuffer;
        shapeFreeQueuedInstances(this);
        currentBuffer=!currentBuffer;
    }
    shapeFreeQueuedInstances(this);
    lastBuffer=currentBuffer;
}
void GsShapeRender::FreeShapeRenderDrawBuffer(s16 id) {
    if(id<0 || id>=256) return;
    u8 next=!currentBuffer;
    GsShapeRender* counters;
    counters=(GsShapeRender*)((s16*)this+next);
    if(counters->freeCount[0]>=256) {
        currentBuffer=next;
        shapeFreeQueuedInstances(this);
        currentBuffer=!currentBuffer;
    }
    freeInstances[next][counters->freeCount[0]]=id;
    counters->freeCount[0]++;
}
s16 GsShapeRender::CreateShapeRenderDrawBuffer() {
    shapeFreeQueuedInstances(this);
    u16 tries=0;
    for(;tries<256;tries++) {
        if(instances[nextInstance]==0) { instances[nextInstance]=1; break; }
        nextInstance++;
        if(nextInstance>=256) nextInstance=0;
    }
    if(tries==256) return -1;
    if(instanceCount>=256) return -1;
    instanceCount++;
    for(u16 i=0;i<objectCount;i++) {
        if(objects[i].CreateShapeDrawBuffer(nextInstance)==0) {
            for(int j=0;j<i;j++) {
                if(objects[j].FreeShapeDrawBuffer(nextInstance)==1) {
                    u32 size=objects[0].entry->vertexCount*(objects[0].entry->textureCount*8+16)*2;
                    instancedMemory-=size; g_instancedMemorySizeAll-=size;
                }
            }
            return -1;
        }
        u32 size=objects[0].entry->vertexCount*(objects[0].entry->textureCount*8+16)*2;
        instancedMemory+=size; g_instancedMemorySizeAll+=size;
    }
    return nextInstance;
}

struct GsShapeFileHeader {
    u8 reserved00[10], layer, reserved0B;
    u32 animationOffset, objectsOffset, texturesOffset;
};
struct GsShapeFileTable { u32 reserved; u16 count, reserved06; u32 entriesOffset; };
struct GsShapeFileTexture { u32 reserved00[3]; u8 reserved0C[2], usesExtraStage, reserved0F[5]; u32 imageOffset; };
struct GsShapeTextureLink { GsShapeFileTexture* entry; GStexture* texture; };
struct GSgfxVF;
extern "C" {
void GSgfxVFInit(GSgfxVF*);
void GSgfxVFCreate(GSgfxVF*);
void GSgfxVFSetElement(GSgfxVF*,s32,s32,s32,u8);
GStexture* GStextureLoad(void*);
void GStextureSetWrap(GStexture*,s32,s32);
GStexture* GStextureCreate(u16,u16,s32,s32,u8);
}
static inline void* shapeFilePointer(u8* base,u32 offset) { return base+offset; }
static inline void shapeRelocateCurve(u8* base,GsShapeCurvePoint*& curve) { curve=(GsShapeCurvePoint*)shapeFilePointer(base,(u32)curve); }
static inline void shapeAccumulateTextureStages(GsShapeRender* render,void* mapping,int index,u8& stages) {
    stages++;
    if(index<2) {
        u16 texture=*(u16*)((u8*)mapping+4);
        if(((GsShapeTextureLink*)render->textures)[texture].entry->usesExtraStage) stages+=2;
        else stages++;
    }
}
bool GsShapeRender::LoadShapeRender(void* file) {
    u8* base=(u8*)file;
    GsShapeFileHeader* header=(GsShapeFileHeader*)file;
    active=0; FreeShapeRender();
    switch(header->layer) {
    case 0: layer=GS_SHAPE_LAYER_DEFAULT; break;
    case 1: layer=GS_SHAPE_LAYER_ALTERNATE; break;
    default: layer=GS_SHAPE_LAYER_DEFAULT; break;
    }
    animation=(GsShapeFileAnimation*)shapeFilePointer(base,header->animationOffset);
    u32* offsets=(u32*)shapeFilePointer(base,animation->keysOffset);
    keyCount=animation->keyCount;
    keys=(GsKeyObject*)GSmemAlloc(animation->keyCount*sizeof(GsKeyObject));
    u16 maxU=0,maxV=0,maxTwist=0,maxGradation=0;
    u32* keyCursor=offsets;
    for(int i=0;i<keyCount;i++,keyCursor++) {
        GsKeyObject* key=&keys[i];
        key->entry=(GsShapeKeyEntry*)shapeFilePointer(base,*keyCursor);
        key->frames=(tagGsFilePrimKeyFrame**)shapeFilePointer(base,(u32)key->entry->frames);
        GsShapeKeyEntry* entry=key->entry;
        for(int j=0;j<key->entry->frameCount;j++) {
            tagGsFilePrimKeyFrame* frame=(tagGsFilePrimKeyFrame*)shapeFilePointer(base,(u32)key->frames[j]);
            key->frames[j]=frame;
            shapeRelocateCurve(base,frame->transformCurves[0]); shapeRelocateCurve(base,frame->transformCurves[1]);
            shapeRelocateCurve(base,frame->transformCurves[2]); shapeRelocateCurve(base,frame->transformCurves[3]);
            shapeRelocateCurve(base,frame->transformCurves[4]); shapeRelocateCurve(base,frame->transformCurves[5]);
            shapeRelocateCurve(base,frame->transformCurves[6]); shapeRelocateCurve(base,frame->transformCurves[7]);
            shapeRelocateCurve(base,frame->transformCurves[8]); shapeRelocateCurve(base,frame->transformCurves[9]);
            shapeRelocateCurve(base,frame->transformCurves[10]); shapeRelocateCurve(base,frame->transformCurves[11]);
            shapeRelocateCurve(base,frame->colorCurves[0]); shapeRelocateCurve(base,frame->colorCurves[1]);
            shapeRelocateCurve(base,frame->colorCurves[2]); shapeRelocateCurve(base,frame->colorCurves[3]);
            shapeRelocateCurve(base,frame->radiusCurves[0]); shapeRelocateCurve(base,frame->radiusCurves[1]);
            shapeRelocateCurve(base,frame->radiusCurves[2]); shapeRelocateCurve(base,frame->radiusCurves[3]);
            shapeRelocateCurve(base,frame->showAngleCurves[0]); shapeRelocateCurve(base,frame->showAngleCurves[1]);
            for(int texture=0;texture<4;texture++) {
                shapeRelocateCurve(base,frame->textureScaleCurves[texture*2]); shapeRelocateCurve(base,frame->textureScaleCurves[texture*2+1]);
                shapeRelocateCurve(base,frame->textureOffsetCurves[texture*2]); shapeRelocateCurve(base,frame->textureOffsetCurves[texture*2+1]);
                shapeRelocateCurve(base,frame->textureColorCurves[texture*4]); shapeRelocateCurve(base,frame->textureColorCurves[texture*4+1]);
                shapeRelocateCurve(base,frame->textureColorCurves[texture*4+2]); shapeRelocateCurve(base,frame->textureColorCurves[texture*4+3]);
                shapeRelocateCurve(base,frame->textureColorLowCurves[texture*4]); shapeRelocateCurve(base,frame->textureColorLowCurves[texture*4+1]);
                shapeRelocateCurve(base,frame->textureColorLowCurves[texture*4+2]); shapeRelocateCurve(base,frame->textureColorLowCurves[texture*4+3]);
            }
            frame->deformU=(f32*)shapeFilePointer(base,(u32)frame->deformU);
            frame->deformV=(f32*)shapeFilePointer(base,(u32)frame->deformV);
            frame->twist=(f32*)shapeFilePointer(base,(u32)frame->twist);
            frame->gradationU=(tagGScol4ub*)shapeFilePointer(base,(u32)frame->gradationU);
            frame->gradationV=(tagGScol4ub*)shapeFilePointer(base,(u32)frame->gradationV);
            if(entry->channelFlags[9]==1 || entry->channelFlags[5]==1 || entry->channelFlags[2]==1 || entry->channelFlags[4]==1) {
                if(maxU<frame->deformCountU) maxU=frame->deformCountU;
                if(maxV<frame->deformCountV) maxV=frame->deformCountV;
            }
            if(entry->channelFlags[5] && maxTwist<frame->twistCount) maxTwist=frame->twistCount;
            if(entry->channelFlags[7] && entry->channelFlags[8]==1) {
                if(frame->gradationType==0) { if(maxGradation<frame->gradationCountU) maxGradation=frame->gradationCountU; }
                else if(maxGradation<frame->gradationCountV) maxGradation=frame->gradationCountV;
            }
        }
    }
    GsShapeFileTable* objectTable=(GsShapeFileTable*)shapeFilePointer(base,header->objectsOffset);
    offsets=(u32*)shapeFilePointer(base,objectTable->entriesOffset);
    objectCount=objectTable->count;
    objects=(GsShapeObject*)GSmemAlloc(objectCount*sizeof(GsShapeObject));
    u8 needsRefraction=0;
    for(int i=0;i<objectCount;i++) {
        tagGsFilePrimObjectEntry* entry=(tagGsFilePrimObjectEntry*)shapeFilePointer(base,offsets[i]);
        objects[i].entry=entry;
        entry->vertices=(Vec*)shapeFilePointer(base,(u32)entry->vertices);
        entry->colors=(tagGScol4ub*)shapeFilePointer(base,(u32)entry->colors);
        entry->textureCoords=(GsShapePair*)shapeFilePointer(base,(u32)entry->textureCoords);
        if(entry->reserved1C) entry->reserved1C=shapeFilePointer(base,(u32)entry->reserved1C);
        for(int j=0;j<entry->textureCount;j++) if(entry->textures[j]) entry->textures[j]=shapeFilePointer(base,(u32)entry->textures[j]);
        if(entry->dynamic==1 && entry->shapeType==8) needsRefraction=1;
        memset(objects[i].drawBuffers,0,sizeof(objects[i].drawBuffers));
    }
    GsShapeFileTable* textureTable=(GsShapeFileTable*)shapeFilePointer(base,header->texturesOffset);
    offsets=(u32*)shapeFilePointer(base,textureTable->entriesOffset);
    textureCount=textureTable->count;
    if(textureCount) textures=GSmemAlloc(textureCount*sizeof(GsShapeTextureLink));
    else textures=0;
    for(int i=0;i<textureCount;i++) {
        GsShapeFileTexture* entry=(GsShapeFileTexture*)shapeFilePointer(base,offsets[i]);
        ((GsShapeTextureLink*)textures)[i].entry=entry;
        ((GsShapeTextureLink*)textures)[i].texture=GStextureLoad(shapeFilePointer(base,entry->imageOffset));
        GStextureSetWrap(((GsShapeTextureLink*)textures)[i].texture,1,1);
    }
    for(int i=0;i<objectCount;i++) {
        u8 stages=0;
        for(int j=0;j<objects[i].entry->textureCount;j++) {
            shapeAccumulateTextureStages(this,objects[i].entry->textures[j],j,stages);
        }
        if(stages) stages++;
        objects[i].reserved45C[0]=stages;
    }
    for(int i=0;i<objectCount;i++) {
        GsShapeObject* object=&objects[i]; tagGsFilePrimObjectEntry* entry=object->entry;
        int attributes[4]={13,14,15,16};
        object->vertexArrays[0]=0; object->vertexArrays[1]=0; object->vertexArrays[2]=0;
        object->vertexArrays[3]=0; object->vertexArrays[4]=0; object->vertexArrays[5]=0;
        GSgfxVFInit((GSgfxVF*)object->vertexFormat); GSgfxVFCreate((GSgfxVF*)object->vertexFormat);
        GSgfxVFSetElement((GSgfxVF*)object->vertexFormat,9,1,4,0); GSgfxVFSetElement((GSgfxVF*)object->vertexFormat,11,1,5,0);
        for(int j=0;j<entry->textureCount;j++) GSgfxVFSetElement((GSgfxVF*)object->vertexFormat,attributes[j],1,4,0);
        object->displayList=0; object->MakeDisplayListShape();
    }
    if(maxU) { deformCountU=maxU; deformU=(f32*)GSmemAlloc(deformCountU*4); }
    if(maxV) { deformCountV=maxV; deformV=(f32*)GSmemAlloc(deformCountV*4); }
    if(maxTwist) { twistCount=maxTwist; twist=(f32*)GSmemAlloc(twistCount*4); }
    if(maxGradation) { gradationCount=maxGradation; gradation=(tagGScol4ub*)GSmemAlloc(gradationCount*4); }
    if(needsRefraction==1) refractTexture=GStextureCreate(0,0,0x45,0,0);
    polygonCount=0;
    for(int i=0;i<objectCount;i++) polygonCount+=objects[i].GetPolygonCount();
    active=1;
    usedMemory=0; usedMemory+=sizeof(GsShapeRender); usedMemory+=keyCount*sizeof(GsKeyObject);
    usedMemory+=objectCount*sizeof(GsShapeObject); usedMemory+=textureCount*sizeof(GsShapeTextureLink);
    if(refractTexture) usedMemory+=0x12C080;
    instancedMemory=0; freeCount[0]=0; freeCount[1]=0;
    return true;
}

// Per-object texture mapping data stored in the primitive file.
struct GsShapeTextureMapping {
    u8 reserved00[0xB], scaleBeforeOffset;
    f32 minU,maxU,minV,maxV;
};
extern "C" GSmtx mtxIdent;
void GsShapeRender::Update(f32 time,s16 id) {
    if(!active) return;
    GsShapeFileAnimation* sequence=animation;
    if(!sequence) return;
    u32 nextFrame;
    if(!sequence) nextFrame=0;
    else {
        nextFrame=(u32)(time*(f32)sequence->frameRate);
        if(sequence->loop==1) nextFrame%=sequence->frameCount-1;
        else if(sequence->loop==2 && nextFrame>sequence->frameCount-1) nextFrame=sequence->frameCount-1;
    }
    frame=nextFrame;
    if(frame>=animation->frameCount) return;
    if(id>=0 && id<256 && tokens[currentBuffer][id]) {
        GSgfxTokenWaitForClear(tokens[currentBuffer][id]);
        tokens[currentBuffer][id]=0;
    }
    for(int i=0;i<keyCount;i++) {
        GsKeyObject* key=&keys[i];
        GsShapeKeyEntry* channel=key->entry;
        GsShapeObject* object=&objects[channel->objectIndex];
        tagGsFilePrimObjectEntry* primitive=object->entry;
        tagGsFilePrimKeyFrame *first,*second;
        f32 t;
        if(!primitive->dynamic || !key->GetFrameInterval(frame,first,second,t)) continue;
        key->visible=first->visible!=0;
        if(!first->visible) continue;
        if(id>=0 && id<256 && object->drawBuffers[id]) {
            u32 offset=0;
            u16 count=primitive->vertexCount;
            if(currentBuffer) offset=count*(primitive->textureCount*8+16);
            u8* vertices=object->drawBuffers[id]+offset;
            object->vertexArrays[0]=vertices;
            u8* colors=vertices+count*12;
            object->vertexArrays[1]=colors;
            for(int j=0;j<4;j++) {
                if(j<primitive->textureCount) { int stride=j*8+4; object->vertexArrays[j+2]=colors+count*stride; }
            }
        } else {
            object->vertexArrays[0]=0; object->vertexArrays[1]=0; object->vertexArrays[2]=0;
            object->vertexArrays[3]=0; object->vertexArrays[4]=0; object->vertexArrays[5]=0;
        }
        int vertexDeform; if(channel->channelFlags[9]==1 && channel->channelFlags[10]==1) vertexDeform=1; else vertexDeform=0;
        int vertexTwist; if(channel->channelFlags[5]==1 && channel->channelFlags[6]==1) vertexTwist=1; else vertexTwist=0;
        if(vertexDeform==1 || vertexTwist==1 || channel->channelFlags[2]==1 || channel->channelFlags[4]==1) {
            if(vertexDeform==1) {
                key->GetDeformParameterU(deformU,first,second,t);
                key->GetDeformParameterV(deformV,first,second,t);
            } else {
                key->GetLinearParameterU(deformU,first);
                key->GetLinearParameterV(deformV,second);
            }
            f32 radiusU=0.0f,radiusV=0.0f,angleU=0.0f,angleV=0.0f;
            if(channel->channelFlags[2]==1) key->GetShapeRadius(&radiusU,&radiusV,first,second,t);
            if(channel->channelFlags[4]==1) key->GetShapeShowAngle(&angleU,&angleV,first,second,t);
            if(vertexTwist==1) key->GetTwistParameter(twist,first,second,t);
            object->DeformVertexCoord(vertexDeform!=0,deformU,deformV,channel->channelFlags[2]!=0,radiusU,radiusV,
                channel->channelFlags[4]!=0,angleU,angleV,vertexTwist!=0,twist);
        }
        key->GetShapeMatrix(&key->shapeMatrix,&key->transformMatrix,primitive,animation->transformCount,animation->transformOrder,first,second,t);
        int textureDeform; if(channel->channelFlags[9]==1 && channel->channelFlags[10]==0) textureDeform=1; else textureDeform=0;
        int textureTwist; if(channel->channelFlags[5]==1 && channel->channelFlags[6]==0) textureTwist=1; else textureTwist=0;
        bool deformTexture=textureDeform!=0,twistTexture=textureTwist!=0;
        for(u8 texture=0;texture<primitive->textureCount;texture++) {
            if((textureDeform==1 || textureTwist==1) && (!refractTexture || texture!=0)) {
                if(textureDeform) {
                    key->GetDeformParameterU(deformU,first,second,t);
                    key->GetDeformParameterV(deformV,first,second,t);
                }
                if(textureTwist) key->GetTwistParameter(twist,first,second,t);
                object->DeformTextureCoord(texture,deformTexture,deformU,deformV,twistTexture,twist);
            }
            if(primitive->shapeType==10 && primitive->textureCount) {
                GsShapePair offset=key->GetTextureOffset(first,second,t,0);
                GsShapePair scale=key->GetTextureScale(first,second,t,0);
                offset.u*=scale.u; offset.v*=scale.v;
                object->WaveTextureCoord(texture,offset.u,offset.v,&key->shapeMatrix,false);
            }
            u32 textureIndex=texture;
            GsShapeTextureMapping* mapping=(GsShapeTextureMapping*)object->entry->textures[textureIndex];
            if(primitive->shapeType==8 && texture==0) memcpy(&key->textureMatrices[textureIndex],&mtxIdent,sizeof(GSmtx));
            else if(channel->channelFlags[12+textureIndex]==1) {
                f32 offsetU,offsetV,scaleU,scaleV;
                if(channel->channelFlags[12+textureIndex]==1) {
                    GsShapePair offset=key->GetTextureOffset(first,second,t,texture);
                    offsetU=offset.u; offsetV=offset.v;
                    GsShapePair scale=key->GetTextureScale(first,second,t,texture);
                    scaleU=scale.u; scaleV=scale.v;
                }
                if(first->textureSwapAxes[texture]) {
                    if(!mapping->scaleBeforeOffset) {
                        GSmtx* matrix=&key->textureMatrices[textureIndex];
                        matrix->matrix[0][0]=0.0f; matrix->matrix[0][1]=1.0f; matrix->matrix[0][2]=0.0f; matrix->matrix[0][3]=0.0f;
                        matrix->matrix[1][0]=1.0f; matrix->matrix[1][1]=0.0f; matrix->matrix[1][2]=0.0f; matrix->matrix[1][3]=0.0f;
                        matrix->matrix[2][0]=0.0f; matrix->matrix[2][1]=0.0f; matrix->matrix[2][2]=1.0f; matrix->matrix[2][3]=0.0f;
                        PSMTXTransApply(matrix->matrix,matrix->matrix,-offsetU,-offsetV,0.0f);
                        PSMTXScaleApply(matrix->matrix,matrix->matrix,scaleU,scaleV,0.0f);
                    } else {
                    GSmtx* matrix=&key->textureMatrices[textureIndex];
                        matrix->matrix[0][0]=0.0f; matrix->matrix[0][1]=1.0f; matrix->matrix[0][2]=0.0f; matrix->matrix[0][3]=0.0f;
                        matrix->matrix[1][0]=1.0f; matrix->matrix[1][1]=0.0f; matrix->matrix[1][2]=0.0f; matrix->matrix[1][3]=0.0f;
                        matrix->matrix[2][0]=0.0f; matrix->matrix[2][1]=0.0f; matrix->matrix[2][2]=1.0f; matrix->matrix[2][3]=0.0f;
                        PSMTXScaleApply(matrix->matrix,matrix->matrix,scaleU,scaleV,0.0f);
                        PSMTXTransApply(matrix->matrix,matrix->matrix,-offsetU,-offsetV,0.0f);
                    }
                } else if(!mapping->scaleBeforeOffset) {
                    GSmtx* matrix=&key->textureMatrices[textureIndex];
                    PSMTXTrans(matrix->matrix,-offsetU,-offsetV,0.0f);
                    PSMTXScaleApply(matrix->matrix,matrix->matrix,scaleU,scaleV,0.0f);
                } else {
                    GSmtx* matrix=&key->textureMatrices[textureIndex];
                    PSMTXScale(matrix->matrix,scaleU,scaleV,0.0f);
                    PSMTXTransApply(matrix->matrix,matrix->matrix,-offsetU,-offsetV,0.0f);
                }
            } else {
                GSmtx* matrix=&key->textureMatrices[textureIndex];
                PSMTXScale(matrix->matrix,mapping->maxU-mapping->minU,mapping->maxV-mapping->minV,0.0f);
                PSMTXTransApply(matrix->matrix,matrix->matrix,mapping->minU,mapping->minV,0.0f);
            }
        }
        if(primitive->colorMode==0) {
            if(channel->channelFlags[7]==1) {
                if(channel->channelFlags[8]==0) {
                    tagGScol4ub color=key->GetShapeColor(first,second,t);
                    object->SetVertexColorSpecify(color,true);
                } else {
                    f32 alpha=key->GetShapeColorAlpha(first,second,t);
                    u8 axis;
                    key->GetGradationParameter(&axis,gradation,first,second,t);
                    object->SetVertexColorGradation(axis,gradation,primitive->shapeType,alpha,true);
                }
            } else {
                f32 alpha=key->GetShapeColorAlpha(first,second,t);
                object->SetVertexColorAlpha(channel->channelFlags[8],primitive->shapeType,alpha,true);
            }
        }
        tagGScol4ub color=key->GetTextureColor(first,second,t,0);
        object->reserved45C[1]=color.r; object->reserved45C[2]=color.g; object->reserved45C[3]=color.b; object->reserved45C[4]=color.a;
        tagGScol4ub colorLow=key->GetTextureColorLow(first,second,t,0);
        object->reserved45C[5]=colorLow.r; object->reserved45C[6]=colorLow.g; object->reserved45C[7]=colorLow.b; object->reserved45C[8]=colorLow.a;
        object->reserved45C[8]=255;
        if(primitive->textureCount>1) {
            tagGScol4ub colorHigh=key->GetTextureColor(first,second,t,1);
            object->reserved45C[9]=colorHigh.r; object->reserved45C[10]=colorHigh.g; object->reserved45C[11]=colorHigh.b; object->reserved45C[12]=colorHigh.a;
            tagGScol4ub colorHighLow=key->GetTextureColorLow(first,second,t,1);
            object->reserved45C[13]=colorHighLow.r; object->reserved45C[14]=colorHighLow.g; object->reserved45C[15]=colorHighLow.b; object->reserved45C[16]=colorHighLow.a;
        }
    }
}
struct GSgfxVF;
struct GsShapeTexture;
enum GSgfxTgenFunc { SHAPE_TGEN_DEFAULT };
enum GSgfxTgenSrc { SHAPE_TGEN_SRC_DEFAULT };
enum GSgfxLayerPass { SHAPE_PASS_DEFAULT };
struct ShapeMatrixFrame {u32 flags;GSmtx matrix;};
struct GSgfxMatrixStack {
    u32 reserved0;
    ShapeMatrixFrame *frame;
    void push(GSmtx *);
    void pushMult(GSmtx *);
    void pop();
};
struct GSgfxLayer {
    u8 reserved0[0xEAC];
    u8 textureStages;
    u8 reservedEAD[0x647];
    u32 constantColor[4];
    u8 reserved1504[0x1A4];
    u32 dirty;
    u8 reserved16AC[0x20];
    u32 stageDirty;
    u8 reserved16D0[0x28];
    u32 constantColorDirty;
    u8 reserved16FC[0x64];
    u32 savedDirty;
    u8 reserved1764[0x20];
    u32 savedStageDirty;
    u8 reserved1788[0x28];
    u32 savedConstantColorDirty;
    u8 reserved17B4[0x1E0];
    GSgfxLayerPass pass;
    u8 reserved1998[8];
    GSgfxMatrixStack *matrixStack;
    void setRenderStateAndSelect(GSgfxVF *);
    void tgenFunc(u8,GSgfxTgenFunc,GSgfxTgenSrc,GSmtx *,bool,GSmtx *);
    void textureCopy(GSgfxLayerPass,GStexture *,bool,u8 *,bool,bool,bool);
    inline void setTextureStages(u8 count) {
        textureStages=count;
        stageDirty|=1;
        dirty|=8;
        savedStageDirty|=1;
        savedDirty|=8;
    }
    inline void setConstantColor(u8 index,tagGScol4ub color) {
        constantColor[index]=*(u32 *)&color;
        constantColorDirty|=1<<index;
        dirty|=0x10;
        savedConstantColorDirty|=1<<index;
        savedDirty|=0x10;
    }
};
typedef char ShapeRenderLayerMatrixOffset[offsetof(GSgfxLayer,matrixStack)==0x19A0?1:-1];
extern "C" {
GSgfxLayer *GSgfxLayerFindByID(GSgfxLayerID);
u32 GScameraGetActiveCamera();
void GScameraGetPerspective(u32,f32 *,f32 *,f32 *,f32 *);
u16 GSgfxTokenMark();
void MakeMatrixBillboard__13GsShapeObjectFP5GSmtxf(GsShapeObject *,GSmtx *,f32);
bool ShadeVertexColor__13GsShapeObjectFP5GSmtxP5GSmtxP5GSmtxfb(GsShapeObject *,GSmtx *,GSmtx *,GSmtx *,f32,bool);
bool RefractTextureCoord__13GsShapeObjectFffP5GSmtxP5GSmtxP5GSmtxf(GsShapeObject *,f32,f32,GSmtx *,GSmtx *,GSmtx *,f32);
void SetStateMode__13GsShapeObjectFP10GSgfxLayer(GsShapeObject *,GSgfxLayer *);
void SetStateTexture__13GsShapeObjectFP10GSgfxLayerP14GsShapeTextureP9GStexture(GsShapeObject *,GSgfxLayer *,GsShapeTexture *,GStexture *);
void CallDisplayListShape__13GsShapeObjectFP10GSgfxLayersUc(GsShapeObject *,GSgfxLayer *,s16,u8);
}

inline bool shapeObjectBillboard(tagGsFilePrimObjectEntry *primitive)
{
    u8 type=((u8 *)primitive)[0xCD];
    u8 result=0;
    if(type>=1 && type<=3) result=1;
    return result!=0;
}

void GsShapeRender::Render(s16 instanceId,GSgfxLayerID layerId)
{
    if(active && frame<animation->frameCount) {
        s32 i;
        u32 activeCamera;
        f32 fov,aspect,depth,farPlane;
        GSmtx *camera;
        GSgfxLayer *renderLayer;
        renderLayer=GSgfxLayerFindByID(layerId);
        depth=0.1f;
        activeCamera=GScameraGetActiveCamera();
        if(activeCamera) GScameraGetPerspective(activeCamera,&fov,&aspect,&depth,&farPlane);
        camera=&renderLayer->matrixStack->frame->matrix;
        if(camera) {
            for(i=0;i<keyCount;i++) {
                GsKeyObject *key=&keys[i];
                GsShapeKeyEntry *channel=key->entry;
                GsShapeObject *object=&objects[channel->objectIndex];
                tagGsFilePrimObjectEntry *primitive=object->entry;
                if(primitive->dynamic && key->visible) {
                    bool billboard=shapeObjectBillboard(primitive);
                    if(billboard==1) MakeMatrixBillboard__13GsShapeObjectFP5GSmtxf(object,camera,depth);
                    GSmtx *view;
                    if(billboard==1) view=(GSmtx *)((u8 *)object+0x470);
                    else view=camera;
                    if(primitive->colorMode && object->entry->reserved1C) {
                        tagGsFilePrimKeyFrame *first,*second;
                        f32 t;
                        if(!key->GetFrameInterval(frame,first,second,t)) continue;
                        if(channel->channelFlags[7]==1) {
                            if(channel->channelFlags[8]==0) {
                                tagGScol4ub color=key->GetShapeColor(first,second,t);
                                object->SetVertexColorSpecify(color,false);
                            } else {
                                f32 alpha=key->GetShapeColorAlpha(first,second,t);
                                u8 axis;
                                key->GetGradationParameter(&axis,gradation,first,second,t);
                                object->SetVertexColorGradation(axis,gradation,primitive->shapeType,alpha,false);
                            }
                        } else {
                            f32 alpha=key->GetShapeColorAlpha(first,second,t);
                            object->SetVertexColorAlpha(channel->channelFlags[8],primitive->shapeType,alpha,false);
                        }
                        ShadeVertexColor__13GsShapeObjectFP5GSmtxP5GSmtxP5GSmtxfb(object,&key->transformMatrix,&key->shapeMatrix,view,depth,channel->channelFlags[2]!=0);
                    }
                    if(primitive->shapeType==8 && primitive->textureCount) {
                        tagGsFilePrimKeyFrame *first,*second;
                        f32 t;
                        if(key->GetFrameInterval(frame,first,second,t)) {
                            GsShapePair offset=key->GetTextureOffset(first,second,t,0);
                            GsShapePair scale=key->GetTextureScale(first,second,t,0);
                            offset.u*=scale.u;
                            offset.v*=scale.v;
                            RefractTextureCoord__13GsShapeObjectFffP5GSmtxP5GSmtxP5GSmtxf(object,offset.u,offset.v,&key->transformMatrix,&key->shapeMatrix,view,depth);
                        }
                    }
                }
            }
            GSgfxTgenSrc sources[8]={(GSgfxTgenSrc)4,(GSgfxTgenSrc)5,(GSgfxTgenSrc)6,(GSgfxTgenSrc)7,(GSgfxTgenSrc)8,(GSgfxTgenSrc)9,(GSgfxTgenSrc)10,(GSgfxTgenSrc)11};
            for(i=0;i<keyCount;i++) {
                GsKeyObject *key=&keys[i];
                GsShapeObject *object=&objects[key->entry->objectIndex];
                tagGsFilePrimObjectEntry *primitive=object->entry;
                if(primitive->dynamic && key->visible) {
                    u8 count=primitive->textureCount;
                    if(count) {
                        renderLayer->setRenderStateAndSelect((GSgfxVF *)object->vertexFormat);
                        renderLayer->setTextureStages(object->reserved45C[0]);
                        renderLayer->setConstantColor(0,*(tagGScol4ub *)&object->reserved45C[1]);
                        renderLayer->setConstantColor(1,*(tagGScol4ub *)&object->reserved45C[5]);
                        renderLayer->setConstantColor(2,*(tagGScol4ub *)&object->reserved45C[9]);
                        renderLayer->setConstantColor(3,*(tagGScol4ub *)&object->reserved45C[13]);
                    } else renderLayer->setRenderStateAndSelect((GSgfxVF *)object->vertexFormat);
                    SetStateMode__13GsShapeObjectFP10GSgfxLayer(object,renderLayer);
                    if(primitive->shapeType==8 && refractTexture) renderLayer->textureCopy(renderLayer->pass,refractTexture,false,0,false,false,false);
                    SetStateTexture__13GsShapeObjectFP10GSgfxLayerP14GsShapeTextureP9GStexture(object,renderLayer,(GsShapeTexture *)textures,primitive->shapeType==8?refractTexture:0);
                    for(u8 texture=0;texture<count;texture++) renderLayer->tgenFunc(texture,(GSgfxTgenFunc)1,sources[texture],&key->textureMatrices[texture],false,0);
                    bool billboard=shapeObjectBillboard(primitive);
                    if(billboard==1) renderLayer->matrixStack->push((GSmtx *)((u8 *)object+0x470));
                    renderLayer->matrixStack->pushMult(&key->transformMatrix);
                    renderLayer->matrixStack->pushMult(&key->shapeMatrix);
                    CallDisplayListShape__13GsShapeObjectFP10GSgfxLayersUc(object,renderLayer,instanceId,currentBuffer);
                    renderLayer->matrixStack->pop();
                    renderLayer->matrixStack->pop();
                    if(billboard==1) renderLayer->matrixStack->pop();
                    if(count) renderLayer->setTextureStages(1);
                }
            }
            if(instanceId>=0 && instanceId<256) tokens[currentBuffer][instanceId]=GSgfxTokenMark();
        }
    }
}
