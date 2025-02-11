/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:34:50 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/11 16:48:44 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_eof(char *line)
{
	if (line)
		return (FALSE);
	return (TRUE);
}

// TODO: lst with error and $ to display err mesg
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
	return (TRUE);
}

static bool	no_need_token(t_data *data)
{
	if (is_eof(data->line))
		return (TRUE);
	if (*data->line == '\0')
		return (TRUE);
	if (is_single_dollar_sign(data->line))
	{
		data->lst = new_token(ft_strdup("$"), ERROR);
		return (TRUE);
	}
	return (FALSE);
}

void	get_tokens(t_data *data)
{
	t_tkn_lst	*lst;
	int			i;

	lst = NULL;
	if (no_need_token(data))
		return ;
	data->line = check_insert_spaces(data->line);
	if (data->line == NULL)
		return ;
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
				return ;
			}
		}
	}
}
