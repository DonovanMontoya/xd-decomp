#include <dolphin/types.h>
#include <libc/stddef.h>

#pragma force_active on
#pragma pack(1)

/* Packed battle commands consumed by WazaSequenceTbl in fightSeqWSWaza.cpp.
 * Operand widths follow the WS_* handlers. 0xFF addresses select UserWork. */
#define SEQ_USER_WORK(offset) ((void*)(0xFF000000UL | (offset)))

enum {
    WS_BADGECHECK = 0x00,
    WS_HITCHECK = 0x01,
    WS_ATTACK_MESSAGE = 0x02,
    WS_PP_DEC = 0x04,
    WS_CRITICAL_CHECK = 0x05,
    WS_DAMAGE_CALC = 0x06,
    WS_TYPE_CHECK = 0x07,
    WS_DAMAGE_LOSS = 0x08,
    WS_DAMAGE_LOSS_ONLY = 0x09,
    WS_WAZA_EFFECT = 0x0A,
    WS_EFFECT_WAIT = 0x0B,
    WS_HP_DEC = 0x0C,
    WS_HP_DEC_WAIT = 0x0D,
    WS_CRITICAL_MESSAGE = 0x0E,
    WS_WAZAKOUKA_SE = 0x0F,
    WS_WAZAKOUKA_MESSAGE = 0x10,
    WS_MESSAGE = 0x11,
    WS_ALERT_MESSAGE = 0x12,
    WS_MESSAGE_WAIT = 0x13,
    WS_MESSAGE_TBL = 0x14,
    WS_ALERT_MESSAGE_TBL = 0x15,
    WS_TSUIKA_CHECK = 0x16,
    WS_TSUIKA_DIRECT_ACT = 0x17,
    WS_TSUIKA_INDIRECT_ACT = 0x18,
    WS_SAKUJO = 0x19,
    WS_KIZETSU_CHECK = 0x1A,
    WS_KIZETSU = 0x1B,
    WS_KIZETSU_WAIT = 0x1C,
    WS_CONDITION_CHECK = 0x1D,
    WS_CONDITION2_CHECK = 0x1E,
    WS_SPEABI_CHECK = 0x1F,
    WS_SIDECONDITION_CHECK = 0x20,
    WS_CONDCHG_CHECK = 0x21,
    WS_WAZAKOUKA_CHECK = 0x22,
    WS_CHECK_TYPE = 0x23,
    WS_GET_EXP = 0x24,
    WS_ZENMETSU_CHECK = 0x25,
    WS_LOOP_INIT = 0x26,
    WS_LOOPCNT = 0x27,
    WS_LOOP = 0x28,
    WS_JUMP = 0x29,
    WS_IF8 = 0x2A,
    WS_IF16 = 0x2B,
    WS_IF32 = 0x2C,
    WS_IFWEQ = 0x2D,
    WS_IFWNE = 0x2E,
    WS_SETVALUE = 0x2F,
    WS_ADDVALUE = 0x30,
    WS_SETWORK = 0x32,
    WS_SET32BIT = 0x36,
    WS_RESET32BIT = 0x39,
    WS_WAIT = 0x3A,
    WS_CLIENT_BIT_WAIT = 0x3B,
    WS_SEQRET = 0x3D,
    WS_WAZAEND = 0x3E,
    WS_SEQEND = 0x3F,
    WS_SPEABIEND = 0x40,
    WS_GOSUB = 0x42,
    WS_MONS_TYPE = 0x43,
    WS_ALERTEND = 0x45,
    WS_FIGHT_EFFECT = 0x46,
    WS_FIGHT_EFFECT2 = 0x47,
    WS_COND_CHG_WORK_SET = 0x48,
    WS_COND_CHG_BIT_CHECK = 0x49,
    WS_WKC_ACT = 0x4A,
    WS_TYPE_CHECK_NO_HIT = 0x4B,
    WS_MODOSU_EFFECT = 0x4C,
    WS_APPEAR_EFFECT_INIT = 0x4D,
    WS_APPEAR_EFFECT = 0x4E,
    WS_APPEAR_EFFECT_WAIT = 0x4F,
    WS_RESHUFFLE_CHECK = 0x50,
    WS_POKE_RESHUFFLE = 0x51,
    WS_POKE_RESHUFFLE_WAIT = 0x52,
    WS_POKE_RESHUFFLE_END = 0x53,
    WS_TRAINER_APPEAR = 0x54,
    WS_ME_PLAY = 0x56,
    WS_VOICE = 0x57,
    WS_END_FIGHT = 0x58,
    WS_POKEDELACTOR = 0x59,
    WS_WAZAOBOE_CHECK = 0x5A,
    WS_WAZAWASURE_CHECK = 0x5B,
    WS_WAZAAKIRAME_CHECK = 0x5C,
    WS_POKE_BLINK = 0x5D,
    WS_OKODUKAI_CALC = 0x5E,
    WS_SWITCH_A_D = 0x60,
    WS_BALL_GAUGE_SET = 0x62,
    WS_BALL_GAUGE_OFF = 0x63,
    WS_WAZASEQADRS = 0x64,
    WS_STATUS_EFFECT = 0x65,
    WS_STATUS_EFFECT2 = 0x66,
    WS_STATUS_EFFECT_DIRECT = 0x67,
    WS_SCA_END_SET = 0x69,
    WS_KORAERU_CHECK = 0x6A,
    WS_KILLITEM = 0x6B,
    WS_STATUS_WINDOW = 0x6D,
    WS_VANISH_OFF = 0x70,
    WS_OBOEWAZANO_SET = 0x72,
    WS_POKE_HPMAX_RATE = 0x74,
    WS_POKE_HPDEC_RATE = 0x75,
    WS_SUBROUTINE_CALL = 0x77,
    WS_TOKUSEI_SET = 0x78,
    WS_GUARD_SUCCESS_CHECK = 0x79,
    WS_JIBAKU_INIT = 0x7A,
    WS_JIBAKU = 0x7B,
    WS_JIBAKU_LOOP = 0x7C,
    WS_KAIFUKU = 0x7D,
    WS_OUMU_CHECK = 0x7E,
    WS_REFLEC = 0x7F,
    WS_YADORIGI = 0x80,
    WS_DAMAGE_CHG = 0x81,
    WS_NEMURU = 0x82,
    WS_NEKODAMASHI = 0x83,
    WS_SAWAGU = 0x84,
    WS_SAWAGU_CHECK = 0x85,
    WS_TAKUWAERU = 0x86,
    WS_HAKIDASU = 0x87,
    WS_NOMIKOMU = 0x88,
    WS_SUITORI = 0x89,
    WS_CONDCHG = 0x8A,
    WS_KUROIKIRI = 0x8B,
    WS_GAMAN = 0x8C,
    WS_ABARERU = 0x8D,
    WS_RENZOKU = 0x8E,
    WS_RENZOKU_NUM_INIT = 0x8F,
    WS_HUKITOBASHI = 0x90,
    WS_TEXTURE = 0x91,
    WS_KOBAN_CHECK = 0x92,
    WS_HIKARINOKABE = 0x93,
    WS_ICHIGEKI = 0x94,
    WS_HPHALF = 0x95,
    WS_WEATHER_CHANGE = 0x96,
    WS_WEATHER_KEEP = 0x97,
    WS_MEROMERO = 0x98,
    WS_CONDITION_GAUGE = 0x99,
    WS_SHIROIKIRI = 0x9A,
    WS_KIAIDAME = 0x9B,
    WS_HENSHIN = 0x9C,
    WS_MIGAWARI = 0x9D,
    WS_MONOMANE = 0x9E,
    WS_YUBIWOHURU = 0x9F,
    WS_CHIKYUUNAGE = 0xA0,
    WS_PSYCHOWAVE = 0xA1,
    WS_COUNTER = 0xA2,
    WS_MIRRORCOAT = 0xA3,
    WS_KANASHIBARI = 0xA4,
    WS_ENCORE = 0xA5,
    WS_ITAMIWAKE = 0xA6,
    WS_TEXTURE2 = 0xA7,
    WS_LOCKON = 0xA8,
    WS_SKETCH = 0xA9,
    WS_NEGOTO = 0xAA,
    WS_MICHIDURE = 0xAB,
    WS_MICHIDURE_CHECK = 0xAC,
    WS_JITABATA = 0xAD,
    WS_URAMI = 0xAE,
    WS_IYASHINOSUZU = 0xAF,
    WS_NOROI = 0xB0,
    WS_MAKIBISHI = 0xB1,
    WS_MIYABURU = 0xB2,
    WS_HOROBINOUTA = 0xB3,
    WS_KOROGARU = 0xB4,
    WS_IBARU = 0xB5,
    WS_RENZOKUGIRI = 0xB6,
    WS_NATSUKI = 0xB7,
    WS_PRESENT = 0xB8,
    WS_SHINPINOMAMORI = 0xB9,
    WS_MAGNITUDE = 0xBA,
    WS_OIUCHI_CHECK = 0xBB,
    WS_HARADAIKO = 0xBC,
    WS_JIKOANJI = 0xBD,
    WS_KOUSOKUSPIN = 0xBE,
    WS_MARUKUNARU = 0xBF,
    WS_WEATHERKAIFUKU = 0xC0,
    WS_MEZAMERUPOWER = 0xC1,
    WS_JISIN = 0xC2,
    WS_MIRAIYOCHI = 0xC3,
    WS_HUKURODATAKI = 0xC4,
    WS_KIERUTAME = 0xC5,
    WS_KIERUTAME_AFTAR = 0xC6,
    WS_CHIISAKUNARU = 0xC7,
    WS_OKIMIYAGE = 0xC8,
    WS_KONOYUBITOMARE = 0xC9,
    WS_JUUDEN = 0xCA,
    WS_SHIZENNOCHIKARA = 0xCB,
    WS_REFLESH = 0xCC,
    WS_ICHAMON = 0xCD,
    WS_KIAIPUNCH = 0xCE,
    WS_CHOUHATSU = 0xCF,
    WS_TEDASUKE = 0xD0,
    WS_TRICK = 0xD1,
    WS_NARIKIRI = 0xD2,
    WS_NEGAIGOTO = 0xD3,
    WS_NEWOHARU = 0xD4,
    WS_REVENGE = 0xD5,
    WS_AKUBI = 0xD6,
    WS_GAMUSYARA = 0xD7,
    WS_HUNKA = 0xD8,
    WS_SKILLSWAP = 0xD9,
    WS_HUUIN = 0xDA,
    WS_ONNEN = 0xDB,
    WS_KETAGURI = 0xDC,
    WS_NEKONOTE = 0xDD,
    WS_MAGICCORT = 0xDE,
    WS_YOKODORI = 0xDF,
    WS_IKAKU = 0xE0,
    WS_SIZENKAIHUKU = 0xE1,
    WS_HP_CHECK = 0xE2,
    WS_HIMITUNOTIKARA = 0xE3,
    WS_MONOHIROI = 0xE4,
    WS_TENKIYA = 0xE5,
    WS_TENKIYA_CHECK = 0xE6,
    WS_ASOBI = 0xE7,
    WS_WEATHER_BALL = 0xE8,
    WS_RECYCLE = 0xE9,
    WS_HOGOSYOKU = 0xEA,
    WS_YOKODORI_CLIENT_SET = 0xEC,
    WS_KAWARAWARI = 0xED,
    WS_DARKREMOVE = 0xEE,
    WS_TELEPORT = 0xEF,
    WS_STATUS_GET8 = 0xF9,
    WS_STATUS_GET16 = 0xFA,
    WS_STATUS_GET32 = 0xFB,
    WS_STATUS_SET8 = 0xFC,
    WS_STATUS_SET16 = 0xFD,
    WS_STATUS_SET32 = 0xFE,
};

typedef struct Seq_BADGECHECK { u8 opcode; } Seq_BADGECHECK;
typedef struct Seq_HITCHECK { u8 opcode; void* operand01; u16 operand05; } Seq_HITCHECK;
typedef struct Seq_ATTACK_MESSAGE { u8 opcode; } Seq_ATTACK_MESSAGE;
typedef struct Seq_PP_DEC { u8 opcode; } Seq_PP_DEC;
typedef struct Seq_CRITICAL_CHECK { u8 opcode; } Seq_CRITICAL_CHECK;
typedef struct Seq_DAMAGE_CALC { u8 opcode; } Seq_DAMAGE_CALC;
typedef struct Seq_TYPE_CHECK { u8 opcode; } Seq_TYPE_CHECK;
typedef struct Seq_DAMAGE_LOSS { u8 opcode; } Seq_DAMAGE_LOSS;
typedef struct Seq_DAMAGE_LOSS_ONLY { u8 opcode; } Seq_DAMAGE_LOSS_ONLY;
typedef struct Seq_WAZA_EFFECT { u8 opcode; } Seq_WAZA_EFFECT;
typedef struct Seq_EFFECT_WAIT { u8 opcode; u8 operand01; } Seq_EFFECT_WAIT;
typedef struct Seq_HP_DEC { u8 opcode; u8 operand01; } Seq_HP_DEC;
typedef struct Seq_HP_DEC_WAIT { u8 opcode; u8 operand01; } Seq_HP_DEC_WAIT;
typedef struct Seq_CRITICAL_MESSAGE { u8 opcode; } Seq_CRITICAL_MESSAGE;
typedef struct Seq_WAZAKOUKA_SE { u8 opcode; } Seq_WAZAKOUKA_SE;
typedef struct Seq_WAZAKOUKA_MESSAGE { u8 opcode; } Seq_WAZAKOUKA_MESSAGE;
typedef struct Seq_MESSAGE { u8 opcode; u32 operand01; } Seq_MESSAGE;
typedef struct Seq_ALERT_MESSAGE { u8 opcode; u16 operand01; } Seq_ALERT_MESSAGE;
typedef struct Seq_MESSAGE_WAIT { u8 opcode; u16 operand01; } Seq_MESSAGE_WAIT;
typedef struct Seq_MESSAGE_TBL { u8 opcode; void* operand01; } Seq_MESSAGE_TBL;
typedef struct Seq_ALERT_MESSAGE_TBL { u8 opcode; void* operand01; } Seq_ALERT_MESSAGE_TBL;
typedef struct Seq_TSUIKA_CHECK { u8 opcode; } Seq_TSUIKA_CHECK;
typedef struct Seq_TSUIKA_DIRECT_ACT { u8 opcode; } Seq_TSUIKA_DIRECT_ACT;
typedef struct Seq_TSUIKA_INDIRECT_ACT { u8 opcode; } Seq_TSUIKA_INDIRECT_ACT;
typedef struct Seq_SAKUJO { u8 opcode; u8 operand01; } Seq_SAKUJO;
typedef struct Seq_KIZETSU_CHECK { u8 opcode; u8 operand01; u8 operand02; void* operand03; } Seq_KIZETSU_CHECK;
typedef struct Seq_KIZETSU { u8 opcode; u8 operand01; } Seq_KIZETSU;
typedef struct Seq_KIZETSU_WAIT { u8 opcode; u8 operand01; } Seq_KIZETSU_WAIT;
typedef struct Seq_CONDITION_CHECK { u8 opcode; u8 operand01; u32 operand02; void* operand06; } Seq_CONDITION_CHECK;
typedef struct Seq_CONDITION2_CHECK { u8 opcode; u8 operand01; u32 operand02; void* operand06; } Seq_CONDITION2_CHECK;
typedef struct Seq_SPEABI_CHECK { u8 opcode; u8 operand01; u8 operand02; void* operand03; } Seq_SPEABI_CHECK;
typedef struct Seq_SIDECONDITION_CHECK { u8 opcode; u8 operand01; u16 operand02; void* operand04; } Seq_SIDECONDITION_CHECK;
typedef struct Seq_CONDCHG_CHECK { u8 opcode; u8 operand01; u8 operand02; u8 operand03; u8 operand04; void* operand05; } Seq_CONDCHG_CHECK;
typedef struct Seq_WAZAKOUKA_CHECK { u8 opcode; u8 operand01; u32 operand02; u8 operand06; void* operand07; } Seq_WAZAKOUKA_CHECK;
typedef struct Seq_CHECK_TYPE { u8 opcode; u8 operand01; u8 operand02; void* operand03; } Seq_CHECK_TYPE;
typedef struct Seq_GET_EXP { u8 opcode; u8 operand01; } Seq_GET_EXP;
typedef struct Seq_ZENMETSU_CHECK { u8 opcode; u32 operand01; } Seq_ZENMETSU_CHECK;
typedef struct Seq_LOOP_INIT { u8 opcode; } Seq_LOOP_INIT;
typedef struct Seq_LOOPCNT { u8 opcode; u8 operand01; } Seq_LOOPCNT;
typedef struct Seq_LOOP { u8 opcode; void* operand01; } Seq_LOOP;
typedef struct Seq_JUMP { u8 opcode; void* operand01; } Seq_JUMP;
typedef struct Seq_IF8 { u8 opcode; u8 operand01; void* operand02; u8 operand06; void* operand07; } Seq_IF8;
typedef struct Seq_IF16 { u8 opcode; u8 operand01; void* operand02; u16 operand06; void* operand08; } Seq_IF16;
typedef struct Seq_IF32 { u8 opcode; u8 operand01; void* operand02; u32 operand06; void* operand0A; } Seq_IF32;
typedef struct Seq_IFWEQ { u8 opcode; void* operand01; void* operand05; u8 operand09; void* operand0A; } Seq_IFWEQ;
typedef struct Seq_IFWNE { u8 opcode; void* operand01; void* operand05; u8 operand09; void* operand0A; } Seq_IFWNE;
typedef struct Seq_SETVALUE { u8 opcode; void* operand01; u8 operand05; } Seq_SETVALUE;
typedef struct Seq_ADDVALUE { u8 opcode; void* operand01; u8 operand05; } Seq_ADDVALUE;
typedef struct Seq_SETWORK { u8 opcode; void* operand01; void* operand05; u8 operand09; } Seq_SETWORK;
typedef struct Seq_SET32BIT { u8 opcode; void* operand01; u32 operand05; } Seq_SET32BIT;
typedef struct Seq_RESET32BIT { u8 opcode; void* operand01; u32 operand05; } Seq_RESET32BIT;
typedef struct Seq_WAIT { u8 opcode; u16 operand01; } Seq_WAIT;
typedef struct Seq_CLIENT_BIT_WAIT { u8 opcode; } Seq_CLIENT_BIT_WAIT;
typedef struct Seq_SEQRET { u8 opcode; } Seq_SEQRET;
typedef struct Seq_WAZAEND { u8 opcode; } Seq_WAZAEND;
typedef struct Seq_SEQEND { u8 opcode; } Seq_SEQEND;
typedef struct Seq_SPEABIEND { u8 opcode; } Seq_SPEABIEND;
typedef struct Seq_GOSUB { u8 opcode; void* operand01; } Seq_GOSUB;
typedef struct Seq_MONS_TYPE { u8 opcode; u8 operand01; u8 operand02; void* operand03; } Seq_MONS_TYPE;
typedef struct Seq_ALERTEND { u8 opcode; } Seq_ALERTEND;
typedef struct Seq_FIGHT_EFFECT { u8 opcode; u8 operand01; u8 operand02; u32 operand03; } Seq_FIGHT_EFFECT;
typedef struct Seq_FIGHT_EFFECT2 { u8 opcode; u8 operand01; u32 operand02; void* operand06; } Seq_FIGHT_EFFECT2;
typedef struct Seq_COND_CHG_WORK_SET { u8 opcode; } Seq_COND_CHG_WORK_SET;
typedef struct Seq_COND_CHG_BIT_CHECK { u8 opcode; u8 operand01; u8 operand02; u8 operand03; } Seq_COND_CHG_BIT_CHECK;
typedef struct Seq_WKC_ACT { u8 opcode; u8 operand01; u8 operand02; } Seq_WKC_ACT;
typedef struct Seq_TYPE_CHECK_NO_HIT { u8 opcode; } Seq_TYPE_CHECK_NO_HIT;
typedef struct Seq_MODOSU_EFFECT { u8 opcode; } Seq_MODOSU_EFFECT;
typedef struct Seq_APPEAR_EFFECT_INIT { u8 opcode; u8 operand01; } Seq_APPEAR_EFFECT_INIT;
typedef struct Seq_APPEAR_EFFECT { u8 opcode; u8 operand01; u8 operand02; } Seq_APPEAR_EFFECT;
typedef struct Seq_APPEAR_EFFECT_WAIT { u8 opcode; u8 operand01; u8 operand02; } Seq_APPEAR_EFFECT_WAIT;
typedef struct Seq_RESHUFFLE_CHECK { u8 opcode; u8 operand01; void* operand02; u8 operand06; } Seq_RESHUFFLE_CHECK;
typedef struct Seq_POKE_RESHUFFLE { u8 opcode; u8 operand01; void* operand02; } Seq_POKE_RESHUFFLE;
typedef struct Seq_POKE_RESHUFFLE_WAIT { u8 opcode; u8 operand01; u8 operand02; } Seq_POKE_RESHUFFLE_WAIT;
typedef struct Seq_POKE_RESHUFFLE_END { u8 opcode; u8 operand01; } Seq_POKE_RESHUFFLE_END;
typedef struct Seq_TRAINER_APPEAR { u8 opcode; u8 operand01; } Seq_TRAINER_APPEAR;
typedef struct Seq_ME_PLAY { u8 opcode; u16 operand01; } Seq_ME_PLAY;
typedef struct Seq_VOICE { u8 opcode; u8 operand01; } Seq_VOICE;
typedef struct Seq_END_FIGHT { u8 opcode; } Seq_END_FIGHT;
typedef struct Seq_POKEDELACTOR { u8 opcode; u8 operand01; } Seq_POKEDELACTOR;
typedef struct Seq_WAZAOBOE_CHECK { u8 opcode; void* operand01; void* operand05; u8 operand09; } Seq_WAZAOBOE_CHECK;
typedef struct Seq_WAZAWASURE_CHECK { u8 opcode; void* operand01; } Seq_WAZAWASURE_CHECK;
typedef struct Seq_WAZAAKIRAME_CHECK { u8 opcode; void* operand01; } Seq_WAZAAKIRAME_CHECK;
typedef struct Seq_POKE_BLINK { u8 opcode; u8 operand01; } Seq_POKE_BLINK;
typedef struct Seq_OKODUKAI_CALC { u8 opcode; void* operand01; } Seq_OKODUKAI_CALC;
typedef struct Seq_SWITCH_A_D { u8 opcode; } Seq_SWITCH_A_D;
typedef struct Seq_BALL_GAUGE_SET { u8 opcode; u8 operand01; } Seq_BALL_GAUGE_SET;
typedef struct Seq_BALL_GAUGE_OFF { u8 opcode; u8 operand01; } Seq_BALL_GAUGE_OFF;
typedef struct Seq_WAZASEQADRS { u8 opcode; u8 operand01; } Seq_WAZASEQADRS;
typedef struct Seq_STATUS_EFFECT { u8 opcode; u8 operand01; } Seq_STATUS_EFFECT;
typedef struct Seq_STATUS_EFFECT2 { u8 opcode; u8 operand01; u32 operand02; } Seq_STATUS_EFFECT2;
typedef struct Seq_STATUS_EFFECT_DIRECT { u8 opcode; u8 operand01; u8 operand02; u32 operand03; } Seq_STATUS_EFFECT_DIRECT;
typedef struct Seq_SCA_END_SET { u8 opcode; } Seq_SCA_END_SET;
typedef struct Seq_KORAERU_CHECK { u8 opcode; } Seq_KORAERU_CHECK;
typedef struct Seq_KILLITEM { u8 opcode; u8 operand01; } Seq_KILLITEM;
typedef struct Seq_STATUS_WINDOW { u8 opcode; } Seq_STATUS_WINDOW;
typedef struct Seq_VANISH_OFF { u8 opcode; u8 operand01; } Seq_VANISH_OFF;
typedef struct Seq_OBOEWAZANO_SET { u8 opcode; } Seq_OBOEWAZANO_SET;
typedef struct Seq_POKE_HPMAX_RATE { u8 opcode; u8 operand01; } Seq_POKE_HPMAX_RATE;
typedef struct Seq_POKE_HPDEC_RATE { u8 opcode; u8 operand01; } Seq_POKE_HPDEC_RATE;
typedef struct Seq_SUBROUTINE_CALL { u8 opcode; u8 operand01; u8 operand02; } Seq_SUBROUTINE_CALL;
typedef struct Seq_TOKUSEI_SET { u8 opcode; u8 operand01; } Seq_TOKUSEI_SET;
typedef struct Seq_GUARD_SUCCESS_CHECK { u8 opcode; } Seq_GUARD_SUCCESS_CHECK;
typedef struct Seq_JIBAKU_INIT { u8 opcode; u8 operand01; } Seq_JIBAKU_INIT;
typedef struct Seq_JIBAKU { u8 opcode; } Seq_JIBAKU;
typedef struct Seq_JIBAKU_LOOP { u8 opcode; void* operand01; u8 operand05; } Seq_JIBAKU_LOOP;
typedef struct Seq_KAIFUKU { u8 opcode; void* operand01; u8 operand05; } Seq_KAIFUKU;
typedef struct Seq_OUMU_CHECK { u8 opcode; } Seq_OUMU_CHECK;
typedef struct Seq_REFLEC { u8 opcode; } Seq_REFLEC;
typedef struct Seq_YADORIGI { u8 opcode; } Seq_YADORIGI;
typedef struct Seq_DAMAGE_CHG { u8 opcode; u8 operand01; } Seq_DAMAGE_CHG;
typedef struct Seq_NEMURU { u8 opcode; void* operand01; } Seq_NEMURU;
typedef struct Seq_NEKODAMASHI { u8 opcode; void* operand01; } Seq_NEKODAMASHI;
typedef struct Seq_SAWAGU { u8 opcode; } Seq_SAWAGU;
typedef struct Seq_SAWAGU_CHECK { u8 opcode; void* operand01; } Seq_SAWAGU_CHECK;
typedef struct Seq_TAKUWAERU { u8 opcode; } Seq_TAKUWAERU;
typedef struct Seq_HAKIDASU { u8 opcode; void* operand01; } Seq_HAKIDASU;
typedef struct Seq_NOMIKOMU { u8 opcode; void* operand01; } Seq_NOMIKOMU;
typedef struct Seq_SUITORI { u8 opcode; } Seq_SUITORI;
typedef struct Seq_CONDCHG { u8 opcode; u8 operand01; void* operand02; } Seq_CONDCHG;
typedef struct Seq_KUROIKIRI { u8 opcode; } Seq_KUROIKIRI;
typedef struct Seq_GAMAN { u8 opcode; } Seq_GAMAN;
typedef struct Seq_ABARERU { u8 opcode; } Seq_ABARERU;
typedef struct Seq_RENZOKU { u8 opcode; u8 operand01; } Seq_RENZOKU;
typedef struct Seq_RENZOKU_NUM_INIT { u8 opcode; } Seq_RENZOKU_NUM_INIT;
typedef struct Seq_HUKITOBASHI { u8 opcode; void* operand01; } Seq_HUKITOBASHI;
typedef struct Seq_TEXTURE { u8 opcode; void* operand01; } Seq_TEXTURE;
typedef struct Seq_KOBAN_CHECK { u8 opcode; } Seq_KOBAN_CHECK;
typedef struct Seq_HIKARINOKABE { u8 opcode; } Seq_HIKARINOKABE;
typedef struct Seq_ICHIGEKI { u8 opcode; void* operand01; } Seq_ICHIGEKI;
typedef struct Seq_HPHALF { u8 opcode; } Seq_HPHALF;
typedef struct Seq_WEATHER_CHANGE { u8 opcode; u8 operand01; u8 operand02; } Seq_WEATHER_CHANGE;
typedef struct Seq_WEATHER_KEEP { u8 opcode; } Seq_WEATHER_KEEP;
typedef struct Seq_MEROMERO { u8 opcode; void* operand01; } Seq_MEROMERO;
typedef struct Seq_CONDITION_GAUGE { u8 opcode; u8 operand01; } Seq_CONDITION_GAUGE;
typedef struct Seq_SHIROIKIRI { u8 opcode; } Seq_SHIROIKIRI;
typedef struct Seq_KIAIDAME { u8 opcode; } Seq_KIAIDAME;
typedef struct Seq_HENSHIN { u8 opcode; } Seq_HENSHIN;
typedef struct Seq_MIGAWARI { u8 opcode; } Seq_MIGAWARI;
typedef struct Seq_MONOMANE { u8 opcode; void* operand01; } Seq_MONOMANE;
typedef struct Seq_YUBIWOHURU { u8 opcode; } Seq_YUBIWOHURU;
typedef struct Seq_CHIKYUUNAGE { u8 opcode; } Seq_CHIKYUUNAGE;
typedef struct Seq_PSYCHOWAVE { u8 opcode; } Seq_PSYCHOWAVE;
typedef struct Seq_COUNTER { u8 opcode; void* operand01; } Seq_COUNTER;
typedef struct Seq_MIRRORCOAT { u8 opcode; void* operand01; } Seq_MIRRORCOAT;
typedef struct Seq_KANASHIBARI { u8 opcode; void* operand01; } Seq_KANASHIBARI;
typedef struct Seq_ENCORE { u8 opcode; void* operand01; } Seq_ENCORE;
typedef struct Seq_ITAMIWAKE { u8 opcode; void* operand01; } Seq_ITAMIWAKE;
typedef struct Seq_TEXTURE2 { u8 opcode; void* operand01; } Seq_TEXTURE2;
typedef struct Seq_LOCKON { u8 opcode; } Seq_LOCKON;
typedef struct Seq_SKETCH { u8 opcode; void* operand01; } Seq_SKETCH;
typedef struct Seq_NEGOTO { u8 opcode; void* operand01; } Seq_NEGOTO;
typedef struct Seq_MICHIDURE { u8 opcode; void* operand01; } Seq_MICHIDURE;
typedef struct Seq_MICHIDURE_CHECK { u8 opcode; } Seq_MICHIDURE_CHECK;
typedef struct Seq_JITABATA { u8 opcode; } Seq_JITABATA;
typedef struct Seq_URAMI { u8 opcode; void* operand01; } Seq_URAMI;
typedef struct Seq_IYASHINOSUZU { u8 opcode; } Seq_IYASHINOSUZU;
typedef struct Seq_NOROI { u8 opcode; void* operand01; } Seq_NOROI;
typedef struct Seq_MAKIBISHI { u8 opcode; void* operand01; } Seq_MAKIBISHI;
typedef struct Seq_MIYABURU { u8 opcode; } Seq_MIYABURU;
typedef struct Seq_HOROBINOUTA { u8 opcode; void* operand01; } Seq_HOROBINOUTA;
typedef struct Seq_KOROGARU { u8 opcode; } Seq_KOROGARU;
typedef struct Seq_IBARU { u8 opcode; u8 operand01; void* operand02; } Seq_IBARU;
typedef struct Seq_RENZOKUGIRI { u8 opcode; } Seq_RENZOKUGIRI;
typedef struct Seq_NATSUKI { u8 opcode; } Seq_NATSUKI;
typedef struct Seq_PRESENT { u8 opcode; } Seq_PRESENT;
typedef struct Seq_SHINPINOMAMORI { u8 opcode; } Seq_SHINPINOMAMORI;
typedef struct Seq_MAGNITUDE { u8 opcode; } Seq_MAGNITUDE;
typedef struct Seq_OIUCHI_CHECK { u8 opcode; void* operand01; } Seq_OIUCHI_CHECK;
typedef struct Seq_HARADAIKO { u8 opcode; void* operand01; } Seq_HARADAIKO;
typedef struct Seq_JIKOANJI { u8 opcode; void* operand01; } Seq_JIKOANJI;
typedef struct Seq_KOUSOKUSPIN { u8 opcode; } Seq_KOUSOKUSPIN;
typedef struct Seq_MARUKUNARU { u8 opcode; } Seq_MARUKUNARU;
typedef struct Seq_WEATHERKAIFUKU { u8 opcode; void* operand01; } Seq_WEATHERKAIFUKU;
typedef struct Seq_MEZAMERUPOWER { u8 opcode; } Seq_MEZAMERUPOWER;
typedef struct Seq_JISIN { u8 opcode; } Seq_JISIN;
typedef struct Seq_MIRAIYOCHI { u8 opcode; void* operand01; } Seq_MIRAIYOCHI;
typedef struct Seq_HUKURODATAKI { u8 opcode; void* operand01; void* operand05; } Seq_HUKURODATAKI;
typedef struct Seq_KIERUTAME { u8 opcode; } Seq_KIERUTAME;
typedef struct Seq_KIERUTAME_AFTAR { u8 opcode; } Seq_KIERUTAME_AFTAR;
typedef struct Seq_CHIISAKUNARU { u8 opcode; } Seq_CHIISAKUNARU;
typedef struct Seq_OKIMIYAGE { u8 opcode; void* operand01; } Seq_OKIMIYAGE;
typedef struct Seq_KONOYUBITOMARE { u8 opcode; } Seq_KONOYUBITOMARE;
typedef struct Seq_JUUDEN { u8 opcode; } Seq_JUUDEN;
typedef struct Seq_SHIZENNOCHIKARA { u8 opcode; } Seq_SHIZENNOCHIKARA;
typedef struct Seq_REFLESH { u8 opcode; void* operand01; } Seq_REFLESH;
typedef struct Seq_ICHAMON { u8 opcode; void* operand01; } Seq_ICHAMON;
typedef struct Seq_KIAIPUNCH { u8 opcode; void* operand01; } Seq_KIAIPUNCH;
typedef struct Seq_CHOUHATSU { u8 opcode; void* operand01; } Seq_CHOUHATSU;
typedef struct Seq_TEDASUKE { u8 opcode; void* operand01; } Seq_TEDASUKE;
typedef struct Seq_TRICK { u8 opcode; void* operand01; } Seq_TRICK;
typedef struct Seq_NARIKIRI { u8 opcode; void* operand01; } Seq_NARIKIRI;
typedef struct Seq_NEGAIGOTO { u8 opcode; u8 operand01; void* operand02; } Seq_NEGAIGOTO;
typedef struct Seq_NEWOHARU { u8 opcode; void* operand01; } Seq_NEWOHARU;
typedef struct Seq_REVENGE { u8 opcode; } Seq_REVENGE;
typedef struct Seq_AKUBI { u8 opcode; void* operand01; } Seq_AKUBI;
typedef struct Seq_GAMUSYARA { u8 opcode; void* operand01; } Seq_GAMUSYARA;
typedef struct Seq_HUNKA { u8 opcode; } Seq_HUNKA;
typedef struct Seq_SKILLSWAP { u8 opcode; void* operand01; } Seq_SKILLSWAP;
typedef struct Seq_HUUIN { u8 opcode; void* operand01; } Seq_HUUIN;
typedef struct Seq_ONNEN { u8 opcode; void* operand01; } Seq_ONNEN;
typedef struct Seq_KETAGURI { u8 opcode; } Seq_KETAGURI;
typedef struct Seq_NEKONOTE { u8 opcode; void* operand01; } Seq_NEKONOTE;
typedef struct Seq_MAGICCORT { u8 opcode; void* operand01; } Seq_MAGICCORT;
typedef struct Seq_YOKODORI { u8 opcode; void* operand01; } Seq_YOKODORI;
typedef struct Seq_IKAKU { u8 opcode; void* operand01; } Seq_IKAKU;
typedef struct Seq_SIZENKAIHUKU { u8 opcode; u8 operand01; } Seq_SIZENKAIHUKU;
typedef struct Seq_HP_CHECK { u8 opcode; u8 operand01; void* operand02; } Seq_HP_CHECK;
typedef struct Seq_HIMITUNOTIKARA { u8 opcode; } Seq_HIMITUNOTIKARA;
typedef struct Seq_MONOHIROI { u8 opcode; } Seq_MONOHIROI;
typedef struct Seq_TENKIYA { u8 opcode; } Seq_TENKIYA;
typedef struct Seq_TENKIYA_CHECK { u8 opcode; } Seq_TENKIYA_CHECK;
typedef struct Seq_ASOBI { u8 opcode; void* operand01; } Seq_ASOBI;
typedef struct Seq_WEATHER_BALL { u8 opcode; } Seq_WEATHER_BALL;
typedef struct Seq_RECYCLE { u8 opcode; void* operand01; } Seq_RECYCLE;
typedef struct Seq_HOGOSYOKU { u8 opcode; void* operand01; } Seq_HOGOSYOKU;
typedef struct Seq_YOKODORI_CLIENT_SET { u8 opcode; } Seq_YOKODORI_CLIENT_SET;
typedef struct Seq_KAWARAWARI { u8 opcode; } Seq_KAWARAWARI;
typedef struct Seq_DARKREMOVE { u8 opcode; } Seq_DARKREMOVE;
typedef struct Seq_TELEPORT { u8 opcode; void* operand01; } Seq_TELEPORT;
typedef struct Seq_STATUS_GET8 { u8 opcode; u8 operand01; void* operand02; void* operand06; u16 operand0A; void* operand0C; void* operand10; } Seq_STATUS_GET8;
typedef struct Seq_STATUS_GET16 { u8 opcode; u8 operand01; void* operand02; void* operand06; u16 operand0A; void* operand0C; void* operand10; } Seq_STATUS_GET16;
typedef struct Seq_STATUS_GET32 { u8 opcode; u8 operand01; void* operand02; void* operand06; u16 operand0A; void* operand0C; void* operand10; } Seq_STATUS_GET32;
typedef struct Seq_STATUS_SET8 { u8 opcode; u8 operand01; void* operand02; void* operand06; u16 operand0A; void* operand0C; void* operand10; } Seq_STATUS_SET8;
typedef struct Seq_STATUS_SET16 { u8 opcode; u8 operand01; void* operand02; void* operand06; u16 operand0A; void* operand0C; void* operand10; } Seq_STATUS_SET16;
typedef struct Seq_STATUS_SET32 { u8 opcode; u8 operand01; void* operand02; void* operand06; u16 operand0A; void* operand0C; void* operand10; } Seq_STATUS_SET32;

typedef struct lbl_80414090_Stream {
    Seq_STATUS_GET16 command000;
    Seq_IF16 command001;
    Seq_WAZAKOUKA_CHECK command002;
    Seq_SET32BIT command003;
    Seq_SETVALUE command004;
    Seq_STATUS_SET8 command005;
} lbl_80414090_Stream;
extern lbl_80414090_Stream lbl_80414090;

typedef struct lbl_804140DE_Stream {
    Seq_BADGECHECK command000;
} lbl_804140DE_Stream;
extern lbl_804140DE_Stream lbl_804140DE;

typedef struct lbl_804140DF_Stream {
    Seq_HITCHECK command000;
} lbl_804140DF_Stream;
extern lbl_804140DF_Stream lbl_804140DF;

typedef struct WAZA_HitCalc_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_PP_DEC command001;
} WAZA_HitCalc_Stream;
extern WAZA_HitCalc_Stream WAZA_HitCalc;

typedef struct WAZA_HitCalcOnly_Stream {
    Seq_CRITICAL_CHECK command000;
    Seq_DAMAGE_CALC command001;
    Seq_TYPE_CHECK command002;
    Seq_DAMAGE_LOSS command003;
} WAZA_HitCalcOnly_Stream;
extern WAZA_HitCalcOnly_Stream WAZA_HitCalcOnly;

typedef struct WAZA_Hit_Stream {
    Seq_SETVALUE command000;
    Seq_WAZA_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_WAZAKOUKA_SE command003;
    Seq_POKE_BLINK command004;
    Seq_CLIENT_BIT_WAIT command005;
    Seq_HP_DEC command006;
    Seq_CRITICAL_MESSAGE command007;
    Seq_MESSAGE_WAIT command008;
    Seq_WAZAKOUKA_MESSAGE command009;
    Seq_MESSAGE_WAIT command010;
    Seq_HP_DEC_WAIT command011;
    Seq_EFFECT_WAIT command012;
    Seq_TSUIKA_CHECK command013;
    Seq_KIZETSU_CHECK command014;
} WAZA_Hit_Stream;
extern WAZA_Hit_Stream WAZA_Hit;

typedef struct WAZA_WazaEnd_Stream {
    Seq_SETVALUE command000;
    Seq_WKC_ACT command001;
    Seq_WAZAEND command002;
} WAZA_WazaEnd_Stream;
extern WAZA_WazaEnd_Stream WAZA_WazaEnd;

typedef struct lbl_80414119_Stream {
    Seq_STATUS_SET16 command000;
} lbl_80414119_Stream;
extern lbl_80414119_Stream lbl_80414119;

typedef struct WAZA_NormalNohit_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_PP_DEC command001;
} WAZA_NormalNohit_Stream;
extern WAZA_NormalNohit_Stream WAZA_NormalNohit;

typedef struct WAZA_NormalNohitWait_Stream {
    Seq_WAIT command000;
} WAZA_NormalNohitWait_Stream;
extern WAZA_NormalNohitWait_Stream WAZA_NormalNohitWait;

typedef struct WAZA_NormalNohit2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_WAZAKOUKA_SE command001;
    Seq_WAZAKOUKA_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
    Seq_BADGECHECK command006;
    Seq_ATTACK_MESSAGE command007;
    Seq_PP_DEC command008;
    Seq_CONDITION2_CHECK command009;
    Seq_CONDITION_CHECK command010;
    Seq_SAWAGU_CHECK command011;
    Seq_CONDITION_CHECK command012;
    Seq_HITCHECK command013;
    Seq_SIDECONDITION_CHECK command014;
    Seq_WAZA_EFFECT command015;
    Seq_EFFECT_WAIT command016;
    Seq_SETVALUE command017;
    Seq_TSUIKA_DIRECT_ACT command018;
    Seq_EFFECT_WAIT command019;
    Seq_JUMP command020;
} WAZA_NormalNohit2_Stream;
extern WAZA_NormalNohit2_Stream WAZA_NormalNohit2;

typedef struct lbl_8041418B_Stream {
    Seq_WAIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} lbl_8041418B_Stream;
extern lbl_8041418B_Stream lbl_8041418B;

typedef struct lbl_804141A4_Stream {
    Seq_WAIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
    Seq_WAIT command006;
    Seq_FIGHT_EFFECT command007;
    Seq_MESSAGE_TBL command008;
    Seq_MESSAGE_WAIT command009;
    Seq_EFFECT_WAIT command010;
    Seq_JUMP command011;
    Seq_SETVALUE command012;
    Seq_JUMP command013;
    Seq_BADGECHECK command014;
    Seq_HITCHECK command015;
    Seq_ATTACK_MESSAGE command016;
    Seq_PP_DEC command017;
    Seq_CRITICAL_CHECK command018;
    Seq_DAMAGE_CALC command019;
    Seq_TYPE_CHECK command020;
    Seq_DAMAGE_LOSS command021;
    Seq_WAZA_EFFECT command022;
    Seq_EFFECT_WAIT command023;
    Seq_WAZAKOUKA_SE command024;
    Seq_POKE_BLINK command025;
    Seq_CLIENT_BIT_WAIT command026;
    Seq_HP_DEC command027;
    Seq_CRITICAL_MESSAGE command028;
    Seq_MESSAGE_WAIT command029;
    Seq_WAZAKOUKA_MESSAGE command030;
    Seq_MESSAGE_WAIT command031;
    Seq_HP_DEC_WAIT command032;
    Seq_EFFECT_WAIT command033;
    Seq_SUITORI command034;
    Seq_SET32BIT command035;
    Seq_SPEABI_CHECK command036;
    Seq_SETVALUE command037;
    Seq_JUMP command038;
    Seq_DAMAGE_CHG command039;
    Seq_SETVALUE command040;
} lbl_804141A4_Stream;
extern lbl_804141A4_Stream lbl_804141A4;

typedef struct lbl_80414228_Stream {
    Seq_WAZA_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_HP_DEC command002;
    Seq_STATUS_GET8 command003;
    Seq_IF8 command004;
    Seq_MESSAGE_TBL command005;
    Seq_MESSAGE_WAIT command006;
} lbl_80414228_Stream;
extern lbl_80414228_Stream lbl_80414228;

typedef struct lbl_80414254_Stream {
    Seq_HP_DEC_WAIT command000;
    Seq_EFFECT_WAIT command001;
    Seq_KIZETSU_CHECK command002;
    Seq_KIZETSU_CHECK command003;
    Seq_JUMP command004;
    Seq_SETVALUE command005;
    Seq_JUMP command006;
    Seq_SETVALUE command007;
    Seq_JUMP command008;
    Seq_SETVALUE command009;
    Seq_JUMP command010;
    Seq_BADGECHECK command011;
    Seq_ATTACK_MESSAGE command012;
    Seq_PP_DEC command013;
    Seq_JIBAKU_INIT command014;
    Seq_JIBAKU command015;
    Seq_CLIENT_BIT_WAIT command016;
    Seq_SETVALUE command017;
    Seq_STATUS_GET8 command018;
    Seq_IF8 command019;
    Seq_GOSUB command020;
    Seq_JUMP command021;
} lbl_80414254_Stream;
extern lbl_80414254_Stream lbl_80414254;

typedef struct lbl_804142C2_Stream {
    Seq_WAZA_EFFECT command000;
    Seq_EFFECT_WAIT command001;
} lbl_804142C2_Stream;
extern lbl_804142C2_Stream lbl_804142C2;

typedef struct lbl_804142C5_Stream {
    Seq_LOOP_INIT command000;
    Seq_CRITICAL_CHECK command001;
    Seq_DAMAGE_CALC command002;
    Seq_TYPE_CHECK command003;
    Seq_DAMAGE_LOSS command004;
    Seq_HITCHECK command005;
    Seq_WAZA_EFFECT command006;
    Seq_EFFECT_WAIT command007;
    Seq_WAZAKOUKA_SE command008;
    Seq_POKE_BLINK command009;
    Seq_CLIENT_BIT_WAIT command010;
    Seq_HP_DEC command011;
    Seq_CRITICAL_MESSAGE command012;
    Seq_MESSAGE_WAIT command013;
    Seq_WAZAKOUKA_MESSAGE command014;
    Seq_MESSAGE_WAIT command015;
    Seq_HP_DEC_WAIT command016;
    Seq_EFFECT_WAIT command017;
    Seq_KIZETSU_CHECK command018;
    Seq_SETVALUE command019;
    Seq_WKC_ACT command020;
    Seq_JIBAKU_LOOP command021;
    Seq_KIZETSU_CHECK command022;
    Seq_WAZAEND command023;
    Seq_FIGHT_EFFECT command024;
    Seq_WAZAKOUKA_SE command025;
    Seq_WAZAKOUKA_MESSAGE command026;
    Seq_MESSAGE_WAIT command027;
    Seq_EFFECT_WAIT command028;
    Seq_SETVALUE command029;
    Seq_WKC_ACT command030;
    Seq_JIBAKU_LOOP command031;
    Seq_KIZETSU_CHECK command032;
    Seq_WAZAEND command033;
    Seq_STATUS_SET16 command034;
    Seq_WAZA_EFFECT command035;
    Seq_EFFECT_WAIT command036;
    Seq_STATUS_SET16 command037;
    Seq_SEQRET command038;
    Seq_BADGECHECK command039;
    Seq_CONDITION2_CHECK command040;
    Seq_CONDITION_CHECK command041;
} lbl_804142C5_Stream;
extern lbl_804142C5_Stream lbl_804142C5;

typedef struct lbl_8041436A_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_PP_DEC command001;
    Seq_MESSAGE_WAIT command002;
    Seq_JUMP command003;
    Seq_HITCHECK command004;
    Seq_ATTACK_MESSAGE command005;
    Seq_PP_DEC command006;
    Seq_CRITICAL_CHECK command007;
    Seq_DAMAGE_CALC command008;
    Seq_TYPE_CHECK command009;
    Seq_DAMAGE_LOSS command010;
    Seq_WAZA_EFFECT command011;
    Seq_EFFECT_WAIT command012;
    Seq_WAZAKOUKA_SE command013;
    Seq_POKE_BLINK command014;
    Seq_CLIENT_BIT_WAIT command015;
    Seq_HP_DEC command016;
    Seq_CRITICAL_MESSAGE command017;
    Seq_MESSAGE_WAIT command018;
    Seq_WAZAKOUKA_MESSAGE command019;
    Seq_MESSAGE_WAIT command020;
    Seq_HP_DEC_WAIT command021;
    Seq_EFFECT_WAIT command022;
    Seq_WAZA_EFFECT command023;
    Seq_EFFECT_WAIT command024;
    Seq_SUITORI command025;
    Seq_SET32BIT command026;
    Seq_HP_DEC command027;
    Seq_STATUS_GET8 command028;
    Seq_IF8 command029;
    Seq_MESSAGE command030;
    Seq_MESSAGE_WAIT command031;
    Seq_HP_DEC_WAIT command032;
    Seq_EFFECT_WAIT command033;
} lbl_8041436A_Stream;
extern lbl_8041436A_Stream lbl_8041436A;

typedef struct lbl_804143D0_Stream {
    Seq_KIZETSU_CHECK command000;
    Seq_JUMP command001;
    Seq_BADGECHECK command002;
    Seq_ATTACK_MESSAGE command003;
    Seq_WAIT command004;
    Seq_OUMU_CHECK command005;
    Seq_PP_DEC command006;
    Seq_STATUS_SET16 command007;
    Seq_FIGHT_EFFECT command008;
    Seq_MESSAGE command009;
    Seq_MESSAGE_WAIT command010;
    Seq_EFFECT_WAIT command011;
    Seq_JUMP command012;
    Seq_SETVALUE command013;
    Seq_JUMP command014;
    Seq_SETVALUE command015;
    Seq_JUMP command016;
    Seq_SETVALUE command017;
    Seq_JUMP command018;
    Seq_SETVALUE command019;
    Seq_JUMP command020;
} lbl_804143D0_Stream;
extern lbl_804143D0_Stream lbl_804143D0;

typedef struct lbl_80414439_Stream {
    Seq_BADGECHECK command000;
} lbl_80414439_Stream;
extern lbl_80414439_Stream lbl_80414439;

typedef struct lbl_8041443A_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_PP_DEC command001;
    Seq_CONDCHG command002;
    Seq_IF8 command003;
    Seq_WAIT command004;
    Seq_JUMP command005;
    Seq_WAZA_EFFECT command006;
    Seq_EFFECT_WAIT command007;
    Seq_COND_CHG_WORK_SET command008;
    Seq_FIGHT_EFFECT command009;
    Seq_EFFECT_WAIT command010;
} lbl_8041443A_Stream;
extern lbl_8041443A_Stream lbl_8041443A;

typedef struct WAZA_CondUpMsg_Stream {
    Seq_MESSAGE_TBL command000;
    Seq_MESSAGE_WAIT command001;
    Seq_EFFECT_WAIT command002;
    Seq_JUMP command003;
} WAZA_CondUpMsg_Stream;
extern WAZA_CondUpMsg_Stream WAZA_CondUpMsg;

typedef struct WAZA_CondUpTsuikaMsg_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_JUMP command001;
    Seq_FIGHT_EFFECT command002;
    Seq_JUMP command003;
    Seq_EFFECT_WAIT command004;
    Seq_MESSAGE_TBL command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SEQRET command008;
    Seq_SETVALUE command009;
    Seq_JUMP command010;
    Seq_SETVALUE command011;
    Seq_JUMP command012;
    Seq_SETVALUE command013;
    Seq_JUMP command014;
    Seq_SETVALUE command015;
    Seq_JUMP command016;
    Seq_SETVALUE command017;
    Seq_JUMP command018;
} WAZA_CondUpTsuikaMsg_Stream;
extern WAZA_CondUpTsuikaMsg_Stream WAZA_CondUpTsuikaMsg;

typedef struct lbl_804144CD_Stream {
    Seq_BADGECHECK command000;
    Seq_CONDITION2_CHECK command001;
    Seq_HITCHECK command002;
    Seq_ATTACK_MESSAGE command003;
    Seq_PP_DEC command004;
    Seq_CONDCHG command005;
    Seq_IF8 command006;
    Seq_IF8 command007;
    Seq_WAIT command008;
    Seq_JUMP command009;
    Seq_WAZA_EFFECT command010;
    Seq_EFFECT_WAIT command011;
    Seq_COND_CHG_WORK_SET command012;
    Seq_FIGHT_EFFECT command013;
    Seq_EFFECT_WAIT command014;
    Seq_JUMP command015;
    Seq_FIGHT_EFFECT command016;
} lbl_804144CD_Stream;
extern lbl_804144CD_Stream lbl_804144CD;

typedef struct WAZA_CondDownMsg_Stream {
    Seq_MESSAGE_TBL command000;
    Seq_MESSAGE_WAIT command001;
    Seq_EFFECT_WAIT command002;
    Seq_JUMP command003;
} WAZA_CondDownMsg_Stream;
extern WAZA_CondDownMsg_Stream WAZA_CondDownMsg;

typedef struct WAZA_CondDownTsuikaMsg_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE_TBL command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
    Seq_BADGECHECK command006;
    Seq_ATTACK_MESSAGE command007;
    Seq_PP_DEC command008;
    Seq_WAZA_EFFECT command009;
    Seq_EFFECT_WAIT command010;
    Seq_KUROIKIRI command011;
    Seq_MESSAGE command012;
    Seq_MESSAGE_WAIT command013;
    Seq_EFFECT_WAIT command014;
    Seq_JUMP command015;
    Seq_CONDITION2_CHECK command016;
    Seq_BADGECHECK command017;
    Seq_ATTACK_MESSAGE command018;
    Seq_PP_DEC command019;
    Seq_WAZA_EFFECT command020;
    Seq_EFFECT_WAIT command021;
    Seq_SET32BIT command022;
    Seq_GAMAN command023;
    Seq_EFFECT_WAIT command024;
    Seq_JUMP command025;
    Seq_BADGECHECK command026;
    Seq_HITCHECK command027;
    Seq_ATTACK_MESSAGE command028;
    Seq_CONDITION2_CHECK command029;
    Seq_PP_DEC command030;
    Seq_ABARERU command031;
    Seq_JUMP command032;
    Seq_BADGECHECK command033;
    Seq_ATTACK_MESSAGE command034;
    Seq_PP_DEC command035;
    Seq_SPEABI_CHECK command036;
    Seq_WAZAKOUKA_CHECK command037;
    Seq_HITCHECK command038;
    Seq_HITCHECK command039;
    Seq_HUKITOBASHI command040;
    Seq_BADGECHECK command041;
    Seq_HITCHECK command042;
    Seq_ATTACK_MESSAGE command043;
    Seq_PP_DEC command044;
    Seq_RENZOKU command045;
    Seq_RENZOKU_NUM_INIT command046;
    Seq_SETVALUE command047;
} WAZA_CondDownTsuikaMsg_Stream;
extern WAZA_CondDownTsuikaMsg_Stream WAZA_CondDownTsuikaMsg;

typedef struct lbl_804145CD_Stream {
    Seq_STATUS_GET16 command000;
    Seq_IF16 command001;
    Seq_CONDITION_CHECK command002;
    Seq_LOOP_INIT command003;
    Seq_SETWORK command004;
    Seq_CRITICAL_CHECK command005;
    Seq_DAMAGE_CALC command006;
    Seq_TYPE_CHECK command007;
    Seq_STATUS_GET8 command008;
    Seq_IF8 command009;
    Seq_DAMAGE_LOSS command010;
    Seq_WAZA_EFFECT command011;
    Seq_EFFECT_WAIT command012;
    Seq_WAZAKOUKA_SE command013;
    Seq_POKE_BLINK command014;
    Seq_CLIENT_BIT_WAIT command015;
    Seq_HP_DEC command016;
    Seq_CRITICAL_MESSAGE command017;
    Seq_MESSAGE_WAIT command018;
    Seq_ADDVALUE command019;
    Seq_SETVALUE command020;
    Seq_STATUS_GET8 command021;
    Seq_IF8 command022;
    Seq_HP_CHECK command023;
    Seq_LOOP command024;
    Seq_JUMP command025;
} lbl_804145CD_Stream;
extern lbl_804145CD_Stream lbl_804145CD;

typedef struct lbl_8041466D_Stream {
    Seq_HP_DEC_WAIT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SETVALUE command002;
    Seq_WKC_ACT command003;
    Seq_HP_CHECK command004;
    Seq_JUMP command005;
} lbl_8041466D_Stream;
extern lbl_8041466D_Stream lbl_8041466D;

typedef struct lbl_80414685_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_WAZAKOUKA_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_STATUS_GET8 command003;
    Seq_IF8 command004;
    Seq_STATUS_SET8 command005;
    Seq_MESSAGE command006;
    Seq_MESSAGE_WAIT command007;
    Seq_HP_DEC_WAIT command008;
    Seq_EFFECT_WAIT command009;
    Seq_SETVALUE command010;
    Seq_WKC_ACT command011;
    Seq_TSUIKA_CHECK command012;
    Seq_KIZETSU_CHECK command013;
    Seq_SETVALUE command014;
    Seq_WKC_ACT command015;
    Seq_SETVALUE command016;
    Seq_WKC_ACT command017;
    Seq_WAZAEND command018;
    Seq_BADGECHECK command019;
    Seq_ATTACK_MESSAGE command020;
    Seq_PP_DEC command021;
    Seq_TEXTURE command022;
    Seq_WAZA_EFFECT command023;
    Seq_EFFECT_WAIT command024;
    Seq_MESSAGE command025;
    Seq_MESSAGE_WAIT command026;
    Seq_EFFECT_WAIT command027;
    Seq_JUMP command028;
    Seq_SETVALUE command029;
    Seq_JUMP command030;
    Seq_BADGECHECK command031;
    Seq_ATTACK_MESSAGE command032;
    Seq_PP_DEC command033;
    Seq_KAIFUKU command034;
    Seq_WAZA_EFFECT command035;
    Seq_EFFECT_WAIT command036;
    Seq_SET32BIT command037;
    Seq_HP_DEC command038;
    Seq_MESSAGE command039;
    Seq_MESSAGE_WAIT command040;
    Seq_HP_DEC_WAIT command041;
    Seq_EFFECT_WAIT command042;
    Seq_JUMP command043;
    Seq_BADGECHECK command044;
    Seq_ATTACK_MESSAGE command045;
    Seq_PP_DEC command046;
    Seq_SPEABI_CHECK command047;
    Seq_CONDITION2_CHECK command048;
    Seq_CONDITION_CHECK command049;
    Seq_CONDITION_CHECK command050;
    Seq_CONDITION_CHECK command051;
    Seq_CHECK_TYPE command052;
    Seq_CHECK_TYPE command053;
    Seq_HITCHECK command054;
    Seq_SIDECONDITION_CHECK command055;
    Seq_WAZA_EFFECT command056;
    Seq_EFFECT_WAIT command057;
    Seq_SETVALUE command058;
    Seq_TSUIKA_DIRECT_ACT command059;
    Seq_WAZAKOUKA_MESSAGE command060;
    Seq_MESSAGE_WAIT command061;
    Seq_EFFECT_WAIT command062;
    Seq_JUMP command063;
} lbl_80414685_Stream;
extern lbl_80414685_Stream lbl_80414685;

typedef struct lbl_804147A4_Stream {
    Seq_WAIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
    Seq_STATUS_GET32 command006;
    Seq_STATUS_SET32 command007;
    Seq_SETVALUE command008;
    Seq_GOSUB command009;
    Seq_JUMP command010;
    Seq_SETVALUE command011;
    Seq_JUMP command012;
    Seq_BADGECHECK command013;
    Seq_ATTACK_MESSAGE command014;
    Seq_PP_DEC command015;
    Seq_HIKARINOKABE command016;
    Seq_JUMP command017;
    Seq_SETVALUE command018;
    Seq_JUMP command019;
    Seq_BADGECHECK command020;
    Seq_ATTACK_MESSAGE command021;
    Seq_PP_DEC command022;
    Seq_CONDITION_CHECK command023;
    Seq_SAWAGU_CHECK command024;
    Seq_NEMURU command025;
    Seq_WAIT command026;
    Seq_STATUS_EFFECT command027;
    Seq_EFFECT_WAIT command028;
    Seq_MESSAGE_TBL command029;
    Seq_MESSAGE_WAIT command030;
    Seq_CONDITION_GAUGE command031;
    Seq_EFFECT_WAIT command032;
    Seq_CLIENT_BIT_WAIT command033;
    Seq_JUMP command034;
    Seq_WAIT command035;
    Seq_FIGHT_EFFECT command036;
    Seq_MESSAGE_TBL command037;
    Seq_MESSAGE_WAIT command038;
    Seq_EFFECT_WAIT command039;
    Seq_JUMP command040;
    Seq_WAIT command041;
    Seq_FIGHT_EFFECT command042;
    Seq_MESSAGE command043;
    Seq_MESSAGE_WAIT command044;
    Seq_EFFECT_WAIT command045;
    Seq_JUMP command046;
    Seq_BADGECHECK command047;
    Seq_ATTACK_MESSAGE command048;
    Seq_PP_DEC command049;
    Seq_HITCHECK command050;
    Seq_TYPE_CHECK command051;
    Seq_STATUS_GET8 command052;
    Seq_IF8 command053;
    Seq_ICHIGEKI command054;
    Seq_MICHIDURE_CHECK command055;
    Seq_JUMP command056;
    Seq_WAIT command057;
    Seq_FIGHT_EFFECT command058;
    Seq_MESSAGE_TBL command059;
    Seq_MESSAGE_WAIT command060;
    Seq_EFFECT_WAIT command061;
    Seq_JUMP command062;
    Seq_CONDITION2_CHECK command063;
    Seq_IF32 command064;
    Seq_SETVALUE command065;
    Seq_BADGECHECK command066;
    Seq_GOSUB command067;
    Seq_JUMP command068;
} lbl_804147A4_Stream;
extern lbl_804147A4_Stream lbl_804147A4;

typedef struct lbl_804148ED_Stream {
    Seq_BADGECHECK command000;
    Seq_SETVALUE command001;
    Seq_SETVALUE command002;
    Seq_SAKUJO command003;
    Seq_SET32BIT command004;
    Seq_STATUS_GET16 command005;
    Seq_IF16 command006;
    Seq_SETVALUE command007;
    Seq_JUMP command008;
} lbl_804148ED_Stream;
extern lbl_804148ED_Stream lbl_804148ED;

typedef struct lbl_80414930_Stream {
    Seq_PP_DEC command000;
    Seq_WAZA_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_SET32BIT command003;
    Seq_SETVALUE command004;
    Seq_TSUIKA_DIRECT_ACT command005;
    Seq_SETWORK command006;
    Seq_MESSAGE_TBL command007;
    Seq_MESSAGE_WAIT command008;
    Seq_EFFECT_WAIT command009;
    Seq_SEQRET command010;
    Seq_BADGECHECK command011;
    Seq_HITCHECK command012;
    Seq_ATTACK_MESSAGE command013;
    Seq_PP_DEC command014;
    Seq_TYPE_CHECK command015;
    Seq_STATUS_SET16 command016;
    Seq_STATUS_SET16 command017;
    Seq_HPHALF command018;
    Seq_JUMP command019;
    Seq_BADGECHECK command020;
    Seq_HITCHECK command021;
    Seq_ATTACK_MESSAGE command022;
    Seq_PP_DEC command023;
    Seq_TYPE_CHECK command024;
    Seq_STATUS_SET16 command025;
    Seq_STATUS_SET16 command026;
    Seq_STATUS_SET32 command027;
    Seq_KORAERU_CHECK command028;
    Seq_JUMP command029;
    Seq_STATUS_GET16 command030;
    Seq_IF16 command031;
    Seq_WAZAKOUKA_CHECK command032;
    Seq_SET32BIT command033;
    Seq_SETVALUE command034;
    Seq_STATUS_SET8 command035;
    Seq_SETVALUE command036;
    Seq_JUMP command037;
    Seq_BADGECHECK command038;
    Seq_HITCHECK command039;
    Seq_ATTACK_MESSAGE command040;
    Seq_PP_DEC command041;
    Seq_RENZOKU command042;
    Seq_RENZOKU_NUM_INIT command043;
    Seq_SETVALUE command044;
    Seq_JUMP command045;
    Seq_BADGECHECK command046;
    Seq_HITCHECK command047;
    Seq_JUMP command048;
    Seq_ATTACK_MESSAGE command049;
    Seq_PP_DEC command050;
    Seq_WAIT command051;
    Seq_FIGHT_EFFECT command052;
    Seq_WAZAKOUKA_MESSAGE command053;
    Seq_MESSAGE_WAIT command054;
    Seq_EFFECT_WAIT command055;
    Seq_SETVALUE command056;
    Seq_STATUS_GET8 command057;
    Seq_IF8 command058;
    Seq_FIGHT_EFFECT command059;
    Seq_EFFECT_WAIT command060;
    Seq_DAMAGE_CALC command061;
    Seq_TYPE_CHECK command062;
    Seq_DAMAGE_LOSS command063;
    Seq_DAMAGE_CHG command064;
    Seq_STATUS_SET16 command065;
    Seq_SET32BIT command066;
    Seq_HP_DEC command067;
    Seq_MESSAGE command068;
    Seq_MESSAGE_WAIT command069;
    Seq_HP_DEC_WAIT command070;
    Seq_EFFECT_WAIT command071;
    Seq_KIZETSU_CHECK command072;
    Seq_STATUS_SET16 command073;
    Seq_JUMP command074;
    Seq_BADGECHECK command075;
    Seq_ATTACK_MESSAGE command076;
    Seq_PP_DEC command077;
    Seq_SHIROIKIRI command078;
    Seq_WAZA_EFFECT command079;
    Seq_EFFECT_WAIT command080;
    Seq_MESSAGE_TBL command081;
    Seq_MESSAGE_WAIT command082;
    Seq_EFFECT_WAIT command083;
    Seq_JUMP command084;
    Seq_BADGECHECK command085;
    Seq_ATTACK_MESSAGE command086;
    Seq_PP_DEC command087;
    Seq_CONDITION2_CHECK command088;
    Seq_KIAIDAME command089;
    Seq_WAZA_EFFECT command090;
    Seq_EFFECT_WAIT command091;
    Seq_MESSAGE_TBL command092;
    Seq_MESSAGE_WAIT command093;
    Seq_EFFECT_WAIT command094;
    Seq_JUMP command095;
    Seq_SETVALUE command096;
    Seq_JUMP command097;
    Seq_BADGECHECK command098;
    Seq_ATTACK_MESSAGE command099;
    Seq_PP_DEC command100;
    Seq_SPEABI_CHECK command101;
    Seq_CONDITION2_CHECK command102;
    Seq_CONDITION2_CHECK command103;
    Seq_HITCHECK command104;
    Seq_SIDECONDITION_CHECK command105;
    Seq_WAZA_EFFECT command106;
    Seq_EFFECT_WAIT command107;
    Seq_SETVALUE command108;
    Seq_TSUIKA_DIRECT_ACT command109;
    Seq_WAZAKOUKA_MESSAGE command110;
    Seq_MESSAGE_WAIT command111;
    Seq_EFFECT_WAIT command112;
    Seq_JUMP command113;
} lbl_80414930_Stream;
extern lbl_80414930_Stream lbl_80414930;

typedef struct lbl_80414B70_Stream {
    Seq_WAIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
    Seq_SETVALUE command006;
    Seq_JUMP command007;
    Seq_SETVALUE command008;
    Seq_JUMP command009;
    Seq_SETVALUE command010;
    Seq_JUMP command011;
    Seq_SETVALUE command012;
    Seq_JUMP command013;
    Seq_SETVALUE command014;
    Seq_JUMP command015;
    Seq_BADGECHECK command016;
    Seq_ATTACK_MESSAGE command017;
    Seq_PP_DEC command018;
    Seq_HENSHIN command019;
    Seq_WAZA_EFFECT command020;
    Seq_EFFECT_WAIT command021;
    Seq_MESSAGE_TBL command022;
    Seq_MESSAGE_WAIT command023;
    Seq_EFFECT_WAIT command024;
    Seq_JUMP command025;
    Seq_SETVALUE command026;
    Seq_JUMP command027;
    Seq_SETVALUE command028;
    Seq_JUMP command029;
    Seq_SETVALUE command030;
    Seq_JUMP command031;
    Seq_SETVALUE command032;
    Seq_JUMP command033;
    Seq_BADGECHECK command034;
    Seq_ATTACK_MESSAGE command035;
    Seq_PP_DEC command036;
    Seq_REFLEC command037;
    Seq_WAZA_EFFECT command038;
    Seq_EFFECT_WAIT command039;
    Seq_MESSAGE_TBL command040;
    Seq_MESSAGE_WAIT command041;
    Seq_EFFECT_WAIT command042;
    Seq_JUMP command043;
    Seq_BADGECHECK command044;
    Seq_ATTACK_MESSAGE command045;
    Seq_PP_DEC command046;
    Seq_SPEABI_CHECK command047;
    Seq_CONDITION2_CHECK command048;
    Seq_CONDITION_CHECK command049;
    Seq_CONDITION_CHECK command050;
    Seq_CHECK_TYPE command051;
    Seq_CHECK_TYPE command052;
    Seq_CONDITION_CHECK command053;
    Seq_HITCHECK command054;
    Seq_SIDECONDITION_CHECK command055;
    Seq_WAZA_EFFECT command056;
    Seq_EFFECT_WAIT command057;
    Seq_SETVALUE command058;
    Seq_TSUIKA_DIRECT_ACT command059;
    Seq_WAZAKOUKA_MESSAGE command060;
    Seq_MESSAGE_WAIT command061;
    Seq_EFFECT_WAIT command062;
    Seq_JUMP command063;
    Seq_BADGECHECK command064;
    Seq_ATTACK_MESSAGE command065;
    Seq_PP_DEC command066;
    Seq_SPEABI_CHECK command067;
    Seq_CONDITION2_CHECK command068;
    Seq_TYPE_CHECK command069;
    Seq_STATUS_GET8 command070;
    Seq_IF8 command071;
    Seq_CONDITION_CHECK command072;
    Seq_CONDITION_CHECK command073;
    Seq_HITCHECK command074;
    Seq_SIDECONDITION_CHECK command075;
    Seq_WAZA_EFFECT command076;
    Seq_EFFECT_WAIT command077;
    Seq_SETVALUE command078;
    Seq_TSUIKA_DIRECT_ACT command079;
    Seq_WAZAKOUKA_MESSAGE command080;
    Seq_MESSAGE_WAIT command081;
    Seq_EFFECT_WAIT command082;
    Seq_JUMP command083;
    Seq_WAIT command084;
    Seq_FIGHT_EFFECT command085;
    Seq_MESSAGE command086;
    Seq_MESSAGE_WAIT command087;
    Seq_EFFECT_WAIT command088;
    Seq_JUMP command089;
    Seq_STATUS_GET32 command090;
    Seq_STATUS_SET32 command091;
    Seq_SETVALUE command092;
    Seq_GOSUB command093;
    Seq_JUMP command094;
    Seq_SETVALUE command095;
    Seq_SETVALUE command096;
    Seq_JUMP command097;
    Seq_SETVALUE command098;
    Seq_SETVALUE command099;
    Seq_JUMP command100;
    Seq_SETVALUE command101;
    Seq_SETVALUE command102;
    Seq_JUMP command103;
    Seq_SETVALUE command104;
    Seq_SETVALUE command105;
    Seq_JUMP command106;
    Seq_SETVALUE command107;
    Seq_SETVALUE command108;
    Seq_JUMP command109;
    Seq_SETVALUE command110;
    Seq_SETVALUE command111;
    Seq_JUMP command112;
    Seq_CONDITION2_CHECK command113;
    Seq_IF32 command114;
    Seq_SETVALUE command115;
    Seq_BADGECHECK command116;
    Seq_GOSUB command117;
    Seq_JUMP command118;
    Seq_SETVALUE command119;
    Seq_JUMP command120;
    Seq_BADGECHECK command121;
    Seq_HITCHECK command122;
    Seq_SETVALUE command123;
    Seq_ATTACK_MESSAGE command124;
    Seq_PP_DEC command125;
    Seq_RENZOKU command126;
    Seq_RENZOKU_NUM_INIT command127;
    Seq_JUMP command128;
    Seq_BADGECHECK command129;
    Seq_PP_DEC command130;
    Seq_ATTACK_MESSAGE command131;
    Seq_CLIENT_BIT_WAIT command132;
    Seq_CONDITION2_CHECK command133;
    Seq_MIGAWARI command134;
    Seq_IF8 command135;
    Seq_JUMP command136;
    Seq_WAZA_EFFECT command137;
    Seq_EFFECT_WAIT command138;
    Seq_HP_DEC command139;
    Seq_MESSAGE_TBL command140;
    Seq_MESSAGE_WAIT command141;
    Seq_HP_DEC_WAIT command142;
    Seq_EFFECT_WAIT command143;
    Seq_JUMP command144;
    Seq_FIGHT_EFFECT command145;
    Seq_MESSAGE_TBL command146;
    Seq_MESSAGE_WAIT command147;
    Seq_EFFECT_WAIT command148;
    Seq_JUMP command149;
    Seq_FIGHT_EFFECT command150;
    Seq_MESSAGE command151;
    Seq_MESSAGE_WAIT command152;
    Seq_EFFECT_WAIT command153;
    Seq_JUMP command154;
    Seq_BADGECHECK command155;
    Seq_HITCHECK command156;
    Seq_SETVALUE command157;
    Seq_JUMP command158;
} lbl_80414B70_Stream;
extern lbl_80414B70_Stream lbl_80414B70;

typedef struct WAZA_Handou_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_JUMP command004;
    Seq_BADGECHECK command005;
    Seq_HITCHECK command006;
    Seq_SETVALUE command007;
    Seq_TSUIKA_DIRECT_ACT command008;
    Seq_EFFECT_WAIT command009;
    Seq_SETVALUE command010;
    Seq_JUMP command011;
    Seq_SETVALUE command012;
    Seq_SAKUJO command013;
    Seq_JUMP command014;
    Seq_BADGECHECK command015;
    Seq_ATTACK_MESSAGE command016;
    Seq_PP_DEC command017;
    Seq_CONDITION2_CHECK command018;
    Seq_HITCHECK command019;
    Seq_MONOMANE command020;
    Seq_WAZA_EFFECT command021;
    Seq_EFFECT_WAIT command022;
    Seq_WAZA_EFFECT command023;
    Seq_EFFECT_WAIT command024;
    Seq_MESSAGE command025;
    Seq_MESSAGE_WAIT command026;
    Seq_EFFECT_WAIT command027;
    Seq_JUMP command028;
    Seq_BADGECHECK command029;
    Seq_ATTACK_MESSAGE command030;
    Seq_WAIT command031;
    Seq_WAZA_EFFECT command032;
    Seq_EFFECT_WAIT command033;
    Seq_SETVALUE command034;
    Seq_SETVALUE command035;
    Seq_YUBIWOHURU command036;
    Seq_BADGECHECK command037;
    Seq_ATTACK_MESSAGE command038;
    Seq_WAIT command039;
    Seq_PP_DEC command040;
    Seq_CONDITION2_CHECK command041;
    Seq_HITCHECK command042;
    Seq_YADORIGI command043;
    Seq_WAZA_EFFECT command044;
    Seq_EFFECT_WAIT command045;
    Seq_MESSAGE_TBL command046;
    Seq_MESSAGE_WAIT command047;
    Seq_EFFECT_WAIT command048;
    Seq_JUMP command049;
    Seq_BADGECHECK command050;
    Seq_ATTACK_MESSAGE command051;
    Seq_PP_DEC command052;
    Seq_WAZA_EFFECT command053;
    Seq_EFFECT_WAIT command054;
    Seq_MESSAGE command055;
    Seq_MESSAGE_WAIT command056;
    Seq_EFFECT_WAIT command057;
    Seq_JUMP command058;
    Seq_BADGECHECK command059;
    Seq_ATTACK_MESSAGE command060;
    Seq_PP_DEC command061;
    Seq_HITCHECK command062;
    Seq_KANASHIBARI command063;
    Seq_WAZA_EFFECT command064;
    Seq_EFFECT_WAIT command065;
    Seq_MESSAGE command066;
    Seq_MESSAGE_WAIT command067;
    Seq_EFFECT_WAIT command068;
    Seq_JUMP command069;
    Seq_BADGECHECK command070;
    Seq_HITCHECK command071;
    Seq_ATTACK_MESSAGE command072;
    Seq_PP_DEC command073;
    Seq_TYPE_CHECK command074;
    Seq_STATUS_SET16 command075;
    Seq_STATUS_SET16 command076;
    Seq_CHIKYUUNAGE command077;
    Seq_KORAERU_CHECK command078;
    Seq_JUMP command079;
    Seq_BADGECHECK command080;
    Seq_HITCHECK command081;
    Seq_ATTACK_MESSAGE command082;
    Seq_PP_DEC command083;
    Seq_TYPE_CHECK command084;
    Seq_STATUS_SET16 command085;
    Seq_STATUS_SET16 command086;
    Seq_PSYCHOWAVE command087;
    Seq_KORAERU_CHECK command088;
    Seq_JUMP command089;
    Seq_BADGECHECK command090;
    Seq_COUNTER command091;
    Seq_HITCHECK command092;
    Seq_ATTACK_MESSAGE command093;
    Seq_PP_DEC command094;
    Seq_TYPE_CHECK_NO_HIT command095;
    Seq_KORAERU_CHECK command096;
    Seq_JUMP command097;
    Seq_BADGECHECK command098;
    Seq_HITCHECK command099;
    Seq_ATTACK_MESSAGE command100;
    Seq_PP_DEC command101;
    Seq_ENCORE command102;
    Seq_WAZA_EFFECT command103;
    Seq_EFFECT_WAIT command104;
    Seq_MESSAGE command105;
    Seq_MESSAGE_WAIT command106;
    Seq_EFFECT_WAIT command107;
    Seq_JUMP command108;
    Seq_BADGECHECK command109;
    Seq_ATTACK_MESSAGE command110;
    Seq_PP_DEC command111;
    Seq_HITCHECK command112;
    Seq_ITAMIWAKE command113;
    Seq_WAZA_EFFECT command114;
    Seq_EFFECT_WAIT command115;
    Seq_SET32BIT command116;
    Seq_HP_DEC command117;
    Seq_HP_DEC_WAIT command118;
    Seq_EFFECT_WAIT command119;
    Seq_WAZA_EFFECT command120;
    Seq_EFFECT_WAIT command121;
    Seq_STATUS_SET32 command122;
    Seq_HP_DEC command123;
    Seq_MESSAGE command124;
    Seq_MESSAGE_WAIT command125;
    Seq_HP_DEC_WAIT command126;
    Seq_EFFECT_WAIT command127;
    Seq_JUMP command128;
    Seq_BADGECHECK command129;
    Seq_CONDITION_CHECK command130;
    Seq_ATTACK_MESSAGE command131;
    Seq_PP_DEC command132;
    Seq_JUMP command133;
    Seq_STATUS_GET16 command134;
    Seq_IF16 command135;
    Seq_STATUS_EFFECT command136;
    Seq_EFFECT_WAIT command137;
    Seq_MESSAGE command138;
    Seq_MESSAGE_WAIT command139;
    Seq_EFFECT_WAIT command140;
    Seq_ATTACK_MESSAGE command141;
    Seq_PP_DEC command142;
    Seq_HITCHECK command143;
    Seq_SETVALUE command144;
    Seq_JUMP command145;
    Seq_BADGECHECK command146;
    Seq_ATTACK_MESSAGE command147;
    Seq_PP_DEC command148;
    Seq_TEXTURE2 command149;
    Seq_WAZA_EFFECT command150;
    Seq_EFFECT_WAIT command151;
    Seq_MESSAGE command152;
    Seq_MESSAGE_WAIT command153;
    Seq_EFFECT_WAIT command154;
    Seq_JUMP command155;
    Seq_BADGECHECK command156;
    Seq_ATTACK_MESSAGE command157;
    Seq_PP_DEC command158;
    Seq_CONDITION2_CHECK command159;
    Seq_HITCHECK command160;
    Seq_LOCKON command161;
    Seq_WAZA_EFFECT command162;
    Seq_EFFECT_WAIT command163;
    Seq_MESSAGE command164;
    Seq_MESSAGE_WAIT command165;
    Seq_EFFECT_WAIT command166;
    Seq_JUMP command167;
    Seq_BADGECHECK command168;
    Seq_ATTACK_MESSAGE command169;
    Seq_PP_DEC command170;
    Seq_CONDITION2_CHECK command171;
    Seq_SKETCH command172;
    Seq_WAZA_EFFECT command173;
    Seq_EFFECT_WAIT command174;
    Seq_WAZA_EFFECT command175;
    Seq_EFFECT_WAIT command176;
    Seq_MESSAGE command177;
    Seq_MESSAGE_WAIT command178;
    Seq_EFFECT_WAIT command179;
    Seq_JUMP command180;
    Seq_BADGECHECK command181;
    Seq_CONDITION_CHECK command182;
    Seq_ATTACK_MESSAGE command183;
    Seq_PP_DEC command184;
    Seq_JUMP command185;
    Seq_STATUS_EFFECT command186;
    Seq_EFFECT_WAIT command187;
    Seq_MESSAGE command188;
    Seq_MESSAGE_WAIT command189;
    Seq_EFFECT_WAIT command190;
    Seq_ATTACK_MESSAGE command191;
    Seq_PP_DEC command192;
    Seq_SET32BIT command193;
    Seq_NEGOTO command194;
    Seq_WAIT command195;
    Seq_JUMP command196;
    Seq_WAZA_EFFECT command197;
    Seq_EFFECT_WAIT command198;
    Seq_SETVALUE command199;
    Seq_SETVALUE command200;
    Seq_WAZASEQADRS command201;
    Seq_BADGECHECK command202;
    Seq_ATTACK_MESSAGE command203;
    Seq_PP_DEC command204;
    Seq_MICHIDURE command205;
    Seq_WAZA_EFFECT command206;
    Seq_EFFECT_WAIT command207;
    Seq_MESSAGE command208;
    Seq_MESSAGE_WAIT command209;
    Seq_EFFECT_WAIT command210;
    Seq_JUMP command211;
    Seq_JITABATA command212;
    Seq_JUMP command213;
    Seq_BADGECHECK command214;
    Seq_ATTACK_MESSAGE command215;
    Seq_PP_DEC command216;
    Seq_HITCHECK command217;
    Seq_URAMI command218;
    Seq_WAZA_EFFECT command219;
    Seq_EFFECT_WAIT command220;
    Seq_MESSAGE command221;
    Seq_MESSAGE_WAIT command222;
    Seq_EFFECT_WAIT command223;
    Seq_JUMP command224;
    Seq_BADGECHECK command225;
    Seq_ATTACK_MESSAGE command226;
    Seq_PP_DEC command227;
    Seq_IYASHINOSUZU command228;
    Seq_CLIENT_BIT_WAIT command229;
    Seq_WAZA_EFFECT command230;
    Seq_EFFECT_WAIT command231;
    Seq_MESSAGE_TBL command232;
    Seq_MESSAGE_WAIT command233;
    Seq_EFFECT_WAIT command234;
    Seq_STATUS_GET16 command235;
    Seq_IF16 command236;
    Seq_IF8 command237;
    Seq_FIGHT_EFFECT command238;
    Seq_MESSAGE command239;
    Seq_MESSAGE_WAIT command240;
    Seq_EFFECT_WAIT command241;
    Seq_IF8 command242;
    Seq_FIGHT_EFFECT command243;
    Seq_MESSAGE command244;
    Seq_MESSAGE_WAIT command245;
    Seq_EFFECT_WAIT command246;
    Seq_CONDITION_GAUGE command247;
    Seq_CONDITION_GAUGE command248;
    Seq_CLIENT_BIT_WAIT command249;
    Seq_JUMP command250;
    Seq_BADGECHECK command251;
    Seq_ATTACK_MESSAGE command252;
    Seq_PP_DEC command253;
    Seq_SETVALUE command254;
    Seq_RENZOKU_NUM_INIT command255;
    Seq_LOOPCNT command256;
} WAZA_Handou_Stream;
extern WAZA_Handou_Stream WAZA_Handou;

typedef struct lbl_804151FD_Stream {
    Seq_STATUS_GET16 command000;
    Seq_IF16 command001;
    Seq_CONDITION_CHECK command002;
    Seq_HITCHECK command003;
    Seq_LOOP_INIT command004;
    Seq_ADDVALUE command005;
    Seq_STATUS_SET8 command006;
    Seq_CRITICAL_CHECK command007;
    Seq_DAMAGE_CALC command008;
    Seq_TYPE_CHECK command009;
    Seq_DAMAGE_LOSS command010;
    Seq_STATUS_GET8 command011;
    Seq_IF8 command012;
    Seq_WAZA_EFFECT command013;
    Seq_EFFECT_WAIT command014;
    Seq_WAZAKOUKA_SE command015;
    Seq_POKE_BLINK command016;
    Seq_CLIENT_BIT_WAIT command017;
    Seq_HP_DEC command018;
    Seq_CRITICAL_MESSAGE command019;
    Seq_MESSAGE_WAIT command020;
    Seq_ADDVALUE command021;
    Seq_SETVALUE command022;
    Seq_STATUS_GET8 command023;
    Seq_IF8 command024;
    Seq_HP_CHECK command025;
    Seq_LOOP command026;
    Seq_JUMP command027;
    Seq_HP_DEC_WAIT command028;
    Seq_EFFECT_WAIT command029;
    Seq_SETVALUE command030;
    Seq_WKC_ACT command031;
    Seq_HP_CHECK command032;
    Seq_JUMP command033;
} lbl_804151FD_Stream;
extern lbl_804151FD_Stream lbl_804151FD;

typedef struct lbl_804152CC_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_IF8 command001;
    Seq_STATUS_SET16 command002;
} lbl_804152CC_Stream;
extern lbl_804152CC_Stream lbl_804152CC;

typedef struct lbl_804152F2_Stream {
    Seq_WAZAKOUKA_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_IF8 command002;
    Seq_STATUS_SET8 command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SETVALUE command008;
    Seq_WKC_ACT command009;
    Seq_TSUIKA_CHECK command010;
    Seq_KIZETSU_CHECK command011;
    Seq_SETVALUE command012;
    Seq_WKC_ACT command013;
    Seq_WAZAEND command014;
    Seq_SETVALUE command015;
    Seq_JUMP command016;
    Seq_BADGECHECK command017;
    Seq_ATTACK_MESSAGE command018;
    Seq_PP_DEC command019;
    Seq_HITCHECK command020;
    Seq_CONDITION2_CHECK command021;
    Seq_CONDITION2_CHECK command022;
    Seq_WAZA_EFFECT command023;
    Seq_SETVALUE command024;
    Seq_TSUIKA_DIRECT_ACT command025;
    Seq_MESSAGE command026;
    Seq_MESSAGE_WAIT command027;
    Seq_EFFECT_WAIT command028;
    Seq_JUMP command029;
    Seq_BADGECHECK command030;
    Seq_ATTACK_MESSAGE command031;
    Seq_PP_DEC command032;
    Seq_CONDITION2_CHECK command033;
    Seq_CONDITION2_CHECK command034;
    Seq_CONDITION_CHECK command035;
    Seq_JUMP command036;
    Seq_WAZA_EFFECT command037;
    Seq_EFFECT_WAIT command038;
    Seq_SETVALUE command039;
    Seq_TSUIKA_DIRECT_ACT command040;
    Seq_MESSAGE command041;
    Seq_MESSAGE_WAIT command042;
    Seq_EFFECT_WAIT command043;
    Seq_JUMP command044;
    Seq_BADGECHECK command045;
    Seq_CHIISAKUNARU command046;
    Seq_SETVALUE command047;
    Seq_JUMP command048;
    Seq_MONS_TYPE command049;
    Seq_BADGECHECK command050;
    Seq_ATTACK_MESSAGE command051;
    Seq_PP_DEC command052;
    Seq_CONDCHG_CHECK command053;
    Seq_CONDCHG_CHECK command054;
    Seq_CONDCHG_CHECK command055;
} lbl_804152F2_Stream;
extern lbl_804152F2_Stream lbl_804152F2;

typedef struct lbl_804153ED_Stream {
    Seq_STATUS_GET32 command000;
    Seq_STATUS_SET32 command001;
    Seq_SETVALUE command002;
    Seq_FIGHT_EFFECT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SETVALUE command005;
    Seq_CONDCHG command006;
    Seq_MESSAGE_TBL command007;
    Seq_WAIT command008;
} lbl_804153ED_Stream;
extern lbl_804153ED_Stream lbl_804153ED;

typedef struct lbl_80415438_Stream {
    Seq_SETVALUE command000;
    Seq_CONDCHG command001;
    Seq_MESSAGE_TBL command002;
    Seq_WAIT command003;
} lbl_80415438_Stream;
extern lbl_80415438_Stream lbl_80415438;

typedef struct lbl_8041544C_Stream {
    Seq_SETVALUE command000;
    Seq_CONDCHG command001;
    Seq_MESSAGE_TBL command002;
    Seq_WAIT command003;
} lbl_8041544C_Stream;
extern lbl_8041544C_Stream lbl_8041544C;

typedef struct lbl_80415460_Stream {
    Seq_MESSAGE_WAIT command000;
    Seq_EFFECT_WAIT command001;
    Seq_JUMP command002;
    Seq_STATUS_GET32 command003;
    Seq_STATUS_GET32 command004;
    Seq_IFWNE command005;
    Seq_SUBROUTINE_CALL command006;
} lbl_80415460_Stream;
extern lbl_80415460_Stream lbl_80415460;

typedef struct lbl_804154A3_Stream {
    Seq_BADGECHECK command000;
    Seq_ATTACK_MESSAGE command001;
    Seq_PP_DEC command002;
    Seq_CONDITION2_CHECK command003;
    Seq_HITCHECK command004;
    Seq_NOROI command005;
    Seq_SET32BIT command006;
    Seq_SETVALUE command007;
    Seq_WAZA_EFFECT command008;
    Seq_EFFECT_WAIT command009;
    Seq_HP_DEC command010;
    Seq_HP_DEC_WAIT command011;
    Seq_EFFECT_WAIT command012;
    Seq_WAZA_EFFECT command013;
    Seq_EFFECT_WAIT command014;
    Seq_MESSAGE command015;
    Seq_MESSAGE_WAIT command016;
    Seq_EFFECT_WAIT command017;
    Seq_KIZETSU_CHECK command018;
    Seq_JUMP command019;
    Seq_BADGECHECK command020;
    Seq_ATTACK_MESSAGE command021;
    Seq_PP_DEC command022;
    Seq_GUARD_SUCCESS_CHECK command023;
    Seq_WAZA_EFFECT command024;
    Seq_EFFECT_WAIT command025;
    Seq_MESSAGE_TBL command026;
    Seq_MESSAGE_WAIT command027;
    Seq_EFFECT_WAIT command028;
    Seq_JUMP command029;
    Seq_BADGECHECK command030;
    Seq_MAKIBISHI command031;
    Seq_ATTACK_MESSAGE command032;
    Seq_PP_DEC command033;
    Seq_WAZA_EFFECT command034;
    Seq_EFFECT_WAIT command035;
    Seq_MESSAGE command036;
    Seq_MESSAGE_WAIT command037;
    Seq_EFFECT_WAIT command038;
    Seq_JUMP command039;
    Seq_BADGECHECK command040;
    Seq_HITCHECK command041;
    Seq_ATTACK_MESSAGE command042;
    Seq_PP_DEC command043;
    Seq_MIYABURU command044;
    Seq_WAZA_EFFECT command045;
    Seq_EFFECT_WAIT command046;
    Seq_MESSAGE command047;
    Seq_MESSAGE_WAIT command048;
    Seq_EFFECT_WAIT command049;
    Seq_JUMP command050;
    Seq_BADGECHECK command051;
    Seq_ATTACK_MESSAGE command052;
    Seq_PP_DEC command053;
    Seq_HOROBINOUTA command054;
    Seq_WAZA_EFFECT command055;
    Seq_EFFECT_WAIT command056;
    Seq_MESSAGE command057;
    Seq_MESSAGE_WAIT command058;
    Seq_EFFECT_WAIT command059;
    Seq_SETVALUE command060;
    Seq_SETVALUE command061;
    Seq_STATUS_GET32 command062;
    Seq_IF32 command063;
    Seq_STATUS_GET8 command064;
    Seq_IF8 command065;
    Seq_STATUS_SET32 command066;
    Seq_STATUS_SET32 command067;
    Seq_SPEABI_CHECK command068;
    Seq_WAZA_EFFECT command069;
    Seq_EFFECT_WAIT command070;
} lbl_804154A3_Stream;
extern lbl_804154A3_Stream lbl_804154A3;

typedef struct lbl_804155CE_Stream {
    Seq_ADDVALUE command000;
    Seq_IFWNE command001;
    Seq_JUMP command002;
    Seq_FIGHT_EFFECT command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
    Seq_BADGECHECK command008;
    Seq_ATTACK_MESSAGE command009;
    Seq_PP_DEC command010;
    Seq_WEATHER_CHANGE command011;
    Seq_JUMP command012;
    Seq_BADGECHECK command013;
    Seq_ATTACK_MESSAGE command014;
    Seq_CONDITION2_CHECK command015;
    Seq_PP_DEC command016;
} lbl_804155CE_Stream;
extern lbl_804155CE_Stream lbl_804155CE;

typedef struct lbl_80415615_Stream {
    Seq_HITCHECK command000;
    Seq_TYPE_CHECK_NO_HIT command001;
    Seq_KOROGARU command002;
    Seq_JUMP command003;
    Seq_BADGECHECK command004;
    Seq_CONDITION2_CHECK command005;
    Seq_HITCHECK command006;
    Seq_ATTACK_MESSAGE command007;
    Seq_PP_DEC command008;
    Seq_IBARU command009;
    Seq_WAZA_EFFECT command010;
    Seq_EFFECT_WAIT command011;
    Seq_SETVALUE command012;
    Seq_CONDCHG command013;
    Seq_IF8 command014;
    Seq_COND_CHG_WORK_SET command015;
    Seq_FIGHT_EFFECT command016;
    Seq_EFFECT_WAIT command017;
    Seq_MESSAGE_TBL command018;
    Seq_MESSAGE_WAIT command019;
    Seq_EFFECT_WAIT command020;
} lbl_80415615_Stream;
extern lbl_80415615_Stream lbl_80415615;

typedef struct lbl_8041566B_Stream {
    Seq_SPEABI_CHECK command000;
    Seq_SIDECONDITION_CHECK command001;
    Seq_SETVALUE command002;
    Seq_TSUIKA_DIRECT_ACT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
    Seq_BADGECHECK command006;
    Seq_ATTACK_MESSAGE command007;
    Seq_PP_DEC command008;
    Seq_HITCHECK command009;
} lbl_8041566B_Stream;
extern lbl_8041566B_Stream lbl_8041566B;

typedef struct lbl_80415692_Stream {
    Seq_RENZOKUGIRI command000;
    Seq_CRITICAL_CHECK command001;
    Seq_DAMAGE_CALC command002;
    Seq_TYPE_CHECK command003;
    Seq_STATUS_GET8 command004;
    Seq_IF8 command005;
    Seq_DAMAGE_LOSS command006;
    Seq_JUMP command007;
    Seq_BADGECHECK command008;
    Seq_ATTACK_MESSAGE command009;
    Seq_PP_DEC command010;
    Seq_HITCHECK command011;
    Seq_MEROMERO command012;
    Seq_WAZA_EFFECT command013;
    Seq_EFFECT_WAIT command014;
    Seq_MESSAGE command015;
    Seq_MESSAGE_WAIT command016;
    Seq_EFFECT_WAIT command017;
    Seq_JUMP command018;
    Seq_BADGECHECK command019;
    Seq_HITCHECK command020;
    Seq_NATSUKI command021;
    Seq_JUMP command022;
    Seq_BADGECHECK command023;
    Seq_HITCHECK command024;
    Seq_ATTACK_MESSAGE command025;
    Seq_PP_DEC command026;
    Seq_TYPE_CHECK command027;
    Seq_PRESENT command028;
    Seq_BADGECHECK command029;
    Seq_ATTACK_MESSAGE command030;
    Seq_PP_DEC command031;
    Seq_SHINPINOMAMORI command032;
    Seq_JUMP command033;
    Seq_SETVALUE command034;
    Seq_JUMP command035;
    Seq_BADGECHECK command036;
    Seq_ATTACK_MESSAGE command037;
    Seq_PP_DEC command038;
    Seq_JISIN command039;
    Seq_MAGNITUDE command040;
    Seq_WAIT command041;
    Seq_MESSAGE command042;
    Seq_MESSAGE_WAIT command043;
    Seq_JUMP command044;
    Seq_BADGECHECK command045;
    Seq_ATTACK_MESSAGE command046;
    Seq_PP_DEC command047;
    Seq_RESHUFFLE_CHECK command048;
    Seq_WAZA_EFFECT command049;
    Seq_EFFECT_WAIT command050;
    Seq_SUBROUTINE_CALL command051;
    Seq_POKE_RESHUFFLE command052;
    Seq_SIZENKAIHUKU command053;
    Seq_CLIENT_BIT_WAIT command054;
    Seq_POKE_RESHUFFLE_WAIT command055;
    Seq_POKEDELACTOR command056;
    Seq_APPEAR_EFFECT_INIT command057;
    Seq_APPEAR_EFFECT command058;
    Seq_POKE_HPMAX_RATE command059;
    Seq_MESSAGE_TBL command060;
    Seq_APPEAR_EFFECT_WAIT command061;
    Seq_MESSAGE_WAIT command062;
    Seq_CLIENT_BIT_WAIT command063;
    Seq_POKE_RESHUFFLE_END command064;
    Seq_JUMP command065;
    Seq_SETVALUE command066;
    Seq_JUMP command067;
    Seq_BADGECHECK command068;
    Seq_HITCHECK command069;
    Seq_ATTACK_MESSAGE command070;
    Seq_PP_DEC command071;
    Seq_TYPE_CHECK command072;
    Seq_STATUS_SET16 command073;
    Seq_STATUS_SET16 command074;
    Seq_STATUS_SET32 command075;
    Seq_KORAERU_CHECK command076;
    Seq_JUMP command077;
    Seq_BADGECHECK command078;
    Seq_ATTACK_MESSAGE command079;
    Seq_PP_DEC command080;
    Seq_WEATHERKAIFUKU command081;
    Seq_JUMP command082;
    Seq_MEZAMERUPOWER command083;
    Seq_JUMP command084;
    Seq_BADGECHECK command085;
    Seq_ATTACK_MESSAGE command086;
    Seq_PP_DEC command087;
    Seq_WEATHER_CHANGE command088;
} lbl_80415692_Stream;
extern lbl_80415692_Stream lbl_80415692;

typedef struct lbl_804157C8_Stream {
    Seq_WAZA_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE_TBL command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_GOSUB command005;
    Seq_JUMP command006;
    Seq_BADGECHECK command007;
    Seq_ATTACK_MESSAGE command008;
    Seq_PP_DEC command009;
    Seq_WEATHER_CHANGE command010;
    Seq_JUMP command011;
    Seq_SETVALUE command012;
    Seq_SETVALUE command013;
    Seq_JUMP command014;
    Seq_SETVALUE command015;
    Seq_SETVALUE command016;
    Seq_JUMP command017;
    Seq_SETVALUE command018;
    Seq_JUMP command019;
    Seq_BADGECHECK command020;
    Seq_ATTACK_MESSAGE command021;
    Seq_PP_DEC command022;
    Seq_HARADAIKO command023;
    Seq_SET32BIT command024;
    Seq_WAZA_EFFECT command025;
    Seq_EFFECT_WAIT command026;
    Seq_HP_DEC command027;
    Seq_MESSAGE command028;
    Seq_MESSAGE_WAIT command029;
    Seq_HP_DEC_WAIT command030;
    Seq_EFFECT_WAIT command031;
    Seq_JUMP command032;
    Seq_BADGECHECK command033;
    Seq_ATTACK_MESSAGE command034;
    Seq_PP_DEC command035;
    Seq_JIKOANJI command036;
    Seq_WAZA_EFFECT command037;
    Seq_EFFECT_WAIT command038;
    Seq_MESSAGE command039;
    Seq_MESSAGE_WAIT command040;
    Seq_EFFECT_WAIT command041;
    Seq_JUMP command042;
    Seq_BADGECHECK command043;
    Seq_MIRRORCOAT command044;
    Seq_HITCHECK command045;
    Seq_ATTACK_MESSAGE command046;
    Seq_PP_DEC command047;
    Seq_TYPE_CHECK_NO_HIT command048;
    Seq_KORAERU_CHECK command049;
    Seq_JUMP command050;
    Seq_CONDITION2_CHECK command051;
    Seq_IF32 command052;
    Seq_SETVALUE command053;
    Seq_BADGECHECK command054;
    Seq_GOSUB command055;
    Seq_SETVALUE command056;
    Seq_CONDCHG command057;
    Seq_IF8 command058;
    Seq_COND_CHG_WORK_SET command059;
    Seq_FIGHT_EFFECT command060;
    Seq_EFFECT_WAIT command061;
    Seq_MESSAGE_TBL command062;
    Seq_MESSAGE_WAIT command063;
    Seq_EFFECT_WAIT command064;
    Seq_JUMP command065;
    Seq_WAZAKOUKA_CHECK command066;
    Seq_SET32BIT command067;
    Seq_SETVALUE command068;
    Seq_STATUS_SET8 command069;
    Seq_SETVALUE command070;
    Seq_JUMP command071;
    Seq_BADGECHECK command072;
    Seq_ATTACK_MESSAGE command073;
    Seq_PP_DEC command074;
    Seq_JISIN command075;
    Seq_LOOP_INIT command076;
    Seq_WAZAKOUKA_CHECK command077;
    Seq_SET32BIT command078;
    Seq_SETVALUE command079;
    Seq_STATUS_SET8 command080;
    Seq_JUMP command081;
    Seq_RESET32BIT command082;
    Seq_SETVALUE command083;
    Seq_STATUS_SET8 command084;
    Seq_HITCHECK command085;
    Seq_CRITICAL_CHECK command086;
    Seq_DAMAGE_CALC command087;
    Seq_TYPE_CHECK command088;
    Seq_DAMAGE_LOSS command089;
    Seq_WAZA_EFFECT command090;
    Seq_EFFECT_WAIT command091;
    Seq_WAZAKOUKA_SE command092;
    Seq_POKE_BLINK command093;
    Seq_CLIENT_BIT_WAIT command094;
    Seq_HP_DEC command095;
    Seq_CRITICAL_MESSAGE command096;
    Seq_MESSAGE_WAIT command097;
    Seq_WAZAKOUKA_MESSAGE command098;
    Seq_MESSAGE_WAIT command099;
    Seq_HP_DEC_WAIT command100;
    Seq_EFFECT_WAIT command101;
    Seq_KIZETSU_CHECK command102;
    Seq_SETVALUE command103;
    Seq_WKC_ACT command104;
    Seq_JIBAKU_LOOP command105;
    Seq_WAZAEND command106;
    Seq_WAIT command107;
    Seq_TYPE_CHECK command108;
    Seq_FIGHT_EFFECT command109;
    Seq_WAZAKOUKA_SE command110;
    Seq_WAZAKOUKA_MESSAGE command111;
    Seq_MESSAGE_WAIT command112;
    Seq_EFFECT_WAIT command113;
    Seq_SETVALUE command114;
    Seq_WKC_ACT command115;
    Seq_JIBAKU_LOOP command116;
    Seq_WAZAEND command117;
    Seq_BADGECHECK command118;
    Seq_ATTACK_MESSAGE command119;
    Seq_PP_DEC command120;
    Seq_MIRAIYOCHI command121;
    Seq_WAZA_EFFECT command122;
    Seq_EFFECT_WAIT command123;
    Seq_MESSAGE_TBL command124;
    Seq_MESSAGE_WAIT command125;
    Seq_EFFECT_WAIT command126;
    Seq_JUMP command127;
    Seq_WAZAKOUKA_CHECK command128;
    Seq_SET32BIT command129;
    Seq_SETVALUE command130;
    Seq_STATUS_SET8 command131;
    Seq_JUMP command132;
    Seq_WAZAKOUKA_CHECK command133;
    Seq_SETVALUE command134;
    Seq_STATUS_SET8 command135;
    Seq_JUMP command136;
    Seq_SETVALUE command137;
    Seq_STATUS_GET16 command138;
    Seq_IF16 command139;
    Seq_CONDITION2_CHECK command140;
    Seq_IF32 command141;
    Seq_SETVALUE command142;
    Seq_BADGECHECK command143;
    Seq_GOSUB command144;
    Seq_JUMP command145;
} lbl_804157C8_Stream;
extern lbl_804157C8_Stream lbl_804157C8;

typedef struct lbl_80415A75_Stream {
    Seq_BADGECHECK command000;
    Seq_SET32BIT command001;
    Seq_SETVALUE command002;
    Seq_TSUIKA_DIRECT_ACT command003;
    Seq_EFFECT_WAIT command004;
    Seq_PP_DEC command005;
    Seq_JUMP command006;
    Seq_SETVALUE command007;
    Seq_SET32BIT command008;
    Seq_JUMP command009;
    Seq_BADGECHECK command010;
    Seq_ATTACK_MESSAGE command011;
    Seq_PP_DEC command012;
    Seq_SUBROUTINE_CALL command013;
    Seq_IF8 command014;
    Seq_IF8 command015;
    Seq_TELEPORT command016;
    Seq_WAZA_EFFECT command017;
    Seq_EFFECT_WAIT command018;
    Seq_MESSAGE command019;
    Seq_MESSAGE_WAIT command020;
    Seq_EFFECT_WAIT command021;
    Seq_SEQEND command022;
    Seq_BADGECHECK command023;
    Seq_HITCHECK command024;
    Seq_ATTACK_MESSAGE command025;
    Seq_WAIT command026;
    Seq_PP_DEC command027;
    Seq_SETVALUE command028;
    Seq_LOOP_INIT command029;
    Seq_HUKURODATAKI command030;
    Seq_CRITICAL_CHECK command031;
    Seq_STATUS_GET8 command032;
    Seq_IF8 command033;
    Seq_DAMAGE_CHG command034;
    Seq_DAMAGE_LOSS command035;
    Seq_WAZA_EFFECT command036;
    Seq_EFFECT_WAIT command037;
    Seq_MESSAGE command038;
    Seq_EFFECT_WAIT command039;
    Seq_WAZAKOUKA_SE command040;
    Seq_POKE_BLINK command041;
    Seq_CLIENT_BIT_WAIT command042;
    Seq_HP_DEC command043;
    Seq_MESSAGE_WAIT command044;
    Seq_CRITICAL_MESSAGE command045;
    Seq_MESSAGE_WAIT command046;
    Seq_WAZAKOUKA_MESSAGE command047;
    Seq_MESSAGE_WAIT command048;
    Seq_HP_DEC_WAIT command049;
    Seq_EFFECT_WAIT command050;
    Seq_KIZETSU_CHECK command051;
    Seq_SETVALUE command052;
    Seq_WKC_ACT command053;
    Seq_JUMP command054;
    Seq_WAZAEND command055;
    Seq_CONDITION2_CHECK command056;
    Seq_IF32 command057;
    Seq_STATUS_GET16 command058;
    Seq_IF16 command059;
    Seq_IF16 command060;
    Seq_IF16 command061;
    Seq_SETVALUE command062;
    Seq_JUMP command063;
    Seq_SETVALUE command064;
    Seq_JUMP command065;
    Seq_SETVALUE command066;
    Seq_JUMP command067;
    Seq_SETVALUE command068;
} lbl_80415A75_Stream;
extern lbl_80415A75_Stream lbl_80415A75;

typedef struct lbl_80415BBD_Stream {
    Seq_BADGECHECK command000;
    Seq_GOSUB command001;
    Seq_KIERUTAME command002;
    Seq_JUMP command003;
} lbl_80415BBD_Stream;
extern lbl_80415BBD_Stream lbl_80415BBD;

typedef struct lbl_80415BC9_Stream {
    Seq_BADGECHECK command000;
    Seq_SETVALUE command001;
    Seq_SETVALUE command002;
    Seq_SAKUJO command003;
    Seq_SET32BIT command004;
    Seq_STATUS_GET16 command005;
    Seq_IF16 command006;
    Seq_SETVALUE command007;
    Seq_HITCHECK command008;
    Seq_KIERUTAME_AFTAR command009;
    Seq_JUMP command010;
} lbl_80415BC9_Stream;
extern lbl_80415BC9_Stream lbl_80415BC9;

typedef struct lbl_80415C14_Stream {
    Seq_KIERUTAME_AFTAR command000;
    Seq_JUMP command001;
    Seq_BADGECHECK command002;
    Seq_ATTACK_MESSAGE command003;
    Seq_PP_DEC command004;
    Seq_MARUKUNARU command005;
    Seq_SETVALUE command006;
    Seq_CONDCHG command007;
    Seq_IF8 command008;
    Seq_WAZA_EFFECT command009;
    Seq_EFFECT_WAIT command010;
    Seq_JUMP command011;
    Seq_BADGECHECK command012;
    Seq_ATTACK_MESSAGE command013;
    Seq_PP_DEC command014;
    Seq_KAIFUKU command015;
} lbl_80415C14_Stream;
extern lbl_80415C14_Stream lbl_80415C14;

typedef struct WAZA_Kaifuku_Stream {
    Seq_WAZA_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_EFFECT_WAIT command002;
    Seq_SET32BIT command003;
    Seq_HP_DEC command004;
    Seq_MESSAGE command005;
    Seq_MESSAGE_WAIT command006;
    Seq_HP_DEC_WAIT command007;
    Seq_EFFECT_WAIT command008;
    Seq_JUMP command009;
} WAZA_Kaifuku_Stream;
extern WAZA_Kaifuku_Stream WAZA_Kaifuku;

typedef struct WAZA_Mantan_Stream {
    Seq_WAIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
    Seq_BADGECHECK command006;
    Seq_NEKODAMASHI command007;
    Seq_SETVALUE command008;
    Seq_JUMP command009;
} WAZA_Mantan_Stream;
extern WAZA_Mantan_Stream WAZA_Mantan;

typedef struct lbl_80415C91_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_PP_DEC command001;
} lbl_80415C91_Stream;
extern lbl_80415C91_Stream lbl_80415C91;

typedef struct WAZA_Umakukimaran_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_STATUS_SET16 command001;
    Seq_WAZAKOUKA_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
    Seq_PP_DEC command006;
    Seq_FIGHT_EFFECT command007;
    Seq_JUMP command008;
} WAZA_Umakukimaran_Stream;
extern WAZA_Umakukimaran_Stream WAZA_Umakukimaran;

typedef struct lbl_80415CC6_Stream {
    Seq_WAIT command000;
    Seq_STATUS_SET16 command001;
    Seq_FIGHT_EFFECT command002;
    Seq_WAZAKOUKA_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
    Seq_BADGECHECK command007;
    Seq_HITCHECK command008;
    Seq_SETVALUE command009;
    Seq_ATTACK_MESSAGE command010;
    Seq_CONDITION2_CHECK command011;
    Seq_PP_DEC command012;
} lbl_80415CC6_Stream;
extern lbl_80415CC6_Stream lbl_80415CC6;

typedef struct lbl_80415D09_Stream {
    Seq_SAWAGU command000;
    Seq_JUMP command001;
    Seq_BADGECHECK command002;
    Seq_ATTACK_MESSAGE command003;
    Seq_PP_DEC command004;
    Seq_TAKUWAERU command005;
    Seq_WAZA_EFFECT command006;
    Seq_EFFECT_WAIT command007;
    Seq_MESSAGE_TBL command008;
    Seq_MESSAGE_WAIT command009;
    Seq_EFFECT_WAIT command010;
    Seq_JUMP command011;
    Seq_BADGECHECK command012;
    Seq_IF8 command013;
    Seq_ATTACK_MESSAGE command014;
    Seq_PP_DEC command015;
    Seq_HITCHECK command016;
    Seq_HAKIDASU command017;
    Seq_TYPE_CHECK command018;
    Seq_KORAERU_CHECK command019;
    Seq_JUMP command020;
    Seq_WAIT command021;
    Seq_FIGHT_EFFECT command022;
    Seq_MESSAGE command023;
    Seq_MESSAGE_WAIT command024;
    Seq_EFFECT_WAIT command025;
    Seq_JUMP command026;
    Seq_ATTACK_MESSAGE command027;
    Seq_PP_DEC command028;
    Seq_WAIT command029;
    Seq_HAKIDASU command030;
    Seq_FIGHT_EFFECT command031;
    Seq_WAZAKOUKA_MESSAGE command032;
    Seq_MESSAGE_WAIT command033;
    Seq_EFFECT_WAIT command034;
    Seq_JUMP command035;
    Seq_BADGECHECK command036;
    Seq_ATTACK_MESSAGE command037;
    Seq_PP_DEC command038;
    Seq_NOMIKOMU command039;
    Seq_JUMP command040;
    Seq_WAIT command041;
    Seq_FIGHT_EFFECT command042;
    Seq_MESSAGE_TBL command043;
    Seq_MESSAGE_WAIT command044;
    Seq_EFFECT_WAIT command045;
    Seq_JUMP command046;
    Seq_BADGECHECK command047;
    Seq_ATTACK_MESSAGE command048;
    Seq_PP_DEC command049;
    Seq_WEATHER_CHANGE command050;
    Seq_JUMP command051;
    Seq_BADGECHECK command052;
    Seq_ATTACK_MESSAGE command053;
    Seq_PP_DEC command054;
    Seq_HITCHECK command055;
    Seq_ICHAMON command056;
    Seq_WAZA_EFFECT command057;
    Seq_EFFECT_WAIT command058;
    Seq_MESSAGE command059;
    Seq_MESSAGE_WAIT command060;
    Seq_EFFECT_WAIT command061;
    Seq_JUMP command062;
    Seq_BADGECHECK command063;
    Seq_CONDITION2_CHECK command064;
    Seq_HITCHECK command065;
    Seq_ATTACK_MESSAGE command066;
    Seq_PP_DEC command067;
    Seq_IBARU command068;
    Seq_WAZA_EFFECT command069;
    Seq_EFFECT_WAIT command070;
    Seq_SETVALUE command071;
    Seq_CONDCHG command072;
    Seq_IF8 command073;
    Seq_COND_CHG_WORK_SET command074;
    Seq_FIGHT_EFFECT command075;
    Seq_EFFECT_WAIT command076;
    Seq_MESSAGE_TBL command077;
    Seq_MESSAGE_WAIT command078;
    Seq_EFFECT_WAIT command079;
    Seq_SPEABI_CHECK command080;
    Seq_SIDECONDITION_CHECK command081;
    Seq_SETVALUE command082;
    Seq_TSUIKA_DIRECT_ACT command083;
    Seq_EFFECT_WAIT command084;
    Seq_JUMP command085;
    Seq_BADGECHECK command086;
    Seq_ATTACK_MESSAGE command087;
    Seq_PP_DEC command088;
    Seq_CONDITION2_CHECK command089;
    Seq_CONDITION_CHECK command090;
    Seq_CHECK_TYPE command091;
    Seq_SPEABI_CHECK command092;
    Seq_CONDITION_CHECK command093;
    Seq_HITCHECK command094;
    Seq_SIDECONDITION_CHECK command095;
    Seq_WAZA_EFFECT command096;
    Seq_EFFECT_WAIT command097;
    Seq_SETVALUE command098;
    Seq_TSUIKA_DIRECT_ACT command099;
    Seq_EFFECT_WAIT command100;
    Seq_JUMP command101;
    Seq_STATUS_GET32 command102;
    Seq_STATUS_SET32 command103;
    Seq_SETVALUE command104;
    Seq_GOSUB command105;
    Seq_JUMP command106;
    Seq_WAIT command107;
    Seq_FIGHT_EFFECT command108;
    Seq_MESSAGE command109;
    Seq_MESSAGE_WAIT command110;
    Seq_EFFECT_WAIT command111;
    Seq_JUMP command112;
    Seq_BADGECHECK command113;
    Seq_IF8 command114;
    Seq_ATTACK_MESSAGE command115;
    Seq_PP_DEC command116;
    Seq_OKIMIYAGE command117;
    Seq_JIBAKU command118;
    Seq_WAZA_EFFECT command119;
    Seq_EFFECT_WAIT command120;
    Seq_CONDITION2_CHECK command121;
    Seq_SETVALUE command122;
    Seq_COND_CHG_BIT_CHECK command123;
    Seq_COND_CHG_BIT_CHECK command124;
    Seq_SETVALUE command125;
    Seq_CONDCHG command126;
    Seq_IF8 command127;
    Seq_MESSAGE_TBL command128;
    Seq_WAIT command129;
} lbl_80415D09_Stream;
extern lbl_80415D09_Stream lbl_80415D09;

typedef struct lbl_80415F20_Stream {
    Seq_COND_CHG_BIT_CHECK command000;
    Seq_SETVALUE command001;
    Seq_CONDCHG command002;
    Seq_IF8 command003;
    Seq_MESSAGE_TBL command004;
    Seq_WAIT command005;
} lbl_80415F20_Stream;
extern lbl_80415F20_Stream lbl_80415F20;

typedef struct lbl_80415F43_Stream {
    Seq_MESSAGE_WAIT command000;
    Seq_KIZETSU_CHECK command001;
    Seq_JUMP command002;
    Seq_FIGHT_EFFECT command003;
    Seq_EFFECT_WAIT command004;
    Seq_MESSAGE command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_JUMP command008;
    Seq_ATTACK_MESSAGE command009;
    Seq_PP_DEC command010;
    Seq_OKIMIYAGE command011;
    Seq_JIBAKU command012;
    Seq_WAIT command013;
    Seq_FIGHT_EFFECT command014;
    Seq_WAZAKOUKA_SE command015;
    Seq_WAZAKOUKA_MESSAGE command016;
    Seq_MESSAGE_WAIT command017;
    Seq_EFFECT_WAIT command018;
    Seq_KIZETSU_CHECK command019;
    Seq_JUMP command020;
    Seq_CONDITION_CHECK command021;
    Seq_JUMP command022;
    Seq_SETVALUE command023;
    Seq_STATUS_SET8 command024;
    Seq_JUMP command025;
    Seq_BADGECHECK command026;
    Seq_KIAIPUNCH command027;
    Seq_PP_DEC command028;
    Seq_FIGHT_EFFECT command029;
    Seq_MESSAGE command030;
    Seq_MESSAGE_WAIT command031;
    Seq_EFFECT_WAIT command032;
    Seq_JUMP command033;
    Seq_CONDITION2_CHECK command034;
    Seq_SETVALUE command035;
    Seq_CONDITION_CHECK command036;
    Seq_JUMP command037;
} lbl_80415F43_Stream;
extern lbl_80415F43_Stream lbl_80415F43;

typedef struct lbl_80415FF9_Stream {
    Seq_SETVALUE command000;
    Seq_STATUS_SET8 command001;
    Seq_JUMP command002;
    Seq_BADGECHECK command003;
    Seq_ATTACK_MESSAGE command004;
    Seq_PP_DEC command005;
    Seq_KONOYUBITOMARE command006;
    Seq_WAZA_EFFECT command007;
    Seq_EFFECT_WAIT command008;
    Seq_MESSAGE command009;
    Seq_MESSAGE_WAIT command010;
    Seq_EFFECT_WAIT command011;
    Seq_JUMP command012;
    Seq_BADGECHECK command013;
    Seq_ATTACK_MESSAGE command014;
    Seq_WAIT command015;
    Seq_SHIZENNOCHIKARA command016;
} lbl_80415FF9_Stream;
extern lbl_80415FF9_Stream lbl_80415FF9;

typedef struct WAZA_ShizennochikaraHitMsg_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_SEQRET command004;
    Seq_BADGECHECK command005;
    Seq_ATTACK_MESSAGE command006;
    Seq_PP_DEC command007;
    Seq_JUUDEN command008;
    Seq_WAZA_EFFECT command009;
    Seq_EFFECT_WAIT command010;
    Seq_MESSAGE command011;
    Seq_MESSAGE_WAIT command012;
    Seq_EFFECT_WAIT command013;
    Seq_JUMP command014;
    Seq_BADGECHECK command015;
    Seq_ATTACK_MESSAGE command016;
    Seq_PP_DEC command017;
    Seq_HITCHECK command018;
    Seq_CHOUHATSU command019;
    Seq_WAZA_EFFECT command020;
    Seq_EFFECT_WAIT command021;
    Seq_MESSAGE command022;
    Seq_MESSAGE_WAIT command023;
    Seq_EFFECT_WAIT command024;
    Seq_JUMP command025;
    Seq_BADGECHECK command026;
    Seq_ATTACK_MESSAGE command027;
    Seq_PP_DEC command028;
    Seq_TEDASUKE command029;
    Seq_WAZA_EFFECT command030;
    Seq_EFFECT_WAIT command031;
    Seq_MESSAGE command032;
    Seq_MESSAGE_WAIT command033;
    Seq_EFFECT_WAIT command034;
    Seq_JUMP command035;
    Seq_BADGECHECK command036;
    Seq_ATTACK_MESSAGE command037;
    Seq_PP_DEC command038;
    Seq_CONDITION2_CHECK command039;
    Seq_HITCHECK command040;
    Seq_TRICK command041;
    Seq_WAZA_EFFECT command042;
    Seq_EFFECT_WAIT command043;
    Seq_WAZA_EFFECT command044;
    Seq_EFFECT_WAIT command045;
    Seq_MESSAGE command046;
    Seq_MESSAGE_WAIT command047;
    Seq_EFFECT_WAIT command048;
    Seq_IF8 command049;
    Seq_IF8 command050;
    Seq_IF8 command051;
    Seq_JUMP command052;
    Seq_FIGHT_EFFECT command053;
    Seq_MESSAGE command054;
    Seq_MESSAGE_WAIT command055;
    Seq_EFFECT_WAIT command056;
    Seq_FIGHT_EFFECT command057;
    Seq_MESSAGE command058;
    Seq_MESSAGE_WAIT command059;
    Seq_EFFECT_WAIT command060;
    Seq_JUMP command061;
    Seq_FIGHT_EFFECT command062;
    Seq_MESSAGE command063;
    Seq_MESSAGE_WAIT command064;
    Seq_EFFECT_WAIT command065;
    Seq_JUMP command066;
    Seq_FIGHT_EFFECT command067;
    Seq_MESSAGE command068;
    Seq_MESSAGE_WAIT command069;
    Seq_EFFECT_WAIT command070;
    Seq_JUMP command071;
    Seq_JUMP command072;
    Seq_BADGECHECK command073;
    Seq_ATTACK_MESSAGE command074;
    Seq_PP_DEC command075;
    Seq_HITCHECK command076;
    Seq_NARIKIRI command077;
    Seq_WAZA_EFFECT command078;
    Seq_EFFECT_WAIT command079;
    Seq_MESSAGE command080;
    Seq_MESSAGE_WAIT command081;
    Seq_EFFECT_WAIT command082;
    Seq_JUMP command083;
    Seq_BADGECHECK command084;
    Seq_ATTACK_MESSAGE command085;
    Seq_PP_DEC command086;
    Seq_NEGAIGOTO command087;
    Seq_WAZA_EFFECT command088;
    Seq_EFFECT_WAIT command089;
    Seq_JUMP command090;
    Seq_BADGECHECK command091;
    Seq_ATTACK_MESSAGE command092;
    Seq_NEKONOTE command093;
    Seq_WAZA_EFFECT command094;
    Seq_EFFECT_WAIT command095;
    Seq_SETVALUE command096;
    Seq_SETVALUE command097;
    Seq_WAZASEQADRS command098;
    Seq_BADGECHECK command099;
    Seq_ATTACK_MESSAGE command100;
    Seq_PP_DEC command101;
    Seq_NEWOHARU command102;
    Seq_WAZA_EFFECT command103;
    Seq_EFFECT_WAIT command104;
    Seq_MESSAGE command105;
    Seq_MESSAGE_WAIT command106;
    Seq_EFFECT_WAIT command107;
    Seq_JUMP command108;
    Seq_SETVALUE command109;
    Seq_JUMP command110;
    Seq_BADGECHECK command111;
    Seq_MAGICCORT command112;
    Seq_ATTACK_MESSAGE command113;
    Seq_PP_DEC command114;
    Seq_WAZA_EFFECT command115;
    Seq_EFFECT_WAIT command116;
    Seq_MESSAGE command117;
    Seq_MESSAGE_WAIT command118;
    Seq_EFFECT_WAIT command119;
    Seq_JUMP command120;
    Seq_BADGECHECK command121;
    Seq_ATTACK_MESSAGE command122;
    Seq_PP_DEC command123;
    Seq_RECYCLE command124;
    Seq_WAZA_EFFECT command125;
    Seq_EFFECT_WAIT command126;
    Seq_MESSAGE command127;
    Seq_MESSAGE_WAIT command128;
    Seq_EFFECT_WAIT command129;
    Seq_JUMP command130;
    Seq_REVENGE command131;
    Seq_JUMP command132;
    Seq_BADGECHECK command133;
    Seq_HITCHECK command134;
    Seq_ATTACK_MESSAGE command135;
    Seq_PP_DEC command136;
    Seq_KAWARAWARI command137;
    Seq_CRITICAL_CHECK command138;
    Seq_DAMAGE_CALC command139;
    Seq_TYPE_CHECK command140;
    Seq_DAMAGE_LOSS command141;
    Seq_IF8 command142;
    Seq_STATUS_SET16 command143;
    Seq_STATUS_SET16 command144;
    Seq_WAZA_EFFECT command145;
    Seq_EFFECT_WAIT command146;
    Seq_IF8 command147;
    Seq_MESSAGE command148;
    Seq_MESSAGE_WAIT command149;
    Seq_TYPE_CHECK_NO_HIT command150;
    Seq_WAZAKOUKA_SE command151;
    Seq_POKE_BLINK command152;
    Seq_CLIENT_BIT_WAIT command153;
    Seq_HP_DEC command154;
    Seq_CRITICAL_MESSAGE command155;
    Seq_MESSAGE_WAIT command156;
    Seq_WAZAKOUKA_MESSAGE command157;
    Seq_MESSAGE_WAIT command158;
    Seq_HP_DEC_WAIT command159;
    Seq_EFFECT_WAIT command160;
    Seq_TSUIKA_CHECK command161;
    Seq_KIZETSU_CHECK command162;
    Seq_JUMP command163;
    Seq_BADGECHECK command164;
    Seq_ATTACK_MESSAGE command165;
    Seq_PP_DEC command166;
    Seq_SPEABI_CHECK command167;
    Seq_SPEABI_CHECK command168;
    Seq_CONDITION2_CHECK command169;
    Seq_SIDECONDITION_CHECK command170;
    Seq_HITCHECK command171;
    Seq_SAWAGU_CHECK command172;
    Seq_AKUBI command173;
    Seq_WAZA_EFFECT command174;
    Seq_EFFECT_WAIT command175;
    Seq_MESSAGE command176;
    Seq_MESSAGE_WAIT command177;
    Seq_EFFECT_WAIT command178;
    Seq_JUMP command179;
} WAZA_ShizennochikaraHitMsg_Stream;
extern WAZA_ShizennochikaraHitMsg_Stream WAZA_ShizennochikaraHitMsg;

typedef struct lbl_804162A5_Stream {
    Seq_STATUS_GET32 command000;
    Seq_STATUS_SET32 command001;
    Seq_WAIT command002;
    Seq_FIGHT_EFFECT command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
    Seq_SETVALUE command008;
    Seq_JUMP command009;
    Seq_BADGECHECK command010;
    Seq_ATTACK_MESSAGE command011;
    Seq_PP_DEC command012;
    Seq_GAMUSYARA command013;
    Seq_STATUS_GET32 command014;
    Seq_STATUS_SET32 command015;
    Seq_HITCHECK command016;
    Seq_TYPE_CHECK command017;
    Seq_STATUS_GET8 command018;
    Seq_IF8 command019;
    Seq_STATUS_SET16 command020;
    Seq_STATUS_SET16 command021;
    Seq_STATUS_GET32 command022;
    Seq_STATUS_SET32 command023;
    Seq_KORAERU_CHECK command024;
    Seq_JUMP command025;
    Seq_HUNKA command026;
    Seq_JUMP command027;
    Seq_BADGECHECK command028;
    Seq_ATTACK_MESSAGE command029;
    Seq_PP_DEC command030;
    Seq_HITCHECK command031;
    Seq_SKILLSWAP command032;
    Seq_WAZA_EFFECT command033;
    Seq_EFFECT_WAIT command034;
    Seq_WAZA_EFFECT command035;
    Seq_EFFECT_WAIT command036;
    Seq_MESSAGE command037;
    Seq_MESSAGE_WAIT command038;
    Seq_EFFECT_WAIT command039;
    Seq_JUMP command040;
    Seq_BADGECHECK command041;
    Seq_ATTACK_MESSAGE command042;
    Seq_PP_DEC command043;
    Seq_HUUIN command044;
    Seq_WAZA_EFFECT command045;
    Seq_EFFECT_WAIT command046;
    Seq_MESSAGE command047;
    Seq_MESSAGE_WAIT command048;
    Seq_EFFECT_WAIT command049;
    Seq_JUMP command050;
    Seq_BADGECHECK command051;
    Seq_ATTACK_MESSAGE command052;
    Seq_PP_DEC command053;
    Seq_REFLESH command054;
    Seq_WAZA_EFFECT command055;
    Seq_EFFECT_WAIT command056;
    Seq_MESSAGE command057;
    Seq_MESSAGE_WAIT command058;
    Seq_CONDITION_GAUGE command059;
    Seq_EFFECT_WAIT command060;
    Seq_JUMP command061;
    Seq_BADGECHECK command062;
    Seq_ATTACK_MESSAGE command063;
    Seq_PP_DEC command064;
    Seq_ONNEN command065;
    Seq_WAZA_EFFECT command066;
    Seq_EFFECT_WAIT command067;
    Seq_MESSAGE command068;
    Seq_MESSAGE_WAIT command069;
    Seq_EFFECT_WAIT command070;
    Seq_JUMP command071;
    Seq_BADGECHECK command072;
    Seq_YOKODORI command073;
    Seq_ATTACK_MESSAGE command074;
    Seq_PP_DEC command075;
    Seq_WAZA_EFFECT command076;
    Seq_EFFECT_WAIT command077;
    Seq_WAIT command078;
    Seq_MESSAGE command079;
    Seq_MESSAGE_WAIT command080;
    Seq_EFFECT_WAIT command081;
    Seq_JUMP command082;
    Seq_BADGECHECK command083;
    Seq_ATTACK_MESSAGE command084;
    Seq_PP_DEC command085;
    Seq_KETAGURI command086;
    Seq_HITCHECK command087;
    Seq_JUMP command088;
    Seq_HIMITUNOTIKARA command089;
    Seq_JUMP command090;
    Seq_SETVALUE command091;
    Seq_JUMP command092;
    Seq_BADGECHECK command093;
    Seq_ATTACK_MESSAGE command094;
    Seq_PP_DEC command095;
    Seq_SETVALUE command096;
    Seq_SETVALUE command097;
    Seq_LOOP_INIT command098;
    Seq_SETVALUE command099;
    Seq_STATUS_GET32 command100;
    Seq_IF32 command101;
    Seq_STATUS_GET8 command102;
    Seq_IF8 command103;
    Seq_STATUS_GET32 command104;
    Seq_IFWEQ command105;
    Seq_STATUS_SET32 command106;
    Seq_SPEABI_CHECK command107;
    Seq_CONDITION2_CHECK command108;
    Seq_CONDITION2_CHECK command109;
    Seq_HP_CHECK command110;
    Seq_HITCHECK command111;
    Seq_SIDECONDITION_CHECK command112;
    Seq_WAZA_EFFECT command113;
    Seq_EFFECT_WAIT command114;
    Seq_TSUIKA_DIRECT_ACT command115;
    Seq_WAZAKOUKA_MESSAGE command116;
    Seq_MESSAGE_WAIT command117;
    Seq_EFFECT_WAIT command118;
} lbl_804162A5_Stream;
extern lbl_804162A5_Stream lbl_804162A5;

typedef struct lbl_8041651D_Stream {
    Seq_SETVALUE command000;
    Seq_WKC_ACT command001;
} lbl_8041651D_Stream;
extern lbl_8041651D_Stream lbl_8041651D;

typedef struct lbl_80416526_Stream {
    Seq_ADDVALUE command000;
    Seq_IFWNE command001;
    Seq_WAZAEND command002;
    Seq_WAIT command003;
    Seq_FIGHT_EFFECT command004;
    Seq_MESSAGE command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_JUMP command008;
    Seq_WAIT command009;
    Seq_FIGHT_EFFECT command010;
    Seq_MESSAGE command011;
    Seq_MESSAGE_WAIT command012;
    Seq_EFFECT_WAIT command013;
    Seq_JUMP command014;
} lbl_80416526_Stream;
extern lbl_80416526_Stream lbl_80416526;

typedef struct lbl_8041656D_Stream {
    Seq_WAIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
    Seq_WAIT command006;
    Seq_FIGHT_EFFECT command007;
    Seq_MESSAGE command008;
    Seq_MESSAGE_WAIT command009;
    Seq_EFFECT_WAIT command010;
    Seq_JUMP command011;
    Seq_FIGHT_EFFECT command012;
    Seq_WAZAKOUKA_MESSAGE command013;
    Seq_MESSAGE_WAIT command014;
    Seq_EFFECT_WAIT command015;
    Seq_JUMP command016;
    Seq_BADGECHECK command017;
    Seq_ATTACK_MESSAGE command018;
    Seq_PP_DEC command019;
    Seq_ASOBI command020;
    Seq_WAZA_EFFECT command021;
    Seq_EFFECT_WAIT command022;
    Seq_MESSAGE_TBL command023;
    Seq_MESSAGE_WAIT command024;
    Seq_EFFECT_WAIT command025;
    Seq_JUMP command026;
    Seq_SETVALUE command027;
    Seq_JUMP command028;
    Seq_WEATHER_BALL command029;
    Seq_JUMP command030;
    Seq_SETVALUE command031;
    Seq_JUMP command032;
    Seq_BADGECHECK command033;
    Seq_ATTACK_MESSAGE command034;
    Seq_PP_DEC command035;
    Seq_CONDCHG_CHECK command036;
    Seq_CONDCHG_CHECK command037;
    Seq_HITCHECK command038;
    Seq_WAZA_EFFECT command039;
    Seq_EFFECT_WAIT command040;
    Seq_SETVALUE command041;
    Seq_COND_CHG_BIT_CHECK command042;
    Seq_COND_CHG_BIT_CHECK command043;
    Seq_SETVALUE command044;
    Seq_CONDCHG command045;
    Seq_IF8 command046;
    Seq_MESSAGE_TBL command047;
    Seq_WAIT command048;
} lbl_8041656D_Stream;
extern lbl_8041656D_Stream lbl_8041656D;

typedef struct lbl_80416633_Stream {
    Seq_COND_CHG_BIT_CHECK command000;
    Seq_SETVALUE command001;
    Seq_CONDCHG command002;
    Seq_IF8 command003;
    Seq_MESSAGE_TBL command004;
    Seq_WAIT command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_JUMP command008;
} lbl_80416633_Stream;
extern lbl_80416633_Stream lbl_80416633;

typedef struct lbl_80416660_Stream {
    Seq_WAIT command000;
    Seq_STATUS_SET16 command001;
    Seq_FIGHT_EFFECT command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
    Seq_BADGECHECK command007;
    Seq_ATTACK_MESSAGE command008;
    Seq_PP_DEC command009;
    Seq_CONDCHG_CHECK command010;
    Seq_CONDCHG_CHECK command011;
    Seq_WAZA_EFFECT command012;
    Seq_EFFECT_WAIT command013;
    Seq_SETVALUE command014;
    Seq_COND_CHG_BIT_CHECK command015;
    Seq_SETVALUE command016;
    Seq_CONDCHG command017;
    Seq_IF8 command018;
    Seq_MESSAGE_TBL command019;
    Seq_WAIT command020;
    Seq_SETVALUE command021;
    Seq_CONDCHG command022;
    Seq_IF8 command023;
    Seq_MESSAGE_TBL command024;
    Seq_WAIT command025;
    Seq_MESSAGE_WAIT command026;
    Seq_EFFECT_WAIT command027;
    Seq_JUMP command028;
    Seq_SET32BIT command029;
    Seq_JUMP command030;
    Seq_BADGECHECK command031;
    Seq_ATTACK_MESSAGE command032;
    Seq_PP_DEC command033;
    Seq_CONDCHG_CHECK command034;
    Seq_CONDCHG_CHECK command035;
    Seq_WAZA_EFFECT command036;
    Seq_EFFECT_WAIT command037;
    Seq_SETVALUE command038;
    Seq_COND_CHG_BIT_CHECK command039;
    Seq_SETVALUE command040;
    Seq_CONDCHG command041;
    Seq_IF8 command042;
    Seq_MESSAGE_TBL command043;
    Seq_WAIT command044;
    Seq_SETVALUE command045;
    Seq_CONDCHG command046;
    Seq_IF8 command047;
    Seq_MESSAGE_TBL command048;
    Seq_WAIT command049;
    Seq_MESSAGE_WAIT command050;
    Seq_EFFECT_WAIT command051;
    Seq_JUMP command052;
    Seq_BADGECHECK command053;
    Seq_ATTACK_MESSAGE command054;
    Seq_PP_DEC command055;
    Seq_CONDCHG_CHECK command056;
    Seq_CONDCHG_CHECK command057;
    Seq_WAZA_EFFECT command058;
    Seq_EFFECT_WAIT command059;
    Seq_SETVALUE command060;
    Seq_COND_CHG_BIT_CHECK command061;
    Seq_SETVALUE command062;
    Seq_CONDCHG command063;
    Seq_IF8 command064;
    Seq_MESSAGE_TBL command065;
    Seq_WAIT command066;
} lbl_80416660_Stream;
extern lbl_80416660_Stream lbl_80416660;

typedef struct lbl_804167B0_Stream {
    Seq_SETVALUE command000;
    Seq_CONDCHG command001;
    Seq_IF8 command002;
    Seq_MESSAGE_TBL command003;
    Seq_WAIT command004;
} lbl_804167B0_Stream;
extern lbl_804167B0_Stream lbl_804167B0;

typedef struct lbl_804167CF_Stream {
    Seq_MESSAGE_WAIT command000;
    Seq_EFFECT_WAIT command001;
    Seq_JUMP command002;
} lbl_804167CF_Stream;
extern lbl_804167CF_Stream lbl_804167CF;

typedef struct lbl_804167D9_Stream {
    Seq_WAIT command000;
    Seq_STATUS_SET16 command001;
    Seq_FIGHT_EFFECT command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
    Seq_BADGECHECK command007;
    Seq_ATTACK_MESSAGE command008;
    Seq_PP_DEC command009;
    Seq_CONDCHG_CHECK command010;
    Seq_CONDCHG_CHECK command011;
    Seq_WAZA_EFFECT command012;
    Seq_EFFECT_WAIT command013;
    Seq_SETVALUE command014;
    Seq_COND_CHG_BIT_CHECK command015;
    Seq_SETVALUE command016;
    Seq_CONDCHG command017;
    Seq_IF8 command018;
    Seq_MESSAGE_TBL command019;
    Seq_WAIT command020;
} lbl_804167D9_Stream;
extern lbl_804167D9_Stream lbl_804167D9;

typedef struct lbl_80416847_Stream {
    Seq_SETVALUE command000;
    Seq_CONDCHG command001;
    Seq_IF8 command002;
    Seq_MESSAGE_TBL command003;
    Seq_WAIT command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
    Seq_BADGECHECK command008;
    Seq_ATTACK_MESSAGE command009;
    Seq_PP_DEC command010;
    Seq_HOGOSYOKU command011;
    Seq_WAZA_EFFECT command012;
    Seq_EFFECT_WAIT command013;
    Seq_MESSAGE command014;
    Seq_MESSAGE_WAIT command015;
    Seq_EFFECT_WAIT command016;
    Seq_JUMP command017;
    Seq_SETVALUE command018;
    Seq_JUMP command019;
    Seq_BADGECHECK command020;
    Seq_ATTACK_MESSAGE command021;
    Seq_PP_DEC command022;
    Seq_WEATHER_CHANGE command023;
    Seq_JUMP command024;
    Seq_BADGECHECK command025;
    Seq_ATTACK_MESSAGE command026;
    Seq_PP_DEC command027;
    Seq_DARKREMOVE command028;
    Seq_WAZA_EFFECT command029;
    Seq_MESSAGE_TBL command030;
    Seq_MESSAGE_WAIT command031;
    Seq_EFFECT_WAIT command032;
    Seq_SEQEND command033;
    Seq_BADGECHECK command034;
    Seq_ATTACK_MESSAGE command035;
    Seq_PP_DEC command036;
    Seq_JIBAKU_INIT command037;
    Seq_LOOP_INIT command038;
    Seq_TYPE_CHECK command039;
    Seq_STATUS_SET16 command040;
    Seq_STATUS_SET16 command041;
    Seq_HPHALF command042;
    Seq_SETVALUE command043;
    Seq_HITCHECK command044;
    Seq_WAZA_EFFECT command045;
    Seq_EFFECT_WAIT command046;
    Seq_WAZAKOUKA_SE command047;
    Seq_POKE_BLINK command048;
    Seq_CLIENT_BIT_WAIT command049;
    Seq_HP_DEC command050;
    Seq_CRITICAL_MESSAGE command051;
    Seq_MESSAGE_WAIT command052;
    Seq_WAZAKOUKA_MESSAGE command053;
    Seq_MESSAGE_WAIT command054;
    Seq_HP_DEC_WAIT command055;
    Seq_EFFECT_WAIT command056;
    Seq_KIZETSU_CHECK command057;
    Seq_SETVALUE command058;
    Seq_WKC_ACT command059;
    Seq_JIBAKU_LOOP command060;
    Seq_KIZETSU_CHECK command061;
    Seq_TSUIKA_CHECK command062;
    Seq_WAZAEND command063;
    Seq_FIGHT_EFFECT command064;
    Seq_WAZAKOUKA_SE command065;
    Seq_WAZAKOUKA_MESSAGE command066;
    Seq_MESSAGE_WAIT command067;
    Seq_EFFECT_WAIT command068;
    Seq_SETVALUE command069;
    Seq_WKC_ACT command070;
    Seq_JIBAKU_LOOP command071;
    Seq_KIZETSU_CHECK command072;
    Seq_TSUIKA_CHECK command073;
    Seq_WAZAEND command074;
} lbl_80416847_Stream;
extern lbl_80416847_Stream lbl_80416847;

typedef struct WAZA_KizetsuA_Stream {
    Seq_KIZETSU command000;
    Seq_VOICE command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_KIZETSU_WAIT command004;
    Seq_SEQRET command005;
} WAZA_KizetsuA_Stream;
extern WAZA_KizetsuA_Stream WAZA_KizetsuA;

typedef struct WAZA_KizetsuD_Stream {
    Seq_KIZETSU command000;
    Seq_VOICE command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_KIZETSU_WAIT command004;
    Seq_SEQRET command005;
} WAZA_KizetsuD_Stream;
extern WAZA_KizetsuD_Stream WAZA_KizetsuD;

typedef struct WAZA_KizetsuK_Stream {
    Seq_KIZETSU command000;
    Seq_VOICE command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_KIZETSU_WAIT command004;
    Seq_SEQRET command005;
} WAZA_KizetsuK_Stream;
extern WAZA_KizetsuK_Stream WAZA_KizetsuK;

typedef struct WAZA_GetEXP_Stream {
    Seq_GET_EXP command000;
    Seq_SEQEND command001;
} WAZA_GetEXP_Stream;
extern WAZA_GetEXP_Stream WAZA_GetEXP;

typedef struct WAZA_LevelUp_Stream {
    Seq_ME_PLAY command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_STATUS_WINDOW command003;
    Seq_WAZAOBOE_CHECK command004;
    Seq_JUMP command005;
    Seq_WAZAOBOE_CHECK command006;
    Seq_OBOEWAZANO_SET command007;
    Seq_MESSAGE command008;
    Seq_MESSAGE command009;
    Seq_MESSAGE command010;
    Seq_CLIENT_BIT_WAIT command011;
    Seq_WAZAWASURE_CHECK command012;
    Seq_MESSAGE command013;
    Seq_CLIENT_BIT_WAIT command014;
    Seq_WAZAAKIRAME_CHECK command015;
    Seq_MESSAGE command016;
    Seq_JUMP command017;
    Seq_MESSAGE command018;
    Seq_MESSAGE command019;
    Seq_MESSAGE command020;
} WAZA_LevelUp_Stream;
extern WAZA_LevelUp_Stream WAZA_LevelUp;

typedef struct lbl_804169D6_Stream {
    Seq_OBOEWAZANO_SET command000;
    Seq_ME_PLAY command001;
    Seq_MESSAGE command002;
    Seq_SUBROUTINE_CALL command003;
    Seq_JUMP command004;
} lbl_804169D6_Stream;
extern lbl_804169D6_Stream lbl_804169D6;

typedef struct lbl_804169E7_Stream {
    Seq_MESSAGE_WAIT command000;
    Seq_SEQRET command001;
} lbl_804169E7_Stream;
extern lbl_804169E7_Stream lbl_804169E7;

typedef struct WAZA_Zenmetsu_Stream {
    Seq_ZENMETSU_CHECK command000;
    Seq_SEQEND command001;
} WAZA_Zenmetsu_Stream;
extern WAZA_Zenmetsu_Stream WAZA_Zenmetsu;

typedef struct WAZA_MineReshuffleStart_Stream {
    Seq_POKE_RESHUFFLE command000;
    Seq_POKE_RESHUFFLE_WAIT command001;
    Seq_BALL_GAUGE_SET command002;
    Seq_APPEAR_EFFECT_INIT command003;
    Seq_APPEAR_EFFECT command004;
    Seq_POKE_HPMAX_RATE command005;
    Seq_MESSAGE_TBL command006;
    Seq_BALL_GAUGE_OFF command007;
    Seq_APPEAR_EFFECT_WAIT command008;
    Seq_MESSAGE_WAIT command009;
    Seq_POKE_RESHUFFLE_END command010;
    Seq_STATUS_GET16 command011;
    Seq_IF16 command012;
    Seq_STATUS_GET16 command013;
    Seq_IF16 command014;
    Seq_SCA_END_SET command015;
} WAZA_MineReshuffleStart_Stream;
extern WAZA_MineReshuffleStart_Stream WAZA_MineReshuffleStart;

typedef struct WAZA_ZenmetsuEnd_Stream {
    Seq_SEQEND command000;
} WAZA_ZenmetsuEnd_Stream;
extern WAZA_ZenmetsuEnd_Stream WAZA_ZenmetsuEnd;

typedef struct WAZA_OkodukaiCheck_Stream {
    Seq_OKODUKAI_CALC command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_SEQEND command003;
} WAZA_OkodukaiCheck_Stream;
extern WAZA_OkodukaiCheck_Stream WAZA_OkodukaiCheck;

typedef struct WAZA_KobanCheck_Stream {
    Seq_KOBAN_CHECK command000;
    Seq_SEQEND command001;
} WAZA_KobanCheck_Stream;
extern WAZA_KobanCheck_Stream WAZA_KobanCheck;

typedef struct WAZA_TrainerWin_Stream {
    Seq_MESSAGE command000;
    Seq_TRAINER_APPEAR command001;
    Seq_CLIENT_BIT_WAIT command002;
    Seq_MESSAGE command003;
    Seq_OKODUKAI_CALC command004;
    Seq_MESSAGE command005;
    Seq_MESSAGE_WAIT command006;
} WAZA_TrainerWin_Stream;
extern WAZA_TrainerWin_Stream WAZA_TrainerWin;

typedef struct WAZA_Win_Stream {
    Seq_KOBAN_CHECK command000;
    Seq_MONOHIROI command001;
    Seq_SEQEND command002;
} WAZA_Win_Stream;
extern WAZA_Win_Stream WAZA_Win;

typedef struct WAZA_Lose_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_SEQEND command004;
} WAZA_Lose_Stream;
extern WAZA_Lose_Stream WAZA_Lose;

typedef struct WAZA_TuushinWin_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_END_FIGHT command002;
    Seq_MESSAGE_WAIT command003;
    Seq_SEQEND command004;
} WAZA_TuushinWin_Stream;
extern WAZA_TuushinWin_Stream WAZA_TuushinWin;

typedef struct WAZA_BattleTowerWin_Stream {
    Seq_MESSAGE command000;
    Seq_TRAINER_APPEAR command001;
    Seq_CLIENT_BIT_WAIT command002;
    Seq_SEQEND command003;
} WAZA_BattleTowerWin_Stream;
extern WAZA_BattleTowerWin_Stream WAZA_BattleTowerWin;

typedef struct WAZA_ItemEscape_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_ItemEscape_Stream;
extern WAZA_ItemEscape_Stream WAZA_ItemEscape;

typedef struct WAZA_SpeabiEscape_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQEND command002;
} WAZA_SpeabiEscape_Stream;
extern WAZA_SpeabiEscape_Stream WAZA_SpeabiEscape;

typedef struct WAZA_Escape_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQEND command002;
} WAZA_Escape_Stream;
extern WAZA_Escape_Stream WAZA_Escape;

typedef struct WAZA_EnemyEscape_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQEND command002;
} WAZA_EnemyEscape_Stream;
extern WAZA_EnemyEscape_Stream WAZA_EnemyEscape;

typedef struct WAZA_TrainerEscape_Stream {
    Seq_MESSAGE command000;
    Seq_SEQEND command001;
} WAZA_TrainerEscape_Stream;
extern WAZA_TrainerEscape_Stream WAZA_TrainerEscape;

typedef struct WAZA_EscapeNG_Stream {
    Seq_MESSAGE_TBL command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQEND command002;
} WAZA_EscapeNG_Stream;
extern WAZA_EscapeNG_Stream WAZA_EscapeNG;

typedef struct WAZA_EscapeNG2_Stream {
    Seq_ALERT_MESSAGE_TBL command000;
    Seq_ALERTEND command001;
} WAZA_EscapeNG2_Stream;
extern WAZA_EscapeNG2_Stream WAZA_EscapeNG2;

typedef struct WAZA_SafariBallThrowNG_Stream {
    Seq_ALERT_MESSAGE command000;
    Seq_ALERTEND command001;
} WAZA_SafariBallThrowNG_Stream;
extern WAZA_SafariBallThrowNG_Stream WAZA_SafariBallThrowNG;

typedef struct WAZA_PokeReshuffle_Stream {
    Seq_POKE_HPDEC_RATE command000;
    Seq_MESSAGE_TBL command001;
    Seq_MESSAGE_WAIT command002;
    Seq_SETVALUE command003;
    Seq_SETVALUE command004;
} WAZA_PokeReshuffle_Stream;
extern WAZA_PokeReshuffle_Stream WAZA_PokeReshuffle;

typedef struct lbl_80416B06_Stream {
    Seq_OIUCHI_CHECK command000;
    Seq_SWITCH_A_D command001;
    Seq_MICHIDURE_CHECK command002;
    Seq_GOSUB command003;
    Seq_SWITCH_A_D command004;
    Seq_ADDVALUE command005;
    Seq_IF8 command006;
    Seq_SIZENKAIHUKU command007;
    Seq_CLIENT_BIT_WAIT command008;
    Seq_MODOSU_EFFECT command009;
    Seq_CLIENT_BIT_WAIT command010;
    Seq_BALL_GAUGE_SET command011;
    Seq_APPEAR_EFFECT_INIT command012;
    Seq_APPEAR_EFFECT command013;
    Seq_POKE_HPMAX_RATE command014;
    Seq_MESSAGE_TBL command015;
    Seq_BALL_GAUGE_OFF command016;
    Seq_APPEAR_EFFECT_WAIT command017;
    Seq_MESSAGE_WAIT command018;
    Seq_CLIENT_BIT_WAIT command019;
    Seq_POKE_RESHUFFLE_END command020;
    Seq_SETVALUE command021;
    Seq_WKC_ACT command022;
    Seq_SETVALUE command023;
    Seq_WKC_ACT command024;
    Seq_SEQEND command025;
    Seq_SETVALUE command026;
    Seq_STATUS_SET8 command027;
    Seq_WAIT command028;
    Seq_ATTACK_MESSAGE command029;
    Seq_PP_DEC command030;
    Seq_CRITICAL_CHECK command031;
    Seq_DAMAGE_CALC command032;
    Seq_TYPE_CHECK command033;
    Seq_DAMAGE_LOSS command034;
    Seq_SETVALUE command035;
    Seq_WAZA_EFFECT command036;
    Seq_EFFECT_WAIT command037;
    Seq_WAZAKOUKA_SE command038;
    Seq_POKE_BLINK command039;
    Seq_CLIENT_BIT_WAIT command040;
    Seq_HP_DEC command041;
    Seq_HP_DEC_WAIT command042;
    Seq_CRITICAL_MESSAGE command043;
    Seq_MESSAGE_WAIT command044;
    Seq_WAZAKOUKA_MESSAGE command045;
    Seq_MESSAGE_WAIT command046;
    Seq_EFFECT_WAIT command047;
    Seq_KIZETSU_CHECK command048;
    Seq_SETVALUE command049;
    Seq_WKC_ACT command050;
    Seq_SUBROUTINE_CALL command051;
    Seq_IF8 command052;
    Seq_GET_EXP command053;
    Seq_WAIT command054;
    Seq_SEQRET command055;
} lbl_80416B06_Stream;
extern lbl_80416B06_Stream lbl_80416B06;

typedef struct WAZA_Wait_Stream {
    Seq_WAIT command000;
    Seq_SEQRET command001;
} WAZA_Wait_Stream;
extern WAZA_Wait_Stream WAZA_Wait;

typedef struct WAZA_WeatherDamage_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE_TBL command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_SETVALUE command004;
    Seq_SETVALUE command005;
    Seq_STATUS_GET32 command006;
    Seq_IF32 command007;
    Seq_STATUS_SET32 command008;
    Seq_WEATHER_KEEP command009;
    Seq_STATUS_GET32 command010;
    Seq_IF32 command011;
    Seq_FIGHT_EFFECT2 command012;
    Seq_EFFECT_WAIT command013;
    Seq_SET32BIT command014;
    Seq_HP_DEC command015;
    Seq_MESSAGE_TBL command016;
    Seq_MESSAGE_WAIT command017;
    Seq_WAZAKOUKA_SE command018;
    Seq_POKE_BLINK command019;
    Seq_HP_DEC_WAIT command020;
    Seq_EFFECT_WAIT command021;
    Seq_KIZETSU_CHECK command022;
    Seq_ZENMETSU_CHECK command023;
    Seq_STATUS_GET16 command024;
    Seq_IF8 command025;
    Seq_ADDVALUE command026;
    Seq_IFWNE command027;
    Seq_RESET32BIT command028;
    Seq_SEQEND command029;
} WAZA_WeatherDamage_Stream;
extern WAZA_WeatherDamage_Stream WAZA_WeatherDamage;

typedef struct WAZA_WeatherDamageEnd_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE_TBL command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_SEQEND command004;
} WAZA_WeatherDamageEnd_Stream;
extern WAZA_WeatherDamageEnd_Stream WAZA_WeatherDamageEnd;

typedef struct WAZA_Amefuri_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE_TBL command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_IF8 command004;
    Seq_SEQEND command005;
} WAZA_Amefuri_Stream;
extern WAZA_Amefuri_Stream WAZA_Amefuri;

typedef struct WAZA_Hare_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_SEQEND command004;
} WAZA_Hare_Stream;
extern WAZA_Hare_Stream WAZA_Hare;

typedef struct WAZA_HareEnd_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_SEQEND command004;
} WAZA_HareEnd_Stream;
extern WAZA_HareEnd_Stream WAZA_HareEnd;

typedef struct WAZA_FieldWeather_Stream {
    Seq_MESSAGE_TBL command000;
    Seq_MESSAGE_WAIT command001;
    Seq_STATUS_GET16 command002;
    Seq_IF16 command003;
    Seq_IF16 command004;
    Seq_IF16 command005;
    Seq_IF16 command006;
    Seq_IF16 command007;
    Seq_JUMP command008;
    Seq_FIGHT_EFFECT2 command009;
    Seq_JUMP command010;
    Seq_FIGHT_EFFECT2 command011;
    Seq_JUMP command012;
    Seq_FIGHT_EFFECT2 command013;
    Seq_JUMP command014;
    Seq_FIGHT_EFFECT2 command015;
    Seq_JUMP command016;
    Seq_FIGHT_EFFECT2 command017;
    Seq_JUMP command018;
} WAZA_FieldWeather_Stream;
extern WAZA_FieldWeather_Stream WAZA_FieldWeather;

typedef struct lbl_80416D9B_Stream {
    Seq_EFFECT_WAIT command000;
    Seq_SPEABIEND command001;
} lbl_80416D9B_Stream;
extern lbl_80416D9B_Stream lbl_80416D9B;

typedef struct WAZA_ReflecEnd_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_ReflecEnd_Stream;
extern WAZA_ReflecEnd_Stream WAZA_ReflecEnd;

typedef struct WAZA_Shinpi_Stream {
    Seq_WAIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQEND command006;
} WAZA_Shinpi_Stream;
extern WAZA_Shinpi_Stream WAZA_Shinpi;

typedef struct WAZA_ShinpiEnd_Stream {
    Seq_WAIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQEND command006;
} WAZA_ShinpiEnd_Stream;
extern WAZA_ShinpiEnd_Stream WAZA_ShinpiEnd;

typedef struct WAZA_Yadorigi_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_HP_DEC_WAIT command004;
    Seq_STATUS_GET32 command005;
    Seq_STATUS_SET32 command006;
    Seq_SPEABI_CHECK command007;
    Seq_DAMAGE_CHG command008;
    Seq_SETVALUE command009;
    Seq_JUMP command010;
    Seq_SETVALUE command011;
    Seq_EFFECT_WAIT command012;
    Seq_FIGHT_EFFECT command013;
    Seq_SET32BIT command014;
    Seq_HP_DEC command015;
    Seq_MESSAGE_TBL command016;
    Seq_MESSAGE_WAIT command017;
    Seq_EFFECT_WAIT command018;
    Seq_HP_DEC_WAIT command019;
    Seq_EFFECT_WAIT command020;
    Seq_KIZETSU_CHECK command021;
    Seq_KIZETSU_CHECK command022;
    Seq_SEQEND command023;
    Seq_SET32BIT command024;
    Seq_MESSAGE_TBL command025;
    Seq_MESSAGE_WAIT command026;
    Seq_EFFECT_WAIT command027;
    Seq_FIGHT_EFFECT command028;
    Seq_EFFECT_WAIT command029;
    Seq_HP_DEC command030;
    Seq_HP_DEC_WAIT command031;
    Seq_EFFECT_WAIT command032;
    Seq_KIZETSU_CHECK command033;
    Seq_KIZETSU_CHECK command034;
    Seq_SEQEND command035;
} WAZA_Yadorigi_Stream;
extern WAZA_Yadorigi_Stream WAZA_Yadorigi;

typedef struct WAZA_Gaman_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_Gaman_Stream;
extern WAZA_Gaman_Stream WAZA_Gaman;

typedef struct WAZA_GamanOff_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_HITCHECK command005;
    Seq_TYPE_CHECK command006;
    Seq_STATUS_SET16 command007;
    Seq_STATUS_SET16 command008;
    Seq_STATUS_SET32 command009;
    Seq_KORAERU_CHECK command010;
    Seq_SETVALUE command011;
    Seq_WAZA_EFFECT command012;
    Seq_EFFECT_WAIT command013;
    Seq_WAZAKOUKA_SE command014;
    Seq_POKE_BLINK command015;
    Seq_CLIENT_BIT_WAIT command016;
    Seq_HP_DEC command017;
    Seq_WAZAKOUKA_MESSAGE command018;
    Seq_MESSAGE_WAIT command019;
    Seq_HP_DEC_WAIT command020;
    Seq_EFFECT_WAIT command021;
    Seq_KIZETSU_CHECK command022;
    Seq_JUMP command023;
} WAZA_GamanOff_Stream;
extern WAZA_GamanOff_Stream WAZA_GamanOff;

typedef struct WAZA_GamanFaild_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_GamanFaild_Stream;
extern WAZA_GamanFaild_Stream WAZA_GamanFaild;

typedef struct WAZA_Hukitobashi_Stream {
    Seq_WAZA_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SIZENKAIHUKU command002;
    Seq_POKEDELACTOR command003;
    Seq_CLIENT_BIT_WAIT command004;
    Seq_APPEAR_EFFECT_INIT command005;
    Seq_APPEAR_EFFECT command006;
    Seq_MESSAGE command007;
    Seq_APPEAR_EFFECT_WAIT command008;
    Seq_CLIENT_BIT_WAIT command009;
    Seq_POKE_RESHUFFLE_END command010;
    Seq_JUMP command011;
} WAZA_Hukitobashi_Stream;
extern WAZA_Hukitobashi_Stream WAZA_Hukitobashi;

typedef struct WAZA_HukitobashiFightEnd_Stream {
    Seq_WAZA_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_TELEPORT command002;
    Seq_SEQEND command003;
} WAZA_HukitobashiFightEnd_Stream;
extern WAZA_HukitobashiFightEnd_Stream WAZA_HukitobashiFightEnd;

typedef struct WAZA_Shiroikiri_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQRET command006;
} WAZA_Shiroikiri_Stream;
extern WAZA_Shiroikiri_Stream WAZA_Shiroikiri;

typedef struct WAZA_Ikari_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_SEQRET command004;
} WAZA_Ikari_Stream;
extern WAZA_Ikari_Stream WAZA_Ikari;

typedef struct WAZA_Kanashibari_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_Kanashibari_Stream;
extern WAZA_Kanashibari_Stream WAZA_Kanashibari;

typedef struct WAZA_KanashibariEnd_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_KanashibariEnd_Stream;
extern WAZA_KanashibariEnd_Stream WAZA_KanashibariEnd;

typedef struct WAZA_EncoreEnd_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_EncoreEnd_Stream;
extern WAZA_EncoreEnd_Stream WAZA_EncoreEnd;

typedef struct WAZA_Michidure_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_KIZETSU_CHECK command008;
    Seq_SEQRET command009;
} WAZA_Michidure_Stream;
extern WAZA_Michidure_Stream WAZA_Michidure;

typedef struct WAZA_MakibishiA_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_HP_DEC_WAIT command004;
    Seq_GOSUB command005;
    Seq_EFFECT_WAIT command006;
    Seq_KIZETSU_CHECK command007;
    Seq_KIZETSU_CHECK command008;
    Seq_SEQRET command009;
    Seq_GET_EXP command010;
    Seq_JUMP command011;
} WAZA_MakibishiA_Stream;
extern WAZA_MakibishiA_Stream WAZA_MakibishiA;

typedef struct WAZA_MakibishiD_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_HP_DEC_WAIT command004;
    Seq_GOSUB command005;
    Seq_EFFECT_WAIT command006;
    Seq_KIZETSU_CHECK command007;
    Seq_KIZETSU_CHECK command008;
    Seq_SEQRET command009;
    Seq_GET_EXP command010;
    Seq_JUMP command011;
} WAZA_MakibishiD_Stream;
extern WAZA_MakibishiD_Stream WAZA_MakibishiD;

typedef struct WAZA_MakibishiK_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_HP_DEC_WAIT command004;
    Seq_GOSUB command005;
    Seq_EFFECT_WAIT command006;
    Seq_KIZETSU_CHECK command007;
    Seq_KIZETSU_CHECK command008;
    Seq_SEQRET command009;
} WAZA_MakibishiK_Stream;
extern WAZA_MakibishiK_Stream WAZA_MakibishiK;

typedef struct lbl_8041708E_Stream {
    Seq_GET_EXP command000;
    Seq_JUMP command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_SEQRET command004;
} lbl_8041708E_Stream;
extern lbl_8041708E_Stream lbl_8041708E;

typedef struct WAZA_Horobinouta_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_KIZETSU_CHECK command008;
    Seq_SEQEND command009;
} WAZA_Horobinouta_Stream;
extern WAZA_Horobinouta_Stream WAZA_Horobinouta;

typedef struct WAZA_Horobinoutaing_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_Horobinoutaing_Stream;
extern WAZA_Horobinoutaing_Stream WAZA_Horobinoutaing;

typedef struct WAZA_Genshinochikara_Stream {
    Seq_CONDCHG_CHECK command000;
    Seq_CONDCHG_CHECK command001;
    Seq_CONDCHG_CHECK command002;
    Seq_CONDCHG_CHECK command003;
    Seq_CONDCHG_CHECK command004;
    Seq_SETVALUE command005;
    Seq_COND_CHG_BIT_CHECK command006;
    Seq_SETVALUE command007;
    Seq_CONDCHG command008;
    Seq_MESSAGE_TBL command009;
    Seq_WAIT command010;
} WAZA_Genshinochikara_Stream;
extern WAZA_Genshinochikara_Stream WAZA_Genshinochikara;

typedef struct lbl_80417125_Stream {
    Seq_SETVALUE command000;
    Seq_CONDCHG command001;
    Seq_MESSAGE_TBL command002;
    Seq_WAIT command003;
    Seq_SETVALUE command004;
    Seq_CONDCHG command005;
    Seq_MESSAGE_TBL command006;
    Seq_WAIT command007;
    Seq_SETVALUE command008;
    Seq_CONDCHG command009;
    Seq_MESSAGE_TBL command010;
    Seq_WAIT command011;
    Seq_SETVALUE command012;
    Seq_CONDCHG command013;
    Seq_MESSAGE_TBL command014;
    Seq_WAIT command015;
    Seq_MESSAGE_WAIT command016;
    Seq_EFFECT_WAIT command017;
    Seq_SEQRET command018;
} lbl_80417125_Stream;
extern lbl_80417125_Stream lbl_80417125;

typedef struct WAZA_Kousokuspin_Stream {
    Seq_KOUSOKUSPIN command000;
    Seq_SEQRET command001;
} WAZA_Kousokuspin_Stream;
extern WAZA_Kousokuspin_Stream WAZA_Kousokuspin;

typedef struct WAZA_ShimeEscape_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_ShimeEscape_Stream;
extern WAZA_ShimeEscape_Stream WAZA_ShimeEscape;

typedef struct WAZA_YadorigiEscape_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_YadorigiEscape_Stream;
extern WAZA_YadorigiEscape_Stream WAZA_YadorigiEscape;

typedef struct WAZA_MakibishiEscape_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_MakibishiEscape_Stream;
extern WAZA_MakibishiEscape_Stream WAZA_MakibishiEscape;

typedef struct WAZA_Miraiyochi_Stream {
    Seq_IF8 command000;
    Seq_HITCHECK command001;
    Seq_FIGHT_EFFECT command002;
    Seq_EFFECT_WAIT command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_JUMP command006;
    Seq_HITCHECK command007;
    Seq_FIGHT_EFFECT command008;
    Seq_EFFECT_WAIT command009;
    Seq_MESSAGE command010;
    Seq_MESSAGE_WAIT command011;
} WAZA_Miraiyochi_Stream;
extern WAZA_Miraiyochi_Stream WAZA_Miraiyochi;

typedef struct lbl_804171F9_Stream {
    Seq_DAMAGE_LOSS_ONLY command000;
    Seq_IF8 command001;
    Seq_EFFECT_WAIT command002;
    Seq_JUMP command003;
} lbl_804171F9_Stream;
extern lbl_804171F9_Stream lbl_804171F9;

typedef struct lbl_8041720C_Stream {
    Seq_HP_DEC command000;
    Seq_WAZAKOUKA_SE command001;
    Seq_POKE_BLINK command002;
    Seq_CLIENT_BIT_WAIT command003;
    Seq_WAZAKOUKA_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_KIZETSU_CHECK command008;
    Seq_ZENMETSU_CHECK command009;
    Seq_SETVALUE command010;
    Seq_WKC_ACT command011;
    Seq_SETVALUE command012;
    Seq_WKC_ACT command013;
    Seq_STATUS_SET16 command014;
    Seq_SEQEND command015;
    Seq_STATUS_SET16 command016;
    Seq_STATUS_SET16 command017;
    Seq_FIGHT_EFFECT command018;
    Seq_EFFECT_WAIT command019;
    Seq_MESSAGE command020;
    Seq_MESSAGE_WAIT command021;
    Seq_WAZAKOUKA_MESSAGE command022;
    Seq_MESSAGE_WAIT command023;
    Seq_EFFECT_WAIT command024;
    Seq_STATUS_SET16 command025;
    Seq_SEQEND command026;
} lbl_8041720C_Stream;
extern lbl_8041720C_Stream lbl_8041720C;

typedef struct WAZA_PPNoneAttack_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
} WAZA_PPNoneAttack_Stream;
extern WAZA_PPNoneAttack_Stream WAZA_PPNoneAttack;

typedef struct WAZA_Chouhatsu2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_Chouhatsu2_Stream;
extern WAZA_Chouhatsu2_Stream WAZA_Chouhatsu2;

typedef struct WAZA_Negaigoto_Stream {
    Seq_NEGAIGOTO command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_FIGHT_EFFECT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SET32BIT command008;
    Seq_HP_DEC command009;
    Seq_MESSAGE command010;
    Seq_MESSAGE_WAIT command011;
    Seq_HP_DEC_WAIT command012;
    Seq_EFFECT_WAIT command013;
    Seq_SEQEND command014;
    Seq_FIGHT_EFFECT command015;
    Seq_EFFECT_WAIT command016;
    Seq_MESSAGE command017;
    Seq_MESSAGE_WAIT command018;
    Seq_WAIT command019;
    Seq_MESSAGE command020;
    Seq_MESSAGE_WAIT command021;
    Seq_EFFECT_WAIT command022;
    Seq_SEQEND command023;
} WAZA_Negaigoto_Stream;
extern WAZA_Negaigoto_Stream WAZA_Negaigoto;

typedef struct WAZA_Newoharu_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SEQEND command008;
    Seq_WAIT command009;
    Seq_FIGHT_EFFECT command010;
    Seq_EFFECT_WAIT command011;
    Seq_MESSAGE command012;
    Seq_MESSAGE_WAIT command013;
    Seq_EFFECT_WAIT command014;
    Seq_JUMP command015;
} WAZA_Newoharu_Stream;
extern WAZA_Newoharu_Stream WAZA_Newoharu;

typedef struct WAZA_Bakadikara_Stream {
    Seq_SETVALUE command000;
    Seq_COND_CHG_BIT_CHECK command001;
    Seq_COND_CHG_BIT_CHECK command002;
    Seq_SETVALUE command003;
    Seq_CONDCHG command004;
    Seq_IF8 command005;
    Seq_MESSAGE_TBL command006;
    Seq_WAIT command007;
} WAZA_Bakadikara_Stream;
extern WAZA_Bakadikara_Stream WAZA_Bakadikara;

typedef struct lbl_80417394_Stream {
    Seq_COND_CHG_BIT_CHECK command000;
    Seq_SETVALUE command001;
    Seq_CONDCHG command002;
    Seq_IF8 command003;
    Seq_MESSAGE_TBL command004;
    Seq_WAIT command005;
} lbl_80417394_Stream;
extern lbl_80417394_Stream lbl_80417394;

typedef struct lbl_804173B7_Stream {
    Seq_MESSAGE_WAIT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SEQRET command002;
} lbl_804173B7_Stream;
extern lbl_804173B7_Stream lbl_804173B7;

typedef struct WAZA_Hatakiotosu_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_SEQRET command004;
} WAZA_Hatakiotosu_Stream;
extern WAZA_Hatakiotosu_Stream WAZA_Hatakiotosu;

typedef struct WAZA_Huuin_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_Huuin_Stream;
extern WAZA_Huuin_Stream WAZA_Huuin;

typedef struct WAZA_Onnen_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_Onnen_Stream;
extern WAZA_Onnen_Stream WAZA_Onnen;

typedef struct WAZA_MagicCort_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_PP_DEC command001;
    Seq_FIGHT_EFFECT command002;
    Seq_EFFECT_WAIT command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_SET32BIT command007;
    Seq_SUBROUTINE_CALL command008;
    Seq_SEQRET command009;
} WAZA_MagicCort_Stream;
extern WAZA_MagicCort_Stream WAZA_MagicCort;

typedef struct WAZA_Yokodori_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_PP_DEC command001;
    Seq_FIGHT_EFFECT command002;
    Seq_EFFECT_WAIT command003;
    Seq_YOKODORI_CLIENT_SET command004;
    Seq_MESSAGE command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SET32BIT command008;
    Seq_SWITCH_A_D command009;
    Seq_SEQRET command010;
} WAZA_Yokodori_Stream;
extern WAZA_Yokodori_Stream WAZA_Yokodori;

typedef struct WAZA_Koraeta_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQRET command002;
} WAZA_Koraeta_Stream;
extern WAZA_Koraeta_Stream WAZA_Koraeta;

typedef struct WAZA_Ichigeki_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQRET command002;
} WAZA_Ichigeki_Stream;
extern WAZA_Ichigeki_Stream WAZA_Ichigeki;

typedef struct WAZA_OverHeat_Stream {
    Seq_SETVALUE command000;
    Seq_COND_CHG_BIT_CHECK command001;
    Seq_SETVALUE command002;
    Seq_CONDCHG command003;
    Seq_IF8 command004;
    Seq_EFFECT_WAIT command005;
    Seq_MESSAGE_TBL command006;
    Seq_MESSAGE_WAIT command007;
} WAZA_OverHeat_Stream;
extern WAZA_OverHeat_Stream WAZA_OverHeat;

typedef struct lbl_8041747B_Stream {
    Seq_EFFECT_WAIT command000;
    Seq_SEQRET command001;
} lbl_8041747B_Stream;
extern lbl_8041747B_Stream lbl_8041747B;

typedef struct WAZA_KiaiPunch_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_KiaiPunch_Stream;
extern WAZA_KiaiPunch_Stream WAZA_KiaiPunch;

typedef struct WAZA_Hyper_Stream {
    Seq_JUMP command000;
} WAZA_Hyper_Stream;
extern WAZA_Hyper_Stream WAZA_Hyper;

typedef struct WAZA_Nemuru_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_Nemuru_Stream;
extern WAZA_Nemuru_Stream WAZA_Nemuru;

typedef struct WAZA_Mezame_Stream {
    Seq_RESET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_CONDITION_GAUGE command003;
    Seq_MESSAGE_TBL command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_SEQRET command007;
} WAZA_Mezame_Stream;
extern WAZA_Mezame_Stream WAZA_Mezame;

typedef struct WAZA_SawaguMezame_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQEND command006;
} WAZA_SawaguMezame_Stream;
extern WAZA_SawaguMezame_Stream WAZA_SawaguMezame;

typedef struct WAZA_Revers_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_JUMP command005;
} WAZA_Revers_Stream;
extern WAZA_Revers_Stream WAZA_Revers;

typedef struct WAZA_Dokudoku_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
} WAZA_Dokudoku_Stream;
extern WAZA_Dokudoku_Stream WAZA_Dokudoku;

typedef struct lbl_80417511_Stream {
    Seq_MESSAGE_WAIT command000;
    Seq_HP_DEC_WAIT command001;
    Seq_EFFECT_WAIT command002;
    Seq_KIZETSU_CHECK command003;
    Seq_ZENMETSU_CHECK command004;
    Seq_SEQEND command005;
} lbl_80417511_Stream;
extern lbl_80417511_Stream lbl_80417511;

typedef struct WAZA_Yakedo_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_JUMP command005;
} WAZA_Yakedo_Stream;
extern WAZA_Yakedo_Stream WAZA_Yakedo;

typedef struct WAZA_Koori_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_Koori_Stream;
extern WAZA_Koori_Stream WAZA_Koori;

typedef struct WAZA_Melt_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE_TBL command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQRET command006;
} WAZA_Melt_Stream;
extern WAZA_Melt_Stream WAZA_Melt;

typedef struct WAZA_Melt2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQRET command006;
} WAZA_Melt2_Stream;
extern WAZA_Melt2_Stream WAZA_Melt2;

typedef struct WAZA_Mahi_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_Mahi_Stream;
extern WAZA_Mahi_Stream WAZA_Mahi;

typedef struct WAZA_Hirumu_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_Hirumu_Stream;
extern WAZA_Hirumu_Stream WAZA_Hirumu;

typedef struct WAZA_Sawagu_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE_TBL command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_Sawagu_Stream;
extern WAZA_Sawagu_Stream WAZA_Sawagu;

typedef struct WAZA_AbareruEnd_Stream {
    Seq_STATUS_EFFECT_DIRECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_AbareruEnd_Stream;
extern WAZA_AbareruEnd_Stream WAZA_AbareruEnd;

typedef struct WAZA_Konran_Stream {
    Seq_STATUS_EFFECT2 command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_IF8 command005;
} WAZA_Konran_Stream;
extern WAZA_Konran_Stream WAZA_Konran;

typedef struct lbl_804175ED_Stream {
    Seq_SUBROUTINE_CALL command000;
    Seq_DAMAGE_LOSS_ONLY command001;
    Seq_SET32BIT command002;
    Seq_FIGHT_EFFECT command003;
    Seq_EFFECT_WAIT command004;
    Seq_WAZAKOUKA_SE command005;
    Seq_POKE_BLINK command006;
    Seq_CLIENT_BIT_WAIT command007;
    Seq_HP_DEC command008;
    Seq_MESSAGE command009;
    Seq_MESSAGE_WAIT command010;
    Seq_WAZAKOUKA_MESSAGE command011;
    Seq_MESSAGE_WAIT command012;
    Seq_HP_DEC_WAIT command013;
    Seq_EFFECT_WAIT command014;
    Seq_KIZETSU_CHECK command015;
    Seq_JUMP command016;
    Seq_SEQRET command017;
} lbl_804175ED_Stream;
extern lbl_804175ED_Stream lbl_804175ED;

typedef struct WAZA_KonranEnd_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_KonranEnd_Stream;
extern WAZA_KonranEnd_Stream WAZA_KonranEnd;

typedef struct WAZA_Nekonikoban_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQRET command002;
} WAZA_Nekonikoban_Stream;
extern WAZA_Nekonikoban_Stream WAZA_Nekonikoban;

typedef struct WAZA_Shime_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_JUMP command005;
} WAZA_Shime_Stream;
extern WAZA_Shime_Stream WAZA_Shime;

typedef struct WAZA_ShimeEnd_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQEND command005;
} WAZA_ShimeEnd_Stream;
extern WAZA_ShimeEnd_Stream WAZA_ShimeEnd;

typedef struct WAZA_Meromero_Stream {
    Seq_STATUS_EFFECT2 command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_Meromero_Stream;
extern WAZA_Meromero_Stream WAZA_Meromero;

typedef struct WAZA_MeromeroNext_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_MeromeroNext_Stream;
extern WAZA_MeromeroNext_Stream WAZA_MeromeroNext;

typedef struct WAZA_Akumu_Stream {
    Seq_STATUS_EFFECT2 command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_JUMP command005;
} WAZA_Akumu_Stream;
extern WAZA_Akumu_Stream WAZA_Akumu;

typedef struct WAZA_Noroi_Stream {
    Seq_STATUS_EFFECT2 command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_JUMP command005;
} WAZA_Noroi_Stream;
extern WAZA_Noroi_Stream WAZA_Noroi;

typedef struct WAZA_NoMahi_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQRET command006;
} WAZA_NoMahi_Stream;
extern WAZA_NoMahi_Stream WAZA_NoMahi;

typedef struct WAZA_AddNemuri_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE_TBL command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
} WAZA_AddNemuri_Stream;
extern WAZA_AddNemuri_Stream WAZA_AddNemuri;

typedef struct lbl_80417700_Stream {
    Seq_CLIENT_BIT_WAIT command000;
    Seq_SEQRET command001;
} lbl_80417700_Stream;
extern lbl_80417700_Stream lbl_80417700;

typedef struct WAZA_AddNemuri2_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_CLIENT_BIT_WAIT command006;
    Seq_VANISH_OFF command007;
    Seq_SEQEND command008;
} WAZA_AddNemuri2_Stream;
extern WAZA_AddNemuri2_Stream WAZA_AddNemuri2;

typedef struct WAZA_AddDoku_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE_TBL command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
} WAZA_AddDoku_Stream;
extern WAZA_AddDoku_Stream WAZA_AddDoku;

typedef struct WAZA_AddYakedo_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE_TBL command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
} WAZA_AddYakedo_Stream;
extern WAZA_AddYakedo_Stream WAZA_AddYakedo;

typedef struct WAZA_AddKoori_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE_TBL command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
} WAZA_AddKoori_Stream;
extern WAZA_AddKoori_Stream WAZA_AddKoori;

typedef struct WAZA_AddMahi_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE_TBL command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
} WAZA_AddMahi_Stream;
extern WAZA_AddMahi_Stream WAZA_AddMahi;

typedef struct WAZA_AddSawagu_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_AddSawagu_Stream;
extern WAZA_AddSawagu_Stream WAZA_AddSawagu;

typedef struct WAZA_AddDokudoku_Stream {
    Seq_STATUS_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
} WAZA_AddDokudoku_Stream;
extern WAZA_AddDokudoku_Stream WAZA_AddDokudoku;

typedef struct WAZA_AddNekonikoban_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_AddNekonikoban_Stream;
extern WAZA_AddNekonikoban_Stream WAZA_AddNekonikoban;

typedef struct WAZA_AddShime_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_MESSAGE_TBL command001;
    Seq_MESSAGE_WAIT command002;
    Seq_EFFECT_WAIT command003;
    Seq_SEQRET command004;
} WAZA_AddShime_Stream;
extern WAZA_AddShime_Stream WAZA_AddShime;

typedef struct WAZA_AddKonran_Stream {
    Seq_STATUS_EFFECT_DIRECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_AddKonran_Stream;
extern WAZA_AddKonran_Stream WAZA_AddKonran;

typedef struct WAZA_AddHanekaeri_Stream {
    Seq_STATUS_GET16 command000;
    Seq_IF16 command001;
    Seq_IF16 command002;
    Seq_SPEABI_CHECK command003;
} WAZA_AddHanekaeri_Stream;
extern WAZA_AddHanekaeri_Stream WAZA_AddHanekaeri;

typedef struct lbl_80417800_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_KIZETSU_CHECK command008;
} lbl_80417800_Stream;
extern lbl_80417800_Stream lbl_80417800;

typedef struct lbl_80417827_Stream {
    Seq_SEQRET command000;
} lbl_80417827_Stream;
extern lbl_80417827_Stream lbl_80417827;

typedef struct WAZA_AddDorobou_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_AddDorobou_Stream;
extern WAZA_AddDorobou_Stream WAZA_AddDorobou;

typedef struct WAZA_Amehurashi_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_TOKUSEI_SET command003;
    Seq_MESSAGE_WAIT command004;
    Seq_CLIENT_BIT_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_GOSUB command007;
    Seq_SPEABIEND command008;
} WAZA_Amehurashi_Stream;
extern WAZA_Amehurashi_Stream WAZA_Amehurashi;

typedef struct WAZA_Sunaokosi_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_TOKUSEI_SET command003;
    Seq_MESSAGE_WAIT command004;
    Seq_CLIENT_BIT_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_GOSUB command007;
    Seq_SPEABIEND command008;
} WAZA_Sunaokosi_Stream;
extern WAZA_Sunaokosi_Stream WAZA_Sunaokosi;

typedef struct WAZA_Hideri_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_TOKUSEI_SET command003;
    Seq_MESSAGE_WAIT command004;
    Seq_CLIENT_BIT_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_GOSUB command007;
    Seq_SPEABIEND command008;
} WAZA_Hideri_Stream;
extern WAZA_Hideri_Stream WAZA_Hideri;

typedef struct WAZA_Ikaku_Stream {
    Seq_GOSUB command000;
    Seq_SPEABIEND command001;
} WAZA_Ikaku_Stream;
extern WAZA_Ikaku_Stream WAZA_Ikaku;

typedef struct lbl_80417896_Stream {
    Seq_WAIT command000;
} lbl_80417896_Stream;
extern lbl_80417896_Stream lbl_80417896;

typedef struct WAZA_IkakuAct_Stream {
    Seq_SETVALUE command000;
    Seq_IKAKU command001;
    Seq_SEQRET command002;
} WAZA_IkakuAct_Stream;
extern WAZA_IkakuAct_Stream WAZA_IkakuAct;

typedef struct WAZA_IkakuLoop_Stream {
    Seq_CONDITION2_CHECK command000;
    Seq_SPEABI_CHECK command001;
    Seq_SPEABI_CHECK command002;
    Seq_SPEABI_CHECK command003;
    Seq_CONDCHG command004;
    Seq_IF8 command005;
    Seq_COND_CHG_WORK_SET command006;
    Seq_FIGHT_EFFECT command007;
    Seq_EFFECT_WAIT command008;
    Seq_MESSAGE command009;
    Seq_TOKUSEI_SET command010;
    Seq_MESSAGE_WAIT command011;
    Seq_EFFECT_WAIT command012;
} WAZA_IkakuLoop_Stream;
extern WAZA_IkakuLoop_Stream WAZA_IkakuLoop;

typedef struct lbl_804178EB_Stream {
    Seq_SEQRET command000;
} lbl_804178EB_Stream;
extern lbl_804178EB_Stream lbl_804178EB;

typedef struct lbl_804178EC_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_TOKUSEI_SET command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_JUMP command006;
} lbl_804178EC_Stream;
extern lbl_804178EC_Stream lbl_804178EC;

typedef struct WAZA_Trace_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_TOKUSEI_SET command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SPEABIEND command006;
} WAZA_Trace_Stream;
extern WAZA_Trace_Stream WAZA_Trace;

typedef struct WAZA_Ameukezara_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_TOKUSEI_SET command005;
    Seq_MESSAGE_WAIT command006;
    Seq_HP_DEC_WAIT command007;
    Seq_EFFECT_WAIT command008;
    Seq_SPEABIEND command009;
} WAZA_Ameukezara_Stream;
extern WAZA_Ameukezara_Stream WAZA_Ameukezara;

typedef struct WAZA_Dappi_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_SPEABIEND command007;
} WAZA_Dappi_Stream;
extern WAZA_Dappi_Stream WAZA_Dappi;

typedef struct WAZA_Kasokusouti_Stream {
    Seq_SETVALUE command000;
    Seq_SETVALUE command001;
    Seq_FIGHT_EFFECT command002;
    Seq_EFFECT_WAIT command003;
    Seq_MESSAGE command004;
    Seq_TOKUSEI_SET command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SPEABIEND command008;
    Seq_TENKIYA_CHECK command009;
    Seq_SEQRET command010;
} WAZA_Kasokusouti_Stream;
extern WAZA_Kasokusouti_Stream WAZA_Kasokusouti;

typedef struct WAZA_Tenkiya_Stream {
    Seq_GOSUB command000;
    Seq_SPEABIEND command001;
} WAZA_Tenkiya_Stream;
extern WAZA_Tenkiya_Stream WAZA_Tenkiya;

typedef struct WAZA_Tenkiya2_Stream {
    Seq_TENKIYA command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_CLIENT_BIT_WAIT command003;
    Seq_MESSAGE command004;
    Seq_TOKUSEI_SET command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SEQRET command008;
} WAZA_Tenkiya2_Stream;
extern WAZA_Tenkiya2_Stream WAZA_Tenkiya2;

typedef struct WAZA_Hiraishin_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_WAIT command003;
    Seq_MESSAGE command004;
    Seq_TOKUSEI_SET command005;
    Seq_MESSAGE_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SET32BIT command008;
    Seq_SEQRET command009;
} WAZA_Hiraishin_Stream;
extern WAZA_Hiraishin_Stream WAZA_Hiraishin;

typedef struct WAZA_TyosuiPPDec_Stream {
    Seq_PP_DEC command000;
} WAZA_TyosuiPPDec_Stream;
extern WAZA_TyosuiPPDec_Stream WAZA_TyosuiPPDec;

typedef struct WAZA_Tyosui_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_SET32BIT command001;
    Seq_FIGHT_EFFECT command002;
    Seq_EFFECT_WAIT command003;
    Seq_HP_DEC command004;
    Seq_MESSAGE command005;
    Seq_TOKUSEI_SET command006;
    Seq_MESSAGE_WAIT command007;
    Seq_HP_DEC_WAIT command008;
    Seq_EFFECT_WAIT command009;
    Seq_STATUS_SET16 command010;
    Seq_JUMP command011;
} WAZA_Tyosui_Stream;
extern WAZA_Tyosui_Stream WAZA_Tyosui;

typedef struct WAZA_NOKaifukuPPDec_Stream {
    Seq_PP_DEC command000;
} WAZA_NOKaifukuPPDec_Stream;
extern WAZA_NOKaifukuPPDec_Stream WAZA_NOKaifukuPPDec;

typedef struct WAZA_NOKaifuku_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_STATUS_SET16 command007;
    Seq_JUMP command008;
} WAZA_NOKaifuku_Stream;
extern WAZA_NOKaifuku_Stream WAZA_NOKaifuku;

typedef struct WAZA_MoraibiPPDec_Stream {
    Seq_PP_DEC command000;
} WAZA_MoraibiPPDec_Stream;
extern WAZA_MoraibiPPDec_Stream WAZA_MoraibiPPDec;

typedef struct WAZA_Moraibi_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_MESSAGE_TBL command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
} WAZA_Moraibi_Stream;
extern WAZA_Moraibi_Stream WAZA_Moraibi;

typedef struct WAZA_Ganzyou_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
} WAZA_Ganzyou_Stream;
extern WAZA_Ganzyou_Stream WAZA_Ganzyou;

typedef struct WAZA_Shimerike_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
} WAZA_Shimerike_Stream;
extern WAZA_Shimerike_Stream WAZA_Shimerike;

typedef struct lbl_80417A7F_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
} lbl_80417A7F_Stream;
extern lbl_80417A7F_Stream lbl_80417A7F;

typedef struct WAZA_ClearBody_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_SEQRET command007;
} WAZA_ClearBody_Stream;
extern WAZA_ClearBody_Stream WAZA_ClearBody;

typedef struct WAZA_Mizunobeeru_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE_TBL command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_SEQRET command007;
} WAZA_Mizunobeeru_Stream;
extern WAZA_Mizunobeeru_Stream WAZA_Mizunobeeru;

typedef struct WAZA_Juunan_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE_TBL command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_SEQRET command007;
} WAZA_Juunan_Stream;
extern WAZA_Juunan_Stream WAZA_Juunan;

typedef struct WAZA_Meneki_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE_TBL command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_SEQRET command007;
} WAZA_Meneki_Stream;
extern WAZA_Meneki_Stream WAZA_Meneki;

typedef struct WAZA_Donkan_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
} WAZA_Donkan_Stream;
extern WAZA_Donkan_Stream WAZA_Donkan;

typedef struct WAZA_Seisinryoku_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
} WAZA_Seisinryoku_Stream;
extern WAZA_Seisinryoku_Stream WAZA_Seisinryoku;

typedef struct WAZA_Mypace_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
} WAZA_Mypace_Stream;
extern WAZA_Mypace_Stream WAZA_Mypace;

typedef struct WAZA_Bouon_Stream {
    Seq_ATTACK_MESSAGE command000;
    Seq_PP_DEC command001;
    Seq_WAIT command002;
    Seq_FIGHT_EFFECT command003;
    Seq_EFFECT_WAIT command004;
    Seq_MESSAGE command005;
    Seq_TOKUSEI_SET command006;
    Seq_MESSAGE_WAIT command007;
    Seq_EFFECT_WAIT command008;
    Seq_JUMP command009;
} WAZA_Bouon_Stream;
extern WAZA_Bouon_Stream WAZA_Bouon;

typedef struct WAZA_Kairikibasami_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_SETVALUE command006;
    Seq_EFFECT_WAIT command007;
    Seq_SEQRET command008;
} WAZA_Kairikibasami_Stream;
extern WAZA_Kairikibasami_Stream WAZA_Kairikibasami;

typedef struct WAZA_Nentyaku_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_JUMP command007;
} WAZA_Nentyaku_Stream;
extern WAZA_Nentyaku_Stream WAZA_Nentyaku;

typedef struct WAZA_Nentyaku2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_WAIT command002;
    Seq_MESSAGE command003;
    Seq_TOKUSEI_SET command004;
    Seq_MESSAGE_WAIT command005;
    Seq_EFFECT_WAIT command006;
    Seq_SEQRET command007;
} WAZA_Nentyaku2_Stream;
extern WAZA_Nentyaku2_Stream WAZA_Nentyaku2;

typedef struct WAZA_Hensyoku_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_TOKUSEI_SET command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQRET command006;
} WAZA_Hensyoku_Stream;
extern WAZA_Hensyoku_Stream WAZA_Hensyoku;

typedef struct WAZA_Samehada_Stream {
    Seq_SET32BIT command000;
    Seq_FIGHT_EFFECT command001;
    Seq_EFFECT_WAIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_TOKUSEI_SET command005;
    Seq_MESSAGE_WAIT command006;
    Seq_HP_DEC_WAIT command007;
    Seq_EFFECT_WAIT command008;
    Seq_KIZETSU_CHECK command009;
    Seq_SEQRET command010;
} WAZA_Samehada_Stream;
extern WAZA_Samehada_Stream WAZA_Samehada;

typedef struct WAZA_Honoonokarada_Stream {
    Seq_CLIENT_BIT_WAIT command000;
    Seq_TSUIKA_INDIRECT_ACT command001;
    Seq_TOKUSEI_SET command002;
    Seq_SEQRET command003;
} WAZA_Honoonokarada_Stream;
extern WAZA_Honoonokarada_Stream WAZA_Honoonokarada;

typedef struct WAZA_MeromeroBody_Stream {
    Seq_STATUS_EFFECT2 command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_TOKUSEI_SET command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQRET command006;
} WAZA_MeromeroBody_Stream;
extern WAZA_MeromeroBody_Stream WAZA_MeromeroBody;

typedef struct WAZA_Sinkuro_Stream {
    Seq_CLIENT_BIT_WAIT command000;
    Seq_TSUIKA_DIRECT_ACT command001;
    Seq_EFFECT_WAIT command002;
    Seq_SEQRET command003;
} WAZA_Sinkuro_Stream;
extern WAZA_Sinkuro_Stream WAZA_Sinkuro;

typedef struct WAZA_SpeabiNoJoutaiijou_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_SEQRET command006;
} WAZA_SpeabiNoJoutaiijou_Stream;
extern WAZA_SpeabiNoJoutaiijou_Stream WAZA_SpeabiNoJoutaiijou;

typedef struct WAZA_OrderIgnoreSleep_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SETVALUE command005;
    Seq_WKC_ACT command006;
    Seq_WAZAEND command007;
} WAZA_OrderIgnoreSleep_Stream;
extern WAZA_OrderIgnoreSleep_Stream WAZA_OrderIgnoreSleep;

typedef struct WAZA_OrderIgnore_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_WAZASEQADRS command005;
} WAZA_OrderIgnore_Stream;
extern WAZA_OrderIgnore_Stream WAZA_OrderIgnore;

typedef struct WAZA_Namakeru_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE_TBL command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SETVALUE command005;
    Seq_WKC_ACT command006;
    Seq_WAZAEND command007;
} WAZA_Namakeru_Stream;
extern WAZA_Namakeru_Stream WAZA_Namakeru;

typedef struct WAZA_Hirune_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SETVALUE command005;
    Seq_TSUIKA_DIRECT_ACT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SETVALUE command008;
    Seq_WKC_ACT command009;
    Seq_WAZAEND command010;
} WAZA_Hirune_Stream;
extern WAZA_Hirune_Stream WAZA_Hirune;

typedef struct WAZA_OwnAttack_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_JUMP command005;
} WAZA_OwnAttack_Stream;
extern WAZA_OwnAttack_Stream WAZA_OwnAttack;

typedef struct WAZA_HyperOrderIgnore_Stream {
    Seq_WAZASEQADRS command000;
} WAZA_HyperOrderIgnore_Stream;
extern WAZA_HyperOrderIgnore_Stream WAZA_HyperOrderIgnore;

typedef struct WAZA_HyperOwnAttack_Stream {
    Seq_JUMP command000;
} WAZA_HyperOwnAttack_Stream;
extern WAZA_HyperOwnAttack_Stream WAZA_HyperOwnAttack;

typedef struct WAZA_HyperPost_Stream {
    Seq_SETVALUE command000;
    Seq_WKC_ACT command001;
    Seq_WAZAEND command002;
} WAZA_HyperPost_Stream;
extern WAZA_HyperPost_Stream WAZA_HyperPost;

typedef struct WAZA_HyperModoru_Stream {
    Seq_POKE_RESHUFFLE command000;
    Seq_CLIENT_BIT_WAIT command001;
    Seq_POKE_RESHUFFLE_WAIT command002;
    Seq_APPEAR_EFFECT_INIT command003;
    Seq_APPEAR_EFFECT command004;
    Seq_POKE_HPMAX_RATE command005;
    Seq_MESSAGE_TBL command006;
    Seq_APPEAR_EFFECT_WAIT command007;
    Seq_MESSAGE_WAIT command008;
    Seq_CLIENT_BIT_WAIT command009;
    Seq_POKE_RESHUFFLE_END command010;
    Seq_JUMP command011;
} WAZA_HyperModoru_Stream;
extern WAZA_HyperModoru_Stream WAZA_HyperModoru;

typedef struct WAZA_MigawariKizetsu_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_SEQRET command005;
} WAZA_MigawariKizetsu_Stream;
extern WAZA_MigawariKizetsu_Stream WAZA_MigawariKizetsu;

typedef struct WAZA_ItemNoMahi_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemNoMahi_Stream;
extern WAZA_ItemNoMahi_Stream WAZA_ItemNoMahi;

typedef struct WAZA_ItemNoMahi2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_KILLITEM command006;
    Seq_SEQRET command007;
} WAZA_ItemNoMahi2_Stream;
extern WAZA_ItemNoMahi2_Stream WAZA_ItemNoMahi2;

typedef struct WAZA_ItemNoDoku_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemNoDoku_Stream;
extern WAZA_ItemNoDoku_Stream WAZA_ItemNoDoku;

typedef struct WAZA_ItemNoDoku2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_KILLITEM command006;
    Seq_SEQRET command007;
} WAZA_ItemNoDoku2_Stream;
extern WAZA_ItemNoDoku2_Stream WAZA_ItemNoDoku2;

typedef struct WAZA_ItemNoYakedo_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemNoYakedo_Stream;
extern WAZA_ItemNoYakedo_Stream WAZA_ItemNoYakedo;

typedef struct WAZA_ItemNoYakedo2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_KILLITEM command006;
    Seq_SEQRET command007;
} WAZA_ItemNoYakedo2_Stream;
extern WAZA_ItemNoYakedo2_Stream WAZA_ItemNoYakedo2;

typedef struct WAZA_ItemNoKoori_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemNoKoori_Stream;
extern WAZA_ItemNoKoori_Stream WAZA_ItemNoKoori;

typedef struct WAZA_ItemNoKoori2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_KILLITEM command006;
    Seq_SEQRET command007;
} WAZA_ItemNoKoori2_Stream;
extern WAZA_ItemNoKoori2_Stream WAZA_ItemNoKoori2;

typedef struct WAZA_ItemNoNemuri_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemNoNemuri_Stream;
extern WAZA_ItemNoNemuri_Stream WAZA_ItemNoNemuri;

typedef struct WAZA_ItemNoNemuri2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_KILLITEM command006;
    Seq_SEQRET command007;
} WAZA_ItemNoNemuri2_Stream;
extern WAZA_ItemNoNemuri2_Stream WAZA_ItemNoNemuri2;

typedef struct WAZA_ItemNoKonran_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemNoKonran_Stream;
extern WAZA_ItemNoKonran_Stream WAZA_ItemNoKonran;

typedef struct WAZA_ItemNoKonran2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_KILLITEM command005;
    Seq_SEQRET command006;
} WAZA_ItemNoKonran2_Stream;
extern WAZA_ItemNoKonran2_Stream WAZA_ItemNoKonran2;

typedef struct WAZA_ItemNoJoutaiijou_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemNoJoutaiijou_Stream;
extern WAZA_ItemNoJoutaiijou_Stream WAZA_ItemNoJoutaiijou;

typedef struct WAZA_ItemNoJoutaiijou2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDITION_GAUGE command002;
    Seq_MESSAGE_TBL command003;
    Seq_MESSAGE_WAIT command004;
    Seq_EFFECT_WAIT command005;
    Seq_KILLITEM command006;
    Seq_SEQRET command007;
} WAZA_ItemNoJoutaiijou2_Stream;
extern WAZA_ItemNoJoutaiijou2_Stream WAZA_ItemNoJoutaiijou2;

typedef struct WAZA_ItemAbiKaifuku_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemAbiKaifuku_Stream;
extern WAZA_ItemAbiKaifuku_Stream WAZA_ItemAbiKaifuku;

typedef struct WAZA_ItemAbiKaifuku2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_KILLITEM command005;
    Seq_SEQRET command006;
} WAZA_ItemAbiKaifuku2_Stream;
extern WAZA_ItemAbiKaifuku2_Stream WAZA_ItemAbiKaifuku2;

typedef struct WAZA_ItemHPKaifuku_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_KILLITEM command008;
    Seq_SEQEND command009;
} WAZA_ItemHPKaifuku_Stream;
extern WAZA_ItemHPKaifuku_Stream WAZA_ItemHPKaifuku;

typedef struct WAZA_ItemPPKaifuku_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_KILLITEM command005;
    Seq_SEQEND command006;
} WAZA_ItemPPKaifuku_Stream;
extern WAZA_ItemPPKaifuku_Stream WAZA_ItemPPKaifuku;

typedef struct WAZA_ItemHPKaifukuEveryTurn_Stream {
    Seq_GOSUB command000;
    Seq_SEQEND command001;
} WAZA_ItemHPKaifukuEveryTurn_Stream;
extern WAZA_ItemHPKaifukuEveryTurn_Stream WAZA_ItemHPKaifukuEveryTurn;

typedef struct WAZA_ItemHPKaifukuEveryTurn2_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_EFFECT_WAIT command007;
    Seq_SEQRET command008;
} WAZA_ItemHPKaifukuEveryTurn2_Stream;
extern WAZA_ItemHPKaifukuEveryTurn2_Stream WAZA_ItemHPKaifukuEveryTurn2;

typedef struct WAZA_ItemHPKaifukuKonran_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_SET32BIT command002;
    Seq_HP_DEC command003;
    Seq_MESSAGE command004;
    Seq_MESSAGE_WAIT command005;
    Seq_HP_DEC_WAIT command006;
    Seq_MESSAGE command007;
    Seq_MESSAGE_WAIT command008;
    Seq_EFFECT_WAIT command009;
    Seq_SETVALUE command010;
    Seq_TSUIKA_DIRECT_ACT command011;
    Seq_KILLITEM command012;
    Seq_SEQEND command013;
} WAZA_ItemHPKaifukuKonran_Stream;
extern WAZA_ItemHPKaifukuKonran_Stream WAZA_ItemHPKaifukuKonran;

typedef struct WAZA_ItemCondUp_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_CONDCHG command002;
    Seq_SETVALUE command003;
    Seq_GOSUB command004;
    Seq_KILLITEM command005;
    Seq_SEQEND command006;
} WAZA_ItemCondUp_Stream;
extern WAZA_ItemCondUp_Stream WAZA_ItemCondUp;

typedef struct WAZA_ItemCriticalUp_Stream {
    Seq_FIGHT_EFFECT command000;
    Seq_EFFECT_WAIT command001;
    Seq_MESSAGE command002;
    Seq_MESSAGE_WAIT command003;
    Seq_EFFECT_WAIT command004;
    Seq_KILLITEM command005;
    Seq_SEQEND command006;
} WAZA_ItemCriticalUp_Stream;
extern WAZA_ItemCriticalUp_Stream WAZA_ItemCriticalUp;

typedef struct WAZA_ItemKoraeta_Stream {
    Seq_MESSAGE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQRET command002;
} WAZA_ItemKoraeta_Stream;
extern WAZA_ItemKoraeta_Stream WAZA_ItemKoraeta;

typedef struct WAZA_DouguAlert_Stream {
    Seq_ALERT_MESSAGE command000;
    Seq_ALERTEND command001;
} WAZA_DouguAlert_Stream;
extern WAZA_DouguAlert_Stream WAZA_DouguAlert;

typedef struct WAZA_BlankMsg_Stream {
    Seq_SETVALUE command000;
    Seq_MESSAGE_WAIT command001;
    Seq_SEQRET command002;
} WAZA_BlankMsg_Stream;
extern WAZA_BlankMsg_Stream WAZA_BlankMsg;

typedef struct WAZA_Null_Stream {
    Seq_SEQEND command000;
} WAZA_Null_Stream;
extern WAZA_Null_Stream WAZA_Null;

typedef struct WazaEffectTbl_Stream {
    u8* entries[218];
} WazaEffectTbl_Stream;
extern WazaEffectTbl_Stream WazaEffectTbl;

extern u8 AddDokuMsgTbl[];
extern u8 AddKooriMsgTbl[];
extern u8 AddMahiMsgTbl[];
extern u8 AddNemuriMsgTbl[];
extern u8 AddYakedoMsgTbl[];
extern u8 AmagoiKeepMsgTbl[];
extern u8 AppearMsgTbl[];
extern u8 AsobiMsgTbl[];
extern u8 CondDownMsgTbl[];
extern u8 CondUpMsgTbl[];
extern u8 DarkRemoveMsgTbl[];
extern u8 EscapeNGMsgTbl[];
extern u8 HenshinMsgTbl[];
extern u8 IchigekiMsgTbl[];
extern u8 IrekaeMsgTbl[];
extern u8 ItemMultiRecoverTbl[];
extern u8 IyashiNoSuzuMsgTbl[];
extern u8 JuunanMsgTbl[];
extern u8 KiaidameMsgTbl[];
extern u8 MamoruMsgTbl[];
extern u8 MeltMsgTbl[];
extern u8 MenekiMsgTbl[];
extern u8 MigawariMsgTbl[];
extern u8 MiraiyochiMsgTbl[];
extern u8 MizunobeeruMsgTbl[];
extern u8 MoraibiMsgTbl[];
extern u8 NamaketeiruMsgTbl[];
extern u8 NemuruMsgTbl[];
extern u8 NomikomuMsgTbl[];
extern u8 ReflecMsgTbl[];
extern u8 SawaguMsgTbl[];
extern u8 ServerStatusFlag[];
extern u8 ServerWork[];
extern u8 ShimeMsgTbl[];
extern u8 ShiroikiriMsgTbl[];
extern u8 SleepMsgTbl[];
extern u8 SleepNGMsgTbl[];
extern u8 SuitoriMsgTbl[];
extern u8 TakuwaeruMsgTbl[];
extern u8 TameMsgTbl[];
extern u8 TenkouMsgTbl[];
extern u8 WazaDamage[];
extern u8 WeatherDamageEndMsgTbl[];
extern u8 WeatherDamageMsgTbl[];
extern u8 WeatherKeepMsgTbl[];
extern u8 YadorigiMsgTbl[];
extern u8 fight_seq_banme_buff[];
extern u8 fight_seq_banme_max[];
extern u8 fight_seq_cond_chg_multi[];
extern u8 fight_seq_fightout_pokemon_ptr[];
extern u8 fight_seq_fightout_pokemon_ptr2[];
extern u8 fight_seq_gaman_damage[];
extern u8 fight_seq_oiuchiflag[];
extern u8 fight_seq_renzoku_count[];
extern u8 fight_seq_server_work3_temp[];
extern u8 fight_seq_tame_msg[];
extern u8 fight_seq_triple_kick_pow[];
extern u8 fight_seq_uchar_buff[];
extern u8 fight_seq_uchar_buff2[];
extern u8 fight_seq_ulong_buff[];
extern u8 fight_seq_ushort_buff[];
extern u8 fight_seq_value_20[];
extern u8 fight_seq_value_40[];
extern u8 fight_seq_wkc_work[];
extern u8 joutai_data_null[];
extern u8 joutai_data_waza_batugun[];
extern u8 joutai_data_waza_imahitotu[];
extern u8 joutai_data_waza_koukanai[];
extern u8 joutai_data_waza_nohit[];
extern u8 joutai_data_waza_umakukimaran[];

/* The retail labels below are source-relative aliases supplied by the LCF. */
typedef struct FightWazaCommandStreams {
    lbl_80414090_Stream lbl_80414090;
    lbl_804140DE_Stream lbl_804140DE;
    lbl_804140DF_Stream lbl_804140DF;
    WAZA_HitCalc_Stream WAZA_HitCalc;
    WAZA_HitCalcOnly_Stream WAZA_HitCalcOnly;
    WAZA_Hit_Stream WAZA_Hit;
    WAZA_WazaEnd_Stream WAZA_WazaEnd;
    lbl_80414119_Stream lbl_80414119;
    WAZA_NormalNohit_Stream WAZA_NormalNohit;
    WAZA_NormalNohitWait_Stream WAZA_NormalNohitWait;
    WAZA_NormalNohit2_Stream WAZA_NormalNohit2;
    lbl_8041418B_Stream lbl_8041418B;
    lbl_804141A4_Stream lbl_804141A4;
    lbl_80414228_Stream lbl_80414228;
    lbl_80414254_Stream lbl_80414254;
    lbl_804142C2_Stream lbl_804142C2;
    lbl_804142C5_Stream lbl_804142C5;
    lbl_8041436A_Stream lbl_8041436A;
    lbl_804143D0_Stream lbl_804143D0;
    lbl_80414439_Stream lbl_80414439;
    lbl_8041443A_Stream lbl_8041443A;
    WAZA_CondUpMsg_Stream WAZA_CondUpMsg;
    WAZA_CondUpTsuikaMsg_Stream WAZA_CondUpTsuikaMsg;
    lbl_804144CD_Stream lbl_804144CD;
    WAZA_CondDownMsg_Stream WAZA_CondDownMsg;
    WAZA_CondDownTsuikaMsg_Stream WAZA_CondDownTsuikaMsg;
    lbl_804145CD_Stream lbl_804145CD;
    lbl_8041466D_Stream lbl_8041466D;
    lbl_80414685_Stream lbl_80414685;
    lbl_804147A4_Stream lbl_804147A4;
    lbl_804148ED_Stream lbl_804148ED;
    lbl_80414930_Stream lbl_80414930;
    lbl_80414B70_Stream lbl_80414B70;
    WAZA_Handou_Stream WAZA_Handou;
    lbl_804151FD_Stream lbl_804151FD;
    lbl_804152CC_Stream lbl_804152CC;
    lbl_804152F2_Stream lbl_804152F2;
    lbl_804153ED_Stream lbl_804153ED;
    lbl_80415438_Stream lbl_80415438;
    lbl_8041544C_Stream lbl_8041544C;
    lbl_80415460_Stream lbl_80415460;
    lbl_804154A3_Stream lbl_804154A3;
    lbl_804155CE_Stream lbl_804155CE;
    lbl_80415615_Stream lbl_80415615;
    lbl_8041566B_Stream lbl_8041566B;
    lbl_80415692_Stream lbl_80415692;
    lbl_804157C8_Stream lbl_804157C8;
    lbl_80415A75_Stream lbl_80415A75;
    lbl_80415BBD_Stream lbl_80415BBD;
    lbl_80415BC9_Stream lbl_80415BC9;
    lbl_80415C14_Stream lbl_80415C14;
    WAZA_Kaifuku_Stream WAZA_Kaifuku;
    WAZA_Mantan_Stream WAZA_Mantan;
    lbl_80415C91_Stream lbl_80415C91;
    WAZA_Umakukimaran_Stream WAZA_Umakukimaran;
    lbl_80415CC6_Stream lbl_80415CC6;
    lbl_80415D09_Stream lbl_80415D09;
    lbl_80415F20_Stream lbl_80415F20;
    lbl_80415F43_Stream lbl_80415F43;
    lbl_80415FF9_Stream lbl_80415FF9;
    WAZA_ShizennochikaraHitMsg_Stream WAZA_ShizennochikaraHitMsg;
    lbl_804162A5_Stream lbl_804162A5;
    lbl_8041651D_Stream lbl_8041651D;
    lbl_80416526_Stream lbl_80416526;
    lbl_8041656D_Stream lbl_8041656D;
    lbl_80416633_Stream lbl_80416633;
    lbl_80416660_Stream lbl_80416660;
    lbl_804167B0_Stream lbl_804167B0;
    lbl_804167CF_Stream lbl_804167CF;
    lbl_804167D9_Stream lbl_804167D9;
    lbl_80416847_Stream lbl_80416847;
    WAZA_KizetsuA_Stream WAZA_KizetsuA;
    WAZA_KizetsuD_Stream WAZA_KizetsuD;
    WAZA_KizetsuK_Stream WAZA_KizetsuK;
    WAZA_GetEXP_Stream WAZA_GetEXP;
    WAZA_LevelUp_Stream WAZA_LevelUp;
    lbl_804169D6_Stream lbl_804169D6;
    lbl_804169E7_Stream lbl_804169E7;
    WAZA_Zenmetsu_Stream WAZA_Zenmetsu;
    WAZA_MineReshuffleStart_Stream WAZA_MineReshuffleStart;
    WAZA_ZenmetsuEnd_Stream WAZA_ZenmetsuEnd;
    WAZA_OkodukaiCheck_Stream WAZA_OkodukaiCheck;
    WAZA_KobanCheck_Stream WAZA_KobanCheck;
    WAZA_TrainerWin_Stream WAZA_TrainerWin;
    WAZA_Win_Stream WAZA_Win;
    WAZA_Lose_Stream WAZA_Lose;
    WAZA_TuushinWin_Stream WAZA_TuushinWin;
    WAZA_BattleTowerWin_Stream WAZA_BattleTowerWin;
    WAZA_ItemEscape_Stream WAZA_ItemEscape;
    WAZA_SpeabiEscape_Stream WAZA_SpeabiEscape;
    WAZA_Escape_Stream WAZA_Escape;
    WAZA_EnemyEscape_Stream WAZA_EnemyEscape;
    WAZA_TrainerEscape_Stream WAZA_TrainerEscape;
    WAZA_EscapeNG_Stream WAZA_EscapeNG;
    WAZA_EscapeNG2_Stream WAZA_EscapeNG2;
    WAZA_SafariBallThrowNG_Stream WAZA_SafariBallThrowNG;
    WAZA_PokeReshuffle_Stream WAZA_PokeReshuffle;
    lbl_80416B06_Stream lbl_80416B06;
    WAZA_Wait_Stream WAZA_Wait;
    WAZA_WeatherDamage_Stream WAZA_WeatherDamage;
    WAZA_WeatherDamageEnd_Stream WAZA_WeatherDamageEnd;
    WAZA_Amefuri_Stream WAZA_Amefuri;
    WAZA_Hare_Stream WAZA_Hare;
    WAZA_HareEnd_Stream WAZA_HareEnd;
    WAZA_FieldWeather_Stream WAZA_FieldWeather;
    lbl_80416D9B_Stream lbl_80416D9B;
    WAZA_ReflecEnd_Stream WAZA_ReflecEnd;
    WAZA_Shinpi_Stream WAZA_Shinpi;
    WAZA_ShinpiEnd_Stream WAZA_ShinpiEnd;
    WAZA_Yadorigi_Stream WAZA_Yadorigi;
    WAZA_Gaman_Stream WAZA_Gaman;
    WAZA_GamanOff_Stream WAZA_GamanOff;
    WAZA_GamanFaild_Stream WAZA_GamanFaild;
    WAZA_Hukitobashi_Stream WAZA_Hukitobashi;
    WAZA_HukitobashiFightEnd_Stream WAZA_HukitobashiFightEnd;
    WAZA_Shiroikiri_Stream WAZA_Shiroikiri;
    WAZA_Ikari_Stream WAZA_Ikari;
    WAZA_Kanashibari_Stream WAZA_Kanashibari;
    WAZA_KanashibariEnd_Stream WAZA_KanashibariEnd;
    WAZA_EncoreEnd_Stream WAZA_EncoreEnd;
    WAZA_Michidure_Stream WAZA_Michidure;
    WAZA_MakibishiA_Stream WAZA_MakibishiA;
    WAZA_MakibishiD_Stream WAZA_MakibishiD;
    WAZA_MakibishiK_Stream WAZA_MakibishiK;
    lbl_8041708E_Stream lbl_8041708E;
    WAZA_Horobinouta_Stream WAZA_Horobinouta;
    WAZA_Horobinoutaing_Stream WAZA_Horobinoutaing;
    WAZA_Genshinochikara_Stream WAZA_Genshinochikara;
    lbl_80417125_Stream lbl_80417125;
    WAZA_Kousokuspin_Stream WAZA_Kousokuspin;
    WAZA_ShimeEscape_Stream WAZA_ShimeEscape;
    WAZA_YadorigiEscape_Stream WAZA_YadorigiEscape;
    WAZA_MakibishiEscape_Stream WAZA_MakibishiEscape;
    WAZA_Miraiyochi_Stream WAZA_Miraiyochi;
    lbl_804171F9_Stream lbl_804171F9;
    lbl_8041720C_Stream lbl_8041720C;
    WAZA_PPNoneAttack_Stream WAZA_PPNoneAttack;
    WAZA_Chouhatsu2_Stream WAZA_Chouhatsu2;
    WAZA_Negaigoto_Stream WAZA_Negaigoto;
    WAZA_Newoharu_Stream WAZA_Newoharu;
    WAZA_Bakadikara_Stream WAZA_Bakadikara;
    lbl_80417394_Stream lbl_80417394;
    lbl_804173B7_Stream lbl_804173B7;
    WAZA_Hatakiotosu_Stream WAZA_Hatakiotosu;
    WAZA_Huuin_Stream WAZA_Huuin;
    WAZA_Onnen_Stream WAZA_Onnen;
    WAZA_MagicCort_Stream WAZA_MagicCort;
    WAZA_Yokodori_Stream WAZA_Yokodori;
    WAZA_Koraeta_Stream WAZA_Koraeta;
    WAZA_Ichigeki_Stream WAZA_Ichigeki;
    WAZA_OverHeat_Stream WAZA_OverHeat;
    lbl_8041747B_Stream lbl_8041747B;
    WAZA_KiaiPunch_Stream WAZA_KiaiPunch;
    WAZA_Hyper_Stream WAZA_Hyper;
    WAZA_Nemuru_Stream WAZA_Nemuru;
    WAZA_Mezame_Stream WAZA_Mezame;
    WAZA_SawaguMezame_Stream WAZA_SawaguMezame;
    WAZA_Revers_Stream WAZA_Revers;
    WAZA_Dokudoku_Stream WAZA_Dokudoku;
    lbl_80417511_Stream lbl_80417511;
    WAZA_Yakedo_Stream WAZA_Yakedo;
    WAZA_Koori_Stream WAZA_Koori;
    WAZA_Melt_Stream WAZA_Melt;
    WAZA_Melt2_Stream WAZA_Melt2;
    WAZA_Mahi_Stream WAZA_Mahi;
    WAZA_Hirumu_Stream WAZA_Hirumu;
    WAZA_Sawagu_Stream WAZA_Sawagu;
    WAZA_AbareruEnd_Stream WAZA_AbareruEnd;
    WAZA_Konran_Stream WAZA_Konran;
    lbl_804175ED_Stream lbl_804175ED;
    WAZA_KonranEnd_Stream WAZA_KonranEnd;
    WAZA_Nekonikoban_Stream WAZA_Nekonikoban;
    WAZA_Shime_Stream WAZA_Shime;
    WAZA_ShimeEnd_Stream WAZA_ShimeEnd;
    WAZA_Meromero_Stream WAZA_Meromero;
    WAZA_MeromeroNext_Stream WAZA_MeromeroNext;
    WAZA_Akumu_Stream WAZA_Akumu;
    WAZA_Noroi_Stream WAZA_Noroi;
    WAZA_NoMahi_Stream WAZA_NoMahi;
    WAZA_AddNemuri_Stream WAZA_AddNemuri;
    lbl_80417700_Stream lbl_80417700;
    WAZA_AddNemuri2_Stream WAZA_AddNemuri2;
    WAZA_AddDoku_Stream WAZA_AddDoku;
    WAZA_AddYakedo_Stream WAZA_AddYakedo;
    WAZA_AddKoori_Stream WAZA_AddKoori;
    WAZA_AddMahi_Stream WAZA_AddMahi;
    WAZA_AddSawagu_Stream WAZA_AddSawagu;
    WAZA_AddDokudoku_Stream WAZA_AddDokudoku;
    WAZA_AddNekonikoban_Stream WAZA_AddNekonikoban;
    WAZA_AddShime_Stream WAZA_AddShime;
    WAZA_AddKonran_Stream WAZA_AddKonran;
    WAZA_AddHanekaeri_Stream WAZA_AddHanekaeri;
    lbl_80417800_Stream lbl_80417800;
    lbl_80417827_Stream lbl_80417827;
    WAZA_AddDorobou_Stream WAZA_AddDorobou;
    WAZA_Amehurashi_Stream WAZA_Amehurashi;
    WAZA_Sunaokosi_Stream WAZA_Sunaokosi;
    WAZA_Hideri_Stream WAZA_Hideri;
    WAZA_Ikaku_Stream WAZA_Ikaku;
    lbl_80417896_Stream lbl_80417896;
    WAZA_IkakuAct_Stream WAZA_IkakuAct;
    WAZA_IkakuLoop_Stream WAZA_IkakuLoop;
    lbl_804178EB_Stream lbl_804178EB;
    lbl_804178EC_Stream lbl_804178EC;
    WAZA_Trace_Stream WAZA_Trace;
    WAZA_Ameukezara_Stream WAZA_Ameukezara;
    WAZA_Dappi_Stream WAZA_Dappi;
    WAZA_Kasokusouti_Stream WAZA_Kasokusouti;
    WAZA_Tenkiya_Stream WAZA_Tenkiya;
    WAZA_Tenkiya2_Stream WAZA_Tenkiya2;
    WAZA_Hiraishin_Stream WAZA_Hiraishin;
    WAZA_TyosuiPPDec_Stream WAZA_TyosuiPPDec;
    WAZA_Tyosui_Stream WAZA_Tyosui;
    WAZA_NOKaifukuPPDec_Stream WAZA_NOKaifukuPPDec;
    WAZA_NOKaifuku_Stream WAZA_NOKaifuku;
    WAZA_MoraibiPPDec_Stream WAZA_MoraibiPPDec;
    WAZA_Moraibi_Stream WAZA_Moraibi;
    WAZA_Ganzyou_Stream WAZA_Ganzyou;
    WAZA_Shimerike_Stream WAZA_Shimerike;
    lbl_80417A7F_Stream lbl_80417A7F;
    WAZA_ClearBody_Stream WAZA_ClearBody;
    WAZA_Mizunobeeru_Stream WAZA_Mizunobeeru;
    WAZA_Juunan_Stream WAZA_Juunan;
    WAZA_Meneki_Stream WAZA_Meneki;
    WAZA_Donkan_Stream WAZA_Donkan;
    WAZA_Seisinryoku_Stream WAZA_Seisinryoku;
    WAZA_Mypace_Stream WAZA_Mypace;
    WAZA_Bouon_Stream WAZA_Bouon;
    WAZA_Kairikibasami_Stream WAZA_Kairikibasami;
    WAZA_Nentyaku_Stream WAZA_Nentyaku;
    WAZA_Nentyaku2_Stream WAZA_Nentyaku2;
    WAZA_Hensyoku_Stream WAZA_Hensyoku;
    WAZA_Samehada_Stream WAZA_Samehada;
    WAZA_Honoonokarada_Stream WAZA_Honoonokarada;
    WAZA_MeromeroBody_Stream WAZA_MeromeroBody;
    WAZA_Sinkuro_Stream WAZA_Sinkuro;
    WAZA_SpeabiNoJoutaiijou_Stream WAZA_SpeabiNoJoutaiijou;
    WAZA_OrderIgnoreSleep_Stream WAZA_OrderIgnoreSleep;
    WAZA_OrderIgnore_Stream WAZA_OrderIgnore;
    WAZA_Namakeru_Stream WAZA_Namakeru;
    WAZA_Hirune_Stream WAZA_Hirune;
    WAZA_OwnAttack_Stream WAZA_OwnAttack;
    WAZA_HyperOrderIgnore_Stream WAZA_HyperOrderIgnore;
    WAZA_HyperOwnAttack_Stream WAZA_HyperOwnAttack;
    WAZA_HyperPost_Stream WAZA_HyperPost;
    WAZA_HyperModoru_Stream WAZA_HyperModoru;
    WAZA_MigawariKizetsu_Stream WAZA_MigawariKizetsu;
    WAZA_ItemNoMahi_Stream WAZA_ItemNoMahi;
    WAZA_ItemNoMahi2_Stream WAZA_ItemNoMahi2;
    WAZA_ItemNoDoku_Stream WAZA_ItemNoDoku;
    WAZA_ItemNoDoku2_Stream WAZA_ItemNoDoku2;
    WAZA_ItemNoYakedo_Stream WAZA_ItemNoYakedo;
    WAZA_ItemNoYakedo2_Stream WAZA_ItemNoYakedo2;
    WAZA_ItemNoKoori_Stream WAZA_ItemNoKoori;
    WAZA_ItemNoKoori2_Stream WAZA_ItemNoKoori2;
    WAZA_ItemNoNemuri_Stream WAZA_ItemNoNemuri;
    WAZA_ItemNoNemuri2_Stream WAZA_ItemNoNemuri2;
    WAZA_ItemNoKonran_Stream WAZA_ItemNoKonran;
    WAZA_ItemNoKonran2_Stream WAZA_ItemNoKonran2;
    WAZA_ItemNoJoutaiijou_Stream WAZA_ItemNoJoutaiijou;
    WAZA_ItemNoJoutaiijou2_Stream WAZA_ItemNoJoutaiijou2;
    WAZA_ItemAbiKaifuku_Stream WAZA_ItemAbiKaifuku;
    WAZA_ItemAbiKaifuku2_Stream WAZA_ItemAbiKaifuku2;
    WAZA_ItemHPKaifuku_Stream WAZA_ItemHPKaifuku;
    WAZA_ItemPPKaifuku_Stream WAZA_ItemPPKaifuku;
    WAZA_ItemHPKaifukuEveryTurn_Stream WAZA_ItemHPKaifukuEveryTurn;
    WAZA_ItemHPKaifukuEveryTurn2_Stream WAZA_ItemHPKaifukuEveryTurn2;
    WAZA_ItemHPKaifukuKonran_Stream WAZA_ItemHPKaifukuKonran;
    WAZA_ItemCondUp_Stream WAZA_ItemCondUp;
    WAZA_ItemCriticalUp_Stream WAZA_ItemCriticalUp;
    WAZA_ItemKoraeta_Stream WAZA_ItemKoraeta;
    WAZA_DouguAlert_Stream WAZA_DouguAlert;
    WAZA_BlankMsg_Stream WAZA_BlankMsg;
    WAZA_Null_Stream WAZA_Null;
    WazaEffectTbl_Stream WazaEffectTbl;
} FightWazaCommandStreams;

typedef char WazaOffset_lbl_80414090[(offsetof(FightWazaCommandStreams, lbl_80414090) == 0x0) ? 1 : -1];
typedef char WazaSize_lbl_80414090[(sizeof(lbl_80414090_Stream) == 0x4E) ? 1 : -1];
typedef char WazaOffset_lbl_804140DE[(offsetof(FightWazaCommandStreams, lbl_804140DE) == 0x4E) ? 1 : -1];
typedef char WazaSize_lbl_804140DE[(sizeof(lbl_804140DE_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_lbl_804140DF[(offsetof(FightWazaCommandStreams, lbl_804140DF) == 0x4F) ? 1 : -1];
typedef char WazaSize_lbl_804140DF[(sizeof(lbl_804140DF_Stream) == 0x7) ? 1 : -1];
typedef char WazaOffset_WAZA_HitCalc[(offsetof(FightWazaCommandStreams, WAZA_HitCalc) == 0x56) ? 1 : -1];
typedef char WazaSize_WAZA_HitCalc[(sizeof(WAZA_HitCalc_Stream) == 0x2) ? 1 : -1];
typedef char WazaOffset_WAZA_HitCalcOnly[(offsetof(FightWazaCommandStreams, WAZA_HitCalcOnly) == 0x58) ? 1 : -1];
typedef char WazaSize_WAZA_HitCalcOnly[(sizeof(WAZA_HitCalcOnly_Stream) == 0x4) ? 1 : -1];
typedef char WazaOffset_WAZA_Hit[(offsetof(FightWazaCommandStreams, WAZA_Hit) == 0x5C) ? 1 : -1];
typedef char WazaSize_WAZA_Hit[(sizeof(WAZA_Hit_Stream) == 0x23) ? 1 : -1];
typedef char WazaOffset_WAZA_WazaEnd[(offsetof(FightWazaCommandStreams, WAZA_WazaEnd) == 0x7F) ? 1 : -1];
typedef char WazaSize_WAZA_WazaEnd[(sizeof(WAZA_WazaEnd_Stream) == 0xA) ? 1 : -1];
typedef char WazaOffset_lbl_80414119[(offsetof(FightWazaCommandStreams, lbl_80414119) == 0x89) ? 1 : -1];
typedef char WazaSize_lbl_80414119[(sizeof(lbl_80414119_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_NormalNohit[(offsetof(FightWazaCommandStreams, WAZA_NormalNohit) == 0x9D) ? 1 : -1];
typedef char WazaSize_WAZA_NormalNohit[(sizeof(WAZA_NormalNohit_Stream) == 0x2) ? 1 : -1];
typedef char WazaOffset_WAZA_NormalNohitWait[(offsetof(FightWazaCommandStreams, WAZA_NormalNohitWait) == 0x9F) ? 1 : -1];
typedef char WazaSize_WAZA_NormalNohitWait[(sizeof(WAZA_NormalNohitWait_Stream) == 0x3) ? 1 : -1];
typedef char WazaOffset_WAZA_NormalNohit2[(offsetof(FightWazaCommandStreams, WAZA_NormalNohit2) == 0xA2) ? 1 : -1];
typedef char WazaSize_WAZA_NormalNohit2[(sizeof(WAZA_NormalNohit2_Stream) == 0x59) ? 1 : -1];
typedef char WazaOffset_lbl_8041418B[(offsetof(FightWazaCommandStreams, lbl_8041418B) == 0xFB) ? 1 : -1];
typedef char WazaSize_lbl_8041418B[(sizeof(lbl_8041418B_Stream) == 0x19) ? 1 : -1];
typedef char WazaOffset_lbl_804141A4[(offsetof(FightWazaCommandStreams, lbl_804141A4) == 0x114) ? 1 : -1];
typedef char WazaSize_lbl_804141A4[(sizeof(lbl_804141A4_Stream) == 0x84) ? 1 : -1];
typedef char WazaOffset_lbl_80414228[(offsetof(FightWazaCommandStreams, lbl_80414228) == 0x198) ? 1 : -1];
typedef char WazaSize_lbl_80414228[(sizeof(lbl_80414228_Stream) == 0x2C) ? 1 : -1];
typedef char WazaOffset_lbl_80414254[(offsetof(FightWazaCommandStreams, lbl_80414254) == 0x1C4) ? 1 : -1];
typedef char WazaSize_lbl_80414254[(sizeof(lbl_80414254_Stream) == 0x6E) ? 1 : -1];
typedef char WazaOffset_lbl_804142C2[(offsetof(FightWazaCommandStreams, lbl_804142C2) == 0x232) ? 1 : -1];
typedef char WazaSize_lbl_804142C2[(sizeof(lbl_804142C2_Stream) == 0x3) ? 1 : -1];
typedef char WazaOffset_lbl_804142C5[(offsetof(FightWazaCommandStreams, lbl_804142C5) == 0x235) ? 1 : -1];
typedef char WazaSize_lbl_804142C5[(sizeof(lbl_804142C5_Stream) == 0xA5) ? 1 : -1];
typedef char WazaOffset_lbl_8041436A[(offsetof(FightWazaCommandStreams, lbl_8041436A) == 0x2DA) ? 1 : -1];
typedef char WazaSize_lbl_8041436A[(sizeof(lbl_8041436A_Stream) == 0x66) ? 1 : -1];
typedef char WazaOffset_lbl_804143D0[(offsetof(FightWazaCommandStreams, lbl_804143D0) == 0x340) ? 1 : -1];
typedef char WazaSize_lbl_804143D0[(sizeof(lbl_804143D0_Stream) == 0x69) ? 1 : -1];
typedef char WazaOffset_lbl_80414439[(offsetof(FightWazaCommandStreams, lbl_80414439) == 0x3A9) ? 1 : -1];
typedef char WazaSize_lbl_80414439[(sizeof(lbl_80414439_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_lbl_8041443A[(offsetof(FightWazaCommandStreams, lbl_8041443A) == 0x3AA) ? 1 : -1];
typedef char WazaSize_lbl_8041443A[(sizeof(lbl_8041443A_Stream) == 0x28) ? 1 : -1];
typedef char WazaOffset_WAZA_CondUpMsg[(offsetof(FightWazaCommandStreams, WAZA_CondUpMsg) == 0x3D2) ? 1 : -1];
typedef char WazaSize_WAZA_CondUpMsg[(sizeof(WAZA_CondUpMsg_Stream) == 0xF) ? 1 : -1];
typedef char WazaOffset_WAZA_CondUpTsuikaMsg[(offsetof(FightWazaCommandStreams, WAZA_CondUpTsuikaMsg) == 0x3E1) ? 1 : -1];
typedef char WazaSize_WAZA_CondUpTsuikaMsg[(sizeof(WAZA_CondUpTsuikaMsg_Stream) == 0x5C) ? 1 : -1];
typedef char WazaOffset_lbl_804144CD[(offsetof(FightWazaCommandStreams, lbl_804144CD) == 0x43D) ? 1 : -1];
typedef char WazaSize_lbl_804144CD[(sizeof(lbl_804144CD_Stream) == 0x51) ? 1 : -1];
typedef char WazaOffset_WAZA_CondDownMsg[(offsetof(FightWazaCommandStreams, WAZA_CondDownMsg) == 0x48E) ? 1 : -1];
typedef char WazaSize_WAZA_CondDownMsg[(sizeof(WAZA_CondDownMsg_Stream) == 0xF) ? 1 : -1];
typedef char WazaOffset_WAZA_CondDownTsuikaMsg[(offsetof(FightWazaCommandStreams, WAZA_CondDownTsuikaMsg) == 0x49D) ? 1 : -1];
typedef char WazaSize_WAZA_CondDownTsuikaMsg[(sizeof(WAZA_CondDownTsuikaMsg_Stream) == 0xA0) ? 1 : -1];
typedef char WazaOffset_lbl_804145CD[(offsetof(FightWazaCommandStreams, lbl_804145CD) == 0x53D) ? 1 : -1];
typedef char WazaSize_lbl_804145CD[(sizeof(lbl_804145CD_Stream) == 0xA0) ? 1 : -1];
typedef char WazaOffset_lbl_8041466D[(offsetof(FightWazaCommandStreams, lbl_8041466D) == 0x5DD) ? 1 : -1];
typedef char WazaSize_lbl_8041466D[(sizeof(lbl_8041466D_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_lbl_80414685[(offsetof(FightWazaCommandStreams, lbl_80414685) == 0x5F5) ? 1 : -1];
typedef char WazaSize_lbl_80414685[(sizeof(lbl_80414685_Stream) == 0x11F) ? 1 : -1];
typedef char WazaOffset_lbl_804147A4[(offsetof(FightWazaCommandStreams, lbl_804147A4) == 0x714) ? 1 : -1];
typedef char WazaSize_lbl_804147A4[(sizeof(lbl_804147A4_Stream) == 0x149) ? 1 : -1];
typedef char WazaOffset_lbl_804148ED[(offsetof(FightWazaCommandStreams, lbl_804148ED) == 0x85D) ? 1 : -1];
typedef char WazaSize_lbl_804148ED[(sizeof(lbl_804148ED_Stream) == 0x43) ? 1 : -1];
typedef char WazaOffset_lbl_80414930[(offsetof(FightWazaCommandStreams, lbl_80414930) == 0x8A0) ? 1 : -1];
typedef char WazaSize_lbl_80414930[(sizeof(lbl_80414930_Stream) == 0x240) ? 1 : -1];
typedef char WazaOffset_lbl_80414B70[(offsetof(FightWazaCommandStreams, lbl_80414B70) == 0xAE0) ? 1 : -1];
typedef char WazaSize_lbl_80414B70[(sizeof(lbl_80414B70_Stream) == 0x2EF) ? 1 : -1];
typedef char WazaOffset_WAZA_Handou[(offsetof(FightWazaCommandStreams, WAZA_Handou) == 0xDCF) ? 1 : -1];
typedef char WazaSize_WAZA_Handou[(sizeof(WAZA_Handou_Stream) == 0x39E) ? 1 : -1];
typedef char WazaOffset_lbl_804151FD[(offsetof(FightWazaCommandStreams, lbl_804151FD) == 0x116D) ? 1 : -1];
typedef char WazaSize_lbl_804151FD[(sizeof(lbl_804151FD_Stream) == 0xCF) ? 1 : -1];
typedef char WazaOffset_lbl_804152CC[(offsetof(FightWazaCommandStreams, lbl_804152CC) == 0x123C) ? 1 : -1];
typedef char WazaSize_lbl_804152CC[(sizeof(lbl_804152CC_Stream) == 0x26) ? 1 : -1];
typedef char WazaOffset_lbl_804152F2[(offsetof(FightWazaCommandStreams, lbl_804152F2) == 0x1262) ? 1 : -1];
typedef char WazaSize_lbl_804152F2[(sizeof(lbl_804152F2_Stream) == 0xFB) ? 1 : -1];
typedef char WazaOffset_lbl_804153ED[(offsetof(FightWazaCommandStreams, lbl_804153ED) == 0x135D) ? 1 : -1];
typedef char WazaSize_lbl_804153ED[(sizeof(lbl_804153ED_Stream) == 0x4B) ? 1 : -1];
typedef char WazaOffset_lbl_80415438[(offsetof(FightWazaCommandStreams, lbl_80415438) == 0x13A8) ? 1 : -1];
typedef char WazaSize_lbl_80415438[(sizeof(lbl_80415438_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_lbl_8041544C[(offsetof(FightWazaCommandStreams, lbl_8041544C) == 0x13BC) ? 1 : -1];
typedef char WazaSize_lbl_8041544C[(sizeof(lbl_8041544C_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_lbl_80415460[(offsetof(FightWazaCommandStreams, lbl_80415460) == 0x13D0) ? 1 : -1];
typedef char WazaSize_lbl_80415460[(sizeof(lbl_80415460_Stream) == 0x43) ? 1 : -1];
typedef char WazaOffset_lbl_804154A3[(offsetof(FightWazaCommandStreams, lbl_804154A3) == 0x1413) ? 1 : -1];
typedef char WazaSize_lbl_804154A3[(sizeof(lbl_804154A3_Stream) == 0x12B) ? 1 : -1];
typedef char WazaOffset_lbl_804155CE[(offsetof(FightWazaCommandStreams, lbl_804155CE) == 0x153E) ? 1 : -1];
typedef char WazaSize_lbl_804155CE[(sizeof(lbl_804155CE_Stream) == 0x47) ? 1 : -1];
typedef char WazaOffset_lbl_80415615[(offsetof(FightWazaCommandStreams, lbl_80415615) == 0x1585) ? 1 : -1];
typedef char WazaSize_lbl_80415615[(sizeof(lbl_80415615_Stream) == 0x56) ? 1 : -1];
typedef char WazaOffset_lbl_8041566B[(offsetof(FightWazaCommandStreams, lbl_8041566B) == 0x15DB) ? 1 : -1];
typedef char WazaSize_lbl_8041566B[(sizeof(lbl_8041566B_Stream) == 0x27) ? 1 : -1];
typedef char WazaOffset_lbl_80415692[(offsetof(FightWazaCommandStreams, lbl_80415692) == 0x1602) ? 1 : -1];
typedef char WazaSize_lbl_80415692[(sizeof(lbl_80415692_Stream) == 0x136) ? 1 : -1];
typedef char WazaOffset_lbl_804157C8[(offsetof(FightWazaCommandStreams, lbl_804157C8) == 0x1738) ? 1 : -1];
typedef char WazaSize_lbl_804157C8[(sizeof(lbl_804157C8_Stream) == 0x2AD) ? 1 : -1];
typedef char WazaOffset_lbl_80415A75[(offsetof(FightWazaCommandStreams, lbl_80415A75) == 0x19E5) ? 1 : -1];
typedef char WazaSize_lbl_80415A75[(sizeof(lbl_80415A75_Stream) == 0x148) ? 1 : -1];
typedef char WazaOffset_lbl_80415BBD[(offsetof(FightWazaCommandStreams, lbl_80415BBD) == 0x1B2D) ? 1 : -1];
typedef char WazaSize_lbl_80415BBD[(sizeof(lbl_80415BBD_Stream) == 0xC) ? 1 : -1];
typedef char WazaOffset_lbl_80415BC9[(offsetof(FightWazaCommandStreams, lbl_80415BC9) == 0x1B39) ? 1 : -1];
typedef char WazaSize_lbl_80415BC9[(sizeof(lbl_80415BC9_Stream) == 0x4B) ? 1 : -1];
typedef char WazaOffset_lbl_80415C14[(offsetof(FightWazaCommandStreams, lbl_80415C14) == 0x1B84) ? 1 : -1];
typedef char WazaSize_lbl_80415C14[(sizeof(lbl_80415C14_Stream) == 0x32) ? 1 : -1];
typedef char WazaOffset_WAZA_Kaifuku[(offsetof(FightWazaCommandStreams, WAZA_Kaifuku) == 0x1BB6) ? 1 : -1];
typedef char WazaSize_WAZA_Kaifuku[(sizeof(WAZA_Kaifuku_Stream) == 0x21) ? 1 : -1];
typedef char WazaOffset_WAZA_Mantan[(offsetof(FightWazaCommandStreams, WAZA_Mantan) == 0x1BD7) ? 1 : -1];
typedef char WazaSize_WAZA_Mantan[(sizeof(WAZA_Mantan_Stream) == 0x2A) ? 1 : -1];
typedef char WazaOffset_lbl_80415C91[(offsetof(FightWazaCommandStreams, lbl_80415C91) == 0x1C01) ? 1 : -1];
typedef char WazaSize_lbl_80415C91[(sizeof(lbl_80415C91_Stream) == 0x2) ? 1 : -1];
typedef char WazaOffset_WAZA_Umakukimaran[(offsetof(FightWazaCommandStreams, WAZA_Umakukimaran) == 0x1C03) ? 1 : -1];
typedef char WazaSize_WAZA_Umakukimaran[(sizeof(WAZA_Umakukimaran_Stream) == 0x33) ? 1 : -1];
typedef char WazaOffset_lbl_80415CC6[(offsetof(FightWazaCommandStreams, lbl_80415CC6) == 0x1C36) ? 1 : -1];
typedef char WazaSize_lbl_80415CC6[(sizeof(lbl_80415CC6_Stream) == 0x43) ? 1 : -1];
typedef char WazaOffset_lbl_80415D09[(offsetof(FightWazaCommandStreams, lbl_80415D09) == 0x1C79) ? 1 : -1];
typedef char WazaSize_lbl_80415D09[(sizeof(lbl_80415D09_Stream) == 0x217) ? 1 : -1];
typedef char WazaOffset_lbl_80415F20[(offsetof(FightWazaCommandStreams, lbl_80415F20) == 0x1E90) ? 1 : -1];
typedef char WazaSize_lbl_80415F20[(sizeof(lbl_80415F20_Stream) == 0x23) ? 1 : -1];
typedef char WazaOffset_lbl_80415F43[(offsetof(FightWazaCommandStreams, lbl_80415F43) == 0x1EB3) ? 1 : -1];
typedef char WazaSize_lbl_80415F43[(sizeof(lbl_80415F43_Stream) == 0xB6) ? 1 : -1];
typedef char WazaOffset_lbl_80415FF9[(offsetof(FightWazaCommandStreams, lbl_80415FF9) == 0x1F69) ? 1 : -1];
typedef char WazaSize_lbl_80415FF9[(sizeof(lbl_80415FF9_Stream) == 0x3B) ? 1 : -1];
typedef char WazaOffset_WAZA_ShizennochikaraHitMsg[(offsetof(FightWazaCommandStreams, WAZA_ShizennochikaraHitMsg) == 0x1FA4) ? 1 : -1];
typedef char WazaSize_WAZA_ShizennochikaraHitMsg[(sizeof(WAZA_ShizennochikaraHitMsg_Stream) == 0x271) ? 1 : -1];
typedef char WazaOffset_lbl_804162A5[(offsetof(FightWazaCommandStreams, lbl_804162A5) == 0x2215) ? 1 : -1];
typedef char WazaSize_lbl_804162A5[(sizeof(lbl_804162A5_Stream) == 0x278) ? 1 : -1];
typedef char WazaOffset_lbl_8041651D[(offsetof(FightWazaCommandStreams, lbl_8041651D) == 0x248D) ? 1 : -1];
typedef char WazaSize_lbl_8041651D[(sizeof(lbl_8041651D_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_lbl_80416526[(offsetof(FightWazaCommandStreams, lbl_80416526) == 0x2496) ? 1 : -1];
typedef char WazaSize_lbl_80416526[(sizeof(lbl_80416526_Stream) == 0x47) ? 1 : -1];
typedef char WazaOffset_lbl_8041656D[(offsetof(FightWazaCommandStreams, lbl_8041656D) == 0x24DD) ? 1 : -1];
typedef char WazaSize_lbl_8041656D[(sizeof(lbl_8041656D_Stream) == 0xC6) ? 1 : -1];
typedef char WazaOffset_lbl_80416633[(offsetof(FightWazaCommandStreams, lbl_80416633) == 0x25A3) ? 1 : -1];
typedef char WazaSize_lbl_80416633[(sizeof(lbl_80416633_Stream) == 0x2D) ? 1 : -1];
typedef char WazaOffset_lbl_80416660[(offsetof(FightWazaCommandStreams, lbl_80416660) == 0x25D0) ? 1 : -1];
typedef char WazaSize_lbl_80416660[(sizeof(lbl_80416660_Stream) == 0x150) ? 1 : -1];
typedef char WazaOffset_lbl_804167B0[(offsetof(FightWazaCommandStreams, lbl_804167B0) == 0x2720) ? 1 : -1];
typedef char WazaSize_lbl_804167B0[(sizeof(lbl_804167B0_Stream) == 0x1F) ? 1 : -1];
typedef char WazaOffset_lbl_804167CF[(offsetof(FightWazaCommandStreams, lbl_804167CF) == 0x273F) ? 1 : -1];
typedef char WazaSize_lbl_804167CF[(sizeof(lbl_804167CF_Stream) == 0xA) ? 1 : -1];
typedef char WazaOffset_lbl_804167D9[(offsetof(FightWazaCommandStreams, lbl_804167D9) == 0x2749) ? 1 : -1];
typedef char WazaSize_lbl_804167D9[(sizeof(lbl_804167D9_Stream) == 0x6E) ? 1 : -1];
typedef char WazaOffset_lbl_80416847[(offsetof(FightWazaCommandStreams, lbl_80416847) == 0x27B7) ? 1 : -1];
typedef char WazaSize_lbl_80416847[(sizeof(lbl_80416847_Stream) == 0x100) ? 1 : -1];
typedef char WazaOffset_WAZA_KizetsuA[(offsetof(FightWazaCommandStreams, WAZA_KizetsuA) == 0x28B7) ? 1 : -1];
typedef char WazaSize_WAZA_KizetsuA[(sizeof(WAZA_KizetsuA_Stream) == 0xF) ? 1 : -1];
typedef char WazaOffset_WAZA_KizetsuD[(offsetof(FightWazaCommandStreams, WAZA_KizetsuD) == 0x28C6) ? 1 : -1];
typedef char WazaSize_WAZA_KizetsuD[(sizeof(WAZA_KizetsuD_Stream) == 0xF) ? 1 : -1];
typedef char WazaOffset_WAZA_KizetsuK[(offsetof(FightWazaCommandStreams, WAZA_KizetsuK) == 0x28D5) ? 1 : -1];
typedef char WazaSize_WAZA_KizetsuK[(sizeof(WAZA_KizetsuK_Stream) == 0xF) ? 1 : -1];
typedef char WazaOffset_WAZA_GetEXP[(offsetof(FightWazaCommandStreams, WAZA_GetEXP) == 0x28E4) ? 1 : -1];
typedef char WazaSize_WAZA_GetEXP[(sizeof(WAZA_GetEXP_Stream) == 0x3) ? 1 : -1];
typedef char WazaOffset_WAZA_LevelUp[(offsetof(FightWazaCommandStreams, WAZA_LevelUp) == 0x28E7) ? 1 : -1];
typedef char WazaSize_WAZA_LevelUp[(sizeof(WAZA_LevelUp_Stream) == 0x5F) ? 1 : -1];
typedef char WazaOffset_lbl_804169D6[(offsetof(FightWazaCommandStreams, lbl_804169D6) == 0x2946) ? 1 : -1];
typedef char WazaSize_lbl_804169D6[(sizeof(lbl_804169D6_Stream) == 0x11) ? 1 : -1];
typedef char WazaOffset_lbl_804169E7[(offsetof(FightWazaCommandStreams, lbl_804169E7) == 0x2957) ? 1 : -1];
typedef char WazaSize_lbl_804169E7[(sizeof(lbl_804169E7_Stream) == 0x4) ? 1 : -1];
typedef char WazaOffset_WAZA_Zenmetsu[(offsetof(FightWazaCommandStreams, WAZA_Zenmetsu) == 0x295B) ? 1 : -1];
typedef char WazaSize_WAZA_Zenmetsu[(sizeof(WAZA_Zenmetsu_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_MineReshuffleStart[(offsetof(FightWazaCommandStreams, WAZA_MineReshuffleStart) == 0x2961) ? 1 : -1];
typedef char WazaSize_WAZA_MineReshuffleStart[(sizeof(WAZA_MineReshuffleStart_Stream) == 0x62) ? 1 : -1];
typedef char WazaOffset_WAZA_ZenmetsuEnd[(offsetof(FightWazaCommandStreams, WAZA_ZenmetsuEnd) == 0x29C3) ? 1 : -1];
typedef char WazaSize_WAZA_ZenmetsuEnd[(sizeof(WAZA_ZenmetsuEnd_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_WAZA_OkodukaiCheck[(offsetof(FightWazaCommandStreams, WAZA_OkodukaiCheck) == 0x29C4) ? 1 : -1];
typedef char WazaSize_WAZA_OkodukaiCheck[(sizeof(WAZA_OkodukaiCheck_Stream) == 0xE) ? 1 : -1];
typedef char WazaOffset_WAZA_KobanCheck[(offsetof(FightWazaCommandStreams, WAZA_KobanCheck) == 0x29D2) ? 1 : -1];
typedef char WazaSize_WAZA_KobanCheck[(sizeof(WAZA_KobanCheck_Stream) == 0x2) ? 1 : -1];
typedef char WazaOffset_WAZA_TrainerWin[(offsetof(FightWazaCommandStreams, WAZA_TrainerWin) == 0x29D4) ? 1 : -1];
typedef char WazaSize_WAZA_TrainerWin[(sizeof(WAZA_TrainerWin_Stream) == 0x1A) ? 1 : -1];
typedef char WazaOffset_WAZA_Win[(offsetof(FightWazaCommandStreams, WAZA_Win) == 0x29EE) ? 1 : -1];
typedef char WazaSize_WAZA_Win[(sizeof(WAZA_Win_Stream) == 0x3) ? 1 : -1];
typedef char WazaOffset_WAZA_Lose[(offsetof(FightWazaCommandStreams, WAZA_Lose) == 0x29F1) ? 1 : -1];
typedef char WazaSize_WAZA_Lose[(sizeof(WAZA_Lose_Stream) == 0x11) ? 1 : -1];
typedef char WazaOffset_WAZA_TuushinWin[(offsetof(FightWazaCommandStreams, WAZA_TuushinWin) == 0x2A02) ? 1 : -1];
typedef char WazaSize_WAZA_TuushinWin[(sizeof(WAZA_TuushinWin_Stream) == 0xD) ? 1 : -1];
typedef char WazaOffset_WAZA_BattleTowerWin[(offsetof(FightWazaCommandStreams, WAZA_BattleTowerWin) == 0x2A0F) ? 1 : -1];
typedef char WazaSize_WAZA_BattleTowerWin[(sizeof(WAZA_BattleTowerWin_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemEscape[(offsetof(FightWazaCommandStreams, WAZA_ItemEscape) == 0x2A18) ? 1 : -1];
typedef char WazaSize_WAZA_ItemEscape[(sizeof(WAZA_ItemEscape_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_SpeabiEscape[(offsetof(FightWazaCommandStreams, WAZA_SpeabiEscape) == 0x2A2C) ? 1 : -1];
typedef char WazaSize_WAZA_SpeabiEscape[(sizeof(WAZA_SpeabiEscape_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_Escape[(offsetof(FightWazaCommandStreams, WAZA_Escape) == 0x2A35) ? 1 : -1];
typedef char WazaSize_WAZA_Escape[(sizeof(WAZA_Escape_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_EnemyEscape[(offsetof(FightWazaCommandStreams, WAZA_EnemyEscape) == 0x2A3E) ? 1 : -1];
typedef char WazaSize_WAZA_EnemyEscape[(sizeof(WAZA_EnemyEscape_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_TrainerEscape[(offsetof(FightWazaCommandStreams, WAZA_TrainerEscape) == 0x2A47) ? 1 : -1];
typedef char WazaSize_WAZA_TrainerEscape[(sizeof(WAZA_TrainerEscape_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_EscapeNG[(offsetof(FightWazaCommandStreams, WAZA_EscapeNG) == 0x2A4D) ? 1 : -1];
typedef char WazaSize_WAZA_EscapeNG[(sizeof(WAZA_EscapeNG_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_EscapeNG2[(offsetof(FightWazaCommandStreams, WAZA_EscapeNG2) == 0x2A56) ? 1 : -1];
typedef char WazaSize_WAZA_EscapeNG2[(sizeof(WAZA_EscapeNG2_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_SafariBallThrowNG[(offsetof(FightWazaCommandStreams, WAZA_SafariBallThrowNG) == 0x2A5C) ? 1 : -1];
typedef char WazaSize_WAZA_SafariBallThrowNG[(sizeof(WAZA_SafariBallThrowNG_Stream) == 0x4) ? 1 : -1];
typedef char WazaOffset_WAZA_PokeReshuffle[(offsetof(FightWazaCommandStreams, WAZA_PokeReshuffle) == 0x2A60) ? 1 : -1];
typedef char WazaSize_WAZA_PokeReshuffle[(sizeof(WAZA_PokeReshuffle_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_lbl_80416B06[(offsetof(FightWazaCommandStreams, lbl_80416B06) == 0x2A76) ? 1 : -1];
typedef char WazaSize_lbl_80416B06[(sizeof(lbl_80416B06_Stream) == 0xB1) ? 1 : -1];
typedef char WazaOffset_WAZA_Wait[(offsetof(FightWazaCommandStreams, WAZA_Wait) == 0x2B27) ? 1 : -1];
typedef char WazaSize_WAZA_Wait[(sizeof(WAZA_Wait_Stream) == 0x4) ? 1 : -1];
typedef char WazaOffset_WAZA_WeatherDamage[(offsetof(FightWazaCommandStreams, WAZA_WeatherDamage) == 0x2B2B) ? 1 : -1];
typedef char WazaSize_WAZA_WeatherDamage[(sizeof(WAZA_WeatherDamage_Stream) == 0xE5) ? 1 : -1];
typedef char WazaOffset_WAZA_WeatherDamageEnd[(offsetof(FightWazaCommandStreams, WAZA_WeatherDamageEnd) == 0x2C10) ? 1 : -1];
typedef char WazaSize_WAZA_WeatherDamageEnd[(sizeof(WAZA_WeatherDamageEnd_Stream) == 0x12) ? 1 : -1];
typedef char WazaOffset_WAZA_Amefuri[(offsetof(FightWazaCommandStreams, WAZA_Amefuri) == 0x2C22) ? 1 : -1];
typedef char WazaSize_WAZA_Amefuri[(sizeof(WAZA_Amefuri_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_Hare[(offsetof(FightWazaCommandStreams, WAZA_Hare) == 0x2C3F) ? 1 : -1];
typedef char WazaSize_WAZA_Hare[(sizeof(WAZA_Hare_Stream) == 0x12) ? 1 : -1];
typedef char WazaOffset_WAZA_HareEnd[(offsetof(FightWazaCommandStreams, WAZA_HareEnd) == 0x2C51) ? 1 : -1];
typedef char WazaSize_WAZA_HareEnd[(sizeof(WAZA_HareEnd_Stream) == 0x12) ? 1 : -1];
typedef char WazaOffset_WAZA_FieldWeather[(offsetof(FightWazaCommandStreams, WAZA_FieldWeather) == 0x2C63) ? 1 : -1];
typedef char WazaSize_WAZA_FieldWeather[(sizeof(WAZA_FieldWeather_Stream) == 0xA8) ? 1 : -1];
typedef char WazaOffset_lbl_80416D9B[(offsetof(FightWazaCommandStreams, lbl_80416D9B) == 0x2D0B) ? 1 : -1];
typedef char WazaSize_lbl_80416D9B[(sizeof(lbl_80416D9B_Stream) == 0x3) ? 1 : -1];
typedef char WazaOffset_WAZA_ReflecEnd[(offsetof(FightWazaCommandStreams, WAZA_ReflecEnd) == 0x2D0E) ? 1 : -1];
typedef char WazaSize_WAZA_ReflecEnd[(sizeof(WAZA_ReflecEnd_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Shinpi[(offsetof(FightWazaCommandStreams, WAZA_Shinpi) == 0x2D22) ? 1 : -1];
typedef char WazaSize_WAZA_Shinpi[(sizeof(WAZA_Shinpi_Stream) == 0x17) ? 1 : -1];
typedef char WazaOffset_WAZA_ShinpiEnd[(offsetof(FightWazaCommandStreams, WAZA_ShinpiEnd) == 0x2D39) ? 1 : -1];
typedef char WazaSize_WAZA_ShinpiEnd[(sizeof(WAZA_ShinpiEnd_Stream) == 0x17) ? 1 : -1];
typedef char WazaOffset_WAZA_Yadorigi[(offsetof(FightWazaCommandStreams, WAZA_Yadorigi) == 0x2D50) ? 1 : -1];
typedef char WazaSize_WAZA_Yadorigi[(sizeof(WAZA_Yadorigi_Stream) == 0xBA) ? 1 : -1];
typedef char WazaOffset_WAZA_Gaman[(offsetof(FightWazaCommandStreams, WAZA_Gaman) == 0x2E0A) ? 1 : -1];
typedef char WazaSize_WAZA_Gaman[(sizeof(WAZA_Gaman_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_GamanOff[(offsetof(FightWazaCommandStreams, WAZA_GamanOff) == 0x2E22) ? 1 : -1];
typedef char WazaSize_WAZA_GamanOff[(sizeof(WAZA_GamanOff_Stream) == 0x7B) ? 1 : -1];
typedef char WazaOffset_WAZA_GamanFaild[(offsetof(FightWazaCommandStreams, WAZA_GamanFaild) == 0x2E9D) ? 1 : -1];
typedef char WazaSize_WAZA_GamanFaild[(sizeof(WAZA_GamanFaild_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_Hukitobashi[(offsetof(FightWazaCommandStreams, WAZA_Hukitobashi) == 0x2EB5) ? 1 : -1];
typedef char WazaSize_WAZA_Hukitobashi[(sizeof(WAZA_Hukitobashi_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_HukitobashiFightEnd[(offsetof(FightWazaCommandStreams, WAZA_HukitobashiFightEnd) == 0x2ED2) ? 1 : -1];
typedef char WazaSize_WAZA_HukitobashiFightEnd[(sizeof(WAZA_HukitobashiFightEnd_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_Shiroikiri[(offsetof(FightWazaCommandStreams, WAZA_Shiroikiri) == 0x2EDB) ? 1 : -1];
typedef char WazaSize_WAZA_Shiroikiri[(sizeof(WAZA_Shiroikiri_Stream) == 0x17) ? 1 : -1];
typedef char WazaOffset_WAZA_Ikari[(offsetof(FightWazaCommandStreams, WAZA_Ikari) == 0x2EF2) ? 1 : -1];
typedef char WazaSize_WAZA_Ikari[(sizeof(WAZA_Ikari_Stream) == 0x12) ? 1 : -1];
typedef char WazaOffset_WAZA_Kanashibari[(offsetof(FightWazaCommandStreams, WAZA_Kanashibari) == 0x2F04) ? 1 : -1];
typedef char WazaSize_WAZA_Kanashibari[(sizeof(WAZA_Kanashibari_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_KanashibariEnd[(offsetof(FightWazaCommandStreams, WAZA_KanashibariEnd) == 0x2F1C) ? 1 : -1];
typedef char WazaSize_WAZA_KanashibariEnd[(sizeof(WAZA_KanashibariEnd_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_EncoreEnd[(offsetof(FightWazaCommandStreams, WAZA_EncoreEnd) == 0x2F30) ? 1 : -1];
typedef char WazaSize_WAZA_EncoreEnd[(sizeof(WAZA_EncoreEnd_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Michidure[(offsetof(FightWazaCommandStreams, WAZA_Michidure) == 0x2F44) ? 1 : -1];
typedef char WazaSize_WAZA_Michidure[(sizeof(WAZA_Michidure_Stream) == 0x28) ? 1 : -1];
typedef char WazaOffset_WAZA_MakibishiA[(offsetof(FightWazaCommandStreams, WAZA_MakibishiA) == 0x2F6C) ? 1 : -1];
typedef char WazaSize_WAZA_MakibishiA[(sizeof(WAZA_MakibishiA_Stream) == 0x33) ? 1 : -1];
typedef char WazaOffset_WAZA_MakibishiD[(offsetof(FightWazaCommandStreams, WAZA_MakibishiD) == 0x2F9F) ? 1 : -1];
typedef char WazaSize_WAZA_MakibishiD[(sizeof(WAZA_MakibishiD_Stream) == 0x33) ? 1 : -1];
typedef char WazaOffset_WAZA_MakibishiK[(offsetof(FightWazaCommandStreams, WAZA_MakibishiK) == 0x2FD2) ? 1 : -1];
typedef char WazaSize_WAZA_MakibishiK[(sizeof(WAZA_MakibishiK_Stream) == 0x2C) ? 1 : -1];
typedef char WazaOffset_lbl_8041708E[(offsetof(FightWazaCommandStreams, lbl_8041708E) == 0x2FFE) ? 1 : -1];
typedef char WazaSize_lbl_8041708E[(sizeof(lbl_8041708E_Stream) == 0x10) ? 1 : -1];
typedef char WazaOffset_WAZA_Horobinouta[(offsetof(FightWazaCommandStreams, WAZA_Horobinouta) == 0x300E) ? 1 : -1];
typedef char WazaSize_WAZA_Horobinouta[(sizeof(WAZA_Horobinouta_Stream) == 0x28) ? 1 : -1];
typedef char WazaOffset_WAZA_Horobinoutaing[(offsetof(FightWazaCommandStreams, WAZA_Horobinoutaing) == 0x3036) ? 1 : -1];
typedef char WazaSize_WAZA_Horobinoutaing[(sizeof(WAZA_Horobinoutaing_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Genshinochikara[(offsetof(FightWazaCommandStreams, WAZA_Genshinochikara) == 0x304A) ? 1 : -1];
typedef char WazaSize_WAZA_Genshinochikara[(sizeof(WAZA_Genshinochikara_Stream) == 0x4B) ? 1 : -1];
typedef char WazaOffset_lbl_80417125[(offsetof(FightWazaCommandStreams, lbl_80417125) == 0x3095) ? 1 : -1];
typedef char WazaSize_lbl_80417125[(sizeof(lbl_80417125_Stream) == 0x56) ? 1 : -1];
typedef char WazaOffset_WAZA_Kousokuspin[(offsetof(FightWazaCommandStreams, WAZA_Kousokuspin) == 0x30EB) ? 1 : -1];
typedef char WazaSize_WAZA_Kousokuspin[(sizeof(WAZA_Kousokuspin_Stream) == 0x2) ? 1 : -1];
typedef char WazaOffset_WAZA_ShimeEscape[(offsetof(FightWazaCommandStreams, WAZA_ShimeEscape) == 0x30ED) ? 1 : -1];
typedef char WazaSize_WAZA_ShimeEscape[(sizeof(WAZA_ShimeEscape_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_YadorigiEscape[(offsetof(FightWazaCommandStreams, WAZA_YadorigiEscape) == 0x3101) ? 1 : -1];
typedef char WazaSize_WAZA_YadorigiEscape[(sizeof(WAZA_YadorigiEscape_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_MakibishiEscape[(offsetof(FightWazaCommandStreams, WAZA_MakibishiEscape) == 0x3115) ? 1 : -1];
typedef char WazaSize_WAZA_MakibishiEscape[(sizeof(WAZA_MakibishiEscape_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Miraiyochi[(offsetof(FightWazaCommandStreams, WAZA_Miraiyochi) == 0x3129) ? 1 : -1];
typedef char WazaSize_WAZA_Miraiyochi[(sizeof(WAZA_Miraiyochi_Stream) == 0x40) ? 1 : -1];
typedef char WazaOffset_lbl_804171F9[(offsetof(FightWazaCommandStreams, lbl_804171F9) == 0x3169) ? 1 : -1];
typedef char WazaSize_lbl_804171F9[(sizeof(lbl_804171F9_Stream) == 0x13) ? 1 : -1];
typedef char WazaOffset_lbl_8041720C[(offsetof(FightWazaCommandStreams, lbl_8041720C) == 0x317C) ? 1 : -1];
typedef char WazaSize_lbl_8041720C[(sizeof(lbl_8041720C_Stream) == 0x95) ? 1 : -1];
typedef char WazaOffset_WAZA_PPNoneAttack[(offsetof(FightWazaCommandStreams, WAZA_PPNoneAttack) == 0x3211) ? 1 : -1];
typedef char WazaSize_WAZA_PPNoneAttack[(sizeof(WAZA_PPNoneAttack_Stream) == 0x19) ? 1 : -1];
typedef char WazaOffset_WAZA_Chouhatsu2[(offsetof(FightWazaCommandStreams, WAZA_Chouhatsu2) == 0x322A) ? 1 : -1];
typedef char WazaSize_WAZA_Chouhatsu2[(sizeof(WAZA_Chouhatsu2_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_Negaigoto[(offsetof(FightWazaCommandStreams, WAZA_Negaigoto) == 0x3242) ? 1 : -1];
typedef char WazaSize_WAZA_Negaigoto[(sizeof(WAZA_Negaigoto_Stream) == 0x59) ? 1 : -1];
typedef char WazaOffset_WAZA_Newoharu[(offsetof(FightWazaCommandStreams, WAZA_Newoharu) == 0x329B) ? 1 : -1];
typedef char WazaSize_WAZA_Newoharu[(sizeof(WAZA_Newoharu_Stream) == 0x3C) ? 1 : -1];
typedef char WazaOffset_WAZA_Bakadikara[(offsetof(FightWazaCommandStreams, WAZA_Bakadikara) == 0x32D7) ? 1 : -1];
typedef char WazaSize_WAZA_Bakadikara[(sizeof(WAZA_Bakadikara_Stream) == 0x2D) ? 1 : -1];
typedef char WazaOffset_lbl_80417394[(offsetof(FightWazaCommandStreams, lbl_80417394) == 0x3304) ? 1 : -1];
typedef char WazaSize_lbl_80417394[(sizeof(lbl_80417394_Stream) == 0x23) ? 1 : -1];
typedef char WazaOffset_lbl_804173B7[(offsetof(FightWazaCommandStreams, lbl_804173B7) == 0x3327) ? 1 : -1];
typedef char WazaSize_lbl_804173B7[(sizeof(lbl_804173B7_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_Hatakiotosu[(offsetof(FightWazaCommandStreams, WAZA_Hatakiotosu) == 0x332D) ? 1 : -1];
typedef char WazaSize_WAZA_Hatakiotosu[(sizeof(WAZA_Hatakiotosu_Stream) == 0x12) ? 1 : -1];
typedef char WazaOffset_WAZA_Huuin[(offsetof(FightWazaCommandStreams, WAZA_Huuin) == 0x333F) ? 1 : -1];
typedef char WazaSize_WAZA_Huuin[(sizeof(WAZA_Huuin_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_Onnen[(offsetof(FightWazaCommandStreams, WAZA_Onnen) == 0x3357) ? 1 : -1];
typedef char WazaSize_WAZA_Onnen[(sizeof(WAZA_Onnen_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_MagicCort[(offsetof(FightWazaCommandStreams, WAZA_MagicCort) == 0x336B) ? 1 : -1];
typedef char WazaSize_WAZA_MagicCort[(sizeof(WAZA_MagicCort_Stream) == 0x22) ? 1 : -1];
typedef char WazaOffset_WAZA_Yokodori[(offsetof(FightWazaCommandStreams, WAZA_Yokodori) == 0x338D) ? 1 : -1];
typedef char WazaSize_WAZA_Yokodori[(sizeof(WAZA_Yokodori_Stream) == 0x21) ? 1 : -1];
typedef char WazaOffset_WAZA_Koraeta[(offsetof(FightWazaCommandStreams, WAZA_Koraeta) == 0x33AE) ? 1 : -1];
typedef char WazaSize_WAZA_Koraeta[(sizeof(WAZA_Koraeta_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_Ichigeki[(offsetof(FightWazaCommandStreams, WAZA_Ichigeki) == 0x33B7) ? 1 : -1];
typedef char WazaSize_WAZA_Ichigeki[(sizeof(WAZA_Ichigeki_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_OverHeat[(offsetof(FightWazaCommandStreams, WAZA_OverHeat) == 0x33C0) ? 1 : -1];
typedef char WazaSize_WAZA_OverHeat[(sizeof(WAZA_OverHeat_Stream) == 0x2B) ? 1 : -1];
typedef char WazaOffset_lbl_8041747B[(offsetof(FightWazaCommandStreams, lbl_8041747B) == 0x33EB) ? 1 : -1];
typedef char WazaSize_lbl_8041747B[(sizeof(lbl_8041747B_Stream) == 0x3) ? 1 : -1];
typedef char WazaOffset_WAZA_KiaiPunch[(offsetof(FightWazaCommandStreams, WAZA_KiaiPunch) == 0x33EE) ? 1 : -1];
typedef char WazaSize_WAZA_KiaiPunch[(sizeof(WAZA_KiaiPunch_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Hyper[(offsetof(FightWazaCommandStreams, WAZA_Hyper) == 0x3402) ? 1 : -1];
typedef char WazaSize_WAZA_Hyper[(sizeof(WAZA_Hyper_Stream) == 0x5) ? 1 : -1];
typedef char WazaOffset_WAZA_Nemuru[(offsetof(FightWazaCommandStreams, WAZA_Nemuru) == 0x3407) ? 1 : -1];
typedef char WazaSize_WAZA_Nemuru[(sizeof(WAZA_Nemuru_Stream) == 0x13) ? 1 : -1];
typedef char WazaOffset_WAZA_Mezame[(offsetof(FightWazaCommandStreams, WAZA_Mezame) == 0x341A) ? 1 : -1];
typedef char WazaSize_WAZA_Mezame[(sizeof(WAZA_Mezame_Stream) == 0x1F) ? 1 : -1];
typedef char WazaOffset_WAZA_SawaguMezame[(offsetof(FightWazaCommandStreams, WAZA_SawaguMezame) == 0x3439) ? 1 : -1];
typedef char WazaSize_WAZA_SawaguMezame[(sizeof(WAZA_SawaguMezame_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_Revers[(offsetof(FightWazaCommandStreams, WAZA_Revers) == 0x344F) ? 1 : -1];
typedef char WazaSize_WAZA_Revers[(sizeof(WAZA_Revers_Stream) == 0x1E) ? 1 : -1];
typedef char WazaOffset_WAZA_Dokudoku[(offsetof(FightWazaCommandStreams, WAZA_Dokudoku) == 0x346D) ? 1 : -1];
typedef char WazaSize_WAZA_Dokudoku[(sizeof(WAZA_Dokudoku_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_lbl_80417511[(offsetof(FightWazaCommandStreams, lbl_80417511) == 0x3481) ? 1 : -1];
typedef char WazaSize_lbl_80417511[(sizeof(lbl_80417511_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Yakedo[(offsetof(FightWazaCommandStreams, WAZA_Yakedo) == 0x3495) ? 1 : -1];
typedef char WazaSize_WAZA_Yakedo[(sizeof(WAZA_Yakedo_Stream) == 0x19) ? 1 : -1];
typedef char WazaOffset_WAZA_Koori[(offsetof(FightWazaCommandStreams, WAZA_Koori) == 0x34AE) ? 1 : -1];
typedef char WazaSize_WAZA_Koori[(sizeof(WAZA_Koori_Stream) == 0x13) ? 1 : -1];
typedef char WazaOffset_WAZA_Melt[(offsetof(FightWazaCommandStreams, WAZA_Melt) == 0x34C1) ? 1 : -1];
typedef char WazaSize_WAZA_Melt[(sizeof(WAZA_Melt_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_Melt2[(offsetof(FightWazaCommandStreams, WAZA_Melt2) == 0x34D7) ? 1 : -1];
typedef char WazaSize_WAZA_Melt2[(sizeof(WAZA_Melt2_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_Mahi[(offsetof(FightWazaCommandStreams, WAZA_Mahi) == 0x34ED) ? 1 : -1];
typedef char WazaSize_WAZA_Mahi[(sizeof(WAZA_Mahi_Stream) == 0x13) ? 1 : -1];
typedef char WazaOffset_WAZA_Hirumu[(offsetof(FightWazaCommandStreams, WAZA_Hirumu) == 0x3500) ? 1 : -1];
typedef char WazaSize_WAZA_Hirumu[(sizeof(WAZA_Hirumu_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_Sawagu[(offsetof(FightWazaCommandStreams, WAZA_Sawagu) == 0x3518) ? 1 : -1];
typedef char WazaSize_WAZA_Sawagu[(sizeof(WAZA_Sawagu_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_AbareruEnd[(offsetof(FightWazaCommandStreams, WAZA_AbareruEnd) == 0x352C) ? 1 : -1];
typedef char WazaSize_WAZA_AbareruEnd[(sizeof(WAZA_AbareruEnd_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Konran[(offsetof(FightWazaCommandStreams, WAZA_Konran) == 0x3540) ? 1 : -1];
typedef char WazaSize_WAZA_Konran[(sizeof(WAZA_Konran_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_lbl_804175ED[(offsetof(FightWazaCommandStreams, lbl_804175ED) == 0x355D) ? 1 : -1];
typedef char WazaSize_lbl_804175ED[(sizeof(lbl_804175ED_Stream) == 0x39) ? 1 : -1];
typedef char WazaOffset_WAZA_KonranEnd[(offsetof(FightWazaCommandStreams, WAZA_KonranEnd) == 0x3596) ? 1 : -1];
typedef char WazaSize_WAZA_KonranEnd[(sizeof(WAZA_KonranEnd_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Nekonikoban[(offsetof(FightWazaCommandStreams, WAZA_Nekonikoban) == 0x35AA) ? 1 : -1];
typedef char WazaSize_WAZA_Nekonikoban[(sizeof(WAZA_Nekonikoban_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_Shime[(offsetof(FightWazaCommandStreams, WAZA_Shime) == 0x35B3) ? 1 : -1];
typedef char WazaSize_WAZA_Shime[(sizeof(WAZA_Shime_Stream) == 0x1E) ? 1 : -1];
typedef char WazaOffset_WAZA_ShimeEnd[(offsetof(FightWazaCommandStreams, WAZA_ShimeEnd) == 0x35D1) ? 1 : -1];
typedef char WazaSize_WAZA_ShimeEnd[(sizeof(WAZA_ShimeEnd_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Meromero[(offsetof(FightWazaCommandStreams, WAZA_Meromero) == 0x35E5) ? 1 : -1];
typedef char WazaSize_WAZA_Meromero[(sizeof(WAZA_Meromero_Stream) == 0x13) ? 1 : -1];
typedef char WazaOffset_WAZA_MeromeroNext[(offsetof(FightWazaCommandStreams, WAZA_MeromeroNext) == 0x35F8) ? 1 : -1];
typedef char WazaSize_WAZA_MeromeroNext[(sizeof(WAZA_MeromeroNext_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_Akumu[(offsetof(FightWazaCommandStreams, WAZA_Akumu) == 0x3610) ? 1 : -1];
typedef char WazaSize_WAZA_Akumu[(sizeof(WAZA_Akumu_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_Noroi[(offsetof(FightWazaCommandStreams, WAZA_Noroi) == 0x362D) ? 1 : -1];
typedef char WazaSize_WAZA_Noroi[(sizeof(WAZA_Noroi_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_NoMahi[(offsetof(FightWazaCommandStreams, WAZA_NoMahi) == 0x364A) ? 1 : -1];
typedef char WazaSize_WAZA_NoMahi[(sizeof(WAZA_NoMahi_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_AddNemuri[(offsetof(FightWazaCommandStreams, WAZA_AddNemuri) == 0x3660) ? 1 : -1];
typedef char WazaSize_WAZA_AddNemuri[(sizeof(WAZA_AddNemuri_Stream) == 0x10) ? 1 : -1];
typedef char WazaOffset_lbl_80417700[(offsetof(FightWazaCommandStreams, lbl_80417700) == 0x3670) ? 1 : -1];
typedef char WazaSize_lbl_80417700[(sizeof(lbl_80417700_Stream) == 0x2) ? 1 : -1];
typedef char WazaOffset_WAZA_AddNemuri2[(offsetof(FightWazaCommandStreams, WAZA_AddNemuri2) == 0x3672) ? 1 : -1];
typedef char WazaSize_WAZA_AddNemuri2[(sizeof(WAZA_AddNemuri2_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_AddDoku[(offsetof(FightWazaCommandStreams, WAZA_AddDoku) == 0x3686) ? 1 : -1];
typedef char WazaSize_WAZA_AddDoku[(sizeof(WAZA_AddDoku_Stream) == 0x15) ? 1 : -1];
typedef char WazaOffset_WAZA_AddYakedo[(offsetof(FightWazaCommandStreams, WAZA_AddYakedo) == 0x369B) ? 1 : -1];
typedef char WazaSize_WAZA_AddYakedo[(sizeof(WAZA_AddYakedo_Stream) == 0x15) ? 1 : -1];
typedef char WazaOffset_WAZA_AddKoori[(offsetof(FightWazaCommandStreams, WAZA_AddKoori) == 0x36B0) ? 1 : -1];
typedef char WazaSize_WAZA_AddKoori[(sizeof(WAZA_AddKoori_Stream) == 0x15) ? 1 : -1];
typedef char WazaOffset_WAZA_AddMahi[(offsetof(FightWazaCommandStreams, WAZA_AddMahi) == 0x36C5) ? 1 : -1];
typedef char WazaSize_WAZA_AddMahi[(sizeof(WAZA_AddMahi_Stream) == 0x15) ? 1 : -1];
typedef char WazaOffset_WAZA_AddSawagu[(offsetof(FightWazaCommandStreams, WAZA_AddSawagu) == 0x36DA) ? 1 : -1];
typedef char WazaSize_WAZA_AddSawagu[(sizeof(WAZA_AddSawagu_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_AddDokudoku[(offsetof(FightWazaCommandStreams, WAZA_AddDokudoku) == 0x36EE) ? 1 : -1];
typedef char WazaSize_WAZA_AddDokudoku[(sizeof(WAZA_AddDokudoku_Stream) == 0x15) ? 1 : -1];
typedef char WazaOffset_WAZA_AddNekonikoban[(offsetof(FightWazaCommandStreams, WAZA_AddNekonikoban) == 0x3703) ? 1 : -1];
typedef char WazaSize_WAZA_AddNekonikoban[(sizeof(WAZA_AddNekonikoban_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_AddShime[(offsetof(FightWazaCommandStreams, WAZA_AddShime) == 0x3717) ? 1 : -1];
typedef char WazaSize_WAZA_AddShime[(sizeof(WAZA_AddShime_Stream) == 0x12) ? 1 : -1];
typedef char WazaOffset_WAZA_AddKonran[(offsetof(FightWazaCommandStreams, WAZA_AddKonran) == 0x3729) ? 1 : -1];
typedef char WazaSize_WAZA_AddKonran[(sizeof(WAZA_AddKonran_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_AddHanekaeri[(offsetof(FightWazaCommandStreams, WAZA_AddHanekaeri) == 0x373D) ? 1 : -1];
typedef char WazaSize_WAZA_AddHanekaeri[(sizeof(WAZA_AddHanekaeri_Stream) == 0x33) ? 1 : -1];
typedef char WazaOffset_lbl_80417800[(offsetof(FightWazaCommandStreams, lbl_80417800) == 0x3770) ? 1 : -1];
typedef char WazaSize_lbl_80417800[(sizeof(lbl_80417800_Stream) == 0x27) ? 1 : -1];
typedef char WazaOffset_lbl_80417827[(offsetof(FightWazaCommandStreams, lbl_80417827) == 0x3797) ? 1 : -1];
typedef char WazaSize_lbl_80417827[(sizeof(lbl_80417827_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_WAZA_AddDorobou[(offsetof(FightWazaCommandStreams, WAZA_AddDorobou) == 0x3798) ? 1 : -1];
typedef char WazaSize_WAZA_AddDorobou[(sizeof(WAZA_AddDorobou_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_Amehurashi[(offsetof(FightWazaCommandStreams, WAZA_Amehurashi) == 0x37AC) ? 1 : -1];
typedef char WazaSize_WAZA_Amehurashi[(sizeof(WAZA_Amehurashi_Stream) == 0x1C) ? 1 : -1];
typedef char WazaOffset_WAZA_Sunaokosi[(offsetof(FightWazaCommandStreams, WAZA_Sunaokosi) == 0x37C8) ? 1 : -1];
typedef char WazaSize_WAZA_Sunaokosi[(sizeof(WAZA_Sunaokosi_Stream) == 0x1C) ? 1 : -1];
typedef char WazaOffset_WAZA_Hideri[(offsetof(FightWazaCommandStreams, WAZA_Hideri) == 0x37E4) ? 1 : -1];
typedef char WazaSize_WAZA_Hideri[(sizeof(WAZA_Hideri_Stream) == 0x1C) ? 1 : -1];
typedef char WazaOffset_WAZA_Ikaku[(offsetof(FightWazaCommandStreams, WAZA_Ikaku) == 0x3800) ? 1 : -1];
typedef char WazaSize_WAZA_Ikaku[(sizeof(WAZA_Ikaku_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_lbl_80417896[(offsetof(FightWazaCommandStreams, lbl_80417896) == 0x3806) ? 1 : -1];
typedef char WazaSize_lbl_80417896[(sizeof(lbl_80417896_Stream) == 0x3) ? 1 : -1];
typedef char WazaOffset_WAZA_IkakuAct[(offsetof(FightWazaCommandStreams, WAZA_IkakuAct) == 0x3809) ? 1 : -1];
typedef char WazaSize_WAZA_IkakuAct[(sizeof(WAZA_IkakuAct_Stream) == 0xC) ? 1 : -1];
typedef char WazaOffset_WAZA_IkakuLoop[(offsetof(FightWazaCommandStreams, WAZA_IkakuLoop) == 0x3815) ? 1 : -1];
typedef char WazaSize_WAZA_IkakuLoop[(sizeof(WAZA_IkakuLoop_Stream) == 0x46) ? 1 : -1];
typedef char WazaOffset_lbl_804178EB[(offsetof(FightWazaCommandStreams, lbl_804178EB) == 0x385B) ? 1 : -1];
typedef char WazaSize_lbl_804178EB[(sizeof(lbl_804178EB_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_lbl_804178EC[(offsetof(FightWazaCommandStreams, lbl_804178EC) == 0x385C) ? 1 : -1];
typedef char WazaSize_lbl_804178EC[(sizeof(lbl_804178EC_Stream) == 0x1A) ? 1 : -1];
typedef char WazaOffset_WAZA_Trace[(offsetof(FightWazaCommandStreams, WAZA_Trace) == 0x3876) ? 1 : -1];
typedef char WazaSize_WAZA_Trace[(sizeof(WAZA_Trace_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_Ameukezara[(offsetof(FightWazaCommandStreams, WAZA_Ameukezara) == 0x388C) ? 1 : -1];
typedef char WazaSize_WAZA_Ameukezara[(sizeof(WAZA_Ameukezara_Stream) == 0x23) ? 1 : -1];
typedef char WazaOffset_WAZA_Dappi[(offsetof(FightWazaCommandStreams, WAZA_Dappi) == 0x38AF) ? 1 : -1];
typedef char WazaSize_WAZA_Dappi[(sizeof(WAZA_Dappi_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_Kasokusouti[(offsetof(FightWazaCommandStreams, WAZA_Kasokusouti) == 0x38C7) ? 1 : -1];
typedef char WazaSize_WAZA_Kasokusouti[(sizeof(WAZA_Kasokusouti_Stream) == 0x24) ? 1 : -1];
typedef char WazaOffset_WAZA_Tenkiya[(offsetof(FightWazaCommandStreams, WAZA_Tenkiya) == 0x38EB) ? 1 : -1];
typedef char WazaSize_WAZA_Tenkiya[(sizeof(WAZA_Tenkiya_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_Tenkiya2[(offsetof(FightWazaCommandStreams, WAZA_Tenkiya2) == 0x38F1) ? 1 : -1];
typedef char WazaSize_WAZA_Tenkiya2[(sizeof(WAZA_Tenkiya2_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_Hiraishin[(offsetof(FightWazaCommandStreams, WAZA_Hiraishin) == 0x3909) ? 1 : -1];
typedef char WazaSize_WAZA_Hiraishin[(sizeof(WAZA_Hiraishin_Stream) == 0x23) ? 1 : -1];
typedef char WazaOffset_WAZA_TyosuiPPDec[(offsetof(FightWazaCommandStreams, WAZA_TyosuiPPDec) == 0x392C) ? 1 : -1];
typedef char WazaSize_WAZA_TyosuiPPDec[(sizeof(WAZA_TyosuiPPDec_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_WAZA_Tyosui[(offsetof(FightWazaCommandStreams, WAZA_Tyosui) == 0x392D) ? 1 : -1];
typedef char WazaSize_WAZA_Tyosui[(sizeof(WAZA_Tyosui_Stream) == 0x3C) ? 1 : -1];
typedef char WazaOffset_WAZA_NOKaifukuPPDec[(offsetof(FightWazaCommandStreams, WAZA_NOKaifukuPPDec) == 0x3969) ? 1 : -1];
typedef char WazaSize_WAZA_NOKaifukuPPDec[(sizeof(WAZA_NOKaifukuPPDec_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_WAZA_NOKaifuku[(offsetof(FightWazaCommandStreams, WAZA_NOKaifuku) == 0x396A) ? 1 : -1];
typedef char WazaSize_WAZA_NOKaifuku[(sizeof(WAZA_NOKaifuku_Stream) == 0x2F) ? 1 : -1];
typedef char WazaOffset_WAZA_MoraibiPPDec[(offsetof(FightWazaCommandStreams, WAZA_MoraibiPPDec) == 0x3999) ? 1 : -1];
typedef char WazaSize_WAZA_MoraibiPPDec[(sizeof(WAZA_MoraibiPPDec_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_WAZA_Moraibi[(offsetof(FightWazaCommandStreams, WAZA_Moraibi) == 0x399A) ? 1 : -1];
typedef char WazaSize_WAZA_Moraibi[(sizeof(WAZA_Moraibi_Stream) == 0x1B) ? 1 : -1];
typedef char WazaOffset_WAZA_Ganzyou[(offsetof(FightWazaCommandStreams, WAZA_Ganzyou) == 0x39B5) ? 1 : -1];
typedef char WazaSize_WAZA_Ganzyou[(sizeof(WAZA_Ganzyou_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_Shimerike[(offsetof(FightWazaCommandStreams, WAZA_Shimerike) == 0x39D2) ? 1 : -1];
typedef char WazaSize_WAZA_Shimerike[(sizeof(WAZA_Shimerike_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_lbl_80417A7F[(offsetof(FightWazaCommandStreams, lbl_80417A7F) == 0x39EF) ? 1 : -1];
typedef char WazaSize_lbl_80417A7F[(sizeof(lbl_80417A7F_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_ClearBody[(offsetof(FightWazaCommandStreams, WAZA_ClearBody) == 0x3A0C) ? 1 : -1];
typedef char WazaSize_WAZA_ClearBody[(sizeof(WAZA_ClearBody_Stream) == 0x19) ? 1 : -1];
typedef char WazaOffset_WAZA_Mizunobeeru[(offsetof(FightWazaCommandStreams, WAZA_Mizunobeeru) == 0x3A25) ? 1 : -1];
typedef char WazaSize_WAZA_Mizunobeeru[(sizeof(WAZA_Mizunobeeru_Stream) == 0x19) ? 1 : -1];
typedef char WazaOffset_WAZA_Juunan[(offsetof(FightWazaCommandStreams, WAZA_Juunan) == 0x3A3E) ? 1 : -1];
typedef char WazaSize_WAZA_Juunan[(sizeof(WAZA_Juunan_Stream) == 0x19) ? 1 : -1];
typedef char WazaOffset_WAZA_Meneki[(offsetof(FightWazaCommandStreams, WAZA_Meneki) == 0x3A57) ? 1 : -1];
typedef char WazaSize_WAZA_Meneki[(sizeof(WAZA_Meneki_Stream) == 0x19) ? 1 : -1];
typedef char WazaOffset_WAZA_Donkan[(offsetof(FightWazaCommandStreams, WAZA_Donkan) == 0x3A70) ? 1 : -1];
typedef char WazaSize_WAZA_Donkan[(sizeof(WAZA_Donkan_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_Seisinryoku[(offsetof(FightWazaCommandStreams, WAZA_Seisinryoku) == 0x3A8D) ? 1 : -1];
typedef char WazaSize_WAZA_Seisinryoku[(sizeof(WAZA_Seisinryoku_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_Mypace[(offsetof(FightWazaCommandStreams, WAZA_Mypace) == 0x3AAA) ? 1 : -1];
typedef char WazaSize_WAZA_Mypace[(sizeof(WAZA_Mypace_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_Bouon[(offsetof(FightWazaCommandStreams, WAZA_Bouon) == 0x3AC7) ? 1 : -1];
typedef char WazaSize_WAZA_Bouon[(sizeof(WAZA_Bouon_Stream) == 0x1F) ? 1 : -1];
typedef char WazaOffset_WAZA_Kairikibasami[(offsetof(FightWazaCommandStreams, WAZA_Kairikibasami) == 0x3AE6) ? 1 : -1];
typedef char WazaSize_WAZA_Kairikibasami[(sizeof(WAZA_Kairikibasami_Stream) == 0x1F) ? 1 : -1];
typedef char WazaOffset_WAZA_Nentyaku[(offsetof(FightWazaCommandStreams, WAZA_Nentyaku) == 0x3B05) ? 1 : -1];
typedef char WazaSize_WAZA_Nentyaku[(sizeof(WAZA_Nentyaku_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_Nentyaku2[(offsetof(FightWazaCommandStreams, WAZA_Nentyaku2) == 0x3B22) ? 1 : -1];
typedef char WazaSize_WAZA_Nentyaku2[(sizeof(WAZA_Nentyaku2_Stream) == 0x19) ? 1 : -1];
typedef char WazaOffset_WAZA_Hensyoku[(offsetof(FightWazaCommandStreams, WAZA_Hensyoku) == 0x3B3B) ? 1 : -1];
typedef char WazaSize_WAZA_Hensyoku[(sizeof(WAZA_Hensyoku_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_Samehada[(offsetof(FightWazaCommandStreams, WAZA_Samehada) == 0x3B51) ? 1 : -1];
typedef char WazaSize_WAZA_Samehada[(sizeof(WAZA_Samehada_Stream) == 0x2A) ? 1 : -1];
typedef char WazaOffset_WAZA_Honoonokarada[(offsetof(FightWazaCommandStreams, WAZA_Honoonokarada) == 0x3B7B) ? 1 : -1];
typedef char WazaSize_WAZA_Honoonokarada[(sizeof(WAZA_Honoonokarada_Stream) == 0x5) ? 1 : -1];
typedef char WazaOffset_WAZA_MeromeroBody[(offsetof(FightWazaCommandStreams, WAZA_MeromeroBody) == 0x3B80) ? 1 : -1];
typedef char WazaSize_WAZA_MeromeroBody[(sizeof(WAZA_MeromeroBody_Stream) == 0x15) ? 1 : -1];
typedef char WazaOffset_WAZA_Sinkuro[(offsetof(FightWazaCommandStreams, WAZA_Sinkuro) == 0x3B95) ? 1 : -1];
typedef char WazaSize_WAZA_Sinkuro[(sizeof(WAZA_Sinkuro_Stream) == 0x5) ? 1 : -1];
typedef char WazaOffset_WAZA_SpeabiNoJoutaiijou[(offsetof(FightWazaCommandStreams, WAZA_SpeabiNoJoutaiijou) == 0x3B9A) ? 1 : -1];
typedef char WazaSize_WAZA_SpeabiNoJoutaiijou[(sizeof(WAZA_SpeabiNoJoutaiijou_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_OrderIgnoreSleep[(offsetof(FightWazaCommandStreams, WAZA_OrderIgnoreSleep) == 0x3BB0) ? 1 : -1];
typedef char WazaSize_WAZA_OrderIgnoreSleep[(sizeof(WAZA_OrderIgnoreSleep_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_OrderIgnore[(offsetof(FightWazaCommandStreams, WAZA_OrderIgnore) == 0x3BCD) ? 1 : -1];
typedef char WazaSize_WAZA_OrderIgnore[(sizeof(WAZA_OrderIgnore_Stream) == 0x15) ? 1 : -1];
typedef char WazaOffset_WAZA_Namakeru[(offsetof(FightWazaCommandStreams, WAZA_Namakeru) == 0x3BE2) ? 1 : -1];
typedef char WazaSize_WAZA_Namakeru[(sizeof(WAZA_Namakeru_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_Hirune[(offsetof(FightWazaCommandStreams, WAZA_Hirune) == 0x3BFF) ? 1 : -1];
typedef char WazaSize_WAZA_Hirune[(sizeof(WAZA_Hirune_Stream) == 0x26) ? 1 : -1];
typedef char WazaOffset_WAZA_OwnAttack[(offsetof(FightWazaCommandStreams, WAZA_OwnAttack) == 0x3C25) ? 1 : -1];
typedef char WazaSize_WAZA_OwnAttack[(sizeof(WAZA_OwnAttack_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_HyperOrderIgnore[(offsetof(FightWazaCommandStreams, WAZA_HyperOrderIgnore) == 0x3C3D) ? 1 : -1];
typedef char WazaSize_WAZA_HyperOrderIgnore[(sizeof(WAZA_HyperOrderIgnore_Stream) == 0x2) ? 1 : -1];
typedef char WazaOffset_WAZA_HyperOwnAttack[(offsetof(FightWazaCommandStreams, WAZA_HyperOwnAttack) == 0x3C3F) ? 1 : -1];
typedef char WazaSize_WAZA_HyperOwnAttack[(sizeof(WAZA_HyperOwnAttack_Stream) == 0x5) ? 1 : -1];
typedef char WazaOffset_WAZA_HyperPost[(offsetof(FightWazaCommandStreams, WAZA_HyperPost) == 0x3C44) ? 1 : -1];
typedef char WazaSize_WAZA_HyperPost[(sizeof(WAZA_HyperPost_Stream) == 0xA) ? 1 : -1];
typedef char WazaOffset_WAZA_HyperModoru[(offsetof(FightWazaCommandStreams, WAZA_HyperModoru) == 0x3C4E) ? 1 : -1];
typedef char WazaSize_WAZA_HyperModoru[(sizeof(WAZA_HyperModoru_Stream) == 0x24) ? 1 : -1];
typedef char WazaOffset_WAZA_MigawariKizetsu[(offsetof(FightWazaCommandStreams, WAZA_MigawariKizetsu) == 0x3C72) ? 1 : -1];
typedef char WazaSize_WAZA_MigawariKizetsu[(sizeof(WAZA_MigawariKizetsu_Stream) == 0x14) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoMahi[(offsetof(FightWazaCommandStreams, WAZA_ItemNoMahi) == 0x3C86) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoMahi[(sizeof(WAZA_ItemNoMahi_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoMahi2[(offsetof(FightWazaCommandStreams, WAZA_ItemNoMahi2) == 0x3C8C) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoMahi2[(sizeof(WAZA_ItemNoMahi2_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoDoku[(offsetof(FightWazaCommandStreams, WAZA_ItemNoDoku) == 0x3CA4) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoDoku[(sizeof(WAZA_ItemNoDoku_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoDoku2[(offsetof(FightWazaCommandStreams, WAZA_ItemNoDoku2) == 0x3CAA) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoDoku2[(sizeof(WAZA_ItemNoDoku2_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoYakedo[(offsetof(FightWazaCommandStreams, WAZA_ItemNoYakedo) == 0x3CC2) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoYakedo[(sizeof(WAZA_ItemNoYakedo_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoYakedo2[(offsetof(FightWazaCommandStreams, WAZA_ItemNoYakedo2) == 0x3CC8) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoYakedo2[(sizeof(WAZA_ItemNoYakedo2_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoKoori[(offsetof(FightWazaCommandStreams, WAZA_ItemNoKoori) == 0x3CE0) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoKoori[(sizeof(WAZA_ItemNoKoori_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoKoori2[(offsetof(FightWazaCommandStreams, WAZA_ItemNoKoori2) == 0x3CE6) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoKoori2[(sizeof(WAZA_ItemNoKoori2_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoNemuri[(offsetof(FightWazaCommandStreams, WAZA_ItemNoNemuri) == 0x3CFE) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoNemuri[(sizeof(WAZA_ItemNoNemuri_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoNemuri2[(offsetof(FightWazaCommandStreams, WAZA_ItemNoNemuri2) == 0x3D04) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoNemuri2[(sizeof(WAZA_ItemNoNemuri2_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoKonran[(offsetof(FightWazaCommandStreams, WAZA_ItemNoKonran) == 0x3D1C) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoKonran[(sizeof(WAZA_ItemNoKonran_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoKonran2[(offsetof(FightWazaCommandStreams, WAZA_ItemNoKonran2) == 0x3D22) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoKonran2[(sizeof(WAZA_ItemNoKonran2_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoJoutaiijou[(offsetof(FightWazaCommandStreams, WAZA_ItemNoJoutaiijou) == 0x3D38) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoJoutaiijou[(sizeof(WAZA_ItemNoJoutaiijou_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemNoJoutaiijou2[(offsetof(FightWazaCommandStreams, WAZA_ItemNoJoutaiijou2) == 0x3D3E) ? 1 : -1];
typedef char WazaSize_WAZA_ItemNoJoutaiijou2[(sizeof(WAZA_ItemNoJoutaiijou2_Stream) == 0x18) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemAbiKaifuku[(offsetof(FightWazaCommandStreams, WAZA_ItemAbiKaifuku) == 0x3D56) ? 1 : -1];
typedef char WazaSize_WAZA_ItemAbiKaifuku[(sizeof(WAZA_ItemAbiKaifuku_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemAbiKaifuku2[(offsetof(FightWazaCommandStreams, WAZA_ItemAbiKaifuku2) == 0x3D5C) ? 1 : -1];
typedef char WazaSize_WAZA_ItemAbiKaifuku2[(sizeof(WAZA_ItemAbiKaifuku2_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemHPKaifuku[(offsetof(FightWazaCommandStreams, WAZA_ItemHPKaifuku) == 0x3D72) ? 1 : -1];
typedef char WazaSize_WAZA_ItemHPKaifuku[(sizeof(WAZA_ItemHPKaifuku_Stream) == 0x23) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemPPKaifuku[(offsetof(FightWazaCommandStreams, WAZA_ItemPPKaifuku) == 0x3D95) ? 1 : -1];
typedef char WazaSize_WAZA_ItemPPKaifuku[(sizeof(WAZA_ItemPPKaifuku_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemHPKaifukuEveryTurn[(offsetof(FightWazaCommandStreams, WAZA_ItemHPKaifukuEveryTurn) == 0x3DAB) ? 1 : -1];
typedef char WazaSize_WAZA_ItemHPKaifukuEveryTurn[(sizeof(WAZA_ItemHPKaifukuEveryTurn_Stream) == 0x6) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemHPKaifukuEveryTurn2[(offsetof(FightWazaCommandStreams, WAZA_ItemHPKaifukuEveryTurn2) == 0x3DB1) ? 1 : -1];
typedef char WazaSize_WAZA_ItemHPKaifukuEveryTurn2[(sizeof(WAZA_ItemHPKaifukuEveryTurn2_Stream) == 0x21) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemHPKaifukuKonran[(offsetof(FightWazaCommandStreams, WAZA_ItemHPKaifukuKonran) == 0x3DD2) ? 1 : -1];
typedef char WazaSize_WAZA_ItemHPKaifukuKonran[(sizeof(WAZA_ItemHPKaifukuKonran_Stream) == 0x32) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemCondUp[(offsetof(FightWazaCommandStreams, WAZA_ItemCondUp) == 0x3E04) ? 1 : -1];
typedef char WazaSize_WAZA_ItemCondUp[(sizeof(WAZA_ItemCondUp_Stream) == 0x1D) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemCriticalUp[(offsetof(FightWazaCommandStreams, WAZA_ItemCriticalUp) == 0x3E21) ? 1 : -1];
typedef char WazaSize_WAZA_ItemCriticalUp[(sizeof(WAZA_ItemCriticalUp_Stream) == 0x16) ? 1 : -1];
typedef char WazaOffset_WAZA_ItemKoraeta[(offsetof(FightWazaCommandStreams, WAZA_ItemKoraeta) == 0x3E37) ? 1 : -1];
typedef char WazaSize_WAZA_ItemKoraeta[(sizeof(WAZA_ItemKoraeta_Stream) == 0x9) ? 1 : -1];
typedef char WazaOffset_WAZA_DouguAlert[(offsetof(FightWazaCommandStreams, WAZA_DouguAlert) == 0x3E40) ? 1 : -1];
typedef char WazaSize_WAZA_DouguAlert[(sizeof(WAZA_DouguAlert_Stream) == 0x4) ? 1 : -1];
typedef char WazaOffset_WAZA_BlankMsg[(offsetof(FightWazaCommandStreams, WAZA_BlankMsg) == 0x3E44) ? 1 : -1];
typedef char WazaSize_WAZA_BlankMsg[(sizeof(WAZA_BlankMsg_Stream) == 0xA) ? 1 : -1];
typedef char WazaOffset_WAZA_Null[(offsetof(FightWazaCommandStreams, WAZA_Null) == 0x3E4E) ? 1 : -1];
typedef char WazaSize_WAZA_Null[(sizeof(WAZA_Null_Stream) == 0x1) ? 1 : -1];
typedef char WazaOffset_WazaEffectTbl[(offsetof(FightWazaCommandStreams, WazaEffectTbl) == 0x3E4F) ? 1 : -1];
typedef char WazaSize_WazaEffectTbl[(sizeof(WazaEffectTbl_Stream) == 0x368) ? 1 : -1];
typedef char WazaStorageSize[(sizeof(FightWazaCommandStreams) == 0x41B7) ? 1 : -1];

/* Sixteen-byte input alignment reproduces both versions' retail boundaries.
 * The final gap belongs to the next contribution's alignment. */
__declspec(section ".data") FightWazaCommandStreams FightWazaCommandStorage __attribute__((aligned(16))) = {
    { /* lbl_80414090 */
        {WS_STATUS_GET16, 7, 0, 0, 55, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 1, (u8*)&fight_seq_ushort_buff, 57, (u8*)&lbl_804140DE},
        {WS_WAZAKOUKA_CHECK, 18, 33, 0, (u8*)&lbl_804140DE},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x40000},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
    },
    { /* lbl_804140DE */
        {WS_BADGECHECK},
    },
    { /* lbl_804140DF */
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
    },
    { /* WAZA_HitCalc */
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
    },
    { /* WAZA_HitCalcOnly */
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
    },
    { /* WAZA_Hit */
        {WS_SETVALUE, (u8*)&fight_seq_oiuchiflag, 0},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_TSUIKA_CHECK},
        {WS_KIZETSU_CHECK, 18, 0, 0},
    },
    { /* WAZA_WazaEnd */
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 0, 0},
        {WS_WAZAEND},
    },
    { /* lbl_80414119 */
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_nohit},
    },
    { /* WAZA_NormalNohit */
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
    },
    { /* WAZA_NormalNohitWait */
        {WS_WAIT, 32},
    },
    { /* WAZA_NormalNohit2 */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_SE},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION_CHECK, 18, 8, (u8*)&lbl_8041418B},
        {WS_SAWAGU_CHECK, (u8*)&lbl_804141A4 + 0x19},
        {WS_CONDITION_CHECK, 18, 1, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 1},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_8041418B */
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E3D},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_804141A4 */
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E3F},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE_TBL, (u8*)&SleepNGMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 2},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_SUITORI},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_SPEABI_CHECK, 18, 64, (u8*)&lbl_804141A4 + 0x7C},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 0},
        {WS_JUMP, (u8*)&lbl_80414228},
        {WS_DAMAGE_CHG, 0},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 1},
    },
    { /* lbl_80414228 */
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_80414254},
        {WS_MESSAGE_TBL, (u8*)&SuitoriMsgTbl},
        {WS_MESSAGE_WAIT, 96},
    },
    { /* lbl_80414254 */
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 3},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 4},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 5},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_JIBAKU_INIT, 1},
        {WS_JIBAKU},
        {WS_CLIENT_BIT_WAIT},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff2, 64},
        {WS_STATUS_GET8, 7, 0, 0, 59, (u8*)&fight_seq_uchar_buff2, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_804142C2},
        {WS_GOSUB, (u8*)&lbl_804142C5 + 0x64},
        {WS_JUMP, (u8*)&lbl_804142C5},
    },
    { /* lbl_804142C2 */
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
    },
    { /* lbl_804142C5 */
        {WS_LOOP_INIT},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
        {WS_HITCHECK, (u8*)&lbl_804142C5 + 0x3F, 0},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_JIBAKU_LOOP, (u8*)&lbl_804142C5, 1},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_WAZAEND},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_SE},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_JIBAKU_LOOP, (u8*)&lbl_804142C5, 1},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_WAZAEND},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_null},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_nohit},
        {WS_SEQRET},
        {WS_BADGECHECK},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&lbl_8041436A},
        {WS_CONDITION_CHECK, 18, 8, (u8*)&lbl_8041436A + 0xA},
    },
    { /* lbl_8041436A */
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_MESSAGE_WAIT, 64},
        {WS_JUMP, (u8*)&lbl_804141A4},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 255},
        {WS_SUITORI},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 17},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_804143D0},
        {WS_MESSAGE, 0x4E55},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
    },
    { /* lbl_804143D0 */
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_WAIT, 64},
        {WS_OUMU_CHECK},
        {WS_PP_DEC},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_umakukimaran},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4F2B},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 17},
        {WS_JUMP, (u8*)&lbl_80414439},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_JUMP, (u8*)&lbl_80414439},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 20},
        {WS_JUMP, (u8*)&lbl_80414439},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 23},
        {WS_JUMP, (u8*)&lbl_80414439},
    },
    { /* lbl_80414439 */
        {WS_BADGECHECK},
    },
    { /* lbl_8041443A */
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDCHG, 65, (u8*)&WAZA_CondUpMsg + 0xA},
        {WS_IF8, 1, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_8041443A + 0x1B},
        {WS_WAIT, 32},
        {WS_JUMP, (u8*)&WAZA_CondUpMsg},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_COND_CHG_WORK_SET},
        {WS_FIGHT_EFFECT, 17, 1, 0xFF0160A4},
        {WS_EFFECT_WAIT, 255},
    },
    { /* WAZA_CondUpMsg */
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_CondUpTsuikaMsg */
        {WS_FIGHT_EFFECT, 22, 1, 0xFF0160A4},
        {WS_JUMP, (u8*)&WAZA_CondUpTsuikaMsg + 0x18},
        {WS_FIGHT_EFFECT, 17, 1, 0xFF0160A4},
        {WS_JUMP, (u8*)&WAZA_CondUpTsuikaMsg + 0x18},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 145},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 146},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 147},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 150},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 151},
        {WS_JUMP, (u8*)&lbl_804144CD},
    },
    { /* lbl_804144CD */
        {WS_BADGECHECK},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&lbl_80415C91},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDCHG, 1, (u8*)&WAZA_CondDownMsg + 0xA},
        {WS_IF8, 3, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_804144CD + 0x38},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 3, (u8*)&WAZA_CondDownMsg + 0xA},
        {WS_WAIT, 32},
        {WS_JUMP, (u8*)&lbl_804144CD + 0x4A},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_COND_CHG_WORK_SET},
        {WS_FIGHT_EFFECT, 18, 1, 0xFF0160A4},
        {WS_EFFECT_WAIT, 0},
        {WS_JUMP, (u8*)&WAZA_CondDownMsg},
        {WS_FIGHT_EFFECT, 18, 23, 0},
    },
    { /* WAZA_CondDownMsg */
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_CondDownTsuikaMsg */
        {WS_FIGHT_EFFECT, 22, 1, 0xFF0160A4},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_KUROIKIRI},
        {WS_MESSAGE, 0x4F3C},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&lbl_804148ED},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x8000000},
        {WS_GAMAN},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&WAZA_CondDownTsuikaMsg + 0x5F},
        {WS_PP_DEC},
        {WS_ABARERU},
        {WS_JUMP, (u8*)&WAZA_HitCalcOnly},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SPEABI_CHECK, 18, 21, (u8*)&lbl_80417A7F},
        {WS_WAZAKOUKA_CHECK, 18, 37, 1, (u8*)&WAZA_Newoharu + 0x21},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFF},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit2, 0},
        {WS_HUKITOBASHI, (u8*)&WAZA_Umakukimaran},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_RENZOKU, 0},
        {WS_RENZOKU_NUM_INIT},
        {WS_SETVALUE, (u8*)&fight_seq_server_work3_temp, 0},
    },
    { /* lbl_804145CD */
        {WS_STATUS_GET16, 7, 0, 0, 56, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 214, (u8*)&lbl_804145CD + 0x2A},
        {WS_CONDITION_CHECK, 17, 8, (u8*)&lbl_80414685 + 0x7},
        {WS_LOOP_INIT},
        {WS_SETWORK, (u8*)&ServerWork + 0x3, (u8*)&fight_seq_server_work3_temp, 1},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_80414685},
        {WS_DAMAGE_LOSS},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_ADDVALUE, (u8*)&fight_seq_renzoku_count, 1},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff2, 70},
        {WS_STATUS_GET8, 7, 0, 0, 59, (u8*)&fight_seq_uchar_buff2, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 1, (u8*)&lbl_80414685 + 0x7},
        {WS_HP_CHECK, 18, (u8*)&lbl_80414685 + 0x7},
        {WS_LOOP, (u8*)&lbl_8041466D},
        {WS_JUMP, (u8*)&lbl_80414685 + 0x7},
    },
    { /* lbl_8041466D */
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_HP_CHECK, 17, (u8*)&lbl_80414685},
        {WS_JUMP, (u8*)&lbl_804145CD},
    },
    { /* lbl_80414685 */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_80414685 + 0x46},
        {WS_STATUS_SET8, 7, 0, 0, 94, 0, (u8*)&fight_seq_renzoku_count},
        {WS_MESSAGE, 0x4E3A},
        {WS_MESSAGE_WAIT, 64},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_TSUIKA_CHECK},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 2},
        {WS_WKC_ACT, 1, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 4},
        {WS_WKC_ACT, 0, 0},
        {WS_WAZAEND},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TEXTURE, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E60},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 8},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_KAIFUKU, (u8*)&WAZA_Mantan, 17},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 255},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4E62},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SPEABI_CHECK, 18, 17, (u8*)&lbl_804147A4 + 0x19},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION_CHECK, 18, 3, (u8*)&lbl_804147A4},
        {WS_CONDITION_CHECK, 18, 4, (u8*)&lbl_804147A4},
        {WS_CONDITION_CHECK, 18, 1, (u8*)&WAZA_Umakukimaran},
        {WS_CHECK_TYPE, 18, 3, (u8*)&lbl_80415CC6},
        {WS_CHECK_TYPE, 18, 8, (u8*)&lbl_80415CC6},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 6},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_804147A4 */
        {WS_WAIT, 64},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E43},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_STATUS_GET32, 7, 0, 0, 66, 0, (u8*)&fight_seq_ulong_buff},
        {WS_STATUS_SET32, 7, 0, 0, 71, 0, (u8*)&fight_seq_ulong_buff},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 0},
        {WS_GOSUB, (u8*)&WAZA_Meneki},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 11},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HIKARINOKABE},
        {WS_JUMP, (u8*)&lbl_80414B70 + 0x96},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 9},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION_CHECK, 17, 8, (u8*)&lbl_804147A4 + 0xB9},
        {WS_SAWAGU_CHECK, (u8*)&lbl_804147A4 + 0xA0},
        {WS_NEMURU, (u8*)&WAZA_Mantan},
        {WS_WAIT, 32},
        {WS_STATUS_EFFECT, 17},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&NemuruMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_CONDITION_GAUGE, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_CLIENT_BIT_WAIT},
        {WS_JUMP, (u8*)&WAZA_Kaifuku},
        {WS_WAIT, 64},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE_TBL, (u8*)&SleepNGMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4E3E},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFF},
        {WS_TYPE_CHECK},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&WAZA_Hit},
        {WS_ICHIGEKI, (u8*)&lbl_804147A4 + 0x107},
        {WS_MICHIDURE_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_WAIT, 64},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE_TBL, (u8*)&IchigekiMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&lbl_804148ED},
        {WS_IF32, 4, (u8*)&ServerStatusFlag, 512, (u8*)&lbl_804148ED},
        {WS_SETVALUE, (u8*)&fight_seq_tame_msg, 0},
        {WS_BADGECHECK},
        {WS_GOSUB, (u8*)&lbl_80414930},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_804148ED */
        {WS_BADGECHECK},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 12},
        {WS_SETVALUE, SEQ_USER_WORK(0x16002), 1},
        {WS_SAKUJO, 17},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x800},
        {WS_STATUS_GET16, 7, 0, 0, 55, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 1, (u8*)&fight_seq_ushort_buff, 143, (u8*)&lbl_804140DF},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 8},
        {WS_JUMP, (u8*)&lbl_804140DF},
    },
    { /* lbl_80414930 */
        {WS_PP_DEC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 255},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x8000000},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 76},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_SETWORK, (u8*)&ServerWork + 0x5, (u8*)&fight_seq_tame_msg, 1},
        {WS_MESSAGE_TBL, (u8*)&TameMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TYPE_CHECK},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_batugun},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_imahitotu},
        {WS_HPHALF},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TYPE_CHECK},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_batugun},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_imahitotu},
        {WS_STATUS_SET32, 7, 0, 0, 62, 0, (u8*)&fight_seq_value_40},
        {WS_KORAERU_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_STATUS_GET16, 7, 0, 0, 55, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 1, (u8*)&fight_seq_ushort_buff, 250, (u8*)&lbl_80414930 + 0xFD},
        {WS_WAZAKOUKA_CHECK, 18, 33, 0, (u8*)&lbl_80414930 + 0xFD},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x40000},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 13},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_RENZOKU, 2},
        {WS_RENZOKU_NUM_INIT},
        {WS_SETVALUE, (u8*)&fight_seq_server_work3_temp, 0},
        {WS_JUMP, (u8*)&lbl_804145CD},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&lbl_80414930 + 0x12D, 0},
        {WS_JUMP, (u8*)&WAZA_HitCalc},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAIT, 64},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff2, 67},
        {WS_STATUS_GET8, 7, 0, 0, 59, (u8*)&fight_seq_uchar_buff2, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 1, (u8*)&WAZA_WazaEnd},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
        {WS_DAMAGE_CHG, 1},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_nohit},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4E7B},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_nohit},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SHIROIKIRI},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&ShiroikiriMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 17, 15, (u8*)&WAZA_Umakukimaran},
        {WS_KIAIDAME},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&KiaidameMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 206},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SPEABI_CHECK, 18, 20, (u8*)&WAZA_Mypace},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION2_CHECK, 18, 9, (u8*)&lbl_80414B70},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 7},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_80414B70 */
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E5B},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 33},
        {WS_JUMP, (u8*)&lbl_80414439},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 34},
        {WS_JUMP, (u8*)&lbl_80414439},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 35},
        {WS_JUMP, (u8*)&lbl_80414439},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 36},
        {WS_JUMP, (u8*)&lbl_80414439},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 37},
        {WS_JUMP, (u8*)&lbl_80414439},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HENSHIN},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&HenshinMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 161},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 162},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 163},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 165},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_REFLEC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE_TBL, (u8*)&ReflecMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SPEABI_CHECK, 18, 17, (u8*)&lbl_804147A4 + 0x19},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION_CHECK, 18, 3, (u8*)&lbl_804147A4},
        {WS_CONDITION_CHECK, 18, 4, (u8*)&lbl_804147A4},
        {WS_CHECK_TYPE, 18, 3, (u8*)&lbl_80415CC6},
        {WS_CHECK_TYPE, 18, 8, (u8*)&lbl_80415CC6},
        {WS_CONDITION_CHECK, 18, 1, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 2},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SPEABI_CHECK, 18, 7, (u8*)&lbl_80414B70 + 0x191},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_TYPE_CHECK},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION_CHECK, 18, 5, (u8*)&lbl_80414B70 + 0x178},
        {WS_CONDITION_CHECK, 18, 1, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 5},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E53},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_STATUS_GET32, 7, 0, 0, 66, 0, (u8*)&fight_seq_ulong_buff},
        {WS_STATUS_SET32, 7, 0, 0, 71, 0, (u8*)&fight_seq_ulong_buff},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 0},
        {WS_GOSUB, (u8*)&WAZA_Juunan},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 22},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 17},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 23},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 24},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 19},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 25},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 20},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 26},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 21},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 27},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 22},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&lbl_804148ED},
        {WS_IF32, 4, (u8*)&ServerStatusFlag, 512, (u8*)&lbl_804148ED},
        {WS_SETVALUE, (u8*)&fight_seq_tame_msg, 3},
        {WS_BADGECHECK},
        {WS_GOSUB, (u8*)&lbl_80414930},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 7},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_SETVALUE, (u8*)&fight_seq_server_work3_temp, 2},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_RENZOKU, 2},
        {WS_RENZOKU_NUM_INIT},
        {WS_JUMP, (u8*)&lbl_804145CD},
        {WS_BADGECHECK},
        {WS_PP_DEC},
        {WS_ATTACK_MESSAGE},
        {WS_CLIENT_BIT_WAIT},
        {WS_CONDITION2_CHECK, 17, 20, (u8*)&lbl_80414B70 + 0x2C6},
        {WS_MIGAWARI},
        {WS_IF8, 1, (u8*)&ServerWork + 0x5, 1, (u8*)&lbl_80414B70 + 0x29A},
        {WS_JUMP, (u8*)&lbl_80414B70 + 0x2B0},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_MESSAGE_TBL, (u8*)&MigawariMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE_TBL, (u8*)&MigawariMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4E9B},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 221},
        {WS_JUMP, (u8*)&WAZA_HitCalc},
    },
    { /* WAZA_Handou */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4E9E},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_Handou + 0x32, 0},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 30},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 0},
        {WS_JUMP, (u8*)&WAZA_HitCalc},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 30},
        {WS_SAKUJO, 17},
        {WS_JUMP, (u8*)&WAZA_NormalNohit},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFF},
        {WS_MONOMANE, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F4B},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_WAIT, 32},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x16002), 0},
        {WS_SETVALUE, SEQ_USER_WORK(0x160A1), 0},
        {WS_YUBIWOHURU},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_WAIT, 32},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Handou + 0x99, 0},
        {WS_YADORIGI},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&YadorigiMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F28},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_KANASHIBARI, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EA0},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TYPE_CHECK},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_batugun},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_imahitotu},
        {WS_CHIKYUUNAGE},
        {WS_KORAERU_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TYPE_CHECK},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_batugun},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_imahitotu},
        {WS_PSYCHOWAVE},
        {WS_KORAERU_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_BADGECHECK},
        {WS_COUNTER, (u8*)&lbl_80415C91},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TYPE_CHECK_NO_HIT},
        {WS_KORAERU_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_ENCORE, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EA2},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFF},
        {WS_ITAMIWAKE, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 17},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_STATUS_SET32, 7, 0, 0, 62, 0, (u8*)&WazaDamage},
        {WS_HP_DEC, 18},
        {WS_MESSAGE, 0x4F3F},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_CONDITION_CHECK, 17, 8, (u8*)&WAZA_Handou + 0x1EA},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_JUMP, (u8*)&WAZA_Umakukimaran},
        {WS_STATUS_GET16, 7, 0, 0, 56, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 214, (u8*)&WAZA_Handou + 0x218},
        {WS_STATUS_EFFECT, 17},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E87},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit2, 0},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 8},
        {WS_JUMP, (u8*)&WAZA_HitCalcOnly},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TEXTURE2, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E60},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_LOCKON},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EA4},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_SKETCH, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EA5},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_CONDITION_CHECK, 17, 8, (u8*)&WAZA_Handou + 0x2A6},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_JUMP, (u8*)&WAZA_Umakukimaran},
        {WS_STATUS_EFFECT, 17},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E87},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x800},
        {WS_NEGOTO, (u8*)&WAZA_Handou + 0x2CC},
        {WS_WAIT, 64},
        {WS_JUMP, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x16002), 0},
        {WS_SETVALUE, SEQ_USER_WORK(0x160A1), 0},
        {WS_WAZASEQADRS, 1},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_MICHIDURE, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EA6},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_JITABATA},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_URAMI, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EA8},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_IYASHINOSUZU},
        {WS_CLIENT_BIT_WAIT},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&IyashiNoSuzuMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_STATUS_GET16, 7, 0, 0, 55, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 1, (u8*)&fight_seq_ushort_buff, 215, (u8*)&WAZA_Handou + 0x388},
        {WS_IF8, 5, (u8*)&ServerWork + 0x5, 1, (u8*)&WAZA_Handou + 0x36C},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4EFC},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_IF8, 5, (u8*)&ServerWork + 0x5, 2, (u8*)&WAZA_Handou + 0x388},
        {WS_FIGHT_EFFECT, 25, 23, 0},
        {WS_MESSAGE, 0x4EFD},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_CONDITION_GAUGE, 17},
        {WS_CONDITION_GAUGE, 25},
        {WS_CLIENT_BIT_WAIT},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SETVALUE, (u8*)&fight_seq_triple_kick_pow, 0},
        {WS_RENZOKU_NUM_INIT},
        {WS_LOOPCNT, 3},
    },
    { /* lbl_804151FD */
        {WS_STATUS_GET16, 7, 0, 0, 56, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 214, (u8*)&lbl_804151FD + 0x2A},
        {WS_CONDITION_CHECK, 17, 8, (u8*)&lbl_804152CC},
        {WS_HITCHECK, (u8*)&lbl_804152CC, 0},
        {WS_LOOP_INIT},
        {WS_ADDVALUE, (u8*)&fight_seq_triple_kick_pow, 10},
        {WS_STATUS_SET8, 7, 0, 0, 63, 0, (u8*)&fight_seq_triple_kick_pow},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_804152CC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_ADDVALUE, (u8*)&fight_seq_renzoku_count, 1},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff2, 70},
        {WS_STATUS_GET8, 7, 0, 0, 59, (u8*)&fight_seq_uchar_buff2, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 1, (u8*)&lbl_804152F2},
        {WS_HP_CHECK, 18, (u8*)&lbl_804152F2},
        {WS_LOOP, (u8*)&lbl_804151FD + 0xB7},
        {WS_JUMP, (u8*)&lbl_804152F2},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_HP_CHECK, 17, (u8*)&lbl_804152CC},
        {WS_JUMP, (u8*)&lbl_804151FD},
    },
    { /* lbl_804152CC */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_IF8, 0, (u8*)&fight_seq_renzoku_count, 0, (u8*)&lbl_804152F2},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_nohit},
    },
    { /* lbl_804152F2 */
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_IF8, 0, (u8*)&fight_seq_renzoku_count, 0, (u8*)&lbl_804152F2 + 0x2B},
        {WS_STATUS_SET8, 7, 0, 0, 94, 0, (u8*)&fight_seq_renzoku_count},
        {WS_MESSAGE, 0x4E3A},
        {WS_MESSAGE_WAIT, 64},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_TSUIKA_CHECK},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 14},
        {WS_WKC_ACT, 0, 0},
        {WS_WAZAEND},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 31},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFE},
        {WS_CONDITION2_CHECK, 18, 22, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 32},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_MESSAGE, 0x4EAA},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION2_CHECK, 18, 23, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION_CHECK, 18, 8, (u8*)&lbl_804152F2 + 0xB0},
        {WS_JUMP, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 255},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 33},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_MESSAGE, 0x4EAB},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_CHIISAKUNARU},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 23},
        {WS_JUMP, (u8*)&lbl_8041443A},
        {WS_MONS_TYPE, 17, 7, (u8*)&lbl_80415460 + 0xA},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDCHG_CHECK, 17, 2, 3, 0, (u8*)&lbl_804153ED},
        {WS_CONDCHG_CHECK, 17, 1, 1, 12, (u8*)&lbl_804153ED},
        {WS_CONDCHG_CHECK, 17, 0, 2, 12, (u8*)&WAZA_Umakukimaran},
    },
    { /* lbl_804153ED */
        {WS_STATUS_GET32, 7, 0, 0, 54, 0, (u8*)&fight_seq_fightout_pokemon_ptr},
        {WS_STATUS_SET32, 7, 0, 0, 67, 0, (u8*)&fight_seq_fightout_pokemon_ptr},
        {WS_SETVALUE, SEQ_USER_WORK(0x16002), 1},
        {WS_FIGHT_EFFECT, 17, 26, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 147},
        {WS_CONDCHG, 65, (u8*)&lbl_80415438},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_80415438 */
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 17},
        {WS_CONDCHG, 65, (u8*)&lbl_8041544C},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_8041544C */
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_CONDCHG, 65, (u8*)&lbl_80415460},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_80415460 */
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_STATUS_GET32, 7, 0, 0, 54, 0, (u8*)&fight_seq_fightout_pokemon_ptr},
        {WS_STATUS_GET32, 7, 0, 0, 66, 0, (u8*)&fight_seq_fightout_pokemon_ptr2},
        {WS_IFWNE, (u8*)&fight_seq_fightout_pokemon_ptr, (u8*)&fight_seq_fightout_pokemon_ptr2, 4, (u8*)&lbl_804154A3},
        {WS_SUBROUTINE_CALL, 17, 3},
    },
    { /* lbl_804154A3 */
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFF},
        {WS_NOROI, (u8*)&WAZA_Umakukimaran},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_SETVALUE, SEQ_USER_WORK(0x16002), 0},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EAD},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_GUARD_SUCCESS_CHECK},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&MamoruMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_MAKIBISHI, (u8*)&lbl_80415C91},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EAF},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_MIYABURU},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EB1},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HOROBINOUTA, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F41},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_banme_buff, 0},
        {WS_SETVALUE, (u8*)&fight_seq_banme_max, 8},
        {WS_STATUS_GET32, 7, 0, 0, 93, (u8*)&fight_seq_banme_buff, (u8*)&fight_seq_ulong_buff},
        {WS_IF32, 0, (u8*)&fight_seq_ulong_buff, 0, (u8*)&lbl_804155CE},
        {WS_STATUS_GET8, 5, (u8*)&fight_seq_ulong_buff, 0, 291, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_804155CE},
        {WS_STATUS_SET32, 7, 0, 0, 75, 0, (u8*)&fight_seq_ulong_buff},
        {WS_STATUS_SET32, 7, 0, 0, 66, 0, (u8*)&fight_seq_ulong_buff},
        {WS_SPEABI_CHECK, 25, 43, (u8*)&lbl_804155CE + 0x19},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
    },
    { /* lbl_804155CE */
        {WS_ADDVALUE, (u8*)&fight_seq_banme_buff, 1},
        {WS_IFWNE, (u8*)&fight_seq_banme_buff, (u8*)&fight_seq_banme_max, 1, (u8*)&lbl_804154A3 + 0xB8},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_FIGHT_EFFECT, 25, 23, 0},
        {WS_MESSAGE, 0x4EFD},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_804155CE},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WEATHER_CHANGE, 86, 3},
        {WS_JUMP, (u8*)&lbl_804157C8},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&lbl_80415615},
        {WS_PP_DEC},
    },
    { /* lbl_80415615 */
        {WS_HITCHECK, (u8*)&lbl_80415615 + 0x7, 0},
        {WS_TYPE_CHECK_NO_HIT},
        {WS_KOROGARU},
        {WS_JUMP, (u8*)&WAZA_HitCalcOnly},
        {WS_BADGECHECK},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&lbl_80414119},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_IBARU, 1, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 33},
        {WS_CONDCHG, 1, (u8*)&lbl_8041566B},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_8041566B},
        {WS_COND_CHG_WORK_SET},
        {WS_FIGHT_EFFECT, 18, 1, 0xFF0160A4},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
    },
    { /* lbl_8041566B */
        {WS_SPEABI_CHECK, 18, 20, (u8*)&WAZA_Mypace},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 7},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&lbl_80415692, 0},
    },
    { /* lbl_80415692 */
        {WS_RENZOKUGIRI},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_80415692},
        {WS_DAMAGE_LOSS},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_MEROMERO, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E5C},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_NATSUKI},
        {WS_JUMP, (u8*)&WAZA_HitCalc},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TYPE_CHECK},
        {WS_PRESENT},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SHINPINOMAMORI},
        {WS_JUMP, (u8*)&lbl_80414B70 + 0x96},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 3},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_JISIN},
        {WS_MAGNITUDE},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4EB5},
        {WS_MESSAGE_WAIT, 64},
        {WS_JUMP, (u8*)&lbl_804157C8 + 0x137},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_RESHUFFLE_CHECK, 17, (u8*)&WAZA_Umakukimaran, 0},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SUBROUTINE_CALL, 17, 7},
        {WS_POKE_RESHUFFLE, 17, (u8*)&WAZA_Umakukimaran},
        {WS_SIZENKAIHUKU, 17},
        {WS_CLIENT_BIT_WAIT},
        {WS_POKE_RESHUFFLE_WAIT, 17, 2},
        {WS_POKEDELACTOR, 17},
        {WS_APPEAR_EFFECT_INIT, 17},
        {WS_APPEAR_EFFECT, 17, 1},
        {WS_POKE_HPMAX_RATE, 17},
        {WS_MESSAGE_TBL, (u8*)&AppearMsgTbl},
        {WS_APPEAR_EFFECT_WAIT, 17, 1},
        {WS_MESSAGE_WAIT, 0},
        {WS_CLIENT_BIT_WAIT},
        {WS_POKE_RESHUFFLE_END, 17},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 163},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TYPE_CHECK},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_batugun},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_imahitotu},
        {WS_STATUS_SET32, 7, 0, 0, 62, 0, (u8*)&fight_seq_value_20},
        {WS_KORAERU_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WEATHERKAIFUKU, (u8*)&WAZA_Mantan},
        {WS_JUMP, (u8*)&WAZA_Kaifuku},
        {WS_MEZAMERUPOWER},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WEATHER_CHANGE, 85, 0},
    },
    { /* lbl_804157C8 */
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&TenkouMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_GOSUB, (u8*)&WAZA_Kasokusouti + 0x22},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WEATHER_CHANGE, 84, 4},
        {WS_JUMP, (u8*)&lbl_804157C8},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 80},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 79},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 17},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 98},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HARADAIKO, (u8*)&WAZA_Umakukimaran},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4EB6},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_JIKOANJI, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EB7},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_MIRRORCOAT, (u8*)&lbl_80415C91},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TYPE_CHECK_NO_HIT},
        {WS_KORAERU_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&lbl_804148ED},
        {WS_IF32, 4, (u8*)&ServerStatusFlag, 512, (u8*)&lbl_804148ED},
        {WS_SETVALUE, (u8*)&fight_seq_tame_msg, 2},
        {WS_BADGECHECK},
        {WS_GOSUB, (u8*)&lbl_80414930},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_CONDCHG, 65, (u8*)&lbl_804157C8 + 0xF5},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_804157C8 + 0xF5},
        {WS_COND_CHG_WORK_SET},
        {WS_FIGHT_EFFECT, 17, 1, 0xFF0160A4},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_WAZAKOUKA_CHECK, 18, 31, 0, (u8*)&lbl_804157C8 + 0x128},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x10000},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 8},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_JISIN},
        {WS_LOOP_INIT},
        {WS_WAZAKOUKA_CHECK, 18, 32, 0, (u8*)&lbl_804157C8 + 0x16B},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x20000},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_JUMP, (u8*)&lbl_804157C8 + 0x18E},
        {WS_RESET32BIT, (u8*)&ServerStatusFlag, 0x20000},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 1},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_HITCHECK, (u8*)&lbl_804157C8 + 0x1C5, 0},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_JIBAKU_LOOP, (u8*)&lbl_804157C8 + 0x137, 1},
        {WS_WAZAEND},
        {WS_WAIT, 32},
        {WS_TYPE_CHECK},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_SE},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_JIBAKU_LOOP, (u8*)&lbl_804157C8 + 0x137, 1},
        {WS_WAZAEND},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_MIRAIYOCHI, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&MiraiyochiMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_WAZAKOUKA_CHECK, 18, 31, 0, (u8*)&lbl_80414090},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x10000},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_WAZAKOUKA_CHECK, 18, 35, 0, (u8*)&lbl_804157C8 + 0x128},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_JUMP, (u8*)&lbl_804157C8 + 0x128},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 1},
        {WS_STATUS_GET16, 7, 0, 0, 19, (u8*)&fight_seq_uchar_buff, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 1, (u8*)&lbl_80415A75},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&lbl_804148ED},
        {WS_IF32, 4, (u8*)&ServerStatusFlag, 512, (u8*)&lbl_804148ED},
        {WS_SETVALUE, (u8*)&fight_seq_tame_msg, 1},
        {WS_BADGECHECK},
        {WS_GOSUB, (u8*)&lbl_80414930},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_80415A75 */
        {WS_BADGECHECK},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x8000000},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 76},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_EFFECT_WAIT, 4},
        {WS_PP_DEC},
        {WS_JUMP, (u8*)&lbl_804148ED + 0x1},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 5},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x10000},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SUBROUTINE_CALL, 1, 2},
        {WS_IF8, 0, (u8*)&ServerWork, 1, (u8*)&WAZA_Umakukimaran},
        {WS_IF8, 0, (u8*)&ServerWork, 2, (u8*)&lbl_804162A5 + 0x28},
        {WS_TELEPORT, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x500A},
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_WAIT, 32},
        {WS_PP_DEC},
        {WS_SETVALUE, (u8*)&ServerWork, 0},
        {WS_LOOP_INIT},
        {WS_HUKURODATAKI, (u8*)&lbl_80415A75 + 0xD0, (u8*)&WAZA_Umakukimaran},
        {WS_CRITICAL_CHECK},
        {WS_STATUS_GET8, 7, 0, 0, 58, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 1, (u8*)&fight_seq_uchar_buff, 2, (u8*)&lbl_80415A75 + 0x9B},
        {WS_DAMAGE_CHG, 2},
        {WS_DAMAGE_LOSS},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4EBE},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_MESSAGE_WAIT, 64},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_JUMP, (u8*)&lbl_80415A75 + 0x6F},
        {WS_WAZAEND},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&lbl_80415BC9},
        {WS_IF32, 4, (u8*)&ServerStatusFlag, 512, (u8*)&lbl_80415BC9},
        {WS_STATUS_GET16, 7, 0, 0, 55, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 19, (u8*)&lbl_80415A75 + 0x142},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 291, (u8*)&lbl_80415A75 + 0x137},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 340, (u8*)&lbl_80415A75 + 0x12C},
        {WS_SETVALUE, (u8*)&fight_seq_tame_msg, 5},
        {WS_JUMP, (u8*)&lbl_80415BBD},
        {WS_SETVALUE, (u8*)&fight_seq_tame_msg, 7},
        {WS_JUMP, (u8*)&lbl_80415BBD},
        {WS_SETVALUE, (u8*)&fight_seq_tame_msg, 6},
        {WS_JUMP, (u8*)&lbl_80415BBD},
        {WS_SETVALUE, (u8*)&fight_seq_tame_msg, 4},
    },
    { /* lbl_80415BBD */
        {WS_BADGECHECK},
        {WS_GOSUB, (u8*)&lbl_80414930},
        {WS_KIERUTAME},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_80415BC9 */
        {WS_BADGECHECK},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 12},
        {WS_SETVALUE, SEQ_USER_WORK(0x16002), 1},
        {WS_SAKUJO, 17},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x800},
        {WS_STATUS_GET16, 7, 0, 0, 55, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 1, (u8*)&fight_seq_ushort_buff, 340, (u8*)&lbl_80415BC9 + 0x3E},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 5},
        {WS_HITCHECK, (u8*)&lbl_80415C14, 0},
        {WS_KIERUTAME_AFTAR},
        {WS_JUMP, (u8*)&WAZA_HitCalc},
    },
    { /* lbl_80415C14 */
        {WS_KIERUTAME_AFTAR},
        {WS_JUMP, (u8*)&WAZA_NormalNohit},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_MARUKUNARU},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_CONDCHG, 65, (u8*)&lbl_80415C14 + 0x24},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&WAZA_CondUpMsg},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_8041443A + 0x1E},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_KAIFUKU, (u8*)&WAZA_Mantan, 18},
    },
    { /* WAZA_Kaifuku */
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 255},
        {WS_EFFECT_WAIT, 1},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 18},
        {WS_MESSAGE, 0x4E62},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Mantan */
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E63},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_NEKODAMASHI, (u8*)&lbl_80415C91},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 136},
        {WS_JUMP, (u8*)&lbl_80414090},
    },
    { /* lbl_80415C91 */
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
    },
    { /* WAZA_Umakukimaran */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_umakukimaran},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_PP_DEC},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_JUMP, (u8*)&WAZA_Umakukimaran + 0x7},
    },
    { /* lbl_80415CC6 */
        {WS_WAIT, 32},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_koukanai},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 74},
        {WS_ATTACK_MESSAGE},
        {WS_CONDITION2_CHECK, 17, 34, (u8*)&lbl_80415D09},
        {WS_PP_DEC},
    },
    { /* lbl_80415D09 */
        {WS_SAWAGU},
        {WS_JUMP, (u8*)&WAZA_HitCalcOnly},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TAKUWAERU},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&TakuwaeruMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_IF8, 0, (u8*)&ServerWork + 0x6, 1, (u8*)&lbl_80415D09 + 0x56},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_HAKIDASU, (u8*)&lbl_80415D09 + 0x3D},
        {WS_TYPE_CHECK},
        {WS_KORAERU_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4F3A},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAIT, 64},
        {WS_HAKIDASU, (u8*)&lbl_80415D09 + 0x3D},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_NOMIKOMU, (u8*)&lbl_80415D09 + 0x7F},
        {WS_JUMP, (u8*)&WAZA_Kaifuku},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE_TBL, (u8*)&NomikomuMsgTbl},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WEATHER_CHANGE, 83, 5},
        {WS_JUMP, (u8*)&lbl_804157C8},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_ICHAMON, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EC3},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&lbl_80414119},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_IBARU, 4, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 20},
        {WS_CONDCHG, 1, (u8*)&lbl_80415D09 + 0x10C},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80415D09 + 0x10C},
        {WS_COND_CHG_WORK_SET},
        {WS_FIGHT_EFFECT, 18, 1, 0xFF0160A4},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SPEABI_CHECK, 18, 20, (u8*)&WAZA_Mypace},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 7},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_CONDITION_CHECK, 18, 6, (u8*)&lbl_80415D09 + 0x1B0},
        {WS_CHECK_TYPE, 18, 10, (u8*)&lbl_80415CC6},
        {WS_SPEABI_CHECK, 18, 41, (u8*)&lbl_80415D09 + 0x178},
        {WS_CONDITION_CHECK, 18, 1, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 3},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_STATUS_GET32, 7, 0, 0, 66, 0, (u8*)&fight_seq_ulong_buff},
        {WS_STATUS_SET32, 7, 0, 0, 71, 0, (u8*)&fight_seq_ulong_buff},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 0},
        {WS_GOSUB, (u8*)&WAZA_Mizunobeeru},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E49},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_IF8, 0, (u8*)&ServerWork + 0x6, 1, (u8*)&lbl_80415F43 + 0x27},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_OKIMIYAGE, (u8*)&WAZA_Umakukimaran},
        {WS_JIBAKU},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&lbl_80415F43 + 0xF},
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 18, 18, 7},
        {WS_COND_CHG_BIT_CHECK, 18, 2, 3},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 161},
        {WS_CONDCHG, 1, (u8*)&lbl_80415F20},
        {WS_IF8, 2, (u8*)&ServerWork + 0x5, 1, (u8*)&lbl_80415F20},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_80415F20 */
        {WS_COND_CHG_BIT_CHECK, 18, 16, 3},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 164},
        {WS_CONDCHG, 1, (u8*)&lbl_80415F43},
        {WS_IF8, 2, (u8*)&ServerWork + 0x5, 1, (u8*)&lbl_80415F43},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_80415F43 */
        {WS_MESSAGE_WAIT, 0},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EE4},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_80415F43},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_OKIMIYAGE, (u8*)&lbl_80415F43 + 0x2E},
        {WS_JIBAKU},
        {WS_WAIT, 64},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_SE},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_CONDITION_CHECK, 17, 2, (u8*)&lbl_80415F43 + 0x5B},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_KIAIPUNCH, (u8*)&lbl_804140DF},
        {WS_PP_DEC},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4EE1},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 164},
        {WS_CONDITION_CHECK, 18, 5, (u8*)&lbl_80415FF9},
        {WS_JUMP, (u8*)&lbl_80414090},
    },
    { /* lbl_80415FF9 */
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_KONOYUBITOMARE},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EBF},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_WAIT, 32},
        {WS_SHIZENNOCHIKARA},
    },
    { /* WAZA_ShizennochikaraHitMsg */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4EC1},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_JUUDEN},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EC0},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_CHOUHATSU, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EC5},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_TEDASUKE, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EC6},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_TRICK, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EC7},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&WAZA_ShizennochikaraHitMsg + 0xB2},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 0, (u8*)&WAZA_ShizennochikaraHitMsg + 0xD9},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 1, (u8*)&WAZA_ShizennochikaraHitMsg + 0xEF},
        {WS_JUMP, (u8*)&WAZA_ShizennochikaraHitMsg + 0x105},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4EC8},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4EC9},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_ShizennochikaraHitMsg + 0x105},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4EC8},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_ShizennochikaraHitMsg + 0x105},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4EC9},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_ShizennochikaraHitMsg + 0x105},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFF},
        {WS_NARIKIRI, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ECA},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_NEGAIGOTO, 0, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_NEKONOTE, (u8*)&WAZA_Umakukimaran + 0x26},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, SEQ_USER_WORK(0x16002), 0},
        {WS_SETVALUE, SEQ_USER_WORK(0x160A1), 0},
        {WS_WAZASEQADRS, 1},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_NEWOHARU, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ECD},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 229},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_MAGICCORT, (u8*)&lbl_80415C91},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4ED6},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_RECYCLE, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EDC},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_REVENGE},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit, 0},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_KAWARAWARI},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
        {WS_IF8, 0, SEQ_USER_WORK(0x16002), 0, (u8*)&WAZA_ShizennochikaraHitMsg + 0x1F5},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_nohit},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_koukanai},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_IF8, 3, SEQ_USER_WORK(0x16002), 2, (u8*)&WAZA_ShizennochikaraHitMsg + 0x20B},
        {WS_MESSAGE, 0x4EE3},
        {WS_MESSAGE_WAIT, 96},
        {WS_TYPE_CHECK_NO_HIT},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_TSUIKA_CHECK},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SPEABI_CHECK, 18, 72, (u8*)&lbl_804162A5},
        {WS_SPEABI_CHECK, 18, 15, (u8*)&lbl_804162A5},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&WAZA_Umakukimaran},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&WAZA_Shinpi},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFF},
        {WS_SAWAGU_CHECK, (u8*)&WAZA_Umakukimaran},
        {WS_AKUBI, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ED0},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_804162A5 */
        {WS_STATUS_GET32, 7, 0, 0, 72, 0, (u8*)&fight_seq_ulong_buff},
        {WS_STATUS_SET32, 7, 0, 0, 75, 0, (u8*)&fight_seq_ulong_buff},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4F0A},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 54},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_GAMUSYARA, (u8*)&WAZA_Umakukimaran},
        {WS_STATUS_GET32, 7, 0, 0, 62, 0, (u8*)&WazaDamage},
        {WS_STATUS_SET32, 7, 0, 0, 65, 0, (u8*)&WazaDamage},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit2, 0},
        {WS_TYPE_CHECK},
        {WS_STATUS_GET8, 7, 0, 0, 61, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&WAZA_Hit},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_batugun},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_imahitotu},
        {WS_STATUS_GET32, 7, 0, 0, 65, 0, (u8*)&WazaDamage},
        {WS_STATUS_SET32, 7, 0, 0, 62, 0, (u8*)&WazaDamage},
        {WS_KORAERU_CHECK},
        {WS_JUMP, (u8*)&WAZA_Hit},
        {WS_HUNKA},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0xFFFF},
        {WS_SKILLSWAP, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ED2},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HUUIN, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ED3},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_REFLESH, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EC2},
        {WS_MESSAGE_WAIT, 96},
        {WS_CONDITION_GAUGE, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_ONNEN, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ED4},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_YOKODORI, (u8*)&lbl_80415C91},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4ED8},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_KETAGURI},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit2, 0},
        {WS_JUMP, (u8*)&WAZA_HitCalcOnly},
        {WS_HIMITUNOTIKARA},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 230},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_SETVALUE, (u8*)&fight_seq_banme_buff, 0},
        {WS_SETVALUE, (u8*)&fight_seq_banme_max, 8},
        {WS_LOOP_INIT},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 7},
        {WS_STATUS_GET32, 7, 0, 0, 93, (u8*)&fight_seq_banme_buff, (u8*)&fight_seq_ulong_buff},
        {WS_IF32, 0, (u8*)&fight_seq_ulong_buff, 0, (u8*)&lbl_80416526},
        {WS_STATUS_GET8, 5, (u8*)&fight_seq_ulong_buff, 0, 291, 0, (u8*)&fight_seq_uchar_buff},
        {WS_IF8, 0, (u8*)&fight_seq_uchar_buff, 0, (u8*)&lbl_80416526},
        {WS_STATUS_GET32, 7, 0, 0, 54, 0, (u8*)&fight_seq_fightout_pokemon_ptr},
        {WS_IFWEQ, (u8*)&fight_seq_fightout_pokemon_ptr, (u8*)&fight_seq_ulong_buff, 4, (u8*)&lbl_80416526},
        {WS_STATUS_SET32, 7, 0, 0, 67, 0, (u8*)&fight_seq_ulong_buff},
        {WS_SPEABI_CHECK, 18, 20, (u8*)&lbl_80416526 + 0x15},
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&lbl_8041656D},
        {WS_CONDITION2_CHECK, 18, 9, (u8*)&lbl_8041656D + 0x19},
        {WS_HP_CHECK, 18, (u8*)&lbl_80416526},
        {WS_HITCHECK, (u8*)&lbl_8041656D + 0x32, 0},
        {WS_SIDECONDITION_CHECK, 18, 75, (u8*)&lbl_80416526 + 0x2E},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
    },
    { /* lbl_8041651D */
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
    },
    { /* lbl_80416526 */
        {WS_ADDVALUE, (u8*)&fight_seq_banme_buff, 1},
        {WS_IFWNE, (u8*)&fight_seq_banme_buff, (u8*)&fight_seq_banme_max, 1, (u8*)&lbl_804162A5 + 0x1C0},
        {WS_WAZAEND},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4EF4},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_8041651D},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E68},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_8041651D},
    },
    { /* lbl_8041656D */
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4F29},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_8041651D},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E5B},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_8041651D},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_8041651D},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_ASOBI, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&AsobiMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 6},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_WEATHER_BALL},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 251},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDCHG_CHECK, 18, 2, 1, 0, (u8*)&lbl_8041656D + 0x8F},
        {WS_CONDCHG_CHECK, 18, 0, 2, 0, (u8*)&lbl_80416660},
        {WS_HITCHECK, (u8*)&WAZA_Umakukimaran, 0},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 18, 6, 5},
        {WS_COND_CHG_BIT_CHECK, 18, 2, 1},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 145},
        {WS_CONDCHG, 1, (u8*)&lbl_80416633},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80416633},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_80416633 */
        {WS_COND_CHG_BIT_CHECK, 18, 4, 1},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 146},
        {WS_CONDCHG, 1, (u8*)&lbl_80416633 + 0x23},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80416633 + 0x23},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_WAIT, 64},
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_80416660 */
        {WS_WAIT, 32},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_umakukimaran},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4F19},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDCHG_CHECK, 17, 3, 2, 12, (u8*)&lbl_80416660 + 0x42},
        {WS_CONDCHG_CHECK, 17, 0, 5, 12, (u8*)&lbl_804167D9},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 17, 36, 0},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_CONDCHG, 65, (u8*)&lbl_80416660 + 0x6E},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80416660 + 0x6E},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 21},
        {WS_CONDCHG, 65, (u8*)&lbl_80416660 + 0x8D},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80416660 + 0x8D},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x10000},
        {WS_JUMP, (u8*)&lbl_80414090},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDCHG_CHECK, 17, 3, 1, 12, (u8*)&lbl_80416660 + 0xBA},
        {WS_CONDCHG_CHECK, 17, 0, 2, 12, (u8*)&lbl_804167D9},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 17, 6, 0},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 17},
        {WS_CONDCHG, 65, (u8*)&lbl_80416660 + 0xE6},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80416660 + 0xE6},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_CONDCHG, 65, (u8*)&lbl_80416660 + 0x105},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80416660 + 0x105},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDCHG_CHECK, 17, 3, 4, 12, (u8*)&lbl_80416660 + 0x124},
        {WS_CONDCHG_CHECK, 17, 0, 5, 12, (u8*)&lbl_804167D9},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 17, 48, 0},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 20},
        {WS_CONDCHG, 65, (u8*)&lbl_804167B0},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_804167B0},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_804167B0 */
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 21},
        {WS_CONDCHG, 65, (u8*)&lbl_804167CF},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_804167CF},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_804167CF */
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_804167D9 */
        {WS_WAIT, 32},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_umakukimaran},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4F18},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CONDCHG_CHECK, 17, 3, 1, 12, (u8*)&lbl_804167D9 + 0x42},
        {WS_CONDCHG_CHECK, 17, 0, 3, 12, (u8*)&lbl_804167D9},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 17, 10, 0},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 17},
        {WS_CONDCHG, 65, (u8*)&lbl_80416847},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80416847},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_80416847 */
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 19},
        {WS_CONDCHG, 65, (u8*)&lbl_80416847 + 0x1F},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80416847 + 0x1F},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_HOGOSYOKU, (u8*)&WAZA_Umakukimaran},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E60},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 167},
        {WS_JUMP, (u8*)&lbl_804144CD},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WEATHER_CHANGE, 82, 6},
        {WS_JUMP, (u8*)&lbl_804157C8},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_DARKREMOVE},
        {WS_WAZA_EFFECT},
        {WS_MESSAGE_TBL, (u8*)&DarkRemoveMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
        {WS_BADGECHECK},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_JIBAKU_INIT, 0},
        {WS_LOOP_INIT},
        {WS_TYPE_CHECK},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_batugun},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_imahitotu},
        {WS_HPHALF},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 221},
        {WS_HITCHECK, (u8*)&lbl_80416847 + 0xDA, 0},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_JIBAKU_LOOP, (u8*)&lbl_80416847 + 0x6E, 0},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_TSUIKA_CHECK},
        {WS_WAZAEND},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_WAZAKOUKA_SE},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_JIBAKU_LOOP, (u8*)&lbl_80416847 + 0x6E, 0},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_TSUIKA_CHECK},
        {WS_WAZAEND},
    },
    { /* WAZA_KizetsuA */
        {WS_KIZETSU, 17},
        {WS_VOICE, 17},
        {WS_MESSAGE, 0x4E35},
        {WS_MESSAGE_WAIT, 112},
        {WS_KIZETSU_WAIT, 17},
        {WS_SEQRET},
    },
    { /* WAZA_KizetsuD */
        {WS_KIZETSU, 18},
        {WS_VOICE, 18},
        {WS_MESSAGE, 0x4E36},
        {WS_MESSAGE_WAIT, 112},
        {WS_KIZETSU_WAIT, 18},
        {WS_SEQRET},
    },
    { /* WAZA_KizetsuK */
        {WS_KIZETSU, 21},
        {WS_VOICE, 21},
        {WS_MESSAGE, 0x4FCD},
        {WS_MESSAGE_WAIT, 112},
        {WS_KIZETSU_WAIT, 21},
        {WS_SEQRET},
    },
    { /* WAZA_GetEXP */
        {WS_GET_EXP, 21},
        {WS_SEQEND},
    },
    { /* WAZA_LevelUp */
        {WS_ME_PLAY, 967},
        {WS_MESSAGE, 0x4E26},
        {WS_MESSAGE_WAIT, 0},
        {WS_STATUS_WINDOW},
        {WS_WAZAOBOE_CHECK, (u8*)&lbl_804169D6, (u8*)&lbl_804169E7, 1},
        {WS_JUMP, (u8*)&WAZA_LevelUp + 0x25},
        {WS_WAZAOBOE_CHECK, (u8*)&lbl_804169D6, (u8*)&lbl_804169E7, 0},
        {WS_OBOEWAZANO_SET},
        {WS_MESSAGE, 0x4E28},
        {WS_MESSAGE, 0x4E29},
        {WS_MESSAGE, 0x4E2A},
        {WS_CLIENT_BIT_WAIT},
        {WS_WAZAWASURE_CHECK, (u8*)&WAZA_LevelUp + 0x50},
        {WS_MESSAGE, 0x4E2C},
        {WS_CLIENT_BIT_WAIT},
        {WS_WAZAAKIRAME_CHECK, (u8*)&WAZA_LevelUp + 0x25},
        {WS_MESSAGE, 0x4E2D},
        {WS_JUMP, (u8*)&WAZA_LevelUp + 0x1B},
        {WS_MESSAGE, 0x4F1C},
        {WS_MESSAGE, 0x4E2B},
        {WS_MESSAGE, 0x4F1D},
    },
    { /* lbl_804169D6 */
        {WS_OBOEWAZANO_SET},
        {WS_ME_PLAY, 967},
        {WS_MESSAGE, 0x4E27},
        {WS_SUBROUTINE_CALL, 0, 6},
        {WS_JUMP, (u8*)&WAZA_LevelUp + 0x1B},
    },
    { /* lbl_804169E7 */
        {WS_MESSAGE_WAIT, 32},
        {WS_SEQRET},
    },
    { /* WAZA_Zenmetsu */
        {WS_ZENMETSU_CHECK, 1},
        {WS_SEQEND},
    },
    { /* WAZA_MineReshuffleStart */
        {WS_POKE_RESHUFFLE, 21, (u8*)&WAZA_ZenmetsuEnd},
        {WS_POKE_RESHUFFLE_WAIT, 21, 2},
        {WS_BALL_GAUGE_SET, 21},
        {WS_APPEAR_EFFECT_INIT, 21},
        {WS_APPEAR_EFFECT, 21, 0},
        {WS_POKE_HPMAX_RATE, 21},
        {WS_MESSAGE_TBL, (u8*)&AppearMsgTbl},
        {WS_BALL_GAUGE_OFF, 21},
        {WS_APPEAR_EFFECT_WAIT, 21, 0},
        {WS_MESSAGE_WAIT, 0},
        {WS_POKE_RESHUFFLE_END, 21},
        {WS_STATUS_GET16, 7, 0, 0, 22, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 1, (u8*)&fight_seq_ushort_buff, 1, (u8*)&WAZA_ZenmetsuEnd},
        {WS_STATUS_GET16, 7, 0, 0, 24, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 1, (u8*)&fight_seq_ushort_buff, 1, (u8*)&WAZA_ZenmetsuEnd},
        {WS_SCA_END_SET},
    },
    { /* WAZA_ZenmetsuEnd */
        {WS_SEQEND},
    },
    { /* WAZA_OkodukaiCheck */
        {WS_OKODUKAI_CALC, (u8*)&WAZA_OkodukaiCheck + 0xD},
        {WS_MESSAGE, 0x4E37},
        {WS_MESSAGE_WAIT, 0},
        {WS_SEQEND},
    },
    { /* WAZA_KobanCheck */
        {WS_KOBAN_CHECK},
        {WS_SEQEND},
    },
    { /* WAZA_TrainerWin */
        {WS_MESSAGE, 0x4F4C},
        {WS_TRAINER_APPEAR, 1},
        {WS_CLIENT_BIT_WAIT},
        {WS_MESSAGE, 0x4E22},
        {WS_OKODUKAI_CALC, (u8*)&WAZA_Win},
        {WS_MESSAGE, 0x4E37},
        {WS_MESSAGE_WAIT, 64},
    },
    { /* WAZA_Win */
        {WS_KOBAN_CHECK},
        {WS_MONOHIROI},
        {WS_SEQEND},
    },
    { /* WAZA_Lose */
        {WS_MESSAGE, 0x4E38},
        {WS_MESSAGE_WAIT, 64},
        {WS_MESSAGE, 0x4E39},
        {WS_MESSAGE_WAIT, 64},
        {WS_SEQEND},
    },
    { /* WAZA_TuushinWin */
        {WS_MESSAGE, 5},
        {WS_MESSAGE_WAIT, 64},
        {WS_END_FIGHT},
        {WS_MESSAGE_WAIT, 64},
        {WS_SEQEND},
    },
    { /* WAZA_BattleTowerWin */
        {WS_MESSAGE, 0x4F4C},
        {WS_TRAINER_APPEAR, 1},
        {WS_CLIENT_BIT_WAIT},
        {WS_SEQEND},
    },
    { /* WAZA_ItemEscape */
        {WS_FIGHT_EFFECT, 1, 8, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 1},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_SpeabiEscape */
        {WS_MESSAGE, 1},
        {WS_MESSAGE_WAIT, 64},
        {WS_SEQEND},
    },
    { /* WAZA_Escape */
        {WS_MESSAGE, 0x4F21},
        {WS_MESSAGE_WAIT, 64},
        {WS_SEQEND},
    },
    { /* WAZA_EnemyEscape */
        {WS_MESSAGE, 1},
        {WS_MESSAGE_WAIT, 64},
        {WS_SEQEND},
    },
    { /* WAZA_TrainerEscape */
        {WS_MESSAGE, 1},
        {WS_SEQEND},
    },
    { /* WAZA_EscapeNG */
        {WS_MESSAGE_TBL, (u8*)&EscapeNGMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_SEQEND},
    },
    { /* WAZA_EscapeNG2 */
        {WS_ALERT_MESSAGE_TBL, (u8*)&EscapeNGMsgTbl},
        {WS_ALERTEND},
    },
    { /* WAZA_SafariBallThrowNG */
        {WS_ALERT_MESSAGE, 0x4F8B},
        {WS_ALERTEND},
    },
    { /* WAZA_PokeReshuffle */
        {WS_POKE_HPDEC_RATE, 20},
        {WS_MESSAGE_TBL, (u8*)&IrekaeMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_SETVALUE, (u8*)&fight_seq_banme_buff, 0},
        {WS_SETVALUE, (u8*)&fight_seq_banme_max, 8},
    },
    { /* lbl_80416B06 */
        {WS_OIUCHI_CHECK, (u8*)&lbl_80416B06 + 0xD},
        {WS_SWITCH_A_D},
        {WS_MICHIDURE_CHECK},
        {WS_GOSUB, (u8*)&lbl_80416B06 + 0x4F},
        {WS_SWITCH_A_D},
        {WS_ADDVALUE, (u8*)&fight_seq_banme_buff, 1},
        {WS_IF8, 3, (u8*)&fight_seq_banme_buff, 8, (u8*)&lbl_80416B06},
        {WS_SIZENKAIHUKU, 20},
        {WS_CLIENT_BIT_WAIT},
        {WS_MODOSU_EFFECT},
        {WS_CLIENT_BIT_WAIT},
        {WS_BALL_GAUGE_SET, 20},
        {WS_APPEAR_EFFECT_INIT, 20},
        {WS_APPEAR_EFFECT, 20, 0},
        {WS_POKE_HPMAX_RATE, 20},
        {WS_MESSAGE_TBL, (u8*)&AppearMsgTbl},
        {WS_BALL_GAUGE_OFF, 20},
        {WS_APPEAR_EFFECT_WAIT, 20, 0},
        {WS_MESSAGE_WAIT, 0},
        {WS_CLIENT_BIT_WAIT},
        {WS_POKE_RESHUFFLE_END, 20},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 4},
        {WS_WKC_ACT, 1, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 15},
        {WS_WKC_ACT, 1, 0},
        {WS_SEQEND},
        {WS_SETVALUE, (u8*)&fight_seq_uchar_buff, 2},
        {WS_STATUS_SET8, 7, 0, 0, 57, 0, (u8*)&fight_seq_uchar_buff},
        {WS_WAIT, 32},
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_CRITICAL_CHECK},
        {WS_DAMAGE_CALC},
        {WS_TYPE_CHECK},
        {WS_DAMAGE_LOSS},
        {WS_SETVALUE, (u8*)&fight_seq_oiuchiflag, 1},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_HP_DEC_WAIT, 18},
        {WS_CRITICAL_MESSAGE},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 3},
        {WS_WKC_ACT, 2, 6},
        {WS_SUBROUTINE_CALL, 18, 4},
        {WS_IF8, 0, (u8*)&ServerWork, 0, (u8*)&lbl_80416B06 + 0xAD},
        {WS_GET_EXP, 18},
        {WS_WAIT, 32},
        {WS_SEQRET},
    },
    { /* WAZA_Wait */
        {WS_WAIT, 32},
        {WS_SEQRET},
    },
    { /* WAZA_WeatherDamage */
        {WS_FIGHT_EFFECT, 17, 30, 0},
        {WS_MESSAGE_TBL, (u8*)&WeatherKeepMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_banme_buff, 0},
        {WS_SETVALUE, (u8*)&fight_seq_banme_max, 8},
        {WS_STATUS_GET32, 7, 0, 0, 89, (u8*)&fight_seq_banme_buff, (u8*)&fight_seq_ulong_buff},
        {WS_IF32, 0, (u8*)&fight_seq_ulong_buff, 0, (u8*)&WAZA_WeatherDamage + 0xA8},
        {WS_STATUS_SET32, 7, 0, 0, 54, 0, (u8*)&fight_seq_ulong_buff},
        {WS_WEATHER_KEEP},
        {WS_STATUS_GET32, 7, 0, 0, 62, 0, (u8*)&WazaDamage},
        {WS_IF32, 0, (u8*)&WazaDamage, 0, (u8*)&WAZA_WeatherDamage + 0xA8},
        {WS_FIGHT_EFFECT2, 17, 0xFF0160A4, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x1100120},
        {WS_HP_DEC, 17},
        {WS_MESSAGE_TBL, (u8*)&WeatherDamageMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 17},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_ZENMETSU_CHECK, 0},
        {WS_STATUS_GET16, 7, 0, 0, 92, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF8, 1, (u8*)&fight_seq_ushort_buff, 0, (u8*)&WAZA_WeatherDamage + 0xDB},
        {WS_ADDVALUE, (u8*)&fight_seq_banme_buff, 1},
        {WS_IFWNE, (u8*)&fight_seq_banme_buff, (u8*)&fight_seq_banme_max, 1, (u8*)&WAZA_WeatherDamage + 0x1D},
        {WS_RESET32BIT, (u8*)&ServerStatusFlag, 0x1100120},
        {WS_SEQEND},
    },
    { /* WAZA_WeatherDamageEnd */
        {WS_FIGHT_EFFECT, 17, 31, 0},
        {WS_MESSAGE_TBL, (u8*)&WeatherDamageEndMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Amefuri */
        {WS_FIGHT_EFFECT, 17, 30, 0},
        {WS_MESSAGE_TBL, (u8*)&AmagoiKeepMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&WAZA_Amefuri + 0x1C},
        {WS_SEQEND},
    },
    { /* WAZA_Hare */
        {WS_FIGHT_EFFECT, 17, 30, 0},
        {WS_MESSAGE, 0x4F35},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_HareEnd */
        {WS_FIGHT_EFFECT, 17, 31, 0},
        {WS_MESSAGE, 0x4F36},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_FieldWeather */
        {WS_MESSAGE_TBL, 0},
        {WS_MESSAGE_WAIT, 64},
        {WS_STATUS_GET16, 7, 0, 0, 19, (u8*)&fight_seq_uchar_buff, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 2, (u8*)&WAZA_FieldWeather + 0x5D},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 1, (u8*)&WAZA_FieldWeather + 0x6C},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 3, (u8*)&WAZA_FieldWeather + 0x7B},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 4, (u8*)&WAZA_FieldWeather + 0x8A},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 5, (u8*)&WAZA_FieldWeather + 0x99},
        {WS_JUMP, (u8*)&lbl_80416D9B},
        {WS_FIGHT_EFFECT2, 17, 10, 0},
        {WS_JUMP, (u8*)&lbl_80416D9B},
        {WS_FIGHT_EFFECT2, 17, 11, 0},
        {WS_JUMP, (u8*)&lbl_80416D9B},
        {WS_FIGHT_EFFECT2, 17, 12, 0},
        {WS_JUMP, (u8*)&lbl_80416D9B},
        {WS_FIGHT_EFFECT2, 17, 13, 0},
        {WS_JUMP, (u8*)&lbl_80416D9B},
        {WS_FIGHT_EFFECT2, 17, 37, 0},
        {WS_JUMP, (u8*)&lbl_80416D9B},
    },
    { /* lbl_80416D9B */
        {WS_EFFECT_WAIT, 4},
        {WS_SPEABIEND},
    },
    { /* WAZA_ReflecEnd */
        {WS_FIGHT_EFFECT, 17, 31, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E83},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Shinpi */
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E68},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_ShinpiEnd */
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 17, 31, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E69},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Yadorigi */
        {WS_FIGHT_EFFECT, 17, 14, 0xFF0160A4},
        {WS_EFFECT_WAIT, 255},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_HP_DEC, 17},
        {WS_HP_DEC_WAIT, 17},
        {WS_STATUS_GET32, 7, 0, 0, 65, 0, (u8*)&WazaDamage},
        {WS_STATUS_SET32, 7, 0, 0, 62, 0, (u8*)&WazaDamage},
        {WS_SPEABI_CHECK, 17, 64, (u8*)&WAZA_Yadorigi + 0x52},
        {WS_DAMAGE_CHG, 0},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 3},
        {WS_JUMP, (u8*)&WAZA_Yadorigi + 0x89},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 4},
        {WS_EFFECT_WAIT, 4},
        {WS_FIGHT_EFFECT, 18, 27, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_HP_DEC, 18},
        {WS_MESSAGE_TBL, (u8*)&YadorigiMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 255},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SEQEND},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_MESSAGE_TBL, (u8*)&YadorigiMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_FIGHT_EFFECT, 18, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_HP_DEC, 18},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_SEQEND},
    },
    { /* WAZA_Gaman */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E94},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_GamanOff */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E95},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_HITCHECK, (u8*)&WAZA_NormalNohit2, 0},
        {WS_TYPE_CHECK},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_batugun},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_waza_imahitotu},
        {WS_STATUS_SET32, 7, 0, 0, 62, 0, (u8*)&fight_seq_gaman_damage},
        {WS_KORAERU_CHECK},
        {WS_SETVALUE, SEQ_USER_WORK(0x16002), 1},
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 18},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_GamanFaild */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E95},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_Umakukimaran},
    },
    { /* WAZA_Hukitobashi */
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_SIZENKAIHUKU, 18},
        {WS_POKEDELACTOR, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_APPEAR_EFFECT_INIT, 18},
        {WS_APPEAR_EFFECT, 18, 2},
        {WS_MESSAGE, 0x4EE2},
        {WS_APPEAR_EFFECT_WAIT, 18, 2},
        {WS_CLIENT_BIT_WAIT},
        {WS_POKE_RESHUFFLE_END, 18},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_HukitobashiFightEnd */
        {WS_WAZA_EFFECT},
        {WS_EFFECT_WAIT, 4},
        {WS_TELEPORT, (u8*)&WAZA_Hukitobashi + 0x8},
        {WS_SEQEND},
    },
    { /* WAZA_Shiroikiri */
        {WS_FIGHT_EFFECT, 25, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4E7D},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Ikari */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_MESSAGE, 0x4E9F},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Kanashibari */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EE6},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_KanashibariEnd */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EA1},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_EncoreEnd */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EA3},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Michidure */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4EA7},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_SEQRET},
    },
    { /* WAZA_MakibishiA */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_FIGHT_EFFECT, 17, 24, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_HP_DEC_WAIT, 17},
        {WS_GOSUB, (u8*)&lbl_8041708E + 0x7},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_KIZETSU_CHECK, 17, 1, (u8*)&WAZA_MakibishiA + 0x2C},
        {WS_SEQRET},
        {WS_GET_EXP, 17},
        {WS_JUMP, (u8*)&WAZA_Zenmetsu},
    },
    { /* WAZA_MakibishiD */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_FIGHT_EFFECT, 18, 24, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 18},
        {WS_HP_DEC_WAIT, 18},
        {WS_GOSUB, (u8*)&lbl_8041708E + 0x7},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_KIZETSU_CHECK, 18, 1, (u8*)&WAZA_MakibishiD + 0x2C},
        {WS_SEQRET},
        {WS_GET_EXP, 18},
        {WS_JUMP, (u8*)&WAZA_Zenmetsu},
    },
    { /* WAZA_MakibishiK */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_FIGHT_EFFECT, 21, 24, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 21},
        {WS_HP_DEC_WAIT, 21},
        {WS_GOSUB, (u8*)&lbl_8041708E + 0x7},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 21, 0, 0},
        {WS_KIZETSU_CHECK, 21, 1, (u8*)&lbl_8041708E},
        {WS_SEQRET},
    },
    { /* lbl_8041708E */
        {WS_GET_EXP, 21},
        {WS_JUMP, (u8*)&WAZA_Zenmetsu},
        {WS_MESSAGE, 0x4EB0},
        {WS_MESSAGE_WAIT, 96},
        {WS_SEQRET},
    },
    { /* WAZA_Horobinouta */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4EB2},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_SEQEND},
    },
    { /* WAZA_Horobinoutaing */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EB2},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Genshinochikara */
        {WS_CONDCHG_CHECK, 17, 3, 1, 12, (u8*)&WAZA_Genshinochikara + 0x2D},
        {WS_CONDCHG_CHECK, 17, 3, 2, 12, (u8*)&WAZA_Genshinochikara + 0x2D},
        {WS_CONDCHG_CHECK, 17, 3, 3, 12, (u8*)&WAZA_Genshinochikara + 0x2D},
        {WS_CONDCHG_CHECK, 17, 3, 4, 12, (u8*)&WAZA_Genshinochikara + 0x2D},
        {WS_CONDCHG_CHECK, 17, 0, 5, 12, (u8*)&lbl_80417125 + 0x50},
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 17, 62, 0},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 17},
        {WS_CONDCHG, 65, (u8*)&lbl_80417125},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_80417125 */
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 18},
        {WS_CONDCHG, 65, (u8*)&lbl_80417125 + 0x14},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 19},
        {WS_CONDCHG, 65, (u8*)&lbl_80417125 + 0x28},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 20},
        {WS_CONDCHG, 65, (u8*)&lbl_80417125 + 0x3C},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 21},
        {WS_CONDCHG, 65, (u8*)&lbl_80417125 + 0x50},
        {WS_MESSAGE_TBL, (u8*)&CondUpMsgTbl},
        {WS_WAIT, 64},
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Kousokuspin */
        {WS_KOUSOKUSPIN},
        {WS_SEQRET},
    },
    { /* WAZA_ShimeEscape */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EB8},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_YadorigiEscape */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EB9},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_MakibishiEscape */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EBA},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Miraiyochi */
        {WS_IF8, 1, (u8*)&ServerWork + 0x5, 0, (u8*)&WAZA_Miraiyochi + 0x28},
        {WS_HITCHECK, (u8*)&lbl_8041720C + 0x41, 248},
        {WS_FIGHT_EFFECT, 18, 18, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EBC},
        {WS_MESSAGE_WAIT, 96},
        {WS_JUMP, (u8*)&lbl_804171F9},
        {WS_HITCHECK, (u8*)&lbl_8041720C + 0x41, 353},
        {WS_FIGHT_EFFECT, 18, 19, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EBC},
        {WS_MESSAGE_WAIT, 96},
    },
    { /* lbl_804171F9 */
        {WS_DAMAGE_LOSS_ONLY},
        {WS_IF8, 1, (u8*)&ServerWork + 0x5, 0, (u8*)&lbl_8041720C},
        {WS_EFFECT_WAIT, 0},
        {WS_JUMP, (u8*)&lbl_8041720C},
    },
    { /* lbl_8041720C */
        {WS_HP_DEC, 18},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 18},
        {WS_CLIENT_BIT_WAIT},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 18, 0, 0},
        {WS_ZENMETSU_CHECK, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 1, 0},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 8},
        {WS_WKC_ACT, 2, 14},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_null},
        {WS_SEQEND},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_null},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_umakukimaran},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EBC},
        {WS_MESSAGE_WAIT, 96},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_STATUS_SET16, 7, 0, 0, 60, 0, (u8*)&joutai_data_null},
        {WS_SEQEND},
    },
    { /* WAZA_PPNoneAttack */
        {WS_ATTACK_MESSAGE},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F43},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Chouhatsu2 */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EE8},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Negaigoto */
        {WS_NEGAIGOTO, 1, (u8*)&WAZA_Negaigoto + 0x3A},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ECC},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_FIGHT_EFFECT, 18, 22, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 18},
        {WS_MESSAGE, 0x4E62},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ECC},
        {WS_MESSAGE_WAIT, 96},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4E63},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Newoharu */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_FIGHT_EFFECT, 17, 21, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4ECE},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ECF},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Bakadikara */
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 17, 6, 13},
        {WS_COND_CHG_BIT_CHECK, 17, 2, 9},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 145},
        {WS_CONDCHG, 193, (u8*)&lbl_80417394},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_80417394},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_80417394 */
        {WS_COND_CHG_BIT_CHECK, 17, 4, 9},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 146},
        {WS_CONDCHG, 193, (u8*)&lbl_804173B7},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_804173B7},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_WAIT, 64},
    },
    { /* lbl_804173B7 */
        {WS_MESSAGE_WAIT, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Hatakiotosu */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_MESSAGE, 0x4ED1},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Huuin */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EE9},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Onnen */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ED5},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_MagicCort */
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4ED7},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x800C00},
        {WS_SUBROUTINE_CALL, 17, 1},
        {WS_SEQRET},
    },
    { /* WAZA_Yokodori */
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_FIGHT_EFFECT, 25, 17, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_YOKODORI_CLIENT_SET},
        {WS_MESSAGE, 0x4ED9},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x800C00},
        {WS_SWITCH_A_D},
        {WS_SEQRET},
    },
    { /* WAZA_Koraeta */
        {WS_MESSAGE, 0x4EB4},
        {WS_MESSAGE_WAIT, 96},
        {WS_SEQRET},
    },
    { /* WAZA_Ichigeki */
        {WS_MESSAGE, 0x4F1B},
        {WS_MESSAGE_WAIT, 80},
        {WS_SEQRET},
    },
    { /* WAZA_OverHeat */
        {WS_SETVALUE, (u8*)&fight_seq_cond_chg_multi, 0},
        {WS_COND_CHG_BIT_CHECK, 17, 16, 11},
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 164},
        {WS_CONDCHG, 193, (u8*)&lbl_8041747B},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 2, (u8*)&lbl_8041747B},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&CondDownMsgTbl},
        {WS_MESSAGE_WAIT, 96},
    },
    { /* lbl_8041747B */
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_KiaiPunch */
        {WS_FIGHT_EFFECT, 17, 20, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EC4},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Hyper */
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Nemuru */
        {WS_STATUS_EFFECT, 17},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E87},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Mezame */
        {WS_RESET32BIT, (u8*)&ServerStatusFlag, 16},
        {WS_FIGHT_EFFECT, 17, 35, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 17},
        {WS_MESSAGE_TBL, (u8*)&SleepMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_SawaguMezame */
        {WS_FIGHT_EFFECT, 17, 35, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 17},
        {WS_MESSAGE, 0x4E8A},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Revers */
        {WS_FIGHT_EFFECT, 17, 38, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x5009},
        {WS_JUMP, (u8*)&lbl_80417511},
    },
    { /* WAZA_Dokudoku */
        {WS_STATUS_EFFECT, 17},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4E42},
    },
    { /* lbl_80417511 */
        {WS_MESSAGE_WAIT, 64},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_ZENMETSU_CHECK, 0},
        {WS_SEQEND},
    },
    { /* WAZA_Yakedo */
        {WS_STATUS_EFFECT, 17},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4E48},
        {WS_JUMP, (u8*)&lbl_80417511},
    },
    { /* WAZA_Koori */
        {WS_STATUS_EFFECT, 17},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E4C},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Melt */
        {WS_FIGHT_EFFECT, 17, 36, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 17},
        {WS_MESSAGE_TBL, (u8*)&MeltMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Melt2 */
        {WS_FIGHT_EFFECT, 18, 36, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 18},
        {WS_MESSAGE, 0x4E4D},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Mahi */
        {WS_STATUS_EFFECT, 17},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E52},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Hirumu */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E61},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Sawagu */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&SawaguMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_AbareruEnd */
        {WS_STATUS_EFFECT_DIRECT, 17, 1, 7},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E96},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Konran */
        {WS_STATUS_EFFECT2, 17, 9},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E58},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_IF8, 0, (u8*)&ServerWork + 0x5, 0, (u8*)&lbl_804175ED + 0x38},
    },
    { /* lbl_804175ED */
        {WS_SUBROUTINE_CALL, 17, 0},
        {WS_DAMAGE_LOSS_ONLY},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_FIGHT_EFFECT, 18, 25, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAZAKOUKA_SE},
        {WS_POKE_BLINK, 17},
        {WS_CLIENT_BIT_WAIT},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4F2A},
        {WS_MESSAGE_WAIT, 80},
        {WS_WAZAKOUKA_MESSAGE},
        {WS_MESSAGE_WAIT, 80},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
        {WS_SEQRET},
    },
    { /* WAZA_KonranEnd */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E59},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Nekonikoban */
        {WS_MESSAGE, 0x4E97},
        {WS_MESSAGE_WAIT, 64},
        {WS_SEQRET},
    },
    { /* WAZA_Shime */
        {WS_FIGHT_EFFECT, 17, 6, 0xFF0160A4},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4E79},
        {WS_JUMP, (u8*)&lbl_80417511},
    },
    { /* WAZA_ShimeEnd */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E7A},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQEND},
    },
    { /* WAZA_Meromero */
        {WS_STATUS_EFFECT2, 17, 10},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E5D},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_MeromeroNext */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E5E},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Akumu */
        {WS_STATUS_EFFECT2, 17, 23},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4EAC},
        {WS_JUMP, (u8*)&lbl_80417511},
    },
    { /* WAZA_Noroi */
        {WS_STATUS_EFFECT2, 17, 24},
        {WS_EFFECT_WAIT, 0},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4EAE},
        {WS_JUMP, (u8*)&lbl_80417511},
    },
    { /* WAZA_NoMahi */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 18},
        {WS_MESSAGE, 0x4E54},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_AddNemuri */
        {WS_STATUS_EFFECT, 22},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 22},
        {WS_MESSAGE_TBL, (u8*)&AddNemuriMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
    },
    { /* lbl_80417700 */
        {WS_CLIENT_BIT_WAIT},
        {WS_SEQRET},
    },
    { /* WAZA_AddNemuri2 */
        {WS_STATUS_EFFECT, 22},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 22},
        {WS_MESSAGE, 0x4E3B},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_CLIENT_BIT_WAIT},
        {WS_VANISH_OFF, 22},
        {WS_SEQEND},
    },
    { /* WAZA_AddDoku */
        {WS_STATUS_EFFECT, 22},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 22},
        {WS_MESSAGE_TBL, (u8*)&AddDokuMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_80417700},
    },
    { /* WAZA_AddYakedo */
        {WS_STATUS_EFFECT, 22},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 22},
        {WS_MESSAGE_TBL, (u8*)&AddYakedoMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_80417700},
    },
    { /* WAZA_AddKoori */
        {WS_STATUS_EFFECT, 22},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 22},
        {WS_MESSAGE_TBL, (u8*)&AddKooriMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_80417700},
    },
    { /* WAZA_AddMahi */
        {WS_STATUS_EFFECT, 22},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 22},
        {WS_MESSAGE_TBL, (u8*)&AddMahiMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_80417700},
    },
    { /* WAZA_AddSawagu */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4E8B},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_AddDokudoku */
        {WS_STATUS_EFFECT, 22},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 22},
        {WS_MESSAGE, 0x4E44},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_80417700},
    },
    { /* WAZA_AddNekonikoban */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F3D},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_AddShime */
        {WS_FIGHT_EFFECT, 22, 23, 0},
        {WS_MESSAGE_TBL, (u8*)&ShimeMsgTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_AddKonran */
        {WS_STATUS_EFFECT_DIRECT, 22, 1, 7},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E5A},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_AddHanekaeri */
        {WS_STATUS_GET16, 7, 0, 0, 55, 0, (u8*)&fight_seq_ushort_buff},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 165, (u8*)&lbl_80417800},
        {WS_IF16, 0, (u8*)&fight_seq_ushort_buff, 359, (u8*)&lbl_80417800},
        {WS_SPEABI_CHECK, 17, 69, (u8*)&lbl_80417827},
    },
    { /* lbl_80417800 */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_FIGHT_EFFECT, 17, 24, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4E7F},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
    },
    { /* lbl_80417827 */
        {WS_SEQRET},
    },
    { /* WAZA_AddDorobou */
        {WS_FIGHT_EFFECT, 17, 16, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4EA9},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Amehurashi */
        {WS_FIGHT_EFFECT, 25, 32, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4EEA},
        {WS_TOKUSEI_SET, 25},
        {WS_MESSAGE_WAIT, 64},
        {WS_CLIENT_BIT_WAIT},
        {WS_EFFECT_WAIT, 4},
        {WS_GOSUB, (u8*)&WAZA_Kasokusouti + 0x22},
        {WS_SPEABIEND},
    },
    { /* WAZA_Sunaokosi */
        {WS_FIGHT_EFFECT, 25, 34, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4EFF},
        {WS_TOKUSEI_SET, 25},
        {WS_MESSAGE_WAIT, 64},
        {WS_CLIENT_BIT_WAIT},
        {WS_EFFECT_WAIT, 4},
        {WS_GOSUB, (u8*)&WAZA_Kasokusouti + 0x22},
        {WS_SPEABIEND},
    },
    { /* WAZA_Hideri */
        {WS_FIGHT_EFFECT, 25, 33, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4F00},
        {WS_TOKUSEI_SET, 25},
        {WS_MESSAGE_WAIT, 64},
        {WS_CLIENT_BIT_WAIT},
        {WS_EFFECT_WAIT, 4},
        {WS_GOSUB, (u8*)&WAZA_Kasokusouti + 0x22},
        {WS_SPEABIEND},
    },
    { /* WAZA_Ikaku */
        {WS_GOSUB, (u8*)&lbl_80417896},
        {WS_SPEABIEND},
    },
    { /* lbl_80417896 */
        {WS_WAIT, 32},
    },
    { /* WAZA_IkakuAct */
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 145},
        {WS_IKAKU, 0},
        {WS_SEQRET},
    },
    { /* WAZA_IkakuLoop */
        {WS_CONDITION2_CHECK, 18, 20, (u8*)&lbl_804178EB},
        {WS_SPEABI_CHECK, 18, 29, (u8*)&lbl_804178EC},
        {WS_SPEABI_CHECK, 18, 52, (u8*)&lbl_804178EC},
        {WS_SPEABI_CHECK, 18, 73, (u8*)&lbl_804178EC},
        {WS_CONDCHG, 33, (u8*)&lbl_804178EB},
        {WS_IF8, 2, (u8*)&ServerWork + 0x5, 1, (u8*)&lbl_804178EB},
        {WS_COND_CHG_WORK_SET},
        {WS_FIGHT_EFFECT, 18, 1, 0xFF0160A4},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4EF7},
        {WS_TOKUSEI_SET, 17},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
    },
    { /* lbl_804178EB */
        {WS_SEQRET},
    },
    { /* lbl_804178EC */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F09},
        {WS_TOKUSEI_SET, 17},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_804178EB},
    },
    { /* WAZA_Trace */
        {WS_FIGHT_EFFECT, 25, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EFA},
        {WS_TOKUSEI_SET, 25},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SPEABIEND},
    },
    { /* WAZA_Ameukezara */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4EFE},
        {WS_TOKUSEI_SET, 17},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_SPEABIEND},
    },
    { /* WAZA_Dappi */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 17},
        {WS_MESSAGE, 0x4F04},
        {WS_TOKUSEI_SET, 17},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SPEABIEND},
    },
    { /* WAZA_Kasokusouti */
        {WS_SETVALUE, SEQ_USER_WORK(0x1601E), 19},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 17},
        {WS_FIGHT_EFFECT, 25, 1, 0xFF0160A4},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4EEB},
        {WS_TOKUSEI_SET, 25},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SPEABIEND},
        {WS_TENKIYA_CHECK},
        {WS_SEQRET},
    },
    { /* WAZA_Tenkiya */
        {WS_GOSUB, (u8*)&WAZA_Tenkiya2},
        {WS_SPEABIEND},
    },
    { /* WAZA_Tenkiya2 */
        {WS_TENKIYA},
        {WS_FIGHT_EFFECT, 25, 0, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CLIENT_BIT_WAIT},
        {WS_MESSAGE, 0x4F06},
        {WS_TOKUSEI_SET, 25},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Hiraishin */
        {WS_ATTACK_MESSAGE},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4F07},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x400},
        {WS_SEQRET},
    },
    { /* WAZA_TyosuiPPDec */
        {WS_PP_DEC},
    },
    { /* WAZA_Tyosui */
        {WS_ATTACK_MESSAGE},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_FIGHT_EFFECT, 18, 7, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 18},
        {WS_MESSAGE, 0x4EEE},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 18},
        {WS_EFFECT_WAIT, 4},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_koukanai},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_NOKaifukuPPDec */
        {WS_PP_DEC},
    },
    { /* WAZA_NOKaifuku */
        {WS_ATTACK_MESSAGE},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EEF},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_STATUS_SET16, 7, 0, 0, 59, 0, (u8*)&joutai_data_waza_koukanai},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_MoraibiPPDec */
        {WS_PP_DEC},
    },
    { /* WAZA_Moraibi */
        {WS_ATTACK_MESSAGE},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&MoraibiMsgTbl},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Ganzyou */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4EEC},
        {WS_TOKUSEI_SET, 18},
        {WS_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Shimerike */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4EED},
        {WS_TOKUSEI_SET, 18},
        {WS_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* lbl_80417A7F */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4EF6},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_ClearBody */
        {WS_FIGHT_EFFECT, 25, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4EF8},
        {WS_TOKUSEI_SET, 25},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Mizunobeeru */
        {WS_FIGHT_EFFECT, 22, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE_TBL, (u8*)&MizunobeeruMsgTbl},
        {WS_TOKUSEI_SET, 22},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Juunan */
        {WS_FIGHT_EFFECT, 22, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE_TBL, (u8*)&JuunanMsgTbl},
        {WS_TOKUSEI_SET, 22},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Meneki */
        {WS_FIGHT_EFFECT, 22, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE_TBL, (u8*)&MenekiMsgTbl},
        {WS_TOKUSEI_SET, 22},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Donkan */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4EF2},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Seisinryoku */
        {WS_FIGHT_EFFECT, 22, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4F0B},
        {WS_TOKUSEI_SET, 22},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Mypace */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4EF4},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Bouon */
        {WS_ATTACK_MESSAGE},
        {WS_PP_DEC},
        {WS_WAIT, 32},
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EFC},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Kairikibasami */
        {WS_FIGHT_EFFECT, 25, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4F01},
        {WS_TOKUSEI_SET, 25},
        {WS_MESSAGE_WAIT, 80},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 3},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Nentyaku */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4F03},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&WAZA_WazaEnd},
    },
    { /* WAZA_Nentyaku2 */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_WAIT, 32},
        {WS_MESSAGE, 0x4F03},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 80},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Hensyoku */
        {WS_FIGHT_EFFECT, 18, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4EF0},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Samehada */
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 0x100100},
        {WS_FIGHT_EFFECT, 17, 24, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4EF9},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KIZETSU_CHECK, 17, 0, 0},
        {WS_SEQRET},
    },
    { /* WAZA_Honoonokarada */
        {WS_CLIENT_BIT_WAIT},
        {WS_TSUIKA_INDIRECT_ACT},
        {WS_TOKUSEI_SET, 18},
        {WS_SEQRET},
    },
    { /* WAZA_MeromeroBody */
        {WS_STATUS_EFFECT2, 17, 10},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4F02},
        {WS_TOKUSEI_SET, 18},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_Sinkuro */
        {WS_CLIENT_BIT_WAIT},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_SpeabiNoJoutaiijou */
        {WS_FIGHT_EFFECT, 25, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_CONDITION_GAUGE, 25},
        {WS_MESSAGE, 0x4F0D},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_OrderIgnoreSleep */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F44},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_WAZAEND},
    },
    { /* WAZA_OrderIgnore */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F45},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_WAZASEQADRS, 0},
    },
    { /* WAZA_Namakeru */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE_TBL, (u8*)&NamaketeiruMsgTbl},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_WAZAEND},
    },
    { /* WAZA_Hirune */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F46},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 65},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_WAZAEND},
    },
    { /* WAZA_OwnAttack */
        {WS_FIGHT_EFFECT, 17, 23, 0},
        {WS_EFFECT_WAIT, 0},
        {WS_MESSAGE, 0x4F48},
        {WS_MESSAGE_WAIT, 64},
        {WS_EFFECT_WAIT, 4},
        {WS_JUMP, (u8*)&lbl_804175ED},
    },
    { /* WAZA_HyperOrderIgnore */
        {WS_WAZASEQADRS, 0},
    },
    { /* WAZA_HyperOwnAttack */
        {WS_JUMP, (u8*)&lbl_804175ED},
    },
    { /* WAZA_HyperPost */
        {WS_SETVALUE, (u8*)&fight_seq_wkc_work, 0},
        {WS_WKC_ACT, 2, 16},
        {WS_WAZAEND},
    },
    { /* WAZA_HyperModoru */
        {WS_POKE_RESHUFFLE, 17, (u8*)&WAZA_HyperPost},
        {WS_CLIENT_BIT_WAIT},
        {WS_POKE_RESHUFFLE_WAIT, 17, 2},
        {WS_APPEAR_EFFECT_INIT, 17},
        {WS_APPEAR_EFFECT, 17, 0},
        {WS_POKE_HPMAX_RATE, 17},
        {WS_MESSAGE_TBL, (u8*)&AppearMsgTbl},
        {WS_APPEAR_EFFECT_WAIT, 17, 0},
        {WS_MESSAGE_WAIT, 0},
        {WS_CLIENT_BIT_WAIT},
        {WS_POKE_RESHUFFLE_END, 17},
        {WS_JUMP, (u8*)&WAZA_HyperPost},
    },
    { /* WAZA_MigawariKizetsu */
        {WS_FIGHT_EFFECT, 18, 2, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4E9D},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_ItemNoMahi */
        {WS_GOSUB, (u8*)&WAZA_ItemNoMahi2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemNoMahi2 */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 25},
        {WS_MESSAGE, 0x4F8E},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 25},
        {WS_SEQRET},
    },
    { /* WAZA_ItemNoDoku */
        {WS_GOSUB, (u8*)&WAZA_ItemNoDoku2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemNoDoku2 */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 25},
        {WS_MESSAGE, 0x4F8F},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 25},
        {WS_SEQRET},
    },
    { /* WAZA_ItemNoYakedo */
        {WS_GOSUB, (u8*)&WAZA_ItemNoYakedo2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemNoYakedo2 */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 25},
        {WS_MESSAGE, 0x4F90},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 25},
        {WS_SEQRET},
    },
    { /* WAZA_ItemNoKoori */
        {WS_GOSUB, (u8*)&WAZA_ItemNoKoori2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemNoKoori2 */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 25},
        {WS_MESSAGE, 0x4F91},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 25},
        {WS_SEQRET},
    },
    { /* WAZA_ItemNoNemuri */
        {WS_GOSUB, (u8*)&WAZA_ItemNoNemuri2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemNoNemuri2 */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 25},
        {WS_MESSAGE, 0x4F92},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 25},
        {WS_SEQRET},
    },
    { /* WAZA_ItemNoKonran */
        {WS_GOSUB, (u8*)&WAZA_ItemNoKonran2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemNoKonran2 */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4F93},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 25},
        {WS_SEQRET},
    },
    { /* WAZA_ItemNoJoutaiijou */
        {WS_GOSUB, (u8*)&WAZA_ItemNoJoutaiijou2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemNoJoutaiijou2 */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_CONDITION_GAUGE, 25},
        {WS_MESSAGE_TBL, (u8*)&ItemMultiRecoverTbl},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 25},
        {WS_SEQRET},
    },
    { /* WAZA_ItemAbiKaifuku */
        {WS_GOSUB, (u8*)&WAZA_ItemAbiKaifuku2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemAbiKaifuku2 */
        {WS_FIGHT_EFFECT, 25, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4F98},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 25},
        {WS_SEQRET},
    },
    { /* WAZA_ItemHPKaifuku */
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4F96},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 17},
        {WS_SEQEND},
    },
    { /* WAZA_ItemPPKaifuku */
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4F97},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 17},
        {WS_SEQEND},
    },
    { /* WAZA_ItemHPKaifukuEveryTurn */
        {WS_GOSUB, (u8*)&WAZA_ItemHPKaifukuEveryTurn2},
        {WS_SEQEND},
    },
    { /* WAZA_ItemHPKaifukuEveryTurn2 */
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4F99},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_EFFECT_WAIT, 4},
        {WS_SEQRET},
    },
    { /* WAZA_ItemHPKaifukuKonran */
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_SET32BIT, (u8*)&ServerStatusFlag, 256},
        {WS_HP_DEC, 17},
        {WS_MESSAGE, 0x4F96},
        {WS_MESSAGE_WAIT, 96},
        {WS_HP_DEC_WAIT, 17},
        {WS_MESSAGE, 0x4EDF},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_SETVALUE, (u8*)&ServerWork + 0x3, 71},
        {WS_TSUIKA_DIRECT_ACT},
        {WS_KILLITEM, 17},
        {WS_SEQEND},
    },
    { /* WAZA_ItemCondUp */
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 4},
        {WS_CONDCHG, 65, (u8*)&WAZA_ItemCondUp + 0xF},
        {WS_SETVALUE, (u8*)&ServerWork + 0x5, 4},
        {WS_GOSUB, (u8*)&WAZA_CondUpTsuikaMsg + 0xC},
        {WS_KILLITEM, 17},
        {WS_SEQEND},
    },
    { /* WAZA_ItemCriticalUp */
        {WS_FIGHT_EFFECT, 17, 7, 0},
        {WS_EFFECT_WAIT, 255},
        {WS_MESSAGE, 0x4EE0},
        {WS_MESSAGE_WAIT, 96},
        {WS_EFFECT_WAIT, 4},
        {WS_KILLITEM, 17},
        {WS_SEQEND},
    },
    { /* WAZA_ItemKoraeta */
        {WS_MESSAGE, 0x4F9B},
        {WS_MESSAGE_WAIT, 80},
        {WS_SEQRET},
    },
    { /* WAZA_DouguAlert */
        {WS_ALERT_MESSAGE, 0x4EDE},
        {WS_ALERTEND},
    },
    { /* WAZA_BlankMsg */
        {WS_SETVALUE, (u8*)&ServerWork + 0x7, 1},
        {WS_MESSAGE_WAIT, 0},
        {WS_SEQRET},
    },
    { /* WAZA_Null */
        {WS_SEQEND},
    },
    { /* WazaEffectTbl */
        {(u8*)&lbl_80414090, (u8*)&WAZA_NormalNohit2 + 0x13, (u8*)&lbl_804141A4 + 0x32, (u8*)&lbl_804141A4 + 0x3D, (u8*)&lbl_80414254 + 0x17, (u8*)&lbl_80414254 + 0x22, (u8*)&lbl_80414254 + 0x2D, (u8*)&lbl_80414254 + 0x38, (u8*)&lbl_804142C5 + 0x90, (u8*)&lbl_804143D0 + 0xC, (u8*)&lbl_804143D0 + 0x3D, (u8*)&lbl_804143D0 + 0x48, (u8*)&lbl_80414090, (u8*)&lbl_804143D0 + 0x53, (u8*)&lbl_80414090, (u8*)&lbl_80414090, (u8*)&lbl_804143D0 + 0x5E, (u8*)&lbl_80414090, (u8*)&WAZA_CondUpTsuikaMsg + 0x25, (u8*)&WAZA_CondUpTsuikaMsg + 0x30, (u8*)&WAZA_CondUpTsuikaMsg + 0x3B, (u8*)&lbl_80414090, (u8*)&lbl_80414090, (u8*)&WAZA_CondUpTsuikaMsg + 0x46, (u8*)&WAZA_CondUpTsuikaMsg + 0x51, (u8*)&WAZA_CondDownTsuikaMsg + 0x14, (u8*)&WAZA_CondDownTsuikaMsg + 0x2A, (u8*)&WAZA_CondDownTsuikaMsg + 0x4B, (u8*)&WAZA_CondDownTsuikaMsg + 0x65, (u8*)&WAZA_CondDownTsuikaMsg + 0x8D, (u8*)&lbl_80414685 + 0x6E, (u8*)&lbl_80414685 + 0x88, (u8*)&lbl_80414685 + 0x93, (u8*)&lbl_80414685 + 0xBB, (u8*)&lbl_804147A4 + 0x51, (u8*)&lbl_804147A4 + 0x5C, (u8*)&lbl_804147A4 + 0x65, (u8*)&lbl_804147A4 + 0x70, (u8*)&lbl_804147A4 + 0xD2, (u8*)&lbl_804147A4 + 0x120, (u8*)&lbl_80414930 + 0x29, (u8*)&lbl_80414930 + 0x62, (u8*)&lbl_80414930 + 0xAF, (u8*)&lbl_80414090, (u8*)&lbl_80414930 + 0x108, (u8*)&lbl_80414930 + 0x120, (u8*)&lbl_80414930 + 0x1BD, (u8*)&lbl_80414930 + 0x1D3, (u8*)&lbl_80414930 + 0x1F3, (u8*)&lbl_80414930 + 0x1FE, (u8*)&lbl_80414B70 + 0x19, (u8*)&lbl_80414B70 + 0x24, (u8*)&lbl_80414B70 + 0x2F, (u8*)&lbl_80414B70 + 0x3A, (u8*)&lbl_80414B70 + 0x45, (u8*)&lbl_80414090, (u8*)&lbl_80414090, (u8*)&lbl_80414B70 + 0x50, (u8*)&lbl_80414B70 + 0x66, (u8*)&lbl_80414B70 + 0x71, (u8*)&lbl_80414B70 + 0x7C, (u8*)&lbl_80414090, (u8*)&lbl_80414B70 + 0x87, (u8*)&lbl_80414090, (u8*)&lbl_80414090, (u8*)&lbl_80414B70 + 0x92, (u8*)&lbl_80414B70 + 0xA8, (u8*)&lbl_80414B70 + 0x10C, (u8*)&lbl_80414B70 + 0x1C9, (u8*)&lbl_80414B70 + 0x1DA, (u8*)&lbl_80414B70 + 0x1EB, (u8*)&lbl_80414B70 + 0x1FC, (u8*)&lbl_80414B70 + 0x20D, (u8*)&lbl_80414B70 + 0x21E, (u8*)&lbl_80414090, (u8*)&lbl_80414B70 + 0x22F, (u8*)&lbl_80414B70 + 0x258, (u8*)&lbl_80414B70 + 0x263, (u8*)&lbl_80414090, (u8*)&lbl_80414B70 + 0x27B, (u8*)&lbl_80414B70 + 0x2DC, (u8*)&WAZA_Handou + 0x16, (u8*)&WAZA_Handou + 0x3F, (u8*)&WAZA_Handou + 0x6D, (u8*)&WAZA_Handou + 0x82, (u8*)&WAZA_Handou + 0xAC, (u8*)&WAZA_Handou + 0xC1, (u8*)&WAZA_Handou + 0xE2, (u8*)&WAZA_Handou + 0x11C, (u8*)&WAZA_Handou + 0x156, (u8*)&WAZA_Handou + 0x16C, (u8*)&WAZA_Handou + 0x18D, (u8*)&WAZA_Handou + 0x1D8, (u8*)&WAZA_Handou + 0x22C, (u8*)&WAZA_Handou + 0x246, (u8*)&WAZA_Handou + 0x26D, (u8*)&lbl_80414090, (u8*)&WAZA_Handou + 0x294, (u8*)&WAZA_Handou + 0x2DD, (u8*)&WAZA_Handou + 0x2F7, (u8*)&WAZA_Handou + 0x2FD, (u8*)&lbl_80414090, (u8*)&WAZA_Handou + 0x31E, (u8*)&lbl_80414090, (u8*)&WAZA_Handou + 0x392, (u8*)&lbl_804152F2 + 0x4A, (u8*)&lbl_804152F2 + 0x55, (u8*)&lbl_804152F2 + 0x8A, (u8*)&lbl_804152F2 + 0xC9, (u8*)&lbl_804152F2 + 0xD6, (u8*)&lbl_80414090, (u8*)&lbl_804154A3 + 0x4A, (u8*)&lbl_804154A3 + 0x60, (u8*)&lbl_804154A3 + 0x7A, (u8*)&lbl_804154A3 + 0x97, (u8*)&lbl_804155CE + 0x2F, (u8*)&lbl_804154A3 + 0x4A, (u8*)&lbl_804155CE + 0x3A, (u8*)&lbl_80415615 + 0xE, (u8*)&lbl_8041566B + 0x1D, (u8*)&lbl_80415692 + 0x29, (u8*)&lbl_80415692 + 0x4A, (u8*)&lbl_80415692 + 0x58, (u8*)&lbl_80415692 + 0x4A, (u8*)&lbl_80415692 + 0x64, (u8*)&lbl_80415692 + 0x6D, (u8*)&lbl_80415692 + 0x78, (u8*)&lbl_80415692 + 0x8D, (u8*)&lbl_80414090, (u8*)&lbl_80415692 + 0xC5, (u8*)&lbl_80415692 + 0xD0, (u8*)&lbl_80414090, (u8*)&lbl_80415692 + 0x11D, (u8*)&lbl_80415692 + 0x11D, (u8*)&lbl_80415692 + 0x11D, (u8*)&lbl_80415692 + 0x12A, (u8*)&lbl_80415692 + 0x130, (u8*)&lbl_804157C8 + 0x17, (u8*)&lbl_804157C8 + 0x22, (u8*)&lbl_804157C8 + 0x33, (u8*)&lbl_804157C8 + 0x44, (u8*)&lbl_80414090, (u8*)&lbl_804157C8 + 0x4F, (u8*)&lbl_804157C8 + 0x76, (u8*)&lbl_804157C8 + 0x90, (u8*)&lbl_804157C8 + 0xA6, (u8*)&lbl_804157C8 + 0xFA, (u8*)&lbl_804157C8 + 0x133, (u8*)&lbl_804157C8 + 0x1E7, (u8*)&lbl_804157C8 + 0x201, (u8*)&lbl_804157C8 + 0x234, (u8*)&lbl_804157C8 + 0x25E, (u8*)&lbl_80415A75 + 0x19, (u8*)&lbl_80415A75 + 0x2D, (u8*)&lbl_80415A75 + 0x5C, (u8*)&lbl_80415A75 + 0xD1, (u8*)&lbl_80415C14 + 0x6, (u8*)&lbl_80415C14 + 0x29, (u8*)&WAZA_Mantan + 0x19, (u8*)&lbl_80415CC6 + 0x29, (u8*)&lbl_80415D09 + 0x6, (u8*)&lbl_80415D09 + 0x1C, (u8*)&lbl_80415D09 + 0x72, (u8*)&lbl_80414090, (u8*)&lbl_80415D09 + 0x98, (u8*)&lbl_80415D09 + 0xA3, (u8*)&lbl_80415D09 + 0xC4, (u8*)&lbl_80415D09 + 0x129, (u8*)&lbl_80415D09 + 0x1C9, (u8*)&lbl_80415F43 + 0x4C, (u8*)&lbl_80415F43 + 0x7A, (u8*)&lbl_80415F43 + 0x97, (u8*)&lbl_80415FF9 + 0x1F, (u8*)&lbl_80415FF9 + 0x35, (u8*)&WAZA_ShizennochikaraHitMsg + 0x12, (u8*)&WAZA_ShizennochikaraHitMsg + 0x28, (u8*)&WAZA_ShizennochikaraHitMsg + 0x49, (u8*)&WAZA_ShizennochikaraHitMsg + 0x63, (u8*)&WAZA_ShizennochikaraHitMsg + 0x10A, (u8*)&WAZA_ShizennochikaraHitMsg + 0x12B, (u8*)&WAZA_ShizennochikaraHitMsg + 0x13C, (u8*)&WAZA_ShizennochikaraHitMsg + 0x154, (u8*)&WAZA_ShizennochikaraHitMsg + 0x16E, (u8*)&WAZA_ShizennochikaraHitMsg + 0x179, (u8*)&WAZA_ShizennochikaraHitMsg + 0x193, (u8*)&WAZA_ShizennochikaraHitMsg + 0x1AD, (u8*)&WAZA_ShizennochikaraHitMsg + 0x1B3, (u8*)&WAZA_ShizennochikaraHitMsg + 0x22B, (u8*)&lbl_804162A5 + 0x41, (u8*)&lbl_804162A5 + 0x4C, (u8*)&lbl_804162A5 + 0xF9, (u8*)&lbl_804162A5 + 0xFF, (u8*)&lbl_804162A5 + 0x123, (u8*)&lbl_804162A5 + 0x13D, (u8*)&lbl_804162A5 + 0x159, (u8*)&lbl_804162A5 + 0x173, (u8*)&lbl_804162A5 + 0x190, (u8*)&lbl_804162A5 + 0x1A0, (u8*)&lbl_804162A5 + 0x1A6, (u8*)&lbl_804162A5 + 0x1B1, (u8*)&lbl_80414254 + 0x17, (u8*)&lbl_8041656D + 0x44, (u8*)&lbl_8041656D + 0x5E, (u8*)&lbl_8041656D + 0x69, (u8*)&lbl_8041656D + 0x6F, (u8*)&lbl_8041656D + 0x7A, (u8*)&lbl_80416660 + 0x2D, (u8*)&lbl_80416660 + 0x97, (u8*)&lbl_80416660 + 0xA5, (u8*)&lbl_804141A4 + 0x32, (u8*)&lbl_8041656D + 0x44, (u8*)&lbl_80416660 + 0x10F, (u8*)&lbl_804167D9 + 0x2D, (u8*)&lbl_80416847 + 0x29, (u8*)&lbl_80416847 + 0x43, (u8*)&lbl_80416847 + 0x4E, (u8*)&lbl_80416847 + 0x59, (u8*)&lbl_80416847 + 0x69},
    },
};

#pragma pack()
#pragma force_active reset
