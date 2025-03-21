/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_creator_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:02:39 by tgastelu          #+#    #+#             */
/*   Updated: 2025/03/18 13:39:34 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

int	is_pipe(t_commande **cmd, t_tkn_lst *next, t_tkn_lst *node, int *i)
{
	if (node && node->token == T_PIPE)
	{
		if (!next || !node->prev)
			return (g_error_value = 2, ft_printf(PIPE_ERROR), 0);
		else if (next->token != T_LITERAL && next->token != T_REDIRECT)
			return (g_error_value = 2, ft_printf
				(T_ERROR, next->value), 0);
		(*cmd)->next = cmd_init();
		if (!(*cmd)->next)
			return (0);
		(*cmd) = (*cmd)->next;
		*i = 0;
	}
	return (1);
}

int	is_and_or(t_commande **cmd, t_tkn_lst *node, int *i)
{
	if (node->token == T_AND_OR)
	{
		(*cmd)->next = cmd_init();
		if (!(*cmd)->next)
			return (0);
		(*cmd) = (*cmd)->next;
		if (!ft_strcmp(node->value, "||"))
			(*cmd)->path = ft_strdup("||");
		else if (!ft_strcmp(node->value, "&&"))
			(*cmd)->path = ft_strdup("&&");
		if (!(*cmd)->path)
			return (0);
		(*cmd)->next = cmd_init();
		if (!(*cmd)->next)
			return (0);
		(*cmd) = (*cmd)->next;
		*i = 0;
	}
	return (1);
}

int	is_parentesys(t_commande **cmd, t_tkn_lst *node)
{
	if (node && node->token == T_OPAR)
	{
		(*cmd)->token = T_OPAR;
		(*cmd)->next = cmd_init();
		(*cmd) = (*cmd)->next;
	}
	else if (node && node->token == T_CPAR)
	{
		(*cmd)->next = cmd_init();
		(*cmd) = (*cmd)->next;
		(*cmd)->token = T_CPAR;
	}
	else if (node && node->token == ERROR)
		return (g_error_value = 2, ft_printf(T_ERROR, node->value), 0);
	return (1);
}

int	is_redir(t_commande **cmd, t_tkn_lst **node)
{
	if ((*node)->token == T_REDIRECT && (*cmd)->exit_code == 0)
	{
		if (redirect(*node, cmd) < -1)
			return (0);
		(*node) = (*node)->next;
	}
	return (1);
}

int	is_cmd(t_commande **cmd, t_tkn_lst *node, t_env *env, int *i)
{
	if (node && node->token == T_LITERAL && *i == 0 && (*cmd)->exit_code == 0)
	{
		if (cmd_creator(node, cmd, env) < -1)
			return (0);
		*i = 1;
	}
	return (1);
}
