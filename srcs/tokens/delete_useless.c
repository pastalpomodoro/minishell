/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_useless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:45:05 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/18 14:03:08 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_quote(char *in_quote, char *line, int i)
{
	if (*in_quote != 0 && line[i] == *in_quote)
		*in_quote = 0;
	else if ((line[i] == '\'' && line[i + 1] != '\'')
		|| (line[i] == '\"' && line[i + 1] != '\"'))
		*in_quote = line[i];
}

static int	check_export_quote(char *line, int *i, char **res)
{
	char	*tmp;

	if (!ft_strncmp(&line[*i], "export \"\"", 9)
		|| !ft_strncmp(&line[*i], "export ''", 9))
	{
		*i += 9;
		tmp = ft_strjoin(*res, "export ''");
		free(*res);
		if (tmp == NULL)
			return (1);
		*res = tmp;
	}
	return (0);
}

static bool	t2quote(char *line, int i)
{
	if (line[i] && line[i + 1] && ((line[i] == '\"' && line[i + 1] == '\"')
			|| (line[i] == '\'' && line[i + 1] == '\'')))
		return (true);
	return (false);
}

static int	check_special_cases(char *line, int *i, char **res, char *in_quote)
{
	if (check_export_quote(line, i, res))
		return (1);
	check_quote(in_quote, line, *i);
	if (line[*i])
	{
		if (*in_quote == 0 && line[*i] == ':' && (ft_isspace(line[*i + 1])
				|| !line[*i + 1]) && (*i - 1 < 0 || ft_isspace(line[*i - 1])))
			(*i)++;
		else if (*in_quote == 0 && line[*i] == '.' && (ft_isspace(line[*i + 1])
				|| !line[*i + 1]) && (*i - 1 < 0 || ft_isspace(line[*i - 1])))
			(*i)++;
	}
	check_quote(in_quote, line, *i);
	return (0);
}

char	*delete_useless(char *line)
{
	char	*res;
	int		i;
	char	in_quote;

	res = NULL;
	i = 0;
	in_quote = 0;
	while (line[i])
	{
		if (check_special_cases(line, &i, &res, &in_quote))
			return (free(line), NULL);
		if (line[i] && line[i] == '$' && t2quote(line, i + 1) && in_quote == 0)
			i += 3;
		else if (t2quote(line, i) && in_quote == 0)
			i += 2;
		else if (line[i])
		{
			res = ft_strjoin_char(res, line[i]);
			if (res == NULL)
				return (free(line), NULL);
			check_quote(&in_quote, line, i);
			i++;
		}
	}
	return (free(line), res);
}
