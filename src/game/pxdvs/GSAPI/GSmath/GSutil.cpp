#include <global.h>

extern "C" f64 cos(f64);

f32 gCosTable[181];

struct CosTableDegrees { f32 step; };
struct DegreesToRadians { f32 factor; };
static const CosTableDegrees cosTableDegrees = {0.5f};
static const DegreesToRadians degreesToRadians = {0.017453292f};

extern "C" void GSmathInitCosTable() {
    for (s32 i = 0; i < 181; i++) {
        f32 degrees = cosTableDegrees.step * i;
        gCosTable[i] = cos(degreesToRadians.factor * degrees);
    }
}
