////////////////////////////////////////////////////////////////////////////////
/// @file	: shell.c
/// @brief	: linux shell
/// @date	: 2018/07/05 
/// @author : YYY (最終更新者)
/// @mail   : yinyy2825@163.com
/// @version: 1.0 新規 (更新情報（更新日、更新内容、更新案件）)
///	@note	: Copyright (C) 2017,2018 Free Software Foundation, Inc.
////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// @实现功能	: shell的命令行
///                 cd ,...
/// @未实现功能 : shell脚本,export未实现
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
///						 INCLUDE											 ///
////////////////////////////////////////////////////////////////////////////////
#include "shell_c.h"
/////有疑问请与我联系

extern int Command_Display(const char *user,const char *pwd,char*cmd);
extern int export_c(char *cmd ,char *pCurrentEnv);

//命令行命令最多有八个参数,先设置这麽多
static char *argv[8] = {NULL};
static int argc = 0;

//命令行参数处理
static void shell_parse(char* cmd)
{
    //status=1 标志一个参数字符串还没有结束 
    //status-0 标志当前命令行字符为空格
    int status = 0;

    for(int i = 0; cmd[i]; i++)
    {
        //将buf中第一个字符地址给 argv[argc++]，然后status置位，直到遇到空格后的下个参数，再将其字符起始地址赋给 argv[]
        if(!isspace(cmd[i])&&status == 0)
        {
            argv[argc++] = cmd+i;
            status = 1;
        }
        else if(isspace(cmd[i]))
        {
            status = 0;
            cmd[i] = 0;
        }
    }    
    for(int i =0 ;i<8;i++)
    {
         fprintf(stdout,"argv[%d] = %s\n",i,argv[i]); 
    }
    argv[argc] = NULL;
    argc = 0;
}

static void shell_execute()
{
    pid_t pid = fork();

    switch(pid)
    {
    //子进程创建失败
    case -1:
        perror("fork error");
        exit(EXIT_FAILURE);
        break;
    //子进程替换,fork()给子进程返回0
    case 0:
        
         //数组形式参数，自动检索环境变量
         execvp(argv[0], argv);
         //进程替换成功不返回，直接从替换进程处结束，如果运行到这里，说明进程替换失败，打印提示信息
         fprintf(stderr,"%s: %s\n",argv[0],"command not found"); 
         exit(EXIT_FAILURE);
    //父进程
    default:
        {
            int st;
            //阻塞等待子进程
            while(wait(&st) != pid);
        }
    }
}

int main(void)
{
    int iRslt = D_ERR;
    char cmd[1024] = {0};
// -r  4.13.0-36-generic
// -s  Linux
// -n  ivilinux-VirtualBox
// -m  x86_64
// -v  #40~16.04.1-Ubuntu SMP Fri Feb 16 23:25:58 UTC 2018
// -o  GNU/Linux
    char computer[256] = {0};
    struct utsname  usname;
    gethostname(computer,256);
    if(uname(&usname) != -1)
    {
        int sysRslt = system("clear");
        if(0 != sysRslt)
        {
            return D_ERR;
        }
        fprintf(stdout,"Welcome to Ubuntu 16.04.2 LTS (%s %s %s)\n\n",computer,usname.release,usname.machine); 
    }
    while(1)
    {
        //printf("start");
        char *home = getenv("HOME");
        char *pwd =  getenv("PWD");
        char *user = getenv("USER");
        iRslt = Command_Display(user,pwd,cmd);
        if(D_ERR == iRslt)
        {
            continue;
        }
        else if(D_EXIT == iRslt)
        {
             return D_SHELL_OK;
        }
        shell_parse(cmd);
        iRslt = export_c(argv[0] ,argv[1]);
        if(D_OK == iRslt)
        {
            continue;
        } 
        iRslt = cd_parse(argv[0],argv[1],home);
        if(D_OK == iRslt)
        {
            continue;
        } 
        shell_execute();
    }
    return D_SHELL_OK;
}
  
   
    





   
























