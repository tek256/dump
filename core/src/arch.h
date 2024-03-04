#ifndef DUMP_ARCH_H
#define DUMP_ARCH_H

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#if defined(DUMP_LOWP_TIME)
typedef float time_s;
#else
typedef double time_s;
#endif

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float  f32;
typedef double f64;

typedef ptrdiff_t sz;
typedef size_t    usz;

typedef struct {
  u32 a, b;
} u32_pair;

// === macros ===

#define alignof(x)  ((size) _Alignof(x))
#define countof(a)  (sizeof(a) / sizeof(*(a)))
#define lengthof(s) (countof(s) - 1)

// note: this definition of checkbit returns pos if the value is set
// #define check_bit(x, pos)  ((x) & (1 << (pos)))
// this one doesn't
#define check_bit(x, pos) (((x) >> (pos)) & 1)

#ifdef __GNUC__
#define unreachable() (__builtin_unreachable())
#elif defined(_MSC_VER)
#define unreachable() (__assume(false))
#endif

#if !defined(SASSERT)
#define SASSERT(x) assert((x))
#endif

#if !defined(sassert)
#define sassert(x) assert((x))
#endif

#endif
