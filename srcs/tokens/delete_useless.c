/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_useless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:45:05 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/05 18:53:50 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*delete_useless(char *line)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] && line[i + 1] && ((line[i] == '\"' && line[i + 1] == '\"')
				|| (line[i] == '\'' && line[i + 1] == '\'')))
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
