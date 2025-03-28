/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/25 18:25:07 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

int	double_in(t_tkn_lst *node, t_commande **cmd)
{
	char		*line;
	int			pipe_fd[2];
	t_tkn_lst	*next;

	next = node->next;
	if (node->next == NULL)
		return ((*cmd)->exit_code = 2, ft_printf(NL_ERROR), -2);
	if (next->token != T_LITERAL)
		return ((*cmd)->exit_code = 2, ft_printf(T_ERROR, next->value), -2);
	if (pipe(pipe_fd) == -1)
		return (-2);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (free(line), close(pipe_fd[1]),
				ft_printf(HDOC_ERROR, next->value), pipe_fd[0]);
		else if (ft_strcmp(line, next->value) == 0)
			break ;
		(write(pipe_fd[1], line, ft_strlen(line)), write(pipe_fd[1], "\n", 1));
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	simple_in(t_tkn_lst *node, t_commande **cmd)
{
	int			fd;
	t_tkn_lst	*next;

	next = node->next;
	if (node->next == NULL || (!ft_strcmp(next->value, ">")
			&& next->next == NULL))
		return ((*cmd)->exit_code = 2, ft_printf(NL_ERROR), -2);
	if (next->token != T_LITERAL)
		return ((*cmd)->exit_code = 2, ft_printf(T_ERROR, next->value), -2);
	fd = open(next->value, O_RDONLY);
	if (fd < 0)
	{
		(*cmd)->exit_code = 1;
		ft_printf(FILE_ERROR, next->value);
	}
	return (fd);
}

int	out(t_tkn_lst *node, t_commande **cmd, int type)
{
	t_tkn_lst	*next;

	next = node->next;
	if (next == NULL || (type == 1 && next->token == T_PIPE))
		return ((*cmd)->exit_code = 2, ft_printf(NL_ERROR), -2);
	if (next->token != T_LITERAL)
		return ((*cmd)->exit_code = 2, ft_printf(T_ERROR, next->value), -2);
	if ((*cmd)->fd_out > 2)
		close((*cmd)->fd_out);
	if (type == 1)
		(*cmd)->fd_out = open(next->value, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (type == 2)
		(*cmd)->fd_out = open(next->value, O_RDWR | O_CREAT | O_APPEND, 0777);
	return (1);
}

int	redirect(t_tkn_lst *node, t_commande **cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	if (i++, ft_strcmp(node->value, "<<") == 0)
		fd = double_in(node, cmd);
	else if (i++, ft_strcmp(node->value, "<") == 0)
		fd = simple_in(node, cmd);
	else if (i++, ft_strcmp(node->value, ">") == 0)
		fd = out(node, cmd, 1);
	else if (i++, ft_strcmp(node->value, ">>") == 0)
		fd = out(node, cmd, 2);
	g_error_value = (*cmd)->exit_code;
	if (fd < 0)
		return (fd);
	if (i < 3 && (*cmd)->infile > 2)
		close((*cmd)->infile);
	if (i < 3)
		(*cmd)->infile = fd;
	return (fd);
}
