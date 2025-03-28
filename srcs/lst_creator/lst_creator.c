/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:25:03 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/18 15:56:13 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

t_commande	*cmd_init(void)
{
	t_commande	*cmd;

	cmd = malloc(sizeof(t_commande));
	if (!cmd)
		return (NULL);
	cmd->pipe_fd = malloc(sizeof(int) * 2);
	if (!cmd->pipe_fd)
		return (free(cmd), NULL);
	cmd->token = T_NULL;
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->next = NULL;
	cmd->fd_out = 1;
	cmd->cmd_type = 0;
	cmd->infile = 0;
	cmd->exit_code = 0;
	return (cmd);
}

void	free_cmd_node(t_commande **cmd)
{
	if ((*cmd)->infile > 2)
		close((*cmd)->infile);
	if ((*cmd)->fd_out > 2)
		close((*cmd)->fd_out);
	if ((*cmd)->path)
		free((*cmd)->path);
	if ((*cmd)->cmd)
		free_double_tab((*cmd)->cmd);
	if ((*cmd)->pipe_fd)
		free((*cmd)->pipe_fd);
	free((*cmd));
}

void	free_cmd(t_commande **cmd, t_data *data)
{
	t_commande	*nxt;

	while ((*cmd))
	{
		nxt = (*cmd)->next;
		if ((*cmd)->token == T_CPAR && data)
			data->and_or = false;
		free_cmd_node(cmd);
		(*cmd) = nxt;
	}
}

t_commande	*creator(t_tkn_lst *node, t_env *env)
{
	t_commande	*cmd;
	t_commande	*init;
	int			i;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	i = 0;
	init = cmd;
	while (node && node->token != T_AND_OR)
	{
		if (is_cmd(&cmd, node, env, &i) == 0)
			return (free_cmd(&init, NULL), NULL);
		else if (is_redir(&cmd, &node) == 0)
			return (free_cmd(&init, NULL), NULL);
		else if (is_pipe(&cmd, node->next, node, &i) == 0)
			return (free_cmd(&init, NULL), NULL);
		else if (is_parentesys(&cmd, node) == 0)
			return (free_cmd(&init, NULL), NULL);
		if (node)
			node = node->next;
	}
	return (init);
}
