/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:34:50 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/29 14:29:29 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_eof(char *line)
{
	if (line)
		return (FALSE);
	return (TRUE);
}

static bool	is_single_dollar_sign(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (!(*line))
		return (FALSE);
	if (*line == '$')
		line++;
	while (ft_isspace(*line))
		line++;
	if (*line)
		return (FALSE);
	// TODO: add error message $ not foud
	return (TRUE);
}

static bool	no_need_token(char *line)
{
	if (is_eof(line))
		return (TRUE);
	if (*line == '\0')
		return (TRUE);
	if (is_single_dollar_sign(line))
		return (TRUE);
	return (FALSE);
}

t_tkn_lst	*get_tokens(t_data *data)
{
	t_tkn_lst	*lst;
	int			i;

	lst = NULL;
	if (no_need_token(data->line))
		return (NULL);
	data->line = check_insert_spaces(data->line);
	if (data->line == NULL)
		return (NULL);
	i = 0;
	while (data->line[i])
	{
		while (ft_isspace(data->line[i]))
			i++;
		if (data->line[i])
		{
			if (split_token(data, &i))
			{
				tkn_lst_clear(&lst);
				return (NULL);
			}
		}
	}
	return (lst);
}
