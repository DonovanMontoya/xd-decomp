#ifndef PE_NODE_PRIVATE_HPP
#define PE_NODE_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peEmitterData.hpp>
#include <libc/stddef.h>
#include <game/pxdvs/GSAPI/GSparticle/peNode.hpp>
typedef char NodeTransformSize[sizeof(NodeTransform)==0x28?1:-1];
typedef char NodeBaseSize[sizeof(peNode)==0x30?1:-1];
typedef char NodeForceOffset[offsetof(peEmitterNode,force)==0x9c?1:-1];
typedef char NodeEmitterOffset[offsetof(peEmitterNode,emitter)==0xfc?1:-1];
typedef char NodeParamsSize[sizeof(_EmitParams)==0x48?1:-1];
typedef char NodeEmitterAttraction[offsetof(_peEmitter,attraction)==0xa8?1:-1];
extern "C" { Mtx *GSgfxMatrixGetPtr(s32); }
#endif
