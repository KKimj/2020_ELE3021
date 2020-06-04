#include "types.h"
#include "stat.h"
#include "user.h"

void f(int depth)
{
  volatile char arr[1000] = {0};
  sleep(100);
  printf(1, "Recursion depth: %d arr address : %p\n", depth + arr[0], arr);
  f(depth + 1);
}

int main(int argc, char *argv[])
{
  f(1);
  exit();
  return 0;
}

