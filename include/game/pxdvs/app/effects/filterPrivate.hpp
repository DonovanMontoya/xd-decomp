#ifndef FILTER_PRIVATE_HPP
#define FILTER_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
#include <game/pxdvs/GSAPI/GSgfxM/GSgfxColAu8.hpp>
struct GSmodel;struct GScamera;struct GSbound;struct GSgfxLayer;enum GSgfxLayerPass{BillboardPass};struct _GSparticleBank;struct _GSparticleGen;
struct GSeffectBase{u32 field0,field4;};
class GSeffect:public GSeffectBase{public:GSeffect();virtual bool _start();virtual void _stop();virtual bool _update(f32);virtual void _render(GSgfxLayer*,GSgfxLayerPass);virtual void _fastRender();virtual ~GSeffect();void Stop();};
typedef GSgfxColAu8 FilterColor;
class filterEffect:public GSeffect{public:void*target;FilterColor original;u8 pe,combine,saved,pad17,modulation;FilterColor color;virtual ~filterEffect();virtual bool _start();virtual void _stop();virtual bool _update(f32);void InitModulation();void UpdateModulation();};
#endif
