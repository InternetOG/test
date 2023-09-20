#include "shell.h"

int strToInt(char *str)
{
        unsigned int cnt = 0;
        int sign = 1;

        for (; *str != '\0'; str++)
        {
                switch (*str)
                {
                        case '-':
                                sign = -1;
                                break;
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                                cnt = (cnt * 10) + (*str - '0');
                                break;
                        default:
                                return -1;
                }
        }

        return (cnt * sign);
}

void __exit(char **cmd_token)
{
        int cntToken = 0;
        int para;

        while (cmd_token[cntToken] != NULL)
        {
                cntToken++;
        }
        if (cntToken == 1)
        {
                free(cmd_token);
                free(buff);
                free(cmds);
                exit(check_status);
        } else if (cntToken == 2)
        {
                para = strToInt(cmd_token[1]);
                if (para == -1)
                {
                        _printf(sh_name, 2);
                        _printf(": 1: exit: Illegal number: ", 2);
                        _printf(cmd_token[1], 2);
                        _printf("\n", 2);
                        check_status = 2;
                } else
                {
                        free(buff);
                        free(cmd_token);
                        free(cmds);
                        exit(para);
                }
        } else
        _printf("$: too many arguments\n", 2);
}

void non_interactive(void)
{
        char **curr_cmd = NULL;
        int    i = 0;
        int    type_cmd = 0;
        size_t bytes = 0;

        if (!(isatty(0)))
        {
                while (getline(&buff, &bytes, stdin) != -1)
                {
                        remove_nwl(buff);
                        remove_cmt(buff);
                        cmds = token(buff, ";");

                        while (cmds[i] != NULL)
                        {
                                curr_cmd = token(cmds[i], " ");
                                if (curr_cmd[0] == NULL)
                                {
                                        free(curr_cmd);
                                        break;
                                }
                                type_cmd = parse_cmd(curr_cmd[0]);
                                init(curr_cmd, type_cmd);
                                free(curr_cmd);
                        }
                        free(cmds);
                }
                free(buff);
                exit(check_status);
        }
}

void _env(char **c)
{		 
        int cnt = 0;
	    (void) c;

        while (environ != NULL)
        {
                _printf(environ[cnt], 1);
                _printf("\n", 1);
        }
}

void ctrl_c(int num)
{
        if (num == SIGINT)
        {
                _printf("\n($)", 0);
        }
}
