//*************************************************************************************
//  call time to get current calendar time.
//  call localtime to convert it to a broken down time
//  call strftime to format the result.
//*************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#ifdef __MACH__
#include <mach/mach_time.h>
#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 0
int clock_gettime(int clk_id, struct timespec *t){
    mach_timebase_info_data_t timebase;
    mach_timebase_info(&timebase);
    uint64_t time;
    time = mach_absolute_time();
    double nseconds = ((double)time * (double)timebase.numer)/((double)timebase.denom);
    double seconds = ((double)time * (double)timebase.numer)/((double)timebase.denom * 1e9);
    t->tv_sec = seconds;
    t->tv_nsec = nseconds;
    return 0;
}

int clock_getres(int clock_id, struct timespec *ts) {
    ts->tv_sec  = 0;
    ts->tv_nsec = 1;
    return 0;
}
#else
#include <time.h>
#endif

#ifndef clockid_t
typedef int clockid_t;
#endif  

int main(){
  printf("==================================================================\n");
  printf("usage of func time\n");
  printf("==================================================================\n");
  time_t t;
  time(&t);
  printf("return value of func time : %zu\n",time(&t));
  printf("fill time value in tmp    : %zu\n", t);
  printf("\n");

  printf("==================================================================\n");
  printf("usage of func clock_gettime\n");
  printf("==================================================================\n");
  int rtn_clock;
  struct timespec tsp1;
  rtn_clock = clock_gettime(CLOCK_REALTIME, &tsp1);
  printf("return value : %d\n", rtn_clock);
  
  printf("second value : %zu\n",tsp1.tv_sec);
  printf("nanosecond value : %zu\n",tsp1.tv_nsec);
  printf("\n");
  
  printf("==================================================================\n");
  printf("usage of func clock_getres\n");
  printf("==================================================================\n");
  clockid_t clocks[]= {  
    CLOCK_REALTIME,  
    CLOCK_MONOTONIC,  
    // CLOCK_PROCESS_CPUTIME_ID,  
    // CLOCK_THREAD_CPUTIME_ID,  
    (clockid_t) -1,  
  };  
  
  int i;  
  for(i = 0; clocks[i] != (clockid_t) -1; i++) {  
    struct timespec res;  
    int ret;  
    ret = clock_getres(clocks[i], &res);  
    if (ret)  
      perror("clock_getres");  
    else
      printf("clock = [%d],sec = [%ld],nsec = [%ld]\n",
             i, res.tv_sec, res.tv_nsec);  
  }  
  printf("\n");

  printf("==================================================================\n");
  printf("usage of func gettimeofday\n");
  printf("==================================================================\n");
  struct timeval tp;
  gettimeofday(&tp,NULL);

  printf("seconds part   : %zu\n",tp.tv_sec);
  printf("suseconds part : %d\n",tp.tv_usec);  
  printf("\n");
  
  printf("==================================================================\n");
  printf("usage of func strftime\n");
  printf("==================================================================\n");
  time_t t2;
  struct tm *tmp;
  char buf1[16];
  char buf2[64];

  tmp = localtime(&t2);
  if (strftime(buf1, 16, "time and date: %r, %a %b %d, %Y", tmp) == 0)
    printf("buffer length 16 is too small\n");
  else
    printf("%s\n", buf1);
  if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)
    printf("buffer length 64 is too small\n");
  else
    printf("%s\n", buf2);
  printf("\n");
  
  printf("==================================================================\n");
  printf("usage of func ctime\n");
  printf("==================================================================\n");
  struct timeval tv;
  static char str[30];
  char *ptr;

  if(gettimeofday(&tv,NULL) < 0)
      perror("gettimeofday error");
  ptr = ctime(&tv.tv_sec);
  strcpy(str,&ptr[11]);
  snprintf(str +8, sizeof(str) - 8, ".%06d", tv.tv_usec );

  printf("str is %s\n",str);

  return 0;
}
