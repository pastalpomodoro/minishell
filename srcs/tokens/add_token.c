/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:11:18 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/22 21:53:36 by rbaticle         ###   ########.fr       */
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

static char	*get_value(char *line, int size, int *cur)
{
	char	*value;
	int		i;

	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
	{
		i = 0;
		while (line[i] && !(line[i] == '\'' || line[i] == '\"'))
			i++;
		value = ft_strndup(line, i);
	}
	else
		value = ft_strndup(line, size);
	if (value == NULL)
		return (NULL);
	i = ft_strlen(value);
	while (*line && i--)
		(*cur)++;
	return (value);
}

int	add_token(char *line, int size, t_tkn_lst **lst, int *i)
{
	char		*value;
	t_token		type;
	t_tkn_lst	*e;

	type = get_type(line, size);
	if (*lst && type == T_LITERAL && (*lst)->prev && (*lst)->prev->prev)
	{
		if ((*lst)->prev->prev->token == T_REDIRECT)
			type = ERROR;
	}
	value = get_value(line, size, i);
	if (value == NULL)
		return (1);
	e = new_token(value, type);
	if (e == NULL)
		return (free(value), 1);
	tkn_add_back(lst, e);
	return (0);
}
