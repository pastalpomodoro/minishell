/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:11:18 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/30 13:00:29 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO: get type for parenthesis + others cmds ???
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

	type = get_type(&data->line[*i], size);
	if (data->lst && type == T_LITERAL && data->lst->prev
		&& data->lst->prev->prev)
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
