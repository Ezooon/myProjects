
#include<sys/resource.h>
#include<unistd.h>
#include <stdio.h>

double getTime(int flag)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  struct timeval user_time, sys_time;
  user_time = usage.ru_utime;
  sys_time  = usage.ru_stime;
  if (flag==1)
    return user_time.tv_sec+user_time.tv_usec/1e6;
  if (flag==2)
    {
      return user_time.tv_sec+sys_time.tv_sec + (user_time.tv_usec+sys_time.tv_sec)/1e6;
    }
  return -1;
}
