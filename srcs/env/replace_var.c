/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:02:03 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/29 14:56:33 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_char(char *s1, char ch)
{
	char	*str;
	size_t	i;
	size_t	c;

	if (ch)
		str = malloc(ft_strlen(s1) + 2);
	else
		str = malloc(ft_strlen(s1) + 1);
	if (!str)
		return (0);
	c = 0;
	i = 0;
	if (s1)
	{
		while (s1[i])
			str[c++] = s1[i++];
	}
	i = 0;
	if (ch)
		str[c++] = ch;
	str[c] = '\0';
	free(s1);
	return (str);
}

// TODO: replace env var with " && '
char	*replace_vars(t_env *env, char *line)
{
	char	*res;
	bool	use_env;

	res = NULL;
	use_env = TRUE;
	while (*line)
	{
		if (use_env && *line == '$')
			continue ;
		else if (*line == '\'')
			continue ;
		else if (*line == '\"')
			continue ;
		else
		{
			res = ft_strjoin_char(res, *line);
			if (res == NULL)
				return (NULL);
			line++;
		}
	}
	return (res);
}
