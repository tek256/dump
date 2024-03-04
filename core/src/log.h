#ifndef SOL_LOG_H
#define SOL_LOG_H

#include "arch.h"

// Forward declare allocators
struct allocator_t;

#if !defined(SOL_LOG_FILE_PATH)
#define SOL_LOG_FILE_PATH "sol_log.txt"
#define SOL_LOG_FILE_NAME "sol_log"
#endif

#define SOL_MAX_LOG_FILES 4

#define LOG_STATUS   0
#define LOG_WARNING  1
#define LOG_ERROR    2
#define _l(fmt, ...) log_(LOG_STATUS, fmt, ##__VA_ARGS__)
#define _w(fmt, ...) log_(LOG_WARNING, fmt, ##__VA_ARGS__)
#define _e(fmt, ...) log_(LOG_ERROR, fmt, ##__VA_ARGS__)
#define _l_func(fmt, ...)            \
  log_(LOG_STATUS, "%s:", __func__); \
  log_(LOG_STATUS, fmt, ##__VA_ARGS__)
#define _w_func(fmt, ...)             \
  log_(LOG_WARNING, "%s:", __func__); \
  log_(LOG_WARNING, fmt, ##__VA_ARGS__)
#define _e_func(fmt, ...)           \
  log_(LOG_ERROR, "%s:", __func__); \
  log_(LOG_ERROR, fmt, ##__VA_ARGS__)

u8   log_turn_filepath(struct allocator_t* alloc);
void log_set_filepath(const char* filepath);
void log_(u8 level, const char* fmt, ...);

#endif
