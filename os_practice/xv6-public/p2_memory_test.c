#include "types.h"
#include "stat.h"
#include "user.h"

#define N 4096

int main(int argc, char *argv[])
{
  int total = 0;
  int pid = getpid();
  int i=0;
  char * pre_ptr;
  printf(1, "Memory test: pid is %d\n", pid);
  for (;;)
  {
    char * ptr = malloc(N);
    if (ptr == 0)
    {
      printf(1, "Memory allocation failed.\n");
      exit();
    }
    *ptr = i++;
    total += N;
    printf(1, "Memory allocated: %d bytes\n", total);
    sleep(300);
    if(pre_ptr)
    printf(1, "test : last memory in : %c\n", *pre_ptr);

    pre_ptr = ptr;
  }
  exit();
  return 0;
}

