/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:31:04 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/06 13:41:04 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_regular_char(char *res, char **line)
{
	char	*tmp;

	tmp = ft_strjoin_char(res, **line);
	if (tmp == NULL)
		return (free(res), NULL);
	(*line)++;
	return (tmp);
}
