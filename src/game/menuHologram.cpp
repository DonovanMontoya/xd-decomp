#include <game/menuHologramLayout.hpp>

extern "C" {
void *GSmemAllocClr(u32);
void GSmemFree(void *);
void GSmodelSetAnimIndex(void *, s32);
void GSmodelSetAnimType(void *, s32);
void GSmodelStartAnimation(void *);
void *GSresGetResourceAllGroup(u32);
GSgfxLayer *GSgfxLayerFindByID(GSgfxLayerID);
void Sequence_SetVisibility(u32, s32);
void Sequence_Free(u32);
void WazaSequence_Free(u32);
void GSmodelSetVisibility(void *, s32);
void scriptModelClose(s32);
void GSlightFree(s32);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
void cameraSetType(s32);
void GSmodelFree(void *);
void *memset(void *, int, u32);
void Sequence_SetPosition(u32, f32 *);
u32 Sequence_LoadPokemon(u16, u32, s32);
void *Sequence_GetGSmodel(u32);
u32 Sequence_LoadWaza(u32, u16, s32, s32);
void WazaSequence_Start(u32, s32);
void Sequence_DoAnimation(u32, u8);
void GSmodelSetForceUseFractionalFramesFlag(void *, s32);
void GSmodelSetSkipFractionalFramesFlag(void *, s32);
s32 menuModelGetPokemonAnimationIndexByPointer(Pokemon *);
u8 pokemonIsJoutaiDataId(Pokemon *, s32);
s32 pokemonGetStatus(Pokemon *, s32, s32, s32);
void Sequence_SetScale(u32, f32 *);
struct ReliveHallData {
    u8 reserved0[4];
    u16 unk4;
};
extern ReliveHallData *relivehall_data;
void *memcpy(void *, const void *, u32);
void GStextureFree(GStexture *);
GStexture *GStextureCreate(s32, s32, s32, s32, s32);
void *HSD_ArchiveGetPublicAddress(void *, const char *);
u32 soundGetBGMID(void);
void soundStop(u32, s32);
void GSflagSet(u32, s32);
void GSmodelGetAnimIndex(void *, s32 *, s32);
u8 GSmodelHasAnimationEnded(void *);
void GSmodelSetPosition(void *, f32 *);
void GSmodelSetRotation(void *, f32 *);
void GSmodelSetScale(void *, f32 *);
void GSthreadSwitch();
u32 windowGetKeyTrg();
u32 windowGetKeyOn();
s32 floorGetCurrentGroupID();
void cameraPlayAnime(s32, u32, f32, s32);
void GScharCpy(u16 *, u16 *);
void menuDrawReliveUpdate();
extern GSgfxColAu8 GSgfxColAu8_Black;
extern GSgfxColAu8 relivehallAisyou2ColorTbl[];
}

s32 reliveHallPokemonToAisyou(Pokemon *, Pokemon *);
extern u8 pcReliveHallSoundTbl[];
long relivehallGetLastViewStage(void);
void menuModelGetPkxRndFromPokemonForSeqenceLoad(unsigned long &, unsigned short &, Pokemon *);
f32 menuGetPokemonScale(u32, int);
void menuPtPlayBgm(u32);
void menuPtPlaySe(u32);
extern "C" int actionMenu__9CMetaMenuFPUlill(CMetaMenu *, u32 *, int, long, long, long);
void relivehallSetLastViewStage(long);
void relivehallDraw9StageNumber(int);
void relivehallDraw9StageInfo(int);
void relivehallDrawStageInfoCursor(long, int, int, Pokemon *, bool);
u32 reliveCeremonyFromHologram(Pokemon *, unsigned long);

inline void *operator new(unsigned long, void *p)
{
    return p;
}

struct GSpart;
enum GSpartMixType { GSPART_MIX_0 };

struct GSvec {
    f32 x;
    f32 y;
    f32 z;
    GSvec(f32 ax, f32 ay, f32 az)
    {
        x = ax;
        y = ay;
        z = az;
    }
};


extern "C" {
s32 scriptModelOpen(u32);
void GSfsysReadWait(u32);
void GSmodelSetRenderLayer(void *, s32, GSgfxLayerID *);
GSpart *GSmodelGetPart(void *, s32);
void GSmodelAttachToGSpart(void *, GSpart *, s32, s32, s32);
void GSpartFree(GSpart *);
void GSmodelDisableModulation(void *);
void GSmaterialSetModulate(void *, GSgfxColAu8 *);
void GSmaterialEnableExtension(void *, s32);
s32 GSlightLoad(u32);
void GSlightSetActive(s32, s32);
u8 GSlightCanAnimate(s32);
void GSlightSetAnimIndex(s32, s32);
void GSlightSetAnimRate(s32, f32);
void GSlightStartAnimation(s32);
void floorReadMakeLightResID(u32);
void *floorOpenObject(u32);
void GSmodelSetAnimRate(void *, f32);
void *peopleInfoBiosGetPtr(u32);
s8 peopleInfoBiosGetNeckIndex(void *);
void GSpartRegisterAnimMix(GSpart *, s32, s32, f32 (*)(GSpart *, GSpartMixType, void *, GSvec *), void *);
u32 Sequence_CreateNull();
void Sequence_SetRotation(u32, f32 *);
}

extern "C" {
GSgfxVF *GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void spriteSetOffset(s32, s32, s32);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void GSmtx44Ortho(f32 *, f32, f32, f32, f32, f32, f32);
extern f32 mtxIdent[3][4];
}
struct HologramTextureFlags { u8 reserved0[7]; u8 dirty; };

inline void CState::change(s32 n)
{
    next = n;
    memset(work, 0, 0x40);
}

namespace {

CMenuHologram *pMenuHologram;

void thisExec(CMenuGlobalState &);
void thisFree();
void thisNew();

void thisExec(CMenuGlobalState &state)
{
    thisNew();
    pMenuHologram->main(state);
    thisFree();
}

void thisFree()
{
    if (pMenuHologram != 0) {
        GSmemFree(pMenuHologram);
        pMenuHologram = 0;
    }
}

void thisNew()
{
    CMenuHologram *p = (CMenuHologram *)GSmemAllocClr(0x418);
    new (p) CMenuHologram;
    pMenuHologram = p;
}

f32 _getNeckRotationCB(GSpart *, GSpartMixType, void *, GSvec *out)
{
    static GSvec neckRotVec(-0.7853982f, 0.0f, 0.0f);
    *out = neckRotVec;
    return 1.0f;
}

inline s32 ModelSlot::getAnimIndex()
{
    s32 index;
    if (model == 0) {
        return 0;
    }
    GSmodelGetAnimIndex(model, &index, 0);
    return index;
}

inline void ModelSlot::setAnim(s32 index)
{
    if (model != 0) {
        GSmodelSetAnimIndex(model, index);
        GSmodelSetAnimType(model, 1);
        GSmodelStartAnimation(model);
    }
}

void CMenuHologram::drawAll()
{
    if (stageModel != 0) {
        static GSvec pos(0.0f, 0.0f, 0.0f);
        static GSvec rot(0.0f, 3.1415927f, 0.0f);
        static GSvec scl(1.0f, 1.0f, 1.0f);
        GSmodelSetPosition(stageModel, &pos.x);
        GSmodelSetRotation(stageModel, &rot.x);
        GSmodelSetScale(stageModel, &scl.x);
    }
    renderOffscreenData();
    if (unk375 == 0) {
        if (slots[0].model != 0) {
            s32 anim = slots[0].getAnimIndex();
            if (anim == 1 || anim == 3) {
                if (GSmodelHasAnimationEnded(slots[0].model)) {
                    {
                        s32 next = anim + 1;
                        slots[0].setAnim(next);
                    }
                }
            }
        }
        if (slots[1].model != 0) {
            s32 anim = slots[1].getAnimIndex();
            if (anim == 1 || anim == 3) {
                if (GSmodelHasAnimationEnded(slots[1].model)) {
                    {
                        s32 next = anim + 1;
                        slots[1].setAnim(next);
                    }
                }
            }
        }
        if (unk344 != 0) {
            f32 t = calcAnimationTimeRate0to1(32.0f);
            f32 v[3];
            v[0] = 0.0f;
            v[2] = 0.0f;
            v[1] = 2.0f * (3.1415927f * -t);
            GSmodelSetRotation(slots[1].model, v);
        }
        {
            CReliveStage *st = CReliveHall::getPointer()->getStage(stageIndex2);
            s32 tempo = st->getTempo();
            bool cursor;
            relivehallDraw9StageNumber(stageIndex);
            relivehallDraw9StageInfo(stageIndex2);
            cursor = false;
            if (state.current != 4 && state.current != 7) {
                cursor = true;
            }
            relivehallDrawStageInfoCursor(stageIndex2, tempo, st->getDancerQuantity(), st->getVisitorPointer(), cursor);
            infoWindow.draw();
            localWindowDrawAll();
            menuDrawReliveUpdate();
        }
    }
}

void CMenuHologram::stateReliveCeremony()
{
    Pokemon copy;
    u16 name[12];
    Pokemon *visitor;
    u32 trigger;
    GSflagSet(0x5A3, 1);
    unk344 = 0;
    for (;;) {
        if (slots[1].getAnimIndex() == 2) {
            break;
        }
        updateAll();
    }
    aButtonWait();
    menuPtPlayBgm(0x5A8);
    menuPtPlaySe(0x5A7);
    cameraPlayAnime(floorGetCurrentGroupID(), 0x18E21800, 0.0f, 0);
    cameraSetType(4);
    if (slots[0].model != 0) {
        GSmodelSetAnimIndex(slots[0].model, 3);
        GSmodelSetAnimType(slots[0].model, 0);
        GSmodelStartAnimation(slots[0].model);
    }
    waitAtTime(0.3f);
    GSmodelSetVisibility(stageModel, 0);
    waitAtTime(6.0f);
    visitor = stage->getVisitorPointer();
    unk375 = 1;
    unk384 = reliveCeremonyFromHologram(visitor, slots[2].sequence);
    unk375 = 0;
    systemFadeInKick();
    systemFadeWaitToEnd();
    GScharCpy(name, visitor->getNicknamePtr());
    do {
        GSthreadSwitch();
        trigger = windowGetKeyTrg();
    } while ((u16)windowGetKeyOn() != 0 || (u16)trigger != 0);
    infoWindow.setMsgCtrlValue(0x32, (u32)name);
    infoWindow.exec(*this, 0xD15E, true);
    stage->pickupVisitor(copy);
    PCBOX::getPointer()->addPokemonLastWatchBox(&copy);
    if (CReliveHall::getPointer()->isReliveReadyPokemonExist()) {
        systemFadeInKick();
        if (PCBOX::getPointer()->isPokemonFull()) {
            infoWindow.exec(*this, 0xD132, true);
            state.change(7);
        } else if (actionYesNo(0xD131, true) == 0) {
            systemFadeOutSetAndWait(-1.0f);
            setStageToReliveReady();
            reloadDatas(true);
            systemFadeInKick();
            state.change(4);
        } else {
            state.change(7);
        }
    } else {
        state.change(7);
    }
}

void CMenuHologram::stateMainProc()
{
    do {
        MetaKeyInfo *key = getKeyInfo();
        if ((key->trigger | key->repeat) != 0) {
            switch (key->repeat) {
            case 4:
            case 0x200:
                stageIndex2 = (stageIndex2 + 8) % 9;
                menuPtPlaySe(0x45F);
                break;
            case 8:
            case 0x400:
                stageIndex2 = (stageIndex2 + 1) % 9;
                menuPtPlaySe(0x45F);
                break;
            }
            switch (key->trigger) {
            case 0x10:
                menuPtPlaySe(0x45A);
                state.change(3);
                break;
            case 0x20:
                menuPtPlaySe(0x45B);
                state.change(6);
                break;
            }
        }
        updateAll();
    } while (state.next == -1);
}

void CMenuHologram::setStage(int index)
{
    stageIndex = index;
    stageIndex2 = index;
    stage = CReliveHall::getPointer()->getStage(stageIndex);
}

void CMenuHologram::setStageToReliveReady()
{
    int i = 0;
    do {
        if (CReliveHall::getPointer()->getStage(i)->isReliveReady()) {
            break;
        }
        i++;
    } while (i < 9);
    if (i == 9) {
        setStage(relivehallGetLastViewStage());
    } else {
        setStage(i);
    }
}

void CMenuHologram::moveStageWait(int index)
{
    systemFadeOutSetAndWait(0.1f);
    unloadDatas();
    setStage(index);
    reloadDatas(true);
    systemFadeInKick();
}

void CMenuHologram::reloadDatas(bool kick)
{
    stageAllModelLoad();
    if (slots[0].model != 0) {
        GSmodelSetAnimIndex(slots[0].model, 2);
        GSmodelSetAnimType(slots[0].model, 1);
        GSmodelStartAnimation(slots[0].model);
    }
    if (slots[1].model != 0) {
        GSmodelSetAnimIndex(slots[1].model, 2);
        GSmodelSetAnimType(slots[1].model, 1);
        GSmodelStartAnimation(slots[1].model);
    }
    localWindowCreateAll();
    if (kick) {
        bgmKick();
    }
}

static long localWindowTable[] = { 0x71, 0x72, 0x88, 0xD0, 0x87, 0 };

int CMenuHologram::actionYesNo(u32 message, bool exec)
{
    static u32 msgTbl[2] = { 0x426A, 0x426B };
    int result;
    if (exec) {
        infoWindow.exec(*this, message, false);
    } else {
        infoWindow.open(message, false);
    }
    result = actionMenu__9CMetaMenuFPUlill(this, msgTbl, 2, 0x1FE, 0x7F, 0);
    infoWindow.close();
    return result;
}

void CMenuHologram::loop()
{
    state.change(1);
    for (;;) {
        state.update();
        switch (state.current) {
        case 0:
            break;
        case 1:
            if (stage->isReliveReady()) {
                state.change(4);
            } else {
                state.change(2);
            }
            break;
        case 2:
            unk344 = 1;
            stateMainProc();
            break;
        case 3: {
            static u32 msgTbl[3] = { 0xD134, 0xD135, 0xD136 };
            switch (actionMenu__9CMetaMenuFPUlill(this, msgTbl, 3, 0x1B8, 0x78, 0)) {
            case 0:
                state.change(5);
                break;
            case 1:
                moveStageWait(stageIndex2);
                state.change(2);
                break;
            case 2:
                state.change(2);
                break;
            }
            break;
        }
        case 4:
            stateReliveCeremony();
            break;
        case 5:
            relivehallSetLastViewStage(stageIndex2);
            systemFadeOutSetAndWait(-1.0f);
            {
                CMenuGlobalState *g = globalState;
                g->previous = g->current;
                g->current = 2;
            }
            return;
        case 6:
            if (actionYesNo(0xD15C, false) == 0) {
                state.change(2);
            } else {
                state.change(8);
            }
            break;
        case 7:
        case 8:
            relivehallSetLastViewStage(stageIndex);
            systemFadeOutSetAndWait(-1.0f);
            {
                CMenuGlobalState *g = globalState;
                g->previous = g->current;
                g->current = 0;
            }
            return;
        }
    }
}

void CMenuHologram::init(CMenuGlobalState &gstate)
{
    time1 = 0;
    time0 = 0;
    state.init();
    fadeTime = 0;
    fadeState = 0;
    memset(windows, 0, 0x100);
    memset(windowFuncs, 0, 0x100);
    windowTable = defautlLocalWindowOpenTable;
    if (pcReliveHallSoundTbl != 0) {
        memcpy(sound, pcReliveHallSoundTbl, 0x14);
    }
    tutorialActive = 0;
    unk32C = 0;
    unk32E = 0;
    memset(keyInfo, 0, 0x1A);
    repeatCount = 0;
    lastKey = 0;
    unk375 = 0;
    stageIndex = 0;
    stageIndex2 = 0;
    stage = 0;
    unk344 = 0;
    memset(lights, 0, sizeof(lights));
    lightCount = 0;
    offscreenTexture = 0;
    stageLoaded = 0;
    unk37C = 0;
    unk380 = 0;
    unk384 = 0;
    globalState = &gstate;
    localWindowSetTable(localWindowTable);
    infoWindow.init(0xD0, 0x5DA);
    setStageToReliveReady();
    reloadDatas(true);
}

s32 CMenuHologram::model_z_layer = -1;

void CMenuHologram::renderOffscreenData()
{
    if (offscreenTexture != 0) {
        GSgfxLayer *layer = GSgfxLayerFindByID((GSgfxLayerID)6);
        if (layer != 0) {
            GSgfxVF *format = GSgfxVFBuildTemp(0, 2, 0, 0, 1, 5, 1, 1, 0);
            spriteSetOffset(6, 0, 0);
            spriteClearScissor(6);
            spriteSetEnv(6);
            f32 projection[16];
            GSmtx44Ortho(projection, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
            layer->projectionType = 1;

            layer->projectionScaleX = projection[0];
            layer->projectionOffsetX = projection[3];
            layer->projectionScaleY = projection[5];
            layer->projectionOffsetY = projection[7];
            layer->projectionScaleZ = projection[10];
            layer->projectionOffsetZ = projection[11];
            LayerMatrixStack *stack = layer->matrixStack;
            memcpy(stack->frame->matrix, mtxIdent, 0x30);
            u32 *matrixFlags = &stack->frame->flags;
            *matrixFlags |= 1;
            layer->depthRangeNear = 0.0f;
            layer->depthRangeFar = 30000.0f;
            if ((u8) layer->projectionDepthEnabled != 0) {
                if ((u8) layer->projectionDepthDirty != 0) {
                    layer->pixelDirty = (s32) (layer->pixelDirty | 0x100);
                    layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 0x100);
                }
                layer->pixelDirty = (s32) (layer->pixelDirty | 0x40);
                layer->dirty = (s32) (layer->dirty | 0x40);
                layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 0x40);
                layer->savedDirty = (s32) (layer->savedDirty | 0x40);
            }
            layer->unk16AC = (s32) (layer->unk16AC | 0x20);
            layer->dirty = (s32) (layer->dirty | 1);
            layer->unk1764 = (s32) (layer->unk1764 | 0x20);
            layer->savedDirty = (s32) (layer->savedDirty | 1);
            layer->colorUpdate = 1;
            layer->alphaUpdate = 0;
            layer->depthBeforeTexture = 0;
            layer->pixelDirty = (s32) (layer->pixelDirty | 4);
            layer->dirty = (s32) (layer->dirty | 0x40);
            layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 4);
            layer->savedDirty = (s32) (layer->savedDirty | 0x40);
            layer->depthEnable = 0;
            layer->depthCompare = 7;
            layer->pixelDirty = (s32) (layer->pixelDirty | 8);
            layer->dirty = (s32) (layer->dirty | 0x40);
            layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 8);
            layer->savedDirty = (s32) (layer->savedDirty | 0x40);
            layer->unkD8C = 2;
            layer->unk16B8 = (s32) (layer->unk16B8 | 2);
            layer->dirty = (s32) (layer->dirty | 2);
            layer->unk1770 = (s32) (layer->unk1770 | 2);
            layer->savedDirty = (s32) (layer->savedDirty | 2);
            layer->primitiveType = 0x80;
            layer->vertexFormat = format;
            layer->unkC70 = 1;
            layer->unk16AC = (s32) (layer->unk16AC | 1);
            layer->dirty = (s32) (layer->dirty | 1);
            layer->unk1764 = (s32) (layer->unk1764 | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 1);
            layer->tgenFunc(0, (GSgfxTgenFunc)1, (GSgfxTgenSrc)4, 0, false, 0);
            layer->unkDB8 = 1;
            layer->unk16BC = (s32) (layer->unk16BC | 1);
            layer->dirty = (s32) (layer->dirty | 4);
            layer->unk1774 = (s32) (layer->unk1774 | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 4);
                        layer->cunitChannelGen(0, (GSgfxCunitAlpha)2, (GSgfxCunitSrc)1, (GSgfxCunitSrc)1, 0, 0, (GSgfxLightType)2, (GSgfxDiffuseFunc)0);
            layer->unkEAC = 1;
            layer->unk16CC = (s32) (layer->unk16CC | 1);
            layer->dirty = (s32) (layer->dirty | 8);
            layer->unk1784 = (s32) (layer->unk1784 | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 8);
            layer->unkEB0 = 0;
            layer->unkEB4 = 0;
            layer->unkEB8 = 4;
            layer->unk16D0 = (s32) (layer->unk16D0 | 1);
            layer->dirty = (s32) (layer->dirty | 8);
            layer->unk1788 = (s32) (layer->unk1788 | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 8);
            layer->unk1170 = 0;
            layer->unk1174 = 0;
            layer->unk1178 = 0;
            layer->unk117C = 1;
            layer->unk1180 = 0;
            layer->unk16DC = (s32) (layer->unk16DC | 1);
            layer->dirty = (s32) (layer->dirty | 8);
            layer->unk1794 = (s32) (layer->unk1794 | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 8);
            layer->unkF70 = 0xF;
            layer->unkF74 = 0xF;
            layer->unkF78 = 0xF;
            layer->unkF7C = 8;
            layer->unk16D4 = (s32) (layer->unk16D4 | 1);
            layer->dirty = (s32) (layer->dirty | 8);
            layer->unk178C = (s32) (layer->unk178C | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 8);
            layer->unk12B0 = 0;
            layer->unk12B4 = 0;
            layer->unk12B8 = 0;
            layer->unk12BC = 1;
            layer->unk12C0 = 0;
            layer->unk16E0 = (s32) (layer->unk16E0 | 1);
            layer->dirty = (s32) (layer->dirty | 8);
            layer->unk1798 = (s32) (layer->unk1798 | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 8);
            layer->unk1070 = 7;
            layer->unk1074 = 5;
            layer->unk1078 = 4;
            layer->unk107C = 7;
            layer->unk16D8 = (s32) (layer->unk16D8 | 1);
            layer->dirty = (s32) (layer->dirty | 8);
            layer->unk1790 = (s32) (layer->unk1790 | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 8);
            if ((s32) layer->pass != 1) {
                layer->pass = 1;
                layer->currentPass = &layer->passes[layer->pass];
            }
            layer->blendMode = 1;
            layer->blendSource = 4;
            layer->blendDestination = 1;
            layer->logicOperation = 5;
            layer->pixelDirty = (s32) (layer->pixelDirty | 1);
            layer->dirty = (s32) (layer->dirty | 0x40);
            layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 1);
            layer->savedDirty = (s32) (layer->savedDirty | 0x40);
            GStexture *texture = offscreenTexture;
            if ((layer->texture0 != texture) || (layer->savedTexture0 != texture) || (((HologramTextureFlags *)texture)->dirty != 0)) {
                layer->texture0 = texture;
                layer->textureDirty = (s32) (layer->textureDirty | 1);
                layer->savedTexture0 = texture;
                layer->savedTextureDirty = (s32) (layer->savedTextureDirty | 1);
            }
            layer->beginSurface(4);
            *(volatile s16 *)0xCC008000 = 0;
            *(volatile s16 *)0xCC008000 = 0;
            u8 *hallData = (u8 *)relivehall_data;
            u8 alpha00 = hallData[0];
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = alpha00;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile s16 *)0xCC008000 = 640;
            *(volatile s16 *)0xCC008000 = 0;
            u8 alpha10 = hallData[0];
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = alpha10;
            *(volatile u8 *)0xCC008000 = 1;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile s16 *)0xCC008000 = 640;
            *(volatile s16 *)0xCC008000 = 480;
            u8 alpha11 = hallData[0];
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = alpha11;
            *(volatile u8 *)0xCC008000 = 1;
            *(volatile u8 *)0xCC008000 = 1;
            *(volatile s16 *)0xCC008000 = 0;
            *(volatile s16 *)0xCC008000 = 480;
            u8 alpha01 = hallData[0];
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = 255;
            *(volatile u8 *)0xCC008000 = alpha01;
            *(volatile u8 *)0xCC008000 = 0;
            *(volatile u8 *)0xCC008000 = 1;
            layer->endSurface();
        }
    }
}

void CMenuHologram::releaseOffscreenData()
{
    GSgfxLayer *layer = GSgfxLayerFindByID((GSgfxLayerID)2);
    layer->SetClearFlags(false, false, false);
    layer->SetTextureCopy(0, false, 0);
    if (model_z_layer != -1) {
        GSgfxLayerConfig::Remove((GSgfxLayerID)model_z_layer);
        model_z_layer = -1;
    }
    GSgfxLayerConfig::Move((GSgfxLayerID)2, (GSgfxLayerID)4, (GSgfxLayerOffset)1);
    if (offscreenTexture != 0) {
        GStextureFree(offscreenTexture);
        offscreenTexture = 0;
    }
}

void CMenuHologram::initializeOffscreenData()
{
    offscreenTexture = GStextureCreate(0, 0, 0x45, 0, 0);
    if (offscreenTexture != 0) {
        GSgfxLayer *layer;
        GSgfxLayerConfig::Move((GSgfxLayerID)2, (GSgfxLayerID)0, (GSgfxLayerOffset)1);
        if (model_z_layer == -1) {
            GSgfxLayer *zlayer;
            model_z_layer = GSgfxLayerConfig::Add("model z layer", 0xE000, 0x2000, 8, (GSgfxLayerType)0, false, false, false,
                                                  (GSgfxLayerID)2, (GSgfxLayerOffset)1);
            zlayer = GSgfxLayerFindByID((GSgfxLayerID)model_z_layer);
            if (zlayer != 0) {
                zlayer->SetClearFlags(true, true, false);
            }
        }
        layer = GSgfxLayerFindByID((GSgfxLayerID)2);
        layer->SetTextureCopy(offscreenTexture, false, 0);
        layer->SetClearFlags(true, true, true);
    }
}

static s32 plateIndexTbl[4][5][5] = {
    {
        { 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 2, 3, 0, 0, 0 },
        { 4, 5, 6, 0, 0 },
        { 7, 8, 9, 10, 0 },
        { 11, 12, 13, 14, 15 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 16, 17, 18, 19, 20 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 21, 22, 0, 0, 0 },
        { 23, 24, 25, 0, 0 },
        { 26, 27, 28, 29, 0 },
        { 30, 31, 32, 33, 34 },
    },
};

static s32 colorLineIndexTbl[4][5][5] = {
    {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 35, 36, 0, 0, 0 },
        { 37, 39, 38, 0, 0 },
        { 40, 43, 42, 41, 0 },
        { 44, 48, 47, 46, 45 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 49, 53, 52, 51, 50 },
    },
    {
        { 0, 0, 0, 0, 0 },
        { 54, 55, 0, 0, 0 },
        { 56, 58, 57, 0, 0 },
        { 59, 62, 61, 60, 0 },
        { 63, 67, 66, 65, 64 },
    },
};

void *_makeArchiveHeader(u32);

inline void loadStageModel(ModelSlot &slot, u32 id)
{
    memset(&slot, 0, sizeof(slot));
    const GSgfxLayerID layer[1] = { (GSgfxLayerID)0 };
    slot.script = scriptModelOpen(id);
    slot.model = GSresGetResourceAllGroup(slot.script);
    GSmodelSetRenderLayer(slot.model, 1, (GSgfxLayerID *)layer);
    if (slot.model != 0) {
        GSmodelSetAnimIndex(slot.model, 1);
        GSmodelSetAnimType(slot.model, 0);
        GSmodelStartAnimation(slot.model);
    }
}

void CMenuHologram::stageAllModelLoad()
{
    s32 st;
    u32 archive;
    u32 camera;
    s32 count;
    u16 effect;
    stageAllModelUnLoad();
    initializeOffscreenData();
    st = stage->getState();
    count = stage->getDancerQuantity();
    switch (st) {
    case 0:
        if (stage->getVisitorPointer() != 0) {
            effect = 0xF0;
        } else {
            effect = 0;
        }
        resGroup = 0x8E4;
        GSfsysReadWait(resGroup);
        loadStageModel(slots[0], 0x18D91000);
        loadStageModel(slots[1], 0x18D91000 + 1);
        camera = 0x18D71800;
        archive = 0x18D90400;
        break;
    case 1:
        effect = 0xF3;
        resGroup = 0x8E5;
        GSfsysReadWait(resGroup);
        loadStageModel(slots[0], 0x18DC1000);
        loadStageModel(slots[1], 0x18DC1000 + count);
        camera = 0x18DA1800;
        archive = 0x18DC0400;
        break;
    case 2:
        effect = 0xEF;
        resGroup = 0x8E6;
        GSfsysReadWait(resGroup);
        loadStageModel(slots[0], 0x18DF1000);
        loadStageModel(slots[1], 0x18DF1000 + 1);
        camera = 0x18DD1800;
        archive = 0x18DF0400;
        break;
    case 3:
        effect = 0xEF;
        resGroup = 0x8E7;
        GSfsysReadWait(resGroup);
        loadStageModel(slots[0], 0x18E41000);
        loadStageModel(slots[1], 0x18E41000 + count);
        camera = 0x18E01800;
        archive = 0x18E40400;
        break;
    }
    Pokemon *visitor = stage->getVisitorPointer();
    if (visitor != 0) {
        ModelSlot *slot = modelPokemonLoad(2);
        GSpart *part = GSmodelGetPart(slots[1].model, ((u8 *)relivehall_data)[6 + plateIndexTbl[st][count][0]]);
        GSmodelAttachToGSpart(slot->model, part, 7, 0, 1);
        GSpartFree(part);
        modelVisitorSetYPosition(2);
        modelPokemonSetScale(2);
    }
    for (s32 i = 0; i < count; i++) {
        s32 index = i + 3;
        ModelSlot *slot = modelPokemonLoad(index);
        GSpart *part = GSmodelGetPart(slots[1].model, ((u8 *)relivehall_data)[6 + plateIndexTbl[st][count][(count + (i - stage->firstDancer)) % count + 1]]);
        GSmodelAttachToGSpart(slot->model, part, 7, 0, 1);
        GSpartFree(part);
        modelPokemonSetScale(index);
    }
    u8 *materials = slots[1].model != 0 ? *(u8 **)((u8 *)slots[1].model + 0x5E0) : 0;
    GSmodelDisableModulation(slots[1].model);
    if (count != 0) {
        GSgfxColAu8 color;
        memset(&color, 0, 4);
        if (visitor != 0) {
            GSgfxColAu8 c = pokemonToAisyouColor(visitor, stage->getDancerPointer(stage->firstDancer));
            ((u8 *)&color)[0] = ((u8 *)&c)[0];
            ((u8 *)&color)[1] = ((u8 *)&c)[1];
            ((u8 *)&color)[2] = ((u8 *)&c)[2];
            ((u8 *)&color)[3] = ((u8 *)&c)[3];
        }
        void *material = materials + (((u8 *)relivehall_data)[6 + colorLineIndexTbl[st][count][0]] - 1) * 0x34;
        GSmaterialSetModulate(material, &color);
        GSmaterialEnableExtension(material, 1);
    }
    for (s32 i = 0; i < count; i++) {
        Pokemon *next = stage->getDancerPointer((i + 1) % count);
        GSgfxColAu8 color = pokemonToAisyouColor(stage->getDancerPointer(i), next);
        void *material = materials + (((u8 *)relivehall_data)[6 + colorLineIndexTbl[st][count][(count + (i - stage->firstDancer)) % count + 1]] - 1) * 0x34;
        GSmaterialSetModulate(material, &color);
        GSmaterialEnableExtension(material, 1);
    }
    cameraPlayAnime(resGroup, camera, 0.0f, 1);
    cameraSetType(4);
    struct ArchiveHeader { u8 reserved0[8]; u32 *lights; };
    ArchiveHeader *header = (ArchiveHeader *)_makeArchiveHeader(archive);
    if (header->lights != 0) {
        floorReadMakeLightResID(archive);
        for (s32 i = 0; header->lights[i] != 0; i++) {
            s32 light = GSlightLoad(header->lights[i]);
            lights[lightCount++] = light;
            GSlightSetActive(light, 1);
            if (GSlightCanAnimate(light)) {
                GSlightSetAnimIndex(light, 0);
                GSlightSetAnimRate(light, 0.5f);
                GSlightStartAnimation(light);
            }
        }
    }
    GSgfxLayerID layers[2] = { (GSgfxLayerID)0, (GSgfxLayerID)0 };
    layers[1] = (GSgfxLayerID)model_z_layer;
    stageModel = floorOpenObject(0x16C90400);
    GSmodelSetAnimIndex(stageModel, 3);
    GSmodelSetAnimRate(stageModel, 0.5f);
    GSmodelStartAnimation(stageModel);
    GSmodelSetVisibility(stageModel, 1);
    GSmodelSetAnimType(stageModel, 1);
    GSmodelSetRenderLayer(stageModel, 2, layers);
    s8 neck = peopleInfoBiosGetNeckIndex(peopleInfoBiosGetPtr(0x16C90400));
    GSpart *part = GSmodelGetPart(stageModel, neck);
    GSpartRegisterAnimMix(part, 2, 0x20202, _getNeckRotationCB, 0);
    GSpartFree(part);
    if (effect != 0) {
        unk37C = Sequence_CreateNull();
        unk380 = Sequence_LoadWaza(unk37C, effect, 4, 0);
        GSvec pos(0.0f, 0.0f, 0.0f);
        GSvec rot(0.0f, 0.0f, 0.0f);
        Sequence_SetPosition(unk37C, &pos.x);
        Sequence_SetRotation(unk37C, &rot.x);
        WazaSequence_Start(unk380, 0);
    }
    stageLoaded = 1;
}

void CMenuHologram::stageAllModelUnLoad()
{
    if (stageLoaded != 0) {
        u8 *slot;
        u32 i;
        s32 j;
        u8 *light;
        if (unk384 != 0) {
            Sequence_SetVisibility(unk384, 0);
            Sequence_Free(unk384);
            unk384 = 0;
        }
        if (unk380 != 0) {
            WazaSequence_Free(unk380);
            Sequence_Free(unk37C);
        }
        unk380 = 0;
        unk37C = 0;
        releaseOffscreenData();
        for (slot = (u8 *)this, i = 0; i < 7; slot += 12, i++) {
            void *model = *(void **)(slot + 0x38C);
            if (model != 0) {
                if (*(u32 *)(slot + 0x390) != 0) {
                    Sequence_SetVisibility(*(u32 *)(slot + 0x390), 0);
                    Sequence_Free(*(u32 *)(slot + 0x390));
                } else {
                    GSmodelSetVisibility(model, 0);
                    scriptModelClose(*(s32 *)(slot + 0x388));
                }
            }
        }
        memset(slots, 0, sizeof(slots));
        light = (u8 *)this;
        j = 0;
        while (j < lightCount) {
            GSlightFree(*(s32 *)(light + 0x348));
            light += 4;
            j++;
        }
        memset(lights, 0, sizeof(lights));
        lightCount = 0;
        if (resGroup != 0) {
            GSfsysFree(resGroup);
            GSresFreeGroup(resGroup);
            resGroup = 0;
        }
        cameraSetType(3);
        if (stageModel != 0) {
            GSmodelFree(stageModel);
            stageModel = 0;
        }
        stageLoaded = 0;
    }
}

ModelSlot *CMenuHologram::modelPokemonLoad(long index)
{
    ModelSlot *slot = &slots[index];
    Pokemon *pokemon;
    u16 waza;
    u16 id;
    unsigned long rnd;
    memset(slot, 0, 12);
    if (index == 2) {
        pokemon = stage->getVisitorPointer();
    } else {
        pokemon = stage->getDancerPointer(index - 3);
    }
    if (pokemon == 0) {
        return 0;
    }
    waza = 0;
    if (pokemon->isDarkPokemon() && !stage->isReliveReady()) {
        if (pokemonIsJoutaiDataId(pokemon, 0x3E) == 1) {
            waza = 0x87;
        } else {
            waza = 0x25;
        }
    }
    menuModelGetPkxRndFromPokemonForSeqenceLoad(rnd, id, pokemon);
    slot->sequence = Sequence_LoadPokemon(id, rnd, pokemonGetStatus(pokemon, 0, 0xC1, 0) != 0);
    slot->model = Sequence_GetGSmodel(slot->sequence);
    Sequence_SetVisibility(slot->sequence, 1);
    if (waza != 0) {
        u32 seq = Sequence_LoadWaza(slot->sequence, waza, 4, 0);
        if (seq != 0) {
            WazaSequence_Start(seq, 0);
        }
    }
    Sequence_DoAnimation(slot->sequence, menuModelGetPokemonAnimationIndexByPointer(pokemon));
    GSmodelSetForceUseFractionalFramesFlag(slot->model, 1);
    GSmodelSetSkipFractionalFramesFlag(slot->model, 1);
    return slot;
}

ModelSlot *CMenuHologram::modelPokemonSetScale(long index)
{
    ModelSlot *slot = &slots[index];
    Pokemon *pokemon;
    f32 scale;
    f32 v[3];
    if (index == 2) {
        pokemon = stage->getVisitorPointer();
    } else {
        pokemon = stage->getDancerPointer(index - 3);
    }
    if (pokemon == 0) {
        return 0;
    }
    u16 id = pokemon->getPokemonDataId();
    f32 m = menuGetPokemonScale(slot->sequence, id);
    scale = m * (f32)relivehall_data->unk4 / 100.0f;
    v[0] = scale;
    v[1] = scale;
    v[2] = scale;
    Sequence_SetScale(slot->sequence, v);
    return slot;
}

void CMenuHologram::modelVisitorSetYPosition(long index)
{
    ModelSlot *slot = &slots[index];
    f32 pos[3];
    u16 id = stage->getVisitorPointer()->getPokemonDataId();
    f32 y = 0.0f;
    switch (id) {
    case 0xA5:
        y = -2.0f;
        break;
    case 0xA6:
        y = -10.0f;
        break;
    case 0x14A:
        y = -6.5f;
        break;
    case 0x14B:
        y = -20.0f;
        break;
    case 0x14C:
        y = 0.0f;
        break;
    case 0x169:
        break;
    case 0x16A:
        break;
    case 0x15:
        y = -2.0f;
        break;
    case 0x16:
        y = -9.0f;
        break;
    case 0xF:
        y = -5.5f;
        break;
    case 0xC:
        y = -8.0f;
        break;
    case 0x31:
        y = -9.0f;
        break;
    case 0x46:
        y = -2.0f;
        break;
    case 0x47:
        y = -6.5f;
        break;
    case 0x52:
        y = 0.0f;
        break;
    case 0x15D:
        y = -6.5f;
        break;
    case 0x83:
        y = -6.5f;
        break;
    }
    pos[1] = y;
    pos[0] = 0.0f;
    pos[2] = 0.0f;
    Sequence_SetPosition(slot->sequence, pos);
}

void CMenuHologram::unloadDatas()
{
    localWindowDeleteAll();
    stageAllModelUnLoad();
}

GSgfxColAu8 CMenuHologram::pokemonToAisyouColor(Pokemon *a, Pokemon *b)
{
    GSgfxColAu8 color;
    s32 aisyou = reliveHallPokemonToAisyou(a, b);
    if (aisyou == -1) {
        color = GSgfxColAu8_Black;
    } else {
        color = relivehallAisyou2ColorTbl[aisyou];
    }
    return color;
}

void CMenuHologram::bgmStop()
{
    soundStop(soundGetBGMID(), 50);
}

void CMenuHologram::bgmKick()
{
    u32 bgm;
    s32 tempo;
    stage->getState();
    tempo = stage->getTempo();
    if (tempo <= 0) {
        bgm = 0x5BB;
    } else if (tempo <= 0x35) {
        bgm = 0x510;
    } else if (tempo <= 0x5F) {
        bgm = 0x50F;
    } else {
        bgm = 0x50E;
    }
    u32 current = soundGetBGMID();
    if (current != bgm) {
        menuPtPlayBgm(bgm);
    }
}

void CMenuHologram::main(CMenuGlobalState &state)
{
    systemFadeOutKeepAfterFloorPush();
    init(state);
    systemFadeInKick();
    loop();
    unloadDatas();
    bgmStop();
}

void *_makeArchiveHeader(u32 group)
{
    return HSD_ArchiveGetPublicAddress(GSresGetResourceAllGroup(group), "scene_data");
}

}

extern "C" {
void menuHologramReloadDatas(void)
{
    pMenuHologram->reloadDatas(false);
}

void menuHologramUnloadDatas(void)
{
    pMenuHologram->unloadDatas();
}
}

void menuHologramExecFromPcBox(CMenuGlobalState &state)
{
    thisExec(state);
}
