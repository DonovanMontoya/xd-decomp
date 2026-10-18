#ifndef MENU_PCBOX_NEW_PRIVATE_HPP
#define MENU_PCBOX_NEW_PRIVATE_HPP
#include <dolphin/types.h>
struct tagWINDOW_WORK {u8 pad0;s8 mode,sub;u8 pad3;s32 id;};
struct tagSPRITE_WORK {u8 pad0[0x4C];u32 message;};
struct Pokemon {u8 data[0xC4];};
struct MenuPtWorkSound {u32 bgm,env;u8 volume[4];};
class CMenuGlobalState {public:
    enum enumCallFrom {Pc,Relive,Hologram,Tutorial};
    enumCallFrom from;
    s32 previous, current;
    u8 reservedC[0x150];
    u8 tutorial, tutorialExit, cancelExit;
    u8 reserved15F[0xA9];
    void init();
};
class CState {public:
    s32 current, next, previous;
    u8 reservedC[0xC];
    u8 work[0x40];
    u8 reserved58[0x50];
    void init();
    void update();
    void change(s32);
};
struct MenuBaseLayout {
    s32 fadeTime, fadeState;
    u8 sound[0x14];
    long windows[64];
    void *windowFuncs[64];
    long *windowTable;
    u8 keyInfo[0x1A];
    u8 reserved23A[2];
    s32 repeatCount;
    u16 lastKey;
    u8 tutorialActive;
    u8 reserved243[0x35];
    CState state;
    u32 time0, time1;
    u8 reserved328[4];
    u8 unk32C, reserved32D;
    u16 unk32E;
};
class CMetaMenuBase {public:union{u8 bytes[0x330];MenuBaseLayout base;u64 alignment;};};
class CMetaMenu:public CMetaMenuBase {public:virtual void drawAll()=0;virtual bool isAnimationStateNone();virtual void updateAll();virtual void tutorialExitKick();void localWindowSetTable(long*);void localWindowCreateAll();void localWindowDeleteAll();static long defautlLocalWindowOpenTable[];void systemFadeOutSetAndWait(f32);static void systemFadeInKick();void systemFadeWaitToEnd();};
class PCBOX {public:static PCBOX *getPointer();void init();void setPokemon(Pokemon*,signed char,signed char);};
class CReliveHall {public:static CReliveHall *getPointer();void init();void allocMakeBackup();void checkWithBackupSet();static u8 isOpen();};
#endif
