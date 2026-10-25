// Needs extra cflags: -opt nopeephole
extern "C" {
#include <dolphin/types.h>
#include <dolphin/os/OSFastCast.h>
}

struct GStexture;
struct GSvec2 {
    f32 x, y;
};
struct FLASHMATRIXF {
    f32 m[6];
};
struct FLASHMATRIX {
    s32 m[6];
};
struct FLASHCXFORM {
    s16 v[8];
};
struct VEC_GRAPH_DATA {
    s32 fillLeft,fillRight,shiftLeft,shiftRight,previousLeft,previousRight;
    s16 minX,minY,maxX,maxY,centerX,centerY,width,height;
    u32 color;
    FLASHCXFORM* colorTransform;
    u32 lineColor,styleCount;
    void* fillStyles;
    void* lineStyles;
    void* gradient;
    s32 originX,originY;
    f32 scale,angle,sinAngle,cosAngle,inverseSin,inverseCos;
    u8 reserved64[0x400];
    s16 crossPoints[256][8];
};
struct GXColor {
    u8 r, g, b, a;
};
struct GXColorS10 {
    s16 r, g, b, a;
};
struct SHAPEMOVE {
    s32 pad;
    s32 x;
    s32 y;
};
struct _SHAPERECORD {
    u8 type;
    u8 pad[3];
    SHAPEMOVE *move;
    _SHAPERECORD *next;
};

extern "C" {
GStexture *FlashSystemGetGStexture(u32 id, long index);
void GSprimDraw2DTexQuad4V(const GSvec2 *, const GSvec2 *, GStexture *, const GXColor *);
void GSprimDraw2DTexQuad4VCA(const GSvec2 *, const GSvec2 *, GStexture *, const GXColor *, const GXColorS10 *);
}

struct SBRow {
    s8 count;
    u8 pad;
    s16 pts[33];
    VEC_GRAPH_DATA data;
};

typedef char SBRowSize[sizeof(SBRow) == 0x14A8 ? 1 : -1];

s32 bit_value[32] = {
    0x00000001,
    0x00000002,
    0x00000004,
    0x00000008,
    0x00000010,
    0x00000020,
    0x00000040,
    0x00000080,
    0x00000100,
    0x00000200,
    0x00000400,
    0x00000800,
    0x00001000,
    0x00002000,
    0x00004000,
    0x00008000,
    0x00010000,
    0x00020000,
    0x00040000,
    0x00080000,
    0x00100000,
    0x00200000,
    0x00400000,
    0x00800000,
    0x01000000,
    0x02000000,
    0x04000000,
    0x08000000,
    0x10000000,
    0x20000000,
    0x40000000,
    0x80000000
};

u8 gVecDat[0x1464];
u8 scanline_buffer[0x25800];
static s16 vecRect[8];
SBRow lPoint[4];
static u32 lList[0x601];

static s32 debugstep = 1;
static s32 _type = 1;
static s32 _src = 4;
static s32 _dst = 5;
static s32 _typemask = 1;
static s32 _srcmask = 4;
static s32 _dstmask = 5;

static void SBdec(u32 bits, s16 idx, u32 n) {
    u32 i;
    if ((bits & 0xFF) != 0) {
        s32 base = idx * 8;
        for (i = 0; i < n; i++) {
            if ((bits & bit_value[i]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base;
            }
            if ((bits & bit_value[i + 4]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 1;
            }
        }
    }
    if ((bits & 0xFF00) != 0) {
        s32 base = idx * 8;
        for (i = 0; i < n; i++) {
            if ((bits & bit_value[i + 8]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 2;
            }
            if ((bits & bit_value[i + 12]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 3;
            }
        }
    }
    if ((bits & 0xFF0000) != 0) {
        s32 base = idx * 8;
        for (i = 0; i < n; i++) {
            if ((bits & bit_value[i + 16]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 4;
            }
            if ((bits & bit_value[i + 20]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 5;
            }
        }
    }
    if ((bits & 0xFF000000) != 0) {
        s32 base = idx * 8;
        for (i = 0; i < n; i++) {
            if ((bits & bit_value[i + 24]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 6;
            }
            if ((bits & bit_value[i + 28]) != 0) {
                lPoint[i].pts[lPoint[i].count++] = (s16)base + 7;
            }
        }
    }
}

static void getUV(GSvec2 *, GSvec2 *, GSvec2 *, FLASHMATRIXF *, FLASHMATRIXF *, GStexture *);
static void SpriteDisp(GStexture *, FLASHMATRIXF *, FLASHMATRIX *, GSvec2 *, VEC_GRAPH_DATA *, FLASHCXFORM *);

static _SHAPERECORD *SpriteCode(u32 id, _SHAPERECORD *rec, u16 index, FLASHMATRIXF *m, FLASHMATRIX *fm, long x, long y,
                                VEC_GRAPH_DATA *vg, FLASHCXFORM *cx) {
    GSvec2 pts[4];
    GSvec2 *q;
    u8 more = 1;
    _SHAPERECORD *last = 0;
    s32 n = 0;
    do {
        if (rec->type == 2) {
            x += rec->move->x;
            y += rec->move->y;
            last = rec;
            q = &pts[n++];
            q->x = (f32)x / 20.0f;
            q->y = (f32)y / 20.0f;
            rec = rec->next;
        } else {
            more = 0;
        }
    } while (more);
    SpriteDisp(FlashSystemGetGStexture(id, index), m, fm, pts, vg, cx);
    return last;
}

static void SpriteDisp(GStexture *tex, FLASHMATRIXF *m, FLASHMATRIX *fm, GSvec2 *vec, VEC_GRAPH_DATA *vg, FLASHCXFORM *cx) {
    if (tex != 0) {
        FLASHMATRIXF fl;
        GSvec2 uv[4];
        GSvec2 pos[4];
        GXColorS10 add;
        GXColor col;
        fl.m[0] = (f32)fm->m[0] / 1310720.0f;
        fl.m[1] = (f32)fm->m[1] / 1310720.0f;
        fl.m[2] = (f32)fm->m[2] / 1310720.0f;
        fl.m[3] = (f32)fm->m[3] / 1310720.0f;
        fl.m[4] = (f32)fm->m[4] / 20.0f;
        fl.m[5] = (f32)fm->m[5] / 20.0f;
        getUV(pos, uv, vec, m, &fl, tex);
        col.a = (cx->v[0] * 0xff) >> 8;
        col.r = (cx->v[2] * 0xff) >> 8;
        col.g = (cx->v[4] * 0xff) >> 8;
        col.b = (cx->v[6] * 0xff) >> 8;
        add.a = cx->v[1];
        add.r = cx->v[3];
        add.g = cx->v[5];
        add.b = cx->v[7];
        if (((s16)add.a | (s16)add.r | (s16)add.g | (s16)add.b) == 0) {
            GXColor c = col;
            GSprimDraw2DTexQuad4V(pos, uv, tex, &c);
            return;
        }
        {
            GXColorS10 a = add;
            GXColor c = col;
            GSprimDraw2DTexQuad4VCA(pos, uv, tex, &c, &a);
        }
    }
}

extern "C" void vectroGraphSetBlendMode(s32 src, s32 dst) {
    _src = src;
    _dst = dst;
}

void getCrossPoint(long column,short y,short x1,short x2,short originX,short originY,VEC_GRAPH_DATA* data) {
    s32 dy = y - originX;
    s32 dx1 = x1 - originY;
    s32 dx2 = x2 - originY;
    f32 sine = data->sinAngle;
    f32 cosine = data->cosAngle;
    vecRect[0] = cosine * dy - sine * dx1;
    vecRect[1] = sine * dy + cosine * dx1;
    vecRect[2] = cosine * dy - sine * dx2;
    vecRect[3] = sine * dy + cosine * dx2;
    vecRect[6] = vecRect[2] > vecRect[0] ? vecRect[2] - vecRect[0] : vecRect[0] - vecRect[2];
    vecRect[7] = vecRect[3] > vecRect[1] ? vecRect[3] - vecRect[1] : vecRect[1] - vecRect[3];
    if (vecRect[6] == 0 || vecRect[7] == 0) {
        s16 value = vecRect[0] + originX;
        for (s32 i=0;i<256;i++) data->crossPoints[i][column] = value;
    } else {
        for (s32 i=0;i<256;i++) {
            s16 position = i + data->originY - originY;
            s16 distance = position > vecRect[1] ? position - vecRect[1] : vecRect[1] - position;
            f32 fraction = (f32)distance / (f32)vecRect[7];
            s16 value;
            if (vecRect[0] < vecRect[2]) {
                f32 interpolated = (f32)vecRect[6] * fraction + (f32)vecRect[0];
                value = interpolated;
                if (vecRect[2] < (s16)interpolated) value = vecRect[2];
            } else {
                f32 interpolated = -((f32)vecRect[6] * fraction - (f32)vecRect[0]);
                value = interpolated;
                if (vecRect[2] > (s16)interpolated) value = vecRect[2];
            }
            data->crossPoints[i][column] = value + originX;
        }
    }
}

extern "C" {
void flcalcMatrix(GSvec2*,FLASHMATRIXF*,GSvec2*);
extern f32 __float_nan[];
}
static inline s32 vecFloatClass(f32 x) {
    union {f32 value;s32 bits;} v;v.value=x;
    switch(v.bits&0x7f800000) {
    case 0x7f800000:return (v.bits&0x7fffff)?1:2;
    case 0:return (v.bits&0x7fffff)?5:3;
    default:return 4;
    }
}
static inline f32 vecSqrt(f32 x) {
    if(x>0.0f) {
        f64 guess=__frsqrte(x);
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        return (f32)((f64)x*guess);
    }
    if((f64)x<0.0)return __float_nan[0];
    if(vecFloatClass(x)==1)return __float_nan[0];
    return x;
}
static void getUV(GSvec2* output,GSvec2* uv,GSvec2* quad,FLASHMATRIXF* transform,FLASHMATRIXF* textureTransform,GStexture* texture) {
    GSvec2 origin;
    FLASHMATRIXF* matrix=textureTransform;
    GSvec2* currentOutput;
    origin.x=0.0f;origin.y=0.0f;
    flcalcMatrix(uv,matrix,&origin);
    f32 x=uv->x,y=uv->y;
    f32 scaleX=vecSqrt(matrix->m[0]*matrix->m[0]+matrix->m[1]*matrix->m[1]);
    f32 scaleY=vecSqrt(matrix->m[2]*matrix->m[2]+matrix->m[3]*matrix->m[3]);
    f32 nearest=1.0e9f;
    s32 index;
    GSvec2* point=quad;
    for(s32 i=0;i<4;point++,i++) {
        f32 dx=point->x-x,dy=point->y-y;
        f32 distance=vecSqrt(dx*dx+dy*dy);
        if(nearest>distance) {index=i;nearest=distance;}
    }
    currentOutput=output;
    for(s32 i=0;i<4;currentOutput++,uv++,i++) {
        *currentOutput=quad[(index+i)&3];
        uv->x=(currentOutput->x-x)/(f32)*(u16*)texture;
        uv->x/=scaleX;
        if(uv->x<0.0f)uv->x=-uv->x;
        if(uv->x>1.0f)uv->x=1.0f;
        uv->y=(currentOutput->y-y)/(f32)*((u16*)texture+1);
        uv->y/=scaleY;
        if(uv->y<0.0f)uv->y=-uv->y;
        if(uv->y>1.0f)uv->y=1.0f;
        flcalcMatrix(currentOutput,transform,currentOutput);
    }
}

struct _FILLSTYLEARRAY {u32 count;void* styles;};
struct _LINESTYLEARRAY {u32 count;void* styles;};
static void vecExec(u32,_FILLSTYLEARRAY*,_LINESTYLEARRAY*,_SHAPERECORD*,FLASHMATRIXF*,FLASHMATRIXF*,FLASHCXFORM*);
struct GSgfxLayer {
    u8 reserved0[0x1644];
    s32 blendMode,blendSource,blendDestination,blendLogic;
    u8 reserved1654[0x20];
    u8 dithering;
    u8 reserved1675[0x33];
    u32 dirty;
    u8 reserved16AC[0x60];
    u32 pixelDirty;
    u8 reserved1710[0x50];
    u32 savedDirty;
    u8 reserved1764[0x60];
    u32 savedPixelDirty;
    u8 reserved17C8[0x1C8];
    void* shader;
    s32 shaderIndex;
};
extern "C" {
void GSprimSetup2DRender__FP10GSgfxLayer(GSgfxLayer*);
s32 GSgfxLayerGetActive();
GSgfxLayer* GSgfxLayerFindByID(s32);
void GSprimSetQuadVertexOrder(s32);
u32 flcalcMultiTransformColor(FLASHCXFORM*,u32);
void* memset(void*,int,unsigned long);
}
static inline void vecPixelDirty(GSgfxLayer* layer,u32 bits) {
    layer->pixelDirty|=bits;layer->dirty|=0x40;layer->savedPixelDirty|=bits;layer->savedDirty|=0x40;
}
static inline void vecSelectShader(GSgfxLayer* layer,s32 index) {
    if(layer->shaderIndex!=index) {
        layer->shaderIndex=index;layer->shader=(u8*)layer+0x1818+layer->shaderIndex*0xbc;
    }
}
static inline void vecBlend(GSgfxLayer* layer,s32 type,s32 source,s32 destination) {
    if(type==0) {vecSelectShader(layer,0);layer->blendMode=0;layer->blendSource=1;layer->blendDestination=1;layer->blendLogic=5;}
    else {vecSelectShader(layer,1);layer->blendMode=type;layer->blendSource=source;layer->blendDestination=destination;layer->blendLogic=5;}
    vecPixelDirty(layer,1);
}
extern "C" void vectorGraph(u32 id,_FILLSTYLEARRAY* fills,_LINESTYLEARRAY* lines,_SHAPERECORD* shapes,FLASHMATRIXF* matrix,FLASHMATRIXF* textureMatrix,FLASHCXFORM* colors,u8 flags) {
    if(debugstep!=0x18) {
        GSprimSetup2DRender__FP10GSgfxLayer(0);
        GSgfxLayer* layer=GSgfxLayerFindByID(GSgfxLayerGetActive());
        layer->dithering=1;vecPixelDirty(layer,0x20);
        if(flags&0x40)vecBlend(layer,_typemask,_srcmask,_dstmask);
        else vecBlend(layer,_type,_src,_dst);
        GSprimSetQuadVertexOrder(1);
        ((VEC_GRAPH_DATA*)gVecDat)->fillLeft=0;((VEC_GRAPH_DATA*)gVecDat)->shiftLeft=-1;((VEC_GRAPH_DATA*)gVecDat)->previousLeft=-1;
        ((VEC_GRAPH_DATA*)gVecDat)->fillRight=0;((VEC_GRAPH_DATA*)gVecDat)->shiftRight=-1;((VEC_GRAPH_DATA*)gVecDat)->previousRight=-1;
        ((VEC_GRAPH_DATA*)gVecDat)->styleCount=fills->count;((VEC_GRAPH_DATA*)gVecDat)->colorTransform=colors;
        ((VEC_GRAPH_DATA*)gVecDat)->lineColor=flcalcMultiTransformColor(colors,0xffffffff);
        ((VEC_GRAPH_DATA*)gVecDat)->fillStyles=fills->styles;((VEC_GRAPH_DATA*)gVecDat)->lineStyles=lines->styles;
        ((VEC_GRAPH_DATA*)gVecDat)->minY=0x7fff;((VEC_GRAPH_DATA*)gVecDat)->minX=0x7fff;((VEC_GRAPH_DATA*)gVecDat)->maxY=-0x8000;((VEC_GRAPH_DATA*)gVecDat)->maxX=-0x8000;
        memset(scanline_buffer,0,sizeof(scanline_buffer));
        vecExec(id,fills,lines,shapes,matrix,textureMatrix,colors);
    }
}


extern "C" {
int printf(const char*,...);
void* memcpy(void*,const void*,u32);
void GSprimSetLineWidth(f32);
void GSprimDraw2DLineListC(const GSvec2*,u32,const GXColor*);
}
struct VEC_RECT {s16 x0,y0,x1,y1,twiceX,twiceY,dx,dy;};
static void calcVecRect(VEC_RECT*,VEC_GRAPH_DATA*,long);
static void gradientline(s16,s16,s16,VEC_GRAPH_DATA*);

static inline void vecTogglePoint(s16 x,s16 y,u32* row) {
    if(x<0)x=0;
    if(x>=640)x=639;
    if(y>=0 && y<480) {
        u32* bits=row+x/8;
        VEC_GRAPH_DATA* data=(VEC_GRAPH_DATA*)gVecDat;
        if(data->fillLeft) {
            u32 mask=bit_value[data->shiftLeft+(x%8)*4];
            if(*bits&mask)*bits^=mask;else *bits|=mask;
        }
        if(data->fillRight) {
            u32 mask=bit_value[data->shiftRight+(x%8)*4];
            if(*bits&mask)*bits^=mask;else *bits|=mask;
        }
        if(debugstep==0)printf("x = %3d\t\ty = %3d\n",x,y);
    }
}

static void SBline(GSvec2* first,GSvec2* second) {
    s16 previousY=-1;
    if(debugstep==0x77F)return;
    if(first->y<second->y) {
        vecRect[0]=(s16)first->x;vecRect[1]=(s16)first->y;
        vecRect[2]=(s16)second->x;vecRect[3]=(s16)second->y;
    }else if(first->y>second->y) {
        vecRect[0]=(s16)second->x;vecRect[1]=(s16)second->y;
        vecRect[2]=(s16)first->x;vecRect[3]=(s16)first->y;
    }else return;
    vecRect[7]=vecRect[3]-vecRect[1];
    if(vecRect[7]==0)return;
    s16 direction=vecRect[2]>vecRect[0]?1:-1;
    s16 width=vecRect[2]>vecRect[0]?vecRect[2]-vecRect[0]:vecRect[0]-vecRect[2];
    vecRect[6]=width;
    s16 x=vecRect[0],y=vecRect[1];
    vecRect[4]=width*2;vecRect[5]=vecRect[7]*2;
    if(width==0) {
        for(s16 i=0;i<vecRect[7];++i) {
            s16 row=y++;
            vecTogglePoint(x,row,(u32*)(scanline_buffer+row*0x140));
        }
        return;
    }
    if(vecRect[7]<2) {
        vecTogglePoint(x,y,(u32*)(scanline_buffer+y*0x140));
        return;
    }
    if(width>=vecRect[7]) {
        s16 error=-width;
        u32* row=(u32*)(scanline_buffer+y*0x140);
        for(s16 i=0;i<=vecRect[6];++i) {
            if(y==vecRect[3])return;
            if(previousY!=y) {
                vecTogglePoint(x,y,row);
                previousY=y;
            }
            x+=direction;
            error+=vecRect[5];
            if(error>=0) {
                row+=0x50;++y;
                error-=vecRect[4];
            }
        }
    }else {
        s16 error=-vecRect[7];
        u32* row=(u32*)(scanline_buffer+y*0x140);
        for(s16 i=0;i<vecRect[7];++i) {
            vecTogglePoint(x,y,row);
            row+=0x50;++y;
            error+=vecRect[4];
            if(error>=0) {x+=direction;error-=vecRect[5];}
        }
    }
}

static inline void vecFlushLines() {
    if(debugstep==0x1229)lList[0]=0;
    else {
        if(lList[0])GSprimDraw2DLineListC((GSvec2*)&lList[0x201],lList[0]>>1,(GXColor*)&lList[1]);
        lList[0]=0;
    }
}
static inline void vecLineVertex(s16 x,s16 y,u32 color) {
    if(lList[0]>=0x200)vecFlushLines();
    memcpy(&lList[lList[0]+1],&color,4);
    ((GSvec2*)&lList[0x201])[lList[0]].x=(f32)x;
    ((GSvec2*)&lList[0x201])[lList[0]].y=(f32)y;
    ++lList[0];
}
static void SBscan() {
    VEC_GRAPH_DATA* data=(VEC_GRAPH_DATA*)gVecDat;
    if(data->styleCount>4) {printf("ERROR:style count %d\n",data->styleCount);return;}
    if(debugstep==0x174B || debugstep==0x77F)return;
    GSprimSetLineWidth(1.0f);
    lList[0]=0;
    for(u32 style=0;style<data->styleCount;++style) {
        calcVecRect((VEC_RECT*)vecRect,data,style);
        lPoint[style].data=*data;
    }
    s16 y=vecRect[1];
    u32* row=(u32*)(scanline_buffer+y*0x140);
    for(;y<=vecRect[3];++y,row+=0x50) {
        lPoint[3].count=0;lPoint[2].count=0;lPoint[1].count=0;lPoint[0].count=0;
        s16 block=vecRect[0]/8;
        u32* bits=row+block;
        for(;block<=vecRect[2]/8;++block,++bits)if(*bits)SBdec(*bits,block,data->styleCount);
        for(u32 style=0;style<data->styleCount;++style) {
            SBRow* points=&lPoint[style];
            if(points->count%2==0)for(s32 i=0;i<points->count;i+=2) {
                s16 right=points->pts[i+1];
                if(points->data.gradient)gradientline(points->pts[i],right,y,&points->data);
                else {
                    vecLineVertex(points->pts[i],y,points->data.color);
                    vecLineVertex(right,y,points->data.color);
                }
            }
        }
    }
    vecFlushLines();
}


struct VecGradientStop {u8 ratio;u8 padding[3];u32 color;};
struct VecGradient {u8 count;u8 padding[3];VecGradientStop stops[8];};
struct VecFillStyle {
    u8 type;u8 padding[3];u32 color;
    FLASHMATRIX matrix;
    VecGradient gradient;
    u16 texture;u16 reserved66;
    FLASHMATRIX textureMatrix;
};
typedef char VecFillStyleSize[sizeof(VecFillStyle)==0x80?1:-1];
struct VecStyleChange {
    u8 flags;u8 reserved[3];s32 x,y;
    u8 left,right,line,padding;
    void* lineStyles;void* fillStyles;
};
struct VecCurve {s32 controlX,controlY,endX,endY;};
extern "C" {
void flcalcMulMatrixf(FLASHMATRIXF*,FLASHMATRIXF*,FLASHMATRIXF*);
void flcalcBezier3(GSvec2*,GSvec2*,f32);
f64 acos(f64);
f64 sin(f64);
f64 cos(f64);
}
static inline void vecBounds(const GSvec2* point) {
    VEC_GRAPH_DATA* data=(VEC_GRAPH_DATA*)gVecDat;
    s16 x=(s16)point->x,y=(s16)point->y;
    if(x<data->minX)data->minX=x;
    if(x>data->maxX)data->maxX=x;
    if(y<data->minY)data->minY=y;
    if(y>data->maxY)data->maxY=y;
}
static void vecExec(u32 id,_FILLSTYLEARRAY* fills,_LINESTYLEARRAY* lines,_SHAPERECORD* shape,FLASHMATRIXF* matrix,FLASHMATRIXF* parent,FLASHCXFORM* colors) {
    FLASHMATRIXF combined;
    GSvec2 oldPoint,newPoint,control,local;
    GSvec2 curve[3],previous,current;
    s32 x=0,y=0;
    u8 sprite=0,more=1;
    if(fills->count==0 && fills->styles)((VecFillStyle*)fills->styles)->color=0xffffffff;
    if(matrix)flcalcMulMatrixf(&combined,parent,matrix);
    else for(s32 component=0;component<6;++component)combined.m[component]=parent->m[component];
    VEC_GRAPH_DATA* data=(VEC_GRAPH_DATA*)gVecDat;
    do {
        switch(shape->type) {
        case 0:more=0;break;
        case 1: {
            VecStyleChange* change=(VecStyleChange*)shape->move;
            sprite=0;
            if(change->flags&1) {
                x=change->x;y=change->y;
                local.x=(f32)x/20.0f;local.y=(f32)y/20.0f;
                flcalcMatrix(&oldPoint,&combined,&local);
            }
            if(change->flags&4) {
                if(change->right) {data->shiftRight=change->right-1;data->fillRight=1;}
                else data->fillRight=0;
            }
            if(change->flags&2) {
                if(change->left) {data->shiftLeft=change->left-1;data->fillLeft=1;}
                else data->fillLeft=0;
            }
            if(change->flags&8) {
                if(data->fillLeft) {data->previousLeft=change->line;if(change->line && !(change->flags&6))sprite=1;}
                if(data->fillRight) {data->previousRight=change->line;if(change->line && !(change->flags&6))sprite=1;}
            }
            if((change->flags&16) && change->fillStyles) {
                SBscan();
                data->minY=0x7fff;data->minX=0x7fff;data->maxY=-0x8000;data->maxX=-0x8000;
                memset(scanline_buffer,0,sizeof(scanline_buffer));
                data->fillStyles=change->fillStyles;
                data->shiftRight=0;data->shiftLeft=0;data->fillRight=0;data->fillLeft=0;
                if(!(change->flags&4)){data->shiftRight=0;data->fillRight=0;}
                if(!(change->flags&2)){data->shiftLeft=0;data->fillLeft=0;}
            }else {
                for(s32 side=0;side<2;++side) {
                    s32* active=&data->fillLeft+side;
                    if(*active) {
                        s32 style=active[2];
                        VecFillStyle* fill=&((VecFillStyle*)data->fillStyles)[style];
                        if(fill->type&0x40) {
                            if(!(change->flags&1)){y=0;x=0;}
                            sprite=1;
                            shape=SpriteCode(id,shape->next,fill->texture,&combined,&fill->textureMatrix,x,y,data,colors);
                        }
                    }
                }
            }
            break;
        }
        case 2:
            x+=shape->move->x;y+=shape->move->y;
            local.x=(f32)x/20.0f;local.y=(f32)y/20.0f;
            if(!sprite) {
                flcalcMatrix(&newPoint,&combined,&local);
                SBline(&oldPoint,&newPoint);
                vecBounds(&newPoint);
                oldPoint=newPoint;
            }
            break;
        case 3: {
            VecCurve* edge=(VecCurve*)shape->move;
            s32 controlX=x+edge->controlX,controlY=y+edge->controlY;
            local.x=(f32)controlX/20.0f;local.y=(f32)controlY/20.0f;
            flcalcMatrix(&control,&combined,&local);
            x=controlX+edge->endX;y=controlY+edge->endY;
            local.x=(f32)x/20.0f;local.y=(f32)y/20.0f;
            if(!sprite) {
                flcalcMatrix(&newPoint,&combined,&local);
                curve[1]=control;
                if(oldPoint.y<newPoint.y){curve[0]=oldPoint;curve[2]=newPoint;}
                else {curve[0]=newPoint;curve[2]=oldPoint;}
                previous=curve[0];
                f32 fraction=0;
                for(s32 i=0;i<9;++i) {
                    fraction+=0.1f;
                    flcalcBezier3(&current,curve,fraction);
                    SBline(&previous,&current);
                    previous=current;
                    vecBounds(&current);
                }
                current=curve[2];
                SBline(&previous,&current);
                vecBounds(&current);
                oldPoint=newPoint;
            }
            break;
        }
        default:printf("error flash record!\n");break;
        }
        shape=shape->next;
        if(!shape->next)more=0;
    }while(more);
    if(!sprite)SBscan();
}

static void calcVecRect(VEC_RECT* rect,VEC_GRAPH_DATA* data,long style) {
    data->centerX=(data->maxX+data->minX)/2;
    data->centerY=(data->maxY+data->minY)/2;
    data->width=data->maxX-data->minX;
    data->height=data->maxY-data->minY;
    if(data->fillStyles) {
        VecFillStyle* fill=&((VecFillStyle*)data->fillStyles)[style];
        if(style) {
            switch(fill->type) {
            case 0:data->color=flcalcMultiTransformColor(data->colorTransform,fill->color);data->gradient=0;return;
            case 16: {
                    data->gradient=&fill->gradient;
                    if(data->scale==0.0f)data->scale=1.0f;
                    for(s16 i=0;i<((VecGradient*)data->gradient)->count;++i) {
                        f32 distance=(f32)(((VecGradient*)data->gradient)->stops[i].ratio-128);
                        getCrossPoint(i,data->originX+(s16)(distance*data->scale+128.0f),-256,512,data->originX+128,128,data);
                    }

                    u32 oldColor;
                    memcpy(&oldColor,&((VecGradient*)data->gradient)->stops[0].color,4);
                    s32 position=0;
                    for(s32 stop=0;stop<((VecGradient*)data->gradient)->count;++stop) {
                        s32 length=((VecGradient*)data->gradient)->stops[stop].ratio-position;
                        if(length!=0) {
                            u8* previous=(u8*)&oldColor;
                            u8* next=(u8*)&((VecGradient*)data->gradient)->stops[stop].color;
                            f32 n0=__OSu8tof32(&next[0]);
                            f32 n1=__OSu8tof32(&next[1]);
                            f32 n2=__OSu8tof32(&next[2]);
                            f32 n3=__OSu8tof32(&next[3]);
                            f32 d0=(n0-(f32)previous[0])/(f32)length;
                            f32 d1=(n1-(f32)previous[1])/(f32)length;
                            f32 d2=(n2-(f32)previous[2])/(f32)length;
                            f32 d3=(n3-(f32)previous[3])/(f32)length;
                            for(s32 i=0;i<length;++i) {
                                u8 components[4];
                                components[0]=(u8)(s32)(d0*(f32)i+(f32)previous[0]);
                                components[1]=(u8)(s32)(d1*(f32)i+(f32)previous[1]);
                                components[2]=(u8)(s32)(d2*(f32)i+(f32)previous[2]);
                                components[3]=(u8)(s32)(d3*(f32)i+(f32)previous[3]);
                                u32 interpolated=((u32)components[0]<<24)|((u32)components[1]<<16)|((u32)components[2]<<8)|components[3];
                                ((u32*)data->reserved64)[position+i]=flcalcMultiTransformColor(data->colorTransform,interpolated);
                            }
                        }
                        memcpy(&oldColor,&((VecGradient*)data->gradient)->stops[stop].color,4);
                        position+=length;
                    }
                    memcpy(&oldColor,&((u32*)data->reserved64)[position-1],4);
                    for(;position<256;++position)memcpy(&((u32*)data->reserved64)[position],&oldColor,4);

                    return;
                }
            }
            return;
        }
        f32 first=(f32)fill->matrix.m[0];
        f32 second=(f32)fill->matrix.m[1];
        data->originX=fill->matrix.m[4]/20-data->centerX;
        data->originY=((VecFillStyle*)data->fillStyles)[style].matrix.m[5]/20-data->centerY;
        f32 magnitude=vecSqrt(first*first+second*second);
        data->angle=(f32)acos((f32)first/magnitude);
        if(second<0.0f)data->angle=-data->angle;
        if(data->width-1)data->scale=(1638.4f*(magnitude/65536.0f))/(f32)(data->width-1);
        else data->scale=1638.4f*(magnitude/65536.0f);
        data->sinAngle=(f32)sin(data->angle);data->cosAngle=(f32)cos(data->angle);
        data->inverseSin=(f32)sin(-data->angle);data->inverseCos=(f32)cos(-data->angle);
        switch(fill->type) {
        case 0:data->color=flcalcMultiTransformColor(data->colorTransform,fill->color);data->gradient=0;break;
        case 16: {
                data->gradient=&fill->gradient;
                if(data->scale==0.0f)data->scale=1.0f;
                for(s16 i=0;i<((VecGradient*)data->gradient)->count;++i) {
                    f32 distance=(f32)(((VecGradient*)data->gradient)->stops[i].ratio-128);
                    getCrossPoint(i,data->originX+(s16)(distance*data->scale+128.0f),-256,512,data->originX+128,128,data);
                }

                u32 oldColor;
                memcpy(&oldColor,&((VecGradient*)data->gradient)->stops[0].color,4);
                s32 position=0;
                for(s32 stop=0;stop<((VecGradient*)data->gradient)->count;++stop) {
                    s32 length=((VecGradient*)data->gradient)->stops[stop].ratio-position;
                    if(length!=0) {
                        u8* previous=(u8*)&oldColor;
                        u8* next=(u8*)&((VecGradient*)data->gradient)->stops[stop].color;
                        f32 n0=__OSu8tof32(&next[0]);
                        f32 n1=__OSu8tof32(&next[1]);
                        f32 n2=__OSu8tof32(&next[2]);
                        f32 n3=__OSu8tof32(&next[3]);
                        f32 d0=(n0-(f32)previous[0])/(f32)length;
                        f32 d1=(n1-(f32)previous[1])/(f32)length;
                        f32 d2=(n2-(f32)previous[2])/(f32)length;
                        f32 d3=(n3-(f32)previous[3])/(f32)length;
                        for(s32 i=0;i<length;++i) {
                            u8 components[4];
                            components[0]=(u8)(s32)(d0*(f32)i+(f32)previous[0]);
                            components[1]=(u8)(s32)(d1*(f32)i+(f32)previous[1]);
                            components[2]=(u8)(s32)(d2*(f32)i+(f32)previous[2]);
                            components[3]=(u8)(s32)(d3*(f32)i+(f32)previous[3]);
                            u32 interpolated=((u32)components[0]<<24)|((u32)components[1]<<16)|((u32)components[2]<<8)|components[3];
                            ((u32*)data->reserved64)[position+i]=flcalcMultiTransformColor(data->colorTransform,interpolated);
                        }
                    }
                    memcpy(&oldColor,&((VecGradient*)data->gradient)->stops[stop].color,4);
                    position+=length;
                }
                memcpy(&oldColor,&((u32*)data->reserved64)[position-1],4);
                for(;position<256;++position)memcpy(&((u32*)data->reserved64)[position],&oldColor,4);

                break;
            }
        }
    }else {
        data->originY=0;data->originX=0;data->scale=0.0f;data->angle=0.0f;
        data->sinAngle=(f32)sin(data->angle);data->cosAngle=(f32)cos(data->angle);
        data->inverseSin=(f32)sin(-data->angle);data->inverseCos=(f32)cos(-data->angle);
    }
    rect->y0=data->minY<0?0:data->minY;
    rect->y1=data->maxY>=480?479:data->maxY;
    rect->x0=data->minX<0?0:data->minX;
    rect->x1=data->maxX>=640?639:data->maxX;
}
static inline s16 vecGradientIndex(s16 x,s16 y,VEC_GRAPH_DATA* data) {
    s32 vertical=data->originY+((y-data->minY)*256)/data->height;
    s32 horizontal=((x-data->minX)*256)/data->width-data->originX;
    s16 index=(s16)(128.0f+(((f32)horizontal-128.0f)*data->inverseCos-((f32)vertical-128.0f)*data->inverseSin)/data->scale);
    if(index<0)index=0;
    if(index>=256)index=255;
    return index;
}
static void gradientline(s16 left,s16 right,s16 y,VEC_GRAPH_DATA* data) {
    s16 points[8];
    s32 count=0;
    VecGradient* gradient=(VecGradient*)data->gradient;
    for(s32 i=0;i<gradient->count;++i) {
        s16 x=data->minX+(data->crossPoints[((y-data->minY)*256)/data->height][i]*data->width)/256;
        if(left<x && right>x)points[count++]=x;
    }
    for(s32 i=0;i<count-1;++i)for(s32 j=i+1;j<count;++j)if(points[i]>points[j]) {s16 temp=points[i];points[i]=points[j];points[j]=temp;}
    u32* palette=(u32*)data->reserved64;
    vecLineVertex(left,y,palette[vecGradientIndex(left,y,data)]);
    for(s32 i=0;i<count;++i) {
        u32 color=palette[vecGradientIndex(points[i],y,data)];
        vecLineVertex(points[i],y,color);
        vecLineVertex(points[i],y,color);
    }
    vecLineVertex(right,y,palette[vecGradientIndex(right,y,data)]);
}
