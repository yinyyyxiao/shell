////////////////////////////////////////////////////////////////////////////////
/// @file	: exports.c
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
extern char **environ; 

static int get_equal_sign(char *env)
{
    int index = 0;
    int envlen = strlen(env) + 1;
    if(envlen == 0)
    {
        return -1;
    }
    for(int i = 0;i < envlen; i++)
    {
        if(env[i] == '=')
        {
            fprintf(stderr,"%d\n",index);
            return index;
        }
        index++;
    }
    return -2;
}


int export_c(char *cmd ,char *pCurrentEnv)
{ 
    char **env = environ;   
    fprintf(stderr,"%s %d\n",__func__,__LINE__);
    if(memcmp(cmd,"export",strlen("export") + 1))
    {
        return D_ERR;
    }
    if(NULL == pCurrentEnv)
    {
        while(*env) 
        {
            fprintf(stderr,"declare -x %s\n",*env);
            env++;
        }
        return D_OK;
    }
    int index = get_equal_sign(pCurrentEnv);
    fprintf(stderr,"%d\n",index);
    if(-2 == index)  //没有等号
    {
        char envName[64] = {0};
        int i = 0;
        for(i = 0;i < index + 1;i++)
        {
            envName[i] = pCurrentEnv[i];
        }
        envName[i + 1] = '\0';
         setenv(envName,envName,1);
    }
    else if(0 == index)  //等号后面没有值
    {
        fprintf(stderr,"-csh: exprot '=':not a valid identifier\n");
        //return D_OK;
    }
    else  //有等号
    {
        char envName[64] = {0};
        int i = 0;
        for(i = 0;i < index + 1;i++)
        {
            envName[i] = pCurrentEnv[i];
        }
        envName[i + 1] = '\0';
        
        if(!getenv(envName))
        {
           fprintf(stderr,"%s : first declare\n",envName);
        }

        setenv(envName,&pCurrentEnv[index+2],1);
    }
    return D_OK;
}