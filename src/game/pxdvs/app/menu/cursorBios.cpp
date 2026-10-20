#include <global.h>
struct CursorPosition {s16 x,y;};
static CursorPosition _cursor[16];
static const CursorPosition invalidSetPosition = {-1, -1};
static const CursorPosition invalidGetPosition = {-1, -1};
extern "C" CursorPosition cursorBiosGetPos(u16 id){CursorPosition result=invalidGetPosition;if(id>=16)return result;result.x=_cursor[id].x;result.y=_cursor[id].y;return result;}
extern "C" CursorPosition cursorBiosSetPos(u16 id,const CursorPosition* position){CursorPosition result=invalidSetPosition;if(id>=16)return result;result.x=_cursor[id].x;result.y=_cursor[id].y;_cursor[id].x=position->x;_cursor[id].y=position->y;return result;}
extern "C" void cursorBiosInit(){for(s32 i=0;i<16;i++){_cursor[i].x=0;_cursor[i].y=0;}}
