#include <game/pxdvs/GSAPI/GSparticle/peParticleStripPrivate.hpp>
#include <dolphin/os/OSFastCast.h>
static inline f32 emitterFloat(peEmitterNode *owner,u32 offset) {return *(f32*)((u8*)owner->emitter+offset);}
static inline u32 &layerWord(u32 offset) {return *(u32*)((u8*)g_current_layer+offset);}
static inline u8 byte(f32 value) {if(value<0)return 0;if(value>255)return 255;return (u8)value;}
static inline s16 shortValue(f32 value) {if(value<-32768)return -32768;if(value>32767)return 32767;return (s16)value;}
static inline f32 spline(ShapeSpline *s,f32 t) {if(!s||!(s->flags&3))return 1;f32 d=s->time-t;if(d<0)d=-d;return d<=0.00001f?s->value:peSplineGetValue(s,t);}
#pragma opt_unroll_loops off
void peParticleStripContainer::RearrangeIndices() {
 if(active) {
  u16 output=0,ordinal=0;u32 flags=definition->flags;u32 extended=(flags>>18)&1;
  if(count>=2) {
   f32 *parameters=(f32*)owner->emitter;f32 step;if(flags&0x10000){u16 lastIndex=count-1;step=1.0f/__OSu16tof32(&lastIndex);}else step=parameters[2];
   u32 mirror=(flags>>15)&1;u32 reverse=(flags>>17)&1;
   u8 vertexStride,indexStep,dataStride;
   if(extended){vertexStride=12;indexStep=8;dataStride=0x30;}else{vertexStride=11;indexStep=6;dataStride=0x2c;}
   peParticleStripNode *node=(peParticleStripNode*)nodes;GSgfxDL *list=&displayLists[swapIndex];u8 *base=renderData[swapIndex];
   while(node) {
    f32 *data=(f32*)(base+node->index*dataStride);node->sortIndex=output;u16 first=node->index*vertexStride;
    u16 *indices=(u16*)((list->flags&1)?list->data+3:0);indices+=output;
    u16 j=0;
    if(extended) {for(;j<2;j++){indices[0]=first+j*3;indices[1]=first;indices[2]=first;indices[3]=first+j*2;indices+=4;}}
    else {for(;j<2;j++){indices[0]=first+j*3;indices[1]=first;indices[2]=first+j*2;indices+=3;}}
    f32 value;if(reverse){u16 flipped=count-ordinal-1;value=__OSu16tof32(&flipped);}else{u16 current=ordinal;value=__OSu16tof32(&current);}
    if(mirror)data[7]=data[9]=-((value*step)-1.0f);else data[7]=data[9]=value*step;
    output+=indexStep;++ordinal;data[8]=definition->v0;data[10]=definition->v1;node=(peParticleStripNode*)node->next;
   }list->flags|=2;
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
static inline void stripSetupTexture(u8 unit,void* texture,u32 flags) {
 s32 magFilter=0;if(flags&0x20)magFilter=2;
 s32 wrapS=0;s32 wrapT=(flags>>8)&3;
 s32 minFilter=0;if(flags&0x10)minFilter=2;
 particleEngineSetupTexture(unit,texture,wrapS,wrapT,minFilter,magFilter);
}
void peParticleStripContainer::Render() {
 if(active&&visible(this)) {
  ResolveMultipleSwap();u32 flags=definition->flags;u32 extended=(flags>>18)&1;
  {u8* layer=(u8*)g_current_layer;*(u32*)(layer+0xd8c)=0;*(u32*)(layer+0x16b8)|=2;*(u32*)(layer+0x16a8)|=2;*(u32*)(layer+0x1770)|=2;*(u32*)(layer+0x1760)|=2;}
  particleEngineSetupBlendMode(flags&7);
  GSgfxDL *list=&displayLists[swapIndex];u8 *data=renderData[swapIndex];GSgfxVF *format=(list->flags&1)?(GSgfxVF*)list->reserved:0;
  if(extended) {
   GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x18,4,renderBytes);GSgfxVFSetArray(format,12,3,data+0x2c,4,renderBytes);GSgfxVFSetArray(format,13,3,data+0x1c,4,renderBytes);
  } else {
   GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x18,4,renderBytes);GSgfxVFSetArray(format,13,3,data+0x1c,4,renderBytes);
  }
  if(flags&0x400) {
   StripAnimation *animation=(StripAnimation*)definition->texture;u16 current=frame;
   if(flags&0x1000) {
    u16 count=animation->count;f32 span=__OSu16tof32(&count);u32 blend=(flags>>13)&1;particleEngineSetupTevStages(0,extended,blend);if(blend)span-=1.0f;
    f32 time;
    if(flags&0x4000000)time=span*(emitterFloat(owner,0x28)-remaining)/definition->frameRate;else time=definition->frameRate*(span*(1.0f-remaining/emitterFloat(owner,0x28)));
    u16 frame0=current;f32 value=fmod(time+__OSu16tof32(&frame0),span);current=__OSf32tou16(value)%(u16)animation->count;
    if(blend){
     u16 whole=current;u8 fraction=__OSf32tou8(255.0f*(value-__OSu16tof32(&whole)));
     StripKColor color;color.a=fraction;color.b=fraction;color.g=fraction;color.r=fraction;stripSetTevKColor(0,color);
     stripSetupTexture(1,animation->textures[current+1],flags);
    }
   }else particleEngineSetupTevStages(0,extended,0);
   stripSetupTexture(0,animation->textures[current],flags);
  }else{particleEngineSetupTevStages(0,extended,0);stripSetupTexture(0,definition->texture,flags);}
  dlDraw__10GSgfxLayerFP7GSgfxDL(g_current_layer,&displayLists[swapIndex]);MarkForSwap();
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
  stripStartNode(node,owner,definition,&displayLists[swapIndex],params,emitterFloat(owner,8)*__OSu16tof32(&ordinal));
  node=next;--left;++params;
 }return result;
}
static inline f32 stripRandomFrame(u16 frames) {
 return __OSu16tof32(&frames)*HSD_Randf();
}
void peParticleStripContainer::Start() {
 if(!active){active=1;u32 flags=definition->flags;InitSwap();if(flags&0x400000)SetLayerVisibility((GSgfxLayerID)1,true);if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)3,true);if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)5,true);
  if((flags&0xc00)==0xc00){frame=__OSf32tou8(stripRandomFrame(((StripAnimation*)definition->texture)->count));}else frame=0;remaining=emitterFloat(owner,0x28);
 }
}
peParticleStripContainer::~peParticleStripContainer(){g_particle_debug_stats.node-=0x60;g_particle_debug_stats.total-=0x60;}
peParticleStripContainer::peParticleStripContainer(peEmitterNode *emitter,_peParticleStrip *d,u16 maximum):peRenderContainer(emitter,0x40,maximum,(d->flags&0x40000)?&g_ext_vertex_format:&g_vertex_format,(GSgfxPrimType)0x98,2,(d->flags&0x40000)?0x30:0x2c,(d->flags>>19)&1) {
 definition=d;frame=0xff;peParticleStripNode *node=(peParticleStripNode*)freeNodes;s16 index=0;while(node){node->index=index;node->sortIndex=index;++index;node=(peParticleStripNode*)node->next;}g_particle_debug_stats.node+=0x60;g_particle_debug_stats.total+=0x60;
}
void peParticleStripNode::UpdateRenderData(peEmitterNode *emitter,_peParticleStrip *d,char *data,f32 progress) {
 u32 flags=d->flags;u32 extended=(flags>>18)&1;Mtx matrix;Mtx segmentMatrix;ShapeTransform *parent=(ShapeTransform*)transform;Vec world,segment;
 Vec offset,half;
 u8 color[4];u8 red,green,blue;
 f32 wy=position.y*parent->scale.y;f32 wz=position.z*parent->scale.z;f32 wx=position.x*parent->scale.x;world.x=wx;world.y=wy;world.z=wz;PSMTXQuat(matrix,&parent->rotation);PSMTXMultVecSR(matrix,&world,&world);PSVECAdd(&world,&((ShapeTransform*)transform)->position,&world);
 char *out;if(extended)out=data+index*0x30;else out=data+index*0x2c;
 parent=(ShapeTransform*)transform;f32 sy=this->segment.y*parent->scale.y;f32 sz=this->segment.z*parent->scale.z;f32 sx=this->segment.x*parent->scale.x;segment.x=sx;segment.y=sy;segment.z=sz;PSMTXQuat(segmentMatrix,&parent->rotation);PSMTXMultVecSR(segmentMatrix,&segment,&segment);
 if(flags&0x4000){PSVECScale(&segment,&half,0.5f);offset=half;PSVECSubtract(&world,&offset,&world);}
 *(Vec*)out=world;if(g_currentBound)GSboundAddPoint(g_currentBound,world.x,world.y,world.z);PSVECAdd(&world,&segment,&world);*(Vec*)(out+0xc)=world;if(g_currentBound)GSboundAddPoint(g_currentBound,world.x,world.y,world.z);
 peColorSplineGetValue(color,d->colorSpline,progress);red=color[0];color[0]=__OSf32tou8(__OSu8tof32(&red)*emitter->color[0]);green=color[1];color[1]=__OSf32tou8(__OSu8tof32(&green)*emitter->color[1]);blue=color[2];color[2]=__OSf32tou8(__OSu8tof32(&blue)*emitter->color[2]);color[3]=__OSf32tou8((255.0f*emitter->color[3])*spline(d->alphaSpline,progress));*(u32*)(out+0x18)=*(u32*)color;
 if(extended){peColorSplineGetValue(color,d->secondColorSpline,progress);*(u32*)(out+0x2c)=*(u32*)color;}
}
