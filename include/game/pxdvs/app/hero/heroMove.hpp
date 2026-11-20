#ifndef HERO_MOVE_H
#define HERO_MOVE_H

#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
#include <libc/stddef.h>

struct HeroMoveQueuedEvent {
    GSvec vertices[3];
    f32 normal[3];
    u16 eventID;
    u16 padding;
};

typedef char HeroMoveQueuedEvent_size_check[sizeof(HeroMoveQueuedEvent) == 0x34 ? 1 : -1];
typedef char HeroMoveQueuedEvent_normal_check[offsetof(HeroMoveQueuedEvent, normal) == 0x24 ? 1 : -1];
typedef char HeroMoveQueuedEvent_id_check[offsetof(HeroMoveQueuedEvent, eventID) == 0x30 ? 1 : -1];

extern "C" s32 heroMoveCheckEvent(HeroMoveQueuedEvent*);
extern "C" void heroMoveSetEventList(u8 kind, HeroMoveQueuedEvent* events, s32 count);

extern "C" void heroMoveGetHeroPos(GSvec *);
extern "C" void heroMoveGetHeroRot(GSvec *);

#endif
