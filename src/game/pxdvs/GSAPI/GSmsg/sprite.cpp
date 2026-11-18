#include <game/pxdvs/GSAPI/GSmsg/spritePrivate.hpp>
#include <libc/string.h>
struct _struct__spriteWork_0x10 {f32 unk0,unk4,unk8,unkC;};
static _struct__spriteWork_0x10 _spriteWork[3]={{0,0,1,1},{0,0,1,1},{0,0,1,1}};
extern "C" {
double tan(double);
void spriteClearScissor(s32 layer) {
    GSgfxLayer *temp_r3;

    temp_r3 = GSgfxLayerFindByID(layer);
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        temp_r3->unkD70 = 0;
        temp_r3->unkD72 = 0;
        GSgfxVideoGetEFBSize(&temp_r3->unkD74, &temp_r3->unkD76);
        temp_r3->unk16B8 = (s32) (temp_r3->unk16B8 | 1);
        temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 2);
        temp_r3->unk1770 = (s32) (temp_r3->unk1770 | 1);
        temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 2);
    }
}

#pragma opt_lifetimes off
#pragma opt_propagation off
void spriteSetScissor(s32 layerId, s32 x, s32 y, s32 width, s32 height) {
    f32 scaleX;
    f32 scaleY;
    s16 transformIndex;
    struct _struct__spriteWork_0x10 *transform;
    GSgfxLayer *layer;

    s32 menuLayer = floorGetMenuLayerID();
    s32 targetLayerId = layerId;
    if (layerId == menuLayer) {
        transformIndex = 0;
    } else if (layerId == 7) {
        transformIndex = 1;
    } else {
        transformIndex = 2;
    }
    transform = &_spriteWork[transformIndex];
    layer = GSgfxLayerFindByID(targetLayerId);
    _TargetLayer = layer;
    if (layer != NULL) {
        scaleX = transform->unk8;
        scaleY = transform->unkC;
        x = (s32)(transform->unk0 + (f32)x);
        y = (s32)(transform->unk4 + (f32)y);
        x = (s32)((f32)x * scaleX);
        y = (s32)((f32)y * scaleY);
        width = (s32)((f32)width * scaleX);
        height = (s32)((f32)height * scaleY);
        if (x >= 0x280) {
            x = 0x280;
        }
        if (y >= 0x1E0) {
            y = 0x1E0;
        }
        if (width >= 0x280) {
            width = 0x280;
        }
        if (height >= 0x1E0) {
            height = 0x1E0;
        }
        if (x < 0) {
            x = 0;
        }
        if (y < 0) {
            y = 0;
        }
        if (width < 0) {
            width = 0;
        }
        if (height < 0) {
            height = 0;
        }
        layer->unkD70 = (u16) x;
        layer->unkD72 = (u16) y;
        layer->unkD74 = (u16) width;
        layer->unkD76 = (u16) height;
        layer->unk16B8 = (s32) (layer->unk16B8 | 1);
        layer->unk16A8 = (s32) (layer->unk16A8 | 2);
        layer->unk1770 = (s32) (layer->unk1770 | 1);
        layer->unk1760 = (s32) (layer->unk1760 | 2);
    }
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

void spriteClearEnv(s32 layer) {
    GSgfxLayer *temp_r3;

    temp_r3 = GSgfxLayerFindByID(layer);
    _TargetLayer = temp_r3;
    if (temp_r3 != NULL) {
        if ((s32) temp_r3->unk1994 != 1) {
            temp_r3->unk1994 = 1;
            temp_r3->unk1990 = temp_r3->shaders[temp_r3->unk1994];
        }
        temp_r3->unk1644 = 1;
        temp_r3->unk1648 = 4;
        temp_r3->unk164C = 5;
        temp_r3->unk1650 = 5;
        temp_r3->unk170C = (s32) (temp_r3->unk170C | 1);
        temp_r3->unk16A8 = (s32) (temp_r3->unk16A8 | 0x40);
        temp_r3->unk17C4 = (s32) (temp_r3->unk17C4 | 1);
        temp_r3->unk1760 = (s32) (temp_r3->unk1760 | 0x40);
    }
}

#pragma opt_propagation off
void spriteSetEnv(s32 layerId) {
    Mtx view;
    Mtx44 projection;
    Vec eye, center, up;
    f32 halfWidth;
    f32 halfHeight;
    f32 viewWidth;
    f32 viewHeight;
    f32 viewAngle;
    s16 transformIndex;
    SpriteMatrixFrame *temp_r3_2;
    SpriteMatrixFrame *temp_r3_4;
    f32 (*temp_r3_3)[4];
    struct _struct__spriteWork_0x10 *transform;
    GSgfxLayer *temp_r31_2;
    SpriteMatrixStack *temp_r31_3;
    SpriteMatrixStack *temp_r31_4;
    GSgfxLayer *layer;

    s32 menuLayer = floorGetMenuLayerID();
    s32 targetLayer = layerId;
    if (layerId == menuLayer) {
        transformIndex = 0;
    } else if (layerId == 7) {
        transformIndex = 1;
    } else {
        transformIndex = 2;
    }
    transform = &_spriteWork[transformIndex];
    layer = GSgfxLayerFindByID(targetLayer);
    _TargetLayer = layer;
    if (layer != NULL) {
        f32 scaleX, baseWidth, scaleY, baseHeight;
        baseWidth = 640.0f;
        scaleX = transform->unk8;
        baseHeight = 480.0f;
        scaleY = transform->unkC;
        viewWidth = baseWidth / scaleX;
        viewHeight = baseHeight / scaleY;
        f32 half = 0.5f;
        halfWidth = viewWidth * half;
        halfHeight = viewHeight * half;
        viewAngle = 0.2617994f;
        f32 tangent, coordinate, offsetX, viewY, zero;
        tangent = (f32)tan(viewAngle);
        zero = 0.0f;
        viewY = transform->unk4;
        offsetX = transform->unk0;
        coordinate = halfHeight / tangent;
        center.z = zero;
        up.x = zero;
        viewY = halfHeight - viewY;
        eye.z = coordinate;
        coordinate = halfWidth - offsetX;
        up.y = -1.0f;
        eye.x = coordinate;
        eye.y = viewY;
        center.x = coordinate;
        center.y = viewY;
        up.z = zero;
        C_MTXLookAt(view, &eye, &up, &center);
        temp_r31_2 = _TargetLayer;
        GSmtx44Perspective(projection, 30.0f, -(viewWidth / viewHeight), 0.1f, 30000.0f);
        temp_r31_2->unkD54 = 0;
        temp_r31_2->unkD58 = projection[0][0];
        temp_r31_2->unkD5C = projection[0][2];
        temp_r31_2->unkD60 = projection[1][1];
        temp_r31_2->unkD64 = projection[1][2];
        temp_r31_2->unkD68 = projection[2][2];
        temp_r31_2->unkD6C = projection[2][3];
        temp_r31_2->unk1684 = 0.1f;
        temp_r31_2->unk1688 = 30000.0f;
        if ((u8) temp_r31_2->unk16A7 != 0) {
            if ((u8) temp_r31_2->unk16A6 != 0) {
                temp_r31_2->unk170C = (s32) (temp_r31_2->unk170C | 0x100);
                temp_r31_2->unk17C4 = (s32) (temp_r31_2->unk17C4 | 0x100);
            }
            temp_r31_2->unk170C = (s32) (temp_r31_2->unk170C | 0x40);
            temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 0x40);
            temp_r31_2->unk17C4 = (s32) (temp_r31_2->unk17C4 | 0x40);
            temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 0x40);
        }
        temp_r31_2->unk16AC = (s32) (temp_r31_2->unk16AC | 0x20);
        temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 1);
        temp_r31_2->unk1764 = (s32) (temp_r31_2->unk1764 | 0x20);
        temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 1);
        temp_r31_3 = _TargetLayer->unk19A0;
        memcpy(temp_r31_3->frame->matrix, mtxIdent, 0x30);
        temp_r3_2 = temp_r31_3->frame;
        temp_r3_2->flags |= 1;
        temp_r31_4 = _TargetLayer->unk19A0;
        temp_r3_3 = temp_r31_4->frame->matrix;
        PSMTXConcat(temp_r3_3, view, temp_r3_3);
        temp_r3_4 = temp_r31_4->frame;
        temp_r3_4->flags |= 1;
        temp_r31_2=_TargetLayer;
        if ((s32) temp_r31_2->unk1994 != 1) {
            temp_r31_2->unk1994 = 1;
            temp_r31_2->unk1990 = temp_r31_2->shaders[temp_r31_2->unk1994];
        }
        temp_r31_2->unk1644 = 1;
        temp_r31_2->unk1648 = 4;
        temp_r31_2->unk164C = 5;
        temp_r31_2->unk1650 = 5;
        temp_r31_2->unk170C = (s32) (temp_r31_2->unk170C | 1);
        temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 0x40);
        temp_r31_2->unk17C4 = (s32) (temp_r31_2->unk17C4 | 1);
        temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 0x40);
        temp_r31_2=_TargetLayer;
        temp_r31_2->unk1656 = 1;
        temp_r31_2->unk1657 = 0;
        temp_r31_2->unk1658 = 1;
        temp_r31_2->unk170C = (s32) (temp_r31_2->unk170C | 4);
        temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 0x40);
        temp_r31_2->unk17C4 = (s32) (temp_r31_2->unk17C4 | 4);
        temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 0x40);
        temp_r31_2=_TargetLayer;
        temp_r31_2->unk1664 = 7;
        temp_r31_2->unk1670 = 0;
        temp_r31_2->unk1668 = 0;
        temp_r31_2->unk166C = 7;
        temp_r31_2->unk1671 = 0;
        temp_r31_2->unk1672 = 1;
        temp_r31_2->unk170C = (s32) (temp_r31_2->unk170C | 0x10);
        temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 0x40);
        temp_r31_2->unk17C4 = (s32) (temp_r31_2->unk17C4 | 0x10);
        temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 0x40);
        temp_r31_2=_TargetLayer;
        temp_r31_2->unk165C = 0;
        temp_r31_2->unk1660 = 3;
        temp_r31_2->unk170C = (s32) (temp_r31_2->unk170C | 8);
        temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 0x40);
        temp_r31_2->unk17C4 = (s32) (temp_r31_2->unk17C4 | 8);
        temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 0x40);
        temp_r31_2=_TargetLayer;
        temp_r31_2->unkD8C = 0;
        temp_r31_2->unk16B8 = (s32) (temp_r31_2->unk16B8 | 2);
        temp_r31_2->unk16A8 = (s32) (temp_r31_2->unk16A8 | 2);
        temp_r31_2->unk1770 = (s32) (temp_r31_2->unk1770 | 2);
        temp_r31_2->unk1760 = (s32) (temp_r31_2->unk1760 | 2);
    }
}

#pragma opt_propagation reset

void spriteGetOffset(s32 arg0, s16 *arg1, s16 *arg2) {
    s16 var_r0;
    struct _struct__spriteWork_0x10 *temp_r3;

    if (arg0 == floorGetMenuLayerID()) {
        var_r0 = 0;
    } else if (arg0 == 7) {
        var_r0 = 1;
    } else {
        var_r0 = 2;
    }
    temp_r3 = &_spriteWork[var_r0];
    if (arg1 != NULL) {
        *arg1 = (s16) temp_r3->unk0;
    }
    if (arg2 != NULL) {
        *arg2 = (s16) temp_r3->unk4;
    }
}

void spriteSetOffset(s32 arg0, s16 arg1, s16 arg2) {
    s16 var_r5;
    struct _struct__spriteWork_0x10 *temp_r4;

    if (arg0 == floorGetMenuLayerID()) {
        var_r5 = 0;
    } else if (arg0 == 7) {
        var_r5 = 1;
    } else {
        var_r5 = 2;
    }
    temp_r4 = &_spriteWork[var_r5];
    temp_r4->unk0 = (f32) arg1;
    temp_r4->unk4 = (f32) arg2;
}

}
