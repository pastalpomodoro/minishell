#include "../../includes/minishell.h"

int my_execve(t_commande *cmd, t_env **lst_env, int *exit_code)
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
		*exit_code = ft_echo(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export") && cmd->cmd[1]) 
		*exit_code = ft_export(cmd->cmd[1], lst_env);
	else if (!ft_strcmp(cmd->cmd[0], "cd") && cmd->cmd[1])
		*exit_code = ft_cd(cmd->cmd[1], *lst_env);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		*exit_code = ft_env(*lst_env);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && cmd->cmd[1])
		*exit_code = ft_unset(cmd->cmd[1], lst_env);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		*exit_code = ft_pwd();
	// if (!ft_strcmp(cmd->cmd[0], "exit"))
	// 	ft_exit(init);
	if (cmd->outfile_type > 0)
	{
		if (dup2(save, STDOUT_FILENO) == -1)
			return (0);
	}
	return (1);
}

int	exec(t_commande *cmd, char **env, int *pipe_fd, t_env **lst_env)
{
	t_commande *next;

	next = cmd->next;
	close(pipe_fd[0]);
	if (cmd->outfile_type == 0 && next && next->path && ft_strcmp(next->path, "&&") && ft_strcmp(next->path, "||"))
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
	// ft_printf("OUTFILE: %d\n", cmd->fd_out);
	if (!ft_strcmp(cmd->cmd[0], "env"))
		ft_env(*lst_env);
	else if (execve(cmd->path, cmd->cmd, env) == -1)
		exit(0);
	exit (0);
}

int	exec_pipe(t_commande *cmd, t_commande *next, char **env, t_env **lst_env)
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
		exec(cmd, env, pipe_fd, lst_env);
	wait(&status);
	if (next && next->cmd && next->infile <= 2)
		next->infile = pipe_fd[0];
	else
		close(pipe_fd[0]);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	return (close(pipe_fd[1]), status);
}
void skip_parentesys(t_commande **cmd)
{
	int c_par;

	c_par = 0;
	while ((*cmd))
	{
		(*cmd) = (*cmd)->next;
		if ((*cmd)->token == T_OPAR)
			c_par++;
		else if ((*cmd)->token == T_CPAR && c_par == 0)
		{
			(*cmd) = (*cmd)->next;
			break;
		}
		else if ((*cmd)->token == T_CPAR && c_par > 0)
			c_par--;
	}
}
int	exec_manage(t_commande *cmd, t_env **lst_env, char **env)
{
	t_commande	*next;
	int exit_code;
	int i;
	int pid;

	i = 0;
	pid = -1;
	while (cmd)
	{
		exit_code = cmd->exit_code;
		if (cmd->token == T_OPAR)
		{
			cmd = cmd->next;
			pid = fork();
			if (pid < 0)
				return (ft_printf("Erreur avec fork\n"), -2);
			else if (pid == 0)
			{
				exec_manage(cmd, lst_env, env);
			}
			wait(NULL);
			skip_parentesys(&cmd);
			if (cmd)
				next = cmd->next;
			else
				next = cmd;
		}
		else
			next = cmd->next;
		if (cmd && cmd->cmd)
		{
			// if (cmd->path)
				// ft_printf("INFILE: %d, PATH: %s", cmd->infile, cmd->path);
			if (cmd->exit_code == 0 && (cmd->cmd_type == 2 || ft_strcmp(cmd->cmd[0], "export") == 0 || ft_strcmp(cmd->cmd[0], "unset") == 0))//ca veut dire que le path n a pas ete toruve et que on va utiliser les commandes que on a code nous
				my_execve(cmd, lst_env, &exit_code);
			else if (cmd->exit_code == 0 && cmd->cmd_type == 1)
				exit_code = exec_pipe(cmd, next, env, lst_env);
		}
		if (cmd && cmd->token == T_CPAR)
		{
			// printf("EXIT\n");
			exit(1);
		}
		cmd = next;
		if (cmd && cmd->path && !ft_strcmp(cmd->path, "||") && exit_code == 0)//sy je suis dans un processus enfant je dois exit
			break;
		else if (cmd && cmd->path && !ft_strcmp(cmd->path, "&&") && exit_code != 0)
			break;
		i++;
	}
	return (exit_code);
}
