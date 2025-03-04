/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:04 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/04 14:32:33 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_tab(t_tkn_lst *node)
{
	int	size;

	size = 0;
	while (node && node->token == T_LITERAL)
	{
		node = node->next;
		size++;
		if (node && node->token == T_REDIRECT)
		{
			node = node->next;
			if (!node)
				break ;
			node = node->next;
		}
	}
	return (size);
}

int	is_our_cmd(char *value)
{
	if (!ft_strcmp("echo", value) || !ft_strcmp("env", value)
		|| !ft_strcmp("export", value) || !ft_strcmp("pwd", value)
		|| !ft_strcmp("unset", value) || !ft_strcmp("exit", value)
		|| !ft_strcmp("cd", value))
		return (1);
	return (0);
}

int	t_redirect(t_tkn_lst **node)
{
	if ((*node) && (*node)->token == T_REDIRECT)
	{
		(*node) = (*node)->next;
		if (!(*node))
			return (0);
		(*node) = (*node)->next;
	}
	return (1);
}

int	cmd_creator(t_tkn_lst *node, t_commande **cmd, t_env *env)
{
	char	*path;
	char	**utils;
	int		i;

	path = get_path(node->value, env, cmd);
	if (!path)
		return (-2);
	if (!ft_strlen(path) && !is_our_cmd(node->value))
		return (ft_printf("minishell: %s: command not found\n", node->value),
			free(path), -1);
	else if (!ft_strlen(path) && is_our_cmd(node->value))
	{
		(*cmd)->exit_code = 0;
		(*cmd)->cmd_type = 2;
	}
	else if (ft_strlen(path))
		(*cmd)->cmd_type = 1;
	(*cmd)->path = path;
	utils = malloc(sizeof(char *) * (size_tab(node) + 1));
	if (!utils)
		return (-2);
	i = 0;
	utils[i] = NULL;
	while (node && node->token == T_LITERAL)
	{
		utils[i] = ft_strdup(node->value);
		if (!utils[i])
			return (free_double_tab(utils), -2);
		i++;
		utils[i] = NULL;
		node = node->next;
		if (t_redirect(&node) == 0)
			break ;
	}
	return ((*cmd)->cmd = utils, 1);
}
