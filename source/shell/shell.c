#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_CMD_LEN 256
#define MAX_ARGS 64
#define MAX_PATH_LEN 1024

void cd(char *path)
{
    if (chdir(path) != 0)
    {
        perror("chdir");
    }
}

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

void init_shell()
{
    char cmd[MAX_CMD_LEN];
    char cwd[MAX_PATH_LEN];

    while (1)
    {
        getcwd(cwd, sizeof(cwd));
        printf("\033[0;32mGalactix %s> \033[0m", cwd);

        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
        {
            break;
        }

        if (cmd[strlen(cmd) - 1] == '\n')
        {
            cmd[strlen(cmd) - 1] = 0;
        }

        if (strcmp(cmd, "exit") == 0)
        {
            break;
        }
        else if (strcmp(cmd, "ls") == 0)
        {
            execute("/bin/ls");
            continue;
        }
        else if (strncmp(cmd, "cd ", 3) == 0)
        {
            cd(cmd + 3);
            continue;
        }
        else if (strncmp(cmd, "exec ", 5) == 0)
        {
            execute(cmd + 5);
            continue;
        }
        else
        {
            printf("Unknow command: %s\n", cmd);
        }
    }
}