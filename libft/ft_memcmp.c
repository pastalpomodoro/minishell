/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:00:16 by rbaticle          #+#    #+#             */
/*   Updated: 2024/11/12 12:25:36 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && *(const unsigned char *)(s1 + i)
		== *(const unsigned char *)(s2 + i))
		i++;
	if (i != n)
		return (*(const unsigned char *)(s1 + i)
		- *(const unsigned char *)(s2 + i));
	return (0);
}
