/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:51:45 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/25 18:28:06 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

extern int	g_error_value;

void	if_pwd_exec(t_commande *cmd, char **env)
{
	if (!ft_strcmp(cmd->cmd[0], "pwd")
		|| !ft_strcmp(cmd->cmd[0], "/usr/bin/pwd")
		|| !ft_strcmp(cmd->cmd[0], "/bin/pwd"))
	{
		if (execve(cmd->path, (char *[]){"pwd", NULL}, env) == -1)
			exit(1);
	}
	else
	{
		if (execve(cmd->path, cmd->cmd, env) == -1)
			exit(1);
	}
}

void	exec(t_commande *cmd, t_commande *before, t_data *data, char **env)
{
	int	save;
	int	save_in;

	if (cmd->cmd_type == 2 || (cmd->cmd && !ft_strcmp(cmd->cmd[0], "env")))
	{
		save = dup(STDOUT_FILENO);
		save_in = dup(STDIN_FILENO);
		if (cmd->cmd && ft_strcmp(cmd->cmd[0], "exit"))
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
		if_pwd_exec(cmd, env);
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
			if (before && before->cmd && ft_strcmp(before->cmd[0], "exit"))
				close(before->pipe_fd[0]);
			before = cmd;
		}
		cmd = cmd->next;
	}
	if (before && before->cmd && before->exit_code == 0)
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
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		if (WTERMSIG(status) == SIGQUIT)
			return (131);
	}
	if (status)
		return (1);
	return (0);
}
