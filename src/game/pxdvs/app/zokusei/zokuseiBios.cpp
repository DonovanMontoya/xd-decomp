#include <game/pxdvs/app/waza/wazaLayout.hpp>

// Index fields in units of their stored type, keeping the row and field offsets together.
#define TYPE_FIELD(type, field, id) \
    ((type*)zokusei_data)[(id) * (sizeof(TypeRecord) / sizeof(type)) + \
                        offsetof(TypeRecord, field) / sizeof(type)]

extern "C" {
u16 zokuseiBiosGetSmallSpriteID(u16 id) {
    if (id >= *zokusei_data_number) return 0;
    return TYPE_FIELD(u16, smallSprite, id);
}

u16 zokuseiBiosGetSpriteID(u16 id) {
    if (id >= *zokusei_data_number) return 0;
    return TYPE_FIELD(u16, sprite, id);
}

u8 zokuseiBiosGetWazaKind(u16 id) {
    if (id >= *zokusei_data_number) return 0;
    return TYPE_FIELD(u8, kind, id);
}

u32 zokuseiBiosGetName(u16 id) {
    if (id >= *zokusei_data_number) return 0;
    return TYPE_FIELD(u32, name, id);
}

u16 zokuseiBiosGetWazaJoutai(u32 attack, u32 defense) {
    if (attack >= *zokusei_data_number) return 0;
    if (defense >= 18) return 0;
    return zokusei_data[attack].matchup[defense];
}
}

#undef TYPE_FIELD
