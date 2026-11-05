#include <dolphin/types.h>

/* GSmsg::_msgCallCtrlFunc uses the flag byte and a callback at offset 4. */
struct MsgCtx;
typedef u32 (*MsgControlCallback)(struct MsgCtx*);
typedef struct MsgControl {
    u8 flags;
    MsgControlCallback callback;
} MsgControl;

extern s32 msgctrlAlign(struct MsgCtx* c);
extern u16* msgctrlAttackMons(void);
extern s32 msgctrlBaseLineBias(struct MsgCtx* c);
extern s32 msgctrlCR(struct MsgCtx* c);
extern s32 msgctrlCheckEnd(struct MsgCtx* c);
extern s32 msgctrlCheckWait(struct MsgCtx* c);
extern u16* msgctrlClientMos(void);
extern u16* msgctrlClientnowork(void);
extern s32 msgctrlColor(struct MsgCtx* c);
extern u16* msgctrlDeffenceMons(void);
extern u16* msgctrlDigit(void);
extern u16* msgctrlDigit2(void);
extern u16* msgctrlDigitH(void);
extern u16* msgctrlDigitH2(void);
extern u32 msgctrlEnemyMons(void);
extern u32 msgctrlEnemyMons2(void);
extern u32 msgctrlEnemyTmons(void);
extern u32 msgctrlEnemyTmons2(void);
extern u32 msgctrlEvStrBuf0(void);
extern u32 msgctrlEvStrBuf1(void);
extern u32 msgctrlEvStrBuf2(void);
extern s32 msgctrlFont(struct MsgCtx* c);
extern u16* msgctrlHero(void);
extern u16* msgctrlHizuki(void);
extern s32 msgctrlIndentOff(struct MsgCtx* c);
extern u32 msgctrlItem(void);
extern u32 msgctrlItem2(void);
extern u32 msgctrlItemName(void);
extern s32 msgctrlKeyEnd(struct MsgCtx* c);
extern s32 msgctrlKeyWait(struct MsgCtx* c);
extern s32 msgctrlLineSpace(struct MsgCtx* c);
extern u16* msgctrlMenuDigit(void);
extern u16* msgctrlMenuDigit2(void);
extern u16* msgctrlMenuDigitH(void);
extern u16* msgctrlMenuDigitH2(void);
extern u16* msgctrlMenuFullDigit(void);
extern u16* msgctrlMenuHex(void);
extern u16* msgctrlMenuHex2(void);
extern u16* msgctrlMenuHexH(void);
extern u16* msgctrlMenuHexH2(void);
extern u16* msgctrlMenuMoney(void);
extern u16* msgctrlMenuMoneyH(void);
extern u32 msgctrlMenuMsg(void);
extern u32 msgctrlMenuMsg2(void);
extern u32 msgctrlMenuMsgID(void);
extern u32 msgctrlMenuMsgID2(void);
extern u32 msgctrlMenuPokemon(void);
extern u16* msgctrlMenuUDigit(void);
extern u16* msgctrlMenuUDigit2(void);
extern u16* msgctrlMenuUDigitH(void);
extern u16* msgctrlMenuUDigitH2(void);
extern u16* msgctrlMenuZDigit(void);
extern u16* msgctrlMenuZDigit2(void);
extern u16* msgctrlMenuZDigitH(void);
extern u16* msgctrlMenuZDigitH2(void);
extern u16* msgctrlMoney(void);
extern u16* msgctrlMoneyH(void);
extern u32 msgctrlMsgID(void);
extern u32 msgctrlMyMons(void);
extern u32 msgctrlMyMons2(void);
extern u32 msgctrlMyName(void);
extern u32 msgctrlNpc(void);
extern s32 msgctrlPalette(struct MsgCtx* c);
extern u32 msgctrlPasoName(void);
extern u32 msgctrlPokemon(void);
extern u32 msgctrlPokemon2(void);
extern u32 msgctrlPokemonID(void);
extern s32 msgctrlRubyEnd(struct MsgCtx* c);
extern s32 msgctrlRubyStart(struct MsgCtx* c);
extern s32 msgctrlRubyTop(struct MsgCtx* c);
extern s32 msgctrlSeOff(void);
extern s32 msgctrlSeOn(void);
extern s32 msgctrlSetPeopleTalkFlag(void);
extern s32 msgctrlShadow(struct MsgCtx* c);
extern u16* msgctrlSideAttackNameha(void);
extern u16* msgctrlSideAttackNameno(void);
extern u16* msgctrlSideAttackNamewo(void);
extern u16* msgctrlSideDefenceNameha(void);
extern u16* msgctrlSideDefenceNameno(void);
extern u16* msgctrlSideDefenceNamewo(void);
extern s32 msgctrlSndPlay(struct MsgCtx* c);
extern s32 msgctrlSndWait(struct MsgCtx* c);
extern u32 msgctrlSpeabiNamea(void);
extern u32 msgctrlSpeabiNamec(void);
extern u32 msgctrlSpeabiNamed(void);
extern u32 msgctrlSpeabiNamet(void);
extern u32 msgctrlString(void);
extern u32 msgctrlString2(void);
extern s32 msgctrlTalkSE(struct MsgCtx* c);
extern u16* msgctrlTime(void);
extern u16* msgctrlTimeH(void);
extern u32 msgctrlTrainerClientno(void);
extern u32 msgctrlTrainerEnename(void);
extern u32 msgctrlTrainerEnename2(void);
extern u32 msgctrlTrainerLose(void);
extern u32 msgctrlTrainerName(void);
extern u32 msgctrlTrainerType(void);
extern u32 msgctrlTribe(void);
extern u16* msgctrlTsuikaMons(void);
extern s32 msgctrlWait(struct MsgCtx* c);
extern u32 msgctrlWaza(void);
extern u32 msgctrlWazaName(void);

MsgControl msgctrlcode[] = {
    { 0x08, (MsgControlCallback)msgctrlCR },
    { 0x08, (MsgControlCallback)msgctrlCR },
    { 0x30, (MsgControlCallback)msgctrlKeyEnd },
    { 0x38, (MsgControlCallback)msgctrlKeyWait },
    { 0x18, (MsgControlCallback)msgctrlRubyStart },
    { 0x18, (MsgControlCallback)msgctrlRubyTop },
    { 0x18, (MsgControlCallback)msgctrlRubyEnd },
    { 0x18, (MsgControlCallback)msgctrlFont },
    { 0x18, (MsgControlCallback)msgctrlColor },
    { 0x38, (MsgControlCallback)msgctrlWait },
    { 0x00, NULL },
    { 0x00, NULL },
    { 0x00, NULL },
    { 0x58, (MsgControlCallback)msgctrlEvStrBuf0 },
    { 0x58, (MsgControlCallback)msgctrlEvStrBuf1 },
    { 0x58, (MsgControlCallback)msgctrlAttackMons },
    { 0x58, (MsgControlCallback)msgctrlDeffenceMons },
    { 0x58, (MsgControlCallback)msgctrlClientMos },
    { 0x58, (MsgControlCallback)msgctrlTsuikaMons },
    { 0x58, (MsgControlCallback)msgctrlMyName },
    { 0x58, (MsgControlCallback)msgctrlMyMons },
    { 0x58, (MsgControlCallback)msgctrlMyMons2 },
    { 0x58, (MsgControlCallback)msgctrlEnemyMons },
    { 0x58, (MsgControlCallback)msgctrlEnemyMons2 },
    { 0x58, (MsgControlCallback)msgctrlEnemyTmons },
    { 0x58, (MsgControlCallback)msgctrlEnemyTmons2 },
    { 0x58, (MsgControlCallback)msgctrlSpeabiNamea },
    { 0x58, (MsgControlCallback)msgctrlSpeabiNamed },
    { 0x58, (MsgControlCallback)msgctrlSpeabiNamec },
    { 0x58, (MsgControlCallback)msgctrlSpeabiNamet },
    { 0x58, (MsgControlCallback)msgctrlClientnowork },
    { 0x58, (MsgControlCallback)msgctrlSideAttackNameha },
    { 0x58, (MsgControlCallback)msgctrlSideAttackNamewo },
    { 0x58, (MsgControlCallback)msgctrlSideAttackNameno },
    { 0x58, (MsgControlCallback)msgctrlTrainerType },
    { 0x58, (MsgControlCallback)msgctrlTrainerName },
    { 0x58, (MsgControlCallback)msgctrlTrainerLose },
    { 0x58, (MsgControlCallback)msgctrlTrainerEnename },
    { 0x58, (MsgControlCallback)msgctrlTrainerEnename2 },
    { 0x58, (MsgControlCallback)msgctrlTrainerClientno },
    { 0x58, (MsgControlCallback)msgctrlWazaName },
    { 0x58, (MsgControlCallback)msgctrlItemName },
    { 0x58, (MsgControlCallback)msgctrlPasoName },
    { 0x58, (MsgControlCallback)msgctrlHero },
    { 0x58, (MsgControlCallback)msgctrlHizuki },
    { 0x98, (MsgControlCallback)msgctrlItem },
    { 0x98, (MsgControlCallback)msgctrlItem2 },
    { 0x58, (MsgControlCallback)msgctrlDigit },
    { 0x58, (MsgControlCallback)msgctrlDigit2 },
    { 0x98, (MsgControlCallback)msgctrlMsgID },
    { 0x58, (MsgControlCallback)msgctrlPokemon },
    { 0x58, (MsgControlCallback)msgctrlPokemon2 },
    { 0x58, (MsgControlCallback)msgctrlMenuDigit },
    { 0x58, (MsgControlCallback)msgctrlMenuDigit2 },
    { 0x58, (MsgControlCallback)msgctrlMenuPokemon },
    { 0x58, (MsgControlCallback)msgctrlMenuMsg },
    { 0x18, (MsgControlCallback)msgctrlPalette },
    { 0x98, (MsgControlCallback)msgctrlWaza },
    { 0x98, NULL },
    { 0x98, NULL },
    { 0x58, NULL },
    { 0x10, (MsgControlCallback)msgctrlSeOff },
    { 0x10, (MsgControlCallback)msgctrlSeOn },
    { 0x18, NULL },
    { 0x18, NULL },
    { 0x58, (MsgControlCallback)msgctrlEvStrBuf2 },
    { 0x58, (MsgControlCallback)msgctrlSideDefenceNameha },
    { 0x58, (MsgControlCallback)msgctrlSideDefenceNamewo },
    { 0x58, (MsgControlCallback)msgctrlSideDefenceNameno },
    { 0x58, (MsgControlCallback)msgctrlMenuUDigit },
    { 0x58, (MsgControlCallback)msgctrlMenuUDigit2 },
    { 0x58, (MsgControlCallback)msgctrlMenuHex },
    { 0x58, (MsgControlCallback)msgctrlMenuHex2 },
    { 0x58, (MsgControlCallback)msgctrlMenuZDigit },
    { 0x58, (MsgControlCallback)msgctrlMenuZDigit2 },
    { 0x58, (MsgControlCallback)msgctrlMoney },
    { 0x58, (MsgControlCallback)msgctrlTime },
    { 0x58, (MsgControlCallback)msgctrlString },
    { 0x98, (MsgControlCallback)msgctrlPokemonID },
    { 0x58, (MsgControlCallback)msgctrlMenuFullDigit },
    { 0x58, (MsgControlCallback)msgctrlMenuMoney },
    { 0x58, (MsgControlCallback)msgctrlMenuMsg2 },
    { 0x08, (MsgControlCallback)msgctrlShadow },
    { 0x08, (MsgControlCallback)msgctrlAlign },
    { 0x10, (MsgControlCallback)msgctrlTalkSE },
    { 0x98, (MsgControlCallback)msgctrlMenuMsgID },
    { 0x98, (MsgControlCallback)msgctrlMenuMsgID2 },
    { 0x58, (MsgControlCallback)msgctrlString2 },
    { 0x98, (MsgControlCallback)msgctrlTribe },
    { 0x98, (MsgControlCallback)msgctrlNpc },
    { 0x10, (MsgControlCallback)msgctrlIndentOff },
    { 0x18, (MsgControlCallback)msgctrlLineSpace },
    { 0x18, (MsgControlCallback)msgctrlBaseLineBias },
    { 0x10, (MsgControlCallback)msgctrlSndPlay },
    { 0x30, (MsgControlCallback)msgctrlSndWait },
    { 0x58, (MsgControlCallback)msgctrlMenuDigitH },
    { 0x58, (MsgControlCallback)msgctrlMenuDigitH2 },
    { 0x58, (MsgControlCallback)msgctrlMenuUDigitH },
    { 0x58, (MsgControlCallback)msgctrlMenuUDigitH2 },
    { 0x58, (MsgControlCallback)msgctrlMoneyH },
    { 0x58, (MsgControlCallback)msgctrlTimeH },
    { 0x58, (MsgControlCallback)msgctrlMenuHexH },
    { 0x58, (MsgControlCallback)msgctrlMenuHexH2 },
    { 0x58, (MsgControlCallback)msgctrlMenuZDigitH },
    { 0x58, (MsgControlCallback)msgctrlMenuZDigitH2 },
    { 0x58, (MsgControlCallback)msgctrlMenuMoneyH },
    { 0x10, (MsgControlCallback)msgctrlSetPeopleTalkFlag },
    { 0x58, (MsgControlCallback)msgctrlDigitH },
    { 0x58, (MsgControlCallback)msgctrlDigitH2 },
    { 0x30, (MsgControlCallback)msgctrlCheckEnd },
    { 0x38, (MsgControlCallback)msgctrlCheckWait },
};
