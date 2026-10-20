#include <global.h>
extern "C" {
extern u8 fight_abicnt_data[];
extern u32 fight_abicnt_data_number;
void* fightAbicntDataBiosGetPtr(u16);
u32 fightAbicntDataBiosGetWaru(void*);
u8 fightAbicntDataBiosGetKake(u8*);
u32 fightAbicntGetWaru(u16);
u8 fightAbicntGetKake(u16);
s32 fightAbicntFitMinMax(s32 x){if(x<0)x=0;if(x>12)return 12;return x;}
u32 fightAbicntDoKakeWaru(u16 a,u32 b){u8 w=fightAbicntGetWaru(a);return (b*fightAbicntGetKake(a))/w;}
u32 fightAbicntGetWaru(u16 id){void* p=fightAbicntDataBiosGetPtr(id);u8 r=1;if(p==0)return r;return fightAbicntDataBiosGetWaru(p);}
u8 fightAbicntGetKake(u16 id){void* p=fightAbicntDataBiosGetPtr(id);u8 r=0;if(p==0)return r;return fightAbicntDataBiosGetKake((u8*)p);}
u32 fightAbicntDataBiosGetWaru(void* p){if(p==0)return 1;return *((u8*)p+1);}
u8 fightAbicntDataBiosGetKake(u8* p){if(p==0)return 0;return *p;}
void* fightAbicntDataBiosGetPtr(u16 i){if(i>=fight_abicnt_data_number)return 0;return fight_abicnt_data+i*2;}
}
