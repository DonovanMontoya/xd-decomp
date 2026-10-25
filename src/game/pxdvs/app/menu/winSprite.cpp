// Needs extra cflags: -inline noauto,deferred -opt nopeephole
// Functions are written in reverse object order because "deferred" emits them reversed;
// this also reproduces the function-local static suffix numbering ($NNNN) once all bodies exist.
#include <game/pxdvs/app/menu/winSpritePrivate.hpp>
#include <libc/string.h>
#include <game/pxdvs/app/menu/menuOffScreenPrivate.hpp>

extern "C" {
void *GSmemAlloc(s32);
void GSlogWrite(const char *, ...);
MenuData *menuDataBiosGetPtr(s32);
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, s16);
u32 menuSeqBiosGetPtr(u32);
s32 menuBiosGetCursorSize();
s32 dbgMenuGetLayerID();
s32 floorGetMenuLayerID();
tagWINDOW_WORK *windowSearchID(s32);
}

extern "C" {
s32 timeGetLastFrameTime();
f64 sqrt(f64);
void *menuSpriteBiosGetPtr(s16);
void *menuSpriteBiosGetValPtr(void *);
}

static void _winSeqMoveSprite(s32 id, tagSPRITE_WORK *sprite);
static void _winSeqMoveMenu(tagWINDOW_WORK *win);
static void _winSeqMoveSub(SEQ_WORK_COMMON *common, tagSEQ_WORK *seq);

static u8 *_spriteWork;
extern "C" void winSetSequence(void *work, u16 seq);

extern "C" {
s32 winSpriteGetLayerID(tagWINDOW_WORK *win, WindowSprite *winSprite) {
    tagSPRITE_WORK *sprite = (tagSPRITE_WORK *)winSprite;
    MenuData *md = menuDataBiosGetPtr(win->menuID);
    if (win->layerID == dbgMenuGetLayerID()) {
        return dbgMenuGetLayerID();
    }
    if ((u32)((md->flags >> 5) & 7) == 3) {
        s32 layer = dbgMenuGetLayerID();
        if (win->layerID != layer) {
            win->layerID = layer;
        }
        return layer;
    }
    if (sprite->drawType == 0) {
        return 7;
    }
    return floorGetMenuLayerID();
}
}

extern "C" {
void winSpriteInit() {
    _spriteWork = (u8 *)GSmemAlloc(0xEA60);
    if (_spriteWork != 0) {
        memset(_spriteWork, 0, 0xEA60);
    }
}
}

extern "C" {
tagSPRITE_WORK *winSpriteAdd(tagSPRITE_WORK **list) {
    if (list == 0) {
        return 0;
    }
    tagSPRITE_WORK *s = (tagSPRITE_WORK *)_spriteWork;
    for (s32 i = 0; i < 500; i++, s++) {
        if (s->type == 0) {
            memset(s, 0, 0x78);
            s->type = 7;
            s->scaleX = 1.0f;
            s->scaleY = 1.0f;
            s->color = -1;
            tagSPRITE_WORK **p = list;
            while (*p != 0) {
                p = &(*p)->next;
            }
            *p = s;
            return s;
        }
    }
    GSlogWrite("Error!! winSpriteAdd() [\x83\x58\x83\x76\x83\x89\x83\x43\x83\x67\x83\x8f\x81\x5b\x83\x4e\x95\x73\x91\xab]\n\0");
    return 0;
}
}

extern "C" {
void winSpriteRelease(tagSPRITE_WORK **list) {
    if (list != 0) {
        tagSPRITE_WORK **p = list;
        while (*p != 0) {
            (*p)->type = 0;
            p = (tagSPRITE_WORK **)*p;
        }
        *list = 0;
    }
}
}

extern "C" {
void winSpriteSetDisp(tagSPRITE_WORK *sprite, u8 disp) {
    if (sprite != 0) {
        if (disp != 0) {
            sprite->type |= 2;
            return;
        }
        sprite->type &= ~2;
    }
}
}

extern "C" {
s32 winSpriteGetDisp(tagSPRITE_WORK *sprite) {
    if (sprite == 0) {
        return 0;
    }
    return (sprite->type & 2) != 0;
}
}

static void _spriteSetAlphaMode(GSgfxLayer *layer, u8 mode) {
    switch (mode) {
    case 0:
        layer->alphaCompare0 = 7;
        layer->alphaReference0 = 0;
        layer->alphaCombine = 0;
        layer->alphaCompare1 = 7;
        layer->alphaReference1 = 0;
        layer->alphaDisabled = 1;
        layer->pixelDirty |= 0x10;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 0x10;
        layer->savedDirty |= 0x40;
        if (layer->blendIndex != 1) {
            layer->blendIndex = 1;
            layer->currentBlend = &layer->blendRecords[layer->blendIndex];
        }
        layer->blendMode = 1;
        layer->blendSource = 4;
        layer->blendDestination = 5;
        layer->logicOperation = 5;
        layer->pixelDirty |= 1;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 1;
        layer->savedDirty |= 0x40;
        return;
    case 1:
        layer->alphaCompare0 = 4;
        layer->alphaReference0 = 0;
        layer->alphaCombine = 1;
        layer->alphaCompare1 = 0;
        layer->alphaReference1 = 0;
        layer->alphaDisabled = 0;
        layer->pixelDirty |= 0x10;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 0x10;
        layer->savedDirty |= 0x40;
        if (layer->blendIndex != 1) {
            layer->blendIndex = 1;
            layer->currentBlend = &layer->blendRecords[layer->blendIndex];
        }
        layer->blendMode = 1;
        layer->blendSource = 2;
        layer->blendDestination = 0;
        layer->logicOperation = 5;
        layer->pixelDirty |= 1;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 1;
        layer->savedDirty |= 0x40;
        return;
    case 2:
        layer->alphaCompare0 = 7;
        layer->alphaReference0 = 0;
        layer->alphaCombine = 0;
        layer->alphaCompare1 = 7;
        layer->alphaReference1 = 0;
        layer->alphaDisabled = 1;
        layer->pixelDirty |= 0x10;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 0x10;
        layer->savedDirty |= 0x40;
        if (layer->blendIndex != 1) {
            layer->blendIndex = 1;
            layer->currentBlend = &layer->blendRecords[layer->blendIndex];
        }
        layer->blendMode = 1;
        layer->blendSource = 4;
        layer->blendDestination = 1;
        layer->logicOperation = 5;
        layer->pixelDirty |= 1;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 1;
        layer->savedDirty |= 0x40;
        return;
    }
}

extern "C" {
void winAnimeCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    menuBiosGetCursorSize();
    if (*(s16 *)((u8 *)win + 0xA2) != win->cursorIndex) {
        winSetSequence(sprite->sequence, 0x141);
    }
    if (win->state == 3) {
        winSetSequence(sprite->sequence, 0);
    }
}
}

extern "C" {
void winSetSequence(void *work, u16 seq) {
    if (seq == 0) {
        *(u32 *)work = 0;
        *(u16 *)((u8 *)work + 4) = 0;
        return;
    }
    memset(work, 0, 0x3C);
    *(u32 *)work = menuSeqBiosGetPtr(seq);
}
}

extern "C" {
void winSeqSetMenu(s32 id, u16 seq) {
    tagWINDOW_WORK *win = windowSearchID(id);
    if (win != 0) {
        winSetSequence(win->reserved2C, seq);
        _winSeqMoveMenu(win);
    }
}
}

extern "C" {
s32 winSeqIsCheck(s32 id, u16 seq) {
    tagWINDOW_WORK *win = windowSearchID(id);
    if (win != 0 && *(u32 *)win->reserved2C == menuSeqBiosGetPtr(seq)) {
        return 1;
    }
    return 0;
}
}

static void _winSeqMoveSub(SEQ_WORK_COMMON *common, tagSEQ_WORK *seq) {
    f32 startScaleY;
    f32 quadraticBlend;
    f32 scaleBlend;
    f32 linearBlend;
    f32 rootBlend;
    f32 colorBlend;
    f32 startScaleX;
    f64 durationRoot;
    s16 moveFrame;
    s16 moveDuration;
    s16 rootDuration;
    s16 rootFrame;
    s16 wait;
    s16 linearStartY;
    s16 quadraticStartY;
    s16 rootStartY;
    s16 rootStartX;
    s16 linearStartX;
    s16 quadraticStartX;
    s32 relative;
    s32 easing;
    u8 stopped;
    u32 frameIndex;
    s32 frames;
    u8 moveMode;
    u8 startGreen;
    u8 startBlue;
    u8 startAlpha;
    u8 opcode;
    u8 startRed;
    WindowSequenceCommand *command;
    WindowSpriteValue *spriteData;

    stopped = 0;
    frames = timeGetLastFrameTime();
    if (frames > 2) {
        frames = 2;
    }
    for (frameIndex = 0; frameIndex < (u32)frames; ++frameIndex) {
        if (!seq->commands) break;
        {
            if ((u8) seq->moveMode != 0) {
                ++seq->moveFrame;
                moveMode = seq->moveMode;
                switch ((s32) moveMode) {
                case 1:
                    linearStartX = seq->startX;
                    linearBlend = (f32) seq->moveFrame / (f32) seq->moveDuration;
                    common->x = (s16) ((linearBlend * (f32) (seq->endX - linearStartX)) + (f32) linearStartX);
                    linearStartY = seq->startY;
                    common->y = (s16) ((linearBlend * (f32) (seq->endY - linearStartY)) + (f32) linearStartY);
                    break;
                case 2:
                    moveFrame = seq->moveFrame;
                    moveDuration = seq->moveDuration;
                    quadraticStartX = seq->startX;
                    quadraticBlend = (((f32) moveFrame * (f32) moveFrame) / (f32) moveDuration) / (f32) moveDuration;
                    common->x = (s16) ((quadraticBlend * (f32) (seq->endX - quadraticStartX)) + (f32) quadraticStartX);
                    quadraticStartY = seq->startY;
                    common->y = (s16) ((quadraticBlend * (f32) (seq->endY - quadraticStartY)) + (f32) quadraticStartY);
                    break;
                case 3:
                    rootDuration = seq->moveDuration;
                    durationRoot = sqrt((f64) rootDuration);
                    rootFrame = seq->moveFrame;
                    rootBlend = (f32) (sqrt((f64) rootFrame) / durationRoot);
                    rootStartX = seq->startX;
                    common->x = (s16) ((rootBlend * (f32) (seq->endX - rootStartX)) + (f32) rootStartX);
                    rootStartY = seq->startY;
                    common->y = (s16) ((rootBlend * (f32) (seq->endY - rootStartY)) + (f32) rootStartY);
                    break;
                }
                if ((s16) seq->moveFrame >= (s16) seq->moveDuration) {
                    seq->moveMode = 0U;
                }
            }
            if ((u8) seq->colorMode != 0) {
                ++seq->colorFrame;
                switch (seq->colorMode) {
                case 1: {
                    startRed = seq->startColor[0];
                    colorBlend = (f32) seq->colorFrame / (f32) seq->colorDuration;
                    ((s8 *)&common->color)[0] = ((colorBlend * (f32) (seq->endColor[0] - startRed)) + (f32) startRed);
                    startGreen = seq->startColor[1];
                    ((s8 *)&common->color)[1] = ((colorBlend * (f32) (seq->endColor[1] - startGreen)) + (f32) startGreen);
                    startBlue = seq->startColor[2];
                    ((s8 *)&common->color)[2] = ((colorBlend * (f32) (seq->endColor[2] - startBlue)) + (f32) startBlue);
                    startAlpha = seq->startColor[3];
                    ((s8 *)&common->color)[3] = ((colorBlend * (f32) (seq->endColor[3] - startAlpha)) + (f32) startAlpha);
                }
                }
                if ((s16) seq->colorFrame >= (s16) seq->colorDuration) {
                    seq->colorMode = 0U;
                }
            }
            if ((u8) seq->scaleMode != 0) {
                ++seq->scaleFrame;
                switch (seq->scaleMode) {
                case 1: {
                    startScaleX = seq->startScaleX;
                    scaleBlend = (f32) seq->scaleFrame / (f32) seq->scaleDuration;
                    common->scaleX = (f32) ((scaleBlend * (seq->endScaleX - startScaleX)) + startScaleX);
                    startScaleY = seq->startScaleY;
                    common->scaleY = (f32) ((scaleBlend * (seq->endScaleY - startScaleY)) + startScaleY);
                }
                }
                if ((s16) seq->scaleFrame >= (s16) seq->scaleDuration) {
                    seq->scaleMode = 0U;
                }
            }
nextCommand:
            wait = seq->wait;
            if (wait > 0) {
                --seq->wait;
            } else {
                command = seq->commands + seq->index;
                opcode = command->command;
                switch (opcode) {
                case 0:
                    stopped = 1;
                    seq->commands = 0U;
                    seq->index = 0;
                    break;
                case 1:
                    seq->wait = (s16) command->duration;
                    break;
                case 3:
                case 9:
                    if (opcode == 9) {
                        seq->endX = (s16) common->baseX;
                        seq->endY = (s16) common->baseY;
                    } else {
                        relative = ((u8) command->flags >> 7U) & 1;
                        switch (relative) {
                        case 0:
                            seq->endX = (s16) command->x;
                            seq->endY = (s16) command->y;
                            break;
                        case 1:
                            seq->endX = (s16) (common->x + command->x);
                            seq->endY = (s16) (common->y + command->y);
                            break;
                        }
                    }
                    if ((s32) (command->bits.axes & 1) != 0) {
                        seq->endX = (s16) common->x;
                    }
                    if ((s32) (command->bits.axes & 2) != 0) {
                        seq->endY = (s16) common->y;
                    }
                    seq->moveDuration = (s16) command->duration;
                    if ((s16) seq->moveDuration == 0) {
                        common->x = (s16) seq->endX;
                        common->y = (s16) seq->endY;
                        seq->moveMode = 0U;
                    } else {
                        seq->startX = (s16) common->x;
                        seq->startY = (s16) common->y;
                        seq->moveFrame = 0;
                        easing = ((u8) command->flags >> 5U) & 3;
                        switch (easing) {
                        case 0:
                            seq->moveMode = 1U;
                            break;
                        case 1:
                            seq->moveMode = 2U;
                            break;
                        case 2:
                            seq->moveMode = 3U;
                            break;
                        case 3:
                            seq->moveMode = 1U;
                            break;
                        }
                    }
                    break;
                case 7:
                    seq->startColor[0] = (u8) ((u8 *)&common->color)[0];
                    seq->startColor[1] = (u8) ((u8 *)&common->color)[1];
                    seq->startColor[2] = (u8) ((u8 *)&common->color)[2];
                    seq->startColor[3] = (u8) ((u8 *)&common->color)[3];
                    seq->endColor[0] = (((u32)command->x >> 24) & 255);
                    seq->endColor[1] = (((u32)command->x >> 16) & 255);
                    seq->endColor[2] = (((u32)command->x >> 8) & 255);
                    seq->endColor[3] = (((u32)command->x >> 0) & 255);
                    seq->colorFrame = 0;
                    seq->colorDuration = (s16) command->duration;
                    seq->colorMode = 1U;
                    if ((s16) seq->colorDuration == 0) {
                        ((u8 *)&common->color)[0] = seq->endColor[0];
                        ((u8 *)&common->color)[1] = seq->endColor[1];
                        ((u8 *)&common->color)[2] = seq->endColor[2];
                        ((u8 *)&common->color)[3] = seq->endColor[3];
                        seq->colorMode = 0U;
                    }
                    break;
                case 6:
                    seq->startScaleX = (f32) common->scaleX;
                    seq->startScaleY = (f32) common->scaleY;
                    seq->endScaleX = (f32) ((f32) command->x / 100.0f);
                    seq->endScaleY = (f32) ((f32) command->y / 100.0f);
                    seq->scaleFrame = 0;
                    seq->scaleDuration = (s16) command->duration;
                    seq->scaleMode = 1U;
                    if ((s16) seq->scaleDuration == 0) {
                        common->scaleX = (f32) seq->endScaleX;
                        common->scaleY = (f32) seq->endScaleY;
                        seq->scaleMode = 0U;
                    }
                    break;
                case 2:
                    if ((s32) command->x != 0) {
                        *(s8 *)&common->type = (s8)(common->type | 2);
                    } else {
                        *(s8 *)&common->type = (s8)(common->type & ~2);
                    }
                    break;
                case 11:
                    if ((s32) command->x != 0) {
                        seq->loopFlag = 1;
                    } else {
                        seq->loopFlag = 0;
                    }
                    break;
                case 10:
                    if ((u8) seq->loopActive == 0) {
                        seq->loopActive = 1U;
                        seq->loopCount = (s16) command->duration;
                    }
                    if ((u32) (((u8) command->flags >> 7U) & 1) == 0) {
                        --seq->loopCount;
                    }
                    if ((s16) seq->loopCount < 0) {
                        seq->loopCount = 0;
                        seq->loopActive = 0U;
                        break;
                    }
                    seq->index = (s16) command->x;
                    goto nextCommand;
                case 8:
                    spriteData = (WindowSpriteValue *)menuSpriteBiosGetValPtr(((void *(*)(s32))menuSpriteBiosGetPtr)(command->x));
                    common->resource = (s32) spriteData->resource;
                    common->sourceX = (s16) spriteData->x;
                    common->sourceY = (s16) spriteData->y;
                    common->sourceWidth = (s16) spriteData->width;
                    common->sourceHeight = (s16) spriteData->height;
                    break;
                }
                if (!stopped) {
                    ++seq->index;
                    goto nextCommand;
                }
            }

        }
    }
}

static void _winSeqMoveMenu(tagWINDOW_WORK *win) {
    static SEQ_WORK_COMMON seqTemp;
    seqTemp.x = win->x;
    seqTemp.y = win->y;
    seqTemp.color = *(s32 *)&win->frame;
    seqTemp.type = win->flags;
    seqTemp.baseX = menuDataBiosGetPtr(win->menuID)->x;
    seqTemp.baseY = menuDataBiosGetPtr(win->menuID)->y;
    _winSeqMoveSub(&seqTemp, (tagSEQ_WORK *)win->reserved2C);
    win->x = seqTemp.x;
    win->y = seqTemp.y;
    *(s32 *)&win->frame = seqTemp.color;
    win->flags = seqTemp.type;
}

#pragma dollar_identifiers on
extern "C" {static SEQ_WORK_COMMON seqTemp$2282;}
static void _winSeqMoveSprite(s32 id, tagSPRITE_WORK *sprite) {
    seqTemp$2282.x = sprite->x;
    seqTemp$2282.y = sprite->y;
    seqTemp$2282.color = sprite->color;
    seqTemp$2282.scaleX = sprite->scaleX;
    seqTemp$2282.scaleY = sprite->scaleY;
    seqTemp$2282.type = sprite->type;
    seqTemp$2282.resource = sprite->resource;
    seqTemp$2282.sourceX = sprite->sourceX;
    seqTemp$2282.sourceY = sprite->sourceY;
    seqTemp$2282.sourceWidth = sprite->sourceWidth;
    seqTemp$2282.sourceHeight = sprite->sourceHeight;
    seqTemp$2282.baseX = menuItemBiosGetPtr(id, sprite->itemID)->x;
    seqTemp$2282.baseY = menuItemBiosGetPtr(id, sprite->itemID)->y;
    _winSeqMoveSub(&seqTemp$2282, (tagSEQ_WORK *)sprite->sequence);
    sprite->x = seqTemp$2282.x;
    sprite->y = seqTemp$2282.y;
    sprite->color = seqTemp$2282.color;
    sprite->scaleX = seqTemp$2282.scaleX;
    sprite->scaleY = seqTemp$2282.scaleY;
    *(u8*)&sprite->type = seqTemp$2282.type;
    sprite->resource = seqTemp$2282.resource;
    sprite->sourceX = seqTemp$2282.sourceX;
    sprite->sourceY = seqTemp$2282.sourceY;
    sprite->sourceWidth = seqTemp$2282.sourceWidth;
    sprite->sourceHeight = seqTemp$2282.sourceHeight;
}

extern "C" {
void winSeqMoveMenu(tagWINDOW_WORK *win) {
    _winSeqMoveMenu(win);
    for (tagSPRITE_WORK *s = (tagSPRITE_WORK *)win->items; s != 0; s = s->next) {
        _winSeqMoveSprite(win->menuID, s);
    }
    for (tagSPRITE_WORK *s = (tagSPRITE_WORK *)win->cursor; s != 0; s = s->next) {
        _winSeqMoveSprite(win->menuID, s);
    }
}
}

extern "C" {
s32 winSeqCheckMove(s32 id) {
    tagWINDOW_WORK *win = windowSearchID(id);
    if (win == 0) {
        return 0;
    }
    if (*(u32 *)win->reserved2C != 0) {
        return 1;
    }
    for (tagSPRITE_WORK *s = (tagSPRITE_WORK *)win->items; s != 0; s = s->next) {
        if (*(u32 *)s->sequence != 0 && s->sequence[0x3A] == 0) {
            return 1;
        }
    }
    return 0;
}
}

#include <dolphin/mtx.h>
extern "C" {

GSgfxVF* GSgfxVFBuildTemp(s32,s32,s32,s32,s32,s32,s32,s32,s32);
void* GSresGetResourceAllGroup(u32);
u16 GStextureGetXsize(void*);
u16 GStextureGetYsize(void*);
void GSvecTransformQuat(Vec*,Quaternion*,Vec*);
void C_QUATRotAxisRad(Quaternion*,const Vec*,f32);
extern Vec yAxisVector;
void spriteSetEnv(s32);
void spriteSetOffset(s32,s32,s32);
void* menuSpriteBiosGetPtr(s16);
void* menuSpriteBiosGetValPtr(void*);
s32 windowGetActiveID();
void menuSubDrawSimpleWindow(s32,s32,s32,s32,s32);
void menuSubDrawNormalWindow2(s32,s32,s32,s32,s32,u8);
void menuSubDrawMsgWindow2(s32,s32,s32,s32,s32,u8,s32);
void menuSubDrawCursorBack(s32,s32,s32,s32,s32,u8,s32);
void menuSubDrawCursorBackAnimeOnOff(s32,s32,s32,s32,s32,u8,s32,s32);
void GSmsgPrintRect(s32,s32,s32,s32,s32,u32,u32);
void FlashSystemPlay(s32);
void FlashSystemDraw(s32,tagWINDOW_WORK*,tagSPRITE_WORK*);
void winSpriteDrawTexture(tagWINDOW_WORK*,tagSPRITE_WORK*);
}
static inline s32 spriteAbs(s32 value) {if(value<0)value=-value;return value;}
struct SpritePoint {f32 x,y;};
#pragma dollar_identifiers on
extern "C" {
static SpritePoint xy$2102[4],st$2103[4];
static SpritePoint cxy$2104;
}
extern "C" void winSpriteDrawTexture(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite) {
    GSgfxLayer* layer=(GSgfxLayer*)GSgfxLayerFindByID(winSpriteGetLayerID(window,(WindowSprite*)sprite));
    u8* sc=(u8*)&sprite->color;
    u8* wc=(u8*)&window->frame;
    u8 alpha,blue,green,red;
    s16 width,height;
    void* texture;
    s16 sx,sy;
    red=sc[0]*wc[0]/255;green=sc[1]*wc[1]/255;blue=sc[2]*wc[2]/255;alpha=sc[3]*wc[3]/255;
    texture=GSresGetResourceAllGroup(sprite->resource);
    if(texture) {
        if(layer->textures[0]!=texture || layer->savedTextures[0]!=texture || ((TextureRecord*)texture)->dirty) {
            layer->textures[0]=(TextureRecord*)texture;layer->textureDirty|=1;
            layer->savedTextures[0]=(TextureRecord*)texture;layer->savedTextureDirty|=1;
        }
        switch(sprite->mode) {
        default:case 0: {
            s32 w=sprite->width;if(w<0)w=-w;
            s32 source=sprite->sourceWidth;
            if(source!=w) {
                if(source<0) {sx=sprite->sourceX;if(source<0)source=-source;width=source;}
                else {width=source-2;sx=sprite->sourceX+1;}
                if(width<0)width=0;
            }else {sx=sprite->sourceX;width=source;}
            s32 h=sprite->height;if(h<0)h=-h;
            source=sprite->sourceHeight;
            if(source!=h) {
                if(source<0) {sy=sprite->sourceY;if(source<0)source=-source;height=source;}
                else {height=source-2;sy=sprite->sourceY+1;}
                if(height<0)height=0;
            }else {sy=sprite->sourceY;height=source;}
            break;
        }
        case 1:case 2:case 3:
            sx=sprite->sourceX;width=sprite->sourceWidth;sy=sprite->sourceY;height=sprite->sourceHeight;break;
        }
        st$2103[0].x=st$2103[1].x=(f32)sx/GStextureGetXsize(texture);
        st$2103[2].x=st$2103[3].x=(f32)(sx+width)/GStextureGetXsize(texture);
        st$2103[0].y=st$2103[3].y=(f32)(sy+height)/GStextureGetYsize(texture);
        st$2103[1].y=st$2103[2].y=(f32)sy/GStextureGetYsize(texture);
    }else {
        st$2103[0].x=st$2103[1].x=0.0f;st$2103[2].x=st$2103[3].x=1.0f;
        st$2103[0].y=st$2103[3].y=1.0f;st$2103[1].y=st$2103[2].y=0.0f;
    }
    s16 x,y;
    switch(sprite->mode) {
    default:case 0:x=sprite->x;y=sprite->y;width=spriteAbs(sprite->width);height=spriteAbs(sprite->height);break;
    case 1:x=sprite->x+(spriteAbs(sprite->width)-sprite->sourceWidth)/2;y=sprite->y+(spriteAbs(sprite->height)-sprite->sourceHeight)/2;break;
    case 2:x=sprite->x;y=sprite->y+(spriteAbs(sprite->height)-sprite->sourceHeight);break;
    case 3:x=sprite->x+(spriteAbs(sprite->width)-sprite->sourceWidth);y=sprite->y+(spriteAbs(sprite->height)-sprite->sourceHeight);break;
    }
    cxy$2104.x=width/2.0f+x;cxy$2104.y=height/2.0f+y;
    if(sprite->width<0) {xy$2102[0].x=xy$2102[1].x=(f32)(x+width)-cxy$2104.x;xy$2102[2].x=xy$2102[3].x=(f32)x-cxy$2104.x;}
    else {xy$2102[0].x=xy$2102[1].x=(f32)x-cxy$2104.x;xy$2102[2].x=xy$2102[3].x=(f32)(x+width)-cxy$2104.x;}
    if(sprite->height<0) {xy$2102[0].y=xy$2102[3].y=(f32)y-cxy$2104.y;xy$2102[1].y=xy$2102[2].y=(f32)(y+height)-cxy$2104.y;}
    else {xy$2102[0].y=xy$2102[3].y=(f32)(y+height)-cxy$2104.y;xy$2102[1].y=xy$2102[2].y=(f32)y-cxy$2104.y;}
    Quaternion rotation;
    if(*(f32*)sprite->reserved70!=0.0f)C_QUATRotAxisRad(&rotation,&yAxisVector,*(f32*)sprite->reserved70);
    else {rotation.x=0;rotation.y=0;rotation.z=0;rotation.w=1;}
    layer->primitiveType=0x80;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0,3,0,0,1,5,1,1,4));layer->beginSurface(4);
    for(s32 i=0;i<4;i++) {
        Vec position;position.x=xy$2102[i].x;position.y=0;position.z=xy$2102[i].y;
        GSvecTransformQuat(&position,&rotation,&position);
        xy$2102[i].x=position.x*sprite->scaleX;xy$2102[i].y=position.z*sprite->scaleY;
        *(s16*)0xcc008000=(s16)(cxy$2104.x+xy$2102[i].x);*(s16*)0xcc008000=(s16)(cxy$2104.y+xy$2102[i].y);
        *(u8*)0xcc008000=red;*(u8*)0xcc008000=green;*(u8*)0xcc008000=blue;*(u8*)0xcc008000=alpha;
        *(f32*)0xcc008000=st$2103[i].x;*(f32*)0xcc008000=st$2103[i].y;
    }
    layer->endSurface();
}

static inline void spriteVertex(s16 x,s16 y,u8 red,u8 green,u8 blue,u8 alpha) {
    *(s16*)0xcc008000=x;*(s16*)0xcc008000=y;
    *(u8*)0xcc008000=red;*(u8*)0xcc008000=green;*(u8*)0xcc008000=blue;*(u8*)0xcc008000=alpha;
}
static inline void spriteLineWidth(GSgfxLayer* layer) {
    layer->lineWidth=6;layer->lineOffset=0;layer->lineDirty|=4;layer->dirty|=1;layer->savedLineDirty|=4;layer->savedDirty|=1;
}
static inline void spritePrimitive(GSgfxLayer* layer,u32 primitive,u16 vertices) {
    layer->primitiveType=primitive;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0,3,0,0,1,5,0,0,0));layer->beginSurface(vertices);
}
extern "C" void winSpriteDraw(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite) {
    u8 red;
    u8 blue;
    u8 alpha;
    u32 color;
    u8 green;
    GSgfxLayer* layer;
    s32 layerID;
    GSgfxLayerFindByID(window->layerID);
    layerID=winSpriteGetLayerID(window,(WindowSprite*)sprite);
    layer=(GSgfxLayer*)GSgfxLayerFindByID(layerID);
    _spriteSetAlphaMode(layer,sprite->blendType);
    if(sprite->flags&8) {
        spriteSetOffset(layerID,(s16)(window->x+sprite->x),(s16)(window->y+sprite->y));spriteSetEnv(layerID);
        ((void(*)(tagWINDOW_WORK*,tagSPRITE_WORK*))sprite->callback)(window,sprite);
        spriteSetOffset(layerID,window->x,window->y);spriteSetEnv(layerID);_spriteSetAlphaMode(layer,sprite->blendType);
    }else spriteSetEnv(layerID);
    if((u8)winSpriteGetDisp(sprite)) {
        u8* sc=(u8*)&sprite->color;u8* wc=(u8*)&window->frame;
        red=sc[0]*wc[0]/255;green=sc[1]*wc[1]/255;blue=sc[2]*wc[2]/255;alpha=sc[3]*wc[3]/255;
        color=(red<<24)|(green<<16)|(blue<<8)|alpha;
        if(alpha) {
            if(sprite->flags&1) {menuSpriteBiosGetPtr(menuItemBiosGetPtr(window->menuID,sprite->itemID)->spriteID);winSpriteDrawTexture(window,sprite);}
            if(sprite->flags&2) {
                switch(sprite->texture) {
                case 0x10000:
                    spritePrimitive(layer,0x90,3);
                    spriteVertex(sprite->x,sprite->y,red,green,blue,alpha);
                    spriteVertex(sprite->x+sprite->sourceX,sprite->y+sprite->sourceY,red,green,blue,alpha);
                    spriteVertex(sprite->x+sprite->width,sprite->y+sprite->height,red,green,blue,alpha);
                    layer->endSurface();break;
                case 0x10001:menuSubDrawSimpleWindow(layer->blendSelection,sprite->x,sprite->y,sprite->width,sprite->height);break;
                case 0x10004:menuSubDrawNormalWindow2(layer->blendSelection,sprite->x,sprite->y,sprite->width,sprite->height,alpha);break;
                case 0x10005:menuSubDrawMsgWindow2(layer->blendSelection,sprite->x,sprite->y,sprite->width,sprite->height,alpha,1);break;
                case 0x10006: {
                    MENU_ITEM_dd_* item=menuItemBiosGetPtr(window->menuID,sprite->itemID);
                    tagWINDOW_WORK* active=windowSearchID(windowGetActiveID());
                    if(item->spriteID==0xbd) {
                        if(window==active)menuSubDrawCursorBack(layer->blendSelection,sprite->x,sprite->y,item->width,item->height,alpha,0);
                        else menuSubDrawCursorBackAnimeOnOff(layer->blendSelection,sprite->x,sprite->y,item->width,item->height,alpha,0,0);
                    }else menuSubDrawCursorBackAnimeOnOff(layer->blendSelection,sprite->x,sprite->y,item->width,item->height,alpha,0,0);
                    break;
                }
                case 0x10007: {
                    MENU_ITEM_dd_* item=menuItemBiosGetPtr(window->menuID,sprite->itemID);
                    tagWINDOW_WORK* active=windowSearchID(windowGetActiveID());
                    if(item->spriteID==0xc3) {
                        if(window==active)menuSubDrawCursorBack(layer->blendSelection,sprite->x,sprite->y,item->width,item->height,alpha,1);
                        else menuSubDrawCursorBackAnimeOnOff(layer->blendSelection,sprite->x,sprite->y,item->width,item->height,alpha,1,0);
                    }else menuSubDrawCursorBackAnimeOnOff(layer->blendSelection,sprite->x,sprite->y,item->width,item->height,alpha,1,0);
                    break;
                }
                case 0x10002: {
                    red=(u16)sprite->sourceX*red/255;green=(u16)sprite->sourceY*green/255;blue=(u16)sprite->sourceWidth*blue/255;
                    spritePrimitive(layer,0x98,4);
                    spriteVertex(sprite->x,sprite->y,red,green,blue,alpha);
                    spriteVertex(sprite->x+sprite->width,sprite->y,red,green,blue,alpha);
                    spriteVertex(sprite->x,sprite->y+sprite->height,red,green,blue,alpha);
                    spriteVertex(sprite->x+sprite->width,sprite->y+sprite->height,red,green,blue,alpha);
                    layer->endSurface();break;
                }
                case 0x10008: {
                    red=(u16)sprite->sourceX*red/255;green=(u16)sprite->sourceY*green/255;blue=(u16)sprite->sourceWidth*blue/255;
                    spriteLineWidth(layer);
                    spritePrimitive(layer,0xb0,5);
                    spriteVertex(sprite->x,sprite->y,red,green,blue,alpha);
                    spriteVertex(sprite->x+sprite->width,sprite->y,red,green,blue,alpha);
                    spriteVertex(sprite->x+sprite->width,sprite->y+sprite->height,red,green,blue,alpha);
                    spriteVertex(sprite->x,sprite->y+sprite->height,red,green,blue,alpha);
                    spriteVertex(sprite->x,sprite->y,red,green,blue,alpha);
                    layer->endSurface();break;
                }
                case 0x10003: {
                    red=(u16)sprite->sourceX*red/255;green=(u16)sprite->sourceY*green/255;blue=(u16)sprite->sourceWidth*blue/255;
                    spriteLineWidth(layer);
                    spritePrimitive(layer,0xa8,2);
                    spriteVertex(sprite->x,sprite->y,red,green,blue,alpha);
                    spriteVertex(sprite->width,sprite->height,red,green,blue,alpha);
                    layer->endSurface();break;
                }
                }
            }
            if(sprite->message)GSmsgPrintRect(layerID,sprite->x,sprite->y,sprite->width,sprite->height,color,sprite->message);
            if(sprite->flags&0x10) {menuSpriteBiosGetValPtr(((void*(*)(s32))menuSpriteBiosGetPtr)(sprite->resource));FlashSystemPlay(sprite->texture);FlashSystemDraw(sprite->texture,window,sprite);}
        }
    }
}
