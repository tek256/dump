#include "dtime.h"
#include "log.h"

#include <math.h>
#if defined(__linux__) || defined(__unix__) || defined(__FreeBSD__) || \
    defined(__APPLE__)
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <time.h>
#endif

#if defined(__linux)
#define HAVE_POSIX_TIMER
#include <time.h>
#ifdef CLOCK_MONOTONIC
#define CLOCKID CLOCK_MONOTONIC
#else
#define CLOCKID CLOCK_REALTIME
#endif
#elif defined(__APPLE__)
#define HAVE_MACH_TIMER
#include <mach/mach_time.h>
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

/* Get time in nanoseconds from the Operating System's High performance timer */
static u64 s_get_ns() {
  static u64 is_init = 0;
#if defined(__APPLE__)
  static mach_timebase_info_data_t info;
  if (0 == is_init) {
    mach_timebase_info(&info);
    is_init = 1;
  }
  u64 now;
  now = mach_absolute_time();
  now *= info.numer;
  now /= info.denom;
  return now;
#elif defined(__linux)
  static struct timespec linux_rate;
  if (0 == is_init) {
    clock_getres(CLOCKID, &linux_rate);
    is_init = 1;
  }
  u64             now;
  struct timespec spec;
  clock_gettime(CLOCKID, &spec);
  now = spec.tv_sec * 1.0e9 + spec.tv_nsec;
  return now;
#elif defined(_WIN32)
  static LARGE_INTEGER win_frequency;
  if (0 == is_init) {
    QueryPerformanceFrequency(&win_frequency);
    is_init = 1;
  }
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (u64)((1e9 * now.QuadPart) / win_frequency.QuadPart);
#endif
}

/* Call the OS's sleep function for given milliseconds */
time_s s_sleep(time_s duration) {
#if defined(_WIN32) || defined(_WIN64)
  Sleep(duration * MS_TO_MCS);
#elif _POSIX_C_SOURCE >= 199309L
  struct timespec ts;
  ts.tv_sec  = duration / MS_TO_SEC;
  ts.tv_nsec = fmod(duration, MS_TO_NS);
  nanosleep(&ts, NULL);
#else
  u32 sleep_conv = duration / MS_TO_MCS;
  usleep(sleep_conv);
#endif
  return duration;
}

/* Returns time in milliseconds */
time_s t_get_time() {
  return s_get_ns() / NS_TO_MS;
}

/* Update a timer with current time & calculate delta from last update */
time_s t_timer_update(t_timer* t) {
  time_s current = t_get_time();
  t->delta       = current - t->last;
  t->last        = current;
  return t->delta;
}

/* Create the timer structure with current time */
t_timer t_timer_create() {
  return (t_timer){t_get_time(), 0};
}
