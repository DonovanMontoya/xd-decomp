#include <dolphin/types.h>

typedef struct FIGHT_TRAINER FIGHT_TRAINER;
typedef struct FightOutPokemon FightOutPokemon;
typedef struct FightAiAllWazaValid FightAiAllWazaValid;
typedef s32 (*FightComboAction)(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
typedef s32 (*FightComboContinue)(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16);
typedef struct FightComboId {
    u8 count; u8 inverted; FightComboAction action; FightComboContinue continuation;
} FightComboId;

extern s32 fightAiCombo_null(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_null_Continue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16);
extern s32 fightAiCombo_Nihonbare_Sooraabiimu_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Nihonbare_Honoo_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Amagoi_Kaminari_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Amagoi_Mizu_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Nihonbare_Whezaabooru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Amagoi_Whezaabooru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Sunaarasi_Whezaabooru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Arare_Whezaabooru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Kinokonohousi_Kiaipanti_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Nemurase_Yumekui_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Daibakuhatu_Koraeru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Tedasuke_Iryoku_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Zisin_Mamoru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Haradaiko_Zikoanzi_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Daibakuhatu_Daibakuhatu_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Hurahuradansu_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Zisin_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Daibakuhatu_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_StatusUp_Batontatti_1(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Batontatti_Nekodamasi_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Batontatti_Nekodamasi_Continue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16);
extern s32 fightAiCombo_Batontatti_Zikoanzi_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Batontatti_Zikoanzi_Continue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16);
extern s32 fightAiCombo_Makibisi_Hoeru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Konran_DefDown_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Amaikaori_Hubuki_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Amaikaori_Hubuki_Continue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16);
extern s32 fightAiCombo_Nihonbare_Asanohizasi_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Nihonbare_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Amagoi_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Sunaarasi_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Sukirusuwappu_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Sukirusuwappu_Irekae_Continue(FIGHT_TRAINER*, FightOutPokemon*, FightOutPokemon**, u16);
extern s32 fightAiCombo_Konoyubitomare_StatusUp_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Konoyubitomare_Kiaipanti_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Horobinouta_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Dokudoku_Karagenki_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Honoo_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Horobinouta_Irekae2_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Ibaru_Irekae_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Hakaikousen_Hoeru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Daibakuhatu_Horobinouta_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Migawari_Kisikaisei_1(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Torikku_Kodawarihatimaki_1(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Konran_DefDown_1(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Amaikaori_Hubuki_1(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Sukirusuwappu_Irekae_1(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Darkweather_DarkIryoku_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Darkmist_Darkpanic_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Darkmist_Darkhold_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Darkmist_Darkend_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_Darkdown_PhyatkIryoku_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);
extern s32 fightAiCombo_DarkWeather_Whezaabooru_2(FIGHT_TRAINER*, FightOutPokemon**, u16, FightOutPokemon**, u16, FightAiAllWazaValid*, u8);

FightComboId comboid[] = {
    {0, 0, fightAiCombo_null, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Nihonbare_Sooraabiimu_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Nihonbare_Honoo_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Amagoi_Kaminari_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Amagoi_Mizu_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Nihonbare_Whezaabooru_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Amagoi_Whezaabooru_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Sunaarasi_Whezaabooru_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Arare_Whezaabooru_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Kinokonohousi_Kiaipanti_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Nemurase_Yumekui_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Daibakuhatu_Koraeru_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Tedasuke_Iryoku_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Zisin_Mamoru_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Haradaiko_Zikoanzi_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Daibakuhatu_Daibakuhatu_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Hurahuradansu_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Zisin_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Daibakuhatu_Irekae_2, fightAiCombo_null_Continue},
    {1, 0, fightAiCombo_StatusUp_Batontatti_1, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Batontatti_Nekodamasi_2, fightAiCombo_Batontatti_Nekodamasi_Continue},
    {2, 0, fightAiCombo_Batontatti_Zikoanzi_2, fightAiCombo_Batontatti_Zikoanzi_Continue},
    {2, 0, fightAiCombo_Makibisi_Hoeru_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Konran_DefDown_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Amaikaori_Hubuki_2, fightAiCombo_Amaikaori_Hubuki_Continue},
    {2, 0, fightAiCombo_Nihonbare_Asanohizasi_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Nihonbare_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Amagoi_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Sunaarasi_Irekae_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Sukirusuwappu_Irekae_2, fightAiCombo_Sukirusuwappu_Irekae_Continue},
    {2, 0, fightAiCombo_Konoyubitomare_StatusUp_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Konoyubitomare_Kiaipanti_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Horobinouta_Irekae_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Dokudoku_Karagenki_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Honoo_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Horobinouta_Irekae2_2, fightAiCombo_null_Continue},
    {2, 1, fightAiCombo_Ibaru_Irekae_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Hakaikousen_Hoeru_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Daibakuhatu_Horobinouta_2, fightAiCombo_null_Continue},
    {1, 0, fightAiCombo_Migawari_Kisikaisei_1, fightAiCombo_null_Continue},
    {1, 0, fightAiCombo_Torikku_Kodawarihatimaki_1, fightAiCombo_null_Continue},
    {1, 0, fightAiCombo_Konran_DefDown_1, fightAiCombo_null_Continue},
    {1, 0, fightAiCombo_Amaikaori_Hubuki_1, fightAiCombo_null_Continue},
    {1, 0, fightAiCombo_Sukirusuwappu_Irekae_1, fightAiCombo_Sukirusuwappu_Irekae_Continue},
    {2, 0, fightAiCombo_Darkweather_DarkIryoku_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Darkmist_Darkpanic_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Darkmist_Darkhold_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Darkmist_Darkend_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_Darkdown_PhyatkIryoku_2, fightAiCombo_null_Continue},
    {2, 0, fightAiCombo_DarkWeather_Whezaabooru_2, fightAiCombo_null_Continue},
};
