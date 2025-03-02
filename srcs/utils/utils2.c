/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:22:35 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/26 11:22:48 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*strjoin_space(char *s1, char *s2)
{
	char	*res;

	if (s1 == NULL)
		res = ft_strdup(s2);
	else
	{
		res = variadic_strjoin(3, s1, " ", s2);
		free(s1);
	}
	return (res);
}
