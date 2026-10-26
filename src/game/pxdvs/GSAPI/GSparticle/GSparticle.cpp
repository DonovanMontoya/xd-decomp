#include <global.h>

struct _GSparticleGen;
struct _GSparticleBank;
enum GenKind { GEN_PS = 0, GEN_BANK = 1 };

struct psGenX {
    u8 reserved0[0x15];
    u8 familyB;
    u8 reserved16[2];
    u16 familyA;
    u8 reserved1a[6];
    f32 x, y, z;
};

struct psCtl {
    u8 reserved0[0x10];
    u16 lifeA;
    u8 reserved12[5];
    u8 flag17;
    u8 reserved18[0x90 - 0x18];
    f32 rx, ry, rz;
    f32 sx, sy, sz;
};

struct peBankX {
    u8 isInfinite0;
    u8 kind1;
    u8 reserved2[2];
    u32 birth;
    psGenX *ps;
    f32 x, y, z;
    u8 reserved18[0x118 - 0x18];
    f32 qx, qy, qz, qw;
    f32 sx, sy, sz;
    u32 flags;
    u8 reserved138[0x160 - 0x138];
    void *camera;
};

struct psWrap {
    u8 flag0;
    u8 isFinite;
    u16 id;
    u32 birth;
    psCtl *ps;
    u8 reserved0c[0xc];
    f32 x, y, z;
    f32 sx, sy, sz;
};

struct _GSparticleGen {
    u8 isBank;
    u8 f1;
    bool f2;
    u8 pad3;
    s32 f4;
    s32 part;
    s32 fc;
    f32 px, py, pz;
    f32 rx, ry, rz;
    f32 sx, sy, sz;
    _GSparticleBank *parent;
    peBankX *bank;
};

struct _GSparticleBank {
    u8 reserved0;
    u8 kind;
    u8 loaded;
    u8 count;
    u8 disabled;
    u8 reserved5[3];
    void *file;
    _GSparticleGen *gens;
    void *camera;
};

extern "C" {
void GSmemFree(void *);
void GSgfxRenderWaitForDrawComplete__Fv(void);
void GSparticleDestroyGenerator(_GSparticleGen *, u8);
void GSparticleDestroyAllGenerators(_GSparticleBank *, u8);
void peBankFreeFile(void *);
void psSetParticleVisibility(psGenX *, u8);
void psSetRandomVelocityScaling(psGenX *, u8);
void psSetNodeScaling(psGenX *, u8);
void psSetTornadoScaling(psGenX *, u8, u8);
void psSetParticleTexScaling(psGenX *, u8);
void psSetOffsetRotationInLocal(psGenX *, u8, u8);
void psSetVelocityRotationInLocal(psGenX *, u8);
void psGeneratorSetCamera(psGenX *, void *);
u8 peBankIsInfinite(peBankX *);
void peBankStop(peBankX *);
void peBankStopLoop(peBankX *);
void peBankFree(peBankX *);
void psKillFamily(u16, u8);
s32 GSgfxPerfbarCPUEntry(s32);
void particleEnginePostUpdate(void);
u8 GScameraIsValid(u32);
void *GScameraGetActiveCamera(void);
void *memset(void *, int, unsigned long);
void particleEngineUpdate(u8, f32);
void psDispBeginFrame(void);
void psExecGenerator(int);
void *psGeneratorGetCamera(psGenX *);
void psInterpretParticles(int);
void psSetBillboardCamera(void *);
u32 psGetGeneratorChildMaxLife(psCtl *);
u32 psGetParticleChildCount(psCtl *);
void psSetGeneratorAngleRadiusScale(psCtl *, f32 *, u8);
f32 peBankGetLife(peBankX *);
u8 GSgfxVideoGetVsyncRate(void);
void EulerToQuat(void *, f32 *);
void psKillGenerator(void *);
void *GSmemAlloc(u32);
psCtl *psCreateGeneratorID(u8, u8, u32);
peBankX *peBankCreate(void *);
void peBankStart(peBankX *);
u32 GSgfxVideoGetVsyncCount(void);
void GSparticleDetachGeneratorFromGSpart(_GSparticleGen *, u8);
void GScameraLoadProjection(void *, void *);
void GScameraLoadActiveCameraMatrix(s32);
void particleEngineRender(void *);
s32 psDispHasRenderData(s32);
void psDispParticles(s32, s32, void *);
void psDispSetProjection(void *);
void psSetToken(s16);
void GSlogWrite(const char *, ...);
void *GSmemAllocClr(u32);
void DCFlushRange(void *, u32);
void *peBankLoadFile(void *, void *);
void psInitDataBank(s32, void *, void *, void *, s32);
void GSvecMakeFromQuat(void *, f32 *);
void psLinkChildGensToJObj(void *, void *);
void GSmodelSet60fpsAnimFlag(s32, s32);
void psUnlinkChildGensFromJObj(void *);
void psInitParticle(s32);
void psInitGenerator(s32);
s32 psInitAppSRT(s32, s32);
void psSetPointJObjNodup(void *, s32);
void particleEngineInit(void);
s32 GSmodelSearchModelList(void *);
s32 GSmodelGetLinkedGSparticleBank(void);
u8 GSmodelIsRootNullAdded(s32);
s32 GSpartGetJObjIndex(void *, void *);
s32 GSmodelGetPart(s32, s32 = 0);
s32 GSmodelGetGSparticleLinkAttachMode(s32);
s32 GSmodelGetVisibility(s32);
void GSpartFree(s32);
}

struct partX {
    u8 reserved0[2];
    u16 id;
    s32 model;
    void *jobj;
};
struct VecX3 { f32 x, y, z; };
struct QuatX4 { f32 x, y, z, w; };
extern VecX3 zeroVector;
extern QuatX4 zeroQuaternion;
extern VecX3 unitScaleVector;
extern "C" void GSparticleAttachGeneratorToGSpart(_GSparticleGen *, partX *, s32, s8, u8, u8);

struct _HSD_JObj {
    u8 reserved0[0xc];
    _HSD_JObj *parent;
    _HSD_JObj *child;
};
extern "C" void HSD_JObjSetSPtclCallback(void (*)(int, int, int, _HSD_JObj *));
extern "C" void HSD_JObjSetDPtclCallback(void (*)(int, int, int, _HSD_JObj *));
extern "C" void HSD_JObjSetPtclTargetCallback(void (*)(void *, s32));
extern "C" void GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(u8, void *, void *);
static void _particleJObjCallback(int, int, int, _HSD_JObj *);
struct ParticleRenderModule {
    void *callbacks[6];
    u32 id;
};

enum GSgfxLayerPass { PARTICLE_PASS_DEFAULT };

struct GSgfxCamX {
    u32 reserved0;
    u32 reserved4;
    void *obj;
};

struct GSgfxLayer {
    u8 reserved0[4];
    u32 flags4;
    u8 reserved8[0x28 - 8];
    s32 mode;
    u8 reserved2c[0xd44 - 0x2c];
    u8 flagD44;
    u8 flagD45;
    u8 reservedD46[0xd54 - 0xd46];
    u8 projection[0xd90 - 0xd54];
    s32 fieldD90;
    u8 reservedD94[0x16a6 - 0xd94];
    u8 flag16A6;
    u8 flag16A7;
    u32 f16A8;
    u8 reserved16AC[0x16b4 - 0x16ac];
    u32 f16B4;
    u32 f16B8;
    u8 reserved16BC[0x170c - 0x16bc];
    u32 f170C;
    u8 reserved1710[0x1760 - 0x1710];
    u32 f1760;
    u8 reserved1764[0x176c - 0x1764];
    u32 f176C;
    u32 f1770;
    u8 reserved1774[0x17c4 - 0x1774];
    u32 f17C4;
    void FlushState();
    void InvalidateState();
};

void *g_particle_cameras[4];
s32 g_particle_cameras_count;
static void *_particleBankStructList;
static s32 _particleBankStructCount;
static u8 _particlePALFrameCount;
static u8 _invalidateVtx;
static u8 _invalidateTex;

static inline s32 _findFreeGenerator(_GSparticleBank *bank) {
    _GSparticleGen *g = bank->gens;
    s32 i;
    for (i = 0; i < bank->count; i++, g++) {
        if (bank->loaded != g->isBank) {
            return -1;
        }
        if (g->bank == 0) {
            return i;
        }
    }
    return -1;
}

static inline void _setBankVisibility(peBankX *b, bool v) {
    if (b) {
        if (v) {
            b->flags |= 4;
        } else {
            b->flags &= ~4;
        }
    }
}

static inline u32 _generatorLife(_GSparticleGen *g) {
    peBankX *b = g->bank;
    if (b == 0) {
        return 0;
    }
    if (g->isBank != 0) {
        if (peBankIsInfinite(b) != 0) {
            return -1;
        }
        f32 rate = (f32)GSgfxVideoGetVsyncRate();
        f32 life = peBankGetLife(g->bank);
        return (u32)(life * rate);
    }
    if (((psWrap *)b)->isFinite == 1) {
        return -1;
    }
    return psGetGeneratorChildMaxLife(((psWrap *)b)->ps);
}

static inline u8 _isGeneratorAlive(_GSparticleGen *g) {
    peBankX *b = g->bank;
    if (b == 0) {
        return 0;
    }
    if (g->isBank != 0) {
        return _generatorLife(g) != 0;
    }
    if (((psWrap *)b)->isFinite != 0) {
        return 1;
    }
    if (psGetParticleChildCount(((psWrap *)b)->ps) != 0) {
        return 1;
    }
    return _generatorLife(g) != 0;
}

static void _particleRender(GSgfxLayer *layer, GSgfxLayerPass pass) {
    GSgfxCamX *cam = (GSgfxCamX *)GScameraGetActiveCamera();
    s32 type = 1;
    u32 wasOn = layer->flag16A7 != 0;
    if (cam == 0 || !GScameraIsValid((u32)cam)) {
        return;
    }
    {
        s32 perf = GSgfxPerfbarCPUEntry(0xff00ff);
        if (_invalidateVtx != 0) {
            layer->flags4 |= 0x8000000;
            _invalidateVtx = 0;
        }
        if (_invalidateTex != 0) {
            layer->flags4 |= 0x10000000;
            _invalidateTex = 0;
        }
        if (wasOn != 0) {
            layer->flag16A7 = 0;
            layer->f170C |= 0x40;
            layer->f17C4 |= 0x40;
            layer->f16A8 |= 0x40;
            layer->f1760 |= 0x40;
        }
        switch (layer->mode) {
        case 4:
            type = 2;
        case 2:
            if (pass == 1 && psDispHasRenderData(type) == 1) {
                u8 any = 0;
                void **p;
                GSgfxCamX *c;
                u32 i;
                layer->fieldD90 = 0;
                layer->f16B8 |= 4;
                layer->f16A8 |= 2;
                layer->f1770 |= 4;
                layer->f1760 |= 2;
                GScameraLoadProjection(cam, layer);
                layer->FlushState();
                psDispSetProjection(layer->projection);
                psSetBillboardCamera(cam->obj);
                psDispParticles(type, 1, 0);
                psDispParticles(type, 2, 0);
                layer->InvalidateState();
                for (i=0;i<(u32)g_particle_cameras_count;i++) {
                    c=(GSgfxCamX*)g_particle_cameras[i];
                    if (GScameraIsValid((u32)c)) {
                        any = 1;
                        GScameraLoadProjection(c, layer);
                        layer->FlushState();
                        psDispSetProjection(layer->projection);
                        psSetBillboardCamera(c->obj);
                        psDispParticles(type, 1, c);
                        psDispParticles(type, 2, c);
                        layer->InvalidateState();
                    }
                }
                layer->flagD44 = 0;
                layer->flagD45 = 0;
                layer->f16B4 |= 1;
                layer->f16A8 |= 1;
                layer->f176C |= 1;
                layer->f1760 |= 1;
                if (any) {
                    GScameraLoadActiveCameraMatrix(layer->mode);
                }
            }
        case 0:
        case 1:
        case 3:
        case 5:
            particleEngineRender(layer);
            break;
        }
        if (wasOn != 0) {
            layer->flag16A7 = 1;
            layer->f170C |= 0x40;
            layer->f17C4 |= 0x40;
            layer->f170C |= 0x200;
            layer->f17C4 |= 0x200;
            if (layer->flag16A6 != 0) {
                layer->f170C |= 0x100;
                layer->f17C4 |= 0x100;
            }
            layer->f16A8 |= 0x40;
            layer->f1760 |= 0x40;
        }
        GSgfxPerfbarCPUEntry(perf);
    }
}

static void _particlePostUpdate(f32) {
    u32 i;
    u32 j;
    s32 perf = GSgfxPerfbarCPUEntry(0x800080);
    for (i = 0; i < (u32)_particleBankStructCount; i++) {
        _GSparticleGen *g;
        _GSparticleBank *bank = &((_GSparticleBank *)_particleBankStructList)[i];
        if (bank->reserved0 == 1) {
            g = bank->gens;
            for (j = 0; j < bank->count; j++, g++) {
                if (g->bank != 0) {
                    if (!_isGeneratorAlive(g)) {
                        GSparticleDestroyGenerator(g, 1);
                    }
                }
            }
        }
    }
    particleEnginePostUpdate();
    GSgfxPerfbarCPUEntry(perf);
}

static inline void _genSetCamera(_GSparticleGen *g, void *cam) {
    peBankX *b = g->bank;
    if (b) {
        if (g->isBank) {
            if (b) {
                b->camera = cam;
            }
        } else {
            psGeneratorSetCamera(b->ps, cam);
        }
    }
}

static inline void *_genGetCamera(_GSparticleGen *g) {
    peBankX *b = g->bank;
    if (b == 0) {
        return 0;
    }
    if (g->isBank) {
        if (b) {
            return b->camera;
        }
        return 0;
    }
    return psGeneratorGetCamera(b->ps);
}

static void _particleUpdateAttachment(_GSparticleGen *g);

static void _particlePreUpdate(f32 dt) {
    static f32 sysdolRemain = 0.0f;
    u32 steps;
    u32 i;
    u32 j;
    s32 perf;
    perf = GSgfxPerfbarCPUEntry(0x800080);
    memset(g_particle_cameras, 0, 0x10);
    g_particle_cameras_count = 0;
    for (i = 0; i < (u32)_particleBankStructCount; i++) {
        _GSparticleBank *bank = &((_GSparticleBank *)_particleBankStructList)[i];
        if (bank->reserved0 == 1) {
            _GSparticleGen *g;
            if (bank->camera != 0 && !GScameraIsValid((u32)bank->camera)) {
                if (bank != 0 && bank->reserved0 != 0) {
                    u8 n;
                    bank->camera = 0;
                    n = bank->count;
                    g = bank->gens;
                    while (n--) {
                        if (g->bank != 0) {
                            _genSetCamera(g, 0);
                        }
                        g++;
                    }
                }
            }
            g = bank->gens;
            for (j = 0; j < bank->count; j++, g++) {
                if (g->bank != 0) {
                    void *cam;
                    _particleUpdateAttachment(g);
                    cam = _genGetCamera(g);
                    if (GScameraIsValid((u32)cam)) {
                        u8 found = 0;
                        u32 k;
                        for (k = 0; k < (u32)g_particle_cameras_count; k++) {
                            if (g_particle_cameras[k] == cam) {
                                found = 1;
                                break;
                            }
                        }
                        if (!found) {
                            g_particle_cameras[g_particle_cameras_count] = cam;
                            g_particle_cameras_count++;
                        }
                    } else {
                        _genSetCamera(g, 0);
                    }
                }
            }
        }
    }
    steps = (u32)dt;
    sysdolRemain = sysdolRemain + (dt - (f32)steps);
    if (sysdolRemain >= 1.0f) {
        u32 extra = (u32)sysdolRemain;
        steps += extra;
        sysdolRemain = sysdolRemain - (f32)extra;
    }
    if (GSgfxVideoGetVsyncRate() == 0x32) {
        _particlePALFrameCount++;
        if (_particlePALFrameCount >= 5) {
            steps++;
            _particlePALFrameCount = 0;
        }
    }
    {
        void *camera = GScameraGetActiveCamera();
        if (camera != 0 && GScameraIsValid((u32)camera)) {
            u32 n;
            psSetBillboardCamera(((psCtl **)camera)[2]);
            for (n = 0; n < steps; n++) {
                psInterpretParticles(0);
                psExecGenerator(0);
            }
        }
    }
    {
        u8 rate = GSgfxVideoGetVsyncRate();
        particleEngineUpdate(rate, dt / (f32)rate);
    }
    psDispBeginFrame();
    GSgfxPerfbarCPUEntry(perf);
}

extern "C" void GSparticleGeneratorSetCamera(_GSparticleGen *g, void *cam) {
    peBankX *b = g->bank;
    if (b) {
        if (g->isBank) {
            if (b) {
                b->camera = cam;
            }
        } else {
            psGeneratorSetCamera(b->ps, cam);
        }
    }
}

extern "C" void GSparticleFree(_GSparticleBank *bank) {
    GSgfxRenderWaitForDrawComplete__Fv();
    GSparticleDestroyAllGenerators(bank, 1);
    if (bank->gens) {
        GSmemFree(bank->gens);
        bank->gens = 0;
    }
    bank->gens = 0;
    bank->count = 0;
    if (bank->loaded) {
        peBankFreeFile(bank->file);
    }
    bank->reserved0 = 0;
}

extern "C" void GSparticleDestroyAllGenerators(_GSparticleBank *bank, u8 flag) {
    _GSparticleGen *g = bank->gens;
    for (u32 i = 0; i < bank->count; i++, g = (_GSparticleGen *)((u8 *)g + 0x3C)) {
        if (g->bank) {
            GSparticleDestroyGenerator(g, flag);
        }
    }
}

extern "C" void GSparticleStopGenerator(_GSparticleGen *g) {
    peBankX *b = g->bank;
    if (b && g->isBank) {
        if (peBankIsInfinite(b)) {
            peBankStopLoop(g->bank);
        } else {
            peBankStop(g->bank);
        }
    }
}

extern "C" void GSparticleSetBankVisibility(_GSparticleBank *bank, bool v) {
    _GSparticleGen *g = bank->gens;
    for (u32 i = 0; i < bank->count; i++, g = (_GSparticleGen *)((u8 *)g + 0x3C)) {
        peBankX *b = g->bank;
        if (b) {
            if (g->isBank) {
                _setBankVisibility(b, v);
            } else {
                psSetParticleVisibility(b->ps, v);
            }
        }
    }
}

extern "C" void GSparticleSetGeneratorVisibility(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        if (g->isBank) {
            _setBankVisibility(b, v);
        } else {
            psSetParticleVisibility(b->ps, v);
        }
    }
}

extern "C" void GSparticleSetRandomVelocityScaling(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetRandomVelocityScaling(b->ps, v);
            break;
        }
    }
}

extern "C" void GSparticleSetNodeScaling(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetNodeScaling(b->ps, v);
            break;
        }
    }
}

extern "C" void GSparticleSetTornadoScaling(_GSparticleGen *g, bool a, bool c) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetTornadoScaling(b->ps, a, c);
            break;
        }
    }
}

extern "C" void GSparticleSetParticleTextureScaling(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetParticleTexScaling(b->ps, v);
            break;
        }
    }
}

extern "C" void GSparticleSetOffsetRotationInLocal(_GSparticleGen *g, bool a, bool c) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetOffsetRotationInLocal(b->ps, a, c);
            break;
        }
    }
}

extern "C" void GSparticleSetVelocityRotationInLocal(_GSparticleGen *g, bool v) {
    peBankX *b = g->bank;
    if (b) {
        switch ((u32)g->isBank) {
        case 0:
            psSetVelocityRotationInLocal(b->ps, v);
            break;
        }
    }
}

extern "C" void GSparticleActivateBank(_GSparticleBank *bank) {
    bank->disabled = 0;
}

extern "C" void GSparticleDisactivateBank(_GSparticleBank *bank) {
    bank->disabled = 1;
}

extern "C" u8 GSparticleIsGeneratorAlive(_GSparticleGen *g) {
    return _isGeneratorAlive(g);
}

extern "C" u32 GSparticleGetGeneratorLife(_GSparticleGen *g) {
    return _generatorLife(g);
}

static inline void _clampScale(f32 *p) {
    f32 v = *p;
    f32 a = v > 0.0f ? v : -v;
    f32 e = 0.00001f;
    if (a < 0.00001f) {
        if (v < 0.0f) {
            e = -0.00001f;
        }
        *p = e;
    }
}

extern "C" void GSparticleSetGeneratorScale(_GSparticleGen *g, f32 *scale, u8 flag, u32 radius) {
    if (g->bank != 0) {
        if (g->part == 0) {
            _clampScale(&scale[0]);
            _clampScale(&scale[1]);
            _clampScale(&scale[2]);
            if (g->isBank != 0) {
                peBankX *bank = g->bank;
                if (bank != 0) {
                    bank->sx = scale[0];
                    bank->sy = scale[1];
                    bank->sz = scale[2];
                }
            } else {
                psWrap *w = (psWrap *)g->bank;
                w->sx = scale[0];
                w->sy = scale[1];
                w->sz = scale[2];
                w->ps->sx = scale[0];
                w->ps->sy = scale[1];
                w->ps->sz = scale[2];
            }
        } else {
            g->sx = scale[0];
            g->sy = scale[1];
            g->sz = scale[2];
        }
        if (g->isBank == 0 && flag == 1) {
            psSetGeneratorAngleRadiusScale(((psWrap *)g->bank)->ps, scale, radius);
        }
    }
}

extern "C" void GSparticleSetGeneratorRotation(_GSparticleGen *g, f32 *rot) {
    peBankX *b = g->bank;
    if (b != 0) {
        if (g->part == 0) {
            if (g->isBank != 0) {
                f32 quat[4];
                EulerToQuat(rot, quat);
                peBankX *bank = g->bank;
                if (bank != 0) {
                    bank->qx = quat[0];
                    bank->qy = quat[1];
                    bank->qz = quat[2];
                    bank->qw = quat[3];
                }
            } else {
                psWrap *w = (psWrap *)b;
                w->x = rot[0];
                w->y = rot[1];
                w->z = rot[2];
                w->ps->rx = rot[0];
                w->ps->ry = rot[1];
                w->ps->rz = rot[2];
            }
        } else {
            g->rx = rot[0];
            g->ry = rot[1];
            g->rz = rot[2];
        }
    }
}

extern "C" void GSparticleBankSetCamera(_GSparticleBank *bank, void *cam) {
    _GSparticleGen *g;
    u8 n;
    if (bank == 0 || bank->reserved0 == 0) return;
    bank->camera = cam;
    n = bank->count;
    g = bank->gens;
    while (n--) {
        if (g->bank != 0) {
            GSparticleGeneratorSetCamera(g, cam);
        }
        g++;
    }
}

extern "C" void GSparticleSetGeneratorPosition(_GSparticleGen *g, f32 *pos) {
    peBankX *b = g->bank;
    if (b == 0) {
        return;
    }
    if (g->part == 0) {
        if (g->isBank) {
            if (b != 0) {
                f32 *p = (f32 *)((u8 *)b + 0x10C);
                p[0] = pos[0];
                p[1] = pos[1];
                p[2] = pos[2];
            }
        } else {
            b->x = pos[0];
            b->y = pos[1];
            b->z = pos[2];
            b->ps->x = pos[0];
            b->ps->y = pos[1];
            b->ps->z = pos[2];
        }
    } else {
        g->px = pos[0];
        g->py = pos[1];
        g->pz = pos[2];
    }
}

extern "C" void GSparticleAttachGeneratorToGSpart(_GSparticleGen *g, partX *p, s32 mode, s8 f1, u8 reset, u8 link) {
    if (g->bank != 0 && g->part == 0 && mode != 0) {
        g->fc = (s32)p->model;
        g->f4 = p->id;
        if (reset == 1) {
            g->px = 0.0f;
            g->py = 0.0f;
            g->pz = 0.0f;
            g->rx = 0.0f;
            g->ry = 0.0f;
            g->rz = 0.0f;
            g->sx = 1.0f;
            g->sy = 1.0f;
            g->sz = 1.0f;
        } else if (g->isBank != 0) {
            peBankX *b = g->bank;
            f32 q[4];
            if (b != 0) {
                g->px = ((VecX3 *)((u8 *)b + 0x10C))->x;
                g->py = ((VecX3 *)((u8 *)b + 0x10C))->y;
                g->pz = ((VecX3 *)((u8 *)b + 0x10C))->z;
            } else {
                g->px = 0.0f;
                g->py = 0.0f;
                g->pz = 0.0f;
            }
            b = g->bank;
            if (b != 0) {
                q[0] = b->qx;
                q[1] = b->qy;
                q[2] = b->qz;
                q[3] = b->qw;
            } else {
                q[0] = 0.0f;
                q[1] = 0.0f;
                q[2] = 0.0f;
                q[3] = 1.0f;
            }
            GSvecMakeFromQuat(&g->rx, q);
            b = g->bank;
            if (b != 0) {
                g->sx = b->sx;
                g->sy = b->sy;
                g->sz = b->sz;
            } else {
                g->sx = 1.0f;
                g->sy = 1.0f;
                g->sz = 1.0f;
            }
        } else {
            psWrap *w = (psWrap *)g->bank;
            peBankX *b = g->bank;
            g->px = b->x;
            g->py = b->y;
            g->pz = b->z;
            w = (psWrap *)g->bank;
            g->rx = w->x;
            g->ry = w->y;
            g->rz = w->z;
            w = (psWrap *)g->bank;
            g->sx = w->sx;
            g->sy = w->sy;
            g->sz = w->sz;
        }
        if (g->isBank != 0) {
            peBankX *b = g->bank;
            if (b != 0) {
                ((VecX3 *)((u8 *)b + 0x10C))->x = zeroVector.x;
                ((VecX3 *)((u8 *)b + 0x10C))->y = zeroVector.y;
                ((VecX3 *)((u8 *)b + 0x10C))->z = zeroVector.z;
            }
            b = g->bank;
            if (b != 0) {
                b->qx = zeroQuaternion.x;
                b->qy = zeroQuaternion.y;
                b->qz = zeroQuaternion.z;
                b->qw = zeroQuaternion.w;
            }
            b = g->bank;
            if (b != 0) {
                b->sx = unitScaleVector.x;
                b->sy = unitScaleVector.y;
                b->sz = unitScaleVector.z;
            }
        } else {
            peBankX *b = g->bank;
            psWrap *w;
            b->x = 0.0f;
            b->y = 0.0f;
            b->z = 0.0f;
            w = (psWrap *)g->bank;
            w->x = 0.0f;
            w->y = 0.0f;
            w->z = 0.0f;
            w = (psWrap *)g->bank;
            w->sx = 1.0f;
            w->sy = 1.0f;
            w->sz = 1.0f;
            if (link != 0) {
                psLinkChildGensToJObj(((psWrap *)g->bank)->ps, p->jobj);
            }
        }
        g->part = mode;
        g->f1 = f1;
        g->f2 = 1;
    }
}

extern "C" void GSparticleDetachGeneratorFromGSpart(_GSparticleGen *g, u8 flag) {
    if (g->bank != 0 && g->part != 0) {
        GSmodelSet60fpsAnimFlag(g->fc, 0);
        g->fc = 0;
        g->f4 = 0;
        g->f2 = 0;
        g->f1 = 0;
        if (g->isBank == 0) {
            psUnlinkChildGensFromJObj(((psWrap *)g->bank)->ps);
        }
        g->part = 0;
        if (flag == 0) {
            GSparticleSetGeneratorPosition(g, &g->px);
            GSparticleSetGeneratorRotation(g, &g->rx);
            GSparticleSetGeneratorScale(g, &g->sx, 0, 0);
        }
    }
}

#pragma dont_inline on
extern "C" void GSparticleDestroyGenerator(_GSparticleGen *g, u8 flag) {
    if (g->bank != 0) {
        if (g->part != 0) {
            GSparticleDetachGeneratorFromGSpart(g, 0);
        }
        if (g->isBank) {
            peBankFree(g->bank);
            g->bank = 0;
        } else {
            if (flag == 1) {
                psGenX *ps = g->bank->ps;
                psKillFamily(ps->familyA, ps->familyB);
            }
            psKillGenerator(g->bank->ps);
            if (g->bank != 0) {
                GSmemFree(g->bank);
                g->bank = 0;
            }
        }
    }
}
#pragma dont_inline reset

static void _particleBankDestroyOldestGenerator(_GSparticleBank *bank);

static inline void peBankSetCamera(peBankX *b, void *camera) {
    if (b != 0) {
        b->camera = camera;
    }
}
extern "C" _GSparticleGen *GSparticleCreateGenerator(_GSparticleBank *bank, u32 id, u8 flag) {
    s32 bankIndex;
    s32 psIndex;
    peBankX* b;
    _GSparticleGen* g;
    if (bank->reserved0 == 0) {
        return 0;
    }
    if (bank->disabled != 0) {
        return 0;
    }
    if (bank->loaded != 0) {

        bankIndex = _findFreeGenerator(bank);
        if (bankIndex < 0) {
            return 0;
        }
        b = peBankCreate(bank->file);
        if (b == 0) {
            return 0;
        }
        g = &bank->gens[bankIndex];
        if (g->isBank == 0) {
            return 0;
        }
        peBankSetCamera(b, bank->camera);
        peBankStart(b);
        g->bank = b;
        _invalidateVtx = 1;
    } else {
        psIndex = _findFreeGenerator(bank);
        psWrap *w;
        if (psIndex < 0) {
            _particleBankDestroyOldestGenerator(bank);
            psIndex = _findFreeGenerator(bank);
            if (psIndex < 0) {
                return 0;
            }
        }
        w = (psWrap *)GSmemAlloc(0x30);
        if (w == 0) {
            return 0;
        }
        u8 type = 0;
        if (flag == 1) type = 1;
        w->ps = psCreateGeneratorID(type, bank->kind, id);
        if (w->ps == 0) {
            GSmemFree(w);
            return 0;
        }
        w->ps->flag17 = 1;
        psGeneratorSetCamera((psGenX *)w->ps, bank->camera);
        w->id = id;
        w->flag0 = flag;
        w->birth = GSgfxVideoGetVsyncCount();
        if (w->ps->lifeA == 0) {
            w->isFinite = 1;
        } else {
            w->isFinite = 0;
        }
        g = &bank->gens[psIndex];
        if (g->isBank != 0) {
            return 0;
        }
        g->bank = (peBankX *)w;
    }
    _invalidateTex = 1;
    g->part = 0;
    g->fc = 0;
    g->f4 = 0;
    g->f1 = 0;
    g->f2 = 0;
    g->parent = bank;
    return g;
}

static void _particleBankDestroyOldestGenerator(_GSparticleBank *bank) {
    s32 i;
    _GSparticleGen* g;
    _GSparticleGen* gens;
    peBankX* currentBank;
    u32 best;
    s32 oldest;
    gens=bank->gens;
    g=gens;
    best=-1;
    oldest=-1;
    for (i = 0; i < bank->count; i++, g++) {
        currentBank=g->bank;
        if (currentBank != 0) {
            u32 t = currentBank->birth;
            if (t < best) {
                best = t;
                oldest = i;
            }
        }
    }
    if (oldest != -1) {
        GSparticleDestroyGenerator(&gens[oldest], 1);
    }
}

struct GptHdr {
    s32 magic;
    u32 w4;
    u32 w8;
    u32 size;
    u32 w10;
};

static inline _GSparticleBank *_findFreeBank(void) {
    _GSparticleBank *b = (_GSparticleBank *)_particleBankStructList;
    s32 i;
    for (i = 0; i < (u32)_particleBankStructCount; i++, b++) {
        if (b->reserved0 == 0) {
            return b;
        }
    }
    return 0;
}

static inline bool _bankIdInUse(u8 id) {
    _GSparticleBank *b = (_GSparticleBank *)_particleBankStructList;
    s32 i;
    for (i = 0; i < (u32)_particleBankStructCount; i++, b++) {
        if (b->kind == id) {
            return true;
        }
    }
    return false;
}

extern "C" void GSparticleInit(u32 count) {
    ParticleRenderModule module = {{0, (void *)_particlePreUpdate, (void *)_particleRender, 0, (void *)_particlePostUpdate, 0}, 0xb29a48e1};
    memset(g_particle_cameras, 0, 0x10);
    _particleBankStructCount = count;
    g_particle_cameras_count = 0;
    _particleBankStructList = GSmemAlloc(count * 0x14);
    if (_particleBankStructList) {
        u32 i;
        for (i = 0; i < (u32)_particleBankStructCount; i++) {
            ((_GSparticleBank *)_particleBankStructList)[i].reserved0 = 0;
        }
        psSetToken(0);
        psInitParticle(0);
        psInitGenerator(0);
        psInitAppSRT(0, 0x74);
        HSD_JObjSetSPtclCallback(_particleJObjCallback);
        HSD_JObjSetDPtclCallback(_particleJObjCallback);
        HSD_JObjSetPtclTargetCallback(psSetPointJObjNodup);
        particleEngineInit();
        GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(0x40, &module, 0);
    }
}

// Stripped from the DOL; its string still occupies .rodata.
extern "C" void GSparticleSetGeneratorZDraw(_GSparticleGen *, u8) {
    GSlogWrite("GSparticle: changing the Z draw flag of a generator currently has no effect\n");
}


static inline u8 _findBankId(void) {
 u8 id;
 for(id=0;id<0x40;++id) {if(!_bankIdInUse(id))return id;}
 return 0xff;
}

extern "C" _GSparticleBank *GSparticleLoad(void *file) {
    GptHdr *hdr = (GptHdr *)file;
    u8 id;
    _GSparticleBank *bank = _findFreeBank();
    if (bank == 0) {
        return 0;
    }
    id=_findBankId();
    if (id == 0xff) {
        return 0;
    }
    bank->camera = 0;
    bank->gens = 0;
    bank->disabled = 0;
    if (hdr->magic == 0x1F056DA) {
        if (hdr->w4 != 0x30002) {
            return 0;
        }
        bank->loaded = 1;
        bank->count = 0x10;
        bank->gens = (_GSparticleGen *)GSmemAllocClr(0x3c0);
        if (bank->gens == 0) {
            return 0;
        }
        bank->gens[0].isBank = 1;
        bank->gens[1].isBank = 1;
        bank->gens[2].isBank = 1;
        bank->gens[3].isBank = 1;
        bank->gens[4].isBank = 1;
        bank->gens[5].isBank = 1;
        bank->gens[6].isBank = 1;
        bank->gens[7].isBank = 1;
        bank->gens[8].isBank = 1;
        bank->gens[9].isBank = 1;
        bank->gens[10].isBank = 1;
        bank->gens[11].isBank = 1;
        bank->gens[12].isBank = 1;
        bank->gens[13].isBank = 1;
        bank->gens[14].isBank = 1;
        _GSparticleGen* gens=bank->gens;gens[15].isBank = 1;
        bank->file = peBankLoadFile(file, gens);
        if (bank->file == 0) {
            goto fail;
        }
    } else {
        bank->loaded = 0;
        bank->count = 0x40;
        bank->gens = (_GSparticleGen *)GSmemAllocClr(0xf00);
        if (bank->gens == 0) {
            return 0;
        }
        switch (hdr->magic) {
        case 0x47505430:
            GSlogWrite("GSparticle: ***************************************************************************\n");
            GSlogWrite("GSparticle: ************* version 0 .gpt files are no longer supported ****************\n");
            GSlogWrite("GSparticle: ***************************************************************************\n");
            goto fail;
        default:
            GSlogWrite("GSparticle: unknown version\n");
            goto fail;
        case 0x47505431:
            hdr->w4 += (u32)file;
            hdr->w8 += (u32)file;
            hdr->w10 += (u32)file;
            if ((s32)*(u16 *)hdr->w4 != 0x43) {
                GSlogWrite("GSparticle: version mismatch between system(%d) and ptcl-file(%d)", 0x43, *(u16 *)hdr->w4);
                goto fail;
            }
            bank->file = file;
            DCFlushRange((void *)hdr->w8, (hdr->size + 0x1f) & ~0x1f);
            psInitDataBank(id, (void *)hdr->w4, (void *)hdr->w8, (void *)hdr->w10, 0);
            break;
        }
    }
    bank->reserved0 = 1;
    bank->kind = id;
    return bank;
fail:
    if (bank->gens != 0) {
        GSmemFree(bank->gens);
        bank->gens = 0;
    }
    return 0;
}

static inline _HSD_JObj *_jobjParent(_HSD_JObj *j) {
    if (j == 0) {
        return 0;
    }
    return j->parent;
}

static void _particleJObjCallback(int, int, int id, _HSD_JObj *jobj) {
    _HSD_JObj *root = jobj;
    s32 model;
    s32 bank;
    s32 part;
    u32 idx;
    _GSparticleGen *g;
    while (_jobjParent(root) != 0) {
        root = _jobjParent(root);
    }
    model = GSmodelSearchModelList(root);
    if (model != 0) {
        bank = GSmodelGetLinkedGSparticleBank();
        if (bank != 0) {
            if (GSmodelIsRootNullAdded(model)) {
                root = root->child;
            }
            idx = GSpartGetJObjIndex(root, jobj);
            if (idx + 0x10000 != 0xffff) {
                part = GSmodelGetPart(model, idx);
                if (part != 0) {
                    g = GSparticleCreateGenerator((_GSparticleBank *)bank, id, 0);
                    if (g != 0) {
                        peBankX *b = g->bank;
                        s32 vis;
                        if (b != 0 && g->isBank == 0) {
                            psSetParticleTexScaling(b->ps, 1);
                        }
                        b = g->bank;
                        if (b != 0 && g->isBank == 0) {
                            psSetRandomVelocityScaling(b->ps, 1);
                        }
                        GSparticleAttachGeneratorToGSpart(g, (partX *)part, GSmodelGetGSparticleLinkAttachMode(model), 0, 1, 0);
                        vis = GSmodelGetVisibility(model);
                        b = g->bank;
                        if (b != 0) {
                            if (g->isBank != 0) {
                                if (b != 0) {
                                    if ((u8)vis != 0) {
                                        b->flags |= 4;
                                    } else {
                                        b->flags &= ~4;
                                    }
                                }
                            } else {
                                psSetParticleVisibility(b->ps, vis);
                            }
                        }
                    }
                    GSpartFree(part);
                }
            }
        }
    }
}

#define PARTICLE_FIELD(base, type, offset) (*(type*)((u8*)(base) + (offset)))
extern "C" {
void GSpartGetTransform(s32, void*, void*, void*);
void GSvecTransformQuat(void*, void*, void*);
void PSVECAdd(void*, void*, void*);
static inline void clampParticleScale(f32* field) {
    f32 value = *field;
    f32 magnitude;
    f32 bound;
    if (value > 0.0f) magnitude = value;
    else magnitude = -value;
    bound = 0.00001f;
    if (magnitude < 0.00001f) {
        if (value < 0.0f) bound = -0.00001f;
        *field = bound;
    }
}
#pragma opt_common_subs off
#pragma opt_loop_invariants off
static void _particleUpdateAttachment(_GSparticleGen *arg0) {
    VecX3 position;
    VecX3 rotation;
    VecX3 scale;
    QuatX4 quaternion;
    VecX3 offset;
    QuatX4 q48;
    QuatX4 q38;
    QuatX4 q28;
    QuatX4 q18;
    QuatX4 q8;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 var_f0;
    f32 var_f0_10;
    f32 var_f0_11;
    f32 var_f0_12;
    f32 var_f0_13;
    f32 var_f0_14;
    f32 var_f0_15;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f0_5;
    f32 var_f0_6;
    f32 var_f0_7;
    f32 var_f0_8;
    f32 var_f0_9;
    f32 var_f1;
    f32 var_f1_10;
    f32 var_f1_11;
    f32 var_f1_12;
    f32 var_f1_13;
    f32 var_f1_14;
    f32 var_f1_15;
    f32 var_f1_2;
    f32 var_f1_3;
    f32 var_f1_4;
    f32 var_f1_5;
    f32 var_f1_6;
    f32 var_f1_7;
    f32 var_f1_8;
    f32 var_f1_9;
    s32 temp_r0;
    s32 temp_r30;
    void *temp_r3;
    void *temp_r3_10;
    void *temp_r3_11;
    void *temp_r3_12;
    void *temp_r3_13;
    void *temp_r3_14;
    void *temp_r3_15;
    void *temp_r3_2;
    void *temp_r3_3;
    void *temp_r3_4;
    void *temp_r3_5;
    void *temp_r3_6;
    void *temp_r3_7;
    void *temp_r3_8;
    void *temp_r3_9;
    void *temp_r4;
    void *temp_r4_10;
    void *temp_r4_11;
    void *temp_r4_12;
    void *temp_r4_13;
    void *temp_r4_14;
    void *temp_r4_15;
    void *temp_r4_2;
    void *temp_r4_3;
    void *temp_r4_4;
    void *temp_r4_5;
    void *temp_r4_6;
    void *temp_r4_7;
    void *temp_r4_8;
    void *temp_r4_9;

    if (((s32) PARTICLE_FIELD(arg0, s32, 0x8) != 0) && ((u8) PARTICLE_FIELD(arg0, u8, 0x2) != 0)) {
        temp_r30 = GSmodelGetPart(PARTICLE_FIELD(arg0, s32, 0xC), PARTICLE_FIELD(arg0, s32, 0x4));
        GSpartGetTransform(temp_r30, &position.x, &rotation.x, &scale.x);
        GSpartFree(temp_r30);
        EulerToQuat(&rotation.x, &quaternion.x);
        GSvecTransformQuat(&offset.x, &quaternion.x, (u8*)arg0 + 0x10);
        PSVECAdd(&position.x, &offset.x, &position.x);
        PSVECAdd(&rotation.x, (u8*)arg0 + 0x1C, &rotation.x);
        scale.x *= PARTICLE_FIELD(arg0, f32, 0x28);
        scale.y *= PARTICLE_FIELD(arg0, f32, 0x2C);
        scale.z *= PARTICLE_FIELD(arg0, f32, 0x30);
        if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
            temp_r3 = PARTICLE_FIELD(arg0, void*, 0x38);
            if (temp_r3 != NULL) {
                PARTICLE_FIELD(temp_r3, f32, 0x10C) = (f32) PARTICLE_FIELD(arg0, f32, 0x10);
                PARTICLE_FIELD(temp_r3, f32, 0x110) = (f32) PARTICLE_FIELD(arg0, f32, 0x14);
                PARTICLE_FIELD(temp_r3, f32, 0x114) = (f32) PARTICLE_FIELD(arg0, f32, 0x18);
            }
        } else {
            temp_r4 = PARTICLE_FIELD(arg0, void*, 0x38);
            PARTICLE_FIELD(temp_r4, f32, 0xC) = (f32) PARTICLE_FIELD(arg0, f32, 0x10);
            PARTICLE_FIELD(temp_r4, f32, 0x10) = (f32) PARTICLE_FIELD(arg0, f32, 0x14);
            PARTICLE_FIELD(temp_r4, f32, 0x14) = (f32) PARTICLE_FIELD(arg0, f32, 0x18);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4, void*, 8), f32, 0x20) = (f32) PARTICLE_FIELD(arg0, f32, 0x10);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4, void*, 8), f32, 0x24) = (f32) PARTICLE_FIELD(arg0, f32, 0x14);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4, void*, 8), f32, 0x28) = (f32) PARTICLE_FIELD(arg0, f32, 0x18);
        }
        if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
            EulerToQuat((u8*)arg0 + 0x1C, &q48.x);
            temp_r3_2 = PARTICLE_FIELD(arg0, void*, 0x38);
            if (temp_r3_2 != NULL) {
                PARTICLE_FIELD(temp_r3_2, f32, 0x118) = q48.x;
                PARTICLE_FIELD(temp_r3_2, f32, 0x11C) = q48.y;
                PARTICLE_FIELD(temp_r3_2, f32, 0x120) = q48.z;
                PARTICLE_FIELD(temp_r3_2, f32, 0x124) = q48.w;
            }
        } else {
            temp_r4_2 = PARTICLE_FIELD(arg0, void*, 0x38);
            PARTICLE_FIELD(temp_r4_2, f32, 0x18) = (f32) PARTICLE_FIELD(arg0, f32, 0x1C);
            PARTICLE_FIELD(temp_r4_2, f32, 0x1C) = (f32) PARTICLE_FIELD(arg0, f32, 0x20);
            PARTICLE_FIELD(temp_r4_2, f32, 0x20) = (f32) PARTICLE_FIELD(arg0, f32, 0x24);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_2, void*, 8), f32, 0x90) = (f32) PARTICLE_FIELD(arg0, f32, 0x1C);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_2, void*, 8), f32, 0x94) = (f32) PARTICLE_FIELD(arg0, f32, 0x20);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_2, void*, 8), f32, 0x98) = (f32) PARTICLE_FIELD(arg0, f32, 0x24);
        }
        clampParticleScale(&PARTICLE_FIELD(arg0, f32, 0x28));
        clampParticleScale(&PARTICLE_FIELD(arg0, f32, 0x2C));
        clampParticleScale(&PARTICLE_FIELD(arg0, f32, 0x30));
        if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
            temp_r3_3 = PARTICLE_FIELD(arg0, void*, 0x38);
            if (temp_r3_3 != NULL) {
                PARTICLE_FIELD(temp_r3_3, f32, 0x128) = (f32) PARTICLE_FIELD(arg0, f32, 0x28);
                PARTICLE_FIELD(temp_r3_3, f32, 0x12C) = (f32) PARTICLE_FIELD(arg0, f32, 0x2C);
                PARTICLE_FIELD(temp_r3_3, f32, 0x130) = (f32) PARTICLE_FIELD(arg0, f32, 0x30);
            }
        } else {
            temp_r4_3 = PARTICLE_FIELD(arg0, void*, 0x38);
            PARTICLE_FIELD(temp_r4_3, f32, 0x24) = (f32) PARTICLE_FIELD(arg0, f32, 0x28);
            PARTICLE_FIELD(temp_r4_3, f32, 0x28) = (f32) PARTICLE_FIELD(arg0, f32, 0x2C);
            PARTICLE_FIELD(temp_r4_3, f32, 0x2C) = (f32) PARTICLE_FIELD(arg0, f32, 0x30);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_3, void*, 8), f32, 0x9C) = (f32) PARTICLE_FIELD(arg0, f32, 0x28);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_3, void*, 8), f32, 0xA0) = (f32) PARTICLE_FIELD(arg0, f32, 0x2C);
            PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_3, void*, 8), f32, 0xA4) = (f32) PARTICLE_FIELD(arg0, f32, 0x30);
        }
        temp_r0 = PARTICLE_FIELD(arg0, s32, 0x8);
        {
            switch (temp_r0) {
            case 1:
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    temp_r3_4 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_4 != NULL) {
                        PARTICLE_FIELD(temp_r3_4, f32, 0x10C) = position.x;
                        PARTICLE_FIELD(temp_r3_4, f32, 0x110) = position.y;
                        PARTICLE_FIELD(temp_r3_4, f32, 0x114) = position.z;
                    }
                } else {
                    temp_r4_4 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_4, f32, 0xC) = position.x;
                    PARTICLE_FIELD(temp_r4_4, f32, 0x10) = position.y;
                    PARTICLE_FIELD(temp_r4_4, f32, 0x14) = position.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_4, void*, 8), f32, 0x20) = position.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_4, void*, 8), f32, 0x24) = position.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_4, void*, 8), f32, 0x28) = position.z;
                }
                break;
            case 2:
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    EulerToQuat(&rotation.x, &q38.x);
                    temp_r3_5 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_5 != NULL) {
                        PARTICLE_FIELD(temp_r3_5, f32, 0x118) = q38.x;
                        PARTICLE_FIELD(temp_r3_5, f32, 0x11C) = q38.y;
                        PARTICLE_FIELD(temp_r3_5, f32, 0x120) = q38.z;
                        PARTICLE_FIELD(temp_r3_5, f32, 0x124) = q38.w;
                    }
                } else {
                    temp_r4_5 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_5, f32, 0x18) = rotation.x;
                    PARTICLE_FIELD(temp_r4_5, f32, 0x1C) = rotation.y;
                    PARTICLE_FIELD(temp_r4_5, f32, 0x20) = rotation.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_5, void*, 8), f32, 0x90) = rotation.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_5, void*, 8), f32, 0x94) = rotation.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_5, void*, 8), f32, 0x98) = rotation.z;
                }
                break;
            case 3:
                clampParticleScale(&scale.x);
                clampParticleScale(&scale.y);
                clampParticleScale(&scale.z);
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    temp_r3_6 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_6 != NULL) {
                        PARTICLE_FIELD(temp_r3_6, f32, 0x128) = scale.x;
                        PARTICLE_FIELD(temp_r3_6, f32, 0x12C) = scale.y;
                        PARTICLE_FIELD(temp_r3_6, f32, 0x130) = scale.z;
                    }
                } else {
                    temp_r4_6 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_6, f32, 0x24) = scale.x;
                    PARTICLE_FIELD(temp_r4_6, f32, 0x28) = scale.y;
                    PARTICLE_FIELD(temp_r4_6, f32, 0x2C) = scale.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_6, void*, 8), f32, 0x9C) = scale.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_6, void*, 8), f32, 0xA0) = scale.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_6, void*, 8), f32, 0xA4) = scale.z;
                }
                break;
            case 4:
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    temp_r3_7 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_7 != NULL) {
                        PARTICLE_FIELD(temp_r3_7, f32, 0x10C) = position.x;
                        PARTICLE_FIELD(temp_r3_7, f32, 0x110) = position.y;
                        PARTICLE_FIELD(temp_r3_7, f32, 0x114) = position.z;
                    }
                } else {
                    temp_r4_7 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_7, f32, 0xC) = position.x;
                    PARTICLE_FIELD(temp_r4_7, f32, 0x10) = position.y;
                    PARTICLE_FIELD(temp_r4_7, f32, 0x14) = position.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_7, void*, 8), f32, 0x20) = position.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_7, void*, 8), f32, 0x24) = position.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_7, void*, 8), f32, 0x28) = position.z;
                }
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    EulerToQuat(&rotation.x, &q28.x);
                    temp_r3_8 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_8 != NULL) {
                        PARTICLE_FIELD(temp_r3_8, f32, 0x118) = q28.x;
                        PARTICLE_FIELD(temp_r3_8, f32, 0x11C) = q28.y;
                        PARTICLE_FIELD(temp_r3_8, f32, 0x120) = q28.z;
                        PARTICLE_FIELD(temp_r3_8, f32, 0x124) = q28.w;
                    }
                } else {
                    temp_r4_8 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_8, f32, 0x18) = rotation.x;
                    PARTICLE_FIELD(temp_r4_8, f32, 0x1C) = rotation.y;
                    PARTICLE_FIELD(temp_r4_8, f32, 0x20) = rotation.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_8, void*, 8), f32, 0x90) = rotation.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_8, void*, 8), f32, 0x94) = rotation.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_8, void*, 8), f32, 0x98) = rotation.z;
                }
                break;
            case 5:
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    EulerToQuat(&rotation.x, &q18.x);
                    temp_r3_9 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_9 != NULL) {
                        PARTICLE_FIELD(temp_r3_9, f32, 0x118) = q18.x;
                        PARTICLE_FIELD(temp_r3_9, f32, 0x11C) = q18.y;
                        PARTICLE_FIELD(temp_r3_9, f32, 0x120) = q18.z;
                        PARTICLE_FIELD(temp_r3_9, f32, 0x124) = q18.w;
                    }
                } else {
                    temp_r4_9 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_9, f32, 0x18) = rotation.x;
                    PARTICLE_FIELD(temp_r4_9, f32, 0x1C) = rotation.y;
                    PARTICLE_FIELD(temp_r4_9, f32, 0x20) = rotation.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_9, void*, 8), f32, 0x90) = rotation.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_9, void*, 8), f32, 0x94) = rotation.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_9, void*, 8), f32, 0x98) = rotation.z;
                }
                clampParticleScale(&scale.x);
                clampParticleScale(&scale.y);
                clampParticleScale(&scale.z);
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    temp_r3_10 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_10 != NULL) {
                        PARTICLE_FIELD(temp_r3_10, f32, 0x128) = scale.x;
                        PARTICLE_FIELD(temp_r3_10, f32, 0x12C) = scale.y;
                        PARTICLE_FIELD(temp_r3_10, f32, 0x130) = scale.z;
                    }
                } else {
                    temp_r4_10 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_10, f32, 0x24) = scale.x;
                    PARTICLE_FIELD(temp_r4_10, f32, 0x28) = scale.y;
                    PARTICLE_FIELD(temp_r4_10, f32, 0x2C) = scale.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_10, void*, 8), f32, 0x9C) = scale.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_10, void*, 8), f32, 0xA0) = scale.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_10, void*, 8), f32, 0xA4) = scale.z;
                }
                break;
            case 6:
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    temp_r3_11 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_11 != NULL) {
                        PARTICLE_FIELD(temp_r3_11, f32, 0x10C) = position.x;
                        PARTICLE_FIELD(temp_r3_11, f32, 0x110) = position.y;
                        PARTICLE_FIELD(temp_r3_11, f32, 0x114) = position.z;
                    }
                } else {
                    temp_r4_11 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_11, f32, 0xC) = position.x;
                    PARTICLE_FIELD(temp_r4_11, f32, 0x10) = position.y;
                    PARTICLE_FIELD(temp_r4_11, f32, 0x14) = position.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_11, void*, 8), f32, 0x20) = position.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_11, void*, 8), f32, 0x24) = position.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_11, void*, 8), f32, 0x28) = position.z;
                }
                clampParticleScale(&scale.x);
                clampParticleScale(&scale.y);
                clampParticleScale(&scale.z);
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    temp_r3_12 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_12 != NULL) {
                        PARTICLE_FIELD(temp_r3_12, f32, 0x128) = scale.x;
                        PARTICLE_FIELD(temp_r3_12, f32, 0x12C) = scale.y;
                        PARTICLE_FIELD(temp_r3_12, f32, 0x130) = scale.z;
                    }
                } else {
                    temp_r4_12 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_12, f32, 0x24) = scale.x;
                    PARTICLE_FIELD(temp_r4_12, f32, 0x28) = scale.y;
                    PARTICLE_FIELD(temp_r4_12, f32, 0x2C) = scale.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_12, void*, 8), f32, 0x9C) = scale.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_12, void*, 8), f32, 0xA0) = scale.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_12, void*, 8), f32, 0xA4) = scale.z;
                }
                break;
            case 7:
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    temp_r3_13 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_13 != NULL) {
                        PARTICLE_FIELD(temp_r3_13, f32, 0x10C) = position.x;
                        PARTICLE_FIELD(temp_r3_13, f32, 0x110) = position.y;
                        PARTICLE_FIELD(temp_r3_13, f32, 0x114) = position.z;
                    }
                } else {
                    temp_r4_13 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_13, f32, 0xC) = position.x;
                    PARTICLE_FIELD(temp_r4_13, f32, 0x10) = position.y;
                    PARTICLE_FIELD(temp_r4_13, f32, 0x14) = position.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_13, void*, 8), f32, 0x20) = position.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_13, void*, 8), f32, 0x24) = position.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_13, void*, 8), f32, 0x28) = position.z;
                }
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    EulerToQuat(&rotation.x, &q8.x);
                    temp_r3_14 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_14 != NULL) {
                        PARTICLE_FIELD(temp_r3_14, f32, 0x118) = q8.x;
                        PARTICLE_FIELD(temp_r3_14, f32, 0x11C) = q8.y;
                        PARTICLE_FIELD(temp_r3_14, f32, 0x120) = q8.z;
                        PARTICLE_FIELD(temp_r3_14, f32, 0x124) = q8.w;
                    }
                } else {
                    temp_r4_14 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_14, f32, 0x18) = rotation.x;
                    PARTICLE_FIELD(temp_r4_14, f32, 0x1C) = rotation.y;
                    PARTICLE_FIELD(temp_r4_14, f32, 0x20) = rotation.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_14, void*, 8), f32, 0x90) = rotation.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_14, void*, 8), f32, 0x94) = rotation.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_14, void*, 8), f32, 0x98) = rotation.z;
                }
                clampParticleScale(&scale.x);
                clampParticleScale(&scale.y);
                clampParticleScale(&scale.z);
                if ((u8) PARTICLE_FIELD(arg0, u8, 0x0) != 0) {
                    temp_r3_15 = PARTICLE_FIELD(arg0, void*, 0x38);
                    if (temp_r3_15 != NULL) {
                        PARTICLE_FIELD(temp_r3_15, f32, 0x128) = scale.x;
                        PARTICLE_FIELD(temp_r3_15, f32, 0x12C) = scale.y;
                        PARTICLE_FIELD(temp_r3_15, f32, 0x130) = scale.z;
                    }
                } else {
                    temp_r4_15 = PARTICLE_FIELD(arg0, void*, 0x38);
                    PARTICLE_FIELD(temp_r4_15, f32, 0x24) = scale.x;
                    PARTICLE_FIELD(temp_r4_15, f32, 0x28) = scale.y;
                    PARTICLE_FIELD(temp_r4_15, f32, 0x2C) = scale.z;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_15, void*, 8), f32, 0x9C) = scale.x;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_15, void*, 8), f32, 0xA0) = scale.y;
                    PARTICLE_FIELD(PARTICLE_FIELD(temp_r4_15, void*, 8), f32, 0xA4) = scale.z;
                }
                break;
            }
        }
        arg0->f2 = arg0->f1 == 0;
    }
}

}
#pragma opt_loop_invariants reset
#pragma opt_common_subs reset
#undef PARTICLE_FIELD
