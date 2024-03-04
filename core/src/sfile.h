#ifndef CORE_FILE_H
#define CORE_FILE_H

#include "arch.h"
#include "hash.h"

typedef enum {
  FS_EMPTY = 0,
  FS_OK,
  FS_UNABLE_TO_OPEN,
  FS_NOT_ENOUGH_SPACE,
  FS_NON_EQUAL_READ,
  FS_NON_EQUAL_WRITE,
  FS_INVALID_ARGS,
} FS_STATUS;

typedef struct {
  void*       data;
  u32         data_len, capacity;
  const char* path;
  u8          status,
      allocated; // allocated = if we allocated for the file indepedently
} file_t;

file_t file_load_verify(const char* path, void* buffer, u32 buffer_capacity,
                        u32 hash_expected);
file_t file_load(const char* path, void* buffer, u32 buffer_capacity);
u32    file_size(const char* path);
u8     file_exists(const char* path);
file_t file_write(const char* path, u8* data, u32 length);
file_t file_append(const char* path, u8* data, u32 length);
u8     file_delete_fp(const char* path);
void   file_free(file_t* file);

#endif
