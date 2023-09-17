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
    int i;
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

}
