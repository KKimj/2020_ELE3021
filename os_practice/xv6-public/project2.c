#include "types.h"
#include "stat.h"
#include "user.h"

#define VERBOS

int getadmin(char *password);
int exec2(char *path, char **argv, int stacksize);
int setmemorylimit(int pid, int limit);
char * getshmem(int pid); 


int
sys_getadmin(void)
{
    char * passwd = "2018008159";
    return getadmin(passwd);
}

int
sys_exec2(void)
{
    char * path = "pmanager";
    char * argv[] = {"argv0", "argv1"};
    int stacksize = 0;
    return exec2(path, argv, stacksize);
}

int
sys_setmemorylimit(void)
{
    int pid = 0, limit=0;
    return setmemorylimit(pid, limit);
}

int
sys_getshmem(void)
{
    int pid = 0;
    return getshmem(pid);
}


int getadmin(char *password)
{
    #ifdef VERBOS
    printf(1, "getadmin Start!\n");
    #endif

    if(1)  // login fail
    {
        return -1;
    }

    #ifdef VERBOS
    printf(1, "getadmin exit!\n");
    #endif
    return 0; // login success
}

int exec2(char *path, char **argv, int stacksize)
{
    #ifdef VERBOS
    printf(1, "exec2 Start!\n");
    #endif

    if(1) // exec2 fail
    {
        return -1;
    }

    #ifdef VERBOS
    printf(1, "exec2 exit!\n");
    #endif
    return 0; // exec2 success
}
int setmemorylimit(int pid, int limit)
{
    #ifdef VERBOS
    printf(1, "setmemorylimit Start!\n");
    #endif

    if(1) // setmemory limit fail
    {
        return -1;
    }

    #ifdef VERBOS
    printf(1, "setmemorylimit exit!\n");
    #endif
    return 0; // setmemory limit success
}
char * getshmem(int pid)
{
    char * ret_val = 0xFFFFFFFF;

    #ifdef VERBOS
    printf(1, "getshmem Start!\n");
    #endif


    #ifdef VERBOS
    printf(1, "getshmem exit!\n");
    #endif
    return ret_val;
}

