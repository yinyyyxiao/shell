////////////////////////////////////////////////////////////////////////////////
/// @file	: command_display.c
/// @brief	: linux shell
/// @date	: 2018/07/05 
/// @author : YYY (最終更新者)
/// @mail   : yinyy2825@163.com
/// @version: 1.0 新規 (更新情報（更新日、更新内容、更新案件）)
///	@note	: Copyright (C) 2017,2018 Free Software Foundation, Inc.
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
///						 INCLUDE											 ///
////////////////////////////////////////////////////////////////////////////////
#include "shell_common.h"
#include "s_readline.h"


extern char* cmd;

int Command_Display(const char *user,const char* pwd, char* computer)
{
    char cmdline[1024] = {0};
    if(memcmp("root",user,sizeof("root")) == 0)
    {
        strcat(cmdline, user);
        strcat(cmdline, "@");
        strcat(cmdline, computer);
        strcat(cmdline, ":");
        strcat(cmdline, pwd); 
        strcat(cmdline, "$ ");
    }
    else
    {
        if(strlen(pwd) < 14)
        {
            fprintf(stderr,"%s@%s:~%s$ ",user, computer, pwd); 
        }
        else
        {
            fprintf(stderr,"%s@%s:~%s$ ",user, computer, pwd+14); 
        }
    }
    
    if(cmd != NULL) {
        free(cmd);
        cmd = NULL;
    }

    cmd = readline(cmdline);
    if (cmd == NULL) {
        
        fprintf(stdout,"cmd is null\n");
        return D_ERR;
    }
    add_history(cmd);
    if(memcmp("",cmd,sizeof("")) == 0)
    {
        return D_ERR;
    }
    else if(memcmp("exit",cmd,sizeof("exit")) == 0)
    {
        fprintf(stdout,"exit\n");
        return D_EXIT;
    }
    else
    {
        //
    }
    return D_OK;
}
