/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:46:53 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/20 20:50:16 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*variadic_strjoin(unsigned int argc, ...)
{
	va_list			list;
	unsigned int	i;
	char			*arg_buff;
	char			*tmp;
	char			*res;

	va_start(list, argc);
	i = 0;
	res = NULL;
	while (i < argc)
	{
		arg_buff = va_arg(list, char *);
		if (res == NULL)
			res = ft_strdup(arg_buff);
		else
		{
			tmp = ft_strjoin(res, arg_buff);
			free(res);
			res = tmp;
		}
		i++;
	}
	va_end(list);
	return (res);
}
