/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:43:08 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/20 12:43:21 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
