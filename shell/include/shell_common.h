////////////////////////////////////////////////////////////////////////////////
/// @file	: shell_commmon.h
/// @brief	: linux shell
/// @date	: 2018/07/05 
/// @author : YYY (最終更新者)
/// @mail   : yinyy2825@163.com
/// @version: 1.0 新規 (更新情報（更新日、更新内容、更新案件）)
///	@note	: Copyright (C) 2017,2018 Free Software Foundation, Inc.
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHELL_COMMON_H_
#define _SHELL_COMMON_H_


//////////////////////////////////////////////////////////////////////////////
/////////  #define
/////////////////////////////////////////////////////////////////////////////
#define D_OK   (0)
#define D_ERR  (-1)
#define D_SHELL_OK (0)
#define D_EXIT  (1)
////////////////////////////////////////////////////////////////////////////////
///						 INCLUDE											 ///
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/utsname.h>


struct CommandInfo {
    char cmd[1024];
    struct CommandInfo *pNext;
};


typedef struct HistoryStore {
    char *data;
    struct HistoryStore *pNext;
} HistoryStore;


#endif //_SHELL_COMMON_H_
