#pragma defer_codegen on
#include <global.h>

extern "C" { void underTakerMenuResore(); }
extern "C" { u32 underTakerGetMiraboPlace(); }
extern "C" { void underTakerCallBackFunc(s32, s32, u16 steps); }
extern "C" { void underTakerMiraboDisAppear(); }
extern "C" { static void _appearMirabo__Fv(); }
extern "C" { s32 undertakerGetPlace(s32 *output); }
extern "C" { void undertakerSetPlace(s32 place); }
extern "C" { s32 undertakerGetStartFlagID(); }
struct UnderTakerPlace {u16 weight,place;u32 unused;};
struct UnderTakerData {u16 interval,increase,decrease,randomMax,maximum,duration;s32 startFlag,stepFlag,countFlag,placeFlag,timeFlag,endFlag;u32 unused,progressFirst,progressLast;s32 sideFlag;UnderTakerPlace places[7];};
struct WorldmapXD {u8 pad[0x94];s32 firstFlag;u8 pad2[0x190-0x98];s32 secondFlag;};
extern "C" {
extern UnderTakerData *undertakerdata;extern WorldmapXD *worldmapXD_data;extern u8 *flag_etc;
u32 GSflagGet(s32);void GSflagSet(s32,u32);u8 GSflagTest(s32);s32 HSD_Rand();u8 darkpokemonCheckUnderTaker();u16 esabaGetPokemonID(s32);u32 floorGetCurrent();void heroMoveInitEvent();void heroMoveSetColision(s32);void heroMoveTermEvent();void GSthreadSwitch();void menuIntUnderTakerMenuClose();void menuIntUnderTakerMenuOpen();void winMsgOpen(s32,s32,s32,s32);void winMsgClose(s32);
static void _appearMirabo__Fv();
}
static inline u8 progressBlocked(){u32 progress=GSflagGet(0x3C4);if(progress>=((u32*)(flag_etc+8))[undertakerdata->progressFirst*8]&&progress<=((u32*)(flag_etc+8))[undertakerdata->progressLast*8])return 1;return 0;}
static inline u8 firstAvailable(){u32 floor=floorGetCurrent();if(GSflagTest(worldmapXD_data->firstFlag)&&floor!=0x71)return 1;return 0;}
static inline u8 secondAvailable(){u32 floor=floorGetCurrent();s32 flag=worldmapXD_data->secondFlag;if(GSflagTest(0x8D1)&&GSflagTest(flag)&&floor!=0x3B)return 1;return 0;}
static inline UnderTakerPlace *getPlace(s32 index){if(index>=7)return 0;return &undertakerdata->places[index];}
static inline void freeSpot(u32 *out){s32 available[3];s32 places[3]={90,91,92};s32 count=0;for(s32 i=0;i<=2;i++){if(esabaGetPokemonID(i)==0)available[count++]=i;}if(count==0){*out=0;return;}*out=places[available[(u16)((u16)HSD_Rand()%count)]];}
extern "C" {

static inline void disappearMessage(){underTakerMiraboDisAppear();heroMoveInitEvent();heroMoveSetColision(1);winMsgOpen(3,0x3E85,1,1);winMsgClose(1);heroMoveTermEvent();}
static inline void announceMirabo(){heroMoveInitEvent();heroMoveSetColision(1);GSthreadSwitch();menuIntUnderTakerMenuOpen();winMsgOpen(3,0x3E84,1,1);winMsgClose(1);menuIntUnderTakerMenuClose();heroMoveTermEvent();}

}

#pragma force_active on
extern "C" {
s32 undertakerGetStartFlagID(){return undertakerdata->startFlag;}
}
extern "C" {
void undertakerSetPlace(s32 place){GSflagSet(undertakerdata->placeFlag,place);GSflagSet(undertakerdata->timeFlag,0);u16 r=HSD_Rand();u8 side=r%2;GSflagSet(undertakerdata->sideFlag,side);announceMirabo();}
}
extern "C" {
s32 undertakerGetPlace(s32 *output){s32 count=0;if(GSflagTest(undertakerdata->startFlag)&&!GSflagTest(undertakerdata->endFlag)&&darkpokemonCheckUnderTaker()){s32 places[7];s32 i=0;UnderTakerPlace *place;for(;;){place=getPlace(i);if(!place)break;places[i]=place->place;i++;}output[count++]=0;if(!firstAvailable())output[count++]=places[0];if(!secondAvailable())output[count++]=places[1];for(s32 j=0;j<=2;j++){if(esabaGetPokemonID(j)==0)output[count++]=places[j+2];}}return count;}
}
extern "C" {
static void _appearMirabo__Fv(){u32 selected;u16 total=0;s32 i=0;UnderTakerPlace *place;for(;;){place=getPlace(i);if(!place)break;total+=place->weight;i++;}u16 random=(u16)HSD_Rand()%total;u16 cumulative=0;i=0;for(;;){place=getPlace(i);if(!place)break;cumulative+=place->weight;if(random<cumulative){selected=place->place;break;}i++;}u32 current=floorGetCurrent();if(selected==undertakerdata->places[0].place){if(!firstAvailable())freeSpot(&selected);}else if(selected==undertakerdata->places[1].place){if(!secondAvailable()){if(firstAvailable())selected=undertakerdata->places[0].place;else selected=0;if(!selected)freeSpot(&selected);}}else if(selected==undertakerdata->places[2].place){if(esabaGetPokemonID(0)||current==selected){if(firstAvailable())selected=undertakerdata->places[0].place;else selected=0;}}else if(selected==undertakerdata->places[3].place){if(esabaGetPokemonID(1)||current==selected){if(firstAvailable())selected=undertakerdata->places[0].place;else selected=0;}}else if(selected==undertakerdata->places[4].place&&(esabaGetPokemonID(2)||current==selected)){if(firstAvailable())selected=undertakerdata->places[0].place;else selected=0;}if(selected){GSflagSet(undertakerdata->placeFlag,selected);GSflagSet(undertakerdata->timeFlag,0);u16 r=HSD_Rand();u8 side=r%2;GSflagSet(undertakerdata->sideFlag,side);announceMirabo();return;}GSflagSet(undertakerdata->stepFlag,0);GSflagSet(undertakerdata->countFlag,(u16)(undertakerdata->maximum-2));}
}
extern "C" {
void underTakerMiraboDisAppear(){GSflagSet(undertakerdata->placeFlag,0);GSflagSet(undertakerdata->stepFlag,0);GSflagSet(undertakerdata->countFlag,0);menuIntUnderTakerMenuClose();}
}
extern "C" {
void underTakerCallBackFunc(s32, s32, u16 steps) {
    if (GSflagTest(undertakerdata->startFlag) &&
        !GSflagTest(undertakerdata->endFlag) && darkpokemonCheckUnderTaker()) {
        if (GSflagGet(undertakerdata->placeFlag) == 0) {
            u16 total;
            u32 count;
            u16 increase;
            u16 divisor;
            u32 elapsed = (u16)GSflagGet(undertakerdata->stepFlag);
            elapsed = elapsed + (u16)steps;
            if ((u16)elapsed >= undertakerdata->interval) {
                increase = undertakerdata->increase;
                total = increase + undertakerdata->decrease;
                divisor = undertakerdata->randomMax;
                u16 random = (u16)HSD_Rand() % divisor;
                if (random < increase) {
                    count = (u16)GSflagGet(undertakerdata->countFlag) + 1;
                    if ((s32)(u16)count >= undertakerdata->maximum - 1) {
                        if (progressBlocked()) count--;
                        else _appearMirabo__Fv();
                    }
                    GSflagSet(undertakerdata->countFlag, (u16)count);
                } else if (random < total) {
                    count = (u16)GSflagGet(undertakerdata->countFlag);
                    if ((u16)count) count--;
                    GSflagSet(undertakerdata->countFlag, (u16)count);
                }
                elapsed = (elapsed - undertakerdata->interval) & 0xffff;
            }
            GSflagSet(undertakerdata->stepFlag, (u16)elapsed);
            return;
        }
        if (progressBlocked()) {
            disappearMessage();
            return;
        }
        u32 elapsed = (u16)GSflagGet(undertakerdata->timeFlag);
        elapsed = elapsed + (u16)steps;
        if ((u16)elapsed >= undertakerdata->duration) disappearMessage();
        GSflagSet(undertakerdata->timeFlag, (u16)elapsed);
    }
}
}
extern "C" {
u32 underTakerGetMiraboPlace(){return GSflagGet(undertakerdata->placeFlag);}
}
extern "C" {
void underTakerMenuResore(){}
}
