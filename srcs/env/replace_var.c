/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:02:03 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/21 14:49:01 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var(t_env *env, char **line, bool inside_quote)
{
	char	*tmp;
	int		first;

	(void) inside_quote;
	tmp = NULL;
	(*line)++;
	first = 0;
	if (!is_valid_input(**line, first) && (**line == '\'' || **line == '\"')
		&& *(line - 2) && (*(*line - 2) == '\'' || *(*line - 2) == '\"'))
		return (ft_strdup("$"));
	while (**line && is_valid_input(**line, first))
	{
		tmp = ft_strjoin_char(tmp, **line);
		if (tmp == NULL)
			return (NULL);
		(*line)++;
		first++;
	}
	tmp = search_env(env, tmp);
	return (tmp);
}

static int	join_var_res(t_env *env, char **line, char **res, bool inside_quote)
{
	char	*tmp;
	char	*new_res;

	tmp = get_var(env, line, inside_quote);
	if (tmp == NULL)
	{
		free(*res);
		*res = NULL;
		return (1);
	}
	new_res = ft_strjoin(*res, tmp);
	free(tmp);
	if (new_res == NULL)
	{
		free(*res);
		*res = NULL;
		return (1);
	}
	free(*res);
	*res = new_res;
	return (0);
}

static void	replace_inside_dquote(t_env *env, char **line, char **res)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$' && !(**(line + 1) == ' ' || **(line + 1) == '\0'))
		{
			if (join_var_res(env, line, res, TRUE))
				return ;
		}
		else
		{
			*res = ft_strjoin_char(*res, **line);
			if (*res == NULL)
				return ;
			(*line)++;
		}
	}
}

static void	replace_inside_quote(t_env *env, char **line, char **res)
{
	if (**line == '\'')
	{
		(*line)++;
		while (**line && **line != '\'')
		{
			*res = ft_strjoin_char(*res, **line);
			if (*res == NULL)
				return ;
			(*line)++;
		}
		if (**line)
			(*line)++;
	}
	else if (**line == '\"')
		replace_inside_dquote(env, line, res);
}

char	*replace_vars(t_env *env, char *line)
{
	char	*res;

	res = NULL;
	while (*line)
	{
		if (*line == '$' && !(*(line + 1) == ' ' || *(line + 1) == '\0'))
		{
			if (join_var_res(env, &line, &res, FALSE))
				return (free(res), NULL);
		}
		else if (*line == '\'' || *line == '\"')
		{
			replace_inside_quote(env, &line, &res);
			if (res == NULL)
				return (NULL);
		}
		else
		{
			res = handle_regular_char(res, &line);
			if (res == NULL)
				return (NULL);
		}
	}
	return (res);
}
