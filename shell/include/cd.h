////////////////////////////////////////////////////////////////////////////////
/// @file	: cd.h
/// @brief	: linux shell
/// @date	: 2018/07/05 
/// @author : YYY (最終更新者)
/// @mail   : yinyy2825@163.com
/// @version: 1.0 新規 (更新情報（更新日、更新内容、更新案件）)
/// @note	: Copyright (C) 2017,2018 Free Software Foundation, Inc.
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHELL_CD_H_
#define _SHELL_CD_H_

////////////////////////////////////////////////////////////////////////////////
///						 INCLUDE											 ///
////////////////////////////////////////////////////////////////////////////////
#include "shell_common.h"


int cd_parse(char *after_cmd, char *argc, const char *home);


#endif //_SHELL_CD_H_
