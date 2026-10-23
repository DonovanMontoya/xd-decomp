#include <game/pxdvs/GSAPI/GSparticle/peDistortionPrivate.hpp>
#include <dolphin/os/OSFastCast.h>
#include <dolphin/os.h>
#include <libc/math.h>
static inline f32 spline(ShapeSpline *s,f32 t) {
 if(!s || !(s->flags&3))return 1.0f;
 f32 d=s->time-t;if(d<0)d=-d;
 return d<=0.00001f?s->value:peSplineGetValue(s,t);
}
static inline u32 &layerWord(u32 offset) {return *(u32*)((u8*)g_current_layer+offset);}
static inline u8 &layerByte(u32 offset) {return *((u8*)g_current_layer+offset);}
static inline void invalidate(peDistortionNode *node,GSgfxDL *list) {
 u16 vertex=node->index*4;
 u16 *indices=(list->flags&1)?(u16*)(list->data+(vertex*list->stride)+3):0;
 u16 vertices=4;while(vertices--) {indices[0]=0xffff;indices[1]=0xffff;indices[2]=0xffff;indices+=3;}list->flags|=2;
}
void peDistortionContainer::Stop() {
 if(active) {
  PreUpdate();active=0;peDistortionNode *node=(peDistortionNode*)nodes;u32 flags=owner->emitter->flags;
  if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)1,false);
  if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)3,false);
  if(flags&0x2000000)SetLayerVisibility((GSgfxLayerID)5,false);
  while(node) {invalidate(node,&displayLists[swapIndex]);node=(peDistortionNode*)node->next;}
  RemoveAll();ResetSwap();
 }
}
static inline u8 visible(peDistortionContainer *c) {
 if(!c->active)return 0;u32 flags=c->definition->flags;
 if(!c->count||g_render_pass!=1)return 0;
 switch(layerWord(0x28)) {case 1:if(!(flags&0x2000))return 0;break;case 3:if(flags&0x10)return 0;break;case 5:if(!(flags&0x10))return 0;break;default:return 0;}return 1;
}
void peDistortionContainer::Render() {
 if(active&&visible(this)) {
  ResolveMultipleSwap();u32 flags=definition->flags;
  if(flags&0x100){layerWord(0xd8c)=2;layerWord(0x16b8)|=2;layerWord(0x16a8)|=2;layerWord(0x1770)|=2;layerWord(0x1760)|=2;}
  else{layerWord(0xd8c)=0;layerWord(0x16b8)|=2;layerWord(0x16a8)|=2;layerWord(0x1770)|=2;layerWord(0x1760)|=2;}
  layerWord(0x165c)=0;layerWord(0x1660)=3;layerWord(0x170c)|=8;layerWord(0x16a8)|=0x40;layerWord(0x17c4)|=8;layerWord(0x1760)|=0x40;
  layerByte(0x1656)=1;layerByte(0x1657)=0;layerByte(0x1658)=0;layerWord(0x170c)|=4;layerWord(0x16a8)|=0x40;layerWord(0x17c4)|=4;layerWord(0x1760)|=0x40;
  layerWord(0x1664)=7;layerByte(0x1670)=0;layerWord(0x1668)=0;layerWord(0x166c)=7;layerByte(0x1671)=0;layerByte(0x1672)=1;
  layerWord(0x170c)|=0x10;layerWord(0x16a8)|=0x40;layerWord(0x17c4)|=0x10;layerWord(0x1760)|=0x40;
  particleEngineSetupBlendMode(0);particleEngineSetupTevStages(0,0,0);
  u32 wrapT=0;if(flags&0x40)wrapT=2;u32 wrapS=0;if(flags&0x20)wrapS=2;
  particleEngineSetupTexture(0,definition->texture,flags&3,(flags>>2)&3,wrapS,wrapT);
  GSgfxDL *list=&displayLists[swapIndex];GSgfxVF *format=(list->flags&1)?(GSgfxVF*)list->reserved:0;u8 *data=renderData[swapIndex];
  GSgfxVFSetArray(format,9,3,data,4,renderBytes);GSgfxVFSetArray(format,11,3,data+0x30,4,renderBytes);GSgfxVFSetArray(format,13,3,uv,4,0x20);
  dlDraw__10GSgfxLayerFP7GSgfxDL(g_current_layer,list);MarkForSwap();
 }
}
static inline u8 distortionUpdateNode(peDistortionNode* node,peEmitterNode* emitter,_peDistortion* d,GSgfxDL* list,u8* data,f32 dt) {
 if(!data)return 0;
 if((list->flags&1)!=1)return 0;
 if(!node->peNode::Update(emitter,dt))return 0;
 f32 progress=1.0f-node->time/node->life;
 if(d->flags&0x200)node->angle=d->angle*spline(d->angleSpline,progress);
 node->angle+=node->angularSpeed*dt;
 node->UpdateRenderData(emitter,d,(char*)data,progress);
 return 1;
}
void peDistortionContainer::Update(f32 dt) {
 if(active) {
  peDistortionNode* node=(peDistortionNode*)nodes;
  while(node) {
   peDistortionNode* next=(peDistortionNode*)node->next;
   if(!distortionUpdateNode(node,owner,definition,&displayLists[swapIndex],renderData[swapIndex],dt)) {
    invalidate(node,&displayLists[swapIndex]);RemoveNode(node);
   }
   node=next;
  }
 }
}
static inline void distortionStartNode(peDistortionNode* node,peEmitterNode* emitter,_peDistortion* d,GSgfxDL* list,_EmitParams* params) {
 u32 flags=d->flags;
 if((list->flags&1)==1) {
   node->peNode::Start(emitter,params);f32 random=HSD_Randf();node->width=d->widthRange*random;node->height=d->heightRange*random;node->width+=d->width;node->height+=d->height;
   if(flags&0x80)node->rotation=6.2831855f*HSD_Randf();else node->rotation=0.0f;
   if((flags&0x1000)&&HSD_Randf()<0.5f)node->flags|=1;
   node->angle=d->angle;node->angularSpeed=d->angularRange*HSD_Randf()+d->angularMin;
   u16 base=node->index*13;u16 vertex=node->index*4;
 u16 *indices=(list->flags&1)?(u16*)(list->data+(vertex*list->stride)+3):0;
   indices[0]=base;indices[1]=base;indices[2]=0;indices[3]=base+3;indices[4]=base;indices[5]=2;indices[6]=base+6;indices[7]=base;indices[8]=4;indices[9]=base+9;indices[10]=base;indices[11]=6;list->flags|=2;
 }
}
u16 peDistortionContainer::Emit(u16 requested) {
 if(!active)return 0;
 u16 remaining=CreateNodes(requested);_EmitParams* params=g_emitParams;peDistortionNode* node=(peDistortionNode*)nodes;peDistortionNode* next;u16 created=remaining;
 while(remaining) {
  next=(peDistortionNode*)node->next;
  distortionStartNode(node,owner,definition,&displayLists[swapIndex],params);
  node=next;--remaining;++params;
 }
 return created;
}
void peDistortionContainer::Start() {
 if(!active) {active=1;u32 flags=owner->emitter->flags;InitSwap();
  if(flags&0x800000)SetLayerVisibility((GSgfxLayerID)1,true);if(flags&0x1000000)SetLayerVisibility((GSgfxLayerID)3,true);if(flags&0x2000000)SetLayerVisibility((GSgfxLayerID)5,true);
 }
}
peDistortionContainer::~peDistortionContainer() {g_particle_debug_stats.node-=0x78;g_particle_debug_stats.total-=0x78;}
peDistortionContainer::peDistortionContainer(peEmitterNode *emitter,_peDistortion *d,u16 maximum):peRenderContainer(emitter,0x48,maximum,&g_vertex_format,(GSgfxPrimType)0x80,4,0x34,(d->flags>>14)&1) {
 definition=d;_peDistortion *textureDefinition=definition;uv[0]=textureDefinition->u1;uv[1]=textureDefinition->v1;uv[2]=textureDefinition->u0;uv[3]=textureDefinition->v1;uv[4]=textureDefinition->u0;uv[5]=textureDefinition->v0;uv[6]=textureDefinition->u1;uv[7]=textureDefinition->v0;DCFlushRange(uv,0x20);
 peDistortionNode *node=(peDistortionNode*)freeNodes;s16 index=0;while(node){node->index=index++;node=(peDistortionNode*)node->next;}g_particle_debug_stats.node+=0x78;g_particle_debug_stats.total+=0x78;
}
extern "C" f32 __float_nan[];
struct DistortionColor {u8 r,g,b,a;};
struct DistortionData {Vec vertices[4];u32 color;};
static inline s32 distortionFloatClass(f32 x) {
    union {f32 value;s32 bits;} v;v.value=x;
    s32 result;
    switch(v.bits&0x7f800000) {
    case 0x7f800000:if(v.bits&0x7fffff)result=1;else result=2;break;
    case 0:if(v.bits&0x7fffff)result=5;else result=3;break;
    default:result=4;break;
    }
    return result;
}
static inline f32 distortionSpline(ShapeSpline* spline,f32 progress) {
    if(!spline || !(spline->flags&3))return 1.0f;
    f32 difference=spline->time-progress;
    if(difference<0.0f)difference=-difference;
    if(difference<=0.00001f)return spline->value;
    return peSplineGetValue(spline,progress);
}
void peDistortionNode::UpdateRenderData(peEmitterNode* emitter,_peDistortion* definition,char* data,f32 progress) {
    Mtx m39c,m36c,m33c,m30c,m2dc,m2ac,m27c,m24c,m21c,m1ec,m1bc,m18c,m15c;
    Vec right,up,work,offset,normal,center;
    Quaternion orientation;
    Vec angles;
    Quaternion rotationBefore,rotationAfter,inverseRight,inverseUp;
    Vec unusedCross,toCamera,crossRight,crossNormal,localRight,localUp,scaledRight,scaledUp,corner1,corner2,corner3;
    Quaternion inverseRightResult,inverseUpResult;
    DistortionColor color;
    u32 flags=definition->flags;
    ShapeTransform* transform=(ShapeTransform*)this->transform;
f32 cx=position.x*transform->scale.x;
f32 cy=position.y*transform->scale.y;
f32 cz=position.z*transform->scale.z;
center.x=cx;center.y=cy;center.z=cz;
    PSMTXQuat(m39c,&transform->rotation);
    PSMTXMultVecSR(m39c,&center,&center);
    PSVECAdd(&center,&((ShapeTransform*)this->transform)->position,&center);

    if(flags&0x100) {
        if(flags&0x400) {
            PSVECSubtract(&g_CameraPosition,&center,&toCamera);
            normal=toCamera;
            PSVECNormalize(&normal,&normal);
            PSVECCrossProduct(&normal,&g_CameraUpDir,&crossRight);
            right=crossRight;
            PSVECNormalize(&right,&right);
            PSVECCrossProduct(&normal,&right,&unusedCross);
        } else {
            up=g_CameraUpDir;
            right=g_CameraSideDir;
        }
    } else {
        right=xAxisVector;up=yAxisVector;
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
            else if(distortionFloatClass(horizontal)==1)horizontal=__float_nan[0];
            angles.x=atan2(-vy,horizontal);
            angles.y=atan2(vx,vz);angles.z=0.0f;
            EulerToQuat(&angles,&orientation);
            PSMTXQuat(m36c,&orientation);PSMTXMultVecSR(m36c,&right,&right);
            PSMTXQuat(m33c,&orientation);PSMTXMultVecSR(m33c,&up,&up);
        }
        PSMTXQuat(m30c,&((ShapeTransform*)this->transform)->rotation);PSMTXMultVecSR(m30c,&right,&right);
        PSMTXQuat(m2dc,&((ShapeTransform*)this->transform)->rotation);PSMTXMultVecSR(m2dc,&up,&up);
    }
    PSVECCrossProduct(&up,&right,&crossNormal);normal=crossNormal;

f32 baseAngle=0.0f;
    if(this->flags&1)baseAngle-=(this->rotation+angle);
    else baseAngle+=(this->rotation+angle);
    u32 rotateBefore=flags&0x8000;
    if(rotateBefore) {
        f32 magnitude;if(baseAngle<0.0f)magnitude=-baseAngle;else magnitude=baseAngle;
        if(magnitude>0.00001f) {
            C_QUATRotAxisRad(&rotationBefore,&normal,baseAngle);
            PSMTXQuat(m2ac,&rotationBefore);PSMTXMultVecSR(m2ac,&up,&up);
            PSMTXQuat(m27c,&rotationBefore);PSMTXMultVecSR(m27c,&right,&right);
        }
    }
    PSQUATInverse(&((ShapeTransform*)this->transform)->rotation,&inverseRightResult);
    inverseRight=inverseRightResult;
    PSMTXQuat(m18c,&inverseRight);PSMTXMultVecSR(m18c,&right,&localRight);work=localRight;
    transform=(ShapeTransform*)this->transform;
    work.x*=transform->scale.x;work.y*=transform->scale.y;work.z*=transform->scale.z;
    PSMTXQuat(m24c,&transform->rotation);PSMTXMultVecSR(m24c,&work,&work);
    PSVECScale(&right,&right,PSVECDotProduct(&right,&work));
    PSQUATInverse(&((ShapeTransform*)this->transform)->rotation,&inverseUpResult);
    inverseUp=inverseUpResult;
    PSMTXQuat(m15c,&inverseUp);PSMTXMultVecSR(m15c,&up,&localUp);work=localUp;
    transform=(ShapeTransform*)this->transform;
    work.x*=transform->scale.x;work.y*=transform->scale.y;work.z*=transform->scale.z;
    PSMTXQuat(m21c,&transform->rotation);PSMTXMultVecSR(m21c,&work,&work);
    PSVECScale(&up,&up,PSVECDotProduct(&up,&work));
    PSVECScale(&right,&right,width*distortionSpline(definition->widthSpline,progress));
    PSVECScale(&up,&up,height*distortionSpline(definition->heightSpline,progress));
    if(!rotateBefore) {
        f32 magnitude;if(baseAngle<0.0f)magnitude=-baseAngle;else magnitude=baseAngle;
        if(magnitude>0.00001f) {
            C_QUATRotAxisRad(&rotationAfter,&normal,baseAngle);
            PSMTXQuat(m1ec,&rotationAfter);PSMTXMultVecSR(m1ec,&up,&up);
            PSMTXQuat(m1bc,&rotationAfter);PSMTXMultVecSR(m1bc,&right,&right);
        }
    }
    bool offsetEnabled=(flags&0x800)!=0;
    if(offsetEnabled) {
        PSVECScale(&right,&scaledRight,definition->offsetX);offset=scaledRight;
        PSVECScale(&up,&scaledUp,definition->offsetY);
        offset.x*=scaledUp.x;offset.y*=scaledUp.y;offset.z*=scaledUp.z;
    }
    DistortionData* output=(DistortionData*)(data+index*0x34);
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
    color.b=255;color.g=255;color.r=255;
    color.a=__OSf32tou8((255.0f*emitter->color[3])*distortionSpline(definition->alphaSpline,progress));
    output->color=*(u32*)&color;
}
