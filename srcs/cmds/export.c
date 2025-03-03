/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:36:15 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/19 13:35:02 by rbaticle         ###   ########.fr       */
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

static int	check_cmd(char *cmd)
{
	if (!(ft_isalpha(*cmd) || *cmd == '_'))
		return (1);
	if (*cmd == '_' && *(cmd + 1) == '=')
		return (1);
	while (ft_isalnum(*cmd) || *cmd == '_')
		cmd++;
	if (*cmd != '=')
		return (1);
	return (0);
}

int	ft_export(char *cmd, t_env **env)
{
	char	*name;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (ft_env_export(*env));
	if (check_cmd(cmd))
		return (ft_printf("minishell: export: « %s » : \
identifiant non valable\n", cmd), 1);
	if (*env == NULL)
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

static void	delete_node(t_env *to_delete, t_env *init)
{
	t_env	*tmp;

	while (ft_strcmp(init->next->content, to_delete->content))
		init = init->next;
	tmp = to_delete->next;
	free(to_delete->content);
	free(to_delete);
	init->next = tmp;
}

int	ft_unset(char *cmd, t_env **env)
{
	t_env	*tmp;

	if (*env)
	{
		tmp = *env;
		while (tmp)
		{
			if (!ft_strncmp(cmd, tmp->content, ft_strlen(cmd)))
				return (delete_node(tmp, *env), 0);
			tmp = tmp->next;
		}
	}
	return (0);
}
