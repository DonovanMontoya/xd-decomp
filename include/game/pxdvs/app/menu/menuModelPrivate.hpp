#ifndef MENU_MODEL_PRIVATE_H
#define MENU_MODEL_PRIVATE_H

#include <dolphin/types.h>

struct GSlight;
struct GStexture;
struct Pokemon;

struct MENU_MODEL_LOAD {
    u8 isPokemon;   // 0x0
    u8 pad1[3];
    union Resource {
        u32 objectId;
        struct PokemonResource {
            u16 id;
            u16 waza;
        } p;
    } u;            // 0x4
    u32 rnd;        // 0x8
    u16 unkC;       // 0xC
    u8 shiny;       // 0xE
    u8 anim;        // 0xF
};

struct MENU_MODEL {
    MENU_MODEL() {}

    u8 state;               // 0x0
    u8 loading;             // 0x1
    u8 initialized;         // 0x2
    u8 enable;              // 0x3
    u8 clip;                // 0x4
    u8 pad5[7];
    f32 unkC;               // 0xC
    MENU_MODEL_LOAD req;    // 0x10
    MENU_MODEL_LOAD cur;    // 0x20
    u32 model;              // 0x30
    u32 waza;               // 0x34
    u32 nextModel;          // 0x38
    u32 nextWaza;           // 0x3C
    f32 angle[3];           // 0x40
    f32 offset[3];          // 0x4C
    u32 thread;             // 0x58
    s32 sizeX;              // 0x5C
    s32 sizeY;              // 0x60
    s32 sizeW;              // 0x64
    s32 sizeH;              // 0x68
    u32 camera;             // 0x6C
    GSlight* light[3];      // 0x70
    f32 zoom;               // 0x7C
    s32 unk80;              // 0x80
    u8 unk84;               // 0x84
    u8 pad85[3];
    f32 camRot[3];          // 0x88
    f32 mtx[12];            // 0x94
    u8 boundValid;          // 0xC4
    u8 pad[3];
    f32 boundSize[3];       // 0xC8
    f32 boundMin[3];        // 0xD4
    f32 boundMax[3];        // 0xE0
};

typedef char MenuModelLoadSizeCheck[sizeof(MENU_MODEL_LOAD) == 0x10 ? 1 : -1];
typedef char MenuModelSizeCheck[sizeof(MENU_MODEL) == 0xEC ? 1 : -1];

extern "C" {
s32 menuModelInit(MENU_MODEL *model, s32 width, s32 height);
s32 menuModelTerm(MENU_MODEL *model);
s32 menuModelLoadPokemon(MENU_MODEL *model, Pokemon *pokemon);
s32 menuModelFree(MENU_MODEL *model);
bool menuModelCheck(MENU_MODEL *model, u8 wait);
s32 menuModelSetSize(MENU_MODEL *model, s32 x, s32 y, s32 width, s32 height);
void menuModelAdjustCamera(MENU_MODEL *model);
void menuModelSetZoom(MENU_MODEL *model, f32 zoom);
GStexture *menuModelRender(MENU_MODEL *model);
}

#endif
