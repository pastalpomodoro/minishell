/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:30:43 by rbaticle          #+#    #+#             */
/*   Updated: 2024/11/12 13:38:52 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == c)
				i++;
			else
			{
				count++;
				while (s[i] != c && s[i])
					i++;
			}
		}
	}
	return (count);
}

static size_t	len_word(const char *s, char c, size_t pos)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[pos + i] != c && s[pos + i])
			i++;
	}
	return (i);
}

static char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dst;

	dst = malloc(n + 1);
	if (!dst)
		return (0);
	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	fill_res(char ***res, char const *s, char c, size_t *j)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			(*res)[*j] = ft_strndup(s + i, len_word(s, c, i));
			if (!(*res)[*j])
			{
				while ((*j)-- != 0)
					free((*res)[*j]);
				free(*res);
				return (0);
			}
			i += len_word(s, c, i);
			(*j)++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	j;

	res = malloc(sizeof(char *) * (get_words(s, c) + 1));
	if (!res)
		return (0);
	j = 0;
	if (s)
	{
		if (!fill_res(&res, s, c, &j))
			return (0);
	}
	res[j] = 0;
	return (res);
}
