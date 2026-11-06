#include <dolphin/types.h>

typedef struct FIGHT_ACTION FIGHT_ACTION;
typedef u8 (*FightActionFunc)(FIGHT_ACTION*);
typedef struct FightActionKindData {
    s8 priority; FightActionFunc flow; FightActionFunc disp;
} FightActionKindData;

extern u8 fightActionFlowNullFunc(FIGHT_ACTION*);
extern u8 fightActionDispNullFunc(FIGHT_ACTION*);
extern u8 fightActionFlowKaijou(FIGHT_ACTION*);
extern u8 fightActionDispKaijou(FIGHT_ACTION*);
extern u8 fightActionFlowKaisiPre(FIGHT_ACTION*);
extern u8 fightActionDispKaisiPre(FIGHT_ACTION*);
extern u8 fightActionFlowKaisiNyuujouTrainer(FIGHT_ACTION*);
extern u8 fightActionDispKaisiNyuujouTrainer(FIGHT_ACTION*);
extern u8 fightActionFlowKaisiNyuujouPokemon(FIGHT_ACTION*);
extern u8 fightActionDispKaisiNyuujouPokemon(FIGHT_ACTION*);
extern u8 fightActionFlowKaisiPost(FIGHT_ACTION*);
extern u8 fightActionDispKaisiPost(FIGHT_ACTION*);
extern u8 fightActionFlowTenkouInit(FIGHT_ACTION*);
extern u8 fightActionDispTenkouInit(FIGHT_ACTION*);
extern u8 fightActionFlowAllFightTrainerSelectFightAction(FIGHT_ACTION*);
extern u8 fightActionDispAllFightTrainerSelectFightAction(FIGHT_ACTION*);
extern u8 fightActionFlowFightNigeru(FIGHT_ACTION*);
extern u8 fightActionDispFightNigeru(FIGHT_ACTION*);
extern u8 fightActionFlowFightOutPokemonIrekae(FIGHT_ACTION*);
extern u8 fightActionDispFightOutPokemonIrekae(FIGHT_ACTION*);
extern u8 fightActionFlowFightTrainerCall(FIGHT_ACTION*);
extern u8 fightActionDispFightTrainerCall(FIGHT_ACTION*);
extern u8 fightActionFlowAllFightOutPokemonDoFightAction(FIGHT_ACTION*);
extern u8 fightActionDispAllFightOutPokemonDoFightAction(FIGHT_ACTION*);
extern u8 fightActionFlowWazaKiaipantiPre(FIGHT_ACTION*);
extern u8 fightActionDispWazaKiaipantiPre(FIGHT_ACTION*);
extern u8 fightActionFlowOneTurnPost(FIGHT_ACTION*);
extern u8 fightActionDispOneTurnPost(FIGHT_ACTION*);
extern u8 fightActionFlowSyuuryouPre(FIGHT_ACTION*);
extern u8 fightActionDispSyuuryouPre(FIGHT_ACTION*);
extern u8 fightActionFlowSyuuryou(FIGHT_ACTION*);
extern u8 fightActionDispSyuuryou(FIGHT_ACTION*);
extern u8 fightActionFlowSyuuryouPost(FIGHT_ACTION*);
extern u8 fightActionDispSyuuryouPost(FIGHT_ACTION*);
extern u8 fightActionFlowHeijou(FIGHT_ACTION*);
extern u8 fightActionDispHeijou(FIGHT_ACTION*);
extern u8 fightActionFlowFightTrainerUseItem(FIGHT_ACTION*);
extern u8 fightActionDispFightTrainerUseItem(FIGHT_ACTION*);
extern u8 fightActionFlowFightOutPokemonOutWaza(FIGHT_ACTION*);
extern u8 fightActionDispFightOutPokemonOutWaza(FIGHT_ACTION*);

FightActionKindData fight_action_kind_data[] = {
    {-1, fightActionFlowNullFunc, fightActionDispNullFunc},
    {-1, fightActionFlowKaijou, fightActionDispKaijou},
    {-1, fightActionFlowKaisiPre, fightActionDispKaisiPre},
    {-1, fightActionFlowKaisiNyuujouTrainer, fightActionDispKaisiNyuujouTrainer},
    {-1, fightActionFlowKaisiNyuujouPokemon, fightActionDispKaisiNyuujouPokemon},
    {-1, fightActionFlowKaisiPost, fightActionDispKaisiPost},
    {-1, fightActionFlowTenkouInit, fightActionDispTenkouInit},
    {-1, fightActionFlowAllFightTrainerSelectFightAction, fightActionDispAllFightTrainerSelectFightAction},
    {0, fightActionFlowFightNigeru, fightActionDispFightNigeru},
    {3, fightActionFlowFightOutPokemonIrekae, fightActionDispFightOutPokemonIrekae},
    {2, fightActionFlowFightTrainerCall, fightActionDispFightTrainerCall},
    {-1, fightActionFlowAllFightOutPokemonDoFightAction, fightActionDispAllFightOutPokemonDoFightAction},
    {-1, fightActionFlowWazaKiaipantiPre, fightActionDispWazaKiaipantiPre},
    {-1, fightActionFlowOneTurnPost, fightActionDispOneTurnPost},
    {-1, fightActionFlowSyuuryouPre, fightActionDispSyuuryouPre},
    {-1, fightActionFlowSyuuryou, fightActionDispSyuuryou},
    {-1, fightActionFlowSyuuryouPost, fightActionDispSyuuryouPost},
    {-1, fightActionFlowHeijou, fightActionDispHeijou},
    {1, fightActionFlowFightTrainerUseItem, fightActionDispFightTrainerUseItem},
    {4, fightActionFlowFightOutPokemonOutWaza, fightActionDispFightOutPokemonOutWaza},
};

u32 fight_action_kind_data_number = 20;
