#ifndef PXDVS_APP_FLASHMENU_FLASHMENU_PRIVATE_HPP
#define PXDVS_APP_FLASHMENU_FLASHMENU_PRIVATE_HPP

#include <dolphin/types.h>

struct _PLACEOBJECT2;
struct _SHAPERECORD;
struct _DEFINETEXT;
struct _DEFINEFONT2;
struct _DEFINESHAPE;
struct _DEFINEMORPHSHAPE;
struct _DEFINESPRITE;
struct GStexture;
struct GSgfxLayer;
enum GSgfxLayerID { GSGFX_LAYER_ID_DUMMY };
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;

struct FLASHMATRIX {
    s32 m[6];
};
struct FLASHMATRIXF {
    f32 m[6];
};

struct FLASHCXFORM {
    f32 m[4];
};

struct FlashHeader {
    u8 reserved0[6];
    u16 frameCount;
    u8 reserved8[0xC];
    u32 relocated;
    u16 layerCount;
    u16 itemCount;
};

struct FlashItem {
    s16 frame;
    u8 reserved2[2];
    FLASHMATRIX matrix;
    f32 depth;
    FLASHCXFORM cxform;
    s32 field30;
    s32 field34;
    void *extra;
    u8 flag;
    u8 reserved3D[3];
};

struct FlashLayer {
    u32 reserved0;
    FlashItem *items;
};

struct FlashMenuLabel {
    u16 frame;
    u16 pad;
    char *name;
    FlashMenuLabel *next;
    FlashMenuLabel() : name(0), next(0) {}
};

struct FlashMenuTextureSlot {
    s32 id;
    GStexture *texture;
};

class FlashMenu {
public:
    u32 pos;
    u32 start;
    FlashHeader *header;
    u32 frameStart;
    u16 field10;
    u8 reserved12[2];
    u32 field14;
    s32 activeLayer;
    u16 activeFrame;
    u8 field1E;
    u8 reserved1F;
    u32 field20;
    u8 loop;
    u8 paused;
    u8 reserved26[2];
    u32 loopFrame;
    u32 endFrame;
    u32 totalFrames;
    u32 field34;
    void *memory;
    FlashItem *items;
    FlashLayer *layers;
    u32 playFrame;
    f32 fps;
    FlashMenuTextureSlot textures[30];
    FlashMenuLabel *labels;

    void Init(void*,unsigned long);
    FlashMenu();
    ~FlashMenu();
    GStexture *GetGStexture(long);
    u16 GetFrameFromLabel(char *);
    u32 GetPlayFrame();
    void SetPlayFrame(unsigned long);
    void ParsePlaceObject2(bool);
    void ParsePlaceObject2Sub(_PLACEOBJECT2 *);
    void Update();
    void InitDataPointer();
    void Draw(tagWINDOW_WORK *, tagSPRITE_WORK *);
    void Release();
    void DrawSub(GSgfxLayerID, tagWINDOW_WORK *, tagSPRITE_WORK *);
    void DrawSprite(_DEFINESPRITE*,FLASHMATRIXF*,FLASHCXFORM*,u16,u8);
    void DrawText(_DEFINETEXT*,FLASHMATRIXF*,FLASHMATRIXF*,FLASHCXFORM*,u8);
    unsigned char ParseTag(unsigned long, unsigned long, bool, bool, bool);
    void ParseDefineShapeSub(_DEFINESHAPE *);
    void ParseDefineMorphShapeSub(_DEFINEMORPHSHAPE *);
    void ParseDefineFont2Sub(_DEFINEFONT2 *);
    void ParaseTextRecord(_DEFINETEXT *);
    void BlendShapeRecord(_SHAPERECORD *, _SHAPERECORD *, _SHAPERECORD *, f32);
};

#endif
