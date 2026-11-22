#include <game/pxdvs/app/fade/fade.hpp>
#include <game/pxdvs/GSAPI/GSgfxM/vf.hpp>
#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>
#include <libc/string.h>
#include <game/pxdvs/GSAPI/GSgfxM/backfbPrivate.hpp>

struct FadeWork;
typedef u8 (*FadeCallback)(u32, s32, GStexture*, volatile FadeWork*, f32, f32, f32, f32);
struct FadeWork { u8 unk0,busy; u16 unk2; f32 unk4,unk8; FadeCallback unkC; GStexture* capture; f32 unk14,unk18; };
static volatile FadeWork _fadeWork;
static u8 _complete;
static void _fadeSnapshot();
static u8 myBackFB(GStexture*, u32, void*);

extern "C" {
void GSthreadSwitch(); void GSsndPlayNow(s32); void fadeEffectHookFunction_Doku_Init(); void fadeEffectInit(); GStexture* menuOffScreenGetPtr(); u8 menuOffScreenIsDoing();  s32 GSmemGetCurrentHeap(); s32 GSmemSetAllocMethodHeap(s32,s32);
s32 GSgfxBeginBackFBCapture(GStexture*, BackFBCaptureCallback, void*);
s32 fadeSetEX(u16,void(*)(),u8,f32,f32); static s32 fadeSetFunction__FPFv_vbUsf(void(*)(),u8,u16,f32);
void fadeEffectDokuStop(void) {
    if (_fadeWork.unk0 == 4) {
        _fadeWork.busy = 0;
        _fadeWork.unk0 = 0;
    }
}

void fadeEffectDokuStart(void) {
    if (_fadeWork.unk0 == 0) {
        fadeSetEX(9U, fadeEffectHookFunction_Doku_Init, 0U, 1.0f, 0.5f);
        GSsndPlayNow(0x18);
    }
}

s32 fadeGetType(void) {
    return _fadeWork.unk2;
}

s8 fadeCheck(u8 arg0) {
    if (arg0 == 0) {
        return (s8) _fadeWork.busy;
    }
while (_fadeWork.busy == 1) GSthreadSwitch();
    GSthreadSwitch();
    return (s8) _fadeWork.busy;
}

s32 fadeSetEX(u16 arg0, void (*arg1)(), u8 arg2, f32 farg0, f32 farg1) {
    s32 temp_r31;

    temp_r31 = fadeSetFunction__FPFv_vbUsf(arg1, arg2, arg0, farg1);
    fadeSet(arg0, farg0);
    return temp_r31;
}

void fadeSetToBlackInIfBlack(f32 time) {
    if (_fadeWork.unk0 == 2) {
        fadeSet(2U,time);
    }
}

void fadeSetToBlackOutIfNotBlack(f32 time) {
    if (_fadeWork.unk0 != 2) {
        fadeSet(3U,time);
    }
}

void fadeSet(u16 arg0, f32 farg0) {
    _fadeWork.busy = 1;
    _fadeWork.unk2 = arg0;
    _fadeWork.unk4 = farg0;
    _fadeWork.unk8 = 0.0f;
    if ((s32) (arg0 & 8) != 0) {
        if ((s32) (arg0 & 1) != 0) {
            _fadeWork.unk0 = 4;
            return;
        }
        _fadeWork.unk0 = 3;
        return;
    }
    if ((s32) (arg0 & 1) != 0) {
        _fadeWork.unk0 = 2;
        return;
    }
    _fadeWork.unk0 = 1;
}

s32 fadeSetFunction__FPFv_vbUsf(void (*arg0)(), u8 arg1, u16 arg2, f32 farg0) {
    s32 temp_r31;

    if (arg0 == NULL) {
        return (s32)_fadeWork.unkC;
    }
    _fadeWork.busy = 1;
    _fadeWork.unk2 = arg2;
    _fadeWork.unk14 = farg0;
    _fadeWork.unk18 = 0.0f;
    _fadeWork.unk0 = 0;
    temp_r31 = (s32)_fadeWork.unkC;
    _fadeWork.unkC = 0;
    if (arg1 == 1) {
        _fadeSnapshot();
    } else if (_fadeWork.capture != 0) {
        if (_fadeWork.capture != menuOffScreenGetPtr()) {
            GStextureFree(_fadeWork.capture);
        }
        _fadeWork.capture = 0;
    }
    fadeEffectInit();
    arg0();
    return temp_r31;
}

void fadeSetFunctionOnly(s32 arg0) {
    _fadeWork.unkC = (FadeCallback)arg0;
}

}

static void _fadeSnapshot() {
    GStexture* texture = _fadeWork.capture;
    _fadeWork.capture = 0;
    if (!menuOffScreenIsDoing()) {
        texture = menuOffScreenGetPtr();
    }
    if (!texture) {
        s32 previousMethod = GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(), 3);
        texture = GStextureCreate(0, 0, 0x44, 0, 0);
        GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(), previousMethod);
    }
    if (texture) {
        _complete = 0;
        GSgfxBeginBackFBCapture(texture, myBackFB, 0);
        while (!_complete) GSthreadSwitch();
        _fadeWork.capture = texture;
    }
}

static u8 myBackFB(GStexture*, u32, void*) {
    _complete = 1;
    return 0;
}

extern "C" {
void fadeInit(void) {
    _fadeWork.unk0 = 0;
    _fadeWork.busy = 0;
    _fadeWork.unk2 = 0;
    _fadeWork.unk4 = 0.0f;
    _fadeWork.unk8 = 0.0f;
    _fadeWork.unkC = 0;
    _fadeWork.capture = 0;
    _fadeWork.unk14 = 0.0f;
    _fadeWork.unk18 = 0.0f;
}

}

extern "C" { u8 GSgfxVideoGetVsyncRate(); u32 timeGetLastFrameTime();  }
extern "C" void fadeDaemon() {
    Mtx44 projection;
    GXColor white={255,255,255,255};
    GXColor black={0,0,0,255};
    u8 red,green,blue;
    u8 alpha;
    u32 wasBusy;
    GSgfxMatrixStack* stack;
    GSgfxLayer* layer=GSgfxLayerFindByID(7);
    if (!layer) return;
    u32 busy=_fadeWork.busy;
    wasBusy=_fadeWork.busy;
    if (busy==1) {
        switch (_fadeWork.unk0) {
        case 0: case 4: break;
        case 1: case 2: case 3: {
            f32 rate=GSgfxVideoGetVsyncRate();
            _fadeWork.unk8 += (f32)timeGetLastFrameTime()/rate;
            if (_fadeWork.unk8>=_fadeWork.unk4) {
                _fadeWork.unk8=_fadeWork.unk4;
                _fadeWork.busy=0;
                if (_fadeWork.unk2&1) _fadeWork.unk0=2;
                else _fadeWork.unk0=0;
            }
            break;
        }
        default: break;
        }
    }
    if (_fadeWork.unkC) {
        f32 rate=GSgfxVideoGetVsyncRate();
        _fadeWork.unk18 += (f32)timeGetLastFrameTime()/rate;
        if (_fadeWork.unk18>=_fadeWork.unk14) _fadeWork.unk18=_fadeWork.unk14;
        GStexture* texture = _fadeWork.capture;
        FadeCallback callback=_fadeWork.unkC;
        if (!callback(layer->id,_fadeWork.busy,texture,&_fadeWork,_fadeWork.unk8,_fadeWork.unk4,_fadeWork.unk18,_fadeWork.unk14)) {
            _fadeWork.unkC=0;
            if (_fadeWork.capture) {
                if (_fadeWork.capture!=menuOffScreenGetPtr()) GStextureFree(_fadeWork.capture);
                _fadeWork.capture=0;
            }
        }
    } else if ((_fadeWork.unk2&16) && wasBusy==0) _fadeWork.unk0=5;
    switch (_fadeWork.unk0) {
    case 0: break;
    case 3: case 4: break;
    case 1: case 2: case 5: {
        f32 progress;
        if (_fadeWork.unk4==0.0f) progress=1.0f;
        else progress=_fadeWork.unk8/_fadeWork.unk4;

        if (_fadeWork.unk2&1) alpha=255.0f*progress;
        else alpha=(u8)(255-(s32)(255.0f*progress));
        if (_fadeWork.unk2&2) {red=black.r;green=black.g;blue=black.b;}
        else {red=white.r;green=white.g;blue=white.b;}
        if (_fadeWork.unk0==5) {red=black.r;green=black.g;blue=black.b;alpha=255.0f*progress;}
        GSmtx44Ortho(projection,0.0f,480.0f,0.0f,640.0f,0.0f,-30000.0f);
        layer->projectionType=1;
        layer->projection[0]=projection[0][0];
        layer->projection[1]=projection[0][3];
        layer->projection[2]=projection[1][1];
        layer->projection[3]=projection[1][3];
        layer->projection[4]=projection[2][2];
        layer->projection[5]=projection[2][3];
        stack=layer->matrixStack;
        memcpy(stack->current->matrix,mtxIdent,48);
        stack->current->dirty |=1;
            layer->depthNear = 0.0f;
            layer->depthFar = 30000.0f;
            if ((u8) layer->fogEnable != 0) {
                if ((u8) layer->fogRangeAdjust != 0) {
                    layer->pixelDirty = (s32) (layer->pixelDirty | 0x100);
                    layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 0x100);
                }
                layer->pixelDirty = (s32) (layer->pixelDirty | 0x40);
                layer->dirty = (s32) (layer->dirty | 0x40);
                layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 0x40);
                layer->savedDirty = (s32) (layer->savedDirty | 0x40);
            }
            layer->rasterDirty = (s32) (layer->rasterDirty | 0x20);
            layer->dirty = (s32) (layer->dirty | 1);
            layer->savedRasterDirty = (s32) (layer->savedRasterDirty | 0x20);
            layer->savedDirty = (s32) (layer->savedDirty | 1);
            if ((s32) layer->shaderIndex != 1) {
                layer->shaderIndex = 1;
                layer->shader = &layer->shaders[layer->shaderIndex];
            }
            layer->blendMode = 1;
            layer->blendSource = 4;
            layer->blendDestination = 5;
            layer->blendLogic = 5;
            layer->pixelDirty = (s32) (layer->pixelDirty | 1);
            layer->dirty = (s32) (layer->dirty | 0x40);
            layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 0x40);
            layer->colorUpdate = 1;
            layer->alphaUpdate = 1;
            layer->destinationAlpha = 0;
            layer->pixelDirty = (s32) (layer->pixelDirty | 4);
            layer->dirty = (s32) (layer->dirty | 0x40);
            layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 4);
            layer->savedDirty = (s32) (layer->savedDirty | 0x40);
            layer->depthEnable = 0;
            layer->depthFunction = 1;
            layer->pixelDirty = (s32) (layer->pixelDirty | 8);
            layer->dirty = (s32) (layer->dirty | 0x40);
            layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 8);
            layer->savedDirty = (s32) (layer->savedDirty | 0x40);
            layer->cullMode = 0;
            layer->transformDirty = (s32) (layer->transformDirty | 2);
            layer->dirty = (s32) (layer->dirty | 2);
            layer->savedTransformDirty = (s32) (layer->savedTransformDirty | 2);
            layer->savedDirty = (s32) (layer->savedDirty | 2);
            layer->primitive = 0x98;

        layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1,4,0,0,1,5,0,0,0));
        layer->beginSurface(4);
        *(f32*)0xCC008000=0.0f;
        *(f32*)0xCC008000=0.0f;
        *(f32*)0xCC008000=0.0f;
        *(u8*)0xCC008000=red;
        *(u8*)0xCC008000=green;
        *(u8*)0xCC008000=blue;
        *(u8*)0xCC008000=alpha;
        *(f32*)0xCC008000=640.0f;
        *(f32*)0xCC008000=0.0f;
        *(f32*)0xCC008000=0.0f;
        *(u8*)0xCC008000=red;
        *(u8*)0xCC008000=green;
        *(u8*)0xCC008000=blue;
        *(u8*)0xCC008000=alpha;
        *(f32*)0xCC008000=0.0f;
        *(f32*)0xCC008000=480.0f;
        *(f32*)0xCC008000=0.0f;
        *(u8*)0xCC008000=red;
        *(u8*)0xCC008000=green;
        *(u8*)0xCC008000=blue;
        *(u8*)0xCC008000=alpha;
        *(f32*)0xCC008000=640.0f;
        *(f32*)0xCC008000=480.0f;
        *(f32*)0xCC008000=0.0f;
        *(u8*)0xCC008000=red;
        *(u8*)0xCC008000=green;
        *(u8*)0xCC008000=blue;
        *(u8*)0xCC008000=alpha;
        layer->endSurface();
        break;
    }
    default: break;
    }
}
