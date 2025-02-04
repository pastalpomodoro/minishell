/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:58:10 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/04 16:52:51 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*get_last_env(t_env *env)
{
	if (env == NULL)
		return (env);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

int	env_add_last(t_env **env, t_env *to_add)
{
	t_env	*tmp;

	if (to_add == NULL)
		return (1);
	if (*env == NULL)
	{
		*env = to_add;
		return (0);
	}
	tmp = get_last_env(*env);
	tmp->next = to_add;
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		free(env->content);
		env = env->next;
		free(temp);
	}
}

t_env	*init_env(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	if (value == NULL)
		return (free(new), NULL);
	new->content = ft_strdup(value);
	if (!new->content)
		return (free(new), NULL);
	return (new);
}

//return (NULL) si probleme de malloc
t_env	*env_creator(char **env)
{
	int		i;
	t_env	*init;
	t_env	*node;

	node = init_env(env[0]);
	if (!node)
		return (NULL);
	init = node;
	i = 0;
	while (i++, env[i])
	{
		node->next = init_env(env[i]);
		if (node->next == NULL)
			return (free_env(init), NULL);
		node = node->next;
	}
	return (init);
}
