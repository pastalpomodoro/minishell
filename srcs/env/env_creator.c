/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:58:10 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/29 14:23:53 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static t_env	*init_env(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->content = ft_strdup(value);
	if (!new->content)
		return (NULL);
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
		node = node->next;
	}
	node->next = init_env("CIAO=salut");
	return (init);
}
