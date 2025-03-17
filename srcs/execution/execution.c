/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:51:45 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/17 14:39:41 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

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

void dup2isor(t_commande *cmd, t_commande *next, t_commande *before)
{
	close(cmd->pipe_fd[0]);
	if (cmd->fd_out > 2)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exit (1);
		close(cmd->fd_out);
	}
	else if (next)
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
}

void	exec(t_commande *cmd, t_commande *before, t_data *data, char **env)
{
	if (cmd->cmd_type == 2)
	{
		dup2isor(cmd, cmd->next, before);
		if_statement(cmd, data);
		exit(0);
	}
	else if (cmd->cmd_type == 1 && cmd->cmd)
	{
		dup2isor(cmd, cmd->next, before);
		if (execve(cmd->path, cmd->cmd, env) == -1)
			exit(1);
		exit(0);
	}
}

int fork_create(t_commande *cmd, t_data *data, char **env)
{
	t_commande *init;
	t_commande *before;

	init = cmd;
	before = NULL;
	while (cmd)
	{
		if (cmd->exit_code == 0)
		{	
			if (pipe(cmd->pipe_fd) == -1)
				return (free_cmd(&init, NULL), -1);
			cmd->pid = fork();
			if (cmd->pid == -1)
				return (free_cmd(&init, NULL), -1);
			else if (cmd->pid == 0)
				exec(cmd, before, data, env);
			close(cmd->pipe_fd[1]);
			if (before)
				close(before->pipe_fd[0]);
			before = cmd;
		}
		cmd = cmd->next;
	}
	if (before && before->exit_code == 0)
		close(before->pipe_fd[0]);
	return (1);
}

int	exec_manage(t_commande *cmd, t_data *data, char **env)
{
	int status;

	status = 0;
	if (fork_create(cmd, data, env) == -1)
		return (-1);
	while (cmd)
	{
		if (cmd->exit_code == 0)
			waitpid(cmd->pid, &status, 0);
		if (!cmd->next && cmd->exit_code)
			return (cmd->exit_code);
		cmd = cmd->next;
	}
	if (status)
		return (130);
	return (0);
}
