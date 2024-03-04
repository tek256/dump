#include "hash.h"

u32 hash_fnv1a(const void* data, u32 size) {
  u32 hash = FNV1A_HASH_SEED;

  const unsigned char* d = data;
  while (size--) {
    hash = (hash ^ *d++) * 16777619;
  }

  return hash;
}

u32 hash_fnv1a_chunk(u32 seed, const void* data, u32 size) {
  u32 hash = seed;

  const unsigned char* d = data;
  while (size--) {
    hash = (hash ^ *d++) * 16777619;
  }

  return hash;
}
