#include "sfile.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32)
#include <io.h>
#define F_OK   0
#define access _access
#else
#include <unistd.h>
#endif

file_t file_load_verify(const char* path, void* buffer, u32 buffer_capacity,
                        u32 hash_expected) {
  file_t file = (file_t){0};

  if (!buffer || !buffer_capacity) {
    file.status = FS_NOT_ENOUGH_SPACE;
    return file;
  }

  FILE* f = fopen(path, "rb");
  if (!f) {
    file.status = FS_UNABLE_TO_OPEN;
    return file;
  }

  fseek(f, 0, SEEK_END);
  file.data_len = ftell(f);
  rewind(f);

  if (file.data_len > buffer_capacity) {
    file.status = FS_NOT_ENOUGH_SPACE;
    fclose(f);
    return file;
  }

  const usz chunk_size   = 4096;
  usz       data_read    = 0;
  u32       running_hash = FNV1A_HASH_SEED; // TODO abstract this out?

  // u32 hash_fnv1a_chunk(u32 seed, const void* data, u32 size);
  // TODO add parameter for read chunk size?
  while (data_read < file.data_len) {
    usz chunk_read = fread(buffer, sizeof(unsigned char), chunk_size, f);
    running_hash =
        hash_fnv1a_chunk(running_hash, &buffer[data_read], chunk_read);
    data_read += chunk_read;
  }

  _l("running_hash: %i\n", running_hash);

  if (data_read != file.data_len) {
    file.status = FS_NON_EQUAL_READ;
  }

  ((unsigned char*)buffer)[data_read] = 0;
  fclose(f);

  file.data      = buffer;
  file.capacity  = buffer_capacity;
  file.path      = path;
  file.status    = FS_OK;
  file.allocated = 0;

  return file;
}

file_t file_load(const char* path, void* buffer, u32 buffer_capacity) {
  file_t file = (file_t){0};

  if (!buffer || !buffer_capacity) {
    file.status = FS_NOT_ENOUGH_SPACE;
    return file;
  }

  FILE* f = fopen(path, "rb");
  if (!f) {
    file.status = FS_UNABLE_TO_OPEN;
    return file;
  }

  fseek(f, 0, SEEK_END);
  file.data_len = ftell(f);
  rewind(f);

  if (file.data_len > buffer_capacity) {
    file.status = FS_NOT_ENOUGH_SPACE;
    fclose(f);
    return file;
  }

  u32 data_read = (u32)fread(buffer, sizeof(unsigned char), file.data_len, f);
  if (data_read != file.data_len) {
    file.status = FS_NON_EQUAL_READ;
  }

  ((unsigned char*)buffer)[data_read] = 0;
  fclose(f);

  file.data      = buffer;
  file.capacity  = buffer_capacity;
  file.path      = path;
  file.status    = FS_OK;
  file.allocated = 0;

  return file;
}

u32 file_size(const char* path) {
  FILE* f = fopen(path, "r");
  if (!f) {
    return 0;
  }
  fseek(f, 0, SEEK_END);
  u32 s = (u32)ftell(f);
  fclose(f);
  return s;
}

u8 file_exists(const char* path) {
  return access(path, F_OK) == 0;
}

file_t file_write(const char* path, u8* data, u32 length) {
  file_t file = (file_t){
      .path      = path,
      .data      = data,
      .data_len  = length,
      .capacity  = length,
      .status    = FS_EMPTY,
      .allocated = 0,
  };
  FILE* f = fopen(path, "wb");
  if (!f) {
    file.status = FS_EMPTY;
    return file;
  }

  u32 write_length = (u32)fwrite(data, length, 1, f);
  file.data_len    = write_length;
  fclose(f);
  if (write_length != length) {
    file.status = FS_NON_EQUAL_WRITE;
    return file;
  }

  file.status = FS_OK;
  return file;
}

file_t file_append(const char* path, u8* data, u32 length) {
  file_t file = (file_t){
      .path      = path,
      .data      = data,
      .data_len  = length,
      .capacity  = length,
      .status    = FS_EMPTY,
      .allocated = 0,
  };

  FILE* f = fopen(path, "ab");
  if (!f) {
    file.status = FS_EMPTY;
    return file;
  }

  u32 write_length = (u32)fwrite(data, length, 1, f);
  file.data_len    = write_length;
  fclose(f);
  if (write_length != length) {
    file.status = FS_NON_EQUAL_WRITE;
    return file;
  }

  file.status = FS_OK;
  return file;
}

void file_free(file_t* file) {
  //
}

u8 file_delete_fp(const char* filepath) {
  sassert(filepath);
  return remove(filepath) == 0;
}
