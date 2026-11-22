#ifndef HSD_AOBJ_H
#define HSD_AOBJ_H
#include "game/maximum/GSAPI/baselib/fobj.h"
#include "game/maximum/GSAPI/baselib/animation_objects.h"
typedef struct HSD_AObjDesc HSD_AObjDesc;
typedef struct HSD_AnimJoint HSD_AnimJoint;
#ifdef __cplusplus
extern "C" {
#endif
typedef union _callbackArg {
    float f;
    unsigned int d;
    void* v;
} callbackArg;

struct HSD_AObj {
    unsigned int flags;
    float curr_frame;
    float rewind_frame;
    float end_frame;
    float framerate;
    HSD_FObj* fobj;
    struct HSD_Obj* hsd_obj;
};

struct HSD_AObjDesc {
    unsigned int flags;
    float end_frame;
    HSD_FObjDesc* fobjdesc;
    /// The descriptor of the object to animate, whose address is the key
    /// that object is registered under once loaded (#HSD_IDGetDataFromTable):
    /// a joint, a material, or another kind. Loaded as a joint if nothing is
    /// registered under it yet.
    void* obj_id;
};

struct HSD_AnimJoint {
    HSD_AnimJoint* child;
    HSD_AnimJoint* next;
    HSD_AObjDesc* aobjdesc;
    HSD_RObjAnimJoint* robj_anim;
    unsigned int flags;
};

void HSD_AObjInitAllocData(void);
HSD_ObjAllocData* HSD_AObjGetAllocData(void);
unsigned int HSD_AObjGetFlags(HSD_AObj* aobj);
void HSD_AObjInitEndCallBack(void);
void HSD_AObjInvokeCallBacks(void);
void HSD_AObjReqAnim(HSD_AObj* aobj, float frame);

void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj,
                           HSD_ObjUpdateFunc update_func);

HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc);
void HSD_AObjRemove(HSD_AObj* aobj);
void _HSD_AObjForgetMemory(void* low, void* high);


#ifdef __cplusplus
}
#endif
#endif
