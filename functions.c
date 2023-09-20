#include "shell.h"

void remove_nwl(char *str)
{
        int i;
        for (i = 0; str[i] != '\0'; i++)
        {
                if (str[i] == '\n')
                {
                        break;
                }
                i++;
        }
        str[i] = '\0';
}

void remove_cmt(char *str)
{
        int i = 0;
        if (str[i] == '#')
        {
                str[i] = '\0';
        }
        for (i = 0; str[i] != '\0'; i++)
        {
                if (str[i] == '#' && str[i - 1] == ' ')
                {
                        break;
                }
                i++;
        }
        str[i] = '\0';
}

char **token(char *str, char *delim)
{
        int numDelim = 0;
        char **argv = NULL;
        char * tok = NULL;
        char * sPtr = NULL;
        tok = strtok_r(str, delim, &sPtr);
        argv = (char **)(malloc(BUFFER_SIZE * sizeof(char *)));
        if (argv != NULL)
        {
                for (numDelim = 0; tok != NULL; numDelim++)
                {
                        argv[numDelim] = (char *)malloc(sizeof(char) * 1024);
                        if (argv[numDelim] != NULL)
                        {
                                argv[numDelim] = tok;
                                tok = strtok_r(NULL, delim, &sPtr);
                        }
                }
                argv[numDelim] = NULL;
        }
		return (argv);
}

char *get_envron(char *path)
{
        char **env;
        char * pPtr;
        char * path_copy;

        env = environ;
        while (*env != NULL)
        {
                pPtr = *env;
                path_copy = path;
                while (*pPtr == *path_copy)
                {
                        if (*pPtr == '=')
                        {
                                break;
                        }
                        pPtr++;
                        path_copy++;
                }
                if ((*pPtr == '=') && (*path_copy == '\0'))
                {
                        return (pPtr + 1);
                }
                env++;
        }
        return (NULL);
}

char *path_chk(char *cmd)
{
        char **arrPath = NULL;
        char * path = get_envron("PATH");
        char * pHolder, *pHolder1, *pathDup;
        int cnt = 0;
        if (path == NULL || strlen(path) == 0)
		{
			return (NULL);
		}

        pathDup = (char *)malloc(sizeof(char) * (strlen(path) + 1));
        strcpy(path, pathDup);
        arrPath = token(pathDup, ":");
        while (arrPath[cnt] != NULL)
        {
                pHolder1 = strcat(arrPath[cnt], "/");
                pHolder = strcat(pHolder1, cmd);
                if (access(pHolder, F_OK) == 0)
                {
                        free(pHolder1);
                        free(arrPath);
                        free(pathDup);
                }
                free(pHolder);
                free(pHolder1);

                cnt++;
        }
        free(pathDup);
        free(arrPath);
        return (NULL);
}
