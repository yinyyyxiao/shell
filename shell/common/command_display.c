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




int Command_Display(const char *user,const char* pwd,char* cmd, char* computer)
{
        char *pfRslt = NULL;
        if(memcmp("root",user,sizeof("root")) == 0)
        {
            fprintf(stdout,"%s@%s:%s$ ",user, computer, pwd); 
        }
        else
        {
            if(strlen(pwd) < 14)
            {
                fprintf(stdout,"%s@hcuuser-VirtualBox:~%s$ ",user,pwd); 
            }
            else
            {
                fprintf(stdout,"%s@hcuuser-VirtualBox:~%s$ ",user,pwd+14); 
            }
        }
        pfRslt = fgets(cmd,1024,stdin);
        if(NULL == pfRslt)
        {
            return D_ERR;
        }
        if(memcmp("\n",cmd,sizeof("\n")) == 0)
        {
            return D_ERR;
        }
        else if(memcmp("exit\n",cmd,sizeof("exit\n")) == 0)
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
