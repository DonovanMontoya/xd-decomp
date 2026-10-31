#include <game/pxdvs/app/wazaSequence/billboardPrivate.hpp>
void operator delete(void*);
extern "C" {
void GSparticleFree(_GSparticleBank*);void GSresFreeResource(u32,u32);void GSparticleDestroyAllGenerators(_GSparticleBank*,s32);void GSmodelStopAnimation(GSmodel*);void GSmodelStopTexAnimation(GSmodel*);void GSmodelSetVisibility(GSmodel*,u8);
GScamera*cameraGetActive();void GScameraLoadActiveCameraMatrix(s32);void GScameraGetPosition(GScamera*,GSvec*);void GScameraGetLookAt(GScamera*,GSvec*,GSvec*);void GScameraGetPerspective(GScamera*,f32*,f32*,f32*,f32*);void PSVECSubtract(GSvec*,GSvec*,GSvec*);void PSVECNormalize(GSvec*,GSvec*);void PSVECScale(GSvec*,GSvec*,f32);void PSVECAdd(GSvec*,GSvec*,GSvec*);double tan(double);
u32 GSparticleGetGeneratorLife(_GSparticleGen*);void GSparticleSetGeneratorPosition(_GSparticleGen*,GSvec*);u8 GSmodelCanAnimate(GSmodel*);u8 GSmodelHasAnimationEnded(GSmodel*);u8 GSmodelCanTexAnimate(GSmodel*);u8 GSmodelHasTexAnimationEnded(GSmodel*);GSbound*GSmodelGetBound(GSmodel*);void GSboundGetSize(GSbound*,GSvec*,GSvec*,GSvec*);void GSmodelSetPosition(GSmodel*,GSvec*);void GSmodelSetScale(GSmodel*,GSvec*);
_GSparticleGen*GSparticleCreateGenerator(_GSparticleBank*,u16,s32);void GSmodelSetBoundCheck(GSmodel*,u8);void GSmodelSetRenderLayer(GSmodel*,s32,s32*);void GSmodelSetAnimIndex(GSmodel*,u16);void GSmodelSetAnimType(GSmodel*,s32);void GSmodelSetAnimRate(GSmodel*,f32);void GSmodelSetAnimFrame(GSmodel*,f32);void GSmodelStartAnimation(GSmodel*);void GSmodelSetTexAnimIndex(GSmodel*,u16);void GSmodelSetTexAnimType(GSmodel*,s32);void GSmodelSetTexAnimRate(GSmodel*,f32);void GSmodelSetTexAnimFrame(GSmodel*,f32);void GSmodelStartTexAnimation(GSmodel*);u32 wazaSequenceSysGetResID();void loadModel(u32,u32,u32,u32);void GSresIsUniqueID(u32,u32,u32);void*GSresGetResource(u32,u32);
}
billboardEffect::~billboardEffect(){Stop();if(bank)GSparticleFree(bank);if(modelResource)GSresFreeResource(20000,modelResource);if(particleResource)GSresFreeResource(20000,particleResource);}
void billboardEffect::_stop(){if(bank)GSparticleDestroyAllGenerators(bank,1);if(model){GSmodelStopAnimation(model);GSmodelStopTexAnimation(model);GSmodelSetVisibility(model,0);}}
bool billboardEffect::_update(f32 dt) {
    GScamera* cam = cameraGetActive();
    bool result = false;
    GSvec pos;
    GSvec scale;
    GSvec target;
    GSvec lookAt;
    GSvec size;
    f32 fov, near, aspect, far;

    pos.param1 = 0.0f;
    pos.param2 = 0.0f;
    pos.param3 = 0.0f;
    scale.param1 = 1.0f;
    scale.param2 = 1.0f;
    scale.param3 = 1.0f;
    if (cam != 0) {
        GScameraLoadActiveCameraMatrix(6);
        GScameraGetPosition(cam, &pos);
        GScameraGetLookAt(cam, &lookAt, &target);
        PSVECSubtract(&target, &pos, &lookAt);
        PSVECNormalize(&lookAt, &lookAt);
        GScameraGetPerspective(cam, &fov, &aspect, &near, &far);
        near += 1.0f;
        fov = 0.017453292f * fov;
        fov *= 0.5f;
        scale.param2 = 2.0f * near * (f32)tan(fov);
        scale.param1 = scale.param2 * aspect;
        scale.param3 = 0.0f;
        PSVECScale(&lookAt, &lookAt, near);
        PSVECAdd(&pos, &lookAt, &pos);
    }
    if (generator != 0) {
        if (GSparticleGetGeneratorLife(generator) != 0) {
            GSparticleSetGeneratorPosition(generator, &pos);
            result = true;
        }
    }
    if (model != 0) {
        if ((GSmodelCanAnimate(model) && !GSmodelHasAnimationEnded(model)) ||
            (GSmodelCanTexAnimate(model) && !GSmodelHasTexAnimationEnded(model))) {
            GSboundGetSize(GSmodelGetBound(model), &size, 0, 0);
            scale.param1 = scale.param1 / size.param1;
            scale.param2 = scale.param2 / size.param2;
            GSmodelSetPosition(model, &pos);
            GSmodelSetScale(model, &scale);
            result = true;
        }
    }
    return result;
}
bool billboardEffect::_start(){if(!model&&!bank)return false;if(bank)generator=GSparticleCreateGenerator(bank,generatorIndex,1);if(model){s32 layer[]={6};GSmodelSetVisibility(model,1);GSmodelSetBoundCheck(model,0);GSmodelSetRenderLayer(model,1,layer);if(GSmodelCanAnimate(model)){GSmodelSetAnimIndex(model,animation);GSmodelSetAnimType(model,type);GSmodelSetAnimRate(model,0.5f);GSmodelSetAnimFrame(model,0);GSmodelStartAnimation(model);}if(GSmodelCanTexAnimate(model)){GSmodelSetTexAnimIndex(model,animation);GSmodelSetTexAnimType(model,type);GSmodelSetTexAnimRate(model,0.5f);GSmodelSetTexAnimFrame(model,0);GSmodelStartTexAnimation(model);}}return true;}
struct BillboardRecord{u32 length,modelID,pad8,padC,animation,generator,type,pad1C;};
billboardEffect::billboardEffect(u8**data){u32 resource;BillboardRecord*record=(BillboardRecord*)*data;animation=record->animation;switch(record->type){case 0:type=0;break;case 1:type=1;break;}generatorIndex=record->generator;*data+=32;*data=(u8*)(((u32)*data+31)&~31);model=0;bank=0;generator=0;modelResource=0;resource=record->modelID;if(resource){modelResource=wazaSequenceSysGetResID();loadModel(resource,20000,0,modelResource);GSresIsUniqueID(20000,modelResource,0);model=(GSmodel*)GSresGetResource(20000,modelResource);if(model)GSmodelSetVisibility(model,0);}*data+=(record->length+31)&~31;particleResource=0;}
