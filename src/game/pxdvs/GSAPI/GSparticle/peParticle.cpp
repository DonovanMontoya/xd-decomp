#include <game/pxdvs/GSAPI/GSparticle/peParticlePrivate.hpp>
#include <dolphin/os/OSFastCast.h>
extern "C" f32 HSD_Randf();
extern "C" GSgfxVF g_vertex_format,g_ext_vertex_format;
extern "C" void DCFlushRange(void*,u32);
static inline void invalidateParticle(peParticleNode* node,u32 flags,GSgfxDL* list) {
    u16* indices;
    bool extended=(flags&0x2000000)!=0;
    indices=0;
    node->live=0;
    u16 vertex=node->sortIndex*4;
    if(list->flags&1)indices=(u16*)(list->data+(vertex*list->stride)+3);
    u16 vertices=4;
    while(vertices--) {indices[0]=0xffff;indices[1]=0xffff;indices[2]=0xffff;indices+=3;if(extended)*indices++=0xffff;}
    list->flags|=2;
}
void peParticleContainer::Stop() {
    if(active) {
        PreUpdate();active=0;u32 flags=particle->flags;
        if(flags&0x20000000)SetLayerVisibility((GSgfxLayerID)1,false);
        if(flags&0x40000000)SetLayerVisibility((GSgfxLayerID)3,false);
        if(flags&0x80000000)SetLayerVisibility((GSgfxLayerID)5,false);
        peParticleNode* node=(peParticleNode*)nodes;
        while(node){invalidateParticle(node,particle->flags,&displayLists[swapIndex]);node=(peParticleNode*)node->next;}
        RemoveAll();ResetSwap();
    }
}
extern "C" {
extern s32 g_render_pass;
void GSgfxVFSetArray(GSgfxVF*,s32,s32,void*,u8,u32);
void particleEngineSetupTevStages(u32,u32,s32);
void particleEngineSetupBlendMode(u32);
void particleEngineSetupTexture(u8,void*,s32,s32,s32,s32);
void dlDraw__10GSgfxLayerFP7GSgfxDL(GSgfxLayer*,GSgfxDL*);
}
static inline u32 &layerWord(u32 offset) {return *(u32*)((u8*)g_current_layer+offset);}
static inline u8 visible(peParticleContainer* c) {
    if(!c->active)return 0;
    if(!c->count)return 0;
    if(g_render_pass!=1)return 0;
    u32 flags=c->particle->flags;
    switch(layerWord(0x28)){
    case 0:if(flags&0x8000000)return 1;break;
    case 2:if(flags&0x10000000)return 1;if(!(flags&0xf8000800))return 1;break;
    case 4:if(flags&0x800)return 1;break;
    case 1:if(flags&0x20000000)return 1;break;
    case 3:if(flags&0x40000000)return 1;break;
    case 5:if(flags&0x80000000)return 1;break;
    default:return 0;}
    return 0;
}
void peParticleContainer::Render() {
    if(active&&visible(this)) {
        ResolveMultipleSwap();u32 flags=particle->flags;u32 extended=(flags>>25)&1;
        if(flags&0x200) {
            u8* layer=(u8*)g_current_layer;
            *(u32*)(layer+0xd8c)=2;*(u32*)(layer+0x16b8)|=2;*(u32*)(layer+0x16a8)|=2;*(u32*)(layer+0x1770)|=2;*(u32*)(layer+0x1760)|=2;
        } else {
            u8* layer=(u8*)g_current_layer;
            *(u32*)(layer+0xd8c)=0;*(u32*)(layer+0x16b8)|=2;*(u32*)(layer+0x16a8)|=2;*(u32*)(layer+0x1770)|=2;*(u32*)(layer+0x1760)|=2;
        }
        particleEngineSetupBlendMode(flags&7);
        GSgfxDL *list=&displayLists[swapIndex];u8 *data=(u8*)renderData[swapIndex];GSgfxVF *format=(list->flags&1)?(GSgfxVF*)list->reserved:0;
        if(extended) {
            GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x30,4,renderBytes);GSgfxVFSetArray(format,12,3,data+0x34,4,renderBytes);GSgfxVFSetArray(format,13,3,uv,4,0x20);
        } else {
            GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x30,4,renderBytes);GSgfxVFSetArray(format,13,3,uv,4,0x20);
        }
        if(flags&0x100000) {
            particleEngineSetupTevStages(0,extended,0xc00000==(flags&0xc00000)?1:0);
            layerWord(0x1998)=0x80;layerWord(0x199c)=(u32)format;
            peParticleNode* node=(peParticleNode*)nodes;
            while(node){node->Render(particle,&displayLists[swapIndex],(char*)renderData[swapIndex]);node=(peParticleNode*)node->next;}
        } else {
            particleEngineSetupTevStages(0,extended,0);
            s32 wrapT=0;if(flags&0x100)wrapT=2;
            void* texture=particle->texture;
            s32 clampS=(flags>>12)&3;s32 clampT=(flags>>14)&3;
            s32 wrapS=0;if(flags&0x80)wrapS=2;
            particleEngineSetupTexture(0,texture,clampS,clampT,wrapS,wrapT);
            dlDraw__10GSgfxLayerFP7GSgfxDL(g_current_layer,&displayLists[swapIndex]);
        }
        MarkForSwap();
    }
}
u16 peParticleContainer::Emit(u16 requested) {
    if(!active)return 0;
    u16 remaining=CreateNodes(requested);_EmitParams* params=g_emitParams;peNode* node=nodes;peNode* next;u16 result=remaining;
    while(remaining){next=node->next;((peParticleNode*)node)->Start(owner,particle,&displayLists[swapIndex],params);node=next;--remaining;++params;}
    return result;
}
void peParticleContainer::Start() {
    if(!active){active=1;u32 flags=particle->flags;InitSwap();
        if(flags&0x20000000)SetLayerVisibility((GSgfxLayerID)1,true);
        if(flags&0x40000000)SetLayerVisibility((GSgfxLayerID)3,true);
        if(flags&0x80000000)SetLayerVisibility((GSgfxLayerID)5,true);
    }
}
peParticleContainer::~peParticleContainer(){if(sorted)delete[] sorted;g_particle_debug_stats.node-=0x7c;g_particle_debug_stats.total-=0x7c;}
void peParticleContainer::DepthSort() {
    if(active && (particle->flags&0x80000) && count>=2 && sorted) {
        u8 changed=0;
        for(s32 i=1;i<(s32)capacity;++i) {
            peParticleNode* node=sorted[i];
            if(node->live) {
                s32 position=i;
                for(;;) {
                    s32 previous=position;
                    if(!sorted)previous=-1;
                    else {
                        peParticleNode** cursor=&sorted[position];
                        for(;;) {
                            if(previous<=0){previous=-1;break;}
                            peParticleNode* before=cursor[-1];--cursor;--previous;
                            if(before->live)break;
                        }
                    }
                    if(previous>=0) {
                        peParticleNode* before=sorted[previous];
                        u8 move;
                        if(before->depth==node->depth)move=0;
                        else if(before->sortIndex<node->sortIndex)move=before->depth<node->depth;
                        else move=before->depth>node->depth;
                        if(move){sorted[position]=before;position=previous;changed=1;continue;}
                    }
                    sorted[position]=node;break;
                }
            }
        }
        if(changed) {
            u32 extended=(particle->flags>>25)&1;
            GSgfxDL* list=&displayLists[swapIndex];
            for(s32 i=0;i<(s32)capacity;++i) {
                peParticleNode* node=sorted[i];
                if(node->live && node->sortIndex!=(u16)i) {
                    node->sortIndex=i;
                    u16 vertex=node->index*(u16)((extended!=0)+13);
                    u16* indices=(list->flags&1)?(u16*)(list->data+(((i*4)&0xfffc)*list->stride)+3):0;
                    u16 j=0;
                    if(extended) {
                        for(;j<4;++j){s16 uv=j*2;indices[0]=vertex+j*3;indices[1]=vertex;indices[2]=vertex;indices[3]=uv;indices+=4;}
                    } else {
                        for(;j<4;++j){s16 uv=j*2;indices[0]=vertex+j*3;indices[1]=vertex;indices[2]=uv;indices+=3;}
                    }
                }
            }
            list->flags|=2;dirty=1;
        }
    }
}

void peParticleContainer::Update(f32 time) {
    if(active) {
        peParticleNode* node=(peParticleNode*)nodes;
        while(node) {
            peParticleNode* next=(peParticleNode*)node->next;
            peEmitterNode* emitter;
            _peParticle* definition=particle;
            emitter=owner;
            char* data=(char*)renderData[swapIndex];
            u8 alive;
            if(!data)alive=0;
            else if(!node->peNode::Update(emitter,time))alive=0;
            else {
                f32 progress=1.0f-(node->time/node->life);
                if(definition->flags&0x10000) {
                    ParticleSpline* spline=definition->angleSpline;
                    f32 value;
                    if(!spline || !(spline->flags&3))value=1.0f;
                    else {
                        f32 difference=spline->time-progress;if(difference<0.0f)difference=-difference;
                        if(difference<=0.00001f)value=spline->value;else value=peSplineGetValue(spline,progress);
                    }
                    node->angle=definition->angle*value;
                }
                node->angle=node->angularSpeed*time+node->angle;
                node->UpdateRenderData(emitter,definition,data,progress);
                alive=1;
            }
            if(!alive){invalidateParticle(node,particle->flags,&displayLists[swapIndex]);RemoveNode(node);}
            node=next;
        }
        DepthSort();
    }
}

struct ParticleAnimation {u32 count;void* textures[1];};
struct ParticleKColor {u8 r,g,b,a;};
struct ParticleRenderData {u8 reserved00[0x34];ParticleKColor color;};
static inline f32 particleFrameFraction(f32 value,u16 frame) {return value-__OSu16tof32(&frame);}
extern "C" {
double fmod(double,double);
void beginSurface__10GSgfxLayerFUs(GSgfxLayer*,u16);
void endSurface__10GSgfxLayerFv(GSgfxLayer*);
}
static inline void setTevKColor(u32 id,ParticleKColor color) {
    u8* layer=(u8*)g_current_layer;
    *(u32*)(layer+0x14f4+id*4)=*(u32*)&color;*(u32*)(layer+0x16f8)|=1<<id;*(u32*)(layer+0x16a8)|=0x10;*(u32*)(layer+0x17b0)|=1<<id;*(u32*)(layer+0x1760)|=0x10;
}
static inline void setupParticleTexture(u8 unit,void* texture,u32 flags) {
    s32 magFilter=0;if(flags&0x100)magFilter=2;
    s32 wrapS=(flags>>12)&3;s32 wrapT=(flags>>14)&3;
    s32 minFilter=0;if(flags&0x80)minFilter=2;
    particleEngineSetupTexture(unit,texture,wrapS,wrapT,minFilter,magFilter);
}
void peParticleNode::Start(peEmitterNode* emitter,_peParticle* definition,GSgfxDL* list,_EmitParams* params) {
    u32 flags=definition->flags;
    u32 extended=(flags>>25)&1;
    if((list->flags&1)==1) {
        peNode::Start(emitter,params);
        reserved35=0;
        live=1;
        f32 random=HSD_Randf();
        width=definition->rangeX*random;
        height=definition->rangeY*random;
        width=width+definition->sizeX;
        height=height+definition->sizeY;
        if(flags&0x40)rotation=6.2831855f*HSD_Randf();
        else rotation=0.0f;
        if((flags&0x20)&&HSD_Randf()<0.5f)reserved35|=1;
        angle=definition->angle;
        angularSpeed=definition->angularRange*HSD_Randf()+definition->angularMin;
        if((flags&0x300000)==0x300000) {
            u16 frames=*(u32*)definition->texture;
            f32 scaled=__OSu16tof32(&frames)*HSD_Randf();
            texture=__OSf32tou8(scaled);
        } else texture=0;
        u16 slot=(u16)(sortIndex<<2);
        u16 vertex=index*(u8)((extended!=0)+13);
        u16* indices=(list->flags&1)?(u16*)(list->data+(slot*list->stride)+3):0;
        u16 i=0;
        if(extended) {
            for(;i<4;++i){u16 uv=i*2;indices[0]=vertex+i*3;indices[1]=vertex;indices[2]=vertex;indices[3]=uv;indices+=4;}
        } else {
            for(;i<4;++i){u16 uv=i*2;indices[0]=vertex+i*3;indices[1]=vertex;indices[2]=uv;indices+=3;}
        }
        list->flags|=2;
    }
}

peParticleContainer::peParticleContainer(peEmitterNode* emitter,_peParticle* definition,u16 maximum):peRenderContainer(emitter,0x50,maximum,(definition->flags&0x2000000)?&g_ext_vertex_format:&g_vertex_format,(GSgfxPrimType)0x80,4,(definition->flags&0x2000000)?0x38:0x34,(definition->flags>>26)&1) {
    sorted=0;
    particle=definition;
    _peParticle* texture=particle;
    s16 sv0,sv1,sv2,sv3;
    sv0=texture->u0;
    sv1=texture->v0;
    f32 fu0=__OSs16tof32(&sv0)/1024.0f;
    f32 fv0=__OSs16tof32(&sv1)/1024.0f;
    sv2=texture->u1;
    f32 fu1=__OSs16tof32(&sv2)/1024.0f;
    sv3=texture->v1;
    f32 fv1=__OSs16tof32(&sv3)/1024.0f;
    uv[0]=fu1;uv[1]=fv1;uv[2]=fu0;uv[3]=fv1;uv[4]=fu0;uv[5]=fv0;uv[6]=fu1;uv[7]=fv0;
    DCFlushRange(uv,0x20);
    if(particle->flags&0x80000)sorted=(peParticleNode**)new peParticleNode*[maximum];
    peParticleNode* node=(peParticleNode*)freeNodes;
    u16 slot=0;
    while(node){node->index=slot;node->sortIndex=slot;if(sorted)sorted[slot]=node;node=(peParticleNode*)node->next;++slot;}
    g_particle_debug_stats.node+=0x7c;g_particle_debug_stats.total+=0x7c;
}

#include <dolphin/gx/GXVert.h>
extern "C" double fmod(double, double);
extern "C" void beginSurface__10GSgfxLayerFUs(GSgfxLayer*, u16);
extern "C" void endSurface__10GSgfxLayerFv(GSgfxLayer*);
struct ParticleColor {
    union { struct { u8 r,g,b,a; } channels; u32 word; };
    ParticleColor() {}
};
static inline void particleSetKColor(u8 index, ParticleColor color) {
    u8* layer=(u8*)g_current_layer;
    *(ParticleColor*)(layer+0x14f4+index*4)=color;
    *(u32*)(layer+0x16f8)|=1<<index;
    *(u32*)(layer+0x16a8)|=0x10;
    *(u32*)(layer+0x17b0)|=1<<index;
    *(u32*)(layer+0x1760)|=0x10;
}
static inline s32 particleWrap(u32 flags,u32 mask) { s32 mode=0; if(flags&mask)mode=2; return mode; }
static inline void particleSetupFrameTexture(u8 unit,void* image,s32 filterS,s32 filterT,u32 flags,s32 wrapT) {
    s32 wrapS=0;
    if(flags&0x80)wrapS=2;
    particleEngineSetupTexture(unit,image,filterS,filterT,wrapS,wrapT);
}
static inline ParticleColor particleRenderColor(char* data,u16 index) {
    data+=index*0x38;
    return *(ParticleColor*)(data+0x34);
}
void peParticleNode::Render(_peParticle* definition,GSgfxDL* list,char* data) {
    u32 flags=definition->flags;
    u32* animation=(u32*)definition->texture;
    u32 extended=(flags>>25)&1;
    u16 current=texture;
    if(data && (list->flags&1)==1) {
        if(flags&0x400000) {
            u16 count=*animation;
            f32 limit=__OSu16tof32(&count);
            u32 blend=(flags>>23)&1;
            if(blend)limit-=1.0f;
            f32 frame;
            if(flags&0x1000000)frame=limit*(life-time)/definition->frameDuration;
            else frame=definition->frameDuration*(limit*(1.0f-time/life));
            u16 initial=current;
            f32 value=fmod(frame+__OSu16tof32(&initial),limit);
            current=__OSf32tou16(value)%(u16)*animation;
            if(blend) {
                u16 whole=current;
                f32 remainder=value;
                remainder-=__OSu16tof32(&whole);
                u8 fraction=__OSf32tou8(255.0f*remainder);
                ParticleColor color;
                color.channels.r=color.channels.g=color.channels.b=color.channels.a=fraction;
                particleSetKColor(0,color);
                if(extended) {
                    ParticleColor next=particleRenderColor(data,index);
                    color.channels.r=next.channels.r;
                    color.channels.g=next.channels.g;
                    color.channels.b=next.channels.b;
                    color.channels.a=next.channels.a;
                    particleSetKColor(1,color);
                }
                void* image=(void*)animation[current+2];
                s32 wrapT=particleWrap(flags,0x100);
                particleSetupFrameTexture(1,image,(flags>>12)&3,(flags>>14)&3,flags,wrapT);
            }
        }
        void* image=(void*)animation[current+1];
        s32 wrapT=particleWrap(flags,0x100);
        particleSetupFrameTexture(0,image,(flags>>12)&3,(flags>>14)&3,flags,wrapT);
        beginSurface__10GSgfxLayerFUs(g_current_layer,4);
        u16 vertex=(sortIndex*4)&0xfffc;
        u16* indices=(list->flags&1)?(u16*)(list->data+vertex*list->stride+3):0;
        u16 remaining=4;
        volatile PPCWGPipe* fifo=&GXWGFifo;
        if(extended) {
            for(;remaining--;) {
                fifo->u16=indices[0];fifo->u16=indices[1];fifo->u16=indices[2];fifo->u16=indices[3];indices+=4;
            }
        } else {
            for(;remaining--;) {
                fifo->u16=indices[0];fifo->u16=indices[1];fifo->u16=indices[2];indices+=3;
            }
        }
        endSurface__10GSgfxLayerFv(g_current_layer);
    }
}

extern "C" {
extern Vec g_CameraPosition,g_CameraUpDir,g_CameraSideDir,g_CameraLookDir,xAxisVector,yAxisVector,zAxisVector;
extern void* g_currentBound;
extern f32 __float_nan[];
f64 atan2(f64,f64);
void EulerToQuat(Vec*,Quaternion*);
void GSboundAddPoint(void*,f32,f32,f32);
}
struct ParticleTransform {Vec position;Quaternion rotation;Vec scale;};

struct ParticleData {Vec vertices[4];u32 color,extraColor;};
extern "C" void peColorSplineGetValue(ParticleColor*,void*,f32);
static inline s32 particleFloatClass(f32 x) {
    union {f32 value;s32 bits;} v;v.value=x;
    s32 result;
    switch(v.bits&0x7f800000) {
    case 0x7f800000:if(v.bits&0x7fffff)result=1;else result=2;break;
    case 0:if(v.bits&0x7fffff)result=5;else result=3;break;
    default:result=4;break;
    }
    return result;
}
static inline f32 particleSpline(ParticleSpline* spline,f32 progress) {
    if(!spline || !(spline->flags&3))return 1.0f;
    f32 difference=spline->time-progress;
    if(difference<0.0f)difference=-difference;
    if(difference<=0.00001f)return spline->value;
    return peSplineGetValue(spline,progress);
}
void peParticleNode::UpdateRenderData(peEmitterNode* emitter,_peParticle* definition,char* data,f32 progress) {
    Mtx m438,m408,m3d8,m3a8,m378,m348,m318,m2e8,m2b8,m288,m258,m228,m1f8,m1c8,m198;
    Vec right,up,normal,offset,work,center;
    Quaternion orientation,basis;
    Vec angles;
    Quaternion inverseRight,inverseUp;
    Vec scaledUp,cameraWork,cameraDelta,toCamera,crossRight,crossUp,rotatedRight,rotatedUp,crossNormal,localRight,localUp,scaledRight,scaledUpResult,corner1,corner2,corner3;
    Quaternion inverseRightResult,inverseUpResult;
    ParticleColor color;
    u32 flags=definition->flags;
    u32 extended=(flags>>25)&1;
    f32 baseAngle;
    f32 redValue,greenValue,blueValue,alphaValue;
    ParticleTransform* transform=(ParticleTransform*)this->transform;
f32 cx=position.x*transform->scale.x;
f32 cy=position.y*transform->scale.y;
f32 cz=position.z*transform->scale.z;
center.x=cx;center.y=cy;center.z=cz;
    PSMTXQuat(m438,&transform->rotation);
    PSMTXMultVecSR(m438,&center,&center);
    PSVECAdd(&center,&((ParticleTransform*)this->transform)->position,&center);

    if(flags&0x200) {
        if(flags&0x20000) {
            PSVECSubtract(&g_CameraPosition,&center,&toCamera);
            normal=toCamera;
            PSVECNormalize(&normal,&normal);
            PSVECCrossProduct(&normal,&g_CameraUpDir,&crossRight);
            right=crossRight;
            PSVECNormalize(&right,&right);
            if(flags&0x400) {
                normal.y=0.0f;PSVECNormalize(&normal,&normal);
                up.x=0.0f;up.y=1.0f;up.z=0.0f;
            } else {PSVECCrossProduct(&right,&normal,&crossUp);up=crossUp;}
        } else {
            if(flags&0x400)up=yAxisVector;else up=g_CameraUpDir;
            right=g_CameraSideDir;
        }
        baseAngle=definition->yaw;
    } else {
        C_QUATRotAxisRad(&orientation,&yAxisVector,definition->yaw);
        C_QUATRotAxisRad(&basis,&zAxisVector,definition->roll);
        PSQUATMultiply(&basis,&orientation,&basis);
        PSMTXQuat(m228,&basis);PSMTXMultVecSR(m228,&xAxisVector,&rotatedRight);right=rotatedRight;
        PSMTXQuat(m1f8,&basis);PSMTXMultVecSR(m1f8,&yAxisVector,&rotatedUp);up=rotatedUp;
        if(emitter->emitter->flags&0x400) {
            f32 vx=velocity.x; f32 vy=velocity.y; f32 vz=velocity.z;
            f32 horizontal=vx*vx+vz*vz;
            if(horizontal>0.0f) {
                f64 guess=__frsqrte(horizontal);
                guess=0.5*guess*(3.0-(f64)horizontal*(guess*guess));
                guess=0.5*guess*(3.0-(f64)horizontal*(guess*guess));
                guess=0.5*guess*(3.0-(f64)horizontal*(guess*guess));
                horizontal=(f32)((f64)horizontal*guess);
            } else if((f64)horizontal<0.0)horizontal=__float_nan[0];
            else if(particleFloatClass(horizontal)==1)horizontal=__float_nan[0];
            angles.x=atan2(-vy,horizontal);
            angles.y=atan2(vx,vz);angles.z=0.0f;
            EulerToQuat(&angles,&orientation);
            PSMTXQuat(m408,&orientation);PSMTXMultVecSR(m408,&right,&right);
            PSMTXQuat(m3d8,&orientation);PSMTXMultVecSR(m3d8,&up,&up);
        }
        PSMTXQuat(m3a8,&((ParticleTransform*)this->transform)->rotation);PSMTXMultVecSR(m3a8,&right,&right);
        PSMTXQuat(m378,&((ParticleTransform*)this->transform)->rotation);PSMTXMultVecSR(m378,&up,&up);
        baseAngle=0.0f;
    }
    PSVECCrossProduct(&up,&right,&crossNormal);normal=crossNormal;

    if(reserved35&1)baseAngle-=(this->rotation+angle);
    else baseAngle+=(this->rotation+angle);
    u32 rotateBefore=flags&0x10;
    if(rotateBefore) {
        f32 magnitude;if(baseAngle<0.0f)magnitude=-baseAngle;else magnitude=baseAngle;
        if(magnitude>0.00001f) {
            C_QUATRotAxisRad(&orientation,&normal,baseAngle);
            PSMTXQuat(m348,&orientation);PSMTXMultVecSR(m348,&up,&up);
            PSMTXQuat(m318,&orientation);PSMTXMultVecSR(m318,&right,&right);
        }
    }
    PSQUATInverse(&((ParticleTransform*)this->transform)->rotation,&inverseRightResult);
    inverseRight=inverseRightResult;
    PSMTXQuat(m1c8,&inverseRight);PSMTXMultVecSR(m1c8,&right,&localRight);work=localRight;
    transform=(ParticleTransform*)this->transform;
    work.x*=transform->scale.x;work.y*=transform->scale.y;work.z*=transform->scale.z;
    PSMTXQuat(m2e8,&transform->rotation);PSMTXMultVecSR(m2e8,&work,&work);
    PSVECScale(&right,&right,PSVECDotProduct(&right,&work));
    PSQUATInverse(&((ParticleTransform*)this->transform)->rotation,&inverseUpResult);
    inverseUp=inverseUpResult;
    PSMTXQuat(m198,&inverseUp);PSMTXMultVecSR(m198,&up,&localUp);work=localUp;
    transform=(ParticleTransform*)this->transform;
    work.x*=transform->scale.x;work.y*=transform->scale.y;work.z*=transform->scale.z;
    PSMTXQuat(m2b8,&transform->rotation);PSMTXMultVecSR(m2b8,&work,&work);
    PSVECScale(&up,&up,PSVECDotProduct(&up,&work));
    PSVECScale(&right,&right,width*particleSpline(definition->widthSpline,progress));
    PSVECScale(&up,&up,height*particleSpline(definition->heightSpline,progress));
    if(!rotateBefore) {
        f32 magnitude;if(baseAngle<0.0f)magnitude=-baseAngle;else magnitude=baseAngle;
        if(magnitude>0.00001f) {
            C_QUATRotAxisRad(&orientation,&normal,baseAngle);
            PSMTXQuat(m288,&orientation);PSMTXMultVecSR(m288,&up,&up);
            PSMTXQuat(m258,&orientation);PSMTXMultVecSR(m258,&right,&right);
        }
    }
    bool offsetEnabled=(flags&0x40000)!=0;
    if(offsetEnabled) {
        PSVECScale(&right,&scaledRight,definition->offsetX);offset=scaledRight;
        PSVECScale(&up,&scaledUpResult,definition->offsetY);scaledUp=scaledUpResult;
        PSVECAdd(&offset,&scaledUp,&offset);
    }
    ParticleData* output;
    if(extended)output=(ParticleData*)(data+index*0x38);
    else output=(ParticleData*)(data+index*0x34);
    PSVECSubtract(&center,&g_CameraPosition,&cameraDelta);
    cameraWork=cameraDelta;
    depth=PSVECDotProduct(&g_CameraLookDir,&cameraWork);
    // Keep the original z-component read ahead of the x/y stores.
    f32 nz = -((volatile Vec*)&right)->z;
    f32 nx = -right.x;
    f32 ny = -right.y;
    work.x = nx;
    work.y = ny;
    work.z = nz;
    PSVECSubtract(&work,&up,&work);
    if(offsetEnabled)PSVECAdd(&work,&offset,&work);
    PSVECAdd(&work,&center,&work);
    output->vertices[0].x=work.x;output->vertices[0].y=work.y;output->vertices[0].z=work.z;
    if(g_currentBound)GSboundAddPoint(g_currentBound,work.x,work.y,work.z);
    PSVECSubtract(&right,&up,&corner1);work=corner1;
    if(offsetEnabled)PSVECAdd(&work,&offset,&work);
    PSVECAdd(&work,&center,&work);
    output->vertices[1].x=work.x;output->vertices[1].y=work.y;output->vertices[1].z=work.z;
    if(g_currentBound)GSboundAddPoint(g_currentBound,work.x,work.y,work.z);
    PSVECAdd(&right,&up,&corner2);work=corner2;
    if(offsetEnabled)PSVECAdd(&work,&offset,&work);
    PSVECAdd(&work,&center,&work);
    output->vertices[2].x=work.x;output->vertices[2].y=work.y;output->vertices[2].z=work.z;
    if(g_currentBound)GSboundAddPoint(g_currentBound,work.x,work.y,work.z);
    PSVECSubtract(&up,&right,&corner3);work=corner3;
    if(offsetEnabled)PSVECAdd(&work,&offset,&work);
    PSVECAdd(&work,&center,&work);
    output->vertices[3].x=work.x;output->vertices[3].y=work.y;output->vertices[3].z=work.z;
    if(g_currentBound)GSboundAddPoint(g_currentBound,work.x,work.y,work.z);
    peColorSplineGetValue(&color,definition->colorSpline,progress);
    u8 red=color.channels.r;
    redValue=emitter->color[0]*__OSu8tof32(&red);
    OSf32tou8(&redValue,&color.channels.r);
    u8 green=color.channels.g;
    greenValue=emitter->color[1]*__OSu8tof32(&green);
    OSf32tou8(&greenValue,&color.channels.g);
    u8 blue=color.channels.b;
    blueValue=emitter->color[2]*__OSu8tof32(&blue);
    OSf32tou8(&blueValue,&color.channels.b);
    alphaValue=(255.0f*emitter->color[3])*particleSpline(definition->alphaSpline,progress);
    color.channels.a=__OSf32tou8(alphaValue);
    output->color=*(u32*)&color;
    if(extended) {peColorSplineGetValue(&color,definition->extraColorSpline,progress);output->extraColor=*(u32*)&color;}
}
