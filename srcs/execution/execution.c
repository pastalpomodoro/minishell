/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:51:45 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/20 12:23:35 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

void	dup2isor(t_commande *cmd, t_commande *next, t_commande *before)
{
	if (cmd->fd_out > 2)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exit (1);
		close(cmd->fd_out);
	}
	else if (next && next->token == T_NULL)
	{
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	close(cmd->pipe_fd[1]);
	if (cmd->infile > 2)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			exit (1);
		close(cmd->infile);
	}
	else if (before && before->cmd
		&& cmd->infile <= 2 && before->exit_code == 0)
	{
		if (dup2(before->pipe_fd[0], STDIN_FILENO) == -1)
			exit (1);
		close(before->pipe_fd[0]);
	}
}

int	dup2_our_cmd(t_commande *cmd, t_commande *next, t_commande *before)
{
	if (cmd->fd_out > 2)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (141);
		close(cmd->fd_out);
	}
	else if (next && next->token == T_NULL)
	{
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			return (141);
	}
	if (cmd->infile > 2)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (141);
		close(cmd->infile);
	}
	else if (before && before->cmd && cmd->infile <= 2
		&& before->exit_code == 0)
	{
		if (dup2(before->pipe_fd[0], STDIN_FILENO) == -1)
			return (141);
		close(before->pipe_fd[0]);
	}
	return (close(cmd->pipe_fd[1]), 0);
}

void	exec(t_commande *cmd, t_commande *before, t_data *data, char **env)
{
	int	save;
	int	save_in;

	if (cmd->cmd_type == 2 || (cmd->cmd && !ft_strcmp(cmd->cmd[0], "env")))
	{
		save = dup(STDOUT_FILENO);
		save_in = dup(STDIN_FILENO);
		if (ft_strcmp(cmd->cmd[0], "exit"))
			cmd->exit_code = dup2_our_cmd(cmd, cmd->next, before);
		if (cmd->exit_code == 0)
			if_statement(cmd, data);
		dup2(save, STDOUT_FILENO);
		dup2(save_in, STDIN_FILENO);
		close(save);
		close(save_in);
	}
	else if (cmd->cmd_type == 1 && cmd->cmd)
	{
		close(cmd->pipe_fd[0]);
		dup2isor(cmd, cmd->next, before);
		if (execve(cmd->path, cmd->cmd, env) == -1)
			exit(1);
		exit(0);
	}
}

int	fork_create(t_commande *cmd, t_data *data, char **env)
{
	t_commande	*init;
	t_commande	*before;

	init = cmd;
	before = NULL;
	while (cmd)
	{
		if (cmd->exit_code == 0)
		{
			if (manage(cmd, before, data, env) == -1)
				return (free_cmd(&init, NULL), -1);
			if (before && ft_strcmp(before->cmd[0], "exit"))
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
	int	status;

	status = 0;
	if (fork_create(cmd, data, env) == -1)
		return (-1);
	while (cmd)
	{
		if (cmd->exit_code == 0 && cmd->cmd_type != 2)
			waitpid(cmd->pid, &status, 0);
		if (!cmd->next && cmd->exit_code)
			return (cmd->exit_code);
		cmd = cmd->next;
	}
	if (status)
		return (130);
	return (0);
}
