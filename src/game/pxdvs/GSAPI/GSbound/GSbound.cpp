#pragma defer_codegen on
// Deferred code generation emits these definitions in reverse order.
#pragma force_active on
#include <game/pxdvs/GSAPI/GSbound/GSbound.hpp>
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <libc/string.h>
extern "C" {
void* GSmemAlloc(u32);
void GSmemFree(void*);
void GSmodelGetRootPosition(GSmodel*, Vec*);
void GSmodelGetRootRotation(GSmodel*, Vec*);
void GSmodelGetRootScale(GSmodel*, Vec*);
}

extern "C" {

#pragma dont_inline on

#pragma dont_inline reset

}

extern "C" {

s32 GSgfxProjectFastList(Vec*, Vec*, s32);

}

#include <game/pxdvs/GSAPI/GSgfxM/matrixStack.hpp>
struct GSgfxVF;
class GSgfxLayer {public:
    u8 reserved0[0x28];
    s32 field28;
    u8 reserved2C[0xD08];
    u8 fieldD34;
    u8 reservedD35[0x3];
    s32 fieldD38;
    u8 reservedD3C[0x50];
    s32 fieldD8C;
    s32 fieldD90;
    u8 reservedD94[0x8B0];
    s32 field1644;
    s32 field1648;
    s32 field164C;
    s32 field1650;
    u8 reserved1654[0x2];
    u8 field1656;
    u8 field1657;
    u8 field1658;
    u8 reserved1659[0x3];
    u8 field165C;
    u8 reserved165D[0x3];
    s32 field1660;
    s32 field1664;
    s32 field1668;
    s32 field166C;
    u8 field1670;
    u8 field1671;
    u8 field1672;
    u8 reserved1673[0x35];
    s32 field16A8;
    s32 field16AC;
    u8 reserved16B0[0x8];
    s32 field16B8;
    u8 reserved16BC[0x50];
    s32 field170C;
    u8 reserved1710[0x50];
    s32 field1760;
    s32 field1764;
    u8 reserved1768[0x8];
    s32 field1770;
    u8 reserved1774[0x50];
    s32 field17C4;
    u8 reserved17C8[0x1C8];
    void* field1990;
    s32 field1994;
    s32 field1998;
    GSgfxVF* field199C;
    GSgfxMatrixStack* field19A0;
    void setRenderState(bool,u8,bool);void beginSurface(u16);void endSurface();
};
extern "C" {void GScameraLoadActiveCameraMatrix(s32);GSgfxVF* GSgfxVFBuildTemp(s32,s32,s32,s32,s32,s32,s32,s32,s32);}

static inline void boundEulerToQuat(Vec* vector, Quaternion* quaternion) {
    EulerToQuat((HSD_Vec3*)vector, (HSD_Quaternion*)quaternion);
}

static inline f32 absDot(Vec* first, Vec* second) {
    f32 result;
    if (PSVECDotProduct(first, second) > 0.0f) result = PSVECDotProduct(first, second);
    else result = -PSVECDotProduct(first, second);
    return result;
}

static inline void _boundGenPointList(Vec* points, Vec* mm)
{
    points[0].x = mm[0].x;
    points[0].y = mm[0].y;
    points[0].z = mm[0].z;
    points[1].x = mm[0].x;
    points[1].y = mm[0].y;
    points[1].z = mm[1].z;
    points[2].x = mm[0].x;
    points[2].y = mm[1].y;
    points[2].z = mm[0].z;
    points[3].x = mm[0].x;
    points[3].y = mm[1].y;
    points[3].z = mm[1].z;
    points[4].x = mm[1].x;
    points[4].y = mm[0].y;
    points[4].z = mm[0].z;
    points[5].x = mm[1].x;
    points[5].y = mm[0].y;
    points[5].z = mm[1].z;
    points[6].x = mm[1].x;
    points[6].y = mm[1].y;
    points[6].z = mm[0].z;
    points[7].x = mm[1].x;
    points[7].y = mm[1].y;
    points[7].z = mm[1].z;
}

static inline s32 _boundIsInScreenView(Vec* screen)
{
    s32 i;
    u8 orCode = 0;
    u8 andCode = 0x1f;
    for (i = 0; i < 8; i++) {
        u8 code;
        if (screen[i].x < 0.0f) {
            code = 1;
        } else if (screen[i].x > 640.0f) {
            code = 2;
        } else {
            code = 0;
        }
        if (screen[i].y < 0.0f) {
            code |= 4;
        } else if (screen[i].y > 480.0f) {
            code |= 8;
        }
        if (screen[i].z == -1.0f) {
            code |= 0x10;
        }
        orCode |= code;
        andCode &= code;
    }
    if (orCode == 0) {
        return 2;
    } else if (andCode != 0) {
        return 0;
    } else {
        return 1;
    }
}

extern "C" { void GSboundGetShadowSize(Vec* result, GSbound* bound, Vec* from, Vec* to, Vec* direction); }
extern "C" { void GSboundGetShadowVolume(GSbound* output,GSbound* bound,Vec* light,f32 plane); }
extern "C" { void GSboundGetLocalPosition(GSbound* bound, Vec* position); }
extern "C" { void GSboundGetWorldPosition(GSbound* bound, Vec* position); }
extern "C" { void GSboundGetSize(GSbound* bound, Vec* size, u8 scale, u8 rotate); }
extern "C" { void GSboundGetMinMax(GSbound* bound, Vec* minimum, Vec* maximum, u8 scale, u8 rotate, u8 translate, u8 skipRoot); }
extern "C" { void GSboundSetAnimFrame(GSbound* bound, f32 frame); }
extern "C" { void GSboundSetAnimIndex(GSbound* bound, s32 index); }
extern "C" { s32 GSboundHasAnimData(GSbound* bound); }
extern "C++" { void GSboundDraw(GSbound* bound,GSgfxLayer* layer); }
extern "C" { void GSboundAlwaysInView(GSbound* bound, u8 enabled); }
extern "C" { s32 GSboundIsInViewFast(GSbound* b); }
extern "C" { void GSboundAddPoint(GSbound* bound, f32 x, f32 y, f32 z); }
extern "C" { void GSboundReset(GSbound* bound); }
extern "C" { void GSboundSetDataPtr(GSbound* bound, s32 type, void* data); }
extern "C" { void GSboundFree(GSbound* bound); }
extern "C" { void GSboundCreate(GSbound* bound, GSboundData* data); }

extern "C" {
void GSboundCreate(GSbound* bound, GSboundData* data) {
    memset(bound, 0, sizeof(GSbound));
    if (!data) { bound->flags |= 1; return; }
    bound->bounds.animated.data = data;
    bound->bounds.animated.index = 0;
    bound->bounds.animated.frame = 0.0f;
    bound->bounds.animated.animations = (GSboundAnimation**)GSmemAlloc(bound->bounds.animated.data->animationCount * 4);
    s32 i;
    u8* cursor = (u8*)(bound->bounds.animated.data + 1);
    for (i = 0; i < bound->bounds.animated.data->animationCount; ++i) {
        bound->bounds.animated.animations[i] = (GSboundAnimation*)cursor;
        cursor += ((GSboundAnimation*)cursor)->frameCount * sizeof(GSboundFrame);
        cursor += 4;
    }
    bound->flags |= 8;
}
}

extern "C" {
void GSboundFree(GSbound* bound) {
    bound->transformType = 0;
    if (bound->flags & 8) { GSmemFree(bound->bounds.animated.animations); bound->bounds.animated.animations = 0; }
}
}

extern "C" {
void GSboundSetDataPtr(GSbound* bound, s32 type, void* data) {
    if (!data) { bound->transformType = 0; return; }
    bound->transformType = type;
    switch (type) {
    case 1: case 2: case 3: bound->transform.pointer = data; break;
    default: bound->transformType = 0; bound->transform.pointer = 0; break;
    }
}
}

extern "C" {
void GSboundReset(GSbound* bound) { if (!(bound->flags & 8)) bound->flags |= 1; }
}

extern "C" {
void GSboundAddPoint(GSbound* bound, f32 x, f32 y, f32 z) {
    u16 flags = bound->flags;
    if (!(flags & 8)) {
        if (flags & 1) {
            bound->bounds.box.minimum.x = x; bound->bounds.box.minimum.y = y; bound->bounds.box.minimum.z = z;
            bound->bounds.box.maximum.x = x; bound->bounds.box.maximum.y = y; bound->bounds.box.maximum.z = z;
            bound->flags &= ~1;
            return;
        }
        if (x < bound->bounds.box.minimum.x) bound->bounds.box.minimum.x = x;
        if (y < bound->bounds.box.minimum.y) bound->bounds.box.minimum.y = y;
        if (z < bound->bounds.box.minimum.z) bound->bounds.box.minimum.z = z;
        if (x > bound->bounds.box.maximum.x) bound->bounds.box.maximum.x = x;
        if (y > bound->bounds.box.maximum.y) bound->bounds.box.maximum.y = y;
        if (z > bound->bounds.box.maximum.z) bound->bounds.box.maximum.z = z;
    }
}
}

extern "C" {
s32 GSboundIsInViewFast(GSbound* b)
{
    Vec mm[2];
    Vec points[8];
    Vec screen[8];

    if (b->flags & 4) {
        return 2;
    }
    GSboundGetMinMax(b, &mm[0], &mm[1], true, true, true, false);
    _boundGenPointList(points, mm);
    if (GSgfxProjectFastList(points, screen, 8) != 2) {
        return 2;
    }
    return _boundIsInScreenView(screen);
}
}

extern "C" {
void GSboundAlwaysInView(GSbound* bound, u8 enabled) {
    if (enabled) bound->flags |= 4;
    else bound->flags &= ~4;
}
}

extern "C++" {
void GSboundDraw(GSbound* bound,GSgfxLayer* layer) {
    Mtx matrix,inverseScale,transform,modelRotation,transformRotation;
    Vec size,center,angles;Quaternion quaternion;Vec maximum,minimum;
    if(layer->field1994==1 && !(bound->flags&1)) {
        GSboundGetSize(bound,&size,1,0);
        if(!(PSVECSquareMag(&size)<0.00001f)) {
            GScameraLoadActiveCameraMatrix(layer->field28);
            layer->field1656 = 1;
            layer->field1657 = 1;
            layer->field1658 = 0;
            layer->field170C = layer->field170C | 4;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 4;
            layer->field1760 = layer->field1760 | 0x40;
            layer->field165C = 0;
            layer->field1660 = 3;
            layer->field170C = layer->field170C | 8;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 8;
            layer->field1760 = layer->field1760 | 0x40;
            layer->field1664 = 7;
            layer->field1670 = 0;
            layer->field1668 = 0;
            layer->field166C = 7;
            layer->field1671 = 0;
            layer->field1672 = 1;
            layer->field170C = layer->field170C | 0x10;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 0x10;
            layer->field1760 = layer->field1760 | 0x40;
            layer->fieldD8C = 0;
            layer->field16B8 = layer->field16B8 | 2;
            layer->field16A8 = layer->field16A8 | 2;
            layer->field1770 = layer->field1770 | 2;
            layer->field1760 = layer->field1760 | 2;
            if ((s32) layer->field1994 != 1) {
                layer->field1994 = 1;
                layer->field1990 = (u8*)layer+layer->field1994*0xbc+0x1818;
            }
            layer->field1644 = 1;
            layer->field1648 = 4;
            layer->field164C = 1;
            layer->field1650 = 5;
            layer->field170C = layer->field170C | 1;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 1;
            layer->field1760 = layer->field1760 | 0x40;
            layer->fieldD90 = 0;
            layer->field16B8 = layer->field16B8 | 4;
            layer->field16A8 = layer->field16A8 | 2;
            layer->field1770 = layer->field1770 | 4;
            layer->field1760 |= 2;
            layer->fieldD34 = 6;
            layer->fieldD38 = 0;
            layer->field16AC = layer->field16AC | 4;
            layer->field16A8 = layer->field16A8 | 1;
            layer->field1764 = layer->field1764 | 4;
            layer->field1760 = layer->field1760 | 1;
            layer->setRenderState(true,0,false);
            layer->field199C = GSgfxVFBuildTemp(1,4,0,0,1,5,0,0,0);

            PSMTXScale(matrix,size.x,size.y,size.z);
            switch(bound->transformType) {
            case 1:
                GSmodelGetRotation(bound->transform.model,(GSvec*)&angles);
                boundEulerToQuat(&angles,&quaternion);
                PSMTXQuat(modelRotation,&quaternion);PSMTXConcat(modelRotation,matrix,matrix);break;
            case 2: {
                PSMTXCopy(bound->transform.matrix,transform);
                transform[0][3]=0.0f;transform[1][3]=0.0f;transform[2][3]=0.0f;
                MtxPtr source=bound->transform.matrix;
                f32 x=PSVECMag((Vec*)source[0]);f32 y=PSVECMag((Vec*)source[1]);
                PSMTXScale(inverseScale,x,y,PSVECMag((Vec*)source[2]));
                PSMTXInverse(inverseScale,inverseScale);PSMTXConcat(inverseScale,transform,transform);PSMTXConcat(transform,matrix,matrix);break;
            }
            case 3:
                PSMTXQuat(transformRotation,&bound->transform.transform->rotation);PSMTXConcat(transformRotation,matrix,matrix);break;
            }
            GSboundGetMinMax(bound,&minimum,&maximum,1,1,1,0);
            PSVECAdd(&minimum,&maximum,&center);PSVECScale(&center,&center,0.5f);
            PSMTXTransApply(matrix,matrix,center.x,center.y,center.z);
            layer->field19A0->pushMult((GSmtx*)matrix);
            layer->field1998 = 0x80;
            layer->beginSurface(0x18);
            for(f32 coordinate=-0.5f;coordinate<1.0f;coordinate+=1.0f) {
                *(f32 *)0xCC008000 = coordinate;
                *(f32 *)0xCC008000 = -0.5f;
                *(f32 *)0xCC008000 = -0.5f;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = coordinate;
                *(f32 *)0xCC008000 = 0.5f;
                *(f32 *)0xCC008000 = -0.5f;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = coordinate;
                *(f32 *)0xCC008000 = 0.5f;
                *(f32 *)0xCC008000 = 0.5f;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = coordinate;
                *(f32 *)0xCC008000 = -0.5f;
                *(f32 *)0xCC008000 = 0.5f;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = -0.5f;
                *(f32 *)0xCC008000 = coordinate;
                *(f32 *)0xCC008000 = -0.5f;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = 0.5f;
                *(f32 *)0xCC008000 = coordinate;
                *(f32 *)0xCC008000 = -0.5f;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = 0.5f;
                *(f32 *)0xCC008000 = coordinate;
                *(f32 *)0xCC008000 = 0.5f;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = -0.5f;
                *(f32 *)0xCC008000 = coordinate;
                *(f32 *)0xCC008000 = 0.5f;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = -0.5f;
                *(f32 *)0xCC008000 = -0.5f;
                *(f32 *)0xCC008000 = coordinate;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = 0.5f;
                *(f32 *)0xCC008000 = -0.5f;
                *(f32 *)0xCC008000 = coordinate;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = 0.5f;
                *(f32 *)0xCC008000 = 0.5f;
                *(f32 *)0xCC008000 = coordinate;
                *(u32 *)0xCC008000 = 0x80808040;
                *(f32 *)0xCC008000 = -0.5f;
                *(f32 *)0xCC008000 = 0.5f;
                *(f32 *)0xCC008000 = coordinate;
                *(u32 *)0xCC008000 = 0x80808040;
            }
            layer->endSurface();
            layer->field165C = 1;
            layer->field1660 = 3;
            layer->field170C = layer->field170C | 8;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 8;
            layer->field1760 = layer->field1760 | 0x40;
            if ((s32) layer->field1994 != 1) {
                layer->field1994 = 1;
                layer->field1990 = (u8*)layer+layer->field1994*0xbc+0x1818;
            }
            layer->field1644 = 1;
            layer->field1648 = 4;
            layer->field164C = 5;
            layer->field1650 = 5;
            layer->field170C = layer->field170C | 1;
            layer->field16A8 = layer->field16A8 | 0x40;
            layer->field17C4 = layer->field17C4 | 1;
            layer->field1760 |= 0x40;
            layer->field1998 = 0xB0;
            layer->beginSurface(5);
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            layer->endSurface();
            layer->beginSurface(5);
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            layer->endSurface();
            layer->field1998 = 0xA8;
            layer->beginSurface(8);
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            *(f32 *)0xCC008000 = 0.5f;
            *(f32 *)0xCC008000 = -0.5f;
            *(f32 *)0xCC008000 = 0.5f;
            *(u32 *)0xCC008000 = 0x80808080;
            layer->endSurface();
            layer->field19A0->pop();
        }
    }
}
}

extern "C" {
s32 GSboundHasAnimData(GSbound* bound) { return (bound->flags >> 3) & 1; }
}

extern "C" {
void GSboundSetAnimIndex(GSbound* bound, s32 index) {
    if (bound->flags & 8) { bound->bounds.animated.index = index; bound->bounds.animated.frame = 0.0f; }
}
}

extern "C" {
void GSboundSetAnimFrame(GSbound* bound, f32 frame) {
    if (bound->flags & 8) {
        u16 count = bound->bounds.animated.animations[bound->bounds.animated.index]->frameCount;
        if (frame >= count) frame = count - 1;
        bound->bounds.animated.frame = frame;
    }
}
}

extern "C" {
void GSboundGetMinMax(GSbound* bound, Vec* minimum, Vec* maximum, u8 scale, u8 rotate, u8 translate, u8 skipRoot) {
    Mtx matrix, rootRotation, modelRotation, firstRotation, secondRotation;
    Vec vector;
    Quaternion quaternion, matrixQuaternion;
    if (bound->flags & 8) {
        GSboundAnimation* animation = bound->bounds.animated.animations[bound->bounds.animated.index];
        animation = (GSboundAnimation*)((u8*)animation + (s32)bound->bounds.animated.frame * sizeof(GSboundFrame));
        *minimum = animation->frames[0].minimum;
        *maximum = animation->frames[0].maximum;
    } else {
        *minimum = bound->bounds.box.minimum;
        *maximum = bound->bounds.box.maximum;
    }
    switch (bound->transformType) {
    case 1:
        if (skipRoot || !GSmodelIsRootNullAdded(bound->transform.model)) PSMTXIdentity(matrix);
        else {
            GSmodelGetRootScale(bound->transform.model, &vector);
            PSMTXScale(matrix, vector.x, vector.y, vector.z);
            GSmodelGetRootRotation(bound->transform.model, &vector);
            boundEulerToQuat(&vector, &quaternion);
            PSMTXQuat(rootRotation, &quaternion);
            PSMTXConcat(rootRotation, matrix, matrix);
            GSmodelGetRootPosition(bound->transform.model, &vector);
            PSMTXTransApply(matrix, matrix, vector.x, vector.y, vector.z);
        }
        if (scale) {
            GSmodelGetScale(bound->transform.model, (GSvec*)&vector);
            PSMTXScaleApply(matrix, matrix, vector.x, vector.y, vector.z);
        }
        if (rotate) {
            GSmodelGetRotation(bound->transform.model, (GSvec*)&vector);
            boundEulerToQuat(&vector, &quaternion);
            PSMTXQuat(modelRotation, &quaternion);
            PSMTXConcat(modelRotation, matrix, matrix);
        }
        if (translate) {
            GSmodelGetPosition(bound->transform.model, (GSvec*)&vector);
            PSMTXTransApply(matrix, matrix, vector.x, vector.y, vector.z);
        }
        PSMTXMultVec(matrix, minimum, minimum);
        PSMTXMultVec(matrix, maximum, maximum);
        return;
    case 2:
        if (scale && rotate && translate) {
            PSMTXMultVec(bound->transform.matrix, minimum, minimum);
            PSMTXMultVec(bound->transform.matrix, maximum, maximum);
            return;
        }
        if (scale && rotate) {
            PSMTXMultVecSR(bound->transform.matrix, minimum, minimum);
            PSMTXMultVecSR(bound->transform.matrix, maximum, maximum);
            return;
        }
        if (scale) {
            MtxPtr source = bound->transform.matrix;
            f32 x = PSVECMag((Vec*)source[0]);
            f32 y = PSVECMag((Vec*)source[1]);
            PSMTXScale(matrix, x, y, PSVECMag((Vec*)source[2]));
        } else if (rotate) {
            C_QUATMtx(&matrixQuaternion, bound->transform.matrix);
            PSMTXQuat(matrix, &matrixQuaternion);
        }
        if (translate) {
            MtxPtr source = bound->transform.matrix;
            PSMTXTransApply(matrix, matrix, source[0][3], source[1][3], source[2][3]);
        }
        PSMTXMultVec(matrix, minimum, minimum);
        PSMTXMultVec(matrix, maximum, maximum);
        return;
    case 3:
        if (scale) {
            GSboundTransform* transform = bound->transform.transform;
            minimum->x *= transform->scale.x;
            minimum->y *= transform->scale.y;
            minimum->z *= transform->scale.z;
            transform = bound->transform.transform;
            maximum->x *= transform->scale.x;
            maximum->y *= transform->scale.y;
            maximum->z *= transform->scale.z;
        }
        if (rotate) {
            PSMTXQuat(firstRotation, &bound->transform.transform->rotation);
            PSMTXMultVecSR(firstRotation, minimum, minimum);
            PSMTXQuat(secondRotation, &bound->transform.transform->rotation);
            PSMTXMultVecSR(secondRotation, maximum, maximum);
        }
        if (translate) {
            PSVECAdd(minimum, &bound->transform.transform->position, minimum);
            PSVECAdd(maximum, &bound->transform.transform->position, maximum);
        }
        return;
    }
}
}

extern "C" {
void GSboundGetSize(GSbound* bound, Vec* size, u8 scale, u8 rotate) {
    Mtx matrix, inverseScale;
    Vec minimum, maximum, corner;
    Quaternion quaternion;
    Vec difference;
    Vec saved;
    GSboundGetMinMax(bound, &minimum, &maximum, scale, 0, 0, 0);
    PSVECSubtract(&maximum, &minimum, &difference);
    f32 dx = difference.x, dy = difference.y, dz = difference.z;
    size->x = dx; size->y = dy; size->z = dz;
    if (size->x < 0.0f) size->x = -size->x;
    if (size->y < 0.0f) size->y = -size->y;
    if (size->z < 0.0f) size->z = -size->z;
    if (rotate) {
        switch (bound->transformType) {
        case 1:
            GSmodelGetRotation(bound->transform.model, (GSvec*)&corner);
            boundEulerToQuat(&corner, &quaternion);
            PSMTXQuat(matrix, &quaternion);
            break;
        case 2: {
            PSMTXCopy(bound->transform.matrix, matrix);
            matrix[0][3] = 0.0f; matrix[1][3] = 0.0f; matrix[2][3] = 0.0f;
            MtxPtr source = bound->transform.matrix;
            Vec lengths;
            lengths.x = PSVECMag((Vec*)source[0]);
            lengths.y = PSVECMag((Vec*)source[1]);
            PSMTXScale(inverseScale, lengths.x, lengths.y, PSVECMag((Vec*)source[2]));
            PSMTXInverse(inverseScale, inverseScale);
            PSMTXConcat(inverseScale, matrix, matrix);
            break;
        }
        case 3: PSMTXQuat(matrix, &bound->transform.transform->rotation); break;
        default: return;
        }
        saved.x = size->x; saved.y = size->y; saved.z = size->z;
        PSMTXMultVec(matrix, size, size);
        f32* component = &corner.x;
        for (s32 i = 0; i < 3; ++i, ++component) {
            corner.x = saved.x; corner.y = saved.y; corner.z = saved.z;
            *component *= -1.0f;
            PSMTXMultVec(matrix, &corner, &corner);
            if (corner.x < 0.0f) corner.x = -corner.x;
            if (corner.y < 0.0f) corner.y = -corner.y;
            if (corner.z < 0.0f) corner.z = -corner.z;
            if (corner.x > size->x) size->x = corner.x;
            if (corner.y > size->y) size->y = corner.y;
            if (corner.z > size->z) size->z = corner.z;
        }
    }
}
}

extern "C" {
void GSboundGetWorldPosition(GSbound* bound, Vec* position) {
    Vec minimum, maximum;
    GSboundGetMinMax(bound, &minimum, &maximum, 1, 1, 1, 0);
    PSVECAdd(&minimum, &maximum, position);
    PSVECScale(position, position, 0.5f);
}
}

extern "C" {
void GSboundGetLocalPosition(GSbound* bound, Vec* position) {
    Vec minimum, maximum;
    GSboundGetMinMax(bound, &minimum, &maximum, 0, 0, 0, 0);
    PSVECAdd(&minimum, &maximum, position);
    PSVECScale(position, position, 0.5f);
}
}

extern "C" {
void GSboundGetShadowVolume(GSbound* output,GSbound* bound,Vec* light,f32 plane) {
    Vec corners[8];
    Mtx matrix,modelRotation,transformRotation;
    Vec limits[2],temp,center;
    Quaternion quaternion;
    Vec sumCopy,transformCopy,scaleCopy,halfCenter,transformed,difference,projection,sum,scaled;
    memset(output,0,sizeof(GSbound));output->flags|=1;
    GSboundGetMinMax(bound,&limits[0],&limits[1],0,0,0,0);
    corners[0].x=limits[0].x;corners[0].y=limits[0].y;corners[0].z=limits[0].z;
    corners[1].x=limits[0].x;corners[1].y=limits[0].y;corners[1].z=limits[1].z;
    corners[2].x=limits[0].x;corners[2].y=limits[1].y;corners[2].z=limits[0].z;
    corners[3].x=limits[0].x;corners[3].y=limits[1].y;corners[3].z=limits[1].z;
    corners[4].x=limits[1].x;corners[4].y=limits[0].y;corners[4].z=limits[0].z;
    corners[5].x=limits[1].x;corners[5].y=limits[0].y;corners[5].z=limits[1].z;
    corners[6].x=limits[1].x;corners[6].y=limits[1].y;corners[6].z=limits[0].z;
    corners[7].x=limits[1].x;corners[7].y=limits[1].y;corners[7].z=limits[1].z;
    PSVECAdd(&limits[0],&limits[1],&sum);sumCopy=sum;PSVECScale(&sumCopy,&halfCenter,0.5f);center=halfCenter;
    switch(bound->transformType) {
    case 1:
        GSmodelGetScale(bound->transform.model,(GSvec*)&temp);PSMTXScale(matrix,temp.x,temp.y,temp.z);
        GSmodelGetRotation(bound->transform.model,(GSvec*)&temp);boundEulerToQuat(&temp,&quaternion);PSMTXQuat(modelRotation,&quaternion);PSMTXConcat(modelRotation,matrix,matrix);
        GSmodelGetPosition(bound->transform.model,(GSvec*)&temp);PSMTXTransApply(matrix,matrix,temp.x,temp.y,temp.z);break;
    case 2:PSMTXCopy(bound->transform.matrix,matrix);break;
    case 3: {
        GSboundTransform* transform=bound->transform.transform;
        PSMTXScale(matrix,transform->scale.x,transform->scale.y,transform->scale.z);
        PSMTXQuat(transformRotation,&bound->transform.transform->rotation);PSMTXConcat(transformRotation,matrix,matrix);
        transform=bound->transform.transform;PSMTXTransApply(matrix,matrix,transform->position.x,transform->position.y,transform->position.z);break;
    }
    default:PSMTXIdentity(matrix);break;
    }
    f32 distance=light->y-plane;
    if(!(distance<0.00001f) || !(distance>-0.00001f)) {
        Vec* corner=corners;
        for(s32 i=0;i<8;i++,corner++) {
            PSVECSubtract(corner,&center,corner);PSMTXMultVec(matrix,corner,corner);
            PSMTXMultVecSR(matrix,&center,&transformed);transformCopy=transformed;PSVECAdd(corner,&transformCopy,corner);
            PSVECSubtract(corner,light,&difference);temp=difference;
            f32 height = temp.y;
            f32 denominator=height-plane;
            if(!(height<0.00001f) || !(height>-0.00001f)) {
                PSVECScale(&temp,&scaled,distance/denominator);scaleCopy=scaled;
                PSVECSubtract(light,&scaleCopy,&projection);*corner=projection;
                GSboundAddPoint(output,corner->x,corner->y,corner->z);
            }
        }
    }
}
}

extern "C" {
void GSboundGetShadowSize(Vec* result, GSbound* bound, Vec* from, Vec* to, Vec* direction) {
    Vec minimum, maximum, right, up, extent;
    Quaternion quaternion;
    Vec normal, toFrom, firstCross, secondCross, sizeDifference;
    Vec corners[4];
    Mtx rotation;
    Mtx scaleMatrix;
    PSVECNormalize(direction, &normal);
    right = normal;
    PSVECSubtract(to, from, &toFrom);
    extent = toFrom;
    PSVECNormalize(&extent, &extent);
    PSVECCrossProduct(&right, &extent, &firstCross);
    up = firstCross;
    PSVECNormalize(&up, &up);
    PSVECCrossProduct(&extent, &up, &secondCross);
    right = secondCross;
    GSboundGetMinMax(bound, &minimum, &maximum, 1, 0, 0, 0);
    switch (bound->transformType) {
    case 1:
        GSmodelGetRotation(bound->transform.model, (GSvec*)&extent);
        boundEulerToQuat(&extent, &quaternion);
        PSMTXQuat(rotation, &quaternion);
        break;
    case 2: {
        PSMTXCopy(bound->transform.matrix, rotation);
        rotation[0][3] = 0.0f; rotation[1][3] = 0.0f; rotation[2][3] = 0.0f;
        MtxPtr source = bound->transform.matrix;
        f32 x = PSVECMag((Vec*)source[0]);
        f32 y = PSVECMag((Vec*)source[1]);
        PSMTXScale(scaleMatrix, x, y, PSVECMag((Vec*)source[2]));
        PSMTXInverse(scaleMatrix, scaleMatrix);
        PSMTXConcat(scaleMatrix, rotation, rotation);
        break;
    }
    case 3: PSMTXQuat(rotation, &bound->transform.transform->rotation); break;
    default: PSMTXIdentity(rotation); break;
    }
    PSVECSubtract(&maximum, &minimum, &sizeDifference);
    extent = sizeDifference;
    if (extent.x < 0.0f) extent.x = -extent.x;
    if (extent.y < 0.0f) extent.y = -extent.y;
    if (extent.z < 0.0f) extent.z = -extent.z;
    f32 a;
    f32 maxA = 0.0f, maxB = 0.0f;
    Vec* corner = corners;
    corners[0] = extent;
    corners[1] = extent; corners[1].y *= -1.0f;
    corners[2] = extent; corners[2].x *= -1.0f;
    corners[3] = extent; corners[3].x *= -1.0f; corners[3].y *= -1.0f;
    for (s32 i = 0; i < 4; ++i, ++corner) {
        f32 b;
        PSMTXMultVec(rotation, corner, corner);
        if (PSVECDotProduct(corner, &up) > 0.0f) { a = PSVECDotProduct(corner, &up); }
        else { a = PSVECDotProduct(corner, &up); a = -a; }
        b = absDot(corner, &right);
        if (a > maxA) maxA = a;
        if (b > maxB) maxB = b;
    }
    result->x = maxA;
    result->y = 0.0f;
    result->z = maxB;
}
}
