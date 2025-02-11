/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:44:15 by tgastelu          #+#    #+#             */
/*   Updated: 2025/01/14 15:27:56 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

static int	if_sep(char s, char *c)
{
	size_t	i;

	i = -1;
	while (i++, i < 6)
	{
		if (s == c[i])
			return (1);
	}
	return (0);
}

static char	**count_word(char const *s, char *c)
{
	size_t	i;
	size_t	count_w;
	char	**tab;

	count_w = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && if_sep(s[i], c) == 0)
			count_w++;
		if (if_sep(s[i], c) && if_sep(s[i + 1], c) == 0 && s[i + 1] != '\0')
			count_w++;
		i++;
	}
	tab = malloc(sizeof(char *) * (count_w + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

static char	**ft_free2(char **tab, size_t i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
	return (NULL);
}

char	**ft_split2(char const *s, char *c)
{
	char	**tab;
	size_t	i;
	size_t	start;
	size_t	count_w;

	tab = count_word(s, c);
	if (!tab)
		return (NULL);
	i = 0;
	count_w = 0;
	while (s[i])
	{
		while (s[i] && if_sep(s[i], c))
			i++;
		start = i;
		while (s[i] && if_sep(s[i], c) == 0)
			i++;
		if (start < i)
			tab[count_w] = ft_substr(s, start, i - start);
		if (start < i && !tab[count_w++])
			return (ft_free2(tab, count_w - 1));
	}
	tab[count_w] = NULL;
	return (tab);
}
