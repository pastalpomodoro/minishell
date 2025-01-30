#include "../../includes/minishell.h"

int ft_echo(char **cmd, int outfile)
{
    int type;
    int i;
    int save;

    type = 0;
    if (ft_strcmp(cmd[0], "-n") == 0)
        type = 1;
    save = dup(STDOUT_FILENO);
    if (save < 0)
        return (-1);
    if (dup2(outfile, STDOUT_FILENO) == -1)
        return (-1);
    close(outfile);
    i = type - 1;
    while (i++, cmd[i])
    {
        ft_printf("%s", cmd[i]);
        if (cmd[i + 1])
            ft_printf(" ");
    }
    if (type == 0)
        ft_printf("\n");
    if (dup2(save, STDOUT_FILENO) == -1)
        return (-1);
    return (close(save), 1);
}
