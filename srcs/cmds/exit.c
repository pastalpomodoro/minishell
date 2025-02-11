/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:27:36 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/11 16:35:32 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *arg, t_data *data)
{
	if (data->lst)
		tkn_lst_clear(&(data->lst));
	if (data->line)
		free(data->line);
	rl_clear_history();
	if (data->env)
		free_env(data->env);
	ft_printf("exit\n");
	if (arg)
		exit(ft_atoi(arg));
	exit(0);
}
