#include <game/pxdvs/GSAPI/GSgfxM/renderModule.hpp>
extern "C" {
void* memcpy(void*, const void*, unsigned long);
void* memset(void*, int, unsigned long);
}
extern f32 __float_epsilon[];
struct ModuleEntry {
    ModuleEntry* next;
    u8 used, priority;
    u8 padding[2];
    GSgfxRenderModule module;
};
typedef char ModuleEntrySize[sizeof(ModuleEntry) == 0x24 ? 1 : -1];
static ModuleEntry _renderModuleList[9];
static ModuleEntry* _renderModuleBottom;
static bool _renderModuleIsRendering;

void GSgfxRenderModuleInit();
void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* context);
void GSgfxRenderModuleDoPreUpdate(f32 delta);
void GSgfxRenderModuleDoRenderFast();
void GSgfxRenderModuleDoRender(GSgfxLayer* layer, GSgfxLayerPass pass);
void GSgfxRenderModuleDoPostUpdate(f32 delta);
bool GSgfxRenderModuleIsRendering();

bool GSgfxRenderModuleIsRendering() {
    return _renderModuleIsRendering;
}

static inline void _renderModuleUnlink(ModuleEntry* entry) {
    ModuleEntry* previous = _renderModuleBottom;
    if (previous == entry) {
        _renderModuleBottom = entry->next;
    } else {
        while (previous != 0) {
            if (previous->next == entry) break;
            previous = previous->next;
        }
        previous->next = entry->next;
    }
}

static inline void _renderModuleInsert(ModuleEntry* entry, u8 priority) {
    ModuleEntry* previous = _renderModuleBottom;
    entry->next = 0;
    entry->priority = priority;
    if (previous == 0 || previous->priority > priority) {
        entry->next = previous;
        _renderModuleBottom = entry;
    } else {
        ModuleEntry* next = previous->next;
        while (next != 0) {
            if (next->priority > priority) break;
            previous = next;
            next = next->next;
        }
        entry->next = next;
        previous->next = entry;
    }
}

void GSgfxRenderModuleDoPostUpdate(f32 delta) {
    ModuleEntry* entry;
    u32 i;
    u32 ticks = (u32)(delta + __float_epsilon[0]);
    for (i = 0; i < ticks; ++i) {
        for (entry = _renderModuleBottom; entry; entry = entry->next) {
            if (entry->module.tick) entry->module.tick();
        }
    }
    for (entry = _renderModuleBottom; entry; entry = entry->next) {
        if (entry->module.postUpdate) entry->module.postUpdate(delta);
    }
}

void GSgfxRenderModuleDoRender(GSgfxLayer* layer, GSgfxLayerPass pass) {
    ModuleEntry* entry = _renderModuleBottom;
    _renderModuleIsRendering = true;
    for (; entry; entry = entry->next) {
        if (entry->module.render) entry->module.render(layer, pass);
    }
    _renderModuleIsRendering = false;
}

void GSgfxRenderModuleDoRenderFast() {
    ModuleEntry* entry = _renderModuleBottom;
    _renderModuleIsRendering = true;
    for (; entry; entry = entry->next) {
        if (entry->module.renderFast) entry->module.renderFast();
    }
    _renderModuleIsRendering = false;
}

void GSgfxRenderModuleDoPreUpdate(f32 delta) {
    for (ModuleEntry* entry = _renderModuleBottom; entry; entry = entry->next) {
        if (entry->module.preUpdate) entry->module.preUpdate(delta);
    }
}

void GSgfxRenderModuleRegister(u8 priority, GSgfxRenderModule* module, void* context) {
    for (int i = 0; i < 9; i++) {
        ModuleEntry* entry = &_renderModuleList[i];
        if (entry->used) continue;
        entry->used = 1;
        entry->priority = 0;
        entry->next = _renderModuleBottom;
        _renderModuleBottom = entry;
        memcpy(&entry->module, module, sizeof(GSgfxRenderModule));
        if (entry->priority != priority) {
            _renderModuleUnlink(entry);
            _renderModuleInsert(entry, priority);
        }
        if (module->init) module->init(context);
        return;
    }
}

void GSgfxRenderModuleInit() {
    memset(_renderModuleList, 0, sizeof(_renderModuleList));
    _renderModuleBottom = 0;
    _renderModuleIsRendering = false;
}
