/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:51:45 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/11 19:35:15 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

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
		ft_printf("CMD_TYPE: %d\nINFILE: %d\n", cmd->cmd_type, cmd->infile);
		ft_printf("EXIT_CODE: %d\n", cmd->exit_code);
		cmd = cmd->next;
		printf("------------------------------------------\n\n");
	}
}

void	if_statement(t_commande *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		g_error_value = ft_echo(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
	{
		if (cmd->cmd[1])
			g_error_value = ft_export(cmd->cmd[1], &data->env);
		else
			g_error_value = ft_export(NULL, &data->env);
	}
	else if (!ft_strcmp(cmd->cmd[0], "cd") && cmd->cmd[1])
		g_error_value = ft_cd(cmd->cmd[1], data->env);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		g_error_value = ft_env(data->env);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && cmd->cmd[1])
		g_error_value = ft_unset(cmd->cmd[1], &data->env);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		g_error_value = ft_pwd();
	if (!ft_strcmp(cmd->cmd[0], "exit"))
	{
		if (cmd->cmd[1])
			g_error_value = ft_atoi(cmd->cmd[1]);
		else
			g_error_value = 0;
	}
}

int	pipe_settings(t_commande **cmd, t_commande **next, int pipe_fd[2],
				int *save)
{
	if ((*cmd)->fd_out < 3 && (*next) && (*next)->cmd)
		(*cmd)->fd_out = pipe_fd[1];
	else
		close(pipe_fd[1]);
	if ((*cmd)->fd_out > 2)
	{
		*save = dup(STDOUT_FILENO);
		if (*save == -1)
			return (0);
		if (dup2((*cmd)->fd_out, STDOUT_FILENO) == -1)
			return (0);
		close((*cmd)->fd_out);
	}
	if ((*next) && (*next)->cmd && (*next)->infile < 3)
		(*next)->infile = pipe_fd[0];
	else
		close(pipe_fd[0]);
	return (1);
}

int	my_execve(t_commande *cmd, t_commande *next, t_data *data)
{
	int	save;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (0);
	if (!pipe_settings(&cmd, &next, pipe_fd, &save))
		return (0);
	if_statement(cmd, data);
	if (cmd->fd_out > 2)
	{
		if (dup2(save, STDOUT_FILENO) == -1)
			return (0);
		close(save);
	}
	return (1);
	printf("%s%d", data->env->content, g_error_value);
}

int	exec(t_commande *cmd, t_commande *before, t_commande *next, char **env)
{
	if (cmd->fd_out > 2)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exit (1);
		close(cmd->fd_out);
	}
	else if (next && next->cmd)
	{
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	close(cmd->pipe_fd[1]);
	if (before && before->cmd && cmd->infile <= 2)
	{
		if (dup2(before->pipe_fd[0], STDIN_FILENO) == -1)
			exit (1);
		close(before->pipe_fd[0]);
	}
	if (execve(cmd->path, cmd->cmd, env) == -1)
		exit(1);
	exit(0);
}

int fork_create(t_commande *cmd, t_data data, char **env)
{
	t_commande *init;
	t_commande *before;

	init = cmd;
	before = NULL;
	while (cmd)
	{
		if (pipe(cmd->pipe_fd) == -1)
			return (free_cmd(&init, NULL), -1);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (free_cmd(&init, NULL), -1);
		else if (cmd->pid == 0)
		{
			if (cmd->cmd_type == 2)
				printf("faire l execution avec nos cmd %s\n", data.env->content);
			else if (cmd->cmd_type == 1 && cmd->cmd)
				exec(cmd, before, cmd->next, env);
		}
		close(cmd->pipe_fd[1]);
		before = cmd;
		cmd = cmd->next;
		// printf("ciao");
	}
	return (1);
}
int waitor(t_commande *cmd)
{
	int status;

	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	return (1);
}
int	exec_manage(t_commande *cmd, t_data *data, char **env)
{
	show_cmds(cmd);
	if (fork_create(cmd, *data, env) == -1)
		return (-1);
	waitor(cmd);

	return (1);
}
