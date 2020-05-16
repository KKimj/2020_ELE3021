#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[])
{
    printf(1, "start\n");
    yield();
    printf(1, "Call yield\n");
    printf(1, "Call getlev return value : %d\n", getlev());
    printf(1, "Call setpriority return value : %d\n", setpriority(1, 4));
    exit();
}
