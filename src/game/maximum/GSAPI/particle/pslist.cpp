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


PSParticle* particleSort(s32 link, PSParticle** edgeOut, PSParticle** xluOut) {
    struct Bucket { PSParticle* head; PSParticle* tail; } buckets[16];
    PSParticle* current = activeParticle[link];
    PSParticle* next;
    PSParticle* edge = NULL;
    PSParticle* xlu = NULL;
    PSParticle** edgeTail = NULL;
    PSParticle** xluTail = NULL;
    PSParticle* head;
    s32 bucket, i;
    u32 kind;
    if (!sortDirty[link]) {
        if (current == NULL) { *edgeOut=NULL; *xluOut=NULL; return NULL; }
        *edgeOut = (current->kind & 8) ? current : NULL;
        *xluOut = activeParticleXLU[link];
        return current;
    }
    sortDirty[link] = 0;
    if (current == NULL) { activeParticleXLU[link]=NULL; *edgeOut=NULL; *xluOut=NULL; return NULL; }
    memset(buckets, 0, sizeof(buckets));
    kind = current->kind;
    bucket = ((kind >> 25) & 7) + ((((kind >> 3) & 1) ^ 1) * 8);
    buckets[bucket].head = current;
    next = current->next;
    while (next != NULL) {
        if ((current->kind ^ next->kind) & 0x0E000008) {
            buckets[bucket].tail = current;
            kind = next->kind;
            bucket = ((kind >> 25) & 7) + ((((kind >> 3) & 1) ^ 1) * 8);
            if (buckets[bucket].head == NULL) buckets[bucket].head = next;
            else buckets[bucket].tail->next = next;
        }
        current = next; next = next->next;
    }
    buckets[bucket].tail = current;
    for (i=0;i<8;i++) {
        if (buckets[i].head != NULL) {
            if (edge == NULL) edge = buckets[i].head;
            else *edgeTail = buckets[i].head;
            edgeTail = &buckets[i].tail->next;
        }
    }
    for (i=8;i<16;i++) {
        if (buckets[i].head != NULL) {
            if (xlu == NULL) xlu = buckets[i].head;
            else *xluTail = buckets[i].head;
            xluTail = &buckets[i].tail->next;
        }
    }
    head = NULL;
    if (edgeTail != NULL) { head=edge; *edgeTail=xlu; }
    if (xluTail != NULL) { if (head == NULL) head=xlu; *xluTail=NULL; }
    activeParticle[link]=head; activeParticleXLU[link]=xlu;
    *edgeOut=edge; *xluOut=xlu;
    return head;
}
