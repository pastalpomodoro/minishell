/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:27:36 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/27 13:33:50 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

static void	ft_exit_str_error(char *code, t_data *data, t_commande **cmd)
{
	ft_printf("exit\n");
	ft_printf("minishell: exit: %s: numeric argument required\n", code);
	if (data->lst)
		tkn_lst_clear(&(data->lst));
	if (data->line)
		free(data->line);
	rl_clear_history();
	if (data->env)
		free_env(data->env);
	if (cmd)
		free_cmd(cmd, NULL);
	exit(2);
}

int	check_exit_error(char **code, t_data *data, t_commande **cmd)
{
	int	i;

	i = -1;
	while (code[0][++i])
	{
		if (!ft_isdigit(code[0][i]))
			ft_exit_str_error(code[0], data, cmd);
	}
	i = 0;
	while (code[i])
	{
		i++;
	}
	if (i > 1)
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		g_error_value = 1;
		return (1);
	}
	ft_exit(ft_atoi(code[0]), data, cmd);
	return (0);
}

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
