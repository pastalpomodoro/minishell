/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:36:15 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/06 11:12:00 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 0 -> remplace 1 -> erreur de malloc 2 -> pas de cas trouve
static int	search_replace_env(char *name, char *cmd, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(name, env->content, ft_strlen(name)))
		{
			free(env->content);
			env->content = ft_strdup(cmd);
			if (env->content == NULL)
				return (1);
			return (0);
		}
		env = env->next;
	}
	return (2);
}

int	ft_export(char *cmd, t_env **env)
{
	char	*name;
	int		i;

	i = 0;
	if (env == NULL)
		return (env_add_last(env, init_env(cmd)));
	while (cmd[i] != '=')
		i++;
	name = ft_substr(cmd, 0, i);
	if (name == NULL)
		return (1);
	i = search_replace_env(name, cmd, *env);
	free(name);
	if (i == 0 || i == 1)
		return (i);
	else
		return (env_add_last(env, init_env(cmd)));
}

void	del_node_env(t_env *node)
{
	free(node->content);
	free(node);
}

int	ft_unset(char *cmd, t_env **env)
{
	t_env	*temp;
	t_env	*temp1;

	if (ft_strncmp(cmd, env[0]->content, ft_strlen(cmd)) == 0
		&& env[0]->content[ft_strlen(cmd)] == '=')
	{
		temp = env[0]->next;
		del_node_env(env[0]);
		env[0] = temp;
		return (0);
	}
	temp1 = env[0];
	while (temp1)
	{
		if (ft_strncmp(cmd, temp1->content, ft_strlen(cmd)) == 0
			&& temp1->content[ft_strlen(cmd)] == '=')
		{
			temp->next = temp1->next;
			del_node_env(temp1);
			return (0);
		}
		temp = temp1;
		temp1 = temp1->next;
	}
	return (0);
}
