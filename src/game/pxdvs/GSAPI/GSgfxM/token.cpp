#include "graphics_round1.h"

void GSgfxRenderWaitInit(GSgfxRenderWaitData* data);
void GSgfxRenderWaitTick(GSgfxRenderWaitData* data);
void GSgfxRenderWaitExit(GSgfxRenderWaitData* data);
void GSgfxGPUSetDrawSyncCallback(void (*callback)(unsigned short));

extern "C" {
u16 GXReadDrawSync(void);
void GXSetDrawSync(u16 token);
}

struct TokenRegister {
    u16 first;
    u16 last;
    void (*callback)(u16 token);
};
ABI_SIZE(TokenRegister, 8);
ABI_OFF(TokenRegister, callback, 4);

static TokenRegister _tokenRegisterList[4];
static u16 _tokenCurrent;
static u16 _tokenFrameStart;
static u16 _tokenFrameEnd;
static u16 _tokenLastGPU;
static u16 _tokenMaximum;
static u8 _tokenRegisterCount;

static void _tokenDrawSyncCallback(unsigned short token);

static inline bool _tokenPassed(u16 token, u16 gpu) {
    u16 end = _tokenFrameEnd;
    if (end > gpu) {
        if (token <= gpu || token > end) {
            return true;
        }
    } else if (token > end && token <= gpu) {
        return true;
    }
    return false;
}

static inline bool _tokenIsCleared(u16 token) {
    u16 sync;
    if (_tokenPassed(token, _tokenLastGPU)) {
        return true;
    }
    sync = GXReadDrawSync();
    if (sync >= _tokenMaximum) {
        return false;
    }
    if (_tokenPassed(token, sync)) {
        return true;
    }
    return false;
}

static inline bool _tokenIsValid(u16 token) {
    if (token == 0 || token >= _tokenMaximum) {
        return false;
    }
    return true;
}

static inline bool _tokenIsPending(u16 token) {
    u32 start;
    u16 end;
    if (token == 0 || token >= _tokenMaximum) {
        return false;
    }
    start = _tokenFrameStart;
    end = _tokenFrameEnd;
    if (start <= end) {
        if (token >= start && token <= end) {
            return false;
        }
    } else if (token >= start || token <= end) {
        return false;
    }
    return true;
}

static inline bool _tokenCleared(u16 token) {
    if (!_tokenIsValid(token)) {
        return true;
    }
    return _tokenIsCleared(token);
}

extern "C" {

void GSgfxTokenWaitForClearAndReset(u16* tokenPtr) {
    u16 token = *tokenPtr;
    if (token == 0) {
        return;
    }
    if (_tokenIsPending(*tokenPtr)) {
        GSgfxRenderWaitData wait;
        GSgfxRenderWaitInit(&wait);
        while (!_tokenIsCleared(token)) {
            GSgfxRenderWaitTick(&wait);
        }
        GSgfxRenderWaitExit(&wait);
    }
    *tokenPtr = 0;
}

void GSgfxTokenIfClearedReset(u16* tokenPtr) {
    s16 token = *tokenPtr;
    u16 timer = token;
    if (timer == 0) {
        return;
    }
    if (_tokenCleared(token) == true) {
        *tokenPtr = 0;
    }
}

void GSgfxTokenWaitForClear(u16 token) {
    if (_tokenIsPending(token)) {
        GSgfxRenderWaitData wait;
        GSgfxRenderWaitInit(&wait);
        while (!_tokenIsCleared(token)) {
            GSgfxRenderWaitTick(&wait);
        }
        GSgfxRenderWaitExit(&wait);
    }
}

bool GSgfxTokenCleared(u16 token) {
    return _tokenCleared(token);
}

}

u16 GSgfxTokenMark_Sub() {
    u32 token = _tokenCurrent;
    u16 end = _tokenFrameEnd;
    if (token == end) {
        return end;
    }
    GXSetDrawSync(token);
    if (++_tokenCurrent >= _tokenMaximum) {
        _tokenCurrent = 1;
    }
    return token;
}

void GSgfxTokenMarkFrame() {
    _tokenFrameStart = _tokenCurrent;
    _tokenFrameEnd = _tokenCurrent + 0x1000;
    if (_tokenFrameEnd >= _tokenMaximum) {
        _tokenFrameEnd -= _tokenMaximum;
    }
}

void GSgfxTokenSetDrawSyncCBFunc(void (*func)(void (*)(unsigned short))) {
    if (func != 0) {
        func(_tokenDrawSyncCallback);
    }
}

void GSgfxTokenAbortFrame() {
    _tokenLastGPU = _tokenFrameStart;
}

void GSgfxTokenInit() {
    _tokenLastGPU = 0;
    _tokenCurrent = 1;
    _tokenMaximum = 0xE000;
    _tokenFrameStart = 1;
    _tokenFrameEnd = 0x1001;
    _tokenRegisterList[0].callback = 0;
    _tokenRegisterList[1].callback = 0;
    _tokenRegisterList[2].callback = 0;
    _tokenRegisterList[3].callback = 0;
    _tokenRegisterCount = 0;
    GSgfxGPUSetDrawSyncCallback(_tokenDrawSyncCallback);
}

static void _tokenDrawSyncCallback(unsigned short token) {
    u8 i;
    for (i = 0; i < _tokenRegisterCount; i++) {
        TokenRegister* reg = &_tokenRegisterList[i];
        if (reg->first <= token && reg->last >= token) {
            reg->callback(token);
            return;
        }
    }
    _tokenLastGPU = token;
}
