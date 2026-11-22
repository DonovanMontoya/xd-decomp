#pragma defer_codegen on
#include <game/pxdvs/app/hero/heroParty.hpp>
#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/sodateya/sodateya.hpp>
extern "C" {
void *savedataGetStatus(void*,u16);Pokemon *heroBiosGetPokemonPtr(Hero*,u16);u8 pokemonCheckValid(void*);u8 pokemonBiosGetLevel(void*);u8 pokemonBiosGetDarkFlag(void*);u32 pokemonBiosGetDp(void*);u16 pokemonBiosGetDarkpokemonDataId(void*);u16 pokemonBiosGetHp(void*);u32 pokemonBiosGetExp(void*);f32 pokemonGetDp(void*);
void pokemonInit(void*);void pokemonAllKaihuku(void*);u8 pokemonIsJoutaiDataId(void*,u16);void pokemonInitJoutaiDataId(void*,u16);
u8 darkPokemonBiosGetReliveFlag(u16);u8 darkPokemonBiosGetInformationFlag(u16);s32 darkPokemonBiosGetSteps(u16);void darkPokemonBiosSetSteps(u16,u16);void pokemonAddDpFormPokemonDpFilterId(void*,s32,s32);void pokemonGrowBasisStatus(void*,u32);void pokemonOboeWaza(void*,u8,s32,u8*);
u32 GSflagGet(s32);void GSflagSet(s32,u32);void GSthreadSwitch();void heroMoveInitEvent();void heroMoveSetColision(s32);void heroMoveTermEvent();void menuScriptInfoRelive(void*,s32);s32 heroMoveAddStepCallback(void(*)(s32,s32,s32),s32);
static void _sodateyaCallBackFunc__Fl15FootStepCounterl(s32,s32,s32);
}
static s32 _sodateyaHandle;
static inline Sodateya *getWork(Sodateya *work){if(!work)work=(Sodateya*)savedataGetStatus(0,11);return work;}
static inline u32 getInitialDP(Sodateya *work){work=getWork(work);if(work->active)return work->initialDP;return 0xFFFFFFFF;}
static inline u8 getInitialLevel(Sodateya *work){work=getWork(work);if(work->active)return work->initialLevel;return 0xFF;}
static inline void setActive(Sodateya *work,u8 active){work=getWork(work);if(work)work->active=active;}
static inline void setLevel(Sodateya *work,u8 level){work=getWork(work);if(work)work->initialLevel=level;}
static inline void setSteps(Sodateya *work,u16 steps){work=getWork(work);if(work)work->steps=steps;}
static inline u16 validDark(void *pokemon, s32 mode) {
    u16 id = pokemonBiosGetDarkpokemonDataId(pokemon);
    if (id) {
        if (mode == 1) {
            if (darkPokemonBiosGetReliveFlag(id) || id == 73) return 0;
            if (pokemonGetDp(pokemon) == 0.0f) return id;
            return 0;
        }
        if (darkPokemonBiosGetReliveFlag(id) || pokemonBiosGetHp(pokemon) == 0 || id == 73) return 0;
    }
    return id;
}
static inline void notifyRelive(void *pokemon,s32 mode){u16 id=validDark(pokemon,mode);if(id&&darkPokemonBiosGetInformationFlag(id)==0){heroMoveInitEvent();heroMoveSetColision(1);GSthreadSwitch();menuScriptInfoRelive(pokemon,1);heroMoveTermEvent();}}
static inline u32 addExperience(u32 original, u32 steps) {
    u32 sum = original + steps;
    if (original > sum) return -1U;
    return sum;
}
extern "C" {
s32 sodateyaeChekcRais();
s32 sodateyaGetPokemonDPValue();
s32 sodateyaGetPokemonLevelUpValue();
s32 sodateyaCalcPrice(s32 levels);
void sodateyaReclaim(s32 slot);
void sodateyaRaise(s32 slot);
void sodateyaHeroCallBackInit();
static inline void sodateyaPartyStep(s32 arg1, s32 arg2){
    u16 var_r25;
    u8 *temp_r26;
    Hero *hero;
    u16 var_r24_2;
    u16 var_r24;
    u16 temp_r0;
    u16 var_r28;
    hero = (Hero*)savedataGetStatus(0, 2);
    if (hero != NULL) {
        for(var_r28=0;var_r28<6U;var_r28++) {
            temp_r26 = (u8*)heroBiosGetPokemonPtr(hero, var_r28);
            if ((pokemonCheckValid(temp_r26) != 0) && (temp_r26 != NULL)) {
                var_r25 = validDark(temp_r26, arg1);
                if (var_r25 != 0) {
                    if (pokemonBiosGetDp(temp_r26) != 0U) {
                        s32 previousSteps = darkPokemonBiosGetSteps(var_r25);
                        temp_r0 = previousSteps + arg2;
                        if (temp_r0 >= 0x100U) {
                            pokemonAddDpFormPokemonDpFilterId(temp_r26, 0, 1);
                            if (pokemonGetDp(temp_r26) == 0.0f) {
                                var_r24 = validDark(temp_r26, arg1);
                                if ((var_r24 != 0) && (darkPokemonBiosGetInformationFlag(var_r24) == 0)) {
                                    heroMoveInitEvent();
                                    heroMoveSetColision(1);
                                    GSthreadSwitch();
                                    menuScriptInfoRelive(temp_r26, 1);
                                    heroMoveTermEvent();
                                }
                                darkPokemonBiosSetSteps(var_r25, 0U);
                            } else {
                                darkPokemonBiosSetSteps(var_r25, (u16) (temp_r0 - 0x100));
                            }
                        } else {
                            darkPokemonBiosSetSteps(var_r25, temp_r0);
                        }
                    } else {
                        var_r24_2 = validDark(temp_r26, arg1);
                        if ((var_r24_2 != 0) && (darkPokemonBiosGetInformationFlag(var_r24_2) == 0)) {
                            heroMoveInitEvent();
                            heroMoveSetColision(1);
                            GSthreadSwitch();
                            menuScriptInfoRelive(temp_r26, 1);
                            heroMoveTermEvent();
                        }
                    }
                }
            }
        }
    }
}
static void _sodateyaCallBackFunc__Fl15FootStepCounterl(s32, s32 arg1, s32 arg2);

}

extern "C" {
static void _sodateyaCallBackFunc__Fl15FootStepCounterl(s32, s32 arg1, s32 arg2) {
    u16 temp_r3_2;
    s32 temp_r0_2;
    u32 temp_r3_6;
    Sodateya *work;
    u16 temp_r3_5;
    u16 temp_r3_4;
    u16 var_r31;
    u8 sp8;
    u32 var_r4;
    s32 var_r3;
    u16 temp_r3_3;
    u32 temp_r5;
    Pokemon *stored;
    u16 var_r24_3;

    sodateyaPartyStep(arg1, arg2);
    if (GSflagGet(4) != 0) {
        var_r31 = (u16)GSflagGet(5);
        if ((u32)var_r31 < 0x2710U) {
            temp_r0_2 = var_r31 + arg2;
            var_r3 = 0xFFFF;
            if (temp_r0_2 < 0xFFFF) {
                var_r3 = temp_r0_2;
            }
            var_r31 = (u16) var_r3;
        }
        GSflagSet(5, (u16)var_r31);
    }
    if (getWork(0)->active != 0) {
        if (arg2 > 0) {
            stored = &getWork(0)->pokemon;
            var_r24_3 = 0;
            if (stored != NULL) {
                var_r24_3 = validDark(stored, arg1);
                if ((var_r24_3 != 0) && (darkPokemonBiosGetReliveFlag(var_r24_3) != 0)) {
                    var_r24_3 = 0;
                }
            }
            if ((var_r24_3 == 0) && (pokemonBiosGetLevel(stored) < 0x64U)) {
                pokemonGrowBasisStatus(stored, addExperience(pokemonBiosGetExp(stored), arg2));
                sp8 = 0;
                pokemonOboeWaza(stored, pokemonBiosGetLevel(stored), 1, &sp8);
            }
        }
        work = getWork(0);
        if (work != NULL) {
            work->steps = var_r31;
        }
    }
}

void sodateyaHeroCallBackInit(){_sodateyaHandle=heroMoveAddStepCallback(_sodateyaCallBackFunc__Fl15FootStepCounterl,0);}

void sodateyaInit(Sodateya *work){work=getWork(work);if(work){setSteps(work,0);work->initialLevel=0;work->active=0;}}

Pokemon* sodateyaGetPokemonPtr(Sodateya* work) {
    return &getWork(work)->pokemon;
}

s32 sodateyaGetPokemonLevelUpValue(){u8 initial=getInitialLevel(0);u8 current=pokemonBiosGetLevel(sodateyaGetPokemonPtr(0));s32 result=initial;return current-result;}

s32 sodateyaGetPokemonDPValue(){sodateyaGetPokemonPtr(0);u32 initial=getInitialDP(0);return (s32)(initial-pokemonBiosGetDp(sodateyaGetPokemonPtr(0)))/100;}

void sodateyaRaise(s32 slot) {
    Pokemon* pokemon;
    Hero* hero = (Hero*)savedataGetStatus(0, 2);
    pokemon = heroBiosGetPokemonPtr(hero, slot);
    s32 count = heroGetPokeomCount(hero);
    Sodateya* work = getWork(0);
    u8 success;
    if (!pokemon) {
        success = 0;
    } else {
        setLevel(work, pokemonBiosGetLevel(pokemon));
        Pokemon* stored = sodateyaGetPokemonPtr(work);
        if (!stored) {
            success = 0;
        } else {
            if (pokemonIsJoutaiDataId(pokemon, 62)) {
                pokemonInitJoutaiDataId(pokemon, 62);
            }
            *stored = *pokemon;
            if (pokemonBiosGetDarkFlag(pokemon)) {
                work->initialDP = pokemonBiosGetDp(pokemon);
            } else {
                work->initialDP = 0;
            }
            DarkPokemon* dark = pokemon->getDarkPokemon();
            if (dark) dark->setPlace(place4, 0);
            setActive(work, 1);
            pokemonInit(pokemon);
            success = 1;
        }
    }
    if (success && slot < 6) {
        s32 i = slot;
        while (i < count - 1) {
            Pokemon* destination = heroBiosGetPokemonPtr(hero, i);
            pokemon = heroBiosGetPokemonPtr(hero, i + 1);
            if (!pokemonCheckValid(pokemon)) break;
            *destination = *pokemon;
            ++i;
        }
        pokemonInit(pokemon);
    }
}

void sodateyaReclaim(s32 slot) {
    Hero* hero = (Hero*)savedataGetStatus(0, 2);
    Pokemon* pokemon = heroBiosGetPokemonPtr(hero, slot);
    Sodateya* work = getWork(0);
    if (pokemon) {
        Pokemon* stored = sodateyaGetPokemonPtr(work);
        if (stored) {
            *pokemon = *stored;
            if (pokemonBiosGetDarkFlag(stored)) {
                pokemonBiosGetDp(stored);
            }
            DarkPokemon* dark = pokemon->getDarkPokemon();
            if (dark) dark->setPlace(place1, 0);
            setActive(work, 0);
            pokemonInit(stored);
        }
    }
    pokemonAllKaihuku(pokemon);
}

s32 sodateyaCalcPrice(s32 levels){s32 dpPrice;if(getInitialDP(0)){s32 gain=sodateyaGetPokemonDPValue();if(gain)dpPrice=gain*100+100;else dpPrice=0;}else dpPrice=0;s32 base=100*levels;dpPrice=base+dpPrice;dpPrice+=100;return dpPrice;}

s32 sodateyaeChekcRais(){Sodateya *work=getWork(0);if(!work)return -1;switch(work->active){case 1:return 1;case 0:return 0;default:return -1;}}
}
