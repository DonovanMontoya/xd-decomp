#pragma defer_codegen on
// Deferred code generation emits these definitions in reverse order.
#pragma force_active on
#include <dolphin/types.h>
#include <dolphin/gx/GXStruct.h>

#pragma pool_strings off

struct GStexture;
struct HSD_TExp {
    u32 type;
    HSD_TExp* next;
};
struct HSD_PEDesc;

struct HSD_ImageDesc {
    void* image_ptr;
    u16 width;
    u16 height;
    u32 format;
    u32 mipmap;
    f32 minLOD;
    f32 maxLOD;
};

struct HSD_TObj {
    u8 pad0[0x8];
    HSD_TObj* next;
    u8 pad1[0x50 - 0xC];
    f32 blending;
    u8 pad2[0x58 - 0x54];
    HSD_ImageDesc* imagedesc;
};

struct HSD_Material {
    u8 pad[0xC];
    f32 alpha;
};

struct GSmaterial;

struct HSD_MObj {
    u8 pad0[0x8];
    HSD_TObj* tobj;
    HSD_Material* mat;
    HSD_PEDesc* pe;
    u8 pad1[0x20 - 0x14];
    GSmaterial* user;
};

struct HSD_TObjDesc {
    u32 head[7];
    f32 scale[3];
    u32 mid[5];
    u8 wrap[4];
    u32 flags;
    f32 blending;
    u32 magFilt;
    HSD_ImageDesc* imagedesc;
    u32 tail[3];
};

struct HSD_MObjInfo {
    void (*init)(void);
    u32 classInfo[14];
    void* setup;
    int (*load)(HSD_MObj*, void*);
    HSD_TExp* (*make_texp)(HSD_MObj*, HSD_TObj*, HSD_TExp**);
    void* setup_tev;
    void* unk4c;
    void* unk50;
};

struct GSmaterial {
    u16 savedAlpha;
    u16 extensions;
    u32 savedFlags;
    HSD_MObj* mobj;
    GXColor modulate;
    u8 channels[4];
    HSD_TObj* envTObj;
    HSD_ImageDesc* envImage;
    GStexture* envTexture;
    s32 envType;
    s32 envMode;
    f32 envBlend;
    HSD_ImageDesc* savedImage;
    HSD_PEDesc* savedPE;
};

#define GSMATERIAL_UNSET ((void*)0xFEFEFEFE)

extern "C" {
void GSlogWrite(const char*, ...);
void HSD_ImageDescRemove(HSD_ImageDesc*);
HSD_ImageDesc* HSD_ImageDescAlloc(void);
void HSD_ImageDescFree(HSD_ImageDesc*);
void HSD_TObjRemove(HSD_TObj*);
HSD_TObj* HSD_TObjLoadDesc(HSD_TObjDesc*);
void HSD_MObjSetAlpha(HSD_MObj*, f32);
u32 HSD_MObjGetFlags(HSD_MObj*);
void HSD_MObjSetFlags(HSD_MObj*, u32);
void HSD_MObjClearFlags(HSD_MObj*, u32);
void HSD_MObjCompileTev(HSD_MObj*);
void HSD_MObjSetDefaultClass(HSD_MObjInfo*);
HSD_TObj* HSD_MObjGetTObj(HSD_MObj*);
void HSD_MObjAddTObj(HSD_MObj*, HSD_TObj*);
void HSD_MObjAddTObjNext(HSD_MObj*, HSD_TObj*, HSD_TObj*);
void hsdInitClassInfo(void*, void*, const char*, const char*, u32, u32);
s32 HSD_TExpGetType(HSD_TExp*);
void HSD_TExpColorSwap(HSD_TExp*, u8, u8, u8, u8);
HSD_TExp* HSD_TExpCnst(void*, u32, u32, HSD_TExp**);
HSD_TExp* HSD_TExpTev(HSD_TExp**);
void HSD_TExpColorOp(HSD_TExp*, u32, u32, u32, u32);
void HSD_TExpColorIn(HSD_TExp*, u32, HSD_TExp*, u32, HSD_TExp*, u32, HSD_TExp*, u32, HSD_TExp*);
void HSD_TExpAlphaOp(HSD_TExp*, u32, u32, u32, u32);
void HSD_TExpAlphaIn(HSD_TExp*, u32, HSD_TExp*, u32, HSD_TExp*, u32, HSD_TExp*, u32, HSD_TExp*);
void* GStextureLockImage(GStexture*, s32);
void GStextureUnlockImage(GStexture*);
u16 GStextureGetXsize(GStexture*);
u16 GStextureGetYsize(GStexture*);
u32 GStextureGetGXformat(GStexture*, s32);
u8 GStextureGetMiplevels(GStexture*);
s32 GXFmtToGStextureFmt(u32);
void GStextureCreateFromMemory(GStexture*, u16, u16, void*, s32, void*, u8);

extern HSD_MObjInfo hsdMObj;
}

extern "C" {

static void _GSmaterialObjInit(void);
static HSD_TExp* _matGSmatObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj, HSD_TExp** list);
static void _matGSmatEnableEnvMapExt(GSmaterial* material);
static int _matGSmatObjLoad(HSD_MObj* mobj, void* desc);

HSD_MObjInfo _matGSmatObj = { _GSmaterialObjInit };

}

extern "C" {
void GSmaterialResetTexture(GSmaterial* material);
}
extern "C" {
void GSmaterialGetTexture(GSmaterial* material, GStexture* texture);
}
extern "C" {
void GSmaterialSetTexture(GSmaterial* material, GStexture* texture);
}
extern "C" {
void GSmaterialGetModulate(GSmaterial* m, GXColor* color);
}
extern "C" {
void GSmaterialResetAlpha(GSmaterial* material);
}
extern "C" {
void GSmaterialStoreAlpha(GSmaterial* material);
}
extern "C" {
void GSmaterialSetEnvMapBlendValue(GSmaterial* material, f32 blend);
}
extern "C" {
void GSmaterialSetEnvMapParams(GSmaterial* material, s32 type, s32 mode, f32 blend, GStexture* texture);
}
extern "C" {
void GSmaterialSetModulate(GSmaterial* m, GXColor* c);
}
extern "C" {
void GSmaterialSetColorChannels(GSmaterial* m, u8* c);
}
extern "C" {
void GSmaterialSetAlpha(GSmaterial* material, f32 alpha);
}
extern "C" {
u32 GSmaterialGetEnabledExtensions(GSmaterial* m);
}
extern "C" {
static inline void _matRemoveEnvMap(GSmaterial* material);
}
extern "C" {
void GSmaterialDisableExtension(GSmaterial* material, u32 extensions);
}
extern "C" {
void GSmaterialEnableExtension(GSmaterial* material, u32 extensions);
}
extern "C" {
u32 GSmaterialGetFlags(GSmaterial* material);
}
extern "C" {
void GSmaterialResetPEdescr(GSmaterial* material);
}
extern "C" {
void GSmaterialSetPEdescr(GSmaterial* material, HSD_PEDesc* pe);
}
extern "C" {
void GSmaterialResetFlags(GSmaterial* material);
}
extern "C" {
void GSmaterialSetFlags(GSmaterial* material, u32 flags);
}
extern "C" {
void GSmaterialInit();
}
extern "C" {
static void _GSmaterialObjInit(void);
}
extern "C" {
static HSD_TExp* _matGSmatObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj, HSD_TExp** list);
}
extern "C" {
static void _matGSmatEnableEnvMapExt(GSmaterial* material);
}
extern "C" {
static int _matGSmatObjLoad(HSD_MObj* mobj, void* desc);
}

extern "C" {
static inline void _matRemoveEnvMap(GSmaterial* material)
{
    HSD_MObj* mobj;
    HSD_TObj* envTObj;
    HSD_TObj* tobj;
    HSD_ImageDesc* image;

    mobj = material->mobj;
    envTObj = material->envTObj;
    tobj = mobj->tobj;
    image = material->envImage;

    if (tobj != 0 && envTObj != 0) {
        if (tobj == envTObj) {
            mobj->tobj = envTObj->next;
        } else {
            while (tobj != 0) {
                if (tobj->next == envTObj) {
                    tobj->next = envTObj->next;
                }
                tobj = tobj->next;
            }
        }
        if (image != 0) {
            HSD_ImageDescRemove(image);
        }
        if (envTObj != 0) {
            HSD_TObjRemove(envTObj);
        }
    }
    material->envTexture = 0;
}
}

extern "C" {
static int _matGSmatObjLoad(HSD_MObj* mobj, void* desc)
{
    int ret = hsdMObj.load(mobj, desc);

    if (ret != 0) {
        return ret;
    }
    mobj->user = 0;
    return 0;
}
}

extern "C" {
static void _matGSmatEnableEnvMapExt(GSmaterial* material)
{
    static HSD_TObjDesc tobjdesc = {
        { 0, 0, 0, 4, 0, 0, 0 },
        { 1.0f, 1.0f, 1.0f },
        { 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0 },
        0,
        0.5f,
        1,
        0,
        { 0, 0, 0 },
    };
    GStexture* texture = material->envTexture;
    HSD_MObj* mobj;
    HSD_ImageDesc* image;
    HSD_TObj* tobj;
    HSD_TObj* last;

    if (texture != 0) {
        mobj = material->mobj;
        image = HSD_ImageDescAlloc();
        tobjdesc.flags = 0x80;
        tobjdesc.blending = material->envBlend;
        switch (material->envType) {
        case 1:
            tobjdesc.flags |= 5;
            break;
        case 0:
            tobjdesc.flags |= 1;
            break;
        case 2:
        default:
            tobjdesc.flags |= 6;
            break;
        }
        if (material->envMode == 0) {
            tobjdesc.flags |= 0x40000;
        } else {
            tobjdesc.flags |= 0x30000;
        }
        image->image_ptr = GStextureLockImage(texture, 0);
        image->width = GStextureGetXsize(texture);
        image->height = GStextureGetYsize(texture);
        image->format = GStextureGetGXformat(texture, 1);
        switch (image->format) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 14:
            break;
        default:
            GSlogWrite("GSmaterial: Unsupported texture format for environment map!\n");
            HSD_ImageDescRemove(image);
            HSD_ImageDescFree(image);
            GSmaterialDisableExtension(material, 4);
            return;
        }
        image->mipmap = GStextureGetMiplevels(texture) != 0;
        image->minLOD = 0.0f;
        image->maxLOD = 0.0f;
        tobjdesc.imagedesc = image;
        tobj = HSD_TObjLoadDesc(&tobjdesc);
        last = HSD_MObjGetTObj(mobj);
        if (last != 0) {
            while (last->next != 0) {
                last = last->next;
            }
            HSD_MObjAddTObjNext(mobj, last, tobj);
        } else {
            HSD_MObjAddTObj(mobj, tobj);
        }
        material->envTObj = tobj;
        material->envImage = image;
        GStextureUnlockImage(texture);
    } else {
        GSlogWrite("GSmaterial: Error creating environment map: no texture defined!\n");
        GSmaterialDisableExtension(material, 4);
    }
}
}

extern "C" {
static HSD_TExp* _matGSmatObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj, HSD_TExp** list)
{
    HSD_TExp* t;
    HSD_TExp* texp;
    GSmaterial* material;
    HSD_TExp* color;
    HSD_TExp* tev;
    HSD_TExp* alpha;

    texp = hsdMObj.make_texp(mobj, tobj, list);
    material = mobj->user;
    if (material == 0) {
        return texp;
    }
    if (material->extensions & 2) {
        for (t = texp; t != 0; t = t->next) {
            if (HSD_TExpGetType(t) == 1) {
                HSD_TExpColorSwap(t, material->channels[0], material->channels[1], material->channels[2], material->channels[3]);
            }
        }
    }
    if (material->extensions & 1) {
        color = HSD_TExpCnst(&material->modulate, 1, 0, list);
        alpha = HSD_TExpCnst(&material->modulate.a, 6, 0, list);
        tev = HSD_TExpTev(list);
        HSD_TExpColorOp(tev, 0, 0, 1, 1);
        HSD_TExpColorIn(tev, 0, 0, 1, color, 1, texp, 0, 0);
        HSD_TExpAlphaOp(tev, 0, 0, 0, 1);
        HSD_TExpAlphaIn(tev, 0, 0, 5, alpha, 5, texp, 0, 0);
        texp = tev;
    }
    return texp;
}
}

extern "C" {
static void _GSmaterialObjInit(void)
{
    hsdInitClassInfo(&_matGSmatObj, &hsdMObj, "GSmaterial MObj", "GSmaterial MObj", sizeof(HSD_MObjInfo), 0x24);
    _matGSmatObj.load = _matGSmatObjLoad;
    _matGSmatObj.make_texp = _matGSmatObjMakeTExp;
}
}

extern "C" {
void GSmaterialInit() { HSD_MObjSetDefaultClass(&_matGSmatObj); }
}

extern "C" {
void GSmaterialSetFlags(GSmaterial* material, u32 flags)
{
    u32 result;

    material->savedFlags = HSD_MObjGetFlags(material->mobj);
    HSD_MObjClearFlags(material->mobj, 0x4000600F);
    result = 0;
    if (flags & 1) {
        result |= 1;
    }
    if (flags & 2) {
        result |= 2;
    }
    if (flags & 4) {
        result |= 4;
    }
    if (flags & 8) {
        result |= 8;
    }
    if (flags & 0x10) {
        result |= 0x40000000;
    }
    if (flags & 0x20) {
        result |= 0x2000;
    }
    if (flags & 0x40) {
        result |= 0x4000;
    }
    HSD_MObjSetFlags(material->mobj, result);
    HSD_MObjCompileTev(material->mobj);
}
}

extern "C" {
void GSmaterialResetFlags(GSmaterial* material)
{
    HSD_MObjClearFlags(material->mobj, 0x4000600F);
    HSD_MObjSetFlags(material->mobj, material->savedFlags);
    HSD_MObjCompileTev(material->mobj);
}
}

extern "C" {
void GSmaterialSetPEdescr(GSmaterial* material, HSD_PEDesc* pe)
{
    if (material->savedPE == GSMATERIAL_UNSET) {
        material->savedPE = material->mobj->pe;
    } else {
        GSlogWrite("GSmaterialSetPEdescr: Warning: already using a custom description!\n");
    }
    material->mobj->pe = pe;
}
}

extern "C" {
void GSmaterialResetPEdescr(GSmaterial* material)
{
    HSD_PEDesc* saved = material->savedPE;

    if (saved != GSMATERIAL_UNSET) {
        material->mobj->pe = saved;
        material->savedPE = (HSD_PEDesc*)GSMATERIAL_UNSET;
    }
}
}

extern "C" {
u32 GSmaterialGetFlags(GSmaterial* material)
{
    u32 flags = HSD_MObjGetFlags(material->mobj);
    u32 result = 0;

    if (flags & 1) {
        result |= 1;
    }
    if (flags & 2) {
        result |= 2;
    }
    if (flags & 4) {
        result |= 4;
    }
    if (flags & 8) {
        result |= 8;
    }
    if (flags & 0x40000000) {
        result |= 0x10;
    }
    if (flags & 0x2000) {
        result |= 0x20;
    }
    if (flags & 0x4000) {
        result |= 0x40;
    }
    return result;
}
}

extern "C" {
void GSmaterialEnableExtension(GSmaterial* material, u32 extensions)
{
    u32 enable;
    HSD_MObj* mobj;

    mobj = material->mobj;
    enable = extensions & ~material->extensions;
    if (enable != 0) {
        mobj->user = material;
        if (enable & 4) {
            _matGSmatEnableEnvMapExt(material);
        }
        material->extensions |= enable;
        HSD_MObjCompileTev(mobj);
    }
}
}

extern "C" {
void GSmaterialDisableExtension(GSmaterial* material, u32 extensions)
{
    u32 disable;
    HSD_MObj* mobj;

    mobj = material->mobj;
    disable = extensions & material->extensions;
    if (disable & 1) {
        material->modulate.r = material->modulate.g = material->modulate.b = material->modulate.a = 0x7F;
    }
    if (disable & 2) {
        material->channels[0] = 0;
        material->channels[1] = 1;
        material->channels[2] = 2;
        material->channels[3] = 3;
    }
    if (disable & 4) {
        _matRemoveEnvMap(material);
    }
    material->extensions &= ~disable;
    if (material->extensions == 0) {
        mobj->user = 0;
    }
    HSD_MObjCompileTev(mobj);
}
}

extern "C" {
u32 GSmaterialGetEnabledExtensions(GSmaterial* m) { return m->extensions; }
}

extern "C" {
void GSmaterialSetAlpha(GSmaterial* material, f32 alpha)
{
    HSD_MObjSetAlpha(material->mobj, alpha);
}
}

extern "C" {
void GSmaterialSetColorChannels(GSmaterial* m, u8* c) { m->channels[0] = c[0]; m->channels[1] = c[1]; m->channels[2] = c[2]; m->channels[3] = c[3]; }
}

extern "C" {
void GSmaterialSetModulate(GSmaterial* m, GXColor* c) { m->modulate.r = c->r; m->modulate.g = c->g; m->modulate.b = c->b; m->modulate.a = c->a; }
}

extern "C" {
void GSmaterialSetEnvMapParams(GSmaterial* material, s32 type, s32 mode, f32 blend, GStexture* texture)
{
    material->envType = type;
    material->envMode = mode;
    material->envBlend = blend;
    material->envTexture = texture;
}
}

extern "C" {
void GSmaterialSetEnvMapBlendValue(GSmaterial* material, f32 blend)
{
    HSD_TObj* tobj = material->envTObj;

    material->envBlend = blend;
    if (tobj != 0) {
        tobj->blending = blend;
    }
}
}

extern "C" {
void GSmaterialStoreAlpha(GSmaterial* material)
{
    material->savedAlpha = (u8)(255.0f * material->mobj->mat->alpha);
}
}

extern "C" {
void GSmaterialResetAlpha(GSmaterial* material)
{
    HSD_MObjSetAlpha(material->mobj, material->savedAlpha / 255.0f);
}
}

extern "C" {
void GSmaterialGetModulate(GSmaterial* m, GXColor* color) {
    color->r = m->modulate.r; color->g = m->modulate.g;
    color->b = m->modulate.b; color->a = m->modulate.a;
}
}

extern "C" {
void GSmaterialSetTexture(GSmaterial* material, GStexture* texture)
{
    HSD_ImageDesc* image;

    if (material->savedImage == GSMATERIAL_UNSET) {
        material->savedImage = material->mobj->tobj->imagedesc;
        image = HSD_ImageDescAlloc();
    } else {
        image = material->mobj->tobj->imagedesc;
    }
    if (image != 0) {
        image->image_ptr = GStextureLockImage(texture, 0);
        image->width = GStextureGetXsize(texture);
        image->height = GStextureGetYsize(texture);
        image->format = GStextureGetGXformat(texture, 1);
        image->mipmap = GStextureGetMiplevels(texture) != 0;
        image->minLOD = 0.0f;
        image->maxLOD = 0.0f;
        GStextureUnlockImage(texture);
        material->mobj->tobj->imagedesc = image;
    }
}
}

extern "C" {
void GSmaterialGetTexture(GSmaterial* material, GStexture* texture)
{
    HSD_ImageDesc* image;

    if (material->savedImage != GSMATERIAL_UNSET) {
        image = material->savedImage;
    } else {
        image = material->mobj->tobj->imagedesc;
    }
    ((u8*)texture)[6] = 0;
    if (image != 0) {
        GStextureCreateFromMemory(texture, image->width, image->height, image->image_ptr, GXFmtToGStextureFmt(image->format), 0, image->mipmap);
    }
}
}

extern "C" {
void GSmaterialResetTexture(GSmaterial* material)
{
    HSD_ImageDesc* old;

    if (material->savedImage != GSMATERIAL_UNSET) {
        old = material->mobj->tobj->imagedesc;
        material->mobj->tobj->imagedesc = material->savedImage;
        HSD_ImageDescRemove(old);
        material->savedImage = (HSD_ImageDesc*)GSMATERIAL_UNSET;
    }
}
}
