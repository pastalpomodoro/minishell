/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:40:19 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/30 12:12:20 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_env(t_env *env, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_strdup(""));
	while (env && env->content[i])
	{
		if (str[i] && env->content[i] && env->content[i] == str[i])
			i++;
		else if (env->content[i] == '=')
			return (free(str), ft_strdup(&env->content[i + 1]));
		else
		{
			env = env->next;
			i = 0;
		}
	}
	return (free(str), ft_strdup(""));
}
