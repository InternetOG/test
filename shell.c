#include "shell.h"

char **cmds = NULL;
char *buff = NULL;
char *sh_name = NULL;
int check_status = 0;


int main(int argc, char *argv[])
{
        char **curr_cmd = NULL;
        int i, cmd_type = 0;
        size_t cnt = 0;

        (void) argc;

        signal(SIGINT, ctrl_c);
        sh_name = argv[0];
        while (1)
        {
                non_interactive();
                _printf(" ($) ", 1);
                if (getline(&buff, &cnt, 0) == -1)
                {
                        free(buff);
                        exit(check_status);
                }
                remove_nwl(buff);
                remove_cmt(buff);
                cmds = token(buff, ";");
                i = 0;
                while (cmds[i] != NULL)
                {
                        curr_cmd = token(cmds[i], " ");
                        if (curr_cmd[0] == NULL)
                        {
                                free(curr_cmd);
                                break;
                        }
                        cmd_type = parse_cmd(curr_cmd[0]);
                        init(curr_cmd, cmd_type);
                        free(curr_cmd);
                }
                free(cmds);
        }
        free(buff);
        return (check_status);
}
