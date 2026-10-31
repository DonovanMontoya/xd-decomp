#include <game/pxdvs/app/battleGrid/battleCameraPrivate.hpp>
#include <game/maximum/GSAPI/baselib/math_support.h>
#include <dolphin/os/OSFastCast.h>

extern GSvec zeroVector;
extern GSvec unitScaleVector;

WazaSequence *gActiveWazaSequenceCamera;
static f32 gLoopCameraWaitTime = 3.0f;
static s32 gLastSelectedIndex = -1;
static u8 gBattleGridSimpleCamera;
static u8 g_mode;
static u8 g_enable_battle_camera;

static inline ModelSequence *asModel(NullSequence *sequence) {
    if (sequence->type == 1) return static_cast<ModelSequence *>(sequence);
    return 0;
}

static void _battleCameraStartRandom(ModelSequence *sequence);
static void _battleCameraUpdateWaza();

// Clears the offsets left behind by the previous shot and fixes up the camera mode.
static inline void battleCameraResetOffsets() {
    battleGridResetModelVisibilityFlags();
    cameraMoveStop();
    cameraSetOffsetPosition(&zeroVector);
    cameraSetOffsetRotation(&zeroVector);
    cameraSetOffsetScale(&unitScaleVector);
    cameraSetMirrorFlag(0);
}

extern "C" {

void battleCameraDisable() {
    g_enable_battle_camera = 0;
}

u8 battleCameraIsSimple() {
    return gBattleGridSimpleCamera;
}

void battleCameraDoFull() {
    gBattleGridSimpleCamera = 0;
}

void battleCameraDoSimple() {
    gBattleGridSimpleCamera = 1;
}

void battleCameraInit(u32 enable) {
    g_mode = 0;
    gActiveWazaSequenceCamera = 0;
    gLastSelectedIndex = -1;
    gLoopCameraWaitTime = 3.0f;
    gBattleGridSimpleCamera = 0;
    u8 enabled = 0;
    if (enable != 0 && floorDataBiosGetFloorKind() == 2) {
        enabled = 1;
    }
    g_enable_battle_camera = enabled;
}

void battleCameraUpdate() {
    switch (g_mode) {
    case 2:
        _battleCameraUpdateWaza();
        break;
    case 1:
        if (cameraMoveEndCheckSpecial(0) == 0) {
            battleCameraResetOffsets();
            switch (g_mode) {
            case 2:
                if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) != 0 && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) != 0) {
                    cameraStopAnime();
                }
                gActiveWazaSequenceCamera = 0;
                g_mode = 0;
                break;
            case 1:
                g_mode = 3;
                break;
            case 3:
                g_mode = 0;
                break;
            }
        }
        break;
    case 3:
        battleCameraStartRandom(gBattleGridSimpleCamera);
        break;
    }
}

void battleCameraStop() {
    battleCameraResetOffsets();
    switch (g_mode) {
    case 2:
        if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) != 0 && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) != 0) {
            cameraStopAnime();
        }
        gActiveWazaSequenceCamera = 0;
        g_mode = 0;
        break;
    case 1:
        g_mode = 3;
        break;
    case 3:
        g_mode = 0;
        break;
    }
}

void battleCameraStartRandom(u8 simple) {
    s32 i;
    s32 j;
    s32 pick;
    s32 seen;
    BattleCameraGridEntry *entry;
    int count = gBattleGrid.pokemonCount;
    if (g_enable_battle_camera != 0 && g_mode != 1) {
        if (count == 0) {
            _battleCameraStartRandom(0);
            return;
        }
        if (count == 1) {
            pick = 0;
        } else {
            pick = (u16)HSD_Rand() % count;
            while (pick == gLastSelectedIndex) {
                pick = (u16)HSD_Rand() % count;
            }
        }
        gLastSelectedIndex = pick;
        seen = 0;
        entry = gBattleGrid.entry;
        for (i = 0; i < 4; i++, entry++) {
            if (entry->trainer != 0) {
                for (j = 0; j < 2; j++) {
                    if (entry->pokemon[j] != 0) {
                        if (seen == pick) {
                            _battleCameraStartRandom(entry->pokemon[j]);
                            gLoopCameraWaitTime = 3.0f;
                            return;
                        }
                        seen++;
                    }
                }
            }
        }
    }
}

}  // extern "C"

static inline f32 Lerp(f32 a, f32 b, f32 t) {
    f32 d = b - a;
    return d * t + a;
}

static inline f32 RotAdd(f32 min, f32 max, f32 base, f32 t) {
    f32 d = max - min;
    return d * t + (base + min);
}

static inline f32 RotSub(f32 min, f32 max, f32 base, f32 t) {
    f32 d = max - min;
    return (base - min) - d * t;
}

static inline void DoPreset(GSvec* t, GSvec* a, GSvec* b, f32 time, f32 fov) {
    f32 s = battleGridGetUnscaledDistance(true);
    s = battleGridGetDistance(true) / s;
    PSVECScale(a, a, s);
    PSVECScale(b, b, s);
    if (HSD_Randf() < 0.5f) {
        cameraSetType(2);
        cameraSetPosition(a);
        cameraMovePosition(2, b, time);
        cameraSetFov(fov);
        cameraSetTargetPos(t);
        cameraSetTargetOfs(&zeroVector);
    } else {
        cameraSetType(2);
        cameraSetPosition(b);
        cameraMovePosition(2, a, time);
        cameraSetFov(fov);
        cameraSetTargetPos(t);
        cameraSetTargetOfs(&zeroVector);
    }
}

static inline void DoTracked(GSvec* t, GSvec* a, GSvec* b, f32 fov) {
    f32 r = HSD_Randf();
    cameraSetType(2);
    cameraSetPosition(a);
    cameraMovePosition(2, b, 3.0f + r);
    cameraSetFov(fov);
    cameraSetTargetPos(t);
    cameraSetTargetOfs(&zeroVector);
}

static inline void StopWazaCamera(void) {
    if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera)) {
        if (wazaSequenceCameraAnim(gActiveWazaSequenceCamera) != 0) {
            cameraStopAnime();
        }
    }
    gActiveWazaSequenceCamera = 0;
}

static void _battleCameraStartRandom(ModelSequence* seq) {
    wazaSequenceCameraParams params;
    GSvec cur;
    GSvec a;
    GSvec b;
    GSvec t;
    u8 pattern;
    u8 nonTrainerActive;
    bool again;
    bool isTrainer;
    int flags;
    f32 dir;
    f32 d1;
    f32 d0;
    f32 dur;
    f32 dist1;
    f32 rot2;
    f32 fov2;
    f32 dist2;
    f32 fov1;
    f32 height;
    f32 rot1;
    f32 r;
    f32 d;
    f32 lo;
    f32 lowA, highA, lowB, highB;
    static u8 old_pos_pattern[2] = {12, 12};

    isTrainer = fightFloor_GetTrainer(0) != 0;
    nonTrainerActive = fightPokemonGetNonTrainerPokemonIsActiveFlag();
    flags = 0;
    if (!g_enable_battle_camera) {
        return;
    }
    if (!wazaSequenceSysIsValidSequence(seq) || seq->visible == 0) {
        seq = 0;
    }
    battleCameraResetOffsets();
    switch (g_mode) {
    case 2:
        StopWazaCamera();
        break;
    case 1:
    case 3:
        break;
    }
    g_mode = 1;
    again = true;
    while (again) {
        bool noParent = (seq == 0 || seq->isPokemon == 0);
        pattern = (u16)HSD_Rand() % (noParent ? 10 : 12);
        if (pattern != old_pos_pattern[0] && pattern != old_pos_pattern[1]) {
            again = false;
        }
        if (!isTrainer && pattern == 3) {
            again = true;
        }
    }
    old_pos_pattern[1] = old_pos_pattern[0];
    old_pos_pattern[0] = pattern;
    if (seq != 0 && seq->isPokemon == 0) {
        switch (battleGridGetNumPokemonsForTrainer(seq)) {
        case 1:
            flags = 7;
            break;
        case 2:
            flags = 1;
            break;
        }
    }
    if (seq != 0) {
        _wazaSequenceCameraCalculateParams(seq, flags, &params);
    }
    switch (pattern) {
    case 0:
        t.param3 = t.param2 = t.param1 = 0.0f;
        a.param1 = -20.0f; a.param2 = 27.5f; a.param3 = 110.0f;
        b.param1 = 20.0f; b.param2 = 27.5f; b.param3 = 110.0f;
        DoPreset(&t, &a, &b, 4.0f, 60.0f);
        return;
    case 1:
        t.param3 = t.param2 = t.param1 = 0.0f;
        a.param1 = 110.0f; a.param2 = 27.5f; a.param3 = 0.0f;
        b.param1 = 110.0f; b.param2 = 27.5f; b.param3 = 20.0f;
        DoPreset(&t, &a, &b, 2.5f, 60.0f);
        return;
    case 2:
        t.param3 = t.param2 = t.param1 = 0.0f;
        a.param1 = -110.0f; a.param2 = 27.5f; a.param3 = 20.0f;
        b.param1 = -110.0f; b.param2 = 27.5f; b.param3 = 0.0f;
        DoPreset(&t, &a, &b, 2.5f, 60.0f);
        return;
    case 3:
        t.param3 = t.param2 = t.param1 = 0.0f;
        a.param1 = -65.0f; a.param2 = 27.5f; a.param3 = 100.0f;
        b.param1 = -100.0f; b.param2 = 27.5f; b.param3 = 65.0f;
        DoPreset(&t, &a, &b, 4.0f, 60.0f);
        return;
    case 4:
        t.param3 = t.param2 = t.param1 = 0.0f;
        a.param1 = 100.0f; a.param2 = 27.5f; a.param3 = 65.0f;
        b.param1 = 65.0f; b.param2 = 27.5f; b.param3 = 100.0f;
        DoPreset(&t, &a, &b, 4.0f, 60.0f);
        return;
    case 5:
        if ((isTrainer || nonTrainerActive) && HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        t.param1 = -d1 * dir; t.param2 = 5.0f; t.param3 = 0.0f;
        a.param1 = d1 * dir; a.param2 = 5.0f; a.param3 = d1;
        b.param1 = 0.2f * d1 * dir; b.param2 = 5.0f; b.param3 = d1;
        DoTracked(&t, &a, &b, 40.0f);
        return;
    case 6:
        if (HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        d0 = battleGridGetDistance(false);
        t.param1 = -d0 * dir; t.param2 = 0.0f; t.param3 = 0.0f;
        a.param1 = dir * (d1 + d0); a.param2 = 5.0f; a.param3 = 0.7f * d1;
        b.param1 = dir * (d1 + d0); b.param2 = 5.0f; b.param3 = 0.7f * -d1;
        DoTracked(&t, &a, &b, 30.0f);
        return;
    case 7:
        if ((isTrainer || nonTrainerActive) && HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        d0 = battleGridGetDistance(false);
        t.param1 = -d0 * dir; t.param2 = 5.0f; t.param3 = 0.0f;
        a.param1 = 0.0f; a.param2 = 5.0f; a.param3 = 0.7f * d1;
        b.param1 = 0.0f; b.param2 = 5.0f; b.param3 = 0.7f * -d1;
        DoTracked(&t, &a, &b, 60.0f);
        return;
    case 8: {
        f32 hiA = 2.0f * HSD_Randf() + 5.0f;
        f32 hiB = 2.0f * HSD_Randf() + 5.0f;
        r = HSD_Randf();
        if (r < 0.5f) {
            hiA *= -1.0f;
        }
        if (!(r < 0.5f)) {
            hiB *= -1.0f;
        }
        if (HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        d0 = battleGridGetDistance(false);
        t.param1 = -d1 * dir; t.param2 = 0.0f; t.param3 = 0.0f;
        a.param1 = dir * (d1 + d0); a.param2 = 5.0f; a.param3 = hiA;
        b.param1 = a.param1; b.param2 = 20.0f; b.param3 = hiB;
        DoTracked(&t, &a, &b, 20.0f);
        return;
    }
    case 9:
        if (HSD_Randf() < 0.5f) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
        d1 = battleGridGetDistance(true);
        d0 = battleGridGetDistance(false);
        t.param1 = -d0 * dir; t.param2 = 5.0f; t.param3 = 0.0f;
        a.param1 = dir * (d1 + d0); a.param2 = 2.0f; a.param3 = 0.25f * d1;
        b.param1 = dir * (d1 + d0); b.param2 = 2.0f; b.param3 = 0.25f * -d1;
        DoTracked(&t, &a, &b, 15.0f);
        return;
    case 10:
        r = HSD_Randf();
        lo = params.distanceMin;
        d = params.distanceMax - lo;
        dist1 = d * r + lo;
        r = HSD_Randf();
        lo = params.distanceMin;
        d = params.distanceMax - lo;
        dist2 = d * r + lo;
        if (dist1 < dist2) {
            f32 tmp = dist2;
            dist2 = dist1;
            dist1 = tmp;
        }
        height = Lerp(params.heightMin, params.heightMax, HSD_Randf());
        if (seq->flipped != 0) {
            rot2 = rot1 = RotSub(params.rotationA, params.rotationB, params.baseRotation, HSD_Randf());
        } else {
            rot2 = rot1 = RotAdd(params.rotationA, params.rotationB, params.baseRotation, HSD_Randf());
        }
        break;
    case 11:
        dist1 = dist2 = Lerp(params.distanceMin, params.distanceMax, HSD_Randf());
        height = Lerp(params.heightMin, params.heightMax, HSD_Randf());
        if (seq->flipped != 0) {
            r = HSD_Randf();
            lo = params.rotationA;
            d = params.rotationB - lo;
            rot2 = (params.baseRotation - lo) - d * r;
            rot1 = RotSub(params.rotationA, params.rotationB, params.baseRotation, HSD_Randf());
        } else {
            r = HSD_Randf();
            lo = params.rotationA;
            d = params.rotationB - lo;
            rot2 = d * r + (params.baseRotation + lo);
            rot1 = RotAdd(params.rotationA, params.rotationB, params.baseRotation, HSD_Randf());
        }
        break;
    default:
        dist1 = dist2 = Lerp(params.distanceMin, params.distanceMax, HSD_Randf());
        height = Lerp(params.heightMin, params.heightMax, HSD_Randf());
        if (seq->flipped != 0) {
            rot2 = rot1 = RotSub(params.rotationA, params.rotationB, params.baseRotation, HSD_Randf());
        } else {
            rot2 = rot1 = RotAdd(params.rotationA, params.rotationB, params.baseRotation, HSD_Randf());
        }
        break;
    }

    {
        f32 hsq = height;
        hsq *= height;
        _wazaSequenceCameraGetFOVRange(&params, &lowA, &highA, hsdSqrt(dist1 * dist1 + hsq));
        _wazaSequenceCameraGetFOVRange(&params, &lowB, &highB, hsdSqrt(dist2 * dist2 + hsq));
    }
    switch ((u8)((u16)HSD_Rand() % 3)) {
    case 1:
        r = HSD_Randf();
        fov2 = lowA;
        d = highA - fov2;
        fov2 = d * r + fov2;
        r = HSD_Randf();
        fov1 = lowB;
        d = highB - fov1;
        fov1 = d * r + fov1;
        if (fov2 < fov1) {
            f32 tmp = fov1;
            fov1 = fov2;
            fov2 = tmp;
        }
        break;
    case 2:
        r = HSD_Randf();
        fov2 = lowA;
        d = highA - fov2;
        fov2 = d * r + fov2;
        r = HSD_Randf();
        fov1 = lowB;
        d = highB - fov1;
        fov1 = d * r + fov1;
        if (fov2 > fov1) {
            f32 tmp = fov1;
            fov1 = fov2;
            fov2 = tmp;
        }
        break;
    case 0:    default:
        fov2 = fov1 = Lerp(lowA, highA, HSD_Randf());
        break;
    }
    dur = HSD_Randf();
    dur = dur + 3.0f;
    cameraMoveStop();
    cameraSetType(7);
    fn_80196A14(1);
    {
        _GSmodel* model = seq->model;
        u32 id = seq->field3C;
        u32 part;
        if (model != 0) {
            part = GSmodelCenterNull(model);
        } else {
            part = 0;
        }
        cameraSetTargetExt(20000, id, part);
    }
    cameraRefreshTargetPos();
    cameraSetTargetExt(0, 0, -1);
    cameraSetDistance(dist1);
    cameraSetHeight(height);
    cameraSetRotY(rot2);
    cameraSetFov(fov2);
    cameraUpdate();
    cameraGetPosition(&cur);
    cameraGetTargetPos(&t);
    PSVECSubtract(&cur, &t, &cur);
    cur.param2 = 0.0f;
    PSVECScale(&cur, &cur, dist2 / dist1);
    cur.param2 = height;
    PSVECAdd(&cur, &t, &cur);
    cameraMovePosition(7, &cur, dur);
    cameraMoveRotationXYZ(7, 0.0f, rot1, 0.0f, dur);
    cameraMoveFov(7, fov1, dur);
    cameraMovePositionAcc(dur * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
    cameraMoveRotationAcc(dur * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
    cameraMoveFovAcc(dur * (0.25f / (f32)GSgfxVideoGetVsyncRate()));
}

extern "C" void battleCameraStartWaza(WazaSequence *waza) {
    ModelSequence *sequence;
    _GSmodel *model;
    f32 speed = 1.0f;
    bool flip = false;
    s32 fovMask = 0;
    wazaSequenceCameraParams params;
    GSvec rootPosition;
    GSvec offsetPosition;
    GSvec offsetRotation;
    GSvec offsetScale;
    GSvec boundMiddle;
    GSvec boundMin;
    GSvec boundMax;
    GSvec probe;
    GSvec probeTrainer;
    GSvec boundSum;
    battleCameraResetOffsets();
    switch (g_mode) {
    case 2:
        if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) != 0 && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) != 0) {
            cameraStopAnime();
        }
        gActiveWazaSequenceCamera = 0;
        g_mode = 0;
        break;
    case 1:
        g_mode = 3;
        break;
    case 3:
        g_mode = 0;
        break;
    }
    if (wazaSequenceSysIsValidWaza(waza) != 0) {
    sequence = asModel(waza->owner);
    if (sequence != 0 && (model = sequence->model) != 0) {
    if (GSmodelIsRootNullAdded(model) != 0) {
        GSmodelGetRootPosition(model, &rootPosition);
    } else {
        rootPosition.param1 = 0.0f;
        rootPosition.param2 = 0.0f;
        rootPosition.param3 = 0.0f;
    }
    gActiveWazaSequenceCamera = waza;
    g_mode = 2;
    if (sequence->flipped != 0 && !(wazaSequenceFlags(waza) & 0x80)) {
        flip = true;
    }
    if (wazaSequenceCameraAnim(waza) != 0 && GSresGetResource(20000, wazaSequenceCameraAnim(waza)) != 0) {
        s32 mirror = 0;
        if (flip != 0) mirror = 4;
        cameraPlayOffsetAnime(20000, wazaSequenceCameraAnim(waza), 0, 0);
        u32 flags = wazaSequenceFlags(waza);
        if (flags & 4) {
            offsetPosition.param1 = 0.0f;
            offsetPosition.param2 = 0.0f;
            offsetPosition.param3 = 0.0f;
            offsetRotation.param1 = 0.0f;
            offsetRotation.param2 = 0.0f;
            offsetRotation.param3 = 0.0f;
            if (sequence->flipped != 0 && (flags & 0x02000000)) {
                offsetRotation.param2 = 3.1415927f;
            }
            if (wazaSequenceFlags(waza) & 0x800000) {
                battleGridGetNormalisedScale(&offsetScale);
                if (wazaSequenceFlags(waza) & 0x01000000) {
                    offsetScale.param2 = 1.0f;
                }
            } else {
                offsetScale.param1 = 1.0f;
                offsetScale.param2 = 1.0f;
                offsetScale.param3 = 1.0f;
            }
        } else {
            sequence->GetPosition(&offsetPosition);
            sequence->GetRotation(&offsetRotation);
            if (wazaSequenceFlags(waza) & 0x20000000) {
                offsetScale.param3 = 1.0f;
                offsetScale.param2 = 1.0f;
                offsetScale.param1 = 1.0f;
            } else {
                f32 scale = sequence->GetModelScale(true);
                offsetScale.param3 = scale;
                offsetScale.param2 = scale;
                offsetScale.param1 = scale;
            }
            if (wazaSequenceFlags(waza) & 0x4000) {
                GSboundGetMinMax(GSmodelGetBound(model), &boundMin, &boundMax, 1, 1, 0, 0);
                PSVECAdd(&boundMin, &boundMax, &boundSum);
                boundMiddle.param1 = boundSum.param1;
                boundMiddle.param2 = boundSum.param2;
                boundMiddle.param3 = boundSum.param3;
                PSVECScale(&boundMiddle, &boundMiddle, 0.5f);
                PSVECAdd(&offsetPosition, &boundMiddle, &offsetPosition);
            }
            if (waza->category == 2 && (sequence->flags & 1) == 1) {
                offsetPosition.param2 += rootPosition.param2;
            }
        }
        cameraSetMirrorFlag(mirror);
        cameraMoveStop();
        cameraSetOffsetPosition(&offsetPosition);
        cameraSetOffsetRotation(&offsetRotation);
        cameraSetOffsetScale(&offsetScale);
        cameraUpdate();
        return;
    }
    if (sequence->isPokemon != 0) {
        u32 flags = wazaSequenceFlags(waza);
        if (flags & 0x200000) {
            fovMask = 3;
        } else if (flags & 0x200) {
            fovMask = 4;
        } else if (flags & 0x400000) {
            sequence->GetPosition(&probe);
            if (probe.param3 < 0.0f) {
                fovMask = 4;
            } else {
                fovMask = 5;
            }
        }
    } else {
        switch (battleGridGetNumPokemonsForTrainer(sequence)) {
        case 1:
            if (wazaSequenceFlags(waza) & 0x400000) {
                fovMask = 7;
            } else {
                fovMask = 6;
            }
            break;
        case 2:
            if (wazaSequenceFlags(waza) & 0x200000) {
                fovMask = 1;
            } else {
                fovMask = 2;
            }
        default: {
            u32 flags = wazaSequenceFlags(waza);
            if (flags & 0x200000) {
                fovMask = 3;
            } else if (flags & 0x200) {
                fovMask = 4;
            } else if (flags & 0x400000) {
                sequence->GetPosition(&probeTrainer);
                if (probeTrainer.param3 < 0.0f) {
                    fovMask = 4;
                } else {
                    fovMask = 5;
                }
            }
            break;
        }
        }
        speed = 2.0f;
    }
    u32 flagsAfter = wazaSequenceFlags(waza);
    if (flagsAfter & 0x400) {
        fovMask |= 0x80;
    } else if (flagsAfter & 0x800) {
        fovMask |= 0x100;
    } else if (flagsAfter & 0x1000) {
        fovMask |= 0x200;
    }
    cameraMoveStop();
    cameraSetType(7);
    u32 targetId = sequence->field3C;
    s32 joint;
    WazaSequence *active = gActiveWazaSequenceCamera;
    if (sequence->model == 0) {
        joint = 0;
    } else if (active != 0) {
        ModelRecord *record = &sequence->records[sequence->wazaIndex];
        if ((((TemplateExpFileHeader *)record)->flags & 0x20) || wazaSequenceJointIndex(active) == 0x10) {
            joint = GSmodelCenterNull(sequence->model);
        } else {
            joint = record->joints[wazaSequenceJointIndex(active)];
        }
    } else {
        joint = GSmodelCenterNull(sequence->model);
    }
    cameraSetTargetExt(20000, targetId, joint);
    cameraRefreshTargetPos();
    cameraSetTargetExt(0, 0, -1);
    _wazaSequenceCameraCalculateParams(sequence, fovMask, &params);
    _wazaSequenceCameraSelectMotion(sequence, waza, &params);
    _wazaSequenceCameraDoPosition(sequence, &params, speed, flip);
    _wazaSequenceCameraDoFOV(sequence, &params, fovMask, speed);
    cameraUpdate();
    }
    }
}

static inline u32 GetTargetPart(ModelSequence* ms, WazaSequence* active) {
    u32 part;
    if (ms->model == 0) {
        part = 0;
    } else if (active != 0) {
        ModelRecord* sec = &ms->records[ms->wazaIndex];
        if ((((TemplateExpFileHeader*)sec)->flags & 0x20) || wazaSequenceJointIndex(active) == 0x10) {
            part = (u16)GSmodelCenterNull(ms->model);
        } else {
            part = sec->joints[wazaSequenceJointIndex(active)];
        }
    } else {
        part = GSmodelCenterNull(ms->model);
    }
    return part;
}

static void _battleCameraUpdateWaza(void) {
    ModelSequence* ms;
    CameraFovKey* key = gFOVlist;
    f32 t;
    int i;

    if (wazaSequenceSysIsValidWaza(gActiveWazaSequenceCamera) && wazaSequenceCameraAnim(gActiveWazaSequenceCamera) == 0) {
        ms = gActiveWazaSequenceCamera->owner->type == 1 ? (ModelSequence*)gActiveWazaSequenceCamera->owner : 0;
        {
            f32 frames = 0.5f + GSgfxVideoGetLastRenderTime();
            u16 frameCount = __OSf32tou16(frames);
            u32 part = GetTargetPart(ms, gActiveWazaSequenceCamera);
            if (!(wazaSequenceFlags(gActiveWazaSequenceCamera) & 0x40000000)) {
                void* partObj = GSmodelGetPart(ms->model, part);
                if (partObj != 0) {
                    GSvec ofs;
                    GSvec cur;
                    GSpartGetTransform(partObj, &ofs, 0, 0);
                    ms->NullSequence::GetPosition(&cur);
                    PSVECSubtract(&ofs, &cur, &ofs);
                    cameraMoveTargetOfs(7, &ofs, 0.25f);
                    GSpartFree(partObj);
                }
            }
            t = gCurrentFOVTime + (f32)frameCount / (f32)GSgfxVideoGetVsyncRate();
            gCurrentFOVTime = t;
        }
        for (i = 0; i < 2; i++, key++) {
            if (t <= key->startTime) {
                gCurrentFOV = key->startFov;
                break;
            }
            if (t <= key->endTime) {
                gCurrentFOV = GSlerpGetLinearInterpolationFloat(key->startFov, key->endFov,
                                                                (t - key->startTime) / (key->endTime - key->startTime));
                break;
            }
            gCurrentFOV = key->endFov;
        }
        cameraSetFov(gCurrentFOV);
    }
}
