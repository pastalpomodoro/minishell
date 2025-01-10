/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:07:34 by rbaticle          #+#    #+#             */
/*   Updated: 2024/09/25 16:00:29 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;

	if (!dst)
		return (0);
	if (!src)
		return (dst);
	i = -1;
	while (++i < n)
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
	return (dst);
}
