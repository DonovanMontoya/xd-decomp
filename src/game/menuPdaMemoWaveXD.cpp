#include <dolphin/types.h>
#include <dolphin/gx/GXVert.h>

#pragma peephole off

struct GSgfxVF;
enum GSgfxLayerID { GSgfxLayerID0 };

class GSgfxLayer {
public:
    u8 pad0[0xD34];
    u8 colorCount;
    u8 padD35[3];
    u32 colorMode;
    u8 padD3C[0x16A8 - 0xD3C];
    u32 flagsA;
    u32 flagsB;
    u8 pad16B0[0x1760 - 0x16B0];
    u32 flagsC;
    u32 flagsD;
    u8 pad1768[0x1998 - 0x1768];
    u32 primitive;
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};

struct GSvec {
    f32 x, y, z;
    GSvec() {}
    GSvec(const GSvec& o) {
        x = o.x;
        y = o.y;
        z = o.z;
    }
    GSvec& operator=(const GSvec& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
};

struct GSspline {
    s32 interpolation, dataType;
    u8 capacity, count, reservedA, timeCount;
    GSvec* values;
};

struct tagWINDOW_WORK {
    u8 unk0[0x1C];
    s32 layer;
};

struct tagSPRITE_WORK {
    u8 unk0[0x1C];
    s32 layer;
};

struct NakigoeDispWork {
    u8* data;
    f32 scale;
    u32 voice;
    f32 f0c;
    s32 count10;
    f32 f14;
    s32 count18;
    f32 f1c;
    f32 f20;
};

class pdaMemoNakigoe {
public:
    void SetNakigoe(long index);
    void SetSE(unsigned long id);
    long GetVocie(long index);
    void DispInit();
    void DispRequest(signed char* data, unsigned long voice);
    void NakigoeDispFunc(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite);
    void DispFuncSub(NakigoeDispWork* work, GSgfxLayerID layer);
    u8 NakigoeCheck();
    signed char* GetWaveDispDataAddress(long index);

    inline void Init() {
        for (int i = 0; i < 8; i++) {
            disp[i].data = 0;
        }
        index = 0;
        DispInit();
    }

    NakigoeDispWork disp[8];
    u32 index;
};

extern "C" {
void* __nw__FUl(unsigned long);
GSgfxLayer* GSgfxLayerFindByID(s32);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
void GSthreadSwitch(void);
void GSsndPlay(s32, s32, s32);
s32 GSsndGetStatus(u32);
GSspline* GSsplineCreate(s32, s32, u8);
void GSsplineAddControlVectorValue(GSspline*, GSvec*, f32);
void GSsplineFree(GSspline*);
u16 memoDataGetCount(s32);
void* menuPdaMemoListGetPokemonDataPointer(long);
s32 pokemonDataBiosGetVoice(void*);
signed char* pokemonNakigoeDataBiosGetDataAddress(void*);
}

static void _drawLine(GSgfxLayerID layer, GSvec* a, GSvec* b, float width);

pdaMemoNakigoe* _nakigoe;

extern "C" {

void menuPdaMemoWaveHook(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    if (_nakigoe != 0) {
        _nakigoe->NakigoeDispFunc(window, sprite);
    }
}

void menuPdaMemoWaveInit(void) {
    if (_nakigoe != 0) {
        _nakigoe->Init();
    }
}

void menuPdaMemoWave(long index) {
    if (_nakigoe == 0) {
        pdaMemoNakigoe* work = (pdaMemoNakigoe*)__nw__FUl(sizeof(pdaMemoNakigoe));
        if (work != 0) {
            work->Init();
        }
        _nakigoe = work;
    }
    _nakigoe->Init();
    _nakigoe->SetNakigoe(index);
    pdaMemoNakigoe* nakigoe = _nakigoe;
    for (;;) {
        if (!nakigoe->NakigoeCheck()) {
            break;
        }
        if ((GSinputButtonsPressed(1) & GSinputButtonsChanged(1)) & 0x100) {
            nakigoe->SetNakigoe(index);
        } else if ((GSinputButtonsPressed(1) & GSinputButtonsChanged(1)) & 0x200) {
            break;
        }
        GSthreadSwitch();
    }
}

}

void pdaMemoNakigoe::SetNakigoe(long index) {
    u32 raw = GetVocie(index);
    u16 voice = raw;
    SetSE(voice);
    DispRequest(GetWaveDispDataAddress(index), voice);
}

void pdaMemoNakigoe::SetSE(unsigned long id) {
    GSsndPlay(id, 0, 0);
}

long pdaMemoNakigoe::GetVocie(long index) {
    if (memoDataGetCount(0) != 0) {
        void* pokemon = menuPdaMemoListGetPokemonDataPointer(index);
        if (pokemon != 0) {
            return pokemonDataBiosGetVoice(pokemon);
        }
        return 0xFFFF;
    }
    return 0xFFFF;
}

void pdaMemoNakigoe::DispInit() {
    for (int i = 0; i < 8; i++) {
        DispRequest(0, 0);
    }
}

void pdaMemoNakigoe::DispRequest(signed char* data, unsigned long voice) {
    index++;
    if (index >= 8) {
        index = 0;
    }
    disp[index].data = (u8*)data;
    disp[index].voice = voice;
    disp[index].f0c = 0.0f;
    disp[index].f14 = 0.0f;
    disp[index].count10 = 0;
    disp[index].count18 = 1;
    disp[index].f1c = 255.0f;
    disp[index].f20 = 0.5f;
    for (int i = index - 1; i >= 0; i--) {
        disp[i].count10 = (s32)((f32)disp[i].count10 + disp[i].scale);
        disp[i].f20 += 0.2f;
    }
    for (u32 i = 7; i > index; i--) {
        disp[i].count10 = (s32)((f32)disp[i].count10 + disp[i].scale);
        disp[i].f20 += 0.2f;
    }
}

void pdaMemoNakigoe::NakigoeDispFunc(tagWINDOW_WORK* window, tagSPRITE_WORK* sprite) {
    for (int i = 0; i < 8; i++) {
        DispFuncSub(&disp[i], (GSgfxLayerID)window->layer);
    }
    for (int i = index - 1; i >= 0; i--) {
        disp[i].f1c -= 10.0f;
        if (disp[i].f1c < 0.0f) {
            disp[i].f1c = 0.0f;
        }
    }
    for (u32 i = 7; i > index; i--) {
        disp[i].f1c -= 10.0f;
        if (disp[i].f1c < 0.0f) {
            disp[i].f1c = 0.0f;
        }
    }
}

void pdaMemoNakigoe::DispFuncSub(NakigoeDispWork* work, GSgfxLayerID layer) {
    GSspline* spline;
    u8* data = work->data;
    if (data != 0) {
        int cnt = data[0] + 2;
        u8 n = cnt;
        work->scale = (f32)n;
        if (work->count18 < n) {
            work->count18++;
        } else if (work->count10 < n) {
            work->count10++;
        } else if (work->count10 < n + 30) {
            work->count10++;
            if (work->f14 < (f32)n) {
                work->f14 += work->f20;
            }
        } else if (work->f0c < (f32)n) {
            work->f0c += work->f20;
            if (work->f14 < (f32)n) {
                work->f14 += work->f20;
            }
        } else if (work->f14 < (f32)n) {
            work->f14 += work->f20;
        }
        spline = GSsplineCreate(3, 1, cnt);
        if (spline != 0) {
            GSvec v;
            GSvec p0;
            GSvec p1;
            f32 time;
            f32 step = 1.0f / (f32)(u8)cnt;
            v.x = 0.0f;
            v.y = 0.0f;
            v.z = work->f1c;
            f32 dx = work->scale;
            GSsplineAddControlVectorValue(spline, &v, 0.0f);
            time = step;
            v.x = v.x + (dx = 556.0f / dx);
            s32 i;
            for (i = 0; i < n - 2; i++) {
                f32 y = (f32)(s8)data[i + 1];
                v.y = y;
                v.y = -y;
                GSsplineAddControlVectorValue(spline, &v, time);
                time += step;
                v.x = v.x + dx;
            }
            v.y = 0.0f;
            v.x = 556.0f;
            GSsplineAddControlVectorValue(spline, &v, 1.0f);
            for (int j = 0; j < (s32)work->f0c; j++) {
                p0 = spline->values[j];
                p0.z = 0.0f;
                spline->values[j] = p0;
            }
            for (i = (s32)work->f0c; i < (s32)work->f14; i++) {
                p0 = spline->values[i];
                p0.z = (work->f1c / (f32)((s32)work->f14 - (s32)work->f0c)) * (f32)(i - (s32)work->f0c);
                spline->values[i] = p0;
            }
            for (i = 0; i < work->count18 - 1; i++) {
                p0 = spline->values[i];
                p1 = spline->values[i + 1];
                _drawLine(layer, &p0, &p1, work->scale);
            }
            GSsplineFree(spline);
        }
    }
}

u8 pdaMemoNakigoe::NakigoeCheck(){s32 i;u8 playing=0;for(i=0;i<8;i++)if(disp[i].data){switch(GSsndGetStatus(disp[i].voice)){case 0:case 1:break;case 2:playing=1;break;case 3:break;}}return playing;}

#define GXFifoNV (*(PPCWGPipe*)GXFIFO_ADDR)
static inline void dlPos(s16 x, s16 y) { GXFifoNV.s16 = x; GXFifoNV.s16 = y; }
static void _drawLine(GSgfxLayerID layerID, GSvec* a, GSvec* b, float width) {
    GSgfxLayer* layer = GSgfxLayerFindByID(layerID);
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0, 3, 0, 0, 1, 5, 0, 0, 0));
    layer->primitive = 0xA8;
    layer->colorCount = 0x18;
    layer->colorMode = 0;
    layer->flagsB |= 4;
    layer->flagsA |= 1;
    layer->flagsD |= 4;
    layer->flagsC |= 1;
    layer->beginSurface(2);
    dlPos(a->x, 0.5f * a->y + 105.0f);
    GXColor1u32((u8)(s32)a->z | 0x96E6F000);
    dlPos(b->x, 0.5f * b->y + 105.0f);
    GXColor1u32((u8)(s32)b->z | 0x96E6F000);
    layer->endSurface();
    layer->colorCount = 6;
    layer->colorMode = 0;
    layer->flagsB |= 4;
    layer->flagsA |= 1;
    layer->flagsD |= 4;
    layer->flagsC |= 1;
}

signed char* pdaMemoNakigoe::GetWaveDispDataAddress(long index) {
    s32 count = memoDataGetCount(0);
    if (count != 0) {
        void* pokemon = menuPdaMemoListGetPokemonDataPointer(index);
        if (pokemon != 0) {
            return pokemonNakigoeDataBiosGetDataAddress(pokemon);
        }
        return 0;
    }
    return 0;
}
