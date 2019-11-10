////////////////////////////////////////////////////////////////////////////////
/// @file	: shell_pwd.h
/// @brief	: linux shell
/// @date	: 2018/07/05 
/// @author : YYY (最終更新者)
/// @mail   : yinyy2825@163.com
/// @version: 1.0 新規 (更新情報（更新日、更新内容、更新案件）)
///	@note	: Copyright (C) 2017,2018 Free Software Foundation, Inc.
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHELL_PWD_H_
#define _SHELL_PWD_H_

////////////////////////////////////////////////////////////////////////////////
///						 INCLUDE											 ///
////////////////////////////////////////////////////////////////////////////////
#include "shell_common.h"

ino_t get_inode(char *dirname);

void inode_to_dirname(ino_t inode_num, char *pWorkPath, int iPathlen);

void get_work_dir(ino_t inode_num);


#endif //_SHELL_PWD_H_
