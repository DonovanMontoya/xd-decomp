#include <global.h>

extern "C" {
void* fightKoukaDataBiosGetPtr(u16);
u16 fightKoukaDataBiosGetKoukaDataId(void*);
u16 fightKoukaDataBiosGetFightTargetDataId(void*);
u16 fightKoukaDataBiosGetFightJoukenDataId(void*);
u8 fightFloor_GetFightType(void*);
void* fightTargetGetPtr(u16, void*, u16);
u8 fightJoukenExec(u16, s32);
s32 fightKoukaDoJoukenAndKouka(void*, u16, u16, u16);
void koukaExec(s32, void*, void*, u32);
}

extern "C" u16 fightKoukaDataGetKoukaDataId(u16 id) {
    return fightKoukaDataBiosGetKoukaDataId(fightKoukaDataBiosGetPtr(id));
}
extern "C" u16 fightKoukaDataGetFightTargetDataId(u16 id) {
    return fightKoukaDataBiosGetFightTargetDataId(fightKoukaDataBiosGetPtr(id));
}
extern "C" u16 fightKoukaDataGetFightJoukenDataId(u16 id) {
    return fightKoukaDataBiosGetFightJoukenDataId(fightKoukaDataBiosGetPtr(id));
}
#pragma push
#pragma dont_inline on
#pragma optimize_for_size on
extern "C" void fightKoukaDoFightKoukaJoukenAndKouka(void* base, u16 id) {
    u16 condition = fightKoukaDataGetFightJoukenDataId(id);
    u16 target = fightKoukaDataGetFightTargetDataId(id);
    u16 effect = fightKoukaDataGetKoukaDataId(id);
    fightKoukaDoJoukenAndKouka(base, condition, target, effect);
}
#pragma pop
extern "C" s32 fightKoukaDoJoukenAndKouka(void* base, u16 condition, u16 targetId, u16 effect) {
    s32 ret = 0;
    u16 type = fightFloor_GetFightType(0);
    void* target = fightTargetGetPtr(targetId, base, type);
    u8 result = fightJoukenExec(condition, (s32)base);
    if (result == 1) {
        koukaExec(effect, target, base, 0);
        ret = 1;
    }
    return ret;
}
