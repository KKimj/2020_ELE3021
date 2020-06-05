#include "types.h"
#include "stat.h"
#include "user.h"

#define N 4096

int main(int argc, char *argv[])
{
  int pid, parent;
  char *shmem;
  parent = getpid();
  shmem = malloc(N);

  if ((pid = fork()) < 0)
  {
    printf(1, "fork failed!\n");
    exit();
  }
  if (pid == 0)
  {
    sleep(100);
    // shmem = getshmem(parent);
    printf(1, "A message from the parent  arddress : %p address cast to int %d char : %c\n", shmem, shmem, *shmem);
  }
  else
  {
    // shmem = getshmem(parent);
    
    // *shmem = 'H';
    printf(1, "parent adrress : %p address cast to int %d char : %c\n", shmem, shmem, *shmem);
    wait();
    
  }

  exit();
  return 0;
}

