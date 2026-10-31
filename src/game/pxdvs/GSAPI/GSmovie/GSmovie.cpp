#include <game/pxdvs/GSAPI/GSmovie/moviePrivate.hpp>
#include <libc/string.h>
static u8 _initFlag;
static s32 _movieDaemonHDL;
static u32 _maxStreaming;
static __GSmovieStreaming* _movieStreaming;
static __GSmovieStreaming* _activeMovieStreaming;
static u8 _movieValidScratch;
static void (*OldVIPostCallback)(u32);
static u8 _readWaitFlag;
static u8* _readAddr;
static u32 _readOffset,_readBytes;
static s32 _movieLayerUseCount;
static s32 _movieLayerID=-1;
extern "C" {
void GSgfxRenderWaitForDrawComplete__Fv();
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(s32);
void GSfsysCancel(u32); void GSthreadSwitch(); void GSscratchSetValid();
void (*GSgfxVideoSetVSyncCallback(void(*)(u32)))(u32);
u32 GSfsysStreamGetCacheSize();
u8 GSfsysStreamGetData(u32,u32,void*,u32,u32,void(*)(s32,void*,s32),void*,s32);
}
static inline __GSmovieStreaming* findMovie(u32 handle) {
    u32 base;
    __GSmovieStreaming* movie;
    s32 offset;
    u32 count;
    count=_maxStreaming;
    offset=0;
    base=(u32)_movieStreaming;
    for(u32 i=0;i<count;++i) {
        movie=(__GSmovieStreaming*)(base+offset);
        if(movie->state && handle==movie->handle) return movie;
        offset+=0x20;
    }
    return 0;
}
static void _movieStreamTHPPlayerPrepareGetDataCallback(s32, void*, s32);
static inline bool _movieReadStart(__GSmovieStreaming* s) {
    s32 level = OSDisableInterrupts();
    bool started;
    if ((u8)GSfsysStreamGetData(s->handle, 0, _readAddr, 0x8000, _readOffset,
                                _movieStreamTHPPlayerPrepareGetDataCallback, s, 0) == 1) {
        _readWaitFlag = 0;
        started = true;
    } else {
        started = false;
    }
    OSRestoreInterrupts(level);
    return started;
}
static void _movieStreamTHPPlayerPrepareGetDataCallback(s32, void* arg, s32) {
    __GSmovieStreaming* s = (__GSmovieStreaming*)arg;
    MovieDecoder* p = s->decoder;
    _readOffset += 0x8000;
    if (_readOffset >= p->movieBytes) {
        _readOffset = 0;
    }
    if (_readOffset >= GSfsysStreamGetCacheSize()) {
        _readOffset = 0;
    }
    _readAddr += 0x8000;
    _readBytes += 0x8000;
    if (_readBytes >= p->movieBytes) {
        _readWaitFlag = 1;
    } else {
        bool started = _movieReadStart(s);
        if (!started) {
            _readWaitFlag = 1;
        }
    }
}
static inline void movieContinueOne(u32 handle) {
    if(_initFlag) {__GSmovieStreaming* movie=findMovie(handle);if(movie)movie->decoder->paused=0;}
}
static inline void moviePauseOne(u32 handle) {
    if(_initFlag) {__GSmovieStreaming* movie=findMovie(handle);if(movie)movie->decoder->paused=1;}
}
extern "C" {
void GSmovieAllContinue() {
    for(u32 i=0;i<_maxStreaming;++i) {
        __GSmovieStreaming* current=&_movieStreaming[i];
        if(current->state)movieContinueOne(current->handle);
    }
}
void GSmovieAllPause() {
    for(u32 i=0;i<_maxStreaming;++i) {
        __GSmovieStreaming* current=&_movieStreaming[i];
        if(current->state)moviePauseOne(current->handle);
    }
}
inline void movieStop(u32 handle) {
    if(_initFlag) {
        __GSmovieStreaming* movie=findMovie(handle);
        if(movie) {
            GSgfxRenderWaitForDrawComplete__Fv();
            if(movie->layer && --_movieLayerUseCount==0) { Remove__16GSgfxLayerConfigF12GSgfxLayerID(_movieLayerID); _movieLayerID=-1; }
            GSfsysCancel(movie->handle);
            MovieDecoder* decoder=movie->decoder;
            if(decoder->state) {
                decoder->nextState=0; decoder->state=0;
                if(decoder->hasAudio) _StreamQuit(movie);
                decoder->videoError=0; decoder->audioError=0;
            }
            GSmemFree(movie->workBuffer);
            if(movie==_activeMovieStreaming) _activeMovieStreaming=0;
            s32 interrupts=OSDisableInterrupts();
            movie->state=0; movie->handle=0;
            if(movie->decoder) { GSmemFree(movie->decoder); movie->decoder=0; }
            OSRestoreInterrupts(interrupts);
            if(_movieValidScratch==1) {
                u8 active=0;
                for(u32 i=0;i<_maxStreaming;++i) if(_movieStreaming[i].state) active=1;
                if(!active) { GSscratchSetValid(); _movieValidScratch=0; GSgfxVideoSetVSyncCallback(OldVIPostCallback); OldVIPostCallback=0; }
            }
        }
    }
}
void GSmovieStop(u32 handle) {
    if(_initFlag) {
        __GSmovieStreaming* movie=findMovie(handle);
        if(movie) {
            GSgfxRenderWaitForDrawComplete__Fv();
            if(movie->layer && --_movieLayerUseCount==0) { Remove__16GSgfxLayerConfigF12GSgfxLayerID(_movieLayerID); _movieLayerID=-1; }
            GSfsysCancel(movie->handle);
            MovieDecoder* decoder=movie->decoder;
            if(decoder->state) {
                decoder->nextState=0; decoder->state=0;
                if(decoder->hasAudio) _StreamQuit(movie);
                decoder->videoError=0; decoder->audioError=0;
            }
            GSmemFree(movie->workBuffer);
            if(movie==_activeMovieStreaming) _activeMovieStreaming=0;
            s32 interrupts=OSDisableInterrupts();
            movie->state=0; movie->handle=0;
            if(movie->decoder) { GSmemFree(movie->decoder); movie->decoder=0; }
            OSRestoreInterrupts(interrupts);
            if(_movieValidScratch==1) {
                u8 active=0;
                for(u32 i=0;i<_maxStreaming;++i) if(_movieStreaming[i].state) active=1;
                if(!active) { GSscratchSetValid(); _movieValidScratch=0; GSgfxVideoSetVSyncCallback(OldVIPostCallback); OldVIPostCallback=0; }
            }
        }
    }
}

void GSmoviePlayWait(u32 handle) {
    if(_initFlag) {
        for(;;) {
            __GSmovieStreaming* movie=findMovie(handle);
            if(!movie) return;
            switch(movie->state) { case 0: case 9: case 10: case 11: return; }
            GSthreadSwitch();
        }
    }
}
s32 fn_801E3C5C(u32 handle) {
    if(!_initFlag) return -2;
    __GSmovieStreaming* movie=findMovie(handle);
    if(!movie) return -1;
    MovieDecoder* decoder=movie->decoder;
    if(decoder->paused==1) return 2;
    switch(decoder->state) {case 5:return -2;case 3:return 0;default:case 4:return 1;}
}
u8 GSmoviePlayCheck(u32 handle) { if(!_initFlag) return 0; __GSmovieStreaming* movie=findMovie(handle); if(!movie) return 0; return 1; }
}

#pragma force_active on
static s32 _THPPlayerSetBuffer(__GSmovieStreaming* movie) {
    s32 i;
    u8* memory;
    MovieDecoder* decoder=movie->decoder;
    if(decoder->state==0) {
        memory=movie->workBuffer;
        if(decoder->preload) { decoder->preloadBuffer=memory; memory+=decoder->movieBytes; }
        for(i=0;i<10;++i) {
            decoder->reads[i].data=memory; decoder->reads[i].valid=0; decoder->reads[i].video=0;
            if(decoder->hasAudio) decoder->reads[i].audio=0; else decoder->reads[i].audio=1;
            decoder->reads[i].size=0; memory+=(decoder->maxBufferSize+31)&~31;
        }
        u32 pixels=decoder->width*decoder->height;
        u32 yBytes=(pixels+31)&~31;
        u32 uvBytes=((pixels>>2)+31)&~31;
        for(i=0;i<3;++i) {
            decoder->textures[i].y=memory; DCInvalidateRange(memory,yBytes); memory+=yBytes;
            decoder->textures[i].u=memory; DCInvalidateRange(memory,uvBytes); memory+=uvBytes;
            decoder->textures[i].v=memory; DCInvalidateRange(memory,uvBytes); memory+=uvBytes;
            decoder->textures[i].valid=0; decoder->textures[i].displayed=0;
        }
        if(decoder->hasAudio) {
            for(i=0;i<6;++i) {
                decoder->audio[i].buffer=(s16*)memory; decoder->audio[i].current=(s16*)memory; decoder->audio[i].samples=0; decoder->audio[i].state[0]=0;
                memory+=((decoder->maxAudioSamples*4)+31)&~31;
            }
            decoder->leftBuffer=(s16*)memory;
            memory+=((((u32)(0.5f+(f32)(decoder->sampleRate*60)/1000.0f)+31)*2)&~63);
            if(decoder->channels==2) {
                decoder->rightBuffer=(s16*)memory;
                memory+=((((u32)(0.5f+(f32)(decoder->sampleRate*60)/1000.0f)+31)*2)&~63);
            }
        }
        *(u8**)((u8*)decoder+0x8074)=memory;
        return 1;
    }
    return 0;
}

#pragma force_active reset

extern "C" MovieDecoder* GSmovieStreamPreFunc(u32 handle) {
    if(!_initFlag) return 0;
    __GSmovieStreaming* movie=findMovie(handle);
    if(!movie) return 0;
    return movie->decoder;
}
extern "C" void GSfsysStreamSetLoopFlag(u32,u32,u8);
extern "C" void GSmovieStreamPostFunc(u32 handle,u32 resource) {
    if(_initFlag) {
        __GSmovieStreaming* movie=findMovie(handle);
        if(movie) { movie->state=3; GSfsysStreamSetLoopFlag(handle,resource,movie->loop); }
    }
}
struct GSgfxLayer;
enum GSgfxLayerPass { MOVIE_PASS_DEFAULT };
struct GStexture;
struct GSgfxLayer { u8 reserved0[0x28]; s32 id; void textureCopy(GSgfxLayerPass,GStexture*,bool,u8*,bool,bool,bool); };
static void _movieRender(GSgfxLayer*,GSgfxLayerPass);
extern "C" {
void THPGXSetRenderLayer(GSgfxLayer*); void THPGXYuv2RgbSetup(); void THPGXRestore();
u16 THPGXYuv2RgbDraw(void*,void*,void*,s16,s16,s16,s16,s16,s16);
}
extern void _movieDaemon();
extern "C" void GSgfxTokenWaitForClearAndReset(u16*);
#pragma force_active on
static void _movieBeforeRender(f32) {
    u8 active=0;
    for(u32 i=0;i<_maxStreaming;++i) {
        __GSmovieStreaming* movie=&_movieStreaming[i];
        if(movie->state && GSmoviePlayCheck(movie->handle)) {
            active=1;
            switch((s32)movie->decoder->state) {
            case 3:case 5: movie->state=10;break;
            case 4:break;
            }
        }
    }
    if(active==1) {
        MovieDecoder* decoder;
        for(u32 i=0;i<_maxStreaming;++i) {
            __GSmovieStreaming* movie=&_movieStreaming[i];
            if(movie->state) {
                decoder=movie->decoder;
                GSgfxTokenWaitForClearAndReset(&movie->token);
                for(s32 j=0;j<3;++j) {
                    if(decoder->textures[j].displayed==1) {decoder->textures[j].valid=decoder->textures[j].displayed=0;}
                }
            }
        }
    }
}
#pragma force_active reset
struct GSgfxRenderModule {void* reserved00;void(*update)(f32);void(*render)(GSgfxLayer*,GSgfxLayerPass);void(*fastRender)();void* reserved10;void* reserved14;u32 id;};
extern void GSgfxRenderModuleRegister(u8,GSgfxRenderModule*,void*);
extern "C" u32 GSgappCreate(s32,u8,u32,void(*)(u32,u32));
extern "C" void GSgappSetName(u32,const char*);
static inline void _movieStreamingClear()
{
    __GSmovieStreaming* movie;
    u32 i;
    for(i=0;i<_maxStreaming;++i) {
        movie=&_movieStreaming[i];
        movie->handle=0;movie->state=0;movie->decoder=0;
    }
}
extern "C" void GSmovieInit() {
    GSgfxRenderModule module={0,_movieBeforeRender,_movieRender,0,0,0,0xb29a48e1};
    if(_initFlag!=1) {
        _maxStreaming=4;
        _movieStreaming=(__GSmovieStreaming*)GSmemAllocAlignFromEnd(0x80,0x20);
        u8 success;
        if(!_movieStreaming) success=0;
        else {
            _movieStreamingClear();
            success=1;
        }
        if(success) {
            _movieDaemonHDL=GSgappCreate(1,30,0,(void(*)(u32,u32))_movieDaemon);
            GSgappSetName(_movieDaemonHDL,"GSmovieDaemon");
            _activeMovieStreaming=0;_movieValidScratch=0;
            GSgfxRenderModuleRegister(8,&module,0);_initFlag=1;
        }
    }
}
extern "C" u32 VIGetNextField();
extern "C" u32 VIGetTvFormat();

inline THPTextureSet *movieNextTexture(__GSmovieStreaming *movie)
{
    MovieDecoder *decoder=movie->decoder;
    THPTextureSet *texture=&decoder->textures[decoder->texRead];
    if(texture->valid==0 || texture->displayed==1) return 0;
    decoder->texRead++;
    if(decoder->texRead>=3) decoder->texRead=0;
    return texture;
}

inline u8 movieFieldReady(__GSmovieStreaming *movie)
{
    MovieDecoder *decoder=movie->decoder;
    if(decoder->videoType&1) {
        if(VIGetNextField()==0) return 1;
    } else if(decoder->videoType&2) {
        if(VIGetNextField()==1) return 1;
    } else {
        s32 rate=100.0f*decoder->frameRate;
        if(VIGetTvFormat()==1) decoder->playbackClock.targetFrameClock=decoder->videoTicks*rate/5000;
        else decoder->playbackClock.targetFrameClock=decoder->videoTicks*rate/5994;
        if((s32)decoder->playbackClock.frameClock!=(s32)decoder->playbackClock.targetFrameClock) {
            decoder->playbackClock.frameClock=decoder->playbackClock.targetFrameClock;
            return 1;
        }
    }
    return 0;
}

static inline u8 movieInitialFieldReady(__GSmovieStreaming *movie) {
    s32 field = movie->decoder->videoType;
    if (field & 1) {
        if (VIGetNextField() == 0) return 1;
    } else if (field & 2) {
        if (VIGetNextField() == 1) return 1;
    } else {
        return 1;
    }
    return 0;
}

void _PlayControlExec(__GSmovieStreaming *movie)
{
    THPTextureSet *texture;
    MovieDecoder *decoder=movie->decoder;
    if(decoder->paused!=1) {
        texture=(THPTextureSet *)-1;
        if(decoder->state==2) {
            if(decoder->videoError!=0 || decoder->audioError!=0) {
                decoder->nextState=5;
                decoder->state=5;
                return;
            }
            decoder->videoTicks++;
            u8 ready;
            if(decoder->videoTicks==0) {
                ready=movieInitialFieldReady(movie);
                if(ready) {
                    if(decoder->hasAudio) {
                        if(decoder->lastAudioFrame-decoder->playedAudioFrame<=1) {
                            texture=movieNextTexture(movie);
                            decoder->lastAudioFrame++;
                        } else {
                            if(_StreamPlay(movie)==0) {
                                decoder->nextState=5;
                                decoder->state=5;
                                return;
                            }
                            decoder->nextState=2;
                        }
                    } else texture=movieNextTexture(movie);
                } else decoder->videoTicks=-1;
            } else {
                if(decoder->hasAudio && decoder->videoTicks==1 && decoder->nextState!=2) {
                    if(_StreamPlay(movie)==0) {
                        decoder->nextState=5;
                        decoder->state=5;
                        return;
                    }
                    decoder->nextState=2;
                }
                if(movieFieldReady(movie)) {
                    if(decoder->hasAudio) {
                        if(decoder->lastAudioFrame-decoder->playedAudioFrame<=1) {
                            texture=movieNextTexture(movie);
                            decoder->lastAudioFrame++;
                        }
                    } else texture=movieNextTexture(movie);
                }
            }
            if(texture!=0 && texture!=(THPTextureSet *)-1) {
                if(decoder->displayTexture) decoder->displayTexture->displayed=1;
                decoder->displayTexture=texture;
            }
            if(!(decoder->loop&1)) {
                if(decoder->hasAudio) {
                    u32 frame = decoder->playedAudioFrame + decoder->currentFrame;
                    if(frame==decoder->frames && decoder->currentAudio==0) {
                        decoder->nextState=3;
                        decoder->state=3;
                    }
                } else {
                    u32 frame;
                    if(decoder->displayTexture) frame=decoder->displayTexture->frame+decoder->currentFrame;
                    else frame=decoder->currentFrame-1;
                    if(frame==decoder->frames-1 && texture==0) {
                        decoder->nextState=3;
                        decoder->state=3;
                    }
                }
            }
        }
    }
}

#pragma force_active on
static void _PlayControl(u32 count) {
    if(OldVIPostCallback) OldVIPostCallback(count);
    s32 offset;
    u32 i;
    i=0;
    offset=0;
    for(;i<_maxStreaming;) {
        __GSmovieStreaming* movie=(__GSmovieStreaming*)((u8*)_movieStreaming+offset);
        if(movie->state) _PlayControlExec(movie);
        ++i;
        offset+=0x20;
    }
}
#pragma force_active reset

static void _movieRender(GSgfxLayer* layer,GSgfxLayerPass pass) {
    __GSmovieStreaming* movie;
    MovieDecoder* decoder;
    if(pass==MOVIE_PASS_DEFAULT) {
        for(u32 i=0;i<_maxStreaming;++i) {
            movie=&_movieStreaming[i];
            if(!movie->state || !movie->decoder->visible) continue;
            if(movie->layer==0) { if(layer->id!=2) continue; }
            else if(_movieLayerID!=layer->id) continue;
            decoder=movie->decoder;
            if(decoder->state && decoder->displayTexture) {
                THPGXSetRenderLayer(layer);
                THPGXYuv2RgbSetup();
                THPTextureSet* t=decoder->displayTexture;
                movie->token=THPGXYuv2RgbDraw(t->y,t->u,t->v,movie->x,movie->y,decoder->width,decoder->height,decoder->width,decoder->height);
                THPGXRestore();
            }
            if(movie->layer) layer->textureCopy(pass,(GStexture*)movie->layer,false,0,true,true,true);
        }
    }
}
extern "C" {
u32 OSGetTick();
void GSgfxVideoGetEFBSize(u16 *,u16 *);
void GSscratchSetInvalid();
void THPInit();
}

inline void movieOpenDecoder(__GSmovieStreaming *movie)
{
    MovieDecoder *decoder=movie->decoder;
    decoder->hasAudio=0;
    for(u32 i=0;i<decoder->componentCount;i++) {
        switch(decoder->componentTypes[i]) {
        case 1: decoder->hasAudio=1;
        case 0: break;
        default: return;
        }
    }
    decoder->nextState=0;
    decoder->state=0;
    decoder->loop=0;
}

inline u32 movieBufferSize(__GSmovieStreaming *movie)
{
    MovieDecoder *decoder=movie->decoder;
    u32 size;
    if(decoder->preload) size=(decoder->movieBytes+31)&~31;
    else size=0;
    u32 pixels=decoder->width*decoder->height;
    u32 uvBytes;
    size+=((decoder->maxBufferSize+31)&~31)*10;
    size+=((pixels+31)&~31)*3;
    uvBytes=(((pixels>>2)+31)&~31)*3;
    size+=uvBytes;
    size+=uvBytes;
    if(decoder->hasAudio) {
        size+=((decoder->maxAudioSamples*4+31)&~31)*6;
        size+=decoder->channels*((((u32)(0.5f+(f32)(decoder->sampleRate*60)/1000.0f)+31)*2)&~63);
    }
    return size;
}

inline u8 moviePrepareDecoder(__GSmovieStreaming *movie,bool loop,u8 track)
{
    MovieDecoder *decoder=movie->decoder;
    if(decoder->state==0) {
        decoder->currentOffset=decoder->firstFrameOffset;
        decoder->currentSize=decoder->firstFrameSize;
        decoder->currentFrame=0;
        decoder->fetchSize=decoder->currentSize;
        if(decoder->hasAudio) {
            if((s32)track<0 || track>=decoder->tracks) return 0;
            decoder->audioTrack=track;
        }
        decoder->loop=loop&1;
        decoder->framesDecoded=0;
        decoder->lastAudioFrame=-1;
        decoder->playedAudioFrame=0;
        return 1;
    }
    return 0;
}

inline void movieStartDecoder(__GSmovieStreaming *movie)
{
    MovieDecoder *decoder=movie->decoder;
    u8 state=decoder->state;
    if(state==1 || state==4) {
        decoder->state=2;
        decoder->playbackClock.frameClock=0;
        decoder->playbackClock.targetFrameClock=0;
        decoder->videoTicks=-1;
        if(OldVIPostCallback==0) OldVIPostCallback=GSgfxVideoSetVSyncCallback(_PlayControl);
    }
}

static inline u8 movieRequestPreload(__GSmovieStreaming* movie) {
 s32 interrupts=OSDisableInterrupts();
 u8 success;
 if(GSfsysStreamGetData(movie->handle,0,_readAddr,0x8000,_readOffset,_movieStreamTHPPlayerPrepareGetDataCallback,movie,0)==1) {success=1;_readWaitFlag=0;}else success=0;
 OSRestoreInterrupts(interrupts);
 return success;
}

static inline s32 movieReadState(__GSmovieStreaming* movie) {
 MovieDecoder* decoder=movie->decoder;
 if(_readWaitFlag==0)return 2;
 if(_readBytes>=decoder->movieBytes)return 1;
 return 0;
}

void _movieDaemon()
{
    u16 width,height;
    u32 i=0;
    for(;i<_maxStreaming;i++) {
        __GSmovieStreaming *movie=&_movieStreaming[i];
        if(movie->state) {
            MovieDecoder *decoder=movie->decoder;
            if(decoder->startAudio==1) {
                decoder->startAudio=0;
                _StreamPlay(movie);
            }
            _movieStreamPrepareGetData(movie);
            switch(movie->state) {
            case 3: {
                if(decoder->version!=0x11000) {
                    movieStop(movie->handle);
                    break;
                }
                movieOpenDecoder(movie);
                u32 bufferBytes=movieBufferSize(movie);
                movie->workBuffer=(u8 *)GSmemAllocAlignFromEnd(bufferBytes+0x1000,0x20);
                if(movie->workBuffer==0) {
                    movieStop(movie->handle);
                    break;
                }
                _THPPlayerSetBuffer(movie);
                if(decoder->tracks!=1) movie->track=OSGetTick()%decoder->tracks;
                else movie->track=0;
                if(movie->layer==0) {
                    GSgfxVideoGetEFBSize(&width,&height);
                    movie->x=(width-decoder->width)>>1;
                    movie->y=(height-decoder->height)>>1;
                    if(_activeMovieStreaming==0) _activeMovieStreaming=movie;
                } else {
                    movie->x=0;
                    movie->y=0;
                }
                if(_movieValidScratch==0) {
                    GSscratchSetInvalid();
                    THPInit();
                }
                _movieValidScratch=1;
                movie->state=2;
            }
            case 2:
                if(moviePrepareDecoder(movie,movie->loop==1,movie->track)==0) {
                    movie->state=10;
                    break;
                }
                if(decoder->preload) {
                    _readWaitFlag=0;
                    _readAddr=decoder->preloadBuffer;
                    _readOffset=0;
                    _readBytes=0;
                    movie->state=6;
                } else {
                    movie->state=7;
                    break;
                }
            case 6: {
                if(movieRequestPreload(movie)!=1)break;
                movie->state=5;
            }
            case 5: {
                s32 state=movieReadState(movie);
                switch(state) {
                case 2: break;
                case 0: movie->state=6;break;
                case 1: movie->state=7;break;
                }
                break;
            }
            case 7:
                _movieStreamDecode(movie);
                if(movie->ready) {
                    decoder->state=1;
                    decoder->nextState=0;
                    decoder->displayTexture=0;
                    decoder->currentAudio=0;
                    if(decoder->hasAudio) {
                        _StreamInit(movie);
                        _StreamInitFillStreamBuffer(movie);
                    }
                    movieStartDecoder(movie);
                    movie->state=9;
                }
                break;
            case 9:
                _movieStreamDecode(movie);
                break;
            case 10:
                movie->state=11;
                movieStop(movie->handle);
                break;
            }
        }
    }
}

extern "C" {
u8 GSfsysReadStreaming(u32);
s32 Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(char*,u32,u32,u32,s32,bool,bool,bool,s32,s32);
void GSmoviePlay(u32 handle,s8 preload,s8 loop,u32 layer) {
    if(_initFlag) {
        switch(fn_801E3C5C(handle)) {
        case 2:
            if(_initFlag) {
                __GSmovieStreaming* movie=findMovie(handle);
                if(movie)movie->decoder->paused=0;
            }
            break;
        case 1:break;
        default: {
            s32 interrupts=OSDisableInterrupts();
            __GSmovieStreaming* movie=0;
            s32 offset;
            u32 base;
            u32 count=_maxStreaming;
            offset=0;
            base=(u32)_movieStreaming;
            for(u32 i=0;i<count;i++,offset+=0x20) {
                movie=(__GSmovieStreaming*)(base+offset);
                if(movie->state==0) {
                    movie->decoder=(MovieDecoder*)GSmemAllocAlignFromEnd(0x8280,0x20);
                    if(!movie->decoder)movie=0;
                    else movie->state=1;
                    break;
                }
            }
            OSRestoreInterrupts(interrupts);
            if(movie) {
                movie->state=1;movie->layer=layer;movie->handle=handle;
                movie->workBuffer=0;movie->ready=0;movie->reading=1;movie->loop=loop;movie->track=0;movie->token=0;*(u8*)&movie->reserved1a=0;
                MovieDecoder* decoder=movie->decoder;
                memset(&decoder->width,0,12);memset(&decoder->channels,0,16);
                decoder->fetchState=1;decoder->streamOffset=0;decoder->fetchArg=0;decoder->fetchSize=0;decoder->fetchPos=0;decoder->videoWork=0;
                decoder->state=0;decoder->nextState=0;decoder->loop=0;decoder->hasAudio=0;decoder->videoError=0;decoder->audioError=0;
                decoder->preload=preload;decoder->startAudio=0;decoder->paused=0;decoder->visible=1;
                decoder->preloadBuffer=0;decoder->currentOffset=0;decoder->currentSize=0;decoder->currentFrame=0;
                decoder->videoTicks=0;decoder->playbackClock.frameClock=0;decoder->playbackClock.targetFrameClock=0;decoder->framesDecoded=0;decoder->audioTrack=0;decoder->lastAudioFrame=0;decoder->playedAudioFrame=0;
                decoder->token1=0;decoder->token2=0;decoder->displayTexture=0;decoder->currentAudio=0;
                decoder->readWrite=0;decoder->readVideo=0;decoder->readAudio=0;decoder->texWrite=0;decoder->texRead=0;decoder->audioWrite=0;decoder->audioRead=0;
                decoder->leftStream=-1;decoder->rightStream=-1;decoder->leftBuffer=0;decoder->rightBuffer=0;
                memset(decoder->marks,0,0x48);
                if(!GSfsysReadStreaming(handle)) {
                    s32 interrupts=OSDisableInterrupts();movie->state=0;movie->handle=0;
                    if(movie->decoder) {GSmemFree(movie->decoder);movie->decoder=0;}
                    OSRestoreInterrupts(interrupts);
                }
                if(movie->layer) {
                    if(!_movieLayerUseCount)_movieLayerID=Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset("movie",0x2000,0,4,0,false,false,false,-1,3);
                    _movieLayerUseCount++;
                }
            }
            break;
        }
        }
    }
}
}
