#include <dolphin/types.h>

/* Both symbol maps give this state object 0x38 bytes. dbgMenuWaza.cpp
 * accesses the two bytes at 0x16/0x17 and the signed word at 0x30. */
typedef struct WazaViewerData {
    u8 unknown00[0x16];
    u8 unknown16;
    u8 unknown17;
    u8 unknown18[0x18];
    s32 unknown30;
    u8 unknown34[4];
} WazaViewerData;

WazaViewerData wazaViewerData;
