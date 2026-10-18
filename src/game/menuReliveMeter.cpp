#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>
extern "C" double sin(double);
class DarkPokemon {public:s32 getInitDarkPointDirect()const;s32 getDarkPointDirect()const;};
class Pokemon {public:bool isDarkPokemon()const;DarkPokemon *getDarkPokemon();};
class GSgfxLayer;
static f32 meterCount;
static f32 max_alpha=255.0f;
extern "C" {f32 timeGetLastFrameSec();}
static void _menuDrawReliveMeterSubDpValue(long,long,long,long,long,long,u8,GSgfxLayer*);
static void _menuDrawReliveMeterSub(DarkPokemon *p,long x,long y,long width,long height,u8 alpha,GSgfxLayer *layer){s32 max=p->getInitDarkPointDirect();s32 current=p->getDarkPointDirect();_menuDrawReliveMeterSubDpValue(max,current,x,y,width,height,alpha,layer);}
extern "C" void menuDrawReliveMeter3(Pokemon *pokemon,s32 x,s32 y,s32 width,s32 height,u8 alpha,s32 layerID){GSgfxLayer *layer=GSgfxLayerFindByID(layerID);if(layer)_menuDrawReliveMeterSub(pokemon->getDarkPokemon(),x,y,width,height,alpha,layer);}
extern "C" void menuDrawReliveMeterByDarkPokemon(DarkPokemon *p,s32 x,s32 y,s32 width,s32 height,u8 alpha,s32 layerID){GSgfxLayer *layer=GSgfxLayerFindByID(layerID);if(layer)_menuDrawReliveMeterSub(p,x,y,width,height,alpha,layer);}
extern "C" void menuDrawReliveMeter(Pokemon *pokemon,s32 width,s32 height,s32 layerID){if(pokemon->isDarkPokemon()){GSgfxLayer *layer=GSgfxLayerFindByID(layerID);if(layer)_menuDrawReliveMeterSub(pokemon->getDarkPokemon(),0,0,width,height,255,layer);}}
extern "C" void menuDrawReliveUpdate(){meterCount+=timeGetLastFrameSec();}

static inline void meterVertex(s16 x,s16 y,const GXColor& color) {
    *(volatile s16*)0xcc008000=x; *(volatile s16*)0xcc008000=y;
    *(volatile u8*)0xcc008000=color.r; *(volatile u8*)0xcc008000=color.g;
    *(volatile u8*)0xcc008000=color.b; *(volatile u8*)0xcc008000=color.a;
}
static inline void meterRect(GSgfxLayer* layer,s16 x,s16 y,s16 right,s16 bottom,GXColor color) {
    layer->primitive=0x80; layer->setLineWidth(6,0);
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(3)); layer->beginSurface(4);
    meterVertex(x,y,color);meterVertex(right,y,color);meterVertex(right,bottom,color);meterVertex(x,bottom,color);
    layer->endSurface();
}
static inline void meterLine(GSgfxLayer* layer,s16 x,s16 y,s16 right,s16 bottom,GXColor color) {
    layer->primitive=0xa8;layer->setLineWidth(6,0);
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(3));layer->beginSurface(2);
    meterVertex(x,y,color);meterVertex(right,bottom,color);layer->endSurface();
}
static void _menuDrawReliveMeterSubDpValue(long maximum,long current,long x,long y,long width,long height,u8 alpha,GSgfxLayer* layer) {
    if(!maximum)return;
    s32 gap=2;
    s32 scale=width*100/210;
    s32 segment=scale*40/100;
    s32 h=(height*100/16)*14/100;
    if(scale<50)gap/=2;
    GXColor color;
    color.b=0;color.g=0;color.r=0;color.a=alpha;
    meterRect(layer,x,y,segment*5+(gap*4+2+x),h+y+2,color);
    color.b=117;color.g=117;color.r=117;color.a=alpha;
    for(s32 i=0,offset=0;i<5;i++,offset+=segment+gap)
        meterRect(layer,offset+x+1,y+1,offset+x+1+segment,y+h+1,color);
    if(current) {
        s32 percent=current*100/maximum;
        s32 count=percent/20+1;
        if(count>5)count=5;
        color.r=134;color.g=0;color.b=225;color.a=alpha;
        for(s32 i=0,used=0,offset=0;i<count;i++,used+=20,offset+=segment+gap) {
            color.r=134;color.g=0;color.b=225;color.a=alpha;
            if(count==i+1) {
                percent-=used;
                meterRect(layer,offset+1+x,y+1,offset+1+x+segment*percent/20,y+h+1,color);
                color.r=174;color.g=54;color.b=225;color.a=alpha;
                meterLine(layer,offset+1+x,y+2,offset+1+x+segment*percent/20,y+2,color);
                color.r=108;color.g=0;color.b=181;color.a=alpha;
                meterLine(layer,offset+1+x,y+h+1,offset+1+x+segment*percent/20,y+h+1,color);
            } else {
                meterRect(layer,offset+1+x,y+1,offset+1+x+segment,y+h+1,color);
                color.r=174;color.g=54;color.b=225;color.a=alpha;
                meterLine(layer,offset+1+x,y+2,offset+1+x+segment,y+2,color);
                color.r=108;color.g=0;color.b=181;color.a=alpha;
                meterLine(layer,offset+1+x,y+h+1,offset+1+x+segment,y+h+1,color);
            }
        }
        return;
    }
    color.b=255;color.g=255;color.r=255;
    f32 fade=150.0f*(1.0f+(f32)sin(6.2831855f*meterCount));
    if(fade>=max_alpha)fade=max_alpha;
    u16 intensity=(u16)(s32)fade*alpha/255;
    for(s32 i=0,offset=0;i<5;i++,offset+=segment+gap) {
        color.a=intensity;
        meterRect(layer,offset+1+x,y+1,offset+1+x+segment,y+h+1,color);
        color.a=intensity*75/100;
        meterLine(layer,offset+1+x,y+1,offset+1+x+segment,y+1,color);
        meterLine(layer,offset+2+x,y+1,offset+2+x,y+h+1,color);
        meterLine(layer,offset+1+segment+x,y+1,offset+1+segment+x,y+h+1,color);
        meterLine(layer,offset+1+x,y+h+1,offset+1+x+segment,y+h+1,color);
    }
}
