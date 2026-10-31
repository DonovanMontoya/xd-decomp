#include <dolphin/types.h>

extern "C" {
u8 koukaDataBiosGetStatusKind(u32 id);
u16 koukaDataBiosGetStatus(u32 id);
s16 koukaDataBiosGetValue(u32 id, u32 index);
u8 koukaDataBiosGetVar(u32 id);
u16 koukaDataBiosGetLink(u32 id);
u16 koukaLinkDataBiosGetKouka(u32 id, u32 index);
s32 statusGetStatus(u8 statusKind, void* fightPokemon, u16, u16, u16);
s32 statusSetStatus(u8 statusKind, void* fightPokemon, u16, u16, void* target, s32 value);
u32 fightFloorGetStatus(s32, s32, s32, s32);
void* fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void* target, u16 id);
}

static inline s16 koukaGetBaseValue(u32 id) {
    return koukaDataBiosGetValue(id, 0);
}

static s32 _koukaOneExec(u32 id, void* fightPokemon, void* target, s32* out);

extern "C" void koukaExec(u32 id, void* fightPokemon, void* target, s32* out) {
    u16 link;
    u16 i;
    if (out != NULL) {
        _koukaOneExec(id, fightPokemon, target, out);
    } else {
        _koukaOneExec(id, fightPokemon, target, 0);
    }
    link = koukaDataBiosGetLink(id);
    if (link != 0) {
        for (i = 0; i < 8; i++) {
            if (koukaLinkDataBiosGetKouka(link, i) != 0) {
                if (out != NULL) {
                    _koukaOneExec(id, fightPokemon, target, &out[i + 1]);
                } else {
                    _koukaOneExec(id, fightPokemon, target, 0);
                }
            }
        }
    }
}

static s32 _koukaOneExec(u32 id, void* fightPokemon, void* target, s32* out) {
    u16 status;
    u8 statusKind;
    s16 value0;
    s16 value1;
    u32 var;
    s32 current;
    s32 result;
    s32 ret;

    if (id == 0) {
        return 0;
    }
    statusKind = koukaDataBiosGetStatusKind(id);
    status = koukaDataBiosGetStatus(id);
    value0 = koukaGetBaseValue(id);
    value1 = koukaDataBiosGetValue(id, 1);
    var = koukaDataBiosGetVar(id);
    current = statusGetStatus(statusKind, fightPokemon, 0, status, value0);
    if (var == 0 || var == 2 || var == 3) {
        if (value0 == -1) {
            value0 = statusGetStatus(statusKind, fightPokemon, 0, value1, 0) / 2;
        } else if (value0 == -2) {
            value0 = statusGetStatus(statusKind, fightPokemon, 0, value1, 0);
        } else if (value0 < 0 || value1 < 0) {
            return 0;
        }
    }
    switch ((s32)var) {
    case 0:
        result = value0;
        break;
    case 1:
        result = current * value0 / value1;
        break;
    case 2:
        result = current + value0;
        break;
    case 3:
        result = current - value0;
        break;
    case 4:
        result = current + current * value0 / value1;
        break;
    case 5:
        result = current - current * value0 / value1;
        break;
    default:
        return 0;
    }
    ret = statusSetStatus(statusKind, fightPokemon, 0, status,
                          target != NULL ? fightTargetGetTragetPtrToRelativeHostSideFightTargetId(
                                               target, fightFloorGetStatus(0, 0, 0x14, 0))
                                         : 0,
                          result);
    if (out != NULL) {
        *out = result;
    }
    return ret;
}
