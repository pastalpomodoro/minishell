#include "../../includes/minishell.h"

int	exec(t_commande *cmd, char **env, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (cmd->outfile_type == 0 && cmd->next)
		cmd->fd_out = pipe_fd[1];
	else
		close(pipe_fd[1]);
	if (cmd->infile > 2)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			exit(1);
		close(cmd->infile);
	}
	if (cmd->fd_out > 2)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exit(1);
		close(cmd->fd_out);
	}
	if (execve(cmd->path, cmd->cmd, env) == -1)
		exit(1);
	return (1);
}

int	exec_pipe(t_commande *cmd, t_commande *next, char **env)
{
	int	status;
	int	pid;
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (0);
	cmd->fd_out = 1;
	if (cmd->outfile_type == 1)
		cmd->fd_out = open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (cmd->outfile_type == 2)
		cmd->fd_out = open(cmd->outfile, O_RDWR | O_CREAT | O_APPEND, 0777);
	pid = fork();
	if (pid < 0)
		return (ft_printf("Erreur avec fork\n"), -2);
	else if (pid == 0)
		exec(cmd, env, pipe_fd);
	wait(&status);
	if (next && next->infile <= 2)
		next->infile = pipe_fd[0];
	else
		close(pipe_fd[0]);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	return (close(pipe_fd[1]), status);
}

int	exec_manage(t_commande *cmd, char **env)
{
	t_commande	*temp;
	int i;

	i = 0;
	while (cmd)
	{
		temp = cmd->next;
		if (cmd->exit_code == 0 && cmd->cmd)
		{
			if (exec_pipe(cmd, temp, env) != 0)
				return (0);
		}
		cmd = temp;
		i++;
	}
	return (1);
}

// int gestion(t_commande *cmd, char **env)
// {
// 	t_commande *next;

// 	while (cmd)
// 	{
// 		next = cmd->next;
// 		if (execution())
// 	}
// }
//&& ft_strcmp(temp->path, "&&") != 0 && ft_strcmp(temp->path, "") != 0