/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:27:36 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/11 10:39:32 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(int code, t_data *data, t_commande **cmd)
{
	if (data->lst)
		tkn_lst_clear(&(data->lst));
	if (data->line)
		free(data->line);
	rl_clear_history();
	if (data->env)
		free_env(data->env);
	if (cmd)
		free_cmd(cmd, NULL);
	ft_printf("exit\n");
	exit(code);
}
