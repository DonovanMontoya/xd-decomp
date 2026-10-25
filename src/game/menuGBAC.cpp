#include <dolphin/types.h>
struct Hero;
enum _MENU_GBAC_TYPE {GBAType0,GBAType1,GBAType2,GBAType3};
enum _GBA_PHASE {GBAPhase0};enum _GBA_WAIT_FLAG {GBAWait0};
struct _GBA_Connect_WORK {s32 phase[4];u8 pad10[0x11];s8 channel;u8 pad22[2];u32 flags,result;s32 type;u8 kind[4];u8 pad34[0x14];u8 enabled[4];};
static u16 GBA_ROM_VERSION_FLAG[4] = {0, 0, 0, 0};
static u8 _menu_ports[4]={1,2,4,8};
static s8 chans[4]={1,2,3,0};
static u16 gba_player_number[4]={1,2,3,0};
_GBA_Connect_WORK gbaConectGBA_Connect_WORK;
static s8 _mes_flag_type;
extern u8 _CB[];
extern "C" {void AGB_FileBuffAlloc();void AGB_FileBuffFree();void AGB_Terminate(s32);s32 AGB_IsComplete(s32);s32 AGB_GetStatus(s32);u32 gba_SIProbe(s32);f32 GSgfxVideoGetLastRenderTime();u8 GSgfxVideoGetVsyncRate();u8 GSinputIsConnected(s32);void GSsndPlayNow(u32);void GSthreadSwitch();u8 gamedataAttestBiosGetLangareaId();void *gamedataBiosGetGamedataAtttestPtr();u8 gbaCommandIsConnected(s32);void gbaCommandSetKeyState(s32,s32);s8 menuCB_MessageDispCheck();void menuCB_MessageDispOff();void menuCB_MessageDispOn(u32,s32);void menuCB_SE_Play(s32);void menuCloseCustom(s32,s32,s32);s32 menuGetEnablePort();u8 menuIsCheck(s32);s32 menuOpen(s32,s32);u8 menuSetEnablePort(u8);void msgctrlSetValue(s32,s32);void winMsgClose(s32);void *savedataBiosGetGamedataPtr();void *savedataBiosGetNowSavedataPtr();u16 *windowGetKeyInfo();}
static u8 _mainFlow(_MENU_GBAC_TYPE,unsigned long,Hero**);
static u8 _checkDisconnect(_GBA_Connect_WORK *w){s32 i;u8 result=0;for(i=0;i<=3;i++){s32 phase=w->phase[i];if((phase==5 || phase==4) && !gbaCommandIsConnected(i+1)){menuSetEnablePort(menuGetEnablePort()&~_menu_ports[i]);w->phase[i]=7;w->result=8;}if(w->phase[i]==7)result=1;}return result;}
static void _menuWait(f32 seconds){f32 timer=0;while(timer<seconds){GSthreadSwitch();timer+=GSgfxVideoGetLastRenderTime()/GSgfxVideoGetVsyncRate();}}
static void _message_type2(unsigned long message,long channel){msgctrlSetValue(0x2F,channel+1);menuCB_MessageDispOn(message,1);}
static void _message(unsigned long message,long channel){msgctrlSetValue(0x2F,channel+1);menuCB_MessageDispOn(message,0);}
static u8 _showDisconnected(_GBA_Connect_WORK *w){s32 frame=0;_mes_flag_type=0;do{if(_checkDisconnect(w))break;GSthreadSwitch();frame++;}while(frame<15);GSsndPlayNow(0x13);s32 port=0;for(;port<4;port++)if(w->phase[port]==7)break;if(port>3 && !(w->result&8))return 0;menuSetEnablePort(menuGetEnablePort()|1);u32 message;if(port==0)message=0x4438;else if(w->type==3){if(GSinputIsConnected(1))message=0x442B;else message=0x442D;}else message=0x442B;_mes_flag_type=1;msgctrlSetValue(0x2F,port+1);menuCB_MessageDispOn(message,1);if(message==0x4438 || message==0x442D){do{GSthreadSwitch();}while(!GSinputIsConnected(1));}w->result=8;return 1;}
static s32 _waitComplete(_GBA_Connect_WORK *w){w->result=0;while(!AGB_IsComplete(w->channel)){if(menuIsCheck(0x2A)){GSthreadSwitch();continue;}if(windowGetKeyInfo()[2]&0x20){w->result=2;AGB_Terminate(w->channel);return 4;}if(w->result==8)return 4;GSthreadSwitch();}w->result=0;return AGB_GetStatus(w->channel);}
static u8 _waitAction(_GBA_Connect_WORK *w,_GBA_WAIT_FLAG flags){u8 disconnected=1;w->result=0;if(w->channel>=0 && gba_SIProbe(w->channel)==0x40000)disconnected=0;for(;;){if(menuIsCheck(0x2A)){GSthreadSwitch();continue;}if((flags&2) && (windowGetKeyInfo()[2]&0x20)){w->result=2;return 0;}if(w->result==8)return 0;if(w->phase[0]==7)return 0;if(w->phase[1]==7)return 0;if(w->phase[2]==7)return 0;if(w->phase[3]==7)return 0;if(flags&1){s8 message=menuCB_MessageDispCheck();if(message==0){w->result=1;return 1;}if((windowGetKeyInfo()[2]&0x10) && message==-1){w->result=1;return 1;}}if(flags&4){u32 probe=gba_SIProbe(w->channel);if(probe!=0x80){if(disconnected){if(probe==0x40000){w->result=4;return 1;}}else if(probe!=0x40000)disconnected=1;}}GSthreadSwitch();}}
static u8 _poweroff(_GBA_Connect_WORK *w,_GBA_PHASE phase){menuSetEnablePort(menuGetEnablePort()|1);if(!_showDisconnected(w))w->phase[w->channel]=phase;if(_mes_flag_type==1){AGB_Terminate(w->channel);return 0;}u32 message;if(w->type==3){if(GSinputIsConnected(1))message=0x442C;else message=0x442D;}else message=0x442C;menuCB_MessageDispOn(message,1);if(message==0x442D){do{GSthreadSwitch();}while(!GSinputIsConnected(1));}AGB_Terminate(w->channel);return 0;}
static u8 _error(_GBA_Connect_WORK *w,unsigned long message,_GBA_PHASE phase){if(_showDisconnected(w))return (w->flags&8)!=0;w->phase[w->channel]=phase;_message(message,w->channel);if(!(w->flags&8))_waitAction(w,(_GBA_WAIT_FLAG)1);else if(_waitAction(w,(_GBA_WAIT_FLAG)7))return 1;AGB_Terminate(w->channel);return 0;}
extern "C" {
u16 menuGBACGetRomVer(u16 port){if(port>3)return 0;return GBA_ROM_VERSION_FLAG[port];}
void menuGBACSetRomVer(u16 version,u16 port){switch(port){case 0:case 1:case 2:case 3:GBA_ROM_VERSION_FLAG[port]=version;break;default:GBA_ROM_VERSION_FLAG[3]=0;GBA_ROM_VERSION_FLAG[2]=0;GBA_ROM_VERSION_FLAG[1]=0;GBA_ROM_VERSION_FLAG[0]=0;break;}if(port==0xFFFF){gbaCommandSetKeyState(1,0);gbaCommandSetKeyState(2,0);gbaCommandSetKeyState(3,0);gbaCommandSetKeyState(4,0);}}
s32 openMenuGBA(_MENU_GBAC_TYPE type,u32 flags,Hero **heroes){u8 oldPort=menuSetEnablePort(1);AGB_FileBuffAlloc();u8 result=_mainFlow(type,flags,heroes);winMsgClose(0);if(menuIsCheck(0xB0)){menuCB_MessageDispOff();menuCB_SE_Play(0x15);menuCloseCustom(0xB0,0,1);}menuSetEnablePort(oldPort);for(s32 i=0;i<3;i++)AGB_Terminate(i);AGB_FileBuffFree();if(result)return 0;return -1;}
u8 fn_8004FB00(){u8 result=255;if(savedataBiosGetNowSavedataPtr() && savedataBiosGetGamedataPtr() && gamedataBiosGetGamedataAtttestPtr()){result=gamedataAttestBiosGetLangareaId();if(result==8)result=2;}return result;}
}
extern "C" s32 pokecoloGetCountryCode();
static u8 _check_langarea(u8 language){s32 country=pokecoloGetCountryCode();switch(country){case 0:{u8 expected;switch(language){case 1:expected=1;break;case 2:expected=2;break;case 3:expected=4;break;case 4:expected=5;break;case 5:expected=3;break;case 7:expected=6;break;default:return 0;}if(savedataBiosGetNowSavedataPtr() && savedataBiosGetGamedataPtr() && gamedataBiosGetGamedataAtttestPtr()){u8 id=gamedataAttestBiosGetLangareaId();if(id==expected)return 1;}break;}case 1:case 2:{u8 expected;switch(language){case 1:expected=1;break;case 2:expected=2;break;case 3:expected=4;break;case 4:expected=5;break;case 5:expected=3;break;case 7:expected=6;break;default:return 0;}if(expected==fn_8004FB00())return 1;break;}default:break;}return 0;}
static const s32 _initial_phase[4][4]={{8,1,0,0},{8,1,1,0},{8,1,1,1},{1,1,1,1}};
static _GBA_Connect_WORK *_open_menu(_MENU_GBAC_TYPE type,unsigned long flags,long index){_GBA_Connect_WORK *w=&gbaConectGBA_Connect_WORK;w->flags=flags;w->type=type;w->channel=chans[index];switch(type){case GBAType0:w->kind[0]=1;w->kind[1]=2;w->kind[2]=0;w->kind[3]=0;break;case GBAType1:w->kind[0]=4;w->kind[1]=2;w->kind[2]=2;w->kind[3]=0;break;case GBAType2:w->kind[0]=1;w->kind[1]=2;w->kind[2]=2;w->kind[3]=2;break;case GBAType3:w->kind[0]=4;w->kind[1]=2;w->kind[2]=2;w->kind[3]=2;break;}for(s32 i=0;i<4;i++){s8 channel=chans[i];w->phase[channel]=_initial_phase[type][channel];if(i<index && w->phase[channel]==1)w->phase[channel]=5;w->enabled[i]=1;}menuCB_SE_Play(0x14);menuOpen(0xB0,0);menuCB_MessageDispOn(1,0);*(s32*)(_CB+0xB16C)=-1;*(s32*)(_CB+0xB168)=2;return w;}


#pragma dollar_identifiers on
extern "C" {
void AGB_Terminate_init();
s32 AGB_Prepare(char*);
void AGB_Upload(s32, s32);
void AGB_GetPokemon(s32, Hero*, u32*);
Hero* savedataGetStatus(s32, s32);
u8 menuCBRule_CheckHero(Hero*);
void menuCBRule_ErrorFlagSet(Hero*,u16);
void menuCB_Pokemon_ErrorDisp(Hero*,u16);
void heroBiosCopy(Hero*, Hero*);
void heroInit(Hero*);
char *lbl_8032EBD8[0xC] = {
    "maxbtl.bin",
    "maxcng.bin",
    "maxbtl_english.bin",
    "maxcng_english.bin",
    "maxbtl_france.bin",
    "maxcng_france.bin",
    "maxbtl_germany.bin",
    "maxcng_germany.bin",
    "maxbtl_italy.bin",
    "maxcng_italy.bin",
    "maxbtl_spain.bin",
    "maxcng_spain.bin",
};
static char *gba_bin_name$2220[2] = { "maxbtl.bin", "maxcng.bin" };
}
static inline void gbacSetHostKind(_GBA_Connect_WORK* work, u8 kind) {
    work->kind[0] = kind;
    if (kind != 0) { work->kind[0] = 3; work->enabled[0] = 1; }
}
static u8 _mainFlow(_MENU_GBAC_TYPE arg0, unsigned long arg1, Hero **arg2) {
    u8 *sp988;
    u32 sp10[0x978/4];
    u32 spC;
    Hero **sp8;
    Hero *temp_r0;
    Hero *temp_r3_2;
    Hero *var_r15;
    s32 temp_r0_2;
    s32 temp_r20;
    s32 temp_r3;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 var_ctr;
    s32 var_r14;
    s32 var_r19;
    s32 var_r29;
    u16 *var_r27;
    u32 temp_r22;
    u32 temp_r23;
    u8 *var_r3;
    u8 temp_r16;
    u8 var_r18;
    u8 var_r4;
    _GBA_Connect_WORK *var_r17;

    sp8 = arg2;
    var_r14 = 0;
    var_r18 = 0;
    AGB_Terminate_init();
    temp_r22 = arg1 & 1;
    if (temp_r22 == 1) {
        var_r14 = 1;
    }
    temp_r23 = arg1 & 2;
    if (temp_r23 == 2) {
        var_r14 = 0;
    }
    temp_r3 = pokecoloGetCountryCode();
    switch (temp_r3) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        while (AGB_Prepare(gba_bin_name$2220[var_r14]) == 0) {
            GSthreadSwitch();
        }
        break;
    case 1:                                         /* switch 1 */
        while (AGB_Prepare(lbl_8032EBD8[var_r14+2]) == 0) {
            GSthreadSwitch();
        }
        break;
    }
    var_r17 = _open_menu(arg0, arg1, 0);
    if (((u32) (arg1 & 0x10) != 0) && ((arg0 == 0) || (arg0 == 2))) {
        temp_r3_2 = savedataGetStatus(0, 2);
        var_r17->channel = 0;
        var_r17->phase[0] = 8;
        if (temp_r23 != 0) {
            _message(0x4437, 0);
            _menuWait(1.0f);
            if (menuCBRule_CheckHero(temp_r3_2) == 0) {
                menuCBRule_ErrorFlagSet(temp_r3_2, 0U);
                menuCB_MessageDispOff();
                menuCB_SE_Play(0x15);
                menuCloseCustom(0xB0, 0, 1);
                menuCB_Pokemon_ErrorDisp(temp_r3_2, 0U);
                return 0;
            }
        }
        if ((sp8 != NULL) && (*sp8 != NULL)) {
            heroBiosCopy(*sp8, temp_r3_2);
        }
        var_r17->phase[0] = 0xA;
        goto block_25;
    }
block_25:
    menuGBACSetRomVer(0, 0xFFFFU);
    sp988 = (u8*)chans;
    var_r19 = 0;
    var_r27 = gba_player_number;
loop_26:
    temp_r16 = *sp988;
    *(u8*)&var_r17->channel = temp_r16;
    if ((sp8 != NULL) && (temp_r0 = sp8[(s8) temp_r16], ((temp_r0 == NULL) == 0))) {
        var_r15 = temp_r0;
    } else {
        var_r15 = (Hero*)sp10;
    }
    if ((s8) temp_r16 == 0) {
        gbacSetHostKind(var_r17, 4);
    }
    temp_r20 = (s8) temp_r16 * 4;
loop_34:
    menuSetEnablePort((u8) (menuGetEnablePort() & ~_menu_ports[(s8)temp_r16]));
    if ((u32) var_r17->result != 4U) {
        var_r17->phase[(s8)temp_r16] = 2;
        _message(0x441E, (s8) temp_r16);
        if (_waitAction(var_r17, (_GBA_WAIT_FLAG)6) == 0) {
            return _poweroff(var_r17, (_GBA_PHASE)6);
        }
    }
    _message(0x441F, (s8) temp_r16);
    var_r17->phase[(s8)temp_r16] = 3;
    (*(s32*)(_CB+0xB16C)) = (s32) (s8) temp_r16;
    (*(s32*)(_CB+0xB168)) = 2;
    if (var_r18 == 0) {
        if (_waitComplete(var_r17) == 4) {
            return _poweroff(var_r17, (_GBA_PHASE)6);
        }
        var_r18 = 1;
        goto block_41;
    }
block_41:
    AGB_Upload((s8) temp_r16, 0);
    temp_r3_3 = _waitComplete(var_r17);
    switch (temp_r3_3) {                            /* switch 2; irregular */
    case 4:                                         /* switch 2 */
        return _poweroff(var_r17, (_GBA_PHASE)6);
    default:                                        /* switch 2 */
    case 2:                                         /* switch 2 */
        if (_error(var_r17, 0x4421, (_GBA_PHASE)6) == 0) {
            return 0;
        }
        goto loop_34;
    case 0:                                         /* switch 2 */
        var_r29 = 0;
        var_r17->phase[(s8)temp_r16] = 4;
loop_51:
        if (gbaCommandIsConnected((s8) temp_r16 + 1) != 0) {
            menuSetEnablePort((u8) (_menu_ports[(s8)temp_r16] | menuGetEnablePort()));
        } else {
            GSthreadSwitch();
            var_r29 += 1;
            if (var_r29 < 0x12C) {
                goto loop_51;
            }
        }
        if ((u32) (arg1 & 0x40) == 0) {
            _message(0x4435, (s8) temp_r16);
            _menuWait(1.0f);
        }
        heroInit(var_r15);
        spC = 0;
        AGB_GetPokemon((s8) temp_r16, var_r15, &spC);
        temp_r3_4 = _waitComplete(var_r17);
        if (temp_r3_4 != 4) {
            menuGBACSetRomVer((spC >> 0xAU) & 0xF, *var_r27);
            if ((u32) ((spC >> 8U) & 3) != 0) {
                if (_error(var_r17, 0x4422, (_GBA_PHASE)6) == 0) {
                    return 0;
                }
                goto loop_34;
            }
            if (_check_langarea((spC >> 4U) & 0xF) == 0) {
                if (_error(var_r17, 0x4423, (_GBA_PHASE)6) == 0) {
                    return 0;
                }
                goto loop_34;
            }
            if (temp_r3_4 != 0) {
                goto block_68;
            }
            if ((u32) (spC & 2) == 0) {
block_68:
                if (_error(var_r17, 0x4422, (_GBA_PHASE)6) == 0) {
                    return 0;
                }
                goto loop_34;
            }
            if (temp_r22 != 0) {
                temp_r0_2 = (spC >> 0xAU) & 0xF;
                var_r4 = 1;
                switch (temp_r0_2) {
                case 1: case 2:
                    if (!(spC & 0x4000)) var_r4 = 0;
                    if (!var_r4) {
                        if (!_error(var_r17, 0x4445, (_GBA_PHASE)6)) return 0;
                        goto loop_34;
                    }
                    break;
                case 3: case 4:
                    if (!(spC & 8)) var_r4 = 0;
                    if (!var_r4) {
                        if (!_error(var_r17, 0x4446, (_GBA_PHASE)6)) return 0;
                        goto loop_34;
                    }
                    break;
                case 5:
                    if (!(spC & 0x4000)) var_r4 = 0;
                    if (!var_r4) {
                        if (!_error(var_r17, 0x4447, (_GBA_PHASE)6)) return 0;
                        goto loop_34;
                    }
                    break;
                default:
                    if (!_error(var_r17, 0x4421, (_GBA_PHASE)6)) return 0;
                    goto loop_34;
                }

            }
block_93:
            if (temp_r23 != 0) {
                if ((u32) (spC & 1) == 0) {
                    if (_error(var_r17, 0x4424, (_GBA_PHASE)6) == 0) {
                        return 0;
                    }
                    goto loop_34;
                }
                if (menuCBRule_CheckHero(var_r15) == 0) {
                    menuCBRule_ErrorFlagSet(var_r15, *var_r27);
                    menuCB_MessageDispOff();
                    menuCB_SE_Play(0x15);
                    menuCloseCustom(0xB0, 0, 1);
                    menuCB_Pokemon_ErrorDisp(var_r15, *var_r27);
                    if ((u32) (arg1 & 8) == 0) {
                        return 0;
                    }
                    (*(s32*)((u8*)var_r17 + 0x10)) = (s32) var_r17->phase[0];
                    (*(s32*)((u8*)var_r17 + 0x14)) = (s32) var_r17->phase[1];
                    (*(s32*)((u8*)var_r17 + 0x18)) = (s32) var_r17->phase[2];
                    (*(s32*)((u8*)var_r17 + 0x1C)) = (s32) var_r17->phase[3];
                    var_r17 = _open_menu(arg0, arg1, var_r19);
                    if ((s8) temp_r16 == 0) {
                        gbacSetHostKind(var_r17, 4);
                    }
                    var_r17->phase[0] = (s32) (*(s32*)((u8*)var_r17 + 0x10));
                    var_r17->phase[1] = (s32) (*(s32*)((u8*)var_r17 + 0x14));
                    var_r17->phase[2] = (s32) (*(s32*)((u8*)var_r17 + 0x18));
                    temp_r3_5 = (*(s32*)((u8*)var_r17 + 0x1C));
                    var_r17->phase[3] = temp_r3_5;
                    var_r17->phase[(s8)temp_r16] = 6;
                    GSthreadSwitch();
                    for (s32 i = 0; i < var_r19; ++i) {
                        if (var_r17->phase[chans[i]] == 7) {
                            return _poweroff(var_r17, (_GBA_PHASE)6);
                        }
                    }
block_107:
                    _message_type2(0x4425, (s8) temp_r16);
                    goto loop_34;
                }
                goto block_108;
            }
block_108:
            AGB_Terminate((s8) temp_r16);
            GSsndPlayNow(0x1B);
            var_r17->phase[(s8)temp_r16] = 5;
            menuSetEnablePort((u8) (_menu_ports[(s8)temp_r16] | menuGetEnablePort()));
            _message(0x4420, (s8) temp_r16);
            switch (arg0) {                         /* switch 3; irregular */
            case 0:                                 /* switch 3 */
                if (_waitAction(var_r17, (_GBA_WAIT_FLAG)3) != 0) {
                    return 1;
                }
                return _poweroff(var_r17, (_GBA_PHASE)6);
            case 1:                                 /* switch 3 */
                if ((s8) temp_r16 == 2) {
                    if (_waitAction(var_r17, (_GBA_WAIT_FLAG)3) != 0) {
                        return 1;
                    }
                    return _poweroff(var_r17, (_GBA_PHASE)6);
                }
                goto block_130;
            case 2:                                 /* switch 3 */
                if ((s8) temp_r16 == 3) {
                    if (_waitAction(var_r17, (_GBA_WAIT_FLAG)3) != 0) {
                        return 1;
                    }
                    return _poweroff(var_r17, (_GBA_PHASE)6);
                }
                goto block_130;
            case 3:                                 /* switch 3 */
                if ((s8) temp_r16 == 0) {
                    if (_waitAction(var_r17, (_GBA_WAIT_FLAG)3) != 0) {
                        return 1;
                    }
                    return _poweroff(var_r17, (_GBA_PHASE)6);
                }
                goto block_130;
            default:                                /* switch 3 */
block_130:
                var_r17->channel = (u8) sp988[1];
                if (_waitAction(var_r17, (_GBA_WAIT_FLAG)7) == 0) {
                    return _poweroff(var_r17, (_GBA_PHASE)6);
                }
                var_r27 += 1;
                var_r19 += 1;
                sp988 = &sp988[1];
                if ((u32) var_r19 >= 4U) {
                    return 1;
                }
                goto loop_26;
            }
        } else {
            return _poweroff(var_r17, (_GBA_PHASE)6);
        }
        break;
    }
}
