/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:20:13 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/04 20:16:54 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putptr(unsigned long p)
{
	int		len;
	char	addr[16];
	int		i;

	len = 0;
	if (!p)
		return (ftf_putstr_fd(NULL_PTR, 1));
	if (write(1, "0x", 2) == -1)
		return (-1);
	len += 2;
	i = 0;
	while (p)
	{
		addr[i] = BASE16_L[p % 16];
		p /= 16;
		i++;
	}
	while (i--)
	{
		if (write(1, &addr[i], 1) == -1)
			return (-1);
		len++;
	}
	return (len);
}

static int	puthex(unsigned long n, int uppercase)
{
	unsigned int	nb;
	int				count;
	char			c;

	count = 0;
	nb = n;
	if (nb >= 16)
	{
		count += puthex(nb / 16, uppercase);
		count += puthex(nb % 16, uppercase);
	}
	else
	{
		if (uppercase)
			c = BASE16_U[nb % 16];
		else
			c = BASE16_L[nb % 16];
		if (write(1, &c, 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

static int	handle_percent(const char *str, va_list *valist)
{
	if (!*str)
		return (-1);
	else if (*str == 'c')
		return (ftf_putchar_fd((unsigned char) va_arg(*valist, int), 1));
	else if (*str == 's')
		return (ftf_putstr_fd(va_arg(*valist, char *), 1));
	else if (*str == 'p')
		return (putptr(va_arg(*valist, unsigned long)));
	else if (*str == 'd' || *str == 'i')
		return (ftf_putnbr_fd(va_arg(*valist, int), 1));
	else if (*str == 'u')
		return (ftf_putnbr_fd(va_arg(*valist, unsigned int), 1));
	else if (*str == 'x')
		return (puthex(va_arg(*valist, unsigned long), 0));
	else if (*str == 'X')
		return (puthex(va_arg(*valist, unsigned long), 1));
	return (write(1, str, 1));
}

int	iter_str(const char *str, va_list *valist)
{
	int	count;
	int	tmp;

	count = 0;
	while (*str)
	{
		if (*str != '%')
		{
			tmp = ftf_putchar_fd(*str, 1);
			if (tmp == -1)
				return (-1);
			count += tmp;
			str++;
		}
		else
		{
			tmp = handle_percent(str + 1, valist);
			if (tmp == -1)
				return (-1);
			count += tmp;
			str += 2;
		}
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	valist;

	count = 0;
	if (str)
	{
		va_start(valist, str);
		count = iter_str(str, &valist);
		if (count == -1)
			return (-1);
		va_end(valist);
		return (count);
	}
	return (-1);
}
