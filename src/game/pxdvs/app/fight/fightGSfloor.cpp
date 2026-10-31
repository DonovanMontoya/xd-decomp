#include <dolphin/types.h>

struct GSvec {
    f32 x, y, z;
};

struct _GSmodel;
struct FIGHT_FLOOR;
struct GridRow {
    u32 trainer;
    u32 pokemon[2];
    u32 info;
};
struct battleGrid {
    GridRow rows[4];
    u8 rest[4];
};

struct GSmodelState {
    u8 data[0x6C];
};

struct GSfloorScan {
    u8 collect;
    u8 consume;
    u16 count;
    battleGrid* grid;
    u8* next;
};

struct GSfloorTrainerEntry {
    u32 target;
    u16 id;
    u8 flags;
    u8 flipped;
    u32* bgSeq;
    GSmodelState state;
};

struct GSfloorPokemonEntry {
    u32 target;
    u16 id;
    u8 flags;
    u8 rare;
    u8 flipped;
    u32 rnd;
    u32* bgSeq;
    GSmodelState state;
};

struct GSfloorPush {
    u16 trainerCount;
    u16 pokemonCount;
    u16 evtFlag;
    u8 pad[2];
    u8 grid[0x44];
};

typedef u8 (*GSfloorLoopFunc)(void*, u16, void*);

extern "C" {
void* memcpy(void* dst, const void* src, u32 n);
void* memset(void* dst, int val, u32 n);
battleGrid* battleGridGetPtr(void);
void battleGridReset(void);
void fightMainAllCamera(u32, u32);
void fightFloorLoopValidFightTrainer(FIGHT_FLOOR* floor, GSfloorLoopFunc func, void* data, u8 thread);
u8 fightFloorLoopValidFightOutPokemon(FIGHT_FLOOR* floor, GSfloorLoopFunc func, void* data, u8 useAry);
u8 fightFloorIsNowEncountSnatchOnly(FIGHT_FLOOR* floor);
void fightFloorSetShadow(void);
u32 fightEvtGetSequence(void);
void fightEvtSetSequence(u32 seq);
u32 pokemonGetStatus(void* ptr, u16 pokemonDataId, u16 kind, u16 index);
u32 fightTrainerGetStatus(void* trainer, u16 id, u16 kind, u16 arg);
void GSmodelPushState(_GSmodel* model, GSmodelState* state);
void GSmodelPopState(_GSmodel* model, GSmodelState* state);
void GSmodelGetPosition(_GSmodel* model, GSvec* v);
void GSmodelGetRotation(_GSmodel* model, GSvec* v);
void GSmodelGetScale(_GSmodel* model, GSvec* v);
u32 GSmodelGetVisibility(_GSmodel* model);
u32 Sequence_LoadTrainer(u32 id);
u32 Sequence_LoadPokemon(u32 id, u32 rnd, u32 rare);
_GSmodel* Sequence_GetGSmodel(u32 seq);
void Sequence_SetPosition(u32 seq, GSvec* v);
void Sequence_SetRotation(u32 seq, GSvec* v);
void Sequence_SetScale(u32 seq, GSvec* v);
void Sequence_SetFlipped(u32 seq, u8 flipped);
void Sequence_SetFlags(u32 seq, u8 flags);
void Sequence_SetVisibility(u32 seq, u32 visible);
u8 Sequence_GetFlags(u32 seq);
u8 Sequence_IsFlipped(u32 seq);
u8 Sequence_IsRare(u32 seq);
u32 Sequence_GetPokemonRndVal(u32 seq);
u16 Sequence_GetID(u32 seq);
void Sequence_Free(u32 seq);
}

static u8 _fightGSfloorTrainerEvt(void*, u16, void*);
static u8 _fightGSfloorPokemonCB(void*, u16, void*);
static u8 _fightGSfloorTrainerCB(void*, u16, void*);
static u32* _fightGSfloorFindBGSeqPtr(battleGrid* grid, u32 seq, bool trainer);

extern "C" {

void fightGSfloorFree(void) {
    GSfloorScan scan;
    memset(&scan, 0, sizeof(scan));
    scan.consume = 1;
    fightFloorLoopValidFightTrainer(0, _fightGSfloorTrainerCB, &scan, 0);
    if (fightFloorIsNowEncountSnatchOnly(0) == 1) {
        _fightGSfloorTrainerEvt(0, 0, &scan);
    }
    fightFloorLoopValidFightOutPokemon(0, _fightGSfloorPokemonCB, &scan, 0);
    battleGridReset();
    fightMainAllCamera(1, 0);
}

u32 fightGSfloorGetPushDataSize(void) {
    GSfloorScan scan;
    u16 trainerCount;
    u16 pokemonCount;
    s32 total;
    scan.collect = 0;
    scan.consume = 0;
    scan.count = 0;
    scan.next = 0;
    fightFloorLoopValidFightTrainer(0, _fightGSfloorTrainerCB, &scan, 0);
    trainerCount = scan.count;
    scan.count = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightGSfloorPokemonCB, &scan, 0);
    pokemonCount = scan.count;
    if (fightFloorIsNowEncountSnatchOnly(0) == 1) {
        trainerCount++;
    }
    total = trainerCount * 0x78;
    total += pokemonCount * 0x80;
    return total + 0x4C;
}

void fightGSfloorPushData(GSfloorPush* out) {
    GSfloorScan scan;
    u16 trainerCount;
    u16 pokemonCount;
    u8* grid = out->grid;
    memcpy(grid, battleGridGetPtr(), 0x44);
    scan.collect = 1;
    scan.consume = 0;
    scan.count = 0;
    scan.grid = (battleGrid*)grid;
    scan.next = grid + 0x44;
    fightFloorLoopValidFightTrainer(0, _fightGSfloorTrainerCB, &scan, 0);
    trainerCount = scan.count;
    if (fightFloorIsNowEncountSnatchOnly(0) == 1) {
        _fightGSfloorTrainerEvt(0, 0, &scan);
    }
    scan.count = 0;
    fightFloorLoopValidFightOutPokemon(0, _fightGSfloorPokemonCB, &scan, 0);
    pokemonCount = scan.count;
    memset(out, 0, 8);
    out->trainerCount = trainerCount;
    out->pokemonCount = pokemonCount;
    if (fightFloorIsNowEncountSnatchOnly(0) == 1) {
        out->evtFlag = 1;
    }
}

void fightGSfloorPopData(GSfloorPush* in) {
    u16 pokemonCount;
    u8* grid;
    u16 trainerCount;
    u16 evtFlag;
    GSfloorTrainerEntry* t;
    GSfloorPokemonEntry* p;
    _GSmodel* model;
    u32 seq;
    GSvec v;

    grid = in->grid;
    t = (GSfloorTrainerEntry*)(grid + 0x44);
    trainerCount = in->trainerCount;
    pokemonCount = in->pokemonCount;
    evtFlag = in->evtFlag;
    while (trainerCount-- != 0) {
        seq = Sequence_LoadTrainer(t->id);
        *(u32*)(t->target + 0x3544) = seq;
        *t->bgSeq = seq;
        model = Sequence_GetGSmodel(seq);
        GSmodelPopState(model, &t->state);
        GSmodelGetPosition(model, &v);
        Sequence_SetPosition(seq, &v);
        GSmodelGetRotation(model, &v);
        Sequence_SetRotation(seq, &v);
        GSmodelGetScale(model, &v);
        Sequence_SetScale(seq, &v);
        Sequence_SetFlipped(seq, t->flipped);
        Sequence_SetFlags(seq, t->flags);
        Sequence_SetVisibility(seq, GSmodelGetVisibility(model));
        t++;
    }
    if (evtFlag != 0) {
        seq = Sequence_LoadTrainer(0x40);
        fightEvtSetSequence(seq);
        model = Sequence_GetGSmodel(seq);
        GSmodelPopState(model, &t->state);
        GSmodelGetPosition(model, &v);
        Sequence_SetPosition(seq, &v);
        GSmodelGetRotation(model, &v);
        Sequence_SetRotation(seq, &v);
        GSmodelGetScale(model, &v);
        Sequence_SetScale(seq, &v);
        Sequence_SetFlipped(seq, t->flipped);
        Sequence_SetFlags(seq, t->flags);
        Sequence_SetVisibility(seq, GSmodelGetVisibility(model));
        t++;
    }
    p = (GSfloorPokemonEntry*)t;
    while (pokemonCount-- != 0) {
        seq = Sequence_LoadPokemon(p->id, p->rnd, p->rare);
        *(u32*)(p->target + 0x7AC) = seq;
        *p->bgSeq = seq;
        model = Sequence_GetGSmodel(seq);
        GSmodelPopState(model, &p->state);
        GSmodelGetPosition(model, &v);
        Sequence_SetPosition(seq, &v);
        GSmodelGetRotation(model, &v);
        Sequence_SetRotation(seq, &v);
        GSmodelGetScale(model, &v);
        Sequence_SetScale(seq, &v);
        Sequence_SetFlipped(seq, p->flipped);
        Sequence_SetFlags(seq, p->flags);
        Sequence_SetVisibility(seq, GSmodelGetVisibility(model));
        p++;
    }
    memcpy(battleGridGetPtr(), grid, 0x44);
    fightMainAllCamera(1, 0);
    fightFloorSetShadow();
}

}

static u8 _fightGSfloorTrainerEvt(void* target, u16 id, void* data) {
    GSfloorScan* scan = (GSfloorScan*)data;
    u32 seq = fightEvtGetSequence();
    if (seq == 0) {
        return 1;
    }
    if (scan->collect != 0) {
        GSfloorTrainerEntry* e = (GSfloorTrainerEntry*)scan->next;
        e->target = 0;
        e->id = 0x40;
        e->flags = Sequence_GetFlags(seq);
        e->flipped = Sequence_IsFlipped(seq);
        e->bgSeq = (u32*)&seq;
        GSmodelPushState(Sequence_GetGSmodel(seq), &e->state);
        scan->next = (u8*)((GSfloorTrainerEntry*)scan->next + 1);
    }
    if (scan->consume != 0) {
        Sequence_Free(seq);
    }
    scan->count++;
    return 1;
}

static u8 _fightGSfloorPokemonCB(void* target, u16 id, void* data) {
    GSfloorScan* scan = (GSfloorScan*)data;
    GSfloorPokemonEntry* e;
    u32 seq;
    u16 seqId;
    seq = pokemonGetStatus(target, 0, 0xEE, 0);
    if (seq == 0) {
        return 1;
    }
    seqId = Sequence_GetID(seq);
    if (seqId == 0) {
        return 1;
    }
    if (scan->collect != 0) {
        e = (GSfloorPokemonEntry*)scan->next;
        e->target = (u32)target;
        e->id = seqId;
        e->flags = Sequence_GetFlags(seq);
        e->flipped = Sequence_IsFlipped(seq);
        e->rare = Sequence_IsRare(seq);
        e->rnd = Sequence_GetPokemonRndVal(seq);
        e->bgSeq = _fightGSfloorFindBGSeqPtr(scan->grid, seq, false);
        GSmodelPushState(Sequence_GetGSmodel(seq), &e->state);
        scan->next = (u8*)((GSfloorPokemonEntry*)scan->next + 1);
    }
    if (scan->consume != 0) {
        Sequence_Free(seq);
    }
    scan->count++;
    return 1;
}

static u8 _fightGSfloorTrainerCB(void* target, u16 id, void* data) {
    GSfloorScan* scan = (GSfloorScan*)data;
    GSfloorTrainerEntry* e;
    u32 seq;
    u16 seqId;
    seq = fightTrainerGetStatus(target, 0, 0x4C, 0);
    if (seq == 0) {
        return 1;
    }
    seqId = Sequence_GetID(seq);
    if (seqId == 0) {
        return 1;
    }
    if (scan->collect != 0) {
        e = (GSfloorTrainerEntry*)scan->next;
        e->target = (u32)target;
        e->id = seqId;
        e->flags = Sequence_GetFlags(seq);
        e->flipped = Sequence_IsFlipped(seq);
        e->bgSeq = _fightGSfloorFindBGSeqPtr(scan->grid, seq, true);
        GSmodelPushState(Sequence_GetGSmodel(seq), &e->state);
        scan->next = (u8*)((GSfloorTrainerEntry*)scan->next + 1);
    }
    if (scan->consume != 0) {
        Sequence_Free(seq);
    }
    scan->count++;
    return 1;
}

static u32* _fightGSfloorFindBGSeqPtr(battleGrid* grid, u32 seq, bool trainer) {
    GridRow* row;
    s32 i;
    s32 j;
    if (seq == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        row = &grid->rows[i];
        if (trainer == 1) {
            if (row->trainer == seq) {
                return &row->trainer;
            }
        } else {
            for (j = 0; j < 2; j++) {
                if (row->pokemon[j] == seq) {
                    return &row->pokemon[j];
                }
            }
        }
    }
    return 0;
}
