/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:57:48 by rbaticle          #+#    #+#             */
/*   Updated: 2024/09/25 19:10:03 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	size_t	i;

	ch = (char) c;
	i = ft_strlen(s) + 1;
	while (i > 0)
	{
		if (s[i - 1] == ch)
			return ((char *) &s[i - 1]);
		i--;
	}
	return (0);
}
