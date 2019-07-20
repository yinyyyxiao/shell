#include <stdio.h>
#include <shell_common.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"
#include "s_readline.h"
// hiisory store
static HistoryStore*  history = NULL;
#define MAX_LINE (1024)

static int fromFileCmd = 0;

static HistoryStore* CreateHistory()
{
    HistoryStore* history = (HistoryStore*)malloc(sizeof(HistoryStore));
    if(history == NULL) {
        return NULL;
    }
    history->data = NULL;
    history->pNext = NULL;
    return history;
}

void historyInit()
{
    HistoryStore* pTmp = history;
    while(pTmp->pNext != NULL) {
        pTmp = pTmp->pNext;
        add_history(pTmp->data);
    }
}

static void stripEnter(char* data)
{
    int i = 0;
    while(data[i] != '\0') {
        if(data[i] == '\n') {
            data[i] = '\0';
        }
        ++i;
    }
}

static void getHistoryFileName(char* cshrc)
{
    char* home = getenv("HOME");
    memcpy(cshrc, home, strlen(home));
    strcat(cshrc, "/.bash_history");
}

void getHistoryList()
{
    if(history == NULL) {
        history = CreateHistory();
        if (history == NULL) {
            return;
        }
    }
    char str[MAX_LINE] = {0};
    char cshrc[1024] = {0};
    getHistoryFileName(cshrc);
    FILE* fp = fopen(cshrc, "a+");
    if (fp == NULL)
    {
        printf("%s : %s",cshrc,strerror(errno));
        return;
    }
    while(!feof(fp)) {
        fgets(str,MAX_LINE,fp);
        if (*str == '#') {
            continue;
        }
        stripEnter(str);
        if (memcmp(str,"",sizeof("")) == 0) {
            continue;        
        }
        HistoryStore* pNode = (HistoryStore*)malloc(sizeof(HistoryStore));
        pNode->data = (char*)malloc(strlen(str));
        pNode->pNext = NULL;
        memcpy(pNode->data,str,strlen(str));
        HistoryStore* pTmp = history;
        while(pTmp->pNext != NULL) {
            pTmp = pTmp->pNext;
        }
        ++fromFileCmd;
        pTmp->pNext = pNode;
        memset(str,0,MAX_LINE);
    }
    printf("lllll: %d", fromFileCmd);
    fclose(fp);
}

static void  writeHistoryFile()
{
    char cshrc[1024] = {0};
    getHistoryFileName(cshrc);
    FILE* fp = fopen(cshrc, "a");
    if (fp == NULL)
    {
        printf("%s : %s",cshrc,strerror(errno));
        return;
    }
    HistoryStore* pTmp = history;
    int i = 0;
    while(pTmp->pNext != NULL) {
        pTmp = pTmp->pNext;
        ++i;
        if(i > fromFileCmd) {
            fprintf(stderr,"%s\n",pTmp->data);
            fprintf(fp,"%s\n",pTmp->data);
            fflush(fp);
        }
    }
    fclose(fp);
}

void addHistory(const char* cmd)
{
    if ((cmd == NULL) ||
        (memcmp(cmd,"",sizeof("")) == 0) || 
        (memcmp(cmd, "\n", sizeof("\n")) == 0)) {
        return;
    }
    printf("%s",cmd);
    HistoryStore* pNode = (HistoryStore*)malloc(sizeof(HistoryStore));
    pNode->data = (char*)malloc(strlen(cmd));
    pNode->pNext = NULL;
    memcpy(pNode->data,cmd,strlen(cmd));
    HistoryStore* pTmp = history;
    while(pTmp->pNext != NULL) {
        pTmp = pTmp->pNext;
    }
    pTmp->pNext = pNode;
}

void destoryHistory()
{
    writeHistoryFile();
    HistoryStore* pDel = NULL;
    HistoryStore* pTmp = history;
    while(pTmp->pNext != NULL) {
        pDel = pTmp->pNext;
        pTmp = pTmp->pNext;
        if (pDel->data != NULL) {
            free(pDel->data);
            pDel->data = NULL;
        }
        free(pDel);
        pDel = NULL;
    }
    free(history);
    history = NULL;
}


