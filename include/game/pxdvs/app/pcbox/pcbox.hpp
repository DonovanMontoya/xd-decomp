#ifndef PXDVS_APP_PCBOX_HPP
#define PXDVS_APP_PCBOX_HPP

#include <game/pxdvs/app/item/itemBiosLayout.hpp>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

struct PCBOXBox {
    char16 name[9];             // 0x0
    Pokemon pokemon[30];        // 0x14
};

class PCBOX {
public:
    PCBOXBox boxes[8];          // 0x0
    ItemBiosRecord items[235];  // 0xB860
    s32 lastViewBox;            // 0xBC0C
    u32 unkBC10[16];

    static s8 lastWatchBoxID;
    static PCBOX* getPointer();
    bool isPokemonFull();

    s8 getPokemonBoxNbEmptySlot(s8);
    s32 getPokemonBoxNbUsedSlot(s8);
    char16* getPokemonBoxName(s8);
    s32 delPokemon(s8, s8);
    s32 addPokemonLastWatchBox(Pokemon*);
    s32 addPokemon(Pokemon*, s8);
    s32 setPokemon(Pokemon*, s8, s8);
    Pokemon* getPokemon(s8, s8);
    void init();

    ItemBiosRecord* getItem(s16);
    s16 searchItem(u16);
};

typedef char PCBOXBoxPokemonOffsetCheck[offsetof(PCBOXBox, pokemon) == 0x14 ? 1 : -1];
typedef char PCBOXBoxSizeCheck[sizeof(PCBOXBox) == 0x170C ? 1 : -1];
typedef char PCBOXItemsOffsetCheck[offsetof(PCBOX, items) == 0xB860 ? 1 : -1];
typedef char PCBOXLastViewBoxOffsetCheck[offsetof(PCBOX, lastViewBox) == 0xBC0C ? 1 : -1];
typedef char PCBOXTrailingWordsOffsetCheck[offsetof(PCBOX, unkBC10) == 0xBC10 ? 1 : -1];
typedef char PCBOXSizeCheck[sizeof(PCBOX) == 0xBC50 ? 1 : -1];

#endif
