#include <game/gbaCommandPrivate.hpp>
#include <libc/string.h>
#pragma dont_inline on
#pragma force_active on
static u32 _swap32(unsigned long value){return (value>>24)|(((value&0xff0000)>>8)|((value<<24)|((value&0xff00)<<8)));}
static u16 _swap16(unsigned short value){return (value<<8)|(value>>8);}
static s32 _SIProbe_Result[4]={0,0,0,0};
static u32 _SIProbe_Counter[4]={0,0,0,0};
static s32 _keyState[4];
static s32 _keyResult[4];
static u8 gba_SIProbe_ErrorCnt[4];
static u16 _keyCounter[4];
static u16 _keyPressed[4];
static u8 _needSelect;
static s32 _dummySelect(FightOutPokemon*,u16,u16){_needSelect=1;return 0;}
extern "C" {
void PKJB_ExchangeEnd(s32);
s32 PKJB_ExchangeIsPrepared(s32);
s32 PKJB_ExchangeStart(s32,GbaExchangePacket*);
s32 PKJB_EntryGetStatus(s32,u32*);
void PKJB_EntryRequest(s32,u32);
void PKJB_SendWazaText(s32,GbaWazaText*);
s32 PKJB_GetKey(s32,u16*);
s32 PKJB_IdleSend(s32);
u16 pokemonBiosGetPokemonDataId(void*);
u8 pokemonBiosGetTokuseiFlag(void*);
void pokemonBiosSetTokuseiFlag(void*,bool);
void gbaPokemonFromGC(void*,GbaPokemonRecord*);
s8 exribbonGetNo(s32);
void wazaconv(u32,GbaWazaText*);
u32 SIProbe(s32);
s32 menuCB_GetToolBattleModeFlag();
u8 menuCBBios_CurrentlyWorkingToolBattle();
s32 gbaCommandSetKeyState(s32,s32);
void gba_SIProbe_ErrorCntClear(s32 channel){
    if(channel==-1){gba_SIProbe_ErrorCnt[3]=0;gba_SIProbe_ErrorCnt[2]=0;gba_SIProbe_ErrorCnt[1]=0;gba_SIProbe_ErrorCnt[0]=0;}
    else gba_SIProbe_ErrorCnt[channel]=0;
}
s32 gba_SIProbe(s32 channel){return _SIProbe_Result[channel];}
void gbaCommandChangePokemonEnd(s32 channel){PKJB_ExchangeEnd(channel-1);}
s32 gbaCommandChangePokemonIsPrepared(s32 channel){
    s32 state=PKJB_ExchangeIsPrepared(channel-1);
    if(state<0)_keyCounter[channel-1]=0;
    else if(state==1 || state==2){if(++_keyCounter[channel-1]<=10)state=-1;}
    return state;
}
s32 gbaCommandChangePokemon(s32 channel,void* pokemon,u32 state,s32 id){
    s8* ribbon;
    GbaExchangePacket packet;
    packet.status=_swap32(state);
    packet.pokemonId=_swap32((id<<16)|pokemonBiosGetPokemonDataId(pokemon));
    if(pokemonBiosGetPokemonDataId(pokemon)==0x181)pokemonBiosSetTokuseiFlag(pokemon,!pokemonBiosGetTokuseiFlag(pokemon));
    gbaPokemonFromGC(pokemon,&packet.pokemon);
    memset(packet.ribbons,0,sizeof(packet.ribbons));
    ribbon=packet.ribbons;
    s32 i;
    for(i=0;i<11;i++){*ribbon++=exribbonGetNo(i);}
    s32 r=PKJB_ExchangeStart(channel-1,&packet);
    _keyCounter[channel-1]=0;
    return r;
}
u32 gbaCommandGetGBAChangePokemon(u32 state){return state&0xffff;}
u32 gbaCommandGetWazaTarget(u32 state){return (state>>8)&0xff;}
u32 gbaCommandGetWazaDataId(u32 state){return state&0xff;}
u32 gbaCommandGetAction(u32 state){return state>>16;}
s32 gbaCommandEntryPokemon(u32 selection,u8* positions){
    positions[0]=selection&15;
    positions[1]=(selection>>4)&15;
    positions[2]=(selection>>8)&15;
    positions[3]=(selection>>12)&15;
    positions[4]=(selection>>16)&15;
    positions[5]=(selection>>20)&15;
    return 0;
}
s32 gbaCommandEntryResult(s32 channel,u32* result){
    u32 value;
    s32 index=channel-1;
    *result=0x02000000;
    s32 state=PKJB_EntryGetStatus(index,&value);
    if(state==1){u8* errors=gba_SIProbe_ErrorCnt;errors+=channel;--errors;++*errors;if(*errors!=2)state=-1;}
    else gba_SIProbe_ErrorCntClear(index);
    if(state<0){value=0x02000000;}
    else {
        if(state!=0){*result=0x03000000;gbaCommandSetKeyState(channel,1);return state;}
        *result=_swap32(value);
        if((*result>>24)==0)gbaCommandSetKeyState(channel,1);
    }
    return 0;
}
void gbaCommandEntryRequest(s32 channel,u32 first,u32 second,u32 mode){PKJB_EntryRequest(channel-1,(second<<8)|((mode<<24)|first));}
void gbaCommandSendWazaText(s32 channel,u32 message){GbaWazaText text;wazaconv(message,&text);PKJB_SendWazaText(channel-1,&text);}
u16 gbaCommandKeyPressed(s32 channel){return _keyPressed[channel-1];}
bool gbaCommandIsConnected(s32 channel){bool connected=false;if(_keyState[channel-1]!=0 && _keyResult[channel-1]==0)connected=true;return connected;}
s32 gbaCommandSetKeyState(s32 channel,s32 state){
    s32 previous=_keyState[channel-1];
    _keyState[channel-1]=state;
    _keyResult[channel-1]=0;
    _keyCounter[channel-1]=0;
    _keyPressed[channel-1]=0;
    return previous;
}
s32 gbaCommandKeyRead(s32 channel){
    u16 key;
    if(channel==2){
        u32 status;
        for(s32 i=0;i<4;++i){
            status=SIProbe(i);
            if(menuCB_GetToolBattleModeFlag()==1 && menuCBBios_CurrentlyWorkingToolBattle())status=0x40000;
            if(status==0x40000){_SIProbe_Result[i]=status;_SIProbe_Counter[i]=2;}
            else if(_SIProbe_Counter[i]==0)_SIProbe_Result[i]=status;
            else --_SIProbe_Counter[i];
        }
    }
    s32 result;
    switch(_keyState[channel-1]){
    case 1:
        result=PKJB_GetKey(channel-1,&key);
        if(result==0){_keyCounter[channel-1]=0;_keyPressed[channel-1]=key;}
        else if(result<=2 && ++_keyCounter[channel-1]<=10)result=0;
        else{_keyPressed[channel-1]=0;gbaCommandSetKeyState(channel,0);}
        break;
    case 3:
        result=PKJB_IdleSend(channel-1);
        if(result==0)_keyCounter[channel-1]=0;
        else if(result<=2 && ++_keyCounter[channel-1]<=10)result=0;
        else{_keyPressed[channel-1]=0;gbaCommandSetKeyState(channel,0);}
        _keyPressed[channel-1]=0;
        break;
    case 2:_keyPressed[channel-1]=0;result=0;break;
    default:_keyPressed[channel-1]=0;result=1;break;
    }
    _keyResult[channel-1]=result;
    return result;
}
}
#pragma force_active reset

extern "C" {
u32 fightFloorGetStatus(void*,u16,u16,u16);
void* fightTypeDataBiosGetPtr(u16);
u8 fightTypeDataBiosGetTrainerNum(void*);
u8 fightTypeDataBiosGetEntryPokemonNum(void*);
u8 fightTypeDataBiosGetFightoutPokemonNum(void*);
void* fightTargetGetPtr(s32,void*,u16);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(void*,u16);
u8 fightTrainerBiosGetControllerId(void*);
void* fightTrainerGetValidFightPokemonPtr(void*,u16);
void* fightPokemonGetPokemonPtr(void*);
u16 pokemonBiosGetFightTrainerPokemonDataId(void*);
u8 fightTrainerCheckCanIrekaeFightPokemon(void*,void*);
u8 pokemonBiosGetPokerus(void*);
u16 pokemonBiosGetHp(void*);
u16 pokemonBiosGetMaxHp(void*);
u16 gbaPokemonConditonFromGC(void*);
u16 fightPokemonGetSoubiItemDataId(void*);
u8 pokemonBiosGetMailId(void*);
u16 pokemonBiosGetPokemonWazaDataId(void*,u16);
s8 pokemonBiosGetPokemonWazaPp(void*,u16);
void GetWazaDocGBA(void*,u16);
void* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
void fightOutPokemonGetRndStatus(FightOutPokemon*,u32*,u32*);
u16 fightOutPokemonBiosGetZokuseiDataId(FightOutPokemon*,u16);
void* fightFloorBiosGetFightFloorPtr();
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(void*,FightOutPokemon*,FightOutPokemon**);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon*,u8);
FightOutPokemon* fightSeqSelectDefensePokemonPtr(FightOutPokemon*,u16,u16,s32(*)(FightOutPokemon*,u16,u16),u8,u8,s16);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon*,u16,u8,u16*);
u32 pokemonBiosGetAttest(void*);
u8 gamedataAttestBiosGetLangareaId(u32);
s32 GBAMakeFromGSchar(u8*,const u16*,s32);
const u16* pokemonBiosGetNicknamePtr(void*);
u8 pokemonGetSex(void*);
s8 pokemonBiosGetLevel(void*);
u32 pokemonBiosGetRnd(void*);
u8 menuCBRule_DEOKISISUCamouflage();
u8 pokemonGetDeoxysSel(u8);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*,u16);
extern u8 _CB[];
void* memmove(void*,const void*,u32);
void PKJB_BattleRequest(s32,GbaActionPacket*,s32);
u16 fightGetFightResultId();
u8 fightFloorIsUseFightTimerCommand(s32);
u8 fightTimerCommandIsOver();
void PKJB_ReturnTitle(s32);
s32 PKJB_BattleGetStatus(s32,u32*);
void GSthreadSwitch();
}
extern "C" s32 gbaCommandRequestAction(s32 channel,void* trainer,s32 position,s32 special) {
    GbaActionPacket packet;
    u8 controllers[4];
    u32 random0,random1;
    FightOutPokemon* trapped;
    FightOutPokemon* opponents[4];
    u16 fightType=fightFloorGetStatus(0,0,20,0);
    void* type=fightTypeDataBiosGetPtr(fightType);
    u8 trainers=fightTypeDataBiosGetTrainerNum(type);
    u8 partySize=fightTypeDataBiosGetEntryPokemonNum(type);
    u8 active=fightTypeDataBiosGetFightoutPokemonNum(type);
    u8 count=trainers*active*2;
    void* host=fightTargetGetPtr(11,trainer,fightType);
    opponents[0]=fightTrainerGetValidFightOutPokemonPtr(host,0);controllers[0]=1;
    if(trainers==2) {
        void* target=fightTargetGetPtr(7,host,fightType);opponents[1]=fightTrainerGetValidFightOutPokemonPtr(target,0);controllers[1]=fightTrainerBiosGetControllerId(target);
        target=fightTargetGetPtr(9,host,fightType);opponents[2]=fightTrainerGetValidFightOutPokemonPtr(target,0);controllers[2]=fightTrainerBiosGetControllerId(target);
        target=fightTargetGetPtr(10,host,fightType);opponents[3]=fightTrainerGetValidFightOutPokemonPtr(target,0);controllers[3]=fightTrainerBiosGetControllerId(target);
    }else if(active==2) {
        opponents[1]=fightTrainerGetValidFightOutPokemonPtr(host,1);
        void* target=fightTargetGetPtr(9,host,fightType);opponents[2]=fightTrainerGetValidFightOutPokemonPtr(target,0);opponents[3]=fightTrainerGetValidFightOutPokemonPtr(target,1);
        controllers[1]=1;controllers[2]=2;controllers[3]=2;
    }else {opponents[1]=fightTrainerGetValidFightOutPokemonPtr(fightTargetGetPtr(9,host,fightType),0);controllers[1]=1;}
    FightOutPokemon* current=fightTrainerGetValidFightOutPokemonPtr(trainer,position);
    packet.slot=active==2?position+1:0;packet.count=count;packet.special=special;
    u32 ids=0,swaps=0;
    s32 index=0;
    for(;index<partySize;index++) {
        void* fightPokemon=fightTrainerGetValidFightPokemonPtr(trainer,index);
        if(!fightPokemon)break;
        void* pokemon=fightPokemonGetPokemonPtr(fightPokemon);
        ids|=pokemonBiosGetFightTrainerPokemonDataId(pokemon)<<(index*4+8);
        swaps|=fightTrainerCheckCanIrekaeFightPokemon(trainer,fightPokemon)<<(index*4+8);
        u8 pokerus=pokemonBiosGetPokerus(pokemon);
        packet.party[index].hp=_swap16(pokemonBiosGetHp(pokemon));
        s32 condition=gbaPokemonConditonFromGC(pokemon);packet.party[index].condition=condition;
        packet.party[index].held=fightPokemonGetSoubiItemDataId(fightPokemon)!=0;
        packet.party[index].mail=pokemonBiosGetMailId(pokemon)!=255;
        packet.party[index].pokerusActive=(pokerus&15)!=0;packet.party[index].pokerusPast=(pokerus&0xf0)!=0;packet.party[index].conditionHigh=condition>>8;
        packet.party[index].item=_swap16(fightPokemonGetSoubiItemDataId(fightPokemon));
        for(s32 move=0;move<4;move++) {
            u16 id=pokemonBiosGetPokemonWazaDataId(pokemon,move);
            packet.party[index].moves[move]=_swap16(id);packet.party[index].pp[move]=pokemonBiosGetPokemonWazaPp(pokemon,move);GetWazaDocGBA(packet.party[index].descriptions[move],id);
        }
    }
    ids|=-(1<<((u8)index*4+8));packet.selection=_swap32(ids);packet.swaps=_swap32(swaps);
    u16 available=0,forced;
    void* pokemon=fightOutPokemonGetPokemonPtr(current);
    fightOutPokemonGetRndStatus(current,&random0,&random1);packet.random[0]=_swap32(random0);packet.random[1]=_swap32(random1);
    u16 species=pokemonBiosGetPokemonDataId(pokemon);packet.species=_swap16(species);
    if(species==0x181) {
        u32 form;
        u16 attribute=fightOutPokemonBiosGetZokuseiDataId(current,0);if(attribute==10)form=1;else if(attribute==11)form=2;else if(attribute==15)form=3;else form=0;
        packet.form=_swap16((u16)form);
    }else packet.form=0;
    u8 trap; s32 trapIndex;
    if(special) {trap=0;trapIndex=0;}
    else {
        trap=fightFloorCheckFightActionFightOutPokemonIrekaeSelect(fightFloorBiosGetFightFloorPtr(),current,&trapped);
        if(trap==2) {
            u16 ability=fightOutPokemonGetTokuseiDataId(trapped);
            trap=ability==23?2:ability==42?3:ability==71?4:0;
        }
        for(trapIndex=count-1;trapIndex>0;trapIndex--)if(trapped==opponents[trapIndex])break;
    }
    packet.trap=trap;packet.trappedBy=trapIndex;
    packet.forbidden=fightOutPokemonCheckFightActionWazaSelect(current,0);

    for(s32 move=0,bit=0;move<4;move++,bit+=4) {
        _needSelect=0;
        u16 id=pokemonBiosGetPokemonWazaDataId(pokemon,move);packet.moves[move]=_swap16(id);packet.pp[move]=pokemonBiosGetPokemonWazaPp(pokemon,move);
        fightSeqSelectDefensePokemonPtr(current,id,fightType,_dummySelect,1,0,-1);
        if(_needSelect)available|=8<<bit;
        u16 forcedId;
        u8 allowed=fightOutPokemonCheckCanOutOkWazaBanme(current,move,1,&forcedId);
        available|=allowed<<bit;
        if(allowed==5)forced=forcedId;
    }
    packet.available=_swap16(available);
    s32 forcedIndex=3;
    do {if(packet.moves[forcedIndex]==_swap16(forced))break;--forcedIndex;}while(forcedIndex>0);
    packet.forcedMove=forcedIndex;
    for(s32 i=0;i<count;i++) {
        memset(&packet.opponents[i],0,sizeof(packet.opponents[i]));
        if(opponents[i]==current)packet.opponents[i].nickname[0]=255;
        else {
            void* other=fightOutPokemonGetPokemonPtr(opponents[i]);
            u32 attest=pokemonBiosGetAttest(other);u32 language=gamedataAttestBiosGetLangareaId(attest);
            s32 length=GBAMakeFromGSchar(packet.opponents[i].nickname,pokemonBiosGetNicknamePtr(other),language);if(length<10)packet.opponents[i].nickname[length]=255;
            u16 id=pokemonBiosGetPokemonDataId(other);
            packet.opponents[i].sex=pokemonGetSex(other);packet.opponents[i].nidoranMale=(u8)(id==32);packet.opponents[i].nidoranFemale=(u8)(id==29);packet.opponents[i].controller=controllers[i];if(gamedataAttestBiosGetLangareaId(attest)==1)packet.opponents[i].japanese=1;else packet.opponents[i].japanese=0;
            packet.opponents[i].level=pokemonBiosGetLevel(other);packet.opponents[i].random=_swap32(pokemonBiosGetRnd(other));packet.opponents[i].species=_swap16(pokemonBiosGetPokemonDataId(other));packet.opponents[i].hp=_swap16(pokemonBiosGetHp(other));packet.opponents[i].maxHp=_swap16(pokemonBiosGetMaxHp(other));packet.opponents[i].form=0;
            if(pokemonBiosGetPokemonDataId(other)==0x19a) {
                if(menuCBRule_DEOKISISUCamouflage()) {if(*(s32*)(_CB+8)==2 || *(s32*)(_CB+28)==0)packet.opponents[i].form=_swap16(pokemonGetDeoxysSel(controllers[i]));else packet.opponents[i].form=_swap16(pokemonGetDeoxysSel(controllers[i]+1));}
                if(fightOutPokemonIsJoutaiDataId(opponents[i],16)==1)packet.opponents[i].form=0;
            }
        }
    }
    s32 opponentBytes=count*sizeof(GbaOpponentActionRecord);
    memmove((u8*)&packet+0x24+(u8)index*0x154,packet.opponents,opponentBytes);
    s32 port=channel-1;
    PKJB_BattleRequest(port,&packet,(u8)index*0x154+opponentBytes+0x24);gba_SIProbe_ErrorCntClear(port);
    for(;;) {
        if(fightGetFightResultId()==1) {PKJB_ReturnTitle(port);return 0x50000;}
        if(fightFloorIsUseFightTimerCommand(0)==1 && fightTimerCommandIsOver()==1) {PKJB_ReturnTitle(port);return 0x40000;}
        u32 response;s32 result=PKJB_BattleGetStatus(port,&response);
        if(result==1) {++gba_SIProbe_ErrorCnt[port];if(gba_SIProbe_ErrorCnt[port]!=2)result=-1;}else gba_SIProbe_ErrorCntClear(port);
        if(result>0)return result|0x50000;
        if(result==0)return _swap32(response);
        GSthreadSwitch();
    }
}
