/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:51:45 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/06 15:40:28 by tgastelu         ###   ########.fr       */
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

void	if_statement(t_commande *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		g_error_value = ft_echo(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
	{
		if (cmd->cmd[1])
			g_error_value = ft_export(cmd->cmd[1], &data->env);
		else
			g_error_value = ft_export(NULL, &data->env);
	}
	else if (!ft_strcmp(cmd->cmd[0], "cd") && cmd->cmd[1])
		g_error_value = ft_cd(cmd->cmd[1], data->env);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		g_error_value = ft_env(data->env);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && cmd->cmd[1])
		g_error_value = ft_unset(cmd->cmd[1], &data->env);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		g_error_value = ft_pwd();
	if (!ft_strcmp(cmd->cmd[0], "exit") && cmd->next)
	{
		if (cmd->cmd[1])
			ft_exit(ft_atoi(cmd->cmd[1]), data);
		else
			ft_exit(0, data);
	}
}

int	pipe_settings(t_commande **cmd, t_commande **next, int pipe_fd[2],
				int *save)
{
	if ((*cmd)->fd_out < 3 && (*next) && (*next)->cmd)
		(*cmd)->fd_out = pipe_fd[1];
	else
		close(pipe_fd[1]);
	if ((*cmd)->fd_out > 2)
	{
		*save = dup(STDOUT_FILENO);
		if (*save == -1)
			return (0);
		if (dup2((*cmd)->fd_out, STDOUT_FILENO) == -1)
			return (0);
		close((*cmd)->fd_out);
	}
	if ((*next) && (*next)->cmd && (*next)->infile < 3)
		(*next)->infile = pipe_fd[0];
	else
		close(pipe_fd[0]);
	return (1);
}

int	my_execve(t_commande *cmd, t_commande *next, t_data *data)
{
	int	save;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (0);
	if (!pipe_settings(&cmd, &next, pipe_fd, &save))
		return (0);
	if_statement(cmd, data);
	if (cmd->fd_out > 2)
	{
		if (dup2(save, STDOUT_FILENO) == -1)
			return (0);
		close(save);
	}
	return (1);
	printf("%s%d", data->env->content, g_error_value);
}

int	exec(t_commande *cmd, t_commande *next, char **env, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (cmd->fd_out < 3 && next && next->cmd)
		cmd->fd_out = pipe_fd[1];
	else
		close(pipe_fd[1]);
	if (cmd->infile > 2)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			exit(1);
		close(cmd->infile);
	}
	if (cmd->fd_out > 2)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			exit(1);
		close(cmd->fd_out);
	}
	if (execve(cmd->path, cmd->cmd, env) == -1)
		exit(1);
	exit (0);
}

int	exec_pipe(t_commande *cmd, t_commande *next, char **env)
{
	int	status;
	int	pid;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (ft_printf("Erreur avec fork\n"), -2);
	else if (pid == 0)
		exec(cmd, next, env, pipe_fd);
	wait(&status);
	if (next && next->cmd && next->infile <= 2)
		next->infile = pipe_fd[0];
	else
		close(pipe_fd[0]);
	if (cmd && cmd->fd_out > 2)
		close(cmd->fd_out);
	if (cmd && cmd->infile > 2)
		close(cmd->infile);
	return (close(pipe_fd[1]), status);
}

int	exec_manage(t_commande *cmd, t_data *data, char **env)
{
	t_commande	*next;

	while (cmd)
	{
		g_error_value = cmd->exit_code;
		next = cmd->next;
		if (cmd && cmd->cmd)
		{
			if (cmd->exit_code == 0 && cmd->cmd_type == 2)
				my_execve(cmd, next, data);
			else if (cmd->exit_code == 0 && cmd->cmd_type == 1)
				g_error_value = exec_pipe(cmd, next, env);
		}
		if (cmd)
			cmd = next;
	}
	return (g_error_value);
	printf("%s", env[0]);
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
void skip_for_and_or(char **line)
{
	char *tmp;
	char *new;
	int i;

	i = 0;
	tmp = *line;
	while (tmp[i])
	{
		if ((tmp[i] == '&' && tmp[i + 1] == '&')
			|| (tmp[i] == '|' && tmp[i + 1] == '|'))
		{
			break;
		}
		i++;
	}
	// printf("%s\n", *line);
	new = ft_strdup(&tmp[i]);
	free(*line);
	*line = new;
}

int	is_novoid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32 && line[i] != 9 && line[i] != 10
			&& line[i] != 11 && line[i] != 12 && line[i] != 13)
			return (1);
		i++;
	}
	return (0);
}

int	and_or_exec(t_commande *cmd, t_data data, char **env, int p)
{
	int			exit_code;
	int			status;
	int			pid;
	t_commande	*tmp;
	t_tkn_lst	*l;

	exit_code = 0;
	while (1 && is_novoid_line(data.line))
	{
		if (!data.lst)
			get_tokens(&data);
		if (!cmd)
			cmd = creator(data.lst, data.env);
		if (cmd)
			exit_code = cmd->exit_code;
		if (cmd && cmd->token == T_OPAR)
		{
			tmp = cmd;
			cmd = cmd->next;
			free_cmd_node(&tmp);
			pid = fork();
			if (pid == 0)
				and_or_exec(cmd, data, env, p + 1);
			wait(&status);
			skip_par(&data.line, 0);
			exit_code = status;
		}
		else if (cmd)
			exit_code = exec_manage(cmd, &data, env);
		free_cmd(&cmd, &data);
		l = data.lst;
		while (l && l->next)
			l = l->next;
		if (l && ((l->value[0] == '&' && exit_code != 0) || (l->value[0] == '|' && exit_code == 0)) && data.line[1] == '(')
			skip_par(&data.line, 1);
		else if ((l && l->value[0] == '&' && exit_code != 0) || (l && l->value[0] == '|' && exit_code == 0))
			skip_for_and_or(&data.line);
		tkn_lst_clear(&data.lst);
		if (!data.and_or)
			break ;
	}
	if (data.line)
		free(data.line);
	if (data.lst)
		tkn_lst_clear(&data.lst);
	if (p > 0)
	{
		if (data.env)
			free_env(data.env);
		exit(exit_code);
	}
	return (1);
}
