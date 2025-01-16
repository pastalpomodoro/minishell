/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:34:50 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/16 15:23:59 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tkn_lst	*get_first(t_tkn_lst *list)
{
	while (list->prev)
		list = list->prev;
	return (list);
}

static char	*get_value(t_token type, char **line)
{
	char	*val;

	if (type == T_O_PAR || type == T_C_PAR || type == T_PIPE || type == T_LESS
		|| type == T_GREAT)
		val = malloc(2);
	else if (type == T_AND || type == T_OR || type == T_DLESS
		|| type == T_DGREAT)
		val = malloc(3);
	else
		val = malloc(get_cmd_size(*line, type) + 1);
	if (val == NULL)
		return (NULL);
	return (val);
}

static t_tkn_lst	*create_token(char **line, t_token type, t_tkn_lst *list)
{
	t_tkn_lst	*e;

	e = malloc(sizeof(t_tkn_lst));
	if (!e)
		return (NULL);
	e->prev = list;
	list = e;
	list->token = type;
	list->value = get_value(type, line);
	if (list->value == NULL)
	{
		// TODO: free list + all heap before
		exit(0);
	}
	return (list);
}

t_tkn_lst	*get_tokens(char *line)
{
	t_tkn_lst	*list;
	t_token		type;

	if (!line)
		return (NULL);
	while (*line)
	{
		type = identify_type(line);
		list = create_token(&line, type, list);
	}
	return (get_first(list));
}
