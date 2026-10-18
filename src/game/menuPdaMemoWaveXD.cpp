#include <game/menuPcBoxPokemonLayout.hpp>
#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
enum GSgfxLayerID {WaveLayerDummy};
struct NakigoeDispWork {s8 *data;f32 count;u32 sound;f32 start;s32 time;f32 end;s32 samples;f32 alpha,speed;};
class pdaMemoNakigoe {public:NakigoeDispWork waves[8];u32 index;pdaMemoNakigoe(){Reset();}void Reset(){for(s32 i=0;i<8;i++)waves[i].data=0;index=0;DispInit();}void DispInit();void SetNakigoe(long);void SetSE(unsigned long);u16 GetVocie(long);s8 *GetWaveDispDataAddress(long);void DispRequest(s8*,unsigned long);void NakigoeDispFunc(tagWINDOW_WORK*,tagSPRITE_WORK*);void DispFuncSub(NakigoeDispWork*,GSgfxLayerID);u8 NakigoeCheck();};
static pdaMemoNakigoe *_nakigoe;
extern "C" {u32 GSinputButtonsChanged(s32);u32 GSinputButtonsPressed(s32);void GSthreadSwitch();void GSsndPlay(u32,s32,s32);s32 GSsndGetStatus(u32);u16 memoDataGetCount(s32);void *menuPdaMemoListGetPokemonDataPointer(s32);u16 pokemonDataBiosGetVoice(void*);s8 *pokemonNakigoeDataBiosGetDataAddress(void*);}
extern "C" void menuPdaMemoWaveHook(tagWINDOW_WORK *w,tagSPRITE_WORK *s){if(_nakigoe)_nakigoe->NakigoeDispFunc(w,s);}
extern "C" void menuPdaMemoWaveInit(){if(_nakigoe){_nakigoe->Reset();}}
extern "C" void menuPdaMemoWave(s32 pokemon){if(!_nakigoe)_nakigoe=new pdaMemoNakigoe;_nakigoe->Reset();_nakigoe->SetNakigoe(pokemon);pdaMemoNakigoe *work=_nakigoe;for(;;){if(!work->NakigoeCheck())return;u32 changed=GSinputButtonsChanged(1);u32 pressed=GSinputButtonsPressed(1);if(pressed&changed&0x100)work->SetNakigoe(pokemon);else{changed=GSinputButtonsChanged(1);pressed=GSinputButtonsPressed(1);if(pressed&changed&0x200)return;}GSthreadSwitch();}}
void pdaMemoNakigoe::SetNakigoe(long pokemon){u16 voice=GetVocie(pokemon);SetSE(voice);DispRequest(GetWaveDispDataAddress(pokemon),voice);}
void pdaMemoNakigoe::SetSE(unsigned long id){GSsndPlay(id,0,0);}
u16 pdaMemoNakigoe::GetVocie(long pokemon){if(memoDataGetCount(0)){void *p=menuPdaMemoListGetPokemonDataPointer(pokemon);if(p)return pokemonDataBiosGetVoice(p);return 0xFFFF;}return 0xFFFF;}
void pdaMemoNakigoe::DispInit(){for(s32 i=0;i<8;i++)DispRequest(0,0);}
void pdaMemoNakigoe::DispRequest(s8 *data,unsigned long sound){index++;if(index>=8)index=0;waves[index].data=data;waves[index].sound=sound;waves[index].start=0;waves[index].end=0;waves[index].time=0;waves[index].samples=1;waves[index].alpha=255.0f;waves[index].speed=0.5f;for(s32 i=index-1;i>=0;i--){waves[i].time+=waves[i].count;waves[i].speed+=0.2f;}for(u32 i=7;i>index;i--){waves[i].time+=waves[i].count;waves[i].speed+=0.2f;}}
void pdaMemoNakigoe::NakigoeDispFunc(tagWINDOW_WORK *w,tagSPRITE_WORK *){for(s32 i=0;i<8;i++)DispFuncSub(&waves[i],(GSgfxLayerID)w->layer);for(s32 i=index-1;i>=0;i--){waves[i].alpha-=10.0f;if(waves[i].alpha<0)waves[i].alpha=0;}for(u32 i=7;i>index;i--){waves[i].alpha-=10.0f;if(waves[i].alpha<0)waves[i].alpha=0;}}
u8 pdaMemoNakigoe::NakigoeCheck(){s32 i;u8 playing=0;for(i=0;i<8;i++)if(waves[i].data){switch(GSsndGetStatus(waves[i].sound)){case 0:case 1:break;case 2:playing=1;break;case 3:break;}}return playing;}
s8 *pdaMemoNakigoe::GetWaveDispDataAddress(long pokemon){s32 count=memoDataGetCount(0);if(count){void *p=menuPdaMemoListGetPokemonDataPointer(pokemon);if(p)return pokemonNakigoeDataBiosGetDataAddress(p);return 0;}return 0;}

struct WaveSpline { u8 reserved[12]; GSvec* points; };
extern "C" {
WaveSpline* GSsplineCreate(s32,s32,u8);
void GSsplineAddControlVectorValue(WaveSpline*,GSvec*,f32);
void GSsplineFree(WaveSpline*);
GSgfxVF* GSgfxVFBuildTemp(s32,s32,s32,s32,s32,s32,s32,s32,s32);
}
union WaveFifo { s16 shortValue; u32 word; };
static inline void waveVertex(f32 x,f32 y) { volatile WaveFifo* fifo=(volatile WaveFifo*)0xcc008000;fifo->shortValue=(s16)x;fifo->shortValue=(s16)y; }
static void _drawLine(GSgfxLayerID layerID,GSvec* from,GSvec* to,f32 count) {
    GSgfxLayer* layer=GSgfxLayerFindByID(layerID);
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0,3,0,0,1,5,0,0,0));
    layer->primitive=0xa8;layer->setLineWidth(24,0);layer->beginSurface(2);
    waveVertex(from->param1,0.5f*from->param2+105.0f);
    *(volatile u32*)0xcc008000=0x96e6f000|(u8)(s32)from->param3;
    waveVertex(to->param1,0.5f*to->param2+105.0f);
    *(volatile u32*)0xcc008000=0x96e6f000|(u8)(s32)to->param3;
    layer->endSurface();layer->setLineWidth(6,0);
}
void pdaMemoNakigoe::DispFuncSub(NakigoeDispWork* work,GSgfxLayerID layer) {
    WaveSpline* spline;
    s8* data=work->data;
    if(!data)return;
    u32 count;
    s32 length;
    count=(u8)data[0]+2;
    length=(u8)count;
    work->count=(f32)(u8)count;
    if(work->samples<length)work->samples++;
    else if(work->time<length)work->time++;
    else if(work->time<length+30) {
        work->time++;
        if(work->end<(u8)count)work->end+=work->speed;
    } else if(work->start<(u8)count) {
        work->start+=work->speed;
        if(work->end<(u8)count)work->end+=work->speed;
    } else if(work->end<(u8)count)work->end+=work->speed;
    spline=GSsplineCreate(3,1,count);
    if(spline) {
        GSvec control,from,to;
        f32 time;
        f32 step=1.0f/(f32)(u8)count;
        control.param1=0.0f;control.param2=0.0f;control.param3=work->alpha;
        f32 spacing=work->count;
        GSsplineAddControlVectorValue(spline,&control,0.0f);
        time=step;
        spacing=556.0f/spacing;
        control.param1+=spacing;
        for(s32 i=0;i<length-2;i++) {
            control.param2=(f32)data[i+1];control.param2=-control.param2;
            GSsplineAddControlVectorValue(spline,&control,time);
            time+=step;control.param1+=spacing;
        }
        control.param2=0.0f;control.param1=556.0f;
        GSsplineAddControlVectorValue(spline,&control,1.0f);
        s32 i=0;
        for(;i<(s32)work->start;i++) {
            from=spline->points[i];from.param3=0.0f;spline->points[i]=from;
        }
        i=(s32)work->start;
        for(;i<(s32)work->end;i++) {
            from=spline->points[i];
            s32 start=(s32)work->start;
            from.param3=(work->alpha/(f32)((s32)work->end-start))*(f32)(i-start);
            spline->points[i]=from;
        }
        for(s32 j=0;j<work->samples-1;j++) {
            from=spline->points[j];to=spline->points[j+1];
            _drawLine(layer,&from,&to,work->count);
        }
        GSsplineFree(spline);
    }
}
