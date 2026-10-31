#include <game/pxdvs/app/waza/wazaLayout.hpp>

#pragma force_active on
extern "C" {
u16 zokuseiBiosGetSmallSpriteID(u16 id) {
    if (id >= *zokusei_data_number) return 0;
    return zokusei_data[id].smallSprite;
}

u16 zokuseiBiosGetSpriteID(u16 id) {
    if (id >= *zokusei_data_number) return 0;
    return zokusei_data[id].sprite;
}

u8 zokuseiBiosGetWazaKind(u16 id) {
    if (id >= *zokusei_data_number) return 0;
    return zokusei_data[id].kind;
}

u32 zokuseiBiosGetName(u16 id) {
    if (id >= *zokusei_data_number) return 0;
    return zokusei_data[id].name;
}

u16 zokuseiBiosGetWazaJoutai(u32 attack, u32 defense) {
    if (attack >= *zokusei_data_number) return 0;
    if (defense >= 18) return 0;
    return zokusei_data[attack].matchup[defense];
}
}

#pragma force_active reset
