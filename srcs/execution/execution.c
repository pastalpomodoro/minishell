#include "../../includes/minishell.h"

int my_execve(t_commande *cmd, t_env **lst_env)
{
	int save;

	if (cmd->outfile_type > 0)
	{
		save = dup(STDOUT_FILENO);
		if (save == -1)
			return (0);
		if (cmd->outfile_type == 1)
			cmd->fd_out = open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (cmd->outfile_type == 2)
			cmd->fd_out = open(cmd->outfile, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (0);
		close(cmd->fd_out);
	}
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		ft_echo(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export") && cmd->cmd[1]) // juste export ca fais un truc a gerer
		ft_export(cmd->cmd[1], lst_env);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		ft_cd(cmd->cmd[1], *lst_env);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		ft_env(*lst_env);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		ft_unset(cmd->cmd[1], lst_env);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		ft_pwd();
	// if (!ft_strcmp(cmd->cmd[0], "exit"))
	// 	ft_exit(init);
	if (cmd->outfile_type > 0)
	{
		if (dup2(save, STDOUT_FILENO) == -1)
			return (0);
	}
	return (1);
}

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

int	exec_manage(t_commande *cmd, t_env **lst_env, char **env)
{
	t_commande	*temp;
	int i;

	i = 0;
	while (cmd)
	{
		temp = cmd->next;
		if (cmd->cmd)
		{
			if (cmd->exit_code == 0 && (cmd->cmd_type == 2 || ft_strcmp(cmd->cmd[0], "export") == 0 || ft_strcmp(cmd->cmd[0], "env") == 0 || ft_strcmp(cmd->cmd[0], "unset") == 0))//ca veut dire que le path n a pas ete toruve et que on va utiliser les commandes que on a code nous
				my_execve(cmd, lst_env);
			if (cmd->exit_code == 0 && cmd->cmd_type == 1)
				exec_pipe(cmd, temp, env);
		}
		cmd = temp;
		i++;
	}
	return (1);
}