/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:50:18 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/11 15:53:52 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

static int	add_wildcard_tokens(t_data *data, char *value)
{
	char		*tmp;
	char		**split;
	int			i;
	t_tkn_lst	*e;

	tmp = get_wildcard(value);
	if (tmp == NULL && g_error_value == MALLOC_ERROR)
		return (1);
	if (tmp == NULL)
		return (1);
	split = ft_split(tmp, ' ');
	if (free(tmp), split == NULL)
		return (1);
	i = -1;
	while (split[++i])
	{
		tmp = ft_strdup(split[i]);
		if (tmp == NULL)
			return (free_double_tab(split), 1);
		e = new_token(tmp, T_LITERAL);
		if (e == NULL)
			return (free_double_tab(split), 1);
		tkn_add_back(&data->lst, e);
	}
	return (free_double_tab(split), 0);
}

int	check_wildcards(char *value, t_data *data)
{
	if (ft_strchr(value, '*'))
	{
		if (add_wildcard_tokens(data, value))
			return (free(value), 1);
		return (free(value), 0);
	}
	return (2);
}
