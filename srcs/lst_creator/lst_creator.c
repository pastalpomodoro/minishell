/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:05 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/04 13:42:06 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_commande	*cmd_init(void)
{
	t_commande	*cmd;

	cmd = malloc(sizeof(t_commande));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->next = NULL;
	cmd->infile = 0;
	cmd->outfile = 1;
	return (cmd);
}

void	free_cmd_node(t_commande **cmd)
{
	if ((*cmd)->infile > 2)
		close((*cmd)->infile);
	if ((*cmd)->outfile > 2)
		close((*cmd)->outfile);
	if ((*cmd)->path)
		free((*cmd)->path);
	if ((*cmd)->cmd)
		free_double_tab((*cmd)->cmd);
	free((*cmd));
}

t_commande	*creator(t_tkn_lst *node, t_env *env)
{
	t_commande	*cmd;
	// t_commande	*init;
	int i;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	i = 0;
	// init = cmd;
	while (node)
	{
		if (node->token == T_REDIRECT)
		{
			if (redirect(node, &cmd) < 0)
				return (free_cmd_node(&cmd), NULL);
			node = node->next;
		}
		else if (node->token == T_LITERAL)
		{
			cmd_creator(node, &cmd, env);
			return (cmd);
			i = 1;
		}
		else if (node->token  == T_PIPE)
		{
		    cmd->next = cmd_init();
		    if (!cmd->next)
		        return (NULL);
		    cmd = cmd->next;
			i = 0; 
		}
		if (i == 0)
			node = node->next;
	}
	return (cmd);
}
