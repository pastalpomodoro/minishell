/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:09 by rbaticle          #+#    #+#             */
/*   Updated: 2024/09/24 17:55:21 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*sdst;
	unsigned char	*ssrc;

	if (!dst)
		return (0);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		sdst = (unsigned char *) dst;
		ssrc = (unsigned char *) src;
		while (len-- > 0)
			sdst[len] = ssrc[len];
	}
	return (dst);
}
