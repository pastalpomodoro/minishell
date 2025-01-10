/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:03:27 by rbaticle          #+#    #+#             */
/*   Updated: 2024/09/26 15:09:29 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*str;

	str = malloc(ft_strlen(s1) + 1);
	if (!str)
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}
