#include "shell_common.h"
#include <readline/readline.h>
#include <readline/history.h>


struct CommandInfo;
char *command_generator(const char *text, int state);
char **fileman_completion(const char *text, int start, int end);
extern struct CommandInfo *head;
struct CommandInfo *pTmp;

char *dupstr(char *s)
{
    char *r;
    r = (char *) malloc(strlen(s) + 1);
    strcpy(r, s);
    return (r);
}

void initialize_readline()
{
    pTmp = head;
    rl_attempted_completion_function = fileman_completion;
}

char **fileman_completion(const char *text, int start, int end)
{
    char **matches;
    matches = (char **) NULL;
    if (start == 0)
        matches = rl_completion_matches(text, command_generator);
    return (matches);
}

char *
command_generator(text, state)
        const char *text;
        int state;
{
    static int len = 0;
    /* If this is a new word to complete, initialize now.  This includes
       saving the length of TEXT for efficiency, and initializing the index
       variable to 0. */
    if (!state) {
        len = strlen(text);
    }

    while (pTmp->pNext != NULL) {
        pTmp = pTmp->pNext;
        if (strncmp(pTmp->cmd, text, len) == 0) {
            return (dupstr(pTmp->cmd));
        }
    }
    if (pTmp->pNext == NULL) {
        pTmp = head;
    }
    /* If no names matched, then return NULL. */
    return ((char *) NULL);
}
