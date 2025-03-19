/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:51:45 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/19 11:28:37 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

void	show_cmds(t_commande *cmd)
{
	int	i;

	while (cmd)
	{
		if (cmd->path)
			ft_printf("PATH: %s\n", cmd->path);
		if (cmd->cmd)
		{
			i = -1;
			while (i++, cmd->cmd[i])
				ft_printf("CMD: %s\n", cmd->cmd[i]);
		}
		ft_printf("CMD_TYPE: %d\nINFILE: %d\n", cmd->cmd_type, cmd->infile);
		ft_printf("EXIT_CODE: %d\n", cmd->exit_code);
		cmd = cmd->next;
		printf("------------------------------------------\n\n");
	}
}

void	skip_par(char **line, int n)
{
	int		o_par;
	char	*new;
	char	*tmp;

	o_par = 0;
	tmp = *line;
	while (**line)
	{
		if (**line == '(')
			o_par++;
		else if (**line == ')' && o_par > n)
			o_par--;
		else if (**line == ')' && o_par == n)
		{
			(*line)++;
			break ;
		}
		(*line)++;
	}
	new = ft_strdup(*line);
	free(tmp);
	*line = new;
}

void	skip_for_and_or(char **line)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	tmp = *line;
	while (tmp[i])
	{
		if ((tmp[i] == '&' && tmp[i + 1] == '&')
			|| (tmp[i] == '|' && tmp[i + 1] == '|'))
		{
			break ;
		}
		i++;
	}
	new = ft_strdup(&tmp[i]);
	free(*line);
	*line = new;
}

int	is_novoid_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if (line[i] != 32 && line[i] != 9 && line[i] != 10
			&& line[i] != 11 && line[i] != 12 && line[i] != 13)
			return (1);
		i++;
	}
	return (0);
}

int	and_or_exec(t_commande *cmd, t_data *data, char **env, int p)
{
	int			status;
	int			pid;
	t_commande	*tmp;
	t_tkn_lst	*l;

	while (1 && is_novoid_line(data->line))
	{
		init_signal_in_cmd();
		if (!data->lst)
			get_tokens(data);
		if (!cmd)
			cmd = creator(data->lst, data->env);
		if (cmd && cmd->cmd)
		{
			g_error_value = cmd->exit_code;
			if (!ft_strcmp(cmd->cmd[0], "exit") && cmd->cmd[1] && cmd->cmd[1][0] == '1' && !cmd->next)
				ft_exit(1, data, &cmd);
			else if (!ft_strcmp(cmd->cmd[0], "exit") && !cmd->next)
				ft_exit(0, data, &cmd);
		}
		if (cmd && cmd->token == T_OPAR)
		{
			tmp = cmd;
			cmd = cmd->next;
			free_cmd_node(&tmp);
			pid = fork();
			if (pid == 0)
				and_or_exec(cmd, data, env, p + 1);
			wait(&status);
			skip_par(&data->line, 0);
			g_error_value = status;
		}
		else if (cmd)
			g_error_value = exec_manage(cmd, data, env);
		free_cmd(&cmd, data);
		l = data->lst;
		while (l && l->next)
			l = l->next;
		// printf("TOKEN: %s\n", data->line);
		if (l && ((l->value[0] == '&' && g_error_value != 0) || (l->value[0] == '|' && g_error_value == 0)) && data->line[1] == '(')
			skip_par(&data->line, 1);
		else if ((l && l->value[0] == '&' && g_error_value != 0) || (l && l->value[0] == '|' && g_error_value == 0))
			skip_for_and_or(&data->line);
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
