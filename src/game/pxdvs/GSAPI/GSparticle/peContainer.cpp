#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>

void peRenderContainer::ResetSwap() {}
void peRenderContainer::InitSwap() {
    if((displayLists[0].flags&1)==1) {tokens[0]=0;displayLists[0].flags|=2;if((displayLists[1].flags&1)==1){tokens[1]=0;displayLists[1].flags|=2;}}
}
void peRenderContainer::ResolveMultipleSwap() {
    if((displayLists[0].flags&1)==1 && (displayLists[1].flags&1)==1 && swapped) {swapIndex^=1;swapped=0;}
}
void peRenderContainer::MarkForSwap() {
    if((displayLists[0].flags&1)==1) {
        u16 token=g_current_layer->tokenMark();g_bank_token=token;tokens[swapIndex]=token;
        if((displayLists[1].flags&1)==1){swapIndex^=1;swapped=1;}
    }
}
#pragma opt_dead_assignments off
void peRenderContainer::PreUpdate() {
    if(active && (displayLists[0].flags&1)==1) {
        if(tokens[swapIndex]) {GSgfxTokenWaitForClear(tokens[swapIndex]);tokens[swapIndex]=0;}
        if((displayLists[1].flags&1)==1 && swapped) {
            swapped=0;
            if(dirty) {
                u8 current=swapIndex;
                memcpy(displayLists[current].data,displayLists[!current].data,displayLists[0].size);
                u32 flagsOffset=swapIndex*16+40;u16* flags=(u16*)((u32)this+flagsOffset);*flags|=2;dirty=0;
            }
        }
    }
}
#pragma opt_dead_assignments reset
void peContainer::MoveNode(peNode* node,peNode* after) {
    peNode* next=node->next;peNode* previous=node->previous;
    if(next)next->previous=previous;if(previous)previous->next=next;else nodes=next;
    peNode* before=after->previous;after->previous=node;node->next=after;node->previous=before;
    if(before){before->next=node;return;}nodes=node;
}
void peContainer::RemoveAll() {
    peNode* node=nodes;if(!node)return;
    while(node->next)node=node->next;
    peNode* free=freeNodes;node->next=free;if(free)free->previous=node;
    freeNodes=nodes;nodes=0;count=0;dirty=1;
}
void peContainer::RemoveNode(peNode* node) {
    peNode* next=node->next;peNode* previous=node->previous;
    if(next)next->previous=previous;if(previous)previous->next=next;else nodes=next;
    node->previous=0;peNode* free=freeNodes;node->next=free;if(free)free->previous=node;
    freeNodes=node;--count;dirty=1;
}
u16 peContainer::CreateNodes(u16 requested) {
    peNode* next;
    peNode* first=freeNodes;if(!first)return 0;
    peNode* last=first;u16 created=1;
    while((next=last->next)!=0 && created<requested){last=next;++created;}
    if(next)next->previous=0;
    freeNodes=last->next;peNode* old=nodes;last->next=old;if(old)old->previous=last;
    first->previous=0;nodes=first;count+=created;dirty=1;return created;
}
void peContainer::SetLayerVisibility(GSgfxLayerID id,bool visible) {GSgfxLayer* layer=GSgfxLayerFindByID(id);if(layer)layer->SetLayerVisibility(visible);}
void peContainer::PreUpdate() {}
void peContainer::Start(){if(!active)active=1;}
peContainer::~peContainer() {
    if(memory){u32 size=GSmemGetSize(memory);g_particle_debug_stats.node-=size;g_particle_debug_stats.total-=size;GSmemFree(memory);memory=0;}
}
peContainer::peContainer(peEmitterNode* emitter,u32 nodeBytes,u16 maximum):owner(emitter),next(0),memory(0),freeNodes(0),nodes(0),count(0),capacity(maximum),dirty(0),active(0) {
    u32 totalNodes=maximum;
    u32 bytes=totalNodes*nodeBytes;
    u32 localTransform=(owner->emitter->flags>>6)&1;
    if(localTransform)bytes+=totalNodes*0x28;
    memory=(u8*)GSmemAllocClr(bytes);if(!memory)return;
    u32 size=GSmemGetSize(memory);g_particle_debug_stats.node+=size;g_particle_debug_stats.total+=size;
    freeNodes=(peNode*)memory;peNode* node;u8* cursor=(u8*)freeNodes;peNode* previous=0;
    for(u32 i=0;i<totalNodes;++i) {
        node=(peNode*)cursor;cursor+=nodeBytes;
        if(localTransform){node->transform=cursor;cursor+=0x28;}else node->transform=emitter->world;
        node->previous=previous;if(previous)previous->next=node;previous=node;
    }
    dirty=1;
}
peRenderContainer::~peRenderContainer() {
    if ((displayLists[0].flags & 1) == 1) {
        u32 s = displayLists[0].size;
        g_particle_debug_stats.displayList -= s;
        g_particle_debug_stats.total -= s;
        GSgfxDLFree(&displayLists[0]);
        if ((displayLists[1].flags & 1) == 1) {
            u32 s2 = displayLists[1].size;
            g_particle_debug_stats.displayList -= s2;
            g_particle_debug_stats.total -= s2;
            GSgfxDLFree(&displayLists[1]);
        }
        if (renderData[0]) {
            renderData[0] = (u8*)((u32)renderData[0] - 0x40000000);
            u32 sz = GSmemGetSize(renderData[0]);
            g_particle_debug_stats.renderData -= sz;
            g_particle_debug_stats.total -= sz;
            if (renderData[0]) {
                GSmemFree(renderData[0]);
                renderData[0] = 0;
            }
        }
    }
}
peRenderContainer::peRenderContainer(peEmitterNode* e, u32 nodeSize, u16 max, GSgfxVF* vf, GSgfxPrimType prim,
                                     u8 vertsPerNode, u8 bytesPerVert, bool dbl)
    : peContainer(e, nodeSize, max) {
    u32 aligned;
    u32 total = max * bytesPerVert;
    swapped = 0;
    swapIndex = 0;
    renderBytes = 0;
    memset(&displayLists[0], 0, 0x10);
    memset(&displayLists[1], 0, 0x10);
    renderData[0] = 0;
    renderData[1] = 0;
    tokens[0] = 0;
    tokens[1] = 0;
    aligned = (total + 31) & ~31;
    u8* mem = (u8*)GSmemAllocAlignClr(dbl ? aligned * 2 : aligned, 0x20);
    if (!mem) {
        return;
    }
    u32 verts = max * vertsPerNode;
    GSgfxDLCreate(&displayLists[0], prim, vf, verts);
    if ((displayLists[0].flags & 1) != 1) {
        if (mem) {
            GSmemFree(mem);
        }
        return;
    }
    if (dbl) {
        GSgfxDLCreate(&displayLists[1], prim, vf, verts);
    }
    u32 sz = GSmemGetSize(mem);
    u32 display0=displayLists[0].size,display1=displayLists[1].size;
    u32 oldDisplay=g_particle_debug_stats.displayList,oldData=g_particle_debug_stats.renderData,oldTotal=g_particle_debug_stats.total;
    g_particle_debug_stats.displayList=display0+(display1+oldDisplay);
    g_particle_debug_stats.renderData=oldData+sz;
    g_particle_debug_stats.total=sz+(display0+display1+oldTotal);
    if ((displayLists[1].flags & 1) == 1) {
        DCFlushRange(mem, aligned * 2);
        u8* p = mem + 0x40000000;
        renderData[0] = p;
        renderData[1] = p + aligned;
    } else {
        DCFlushRange(mem, total);
        renderData[0] = mem + 0x40000000;
    }
    renderBytes = total;
    char* colors0 = displayLists[0].VertexData(0);
    memset(colors0, 0xff, max * (vertsPerNode * (u16)((displayLists[0].flags & 1) ? displayLists[0].stride : 0)));
    displayLists[0].flags |= 2;
    if ((displayLists[1].flags & 1) == 1) {
        char* colors1 = displayLists[1].VertexData(0);
        memset(colors1, 0xff, max * (vertsPerNode * (u16)((displayLists[1].flags & 1) ? displayLists[1].stride : 0)));
        displayLists[1].flags |= 2;
    }
}
