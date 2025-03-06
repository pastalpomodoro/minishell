/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:11:18 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/06 16:44:08 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

static t_token	get_type(char *line)
{
	if (!ft_strncmp(line, ">", 1) || !ft_strncmp(line, "<", 1)
		|| !ft_strncmp(line, ">>", 2) || !ft_strncmp(line, "<<", 2))
		return (T_REDIRECT);
	if (!ft_strncmp(line, "||", 2) || !ft_strncmp(line, "&&", 2))
		return (T_AND_OR);
	if (!ft_strncmp(line, "|", 1))
		return (T_PIPE);
	if (!ft_strncmp(line, "(", 1))
		return (T_OPAR);
	if (!ft_strncmp(line, ")", 1))
		return (T_CPAR);
	return (T_LITERAL);
}

static char	*get_value(char *line, int size, int *cur, t_env *env)
{
	char	*value;
	char	*tmp;

	(void) cur;
	value = ft_strndup(line, size);
	*cur += size;
	if (value == NULL)
		return (NULL);
	tmp = replace_vars(env, value);
	free(value);
	if (tmp == NULL)
		return (NULL);
	value = tmp;
	return (value);
}

static int	add_wildcard_tokens(t_data *data, char *value)
{
	char		*tmp;
	char		**split;
	int			i;
	t_tkn_lst	*e;

	tmp = get_wildcard(value);
	if (tmp == NULL && g_error_value == MALLOC_ERROR)
		return (1);
	if (tmp == NULL)
		return (1);
	split = ft_split(tmp, ' ');
	if (free(tmp), split == NULL)
		return (1);
	i = -1;
	while (split[++i])
	{
		tmp = ft_strdup(split[i]);
		if (tmp == NULL)
			return (free_double_tab(split), 1);
		e = new_token(tmp, T_LITERAL);
		if (e == NULL)
			return (free_double_tab(split), 1);
		tkn_add_back(&data->lst, e);
	}
	return (free_double_tab(split), 0);
}

static int	end_tokenisation_change_line(t_data *data, int size, int *i)
{
	char	*tmp;

	tmp = ft_strdup(&data->line[*i + size - 1]);
	if (tmp == NULL)
		return (1);
	free(data->line);
	data->line = tmp;
	data->and_or = true;
	return (2);
}

int	add_token(t_data *data, int size, int *i)
{
	char		*value;
	t_token		type;
	t_tkn_lst	*e;

	type = get_type(&data->line[*i]);
	value = get_value(&data->line[*i], size, i, data->env);
	data->and_or = false;
	if (value == NULL)
		return (1);
	if (ft_strchr(value, '*'))
	{
		if (add_wildcard_tokens(data, value))
			return (free(value), 1);
		return (free(value), 0);
	}
	e = new_token(value, type);
	if (e == NULL)
		return (free(value), 1);
	tkn_add_back(&data->lst, e);
	if (type == T_AND_OR)
		return (end_tokenisation_change_line(data, size, i));
	return (0);
}
