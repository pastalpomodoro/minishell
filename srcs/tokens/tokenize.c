/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:34:50 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/22 21:48:46 by rbaticle         ###   ########.fr       */
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
	while (*line == ' ' || *line == '\t')
		line++;
	if (!(*line))
		return (FALSE);
	if (*line == '$')
		line++;
	while (*line == ' ' || *line == '\t')
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

t_tkn_lst	*get_tokens(char *line)
{
	t_tkn_lst	*lst;
	int			i;

	if (no_need_token(line))
		return (NULL);
	line = check_insert_spaces(line);
	if (line == NULL)
		return (new_token("MALLOC ERROR", ERROR));
	i = 0;
	while (line[i])
	{
		if (split_token(&line[i], &lst, &i))
		{
			tkn_lst_clear(&lst);
			return (new_token("MALLOC ERROR", ERROR));
		}
	}
	return (lst);
}
