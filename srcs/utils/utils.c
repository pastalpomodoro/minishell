/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:35:47 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/30 12:39:46 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

//fonction qui free un double tableau attention le double tableau doit
// toujours finir par NULL
void	free_double_tab(char **tab)
{
	int	size;

	size = 0;
	while (tab[size])
		size++;
	while (size >= 0)
		free(tab[size--]);
	free(tab);
}

bool	ft_isspace(char c)
{
	return ((c == ' ') || (c >= 9 && c <= 13));
}

char	*ft_strjoin_char(char *s1, char ch)
{
	char	*str;
	size_t	i;

	if (ch)
		str = malloc(ft_strlen(s1) + 2);
	else
		str = malloc(ft_strlen(s1) + 1);
	if (!str)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	i = -1;
	if (s1)
	{
		while (s1[++i])
			str[i] = s1[i];
	}
	if (ch)
		str[ft_strlen(s1)] = ch;
	str[ft_strlen(s1) + 1] = '\0';
	if (s1)
		free(s1);
	return (str);
}
