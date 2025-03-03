/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:21:52 by rbaticle          #+#    #+#             */
/*   Updated: 2024/09/27 16:06:56 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ad;
	size_t	len;

	len = count * size;
	if (count != 0)
	{
		if (len / count != size)
			return (0);
	}
	if (size != 0)
	{
		if (len / size != count)
			return (0);
	}
	ad = malloc(len);
	if (!ad)
		return (0);
	ft_bzero(ad, len);
	return (ad);
}
