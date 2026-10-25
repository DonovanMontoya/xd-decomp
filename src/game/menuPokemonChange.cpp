#include <game/menuPokemonChangeLayout.hpp>

extern "C" {
s32 windowGetParam(tagWINDOW_WORK*, s32);
u8 GSgfxVideoGetVsyncRate();
double sin(double);
u32 GSmsgGetGSchar(u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32,s32,s32,u32,u32);
void GSmsgPrintRect(s32,s16,s16,s16,s16,u32,u32);
u32 heroBiosGetNamePtr(Hero*);
void menuFaceDisp(tagWINDOW_WORK*,tagSPRITE_WORK*,Pokemon*);
void menuCBMessageCenterDisp(tagWINDOW_WORK*,tagSPRITE_WORK*,u32);
void menuModelAdjustCamera(MENU_MODEL*);
void menuModelSetSize(MENU_MODEL*,s32,s16,s16,s16);
void menuModelSetZoom(MENU_MODEL*,f32);
void menuModelRender(MENU_MODEL*);
u8 menuSubGetPokemonSexForFightDisp(Pokemon*);
u8 fn_80098B44(u8,Pokemon*);
u16 pokemonBiosGetItemDataId(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
u32 pokemonBiosGetPokemonWazaDataId(Pokemon*,u16);
u16 pokemonGetSoubiItemDataId(Pokemon*);
u8 pokemonWazaCheckValid(Pokemon*,u16);
u32 pokemonDataBiosGetName(void*);
u32 itemDataBiosGetName(void*);
u32 wazaGetStatus(void*,s32,s32,s32);
s32 pokecoloGetCountryCode();

void floorMapSetDisp(s32);
void scriptModelStopMotion(u32);
void GSthreadSwitch(void);
u8 winSeqCheckMove(s32);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
void menuSetDisp(s32, bool);
tagWINDOW_WORK *windowSearchID(s32);
tagSPRITE_WORK *windowSearchItemID(tagWINDOW_WORK *, u16);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
s32 floorGetCurrentGroupID(void);
void *scriptModelOpen(u32);
void *GSresGetResource(s32, void *);
void cameraPlayAnime(s32, u32, s32, f32);
void cameraSetType(s32);
void GSmodelSetVisibility(void *, s32);
void fadeSet(s32, f32);
void GSfsysReadWait(s32);
void *memcardMemAllocForSavedata(void);
void menuGBACSetRomVer(s32, s32);
u8 menuFaceCheckLoading(void);
void GSfsysFree(s32);
void GSresFreeGroup(s32);
u8 GSfloorIsFloorPushed(void);
void GSfloorPop(void);
s32 floorGetPrevFloorID(void);
void floorLink(s32, s32);
u8 pokemonBiosGetFuseiFlag(Pokemon *);
u8 pokemonCheckValid(Pokemon *);
u8 pokemonBiosGetTamagoFlag(Pokemon *);
u8 menuCBRule_CheckPokemonEventFlag(Pokemon *);
u8 menuCBRule_CheckPokemonError(Pokemon *, s32);
void *itemDataBiosGetPtr(u16);
u8 itemDataBiosCheckExportable(void *);
u8 itemDataBiosCheckImportable(void *);
void msgctrlSetValue(s32, u32);
u32 pokemonBiosGetNicknamePtr(Pokemon *);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
void winMsgOpenWithSE(s32, s32, s32, s32, s32);
void winMsgClose(s32);
void windowCheckCursor(s32, s32);
s32 windowGetValue(s32);
s32 menuGetLastError(void);
void menuClose(s32);
u32 heroGetStatus(Hero *, s32, s32);
void memoDataSet(s32, Pokemon *);
void pokemonBiosSetFriend(Pokemon *, s32);
void pokemonBiosCopy(Pokemon *, Pokemon *);
void pokemonInit(Pokemon *);
void scriptModelSetMotion(u32, s32, s32, s32);
void cameraWaitSyncAnime(s32);
void winSeqSetMenu(s32, s32);
void menuCloseCustom(s32, s32, s32);
void scriptModelClose(void *);
void fadeSetToBlackOutIfNotBlack(f32);
void fadeSetToBlackInIfBlack(f32);
f32 timeGetLastFrameSec(void);
u8 gbaCommandIsConnected(s32);
void menuSetEnablePort(s32);
void GSsndPlayNow(u32);
void winMsgOpen(s32, s32, s32, s32);
void fadeCheck(s32);
void *memset(void *, int, u32);
void menuFaceLoad(Pokemon *, Pokemon *(*)(void *), void *);
void menuCursorNormal(tagWINDOW_WORK *, s32);
u32 pokemonGetStatus(Pokemon *, s32, s32, s32);
u32 GSmsgGetCharLength(u16 *);
s32 GSfloorGetCurrentFloorGroupID(void);
s8 menuSubOpenYesNoField(void);
s32 floorGetNextFloorID(void);
void gamedatasaveSetStatus(s32, s32, s32);
s32 memcardTaskCall(s32, s32, s32);
void GSthreadUnblockGroup(s32);
struct PcPortKey {
    u8 pad0[4];
    u16 trg;
};
PcPortKey *windowGetPortKeyInfo(s32);
s32 GSfsysGetDriveStatus(void);
void *savedataGetStatus(s32, s32);
void *memcpy(void *, const void *, u32);
void GSfloorPush(s32);
void floorWaitForChange(void);
s32 openMenuGBA(s32, s32, Hero **);
void pokemonEvolutionAll(Pokemon *, u16, u16, void *, s32, s32, s32, s32);
s32 menuPokemonStatusOpenFromPokemonChange(Pokemon *, Pokemon *(*)(Pokemon *, MENU_POKEMON_CB_TYPE, long), long);
}

struct PcMenuItem {
    u8 enable : 1;
    u8 rest : 7;
    u8 pad1[5];
    s16 x;
    u8 pad8[0x10];
    s16 next;
};
struct PcMenuData {
    u8 pad0[6];
    s16 first;
};
extern "C" {
PcMenuData *menuDataBiosGetPtr(s32);
PcMenuItem *menuItemBiosGetPtr(s32, s32);
}

struct MenuItemSimple {
    u8 pad[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};
MenuItemSimple *menuPtItemGetByMenuIdAndItemId(long, u32, long);
u32 menuPtSpriteWorkGetIndexFromId(tagWINDOW_WORK*,tagSPRITE_WORK*,u32);
struct MENU_MODEL;
extern "C" {
void menuModelInit(MENU_MODEL *, long, long);
void menuModelLoadPokemon(MENU_MODEL *, Pokemon *);
void menuModelCheck(MENU_MODEL *, s32);
void menuModelFree(MENU_MODEL *);
void menuModelTerm(MENU_MODEL *);
}

struct PokemonChangeKeys {
    u8 pad0[0x14];
    u16 hold;
    u8 pad16[4];
    u16 repeat;
};
extern PokemonChangeKeys winSysWork;
extern PokemonChangeKeys winSysWork2;

struct POKEMON_EVOLUTION_INFO {
    u8 data[4];
};

namespace {

enum enumPlayerIndex { PLAYER_0, PLAYER_1 };
enum MENU_POKEMONCHANGE_USERTYPE { MENU_POKEMONCHANGE_USERTYPE_0, MENU_POKEMONCHANGE_USERTYPE_1 };
enum enumMenuState { MENU_STATE_0, MENU_STATE_1, MENU_STATE_2, MENU_STATE_3, MENU_STATE_4, MENU_STATE_5, MENU_STATE_6 };

void _menuSetMsg(long, u16, u32);
long _getPokemonState(Pokemon *, enumPlayerIndex);
bool _isPokemonItemExchangeOk(Pokemon*,enumPlayerIndex);
bool _isPokemonBattleAble(Pokemon *, enumPlayerIndex);

bool _isPokemonValid(Pokemon *, enumPlayerIndex);
bool _isPokemonExchangeAble(Pokemon *, enumPlayerIndex);
void _setInfo(u32);
s16 _selectDisplay_2p_offset();
Pokemon *_cbMenuPokemonStatus(Pokemon *, MENU_POKEMON_CB_TYPE, long);
long _actionSelect2or3(u32, u32, u32);
void _menuWait(f32);
void _pokemonChangeFadeOut(f32);
void _pokemonChangeFadeIn(f32);

class CMenuPokemonChange {
public:
    s32 menuState;
    s32 menuTbl[8];
    Hero *hero0;
    Hero hero1;
    s32 currentPlayer;
    CState cstate;
    s32 menuId;
    void *saveData;
    u8 ready[2];
    u8 padA56[2];
    s32 bgModelId;
    void *bgModel;
    s32 selectIndex[2];
    s32 lookIndex;
    MENU_MODEL models[2];
    s32 exchangeSeed;
    unsigned long long elapsed;
    u8 flagC50;
    u8 flagC51;
    u8 padC52[6];

    void ctrlHook(tagWINDOW_WORK *);
    void selectItemHook(tagWINDOW_WORK *, tagSPRITE_WORK *);
    void selectItemHookPrime(tagWINDOW_WORK *, tagSPRITE_WORK *, u32);
    void selectDrawHook(tagWINDOW_WORK *);
    void bgDrawFadeIn();
    void bgDrawFadeIn(f32);
    void stateFunctionSaveReport();
    void stateFunctionEvolution();
    void stateFunctionExChangeOK();
    void stateFunctionExChangeMain();
    void stateFunctionExChangeStart();
    bool bgDrawFadeIsLive();
    void bgModelRelease();
    Pokemon *pokemonStatusCallback(Pokemon *, MENU_POKEMON_CB_TYPE, enumPlayerIndex);
    long pokemonStatusSearch(long, long);
    void requestPokemonFaceLoad();
    void stateFunctionCheckconnection();
    void stateFunctionConfirmExChange();
    void _pokemonChangeEvolutionEffect(Pokemon *, MENU_POKEMONCHANGE_USERTYPE, u16, POKEMON_EVOLUTION_INFO);
    void main();
    bool gbaConnectionCheckIsError();
    void stateFunctionSelectPokemon2PokeExChange();
    void stateFunctionSelectPokemon1PokeExChange();
    void stateFunctionSelectPokemon1CheckStatus();
    void stateFunctionSelectPokemonStart();
    void stateFunctionSelectPokemon2Reset();
    long getQuantityAllPokemon();
    long getQuantityHeroPokemon(enumPlayerIndex);
    void waitMenuOpen();
    void stateFunctionError(Pokemon *, u32);
    void stateFunctionCheckNext();
    void stateFunctionSelectPokemon2DecideAfterWait();
    void stateFunctionSelectPokemon2CheckStatus();
    void stateFunctionSelectPokemon2Selected();
    void stateFunctionSelectPokemon2Main();
    void stateFunctionSelectPokemon1Chanceld();
    void stateFunctionSelectPokemon1Selected();
    void stateFunctionSelectPokemon1Main();
    bool pokmonSelectCheck(enumPlayerIndex);
    bool isPokemonLookAbleStatus(long);
    inline Pokemon *getPokemonBySelect(long selected) {
        int side = 0;
        if (selected >= getQuantityHeroPokemon(PLAYER_0)) {
            selected -= getQuantityHeroPokemon(PLAYER_0);
            side = 1;
        }
        Hero *hero;
        if (side == 0) {
            hero = hero0;
        } else {
            hero = &hero1;
        }
        return hero->getPokemon(selected);
    }
    void loop();
    void init();
    void bgModelLoad();
    void bgDrawFadeOut();
    void oneMenuLoad(long);
    long selectPokemonMenuOpen();
    bool pokemonExchangeCheck(enumPlayerIndex);
    void menuStateChange(enumMenuState);
    void menuPokemonStatusExecute(enumPlayerIndex);
    void setMenuByTbl(long *);
};

CMenuPokemonChange MenuPokemonChange;


inline u32 pokemonChangeSecondsToFrames(f32 seconds) {
    return (u32)(seconds * (f32)GSgfxVideoGetVsyncRate());
}

#pragma opt_common_subs off
void CMenuPokemonChange::selectItemHookPrime(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, u32 id) {
    s32 player;
    u32 color;
    Hero* hero;
    Pokemon* selected;
    u8 pulse;
    player = windowGetParam(win,0);
    hero = player == 0 ? hero0 : &hero1;
    selected = getPokemonBySelect(selectIndex[player]);
    u8 alpha = win->alpha;
    sprite->channels.alpha = alpha;
    color = alpha | ~0xFF;
    if (cstate.unk0 == 13 || cstate.unk0 == 8) pulse = 255;
    else {
        u32 period = pokemonChangeSecondsToFrames(1.0f);
        f32 frame = (f32)(u32)(elapsed % period);
        pulse = (sprite->channels.alpha * (u32)(205.0f * (f32)sin(3.1415927f * (frame / (f32)period)) + 50.0f)) / 255;
    }
    switch(id) {
    case 0x5F3:
    case 0x5F4:
    case 0x5F5:
    case 0x5F6:
    case 0x5F7:
    case 0x5F8:
    {
        Pokemon* poke = hero->getPokemon(menuPtSpriteWorkGetIndexFromId(win,sprite,0x5F3));
        if (_isPokemonValid(poke,(enumPlayerIndex)player)) {
            menuFaceDisp(win,sprite,poke); winSpriteSetDisp(sprite,1);
        } else winSpriteSetDisp(sprite,0);
        break;
    }
    case 0x5F9:
    case 0x5FA:
    case 0x5FB:
    case 0x5FC:
    case 0x5FD:
    case 0x5FE:
    {
        Pokemon* poke = hero->getPokemon(menuPtSpriteWorkGetIndexFromId(win,sprite,0x5F9));
        switch(_getPokemonState(poke,(enumPlayerIndex)player)) {
        case 4: case 7: case 0: sprite->color = 0xFFFFFFFF; break;
        case 3: sprite->color = 0xB473C8FF; break;
        default: sprite->color = 0xDC6464FF; break;
        }
        break;
    }
    case 0x5FF:
    case 0x600:
    case 0x601:
    case 0x602:
    case 0x603:
    case 0x604:
    {
        Pokemon* poke = hero->getPokemon(menuPtSpriteWorkGetIndexFromId(win,sprite,0x5FF));
        u16 item = 0;
        if (_isPokemonValid(poke,(enumPlayerIndex)player)) item = pokemonBiosGetItemDataId(poke);
        sprite->color = 0xFFFFFFFF;
        if (item != 0 && !_isPokemonItemExchangeOk(poke,(enumPlayerIndex)player)) sprite->color = 0xFF0000FF;
        winSpriteSetDisp(sprite,item != 0);
        break;
    }
    case 0x60F:
    case 0x610:
    case 0x611:
    case 0x612:
    case 0x613:
    case 0x614:
    {
        Pokemon* poke = hero->getPokemon(menuPtSpriteWorkGetIndexFromId(win,sprite,0x60F));
        u32 sex = 0;
        switch(_getPokemonState(poke,(enumPlayerIndex)player)) {
        case 0: case 1: case 2: break;
        default:
            switch(fn_80098B44(menuSubGetPokemonSexForFightDisp(poke),poke)) {
            case 0: sex = 0x9C5; break;
            case 1: sex = 0x9C6; break;
            }
        }
        if (sex != 0) {
            msgctrlSetValue(0x37,GSmsgGetGSchar(sex));
            GSmsgPrint2(win->messageContext,0,0,color,0x4276);
            winSpriteSetDisp(sprite,1);
        } else winSpriteSetDisp(sprite,0);
        break;
    }
    case 0x615:
    case 0x616:
    case 0x617:
    case 0x618:
    case 0x619:
    case 0x61A:
    {
        Pokemon* poke = hero->getPokemon(menuPtSpriteWorkGetIndexFromId(win,sprite,0x615));
        u32 message = 0x4277;
        switch(_getPokemonState(poke,(enumPlayerIndex)player)) {
        case 1: msgctrlSetValue(0x37,GSmsgGetGSchar(0x56C)); break;
        case 2: msgctrlSetValue(0x37,GSmsgGetGSchar(0x56B)); break;
        case 0: message = 0; break;
        default: msgctrlSetValue(0x37,pokemonBiosGetNicknamePtr(poke)); break;
        }
        if (message) {
            u32 rect = GSmsgGetRect(message);
            GSmsgPrint2(win->messageContext,(s16)(sprite->width / 2 - (s16)(rect >> 16) / 2) - 1,0,color,0x4277);
            winSpriteSetDisp(sprite,1);
        } else winSpriteSetDisp(sprite,0);
        break;
    }
    case 0x61B:
        msgctrlSetValue(0x37,heroBiosGetNamePtr(hero));
        GSmsgPrint2(win->messageContext,0,0,color,0x4277); break;
    case 0x605:
    case 0x606:
    case 0x607:
    case 0x608:
    case 0x609:
    case 0x60A:
    case 0x60B:
    case 0x60C:
        winSpriteSetDisp(sprite, menuState == player); break;
    case 0x8B9:
    case 0x8BA:
    case 0x8BB:
    case 0x8BC:
    case 0x8BD:
    case 0x8BE:
    {
        s32 index = selectIndex[player];
        if (index >= getQuantityHeroPokemon(PLAYER_0)) index -= getQuantityHeroPokemon(PLAYER_0);
        u8 display = 0;
        if (index == menuPtSpriteWorkGetIndexFromId(win,sprite,0x8B9)) {
            if (player == 0) {u8 active = 0; if(cstate.unk0 >= 12 && cstate.unk0 <= 16) active=1; display=active;}
            else if (player == 1) display = cstate.unk0 == 16;
        }
        winSpriteSetDisp(sprite,display); break;
    }
    case 0x8CE:
    case 0x8CF:
    case 0x8D0:
    case 0x8D1:
    case 0x8D2:
    case 0x8D3:
    {
        s32 selection=windowGetValue(0xD6);
        s32 index=selection;
        if(index>=getQuantityHeroPokemon(PLAYER_0)) index-=getQuantityHeroPokemon(PLAYER_0);
        s32 side;
        if(selection>=getQuantityHeroPokemon(PLAYER_0)) side=1;else side=0;
        s32 slot=menuPtSpriteWorkGetIndexFromId(win,sprite,0x8CE);
        u8 display=0;
        if(slot==index && side==player && cstate.unk0!=16 && slot<getQuantityHeroPokemon((enumPlayerIndex)side)) display=1;
        winSpriteSetDisp(sprite,display); sprite->channels.alpha=pulse;break;
    }
    case 0x620:
        winSpriteSetDisp(sprite,flagC50);
        if (flagC50) menuCBMessageCenterDisp(win,sprite,0xC4AC);
        break;
    case 0x61F: winSpriteSetDisp(sprite,flagC50); break;
    case 0x8D4:
        {s32 selection=windowGetValue(0xD6);s32 count=getQuantityHeroPokemon(PLAYER_1);
        winSpriteSetDisp(sprite,selection==getQuantityHeroPokemon(PLAYER_0)+count);sprite->channels.alpha=pulse;}break;
    case 0x8BF: winSpriteSetDisp(sprite,windowGetValue(win->menu)==0); break;
    case 0x8C0: winSpriteSetDisp(sprite,windowGetValue(win->menu)==1); break;
    case 0x8C5: winSpriteSetDisp(sprite,windowGetValue(win->menu)==0); break;
    case 0x8C6: winSpriteSetDisp(sprite,windowGetValue(win->menu)==1); break;
    case 0x8C7: winSpriteSetDisp(sprite,windowGetValue(win->menu)==2); break;
    case 0x63D:
        if(win->alpha==255) {
            MENU_MODEL* model = &models[player];
            menuModelAdjustCamera(model);
            menuModelSetSize(model,win->x+sprite->x,sprite->y,sprite->width,sprite->height);
            f32 zoom;
            if(pokemonBiosGetPokemonDataId(selected)==0x18E) zoom=0.4f; else zoom=0.65f;
            menuModelSetZoom(model,zoom); menuModelRender(model);
        }
        break;
    case 0x640: selectItemHookPrime(win,sprite,0x61B); break;
    case 0x642:
        msgctrlSetValue(0x34,selected->getLevel());
        GSmsgPrint2(win->messageContext,0,0,color,0x426F); break;
    case 0x7B3:
        msgctrlSetValue(0x37,(u32)selected->getNicknamePtr());
        switch(pokecoloGetCountryCode()) {
        case 0: GSmsgPrint2(win->messageContext,0,0,color,0x4276); break;
        case 1: case 2: GSmsgPrint2(win->messageContext,0,0,color,0x4277); break;
        }
        break;
    case 0x7B4: {
        u32 sex;
        switch(fn_80098B44(menuSubGetPokemonSexForFightDisp(selected),selected)) {
        case 0: sex=0x9C5; break; case 1:sex=0x9C6;break; default:sex=0;break;
        }
        if(sex) {msgctrlSetValue(0x37,GSmsgGetGSchar(sex)); GSmsgPrint2(win->messageContext,0,0,color,0x4276);winSpriteSetDisp(sprite,1);}
        else winSpriteSetDisp(sprite,0);
        break;
    }
    case 0x643:
        msgctrlSetValue(0x37,GSmsgGetGSchar(pokemonDataBiosGetName(selected->getPokemonDataPtr())));
        switch(pokecoloGetCountryCode()) {
        case 0: GSmsgPrint2(win->messageContext,0,0,color,0x4276); break;
        case 1: case 2: GSmsgPrint2(win->messageContext,0,0,color,0x4277); break;
        }
        break;
    case 0x645:
    case 0x646:
    case 0x647:
    case 0x648:
    {
        u16 slot=menuPtSpriteWorkGetIndexFromId(win,sprite,0x645);
        s32 move=pokemonBiosGetPokemonWazaDataId(selected,slot);
        if(pokemonWazaCheckValid(selected,slot)) {
            u32 name=wazaGetStatus(0,move,1,0);
            if(name) {msgctrlSetValue(0x37,GSmsgGetGSchar(name));GSmsgPrintRect(win->messageContext,0,0,sprite->width,sprite->height,color,0x4277);winSpriteSetDisp(sprite,1);}
            else winSpriteSetDisp(sprite,0);
        } else winSpriteSetDisp(sprite,0);
        break;
    }
    case 0x64A:
        {u16 item=pokemonGetSoubiItemDataId(selected);
        if(item) {msgctrlSetValue(0x37,GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(item))));GSmsgPrint2(win->messageContext,0,0,color,0x4277);winSpriteSetDisp(sprite,1);}
        else winSpriteSetDisp(sprite,0);}
        break;
    case 0x637: winSpriteSetDisp(sprite,ready[player]==0);break;
    case 0x638: winSpriteSetDisp(sprite,ready[player]==0);break;
    case 0x64B: sprite->message=0xC495;winSpriteSetDisp(sprite,ready[player]==0);break;
    case 0x64C: winSpriteSetDisp(sprite,ready[player]==0);sprite->message=0x4295;break;
    case 0x64D: winSpriteSetDisp(sprite,ready[player]);break;
    case 0x652: selectItemHookPrime(win,sprite,0x63D);break;
    case 0x653: selectItemHookPrime(win,sprite,0x61B);break;
    }
}

#pragma opt_common_subs reset
void CMenuPokemonChange::selectItemHook(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    selectItemHookPrime(win, sprite, sprite->id);
}

bool CMenuPokemonChange::gbaConnectionCheckIsError() {
    if (!gbaCommandIsConnected(2)) {
        menuSetEnablePort(1);
        GSsndPlayNow(0x13);
        winMsgOpen(2, 0xC4A3, 1, 0);
        cstate.unk4 = 2;
        memset(cstate.saved, 0, 0x40);
        return true;
    }
    return false;
}

void CMenuPokemonChange::stateFunctionSelectPokemon2PokeExChange() {
    if (pokemonExchangeCheck(PLAYER_1)) {
        cstate.unk4 = 0x10;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1PokeExChange() {
    if (pokemonExchangeCheck(PLAYER_0)) {
        cstate.unk4 = 0xC;
        memset(cstate.saved, 0, 0x40);
        stateFunctionSelectPokemon2Reset();
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1CheckStatus() {
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    menuPokemonStatusExecute(PLAYER_0);
    flagC51 = 1;
    menuStateChange(MENU_STATE_3);
    waitMenuOpen();
    _pokemonChangeFadeIn(0.3f);
    fadeCheck(1);
    cstate.unk4 = 8;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionSelectPokemonStart() {
    selectIndex[0] = 0;
    selectIndex[1] = getQuantityHeroPokemon(PLAYER_0);
    cstate.unk4 = cstate.unk0 + 1;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionSelectPokemon2Reset() {
    selectIndex[1] = getQuantityHeroPokemon(PLAYER_0);
}

long CMenuPokemonChange::getQuantityAllPokemon() {
    long a = getQuantityHeroPokemon(PLAYER_1);
    long b = getQuantityHeroPokemon(PLAYER_0);
    return b + a;
}

long CMenuPokemonChange::getQuantityHeroPokemon(enumPlayerIndex player) {
    Hero *hero;
    long i;
    if (player == PLAYER_0) {
        hero = hero0;
    } else {
        hero = &hero1;
    }
    i = 0;
    do {
        if (!_isPokemonValid(hero->getPokemon(i), player)) {
            break;
        }
        i++;
    } while (i < 6);
    return i;
}

long CMenuPokemonChange::selectPokemonMenuOpen() {
    enumPlayerIndex player = (enumPlayerIndex)currentPlayer;
    Hero *hero;
    PcMenuItem *item;
    int side;
    int i;
    PcMenuData *data;
    windowSearchID(0xD6);
    data = menuDataBiosGetPtr(0xD6);
    item = menuItemBiosGetPtr(0xD6, data->first);
    for (side = 0; side < 2; side++) {
        if (side == 0) {
            hero = hero0;
        } else {
            hero = &hero1;
        }
        for (i = 0; i < 6; i++) {
            item->enable = _isPokemonValid(hero->getPokemon(i), player);
            item = menuItemBiosGetPtr(0xD6, item->next);
        }
    }
    static bool isDirty = false;
    if (!isDirty) {
        isDirty = true;
        s16 offset = _selectDisplay_2p_offset();
        int j;
        item = menuItemBiosGetPtr(0xD6, 0x627);
        for (j = 0; j < 6; j++) {
            item->x += offset;
            item = menuItemBiosGetPtr(0xD6, item->next);
        }
    }
    menuOpenCustom(0xD6, windowGetActiveID(), &selectIndex[player], flagC51 ? 4 : 0, 0, 0);
    _setInfo(0xC491);
    return 0xD6;
}

void CMenuPokemonChange::waitMenuOpen() {
    while (winSeqCheckMove(menuId)) {
        GSthreadSwitch();
    }
}

void CMenuPokemonChange::oneMenuLoad(long id) {
    menuId = id;
    if (id == 0xD6) {
        selectPokemonMenuOpen();
    } else {
        menuOpenCustom(id, windowGetActiveID(), 0, 4, 0, 0);
        menuSetDisp(id, id == 0xD3);
    }
}

void CMenuPokemonChange::menuStateChange(enumMenuState state) {
    menuState = state;
    switch (state) {
    case MENU_STATE_0: {
        static long tbl[] = {0};
        setMenuByTbl(tbl);
        break;
    }
    case MENU_STATE_1: {
        static long tbl[] = {0xD3, 0};
        setMenuByTbl(tbl);
        break;
    }
    case MENU_STATE_2: {
        static long tbl[] = {0xD3, 0xE1, 0};
        setMenuByTbl(tbl);
        break;
    }
    case MENU_STATE_3:
    case MENU_STATE_4: {
        static long tbl[] = {0xD3, 0xE1, 0xD4, 0xD5, 0xD6, 0};
        setMenuByTbl(tbl);
        break;
    }
    case MENU_STATE_5: {
        static long tbl[] = {0xD3, 0xE1, 0xDD, 0};
        setMenuByTbl(tbl);
        break;
    }
    case MENU_STATE_6: {
        static long tbl[] = {0xD3, 0xE1, 0xDE, 0};
        setMenuByTbl(tbl);
        break;
    }
    }
    flagC51 = 0;
}

Pokemon *pokemonChangeRequestPokemonFaceLoadCallBack(void *arg) {
    u32 *p = (u32 *)arg;
    if (p == 0) {
        return 0;
    }
    if (p[13] >= 13) {
        return 0;
    }
    u32 idx = p[13];
    p[13] = idx + 1;
    return (Pokemon *)p[idx];
}

void CMenuPokemonChange::requestPokemonFaceLoad() {
    static struct {
        Pokemon *list[13];
        u32 index;
    } stPokemonListFace;
    int count = 0;
    enumPlayerIndex side;
    int i;
    for (side = PLAYER_0; side < 2; side = (enumPlayerIndex)(side + 1)) {
        for (i = 0; i < 6; i++) {
            Hero *hero;
            if (side == 0) {
                hero = hero0;
            } else {
                hero = &hero1;
            }
            Pokemon *pokemon = hero->getPokemon(i);
            if (_isPokemonValid(pokemon, side)) {
                stPokemonListFace.list[count++] = pokemon;
            }
        }
    }
    stPokemonListFace.list[count] = 0;
    stPokemonListFace.index = 0;
    menuFaceLoad(0, pokemonChangeRequestPokemonFaceLoadCallBack, &stPokemonListFace);
}

Pokemon *CMenuPokemonChange::pokemonStatusCallback(Pokemon *, MENU_POKEMON_CB_TYPE type, enumPlayerIndex) {
    getQuantityAllPokemon();
    long idx = lookIndex;
    if (type == MENU_POKEMON_CB_TYPE_1) {
        idx = pokemonStatusSearch(lookIndex, -1);
    } else if (type == MENU_POKEMON_CB_TYPE_2) {
        idx = pokemonStatusSearch(lookIndex, 1);
    }
    lookIndex = idx;
    return getPokemonBySelect(lookIndex);
}

long CMenuPokemonChange::pokemonStatusSearch(long, long dir) {
    long total = getQuantityAllPokemon();
    long idx = lookIndex;
    do {
        idx += dir;
        if (idx < 0 || idx >= total) {
            return lookIndex;
        }
    } while (!isPokemonLookAbleStatus(idx));
    return idx;
}

void CMenuPokemonChange::menuPokemonStatusExecute(enumPlayerIndex player) {
    lookIndex = selectIndex[player];
    Pokemon *pokemon = getPokemonBySelect(selectIndex[player]);
    menuPokemonStatusOpenFromPokemonChange(pokemon, _cbMenuPokemonStatus, player);
    selectIndex[player] = lookIndex;
}

void CMenuPokemonChange::stateFunctionCheckconnection() {
    Hero *heroes[4] = {0, 0, 0, 0};
    heroes[1] = &hero1;
    if (openMenuGBA(0, 9, heroes) < 0) {
        cstate.unk4 = 4;
        memset(cstate.saved, 0, 0x40);
    } else {
        requestPokemonFaceLoad();
        cstate.unk4 = cstate.unk0 + 1;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::_pokemonChangeEvolutionEffect(Pokemon *pokemon, MENU_POKEMONCHANGE_USERTYPE type, u16 id, POKEMON_EVOLUTION_INFO info) {
    if (id != 0 && id != 0xFFFF) {
        switch (type) {
        case MENU_POKEMONCHANGE_USERTYPE_0:
            pokemonEvolutionAll(pokemon, id, 0, &info, 0, 0, 0, 1);
            break;
        case MENU_POKEMONCHANGE_USERTYPE_1:
            pokemonEvolutionAll(pokemon, id, 0, &info, 0, 1, 0, 1);
            break;
        }
    }
}

void CMenuPokemonChange::stateFunctionConfirmExChange() {
    long i;
    CMenuPokemonChange *m;
    u8 ready0;
    u8 ready1;
    u32 key0;
    u32 key1;
    ready[0] = 0;
    ready[1] = 0;
    menuStateChange((enumMenuState)5);
    bgDrawFadeIn();
    menuSetEnablePort(3);
    ready0 = 0;
    ready1 = 0;
    while (!ready0 || !ready1) {
        key0 = windowGetPortKeyInfo(1)->trg;
        key1 = windowGetPortKeyInfo(2)->trg;
        if (gbaConnectionCheckIsError()) {
            goto done;
        }
        if (GSfsysGetDriveStatus() != 5) {
            if (key0 & 0x10) {
                if (!ready0) {
                    GSsndPlayNow(0x11);
                }
                ready0 = 1;
            } else if (key0 & 0x20) {
                GSsndPlayNow(0x12);
                if (!ready0) {
                    break;
                }
                ready0 = 0;
            }
            if (key1 & 0x10) {
                if (!ready1) {
                    GSsndPlayNow(0x11);
                }
                ready1 = 1;
            } else if (key1 & 0x20) {
                GSsndPlayNow(0x12);
                if (!ready1) {
                    break;
                }
                ready1 = 0;
            }
        }
        GSthreadSwitch();
        ready[0] = ready0;
        ready[1] = ready1;
    }
    ready[0] = ready0;
    ready[1] = ready1;
    if (!ready0 || !ready1) {
        cstate.unk4 = 7;
        memset(cstate.saved, 0, 0x40);
    } else {
        void *src = savedataGetStatus(0, 0);
        memcpy(saveData, src, 0x27FD0);
        cstate.unk4 = 0x12;
        memset(cstate.saved, 0, 0x40);
    }
done:
    bgDrawFadeOut();
    m = this;
    for (i = 0; i < 2; i++) {
        menuModelFree(&m->models[0]);
        menuModelTerm(&m->models[0]);
        m = (CMenuPokemonChange *)((u8 *)m + sizeof(MENU_MODEL));
    }
    menuSetEnablePort(1);
}

void _pokemonChangeFadeIn(f32 t) {
    fadeSetToBlackInIfBlack(t);
}

void _pokemonChangeFadeOut(f32 t) {
    fadeSetToBlackOutIfNotBlack(t);
    fadeCheck(1);
}

void _menuWait(f32 t) {
    f32 elapsed = 0.0f;
    while (elapsed < t) {
        GSthreadSwitch();
        elapsed += timeGetLastFrameSec();
    }
}

void _setInfo(u32 msg) {
    _menuSetMsg(0xD5, 0x61E, msg);
}

s16 _selectDisplay_2p_offset() {
    MenuItemSimple *a = menuPtItemGetByMenuIdAndItemId(0xD4, 0x60D, 0);
    MenuItemSimple *b = menuPtItemGetByMenuIdAndItemId(0xD4, 0x60E, 0);
    return b->x - a->x;
}

bool _isPokemonExchangeAble(Pokemon *p, enumPlayerIndex player) {
    return _getPokemonState(p, player) == 7;
}

bool _isPokemonValid(Pokemon *p, enumPlayerIndex player) {
    return _getPokemonState(p, player) != 0;
}

bool _pokemonChangeGetHinsi(Pokemon *p) {
    return p->getHp() == 0;
}

long _getQuantityBattleAbleWoIt(Hero *hero, long skip, enumPlayerIndex player) {
    long n = 0;
    long i;
    for (i = 0; i < 6; i++) {
        if (i != skip && _isPokemonBattleAble(hero->getPokemon(i), player)) {
            n++;
        }
    }
    return n;
}

bool _isPokemonItemExchangeOk(Pokemon *p, enumPlayerIndex player) {
    u16 item = p->getItemDataId();
    if (item == 0) {
        return true;
    }
    if (player == PLAYER_0) {
        if (!itemDataBiosCheckExportable(itemDataBiosGetPtr(item))) {
            return false;
        }
    } else {
        if (!itemDataBiosCheckImportable(itemDataBiosGetPtr(item))) {
            return false;
        }
    }
    return true;
}

long _getPokemonState(Pokemon *p, enumPlayerIndex player) {
    if (p == 0) {
        return 0;
    }
    if (pokemonBiosGetFuseiFlag(p)) {
        return 1;
    }
    if (!pokemonCheckValid(p)) {
        return 0;
    }
    if (pokemonBiosGetTamagoFlag(p)) {
        return 2;
    }
    if (p->isDarkPokemon()) {
        return 3;
    }
    if (!menuCBRule_CheckPokemonEventFlag(p)) {
        return 5;
    }
    if (!menuCBRule_CheckPokemonError(p, 0)) {
        return 6;
    }
    if (_isPokemonItemExchangeOk(p, player)) {
        return 7;
    }
    return 4;
}

bool _isPokemonBattleAble(Pokemon *p, enumPlayerIndex player) {
    long state = _getPokemonState(p, player);
    switch (state) {
    case 0:
    case 1:
    case 2:
        return false;
    }
    return !_pokemonChangeGetHinsi(p);
}

void _menuSetMsg(long menu, u16 item, u32 msg) {
    tagWINDOW_WORK *win = windowSearchID(menu);
    tagSPRITE_WORK *sprite = windowSearchItemID(win, item);
    if (msg != 0) {
        if (win != 0 && sprite != 0) {
            winSpriteSetDisp(sprite, 1);
            sprite->message = msg;
        }
    } else if (win != 0 && sprite != 0) {
        sprite->message = 0;
        winSpriteSetDisp(sprite, 0);
    }
}

void CMenuPokemonChange::bgModelLoad() {
    s32 group = floorGetCurrentGroupID();
    bgModelId = (s32)scriptModelOpen(0x5681000);
    bgModel = GSresGetResource(group, (void *)bgModelId);
    cameraPlayAnime(0x37C, 0x5691800, 1, 0.0f);
    cameraSetType(4);
    GSmodelSetVisibility(bgModel, 0);
}

void CMenuPokemonChange::init() {
    memset(this, 0, 0xC58);
    hero0 = Hero::getHeroPtr();
    cstate.init();
    fadeSet(3, 0.0f);
    GSfsysReadWait(0x88C);
    menuStateChange(MENU_STATE_2);
    bgModelLoad();
    _pokemonChangeFadeIn(0.3f);
}

void CMenuPokemonChange::main() {
    init();
    saveData = memcardMemAllocForSavedata();
    cstate.unk4 = 1;
    memset(cstate.saved, 0, 0x40);
    loop();
    menuGBACSetRomVer(0, 0xFFFF);
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    while (menuFaceCheckLoading()) {
        GSthreadSwitch();
    }
    bgModelRelease();
    GSfsysFree(0x88C);
    GSresFreeGroup(0x88C);
    if (GSfloorIsFloorPushed()) {
        GSfloorPop();
    } else {
        floorLink(floorGetPrevFloorID(), 0);
    }
}

bool CMenuPokemonChange::isPokemonLookAbleStatus(long index) {
    int selected = index;
    Pokemon *p = getPokemonBySelect(selected);
    long state;
    state = _getPokemonState(p, index >= getQuantityHeroPokemon(PLAYER_0) ? PLAYER_1 : PLAYER_0);
    switch (state) {
    case 1:
    case 2:
        return false;
    }
    return true;
}

#pragma opt_common_subs off
bool CMenuPokemonChange::pokmonSelectCheck(enumPlayerIndex player) {
    Pokemon *p = getPokemonBySelect(selectIndex[player]);
    long state;
    if (isPokemonLookAbleStatus(selectIndex[player])) {
        return true;
    }
    state = _getPokemonState(p, player);
    switch (state) {
    case 2:
        stateFunctionError(p, 0xC492);
        break;
    case 1:
        stateFunctionError(p, 0xC493);
        break;
    }
    return false;
}
#pragma opt_common_subs reset

bool CMenuPokemonChange::pokemonExchangeCheck(enumPlayerIndex player) {
    long index = selectIndex[player];
    Pokemon *p = getPokemonBySelect(index);
    long state = _getPokemonState(p, player);
    Hero *hero;
    switch (state) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        stateFunctionError(p, 0xC497);
        return false;
    case 4:
        stateFunctionError(p, 0xC496);
        return false;
    case 5:
    case 6:
        stateFunctionError(p, 0xC4AB);
        return false;
    case 7:
        break;
    }
    if (player == PLAYER_0) {
        hero = hero0;
    } else {
        hero = &hero1;
    }
    index = selectIndex[player];
    if (index >= getQuantityHeroPokemon(PLAYER_0)) {
        index -= getQuantityHeroPokemon(PLAYER_0);
    }
    if (_getQuantityBattleAbleWoIt(hero, index, player) == 0) {
        stateFunctionError(p, 0xC498);
        return false;
    }
    return true;
}

void CMenuPokemonChange::stateFunctionError(Pokemon *p, u32 msg) {
    u32 nickname = pokemonBiosGetNicknamePtr(p);
    msgctrlSetValue(0x32, nickname);
    _setInfo(msg);
    GSsndPlayNow(0x13);
    _menuWait(1.5f);
    _setInfo(0);
    if (cstate.unk0 >= 0xC) {
        cstate.unk4 = 0xC;
        memset(cstate.saved, 0, 0x40);
    } else {
        cstate.unk4 = 7;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionCheckNext() {
    s8 answer;
    long i;
    CMenuPokemonChange *m;
    winMsgOpen(2, 0xC4A1, 0, 0);
    answer = menuSubOpenYesNo(0, -1, -1, 0);
    winMsgClose(1);
    _menuWait(0.5f);
    bgDrawFadeOut();
    m = this;
    for (i = 0; i < 2; i++) {
        menuModelFree(&m->models[0]);
        menuModelTerm(&m->models[0]);
        m = (CMenuPokemonChange *)((u8 *)m + sizeof(MENU_MODEL));
    }
    if (answer == 0) {
        cstate.unk4 = 6;
        memset(cstate.saved, 0, 0x40);
    } else {
        cstate.unk4 = 2;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon2DecideAfterWait() {
    MenuItemSimple *item;
    long i;
    _menuWait(0.6f);
    item = menuPtItemGetByMenuIdAndItemId(0xDD, 0x63D, 0);
    i = 0;
    do {
        menuModelInit(&models[i], item->width, item->height);
        menuModelLoadPokemon(&models[i], getPokemonBySelect(selectIndex[i]));
        menuModelCheck(&models[i], 1);
        i++;
    } while (i < 2);
    bgDrawFadeOut();
    cstate.unk4 = 0x11;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionSelectPokemon2CheckStatus() {
    _pokemonChangeFadeOut(0.3f);
    menuStateChange(MENU_STATE_0);
    menuSetEnablePort(2);
    menuPokemonStatusExecute(PLAYER_1);
    menuSetEnablePort(1);
    flagC51 = 1;
    menuStateChange((enumMenuState)4);
    waitMenuOpen();
    _pokemonChangeFadeIn(0.3f);
    fadeCheck(1);
    if (menuGetLastError() == 1) {
        GSsndPlayNow(0x13);
        winMsgOpen(2, 0xC4A3, 1, 0);
        cstate.unk4 = 2;
        memset(cstate.saved, 0, 0x40);
    } else {
        cstate.unk4 = 0xD;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon2Selected() {
    if (pokmonSelectCheck(PLAYER_1)) {
        long index;
        long result;
        int player;
        menuSetEnablePort(2);
        index = selectIndex[currentPlayer];
        if (index >= getQuantityHeroPokemon(PLAYER_0)) {
            player = 1;
        } else {
            player = 0;
        }
        if (player == currentPlayer) {
            result = _actionSelect2or3(0xC494, 0xC495, 0xC4AC);
        } else {
            result = _actionSelect2or3(0xC494, 0xC4AC, 0);
        }
        menuSetEnablePort(1);
        if (!gbaConnectionCheckIsError()) {
            switch (result) {
            case 0xC494:
                cstate.unk4 = 0xE;
                memset(cstate.saved, 0, 0x40);
                return;
            case 0xC495:
                cstate.unk4 = 0xF;
                memset(cstate.saved, 0, 0x40);
                return;
            case 0xC4AC:
                cstate.unk4 = 0xC;
                memset(cstate.saved, 0, 0x40);
                break;
            }
        }
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon2Main() {
    long value;
    currentPlayer = 1;
    menuSetEnablePort(2);
    menuStateChange((enumMenuState)4);
    flagC50 = 1;
    windowCheckCursor(0xD6, 1);
    flagC50 = 0;
    menuSetEnablePort(1);
    if (!gbaConnectionCheckIsError()) {
        value = windowGetValue(0xD6);
        if (value == -1 || value >= getQuantityAllPokemon()) {
            cstate.unk4 = 7;
            memset(cstate.saved, 0, 0x40);
            return;
        }
        selectIndex[currentPlayer] = value;
        cstate.unk4 = 0xD;
        memset(cstate.saved, 0, 0x40);
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1Chanceld() {
    long result;
    _setInfo(0xC499);
    result = _actionSelect2or3(0x426A, 0x426B, 0);
    _setInfo(0);
    switch (result) {
    case 0x426A:
        cstate.unk4 = 2;
        memset(cstate.saved, 0, 0x40);
        return;
    case 0x426B:
        cstate.unk4 = 7;
        memset(cstate.saved, 0, 0x40);
        return;
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1Selected() {
    if (pokmonSelectCheck(PLAYER_0)) {
        long index;
        long result;
        int player;
        index = selectIndex[currentPlayer];
        if (index >= getQuantityHeroPokemon(PLAYER_0)) {
            player = 1;
        } else {
            player = 0;
        }
        if (player == currentPlayer) {
            result = _actionSelect2or3(0xC494, 0xC495, 0xC4AC);
        } else {
            result = _actionSelect2or3(0xC494, 0xC4AC, 0);
        }
        switch (result) {
        case 0xC494:
            cstate.unk4 = 0xA;
            memset(cstate.saved, 0, 0x40);
            return;
        case 0xC495:
            cstate.unk4 = 0xB;
            memset(cstate.saved, 0, 0x40);
            return;
        case 0xC4AC:
            cstate.unk4 = 7;
            memset(cstate.saved, 0, 0x40);
            break;
        }
    }
}

void CMenuPokemonChange::stateFunctionSelectPokemon1Main() {
    long value;
    stateFunctionSelectPokemon2Reset();
    currentPlayer = 0;
    if (bgDrawFadeIsLive()) {
        menuStateChange(MENU_STATE_2);
        bgDrawFadeIn();
    }
    menuStateChange(MENU_STATE_3);
    flagC50 = 1;
    windowCheckCursor(0xD6, 1);
    flagC50 = 0;
    value = windowGetValue(0xD6);
    if (value == -1 || value >= getQuantityAllPokemon()) {
        cstate.unk4 = 9;
        memset(cstate.saved, 0, 0x40);
        return;
    }
    selectIndex[currentPlayer] = value;
    cstate.unk4 = 8;
    memset(cstate.saved, 0, 0x40);
}

long _actionSelect2or3(u32 a, u32 b, u32 c) {
    u32 values[3] = { 0, 0, 0 };
    long menu;
    long result;
    values[0] = a;
    values[1] = b;
    values[2] = c;
    menuOpenCustom(0xD2, windowGetActiveID(), 0, 0, 0, 0);
    if (c == 0) {
        menu = 0x11A;
    } else {
        menu = 0x11B;
    }
    menuOpenCustom(menu, windowGetActiveID(), 0, 0, 0, 0);
    if (c == 0) {
        _menuSetMsg(menu, 0x8C3, a);
        _menuSetMsg(menu, 0x8C4, b);
    } else {
        _menuSetMsg(menu, 0x8CD, a);
        _menuSetMsg(menu, 0x8CC, b);
        _menuSetMsg(menu, 0x8CB, c);
    }
    windowCheckCursor(menu, 1);
    result = windowGetValue(menu);
    menuClose(menu);
    menuClose(0xD2);
    if (result == -1) {
        if (c == 0) {
            result = 1;
        } else {
            result = 2;
        }
    }
    return values[result];
}

bool _isTemochiPokemonCheck() {
    Hero *hero = Hero::getHeroPtr();
    long i = 0;
    long exchangeable = 0;
    long counts[8];
    memset(counts, 0, 0x20);
    do {
        Pokemon *p = hero->getPokemon(i);
        long state;
        if (_isPokemonExchangeAble(p, PLAYER_0)) {
            exchangeable++;
        }
        state = _getPokemonState(p, PLAYER_0);
        counts[state]++;
        if (!_isPokemonValid(p, PLAYER_0)) {
            break;
        }
        i++;
    } while (i < 6);
    if (i <= 1) {
        GSsndPlayNow(0x13);
        winMsgOpenWithSE(3, 0xC482, 1, 0, 2);
        winMsgClose(1);
        return false;
    }
    if (exchangeable == 0) {
        long msg = 0xC4A5;
        if (counts[3] != 0) {
            msg = 0xC483;
        } else if (counts[4] != 0) {
            msg = 0xC484;
        } else if (counts[2] != 0 || counts[1] != 0) {
            msg = 0xC4A7;
        } else if (counts[5] != 0 || counts[6] != 0) {
            msg = 0xC4AA;
        }
        GSsndPlayNow(0x13);
        winMsgOpenWithSE(3, msg, 1, 0, 2);
        winMsgClose(1);
        return false;
    }
    return true;
}

void CMenuPokemonChange::ctrlHook(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            switch (win->menu) {
            case 0xD4:
            case 0xD6:
                winSeqSetMenu(win->menu, 0x1BC);
                break;
            case 0xD5:
                break;
            }
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            win->step = 1;
        }
        break;
    }
}

void CMenuPokemonChange::bgDrawFadeIn(f32 duration) {
    tagWINDOW_WORK *win = windowSearchID(0xDF);
    if (win != 0) {
        f32 t = 0.0f;
        while (t < duration) {
            win->alpha = (u8)(255.0f * (1.0f - t / duration));
            GSthreadSwitch();
            t += timeGetLastFrameSec();
        }
        win->alpha = 0;
        menuCloseCustom(0xDF, 0, 1);
    }
}

void CMenuPokemonChange::bgDrawFadeOut() {
    f32 t;
    tagWINDOW_WORK *win;
    menuOpenCustom(0xDF, windowGetActiveID(), 0, 2, 0, 0);
    menuSetDisp(0xDF, 1);
    win = windowSearchID(0xDF);
    t = 0.0f;
    while (t < 0.3f) {
        win->alpha = (u8)(255.0f * (t / 0.3f));
        GSthreadSwitch();
        t += timeGetLastFrameSec();
    }
    win->alpha = 0xFF;
}

void CMenuPokemonChange::stateFunctionExChangeOK() {
    u32 id0;
    u32 id1;
    u32 nick0;
    u32 nick1;
    pokemonBiosSetFriend(getPokemonBySelect(selectIndex[0]), 0x46);
    pokemonBiosSetFriend(getPokemonBySelect(selectIndex[1]), 0x46);
    memoDataSet(0, getPokemonBySelect(selectIndex[0]));
    id0 = heroGetStatus(hero0, 1, 0);
    id1 = heroGetStatus(&hero1, 1, 0);
    nick0 = pokemonBiosGetNicknamePtr(getPokemonBySelect(selectIndex[0]));
    nick1 = pokemonBiosGetNicknamePtr(getPokemonBySelect(selectIndex[1]));
    msgctrlSetValue(0x4D, id0);
    msgctrlSetValue(0x57, id1);
    msgctrlSetValue(0x32, nick0);
    msgctrlSetValue(0x33, nick1);
    winMsgOpen(2, 0xC49C, 1, 0);
    winMsgClose(1);
    cstate.unk4 = 0x15;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionExChangeMain() {
    static Pokemon pokemon;
    Pokemon *pokemons[2];
    MenuItemSimple *item;
    long i;
    long j;
    pokemonInit(&pokemon);
    for (i = 0; i < 2; i++) {
        pokemons[i] = getPokemonBySelect(selectIndex[i]);
    }
    if (pokemons[0]->getDarkPokemon() != 0) {
        pokemons[0]->getDarkPokemon()->setPlace(place0, 0);
    }
    pokemonBiosCopy(&pokemon, pokemons[1]);
    pokemonBiosCopy(pokemons[1], pokemons[0]);
    pokemonBiosCopy(pokemons[0], &pokemon);
    bgDrawFadeIn(2.0f);
    _pokemonChangeFadeOut(0.0f);
    _pokemonChangeFadeIn(1.0f);
    cameraPlayAnime(floorGetCurrentGroupID(), 0xFCD1800, 0, 0.0f);
    GSthreadSwitch();
    GSsndPlayNow(0x462);
    floorMapSetDisp(1);
    scriptModelSetMotion(0xFCC1000, 0, 0, 0);
    _pokemonChangeFadeIn(3.0f);
    cameraWaitSyncAnime(1);
    _pokemonChangeFadeOut(0.7f);
    floorMapSetDisp(0);
    item = menuPtItemGetByMenuIdAndItemId(0xDE, 0x652, 0);
    for (j = 0; j < 2; j++) {
        menuModelInit(&models[j], item->width, item->height);
        menuModelLoadPokemon(&models[j], getPokemonBySelect(selectIndex[j]));
        menuModelCheck(&models[j], 1);
    }
    menuStateChange((enumMenuState)6);
    _pokemonChangeFadeIn(0.15f);
    cstate.unk4 = 0x14;
    memset(cstate.saved, 0, 0x40);
}

void CMenuPokemonChange::stateFunctionExChangeStart() {
    MenuItemSimple *item;
    long i;
    long j;
    u32 id0;
    u32 id1;
    u32 nick0;
    u32 nick1;
    item = menuPtItemGetByMenuIdAndItemId(0xDE, 0x652, 0);
    for (i = 0; i < 2; i++) {
        menuModelInit(&models[i], item->width, item->height);
        menuModelLoadPokemon(&models[i], getPokemonBySelect(selectIndex[i]));
        menuModelCheck(&models[i], 1);
    }
    menuStateChange((enumMenuState)6);
    bgDrawFadeIn();
    _menuWait(1.0f);
    id0 = heroGetStatus(hero0, 1, 0);
    id1 = heroGetStatus(&hero1, 1, 0);
    nick0 = pokemonBiosGetNicknamePtr(getPokemonBySelect(selectIndex[0]));
    nick1 = pokemonBiosGetNicknamePtr(getPokemonBySelect(selectIndex[1]));
    msgctrlSetValue(0x4D, id1);
    msgctrlSetValue(0x57, id0);
    msgctrlSetValue(0x32, nick0);
    msgctrlSetValue(0x33, nick1);
    winMsgOpen(2, 0xC49A, 1, 0);
    winMsgOpen(2, 0xC49B, 1, 0);
    winMsgClose(1);
    bgDrawFadeOut();
    for (j = 0; j < 2; j++) {
        menuModelFree(&models[j]);
        menuModelTerm(&models[j]);
    }
    menuStateChange(MENU_STATE_1);
    cstate.unk4 = 0x13;
    memset(cstate.saved, 0, 0x40);
}

MENU_MODEL::MENU_MODEL() {
}

Pokemon *_cbMenuPokemonStatus(Pokemon *p, MENU_POKEMON_CB_TYPE type, long player) {
    return MenuPokemonChange.pokemonStatusCallback(p, type, (enumPlayerIndex)player);
}

void CMenuPokemonChange::bgDrawFadeIn() {
    bgDrawFadeIn(0.3f);
}

bool CMenuPokemonChange::bgDrawFadeIsLive() {
    return windowSearchID(0xDF) ? true : false;
}

void CMenuPokemonChange::bgModelRelease() {
    scriptModelClose((void *)bgModelId);
}

}  // namespace

extern "C" s32 menuPokemonChangeCtrl(tagWINDOW_WORK *win) {
    MenuPokemonChange.ctrlHook(win);
    return 0;
}

extern "C" void menuPokemonChangeItemHook(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    MenuPokemonChange.selectItemHook(win, sprite);
}

extern "C" void menuPokemonChangeDraw(tagWINDOW_WORK *win) {
    MenuPokemonChange.selectDrawHook(win);
}

extern "C" void menuPokemonChangeExit(void) {
}

extern "C" void menuPokemonChangeMain(void) {
    MenuPokemonChange.main();
}

extern "C" void menuPokemonChangeInit(void) {
    floorMapSetDisp(0);
    scriptModelStopMotion(0xFCC1000);
}

extern "C" void menuPokemonChangeCursor(tagWINDOW_WORK *win) {
    if (!winSeqCheckMove(win->menu)) {
        PokemonChangeKeys *k1 = &winSysWork;
        PokemonChangeKeys *k2 = &winSysWork2;
        u16 hold1 = k1->hold;
        u16 hold2 = k2->hold;
        u16 any = hold1 | hold2;
        if ((any & 0xC) != 0 && (any & 3) != 0) {
            u16 rep1 = k1->repeat;
            u16 rep2 = k2->repeat;
            k1->hold = hold1 & 0xC;
            k1->repeat = rep1 & 0xC;
            k2->hold = hold2 & 0xC;
            k2->repeat = rep2 & 0xC;
            menuCursorNormal(win, 1);
            k1->hold = hold1 & 3;
            k1->repeat = rep1 & 3;
            k2->hold = hold2 & 3;
            k2->repeat = rep2 & 3;
            menuCursorNormal(win, 1);
            k1->hold = hold1;
            k1->repeat = rep1;
            k2->hold = hold2;
            k2->repeat = rep2;
        } else {
            menuCursorNormal(win, 1);
        }
    }
}

extern "C" void menuPokemonChange(void) {
    s32 group;
    if (_isTemochiPokemonCheck()) {
        group = GSfloorGetCurrentFloorGroupID();
        winMsgOpenWithSE(3, 0xC48E, 1, 0, 2);
        if (menuSubOpenYesNoField() == 0) {
            s32 nextFloor = floorGetNextFloorID();
            gamedatasaveSetStatus(0, 5, nextFloor);
            s32 result = memcardTaskCall(4, 2, 0);
            winMsgClose(1);
            if (result == 4) {
                GSfloorPush(0x394);
                floorWaitForChange();
            }
            return;
        }
    }
    winMsgClose(1);
    GSthreadUnblockGroup(group);
}

extern "C" u8 fn_80098B44(u8 mode, Pokemon *pokemon) {
    u16 *name = (u16 *)pokemonGetStatus(pokemon, 0, 0x77, 0);
    u32 len = GSmsgGetCharLength(name);
    u16 countA;
    u16 countB;
    u16 charA;
    u16 charB;
    u32 i;
    countB = 0;
    countA = 0;
    switch (mode) {
    case 0:
        charA = 0x2642;
        charB = 0x2640;
        break;
    case 1:
        charA = 0x2640;
        charB = 0x2642;
        break;
    default:
        return mode;
    }
    for (i = 0; i < len; i++) {
        if (charA == name[i]) {
            countA++;
        }
        if (charB == name[i]) {
            countB++;
        }
    }
    if (countB == 0 && countA != 0) {
        return 2;
    }
    return mode;
}

extern "C" {
s32 gbaCommandChangePokemon(s32,Pokemon*,s32,s32);
s32 gbaCommandChangePokemonIsPrepared(s32);
void gbaCommandSetKeyState(s32,s32);
void memcardSetupTask(s32,s32,s32);
u8 memcardCheckTaskWaitGBA();
void memcardUnlockWaitGBA(s32);
s32 memcardGetTaskResult();
void memcardFinalizeTask();
u32 HSD_Rand();
}
namespace {
#pragma push
#pragma opt_dead_assignments off
void CMenuPokemonChange::stateFunctionSaveReport() {
    CMenuPokemonChange *m;
    u8 unlocked,success;
    success=0;unlocked=0;
    winMsgOpen(2,0xC49D,1,1);
    s32 index;
    Pokemon* pokemon=getPokemonBySelect(selectIndex[1]);
    index=selectIndex[1];
    if(index>=getQuantityHeroPokemon(PLAYER_0))index-=getQuantityHeroPokemon(PLAYER_0);
    if(gbaCommandChangePokemon(2,pokemon,index,exchangeSeed)==0) {
        memcardSetupTask(8,2,0);
        s32 result;
        do {
            if(!unlocked && memcardCheckTaskWaitGBA()) {
                s32 prepared=gbaCommandChangePokemonIsPrepared(2);
                if(prepared>=0) {
                    if(prepared)memcardUnlockWaitGBA(0);
                    else memcardUnlockWaitGBA(1);
                    unlocked=1;
                }
            }
            GSthreadSwitch();
            result=memcardGetTaskResult();
        }while(result==0);
        gbaCommandSetKeyState(2,1);
        memcardFinalizeTask();
        if(result==4)success=1;
    }
    if(!unlocked || !success) {
        memcpy(savedataGetStatus(0,0),saveData,0x27FD0);
        GSsndPlayNow(0x13);
        winMsgOpen(2,0xC49E,1,0);
        winMsgClose(1);
        m=this;
        for(index=0;index<2;index++) {menuModelFree(&m->models[0]);menuModelTerm(&m->models[0]);m=(CMenuPokemonChange *)((u8 *)m+sizeof(MENU_MODEL));}
        cstate.unk4=3;
        memset(cstate.saved,0,0x40);
        return;
    }
    u32 low=HSD_Rand();
    u32 high=HSD_Rand()<<16;
    u32 combined=high|low;
    u32 wait=combined%60;
    u32 frames=wait;
    while(frames--)GSthreadSwitch();
    winMsgOpen(2,0xC4A0,1,0);
    winMsgClose(1);
    cstate.unk4=0x17;
    memset(cstate.saved,0,0x40);
}
#pragma pop
}

namespace {
void CMenuPokemonChange::setMenuByTbl(long* table) {
    s32 count=0;
    for(long* entry=table;*entry;) {entry++;count++;}
    u32 same=0;
    for(;same<8;same++) {
        if(!menuTbl[same] || menuTbl[same]!=table[same])break;
    }
    u32 first=same;
    s32 old;
    for(;(old=menuTbl[same]) && same<8;same++) {
        long* entry;
        u8 found=0;
        for(entry=table;*entry;entry++) {
            if(old==*entry){found=1;break;}
        }
        if(!found)menuCloseCustom(old,2,0);
    }
    u8 loaded=0;
    for(same=first;table[same] && same<8;same++) {
        oneMenuLoad(table[same]);
        loaded=1;
    }
    if(!loaded) {
        switch(table[count-1]) {case 0xD6:oneMenuLoad(table[count-1]);break;}
    }
    memset(menuTbl,0,0x20);
    memcpy(menuTbl,table,(count+1)*4);
}
}

extern "C" void* memcardMemFreeForSavedata(void*);
namespace {
void CMenuPokemonChange::loop() {
    u8* stateSaved=cstate.saved;
    for(;;) {
        cstate.update();
        switch(cstate.unk0) {
        case 1:cstate.unk4=5;memset(stateSaved,0,0x40);break;
        case 2:
            menuStateChange(MENU_STATE_2);bgDrawFadeIn();
            winMsgOpen(2,0xC4A2,1,0);winMsgClose(1);
            cstate.unk4=4;memset(stateSaved,0,0x40);break;
        case 3:
            menuStateChange(MENU_STATE_2);bgDrawFadeIn();
            winMsgOpen(2,0xC49F,1,0);winMsgClose(1);
            cstate.unk4=4;memset(stateSaved,0,0x40);break;
        case 4:saveData=memcardMemFreeForSavedata(saveData);return;
        case 5:stateFunctionCheckconnection();break;
        case 6:stateFunctionSelectPokemonStart();break;
        case 7:stateFunctionSelectPokemon1Main();break;
        case 8:stateFunctionSelectPokemon1Selected();break;
        case 9:stateFunctionSelectPokemon1Chanceld();break;
        case 10:stateFunctionSelectPokemon1CheckStatus();break;
        case 11:stateFunctionSelectPokemon1PokeExChange();break;
        case 12:stateFunctionSelectPokemon2Main();break;
        case 13:stateFunctionSelectPokemon2Selected();break;
        case 14:stateFunctionSelectPokemon2CheckStatus();break;
        case 15:stateFunctionSelectPokemon2PokeExChange();break;
        case 16:stateFunctionSelectPokemon2DecideAfterWait();break;
        case 17:stateFunctionConfirmExChange();break;
        case 18:stateFunctionExChangeStart();break;
        case 19:stateFunctionExChangeMain();break;
        case 20:stateFunctionExChangeOK();break;
        case 21:stateFunctionEvolution();break;
        case 22:stateFunctionSaveReport();break;
        case 23:stateFunctionCheckNext();break;
        }
    }
}
}

void menuPtWindowWorkDraw(tagWINDOW_WORK*);
void menuPtWindowWorkDraw(long);
tagSPRITE_WORK* menuPtSpriteWorkGetByItemID(long,u32,long);
void menuPtSpriteWorkSetSpriteId(tagSPRITE_WORK*,u32);
extern "C" {
void windowSetParam(tagWINDOW_WORK*,s32,s32);
u32 timeGetLastFrameTime();
}
namespace {
void CMenuPokemonChange::selectDrawHook(tagWINDOW_WORK*) {
    if(menuState) {
        tagWINDOW_WORK* win=windowSearchID(0xE1);
        if(win)menuPtWindowWorkDraw(win);
        win=windowSearchID(0xD4);
        if(win) {
            tagSPRITE_WORK* sprite=menuPtSpriteWorkGetByItemID(win->menu,0x60D,0);
            s16 x=win->x;
            win->x=x;
            menuPtSpriteWorkSetSpriteId(sprite,0x20F);
            windowSetParam(win,0,0);
            menuPtWindowWorkDraw(win);
            win->x=(s16)(_selectDisplay_2p_offset()-x);
            menuPtSpriteWorkSetSpriteId(sprite,0x20E);
            windowSetParam(win,0,1);
            menuPtWindowWorkDraw(win);
            win->x=x;
            menuPtWindowWorkDraw(0xD5);
        }
        win=windowSearchID(0xDD);
        if(win) {
            tagSPRITE_WORK* sprite=menuPtSpriteWorkGetByItemID(win->menu,0x63E,0);
            win->x=0;
            menuPtSpriteWorkSetSpriteId(sprite,0x20F);
            windowSetParam(win,0,0);
            menuPtWindowWorkDraw(win);
            win->x=_selectDisplay_2p_offset();
            menuPtSpriteWorkSetSpriteId(sprite,0x20E);
            windowSetParam(win,0,1);
            menuPtWindowWorkDraw(win);
        }
        win=windowSearchID(0xDE);
        if(win) {
            tagSPRITE_WORK* sprite=menuPtSpriteWorkGetByItemID(win->menu,0x650,0);
            win->x=0;
            menuPtSpriteWorkSetSpriteId(sprite,0x20F);
            windowSetParam(win,0,0);
            menuPtWindowWorkDraw(win);
            win->x=_selectDisplay_2p_offset();
            menuPtSpriteWorkSetSpriteId(sprite,0x20E);
            windowSetParam(win,0,1);
            menuPtWindowWorkDraw(win);
        }
        elapsed+=timeGetLastFrameTime();
    }
}
}

extern "C" {
u16 pokemonEvolutionCheck(Pokemon*,s32,s32,s32*,POKEMON_EVOLUTION_INFO*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
u32 menuFaceGetID(Pokemon*);
s8 menuFaceSearchEnable(u32);
}
namespace {
void CMenuPokemonChange::stateFunctionEvolution() {
    POKEMON_EVOLUTION_INFO info0;
    POKEMON_EVOLUTION_INFO info1;
    s32 auxiliary;
    u16 species0;
    u16 species1;
    u8 evolution=0;
    exchangeSeed=0;
    species0=pokemonEvolutionCheck(getPokemonBySelect(selectIndex[0]),2,0,&auxiliary,&info0);
    if(species0 && species0!=0xFFFF)evolution=1;
    species1=pokemonEvolutionCheck(getPokemonBySelect(selectIndex[1]),2,0,&auxiliary,&info1);
    if(species1 && species1!=0xFFFF) {
        evolution=1;
        exchangeSeed=pokemonBiosGetPokemonDataId(getPokemonBySelect(selectIndex[1]));
    }
    if(evolution) {
        _pokemonChangeFadeOut(0.3f);
        menuStateChange(MENU_STATE_0);
        for(s32 i=0;i<2;i++) {menuModelFree(&models[i]);menuModelTerm(&models[i]);}
        bgModelRelease();
        GSthreadSwitch();
        _pokemonChangeFadeIn(0.0f);
        _pokemonChangeEvolutionEffect(getPokemonBySelect(selectIndex[0]),MENU_POKEMONCHANGE_USERTYPE_1,species0,info0);
        _pokemonChangeEvolutionEffect(getPokemonBySelect(selectIndex[1]),MENU_POKEMONCHANGE_USERTYPE_0,species1,info1);
        _pokemonChangeFadeOut(0.0f);
        bgModelLoad();
        MenuItemSimple* item=menuPtItemGetByMenuIdAndItemId(0xDE,0x652,0);
        for(s32 i=0;i<2;i++) {
            menuModelInit(&models[i],item->width,item->height);
            menuModelLoadPokemon(&models[i],getPokemonBySelect(selectIndex[i]));
            menuModelCheck(&models[i],1);
        }
        menuStateChange(MENU_STATE_6);
        _pokemonChangeFadeIn(0.3f);
        for(s32 i=0;i<2;i++) {
            Pokemon* pokemon=getPokemonBySelect(selectIndex[i]);
            menuFaceLoad(pokemon,0,0);
            while(menuFaceSearchEnable(menuFaceGetID(pokemon))==0)GSthreadSwitch();
        }
    }
    cstate.unk4=0x16;
    memset(cstate.saved,0,0x40);
}
}
