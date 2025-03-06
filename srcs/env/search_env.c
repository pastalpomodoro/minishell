/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:40:19 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/06 15:22:31 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

int	is_valid_input(char c, int first)
{
	if (first && !(c == '_' || ft_isalpha(c)))
		return (0);
	if (!(ft_isalnum(c) || c == '_'))
		return (0);
	return (1);
}

char	*search_env(t_env *env, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_strdup(""));
	/*if (!ft_strcmp(str, "UID"))*/
	/*	return (free(str), ft_strdup(getenv("USER")));*/
	if (str[0] == '?' && str[1] == '\0')
		return (free(str), ft_itoa(g_error_value));
	while (env && env->content[i])
	{
		if (str[i] && env->content[i] && env->content[i] == str[i])
			i++;
		else if (env->content[i] == '=' && (ft_isspace(str[i])
				|| str[i] == '$' || str[i] == '\0'))
			return (free(str), ft_strdup(&env->content[i + 1]));
		else
		{
			env = env->next;
			i = 0;
		}
	}
	return (free(str), ft_strdup(""));
}
