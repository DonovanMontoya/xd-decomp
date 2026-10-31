#pragma auto_inline off
#pragma defer_codegen off
#include <game/pxdvs/GSAPI/GScolsys/GScolsys2DrawPrivate.hpp>
#include <libc/string.h>
static DrawList _colsysDL;
union CollisionDebugColor { u8 channels[4]; u32 packed; };

inline void writeCollisionDebugColor(u8 red, u8 green, u8 blue, u8 alpha)
{
    GXWGFifo.u8 = red;
    GXWGFifo.u8 = green;
    GXWGFifo.u8 = blue;
    GXWGFifo.u8 = alpha;
}

inline void writePackedCollisionDebugColor(u32* packed)
{
    u8* color = (u8*)packed;
    writeCollisionDebugColor(color[0], color[1], color[2], color[3]);
}

template <class Model, class Head> inline void drawDebugMesh(Head* head, GSmtx* mtx, const CollisionDebugColor& meshColor)
{

    u32 t;
    s32 k;
    Model* mdl;

    mdl = (Model*)head->polygons;
    GSgfxDLPrimitiveType(GX_TRIANGLES);
    for (t = 0; t < (u32)head->count; t++, mdl++) {
        GSgfxDLBeginSurface(3);
        for (k = 0; k < 3; k++) {
            Vec v;
            PSMTXMultVec((MtxPtr)mtx, (const Vec *)&mdl->vertices[k], (Vec *)&v);
            GXWGFifo.f32 = v.x;
            GXWGFifo.f32 = v.y;
            GXWGFifo.f32 = v.z;
            GXWGFifo.u8 = meshColor.channels[0];
            GXWGFifo.u8 = meshColor.channels[1];
            GXWGFifo.u8 = meshColor.channels[2];
            GXWGFifo.u8 = meshColor.channels[3];
        }
        GSgfxDLEndSurface();
    }
}

void drawHitMdl(CCD_HITMDL_HEAD* head, GSmtx* mtx, GSmtx* rotMtx)
{
    Vec tri[3];
    CollisionDebugColor color = {{255,255,255,255}};
    u32 t;
    DrawPolygon* mdl;
    s32 i;

    mdl = (DrawPolygon*)head->polygons;
    for (t = 0; t < (u32)head->count; t++, mdl++) {
        for (i = 0; i < 3; i++) {
            PSMTXMultVec((MtxPtr)mtx, (const Vec *)&mdl->vertices[i], (Vec *)&tri[i]);
        }
        GSgfxDLPrimitiveType(GX_LINES);
        for (i = 0; i < 3; i++) {
            s32 j = i + 1;

            if (j >= 3) {
                j = 0;
            }
            GSgfxDLBeginSurface(2);
            GXWGFifo.f32 = tri[i].x;
            GXWGFifo.f32 = tri[i].y;
            GXWGFifo.f32 = tri[i].z;
            writePackedCollisionDebugColor((u32*)&color);
            GXWGFifo.f32 = tri[j].x;
            GXWGFifo.f32 = tri[j].y;
            GXWGFifo.f32 = tri[j].z;
            writePackedCollisionDebugColor((u32*)&color);
            GSgfxDLEndSurface();
        }
    }
}

inline void drawThruMdl(CCD_HITMDL_HEAD* head, GSmtx* mtx) { CollisionDebugColor color = {{255,0,255,192}}; drawDebugMesh<DrawPolygon>(head, mtx, color); }

inline void drawSecondaryThruMdl(CCD_HITMDL_HEAD* head, GSmtx* mtx) { CollisionDebugColor color = {{255,255,0,192}}; drawDebugMesh<DrawPolygon>(head, mtx, color); }

inline void drawCheckMdl(DrawSunModel* head, GSmtx* mtx) { CollisionDebugColor color = {{0,255,255,192}}; drawDebugMesh<DrawSunPolygon>(head, mtx, color); }

#pragma dont_inline on
static void drawWalkMdl(CCD_WALKMDL_HEAD *model, GSmtx *matrix, GSmtx *rotation) {
 Vec transformed;
 GXColor color;
 GSgfxDLPrimitiveType(0x90);
 u32 p;
 DrawPolygon *polygon=model->polygons;
 for(p=0;p<model->count;++p,++polygon) {
  memset(&color,0,4); color.a=0xc0;
  u8 attribute=polygon->attribute;
  int blue=(attribute&15)+1;
  color.g=(s8)(127.0f*((f32)((attribute>>4)&15)/15.0f)+128.0f);
  if(blue>=16) blue=0;
  color.b=(s8)(255.0f*((f32)blue/15.0f));
  int red=(polygon->flags>>4)&15;
  if(red>0) color.r=red*4+0xc0;
  GSgfxDLBeginSurface(3);
  Vec *src;
  int i=0;
  src=polygon->vertices;
  for(;i<3;++i,++src) {
   PSMTXMultVec(matrix->m,src,&transformed);
   GXWGFifo.f32=transformed.x; GXWGFifo.f32=0.1f+transformed.y; GXWGFifo.f32=transformed.z;
   GXWGFifo.u8=color.r; GXWGFifo.u8=color.g; GXWGFifo.u8=color.b; GXWGFifo.u8=color.a;
  }
  GSgfxDLEndSurface();
 }
}

#pragma dont_inline reset
static DrawList* makeDisplayListFixedObj(void)
{
    u32 i;
    DrawObject* object;
    DrawFile* file;

    file = GScolsys2GetCCDFileHead();
    if (file == 0) {
        return 0;
    }
    memset(&_colsysDL, 0, 0x10);
    GSgfxDLBegin(&_colsysDL, GScolsys2.format, 0x400, 0x8000);
    object = file->objects;
    for (i = 0; i < (u32)file->count; i++, object++) {
        GSmtx obj;
        GSmtx rot;

        if (object->flags & 1) {
            continue;
        }
        GScolsys2GetObjMatrix(obj.m, i);
        GScolsys2GetObjRotMatrix(rot.m, i);
        if (object->walk != 0) {
            drawWalkMdl(object->walk, &obj, &rot);
        }
        if (object->hit != 0) {
            drawHitMdl(object->hit, &obj, &rot);
        }
        if (object->thru != 0) {
            drawThruMdl(object->thru, &obj);
        }
        if (object->check != 0) {
            drawSecondaryThruMdl(object->check, &obj);
        }
        if (object->npc != 0) {
            drawHitMdl(object->npc, &obj, &rot);
        }
        if (object->sun != 0) {
            drawCheckMdl(object->sun, &obj);
        }
    }
    GSgfxDLEnd();
    return &_colsysDL;
}

extern "C" void GScolsys2Draw(void)
{
    u32 i;
    DrawObject* object;
    DrawFile* file;
    DrawStateObject* draw;
    GSmtx obj;
    GSmtx rot;
    DrawList* list;

    file = GScolsys2GetCCDFileHead();
    if (file == 0) {
        return;
    }
    if ((GSinputButtonsPressed(1) & 0x40) != 0) {
        floorMapSetDisp(0);
    } else if ((GSinputButtonsPressed(1) & 0x20) != 0) {
        floorMapSetDisp(1);
    }
    GSgfxLayerSetActive(2);
    GScameraLoadActiveCameraMatrix(2);
    GSgfxCullMode(GX_CULL_FRONT);
    GSgfxSetupRenderAndSelect(GScolsys2.format);
    GSgfxBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
    GSgfxZCompare(GX_TRUE, GX_LEQUAL);
    GSgfxPixelMode(GX_TRUE, GX_TRUE, GX_TRUE);
    object = file->objects;
    draw = GScolsys2.floors[GScolsys2.currentFloor].objects;
    for (i = 0;
         i < (u32)file->count; i++, object++, draw++) {
        /* Draw only moving objects whose floor record is enabled. */
        if (draw->flags & 1) {
            continue;
        }
        if (!(object->flags & 1)) {
            continue;
        }
        GScolsys2GetObjMatrix(obj.m, i);
        GScolsys2GetObjRotMatrix(rot.m, i);
        if (object->walk != 0) {
            drawWalkMdl(object->walk, &obj, &rot);
        }
        if (object->hit != 0) {
            drawHitMdl(object->hit, &obj, &rot);
        }
        if (object->thru != 0) {
            drawThruMdl(object->thru, &obj);
        }
        if (object->check != 0) {
            drawSecondaryThruMdl(object->check, &obj);
        }
        if (object->npc != 0) {
            drawHitMdl(object->npc, &obj, &rot);
        }
        if (object->sun != 0) {
            drawCheckMdl(object->sun, &obj);
        }

    }
    /* The fixed-object display list is built once and cached; the human
     * collision overlay is drawn whether or not the list was ready. */
    if (GScolsys2.displayList == 0) {
        GScolsys2.displayList = makeDisplayListFixedObj();
    }
    list = GScolsys2.displayList;
    if (list != 0) {
        GSgfxDLDraw(list);
    }
    GScolsys2HumanDispColision();
}
