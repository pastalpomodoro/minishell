/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:11:18 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/29 14:57:23 by rbaticle         ###   ########.fr       */
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
	return (T_LITERAL);
}

// TODO: replace env (check for malloc err) + delete ' && "
static char	*get_value(char *line, int size, int *cur, t_env *env)
{
	char	*value;
	/*int		i;*/
	/*char	*tmp;*/
	(void) cur;
	(void) env;

	value = ft_strndup(line, size);
	*cur += size;
	if (value == NULL)
		return (NULL);
	/*if (ft_strchr(line, '$'))*/
	/*	value = replace_vars(env, line);*/
	return (value);
}

int	add_token(t_data *data, int size, int *i)
{
	char		*value;
	t_token		type;
	t_tkn_lst	*e;

	type = get_type(&data->line[*i], size);
	if (data->lst && type == T_LITERAL && data->lst->prev && data->lst->prev->prev)
	{
		if (data->lst->prev->prev->token == T_REDIRECT)
			type = ERROR;
	}
	value = get_value(&data->line[*i], size, i, data->env);
	if (value == NULL)
		return (1);
	e = new_token(value, type);
	if (e == NULL)
		return (free(value), 1);
	tkn_add_back(&data->lst, e);
	return (0);
}
