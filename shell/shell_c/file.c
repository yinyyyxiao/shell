#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

struct CommandInfo;
extern struct CommandInfo* head;
extern struct CommandInfo* CreateTable();
extern int add_cmdInfo(char* cmd);



void getPathFile()
{
    if (head == NULL) {


        DIR *dir;
        head = CreateTable();
        struct dirent *dp;
        int pos = 0;
        char subpath[1024] = {0};
        char* path = getenv("PATH");
        size_t len = strlen(path);
        for(int i = 0; i < len + 1; ++i) {
            if ((path[i] == ':') || (i == len)) {
                memcpy(subpath, &path[pos], i - pos);
                pos = i + 1;

                dir = opendir(subpath);
                if(dir == NULL) {
                    return;
                }
                while ((dp = readdir(dir)) != NULL) {
                    add_cmdInfo(dp->d_name);
                }
                memset(subpath,0,1024);
                closedir(dir);
            }
        }
    }
}


