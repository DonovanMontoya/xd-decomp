/* XD TEV expression simplification, merging, and range propagation. */
#include "game/maximum/GSAPI/baselib/texpopt.h"
#define bool int
#define false 0
#define true 1
static int SimplifySrc(HSD_TExp*);
static int SimplifyThis(HSD_TExp*);
static int SimplifyByMerge(HSD_TExp*);
static void CalcTevRange(HSD_TExp*);
static HSD_TEArg TE_ARG_ZERO = { 0x00, 0x07, 0xFF };

static int SimplifySrc(HSD_TExp* arg0)
{
    int i;
    bool result;

    result = false;
    i = 0;

    for (; i < 4; i++) {
        if (arg0->tev.c_in[i].type == HSD_TE_TEV) {
            HSD_TExp* src = arg0->tev.c_in[i].exp;
            u8 sel = arg0->tev.c_in[i].sel;
            if (HSD_TExpSimplify(src) != 0) {
                result = true;
            }
            if (sel == HSD_TE_RGB) {
                switch (src->tev.c_op) {
                case 0xFF:
                    HSD_TExpUnref(src, sel);
                    result = true;
                    arg0->tev.c_in[i] = TE_ARG_ZERO;
                    break;
                case GX_TEV_ADD:
                    if (src->tev.c_in[0].sel == HSD_TE_0 &&
                        src->tev.c_in[1].sel == HSD_TE_0 &&
                        src->tev.c_bias == 0 && src->tev.c_scale == 0)
                    {
                        switch (src->tev.c_in[3].type) {
                        case HSD_TE_IMM:
                            arg0->tev.c_in[i] = src->tev.c_in[3];
                            HSD_TExpRef(arg0->tev.c_in[i].exp, arg0->tev.c_in[i].sel);
                            HSD_TExpUnref(src, sel);
                            result = true;
                            break;
                        case HSD_TE_TEV:
                            if (i == 3 && src->tev.c_clamp != 0 && src->tev.c_range == 1) break;
                            arg0->tev.c_in[i] = src->tev.c_in[3];
                            HSD_TExpRef(arg0->tev.c_in[i].exp, arg0->tev.c_in[i].sel);
                            HSD_TExpUnref(src, sel);
                            result = true;
                            break;
                        case HSD_TE_TEX:
                            if ((arg0->tev.tex == NULL ||
                                 arg0->tev.tex == src->tev.tex) &&
                                (arg0->tev.tex_swap == 0xFF ||
                                 src->tev.tex_swap == 0xFF ||
                                 arg0->tev.tex_swap == src->tev.tex_swap))
                            {
                                arg0->tev.c_in[i] = src->tev.c_in[3];
                                arg0->tev.tex = src->tev.tex;
                                if (arg0->tev.tex_swap == 0xFF) {
                                    arg0->tev.tex_swap = src->tev.tex_swap;
                                }
                                HSD_TExpUnref(src, sel);
                                result = true;
                            }
                            break;
                        case HSD_TE_RAS:
                            if ((arg0->tev.chan == 0xFF ||
                                 arg0->tev.chan == src->tev.chan) &&
                                (arg0->tev.ras_swap == 0xFF ||
                                 src->tev.ras_swap == 0xFF ||
                                 arg0->tev.ras_swap == src->tev.ras_swap))
                            {
                                arg0->tev.c_in[i] = src->tev.c_in[3];
                                arg0->tev.chan = src->tev.chan;
                                if (arg0->tev.ras_swap == 0xFF) {
                                    arg0->tev.ras_swap = src->tev.ras_swap;
                                }
                                HSD_TExpUnref(src, sel);
                                result = true;
                            }
                            break;
                        }
                    }
                    break;
                }
            } else {
                switch (src->tev.a_op) {
                case GX_TEV_ADD:
                    break;
                case 0xFF:
                    HSD_TExpUnref(src, sel);
                    result = true;
                    arg0->tev.c_in[i] = TE_ARG_ZERO;
                    break;
                }
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (arg0->tev.a_in[i].type == HSD_TE_TEV) {
            HSD_TExp* src = arg0->tev.a_in[i].exp;
            u8 sel = arg0->tev.a_in[i].sel;
            HSD_TExpSimplify(src);
            switch (src->tev.a_op) {
            case 0xFF:
                HSD_TExpUnref(src, sel);
                result = true;
                arg0->tev.a_in[i] = TE_ARG_ZERO;
                break;
            case GX_TEV_ADD:
                if (src->tev.a_in[0].sel == HSD_TE_0 &&
                    src->tev.a_in[1].sel == HSD_TE_0 && src->tev.a_bias == 0 &&
                    src->tev.a_scale == 0)
                {
                    switch (src->tev.a_in[3].type) {
                    case HSD_TE_IMM:
                        arg0->tev.a_in[i] = src->tev.a_in[3];
                        HSD_TExpRef(arg0->tev.a_in[i].exp, arg0->tev.a_in[i].sel);
                        HSD_TExpUnref(src, sel);
                        result = true;
                        /* fall through */
                    case HSD_TE_TEV:
                        if (i == 3 && src->tev.a_clamp != 0 && src->tev.a_range == 1) break;
                        arg0->tev.a_in[i] = src->tev.a_in[3];
                        HSD_TExpRef(arg0->tev.a_in[i].exp,
                                    arg0->tev.a_in[i].sel);
                        HSD_TExpUnref(src, sel);
                        result = true;
                        break;
                    case HSD_TE_TEX:
                        if (arg0->tev.tex == NULL ||
                            arg0->tev.tex == src->tev.tex)
                        {
                            arg0->tev.a_in[i] = src->tev.a_in[3];
                            arg0->tev.tex = src->tev.tex;
                            HSD_TExpUnref(src, sel);
                            result = true;
                        }
                        break;
                    case HSD_TE_RAS:
                        if (arg0->tev.chan == 0xFF ||
                            arg0->tev.chan == src->tev.chan)
                        {
                            arg0->tev.a_in[i] = src->tev.a_in[3];
                            arg0->tev.chan = src->tev.chan;
                            HSD_TExpUnref(src, sel);
                            result = true;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    return result;
}

#define CLEAR_ARG(arg)                                                        \
    do {                                                                      \
        (arg) = TE_ARG_ZERO;                                         \
    } while (0)

#define BIAS_TO_INT(bias) ((bias) == 1 ? 1 : ((bias) == 2 ? -1 : 0))
#define INT_TO_BIAS(v) ((v) == 1 ? 1 : ((v) == -1 ? 2 : 0))
#define RESOURCE_CONFLICT(tex_obj, chan_id, src_exp)                          \
    ((((tex_obj) != NULL) && ((src_exp)->tev.tex != NULL) &&                  \
      ((tex_obj) != (src_exp)->tev.tex)) ||                                   \
     (((chan_id) != 0xFF) && ((src_exp)->tev.chan != 0xFF) &&                 \
      ((chan_id) != (src_exp)->tev.chan)))

static int SimplifyThis(HSD_TExp* arg0)
{
    int i;
    int color_tex;
    int alpha_tex;
    int color_ras;
    int alpha_ras;
    int result;
    int changed;
    int op;

    result = 0;
    do {
        color_tex = -1;
        alpha_tex = -1;
        color_ras = -1;
        alpha_ras = -1;

        for (i = 0; i < 4; i++) {
            switch (arg0->tev.c_in[i].type) {
            case HSD_TE_TEX:
                color_tex = i;
                break;
            case HSD_TE_RAS:
                color_ras = i;
                break;
            }
            switch (arg0->tev.a_in[i].type) {
            case HSD_TE_TEX:
                alpha_tex = i;
                break;
            case HSD_TE_RAS:
                alpha_ras = i;
                break;
            }
        }

        if (color_tex == -1 && alpha_tex == -1) {
            arg0->tev.tex = NULL;
            arg0->tev.tex_swap = 0xFF;
        }
        if (color_ras == -1 && alpha_ras == -1) {
            arg0->tev.chan = 0xFF;
            arg0->tev.ras_swap = 0xFF;
        }

        changed = 0;
        if (arg0->tev.a_op == 0xFF || arg0->tev.a_op == 0xE ||
            arg0->tev.a_op == 0xF || (arg0->tev.a_op == 0 || arg0->tev.a_op == 1))
        {
            if (arg0->tev.c_op != 0xFF && arg0->tev.c_ref == 0) {
                arg0->tev.c_op = 0xFF;
                for (i = 0; i < 4; i++) {
                    HSD_TExpUnref(arg0->tev.c_in[i].exp,
                                  arg0->tev.c_in[i].sel);
                    arg0->tev.c_in[i] = TE_ARG_ZERO;
                }
                changed = 1;
            }

            switch (arg0->tev.c_op) {
            case 0:
            case 1:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    if (arg0->tev.c_in[1].sel != HSD_TE_0) {
                        HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                      arg0->tev.c_in[1].sel);
                        changed = 1;
                        CLEAR_ARG(arg0->tev.c_in[1]);
                    }
                    if (arg0->tev.c_op == 0 &&
                        arg0->tev.c_in[3].sel == HSD_TE_0)
                    {
                        changed = 1;
                        arg0->tev.c_in[3] = arg0->tev.c_in[0];
                        CLEAR_ARG(arg0->tev.c_in[0]);
                        arg0->tev.c_clamp = 1;
                    }
                }
                if (arg0->tev.c_in[2].sel == HSD_TE_1) {
                    if (arg0->tev.c_in[0].sel != HSD_TE_0) {
                        HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                      arg0->tev.c_in[0].sel);
                        changed = 1;
                        CLEAR_ARG(arg0->tev.c_in[0]);
                    }
                    if (arg0->tev.c_op == 0 &&
                        arg0->tev.c_in[3].sel == HSD_TE_0)
                    {
                        changed = 1;
                        arg0->tev.c_in[3] = arg0->tev.c_in[1];
                        CLEAR_ARG(arg0->tev.c_in[1]);
                        CLEAR_ARG(arg0->tev.c_in[2]);
                    }
                }
                if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                arg0->tev.c_in[1].sel == HSD_TE_1) {
                arg0->tev.c_in[0] = arg0->tev.c_in[2];
                CLEAR_ARG(arg0->tev.c_in[1]);
                CLEAR_ARG(arg0->tev.c_in[2]);
                changed = 1;
            }
            if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                    arg0->tev.c_in[1].sel == HSD_TE_0 &&
                    arg0->tev.c_in[3].sel == HSD_TE_0 && arg0->tev.c_bias == 0)
                {
                    arg0->tev.c_op = 0xFF;
                    HSD_TExpUnref(arg0->tev.c_in[2].exp,
                                  arg0->tev.c_in[2].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            case 8:
            case 10:
            case 12:
            case 14:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                  arg0->tev.c_in[0].sel);
                    CLEAR_ARG(arg0->tev.c_in[0]);
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[1]);
                } else if (arg0->tev.c_in[0].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    CLEAR_ARG(arg0->tev.c_in[1]);
                    HSD_TExpUnref(arg0->tev.c_in[2].exp,
                                  arg0->tev.c_in[2].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            case 9:
            case 11:
            case 13:
            case 15:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                  arg0->tev.c_in[0].sel);
                    CLEAR_ARG(arg0->tev.c_in[0]);
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[1]);
                } else if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                           arg0->tev.c_in[1].sel == HSD_TE_0)
                {
                    arg0->tev.c_op = 0;
                    changed = 1;
                    arg0->tev.c_in[0] = arg0->tev.c_in[2];
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            }
        }

        if (arg0->tev.a_op != 0xFF && arg0->tev.a_ref == 0) {
            arg0->tev.a_op = 0xFF;
            for (i = 0; i < 4; i++) {
                HSD_TExpUnref(arg0->tev.a_in[i].exp, arg0->tev.a_in[i].sel);
                CLEAR_ARG(arg0->tev.a_in[i]);
            }
            changed = 1;
        }

        switch (arg0->tev.a_op) {
        case 0:
        case 1:
            if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                if (arg0->tev.a_in[1].sel != HSD_TE_0) {
                    HSD_TExpUnref(arg0->tev.a_in[1].exp,
                                  arg0->tev.a_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.a_in[1]);
                }
                if (arg0->tev.a_op == 0 && arg0->tev.a_in[3].sel == HSD_TE_0) {
                    changed = 1;
                    arg0->tev.a_in[3] = arg0->tev.a_in[0];
                    CLEAR_ARG(arg0->tev.a_in[0]);
                }
            }
            if (arg0->tev.a_in[2].sel == HSD_TE_1) {
                if (arg0->tev.a_in[0].sel != HSD_TE_0) {
                    HSD_TExpUnref(arg0->tev.a_in[0].exp,
                                  arg0->tev.a_in[0].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.a_in[0]);
                }
                if (arg0->tev.a_op == 0 && arg0->tev.a_in[3].sel == HSD_TE_0) {
                    changed = 1;
                    arg0->tev.a_in[3] = arg0->tev.a_in[1];
                    CLEAR_ARG(arg0->tev.a_in[1]);
                    CLEAR_ARG(arg0->tev.a_in[2]);
                }
            }
            if (arg0->tev.a_in[0].sel == HSD_TE_0 &&
                arg0->tev.a_in[1].sel == HSD_TE_0 &&
                arg0->tev.a_in[3].sel == HSD_TE_0)
            {
                arg0->tev.a_op = 0xFF;
                changed = 1;
            }
            break;

        case 8:
        case 9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
            if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                arg0->tev.a_op = 0;
                HSD_TExpUnref(arg0->tev.a_in[0].exp, arg0->tev.a_in[0].sel);
                CLEAR_ARG(arg0->tev.a_in[0]);
                HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
                changed = 1;
                CLEAR_ARG(arg0->tev.a_in[1]);
            }
            break;

        case 0xE:
            if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                arg0->tev.a_op = 0;
                HSD_TExpUnref(arg0->tev.a_in[0].exp, arg0->tev.a_in[0].sel);
                CLEAR_ARG(arg0->tev.a_in[0]);
                HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
                changed = 1;
                CLEAR_ARG(arg0->tev.a_in[1]);
            } else if (arg0->tev.a_in[0].sel == HSD_TE_0) {
                arg0->tev.a_op = 0;
                HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
                CLEAR_ARG(arg0->tev.a_in[1]);
                HSD_TExpUnref(arg0->tev.a_in[2].exp, arg0->tev.a_in[2].sel);
                changed = 1;
                CLEAR_ARG(arg0->tev.a_in[2]);
            }
            break;

        case 0xF:
            if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                arg0->tev.a_op = 0;
                HSD_TExpUnref(arg0->tev.a_in[0].exp, arg0->tev.a_in[0].sel);
                CLEAR_ARG(arg0->tev.a_in[0]);
                HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
                changed = 1;
                CLEAR_ARG(arg0->tev.a_in[1]);
            } else if (arg0->tev.a_in[0].sel == HSD_TE_0 &&
                       arg0->tev.a_in[1].sel == HSD_TE_0)
            {
                arg0->tev.a_op = 0;
                changed = 1;
                arg0->tev.a_in[0] = arg0->tev.a_in[2];
                CLEAR_ARG(arg0->tev.a_in[2]);
            }
            break;
        }

        if (changed != 0) {
            result = 1;
        }
    } while (changed != 0);

    return result;
}

#define TE_CONFLICT(conflict, p, c)                                           \
    do {                                                                      \
        if ((p)->tev.tex != NULL && (c)->tev.tex != NULL &&                   \
            (p)->tev.tex != (c)->tev.tex)                                     \
        {                                                                     \
            conflict = 1;                                                     \
        } else if ((p)->tev.chan != 0xFF && (c)->tev.chan != 0xFF &&          \
                   (p)->tev.chan != (c)->tev.chan)                            \
        {                                                                     \
            conflict = 1;                                                     \
        } else {                                                              \
            conflict = 0;                                                     \
        }                                                                     \
    } while (0)

static inline int HasCnst_c_in(HSD_TExp* x)
{
    return x->tev.c_in[0].type == HSD_TE_CNST ||
           x->tev.c_in[1].type == HSD_TE_CNST ||
           x->tev.c_in[2].type == HSD_TE_CNST ||
           x->tev.c_in[3].type == HSD_TE_CNST;
}

static inline int HasCnst_a_in(HSD_TExp* x)
{
    return x->tev.a_in[0].type == HSD_TE_CNST ||
           x->tev.a_in[1].type == HSD_TE_CNST ||
           x->tev.a_in[2].type == HSD_TE_CNST ||
           x->tev.a_in[3].type == HSD_TE_CNST;
}

#define TE_HAS_CNST(x, in) HasCnst_##in(x)

static inline int MergeBias(u8 child_bias, int op, u8 bias_in, u8* out)
{
    int bias;

    switch ((s32) child_bias) {
    case 1:
        bias = 1;
        break;
    case 2:
        bias = -1;
        break;
    default:
        bias = 0;
        break;
    }
    if (op == 1) {
        bias = -bias;
    }
    switch ((s32) bias_in) {
    case 1:
        bias += 1;
        break;
    case 2:
        bias -= 1;
        break;
    }
    switch (bias) {
    case 0:
        *out = 0;
        return 1;
    case 1:
        *out = 1;
        return 1;
    case -1:
        *out = 2;
        return 1;
    }
    return 0;
}

static inline int ScaleHalves(u8 scale)
{
    switch ((s32) scale) {
    case 0:
        return 2;
    case 1:
        return 4;
    case 2:
        return 8;
    case 3:
        return 1;
    }
    return 2;
}

static inline int MergeScale(u8 parent, u8 child, u8* out)
{
    int parent_scale = ScaleHalves(parent);
    int child_scale = ScaleHalves(child);
    int combined = (parent_scale * child_scale) / 2;

    switch (combined) {
    case 1:
        *out = 3;
        break;
    case 2:
        *out = 0;
        break;
    case 4:
        *out = 1;
        break;
    case 8:
        *out = 2;
        break;
    default:
        return 0;
    }
    return 1;
}

static int SimplifyByMerge(HSD_TExp* arg0)
{
    HSD_TExp* child;
    int result;
    int merged;
    int i;
    int conflict;
    u8 child_sel;
    u8 out_bias;
    u8 out_scale;
    HSD_TEArg swap_c;
    HSD_TEArg swap_a;

    result = 0;
    do {
        merged = 0;

        if ((arg0->tev.c_op == 0 || arg0->tev.c_op == 1) &&
            arg0->tev.c_in[2].sel == HSD_TE_0)
        {
            child = arg0->tev.c_in[0].exp;
            child_sel = arg0->tev.c_in[0].sel;
            if (arg0->tev.c_in[0].type == HSD_TE_TEV &&
                arg0->tev.c_in[0].sel == HSD_TE_RGB &&
                child->tev.c_range == 0 && child->tev.c_in[3].sel == HSD_TE_0)
            {
                TE_CONFLICT(conflict, arg0, child);
                if (conflict == 0 &&
                    !(TE_HAS_CNST(arg0, c_in) && TE_HAS_CNST(child, c_in)))
                {
                    goto merge_c1;
                }
            }
            child = arg0->tev.c_in[3].exp;
            child_sel = arg0->tev.c_in[3].sel;
            if (arg0->tev.c_op != 0 || arg0->tev.c_in[3].type != HSD_TE_TEV ||
                arg0->tev.c_in[3].sel != HSD_TE_RGB ||
                child->tev.c_range != 0 || child->tev.c_in[3].sel != HSD_TE_0)
            {
                goto end_c1;
            }
            TE_CONFLICT(conflict, arg0, child);
            if (conflict != 0) {
                goto end_c1;
            }
            if (TE_HAS_CNST(arg0, c_in) && TE_HAS_CNST(child, c_in)) {
                goto end_c1;
            }
            if (arg0->tev.c_in[0].type == HSD_TE_TEV) {
                if (arg0->tev.c_in[0].sel == HSD_TE_RGB) {
                    if (arg0->tev.c_in[0].exp->tev.c_range != 0 &&
                        arg0->tev.c_in[0].exp->tev.c_clamp != 1)
                    {
                        goto end_c1;
                    }
                } else if (arg0->tev.c_in[0].exp->tev.a_range != 0 &&
                           arg0->tev.c_in[0].exp->tev.a_clamp != 1)
                {
                    goto end_c1;
                }
            }
            swap_c = arg0->tev.c_in[0];
            arg0->tev.c_in[0] = arg0->tev.c_in[3];
            arg0->tev.c_in[3] = swap_c;
        merge_c1:
            if (child->tev.c_scale == 0) {
                if (!MergeBias(child->tev.c_bias, arg0->tev.c_op,
                               arg0->tev.c_bias, &out_bias))
                {
                    goto end_c1;
                }
                out_scale = arg0->tev.c_scale;
            } else {
                if (arg0->tev.c_in[3].sel != HSD_TE_0 ||
                    arg0->tev.c_bias != 0)
                {
                    goto end_c1;
                }
                if (!MergeScale(arg0->tev.c_scale, child->tev.c_scale,
                                &out_scale))
                {
                    goto end_c1;
                }
                out_bias = child->tev.c_bias;
            }
            {
                if (arg0->tev.c_op == 1) {
                    arg0->tev.c_op = child->tev.c_op == 0;
                } else {
                    arg0->tev.c_op = child->tev.c_op;
                }
                for (i = 0; i < 3; i++) {
                    arg0->tev.c_in[i] = child->tev.c_in[i];
                    HSD_TExpRef(arg0->tev.c_in[i].exp, arg0->tev.c_in[i].sel);
                }
                arg0->tev.c_bias = out_bias;
                arg0->tev.c_scale = out_scale;
                HSD_TExpUnref(child, child_sel);
                if (arg0->tev.tex == NULL) {
                    arg0->tev.tex = child->tev.tex;
                }
                if (arg0->tev.chan == 0xFF) {
                    arg0->tev.chan = child->tev.chan;
                }
                if (arg0->tev.tex_swap == 0xFF) {
                    arg0->tev.tex_swap = child->tev.tex_swap;
                }
                if (arg0->tev.ras_swap == 0xFF) {
                    arg0->tev.ras_swap = child->tev.ras_swap;
                }
                merged = 1;
            }
        }
    end_c1:

        child = arg0->tev.c_in[3].exp;
        child_sel = arg0->tev.c_in[3].sel;
        if (arg0->tev.c_in[3].type == HSD_TE_TEV &&
            child_sel == HSD_TE_RGB) {
            TE_CONFLICT(conflict, arg0, child);
            if (conflict == 0 &&
                !(TE_HAS_CNST(arg0, c_in) && TE_HAS_CNST(child, c_in)))
            {
                if (child->tev.c_range != 0 && child->tev.c_clamp == 1) {
                    if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                        arg0->tev.c_in[2].sel == HSD_TE_0 &&
                        arg0->tev.c_bias == 0 && arg0->tev.c_scale != 3)
                    {
                        if (MergeScale(arg0->tev.c_scale, child->tev.c_scale,
                                       &out_scale))
                        {
                            merged = 1;
                            arg0->tev.c_bias = child->tev.c_bias;
                            arg0->tev.c_scale = out_scale;
                            if (arg0->tev.c_clamp != 1) {
                                arg0->tev.c_clamp = child->tev.c_clamp;
                            }
                            if (arg0->tev.tex == NULL) {
                                arg0->tev.tex = child->tev.tex;
                            }
                            if (arg0->tev.chan == 0xFF) {
                                arg0->tev.chan = child->tev.chan;
                            }
                            if (arg0->tev.tex_swap == 0xFF) {
                                arg0->tev.tex_swap = child->tev.tex_swap;
                            }
                            if (arg0->tev.ras_swap == 0xFF) {
                                arg0->tev.ras_swap = child->tev.ras_swap;
                            }
                            for (i = 0; i < 4; i++) {
                                HSD_TExp* old_exp = arg0->tev.c_in[i].exp;
                                u8 old_sel = arg0->tev.c_in[i].sel;
                                arg0->tev.c_in[i] = child->tev.c_in[i];
                                HSD_TExpRef(arg0->tev.c_in[i].exp,
                                            arg0->tev.c_in[i].sel);
                                HSD_TExpUnref(old_exp, old_sel);
                            }
                        }
                    }
                } else {
                    if (!(arg0->tev.a_op == 0xFF || arg0->tev.a_op == 0xE ||
                          arg0->tev.a_op == 0xF || arg0->tev.a_op <= 1))
                    {
                        if (child->tev.c_in[0].sel != HSD_TE_0 ||
                            child->tev.c_in[1].sel != HSD_TE_0 ||
                            child->tev.c_in[2].sel != HSD_TE_0)
                        {
                            goto end_c2;
                        }
                    }
                    if (child->tev.c_scale == 0) {
                        if (!(arg0->tev.c_in[0].sel == HSD_TE_0 &&
                              arg0->tev.c_in[2].sel == HSD_TE_0))
                        {
                            if (!(child->tev.c_in[0].sel == HSD_TE_0 &&
                                  child->tev.c_in[2].sel == HSD_TE_0))
                            {
                                goto end_c2;
                            }
                        }
                        if (!MergeBias(child->tev.c_bias, 0, arg0->tev.c_bias,
                                       &out_bias))
                        {
                            goto end_c2;
                        }
                        out_scale = arg0->tev.c_scale;
                    } else {
                        if (!(arg0->tev.c_in[0].sel == HSD_TE_0 &&
                               arg0->tev.c_in[1].sel == HSD_TE_0 &&
                               arg0->tev.c_in[2].sel == HSD_TE_0 &&
                              arg0->tev.c_bias == 0))
                        {
                            goto end_c2;
                        }
                        if (!MergeScale(arg0->tev.c_scale, child->tev.c_scale,
                                        &out_scale))
                        {
                            goto end_c2;
                        }
                        out_bias = child->tev.c_bias;
                    }
                    {
                        merged = 1;
                        arg0->tev.c_in[3] = child->tev.c_in[3];
                        HSD_TExpRef(arg0->tev.c_in[3].exp,
                                    arg0->tev.c_in[3].sel);
                        arg0->tev.c_bias = out_bias;
                        arg0->tev.c_scale = out_scale;
                        if (arg0->tev.tex == NULL) {
                            arg0->tev.tex = child->tev.tex;
                        }
                        if (arg0->tev.chan == 0xFF) {
                            arg0->tev.chan = child->tev.chan;
                        }
                        if (arg0->tev.tex_swap == 0xFF) {
                            arg0->tev.tex_swap = child->tev.tex_swap;
                        }
                        if (arg0->tev.ras_swap == 0xFF) {
                            arg0->tev.ras_swap = child->tev.ras_swap;
                        }
                        if (!(child->tev.c_in[0].sel == HSD_TE_0 &&
                              child->tev.c_in[1].sel == HSD_TE_0 &&
                              child->tev.c_in[2].sel == HSD_TE_0))
                        {
                            for (i = 0; i < 3; i++) {
                                HSD_TExp* old_exp = arg0->tev.c_in[i].exp;
                                u8 old_sel = arg0->tev.c_in[i].sel;
                                arg0->tev.c_in[i] = child->tev.c_in[i];
                                HSD_TExpRef(arg0->tev.c_in[i].exp,
                                            arg0->tev.c_in[i].sel);
                                HSD_TExpUnref(old_exp, old_sel);
                            }
                        }
                        HSD_TExpUnref(child, child_sel);
                    }
                }
            }
        }
    end_c2:

        if ((arg0->tev.a_op == 0 || arg0->tev.a_op == 1) &&
            arg0->tev.a_in[2].sel == HSD_TE_0)
        {
            child = arg0->tev.a_in[0].exp;
            child_sel = arg0->tev.a_in[0].sel;
            if (arg0->tev.a_in[0].type == HSD_TE_TEV &&
                child->tev.a_range == 0 && child->tev.a_in[3].sel == HSD_TE_0)
            {
                TE_CONFLICT(conflict, arg0, child);
                if (conflict == 0 &&
                    !(TE_HAS_CNST(arg0, a_in) && TE_HAS_CNST(child, a_in)))
                {
                    goto merge_a1;
                }
            }
            child = arg0->tev.a_in[3].exp;
            child_sel = arg0->tev.a_in[3].sel;
            if (arg0->tev.a_op != 0 || arg0->tev.a_in[3].type != HSD_TE_TEV ||
                child->tev.a_range != 0 || child->tev.a_in[3].sel != HSD_TE_0)
            {
                goto end_a1;
            }
            TE_CONFLICT(conflict, arg0, child);
            if (conflict != 0) {
                goto end_a1;
            }
            if (TE_HAS_CNST(child, a_in) && TE_HAS_CNST(child, a_in)) {
                goto end_a1;
            }
            if (arg0->tev.a_in[0].type == HSD_TE_TEV) {
                if (arg0->tev.a_in[0].exp->tev.a_range != 0 &&
                    arg0->tev.a_in[0].exp->tev.a_clamp != 1)
                {
                    goto end_a1;
                }
            }
            swap_a = arg0->tev.a_in[0];
            arg0->tev.a_in[0] = arg0->tev.a_in[3];
            arg0->tev.a_in[3] = swap_a;
        merge_a1:
            if (child->tev.a_scale == 0) {
                if (!MergeBias(child->tev.a_bias, arg0->tev.a_op,
                               arg0->tev.a_bias, &out_bias))
                {
                    goto end_a1;
                }
                out_scale = arg0->tev.a_scale;
            } else {
                if (arg0->tev.a_in[3].sel != HSD_TE_0 ||
                    arg0->tev.a_bias != 0)
                {
                    goto end_a1;
                }
                if (!MergeScale(arg0->tev.a_scale, child->tev.a_scale,
                                &out_scale))
                {
                    goto end_a1;
                }
                out_bias = child->tev.a_bias;
            }
            {
                if (arg0->tev.a_op == 1) {
                    arg0->tev.a_op = child->tev.a_op == 0;
                } else {
                    arg0->tev.a_op = child->tev.a_op;
                }
                for (i = 0; i < 3; i++) {
                    arg0->tev.a_in[i] = child->tev.a_in[i];
                    HSD_TExpRef(arg0->tev.a_in[i].exp, arg0->tev.a_in[i].sel);
                }
                arg0->tev.a_bias = out_bias;
                arg0->tev.a_scale = out_scale;
                HSD_TExpUnref(child, child_sel);
                if (arg0->tev.tex == NULL) {
                    arg0->tev.tex = child->tev.tex;
                }
                if (arg0->tev.chan == 0xFF) {
                    arg0->tev.chan = child->tev.chan;
                }
                if (arg0->tev.tex_swap == 0xFF) {
                    arg0->tev.tex_swap = child->tev.tex_swap;
                }
                if (arg0->tev.ras_swap == 0xFF) {
                    arg0->tev.ras_swap = child->tev.ras_swap;
                }
                merged = 1;
            }
        }
    end_a1:

        child = arg0->tev.a_in[3].exp;
        child_sel = arg0->tev.a_in[3].sel;
        if (arg0->tev.a_in[3].type == HSD_TE_TEV) {
            TE_CONFLICT(conflict, arg0, child);
            if (conflict == 0 &&
                !(TE_HAS_CNST(arg0, a_in) && TE_HAS_CNST(child, a_in)))
            {
                if (child->tev.a_range != 0 && child->tev.a_clamp == 1) {
                    if (arg0->tev.a_in[0].sel == HSD_TE_0 &&
                        arg0->tev.a_in[2].sel == HSD_TE_0 &&
                        arg0->tev.a_bias == 0 && arg0->tev.a_scale != 3)
                    {
                        if (MergeScale(arg0->tev.a_scale, child->tev.a_scale,
                                       &out_scale))
                        {
                            merged = 1;
                            arg0->tev.a_bias = child->tev.a_bias;
                            arg0->tev.a_scale = out_scale;
                            if (arg0->tev.a_clamp != 1) {
                                arg0->tev.a_clamp = child->tev.a_clamp;
                            }
                            if (arg0->tev.tex == NULL) {
                                arg0->tev.tex = child->tev.tex;
                            }
                            if (arg0->tev.chan == 0xFF) {
                                arg0->tev.chan = child->tev.chan;
                            }
                            if (arg0->tev.tex_swap == 0xFF) {
                                arg0->tev.tex_swap = child->tev.tex_swap;
                            }
                            if (arg0->tev.ras_swap == 0xFF) {
                                arg0->tev.ras_swap = child->tev.ras_swap;
                            }
                            for (i = 0; i < 4; i++) {
                                HSD_TExp* old_exp = arg0->tev.a_in[i].exp;
                                u8 old_sel = arg0->tev.a_in[i].sel;
                                arg0->tev.a_in[i] = child->tev.a_in[i];
                                HSD_TExpRef(arg0->tev.a_in[i].exp,
                                            arg0->tev.a_in[i].sel);
                                HSD_TExpUnref(old_exp, old_sel);
                            }
                        }
                    }
                } else {

                    if (child->tev.a_scale == 0) {
                        if (!(arg0->tev.a_in[0].sel == HSD_TE_0 &&
                              arg0->tev.a_in[2].sel == HSD_TE_0))
                        {
                            if (!(child->tev.a_in[0].sel == HSD_TE_0 &&
                                  child->tev.a_in[2].sel == HSD_TE_0))
                            {
                                goto end_a2;
                            }
                        }
                        if (!MergeBias(child->tev.a_bias, 0, arg0->tev.a_bias,
                                       &out_bias))
                        {
                            goto end_a2;
                        }
                        out_scale = arg0->tev.a_scale;
                    } else {
                        if (!(arg0->tev.a_in[0].sel == HSD_TE_0 &&
                               arg0->tev.a_in[1].sel == HSD_TE_0 &&
                               arg0->tev.a_in[2].sel == HSD_TE_0 &&
                              arg0->tev.a_bias == 0))
                        {
                            goto end_a2;
                        }
                        if (!MergeScale(arg0->tev.a_scale, child->tev.a_scale,
                                        &out_scale))
                        {
                            goto end_a2;
                        }
                        out_bias = child->tev.a_bias;
                    }
                    {
                        merged = 1;
                        arg0->tev.a_in[3] = child->tev.a_in[3];
                        HSD_TExpRef(arg0->tev.a_in[3].exp,
                                    arg0->tev.a_in[3].sel);
                        arg0->tev.a_bias = out_bias;
                        arg0->tev.a_scale = out_scale;
                        if (arg0->tev.tex == NULL) {
                            arg0->tev.tex = child->tev.tex;
                        }
                        if (arg0->tev.chan == 0xFF) {
                            arg0->tev.chan = child->tev.chan;
                        }
                        if (arg0->tev.tex_swap == 0xFF) {
                            arg0->tev.tex_swap = child->tev.tex_swap;
                        }
                        if (arg0->tev.ras_swap == 0xFF) {
                            arg0->tev.ras_swap = child->tev.ras_swap;
                        }
                        if (!(child->tev.a_in[0].sel == HSD_TE_0 &&
                              child->tev.a_in[1].sel == HSD_TE_0 &&
                              child->tev.a_in[2].sel == HSD_TE_0))
                        {
                            for (i = 0; i < 3; i++) {
                                HSD_TExp* old_exp = arg0->tev.a_in[i].exp;
                                u8 old_sel = arg0->tev.a_in[i].sel;
                                arg0->tev.a_in[i] = child->tev.a_in[i];
                                HSD_TExpRef(arg0->tev.a_in[i].exp,
                                            arg0->tev.a_in[i].sel);
                                HSD_TExpUnref(old_exp, old_sel);
                            }
                        }
                        HSD_TExpUnref(child, child_sel);
                    }
                }
            }
        }
    end_a2:

        if (merged != 0) {
            result = 1;
        }
    } while (merged != 0);

    return result;
}

static void CalcTevRange(HSD_TExp* texp)
{
    int range = 0;
    int i;
    HSD_TExp* src;
    if (texp->tev.c_in[3].sel != HSD_TE_0) {
        switch (HSD_TExpGetType(texp->tev.c_in[3].exp)) {
        case HSD_TE_TEV:
            if (texp->tev.c_in[3].sel == HSD_TE_RGB) {
                src = texp->tev.c_in[3].exp;
                if (src->tev.c_clamp != 1 && src->tev.c_range == 1) {
                    texp->tev.c_range = 1;
                    goto alpha;
                }
                range = 256;
                break;
            } else {
                src = texp->tev.c_in[3].exp;
                if (src->tev.a_clamp != 1 && src->tev.a_range == 1) {
                    texp->tev.c_range = 1;
                    goto alpha;
                }
            }
            range = 256;
            break;
        default:
            range = 256;
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        if (texp->tev.c_in[i].sel != HSD_TE_0) {
            if (texp->tev.c_op == GX_TEV_SUB) {
                texp->tev.c_range = 1;
                goto alpha;
            }
            range += 256;
            break;
        }
    }
    switch (texp->tev.c_bias) {
    case GX_TB_ADDHALF: range += 128; break;
    case GX_TB_SUBHALF: texp->tev.c_range = 1; goto alpha;
    }
    switch (texp->tev.c_scale) {
    case GX_CS_SCALE_2: range *= 2; break;
    case GX_CS_SCALE_4: range *= 4; break;
    case GX_CS_DIVIDE_2: range /= 2; break;
    }
    texp->tev.c_range = range > 256;
alpha:
    range = 0;
    if (texp->tev.a_in[3].sel != HSD_TE_0) {
        switch (HSD_TExpGetType(texp->tev.a_in[3].exp)) {
        case HSD_TE_TEV:
            src = texp->tev.a_in[3].exp;
            if (src->tev.a_clamp != 1 && src->tev.a_range == 1) {
                texp->tev.a_range = 1;
                return;
            }
            range = 256;
            break;
        default:
            range = 256;
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        if (texp->tev.a_in[i].sel != HSD_TE_0) {
            if (texp->tev.a_op == GX_TEV_SUB) {
                texp->tev.a_range = 1;
                return;
            }
            range += 256;
            break;
        }
    }
    switch (texp->tev.a_bias) {
    case GX_TB_ADDHALF: range += 128; break;
    case GX_TB_SUBHALF: texp->tev.a_range = 1; return;
    }
    switch (texp->tev.a_scale) {
    case GX_CS_SCALE_2: range *= 2; break;
    case GX_CS_SCALE_4: range *= 4; break;
    case GX_CS_DIVIDE_2: range /= 2; break;
    }
    texp->tev.a_range = range > 256;
}

int HSD_TExpSimplify(HSD_TExp* texp_)
{
    HSD_TExp* texp = (HSD_TExp*) texp_;
    int res = false;
    if (HSD_TExpGetType(texp) != HSD_TE_TEV) {
        return false;
    }
    if (SimplifySrc(texp) != 0) {
        res = true;
    }
    if (SimplifyThis(texp) != 0) {
        res = true;
    }
    if (SimplifyByMerge(texp) != 0) {
        res = true;
    }
    CalcTevRange(texp);
    return res;
}

int HSD_TExpSimplify2(HSD_TExp* texp_)
{
    HSD_TExp* texp = texp_;
    HSD_TExp* src_exp;
    u8 src_sel;
    HSD_TExp* cursor;
    int i;

    for (i = 0, cursor=texp; i < 4; i++, cursor=(HSD_TExp*)((u8*)cursor+sizeof(HSD_TEArg))) {
        src_exp = cursor->tev.c_in[0].exp;
        src_sel = cursor->tev.c_in[0].sel;
        if (cursor->tev.c_in[0].type == HSD_TE_TEV && src_sel == 1 &&
            IsThroughColor(src_exp))
        {
            switch (src_exp->tev.c_in[3].type) {
            case HSD_TE_KONST:
                if (texp->tev.kcsel == 0xFF) {
                    texp->tev.kcsel = src_exp->tev.kcsel;
                } else if (texp->tev.kcsel != src_exp->tev.kcsel) {
                    break;
                }
                /* fallthrough */
            case HSD_TE_IMM:
                cursor->tev.c_in[0] = src_exp->tev.c_in[3];
                HSD_TExpRef(cursor->tev.c_in[0].exp, cursor->tev.c_in[0].sel);
                HSD_TExpUnref(src_exp, src_sel);
                break;
            }
        }
    }
    for (i = 0, cursor=texp; i < 4; i++, cursor=(HSD_TExp*)((u8*)cursor+sizeof(HSD_TEArg))) {
        src_exp = cursor->tev.a_in[0].exp;
        src_sel = cursor->tev.a_in[0].sel;
        if (cursor->tev.a_in[0].type == HSD_TE_TEV && IsThroughAlpha(src_exp)) {
            switch (src_exp->tev.a_in[3].type) {
            case HSD_TE_KONST:
                if (texp->tev.kasel == 0xFF) {
                    texp->tev.kasel = src_exp->tev.kasel;
                } else if (texp->tev.kasel != src_exp->tev.kasel) {
                    break;
                }
                /* fallthrough */
            case HSD_TE_IMM:
                cursor->tev.a_in[0] = src_exp->tev.a_in[3];
                HSD_TExpRef(cursor->tev.a_in[0].exp, cursor->tev.a_in[0].sel);
                HSD_TExpUnref(src_exp, src_sel);
                break;
            }
        }
    }
    return 0;
}
