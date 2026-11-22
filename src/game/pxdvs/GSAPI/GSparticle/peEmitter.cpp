#include <game/pxdvs/GSAPI/GSparticle/peEmitterPrivate.hpp>
#include <dolphin/os/OSFastCast.h>
#include <game/pxdvs/GSAPI/GSparticle/peDistortionPrivate.hpp>
#include <game/pxdvs/GSAPI/GSparticle/peModelPrivate.hpp>
#include <game/pxdvs/GSAPI/GSparticle/peParticlePrivate.hpp>
#include <game/pxdvs/GSAPI/GSparticle/peParticleStripPrivate.hpp>
#include <game/pxdvs/GSAPI/GSparticle/peShapePrivate.hpp>

inline peEmitterContainer::peEmitterContainer(peEmitterNode* owner, _peEmitter* definition, u16 maximum) : peContainer(owner, sizeof(peEmitterNode), maximum) {
    emitter = definition;
    peNode* node = freeNodes;
    while (node) {
        peNode* next = node->next;
        static_cast<peEmitterNode*>(node)->Init(definition);
        node = next;
    }
    g_particle_debug_stats.node += sizeof(peEmitterContainer);
    g_particle_debug_stats.total += sizeof(peEmitterContainer);
}

extern "C" {
f32 HSD_Randf();
s32 EulerToQuat(Vec*, Quaternion*);
extern Vec unitScaleVector;
}

extern "C" {
extern Vec g_CameraPosition, g_CameraLookDir;
}

static inline void emitterCopy(Vec* destination,const Vec* source) {
    f32 z,y,x;
    y=source->y;
    z=source->z;
    x=source->x;
    destination->x=x;destination->y=y;destination->z=z;
}
static inline f32 emitterAbs(f32 value) { if(value<0.0f)value=-value;return value; }

// Keep each transform temporary distinct and preserve the scalar copy order.
static inline void emitterCopyVecXYZ(Vec* out,const Vec* in) {f32 x=in->x,y=in->y,z=in->z;out->x=x;out->y=y;out->z=z;}
static inline void emitterCopyVec(Vec* out,const Vec* in) {f32 z,y,x;y=in->y;z=in->z;x=in->x;out->x=x;out->y=y;out->z=z;}
static inline void emitterCopyQuat(Quaternion* out,const Quaternion* in) {f32 x=in->x,y=in->y,z=in->z,w=in->w;out->x=x;out->y=y;out->z=z;out->w=w;}

extern "C" {
extern f32 __float_nan[];
extern u16 g_maxEmitParams;
f64 atan2(f64,f64);
}
static inline s32 emitterFloatClass(f32 x) {
    union {f32 value;s32 bits;} v;v.value=x;
    s32 result;
    switch(v.bits&0x7f800000) {
    case 0x7f800000:if(v.bits&0x7fffff)result=1;else result=2;break;
    case 0:if(v.bits&0x7fffff)result=5;else result=3;break;
    default:result=4;break;
    }
    return result;
}
static inline f32 emitterSpline(PeSpline* spline,f32 progress) {
    if(!spline || !(spline->flags&3))return 1.0f;
    f32 difference=spline->time-progress;
    if(difference<0.0f)difference=-difference;
    if(difference<=0.00001f)return spline->value;
    return peSplineGetValue(spline,progress);
}
static inline f32 emitterColorChannel(u8 value) {return __OSu8tof32(&value);}
static inline u16 emitterEmitCount(peEmitterNode* node,f32 delta,f32 progress) {
    if(node->flags&0x40)return 0;
    if(!(node->flags&8) && node->lastLoop<node->emitter->startTime)return 0;
    node->flags|=8;
    if((node->flags&0x10) && node->lastLoop>node->emitter->startTime+node->emitter->endTime)return 0;
    node->flags|=0x10;
    f32 random=HSD_Randf();
    _peEmitter* definition=node->emitter;
    f32 rate=definition->rateRange * random + definition->rate;
    rate*=emitterSpline(definition->rateSpline,progress);
    if(node->emitter->endTime<=0.00001f) {
        node->emissionRemainder=0.0f;
        return __OSf32tou16(rate);
    }
    rate*=delta;
    rate+=node->emissionRemainder;
    u16 count=__OSf32tou16(rate);
    u16 whole=count;
    node->emissionRemainder=rate-__OSu16tof32(&whole);
    if(count==0 && node->count==0) {
        count=1;
        node->emissionRemainder=0.0f;
    }
    return count;
}

void peEmitterNode::GetPositionParameter(GSvec* position,GSvec* direction,_pePositionFunction* function,f32 time) {
    Mtx matrix4,matrix3,matrix2,matrix1;
    Vec offset;
    Quaternion rotation;
    Vec rotated,range1,range2,normal,cone,scaled,ring;
    switch(function->flags&3) {
    case 0: {
        ((Vec*)direction)->x=function->axis.x;((Vec*)direction)->y=function->axis.y;((Vec*)direction)->z=function->axis.z;
        if((emitterAbs(function->radius)>0.00001f || emitterAbs(function->radiusRange)>0.00001f) && PSVECSquareMag(((Vec*)direction))>0.00001f) {
            f32 angle;
            if(function->flags&0x80)angle=3.1415927f*(2.0f*(function->rate*time));
            else { f32 random=HSD_Randf(); angle=3.1415927f*(2.0f*random); }
            C_QUATRotAxisRad(&rotation,((Vec*)direction),angle);
            PSMTXQuat(matrix3,&rotation);
            PSMTXMultVecSR(matrix3,&function->direction,&rotated);
            emitterCopy(((Vec*)position),&rotated);
            f32 scale;
            if(function->flags&0x20)scale=time*function->radiusRange+function->radius;
            else scale=function->radiusRange*HSD_Randf()+function->radius;
            PSVECScale(((Vec*)position),((Vec*)position),scale);
        } else {((Vec*)position)->x=0.0f;((Vec*)position)->y=0.0f;((Vec*)position)->z=0.0f;}
        if(function->flags&0x10) {
            PSVECScale(&function->range,&range1,time);
            offset.x=range1.x;offset.y=range1.y;offset.z=range1.z;
        } else {
            PSVECScale(&function->range,&range2,HSD_Randf());
            offset.x=range2.x;offset.y=range2.y;offset.z=range2.z;
        }
        PSVECAdd(&offset,&function->origin,&offset);
        PSVECAdd(((Vec*)position),&offset,((Vec*)position));
        if(PSVECSquareMag(((Vec*)position))>0.00001f) {
            PSVECNormalize(((Vec*)position),&normal);
            emitterCopy(((Vec*)direction),&normal);
        } else {((Vec*)direction)->x=0.0f;((Vec*)direction)->y=0.0f;((Vec*)direction)->z=0.0f;}
        return;
    }
    case 1: {
        f32 angle;
        if(function->flags&0x40)angle=function->direction.x*(function->direction.y*time)+function->axis.z;
        else angle=function->direction.x*HSD_Randf()+function->axis.z;
        C_QUATRotAxisRad(&rotation,&function->range,angle);
        PSMTXQuat(matrix2,&rotation);
        PSMTXMultVecSR(matrix2,&function->origin,&cone);
        emitterCopy(((Vec*)direction),&cone);
        if(function->flags&0x80)angle=3.1415927f*(2.0f*(function->direction.z*time));
        else { f32 random=HSD_Randf(); angle=3.1415927f*(2.0f*random); }
        C_QUATRotAxisRad(&rotation,&function->origin,angle);
        PSMTXQuat(matrix4,&rotation);
        PSMTXMultVecSR(matrix4,((Vec*)direction),((Vec*)direction));
        f32 scale;
        if(function->flags&0x20)scale=time*function->axis.y+function->axis.x;
        else scale=function->axis.y*HSD_Randf()+function->axis.x;
        PSVECScale(((Vec*)direction),&scaled,scale);
        emitterCopy(((Vec*)position),&scaled);
        return;
    }
    case 3: {
        ((Vec*)direction)->x=function->range.x;((Vec*)direction)->y=function->range.y;((Vec*)direction)->z=function->range.z;
        f32 angle;
        if(function->flags&0x80)angle=3.1415927f*(2.0f*(function->direction.z*time));
        else { f32 random=HSD_Randf(); angle=3.1415927f*(2.0f*random); }
        C_QUATRotAxisRad(&rotation,((Vec*)direction),angle);
        PSMTXQuat(matrix1,&rotation);
        PSMTXMultVecSR(matrix1,&function->axis,&ring);
        emitterCopy(((Vec*)position),&ring);
        f32 scale;
        if(function->flags&0x20)scale=time*function->direction.y+function->direction.x;
        else scale=function->direction.y*HSD_Randf()+function->direction.x;
        PSVECScale(((Vec*)position),((Vec*)position),scale);
        PSVECAdd(((Vec*)position),&function->origin,((Vec*)position));
        return;
    }
    default:
        ((Vec*)position)->x=0.0f;((Vec*)position)->y=0.0f;((Vec*)position)->z=0.0f;
        ((Vec*)direction)->x=0.0f;((Vec*)direction)->y=0.0f;((Vec*)direction)->z=0.0f;
        return;
    }
}

#pragma opt_common_subs off
#pragma opt_loop_invariants off
static inline void emitterCopyLerpQuat(Quaternion* out,const Quaternion* in) {f32 w,z,y,x;y=in->y;z=in->z;w=in->w;x=in->x;out->x=x;out->y=y;out->z=z;out->w=w;}
void peEmitterNode::CreateParameters(u16 remaining, f32 interval) {
    Mtx inverseMatrix0,inverseMatrix1,inverseMatrix2,inverseMatrix3,matrix2,matrix0;
    Vec position;
    Quaternion rotation,inverseCopy0,inverseCopy1,inverseCopy2,inverseCopy3;
    Vec drift,lerped;
    Quaternion quat;
    Vec scaleLerped,rotated,scaled;
    Quaternion inverse0,inverse1,inverse2,inverse3;
    Vec delta,scaleDelta;
    _peEmitter *def = emitter;
    _EmitParams *params;
    u32 local;
    _pePositionFunction* positionFunction;

    u16 existingCount;
    u32 definitionFlags;
    f32 timeStep;
    u16 total;
    existingCount=this->count;
    definitionFlags=def->flags;
    timeStep=def->emissionTimeStep;
    total=existingCount+remaining;
    local=(definitionFlags>>6)&1;
    f32 time = timeStep * __OSu16tof32(&total);
    u16 countCopy = remaining;
    f32 inverseTotal;
    f32 blend;
    f32 offset;
    f32 offsetStep;
    inverseTotal=1.0f/__OSu16tof32(&countCopy);
    positionFunction=&def->positionFunction;
    blend=1.0f;
    offset=0.0f;
    params=g_emitParams;
    offsetStep=interval*inverseTotal;
    while (remaining--) {

        GetPositionParameter((GSvec *)&params->position, (GSvec *)&position, positionFunction, time);
        switch (def->velocityFlags & 2) {
        case 0: {

            C_QUATRotAxisRad(&rotation, &def->rotationAxis, def->angleRange * HSD_Randf() + def->angle);
            PSMTXQuat(matrix0, &rotation);
            PSMTXMultVecSR(matrix0, &def->velocity.direction, &rotated);
            emitterCopyVec(&params->velocity,&rotated);

            f32 random=HSD_Randf();
            f32 turns=2.0f*random;
            C_QUATRotAxisRad(&rotation, &def->velocity.direction, 3.1415927f * turns);
            PSMTXQuat(matrix2, &rotation);
            PSMTXMultVecSR(matrix2, &params->velocity, &params->velocity);
            f32 speed;
            if (def->velocityFlags & 0x20) speed = time * def->speedRange + def->speed;
            else speed = def->speedRange * HSD_Randf() + def->speed;
            PSVECScale(&params->velocity, &params->velocity, speed);
            break;
        }
        case 2: {

            f32 speed;
            if (def->velocityFlags & 0x20) speed = time * def->velocity.alongNormal.range + def->velocity.alongNormal.speed;
            else speed = def->velocity.alongNormal.range * HSD_Randf() + def->velocity.alongNormal.speed;
            PSVECScale(&position, &scaled, speed);
            emitterCopyVec(&params->velocity,&scaled);
            break;
        }
        default: {
            params->velocity.x = 0.0f;
            params->velocity.y = 0.0f;
            params->velocity.z = 0.0f;
            break;
        }
        }

        PSVECScale(&params->velocity, &drift, offset);
        emitterCopyVecXYZ(&position,&drift);
        PSVECAdd(&params->position, &position, &params->position);

        params->life = (emitter->particleLifeRange * HSD_Randf() + emitter->particleLife) - offset;

        params->forceFactor = emitter->forceFactorRange * HSD_Randf() + emitter->forceFactor;
        if (local) {

            PSVECSubtract(&world.position, &previousWorld.position, &delta);
            emitterCopyVecXYZ(&lerped,&delta);
            PSVECScale(&lerped, &lerped, blend);
            PSVECAdd(&lerped, &previousWorld.position, &lerped);
            emitterCopyVec(&params->transform.position,&lerped);
            C_QUATLerp(&previousWorld.rotation, &world.rotation, &quat, blend);
            emitterCopyLerpQuat(&params->transform.rotation,&quat);
            PSVECSubtract(&world.scale, &previousWorld.scale, &scaleDelta);
            emitterCopyVecXYZ(&scaleLerped,&scaleDelta);
            PSVECScale(&scaleLerped, &scaleLerped, blend);
            PSVECAdd(&scaleLerped, &previousWorld.scale, &scaleLerped);
            emitterCopyVec(&params->transform.scale,&scaleLerped);
            if (positionFunction->flags & 0x100) {

                PSVECSubtract(&params->position, &params->transform.position, &params->position);
                PSQUATInverse(&params->transform.rotation, &inverse0);
                emitterCopyQuat(&inverseCopy0,&inverse0);
                PSMTXQuat(inverseMatrix0, &inverseCopy0);
                PSMTXMultVecSR(inverseMatrix0, &params->position, &params->position);
                if(0.0f != params->transform.scale.x) params->position.x = params->position.x / params->transform.scale.x;
                if(0.0f != params->transform.scale.y) params->position.y = params->position.y / params->transform.scale.y;
                if(0.0f != params->transform.scale.z) params->position.z = params->position.z / params->transform.scale.z;
            }
            if (def->velocityFlags & 0x10) {

                PSQUATInverse(&params->transform.rotation, &inverse1);
                emitterCopyQuat(&inverseCopy1,&inverse1);
                PSMTXQuat(inverseMatrix1, &inverseCopy1);
                PSMTXMultVecSR(inverseMatrix1, &params->velocity, &params->velocity);
            }
        } else {
            if (positionFunction->flags & 0x100) {

                PSVECSubtract(&params->position, &world.position, &params->position);
                PSQUATInverse(&world.rotation, &inverse2);
                emitterCopyQuat(&inverseCopy2,&inverse2);
                PSMTXQuat(inverseMatrix2, &inverseCopy2);
                PSMTXMultVecSR(inverseMatrix2, &params->position, &params->position);
                if(0.0f != world.scale.x) params->position.x = params->position.x / world.scale.x;
                if(0.0f != world.scale.y) params->position.y = params->position.y / world.scale.y;
                if(0.0f != world.scale.z) params->position.z = params->position.z / world.scale.z;
            }
            if (def->velocityFlags & 0x10) {

                PSQUATInverse(&world.rotation, &inverse3);
                emitterCopyQuat(&inverseCopy3,&inverse3);
                PSMTXQuat(inverseMatrix3, &inverseCopy3);
                PSMTXMultVecSR(inverseMatrix3, &params->velocity, &params->velocity);
            }
        }
        time -= timeStep;
        ++params;
        blend -= inverseTotal;
        offset += offsetStep;
    }
}
#pragma opt_common_subs reset
#pragma opt_loop_invariants reset

void peEmitterNode::CreateWorldParams() {
    NodeTransform localTransform;
    Vec direction;
    Vec difference;
    u32 emitterFlags = emitter->flags;
    previousWorld.position.x = world.position.x;
    previousWorld.position.y = world.position.y;
    previousWorld.position.z = world.position.z;
    previousWorld.rotation.x = world.rotation.x;
    previousWorld.rotation.y = world.rotation.y;
    previousWorld.rotation.z = world.rotation.z;
    previousWorld.rotation.w = world.rotation.w;
    previousWorld.scale.x = world.scale.x;
    previousWorld.scale.y = world.scale.y;
    previousWorld.scale.z = world.scale.z;
    if (flags & 1) world.rotation.x = -localRotation.x;
    else world.rotation.x = localRotation.x;
    if (flags & 2) world.rotation.y = -localRotation.y;
    else world.rotation.y = localRotation.y;
    if (flags & 4) world.rotation.z = -localRotation.z;
    else world.rotation.z = localRotation.z;
    world.rotation.w = localRotation.w;
    Vec position;
    PSVECAdd(&this->position, &offset, &position);
    localTransform.position.x = position.x;
    localTransform.position.y = position.y;
    localTransform.position.z = position.z;
    Quaternion rotation;
    PSQUATMultiply(&orientation, &world.rotation, &rotation);
    localTransform.rotation.x = rotation.x;
    localTransform.rotation.y = rotation.y;
    localTransform.rotation.z = rotation.z;
    localTransform.rotation.w = rotation.w;
    localTransform.scale.x = scale.x;
    localTransform.scale.y = scale.y;
    localTransform.scale.z = scale.z;
    peNodeTransformsConcat(&world,transform,&localTransform,(emitterFlags & 2) != 0);
    PSVECSubtract(&world.position,&g_CameraPosition,&difference);
    direction.x = difference.x;
    direction.y = difference.y;
    direction.z = difference.z;
    depth = PSVECDotProduct(&g_CameraLookDir,&direction);
    if (count == 0) {
        previousWorld.position.x = world.position.x;
        previousWorld.position.y = world.position.y;
        previousWorld.position.z = world.position.z;
        previousWorld.rotation.x = world.rotation.x;
        previousWorld.rotation.y = world.rotation.y;
        previousWorld.rotation.z = world.rotation.z;
        previousWorld.rotation.w = world.rotation.w;
        previousWorld.scale.x = world.scale.x;
        previousWorld.scale.y = world.scale.y;
        previousWorld.scale.z = world.scale.z;
    }
}

void peEmitterNode::SetLastLoop() {
    if (flags & 0x40) return;
    if (!(emitter->flags & 1)) return;
    flags |= 0x40;
    f32 loop = emitter->startTime + emitter->endTime;
    if (time < emitter->duration - loop) { time = emitter->duration - loop; lastLoop = loop; }
}

void peEmitterNode::Start(peEmitterNode* parent, _peEmitter* definition, _EmitParams* params) {
    Vec angles;
    u32 definitionFlags = definition->flags;
    peNode::Start(parent, params);
    if (!parent && (definitionFlags & 1)) time = definition->startTime + definition->endTime;
    else time = definition->duration;
    life = definition->duration;
    lastLoop = 0.0f;
    emissionRemainder = 0.0f;
    color[3] = 0.0f;
    count = 0;
    flags = 0x20;
    localRotation.x = 0.0f;
    localRotation.y = 0.0f;
    localRotation.z = 0.0f;
    localRotation.w = 1.0f;
    orientation.x = 0.0f;
    orientation.y = 0.0f;
    orientation.z = 0.0f;
    orientation.w = 1.0f;
    previousWorld.position.x = 0.0f;
    previousWorld.position.y = 0.0f;
    previousWorld.position.z = 0.0f;
    previousWorld.rotation.x = 0.0f;
    previousWorld.rotation.y = 0.0f;
    previousWorld.rotation.z = 0.0f;
    previousWorld.rotation.w = 1.0f;
    previousWorld.scale = unitScaleVector;
    world.position.x = 0.0f;
    world.position.y = 0.0f;
    world.position.z = 0.0f;
    world.rotation.x = 0.0f;
    world.rotation.y = 0.0f;
    world.rotation.z = 0.0f;
    world.rotation.w = 1.0f;
    world.scale = unitScaleVector;
    if (!(definitionFlags & 2) && (!parent || (parent->emitter->flags & 0x400) != 0x400)) {
        if ((definitionFlags & 0x80) != 0x80) EulerToQuat(&definition->euler, &localRotation);
        if (definitionFlags & 0x700038) {
            if (definitionFlags & 8) {
                f32 random = HSD_Randf();
                angles.x = 6.2831855f * random;
            }
            else angles.x = 0.0f;
            if (definitionFlags & 0x10) angles.y = 6.2831855f * HSD_Randf();
            else angles.y = 0.0f;
            if (definitionFlags & 0x20) angles.z = 6.2831855f * HSD_Randf();
            else angles.z = 0.0f;
            if (definitionFlags & 0x100000) {
                if (HSD_Randf() < 0.5f) { flags |= 1; angles.x = -angles.x; }
            }
            if (definitionFlags & 0x200000) {
                if (HSD_Randf() < 0.5f) { flags |= 2; angles.y = -angles.y; }
            }
            if (definitionFlags & 0x400000) {
                if (HSD_Randf() < 0.5f) { flags |= 4; angles.z = -angles.z; }
            }
            EulerToQuat(&angles, &orientation);
        }
    }
    if ((definitionFlags & 0x80) != 0x80) {
        randomOffset.x = definition->angularVelocity.x + definition->angularVelocityRange.x * HSD_Randf();
        randomOffset.y = definition->angularVelocity.y + definition->angularVelocityRange.y * HSD_Randf();
        randomOffset.z = definition->angularVelocity.z + definition->angularVelocityRange.z * HSD_Randf();
    }
    spin.x = definition->scale.x;
    spin.y = definition->scale.y;
    spin.z = definition->scale.z;
    peContainer* container = containers;
    while (container) { container->Start(); container = container->next; }
}

bool peEmitterNode::Update(peEmitterNode* parent,_peEmitter* definition,f32 delta) {
    Mtx matrix;
    Vec angles,velocity;
    Quaternion rotation;
    GSgfxColAu8 sample;
    u32 definitionFlags=definition->flags;
    if(!peNode::Update(parent,delta)) {
        if(!parent && (definitionFlags&1)) {
            if(flags&0x40)return false;
            time+=definition->endTime;
            lastLoop-=definition->duration-definition->startTime;
            count=0;
        } else return false;
        flags&=~0x20;
    }
    f32 progress;
    if(flags&0x20)progress=1.0f-time/life;
    else progress=1.0f;
    peColorSplineGetValue(&sample,definition->colorSpline,progress);
    color[0]=0.00390625f*(2.0f*emitterColorChannel(sample.r));
    color[1]=0.00390625f*(2.0f*emitterColorChannel(sample.g));
    color[2]=0.00390625f*(2.0f*emitterColorChannel(sample.b));
    color[3]=emitterSpline(definition->alphaSpline,progress);
    if(parent) {
        color[0]*=parent->color[0];
        color[1]*=parent->color[1];
        color[2]*=parent->color[2];
        color[3]*=parent->color[3];
    }
    if(!(definitionFlags&2)) {
        if(parent && (parent->emitter->flags&0x400)!=0) {
            velocity.x=this->velocity.x;velocity.y=this->velocity.y;velocity.z=this->velocity.z;
            if(parent->emitter->flags&0x40) {
                PSMTXQuat(matrix,&transform->rotation);
                PSMTXMultVecSR(matrix,&velocity,&velocity);
            }
            f32 horizontal=velocity.x*velocity.x+velocity.z*velocity.z;
            if(horizontal>0.0f) {
                f64 guess=__frsqrte(horizontal);
                guess=0.5*guess*(3.0-(f64)horizontal*(guess*guess));
                guess=0.5*guess*(3.0-(f64)horizontal*(guess*guess));
                guess=0.5*guess*(3.0-(f64)horizontal*(guess*guess));
                horizontal=(f32)((f64)horizontal*guess);
            } else if((f64)horizontal<0.0)horizontal=__float_nan[0];
            else if(emitterFloatClass(horizontal)==1)horizontal=__float_nan[0];
            angles.x=atan2(-velocity.y,horizontal);
            angles.y=atan2(velocity.x,velocity.z);
            angles.z=0.0f;
            EulerToQuat(&angles,&localRotation);
        } else if(definitionFlags&0x80) {
            angles.x=definition->euler.x*emitterSpline(definition->eulerSpline[0],progress);
            angles.y=definition->euler.y*emitterSpline(definition->eulerSpline[1],progress);
            angles.z=definition->euler.z*emitterSpline(definition->eulerSpline[2],progress);
            EulerToQuat(&angles,&localRotation);
        } else {
            angles.x=delta*(randomOffset.x*emitterSpline(definition->angularVelocitySpline[0],progress));
            angles.y=delta*(randomOffset.y*emitterSpline(definition->angularVelocitySpline[1],progress));
            angles.z=delta*(randomOffset.z*emitterSpline(definition->angularVelocitySpline[2],progress));
            EulerToQuat(&angles,&rotation);
            PSQUATMultiply(&localRotation,&rotation,&localRotation);
        }
    }
    scale.x=spin.x*emitterSpline(definition->scaleSpline[0],progress);
    scale.y=spin.y*emitterSpline(definition->scaleSpline[1],progress);
    scale.z=spin.z*emitterSpline(definition->scaleSpline[2],progress);
    offset.x=definition->offset.x*emitterSpline(definition->offsetSpline[0],progress);
    offset.y=definition->offset.y*emitterSpline(definition->offsetSpline[1],progress);
    offset.z=definition->offset.z*emitterSpline(definition->offsetSpline[2],progress);
    force.x=definition->force.x*emitterSpline(definition->forceSpline[0],progress);
    force.y=definition->force.y*emitterSpline(definition->forceSpline[1],progress);
    force.z=definition->force.z*emitterSpline(definition->forceSpline[2],progress);
    CreateWorldParams();
    peContainer* container=containers;
    while(container) {container->PreUpdate();container=container->next;}
    u16 emitted=emitterEmitCount(this,delta,progress);
    if(emitted) {
        if(emitted>g_maxEmitParams)emitted=g_maxEmitParams;
        CreateParameters(emitted,definition->endTime>0.00001f?delta:0.0f);
        container=containers;
        while(container) {count+=container->Emit(emitted);container=container->next;}
    }
    container=containers;
    while(container) {container->Update(delta);container=container->next;}
    lastLoop+=delta;
    return true;
}

void peEmitterNode::Render(_peEmitter*) {
    peContainer* container = containers;
    if (count == 0) return;
    while (container) { container->Render(); container = container->next; }
}

void peEmitterNode::Stop(_peEmitter*) {
    peContainer* container = containers;
    while (container) { container->Stop(); container = container->next; }
}

void peEmitterNode::Init(_peEmitter* definition) {
    peContainer* container;
    peContainer* last;
    void* data;
    u16 maximum;
    _particleData* resource;
    emitter = definition;
    maximum = definition->flags2;
    for (resource = definition->resources; resource; resource = resource->next) {
        data = resource->data;
        if (data) {
            container = 0;
            switch (resource->kind) {
            case 0: {
                _peEmitter* child = static_cast<_peEmitter*>(data);
                if (child->resources) container = new peEmitterContainer(this, child, maximum);
                break;
            }
            case 1:
                if (static_cast<_peParticle*>(data)->textureId) {
                    container = new peParticleContainer(this, static_cast<_peParticle*>(data), maximum);
                }
                break;
            case 6:
                if (static_cast<_peParticleStrip*>(data)->textureId) {
                    container = new peParticleStripContainer(this, static_cast<_peParticleStrip*>(data), maximum);
                }
                break;
            case 3:
                if (static_cast<_peDistortion*>(data)->textureId) {
                    container = new peDistortionContainer(this, static_cast<_peDistortion*>(data), maximum);
                }
                break;
            case 2:
                if (static_cast<_peModel*>(data)->resource.id) {
                    container = new peModelContainer(this, static_cast<_peModel*>(data), maximum);
                }
                break;
            case 4:
                if (static_cast<_peShape*>(data)->textureId) {
                    container = new peShapeContainer(this, static_cast<_peShape*>(data), maximum);
                }
                break;
            }
            if (container) {
                if (!containers) containers = container;
                else {
                    last = containers;
                    while (last->next) last = last->next;
                    last->next = container;
                }
            }
        }
    }
}

void peEmitterNode::Release() {
    peContainer* next;
    peContainer* container = containers;
    while (container) {
        next = container->next;
        container->Stop();
        delete container;
        container = next;
    }
    containers = 0;
}

peEmitterContainer::~peEmitterContainer() {
    peNode* node = freeNodes;
    while (node) {
        peNode* next = node->next;
        static_cast<peEmitterNode*>(node)->Release();
        node = next;
    }
    g_particle_debug_stats.node -= sizeof(peEmitterContainer);
    g_particle_debug_stats.total -= sizeof(peEmitterContainer);
}

void peEmitterContainer::PreUpdate() {
    _particleData* resource = emitter->resources;
    while (resource) resource = resource->next;
}

u16 peEmitterContainer::Emit(u16 count) {
    if (!active) return 0;
    u16 remaining = CreateNodes(count);
    _EmitParams* params = g_emitParams;
    peNode* node = nodes;
    peNode* next;
    u16 result = remaining;
    while (remaining) {
        next = node->next;
        static_cast<peEmitterNode*>(node)->Start(owner, emitter, params);
        node = next; --remaining; ++params;
    }
    return result;
}

void peEmitterContainer::Update(f32 delta) {
    if (active) {
        peEmitterNode* node = static_cast<peEmitterNode*>(nodes);
        peEmitterNode* next;
        while (node) {
            next = static_cast<peEmitterNode*>(node->next);
            if (!node->Update(owner, emitter, delta)) {
                node->Stop(0);
                RemoveNode(node);
            }
            node = next;
        }
        if (active && (emitter->flags & 0x40000) && count >= 2) {
            peEmitterNode* node = static_cast<peEmitterNode*>(nodes->next);
            while (node) {
                f32 depth = node->depth;
                peEmitterNode* before = node;
                peEmitterNode* previous = static_cast<peEmitterNode*>(node->previous);
                while (previous && previous->depth < depth) {
                    before = previous;
                    previous = static_cast<peEmitterNode*>(previous->previous);
                }
                next = static_cast<peEmitterNode*>(node->next);
                if (before != node) MoveNode(node, before);
                node = next;
            }
        }
    }
}

bool peEmitterContainer::DoRender() {
    if (!active) return false;
    u32 flags = emitter->flags;
    if (!count) return false;
    if (flags & 0x80000000) return false;
    switch (g_render_pass) {
    case 0: if (!(flags & 0x800)) return false; break;
    case 1: if (!(flags & 0x1000)) return false; break;
    default: return false;
    }
    switch (g_current_layer->id) {
    case 0: if (flags & 0x2000) return true; break;
    case 2:
        if (flags & 0x4000) return true;
        if (!(flags & 0x0380e000)) return true;
        break;
    case 4: if (flags & 0x8000) return true; break;
    case 1: if (flags & 0x800000) return true; break;
    case 3: if (flags & 0x1000000) return true; break;
    case 5: if (flags & 0x2000000) return true; break;
    default: return false;
    }
    return false;
}

void peEmitterContainer::Render() {
    if (active && DoRender()) {
        peNode* node = nodes;
        while (node) { static_cast<peEmitterNode*>(node)->Render(0); node = node->next; }
    }
}

void peEmitterContainer::Stop() {
    if (active) {
        PreUpdate();
        active = 0;
        peNode* node = nodes;
        while (node) {
            peNode* next = node->next;
            static_cast<peEmitterNode*>(node)->Stop(0);
            node = next;
        }
        RemoveAll();
    }
}
