#include <dolphin/types.h>
#include <libc/string.h>

#pragma pool_strings off

struct GSvec { f32 x, y, z; };
struct GSmodel;
struct PeopleState {
    bool active, display, flag2, flag3;
    u32 flags, groupID, peopleID, objectID;
    u8 pad14[0x20];
    f32 angle, targetAngle;
    u8 pad3C[0xC];
    u8 moveType, mode, flag4A, motion;
    f32 speed;
    GSvec position, destination;
    u16 pointCount, pointIndex;
    GSvec* points;
    u8 pad70[0x2C];
    GSvec savedPosition;
    u8 padA8[0x10];
    u8 targetType;
    u8 padB9[3];
    GSvec targetPosition;
    u8 padC8[0x24];
    u32 targetGroupID, targetPeopleID;
    u8 padF4[0x5C];
    bool flag150;
};
struct tagPeopleWork {
    u8 used, saveFlags;
    u8 pad2[6];
    GSmodel* model;
    PeopleState state;
};
struct SavedFlags {
    u8 active:1, display:1, flag2:1, flag150:1, flag3:1, flag4A:1, unused0:2;
    u8 moveType:3, motion:3, mode:2;
    u8 targetType:2, unused2:6;
    u8 unused3[2];
};

extern "C" {
void* GSmemAllocClr(u32);
void GSmemFree(void*);
s32 peopleBiosGetMaxNum();
tagPeopleWork* peopleBiosGetWorkPtr(s32);
void peopleClose(u32, u32, u8);
void peopleOpen(u32, u32, u32);
void peopleAddCollision(u32, u32);
tagPeopleWork* peopleGet(u32, u32);
void peopleSetDisp(u32, u32, bool);
GSvec* GSmodelGetPositionPtr(GSmodel*);
GSvec* GSmodelGetRotationPtr(GSmodel*);
void GSmodelSetPosition(GSmodel*, GSvec*);
void GSmodelSetRotation(GSmodel*, GSvec*);
void GSlogWrite(const char*, ...);
void heroMoveTermEvent();
void gimmickBoxPop();
}

class GSBinReadStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    GSBinReadStream(void* data, s32 length) { begin = current = (u8*)data; size = length; }
    u8 read8() { return *current++; }
    u16 read16() { u16 n = ((u16)current[0] << 8) | (u16)current[1]; current += 2; return n; }
    u32 read32() { u8* p = current; u32 n = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]; current += 4; return n; }
    f32 readFloat() { union { u32 n; f32 f; f64 align; } value; value.n = read32(); return value.f; }
    void read(void* dst, u32 n) { memcpy(dst, current, n); current += n; }
    s32 tell() const { return current - begin; }
    void seek(s32 n) { current = begin + n; }
};
class GSBinWriteStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    void* allocation;
    u8 writing;
    GSBinWriteStream() { current = 0; allocation = 0; begin = 0; size = 0; writing = 0; }
    GSBinWriteStream(void* data, s32 length) { allocation = 0; current = (u8*)data; begin = (u8*)data; size = length; writing = 1; }
    ~GSBinWriteStream() { if (allocation) GSmemFree(allocation); }
    void countOnly() { current = 0; allocation = 0; begin = 0; size = 0x10000000; writing = 0; }
    void write8(u8 n) { if (!writing) current++; else *current++ = n; }
    void write16(u16 n) { if (!writing) current += 2; else { *current++ = n >> 8; *current++ = n; } }
    void write32(u32 n) { if (!writing) current += 4; else { *current++ = n >> 24; *current++ = n >> 16; *current++ = n >> 8; *current++ = n; } }
    void writeFloat(f32 n) { union { u32 n; f32 f; f64 align; } value; value.f = n; write32(value.n); }
    void write(const void* p, u32 n) { if (writing) memcpy(current, p, n); current += n; }
    s32 tell() const { return current - begin; }
    void seek(s32 n) { current = begin + n; }
};

static void _makeAnywaySaveData(GSBinWriteStream* stream);

extern "C" {
s32 peopleGetAnywaySaveSize() {
    GSBinWriteStream stream;
    stream.countOnly();
    _makeAnywaySaveData(&stream);
    return stream.tell();
}
}

static void _peopleRestoreAnywaySaveData(GSBinReadStream* stream) {
    s32 i, j;
    PeopleState* state;
    tagPeopleWork* people;
    SavedFlags flags;
    u8 count = stream->read8();
    s32 start = stream->tell();
    for (i = 0; i < peopleBiosGetMaxNum(); i++) {
        people = peopleBiosGetWorkPtr(i);
        if (people) people->saveFlags = 0;
    }
    for (j = 0; j < count; j++) {
        if (stream->read8()) {
            s32 startRecord = stream->tell();
            u16 length = stream->read16();
            stream->read(&flags, sizeof(flags));
            stream->read32();
            u32 group = stream->read32();
            u32 id = stream->read32();
            stream->read32();
            for (i = 0; i < peopleBiosGetMaxNum(); i++) {
                people = peopleBiosGetWorkPtr(i);
                state = &people->state;
                if (people->used && group == state->groupID && id == state->peopleID) {
                    people->saveFlags |= 1;
                    break;
                }
            }
            stream->seek(startRecord + length);
        }
    }
    for (i = 0; i < peopleBiosGetMaxNum(); i++) {
        people = peopleBiosGetWorkPtr(i);
        state = &people->state;
        if (!(people->saveFlags & 1)) peopleClose(state->groupID, state->peopleID, 1);
    }
    stream->seek(start);
    for (j = 0; j < count; j++) {
        if (stream->read8()) {
            stream->read16();
            stream->read(&flags, sizeof(flags));
            u32 savedFlags = stream->read32();
            u32 group = stream->read32();
            u32 id = stream->read32();
            u32 object = stream->read32();
            u8 found = 0;
            for (i = 0; i < peopleBiosGetMaxNum(); i++) {
                people = peopleBiosGetWorkPtr(i);
                state = &people->state;
                if (people->used && group == state->groupID && id == state->peopleID) { found = 1; break; }
            }
            if (!found) {
                peopleOpen(group, id, object);
                peopleAddCollision(group, id);
                people = peopleGet(group, id);
                state = &people->state;
            }
            u32 oldObject = state->objectID;
            GSmodel* model = people->model;
            state->active = flags.active;
            state->display = flags.display;
            state->flag2 = flags.flag2;
            state->flag150 = flags.flag150;
            state->flag3 = flags.flag3;
            state->flag4A = flags.flag4A;
            state->moveType = flags.moveType;
            state->motion = flags.motion;
            state->mode = flags.mode;
            state->targetType = flags.targetType;
            state->flags = savedFlags;
            state->groupID = group;
            state->peopleID = id;
            state->objectID = object;
            if (oldObject != state->objectID) {
                GSlogWrite("people %d (%08x) : objID error (%08x, %08x)\n", j, state->peopleID, oldObject, state->objectID);
                state->objectID = oldObject;
            }
            state->speed = stream->readFloat();
            state->motion = stream->read8();
            state->speed = stream->readFloat();
            stream->read(&state->position, sizeof(GSvec));
            stream->read(&state->destination, sizeof(GSvec));
            state->pointCount = stream->read8();
            if (state->pointCount) {
                state->pointIndex = stream->read8();
                state->points = (GSvec*)GSmemAllocClr(state->pointCount * sizeof(GSvec));
                for (s32 j = 0; j < state->pointCount; j++) stream->read(&state->points[j], sizeof(GSvec));
            }
            switch (state->targetType) {
            case 1: state->targetGroupID = stream->read32(); state->targetPeopleID = stream->read32(); break;
            case 2: stream->read(&state->targetPosition, sizeof(GSvec)); break;
            }
            if (model) {
                stream->read(GSmodelGetPositionPtr(model), sizeof(GSvec));
                stream->read(&state->savedPosition, sizeof(GSvec));
                state->angle = stream->readFloat();
                state->targetAngle = stream->readFloat();
                GSmodelGetRotationPtr(model)->y = state->angle;
                GSmodelGetPositionPtr(model);
                GSmodelSetPosition(model, GSmodelGetPositionPtr(model));
                GSmodelSetRotation(model, GSmodelGetRotationPtr(model));
                peopleSetDisp(state->groupID, state->peopleID, state->display);
            } else {
                state->angle = stream->readFloat(); state->angle = stream->readFloat();
                state->angle = stream->readFloat(); state->angle = stream->readFloat();
            }
        }
    }
}

extern "C" {
void peopleRestoreAnywaySaveData(void* data, s32 size) {
    GSBinReadStream object(data, size);
    GSBinReadStream* stream = &object;
    if (stream->read16() == 0x103 && stream->read8() == 4) {
        _peopleRestoreAnywaySaveData(stream);
        heroMoveTermEvent();
        gimmickBoxPop();
    }
}
void peopleMakeAnywaySaveData(void* data, s32 size) {
    GSBinWriteStream stream(data, size);
    _makeAnywaySaveData(&stream);
}
}

static void _makeAnywaySaveData(GSBinWriteStream* stream) {
    GSmodel* model;
    s32 count = peopleBiosGetMaxNum();
    stream->write16(0x103);
    stream->write8(4);
    stream->write8(count);
    for (s32 i = 0; i < peopleBiosGetMaxNum(); i++) {
        tagPeopleWork* people = peopleBiosGetWorkPtr(i);
        PeopleState* state = &people->state;
        if (!people->used || (state->peopleID & 0xFFFF0000) == 0x7FFE0000) {
            stream->write8(0);
        } else {
            stream->write8(1);
            s32 start = stream->tell();
            stream->write16(0);
            model = people->model;
            SavedFlags flags;
            flags.active = state->active;
            flags.display = state->display;
            flags.flag2 = state->flag2;
            flags.flag150 = state->flag150;
            flags.flag3 = state->flag3;
            flags.flag4A = state->flag4A;
            flags.moveType = state->moveType;
            flags.motion = state->motion;
            flags.mode = state->mode;
            flags.targetType = state->targetType;
            stream->write(&flags, sizeof(flags));
            stream->write32(state->flags);
            stream->write32(state->groupID);
            stream->write32(state->peopleID);
            stream->write32(state->objectID);
            stream->writeFloat(state->speed);
            stream->write8(state->motion);
            stream->writeFloat(state->speed);
            stream->write(&state->position, sizeof(GSvec));
            stream->write(&state->destination, sizeof(GSvec));
            stream->write8(state->pointCount);
            if (state->pointCount) {
                stream->write8(state->pointIndex);
                for (s32 j = 0; j < state->pointCount; j++) stream->write(&state->points[j], sizeof(GSvec));
            }
            switch (state->targetType) {
            case 1: stream->write32(state->targetGroupID); stream->write32(state->targetPeopleID); break;
            case 2: stream->write(&state->targetPosition, sizeof(GSvec)); break;
            }
            if (model) {
                stream->write(GSmodelGetPositionPtr(model), sizeof(GSvec));
                stream->write(&state->savedPosition, sizeof(GSvec));
                stream->writeFloat(GSmodelGetRotationPtr(model)->y);
                stream->writeFloat(state->targetAngle);
            } else {
                for (s32 j = 20; j > 0; j--) stream->write8(0);
            }
            int end = stream->tell();
            stream->seek(start);
            stream->write16(end - start);
            stream->seek(end);
            GSmodelGetPositionPtr(model);
        }
    }
}
