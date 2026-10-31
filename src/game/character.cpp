#include <global.h>
#pragma force_active on

// The retail split also owns the shared performance-bar color cache.
#pragma dollar_identifiers on
extern "C" {
__declspec(weak) u32 c$localstatic3$GSgfxPerfColorToGSgfxCol;
}

extern "C" void characterInit() {}
#pragma force_active reset
