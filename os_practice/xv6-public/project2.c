#include "types.h"
#include "defs.h"
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
    getshmem(pid);
    return 0;
}


int getadmin(char *password)
{
    #ifdef VERBOS
    cprintf("%s\n", "getadmin Start!");
    #endif

    if(1)  // login fail
    {
        return -1;
    }

    #ifdef VERBOS
    cprintf("%s\n", "getadmin exit!");
    #endif
    return 0; // login success
}


int exec2(char *path, char **argv, int stacksize)
{
    #ifdef VERBOS
    cprintf("%s\n", "exec two Start!");
    #endif


    if(1) // exec2 fail
    {
        return -1;
    }

    #ifdef VERBOS
    cprintf("%s\n", "exec two exit!");
    #endif
    return 0; // exec2 success
}


int setmemorylimit(int pid, int limit)
{
    #ifdef VERBOS
    cprintf("%s\n", "setmemorylimit Start!");
    #endif


#undef VERBOS
    if(1) // setmemory limit fail
    {
        return -1;
    }

    #ifdef VERBOS
    cprintf("%s\n", "setmemorylimit exit!");
    #endif
    return 0; // setmemory limit success
}
char * getshmem(int pid)
{
    char * ret_val = (char *) 0xFFFFFFFF;

    #ifdef VERBOS
    cprintf("%s\n", "getshmem Start!");
    #endif


    #ifdef VERBOS
    cprintf("%s\n", "getshmem exit!");
    #endif
    return ret_val;
}

