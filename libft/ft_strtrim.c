/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:45:20 by rbaticle          #+#    #+#             */
/*   Updated: 2024/10/14 13:33:22 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_str(char c, const char *str)
{
	size_t	i;

	if (str)
	{
		i = -1;
		while (str[++i])
		{
			if (str[i] == c)
				return (1);
		}
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	pos;
	char	*str;

	if (!s1)
		return (0);
	pos = 0;
	while (in_str(s1[pos], set))
		pos++;
	len = ft_strlen(&s1[pos]);
	i = 0;
	while (s1[pos] && in_str((s1 + pos)[len - i - 1], set))
		i++;
	len -= i;
	str = malloc(len + 1);
	if (!str)
		return (0);
	i = -1;
	while (s1[pos + ++i] && i < len)
		str[i] = s1[pos + i];
	str[i] = '\0';
	return (str);
}
