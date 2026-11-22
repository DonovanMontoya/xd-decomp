#ifndef HSD_ANIMATION_H
#define HSD_ANIMATION_H

typedef struct HSD_AObj HSD_AObj;

typedef enum _HSD_Type {
    AOBJ_TYPE = 1,
    COBJ_TYPE,
    DOBJ_TYPE,
    FOBJ_TYPE,
    FOG_TYPE,
    JOBJ_TYPE,
    LOBJ_TYPE,
    MOBJ_TYPE,
    POBJ_TYPE,
    ROBJ_TYPE,
    TOBJ_TYPE,
    WOBJ_TYPE,
    RENDER_TYPE,
    CHAN_TYPE,
    TEVREG_TYPE,
    CBOBJ_TYPE,
    HSD_MAX_TYPE,
} HSD_Type;

#define MASK_OF(type) (1 << ((type) - 1))

typedef enum _HSD_TypeMask {
    AOBJ_MASK = MASK_OF(AOBJ_TYPE),
    COBJ_MASK = MASK_OF(COBJ_TYPE),
    DOBJ_MASK = MASK_OF(DOBJ_TYPE),
    FOBJ_MASK = MASK_OF(FOBJ_TYPE),
    FOG_MASK = MASK_OF(FOG_TYPE),
    JOBJ_MASK = MASK_OF(JOBJ_TYPE),
    LOBJ_MASK = MASK_OF(LOBJ_TYPE),
    MOBJ_MASK = MASK_OF(MOBJ_TYPE),
    POBJ_MASK = MASK_OF(POBJ_TYPE),
    ROBJ_MASK = MASK_OF(ROBJ_TYPE),
    TOBJ_MASK = MASK_OF(TOBJ_TYPE),
    WOBJ_MASK = MASK_OF(WOBJ_TYPE),
    RENDER_MASK = MASK_OF(RENDER_TYPE),
    CHAN_MASK = MASK_OF(CHAN_TYPE),
    TEVREG_MASK = MASK_OF(TEVREG_TYPE),
    CBOBJ_MASK = MASK_OF(CBOBJ_TYPE),
    ALL_TYPE_MASK = MASK_OF(HSD_MAX_TYPE) - 1,
} HSD_TypeMask;

#define AOBJ_REWINDED (1 << 26)
#define AOBJ_FIRST_PLAY (1 << 27)
#define AOBJ_NO_UPDATE (1 << 28)
#define AOBJ_LOOP (1 << 29)
#define AOBJ_NO_ANIM (1 << 30)

typedef enum _AObj_Arg_Type {
    AOBJ_ARG_A,
    AOBJ_ARG_AF,
    AOBJ_ARG_AV,
    AOBJ_ARG_AU,
    AOBJ_ARG_AO,
    AOBJ_ARG_AOF,
    AOBJ_ARG_AOV,
    AOBJ_ARG_AOU,
    AOBJ_ARG_AOT,
    AOBJ_ARG_AOTF,
    AOBJ_ARG_AOTV,
    AOBJ_ARG_AOTU,
} AObj_Arg_Type;

#ifdef __cplusplus
extern "C" {
#endif

void HSD_AObjSetFlags(HSD_AObj* aobj, unsigned int flags);
void HSD_AObjClearFlags(HSD_AObj* aobj, unsigned int flags);
void HSD_ForeachAnim(void* obj, HSD_Type type, HSD_TypeMask mask, void* func,
                     AObj_Arg_Type arg_type, ...);
void HSD_AObjSetRate(HSD_AObj* aobj, float rate);

#ifdef __cplusplus
}
#endif

#endif
