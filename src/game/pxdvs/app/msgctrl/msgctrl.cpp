#pragma defer_codegen on
#include <game/pxdvs/app/msgctrl/msgctrlPrivate.hpp>

extern "C" { s32 msgctrlSndWait(MsgCtx* c); }
extern "C" { s32 msgctrlSndPlay(MsgCtx* c); }
extern "C" { s32 msgctrlBaseLineBias(MsgCtx* c); }
extern "C" { s32 msgctrlLineSpace(MsgCtx* c); }
extern "C" { s32 msgctrlIndentOff(MsgCtx* c); }
extern "C" { u32 msgctrlNpc(); }
extern "C" { u32 msgctrlTribe(); }
extern "C" { u32 msgctrlString2(); }
extern "C" { u32 msgctrlMenuMsgID2(); }
extern "C" { u32 msgctrlMenuMsgID(); }
extern "C" { s32 msgctrlTalkSE(MsgCtx* c); }
extern "C" { s32 msgctrlAlign(MsgCtx* c); }
extern "C" { s32 msgctrlShadow(MsgCtx* c); }
extern "C" { u16* msgctrlMenuMoney(); }
extern "C" { u16* msgctrlMenuFullDigit(); }
extern "C" { u32 msgctrlPokemonID(); }
extern "C" { u32 msgctrlString(); }
extern "C" { u16* msgctrlTime(); }
extern "C" { u16* msgctrlMoney(); }
extern "C" { u16* msgctrlMenuZDigit2(); }
extern "C" { u16* msgctrlMenuZDigit(); }
extern "C" { u16* msgctrlMenuHex2(); }
extern "C" { u16* msgctrlMenuHex(); }
extern "C" { u16* msgctrlMenuUDigit2(); }
extern "C" { u16* msgctrlMenuUDigit(); }
extern "C" { s32 msgctrlSeOn(); }
extern "C" { s32 msgctrlSeOff(); }
extern "C" { s32 msgctrlSetPeopleTalkFlag(); }
extern "C" { u32 msgctrlPasoName(); }
extern "C" { u32 msgctrlItemName(); }
extern "C" { u32 msgctrlWazaName(); }
extern "C" { u32 msgctrlTrainerClientno(); }
extern "C" { u32 msgctrlTrainerEnename2(); }
extern "C" { u32 msgctrlTrainerEnename(); }
extern "C" { u32 msgctrlTrainerLose(); }
extern "C" { u32 msgctrlTrainerName(); }
extern "C" { u32 msgctrlTrainerType(); }
extern "C" { u16* msgctrlSideDefenceNameno(); }
extern "C" { u16* msgctrlSideDefenceNamewo(); }
extern "C" { u16* msgctrlSideDefenceNameha(); }
extern "C" { u16* msgctrlSideAttackNameno(); }
extern "C" { u16* msgctrlSideAttackNamewo(); }
extern "C" { u16* msgctrlSideAttackNameha(); }
extern "C++" { static u16* _msgctrlSideName(FightOutPokemon* pokemon, u8 kind); }
extern "C" { u16* msgctrlClientnowork(); }
extern "C" { u32 msgctrlSpeabiNamet(); }
extern "C" { u32 msgctrlSpeabiNamec(); }
extern "C" { u32 msgctrlSpeabiNamed(); }
extern "C" { u32 msgctrlSpeabiNamea(); }
extern "C" { u32 msgctrlEnemyTmons2(); }
extern "C" { u32 msgctrlEnemyTmons(); }
extern "C" { u32 msgctrlEnemyMons2(); }
extern "C" { u32 msgctrlEnemyMons(); }
extern "C" { u32 msgctrlMyMons2(); }
extern "C" { u32 msgctrlMyMons(); }
extern "C" { u32 msgctrlMyName(); }
extern "C" { u16* msgctrlTsuikaMons(); }
extern "C" { u16* msgctrlClientMos(); }
extern "C" { u16* msgctrlDeffenceMons(); }
extern "C" { u16* msgctrlAttackMons(); }
extern "C" { u32 msgctrlEvStrBuf2(); }
extern "C" { u32 msgctrlEvStrBuf1(); }
extern "C" { u32 msgctrlEvStrBuf0(); }
extern "C" { u16* msgctrlDigitH2(); }
extern "C" { u16* msgctrlDigitH(); }
extern "C" { u16* msgctrlMenuMoneyH(); }
extern "C" { u16* msgctrlTimeH(); }
extern "C" { u16* msgctrlMoneyH(); }
extern "C" { u16* msgctrlMenuZDigitH2(); }
extern "C" { u16* msgctrlMenuZDigitH(); }
extern "C" { u16* msgctrlMenuHexH2(); }
extern "C" { u16* msgctrlMenuHexH(); }
extern "C" { u16* msgctrlMenuUDigitH2(); }
extern "C" { u16* msgctrlMenuUDigitH(); }
extern "C" { u16* msgctrlMenuDigitH2(); }
extern "C" { u16* msgctrlMenuDigitH(); }
extern "C" { u32 msgctrlWaza(); }
extern "C" { u32 msgctrlMenuMsg2(); }
extern "C" { u32 msgctrlMenuMsg(); }
extern "C" { u32 msgctrlMenuPokemon(); }
extern "C" { u16* msgctrlMenuDigit2(); }
extern "C" { u16* msgctrlMenuDigit(); }
extern "C" { u32 msgctrlPokemon2(); }
extern "C" { u32 msgctrlPokemon(); }
extern "C" { u32 msgctrlMsgID(); }
extern "C" { u16* msgctrlDigit2(); }
extern "C" { u16* msgctrlDigit(); }
extern "C" { u32 msgctrlItem2(); }
extern "C" { u32 msgctrlItem(); }
extern "C" { u16* msgctrlHizuki(); }
extern "C" { u16* msgctrlHero(); }
extern "C" { s32 msgctrlWait(MsgCtx* c); }
extern "C" { s32 msgctrlPalette(MsgCtx* c); }
extern "C" { s32 msgctrlColor(MsgCtx* c); }
extern "C" { s32 msgctrlFont(MsgCtx* c); }
extern "C" { s32 msgctrlRubyEnd(MsgCtx* c); }
extern "C" { s32 msgctrlRubyTop(MsgCtx* c); }
extern "C" { s32 msgctrlRubyStart(MsgCtx* c); }
extern "C" { s32 msgctrlKeyWait(MsgCtx* c); }
extern "C" { s32 msgctrlCheckWait(MsgCtx* c); }
extern "C" { s32 msgctrlCheckEnd(MsgCtx* c); }
extern "C" { s32 msgctrlKeyEnd(MsgCtx* c); }
extern "C" { s32 msgctrlCR(MsgCtx* c); }
extern "C++" { static u16* _msgctrlMakeDigit(u16* buf, s32 len, u32 val, s32 mode); }
extern "C" { void msgctrlSetValue(s32 id, u32 value); }
extern "C" { void msgctrlInitValue(); }

extern "C" { s32 msgctrlSndWait(MsgCtx* c); }
extern "C" { s32 msgctrlSndPlay(MsgCtx* c); }
extern "C" { s32 msgctrlBaseLineBias(MsgCtx* c); }
extern "C" { s32 msgctrlLineSpace(MsgCtx* c); }
extern "C" { s32 msgctrlIndentOff(MsgCtx* c); }
extern "C" { u32 msgctrlNpc(); }
extern "C" { u32 msgctrlTribe(); }
extern "C" { u32 msgctrlString2(); }
extern "C" { u32 msgctrlMenuMsgID2(); }
extern "C" { u32 msgctrlMenuMsgID(); }
extern "C" { s32 msgctrlTalkSE(MsgCtx* c); }
extern "C" { s32 msgctrlAlign(MsgCtx* c); }
extern "C" { s32 msgctrlShadow(MsgCtx* c); }
extern "C" { u16* msgctrlMenuMoney(); }
extern "C" { u16* msgctrlMenuFullDigit(); }
extern "C" { u32 msgctrlPokemonID(); }
extern "C" { u32 msgctrlString(); }
extern "C" { u16* msgctrlTime(); }
extern "C" { u16* msgctrlMoney(); }
extern "C" { u16* msgctrlMenuZDigit2(); }
extern "C" { u16* msgctrlMenuZDigit(); }
extern "C" { u16* msgctrlMenuHex2(); }
extern "C" { u16* msgctrlMenuHex(); }
extern "C" { u16* msgctrlMenuUDigit2(); }
extern "C" { u16* msgctrlMenuUDigit(); }
extern "C" { s32 msgctrlSeOn(); }
extern "C" { s32 msgctrlSeOff(); }
extern "C" { s32 msgctrlSetPeopleTalkFlag(); }
extern "C" { u32 msgctrlPasoName(); }
extern "C" { u32 msgctrlItemName(); }
extern "C" { u32 msgctrlWazaName(); }
extern "C" { u32 msgctrlTrainerClientno(); }
extern "C" { u32 msgctrlTrainerEnename2(); }
extern "C" { u32 msgctrlTrainerEnename(); }
extern "C" { u32 msgctrlTrainerLose(); }
extern "C" { u32 msgctrlTrainerName(); }
extern "C" { u32 msgctrlTrainerType(); }
extern "C" { u16* msgctrlSideDefenceNameno(); }
extern "C" { u16* msgctrlSideDefenceNamewo(); }
extern "C" { u16* msgctrlSideDefenceNameha(); }
extern "C" { u16* msgctrlSideAttackNameno(); }
extern "C" { u16* msgctrlSideAttackNamewo(); }
extern "C" { u16* msgctrlSideAttackNameha(); }
extern "C++" { static u16* _msgctrlSideName(FightOutPokemon* pokemon, u8 kind); }
extern "C" { u16* msgctrlClientnowork(); }
extern "C" { u32 msgctrlSpeabiNamet(); }
extern "C" { u32 msgctrlSpeabiNamec(); }
extern "C" { u32 msgctrlSpeabiNamed(); }
extern "C" { u32 msgctrlSpeabiNamea(); }
extern "C" { u32 msgctrlEnemyTmons2(); }
extern "C" { u32 msgctrlEnemyTmons(); }
extern "C" { u32 msgctrlEnemyMons2(); }
extern "C" { u32 msgctrlEnemyMons(); }
extern "C" { u32 msgctrlMyMons2(); }
extern "C" { u32 msgctrlMyMons(); }
extern "C" { u32 msgctrlMyName(); }
extern "C" { u16* msgctrlTsuikaMons(); }
extern "C" { u16* msgctrlClientMos(); }
extern "C" { u16* msgctrlDeffenceMons(); }
extern "C" { u16* msgctrlAttackMons(); }
extern "C" { u32 msgctrlEvStrBuf2(); }
extern "C" { u32 msgctrlEvStrBuf1(); }
extern "C" { u32 msgctrlEvStrBuf0(); }
extern "C" { u16* msgctrlDigitH2(); }
extern "C" { u16* msgctrlDigitH(); }
extern "C" { u16* msgctrlMenuMoneyH(); }
extern "C" { u16* msgctrlTimeH(); }
extern "C" { u16* msgctrlMoneyH(); }
extern "C" { u16* msgctrlMenuZDigitH2(); }
extern "C" { u16* msgctrlMenuZDigitH(); }
extern "C" { u16* msgctrlMenuHexH2(); }
extern "C" { u16* msgctrlMenuHexH(); }
extern "C" { u16* msgctrlMenuUDigitH2(); }
extern "C" { u16* msgctrlMenuUDigitH(); }
extern "C" { u16* msgctrlMenuDigitH2(); }
extern "C" { u16* msgctrlMenuDigitH(); }
extern "C" { u32 msgctrlWaza(); }
extern "C" { u32 msgctrlMenuMsg2(); }
extern "C" { u32 msgctrlMenuMsg(); }
extern "C" { u32 msgctrlMenuPokemon(); }
extern "C" { u16* msgctrlMenuDigit2(); }
extern "C" { u16* msgctrlMenuDigit(); }
extern "C" { u32 msgctrlPokemon2(); }
extern "C" { u32 msgctrlPokemon(); }
extern "C" { u32 msgctrlMsgID(); }
extern "C" { u16* msgctrlDigit2(); }
extern "C" { u16* msgctrlDigit(); }
extern "C" { u32 msgctrlItem2(); }
extern "C" { u32 msgctrlItem(); }
extern "C" { u16* msgctrlHizuki(); }
extern "C" { u16* msgctrlHero(); }
extern "C" { s32 msgctrlWait(MsgCtx* c); }
extern "C" { s32 msgctrlPalette(MsgCtx* c); }
extern "C" { s32 msgctrlColor(MsgCtx* c); }
extern "C" { s32 msgctrlFont(MsgCtx* c); }
extern "C" { s32 msgctrlRubyEnd(MsgCtx* c); }
extern "C" { s32 msgctrlRubyTop(MsgCtx* c); }
extern "C" { s32 msgctrlRubyStart(MsgCtx* c); }
extern "C" { s32 msgctrlKeyWait(MsgCtx* c); }
extern "C" { s32 msgctrlCheckWait(MsgCtx* c); }
extern "C" { s32 msgctrlCheckEnd(MsgCtx* c); }
extern "C" { s32 msgctrlKeyEnd(MsgCtx* c); }
extern "C" { s32 msgctrlCR(MsgCtx* c); }
extern "C++" { static u16* _msgctrlMakeDigit(u16* buf, s32 len, u32 val, s32 mode); }
extern "C" { void msgctrlSetValue(s32 id, u32 value); }
extern "C" { void msgctrlInitValue(); }

static u16 half_digit_code[16] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46};
static u16 full_digit_code[16] = {0xFF10, 0xFF11, 0xFF12, 0xFF13, 0xFF14, 0xFF15, 0xFF16, 0xFF17, 0xFF18, 0xFF19, 0xFF21, 0xFF22, 0xFF23, 0xFF24, 0xFF25, 0xFF26};
static u32 _EV_STR_BUF0;
static u32 _EV_STR_BUF1;
static u32 _EV_STR_BUF2;
static FightOutPokemon* _ATTACK_MONS;
static FightOutPokemon* _DEFENCE_MONS;
static FightOutPokemon* _CLIENT_MONS;
static FightOutPokemon* _TSUIKA_MONS;
static u32 _MY_NAME;
static u32 _MY_MONS;
static u32 _MY_MONS2;
static u32 _ENEMY_MONS;
static u32 _ENEMY_MONS2;
static u32 _ENEMY_TMONS;
static u32 _ENEMY_TMONS2;
static u32 _SPEABI_NAMEA;
static u32 _SPEABI_NAMED;
static u32 _SPEABI_NAMEC;
static u32 _SPEABI_NAMET;
static FightOutPokemon* _CLIENTNOWORK;
static FightOutPokemon* _SIDE_ATTACK_NAMEHA;
static FightOutPokemon* _SIDE_ATTACK_NAMEWO;
static FightOutPokemon* _SIDE_ATTACK_NAMENO;
static u32 _TRAINER_TYPE;
static u32 _TRAINER_NAME;
static u32 _TRAINER_LOSE;
static u32 _TRAINER_ENENAME;
static u32 _TRAINER_ENENAME2;
static u32 _TRAINER_CLIENTNO;
static u32 _WAZA_NAME;
static u32 _ITEM_NAME;
static u32 _PASO_NAME;
static FightOutPokemon* _SIDE_DEFENCE_NAMEHA;
static FightOutPokemon* _SIDE_DEFENCE_NAMEWO;
static FightOutPokemon* _SIDE_DEFENCE_NAMENO;
static u16 _Item;
static u16 _Item2;
static u32 _Digit;
static u32 _Digit2;
static u32 _MsgID;
static u32 _Pokemon;
static u32 _Pokemon2;
static u32 _MenuDigit;
static u32 _MenuDigit2;
static u32 _MenuPokemon;
static u32 _MenuMsg;
static u32 _MenuMsg2;
static u16 _Waza;
static u32 _Money;
static u32 _Time;
static u32 _String;
static u32 _String2;
static u16 _PokemonID;
static u32 _MenuMoney;
static u32 _MenuMsgID;
static u32 _MenuMsgID2;
static u16 _Tribe;
static u16 _Npc;
static u16 _SndID;
static u16* _msgctrlMakeDigit(u16*, s32, u32, s32);
static u16* _msgctrlSideName(FightOutPokemon*, u8);
static inline u16* _msgctrlMonsName(FightOutPokemon* pokemon) {
    FightTrainer* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    if (fightFloorIsNowEncountTuusinTaisen(0) == 1 && trainer != 0) {
        msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(trainer));
        msgctrlSetValue(0x57, (u32)fightOutPokemonGetNicknamePtr(pokemon));
        return GSmsgGetGSchar(0x4FE4);
    }
    return fightOutPokemonGetNicknamePtr(pokemon);
}

#pragma force_active on
extern "C" {
void msgctrlInitValue() {
    _MenuPokemon = 0;
    _MenuMsg = 0;
    _MenuMsg2 = 0;
    _Pokemon = 0;
    _Pokemon2 = 0;
    _String = 0;
    _String2 = 0;
}
}
extern "C" {
void msgctrlSetValue(s32 id, u32 value) {
    switch (id) {
    case 45: _Item = value; break;
    case 46: _Item2 = value; break;
    case 47: _Digit = value; break;
    case 48: _Digit2 = value; break;
    case 49: _MsgID = value; break;
    case 50: _Pokemon = value; break;
    case 51: _Pokemon2 = value; break;
    case 52: _MenuDigit = value; break;
    case 53: _MenuDigit2 = value; break;
    case 54: _MenuPokemon = value; break;
    case 55: _MenuMsg = value; break;
    case 81: _MenuMsg2 = value; break;
    case 57: _Waza = value; break;
    case 77: _String = value; break;
    case 87: _String2 = value; break;
    case 78: _PokemonID = value; break;
    case 75: _Money = value; break;
    case 76: _Time = value; break;
    case 80: _MenuMoney = value; break;
    case 85: _MenuMsgID = value; break;
    case 86: _MenuMsgID2 = value; break;
    case 88: _Tribe = value; break;
    case 89: _Npc = value; break;
    case 93: _SndID = value; break;
    case 95: _MenuDigit = value; break;
    case 96: _MenuDigit2 = value; break;
    case 99: _Money = value; break;
    case 100: _Time = value; break;
    case 105: _MenuMoney = value; break;
    case 13: _EV_STR_BUF0 = value; break;
    case 14: _EV_STR_BUF1 = value; break;
    case 65: _EV_STR_BUF2 = value; break;
    case 15: _ATTACK_MONS = (FightOutPokemon*)value; break;
    case 16: _DEFENCE_MONS = (FightOutPokemon*)value; break;
    case 17: _CLIENT_MONS = (FightOutPokemon*)value; break;
    case 18: _TSUIKA_MONS = (FightOutPokemon*)value; break;
    case 19: _MY_NAME = value; break;
    case 20: _MY_MONS = value; break;
    case 21: _MY_MONS2 = value; break;
    case 22: _ENEMY_MONS = value; break;
    case 23: _ENEMY_MONS2 = value; break;
    case 24: _ENEMY_TMONS = value; break;
    case 25: _ENEMY_TMONS2 = value; break;
    case 26: _SPEABI_NAMEA = value; break;
    case 27: _SPEABI_NAMED = value; break;
    case 28: _SPEABI_NAMEC = value; break;
    case 29: _SPEABI_NAMET = value; break;
    case 30: _CLIENTNOWORK = (FightOutPokemon*)value; break;
    case 31: _SIDE_ATTACK_NAMEHA = (FightOutPokemon*)value; break;
    case 32: _SIDE_ATTACK_NAMEWO = (FightOutPokemon*)value; break;
    case 33: _SIDE_ATTACK_NAMENO = (FightOutPokemon*)value; break;
    case 34: _TRAINER_TYPE = value; break;
    case 35: _TRAINER_NAME = value; break;
    case 36: _TRAINER_LOSE = value; break;
    case 37: _TRAINER_ENENAME = value; break;
    case 38: _TRAINER_ENENAME2 = value; break;
    case 39: _TRAINER_CLIENTNO = value; break;
    case 40: _WAZA_NAME = value; break;
    case 41: _ITEM_NAME = value; break;
    case 42: _PASO_NAME = value; break;
    case 66: _SIDE_DEFENCE_NAMEHA = (FightOutPokemon*)value; break;
    case 67: _SIDE_DEFENCE_NAMEWO = (FightOutPokemon*)value; break;
    case 68: _SIDE_DEFENCE_NAMENO = (FightOutPokemon*)value; break;
    }
}
}
extern "C++" {
static u16* _msgctrlMakeDigit(u16* buf, s32 len, u32 val, s32 mode)
{
    u32* pv = &val;
    u8 neg = 0;
    u32 base = 10;
    s32 count = 0;
    s32 minDigits = 1;
    u16* digits;
    len--;
    buf[len] = 0;
    switch (mode) {
    case 0:
    case 5:
    case 6:
        if ((s32)*pv < 0) {
            *pv = -(s32)*pv;
            neg = 1;
        }
        break;
    case 2:
    case 8:
        minDigits = 10;
        break;
    case 3:
    case 9:
        base = 16;
        minDigits = 8;
        break;
    case 1:
    case 4:
    case 7:
    case 10:
        break;
    }
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        if (pokecoloGetCountryCode() == 0) {
            digits = full_digit_code;
        } else {
            digits = half_digit_code;
        }
        break;
    case 5:
        digits = full_digit_code;
        break;
    default:
        digits = half_digit_code;
        break;
    }
    while (val != 0) {
        if ((mode == 4 || mode == 10) && count != 0 && count % 3 == 0) {
            switch (pokecoloGetLanguage()) {
            case 3:
            case 6:
                buf[--len] = 0x2E;
                break;
            case 4:
            case 5:
                break;
            case 2:
            default:
                buf[--len] = 0x2C;
                break;
            }
        }
        u32 v = val;
        len--;
        count++;
        val = v / base;
        buf[len] = digits[v - val * base];
    }
    for (; count < minDigits; count++) {
        buf[--len] = digits[0];
    }
    if (neg) {
        len--;
        buf[len] = 0x2D;
    }
    return buf + len;
}
}
extern "C" {
s32 msgctrlCR(MsgCtx* c) {
    c->f0c = c->f04;
    c->f10 = c->f10 + c->f68 * (f32)(c->f23 + c->lineSpace);
    return 0;
}
}
extern "C" {
s32 msgctrlKeyEnd(MsgCtx* c) {
    if (c->flags & 2) c->keyFlag = 1;
    if (menuIsCheck(0xA)) c->keyFlag = 0;
    if (c->keyFlag != 0) c->keyFlag = 0;
    else c->cursor -= 3;
    return 1;
}
}
extern "C" {
s32 msgctrlCheckEnd(MsgCtx* c) {
    if (c->flags & 2) c->keyFlag = 1;
    if (menuIsCheck(0xA)) c->keyFlag = 0;
    if (c->keyFlag != 0) {
        c->keyFlag = 0;
    } else {
        c->cursor -= 3;
        c->checkWaiting = 1;
    }
    return 1;
}
}
extern "C" {
s32 msgctrlCheckWait(MsgCtx* c) {
    if (c->flags & 2) c->keyFlag = 1;
    if (menuIsCheck(0xA)) c->keyFlag = 0;
    if (c->skip == 0) {
        if (c->keyFlag != 0) {
            c->keyFlag = 0;
            c->saved = c->cursor;
            if (*c->cursor != 0) peopleSetTalkKeyWaitCallback();
            if ((c->flags & 2) == 0) GSsndPlayNow(0x11);
        } else {
            c->cursor -= 3;
            c->checkWaiting = 1;
        }
    } else {
        c->f0c = c->f04;
        c->f10 = c->f08;
    }
    return 1;
}
}
extern "C" {
s32 msgctrlKeyWait(MsgCtx* c) {
    if (c->flags & 2) c->keyFlag = 1;
    if (menuIsCheck(0xA)) c->keyFlag = 0;
    if (c->skip == 0) {
        if (c->keyFlag != 0) {
            c->keyFlag = 0;
            c->saved = c->cursor;
            if (*c->cursor != 0) peopleSetTalkKeyWaitCallback();
            if ((c->flags & 2) == 0) GSsndPlayNow(0x11);
        } else {
            c->cursor -= 3;
            c->keyWaiting = 1;
        }
    } else {
        c->f0c = c->f04;
        c->f10 = c->f08;
    }
    return 1;
}
}
extern "C" {
s32 msgctrlRubyStart(MsgCtx* c) {
    if (c->skip != 0) GSmsgInitRuby(c);
    c->ruby = 1;
    return 0;
}
}
extern "C" {
s32 msgctrlRubyTop(MsgCtx* c) {
    c->ruby = 2;
    return 0;
}
}
extern "C" {
s32 msgctrlRubyEnd(MsgCtx* c) {
    c->ruby = 0;
    return 0;
}
}
extern "C" {
s32 msgctrlFont(MsgCtx* c) {
    if (c->skip == 0) {
        c->font = *c->cursor;
        GSmsgSetFontInfo(c);
    } else {
        c->font = *c->cursor;
        GSmsgSetFontInfo(c);
    }
    c->cursor += 1;
    return 0;
}
}
extern "C" {
s32 msgctrlColor(MsgCtx* c) {
    if (c->skip != 0) {
        u32 alpha = c->color & 0xFF;
        c->color = *(u32*)c->cursor;
        c->color &= 0xFFFFFF00;
        c->color |= alpha;
        GSmsgSetColor(c);
    }
    c->cursor += 4;
    return 0;
}
}
extern "C" {
s32 msgctrlPalette(MsgCtx* c) {
    if (c->skip != 0) {
        u32 index = *c->cursor;
        u32 color = c->color;
        if (index >= *msg_palette_number) index = 0;
        u8 r = msg_palette[(u8)index * 4 + 0];
        u8 g = msg_palette[(u8)index * 4 + 1];
        u8 b = msg_palette[(u8)index * 4 + 2];
        u8 a = msg_palette[(u8)index * 4 + 3];
        c->color = ((color >> 24) * r / 255 << 24) | (((color >> 16) & 0xFF) * g / 255 << 16) | (((color >> 8) & 0xFF) * b / 255 << 8) | ((color & 0xFF) * a / 255);
        GSmsgSetColor(c);
        c->color = color;
    }
    c->cursor += 1;
    return 0;
}
}
extern "C" {
s32 msgctrlWait(MsgCtx* c) {
    if (c->skip == 0) {
        if (c->wait == 0) c->wait = *c->cursor + 1;
        if (--c->wait <= 0) {
            c->wait = 0;
        } else {
            c->cursor -= 3;
            return 1;
        }
    }
    c->cursor += 1;
    return 0;
}
}
extern "C" {
u16* msgctrlHero() {
    return heroBiosGetNamePtr(savedataGetStatus(0, 2));
}
}
extern "C" {
u16* msgctrlHizuki() {
    return heroBiosGetHizukiNamePtr(savedataGetStatus(0, 2));
}
}
extern "C" {
u32 msgctrlItem() {
    u32 name = itemDataBiosGetName(itemDataBiosGetPtr(_Item));
    if (name == 0) name = 0x3AD2;
    return name;
}
}
extern "C" {
u32 msgctrlItem2() {
    u32 name = itemDataBiosGetName(itemDataBiosGetPtr(_Item2));
    if (name == 0) name = 0x3AD2;
    return name;
}
}
extern "C" {
u16* msgctrlDigit() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _Digit, 0);
}
}
extern "C" {
u16* msgctrlDigit2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _Digit2, 0);
}
}
extern "C" {
u32 msgctrlMsgID() {
    return _MsgID;
}
}
extern "C" {
u32 msgctrlPokemon() {
    return _Pokemon;
}
}
extern "C" {
u32 msgctrlPokemon2() {
    return _Pokemon2;
}
}
extern "C" {
u16* msgctrlMenuDigit() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 0);
}
}
extern "C" {
u16* msgctrlMenuDigit2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit2, 0);
}
}
extern "C" {
u32 msgctrlMenuPokemon() {
    return _MenuPokemon;
}
}
extern "C" {
u32 msgctrlMenuMsg() {
    return _MenuMsg;
}
}
extern "C" {
u32 msgctrlMenuMsg2() {
    return _MenuMsg2;
}
}
extern "C" {
u32 msgctrlWaza() {
    return wazaDataBiosGetName(wazaDataBiosGetPtr(_Waza));
}
}
extern "C" {
u16* msgctrlMenuDigitH() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 6);
}
}
extern "C" {
u16* msgctrlMenuDigitH2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit2, 6);
}
}
extern "C" {
u16* msgctrlMenuUDigitH() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 7);
}
}
extern "C" {
u16* msgctrlMenuUDigitH2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit2, 7);
}
}
extern "C" {
u16* msgctrlMenuHexH() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 9);
}
}
extern "C" {
u16* msgctrlMenuHexH2() {
    // Retail reads the first menu value in this hexadecimal handler.
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 9);
}
}
extern "C" {
u16* msgctrlMenuZDigitH() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 8);
}
}
extern "C" {
u16* msgctrlMenuZDigitH2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit2, 8);
}
}
extern "C" {
u16* msgctrlMoneyH() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _Money, 10);
}
}
extern "C" {
u16* msgctrlTimeH() {
    static u16 buff[16];
    static u16 buff2[16];
    static u16* top;
    u32 minute;
    u32 hour = _Time / 3600;
    s32 n = 0;
    minute = (_Time % 3600) / 60;
    if (hour >= 100) {
        top = _msgctrlMakeDigit(buff2, 16, hour / 100, 6);
        buff[n++] = *top;
    }
    if (hour >= 10) {
        hour = hour % 100;
        top = _msgctrlMakeDigit(buff2, 16, hour / 10, 6);
        buff[n++] = *top;
    }
    top = _msgctrlMakeDigit(buff2, 16, hour % 10, 6);
    buff[n++] = *top;
    buff[n++] = 0x3A;
    top = _msgctrlMakeDigit(buff2, 16, minute / 10, 6);
    buff[n++] = *top;
    top = _msgctrlMakeDigit(buff2, 16, minute % 10, 6);
    buff[n++] = *top;
    buff[n] = 0;
    return buff;
}
}
extern "C" {
u16* msgctrlMenuMoneyH() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuMoney, 10);
}
}
extern "C" {
u16* msgctrlDigitH() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _Digit, 6);
}
}
extern "C" {
u16* msgctrlDigitH2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _Digit2, 6);
}
}
extern "C" {
u32 msgctrlEvStrBuf0() {
    return _EV_STR_BUF0;
}
}
extern "C" {
u32 msgctrlEvStrBuf1() {
    return _EV_STR_BUF1;
}
}
extern "C" {
u32 msgctrlEvStrBuf2() {
    return _EV_STR_BUF2;
}
}
extern "C" {
u16* msgctrlAttackMons() {
    return _msgctrlMonsName(_ATTACK_MONS);
}
}
extern "C" {
u16* msgctrlDeffenceMons() {
    return _msgctrlMonsName(_DEFENCE_MONS);
}
}
extern "C" {
u16* msgctrlClientMos() {
    return _msgctrlMonsName(_CLIENT_MONS);
}
}
extern "C" {
u16* msgctrlTsuikaMons() {
    return _msgctrlMonsName(_TSUIKA_MONS);
}
}
extern "C" {
u32 msgctrlMyName() {
    return _MY_NAME;
}
}
extern "C" {
u32 msgctrlMyMons() {
    return _MY_MONS;
}
}
extern "C" {
u32 msgctrlMyMons2() {
    return _MY_MONS2;
}
}
extern "C" {
u32 msgctrlEnemyMons() {
    return _ENEMY_MONS;
}
}
extern "C" {
u32 msgctrlEnemyMons2() {
    return _ENEMY_MONS2;
}
}
extern "C" {
u32 msgctrlEnemyTmons() {
    return _ENEMY_TMONS;
}
}
extern "C" {
u32 msgctrlEnemyTmons2() {
    return _ENEMY_TMONS2;
}
}
extern "C" {
u32 msgctrlSpeabiNamea() {
    return _SPEABI_NAMEA;
}
}
extern "C" {
u32 msgctrlSpeabiNamed() {
    return _SPEABI_NAMED;
}
}
extern "C" {
u32 msgctrlSpeabiNamec() {
    return _SPEABI_NAMEC;
}
}
extern "C" {
u32 msgctrlSpeabiNamet() {
    return _SPEABI_NAMET;
}
}
extern "C" {
u16* msgctrlClientnowork() {
    return _msgctrlMonsName(_CLIENTNOWORK);
}
}
extern "C++" {
static u16* _msgctrlSideName(FightOutPokemon* pokemon, u8 kind) {
    u16 status = fightFloorGetStatus(0, 0, 0x14, 0);
    void* target = fightTargetGetPtrAsNowFightType(2, pokemon);
    FightTrainer* owner = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    FightTrainer* trainer;
    u16 count = 0;
    u16 i;
    for (i = 0; i < 2; ++i) {
        trainer = fightSideGetValidFightTrainerPtr(target, i);
        if (trainer != 0 && fightTrainerCheckDoFight(trainer)) {
            if (count == 0) msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(trainer));
            else if (count == 1) msgctrlSetValue(0x57, (u32)fightTrainerGetNamePtr(trainer));
            ++count;
        }
    }
    if (fightFloorIsNowEncountTuusinTaisen(0) == 1 && owner != 0) {
        if (count <= 1) {
            msgctrlSetValue(0x4D, (u32)fightTrainerGetNamePtr(owner));
            if (kind == 0) return GSmsgGetGSchar(0x4FE5);
            if (kind == 1) return GSmsgGetGSchar(0x4FE8);
            return GSmsgGetGSchar(0x4FEA);
        }
        if (kind == 0) return GSmsgGetGSchar(0x4FE6);
        if (kind == 1) return GSmsgGetGSchar(0x4FE9);
        return GSmsgGetGSchar(0x4FEB);
    }
    if (fightTargetIsHostSide(pokemon, status) == 1) {
        if (kind == 0) return GSmsgGetGSchar(0x4F6A);
        if (kind == 1) return GSmsgGetGSchar(0x4F6C);
        return GSmsgGetGSchar(0x4F68);
    }
    if (kind == 0) return GSmsgGetGSchar(0x4F69);
    if (kind == 1) return GSmsgGetGSchar(0x4F6B);
    return GSmsgGetGSchar(0x4F67);
}
}
extern "C" {
u16* msgctrlSideAttackNameha() {
    return _msgctrlSideName(_SIDE_ATTACK_NAMEHA, 0);
}
}
extern "C" {
u16* msgctrlSideAttackNamewo() {
    return _msgctrlSideName(_SIDE_ATTACK_NAMEWO, 1);
}
}
extern "C" {
u16* msgctrlSideAttackNameno() {
    return _msgctrlSideName(_SIDE_ATTACK_NAMENO, 2);
}
}
extern "C" {
u16* msgctrlSideDefenceNameha() {
    return _msgctrlSideName(_SIDE_DEFENCE_NAMEHA, 0);
}
}
extern "C" {
u16* msgctrlSideDefenceNamewo() {
    return _msgctrlSideName(_SIDE_DEFENCE_NAMEWO, 1);
}
}
extern "C" {
u16* msgctrlSideDefenceNameno() {
    return _msgctrlSideName(_SIDE_DEFENCE_NAMENO, 2);
}
}
extern "C" {
u32 msgctrlTrainerType() {
    return _TRAINER_TYPE;
}
}
extern "C" {
u32 msgctrlTrainerName() {
    return _TRAINER_NAME;
}
}
extern "C" {
u32 msgctrlTrainerLose() {
    return _TRAINER_LOSE;
}
}
extern "C" {
u32 msgctrlTrainerEnename() {
    return _TRAINER_ENENAME;
}
}
extern "C" {
u32 msgctrlTrainerEnename2() {
    return _TRAINER_ENENAME2;
}
}
extern "C" {
u32 msgctrlTrainerClientno() {
    return _TRAINER_CLIENTNO;
}
}
extern "C" {
u32 msgctrlWazaName() {
    return _WAZA_NAME;
}
}
extern "C" {
u32 msgctrlItemName() {
    return _ITEM_NAME;
}
}
extern "C" {
u32 msgctrlPasoName() {
    return _PASO_NAME;
}
}
extern "C" {
s32 msgctrlSetPeopleTalkFlag() {
    peopleSetTalkFlagCallback();
    return 0;
}
}
extern "C" {
s32 msgctrlSeOff() {
    return 0;
}
}
extern "C" {
s32 msgctrlSeOn() {
    return 0;
}
}
extern "C" {
u16* msgctrlMenuUDigit() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 1);
}
}
extern "C" {
u16* msgctrlMenuUDigit2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit2, 1);
}
}
extern "C" {
u16* msgctrlMenuHex() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 3);
}
}
extern "C" {
u16* msgctrlMenuHex2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 3);
}
}
extern "C" {
u16* msgctrlMenuZDigit() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 2);
}
}
extern "C" {
u16* msgctrlMenuZDigit2() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit2, 2);
}
}
extern "C" {
u16* msgctrlMoney() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _Money, 4);
}
}
extern "C" {
u16* msgctrlTime() {
    static u16 buff[16];
    static u16 buff2[16];
    static u16* top;
    u32 minute;
    u32 hour = _Time / 3600;
    s32 n = 0;
    minute = (_Time % 3600) / 60;
    if (hour >= 100) {
        top = _msgctrlMakeDigit(buff2, 16, hour / 100, 0);
        buff[n++] = *top;
    }
    if (hour >= 10) {
        hour = hour % 100;
        top = _msgctrlMakeDigit(buff2, 16, hour / 10, 0);
        buff[n++] = *top;
    }
    top = _msgctrlMakeDigit(buff2, 16, hour % 10, 0);
    buff[n++] = *top;
    buff[n++] = 0x3A;
    top = _msgctrlMakeDigit(buff2, 16, minute / 10, 0);
    buff[n++] = *top;
    top = _msgctrlMakeDigit(buff2, 16, minute % 10, 0);
    buff[n++] = *top;
    buff[n] = 0;
    return buff;
}
}
extern "C" {
u32 msgctrlString() {
    return _String;
}
}
extern "C" {
u32 msgctrlPokemonID() {
    return pokemonDataBiosGetName(pokemonDataBiosGetPtr(_PokemonID));
}
}
extern "C" {
u16* msgctrlMenuFullDigit() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuDigit, 5);
}
}
extern "C" {
u16* msgctrlMenuMoney() {
    static u16 buff[16];
    return _msgctrlMakeDigit(buff, 16, _MenuMoney, 4);
}
}
extern "C" {
s32 msgctrlShadow(MsgCtx* c) {
    if (c->skip != 0) c->shadow = *c->cursor;
    c->cursor += 1;
    return 0;
}
}
extern "C" {
s32 msgctrlAlign(MsgCtx* c) {
    if (c->skip != 0) {
        c->align = *c->cursor;
        GSmsgAdjustAlign(c);
    }
    c->cursor += 1;
    return 0;
}
}
extern "C" {
s32 msgctrlTalkSE(MsgCtx* c) {
    if (c->skip == 0) c->talkSE = *c->cursor;
    c->cursor += 1;
    return 0;
}
}
extern "C" {
u32 msgctrlMenuMsgID() {
    return _MenuMsgID;
}
}
extern "C" {
u32 msgctrlMenuMsgID2() {
    return _MenuMsgID2;
}
}
extern "C" {
u32 msgctrlString2() {
    return _String2;
}
}
extern "C" {
u32 msgctrlTribe() {
    return fightTrainerKindDataBiosGetPrefixName(fightTrainerKindDataBiosGetPtr(_Tribe));
}
}
extern "C" {
u32 msgctrlNpc() {
    return _Npc;
}
}
extern "C" {
s32 msgctrlIndentOff(MsgCtx* c) {
    c->indentOff = 1;
    return 0;
}
}
extern "C" {
s32 msgctrlLineSpace(MsgCtx* c) {
    if (c->skip != 0) c->lineSpace = (s8)*c->cursor;
    c->cursor += 1;
    return 0;
}
}
extern "C" {
s32 msgctrlBaseLineBias(MsgCtx* c) {
    if (c->skip != 0) c->baseLineBias = (s8)*c->cursor;
    c->cursor += 1;
    return 0;
}
}
extern "C" {
s32 msgctrlSndPlay(MsgCtx* c) {
    if (c->skip == 0 && _SndID != 0) soundOpenPlay(_SndID, 0, 0xFF);
    return 0;
}
}
extern "C" {
s32 msgctrlSndWait(MsgCtx* c) {
    if (c->skip == 0) {
        if (_SndID == 0) return 0;
        if (GSsndGetStatus(_SndID) == 2) c->cursor -= 3;
    }
    return 1;
}
}
