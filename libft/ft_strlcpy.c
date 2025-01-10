/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:48:19 by rbaticle          #+#    #+#             */
/*   Updated: 2024/09/27 20:25:03 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	if (dstsize > 0)
	{
		i = -1;
		while (++i < dstsize - 1 && src[i])
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (len);
}
