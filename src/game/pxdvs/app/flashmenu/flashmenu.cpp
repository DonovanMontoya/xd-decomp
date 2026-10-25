// Needs extra cflags: -opt nopeephole
#include <game/pxdvs/app/flashmenu/flashmenuPrivate.hpp>

#include <libc/string.h>

extern "C" {
void GSmemFree(void *);
void flcalcUnitCxform(FLASHCXFORM *);
void flcalcUnitMatrix2(FLASHMATRIX *);
void GSprimSetBlendMode(s32);
void GSgfxLayerSetActive(s32);
void *GSgfxLayerFindByID(s32);
s32 flcalcBlend(s32, s32, f32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
u32 GSgfxVideoGetVsyncRate();
u32 timeGetLastFrameTime();
}
void GSprimSetup2DRender(GSgfxLayer *);
void operator delete(void *);
void operator delete[](void *);
extern "C" void* GSmemAlloc(u32);

#define FLASH_FREE(p) \
    if (p != 0) { \
        if (p != 0) { \
            GSmemFree(p); \
        } \
        p = 0; \
    }

GStexture *FlashMenu::GetGStexture(long id) {
    for (s32 i = 0; i < 30; i++) {
        if (textures[i].id == id) {
            return textures[i].texture;
        }
    }
    return 0;
}

FlashMenu::~FlashMenu() {
}

FlashMenu::FlashMenu() {
    field10 = 0;
    field1E = 0;
    field20 = 0;
}

void FlashMenu::Release() {
    struct {FlashHeader* value;} headerRef;headerRef.value=header;
    FLASH_FREE(memory)
    u16 i;
    u16 j;
    for (i = 0; i < headerRef.value->layerCount; i++) {
        if (layers[i].items != 0) {
            for (j = 0; j < headerRef.value->itemCount; j++) {
                if (layers[i].items[j].extra != 0) {
                    delete[] (u8 *)layers[i].items[j].extra;
                    layers[i].items[j].extra = 0;
                }
            }
            delete[] (u8 *)layers[i].items;
            layers[i].items = 0;
        }
    }
    FLASH_FREE(layers)
    for (i = 0; i < headerRef.value->itemCount; i++) {
        if (items[i].extra != 0) {
            delete[] (u8 *)items[i].extra;
            items[i].extra = 0;
        }
    }
    FLASH_FREE(items)
    FlashMenuLabel *label = labels;
    do {
        FlashMenuLabel *cur = label;
        if (label != 0) {
            label = label->next;
            delete cur;
        }
    } while (label != 0);
}

void FlashMenu::Draw(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    u32 frame;
    u8 rate;
    if (memory != 0) {
        s32 layerId = winSpriteGetLayerID(win, sprite);
        GSgfxLayerSetActive(layerId);
        GSgfxLayerFindByID(layerId);
        DrawSub((GSgfxLayerID)layerId, win, sprite);
        frame = playFrame;
        if (paused == 0) {
            rate = GSgfxVideoGetVsyncRate();
            u32 delta = timeGetLastFrameTime();
            if (delta >= 10) {
                delta = 1;
            }
            if (delta == 0) {
                fps = rate;
            } else {
                fps = (f32)rate / (f32)delta;
            }
            frame += delta;
            if (frame > endFrame) {
                if (loop != 0) {
                    frame = loopFrame;
                    FlashItem *item = items;
                    FlashHeader *hdr = header;
                    for (s32 i = 0; i < hdr->itemCount; i++, item++) {
                        item->depth = 0.0f;
                        item->field30 = 0;
                        item->field34 = 0;
                        flcalcUnitCxform(&item->cxform);
                    }
                } else {
                    frame = endFrame;
                }
            }
            playFrame = frame;
        }
        GSgfxLayerSetActive(7);
    }
}

void FlashMenu::InitDataPointer() {
    FlashDataPointer *pointer = (FlashDataPointer *)memory;
    FlashItem *item = items;
        s32 i = 0;
        FlashHeader *hdr = header;
        for (s32 n = 0; n < 200; n++, pointer++) {
            pointer->type = 0;
            pointer->data = 0;
        }
        for (; i < hdr->itemCount; i++, item++) {
            item->field30 = 0;
            item->field34 = 0;
            item->frame = 0;
            item->depth = 0.0f;
            item->flag = 0;
            flcalcUnitCxform(&item->cxform);
            flcalcUnitMatrix2(&item->matrix);
        }
        s32 l = 0;
        s32 off = 0;
        for (; l < hdr->layerCount; l++, off += 8) {
            s32 j = 0;
            s32 ioff = 0;
            for (; j < hdr->itemCount; j++, ioff += 0x40) {
                FlashLayer *layer = (FlashLayer *)((u8 *)layers + off);
                *(s16 *)((u8 *)layer->items + ioff) = 0;
                *(f32 *)((u8 *)layer->items + (ioff + 0x1C)) = 0.0f;
                *(s32 *)((u8 *)layer->items + (ioff + 0x30)) = 0;
                *(s32 *)((u8 *)layer->items + (ioff + 0x34)) = 0;
                *(u8 *)((u8 *)layer->items + (ioff + 0x3C)) = 0;
                flcalcUnitMatrix2((FLASHMATRIX *)((u8 *)layer->items + (ioff + 4)));
                flcalcUnitCxform((FLASHCXFORM *)((u8 *)layer->items + (ioff + 0x20)));
            }
        }
}

void FlashMenu::Update() {
    if (memory != 0) {
        FlashItem *item = items;
        s32 i = 0;
        FlashHeader *hdr = header;
        for (; i < hdr->itemCount; i++, item++) {
            item->field30 = 0;
            item->field34 = 0;
            item->frame = 0;
            item->depth = 0.0f;
            flcalcUnitCxform(&item->cxform);
            flcalcUnitMatrix2(&item->matrix);
        }
        s32 l = 0;
        s32 off = 0;
        for (; l < hdr->layerCount; l++, off += 8) {
            s32 j = 0;
            FlashLayer *layer = (FlashLayer *)((u8 *)layers + off);
            for (; j < hdr->itemCount; j++) {
                layer->items[j].frame = 0;
                layer->items[j].depth = 0.0f;
                layer->items[j].field30 = 0;
                layer->items[j].field34 = 0;
                layer->items[j].flag = 0;
                flcalcUnitMatrix2(&layer->items[j].matrix);
                flcalcUnitCxform(&layer->items[j].cxform);
            }
        }
        GSprimSetup2DRender(0);
        GSprimSetBlendMode(1);
        u32 target = playFrame;
        if (header->frameCount > target) {
            pos = start;
            frameStart = target;
            field14 = 0;
            u8 *tag = (u8 *)header + pos;
            for (;;) {
                if (ParseTag(*(u32 *)tag, *(u32 *)(tag + 4), 0, 0, 0)) {
                    break;
                }
                tag = (u8 *)header + pos;
            }
        }
        field20 = 0;
    }
}

void FlashMenu::ParsePlaceObject2(bool) {
    ParsePlaceObject2Sub((_PLACEOBJECT2 *)((u32)header + pos));
}

struct _DEFINETEXT {
    u8 reserved0[0x2C];
    u32 records;
};
struct TextGlyphs {
    u8 count;
    u8 pad[3];
    u32 data;
};
struct TextRecord {
    u8 type;
    u8 pad[3];
    u32 data;
    u32 next;
};

void FlashMenu::ParaseTextRecord(_DEFINETEXT *text) {
    TextRecord *rec;
    u32 v;
    if (header->relocated == 0 && field1E != 0) {
        v = (u32)text + text->records;
        text->records = v;
    } else {
        v = text->records;
    }
    rec = (TextRecord *)v;
    for (;;) {
        switch (rec->type) {
        case 0:
            break;
        case 1:
            if (header->relocated == 0 && field1E != 0) {
                rec->data = (u32)text + rec->data;
            }
            break;
        case 2: {
            TextGlyphs *glyphs;
            s32 i;
            if (header->relocated == 0 && field1E != 0) {
                glyphs = (TextGlyphs *)((u32)text + rec->data);
                rec->data = (u32)glyphs;
            } else {
                glyphs = (TextGlyphs *)rec->data;
            }
            if (header->relocated == 0 && field1E != 0) {
                glyphs->data = (u32)text + glyphs->data;
            }
            for (i = 0; i < glyphs->count; i++) {
            }
            break;
        }
        }
        u32 n = rec->next;
        if (n == 0) {
            return;
        }
        u32 w;
        if (header->relocated == 0 && field1E != 0) {
            w = (u32)text + n;
            rec->next = w;
        } else {
            // volatile forces the reload the original emitted instead of reusing 'n'.
            w = *(volatile u32 *)&rec->next;
        }
        rec = (TextRecord *)w;
    }
}

struct _DEFINEFONT2 {
    u16 id;
    u8 reserved2[2];
    u16 glyphCount;
    u8 reserved6[0xA];
    u32 field10;
    u32 field14;
    u8 reserved18[4];
    u32 shapes;
};

void FlashMenu::ParseDefineFont2Sub(_DEFINEFONT2 *font) {
    u16 id = font->id;
    u16 count = font->glyphCount;
    s32 i;
    u32 *shape;
    memory[id].type = 8;
    memory[id].data = font;
    if (count != 0) {
        if (font->field14 != 0) {
            for (i = 0; i < count; i++) {
            }
        }
        if (header->relocated == 0 && field1E != 0) {
            shape = (u32 *)((u32)font + font->shapes);
            font->shapes = (u32)shape;
        } else {
            shape = (u32 *)font->shapes;
        }
        for (s32 j = 0; j < count; shape++, j++) {
            u32 v;
            if (header->relocated == 0 && field1E != 0) {
                v = (u32)font + *shape;
                *shape = v;
            } else {
                v = *shape;
            }
            ParseDefineShapeSub((_DEFINESHAPE *)v);
        }
        u32 f10 = font->field10;
        if (f10 != 0) {
            if (header->relocated == 0 && field1E != 0) {
                font->field10 = (u32)font + f10;
            }
            for (i = 0; i < count; i++) {
            }
        }
    }
}

u16 FlashMenu::GetFrameFromLabel(char *name) {
    if (labels != 0) {
        FlashMenuLabel *label = labels;
        for (;;) {
            if (label == 0) {
                break;
            }
            if (strcmp(name, label->name) == 0) {
                return label->frame;
            }
            label = label->next;
        }
    }
    return 0;
}

struct _SHAPERECORD {
    u8 type;
    u8 pad[3];
    void *data;
    _SHAPERECORD *next;
};
struct SRecordStyle {
    u8 flags;
    u8 pad[3];
    s32 x;
    s32 y;
};
struct SRecordLine {
    s32 pad;
    s32 x;
    s32 y;
};
struct SRecordCurve {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};

void FlashMenu::BlendShapeRecord(_SHAPERECORD *dst, _SHAPERECORD *a, _SHAPERECORD *b, f32 t) {
    u8 more = 1;
    u8 hold = 0;
    do {
        switch (a->type) {
        case 0:
            more = 0;
            break;
        case 1: {
            SRecordStyle *sa = (SRecordStyle *)a->data;
            SRecordStyle *sb = (SRecordStyle *)b->data;
            SRecordStyle *sd = (SRecordStyle *)dst->data;
            if ((sa->flags & 1) != 0) {
                sd->x = flcalcBlend(sa->x, sb->x, t);
                sd->y = flcalcBlend(sa->y, sb->y, t);
                if (b->type != 1) {
                    hold = 1;
                }
            } else {
                hold = 1;
            }
            break;
        }
        case 2: {
            SRecordLine *sa = (SRecordLine *)a->data;
            SRecordLine *sb = (SRecordLine *)b->data;
            SRecordLine *sd = (SRecordLine *)dst->data;
            sd->x = flcalcBlend(sa->x, sb->x, t);
            sd->y = flcalcBlend(sa->y, sb->y, t);
            break;
        }
        case 3: {
            SRecordCurve *sa = (SRecordCurve *)a->data;
            SRecordCurve *sb = (SRecordCurve *)b->data;
            SRecordCurve *sd = (SRecordCurve *)dst->data;
            sd->a = flcalcBlend(sa->a, sb->a, t);
            sd->b = flcalcBlend(sa->b, sb->b, t);
            sd->c = flcalcBlend(sa->c, sb->c, t);
            sd->d = flcalcBlend(sa->d, sb->d, t);
            break;
        }
        }
        a = a->next;
        dst = dst->next;
        if (hold == 0) {
            b = b->next;
        }
        hold = 0;
        if (a->next == 0) {
            more = 0;
        }
    } while (more != 0);
}

u32 FlashMenu::GetPlayFrame() {
    return playFrame;
}

void FlashMenu::SetPlayFrame(unsigned long frame) {
    playFrame = frame;
}

struct _PLACEOBJECT2 {
    u8 flags;u8 reserved1[3];s32 character,depth;
    FLASHMATRIX matrix;FLASHCXFORM cxform;u32 ratio,name;
};
inline void flashPlaceReference(FlashMenu* menu,s32 depth, _PLACEOBJECT2* object) {
    if((s32)menu->field14 != 0) {
        if(menu->activeFrame <= ((u16*)menu->items[menu->field10].extra)[(u16)menu->activeLayer]) {
            FlashItem* item=&((FlashLayer*)menu->layers)[menu->activeLayer].items[depth];
            item->field30=0;item->field34=(s32)object;
        }
    } else {menu->items[depth].field30=0;menu->items[depth].field34=(s32)object;}
}
inline void flashPlaceCharacter(FlashMenu* menu,u16 character, s32 depth) {
    if((s32)menu->field14 != 0) {
        if(menu->activeFrame <= ((u16*)menu->items[menu->field10].extra)[(u16)menu->activeLayer]) {
            FlashItem* item=&((FlashLayer*)menu->layers)[menu->activeLayer].items[depth];
            item->frame=character;
        }
    } else {menu->items[depth].frame=character;}
}
inline void flashPlaceMatrix(FlashMenu* menu,FLASHMATRIX* matrix,s32 depth) {
    if((s32)menu->field14 != 0) {
        if(menu->activeFrame <= ((u16*)menu->items[menu->field10].extra)[(u16)menu->activeLayer]) {
            FlashItem* item=&((FlashLayer*)menu->layers)[menu->activeLayer].items[depth];
            memcpy(&item->matrix,matrix,0x18);
        }
    } else {memcpy(&menu->items[depth].matrix,matrix,0x18);}
}
inline void flashPlaceColor(FlashMenu* menu,FLASHCXFORM* color,s32 depth) {
    if((s32)menu->field14 != 0) {
        if(menu->activeFrame <= ((u16*)menu->items[menu->field10].extra)[(u16)menu->activeLayer]) {
            FlashItem* item=&((FlashLayer*)menu->layers)[menu->activeLayer].items[depth];
            memcpy(&item->cxform,color,0x10);
        }
    } else {memcpy(&menu->items[depth].cxform,color,0x10);}
}
inline void flashPlaceRatio(FlashMenu* menu,u32 ratio,s32 depth) {
    if((s32)menu->field14 != 0) {
        if(menu->activeFrame <= ((u16*)menu->items[menu->field10].extra)[(u16)menu->activeLayer]) {
            FlashItem* item=&((FlashLayer*)menu->layers)[menu->activeLayer].items[depth];
            item->depth=(f32)ratio/65536.0f;
        }
    } else {menu->items[depth].depth=(f32)ratio/65536.0f;}
}
void FlashMenu::ParsePlaceObject2Sub(_PLACEOBJECT2* object) {
    u8 flags=object->flags;
    flashPlaceReference(this,object->depth,object);
    if(flags&2) flashPlaceCharacter(this,object->character,object->depth);
    if(flags&4) flashPlaceMatrix(this,&object->matrix,object->depth);
    if(flags&8) flashPlaceColor(this,&object->cxform,object->depth);
    if(flags&16) flashPlaceRatio(this,object->ratio,object->depth);
    if((flags&32) && header->relocated==0 && field1E!=0) object->name=(u32)object+object->name;
}

struct FlashGradientEntry {u8 ratio;u8 reserved1[3];u32 color;};
struct FlashFillStyle {u8 flags;u8 reserved1[3];u32 color;s32 matrix[6];u8 count;u8 reserved21[3];FlashGradientEntry gradients[8];u8 reserved64[0x1C];};
struct _DEFINESHAPE {u32 id;s32 fillCount;FlashFillStyle* fills;s32 lineCount;void* lines;u32 reserved14;_SHAPERECORD* records;};
struct FlashShapeEdges {u8 flags;u8 reserved1[0xF];s32 pointCount;void* points;s32 edgeCount;void* edges;};
void FlashMenu::ParseDefineShapeSub(_DEFINESHAPE* shape) {
    FlashFillStyle* fills;
    s32 fillCount=shape->fillCount;
    if(header->relocated==0 && field1E!=0) {fills=(FlashFillStyle*)((u32)shape+(u32)shape->fills);shape->fills=fills;}
    else fills=shape->fills;
    FlashFillStyle* fill=fills;
    s32 gradient=fills->flags&0x10;
    for(s32 i=0;i<fillCount;fill++,i++) {
        if(gradient) {
            s32 count=fill->count;
            for(s32 j=0;j<count;j++) {}
        }
    }
    s32 lineCount=shape->lineCount;
    if(header->relocated==0 && field1E!=0) shape->lines=(void*)((u32)shape+(u32)shape->lines);
    for(s32 i=0;i<lineCount;i++) {}
    _SHAPERECORD* record;
    if(header->relocated==0 && field1E!=0) {record=(_SHAPERECORD*)((u32)shape+(u32)shape->records);shape->records=record;}
    else record=shape->records;
    u32 id=shape->id;
    memory[id].type=2;
    memory[id].data=shape;
    for(;;) {
        if(record->next==0) return;
        switch(record->type) {
        case 0:break;
        case 1:{
            FlashShapeEdges* edges;
            if(header->relocated==0 && field1E!=0) {edges=(FlashShapeEdges*)((u32)shape+(u32)record->data);record->data=edges;}
            else edges=(FlashShapeEdges*)record->data;
            if(edges->flags&0x10) {
                s32 points=edges->pointCount;
                if(header->relocated==0 && field1E!=0) edges->points=(void*)((u32)shape+(u32)edges->points);
                while(points-- > 0) {}
                s32 count=edges->edgeCount;
                if(header->relocated==0 && field1E!=0) edges->edges=(void*)((u32)shape+(u32)edges->edges);
                for(s32 i=0;i<count;i++) {}
            }
            break;
        }
        case 2:{
            SRecordLine* line;
            if(header->relocated==0 && field1E!=0) {line=(SRecordLine*)((u32)shape+(u32)record->data);record->data=line;}
            else line=(SRecordLine*)record->data;
            if(line->x!=0 && line->y==0) {}
            break;
        }
        case 3:
            if(header->relocated==0 && field1E!=0) record->data=(void*)((u32)shape+(u32)record->data);
            break;
        }
        _SHAPERECORD* next;
        if(header->relocated==0 && field1E!=0) {next=(_SHAPERECORD*)((u32)shape+(u32)record->next);record->next=next;}
        else next=record->next;
        record=next;
    }
}
struct FlashMorphGradientEntry {u8 ratioA,ratioB;u8 reserved2[2];u32 colorA,colorB;};
struct FlashMorphFillStyle {u8 flags;u8 reserved1[3];u32 colorA,colorB;s32 matrixA[6],matrixB[6];u8 count;u8 reserved3D[3];FlashMorphGradientEntry gradients[8];u8 reservedA0[0x34];};
struct _DEFINEMORPHSHAPE {u32 id;u32 reserved4;u32 fillCount;FlashMorphFillStyle* fills;u32 lineCount;void* lines;u32 reserved18;void* start;u32 reserved20;void* end;_DEFINESHAPE* shapes[3];};
void FlashMenu::ParseDefineMorphShapeSub(_DEFINEMORPHSHAPE* morph) {
    struct {s32 index,count;} counters;
    u32 lines;
    s32 offset;
    s32 i;
    if(morph->fillCount) {
        i=0;
        offset=0;
        for(;i<(s32)morph->fillCount;i++) {
            FlashMorphFillStyle* fills;
            if(header->relocated==0 && field1E!=0) {fills=(FlashMorphFillStyle*)((u32)morph+(u32)morph->fills);morph->fills=fills;}
            else fills=morph->fills;
            FlashMorphFillStyle* fill=(FlashMorphFillStyle*)((u8*)fills+offset);
            if(fill->flags&0x10) {
                counters.count=fill->count;
                for(counters.index=0;counters.index<counters.count;counters.index++) {}
            }
            offset+=0xD4;
        }
    }
    if(header->relocated==0 && field1E!=0) morph->lines=(void*)((u32)morph+(u32)morph->lines);
    lines=morph->lineCount;
    if(lines) for(s32 i=0;i<(s32)lines;i++) {}
    if(header->relocated==0 && field1E!=0) morph->start=(void*)((u32)morph+(u32)morph->start);
    if(header->relocated==0 && field1E!=0) morph->end=(void*)((u32)morph+(u32)morph->end);
    _DEFINESHAPE* shape;
    if(header->relocated==0 && field1E!=0) {shape=(_DEFINESHAPE*)((u32)morph+(u32)morph->shapes[0]);morph->shapes[0]=shape;}else shape=morph->shapes[0];
    ParseDefineShapeSub(shape);
    if(header->relocated==0 && field1E!=0) {shape=(_DEFINESHAPE*)((u32)morph+(u32)morph->shapes[1]);morph->shapes[1]=shape;}else shape=morph->shapes[1];
    ParseDefineShapeSub(shape);
    if(header->relocated==0 && field1E!=0) {shape=(_DEFINESHAPE*)((u32)morph+(u32)morph->shapes[2]);morph->shapes[2]=shape;}else shape=morph->shapes[2];
    ParseDefineShapeSub(shape);
    u32 index=morph->id;
    memory[index].type=1;
    memory[index].data=morph;
}

struct FlashTagName {s32 id;const char* name;};
static const FlashTagName _fltagnametable[] = {
    {0, "stagEnd"},
    {1, "stagShowFrame"},
    {2, "stagDefineShape"},
    {3, "stagFreeCharacter"},
    {4, "stagPlaceObject"},
    {5, "stagRemoveObject"},
    {6, "stagDefineBits"},
    {7, "stagDefineButton"},
    {8, "stagJPEGTables"},
    {9, "stagSetBackgroundColor"},
    {10, "stagDefineFont"},
    {11, "stagDefineText"},
    {12, "stagDoAction"},
    {13, "stagDefineFontInfo"},
    {14, "stagDefineSound"},
    {14, "stagDefineSound"},
    {17, "stagDefineButtonSound"},
    {18, "stagSoundStreamHead"},
    {19, "stagSoundStreamBlock"},
    {20, "stagDefineBitsLossless"},
    {21, "stagDefineBitsJPEG2"},
    {22, "stagDefineShape2"},
    {23, "stagDefineButtonCxform"},
    {24, "stagProtect"},
    {26, "stagPlaceObject2"},
    {28, "stagRemoveObject2"},
    {32, "stagDefineShape3"},
    {33, "stagDefineText2"},
    {34, "stagDefineButton2"},
    {35, "stagDefineBitsJPEG3"},
    {36, "stagDefineBitsLossless2"},
    {37, "stagDefineEditText"},
    {39, "stagDefineSprite"},
    {40, "stagNameCharacter"},
    {43, "stagFrameLabel"},
    {45, "stagSoundStreamHead2"},
    {46, "stagDefineMorphShape"},
    {48, "stagDefineFont2"},
    {56, "stagExportAssets"},
    {57, "stagImportAssets"},
    {-1, 0},
};
struct FlashTag {u32 type,size;};

void FlashMenu::Init(void* data,unsigned long parameter) {
    GSgfxLayer* layer=(GSgfxLayer*)GSgfxLayerFindByID(7);
    field34=parameter;
    GSprimSetup2DRender(layer);
    GSprimSetBlendMode(1);
    memory=(FlashDataPointer*)GSmemAlloc(0x640);
    FlashHeader* input=(FlashHeader*)data;
    u16 layerCount;
    if(input->layerCount==0) {layerCount=40;input->layerCount=40;}else layerCount=input->layerCount;
    u16 itemCount;
    if(input->itemCount==0) {itemCount=40;input->itemCount=40;}else itemCount=input->itemCount;
    layers=(FlashLayer*)GSmemAlloc((layerCount*8+31)&~31);
    for(s32 i=0;i<layerCount;i++) {
        layers[i].items=0;
        layers[i].items=new FlashItem[itemCount];
        for(s32 j=0;j<itemCount;j++) {
            layers[i].items[j].extra=0;
            layers[i].items[j].extra=new u16[layerCount];
        }
    }
    items=(FlashItem*)GSmemAlloc(((itemCount<<6)+31)&~31);
    for(s32 i=0;i<itemCount;i++) {items[i].extra=0;items[i].extra=new u16[layerCount];}
    labels=0;
    pos=0x30;
    frameStart=0;
    field1E=0;
    for(s32 i=0;i<layerCount;i++) layers[i].reserved0=0;
    start=pos;
    header=input;
    FlashHeader* original=header;
    field14=0;
    FlashTag* tag=(FlashTag*)((u8*)original+pos);
    frameStart=0;
    field1E=1;
    for(s32 i=0;i<30;i++) {textures[i].id=0;textures[i].texture=0;}
    InitDataPointer();
    FlashHeader* hdr=header;
    playFrame=0;
    fps=0.0f;
    for(u16 item=0;item<hdr->itemCount;item++) {
        for(u16 layer=0;layer<hdr->layerCount;layer++) ((u16*)items[item].extra)[layer]=0;
    }
    for(;;) {
        const FlashTagName* name=_fltagnametable;
        while(name->id!=(s32)tag->type && name->id>=0) ++name;
        if(ParseTag(tag->type,tag->size,true,false,true)) break;
        tag=(FlashTag*)((u8*)header+pos);
    }
    if(field1E!=0 && original->relocated==0) original->relocated=(u32)header;
    loopFrame=0;
    endFrame=frameStart-1;
    loop=0;
    paused=0;
    totalFrames=frameStart;
}

extern "C" u32 GStextureLoad(GStexture*);
struct FlashAction {u32 type;void* data;FlashAction* next;};
struct FlashBitmap {u16 format,id;u8 reserved4[0xC];GStexture* texture;};
struct FlashEditText {u32 reserved0,color;u16 id;u16 flags;u8 reservedC[2];u16 height;u8 reserved10[0xC];u16* text;};
struct _DEFINESPRITE {u16 id,frames;u8 data[1];};
inline void flashDefineBits(FlashMenu* menu,FlashBitmap* bitmap,bool load) {
    if(load) {
        GStexture* texture;
        if(menu->header->relocated==0 && menu->field1E!=0) {texture=(GStexture*)((u32)bitmap+(u32)bitmap->texture);bitmap->texture=texture;}
        else texture=bitmap->texture;
        if(load && GStextureLoad(texture)) {
            u16 id=bitmap->id;
            for(s32 i=0;i<30;i++) {
                if(menu->textures[i].id==id) break;
                if(menu->textures[i].id==0) {menu->textures[i].id=id;menu->textures[i].texture=texture;break;}
            }
        }
    }
}
u8 FlashMenu::ParseTag(unsigned long type,unsigned long size,bool advance,bool,bool load) {
    u8 end=0;
    if(type!=0) pos+=8;
    switch(type) {
    case 0:
        activeFrame=0;
        if((s32)--field14<0) end=1;else pos+=8;
        break;
    case 1:{
        u32 frame=*(u32*)((u8*)header+pos);
        if(load && (s32)field14==0) frameStart++;
        u16 current=frame;
        if((s32)field14!=0) activeFrame=current;
        else if(!advance && current>(u16)playFrame) end=1;
        break;
    }
    case 2:{_DEFINESHAPE* shape=(_DEFINESHAPE*)((u8*)header+pos);if(load) ParseDefineShapeSub(shape);break;}
    case 11:{
        _DEFINETEXT* text=(_DEFINETEXT*)((u8*)header+pos);
        u32 index=*(u16*)text;
        memory[index].type=0x20;
        memory[index].data=text;
        ParaseTextRecord(text);break;
    }
    case 12:{
        FlashAction** root=(FlashAction**)((u8*)header+pos);
        FlashAction* action;
        if(header->relocated==0 && field1E!=0) {action=(FlashAction*)((u32)root+(u32)*root);*root=action;}
        else action=*root;
        for(;;) {
            if(!action) break;
            if(action->data && header->relocated==0 && field1E!=0) action->data=(void*)((u32)root+(u32)action->data);
            u32 next=(u32)action->next;
            if(next) {
                FlashAction* n;
                if(header->relocated==0 && field1E!=0) {n=(FlashAction*)((u32)root+next);action->next=n;}
                else n=(FlashAction*)((u32*)action)[2];
                action=n;
            } else action=(FlashAction*)next;
        }
        break;
    }
    case 20:{
        flashDefineBits(this,(FlashBitmap*)((u8*)header+((pos+31)&~31)),load);
        break;
    }
    case 22:{_DEFINESHAPE* shape=(_DEFINESHAPE*)((u8*)header+pos);if(load) ParseDefineShapeSub(shape);break;}
    case 26:ParsePlaceObject2(load);break;
    case 28:flashPlaceReference(this,*(u16*)((u8*)header+pos),0);break;
    case 32:{_DEFINESHAPE* shape=(_DEFINESHAPE*)((u8*)header+pos);if(load) ParseDefineShapeSub(shape);break;}
    case 33:{
        _DEFINETEXT* text=(_DEFINETEXT*)((u8*)header+pos);
        u32 index=*(u16*)text;
        memory[index].type=0x20;
        memory[index].data=text;
        ParaseTextRecord(text);break;
    }
    case 36:{
        flashDefineBits(this,(FlashBitmap*)((u8*)header+((pos+31)&~31)),load);
        break;
    }
    case 37:{
        FlashEditText* text=(FlashEditText*)((u8*)header+pos);
        u32 index=text->id;
        u16 flags=text->flags;
        memory[index].type=0x10;
        memory[index].data=text;
        if(flags&0x80) {
            u16* string;
            if(header->relocated==0 && field1E!=0) {string=(u16*)((u32)text+(u32)text->text);text->text=string;}
            else string=text->text;
            for(;;) {
                if(*string==0) break;
                string++;
            }
        }
        break;
    }
    case 39:{
        _DEFINESPRITE* sprite=(_DEFINESPRITE*)((u8*)header+pos);
        u32 index=sprite->id;
        memory[index].type=4;
        memory[index].data=sprite;
        field14++;
        activeLayer=sprite->id;
        layers[activeLayer].reserved0=sprite->frames;
        break;
    }
    case 43:{
        char** label=(char**)((u8*)header+pos);
        if(header->relocated==0 && field1E!=0) *label=(char*)((u32)*label+(u32)label);
        if(load) {
            FlashMenuLabel* current=labels;
            if(current) {
                for(;;) {
                    if(current->next==0) {
                        current->next=new FlashMenuLabel;
                        current=current->next;
                        current->frame=frameStart;
                        current->name=*label;
                        break;
                    }
                    current=current->next;
                }
            } else {
                labels=new FlashMenuLabel;
                labels->frame=frameStart;
                labels->name=*label;
            }
        }
        break;
    }
    case 48:ParseDefineFont2Sub((_DEFINEFONT2*)((u8*)header+pos));break;
    case 46:ParseDefineMorphShapeSub((_DEFINEMORPHSHAPE*)((u8*)header+pos));break;
    }
    pos+=size;
    return end;
}

extern "C" {
s32 flcalcBlendColor(s32,s32,f32);
void flcalcConvFlashMatrix(FLASHMATRIXF*,FLASHMATRIX*);
void flcalcMulMatrixf(FLASHMATRIXF*,FLASHMATRIXF*,FLASHMATRIXF*);
void flcalcMulCxform(FLASHCXFORM*,FLASHCXFORM*,FLASHCXFORM*);
void vectorGraph(s32,s32*,s32*,_SHAPERECORD*,FLASHMATRIXF*,FLASHMATRIXF*,FLASHCXFORM*,u8);
void msgctrlSetValue(s32,u32);
void GSmsgPrint2(s32,s32,s32,s32,u32);
}
static u8 _drawflag=1;
void FlashMenu::DrawSprite(_DEFINESPRITE* sprite,FLASHMATRIXF* parent,FLASHCXFORM* parentColor,u16 outerItem,u8 flags) {
    u16 parentItem=outerItem;
    FLASHCXFORM combinedColor;
    FLASHMATRIXF textMatrix;
    _DEFINESHAPE drawShape;
    FLASHMATRIXF local,combined;
    FlashHeader* hdr=header;
    s32 inherited=flags;
    s32 offset=0;
    for(u16 i=0;i<hdr->itemCount;i++,offset+=0x40) {
        FlashItem* item=(FlashItem*)((u8*)layers[sprite->id].items+offset);
        if(item->field34) {
            FlashDataPointer* entry=&memory[item->frame];
            flcalcConvFlashMatrix(&local,&item->matrix);
            field10=i;
            f32 ratio=((FlashItem*)((u8*)layers[sprite->id].items+offset))->depth;
            flcalcMulMatrixf(&combined,&local,parent);
            flcalcMulCxform(&combinedColor,&item->cxform,parentColor);
            item->flag = inherited | item->flag | ((_PLACEOBJECT2*)item->field34)->flags;
            if(entry->type&1) {
                u8 drawFlags=item->flag;
                _DEFINEMORPHSHAPE* morph=(_DEFINEMORPHSHAPE*)entry->data;
                memset(&drawShape,0,0x1C);
                drawShape.fillCount=morph->reserved18;
                drawShape.fills=(FlashFillStyle*)morph->start;
                drawShape.lineCount=morph->reserved20;
                drawShape.lines=morph->end;
                s32 inputOffset=0,outputOffset=0;
                for(s32 fill=0;fill<(s32)morph->fillCount;fill++,inputOffset+=0xD4,outputOffset+=0x80) {
                    FlashMorphFillStyle* source=(FlashMorphFillStyle*)((u8*)morph->fills+inputOffset);
                    FlashFillStyle* destination=(FlashFillStyle*)((u8*)drawShape.fills+outputOffset);
                    if(source->flags==0) destination->color=flcalcBlendColor(source->colorA,source->colorB,ratio);
                    else if(source->flags&16) {
                        u8* input=(u8*)source+0x3C;
                        u8* output=(u8*)destination+0x20;
                        for(s32 j=0;j<source->count;j++,input+=0xC,output+=8) {
                            output[4]=flcalcBlend(input[4],input[5],ratio);
                            *(u32*)(output+8)=flcalcBlendColor(*(u32*)(input+8),*(u32*)(input+12),ratio);
                        }
                        s32* matrix=destination->matrix;
                        matrix[0]=flcalcBlend(source->matrixA[0],source->matrixB[0],ratio);
                        matrix[1]=flcalcBlend(source->matrixA[1],source->matrixB[1],ratio);
                        matrix[2]=flcalcBlend(source->matrixA[2],source->matrixB[2],ratio);
                        matrix[3]=flcalcBlend(source->matrixA[3],source->matrixB[3],ratio);
                        matrix[4]=flcalcBlend(source->matrixA[4],source->matrixB[4],ratio);
                        matrix[5]=flcalcBlend(source->matrixA[5],source->matrixB[5],ratio);
                    }
                }
                BlendShapeRecord(morph->shapes[2]->records,morph->shapes[0]->records,morph->shapes[1]->records,ratio);
                vectorGraph(field34,&drawShape.fillCount,&drawShape.lineCount,morph->shapes[2]->records,parent,&local,&combinedColor,drawFlags);
            }
            if(entry->type&4) {
                _DEFINESPRITE* child=(_DEFINESPRITE*)entry->data;
                if(child!=sprite) {
                    u32 frame=playFrame;
                    if(header->frameCount>frame) {
                        pos=start;frameStart=frame;field14=0;
                        FlashTag* tag=(FlashTag*)((u8*)header+pos);
                        while(!ParseTag(tag->type,tag->size,false,false,false)) tag=(FlashTag*)((u8*)header+pos);
                    }
                    FlashItem* current=(FlashItem*)((u8*)layers[sprite->id].items+offset);
                    flcalcConvFlashMatrix(&local,&current->matrix);
                    flcalcMulMatrixf(&combined,&local,parent);
                    flcalcMulCxform(&combinedColor,&current->cxform,parentColor);
                    DrawSprite(child,&combined,&combinedColor,i,item->flag);
                }
            }
            if(entry->type&2) {
                _DEFINESHAPE* shape=(_DEFINESHAPE*)entry->data;
                if(_drawflag) vectorGraph(field34,&shape->fillCount,&shape->lineCount,shape->records,parent,&local,&combinedColor,item->flag);
                field20++;
            }
            if(entry->type&0x10) {
                FlashEditText* text=(FlashEditText*)entry->data;
                if(text->text) {
                    s32 color=text->color;
                    u16 height=text->height/20;
                    if(parent) flcalcMulMatrixf(&textMatrix,&local,parent);
                    else textMatrix=local;
                    msgctrlSetValue(0x37,(u32)text->text);
                    switch(height) {
                    case 13:GSmsgPrint2(7,(s32)textMatrix.m[4],(s32)textMatrix.m[5],color,0x4278);break;
                    case 22:GSmsgPrint2(7,(s32)textMatrix.m[4],(s32)textMatrix.m[5],color,0x4275);break;
                    default:case 18:GSmsgPrint2(7,(s32)textMatrix.m[4],(s32)textMatrix.m[5],color,0x4276);break;
                    }
                }
            }
            if(entry->type&0x20) DrawText((_DEFINETEXT*)entry->data,parent,&local,parentColor,item->flag);
        }
    }
    u16 id=sprite->id;
    u16 frameCount=layers[id].reserved0;
    if(paused==0 && frameCount!=0) {
        u16 frame=((u16*)items[parentItem].extra)[id];
        u16 elapsed=timeGetLastFrameTime();
        GSgfxVideoGetVsyncRate();
        u16 next=frame+elapsed;
        if(next>=frameCount) {
            next=0;
            FlashHeader* hdr=header;
            FlashLayer* layer=&layers[id];
            s32 offset=0;
            for(u32 i=0;i<hdr->itemCount;i++,offset+=0x40) {
                ((FlashItem*)((u8*)layer->items+offset))->depth=0.0f;
                ((FlashItem*)((u8*)layer->items+offset))->field30=0;
                ((FlashItem*)((u8*)layer->items+offset))->field34=0;
                flcalcUnitCxform(&((FlashItem*)((u8*)layer->items+offset))->cxform);
            }
        }
        ((u16*)items[parentItem].extra)[id]=next;
    }
}

struct FlashTextStyle {
    u8 flags, reserved1;
    u16 font;
    s16 x, y;
    u16 height, reservedA;
    u32 color;
};
struct FlashGlyph { s32 index, scale; };
struct FlashPoint { f32 x, y; };
extern "C" {
void flcalcMatrixCopy(FLASHMATRIXF*, FLASHMATRIXF*);
void flcalcMatrixScale(FLASHMATRIXF*, FLASHMATRIXF*, FlashPoint*);
void flcalcMatrixTranslate(FLASHMATRIXF*, FLASHMATRIXF*, FlashPoint*);
void flcalcUnitMatrix(FLASHMATRIXF*);
void flcalcCreateCxform(FLASHCXFORM*, u32);
}
void FlashMenu::DrawText(_DEFINETEXT* text, FLASHMATRIXF* parent, FLASHMATRIXF* matrix, FLASHCXFORM* color, u8 flags) {
    u16 fontId = 0;
    s16 x = 0, y = 0;
    FLASHMATRIXF local;
    FLASHMATRIXF combined;
    FLASHCXFORM glyphColor;
    FlashPoint scale, translation;
    u16 height = 0;
    s32 currentColor = 0;
    s32 offset = 0;
    TextRecord* record = (TextRecord*)text->records;
    flcalcMatrixCopy(&local, matrix);
    for (;;) {
        switch (record->type) {
        case 1: {
            FlashTextStyle* style = (FlashTextStyle*)record->data;
            u8 styleFlags = style->flags;
            s32 changeFont = styleFlags & 8;
            if (changeFont) fontId = style->font;
            if (styleFlags & 4) currentColor = style->color;
            if (styleFlags & 1) { x = style->x; x = style->x / 20; }
            if (styleFlags & 2) { y = style->y; y = style->y / 20; }
            if (changeFont) height = style->height / 20;
            break;
        }
        case 2: {
            TextGlyphs* glyphs = (TextGlyphs*)record->data;
            _DEFINEFONT2* font = (_DEFINEFONT2*)memory[fontId].data;
            if (font) {
                FlashGlyph* glyph = (FlashGlyph*)glyphs->data;
                for (s32 i = 0; i < glyphs->count; ++i, ++glyph) {
                    flcalcCreateCxform(&glyphColor, currentColor);
                    flcalcMulCxform(&glyphColor, &glyphColor, color);
                    s32 glyphScale = glyph->scale;
                    flcalcMatrixCopy(&local, matrix);
                    if (parent) flcalcMatrixCopy(&combined, parent);
                    else flcalcUnitMatrix(&combined);
                    scale.y = scale.x = (f32)glyphScale * 0.0009765625f;
                    flcalcMatrixScale(&local, &local, &scale);
                    translation.x = x; translation.y = y;
                    flcalcMatrixTranslate(&local, &local, &translation);
                    s32 previous = offset;
                    offset += height;
                    local.m[4] += previous;
                    _DEFINESHAPE* shape = ((_DEFINESHAPE**)font->shapes)[glyph->index];
                    if (*(u32*)((u8*)shape->records + 8)) {
                        vectorGraph(field34, &shape->fillCount, &shape->lineCount, shape->records, &combined, &local, &glyphColor, flags);
                    }
                }
            }
            break;
        }
        }
        TextRecord* next = (TextRecord*)record->next;
        if (!next) return;
        record = next;
    }
}

extern "C" void vectroGraphSetBlendMode(s32,s32);
void FlashMenu::DrawSub(GSgfxLayerID, tagWINDOW_WORK*, tagSPRITE_WORK* sprite) {
    FLASHMATRIXF local, textMatrix;
    _DEFINESHAPE drawShape;
    FlashHeader* hdr = header;
    vectroGraphSetBlendMode(4,5);
    s32 offset = 0;
    for (u16 i = 0; i < hdr->itemCount; ++i, offset += 0x40) {
        FlashItem* item = (FlashItem*)((u8*)items + offset);
        if (item->field34) {
            field10 = i;
            FlashDataPointer* entry = &memory[(u16)item->frame];
            flcalcConvFlashMatrix(&local, &item->matrix);
            item->flag |= *(u8*)item->field34;
            local.m[4] += *(s16*)((u8*)sprite + 0x50);
            local.m[5] += *(s16*)((u8*)sprite + 0x52);
            if (item->flag & 0x40) vectroGraphSetBlendMode(2,5);
            if(entry->type&1) {
                u8 drawFlags=item->flag;
                f32 ratio=item->depth;
                _DEFINEMORPHSHAPE* morph=(_DEFINEMORPHSHAPE*)entry->data;
                memset(&drawShape,0,0x1C);
                drawShape.fillCount=morph->reserved18;
                drawShape.fills=(FlashFillStyle*)morph->start;
                drawShape.lineCount=morph->reserved20;
                drawShape.lines=morph->end;
                s32 inputOffset=0,outputOffset=0;
                for(s32 fill=0;fill<(s32)morph->fillCount;fill++,inputOffset+=0xD4,outputOffset+=0x80) {
                    FlashMorphFillStyle* source=(FlashMorphFillStyle*)((u8*)morph->fills+inputOffset);
                    FlashFillStyle* destination=(FlashFillStyle*)((u8*)drawShape.fills+outputOffset);
                    if(source->flags==0) destination->color=flcalcBlendColor(source->colorA,source->colorB,ratio);
                    else if(source->flags&16) {
                        u8* input=(u8*)source+0x3C;
                        u8* output=(u8*)destination+0x20;
                        for(s32 j=0;j<source->count;j++,input+=0xC,output+=8) {
                            output[4]=flcalcBlend(input[4],input[5],ratio);
                            *(u32*)(output+8)=flcalcBlendColor(*(u32*)(input+8),*(u32*)(input+12),ratio);
                        }
                        s32* matrix=destination->matrix;
                        matrix[0]=flcalcBlend(source->matrixA[0],source->matrixB[0],ratio);
                        matrix[1]=flcalcBlend(source->matrixA[1],source->matrixB[1],ratio);
                        matrix[2]=flcalcBlend(source->matrixA[2],source->matrixB[2],ratio);
                        matrix[3]=flcalcBlend(source->matrixA[3],source->matrixB[3],ratio);
                        matrix[4]=flcalcBlend(source->matrixA[4],source->matrixB[4],ratio);
                        matrix[5]=flcalcBlend(source->matrixA[5],source->matrixB[5],ratio);
                    }
                }
                BlendShapeRecord(morph->shapes[2]->records,morph->shapes[0]->records,morph->shapes[1]->records,ratio);
                vectorGraph(field34,&drawShape.fillCount,&drawShape.lineCount,morph->shapes[2]->records,0,&local,&item->cxform,drawFlags);
            }

            if (entry->type & 4) {
                _DEFINESPRITE* child = (_DEFINESPRITE*)entry->data;
                u32 frame = playFrame;
                if (header->frameCount > frame) {
                    pos = start; frameStart = frame; field14 = 0;
                    FlashTag* tag = (FlashTag*)((u8*)header + pos);
                    while (!ParseTag(tag->type, tag->size, false, false, false)) tag = (FlashTag*)((u8*)header + pos);
                }
                DrawSprite(child, &local, &item->cxform, i, item->flag);
            }
            if (entry->type & 2) {
                _DEFINESHAPE* shape = (_DEFINESHAPE*)entry->data;
                if (_drawflag) vectorGraph(field34, &shape->fillCount, &shape->lineCount, shape->records, 0, &local, &item->cxform, item->flag);
                field20++;
            }
            if (entry->type & 0x10) {
                FlashEditText* text = (FlashEditText*)entry->data;
                if (text->text) {
                    textMatrix = local;
                    s32 color = text->color;
                    u16 height = text->height / 20;
                    msgctrlSetValue(0x37, (u32)text->text);
                    switch (height) {
                    case 13: GSmsgPrint2(7, (s32)textMatrix.m[4], (s32)textMatrix.m[5], color, 0x4278); break;
                    case 22: GSmsgPrint2(7, (s32)textMatrix.m[4], (s32)textMatrix.m[5], color, 0x4275); break;
                    default: case 18: GSmsgPrint2(7, (s32)textMatrix.m[4], (s32)textMatrix.m[5], color, 0x4276); break;
                    }
                }
            }
            if (entry->type & 0x20) DrawText((_DEFINETEXT*)entry->data, 0, &local, &item->cxform, item->flag);
        }
    }
}
