#include <game/sysvarsPrivate.hpp>
#include <libc/string.h>

struct _GSgfxInitParms {
    u8 halt;
    u8 pad1[3];
    u8 buffers;
    u8 pad5;
    u16 height;
    s32 mode;
    u32 a, b, c;
};

extern "C" {
void pokecoloInitRomVersion();
void sysvarsReadSettings(int *, char ***);
void sysvarsShowDebug();
u32 OSGetConsoleSimulatedMemSize();
void *OSGetArenaLo();
void *OSGetArenaHi();
void OSSetArenaLo(void *);
void OSSetArenaHi(void *);
void *GSmemInit(void *, void *, int);
void GSfsysCreateLocalHeap();
void GSfsysCreateCacheHeap();
void floorCreateLocalHeap();
s32 GSmemCreateHeap(void *, void *);
s32 GSmemSetCurrentHeap(s32);
void GSmemInitSysdolAllocator();
s32 pokecoloGetCountryCode();
void ARInit(u32 *, u32);
void ARQInit();
void AIInit(u8 *);
void ARQSetChunkSize(u32);
void GSlogInit(u32, u32);
void GSscratchInit(u32);
void GSdvdSetDVDServer(const char *, u16);
void GSdvdSetReportServer(const char *, u16, u8);
void GSdvdSetGCClient(const char *, const char *, const char *, u8);
void pokecoloMain(int, char **);
}
void GSgfxInit(_GSgfxInitParms *);

extern SystemVars systemVars;

static u8 aiStackMem[0x4000];
static u32 aramMemArray[2];
s32 g_hFloorHeap;
s32 g_hSysdolphineHeap;

extern "C" void main(int argc, char **argv) {
    void *lo;
    void *hi;
    _GSgfxInitParms parms;
    pokecoloInitRomVersion();
    memset((void *)0x80001800, 0, 0x1800);
    sysvarsReadSettings(&argc, &argv);
    if (OSGetConsoleSimulatedMemSize() > 0x1800000) {
        if (systemVars.gsmemsize == 24) {
            OSSetArenaHi((void *)0x817ED780);
        } else if (systemVars.gsmemsize == 48) {
            OSSetArenaHi((void *)0x82DED720);
        }
    }
    lo = OSGetArenaLo();
    OSGetArenaHi();
    OSSetArenaLo(GSmemInit(lo, OSGetArenaHi(), 4));
    GSfsysCreateLocalHeap();
    GSfsysCreateCacheHeap();
    floorCreateLocalHeap();
    lo = OSGetArenaLo();
    hi = OSGetArenaHi();
    g_hFloorHeap = GSmemCreateHeap(lo, hi);
    GSmemSetCurrentHeap(g_hFloorHeap);
    OSSetArenaLo(hi);
    g_hSysdolphineHeap = g_hFloorHeap;
    GSmemInitSysdolAllocator();
    parms.halt = systemVars.errortrap != 0;
    parms.a = 0x50000;
    parms.b = 0x50000;
    parms.c = 0x10;
    switch (pokecoloGetCountryCode()) {
    case 0:
    case 1:
        parms.mode = 0;
        break;
    case 2:
        parms.mode = 1;
        break;
    }
    parms.buffers = 2;
    parms.height = 0x1E0;
    GSgfxInit(&parms);
    if (systemVars.debugsysvars == 1) sysvarsShowDebug();
    ARInit(aramMemArray, 2);
    ARQInit();
    AIInit(aiStackMem + 0x3FF8);
    ARQSetChunkSize(0x8000);
    GSlogInit(0x8000, 2);
    GSscratchInit(0);
    GSdvdSetDVDServer(systemVars.localip, systemVars.serverport);
    GSdvdSetReportServer(systemVars.localip, systemVars.outputport, 1);
    GSdvdSetGCClient(systemVars.gamecubeip, systemVars.netmask, systemVars.gateway, 1);
    pokecoloMain(argc, argv);
}
