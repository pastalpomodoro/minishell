/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:38:05 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/04 13:38:19 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **cmd)
{
	int	type;
	int	i;

	type = 1;
	if (ft_strcmp(cmd[1], "-n") == 0)
		type = 2;
	i = type - 1;
	while (i++, cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
	}
	if (type == 1)
		ft_printf("\n");
	return (0);
}
