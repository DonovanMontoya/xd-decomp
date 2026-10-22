#include <game/menuPcBoxPokemonLayout.hpp>
#include <libc/string.h>
struct InputNumberArg {s32 current,max,min,original;};
static InputNumberArg _inputnumberarg;
static s32 _DrawSelectOffset=12,_addwidth=8,_cursorOffset=5,_lsizecursorYoffset=2,_backWidth=5;
extern "C" {void menuClose(s32);void menuCloseSync(s32,s32);s32 menuOpenCustom(s32,s32,s32,s32,s32,s32,...);s32 windowGetActiveID();void msgctrlSetValue(s32,s32);s32 esabaGetEsaItemNum();u16 *windowGetKeyInfo();u32 windowGetKeyRepeat();void winSeqSetMenu(s32,s32);void menuSubCursorAnimeMain();void menuSubCursorAnimeStart();u8 menuCursorCmp(s32*,s32*,s32);u8 menuDataBiosGetDispMax(s32);u32 windowGetParam(tagWINDOW_WORK*,s32);void windowSetParam(tagWINDOW_WORK*,s32,s32);void *windowAllocMemory(tagWINDOW_WORK*,s32);s32 *windowGetAllocPtr(tagWINDOW_WORK*);s32 *windowGetFreeWork(tagWINDOW_WORK*);void menuSetStatus(s32,s32);u8 winSeqIsCheck(s32,s32);}
extern "C" void menuPaneInputNumberClose(){menuClose(0xB9);menuCloseSync(0xB9,1);}
static s32 _menuPanelInputNumber(short,short,long initial,long*,long min,long max,bool close){_inputnumberarg.current=initial;_inputnumberarg.max=max;_inputnumberarg.min=min;_inputnumberarg.original=initial;s32 result=menuOpenCustom(0xB9,windowGetActiveID(),0,0,1,1,&_inputnumberarg);if(result>=0)result=_inputnumberarg.current;if(close)menuPaneInputNumberClose();return result;}
extern "C" s32 menuPanelInputNumber(s32 initial,s32 *result,s32 min,s32 max,bool close){s32 value=_menuPanelInputNumber(0,0,initial,result,min,max,close);if(value>=0){*result=value;return 1;}*result=initial;return 0;}
extern "C" void menuPanelInputNumberHook(tagWINDOW_WORK *w,tagSPRITE_WORK *s){InputNumberArg *p=(InputNumberArg*)w->parameters[0];switch(s->id){case 0x504:msgctrlSetValue(0x34,p->current/10);return;case 0x503:msgctrlSetValue(0x34,p->current%10);return;case 0x511:{msgctrlSetValue(0x34,p->original-p->current+esabaGetEsaItemNum());return;}}}
extern "C" void menuPanelInputNumberCursor(tagWINDOW_WORK *w){windowGetKeyInfo();InputNumberArg *p=(InputNumberArg*)w->parameters[0];u16 keys=windowGetKeyRepeat();if(keys&1){if(p->current<p->max)p->current++;}else if(keys&2){if(p->current>p->min)p->current--;}}
extern "C" void menuPanelInputNumberCtrl(tagWINDOW_WORK *w){switch(w->phase){case 0:if(!w->step){winSeqSetMenu(w->menu,0x24);w->step=1;}return;case 3:if(!w->step){winSeqSetMenu(w->menu,0x17B);w->step=1;}break;}}
extern "C" s32 menuPanelCursorSelect(tagWINDOW_WORK *w){u32 keys=windowGetKeyInfo()[3];keys|=windowGetKeyRepeat();s8 count=windowGetParam(w,2);s8 visible=menuDataBiosGetDispMax(w->menu);u32 less=visible<count;if(less)count=visible;if(!less)visible=count;struct S {s16 first,selected;}; S next,old;u16 pad=keys;next.first=w->first;next.selected=w->selected;old.first=w->first;old.selected=w->selected;if(pad&1)next.selected--;else if(pad&2)next.selected++;if(next.selected<0){next.first+=next.selected;next.selected=0;if(next.first<0){next.selected=(s8)(visible-1);next.first=(s8)(count-visible);}}else if(next.selected>=visible){s8 end=visible-1;next.first+=next.selected-end;next.selected=end;if(next.first+end>=count){next.first=0;next.selected=0;}}s32 previous=*(s32*)&old;s32 cursor=*(s32*)&next;if(menuCursorCmp(&previous,&cursor,cursor))menuSubCursorAnimeStart();w->first=next.first;w->selected=next.selected;w->value=next.first+next.selected;return 0;}

extern "C" s32 menuPanelCtrlSelect2(tagWINDOW_WORK *w){menuSubCursorAnimeMain();switch(w->phase){case 5:break;case 0:if(!w->step){s32 size;void *source=(void*)windowGetParam(w,1);s32 count=windowGetParam(w,2);void *dest=windowAllocMemory(w,size=count*4);if(dest)memcpy(dest,source,size);u8 enabled=(u32)(windowGetParam(w,5)!=0);if(enabled==0)menuSetStatus(w->menu,8);winSeqSetMenu(w->menu,0x24);w->step=1;}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x17B);w->step=1;}break;}return 0;}
extern "C" s32 menuPanelCtrlSelect(tagWINDOW_WORK *w){menuSubCursorAnimeMain();switch(w->phase){case 5:break;case 0:if(!w->step){s32 size;void *source=(void*)windowGetParam(w,1);s32 count=windowGetParam(w,2);void *dest=windowAllocMemory(w,size=count*4);if(dest)memcpy(dest,source,size);winSeqSetMenu(w->menu,0x24);w->step=1;}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x17B);w->step=1;}break;}return 0;}
extern "C" s32 menuPanelCtrlLvUp(tagWINDOW_WORK *w){u8 open=0;switch(w->phase){case 5:break;case 0:if(!w->step)open=1;if(winSeqIsCheck(w->menu,0x2C)==1)open=1;if(open){winSeqSetMenu(w->menu,0x28);w->step=1;}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x2C);w->step=1;}break;}return 0;}
extern "C" {u32 GSmsgGetRect(u32);void GSmsgPrint2(s32,s32,s32,u32,u32);}
static void _menuPanelDrawDigit(tagWINDOW_WORK *w,tagSPRITE_WORK *s,long value,bool sign){if(sign){s16 r=GSmsgGetRect(0x42CD)>>16;GSmsgPrint2(w->layer,(s->width-48)-r,0,w->alpha|0xFFFFFF00,0x42CD);}msgctrlSetValue(0x34,value);s16 r=GSmsgGetRect(0x426E)>>16;GSmsgPrint2(w->layer,s->width-r,0,w->alpha|0xFFFFFF00,0x426E);}

extern "C" {void menuSubDrawNormalWindow2(s32,s32,s32,s32,s32,u8);void menuSubDrawMsgWindow2(s32,s32,s32,s32,s32,u8,s32);}
struct LevelChanges {bool positive;u8 pad;s16 value[6];};
extern "C" s32 menuPanelDrawLvUpItem(tagWINDOW_WORK *w,tagSPRITE_WORK *s){LevelChanges *changes=(LevelChanges*)windowGetParam(w,0);s16 id=s->id;switch(id){case 0x1C5:if(w->menu==0x29)menuSubDrawNormalWindow2(w->layer,0,0,s->width,s->height,w->alpha);else menuSubDrawMsgWindow2(w->layer,0,0,s->width,s->height,w->alpha,1);break;case 0x1C6:_menuPanelDrawDigit(w,s,changes->value[0],changes->positive);break;case 0x1C7:_menuPanelDrawDigit(w,s,changes->value[1],changes->positive);break;case 0x1C8:_menuPanelDrawDigit(w,s,changes->value[2],changes->positive);break;case 0x1C9:_menuPanelDrawDigit(w,s,changes->value[3],changes->positive);break;case 0x1CA:_menuPanelDrawDigit(w,s,changes->value[4],changes->positive);break;case 0x1CB:_menuPanelDrawDigit(w,s,changes->value[5],changes->positive);break;}return 0;}

extern "C" {
void menuSubCursorAnimeValGet(f32*, s32*);
void menuSubDrawCursorBack(s32,s32,s32,s32,s32,u8,s32);
void menuSubDrawSimpleWindow(s32,s32,s32,s32,s32);
void windowDrawSpriteCursor(s16,s16,u32,tagWINDOW_WORK*,s32,s32,s32,f32*,s32);

s32 menuPanelDrawSelect(tagWINDOW_WORK* window) {
    f32 animation[2];
    s32 animationColor;
    s32 height, width;
    u8 style;
    u32* messages;
    s32 count, maxHeight, offset;
    offset = _DrawSelectOffset;
    height = 0;
    width = 0;
    maxHeight = 0;
    style = windowGetParam(window, 0);
    messages = (u32*)windowGetAllocPtr(window);
    count = (s8)windowGetParam(window, 2);
    u8 visible = menuDataBiosGetDispMax(window->menu);
    if (count > visible) count = visible;
    u32* message = messages;
    for (s32 i = 0; i < count; i++, message++) {
        u32 rect = GSmsgGetRect(*message);
        if (width < (s32)(rect >> 16)) width = rect >> 16;
        s32 rowHeight = (u16)rect;
        if (maxHeight < rowHeight) maxHeight = rowHeight;
        height = rowHeight + (offset + height);
    }
    height -= offset;
    width = width + 26 + _addwidth;
    switch (style) {
    case 0: menuSubDrawNormalWindow2(window->layer,0,0,width,height,window->alpha); break;
    case 1: menuSubDrawMsgWindow2(window->layer,0,0,width,height,window->alpha,1); break;
    case 0x7F: menuSubDrawSimpleWindow(window->layer,0,0,width,height-2); break;
    }
    u32* backMessage = messages;
    s32 y = 1;
    for (s32 i = 0; i < count; i++, backMessage++) {
        s32 step;
        if (*backMessage) step = offset + (u16)GSmsgGetRect(*backMessage);
        else step = 20;
        if (window->selected == i) {
            if (maxHeight >= 20)
                menuSubDrawCursorBack(window->layer,_cursorOffset-5,(y+_lsizecursorYoffset)-7,width+_backWidth,step,window->alpha,0);
            else
                menuSubDrawCursorBack(window->layer,_cursorOffset-6,y-6,width+_backWidth,step,window->alpha,1);
        }
        y += step;
    }
    u32* textMessage = messages;
    s16 textY = 1;
    for (s32 i = 0; i < count; i++, textMessage++) {
        s32 step;
        if (*textMessage) {
            step = offset + (u16)GSmsgGetRect(*textMessage);
            GSmsgPrint2(window->layer,26,textY,window->alpha | 0xFFFFFF00,*textMessage);
        } else step = 20;
        menuSubCursorAnimeValGet(animation,&animationColor);
        if (window->selected == i) {
            if (maxHeight >= 20)
                windowDrawSpriteCursor((s16)_cursorOffset,(s16)(textY+_lsizecursorYoffset),window->alpha|0xFFFFFF00,window,0x7D,0,window->layer,animation,animationColor);
            else
                windowDrawSpriteCursor((s16)_cursorOffset,textY,window->alpha|0xFFFFFF00,window,0xC2,0,window->layer,animation,animationColor);
        }
        textY += step;
    }
    return 0;
}
}

extern "C" s32 menuPanelCursorSelect2(tagWINDOW_WORK* window) {
    struct Pair {s16 first,selected;};
    s8 count;
    s8 visible;
    u32 keys;
    u8 wrap;
    Pair next, old;
    s32 previous;
    s32 cursor;
    s8 end;
    keys = windowGetKeyInfo()[3];
    keys = keys | windowGetKeyRepeat();
    count = windowGetParam(window,2);
    visible = windowGetParam(window,3);
    wrap = (u32)(windowGetParam(window,4) != 0);
    if (count < visible) visible = count;
    next.first = window->first;
    next.selected = window->selected;
    old.first = window->first;
    old.selected = window->selected;

    if ((u16)keys & 1) next.selected--;
    else if ((u16)keys & 2) next.selected++;
    if (next.selected < 0) {
        next.first += next.selected;
        next.selected = 0;
        if (wrap) {
            if (next.first < 0) {
                next.selected = (s8)(visible-1);
                next.first = (s8)(count-visible);
            }
        } else if (next.first < 0) {
            next.selected = 0;
            next.first = 0;
        }
    } else if (next.selected >= visible) {
        end = visible - 1;
        next.first += next.selected - end;
        next.selected = end;
        if (wrap) {
            if (next.first + end >= count) {
                next.first = 0;
                next.selected = 0;
            }
        } else if (next.first + end >= count) {
            next.selected = end;
            next.first = (s8)(count-visible);
        }
    }

    previous = *(s32*)&old;
    cursor = *(s32*)&next;
    if (menuCursorCmp(&previous,&cursor,cursor)) menuSubCursorAnimeStart();
    window->first = next.first;
    window->selected = next.selected;
    return 0;
}

extern "C" s32 menuPanelCursorDecimalInput(tagWINDOW_WORK* window) {
    s32* cursor=windowGetFreeWork(window);
    s32 delta=0;
    s32 digits,base;
    s32 value=windowGetParam(window,0);
    s32 mode=windowGetParam(window,1);
    if(mode==2){digits=8;base=16;}else{digits=10;base=10;}
    u16 keys=windowGetKeyInfo()[3];
    if(keys&8)(*cursor)--;
    else if(keys&4)(*cursor)++;
    if(*cursor<0){value=0;*cursor=0;}
    if(*cursor>=digits)*cursor=digits-1;
    if(keys&1){delta=1;for(s32 i=0;i<*cursor;i++)delta*=base;}
    else if(keys&2){delta=-1;for(s32 i=0;i<*cursor;i++)delta*=base;}
    s64 next;
    if(mode==0){
        next=(s64)value+delta;
        if(next<(-2147483647LL-1))next=(-2147483647LL-1);
        if(next>2147483647LL)next=2147483647LL;
    }else{
        next=(s64)(u32)value+delta;
        if(next<0)next=0;
        if(next>4294967295LL)next=4294967295LL;
    }
    s32 result=next & 0xFFFFFFFFLL;
    window->value=result;
    windowSetParam(window,0,result);
    return 0;
}

struct PanelSprite {s16 x,y,width;};
extern "C" {
void* menuSpriteBiosGetPtr(s32);
PanelSprite* menuSpriteBiosGetValPtr(void*);
void windowDrawSprite(s16,s16,tagWINDOW_WORK*,s32,s32,s32);
s32 menuPanelDrawSelect2(tagWINDOW_WORK* window) {
    f32 animation[2];
    s32 animationColor;
    struct Pair {s16 first, selected;} scroll = *(Pair*)&window->first;
    s32 height, width;
    u8 style;
    u32* messages;
    s32 count, maxHeight, offset;
    offset = _DrawSelectOffset;
    height = 0;
    width = 0;
    maxHeight = 0;
    style = windowGetParam(window, 0);
    messages = (u32*)windowGetAllocPtr(window);
    count = (s8)windowGetParam(window, 2);
    s32 visible = count;
    s32 requestedVisible = windowGetParam(window, 3);
    if (visible > requestedVisible) visible = requestedVisible;
    u32* message = messages;
    for (s32 i = 0; i < count; i++, message++) {
        u32 rect = GSmsgGetRect(*message);
        if (width < (s32)(rect >> 16)) width = rect >> 16;
        s32 rowHeight = (u16)rect;
        if (maxHeight < rowHeight) maxHeight = rowHeight;
        if (i < visible) {height += offset; height += rowHeight;}
    }
    height -= offset;
    width += 26;
    width += _addwidth;
    switch (style) {
    case 0: menuSubDrawNormalWindow2(window->layer,0,0,width+2,height,window->alpha); break;
    case 1: menuSubDrawMsgWindow2(window->layer,0,0,width+2,height,window->alpha,1); break;
    case 0x7F: menuSubDrawSimpleWindow(window->layer,0,0,width+2,height-2); break;
    }
    PanelSprite* sprite = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x237));
    if (count > requestedVisible && scroll.first != 0)
        windowDrawSprite((s16)(width/2-sprite->width/2),-18,window,0x237,2,window->layer);
    if (count > requestedVisible && requestedVisible != count-scroll.first)
        windowDrawSprite((s16)(width/2-sprite->width/2),(s16)(height+10),window,0x237,0,window->layer);
    u32* backMessage = messages;
    s32 y = 1;
    for (s32 i = 0; i < visible; i++, backMessage++) {
        s32 step;
        if (*backMessage) step = offset + (u16)GSmsgGetRect(messages[scroll.first+i]);
        else step = 20;
        if (window->selected == i) {
            if (maxHeight >= 20)
                menuSubDrawCursorBack(window->layer,_cursorOffset-5,(y+_lsizecursorYoffset)-7,width+_backWidth,step,window->alpha,0);
            else
                menuSubDrawCursorBack(window->layer,_cursorOffset-6,y-6,width+_backWidth,step,window->alpha,1);
        }
        y += step;
    }
    u32* textMessage = messages;
    s32 textY = 1;
    for (s32 i = 0; i < visible; i++, textMessage++) {
        s32 step;
        if (*textMessage) {
            step = offset + (u16)GSmsgGetRect(messages[scroll.first+i]);
            GSmsgPrint2(window->layer,26,textY,window->alpha | 0xFFFFFF00,messages[scroll.first+i]);
        } else step = 20;
        menuSubCursorAnimeValGet(animation,&animationColor);
        if (window->selected == i) {
            if (maxHeight >= 20)
                windowDrawSpriteCursor((s16)_cursorOffset,(s16)(textY+_lsizecursorYoffset),window->alpha|0xFFFFFF00,window,0x7D,0,window->layer,animation,animationColor);
            else
                windowDrawSpriteCursor((s16)_cursorOffset,textY,window->alpha|0xFFFFFF00,window,0xC2,0,window->layer,animation,animationColor);
        }
        textY += step;
    }
    return 0;
}
}
