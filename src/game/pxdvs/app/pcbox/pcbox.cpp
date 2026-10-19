#include <game/pxdvs/app/pcbox/pcboxPrivate.hpp>

s8 PCBOX::lastWatchBoxID;

PCBOX* PCBOX::getPointer() {
    return (PCBOX*)savedataGetStatus(0, 3);
}

extern "C" s32 pcboxAddPokemon(PCBOX*, Pokemon*, s8);

s32 PCBOX::addPokemonLastWatchBox(Pokemon* pokemon) {
    return addPokemon(pokemon, -1);
}

s32 PCBOX::addPokemon(Pokemon* pokemon, s8 box) {
    return pcboxAddPokemon(this, pokemon, box) != 0;
}

static inline Pokemon* pokemonSlot(PCBOX* self, s8 box, s8 slot) {
    Pokemon* result;
    if (box < 0 || box >= 8) {
        result = 0;
    } else if (slot < 0 || slot >= 30) {
        result = 0;
    } else {
        result = &self->boxes[box].pokemon[slot];
    }
    return result;
}

Pokemon* PCBOX::getPokemon(s8 box, s8 slot) {
    PCBOX* self = this;
    if (self == 0) {
        self = getPointer();
    }
    return pokemonSlot(self, box, slot);
}

s32 PCBOX::setPokemon(Pokemon* src, s8 box, s8 slot) {
    PCBOX* self = this;
    Pokemon* dst;
    s32 ok;
    if (self == 0) {
        self = getPointer();
    }
    dst = pokemonSlot(self, box, slot);
    if (dst == 0) {
        ok = 0;
    } else {
        DarkPokemon* dark;
        memcpy(dst, src, sizeof(Pokemon));
        pokemonAllKaihuku(dst);
        dark = dst->getDarkPokemon();
        if (dark != 0) {
            dark->setPlace(place2, box);
        }
        ok = 1;
    }
    return ok != 0;
}

s8 PCBOX::getPokemonBoxNbEmptySlot(s8 box) {
    PCBOX* self = this;
    int used = 0;
    s8 slot;
    if (self == 0) {
        self = getPointer();
    }
    if (box < 0 || box >= 8) {
        used = -1;
    } else {
        for (slot = 0; slot < 30; slot++) {
            Pokemon* p = pokemonSlot(self, box, slot);
            if (p != 0 && pokemonCheckValid(p) != 0) {
                used++;
            }
        }
    }
    if ((s8)used < 0) {
        return -1;
    }
    return 30 - used;
}

s32 PCBOX::getPokemonBoxNbUsedSlot(s8 box) {
    PCBOX* self = this;
    int used = 0;
    s8 slot;
    if (self == 0) {
        self = getPointer();
    }
    if (box < 0 || box >= 8) {
        used = -1;
    } else {
        for (slot = 0; slot < 30; slot++) {
            Pokemon* p = pokemonSlot(self, box, slot);
            if (p != 0 && pokemonCheckValid(p) != 0) {
                used++;
            }
        }
    }
    return used;
}

s32 PCBOX::delPokemon(s8 box, s8 slot) {
    PCBOX* self = this;
    Pokemon* p;
    s32 ok;
    if (self == 0) {
        self = getPointer();
    }
    p = pokemonSlot(self, box, slot);
    if (p == 0) {
        ok = 0;
    } else if (pokemonCheckValid(p) == 0) {
        ok = 0;
    } else {
        pokemonInit((u32)p);
        ok = 1;
    }
    return ok != 0;
}

static inline void initBoxes(PCBOX* self) {
    s32 i;
    for (i = 0; i < 8; i++) {
        msgctrlSetValue(0x34, i + 1);
        GSmsgMakeGScharStr(&self->boxes[i], 9, 0x3B39);
        pokemonInitAry((u32)self->boxes[i].pokemon, 0x1E);
    }
    itemInitAry(self->items, 0xEB);
    self->lastItemSlot = 0;
}

void PCBOX::init() {
    PCBOX* self = this;
    if (self == 0) {
        self = getPointer();
    }
    initBoxes(self);
}

PCBOXItem* PCBOX::getItem(s16 idx) {
    PCBOX* self = this;
    if (self == 0) {
        self = getPointer();
    }
    if (idx < 0 || idx >= 0xEB) {
        return 0;
    }
    return &self->items[idx];
}

char16* PCBOX::getPokemonBoxName(s8 box) {
    PCBOX* self = this;
    if (self == 0) {
        self = getPointer();
    }
    if (box < 0 || box >= 8) {
        return 0;
    }
    return self->boxes[box].name;
}

extern "C" {

s32 pcboxGetNbItemSlot() {
    return 0xEB;
}

s32 pcboxGetNbPokemonBox() {
    return 8;
}

PCBOXItem* pcboxGetItem(PCBOX* pcbox, s16 idx) {
    return pcbox->getItem(idx);
}

char16* pcboxGetPokemonBoxName(PCBOX* pcbox, s8 box) {
    return pcbox->getPokemonBoxName(box);
}

void pcboxInit(PCBOX* pcbox) {
    pcbox->init();
}


s8 pcboxGetPokemonBoxNbEmptySlot(PCBOX* pcbox, s8 box) {
    return pcbox->getPokemonBoxNbEmptySlot(box);
}


void pcboxDebugPokemonSetupFull() {
    Pokemon pokemon;
    PCBOX* pcbox = PCBOX::getPointer();
    u32 n;
    int box;
    int slot;
    initBoxes(pcbox);
    PCBOX::getPointer();
    n = 0;
    box = 0;
    do {
        s8 boxID = box;
        slot = 0;
        do {
            menuPocketDebugMakePokemonBySN(pokemon, n++, slot == 1, 0.5f);
            s8 slotID = slot;
            PCBOX::getPointer()->setPokemon(&pokemon, boxID, slotID);
            slot++;
        } while (slot < 0x1E);
        box++;
    } while (box < 8);
}


void pcboxDebugPokemonSetup() {
    Pokemon pokemonA;
    Pokemon pokemonB;
    PCBOX* pcbox = PCBOX::getPointer();
    u32 n;
    int box;
    int slot;
    initBoxes(pcbox);
    PCBOX::getPointer();
    n = 0;
    box = 0;
    do {
        if (box == 7) {
            slot = 0;
            do {
                menuPocketDebugMakePokemonBySN(pokemonA, n++, false, 0.0f);
                PCBOX::getPointer()->setPokemon(&pokemonA, box, slot);
                slot++;
            } while (slot < 0x1E);
        } else {
            slot = 0;
            do {
                menuPocketDebugMakePokemonBySN(pokemonB, n++, (slot % 10) == 0, 0.1f);
                PCBOX::getPointer()->setPokemon(&pokemonB, box, slot);
                slot++;
            } while (slot < 3);
        }
        box++;
    } while (box < 8);
}

}

s16 PCBOX::searchItem(u16 id) {
    s32 i;
    for (i = 0; i < 0xEB; ++i) {
        if (itemCheckValid(&items[i]) && (s32)id == (s32)itemGetStatus(&items[i], 0, 0x1B, 0)) break;
    }
    s16 result = -1;
    if (i < 0xEB) result = i;
    return result;
}

extern "C" {
u16 pcboxAddItem(PCBOX* box, u16 id, u16 count) {
    PCBOX* self = box;
    if (!self) self = PCBOX::getPointer();
    if (!count) return count;
    if (!itemDataBiosGetPtr(id)) return count;
    return (u16)itemAddItemDataIdAry(self->items, 0xEB, id, count, self->searchItem(id), 999, 0, 0);
}
u16 pcboxDelItem(PCBOX* box, u16 id, u16 count) {
    PCBOX* self = box;
    if (!self) self = PCBOX::getPointer();
    if (!count) return count;
    if (!itemDataBiosGetPtr(id)) return count;
    s16 slot = self->searchItem(id);
    if (slot < 0) return count;
    return (u16)itemDecItemDataIdAry(self->items, 0xEB, id, count, slot, 999, 0);
}
s32 pcboxSwapItemSlot(PCBOX* self, s16 a, s16 b) {
    PCBOXItem* first = self->getItem(a);
    if (!first) return 0;
    PCBOXItem* second = self->getItem(b);
    if (!second) return 0;
    itemReplace(first, second);
    return 1;
}
s32 pcboxSetPokemonBoxName(PCBOX* self, s8 box, const u16* name) {
    if (!self) self = PCBOX::getPointer();
    if (box < 0 || box >= 8) return 0;
    if (!name) return 0;
    s32 length = 0;
    const u16* cursor = name;
    while (*cursor) { ++cursor; ++length; }
    if (length > 8) return 0;
    GScharCpy(self->boxes[box].name, name);
    return 1;
}
}

s32 PCBOX::isPokemonFull() {
    for (s32 box = 0; box < 8; ++box) {
        if (getPointer()->getPokemonBoxNbEmptySlot(box) != 0) return 0;
    }
    return 1;
}

static inline u16 itemCount(PCBOX* self, s16 slot) {
    PCBOXItem* item;
    if (slot < 0 || slot >= 0xEB) item = 0;
    else item = &self->items[slot];
    if (!item) return 0xFFFF;
    if (!itemCheckValid(item)) return 0xFFFF;
    return itemGetStatus(item, 0, 0x1C, 0);
}

extern "C" {
u32 pcboxGetItemCapacity(PCBOX* box, u16 id) {
    PCBOX* self = box;
    if (!self) self = PCBOX::getPointer();
    if (!itemDataBiosGetPtr(id)) return 0;
    s16 slot = self->searchItem(id);
    u16 count;
    if (slot >= 0) {
        u16 quantity = itemCount(self, slot);
        count = quantity;
        if ((u16)count > 999) count = 0;
    } else count = 0;
    return (u16)(999 - count);
}
void pcboxSetStatus() {}
u32 pcboxGetStatus() { return 0; }
}

static inline s8 emptyPokemonSlot(PCBOX* self, s8 box) {
    s32 slot;
    for (slot = 0; slot < 30; ++slot) {
        Pokemon* p = pokemonSlot(self, box, slot);
        if (p && !pokemonCheckValid(p)) break;
    }
    s8 result = -1;
    if (slot < 30) result = slot;
    return result;
}

extern "C" s32 pcboxAddPokemon(PCBOX* pcbox, Pokemon* src, s8 box) {
    PCBOX* self = pcbox;
    s8 slot;
    if (!self) self = PCBOX::getPointer();
    if (box < -1 || box >= 8) return 0;
    if (!src) return 0;
    if (box == -1) {
        u8 found = 0;
        for (box = menuPcBoxGetLastViewBox(); box < 8; ++box) {
            slot = emptyPokemonSlot(self, box);
            if (slot >= 0) { found = 1; break; }
        }
        if (!found) {
            for (box = 0; box < menuPcBoxGetLastViewBox(); ++box) {
                slot = emptyPokemonSlot(self, box);
                if (slot >= 0) { found = 1; break; }
            }
        }
        if (!found) return 0;
    } else {
        slot = emptyPokemonSlot(self, box);
        if (slot < 0) return 0;
    }
    if (!self) self = PCBOX::getPointer();
    Pokemon* dst = pokemonSlot(self, box, slot);
    if (!dst) return 0;
    memcpy(dst, src, sizeof(Pokemon));
    pokemonAllKaihuku(dst);
    DarkPokemon* dark = dst->getDarkPokemon();
    if (dark) dark->setPlace(place2, box);
    return 1;
}
