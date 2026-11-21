#ifndef GAME_PXDVS_GSAPI_GSCOLSYS_GSCOLSYS2_STATE_HPP
#define GAME_PXDVS_GSAPI_GSCOLSYS_GSCOLSYS2_STATE_HPP

#include <dolphin/types.h>
#include <libc/stddef.h>

struct CCD_FILEHEAD;
struct DLDisplayList;
struct GSgfxVF;

struct GSCOLSYS2_OBJ {
    f32 position[3], rotation[3], scale[3];
    u16 flags, padding;
    GSCOLSYS2_OBJ() {}
};

struct GSCOLSYS2_HUMAN {
    s32 group;
    u32 resource;
    f32 radius, height;
    u16 flags, padding;
};

struct GSCOLSYS2_FLOOR {
    GSCOLSYS2_OBJ objects[64];
    GSCOLSYS2_HUMAN humans[48];
    GSCOLSYS2_FLOOR() {}
};

struct GSCOLSYS2_STATE {
    CCD_FILEHEAD *head;
    GSCOLSYS2_FLOOR floor[1];
    s32 currentFloor;
    GSgfxVF *format;
    DLDisplayList *displayList;
};

typedef char ColsysObjectSizeCheck[sizeof(GSCOLSYS2_OBJ) == 0x28 ? 1 : -1];
typedef char ColsysFloorSizeCheck[sizeof(GSCOLSYS2_FLOOR) == 0xdc0 ? 1 : -1];
typedef char ColsysStateSizeCheck[sizeof(GSCOLSYS2_STATE) == 0xdd0 ? 1 : -1];
typedef char ColsysCurrentFloorOffsetCheck[offsetof(GSCOLSYS2_STATE, currentFloor) == 0xdc4 ? 1 : -1];
typedef char ColsysObjectFlagsOffsetCheck[offsetof(GSCOLSYS2_OBJ, flags) == 0x24 ? 1 : -1];
typedef char ColsysHumanSizeCheck[sizeof(GSCOLSYS2_HUMAN) == 0x14 ? 1 : -1];
typedef char ColsysHumanFlagsOffsetCheck[offsetof(GSCOLSYS2_HUMAN, flags) == 0x10 ? 1 : -1];
typedef char ColsysHumanArrayOffsetCheck[offsetof(GSCOLSYS2_FLOOR, humans) == 0xa00 ? 1 : -1];
typedef char ColsysFormatOffsetCheck[offsetof(GSCOLSYS2_STATE, format) == 0xdc8 ? 1 : -1];

extern "C" {
extern GSCOLSYS2_STATE GScolsys2;
GSCOLSYS2_FLOOR *GScolsys2GetCurFloor(void);
}

#endif
