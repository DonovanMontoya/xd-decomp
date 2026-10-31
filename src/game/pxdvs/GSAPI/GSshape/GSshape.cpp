#pragma defer_codegen on
// Deferred code generation emits these definitions in reverse order.
#pragma force_active on
#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
static u8 g_primitiveEditorMode;
static u8 g_moduleInited;
static f32 g_primitiveFrameSec;
static u16 g_primitiveAnimation;
static s16 g_primitiveInstanceId = -1;
static u16 g_shapeRenderNum;
static GsShapeRender** g_shapeRender;

extern "C" {

}

struct GSgfxVF;
class GSgfxMatrixStack {
public:
    void pushMult(GSmtx *);
    void pop();
};
struct ShapeLayerPass { u8 bytes[0xBC]; };
class GSgfxLayer {
public:
    u8 reserved0[0xD34];
    u8 channelCount, reservedD35[3];
    s32 channelMask;
    u8 reservedD3C[0x50];
    s32 colorMode;
    u8 reservedD90[0x8B4];
    s32 blendMode, blendSource, blendDestination, logicOperation;
    u8 reserved1654[0x54];
    u32 dirty, channelDirty;
    u8 reserved16B0[8];
    u32 colorDirty;
    u8 reserved16BC[0x50];
    u32 pixelDirty;
    u8 reserved1710[0x50];
    u32 savedDirty, savedChannelDirty;
    u8 reserved1768[8];
    u32 savedColorDirty;
    u8 reserved1774[0x50];
    u32 savedPixelDirty;
    u8 reserved17C8[0x50];
    ShapeLayerPass passes[2];
    ShapeLayerPass *currentPass;
    s32 pass, primitiveType;
    GSgfxVF *format;
    GSgfxMatrixStack *matrixStack;
    void setRenderStateAndSelect(GSgfxVF *);
    void beginSurface(u16);
    void endSurface();
};
extern "C" {
GSgfxLayer *GSgfxLayerFindByID(GSgfxLayerID);
void GScameraLoadActiveCameraMatrix(GSgfxLayerID);
GSgfxVF *GSgfxVFGetPredef(s32);
u8 GSgfxVideoGetVsyncRate();
f32 GSgfxVideoGetLastRenderTime();
void GSprint(GSgfxLayerID,s32,s32,u32,const char *,...);
}

extern "C" u32 GSgfxPerfbarCPUEntry(u32);

struct GsShapeRenderModuleData {
    void (*preRender)(); void (*preUpdate)(f32); void (*render)();
    void (*fastRender)(); void (*postUpdate)(f32); void (*postRender)(); u32 parameter;
};
struct GSgfxRenderModule;
extern void GSgfxRenderModuleRegister(u8,GSgfxRenderModule*,void*);

extern "C" {
u32 shapeGetInstancedMemorySizeAll();
}
extern "C" {
u32 shapeGetUsedMemorySize(u16 index);
}
extern "C" {
void shapeFreePrimitiveInstance(u16 index,s16 instance);
}
extern "C" {
s16 shapeCreatePrimitiveInstance(u16 index);
}
extern "C" {
s32 shapeGenerateIndex();
}
extern "C" {
void shapeRelease(u16 index);
}
extern "C" {
void shapeRender(u16 index,s16 instance,GSgfxLayerID layer);
}
extern "C" {
void shapeUpdate(u16 index,f32 seconds,s16 instance);
}
extern "C" {
bool shapeLoad(u16 index,void* file);
}
extern "C" {
inline GSgfxLayerID primitiveEditorLayer();
}
extern "C" {
static inline void _shapeUpdateAll();
}
extern "C" {
void shapePrimitiveEditorRender(GSgfxLayerID layerId);
}
extern "C++" {
static void _shapePreUpdate(f32);
}
extern "C++" {
static void _shapeFastRender();
}
extern "C" {
static inline void shapeFreeAll();
}
extern "C" {
bool shapeInit(u16 count);
}

extern "C" {
inline GSgfxLayerID primitiveEditorLayer()
{
    if (!g_primitiveEditorMode) return GS_SHAPE_LAYER_DEFAULT;
    if (g_shapeRenderNum && g_shapeRender[0] && g_shapeRender[0]->animation) return g_shapeRender[0]->GetLayerId();
    return GS_SHAPE_LAYER_DEFAULT;
}
}

extern "C" {
static inline void _shapeUpdateAll() {
    for (u16 i = 0; i < g_shapeRenderNum; i++) {
        if (g_shapeRender[i] != 0) {
            shapeUpdate(i, g_primitiveFrameSec, g_primitiveInstanceId);
        }
    }
}
}

extern "C" {
static inline void shapeFreeAll()
{
    u16 i;
    for(i=0;i<g_shapeRenderNum;i++) {
        if(g_shapeRender[i]) {
            g_shapeRender[i]->FreeShapeRender();
            GSmemFree(g_shapeRender[i]); g_shapeRender[i]=0;
        }
    }
}
}

extern "C++" {
static void _shapePreUpdate(f32) {
    for(u16 i=0;i<g_shapeRenderNum;i++) {
        if(g_shapeRender[i] && g_shapeRender[i]->animation) g_shapeRender[i]->SwapBuffers();
    }
}
}

extern "C++" {
static void _shapeFastRender() {
    if(g_primitiveEditorMode) {
        GSgfxLayerID layer;
        if(!g_primitiveEditorMode) layer=GS_SHAPE_LAYER_DEFAULT;
        else if(g_shapeRenderNum && g_shapeRender[0] && g_shapeRender[0]->animation) layer=g_shapeRender[0]->GetLayerId();
        else layer=GS_SHAPE_LAYER_DEFAULT;
        u32 saved=GSgfxPerfbarCPUEntry(0xFF00);
        shapePrimitiveEditorRender(layer);
        GSgfxPerfbarCPUEntry(saved);
    }
}
}

extern "C" {
bool shapeInit(u16 count) {
    g_primitiveEditorMode=0;
    shapeFreeAll();
    if(g_shapeRender) { GSmemFree(g_shapeRender); g_shapeRender=0; }
    g_shapeRenderNum=0;
    if(!g_moduleInited) {
        GsShapeRenderModuleData module={0,_shapePreUpdate,0,_shapeFastRender,0,0,0xB29A48E1};
        GSgfxRenderModuleRegister(0x50,(GSgfxRenderModule*)&module,0); g_moduleInited=1;
    }
    g_shapeRender=(GsShapeRender**)GSmemAllocClr(count*4);
    if(!g_shapeRender) { g_shapeRenderNum=0; return false; }
    g_shapeRenderNum=count;
    return true;
}
}

extern "C" {
bool shapeLoad(u16 index,void* file) {
    if(index>=g_shapeRenderNum) return false;
    if(g_shapeRender[index]) GSmemFree(g_shapeRender[index]);
    g_shapeRender[index]=(GsShapeRender*)GSmemAlloc(sizeof(GsShapeRender));
    if(!g_shapeRender[index]) return false;
    g_shapeRender[index]->InitShapeRender(); g_shapeRender[index]->LoadShapeRender(file);
    return true;
}
}

extern "C" {
void shapeUpdate(u16 index,f32 seconds,s16 instance) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->Update(seconds,instance);
}
}

extern "C" {
void shapeRender(u16 index,s16 instance,GSgfxLayerID layer) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->Render(instance,layer);
}
}

extern "C" {
void shapeRelease(u16 index) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) {
        g_shapeRender[index]->FreeShapeRender(); GSmemFree(g_shapeRender[index]); g_shapeRender[index]=0;
    }
}
}

extern "C" {
s32 shapeGenerateIndex() {
    GsShapeRender *render;
    u16 i;
    for(i=0;i<g_shapeRenderNum;i++) {
        render=g_shapeRender[i];
        if(!render) return i;
        if(!render->animation) return i;
    }
    return -1;
}
}

extern "C" {
s16 shapeCreatePrimitiveInstance(u16 index) {
    if(index>=g_shapeRenderNum) return -1;
    if(g_shapeRender[index] == 0) {
        return -1;
    } else {
        return g_shapeRender[index]->CreateShapeRenderDrawBuffer();
    }
}
}

extern "C" {
void shapeFreePrimitiveInstance(u16 index,s16 instance) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->FreeShapeRenderDrawBuffer(instance);
}
}

extern "C" {
u32 shapeGetUsedMemorySize(u16 index) {
    if(index>=g_shapeRenderNum) return 0;
    if(g_shapeRender[index] == 0) {
        return 0;
    } else {
        return g_shapeRender[index]->GetUsedMemorySizeAll();
    }
}
}

extern "C" {
u32 shapeGetInstancedMemorySizeAll() { return g_instancedMemorySizeAll; }
}

extern "C" {
void shapePrimitiveEditorRender(GSgfxLayerID layerId) {
    GSgfxLayer* layer;
    s32 usedMemory;
    s32 instancedMemory;
    f32 m[3][4];
    f32 rate;
    f32 zero = 0.0f;
    f32 ten = 10.0f;

    if (g_primitiveEditorMode != 0) {
        if (layerId == primitiveEditorLayer()) {
            switch (g_primitiveAnimation) {
            case 0:
                rate = GSgfxVideoGetVsyncRate();
                g_primitiveFrameSec += GSgfxVideoGetLastRenderTime() / rate;
                _shapeUpdateAll();
                break;
            case 1:
                _shapeUpdateAll();
                if (g_shapeRenderNum != 0) {
                    GsShapeRender* r = g_shapeRender[0];
                    if (r != 0 && r->animation != 0 && r->animation->frameRate >= 1) {
                        g_primitiveFrameSec += 1.0f / r->animation->frameRate;
                    }
                }
                g_primitiveAnimation = 2;
                break;
            case 2:
                break;
            }
            layer = GSgfxLayerFindByID(layerId);
            GScameraLoadActiveCameraMatrix(layerId);
            PSMTXRotRad(m, 'Y', -1.5707964f);
            PSMTXTransApply(m, m, 0.0f, 0.1f, 0.0f);
            layer->matrixStack->pushMult((GSmtx*)m);
            layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
            layer->colorMode = 0;
            layer->colorDirty |= 2;
            layer->dirty |= 2;
            layer->savedColorDirty |= 2;
            layer->savedDirty |= 2;
            layer->primitiveType = 0xA8;
            if (layer->pass != 1) {
                layer->pass = 1;
                layer->currentPass = &layer->passes[layer->pass];
            }
            layer->blendMode = 1;
            layer->blendSource = 4;
            layer->blendDestination = 5;
            layer->logicOperation = 5;
            layer->pixelDirty |= 1;
            layer->dirty |= 0x40;
            layer->savedPixelDirty |= 1;
            layer->savedDirty |= 0x40;
            layer->channelCount = 6;
            layer->channelMask = 0;
            layer->channelDirty |= 4;
            layer->dirty |= 1;
            layer->savedChannelDirty |= 4;
            layer->savedDirty |= 1;
            layer->beginSurface(6);
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile f32 *)0xCC008000 = ten;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = ten;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = zero;
            *(volatile f32 *)0xCC008000 = ten;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0xFF;
            *(volatile u8 *)0xCC008000 = 0xFF;
            layer->endSurface();

            usedMemory = 0;
            instancedMemory = 0;
            for (u16 i = 0; i < g_shapeRenderNum; i++) {
                if (g_shapeRender[i] != 0) {
                    if (g_shapeRender[i]->active == 1 && g_shapeRender[i]->animation != 0) {
                        g_shapeRender[i]->animation->loop = 1;
                    }
                    shapeRender(i, g_primitiveInstanceId, layerId);
                    usedMemory += g_shapeRender[i]->GetUsedMemorySizeAll();
                    instancedMemory += g_shapeRender[i]->GetInstancedMemorySizeAll();
                }
            }
            GSprint(primitiveEditorLayer(), 0x226, 0x1E, -1, "%dKB", instancedMemory / 1024);
            layer->matrixStack->pop();
        }
    }
}
}
