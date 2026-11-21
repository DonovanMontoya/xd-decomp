#include <game/pxdvs/app/floor/floorBiosPrivate.hpp>
extern "C" {
extern FloorTreasure *floor_tresure_list;
extern GSfloor_dd_ *floordata;
extern u32 *floordata_number;
u16 fightGetFightEncountDataId();
s32 pokecoloGetRomVersion();
s32 pokecoloGetLanguage();
u32 floorTresureGetResID(u16 index) {
    s32 count = 0;
    GSfloor_dd_ *floor = floorDataBiosGetCurrentPtr();
    FloorTreasure *treasure = floor_tresure_list;
    for (u32 i = 0; i < index; ++i, ++treasure) if (treasure->floorID == floor->floorID) ++count;
    return count | 0x7FFF0000;
}
s32 floorDataBiosModelIDGetFogState(u32 modelID) {
    GSfloor_dd_ *floor = floorDataBiosGetCurrentPtr();
    if (modelID == 0) return 1;
    if (floor == 0) return 1;
    FloorRenderData **table = floor->render;
    if (table == 0) return 1;
    FloorRenderData *render = *table;
    if (render->noFogModelIDs[0] == modelID) return 0;
    if (render->noFogModelIDs[1] == modelID) return 0;
    return render->noFogModelIDs[2] == modelID ? 0 : 1;
}
s32 floorDataBiosGetSecondaryRenderNum(GSfloor_dd_ *floor) {
    s32 count = 0;
    if (floor == 0) return 0;
    FloorRenderData **table = floor->render;
    if (table == 0) return 0;
    FloorRenderData *render = *table;
    if (render == 0) return 0;
    if (render->secondaryRenderIDs[0]) count = 1;
    if (render->secondaryRenderIDs[1]) ++count;
    if (render->secondaryRenderIDs[2]) ++count;
    return count;
}
u32 floorDataBiosGetSecondaryRenderID(GSfloor_dd_ *floor, u32 index) {
    if (floor == 0) return 0;
    FloorRenderData **table = floor->render;
    if (table == 0) return 0;
    if (index >= 3) return 0;
    FloorRenderData *render = *table;
    if (render == 0) return 0;
    return render->secondaryRenderIDs[index];
}
s32 floorDataBiosGetShadowReciveNum(GSfloor_dd_ *floor) {
    s32 count = 0;
    if (floor == 0) return 0;
    FloorRenderData **table = floor->render;
    if (table == 0) return 0;
    FloorRenderData *render = *table;
    if (render == 0) return 0;
    if (render->shadowReceiverIDs[0]) count = 1;
    if (render->shadowReceiverIDs[1]) ++count;
    if (render->shadowReceiverIDs[2]) ++count;
    if (render->shadowReceiverIDs[3]) ++count;
    if (render->shadowReceiverIDs[4]) ++count;
    if (render->shadowReceiverIDs[5]) ++count;
    if (render->shadowReceiverIDs[6]) ++count;
    if (render->shadowReceiverIDs[7]) ++count;
    return count;
}
u32 floorDataBiosGetShadowReciveID(GSfloor_dd_ *floor, u32 index) {
    if (floor == 0) return 0;
    FloorRenderData **table = floor->render;
    if (table == 0) return 0;
    if (index >= 8) return 0;
    FloorRenderData *render = *table;
    if (render == 0) return 0;
    return render->shadowReceiverIDs[index];
}
u32 floorDataBiosGetShadowLightID(GSfloor_dd_ *floor) {
    if (floor == 0) return 0;
    FloorRenderData **table = floor->render;
    if (table == 0) return 0;
    FloorRenderData *render = *table;
    if (render == 0) return 0;
    return render->shadowLightID;
}
u32 floorDataBiosGetLensFlareResID(GSfloor_dd_ *floor) {
    if (floor == 0) return 0;
    FloorRenderData **table = floor->render;
    if (table == 0) return 0;
    FloorRenderData *render = *table;
    if (render == 0) return 0;
    return 0;
}
u32 floorDataBiosGetSunResID(GSfloor_dd_ *floor) {
    if (floor == 0) return 0;
    FloorRenderData **table = floor->render;
    if (table == 0) return 0;
    FloorRenderData *render = *table;
    if (render == 0) return 0;
    return render->sunID;
}
void floorDataBiosSetMapResID(GSfloor_dd_ *floor, u32 id) { if (floor) floor->mapResourceID = id; }
FieldCameraList *floorDataBiosGetFieldCameraListPtr(GSfloor_dd_ *floor) {
    if (floor == 0) return 0;
    FieldCameraList **table = floor->fieldCameras;
    if (table == 0) return 0;
    return *table;
}
#pragma push
#pragma dont_inline on
s32 floorDataBiosGetPosListData(u32 index, GSvec *position, f32 *rotation) {
    FloorPositionList *list = floorDataBiosGetPosListPtr(floorDataBiosGetCurrentPtr());
    if (list == 0) return 0;
    if (index < *list->count) {
        FloorPosition *entry = &list->entries[index];
        if (position) position->set(entry->x, entry->y, entry->z);
        if (rotation) *rotation = 0.017453292f * entry->rotation;
        return 1;
    }
    return 0;
}
#pragma pop
FloorPositionList *floorDataBiosGetPosListPtr(GSfloor_dd_ *floor) {
    if (floor == 0) return 0;
    FloorPositionList **table = floor->positions;
    if (table == 0) return 0;
    return *table;
}
floorCharacter_dd_ *floorDataBiosGetCharInfo(GSfloor_dd_ *floor, u32 index) {
    if (floor == 0) return 0;
    FloorCharacterList **table = floor->characters;
    if (table == 0) return 0;
    FloorCharacterList *list = *table;
    if (index >= *list->count) return 0;
    return &list->entries[index];
}
u32 floorDataBiosGetCharNum(GSfloor_dd_ *floor) {
    if (floor == 0) return 0;
    FloorCharacterList **table = floor->characters;
    if (table == 0) return 0;
    FloorCharacterList *list = *table;
    if (list == 0) return 0;
    return *list->count;
}
void (*floorDataBiosGetPostFunc(GSfloor_dd_ *floor))(GSfloor_dd_ *, u32) { if (floor == 0) return 0; return floor->postFunction; }
void (*floorDataBiosGetMainFunc(GSfloor_dd_ *floor))() { if (floor == 0) return 0; return floor->mainFunction; }
void (*floorDataBiosGetPreFunc(GSfloor_dd_ *floor))(GSfloor_dd_ *, u32) { if (floor == 0) return 0; return floor->preFunction; }
u32 floorDataBiosGetPlaceName(GSfloor_dd_ *floor) { if (floor == 0) return 0; return floor->placeNameID; }
u16 floorDataBiosGetFloorID(GSfloor_dd_ *floor) { if (floor == 0) return 0; return floor->floorID; }
u32 floorDataBiosGetFileGroupID(GSfloor_dd_ *floor) { s32 index = fn_801231D4(); if (floor == 0) return 0; return floor->languageGroupIDs[index]; }
u32 floorDataBiosGetGroupID(GSfloor_dd_ *floor) { s32 index = fn_801231D4(); if (floor == 0) return 0; return floor->languageGroupIDs[index]; }
u8 floorDataBiosGetFloorKind(GSfloor_dd_ *floor) {
    if (floor == 0) return 0;
    if (floor->kind == 2 && fightGetFightEncountDataId() == 0) {
        if (pokecoloGetRomVersion() == 2) return 4;
        return 1;
    }
    return floor->kind;
}
u32 floorDataBiosGetMapResID(GSfloor_dd_ *floor) { if (floor == 0) return 0; return floor->mapResourceID; }
u8 floorDataBiosGetArea(GSfloor_dd_ *floor) { if (floor == 0) return 0; return floor->area; }
GSfloor_dd_ *floorDataBiosGetCurrentPtr() { return floorDataBiosGetPtr(GSfloorGetCurrent()); }
GSfloor_dd_ *floorDataBiosGetPtr(u32 floorID) {
    GSfloor_dd_ *floor = floordata;
    u32 i;
    for (i = 0; i != *floordata_number; i++) {
        if (floor->floorID == floorID) return floor;
        floor++;
    }
    return 0;
}
s32 fn_801231D4() {
    switch (pokecoloGetLanguage()) {
    case 2: return 0;
    case 3: return 1;
    case 4: return 2;
    case 5: return 3;
    case 6: return 4;
    default: return 0;
    }
}
}
