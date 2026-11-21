#include <game/pxdvs/GSAPI/GSparticle/peShapePrivate.hpp>
#include <game/pxdvs/GSAPI/GSgfxM/c_interface.hpp>
#include <dolphin/gx/GXEnum.h>
#pragma defer_codegen on

void peShapeNode::Start(peEmitterNode* emitter,_peShape* shape,_EmitParams* params) {
    Vec randomAngles;
    Vec scale;
    u32 flags=shape->flags;
    peNode::Start(emitter,params);
    flips=0;
    PSVECScale(&shape->scaleRange,&scale,HSD_Randf());
    f32 sy=scale.y,sz=scale.z,sx=scale.x;baseScale.x=sx;baseScale.y=sy;baseScale.z=sz;
    PSVECAdd(&baseScale,&shape->scale,&baseScale);
    randomRotation.x=0.0f;randomRotation.y=0.0f;randomRotation.z=0.0f;randomRotation.w=1.0f;
    world.position.x=0.0f;world.position.y=0.0f;world.position.z=0.0f;
    world.rotation.x=0.0f;world.rotation.y=0.0f;world.rotation.z=0.0f;world.rotation.w=1.0f;
    world.scale=unitScaleVector;
    if(!(emitter->emitter->flags&0x400)) {
        EulerToQuat(&shape->rotation,&localRotation);
        if(flags&0x1c7000) {
            if(flags&0x1000){f32 random=HSD_Randf();randomAngles.x=6.2831855f*random;}else randomAngles.x=0.0f;
            if(flags&0x2000)randomAngles.y=6.2831855f*HSD_Randf();else randomAngles.y=0.0f;
            if(flags&0x4000)randomAngles.z=6.2831855f*HSD_Randf();else randomAngles.z=0.0f;
            if((flags&0x40000) && HSD_Randf()<0.5f)flips|=1;
            if((flags&0x80000) && HSD_Randf()<0.5f)flips|=2;
            if((flags&0x100000) && HSD_Randf()<0.5f)flips|=4;
            EulerToQuat(&randomAngles,&randomRotation);
        }
    }
    angularSpeed=shape->angularSpeed;
    if(flags&0x8000)angularSpeed.x*=HSD_Randf();
    if(flags&0x10000)angularSpeed.y*=HSD_Randf();
    if(flags&0x20000)angularSpeed.z*=HSD_Randf();
}

#include <dolphin/os/OSFastCast.h>
static inline f32 shapeSpline(PeSpline* spline,f32 progress) {
    if(!spline || !(spline->flags&3))return 1.0f;
    f32 difference=spline->time-progress;if(difference<0.0f)difference=-difference;
    if(difference<=0.00001f)return spline->value;
    return peSplineGetValue(spline,progress);
}
static inline u8 shapeColorByte(f32 value) {
    return __OSf32tou8(value);
}
extern "C" { extern f32 __float_nan[]; }
static inline s32 shapeFloatClass(f32 x) {
    union {f32 value;s32 bits;} v;v.value=x;
    switch(v.bits&0x7f800000) {
    case 0x7f800000:if(v.bits&0x7fffff)return 1;return 2;
    case 0:if(v.bits&0x7fffff)return 5;return 3;
    default:return 4;
    }
}
static inline f32 shapeSqrt(f32 x) {
    if(x>0.0f) {
        f64 guess=__frsqrte(x);
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        return (f32)((f64)x*guess);
    }
    if((f64)x<0.0)return __float_nan[0];
    if(shapeFloatClass(x)==1)return __float_nan[0];
    return x;
}
static inline f32 shapeU8(u8 value) { return __OSu8tof32(&value); }
static inline void shapeUpdateColor(GSgfxColAu8 *color, peEmitterNode *emitter, _peShape *shape, f32 progress) {
    peColorSplineGetValue(color, shape->colorSpline, progress);
    color->r = shapeColorByte(emitter->color[0] * shapeU8(color->r));
    color->g = shapeColorByte(emitter->color[1] * shapeU8(color->g));
    color->b = shapeColorByte(emitter->color[2] * shapeU8(color->b));
    color->a = shapeColorByte((255.0f * emitter->color[3]) * shapeSpline(shape->alphaSpline, progress));
}
bool peShapeNode::Update(peEmitterNode* emitter,_peShape* shape,f32 delta) {
    if(!peNode::Update(emitter,delta))return false;
    u32 emitterFlags=emitter->emitter->flags;
    f32 progress=1.0f-time/life;
    Vec angles;
    Quaternion flipped;
    Vec direction;
    Quaternion step;
    Vec copy;
    Vec distance;
    Vec rotationVector;
    Quaternion rotation;
    NodeTransform local;
    Mtx rotationMatrix;
    if(emitterFlags&0x400) {
        direction.x=velocity.x;direction.y=velocity.y;direction.z=velocity.z;
        if(emitterFlags&0x40) {
            PSMTXQuat(rotationMatrix,&transform->rotation);
            PSMTXMultVecSR(rotationMatrix,&direction,&direction);
        }
        f32 horizontal=shapeSqrt(direction.x*direction.x+direction.z*direction.z);
        angles.x=(f32)atan2(-direction.y,horizontal);
        angles.y=(f32)atan2(direction.x,direction.z);angles.z=0.0f;
        EulerToQuat(&angles,&localRotation);
    } else if(shape->flags&0x100) {
        angles.x=shape->rotation.x*shapeSpline(shape->rotationSpline[0],progress);
        angles.y=shape->rotation.y*shapeSpline(shape->rotationSpline[1],progress);
        angles.z=shape->rotation.z*shapeSpline(shape->rotationSpline[2],progress);
        EulerToQuat(&angles,&localRotation);
    } else {
        PSVECScale(&angularSpeed,&rotationVector,delta);angles=rotationVector;
        EulerToQuat(&angles,&step);PSQUATMultiply(&localRotation,&step,&localRotation);
    }
    angles.x=baseScale.x*shapeSpline(shape->scaleSpline[0],progress);
    angles.y=baseScale.y*shapeSpline(shape->scaleSpline[1],progress);
    angles.z=baseScale.z*shapeSpline(shape->scaleSpline[2],progress);
    shapeUpdateColor(&color, emitter, shape, progress);
    if(flips&1)flipped.x=-localRotation.x;else flipped.x=localRotation.x;
    if(flips&2)flipped.y=-localRotation.y;else flipped.y=localRotation.y;
    if(flips&4)flipped.z=-localRotation.z;else flipped.z=localRotation.z;
    flipped.w=localRotation.w;
    local.position=position;
    PSQUATMultiply(&randomRotation,&flipped,&rotation);
    local.rotation.x=rotation.x;local.rotation.y=rotation.y;local.rotation.z=rotation.z;local.rotation.w=rotation.w;
    local.scale=angles;
    peNodeTransformsConcat(&world,transform,&local,false);
    PSVECSubtract(&world.position,&g_CameraPosition,&distance);
    copy.x=distance.x;copy.y=distance.y;copy.z=distance.z;depth=PSVECDotProduct(&g_CameraLookDir,&copy);
    return true;
}

static inline void shapeSetKColor(GSgfxColAu8 color) {
    ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
    state->unk14F4=*(u32*)&color;
    state->unk16F8|=1;state->unk16A8|=0x10;
    state->unk17B0|=1;state->unk1760|=0x10;
}
static inline void shapeSetChannelColor(u8 channel,GSgfxColAu8 ambient,GSgfxColAu8 material) {
    ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
    ((u32*)&state->unkE9C)[channel]=*(u32*)&ambient;
    ((u32*)&state->unkEA4)[channel]=*(u32*)&material;
    u32 bit=1<<channel;
    state->unk16C4|=bit;state->unk16C8|=bit;state->unk16A8|=4;
    state->unk177C|=bit;state->unk1780|=bit;state->unk1760|=4;
}
void peShapeNode::Render(_peShape* shape) {
    Mtx sp50;
    Mtx sp20;
    u32 temp_r31=shape->flags;
    u32 temp_r0;
    GSgfxColAu8 black={0,0,0,0};
    shapeSetKColor(color);
    if(temp_r31&0x200) {
        shapeSetChannelColor(0,shape->ambient,color);
        if(temp_r31&0x400)shapeSetChannelColor(1,black,color);
    }
    PSMTXQuat(sp20, &world.rotation);
    PSMTXScale(sp50, world.scale.x, world.scale.y, world.scale.z);
    PSMTXConcat(sp20, sp50, sp50);
    PSMTXTransApply(sp50, sp50, world.position.x, world.position.y, world.position.z);
    pushMult__16GSgfxMatrixStackFP5GSmtx(((ParticleLayerState*)g_current_layer)->unk19A0, sp50);
    temp_r0 = temp_r31 & 7;
    switch (temp_r0) {
    case 0:
        drawCube__10GSgfxLayerFv(g_current_layer);
        break;
    case 1:
        drawCylinder__10GSgfxLayerFUc(g_current_layer, shape->segments1);
        break;
    case 2:
        drawDodecaedron__10GSgfxLayerFv(g_current_layer);
        break;
    case 3:
        drawIcosahedron__10GSgfxLayerFv(g_current_layer);
        break;
    case 4:
        drawOctahedron__10GSgfxLayerFv(g_current_layer);
        break;
    case 7:
        drawTorus__10GSgfxLayerFfUcUc(g_current_layer,shape->radius,shape->segments0,shape->segments1);
        break;
    case 6:
        drawSphere__10GSgfxLayerFUc(g_current_layer, shape->segments1);
        break;
    default:
        drawSphere__10GSgfxLayerFUcUc(g_current_layer, shape->segments0, shape->segments1);
        break;
    }
    pop__16GSgfxMatrixStackFv(((ParticleLayerState*)g_current_layer)->unk19A0);
}

peShapeContainer::peShapeContainer(peEmitterNode* emitter,_peShape* data,u16 maximum):peContainer(emitter,0x9c,maximum){shape=data;g_particle_debug_stats.node+=0x24;g_particle_debug_stats.total+=0x24;}

peShapeContainer::~peShapeContainer(){g_particle_debug_stats.node-=0x24;g_particle_debug_stats.total-=0x24;}

void peShapeContainer::Start() {
    if(!active) {
        active=1;
        if(shape->flags&0x800000)SetLayerVisibility((GSgfxLayerID)1,true);
        if(shape->flags&0x1000000)SetLayerVisibility((GSgfxLayerID)3,true);
        if(shape->flags&0x2000000)SetLayerVisibility((GSgfxLayerID)5,true);
    }
}

u16 peShapeContainer::Emit(u16 requested) {
    if(!active)return 0;
    u16 remaining=CreateNodes(requested);_EmitParams* params=g_emitParams;peNode* node=nodes;peNode* next;u16 result=remaining;
    while(remaining){next=node->next;((peShapeNode*)node)->Start(owner,shape,params);node=next;--remaining;++params;}
    return result;
}

void peShapeContainer::Update(f32 time) {
    if(active) {
        peShapeNode* node=(peShapeNode*)nodes;
        while(node) {peShapeNode* next=(peShapeNode*)node->next;if(!node->Update(owner,shape,time))RemoveNode(node);node=next;}
        if(g_currentBound && nodes)GSboundAlwaysInView(g_currentBound,1);
        if(active && (shape->flags&0x80) && count>=2) {
            peShapeNode* sorting=(peShapeNode*)nodes->next;
            while(sorting) {
                peShapeNode* before=sorting;f32 depth=sorting->depth;peShapeNode* previous=(peShapeNode*)sorting->previous;
                while(previous && previous->depth<depth) {before=previous;previous=(peShapeNode*)previous->previous;}
                node=(peShapeNode*)sorting->next;
                if(before!=sorting)MoveNode(sorting,before);
                sorting=node;
            }
        }
    }
}

inline void GSgfxLayer::tunitKRegSel(u8 arg1,GSgfxTunitKReg arg2) {
    ParticleLayerState *temp_r5_3;
    ParticleLayerState *temp_r5_4;
    u32 temp_r6_4;
    ParticleLayerState *temp_r5;
    u32 temp_r6;
    ParticleLayerState *temp_r5_2;
    u32 temp_r6_3;
    u32 temp_r6_2;

    switch (arg2) {                                 /* irregular */
    case 0:
        temp_r5 = (ParticleLayerState*)((u8*)this + ((arg1 * 4) & 0x3FC));
        temp_r5->unk1504 = 0xC;
        temp_r6 = 1 << arg1;
        ((ParticleLayerState*)this)->unk16FC = (s32) (((ParticleLayerState*)this)->unk16FC | temp_r6);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B4 = (s32) (((ParticleLayerState*)this)->unk17B4 | temp_r6);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        temp_r5->unk1544 = 0x1C;
        ((ParticleLayerState*)this)->unk1700 = (s32) (((ParticleLayerState*)this)->unk1700 | temp_r6);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B8 = (s32) (((ParticleLayerState*)this)->unk17B8 | temp_r6);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        return;
    case 1:
        temp_r5_2 = (ParticleLayerState*)((u8*)this + ((arg1 * 4) & 0x3FC));
        temp_r5_2->unk1504 = 0xD;
        temp_r6_2 = 1 << arg1;
        ((ParticleLayerState*)this)->unk16FC = (s32) (((ParticleLayerState*)this)->unk16FC | temp_r6_2);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B4 = (s32) (((ParticleLayerState*)this)->unk17B4 | temp_r6_2);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        temp_r5_2->unk1544 = 0x1D;
        ((ParticleLayerState*)this)->unk1700 = (s32) (((ParticleLayerState*)this)->unk1700 | temp_r6_2);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B8 = (s32) (((ParticleLayerState*)this)->unk17B8 | temp_r6_2);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        return;
    case 2:
        temp_r5_3 = (ParticleLayerState*)((u8*)this + ((arg1 * 4) & 0x3FC));
        temp_r5_3->unk1504 = 0xE;
        temp_r6_3 = 1 << arg1;
        ((ParticleLayerState*)this)->unk16FC = (s32) (((ParticleLayerState*)this)->unk16FC | temp_r6_3);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B4 = (s32) (((ParticleLayerState*)this)->unk17B4 | temp_r6_3);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        temp_r5_3->unk1544 = 0x1E;
        ((ParticleLayerState*)this)->unk1700 = (s32) (((ParticleLayerState*)this)->unk1700 | temp_r6_3);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B8 = (s32) (((ParticleLayerState*)this)->unk17B8 | temp_r6_3);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        return;
    case 3:
        temp_r5_4 = (ParticleLayerState*)((u8*)this + ((arg1 * 4) & 0x3FC));
        temp_r5_4->unk1504 = 0xF;
        temp_r6_4 = 1 << arg1;
        ((ParticleLayerState*)this)->unk16FC = (s32) (((ParticleLayerState*)this)->unk16FC | temp_r6_4);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B4 = (s32) (((ParticleLayerState*)this)->unk17B4 | temp_r6_4);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        temp_r5_4->unk1544 = 0x1F;
        ((ParticleLayerState*)this)->unk1700 = (s32) (((ParticleLayerState*)this)->unk1700 | temp_r6_4);
        ((ParticleLayerState*)this)->unk16A8 = (s32) (((ParticleLayerState*)this)->unk16A8 | 0x10);
        ((ParticleLayerState*)this)->unk17B8 = (s32) (((ParticleLayerState*)this)->unk17B8 | temp_r6_4);
        ((ParticleLayerState*)this)->unk1760 = (s32) (((ParticleLayerState*)this)->unk1760 | 0x10);
        return;
    }
}

static inline bool shapeRendersOnLayer(peShapeContainer *container) {
    if (!container->active)
        return false;
    u32 flags = container->shape->flags;
    if (!container->count)
        return false;
    if (g_render_pass != 1)
        return false;
    switch (((ParticleLayerState*)g_current_layer)->unk28) {
    case 0:
        if (flags & 0x200000) return true;
        break;
    case 2:
        if (flags & 0x400000) return true;
        if (!(flags & 0x03E00008)) return true;
        break;
    case 4:
        if (flags & 8) return true;
        break;
    case 1:
        if (flags & 0x800000) return true;
        break;
    case 3:
        if (flags & 0x01000000) return true;
        break;
    case 5:
        if (flags & 0x02000000) return true;
        break;
    default:
        return false;
    }
    return false;
}

enum ShapeTextureFilter {
    SHAPE_FILTER_NEAREST = 0,
    SHAPE_FILTER_LINEAR = 2
};

static inline ShapeTextureFilter shapeMinFilter(u32 flags) {
    if (flags & 0x20)
        return SHAPE_FILTER_LINEAR;
    return SHAPE_FILTER_NEAREST;
}

struct CameraSpacePosition : GSvec {
    CameraSpacePosition(f32 px, f32 py, f32 pz) {
        x = px;
        y = py;
        z = pz;
    }
};

static inline CameraSpacePosition shapeLightPosition(const Vec *position) {
    Vec point;
    PSMTXMultVec(g_CameraMatrix, position, &point);
    return CameraSpacePosition(point.x, point.y, point.z);
}

void peShapeContainer::Render() {
    GSgfxLight* light0;
    GSgfxLight* light1;
    s32 magFilter;
    f32 directionZ, directionY;
    s32 shapeFlags;
    u8 lightCount;
    u8 lightIndex;
    _peShape *definition;
    peShapeNode *node;

    if (active && shapeRendersOnLayer(this)) {
        shapeFlags = shape->flags;
        if (shapeFlags & 0x800) {
            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unkD8C = 2;
            state->unk16B8 = (s32) (state->unk16B8 | 2);
            state->unk16A8 = (s32) (state->unk16A8 | 2);
            state->unk1770 = (s32) (state->unk1770 | 2);
            state->unk1760 = (s32) (state->unk1760 | 2);
            }
        } else {
            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unkD8C = 0;
            state->unk16B8 = (s32) (state->unk16B8 | 2);
            state->unk16A8 = (s32) (state->unk16A8 | 2);
            state->unk1770 = (s32) (state->unk1770 | 2);
            state->unk1760 = (s32) (state->unk1760 | 2);
            }
        }
        magFilter = SHAPE_FILTER_NEAREST;
        if (shapeFlags & 0x40) {
            magFilter = SHAPE_FILTER_LINEAR;
        }
        GStexture* texture = shape->texture;
        particleEngineSetupTexture(0, texture, 0, 0, shapeMinFilter(shapeFlags), magFilter);
        particleEngineSetupBlendMode(2);
        if (shapeFlags & 0x200) {
            GSgfxLight *firstLight = shape->light0;
            light0 = firstLight;
            GSgfxLight* lights[2] = {0, 0};
            lightCount = 1;

            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unkEAC = 1;

            state->unk16CC = (s32) (state->unk16CC | 1);
            lights[0] = firstLight;
            state->unk16A8 = (s32) (state->unk16A8 | 8);
            state->unk1784 = (s32) (state->unk1784 | 1);
            state->unk1760 = (s32) (state->unk1760 | 8);
            }
            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unkDB8 = 1;
            state->unk16BC = (s32) (state->unk16BC | 1);
            state->unk16A8 = (s32) (state->unk16A8 | 4);
            state->unk1774 = (s32) (state->unk1774 | 1);
            state->unk1760 = (s32) (state->unk1760 | 4);
            }
            {
                GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                state->colorOperations[0].op = GX_TEV_ADD;
                state->colorOperations[0].bias = GX_TB_ZERO;
                state->colorOperations[0].scale = GX_CS_SCALE_1;
                state->colorOperations[0].clamp = true;
                state->colorOperations[0].output = GX_TEVPREV;
                state->colorOperationDirty |= 1;
                state->dirty |= 8;
                state->savedColorOperationDirty |= 1;
                state->savedDirty |= 8;
            }
            {
                GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                state->alphaOperations[0].op = GX_TEV_ADD;
                state->alphaOperations[0].bias = GX_TB_ZERO;
                state->alphaOperations[0].scale = GX_CS_SCALE_1;
                state->alphaOperations[0].clamp = true;
                state->alphaOperations[0].output = GX_TEVPREV;
                state->alphaOperationDirty |= 1;
                state->dirty |= 8;
                state->savedAlphaOperationDirty |= 1;
                state->savedDirty |= 8;
            }
            {
                GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                state->colorArguments[0][0] = GX_CC_ZERO;
                state->colorArguments[0][1] = GX_CC_RASC;
                state->colorArguments[0][2] = GX_CC_TEXC;
                state->colorArguments[0][3] = GX_CC_ZERO;
                state->colorArgumentDirty |= 1;
                state->dirty |= 8;
                state->savedColorArgumentDirty |= 1;
                state->savedDirty |= 8;
            }
            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unk1544 = 0x1C;
            state->unk1700 = (s32) (state->unk1700 | 1);
            state->unk16A8 = (s32) (state->unk16A8 | 0x10);
            state->unk17B8 = (s32) (state->unk17B8 | 1);
            state->unk1760 = (s32) (state->unk1760 | 0x10);
            }
            {
                GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                state->alphaArguments[0][0] = GX_CA_ZERO;
                state->alphaArguments[0][1] = GX_CA_KONST;
                state->alphaArguments[0][2] = GX_CA_TEXA;
                state->alphaArguments[0][3] = GX_CA_ZERO;
                state->alphaArgumentDirty |= 1;
                state->dirty |= 8;
                state->savedAlphaArgumentDirty |= 1;
                state->savedDirty |= 8;
            }
            const CameraSpacePosition& position = shapeLightPosition(&shape->position);
            GSgfxLight* positionLight=light0;
            switch (positionLight->mode) {
            case 0:
                goto positionDone;
            case 2:
                positionLight->position.x = position.x;
                positionLight->position.y = position.y;
                positionLight->position.z = position.z;
                break;
            case 1:
                positionLight->position.x = position.x;
                positionLight->position.y = position.y;
                positionLight->position.z = position.z;
                break;
            }
            positionLight->flags = (u16)(positionLight->flags | 2);
positionDone:

            cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(g_current_layer,0,0,0,0,1,&light0,2,2);
            if (shapeFlags & 0x400) {
                GSgfxLight *secondLight = shape->light1;
                light1 = secondLight;
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkEAC = 2;
                lightCount = 2;
                lights[1] = secondLight;
                state->unk16CC = (s32) (state->unk16CC | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1784 = (s32) (state->unk1784 | 1);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkEBC = 0xFF;
                state->unkEC0 = 0xFF;
                state->unkEC4 = 5;
                state->unk16D0 = (s32) (state->unk16D0 | 2);
                state->unk16A8 = (s32) (state->unk16A8 | 8);
                state->unk1788 = (s32) (state->unk1788 | 2);
                state->unk1760 = (s32) (state->unk1760 | 8);
                }
                {
                    GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                    state->colorOperations[1].op = GX_TEV_ADD;
                    state->colorOperations[1].bias = GX_TB_ZERO;
                    state->colorOperations[1].scale = GX_CS_SCALE_1;
                    state->colorOperations[1].clamp = true;
                    state->colorOperations[1].output = GX_TEVPREV;
                    state->colorOperationDirty |= 2;
                    state->dirty |= 8;
                    state->savedColorOperationDirty |= 2;
                    state->savedDirty |= 8;
                }
                {
                    GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                    state->alphaOperations[1].op = GX_TEV_ADD;
                    state->alphaOperations[1].bias = GX_TB_ZERO;
                    state->alphaOperations[1].scale = GX_CS_SCALE_1;
                    state->alphaOperations[1].clamp = false;
                    state->alphaOperations[1].output = GX_TEVPREV;
                    state->alphaOperationDirty |= 2;
                    state->dirty |= 8;
                    state->savedAlphaOperationDirty |= 2;
                    state->savedDirty |= 8;
                }
                {
                    GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                    state->colorArguments[1][0] = GX_CC_ZERO;
                    state->colorArguments[1][1] = GX_CC_RASC;
                    state->colorArguments[1][2] = GX_CC_ONE;
                    state->colorArguments[1][3] = GX_CC_CPREV;
                    state->colorArgumentDirty |= 2;
                    state->dirty |= 8;
                    state->savedColorArgumentDirty |= 2;
                    state->savedDirty |= 8;
                }
                {
                    GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                    state->alphaArguments[1][0] = GX_CA_ZERO;
                    state->alphaArguments[1][1] = GX_CA_ZERO;
                    state->alphaArguments[1][2] = GX_CA_ZERO;
                    state->alphaArguments[1][3] = GX_CA_APREV;
                    state->alphaArgumentDirty |= 2;
                    state->dirty |= 8;
                    state->savedAlphaArgumentDirty |= 2;
                    state->savedDirty |= 8;
                }
                { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
                state->unkDB8 = 2;
                state->unk16BC = (s32) (state->unk16BC | 1);
                state->unk16A8 = (s32) (state->unk16A8 | 4);
                state->unk1774 = (s32) (state->unk1774 | 1);
                state->unk1760 = (s32) (state->unk1760 | 4);
                }

                cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(g_current_layer,1,0,0,0,1,&light1,0,2);
                Vec direction;
                if (PSVECSquareMag(&shape->position) < 0.00001f) {
                    direction.x = 0.0f;
                    direction.y = -1.0f;
                    direction.z = 0.0f;
                } else {
                    definition = this->shape;
                    directionY = definition->position.y;
                    directionZ = definition->position.z;
                    f32 directionX = definition->position.x;
                    direction.y = -directionY;
                    direction.x = -directionX;
                    direction.z = -directionZ;
                    PSVECNormalize(&direction,&direction);
                }
                PSMTXMultVecSR(g_CameraMatrix,&direction,&direction);
                GSgfxLight* directionLight=light1;
                switch (directionLight->mode) {
                case 0:
                case 1:
                    directionLight->direction.x = direction.x;
                    directionLight->direction.y = direction.y;
                    directionLight->direction.z = direction.z;
                    directionLight->flags = (u16)(directionLight->flags | 4);
                    break;
                }

            }
            lightIndex = 0;
            ParticleLayerState* lightState=(ParticleLayerState*)g_current_layer;
            lightState->unkD94 = lightCount;
            while (lightIndex < 8U) {
                if (lightIndex < lightCount) {
                    lightState->lights[lightIndex]=lights[lightIndex];
                } else {
                    lightState->lights[lightIndex]=0;
                }
                lightIndex += 1;
            }
            { ParticleLayerState* state=lightState;
            state->unk16BC = (s32) (state->unk16BC | 0x10);
            state->unk16A8 = (s32) (state->unk16A8 | 4);
            state->unk1774 = (s32) (state->unk1774 | 0x10);
            state->unk1760 = (s32) (state->unk1760 | 4);
            }
        } else {
            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unkDB8 = 0;
            state->unk16BC = (s32) (state->unk16BC | 1);
            state->unk16A8 = (s32) (state->unk16A8 | 4);
            state->unk1774 = (s32) (state->unk1774 | 1);
            state->unk1760 = (s32) (state->unk1760 | 4);
            }
            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unkEAC = 1;
            state->unk16CC = (s32) (state->unk16CC | 1);
            state->unk16A8 = (s32) (state->unk16A8 | 8);
            state->unk1784 = (s32) (state->unk1784 | 1);
            state->unk1760 = (s32) (state->unk1760 | 8);
            }
            { ParticleLayerState* state=(ParticleLayerState*)g_current_layer;
            state->unkEB0 = 0;
            state->unkEB4 = 0;
            state->unkEB8 = 0xFF;
            state->unk16D0 = (s32) (state->unk16D0 | 1);
            state->unk16A8 = (s32) (state->unk16A8 | 8);
            state->unk1788 = (s32) (state->unk1788 | 1);
            state->unk1760 = (s32) (state->unk1760 | 8);
            }
            {
                GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                state->colorOperations[0].op = GX_TEV_ADD;
                state->colorOperations[0].bias = GX_TB_ZERO;
                state->colorOperations[0].scale = GX_CS_SCALE_1;
                state->colorOperations[0].clamp = true;
                state->colorOperations[0].output = GX_TEVPREV;
                state->colorOperationDirty |= 1;
                state->dirty |= 8;
                state->savedColorOperationDirty |= 1;
                state->savedDirty |= 8;
            }
            {
                GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                state->alphaOperations[0].op = GX_TEV_ADD;
                state->alphaOperations[0].bias = GX_TB_ZERO;
                state->alphaOperations[0].scale = GX_CS_SCALE_1;
                state->alphaOperations[0].clamp = true;
                state->alphaOperations[0].output = GX_TEVPREV;
                state->alphaOperationDirty |= 1;
                state->dirty |= 8;
                state->savedAlphaOperationDirty |= 1;
                state->savedDirty |= 8;
            }
            g_current_layer->tunitKRegSel(0,PARTICLE_KREG_DEFAULT);
            {
                GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                state->colorArguments[0][0] = GX_CC_ZERO;
                state->colorArguments[0][1] = GX_CC_KONST;
                state->colorArguments[0][2] = GX_CC_TEXC;
                state->colorArguments[0][3] = GX_CC_ZERO;
                state->colorArgumentDirty |= 1;
                state->dirty |= 8;
                state->savedColorArgumentDirty |= 1;
                state->savedDirty |= 8;
            }
            {
                GraphicsLayerState* state = (GraphicsLayerState*)g_current_layer;
                state->alphaArguments[0][0] = GX_CA_ZERO;
                state->alphaArguments[0][1] = GX_CA_KONST;
                state->alphaArguments[0][2] = GX_CA_TEXA;
                state->alphaArguments[0][3] = GX_CA_ZERO;
                state->alphaArgumentDirty |= 1;
                state->dirty |= 8;
                state->savedAlphaArgumentDirty |= 1;
                state->savedDirty |= 8;
            }
        }
        ((ParticleLayerState*)g_current_layer)->unk199C = GSgfxVFGetPredef(4);
        node=(peShapeNode*)this->nodes;
        while(node != NULL) {
            node->Render(this->shape);
            node=(peShapeNode*)node->next;
        }
        particleEngineSetDefaultRenderState(1);
    }
}

void peShapeContainer::Stop() {
    if(active) {
        PreUpdate();active=0;
        if(shape->flags&0x800000)SetLayerVisibility((GSgfxLayerID)1,false);
        if(shape->flags&0x1000000)SetLayerVisibility((GSgfxLayerID)3,false);
        if(shape->flags&0x2000000)SetLayerVisibility((GSgfxLayerID)5,false);
        RemoveAll();
    }
}
