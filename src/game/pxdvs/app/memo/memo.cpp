#pragma defer_codegen on
#include <global.h>
struct MemoEntry {u16 id,pad;u32 trainer,random;};
struct Memo {u16 count,pad;MemoEntry entry[500];};
extern "C" {
Memo *savedataGetStatus(void*,u16);s32 HSD_Rand();u16 pokemonBiosGetPokemonDataId(void*);u32 pokemonBiosGetRnd(void*);u32 pokemonBiosGetCatchTrainerRnd(void*);

static inline Memo *getMemo(Memo *memo){if(!memo)memo=savedataGetStatus(0,12);return memo;}
static inline u32 randomMemo(){s32 low=HSD_Rand();s32 high=HSD_Rand()<<16;return (high|low)%0xFFFFFFFF;}

}

extern "C" { void memoGetScaleAngle(u16 arg0, f32 *arg1, f32 *arg2); }
extern "C" { void memoInitDebug(Memo *memo); }
extern "C" { u32 memoDataGetPokemonTrainerRndFromID(Memo *memo,u16 id); }
extern "C" { u32 memoDataGetPokemonRndFromID(Memo *memo,u16 id); }
extern "C" { u16 memoDataGetPokemonID(Memo *memo,u16 index); }
extern "C" { u16 memoDataGetCount(Memo *memo); }
extern "C" { s32 memoDataSetMemoFlag(Memo *memo); }
extern "C" { void memoDataSetPokemonID(Memo *memo,u16 id); }
extern "C" { void memoDataSet(Memo *memo,void *pokemon); }
extern "C" { void memoInit(Memo *memo); }

#pragma force_active on
extern "C" {
void memoInit(Memo *memo){memo=getMemo(memo);memo->count=0;for(s32 i=0;i<500;i++){memo->entry[i].id=0;memo->entry[i].random=randomMemo();}}
}
extern "C" {
void memoDataSet(Memo *memo,void *pokemon){memo=getMemo(memo);u16 id=pokemonBiosGetPokemonDataId(pokemon);u16 count=memo->count;for(u16 i=0;i<count;i++){if((u16)(memo->entry[i].id&0x3FFF)==id)return;}memo->entry[count].id=id|0x8000;memo->entry[memo->count].random=pokemonBiosGetRnd(pokemon);memo->entry[memo->count].trainer=pokemonBiosGetCatchTrainerRnd(pokemon);memo->count++;}
}
extern "C" {
void memoDataSetPokemonID(Memo *memo,u16 id){memo=getMemo(memo);u16 count=memo->count;for(u16 i=0;i<count;i++){if((u16)(memo->entry[i].id&0x3FFF)==id)return;}memo->entry[count].id=id|0x8000;memo->entry[memo->count].random=randomMemo();memo->count++;}
}
extern "C" {
s32 memoDataSetMemoFlag(Memo *memo){s32 changed=0;memo=getMemo(memo);for(u16 i=0;i<memo->count;i++){if(memo->entry[i].id&0x8000)changed=1;memo->entry[i].id&=0x3FFF;}return changed;}
}
extern "C" {
u16 memoDataGetCount(Memo *memo){memo=getMemo(memo);return memo->count;}
}
extern "C" {
u16 memoDataGetPokemonID(Memo *memo,u16 index){memo=getMemo(memo);if(memo->count)return memo->entry[index].id;return 0;}
}
extern "C" {
u32 memoDataGetPokemonRndFromID(Memo *memo,u16 id){memo=getMemo(memo);u16 count=memoDataGetCount(memo);for(u16 i=0;i<count;i++){if((memo->entry[i].id&0x3FFF)==id)return memo->entry[i].random;}return 0;}
}
extern "C" {
u32 memoDataGetPokemonTrainerRndFromID(Memo *memo,u16 id){memo=getMemo(memo);u16 count=memoDataGetCount(memo);for(u16 i=0;i<count;i++){if((memo->entry[i].id&0x3FFF)==id)return memo->entry[i].trainer;}return 0;}
}
extern "C" {
void memoInitDebug(Memo *memo){memo=getMemo(memo);for(u16 i=1;i<=251;i++)memoDataSetPokemonID(0,i);for(u16 i=277;i<=411;i++)memoDataSetPokemonID(0,i);}
}
extern "C" {
void memoGetScaleAngle(u16 arg0, f32 *arg1, f32 *arg2) {
    f32 var_f1;

    var_f1 = 1.0f;
    switch ((s32) arg0) {                           /* irregular */
    case 0x15C:
        var_f1 = 1.2f;
        break;
    case 0x26:
        var_f1 = 0.6f;
        break;
    case 0x4B:
        var_f1 = 0.8f;
        break;
    case 0x91:
        var_f1 = 0.75f;
        break;
    case 0x12C:
        var_f1 = 0.7f;
        break;
    case 0x8E:
        var_f1 = 0.85f;
        break;
    case 0x197:
        var_f1 = 0.65f;
        break;
    case 0x198:
        var_f1 = 0.65f;
        break;
    case 0x1A:
        var_f1 = 0.7f;
        break;
    case 0x6:
        var_f1 = 0.7f;
        break;
    case 0xE2:
        var_f1 = 0.75f;
        break;
    case 0xD9:
        var_f1 = 0.75f;
        break;
    case 0x14B:
        var_f1 = 0.78f;
        break;
    case 0x44:
        var_f1 = 0.78f;
        break;
    case 0x136:
        var_f1 = 0.75f;
        break;
    case 0x4A:
        var_f1 = 0.8f;
        break;
    case 0x16B:
        var_f1 = 0.8f;
        break;
    case 0x85:
        var_f1 = 0.8f;
        break;
    case 0x92:
        var_f1 = 0.6f;
        break;
    case 0x90:
        var_f1 = 0.6f;
        break;
    case 0x65:
        var_f1 = 1.2f;
        break;
    case 0xFA:
        var_f1 = 0.65f;
        break;
    case 0x194:
        var_f1 = 0.7f;
        break;
    case 0xF9:
        var_f1 = 0.85f;
        break;
    case 0x135:
        var_f1 = 0.75f;
        break;
    case 0x156:
        var_f1 = 1.25f;
        break;
    case 0x14C:
        var_f1 = 1.2f;
        break;
    case 0x6C:
        var_f1 = 1.3f;
        break;
    case 0x5C:
        var_f1 = 0.8f;
        break;
    case 0x57:
        var_f1 = 1.2f;
        break;
    case 0x13A:
        var_f1 = 1.18f;
        break;
    case 0x82:
        var_f1 = 1.1f;
        break;
    }
    if (arg2 != NULL) {
        *arg2 = 0.2617994f;
    }
    if (arg1 != NULL) {
        *arg1 = var_f1;
    }
}
}
