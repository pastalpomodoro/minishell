/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:23:09 by rbaticle          #+#    #+#             */
/*   Updated: 2024/12/19 16:19:42 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	size_t	i;

	ch = (char) c;
	if (s)
	{
		i = -1;
		while (s[++i])
		{
			if (s[i] == ch)
				return ((char *) &s[i]);
		}
		if (ch == '\0')
			return ((char *) &s[i]);
	}
	return (0);
}
