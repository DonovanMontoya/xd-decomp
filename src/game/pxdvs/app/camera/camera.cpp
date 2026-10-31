void cameraResetOffsets(bool resetFov);
#pragma defer_codegen off
#include <game/pxdvs/app/camera/camera.hpp>
#include <game/pxdvs/GSAPI/GSres/GSres.hpp>
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <game/pxdvs/GSAPI/GSpart/GSpart.hpp>
#include <libc/string.h>
extern "C" {
f64 sin(f64);
f64 cos(f64);
}
extern "C" {
f64 atan2(f64,f64);
u32 GSfloorGetCurrent();
extern u32* floordata_number;
void GSthreadSwitch();
void* GSthreadGetCurrentThread();
void GSlogWrite(const char*, ...);
u8 GSgfxVideoGetVsyncRate();
s32 GSgfxVideoGetLockFrameRate();
u8 floorFieldCameraDataExist();
void floorFieldCameraEnable();
void floorFieldCameraBlend(f32);
}
static CameraWork _cameraWork;
static CameraWork _cameraWorkBak;
struct CameraUpVector : GSvec { CameraUpVector() { param1=0.0f; param2=1.0f; param3=0.0f; } };
static CameraUpVector gUpVec;
extern "C" { CameraWork* pCamWork = &_cameraWork; }
static FloorCamera* _pFloorCamera;

void cameraResetOffsets(bool resetFov) {
    { GSvec* v=&pCamWork->offsetPosition; v->param1=0.0f; v->param2=0.0f; v->param3=0.0f; }
    { GSvec* v=&pCamWork->offsetRotation; v->param1=0.0f; v->param2=0.0f; v->param3=0.0f; }
    f32 fov;
    if (resetFov) fov = 30.0f;
    { GSvec* v=&pCamWork->offsetScale; v->param1=1.0f; v->param2=1.0f; v->param3=1.0f; }
    if (resetFov) pCamWork->fov = fov;
}
#pragma force_active on
#pragma defer_codegen on

static inline FloorCamera* currentFloorCamera() {
    u32 id = GSfloorGetCurrent();
    FloorCamera* camera = _pFloorCamera;
    for (s32 i = 0; (u32)i < *floordata_number; ++camera, ++i)
        if (id == camera->floorID) return &_pFloorCamera[i];
    return 0;
}
static inline GScamera* animationCamera(CameraWork* work) {
    GScamera* camera = (GScamera*)GSresGetResource(work->animationGroup, work->animationID);
    if (!camera) camera = (GScamera*)GSresGetResourceAllGroup(work->animationID);
    return camera;
}
static inline void copyVector(GSvec* to,const GSvec* from) { f32* d=(f32*)to; const f32* s=(const f32*)from; d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; }
static inline Vec* vec(GSvec* v) { return (Vec*)v; }
static inline Vec* vec(const GSvec* v) { return (Vec*)v; }
extern "C" {

static inline void cameraSetFovValue(f32& value) {
    if (value < 3.0f) value = 3.0f;
    if (value > 120.0f) value = 120.0f;
    FloorCamera* floor = currentFloorCamera();
    if (floor) floor->fov = value;
    pCamWork->fov = value;
}

}

static inline void interpolate(f32* out,const f32* a,const f32* b,f32 t) { f32 from=*a; *out=from+(*b-from)*t; }
static inline void interpolate(GSvec* out,const GSvec* a,const GSvec* b,f32 t) {
    Vec delta;
    PSVECSubtract(vec(b),vec(a),&delta);
    PSVECScale(&delta,&delta,t);
    PSVECAdd(vec(a),&delta,vec(out));
}

template<class T> void CameraAnimation<T>::start(const T* from,const T* to,f32 seconds) {
    if(seconds < 1e-7f && seconds > -1e-7f) return;
    moving=1; duration=seconds; elapsed=0.0f; startPosition=*from; endPosition=*to; acceleration=0.05f; speed=0.0f; phase=0;
}
template<class T> void CameraAnimation<T>::stop() { moving=0; accelerating=0; }
template<class T> u8 CameraAnimation<T>::isMove() const { return moving; }
template<class T> u8 CameraAnimation<T>::update(f32 delta) {
    if(!moving) return 0;
    if(accelerating) return updateAcceleration(delta);
    firstUpdate=0;
    elapsed+=delta;
    f32 end, time; time=elapsed; end=duration;
    if(time>=end) { currentPosition=endPosition; elapsed=0.0f; moving=0; accelerating=0; return 1; }
    interpolate(&currentPosition,&startPosition,&endPosition,time/end);
    return 1;
}
template<class T> u8 CameraAnimation<T>::updateAcceleration(f32 delta) {
    if(!moving) return 0;
    if(firstUpdate) {
        if(!accelerateIn && accelerateOut) {
            f32 frame;
            f32 braking=0.0f;
            speed=1.0f;
            frame=1.0f/(f32)GSgfxVideoGetVsyncRate();
            if(GSgfxVideoGetLockFrameRate()==1) frame*=2.0f;
            for(f32 amount=0.0f; amount<1.0f; amount+=acceleration) braking+=frame*amount;
            brakeTime=duration-braking; phase=1;
        }
        firstUpdate=0;
    }
    elapsed+=delta*speed;
    f32 time=elapsed, end=duration;
    if(time>=end) { currentPosition=endPosition; elapsed=0.0f; moving=0; accelerating=0; return 1; }
    interpolate(&currentPosition,&startPosition,&endPosition,time/end);
    switch(phase) {
    case 0: speed+=acceleration; if(speed>=1.0f) { phase=1; brakeTime=duration-elapsed; } break;
    case 1: if(accelerateOut && elapsed>=brakeTime) phase=2; break;
    case 2: speed-=acceleration; if(speed<acceleration) speed=acceleration; break;
    }
    return 1;
}
template<class T> void CameraAnimation<T>::setAcceleration(f32 amount) { acceleration=amount; accelerating=1; accelerateOut=1; accelerateIn=1; }
template<class T> const T* CameraAnimation<T>::getCurrentPos() const { return &currentPosition; }
// Scalar interpolation rounds its multiply separately from the final addition.
#pragma dont_inline on
template<> const f32* CameraAnimation<f32>::getCurrentPos() const { return &currentPosition; }
template<> void CameraAnimation<f32>::setAcceleration(f32 amount) { acceleration=amount; accelerating=1; accelerateOut=1; accelerateIn=1; }
template<> u8 CameraAnimation<f32>::updateAcceleration(f32 delta) {
    if(!moving) return 0;
    if(firstUpdate) {
        if(!accelerateIn && accelerateOut) {
            f32 braking=0.0f;
            f32 frame;
            speed=1.0f;
            frame=1.0f/(f32)GSgfxVideoGetVsyncRate();
            if(GSgfxVideoGetLockFrameRate()==1) frame*=2.0f;
            for(f32 amount=0.0f; amount<1.0f; amount+=acceleration) braking+=frame*amount;
            brakeTime=duration-braking; phase=1;
        }
        firstUpdate=0;
    }
    elapsed+=delta*speed;
    f32 end, time; time=elapsed; end=duration;
    if(time>=end) { currentPosition=endPosition; elapsed=0.0f; moving=0; accelerating=0; return 1; }
#pragma fp_contract off
    f32 to=*(volatile f32*)&endPosition, from=*(volatile f32*)&startPosition;
    f32 fraction=time/end;
    f32 difference=to-from;
    difference=difference*fraction;
    currentPosition=difference+from;
#pragma fp_contract on
    switch(phase) {
    case 0: speed+=acceleration; if(speed>=1.0f) { phase=1; brakeTime=duration-elapsed; } break;
    case 1: if(accelerateOut && elapsed>=brakeTime) phase=2; break;
    case 2: speed-=acceleration; if(speed<acceleration) speed=acceleration; break;
    }
    return 1;
}
#pragma fp_contract off
template<> u8 CameraAnimation<f32>::update(f32 delta) {
    if(!moving) return 0;
    if(accelerating) return updateAcceleration(delta);
    firstUpdate=0;
    elapsed+=delta;
    f32 end, time; time=elapsed; end=duration;
    if(time>=end) { currentPosition=endPosition; elapsed=0.0f; moving=0; accelerating=0; return 1; }
    f32 to=*(volatile f32*)&endPosition, from=*(volatile f32*)&startPosition;
    f32 fraction=time/end;
    f32 difference=to-from;
    difference=difference*fraction;
    currentPosition=difference+from;
    return 1;
}
#pragma dont_inline off
#pragma fp_contract on
#pragma dont_inline on
// Instantiate the defined methods now; constructors follow static initialization.
// MWCC warns about the constructors deliberately deferred past this point.
#pragma push
#pragma supress_warnings on
template class CameraAnimation<f32>;
template class CameraAnimation<GSvec>;
#pragma pop
#pragma dont_inline off
#pragma dont_inline on
template<class T> CameraAnimation<T>::CameraAnimation() { moving=0; accelerating=0; accelerateOut=0; accelerateIn=0; acceleration=0.05f; }
#pragma dont_inline off

struct FloorModuleInterface {
    u32 reserved[6];
    const char* (*name)();
    void (*save)(s32,void*,u32);
    void (*restore)(s32,void*,u32);
    s32 (*size)(s32);
    s32 (*uid)();
};
extern "C" {
FloorModuleInterface _floorModuleCamera;
void FloorModuleInterface_clear(FloorModuleInterface*);
s32 floorRegisterModule(u8,u8,FloorModuleInterface*);
extern s32 _hModuleField;
extern u8* floordata;
void* GSmemAllocClr(u32);

}

#include <game/maximum/GSAPI/baselib/quatlib.h>
extern "C" {
u8 GSinputGetRightStickYData(s32, s32);
u8 GSinputGetRightStickXData(s32, s32);
u8 GSinputGetLeftStickYData(s32, s32);
u8 GSinputGetLeftStickXData(s32, s32);
s32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
f32 GSgfxVideoGetLastRenderTime();
f32 timeGetLastFrameSec();
u8 dbgMenuIsOpen();
u8 floorFieldCameraGetEnabled();
u8 menuIsCheck(s32);
void menuClose(s32);
s32 menuOpenCustom(s32,s32,s32*,u32,u8,s32,...);
void menuSetPosition(s32,s32,s32);
}
extern "C" f32 __float_nan[];
static inline s32 cameraFloatClass(f32 value) {
    union { f32 value; u32 bits; } number;
    number.value=value;
    switch(number.bits & 0x7f800000) {
    case 0x7f800000:
        if(number.bits & 0x7fffff) return 1;
        return 2;
    case 0:
        if(number.bits & 0x7fffff) return 5;
        return 3;
    default: return 4;
    }
}
static inline f32 cameraSqrt(f32 value) {
    if(value>0.0f) {
        f64 guess=__frsqrte(value);
        guess=0.5*guess*(3.0-guess*guess*value);
        guess=0.5*guess*(3.0-guess*guess*value);
        guess=0.5*guess*(3.0-guess*guess*value);
        value=(f32)(value*guess);
    } else if(value<0.0) return __float_nan[0];
    else if(cameraFloatClass(value)==1) return __float_nan[0];
    return value;
}
static inline f32 cameraSqrtFlat(f32 value) {
    if(value>0.0f) {
        f64 guess=__frsqrte(value);
        guess=0.5*guess*(3.0-guess*guess*value);
        guess=0.5*guess*(3.0-guess*guess*value);
        guess=0.5*guess*(3.0-guess*guess*value);
        value=(f32)(value*guess);
    } else if(value<0.0) return __float_nan[0];
    else {
        s32 cls;
        union { f32 value; u32 bits; } number;
        number.value=value;
        switch(number.bits & 0x7f800000) {
        case 0x7f800000:
            if(number.bits & 0x7fffff) cls=1;
            else cls=2;
            break;
        case 0:
            if(number.bits & 0x7fffff) cls=5;
            else cls=3;
            break;
        default: cls=4; break;
        }
        if(cls==1) return __float_nan[0];
    }
    return value;
}
static inline void cameraApplyLockedY(Vec* target) {
    if(pCamWork->flags & 0x10) { pCamWork->flags &= ~0x10; pCamWork->lockedTargetY=target->y; }
    else if(pCamWork->flags & 8) target->y=pCamWork->lockedTargetY;
}
static inline void cameraApplyFov(GScamera* camera) {
    f32 fov,aspect,nearPlane,farPlane;
    GScameraGetPerspective(camera,&fov,&aspect,&nearPlane,&farPlane);
    GScameraSetPerspective(camera,pCamWork->fov,aspect,nearPlane,farPlane);
}
extern "C" {

static inline f32 cameraAngle(f32 height,f32 distance) { return (f32)atan2(height,distance); }
static inline void cameraDisplacement(Vec* out,f32 height,f32 distance) {
    out->x=0.0f;out->y=height;out->z=distance;
}

static inline u8 cameraAnyMoving() {
    return pCamWork->targetAnimation.isMove() || pCamWork->offsetAnimation.isMove() || pCamWork->positionAnimation.isMove() || pCamWork->rotationAnimation.isMove() || pCamWork->fovAnimation.isMove();
}

}

#pragma push
#pragma opt_propagation off
extern "C" {
static void _cameraMakeStateData__F14FloorStateModePvUl(s32 mode,void* data,u32 size) {
    if(mode==1 || mode==2) {
        GScamera* camera;
        void* destination=data;
        CameraWork* work;
        camera=(GScamera*)GSresGetResource(0,0);
        work=pCamWork;
        if(work->type==4 || work->type==8) camera=animationCamera(work);
        memcpy(destination,pCamWork,sizeof(CameraWork));
        GScameraPushState(camera,(GScameraState*)((u8*)destination+sizeof(CameraWork)));
    }
}
}
#pragma pop
#pragma push
#pragma opt_propagation off
extern "C" {
static void _cameraRestoreStateData__F14FloorStateModePvUl(s32 mode,void* data,u32 size) {
    if(mode==1 || mode==2) {
        memcpy(pCamWork,data,sizeof(CameraWork));
        GScamera* camera;
        CameraWork* work;
        camera=(GScamera*)GSresGetResource(0,0);
        work=pCamWork;
        if(work->type==4 || work->type==8) camera=animationCamera(work);
        if(pCamWork->flags & 8) pCamWork->flags |= 0x10;
        GScameraPopState(camera,(GScameraState*)((u8*)data+sizeof(CameraWork)));
        GScameraSetActiveCamera(camera);
    }
}
}
#pragma pop
extern "C" {
static s32 _cameraGetStateSize__F14FloorStateMode(s32 mode) { if(mode==1 || mode==2) return 0x274; return 0; }
}
extern "C" {
static s32 _cameraGetUID__Fv() { return 17; }
}
extern "C" {
static const char* _cameraGetModuleName__Fv() { return "camera"; }
}
extern "C" {
void cameraInit() {
    GSvec offset,up,position;
    offset.param1=0.0f; offset.param2=0.0f; offset.param3=14.0f;
    up.param1=0.0f; up.param2=1.0f; up.param3=0.0f;
    position.param1=0.0f; position.param2=0.0f; position.param3=100.0f;
    memset(&_cameraWork,0,sizeof(CameraWork)); pCamWork=&_cameraWork;
    GScamera* camera=GScameraCreate();
    GSresRegisterResource(camera,0,0,0);
    cameraSetType(0); cameraSetTarget(0,100); cameraSetTargetOfs(&offset);
    _pFloorCamera=(FloorCamera*)GSmemAllocClr(*floordata_number*sizeof(FloorCamera));
    for(u32 i=0; i<*floordata_number; ++i) { _pFloorCamera[i].state=0; _pFloorCamera[i].floorID=*(u16*)(floordata+i*0x40+2); }
    cameraResetOffsets(true);
    FloorModuleInterface_clear(&_floorModuleCamera);
    _floorModuleCamera.save=_cameraMakeStateData__F14FloorStateModePvUl;
    _floorModuleCamera.restore=_cameraRestoreStateData__F14FloorStateModePvUl;
    _floorModuleCamera.size=_cameraGetStateSize__F14FloorStateMode;
    _floorModuleCamera.uid=_cameraGetUID__Fv;
    _floorModuleCamera.name=_cameraGetModuleName__Fv;
    _hModuleField=floorRegisterModule(0x80,0,&_floorModuleCamera);
    GScameraLookAt(camera,vec(&up),vec(&offset));
    GScameraSetPosition(camera,vec(&position)); GScameraSetActiveCamera(camera); GScameraLoadActiveCameraMatrix(0);
}
}
extern "C" {
void cameraSetFloorDefault(f32 height,f32 distance,f32 rotation) {
    FloorCamera* floor=currentFloorCamera();
    if(floor) {
        floor->defaultHeight=height; floor->defaultDistance=distance; floor->defaultRotation=rotation;
        if(floor->state==1) { floor->state=2; cameraSetHeight(height); cameraSetDistance(distance); cameraSetRotY(rotation); }
    }
}
}
extern "C" {
void cameraResetFloor() {
    if(pCamWork->type==6) cameraSetType(0);
    FloorCamera* floor=currentFloorCamera();
    if(floor) {
        cameraSetHeight(floor->defaultHeight); cameraSetDistance(floor->defaultDistance);
        cameraSetRotY(floor->defaultRotation); cameraSetFov(floor->defaultFov);
    }
}
}
extern "C" {
void cameraSetGScamera(GScamera* camera) {
    if(camera) {
        f32 fov,aspect,nearPlane,farPlane;
        Vec distance;
        f32 height,depth,fieldOfView,rotation;
        GScamera* target=(GScamera*)GSresGetResource(0,0);
        GScameraGetPerspective(camera,&fov,&aspect,&nearPlane,&farPlane);
        GScameraSetPerspective(target,fov,aspect,nearPlane,farPlane);
        GScameraGetDistanceVector(camera,&distance);
        cameraSetType(3);
        target->interest=camera->interest;
        target->position=camera->position;
        fieldOfView=fov;
        rotation=(f32)atan2(distance.x,distance.z);
        depth=distance.z; height=distance.y;
        FloorCamera* floor=currentFloorCamera();
        if(floor) {
            if(floor->state) { height=floor->height; depth=floor->distance; rotation=floor->rotation; }
            else {
                if(height<0.0f) height=0.0f;
                if(depth<10.0f) { depth=30.0f; height=0.0f; }
                else if(depth>500.0f) depth=500.0f;
                floor->state=1; floor->defaultHeight=height; floor->defaultDistance=depth; floor->defaultRotation=rotation; floor->defaultFov=fieldOfView;
            }
        }
        cameraSetHeight(height); cameraSetDistance(depth); cameraSetRotY(rotation); cameraSetFovValue(fieldOfView);
    }
}
}
extern "C" {
static void _cameraPadMoveUpdate__FP9_GScamera(GScamera* camera) {
    f32 ry;
    f32 x;
    f32 rx;
    f32 y;
    f32 divisor;
    f32 render;
    render=GSgfxVideoGetLastRenderTime();
    divisor=64.0f;
    if(!dbgMenuIsOpen()) {
        u32 changed=GSinputButtonsChanged(1);
        u32 pressed=GSinputButtonsPressed(1);
        if(pressed&changed&0x400) {
            if(menuIsCheck(6)) menuClose(6);
            else { menuOpenCustom(6,0,0,0,1,0); menuSetPosition(6,20,260); }
        }
        Mtx matrix,yMatrix,zMatrix;
        PSMTXRotRad(matrix,'X',pCamWork->rotation.param1); PSMTXRotRad(yMatrix,'Y',pCamWork->rotation.param2); PSMTXConcat(yMatrix,matrix,matrix);
        PSMTXRotRad(zMatrix,'Z',pCamWork->rotation.param3); PSMTXConcat(zMatrix,matrix,matrix);
        x=render*(f32)(s8)GSinputGetLeftStickXData(1,0); y=render*(f32)(s8)GSinputGetLeftStickYData(1,0);
        rx=render*(f32)(s8)GSinputGetRightStickXData(1,0); ry=render*(f32)(s8)GSinputGetRightStickYData(1,0);
        if(GSinputButtonsPressed(1)&0x40) divisor*=4.0f;
        Vec world,local;
        if(GSinputButtonsPressed(1)&0x800) { local.x=x/divisor; local.y=-y/divisor; local.z=0.0f; }
        else { local.y=0.0f; local.x=x/divisor; local.z=y/divisor; }
        PSMTXMultVec(matrix,&local,&world); PSVECAdd(vec(&pCamWork->position),&world,vec(&pCamWork->position));
        if(GSinputButtonsPressed(1)&0x20) { f32 add=ry/divisor; f32 fov=add+pCamWork->fov; cameraSetFov(fov); }
        else pCamWork->rotation.param1-=ry/(32.0f*divisor);
        pCamWork->rotation.param2-=rx/(32.0f*divisor);
        GScameraSetPosition(camera,vec(&pCamWork->position)); GScameraSetRotation(camera,vec(&pCamWork->rotation)); cameraApplyFov(camera);
    }
}
}
extern "C" {
static void _cameraPadRotateUpdate__FP9_GScamera(GScamera* camera) {
    if(!dbgMenuIsOpen()) {
        s32 render=(s32)GSgfxVideoGetLastRenderTime();
        s32 input=(s8)GSinputGetRightStickXData(1,1);
        s32 horizontal=input*render;
        render=(s32)GSgfxVideoGetLastRenderTime();
        input=(s8)GSinputGetRightStickYData(1,1);
        s32 vertical=input*render;
        f32 angle=cameraAngle(pCamWork->height,pCamWork->distance);
        f32 height=pCamWork->height, distance=pCamWork->distance;
        f32 radius=cameraSqrt((f32)(height*height)+(f32)(distance*distance));
        if(GSinputButtonsPressed(1)&0x20) { f32 fov=(f32)vertical/64.0f+pCamWork->fov;cameraSetFov(fov); }
        else if(GSinputButtonsPressed(1)&0x40) radius+=(f32)vertical/64.0f;
        else angle-=(f32)vertical/4096.0f;
        pCamWork->height=radius*(f32)sin(angle);
        pCamWork->distance=radius*(f32)cos(angle);
        if(pCamWork->distance<10.0f) pCamWork->distance=10.0f;
        else if(pCamWork->distance>500.0f) pCamWork->distance=500.0f;
        cameraSetHeight(pCamWork->height); cameraSetDistance(pCamWork->distance);
        Vec target,displacement;
        cameraDisplacement(&displacement,pCamWork->height,pCamWork->distance);
        pCamWork->rotation.param2+=(f32)horizontal/2048.0f;
        cameraSetRotY(pCamWork->rotation.param2);
        Mtx matrix;
        PSMTXRotRad(matrix,'Y',pCamWork->rotation.param2); PSMTXMultVec(matrix,&displacement,&displacement);
        CameraWork* work=pCamWork;
        Vec* base=vec(&work->targetPosition);
        Vec* offset=vec(&work->targetOffset);
        PSVECAdd(base,offset,&target);
        PSVECAdd(&target,&displacement,vec(&pCamWork->position));
        cameraApplyLockedY(&target);
        GScameraSetPosition(camera,vec(&pCamWork->position)); GScameraLookAt(camera,vec(&gUpVec),&target);
        pCamWork->rotation.param1=-cameraAngle(pCamWork->height,pCamWork->distance);
        cameraApplyFov(camera);
    }
}
}
extern "C" {
static void _cameraOffsetAnimeUpdate__FP9_GScamera(GScamera* camera) {
    GScamera* animation=animationCamera(pCamWork);
    if(!animation || animation==camera || !GScameraIsAnimating(animation) || GScameraHasAnimationEnded(animation)) return;
    f32 fov,aspect,nearPlane,farPlane;
    Quaternion quaternion;
    Vec position,target,up;
    HSD_Quaternion rotation;
    Quaternion inverseCopy,inverse;
    Mtx positionMatrix,targetMatrix,upMatrix;
    GScameraGetPerspective(animation,&fov,&aspect,&nearPlane,&farPlane);
    GScameraGetLookAt(animation,&up,&target); GScameraGetPosition(animation,&position);
    up.x=0.0f; up.y=1.0f; up.z=0.0f;
    position.x*=pCamWork->offsetScale.param1;
    position.y*=pCamWork->offsetScale.param2;
    position.z*=pCamWork->offsetScale.param3;
    target.x*=pCamWork->offsetScale.param1;
    target.y*=pCamWork->offsetScale.param2;
    target.z*=pCamWork->offsetScale.param3;
    EulerToQuat((HSD_Vec3*)&pCamWork->offsetRotation,&rotation);
    quaternion.x=rotation.x; quaternion.y=rotation.y; quaternion.z=rotation.z; quaternion.w=rotation.w;
    PSMTXQuat(positionMatrix,&quaternion); PSMTXMultVecSR(positionMatrix,&position,&position);
    PSMTXQuat(targetMatrix,&quaternion); PSMTXMultVecSR(targetMatrix,&target,&target);
    PSQUATInverse(&quaternion,&inverse);
    inverseCopy.x=inverse.x; inverseCopy.y=inverse.y; inverseCopy.z=inverse.z; inverseCopy.w=inverse.w;
    PSMTXQuat(upMatrix,&inverseCopy); PSMTXMultVecSR(upMatrix,&up,&up);
    if(pCamWork->flags & 1) { target.x*=-1.0f; up.x*=-1.0f; position.x*=-1.0f; }
    if(pCamWork->flags & 2) { target.y*=-1.0f; up.y*=-1.0f; position.y*=-1.0f; }
    if(pCamWork->flags & 4) { target.z*=-1.0f; up.z*=-1.0f; position.z*=-1.0f; }
    PSVECAdd(&position,vec(&pCamWork->offsetPosition),&position);
    PSVECAdd(&target,vec(&pCamWork->offsetPosition),&target);
    cameraApplyLockedY(&target);
    GScameraSetPerspective(camera,fov,aspect,nearPlane,farPlane);
    GScameraSetPosition(camera,&position); GScameraLookAt(camera,&up,&target);
    copyVector(&pCamWork->position,(GSvec*)&position);
    copyVector(&pCamWork->targetPosition,&pCamWork->offsetPosition);
    Vec offset;
    PSVECSubtract(&target,vec(&pCamWork->targetPosition),&offset);
    f32 offsetX=offset.x,offsetY=offset.y,offsetZ=offset.z;
    CameraWork* work=pCamWork;
    work->targetOffset.param1=offsetX;
    work->targetOffset.param2=offsetY;
    work->targetOffset.param3=offsetZ;
    PSVECSubtract(&position,&target,&position);
    pCamWork->height=position.y;
    pCamWork->distance=cameraSqrt(position.x*position.x+position.z*position.z);
    pCamWork->rotation.param2=(f32)atan2(position.x,position.z);
    pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance);
}
}
extern "C" {
void cameraRefreshTargetPos() {
    if(pCamWork->targetGroup || pCamWork->targetID) {
        GSmodel* model=(GSmodel*)GSresGetResource(pCamWork->targetGroup,pCamWork->targetID);
        if(model) {
            GSmodelGetPosition(model,&pCamWork->targetPosition);
            if(pCamWork->targetPart>=0) {
                GSpart* part=GSmodelGetPart(model,pCamWork->targetPart);
                if(part) {
                    GSpartGetTransform(part,vec(&pCamWork->targetOffset),0,0);
                    PSVECSubtract(vec(&pCamWork->targetOffset),vec(&pCamWork->targetPosition),vec(&pCamWork->targetOffset));
                    PSVECAdd(vec(&pCamWork->targetOffset),vec(&pCamWork->partTargetOffset),vec(&pCamWork->targetOffset));
                    GSpartFree(part);
                }
            }
        }
    }
}
}
extern "C" {
void cameraUpdate() {
    GScamera* camera=(GScamera*)GSresGetResource(0,0);
    CameraWork* work=pCamWork;
    if(work->moving==1) {
        f32 delta=timeGetLastFrameSec();
        if(pCamWork->targetAnimation.update(delta)) copyVector(&pCamWork->targetPosition,pCamWork->targetAnimation.getCurrentPos());
        if(pCamWork->offsetAnimation.update(delta)) copyVector(&pCamWork->targetOffset,pCamWork->offsetAnimation.getCurrentPos());
        if(pCamWork->positionAnimation.update(delta)) copyVector(&pCamWork->position,pCamWork->positionAnimation.getCurrentPos());
        if(pCamWork->rotationAnimation.update(delta)) copyVector(&pCamWork->rotation,pCamWork->rotationAnimation.getCurrentPos());
        if(pCamWork->fovAnimation.update(delta)) pCamWork->fov=*pCamWork->fovAnimation.getCurrentPos();
        Vec distance;
        switch(pCamWork->type) {
        case 0:
        case 1:
        case 5:
            if(floorFieldCameraDataExist() && floorFieldCameraGetEnabled()) {
                PSVECAdd((Vec*)&pCamWork->targetPosition,(Vec*)&pCamWork->targetOffset,&distance);
                PSVECSubtract((Vec*)&pCamWork->position,&distance,&distance);
                pCamWork->height=distance.y;
                pCamWork->distance=cameraSqrtFlat(distance.x*distance.x+distance.z*distance.z);
            }
            break;
        case 6:
            break;
        case 7: {
            PSVECSubtract((Vec*)&pCamWork->position,(Vec*)&pCamWork->targetPosition,&distance);
            pCamWork->height=distance.y;
            pCamWork->distance=cameraSqrtFlat(distance.x*distance.x+distance.z*distance.z);
            if(!pCamWork->rotationAnimation.isMove() && !(pCamWork->flags&0x20)) pCamWork->rotation.param2=(f32)atan2(distance.x,distance.z);
            break;
        }
        case 8:
            break;
        }
        u8 busy;
        if(!pCamWork->targetAnimation.isMove() && !pCamWork->offsetAnimation.isMove() && !pCamWork->positionAnimation.isMove() && !pCamWork->rotationAnimation.isMove() && !pCamWork->fovAnimation.isMove()) busy=0;
        else busy=1;
        if(!busy) pCamWork->moving=0;
    } else {
        switch(work->type) {
        case 0: case 1: case 5: case 7: cameraRefreshTargetPos(); break;
        case 4:
            camera=animationCamera(work);
            if(!camera) { pCamWork->animationGroup=0; pCamWork->animationID=0; cameraSetType(pCamWork->previousType); cameraSetTarget(0,100); camera=(GScamera*)GSresGetResource(0,0); }
            break;
        case 2: case 3: case 6: case 8:
            break;
        }
    }
    switch(pCamWork->type) {
    case 0: {
        Vec distance,displacement,target;
        f32 h=pCamWork->height, d=pCamWork->distance; displacement.y=h; displacement.x=0.0f; displacement.z=d;
        Mtx matrix;
        PSMTXRotRad(matrix,'Y',pCamWork->rotation.param2); PSMTXMultVec(matrix,&displacement,&displacement);
        PSVECAdd((Vec*)&pCamWork->targetPosition,(Vec*)&pCamWork->targetOffset,&target); PSVECAdd(&target,&displacement,(Vec*)&pCamWork->position);
        PSVECSubtract((Vec*)&pCamWork->position,&target,&distance);
        if(distance.x<0.00001f && distance.x>-0.00001f && distance.z<0.00001f && distance.z>-0.00001f) pCamWork->position.param3+=1.0f;
        cameraApplyLockedY(&target);
        GScameraSetPosition(camera,(Vec*)&pCamWork->position); GScameraLookAt(camera,vec(&gUpVec),&target);
        pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance);
        cameraApplyFov(camera); break;
    }
    case 1: case 2: {
        Vec distance,target;
        PSVECAdd((Vec*)&pCamWork->targetPosition,(Vec*)&pCamWork->targetOffset,&target); cameraApplyLockedY(&target);
        GScameraSetPosition(camera,(Vec*)&pCamWork->position); GScameraLookAt(camera,vec(&gUpVec),&target);
        PSVECSubtract((Vec*)&pCamWork->position,&target,&distance);
        pCamWork->height=distance.y; pCamWork->distance=cameraSqrt(distance.x*distance.x+distance.z*distance.z);
        pCamWork->rotation.param2=(f32)atan2(distance.x,distance.z); pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance);
        cameraApplyFov(camera); break;
    }
    case 6: _cameraPadMoveUpdate__FP9_GScamera(camera); break;
    case 5: _cameraPadRotateUpdate__FP9_GScamera(camera); break;
    case 3: {
        Vec up,target;
        GScameraSetPosition(camera,(Vec*)&pCamWork->position); GScameraSetRotation(camera,(Vec*)&pCamWork->rotation); GScameraGetLookAt(camera,&up,&target);
        PSVECSubtract(&target,(Vec*)&pCamWork->targetOffset,(Vec*)&pCamWork->targetPosition); cameraApplyFov(camera); break;
    }
    case 8: _cameraOffsetAnimeUpdate__FP9_GScamera(camera); GScameraLoadActiveCameraMatrix(-1); return;
    case 7: {
        Vec displacement,target;
        f32 h=pCamWork->height, d=pCamWork->distance; displacement.y=h; displacement.x=0.0f; displacement.z=d;
        Mtx matrix;
        PSMTXRotRad(matrix,'Y',pCamWork->rotation.param2); PSMTXMultVec(matrix,&displacement,&displacement);
        PSVECAdd((Vec*)&pCamWork->targetPosition,&displacement,(Vec*)&pCamWork->position);
        PSVECAdd((Vec*)&pCamWork->targetPosition,(Vec*)&pCamWork->targetOffset,&target);
        PSMTXRotRad(matrix,'Z',pCamWork->offsetRotation.param3); PSMTXMultVec(matrix,vec(&gUpVec),&displacement);
        PSVECAdd(&target,(Vec*)&pCamWork->offsetPosition,&target); cameraApplyLockedY(&target);
        GScameraSetPosition(camera,(Vec*)&pCamWork->position); GScameraLookAt(camera,&displacement,&target);
        pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance); cameraApplyFov(camera); break;
    }
    }
    GScameraSetActiveCamera(camera); GScameraLoadActiveCameraMatrix(-1);
}
}
extern "C" {
u8 cameraSetType(u8 type) {
    pCamWork->flags=0;
    if(pCamWork->type==type) return type;
    u8 previous=pCamWork->type; pCamWork->type=type; pCamWork->flags &= ~0x20; return previous;
}
}
extern "C" {
u8 cameraGetType() { return pCamWork->type; }
}
extern "C" {
GScamera* cameraGetActive() {
    GScamera* camera=GScameraGetActiveCamera();
    if(camera) return camera;
    camera=(GScamera*)GSresGetResource(0,0); GScameraSetActiveCamera(camera); return camera;
}
}
extern "C" {
void cameraSetTarget(u32 group,u32 id) { pCamWork->targetGroup=group; pCamWork->targetID=id; pCamWork->targetPart=-1; }
}
extern "C" {
void cameraSetTargetExt(u32 group,u32 id,s32 part) {
    pCamWork->targetGroup=group; pCamWork->targetID=id; pCamWork->targetPart=part;
    GSvec* offset=&pCamWork->partTargetOffset; offset->param1=0.0f; offset->param2=0.0f; offset->param3=0.0f;
}
}
#pragma push
#pragma scheduling off
extern "C" {
void cameraSetPartTargetOffset(const GSvec* value) {
    CameraWork* work=pCamWork; work->partTargetOffset.param1=value->param1; work->partTargetOffset.param2=value->param2; work->partTargetOffset.param3=value->param3;
}
}
#pragma pop
#pragma push
#pragma scheduling off
extern "C" {
void cameraSetTargetOfs(const GSvec* value) { CameraWork* work=pCamWork; work->targetOffset.param1=value->param1; work->targetOffset.param2=value->param2; work->targetOffset.param3=value->param3; }
}
#pragma pop
extern "C" {
void cameraGetTargetOfs(GSvec* out) { copyVector(out,&pCamWork->targetOffset); }
}
#pragma push
#pragma scheduling off
extern "C" {
void cameraSetTargetPos(const GSvec* value) { CameraWork* work=pCamWork; work->targetPosition.param1=value->param1; work->targetPosition.param2=value->param2; work->targetPosition.param3=value->param3; }
}
#pragma pop
extern "C" {
void cameraGetTargetPos(GSvec* out) { copyVector(out,&pCamWork->targetPosition); }
}
#pragma push
#pragma scheduling off
extern "C" {
void cameraSetPosition(const GSvec* value) { CameraWork* work=pCamWork; work->position.param1=value->param1; work->position.param2=value->param2; work->position.param3=value->param3; }
}
#pragma pop
extern "C" {
void cameraGetPosition(GSvec* out) { copyVector(out,&pCamWork->position); }
}
extern "C" {
void cameraSetRotation(const GSvec* value) {
    GScamera* camera=(GScamera*)GSresGetResource(0,0);
    volatile f32* target=(volatile f32*)&pCamWork->rotation;
    const volatile f32* source=(const volatile f32*)value;
    target[0]=source[0]; target[1]=source[1]; target[2]=source[2];
    GScameraSetRotation(camera,vec(value));
}
}
extern "C" {
void cameraGetRotation(GSvec* out) { copyVector(out,&pCamWork->rotation); }
}
extern "C" {
void cameraMoveTarget(u32 mode,u32 group,u32 id,f32 duration) {
    GSvec position;position.param1=0.0f;position.param2=0.0f;position.param3=0.0f;
    cameraSetTarget(group,id);
    GSmodel* model=(GSmodel*)GSresGetResource(group,id);
    if(model) GSmodelGetPosition(model,&position);
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetTargetPos(&position); return; }
    pCamWork->moving=1; pCamWork->targetAnimation.start(&pCamWork->targetPosition,&position,duration);
}
}
extern "C" {
void cameraMoveTargetPos(u32 mode,const GSvec* position,f32 duration) {
    if(duration < 1e-7f && duration > -1e-7f) {
        volatile f32* target=(volatile f32*)&pCamWork->targetPosition;
        const volatile f32* source=(const volatile f32*)position;
        target[0]=source[0]; target[1]=source[1]; target[2]=source[2];
        return;
    }
    pCamWork->moving=1; pCamWork->targetAnimation.start(&pCamWork->targetPosition,position,duration);
}
}
extern "C" {
void cameraMoveTargetOfs(u32 mode,const GSvec* position,f32 duration) { pCamWork->moving=1; pCamWork->offsetAnimation.start(&pCamWork->targetOffset,position,duration); }
}
extern "C" {
void cameraMoveTargetXYZ(u32 mode,f32 x,f32 y,f32 z,f32 duration) {
    GSvec position; position.param1=x; position.param2=y; position.param3=z;
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetTargetPos(&position); return; }
    pCamWork->moving=1; pCamWork->targetAnimation.start(&pCamWork->targetPosition,&position,duration);
}
}
extern "C" {
void cameraMovePosition(u32 mode,const GSvec* position,f32 duration) {
    if(duration < 1e-7f && duration > -1e-7f) {
        volatile f32* target=(volatile f32*)&pCamWork->position;
        const volatile f32* source=(const volatile f32*)position;
        target[0]=source[0]; target[1]=source[1]; target[2]=source[2];
        return;
    }
    pCamWork->moving=1; pCamWork->positionAnimation.start(&pCamWork->position,position,duration);
}
}
extern "C" {
void cameraMovePositionXYZ(u32 mode,f32 x,f32 y,f32 z,f32 duration) {
    GSvec position; position.param1=x; position.param2=y; position.param3=z;
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetPosition(&position); return; }
    pCamWork->moving=1; pCamWork->positionAnimation.start(&pCamWork->position,&position,duration);
}
}
extern "C" {
void cameraMoveFov(u32 mode,f32 fov,f32 duration) { pCamWork->moving=1; pCamWork->fovAnimation.start(&pCamWork->fov,&fov,duration); }
}
extern "C" {
void cameraMoveRotation(u32 mode,const GSvec* rotation,f32 duration) {
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetRotation(rotation); return; }
    pCamWork->moving=1; pCamWork->rotationAnimation.start(&pCamWork->rotation,rotation,duration);
}
}
extern "C" {
void cameraMoveRotationXYZ(u32 mode,f32 x,f32 y,f32 z,f32 duration) {
    GSvec rotation; rotation.param1=x; rotation.param2=y; rotation.param3=z;
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetRotation(&rotation); return; }
    pCamWork->moving=1; pCamWork->rotationAnimation.start(&pCamWork->rotation,&rotation,duration);
}
}
extern "C" {
void cameraMoveTargetPosAcc(f32 acceleration) { pCamWork->targetAnimation.setAcceleration(acceleration); }
}
extern "C" {
void cameraMoveTargetOfsAcc(f32 acceleration) { pCamWork->offsetAnimation.setAcceleration(acceleration); }
}
extern "C" {
void cameraMovePositionAcc(f32 acceleration) { pCamWork->positionAnimation.setAcceleration(acceleration); }
}
extern "C" {
void cameraMoveRotationAcc(f32 acceleration) { pCamWork->rotationAnimation.setAcceleration(acceleration); }
}
extern "C" {
void cameraMoveFovAcc(f32 acceleration) { pCamWork->fovAnimation.setAcceleration(acceleration); }
}
extern "C" {
void cameraReturn(f32 duration,u8 wait) {
    GScamera* camera=GScameraGetActiveCamera();
    if(floorFieldCameraDataExist()) {
        if(pCamWork->type==3) {
            Vec position,front;
            GSvec offset;
            offset.param1=pCamWork->targetOffset.param1; offset.param2=pCamWork->targetOffset.param2; offset.param3=pCamWork->targetOffset.param3;
            GScameraGetFrontVector(camera,&front);
            PSVECScale(&front,&front,pCamWork->distance);
            GScameraGetPosition(camera,&position);
            PSVECAdd(&position,&front,&position);
            PSVECSubtract(&position,vec(&offset),&position);
            GSvec* target=&pCamWork->targetPosition;
            target->param1=position.x; target->param2=position.y; target->param3=position.z;
        }
        cameraSetType(0); floorFieldCameraEnable(); floorFieldCameraBlend(duration);
    } else {
        cameraSetType(0);
        FloorCamera* floor=currentFloorCamera();
        if(floor) { cameraSetHeight(floor->defaultHeight); cameraSetDistance(floor->defaultDistance); cameraSetFov(floor->defaultFov); }
        cameraMoveTarget(0,0,100,duration);
        cameraMoveRotationXYZ(0,0.0f,floor->defaultRotation,0.0f,duration);
    }
    for(;;) {
        if(!(pCamWork->targetAnimation.isMove() || pCamWork->offsetAnimation.isMove() || pCamWork->positionAnimation.isMove() || pCamWork->rotationAnimation.isMove() || pCamWork->fovAnimation.isMove())) break;
        if(!wait) break;
        GSthreadSwitch();
    }
}
}
extern "C" {
s32 cameraMoveEndCheck(u8 wait) {
    for(;;) {
        if(!pCamWork->targetAnimation.isMove() && !pCamWork->offsetAnimation.isMove() && !pCamWork->positionAnimation.isMove() && !pCamWork->rotationAnimation.isMove() && !pCamWork->fovAnimation.isMove()) return 0;
        if(wait) GSthreadSwitch(); else return 1;
    }
}
}
extern "C" {
s32 cameraMoveEndCheckSpecial(u8 wait) {
    for(;;) {
        if(!pCamWork->targetAnimation.isMove() && !pCamWork->positionAnimation.isMove() && !pCamWork->rotationAnimation.isMove()) return 0;
        if(wait) GSthreadSwitch(); else return 1;
    }
}
}
extern "C" {
void cameraMoveStop() {
    pCamWork->targetAnimation.stop(); pCamWork->offsetAnimation.stop(); pCamWork->positionAnimation.stop(); pCamWork->rotationAnimation.stop(); pCamWork->fovAnimation.stop(); pCamWork->moving=0;
}
}
extern "C" {
void cameraPlayAnime(u32 group,u32 id,u8 loop,f32 frame) {
    if(pCamWork->animationGroup || pCamWork->animationID) cameraStopAnime();
    u8 previous=cameraSetType(4);
    pCamWork->animationGroup=group; pCamWork->animationID=id; pCamWork->previousType=previous;
    GScamera* camera=animationCamera(pCamWork);
    if(camera) {
        GScameraSetAnimIndex(camera,0); if(loop) GScameraSetAnimType(camera,1); else GScameraSetAnimType(camera,0);
        GScameraSetAnimRate(camera,0.5f); GScameraSetAnimFrame(camera,frame); GScameraStartAnimation(camera); GScameraSetActiveCamera(camera);
    }
}
}
extern "C" {
void cameraPlayOffsetAnime(u32 group,u32 id,s32 frame,u8 loop) {
    if(pCamWork->animationGroup || pCamWork->animationID) cameraStopAnime();
    u8 previous=cameraSetType(8);
    pCamWork->animationGroup=group; pCamWork->animationID=id; pCamWork->previousType=previous;
    GScamera* camera=animationCamera(pCamWork);
    if(camera) {
        GScameraSetAnimIndex(camera,0); if(loop) GScameraSetAnimType(camera,1); else GScameraSetAnimType(camera,0);
        GScameraSetAnimRate(camera,0.5f); GScameraSetAnimFrame(camera,(f32)frame); GScameraStartAnimation(camera);
        cameraResetOffsets(false);
        GScameraSetActiveCamera((GScamera*)GSresGetResource(0,0));
    }
}
}
extern "C" {
s32 cameraWaitSyncAnime(u8 wait) {
    GScamera* camera=animationCamera(pCamWork);
    if(!camera) return 0;
    if(wait) {
        for(;;) {
            if(GScameraHasAnimationEnded(camera)) break;
            if(!GSthreadGetCurrentThread()) { GSlogWrite("cameraWaitSyncAnime()  スレッドから呼ぶようにしてください\n"); break; }
            GSthreadSwitch();
        }
    } else if(!GScameraHasAnimationEnded(camera)) return 1;
    return 0;
}
}
extern "C" {
void cameraStopAnime() {
    GScamera* camera=animationCamera(pCamWork);
    pCamWork->animationGroup=0; pCamWork->animationID=0;
    if(camera) GScameraStopAnimation(camera);
}
}
extern "C" {
void cameraPauseAnime() { GScamera* camera=animationCamera(pCamWork); if(camera) GScameraStopAnimation(camera); }
}
extern "C" {
void cameraResumeAnime() { GScamera* camera=animationCamera(pCamWork); if(camera) GScameraStartAnimation(camera); }
}
extern "C" {
void cameraSetAnimeRate(f32 rate) { GScamera* camera=animationCamera(pCamWork); if(camera) GScameraSetAnimRate(camera,rate); }
}
extern "C" {
void cameraSetTargetOfsXYZ(f32 x,f32 y,f32 z) { CameraWork* work=pCamWork; work->targetOffset.param1=x; work->targetOffset.param2=y; work->targetOffset.param3=z; }
}
extern "C" {
void cameraSetTargetPosXYZ(f32 x,f32 y,f32 z) { CameraWork* work=pCamWork; work->targetPosition.param1=x; work->targetPosition.param2=y; work->targetPosition.param3=z; }
}
extern "C" {
void cameraSetRotationXYZ(f32 x,f32 y,f32 z) {
    GSvec rotation; rotation.param1=x; rotation.param2=y; rotation.param3=z;
    GScamera* camera=(GScamera*)GSresGetResource(0,0);
    copyVector(&pCamWork->rotation,&rotation);
    GScameraSetRotation(camera,vec(&rotation));
}
}
extern "C" {
void cameraSetHeight(f32 value) { FloorCamera* floor=currentFloorCamera(); if (floor) floor->height=value; pCamWork->height=value; }
}
extern "C" {
void cameraSetDistance(f32 value) { FloorCamera* floor=currentFloorCamera(); if (floor) floor->distance=value; pCamWork->distance=value; }
}
extern "C" {
void cameraSetRotY(f32 value) { FloorCamera* floor=currentFloorCamera(); if (floor) floor->rotation=value; pCamWork->rotation.param2=value; }
}
extern "C" {
void cameraSetFov(f32 value) { cameraSetFovValue(value); }
}
extern "C" {
f32 cameraGetHeight() { return pCamWork->height; }
}
extern "C" {
f32 cameraGetDistance() { return pCamWork->distance; }
}
extern "C" {
f32 cameraGetRotY() { return pCamWork->rotation.param2; }
}
extern "C" {
f32 cameraGetFov() { return pCamWork->fov; }
}
#pragma push
#pragma scheduling off
extern "C" {
void cameraSetOffsetPosition(const GSvec* v) { CameraWork* work=pCamWork; work->offsetPosition.param1=v->param1; work->offsetPosition.param2=v->param2; work->offsetPosition.param3=v->param3; }
}
#pragma pop
#pragma push
#pragma scheduling off
extern "C" {
void cameraSetOffsetRotation(const GSvec* v) { CameraWork* work=pCamWork; work->offsetRotation.param1=v->param1; work->offsetRotation.param2=v->param2; work->offsetRotation.param3=v->param3; }
}
#pragma pop
#pragma push
#pragma scheduling off
extern "C" {
void cameraSetOffsetScale(const GSvec* v) { CameraWork* work=pCamWork; work->offsetScale.param1=v->param1; work->offsetScale.param2=v->param2; work->offsetScale.param3=v->param3; }
}
#pragma pop
extern "C" {
void cameraSetMirrorFlag(s32 flags) { pCamWork->flags &= 0x18; pCamWork->flags |= flags; }
}
extern "C" {
void cameraLockYTarget(u8 flag) { if (flag) pCamWork->flags |= 0x18; else pCamWork->flags &= ~8; }
}
extern "C" {
void fn_80196A14(u8 flag) { if (flag) pCamWork->flags |= 0x20; else pCamWork->flags &= ~0x20; }
}
