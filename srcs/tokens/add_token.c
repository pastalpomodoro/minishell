/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:11:18 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/13 14:32:45 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	add_token(t_data *data, int size, int *i)
{
	char		*value;
	t_token		type;
	t_tkn_lst	*e;

	type = get_type(&data->line[*i]);
	value = get_value(&data->line[*i], size, i, data->env);
	if (value == NULL)
		return (1);
	e = new_token(value, type);
	if (e == NULL)
		return (free(value), 1);
	tkn_add_back(&data->lst, e);
	return (0);
}
