/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:37:48 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/04 14:31:38 by rbaticle         ###   ########.fr       */
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

int	ft_env_export(t_env *node)
{
	if (node)
	{
		while (node)
		{
			ft_printf("export %s\n", node->content);
			node = node->next;
		}
	}
	return (0);
}
