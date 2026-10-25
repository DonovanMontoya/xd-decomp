#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
static u8 g_primitiveEditorMode;
static u8 g_moduleInited;
static f32 g_primitiveFrameSec;
static u16 g_primitiveAnimation;
static s16 g_primitiveInstanceId = -1;
static u16 g_shapeRenderNum;
static GsShapeRender** g_shapeRender;

extern "C" {
u32 shapeGetInstancedMemorySizeAll() { return g_instancedMemorySizeAll; }
u32 shapeGetUsedMemorySize(u16 index) {
    if(index>=g_shapeRenderNum) return 0;
    if(g_shapeRender[index] == 0) {
        return 0;
    } else {
        return g_shapeRender[index]->GetUsedMemorySizeAll();
    }
}
void shapeFreePrimitiveInstance(u16 index,s16 instance) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->FreeShapeRenderDrawBuffer(instance);
}
s16 shapeCreatePrimitiveInstance(u16 index) {
    if(index>=g_shapeRenderNum) return -1;
    if(g_shapeRender[index] == 0) {
        return -1;
    } else {
        return g_shapeRender[index]->CreateShapeRenderDrawBuffer();
    }
}
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
void shapeRelease(u16 index) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) {
        g_shapeRender[index]->FreeShapeRender(); GSmemFree(g_shapeRender[index]); g_shapeRender[index]=0;
    }
}
void shapeRender(u16 index,s16 instance,GSgfxLayerID layer) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->Render(instance,layer);
}
void shapeUpdate(u16 index,f32 seconds,s16 instance) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->Update(seconds,instance);
}
bool shapeLoad(u16 index,void* file) {
    if(index>=g_shapeRenderNum) return false;
    if(g_shapeRender[index]) GSmemFree(g_shapeRender[index]);
    g_shapeRender[index]=(GsShapeRender*)GSmemAlloc(sizeof(GsShapeRender));
    if(!g_shapeRender[index]) return false;
    g_shapeRender[index]->InitShapeRender(); g_shapeRender[index]->LoadShapeRender(file);
    return true;
}
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

inline GSgfxLayerID primitiveEditorLayer()
{
    if (!g_primitiveEditorMode) return GS_SHAPE_LAYER_DEFAULT;
    if (g_shapeRenderNum && g_shapeRender[0] && g_shapeRender[0]->animation) return g_shapeRender[0]->GetLayerId();
    return GS_SHAPE_LAYER_DEFAULT;
}

extern "C" void shapePrimitiveEditorRender(GSgfxLayerID layerId)
{
    u16 i;
    if (g_primitiveEditorMode && layerId == primitiveEditorLayer()) {
        switch (g_primitiveAnimation) {
        case 2:
            break;
        case 0: {
            f32 rate = GSgfxVideoGetVsyncRate();
            g_primitiveFrameSec += GSgfxVideoGetLastRenderTime() / rate;
            for (i=0; i<g_shapeRenderNum; i++) {
                if (g_shapeRender[i]) shapeUpdate(i,g_primitiveFrameSec,g_primitiveInstanceId);
            }
            break;
        }
        case 1:
            for (i=0; i<g_shapeRenderNum; i++) {
                if (g_shapeRender[i]) shapeUpdate(i,g_primitiveFrameSec,g_primitiveInstanceId);
            }
            if (g_shapeRenderNum && g_shapeRender[0] && g_shapeRender[0]->animation) {
                u32 rate=g_shapeRender[0]->animation->frameRate;
                if (rate>=1) g_primitiveFrameSec += 1.0f/(f32)rate;
            }
            g_primitiveAnimation=2;
            break;
        }
        GSgfxLayer *layer=GSgfxLayerFindByID(layerId);
        GScameraLoadActiveCameraMatrix(layerId);
        GSmtx matrix;
        PSMTXRotRad(matrix.matrix,'Y',-1.5707964f);
        PSMTXTransApply(matrix.matrix,matrix.matrix,0.0f,0.1f,0.0f);
        layer->matrixStack->pushMult(&matrix);
        layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
        layer->colorMode=0;
        layer->colorDirty |= 2;
        layer->dirty |= 2;
        layer->savedColorDirty |= 2;
        layer->savedDirty |= 2;
        layer->primitiveType=0xA8;
        if (layer->pass!=1) {
            layer->pass=1;
            layer->currentPass=&layer->passes[layer->pass];
        }
        layer->blendMode=1;
        layer->blendSource=4;
        layer->blendDestination=5;
        layer->logicOperation=5;
        layer->pixelDirty |= 1;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 1;
        layer->savedDirty |= 0x40;
        layer->channelCount=6;
        layer->channelMask=0;
        layer->channelDirty |= 4;
        layer->dirty |= 1;
        layer->savedChannelDirty |= 4;
        layer->savedDirty |= 1;
        layer->beginSurface(6);
        f32 zero=0.0f;
        f32 axisLength=10.0f;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = axisLength;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = axisLength;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = axisLength;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 255;
        *(volatile u8 *)0xCC008000 = 255;
        layer->endSurface();
        s32 used=0;
        s32 instanced=0;
        for(i=0;i<g_shapeRenderNum;i++) {
            GsShapeRender *render=g_shapeRender[i];
            if(render) {
                if(render->active==1 && render->animation) render->animation->loop=1;
                shapeRender(i,g_primitiveInstanceId,layerId);
                used+=g_shapeRender[i]->GetUsedMemorySizeAll();
                instanced+=g_shapeRender[i]->GetInstancedMemorySizeAll();
            }
        }
        GSprint(primitiveEditorLayer(),0x226,0x1E,~0u,"%dKB",instanced/1024);
        layer->matrixStack->pop();
    }
}


extern "C" u32 GSgfxPerfbarCPUEntry(u32);
static void _shapePreUpdate(f32) {
    for(u16 i=0;i<g_shapeRenderNum;i++) {
        if(g_shapeRender[i] && g_shapeRender[i]->animation) g_shapeRender[i]->SwapBuffers();
    }
}
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
struct GsShapeRenderModuleData {
    void (*preRender)(); void (*preUpdate)(f32); void (*render)();
    void (*fastRender)(); void (*postUpdate)(f32); void (*postRender)(); u32 parameter;
};
struct GSgfxRenderModule;
extern void GSgfxRenderModuleRegister(u8,GSgfxRenderModule*,void*);
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
extern "C" bool shapeInit(u16 count) {
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
