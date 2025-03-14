/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:34:37 by rbaticle          #+#    #+#             */
/*   Updated: 2024/12/19 16:19:19 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	c;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
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
	if (s2)
	{
		while (s2[i])
			str[c++] = s2[i++];
	}
	str[c] = '\0';
	return (str);
}
