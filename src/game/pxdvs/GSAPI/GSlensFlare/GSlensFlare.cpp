#include <game/pxdvs/GSAPI/GSlensFlare/GSlensFlarePrivate.hpp>
#include <libc/string.h>
#include <dolphin/os/OSFastCast.h>

static LensFlareWork* _lfLensFlarePtrs[4];
static u8 gModuleInited;
static inline Vec* lensVec(GSvec* value) { return (Vec*)value; }
static inline void lensCopy(GSvec* out,const GSvec* in) {
    out->param1=in->param1; out->param2=in->param2; out->param3=in->param3;
}
static inline void lensSet(GSvec& out,f32 x,f32 y,f32 z) {
    out.param1=x; out.param2=y; out.param3=z;
}
struct LensVector : GSvec {
    LensVector() {}
    LensVector(const LensVector& value) { lensCopy(this,&value); }
};
static inline void lensAssign(GSvec& out,const GSvec& value) { lensCopy(&out,&value); }
static inline LensVector lensScale(const GSvec& value, f32 scale) {
    LensVector result;
    PSVECScale((const Vec*)&value,(Vec*)&result,scale);
    return result;
}
static inline LensVector lensSubtract(const GSvec& value, LensVector other) {
    LensVector result;
    PSVECSubtract((const Vec*)&value,(const Vec*)&other,(Vec*)&result);
    return result;
}
static inline LensVector lensAdd(const GSvec& value, LensVector other) {
    LensVector result;
    PSVECAdd((const Vec*)&value,(const Vec*)&other,(Vec*)&result);
    return result;
}
static inline f32 lensU8(u8 v) { return __OSu8tof32(&v); }
static inline f32 lensU16(u16 v) { return __OSu16tof32(&v); }
static inline f32 lensClamp(f32 value) {
    if (value < 0.0f) value=0.0f;
    else if (value > 1.0f) value=1.0f;
    return value;
}
static inline void lensIdentity(GSgfxLayer* layer) {
    GSgfxMatrixStack* stack=layer->matrixStack;
    memcpy(stack->current->matrix,mtxIdent,0x30);
    stack->current->flags |= 1;
}
static inline void lensPosition(f32 x,f32 y,f32 z) {
    *(volatile f32*)0xCC008000=x;
    *(volatile f32*)0xCC008000=y;
    *(volatile f32*)0xCC008000=z;
}
static inline void lensColor(const u8* color) {
    *(volatile u8*)0xCC008000=color[0];
    *(volatile u8*)0xCC008000=color[1];
    *(volatile u8*)0xCC008000=color[2];
    *(volatile u8*)0xCC008000=color[3];
}
static inline void lensTintColor(s32 intensity,u8 alpha) {
    *(volatile u8*)0xCC008000=intensity;
    *(volatile u8*)0xCC008000=intensity;
    *(volatile u8*)0xCC008000=intensity;
    *(volatile u8*)0xCC008000=alpha;
}
static inline void lensVertex(f32 x,f32 y,const u8* color,f32 z){lensPosition(x,y,z);lensColor(color);}
static inline void lensPrepare(GSgfxLayer* layer,s32 layerID,Mtx44 projection) {
    GScameraLoadActiveCameraMatrix(layerID);
    GSmtx44Ortho(projection,0.0f,480.0f,0.0f,640.0f,0.0f,-30000.0f);
    layer->projectionType=1;
    layer->p0=projection[0][0]; layer->p1=projection[0][3];
    layer->p2=projection[1][1]; layer->p3=projection[1][3];
    layer->p4=projection[2][2]; layer->p5=projection[2][3];
    lensIdentity(layer);
    layer->field1684=0.0f; layer->field1688=30000.0f;
    if (layer->field16A7) {
        if (layer->field16A6) { layer->field170C|=0x100; layer->field17C4|=0x100; }
        layer->field170C|=0x40; layer->field16A8|=0x40;
        layer->field17C4|=0x40; layer->field1760|=0x40;
    }
    layer->field16AC|=0x20; layer->field16A8|=1;
    layer->field1764|=0x20; layer->field1760|=1;
    layer->field1656=1; layer->field1657=1; layer->field1658=0;
    layer->field170C|=4; layer->field16A8|=0x40;
    layer->field17C4|=4; layer->field1760|=0x40;
    layer->field165C=0; layer->field1660=3;
    layer->field170C|=8; layer->field16A8|=0x40;
    layer->field17C4|=8; layer->field1760|=0x40;
    layer->fieldD8C=2;
    layer->field16B8|=2; layer->field16A8|=2;
    layer->field1770|=2; layer->field1760|=2;
    layer->field1998=0x98;
    if (layer->field1994 != 1) {
        layer->field1994=1;
        layer->field1990=(u8*)layer + 0x1818 + layer->field1994*0xBC;
    }
    layer->field1644=1; layer->field1648=4; layer->field164C=1; layer->field1650=5;
    layer->field170C|=1; layer->field16A8|=0x40;
    layer->field17C4|=1; layer->field1760|=0x40;
}
extern "C" {
void GSlensFlareSetVisible(u32 id,bool visible) {
    if (gModuleInited && id) {
        s32 index=id-1;
        LensFlareWork* flare=_lfLensFlarePtrs[index];
        if (flare && visible != flare->visible) {
            flare->visible=visible;
            if (_lfLensFlarePtrs[index]->header->flags & 8) {
                GSgfxLayer* layer=GSgfxLayerFindByID(5);
                if (layer) layer->SetLayerVisibility(visible);
            }
        }
    }
}
void GSlensFlareSetSunPosition(u32 id,GSvec* position) {
    if (gModuleInited && id) {
        s32 index=id-1;
        LensFlareWork* flare=_lfLensFlarePtrs[index];
        if (flare) lensCopy(&flare->sun,position);
    }
}
void GSlensFlareFree(u32 id) {
    if (gModuleInited && id) {
        s32 index=id-1;
        if (_lfLensFlarePtrs[index]) {
            delete _lfLensFlarePtrs[index];
            _lfLensFlarePtrs[index]=0;
        }
    }
}
u32 GSlensFlareLoad(LensHeader* data) {
    s32 textureIndex;
    GStexture* texture;
    s32 index;
    LensTextureRecord* record;
    LensFlareWork* flare;
    if (!gModuleInited) return 0;
    for (index=0;index<4;index++) {
        if (_lfLensFlarePtrs[index]==0) {
            flare=new LensFlareWork;
            if (flare==0) { flare=0; goto loaded; }
            flare->header=data;
            if (flare->header->magic != 0x7B1EE3F2) { delete flare; flare=0; goto loaded; }
            flare->elements=(LensElement*)((u8*)flare->header+0x2C);
            record=(LensTextureRecord*)(flare->elements+flare->header->elementCount);
            for (textureIndex=0;textureIndex<flare->header->textureCount;record++,textureIndex++) {
                record->data += (u32)data;
                texture=GStextureLoad((void*)record->data);
                GStextureSetFilter(texture,2,2,0);
                if (texture==0) { delete flare; flare=0; goto loaded; }
                flare->textures[record->index]=texture;
            }
            flare->alpha=1.0f;
loaded:
            _lfLensFlarePtrs[index]=flare;
            return _lfLensFlarePtrs[index] ? index+1 : 0;
        }
    }
    return 0;
}

void GSlensFlareInit() {
    memset(_lfLensFlarePtrs,0,sizeof(_lfLensFlarePtrs));
    if (!gModuleInited) {
        LensRenderModule module={0,0,_lensFlareRender__FP10GSgfxLayer14GSgfxLayerPass,0,0,0,0xB29A48E1};
        GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(0x80,&module,0);
        gModuleInited=1;
    }
}
static void _lensFlareRender__FP10GSgfxLayer14GSgfxLayerPass(GSgfxLayer* layer,s32 pass) {
    register f32 zero=0.0f,one=1.0f,width=640.0f,height=480.0f;
    f32 centerX,centerY;
    s32 layerID=layer->id;
    u8 cameraReady=0, layerReady=0;
    Mtx44 projectionMatrix;
    Mtx rotationNegative,rotationPositive;
    GSvec projected,screen,offset,up,right,cameraPosition;
    GSvec copied0,copied1,copied2,copied3;
    GSvec result0,result1,result2,result3;
    GSvec scaled0,scaled1,scaled2,scaled3;
    if (pass!=1 || (layerID!=6 && layerID!=5)) return;
    for (u16 i=0;i<4;i++) {
        LensFlareWork* flare=_lfLensFlarePtrs[i];
        if (!flare || !flare->visible) continue;
        LensHeader* header=flare->header;
        if (layer->mode==1 && !(header->flags&8)) continue;
        if (!cameraReady) {
            void* camera=GScameraGetActiveCamera();
            if (!camera) return;
            GScameraLoadActiveCameraMatrix(-1);
            f32 (*matrix)[4]=GScameraGetMatrixPtr(camera);
            GScameraGetPosition(camera,&cameraPosition);
            f32 upY=matrix[1][1],upZ=matrix[2][1],upX=matrix[0][1];
            centerX=320.0f;centerY=240.0f;
            lensSet(up,upX,upY,upZ);
            f32 rightY=matrix[1][0],rightZ=matrix[2][0],rightX=matrix[0][0];
            lensSet(right,rightX,rightY,rightZ);
            GSgfxProjectSetupParameters(); cameraReady=1;
        }

        s32 projection=GSgfxProjectFast(&flare->sun,&projected);
        if (!projection) continue;
        f32 sx=projected.param1-centerX;f32 sy=projected.param2-centerY;
        screen.param3=0.0f;screen.param1=sx;screen.param2=sy;
        f32 distance=PSVECMag(lensVec(&screen));
        if (distance>(f32)header->outerRadius) continue;
        f32 occlusion=1.0f;
        if (header->flags&0x10) {
            if (header->flags&0x20) {
                GSvec points[21]; u8 blocked[21];
                __construct_array(points,__ct__5GSvecFv,0,12,21);
                f32 step=0.2f*header->sampleRadius;
                for (u16 j=0;j<5;j++) {
                    f32 spread=step*lensU16(j);
                    {
                      PSVECScale(lensVec(&up),lensVec(&scaled0),spread);
                      lensCopy(&copied0,&scaled0);
                      PSVECSubtract(lensVec(&flare->sun),lensVec(&copied0),lensVec(&result0));
                      lensCopy(&points[j],&result0); }
                    {
                      PSVECScale(lensVec(&up),lensVec(&scaled1),spread);
                      lensCopy(&copied1,&scaled1);
                      PSVECAdd(lensVec(&flare->sun),lensVec(&copied1),lensVec(&result1));
                      lensCopy(&points[j+5],&result1); }
                    {
                      PSVECScale(lensVec(&right),lensVec(&scaled2),spread);
                      lensCopy(&copied2,&scaled2);
                      PSVECSubtract(lensVec(&flare->sun),lensVec(&copied2),lensVec(&result2));
                      lensCopy(&points[j+10],&result2); }
                    {
                      PSVECScale(lensVec(&right),lensVec(&scaled3),spread);
                      lensCopy(&copied3,&scaled3);
                      PSVECAdd(lensVec(&flare->sun),lensVec(&copied3),lensVec(&result3));
                      lensCopy(&points[j+15],&result3); }

                }
                lensCopy(&points[20],&flare->sun);
                if (GScolsys2SunArray(blocked,&cameraPosition,points,21)==1) {
                    f32 visible=blocked[20] ? 0.0f : 2.0f;
                    for (u16 j=0;j<20;j++) visible += blocked[j] ? 0.0f : 1.0f;
                    occlusion=visible/22.0f;
                }
            } else if (GScolsys2Sun(&flare->sun,&cameraPosition)==1) continue;
        }
        if (!layerReady) { lensPrepare(layer,layerID,projectionMatrix); layerReady=1; }
        if (projection==2) {
            f32 sunScale=1.0f;
            LensElement* sunElement=flare->elements;
            for (s32 remaining=header->elementCount;remaining--!=0;sunElement++) {
                if (sunElement->flags&1) { sunScale=sunElement->scale; break; }
            }
            f32 scaleDistance=distance;
            if (distance<header->minDistance) scaleDistance=header->minDistance;
            f32 radialFade;
            if (distance<(f32)header->fadeStart) radialFade=1.0f;
            else {
                u32 span=header->outerRadius-header->fadeStart;
                radialFade=((f32)span-(distance-(f32)header->fadeStart))/(f32)span;
                if(radialFade<0.0f)radialFade=0.0f;
                else if(radialFade>1.0f)radialFade=1.0f;
            }
            f32 scaleFactor=header->scaleFactor;
            u32 perspective=header->flags&1;
            layer->setRenderStateAndSelect(GSgfxVFGetPredef(5));
            LensElement* element=flare->elements;
            for (s32 remaining=header->elementCount;remaining--!=0;) {
                if (layer->mode==1 && !(element->flags&2)) { ++element; continue; }
                GStexture* texture=flare->textures[element->texture];
                lensIdentity(layer);
                f32 scale=element->scale;
                GSgfxMatrixStack::Entry* current;
                if (element->flags&1) {
                    GSgfxMatrixStack* stack=layer->matrixStack;
                    current=stack->current;
                    PSMTXTransApply(current->matrix,current->matrix,projected.param1,projected.param2,0.0f);
                    stack->current->flags|=1;
                } else {

                    PSVECScale(lensVec(&screen),lensVec(&offset),1.0f/element->divisor);
                    if (perspective) {
                        f32 adjustment;
                        if (element->divisor>0.0f && element->divisor<1.0f) adjustment=(1.0f/element->divisor)-1.0f;
                        else adjustment=1.0f-(1.0f/element->divisor);
                        scale *= 1.0f+(f32)(adjustment*(800.0f/scaleDistance)*((scaleFactor/sunScale)-1.0f));
                    } else scale *= 1.0f+(((scaleFactor-1.0f)*PSVECMag(lensVec(&offset)))/800.0f);
                    GSgfxMatrixStack* stack=layer->matrixStack;
                    current=stack->current;
                    PSMTXTransApply(current->matrix,current->matrix,offset.param1+centerX,offset.param2+centerY,0.0f);
                    stack->current->flags|=1;
                }
                f32 left=-(scale*(f32)(GStextureGetXsize(texture)>>1));
                f32 top=-(scale*(f32)(GStextureGetYsize(texture)>>1));
                f32 rightEdge=scale*(f32)(GStextureGetXsize(texture)>>1);
                f32 bottom=scale*(f32)(GStextureGetYsize(texture)>>1);
                if (header->flags&2) {
                    if (header->flags&4) {
                        f32 rotation=(f32)atan2(screen.param2,screen.param1);
                        GSgfxMatrixStack* stack=layer->matrixStack;

                        PSMTXRotRad(rotationNegative,'X',0.0f); current=stack->current;
                        PSMTXConcat(current->matrix,rotationNegative,current->matrix);
                        PSMTXRotRad(rotationNegative,'Y',0.0f); current=stack->current;
                        PSMTXConcat(current->matrix,rotationNegative,current->matrix);
                        PSMTXRotRad(rotationNegative,'Z',-rotation); current=stack->current;
                        PSMTXConcat(current->matrix,rotationNegative,current->matrix);
                        stack->current->flags|=1;
                    } else {
                        f32 rotation=(f32)atan2(screen.param2,screen.param1);
                        GSgfxMatrixStack* stack=layer->matrixStack;

                        PSMTXRotRad(rotationPositive,'X',0.0f); current=stack->current;
                        PSMTXConcat(current->matrix,rotationPositive,current->matrix);
                        PSMTXRotRad(rotationPositive,'Y',0.0f); current=stack->current;
                        PSMTXConcat(current->matrix,rotationPositive,current->matrix);
                        PSMTXRotRad(rotationPositive,'Z',rotation); current=stack->current;
                        PSMTXConcat(current->matrix,rotationPositive,current->matrix);
                        stack->current->flags|=1;
                    }
                }
                u8 color[4];
                color[0]=__OSf32tou8(radialFade*lensU8(element->color[0]));
                color[1]=__OSf32tou8(radialFade*lensU8(element->color[1]));
                color[2]=__OSf32tou8(radialFade*lensU8(element->color[2]));
                color[3]=__OSf32tou8(occlusion*(flare->alpha*(radialFade*lensU8(element->color[3])))+0.5f);
                if (layer->field1740!=texture || layer->field17F8!=texture || texture->dirty) {
                    layer->field1740=texture; layer->field173C|=1;
                    layer->field17F8=texture; layer->field17F4|=1;
                }
                layer->beginSurface(4);
                lensVertex(left,top,color,zero); *(volatile f32*)0xCC008000=zero; *(volatile f32*)0xCC008000=zero;
                lensVertex(rightEdge,top,color,zero); *(volatile f32*)0xCC008000=one; *(volatile f32*)0xCC008000=zero;
                lensVertex(left,bottom,color,zero); *(volatile f32*)0xCC008000=zero; *(volatile f32*)0xCC008000=one;
                lensVertex(rightEdge,bottom,color,zero); *(volatile f32*)0xCC008000=one; *(volatile f32*)0xCC008000=one;
                layer->endSurface();
                ++element;
            }
            if (layer->mode==0) {
                if (distance < (f32)header->fadeStart) {
                    f32 fade;
                    if (distance < (f32)header->fadePeak) fade=header->frontTint;
                    else {
                        u32 span=header->fadeStart-header->fadePeak;
                        fade=lensClamp(header->frontTint * (((f32)span-(distance-(f32)header->fadePeak))/(f32)span));
                    }
                    s32 intensity=(s32)(255.0f*fade);
                    layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
                    lensIdentity(layer);
                    layer->beginSurface(4);
                    u8 alpha;
                    lensPosition(zero,zero,zero);
                    alpha=__OSf32tou8((255.0f*flare->alpha*occlusion)+0.5f);
                    lensTintColor(intensity,alpha);
                    lensPosition(width,zero,zero);
                    alpha=__OSf32tou8((255.0f*flare->alpha*occlusion)+0.5f);
                    lensTintColor(intensity,alpha);
                    lensPosition(zero,height,zero);
                    alpha=__OSf32tou8((255.0f*flare->alpha*occlusion)+0.5f);
                    lensTintColor(intensity,alpha);
                    lensPosition(width,height,zero);
                    alpha=__OSf32tou8((255.0f*flare->alpha*occlusion)+0.5f);
                    lensTintColor(intensity,alpha);
                    layer->endSurface();
                }
            }
        } else if (layer->mode==0) {
            PSVECSubtract(lensVec(&cameraPosition),lensVec(&flare->sun),lensVec(&screen));
            PSVECAdd(lensVec(&cameraPosition),lensVec(&screen),lensVec(&screen));
            if (GSgfxProjectFast(&screen,&projected)==2) {
                f32 sx=projected.param1-centerX;f32 sy=projected.param2-centerY;
                screen.param3=0.0f;screen.param1=sx;screen.param2=sy;
                f32 backDistance=PSVECMag(lensVec(&screen));
                if (backDistance>0.00001f && backDistance<(f32)header->outerRadius) {
                    if (backDistance < (f32)header->fadeStart) {
                        f32 fade;
                        if (backDistance < (f32)header->fadePeak) fade=header->backTint;
                        else {
                            u32 span=header->fadeStart-header->fadePeak;
                            fade=lensClamp(header->backTint * (((f32)span-(backDistance-(f32)header->fadePeak))/(f32)span));
                        }
                        s32 intensity=(s32)(255.0f*fade);
                        layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
                        lensIdentity(layer);
                        layer->beginSurface(4);
                        u8 alpha;
                        lensPosition(zero,zero,zero);
                        alpha=__OSf32tou8((255.0f*flare->alpha*occlusion)+0.5f);
                        lensTintColor(intensity,alpha);
                        lensPosition(width,zero,zero);
                        alpha=__OSf32tou8((255.0f*flare->alpha*occlusion)+0.5f);
                        lensTintColor(intensity,alpha);
                        lensPosition(zero,height,zero);
                        alpha=__OSf32tou8((255.0f*flare->alpha*occlusion)+0.5f);
                        lensTintColor(intensity,alpha);
                        lensPosition(width,height,zero);
                        alpha=__OSf32tou8((255.0f*flare->alpha*occlusion)+0.5f);
                        lensTintColor(intensity,alpha);
                        layer->endSurface();
                    }
                }
            }
        }
    }
}
}
