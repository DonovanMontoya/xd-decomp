#include <game/pxdvs/GSAPI/GSparticle/peParticlePrivate.hpp>
#include <dolphin/os/OSFastCast.h>
extern "C" f32 HSD_Randf();
extern "C" GSgfxVF g_vertex_format,g_ext_vertex_format;
extern "C" void DCFlushRange(void*,u32);
static inline void invalidateParticle(peParticleNode* node,u32 flags,GSgfxDL* list) {
    u16* indices;
    u32 extended=(flags>>25)&1;
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
void peParticleNode::Render(_peParticle* definition,GSgfxDL* list,char* data) {
    u32 flags=definition->flags;
    ParticleAnimation* animation=(ParticleAnimation*)definition->texture;
    u32 extended=(flags>>25)&1;
    u16 current=texture;
    if(data!=0&&(list->flags&1)==1) {
        if(flags&0x400000) {
            u16 count=animation->count;
            f32 span=__OSu16tof32(&count);
            u32 blend=(flags>>23)&1;
            if(blend)span-=1.0f;
            f32 time;
            if(flags&0x1000000)time=span*(life-this->time)/definition->frameDuration;
            else time=definition->frameDuration*(span*(1.0f-this->time/life));
            u16 frame=current;
            f32 value=fmod(time+__OSu16tof32(&frame),span);
            current=__OSf32tou16(value)%(u16)animation->count;
            if(blend) {
                u16 whole=current;
                u8 fraction=__OSf32tou8(255.0f*(value-__OSu16tof32(&whole)));
                ParticleKColor color;
                color.a=fraction;color.b=fraction;color.g=fraction;color.r=fraction;
                setTevKColor(0,color);
                if(extended) {
                    ParticleKColor source=((ParticleRenderData*)(data+index*sizeof(ParticleRenderData)))->color;
                    color.r=source.r;color.g=source.g;color.b=source.b;color.a=source.a;
                    setTevKColor(1,color);
                }
                setupParticleTexture(1,animation->textures[current+1],flags);
            }
        }
        setupParticleTexture(0,animation->textures[current],flags);
        beginSurface__10GSgfxLayerFUs(g_current_layer,4);
        u16 vertex=sortIndex*4;
        u16* vertices=(list->flags&1)?(u16*)(list->data+(vertex*list->stride)+3):0;
        u16 n=4;
        volatile u16* pipe=(volatile u16*)0xcc008000;
        if(extended) {
            while(n--){*pipe=vertices[0];*pipe=vertices[1];*pipe=vertices[2];*pipe=vertices[3];vertices+=4;}
        } else {
            while(n--){*pipe=vertices[0];*pipe=vertices[1];*pipe=vertices[2];vertices+=3;}
        }
        endSurface__10GSgfxLayerFv(g_current_layer);
    }
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
            for(;i<4;++i){s16 uv=i*2;indices[0]=vertex+i*3;indices[1]=vertex;indices[2]=vertex;indices[3]=uv;indices+=4;}
        } else {
            for(;i<4;++i){s16 uv=i*2;indices[0]=vertex+i*3;indices[1]=vertex;indices[2]=uv;indices+=3;}
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
