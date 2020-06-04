#include "types.h"
#include "defs.h"
#define VERBOSE
#define MAXARG       32  // max exec arguments

int getadmin(char *password);
int exec2(char *path, char **argv, int stacksize);
int setmemorylimit(int pid, int limit);
char * getshmem(int pid); 


int
sys_getadmin(void)
{
    char * passwd;
    if( argstr(0, &passwd) <0 )
        return -1;
    #ifdef VERBOSE
    cprintf("%s\n", passwd);
    #endif

    int ret = getadmin(passwd);
    #ifdef VERBOSE
    if(!ret)
        cprintf("ok\n");
    else
        cprintf("no\n"); 
    #endif

    return ret;
}

int
sys_exec2(void)
{
    int stacksize = 0;

    char *path, *argv[MAXARG];
    int i;
    uint uargv, uarg;

    if(argstr(0, &path) < 0 || argint(1, (int*)&uargv) < 0){
        return -1;
    }
    memset(argv, 0, sizeof(argv));
    for(i=0;; i++){
        if(i >= NELEM(argv))
            return -1;
        if(fetchint(uargv+4*i, (int*)&uarg) < 0)
            return -1;
        if(uarg == 0){
            argv[i] = 0;
            break;
        }
        if(fetchstr(uarg, &argv[i]) < 0)
            return -1;
    }

    if(argint(2,&stacksize) < 0)
        return -1;

    #ifdef VERBOSE
    cprintf("%s\n", argv[0]);
    cprintf("%d\n", stacksize);
    #endif

    return exec2(path, argv, stacksize);
}

int
sys_setmemorylimit(void)
{
    int pid = 0, limit=0;
    if(argint(0,&pid) < 0)
        return -1;

    if(argint(1,&limit) < 0)
        return -1;

    #ifdef VERBOSE
    cprintf("%d ", pid);
    cprintf("%d\n", limit);
    #endif
    return setmemorylimit(pid, limit);
}

int
sys_getshmem(void)
{
    int pid = 0;
    if(argint(0,&pid) < 0)
        return -1;
    getshmem(pid);
    return 0;
}

#ifdef VERBOSE
#undef VERBOSE
#endif

#ifdef VERBOSE
// char * msg_start = "Start";
// char * msg_exit = "Exit";
// char * msg_getadmin = "GetAd";
// char * msg_exec2 = "ExeTw";
// char * msg_setmemorylimit = "SetML";
// char * msg_getshmem = "GetShM";

char * msg_start = "Start!";
char * msg_exit = "Exit!";
char * msg_getadmin = "Getadmin ";
char * msg_exec2 = "extwo ";
char * msg_setmemorylimit = "SetmemLmit";
char * msg_getshmem = "Getshmem";
#endif

char key[] = "2018008159";
int getadmin(char *password)
{
    #ifdef VERBOSE
    cprintf("%s%s\n", msg_getadmin, msg_start);
    #endif

    char *_key = key;
    int cnt = 0;
    while(*password == *_key)
    {
        cnt++;
        password++, _key++;
    }
    if(cnt<10)  // login fail
    {
        cprintf("%s\n", _key);
        return -1;
    }
    #ifdef VERBOSE
    cprintf("%s%s\n", msg_getadmin, msg_exit);
    #endif
    return 0; // login success
}


int exec2(char *path, char **argv, int stacksize)
{
    #ifdef VERBOSE
    cprintf("%s%s\n", msg_exec2, msg_start);
    #endif


    if(1) // exec2 fail
    {
        return -1;
    }

    #ifdef VERBOSE
    cprintf("%s%s\n", msg_exec2, msg_exit);
    #endif
    return 0; // exec2 success
}


int setmemorylimit(int pid, int limit)
{
    #ifdef VERBOSE
    // cprintf("%s%s\n", msg_setmemorylimit, msg_start);
    #endif

    if(1) // setmemory limit fail
    {
        return -1;
    }

    #ifdef VERBOSE
    cprintf("%s%s\n", msg_setmemorylimit, msg_exit);
    #endif
    return 0; // setmemory limit success
}
char * getshmem(int pid)
{
    char * ret_val = (char *) 0xFFFFFFFF;

    #ifdef VERBOSE
    cprintf("%s%s\n", msg_getshmem, msg_start);
    #endif


    #ifdef VERBOSE
    cprintf("%s%s\n", msg_getshmem, msg_exit);
    #endif
    return ret_val;
}

