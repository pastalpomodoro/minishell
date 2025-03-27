/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:51:45 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/27 12:55:50 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

int	exitt(t_commande **cmd, t_data *data)
{
	if ((*cmd) && (*cmd)->cmd)
	{
		g_error_value = (*cmd)->exit_code;
		if (!ft_strcmp((*cmd)->cmd[0], "exit") && !(*cmd)->next)
		{
			if ((*cmd)->cmd[1])
			{
				if (check_exit_error(&(*cmd)->cmd[1], data, cmd))
					return (1);
			}
			else
				ft_exit(0, data, cmd);
		}
	}
	return (0);
}

void	execution(t_commande **cmd, t_data *data, char **env, int p)
{
	t_commande	*tmp;
	int			status;
	int			pid;

	if (exitt(cmd, data))
		return ;
	if ((*cmd) && (*cmd)->token == T_OPAR)
	{
		tmp = *cmd;
		(*cmd) = (*cmd)->next;
		free_cmd_node(&tmp);
		pid = fork();
		if (pid == 0)
			and_or_exec((*cmd), data, env, p + 1);
		wait(&status);
		skip_par(&data->line, 0);
		g_error_value = status;
	}
	else if ((*cmd))
		g_error_value = exec_manage((*cmd), data, env);
}

void	and_or(t_data *data)
{
	t_tkn_lst	*l;

	l = data->lst;
	while (l && l->next)
		l = l->next;
	if (l && ((l->value[0] == '&' && g_error_value != 0)
			|| (l->value[0] == '|' && g_error_value == 0))
		&& data->line[1] == '(')
		skip_par(&data->line, 1);
	else if ((l && l->value[0] == '&' && g_error_value != 0)
		|| (l && l->value[0] == '|' && g_error_value == 0))
		skip_for_and_or(&data->line);
}

int	and_or_exec(t_commande *cmd, t_data *data, char **env, int p)
{
	while (1 && is_novoid_line(data->line))
	{
		init_signal_in_cmd();
		if (!data->lst)
			get_tokens(data);
		if (!cmd)
			cmd = creator(data->lst, data->env);
		execution(&cmd, data, env, p);
		free_cmd(&cmd, data);
		and_or(data);
		tkn_lst_clear(&data->lst);
		if (!data->and_or)
			break ;
	}
	if (data->line)
		free(data->line);
	if (data->lst)
		tkn_lst_clear(&data->lst);
	if (p > 0)
	{
		if (data->env)
			free_env(data->env);
		exit(g_error_value);
	}
	return (1);
}
