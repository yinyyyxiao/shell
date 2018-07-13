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
#include "shell_pwd.h"


//pwd
char sPwdPath[1024] = "";
int iPwdFlag = 0;

ino_t get_inode(char *dirname)                                                                
{                                                                                             
    struct stat info;                                                                         
    if (stat(dirname, &info) == -1)                                                           
    {                                                                                         
        perror("dirname");                                                                    
        exit(1);                                                                                    
    }                                                                                               
    return info.st_ino;                                                                             
}  

void inode_to_dirname(ino_t inode_num, char *pWorkPath,int iPathlen)                                         
{                                                                                                    
    DIR *dir_ptr;                                                                                    
    struct dirent *dire;                                                                             
    if ((dir_ptr = opendir(".")) == NULL)                                                            
    {                                                                                                
        perror(".");                                                                                 
        exit(1);                                                                                     
    }                                                                                                
    while ((dire = readdir(dir_ptr)) != NULL)                                                        
    {                                                                                                
        if (dire->d_ino == inode_num)                                                                
        {                                                                                            
            strncpy(pWorkPath, dire->d_name, iPathlen);                                                      
            pWorkPath[strlen(pWorkPath)] = '\0';                                                                 
            closedir(dir_ptr);                                                                       
            return ;                                                                                 
        }                                                                                            
    }                                                                                                
    fprintf(stderr, "error looking for inode number %d\n", (int)inode_num);                          
    exit(1);                                                                                         
}

void get_work_dir(ino_t inode_num)                                                                  
{                                                                                                   
    ino_t parent_inode;      
    char cWorkPath[128] = "";                                                                                                                                                        
    if (get_inode("..") != inode_num)                                                               
    {                                                                                               
        chdir("..");                                                                                
        inode_to_dirname(inode_num, cWorkPath, 128);                                                     
        parent_inode = get_inode(".");                                                              
        get_work_dir(parent_inode);                                                                 
        sprintf(sPwdPath,"/%s", cWorkPath);                                                                         
    }                                                                                               
}
