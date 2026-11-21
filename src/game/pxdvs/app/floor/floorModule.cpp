#include <game/pxdvs/app/floor/floorModulePrivate.hpp>
extern "C" void *memset(void *, int, u32);

struct FloorData;
extern "C" {
FloorData *floorDataBiosGetPtr(u32);
u32 floorDataBiosGetGroupID(FloorData *);
void *GSmemAlloc(u32);
void GSmemFree(void *);
void *floorCreateThread(s32, u32, s32, s32 (*)(GSthread *));
void GSthreadSetName(void *, const char *);
void GSthreadSwitch();
}
GSscript::Tiga *floorGetCommonScript();
GSscript::Tiga *floorGetCurentScript();

static void _dispModuleName(FloorModuleInterface *, const char *);
static const char *_floorStateToStr(FloorState);

void FloorModuleList::dumpModule() {}

void FloorModuleList::waitFloorScript(FloorState state) {
    while (!executeIsDone(state)) GSthreadSwitch();
}

bool FloorModuleList::executeIsDone(FloorState state) {
    for (FloorModuleEntry *e = head; e; e = e->getNext()) {
        if (!e->isBlock() && e->isScriptRunning(state)) return false;
    }
    return true;
}

void FloorModuleList::executeAll(unsigned int a, FloorState state, FloorModuleType type, FloorEnterMode mode, u32 group) {
    FloorModuleEntry *e;
    if (state == FloorStatePost || state == FloorStateFree) {
        e = getFMEEnd();
        while (e) {
            FloorModuleEntry *other = e->getPrev();
            if ((group == e->getGroupID() || !e->isBlock()) && (type == FloorTypeAny || type == e->getType())) {
                e->exec(state, a, mode);
            }
            if (e->getPrev()) e = e->getPrev();
            else e = other;
        }
    } else {
        e = head;
        while (e) {
            FloorModuleEntry *other = e->getNext();
            if ((group == e->getGroupID() || !e->isBlock()) && (type == FloorTypeAny || type == e->getType())) {
                e->exec(state, a, mode);
            }
            if (e->getNext()) e = e->getNext();
            else e = other;
        }
    }
}

struct FloorModuleStateHeader {
    u32 id;
    u32 size;
};

void FloorModuleList::restorePopState(void* buffer, FloorStateMode mode, bool freeBuffer) {
    u8* start = (u8*)buffer;
    if (start) {
        dumpModule();
        u32* words = (u32*)start;
        u32 id = *words++;
        u32 recordSize = *words++;
        u8* cursor = (u8*)words;
        u8* end = start + recordSize;
        if (id != 'FLOR') return;

        while (cursor < end) {
            words = (u32*)cursor;
            id = *words++;
            recordSize = *words++;
            cursor = (u8*)words;
            for (FloorModuleEntry* entry = head; entry; entry = entry->getNext()) {
                FloorModuleInterface* module = entry->getModuleInterface();
                if (module && module->getStateSize && id == module->getStateID()) {
                    module->loadState(mode, cursor, recordSize - sizeof(FloorModuleStateHeader));
                    cursor += recordSize - sizeof(FloorModuleStateHeader);
                    break;
                }
            }
        }
        if (freeBuffer) GSmemFree(start);
    }
}

void* FloorModuleList::makePushState(FloorStateMode mode) {
    FloorModuleEntry* entry;
    u32 aligned;
    FloorModuleInterface* module;
    u8* cursor;
    u32 payloadSize;
    u8* data;
    u32 total;
    void* buffer;
    dumpModule();
    total = 0;
    for (FloorModuleEntry* sizingEntry = head; sizingEntry; sizingEntry = sizingEntry->getNext()) {
        module = sizingEntry->getModuleInterface();
        if (module && module->getStateSize) {
            payloadSize = module->getStateSize(mode);
            if (payloadSize) total += ((payloadSize + 3) & ~3) + sizeof(FloorModuleStateHeader);
        }
    }
    FloorModuleStateHeader* header = (FloorModuleStateHeader*)GSmemAlloc(total + sizeof(*header));
    buffer = header;
    if (!header) return 0;
    size = total + sizeof(FloorModuleStateHeader);
    u32* words = (u32*)header;
    *words++ = 'FLOR';
    *words++ = total + sizeof(*header);
    cursor = (u8*)words;
    for (entry = head; entry; entry = entry->getNext()) {
        module = entry->getModuleInterface();
        if (module && module->getStateSize) {
            payloadSize = module->getStateSize(mode);
            if (payloadSize == 0) {
                if (mode == 3) module->saveState(mode, 0, 0);
            } else {
                aligned = (payloadSize + 3) & ~3;
                if (!module->getStateID) return 0;
                FloorModuleStateHeader* record = (FloorModuleStateHeader*)cursor;
                record->id = module->getStateID();
                record->size = aligned + sizeof(*record);
                data = (u8*)(record + 1);
                module->saveState(mode, data, aligned);
                cursor = data + aligned;
            }
        }
    }
    return buffer;
}

void FloorModuleList::killModuleGroup(u32 group) {
    for (FloorModuleEntry *e = head; e; e = e->getNext()) {
        if (group == e->getGroupID()) killModule(e->getHandle());
    }
    floorGetCommonScript()->deleteThreadGroup(group);
    floorGetCurentScript()->deleteThreadGroup(group);
}

void FloorModuleList::unblockModuleGroup(u32 group) {
    for (FloorModuleEntry *e = head; e; e = e->getNext()) {
        if (group == e->getGroupID()) unblockModule(e->getHandle());
    }
    floorGetCommonScript()->unblockThreadGroup(group);
    floorGetCurentScript()->unblockThreadGroup(group);
}

void FloorModuleList::blockModuleGroup(u32 group) {
    for (FloorModuleEntry *e = head; e; e = e->getNext()) {
        if (group == e->getGroupID()) blockModule(e->getHandle());
    }
    floorGetCommonScript()->blockThreadGroup(group);
    floorGetCurentScript()->blockThreadGroup(group);
}

void FloorModuleList::unregisterModuleGroup(u32 group) {
    for (FloorModuleEntry *e = entries; e != entries + count; ++e) {
        if (group == e->getGroupID()) unregisterModule(e->getHandle());
    }
}

void FloorModuleList::killModule(u32 handle) {
    FloorModuleEntry *e = findHandle(handle);
    if (e) e->kill();
}

void FloorModuleList::unblockModule(u32 handle) {
    FloorModuleEntry *e = findHandle(handle);
    if (e) e->unblock();
}

void FloorModuleList::blockModule(u32 handle) {
    FloorModuleEntry *e = findHandle(handle);
    if (e) e->block();
}

void FloorModuleList::unregisterModule(u32 handle) {
    FloorModuleEntry *e = findHandle(handle);
    if (e) {
        e->terminate();
        removeFuncFromList(e);
        e->init();
    }
}

u32 FloorModuleList::registerScriptModule(u8 priority, u32 group, u32 a, u32 b, u32 c) {
    FloorModuleEntry *e = findFree();
    if (!e) return 0;
    e->init();
    e->setScriptModule(priority, group, a, b, c);
    insertFuncIntoList(e);
    e->setHandle(getNewHandle());
    return e->getHandle();
}

u32 FloorModuleList::registerModule(u8 priority, u32 group, FloorModuleInterface *module) {
    if (!module) return 0;
    FloorModuleEntry *e = findFree();
    if (!e) return 0;
    e->init();
    e->setModule(priority, group, module);
    insertFuncIntoList(e);
    e->setHandle(getNewHandle());
    return e->getHandle();
}

void FloorModuleList::removeFuncFromList(FloorModuleEntry *e) {
    if (e->getPrev()) {
        FloorModuleEntry *p = e->getPrev();
        p->setNext(e->getNext());
    }
    if (e->getNext()) {
        FloorModuleEntry *n = e->getNext();
        n->setPrev(e->getPrev());
    }
    if (head == e) head = e->getNext();
    e->setPrev(0);
    e->setNext(0);
}

void FloorModuleList::insertFuncIntoList(FloorModuleEntry *e) {
    if (!head) {
        head = e;
        return;
    }
    FloorModuleEntry *cur = head;
    for (; cur->getNext(); cur = cur->getNext()) {
        if (cur->getPriority() >= e->getPriority()) break;
    }
    if (!cur->getNext() && cur->getPriority() < e->getPriority()) {
        e->setPrev(cur);
        e->setNext(0);
        cur->setNext(e);
    } else {
        if (cur->getPrev()) cur->getPrev()->setNext(e);
        e->setPrev(cur->getPrev());
        e->setNext(cur);
        cur->setPrev(e);
        if (head == cur) head = e;
    }
}

FloorModuleEntry *FloorModuleList::findHandle(u32 handle) {
    for (FloorModuleEntry *e = entries; e != entries + count; ++e) {
        if (!e->isEmpty() && handle == e->getHandle()) return e;
    }
    return 0;
}

FloorModuleEntry *FloorModuleList::findFree() {
    if (!entries) return 0;
    for (FloorModuleEntry *e = entries; e != entries + count; ++e) {
        if (e->isEmpty()) return e;
    }
    return 0;
}

FloorModuleEntry *FloorModuleList::getFMEEnd() {
    FloorModuleEntry *p = head;
    FloorModuleEntry *last = 0;
    while (p) {
        last = p;
        p = p->getNext();
    }
    return last;
}

FloorModuleList::~FloorModuleList() {
    delete[] entries;
}

FloorModuleList::FloorModuleList(u32 n) {
    count = n;
    head = 0;
    entries = new FloorModuleEntry[n];
    if (!entries) return;
    handleCounter = 1;
}

bool FloorModuleEntry::isScriptRunning(FloorState s) {
    switch (type) {
    case FloorTypeTpc:
        return script.isRunning(s);
    case FloorTypeSingleTpc:
        if (s == state) return tpc.isRunning();
        return false;
    default:
        return false;
    }
}

#pragma opt_common_subs off
void FloorModuleEntry::exec(FloorState s, unsigned int a, FloorEnterMode mode) {
    FloorData *data = floorDataBiosGetPtr(a);
    if (data) {
        u32 group = floorDataBiosGetGroupID(data);
        switch (type) {
        case FloorTypeFunc:
            if (FloorModuleInterface_exec(&module, s, a, mode, !entered)) entered = 1;
            break;
        case FloorTypeTpc:
            script.exec(s, priority, group, mode);
            break;
        case FloorTypeSingleTpc:
            if (s == state) tpc.exec(priority, group, mode);
            break;
        }
    }
}
#pragma opt_common_subs reset

void FloorModuleEntry::terminate() {
    switch (type) {
    case FloorTypeTpc:
        script.terminate();
        break;
    case FloorTypeSingleTpc:
        tpc.terminate();
        break;
    }
}

void FloorModuleEntry::kill() {
    if (isTpcScript()) script.kill();
}

void FloorModuleEntry::unblock() {
    blocked = 0;
    switch (type) {
    case FloorTypeTpc:
        script.unblock();
        break;
    case FloorTypeSingleTpc:
        tpc.unblock();
        break;
    }
}

void FloorModuleEntry::block() {
    blocked = 1;
    switch (type) {
    case FloorTypeTpc:
        script.block();
        break;
    case FloorTypeSingleTpc:
        tpc.block();
        break;
    }
}

void FloorModuleEntry::setScriptModule(u8 prio, u32 group, u32 a, u32 b, u32 c) {
    init();
    type = FloorTypeTpc;
    groupID = group;
    priority = prio;
    script.setIDs(a, b, c);
}

void FloorModuleEntry::setModule(u8 prio, u32 group, FloorModuleInterface *m) {
    init();
    type = FloorTypeFunc;
    groupID = group;
    priority = prio;
    module = *m;
}

void FloorModuleEntry::init() {
    prev = 0;
    next = 0;
    blocked = 0;
    entered = 0;
    handle = 0;
    groupID = 0;
    priority = 0;
}

FloorModuleEntry::FloorModuleEntry() {
    init();
}

bool FloorScriptModule::isRunning(FloorState s) {
    ScriptTpcNode *n = stateToNode(s);
    if (n) return n->isRunning();
    return false;
}

void FloorScriptModule::kill() {
    nodes[0].terminate();
    nodes[1].terminate();
    nodes[2].terminate();
}

void FloorScriptModule::terminate() {
    nodes[0].terminate();
    nodes[1].terminate();
    nodes[2].terminate();
}

void FloorScriptModule::unblock() {
    nodes[0].unblock();
    nodes[1].unblock();
    nodes[2].unblock();
}

void FloorScriptModule::block() {
    nodes[0].block();
    nodes[1].block();
    nodes[2].block();
}

void FloorScriptModule::exec(FloorState s, u8 prio, u32 group, FloorEnterMode mode) {
    ScriptTpcNode *n = stateToNode(s);
    if (n) n->exec(prio, group, mode);
}

ScriptTpcNode *FloorScriptModule::stateToNode(FloorState s) {
    switch (s) {
    case FloorStatePre:
        return &nodes[0];
    case FloorStateNormal:
        return &nodes[1];
    case FloorStatePost:
        return &nodes[2];
    default:
        return 0;
    }
}

bool ScriptTpcNode::isRunning() {
    if (!getScript()->isRunningThread(thread)) {
        thread = 0;
        return false;
    }
    return true;
}

void ScriptTpcNode::exec(u8, u32, FloorEnterMode mode) {
    GSscript::tigaVariant args[4];
    args[0].setInteger(mode);
    args[1].setInteger(0);
    args[2].setInteger(0);
    args[3].setInteger(0);
    thread = getScript()->runParams(id, args, 4, true);
}

void ScriptTpcNode::terminate() {
    getScript()->deleteThread(thread);
}

void ScriptTpcNode::unblock() {
    getScript()->unblockThread(thread);
}

void ScriptTpcNode::block() {
    getScript()->blockThread(thread);
}

GSscript::Tiga *ScriptTpcNode::getScript() {
    if ((id & 0xFFFF0000) == 0x05960000) return floorGetCommonScript();
    return floorGetCurentScript();
}

void ScriptTpcNode::setID(u32 v) {
    id = v;
    thread = 0;
}

// MWCC emits these definitions in reverse order, after the virtual table.
#pragma defer_codegen on

inline void GSscript::tigaVariant::setInteger(s32 v) {
    type = 1;
    value = v;
}

inline void FloorScriptModule::setIDs(u32 a, u32 b, u32 c) {
    nodes[0].setID(a);
    nodes[1].setID(b);
    nodes[2].setID(c);
}

inline bool FloorModuleEntry::isTpcScript() const {
    return type == FloorTypeTpc;
}

inline bool FloorModuleEntry::isEmpty() const {
    return handle == 0;
}

inline u8 FloorModuleEntry::getPriority() const {
    return priority;
}

inline void FloorModuleEntry::setNext(FloorModuleEntry *n) {
    next = n;
}

inline void FloorModuleEntry::setPrev(FloorModuleEntry *p) {
    prev = p;
}

inline u32 FloorModuleList::getNewHandle() {
    handleCounter = handleCounter + 1;
    if (handleCounter == 0) handleCounter = handleCounter + 1;
    return handleCounter;
}

inline void FloorModuleEntry::setHandle(u32 h) {
    handle = h;
}

inline u32 FloorModuleEntry::getHandle() const {
    return handle;
}

inline FloorModuleInterface *FloorModuleEntry::getModuleInterface() {
    if (type == FloorTypeFunc) return &module;
    return 0;
}

inline FloorModuleEntry *FloorModuleEntry::getPrev() const {
    return prev;
}

inline u32 FloorModuleEntry::getGroupID() const {
    return groupID;
}

inline FloorModuleType FloorModuleEntry::getType() const {
    return type;
}

inline u8 FloorModuleEntry::isBlock() const {
    return blocked;
}

inline FloorModuleEntry *FloorModuleEntry::getNext() const {
    return next;
}

static const char *_floorStateToStr(FloorState s) {
    switch (s) {
    case FloorStateUnused:
        return "FloorStateUnused";
    case FloorStateCreate:
        return "FloorStateCreate";
    case FloorStatePre:
        return "FloorStatePre";
    case FloorStatePreWait:
        return "FloorStatePreWait";
    case FloorStateNormal:
        return "FloorStateNormal";
    case FloorStateNormalWait:
        return "FloorStateNormalWait";
    case FloorStatePost:
        return "FloorStatePost";
    case FloorStatePostWait:
        return "FloorStatePostWait";
    case FloorStateFree:
        return "FloorStateFree";
    default:
        return "unknownState";
    }
}

static const char *_floorTypeToStr(FloorModuleType t) {
    switch (t) {
    case FloorTypeFunc:
        return "FloorTypeFunc";
    case FloorTypeGSvm:
        return "FloorTypeGSvm";
    case FloorTypeTpc:
        return "FloorTypeTpc";
    case FloorTypeSingleGSvm:
        return "FloorTypeSingleGSvm";
    case FloorTypeSingleTpc:
        return "FloorTypeSingleTpc";
    case FloorTypeAny:
        return "FloorTypeAny";
    default:
        return "FloorUnknown";
    }
}

void FloorModuleInterface_clear(FloorModuleInterface *m) {
    memset(m, 0, sizeof(FloorModuleInterface));
}

static void _dispModuleName(FloorModuleInterface *, const char *) {}

u8 FloorModuleInterface_exec(FloorModuleInterface *m, FloorState state, u32 a, FloorEnterMode mode, bool createThread) {
    switch (state) {
    case FloorStateCreate:
        if (m->create) {
            _dispModuleName(m, _floorStateToStr(state));
            m->create(a, mode);
        }
        break;
    case FloorStatePre:
        if (m->pre) {
            _dispModuleName(m, _floorStateToStr(state));
            m->pre(a, mode);
        }
        break;
    case FloorStateNormal:
        if (m->thread) {
            if (createThread) {
                _dispModuleName(m, "NoramlThread");
                void *t = floorCreateThread(1, 0x4000, 1, m->thread);
                GSthreadSetName(t, m->getName());
                return 1;
            }
            return 0;
        }
        if (m->normal) m->normal(a, mode);
        break;
    case FloorStatePost:
        if (m->post) {
            _dispModuleName(m, _floorStateToStr(state));
            m->post(a, mode);
        }
        break;
    case FloorStateFree:
        if (m->free) {
            _dispModuleName(m, _floorStateToStr(state));
            m->free(a, mode);
        }
        break;
    default:
        break;
    }
    return 0;
}
