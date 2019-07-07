////////////////////////////////////////////////////////////////////////////////
/// @file	: shell_pwd.c
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
#include "cd.h"


///cd -
static char* pCdFront = NULL;
static int CdFrontflag = -1;
//cd ..
//static char* pCurrentDir  = NULL;

//cd - 连续cd -的次数
//static cd_count = 0;


char* GetShortNextdir( char *pCurrentDir)
{
    char *TmpDir = pCurrentDir ;
    int len = strlen(pCurrentDir);
    int index = len - 1;
    while(index >= 0)
    {
        if(pCurrentDir[index] == '/')
        {
            break;
        }
        index--;
    }
    fprintf(stdout,"index = %d\n",index); 
    while(index < len -1)
    {
        TmpDir[index] = '\0';
        index++;
    }
    return TmpDir;
}

int cd_parse(char* after_cmd,char *argc,char*home)
{
    int dirRslt = -1;
    if(memcmp(after_cmd,"cd",sizeof("cd")) == 0)
    {
        if(NULL == argc)
        {
            pCdFront = getenv("PWD");
            dirRslt =  chdir( home);
            if(0 > dirRslt)
            {
                fprintf(stderr,"chdir : %s\n",strerror(errno)); 
            }
            setenv("PWD",home,1);
            setenv("OLDPWD",pCdFront,1);
            CdFrontflag = 0;
            return D_OK;
        }
        else if(memcmp(argc,"-",sizeof("-")) == 0)
        {
            if(CdFrontflag == -1)
            {
                fprintf(stdout,"%s\n","-csh: cd: OLDPWD not set"); 
            }
            else
            {
                char*pwdbuf = getcwd(NULL,0);
                if(NULL == pwdbuf)
                {
                    fprintf(stderr,"getcwd : %d:%s\n",__LINE__,strerror(errno)); 
                }
                // fprintf(stderr,"getcwd : %d:%s\n",__LINE__,pwdbuf); 
                setenv("OLDPWD",pwdbuf,1);
                if(NULL != pwdbuf)
                {
                    free(pwdbuf);
                    pwdbuf = NULL;
                }
                dirRslt =  chdir( pCdFront);
                if(0 > dirRslt)
                {
                    fprintf(stderr,"chdir : %s\n",strerror(errno)); 
                }
                char *pwdbufbakup = getcwd(NULL,0);
                if(NULL == pwdbufbakup)
                {
                    fprintf(stderr,"getcwd : %d:%s\n",__LINE__,strerror(errno));
                }
                pCdFront = getenv("OLDPWD");
                
                setenv("PWD",pwdbufbakup,1);
                if(NULL != pwdbufbakup)
                {
                    free(pwdbufbakup);
                    pwdbufbakup = NULL;
                }
            }
        } 
        else
        {
            int isHome = 0; 
            char* home = getenv("HOME");
            int hLen = strlen(home);
            char arg[1024] = { 0 };
            for (int i = 0; i < strlen(argc); ++i) {
                if(argc[i] == '~') {
                    memcpy(&arg[i], home, hLen + 1);
                    isHome = 1;
                }
                else if(isHome)
                {
                    arg[i + hLen - 1] = argc[i];
                    fprintf(stderr,"arg : %s\n",arg);
                }
                else
                {
                    arg[i] = argc[i];
                }
            }

            CdFrontflag = 0;
            pCdFront = getenv("PWD");
            if( chdir(arg) < 0 )
            {
                fprintf(stderr,"csh: cd: %s: %s\n",argc,strerror(errno));
                return D_OK;
            }
            char*pwdbuf = getcwd(NULL,0);
            if(NULL == pwdbuf)
            {
                fprintf(stderr,"getcwd : %d:%s\n",__LINE__,strerror(errno));
            }
            setenv("PWD",pwdbuf,1);
            setenv("OLDPWD",pCdFront,1);
            if(NULL != pwdbuf)
            {
                free(pwdbuf);
                pwdbuf = NULL;
            }
        }
        return D_OK;
    }
    return D_ERR;
}
