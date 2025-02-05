#include "../../includes/minishell.h"

int exec(t_commande *cmd, char **env, int outfile)
{
    if (cmd->infile > 2)
    {
        if (dup2(cmd->infile, STDIN_FILENO) == -1)
            exit(1);
        close(cmd->infile);
    }
    if (outfile > 2)
    {
        if (dup2(outfile, STDOUT_FILENO) == -1)
            exit(1);
        close(outfile);
    }
    if (execve(cmd->path, cmd->cmd, env) == -1)
       exit(1);
    return (1);
}

int exec_avec_outfile(t_commande *cmd, char **env)
{
    int status;
    int	pid;
    int fd_out;

    fd_out = 1;
    if (cmd->outfile_type == 1)
        fd_out = open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (cmd->outfile_type == 2)
        fd_out = open(cmd->outfile, O_RDWR | O_CREAT | O_APPEND, 0777);
    pid = fork();
	if (pid < 0)
		return (ft_printf("Erreur avec fork\n"), -2);
	else if (pid == 0)
        exec(cmd, env, fd_out);
    wait(&status);
    return (close(fd_out), status);
}
int gestion(t_commande *cmd, char **env)
{
    t_commande *temp;

    while (cmd)
    {
        temp = cmd->next;
        if (cmd->exit_code == 0 && cmd->outfile)
        {
            if (exec_avec_outfile(cmd, env) != 0)
                return (0);
        }
        cmd = temp;
    }
    return (1);
}