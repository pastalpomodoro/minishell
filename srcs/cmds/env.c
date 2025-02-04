/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:37:48 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/04 16:51:54 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *node)
{
	if (node)
	{
		while (node)
		{
			ft_printf("%s\n", node->content);
			node = node->next;
		}
	}
	return (0);
}
