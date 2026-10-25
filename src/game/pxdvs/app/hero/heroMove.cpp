extern "C" float __float_nan[];
#include <game/pxdvs/app/hero/heroMovePrivate.hpp>

struct HeroMoveSlot {
    u32 fn;
    s32 arg;
};

static HeroMoveWork HeroMove;

static void _heroMoveSlowStopFactor(float, bool);
static bool getResID(unsigned long*, unsigned long*, HEROMOVE_MEMBER);
static void* getModel(HEROMOVE_MEMBER);

static void _heroMoveInitialize(unsigned int, FloorEnterMode mode) {
    HeroMove.raw[0x3AD] = 0;
    HeroMove.raw[0x3AC] = 0;
    HeroMove.raw[0x3AE] = 0;
    if (mode == 3) {
        heroMoveSetLockFrame(4);
    }
}

static void _closeHeroThread() {
    _heroMoveSlowStopFactor(4.0f, true);
}

static const char* _heroMoveGetModuleName() {
    return "hero";
}

extern "C" {

u8 heroMoveIsSmoothFloorLink() {
    return HeroMove.raw[0x3AC];
}

void heroMoveSetSmoothFloorLink(u8 v) {
    HeroMove.raw[0x3AC] = v;
}

}

void AnalogStickEmu::init() {
    b0 = 0;
    b1 = 0;
    b2 = 0;
    b3 = 0;
    b4 = 0x14;
    b5 = 10;
}

static void* _heroGetPeople(HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    return peopleGet(group, res);
}

static u8 isStoryMode() {
    return GSflagGet(0x30D) == 0;
}

static void _setStickData(s8 a, s8 b, s8 c, s8 d) {
    HeroMove.raw[0x3AE] = 1;
    HeroMove.raw[0x3AF] = a;
    HeroMove.raw[0x3B0] = b;
    HeroMove.raw[0x3B1] = c;
    HeroMove.raw[0x3B2] = d;
}

static s8 abs(s8 v) {
    return (s8)__abs((int)v);
}

static u32 getEquipItemEffect(u16 item) {
    u32 data = itemDataBiosGetPtr(item);
    if (data == 0) {
        return 0;
    }
    return itemDataBiosGetItemSoubiDataId(data);
}

extern "C" {

void heroMoveSlowStop() {
    _heroMoveSlowStopFactor(3.0f, false);
}

void heroMoveSetLockFrame(s32 frames) {
    if (frames >= 0) {
        *(s32*)&HeroMove.raw[0x3A8] = frames;
        ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    }
}

void heroMoveAddAutoEvent(s32 a, s32 b, s32 c, s32 d, s32 e) {
    *(s32*)&HeroMove.raw[0x3B4] = a;
    *(s32*)&HeroMove.raw[0x3B8] = b;
    *(s32*)&HeroMove.raw[0x3BC] = c;
    *(s32*)&HeroMove.raw[0x3C0] = d;
    *(s32*)&HeroMove.raw[0x3C4] = e;
}

}

static void initFootWork(FOOTWORK* w) {
    w->a = 0.0f;
    w->b = 0.0f;
    w->c = 0.0f;
    w->d = 0.0f;
}

static void setRot(HEROMOVE_MEMBER member, GSvec* rot) {
    GSmodelSetRotation(getModel(member), rot);
}

static void getRot(GSvec* rot, HEROMOVE_MEMBER member) {
    GSmodelGetRotation(getModel(member), rot);
}

extern "C" {

s32 heroMoveGetLeader();

void heroMoveGetHeroRot(GSvec* rot) {
    getRot(rot, (HEROMOVE_MEMBER)heroMoveGetLeader());
}

}

static void getPos(GSvec*, HEROMOVE_MEMBER);

extern "C" {

void heroMoveGetHeroPos(GSvec* pos) {
    getPos(pos, (HEROMOVE_MEMBER)heroMoveGetLeader());
}

}

static void* getModel(HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    return GSresGetResource(group, res);
}

static bool getResID(unsigned long* group, unsigned long* res, HEROMOVE_MEMBER member) {
    unsigned long ids[4] = {0x64, 0x65, 0x68, 0x69};
    if (member < 0 || member >= 4) {
        return false;
    }
    *group = 0;
    *res = ids[member];
    return true;
}

static void getPos(GSvec* pos, HEROMOVE_MEMBER member) {
    void* model = getModel(member);
    if (model != 0) {
        GSmodelGetPosition(model, pos);
    }
}

static void setPos(HEROMOVE_MEMBER member, GSvec* pos) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    peopleSetPos(group, res, pos);
}

static void setDisp(HEROMOVE_MEMBER member, bool disp) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    peopleSetDisp(group, res, disp);
}

extern "C" {

bool heroMoveGetResID(unsigned long* group, unsigned long* res, HEROMOVE_MEMBER member) {
    return getResID(group, res, member);
}

bool heroMoveIsMember(s32 member) {
    if (member < 0 || member >= 4) {
        return false;
    }
    return HeroMove.members[member].flags & 1;
}

s32 heroMoveGetLeader() {
    return *(s32*)&HeroMove.raw[0];
}

s32 heroMoveGetNeckMode(s32 member) {
    if (heroMoveIsMember(member)) {
        return HeroMove.members[member].neckMode;
    }
    return 2;
}

}

static void initLeaderLog() {
    *(s32*)&HeroMove.raw[0x84] = 0;
    *(s32*)&HeroMove.raw[0x88] = 0;
}

extern "C" void fn_80151F6C() {
    *(s32*)&HeroMove.raw[0x644] = 0;
    *(s32*)&HeroMove.raw[0x648] = 0;
    *(s32*)&HeroMove.raw[0x64C] = 0;
    *(s32*)&HeroMove.raw[0x650] = 0;
}

static void remakeFormation();
static f32 moveParty(HEROMOVE_MEMBER);
static void initLeaderLog();
static void cbPoison(long, FootStepCounter, long);
static void cbTsureFriend(long, FootStepCounter, long);
static void _heroMoveFinalize(unsigned int, FloorEnterMode);
static FloorModuleInterface _floorModuleHero;

static f32 GSvecDistanceXZ(GSvec* a, GSvec* b) {
    GSvec va;
    GSvec vb;
    va.param1 = a->param1;
    va.param2 = a->param2;
    va.param3 = a->param3;
    vb.param1 = b->param1;
    vb.param2 = b->param2;
    vb.param3 = b->param3;
    va.param2 = 0.0f;
    vb.param2 = 0.0f;
    return PSVECDistance(&va, &vb);
}

static void* getHumanPeople(HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    getResID(&group, &res, member);
    return peopleSearchID(peopleGetHumanID(group, res));
}

static s32 getObjID(HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    void* people;
    if (!getResID(&group, &res, member)) {
        return -1;
    }
    people = peopleSearchID(peopleGetHumanID(group, res));
    if (people == 0) {
        return -1;
    }
    return *(s32*)((u8*)people + 0x1C);
}

static void updateAnimation(f32 rate, HEROMOVE_MEMBER member) {
    unsigned long group;
    unsigned long res;
    void* people;
    getResID(&group, &res, member);
    people = peopleSearchID(peopleGetHumanID(group, res));
    if (people != 0) {
        *(f32*)((u8*)people + 0x28) = rate;
        peopleUpdateAnimation(people, 0);
    }
}

static void updateMotion(HEROMOVE_MEMBER member, f32 rate) {
    getModel(member);
    updateAnimation(rate, member);
}

static void actionFriendSet(Pokemon* pokemon, u16 level) {
    u32 effect = getEquipItemEffect(pokemonBiosGetItemDataId(pokemon));
    pokemonGetFriendFormPokemonFriendFilterId(pokemon, effect, level);
}

static bool getLeaderLog(GSvec* out, int index) {
    if (index >= *(s32*)&HeroMove.raw[0x88]) {
        return false;
    }
    if (index >= 0x3C) {
        return false;
    }
    out->param1 = HeroMove.leaderLog.log[index].param1;
    out->param2 = HeroMove.leaderLog.log[index].param2;
    out->param3 = HeroMove.leaderLog.log[index].param3;
    return true;
}

static void initHeroMove() {
    HeroMove.members[0].flags = 0;
    HeroMove.members[1].flags = 0;
    HeroMove.members[2].flags = 0;
    HeroMove.members[3].flags = 0;
    *(s32*)&HeroMove.raw[0] = 0;
    *(s32*)&HeroMove.raw[0x3A8] = 0;
    HeroMove.raw[0x3AE] = 0;
    ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
}

extern "C" {

bool heroMoveAppointLeader(s32 member) {
    if (!heroMoveIsMember(member)) {
        return false;
    }
    *(s32*)&HeroMove.raw[0] = member;
    if (heroMoveGetNeckMode(member) == 1) {
        heroMoveSetNeckMode(member, 0);
    }
    remakeFormation();
    initLeaderLog();
    return true;
}

void heroMoveSyncWithHero() {
    u8 join = 0;
    if (isStoryMode()) {
        if (heroGetStatus(0, 0x18, 0) != 0) {
            join = 1;
        }
    }
    if (join) {
        heroMoveJoinMember(1);
    } else {
        heroMoveDismissMember(1);
    }
}

void heroMoveMoveParty() {
    s32 i = 0;
    do {
        if (heroMoveIsMember(i)) {
            if (i != heroMoveGetLeader()) {
                moveParty((HEROMOVE_MEMBER)i);
            }
        }
        i++;
    } while (i < 4);
}

}

extern "C" void heroMoveCallStepCallback(s32 a, s32 b);

extern "C" {

s32 heroMoveDismissMember(s32 member) {
    if (member < 0 || member >= 4) {
        return 0;
    }
    if (member == heroMoveGetLeader()) {
        return 0;
    }
    HeroMove.members[member].flags = HeroMove.members[member].flags & 0xFFFE;
    remakeFormation();
    return 1;
}

s32 heroMoveSetNeckMode(s32 member, s32 mode) {
    unsigned long group;
    unsigned long res;
    if (mode < 0 || mode >= 2) {
        return 0;
    }
    if (!heroMoveIsMember(member)) {
        return 0;
    }
    getResID(&group, &res, (HEROMOVE_MEMBER)member);
    switch (HeroMove.members[member].neckMode) {
    case 1:
        peopleRemoveNeckTarget(group, res, 1.0f);
    }
    switch (mode) {
    case 1:
        peopleSetNeckTargetHero(group, res);
    }
    HeroMove.members[member].neckMode = mode;
    return 1;
}

void heroMoveSetColision(u8 enable) {
    unsigned long group;
    unsigned long res;
    s32 i = 0;
    do {
        if (heroMoveIsMember(i)) {
            getResID(&group, &res, (HEROMOVE_MEMBER)i);
            if (enable != 0) {
                peopleSetCollision(group, res, 1);
                peopleSetFlagOn(group, res, 0x700);
            } else {
                peopleSetFlagOff(group, res, 0x100);
                peopleSetFlagOff(group, res, 0x400);
                peopleSetCollision(group, res, 0);
            }
        }
        i++;
    } while (i < 4);
}

#pragma optimization_level 3
void heroMoveTermEvent() {
    unsigned long group;
    unsigned long res;
    s32 i = 0;
    do {
        if (heroMoveIsMember(i)) {
            getResID(&group, &res, (HEROMOVE_MEMBER)i);
            peopleSetCollision(group, res, 1);
            peopleSetFlagOn(group, res, 0x700);
            peopleSetFlagOff(group, res, 0x80000008);
        }
        i++;
    } while (i < 4);
    ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    peopleRemoveNeckTarget(0, 0x64, 1.0f);
}
#pragma optimization_level reset

void heroMoveInitEvent() {
    unsigned long group;
    unsigned long res;
    s32 i = 0;
    do {
        if (heroMoveIsMember(i)) {
            getResID(&group, &res, (HEROMOVE_MEMBER)i);
            getModel((HEROMOVE_MEMBER)i);
            updateAnimation(0.0f, (HEROMOVE_MEMBER)i);
            peopleSetFlagOn(group, res, 0x80000008);
            peopleSetFlagOff(group, res, 0x100);
            peopleSetFlagOff(group, res, 0x400);
            peopleSetCollision(group, res, 0);
        }
        i++;
    } while (i < 4);
}

void heroMoveSetEventList(u8 kind, void* list, s32 owner) {
    switch (kind) {
    case 1:
        memcpy(&HeroMove.raw[0x498], (void*)list, 0xD0);
        *(s32*)&HeroMove.raw[0x63C] = owner;
        break;
    case 2:
        memcpy(&HeroMove.raw[0x568], (void*)list, 0xD0);
        *(s32*)&HeroMove.raw[0x640] = owner;
        break;
    case 3:
        memcpy(&HeroMove.raw[0x3C8], (void*)list, 0xD0);
        *(s32*)&HeroMove.raw[0x638] = owner;
        break;
    }
}

void heroMovePoolCounter(s32 kind, s32 amount) {
    switch (kind) {
    case 0:
        *(s32*)&HeroMove.raw[0x644] += amount;
        break;
    case 1:
        *(s32*)&HeroMove.raw[0x648] += amount;
        break;
    case 2:
        *(s32*)&HeroMove.raw[0x64C] += amount;
        break;
    case 3:
        *(s32*)&HeroMove.raw[0x650] += amount;
        break;
    }
}

}

extern "C" void heroMoveCallStepCallback(s32 a, s32 b) {
    s32 i;
    for (i = 0; i < 8; i++) {
        HeroMoveSlot* p = (HeroMoveSlot*)&HeroMove + i;
        HeroMoveSlot* e = &p[0x6C];
        if (e != 0) {
            u32 fn = e->fn;
            if (fn != 0) {
                ((void (*)(s32, s32, s32))fn)(e->arg, a, b);
            }
        }
    }
}

extern "C" u8 heroMoveCallStepCallbackAll() {
    u8 called = 0;
    s32 count;
    count = *(s32*)&HeroMove.raw[0x644];
    if (count != 0) {
        heroMoveCallStepCallback(0, count);
        called = 1;
        *(s32*)&HeroMove.raw[0x644] = 0;
    }
    count = *(s32*)&HeroMove.raw[0x648];
    if (count != 0) {
        heroMoveCallStepCallback(1, count);
        called = 1;
        *(s32*)&HeroMove.raw[0x648] = 0;
    }
    count = *(s32*)&HeroMove.raw[0x64C];
    if (count != 0) {
        heroMoveCallStepCallback(2, count);
        called = 1;
        *(s32*)&HeroMove.raw[0x64C] = 0;
    }
    count = *(s32*)&HeroMove.raw[0x650];
    if (count != 0) {
        heroMoveCallStepCallback(3, count);
        called = 1;
        *(s32*)&HeroMove.raw[0x650] = 0;
    }
    return called;
}

static void cbTsureFriend(long, FootStepCounter counter, long amount) {
    if (counter != 1) {
        *(s32*)&HeroMove.raw[0x3A4] += amount;
        while (*(s32*)&HeroMove.raw[0x3A4] > 0x100) {
            s32 i = 0;
            for (; i < 6; i++) {
                Pokemon* p = (Pokemon*)heroGetStatus(0, 3, i);
                if (p != 0 && pokemonCheckValid(p)) {
                    actionFriendSet(p, 5);
                }
            }
            *(s32*)&HeroMove.raw[0x3A4] -= 0x100;
        }
    }
}

static void remakeFormation() {
    f32 d = 12.0f;
    s32 i;
    HeroMove.members[HeroMove.members[0].x0].dist = 0.0f;
    for (i = 0; i < 4; i++) {
        if ((HeroMove.members[i].flags & 1) && HeroMove.members[0].x0 != i) {
            HeroMove.members[i].dist = d;
            d += 12.0f;
        }
    }
}

extern "C" {

s32 heroMoveJoinMember(s32 member) {
    Hero* hero;
    HeroMoveMember* m;
    if (member < 0 || member >= 4) {
        return 0;
    }
    if (heroMoveIsMember(member)) {
        return 1;
    }
    hero = Hero::getHeroPtr();
    hero->setFollowerGrpID(0);
    switch (member) {
    case 1:
        hero->setFollowerResID(0x65);
        hero->setFollowerID(1);
        break;
    case 2:
        hero->setFollowerResID(0x68);
        hero->setFollowerID(2);
        break;
    case 3:
        hero->setFollowerResID(0x69);
        hero->setFollowerID(3);
        break;
    }
    HeroMove.members[member].flags = HeroMove.members[member].flags | 1;
    heroMoveSetNeckMode(member, 1);
    remakeFormation();
    setDisp((HEROMOVE_MEMBER)member, true);
    return 1;
}

}

static void _heroMoveFinalize(unsigned int floorId, FloorEnterMode) {
    HeroMove.raw[0x3AD] = 0;
    if (HeroMove.raw[0x3AC] != 0) {
        if (floorDataBiosGetFloorKind(floorDataBiosGetPtr(floorId)) == 1) {
            floorCreateThread(0x80, 0, 1, _closeHeroThread);
        }
    }
}

extern "C" {

s32 heroMoveAddStepCallback(void (*fn)(long, FootStepCounter, long), s32 arg) {
    s32 i = 0;
    HeroMoveSlot* p = (HeroMoveSlot*)&HeroMove;
    for (; i < 8; i++, p++) {
        if (p[0x6C].fn == 0) {
            break;
        }
    }
    if (i >= 8) {
        return -1;
    }
    p = (HeroMoveSlot*)&HeroMove + i;
    p[0x6C].fn = (u32)fn;
    p[0x6C].arg = arg;
    return i;
}

void heroMoveAllInit() {
    initHeroMove();
    heroMoveJoinMember(0);
    heroMoveAppointLeader(0);
    *(f32*)&HeroMove.raw[0x35C] = 0.0f;
    *(s32*)&HeroMove.raw[0x3B4] = 0;
    *(s32*)&HeroMove.raw[0x360] = 0;
    *(s32*)&HeroMove.raw[0x368] = 0;
    *(s32*)&HeroMove.raw[0x370] = 0;
    *(s32*)&HeroMove.raw[0x378] = 0;
    *(s32*)&HeroMove.raw[0x380] = 0;
    *(s32*)&HeroMove.raw[0x388] = 0;
    *(s32*)&HeroMove.raw[0x390] = 0;
    *(s32*)&HeroMove.raw[0x398] = 0;
    *(s32*)&HeroMove.raw[0x3A0] = 0;
    heroMoveAddStepCallback(cbPoison, 0);
    *(s32*)&HeroMove.raw[0x3A4] = 0;
    heroMoveAddStepCallback(cbTsureFriend, 0);
    HeroMove.raw[0x3AE] = 0;
    *(s32*)&HeroMove.raw[0x644] = 0;
    *(s32*)&HeroMove.raw[0x648] = 0;
    *(s32*)&HeroMove.raw[0x64C] = 0;
    *(s32*)&HeroMove.raw[0x650] = 0;
    ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    FloorModuleInterface_clear(&_floorModuleHero);
    _floorModuleHero.pre = _heroMoveInitialize;
    _floorModuleHero.post = _heroMoveFinalize;
    _floorModuleHero.getName = _heroMoveGetModuleName;
    floorRegisterModule(0x80, 0, &_floorModuleHero);
}

}

extern "C" s32 heroGetFollower() {
    tagPeopleWork* people;
    Hero* hero;
    hero = Hero::getHeroPtr();
    people = (tagPeopleWork*)peopleGet(hero->getFollowerGrpID(), hero->getFollowerResID());
    if (people == 0) {
        return 0;
    }
    if (people->used == 0) {
        return 0;
    }
    if (people->visible == 0) {
        return 0;
    }
    if (people->object == 0) {
        return 0;
    }
    switch (hero->getFollowerResID()) {
    case 0x65:
        return HeroMove.members[1].flags & 1;
    case 0x68:
        return (HeroMove.members[2].flags & 1) ? 2 : 0;
    case 0x69:
        return (HeroMove.members[3].flags & 1) ? 3 : 0;
    default:
        return 0;
    }
}

static f32 moveLeaderPosition(HEROMOVE_MEMBER);
static void procStep(HEROMOVE_MEMBER);
static void updateLeaderMovement(HEROMOVE_MEMBER, float*);
static void updateLeaderLog();
static u8 updateChat(HEROMOVE_MEMBER);

static f32 moveLeader(HEROMOVE_MEMBER member) {
    u32 changed = GSinputButtonsChanged(1);
    u32 pressed = GSinputButtonsPressed(1);
    if ((pressed & changed & 0x100) && updateChat(member) != 0) {
        return 0.0f;
    }
    return moveLeaderPosition(member);
}

static void proc1Step(f32 dt) {
    Hero* hero = Hero::getHeroPtr();
    if (isStoryMode()) {
        unsigned long group;
        unsigned long res;
        heroMoveGetResID(&group, &res, (HEROMOVE_MEMBER)heroMoveGetLeader());
        if (peopleCheckFlag(group, res, 0x80000000) == 0) {
            f32* accum = (f32*)&HeroMove.raw[0x35C];
            *accum = *accum + dt;
            while (*accum >= 7.0f) {
                hero->addFootStep(1);
                heroMoveCallStepCallback(0, 1);
                *accum = *accum - 7.0f;
            }
        }
    }
}

static f32 moveLeaderPosition(HEROMOVE_MEMBER member) {
    f32 dist;
    GSvec prev;
    GSvec cur;
    GSvec delta;
    float move;
    unsigned long group;
    unsigned long res;
    f32 rateF = (u8)GSgfxVideoGetVsyncRate();
    f32 frameTime = (f32)timeGetLastFrameTime();
    f32 step = (30.0f * frameTime) / rateF;
    getPos(&prev, member);
    updateLeaderMovement(member, &move);
    getPos(&cur, member);
    PSVECSubtract(&cur, &prev, &delta);
    getResID(&group, &res, member);
    dist = PSVECMag(&delta);
    if (step == 0.0f) {
        updateMotion(member, 0.0f);
    } else {
        updateMotion(member, dist / step);
    }
    updateLeaderLog();
    return dist;
}

extern "C" {

s32 heroMoveMain() {
    unsigned long group;
    unsigned long res;
    u32 total = 0;
    s32 i;
    u8* p1;
    u8* p2;
    u8* p3;
    f32 moved;
    if (HeroMove.raw[0x3AD] == 0) {
        HeroMove.raw[0x3AD] = 1;
    }
    if (dbgMenuIsOpen() != 0) {
        return 0;
    }
    if (menuIsCheck(0x23) != 0) {
        return 0;
    }
    if (floorGetFloorState() == 2 || floorGetFloorState() == 6) {
        return 0;
    }
    if (cameraGetType() == 6) {
        return 0;
    }
    if (menuIsCheck(0xA) != 0) {
        return 0;
    }
    if (*(s32*)&HeroMove.raw[0x3A8] > 0) {
        *(s32*)&HeroMove.raw[0x3A8] -= 1;
        return 0;
    }
    *(u32*)&HeroMove.raw[0x65C] = pokecoloFrameCounter;
    heroMoveGetResID(&group, &res, (HEROMOVE_MEMBER)heroMoveGetLeader());
    if (peopleCheckFlag(group, res, 0x80000000) != 0) {
        return 0;
    }
    if (*(u32*)&HeroMove.raw[0x3B4] != 0) {
        *(u32*)&HeroMove.raw[0x3B4] = 0;
        floorExecScriptInteger(*(s32*)&HeroMove.raw[0x3B8], *(s32*)&HeroMove.raw[0x3BC], *(s32*)&HeroMove.raw[0x3C0], *(s32*)&HeroMove.raw[0x3C4]);
        return 0;
    }
    if (heroMoveCallStepCallbackAll() != 0) {
        return 0;
    }
    p3 = (u8*)&HeroMove;
    i = 0;
    while (i < *(s32*)&HeroMove.raw[0x638]) {
        total += floorEventExecScript(3, *(u16*)(p3 + 0x3F8));
        p3 += 0x34;
        i++;
    }
    p2 = (u8*)&HeroMove;
    i = 0;
    while (i < *(s32*)&HeroMove.raw[0x640]) {
        total += floorEventExecScript(2, *(u16*)(p2 + 0x598));
        p2 += 0x34;
        i++;
    }
    p1 = (u8*)&HeroMove;
    i = 0;
    while (i < *(s32*)&HeroMove.raw[0x63C]) {
        total += floorEventExecScript(1, *(u16*)(p1 + 0x4C8));
        p1 += 0x34;
        i++;
    }
    *(s32*)&HeroMove.raw[0x63C] = 0;
    *(s32*)&HeroMove.raw[0x640] = 0;
    *(s32*)&HeroMove.raw[0x638] = 0;
    if (*(u32*)&HeroMove.raw[0x3B4] != 0) {
        return 0;
    }
    if (gimmickBoxIsGimmickMoving() == 0 && total == 0 && peopleCheckFlag(group, res, 0x80000000) == 0) {
        s32 changed = GSinputButtonsChanged(1);
        if (GSinputButtonsPressed(1) & changed & 0x1C00) {
            if (floorSound_getBgmMaskObj() != 0) {
                floorSound_getBgmMaskObj()->stopMask();
            }
            menuFieldMain(0);
            return 0;
        }
    }
    if (pokecoloFrameCounter - *(u32*)&HeroMove.raw[0x65C] > 5) {
        ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    }
    moved = moveLeader((HEROMOVE_MEMBER)heroMoveGetLeader());
    procStep((HEROMOVE_MEMBER)heroMoveGetLeader());
    proc1Step(moved);
    return 0;
}

}

extern "C" {
void* peopleBiosGetPosPtr();
void* peopleBiosGetRotPtr(void*);
void PSVECAdd(GSvec*, GSvec*, GSvec*);
s32 GScolsys2CheckGetEventID(GSvec*, GSvec*, void*);
double sin(double);
double cos(double);

s32 heroMoveCheckEvent(void* arg) {
    unsigned long group;
    unsigned long res;
    s32 result;
    void* people;
    getResID(&group, &res, (HEROMOVE_MEMBER)heroMoveGetLeader());
    people = peopleSearchID(peopleGetHumanID(group, res));
    if (people != 0) {
        GSvec* pos = (GSvec*)peopleBiosGetPosPtr();
        f32* rot = (f32*)peopleBiosGetRotPtr(people);
        GSvec start;
        GSvec dir;
        start.param1 = pos->param1;
        start.param2 = pos->param2;
        start.param3 = pos->param3;
        start.param2 += 5.0f;
        dir.param1 = 10.0f * (f32)sin(rot[1]);
        dir.param2 = 0.0f;
        dir.param3 = 10.0f * (f32)cos(rot[1]);
        PSVECAdd(&start, &dir, &dir);
        result = GScolsys2CheckGetEventID(&start, &dir, arg);
    }
    return result;
}
}

void AnalogStickEmu::calculate(s8& x, s8& y, s8& cx, s8& cy) {
    if (b0 < x) {
        if (b0 < 0 && x > 0) {
            b0 = x;
        } else {
            if (abs(x) > abs(b0)) b0 += b4;
            else b0 += b5;
            if (b0 > x) b0 = x;
        }
    } else if (b0 > x) {
        if (b0 > 0 && x < 0) {
            b0 = x;
        } else {
            if (abs(x) > abs(b0)) b0 -= b4;
            else b0 -= b5;
            if (b0 < x) b0 = x;
        }
    }
    if (b1 < y) {
        if (b1 < 0 && y > 0) {
            b1 = y;
        } else {
            if (abs(y) > abs(b1)) b1 += b4;
            else b1 += b5;
            if (b1 > y) b1 = y;
        }
    } else if (b1 > y) {
        if (b1 > 0 && y < 0) {
            b1 = y;
        } else {
            if (abs(y) > abs(b1)) b1 -= b4;
            else b1 -= b5;
            if (b1 < y) b1 = y;
        }
    }
    if (b2 < cx) {
        if (b2 < 0 && cx > 0) {
            b2 = cx;
        } else {
            if (abs(cx) > abs(b2)) b2 += b4;
            else b2 += b5;
            if (b2 > cx) b2 = cx;
        }
    } else if (b2 > cx) {
        if (b2 > 0 && cx < 0) {
            b2 = cx;
        } else {
            if (abs(cx) > abs(b2)) b2 -= b4;
            else b2 -= b5;
            if (b2 < cx) b2 = cx;
        }
    }
    if (b3 < cy) {
        if (b3 < 0 && cy > 0) {
            b3 = cy;
        } else {
            if (abs(cy) > abs(b3)) b3 += b4;
            else b3 += b5;
            if (b3 > cy) b3 = cy;
        }
    } else if (b3 > cy) {
        if (b3 > 0 && cy < 0) {
            b3 = cy;
        } else {
            if (abs(cy) > abs(b3)) b3 -= b4;
            else b3 -= b5;
            if (b3 < cy) b3 = cy;
        }
    }
    x = b0;
    y = b1;
    cx = b2;
    cy = b3;
}

static void _getStickData(s8&, s8&, s8&, s8&);
extern "C" {
void GSthreadSwitch();
f32 timeGetLastFrameSec();
}

static void _heroMoveSlowStopFactor(float factor, bool moveFollowers) {
    s8 x, y, rawX, rawY;
    heroMoveGetLeader();
    _getStickData(x, y, rawX, rawY);
    f32 weight;
    f32 fx = x, fy = y, frx = rawX, fry = rawY;
    weight = 1.0f;
    while (weight >= 0.0f) {
        if (moveFollowers) {
            for (s32 i = 0; i < 4; ++i) {
                if (heroMoveIsMember(i) && i != heroMoveGetLeader()) {
                    updateMotion((HEROMOVE_MEMBER)i, moveParty((HEROMOVE_MEMBER)i));
                }
            }
        }
        fx *= weight;
        fy *= weight;
        frx *= weight;
        fry *= weight;
        _setStickData(fx, fy, frx, fry);
        moveLeaderPosition(HEROMOVE_MEMBER_0);
        if (moveFollowers) {
            moveLeaderPosition(HEROMOVE_MEMBER_1);
            moveLeaderPosition(HEROMOVE_MEMBER_2);
            moveLeaderPosition(HEROMOVE_MEMBER_3);
        }
        GSthreadSwitch();
        weight -= factor * timeGetLastFrameSec();
    }
    HeroMove.raw[0x3AE] = 0;
}

extern "C" {
void fadeEffectDokuStart();
void heroMoveInitEvent();
void heroMoveTermEvent();
void* pokemonBiosGetNicknamePtr(Pokemon*);
void msgctrlSetValue(u32, void*);
void winMsgOpenField(u32, u32, u32);
void winMsgCloseField(u32);
}

static void cbPoison(long, FootStepCounter counter, long) {
    s32 fainted[6];
    s32* readFainted;
    s32 faintedCount = 0;
    u8 poisoned = 0;
    if (counter == 0) {
        if (++*(s32*)&HeroMove.raw[0x3A0] >= 4) {
            *(s32*)&HeroMove.raw[0x3A0] = 0;
            s32 healthyCount = 0;
            for (s32 i = 0; i < 6; ++i) {
                Pokemon* pokemon = (Pokemon*)heroGetStatus(0, 3, i);
                if (pokemon && pokemonCheckValid(pokemon) && pokemon->getHp()) ++healthyCount;
            }
            readFainted = fainted;
            s32* nextFainted = readFainted;
            for (s32 i = 0; i < 6; ++i) {
                Pokemon* pokemon = (Pokemon*)heroGetStatus(0, 3, i);
                if (pokemon && pokemonCheckValid(pokemon)) {
                    u32 hp = pokemon->getHp();
                    if ((u16)hp) {
                        u8 condition = pokemon->getCondition();
                        if (condition == 3 || condition == 4) {
                            poisoned = 1;
                            if (healthyCount > 1 || (u16)hp > 1) {
                                pokemon->setHp(hp - 1);
                                if ((u16)(hp - 1) == 0) {
                                    *nextFainted = i;
                                    --healthyCount;
                                    ++nextFainted;
                                    ++faintedCount;
                                    pokemon->initCondition();
                                    DarkPokemon* dark = pokemon->getDarkPokemon();
                                    if (dark) dark->setReversMode(false);
                                }
                            }
                        }
                    }
                }
            }
            if (poisoned) fadeEffectDokuStart();
            if (faintedCount > 0) {
                heroMoveInitEvent();
                for (s32 i = 0; i < faintedCount; ++readFainted, ++i) {
                    Pokemon* pokemon = (Pokemon*)heroGetStatus(0, 3, *readFainted);
                    void* nickname = pokemonBiosGetNicknamePtr(pokemon);
                    msgctrlSetValue(0x32, nickname);
                    winMsgOpenField(0xC37E, 1, 0);
                    winMsgCloseField(1);
                    actionFriendSet(pokemon, 7);
                }
                heroMoveTermEvent();
            }
        }
    }
}

extern "C" {
u32 heroGetObjID(void*);
u32 floorGetNextFloorID();
s32 menuCBBios_GetToolBattleTrainerKind();

u32 heroMoveGetKenObjID() {
    u32 floors[20] = {0x20, 0x17, 0x21, 0x18, 0x22, 0x19, 0x11, 0x1A, 0x12, 0x1B,
                      0x13, 0x1C, 0x0C, 0x1D, 0x0D, 0x1E, 0x0E, 0x1F, 0x0F, 0x10};
    struct TrainerModel { s32 kind; u32 id; } models[5] = {
        {0, 0x16C90400}, {1, 0x16C90400}, {2, 0x16C90400}, {3, 0x16C90400}, {4, 0x16C90400}
    };
    if (isStoryMode()) return heroGetObjID(0);
    u32 floor = floorGetNextFloorID();
    s32 i;
    for (i = 0; i < 20; ++i) if (floor == floors[i]) break;
    if (i >= 20) return heroGetObjID(0);
    s32 kind = menuCBBios_GetToolBattleTrainerKind();
    for (i = 0; i < 5; ++i) if (kind == models[i].kind) break;
    return models[i].id;
}
}

static void initFloor();
extern "C" {
u8 GSfloorIsPop();
void peopleOpen(u32, u32, u32);
void GSmodelEnableAnimBlend(void*);
void peopleAddCollision(u32, u32);
void peopleSetFlags(u32, u32, u32);
void peopleSetNeckLimitHold(u32, u32, u8);
void peopleSetRot(u32, u32, GSvec*);
void heroSetFollowerWithID(u8, u8);

s32 heroMoveInit(GSvec* position, GSvec* rotation) {
    s32 animationIndex;
    void* models[4];
    if (!GSfloorIsPop()) {
        u32 id = heroMoveGetKenObjID();
        peopleOpen(0, 0x64, id);
        peopleOpen(0, 0x65, 0x16C70400);
        peopleOpen(0, 0x68, 0x195B0400);
        peopleOpen(0, 0x69, 0x19540400);
    }
    for (s32 i = 0; i < 4; ++i) {
        models[i] = getModel((HEROMOVE_MEMBER)i);
        if (models[i]) GSmodelEnableAnimBlend(models[i]);
    }
    peopleAddCollision(0, 0x64);
    peopleAddCollision(0, 0x65);
    peopleAddCollision(0, 0x68);
    peopleAddCollision(0, 0x69);
    if (!GSfloorIsPop()) {
        peopleSetFlags(0, 0x64, 0x40000F00);
        peopleSetFlags(0, 0x65, 0x701);
        peopleSetFlags(0, 0x68, 0x701);
        peopleSetFlags(0, 0x69, 0x701);
    }
    peopleSetNeckLimitHold(0, 0x65, 1);
    peopleSetNeckLimitHold(0, 0x68, 1);
    peopleSetNeckLimitHold(0, 0x69, 1);
    if (!GSfloorIsPop()) {
        peopleSetPos(0, 0x64, position);
        peopleSetRot(0, 0x64, rotation);
    }
    animationIndex = 0;
    do {
        updateAnimation(0.0f, (HEROMOVE_MEMBER)animationIndex);
        ++animationIndex;
    } while (animationIndex < 4);
    initFloor();
    initLeaderLog();
    *(s32*)&HeroMove.raw[0x63C] = 0;
    *(s32*)&HeroMove.raw[0x640] = 0;
    *(s32*)&HeroMove.raw[0x638] = 0;
    *(s32*)&HeroMove.raw[0x3A8] = 0;
    ((AnalogStickEmu*)&HeroMove.raw[0x654])->init();
    Hero* hero = Hero::getHeroPtr();
    u8 follower = hero->getFollowerID();
    u8 level = hero->getFollowerModelLevel();
    if (follower) {
        heroMoveJoinMember(follower);
        heroSetFollowerWithID(follower, level);
    } else {
        heroMoveDismissMember(1);
        heroMoveDismissMember(2);
        heroMoveDismissMember(3);
    }
    return 0;
}
}

extern "C" {
double sin(double);
double cos(double);
struct WalkHeight { f32 height; u8 reserved[8]; };
s32 GScolsys2WalkGetHeight(GSvec*, WalkHeight*);
}

static void initFloor() {
    GSvec rotation, position, followerPosition;
    WalkHeight heights[8];
    s32 k;
    if (!GSfloorIsPop()) {
        getPos(&position, (HEROMOVE_MEMBER)heroMoveGetLeader());
        getRot(&rotation, (HEROMOVE_MEMBER)heroMoveGetLeader());
        f32 dz, dx;
        dx = sin(rotation.param2);
        dz = cos(rotation.param2);
        dx = -dx;
        followerPosition.param2 = position.param2;
        dz = -dz;
        f32 distance = 10.0f;
        for (s32 i = 0; i < 4; ++i) {
            if (heroMoveIsMember(i) && i != heroMoveGetLeader()) {
                followerPosition.param1 = dx * distance + position.param1;
                followerPosition.param2 = position.param2;
                followerPosition.param3 = dz * distance + position.param3;
                s32 count = GScolsys2WalkGetHeight(&followerPosition, heights);
                if (count > 0) {
                    if (count >= 2) {
                        f32 closest = -1000000.0f;
                        f32 highest = closest;
                        s32 found = 0;
                        for (s32 j = 0; j < count; ++j) {
                            f32 height = heights[j].height;
                            if (highest < height) highest = height;
                            if (!(height - followerPosition.param2 >= 100.0f) && closest < height) {
                                closest = height;
                                found = 1;
                            }
                        }
                        if (found) followerPosition.param2 = closest;
                        else followerPosition.param2 = highest;
                    } else {
                        followerPosition.param2 = heights[0].height;
                    }
                }
                distance += 10.0f;
                setPos((HEROMOVE_MEMBER)i, &followerPosition);
                setRot((HEROMOVE_MEMBER)i, &rotation);
            }
        }
    }
    setDisp(HEROMOVE_MEMBER_0, heroMoveIsMember(0));
    if (!GSfloorIsPop()) {
        for (s32 i = 1; i < 4; ++i) setDisp((HEROMOVE_MEMBER)i, heroMoveIsMember(i));
    }
    for (s32 i = 0; i < 4; ++i) initFootWork((FOOTWORK*)(HeroMove.raw + i * 0x20 + 0x14));
    for (k = 0; k < 4; ++k) {
        if (heroMoveIsMember(k)) heroMoveSetNeckMode(k, heroMoveGetNeckMode(k));
    }
    *(s32*)&HeroMove.raw[0x10] = 300;
    *(s32*)&HeroMove.raw[0x30] = 300;
    *(s32*)&HeroMove.raw[0x50] = 300;
    *(s32*)&HeroMove.raw[0x70] = 300;
    *(f32*)&HeroMove.raw[0x35C] = 0.0f;
}

extern "C" {
s8 GSinputGetLeftStickXData(u32, u8);
s8 GSinputGetLeftStickYData(u32, u8);
s8 GSinputGetRightStickXData(u32, u8);
s8 GSinputGetRightStickYData(u32, u8);
}

static void _getStickData(s8& x, s8& y, s8& rawX, s8& rawY) {
    s8 sx, sy, rx, ry;
    if (HeroMove.raw[0x3AE]) {
        sx = *(s8*)&HeroMove.raw[0x3AF];
        sy = *(s8*)&HeroMove.raw[0x3B0];
        rx = *(s8*)&HeroMove.raw[0x3B1];
        ry = *(s8*)&HeroMove.raw[0x3B2];
    } else {
        sx = GSinputGetLeftStickXData(1, 1);
        sy = GSinputGetLeftStickYData(1, 1);
        rx = GSinputGetLeftStickXData(1, 0);
        ry = GSinputGetLeftStickYData(1, 0);
        if (sx == 0 && sy == 0) {
            if (GSinputButtonsPressed(1) & 8) sy = -56;
            if (GSinputButtonsPressed(1) & 4) sy = 56;
            if (GSinputButtonsPressed(1) & 1) sx = -56;
            if (GSinputButtonsPressed(1) & 2) sx = 56;
            rx = sx;
            ry = sy;
        }
        if (cameraGetType() != 6 && cameraGetType() != 5 && sx == 0 && sy == 0 && rx == 0 && ry == 0) {
            s8 cry, crx, cy, cx;
            cx = GSinputGetRightStickXData(1, 1);
            if ((cx < 0 ? -cx : cx) < 16) cx = 0;
            cy = GSinputGetRightStickYData(1, 1);
            if ((cy < 0 ? -cy : cy) < 16) cy = 0;
            crx = GSinputGetRightStickXData(1, 0);
            if ((crx < 0 ? -crx : crx) < 16) crx = 0;
            cry = GSinputGetRightStickYData(1, 0);
            if ((cry < 0 ? -cry : cry) < 16) cry = 0;
            sx = cx * 56 / 44;
            sy = cy * 56 / 44;
            rx = crx * 56 / 44;
            ry = cry * 56 / 44;
        }
    }
    x = sx; y = sy; rawX = rx; rawY = ry;
    ((AnalogStickEmu*)&HeroMove.raw[0x654])->calculate(x, y, rawX, rawY);
    if (gimmickBoxIsGimmickMoving()) { x = 0; y = 0; rawX = 0; rawY = 0; }
}

struct FOOTSTEP {f32 speed[4]; GSvec positions[4];};
struct _GSmodel;
extern "C" {
f32 GSgfxVideoGetLastRenderTime();
void* GSmodelGetPart(_GSmodel*,s32);
void GSpartGetTransform(void*,GSvec*,GSvec*,GSvec*);
void GSpartFree(void*);
}
static void getStep(FOOTSTEP* step,_GSmodel* model,int* parts,FOOTWORK* work) {
    GSvec modelPos;
    GSvec partPos;
    f32 heights[4];
    f32 time, zero;
    time=GSgfxVideoGetLastRenderTime();
    GSmodelGetPosition(model,&modelPos);
    f32* base=heights;
    f32* height=base;
    zero=0.0f;
    int* part=parts;
    for(s32 i=0;i<4;i++,part++,height++) {
        step->positions[i].param1=zero;
        step->positions[i].param2=zero;
        step->positions[i].param3=zero;
        *height=zero;
        if(*part>=0) {
            void* object=GSmodelGetPart(model,*part);
            if(object) {
                GSpartGetTransform(object,&partPos,0,0);
                GSpartFree(object);
                *height=partPos.param2-modelPos.param2;
                step->positions[i].param1=partPos.param1;
                step->positions[i].param2=partPos.param2;
                step->positions[i].param3=partPos.param3;
            }
        }
    }
    f32 threshold=0.5f;
    zero=0.0f;
    if(work->a>=threshold && heights[0]<threshold)step->speed[0]=(work->a-heights[0])/time;
    else step->speed[0]=zero;
    if(work->b>=threshold && heights[1]<threshold)step->speed[1]=(work->b-heights[1])/time;
    else step->speed[1]=zero;
    if(work->c>=threshold && base[2]<threshold)step->speed[2]=(work->c-base[2])/time;
    else step->speed[2]=zero;
    if(work->d>=threshold && base[3]<threshold)step->speed[3]=(work->d-base[3])/time;
    else step->speed[3]=zero;
    work->a=heights[0];work->b=heights[1];work->c=base[2];work->d=base[3];
}

static void updateLeaderLog() {
    GSvec previous,current;
    u8 append=0;
    getPos(&current,(HEROMOVE_MEMBER)heroMoveGetLeader());
    if(getLeaderLog(&previous,1)) {
        f32 x=previous.param1-current.param1;
        f32 z=previous.param3-current.param3;
        f32 xs=x*x,zs=z*z;
        f32 mag=xs+zs;
        if(mag>0.0f) {
            f64 guess=__frsqrte((f64)mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            mag=(f32)(mag*guess);
        } else if(mag<0.0)mag=__float_nan[0];
        else {
            s32 classification;
            f32 classifyValue=mag;
            switch(*(s32*)&classifyValue & 0x7F800000) {
            case 0x7F800000: if(*(s32*)&classifyValue & 0x7FFFFF)classification=1;else classification=2;break;
            case 0: if(*(s32*)&classifyValue & 0x7FFFFF)classification=5;else classification=3;break;
            default: classification=4;break;
            }
            if(classification==1)mag=__float_nan[0];
        }
        if(mag>1.0f)append=1;
    } else append=1;
    if(append) {
        for(s32 i=58;i>=0;i--) {
            HeroMove.leaderLog.log[i+1].param1=HeroMove.leaderLog.log[i].param1;
            HeroMove.leaderLog.log[i+1].param2=HeroMove.leaderLog.log[i].param2;
            HeroMove.leaderLog.log[i+1].param3=HeroMove.leaderLog.log[i].param3;
        }
        *(s32*)&HeroMove.raw[0x84]=0;
        HeroMove.leaderLog.log[0].param1=current.param1;
        HeroMove.leaderLog.log[0].param2=current.param2;
        HeroMove.leaderLog.log[0].param3=current.param3;
        if(*(s32*)&HeroMove.raw[0x88]<60)(*(s32*)&HeroMove.raw[0x88])++;
    }
}

extern "C" {
f32 cameraGetRotY();
f32 peopleGetBlendFactor(f32,f32,f32);
void peopleRotateToAngle(u32,u32,f32,f32);
void peopleMoveForward(u32,u32,f32);
void peopleRotateStop(u32,u32);
f64 sin(f64);
}
static void updateLeaderMovement(HEROMOVE_MEMBER member,float* movement) {
    unsigned long group,res;
    s8 x,y,rx,ry;
    GSresGetResource(0,2);
    getResID(&group,&res,member);
    getModel(member);
    _getStickData(x,y,rx,ry);
    if(!gimmickBoxIsGimmickMoving()) {
        if(x || y) {
            if(x>56)x=56;else if(x<-56)x=-56;
            if(y>56)y=56;else if(y<-56)y=-56;
            f32 mag,ax,ay;
            ax=(f32)(x>0?x:-x)/28.0f;
            ay=(f32)(y>0?y:-y)/28.0f;
            mag=ax*ax+ay*ay;
        if(mag>0.0f) {
            f64 guess=__frsqrte((f64)mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            mag=(f32)(mag*guess);
        } else if(mag<0.0)mag=__float_nan[0];
        else {
            s32 classification;
            f32 classifyValue=mag;
            switch(*(s32*)&classifyValue & 0x7F800000) {
            case 0x7F800000: if(*(s32*)&classifyValue & 0x7FFFFF)classification=1;else classification=2;break;
            case 0: if(*(s32*)&classifyValue & 0x7FFFFF)classification=5;else classification=3;break;
            default: classification=4;break;
            }
            if(classification==1)mag=__float_nan[0];
        }
            *movement=mag;
            if(*movement>2.0f)*movement=2.0f;
            if(rx<=-2 || rx>=2 || ry<=-2 || ry>=2) {
                f32 angle;
                if(ay<0.001f)angle=1.5707964f;
                else {
                    f32 ratio=ax/ay;
                    if(ratio>5.0f)ratio=5.0f;
                    angle=1.5707964f*(f32)sin(ratio/3.1830988f);
                }
                f32 rotation;
                if(y>=0)rotation=angle;else rotation=3.1415927f-angle;
                if(x<0) {
                    if(y>=0)rotation=3.1415927f+(3.1415927f-angle);
                    else rotation=3.1415927f+angle;
                }
                peopleRotateToAngle(group,res,rotation+cameraGetRotY(),*movement);
            }
            u8* people=(u8*)peopleSearchID(peopleGetHumanID(group,res));
            if(*movement<1.0f)*movement=*(f32*)(people+0x20)*peopleGetBlendFactor(*movement,0.0f,1.0f);
            else {
                f32 blend=peopleGetBlendFactor(*movement,1.0f,2.0f);
                *movement=(1.0f-blend)**(f32*)(people+0x20)+blend**(f32*)(people+0x24);
            }
            peopleMoveForward(group,res,*movement);
        } else {
            *movement=0.0f;
            peopleRotateStop(group,res);
        }
    }
}

extern "C" {
f32 peopleInfoBiosGetColBallSize(void*);
u8 GScolsys2HitCollision(GSvec*,GSvec*,s32);
void PSVECScale(GSvec*,GSvec*,f32);
s32 GScolsys2HumanCollision(void*,GSvec*,GSvec*,s32);

u8 heroMoveChkHinderClear(s32 member) {
    GSvec memberPosition,leaderPosition,direction,scaled;
    unsigned long group,res;
    if(!heroMoveIsMember(member))return 0;
    HEROMOVE_MEMBER leader=(HEROMOVE_MEMBER)heroMoveGetLeader();
    getPos(&memberPosition,(HEROMOVE_MEMBER)member);
    memberPosition.param2+=8.5f;
    getPos(&leaderPosition,leader);
    leaderPosition.param2+=8.5f;
    u32 object=getObjID((HEROMOVE_MEMBER)member);
    if(object==0xFFFFFFFF)return 0;
    void* info=peopleInfoBiosGetPtr(object);
    if(!info)return 0;
    f32 memberSize=peopleInfoBiosGetColBallSize(info);
    if(GScolsys2HitCollision(&memberPosition,&leaderPosition,0))return 0;
    object=getObjID(leader);
    if(object==0xFFFFFFFF)return 0;
    info=peopleInfoBiosGetPtr(object);
    if(!info)return 0;
    f32 leaderSize=peopleInfoBiosGetColBallSize(info);
    getResID(&group,&res,(HEROMOVE_MEMBER)member);
    u8* people=(u8*)peopleSearchID(peopleGetHumanID(group,res));
    if(!people)return 0;
    void* collision=*(void**)(people+0x50);
    getPos(&memberPosition,(HEROMOVE_MEMBER)member);
    getPos(&leaderPosition,leader);
    PSVECSubtract(&leaderPosition,&memberPosition,&direction);
    f32 x=memberPosition.param1-leaderPosition.param1;
    f32 z=memberPosition.param3-leaderPosition.param3;
    f32 mag,radius;
    radius=memberSize+leaderSize;
    f32 xs=x*x,zs=z*z;
    mag=xs+zs;
        if(mag>0.0f) {
            f64 guess=__frsqrte((f64)mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            guess=0.5*guess*(3.0-guess*guess*mag);
            mag=(f32)(mag*guess);
        } else if(mag<0.0)mag=__float_nan[0];
        else {
            s32 classification;
            f32 classifyValue=mag;
            switch(*(s32*)&classifyValue & 0x7F800000) {
            case 0x7F800000: if(*(s32*)&classifyValue & 0x7FFFFF)classification=1;else classification=2;break;
            case 0: if(*(s32*)&classifyValue & 0x7FFFFF)classification=5;else classification=3;break;
            default: classification=4;break;
            }
            if(classification==1)mag=__float_nan[0];
        }
    if(mag<=0.0f)return 1;
    if(mag<=radius)return 1;
    PSVECScale(&direction,&scaled,(mag-radius-0.010000001f)/mag);
    PSVECAdd(&memberPosition,&scaled,&leaderPosition);
    return GScolsys2HumanCollision(collision,&memberPosition,&leaderPosition,0)!=6;
}
}

struct HeroMoveEvent {GSvec points[3]; u8 data[16];};
extern "C" {
void __ct__5GSvecFv(void*);
void __construct_array(void*,void (*)(void*),void (*)(void*),u32,u32);
tagPeopleWork* peopleTalkCheck(u32,u32,f32,f32);
void GSinputResetLeftSmoothing(u32,s32,s32);
void GSinputResetRightSmoothing(u32,s32,s32);
void peopleGetNeckPos(u32,u32,GSvec*);
void peopleRotateToXYZ(u32,u32,f32,f32,f32,f32);
u8 peopleCheckTresure(u32,u32);
void floorEventCtrlTresure(u32,u32,s32);
void peopleBlockMoveScript(u32);
void peopleUnblockMoveScript(u32);
void peopleWalkPause(u32,u32,s32);
s32 peopleGetTalkSctID(u32,u32);
void peopleWalkPauseTalkMode(u32,u32,s32);
void floorExecScriptRes(s32,u32,u32);
void peopleTalkMsgEnd(u32,u32);
u8 peopleBiosCheckFlag(void*,u32);
}
static u8 updateChat(HEROMOVE_MEMBER member) {
    HeroMoveEvent events[4];
    GSvec neck;
    unsigned long group,res;
    getResID(&group,&res,member);
    tagPeopleWork* person=peopleTalkCheck(group,res,0.3f,40.0f);
    s32 script;
    if(!person) {
        s32 count;
        __construct_array(events[0].points,__ct__5GSvecFv,0,12,3);
        __construct_array(events[1].points,__ct__5GSvecFv,0,12,3);
        __construct_array(events[2].points,__ct__5GSvecFv,0,12,3);
        __construct_array(events[3].points,__ct__5GSvecFv,0,12,3);
        count=heroMoveCheckEvent(events);
        heroMoveSetEventList(3,events,count);
        if(count) {peopleRotateStop(0,100);return 1;}
        return 0;
    }
    GSinputResetLeftSmoothing(1,0,0);
    GSinputResetRightSmoothing(1,0,0);
    heroMoveInitEvent();
    peopleGetNeckPos(person->group,person->resource,&neck);
    peopleRotateToXYZ(group,res,neck.param1,neck.param2,neck.param3,1.0f);
    if(peopleCheckTresure(person->group,person->resource))floorEventCtrlTresure(person->group,person->resource,2);
    else {
        u8 moving=0;
        u8 type=person->getMoveType();
        if(type==2 || type==3)moving=1;
        peopleBlockMoveScript(peopleGetHumanID(person->group,person->resource));
        if(moving)peopleWalkPause(person->group,person->resource,1);
        script=peopleGetTalkSctID(person->group,person->resource);
        if(script) {
            peopleWalkPauseTalkMode(person->group,person->resource,1);
            floorExecScriptRes(script,person->group,person->resource);
            peopleWalkPauseTalkMode(person->group,person->resource,0);
            peopleTalkMsgEnd(person->group,person->resource);
        }
        if(moving && !peopleBiosCheckFlag(person,0x80000))peopleWalkPause(person->group,person->resource,0);
        peopleUnblockMoveScript(peopleGetHumanID(person->group,person->resource));
    }
    heroMoveTermEvent();
    GSinputResetLeftSmoothing(1,0,0);
    GSinputResetRightSmoothing(1,0,0);
    return 1;
}

static void procStep(HEROMOVE_MEMBER member) {
    int parts[2][4]={{0x35,0x30,-1,-1},{0x2E,0x29,-1,-1}};
    GSgfxVideoGetLastRenderTime();
    FOOTSTEP step;
    __construct_array(step.positions,__ct__5GSvecFv,0,12,4);
    _GSmodel* model=(_GSmodel*)getModel(member);
    if(model)getStep(&step,model,parts[member],(FOOTWORK*)(HeroMove.raw+member*0x20+0x14));
}

#pragma dollar_identifiers on
extern "C" {
static f32 radius_fix$2457;
static s8 init$2458;
static f32 len_fix$2474;
static s8 init$2475;
u8 peopleBiosCheckFlag(void*,u32);
GSvec* peopleBiosGetPrevPosPtr(void*);
f32 peopleVecCalcRotY(GSvec*,GSvec*,f32);
f32 peopleGetBlendFactor(f32,f32,f32);
f32 GScolsys2HumanGetWalkHeight(GSvec*);
void peopleRotateToAngle(u32,u32,f32,f32);
void peopleMoveAlongAngle(u32,u32,f32,f32);
void PSVECNormalize(GSvec*,GSvec*);
}
static f32 moveParty(HEROMOVE_MEMBER member) {
    GSvec destination;
    GSvec direction;
    GSvec closeDirection;
    GSvec difference;
    GSvec added;
    s8 x,y,rx,ry;
    tagPeopleWork* current=(tagPeopleWork*)_heroGetPeople(member);
    if (!current) return 0.0f;
    if (current->attachIndex>0) {
        *(s32*)&HeroMove.raw[0x88]=0;
        return 0.0f;
    }
    tagPeopleWork* leader=(tagPeopleWork*)peopleGet(0,0x64);
    if (!leader) return 0.0f;
    Hero* hero=Hero::getHeroPtr();
    tagPeopleWork* follower=(tagPeopleWork*)peopleGet(hero->getFollowerGrpID(),hero->getFollowerResID());
    if (!follower) return 0.0f;
    if (peopleBiosCheckFlag(follower,0x80000000)) return 0.0f;
    GSvec* leaderPosition=(GSvec*)((void*(*)(void*))peopleBiosGetPosPtr)(leader);
    GSvec* position=(GSvec*)((void*(*)(void*))peopleBiosGetPosPtr)(follower);
    s32 followerID=heroGetFollower();
    if (!followerID) return 0.0f;
    if (heroMoveChkHinderClear(followerID) && !follower->followerMotion) *(s32*)&HeroMove.raw[0x88]=0;
    if (!init$2458) { init$2458=1;radius_fix$2457=3.0f; }
    for(s32 i=0;i<*(s32*)&HeroMove.raw[0x88];i++) {
        if(PSVECDistance(position,&HeroMove.leaderLog.log[i])<radius_fix$2457) {
            *(s32*)&HeroMove.raw[0x88]=i+1;
            break;
        }
    }
    if(current->followerMotion) return 0.0f;
    s32 count=*(s32*)&HeroMove.raw[0x88];
    if(count>0) {
        GSvec* point=&HeroMove.leaderLog.log[count-1];
        destination.param1=point->param1;destination.param2=point->param2;destination.param3=point->param3;
    }
    else {
        PSVECSubtract(position,leaderPosition,&difference);
        direction.param1=difference.param1;direction.param2=difference.param2;direction.param3=difference.param3;
        u8 zero;
        if(!(direction.param1<0.00001f) || !(direction.param1>-0.00001f) ||
           !(direction.param2<0.00001f) || !(direction.param2>-0.00001f) ||
           !(direction.param3<0.00001f) || !(direction.param3>-0.00001f)) zero=0;
        else zero=1;
        if(zero) {
            direction.param1=0.0f;direction.param2=0.0f;direction.param3=1.0f;
        }
        PSVECNormalize(&direction,&direction);
        PSVECScale(&direction,&direction,10.950001f);
        PSVECAdd(leaderPosition,&direction,&added);
        destination.param1=added.param1;destination.param2=added.param2;destination.param3=added.param3;
    }
    GSvecDistanceXZ(position,&destination);
    f32 distance=GSvecDistanceXZ(position,leaderPosition);
    _getStickData(x,y,rx,ry);
    if(!init$2475) { init$2475=1;len_fix$2474=0.5f; }
    if(distance<12.0f-len_fix$2474 && !x && !y && !rx && !ry) return 0.0f;
    follower->walkTarget.param1=destination.param1;
    follower->walkTarget.param2=destination.param2;
    follower->walkTarget.param3=destination.param3;
    f32 movementAngle=peopleVecCalcRotY(position,&follower->walkTarget,0.0f);
    f32 facingAngle=peopleVecCalcRotY(position,leaderPosition,0.0f);
    f32 speed;
    if(distance<=12.0f) {
        PSVECSubtract(position,leaderPosition,&closeDirection);
        if(distance<0.00001f && distance>-0.00001f) {
            closeDirection.param1=0.0f;closeDirection.param2=0.0f;closeDirection.param3=10.950001f;
        } else {
            closeDirection.param2=0.0f;
            PSVECNormalize(&closeDirection,&closeDirection);
            PSVECScale(&closeDirection,&closeDirection,10.950001f);
        }
        PSVECAdd(leaderPosition,&closeDirection,&follower->walkTarget);
        follower->walkTarget.param2=GScolsys2HumanGetWalkHeight(&follower->walkTarget);
        movementAngle=peopleVecCalcRotY(position,&follower->walkTarget,0.0f);
        if(distance<9.900001f) {
            if(distance<=9.0f) speed=leader->unknown2C;
            else speed=leader->unknown2C*peopleGetBlendFactor(distance,9.900001f,9.0f);
        } else speed=0.0f;
    } else if(distance<18.0f) {
        speed=leader->unknown24*peopleGetBlendFactor(distance,12.0f,18.0f);
    } else speed=leader->unknown24;
    peopleRotateToAngle(hero->getFollowerGrpID(),hero->getFollowerResID(),facingAngle,20.0f);
    peopleMoveAlongAngle(hero->getFollowerGrpID(),hero->getFollowerResID(),speed,movementAngle);
    return GSvecDistanceXZ((GSvec*)((void*(*)(void*))peopleBiosGetPosPtr)(follower),peopleBiosGetPrevPosPtr(follower));
}
