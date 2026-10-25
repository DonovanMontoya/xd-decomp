#include <game/menuOrreColosseumLayout.hpp>

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_NONE,
    MENU_POKEMON_CB_PREV,
    MENU_POKEMON_CB_NEXT
};

extern "C" {
u8 GSfloorIsPop(void);
u8 GSfloorIsPush(void);
void GSfloorPush(s32);
void floorWaitForChange(void);
void fightFreeResourceID(s32, u32);
void fightReadResourceID(s32, u32);
void *fightEncountDataBiosGetPtr(u16);
u16 fightEncountDataBiosGetFightTrainerDataId(void *, s32);
void fightTrainerCreateFightTrainerDataIdToHero(u16, s32, Hero *, u16);
Hero *fightGetMenuCtrlHero(void);
Pokemon *heroBiosGetPokemonPtr(Hero *, u16);
s32 menuFaceGetID(Pokemon *);
u8 pokemonBiosGetLevel(Pokemon *);
u16 *pokemonBiosGetNicknamePtr(Pokemon *);
s32 pokemonGetSoubiItemDataId(Pokemon *);
s32 menuSubGetPokemonSexForFightDisp(Pokemon *);
Hero *savedataGetStatus(s32, s32);
void *memcpy(void *, const void *, u32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s32 menuSubOpenSelect2(s32, s32 *, s32, s32, s32, s32, s32, s32);
struct MenuOrreKey {
    u16 unk0;
    u16 unk2;
    u16 unk4;
};
struct MenuOrreItem {
    u8 reserved0[6];
    s16 x,y,unkA,height;
};
MenuOrreKey *windowGetKeyInfo(void);
u16 *heroBiosGetNamePtr(Hero *);
void msgctrlSetValue(s32, void *);
MenuOrreItem *menuItemBiosGetPtr(s32, s16);
u32 GSmsgGetRect(s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSmsgPrint2(s32, s32, s32, u32, s32);
s32 fightTrainerDB_GetName(u16);
void *GSmsgGetGSchar(u16);
void windowDrawSprite2(s16, s16, s16, s16, u32, tagWINDOW_WORK *, u16, s32, s32);
}

void *operator new(unsigned long);
void operator delete(void *);

static OrreHero _orreHero;
static u16 _deckNumber;
static u16 _fightresult;
static menuOrre *pOrre;
static s16 _loadFaceCount;

static Pokemon *_GetTemochiPokemonPtr(u16 index);

extern "C" {
void FlashSystemSetPlayFrameLabel(u32,const char *,const char *);
void FlashSystemSetNowFrame(u32,u32);
u32 FlashSystemGetFrameFromLabel(u32,const char *);
}

static inline void _setNowFrameLabel(s32 index)
{
    const char *labels[5]={"1_start","1_end","2_end","3_end","4_end"};
    FlashSystemSetNowFrame(0x1F5A3000,FlashSystemGetFrameFromLabel(0x1F5A3000,labels[index]));
}

static inline void _setPlayFrameLabel(u32 id, s16 index)
{
    const char *labels[5][2]={{"1_start","1_start"},{"1_start","1_end"},{"1_start","2_end"},{"1_start","3_end"},{"1_start","4_end"}};
    FlashSystemSetPlayFrameLabel(id,labels[index][0],labels[index][1]);
}

extern "C" {
void menuOrreExit(void)
{
    if (pOrre != 0) {
        pOrre->Release();
        if (pOrre != 0) {
            delete pOrre;
        }
        pOrre = 0;
    }
    fightFreeResourceID(0x842, 0x184C3400);
}

void menuOrreMain(void)
{
    if (pOrre != 0) {
        pOrre->Main();
    }
}

void menuOrreInit(void)
{
    if (GSfloorIsPop() == 0) {
        pOrre = new menuOrre;
        if (pOrre != 0) {
            pOrre->Init();
        }
    }
}

u16 menuOrreColosseumGetResult(void)
{
    return _fightresult;
}

void menuOrreColosseum(u16 deck)
{
    _deckNumber = deck;
    _fightresult = 0;
    GSfloorPush(0x38A);
    floorWaitForChange();
}

s32 menuOrreMenuHook(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    if (pOrre != 0) {
        return pOrre->Hook(window, sprite);
    }
    return 0;
}

void menuOrreCtrl(tagWINDOW_WORK *window)
{
    if (pOrre != 0) {
        pOrre->Ctrl(window);
    }
}

void menuOrreButton(tagWINDOW_WORK *window)
{
    if (pOrre != 0) {
        pOrre->Button(window);
    }
}
}

void menuOrre::Release()
{
}

s32 menuOrre::GetDeckPokemonFaceID(u16 index)
{
    return menuFaceGetID(GetDeckPokemonPtr(index));
}

u8 menuOrre::GetDeckPokemonLevel(u16 index)
{
    return pokemonBiosGetLevel(GetDeckPokemonPtr(index));
}

s32 menuOrre::GetDeckPokemonMochimono(u16 index)
{
    return pokemonGetSoubiItemDataId(GetDeckPokemonPtr(index));
}

u16 *menuOrre::GetDeckPokemonName(u16 index)
{
    return pokemonBiosGetNicknamePtr(GetDeckPokemonPtr(index));
}

Pokemon *menuOrre::GetDeckPokemonPtr(u16 index)
{
    return heroBiosGetPokemonPtr(GetHeroPtr(1), index);
}

s32 menuOrre::GetDeckPokemonSex(u16 index)
{
    return menuSubGetPokemonSexForFightDisp(GetDeckPokemonPtr(index));
}

s32 menuOrre::GetTemochiPokemonFaceID(u16 index)
{
    return menuFaceGetID(GetTemochiPokemonPtr(index));
}

u8 menuOrre::GetTemochiPokemonLevel(u16 index)
{
    return pokemonBiosGetLevel(GetTemochiPokemonPtr(index));
}

s32 menuOrre::GetTemochiPokemonMochimono(u16 index)
{
    return pokemonGetSoubiItemDataId(GetTemochiPokemonPtr(index));
}

u16 *menuOrre::GetTemochiPokemonName(u16 index)
{
    return pokemonBiosGetNicknamePtr(GetTemochiPokemonPtr(index));
}

Pokemon *menuOrre::GetTemochiPokemonPtr(u16 index)
{
    return heroBiosGetPokemonPtr(GetHeroPtr(0), index);
}

s32 menuOrre::GetTemochiPokemonSex(u16 index)
{
    return menuSubGetPokemonSexForFightDisp(GetTemochiPokemonPtr(index));
}

static Pokemon *_GetTemochiPokemonPtr(u16 index)
{
    if (pOrre != 0) {
        return pOrre->GetTemochiPokemonPtr(index);
    }
    return 0;
}

static Pokemon *_PokemonStatusDisp_CallBack(Pokemon *pokemon, MENU_POKEMON_CB_TYPE type, long arg)
{
    Pokemon *result = 0;
    switch (type) {
    case MENU_POKEMON_CB_PREV: {
        u32 cur = *(u16 *)arg;
        if (cur == 0) {
            return pokemon;
        }
        (*(u16 *)arg)--;
        result = _GetTemochiPokemonPtr(*(u16 *)arg);
        break;
    }
    case MENU_POKEMON_CB_NEXT: {
        u32 cur = *(u16 *)arg;
        if (cur == 5) {
            return pokemon;
        }
        (*(u16 *)arg)++;
        result = _GetTemochiPokemonPtr(*(u16 *)arg);
        break;
    }
    }
    return result;
}

void menuOrre::Init()
{
    isPush = GSfloorIsPush();
    InitSub();
}

void menuOrre::InitSub()
{
    fightReadResourceID(0x842, 0x184C3400);
    deckNumber = _deckNumber;
    trainerDataId = fightEncountDataBiosGetFightTrainerDataId(fightEncountDataBiosGetPtr(deckNumber), 1);
    fightTrainerCreateFightTrainerDataIdToHero(trainerDataId, 0, &_orreHero, deckNumber);
    Hero *ctrlHero = fightGetMenuCtrlHero();
    memcpy(ctrlHero, GetHeroPtr(0), sizeof(Hero));
    maxLevel = GetTemochiMaxPokemonLevel();
    CreatePokemonList();
}

Hero *menuOrre::GetHeroPtr(u8 flag)
{
    if (flag != 0) {
        return &_orreHero;
    }
    return savedataGetStatus(0, 2);
}

u8 menuOrre::GetTemochiMaxPokemonLevel()
{
    u8 max = 0;
    u16 i;
    for (i = 0; i < 6; i++) {
        u8 level = GetTemochiPokemonLevel(i);
        if (max < level) {
            max = level;
        }
    }
    return max;
}

bool menuOrre::ConfirmPokemon()
{
    bool ok;
    winMsgOpen(2, 0xFFFF - 0x752E, 1, 1);
    if (menuSubOpenYesNo(0, 0x40, 0xC8, 0) == 0) {
        ok = true;
    } else {
        ok = false;
    }
    winMsgClose(1);
    return ok;
}

s32 menuOrre::SelectPokemon(u16 index, bool flag)
{
    s32 a[3] = { 0x8ACE, 0x8ACF, 0x8AD0 };
    s32 b[3] = { 0x8AF1, 0x8ACF, 0x8AD0 };
    if (flag) {
        return menuSubOpenSelect2(0, b, 3, 0x15E, 0xB4, 0, 3, 0);
    }
    return menuSubOpenSelect2(0, a, 3, 0x15E, 0xB4, 0, 3, 0);
}

void menuOrre::CreatePokemonList()
{
    u16 n = 0;
    u16 i;
    u16 j;
    for (i = 0; i < 6; i++) {
        list[n++] = GetTemochiPokemonPtr(i);
    }
    for (j = 0; j < 6; j++) {
        list[n++] = GetDeckPokemonPtr(j);
    }
}

static s32 _loadPokemonCallBack(void *arg)
{
    s32 result = 0;
    if (pOrre != 0) {
        result = (s32)pOrre->list[*(u16 *)arg];
        (*(u16 *)arg)++;
    }
    return result;
}

void menuOrre::Button(tagWINDOW_WORK *window)
{
    MenuOrrePos pos = window->unk9C;
    unkE = pos.b;
    if (window != 0) {
        u16 key = windowGetKeyInfo()->unk4;
        if ((key & 0x10) != 0) {
            window->unkA4 = 1;
        }
        if (unk4 != 0 && (key & 0x20) != 0) {
            window->unkA4 = 1;
            window->unkA5 = 1;
        }
    }
}

void menuOrre::SetNumber(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    s16 ids[6] = { 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 };
    u16 nums[4] = { 0x31C, 0x31D, 0x31E, 0x31F };
    u16 i;
    u16 j;
    for (i = 0; i < 6; i++) {
        if (sprite->unk6 == ids[i]) {
            break;
        }
    }
    for (j = 0; j < 4; j++) {
        if (i == slots[j]) {
            windowDrawSprite2(0, 0, sprite->unk54, sprite->unk56, window->unk93 | 0xFFFFFF00, window, nums[j], 0,
                              winSpriteGetLayerID(window, sprite));
            return;
        }
    }
}

s32 menuOrre::Hook(tagWINDOW_WORK *window, tagSPRITE_WORK *sprite)
{
    switch (sprite->unk6) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        LeftPanel(window, sprite);
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        RightPanel(window, sprite);
        break;
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
        SetNumber(window, sprite);
        break;
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        ControlCursor(window, sprite);
        break;
    case 0x19: {
        MenuOrreItem *item;
        u32 rect;
        msgctrlSetValue(0x37, heroBiosGetNamePtr(GetHeroPtr(0)));
        item = menuItemBiosGetPtr(0xFD, sprite->unk6);
        rect = GSmsgGetRect(0x4276);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), (s16)(item->unkA - (rect >> 16)), 0, window->unk93 | 0xFFFFFF00, 0x4276);
        break;
    }
    case 0x1A:
        msgctrlSetValue(0x37, GSmsgGetGSchar(fightTrainerDB_GetName(trainerDataId)));
        GSmsgGetRect(0x4276);
        GSmsgPrint2(winSpriteGetLayerID(window, sprite), 0, 0, window->unk93 | 0xFFFFFF00, 0x4276);
        break;
    }
    return 0;
}

extern "C" {
void GSmsgPrintRect(s32,s32,s32,s32,s32,u32,s32);
void menuFaceDispFromID3(tagWINDOW_WORK *,tagSPRITE_WORK *,s32,s16 *,s16 *);
}

void menuOrre::LeftPanel(tagWINDOW_WORK *window,tagSPRITE_WORK *sprite) {
    s16 ids[6]={1,2,3,4,5,6};
    s16 position[2],size[2];
    u16 index=0;
    for(;index<6;++index)if(sprite->unk6==ids[index])break;
    MenuOrreItem *frame=menuItemBiosGetPtr(0xFD,sprite->unk6);
    windowDrawSprite2(0,0,frame->unkA,frame->height,window->unk93|0xFFFFFF00,window,0x31B,0,winSpriteGetLayerID(window,sprite));
    MenuOrreItem *name=menuItemBiosGetPtr(0xFD,37);
    u16 *nickname=GetTemochiPokemonName(index);
    msgctrlSetValue(0x37,nickname);
    GSmsgPrintRect(winSpriteGetLayerID(window,sprite),name->x,name->y,sprite->unk54,sprite->unk56,window->unk93|0xFFFFFF00,0x4277);
    MenuOrreItem *level=menuItemBiosGetPtr(0xFD,38);
    GSmsgPrint2(winSpriteGetLayerID(window,sprite),level->x,level->y+2,window->unk93|0xFFFFFF00,0x42C1);
    u32 rect=GSmsgGetRect(0x42C1);
    u8 pokemonLevel=GetTemochiPokemonLevel(index);
    msgctrlSetValue(0x5F,(void *)pokemonLevel);
    s32 layer=winSpriteGetLayerID(window,sprite);
    s32 x=level->x;
    x+=(s16)(rect>>16);
    x+=4;
    GSmsgPrintRect(layer,x,level->y+2,sprite->unk54,sprite->unk56,window->unk93|0xFFFFFF00,0x4352);
    u32 sex=GetTemochiPokemonSex(index);
    MenuOrreItem *gender=menuItemBiosGetPtr(0xFD,39);
    u32 message;
    switch((u8)sex) {case 0:message=0x9C5;break;case 1:message=0x9C6;break;case 2:default:message=0;break;}
    if(message!=0)GSmsgPrint2(winSpriteGetLayerID(window,sprite),gender->x+18,gender->y,window->unk93|0xFFFFFF00,message);
    if((u16)GetTemochiPokemonMochimono(index)!=0) {
        MenuOrreItem *item=menuItemBiosGetPtr(0xFD,36);
        windowDrawSprite2(item->x,item->y,item->unkA,item->height,window->unk93|0xFFFFFF00,window,0x14B,0,winSpriteGetLayerID(window,sprite));
    }
    MenuOrreItem *face=menuItemBiosGetPtr(0xFD,34);
    position[0]=face->x;position[1]=face->y;size[0]=face->unkA;size[1]=face->height;
    s32 faceId=GetTemochiPokemonFaceID(index);
    menuFaceDispFromID3(window,sprite,faceId,size,position);
}

void menuOrre::RightPanel(tagWINDOW_WORK *window,tagSPRITE_WORK *sprite) {
    s16 ids[6]={7,8,9,10,11,12};
    s16 position[2],size[2];
    u16 index=0;
    for(;index<6;++index)if(sprite->unk6==ids[index])break;
    MenuOrreItem *frame=menuItemBiosGetPtr(0xFD,sprite->unk6);
    windowDrawSprite2(0,0,frame->unkA,frame->height,window->unk93|0xFFFFFF00,window,0x31B,0,winSpriteGetLayerID(window,sprite));
    MenuOrreItem *name=menuItemBiosGetPtr(0xFD,31);
    u16 *nickname=GetDeckPokemonName(index);
    msgctrlSetValue(0x37,nickname);
    GSmsgPrintRect(winSpriteGetLayerID(window,sprite),name->x,name->y,sprite->unk54,sprite->unk56,window->unk93|0xFFFFFF00,0x4277);
    MenuOrreItem *level=menuItemBiosGetPtr(0xFD,32);
    GSmsgPrint2(winSpriteGetLayerID(window,sprite),level->x,level->y+2,window->unk93|0xFFFFFF00,0x42C1);
    u32 rect=GSmsgGetRect(0x42C1);
    u8 pokemonLevel=GetDeckPokemonLevel(index);
    msgctrlSetValue(0x5F,(void *)pokemonLevel);
    s32 layer=winSpriteGetLayerID(window,sprite);
    s32 x=level->x;
    x+=(s16)(rect>>16);
    x+=4;
    GSmsgPrintRect(layer,x,level->y+2,sprite->unk54,sprite->unk56,window->unk93|0xFFFFFF00,0x4352);
    u32 sex=GetDeckPokemonSex(index);
    MenuOrreItem *gender=menuItemBiosGetPtr(0xFD,33);
    u32 message;
    switch((u8)sex) {case 0:message=0x9C5;break;case 1:message=0x9C6;break;case 2:default:message=0;break;}
    if(message!=0)GSmsgPrint2(winSpriteGetLayerID(window,sprite),gender->x+18,gender->y,window->unk93|0xFFFFFF00,message);
    if((u16)GetDeckPokemonMochimono(index)!=0) {
        MenuOrreItem *item=menuItemBiosGetPtr(0xFD,30);
        windowDrawSprite2(item->x,item->y,item->unkA,item->height,window->unk93|0xFFFFFF00,window,0x14B,0,winSpriteGetLayerID(window,sprite));
    }
    MenuOrreItem *face=menuItemBiosGetPtr(0xFD,28);
    position[0]=face->x;position[1]=face->y;size[0]=face->unkA;size[1]=face->height;
    s32 faceId=GetDeckPokemonFaceID(index);
    menuFaceDispFromID3(window,sprite,faceId,size,position);
}
extern "C" {
s32 windowGetActiveID();
tagWINDOW_WORK *windowSearchID(s32);
void winSpriteSetDisp(tagSPRITE_WORK *,u8);
u32 FlashSystemGetEndFrame(u32);
u32 FlashSystemGetNowFrame(u32);
void FlashSystemSetPlayFrameLabel(u32,const char *,const char *);
void winSeqSetMenu(s32,u32);
s32 HSD_Rand();
f32 timeGetLastFrameSec();
}
extern "C" double sin(double);
void menuOrre::ControlCursor(tagWINDOW_WORK *window,tagSPRITE_WORK *sprite) {
    MenuOrrePos pos=window->unk9C;
    s32 ids[6]={13,14,15,16,17,18};
    s16 i=0;
    for(;i<6;++i)if(sprite->unk6==ids[i])break;
    if(i==pos.b) {
        if(window==windowSearchID(windowGetActiveID())) {
            s32 frame=unk10%60;
            sprite->color.value=0xFFFFFFFF;
            if(frame<30) {
                sprite->color.channels.alpha-=(u8)(128.0f*(f32)sin(3.14f*((f32)frame/30.0f)));
            }
        } else sprite->color.channels.alpha=255;
        winSpriteSetDisp(sprite,1);
        return;
    }
    winSpriteSetDisp(sprite,0);
}
void menuOrre::Ctrl(tagWINDOW_WORK *window) {
    switch(window->phase) {
    case 0:
        if(window->step==0) {winSeqSetMenu(window->menu,0x24);window->step=1;}
        break;
    case 2:
        if(unk16<4) {
            u32 end=FlashSystemGetEndFrame(0x1F5B3000);
            u8 finished;
            if(FlashSystemGetNowFrame(0x1F5B3000)>=end)finished=1;else finished=0;
            if(finished!=0) {
                unk18-=timeGetLastFrameSec();
                if(unk18<=0.0f) {
                    u16 random=HSD_Rand();
                    f32 delay=50.0f+(f32)(random%50);
                    unk18=delay/100.0f;
                    _setPlayFrameLabel(0x1F5B3000,++unk16);
                }
            }
        }
        break;
    case 3:
        if(window->step==0)window->step=1;
        break;
    }
    unk10=(s32)(60.0f*timeGetLastFrameSec()+(f32)unk10)%1000;
}
extern "C" {
void menuFaceLoad(u32,s32 (*)(void *),void *);
void menuOpen(s32,s32);
void GSthreadSwitch();
u8 FlashSystemIsLastFrame(u32);
s32 menuOpenCustom(s32,s32,...);
void menuClose(s32);
void menuCloseSync(s32,s32);
void fadeSet(s32,f32);
void menuPokemonStatusOpenFromPokemonChange(Pokemon *,Pokemon *(*)(Pokemon *,MENU_POKEMON_CB_TYPE,long),long);
u8 menuFaceCheckLoading();
void pokemonInit(Pokemon *);
void pokemonBiosCopy(Pokemon *,Pokemon *);
void fightSetMenuCtrlHero(Hero *);
u16 fightEncount(u16);
void GSfloorPop();
}
static inline bool _checkSelected(menuOrre *orre, u16 id)
{
    for (u16 i = 0; i < 4; ++i) {
        if (orre->slots[i] == (s16)id) return true;
    }
    return false;
}
static inline u8 _addSelectedPokemon(menuOrre *orre, u16 id)
{
    u8 full = 0;
    orre->slots[orre->unk4++] = id;
    if (orre->unk4 >= 4) full = 1;
    _setPlayFrameLabel(0x1F5A3000, orre->unk4);
    return full;
}

static inline u8 _removeLastSelectedPokemon(menuOrre *orre)
{
    u8 removed;
    if (orre->unk4 != 0) {
        --orre->unk4;
        orre->slots[orre->unk4] = -1;
        _setNowFrameLabel(orre->unk4);
        _setPlayFrameLabel(0x1F5A3000, orre->unk4);
        removed = 1;
    } else removed = 0;
    return removed;
}

static inline Hero *_clearBattlePokemon()
{
    Hero *hero = fightGetMenuCtrlHero();
    for (u16 i = 0; i < 6; ++i) {
        pokemonInit(heroBiosGetPokemonPtr(hero, i));
    }
    return hero;
}

void menuOrre::Main() {
    _loadFaceCount=0;
    u8 battle=1;
    menuFaceLoad(0,_loadPokemonCallBack,&_loadFaceCount);menuOpen(0xFF,0);
    do {GSthreadSwitch();}while(FlashSystemIsLastFrame(0x1F5C3000)==0);
    _setPlayFrameLabel(0x1F5B3000,0);
    for(;;) {
        unk18=1.0f;
        u8 selecting=1;
        _setPlayFrameLabel(0x1F5A3000,0);
        do {
            s32 cursor=unkE;
            if(menuOpenCustom(0xFD,windowGetActiveID(),&cursor,0,1,0)>=0) {
                bool selected=_checkSelected(this,unkE);
                switch(SelectPokemon(unkE,selected)) {
                case 0:
                    if(selected!=0) {
                        u8 removed;
                        u16 id=unkE;
                        if(unk4!=0) {
                            u16 i=0;
                            for(;i<4;++i)if(slots[i]==id)break;
                            --unk4;
                            for(;i<3;++i)slots[i]=slots[i+1];
                            _setNowFrameLabel(unk4);
                            _setPlayFrameLabel(0x1F5A3000,unk4);
                            removed=1;
                        } else removed=0;
                        battle=removed;
                    } else {
                        u8 full = _addSelectedPokemon(this, unkE);
                        if(full==1)selecting=0;
                    }
                    break;
                case 1:
                    menuPokemonStatusOpenFromPokemonChange(GetTemochiPokemonPtr(unkE),_PokemonStatusDisp_CallBack,(long)&unkE);
                    fadeSet(2,0.5f);
                    break;
                case 2:
                    break;
                }
            } else {
                u8 removed = _removeLastSelectedPokemon(this);
                battle=removed;
                if(removed==0)selecting=0;
            }
        }while(selecting!=0);
        if(battle==0) {menuClose(0xFD);break;}
        else {
            u8 finished;
            do {
                GSthreadSwitch();
                u32 end=FlashSystemGetEndFrame(0x1F5A3000);
                if(FlashSystemGetNowFrame(0x1F5A3000)>=end)finished=1;else finished=0;
            }while(finished==0);
            if(ConfirmPokemon()==0) {
                unk4=0;slots[0]=-1;slots[1]=-1;slots[2]=-1;slots[3]=-1;
                continue;
            }
        }
        break;
    }
    if(battle==1) {
        while(menuFaceCheckLoading()!=0)GSthreadSwitch();
        u8 finished;
        do {
            GSthreadSwitch();
            u32 end=FlashSystemGetEndFrame(0x1F5B3000);
            if(FlashSystemGetNowFrame(0x1F5B3000)>=end)finished=1;else finished=0;
        }while(finished==0);
        Hero *hero = _clearBattlePokemon();
        for(u16 i=0;i<4;++i) {
            pokemonBiosCopy(heroBiosGetPokemonPtr(hero,i),GetTemochiPokemonPtr(slots[i]));
        }
        fightSetMenuCtrlHero(fightGetMenuCtrlHero());
        _fightresult=fightEncount(deckNumber);
    }
    menuCloseSync(0xFD,1);menuClose(0xFF);menuCloseSync(0xFF,1);
    if(isPush!=0)GSfloorPop();
}
