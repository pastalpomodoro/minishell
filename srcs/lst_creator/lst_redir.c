/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/06 14:10:22 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	double_in(t_tkn_lst *node, t_commande **cmd)
{
	char		*line;
	int			pipe_fd[2];
	t_tkn_lst	*next;

	next = node->next;
	if (node->next == NULL)
		return ((*cmd)->exit_code = 2, ft_printf("minishell: syntax error near \
unexpected token `newline'\n"), -1);
	if (next->token != T_LITERAL)
		return ((*cmd)->exit_code = 2, ft_printf("minishell: syntax error near \
unexpected token `%s'\n", next->value), -1);
	if (pipe(pipe_fd) == -1)
		return (-2);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		else if (ft_strcmp(line, next->value) == 0)
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
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
	if (node->next == NULL)
		return ((*cmd)->exit_code = 2, ft_printf("minishell: syntax error near \
unexpected token `newline'\n"), -1);
	if (next->token != T_LITERAL)
		return ((*cmd)->exit_code = 2, ft_printf("minishell: syntax error near \
unexpected token `%s'\n", next->value), -1);
	fd = open(next->value, O_RDONLY);
	if (fd < 0)
	{
		(*cmd)->exit_code = 1;
		ft_printf("minishell: %s: No such file or directory\n", next->value);
	}
	return (fd);
}

void	type_out(t_tkn_lst *next, t_commande **cmd, int type)
{
	if (type == 1)//>
	{
		(*cmd)->outfile = ft_strdup(next->value);
		(*cmd)->outfile_type = 1;
	}
	if (type == 2)//>>
	{
		(*cmd)->outfile = ft_strdup(next->value);
		(*cmd)->outfile_type = 2;
	}
}

int	out(t_tkn_lst *node, t_commande **cmd, int type)
{
	t_tkn_lst	*next;

	next = node->next;
	if (next == NULL || (type == 1 && next->token == T_PIPE))
		return ((*cmd)->exit_code = 2, ft_printf("minishell: syntax error near \
unexpected token `newline'\n"), -1);
	if (next->token != T_LITERAL)
		return ((*cmd)->exit_code = 2, ft_printf("minishell: syntax error near \
unexpected token `%s'\n", next->value), -1);
	if ((*cmd)->outfile)
		free((*cmd)->outfile);
	type_out(next, cmd, type);
	if (!(*cmd)->outfile)
		return (-2);
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
	if (fd < 0)
		return (fd);
	if (i < 3 && (*cmd)->infile > 2)
		close((*cmd)->infile);
	if (i < 3)
		(*cmd)->infile = fd;
	return (fd);
}
