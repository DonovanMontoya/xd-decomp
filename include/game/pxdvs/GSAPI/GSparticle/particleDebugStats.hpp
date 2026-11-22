#ifndef PARTICLE_DEBUG_STATS_HPP
#define PARTICLE_DEBUG_STATS_HPP

#include <global.h>

struct ParticleDebugStats {
    u32 bank, node, displayList, renderData, primitiveMemory, total;
    u32 reserved18[3];
};

extern "C" ParticleDebugStats g_particle_debug_stats;

#endif
