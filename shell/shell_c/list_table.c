#include "shell_common.h"

extern struct CommandInfo* head;
struct CommandInfo* CreateTable()
{
    struct CommandInfo* cmd = (struct CommandInfo*)malloc(sizeof(struct CommandInfo));
    if(cmd == NULL)
    {
        return NULL;
    }
    memset(cmd,0,sizeof(struct CommandInfo));
    cmd->pNext = NULL;
    return cmd;
}



int add_cmdInfo(char* cmd)
{
    if((head == NULL) || (cmd == NULL))
    {
        return -1;
    }

    struct CommandInfo* cmdInfo = (struct CommandInfo*)malloc(sizeof(struct CommandInfo));
    if(cmdInfo == NULL)
    {
        return -1;
    }
    size_t cmdLen = strlen(cmd);
    memset(cmdInfo->cmd,0,cmdLen+1);
    memcpy(cmdInfo->cmd, cmd, cmdLen + 1);
    struct CommandInfo* pTmp = head;
    while(pTmp->pNext != NULL) {
        pTmp = pTmp->pNext;
    }

    cmdInfo->pNext = NULL;
    pTmp->pNext = cmdInfo;
    if (pTmp == NULL) {
    
        fprintf(stderr,"nullis\n");
    }
    return 0;
}

void destoryTable()
{
    if(head == NULL) {
        return;
    }
    struct CommandInfo* pTmp = head->pNext;
    struct CommandInfo* pDel = pTmp;
    while(pTmp != NULL) {
        pTmp = pTmp->pNext;
        free(pDel);
        pDel = pTmp;
    }
    free(head);
    head = NULL;
}
