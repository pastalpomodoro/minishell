/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:56:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/21 11:35:09 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tkn_lst	*split_token(char **line)
{
	t_tkn_lst	*lst;

	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (!**line)
		return (NULL);
}
