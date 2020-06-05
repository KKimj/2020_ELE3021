#include "types.h"
#include "defs.h"
#include "stat.h"
#include "user.h"

int sys_smalloc(void)
{
  #ifdef VERBOSE
  printf(2, "@sys_smalloc start!\n");
  #endif

  char * address = malloc(4096);
  int ret = (int) address;
  return ret;
}
int sys_shmemfree(void)
{
  int pid = getpid();
  char * address = getshmem(pid);

  #ifdef VERBOSE
  printf(2, "@sys_shmemfree start! pid : %d address : %p\n", pid, address);
  #endif
  free(address);
  return 1;
}