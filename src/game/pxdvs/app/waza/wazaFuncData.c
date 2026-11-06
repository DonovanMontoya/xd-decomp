#include <dolphin/types.h>

/* Six callbacks per move, selected by wazaBios/wazaDB and invoked by the fight code.
 * Individual declarations retain the parameter widths of their reconstructed definitions. */
typedef struct FIGHT_TRAINER FIGHT_TRAINER;
typedef struct FightOutPokemon FightOutPokemon;
typedef struct FightPokemon FightPokemon;
typedef s32 (*AiWazaFunction)(FIGHT_TRAINER*, FightOutPokemon*, u16, FightOutPokemon*);
typedef s32 (*AiWazaPokemonFunction)(FIGHT_TRAINER*, FightOutPokemon*, u16, FightPokemon*);
typedef void (*WazaWzxTypeFunction)(u16, FightOutPokemon*, FightOutPokemon*, u16, u32);
typedef u32 (*WazaWzxVariationFunction)(u16, FightOutPokemon*);
typedef struct WazaFunctionRecord {
    AiWazaFunction fightTrainerAiWazaValue;
    AiWazaFunction fightTrainerAiWazaHit;
    AiWazaFunction fightTrainerAiWazaDamage;
    AiWazaPokemonFunction fightTrainerAiWazaDamageFightPokemon;
    WazaWzxTypeFunction fightWazaWzxType;
    WazaWzxVariationFunction fightWazaWzxVariation;
} WazaFunctionRecord;

extern s32 fightTrainerAiWazaDamage000(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage001(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage002(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage003(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage004(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage005(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage006(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage007(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage008(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage009(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage010(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage011(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage013(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage016(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage017(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage018(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage019(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage020(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage023(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage024(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage025(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage026(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage027(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage028(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage029(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage030(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage031(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage032(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage033(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage034(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage035(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage036(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage037(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage038(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage039(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage040(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage041(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage042(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage043(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage044(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage045(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage046(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage047(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage048(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage049(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage050(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage051(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage052(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage053(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage054(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage057(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage058(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage059(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage060(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage062(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage065(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage066(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage067(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage068(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage069(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage070(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage071(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage072(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage073(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage075(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage076(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage077(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage078(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage079(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage080(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage081(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage082(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage083(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage084(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage085(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage086(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage087(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage088(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage089(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage090(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage091(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage092(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage093(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage094(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage095(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage097(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage098(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage099(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage100(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage101(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage102(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage103(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage104(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage105(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage106(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage107(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage108(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage109(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage111(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage112(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage113(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage114(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage115(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage116(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage117(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage118(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage119(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage120(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage121(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage122(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage123(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage124(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage125(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage126(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage127(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage128(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage129(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage130(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage132(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage133(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage134(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage135(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage136(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage137(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage138(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage139(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage140(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage142(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage143(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage144(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage145(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage146(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage147(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage148(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage149(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage150(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage151(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage152(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage153(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage154(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage155(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage156(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage157(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage158(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage159(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage160(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage161(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage162(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage164(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage165(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage166(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage167(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage168(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage169(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage170(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage171(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage172(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage173(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u32 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage174(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage175(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage176(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage177(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage178(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage179(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage180(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage181(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage182(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage183(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage184(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage185(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage186(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage187(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage188(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage189(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage190(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage191(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage192(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage193(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage194(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage195(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage196(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage197(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage198(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage199(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage200(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage201(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage202(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage203(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage204(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage205(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage206(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage207(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage208(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage209(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage210(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage211(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage212(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage213(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage214(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage215(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage216(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamage217(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon000(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon001(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon002(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon003(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon004(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon005(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon006(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon007(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon008(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon009(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon010(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon011(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon013(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon016(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon017(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon018(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon019(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon020(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon023(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon024(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon025(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon026(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon027(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon028(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon029(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon030(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon031(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon032(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon033(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon034(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon035(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon036(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon037(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon038(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon039(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon040(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon041(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon042(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon043(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon044(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon045(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon046(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon047(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon048(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon049(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon050(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon051(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon052(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon053(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon054(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon057(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon058(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon059(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon060(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon062(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon065(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon066(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon067(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon068(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon069(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon070(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon071(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon072(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon073(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon075(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon076(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon077(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon078(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon079(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon080(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon081(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon082(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon083(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon084(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon085(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon086(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon087(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon088(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon089(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon090(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon091(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon092(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon093(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon094(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon095(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon097(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon098(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon099(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon100(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon101(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon102(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon103(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon104(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon105(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon106(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon107(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon108(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon109(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon111(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon112(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon113(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon114(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon115(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon116(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon117(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon118(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon119(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon120(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon121(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon122(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon123(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon124(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon125(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon126(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon127(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon128(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon129(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon130(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon132(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon133(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon134(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon135(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon136(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon137(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon138(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon139(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon140(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon142(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon143(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon144(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon145(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon146(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon147(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon148(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon149(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon150(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon151(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon152(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon153(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon154(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon155(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon156(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon157(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon158(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon159(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon160(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon161(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon162(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon164(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon165(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon166(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon167(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon168(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon169(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon170(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon171(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon172(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon173(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u32 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon174(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon175(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon176(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon177(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon178(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon179(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon180(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon181(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon182(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon183(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon184(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon185(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon186(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon187(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon188(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon189(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon190(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon191(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon192(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon193(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon194(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon195(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon196(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon197(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon198(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon199(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon200(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon201(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon202(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon203(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightPokemon *arg3);
extern s32 fightTrainerAiWazaDamageFightPokemon204(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon205(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon206(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon207(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon208(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon209(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon210(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon211(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon212(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon213(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon214(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon215(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon216(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemon217(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageFightPokemonNull(FIGHT_TRAINER* trainer, FightOutPokemon* attacker, u16 move, FightPokemon* defender);
extern s32 fightTrainerAiWazaDamageNull(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit000(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit001(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit002(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit003(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit004(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit005(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit006(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit007(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit008(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit009(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit010(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit011(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit013(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit016(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit017(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit018(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit019(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit020(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit023(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit024(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit025(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit026(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit027(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit028(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit029(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit030(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit031(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit032(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit033(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit034(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit035(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit036(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit037(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit038(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit039(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit040(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit041(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit042(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit043(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit044(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit045(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit046(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit047(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit048(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit049(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit050(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit051(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit052(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit053(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit054(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit057(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit058(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit059(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit060(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit062(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit065(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit066(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit067(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit068(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit069(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit070(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit071(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit072(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit073(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit075(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit076(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit077(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit078(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit079(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit080(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit081(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit082(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit083(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit084(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit085(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit086(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit087(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit088(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit089(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit090(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit091(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit092(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit093(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit094(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit095(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit097(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit098(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit099(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit100(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit101(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit102(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit103(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit104(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit105(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit106(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit107(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit108(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit109(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit111(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit112(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit113(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit114(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit115(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit116(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit117(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit118(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit119(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit120(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit121(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit122(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit123(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit124(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit125(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit126(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit127(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit128(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit129(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit130(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit132(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit133(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit134(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit135(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit136(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit137(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit138(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit139(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit140(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit142(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit143(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit144(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit145(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit146(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit147(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit148(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit149(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit150(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit151(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit152(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit153(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit154(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit155(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit156(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit157(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit158(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit159(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit160(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit161(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit162(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit164(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit165(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit166(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit167(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit168(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit169(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit170(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit171(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit172(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit173(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u32 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit174(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit175(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit176(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit177(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit178(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit179(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit180(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit181(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit182(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit183(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit184(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit185(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit186(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit187(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit188(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit189(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit190(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit191(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit192(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit193(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit194(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit195(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit196(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit197(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit198(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit199(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit200(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit201(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit202(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit203(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit204(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit205(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit206(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit207(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit208(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit209(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit210(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit211(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit212(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit213(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit214(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit215(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit216(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHit217(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaHitNull(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueAbareru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueAkumu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueAmagoi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueAnkooru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueArare(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueAroma(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueAteminage(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueBakadikara(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueBakuretuPanti(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueBatontatti(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueBirudoAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueBougyoAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueBougyoDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueBureizukikku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDarkEnd(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDarkHalf(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDarkHold(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDarkMist(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDarkPanic(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDarkRemove(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDarkWeather(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDenjihou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDoku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDokudokunokiba(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDorokake(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDouguUbau(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueDowasure(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueGamusyara(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueGoddobaado(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHaganenotubasa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHandou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHaradaiko(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHatakiotosu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHikarinokabe(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHimitunotikara(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHittyuu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHonoonouzu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHurahuradansu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueHuuin(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueIbaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueIkarinomaeba(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueIryokuHonoo(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target);
extern s32 fightTrainerAiWazaValueItamiwake(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueItigekihissatu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueJibaku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueJikoanji(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueJikokaitou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueJisin(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueJyuuden(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKaihiDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKaihirituAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKaihuku1(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKaihuku2(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKamaitati(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKanarazuSubayasaDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKanasibari(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKauntaa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKawarawari(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKiaipanti(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKituke(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKogoerukaze(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKonoyubitomare(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKonran(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKoraeru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKorogaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKosumopawaa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKouPuraioritii(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKougekiAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKougekiDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKoukanKinsi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKousokuidou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKuroikiri(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKusuguruDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKyouseikoutai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueKyuusyuu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMahi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMajikkukooto(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMakibisi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMamoru(FIGHT_TRAINER* t, FightOutPokemon* self, u16 waza, FightOutPokemon* target);
extern s32 fightTrainerAiWazaValueMarukunaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMeisou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMeityuuDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMeromero(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMigawari(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMiraakooto(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMitizure(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueMiyaburu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueNekodamasi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueNemurare(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueNemuriKoudou(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueNemuru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueNihonbare(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueNoroi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueNull(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueOdareru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueOiuti(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueOnibi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueOobaahiito(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueOomugaesi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueOororabiimu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValuePhyKuritikaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValuePoizunteeru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueRandamuSentaku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueRibenji(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueRihurekutaa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueRihuressyu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueRisaikuru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueRokettoZutuki(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueRokkuon(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueRyuunomai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSaikobuusuto(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSawagu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSiroikiri(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSizennotikara(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSokubaku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSooraabiimu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSorawotobu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSpeKuritikaru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSubayasaDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSukirusuwappu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueSunaarasi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTakuwaeru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTedasuke(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTeiryouDameeji(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTobihaneru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTokubetuYuusen(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTokubouDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTokukouAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueToraiatakku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueToriaezutukae(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikaDoku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikaHirumi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikaKoori(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikaKougekiAppu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikaMahi(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikouBougyoDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikouKonran(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikouMeityuuDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikouSubayasaDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikouTokubouDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuikouTokukouDaun(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueTuujouIryoku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueUezaabooru(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueUrami(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueYokodori(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueYumekui(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValueZennouryokuappu(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern s32 fightTrainerAiWazaValuetorikku(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, FightOutPokemon *arg3);
extern void fightWazaWzxTypeFuncAllAlly(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncAllEnemy(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncAtt(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncAttDef(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncAttDefSpc(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncHensin(u16 waza, FightOutPokemon* poke, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncHuuin(u16 waza, FightOutPokemon* user, FightOutPokemon* a, u16 mode, u8 flag);
extern void fightWazaWzxTypeFuncItamiwake(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncKawarawari(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncMagiccort(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncMigawari(u16 waza, FightOutPokemon* poke, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncNegaigoto(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncNormal(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncNormal2(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncNull(u16, FightOutPokemon*, FightOutPokemon*, u16, u8);
extern void fightWazaWzxTypeFuncSpc(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncTame(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncTedasuke(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern void fightWazaWzxTypeFuncVampire(u16 waza, FightOutPokemon* atk, FightOutPokemon* def, u16 mode, u32 var);
extern u32 fightWazaWzxVariationFuncHakidasu(u16, FightOutPokemon*);
extern u32 fightWazaWzxVariationFuncIceball(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncKawarawari(u16, FightOutPokemon*);
extern u32 fightWazaWzxVariationFuncKetaguri(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncKorogaru(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncMagnitude(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncNomikomu(u16, FightOutPokemon*);
extern u32 fightWazaWzxVariationFuncNormal(u16, FightOutPokemon*);
extern u32 fightWazaWzxVariationFuncNull(u16, FightOutPokemon*);
extern u32 fightWazaWzxVariationFuncOiuchi(u16, FightOutPokemon*);
extern u32 fightWazaWzxVariationFuncOngaesi(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncPresent(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncRenzokugiri(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncTikyuunage(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncTripleKick(u16, FightOutPokemon* poke);
extern u32 fightWazaWzxVariationFuncWeatherBall(u16, FightOutPokemon*);
extern u32 fightWazaWzxVariationFuncWeatherHP(u16, FightOutPokemon*);
extern u32 fightWazaWzxVariationFuncYatuatari(u16, FightOutPokemon* poke);

WazaFunctionRecord waza_func_data[] = {
    {
        fightTrainerAiWazaValueNull,
        fightTrainerAiWazaHitNull,
        fightTrainerAiWazaDamageNull,
        fightTrainerAiWazaDamageFightPokemonNull,
        (WazaWzxTypeFunction)fightWazaWzxTypeFuncNull,
        fightWazaWzxVariationFuncNull,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValuePhyKuritikaru,
        fightTrainerAiWazaHit043,
        fightTrainerAiWazaDamage043,
        fightTrainerAiWazaDamageFightPokemon043,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit034,
        fightTrainerAiWazaDamage034,
        fightTrainerAiWazaDamageFightPokemon034,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueIryokuHonoo,
        fightTrainerAiWazaHit004,
        fightTrainerAiWazaDamage004,
        fightTrainerAiWazaDamageFightPokemon004,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaKoori,
        fightTrainerAiWazaHit005,
        fightTrainerAiWazaDamage005,
        fightTrainerAiWazaDamageFightPokemon005,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueItigekihissatu,
        fightTrainerAiWazaHit038,
        fightTrainerAiWazaDamage038,
        fightTrainerAiWazaDamageFightPokemon038,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKamaitati,
        fightTrainerAiWazaHit039,
        fightTrainerAiWazaDamage039,
        fightTrainerAiWazaDamageFightPokemon039,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKougekiAppu,
        fightTrainerAiWazaHit050,
        fightTrainerAiWazaDamage050,
        fightTrainerAiWazaDamageFightPokemon050,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit149,
        fightTrainerAiWazaDamage149,
        fightTrainerAiWazaDamageFightPokemon149,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKyouseikoutai,
        fightTrainerAiWazaHit028,
        fightTrainerAiWazaDamage028,
        fightTrainerAiWazaDamageFightPokemon028,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSorawotobu,
        fightTrainerAiWazaHit155,
        fightTrainerAiWazaDamage155,
        fightTrainerAiWazaDamageFightPokemon155,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSokubaku,
        fightTrainerAiWazaHit042,
        fightTrainerAiWazaDamage042,
        fightTrainerAiWazaDamageFightPokemon042,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit150,
        fightTrainerAiWazaDamage150,
        fightTrainerAiWazaDamageFightPokemon150,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit044,
        fightTrainerAiWazaDamage044,
        fightTrainerAiWazaDamageFightPokemon044,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit045,
        fightTrainerAiWazaDamage045,
        fightTrainerAiWazaDamageFightPokemon045,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit031,
        fightTrainerAiWazaDamage031,
        fightTrainerAiWazaDamageFightPokemon031,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMeityuuDaun,
        fightTrainerAiWazaHit023,
        fightTrainerAiWazaDamage023,
        fightTrainerAiWazaDamageFightPokemon023,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit031,
        fightTrainerAiWazaDamage031,
        fightTrainerAiWazaDamageFightPokemon031,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueItigekihissatu,
        fightTrainerAiWazaHit038,
        fightTrainerAiWazaDamage038,
        fightTrainerAiWazaDamageFightPokemon038,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSokubaku,
        fightTrainerAiWazaHit042,
        fightTrainerAiWazaDamage042,
        fightTrainerAiWazaDamageFightPokemon042,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit048,
        fightTrainerAiWazaDamage048,
        fightTrainerAiWazaDamageFightPokemon048,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueAbareru,
        fightTrainerAiWazaHit027,
        fightTrainerAiWazaDamage027,
        fightTrainerAiWazaDamageFightPokemon027,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit198,
        fightTrainerAiWazaDamage198,
        fightTrainerAiWazaDamageFightPokemon198,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoDaun,
        fightTrainerAiWazaHit019,
        fightTrainerAiWazaDamage019,
        fightTrainerAiWazaDamageFightPokemon019,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaDoku,
        fightTrainerAiWazaHit002,
        fightTrainerAiWazaDamage002,
        fightTrainerAiWazaDamageFightPokemon002,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaDoku,
        fightTrainerAiWazaHit077,
        fightTrainerAiWazaDamage077,
        fightTrainerAiWazaDamageFightPokemon077,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoDaun,
        fightTrainerAiWazaHit019,
        fightTrainerAiWazaDamage019,
        fightTrainerAiWazaDamageFightPokemon019,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit031,
        fightTrainerAiWazaDamage031,
        fightTrainerAiWazaDamageFightPokemon031,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKougekiDaun,
        fightTrainerAiWazaHit018,
        fightTrainerAiWazaDamage018,
        fightTrainerAiWazaDamageFightPokemon018,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKyouseikoutai,
        fightTrainerAiWazaHit028,
        fightTrainerAiWazaDamage028,
        fightTrainerAiWazaDamageFightPokemon028,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemurare,
        fightTrainerAiWazaHit001,
        fightTrainerAiWazaDamage001,
        fightTrainerAiWazaDamageFightPokemon001,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKonran,
        fightTrainerAiWazaHit049,
        fightTrainerAiWazaDamage049,
        fightTrainerAiWazaDamageFightPokemon049,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTeiryouDameeji,
        fightTrainerAiWazaHit130,
        fightTrainerAiWazaDamage130,
        fightTrainerAiWazaDamageFightPokemon130,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKanasibari,
        fightTrainerAiWazaHit086,
        fightTrainerAiWazaDamage086,
        fightTrainerAiWazaDamageFightPokemon086,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouBougyoDaun,
        fightTrainerAiWazaHit069,
        fightTrainerAiWazaDamage069,
        fightTrainerAiWazaDamageFightPokemon069,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueIryokuHonoo,
        fightTrainerAiWazaHit004,
        fightTrainerAiWazaDamage004,
        fightTrainerAiWazaDamageFightPokemon004,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueIryokuHonoo,
        fightTrainerAiWazaHit004,
        fightTrainerAiWazaDamage004,
        fightTrainerAiWazaDamageFightPokemon004,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSiroikiri,
        fightTrainerAiWazaHit046,
        fightTrainerAiWazaDamage046,
        fightTrainerAiWazaDamageFightPokemon046,
        fightWazaWzxTypeFuncAllAlly,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaKoori,
        fightTrainerAiWazaHit005,
        fightTrainerAiWazaDamage005,
        fightTrainerAiWazaDamageFightPokemon005,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaKoori,
        fightTrainerAiWazaHit005,
        fightTrainerAiWazaDamage005,
        fightTrainerAiWazaDamageFightPokemon005,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouKonran,
        fightTrainerAiWazaHit076,
        fightTrainerAiWazaDamage076,
        fightTrainerAiWazaDamageFightPokemon076,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouSubayasaDaun,
        fightTrainerAiWazaHit070,
        fightTrainerAiWazaDamage070,
        fightTrainerAiWazaDamageFightPokemon070,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueOororabiimu,
        fightTrainerAiWazaHit068,
        fightTrainerAiWazaDamage068,
        fightTrainerAiWazaDamageFightPokemon068,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHandou,
        fightTrainerAiWazaHit080,
        fightTrainerAiWazaDamage080,
        fightTrainerAiWazaDamageFightPokemon080,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit048,
        fightTrainerAiWazaDamage048,
        fightTrainerAiWazaDamageFightPokemon048,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit196,
        fightTrainerAiWazaDamage196,
        fightTrainerAiWazaDamageFightPokemon196,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncKetaguri,
    },
    {
        fightTrainerAiWazaValueKauntaa,
        fightTrainerAiWazaHit089,
        fightTrainerAiWazaDamage089,
        fightTrainerAiWazaDamageFightPokemon089,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTeiryouDameeji,
        fightTrainerAiWazaHit087,
        fightTrainerAiWazaDamage087,
        fightTrainerAiWazaDamageFightPokemon087,
        fightWazaWzxTypeFuncNormal2,
        fightWazaWzxVariationFuncTikyuunage,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKyuusyuu,
        fightTrainerAiWazaHit003,
        fightTrainerAiWazaDamage003,
        fightTrainerAiWazaDamageFightPokemon003,
        fightWazaWzxTypeFuncVampire,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKyuusyuu,
        fightTrainerAiWazaHit003,
        fightTrainerAiWazaDamage003,
        fightTrainerAiWazaDamageFightPokemon003,
        fightWazaWzxTypeFuncVampire,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit084,
        fightTrainerAiWazaDamage084,
        fightTrainerAiWazaDamageFightPokemon084,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTokukouAppu,
        fightTrainerAiWazaHit013,
        fightTrainerAiWazaDamage013,
        fightTrainerAiWazaDamageFightPokemon013,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSpeKuritikaru,
        fightTrainerAiWazaHit043,
        fightTrainerAiWazaDamage043,
        fightTrainerAiWazaDamageFightPokemon043,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSooraabiimu,
        fightTrainerAiWazaHit151,
        fightTrainerAiWazaDamage151,
        fightTrainerAiWazaDamageFightPokemon151,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDoku,
        fightTrainerAiWazaHit066,
        fightTrainerAiWazaDamage066,
        fightTrainerAiWazaDamageFightPokemon066,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMahi,
        fightTrainerAiWazaHit067,
        fightTrainerAiWazaDamage067,
        fightTrainerAiWazaDamageFightPokemon067,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemurare,
        fightTrainerAiWazaHit001,
        fightTrainerAiWazaDamage001,
        fightTrainerAiWazaDamageFightPokemon001,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueAbareru,
        fightTrainerAiWazaHit027,
        fightTrainerAiWazaDamage027,
        fightTrainerAiWazaDamageFightPokemon027,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSubayasaDaun,
        fightTrainerAiWazaHit020,
        fightTrainerAiWazaDamage020,
        fightTrainerAiWazaDamageFightPokemon020,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTeiryouDameeji,
        fightTrainerAiWazaHit041,
        fightTrainerAiWazaDamage041,
        fightTrainerAiWazaDamageFightPokemon041,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHonoonouzu,
        fightTrainerAiWazaHit042,
        fightTrainerAiWazaDamage042,
        fightTrainerAiWazaDamageFightPokemon042,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMahi,
        fightTrainerAiWazaHit067,
        fightTrainerAiWazaDamage067,
        fightTrainerAiWazaDamageFightPokemon067,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit152,
        fightTrainerAiWazaDamage152,
        fightTrainerAiWazaDamageFightPokemon152,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueJisin,
        fightTrainerAiWazaHit147,
        fightTrainerAiWazaDamage147,
        fightTrainerAiWazaDamageFightPokemon147,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueItigekihissatu,
        fightTrainerAiWazaHit038,
        fightTrainerAiWazaDamage038,
        fightTrainerAiWazaDamageFightPokemon038,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSorawotobu,
        fightTrainerAiWazaHit155,
        fightTrainerAiWazaDamage155,
        fightTrainerAiWazaDamageFightPokemon155,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDoku,
        fightTrainerAiWazaHit033,
        fightTrainerAiWazaDamage033,
        fightTrainerAiWazaDamageFightPokemon033,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouKonran,
        fightTrainerAiWazaHit076,
        fightTrainerAiWazaDamage076,
        fightTrainerAiWazaDamageFightPokemon076,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouTokubouDaun,
        fightTrainerAiWazaHit072,
        fightTrainerAiWazaDamage072,
        fightTrainerAiWazaDamageFightPokemon072,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemurare,
        fightTrainerAiWazaHit001,
        fightTrainerAiWazaDamage001,
        fightTrainerAiWazaDamageFightPokemon001,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKougekiAppu,
        fightTrainerAiWazaHit010,
        fightTrainerAiWazaDamage010,
        fightTrainerAiWazaDamageFightPokemon010,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKousokuidou,
        fightTrainerAiWazaHit052,
        fightTrainerAiWazaDamage052,
        fightTrainerAiWazaDamageFightPokemon052,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKouPuraioritii,
        fightTrainerAiWazaHit103,
        fightTrainerAiWazaDamage103,
        fightTrainerAiWazaDamageFightPokemon103,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit081,
        fightTrainerAiWazaDamage081,
        fightTrainerAiWazaDamageFightPokemon081,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNull,
        fightTrainerAiWazaHit153,
        fightTrainerAiWazaDamage153,
        fightTrainerAiWazaDamageFightPokemon153,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTeiryouDameeji,
        fightTrainerAiWazaHit087,
        fightTrainerAiWazaDamage087,
        fightTrainerAiWazaDamageFightPokemon087,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRandamuSentaku,
        fightTrainerAiWazaHit082,
        fightTrainerAiWazaDamage082,
        fightTrainerAiWazaDamageFightPokemon082,
        fightWazaWzxTypeFuncAttDefSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoDaun,
        fightTrainerAiWazaHit059,
        fightTrainerAiWazaDamage059,
        fightTrainerAiWazaDamageFightPokemon059,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKaihirituAppu,
        fightTrainerAiWazaHit016,
        fightTrainerAiWazaDamage016,
        fightTrainerAiWazaDamageFightPokemon016,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKaihuku2,
        fightTrainerAiWazaHit032,
        fightTrainerAiWazaDamage032,
        fightTrainerAiWazaDamageFightPokemon032,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoAppu,
        fightTrainerAiWazaHit011,
        fightTrainerAiWazaDamage011,
        fightTrainerAiWazaDamageFightPokemon011,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKaihirituAppu,
        fightTrainerAiWazaHit108,
        fightTrainerAiWazaDamage108,
        fightTrainerAiWazaDamageFightPokemon108,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMeityuuDaun,
        fightTrainerAiWazaHit023,
        fightTrainerAiWazaDamage023,
        fightTrainerAiWazaDamageFightPokemon023,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKonran,
        fightTrainerAiWazaHit049,
        fightTrainerAiWazaDamage049,
        fightTrainerAiWazaDamageFightPokemon049,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoAppu,
        fightTrainerAiWazaHit011,
        fightTrainerAiWazaDamage011,
        fightTrainerAiWazaDamageFightPokemon011,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMarukunaru,
        fightTrainerAiWazaHit156,
        fightTrainerAiWazaDamage156,
        fightTrainerAiWazaDamageFightPokemon156,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoAppu,
        fightTrainerAiWazaHit051,
        fightTrainerAiWazaDamage051,
        fightTrainerAiWazaDamageFightPokemon051,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHikarinokabe,
        fightTrainerAiWazaHit035,
        fightTrainerAiWazaDamage035,
        fightTrainerAiWazaDamageFightPokemon035,
        fightWazaWzxTypeFuncAllAlly,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKuroikiri,
        fightTrainerAiWazaHit025,
        fightTrainerAiWazaDamage025,
        fightTrainerAiWazaDamageFightPokemon025,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRihurekutaa,
        fightTrainerAiWazaHit065,
        fightTrainerAiWazaDamage065,
        fightTrainerAiWazaDamageFightPokemon065,
        fightWazaWzxTypeFuncAllAlly,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit047,
        fightTrainerAiWazaDamage047,
        fightTrainerAiWazaDamageFightPokemon047,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit026,
        fightTrainerAiWazaDamage026,
        fightTrainerAiWazaDamageFightPokemon026,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTokubetuYuusen,
        fightTrainerAiWazaHit083,
        fightTrainerAiWazaDamage083,
        fightTrainerAiWazaDamageFightPokemon083,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueOomugaesi,
        fightTrainerAiWazaHit009,
        fightTrainerAiWazaDamage009,
        fightTrainerAiWazaDamageFightPokemon009,
        (WazaWzxTypeFunction)fightWazaWzxTypeFuncNull,
        fightWazaWzxVariationFuncNull,
    },
    {
        fightTrainerAiWazaValueJibaku,
        fightTrainerAiWazaHit007,
        fightTrainerAiWazaDamage007,
        fightTrainerAiWazaDamageFightPokemon007,
        fightWazaWzxTypeFuncAttDef,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaDoku,
        fightTrainerAiWazaHit002,
        fightTrainerAiWazaDamage002,
        fightTrainerAiWazaDamageFightPokemon002,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaDoku,
        fightTrainerAiWazaHit002,
        fightTrainerAiWazaDamage002,
        fightTrainerAiWazaDamageFightPokemon002,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit031,
        fightTrainerAiWazaDamage031,
        fightTrainerAiWazaDamageFightPokemon031,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueIryokuHonoo,
        fightTrainerAiWazaHit004,
        fightTrainerAiWazaDamage004,
        fightTrainerAiWazaDamageFightPokemon004,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSokubaku,
        fightTrainerAiWazaHit042,
        fightTrainerAiWazaDamage042,
        fightTrainerAiWazaDamageFightPokemon042,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHittyuu,
        fightTrainerAiWazaHit017,
        fightTrainerAiWazaDamage017,
        fightTrainerAiWazaDamageFightPokemon017,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRokettoZutuki,
        fightTrainerAiWazaHit145,
        fightTrainerAiWazaDamage145,
        fightTrainerAiWazaDamageFightPokemon145,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouSubayasaDaun,
        fightTrainerAiWazaHit070,
        fightTrainerAiWazaDamage070,
        fightTrainerAiWazaDamageFightPokemon070,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDowasure,
        fightTrainerAiWazaHit054,
        fightTrainerAiWazaDamage054,
        fightTrainerAiWazaDamageFightPokemon054,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMeityuuDaun,
        fightTrainerAiWazaHit023,
        fightTrainerAiWazaDamage023,
        fightTrainerAiWazaDamageFightPokemon023,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKaihuku2,
        fightTrainerAiWazaHit157,
        fightTrainerAiWazaDamage157,
        fightTrainerAiWazaDamageFightPokemon157,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit045,
        fightTrainerAiWazaDamage045,
        fightTrainerAiWazaDamageFightPokemon045,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMahi,
        fightTrainerAiWazaHit067,
        fightTrainerAiWazaDamage067,
        fightTrainerAiWazaDamageFightPokemon067,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueYumekui,
        fightTrainerAiWazaHit008,
        fightTrainerAiWazaDamage008,
        fightTrainerAiWazaDamageFightPokemon008,
        fightWazaWzxTypeFuncAttDefSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDoku,
        fightTrainerAiWazaHit066,
        fightTrainerAiWazaDamage066,
        fightTrainerAiWazaDamageFightPokemon066,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKyuusyuu,
        fightTrainerAiWazaHit003,
        fightTrainerAiWazaDamage003,
        fightTrainerAiWazaDamageFightPokemon003,
        fightWazaWzxTypeFuncVampire,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemurare,
        fightTrainerAiWazaHit001,
        fightTrainerAiWazaDamage001,
        fightTrainerAiWazaDamageFightPokemon001,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueGoddobaado,
        fightTrainerAiWazaHit075,
        fightTrainerAiWazaDamage075,
        fightTrainerAiWazaDamageFightPokemon075,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRandamuSentaku,
        fightTrainerAiWazaHit057,
        fightTrainerAiWazaDamage057,
        fightTrainerAiWazaDamageFightPokemon057,
        fightWazaWzxTypeFuncHensin,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouSubayasaDaun,
        fightTrainerAiWazaHit070,
        fightTrainerAiWazaDamage070,
        fightTrainerAiWazaDamageFightPokemon070,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouKonran,
        fightTrainerAiWazaHit076,
        fightTrainerAiWazaDamage076,
        fightTrainerAiWazaDamageFightPokemon076,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemurare,
        fightTrainerAiWazaHit001,
        fightTrainerAiWazaDamage001,
        fightTrainerAiWazaDamageFightPokemon001,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMeityuuDaun,
        fightTrainerAiWazaHit023,
        fightTrainerAiWazaDamage023,
        fightTrainerAiWazaDamageFightPokemon023,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTeiryouDameeji,
        fightTrainerAiWazaHit088,
        fightTrainerAiWazaDamage088,
        fightTrainerAiWazaDamageFightPokemon088,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNull,
        fightTrainerAiWazaHit085,
        fightTrainerAiWazaDamage085,
        fightTrainerAiWazaDamageFightPokemon085,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoAppu,
        fightTrainerAiWazaHit051,
        fightTrainerAiWazaDamage051,
        fightTrainerAiWazaDamageFightPokemon051,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSpeKuritikaru,
        fightTrainerAiWazaHit043,
        fightTrainerAiWazaDamage043,
        fightTrainerAiWazaDamageFightPokemon043,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueJibaku,
        fightTrainerAiWazaHit007,
        fightTrainerAiWazaDamage007,
        fightTrainerAiWazaDamageFightPokemon007,
        fightWazaWzxTypeFuncAttDef,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit044,
        fightTrainerAiWazaDamage044,
        fightTrainerAiWazaDamageFightPokemon044,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemuru,
        fightTrainerAiWazaHit037,
        fightTrainerAiWazaDamage037,
        fightTrainerAiWazaDamageFightPokemon037,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit031,
        fightTrainerAiWazaDamage031,
        fightTrainerAiWazaDamageFightPokemon031,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit031,
        fightTrainerAiWazaDamage031,
        fightTrainerAiWazaDamageFightPokemon031,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKougekiAppu,
        fightTrainerAiWazaHit010,
        fightTrainerAiWazaDamage010,
        fightTrainerAiWazaDamageFightPokemon010,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRandamuSentaku,
        fightTrainerAiWazaHit030,
        fightTrainerAiWazaDamage030,
        fightTrainerAiWazaDamageFightPokemon030,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToraiatakku,
        fightTrainerAiWazaHit036,
        fightTrainerAiWazaDamage036,
        fightTrainerAiWazaDamageFightPokemon036,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueIkarinomaeba,
        fightTrainerAiWazaHit040,
        fightTrainerAiWazaDamage040,
        fightTrainerAiWazaDamageFightPokemon040,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValuePhyKuritikaru,
        fightTrainerAiWazaHit043,
        fightTrainerAiWazaDamage043,
        fightTrainerAiWazaDamageFightPokemon043,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMigawari,
        fightTrainerAiWazaHit079,
        fightTrainerAiWazaDamage079,
        fightTrainerAiWazaDamageFightPokemon079,
        fightWazaWzxTypeFuncMigawari,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNull,
        fightTrainerAiWazaHit048,
        fightTrainerAiWazaDamage048,
        fightTrainerAiWazaDamageFightPokemon048,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNull,
        fightTrainerAiWazaHit095,
        fightTrainerAiWazaDamage095,
        fightTrainerAiWazaDamageFightPokemon095,
        fightWazaWzxTypeFuncAttDefSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit104,
        fightTrainerAiWazaDamage104,
        fightTrainerAiWazaDamageFightPokemon104,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncTripleKick,
    },
    {
        fightTrainerAiWazaValueDouguUbau,
        fightTrainerAiWazaHit105,
        fightTrainerAiWazaDamage105,
        fightTrainerAiWazaDamageFightPokemon105,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKoukanKinsi,
        fightTrainerAiWazaHit106,
        fightTrainerAiWazaDamage106,
        fightTrainerAiWazaDamageFightPokemon106,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRokkuon,
        fightTrainerAiWazaHit094,
        fightTrainerAiWazaDamage094,
        fightTrainerAiWazaDamageFightPokemon094,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueAkumu,
        fightTrainerAiWazaHit107,
        fightTrainerAiWazaDamage107,
        fightTrainerAiWazaDamageFightPokemon107,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueJikokaitou,
        fightTrainerAiWazaHit125,
        fightTrainerAiWazaDamage125,
        fightTrainerAiWazaDamageFightPokemon125,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemuriKoudou,
        fightTrainerAiWazaHit092,
        fightTrainerAiWazaDamage092,
        fightTrainerAiWazaDamageFightPokemon092,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNoroi,
        fightTrainerAiWazaHit109,
        fightTrainerAiWazaDamage109,
        fightTrainerAiWazaDamageFightPokemon109,
        fightWazaWzxTypeFuncAttDef,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit099,
        fightTrainerAiWazaDamage099,
        fightTrainerAiWazaDamageFightPokemon099,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRandamuSentaku,
        fightTrainerAiWazaHit093,
        fightTrainerAiWazaDamage093,
        fightTrainerAiWazaDamageFightPokemon093,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValuePhyKuritikaru,
        fightTrainerAiWazaHit043,
        fightTrainerAiWazaDamage043,
        fightTrainerAiWazaDamageFightPokemon043,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSubayasaDaun,
        fightTrainerAiWazaHit060,
        fightTrainerAiWazaDamage060,
        fightTrainerAiWazaDamageFightPokemon060,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit099,
        fightTrainerAiWazaDamage099,
        fightTrainerAiWazaDamageFightPokemon099,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueUrami,
        fightTrainerAiWazaHit100,
        fightTrainerAiWazaDamage100,
        fightTrainerAiWazaDamageFightPokemon100,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaKoori,
        fightTrainerAiWazaHit005,
        fightTrainerAiWazaDamage005,
        fightTrainerAiWazaDamageFightPokemon005,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMamoru,
        fightTrainerAiWazaHit111,
        fightTrainerAiWazaDamage111,
        fightTrainerAiWazaDamageFightPokemon111,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKouPuraioritii,
        fightTrainerAiWazaHit103,
        fightTrainerAiWazaDamage103,
        fightTrainerAiWazaDamageFightPokemon103,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSubayasaDaun,
        fightTrainerAiWazaHit060,
        fightTrainerAiWazaDamage060,
        fightTrainerAiWazaDamageFightPokemon060,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHittyuu,
        fightTrainerAiWazaHit017,
        fightTrainerAiWazaDamage017,
        fightTrainerAiWazaDamageFightPokemon017,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKonran,
        fightTrainerAiWazaHit049,
        fightTrainerAiWazaDamage049,
        fightTrainerAiWazaDamageFightPokemon049,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHaradaiko,
        fightTrainerAiWazaHit142,
        fightTrainerAiWazaDamage142,
        fightTrainerAiWazaDamageFightPokemon142,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaDoku,
        fightTrainerAiWazaHit002,
        fightTrainerAiWazaDamage002,
        fightTrainerAiWazaDamageFightPokemon002,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDorokake,
        fightTrainerAiWazaHit073,
        fightTrainerAiWazaDamage073,
        fightTrainerAiWazaDamageFightPokemon073,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouMeityuuDaun,
        fightTrainerAiWazaHit073,
        fightTrainerAiWazaDamage073,
        fightTrainerAiWazaDamageFightPokemon073,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMakibisi,
        fightTrainerAiWazaHit112,
        fightTrainerAiWazaDamage112,
        fightTrainerAiWazaDamageFightPokemon112,
        fightWazaWzxTypeFuncAllEnemy,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDenjihou,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMiyaburu,
        fightTrainerAiWazaHit113,
        fightTrainerAiWazaDamage113,
        fightTrainerAiWazaDamageFightPokemon113,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMitizure,
        fightTrainerAiWazaHit098,
        fightTrainerAiWazaDamage098,
        fightTrainerAiWazaDamageFightPokemon098,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit114,
        fightTrainerAiWazaDamage114,
        fightTrainerAiWazaDamageFightPokemon114,
        fightWazaWzxTypeFuncAttDef,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKogoerukaze,
        fightTrainerAiWazaHit070,
        fightTrainerAiWazaDamage070,
        fightTrainerAiWazaDamageFightPokemon070,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMamoru,
        fightTrainerAiWazaHit111,
        fightTrainerAiWazaDamage111,
        fightTrainerAiWazaDamageFightPokemon111,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRokkuon,
        fightTrainerAiWazaHit094,
        fightTrainerAiWazaDamage094,
        fightTrainerAiWazaDamageFightPokemon094,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueAbareru,
        fightTrainerAiWazaHit027,
        fightTrainerAiWazaDamage027,
        fightTrainerAiWazaDamageFightPokemon027,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSunaarasi,
        fightTrainerAiWazaHit115,
        fightTrainerAiWazaDamage115,
        fightTrainerAiWazaDamageFightPokemon115,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKyuusyuu,
        fightTrainerAiWazaHit003,
        fightTrainerAiWazaDamage003,
        fightTrainerAiWazaDamageFightPokemon003,
        fightWazaWzxTypeFuncVampire,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKoraeru,
        fightTrainerAiWazaHit116,
        fightTrainerAiWazaDamage116,
        fightTrainerAiWazaDamageFightPokemon116,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKougekiDaun,
        fightTrainerAiWazaHit058,
        fightTrainerAiWazaDamage058,
        fightTrainerAiWazaDamageFightPokemon058,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKorogaru,
        fightTrainerAiWazaHit117,
        fightTrainerAiWazaDamage117,
        fightTrainerAiWazaDamageFightPokemon117,
        fightWazaWzxTypeFuncNormal2,
        fightWazaWzxVariationFuncKorogaru,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit101,
        fightTrainerAiWazaDamage101,
        fightTrainerAiWazaDamageFightPokemon101,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueIbaru,
        fightTrainerAiWazaHit118,
        fightTrainerAiWazaDamage118,
        fightTrainerAiWazaDamageFightPokemon118,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKaihuku2,
        fightTrainerAiWazaHit157,
        fightTrainerAiWazaDamage157,
        fightTrainerAiWazaDamageFightPokemon157,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit119,
        fightTrainerAiWazaDamage119,
        fightTrainerAiWazaDamageFightPokemon119,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncRenzokugiri,
    },
    {
        fightTrainerAiWazaValueHaganenotubasa,
        fightTrainerAiWazaHit138,
        fightTrainerAiWazaDamage138,
        fightTrainerAiWazaDamageFightPokemon138,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKoukanKinsi,
        fightTrainerAiWazaHit106,
        fightTrainerAiWazaDamage106,
        fightTrainerAiWazaDamageFightPokemon106,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMeromero,
        fightTrainerAiWazaHit120,
        fightTrainerAiWazaDamage120,
        fightTrainerAiWazaDamageFightPokemon120,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemuriKoudou,
        fightTrainerAiWazaHit097,
        fightTrainerAiWazaDamage097,
        fightTrainerAiWazaDamageFightPokemon097,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueAroma,
        fightTrainerAiWazaHit102,
        fightTrainerAiWazaDamage102,
        fightTrainerAiWazaDamageFightPokemon102,
        fightWazaWzxTypeFuncAllAlly,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit121,
        fightTrainerAiWazaDamage121,
        fightTrainerAiWazaDamageFightPokemon121,
        fightWazaWzxTypeFuncNormal2,
        fightWazaWzxVariationFuncOngaesi,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit122,
        fightTrainerAiWazaDamage122,
        fightTrainerAiWazaDamageFightPokemon122,
        fightWazaWzxTypeFuncNormal2,
        fightWazaWzxVariationFuncPresent,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit123,
        fightTrainerAiWazaDamage123,
        fightTrainerAiWazaDamageFightPokemon123,
        fightWazaWzxTypeFuncNormal2,
        fightWazaWzxVariationFuncYatuatari,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit124,
        fightTrainerAiWazaDamage124,
        fightTrainerAiWazaDamageFightPokemon124,
        fightWazaWzxTypeFuncAllAlly,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueItamiwake,
        fightTrainerAiWazaHit091,
        fightTrainerAiWazaDamage091,
        fightTrainerAiWazaDamageFightPokemon091,
        fightWazaWzxTypeFuncItamiwake,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueJikokaitou,
        fightTrainerAiWazaHit125,
        fightTrainerAiWazaDamage125,
        fightTrainerAiWazaDamageFightPokemon125,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueJisin,
        fightTrainerAiWazaHit126,
        fightTrainerAiWazaDamage126,
        fightTrainerAiWazaDamageFightPokemon126,
        fightWazaWzxTypeFuncNormal2,
        fightWazaWzxVariationFuncMagnitude,
    },
    {
        fightTrainerAiWazaValueBakuretuPanti,
        fightTrainerAiWazaHit076,
        fightTrainerAiWazaDamage076,
        fightTrainerAiWazaDamageFightPokemon076,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBatontatti,
        fightTrainerAiWazaHit127,
        fightTrainerAiWazaDamage127,
        fightTrainerAiWazaDamageFightPokemon127,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueAnkooru,
        fightTrainerAiWazaHit090,
        fightTrainerAiWazaDamage090,
        fightTrainerAiWazaDamageFightPokemon090,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueOiuti,
        fightTrainerAiWazaHit128,
        fightTrainerAiWazaDamage128,
        fightTrainerAiWazaDamageFightPokemon128,
        fightWazaWzxTypeFuncNormal2,
        fightWazaWzxVariationFuncOiuchi,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit129,
        fightTrainerAiWazaDamage129,
        fightTrainerAiWazaDamageFightPokemon129,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKaihiDaun,
        fightTrainerAiWazaHit024,
        fightTrainerAiWazaDamage024,
        fightTrainerAiWazaDamageFightPokemon024,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouBougyoDaun,
        fightTrainerAiWazaHit069,
        fightTrainerAiWazaDamage069,
        fightTrainerAiWazaDamageFightPokemon069,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaKougekiAppu,
        fightTrainerAiWazaHit139,
        fightTrainerAiWazaDamage139,
        fightTrainerAiWazaDamageFightPokemon139,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueAteminage,
        fightTrainerAiWazaHit078,
        fightTrainerAiWazaDamage078,
        fightTrainerAiWazaDamageFightPokemon078,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKaihuku1,
        fightTrainerAiWazaHit132,
        fightTrainerAiWazaDamage132,
        fightTrainerAiWazaDamageFightPokemon132,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncWeatherHP,
    },
    {
        fightTrainerAiWazaValueKaihuku1,
        fightTrainerAiWazaHit133,
        fightTrainerAiWazaDamage133,
        fightTrainerAiWazaDamageFightPokemon133,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncWeatherHP,
    },
    {
        fightTrainerAiWazaValueKaihuku1,
        fightTrainerAiWazaHit134,
        fightTrainerAiWazaDamage134,
        fightTrainerAiWazaDamageFightPokemon134,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncWeatherHP,
    },
    {
        fightTrainerAiWazaValueTokubetuYuusen,
        fightTrainerAiWazaHit135,
        fightTrainerAiWazaDamage135,
        fightTrainerAiWazaDamageFightPokemon135,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValuePhyKuritikaru,
        fightTrainerAiWazaHit043,
        fightTrainerAiWazaDamage043,
        fightTrainerAiWazaDamageFightPokemon043,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit146,
        fightTrainerAiWazaDamage146,
        fightTrainerAiWazaDamageFightPokemon146,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueAmagoi,
        fightTrainerAiWazaHit136,
        fightTrainerAiWazaDamage136,
        fightTrainerAiWazaDamageFightPokemon136,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNihonbare,
        fightTrainerAiWazaHit137,
        fightTrainerAiWazaDamage137,
        fightTrainerAiWazaDamageFightPokemon137,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouTokubouDaun,
        fightTrainerAiWazaHit072,
        fightTrainerAiWazaDamage072,
        fightTrainerAiWazaDamageFightPokemon072,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMiraakooto,
        fightTrainerAiWazaHit144,
        fightTrainerAiWazaDamage144,
        fightTrainerAiWazaDamageFightPokemon144,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueJikoanji,
        fightTrainerAiWazaHit143,
        fightTrainerAiWazaDamage143,
        fightTrainerAiWazaDamageFightPokemon143,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKouPuraioritii,
        fightTrainerAiWazaHit103,
        fightTrainerAiWazaDamage103,
        fightTrainerAiWazaDamageFightPokemon103,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueZennouryokuappu,
        fightTrainerAiWazaHit140,
        fightTrainerAiWazaDamage140,
        fightTrainerAiWazaDamageFightPokemon140,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouTokubouDaun,
        fightTrainerAiWazaHit072,
        fightTrainerAiWazaDamage072,
        fightTrainerAiWazaDamageFightPokemon072,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit148,
        fightTrainerAiWazaDamage148,
        fightTrainerAiWazaDamageFightPokemon148,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouBougyoDaun,
        fightTrainerAiWazaHit069,
        fightTrainerAiWazaDamage069,
        fightTrainerAiWazaDamageFightPokemon069,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSokubaku,
        fightTrainerAiWazaHit042,
        fightTrainerAiWazaDamage042,
        fightTrainerAiWazaDamageFightPokemon042,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit154,
        fightTrainerAiWazaDamage154,
        fightTrainerAiWazaDamageFightPokemon154,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNekodamasi,
        fightTrainerAiWazaHit158,
        fightTrainerAiWazaDamage158,
        fightTrainerAiWazaDamageFightPokemon158,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSawagu,
        fightTrainerAiWazaHit159,
        fightTrainerAiWazaDamage159,
        fightTrainerAiWazaDamageFightPokemon159,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTakuwaeru,
        fightTrainerAiWazaHit160,
        fightTrainerAiWazaDamage160,
        fightTrainerAiWazaDamageFightPokemon160,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit161,
        fightTrainerAiWazaDamage161,
        fightTrainerAiWazaDamageFightPokemon161,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncHakidasu,
    },
    {
        fightTrainerAiWazaValueKaihuku2,
        fightTrainerAiWazaHit162,
        fightTrainerAiWazaDamage162,
        fightTrainerAiWazaDamageFightPokemon162,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNomikomu,
    },
    {
        fightTrainerAiWazaValueIryokuHonoo,
        fightTrainerAiWazaHit004,
        fightTrainerAiWazaDamage004,
        fightTrainerAiWazaDamageFightPokemon004,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueArare,
        fightTrainerAiWazaHit164,
        fightTrainerAiWazaDamage164,
        fightTrainerAiWazaDamageFightPokemon164,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRandamuSentaku,
        fightTrainerAiWazaHit165,
        fightTrainerAiWazaDamage165,
        fightTrainerAiWazaDamageFightPokemon165,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueOdareru,
        fightTrainerAiWazaHit166,
        fightTrainerAiWazaDamage166,
        fightTrainerAiWazaDamageFightPokemon166,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueOnibi,
        fightTrainerAiWazaHit167,
        fightTrainerAiWazaDamage167,
        fightTrainerAiWazaDamageFightPokemon167,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMitizure,
        fightTrainerAiWazaHit168,
        fightTrainerAiWazaDamage168,
        fightTrainerAiWazaDamageFightPokemon168,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit169,
        fightTrainerAiWazaDamage169,
        fightTrainerAiWazaDamageFightPokemon169,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKiaipanti,
        fightTrainerAiWazaHit170,
        fightTrainerAiWazaDamage170,
        fightTrainerAiWazaDamageFightPokemon170,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKituke,
        fightTrainerAiWazaHit171,
        fightTrainerAiWazaDamage171,
        fightTrainerAiWazaDamageFightPokemon171,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKonoyubitomare,
        fightTrainerAiWazaHit172,
        fightTrainerAiWazaDamage172,
        fightTrainerAiWazaDamageFightPokemon172,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSizennotikara,
        (AiWazaFunction)fightTrainerAiWazaHit173,
        (AiWazaFunction)fightTrainerAiWazaDamage173,
        (AiWazaPokemonFunction)fightTrainerAiWazaDamageFightPokemon173,
        (WazaWzxTypeFunction)fightWazaWzxTypeFuncNull,
        fightWazaWzxVariationFuncNull,
    },
    {
        fightTrainerAiWazaValueJyuuden,
        fightTrainerAiWazaHit174,
        fightTrainerAiWazaDamage174,
        fightTrainerAiWazaDamageFightPokemon174,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRandamuSentaku,
        fightTrainerAiWazaHit175,
        fightTrainerAiWazaDamage175,
        fightTrainerAiWazaDamageFightPokemon175,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTedasuke,
        fightTrainerAiWazaHit176,
        fightTrainerAiWazaDamage176,
        fightTrainerAiWazaDamageFightPokemon176,
        fightWazaWzxTypeFuncTedasuke,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValuetorikku,
        fightTrainerAiWazaHit177,
        fightTrainerAiWazaDamage177,
        fightTrainerAiWazaDamageFightPokemon177,
        fightWazaWzxTypeFuncAttDefSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRandamuSentaku,
        fightTrainerAiWazaHit178,
        fightTrainerAiWazaDamage178,
        fightTrainerAiWazaDamageFightPokemon178,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit179,
        fightTrainerAiWazaDamage179,
        fightTrainerAiWazaDamageFightPokemon179,
        fightWazaWzxTypeFuncNegaigoto,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTokubetuYuusen,
        fightTrainerAiWazaHit180,
        fightTrainerAiWazaDamage180,
        fightTrainerAiWazaDamageFightPokemon180,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit181,
        fightTrainerAiWazaDamage181,
        fightTrainerAiWazaDamageFightPokemon181,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBakadikara,
        fightTrainerAiWazaHit182,
        fightTrainerAiWazaDamage182,
        fightTrainerAiWazaDamageFightPokemon182,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMajikkukooto,
        fightTrainerAiWazaHit183,
        fightTrainerAiWazaDamage183,
        fightTrainerAiWazaDamageFightPokemon183,
        fightWazaWzxTypeFuncMagiccort,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRisaikuru,
        fightTrainerAiWazaHit184,
        fightTrainerAiWazaDamage184,
        fightTrainerAiWazaDamageFightPokemon184,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRibenji,
        fightTrainerAiWazaHit185,
        fightTrainerAiWazaDamage185,
        fightTrainerAiWazaDamageFightPokemon185,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKawarawari,
        fightTrainerAiWazaHit186,
        fightTrainerAiWazaDamage186,
        fightTrainerAiWazaDamageFightPokemon186,
        fightWazaWzxTypeFuncKawarawari,
        fightWazaWzxVariationFuncKawarawari,
    },
    {
        fightTrainerAiWazaValueNemurare,
        fightTrainerAiWazaHit187,
        fightTrainerAiWazaDamage187,
        fightTrainerAiWazaDamageFightPokemon187,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHatakiotosu,
        fightTrainerAiWazaHit188,
        fightTrainerAiWazaDamage188,
        fightTrainerAiWazaDamageFightPokemon188,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueGamusyara,
        fightTrainerAiWazaHit189,
        fightTrainerAiWazaDamage189,
        fightTrainerAiWazaDamageFightPokemon189,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit190,
        fightTrainerAiWazaDamage190,
        fightTrainerAiWazaDamageFightPokemon190,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSukirusuwappu,
        fightTrainerAiWazaHit191,
        fightTrainerAiWazaDamage191,
        fightTrainerAiWazaDamageFightPokemon191,
        fightWazaWzxTypeFuncAttDefSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHuuin,
        fightTrainerAiWazaHit192,
        fightTrainerAiWazaDamage192,
        fightTrainerAiWazaDamageFightPokemon192,
        (WazaWzxTypeFunction)fightWazaWzxTypeFuncHuuin,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRihuressyu,
        fightTrainerAiWazaHit193,
        fightTrainerAiWazaDamage193,
        fightTrainerAiWazaDamageFightPokemon193,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMitizure,
        fightTrainerAiWazaHit194,
        fightTrainerAiWazaDamage194,
        fightTrainerAiWazaDamageFightPokemon194,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueYokodori,
        fightTrainerAiWazaHit195,
        fightTrainerAiWazaDamage195,
        fightTrainerAiWazaDamageFightPokemon195,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHimitunotikara,
        fightTrainerAiWazaHit197,
        fightTrainerAiWazaDamage197,
        fightTrainerAiWazaDamageFightPokemon197,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSorawotobu,
        fightTrainerAiWazaHit155,
        fightTrainerAiWazaDamage155,
        fightTrainerAiWazaDamageFightPokemon155,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRandamuSentaku,
        fightTrainerAiWazaHit213,
        fightTrainerAiWazaDamage213,
        fightTrainerAiWazaDamageFightPokemon213,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTokukouAppu,
        fightTrainerAiWazaHit053,
        fightTrainerAiWazaDamage053,
        fightTrainerAiWazaDamageFightPokemon053,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouTokubouDaun,
        fightTrainerAiWazaHit072,
        fightTrainerAiWazaDamage072,
        fightTrainerAiWazaDamageFightPokemon072,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouTokukouDaun,
        fightTrainerAiWazaHit071,
        fightTrainerAiWazaDamage071,
        fightTrainerAiWazaDamageFightPokemon071,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKougekiDaun,
        fightTrainerAiWazaHit058,
        fightTrainerAiWazaDamage058,
        fightTrainerAiWazaDamageFightPokemon058,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHurahuradansu,
        fightTrainerAiWazaHit199,
        fightTrainerAiWazaDamage199,
        fightTrainerAiWazaDamageFightPokemon199,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBureizukikku,
        fightTrainerAiWazaHit200,
        fightTrainerAiWazaDamage200,
        fightTrainerAiWazaDamageFightPokemon200,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit201,
        fightTrainerAiWazaDamage201,
        fightTrainerAiWazaDamageFightPokemon201,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKorogaru,
        fightTrainerAiWazaHit117,
        fightTrainerAiWazaDamage117,
        fightTrainerAiWazaDamageFightPokemon117,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncIceball,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit150,
        fightTrainerAiWazaDamage150,
        fightTrainerAiWazaDamageFightPokemon150,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKaihuku2,
        fightTrainerAiWazaHit032,
        fightTrainerAiWazaDamage032,
        fightTrainerAiWazaDamageFightPokemon032,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDokudokunokiba,
        fightTrainerAiWazaHit202,
        fightTrainerAiWazaDamage202,
        fightTrainerAiWazaDamageFightPokemon202,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouBougyoDaun,
        fightTrainerAiWazaHit069,
        fightTrainerAiWazaDamage069,
        fightTrainerAiWazaDamageFightPokemon069,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHandou,
        fightTrainerAiWazaHit080,
        fightTrainerAiWazaDamage080,
        fightTrainerAiWazaDamageFightPokemon080,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHandou,
        fightTrainerAiWazaHit080,
        fightTrainerAiWazaDamage080,
        fightTrainerAiWazaDamageFightPokemon080,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaKougekiAppu,
        fightTrainerAiWazaHit139,
        fightTrainerAiWazaDamage139,
        fightTrainerAiWazaDamageFightPokemon139,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit150,
        fightTrainerAiWazaDamage150,
        fightTrainerAiWazaDamageFightPokemon150,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueUezaabooru,
        fightTrainerAiWazaHit203,
        fightTrainerAiWazaDamage203,
        fightTrainerAiWazaDamageFightPokemon203,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncWeatherBall,
    },
    {
        fightTrainerAiWazaValueAroma,
        fightTrainerAiWazaHit102,
        fightTrainerAiWazaDamage102,
        fightTrainerAiWazaDamageFightPokemon102,
        fightWazaWzxTypeFuncAllAlly,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTokubouDaun,
        fightTrainerAiWazaHit062,
        fightTrainerAiWazaDamage062,
        fightTrainerAiWazaDamageFightPokemon062,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValuePhyKuritikaru,
        fightTrainerAiWazaHit043,
        fightTrainerAiWazaDamage043,
        fightTrainerAiWazaDamageFightPokemon043,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueOobaahiito,
        fightTrainerAiWazaHit204,
        fightTrainerAiWazaDamage204,
        fightTrainerAiWazaDamageFightPokemon204,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMiyaburu,
        fightTrainerAiWazaHit113,
        fightTrainerAiWazaDamage113,
        fightTrainerAiWazaDamageFightPokemon113,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKanarazuSubayasaDaun,
        fightTrainerAiWazaHit070,
        fightTrainerAiWazaDamage070,
        fightTrainerAiWazaDamageFightPokemon070,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueZennouryokuappu,
        fightTrainerAiWazaHit140,
        fightTrainerAiWazaDamage140,
        fightTrainerAiWazaDamageFightPokemon140,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTokubouDaun,
        fightTrainerAiWazaHit062,
        fightTrainerAiWazaDamage062,
        fightTrainerAiWazaDamageFightPokemon062,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNemurare,
        fightTrainerAiWazaHit001,
        fightTrainerAiWazaDamage001,
        fightTrainerAiWazaDamageFightPokemon001,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKusuguruDaun,
        fightTrainerAiWazaHit205,
        fightTrainerAiWazaDamage205,
        fightTrainerAiWazaDamageFightPokemon205,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKosumopawaa,
        fightTrainerAiWazaHit206,
        fightTrainerAiWazaDamage206,
        fightTrainerAiWazaDamageFightPokemon206,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit190,
        fightTrainerAiWazaDamage190,
        fightTrainerAiWazaDamageFightPokemon190,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouKonran,
        fightTrainerAiWazaHit076,
        fightTrainerAiWazaDamage076,
        fightTrainerAiWazaDamageFightPokemon076,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHittyuu,
        fightTrainerAiWazaHit017,
        fightTrainerAiWazaDamage017,
        fightTrainerAiWazaDamageFightPokemon017,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaHirumi,
        fightTrainerAiWazaHit150,
        fightTrainerAiWazaDamage150,
        fightTrainerAiWazaDamageFightPokemon150,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit207,
        fightTrainerAiWazaDamage207,
        fightTrainerAiWazaDamageFightPokemon207,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSokubaku,
        fightTrainerAiWazaHit042,
        fightTrainerAiWazaDamage042,
        fightTrainerAiWazaDamageFightPokemon042,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueItigekihissatu,
        fightTrainerAiWazaHit038,
        fightTrainerAiWazaDamage038,
        fightTrainerAiWazaDamageFightPokemon038,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouMeityuuDaun,
        fightTrainerAiWazaHit073,
        fightTrainerAiWazaDamage073,
        fightTrainerAiWazaDamageFightPokemon073,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHittyuu,
        fightTrainerAiWazaHit017,
        fightTrainerAiWazaDamage017,
        fightTrainerAiWazaDamageFightPokemon017,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoAppu,
        fightTrainerAiWazaHit051,
        fightTrainerAiWazaDamage051,
        fightTrainerAiWazaDamageFightPokemon051,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKoukanKinsi,
        fightTrainerAiWazaHit106,
        fightTrainerAiWazaDamage106,
        fightTrainerAiWazaDamageFightPokemon106,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKougekiAppu,
        fightTrainerAiWazaHit010,
        fightTrainerAiWazaDamage010,
        fightTrainerAiWazaDamageFightPokemon010,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHandou,
        fightTrainerAiWazaHit080,
        fightTrainerAiWazaDamage080,
        fightTrainerAiWazaDamageFightPokemon080,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBirudoAppu,
        fightTrainerAiWazaHit208,
        fightTrainerAiWazaDamage208,
        fightTrainerAiWazaDamageFightPokemon208,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTobihaneru,
        fightTrainerAiWazaHit155,
        fightTrainerAiWazaDamage155,
        fightTrainerAiWazaDamageFightPokemon155,
        fightWazaWzxTypeFuncTame,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueKanarazuSubayasaDaun,
        fightTrainerAiWazaHit070,
        fightTrainerAiWazaDamage070,
        fightTrainerAiWazaDamageFightPokemon070,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValuePoizunteeru,
        fightTrainerAiWazaHit209,
        fightTrainerAiWazaDamage209,
        fightTrainerAiWazaDamageFightPokemon209,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDouguUbau,
        fightTrainerAiWazaHit105,
        fightTrainerAiWazaDamage105,
        fightTrainerAiWazaDamageFightPokemon105,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit198,
        fightTrainerAiWazaDamage198,
        fightTrainerAiWazaDamageFightPokemon198,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHittyuu,
        fightTrainerAiWazaHit017,
        fightTrainerAiWazaDamage017,
        fightTrainerAiWazaDamageFightPokemon017,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit210,
        fightTrainerAiWazaDamage210,
        fightTrainerAiWazaDamageFightPokemon210,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueMeisou,
        fightTrainerAiWazaHit211,
        fightTrainerAiWazaDamage211,
        fightTrainerAiWazaDamageFightPokemon211,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSpeKuritikaru,
        fightTrainerAiWazaHit043,
        fightTrainerAiWazaDamage043,
        fightTrainerAiWazaDamageFightPokemon043,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueRyuunomai,
        fightTrainerAiWazaHit212,
        fightTrainerAiWazaDamage212,
        fightTrainerAiWazaDamageFightPokemon212,
        fightWazaWzxTypeFuncSpc,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit029,
        fightTrainerAiWazaDamage029,
        fightTrainerAiWazaDamageFightPokemon029,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueHittyuu,
        fightTrainerAiWazaHit017,
        fightTrainerAiWazaDamage017,
        fightTrainerAiWazaDamageFightPokemon017,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikouKonran,
        fightTrainerAiWazaHit076,
        fightTrainerAiWazaDamage076,
        fightTrainerAiWazaDamageFightPokemon076,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueToriaezutukae,
        fightTrainerAiWazaHit148,
        fightTrainerAiWazaDamage148,
        fightTrainerAiWazaDamageFightPokemon148,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueSaikobuusuto,
        fightTrainerAiWazaHit204,
        fightTrainerAiWazaDamage204,
        fightTrainerAiWazaDamageFightPokemon204,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNull,
        fightTrainerAiWazaHitNull,
        fightTrainerAiWazaDamageNull,
        fightTrainerAiWazaDamageFightPokemonNull,
        (WazaWzxTypeFunction)fightWazaWzxTypeFuncNull,
        fightWazaWzxVariationFuncNull,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDarkEnd,
        fightTrainerAiWazaHit048,
        fightTrainerAiWazaDamage048,
        fightTrainerAiWazaDamageFightPokemon048,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueIryokuHonoo,
        fightTrainerAiWazaHit004,
        fightTrainerAiWazaDamage004,
        fightTrainerAiWazaDamageFightPokemon004,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaMahi,
        fightTrainerAiWazaHit006,
        fightTrainerAiWazaDamage006,
        fightTrainerAiWazaDamageFightPokemon006,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuikaKoori,
        fightTrainerAiWazaHit005,
        fightTrainerAiWazaDamage005,
        fightTrainerAiWazaDamageFightPokemon005,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueTuujouIryoku,
        fightTrainerAiWazaHit000,
        fightTrainerAiWazaDamage000,
        fightTrainerAiWazaDamageFightPokemon000,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDarkWeather,
        fightTrainerAiWazaHit215,
        fightTrainerAiWazaDamage215,
        fightTrainerAiWazaDamageFightPokemon215,
        fightWazaWzxTypeFuncAtt,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDarkHold,
        fightTrainerAiWazaHit106,
        fightTrainerAiWazaDamage106,
        fightTrainerAiWazaDamageFightPokemon106,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDarkMist,
        fightTrainerAiWazaHit214,
        fightTrainerAiWazaDamage214,
        fightTrainerAiWazaDamageFightPokemon214,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDarkPanic,
        fightTrainerAiWazaHit049,
        fightTrainerAiWazaDamage049,
        fightTrainerAiWazaDamageFightPokemon049,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueBougyoDaun,
        fightTrainerAiWazaHit059,
        fightTrainerAiWazaDamage059,
        fightTrainerAiWazaDamageFightPokemon059,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDarkRemove,
        fightTrainerAiWazaHit216,
        fightTrainerAiWazaDamage216,
        fightTrainerAiWazaDamageFightPokemon216,
        fightWazaWzxTypeFuncAllEnemy,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueDarkHalf,
        fightTrainerAiWazaHit217,
        fightTrainerAiWazaDamage217,
        fightTrainerAiWazaDamageFightPokemon217,
        fightWazaWzxTypeFuncNormal,
        fightWazaWzxVariationFuncNormal,
    },
    {
        fightTrainerAiWazaValueNull,
        fightTrainerAiWazaHitNull,
        fightTrainerAiWazaDamageNull,
        fightTrainerAiWazaDamageFightPokemonNull,
        (WazaWzxTypeFunction)fightWazaWzxTypeFuncNull,
        fightWazaWzxVariationFuncNull,
    },
};

u32 waza_func_data_number = sizeof(waza_func_data) / sizeof(waza_func_data[0]);
