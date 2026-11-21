#ifndef GAME_FIGHT_TRAINER_AI_COMBO_H
#define GAME_FIGHT_TRAINER_AI_COMBO_H

#include <dolphin/types.h>

typedef struct FIGHT_TRAINER FIGHT_TRAINER;
typedef struct FightOutPokemon FightOutPokemon;

typedef struct FightAiAllWazaValid {
    FightOutPokemon* attackers[2];
    FightOutPokemon* defenders[2];
    u16 moves[2];
    s8 slots[2];
    u8 eligible[2];
    u8 probability[2];
    u8 combination;
    u16 damage[2][2];
    u8 result[2];
    u8 reserved26;
    u16 field28;
} FightAiAllWazaValid;

typedef struct AiWazaWork {
    u8 count;
    u8 reserved[3];
} AiWazaWork;

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 FightComboAction(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
typedef u8 FightComboContinue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16);

typedef struct FightComboId {
    u8 count;
    u8 inverted;
    FightComboAction* action;
    FightComboContinue* continuation;
} FightComboId;

extern FightComboId comboid[];
extern AiWazaWork ai_allwaza_valid_work;

s32 fightAiCombo_Act(FIGHT_TRAINER*, FightOutPokemon**, u16, s32);
s32 fightAiCombo_ActContinue(FIGHT_TRAINER*, FightOutPokemon*, s32);
s32 fightAi_CopyAllWazaValidTable(FightAiAllWazaValid*, FightAiAllWazaValid*);

FightComboAction fightAiCombo_null;
FightComboContinue fightAiCombo_null_Continue;
FightComboAction fightAiCombo_Nihonbare_Sooraabiimu_2;
FightComboAction fightAiCombo_Nihonbare_Honoo_2;
FightComboAction fightAiCombo_Amagoi_Kaminari_2;
FightComboAction fightAiCombo_Amagoi_Mizu_2;
FightComboAction fightAiCombo_Nihonbare_Whezaabooru_2;
FightComboAction fightAiCombo_Amagoi_Whezaabooru_2;
FightComboAction fightAiCombo_Sunaarasi_Whezaabooru_2;
FightComboAction fightAiCombo_Arare_Whezaabooru_2;
FightComboAction fightAiCombo_Kinokonohousi_Kiaipanti_2;
FightComboAction fightAiCombo_Nemurase_Yumekui_2;
FightComboAction fightAiCombo_Daibakuhatu_Koraeru_2;
FightComboAction fightAiCombo_Tedasuke_Iryoku_2;
FightComboAction fightAiCombo_Zisin_Mamoru_2;
FightComboAction fightAiCombo_Haradaiko_Zikoanzi_2;
FightComboAction fightAiCombo_Daibakuhatu_Daibakuhatu_2;
FightComboAction fightAiCombo_Hurahuradansu_Irekae_2;
FightComboAction fightAiCombo_Zisin_Irekae_2;
FightComboAction fightAiCombo_Daibakuhatu_Irekae_2;
FightComboAction fightAiCombo_StatusUp_Batontatti_1;
FightComboAction fightAiCombo_Batontatti_Nekodamasi_2;
FightComboContinue fightAiCombo_Batontatti_Nekodamasi_Continue;
FightComboAction fightAiCombo_Batontatti_Zikoanzi_2;
FightComboContinue fightAiCombo_Batontatti_Zikoanzi_Continue;
FightComboAction fightAiCombo_Makibisi_Hoeru_2;
FightComboAction fightAiCombo_Konran_DefDown_2;
FightComboAction fightAiCombo_Amaikaori_Hubuki_2;
FightComboContinue fightAiCombo_Amaikaori_Hubuki_Continue;
FightComboAction fightAiCombo_Nihonbare_Asanohizasi_2;
FightComboAction fightAiCombo_Nihonbare_Irekae_2;
FightComboAction fightAiCombo_Amagoi_Irekae_2;
FightComboAction fightAiCombo_Sunaarasi_Irekae_2;
FightComboAction fightAiCombo_Sukirusuwappu_Irekae_2;
FightComboContinue fightAiCombo_Sukirusuwappu_Irekae_Continue;
FightComboAction fightAiCombo_Konoyubitomare_StatusUp_2;
FightComboAction fightAiCombo_Konoyubitomare_Kiaipanti_2;
FightComboAction fightAiCombo_Horobinouta_Irekae_2;
FightComboAction fightAiCombo_Dokudoku_Karagenki_2;
FightComboAction fightAiCombo_Honoo_Irekae_2;
FightComboAction fightAiCombo_Horobinouta_Irekae2_2;
FightComboAction fightAiCombo_Ibaru_Irekae_2;
FightComboAction fightAiCombo_Hakaikousen_Hoeru_2;
FightComboAction fightAiCombo_Daibakuhatu_Horobinouta_2;
FightComboAction fightAiCombo_Migawari_Kisikaisei_1;
FightComboAction fightAiCombo_Torikku_Kodawarihatimaki_1;
FightComboAction fightAiCombo_Konran_DefDown_1;
FightComboAction fightAiCombo_Amaikaori_Hubuki_1;
FightComboAction fightAiCombo_Sukirusuwappu_Irekae_1;
FightComboAction fightAiCombo_Darkweather_DarkIryoku_2;
FightComboAction fightAiCombo_Darkmist_Darkpanic_2;
FightComboAction fightAiCombo_Darkmist_Darkhold_2;
FightComboAction fightAiCombo_Darkmist_Darkend_2;
FightComboAction fightAiCombo_Darkdown_PhyatkIryoku_2;
FightComboAction fightAiCombo_DarkWeather_Whezaabooru_2;

#ifdef __cplusplus
}
#endif

typedef char FightComboIdSize[sizeof(FightComboId) == 12 ? 1 : -1];
typedef char FightAiAllWazaValidSize[sizeof(FightAiAllWazaValid) == 0x2C ? 1 : -1];

#endif
