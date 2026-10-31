#include <dolphin/types.h>

#pragma force_active on

struct Attest;
struct FIGHT_FLOOR;
struct FightFloor;
struct FightOutPokemon;
struct FightPokemon;
struct FightTrainer;
struct FightTypeData;
struct GamedataAttest;
struct Pokemon;

extern "C" {

extern "C" {
struct Attest {
    u8 _draft[1];
};
struct FIGHT_FLOOR {
    u8 _draft[1];
};
struct FightFloor {
    u8 _draft[1];
};
struct FightOutPokemon {
    u8 _draft[1];
};
struct FightPokemon {
    u8 _draft[1];
};
struct FightTrainer {
    u8 _draft[1];
};
struct FightTypeData {
    u8 _draft[1];
};
struct GamedataAttest {
    u8 _draft[1];
};
struct Pokemon {
    u8 _draft[1];
};

extern "C" {
s32 GBAMakeFromGSchar(u8* dst, const u16* src, void* gamedata);
void GSthreadSwitch(void);
s32 GetWazaDocGBA(u8* out, u16 wazaID);
long PKJB_BattleGetStatus(long ch, u32* out);
long PKJB_BattleRequest(long ch, const u8* data, int size);
long PKJB_EntryGetStatus(long ch, u32* out);
long PKJB_EntryRequest(long ch, u32 value);
long PKJB_ExchangeEnd(long ch);
long PKJB_ExchangeIsPrepared(long ch);
long PKJB_ExchangeStart(long ch, u8* data);
long PKJB_GetKey(long ch, u16* out);
long PKJB_IdleSend(long ch);
long PKJB_ReturnTitle(long ch);
long PKJB_SendWazaText(long ch, u8* data);
u32 SIProbe(s32 chan);
u8 exribbonGetNo(u32 index);
FightFloor* fightFloorBiosGetFightFloorPtr(void);
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, FightOutPokemon** out);
u32 fightFloorGetStatus(FIGHT_FLOOR* floor, u16 dataId, u16 status, u16 arg);
u8 fightFloorIsUseFightTimerCommand(FIGHT_FLOOR* floor);
u16 fightGetFightResultId(void);
u16 fightOutPokemonBiosGetZokuseiDataId(u8* p, u8 i);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon* fop, u16 banme, u8 initKeep, u16* outItemWaza);
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon* fop, u8 create);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon* fop);
void fightOutPokemonGetRndStatus(FightOutPokemon* fop, u32* rnd, u32* catchRnd);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon* fop);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon* fop, u16 id);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon* fp);
u16 fightPokemonGetSoubiItemDataId(FightPokemon* fp);
s32 fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u16, u16, void*, s32, s32, s32);
void* fightTargetGetPtr(u16 slotType, void* ptr, u16 type);
bool fightTimerCommandIsOver(void);
u8 fightTrainerBiosGetControllerId(FightTrainer* trainer);
u8 fightTrainerCheckCanIrekaeFightPokemon(FightTrainer* trainer, FightPokemon* fp);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FightTrainer* trainer, u16 index);
FightPokemon* fightTrainerGetValidFightPokemonPtr(FightTrainer* trainer, u16 index);
u8 fightTypeDataBiosGetEntryPokemonNum(FightTypeData* data);
u8 fightTypeDataBiosGetFightoutPokemonNum(FightTypeData* data);
FightTypeData* fightTypeDataBiosGetPtr(u16 id);
u8 fightTypeDataBiosGetTrainerNum(FightTypeData* data);
u8 gamedataAttestBiosGetLangareaId(GamedataAttest* attest);
s32 gbaCommandChangePokemon(s32 p0, s32 p1, u32 p2, s32 p3);
void gbaCommandChangePokemonEnd(s32 p0);
s32 gbaCommandChangePokemonIsPrepared(s32 p0);
s32 gbaCommandEntryPokemon(u32, u8*);
void gbaCommandEntryRequest(s32 p0, s32 p1, s32 p2, s32 p3);
s32 gbaCommandEntryResult(s32 p0, u32 *p1);
bool gbaCommandIsConnected(s32 gba);
u16 gbaCommandKeyPressed(s32 p0);
u32 gbaCommandRequestAction(s32 p0, s32 p1, s32 p2, s32 p3);
void gbaCommandSendWazaText(s32 p0, s32 p1);
s32 gbaCommandSetKeyState(s32 chan, s32 state);
u16 gbaPokemonConditonFromGC(s32);
s32 gbaPokemonFromGC(s32, s32*);
u32 gba_SIProbe(s32 chan);
void gba_SIProbe_ErrorCntClear(s32 p0);
void* memmove(void* dst, const void* src, size_t len);
void* memset(void* dst, int val, size_t n);
u8 menuCBBios_CurrentlyWorkingToolBattle();
u8 menuCBRule_DEOKISISUCamouflage(void);
s32 menuCB_GetToolBattleModeFlag();
Attest* pokemonBiosGetAttest(Pokemon* poke);
u16 pokemonBiosGetFightTrainerPokemonDataId(Pokemon* poke);
u16 pokemonBiosGetHp(Pokemon* poke);
u8 pokemonBiosGetLevel(Pokemon* poke);
u8 pokemonBiosGetMailId(Pokemon* poke);
u16 pokemonBiosGetMaxHp(Pokemon* poke);
char* pokemonBiosGetNicknamePtr(Pokemon* poke);
u16 pokemonBiosGetPokemonDataId(Pokemon* poke);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u16 wazaNum);
u8 pokemonBiosGetPokemonWazaPp(Pokemon* poke, u16 wazaNum);
u8 pokemonBiosGetPokerus(Pokemon* poke);
u32 pokemonBiosGetRnd(Pokemon* poke);
u8 pokemonBiosGetTokuseiFlag(Pokemon* poke);
void pokemonBiosSetTokuseiFlag(Pokemon* poke, bool data);
u8 pokemonGetDeoxysSel(u8 controllerId);
u8 pokemonGetSex(Pokemon* pokemon);
s32 wazaconv(void* hero, u8* out);
extern s32 _CB[];
}
extern "C++" {
static s32 _dummySelect(FightOutPokemon* p0, unsigned short p1, unsigned short p2);
static u16 _swap16(unsigned short p0);
static u32 _swap32(u32 value);
}
static u32 _SIProbe_Result[4] = { 0, 0, 0, 0 };
static u32 _SIProbe_Counter[4] = { 0, 0, 0, 0 };
static u8 gba_SIProbe_ErrorCnt[4];
static u16 _keyCounter[4];
static u16 _keyPressed[4];
static s32 _keyState[4];
static s32 _keyResult[4];
static u8 _needSelect;

extern "C" {
s32 gbaCommandKeyRead(s32 p0);
}

void gba_SIProbe_ErrorCntClear(s32 ch) {
    if (ch == -1) {
        gba_SIProbe_ErrorCnt[3] = 0;
        gba_SIProbe_ErrorCnt[2] = 0;
        gba_SIProbe_ErrorCnt[1] = 0;
        gba_SIProbe_ErrorCnt[0] = 0;
        return;
    }
    gba_SIProbe_ErrorCnt[ch] = 0;
}
}

extern "C" {
u32 gba_SIProbe(s32 p0) {
    return _SIProbe_Result[p0];
}
}

extern "C" {
#pragma push
#pragma peephole off
void gbaCommandChangePokemonEnd(s32 p0) {
    PKJB_ExchangeEnd(p0 - 1);
}
#pragma pop
}

extern "C" {
s32 gbaCommandChangePokemonIsPrepared(s32 port) {
    s32 status;

    status = PKJB_ExchangeIsPrepared(port - 1);
    if (status < 0) {
        _keyCounter[port - 1] = 0;
    } else if (status == 1 || status == 2) {
        if (++_keyCounter[port - 1] <= 10) {
            status = -1;
        }
    }

    return status;
}
}

extern "C" {
#pragma peephole off
struct GbaExchangePacket {
    u32 tag;
    u32 species;
    s32 pokemon[0x64 / 4];
    u8 ribbons[0xC];
};

s32 gbaCommandChangePokemon(s32 p0, s32 p1, u32 p2, s32 p3) {
    GbaExchangePacket packet;
    u8* ribbon;
    s32 i;

    packet.tag = _swap32(p2);
    packet.species = _swap32((p3 << 0x10) | pokemonBiosGetPokemonDataId((Pokemon*)p1));
    if (pokemonBiosGetPokemonDataId((Pokemon*)p1) == 0x181) {
        pokemonBiosSetTokuseiFlag((Pokemon*)p1, pokemonBiosGetTokuseiFlag((Pokemon*)p1) == 0);
    }
    gbaPokemonFromGC(p1, packet.pokemon);
    ribbon = packet.ribbons;
    memset(ribbon, 0, 0xC);
    for (i = 0; i < 0xB; i++) {
        *ribbon = exribbonGetNo(i);
        ribbon++;
    }
    s32 result = PKJB_ExchangeStart(p0 - 1, (u8*)&packet);
    _keyCounter[p0 - 1] = 0;
    return result;
}
#pragma peephole reset
}
u16 gbaCommandGetGBAChangePokemon(u32 value) {
    return value;
}

u32 gbaCommandGetWazaTarget(u32 state){return (state>>8)&0xff;}

u8 gbaCommandGetWazaDataId(u32 value) {
    return value;
}

u32 gbaCommandGetAction(u32 value) {
    return value >> 16;
}
struct GbaBattleMon {
 u16 hp;
 u8 condition;
 u8 hasItem : 1;
 u8 hasMail : 1;
 u8 pokerusStrain : 1;
 u8 pokerusDays : 1;
 u8 status : 4;
 u16 item;
 u16 pad_06;
 u16 moves[4];
 u8 pp[4];
 u8 moveInfo[4][0x50];
};

struct GbaBattleFoe {
 u8 name[10];
 u8 sex : 2;
 u8 isNidoranM : 1;
 u8 isNidoranF : 1;
 u8 isJapanese : 1;
 u8 controller : 3;
 u8 level;
 u32 rnd;
 u16 species;
 u16 hp;
 u16 maxHp;
 u16 form;
};

struct GbaBattleSnapshot {
 u32 partyIds : 24;
 u32 isIrekae : 1;
 u32 activeSlot : 7;
 u32 canSwitch : 24;
 u8 fighterCount;
 u32 rnd0;
 u32 rnd1;
 u16 species;
 u16 form;
 u16 moves[4];
 u8 pp[4];
 u16 moveFlags;
 u8 lockedMove : 4;
 u8 moveSelect : 4;
 u8 targetIndex : 4;
 u8 switchMode : 4;
 GbaBattleMon party[6];
 GbaBattleFoe foes[4];
};

#pragma push
#pragma peephole off
#pragma dont_inline on
u32 gbaCommandRequestAction(s32 port, s32 trainer, s32 slot, s32 irekae) {
    GbaBattleSnapshot snap;
    FightOutPokemon* targets[4];
    u8 controllers[4];
    u32 rnd0;
    u32 rnd1;
    FightOutPokemon* target;
    u32 reply;
    u16 locked;
    u16 fightType;
    FightTypeData* type;
    u8 trainerNum;
    u8 entryNum;
    u8 outNum;
    u8 fighterNum;
    FightTrainer* enemy;
    FightTrainer* other;
    FightOutPokemon* out;
    s32 i;
    u16 condition;
    s32 j;
    u32 partyIds;
    u32 canSwitch;
    Pokemon* pokemon;
    u8 pokerus;
    u16 waza;
    u8 count;
    Pokemon* outPokemon;
    u16 moveFlags;
    u16 lockedWaza;
    u8 result;
    u8 mode;
    s32 index;
    FightPokemon* fightPokemon;
    GamedataAttest* attest;
    u16 species;
    u16 form;
    u16 zokusei;
    u16 tokusei;
    s32 length;
    u32 size;
    s32 channel;
    s32 status;
    u16 wazaId;
    Pokemon* foePokemon;

    fightType = fightFloorGetStatus(0, 0, 0x14, 0);
    type = fightTypeDataBiosGetPtr(fightType);
    trainerNum = fightTypeDataBiosGetTrainerNum(type);
    entryNum = fightTypeDataBiosGetEntryPokemonNum(type);
    outNum = fightTypeDataBiosGetFightoutPokemonNum(type);
    fighterNum = trainerNum * outNum * 2;

    enemy = (FightTrainer*)fightTargetGetPtr(0xB, (void*)trainer, fightType);
    targets[0] = fightTrainerGetValidFightOutPokemonPtr(enemy, 0);
    controllers[0] = 1;
    if (trainerNum == 2) {
        other = (FightTrainer*)fightTargetGetPtr(7, enemy, fightType);
        targets[1] = fightTrainerGetValidFightOutPokemonPtr(other, 0);
        controllers[1] = fightTrainerBiosGetControllerId(other);
        other = (FightTrainer*)fightTargetGetPtr(9, enemy, fightType);
        targets[2] = fightTrainerGetValidFightOutPokemonPtr(other, 0);
        controllers[2] = fightTrainerBiosGetControllerId(other);
        other = (FightTrainer*)fightTargetGetPtr(10, enemy, fightType);
        targets[3] = fightTrainerGetValidFightOutPokemonPtr(other, 0);
        controllers[3] = fightTrainerBiosGetControllerId(other);
    } else if (outNum == 2) {
        targets[1] = fightTrainerGetValidFightOutPokemonPtr(enemy, 1);
        other = (FightTrainer*)fightTargetGetPtr(9, enemy, fightType);
        targets[2] = fightTrainerGetValidFightOutPokemonPtr(other, 0);
        targets[3] = fightTrainerGetValidFightOutPokemonPtr(other, 1);
        controllers[1] = 1;
        controllers[2] = 2;
        controllers[3] = 2;
    } else {
        targets[1] = fightTrainerGetValidFightOutPokemonPtr((FightTrainer*)fightTargetGetPtr(9, enemy, fightType), 0);
        controllers[1] = 1;
    }

    out = fightTrainerGetValidFightOutPokemonPtr((FightTrainer*)trainer, slot);
    snap.activeSlot = (u8)(outNum == 2 ? slot + 1 : 0);
    snap.isIrekae = (u8)irekae;
    snap.fighterCount = fighterNum;

    partyIds = 0;
    canSwitch = 0;
    for (i = 0; i < entryNum; i++) {
        fightPokemon = fightTrainerGetValidFightPokemonPtr((FightTrainer*)trainer, i);
        if (fightPokemon == 0) {
            break;
        }
        pokemon = fightPokemonGetPokemonPtr(fightPokemon);
        partyIds |= pokemonBiosGetFightTrainerPokemonDataId(pokemon) << (i * 4 + 8);
        canSwitch |= fightTrainerCheckCanIrekaeFightPokemon((FightTrainer*)trainer, fightPokemon) << (i * 4 + 8);
        pokerus = pokemonBiosGetPokerus(pokemon);
        snap.party[i].hp = _swap16(pokemonBiosGetHp(pokemon));
        condition = ((s32 (*)(Pokemon*))gbaPokemonConditonFromGC)(pokemon);
        snap.party[i].condition = condition;
        snap.party[i].hasItem = fightPokemonGetSoubiItemDataId(fightPokemon) != 0;
        snap.party[i].hasMail = pokemonBiosGetMailId(pokemon) != 0xFF;
        snap.party[i].pokerusDays = (pokerus & 0xF) != 0;
        snap.party[i].pokerusStrain = (pokerus & 0xF0) != 0;
        snap.party[i].status = condition >> 8;
        snap.party[i].item = _swap16(fightPokemonGetSoubiItemDataId(fightPokemon));
        for (j = 0; j < 4; j++) {
            waza = pokemonBiosGetPokemonWazaDataId(pokemon, j);
            snap.party[i].moves[j] = _swap16(waza);
            snap.party[i].pp[j] = pokemonBiosGetPokemonWazaPp(pokemon, j);
            GetWazaDocGBA(snap.party[i].moveInfo[j], waza);
        }
    }
    count = i;

    partyIds |= -(1 << (count * 4 + 8));
    snap.partyIds = _swap32(partyIds);
    snap.canSwitch = _swap32(canSwitch);

    moveFlags = 0;
    outPokemon = fightOutPokemonGetPokemonPtr(out);
    fightOutPokemonGetRndStatus(out, &rnd0, &rnd1);
    snap.rnd0 = _swap32(rnd0);
    snap.rnd1 = _swap32(rnd1);
    species = pokemonBiosGetPokemonDataId(outPokemon);
    snap.species = _swap16(species);
    if (species == 0x181) {
        zokusei = fightOutPokemonBiosGetZokuseiDataId((u8*)out, 0);
        form = zokusei == 0xA ? 1 : zokusei == 0xB ? 2 : zokusei == 0xF ? 3 : 0;
        snap.form = _swap16(form);
    } else {
        snap.form = 0;
    }

    if (irekae != 0) {
        mode = 0;
        index = 0;
    } else {
        mode = fightFloorCheckFightActionFightOutPokemonIrekaeSelect((FIGHT_FLOOR*)fightFloorBiosGetFightFloorPtr(),
                                                                     out, &target);
        if (mode == 2) {
            tokusei = fightOutPokemonGetTokuseiDataId(target);
            mode = tokusei == 0x17 ? 2 : tokusei == 0x2A ? 3 : tokusei == 0x47 ? 4 : 0;
        }
        for (index = fighterNum - 1; index > 0; index--) {
            if (target == targets[index]) {
                break;
            }
        }
    }
    snap.switchMode = mode;
    snap.targetIndex = index;
    snap.moveSelect = fightOutPokemonCheckFightActionWazaSelect(out, 0);

    for (j = 0; j < 4; j++) {
        _needSelect = 0;
        wazaId = pokemonBiosGetPokemonWazaDataId(outPokemon, j);
        snap.moves[j] = _swap16(wazaId);
        snap.pp[j] = pokemonBiosGetPokemonWazaPp(outPokemon, j);
        fightSeqSelectDefensePokemonPtr(out, wazaId, fightType, (void*)_dummySelect, 1, 0, -1);
        if (_needSelect != 0) {
            moveFlags |= 8 << (j * 4);
        }
        result = fightOutPokemonCheckCanOutOkWazaBanme(out, j, 1, &locked);
        moveFlags |= result << (j * 4);
        if (result == 5) {
            lockedWaza = locked;
        }
    }
    snap.moveFlags = _swap16(moveFlags);
    for (index = 3; index > 0; index--) {
        if (snap.moves[index] == _swap16(lockedWaza)) {
            break;
        }
    }
    snap.lockedMove = index;

    for (i = 0; i < fighterNum; i++) {
        memset(snap.foes[i].name, 0, sizeof(GbaBattleFoe));
        if (targets[i] == out) {
            snap.foes[i].name[0] = 0xFF;
        } else {
            foePokemon = fightOutPokemonGetPokemonPtr(targets[i]);
            attest = (GamedataAttest*)pokemonBiosGetAttest(foePokemon);
            length = GBAMakeFromGSchar(snap.foes[i].name, (const u16*)pokemonBiosGetNicknamePtr(foePokemon),
                                       (void*)gamedataAttestBiosGetLangareaId(attest));
            if (length < 10) {
                snap.foes[i].name[length] = 0xFF;
            }
            species = pokemonBiosGetPokemonDataId(foePokemon);
            snap.foes[i].sex = pokemonGetSex(foePokemon);
            snap.foes[i].isNidoranM = species == 0x20;
            snap.foes[i].isNidoranF = species == 0x1D;
            snap.foes[i].controller = controllers[i];
            if (gamedataAttestBiosGetLangareaId(attest) == 1) {
                snap.foes[i].isJapanese = 1;
            } else {
                snap.foes[i].isJapanese = 0;
            }
            snap.foes[i].level = pokemonBiosGetLevel(foePokemon);
            snap.foes[i].rnd = _swap32(pokemonBiosGetRnd(foePokemon));
            snap.foes[i].species = _swap16(pokemonBiosGetPokemonDataId(foePokemon));
            snap.foes[i].hp = _swap16(pokemonBiosGetHp(foePokemon));
            snap.foes[i].maxHp = _swap16(pokemonBiosGetMaxHp(foePokemon));
            snap.foes[i].form = 0;
            if (pokemonBiosGetPokemonDataId(foePokemon) == 0x19A) {
                if (menuCBRule_DEOKISISUCamouflage() != 0) {
                    if (((s32*)_CB)[2] == 2 || ((s32*)_CB)[7] == 0) {
                        snap.foes[i].form = _swap16(pokemonGetDeoxysSel(controllers[i]));
                    } else {
                        snap.foes[i].form = _swap16(pokemonGetDeoxysSel(controllers[i] + 1));
                    }
                }
                if (fightOutPokemonIsJoutaiDataId(targets[i], 0x10) == 1) {
                    snap.foes[i].form = 0;
                }
            }
        }
    }

    size = fighterNum * sizeof(GbaBattleFoe);
    memmove(&snap.party[count], snap.foes, size);
    channel = port - 1;
    PKJB_BattleRequest(channel, (const u8*)&snap, 0x24 + count * sizeof(GbaBattleMon) + size);
    gba_SIProbe_ErrorCntClear(channel);
    while (TRUE) {
        if (fightGetFightResultId() == 1) {
            PKJB_ReturnTitle(channel);
            return 0x50000;
        }
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1) {
            PKJB_ReturnTitle(channel);
            return 0x40000;
        }
        status = PKJB_BattleGetStatus(channel, &reply);
        if (status == 1) {
            gba_SIProbe_ErrorCnt[port - 1]++;
            if (gba_SIProbe_ErrorCnt[port - 1] != 2) {
                status = -1;
            }
        } else {
            gba_SIProbe_ErrorCntClear(channel);
        }
        if (status > 0) {
            return status | 0x50000;
        }
        if (status == 0) {
            return _swap32(reply);
        }
        GSthreadSwitch();
    }
}
#pragma pop

extern "C++" {
static s32 _dummySelect(FightOutPokemon* p0, unsigned short p1, unsigned short p2) {
    _needSelect = 1;
    return 0;
}
}

extern "C" {
s32 gbaCommandEntryPokemon(u32 selection,u8* positions){
    positions[0]=selection&15;
    positions[1]=(selection>>4)&15;
    positions[2]=(selection>>8)&15;
    positions[3]=(selection>>12)&15;
    positions[4]=(selection>>16)&15;
    positions[5]=(selection>>20)&15;
    return 0;
}
}

extern "C" {
#pragma push
#pragma peephole off
#pragma dont_inline on
s32 gbaCommandEntryResult(s32 port, u32* status) {
    u32 raw;
    s32 chan = port - 1;
    s32 result;

    *status = 0x02000000;
    result = PKJB_EntryGetStatus(chan, &raw);
    if (result == 1) {
        gba_SIProbe_ErrorCnt[port - 1]++;
        if (gba_SIProbe_ErrorCnt[port - 1] != 2) {
            result = -1;
        }
    } else {
        gba_SIProbe_ErrorCntClear(chan);
    }
    if (result < 0) {
        raw = 0x02000000;
    } else if (result != 0) {
        *status = 0x03000000;
        gbaCommandSetKeyState(port, 1);
        return result;
    } else {
        *status = _swap32(raw);
        if ((*status >> 24) == 0) {
            gbaCommandSetKeyState(port, 1);
        }
    }
    return 0;
}
#pragma pop
}

extern "C" {
#pragma push
#pragma peephole off
void gbaCommandEntryRequest(s32 p0, s32 p1, s32 p2, s32 p3) {
    PKJB_EntryRequest(p0 - 1, (p2 << 8) | ((p3 << 0x18) | p1));
}
#pragma pop
}

extern "C" {
void gbaCommandSendWazaText(s32 p0, s32 p1) {
    u8 buf[0x780];

    wazaconv((void*)p1, buf);
    PKJB_SendWazaText(p0 - 1, buf);
}
}

extern "C" {
u16 gbaCommandKeyPressed(s32 port) {
    return _keyPressed[port - 1];
}
}

extern "C" {
bool gbaCommandIsConnected(s32 port) {
    bool r = 0;
    if (_keyState[port - 1] != 0 && _keyResult[port - 1] == 0) {
        r = 1;
    }
    return r;
}
}

extern "C" {
#pragma push
#pragma peephole off
s32 gbaCommandSetKeyState(s32 port, s32 state) {
    s32 old = _keyState[port - 1];
    _keyState[port - 1] = state;
    _keyResult[port - 1] = 0;
    _keyCounter[port - 1] = 0;
    _keyPressed[port - 1] = 0;
    return old;
}
#pragma pop
extern "C" {
#pragma push
#pragma peephole off
#pragma dont_inline on
s32 gbaCommandKeyRead(s32 port) {
    u16 key;
    s32 result;

    if (port == 2) {
        u32 type;
        s32 i;
        for (i = 0; i < 4; i++) {
            type = SIProbe(i);
            if (menuCB_GetToolBattleModeFlag() == 1 && menuCBBios_CurrentlyWorkingToolBattle() != 0) {
                type = 0x40000;
            }
            if (type == 0x40000) {
                _SIProbe_Result[i] = type;
                _SIProbe_Counter[i] = 2;
            } else if (_SIProbe_Counter[i] == 0) {
                _SIProbe_Result[i] = type;
            } else {
                _SIProbe_Counter[i]--;
            }
        }
    }
    switch (_keyState[port - 1]) {
    case 1:
        result = PKJB_GetKey(port - 1, &key);
        if (result == 0) {
            _keyCounter[port - 1] = 0;
            _keyPressed[port - 1] = key;
        } else if (result <= 2 && ++_keyCounter[port - 1] <= 10) {
            result = 0;
        } else {
            _keyPressed[port - 1] = 0;
            gbaCommandSetKeyState(port, 0);
        }
        break;
    case 3:
        result = PKJB_IdleSend(port - 1);
        if (result == 0) {
            _keyCounter[port - 1] = 0;
        } else if (result <= 2 && ++_keyCounter[port - 1] <= 10) {
            result = 0;
        } else {
            _keyPressed[port - 1] = 0;
            gbaCommandSetKeyState(port, 0);
        }
        _keyPressed[port - 1] = 0;
        break;
    case 2:
        _keyPressed[port - 1] = 0;
        result = 0;
        break;
    default:
        _keyPressed[port - 1] = 0;
        result = 1;
        break;
    }
    _keyResult[port - 1] = result;
    return result;
}
#pragma pop
}

}

extern "C" {
extern "C++" {
#pragma push
#pragma peephole off
static u32 _swap32(unsigned long p0) {
    return (p0 >> 0x18U) | (((u32) (p0 & 0xFF0000) >> 8U) | ((p0 << 0x18) | ((p0 & 0xFF00) << 8)));
}
#pragma pop
}

extern "C++" {
#pragma push
#pragma peephole off
static u16 _swap16(unsigned short p0) {
    return (u16) ((p0 << 8) | ((s32) p0 >> 8));
}
#pragma pop
}
}

}

#pragma force_active reset
