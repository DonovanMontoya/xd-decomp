#ifndef PXDVS_APP_ITEM_ITEM_H
#define PXDVS_APP_ITEM_ITEM_H

#include <dolphin/types.h>

typedef struct ITEM {
    u16 itemDataId;
    u16 num;
} ITEM;

#ifdef __cplusplus
extern "C" {
#endif

void itemInitAry(ITEM* items, u16 count);
void itemReplace(ITEM* first, ITEM* second);
void itemSortAryByPriority(ITEM* items, u16 count, s32 type);
s32 itemGetQuantityInAry(ITEM* items, u16 count, u16 id, u16 max);

#ifdef __cplusplus
}
#endif

#endif
