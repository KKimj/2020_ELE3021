#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#define PROJECT2

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

#ifdef PROJECT2
// #include "proc.h"
#define VERBOSE
#define MAXARG       32  // max exec arguments

int getadmin(char *password);
int exec2(char *path, char **argv, int stacksize);
//int setmemorylimit(int pid, int limit);
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
    {
        cprintf("ok\n");
    }
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

// #ifdef VERBOSE
// #undef VERBOSE
// #endif

#ifdef VERBOSE
// char * msg_start = "Start";
// char * msg_exit = "Exit";
// char * msg_getadmin = "GetAd";
// char * msg_exec2 = "ExeTw";
// char * msg_setmemorylimit = "SetML";
// char * msg_getshmem = "GetShM";

char  msg_start[] = "Start!";
char  msg_exit[] = "Exit!";
char  msg_getadmin[] = "Getadmin ";
char  msg_exec2[] = "extwo ";
char  msg_setmemorylimit[] = "SetmemLmit";
char  msg_getshmem[] = "Getshmem";
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
        myproc()->mode = USER;
        return -1;
    }
    #ifdef VERBOSE
    cprintf("%s%s\n", msg_getadmin, msg_exit);
    #endif
    myproc()->mode = ADMIN;
    return 0; // login success
}


int exec2(char *path, char **argv, int stacksize)
{
    if(myproc()->mode == USER) return -1;
    if(stacksize < 1 || stacksize > 100) return -1;
    myproc()->stacksize = stacksize;

    #ifdef VERBOSE
    cprintf("@sysproc.c -> myproc stacksize : %d\n", myproc()->stacksize);
    #endif

    return exec(path, argv); // exec2 success
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


int
sys_list(void)
{
  list();
  return 0;
}

int
sys_setmodeadmin(void)
{
  myproc()->mode = ADMIN;
  return 0;
}

int
sys_setmodeuser(void)
{
  myproc()->mode = USER;
  return 0;
}


uint getsz(void)
{
  return myproc()->sz;
}

uint getmemlit(void)
{
  return myproc()->memlim;
}

int
sys_getmemlit(void)
{
  getmemorylimit();
  return 0; 
}


int sys_getsz(void)
{
  getsz();
  return 0;
}

#endif