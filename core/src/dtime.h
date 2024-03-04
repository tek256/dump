#ifndef CORE_TIME_H
#define CORE_TIME_H

#ifndef SOL_TIME_H
#define SOL_TIME_H

#include "arch.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SEC_TO_NS   1e-9
#define SEC_TO_MCS  1e-6
#define SEC_TO_MS   1e-6
#define SEC_TO_MIN  60
#define SEC_TO_HOUR 3600

#define MS_TO_NS   1e-6
#define MS_TO_MCS  1e-3
#define MS_TO_SEC  1e3
#define MS_TO_MIN  (MS_TO_SEC * 60)
#define MS_TO_HOUR (MS_TO_MIN * 60)

#define MCS_TO_NS   1e-3
#define MCS_TO_MS   1e3
#define MCS_TO_SEC  1e6
#define MCS_TO_MIN  (MCS_TO_SEC * 60)
#define MCS_TO_HOUR (MCS_TO_MIN * 60)

#define NS_TO_MCS  1e3
#define NS_TO_MS   1e6
#define NS_TO_SEC  1e9
#define NS_TO_MIN  (NS_TO_SEC * 60)
#define NS_TO_HOUR (NS_TO_MIN * 60)

typedef struct {
  /* last - the last time this struct was updated
     delta - the time between the last update and the update before that */
  time_s last;
  time_s delta;
} t_timer;

/* Get the current time in milliseconds */
time_s t_get_time(void);

/* Update the mark & delta for timer
   t - the timer to update
   returns: the delta from last update of the time */
time_s t_timer_update(t_timer* t);

/* Create a timer that is up to date
   returns: a formatted t_timer marked with current time */
t_timer t_timer_create(void);

/* Sleep for time in Milliseconds
   duration - the time in milliseconds to sleep
   returns: time actually slept */
time_s t_sleep(time_s duration);

#ifdef __cplusplus
}
#endif
#endif

#endif
