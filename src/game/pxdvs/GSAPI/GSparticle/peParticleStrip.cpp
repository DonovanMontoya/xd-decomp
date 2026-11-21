#include <game/pxdvs/GSAPI/GSparticle/peParticleStripPrivate.hpp>
#include <dolphin/os/OSFastCast.h>
#include <dolphin/gx/GXEnum.h>
#include <game/pxdvs/GSAPI/GSmath/GSvec2.hpp>

struct StripVertexPair {
    Vec positions[2];
    u32 color;
    GSvec2 texCoords[2];
};

struct ExtendedStripVertexPair {
    StripVertexPair pair;
    u32 secondColor;
};

static inline u32 &layerWord(u32 offset) {return *(u32*)((u8*)g_current_layer+offset);}
static inline u8 byte(f32 value) {if(value<0)return 0;if(value>255)return 255;return (u8)value;}
static inline s16 shortValue(f32 value) {if(value<-32768)return -32768;if(value>32767)return 32767;return (s16)value;}
static inline f32 spline(PeSpline *s,f32 t) {if(!s||!(s->flags&3))return 1;f32 d=s->time-t;if(d<0)d=-d;return d<=0.00001f?s->value:peSplineGetValue(s,t);}
#pragma opt_unroll_loops off
void peParticleStripContainer::RearrangeIndices() {
    if (active) {
        u16 output = 0, ordinal = 0;
        u32 flags = definition->flags;
        u32 extended = (flags >> 18) & 1;
        if (count >= 2) {
            _peEmitter* emitter = owner->emitter;
            f32 step;
            if (flags & 0x10000) {
                u16 last = count - 1;
                step = 1.0f / __OSu16tof32(&last);
            } else {
                step = emitter->emissionTimeStep;
            }
            u32 mirror = (flags >> 15) & 1;
            u32 reverse = (flags >> 17) & 1;
            u8 vertexStride, indexStep, dataStride;
            if (extended) {
                vertexStride = sizeof(ExtendedStripVertexPair) / sizeof(u32);
                indexStep = 8;
                dataStride = sizeof(ExtendedStripVertexPair);
            } else {
                vertexStride = sizeof(StripVertexPair) / sizeof(u32);
                indexStep = 6;
                dataStride = sizeof(StripVertexPair);
            }
            peParticleStripNode* node = static_cast<peParticleStripNode*>(nodes);
            GSgfxDL* list = &displayLists[swapIndex];
            u8* base = renderData[swapIndex];
            while (node) {
                StripVertexPair* pair = (StripVertexPair*)(base + node->index * dataStride);
                node->sortIndex = output;
                u16 first = node->index * vertexStride;
                u16* indices = (u16*)list->VertexData(0);
                indices += output;
                u16 corner = 0;
                if (extended) {
                    for (; corner < 2; ++corner) {
                        indices[0] = first + corner * 3;
                        indices[1] = first;
                        indices[2] = first;
                        indices[3] = first + corner * 2;
                        indices += 4;
                    }
                } else {
                    for (; corner < 2; ++corner) {
                        indices[0] = first + corner * 3;
                        indices[1] = first;
                        indices[2] = first + corner * 2;
                        indices += 3;
                    }
                }
                f32 value;
                if (reverse) {
                    u16 flipped = count - ordinal - 1;
                    value = __OSu16tof32(&flipped);
                } else {
                    u16 current = ordinal;
                    value = __OSu16tof32(&current);
                }
                if (mirror) {
                    pair->texCoords[0].x = pair->texCoords[1].x = -((value * step) - 1.0f);
                } else {
                    pair->texCoords[0].x = pair->texCoords[1].x = value * step;
                }
                output += indexStep;
                ++ordinal;
                pair->texCoords[0].y = definition->v0;
                pair->texCoords[1].y = definition->v1;
                node = static_cast<peParticleStripNode*>(node->next);
            }
            list->Invalidate();
        }
    }
}
#pragma opt_unroll_loops reset

static inline void invalidate(peParticleStripNode *node,GSgfxDL *list,u32 flags) {
 u8 extended=(flags>>18)&1;u16 *indices=(u16*)((list->flags&1)?list->data+3:0);indices+=node->sortIndex;u16 count=2;
 while(count--){indices[0]=0xffff;indices[1]=0xffff;indices[2]=0xffff;indices+=3;if(extended)*indices++=0xffff;}list->flags|=2;
}
void peParticleStripContainer::Stop() {
 if(active){PreUpdate();active=0;u32 flags=definition->flags;
  if(flags&0x400000)SetLayerVisibility((GSgfxLayerID)1,false);if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)3,false);if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)5,false);
  peParticleStripNode *node=(peParticleStripNode*)nodes;while(node){invalidate(node,&displayLists[swapIndex],definition->flags);node=(peParticleStripNode*)node->next;}RemoveAll();ResetSwap();
 }
}
static inline u8 visible(peParticleStripContainer *c) {
 if(!c->active)return 0;
 u32 flags=c->definition->flags;
 if(c->count<2)return 0;
 if(g_render_pass!=1)return 0;
 switch(layerWord(0x28)){
 case 0:if(flags&0x100000)return 1;break;
 case 2:if(flags&0x200000)return 1;if(!(flags&0x1f00040))return 1;break;
 case 4:if(flags&0x40)return 1;break;
 case 1:if(flags&0x400000)return 1;break;
 case 3:if(flags&0x800000)return 1;break;
 case 5:if(flags&0x1000000)return 1;break;
 default:return 0;}
 return 0;
}
struct StripKColor {u8 r,g,b,a;};
static inline void stripSetTevKColor(u32 id,StripKColor color) {
 u8* layer=(u8*)g_current_layer;
 *(u32*)(layer+0x14f4+id*4)=*(u32*)&color;*(u32*)(layer+0x16f8)|=1<<id;*(u32*)(layer+0x16a8)|=0x10;*(u32*)(layer+0x17b0)|=1<<id;*(u32*)(layer+0x1760)|=0x10;
}
enum StripTextureFilter { STRIP_NEAREST, STRIP_LINEAR = 2 };

static inline StripTextureFilter stripMinFilter(u32 flags) {
    if (flags & 0x10) return STRIP_LINEAR;
    return STRIP_NEAREST;
}

static inline void stripSetupTexture(u32 unit, void* texture, u32 flags) {
    u32 magFilter = STRIP_NEAREST;
    if (flags & 0x20) magFilter = STRIP_LINEAR;
    u32 wrapT = (flags >> 8) & 3;
    particleEngineSetupTexture(unit, texture, 0, wrapT, stripMinFilter(flags), magFilter);
}

void peParticleStripContainer::Render() {
    f32 weight, frameValue;
    if (active && visible(this)) {
        ResolveMultipleSwap();
        u32 flags = definition->flags;
        bool extended = (flags & 0x40000) != 0;
        u8* layer = (u8*)g_current_layer;
        *(u32*)(layer + 0xd8c) = 0;
        *(u32*)(layer + 0x16b8) |= 2;
        *(u32*)(layer + 0x16a8) |= 2;
        *(u32*)(layer + 0x1770) |= 2;
        *(u32*)(layer + 0x1760) |= 2;
        particleEngineSetupBlendMode(flags & 7);

        GSgfxDL* list = &displayLists[swapIndex];
        u8* data = renderData[swapIndex];
        GSgfxVF* format = list->VertexFormat();
        if (extended) {
            GSgfxVFSetArray(format, GX_VA_POS, GX_INDEX16, data, 4, renderBytes);
            GSgfxVFSetArray(format, GX_VA_CLR0, GX_INDEX16, data + offsetof(StripVertexPair, color), 4, renderBytes);
            GSgfxVFSetArray(format, GX_VA_CLR1, GX_INDEX16, data + offsetof(ExtendedStripVertexPair, secondColor), 4, renderBytes);
            GSgfxVFSetArray(format, GX_VA_TEX0, GX_INDEX16, data + offsetof(StripVertexPair, texCoords), 4, renderBytes);
        } else {
            GSgfxVFSetArray(format, GX_VA_POS, GX_INDEX16, data, 4, renderBytes);
            GSgfxVFSetArray(format, GX_VA_CLR0, GX_INDEX16, data + offsetof(StripVertexPair, color), 4, renderBytes);
            GSgfxVFSetArray(format, GX_VA_TEX0, GX_INDEX16, data + offsetof(StripVertexPair, texCoords), 4, renderBytes);
        }

        if (flags & 0x400) {
            StripAnimation* animation = (StripAnimation*)definition->texture;
            u16 current = frame;
            if (flags & 0x1000) {
                u16 count = animation->count;
                f32 span = __OSu16tof32(&count);
                bool blend = (flags & 0x2000) != 0;
                particleEngineSetupTevStages(0, extended, blend);
                if (blend) span -= 1.0f;
                f32 phase;
                if (flags & 0x4000000) {
                    phase = span * (owner->emitter->duration - remaining) / definition->frameRate;
                } else {
                    phase = definition->frameRate * (span * (1.0f - remaining / owner->emitter->duration));
                }
                u16 firstFrame = current;
                frameValue = fmod(phase + __OSu16tof32(&firstFrame), span);
                current = __OSf32tou16(frameValue) % (u16)animation->count;
                if (blend) {
                    u16 whole = current;
                    f32 textureFraction = frameValue;
                    textureFraction -= __OSu16tof32(&whole);
                    weight = 255.0f * textureFraction;
                    u8 fraction = __OSf32tou8(weight);
                    StripKColor color;
                    color.r = color.g = color.b = color.a = fraction;
                    stripSetTevKColor(0, color);
                    stripSetupTexture(1, animation->textures[current + 1], flags);
                }
            } else {
                particleEngineSetupTevStages(0, extended, false);
            }
            stripSetupTexture(0, animation->textures[current], flags);
        } else {
            particleEngineSetupTevStages(0, extended, false);
            u32 magFilter = STRIP_NEAREST;
            if (flags & 0x20) magFilter = STRIP_LINEAR;
            u32 wrapS = 0;
            u32 wrapT = (flags >> 8) & 3;
            particleEngineSetupTexture(0, definition->texture, wrapS, wrapT, stripMinFilter(flags), magFilter);
        }
        dlDraw__10GSgfxLayerFP7GSgfxDL(g_current_layer, &displayLists[swapIndex]);
        MarkForSwap();
    }
}

static inline u8 stripUpdateNode(peParticleStripNode* node,peEmitterNode* emitter,_peParticleStrip* d,GSgfxDL* list,u8* data,f32 dt) {
 if(!data)return 0;
 if((list->flags&1)!=1)return 0;
 if(!node->peNode::Update(emitter,dt))return 0;
 node->UpdateRenderData(emitter,d,(char*)data,1.0f-node->time/node->life);
 return 1;
}
void peParticleStripContainer::Update(f32 dt) {
 if(active){peParticleStripNode *node=(peParticleStripNode*)nodes;
  while(node){peParticleStripNode *next=(peParticleStripNode*)node->next;
   if(!stripUpdateNode(node,owner,definition,&displayLists[swapIndex],renderData[swapIndex],dt)){invalidate(node,&displayLists[swapIndex],definition->flags);RemoveNode(node);}node=next;
  }remaining-=dt;RearrangeIndices();
 }
}
static inline void stripStartNode(peParticleStripNode* node,peEmitterNode* emitter,_peParticleStrip* d,GSgfxDL* list,_EmitParams* params,f32 progress) {
 if((list->flags&1)==1) {
  node->peNode::Start(emitter,params);
  Vec randomSegment;
  Vec segment;
  if(d->flags&0x2000000) {
   PSVECScale(&d->direction,&segment,10.0f*(progress*d->speedRange+d->speedMin));
   f32 z,y,x;
   y=segment.y;z=segment.z;x=segment.x;
   node->segment.x=x;node->segment.y=y;node->segment.z=z;
  } else {
   f32 random=HSD_Randf();
   PSVECScale(&d->direction,&randomSegment,10.0f*(d->speedRange*random+d->speedMin));
   f32 z,y,x;
   y=randomSegment.y;z=randomSegment.z;x=randomSegment.x;
   node->segment.x=x;node->segment.y=y;node->segment.z=z;
  }
  list->flags|=2;
 }
}
u16 peParticleStripContainer::Emit(u16 requested) {
 if(!active)return 0;u16 left=CreateNodes(requested);_EmitParams *params=g_emitParams;peParticleStripNode *node=(peParticleStripNode*)nodes;peParticleStripNode *next;u16 result=left;u16 created=left;
 while(left){next=(peParticleStripNode*)node->next;u16 ordinal=(*(u16*)((u8*)owner+0x4a)+created)-left;
  stripStartNode(node,owner,definition,&displayLists[swapIndex],params,owner->emitter->emissionTimeStep*__OSu16tof32(&ordinal));
  node=next;--left;++params;
 }return result;
}
static inline f32 stripRandomFrame(u16 frames) {
 return __OSu16tof32(&frames)*HSD_Randf();
}
void peParticleStripContainer::Start() {
 if(!active){active=1;u32 flags=definition->flags;InitSwap();if(flags&0x400000)SetLayerVisibility((GSgfxLayerID)1,true);if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)3,true);if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)5,true);
  if((flags&0xc00)==0xc00){frame=__OSf32tou8(stripRandomFrame(((StripAnimation*)definition->texture)->count));}else frame=0;remaining=owner->emitter->duration;
 }
}
peParticleStripContainer::~peParticleStripContainer(){g_particle_debug_stats.node-=0x60;g_particle_debug_stats.total-=0x60;}
peParticleStripContainer::peParticleStripContainer(peEmitterNode *emitter,_peParticleStrip *d,u16 maximum):peRenderContainer(emitter,sizeof(peParticleStripNode),maximum,(d->flags&0x40000)?&g_ext_vertex_format:&g_vertex_format,(GSgfxPrimType)0x98,2,(d->flags&0x40000)?sizeof(ExtendedStripVertexPair):sizeof(StripVertexPair),(d->flags>>19)&1) {
 definition=d;frame=0xff;peParticleStripNode *node=(peParticleStripNode*)freeNodes;s16 index=0;while(node){node->index=index;node->sortIndex=index;++index;node=(peParticleStripNode*)node->next;}g_particle_debug_stats.node+=0x60;g_particle_debug_stats.total+=0x60;
}
void peParticleStripNode::UpdateRenderData(peEmitterNode *emitter,_peParticleStrip *d,char *data,f32 progress) {
 u32 flags=d->flags;u32 extended=(flags>>18)&1;Mtx matrix;Mtx segmentMatrix;NodeTransform *parent=transform;Vec world,segment;
 Vec offset,half;
 GSgfxColAu8 color;u8 red,green,blue;
 f32 wy=position.y*parent->scale.y;f32 wz=position.z*parent->scale.z;f32 wx=position.x*parent->scale.x;world.x=wx;world.y=wy;world.z=wz;PSMTXQuat(matrix,&parent->rotation);PSMTXMultVecSR(matrix,&world,&world);PSVECAdd(&world,&transform->position,&world);
 StripVertexPair* out;
 if (extended) out = &((ExtendedStripVertexPair*)data)[index].pair;
 else out = &((StripVertexPair*)data)[index];
 parent=transform;f32 sy=this->segment.y*parent->scale.y;f32 sz=this->segment.z*parent->scale.z;f32 sx=this->segment.x*parent->scale.x;segment.x=sx;segment.y=sy;segment.z=sz;PSMTXQuat(segmentMatrix,&parent->rotation);PSMTXMultVecSR(segmentMatrix,&segment,&segment);
 if(flags&0x4000){PSVECScale(&segment,&half,0.5f);offset=half;PSVECSubtract(&world,&offset,&world);}
 out->positions[0]=world;if(g_currentBound)GSboundAddPoint(g_currentBound,world.x,world.y,world.z);PSVECAdd(&world,&segment,&world);out->positions[1]=world;if(g_currentBound)GSboundAddPoint(g_currentBound,world.x,world.y,world.z);
 peColorSplineGetValue(&color,d->colorSpline,progress);red=color.r;color.r=__OSf32tou8(__OSu8tof32(&red)*emitter->color[0]);green=color.g;color.g=__OSf32tou8(__OSu8tof32(&green)*emitter->color[1]);blue=color.b;color.b=__OSf32tou8(__OSu8tof32(&blue)*emitter->color[2]);color.a=__OSf32tou8((255.0f*emitter->color[3])*spline(d->alphaSpline,progress));out->color=*(u32*)&color;
 if(extended){peColorSplineGetValue(&color,d->secondColorSpline,progress);((ExtendedStripVertexPair*)out)->secondColor=*(u32*)&color;}
}
