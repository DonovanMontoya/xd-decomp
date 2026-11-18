#ifndef FLOOR_FIELD_CAMERA_EDITOR_PRIVATE_HPP
#define FLOOR_FIELD_CAMERA_EDITOR_PRIVATE_HPP
#include <dolphin/types.h>
struct GSvec {f32 x,y,z;GSvec();void clear();};
enum GSgfxPrimType{PrimDummy};enum GSgfxBlendType{BlendDummy};enum GSgfxBlendFactor{FactorDummy};enum GSgfxLayerPass{PassDummy};enum GSgfxCullType{CullDummy};enum GSgfxACmpFunc{ACmpDummy};enum GSgfxAlphaOp{AlphaDummy};enum GSgfxZCmpFunc{ZCmpDummy};
struct GSgfxVF;struct EditorBlendRecord {u8 bytes[0xBC];};
class GSgfxLayer {public:u8 pad0[3468];s32 unkD8C;u8 padD90[2228];s32 unk1644;s32 unk1648;s32 unk164C;s32 unk1650;u8 pad1654[2];u8 unk1656;u8 unk1657;u8 unk1658;u8 pad1659[3];u8 unk165C;u8 pad165D[3];s32 unk1660;s32 unk1664;s32 unk1668;s32 unk166C;u8 unk1670;u8 unk1671;u8 unk1672;u8 pad1673[53];s32 unk16A8;u8 pad16AC[12];s32 unk16B8;u8 pad16BC[80];s32 unk170C;u8 pad1710[80];s32 unk1760;u8 pad1764[12];s32 unk1770;u8 pad1774[80];s32 unk17C4;u8 pad17C8[80];EditorBlendRecord records[2];void* unk1990;s32 unk1994;s32 unk1998;void SetRenderPass(GSgfxLayerPass);void pixelMode(bool,bool,bool);void zCompare(bool,GSgfxZCmpFunc);void alphaCompare(bool,GSgfxACmpFunc,u8,GSgfxAlphaOp,GSgfxACmpFunc,u8);void cullMode(GSgfxCullType);void blendMode(GSgfxBlendType,GSgfxBlendFactor,GSgfxBlendFactor,bool);void setRenderStateAndSelect(GSgfxVF*);void primitiveType(GSgfxPrimType);void beginSurface(u16);void vertex3f(f32,f32,f32);void color4u8(u8,u8,u8,u8);void endSurface();};
struct FieldCamera {u8 rectangular,pad1[3];GSvec position;f32 distance,height,rotation,extent,aspect,angle;u8 pad28[8];f32 fov;};
struct FieldCameraList {u32*count;FieldCamera*cameras;};
struct GSfloor_dd_ {u8 pad[0x14];FieldCameraList*cameras;};
struct FieldCameraEditor {FieldCamera*selected;FieldCameraList*list;u32 count;void*headerAllocation;void*cameraAllocation;u32 floor;FieldCameraList*originalList;u32 application;u8 testing,mode,pad22[2];};
struct ActiveCamera {u8 pad[0xFC];GSvec position;};
namespace std{f32 sinf(f32);f32 cosf(f32);}

#endif
