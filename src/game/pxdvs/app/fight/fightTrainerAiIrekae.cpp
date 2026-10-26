#include <game/pxdvs/app/fight/fightTrainerAiIrekaePrivate.hpp>
extern "C" {
u8 fightTrainerAiIrekae_SelComboPartner(void *trainer,void *candidate,void *partner) {
    void *pokemon=fightPokemonGetPokemonPtr(candidate);
    void *deck=getDeckTrainerObj__11DeckTrainerFUl(fightTrainer_GetFightTrainerDataId(trainer));
    for(u8 index=0;index<4;index++){
        u16 combo=getComboID__11DeckTrainerCFUc(deck,index);
        if(!combo)continue;
        ComboId *entry=comboid+combo;
        u8 mode=entry->unk1;
        if(entry->unk0==2){
            if(!partner)continue;
            void *other=fightOutPokemonGetPokemonPtr(partner);
            u8 otherFirst=pokemon_GetComboPartner(other,index,1);
            u8 otherSecond=pokemon_GetComboPartner(other,index,0);
            u8 first=pokemon_GetComboPartner(pokemon,index,1);
            u8 second=pokemon_GetComboPartner(pokemon,index,0);
            if(mode==0&&((otherFirst==1&&second==1)||(otherSecond==1&&first==1)))return 1;
            if(mode==1&&otherFirst==1&&second==1)return 2;
        }
        if(entry->unk0==1){
            u8 first=pokemon_GetComboPartner(pokemon,index,1);
            u8 second=pokemon_GetComboPartner(pokemon,index,0);
            if(first==1||second==1){if(mode==0)return 1;if(mode==1)return 0;}
        }
    }
    return 0;
}

s32 fightTrainerAiSelectFightActionIrekae(void *arg0, void *arg1, void *arg2) {
    s16 temp_r3;

    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, arg1);
    if (fightTrainerAiGetFightPokemonIrekaeModosuValue(arg0, arg1, arg2) <= 0) {
        return 0;
    }
    temp_r3 = fightTrainerAiSelectIrekaeDasuFightPokemon(arg0, arg2, 1, arg1);
    if (temp_r3 < 0) {
        return 0;
    }
    fightOutPokemonCreateFightAction(arg1, 0, 9, 0, &fight_action_data_turn, temp_r3);
    return 1;
}

s16 fightTrainerAiSelectIrekaeDasuFightPokemon(void *trainer,void *target,u8 selectMode,void *pokemon) {
    FightOutSnapshot snapshot;
    void *party[24],*candidates[6];
    s32 values[6];
    void *enemies[8],*allies[8];
    u16 moves[8];
    s32 ai=fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    u8 revise=fightTrainerAiDB_GetLastValueRevise();
    s32 weather=fightTrainerAiGetFightFloorNowTenkouDataId(trainer,0,1);
    for(u8 i=0;i<6;i++)values[i]=0;
    fightOutPokemonBiosCopy(&snapshot,pokemon);
    if(fightOutPokemonCheckFightOut(pokemon)==1)fightOutPokemonIsFightActionAttackWazaOut(pokemon,0xE2,0);
    u16 count=fightTrainerGetIrekaeFightPokemonAry(trainer,candidates);
    u16 enemyCount=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
    u16 partyCount=fightFloorGetFightTrainerFightPokemonPtrAry(0,trainer,party,1,1);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,allies,1,1);
    if(count==0)return -1;
    if(fightTrainerAiDB_GetPokemonSelectRandomFlag(ai)==1){
        void *chosen=candidates[(u16)(HSD_Rand()%count)];
        if(chosen){fightFloorGetFightPokemonPtrToFightTrainerPtr(0,chosen);return fightPokemon_GetEntryId(chosen);}
    }
    s32 bestAffinity=-65535;
    u16 firstData=0xFFFF;
    u32 fastest=0;
    for(u8 i=0;i<count;i++){
        void *candidate=candidates[i];
        if(candidate&&fightPokemon_GetEntryId(candidate)>=0){
            u16 speed=fightTrainerAiGetFightPokemonSubayasa(trainer,candidate);
            s32 affinity=fightTrainerAiGetFightPokemonZokuseiAisyouValue(trainer,candidate,2);
            u16 data=pokemon_GetFightTrainerPokemonDataId(fightPokemonGetPokemonPtr(candidate));
            if(fastest<speed)fastest=speed;
            if(bestAffinity<affinity)bestAffinity=affinity;
            if(firstData>data)firstData=data;
        }
    }
    if(fightTrainerAiDB_GetPokemonDataOrderOutFlag(ai)==1){
        for(u8 i=0;i<count;i++){
            void *candidate=candidates[i];
            if(candidate&&fightPokemon_GetEntryId(candidate)>=0){
                fightFloorGetFightPokemonPtrToFightTrainerPtr(0,candidate);
                if(firstData>=pokemon_GetFightTrainerPokemonDataId(fightPokemonGetPokemonPtr(candidate))){fightFloorGetFightPokemonPtrToFightTrainerPtr(0,candidate);return fightPokemon_GetEntryId(candidate);}
            }
        }
    }
    for(u8 i=0;i<count;i++){
        void *candidate=candidates[i];
        if(!candidate||fightPokemon_GetEntryId(candidate)<0)continue;
        fightFloorGetFightPokemonPtrToFightTrainerPtr(0,candidate);
        fightOutPokemonCreate(pokemon,candidate,0);
        u16 moveCount=fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,pokemon,moves,0,1);
        u8 canHit=0;
        for(u8 j=0;j<enemyCount;j++){
            void *enemy=enemies[j];
            if(enemy){for(u16 k=0;k<moveCount;k++){u16 move=moves[k];if(move&&move!=0x176&&fightTrainerAiWazaDoWazaHitFunc(trainer,pokemon,move,enemy)==1){canHit=1;break;}}if(canHit==1)break;}
        }
        fightOutPokemonBiosCopy(pokemon,&snapshot);
        u32 candidateMoves=fightTrainerAiGetFightPokemonWazaDataIdAry(trainer,candidate,moves,0,1);
        u8 combo=fightTrainerAiIrekae_SelComboPartner(trainer,candidate,allies[0]);
        if(combo==1)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,27);
        if(combo==2)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,28);
        u8 key=fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer,candidate);
        if(key==1)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,29);
        if(key==2)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,30);
        if(key==3)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,31);
        for(u8 j=0;j<2;j++){
            u8 element=fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(ai,j);
            if(element!=9&&fightTrainerAiIsFightPokemonZokuseiDataId(trainer,candidate,element)==1)values[i]=fightTrainerAiReviseValueByAddsubDataId(values[i],fightTrainerAiDB_GetZokuseiReviseValue(ai,j),trainer,32);
        }
        if(fightTrainerAiIsFightPokemonNokoriHpHikui(trainer,candidate)==1)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,33);
        if(canHit==0)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,34);
        if(fastest<=(u16)fightTrainerAiGetFightPokemonSubayasa(trainer,candidate))values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,36);
        if(bestAffinity<=fightTrainerAiGetFightPokemonZokuseiAisyouValue(trainer,candidate,2))values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,35);
        for(u8 j=0;j<enemyCount;j++){
            void *enemy=enemies[j];
            if(enemy)for(u16 k=0;k<(u16)candidateMoves;k++){
                u16 move=moves[k];
                if(move){u16 element=fightTrainerAiGetWazaZokuseiDataId(trainer,move,pokemon);if(element!=9&&fightTrainerAiIsWazaTypeId(trainer,move,1)!=0&&fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(trainer,enemy,element,fightTrainerAiGetWazaIryoku(trainer,move))==0x41)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,37);}
            }
        }
        for(u8 j=0;j<enemyCount;j++){
            void *enemy=enemies[j];
            if(enemy){u16 numMoves=fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,enemy,moves,0,0);for(u16 k=0;k<numMoves;k++){
                u16 move=moves[k];
                if(move){u16 element=fightTrainerAiGetWazaZokuseiDataId(trainer,move,enemy);if(element!=9&&fightTrainerAiIsWazaTypeId(trainer,move,1)!=0&&fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(trainer,candidate,element,fightTrainerAiGetWazaIryoku(trainer,move))==0x41)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,38);}
            }}
        }
        if(fightTrainerAiDB_GetPokemonSelectWeakPointFlag(ai)==1){for(u16 element=0;element<*zokusei_data_number;element++){
            if(element!=9&&fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(trainer,candidate,element,1)==0x41){for(u8 j=0;j<partyCount;j++){
                void *member=party[j];
                if(member){
                  void *memberTrainer=fightFloorGetFightPokemonPtrToFightTrainerPtr(0,member);
                  if(memberTrainer){
                    u8 canSwitch=fightTrainerCheckCanIrekaeFightPokemon(memberTrainer,member);
                    if(canSwitch!=1&&(canSwitch==2||canSwitch==3)&&fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(trainer,member,element,1)==0x41)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,39);
                  }
                }
            }}
        }}
        u32 ability=fightTrainerAiGetFightPokemonIrekaeDasuTokuseiAddsubDataId(trainer,candidate);
        if((u16)ability)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,ability);
        if((u8)weather==2){if(fightTrainerAiIsFightPokemonTokuseiDataId(trainer,candidate,33)==1||fightTrainerAiIsFightPokemonTokuseiDataId(trainer,candidate,44)==1)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,44);}
        else if((u8)weather==1){if(fightTrainerAiIsFightPokemonTokuseiDataId(trainer,candidate,34)==1)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,45);}
        else if((u8)weather==3){u8 safe=0;if(fightTrainerAiIsFightPokemonTokuseiDataId(trainer,candidate,8)==1)safe=1;if(fightTrainerAiIsFightPokemonZokuseiDataId(trainer,candidate,8)==1||fightTrainerAiIsFightPokemonZokuseiDataId(trainer,candidate,5)==1||fightTrainerAiIsFightPokemonZokuseiDataId(trainer,candidate,4)==1)safe=1;if(safe==1)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,46);}
        else if((u8)weather==4){if(fightTrainerAiIsFightPokemonZokuseiDataId(trainer,candidate,15)==1)values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,47);}
        for(u8 j=0;j<enemyCount;j++){
            void *enemy=enemies[j];
            if(enemy&&fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer,enemy,34)==1){s32 damage=fightTrainerAiWazaDoWazaDamageFightPokemonFunc(trainer,enemy,fightOutPokemon_GetMotoWazaDataId(enemy),candidate,0);if(damage>=(s32)pokemon_GetHp(fightPokemon_GetPokemonBuffPtr(candidate)))values[i]=fightTrainerAiAddValueByAddsubDataId(values[i],trainer,49);}
        }
        if(dbgMenuFightGetFightTrainerAiLastValueReviseFlag()==1)values[i]=fightTrainerAiAddValue(values[i],(HSD_Rand()%(revise*2+1))-revise);
    }
    s32 selected=fightTrainerAiGetValueAryMaxBanme(values,count,1);
    if(selected<0)return -1;
    void *chosen=candidates[selected];
    if(!chosen)return -1;
    fightFloorGetFightPokemonPtrToFightTrainerPtr(0,chosen);
    return fightPokemon_GetEntryId(chosen);
}

s32 fightTrainerAiGetFightPokemonIrekaeModosuValue(void *trainer,void *pokemon,void *target) {
    void *enemies[8];
    u16 moves[8];
    u16 i;u16 move;u16 j;void *enemy;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    s32 value=0;
    fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0,pokemon);
    u16 speed=fightTrainerAiGetFightOutPokemonBasisSubayasa(trainer,pokemon);
    u16 moveCount=fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,pokemon,moves,0,1);
    u16 count=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
    u8 knockout=0;
    u8 canHit=0;
    for(i=0;i<count;i++){
        enemy=enemies[i];
        if(enemy){
            u16 hp=fightTrainerAiGetFightOutPokemonNowHp(trainer,enemy);
            for(j=0;j<moveCount;j++){
                move=moves[j];
                if(move&&move!=0x176){
                    u8 hit=fightTrainerAiWazaDoWazaHitFunc(trainer,pokemon,move,enemy);
                    if(hit==1)canHit=1;
                    if(fightTrainerAiIsFightOutPokemonJoutaiKie(trainer,enemy)==1)canHit=1;
                    if(fightTrainerAiIsWazaTypeId(trainer,move,1)!=0&&(s32)hp<fightTrainerAiWazaDoWazaDamageFunc(trainer,pokemon,move,enemy,0)&&hit==1)knockout=1;
                }
            }
        }
    }
    if(fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer,pokemon)!=0)value=fightTrainerAiAddValueByAddsubDataId(0,trainer,1);
    if(fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer,pokemon)==0)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,2);
    else if(fightTrainerAiGetFightOutPokemonKeyPlayerFlag(trainer,pokemon)!=0)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,3);
    if(fightTrainerAiIsFightOutPokemonAllAbiCntTakai(trainer,pokemon)==1)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,4);
    if(fightTrainerAiIsFightOutPokemonAllAbiCntHikui(trainer,pokemon)==1)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,5);
    if(canHit==0)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,6);
    if(knockout==1)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,7);
    if(fightTrainerAiIsFightOutPokemonNokoriHpHikui(trainer,pokemon)==1){for(i=0;i<count;i++)if(enemies[i]&&fightTrainerAiGetFightOutPokemonBasisSubayasa(trainer,enemies[i])>speed)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,8);}
    u32 status=fightTrainerAiGetFightOutPokemonIrekaeJoutaiBadJoutaiAddsbuDataId(trainer,pokemon);
    if((u16)status)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,status);
    for(i=0;i<count;i++){
        enemy=enemies[i];
        if(enemy&&fightTrainerAiIsFightOutPokemonJoutaiDataId(trainer,enemy,0x22)==1){
            s32 damage=fightTrainerAiWazaDoWazaDamageFunc(trainer,pokemon,fightOutPokemon_GetMotoWazaDataId(enemy),enemy,0);
            if(damage>=(s32)fightOutPokemonNowHpWaruValue(pokemon,1))value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x1A);
        }
    }
    return value;
}

u32 fightTrainerAiGetFightPokemonIrekaeDasuTokuseiAddsubDataId(void *trainer,void *pokemon) {
    s32 weather=fightTrainerAiGetFightFloorNowTenkouDataId(trainer,0,1);
    void *enemies[8];
    u16 abilities[10]={1,2,35,36,45,50,53,54,59,70};
    u16 count=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
    if(fightTrainerAiIsFightPokemonTokuseiDataId(trainer,pokemon,22)==1){
        for(u16 i=0;i<count;i++){
            u16 attack=fightTrainerAiGetFightOutPokemonBasisPhyAtk(trainer,enemies[i]);
            u16 special=fightTrainerAiGetFightOutPokemonBasisSpeAtk(trainer,enemies[i]);
            if(attack<special)continue;
            return 40;
        }
    }
    if(fightTrainerAiIsFightPokemonTokuseiDataId(trainer,pokemon,36)==1){
        for(u16 i=0;i<count;i++){
            u16 j;
            u8 found=0;
            for(j=0;j<10;j++)if(fightTrainerAiIsFightOutPokemonTokuseiDataId(trainer,enemies[i],abilities[j])==1){found=1;break;}
            if(found!=1)return 41;
        }
    }
    if((u8)weather!=0){if(fightTrainerAiIsFightPokemonTokuseiDataId(trainer,pokemon,77)==1)return 42;if(fightTrainerAiIsFightPokemonTokuseiDataId(trainer,pokemon,13)==1)return 43;}
    return 0;
}

u32 fightTrainerAiGetFightOutPokemonIrekaeJoutaiBadJoutaiAddsbuDataId(void *arg0, void *arg1) {
    s32 temp_r3;
    s8 temp_r28;
    s8 temp_r29;

    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0,arg1,9) == 1) {
        return 9U;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0xA) == 1) {
        return 0xAU;
    }
    temp_r28 = fightOutPokemonGetKaisuuJoutaiDataId(arg1, 0x1E);
    temp_r29 = fightOutPokemonGetNowKaisuuJoutaiDataId(arg1, 0x1E);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1E) == 1) && (fightTrainerAiIsFightOutPokemonNokoriHpHikui(arg0, arg1) == 0) && ((s32) (temp_r29 + 1) >= temp_r28)) {
        return 0xBU;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0xE) == 1) {
        return 0xCU;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x17) == 1) {
        return 0xDU;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x18) == 1) {
        return 0xEU;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x19) == 1) {
        return 0xFU;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1B) == 1) {
        return 0x10U;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1C) == 1) {
        return 0x11U;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1D) == 1) {
        return 0x12U;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x26) == 1) {
        return 0x13U;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x27) == 1) {
        return 0x14U;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x28) == 1) {
        return 0x15U;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x29) == 1) {
        return 0x16U;
    }
    if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x2A) == 1) {
        return 0x17U;
    }
    return fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0,arg1,0x30)==1?0x18:0;
}

}
