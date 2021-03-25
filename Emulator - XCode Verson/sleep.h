//
//  sleep.h
//  Emulator - XCode Verson
//
//  Created by Eric Diskin on 3/20/21.
//

#ifndef sleep_h
#define sleep_h

//https://stackoverflow.com/questions/26063754/nanosleep-does-not-work-for-values-less-than-a-second?answertab=votes#tab-top

#define _POSIX_C_SOURCE 199309L /* shall be >= 199309L */

#include <time.h>
void msleep(int *milliseconds)
{
  int ms_remaining = (*milliseconds) % 1000;
  long usec = ms_remaining * 1000;
  struct timespec ts_sleep;

  ts_sleep.tv_sec = (*milliseconds) / 1000;
  ts_sleep.tv_nsec = 1000*usec;
  nanosleep(&ts_sleep, NULL);
}

#endif /* sleep_h */
