/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:38:05 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/05 16:48:05 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_n(char *cmd)
{
	int i;

	i = 2;
	if (!cmd || ft_strncmp("-n", cmd, 2))
		return (0);
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
int	ft_echo(char **cmd)
{
	int	type;
	int	i;

	type = 1;
	i = 1;
	if (cmd[i] && is_n(cmd[i]))
	{
		while (cmd[i] && is_n(cmd[i]))
			i++;
		type = 2;
		if (i > 1)
			i--;
	}
	else
		i = 0;
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
