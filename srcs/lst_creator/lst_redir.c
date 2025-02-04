/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/04 13:41:37 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	double_in(t_tkn_lst *node)
{
	char		*line;
	int			pipe_fd[2];
	t_tkn_lst	*next;

	next = node->next;
	if (node->next == NULL)
		return (ft_printf("minishell: syntax error near \
unexpected token `newline'\n"), -1);
	if (next->token != T_LITERAL)
		return (ft_printf("minishell: syntax error near \
unexpected token `%s'\n", next->value), -1);
	if (pipe(pipe_fd) == -1)
		return (-2);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, next->value) == 0)
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	simple_in(t_tkn_lst *node)
{
	int			fd;
	t_tkn_lst	*next;

	next = node->next;
	if (node->next == NULL)
		return (ft_printf("minishell: syntax error near \
unexpected token `newline'\n"), -1);
	if (next->token != T_LITERAL)
		return (ft_printf("minishell: syntax error near \
unexpected token `%s'\n", next->value), -1);
	fd = open(next->value, O_RDONLY);
	if (fd < 0)
		ft_printf("minishell: %s: No such file or directory\n", next->value);
	return (fd);
}

int	out(t_tkn_lst *node, int type)
{
	int			fd;
	t_tkn_lst	*next;

	next = node->next;
	if (next == NULL)
		return (ft_printf("minishell: syntax error near \
unexpected token `newline'\n"), -1);
	if (next->token != T_LITERAL)
		return (ft_printf("minishell: syntax error near \
unexpected token `%s'\n", next->value), -1);
	if (type == 1)//>
		fd = open(next->value, O_WRONLY | O_CREAT | O_TRUNC);
	if (type == 2)//>>
		fd = open(next->value, O_WRONLY | O_CREAT | O_APPEND);
	if (fd < 0)
		ft_printf("bash: %s: Permission denied", next->next);
	return (fd);
}

int	redirect(t_tkn_lst *node, t_commande **cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	if (i++, ft_strcmp(node->value, "<<") == 0)
		fd = double_in(node);
	else if (i++, ft_strcmp(node->value, "<") == 0)
		fd = simple_in(node);
	else if (i++, ft_strcmp(node->value, ">") == 0)
		fd = out(node, 1);
	else if (i++, ft_strcmp(node->value, ">>") == 0)
		fd = out(node, 2);
	if (fd < 0)
		return (fd);
	if ((*cmd)->infile > 2)
		close((*cmd)->infile);
	if ((*cmd)->outfile > 2)
		close((*cmd)->outfile);
	if (i < 3)
		(*cmd)->infile = fd;
	else if (i > 2)
		(*cmd)->outfile = fd;
	return (fd);
}
