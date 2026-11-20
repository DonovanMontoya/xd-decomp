#include "game/maximum/GSAPI/particle/generator.h"
#define NULL ((void*)0)
#include "game/maximum/GSAPI/baselib/math_support.h"
f64 __fabs(f64);
static inline f64 fabs(f64 x) { return __fabs(x); }
static inline f32 sinf(f32 x) { return (f32)sin(x); }
static inline f32 cosf(f32 x) { return (f32)cos(x); }
static inline f32 generatorAtan2(f32 y, f32 x) { return (f32)atan2(y, x); }
static void (*psExtExecGenFunc)(PSGenerator*, f32 (*)[4]);
static void (*psExtCreateGenFunc)(PSGenerator*);
static PSCamera* psCamera;
PSGenerator* freeGenerator;
PSGenerator* activeGenerator;
PSGenerator* lastGP;
static void* standbyGenerator;
static u16 psIDNum = 0x100;

static inline int psRefDec(PSCamera *o) {
    int ret;
    if ((ret = (o->references == 0xFFFF))) {
        return ret;
    }
    return o->references-- == 0;
}

static inline void psCameraUnref(PSCamera *cam) {
    if (cam != NULL) {
        if (cam != NULL && psRefDec(cam)) {
            if (cam != NULL) {
                cam->methods->release((PSObject *) cam, cam->methods);
                cam->methods->destroy((PSObject *) cam, cam->methods);
            }
        }
    }
}

static inline void psKillGenNode(PSGenerator *arg0) {
    PSAppSRT *temp_r3;
    PSGenerator *var_r30;

    var_r30 = lastGP;
    if (arg0->type & 0x80) {
        psKillGeneratorChild(arg0);
    }
    if ((u32) arg0->children != 0) {
        var_r30 = arg0;
        arg0->random = 0.0f;
        arg0->life = 1;
    } else if ((arg0->type & 0x3800) && (temp_r3 = arg0->appsrt, temp_r3 != NULL) && ((PSGenerator *) temp_r3->generator == arg0) && ((u16) temp_r3->references != 1)) {
        var_r30 = arg0;
        arg0->random = 0.0f;
        arg0->life = 1;
    } else {
        if (var_r30 == NULL) {
            activeGenerator = arg0->next;
        } else {
            var_r30->next = arg0->next;
        }
        if ((PSAppSRT *) arg0->appsrt != NULL) {
            psRemoveGeneratorAppSRT(arg0);
        }
        arg0->next = freeGenerator;
        freeGenerator = arg0;
        numActiveGenerators -= 1;
    }
    lastGP = var_r30;
}

static inline void psKillGeneratorSub(PSGenerator *arg0) {
    PSGenerator *temp_r0;
    PSGenerator *var_r4;

    var_r4 = activeGenerator;
    lastGP = NULL;
    while (var_r4 != NULL) {
        if (var_r4 == arg0) {
            psKillGenNode(arg0);
            if (lastGP != NULL) {
                while ((temp_r0 = lastGP->next) != NULL) {
                    lastGP = temp_r0;
                }
            } else if ((temp_r0 = activeGenerator) != NULL) {
                lastGP = temp_r0;
                while ((temp_r0 = lastGP->next) != NULL) {
                    lastGP = temp_r0;
                }
            }
            return;
        }
        lastGP = var_r4;
        var_r4 = var_r4->next;
    }
}

static inline PSGenerator *psAllocGenerator(void) {
    PSGenerator *gen;
    PSGenerator *temp_r3;
    PSGenerator *temp_r3_3;

    if (freeGenerator == NULL) {
        temp_r3 = (PSGenerator *) HSD_Alloc(0xB8U);
        freeGenerator = temp_r3;
        memset(temp_r3, 0, 0xB8U);
    }
    gen = freeGenerator;
    if (gen == NULL) {
        gen = NULL;
    } else {
        numActiveGenerators++;
        if (numActiveGenerators > numPeakGenerators) {
            numPeakGenerators = numActiveGenerators;
        }
        freeGenerator = gen->next;
        if ((lastGP == NULL) || (temp_r3_3 = lastGP->next, temp_r3_3 == NULL)) {
            if (activeGenerator == NULL) {
                gen->next = NULL;
                activeGenerator = gen;
            } else {
                gen->next = activeGenerator->next;
                activeGenerator->next = gen;
            }
        } else {
            gen->next = temp_r3_3->next;
            lastGP->next->next = gen;
        }
        if (++psIDNum < 0x100U) {
            psIDNum = 0x100;
        }
        gen->id = psIDNum;
        gen->appsrt = NULL;
        gen->state = 0;
    }
    return gen;
}

u16 psGetNewIDNum(void) {
    if (++psIDNum < 0x100) psIDNum = 0x100;
    return psIDNum;
}

void genPosUpdate(PSGenerator *arg0) {
    PSJObj *temp_r31;
    s32 temp_cr0_eq;
    s32 var_r3;
    u16 temp_r3;
    u32 temp_r4;

    if (arg0 != NULL) {
        temp_r3 = arg0->transformFlags;
        if (!(temp_r3 & 2) && (temp_r3 & 1)) {
            temp_r31 = arg0->jobj;

            if (temp_r31 != NULL) {
                if (temp_r31 != NULL) {
                    if (temp_r31 == NULL) {
                        __assert("jobj.h", 0x25D, "jobj");
                    }
                    temp_r4 = temp_r31->flags;
                    var_r3 = 0;
                    if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                        var_r3 = 1;
                    }
                    if (var_r3 != 0) {
                        HSD_JObjSetupMatrixSub(temp_r31);
                    }
                }
                arg0->position.x = arg0->jobj->matrix[0][3];
                arg0->position.y = arg0->jobj->matrix[1][3];
                arg0->position.z = arg0->jobj->matrix[2][3];
            }
        }
    }
}

void psInitGenerator(s32 count) {
    PSGenerator* gp; s32 i;
    activeGenerator = NULL; freeGenerator = NULL;
    for (i = count - 1; i >= 0; i--) {
        gp = HSD_Alloc(0xB8); memset(gp, 0, 0xB8);
        if (gp == NULL) return;
        gp->next = freeGenerator; freeGenerator = gp;
    }
    numActiveGenerators = 0; numPeakGenerators = 0;
    standbyGenerator = NULL; psCamera = NULL; psExtExecGenFunc = NULL; psExtCreateGenFunc = NULL; lastGP = NULL;
}

void psRemoveGenerator(void) {
    PSGenerator *next;
    PSGenerator *cur;
    PSGenerator *free_cur;

    psKillAllParticle();
    cur = activeGenerator;
    while (cur != NULL) {
        next = cur->next;
        psKillGeneratorSub(cur);
        cur = next;
    }
    while ((void *) standbyGenerator != NULL) {
        standbyGenerator = HSD_SListRemove(standbyGenerator);
    }
    free_cur = freeGenerator;
    while (free_cur != NULL) {
        next = free_cur->next;
        HSD_Free(free_cur);
        free_cur = next;
    }
    freeGenerator = NULL;
    if (psCamera != NULL) {
        psCameraUnref(psCamera);
        psCamera = NULL;
    }
}

#pragma optimization_level 2
void psKillGenerator(PSGenerator *arg0) {
    PSGenerator *temp_r0;
    PSGenerator *var_r4;

    var_r4 = activeGenerator;
    lastGP = NULL;
    while (var_r4 != NULL) {
        if (var_r4 == arg0) {
            psKillGenNode(arg0);
            if (lastGP != NULL) {
                while ((temp_r0 = lastGP->next) != NULL) {
                    lastGP = temp_r0;
                }
            } else if ((temp_r0 = activeGenerator) != NULL) {
                lastGP = temp_r0;
                while ((temp_r0 = lastGP->next) != NULL) {
                    lastGP = temp_r0;
                }
            }
            return;
        }
        lastGP = var_r4;
        var_r4 = var_r4->next;
    }
}
#pragma optimization_level reset

void psKillGeneratorID(u16 arg0) {
    PSAppSRT *temp_r3;
    PSGenerator *var_r30;
    PSGenerator *var_r29;
    PSGenerator *temp_r28;

    var_r29 = activeGenerator;
    lastGP = NULL;
while (var_r29 != NULL) {
        temp_r28 = var_r29->next;
        if ((u16) var_r29->id == arg0) {
            var_r30 = lastGP;
            if (var_r29->type & 0x80) {
                psKillGeneratorChild(var_r29);
            }
            if ((u32) var_r29->children != 0) {
                var_r30 = var_r29;
                var_r29->random = 0.0f;
                var_r29->life = 1;
            } else if ((var_r29->type & 0x3800) && (temp_r3 = var_r29->appsrt, ((temp_r3 == NULL) == 0)) && ((PSGenerator *) temp_r3->generator == var_r29) && ((u16) temp_r3->references != 1)) {
                var_r30 = var_r29;
                var_r29->random = 0.0f;
                var_r29->life = 1;
            } else {
                if (var_r30 == NULL) {
                    activeGenerator = var_r29->next;
                } else {
                    var_r30->next = var_r29->next;
                }
                if ((PSAppSRT *) var_r29->appsrt != NULL) {
                    psRemoveGeneratorAppSRT(var_r29);
                }
                var_r29->next = freeGenerator;
                freeGenerator = var_r29;
                numActiveGenerators -= 1;
            }
            lastGP = var_r30;
        } else {
            lastGP = var_r29;
        }
        var_r29 = temp_r28;
}
}

void psKillAllGenerator(void) {
    PSGenerator *cur;
    PSGenerator *next;

    cur = activeGenerator;
    while (cur != NULL) {
        next = cur->next;
        psKillGeneratorSub(cur);
        cur = next;
    }
    while ((void *) standbyGenerator != NULL) {
        standbyGenerator = HSD_SListRemove(standbyGenerator);
    }
}

f32 generateParticle(PSGenerator* gp)
{
    PSVec vel_copy;
    PSVec emit_pos;
    PSVec tmpvec;
    PSVec vec;
    f32 rot_mtx[3][4];
    f32 mtx_x[3][4];
    f32 mtx_y[3][4];
    f32 mtx_z[3][4];
    PSVec look_dir;
    PSVec cam_up;
    PSVec cross1;
    PSVec vel_norm;
    f32 trig_mtx[3][4];
    f32 cur_angle;
    f32 angle_step;
    f32 scale_x;
    f32 scale_y;
    f32 scale_z;
    f32 vel_mag;
    f32 angle1;
    f32 cone_angle;
    f32 dist;
    f32 radius;
    f32 elevation;
    f32 angle3;

    angle3 = angle1 = 0.0f;
    if (gp->count < 1.0f) {
        return gp->count;
    }

    vel_copy.x = gp->velocity.x;
    vel_copy.y = gp->velocity.y;
    vel_copy.z = gp->velocity.z;
    scale_x = gp->scale.x;
    scale_y = gp->scale.y;
    scale_z = gp->scale.z;
    if ((gp->type & 0xF) == 2 && (gp->transformFlags & 0x80)) {
        vel_copy.x *= scale_x;
        vel_copy.y *= scale_y;
        vel_copy.z *= scale_z;
    }

    vel_mag = hsdSqrt(vel_copy.z * vel_copy.z +
                    (vel_copy.x * vel_copy.x + vel_copy.y * vel_copy.y));

    PSMTXIdentity(rot_mtx);

    if (!(gp->kind & 0x30000)) {
        PSMTXRotRad(mtx_x, 'X', gp->rotation.x);
        PSMTXRotRad(mtx_y, 'Y', gp->rotation.y);
        PSMTXRotRad(mtx_z, 'Z', gp->rotation.z);
        PSMTXConcat(mtx_y, mtx_x, mtx_x);
        PSMTXConcat(mtx_z, mtx_x, mtx_x);

        vec.x = mtx_x[0][0];
        vec.y = mtx_x[1][0];
        vec.z = mtx_x[2][0];
        PSVECNormalize(&vec, &vec);
        rot_mtx[0][0] = vec.x;
        rot_mtx[1][0] = vec.y;
        rot_mtx[2][0] = vec.z;

        vec.x = mtx_x[0][1];
        vec.y = mtx_x[1][1];
        vec.z = mtx_x[2][1];
        PSVECNormalize(&vec, &vec);
        rot_mtx[0][1] = vec.x;
        rot_mtx[1][1] = vec.y;
        rot_mtx[2][1] = vec.z;

        vec.x = mtx_x[0][2];
        vec.y = mtx_x[1][2];
        vec.z = mtx_x[2][2];
        PSVECNormalize(&vec, &vec);
        rot_mtx[0][2] = vec.x;
        rot_mtx[1][2] = vec.y;
        rot_mtx[2][2] = vec.z;

        rot_mtx[2][3] = 0.0f;
        rot_mtx[1][3] = 0.0f;
        rot_mtx[0][3] = 0.0f;
    }

    if (gp->kind & 0x10000) {
        if (psCamera == NULL) {
            __assert("generator.c", 626, "psCamera");
        }
        look_dir.x = psCamera->eye->position.x - gp->position.x;
        look_dir.y = psCamera->eye->position.y - gp->position.y;
        look_dir.z = psCamera->eye->position.z - gp->position.z;
        PSVECNormalize(&look_dir, &look_dir);
        HSD_CObjGetUpVector(psCamera, &cam_up);
        PSVECNormalize(&cam_up, &cam_up);
        PSVECCrossProduct(&cam_up, &look_dir, &cross1);
        PSVECCrossProduct(&look_dir, &cross1, &cam_up);

        rot_mtx[0][0] = cross1.x;
        rot_mtx[1][0] = cross1.y;
        rot_mtx[2][0] = cross1.z;
        rot_mtx[0][1] = cam_up.x;
        rot_mtx[1][1] = cam_up.y;
        rot_mtx[2][1] = cam_up.z;
        rot_mtx[0][2] = look_dir.x;
        rot_mtx[1][2] = look_dir.y;
        rot_mtx[2][2] = look_dir.z;
    }

    if ((gp->type & 0xF) != 1 && vel_mag > __float_epsilon[0]) {
        f32 yaw;
        f32 sin_yaw;
        f32 cos_yaw;
        f32 pitch;
        f32 sin_pitch;
        f32 cos_pitch;

        vel_norm.x = gp->velocity.x;
        vel_norm.y = gp->velocity.y;
        vel_norm.z = gp->velocity.z;
        PSVECNormalize(&vel_norm, &vel_norm);

        if (fabs(vel_norm.z) < __float_min[0]) {
            if (vel_norm.y >= 0.0f) {
                yaw = 1.5707964f;
            } else {
                yaw = -1.5707964f;
            }
        } else {
            yaw = generatorAtan2(vel_norm.y, vel_norm.z);
        }
        sin_yaw = sinf(yaw);
        cos_yaw = cosf(yaw);

        {
            f32 projected_z = vel_norm.y * sin_yaw + vel_norm.z * cos_yaw;

            if (fabs(projected_z) < __float_min[0]) {
                if (vel_norm.x >= 0.0f) {
                    pitch = 1.5707964f;
                } else {
                    pitch = -1.5707964f;
                }
            } else {
                pitch = generatorAtan2(vel_norm.x, projected_z);
            }
        }
        sin_pitch = sinf(pitch);
        cos_pitch = cosf(pitch);

        trig_mtx[0][0] = cos_pitch;
        trig_mtx[0][1] = 0.0f;
        trig_mtx[0][2] = sin_pitch;
        trig_mtx[0][3] = 0.0f;
        trig_mtx[1][0] = -sin_yaw * sin_pitch;
        trig_mtx[1][1] = cos_yaw;
        trig_mtx[1][2] = sin_yaw * cos_pitch;
        trig_mtx[1][3] = 0.0f;
        trig_mtx[2][0] = -cos_yaw * sin_pitch;
        trig_mtx[2][1] = -sin_yaw;
        trig_mtx[2][2] = cos_yaw * cos_pitch;
        trig_mtx[2][3] = 0.0f;
        PSMTXConcat(rot_mtx, trig_mtx, rot_mtx);
    }
    elevation = vel_mag;

    if ((gp->type & 0xF) == 2) {
        if (fabs(rot_mtx[2][2]) < __float_min[0]) {
            if (rot_mtx[1][2] >= 0.0f) {
                angle1 = 1.5707964f;
            } else {
                angle1 = -1.5707964f;
            }
        } else {
            angle1 = generatorAtan2(rot_mtx[1][2], rot_mtx[2][2]);
        }
        {
            f32 comb = rot_mtx[1][2] * sinf(angle1) + rot_mtx[2][2] * cosf(angle1);

            if (fabs(comb) < __float_min[0]) {
                if (rot_mtx[0][2] >= 0.0f) {
                    angle3 = 1.5707964f;
                } else {
                    angle3 = -1.5707964f;
                }
            } else {
                angle3 = generatorAtan2(rot_mtx[0][2], comb);
            }
        }
    }

    if (gp->angle < 0.0f) {
        switch (gp->type & 0xF) {
        case 0:
        case 3:
        case 4: {
            f32 min_a = gp->param1;
            f32 rnd = HSD_Randf();
            f32 step = (gp->param2 - min_a) / (f32) (s32) gp->count;

            angle_step = step;
            cur_angle = step * rnd + min_a;
            break;
        }
        case 6:
        case 7: {
            f32 min_a = gp->param1;
            f32 rnd = HSD_Randf();
            f32 step = (gp->param2 - min_a) / (f32) (s32) gp->count;

            angle_step = step;
            cur_angle = step * rnd + min_a;
            break;
        }
        default:
            cur_angle = (f32) (2.0 * (3.141592653589793 * HSD_Randf()));
            angle_step = (f32) ((2.0 * 3.141592653589793) / (s32) gp->count);
            break;
        }
    }

    while (gp->count >= 1.0f) {
        switch (gp->type & 0xF) {
        case 0:
        case 3:
        case 4:
        case 6:
        case 7:
            if (gp->radius < 0.0f) {
                dist = -gp->radius;
                radius = 1.0f;
            } else {
                radius = HSD_Randf();
                if ((gp->type & 0xF) == 3 || (gp->type & 0xF) == 4) {
                    radius = hsdSqrt(radius);
                }
                dist = radius * gp->radius;
            }

            switch (gp->type & 0xF) {
            case 6:
                if (gp->angle < 0.0f) {
                    cur_angle += angle_step;
                    if (fabs(dist) < __float_min[0]) {
                        if (gp->param3 >= 0.0f) {
                            cone_angle = -gp->angle;
                        } else {
                            cone_angle = (f32) (3.141592653589793 - gp->angle);
                        }
                    } else {
                        cone_angle =
                            (f32) (1.5707963267948966 - generatorAtan2(gp->param3, dist) -
                                   gp->angle);
                    }
                } else {
                    f32 min_angle = gp->param1;

                    cur_angle = (gp->param2 - min_angle) * HSD_Randf() + min_angle;
                    if (fabs(dist) < __float_min[0]) {
                        if (gp->param3 >= 0.0f) {
                            cone_angle = gp->angle;
                        } else {
                            cone_angle = (f32) (3.141592653589793 + gp->angle);
                        }
                    } else {
                        cone_angle =
                            (f32) (gp->angle +
                                   (1.5707963267948966 -
                                    generatorAtan2(gp->param3, dist)));
                    }
                }
                break;
            case 7:
                if (gp->angle < 0.0f) {
                    cone_angle = (f32) (1.5707963267948966 - gp->angle);
                    cur_angle += angle_step;
                } else {
                    cur_angle = gp->param1;
                    cur_angle = (gp->param2 - cur_angle) * HSD_Randf() + cur_angle;
                    cone_angle = (f32) (1.5707963267948966 + gp->angle);
                }
                break;
            default:
                if (gp->angle < 0.0f) {
                    cone_angle = -gp->angle;
                    cur_angle += angle_step;
                    cone_angle = radius * cone_angle;
                } else {
                    cur_angle = gp->param1;
                    cur_angle = (gp->param2 - cur_angle) * HSD_Randf() + cur_angle;
                    cone_angle = radius * gp->angle;
                }
                break;
            }

            emit_pos.x = dist * cosf(cur_angle);
            emit_pos.y = dist * sinf(cur_angle);

            if ((gp->type & 0xF) == 6 || (gp->type & 0xF) == 7) {
                emit_pos.z = HSD_Randf();
                if ((gp->type & 0xF) == 6) {
                    emit_pos.x *= 1.0f - emit_pos.z;
                    emit_pos.y *= 1.0f - emit_pos.z;
                }
                emit_pos.z *= gp->param3;
            } else {
                emit_pos.z = 0.0f;
            }

            {
                f32 sin_ca = elevation * sinf(cone_angle);

                vec.x = sin_ca * cosf(cur_angle);
                vec.y = sin_ca * sinf(cur_angle);
                vec.z = elevation * cosf(cone_angle);
            }

            if ((gp->type & 0xF) == 3) {
                vec.x *= radius;
                vec.y *= radius;
                vec.z *= radius;
            }

            PSMTXMultVec(rot_mtx, &emit_pos, &emit_pos);
            emit_pos.x += gp->position.x;
            emit_pos.y += gp->position.y;
            emit_pos.z += gp->position.z;
            PSMTXMultVec(rot_mtx, &vec, &vec);

            psGenerateParticle(gp->link, gp->bank, 0, gp->kind,
                               gp->texGroup, gp->commands, gp->particleLife,
                               emit_pos.x, emit_pos.y, emit_pos.z,
                               vec.x * scale_x, vec.y * scale_y,
                               vec.z * scale_z, gp->size, gp->gravity,
                               gp->friction, 0, gp);
            break;

        case 1: {
            f32 rnd = HSD_Randf();

            emit_pos.x = rnd * gp->param1;
            emit_pos.y = rnd * gp->param2;
            emit_pos.z = rnd * gp->param3;

            PSMTXMultVec(rot_mtx, &emit_pos, &emit_pos);
            emit_pos.x += gp->position.x;
            emit_pos.y += gp->position.y;
            emit_pos.z += gp->position.z;
            PSMTXMultVec(rot_mtx, &vel_copy, &vec);

            psGenerateParticle(gp->link, gp->bank, 0, gp->kind,
                               gp->texGroup, gp->commands, gp->particleLife,
                               emit_pos.x, emit_pos.y, emit_pos.z,
                               vec.x * scale_x, vec.y * scale_y,
                               vec.z * scale_z, gp->size, gp->gravity,
                               gp->friction, 0, gp);
            break;
        }

        case 2:
            if (gp->radius < 0.0f) {
                dist = 1.0f;
            } else {
                dist = HSD_Randf();
            }
            if (gp->angle < 0.0f) {
                cur_angle += angle_step;
            } else {
                cur_angle = (f32) (2.0 * (3.141592653589793 * HSD_Randf()));
            }
            gp->param1 = elevation;
            psGenerateParticle(gp->link, gp->bank, 0, gp->kind | 4,
                               gp->texGroup, gp->commands, gp->particleLife,
                               0.0f, 0.0f, 0.0f, cur_angle, dist, 0.0f,
                               gp->size, angle1, angle3, 0, gp);
            break;

        case 5:
            emit_pos.x = HSD_Randf();
            emit_pos.y = HSD_Randf();
            emit_pos.z = HSD_Randf();

            switch (gp->edgeFlags) {
            case 0:
                break;
            case 1:
                emit_pos.x = emit_pos.x > 0.5f ? 1.0f : 0.0f;
                break;
            case 2:
                emit_pos.y = emit_pos.y > 0.5f ? 1.0f : 0.0f;
                break;
            case 3: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->param1;

                if (rnd > a2 / (a2 + gp->param2)) {
                    emit_pos.y = emit_pos.y > 0.5f ? 1.0f : 0.0f;
                } else {
                    emit_pos.x = emit_pos.x > 0.5f ? 1.0f : 0.0f;
                }
                break;
            }
            case 4:
                emit_pos.z = emit_pos.z > 0.5f ? 1.0f : 0.0f;
                break;
            case 5: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->param1;

                if (rnd > a2 / (a2 + gp->param3)) {
                    emit_pos.z = emit_pos.z > 0.5f ? 1.0f : 0.0f;
                } else {
                    emit_pos.x = emit_pos.x > 0.5f ? 1.0f : 0.0f;
                }
                break;
            }
            case 6: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->param2;

                if (rnd > a2 / (a2 + gp->param3)) {
                    emit_pos.z = emit_pos.z > 0.5f ? 1.0f : 0.0f;
                } else {
                    emit_pos.y = emit_pos.y > 0.5f ? 1.0f : 0.0f;
                }
                break;
            }
            case 7: {
                f32 rnd = HSD_Randf();
                f32 a2 = gp->param3;
                f32 b2 = gp->param2;
                f32 c2 = gp->param1;
                f32 r0 = 1.0f / (c2 * (b2 + a2) + b2 * a2);

                if (rnd < r0 * (c2 * b2)) {
                    emit_pos.z = emit_pos.z > 0.5f ? 1.0f : 0.0f;
                } else if (rnd > 1.0f - r0 * (c2 * a2)) {
                    emit_pos.y = emit_pos.y > 0.5f ? 1.0f : 0.0f;
                } else {
                    emit_pos.x = emit_pos.x > 0.5f ? 1.0f : 0.0f;
                }
                break;
            }
            }

            emit_pos.x -= 0.5f;
            emit_pos.y -= 0.5f;
            emit_pos.z -= 0.5f;

            tmpvec.x = (gp->axisXX * emit_pos.x + gp->axisYX * emit_pos.y) + gp->axisZX * emit_pos.z;
            tmpvec.y = (gp->axisXY * emit_pos.x + gp->axisYY * emit_pos.y) + gp->axisZY * emit_pos.z;
            tmpvec.z = (gp->axisXZ * emit_pos.x + gp->axisYZ * emit_pos.y) + gp->axisZZ * emit_pos.z;

            PSMTXMultVec(rot_mtx, &tmpvec, &emit_pos);
            emit_pos.x += gp->position.x;
            emit_pos.y += gp->position.y;
            emit_pos.z += gp->position.z;

            {
                f32 mag = hsdSqrt(gp->axisZX * gp->axisZX +
                                gp->axisZY * gp->axisZY +
                                gp->axisZZ * gp->axisZZ);
                f32 scale = elevation / mag;

                vec.x = gp->axisZX * scale;
                vec.y = gp->axisZY * scale;
                vec.z = gp->axisZZ * scale;
            }

            PSMTXMultVec(rot_mtx, &vec, &vec);

            psGenerateParticle(gp->link, gp->bank, 0, gp->kind,
                               gp->texGroup, gp->commands, gp->particleLife,
                               emit_pos.x, emit_pos.y, emit_pos.z,
                               vec.x * scale_x, vec.y * scale_y,
                               vec.z * scale_z, gp->size, gp->gravity,
                               gp->friction, 0, gp);
            break;

        case 8: {
            f32 lat;
            f32 lon;

            if (0.0f == gp->param3) {
                lat = (f32) (3.141592653589793 * HSD_Randf());
            } else {
                lat = gp->param3 * HSD_Randf();
            }
            lon = (f32) (2.0 * (3.141592653589793 * HSD_Randf()));
            {
                f32 r2 = gp->radius;

                if (r2 < 0.0f) {
                    dist = -r2;
                } else {
                    dist = r2 * HSD_Randf();
                }
            }

            vec.x = sinf(lat) * cosf(lon);
            vec.y = sinf(lat) * sinf(lon);
            vec.z = cosf(lat);

            PSMTXMultVec(rot_mtx, &vec, &emit_pos);

            vec.x = emit_pos.x * gp->param1;
            vec.y = emit_pos.y * gp->param1;
            vec.z = emit_pos.z * gp->param1;

            if (gp->radius >= 0.0f && gp->param1 < 0.0f) {
                f32 scale = dist / gp->radius;

                vec.x *= scale;
                vec.y *= scale;
                vec.z *= scale;
            }

            emit_pos.x = dist * emit_pos.x + gp->position.x;
            emit_pos.y = dist * emit_pos.y + gp->position.y;
            emit_pos.z = dist * emit_pos.z + gp->position.z;

            psGenerateParticle(gp->link, gp->bank, 0, gp->kind,
                               gp->texGroup, gp->commands, gp->particleLife,
                               emit_pos.x, emit_pos.y, emit_pos.z,
                               vec.x * scale_x, vec.y * scale_y,
                               vec.z * scale_z, gp->size, gp->gravity,
                               gp->friction, 0, gp);
            break;
        }

        default:
            if (psExtExecGenFunc != 0) {
                psExtExecGenFunc(gp, rot_mtx);
            }
            break;
        }

        gp->count -= 1.0f;
    }

    return gp->count;
}

void psExecGenerator(s32 arg0) {
    PSGenerator *var_r31;
    PSJObj *temp_r29;
    f32 temp_f1;
    s32 temp_cr0_eq;
    s32 var_r3;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 temp_r3_3;
    u32 temp_r4;

while ((void *) standbyGenerator != NULL) {
        standbyGenerator = HSD_SListRemove(standbyGenerator);

}
    var_r31 = activeGenerator;
    lastGP = NULL;
while (var_r31 != NULL) {
        if (arg0 & (1 << (var_r31->link + 0x10))) {
            lastGP = var_r31;
            var_r31 = var_r31->next;
        } else if (var_r31->kind & 0x800) {
            lastGP = var_r31;
            var_r31 = var_r31->next;
        } else {
            if (var_r31 != NULL) {
                temp_r3 = var_r31->transformFlags;
                if (!(temp_r3 & 2) && (temp_r3 & 1)) {
                    temp_r29 = var_r31->jobj;
                    /* null checks below retain the original nested guards */
                    if (temp_r29 != NULL) {
                        if (temp_r29 != NULL) {
                            if (temp_r29 == NULL) {
                                __assert("jobj.h", 0x25D, "jobj");
                            }
                            temp_r4 = temp_r29->flags;
                            var_r3 = 0;
                            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                                var_r3 = 1;
                            }
                            if (var_r3 != 0) {
                                HSD_JObjSetupMatrixSub(temp_r29);
                            }
                        }
                        var_r31->position.x = var_r31->jobj->matrix[0][3];
                        var_r31->position.y = var_r31->jobj->matrix[1][3];
                        var_r31->position.z = var_r31->jobj->matrix[2][3];
                    }
                }
            }
            temp_f1 = var_r31->random;
            if (temp_f1 < 0.0f) {
                var_r31->count -= temp_f1;
            } else {
                var_r31->count += var_r31->random * HSD_Randf();
            }
            if (var_r31->count >= 1.0f) {
                var_r31->count = generateParticle(var_r31);
            }
            if (var_r31->life != 0 && --var_r31->life == 0) {
                if ((u8) var_r31->state == 0) {
                    psKillGenNode(var_r31);
                } else {
                    var_r31->kind |= 0x800;
                }
                if ((PSGenerator *) lastGP != NULL) {
                    var_r31 = lastGP->next;
                } else {
                    var_r31 = activeGenerator;
                }
            } else {
                lastGP = var_r31;
                var_r31 = var_r31->next;
            }
        }
}
}

PSGenerator *psCreateGeneratorID(s32 arg0, s32 arg1, s32 arg2) {
    f32 spC;
    f32 sp8;
    PSAppSRT *temp_r3_10;
    PSCmd *temp_r3_6;
    PSCmd *temp_r3_7;
    PSGenerator *temp_r3;
    PSGenerator *temp_r3_3;
    PSGenerator *var_r29;
    PSTex *temp_r3_5;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f1;
    f32 temp_f1_5;
    f32 temp_f1_9;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f3;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f4;
    f64 temp_f1_2;
    f64 temp_f1_3;
    f64 temp_f1_4;
    f64 temp_f1_6;
    f64 temp_f1_7;
    f64 temp_f1_8;
    s32 temp_r3_8;
    s32 temp_r3_9;
    s32 var_r0;
    s32 var_r0_2;
    u16 temp_r3_2;
    u16 temp_r3_4;
    u32 temp_r0;

    if (arg1 >= 0x40) {
        return NULL;
    }
    if (arg0 >= 8) {
        return NULL;
    }
    if (arg2 >= (s32) psNumCmdList[arg1]) {
        return NULL;
    }
    if ((PSCmd *) psCmdListArray[arg1][arg2] == NULL) {
        return NULL;
    }
    var_r29 = psAllocGenerator();
    if (var_r29 != NULL) {
        var_r29->type = psCmdListArray[arg1][arg2]->type;
        var_r29->bank = (u8) arg1;
        var_r29->link = (u8) arg0;
        var_r29->commandID = (u16) arg2;
        var_r29->camera = 0;
        var_r29->kind = psCmdListArray[arg1][arg2]->kind;
        var_r29->texGroup = (u8) psCmdListArray[arg1][arg2]->texGroup;
        var_r29->particleLife = psCmdListArray[arg1][arg2]->life;
        var_r29->life = psCmdListArray[arg1][arg2]->genLife;
        var_r29->position.z = 0.0f;
        var_r29->position.y = 0.0f;
        var_r29->position.x = 0.0f;
        var_r29->velocity.x = psCmdListArray[arg1][arg2]->velocity.x;
        var_r29->velocity.y = psCmdListArray[arg1][arg2]->velocity.y;
        var_r29->velocity.z = psCmdListArray[arg1][arg2]->velocity.z;
        var_r29->gravity = psCmdListArray[arg1][arg2]->gravity;
        var_r29->friction = psCmdListArray[arg1][arg2]->friction;
        var_r29->size = psCmdListArray[arg1][arg2]->size;
        var_r29->commands = psCmdListArray[arg1][arg2]->commands;
        var_r29->radius = psCmdListArray[arg1][arg2]->radius;
        var_r29->angle = psCmdListArray[arg1][arg2]->angle;
        var_r29->random = psCmdListArray[arg1][arg2]->random;
        if (var_r29->kind & 0x100) {
            temp_f0 = var_r29->random;
            if (temp_f0 < 0.0f) {
                var_f2 = (1.0f + temp_f0) > __float_epsilon[0] ? 1.0f : 0.0f;
                var_r29->count = var_f2;
            } else {
                var_r29->count = 1.0f - __float_epsilon[0];
            }
        } else if (var_r29->random < 0.0f) {
            var_r29->count = 0.0f;
        } else {
            var_r29->count = HSD_Randf();
        }
        temp_r3_5 = psTexGroupArray[arg1][var_r29->texGroup];
        if ((temp_r3_5 != NULL) && ((u16) temp_r3_5->paletteFlags != 0)) {
            var_r29->kind |= 0x10;
        }
        var_r29->children = 0;
        temp_r0 = var_r29->type & 0xF;
        switch (temp_r0) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
        case 3:                                     /* switch 1 */
        case 4:                                     /* switch 1 */
            temp_r3_6 = psCmdListArray[arg1][arg2];
            temp_f2 = temp_r3_6->param1;
            if ((temp_f2 == 0.0f) && (temp_r3_6->param2 == 0.0f)) {
                var_r29->param1 = 0.0f;
                var_r29->param2 = 6.2831855f;
            } else {
                var_r29->param1 = temp_f2;
                var_r29->param2 = psCmdListArray[arg1][arg2]->param2;
            }
            break;
        case 1:                                     /* switch 1 */
            var_r29->param1 = psCmdListArray[arg1][arg2]->param1;
            var_r29->param2 = psCmdListArray[arg1][arg2]->param2;
            var_r29->param3 = psCmdListArray[arg1][arg2]->param3;
            break;
        case 6:                                     /* switch 1 */
        case 7:                                     /* switch 1 */
            temp_r3_7 = psCmdListArray[arg1][arg2];
            temp_f2_2 = temp_r3_7->param1;
            if ((temp_f2_2 == 0.0f) && (temp_r3_7->param2 == 0.0f)) {
                var_r29->param1 = 0.0f;
                var_r29->param2 = 6.2831855f;
            } else {
                var_r29->param1 = temp_f2_2;
                var_r29->param2 = psCmdListArray[arg1][arg2]->param2;
            }
            var_r29->param3 = psCmdListArray[arg1][arg2]->param3;
            break;
        case 5:                                     /* switch 1 */
            temp_f0_2 = psCmdListArray[arg1][arg2]->param1;
            var_r29->param1 = temp_f0_2;
            var_r29->axisXX = temp_f0_2;
            temp_f0_3 = psCmdListArray[arg1][arg2]->param2;
            var_r29->param2 = temp_f0_3;
            var_r29->axisYY = temp_f0_3;
            temp_f0_4 = psCmdListArray[arg1][arg2]->param3;
            var_r29->param3 = temp_f0_4;
            var_r29->axisZZ = temp_f0_4;
            var_r29->axisZY = 0.0f;
            var_r29->axisZX = 0.0f;
            var_r29->axisYZ = 0.0f;
            var_r29->axisYX = 0.0f;
            var_r29->axisXZ = 0.0f;
            var_r29->axisXY = 0.0f;
            var_r29->edgeFlags = 0;
            if (psCmdListArray[arg1][arg2]->param1 < 0.0f) {
                var_r29->edgeFlags |= 1;
            }
            if (psCmdListArray[arg1][arg2]->param2 < 0.0f) {
                var_r29->edgeFlags |= 2;
            }
            if (psCmdListArray[arg1][arg2]->param3 < 0.0f) {
                var_r29->edgeFlags |= 4;
            }
            break;
        case 8:                                     /* switch 1 */
            var_f4 = hsdSqrt(var_r29->velocity.x * var_r29->velocity.x + var_r29->velocity.y * var_r29->velocity.y + var_r29->velocity.z * var_r29->velocity.z);
            var_r29->param1 = var_f4;
            var_f2_2 = hsdSqrt(var_r29->velocity.x * var_r29->velocity.x + var_r29->velocity.z * var_r29->velocity.z);
            if (var_f2_2 < __float_min[0]) {
                if (var_r29->velocity.y >= 0.0f) {
                    var_r29->param2 = 1.5707964f;
                } else {
                    var_r29->param2 = -1.5707964f;
                }
            } else {
                var_r29->param2 = (f32) atan2((f64) var_r29->velocity.y, (f64) var_f2_2);
            }
            temp_f2_4 = var_r29->velocity.x;
            if (__fabs(temp_f2_4) < __float_min[0]) {
                if (var_r29->velocity.z >= 0.0f) {
                    var_r29->axisXX = 1.5707964f;
                } else {
                    var_r29->axisXX = -1.5707964f;
                }
            } else {
                var_r29->axisXX = (f32) atan2((f64) var_r29->velocity.z, (f64) temp_f2_4);
            }
            var_r29->param3 = psCmdListArray[arg1][arg2]->param1;
            temp_f1_9 = var_r29->param3;
            if (temp_f1_9 < 0.0f) {
                var_r29->param3 = -temp_f1_9;
                var_r29->param1 = -var_r29->param1;
            }
            var_r29->axisXY = psCmdListArray[arg1][arg2]->param2;
            break;
        case 2:
            break;
        default:                                    /* switch 1 */
            if (((void (*)(PSGenerator *)) psExtCreateGenFunc) != NULL) {
                psExtCreateGenFunc(var_r29);
            }
            break;
        }
        if (var_r29->kind & 0x20000) {
            var_r29->type |= 0x800;
            psAddGeneratorAppSRT(var_r29, 0);
            temp_r3_10 = var_r29->appsrt;
            if (temp_r3_10 != NULL) {
                temp_r3_10->generatorOwned = 1;
                var_r29->appsrt->generator = var_r29;
            }
        }
        var_r29->transformFlags = 2;
        var_r29->jobj = NULL;
        var_r29->rotation.z = 0.0f;
        var_r29->rotation.y = 0.0f;
        var_r29->rotation.x = 0.0f;
        var_r29->scale.z = 1.0f;
        var_r29->scale.y = 1.0f;
        var_r29->scale.x = 1.0f;
        var_r29->nodeScale.z = 1.0f;
        var_r29->nodeScale.y = 1.0f;
        var_r29->nodeScale.x = 1.0f;
    }
    return var_r29;
}

void psSetBillboardCamera(PSCamera *arg0) {
    if (arg0 != psCamera) {
        psCameraUnref(psCamera);
        if (arg0 != NULL) {
            if (arg0 != NULL) {
                arg0->references++;
                if (arg0->references == 0xFFFF) {
                    __assert("object.h", 0x5D, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
                }
            }
        }
        psCamera = arg0;
    }
}

void psGeneratorSetCamera(PSGenerator *arg0, s32 arg1) {
    arg0->camera = arg1;
}

s32 psGeneratorGetCamera(PSGenerator *arg0) {
    return arg0->camera;
}
