/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:44:27 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/21 13:52:44 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

void	if_statement(t_commande *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		cmd->exit_code = ft_echo(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		cmd->exit_code = ft_export(cmd->cmd[1], &data->env);
	else if (!ft_strcmp(cmd->cmd[0], "cd") && cmd->cmd[1])
		cmd->exit_code = ft_cd(cmd->cmd[1], data->env);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		cmd->exit_code = ft_env(data->env);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && cmd->cmd[1])
		cmd->exit_code = ft_unset(cmd->cmd[1], &data->env);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		cmd->exit_code = ft_pwd();
	if (!ft_strcmp(cmd->cmd[0], "exit"))
	{
		if (cmd->cmd[1])
			cmd->exit_code = ft_atoi(cmd->cmd[1]);
		else
			cmd->exit_code = 0;
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

int	manage(t_commande *cmd, t_commande *before, t_data *data, char **env)
{
	if (cmd->cmd && ft_strcmp(cmd->cmd[0], "exit") && pipe(cmd->pipe_fd) == -1)
		return (-1);
	if (cmd->cmd_type != 2 && cmd->cmd && ft_strcmp(cmd->cmd[0], "env"))
		cmd->pid = fork();
	else
		cmd->pid = 0;
	if (cmd->pid == -1)
		return (-1);
	else if (cmd->pid == 0)
		exec(cmd, before, data, env);
	if (cmd->cmd && ft_strcmp(cmd->cmd[0], "exit"))
		close(cmd->pipe_fd[1]);
	return (1);
}
