/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:02:03 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/29 20:39:25 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var(t_env *env, char **line, bool inside_quote)
{
	char	*tmp;

	tmp = NULL;
	(*line)++;
	if (!inside_quote && (**line == '\'') || **line == '\"')
	{
		return (ft_strdup("$"));
	}
	while (**line && (!ft_isspace(**line) || **line != '\''
			|| **line != '\"'))
	{
		tmp = ft_strjoin_char(tmp, **line);
		if (tmp == NULL)
			return (NULL);
		(*line)++;
	}
	return (search_env(env, tmp));
}

static int	join_var_res(t_env *env, char **line, char **res)
{
	char	*tmp;
	char	*dup;

	(*line)++;
	tmp = get_var(env, line, TRUE);
	if (tmp == NULL)
		return (1);
	dup = ft_strdup(*res);
	if (dup == NULL)
		return (free(tmp), 1);
	*res = ft_strjoin(*res, tmp);
	free(tmp);
	free(dup);
	if (*res == NULL)
		return (1);
	return (0);
}

static void	replace_inside_dquote(t_env *env, char **line, char **res)
{
	char	*tmp;
	char	*dup;

	(*line)++;
	while (**line != '\"')
	{
		if (**line == '$')
		{
			if (join_var_res(env, line, res))
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
		while (**line != '\'')
		{
			*res = ft_strjoin_char(*res, **line);
			if (*res == NULL)
				return ;
			(*line)++;
		}
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
		if (*line == '$')
		{
			if (join_var_res(env, &line, &res))
				return (NULL);
		}
		else if (*line == '\'' || *line == '\"')
		{
			replace_inside_quote(env, &line, &res);
			if (res == NULL)
				return (NULL);
		}
		else
		{
			res = ft_strjoin_char(res, *line);
			if (res == NULL)
				return (NULL);
			line++;
		}
	}
	return (res);
}
