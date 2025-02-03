/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:18:56 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/03 11:31:18 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	has_a_match(char *line, char c, int *i)
{
	int	cpi;

	cpi = *i;
	while (*line++)
	{
		(*i)++;
		if (*line == c)
			return (TRUE);
	}
	*i = cpi;
	return (FALSE);
}

bool	inside_quotes(char *line, int *i)
{
	if ((*line == '\'' || *line == '\"')
		&& has_a_match(line, *line, i))
		return (TRUE);
	return (FALSE);
}

static bool	no_spaces_around(char *line, char *line_init)
{
	char	*tmp;

	if (line == line_init)
		tmp = line;
	else
		tmp = line - 1;
	if (*line && (*line == '|' || *line == '>' || *line == '<'
			|| (*line == '&' && *line + 1 == '&') || *line == '('
			|| *line == ')'))
	{
		line++;
		if (*line && (*line == '>' || *line == '<' || *line == '|'))
			line++;
		if (!ft_isspace(*line) || !ft_isspace(*tmp))
			return (TRUE);
	}
	return (FALSE);
}

char	*check_insert_spaces(char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	while (line[i])
	{
		if (inside_quotes(&line[i], &i))
			i++;
		if (line[i] && no_spaces_around(&line[i], line))
		{
			new_line = insert_spaces(&line[i], line, &i);
			free(line);
			if (new_line == NULL)
				return (NULL);
			line = new_line;
		}
		else
		{
			if (line[i])
				i++;
		}
	}
	return (line);
}
