#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

#define BUFFER_SIZE 1024

/**
 * struct map - It maps and check the env and exit command
 * @cmd_string: The command string to be mapped
 * @func: This is a function pointer that execute another function
 */

struct map
{
	char *cmd_string;
	void (*func)(char **cmd);
};

/* Global variables */
extern int check_status;
extern char **cmds;
extern char **environ;
extern char *sh_name;
extern char *buff;

/* Functions */
void remove_nwl(char *str);
void remove_cmt(char *str);
char **token(char *str, char *delim);
char *get_envron(char *path);
char *path_chk(char *cmd);

/* Function1 */
int parse_cmd(char *cmd);
void (*request_func(char *cmd))(char **);
void _printf(char *str, int fd);
void exec_cmd(char **token_cmd, int cmd_type);
void init(char **currCmd, int cmdType);

/* Function2 */
int strToInt(char *s);
void __exit(char **cmd_token);
void non_interactive(void);
void _env(char **c);
void ctrl_c(int num);

#endif
