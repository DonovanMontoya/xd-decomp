#include <game/pxdvs/GSAPI/GSshape/shapeObjectPrivate.hpp>
#include <dolphin/gx.h>
u32 GsShapeObject::GetPolygonCount() { return entry->segmentsU*entry->segmentsV*2; }
bool GsShapeObject::FreeShapeDrawBuffer(s16 instance) {
    if(instance<0 || instance>=256) return false;
    if(drawBuffers[instance]) { GSmemFree(drawBuffers[instance]); drawBuffers[instance]=0; return true; }
    return false;
}
bool GsShapeObject::CreateShapeDrawBuffer(s16 instance) {
    if(instance<0 || instance>=256) return false;
    drawBuffers[instance]=(u8*)GSmemAlloc(entry->vertexCount*(entry->textureCount*8+16)*2);
    if(!drawBuffers[instance]) return false;
    u32 count=entry->vertexCount;
    int texture;
    for(int buffer=0;buffer<2;buffer++) {
        u32 offset=0;
        if(buffer!=0) offset=count*(entry->textureCount*8+16);
        u8* vertices=drawBuffers[instance]+offset;
        memcpy(vertices,entry->vertices,count*12);
        u8* colors=vertices+count*12;
        memcpy(colors,entry->colors,count*4);
        for(texture=0;texture<entry->textureCount;texture++)
            memcpy(colors+count*(texture*8u+4),entry->textureCoords,count*8);
    }
    return true;
}
void GsShapeObject::FreeDisplayListShape() {
    if(displayList) { GSgfxDLFree(displayList); GSmemFree(displayList); displayList=0; }
}
void GsShapeObject::SetVertexColorSpecify(const tagGScol4ub& value,bool) {
    tagGScol4ub* colors=(tagGScol4ub*)vertexArrays[1];
    if(colors) {
        int column;
        int row;
        int columns;
        int rows;
        tagGScol4ub* out;
        columns=entry->segmentsU+1;
        rows=entry->segmentsV+1;
        out=colors;
        for(row=0;row<rows;row++) {
            for(column=0;column<columns;column++) {
                out->r=value.r; out->g=value.g; out->b=value.b; out->a=value.a;
                out++;
            }
        }
    }
}
void GsShapeObject::SetVertexColorAlpha(int mode,int shape,f32 alpha,bool) {
    void* array=vertexArrays[1];
    if(!array) return;
    int column;
    int row;
    int columns;
    int rows;
    const tagGScol4ub* colors;
    tagGScol4ub* out;
    columns=entry->segmentsU+1;
    rows=entry->segmentsV+1;
    colors=entry->colors;
    out=(tagGScol4ub*)array;
    if(mode==0) {
        if(shape!=5) {
            u8 value=255.0f*alpha;
            for(row=0;row<rows;row++) {
                for(column=0;column<columns;column++) {
                    out->r=colors->r; out->g=colors->g; out->b=colors->b; out->a=value;
                    colors++; out++;
                }
            }
            return;
        }
        for(row=0;row<rows;row++) {
            for(column=0;column<columns;column++) {
                out->r=colors->r*alpha; out->g=colors->g*alpha; out->b=colors->b*alpha; out->a=255;
                colors++; out++;
            }
        }
        return;
    }
    if(shape!=5) {
        for(row=0;row<rows;row++) {
            for(column=0;column<columns;column++) {
                out->r=colors->r; out->g=colors->g; out->b=colors->b; out->a=colors->a*alpha;
                colors++; out++;
            }
        }
        return;
    }
    for(row=0;row<rows;row++) {
        for(column=0;column<columns;column++) {
            u8 value=colors->a;
            f32 factor=(value/255.0f)*alpha;
            out->r=colors->r*factor; out->g=colors->g*factor; out->b=colors->b*factor; out->a=value;
            colors++; out++;
        }
    }
}
void GsShapeObject::SetVertexColorGradation(u8 axis,const tagGScol4ub* colors,int shape,f32 alpha,bool) {
    void* array=vertexArrays[1];
    if(!array) return;
    tagGScol4ub* out=(tagGScol4ub*)array;
    int columns=entry->segmentsU+1,rows=entry->segmentsV+1;
    if(shape==2 || shape==4) {
        for(int row=0;row<rows;row++) {
            const tagGScol4ub* columnColor=colors;
            for(int column=0;column<columns;column++,columnColor++,out++) {
                if(axis==0) { out->r=columnColor->r; out->g=columnColor->g; out->b=columnColor->b; out->a=alpha*columnColor->a; }
                else { out->r=colors[row].r; out->g=colors[row].g; out->b=colors[row].b; out->a=alpha*colors[row].a; }
            }
        }
        return;
    }
    for(int row=0;row<rows;row++) {
        const tagGScol4ub* columnColor=colors;
        for(int column=0;column<columns;column++,columnColor++,out++) {
            if(axis==0) {
                out->r=alpha*(columnColor->r*(columnColor->a/255.0f));
                out->g=alpha*(columnColor->g*(columnColor->a/255.0f));
                out->b=alpha*(columnColor->b*(columnColor->a/255.0f)); out->a=columnColor->a;
            } else {
                out->r=alpha*(colors[row].r*(colors[row].a/255.0f));
                out->g=alpha*(colors[row].g*(colors[row].a/255.0f));
                out->b=alpha*(colors[row].b*(colors[row].a/255.0f)); out->a=colors[row].a;
            }
        }
    }
}

extern "C" {
void GSgfxDLBegin(void*, void*, u32, u32);
void GSgfxDLEnd();
void GSgfxDLPrimitiveType(u32);
void GSgfxDLBeginSurface(u16);
void GSgfxDLEndSurface();
}
void GsShapeObject::MakeShapeGfxDL() {
    u32 vertexCount;
    u16 row;
    u16 base;
    u16 textureCount;
    u16 columns;
    columns = entry->segmentsU + 1;
    textureCount = entry->textureCount;
    GSgfxDLPrimitiveType(0x98);
    vertexCount = columns * 2;
    for (row = 0; row < entry->segmentsV; ++row) {
        u16 column;
        base = row * columns;
        GSgfxDLBeginSurface(vertexCount);
        u16 next = (row + 1) * columns;
        for (column = 0; column < columns; ++column) {
            u16 first = column + base;
            u16 second = column + next;
            u16 i;
            GXWGFifo.u16 = first;
            GXWGFifo.u16 = first;
            for (i = 0; i < textureCount; ++i) GXWGFifo.u16 = first;
            GXWGFifo.u16 = second;
            GXWGFifo.u16 = second;
            for (i = 0; i < textureCount; ++i) GXWGFifo.u16 = second;
        }
        GSgfxDLEndSurface();
    }
}
void GsShapeObject::MakeDisplayListShape() {
    displayList=GSmemAlloc(16);
    if(displayList) {
s32 rows=entry->segmentsV;
        u32 columns=entry->segmentsU+1;
        u16 indices=rows*(columns*2);
        memset(displayList,0,16);
        GSgfxDLBegin(displayList,vertexFormat,rows,indices);
        MakeShapeGfxDL();
        GSgfxDLEnd();
    }
}
bool GsShapeObject::DeformTextureCoord(u32 texture,bool deform,const f32* u,const f32* v,bool twistEnabled,const f32* twist) {
    int row; int column; int columns; f32 offset; int rows; const GsShapePair* original; GsShapePair* out;
    if(!vertexArrays[texture+2]) return false;
    out=(GsShapePair*)vertexArrays[texture+2];
    original=entry->textureCoords;
    columns=entry->segmentsU+1;
    rows=entry->segmentsV+1;
    offset=0.0f;
    for(row=0;row<rows;row++) {
        if(twistEnabled==1) offset=*twist;
        if(deform==1) {
            for(column=0;column<columns;column++) {
                out->u=offset+u[column]; out->v=*v; out++;
            }
        } else {
            for(column=0;column<columns;column++) {
                out->u=original->u+offset; out->v=original->v; out++; original++;
            }
        }
        twist++; v++;
    }
    return true;
}
extern "C" double sin(double);
extern "C" double cos(double);
#include <libc/math.h>
extern "C" double tan(double);
bool GsShapeObject::DeformVertexCoord(bool deform,const f32* u,const f32* v,bool radius,f32 radiusU,f32 radiusV,bool angle,f32 angleU,f32 angleV,bool twistEnabled,const f32* twist) {
    switch(entry->geometryType) {
    case 30: {
        int rows,columns; Vec* out;
        f32 bottom,left,height,width,shear; int row,column;
        out=(Vec*)vertexArrays[0];
        if(!out) return false;
        width=entry->width; height=entry->height;
        left=0.5f*-width; bottom=0.5f*-height;
        shear=0.0f;
        columns=entry->segmentsU+1; rows=entry->segmentsV+1;
        f32 shearAngle=angle?angleU:entry->shearAngle;
        if((f32)fabs(shearAngle)>0.00001f) shear=entry->height*(f32)tan(0.017453292f*shearAngle);
        const f32* tw=twist;const f32* vp=v;
        for(row=0;row<rows;tw++,vp++,row++) {
            f32 z;if(twistEnabled)z=*tw;else z=0.0f;
            f32 vertical=deform?*vp:(f32)row/(f32)(rows-1);
            f32 shift=shear*vertical;
            f32 y=height*vertical+bottom;
            for(column=0;column<columns;column++,out++) {
                f32 horizontal=deform?u[column]:(f32)column/(f32)(columns-1);
                f32 x=width*horizontal+left;out->x=x+shift; out->y=y; out->z=z;
            }
        }
        return true;
    }
    case 31: return DeformVertexCoordCylinderEx(deform,u,v,radius,radiusU,radiusV,angle,angleU,twistEnabled,twist);
    case 32: return DeformVertexCoordSpiral(deform,u,v,radius,radiusU,radiusV,angle,angleU,angleV,twistEnabled,twist);
    case 33: return DeformVertexCoordSphere(deform,u,v,radius,radiusU,radiusV,angle,angleU,angleV,twistEnabled,twist);
    case 34: return DeformVertexCoordTorus(deform,u,v,radius,radiusU,radiusV,angle,angleU,angleV,twistEnabled,twist);
    default: return false;
    }
}

static inline void shapeFastSinCos(f32& angle,f32& cosine) {
    f32 reduced=angle;
    if(angle>3.1415927f) {
        reduced=angle-6.2831855f*(f32)(int)(angle/6.2831855f);
        if(reduced>3.1415927f) reduced-=6.2831855f;
    } else if(angle<-3.1415927f) {
        reduced=angle-6.2831855f*(f32)(int)(angle/6.2831855f);
        if(reduced<-3.1415927f) reduced+=6.2831855f;
    }
    f32 doubled=2.0f*(reduced<-1.5707964f?-3.1415927f-reduced:(reduced<=1.5707964f?reduced:3.1415927f-reduced));
    f32 square=doubled*doubled;
    f32 magnitude=reduced;
    (*(int*)&magnitude)&=0x7fffffff;
    angle=doubled*(0.5f+square*(-0.020833334f+square*(0.00026041668f+-0.0000015500992f*square)));
    cosine=1.0f+square*(-0.125f+square*(0.0026041667f+-0.00002170139f*square));
    if(magnitude>1.5707964f) cosine=-cosine;
}
static inline f32 shapeEntryLength(const tagGsFilePrimObjectEntry* e) { return *(const f32*)((const u8*)e+0xC8); }
bool GsShapeObject::DeformVertexCoordCylinderEx(bool deform,const f32* u,const f32* v,bool radius,f32 radiusU,f32 radiusV,bool angle,f32 angleU,bool twistEnabled,const f32* twist) {
    f32 ring,z,start,sweep,length,radiusDelta,current,sine,scale;
    const f32* horizontal; const f32* tw; const f32* vp; int column,row,columns,rows; Vec* out;
    Vec* buffer=(Vec*)vertexArrays[0];
    if(!buffer) return false;
    out=buffer;
    columns=entry->segmentsU+1;
    rows=entry->segmentsV+1;
    angleU=angle?angleU:entry->shearAngle;
    if(angleU<0.00001f) angleU=0.0f;
    if(angleU>360.0f) angleU=360.0f;
    if(angleU<0.00001f) start=0.0f;
    else start=0.5f*(360.0f-angleU);
    sweep=angleU;
    start+=90.0f;
    sweep*=0.017453292f;
    start*=0.017453292f;
    if(!radius) { radiusU=entry->width; radiusV=entry->height; }
    radiusDelta=radiusU-radiusV;
    length=*(const f32*)((const u8*)entry+0xC8);
    tw=twist; vp=v;
    for(row=0;row<rows;tw++,vp++,row++) {
        if(twistEnabled==1) scale=1.0f+*tw;
        f32 vertical;
        if(deform) vertical=*vp;
        else vertical=(f32)row/(f32)(rows-1);
        ring=radiusDelta*vertical+radiusV;
        z=length*vertical;
        horizontal=u;
        for(column=0;column<columns;horizontal++,column++) {
            f32 across;
            if(deform) across=*horizontal;
            else across=(f32)column/(f32)(columns-1);
            current=ring;
            sine=sweep*across+start;
            if(twistEnabled==1) current*=scale;
            f32 cosine;
            if(column==0 || column==columns-1) {
                f32 theta=sine;
                f32 result=(f32)sin(theta);
                sine=result;
                cosine=(f32)cos(theta);
            } else {
                shapeFastSinCos(sine,cosine);
            }
            out->x=current*cosine;
            out->y=current*sine;
            out->z=z;
            out++;
        }
    }
    return true;
}

#pragma dont_inline off
extern "C" { extern f32 __float_nan[]; }
static inline f32 shapeSqrt(f32 x) {
    if(x>0.0f) {
        f64 guess=__frsqrte(x);
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        guess=0.5*guess*(3.0-(f64)x*(guess*guess));
        return (f32)((f64)x*guess);
    }
    if((f64)x<0.0)return __float_nan[0];
    union {f32 value;s32 bits;} v;v.value=x;
    s32 type;
    switch(v.bits&0x7f800000) {
    case 0x7f800000:if(v.bits&0x7fffff)type=1;else type=2;break;
    case 0:if(v.bits&0x7fffff)type=5;else type=3;break;
    default:type=4;break;
    }
    if(type==1)return __float_nan[0];
    return x;
}
#pragma dont_inline on
bool GsShapeObject::DeformVertexCoordSpiral(bool deform,const f32* u,const f32* v,bool radius,f32 radiusU,f32 radiusV,bool angle,f32 angleU,f32 angleV,bool twistEnabled,const f32* twist) {
    Vec *array=(Vec*)vertexArrays[0];
    if(!array)return false;
    Vec *out=array;
    int row,column;
    const f32 *horizontal;
    Vec *normals=0;
    int columns=entry->segmentsU+1,rows=entry->segmentsV+1;
    if(!radius){radiusU=entry->width;radiusV=entry->height;}
    if(angle)normals=(Vec*)entry->reserved1C;
    else {angleU=entry->shearAngle;angleV=*(f32*)((u8*)entry+0x60);}
    f32 delta=radiusV-radiusU,length=shapeEntryLength(entry);
    f32 angleStart=0.017453292f*angleU;
    f32 angleSweep=0.017453292f*(angleV-angleU);
    f32 widthStart=*(f32*)((u8*)entry+0x64),widthEnd=*(f32*)((u8*)entry+0x68);
    f32 lengthSquared=length*length;
    f32 slant=shapeSqrt(lengthSquared+(f32)(delta*delta));
    u32 mode=*((u8*)entry+0xCC);
    u32 even=((s32)mode%2==0),rounded=(mode>=2);
    f32 quarter=0.25f*lengthSquared;
    f32 taper=1.0f-2.0f/(f32)entry->segmentsU;
    f32 scale;
    for(row=0;row<rows;row++,twist++,v++){
        if(twistEnabled==1)scale=1.0f+*twist;
        f32 vertical;
        if(deform)vertical=*v;else vertical=(f32)row/(f32)(rows-1);
        horizontal=u;
        for(column=0;column<columns;column++,horizontal++){
            f32 across;
            if(deform)across=*horizontal;else across=(f32)column/(f32)(columns-1);
            f32 complement=1.0f-across;
            f32 theta=angleSweep*across+angleStart;
            f32 width=widthStart*complement+widthEnd*across;
            f32 sine,cosine;
            if(even==1||slant<0.00001f){
                f32 sample=across;
                f32 current;
                if(rounded==1){
                    sample=(across-0.5f)*taper+0.5f;
                    current=radiusU*(1.0f-sample)+radiusV*sample;
                    f32 distance=length*(f32)fabs(sample-0.5f);
                    f32 bulge=quarter-distance*distance;
                    if(bulge>0.0f)current+=shapeSqrt(bulge);
                }else current=radiusU*complement+radiusV*across;
                if(twistEnabled==1)current*=scale;
                sine=theta;shapeFastSinCos(sine,cosine);
                out->x=current*cosine;out->y=current*sine;
                out->z=width*vertical+(length*sample-0.5f*width);out++;
            }else{
                f32 fraction,sample;
                f32 current;
                if(rounded==1){
                    fraction=width/slant;
                    sample=(across-0.5f)*(1.0f-fraction)+0.5f;
                    f32 position=((fraction*vertical+(sample-0.5f*fraction))-0.5f)*taper+0.5f;
                    current=radiusU*(1.0f-position)+radiusV*position;
                    f32 distance=length*(f32)fabs(position-0.5f);
                    f32 bulge=quarter-distance*distance;
                    if(bulge>0.0f)current+=shapeSqrt(bulge);
                }else{
                    fraction=width/slant;
                    sample=(across-0.5f)*(1.0f-fraction)+0.5f;
                    f32 position=fraction*vertical+(sample-0.5f*fraction);
                    current=radiusU*(1.0f-position)+radiusV*position;
                }
                if(twistEnabled==1)current*=scale;
                sine=theta;shapeFastSinCos(sine,cosine);
                f32 stripLength=length*fraction;
                out->x=current*cosine;out->y=current*sine;
                out->z=stripLength*vertical+(length*sample-0.5f*stripLength);out++;
            }
            if(normals){normals->x=cosine;normals->y=sine;normals->z=0.0f;normals++;}
        }
    }
    return true;
}

bool GsShapeObject::DeformVertexCoordSphere(bool deform,const f32* u,const f32* v,bool radius,f32 radiusU,f32 radiusV,bool angle,f32 angleU,f32 angleV,bool twistEnabled,const f32* twist) {
    Vec *out=(Vec*)vertexArrays[0];
    if(!out)return false;
    int columns=entry->segmentsU+1,rows=entry->segmentsV+1;
    if(!angle){angleU=entry->shearAngle;angleV=*(f32*)((u8*)entry+0x60);}
    if(angleU<0.00001f)angleU=0.00001f;
    if(angleU>360.0f)angleU=360.0f;
    if(angleV<0.00001f)angleV=0.00001f;
    if(angleV>360.0f)angleV=360.0f;
    f32 start;
    if(angleU<0.00001f)start=0.0f;else start=0.5f*(360.0f-angleU);
    f32 bottom;
    if(*((u8*)entry+0xCF)==0)bottom=0.017453292f*(0.5f*-angleV);else bottom=-1.5707964f;
    if(!radius)radiusU=entry->width;
    f32 scale;
    for(int row=0;row<rows;row++,twist++,v++){
        if(twistEnabled==1)scale=1.0f+*twist;
        f32 vertical;
        if(deform)vertical=*v;else vertical=(f32)row/(f32)(rows-1);
        f32 verticalSine=0.017453292f*angleV*vertical+bottom,verticalCosine;
        shapeFastSinCos(verticalSine,verticalCosine);
        f32 ring=radiusU*verticalCosine;
        const f32 *horizontal=u;
        for(int column=0;column<columns;column++,horizontal++){
            f32 across;
            if(deform)across=*horizontal;else across=(f32)column/(f32)(columns-1);
            f32 current=ring;
            f32 sine=angleU*0.017453292f*across+(start+90.0f)*0.017453292f;
            if(twistEnabled==1)current=ring*scale;
            f32 cosine;
            if(column==0||column==columns-1){f32 theta=sine;sine=(f32)sin(theta);cosine=(f32)cos(theta);}
            else shapeFastSinCos(sine,cosine);
            out->x=current*cosine;out->y=current*sine;out->z=radiusU*verticalSine;out++;
        }
    }
    return true;
}

bool GsShapeObject::DeformVertexCoordTorus(bool deform,const f32* u,const f32* v,bool radius,f32 radiusU,f32 radiusV,bool angle,f32 angleU,f32 angleV,bool twistEnabled,const f32* twist) {
    Vec *out=(Vec*)vertexArrays[0];
    if(!out)return false;
    int columns=entry->segmentsU+1,rows=entry->segmentsV+1;
    if(!radius){radiusV=entry->height;radiusU=entry->width;}
    if(!angle){angleU=entry->shearAngle;angleV=*(f32*)((u8*)entry+0x60);}
    if(angleU<0.00001f)angleU=0.00001f;
    if(angleU>360.0f)angleU=360.0f;
    if(angleV<0.00001f)angleV=0.00001f;
    if(angleV>360.0f)angleV=360.0f;
    f32 start;
    if(angleU<0.00001f)start=0.0f;else start=0.5f*(360.0f-angleU);
    f32 bottom;
    if(angleV<0.00001f)bottom=0.0f;else bottom=0.5f*(360.0f-angleV);
    for(int row=0;row<rows;row++,v++){
        f32 vertical;
        if(deform)vertical=*v;else vertical=(f32)row/(f32)(rows-1);
        f32 verticalSine=angleV*0.017453292f*vertical+(bottom+180.0f)*0.017453292f,verticalCosine;
        shapeFastSinCos(verticalSine,verticalCosine);
        f32 ring=radiusV*verticalCosine+radiusU;
        const f32 *horizontal=u;
        for(int column=0;column<columns;column++,horizontal++){
            f32 across;
            if(deform)across=*horizontal;else across=(f32)column/(f32)(columns-1);
            f32 current=ring;
            f32 sine=angleU*0.017453292f*across+(start+90.0f)*0.017453292f;
            f32 cosine;
            if(column==0||column==columns-1){f32 theta=sine;sine=(f32)sin(theta);cosine=(f32)cos(theta);}
            else shapeFastSinCos(sine,cosine);
            out->x=current*cosine;out->y=current*sine;out->z=radiusV*verticalSine;out++;
        }
    }
    return true;
}

bool GsShapeObject::WaveTextureCoord(u32 texture,f32 offsetU,f32 offsetV,const GSmtx* matrix,bool accumulate) {
    GsShapePair* out=(GsShapePair*)vertexArrays[texture+2];
    if(!out) return false;
    if(texture==0 && entry->textureCount>=2) return false;
    const Vec* displacement=(const Vec*)entry->reserved1C;
    if(!displacement) return false;
    if(!accumulate) memcpy(out,entry->textureCoords,entry->vertexCount*sizeof(GsShapePair));
    u16 segmentsU=entry->segmentsU,segmentsV=entry->segmentsV;
    int columns=segmentsU+1,rows=segmentsV+1;
    if(offsetU>1.0f) offsetU-=(f32)(int)offsetU;
    else if(offsetU<0.0f) offsetU-=(f32)((int)offsetU-1);
    if(offsetV>1.0f) offsetV-=(f32)(int)offsetV;
    else if(offsetV<0.0f) offsetV-=(f32)((int)offsetV-1);
    int shiftU=(int)(offsetU*(f32)segmentsU)%segmentsU;
    int shiftV=(int)(offsetV*(f32)segmentsV)%segmentsV;
    f32 fractionU=(f32)segmentsU*(offsetU-(f32)shiftU/(f32)segmentsU);
    f32 fractionV=(f32)segmentsV*(offsetV-(f32)shiftV/(f32)segmentsV);
    fractionU-=(f32)(int)fractionU; fractionV-=(f32)(int)fractionV;
    f32 diagonalWeight=fractionU*fractionV;
    f32 verticalWeight=(1.0f-fractionU)*fractionV;
    f32 horizontalWeight=fractionU*(1.0f-fractionV);
    f32 originWeight=(1.0f-fractionU)*(1.0f-fractionV);
    int rowOffset=0;
    for(int row=0;row<rows;row++,rowOffset+=columns) {
        for(int column=0;column<columns;column++) {
            u16 sampleU=(column+shiftU)%entry->segmentsU;
            int sampleV=(row+shiftV)%entry->segmentsV;
            if(sampleU==0 && column==columns-1) sampleU=entry->segmentsU;
            if(sampleV==0 && row==rows-1) sampleV=entry->segmentsV;
            int sample=sampleU+sampleV*columns;
            Vec value;
            if(sampleU==columns-1 || sampleV==rows-1) {
                value.x=displacement[sample].x; value.y=displacement[sample].y; value.z=displacement[sample].z;
            } else {
                Vec result, diagonal,vertical,horizontal,origin,sumHorizontal,sumVertical;
                int nextRow=sample+columns;
                PSVECScale(&displacement[nextRow+1],&result,diagonalWeight);
                diagonal.x=result.x; diagonal.y=result.y; diagonal.z=result.z;
                PSVECScale(&displacement[nextRow],&result,verticalWeight);
                vertical.x=result.x; vertical.y=result.y; vertical.z=result.z;
                PSVECScale(&displacement[sample+1],&result,horizontalWeight);
                horizontal.x=result.x; horizontal.y=result.y; horizontal.z=result.z;
                PSVECScale(&displacement[sample],&result,originWeight);
                origin.x=result.x; origin.y=result.y; origin.z=result.z;
                PSVECAdd(&origin,&horizontal,&result);
                sumHorizontal.x=result.x; sumHorizontal.y=result.y; sumHorizontal.z=result.z;
                PSVECAdd(&sumHorizontal,&vertical,&result);
                sumVertical.x=result.x; sumVertical.y=result.y; sumVertical.z=result.z;
                PSVECAdd(&sumVertical,&diagonal,&result);
                value.x=result.x; value.y=result.y; value.z=result.z;
            }
            PSMTXMultVecSR(matrix->matrix,&value,&value);
            GsShapePair* coordinate=&out[rowOffset+column];
            coordinate->u+=value.x; coordinate->v+=value.y;
        }
    }
    return true;
}

void GSgfxLayer::tunitAlphaOp(u8 unit, GSgfxTunitOp operation, GSgfxTunitBias bias, GSgfxTunitScale scale, bool clamp, GSgfxTunitReg output) {
    alphaOps[unit].operation = operation;
    alphaOps[unit].bias = bias;
    alphaOps[unit].scale = scale;
    alphaOps[unit].clamp = clamp;
    alphaOps[unit].output = output;
    alphaOpDirty |= 1 << unit;
    dirty |= 8;
    savedAlphaOpDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::tunitAlphaArg(u8 unit, GSgfxTunitAArg a, GSgfxTunitAArg b, GSgfxTunitAArg c, GSgfxTunitAArg d) {
    alphaArgs[unit][0] = a;
    alphaArgs[unit][1] = b;
    alphaArgs[unit][2] = c;
    alphaArgs[unit][3] = d;
    alphaArgDirty |= 1 << unit;
    dirty |= 8;
    savedAlphaArgDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::tunitColorOp(u8 unit, GSgfxTunitOp operation, GSgfxTunitBias bias, GSgfxTunitScale scale, bool clamp, GSgfxTunitReg output) {
    colorOps[unit].operation = operation;
    colorOps[unit].bias = bias;
    colorOps[unit].scale = scale;
    colorOps[unit].clamp = clamp;
    colorOps[unit].output = output;
    colorOpDirty |= 1 << unit;
    dirty |= 8;
    savedColorOpDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::tunitColorArg(u8 unit, GSgfxTunitCArg a, GSgfxTunitCArg b, GSgfxTunitCArg c, GSgfxTunitCArg d) {
    colorArgs[unit][0] = a;
    colorArgs[unit][1] = b;
    colorArgs[unit][2] = c;
    colorArgs[unit][3] = d;
    colorArgDirty |= 1 << unit;
    dirty |= 8;
    savedColorArgDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::tunitMapping(u8 unit, u8 texture, u8 coordinate, u8 color) {
    mapping[unit].texture = texture;
    mapping[unit].coordinate = coordinate;
    if (color != 0xff) mapping[unit].color = color + 4;
    else mapping[unit].color = 0xff;
    mappingDirty |= 1 << unit;
    dirty |= 8;
    savedMappingDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::texSelect(u8 unit, GStexture* texture) {
    if (textures[unit] == texture && savedTextures[unit] == texture && !texture->dirty) return;
    textures[unit] = texture;
    textureDirty |= 1 << unit;
    savedTextures[unit] = texture;
    savedTextureDirty |= 1 << unit;
}

extern "C" void GSgfxVFSetArray(void*, s32, s32, void*, u8, u32);
extern "C" void dlDraw__10GSgfxLayerFP7GSgfxDL(GSgfxLayer*, void*);
extern "C" void beginSurface__10GSgfxLayerFUs(GSgfxLayer*, u16);
extern "C" void endSurface__10GSgfxLayerFv(GSgfxLayer*);
#pragma push
#pragma dont_inline off
static inline bool shapeSetupVF(GsShapeObject* self, u16 n) {
    const int attrs[4] = {13, 14, 15, 16};
    if (self->vertexArrays[0] == 0) {
        return false;
    }
    if (self->vertexArrays[0] != 0) {
        GSgfxVFSetArray(self->vertexFormat, 9, 3, self->vertexArrays[0], 12, n * 12);
    } else {
        return false;
    }
    if (self->vertexArrays[1] != 0) {
        GSgfxVFSetArray(self->vertexFormat, 11, 3, self->vertexArrays[1], 4, n * 4);
    } else {
        return false;
    }
    int i;
    for (i = 0; i < self->entry->textureCount; i++) {
        if (self->vertexArrays[i + 2] != 0) {
            GSgfxVFSetArray(self->vertexFormat, attrs[i], 3, self->vertexArrays[i + 2], 8, n * 8);
        } else {
            return false;
        }
    }
    return true;
}
#pragma pop
extern "C" void DrawShapeGfx__13GsShapeObjectFP10GSgfxLayersUc(GsShapeObject* self, GSgfxLayer* layer, s16 s, u8 c) {
    u16 b;
    u16 a;
    u16 i;
    u16 base0;
    u16 texN = self->entry->textureCount;
    u16 n = self->entry->segmentsU + 1;
    bool ok = shapeSetupVF(self, self->entry->vertexCount);
    u16 j;
    u16 k;
    u16 base1;
    if (ok) {
        layer->vertexFormat = self->vertexFormat;
        layer->primitive = 0x98;
        for (i = 0; i < self->entry->segmentsV; i++) {
            base0 = i * n;
            beginSurface__10GSgfxLayerFUs(layer, n * 2);
            base1 = (i + 1) * n;
            for (j = 0; j < n; j++) {
                a = j + base0;
                b = j + base1;
                GXWGFifo.u16 = a;
                GXWGFifo.u16 = a;
                for (k = 0; k < texN; k++) {
                    GXWGFifo.u16 = a;
                }
                GXWGFifo.u16 = b;
                GXWGFifo.u16 = b;
                for (k = 0; k < texN; k++) {
                    GXWGFifo.u16 = b;
                }
            }
            endSurface__10GSgfxLayerFv(layer);
        }
    }
}

extern "C" void SetStateMode__13GsShapeObjectFP10GSgfxLayer(GsShapeObject* self, GSgfxLayer* layer) {
    u8 depth = self->entry->reserved05[0] != 0;
    u8 alpha = self->entry->reserved05[1] != 0;
    u8 type;
    if (self->entry->shapeType == 8) {
        depth = 1;
        alpha = 1;
    }
    if (depth == 1) layer->depthEnable = 1;
    else layer->depthEnable = 0;
    layer->depthFunction = 1;
    layer->markPixel(8);
    layer->colorUpdate = 1;
    layer->alphaUpdate = 1;
    if (alpha == 1) layer->destinationAlpha = 1;
    else layer->destinationAlpha = 0;
    layer->markPixel(4);
    layer->cullMode = *((u8*)self->entry + 0xd8);
    layer->transformDirty |= 2;
    layer->dirty |= 2;
    layer->savedTransformDirty |= 2;
    layer->savedDirty |= 2;
    type = self->entry->shapeType;
    if (type == 10 && self->entry->textureCount >= 2) {
        u8 blend = *((u8*)self->entry->textures[1] + 0xa);
        switch (blend) {
        case 2:
        case 4:
            type = blend;
            break;
        }
    }
    switch (type) {
    case 4:
        layer->selectShader(1);
        layer->setBlend(1, 4, 1, 5);
        break;
    case 5:
        layer->selectShader(1);
        layer->setBlend(3, 4, 1, 5);
        break;
    case 2:
        layer->selectShader(1);
        layer->setBlend(1, 4, 5, 5);
        break;
    case 8:
        layer->selectShader(1);
        layer->setBlend(1, 4, 5, 5);
        break;
    case 10:
        layer->selectShader(1);
        layer->setBlend(1, 4, 5, 5);
        break;
    default:
        layer->selectShader(1);
        layer->setBlend(1, 4, 5, 5);
        break;
    }
}

extern "C" void CallDisplayListShape__13GsShapeObjectFP10GSgfxLayersUc(GsShapeObject* self, GSgfxLayer* layer, s16 instance, u8 flags) {
    if (self->displayList) {
        s32 vertexCount;
        tagGsFilePrimObjectEntry* entry = self->entry;
        u32 attributes[4] = {13, 14, 15, 16};
        vertexCount = entry->vertexCount;
        if (self->vertexArrays[0] != 0) {
            if (self->vertexArrays[0] != 0) {
                GSgfxVFSetArray(self->vertexFormat, 9, 3, self->vertexArrays[0], 12, vertexCount * 12);
                if (self->vertexArrays[1] != 0) {
                    GSgfxVFSetArray(self->vertexFormat, 11, 3, self->vertexArrays[1], 4, vertexCount * 4);
                    GsShapeObject* arrays = self;
                    u32* attribute = attributes;
                    u32 size = vertexCount * 8;
                    for (vertexCount = 0; vertexCount < self->entry->textureCount; arrays = (GsShapeObject*)((u8*)arrays + 4), ++attribute, ++vertexCount) {
                        if (arrays->vertexArrays[2] == 0) break;
                        GSgfxVFSetArray(self->vertexFormat, *attribute, 3, arrays->vertexArrays[2], 8, size);
                    }
                }
            }
        }
        dlDraw__10GSgfxLayerFP7GSgfxDL(layer, self->displayList);
    } else {
        DrawShapeGfx__13GsShapeObjectFP10GSgfxLayersUc(self, layer, instance, flags);
    }
}

#pragma dont_inline off
static inline void shapeKColorSelect(GSgfxLayer *layer,u8 stage,GXTevKColorSel value) {
 layer->konstColors[stage]=value;layer->konstColorDirty|=1<<stage;layer->dirty|=0x10;layer->savedKonstColorDirty|=1<<stage;layer->savedDirty|=0x10;
}
static inline void shapeKAlphaSelect(GSgfxLayer *layer,u8 stage,GXTevKAlphaSel value) {
 layer->konstAlphas[stage]=value;layer->konstAlphaDirty|=1<<stage;layer->dirty|=0x10;layer->savedKonstAlphaDirty|=1<<stage;layer->savedDirty|=0x10;
}
#pragma dont_inline on
extern "C" void SetStateTexture__13GsShapeObjectFP10GSgfxLayerP14GsShapeTextureP9GStexture(GsShapeObject *self,GSgfxLayer *layer,GsShapeTexture *textures,GStexture *refract) {
 GXTevKColorSel colorRegisters[4]={GX_TEV_KCSEL_K0,GX_TEV_KCSEL_K1,GX_TEV_KCSEL_K2,GX_TEV_KCSEL_K3};
 GXTevKAlphaSel alphaRegisters[4]={GX_TEV_KASEL_K0_A,GX_TEV_KASEL_K1_A,GX_TEV_KASEL_K2_A,GX_TEV_KASEL_K3_A};
 u8 stage=0,textureIndex=0,count=self->entry->textureCount;
 int var_r5_2,var_r5_3,var_r5_4,var_r5_5,var_r6_2,var_r6_3,var_r6_4,var_r7,var_r7_2,var_r7_3,var_r8,var_r8_10,var_r8_11,var_r8_12,var_r8_13,var_r8_14,var_r8_2,var_r8_3,var_r8_4,var_r8_5,var_r8_6,var_r8_7,var_r8_8,var_r8_9;
 while(textureIndex<count) {
  u32 index=textureIndex;
  ShapeTextureBinding *binding=(ShapeTextureBinding*)self->entry->textures[textureIndex];
  GsShapeTexture *texture=&textures[binding->index];
  int filter, minFilter, magFilter;
  filter=1;
  if(binding->minFilter) filter=2;
  magFilter=1;
  if(binding->magFilter) magFilter=2;
  minFilter=1;
  if(binding->minFilter) minFilter=2;
  GStextureSetFilter(texture->texture,minFilter,magFilter,filter);
  GStextureSetWrap(texture->texture,binding->wrapS,binding->wrapT);
  GStexture *selected=texture->texture;if(textureIndex==0&&refract)selected=refract;
  if(self->entry->shapeType==10&&textureIndex==0&&self->entry->textureCount>=2) {
   layer->texSelect(index,selected);
   layer->tunitMapping(stage,index,index,0);
   layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15);
   layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7);
   layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   int next=stage+1;
   layer->tunitMapping(next,index,index,0);
   layer->tunitColorArg(next,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15);
   layer->tunitColorOp(next,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   layer->tunitAlphaArg(next,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7);
   layer->tunitAlphaOp(next,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   stage+=2;
   if(texture->entry->colorRange==1) {
    layer->tunitMapping(stage,index,index,0);
    layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15);
    layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
    layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7);
    layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
    ++stage;
   }
  } else if(textureIndex<2) {
   if(texture->entry->colorRange) {
    int middle=stage+1,mixStage=stage+2;
    shapeKColorSelect(layer,stage,colorRegisters[index*2]);shapeKAlphaSelect(layer,stage,alphaRegisters[index*2]);
    shapeKColorSelect(layer,middle,colorRegisters[index*2+1]);shapeKAlphaSelect(layer,middle,alphaRegisters[index*2+1]);shapeKAlphaSelect(layer,mixStage,alphaRegisters[1]);
    layer->texSelect(index,selected);layer->tunitMapping(stage,index,index,0);
    layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)14);
    layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)1);
    layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)6,(GSgfxTunitAArg)4,(GSgfxTunitAArg)7);
    layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)1);
    layer->tunitMapping(middle,index,index,0);
    layer->tunitColorArg(middle,(GSgfxTunitCArg)14,(GSgfxTunitCArg)2,(GSgfxTunitCArg)8,(GSgfxTunitCArg)15);
    layer->tunitColorOp(middle,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)2);
    layer->tunitAlphaArg(middle,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)1);
    layer->tunitAlphaOp(middle,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)2);
    layer->tunitMapping(mixStage,index,index,0);
    switch(binding->blend) {

                case 0:
                    var_r7 = 0;
                    if (textureIndex == 0) {
                        var_r7 = 0xC;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(var_r7), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r7_2 = 0;
                    if (textureIndex == 0) {
                        var_r7_2 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(var_r7_2), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 2:
                    var_r5_2 = 0;
                    if (textureIndex == 0) {
                        var_r5_2 = 4;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(var_r5_2), (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(9), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r5_3 = 0;
                    if (textureIndex == 0) {
                        var_r5_3 = 2;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(var_r5_3), (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 3:
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(4));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(2));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 4:
                    var_r8 = 0;
                    if (textureIndex == 0) {
                        var_r8 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_2 = 0;
                    if (textureIndex == 0) {
                        var_r8_2 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_2));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 5:
                    var_r8_3 = 0;
                    if (textureIndex == 0) {
                        var_r8_3 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_3));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(textureIndex != 0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_4 = 0;
                    if (textureIndex == 0) {
                        var_r8_4 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_4));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 9:
                    var_r8_5 = 0;
                    if (textureIndex == 0) {
                        var_r8_5 = 4;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_5));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r7_3 = 0;
                    if (textureIndex == 0) {
                        var_r7_3 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(var_r7_3), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                default:
                    var_r8_6 = 0;
                    if (textureIndex == 0) {
                        var_r8_6 = 0xA;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_6));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_7 = 0;
                    if (textureIndex == 0) {
                        var_r8_7 = 5;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;

    }stage+=3;
   } else {
    int mixStage=stage+1;
    shapeKColorSelect(layer,stage,colorRegisters[index*2]);shapeKAlphaSelect(layer,stage,alphaRegisters[index*2]);shapeKAlphaSelect(layer,mixStage,alphaRegisters[1]);
    layer->texSelect(index,selected);layer->tunitMapping(stage,index,index,0);
    layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)14,(GSgfxTunitCArg)8,(GSgfxTunitCArg)15);
    layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)1);
    layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)6,(GSgfxTunitAArg)4,(GSgfxTunitAArg)7);
    layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)1);
    layer->tunitMapping(mixStage,index,index,0);
    switch(binding->blend) {

                case 0:
                    var_r6_2 = 0;
                    if (textureIndex == 0) {
                        var_r6_2 = 0xC;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r6_2), (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r6_3 = 0;
                    if (textureIndex == 0) {
                        var_r6_3 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r6_3), (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 2:
                    var_r5_4 = 0;
                    if (textureIndex == 0) {
                        var_r5_4 = 0xC;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(var_r5_4), (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(9), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r5_5 = 0;
                    if (textureIndex == 0) {
                        var_r5_5 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(var_r5_5), (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 3:
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0xE), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(6), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 4:
                    var_r8_8 = 0;
                    if (textureIndex == 0) {
                        var_r8_8 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_8));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_9 = 0;
                    if (textureIndex == 0) {
                        var_r8_9 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_9));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 5:
                    var_r8_10 = 0;
                    if (textureIndex == 0) {
                        var_r8_10 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_10));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(textureIndex != 0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_11 = 0;
                    if (textureIndex == 0) {
                        var_r8_11 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_11));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 9:
                    var_r8_12 = 0;
                    if (textureIndex == 0) {
                        var_r8_12 = 8;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_12));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r6_4 = 0;
                    if (textureIndex == 0) {
                        var_r6_4 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r6_4), (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                default:
                    var_r8_13 = 0;
                    if (textureIndex == 0) {
                        var_r8_13 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_13));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_14 = 0;
                    if (textureIndex == 0) {
                        var_r8_14 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_14));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;

    }stage+=2;
   }
  } else {
   layer->texSelect(index,selected);layer->tunitMapping(stage,index,index,0);
   switch(binding->blend) {

            case 0:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0), (GSgfxTunitCArg)(0xF));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(0), (GSgfxTunitAArg)(7));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 2:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(0), (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(9), (GSgfxTunitCArg)(0xF));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 3:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(8));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 4:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 5:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(1), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 9:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(0), (GSgfxTunitAArg)(7));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            default:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;

   }++stage;
  }
  if(index==count-1) {
   layer->tunitMapping(stage,index,index,0);
   layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)10,(GSgfxTunitCArg)0,(GSgfxTunitCArg)15);
   layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)5,(GSgfxTunitAArg)0,(GSgfxTunitAArg)7);
   layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   ++stage;
  }++textureIndex;
 }
}

#pragma dont_inline off

extern "C" f32* GSgfxMatrixGetPtr(s32);
static inline void refractCopy(Vec* out,const Vec* in) {f32 x=in->x,y=in->y,z=in->z;out->x=x;out->y=y;out->z=z;}
extern "C" bool RefractTextureCoord__13GsShapeObjectFffP5GSmtxP5GSmtxP5GSmtxf(GsShapeObject *self,f32 offsetU,f32 offsetV,GSmtx *first,GSmtx *second,GSmtx *third,f32) {
 Mtx transform,projectionMatrix;f32 *sourceProjection=GSgfxMatrixGetPtr(4);
 f32 projection[7];
 f32 viewport[6];
 f32 screenWidth,screenHeight;
 projection[0]=0.0f;projection[1]=sourceProjection[0];projection[2]=sourceProjection[2];projection[3]=sourceProjection[5];projection[4]=sourceProjection[6];projection[5]=sourceProjection[10];projection[6]=sourceProjection[11];
 viewport[0]=0.0f;viewport[1]=0.0f;viewport[2]=640.0f;viewport[3]=480.0f;viewport[4]=0.0f;viewport[5]=1.0f;
 screenWidth=viewport[2];screenHeight=viewport[3];
 u32 copySize=self->entry->vertexCount*sizeof(GsShapePair);
 for(s32 texture=0;texture<self->entry->textureCount;++texture) {
  const Vec *normalGrid=(const Vec*)self->entry->reserved1C;const Vec *positions=self->entry->vertices;
  if(!normalGrid)continue;GsShapePair *out=(GsShapePair*)self->vertexArrays[texture+2];if(!out)continue;
  if(texture==0){PSMTXCopy(second->matrix,transform);PSMTXConcat(first->matrix,transform,transform);PSMTXConcat(third->matrix,transform,transform);memcpy(projectionMatrix,transform,sizeof(Mtx));}
  else {PSMTXCopy(second->matrix,transform);memcpy(out,self->entry->textureCoords,copySize);}
  u16 segmentsU=self->entry->segmentsU,segmentsV=self->entry->segmentsV;int columns=segmentsU+1,rows=segmentsV+1;
  if(offsetU>1.0f)offsetU-=(f32)(int)offsetU;else if(offsetU<0.0f)offsetU-=(f32)((int)offsetU-1);
  if(offsetV>1.0f)offsetV-=(f32)(int)offsetV;else if(offsetV<0.0f)offsetV-=(f32)((int)offsetV-1);
  int shiftU=(int)(offsetU*(f32)segmentsU)%segmentsU,shiftV=(int)(offsetV*(f32)segmentsV)%segmentsV;
  f32 fractionU=(f32)segmentsU*(offsetU-(f32)shiftU/(f32)segmentsU),fractionV=(f32)segmentsV*(offsetV-(f32)shiftV/(f32)segmentsV);
  fractionU-=(f32)(int)fractionU;fractionV-=(f32)(int)fractionV;
  f32 diagonalWeight=fractionU*fractionV,verticalWeight=(1.0f-fractionU)*fractionV,horizontalWeight=fractionU*(1.0f-fractionV),originWeight=(1.0f-fractionU)*(1.0f-fractionV);
  int rowOffset=0;
  for(int row=0;row<rows;++row,rowOffset+=columns) {
   int index=rowOffset;
   for(int column=0;column<columns;++column,++index) {
    int sampleU=(column+shiftU)%self->entry->segmentsU;int sampleV=(row+shiftV)%self->entry->segmentsV;
    if(sampleU==0&&column==columns-1)sampleU=self->entry->segmentsU;
    if(sampleV==0&&row==rows-1)sampleV=self->entry->segmentsV;
    int sample=sampleU+sampleV*columns;Vec value;
    if(sampleU==columns-1) {
     if(sampleV==rows-1) {value.x=normalGrid[sample].x;value.y=normalGrid[sample].y;value.z=normalGrid[sample].z;}
     else {
      int diagonal=sample+columns+1,vertical=sample+columns,horizontal=sample-1;
      Vec a,b,c,d,sum1,sum2;Vec scaleA,scaleB,scaleC,scaleD,add1,add2,add3;
      PSVECScale(&normalGrid[diagonal],&scaleA,diagonalWeight);refractCopy(&a,&scaleA);
      PSVECScale(&normalGrid[vertical],&scaleB,verticalWeight);refractCopy(&b,&scaleB);
      PSVECScale(&normalGrid[horizontal],&scaleC,horizontalWeight);refractCopy(&c,&scaleC);
      PSVECScale(&normalGrid[sample],&scaleD,originWeight);refractCopy(&d,&scaleD);
      PSVECAdd(&d,&c,&add1);refractCopy(&sum1,&add1);
      PSVECAdd(&sum1,&b,&add2);refractCopy(&sum2,&add2);
      PSVECAdd(&sum2,&a,&add3);refractCopy(&value,&add3);

     }
    } else if(sampleV==rows-1) {
      int diagonal=sample-columns+1,vertical=sample-columns,horizontal=sample+1;
      Vec a,b,c,d,sum1,sum2;Vec scaleA,scaleB,scaleC,scaleD,add1,add2,add3;
      PSVECScale(&normalGrid[diagonal],&scaleA,diagonalWeight);refractCopy(&a,&scaleA);
      PSVECScale(&normalGrid[vertical],&scaleB,verticalWeight);refractCopy(&b,&scaleB);
      PSVECScale(&normalGrid[horizontal],&scaleC,horizontalWeight);refractCopy(&c,&scaleC);
      PSVECScale(&normalGrid[sample],&scaleD,originWeight);refractCopy(&d,&scaleD);
      PSVECAdd(&d,&c,&add1);refractCopy(&sum1,&add1);
      PSVECAdd(&sum1,&b,&add2);refractCopy(&sum2,&add2);
      PSVECAdd(&sum2,&a,&add3);refractCopy(&value,&add3);

    } else {
      int diagonal=sample+columns+1,vertical=sample+columns,horizontal=sample+1;
      Vec a,b,c,d,sum1,sum2;Vec scaleA,scaleB,scaleC,scaleD,add1,add2,add3;
      PSVECScale(&normalGrid[diagonal],&scaleA,diagonalWeight);refractCopy(&a,&scaleA);
      PSVECScale(&normalGrid[vertical],&scaleB,verticalWeight);refractCopy(&b,&scaleB);
      PSVECScale(&normalGrid[horizontal],&scaleC,horizontalWeight);refractCopy(&c,&scaleC);
      PSVECScale(&normalGrid[sample],&scaleD,originWeight);refractCopy(&d,&scaleD);
      PSVECAdd(&d,&c,&add1);refractCopy(&sum1,&add1);
      PSVECAdd(&sum1,&b,&add2);refractCopy(&sum2,&add2);
      PSVECAdd(&sum2,&a,&add3);refractCopy(&value,&add3);

    }
    PSMTXMultVecSR(transform,&value,&value);
    if(texture==0) {
     f32 x,y,z;GXProject(positions[index].x,positions[index].y,positions[index].z,projectionMatrix,projection,viewport,&x,&y,&z);
     if((f32)fabs(value.x)>0.00001f||(f32)fabs(value.y)>0.00001f||(f32)fabs(value.z)>0.00001f) {
      PSVECNormalize(&value,&value);
      if(value.x<=0.0f)x=x*(1.0f+value.x);else x=value.x*(screenWidth-x)+x;
      if(value.y<=0.0f)y+=-value.y*(screenHeight-y);else y*=1.0f-value.y;
     }
     out[index].u=x/screenWidth;out[index].v=y/screenHeight;
    }else {out[index].u+=value.x;out[index].v+=value.y;}
   }
  }
 }
 return true;
}

#pragma dont_inline off
extern "C" double acos(double);
static f32 shapeAngleWeight(f32 dot,f32 width) {
 f32 result;
 if(dot>1.0f||width<0.00001f)result=1.0f;
 else {
  f32 distance=shapeSqrt(1.0f-dot),threshold=1.0f-width;
  if(distance<=threshold)result=1.0f;
  else {f32 weight=(f32)cos((1.5707964f*(distance-threshold))/width);result=weight*weight;}
 }
 return result;
}
static f32 shapeAngularWeight(Vec *normal,Vec *view,GsShapeObject *self) {
 f64 absolute=fabs(PSVECDotProduct(normal,view));f32 dot=(f32)absolute;
 return shapeAngleWeight(dot,*(f32*)((u8*)self->entry+0xd0));
}
#pragma dont_inline on
extern "C" bool ShadeVertexColor__13GsShapeObjectFP5GSmtxP5GSmtxP5GSmtxfb(GsShapeObject *self,GSmtx *first,GSmtx *second,GSmtx *third,f32 distance,bool preserveNormal) {
 if(!self->vertexArrays[1])return false;
 Mtx transform,rotation;PSMTXCopy(second->matrix,transform);PSMTXConcat(first->matrix,transform,transform);PSMTXConcat(third->matrix,transform,transform);
 Vec *normals;Vec *positions;tagGScol4ub *colors;int i;int count;
 normals=(Vec*)self->entry->reserved1C;count=self->entry->vertexCount;positions=self->entry->vertices;colors=(tagGScol4ub*)self->vertexArrays[1];i=0;
 for(;i<count;++normals,++positions,++colors,++i) {
  Vec normalInput,position,normal,view;normalInput.x=normals->x;normalInput.y=normals->y;normalInput.z=normals->z;position.x=positions->x;position.y=positions->y;position.z=positions->z;PSMTXMultVecSR(transform,&normalInput,&normal);PSMTXMultVec(transform,&position,&view);f32 viewZ=view.z;view.z=viewZ-distance;
  f32 weight;
  if(self->entry->colorMode==1) {normal.y=0.0f;view.y=0.0f;
   if(PSVECSquareMag(&normal)>9.9999994e-11f&&PSVECSquareMag(&view)>9.9999994e-11f){PSVECNormalize(&normal,&normal);PSVECNormalize(&view,&view);weight=shapeAngularWeight(&normal,&view,self);}else weight=0.0f;}
  else if(self->entry->colorMode==2) {normal.x=0.0f;view.x=0.0f;
   if(PSVECSquareMag(&normal)>9.9999994e-11f&&PSVECSquareMag(&view)>9.9999994e-11f){PSVECNormalize(&normal,&normal);PSVECNormalize(&view,&view);weight=shapeAngularWeight(&normal,&view,self);}else weight=0.0f;}
  else if(self->entry->colorMode==3) {
   if((self->entry->geometryType==31&&*((u8*)self->entry+0xce)==1&&!preserveNormal)||(self->entry->geometryType==32&&(*((u8*)self->entry+0xcc)%2)==0)) {
    Vec forward,axis;forward.x=0.0f;forward.y=0.0f;forward.z=1.0f;PSMTXMultVecSR(transform,&forward,&forward);PSVECCrossProduct(&view,&forward,&axis);
    if(PSVECSquareMag(&axis)>9.9999994e-11f&&PSVECSquareMag(&view)>9.9999994e-11f){PSVECNormalize(&axis,&axis);PSVECNormalize(&view,&view);PSMTXRotAxisRad(rotation,&axis,1.5707964f-(f32)acos(PSVECDotProduct(&forward,&view)));PSMTXMultVecSR(rotation,&normal,&normal);weight=shapeAngularWeight(&normal,&view,self);}else weight=0.0f;
   }else if(PSVECSquareMag(&normal)>9.9999994e-11f&&PSVECSquareMag(&view)>9.9999994e-11f){PSVECNormalize(&normal,&normal);PSVECNormalize(&view,&view);weight=shapeAngularWeight(&normal,&view,self);}else weight=0.0f;}
  else weight=1.0f;
  if(viewZ>0.0f&&distance>0.00001f){f32 attenuation;if(viewZ>distance)attenuation=0.0f;else attenuation=(distance-viewZ)/distance;weight*=attenuation;}
  switch(self->entry->shapeType){case 2:case 8:case 10:((u8*)self->vertexArrays[1])[(i*4+3)]=weight*colors->a;break;default:((u8*)self->vertexArrays[1])[(i*4+0)]=weight*colors->r;((u8*)self->vertexArrays[1])[(i*4+1)]=weight*colors->g;((u8*)self->vertexArrays[1])[(i*4+2)]=weight*colors->b;break;}
 }
 return true;
}
#pragma dont_inline off
extern Mtx mtxIdent;
static inline f32 (*shapeBillboardMatrix(GsShapeObject* object))[4] { return (f32 (*)[4])((u8*)object+0x470); }
#define BB_MATRIX shapeBillboardMatrix(self)
static inline f32 shapeDot2(f32 ax,f32 az,f32 bx,f32 bz) { return ax*bx+az*bz; }
static inline bool shapeBillboardYaw(GsShapeObject* self,f32 x,f32 depth) {
    Vec direction;
    Mtx rotationNegative;
    Mtx rotationPositive;
    direction.x=x; direction.y=0.0f; direction.z=depth;
    if((f32)fabs(direction.x)>0.00001f || (f32)fabs(direction.z)>0.00001f) {
        PSVECNormalize(&direction,&direction);
        f32 dot=shapeDot2(0.0f,1.0f,direction.x,direction.z);
        if(dot>=-1.0f && dot<=1.0f) {
            f32 angle=(f32)acos(dot);
            if(direction.x>0.0f) {
                PSMTXRotRad(rotationPositive,'Y',angle);
                PSMTXConcat(rotationPositive,BB_MATRIX,BB_MATRIX);
            } else {
                PSMTXRotRad(rotationNegative,'Y',-angle);
                PSMTXConcat(rotationNegative,BB_MATRIX,BB_MATRIX);
            }
            return true;
        }
    }
    return false;
}
static inline bool shapeBillboardFull(GsShapeObject* self,f32 x,f32 y,f32 depth) {
    Vec axis;
    Vec direction;
    Vec reference;
    Mtx rotation;
    reference.x=0.0f; reference.y=0.0f; reference.z=1.0f;
    direction.x=x; direction.y=y; direction.z=depth;
    if((f32)fabs(direction.x)>0.00001f || (f32)fabs(direction.y)>0.00001f || (f32)fabs(direction.z)>0.00001f) {
        PSVECNormalize(&direction,&direction);
        PSVECCrossProduct(&reference,&direction,&axis);
        if((f32)fabs(axis.x)>0.00001f || (f32)fabs(axis.y)>0.00001f || (f32)fabs(axis.z)>0.00001f) {
            PSVECNormalize(&axis,&axis);
            f32 dot=PSVECDotProduct(&reference,&direction);
            if(dot>=-1.0f && dot<=1.0f) {
                PSMTXRotAxisRad(rotation,&axis,(f32)acos(dot));
                PSMTXConcat(rotation,BB_MATRIX,BB_MATRIX);
                return true;
            }
        }
    }
    return false;
}
#pragma opt_common_subs off
extern "C" void MakeMatrixBillboard__13GsShapeObjectFP5GSmtxf(GsShapeObject* self,GSmtx* source,f32 depth) {
    f32 x=source->matrix[0][3];
    f32 y=source->matrix[1][3];
    f32 z=source->matrix[2][3];
    f32 scaleX=PSVECMag((Vec*)source->matrix[0]);
    f32 scaleY=PSVECMag((Vec*)source->matrix[1]);
    PSMTXScale(BB_MATRIX,scaleX,scaleY,PSVECMag((Vec*)source->matrix[2]));
    switch(*((u8*)self->entry+0xCD)) {
    case 1:
        PSMTXTransApply(BB_MATRIX,BB_MATRIX,x,y,z);
        break;
    case 2:
        if(!shapeBillboardYaw(self,-x,depth-z)) memcpy(BB_MATRIX,mtxIdent,0x30);
        PSMTXTransApply(BB_MATRIX,BB_MATRIX,x,y,z);
        break;
    case 3:
        if(!shapeBillboardFull(self,-x,-y,depth-z)) memcpy(BB_MATRIX,mtxIdent,0x30);
        PSMTXTransApply(BB_MATRIX,BB_MATRIX,x,y,z);
        break;
    }
}
#pragma opt_common_subs reset
#undef BB_MATRIX
