#include <game/menuWorldMapModelPrivate.hpp>
#include <dolphin/gx/GXVert.h>
struct GSgfxVF;struct GSmtx;struct GSgfxLight;
struct WorldMatrix { u32 dirty;f32 matrix[12]; };
struct WorldMatrixStack { u32 reserved;WorldMatrix* current; };
struct GStexture {u8 reserved[7];u8 dirty;};
enum GSgfxTgenFunc{GSgfxTgenFuncDummy};
enum GSgfxTgenSrc{GSgfxTgenSrcDummy};
enum GSgfxCunitAlpha{GSgfxCunitAlphaDummy};
enum GSgfxCunitSrc{GSgfxCunitSrcDummy};
enum GSgfxLightType{GSgfxLightTypeDummy};
enum GSgfxDiffuseFunc{GSgfxDiffuseFuncDummy};
class GSgfxLayer {public:
u8 reserved0[0xC70];
u8 fieldC70;
u8 reservedC71[0xE3];
s32 fieldD54;
f32 fieldD58;
f32 fieldD5C;
f32 fieldD60;
f32 fieldD64;
f32 fieldD68;
f32 fieldD6C;
u8 reservedD70[0x1C];
s32 fieldD8C;
u8 reservedD90[0x28];
u8 fieldDB8;
u8 reservedDB9[0xF3];
u8 fieldEAC;
u8 reservedEAD[0x3];
s32 fieldEB0;
s32 fieldEB4;
s32 fieldEB8;
u8 reservedEBC[0xB4];
s32 fieldF70;
s32 fieldF74;
s32 fieldF78;
s32 fieldF7C;
u8 reservedF80[0xF0];
s32 field1070;
s32 field1074;
s32 field1078;
s32 field107C;
u8 reserved1080[0xF0];
s32 field1170;
s32 field1174;
s32 field1178;
u8 field117C;
u8 reserved117D[0x3];
s32 field1180;
u8 reserved1184[0x12C];
s32 field12B0;
s32 field12B4;
s32 field12B8;
u8 field12BC;
u8 reserved12BD[0x3];
s32 field12C0;
u8 reserved12C4[0x380];
s32 field1644;
s32 field1648;
s32 field164C;
s32 field1650;
u8 reserved1654[0x2];
u8 field1656;
u8 field1657;
u8 field1658;
u8 reserved1659[0x3];
u8 field165C;
u8 reserved165D[0x3];
s32 field1660;
u8 reserved1664[0x20];
f32 field1684;
f32 field1688;
u8 reserved168C[0x1A];
u8 field16A6;
u8 field16A7;
s32 field16A8;
s32 field16AC;
u8 reserved16B0[0x8];
s32 field16B8;
s32 field16BC;
u8 reserved16C0[0xC];
s32 field16CC;
s32 field16D0;
s32 field16D4;
s32 field16D8;
s32 field16DC;
s32 field16E0;
u8 reserved16E4[0x28];
s32 field170C;
u8 reserved1710[0x2C];
s32 field173C;
GStexture* field1740;
u8 reserved1744[0x1C];
s32 field1760;
s32 field1764;
u8 reserved1768[0x8];
s32 field1770;
s32 field1774;
u8 reserved1778[0xC];
s32 field1784;
s32 field1788;
s32 field178C;
s32 field1790;
s32 field1794;
s32 field1798;
u8 reserved179C[0x28];
s32 field17C4;
u8 reserved17C8[0x2C];
s32 field17F4;
GStexture* field17F8;
u8 reserved17FC[0x194];
void* field1990;
s32 field1994;
s32 field1998;
GSgfxVF* field199C;
WorldMatrixStack* field19A0;
void SetClearFlags(bool,bool,bool);void SetTextureCopy(GStexture*,bool,u8*);void beginSurface(u16);void endSurface();
void tgenFunc(u8,GSgfxTgenFunc,GSgfxTgenSrc,GSmtx*,bool,GSmtx*);
void cunitChannelGen(u8,GSgfxCunitAlpha,GSgfxCunitSrc,GSgfxCunitSrc,u32,GSgfxLight**,GSgfxLightType,GSgfxDiffuseFunc);};
class GSgfxLayerConfig {public:static void Move(GSgfxLayerID,GSgfxLayerID,GSgfxLayerOffset);};
extern "C" {GSgfxLayer *GSgfxLayerFindByID(s32);void GStextureFree(GStexture*);GStexture *GStextureCreate(s32,s32,s32,s32,s32);void *GSresGetResourceAllGroup(u32);void GSresFreeResource(u32,u32);void GSmodelSetVisibility(GSmodel*,bool);void GSmodelDetachFromGSpart(GSmodel*,bool);GSpart *GSmodelGetPart(GSmodel*,s32);void GSmodelAttachToGSpart(GSmodel*,GSpart*,GSattachMode,bool,bool);void GSpartFree(GSpart*);_GSparticleGen *GSparticleCreateGenerator(void*,s32,s32);void GSparticleAttachGeneratorToGSpart(_GSparticleGen*,GSpart*,GSattachMode,bool,bool,bool);void GSparticleDetachGeneratorFromGSpart(_GSparticleGen*,bool);void GSmodelFree(GSmodel*);void GSlightFree(GSlight*);WorldMapArchive *HSD_ArchiveGetPublicAddress(void*,const char*);u32 floorReadMakeModelResID(u32);u32 floorReadMakeLightResID(u32);void floorSetLightInfo(u32,s32);f32 GSmodelGetAnimFrameCount(GSmodel*,s32);f32 GSmodelGetAnimFrame(GSmodel*);void GSmodelStopAnimation(GSmodel*);u8 GSmodelIsAnimating(GSmodel*);void GSmodelSetAnimIndex(GSmodel*,s32);void GSmodelSetAnimFrame(GSmodel*,f32);void GSmodelSetAnimRate(GSmodel*,f32);void GSmodelSetAnimType(GSmodel*,s32);void GSmodelStartAnimation(GSmodel*);void GSmodelSetRenderLayer(GSmodel*,s32,GSgfxLayerID*);}
void WorldMapModel::releaseOffscreenData(){GSgfxLayer *layer=GSgfxLayerFindByID(2);layer->SetClearFlags(0,0,0);layer->SetTextureCopy(0,0,0);GSgfxLayerConfig::Move((GSgfxLayerID)2,(GSgfxLayerID)4,(GSgfxLayerOffset)1);if(offscreen){GStextureFree(offscreen);offscreen=0;}}
void WorldMapModel::initializeOffscreenData(){offscreen=GStextureCreate(0,0,0x45,0,0);if(offscreen){GSgfxLayerConfig::Move((GSgfxLayerID)2,(GSgfxLayerID)0,(GSgfxLayerOffset)1);GSgfxLayer *layer=GSgfxLayerFindByID(2);layer->SetTextureCopy(offscreen,0,0);layer->SetClearFlags(1,1,1);}}
void WorldMapModel::UnloadModel(unsigned long group,unsigned long res){s32 m=0,l=0;u32 base;WorldMapArchive *p=makeArchiveHeader(res);if(p){if(p->models){base=floorReadMakeModelResID(res);for(s32 i=0;p->models[i];i++,m++)GSresFreeResource(group,base|m);}if(p->lights){base=floorReadMakeLightResID(res);for(s32 i=0;p->lights[i];i++,l++)GSresFreeResource(group,base|l);floorSetLightInfo(base,l);}else floorSetLightInfo(0,0);}}
void WorldMapModel::ObjectVisibility(unsigned long res,bool visible){WorldMapArchive *p=makeArchiveHeader(res);u32 id=floorReadMakeModelResID(res);if(p->models)for(s32 i=0;p->models[i];id++,i++)Visibility(id,visible);}
void WorldMapModel::Visibility(unsigned long id,bool show){GSmodel *model=(GSmodel*)GSresGetResourceAllGroup(id);if(model)GSmodelSetVisibility(model,show);}
s32 WorldMapModel::ModelDetach(unsigned long id){GSmodel *model=(GSmodel*)GSresGetResourceAllGroup(id);if(!model)return 0;GSmodelDetachFromGSpart(model,1);return 1;}
s32 WorldMapModel::ModelAttach(unsigned long child,unsigned long parent,long index,GSattachMode mode){GSmodel *c=(GSmodel*)GSresGetResourceAllGroup(child);if(!c)return 0;GSmodel *p=(GSmodel*)GSresGetResourceAllGroup(parent);if(!p)return 0;GSpart *part=GSmodelGetPart(p,index);GSmodelAttachToGSpart(c,part,(GSattachMode)7,0,1);GSpartFree(part);return 1;}
_GSparticleGen *WorldMapModel::SetModelPartPaticle(unsigned long model,unsigned long resource,long index,GSattachMode mode,bool a,bool b,bool c){GSmodel *p=(GSmodel*)GSresGetResourceAllGroup(model);_GSparticleGen *gen;GSpart *part=GSmodelGetPart(p,index);void *res=GSresGetResourceAllGroup(resource);gen=GSparticleCreateGenerator(res,0,0);GSparticleAttachGeneratorToGSpart(gen,part,mode,a,b,c);GSpartFree(part);return gen;}
void WorldMapModel::DetachModelPartPaticle(_GSparticleGen *p,bool free){GSparticleDetachGeneratorFromGSpart(p,free);}
static s32 _unloadModel(void *p,u32,u32){GSmodelFree((GSmodel*)p);return 1;}
static s32 _unloadLight(void *p,u32,u32){GSlightFree((GSlight*)p);return 1;}
extern "C" {GSmodel *GSmodelLoad(void*,s32);GSlight *GSlightLoad(void*);void GSresRegisterResource(void*,u32,u32,s32(*)(void*,u32,u32));void GSlogWrite(const char*,...);u8 GSmodelCanAnimate(GSmodel*);u8 GSmodelCanTexAnimate(GSmodel*);void GSmodelSetTexAnimIndex(GSmodel*,s32);void GSmodelSetTexAnimRate(GSmodel*,f32);void GSmodelStartTexAnimation(GSmodel*);void GSlightSetType(GSlight*,s32);void GSlightSetActive(GSlight*,bool);u8 GSlightCanAnimate(GSlight*);void GSlightSetAnimIndex(GSlight*,s32);void GSlightSetAnimRate(GSlight*,f32);void GSlightStartAnimation(GSlight*);}
WorldMapArchive *WorldMapModel::SetModel(unsigned long group,unsigned long resource,bool active){
    s32 i;
    u32 id;
    u32 base;
    s32 j;
    WorldMapArchive *archive;
    s32 modelCount=0;
    s32 lightCount=0;
    GSgfxLayerID layers[1]={LayerDummy};
    u32 base2;
    GSlight *light;
    GSmodel *model;
archive=makeArchiveHeader(resource);if(!archive)return 0;if(archive->models){base=floorReadMakeModelResID(resource);for(i=0;archive->models[i];i++,modelCount++){model=GSmodelLoad(archive->models[i],0);id=base|modelCount;GSresFreeResource(group,id);GSresRegisterResource(model,group,id,_unloadModel);GSmodelSetRenderLayer(model,1,layers);if(!model){GSlogWrite("Error! %s: couldn't load model %d\x0A",__FUNCTION__);GSlogWrite("\x83\x82\x83\x66\x83\x8B\x82\xCC\x8F\x89\x8A\xFA\x89\xBB\x82\xC9\x8E\xB8\x94\x73\x0A");}else{GSmodelSetVisibility(model,true);if(GSmodelCanAnimate(model)){GSmodelSetAnimIndex(model,0);GSmodelSetAnimRate(model,0.5f);GSmodelStartAnimation(model);}if(GSmodelCanTexAnimate(model)){GSmodelSetTexAnimIndex(model,0);GSmodelSetTexAnimRate(model,0.5f);GSmodelStartTexAnimation(model);}}}}if(archive->lights){base2=floorReadMakeLightResID(resource);for(j=0;archive->lights[j];j++,lightCount++){light=GSlightLoad(archive->lights[j]);if(!light){GSlogWrite("Error! floorReadMapPostFunc: couldn't load light %d\x0A",lightCount);GSlogWrite("\x83\x89\x83\x43\x83\x67\x82\xCC\x8F\x89\x8A\xFA\x89\xBB\x82\xC9\x8E\xB8\x94\x73\x0A");}else{GSresRegisterResource(light,group,base2|lightCount,_unloadLight);if(active && light){if(lightCount==0)GSlightSetType(light,0);else GSlightSetType(light,1);GSlightSetActive(light,true);if(GSlightCanAnimate(light)){GSlightSetAnimIndex(light,0);GSlightSetAnimRate(light,0.5f);GSlightStartAnimation(light);}}}}}return archive;}

WorldMapArchive *WorldMapModel::makeArchiveHeader(unsigned long id){return HSD_ArchiveGetPublicAddress(GSresGetResourceAllGroup(id),"scene_data");}
f32 WorldMapModel::GetAnimeFrameCount(unsigned long id,unsigned long motion){GSmodel *p=(GSmodel*)GSresGetResourceAllGroup(id);if(p)goto found;return 0.0f;found:return GSmodelGetAnimFrameCount(p,motion);}
f32 WorldMapModel::GetAnimeFrame(unsigned long id){GSmodel *p=(GSmodel*)GSresGetResourceAllGroup(id);if(p)goto found;return 0.0f;found:return GSmodelGetAnimFrame(p);}
void WorldMapModel::StopMotion(unsigned long id){GSmodel *p=(GSmodel*)GSresGetResourceAllGroup(id);if(p)GSmodelStopAnimation(p);}
s32 WorldMapModel::CheckMotion(unsigned long id){GSmodel *p=(GSmodel*)GSresGetResourceAllGroup(id);if(p)goto found;return 0;found:return GSmodelIsAnimating(p)!=0;}
void WorldMapModel::SetMotion(unsigned long id,short index,f32 frame,bool loop){GSmodel *p=(GSmodel*)GSresGetResourceAllGroup(id);if(p){GSmodelSetAnimIndex(p,index);GSmodelSetAnimFrame(p,frame);GSmodelSetAnimRate(p,0.5f);if(loop)GSmodelSetAnimType(p,1);else GSmodelSetAnimType(p,0);GSmodelStartAnimation(p);}}
void WorldMapModel::SetLayerID(unsigned long id,long,GSgfxLayerID *layers){GSmodel *p=(GSmodel*)GSresGetResourceAllGroup(id);if(p)GSmodelSetRenderLayer(p,1,layers);}
GSmodel *WorldMapModel::GetModelPtr(unsigned long id){return (GSmodel*)GSresGetResourceAllGroup(id);}

extern "C" {GSgfxVF* GSgfxVFBuildTemp(s32,s32,s32,s32,s32,s32,s32,s32,s32);void spriteSetOffset(s32,s32,s32);void spriteClearScissor(s32);void spriteSetEnv(s32);void GSmtx44Ortho(f32*,f32,f32,f32,f32,f32,f32);void* memcpy(void*,const void*,u32);extern f32 mtxIdent[12];}
void WorldMapModel::renderOffscreenData(f32 fade) {
    f32 projection[16];
    GSgfxVF* format; WorldMatrix* matrix; WorldMatrixStack* stack;GStexture* texture;u8 alpha;GSgfxLayer* layer;
    alpha = 255.0f * fade;
    if (offscreen != 0) {
        layer = GSgfxLayerFindByID(4);
        if (layer != 0) {

            format = GSgfxVFBuildTemp(0,2,0,0,1,5,1,1,0);
            spriteSetOffset(4, 0, 0);
            spriteClearScissor(4);
            spriteSetEnv(4);
            GSmtx44Ortho(&projection[0], 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
            layer->fieldD54 = 1;
            layer->fieldD58 = projection[0];
            layer->fieldD5C = projection[3];
            layer->fieldD60 = projection[5];
            layer->fieldD64 = projection[7];
            layer->fieldD68 = projection[10];
            layer->fieldD6C = projection[11];
            stack = layer->field19A0;
            memcpy(stack->current->matrix, &mtxIdent, 0x30);
            matrix = stack->current;
            matrix->dirty |= 1;
            layer->field1684 = 0.0f;
            layer->field1688 = 30000.0f;
            if ((u8) layer->field16A7 != 0) {
                if ((u8) layer->field16A6 != 0) {
                    layer->field170C = layer->field170C | 0x100;
                    layer->field17C4 = layer->field17C4 | 0x100;
                }
                layer->field170C = layer->field170C | 0x40;
                layer->field16A8 = layer->field16A8 | 0x40;
                layer->field17C4 = layer->field17C4 | 0x40;
                layer->field1760 = layer->field1760 | 0x40;
            }
            layer->field16AC = layer->field16AC | 0x20;
            layer->field16A8 = layer->field16A8 | 1;
            layer->field1764 = layer->field1764 | 0x20;
            layer->field1760 = layer->field1760 | 1;
            layer->field1656 = 1;
            layer->field1657 = 0;
            layer->field1658 = 0;
            layer->field170C = layer->field170C | 4;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 4;
            layer->field1760 = layer->field1760 | 0x40;
            layer->field165C = 0;
            layer->field1660 = 7;
            layer->field170C = layer->field170C | 8;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 8;
            layer->field1760 = layer->field1760 | 0x40;
            layer->fieldD8C = 2;
            layer->field16B8 = layer->field16B8 | 2;
            layer->field16A8 = layer->field16A8 | 2;
            layer->field1770 = layer->field1770 | 2;
            layer->field1760 = layer->field1760 | 2;
            layer->field1998 = 0x80;
            layer->field199C = format;
            layer->fieldC70 = 1;
            layer->field16AC = layer->field16AC | 1;
            layer->field16A8 = layer->field16A8 | 1;
            layer->field1764 = layer->field1764 | 1;
            layer->field1760 = layer->field1760 | 1;
            layer->tgenFunc(0,(GSgfxTgenFunc)1,(GSgfxTgenSrc)4,0,0,0);
            layer->fieldDB8 = 1;
            layer->field16BC = layer->field16BC | 1;
            layer->field16A8 = layer->field16A8 | 4;
            layer->field1774 = layer->field1774 | 1;
            layer->field1760 = layer->field1760 | 4;

            layer->cunitChannelGen(0,(GSgfxCunitAlpha)2,(GSgfxCunitSrc)1,(GSgfxCunitSrc)1,0,0,(GSgfxLightType)2,(GSgfxDiffuseFunc)0);
            layer->fieldEAC = 1;
            layer->field16CC = layer->field16CC | 1;
            layer->field16A8 = layer->field16A8 | 8;
            layer->field1784 = layer->field1784 | 1;
            layer->field1760 = layer->field1760 | 8;
            layer->fieldEB0 = 0;
            layer->fieldEB4 = 0;
            layer->fieldEB8 = 4;
            layer->field16D0 = layer->field16D0 | 1;
            layer->field16A8 = layer->field16A8 | 8;
            layer->field1788 = layer->field1788 | 1;
            layer->field1760 = layer->field1760 | 8;
            layer->field1170 = 0;
            layer->field1174 = 0;
            layer->field1178 = 0;
            layer->field117C = 1;
            layer->field1180 = 0;
            layer->field16DC = layer->field16DC | 1;
            layer->field16A8 = layer->field16A8 | 8;
            layer->field1794 = layer->field1794 | 1;
            layer->field1760 = layer->field1760 | 8;
            layer->fieldF70 = 0xF;
            layer->fieldF74 = 0xF;
            layer->fieldF78 = 0xF;
            layer->fieldF7C = 8;
            layer->field16D4 = layer->field16D4 | 1;
            layer->field16A8 = layer->field16A8 | 8;
            layer->field178C = layer->field178C | 1;
            layer->field1760 = layer->field1760 | 8;
            layer->field12B0 = 0;
            layer->field12B4 = 0;
            layer->field12B8 = 0;
            layer->field12BC = 1;
            layer->field12C0 = 0;
            layer->field16E0 = layer->field16E0 | 1;
            layer->field16A8 = layer->field16A8 | 8;
            layer->field1798 = layer->field1798 | 1;
            layer->field1760 = layer->field1760 | 8;
            layer->field1070 = 7;
            layer->field1074 = 5;
            layer->field1078 = 4;
            layer->field107C = 7;
            layer->field16D8 = layer->field16D8 | 1;
            layer->field16A8 = layer->field16A8 | 8;
            layer->field1790 = layer->field1790 | 1;
            layer->field1760 = layer->field1760 | 8;
            if ((s32) layer->field1994 != 1) {
                layer->field1994 = 1;
                layer->field1990 = (u8*)layer + layer->field1994*0xbc+0x1818;
            }
            layer->field1644 = 1;
            layer->field1648 = 4;
            layer->field164C = 5;
            layer->field1650 = 5;
            layer->field170C = layer->field170C | 1;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 1;
            layer->field1760 = layer->field1760 | 0x40;
            texture = offscreen;
            if (((void *) layer->field1740 != texture) || ((void *) layer->field17F8 != texture) || ((u8) texture->dirty != 0)) {
                layer->field1740 = texture;
                layer->field173C = layer->field173C | 1;
                layer->field17F8 = texture;
                layer->field17F4 = layer->field17F4 | 1;
            }
            layer->beginSurface(4);
            GXPosition2s16(0,0);*(u8*)0xcc008000=255;*(u8*)0xcc008000=255;*(u8*)0xcc008000=255;*(u8*)0xcc008000=alpha;GXTexCoord2u8(0,0);
            GXPosition2s16(640,0);*(u8*)0xcc008000=255;*(u8*)0xcc008000=255;*(u8*)0xcc008000=255;*(u8*)0xcc008000=alpha;GXTexCoord2u8(1,0);
            GXPosition2s16(640,480);*(u8*)0xcc008000=255;*(u8*)0xcc008000=255;*(u8*)0xcc008000=255;*(u8*)0xcc008000=alpha;GXTexCoord2u8(1,1);
            GXPosition2s16(0,480);*(u8*)0xcc008000=255;*(u8*)0xcc008000=255;*(u8*)0xcc008000=255;*(u8*)0xcc008000=alpha;GXTexCoord2u8(0,1);
            layer->endSurface();
        }
    }
}
