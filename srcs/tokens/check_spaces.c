/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:18:56 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/21 16:35:07 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	has_a_match(char **line, char c)
{
	char	*tmp;

	tmp = *line;
	tmp++;
	while (*tmp)
	{
		if (*tmp == c)
		{
			*line = tmp;
			return (TRUE);
		}
		tmp++;
	}
	return (FALSE);
}

bool	inside_quotes(char **line)
{
	if ((**line == '\'' || **line == '\"')
		&& has_a_match(line, **line))
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
	if (*line && (*line == '|' || *line == '>' || *line == '<'))
	{
		line++;
		if (*line && (*line == '>' || *line == '<'))
			line++;
		if (!(*line == ' ' || *line == '\t')
			|| !(*tmp == ' ' || *tmp == '\t'))
			return (TRUE);
	}
	return (FALSE);
}

void	check_insert_spaces(char *line)
{
	char	*current;
	char	*line_init;

	current = line;
	line_init = line;
	while (current && *current)
	{
		if (inside_quotes(&current))
			current++;
		if (no_spaces_around(current, line_init))
			current = insert_spaces(line, current, line_init);
		current++;
	}
}
