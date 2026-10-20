#include <global.h>
#include <dolphin/os/OSFastCast.h>

extern "C" s64 OSGetTime(void);
extern "C" void GSmathInitCosTable();
extern u32* __hsd_rand_seed_hold;

extern "C" void GSmathInit() {
    register u32 gqr6;

    OSInitFastCast();
    gqr6 = 0x06070607;
    asm { mtspr GQR6, gqr6 }
    *__hsd_rand_seed_hold = OSGetTime();
    GSmathInitCosTable();
}
