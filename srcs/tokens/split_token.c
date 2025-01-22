/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:56:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/22 21:53:00 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_end_quotes(char *line)
{
	int		tmp;
	char	quote;
	int		count;

	tmp = 0;
	count = 0;
	if (inside_quotes(line, &tmp))
	{
		quote = *line;
		line++;
		count++;
		while (*line != quote)
		{
			count++;
			line++;
		}
	}
	return (count);
}

static int	get_end(char *line)
{
	int		count;
	char	**split;

	count = 0;
	if (*line == '\'' || *line == '\"')
	{
		count = get_end_quotes(line);
	}
	else
	{
		split = ft_split(line, ' ');
		if (split == NULL)
			return (-1);
		count = ft_strlen(split[0]);
		free_double_tab(split);
	}
	return (count);
}

int	split_token(char *line, t_tkn_lst **lst, int *i)
{
	int	end;

	while (*line == ' ' || *line == '\t')
	{
		line++;
		(*i)++;
	}
	if (!*line)
		return (1);
	end = get_end(line);
	if (end == -1)
		return (1);
	return (add_token(line, end, lst, i));
}
