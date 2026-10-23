#include <game/pxdvs/GSAPI/GSparticle/peBankPrivate.hpp>
#include <dolphin/os/OSFastCast.h>

extern "C" {
ParticleBankState* g_currentBank;
void* g_currentBound;
u16 g_bank_token;
_EmitParams* g_emitParams;
u16 g_maxEmitParams;
ParticleBankState* g_emitParamsBank;
}
extern "C" u8 peBankIsInfinite(ParticleBankState* bank) {
    if (!bank) return 0;
    if (!(bank->flags & 1)) return 0;
    return bank->node.emitter->flags & 1;
}
extern "C" f32 peBankGetLife(ParticleBankState* bank) {
    if (!bank) return 0.0f;
    if (bank->flags & 1) return bank->node.life;
    return 0.0f;
}
extern "C" void peBankStopLoop(ParticleBankState* bank) {
    if (peBankIsInfinite(bank)) bank->node.SetLastLoop();
}
extern "C" void peBankStop(ParticleBankState* bank) {
    if (bank && (bank->flags & 1)) {
        g_currentBank = bank;
        g_currentBound = (bank->flags & 0x10) ? bank->bound : 0;
        bank->node.Stop(bank->data->emitter);
        bank->flags = 0;
    }
}
extern "C" void peBankUpdate(ParticleBankState* bank, f32 delta) {
    if (!bank) return;
    if (!(bank->flags & 1)) return;
    if (bank->flags & 2) return;
    if (bank->token && GSgfxTokenCleared(bank->token)) bank->token = 0;
    if (!particleEnginePrepareUpdate(bank->camera)) return;
    g_currentBank = bank;
    if (bank->flags & 0x10) {
        g_currentBound = bank->bound;
        GSboundReset(g_currentBound);
        GSboundAlwaysInView(g_currentBound, 0);
    } else g_currentBound = 0;
    f32 alive = bank->node.Update(0, bank->data->emitter, delta);
    if (alive <= 0.0f) {
        bank->node.Stop(bank->data->emitter);
        bank->flags = 0;
    } else {
        if (!g_currentBound || GSboundIsInViewFast(g_currentBound)) bank->flags |= 8;
        else bank->flags &= ~8;
    }
}

extern "C" {
extern u16 g_bank_token;
extern void* g_CameraMatrix;
void push__16GSgfxMatrixStackFP5GSmtx(void*,void*);
void pop__16GSgfxMatrixStackFv(void*);
void GSboundDraw__FP7GSboundP10GSgfxLayer(void*,ParticleLayer*);
}
#pragma opt_dead_assignments off
extern "C" void peBankRender(ParticleBankState* bank) {
    if (!bank) return;
    if (!(bank->flags & 1)) return;
    if (!(bank->flags & 4)) return;
    if (!(bank->flags & 8)) return;
    u32 kind=g_current_layer->kind;u32 mask=1<<kind;
    if (g_render_pass == 1) mask <<= 16;
    if (bank->rendered & mask) return;
    g_currentBank = bank;
    g_currentBound = (bank->flags & 0x10) ? bank->bound : 0;
    if (particleEnginePrepareRender(bank->camera)) {
        bank->rendered |= mask;
        push__16GSgfxMatrixStackFP5GSmtx(*(void**)((u8*)g_current_layer + 0x19a0),g_CameraMatrix);
        g_bank_token = 0;
        bank->node.Render(bank->data->emitter);
        if (g_bank_token) bank->token = g_bank_token;
        if ((bank->flags & 0x10) && (bank->flags & 0x20) && g_current_layer->kind == 4 && g_render_pass == 1)
            GSboundDraw__FP7GSboundP10GSgfxLayer(bank->bound,g_current_layer);
        pop__16GSgfxMatrixStackFv(*(void**)((u8*)g_current_layer + 0x19a0));
    }
}
#pragma opt_dead_assignments reset

struct _gpdHeader { u32 magic, version; u16 reserved08, count; u8 references, reserved0d[3]; };
struct _gpdResourceItem { u8 reserved00, flags; u16 reserved02; s32 kind; void* data; };
struct _particleData { u32 flags; s32 kind; void* data; _particleData* next; };
struct BankModel { u32 flags; u8 reserved04[0x48]; void* model; };
struct BankDistortion { u8 reserved00[0x78]; u8* first; u8* second; };
extern "C" {
extern u32 g_particle_debug_stats[6];
void HSD_JObjUnref(void*);
void GStextureFree(void*);
u32 shapeGetUsedMemorySize(u16);
void shapeRelease(u16);
}
static inline _particleData* _peBankData(_gpdHeader* header) {
    u8* cursor = (u8*)header + sizeof(_gpdHeader);
    cursor += header->count * sizeof(_gpdResourceItem);
    return (_particleData*)cursor;
}
static void _peFreeInternalBankData(_particleData* data) {
    void* object = data->data;
    if (object) {
        switch (data->kind) {
        case 0: {
            _peEmitter* emitter = (_peEmitter*)object;
            if (emitter) {
                _particleData* child = (_particleData*)emitter->resources;
                while (child) { _peFreeInternalBankData(child); child = child->next; }
            }
            break;
        }
        case 2: {
            BankModel* model = (BankModel*)object;
            if (!model || (model->flags & 0x40) || !model->model) return;
            HSD_JObjUnref(model->model);
            break;
        }
        case 4: {
            BankDistortion* distortion = (BankDistortion*)object;
            if (distortion->first) {
                g_particle_debug_stats[1] -= 128;
                g_particle_debug_stats[5] -= 128;
                delete distortion->first;
                distortion->first = 0;
            }
            if (distortion->second) {
                g_particle_debug_stats[1] -= 128;
                g_particle_debug_stats[5] -= 128;
                delete distortion->second;
                distortion->second = 0;
            }
            break;
        }
        }
    }
}

extern "C" {
void GSboundCreate(void*, void*);
u8 GSgfxVideoGetVsyncRate();
void* memset(void*, int, u32);
u32 GSmemGetSize(void*);
extern ParticleBankState* g_particleBanks;
}
extern "C" {
f32 HSD_Randf();
inline f32 GSrandf() { return HSD_Randf(); }
inline u16 GScast_float_to_u16(f32 value) {
    u16 result;
    OSf32tou16(&value, &result);
    return result;
}
}
struct EmitterRate { u8 reserved00[0xc]; f32 rate, rateRange; u8 reserved14[8]; f32 endTime; u8 reserved20[0x138 - 0x20]; _particleData* resources; };
static u16 _peBankCalculateMaxParticles(_particleData* data, f32 frameTime) {
    if (data->kind != 0) return 0;
    EmitterRate* emitter = (EmitterRate*)data->data;
    f32 rate = emitter->rate + emitter->rateRange * GSrandf();
    u16 count;
    if (emitter->endTime <= 0.00001f) count = GScast_float_to_u16(0.5f + rate);
    else {
        rate *= frameTime;
        count = GScast_float_to_u16(0.5f + rate);
    }
    if (count == 0) count = 1;
    for (_particleData* child = emitter->resources; child; child = child->next) {
        u16 childCount = _peBankCalculateMaxParticles(child, frameTime);
        if (childCount > count) count = childCount;
    }
    if (count > 1000) count = 1000;
    return count;
}
extern "C" ParticleBankState* peBankCreate(_gpdHeader* file) {
    if (!file) return 0;
    ParticleBankState* bank = new ParticleBankState;
    if (!bank) return 0;
    u32 size = GSmemGetSize(bank);
    g_particle_debug_stats[1] += size;
    g_particle_debug_stats[5] += size;
    GSboundCreate(bank->bound, 0);
    _particleData* data = _peBankData(file);
    bank->file = (ParticleBankFile*)file;
    file->references++;
    memset(&bank->node, 0, sizeof(peEmitterNode));
    bank->data = (ParticleBankFile*)data;
    bank->transform[0] = 0.0f;
    bank->transform[1] = 0.0f;
    bank->transform[2] = 0.0f;
    bank->transform[3] = 0.0f;
    bank->transform[4] = 0.0f;
    bank->transform[5] = 0.0f;
    bank->transform[6] = 1.0f;
    bank->transform[7] = 1.0f;
    bank->transform[8] = 1.0f;
    bank->transform[9] = 1.0f;
    bank->flags = 0;
    bank->rendered = 0;
    bank->token = 0;
    bank->camera = 0;
    ParticleBankState* last = g_particleBanks;
    if (last) {
        while (last->next) last = last->next;
        last->next = bank;
    } else g_particleBanks = bank;
    bank->next = 0;
    g_currentBank = bank;
    bank->node.transformParent = bank->transform;
    bank->node.Init((_peEmitter*)data->data);
    bank->maxParams = _peBankCalculateMaxParticles(data, 1.0f / GSgfxVideoGetVsyncRate());
    if (bank && bank->maxParams > g_maxEmitParams) {
        _EmitParams* old = g_emitParams;
        if (old) {
            g_particle_debug_stats[5] -= g_particle_debug_stats[0];
            g_particle_debug_stats[0] = 0;
            delete[] old;
        }
        u16 max = bank->maxParams;
        g_emitParamsBank = bank;
        g_maxEmitParams = (max + 9) / 10 * 10;
        u16 count = g_maxEmitParams;
        g_emitParams = new _EmitParams[count];
        g_particle_debug_stats[0] += g_maxEmitParams * sizeof(_EmitParams);
        g_particle_debug_stats[5] += g_maxEmitParams * sizeof(_EmitParams);
    }
    return bank;
}

extern "C" void peBankFreeFile(_gpdHeader* file) {
    if (file->magic == 0x01f056da) {
        switch((u32)(file->version - 0x30000)) {
        case 2:
            if (file->references == 0) {
                _peFreeInternalBankData(_peBankData(file));
                _gpdResourceItem* resource = (_gpdResourceItem*)(file + 1);
                u32 remaining = file->count;
                while (remaining) {
                    if ((resource->flags & 0x40) == 0x40) {
                        switch(resource->kind) {
                        case 0: GStextureFree(resource->data); break;
                        case 3: {
                            u16 shape = (u32)resource->data - 1;
                            u32 size = shapeGetUsedMemorySize(shape);
                            g_particle_debug_stats[4] -= size;
                            g_particle_debug_stats[5] -= size;
                            shapeRelease(shape);
                            break;
                        }
                        case 2: {
                            u32* table = (u32*)resource->data;
                            u32 i = 0;
                            u32 count = table[0];
                            u32* textures = table + 1;
                            for(; i < count; ++i, ++textures) {
                                if (*textures) GStextureFree((void*)*textures);
                            }
                            break;
                        }
                        }
                    }
                    ++resource; --remaining;
                }
            }
            break;
        }
    }
}
extern bool _peConvertFileData(_gpdHeader*,_gpdResourceItem*,_particleData*,const char*);
extern "C" _gpdHeader* peBankLoadFile(void* data, void*) {
    u8* cursor = (u8*)data;
    const char* base = (const char*)cursor;
    _gpdHeader* header = (_gpdHeader*)cursor;
    cursor += sizeof(_gpdHeader);
    _gpdResourceItem* items = (_gpdResourceItem*)cursor;
    cursor += header->count * sizeof(_gpdResourceItem);
    if (_peConvertFileData(header, items, (_particleData*)cursor, base)) return header;
    return 0;
}

extern "C" u8 peBankStart(ParticleBankState* bank) {
    static _EmitParams params;
    if (!bank) return 0;
    params.time = 1.0f;
    peBankStop(bank);
    g_currentBank = bank;
    g_currentBound = 0;
    _peEmitter* emitter = bank->data->emitter;
    bank->flags = 5;
    if (emitter->flags & 0x20000) {
        bank->flags |= 0x10;
        g_currentBound = bank->bound;
        GSboundReset(g_currentBound);
        GSboundAlwaysInView(g_currentBound, 0);
    }
    bank->node.Start(0, bank->data->emitter, &params);
    bank->token = 0;
    return 1;
}

extern "C" {
extern u16 g_maxEmitParams;
extern ParticleBankState* g_emitParamsBank;
extern ParticleBankState* g_particleBanks;
void GSgfxTokenWaitForClear(u16);
void GSboundFree(void*);
u32 GSmemGetSize(void*);
}
extern "C" void peBankFree(ParticleBankState* bank) {
    if (bank) {
        peBankStop(bank);
        if (bank->token) {
            GSgfxTokenWaitForClear(bank->token);
            bank->token = 0;
        }
        bank->node.Release();
        --bank->file->references;
        GSboundFree(bank->bound);
        if (bank && g_maxEmitParams && bank == g_emitParamsBank) {
            _EmitParams* old = g_emitParams;
            g_particle_debug_stats[5] -= g_particle_debug_stats[0];
            g_particle_debug_stats[0] = 0;
            delete[] old;
            g_emitParams = 0;
            g_emitParamsBank = 0;
            g_maxEmitParams = 0;
            ParticleBankState* current = g_particleBanks;
            while (current) {
                if (current != bank) {
                    u16 max = current->maxParams;
                    if (max > g_maxEmitParams) {
                        g_maxEmitParams = (max + 9) & ~9;
                        g_emitParamsBank = current;
                    }
                }
                current = current->next;
            }
            u16 count = g_maxEmitParams;
            if (count) {
                g_emitParams = new _EmitParams[count];
                g_particle_debug_stats[0] += g_maxEmitParams * sizeof(_EmitParams);
                g_particle_debug_stats[5] += g_maxEmitParams * sizeof(_EmitParams);
            }
        }
        ParticleBankState* previous = 0;
        ParticleBankState* current = g_particleBanks;
        while (current) {
            if (current == bank) break;
            previous = current;
            current = current->next;
        }
        if (previous) previous->next = current->next;
        else g_particleBanks = current->next;
        current->next = 0;
        u32 bytes = GSmemGetSize(bank);
        g_particle_debug_stats[1] -= bytes;
        g_particle_debug_stats[5] -= bytes;
        delete bank;
    }
}

extern "C" {
#include <game/maximum/GSAPI/baselib/archive.h>
void* GStextureLoad(void*);
s32 shapeGenerateIndex();
u8 shapeLoad(u16,void*);
void* HSD_JObjLoadJoint(void*);
void HSD_JObjAddAnimAll(void*,void*,void*,void*);
void HSD_JObjReqAnimAll(void*,f32);
void HSD_JObjAnimAll(void*);
void HSD_ForeachAnim(void*,s32,u32,void*,s32,...);
void HSD_AObjSetFlags();void HSD_AObjClearFlags();void HSD_AObjSetRate();void _modelGetEndFrame();
void* __nw__FUl(u32);
void* __ct__10GSgfxLightFv(void*);
void MakeDiff__10GSgfxLightFP11GSgfxColAu8P5GSvecb(void*,void*,Vec*,bool);
void MakeSpec__10GSgfxLightFP11GSgfxColAu8P5GSvecfP5GSvec(void*,void*,Vec*,f32,Vec*);
extern Vec zeroVector,zAxisVector;
}
static inline u32 bankRelocate(u32 value,const char* base) {
    u8 offset=0;
    if(value!=0 && value<0x80000000)offset=1;
    if(offset)value+=(u32)base;
    return value;
}
#define BANK_WORD(offset) definition[(offset)/4]
#define BANK_FLOAT(offset) (*(f32*)((u8*)definition+(offset)))
static inline _gpdResourceItem* bankFindResource(_gpdHeader* header,_gpdResourceItem* items,u32 id) {
    u32 remaining=header->count;
    while(remaining) {
        if(id==items->reserved00)break;
        ++items;--remaining;
    }
    if(!remaining)return 0;
    return items;
}
struct BankSceneModel {void* joint;void** animation;void** material;void** shape;};
struct BankScene {BankSceneModel*** models;};
bool _peConvertFileData(_gpdHeader* header,_gpdResourceItem* items,_particleData* records,const char* base) {
    HSD_Archive archive;
    if(header->magic!=0x01f056da || header->version!=0x30002)return false;
    if(header->references)return true;
    u32 resourceCount=header->count;
    u32 recordCount=header->reserved08;
    _gpdResourceItem* item=items;
    while(resourceCount) {
        item->data=(void*)bankRelocate((u32)item->data,base);
        item->flags&=~0x40;
        switch(item->kind) {
        case 0: {
            void* texture=GStextureLoad(item->data);
            if(texture)item->flags|=0x40;
            item->data=texture;
            break;
        }
        case 1: {
            HSD_ArchiveParse(&archive,(u8*)item->data,(item->reserved02<<5)-(item->flags&0x17));
            void* scene=HSD_ArchiveGetPublicAddress(&archive,"scene_data");
            if(scene)item->flags|=0x40;
            item->data=scene;
            break;
        }
        case 2:
            if(item->data) {
                u32* texture=(u32*)item->data;
                u32 count=*texture++;
                for(u32 i=0;i<count;++i,++texture) {
                    *texture=bankRelocate(*texture,(const char*)item->data);
                    *texture=(u32)GStextureLoad((void*)*texture);
                }
                item->flags|=0x40;
            }
            break;
        case 3: {
            u16 index=shapeGenerateIndex()+1;
            if(index) {
                s32 shape=index-1;
                if(shapeLoad(shape,item->data)) {
                    u32 size=shapeGetUsedMemorySize(shape);
                    g_particle_debug_stats[4]+=size;g_particle_debug_stats[5]+=size;
                    item->flags|=0x40;
                } else index=0;
            }
            item->data=(void*)index;
            break;
        }
        }
        ++item;--resourceCount;
    }
    while(recordCount) {
        records->data=(void*)bankRelocate((u32)records->data,base);
        records->next=(_particleData*)bankRelocate((u32)records->next,base);
        u32* definition=(u32*)records->data;
        if(definition) {
            switch(records->kind) {
            case 0:
                BANK_WORD(0x138)=bankRelocate(BANK_WORD(0x138),base);
                BANK_WORD(0x14)=bankRelocate(BANK_WORD(0x14),base);
                BANK_WORD(0x130)=bankRelocate(BANK_WORD(0x130),base);
                BANK_WORD(0x134)=bankRelocate(BANK_WORD(0x134),base);
                BANK_WORD(0xb8)=bankRelocate(BANK_WORD(0xb8),base);
                BANK_WORD(0xbc)=bankRelocate(BANK_WORD(0xbc),base);
                BANK_WORD(0xc0)=bankRelocate(BANK_WORD(0xc0),base);
                BANK_WORD(0xd0)=bankRelocate(BANK_WORD(0xd0),base);
                BANK_WORD(0xd4)=bankRelocate(BANK_WORD(0xd4),base);
                BANK_WORD(0xd8)=bankRelocate(BANK_WORD(0xd8),base);
                BANK_WORD(0xe8)=bankRelocate(BANK_WORD(0xe8),base);
                BANK_WORD(0xec)=bankRelocate(BANK_WORD(0xec),base);
                BANK_WORD(0xf0)=bankRelocate(BANK_WORD(0xf0),base);
                BANK_WORD(0x10c)=bankRelocate(BANK_WORD(0x10c),base);
                BANK_WORD(0x110)=bankRelocate(BANK_WORD(0x110),base);
                BANK_WORD(0x114)=bankRelocate(BANK_WORD(0x114),base);
                BANK_WORD(0x124)=bankRelocate(BANK_WORD(0x124),base);
                BANK_WORD(0x128)=bankRelocate(BANK_WORD(0x128),base);
                BANK_WORD(0x12c)=bankRelocate(BANK_WORD(0x12c),base);
                break;
            case 1: {
                _gpdResourceItem* resource=bankFindResource(header,items,BANK_WORD(0x54));
                if(resource) {
                    if(resource->kind==2)BANK_WORD(0)|=0x100000;
                    else BANK_WORD(0)&=~0x100000;
                    BANK_WORD(0x54)=(resource->flags&0x40)==0x40?(u32)resource->data:0;
                } else BANK_WORD(0x54)=0;
                BANK_WORD(0x34)=bankRelocate(BANK_WORD(0x34),base);
                BANK_WORD(0x14)=bankRelocate(BANK_WORD(0x14),base);
                BANK_WORD(0x18)=bankRelocate(BANK_WORD(0x18),base);
                BANK_WORD(0x38)=bankRelocate(BANK_WORD(0x38),base);
                BANK_WORD(0x3c)=bankRelocate(BANK_WORD(0x3c),base);
                if(!BANK_WORD(0x3c))BANK_WORD(0)&=~0x2000000;
                BANK_WORD(0x40)=bankRelocate(BANK_WORD(0x40),base);
                if(!(BANK_WORD(0)&8)) {
                    *(s16*)((u8*)definition+0x44)=(s16)(1024.0f*BANK_FLOAT(0x44));
                    *(s16*)((u8*)definition+0x46)=(s16)(1024.0f*BANK_FLOAT(0x48));
                    *(s16*)((u8*)definition+0x48)=(s16)(1024.0f*BANK_FLOAT(0x4c));
                    *(s16*)((u8*)definition+0x4a)=(s16)(1024.0f*BANK_FLOAT(0x50));
                    BANK_FLOAT(0x50)=0.0f;BANK_FLOAT(0x4c)=0.0f;
                    BANK_WORD(0)|=8;
                }
                break;
            }
            case 6: {
                _gpdResourceItem* resource=bankFindResource(header,items,BANK_WORD(0x1c));
                if(resource) {
                    if(resource->kind==2) {
                        BANK_WORD(0)|=0x400;
                        if(BANK_WORD(0)&0x2000)BANK_WORD(0)&=~0x40000;
                    } else BANK_WORD(0)&=~0x400;
                    BANK_WORD(0x1c)=(resource->flags&0x40)==0x40?(u32)resource->data:0;
                } else BANK_WORD(0x1c)=0;
                BANK_WORD(8)=bankRelocate(BANK_WORD(8),base);
                BANK_WORD(12)=bankRelocate(BANK_WORD(12),base);
                if(!BANK_WORD(12))BANK_WORD(0)&=~0x40000;
                BANK_WORD(16)=bankRelocate(BANK_WORD(16),base);
                break;
            }
            case 3: {
                _gpdResourceItem* resource=bankFindResource(header,items,BANK_WORD(0x60));
                BANK_WORD(0x60)=resource && (resource->flags&0x40)==0x40?(u32)resource->data:0;
                BANK_WORD(0x30)=bankRelocate(BANK_WORD(0x30),base);
                BANK_WORD(0x14)=bankRelocate(BANK_WORD(0x14),base);
                BANK_WORD(0x18)=bankRelocate(BANK_WORD(0x18),base);
                BANK_WORD(0x34)=bankRelocate(BANK_WORD(0x34),base);
                break;
            }
            case 2: {
                _gpdResourceItem* resource=bankFindResource(header,items,BANK_WORD(0x4c));
                if(!resource)BANK_WORD(0x4c)=0;
                else if((BANK_WORD(0)&0x40) && resource->kind==3)BANK_WORD(0x4c)=(resource->flags&0x40)==0x40?(u32)resource->data:0;
                else if(resource->kind==1) {
                    BankSceneModel*** scene=(BankSceneModel***)((resource->flags&0x40)==0x40?resource->data:0);
                    if(scene) {
                        BankSceneModel* model=**scene;
                        void* joint=HSD_JObjLoadJoint(model->joint);
                        if(joint) {
                            BANK_WORD(0x4c)=(u32)joint;
                            void* animation=0;void* material=0;void* shape=0;
                            BANK_FLOAT(0x54)=0.0f;BANK_FLOAT(0x50)=0.0f;
                            if(model->animation)animation=*model->animation;
                            if(model->material)material=*model->material;
                            if(model->shape)shape=*model->shape;
                            HSD_JObjAddAnimAll(joint,animation,material,shape);
                            if(BANK_WORD(0)&4)HSD_ForeachAnim(joint,6,0xffff,(void*)HSD_AObjSetFlags,3,0x20000000);
                            else HSD_ForeachAnim(joint,6,0xffff,(void*)HSD_AObjClearFlags,3,0x20000000);
                            HSD_ForeachAnim(joint,6,0xffff,(void*)HSD_AObjSetRate,1,0.0);
                            HSD_ForeachAnim(joint,6,0xffff,(void*)_modelGetEndFrame,2,(u8*)definition+0x50);
                            HSD_JObjReqAnimAll(joint,0.0f);HSD_JObjAnimAll(joint);
                            BANK_FLOAT(0x50)/=60.0f;
                        } else BANK_WORD(0x4c)=0;
                    }
                } else BANK_WORD(0x4c)=0;
                BANK_WORD(0x34)=bankRelocate(BANK_WORD(0x34),base);
                BANK_WORD(0x38)=bankRelocate(BANK_WORD(0x38),base);
                BANK_WORD(0x3c)=bankRelocate(BANK_WORD(0x3c),base);
                BANK_WORD(0x40)=bankRelocate(BANK_WORD(0x40),base);
                BANK_WORD(0x44)=bankRelocate(BANK_WORD(0x44),base);
                BANK_WORD(0x48)=bankRelocate(BANK_WORD(0x48),base);
                break;
            }
            case 4: {
                _gpdResourceItem* resource=bankFindResource(header,items,BANK_WORD(0x74));
                BANK_WORD(0x74)=resource && (resource->flags&0x40)==0x40?(u32)resource->data:0;
                BANK_WORD(0x4c)=bankRelocate(BANK_WORD(0x4c),base);
                BANK_WORD(0x50)=bankRelocate(BANK_WORD(0x50),base);
                BANK_WORD(0x34)=bankRelocate(BANK_WORD(0x34),base);
                BANK_WORD(0x38)=bankRelocate(BANK_WORD(0x38),base);
                BANK_WORD(0x3c)=bankRelocate(BANK_WORD(0x3c),base);
                BANK_WORD(0x40)=bankRelocate(BANK_WORD(0x40),base);
                BANK_WORD(0x44)=bankRelocate(BANK_WORD(0x44),base);
                BANK_WORD(0x48)=bankRelocate(BANK_WORD(0x48),base);
                if(BANK_WORD(0)&0x200) {
                    void* light=__nw__FUl(128);
                    if(light)light=__ct__10GSgfxLightFv(light);
                    if(light) {
                        g_particle_debug_stats[1]+=128;g_particle_debug_stats[5]+=128;
                        MakeDiff__10GSgfxLightFP11GSgfxColAu8P5GSvecb(light,(u8*)definition+0x6c,&zeroVector,false);
                        BANK_WORD(0x78)=(u32)light;
                        if(BANK_WORD(0)&0x400) {
                            void* specular=__nw__FUl(128);
                            if(specular)specular=__ct__10GSgfxLightFv(specular);
                            if(specular) {
                                g_particle_debug_stats[1]+=128;g_particle_debug_stats[5]+=128;
                                MakeSpec__10GSgfxLightFP11GSgfxColAu8P5GSvecfP5GSvec(specular,(u8*)definition+0x6c,&zAxisVector,BANK_FLOAT(0x70),0);
                                BANK_WORD(0x7c)=(u32)specular;
                            } else BANK_WORD(0)&=~0x400;
                        }
                    } else BANK_WORD(0)&=~0x600;
                }
                break;
            }
            }
        }
        ++records;--recordCount;
    }
    return true;
}
#undef BANK_WORD
#undef BANK_FLOAT
