#ifndef GAME_MENUHOLOGRAM_LAYOUT_HPP
#define GAME_MENUHOLOGRAM_LAYOUT_HPP
#include <dolphin/types.h>

// Partial views of the relive-hall helper types used by the hologram menu.
class Pokemon {
public:
    u8 data[0xC4];
    u16 getPokemonDataId() const;
    bool isDarkPokemon() const;
    u16 *getNicknamePtr();
};
class CMenuGlobalState {
public:
    s32 reserved0;
    s32 previous;
    s32 current;
};

union GSgfxColAu8 {
    u32 rgba;
    u8 channels[4];
};

class CReliveStage {
public:
    u8 reserved0[0x3D4];
    s8 firstDancer;
    bool isReliveReady();
    s32 getState();
    s32 getTempo();
    Pokemon *getVisitorPointer();
    Pokemon *getDancerPointer(long);
    s32 getDancerQuantity();
    void pickupVisitor(Pokemon &);
};

class PCBOX {
public:
    static PCBOX *getPointer();
    void addPokemonLastWatchBox(Pokemon *);
    bool isPokemonFull();
};

class CReliveHall {
public:
    static CReliveHall *getPointer();
    CReliveStage *getStage(long);
    bool isReliveReadyPokemonExist();
};

struct GStexture;
enum GSgfxLayerID { GSGFX_LAYER_0 };
enum GSgfxLayerOffset { GSGFX_OFFSET_0 };
enum GSgfxLayerType { GSGFX_TYPE_0 };

struct GSgfxVF;
struct GSmtx;
struct GSgfxLight;
struct LayerMatrixFrame { u32 flags; f32 matrix[3][4]; };
struct LayerMatrixStack { u32 reserved; LayerMatrixFrame *frame; };
struct LayerEffectPassState { u8 bytes[0xBC]; };
enum GSgfxTgenFunc { GSGFX_TGEN_0 };
enum GSgfxTgenSrc { GSGFX_TGEN_SRC_0 };
enum GSgfxCunitAlpha { GSGFX_CUNIT_ALPHA_0 };
enum GSgfxCunitSrc { GSGFX_CUNIT_SRC_0 };
enum GSgfxLightType { GSGFX_LIGHT_0 };
enum GSgfxDiffuseFunc { GSGFX_DIFFUSE_0 };

class GSgfxLayer {
public:
    u32 unk0;
    s32 flags;
    u8 reserved8[0xC68];
    u8 unkC70;
    u8 reservedC71[0xE3];
    s32 projectionType;
    f32 projectionScaleX;
    f32 projectionOffsetX;
    f32 projectionScaleY;
    f32 projectionOffsetY;
    f32 projectionScaleZ;
    f32 projectionOffsetZ;
    u8 reservedD70[0x1C];
    s32 unkD8C;
    s32 unkD90;
    u8 reservedD94[0x24];
    u8 unkDB8;
    u8 reservedDB9[0xF3];
    u8 unkEAC;
    u8 reservedEAD[0x3];
    s32 unkEB0;
    s32 unkEB4;
    s32 unkEB8;
    u8 reservedEBC[0xB4];
    s32 unkF70;
    s32 unkF74;
    s32 unkF78;
    s32 unkF7C;
    u8 reservedF80[0xF0];
    s32 unk1070;
    s32 unk1074;
    s32 unk1078;
    s32 unk107C;
    u8 reserved1080[0xF0];
    s32 unk1170;
    s32 unk1174;
    s32 unk1178;
    u8 unk117C;
    u8 reserved117D[0x3];
    s32 unk1180;
    u8 reserved1184[0x12C];
    s32 unk12B0;
    s32 unk12B4;
    s32 unk12B8;
    u8 unk12BC;
    u8 reserved12BD[0x3];
    s32 unk12C0;
    u8 reserved12C4[0x15C];
    s32 unk1420;
    u8 unk1424;
    u8 unk1425;
    u8 unk1426;
    u8 reserved1427[0x1];
    s32 unk1428;
    u8 reserved142C[0x84];
    u8 unk14B0;
    u8 reserved14B1[0x3];
    s32 unk14B4;
    s32 unk14B8;
    u8 reserved14BC[0x18];
    s32 unk14D4;
    s32 unk14D8;
    u8 reserved14DC[0x128];
    s32 copyState[4];
    u8 reserved1614[0x30];
    s32 blendMode;
    s32 blendSource;
    s32 blendDestination;
    s32 logicOperation;
    u8 reserved1654[0x2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 depthBeforeTexture;
    u8 reserved1659[0x3];
    u8 depthEnable;
    u8 reserved165D[0x3];
    s32 depthCompare;
    s32 unk1664;
    s32 unk1668;
    s32 unk166C;
    u8 unk1670;
    u8 unk1671;
    u8 unk1672;
    u8 reserved1673[0x11];
    f32 depthRangeNear;
    f32 depthRangeFar;
    u8 reserved168C[0x1A];
    u8 projectionDepthDirty;
    u8 projectionDepthEnabled;
    s32 dirty;
    s32 unk16AC;
    u8 reserved16B0[0x8];
    s32 unk16B8;
    s32 unk16BC;
    u8 reserved16C0[0xC];
    s32 unk16CC;
    s32 unk16D0;
    s32 unk16D4;
    s32 unk16D8;
    s32 unk16DC;
    s32 unk16E0;
    u8 reserved16E4[0x4];
    s32 unk16E8;
    s32 unk16EC;
    s32 unk16F0;
    s32 unk16F4;
    u8 reserved16F8[0x10];
    s32 copyDirty;
    s32 pixelDirty;
    u8 reserved1710[0x2C];
    s32 textureDirty;
    GStexture* texture0;
    GStexture* texture1;
    u8 reserved1748[0x18];
    s32 savedDirty;
    s32 unk1764;
    u8 reserved1768[0x8];
    s32 unk1770;
    s32 unk1774;
    u8 reserved1778[0xC];
    s32 unk1784;
    s32 unk1788;
    s32 unk178C;
    s32 unk1790;
    s32 unk1794;
    s32 unk1798;
    u8 reserved179C[0x4];
    s32 unk17A0;
    s32 unk17A4;
    s32 unk17A8;
    s32 unk17AC;
    u8 reserved17B0[0x10];
    s32 savedCopyDirty;
    s32 savedPixelDirty;
    u8 reserved17C8[0x2C];
    s32 savedTextureDirty;
    GStexture* savedTexture0;
    GStexture* savedTexture1;
    u8 reserved1800[0x18];
    LayerEffectPassState passes[2];
    LayerEffectPassState* currentPass;
    s32 pass;
    s32 primitiveType;
    GSgfxVF* vertexFormat;
    LayerMatrixStack* matrixStack;
    GStexture* frameBufferTexture;
    u8 reserved19A8[0xC];
    u32 savedClearColor;
    s8 distortionExponent;
    u8 reserved19B9[0x3];
    f32 distortionMatrix[2][3];
    void tgenFunc(u8, GSgfxTgenFunc, GSgfxTgenSrc, GSmtx *, bool, GSmtx *);
    void cunitChannelGen(u8, GSgfxCunitAlpha, GSgfxCunitSrc, GSgfxCunitSrc, unsigned long, GSgfxLight **, GSgfxLightType, GSgfxDiffuseFunc);
    void beginSurface(u16);
    void endSurface();
    void SetClearFlags(bool, bool, bool);
    void SetTextureCopy(GStexture *, bool, unsigned char *);
};

class GSgfxLayerConfig {
public:
    static void Remove(GSgfxLayerID);
    static long Add(char *, unsigned long, unsigned long, unsigned long, GSgfxLayerType, bool, bool, bool, GSgfxLayerID, GSgfxLayerOffset);
    static void Move(GSgfxLayerID, GSgfxLayerID, GSgfxLayerOffset);
};

class CMetaMenu;

class CInfoWindow {
public:
    u8 reserved0[0x34];
    void exec(CMetaMenu &, u32, bool);
    void draw();
    void open(u32, bool);
    void close();
    void init(long, u32);
    void setMsgCtrlValue(u32, u32);
};

class CState {
public:
    s32 current;
    s32 next;
    u8 reserved8[0x10];
    u8 work[0x40];
    u8 reserved58[0x50];
    void init();
    void update();
    void change(s32);
};

struct MetaKeyInfo {
    u16 on, off, trigger, repeat, released;
};

class CMetaMenu {
public:
    s32 fadeTime;
    s32 fadeState;
    u8 sound[0x14];
    long windows[64];
    void *windowFuncs[64];
    long *windowTable;
    u8 keyInfo[0x1A];
    u8 reserved23A[2];
    s32 repeatCount;
    u16 lastKey;
    u8 tutorialActive;
    u8 reserved243[0x278 - 0x243];
    CState state;
    u32 time0;
    u32 time1;
    u8 reserved328[4];
    u8 unk32C;
    u8 reserved32D;
    u16 unk32E;
    static long defautlLocalWindowOpenTable[];
    virtual void drawAll() = 0;
    virtual bool isAnimationStateNone();
    virtual void updateAll();
    virtual void tutorialExitKick();
    MetaKeyInfo *getKeyInfo();
    void aButtonWait();
    f32 calcAnimationTimeRate0to1(f32);
    void localWindowDrawAll();
    void waitAtTime(f32);
    void systemFadeWaitToEnd();
    void systemFadeOutSetAndWait(f32);
    static void systemFadeInKick();
    static void systemFadeOutKeepAfterFloorPush();
    int actionMenu(u32 *, int, long, long);
    static void localWindowDeleteAll();
    void localWindowCreateAll();
    void localWindowSetTable(long *);
};

struct ModelSlot {
    s32 script;
    void *model;
    u32 sequence;
    s32 getAnimIndex();
    void setAnim(s32);
};

namespace {

class CMenuHologram : public CMetaMenu {
public:
    u8 reserved334[4];
    s32 stageIndex;
    s32 stageIndex2;
    CReliveStage *stage;
    u8 unk344;
    u8 reserved345[3];
    s32 lights[8];
    s32 lightCount;
    GStexture *offscreenTexture;
    u32 resGroup;
    u8 stageLoaded;
    u8 unk375;
    u8 reserved376[2];
    void *stageModel;
    u32 unk37C;
    u32 unk380;
    u32 unk384;
    ModelSlot slots[7];
    CInfoWindow infoWindow;
    CMenuGlobalState *globalState;
    u8 reserved414[4];

    virtual void drawAll();
    void stateReliveCeremony();
    void stateMainProc();
    void renderOffscreenData();
    void setStage(int);
    void setStageToReliveReady();
    void moveStageWait(int);
    void reloadDatas(bool);
    void unloadDatas();
    GSgfxColAu8 pokemonToAisyouColor(Pokemon *, Pokemon *);
    static s32 model_z_layer;
    void releaseOffscreenData();
    void initializeOffscreenData();
    void bgmStop();
    void bgmKick();
    void stageAllModelLoad();
    void stageAllModelUnLoad();
    void modelVisitorSetYPosition(long);
    ModelSlot *modelPokemonSetScale(long);
    ModelSlot *modelPokemonLoad(long);
    int actionYesNo(u32, bool);
    void init(CMenuGlobalState &);
    void main(CMenuGlobalState &);
    void loop();
};

}

#endif
