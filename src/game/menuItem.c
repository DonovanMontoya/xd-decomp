#include <dolphin/types.h>

struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
typedef void (*MenuItemDraw)(struct tagWINDOW_WORK*, struct tagSPRITE_WORK*);

/* window.cpp consumes a 28-byte item, including the signed next-item index. */
typedef struct MenuItem {
    u8 flags, typeFlags, alpha;
    s16 spriteID;
    s16 x, y, width, height, cursorSpriteID;
    u32 message;
    MenuItemDraw draw;
    s16 nextItem;
} MenuItem;
typedef char MenuItemSize[sizeof(MenuItem) == 28 ? 1 : -1];

MenuItem _menu_item[] = {
    {0xC0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0x00, 0, 255, 96, 0, 0, 0, 0, 0, 0, 0, 2},
    {0x80, 0, 255, 0, 0, 0, 0, 0, 190, 60308, 0, 3},
    {0x80, 0, 255, 0, 0, 20, 0, 0, 190, 60309, 0, 4},
    {0xC0, 0, 255, 0, 0, 40, 0, 0, 190, 60310, 0, 5},
    {0xC0, 0, 255, 57, 0, 0, 640, 480, 0, 0, 0, 6},
    {0xC0, 0, 255, 58, 0, 0, 640, 480, 0, 0, 0, 7},
    {0x40, 0, 255, 834, 0, 0, 640, 480, 0, 0, 0, -1}
};
