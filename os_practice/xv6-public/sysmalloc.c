#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#define VERBOSE

int sys_smalloc(void)
{
  #ifdef VERBOSE
  printf(2, "@sys_smalloc start!\n");
  #endif

  return 1;
}


int sys_shmemfree(void)
{
  int pid = getpid();
  char * address = getshmem(pid);

  #ifdef VERBOSE
  printf(2, "@sys_shmemfree start! pid : %d address : %p\n", pid, address);
  #endif
//   free(address);
  return 1;
}