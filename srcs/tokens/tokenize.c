/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:34:50 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/06 15:52:25 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_eof(char *line)
{
	if (line)
		return (FALSE);
	return (TRUE);
}

static bool	no_need_token(t_data *data)
{
	if (is_eof(data->line))
		return (TRUE);
	if (*data->line == '\0')
		return (TRUE);
	return (FALSE);
}

static int	check_line(t_data *data)
{
	if (data->line == NULL || data->line[0] == '\0')
	{
		data->lst = new_token(ft_strdup("exit"), T_LITERAL);
		return (1);
	}
	if (no_need_token(data))
		return (1);
	data->line = check_insert_spaces(data->line);
	if (data->line == NULL)
		return (1);
	data->line = delete_useless(data->line);
	return (0);
}

void	get_tokens(t_data *data)
{
	t_tkn_lst	*lst;
	int			i;
	int			code;

	lst = NULL;
	if (check_line(data))
		return ;
	i = 0;
	while (data->line[i])
	{
		while (ft_isspace(data->line[i]))
			i++;
		if (data->line[i])
		{
			code = split_token(data, &i);
			if (code == 1)
			{
				tkn_lst_clear(&lst);
				return ;
			}
			if (code == 2)
				return ;
		}
	}
}
