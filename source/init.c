#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#define MAX_ARGS 64

void execute(char *cmd)
{
    char *args[MAX_ARGS];
    int i = 0;

    args[i] = strtok(cmd, " ");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }

    if (fork() == 0)
    {
        execv(args[0], args);
        perror("execv");
        exit(1);
    }
    else
    {
        wait(NULL);
    }
}

int main()
{
    setenv("PATH", "/bin", 1);
    setenv("PS1", "\\[\e[32m\\]Galactix \\W \\$ \\[\e[0m\\]", 1);
    setenv("TERM", "vt100", 1);
    execute("/bin/bash");

    return 0;
}