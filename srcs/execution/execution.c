#include "../../includes/minishell.h"

void	show_cmds(t_commande *cmd)
{
	int	i;

	while (cmd)
	{
		if (cmd->path)
			ft_printf("PATH: %s\n", cmd->path);
		if (cmd->cmd)
		{
			i = -1;
			while (i++, cmd->cmd[i])
				ft_printf("CMD: %s\n", cmd->cmd[i]);
		}
		ft_printf("CMD_TYPE: %d\nINFILE: %d\n",cmd->cmd_type, cmd->infile);
		ft_printf("OUTFILE: %s, OUTFILE_TYPE: %d\nTOKEN: %d\n", cmd->outfile,
			cmd->outfile_type, cmd->token);
		ft_printf("EXIT_CODE: %d\n", cmd->exit_code);
		cmd = cmd->next;
		printf("------------------------------------------\n");
	}
}

int	my_execve(t_commande *cmd, t_env **lst_env, int *exit_code)
{
	int	save;

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

int	exec(t_commande *cmd, t_commande *next, char **env, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (cmd->outfile_type == 0 && next && next->cmd)
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
		exit(0);
	exit (0);
}

int	exec_pipe(t_commande *cmd, t_commande *next, char **env)
{
	int	status;
	int	pid;
	int	pipe_fd[2];

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
		exec(cmd, next, env, pipe_fd);
	wait(&status);
	if (next && next->cmd && next->infile <= 2)
		next->infile = pipe_fd[0];
	else
		close(pipe_fd[0]);
	if (cmd && cmd->fd_out > 2)
		close(cmd->fd_out);
	if (cmd && cmd->infile > 2)
		close(cmd->infile);
	return (close(pipe_fd[1]), status);
}

int	exec_manage(t_commande *cmd, t_env **lst_env, char **env)
{
	t_commande	*next;
	int			exit_code;

	while (cmd)
	{
		exit_code = cmd->exit_code;
		next = cmd->next;
		if (cmd && cmd->cmd)
		{
			if (cmd->exit_code == 0 && (cmd->cmd_type == 2 || ft_strcmp(cmd->cmd[0], "export") == 0 || ft_strcmp(cmd->cmd[0], "env") == 0 || ft_strcmp(cmd->cmd[0], "unset") == 0))//ca veut dire que le path n a pas ete toruve et que on va utiliser les commandes que on a code nous
				my_execve(cmd, lst_env, &exit_code);
			else if (cmd->exit_code == 0 && cmd->cmd_type == 1)
				exit_code = exec_pipe(cmd, next, env);
		}
		if (cmd)
			cmd = next;
	}
	return (exit_code);
	printf("%s", env[0]);
}

void skip_par(char *line)
{
	int o_par;

	o_par = 0;
	while (*line)
	{
		if (*line == '(')
			o_par++;
		else if (*line == ')' && o_par > 0)
			o_par--;
		else if (*line == ')' && o_par == 0)
		{
			(*line)++;
			break;
		}
		(*line)++;
	}
}

int and_or_exec(t_commande *cmd, t_data data, char **env, int p)
{
	int exit_code;
	int status;
	int pid;
	t_commande *tmp;
	t_tkn_lst *l;

	while (1 && ft_strlen(data.line))
	{
		if (!data.lst)
			get_tokens(&data);
		if (!cmd)
			cmd = creator(data.lst, data.env);
		if (cmd && cmd->token == T_OPAR)
		{
			tmp = cmd;
			cmd = cmd->next;
			free_cmd_node(&tmp);
			pid = fork();
			if (pid == 0)
				and_or_exec(cmd, data, env, p + 1);
			wait(&status);
			skip_par(data.line);
			exit_code = status;
		}
		else if (cmd)
			exit_code = exec_manage(cmd, &data.env, env);
		free_cmd(&cmd);
		l = data.lst;
		while (l->next)
			l = l->next;
		if ((l->value[0] == '&' && exit_code != 0) || (l->value[0] == '|' && exit_code == 0))
			break;
		tkn_lst_clear(&data.lst);
		if (!data.and_or)
			break;
	}
	free(data.line);
	if (data.lst)
		tkn_lst_clear(&data.lst);
	if (p > 0)
	{
		free_env(data.env);
		exit(0);
	}
	return (1);
	printf("%s", env[0]);
}
