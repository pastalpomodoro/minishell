/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:56:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/05 18:43:20 by rbaticle         ###   ########.fr       */
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
	int	count;
	int	tmp;

	count = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			tmp = get_end_quotes(line) + 1;
			count += tmp;
			line += tmp;
		}
		else if (ft_isspace(*line))
			return (count);
		else
		{
			count++;
			line++;
		}
	}
	return (count);
}

int	split_token(t_data *data, int *i)
{
	int	end;

	while (ft_isspace(data->line[*i]))
		(*i)++;
	if (!data->line[*i])
		return (1);
	end = get_end(&data->line[*i]);
	if (end == -1)
		return (1);
	return (add_token(data, end, i));
}
