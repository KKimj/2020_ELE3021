#include "types.h"
#include "stat.h"
#include "user.h"


// int getadmin(char *password);
// int exec2(char *path, char **argv, int stacksize);
// int setmemorylimit(int pid, int limit);
// char * getshmem(int pid); 

#define VERBOSE
#define DEV

int
main(int argc, char *argv[])
{
    #ifdef VERBOSE
    printf(1, "Pmanager Start!\n");
    #endif

    #ifdef DEV
    char * passwd = "2018008159";
    getadmin(passwd);

    char * path = "./cat";
    char * argv_[] = {"Hello", "World!"};
    int stacksize = 0;
    exec2(path, argv_, stacksize);

    int pid = 0;
    int limit = 0;
    setmemorylimit(pid, limit);

    getshmem(pid);
    #endif

    #ifdef VERBOSE
    printf(1, "Pmanager exit!\n");
    #endif
    exit();
}

