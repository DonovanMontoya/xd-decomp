#pragma peephole off
#include <dolphin/types.h>
#pragma pool_strings off
#include <dolphin/gx/GXVert.h>

struct GSgfxVF;
struct GStexture {
    u8 unk0[7];
    u8 unk7;
};

struct BlendState {
    u8 pad[0xbc];
};

struct GSlayerCam {
    u32 pad;
    u32* data;
};

class GSgfxLayer {
public:
    void setRenderStateAndSelect(struct GSgfxVF* vf);
    void beginSurface(u16 count);
    void endSurface();

    u8 pad0[0x28];
    s32 id;
    u8 pad2c[0xd54 - 0x2c];
    s32 projType;
    f32 proj[6];
    u8 pad_d70[0xd8c - 0xd70];
    s32 d8c;
    u8 pad_d90[0x1644 - 0xd90];
    s32 blendOp;
    s32 blendSrc;
    s32 blendDst;
    s32 blendLogic;
    u8 pad_1654[2];
    u8 colorUpdate;
    u8 alphaUpdate;
    u8 zUpdate;
    u8 pad_1659[3];
    u8 zEnable;
    u8 pad_165d[3];
    s32 zFunc;
    s32 f1664;
    s32 f1668;
    s32 f166c;
    u8 f1670;
    u8 f1671;
    u8 f1672;
    u8 pad_1673[0x1684 - 0x1673];
    f32 nearZ;
    f32 farZ;
    u8 pad_168c[0x16a6 - 0x168c];
    u8 f16a6;
    u8 f16a7;
    u32 dirty16a8;
    u32 dirty16ac;
    u8 pad_16b0[8];
    u32 dirty16b8;
    u8 pad_16bc[0x170c - 0x16bc];
    u32 dirty170c;
    u8 pad_1710[0x173c - 0x1710];
    u32 dirty173c;
    void* tex1740;
    u8 pad_1744[0x1760 - 0x1744];
    u32 dirty1760;
    u32 dirty1764;
    u8 pad_1768[8];
    u32 dirty1770;
    u8 pad_1774[0x17c4 - 0x1774];
    u32 dirty17c4;
    u8 pad_17c8[0x17f4 - 0x17c8];
    u32 dirty17f4;
    void* tex17f8;
    u8 pad_17fc[0x1818 - 0x17fc];
    BlendState blendTable[2];
    BlendState* curBlend;
    s32 curBlendIdx;
    u32 primType;
    u8 pad_199c[0x19a0 - 0x199c];
    GSlayerCam* cam;
};

struct GSvec {
    f32 x, y, z;
    void set(f32 a, f32 b, f32 c) {
        x = a;
        y = b;
        z = c;
    }
};

struct GSvec2 {
    f32 x, y;
};

struct FadeFluidWork {
    u32 columns;
    u32 rows;
    f32 accel;
    f32 damping;
    f32 neighbor;
    f32 limit;
    f32 timeStep;
    f32 cellSize;
    f32 xScale;
    f32 yScale;
    GSvec* heightPage[2];
    GSvec* velocityX;
    GSvec* velocityY;
    GSvec2* texCoord;
    u8 pad_3C[4];
};

extern "C" {
GSgfxLayer* GSgfxLayerFindByID(int id);
GSgfxVF* GSgfxVFBuildTemp(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void spriteSetEnv(int layerID);
void GSlerpGetLinearInterpolationVector(GSvec* out, GSvec* a, GSvec* b, f32 t);
void GSmemFree(void* ptr);
void* GSmemAllocAlign(u32 size, u32 align);
s32 GSmemGetCurrentHeap();
s32 GSmemSetAllocMethodHeap(s32 heap, s32 method);
void OSReport(const char* msg, ...);
}

extern f32 __float_nan[];

union FadeFloatShape {
    f32 value;
    s32 bits;
};

static inline f32 fadeSqrtf(f32 value) {
    FadeFloatShape shape;
    f64 estimate;
    s32 exponent;
    s32 fpclass;

    if (value > 0.0f) {
        const f64 half = 0.5;
        const f64 three = 3.0;

        estimate = __frsqrte(value);
        estimate = half * estimate * (three - value * (estimate * estimate));
        estimate = half * estimate * (three - value * (estimate * estimate));
        estimate = half * estimate * (three - value * (estimate * estimate));
        return (f32)(value * estimate);
    }
    if ((f64)value < 0.0) {
        return __float_nan[0];
    }

    shape.value = value;
    exponent = shape.bits & 0x7F800000;
    switch (exponent) {
    case 0x7F800000:
        fpclass = (shape.bits & 0x007FFFFF) != 0 ? 1 : 2;
        break;
    case 0:
        fpclass = (shape.bits & 0x007FFFFF) != 0 ? 5 : 3;
        break;
    default:
        fpclass = 4;
        break;
    }
    if (fpclass == 1) {
        return __float_nan[0];
    }
    return value;
}

static FadeFluidWork _fadeFluidWork;
static u32 _fadeFluidSw;

static void _fadeFluidSetShockSub(u32 x, u32 y, f32 strength);
static void _fadeFluidDoFree(void* ptr);
static void* _fadeFluidDoMalloc(u32 size);

static inline void FluidPosition3f32(f32 x, f32 y, f32 z) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}
static inline void FluidColor4u8(u8 r, u8 g, u8 b, u8 a) {
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;
}
static inline void FluidTexCoord2f32(f32 s, f32 t) {
    GXWGFifo.f32 = s;
    GXWGFifo.f32 = t;
}
static inline u32 FluidRow(u32 y, u32 stride) {
    return y * stride;
}
static inline void FluidVertex2(GSvec* vertex, f32 sx, f32 sy, u8 alpha) {
    FluidPosition3f32(vertex->x * sx, vertex->y * sy, vertex->z * sx);
    FluidColor4u8(255, 255, 255, alpha);
}
static inline void FluidVertex(GSvec* vertex, GSvec2* uv, f32 sx, f32 sy, u8 alpha) {
    FluidPosition3f32(vertex->x * sx, vertex->y * sy, vertex->z * sx);
    FluidColor4u8(255, 255, 255, alpha);
    FluidTexCoord2f32(uv->x, uv->y);
}

extern "C" {

void fadeFluidDispSecond(int layerID, GStexture* tex, f32 progress, f32 blend) {
    u32 count;
    GSvec color;
    GSvec from;
    f32 sx;
    s32 alpha;
    f32 value;
    GSvec to;
    f32 sy;
    s32 y;
    GSgfxLayer* layer;
    u32 stride;
    layer = GSgfxLayerFindByID(layerID);
    from.x = 1.0f; from.y = 1.0f; from.z = 1.0f;
    to.x = 0.0f; to.y = 0.0f; to.z = 0.0f;
    GSlerpGetLinearInterpolationVector(&color, &from, &to, blend);
    value = (f32)(s32)(255.0f * color.x);
    alpha = (s32)(value * (1.0f - progress));
    spriteSetEnv(layerID);
    if (layer->curBlendIdx != 1) {
        layer->curBlendIdx = 1;
        layer->curBlend = &layer->blendTable[layer->curBlendIdx];
    }
    layer->blendOp = 1;
    layer->blendSrc = 4;
    layer->blendDst = 5;
    layer->blendLogic = 5;
    layer->dirty170c |= 1;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 1;
    layer->dirty1760 |= 0x40;
    layer->colorUpdate = 1;
    layer->alphaUpdate = 1;
    layer->zUpdate = 0;
    layer->dirty170c |= 4;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 4;
    layer->dirty1760 |= 0x40;
    layer->zEnable = 0;
    layer->zFunc = 1;
    layer->dirty170c |= 8;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 8;
    layer->dirty1760 |= 0x40;
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != tex || layer->tex17f8 != tex || tex->unk7 != 0) {
        layer->tex1740 = tex;
        layer->dirty173c |= 1;
        layer->tex17f8 = tex;
        layer->dirty17f4 |= 1;
    }
    sx = _fadeFluidWork.xScale; sy = _fadeFluidWork.yScale;
    stride = _fadeFluidWork.columns + 1;
    count = stride * 2;
    for (y = 0; y < _fadeFluidWork.rows; ++y) {
        layer->primType = 0x98;
        GSvec** slot;
        GSvec2* uv;
        u32 rowB;
        u32 j;
        u32 x;
        u32 rowA;
        u32 i;
        layer->beginSurface(count);
        slot = &_fadeFluidWork.heightPage[_fadeFluidSw];
        uv = _fadeFluidWork.texCoord;
        rowA = FluidRow(y, stride); rowB = (y + 1) * stride;
        for (x = 0; x < stride; ++x) {
            i = x + rowA; j = x + rowB;
            FluidVertex2(&(*slot)[i], sx, sy, alpha);
            GSvec2* t0 = &uv[i];
            FluidTexCoord2f32(t0->x, t0->y);
            FluidVertex(&(*slot)[j], &uv[j], sx, sy, alpha);
        }
        layer->endSurface();
    }
}

void fadeFluidDisp(GStexture* tex, f32 progress, f32 blend) {
    u32 count;
    GSvec color;
    GSvec from;
    f32 sx;
    s32 alpha;
    f32 value;
    GSvec to;
    f32 sy;
    s32 y;
    GSgfxLayer* layer;
    u32 stride;
    layer = GSgfxLayerFindByID(7);
    from.x = 1.0f; from.y = 1.0f; from.z = 1.0f;
    to.x = 0.0f; to.y = 0.0f; to.z = 0.0f;
    GSlerpGetLinearInterpolationVector(&color, &from, &to, blend);
    value = (f32)(s32)(255.0f * color.x);
    alpha = (s32)(value * (1.0f - progress));
    spriteSetEnv(7);
    if (layer->curBlendIdx != 1) {
        layer->curBlendIdx = 1;
        layer->curBlend = &layer->blendTable[layer->curBlendIdx];
    }
    layer->blendOp = 1;
    layer->blendSrc = 4;
    layer->blendDst = 5;
    layer->blendLogic = 5;
    layer->dirty170c |= 1;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 1;
    layer->dirty1760 |= 0x40;
    layer->colorUpdate = 1;
    layer->alphaUpdate = 1;
    layer->zUpdate = 0;
    layer->dirty170c |= 4;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 4;
    layer->dirty1760 |= 0x40;
    layer->zEnable = 0;
    layer->zFunc = 1;
    layer->dirty170c |= 8;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 8;
    layer->dirty1760 |= 0x40;
    layer->f1664 = 7;
    layer->f1670 = 0;
    layer->f1668 = 0;
    layer->f166c = 7;
    layer->f1671 = 0;
    layer->f1672 = 1;
    layer->dirty170c |= 0x10;
    layer->dirty16a8 |= 0x40;
    layer->dirty17c4 |= 0x10;
    layer->dirty1760 |= 0x40;
    layer->d8c = 0;
    layer->dirty16b8 |= 2;
    layer->dirty16a8 |= 2;
    layer->dirty1770 |= 2;
    layer->dirty1760 |= 2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 1, 1, 4));
    if (layer->tex1740 != tex || layer->tex17f8 != tex || tex->unk7 != 0) {
        layer->tex1740 = tex;
        layer->dirty173c |= 1;
        layer->tex17f8 = tex;
        layer->dirty17f4 |= 1;
    }
    layer->primType = 0x98;
    sx = _fadeFluidWork.xScale; sy = _fadeFluidWork.yScale;
    stride = _fadeFluidWork.columns + 1;
    count = stride * 2;
    for (y = 0; y < _fadeFluidWork.rows; ++y) {
        GSvec** slot;
        GSvec2* uv;
        u32 rowB;
        u32 j;
        u32 x;
        u32 rowA;
        u32 i;
        layer->beginSurface(count);
        slot = &_fadeFluidWork.heightPage[_fadeFluidSw];
        uv = _fadeFluidWork.texCoord;
        rowA = FluidRow(y, stride); rowB = (y + 1) * stride;
        for (x = 0; x < stride; ++x) {
            i = x + rowA; j = x + rowB;
            FluidVertex2(&(*slot)[i], sx, sy, alpha);
            GSvec2* t0 = &uv[i];
            FluidTexCoord2f32(t0->x, t0->y);
            FluidVertex(&(*slot)[j], &uv[j], sx, sy, alpha);
        }
        layer->endSurface();
    }
}

void fadeFluidSetShockSecond(GSvec* position, f32 strength) {
    f32 cellSize = _fadeFluidWork.cellSize;
    u32 x = position->x / cellSize;
    u32 y = position->y / cellSize;
    f32 edge, corner;

    _fadeFluidSetShockSub(x, y, strength);
    edge = 0.5f * strength;
    corner = 0.25f * strength;
    _fadeFluidSetShockSub(x - 1, y - 1, corner);
    _fadeFluidSetShockSub(x, y - 1, edge);
    _fadeFluidSetShockSub(x + 1, y - 1, corner);
    _fadeFluidSetShockSub(x - 1, y, edge);
    _fadeFluidSetShockSub(x + 1, y, edge);
    _fadeFluidSetShockSub(x - 1, y + 1, corner);
    _fadeFluidSetShockSub(x, y + 1, edge);
    _fadeFluidSetShockSub(x + 1, y + 1, corner);
}

void fadeFluidEvaluateSecond(void) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    GSvec* source;
    u32 rowStride = fluid->columns + 1;
    s32 x;
    s32 y;
    f32 accel = fluid->accel;
    f32 damping = fluid->damping;
    f32 neighbor = fluid->neighbor;

    for (y = 1; y < fluid->rows; y++) {
        u32 row = y * rowStride;
        GSvec* destination;
        source = _fadeFluidWork.heightPage[_fadeFluidSw] + row;
        destination = _fadeFluidWork.heightPage[1 - _fadeFluidSw] + row;

        for (x = 1; x < fluid->columns; x++) {
            destination[x].z =
                accel * source[x].z + damping * destination[x].z +
                neighbor * (source[x + 1].z + source[x - 1].z + source[x + rowStride].z +
                            source[x - rowStride].z);
        }
    }
    _fadeFluidSw = 1 - _fadeFluidSw;
}

void fadeFluidSetShock(GSvec* position, f32 strength) {
    f32 cellSize = _fadeFluidWork.cellSize;
    u32 x = position->x / cellSize;
    u32 y = position->y / cellSize;

    _fadeFluidSetShockSub(x, y, strength);
    strength *= 0.5f;
    _fadeFluidSetShockSub(x - 1, y - 1, strength);
    _fadeFluidSetShockSub(x, y - 1, strength);
    _fadeFluidSetShockSub(x + 1, y - 1, strength);
    _fadeFluidSetShockSub(x - 1, y, strength);
    _fadeFluidSetShockSub(x + 1, y, strength);
    _fadeFluidSetShockSub(x - 1, y + 1, strength);
    _fadeFluidSetShockSub(x, y + 1, strength);
    _fadeFluidSetShockSub(x + 1, y + 1, strength);
}

}

static void _fadeFluidSetShockSub(u32 x, u32 y, f32 strength) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    u32 columns = fluid->columns;

    if (x > columns) {
        return;
    }
    if (y > fluid->rows) {
        return;
    }

    ((f32*)fluid->heightPage[_fadeFluidSw])[3 * (x + (y * (columns + 1))) + 2] -= strength;
}

extern "C" {

void fadeFluidEvaluate(void) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    FadeFluidWork* work;
    u32 rowStride = fluid->columns + 1;
    GSvec* source;
    s32 x;
    s32 y;
    f32 accel = fluid->accel;
    f32 damping = fluid->damping;
    f32 neighbor = fluid->neighbor;

    for (y = 1; y < fluid->rows; y++) {
        u32 row = y * rowStride;
        GSvec* destination;
        source = _fadeFluidWork.heightPage[_fadeFluidSw] + row;
        destination = _fadeFluidWork.heightPage[1 - _fadeFluidSw] + row;

        for (x = 1; x < fluid->columns; x++) {
            destination[x].z =
                accel * source[x].z + damping * destination[x].z +
                neighbor * (source[x + 1].z + source[x - 1].z + source[x + rowStride].z +
                            source[x - rowStride].z);
        }
    }

    _fadeFluidSw = 1 - _fadeFluidSw;
    work = &_fadeFluidWork;
    for (y = 1; y < fluid->rows; y++) {
        u32 row = y * rowStride;
        GSvec* height = _fadeFluidWork.heightPage[_fadeFluidSw] + row;
        GSvec* velocityX = work->velocityX + row;
        GSvec* velocityY = work->velocityY + row;

        for (x = 1; x < work->columns; x++) {
            velocityX[x].x = height[x - 1].z - height[x + 1].z;
            velocityX[x].y = height[x - rowStride].z - height[x + rowStride].z;
            velocityY[x].z = height[x + 1].z - height[x - 1].z;
        }
    }
}

void fadeFluidCalcParms(f32 dt) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    f32 c = fluid->limit;
    f32 d = fluid->cellSize;
    f32 c2 = c * c;
    f32 d2 = d * d;
    f32 mt = fluid->timeStep * dt;
    f32 ct = dt * c2;
    f32 f1 = (dt * ct) / d2;
    f32 f2 = 1.0f / (2.0f + mt);
    f32 k1;
    f32 k2;
    f32 k3;

    k1 = 4.0f - 8.0f * f1;
    fluid->accel = k1 * f2;
    k2 = mt - 2.0f;
    fluid->damping = f2 * k2;
    k3 = 2.0f * f1;
    fluid->neighbor = k3 * f2;
}

void fadeFluidQuit(void) {
    FadeFluidWork* fluid0 = &_fadeFluidWork;
    FadeFluidWork* fluid1;
    FadeFluidWork* fluid2;
    FadeFluidWork* fluid3;
    FadeFluidWork* fluid4;

    if (fluid0->heightPage[0] != 0) {
        _fadeFluidDoFree(fluid0->heightPage[0]);
    }

    fluid1 = &_fadeFluidWork;
    if (fluid1->heightPage[1] != 0) {
        _fadeFluidDoFree(fluid1->heightPage[1]);
    }

    fluid2 = &_fadeFluidWork;
    if (fluid2->velocityX != 0) {
        _fadeFluidDoFree(fluid2->velocityX);
    }

    fluid3 = &_fadeFluidWork;
    if (fluid3->velocityY != 0) {
        _fadeFluidDoFree(fluid3->velocityY);
    }

    fluid4 = &_fadeFluidWork;
    if (fluid4->texCoord != 0) {
        _fadeFluidDoFree(fluid4->texCoord);
    }

    fluid0->heightPage[0] = 0;
    fluid1->heightPage[1] = 0;
    fluid2->velocityX = 0;
    fluid3->velocityY = 0;
    fluid4->texCoord = 0;
}

inline float fadeFluidInitInline(f32 arg0) { return 2.0f * arg0; }

void fadeFluidInit(u32 columns, u32 rows, f32 cellSize, f32 calcStep, f32 waveLimit, f32 timeStep) {
    FadeFluidWork* fluid = &_fadeFluidWork;
    u32 pointCount;
    u32 vectorBytes;
    s32 x;
    s32 y;
    u32 index;
    f32 velocity;
    f32 texStepX;
    f32 texStepY;
    f32 maximumLimit;

    fluid->xScale = 640.0f / (f32)columns;
    pointCount = (columns + 1) * (rows + 1);
    vectorBytes = pointCount * sizeof(GSvec);
    fluid->yScale = 480.0f / (f32)rows;
    fluid->columns = columns;
    fluid->rows = rows;
    _fadeFluidWork.heightPage[0] = (GSvec*)_fadeFluidDoMalloc(vectorBytes);
    _fadeFluidWork.heightPage[1] = (GSvec*)_fadeFluidDoMalloc(vectorBytes);
    _fadeFluidSw = 0;
    _fadeFluidWork.velocityX = (GSvec*)_fadeFluidDoMalloc(vectorBytes);
    _fadeFluidWork.velocityY = (GSvec*)_fadeFluidDoMalloc(vectorBytes);
    _fadeFluidWork.texCoord = (GSvec2*)_fadeFluidDoMalloc(pointCount * sizeof(GSvec2));

    maximumLimit = (cellSize / (2.0f * calcStep)) * fadeSqrtf(2.0f + timeStep);
    if (!(0.0f < waveLimit && waveLimit < maximumLimit)) {
        OSReport("Warning: fadeFluid c parm. Limit Over!! -> 0.0f < %f < %f\n", waveLimit,
                 maximumLimit);
        waveLimit = maximumLimit - 1.0e-6f;
    }
    _fadeFluidWork.cellSize = cellSize;
    _fadeFluidWork.limit = waveLimit;
    _fadeFluidWork.timeStep = timeStep;
    fadeFluidCalcParms(calcStep);

    velocity = fadeFluidInitInline(cellSize);
    texStepX = 1.0f / (f32)_fadeFluidWork.columns;
    texStepY = 1.0f / (f32)fluid->rows;
    index = 0;
    for (y = 0; y <= rows; y++) {
        for (x = 0; x <= columns; x++) {
            _fadeFluidWork.heightPage[0][index].set(cellSize * (f32)x, cellSize * (f32)y, 0.0f);
            _fadeFluidWork.heightPage[1][index] = _fadeFluidWork.heightPage[0][index];
            _fadeFluidWork.velocityX[index].set(0.0f, 0.0f, velocity);
            _fadeFluidWork.velocityY[index].set(velocity, 0.0f, 0.0f);
            _fadeFluidWork.texCoord[index].x = texStepX * (f32)x;
            _fadeFluidWork.texCoord[index].y = texStepY * (f32)y;
            index++;
        }
    }
}

}

static void _fadeFluidDoFree(void* ptr) {
    GSmemFree(ptr);
}

static void* _fadeFluidDoMalloc(u32 size) {
    void* mem;
    s32 old = GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(), 3);
    mem = GSmemAllocAlign(size, 0x20);
    GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(), old);
    return mem;
}
