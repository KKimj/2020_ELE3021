#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[])
{
    printf(1, "start\n");
    printf(1, "Call yield\n", yield());
    printf(1, "Call getlev return value : %d\n", getlev());
    printf(1, "Call setpriority return value : \n", setpriority(1, 1));
    exit();
}