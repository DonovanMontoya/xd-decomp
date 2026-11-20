#ifndef FLOOR_DATA_HPP
#define FLOOR_DATA_HPP

#include <dolphin/types.h>
#include <libc/stddef.h>

struct FloorRenderData;
struct FloorCharacterList;
struct FloorPositionList;
struct FloorOffscreenBundle;

struct FieldCameraEntry {
    u8 isBox;           // 0x0
    u8 pad01[3];
    f32 x;              // 0x4
    f32 y;              // 0x8
    f32 z;              // 0xC
    f32 distance;       // 0x10
    f32 height;         // 0x14
    f32 rotY;           // 0x18
    f32 radius;         // 0x1C
    f32 ratio;          // 0x20
    f32 angle;          // 0x24
    f32 pow;            // 0x28
    f32 blendTime;      // 0x2C
    f32 fov;            // 0x30
};

struct FieldCameraList {
    u32* count;
    FieldCameraEntry* entries;
};

typedef char FieldCameraEntrySize[sizeof(FieldCameraEntry) == 0x34 ? 1 : -1];

struct GSfloor_dd_ {
    u8 area, kind;
    u16 floorID;
    u32 mapResourceID;
    FloorRenderData **render;
    FloorCharacterList **characters;
    FloorPositionList **positions;
    FieldCameraList **fieldCameras;
    u32 placeNameID;
    void (*preFunction)(GSfloor_dd_ *, u32);
    void (*mainFunction)();
    void (*postFunction)(GSfloor_dd_ *, u32);
    FloorOffscreenBundle **offscreen;
    u32 languageGroupIDs[5];
};

typedef char FloorDataSizeCheck[sizeof(GSfloor_dd_) == 0x40 ? 1 : -1];
typedef char FloorDataOffscreenOffset[offsetof(GSfloor_dd_, offscreen) == 0x28 ? 1 : -1];
typedef char FloorDataGroupOffset[offsetof(GSfloor_dd_, languageGroupIDs) == 0x2C ? 1 : -1];

extern "C" {
GSfloor_dd_ *floorDataBiosGetCurrentPtr();
GSfloor_dd_ *floorDataBiosGetPtr(u32 floorID);
FieldCameraList *floorDataBiosGetFieldCameraListPtr(GSfloor_dd_ *floor);
}

#endif
