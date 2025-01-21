/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:56:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/21 15:47:34 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_end_quotes(char *line)
{
	char	*tmp;
	char	quote;
	int		count;

	count = 0;
	tmp = ft_strdup(line);
	if (tmp == NULL)
		return (-1);
	if (inside_quotes(&tmp))
	{
		quote = *line;
		line++;
		count++;
		while (*line != quote)
		{
			count++;
			line++;
		}
		free(tmp);
	}
	return (count);
}

static int	get_end(char *line)
{
	char	*tmp;
	int		count;
	char	quote;
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
		free(split);
	}
	return (count);
}

int	split_token(char **line, t_tkn_lst **lst)
{
	int	end;

	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (!**line)
		return (1);
	end = get_end(*line);
	if (end == -1)
		return (1);
	return (add_token(line, get_end(*line), lst));
}
