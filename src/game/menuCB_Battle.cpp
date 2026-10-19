#define POKEMON_HPP_NO_PROTOTYPES
#include <game/pxdvs/app/hero/hero.hpp>
#include <dolphin/types.h>
struct _MENUCBWORK {u8 bytes[0xB4C0];};
extern u8 _CB[];
static const u16 VS_TRAINER_RANK_NUMBER[40]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
static const s8 VS_TRAINER_RANK_SELECT_TBL[4][2][3]={{{5,30,35},{5,30,30}},{{5,20,25},{5,20,20}},{{5,10,15},{5,10,10}},{{5,0,5},{5,0,0}}};
static const u16 VS_TRAINER_RANK_ENCOUNT_DATA[40]={15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54};
extern "C" {void GSflagOff(u32);s32 fightEncount(u32);u32 soundGetBGMID();void soundStop(u32,s32);void menuTitleBattleSelectFree();void menuCB_SetToolBattleModeFlag(s32);void menuTitleReadWazaSelectMenu();}
extern "C" u16 menuCB_Battle(_MENUCBWORK *work){u32 id;if(*(s32*)(_CB+4)==1)id=VS_TRAINER_RANK_ENCOUNT_DATA[*(u16*)(work->bytes+0x2654)];else switch(*(s32*)(work->bytes+8)){case 0:id=5;break;case 1:id=7;break;case 2:id=8;break;}GSflagOff(0x323);soundStop(soundGetBGMID(),0);menuTitleBattleSelectFree();menuCB_SetToolBattleModeFlag(1);u16 result=fightEncount(id);menuCB_SetToolBattleModeFlag(0);menuTitleReadWazaSelectMenu();return result;}
static void _menuCBBattle_DeleteAllItem(Hero*){}


extern "C" {
u16 HSD_Rand();
void *fightEncountDataBiosGetPtr(u16);
void fightEncountDataBiosSetBgmSndId(void *,u32);
void fightEncountDataBiosSetFightFloorDataId(void *,u16);
void fightEncountDataBiosSetFightKind(void *,s32);
void fightEncountDataBiosSetSyoukaiWzxDataId(void *,u16);
void fightEncountDataBiosSetFightType(void *,s32);
void fightEncountDataBiosSetFightTrainerDataId(void *,s32,u16);
void fightEncountDataBiosSetGSInputDevice(void *,s32,s32);
void menuCBBios_InitTrainerFromDataID(void *,u16,u16);
void menuCBTrainerBios_SetControlerID(void *,s32);
void menuCBTrainerBios_SetHomePlace(void *,s32);
u16 *GSmsgGetGSchar(u32);
void fightTrainerCreateFightTrainerDataIdToHero(u16,s32,Hero *,u16);
void heroBiosSetNamePtr(Hero *,u16 *);
void menuCBBios_InitTrainerFromHero(void *,Hero *,u32);
s32 menuCBBios_PortIDtoControlerID(s32);
void menuCBBios_CopyTrainer(void *,void *);
}
#define CB_LONG(offset) (*(s32 *)(_CB+(offset)))
#define CB_BYTE(offset) (*(s8 *)(_CB+(offset)))
#define WORK_LONG(offset) (*(s32 *)(work->bytes+(offset)))
#define WORK_SHORT(offset) (*(u16 *)(work->bytes+(offset)))
extern "C" s32 menuCB_InitBattle(_MENUCBWORK *work)
{
    static const u32 staBGM_imasugu[3]={0x4F2,0x4F2,0x4F2};
    static const u32 staBGM_tunaide[3]={0x4F3,0x4F3,0x4F3};
    static const u16 staColosseum[6]={0x24,0x26,0x25,0x3C,0x3D,0x3E};
    static const u16 staColosseum_imasugu[6]={0x24,0x26,0x25,0x3C,0x3D,0x3E};
    static const u16 staDefaultNameID[3]={0x3B20,0x3B21,0x3B22};
    Hero hero;
    u16 encounterId;
    void *encounter;
    s32 battleMode,encounterMode,fightMode,typeMode,partyMode,trainerMode,copyMode,inputMode;
    u32 bgm;
    u16 floorId;
    u16 random,nameRandom;
    u16 opponentRank,playerRank,opponentTrainer,playerTrainer,savedRank,character;
    u16 *name,*nameOut;
    encounterId = 0;
    if (CB_BYTE(0xB4A1) == -1) {
        s8 playerBase = VS_TRAINER_RANK_SELECT_TBL[WORK_LONG(0xAFD8)][WORK_LONG(0xAFD4)][1];
        s8 count = VS_TRAINER_RANK_SELECT_TBL[WORK_LONG(0xAFD8)][WORK_LONG(0xAFD4)][0];
        s8 opponentBase = VS_TRAINER_RANK_SELECT_TBL[WORK_LONG(0xAFD8)][WORK_LONG(0xAFD4)][2];
        battleMode = WORK_LONG(0xAFD4);
        if (battleMode == 0) {
            random = HSD_Rand();
            WORK_SHORT(0x1334) = (u16) (playerBase + (random % (u16) count));
            WORK_SHORT(0x2654) = (u16) (opponentBase + (HSD_Rand() % (u16) count));
        } else {
            WORK_SHORT(0x1334) = (u16) (playerBase + (HSD_Rand() % (u16) count));
            do {
                WORK_SHORT(0x2654) = (u16) ((u16) opponentBase + (HSD_Rand() % (u16) count));
            } while ((u16) WORK_SHORT(0x1334) == (u16) WORK_SHORT(0x2654));
            if ((s32) (HSD_Rand() & 0x80) != 0) {
                WORK_SHORT(0x1334) += 5;
                WORK_SHORT(0x2654) += 5;
            }
        }
    }
    if ((s32) CB_LONG(0x4) == 1) {
        encounterId = VS_TRAINER_RANK_ENCOUNT_DATA[WORK_SHORT(0x2654)];
    } else {
        encounterMode = WORK_LONG(0x8);
        switch (encounterMode) {
        case 0:
            encounterId = 5;
            break;
        case 1:
            encounterId = 7;
            break;
        case 2:
            encounterId = 8;
            break;
        }
    }
    encounter = fightEncountDataBiosGetPtr(encounterId);
    WORK_LONG(0x9C7C) = (s32) (WORK_LONG(0x9C7C) + 1);
    if ((s32) CB_LONG(0x4) == 1) {
        WORK_LONG(0x9C7C) = (s32) (WORK_LONG(0x9C7C) % 3);
        bgm = staBGM_imasugu[WORK_LONG(0x9C7C)];
        if ((s32) WORK_LONG(0xAFD8) == 0) {
            bgm = 0x5CD;
        }
    } else {
        WORK_LONG(0x9C7C) = (s32) (WORK_LONG(0x9C7C) % 3);
        bgm = staBGM_tunaide[WORK_LONG(0x9C7C)];
    }
    fightEncountDataBiosSetBgmSndId(encounter, bgm);
    if ((s32) CB_LONG(0x4) != 1) {
        if ((s32) CB_LONG(0xAFFC) == 6) {
            WORK_LONG(0x10) = (s32) (HSD_Rand() % 6);
        }
        floorId = staColosseum[WORK_LONG(0x10)];
    } else {
        WORK_LONG(0x10) = (s32) (HSD_Rand() % 6);
        floorId = staColosseum_imasugu[WORK_LONG(0x10)];
    }
    fightEncountDataBiosSetFightFloorDataId(encounter, floorId);
    fightMode = WORK_LONG(0x4);
    switch (fightMode) {
    case 0:
        fightEncountDataBiosSetFightKind(encounter, 0xB);
        fightEncountDataBiosSetSyoukaiWzxDataId(encounter, 0);
        break;
    default:
    case 1:
        if ((s32) WORK_LONG(0xAFD4) == 0) {
            fightEncountDataBiosSetFightKind(encounter, 0x11);
        } else {
            fightEncountDataBiosSetFightKind(encounter, 0xA);
        }
        fightEncountDataBiosSetSyoukaiWzxDataId(encounter, 0);
        break;
    }
    typeMode = WORK_LONG(0x4);
    switch (typeMode) {
    case 0:
        partyMode = WORK_LONG(0x8);
        switch (partyMode) {
        case 1:
            fightEncountDataBiosSetFightType(encounter, 0x18);
            break;
        case 2:
            fightEncountDataBiosSetFightType(encounter, 0x24);
            break;
        default:
            fightEncountDataBiosSetFightType(encounter, 0x17);
            break;
        }
        break;
    default:
    case 1:
        fightEncountDataBiosSetFightType(encounter, 0x10);
        break;
    }
    trainerMode = WORK_LONG(0x4);
    switch (trainerMode) {
    case 1:
        opponentRank = WORK_SHORT(0x2654);
        playerRank = WORK_SHORT(0x1334);
        opponentTrainer = VS_TRAINER_RANK_NUMBER[opponentRank];
        playerTrainer = VS_TRAINER_RANK_NUMBER[playerRank];
        menuCBBios_InitTrainerFromDataID(work->bytes + 0x1338, opponentTrainer, encounterId);
        WORK_SHORT(0x1338) = opponentTrainer;
        WORK_SHORT(0x2654) = opponentRank;
        menuCBTrainerBios_SetControlerID(work->bytes + 0x1338, CB_LONG(0xB0E0));
        _menuCBBattle_DeleteAllItem((Hero *)(work->bytes + 0x1364));
        _menuCBBattle_DeleteAllItem((Hero *)(work->bytes + 0x1CDC));
        if (CB_BYTE(0xB4A1) == -1) {
            nameRandom = HSD_Rand();
            CB_BYTE(0xB4A1) = (s8) (nameRandom % 3);
            name = GSmsgGetGSchar(staDefaultNameID[CB_BYTE(0xB4A1)]);
            nameOut = (u16 *)(_CB + 0xB4A2);
loop_56:
            character = *name;
            if (character != 0) {
                *nameOut = character;
                name++;
                nameOut++;
                goto loop_56;
            }
            *nameOut = 0;
        }
        fightTrainerCreateFightTrainerDataIdToHero(playerTrainer, menuCBBios_PortIDtoControlerID(0), &hero, encounterId);
        if ((s32) CB_LONG(0xB0E0) == 0) {
            heroBiosSetNamePtr(&hero, (u16 *)(_CB + 0xB4A2));
        }
        _menuCBBattle_DeleteAllItem(&hero);
        savedRank = WORK_SHORT(0x1334);
        menuCBBios_InitTrainerFromHero(work->bytes + 0x18, &hero, 0x1388);
        WORK_SHORT(0x1334) = savedRank;
        if ((s32) CB_LONG(0xB0E0) != 0) {
            WORK_SHORT(0x18) = playerTrainer;
        }
        menuCBTrainerBios_SetControlerID(work->bytes + 0x18, menuCBBios_PortIDtoControlerID(0));
        menuCBTrainerBios_SetHomePlace(work->bytes + 0x18, 0);
        break;
    case 0:
        copyMode = WORK_LONG(0x8);
        if (copyMode != 2) {
            if (copyMode < 2) {
                if (copyMode < 0) {

                } else {
                    WORK_LONG(0x4CC0) = 0;
                    WORK_LONG(0x5FE0) = 1;
                    WORK_LONG(0x7300) = 2;
                    WORK_LONG(0x8620) = 3;
                    menuCBBios_CopyTrainer(work->bytes + 0x18, work->bytes + 0x4C98);
                    menuCBBios_CopyTrainer(work->bytes + 0x1338, work->bytes + 0x5FB8);
                }
            }
        } else {
            menuCBBios_CopyTrainer(work->bytes + 0x18, work->bytes + ((WORK_LONG(0x4CC0) * 0x1320) + 0x4C98));
            menuCBBios_CopyTrainer(work->bytes + 0x1338, work->bytes + ((WORK_LONG(0x5FE0) * 0x1320) + 0x4C98));
            menuCBBios_CopyTrainer(work->bytes + 0x2658, work->bytes + ((WORK_LONG(0x7300) * 0x1320) + 0x4C98));
            menuCBBios_CopyTrainer(work->bytes + 0x3978, work->bytes + ((WORK_LONG(0x8620) * 0x1320) + 0x4C98));
        }
        break;
    }
    inputMode = WORK_LONG(0x8);
    if (inputMode != 2) {
        if (inputMode < 2) {
            if (inputMode < 0) {

            } else {
                goto block_74;
            }
        }
    } else {
        fightEncountDataBiosSetFightTrainerDataId(encounter, 2, WORK_SHORT(0x2658));
        fightEncountDataBiosSetFightTrainerDataId(encounter, 3, WORK_SHORT(0x3978));
        fightEncountDataBiosSetGSInputDevice(encounter, 2, WORK_LONG(0x267C));
        fightEncountDataBiosSetGSInputDevice(encounter, 3, WORK_LONG(0x399C));
block_74:
        fightEncountDataBiosSetFightTrainerDataId(encounter, 0, WORK_SHORT(0x18));
        fightEncountDataBiosSetFightTrainerDataId(encounter, 1, WORK_SHORT(0x1338));
        fightEncountDataBiosSetGSInputDevice(encounter, 0, WORK_LONG(0x3C));
        fightEncountDataBiosSetGSInputDevice(encounter, 1, WORK_LONG(0x135C));
    }
    return 0;
}
