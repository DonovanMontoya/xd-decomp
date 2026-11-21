#ifndef PXDVS_APP_FLASHMENU_FLASH_SHAPE_HPP
#define PXDVS_APP_FLASHMENU_FLASH_SHAPE_HPP

#include <game/pxdvs/GSAPI/GSmath/GSvec2.hpp>
#include <game/pxdvs/app/flashmenu/flashColorTransform.hpp>

struct FLASHMATRIX {
    s32 m[6];
};
struct FLASHMATRIXF {
    f32 m[6];
};

extern "C" {
void flcalcBezier3(GSvec2* out, GSvec2 points[3], f32 t);
void flcalcConvFlashMatrix(FLASHMATRIXF* out, FLASHMATRIX* in);
void flcalcMulMatrixf(FLASHMATRIXF* out, FLASHMATRIXF* left, FLASHMATRIXF* right);
void flcalcUnitMatrix2(FLASHMATRIX* out);
void flcalcUnitMatrix(FLASHMATRIXF* out);
void flcalcMatrixCopy(FLASHMATRIXF* out, FLASHMATRIXF* in);
void flcalcMatrixTranslate(FLASHMATRIXF* out, FLASHMATRIXF* in, GSvec2* translation);
void flcalcMatrixScale(FLASHMATRIXF* out, FLASHMATRIXF* in, GSvec2* scale);
void flcalcMatrix(GSvec2* out, FLASHMATRIXF* matrix, GSvec2* point);
}

struct VecGradientStop {
    u8 ratio;
    u32 color;
};
struct VecGradient {
    u8 count;
    VecGradientStop stops[8];
};
struct VecFillStyle {
    u8 type;
    u32 color;
    FLASHMATRIX matrix;
    VecGradient gradient;
    u32 texture;
    FLASHMATRIX textureMatrix;
};
typedef char VecFillStyleSize[sizeof(VecFillStyle)==0x80?1:-1];
typedef char VecFillTextureOffset[(u32)&((VecFillStyle*)0)->texture==0x64?1:-1];
typedef char VecFillTextureMatrixOffset[(u32)&((VecFillStyle*)0)->textureMatrix==0x68?1:-1];

struct _FILLSTYLEARRAY {
    u32 count;
    VecFillStyle* styles;
};
struct _LINESTYLEARRAY {
    u32 count;
    void* styles;
};

struct VecStyleChange {
    u8 flags;
    s32 x, y;
    u8 left, right, line;
    _FILLSTYLEARRAY fills;
    _LINESTYLEARRAY lines;
};
typedef char VecStyleChangeFillsOffset[(u32)&((VecStyleChange*)0)->fills == 0x10 ? 1 : -1];
typedef char VecStyleChangeLinesOffset[(u32)&((VecStyleChange*)0)->lines == 0x18 ? 1 : -1];

struct SRecordLine {
    s32 pad;
    s32 x, y;
};
struct VecCurve {
    s32 controlX, controlY, endX, endY;
};
struct _SHAPERECORD {
    u8 type;
    void* data;
    _SHAPERECORD* next;
};

extern "C" void vectorGraph(u32 id, _FILLSTYLEARRAY* fills, _LINESTYLEARRAY* lines,
                            _SHAPERECORD* shapes, FLASHMATRIXF* matrix,
                            FLASHMATRIXF* textureMatrix, FLASHCXFORM* colors, u8 flags);

#endif
