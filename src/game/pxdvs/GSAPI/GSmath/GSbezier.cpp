#include <game/pxdvs/GSAPI/GSmath/GSbezier.hpp>

struct BezierParameterLimit {
    f32 value;
};

static const BezierParameterLimit parameterMax = {1.0f};
static const BezierParameterLimit parameterMin = {0.0f};

#pragma opt_common_subs off

void GSbezierCalculateVector(Vec* result, const GSbezier* curve, f32 t) {
    Vec term;
    if (t < parameterMin.value) t = parameterMin.value;
    if (t > parameterMax.value) t = parameterMax.value;

    f32 tSquared = t * t;
    f32 inverseT = parameterMax.value - t;
    f32 inverseTSquared = inverseT * inverseT;

    PSVECScale(&curve->start, result, inverseTSquared * inverseT);
    PSVECScale(&curve->startControl, &term, (3.0f * t) * inverseTSquared);
    PSVECAdd(result, &term, result);
    PSVECScale(&curve->endControl, &term, (3.0f * tSquared) * inverseT);
    PSVECAdd(result, &term, result);
    PSVECScale(&curve->end, &term, tSquared * t);
    PSVECAdd(result, &term, result);
}

#pragma opt_common_subs reset
