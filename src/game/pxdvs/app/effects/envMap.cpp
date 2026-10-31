#pragma defer_codegen off
#include <game/pxdvs/app/wazaSequence/wazaeffectsPrivate.hpp>
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>

extern "C++" { void envMapEffect::_stop(); }
extern "C++" { bool envMapEffect::_update(f32); }
extern "C++" { bool envMapEffect::_start(); }

extern "C" void Stop__8GSeffectFv(GSeffect*);

envMapEffect::~envMapEffect() { Stop__8GSeffectFv(this); }

#pragma force_active on
extern "C++" {
void envMapEffect::_stop() {
    if (model != 0) GSmodelDisableEnvMap(model);
}
}
extern "C++" {
bool envMapEffect::_update(f32) {
    if (model == 0) return false;
    if (!GSmodelIsEnvMapEnabled(model)) GSmodelEnableEnvMap(model, texture, type, value);
    else GSmodelSetEnvMapBlendValue(model, value);
    return true;
}
}
extern "C++" {
bool envMapEffect::_start() {
    if (model == 0) return false;
    GSmodelEnableEnvMap(model, texture, type, value);
    return true;
}
}
