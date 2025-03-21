/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:11:18 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/18 16:42:31 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

static t_token	get_type(char *line)
{
	int	i;

	if (!ft_strncmp(line, ">", 1) || !ft_strncmp(line, "<", 1)
		|| !ft_strncmp(line, ">>", 2) || !ft_strncmp(line, "<<", 2))
		return (T_REDIRECT);
	if (!ft_strncmp(line, "|&", 2))
		return (ERROR);
	if (!ft_strncmp(line, "||", 2) || !ft_strncmp(line, "&&", 2))
	{
		i = 2;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '\0' || line[i] == '&' || line[i] == '|')
			return (ERROR);
		return (T_AND_OR);
	}
	if (!ft_strncmp(line, "&", 1))
		return (ERROR);
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
	if (value[0] == '\0')
		return (*cur += 2, value);
	tmp = replace_vars(env, value);
	free(value);
	if (tmp == NULL)
		return (NULL);
	value = tmp;
	return (value);
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

static char	*get_error_value(char *line)
{
	if (!ft_strncmp(line, "&", 1))
		return (ft_strdup("&"));
	if (!ft_strncmp(line, "&&", 2))
		return (ft_strdup("&&"));
	if (!ft_strncmp(line, "||", 2))
		return (ft_strdup("||"));
	if (!ft_strncmp(line, "|&", 2))
		return (ft_strdup("|&"));
	return (ft_strdup("|"));
}

int	add_token(t_data *data, int size, int *i)
{
	char		*value;
	t_token		type;
	t_tkn_lst	*e;
	int			code;

	type = get_type(&data->line[*i]);
	if (type == ERROR)
		value = get_error_value(&data->line[*i]);
	else
		value = get_value(&data->line[*i], size, i, data->env);
	data->and_or = false;
	if (value == NULL)
		return (1);
	code = check_wildcards(value, data);
	if (code != 2)
		return (code);
	e = new_token(value, type);
	if (e == NULL)
		return (free(value), 1);
	tkn_add_back(&data->lst, e);
	if (type == T_AND_OR)
		return (end_tokenisation_change_line(data, size, i));
	if (type == ERROR)
		return (2);
	return (0);
}
