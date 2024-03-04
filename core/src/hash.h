#ifndef CORE_HASH_H_INCLUDED
#define CORE_HASH_H_INCLUDED

#include "arch.h"

#define FNV1A_HASH_SEED 2166136261

u32 hash_fnv1a(const void* data, u32 size);
u32 hash_fnv1a_chunk(u32 seed, const void* data, u32 size);

#endif
