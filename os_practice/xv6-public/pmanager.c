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

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>&;()";

int getcmd(char *buf, int nbuf);
struct cmd* parsecmd(char *s);
void runcmd(struct cmd *cmd);

int isCmdEnd(char *s);
char* getCmdInt(char *s, int * d);
char* getCmdString(char *s, char *d);

int list(void);

struct cmd cmd;
int cmd_argc;
char cmd_argvchar0[100];
char cmd_argvchar1[100];
char cmd_argvchar2[100];
char * cmd_argv[3];
int cmd_argvint1;
int cmd_argvint2;

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
    int stacksize = 13;
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
        parsecmd(buf);
        if(fork() == 0)
            runcmd(&cmd);
        //wait();
        if(cmd.type == _EXIT)
        {
            exit();
        }
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
      else if(s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't')
      {
          cmd.type = _EXIT;
      }
      else
      {
        cmd.type = -1;
      }
      
  }
  else
  {
      if(s[0] == 'k' && s[1] == 'i' && s[2] == 'l' && s[3] == 'l')
      {
          cmd.type = _KILL;
          
          s = getCmdString(s, cmd_argvchar0);
          if(isCmdEnd(s))
            cmd.type = -1;
          else
          {
            s = getCmdInt(s, &cmd_argvint1);
            if(!isCmdEnd(s))
              cmd.type = -1;  
          }
      }
      else if(s[0] == 'e' && s[1] == 'x' && s[2] == 'e' && s[3] == 'c' && s[4] == 'u' && s[5] == 't' && s[6] == 'e' )
      {
          cmd.type = _EXECUTE;

          s = getCmdString(s, cmd_argvchar0);
          if(isCmdEnd(s))
            cmd.type = -1;
          else
          {
            s = getCmdString(s, cmd_argvchar1);
            if(isCmdEnd(s))
              cmd.type = -1;
            else
            {
              s = getCmdInt(s, &cmd_argvint2);
              if(!isCmdEnd(s))
                cmd.type = -1;
            }
          }
      }
      else if(s[0] == 'm' && s[1] == 'e' && s[2] == 'm' && s[3] == 'l' && s[4] == 'i' && s[5] == 'm' )
      {
          cmd.type = _MEMLIM;
          s = getCmdString(s, cmd_argvchar0);
          if(isCmdEnd(s))
            cmd.type = -1;
          else
          {
            s = getCmdInt(s, &cmd_argvint1);
            if(isCmdEnd(s))
              cmd.type = -1;
            else
            {
              s = getCmdInt(s, &cmd_argvint2);
              if(!isCmdEnd(s))
                cmd.type = -1;
            }
          }
      }
      else
      {
        cmd.type = -1;
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
        list();
        break;
    case _KILL:
    #ifdef VERBOSE
        printf(2, "KILL pid : %d!!\n", cmd_argvint1);
    #endif
        kill(cmd_argvint1);
        break;
    case _EXECUTE:
    #ifdef VERBOSE
        printf(2, "Execute path : %s stack size : %d!!\n", cmd_argvchar1, cmd_argvint2);
    #endif
        char * tmp[] = cmd_argvchar1;
        exec2(cmd_argvchar1, tmp, cmd_argvint2);
        break;
    case _MEMLIM:
    #ifdef VERBOSE    
        printf(2, "Memlimit pid : %d limit : %d!!\n", cmd_argvint1, cmd_argvint2);
    #endif
        setmemorylimit(cmd_argvint1, cmd_argvint2);
        break;
    case _EXIT:
    #ifdef VERBOSE     
        printf(2, "Exit !!\n");
    #endif
        exit();
        break;
    default:
        printf(2, "Input Error!!\n");
  }
  cmd->type = -1;
  exit();
}



int isCmdEnd(char *s)
{
  if(s[0] == 0) 
  {
    #ifdef VERBOSE
    printf(2, "isCmdEnd return val -> 1 at First branch!\n");
    #endif
    return 1;
  }
  while(strchr(whitespace, *s)) 
    s++;

  #ifdef VERBOSE
  printf(2, "isCmdEnd return val -> %d\n", s[0]==0);
  #endif
  
  return s[0] == 0;
}

char * getCmdInt(char *s, int * d)
{
  while(strchr(whitespace, *s)) 
    s++;
  
  int ret = (int)( *(s++) - 48);

  while(!strchr(whitespace, *s))
  {
    ret *= 10;
    ret += (int)( *(s++) - 48);
  }

  while(strchr(whitespace, *s)) 
    s++;
  

  #ifdef VERBOSE
  printf(2, "getCmdInt return val -> %d\n", ret);
  #endif
  *d = ret;
  return s;
}
char* getCmdString(char *s, char *d)
{
  while(strchr(whitespace, *s)) 
    s++;

  #ifdef VERBOSE
  char * old_d = d;
  printf(2, "getCmdString now parsing -> ");
  #endif

  while(!strchr(whitespace, *s))
  {
    #ifdef VERBOSE
    printf(2, "%c", *s);
    #endif
    *d = *s;
    d++,s++;
  }
  #ifdef VERBOSE
  printf(2, "\n");
  #endif
  while(strchr(whitespace, *s)) 
    s++;
  
  #ifdef VERBOSE
  printf(2,"getCmdString return val -> %s\n", old_d);
  #endif
  return s;
}



int list(void)
{
  printf(1, "NAME       | PID | TIME  (ms)  | MEMORY  (bytes) | MEMLIM(bytes)\n");
  //int i;
  
  printf(1, "Pmanager's msg : List Done!\n");
  return 0;
}