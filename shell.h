#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Functions */
void remove_nwl(char *str);
void remove_cmt(char *str):

/* Global variables */
extern char *buff;
extern char **cmds;
#endif
