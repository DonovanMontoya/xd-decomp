#include <game/pxdvs/GSAPI/GSparticle/peBankPrivate.hpp>
#include <dolphin/os/OSFastCast.h>
#include <game/maximum/GSAPI/baselib/animation.h>
#include <game/maximum/GSAPI/baselib/scene.h>
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
#include <game/pxdvs/GSAPI/GSparticle/peResourceData.hpp>
#include <game/pxdvs/GSAPI/GSgfxM/light_gfxmPrivate.hpp>

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
    if (bank->flags & 1) return bank->node.time;
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

extern "C" {
extern u16 g_bank_token;
extern void* g_CameraMatrix;
void push__16GSgfxMatrixStackFP5GSmtx(void*,void*);
void pop__16GSgfxMatrixStackFv(void*);
void GSboundDraw__FP7GSboundP10GSgfxLayer(void*,GSgfxLayer*);
}
#pragma opt_dead_assignments off
extern "C" void peBankRender(ParticleBankState* bank) {
    if (!bank) return;
    if (!(bank->flags & 1)) return;
    if (!(bank->flags & 4)) return;
    if (!(bank->flags & 8)) return;
    u32 kind=g_current_layer->id;u32 mask=1<<kind;
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
        if ((bank->flags & 0x10) && (bank->flags & 0x20) && g_current_layer->id == 4 && g_render_pass == 1)
            GSboundDraw__FP7GSboundP10GSgfxLayer(bank->bound,g_current_layer);
        pop__16GSgfxMatrixStackFv(*(void**)((u8*)g_current_layer + 0x19a0));
    }
}
#pragma opt_dead_assignments reset

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

union BankResourcePayload {
    void* data;
    GStexture* texture;
    ParticleTextureAnimation* animation;
    _HSD_SceneDesc* scene;
};

struct _gpdResourceItem {
    u8 id, flags;
    u16 sizeInBlocks;
    s32 kind;
    BankResourcePayload payload;
};
extern "C" {
void HSD_JObjUnref(HSD_JObj*);
u32 shapeGetUsedMemorySize(u16);
void shapeRelease(u16);
}
static inline _particleData* _peBankData(_gpdHeader* header) {
    u8* cursor = (u8*)header + sizeof(_gpdHeader);
    cursor += header->resourceCount * sizeof(_gpdResourceItem);
    return (_particleData*)cursor;
}

extern "C" {
void GSboundCreate(void*, void*);
u8 GSgfxVideoGetVsyncRate();
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

extern "C" u8 peBankStart(ParticleBankState* bank) {
    static _EmitParams params;
    if (!bank) return 0;
    params.life = 1.0f;
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
            g_particle_debug_stats.total -= g_particle_debug_stats.bank;
            g_particle_debug_stats.bank = 0;
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
                g_particle_debug_stats.bank += g_maxEmitParams * sizeof(_EmitParams);
                g_particle_debug_stats.total += g_maxEmitParams * sizeof(_EmitParams);
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
        g_particle_debug_stats.node -= bytes;
        g_particle_debug_stats.total -= bytes;
        delete bank;
    }
}

static u16 _peBankCalculateMaxParticles(_particleData* data, f32 frameTime);
static void _peFreeInternalBankData(_particleData* data);

extern "C" ParticleBankState* peBankCreate(_gpdHeader* file) {
    if (!file) return 0;
    ParticleBankState* bank = new ParticleBankState;
    if (!bank) return 0;
    u32 size = GSmemGetSize(bank);
    g_particle_debug_stats.node += size;
    g_particle_debug_stats.total += size;
    GSboundCreate(bank->bound, 0);
    _particleData* data = _peBankData(file);
    bank->file = file;
    file->references++;
    memset(&bank->node, 0, sizeof(peEmitterNode));
    bank->data = data;
    bank->transform.position.x = 0.0f;
    bank->transform.position.y = 0.0f;
    bank->transform.position.z = 0.0f;
    bank->transform.rotation.x = 0.0f;
    bank->transform.rotation.y = 0.0f;
    bank->transform.rotation.z = 0.0f;
    bank->transform.rotation.w = 1.0f;
    bank->transform.scale.x = 1.0f;
    bank->transform.scale.y = 1.0f;
    bank->transform.scale.z = 1.0f;
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
    bank->node.transform = &bank->transform;
    bank->node.Init(data->emitter);
    bank->maxParams = _peBankCalculateMaxParticles(data, 4.0f / GSgfxVideoGetVsyncRate());
    if (bank && bank->maxParams > g_maxEmitParams) {
        _EmitParams* old = g_emitParams;
        if (old) {
            g_particle_debug_stats.total -= g_particle_debug_stats.bank;
            g_particle_debug_stats.bank = 0;
            delete[] old;
        }
        u16 max = bank->maxParams;
        g_emitParamsBank = bank;
        g_maxEmitParams = (max + 9) / 10 * 10;
        u16 count = g_maxEmitParams;
        g_emitParams = new _EmitParams[count];
        g_particle_debug_stats.bank += g_maxEmitParams * sizeof(_EmitParams);
        g_particle_debug_stats.total += g_maxEmitParams * sizeof(_EmitParams);
    }
    return bank;
}

extern "C" void peBankFreeFile(_gpdHeader *fileData) {
    ParticleTextureFrame* frames;
    u32 index;
    u32 textureCount;
    u16 shape;
    u32 size;
    char *bankData;
    _gpdResourceItem *resource;
    _gpdHeader *file;
    u32 resourceCount;
    file = (_gpdHeader *)fileData;
    if (file->magic != 0x01f056da || file->version != 0x30002) return;
    if (file->references) return;
    bankData = (char *)(file + 1);
    bankData += file->resourceCount * sizeof(_gpdResourceItem);
    _peFreeInternalBankData((_particleData *)bankData);
    resource = (_gpdResourceItem *)(file + 1);
    resourceCount = file->resourceCount;
    while (resourceCount) {
        if ((resource->flags & 0x40) == 0x40) {
            switch (resource->kind) {
            case 0:
                GStextureFree(resource->payload.texture);
                break;
            case 3:
                shape = (u32)resource->payload.data - 1;
                size = shapeGetUsedMemorySize(shape);
                g_particle_debug_stats.primitiveMemory -= size;
                g_particle_debug_stats.total -= size;
                shapeRelease(shape);
                break;
            case 2:
                textureCount = resource->payload.animation->count;
                frames = resource->payload.animation->frames;
                for (index = 0; index < textureCount; index++, frames++) {
                    if (frames->texture) GStextureFree(frames->texture);
                }
                break;
            }
        }
        resource++;
        resourceCount--;
    }
}
extern bool _peConvertFileData(_gpdHeader*,_gpdResourceItem*,_particleData*,const char*);
extern "C" _gpdHeader* peBankLoadFile(void* data) {
    u8* cursor = (u8*)data;
    const char* base = (const char*)cursor;
    _gpdHeader* header = (_gpdHeader*)cursor;
    cursor += sizeof(_gpdHeader);
    _gpdResourceItem* items = (_gpdResourceItem*)cursor;
    cursor += header->resourceCount * sizeof(_gpdResourceItem);
    if (_peConvertFileData(header, items, (_particleData*)cursor, base)) return header;
    return 0;
}

static u16 _peBankCalculateMaxParticles(_particleData* data, f32 frameTime) {
    if (data->kind != 0) return 0;
    _peEmitter* emitter = data->emitter;
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

static void _peFreeInternalBankData(_particleData* data) {
    void* object = data->data;
    if (object) {
        switch (data->kind) {
        case 0: {
            _peEmitter* emitter = (_peEmitter*)object;
            if (emitter) {
                _particleData* child = emitter->resources;
                while (child) { _peFreeInternalBankData(child); child = child->next; }
            }
            break;
        }
        case 2: {
            _peModel* model = static_cast<_peModel*>(object);
            if (!model || (model->flags & 0x40) || !model->resource.jobj) return;
            HSD_JObjUnref(model->resource.jobj);
            break;
        }
        case 4: {
            _peShape* shape = static_cast<_peShape*>(object);
            if (shape->light0) {
                g_particle_debug_stats.node -= sizeof(GSgfxLight);
                g_particle_debug_stats.total -= sizeof(GSgfxLight);
                delete shape->light0;
                shape->light0 = 0;
            }
            if (shape->light1) {
                g_particle_debug_stats.node -= sizeof(GSgfxLight);
                g_particle_debug_stats.total -= sizeof(GSgfxLight);
                delete shape->light1;
                shape->light1 = 0;
            }
            break;
        }
        }
    }
}

extern "C" {
#include <game/maximum/GSAPI/baselib/archive.h>
s32 shapeGenerateIndex();
u8 shapeLoad(u16,void*);
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint*);
void HSD_JObjAddAnimAll(HSD_JObj*, HSD_AnimJoint*, HSD_MatAnimJoint*, HSD_ShapeAnimJoint*);
void HSD_JObjReqAnimAll(HSD_JObj*, f32);
void HSD_JObjAnimAll(HSD_JObj*);
void _modelGetEndFrame(HSD_AObj*, f32*);
extern GSvec zeroVector, zAxisVector;
}
static inline u32 bankRelocate(u32 value,const char* base) {
    u8 offset=0;
    if(value!=0 && value<0x80000000)offset=1;
    if(offset)value+=(u32)base;
    return value;
}
template <class T>
static inline void bankRelocatePointer(T*& pointer, const char* base) {
    pointer = (T*)bankRelocate((u32)pointer, base);
}
// Keep field addresses local to each conversion, as in the original code.
#pragma opt_common_subs off
bool _peConvertFileData(_gpdHeader* header,_gpdResourceItem* items,_particleData* records,const char* base) {
    HSD_Archive archive;
    if(header->magic!=0x01f056da || header->version!=0x30002)return false;
    if(header->references)return true;
    u32 resourceCount=header->resourceCount;
    u32 recordCount=header->recordCount;
    _gpdResourceItem* item=items;
    while(resourceCount) {
        bankRelocatePointer(item->payload.data, base);
        item->flags&=~0x40;
        switch(item->kind) {
        case 0: {
            GStexture* texture=GStextureLoad(item->payload.data);
            if(texture)item->flags|=0x40;
            item->payload.texture=texture;
            break;
        }
        case 1: {
            HSD_ArchiveParse(&archive, (u8*)item->payload.data,
                             (item->sizeInBlocks << 5) - (item->flags & 0x17));
            _HSD_SceneDesc* scene = static_cast<_HSD_SceneDesc*>(
                HSD_ArchiveGetPublicAddress(&archive, "scene_data"));
            if (scene) item->flags |= 0x40;
            item->payload.scene = scene;
            break;
        }
        case 2:
            if(item->payload.data) {
                ParticleTextureFrame* frame = item->payload.animation->frames;
                u32 count = item->payload.animation->count;
                for(u32 i=0;i<count;++i,++frame) {
                    u32 value = frame->address;
                    u8 relative=0;
                    if(value && value<0x80000000)relative=1;
                    if(relative)value+=(u32)item->payload.data;
                    frame->address = value;
                    frame->texture = GStextureLoad(frame->serialized);
                }
                item->flags|=0x40;
            }
            break;
        case 3: {
            u16 index=shapeGenerateIndex()+1;
            if(index) {
                s32 shape=index-1;
                if(shapeLoad(shape,item->payload.data)) {
                    u32 size=shapeGetUsedMemorySize(shape);
                    g_particle_debug_stats.primitiveMemory+=size;g_particle_debug_stats.total+=size;
                    item->flags|=0x40;
                } else index=0;
            }
            item->payload.data=(void*)index;
            break;
        }
        }
        ++item;--resourceCount;
    }
    while(recordCount) {
        bankRelocatePointer(records->data, base);
        bankRelocatePointer(records->next, base);
        void* definition = records->data;
        if(!definition) {
            ++records;
            --recordCount;
            continue;
        }
        switch(records->kind) {
        case 0: {
            _peEmitter* emitter = (_peEmitter*)definition;
            bankRelocatePointer(emitter->resources, base);
            bankRelocatePointer(emitter->rateSpline, base);
            bankRelocatePointer(emitter->colorSpline, base);
            bankRelocatePointer(emitter->alphaSpline, base);
            bankRelocatePointer(emitter->forceSpline[0], base);
            bankRelocatePointer(emitter->forceSpline[1], base);
            bankRelocatePointer(emitter->forceSpline[2], base);
            bankRelocatePointer(emitter->offsetSpline[0], base);
            bankRelocatePointer(emitter->offsetSpline[1], base);
            bankRelocatePointer(emitter->offsetSpline[2], base);
            bankRelocatePointer(emitter->eulerSpline[0], base);
            bankRelocatePointer(emitter->eulerSpline[1], base);
            bankRelocatePointer(emitter->eulerSpline[2], base);
            bankRelocatePointer(emitter->angularVelocitySpline[0], base);
            bankRelocatePointer(emitter->angularVelocitySpline[1], base);
            bankRelocatePointer(emitter->angularVelocitySpline[2], base);
            bankRelocatePointer(emitter->scaleSpline[0], base);
            bankRelocatePointer(emitter->scaleSpline[1], base);
            bankRelocatePointer(emitter->scaleSpline[2], base);
            break;
        }
        case 1: {
            _peParticle* particle = static_cast<_peParticle*>(definition);
            u32 remaining = header->resourceCount;
            _gpdResourceItem* resource = items;
            while (remaining) {
                if (particle->textureId == resource->id) {
                    if (resource->kind == 2) {
                        particle->flags |= 0x100000;
                        particle->textureAnimation = (resource->flags & 0x40) == 0x40 ? resource->payload.animation : 0;
                        break;
                    } else {
                        particle->flags &= ~0x100000;
                        particle->texture = (resource->flags & 0x40) == 0x40 ? resource->payload.texture : 0;
                        break;
                    }
                }
                ++resource;
                --remaining;
            }
            if (remaining == 0) particle->texture = 0;
            bankRelocatePointer(particle->angleSpline, base);
            bankRelocatePointer(particle->widthSpline, base);
            bankRelocatePointer(particle->heightSpline, base);
            bankRelocatePointer(particle->colorSpline, base);
            bankRelocatePointer(particle->extraColorSpline, base);
            if (!particle->extraColorSpline) particle->flags &= ~0x2000000;
            bankRelocatePointer(particle->alphaSpline, base);
            if (!(particle->flags & 8)) {
                // Read each float pair before overwriting it with packed s16 values.
                f32 x = particle->textureCoordinates[0], y = particle->textureCoordinates[1];
                particle->converted.u0 = (s16)(1024.0f * x);
                particle->converted.v0 = (s16)(1024.0f * y);
                f32 z = particle->textureCoordinates[2], w = particle->textureCoordinates[3];
                particle->converted.u1 = (s16)(1024.0f * z);
                particle->converted.v1 = (s16)(1024.0f * w);
                particle->converted.roll = 0.0f;
                particle->converted.yaw = 0.0f;
                particle->flags |= 8;
            }
            break;
        }
        case 6: {
            _peParticleStrip* strip = static_cast<_peParticleStrip*>(definition);
            u32 remaining = header->resourceCount;
            _gpdResourceItem* resource = items;
            while (remaining) {
                if (strip->textureId == resource->id) {
                    if (resource->kind == 2) {
                        strip->flags |= 0x400;
                        if (strip->flags & 0x2000) strip->flags &= ~0x40000;
                        strip->textureAnimation = (resource->flags & 0x40) == 0x40 ? resource->payload.animation : 0;
                        break;
                    } else {
                        strip->flags &= ~0x400;
                        strip->texture = (resource->flags & 0x40) == 0x40 ? resource->payload.texture : 0;
                        break;
                    }
                }
                ++resource;
                --remaining;
            }
            if (remaining == 0) strip->texture = 0;
            bankRelocatePointer(strip->colorSpline, base);
            bankRelocatePointer(strip->secondColorSpline, base);
            if (!strip->secondColorSpline) strip->flags &= ~0x40000;
            bankRelocatePointer(strip->alphaSpline, base);
            break;
        }
        case 3: {
            _peDistortion* distortion = static_cast<_peDistortion*>(definition);
            u32 remaining = header->resourceCount;
            _gpdResourceItem* resource = items;
            while (remaining) {
                if (distortion->textureId == resource->id) {
                    distortion->texture = (resource->flags & 0x40) == 0x40 ? resource->payload.texture : 0;
                    break;
                }
                ++resource;
                --remaining;
            }
            if (remaining == 0) distortion->texture = 0;
            bankRelocatePointer(distortion->angleSpline, base);
            bankRelocatePointer(distortion->widthSpline, base);
            bankRelocatePointer(distortion->heightSpline, base);
            bankRelocatePointer(distortion->alphaSpline, base);
            break;
        }
        case 2: {
            _peModel* modelRecord = static_cast<_peModel*>(definition);
            u32 remaining = header->resourceCount;
            _gpdResourceItem* resource = items;
            while (remaining) {
                if (modelRecord->resource.id == resource->id) {
                    if ((modelRecord->flags & 0x40) && resource->kind == 3) {
                        modelRecord->resource.primitive = (resource->flags & 0x40) == 0x40 ? (u32)resource->payload.data : 0;
                    } else if (resource->kind == 1) {
                        _HSD_SceneDesc* scene = (resource->flags & 0x40) == 0x40 ? resource->payload.scene : 0;
                        if (scene) {
                            _HSD_SceneModelSet* model = scene->models[0];
                            HSD_JObj* joint = HSD_JObjLoadJoint(model->joint);
                            if (joint) {
                                modelRecord->resource.jobj = joint;
                                HSD_AnimJoint* animation = 0;
                                HSD_MatAnimJoint* material = 0;
                                HSD_ShapeAnimJoint* shape = 0;
                                modelRecord->field54 = 0.0f;
                                modelRecord->duration = 0.0f;
                                if (model->animations) animation = model->animations[0];
                                if (model->materialAnimations) material = model->materialAnimations[0];
                                if (model->shapeAnimations) shape = model->shapeAnimations[0];
                                HSD_JObjAddAnimAll(joint, animation, material, shape);
                                if (modelRecord->flags & 4) {
                                    HSD_ForeachAnim(joint, JOBJ_TYPE, ALL_TYPE_MASK,
                                                    (void*)HSD_AObjSetFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                                } else {
                                    HSD_ForeachAnim(joint, JOBJ_TYPE, ALL_TYPE_MASK,
                                                    (void*)HSD_AObjClearFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                                }
                                HSD_ForeachAnim(joint, JOBJ_TYPE, ALL_TYPE_MASK,
                                                (void*)HSD_AObjSetRate, AOBJ_ARG_AF, 0.0);
                                HSD_ForeachAnim(joint, JOBJ_TYPE, ALL_TYPE_MASK,
                                                (void*)_modelGetEndFrame, AOBJ_ARG_AV, &modelRecord->duration);
                                HSD_JObjReqAnimAll(joint, 0.0f);
                                HSD_JObjAnimAll(joint);
                                modelRecord->duration /= 60.0f;
                            } else {
                                modelRecord->resource.id = 0;
                            }
                        }
                    } else {
                        modelRecord->resource.id = 0;
                    }
                    break;
                }
                ++resource;
                --remaining;
            }
            if (remaining == 0) modelRecord->resource.id = 0;
            bankRelocatePointer(modelRecord->rotationSpline[0], base);
            bankRelocatePointer(modelRecord->rotationSpline[1], base);
            bankRelocatePointer(modelRecord->rotationSpline[2], base);
            bankRelocatePointer(modelRecord->scaleSpline[0], base);
            bankRelocatePointer(modelRecord->scaleSpline[1], base);
            bankRelocatePointer(modelRecord->scaleSpline[2], base);
            break;
        }
        case 4: {
            _peShape* shape = static_cast<_peShape*>(definition);
            u32 remaining = header->resourceCount;
            _gpdResourceItem* resource = items;
            while (remaining) {
                if (shape->textureId == resource->id) {
                    shape->texture = (resource->flags & 0x40) == 0x40 ? resource->payload.texture : 0;
                    break;
                }
                ++resource;
                --remaining;
            }
            if (remaining == 0) shape->texture = 0;
            bankRelocatePointer(shape->colorSpline, base);
            bankRelocatePointer(shape->alphaSpline, base);
            bankRelocatePointer(shape->rotationSpline[0], base);
            bankRelocatePointer(shape->rotationSpline[1], base);
            bankRelocatePointer(shape->rotationSpline[2], base);
            bankRelocatePointer(shape->scaleSpline[0], base);
            bankRelocatePointer(shape->scaleSpline[1], base);
            bankRelocatePointer(shape->scaleSpline[2], base);
            if (shape->flags & 0x200) {
                GSgfxLight* light = new GSgfxLight;
                if (light) {
                    g_particle_debug_stats.node += sizeof(GSgfxLight);
                    g_particle_debug_stats.total += sizeof(GSgfxLight);
                    light->MakeDiff(&shape->lightColor, &zeroVector, false);
                    shape->light0 = light;
                    if (shape->flags & 0x400) {
                        GSgfxLight* specular = new GSgfxLight;
                        if (specular) {
                            g_particle_debug_stats.node += sizeof(GSgfxLight);
                            g_particle_debug_stats.total += sizeof(GSgfxLight);
                            specular->MakeSpec(&shape->lightColor, &zAxisVector, shape->shininess, 0);
                            shape->light1 = specular;
                        } else {
                            shape->flags &= ~0x400;
                        }
                    }
                } else {
                    shape->flags &= ~0x600;
                }
            }
            break;
        }
        }
        ++records;--recordCount;
    }
    return true;
}

#pragma opt_common_subs reset
