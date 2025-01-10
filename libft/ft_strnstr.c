/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:19:02 by rbaticle          #+#    #+#             */
/*   Updated: 2024/09/26 20:29:45 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;

	if (needle[0] == '\0')
		return ((char *) haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		c = 0;
		while (haystack[i + c] == needle[c] && i + c < len)
		{
			if (needle[c + 1] == '\0')
				return ((char *)(haystack + i));
			c++;
		}
		i++;
	}
	return (0);
}
