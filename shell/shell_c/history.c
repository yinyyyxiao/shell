#include <stdio.h>
#include <shell_common.h>
#include <string.h>
#include <stdlib.h>




void getHistoryList()
{
    char* home = getenv("HOME");
    char cshrc[1024] = {0};
    memcpy(cshrc, home, strlen(home));
    strcat(cshrc, "/.bash_hostory");
    FILE* fp = fopen(cshrc, "r+");
    fclose(fp);
}






