#ifndef FLOOR_OFFSCREEN_PRIVATE_HPP
#define FLOOR_OFFSCREEN_PRIVATE_HPP
#include <global.h>
#include <game/pxdvs/app/floor/floorData.hpp>
struct FloorOffscreenData {
    u8 kind, animation;
    u16 index, width, height;
    u32 target, source, camera;
};
struct FloorOffscreenBundle {u32* count; FloorOffscreenData* records;};
typedef char FloorOffscreenRecordSize[sizeof(FloorOffscreenData)==0x14?1:-1];
#endif
