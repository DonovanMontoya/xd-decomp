#include <game/pxdvs/app/fade/fadeFluidPrivate.hpp>

static FluidWork _fadeFluidWork;
static s32 _fadeFluidSw;
static void _fadeFluidDoFree(void *);
static void *_fadeFluidDoMalloc(unsigned long);
static void _fadeFluidSetShockSub(unsigned long,unsigned long,f32);

extern "C" f32 __float_nan[];
static inline f32 FluidSqrt(f32 x) {
    if (x > 0.0f) {
        f64 guess=__frsqrte((f64)x);
        guess=0.5*guess*(3.0-guess*guess*x);
        guess=0.5*guess*(3.0-guess*guess*x);
        guess=0.5*guess*(3.0-guess*guess*x);
        return (f32)(x*guess);
    } else if (x < 0.0) return __float_nan[0];
    else {
        union {f32 f;u32 u;} value;
        value.f=x;
        s32 category;
        switch ((s32)(value.u & 0x7F800000)) {
        case 0x7F800000:category=(s32)(value.u & 0x7FFFFF)!=0?1:2;break;
        case 0:category=(s32)(value.u & 0x7FFFFF)!=0?5:3;break;
        default:category=4;break;
        }
        if (category == 1) return __float_nan[0];
    }
    return x;
}

static inline void FluidSetVector(FluidVec& value,f32 x,f32 y,f32 z) {value.x=x;value.y=y;value.z=z;}
static inline void FluidTexCoord(f32 u,f32 v) { *(volatile f32*)0xCC008000=u; *(volatile f32*)0xCC008000=v; }
static inline void FluidVertex(FluidVec *vertex,FluidUV *uv,f32 sx,f32 sy,u8 alpha) {
    FluidVec value;
    FluidSetVector(value,vertex->x,vertex->y,vertex->z);
    value.x*=sx; value.y*=sy; value.z*=sx;
    *(volatile f32 *)0xCC008000=value.x;
    *(volatile f32 *)0xCC008000=value.y;
    *(volatile f32 *)0xCC008000=value.z;
    *(volatile u8 *)0xCC008000=255;
    *(volatile u8 *)0xCC008000=255;
    *(volatile u8 *)0xCC008000=255;
    *(volatile u8 *)0xCC008000=alpha;
    FluidTexCoord(uv->u,uv->v);
}

extern "C" void fadeFluidDispSecond(s32 layerId,GStexture *texture,f32 fade,f32 progress) {
    FluidVec **slot;
    FluidUV *uv;
    s32 rowA,rowB,i,j;
    u32 x;
    u32 count;
    s32 alpha;
    u32 y;
    GSgfxLayer *layer;
    u32 stride;
    f32 value,sx,sy;


    layer=GSgfxLayerFindByID(layerId);
    FluidVec color;
    FluidVec from;
    FluidVec to;
    from.x=1.0f;from.y=1.0f;from.z=1.0f;
    to.x=0.0f;to.y=0.0f;to.z=0.0f;
    GSlerpGetLinearInterpolationVector(&color,&from,&to,progress);
    value=(f32)(s32)(255.0f*color.x);
    alpha=(s32)(value*(1.0f-fade));
    spriteSetEnv(layerId);
    if (layer->shaderIndex != 1) {
        layer->shaderIndex=1;
        layer->shader=layer->shaders[layer->shaderIndex];
    }
    layer->field1644=1;layer->field1648=4;layer->field164C=5;layer->field1650=5;
    layer->field170C|=1;layer->field16A8|=0x40;layer->field17C4|=1;layer->field1760|=0x40;
    layer->field1656=1;layer->field1657=1;layer->field1658=0;
    layer->field170C|=4;layer->field16A8|=0x40;layer->field17C4|=4;layer->field1760|=0x40;
    layer->field165C=0;layer->field1660=1;
    layer->field170C|=8;layer->field16A8|=0x40;layer->field17C4|=8;layer->field1760|=0x40;
    layer->field1664=7;layer->field1670=0;layer->field1668=0;layer->field166C=7;layer->field1671=0;layer->field1672=1;
    layer->field170C|=16;layer->field16A8|=0x40;layer->field17C4|=16;layer->field1760|=0x40;
    layer->fieldD8C=0;
    layer->field16B8|=2;layer->field16A8|=2;layer->field1770|=2;layer->field1760|=2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1,4,0,0,1,5,1,1,4));
    if (layer->texture0 != texture || layer->texture1 != texture || texture->dirty != 0) {
        layer->texture0=texture;layer->field173C|=1;
        layer->texture1=texture;layer->field17F4|=1;
    }
    sx=_fadeFluidWork.screenX;sy=_fadeFluidWork.screenY;
    stride=_fadeFluidWork.width+1;
    count=stride*2;
    for (y=0;y<_fadeFluidWork.height;++y) {
        layer->primitive=0x98;
        layer->beginSurface(count);
        slot=&_fadeFluidWork.vertices[_fadeFluidSw];
        uv=_fadeFluidWork.uv;
        rowA=(s32)y*(s32)stride;rowB=((s32)y+1)*(s32)stride;
        for (x=0;x<stride;++x) {
            i=(s32)x+rowA;j=(s32)x+rowB;
            FluidVertex(&(*slot)[i],&uv[i],sx,sy,alpha);
            FluidVertex(&(*slot)[j],&uv[j],sx,sy,alpha);
        }
        layer->endSurface();
    }
}
extern "C" void fadeFluidDisp(GStexture *texture,f32 fade,f32 progress) {
    FluidVec **slot;
    FluidUV *uv;
    s32 rowA,rowB,i,j;
    u32 x;
    u32 count;
    s32 alpha;
    u32 y;
    GSgfxLayer *layer;
    u32 stride;
    f32 value,sx,sy;


    layer=GSgfxLayerFindByID(7);
    FluidVec color;
    FluidVec from;
    FluidVec to;
    from.x=1.0f;from.y=1.0f;from.z=1.0f;
    to.x=0.0f;to.y=0.0f;to.z=0.0f;
    GSlerpGetLinearInterpolationVector(&color,&from,&to,progress);
    value=(f32)(s32)(255.0f*color.x);
    alpha=(s32)(value*(1.0f-fade));
    spriteSetEnv(7);
    if (layer->shaderIndex != 1) {
        layer->shaderIndex=1;
        layer->shader=layer->shaders[layer->shaderIndex];
    }
    layer->field1644=1;layer->field1648=4;layer->field164C=5;layer->field1650=5;
    layer->field170C|=1;layer->field16A8|=0x40;layer->field17C4|=1;layer->field1760|=0x40;
    layer->field1656=1;layer->field1657=1;layer->field1658=0;
    layer->field170C|=4;layer->field16A8|=0x40;layer->field17C4|=4;layer->field1760|=0x40;
    layer->field165C=0;layer->field1660=1;
    layer->field170C|=8;layer->field16A8|=0x40;layer->field17C4|=8;layer->field1760|=0x40;
    layer->field1664=7;layer->field1670=0;layer->field1668=0;layer->field166C=7;layer->field1671=0;layer->field1672=1;
    layer->field170C|=16;layer->field16A8|=0x40;layer->field17C4|=16;layer->field1760|=0x40;
    layer->fieldD8C=0;
    layer->field16B8|=2;layer->field16A8|=2;layer->field1770|=2;layer->field1760|=2;
    layer->setRenderStateAndSelect(GSgfxVFBuildTemp(1,4,0,0,1,5,1,1,4));
    if (layer->texture0 != texture || layer->texture1 != texture || texture->dirty != 0) {
        layer->texture0=texture;layer->field173C|=1;
        layer->texture1=texture;layer->field17F4|=1;
    }
    layer->primitive=0x98;
    sx=_fadeFluidWork.screenX;sy=_fadeFluidWork.screenY;
    stride=_fadeFluidWork.width+1;
    count=stride*2;
    for (y=0;y<_fadeFluidWork.height;++y) {
        layer->beginSurface(count);
        slot=&_fadeFluidWork.vertices[_fadeFluidSw];
        uv=_fadeFluidWork.uv;
        rowA=(s32)y*(s32)stride;rowB=((s32)y+1)*(s32)stride;
        for (x=0;x<stride;++x) {
            i=(s32)x+rowA;j=(s32)x+rowB;
            FluidVertex(&(*slot)[i],&uv[i],sx,sy,alpha);
            FluidVertex(&(*slot)[j],&uv[j],sx,sy,alpha);
        }
        layer->endSurface();
    }
}
extern "C" void fadeFluidSetShockSecond(FluidVec *point,f32 strength) {
    f32 spacing=_fadeFluidWork.spacing;
    u32 x=(u32)(point->x/spacing),y=(u32)(point->y/spacing);
    _fadeFluidSetShockSub(x,y,strength);
    f32 diagonal=0.25f*strength,adjacent=0.5f*strength;
    _fadeFluidSetShockSub(x-1,y-1,diagonal);
    _fadeFluidSetShockSub(x,y-1,adjacent);
    _fadeFluidSetShockSub(x+1,y-1,diagonal);
    _fadeFluidSetShockSub(x-1,y,adjacent);
    _fadeFluidSetShockSub(x+1,y,adjacent);
    _fadeFluidSetShockSub(x-1,y+1,diagonal);
    _fadeFluidSetShockSub(x,y+1,adjacent);
    _fadeFluidSetShockSub(x+1,y+1,diagonal);
}
extern "C" void fadeFluidEvaluateSecond() {
    FluidVec *current,*next,*row;
    u32 stride,x,y;
    f32 a=_fadeFluidWork.a,b=_fadeFluidWork.b,c=_fadeFluidWork.c;
    stride=_fadeFluidWork.width+1;
    for (y=1;y<_fadeFluidWork.height;++y) {
        s32 rowOffset=(s32)y*(s32)stride;
        row=&_fadeFluidWork.vertices[_fadeFluidSw][rowOffset];
        current=row+1;
        next=&_fadeFluidWork.vertices[1-_fadeFluidSw][rowOffset]+1;
        for (x=1;x<_fadeFluidWork.width;++x,++current,++next) {
            f32 sides=current[1].z+current[-1].z;
            next->z=c*(row[(s32)x-(s32)stride].z+(sides+row[x+stride].z))+
                (a*current->z+b*next->z);
        }
    }
    _fadeFluidSw=1-_fadeFluidSw;
}
extern "C" void fadeFluidSetShock(FluidVec *point,f32 strength) {
    f32 spacing=_fadeFluidWork.spacing;
    u32 x=(u32)(point->x/spacing),y=(u32)(point->y/spacing);
    _fadeFluidSetShockSub(x,y,strength);
    strength=strength/2.0f;
    _fadeFluidSetShockSub(x-1,y-1,strength);
    _fadeFluidSetShockSub(x,y-1,strength);
    _fadeFluidSetShockSub(x+1,y-1,strength);
    _fadeFluidSetShockSub(x-1,y,strength);
    _fadeFluidSetShockSub(x+1,y,strength);
    _fadeFluidSetShockSub(x-1,y+1,strength);
    _fadeFluidSetShockSub(x,y+1,strength);
    _fadeFluidSetShockSub(x+1,y+1,strength);
}
#pragma opt_dead_assignments off
static void _fadeFluidSetShockSub(unsigned long x,unsigned long y,f32 strength) {
    if (x<=_fadeFluidWork.width && y<=_fadeFluidWork.height) {
        u8 *base=(u8 *)_fadeFluidWork.vertices[_fadeFluidSw];
        f32 *value=(f32 *)(base+(x+y*(_fadeFluidWork.width+1))*12+8);
        *value-=strength;
    }
}
#pragma opt_dead_assignments reset
extern "C" void fadeFluidEvaluate() {
    FluidVec *current,*next,*row;
    FluidVec *current2,*normal2,*tangent2,*row2;
    u32 stride,x,y;
    f32 a=_fadeFluidWork.a,b=_fadeFluidWork.b,c=_fadeFluidWork.c;
    stride=_fadeFluidWork.width+1;
    for (y=1;y<_fadeFluidWork.height;++y) {
        s32 rowOffset=(s32)y*(s32)stride;
        row=&_fadeFluidWork.vertices[_fadeFluidSw][rowOffset];
        current=row+1;
        next=&_fadeFluidWork.vertices[1-_fadeFluidSw][rowOffset]+1;
        for (x=1;x<_fadeFluidWork.width;++x,++current,++next) {
            f32 sides=current[1].z+current[-1].z;
            next->z=c*(row[(s32)x-(s32)stride].z+(sides+row[x+stride].z))+
                (a*current->z+b*next->z);
        }
    }
    _fadeFluidSw=1-_fadeFluidSw;
    for (y=1;y<_fadeFluidWork.height;++y) {
        s32 rowOffset=(s32)y*(s32)stride;
        row2=&_fadeFluidWork.vertices[_fadeFluidSw][rowOffset];
        current2=row2+1;
        normal2=&_fadeFluidWork.normal[rowOffset]+1;
        tangent2=&_fadeFluidWork.tangent[rowOffset]+1;
        for (x=1;x<_fadeFluidWork.width;++x,++current2,++normal2,++tangent2) {
            normal2->x=current2[-1].z-current2[1].z;
            normal2->y=row2[(s32)x-(s32)stride].z-row2[x+stride].z;
            tangent2->z=current2[1].z-current2[-1].z;
        }
    }
}
extern "C" void fadeFluidCalcParms(f32 delta) {
    f32 speed;
    f32 ratio;
    f32 spacing;
    f32 inverse;
    f32 damping;
    speed=_fadeFluidWork.speed;
    spacing=_fadeFluidWork.spacing;
    damping=_fadeFluidWork.damping*delta;
    ratio=(delta*(delta*(speed*speed)))/(spacing*spacing);
    inverse=1.0f/(2.0f+damping);
    _fadeFluidWork.a=-((8.0f*ratio)-4.0f)*inverse;
    _fadeFluidWork.b=inverse*(damping-2.0f);
    _fadeFluidWork.c=2.0f*ratio*inverse;
}

extern "C" void fadeFluidQuit() {
    if (_fadeFluidWork.vertices[0]!=0) _fadeFluidDoFree(_fadeFluidWork.vertices[0]);
    if (_fadeFluidWork.vertices[1]!=0) _fadeFluidDoFree(_fadeFluidWork.vertices[1]);
    if (_fadeFluidWork.normal!=0) _fadeFluidDoFree(_fadeFluidWork.normal);
    if (_fadeFluidWork.tangent!=0) _fadeFluidDoFree(_fadeFluidWork.tangent);
    if (_fadeFluidWork.uv!=0) _fadeFluidDoFree(_fadeFluidWork.uv);
    _fadeFluidWork.vertices[0]=0;_fadeFluidWork.vertices[1]=0;
    _fadeFluidWork.normal=0;_fadeFluidWork.tangent=0;_fadeFluidWork.uv=0;
}
extern "C" void fadeFluidInit(u32 width,u32 height,f32 spacing,f32 delta,f32 speed,f32 damping) {
    FluidVec *vertex,*copy,*normal,*tangent;
    s32 x,y;
    f32 twiceSpacing,vertexY,textureV;
    f32 inverseU,inverseV;
    u32 i;
    u32 count=(width+1)*(height+1);
    u32 bytes=count*sizeof(FluidVec);
    _fadeFluidWork.width=width;_fadeFluidWork.height=height;
    _fadeFluidWork.screenX=640.0f/(f32)width;
    _fadeFluidWork.screenY=480.0f/(f32)height;
    _fadeFluidWork.vertices[0]=(FluidVec *)_fadeFluidDoMalloc(bytes);
    _fadeFluidWork.vertices[1]=(FluidVec *)_fadeFluidDoMalloc(bytes);
    _fadeFluidSw=0;
    _fadeFluidWork.normal=(FluidVec *)_fadeFluidDoMalloc(bytes);
    _fadeFluidWork.tangent=(FluidVec *)_fadeFluidDoMalloc(bytes);
    _fadeFluidWork.uv=(FluidUV *)_fadeFluidDoMalloc(count*sizeof(FluidUV));
    f32 limit=(spacing/(2.0f*delta))*FluidSqrt(2.0f+damping);
    if (!(0.0f<speed && speed<limit)) {
        OSReport("Warning: fadeFluid c parm. Limit Over!! -> 0.0f < %f < %f\n",speed,limit);
        speed=limit-0.000001f;
    }
    _fadeFluidWork.spacing=spacing;_fadeFluidWork.speed=speed;_fadeFluidWork.damping=damping;
    fadeFluidCalcParms(delta);
    twiceSpacing=2.0f*spacing;
    inverseU=1.0f/(f32)_fadeFluidWork.width;
    inverseV=1.0f/(f32)_fadeFluidWork.height;
    i=0;
    for (y=0;y<=height;++y) {
        vertexY=spacing*(f32)y;
        textureV=inverseV*(f32)y;
        for (x=0;x<=width;++i,++x) {
            vertex=&_fadeFluidWork.vertices[0][i];
            vertex->x=spacing*(f32)x;vertex->y=vertexY;vertex->z=0.0f;
            copy=&_fadeFluidWork.vertices[1][i];
            vertex=&_fadeFluidWork.vertices[0][i];
            copy->x=vertex->x;copy->y=vertex->y;copy->z=vertex->z;
            normal=&_fadeFluidWork.normal[i];
            normal->x=0.0f;normal->y=0.0f;normal->z=twiceSpacing;
            tangent=&_fadeFluidWork.tangent[i];
            tangent->x=twiceSpacing;tangent->y=0.0f;tangent->z=0.0f;
            _fadeFluidWork.uv[i].u=inverseU*(f32)x;
            _fadeFluidWork.uv[i].v=textureV;
        }
    }
}
static void _fadeFluidDoFree(void *data) {GSmemFree(data);}
static void *_fadeFluidDoMalloc(unsigned long size) {
    void *result;
    s32 previous=GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(),3);
    result=GSmemAllocAlign(size,32);
    GSmemSetAllocMethodHeap(GSmemGetCurrentHeap(),previous);
    return result;
}
