#include <game/pxdvs/GSAPI/GSthread/GSthreadPrivate.hpp>
#include <libc/stdarg.h>

extern "C" {

void threadSaveGPRRegisters();
void threadSaveFPRRegisters();
void threadExecute();
void fn_80103420();
void threadRemoveFromList(GSthread*);
void threadInsertIntoList(GSthread*);
void threadExecutePass(u32, u8);
void threadExitFunc(s32);
void threadRun(GSthread*, u8*, s32);
void threadInitialize(GSthread*);
void* threadDMAStackToScratch(void*, s32, u8);
GSthread* threadFindNext(GSthread*, u32, u8);
GSthread* threadFindUnused();
void GSthreadTerminate(GSthread*);
void GSthreadSwitch();

static GSthreadRegState _GSthreadRegisterState;
static GSthread* _activeThread;
static GSthread* _nextThread;
static GSthread* _threadListTop;
static u8 _rescan;
static s32 _saveLRReg;
static u32 _usesFPURegisters;
static s32 _tempGPR2;
static s32 _tempGPR1;
static u8* _destRegStatePtr;
static u8* _threadRegStatePtr;
static GSthreadRegState* _localRegStatePtr;
static GSthread* _threadList;
static u32 _maxThreads;

asm void threadLoadGPRRegisters() {
    nofralloc
    stwu r1, -0x8(r1)
    stw r3, 0x8(r1)
    lwz r3, _destRegStatePtr(r13)
    lwz r0, 0x0(r3)
    lwz r2, 0x8(r3)
    lwz r4, 0x10(r3)
    lwz r5, 0x14(r3)
    lwz r6, 0x18(r3)
    lwz r7, 0x1c(r3)
    lwz r8, 0x20(r3)
    lwz r9, 0x24(r3)
    lwz r10, 0x28(r3)
    lwz r11, 0x2c(r3)
    lwz r12, 0x30(r3)
    lwz r13, 0x34(r3)
    lwz r14, 0x38(r3)
    lwz r15, 0x3c(r3)
    lwz r16, 0x40(r3)
    lwz r17, 0x44(r3)
    lwz r18, 0x48(r3)
    lwz r19, 0x4c(r3)
    lwz r20, 0x50(r3)
    lwz r21, 0x54(r3)
    lwz r22, 0x58(r3)
    lwz r23, 0x5c(r3)
    lwz r24, 0x60(r3)
    lwz r25, 0x64(r3)
    lwz r26, 0x68(r3)
    lwz r27, 0x6c(r3)
    lwz r28, 0x70(r3)
    lwz r29, 0x74(r3)
    lwz r30, 0x78(r3)
    lwz r31, 0x7c(r3)
    lwz r3, 0x8(r1)
    addi r1, r1, 0x8
    blr
}

asm void threadLoadFPRRegisters() {
    nofralloc
    stwu r1, -0x8(r1)
    stw r3, 0x8(r1)
    lwz r3, _destRegStatePtr(r13)
    addi r3, r3, 0x88
    lfd f0, 0x0(r3)
    lfd f1, 0x8(r3)
    lfd f2, 0x10(r3)
    lfd f3, 0x18(r3)
    lfd f4, 0x20(r3)
    lfd f5, 0x28(r3)
    lfd f6, 0x30(r3)
    lfd f7, 0x38(r3)
    lfd f8, 0x40(r3)
    lfd f9, 0x48(r3)
    lfd f10, 0x50(r3)
    lfd f11, 0x58(r3)
    lfd f12, 0x60(r3)
    lfd f13, 0x68(r3)
    lfd f14, 0x70(r3)
    lfd f15, 0x78(r3)
    lfd f16, 0x80(r3)
    lfd f17, 0x88(r3)
    lfd f18, 0x90(r3)
    lfd f19, 0x98(r3)
    lfd f20, 0xa0(r3)
    lfd f21, 0xa8(r3)
    lfd f22, 0xb0(r3)
    lfd f23, 0xb8(r3)
    lfd f24, 0xc0(r3)
    lfd f25, 0xc8(r3)
    lfd f26, 0xd0(r3)
    lfd f27, 0xd8(r3)
    lfd f28, 0xe0(r3)
    lfd f29, 0xe8(r3)
    lfd f30, 0xf0(r3)
    lfd f31, 0xf8(r3)
    lwz r3, 0x8(r1)
    addi r1, r1, 0x8
    blr
}

asm void threadSaveGPRRegisters() {
    nofralloc
    stwu r1, -0x8(r1)
    stw r3, 0x8(r1)
    lwz r3, _destRegStatePtr(r13)
    stw r0, 0x0(r3)
    stw r2, 0x8(r3)
    stw r3, 0xc(r3)
    stw r4, 0x10(r3)
    stw r5, 0x14(r3)
    stw r6, 0x18(r3)
    stw r7, 0x1c(r3)
    stw r8, 0x20(r3)
    stw r9, 0x24(r3)
    stw r10, 0x28(r3)
    stw r11, 0x2c(r3)
    stw r12, 0x30(r3)
    stw r13, 0x34(r3)
    stw r14, 0x38(r3)
    stw r15, 0x3c(r3)
    stw r16, 0x40(r3)
    stw r17, 0x44(r3)
    stw r18, 0x48(r3)
    stw r19, 0x4c(r3)
    stw r20, 0x50(r3)
    stw r21, 0x54(r3)
    stw r22, 0x58(r3)
    stw r23, 0x5c(r3)
    stw r24, 0x60(r3)
    stw r25, 0x64(r3)
    stw r26, 0x68(r3)
    stw r27, 0x6c(r3)
    stw r28, 0x70(r3)
    stw r29, 0x74(r3)
    stw r30, 0x78(r3)
    stw r31, 0x7c(r3)
    lwz r3, 0x8(r1)
    addi r1, r1, 0x8
    blr
}

asm void threadSaveFPRRegisters() {
    nofralloc
    stwu r1, -0x8(r1)
    stw r3, 0x8(r1)
    lwz r3, _destRegStatePtr(r13)
    addi r3, r3, 0x88
    stfd f0, 0x0(r3)
    stfd f1, 0x8(r3)
    stfd f2, 0x10(r3)
    stfd f3, 0x18(r3)
    stfd f4, 0x20(r3)
    stfd f5, 0x28(r3)
    stfd f6, 0x30(r3)
    stfd f7, 0x38(r3)
    stfd f8, 0x40(r3)
    stfd f9, 0x48(r3)
    stfd f10, 0x50(r3)
    stfd f11, 0x58(r3)
    stfd f12, 0x60(r3)
    stfd f13, 0x68(r3)
    stfd f14, 0x70(r3)
    stfd f15, 0x78(r3)
    stfd f16, 0x80(r3)
    stfd f17, 0x88(r3)
    stfd f18, 0x90(r3)
    stfd f19, 0x98(r3)
    stfd f20, 0xa0(r3)
    stfd f21, 0xa8(r3)
    stfd f22, 0xb0(r3)
    stfd f23, 0xb8(r3)
    stfd f24, 0xc0(r3)
    stfd f25, 0xc8(r3)
    stfd f26, 0xd0(r3)
    stfd f27, 0xd8(r3)
    stfd f28, 0xe0(r3)
    stfd f29, 0xe8(r3)
    stfd f30, 0xf0(r3)
    stfd f31, 0xf8(r3)
    lwz r3, 0x8(r1)
    addi r1, r1, 0x8
    blr
}

asm void threadExecute() {
    nofralloc
    stwu r1, -0xc(r1)
    stw r3, 0xc(r1)
    mflr r3
    stw r3, 0x8(r1)
    lwz r3, _localRegStatePtr(r13)
    stw r3, _destRegStatePtr(r13)
    bl threadSaveGPRRegisters
    stw r1, 0x4(r3)
    lwz r3, _threadRegStatePtr(r13)
    stw r3, _destRegStatePtr(r13)
    bl threadLoadGPRRegisters
    lwz r5, _usesFPURegisters(r13)
    cmplwi r5, 0x0
    beq lbl_801033F4
    bl threadLoadFPRRegisters
lbl_801033F4:
    lwz r5, 0x84(r3)
    mtlr r5
    lwz r1, 0x4(r3)
    li r5, 0x0
    subi r5, r5, 0x1
    stw r5, 0x0(r1)
    lwz r5, 0x80(r3)
    mtctr r5
    lwz r5, 0x14(r3)
    lwz r3, 0xc(r3)
    bctr
}

asm void fn_80103420() {
    nofralloc
    lwz r3, 0x8(r1)
    mtlr r3
    lwz r3, 0xc(r1)
    addi r1, r1, 0xc
    blr
}

static asm void _threadSwitch() {
    nofralloc
    stw r3, _tempGPR1(r13)
    stw r5, _tempGPR2(r13)
    mflr r5
    lwz r3, _threadRegStatePtr(r13)
    stw r3, _destRegStatePtr(r13)
    bl threadSaveGPRRegisters
    stw r5, 0x80(r3)
    lwz r5, _tempGPR1(r13)
    stw r5, 0xc(r3)
    lwz r5, _tempGPR2(r13)
    stw r5, 0x14(r3)
    stw r1, 0x4(r3)
    lwz r5, _usesFPURegisters(r13)
    cmplwi r5, 0x0
    beq lbl_80103474
    bl threadSaveFPRRegisters
lbl_80103474:
    lwz r3, _localRegStatePtr(r13)
    stw r3, _destRegStatePtr(r13)
    bl threadLoadGPRRegisters
    lwz r5, 0x84(r3)
    mtlr r5
    lwz r1, 0x4(r3)
    lwz r5, 0x14(r3)
    lwz r3, 0xc(r3)
    blr
}

void GSthreadSetName(GSthread* thread, const char* name) {
    if (thread != 0) {
        memcpy(thread->name, name, 0x1F);
        thread->name[0x1F] = 0;
    }
}

void GSthreadSetGroupID(GSthread* thread, u32 groupId) {
    if (thread != 0) {
        thread->groupId = groupId;
    }
}

asm void GSthreadSwitch() {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r3, _activeThread(r13)
    cmplwi r3, 0x0
    beq lbl_80103510
    mflr r5
    stw r5, _saveLRReg(r13)
    stw r5, 0x2c(r3)
    bl _threadSwitch
lbl_80103510:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

GSthread* GSthreadGetCurrentThread() {
    return _activeThread;
}

void GSthreadUnblockGroup(u32 groupId) {
    u32 i;
    if (groupId != 0) {
        for (i = 0; i < _maxThreads; i++) {
            GSthread* t = &_threadList[i];
            if (t->groupId == groupId) {
                t->groupBlocked = 0;
            }
        }
        _rescan = 1;
    }
}

void GSthreadBlockGroup(u32 groupId) {
    u32 i;
    if (groupId != 0) {
        for (i = 0; i < _maxThreads; i++) {
            GSthread* t = &_threadList[i];
            if (t->groupId == groupId) {
                t->groupBlocked = 1;
            }
        }
        _rescan = 1;
    }
}

void GSthreadUnblock(GSthread* thread) {
    if (thread != 0) {
        thread->blocked = 0;
        _rescan = 1;
    }
}

void GSthreadBlock(GSthread* thread) {
    if (thread != 0) {
        thread->blocked = 1;
        _rescan = 1;
    }
}

void GSthreadExecuteAll() {
    threadExecutePass(0, 0);
}

void GSthreadExecuteGroup(u32 groupId) {
    threadExecutePass(groupId, 1);
}

s32 GSthreadClose(GSthread* thread) {
    if (thread == 0) {
        return 0;
    }
    if (thread->autoTerminate == 1) {
        return 0;
    }
    s32 result = thread->result;
    thread->used = 0;
    return result;
}

u8 GSthreadIsRunning(GSthread* thread) {
    if (thread == 0) {
        return 0;
    }
    return thread->running;
}

void GSthreadTerminateGroup(u32 groupId) {
    GSthread* t;
    for (t = _threadListTop; t != 0; t = t->next) {
        if (t->groupId == groupId) {
            GSthreadTerminate(t);
        }
    }
}

void GSthreadTerminate(GSthread* thread) {
    if (thread != 0) {
        if (thread == _activeThread || thread == _nextThread) {
            thread->terminate = 1;
            if (thread == _nextThread) {
                _rescan = 1;
            }
        } else {
            thread->running = 0;
            thread->used = 0;
            threadRemoveFromList(thread);
            if (thread->stack != 0) {
                GSmemFreeHeap(thread->heap, thread->stack);
                thread->stack = 0;
            }
            if (thread->regState != 0) {
                GSmemFreeHeap(thread->heap, thread->regState);
                thread->regState = 0;
            }
        }
    }
}

void GSthreadSetArgs(GSthread* thread, s32 count, ...) {
    va_list ap;
    s32* stack;
    s32 i;
    s32 n;
    s32 off;
    if (thread != 0 && thread->running != 1) {
        stack = thread->stack;
        s32* regs = (s32*)thread->regState;
        va_start(ap, count);
        off = 3;
        n = 8;
        if (count < 8) {
            n = count;
        }
        for (i = 0; i < n; i++) {
            regs[off++] = va_arg(ap, s32);
        }
        if (count > 8) {
            regs[1] -= (count - i) * 4;
            off = (((u32)regs[1] >> 2) + 2);
            for (i = 8; i < count; i++) {
                stack[(u32)off] = va_arg(ap, s32);
                off++;
            }
        }
    }
}



GSthread* GSthreadCreate(u8 priority, u32 groupId, s32 stackSize, u8 usesFPU, u8 autoTerminate, s32 entry) {
    int heap;
    GSthread* thread;
    if (usesFPU == 0) {
        GSlogWrite("GSthreadCreate. Warning: 'usesFPU==FALE' OK?\n");
    }
    thread = threadFindUnused();
    if (thread == 0) {
        return 0;
    }
    heap = GSmemGetCurrentHeap();
    thread->stack = (s32*)GSmemAllocAlignHeap(heap, stackSize, 0x20);
    if (thread->stack == 0) {
        return 0;
    }
    u32 regSize = 0x88;
    if (usesFPU != 0) {
        regSize = 0x188;
    }
    thread->regState = (u8*)GSmemAllocHeap(heap, regSize);
    if (thread->regState == 0) {
        return 0;
    }
    thread->used = 1;
    thread->groupId = groupId;
    thread->stackSize = stackSize;
    thread->running = 0;
    thread->terminate = 0;
    thread->usesFPU = usesFPU;
    thread->entry = entry;
    thread->blocked = 0;
    thread->groupBlocked = 0;
    thread->priority = priority;
    thread->prev = 0;
    thread->next = 0;
    thread->autoTerminate = autoTerminate;
    thread->heap = heap;
    thread->lr = 0;
    thread->name[0] = 0;
    threadInitialize(thread);
    threadInsertIntoList(thread);
    _rescan = 1;
    return thread;
}

s32 GSthreadInit(u32 maxThreads) {
    u32 i;
    _maxThreads = maxThreads;
    _threadList = (GSthread*)GSmemAlloc(maxThreads * sizeof(GSthread));
    if (_threadList == 0) {
        return 0;
    }
    for (i = 0; i < _maxThreads; i++) {
        _threadList[i].used = 0;
    }
    _activeThread = 0;
    _threadListTop = 0;
    GSlogWrite("GSthread: Init OK, maximum of %d threads\n", _maxThreads);
    return 1;
}

void threadRemoveFromList(GSthread* thread) {
    if (thread != 0) {
        if (thread->prev != 0) {
            thread->prev->next = thread->next;
        }
        if (thread->next != 0) {
            thread->next->prev = thread->prev;
        }
        if (_threadListTop == thread) {
            _threadListTop = thread->next;
        }
    }
}

void threadInsertIntoList(GSthread* thread) {
    GSthread* cur;
    if (thread != 0) {
        if (_threadListTop == 0) {
            _threadListTop = thread;
            return;
        }
        cur = _threadListTop;
        while (cur->next != 0 && cur->priority < thread->priority) {
            cur = cur->next;
        }
        if (cur->next == 0 && cur->priority < thread->priority) {
            thread->prev = cur;
            thread->next = 0;
            cur->next = thread;
            return;
        }
        if (cur->prev != 0) {
            cur->prev->next = thread;
        }
        thread->prev = cur->prev;
        thread->next = cur;
        cur->prev = thread;
        if (_threadListTop == cur) {
            _threadListTop = thread;
        }
    }
}

void threadExecutePass(u32 groupId, u8 groupOnly) {
    GSthread* next;
    u8* regState;
    s32* stack;
    void* scratch;
    s32* nextStack;
    void* nextScratch;
    GSthread* cur;

    cur = threadFindNext(0, groupId, groupOnly);
    if (cur != 0) {
        stack = cur->stack;
        regState = cur->regState;
        scratch = threadDMAStackToScratch(stack, cur->stackSize, 1);
        while (cur != 0) {
            next = threadFindNext(cur, groupId, groupOnly);
            _nextThread = next;
            if (next != 0) {
                nextStack = next->stack;
                nextScratch = threadDMAStackToScratch(nextStack, next->stackSize, 0);
            }
            threadRun(cur, regState, (s32)scratch);
            if (cur->terminate != 0) {
                if (GSscratchIsPtr(scratch) != 0) {
                    GSscratchFree(scratch);
                }
                GSthreadTerminate(cur);
            } else if (GSscratchIsPtr(scratch) != 0) {
                DCFlushRange(stack, cur->stackSize);
                GSscratchStore(stack, scratch, cur->stackSize);
                GSscratchWaitForCompletion();
                GSscratchFree(scratch);
            }
            if (_rescan == 0 || _nextThread == threadFindNext(cur, groupId, groupOnly)) {
                cur = _nextThread;
                if (_nextThread != 0) {
                    regState = _nextThread->regState;
                    scratch = nextScratch;
                    stack = nextStack;
                }
            } else {
                if (GSscratchIsPtr(nextScratch) != 0) {
                    GSscratchWaitForCompletion();
                    GSscratchFree(nextScratch);
                }
                if (_nextThread != 0 && _nextThread->terminate != 0) {
                    GSthread* dead = _nextThread;
                    _nextThread = 0;
                    GSthreadTerminate(dead);
                }
                _nextThread = threadFindNext(cur, groupId, groupOnly);
                cur = _nextThread;
                if (cur != 0) {
                    stack = cur->stack;
                    regState = cur->regState;
                    scratch = threadDMAStackToScratch(stack, cur->stackSize, 1);
                }
            }
            _rescan = 0;
        }
    }
}

void threadExitFunc(s32 result) {
    GSthread* thread = _activeThread;
    thread->result = result;
    if (thread->autoTerminate == 1) {
        GSthreadTerminate(thread);
    } else {
        thread->terminate = 1;
        thread->running = 0;
        threadRemoveFromList(thread);
        _rescan = 1;
    }
    GSthreadSwitch();
}

void threadRun(GSthread* thread, u8* regState, s32 stackAdjust) {
    s32 sp;
    _activeThread = thread;
    thread->running = 1;
    sp = *(s32*)(regState + 4);
    sp = stackAdjust + sp;
    *(s32*)(regState + 4) = sp;
    _GSthreadRegisterState.entry = fn_80103420;
    _localRegStatePtr = &_GSthreadRegisterState;
    _threadRegStatePtr = regState;
    _usesFPURegisters = thread->usesFPU;
    threadExecute();
    *(s32*)(regState + 4) = *(s32*)(regState + 4) - stackAdjust;
    _activeThread = 0;
}

void threadInitialize(GSthread* thread) {
    u8* regState;
    s32* stack;
    if (thread != 0) {
        regState = thread->regState;
        stack = thread->stack;
        _destRegStatePtr = regState;
        threadSaveGPRRegisters();
        if (thread->usesFPU != 0) {
            threadSaveFPRRegisters();
        }
        *(s32*)(regState + 4) = thread->stackSize - 8;
        *(s32*)(regState + 0x80) = thread->entry;
        *(void (**)(s32))(regState + 0x84) = threadExitFunc;
        *stack = -1;
    }
}

void* threadDMAStackToScratch(void* stack, s32, u8) {
    return stack;
}

GSthread* threadFindNext(GSthread* thread, u32 groupId, u8 groupOnly) {
    GSthread* cur;
    if (thread == 0) {
        cur = _threadListTop;
    } else {
        cur = thread->next;
    }
    while (cur != 0) {
        if (cur->used != 0 && cur->blocked == 0 && cur->groupBlocked == 0 && cur->terminate == 0) {
            if (groupOnly == 0 || cur->groupId == groupId) {
                return cur;
            }
        }
        cur = cur->next;
    }
    return 0;
}

GSthread* threadFindUnused() {
    GSthread* t = _threadList;
    u32 i;
    for (i = 0; i != _maxThreads; i++) {
        if (t->used == 0) {
            return t;
        }
        t++;
    }
    return 0;
}

}
