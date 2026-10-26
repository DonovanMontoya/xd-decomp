#include <global.h>

extern "C" {
void* HSD_ArchiveGetPublicAddress(void*, const char*);
void* GScameraLoad(void*);
void GScameraFree();
void* GSmodelLoad(void*, void*);
void GSmodelFree();
void GSresRegisterResource(void*, s32, u32, s32 (*)(void*, u32, u32));
}

static s32 _unloadCamera(void*, u32, u32);
static s32 _unloadModel(void*, u32, u32);

extern "C" void loadCamera(void* archive, s32 resourceId, u32 flags) {
    if (archive == 0) return;
    void* sceneData = HSD_ArchiveGetPublicAddress(archive, "scene_data");
    if (sceneData == 0) return;
    void* cameraData = *(void**)((u8*)sceneData + 4);
    void* camera = GScameraLoad(cameraData);
    GSresRegisterResource(camera, resourceId, flags, _unloadCamera);
}

struct HSD_Archive;

extern "C" void loadModel(void* data, s32 resourceId, u32 modelIndex, u32 flags) {
    HSD_Archive* archive = (HSD_Archive*)data;
    if (archive == 0) return;
    void* sceneData = HSD_ArchiveGetPublicAddress(archive, "scene_data");
    if (sceneData == 0) return;
    void* bounds;
    if (modelIndex == 0) bounds = HSD_ArchiveGetPublicAddress(archive, "bound_box");
    else bounds = 0;
    u32* modelList = *(u32**)sceneData;
    u32 index = 0;
    while (modelList[index] != 0) {
        if (index == modelIndex) {
            void* model = GSmodelLoad((void*)modelList[index], bounds);
            GSresRegisterResource(model, resourceId, flags, _unloadModel);
            return;
        }
        ++index;
    }
}

static s32 _unloadCamera(void*, u32, u32) {
    GScameraFree();
    return 1;
}

static s32 _unloadModel(void*, u32, u32) {
    GSmodelFree();
    return 1;
}
