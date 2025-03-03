/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:44:33 by rbaticle          #+#    #+#             */
/*   Updated: 2024/10/02 15:59:27 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nb_len(int n)
{
	long	nb;
	size_t	len;

	nb = n;
	len = 1;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb / 10 != 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	size_t	len;
	size_t	i;
	char	*str;

	len = get_nb_len(n);
	str = malloc(len + 1);
	if (!str)
		return (0);
	nb = n;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	i = 0;
	str[len] = '\0';
	while (nb / 10 != 0)
	{
		str[len - i - 1] = '0' + (nb % 10);
		nb /= 10;
		i++;
	}
	str[len - i - 1] = '0' + (nb % 10);
	return (str);
}
