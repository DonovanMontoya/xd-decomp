#include <game/pxdvs/GSAPI/GSmovie/moviePrivate.hpp>
#include <libc/string.h>
extern "C" void _StreamQuit(__GSmovieStreaming* movie) {
    MovieDecoder* decoder=movie->decoder;
    sndStreamFree(decoder->leftStream);
    decoder->leftStream=-1;
    if(decoder->rightStream!=-1U) { sndStreamFree(decoder->rightStream); decoder->rightStream=-1; }
}
extern "C" u8 _StreamPlay(__GSmovieStreaming* movie) {
    MovieDecoder* decoder=movie->decoder;
    if(decoder->leftStream!=-1U && sndStreamActivate(decoder->leftStream)) {
        if(decoder->rightStream!=-1U) {
            if(sndStreamActivate(decoder->rightStream)) return 1;
            sndStreamDeactivate(decoder->leftStream);
        } else return 1;
    }
    return 0;
}

extern u32 StreamUpdateCallback(void*,u32,void*,u32,u32);
extern "C" u32 sndStreamAllocEx(u8,void*,u32,u32,u8,u32,u8,u8,u32,u32,u32,u32(*)(void*,u32,void*,u32,u32),void*,u32);
extern "C" u8 _StreamInit(__GSmovieStreaming* movie) {
    u32 samples;
    MovieDecoder* decoder=movie->decoder;
    u32 rate=decoder->sampleRate;
    samples=((u32)(0.5f+(f32)(rate*60)/1000.0f)+31)&~31;
    decoder->leftStream=sndStreamAllocEx(255,decoder->leftBuffer,samples,rate,127,decoder->channels==2?0:64,0,0,0,0,0x30000,StreamUpdateCallback,movie,0);
    if(decoder->leftStream==-1U) return 0;
    if(decoder->channels==2) {
        decoder->rightStream=sndStreamAllocEx(255,decoder->rightBuffer,samples,decoder->sampleRate,127,127,0,0,0,0,0x30000,StreamUpdateCallback,0,0);
        if(decoder->rightStream==-1U) { sndStreamFree(decoder->leftStream); return 0; }
    }
    decoder->markRead=0; decoder->markWrite=0;
    decoder->reserved8260[1]=0; decoder->reserved8260[0]=0;
    decoder->reserved8260[3]=0; decoder->reserved8260[2]=0;
    decoder->samplesPlayed=0;
    return 1;
}
#pragma force_active on
static u32 GetAudioSample(__GSmovieStreaming* movie,s16* left,s16* right,u32 requested,s32* status) {
    u32 result=(u32)movie;
    MovieDecoder* decoder=movie->decoder;
    if(!decoder->currentAudio) {
        if(!decoder->audio[decoder->audioRead].state[0]) { *status=2; return 0; }
        decoder->currentAudio=&decoder->audio[decoder->audioRead];
    }
    THPAudioBuffer* audio=decoder->currentAudio;
    u32 count=audio->samples;
    if(count) {
        if(count>=requested) count=requested;
        s16* input=audio->current;
        result=count;
        if(!right) {
            for(u32 n=0; n<count; ++n) { *left++=input[1]; input+=2; }
        } else {
            for(u32 n=0; n<count; ++n) { *right++=input[0]; *left++=input[1]; input+=2; }
        }
        decoder->currentAudio->samples-=count;
        decoder->currentAudio->current=input;
        if(!decoder->currentAudio->samples) {
            decoder->currentAudio->state[0]=0;
            ++decoder->audioRead;
            if(decoder->audioRead>=6) decoder->audioRead=0;
            decoder->currentAudio=0;
            *status=1;
            return result;
        }
        *status=0;
        return result;
    }
    // The release build returns the incoming descriptor when its current buffer is empty.
    return result;
}
#pragma force_active reset

extern "C" u32 GSfsysStreamGetCacheSize();
extern void _movieStreamPrepareGetDataCallback_Exec(__GSmovieStreaming*,u32,u32);
extern "C" s32 THPVideoDecode(void*,void*,void*,void*,void*);
#pragma force_active on
static void _movieStreamPrepareGetDataCallback(s32,void* result,s32 context) {
    __GSmovieStreaming* movie=(__GSmovieStreaming*)context;
    u32 bytes=(u32)result;
    MovieDecoder* decoder=movie->decoder;
    decoder->streamOffset+=0x8000;
    if(decoder->preload) {
        if(decoder->streamOffset>=decoder->movieBytes) decoder->streamOffset=0;
    } else if(decoder->streamOffset>=decoder->movieBytes) decoder->streamOffset=0;
    else if(decoder->streamOffset>=GSfsysStreamGetCacheSize()) decoder->streamOffset=0;
    _movieStreamPrepareGetDataCallback_Exec(movie,0,bytes);
}
static s32 _VideoDecode(__GSmovieStreaming* movie,THPReadBuffer* read,THPTextureSet* texture) {
    u32 component=0;
    u32* sizes;
    u8* data;
    MovieDecoder* decoder=movie->decoder;
    s32 remaining=0;
    u32 raw = (u32)read->data;
    sizes=(u32*)(raw+8);
    data=(u8*)(raw+(decoder->componentCount*4+8));
    for(;component<decoder->componentCount;++component) {
        switch(decoder->componentTypes[component]) {
        case 0:
            s32 error=THPVideoDecode(data,texture->y,texture->u,texture->v,decoder->videoWork);
            decoder->audioError=error;
            if(error) {
                if(movie->reading==1) {movie->ready=0;movie->reading=0;}
                decoder->state=5;
            }
            texture->frame=read->frame; texture->valid=1;
            ++decoder->texWrite;
            if(decoder->texWrite>=3) decoder->texWrite=0;
            u32 frames=decoder->framesDecoded;
            s32 audio=decoder->lastAudioFrame+1;
            decoder->framesDecoded=frames+1;
            remaining=(s32)frames<audio ? audio-frames : 0;
            break;
        default: break;
        }
        data+=*sizes;
        sizes++;
    }
    if(movie->reading==1) { movie->ready=1; movie->reading=0; }
    return remaining;
}
#pragma force_active reset

extern "C" void DCFlushRange(void*,u32);
extern "C" void sndStreamARAMUpdate(u32,u32,u32,u32,u32);
extern "C" u8 _StreamInitFillStreamBuffer(__GSmovieStreaming* movie) {
    s32 stereoStatus,monoStatus;
    MovieDecoder* decoder=movie->decoder;
    u32 samples=((u32)(0.5f+(f32)(decoder->sampleRate*60)/1000.0f)+31)&~31;
    if(decoder->channels==2) {
        u32 remaining=samples;
        s16* left=decoder->leftBuffer;
        s16* right=decoder->rightBuffer;
        u64 played=decoder->samplesPlayed;
        for(;;) {
            u32 count=GetAudioSample(movie,left,right,remaining,&stereoStatus);
            played+=count;
            if(stereoStatus==0) break;
            if(stereoStatus==1) {
                remaining-=count;left+=count;if(right)right+=count;
                MovieDecoder* current=movie->decoder;
                current->marks[current->markWrite]=played;
                if(++current->markWrite>=5) current->markWrite=0;
                continue;
            }
            memset(left,0,remaining*2);if(right)memset(right,0,remaining*2);break;
        }
        decoder->samplesPlayed+=samples;
    } else {
        u32 remaining=samples;
        s16* left=decoder->leftBuffer;
        s16* right=0;
        u64 played=decoder->samplesPlayed;
        for(;;) {
            u32 count=GetAudioSample(movie,left,right,remaining,&monoStatus);
            played+=count;
            if(monoStatus==0) break;
            if(monoStatus==1) {
                remaining-=count;left+=count;if(right)right+=count;
                MovieDecoder* current=movie->decoder;
                current->marks[current->markWrite]=played;
                if(++current->markWrite>=5) current->markWrite=0;
                continue;
            }
            memset(left,0,remaining*2);if(right)memset(right,0,remaining*2);break;
        }
        decoder->samplesPlayed+=samples;
    }
    u32 bytes=samples*2;
    DCFlushRange(decoder->leftBuffer,bytes);
    sndStreamARAMUpdate(decoder->leftStream,0,samples,0,0);
    if(decoder->channels==2) {
        DCFlushRange(decoder->rightBuffer,bytes);
        sndStreamARAMUpdate(decoder->rightStream,0,samples,0,0);
    }
    movie->reserved1a=1;
    return 1;
}

extern "C" u8 GSfsysStreamGetData(u32,u32,void*,u32,u32,void(*)(s32,void*,s32),void*,s32);
static inline void _advanceStream(__GSmovieStreaming* movie,u32 size) {
    MovieDecoder* decoder=movie->decoder;
    decoder->streamOffset+=0x8000;
    if(decoder->preload) {
        if(decoder->streamOffset>=decoder->movieBytes) decoder->streamOffset=0;
    } else if(decoder->streamOffset>=decoder->movieBytes) decoder->streamOffset=0;
    else if(decoder->streamOffset>=GSfsysStreamGetCacheSize()) decoder->streamOffset=0;
    _movieStreamPrepareGetDataCallback_Exec(movie,0,size);
}
static inline void prepareMovieStreamGetData(__GSmovieStreaming* movie) {
    MovieDecoder* decoder;
    s32 state;
    u32 size;
    s32 interrupts;
    MovieDecoder* first=movie->decoder;
    interrupts=OSDisableInterrupts();
    switch(movie->state) {
    case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 10:case 11:
        break;
    default:
        if(!first->reads[first->readWrite].valid) {
            size=first->fetchSize;
            if(size) {
                decoder=movie->decoder;
                state=decoder->fetchState;
                switch(state) {
                case 1:
                    decoder->fetchState=2;
                    u8* buffer=decoder->streamBuffer;
                    u32 offset=decoder->streamOffset;
                    if(!(decoder->loop&1) && decoder->fetchPos+decoder->currentFrame>=decoder->frames) {
                        memset(buffer,0,0x8000);
                        _advanceStream(movie,size);
                    } else if(decoder->preload) {
                        memcpy(buffer,decoder->preloadBuffer+offset,0x8000);
                        _advanceStream(movie,size);
                    } else if(!GSfsysStreamGetData(movie->handle,0,buffer,0x8000,offset,_movieStreamPrepareGetDataCallback,(void*)size,(s32)movie)) {
                        decoder->fetchState=state;
                    }
                    break;
                case 2:
                    break;
                case 3:
                    _movieStreamPrepareGetDataCallback_Exec(movie,decoder->fetchArg,size);
                    break;
                }
            }
        }
        break;
    }
    OSRestoreInterrupts(interrupts);
}

extern "C" void _movieStreamPrepareGetData(__GSmovieStreaming* movie) {
    prepareMovieStreamGetData(movie);
}

void _movieStreamPrepareGetDataCallback_Exec(__GSmovieStreaming* movie, u32 offset, u32 size) {
    s32 count = 0x8000 - offset;
    MovieDecoder* decoder = movie->decoder;
    u8* source = decoder->streamBuffer + offset;
    u32 filled = decoder->reads[decoder->readWrite].size;
    u8* destination = decoder->reads[decoder->readWrite].data + filled;
    if (filled + count > size) {
        count = size - filled;
        decoder->fetchArg = offset + count;
        decoder->fetchState = 3;
    } else {
        decoder->fetchArg = 0;
        decoder->fetchState = 1;
    }
    memcpy(destination, source, count);
    decoder->reads[decoder->readWrite].size += count;
    if (decoder->reads[decoder->readWrite].size >= size) {
        decoder->reads[decoder->readWrite].size = 0;
        decoder->reads[decoder->readWrite].valid = 1;
        decoder->reads[decoder->readWrite].frame = decoder->fetchPos;
        decoder->fetchSize = *(u32*)decoder->reads[decoder->readWrite].data;
        ++decoder->readWrite;
        if (decoder->readWrite >= 10) decoder->readWrite = 0;
        ++decoder->fetchPos;
        if (decoder->fetchPos + decoder->currentFrame >= decoder->frames) {
            if (decoder->loop & 1) {
                decoder->fetchPos = 0;
                decoder->fetchArg = 0;
                decoder->fetchState = 1;
                decoder->fetchSize = decoder->currentSize;
            } else decoder->fetchSize = 0;
        }
    } else decoder->reads[decoder->readWrite].valid = 0;
    prepareMovieStreamGetData(movie);
}

static inline void releaseMovieRead(__GSmovieStreaming* movie, THPReadBuffer* read) {
    MovieDecoder* decoder = movie->decoder;
    if (read->video && read->audio) {
        read->valid = 0;
        read->video = 0;
        ++decoder->readVideo;
        if (decoder->readVideo >= 10) decoder->readVideo = 0;
        if (decoder->hasAudio) {
            read->audio = 0;
            ++decoder->readAudio;
            if (decoder->readAudio >= 10) decoder->readAudio = 0;
        }
    }
}
extern "C" u32 THPAudioDecode(s16*, u8*, s32);
extern "C" void _movieStreamDecode(__GSmovieStreaming* movie) {
    THPTextureSet* texture;
    THPAudioBuffer* audio;
    THPReadBuffer* audioRead;
    MovieDecoder* audioDecoder = movie->decoder;
    if (audioDecoder->hasAudio) {
        audio = &audioDecoder->audio[audioDecoder->audioWrite];
        if (audio->state[0] != 1) {
            audioRead = &audioDecoder->reads[audioDecoder->readAudio];
            if (audioRead->valid && audioRead->audio != 1) {
                u32 component = 0;
                u32 raw = (u32)audioRead->data;
                u32* sizes = (u32*)(raw + 8);
                u8* data = (u8*)(raw + (audioDecoder->componentCount * 4 + 8));
                for (; component < audioDecoder->componentCount; ++sizes, ++component) {
                    switch (audioDecoder->componentTypes[component]) {
                    case 1:
                        audio->samples = THPAudioDecode(audio->buffer, data + *sizes * audioDecoder->audioTrack, 0);
                        audio->current = audio->buffer;
                        audio->state[0] = 1;
                        ++audioDecoder->audioWrite;
                        if (audioDecoder->audioWrite >= 6) audioDecoder->audioWrite = 0;
                        goto audioDecoded;
                    default: break;
                    }
                    data += *sizes;
                }
audioDecoded:
                if (audioDecoder->token2 < 2 && !(audioDecoder->loop & 1) && audioRead->frame + audioDecoder->currentFrame == audioDecoder->frames - 1) movie->ready = 1;
                if (audioDecoder->token2 == 2) movie->ready = 1;
                audioRead->audio = 1;
                releaseMovieRead(movie, audioRead);
                ++audioDecoder->token2;
            }
        }
    }
    THPReadBuffer* videoRead;
    MovieDecoder* decoder = movie->decoder;
    if (decoder->hasAudio) {
        while (decoder->token1) {
            texture = &decoder->textures[decoder->texWrite];
            if (texture->valid == 1) return;
            videoRead = &decoder->reads[decoder->readVideo];
            if (!videoRead->valid || videoRead->video == 1) return;
            if ((videoRead->frame + decoder->currentFrame) % decoder->frames == decoder->frames - 1 && !(decoder->loop & 1)) _VideoDecode(movie, videoRead, texture);
            videoRead->video = 1;
            releaseMovieRead(movie, videoRead);
            --decoder->token1;
            ++decoder->framesDecoded;
        }
    }
    texture = &decoder->textures[decoder->texWrite];
    if (texture->valid != 1) {
        videoRead = &decoder->reads[decoder->readVideo];
        if (videoRead->valid && videoRead->video != 1) {
            decoder->token1 = _VideoDecode(movie, videoRead, texture);
            videoRead->video = 1;
            releaseMovieRead(movie, videoRead);
        }
    }
}

extern "C" void OSReport(const char*, ...);
u32 StreamUpdateCallback(void* first, u32 firstSamples, void* second, u32 secondSamples, u32 context) {
    s32 statusA, statusB, statusC, statusD;
    __GSmovieStreaming* movie = (__GSmovieStreaming*)context;
    if (!movie) return 0;
    MovieDecoder* decoder = movie->decoder;
    if (!first && !second && !firstSamples && !secondSamples) {
        OSReport("--- Drop Stream Voice!! ---\n");
        decoder->startAudio = 1;
        return 0;
    }
    u32 samples = (((u32)(0.5f + (f32)(decoder->sampleRate * 60) / 1000.0f) + 31) & ~31) / 2;
    *(u64*)&decoder->reserved8260[2] = *(u64*)&decoder->reserved8260[0] + firstSamples + secondSamples;
    MovieDecoder* timing = movie->decoder;
    u64 position = *(u64*)&decoder->reserved8260[2];
    while ((s32)timing->markRead != timing->markWrite) {
        if (position < timing->marks[timing->markRead]) break;
        ++timing->markRead;
        if ((s32)timing->markRead >= 5) timing->markRead = 0;
        ++timing->playedAudioFrame;
    }
    if (firstSamples + secondSamples >= samples) {
        if (first == decoder->leftBuffer) {
            if (decoder->channels == 2) {
                MovieDecoder* current = movie->decoder;
                u32 remaining = samples;
                s16* left = decoder->leftBuffer;
                s16* right = decoder->rightBuffer;
                u64 played = current->samplesPlayed;
                for (;;) {
                    u32 count = GetAudioSample(movie, left, right, remaining, &statusA);
                    played += count;
                    if (statusA == 0) break;
                    if (statusA == 1) {
                        remaining -= count;
                        left += count;
                        if (right) right += count;
                        MovieDecoder* marks = movie->decoder;
                        marks->marks[marks->markWrite] = played;
                        if (++marks->markWrite >= 5) marks->markWrite = 0;
                        continue;
                    }
                    memset(left, 0, remaining * 2);
                    if (right) memset(right, 0, remaining * 2);
                    break;
                }
                current->samplesPlayed += samples;
            } else {
                MovieDecoder* current = movie->decoder;
                u32 remaining = samples;
                s16* left = decoder->leftBuffer;
                s16* right = 0;
                u64 played = current->samplesPlayed;
                for (;;) {
                    u32 count = GetAudioSample(movie, left, right, remaining, &statusB);
                    played += count;
                    if (statusB == 0) break;
                    if (statusB == 1) {
                        remaining -= count;
                        left += count;
                        if (right) right += count;
                        MovieDecoder* marks = movie->decoder;
                        marks->marks[marks->markWrite] = played;
                        if (++marks->markWrite >= 5) marks->markWrite = 0;
                        continue;
                    }
                    memset(left, 0, remaining * 2);
                    if (right) memset(right, 0, remaining * 2);
                    break;
                }
                current->samplesPlayed += samples;
            }
            u32 bytes = samples * 2;
            DCFlushRange(decoder->leftBuffer, bytes);
            sndStreamARAMUpdate(decoder->leftStream, 0, samples, 0, 0);
            if (decoder->channels == 2) {
                DCFlushRange(decoder->rightBuffer, bytes);
                sndStreamARAMUpdate(decoder->rightStream, 0, samples, 0, 0);
            }
        } else {
            if (decoder->channels == 2) {
                MovieDecoder* current = movie->decoder;
                u32 remaining = samples;
                s16* left = decoder->leftBuffer + samples;
                s16* right = decoder->rightBuffer + samples;
                u64 played = current->samplesPlayed;
                for (;;) {
                    u32 count = GetAudioSample(movie, left, right, remaining, &statusC);
                    played += count;
                    if (statusC == 0) break;
                    if (statusC == 1) {
                        remaining -= count;
                        left += count;
                        if (right) right += count;
                        MovieDecoder* marks = movie->decoder;
                        marks->marks[marks->markWrite] = played;
                        if (++marks->markWrite >= 5) marks->markWrite = 0;
                        continue;
                    }
                    memset(left, 0, remaining * 2);
                    if (right) memset(right, 0, remaining * 2);
                    break;
                }
                current->samplesPlayed += samples;
            } else {
                MovieDecoder* current = movie->decoder;
                u32 remaining = samples;
                s16* left = decoder->leftBuffer + samples;
                s16* right = 0;
                u64 played = current->samplesPlayed;
                for (;;) {
                    u32 count = GetAudioSample(movie, left, right, remaining, &statusD);
                    played += count;
                    if (statusD == 0) break;
                    if (statusD == 1) {
                        remaining -= count;
                        left += count;
                        if (right) right += count;
                        MovieDecoder* marks = movie->decoder;
                        marks->marks[marks->markWrite] = played;
                        if (++marks->markWrite >= 5) marks->markWrite = 0;
                        continue;
                    }
                    memset(left, 0, remaining * 2);
                    if (right) memset(right, 0, remaining * 2);
                    break;
                }
                current->samplesPlayed += samples;
            }
            u32 bytes = samples * 2;
            DCFlushRange(decoder->leftBuffer + samples, bytes);
            sndStreamARAMUpdate(decoder->leftStream, samples, samples, 0, 0);
            if (decoder->channels == 2) {
                DCFlushRange(decoder->rightBuffer + samples, bytes);
                sndStreamARAMUpdate(decoder->rightStream, samples, samples, 0, 0);
            }
        }
        *(u64*)&decoder->reserved8260[0] += samples;
        return samples;
    }
    return 0;
}
