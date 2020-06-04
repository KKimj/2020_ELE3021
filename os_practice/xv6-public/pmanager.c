#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


// int getadmin(char *password);
// int exec2(char *path, char **argv, int stacksize);
// int setmemorylimit(int pid, int limit);
// char * getshmem(int pid); 

#define VERBOSE
#define DEV


// Parsed command representation
#define EXEC  1
#define REDIR 2
#define PIPE  3
#define LIST  4
#define BACK  5
#define _LIST 10
#define _KILL 11
#define _EXECUTE 12
#define _MEMLIM 13
#define _EXIT 14

#define MAXARGS 10

struct cmd {
  int type;
};

struct execcmd {
  int type;
  char *argv[MAXARGS];
  char *eargv[MAXARGS];
};

struct redircmd {
  int type;
  struct cmd *cmd;
  char *file;
  char *efile;
  int mode;
  int fd;
};

struct pipecmd {
  int type;
  struct cmd *left;
  struct cmd *right;
};

struct listcmd {
  int type;
  struct cmd *left;
  struct cmd *right;
};

struct backcmd {
  int type;
  struct cmd *cmd;
};


int getcmd(char *buf, int nbuf);
struct cmd* parsecmd(char *s);
void runcmd(struct cmd *cmd);


struct cmd cmd;

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
    // char * argv_dev[] = {"cat", "echo!"};
    //exec("cat", argv_dev);
    //exec("pmanager", argv_dev);
    #endif

    static char buf[100];
    int fd;
    // Ensure that three file descriptors are open.
    while((fd = open("console", O_RDWR)) >= 0){
        if(fd >= 3){
            close(fd);
            break;
        }
    }

  // Read and run input commands.
    while(getcmd(buf, sizeof(buf)) >= 0){
        if(fork() == 0)
            runcmd(parsecmd(buf));
        wait();
    }


    #ifdef VERBOSE
    printf(1, "Pmanager exit!\n");
    #endif
    exit();
}


int
getcmd(char *buf, int nbuf)
{
  printf(2, "> ");
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}


struct cmd*
parsecmd(char *s)
{
  int len = strlen(s);

  #ifdef VERBOSE
  printf(2, "cmd length-> %d\n",len);
  printf(2, "cmd string-> %s\n", s);
  printf(2, "cmd last char-> %c\n", s[len-1]);
  #endif

  if(len <= 5)
  {
      if(s[0] == 'l' && s[1] == 'i' && s[2] == 's' && s[3] == 't')
      {
          cmd.type = _LIST;
      }
  }
  
  return &cmd;
}

void
runcmd(struct cmd *cmd)
{
  if(cmd == 0)
    exit();

  switch(cmd->type){
    case _LIST:
    #ifdef VERBOSE
        printf(2, "List !!\n");
    #endif
        break;
    case _KILL:
    #ifdef VERBOSE
        printf(2, "KILL !!\n");
    #endif
        break;
    case _EXECUTE:
    #ifdef VERBOSE
        printf(2, "Execute !!\n");
    #endif
        break;
    case _MEMLIM:
    #ifdef VERBOSE    
        printf(2, "Memlimit !!\n");
    #endif

        break;
    case _EXIT:
    #ifdef VERBOSE     
        printf(2, "Exit !!\n");
    #endif
        break;
    default:
        printf(2, "Input Error!!\n");
  }
  exit();
}
