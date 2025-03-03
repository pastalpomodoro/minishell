/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:46:53 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/03 11:37:07 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*variadic_strjoin(unsigned int argc, ...)
{
	va_list			list;
	unsigned int	i;
	char			*tmp;
	char			*res;
	char			*to_free;

	va_start(list, argc);
	i = -1;
	res = NULL;
	while (++i < argc)
	{
		tmp = va_arg(list, char *);
		if (res == NULL)
			res = ft_strdup(tmp);
		else
		{
			to_free = res;
			res = ft_strjoin(res, tmp);
			free(to_free);
		}
		if (res == NULL)
			return (va_end(list), NULL);
	}
	return (va_end(list), res);
}
