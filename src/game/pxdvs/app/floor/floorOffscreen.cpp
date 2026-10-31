#pragma defer_codegen off
#include <game/pxdvs/app/floor/floorOffscreenPrivate.hpp>
#include <libc/string.h>

extern "C" { bool floorMoviePlay(u32 movie,u32 mode,bool looping,u32 target,u16 width,u16 height); }
extern "C" { void floorOffscreenPlayWait(); }
extern "C" { void* floorGetActiveOffscreenTexture(); }
extern "C" { bool floorSetOffscreenIndex(s32 index); }
extern "C" { void floorReleaseOffscreen(); }
extern "C" { void floorUpdateOffscreen(); }
extern "C" { void floorInitOffscreen(FloorOffscreenRoot* root); }
extern "C++" { static void _floorFreeOffscreenData(); }
extern "C" { void floorOffscreenMainInit(); }
static FloorOffscreenData _userOffData;
static s32 _lastOffIdx=-1;
static FloorOffscreenData* _offRootDataPtr;
static u32 _offRootDataCnt;
static FloorOffscreenData* _offData;
static void* _offTex;
static void* _offMdl;
static void* _offCam;
static void _floorFreeOffscreenData();
extern "C" {
u32 floorGetCurrentGroupID();
void* GSresGetResource(u32,u32);
void* floorOpenModel(u32,u32);
void* GStextureCreate(u16,u16,u32,u32,u32);
void GStextureFree(void*);
void GSmoviePlay(u32,u32,bool,void*);
void GSmoviePlayWait(u32);
void GSmovieStop(u32);
void GSmodelSetTextureChange(void*,void*);
void GSmodelResetTextureChange(void*);
void GSmodelFree(void*);
void GSmodelSetVisibility(void*,bool);
void GSmodelLinkTexAnimToAnim(void*,bool);
void GSmodelSetAnimIndex(void*,u32);
void GSmodelStartAnimation(void*);
void GSmodelForceAnimTransformUpdate(void*);
#pragma dont_inline on

}

#pragma force_active on
extern "C" {
bool floorMoviePlay(u32 movie,u32 mode,bool looping,u32 target,u16 width,u16 height){
    _floorFreeOffscreenData();
    _offData=&_userOffData;
    _offData->kind=1;
    _offData->index=1000;
    _offData->target=target;
    _offData->source=movie;
    _offData->animation=looping;
    _offData->width=width;
    _offData->height=height;
    _offData->camera=0;
    _offTex=GStextureCreate(_offData->width,_offData->height,0x44,0,0);
    if(!_offTex){_offData=0;return false;}
    GSmoviePlay(_offData->source,mode,looping,_offTex);
    GSmodelSetTextureChange(GSresGetResource(floorGetCurrentGroupID(),_offData->target),_offTex);
    _lastOffIdx=1000;
    return true;
}
}
extern "C" {
void floorOffscreenPlayWait(){
    if(_offData==0||_offMdl!=0)return;
    GSmoviePlayWait(_offData->source);
}
}
extern "C" {
void* floorGetActiveOffscreenTexture(){return _offTex;}
}
extern "C" {
bool floorSetOffscreenIndex(s32 index){
    if(_lastOffIdx==index)return true;
    _floorFreeOffscreenData();
    _offData=_offRootDataPtr;
    bool found=false;
    u32 remaining=_offRootDataCnt;
    while(remaining!=0){
        if(_offData->index==index){found=true;break;}
        ++_offData;
        --remaining;
    }
    if(!found){_offData=0;return false;}
    _offTex=GStextureCreate(_offData->width,_offData->height,0x44,0,0);
    if(!_offTex){_offData=0;return false;}
    FloorOffscreenData* data=_offData;
    if(data->kind==0){
        _offMdl=floorOpenModel(floorGetCurrentGroupID(),data->source);
        GSmodelSetVisibility(_offMdl,false);
        GSmodelLinkTexAnimToAnim(_offMdl,true);
        GSmodelSetAnimIndex(_offMdl,_offData->animation);
        GSmodelStartAnimation(_offMdl);
    }else GSmoviePlay(data->source,0,data->animation!=0,_offTex);
    _offCam=GSresGetResource(floorGetCurrentGroupID(),_offData->camera);
    GSmodelSetTextureChange(GSresGetResource(floorGetCurrentGroupID(),_offData->target),_offTex);
    _lastOffIdx=index;
    return true;
}
}
extern "C" {
void floorReleaseOffscreen(){_floorFreeOffscreenData();_offRootDataPtr=0;_offRootDataCnt=0;}
}
extern "C" {
void floorUpdateOffscreen(){if(!_offData||!_offMdl)return;GSmodelForceAnimTransformUpdate(_offMdl);}
}
extern "C" {
void floorInitOffscreen(FloorOffscreenRoot* root){
    if(root->data){
        _offRootDataPtr=(*root->data)->records;
        if(_offRootDataPtr){
            _offRootDataCnt=*(*root->data)->count;
            if(_offRootDataCnt)memset(&_userOffData,0,sizeof(_userOffData));
        }
    }
}
}
extern "C++" {
static void _floorFreeOffscreenData(){
    if(_offData){
        if(_offData->kind==1)GSmovieStop(_offData->source);
        GSmodelResetTextureChange(GSresGetResource(floorGetCurrentGroupID(),_offData->target));
        if(_offTex){GStextureFree(_offTex);_offTex=0;}
        if(_offMdl){GSmodelFree(_offMdl);_offMdl=0;}
        _offCam=0;_offData=0;_lastOffIdx=-1;
    }
}
}
extern "C" {
void floorOffscreenMainInit(){}
}
