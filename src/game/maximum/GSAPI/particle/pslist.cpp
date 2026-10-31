#include "game/maximum/GSAPI/particle/pslist.h"
#define NULL ((void*)0)
PSParticle* activeParticle[16];
static PSParticle* freeParticle;
static s32 sortDirty[16];
static PSParticle* activeParticleXLU[16];


void _psListDelete(PSParticle *arg0, PSParticle *arg1) {
    sortDirty[arg0->link] = 1;
    if (arg1 == NULL) {
        if ((PSParticle *) activeParticle[arg0->link] != arg0) {
            __assert("pslist.c", 0x88, "activeParticle[pp->linkNo] == pp");
        }
        activeParticle[arg0->link] = arg0->next;
    } else {
        if ((PSParticle *) arg1->next != arg0) {
            __assert("pslist.c", 0x8B, "parent->next == pp");
        }
        arg1->next = arg0->next;
    }
    arg0->next = freeParticle;
    freeParticle = arg0;
    numActiveParticles -= 1;
}

PSParticle *_psListGetFirst(s32 arg0) {
    s32 var_r0;

    var_r0 = 0;
    if ((arg0 >= 0) && (arg0 < 0x10)) {
        var_r0 = 1;
    }
    if (var_r0 == 0) {
        __assert("pslist.c", 0x98, "linkNo >= 0 && linkNo < PS_NUM_LINK");
    }
    return activeParticle[arg0];
}

PSParticle *_psListNew(PSParticle *arg0, s32 arg1) {
    PSParticle *temp_r3;
    PSParticle *temp_r3_2;
    u16 temp_r4;

    if ((PSParticle *) freeParticle == NULL) {
        temp_r3_2 = HSD_Alloc(0x94U);
        freeParticle = temp_r3_2;
        memset(temp_r3_2, 0, 0x94U);
    }
    temp_r3 = freeParticle;
    if ((PSParticle *) freeParticle == NULL) {
        return NULL;
    }
    temp_r4 = numActiveParticles + 1;
    numActiveParticles = temp_r4;
    if (temp_r4 > (u16) numPeakParticles) {
        numPeakParticles = temp_r4;
    }
    freeParticle = temp_r3->next;
    if (arg0 == NULL) {
        temp_r3->next = activeParticle[arg1];
        activeParticle[arg1] = temp_r3;
    } else {
        temp_r3->next = arg0->next;
        arg0->next = temp_r3;
    }
    sortDirty[arg1] = 1;
    return temp_r3;
}

void _psListClear(void) {
    PSParticle* node = freeParticle;
    PSParticle* next;
    s32 i;
    while (node != NULL) {
        next = node->next;
        HSD_Free(node);
        node = next;
    }
    freeParticle = NULL;
    for (i = 0; i < 16; i++) {
        node = activeParticle[i];
        while (node != NULL) {
            next = node->next;
            HSD_Free(node);
            node = next;
        }
        activeParticle[i] = NULL;
        sortDirty[i] = 0;
        activeParticleXLU[i] = NULL;
    }
}

s32 _psLinkInit(s32 count) {
    s32 i; u32 j; PSParticle* pp;
    for (j = 0; j < 16; j++) {
        activeParticle[j] = NULL; sortDirty[j] = 0; activeParticleXLU[j] = NULL;
    }
    freeParticle = NULL;
    for (i = count - 1; i >= 0; i--) {
        pp = HSD_Alloc(0x94); memset(pp, 0, 0x94);
        if (pp == NULL) return -1;
        pp->next = freeParticle; freeParticle = pp;
    }
    return i;
}


PSParticle* particleSort(s32 linkNo, PSParticle** texEdge, PSParticle** xlu)
{
    struct Bucket { PSParticle* head; PSParticle* tail; };
    struct Bucket buckets[16];
    PSParticle* pp;
    PSParticle* next;
    PSParticle* head0;
    PSParticle* head1;
    PSParticle** tail0;
    PSParticle** tail1;
    PSParticle* result;
    s32 idx;
    s32 i;

    pp = activeParticle[linkNo];
    if (sortDirty[linkNo] == 0) {
        if (pp == NULL) {
            *texEdge = NULL;
            *xlu = NULL;
            return NULL;
        }
        if (pp->kind & 8) {
            *texEdge = pp;
        } else {
            *texEdge = NULL;
        }
        *xlu = activeParticleXLU[linkNo];
        return pp;
    }

    sortDirty[linkNo] = 0;
    if (pp == NULL) {
        activeParticleXLU[linkNo] = NULL;
        *texEdge = NULL;
        *xlu = NULL;
        return NULL;
    }

    memset(buckets, 0, sizeof(buckets));
    idx = ((pp->kind >> 25) & 7) + (((pp->kind & 8) ? 0 : 1) * 8);
    buckets[idx].head = pp;
    for (next = pp->next; next != NULL; next = next->next) {
        if ((pp->kind ^ next->kind) & 0x0E000008) {
            buckets[idx].tail = pp;
            idx = ((next->kind >> 25) & 7) + (((next->kind & 8) ? 0 : 1) * 8);
            if (buckets[idx].head == NULL) {
                buckets[idx].head = next;
            } else {
                buckets[idx].tail->next = next;
            }
        }
        pp = next;
    }
    buckets[idx].tail = pp;

    tail0 = NULL;
    head0 = NULL;
    tail1 = NULL;
    head1 = NULL;
    for (i = 0; i < 8; i++) {
        if (buckets[i].head != NULL) {
            if (head0 == NULL) {
                head0 = buckets[i].head;
            } else {
                *tail0 = buckets[i].head;
            }
            tail0 = &buckets[i].tail->next;
        }
    }
    for (i = 8; i < 16; i++) {
        if (buckets[i].head != NULL) {
            if (head1 == NULL) {
                head1 = buckets[i].head;
            } else {
                *tail1 = buckets[i].head;
            }
            tail1 = &buckets[i].tail->next;
        }
    }

    result = NULL;
    if (tail0 != NULL) {
        result = head0;
        *tail0 = head1;
    }
    if (tail1 != NULL) {
        if (result == NULL) {
            result = head1;
        }
        *tail1 = NULL;
    }
    activeParticle[linkNo] = result;
    activeParticleXLU[linkNo] = head1;
    *texEdge = head0;
    *xlu = head1;
    return result;
}
