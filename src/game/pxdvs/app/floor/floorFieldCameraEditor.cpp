#include <game/pxdvs/app/floor/floorFieldCameraEditorPrivate.hpp>
static FieldCameraEditor gFieldCameraEditorData;
extern "C" {void*memset(void*,int,unsigned long);void*memcpy(void*,const void*,unsigned long);void*GSmemAlloc(u32);void GSmemFree(void*);u32 GSgappCreate(s32,s32,s32,void(*)());void GSgappTerminate(u32);u32 GSfloorGetCurrent();GSfloor_dd_*floorDataBiosGetPtr(u32);FieldCameraList*floorDataBiosGetFieldCameraListPtr(GSfloor_dd_*);u8 floorFieldCameraGetMode();u8 cameraGetType();void GScameraLoadActiveCameraMatrix(s32);ActiveCamera*GScameraGetActiveCamera();void cameraGetTargetOfs(GSvec*);u8 dbgMenuIsOpen();u8 menuIsCheck(s32);u32 GSinputButtonsChanged(s32);u32 GSinputButtonsPressed(s32);GSgfxLayer*GSgfxLayerFindByID(s32);GSgfxVF*GSgfxVFBuildTemp(s32,s32,u8,s32,u8,s32,u8,s32,s32);f32 cameraGetDistance();f32 cameraGetHeight();f32 cameraGetRotY();f32 cameraGetFov();void floorFieldCameraEditorStopTest();void floorUpdateFieldCameraEditor();}
void floorInitFieldCamera(GSfloor_dd_*);
extern "C" u8 floorFieldCameraEditorGetMode(){return gFieldCameraEditorData.mode;}
extern "C" void floorReleaseFieldCameraEditor(){floorFieldCameraEditorStopTest();if(gFieldCameraEditorData.application)GSgappTerminate(gFieldCameraEditorData.application);GSmemFree(gFieldCameraEditorData.cameraAllocation);GSmemFree(gFieldCameraEditorData.headerAllocation);memset(&gFieldCameraEditorData,0,sizeof(gFieldCameraEditorData));}
extern "C" void floorInitFieldCameraEditor(u32 floorID) {
    void* mem;
    u32* cams;
    u32 size;
    GSfloor_dd_* floor = floorDataBiosGetPtr(floorID);
    u32 count;
    void* arr;
    floorReleaseFieldCameraEditor();
    if (floor != 0) {
        gFieldCameraEditorData.application = GSgappCreate(1, 0x7f, 0, floorUpdateFieldCameraEditor);
        if (gFieldCameraEditorData.application != 0) {
            mem = GSmemAlloc(8);
            if (mem != 0) {
                gFieldCameraEditorData.list = (FieldCameraList*)mem;
                gFieldCameraEditorData.headerAllocation = mem;
                cams = (u32*)floorDataBiosGetFieldCameraListPtr(floor);
                gFieldCameraEditorData.floor = floorID;
                gFieldCameraEditorData.originalList = floor->cameras;
                gFieldCameraEditorData.mode = floorFieldCameraGetMode();
                gFieldCameraEditorData.list->count = &gFieldCameraEditorData.count;
                if (cams != 0) {
                    count = *(u32*)cams[0];
                    if (count != 0) {
                        size = count * 0x34;
                        arr = GSmemAlloc(size);
                        if (arr == 0) {
                            goto fail;
                        }
                        gFieldCameraEditorData.count = count;
                        gFieldCameraEditorData.cameraAllocation = arr;
                        gFieldCameraEditorData.list->cameras = (FieldCamera*)arr;
                        memcpy(gFieldCameraEditorData.list->cameras, (void*)cams[1], size);
                    }
                }
                return;
            }
        }
    }
fail:
    floorReleaseFieldCameraEditor();
}
extern "C" void floorUpdateFieldCameraEditor() {
    FieldCamera* st = gFieldCameraEditorData.selected;
    int i;
    GSfloor_dd_* a = floorDataBiosGetPtr(GSfloorGetCurrent());
    GSfloor_dd_* b = floorDataBiosGetPtr(gFieldCameraEditorData.floor);
    if (a == 0 || a != b) {
        floorReleaseFieldCameraEditor();
        return;
    }
    if (gFieldCameraEditorData.testing == 0 && st != 0) {
        GSvec pos;
        GSvec ofs;
        pos.clear();
        if (cameraGetType() == 5) {
            GScameraLoadActiveCameraMatrix(-1);
            ActiveCamera* cam = GScameraGetActiveCamera();
            if (cam != 0) {
                GSvecCopy(&pos, &cam->position);
                cameraGetTargetOfs(&ofs);
                if (floorFieldCameraEditorGetMode() == 1 && dbgMenuIsOpen() == 0 && menuIsCheck(0x23) == 0) {
                    if (GSinputButtonsPressed(1) & GSinputButtonsChanged(1) & 0x10) {
                        st->rectangular ^= 1;
                    }
                    if (st->rectangular != 0) {
                        if (GSinputButtonsPressed(1) & 0x40) {
                            if (GSinputButtonsPressed(1) & 0x100) {
                                st->angle += 0.1f;
                            } else if (GSinputButtonsPressed(1) & 0x200) {
                                st->angle -= 0.1f;
                            }
                        } else if (GSinputButtonsPressed(1) & 0x20) {
                            if (GSinputButtonsPressed(1) & 0x100) {
                                st->aspect += 0.1f;
                                if (st->aspect > 20.0f) {
                                    st->aspect = 20.0f;
                                }
                            } else if (GSinputButtonsPressed(1) & 0x200) {
                                st->aspect -= 0.1f;
                                if (st->aspect < 1.0f) {
                                    st->aspect = 1.0f;
                                }
                            }
                        }
                    } else if (GSinputButtonsPressed(1) & 0x100) {
                        st->extent += 1.0f;
                        if (st->extent > 500.0f) {
                            st->extent = 500.0f;
                        }
                    } else if (GSinputButtonsPressed(1) & 0x200) {
                        st->extent -= 1.0f;
                        if (st->extent < 5.0f) {
                            st->extent = 5.0f;
                        }
                    }
                    GSgfxLayer* l = GSgfxLayerFindByID(2);
                    if (l != 0) {
                        GScameraLoadActiveCameraMatrix(2);
                        l->pixelMode(1, 1, 0);
                        l->zCompare(0, (GSgfxZCmpFunc)7);
                        l->alphaCompare(0, (GSgfxACmpFunc)7, 0, (GSgfxAlphaOp)0, (GSgfxACmpFunc)7, 0);
                        l->cullMode((GSgfxCullType)0);
                        l->blendMode((GSgfxBlendType)1, (GSgfxBlendFactor)4, (GSgfxBlendFactor)1, 1);
                        l->setRenderStateAndSelect(GSgfxVFBuildTemp(1, 4, 0, 0, 1, 5, 0, 0, 0));
                        if (st->rectangular != 0) {
                            l->primitiveType((GSgfxPrimType)0x80);
                            f32 c = std::cosf(st->angle);
                            f32 s = std::sinf(st->angle);
                            f32 r = st->extent;
                            f32 w = st->aspect * r;
                            l->beginSurface(4);
                            l->vertex3f(pos.x + r * c + w * s, 0.1f + (pos.y - ofs.y), (pos.z - r * s) + w * c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x - r * c) + w * s, 0.1f + (pos.y - ofs.y), pos.z + r * s + w * c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x - r * c) - w * s, 0.1f + (pos.y - ofs.y), (pos.z + r * s) - w * c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->vertex3f((pos.x + r * c) - w * s, 0.1f + (pos.y - ofs.y), (pos.z - r * s) - w * c);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            l->endSurface();
                        } else {
                            l->primitiveType((GSgfxPrimType)0xA0);
                            l->beginSurface(0x12);
                            l->vertex3f(pos.x, 0.1f + (pos.y - ofs.y), pos.z);
                            l->color4u8(0x80, 0x80, 0x80, 0x80);
                            for (i = 0; i < 0x11; i++) {
                                f32 a = 0.3926991f * (f32)i;
                                l->vertex3f(st->extent * std::cosf(a) + pos.x, 0.1f + (pos.y - ofs.y), st->extent * std::sinf(a) + pos.z);
                                l->color4u8(0x80, 0x80, 0x80, 0x80);
                            }
                            l->endSurface();
                        }
                    }
                }
                st->position.x = pos.x;
                st->position.y = pos.y - ofs.y;
                st->position.z = pos.z;
                st->distance = cameraGetDistance();
                st->height = cameraGetHeight();
                st->rotation = cameraGetRotY();
                st->fov = cameraGetFov();
            }
        }
    }
}
extern "C" void floorFieldCameraEditorStopTest(){gFieldCameraEditorData.testing=0;if(gFieldCameraEditorData.floor){GSfloor_dd_*data=floorDataBiosGetPtr(gFieldCameraEditorData.floor);if(data){data->cameras=gFieldCameraEditorData.originalList;floorInitFieldCamera(data);}}}
extern "C" u32 floorFieldCameraEditorGetFloorID(){return gFieldCameraEditorData.floor;}
