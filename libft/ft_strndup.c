/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:40:30 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/21 16:43:41 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*str;

	str = malloc(n + 1);
	if (!str)
		return (0);
	i = -1;
	while (++i < n--)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}
