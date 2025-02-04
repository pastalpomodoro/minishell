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

void	free_cmd(t_commande **cmd)
{
	if ((*cmd)->infile > 2)
		close((*cmd)->infile);
	if ((*cmd)->outfile > 2)
		close((*cmd)->outfile);
	free((*cmd));
}

t_commande	*creator(t_tkn_lst *node, t_env *env)
{
	t_commande	*cmd;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	while (node)
	{
		if (node->token == T_REDIRECT)
		{
			if (redirect(node, &cmd) < 0)
				return (free_cmd(&cmd), NULL);
			// ft_printf("REDIRECT: %s\n", node->value);
		}
		// if (node->token == T_LITERAL)
		// {
		//     // i = cmd_creator(&cmd, node, env);
		//     // if (i < 0)
		//     //     return (i);
		// }
		// if (node->token  == T_PIPE)
		// {
		//     (*cmd)->next = cmd_init();
		//     if (!(*cmd)->next)
		//         return (-2);
		//     cmd = (*cmd)->next; 
		// }
		node = node->next;
	}
	return (cmd);
	ft_printf("%s", env->content);
}
