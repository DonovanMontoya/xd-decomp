#include <game/pxdvs/app/floor/floorFieldCameraEditorPrivate.hpp>

extern "C" {
static void GXParam1u8(u8 value);
static void GXParam1f32(f32 value);
inline void GSvecCopy(GSvec* to, const GSvec* from);
}

static FieldCameraEditor gFieldCameraEditorData;
extern "C" {void*memset(void*,int,unsigned long);void*memcpy(void*,const void*,unsigned long);void*GSmemAlloc(u32);void GSmemFree(void*);u32 GSgappCreate(s32,s32,s32,void(*)());void GSgappTerminate(u32);u32 GSfloorGetCurrent();u8 floorFieldCameraGetMode();u8 cameraGetType();void GScameraLoadActiveCameraMatrix(s32);ActiveCamera*GScameraGetActiveCamera();void cameraGetTargetOfs(GSvec*);u8 dbgMenuIsOpen();u8 menuIsCheck(s32);u32 GSinputButtonsChanged(s32);u32 GSinputButtonsPressed(s32);GSgfxLayer*GSgfxLayerFindByID(s32);GSgfxVF*GSgfxVFBuildTemp(s32,s32,u8,s32,u8,s32,u8,s32,s32);f32 cameraGetDistance();f32 cameraGetHeight();f32 cameraGetRotY();f32 cameraGetFov();void floorFieldCameraEditorStopTest();void floorUpdateFieldCameraEditor();}
void floorInitFieldCamera(GSfloor_dd_*);
extern "C" u8 floorFieldCameraEditorGetMode(){return gFieldCameraEditorData.mode;}
extern "C" void floorReleaseFieldCameraEditor(){floorFieldCameraEditorStopTest();if(gFieldCameraEditorData.application)GSgappTerminate(gFieldCameraEditorData.application);GSmemFree(gFieldCameraEditorData.cameraAllocation);GSmemFree(gFieldCameraEditorData.headerAllocation);memset(&gFieldCameraEditorData,0,sizeof(gFieldCameraEditorData));}
extern "C" void floorInitFieldCameraEditor(u32 floorID) {
    void* mem;
    FieldCameraList* cams;
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
                cams = floorDataBiosGetFieldCameraListPtr(floor);
                gFieldCameraEditorData.floor = floorID;
                gFieldCameraEditorData.originalList = floor->fieldCameras;
                gFieldCameraEditorData.mode = floorFieldCameraGetMode();
                gFieldCameraEditorData.list->count = &gFieldCameraEditorData.count;
                if (cams != 0) {
                    count = *cams->count;
                    if (count != 0) {
                        size = count * sizeof(FieldCameraEntry);
                        arr = GSmemAlloc(size);
                        if (arr == 0) {
                            goto fail;
                        }
                        gFieldCameraEditorData.count = count;
                        gFieldCameraEditorData.cameraAllocation = arr;
                        gFieldCameraEditorData.list->entries = (FieldCameraEntry*)arr;
                        memcpy(gFieldCameraEditorData.list->entries, cams->entries, size);
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
    FieldCameraEntry* st = gFieldCameraEditorData.selected;
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
                        st->isBox ^= 1;
                    }
                    if (st->isBox != 0) {
                        if (GSinputButtonsPressed(1) & 0x40) {
                            if (GSinputButtonsPressed(1) & 0x100) {
                                st->angle += 0.1f;
                            } else if (GSinputButtonsPressed(1) & 0x200) {
                                st->angle -= 0.1f;
                            }
                        } else if (GSinputButtonsPressed(1) & 0x20) {
                            if (GSinputButtonsPressed(1) & 0x100) {
                                st->ratio += 0.1f;
                                if (st->ratio > 20.0f) {
                                    st->ratio = 20.0f;
                                }
                            } else if (GSinputButtonsPressed(1) & 0x200) {
                                st->ratio -= 0.1f;
                                if (st->ratio < 1.0f) {
                                    st->ratio = 1.0f;
                                }
                            }
                        }
                    } else if (GSinputButtonsPressed(1) & 0x100) {
                        st->radius += 1.0f;
                        if (st->radius > 500.0f) {
                            st->radius = 500.0f;
                        }
                    } else if (GSinputButtonsPressed(1) & 0x200) {
                        st->radius -= 1.0f;
                        if (st->radius < 5.0f) {
                            st->radius = 5.0f;
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
                        if (st->isBox != 0) {
                            l->primitiveType((GSgfxPrimType)0x80);
                            f32 c = std::cosf(st->angle);
                            f32 s = std::sinf(st->angle);
                            f32 r = st->radius;
                            f32 w = st->ratio * r;
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
                                l->vertex3f(st->radius * std::cosf(a) + pos.x, 0.1f + (pos.y - ofs.y), st->radius * std::sinf(a) + pos.z);
                                l->color4u8(0x80, 0x80, 0x80, 0x80);
                            }
                            l->endSurface();
                        }
                    }
                }
                st->x = pos.x;
                st->y = pos.y - ofs.y;
                st->z = pos.z;
                st->distance = cameraGetDistance();
                st->height = cameraGetHeight();
                st->rotY = cameraGetRotY();
                st->fov = cameraGetFov();
            }
        }
    }
}
extern "C" void floorFieldCameraEditorStopTest(){gFieldCameraEditorData.testing=0;if(gFieldCameraEditorData.floor){GSfloor_dd_*data=floorDataBiosGetPtr(gFieldCameraEditorData.floor);if(data){data->fieldCameras=gFieldCameraEditorData.originalList;floorInitFieldCamera(data);}}}
extern "C" u32 floorFieldCameraEditorGetFloorID(){return gFieldCameraEditorData.floor;}

inline void GSgfxLayer::color4u8(u8 r,u8 g,u8 b,u8 a){GXParam1u8(r);GXParam1u8(g);GXParam1u8(b);GXParam1u8(a);}
inline void GSgfxLayer::vertex3f(f32 x,f32 y,f32 z){GXParam1f32(x);GXParam1f32(y);GXParam1f32(z);}
inline void GSgfxLayer::primitiveType(GSgfxPrimType type){unk1998=type;}
inline void GSgfxLayer::blendMode(GSgfxBlendType arg1,GSgfxBlendFactor arg2,GSgfxBlendFactor arg3,bool arg4){
    if (arg1 == 0) {
        if (arg4 == 1) {
            SetRenderPass((GSgfxLayerPass)0);
        }
        this->unk1644 = 0;
        this->unk1648 = 1;
        this->unk164C = 1;
        this->unk1650 = 5;
    } else {
        if (arg4 == 1) {
            SetRenderPass((GSgfxLayerPass)1);
        }
        this->unk1644 = arg1;
        this->unk1648 = arg2;
        this->unk164C = arg3;
        this->unk1650 = 5;
    }
    this->unk170C = (s32) (this->unk170C | 1);
    this->unk16A8 = (s32) (this->unk16A8 | 0x40);
    this->unk17C4 = (s32) (this->unk17C4 | 1);
    this->unk1760 = (s32) (this->unk1760 | 0x40);
}

inline void GSgfxLayer::SetRenderPass(GSgfxLayerPass arg1){
    if ((s32) this->unk1994 != arg1) {
        this->unk1994 = arg1;
        this->unk1990=&records[this->unk1994];
    }
}

inline void GSgfxLayer::cullMode(GSgfxCullType arg1){
    this->unkD8C = arg1;
    this->unk16B8 = (s32) (this->unk16B8 | 2);
    this->unk16A8 = (s32) (this->unk16A8 | 2);
    this->unk1770 = (s32) (this->unk1770 | 2);
    this->unk1760 = (s32) (this->unk1760 | 2);
}

inline void GSgfxLayer::alphaCompare(bool arg1,GSgfxACmpFunc arg2,u8 arg3,GSgfxAlphaOp arg4,GSgfxACmpFunc arg5,u8 arg6){
    if (arg1 == 1) {
        this->unk1664 = arg2;
        this->unk1670 = arg3;
        this->unk1668 = arg4;
        this->unk166C = arg5;
        this->unk1671 = arg6;
        this->unk1672 = 0;
    } else {
        this->unk1664 = 7;
        this->unk1670 = 0;
        this->unk1668 = 0;
        this->unk166C = 7;
        this->unk1671 = 0;
        this->unk1672 = 1;
    }
    this->unk170C = (s32) (this->unk170C | 0x10);
    this->unk16A8 = (s32) (this->unk16A8 | 0x40);
    this->unk17C4 = (s32) (this->unk17C4 | 0x10);
    this->unk1760 = (s32) (this->unk1760 | 0x40);
}

inline void GSgfxLayer::zCompare(bool arg1,GSgfxZCmpFunc arg2){
    if (arg1 == 1) {
        this->unk165C = 1;
    } else {
        this->unk165C = 0;
    }
    this->unk1660 = arg2;
    this->unk170C = (s32) (this->unk170C | 8);
    this->unk16A8 = (s32) (this->unk16A8 | 0x40);
    this->unk17C4 = (s32) (this->unk17C4 | 8);
    this->unk1760 = (s32) (this->unk1760 | 0x40);
}

inline void GSgfxLayer::pixelMode(bool arg1,bool arg2,bool arg3){
    if (arg1 == 1) {
        this->unk1656 = 1;
    } else {
        this->unk1656 = 0;
    }
    if (arg2 == 1) {
        this->unk1657 = 1;
    } else {
        this->unk1657 = 0;
    }
    if (arg3 == 1) {
        this->unk1658 = 1;
    } else {
        this->unk1658 = 0;
    }
    this->unk170C = (s32) (this->unk170C | 4);
    this->unk16A8 = (s32) (this->unk16A8 | 0x40);
    this->unk17C4 = (s32) (this->unk17C4 | 4);
    this->unk1760 = (s32) (this->unk1760 | 0x40);
}

extern "C" {
static void GXParam1u8(u8 value) {
    *(u8*)0xCC008000 = value;
}

static void GXParam1f32(f32 value) {
    *(volatile f32*)0xCC008000 = value;
}
}

extern "C" inline void GSvecCopy(GSvec*to,const GSvec*from){to->x=from->x;to->y=from->y;to->z=from->z;}
