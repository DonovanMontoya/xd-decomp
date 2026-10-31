#include <game/menuFightStatusPrivate.hpp>
#include <libc/string.h>
struct MENU_POKEMON_STATUS {u8 pad0[0x16];u8 special,pad17;s16 maxHP,hp;u32 maxEXP,exp;union {u8 pad24[12];struct {u16 condition,face;u8 sex,side,pad2A[3],dark,pad2E[2];} details;};};
struct StatusTween {s16 hp,frames,timer;u16 levelUp;u32 exp;s16 expFrames,expTimer;};
static f32 menuStatusOldTime,menuStatusTime;
extern "C" {tagWINDOW_WORK *windowSearchID(s32);StatusTween *windowGetFreeWork(tagWINDOW_WORK*);MENU_POKEMON_STATUS *windowGetAllocPtr(tagWINDOW_WORK*);MENU_POKEMON_STATUS *windowAllocMemory(tagWINDOW_WORK*,s32);void GSthreadSwitch();void GSsndPlayNow(u32);void GSsndStopNow(u32);f32 timeGetLastFrameSec();u8 fightKind_CheckFightKind(s32);s32 menuFightGetStatus();void menuFightSetStatus(s32);void menuFightSetSeq();void *menuSeqBiosGetPtr(s32);}
static void menuUpdateStatusTime();
extern "C" {
s32 menuFightStatusWaitAnimeEXP(s32 id,u8 wait);
void menuFightStatusStartAnimEXP(s32 id,u32 exp);
s32 menuFightStatusWaitAnimeHP(s32 id,u8 wait);
void menuFightStatusStartAnimHP(s32 id,s16 hp);
void menuFightStatusSetActive();
void menuFightStatusSetHP(s32 id,s16 hp);
s32 menuFightStatusCtrl(tagWINDOW_WORK *w);
}
extern "C" void winSpriteSetDisp(tagSPRITE_WORK*,s32);
extern "C" void menuFightDrawCheckDark(tagWINDOW_WORK *w,tagSPRITE_WORK *sprite);

extern "C" {u16 *GSmsgGetGSchar(u32);void msgctrlSetValue(s32,u32);u32 GSmsgGetRect(u32);s32 winSpriteGetLayerID(tagWINDOW_WORK*,tagSPRITE_WORK*);void GSmsgPrint2(s32,s32,s32,u32,u32);DeckDarkPokemon *deckGetDeckDarkPokemon(u32);}
static s32 menuFightDrawDarkPanel(tagWINDOW_WORK *w,tagSPRITE_WORK *s,Pokemon *pokemon,MENU_POKEMON_STATUS*);

#include <dolphin/gx.h>

#pragma force_active on
struct GSgfxVF;
struct GSgfxLayer {
    u8 reserved[0xD34];u8 blendType;u8 reservedD35[3];u32 blendValue;
    u8 reservedD3C[0x16A8-0xD3C];u32 dirty;u32 pixelDirty;
    u8 reserved16B0[0x1760-0x16B0];u32 savedDirty;u32 savedPixelDirty;
    u8 reserved1768[0x1998-0x1768];u32 primitive;
    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
};
extern "C" {
u8 winSpriteGetDisp(tagSPRITE_WORK*);
void menuFaceDispFromID(tagWINDOW_WORK*,tagSPRITE_WORK*,u16);
s32 fightFloorGetStatus(void*,s32,s32,s32);
u8 menuCBBios_CurrentlyWorkingToolBattle();
void* fightFloorGetNowPtr();
void* fightFloorGetValidFightSidePtr(void*,u16);
void* fightSideGetValidFightTrainerPtr(void*,u16);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*,void*,void**,u8,u8);
u8 fightTrainerIsGcHero(void*);
Pokemon* fightOutPokemonGetPokemonPtr(void*);
void windowDrawSprite2(s16,s16,s16,s16,u32,tagWINDOW_WORK*,u16,s32,s32);
GSgfxLayer* GSgfxLayerFindByID(s32);
GSgfxVF* GSgfxVFBuildTemp(s32,s32,u8,u8,s32,s32,s32,s32,s32);
GSgfxVF* GSgfxVFGetPredef(s32);
u16 gamedataBiosGetFlag(s32,s32,s32);
s32 menuCloseSync(s32,s32);
s32 menuGetCursorItemID(s32);
double sin(double);
}
static inline void fifoPosition2s16(s16 x,s16 y){*(s16*)0xCC008000=x;*(s16*)0xCC008000=y;}
static inline void fifoColor1u32(u32 c){*(u32*)0xCC008000=c;}
static inline void fifoColor4u8(u8 r,u8 g,u8 b,u8 a){*(u8*)0xCC008000=r;*(u8*)0xCC008000=g;*(u8*)0xCC008000=b;*(u8*)0xCC008000=a;}
extern "C" void menuFightDrawParam(tagWINDOW_WORK* w,tagSPRITE_WORK* s);




s32 menuFightStatusWaitAnimeEXP(s32 id,u8 wait){for(;;){tagWINDOW_WORK *w=windowSearchID(id);if(!w)return 0;if(windowGetFreeWork(w)->expFrames==0)return 0;if(wait)GSthreadSwitch();else return 1;}}

void menuFightStatusStartAnimEXP(s32 id,u32 exp){tagWINDOW_WORK *w=windowSearchID(id);if(w){MENU_POKEMON_STATUS *status=windowGetAllocPtr(w);StatusTween *t=windowGetFreeWork(w);u32 diff;if(exp>status->exp)diff=exp-status->exp;else diff=status->exp-exp;t->expFrames=(s16)((diff*100)/status->maxEXP);if(t->expFrames<15)t->expFrames=15;t->exp=status->exp;status->exp=exp;t->expTimer=0;if(exp==status->maxEXP)t->levelUp=1;GSsndPlayNow(0x24);}}

s32 menuFightStatusWaitAnimeHP(s32 id,u8 wait){for(;;){tagWINDOW_WORK *w=windowSearchID(id);if(!w)return 0;if(windowGetFreeWork(w)->frames==0)return 0;if(wait)GSthreadSwitch();else return 1;}}

void menuFightStatusStartAnimHP(s32 id,s16 hp){tagWINDOW_WORK *w=windowSearchID(id);if(w){MENU_POKEMON_STATUS *status=windowGetAllocPtr(w);StatusTween *t=windowGetFreeWork(w);s32 diff=status->hp-hp;if(diff<0)diff=-diff;t->frames=(s16)((diff*100)/status->maxHP);if(t->frames<=0)t->frames=1;t->hp=status->hp;status->hp=hp;t->timer=0;}}

void menuFightStatusSetActive(){}

void menuFightStatusSetHP(s32 id,s16 hp){tagWINDOW_WORK *w=windowSearchID(id);if(w)windowGetAllocPtr(w)->hp=hp;}

extern "C" void menuFightDrawParam(tagWINDOW_WORK* w,tagSPRITE_WORK* s){
    static f32 cFlash=0.0f;
    s32 exp;
    MENU_POKEMON_STATUS* status;
    s32 active;
    u32 message;
    u32 color;
    void* pokemon[6];
    s32 maxExp;
    s16 hp;
    s16 alternate;
    u8 fade;
    f32 value;
    u32 phase;
    f32 hpf;
    s16 oldWidth;
    void* trainer;
    u8 flash;
    u32 oldColor;
    u16 sprite;
    s32 cursor;
    f32 fraction;
    s16 width;
    StatusTween* tween;
    s16 x;
    f32 maxf;
    GSgfxLayer* layer;
    status=windowGetAllocPtr(w);
    tween=windowGetFreeWork(w);
    alternate=0;
    menuFightDrawCheckDark(w,s);
    if(winSpriteGetDisp(s)==0)return;
    color=w->alpha|0xFFFFFF00;
    switch(s->id){
    case 0xD5:case 0xD6:case 0xEF:
        if(status->details.side==2)winSpriteSetDisp(s,0);break;
    case 0xD7:case 0xD8:case 0xF0:
        if(status->details.side==2)winSpriteSetDisp(s,1);else winSpriteSetDisp(s,0);break;
    case 0xD2:case 0xED:menuFaceDispFromID(w,s,status->details.face);break;
    case 0xF4:alternate=1;
    case 0xE8:
        if(fightFloorGetStatus(0,0,0x32,0)==0||alternate==0){
            if(tween->frames){value=((f32)tween->timer/(f32)tween->frames)*(f32)(status->hp-tween->hp)+(f32)tween->hp;hp=value;if(hp==0&&value>0.0f)hp=1;}else hp=status->hp;
            GSmsgPrint2(winSpriteGetLayerID(w,s),32,0,color,0x42C2);
            msgctrlSetValue(0x5F,hp);x=24-(s16)(GSmsgGetRect(0x4272)>>16);
            GSmsgPrint2(winSpriteGetLayerID(w,s),x,1,color,0x4272);
            msgctrlSetValue(0x5F,status->maxHP);width=GSmsgGetRect(0x4272)>>16;
            GSmsgPrint2(winSpriteGetLayerID(w,s),(s16)(s->width-width),1,color,0x4272);
        }break;
    case 0xEA:case 0xF7:winSpriteSetDisp(s,1);if(status->details.dark)winSpriteSetDisp(s,0);break;
    case 0xE9:case 0xF5:
        if(status->details.dark==0){
            if(menuCBBios_CurrentlyWorkingToolBattle()==0&&status->details.side!=0){
                trainer=fightSideGetValidFightTrainerPtr(fightFloorGetValidFightSidePtr(fightFloorGetNowPtr(),0),0);
                fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(),trainer,pokemon,0,0);
                if(w->menu==0x37){
                    if(fightTrainerIsGcHero(trainer)!=0)goto drawLevel;
                    fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(),trainer,pokemon,1,0);
                    if(menuFightDrawDarkPanel(w,s,fightOutPokemonGetPokemonPtr(pokemon[0]),status))break;
                    goto drawLevel;
                }else if(w->menu==0x40){
                    if(fightTrainerIsGcHero(trainer)!=0)goto drawLevel;
                    if((s32)fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(),trainer,pokemon,1,0)==1){
                        if(menuFightDrawDarkPanel(w,s,fightOutPokemonGetPokemonPtr(pokemon[0]),status))break;
                    }else if(menuFightDrawDarkPanel(w,s,fightOutPokemonGetPokemonPtr(pokemon[1]),status))break;
                    goto drawLevel;
                }else if(w->menu==0x38){
                    fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(),trainer,pokemon,0,0);
                    if(menuFightDrawDarkPanel(w,s,fightOutPokemonGetPokemonPtr(pokemon[0]),status))break;
                    goto drawLevel;
                }else if(w->menu==0x41){
                    if((s32)fightFloorGetFightTrainerFightOutPokemonPtrAry(fightFloorGetNowPtr(),trainer,pokemon,0,0)==1){
                        if(menuFightDrawDarkPanel(w,s,fightOutPokemonGetPokemonPtr(pokemon[0]),status))break;
                    }else if(menuFightDrawDarkPanel(w,s,fightOutPokemonGetPokemonPtr(pokemon[1]),status))break;
                    goto drawLevel;
                }else goto drawLevel;
            }else{
drawLevel:
                msgctrlSetValue(0x5F,status->pad17);width=GSmsgGetRect(0x4272)>>16;
                GSmsgPrint2(winSpriteGetLayerID(w,s),(s16)(s->width-width),1,w->alpha|0xFFFFFF00,0x4272);
            }
        }break;
    case 0xE7:case 0xF3:
        msgctrlSetValue(0x37,(u32)status);GSmsgPrint2(winSpriteGetLayerID(w,s),0,1,color,0x4279);
        x=(GSmsgGetRect(0x4279)>>16)+4;
        switch(status->details.sex){case 0:message=0x9C5;break;case 1:message=0x9C6;break;case 2:default:message=0;break;}
        if(message){msgctrlSetValue(0x37,(u32)GSmsgGetGSchar(message));GSmsgPrint2(winSpriteGetLayerID(w,s),x,0,color,0x4278);}break;
    case 0xEB:case 0xF8:windowDrawSprite2(0,0,s->width,s->height,color,w,status->details.condition,0,winSpriteGetLayerID(w,s));break;
    case 0xDA:case 0xF2:
        layer=GSgfxLayerFindByID(winSpriteGetLayerID(w,s));
        if(layer){
            if(tween->frames)hpf=((f32)tween->timer/(f32)tween->frames)*(f32)(status->hp-tween->hp)+(f32)tween->hp;else hpf=status->hp;
            maxf=status->maxHP;
            if(tween->frames){
                if(tween->hp<=0)oldColor=0;else if((f32)tween->hp<=20.0f*maxf/100.0f)oldColor=0x80000000;else if((f32)tween->hp<=50.0f*maxf/100.0f)oldColor=0x64640000;else oldColor=0x00800000;
                oldColor|=w->alpha;
                oldWidth=((maxf-1.0f)+(f32)(tween->hp*s->width))/maxf;
                layer->primitive=0x98;layer->setRenderStateAndSelect(GSgfxVFBuildTemp(0,3,0,0,1,5,0,0,0));layer->beginSurface(4);
                fifoPosition2s16(0,0);fifoColor1u32(oldColor);
                fifoPosition2s16(oldWidth,0);fifoColor1u32(oldColor);
                fifoPosition2s16(0,s->height);fifoColor1u32(oldColor);
                fifoPosition2s16(oldWidth,s->height);fifoColor1u32(oldColor);layer->endSurface();
            }
            if(hpf<=0.0f)sprite=0;else if(hpf<=20.0f*maxf/100.0f)sprite=0xA0;else if(hpf<=50.0f*maxf/100.0f)sprite=0x9F;else sprite=0x90;
            width=(hpf*(f32)s->width+(maxf-1.0f))/maxf;
            if(sprite)windowDrawSprite2(0,0,width,s->height,color,w,sprite,0,winSpriteGetLayerID(w,s));
        }break;
    case 0xDC:
        if(tween->expFrames)exp=((f32)tween->expTimer/(f32)tween->expFrames)*(f32)(status->exp-tween->exp)+(f32)tween->exp;else exp=status->exp;
        maxExp=status->maxEXP;if(exp>maxExp)exp=maxExp;
        if(maxExp>0){
            exp=maxExp+exp*s->width;
            width=(exp-1)/maxExp;
            if(width){cFlash=0.0f;windowDrawSprite2(0,0,width,s->height,color,w,0x92,0,winSpriteGetLayerID(w,s));}
            else if(tween->levelUp){
                windowDrawSprite2(0,0,s->width,s->height,color,w,0x92,0,winSpriteGetLayerID(w,s));
                layer=GSgfxLayerFindByID(winSpriteGetLayerID(w,s));flash=255.0f-254.0f*cFlash;
                layer->primitive=0x80;
                layer->blendType=6;layer->blendValue=0;layer->pixelDirty|=4;layer->dirty|=1;layer->savedPixelDirty|=4;layer->savedDirty|=1;
                layer->setRenderStateAndSelect(GSgfxVFGetPredef(3));layer->beginSurface(4);
                fifoPosition2s16(0,0);fifoColor4u8(flash,flash,flash,flash);
                fifoPosition2s16(s->width,0);fifoColor4u8(flash,flash,flash,flash);
                fifoPosition2s16(s->width,s->height);fifoColor4u8(flash,flash,flash,flash);
                fifoPosition2s16(0,s->height);fifoColor4u8(flash,flash,flash,flash);layer->endSurface();
                cFlash+=timeGetLastFrameSec();if(1.0<=cFlash){cFlash=1.0f;tween->levelUp=0;}
            }
        }break;
    case 0xE6:fraction=*(f32*)&status->exp / *(f32*)&status->maxEXP;if(fraction<0.2f)width=(f32)s->width*(fraction/0.2f);else width=s->width;if(width<0)width=0;windowDrawSprite2(0,0,width,s->height,color,w,0x91,0,winSpriteGetLayerID(w,s));break;
    case 0xE5:fraction=*(f32*)&status->exp / *(f32*)&status->maxEXP;if(fraction<0.4f)width=(f32)s->width*((fraction-0.2f)/0.2f);else width=s->width;if(width<0)width=0;windowDrawSprite2(0,0,width,s->height,color,w,0x91,0,winSpriteGetLayerID(w,s));break;
    case 0xE4:fraction=*(f32*)&status->exp / *(f32*)&status->maxEXP;if(fraction<0.6f)width=(f32)s->width*((fraction-0.4f)/0.2f);else width=s->width;if(width<0)width=0;windowDrawSprite2(0,0,width,s->height,color,w,0x91,0,winSpriteGetLayerID(w,s));break;
    case 0xE3:fraction=*(f32*)&status->exp / *(f32*)&status->maxEXP;if(fraction<0.8f)width=(f32)s->width*((fraction-0.6f)/0.2f);else width=s->width;if(width<0)width=0;windowDrawSprite2(0,0,width,s->height,color,w,0x91,0,winSpriteGetLayerID(w,s));break;
    case 0xE2:fraction=*(f32*)&status->exp / *(f32*)&status->maxEXP;if(fraction<1.0f)width=(f32)s->width*((fraction-0.8f)/0.2f);else width=s->width;if(width<0)width=0;windowDrawSprite2(0,0,width,s->height,color,w,0x91,0,winSpriteGetLayerID(w,s));break;
    case 0xF6:winSpriteSetDisp(s,0);if(gamedataBiosGetFlag(0,14,0)!=0)winSpriteSetDisp(s,1);break;
    case 0xD1:alternate=1;
    case 0xD0:case 0xEC:
        active=0;winSpriteSetDisp(s,0);
        if(menuCloseSync(0x5C,0)!=0){
            cursor=menuGetCursorItemID(0x5C);
            switch(w->menu){case 0x37:if(cursor==0x138)active=1;break;case 0x40:if(cursor==0x139)active=1;break;case 0x38:if(cursor==0x13A)active=1;break;case 0x41:if(cursor==0x13B)active=1;break;}
            phase=(u32)(100.0f*menuStatusTime)%100;s->color.value=0xFFFFFFFF;
            fade=200.0f*(f32)sin(3.14f*(0.01f*(f32)phase));
            s->color.channels.green-=fade;s->color.channels.blue-=fade;
            if(active){if(alternate){if(fightFloorGetStatus(0,0,0x32,0)!=0)winSpriteSetDisp(s,1);}else winSpriteSetDisp(s,1);}
        }break;
    }
}

static s32 menuFightDrawDarkPanel(tagWINDOW_WORK *w,tagSPRITE_WORK *s,Pokemon *pokemon,MENU_POKEMON_STATUS*){if(pokemon && pokemon->isDarkPokemon()){msgctrlSetValue(0x37,(u32)GSmsgGetGSchar(0x4443));s16 width=GSmsgGetRect(0x4278)>>16;GSmsgPrint2(winSpriteGetLayerID(w,s),(s16)(s->width-width),0,w->alpha|0xFFFFFF00,0x4278);msgctrlSetValue(0x5F,deckGetDeckDarkPokemon(pokemon->getDarkPokemon()->getDarkPokemonID())->getPlayerLevel());s16 x=(s->width-width)-(GSmsgGetRect(0x4272)>>16);GSmsgPrint2(winSpriteGetLayerID(w,s),x,1,w->alpha|0xFFFFFF00,0x4272);return 1;}return 0;}

extern "C" void menuFightDrawCheckDark(tagWINDOW_WORK *w,tagSPRITE_WORK *sprite){MENU_POKEMON_STATUS *status=windowGetAllocPtr(w);s16 id=sprite->id;u8 special=status->special;s32 show=1;switch(id){case 0xD3:case 0xD4:case 0xDB:case 0xDC:case 0xEE:if(status->pad24[5])show=0;else show=1;break;case 0xD5:case 0xD6:case 0xDD:case 0xDE:case 0xDF:case 0xE0:case 0xE1:case 0xE2:case 0xE3:case 0xE4:case 0xE5:case 0xE6:case 0xEF:if(status->pad24[5])show=1;else show=0;break;}switch(id){case 0xD4:case 0xD6:case 0xDB:case 0xDC:case 0xDD:case 0xDE:case 0xDF:case 0xE0:case 0xE1:case 0xE2:case 0xE3:case 0xE4:case 0xE5:case 0xE6:if(special==1)show=0;break;}winSpriteSetDisp(sprite,show);}

s32 menuFightStatusCtrl(tagWINDOW_WORK *w){StatusTween *t=windowGetFreeWork(w);u32 reset=0;if(w->phase==0){MENU_POKEMON_STATUS *status=windowAllocMemory(w,0x30);if(status){memcpy(status,(void*)w->parameters[0],0x30);if(fightKind_CheckFightKind(13))status->special=1;if(fightKind_CheckFightKind(14))status->special=1;if(fightKind_CheckFightKind(15))status->special=1;if(menuFightGetStatus())menuFightSetSeq();}}else if(w->phase==1 && menuFightGetStatus()){if(*(void**)((u8*)w+0x2C)==menuSeqBiosGetPtr(0x1A5))reset=1;if(*(void**)((u8*)w+0x2C)==menuSeqBiosGetPtr(0x1A9))reset=1;if(reset)menuFightSetStatus(0);}windowGetAllocPtr(w);if(t->frames){t->timer+= (s32)(60.0f*timeGetLastFrameSec());if(t->timer>t->frames)t->frames=0;}if(t->expFrames){t->expTimer+=(s32)(60.0f*timeGetLastFrameSec());if(t->expTimer>t->expFrames){t->expFrames=0;GSsndStopNow(0x24);}}menuUpdateStatusTime();return 0;}

static void menuUpdateStatusTime(){f32 time=timeGetLastFrameSec();if(time!=menuStatusOldTime){menuStatusOldTime=time;menuStatusTime+=time;}}

#pragma force_active reset
