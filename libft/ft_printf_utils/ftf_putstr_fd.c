/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftf_putstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:09:13 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/04 20:20:05 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ftf_putstr_fd(char *s, int fd)
{
	if (!s)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}
