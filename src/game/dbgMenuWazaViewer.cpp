#include <global.h>

#pragma force_active on

extern "C" {
s32 dbgMenuWazaViewerChangeDisp(void) { return 0; }
s32 dbgMenuWazaViewerChangeRenderBoundingBox(void) { return 0; }
s32 dbgMenuWazaViewerChangeBackgroundVisibility(void) { return 0; }
s32 dbgMenuWazaViewerChangeShowStatusInfo(void) { return 0; }
s32 dbgMenuWazaViewerChangeDoCameraUpdate(void) { return 0; }
s32 dbgMenuWazaViewerChangeRenderNullJoints(void) { return 0; }
}

#pragma force_active reset
