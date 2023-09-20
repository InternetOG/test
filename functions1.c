#include "shell.h"

int parse_cmd(char *cmd)
{
        char *envPath = NULL;
        char *inside_cmd[] = {"exit", "env", NULL};
        int cnt = 0;

        while (cmd[cnt] != '\0')
        {
                if (cmd[cnt] == '/')
                {
                        return (1);
                }
                cnt++;
        }
        cnt = 0;
        while (inside_cmd[cnt] != NULL)
        {
                if (strcmp(cmd, inside_cmd[cnt]) == 0)
                {
                        return (2);
                }
        }

        envPath = path_chk(cmd);
        if (envPath != NULL)
        {
                free(envPath);
                return (3);
        }
        return (-1);
}

void (*request_func(char *cmd))(char **)
{
        int cnt = 0;
        struct map mapped[] = {{"env", _env}, {"exit", __exit}};

        while (cnt < 2)
        {
                if (strcmp(cmd, mapped[cnt].cmd_string) == 0)
                {
                        return (mapped[cnt].func);
                }
                cnt++;
        }
        return (NULL);
}

void _printf(char *str, int fd)
{
        int cnt = 0;

        while (str[cnt] != '\0')
        {
                write(fd, &str[cnt], 1);
                cnt++;
        }
}

void exec_cmd(char **token_cmd, int cmd_type)
{
        void (*func)(char **cmd);

        if (cmd_type == 1)
        {
                if (execve(token_cmd[0], token_cmd, NULL) == -1)
                {
                        perror(get_envron("PWD"));
                        exit(2);
                }
        }

        if (cmd_type == 3)
        {
                if (execve(path_chk(token_cmd[0]), token_cmd, NULL) == -1)
                {
                        perror(get_envron("PWD"));
                        exit(2);
                }
        }

        if (cmd_type == 2)
        {
                func = request_func(token_cmd[0]);
                func(token_cmd);
        }

        if (cmd_type == -1)
        {
                _printf(sh_name, 2);
                _printf(": 1: ", 2);
                _printf(token_cmd[0], 2);
                _printf(": not found\n", 2);
                check_status = 5;
        }
}

void init(char **currCmd, int cmdType)
{
        pid_t pID;
        if (cmdType == 1 || cmdType == 3)
        {
                pID = fork();
                if (pID == 0)
                {
                        exec_cmd(currCmd, cmdType);
                } else
                {
                        waitpid(pID, &check_status, 0);
                        check_status >>= 8;
                }
        } else
        {
                exec_cmd(currCmd, cmdType);
        }
}
