#include "log.h"
#include "sfile.h"

#include <stdio.h>
#include <stdarg.h>

static const char* log_file_path = "log.txt";

void log_set_filepath(const char* filepath) {
  log_file_path = filepath;
}

void log_(u8 level, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  FILE* path = 0;

  // Output to file with debug options on
#if defined(SOL_DEBUG) || defined(SOL_DEBUG_OUTPUT)
  va_list file_args;
  va_copy(file_args, args);
  path = fopen(log_file_path, "a");
  vfprintf(path, fmt, file_args);
  fclose(path);
#endif

  vprintf(fmt, args);

  va_end(args);
}
