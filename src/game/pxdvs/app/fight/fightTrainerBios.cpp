#include <global.h>
struct EnemyStoredMoves { u8 reserved[4]; s16 ids[5]; };
struct EnemyExpectedMoves { u8 reserved[12]; s16 ids[9]; };
extern "C" {
extern s32 fight_trainer_kind_data;
extern u32* fight_trainer_kind_data_number;
extern s32 fight_trainer_ai_value_addsub_data;
extern u32* fight_trainer_ai_value_addsub_data_number;
extern s32 fight_trainer_pokemon_part_data;
extern u32* fight_trainer_pokemon_part_data_number;
extern void* getDeckTrainerAIObj__13DeckTrainerAIFUl(u32);
extern void* getDeckTrainerObj__11DeckTrainerFUl(u32);
#pragma push
#pragma peephole off
s32 fightTrainerKindDataBiosGetBgmSndId(void* p) { if (p == 0) { return 0; } else { return *(s32*)((u8*)p+8); } }
#pragma pop
#pragma push
#pragma peephole off
s32 fightTrainerKindDataBiosGetPrefixName(void* p) { if (p == 0) { return 0; } else { return *(s32*)((u8*)p+4); } }
#pragma pop
#pragma push
#pragma peephole off
u16 fightTrainerKindDataBiosGetSyoukinBairitu(u16* p) { if (p == 0) { return 0; } else { return *p; } }
#pragma pop
s32 fightTrainerKindDataBiosGetPtr(u16 id) { if (id >= *fight_trainer_kind_data_number) return 0; return fight_trainer_kind_data + id*0xC; }
void fightTrainerEnemyPokemonBiosSetParam1bantakaiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x24)=v;}
void fightTrainerEnemyPokemonBiosSetBadwazaHaveFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x23)=v;}
void fightTrainerEnemyPokemonBiosSetDefense1banhikuiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x22)=v;}
void fightTrainerEnemyPokemonBiosSetLv1banhikuiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x21)=v;}
void fightTrainerEnemyPokemonBiosSetNowhp1banhikuiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x20)=v;}
void fightTrainerEnemyPokemonBiosSetStoreTokuseiData(void* p,s16 v){if(p)*(s16*)((u8*)p+0x1e)=v;}
void fightTrainerEnemyPokemonBiosSetTokuseiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x1c)=v;}
void fightTrainerEnemyPokemonBiosSetExpectWazaDataId(EnemyExpectedMoves* p,u8 i,s16 v){if(p&&i<=8)p->ids[i]=v;}
void fightTrainerEnemyPokemonBiosSetStoreWazaDataId(EnemyStoredMoves* p,u8 i,s16 v){if(p&&i<=4)p->ids[i]=v;}
void fightTrainerEnemyPokemonBiosSetExpectWazaNum(void* p,s8 v){if(p)*(s8*)((u8*)p+3)=v;}
void fightTrainerEnemyPokemonBiosSetStoreWazaNum(void* p,s8 v){if(p)*(s8*)((u8*)p+2)=v;}
void fightTrainerEnemyPokemonBiosSetFightEntryeId(s16* p,s16 v){if(p)*p=v;}
#pragma push
#pragma peephole off
s16 fightTrainerEnemyPokemonBiosGetFightEntryeId(s16* p){if(p==0){return 0;}else{return *p;}}
#pragma pop
s32 fightTrainerAiValueAddsubDataBiosGetPtr(u16 id){if(id>=*fight_trainer_ai_value_addsub_data_number)return 0;return fight_trainer_ai_value_addsub_data+id*0x14;}
s32 fightTrainerPokemonPartDataBiosGetPtr(u16 id){if(id>=*fight_trainer_pokemon_part_data_number)return 0;return fight_trainer_pokemon_part_data+id*0x18;}
void* fightTrainerAiDataBiosGetPtr(u16 id){return getDeckTrainerAIObj__13DeckTrainerAIFUl(id);}
void* fightTrainerDataBiosGetPtr(u16 id) {
    switch (id) {
    case 5000: id = 1; break;
    case 5001: case 5003: case 5005: id = 2; break;
    case 5002: case 5004: case 5006: id = 3; break;
    }
    return getDeckTrainerObj__11DeckTrainerFUl(id);
}
#pragma push
#pragma peephole off
u8 fightTrainerBiosGetControllerId(void* p){if(p==0){return 0;}else{return *(u8*)((u8*)p+0x3540);}}
#pragma pop
s32 fightTrainerBiosGetFightPokemonPtr(s32 p,u16 i){if(!p)return 0;if(i>=6)return 0;return p+i*0x300+0x97c;}
#pragma push
#pragma peephole off
s32 fightTrainerBiosGetHeroPtr(u32 p){if(p==0){return 0;}else{return p+4;}}
#pragma pop
}
