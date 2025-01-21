/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:11:18 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/21 16:46:45 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	get_type(char *line, int size)
{
	if (!ft_strncmp(line, "echo", size) || !ft_strncmp(line, "pwd", size)
		|| !ft_strncmp(line, "cd", size) || !ft_strncmp(line, "export", size)
		|| !ft_strncmp(line, "unset", size) || !ft_strncmp(line, "env", size))
		return (T_CMD);
	if (!ft_strncmp(line, ">", size) || !ft_strncmp(line, "<", size)
		|| !ft_strncmp(line, ">>", size) || !ft_strncmp(line, "<<", size))
		return (T_REDIRECT);
	if (!ft_strncmp(line, "|", size))
		return (T_PIPE);
	if (!ft_strncmp(line, "||", size) || !ft_strncmp(line, "&&", size))
		return (T_AND_OR);
	if (*line == '\'')
		return (T_SIMPLE_QUOTE);
	return (T_LITERAL);
}

static char	*get_value(char **line)
{
	// TODO: strndup if no " or ' else dup until ' or "
	return (NULL);
}

int	add_token(char **line, int size, t_tkn_lst **lst)
{
	t_token		type;
	t_tkn_lst	*e;

	e = malloc(sizeof(t_tkn_lst));
	if (e == NULL)
		return (1);
	e->token = get_type(*line, size);
	if (*lst && e->token == T_LITERAL && (*lst)->prev && (*lst)->prev->prev)
	{
		if ((*lst)->prev->prev->token == T_REDIRECT)
			e->token = ERROR;
	}
	e->value = get_value(line);
	return (0);
}
