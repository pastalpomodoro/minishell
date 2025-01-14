/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:34:50 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/14 19:03:43 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tkn_lst	*get_first(t_tkn_lst *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

static t_tkn_lst	*create_token(char *line, t_token type)
{
	t_tkn_lst	*e;

	e = malloc(sizeof(t_tkn_lst));
	if (!e)
		return (NULL);
	
}

t_tkn_lst	*get_tokens(char *line)
{
	t_tkn_lst	*list;

	if (!line)
		return (NULL);
	while (*line)
	{
		if (ft_strncmp(line, "(", 1))
			list = create_token(line, T_O_PAR);
	}
	return (get_first(list));
}
