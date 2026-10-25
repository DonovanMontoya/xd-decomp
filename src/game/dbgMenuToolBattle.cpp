/* Debug menu entries for the battle tool (GBA coupon / connection toggles). */
#include <global.h>

extern "C" {
void menuCBDebug_SkipAGBConnection(u8);
void menuClose(s32);
s32 menuOpen(s32, s32);

volatile s32 dbgMenuGBAAddCoupon_value;
volatile s32 dbgMenuGBAResetCoupon_on;
volatile s32 dbgMenuGBASetClearFlag_on;
volatile s32 dbgMenuGBAClearCouponFlag_on;

// The retail build retains these unused debug menu entry points.
#pragma force_active on
s32 dbgMenuGBAClearCouponFlag(void) {
    dbgMenuGBAClearCouponFlag_on++;
    dbgMenuGBASetClearFlag_on = 0;
    return 0;
}

s32 dbgMenuGBASetClearFlag(void) {
    dbgMenuGBASetClearFlag_on += 1;
    return 0;
}

s32 dbgMenuGBAResetCoupon(void) {
    dbgMenuGBAResetCoupon_on++;
    dbgMenuGBAAddCoupon_value = 0;
    return 0;
}

s32 dbgMenuGBAAddCoupon(void) {
    s32 value = menuOpen(2, 1);

    menuClose(2);
    if (value >= 0) {
        dbgMenuGBAAddCoupon_value += value;
    }
    return 0;
}

s32 dbgToolBattleDebugSetAGBConnectionMode(s32 unused, s32 mode) {
    menuCBDebug_SkipAGBConnection(mode == 0);
    return 0;
}
#pragma force_active reset
}
