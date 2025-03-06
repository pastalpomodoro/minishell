/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_useless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:45:05 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/06 16:35:59 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_quote(char *in_quote, char *line, int i)
{
	if (*in_quote && line[i - 1] == *in_quote)
		*in_quote = 0;
	else if ((line[i] == '\'' && line[i + 1] != '\'')
		|| (line[i] == '\"' && line[i + 1] != '\"'))
		*in_quote = line[i];
}

static bool	is_two_quote(char *line, int i)
{
	if (line[i] && line[i + 1] && ((line[i] == '\"' && line[i + 1] == '\"')
			|| (line[i] == '\'' && line[i + 1] == '\'')))
		return (true);
	return (false);
}

char	*delete_useless(char *line)
{
	char	*res;
	int		i;
	char	in_quote;

	res = NULL;
	i = 0;
	in_quote = false;
	while (line[i])
	{
		check_quote(&in_quote, line, i);
		if (line[i] && line[i] == '$' && is_two_quote(line, i + 1)
			&& in_quote == 0)
			i += 3;
		else if (is_two_quote(line, i) && in_quote == 0)
			i += 2;
		else
		{
			res = ft_strjoin_char(res, line[i]);
			if (res == NULL)
				return (free(line), NULL);
			i++;
		}
	}
	return (free(line), res);
}
