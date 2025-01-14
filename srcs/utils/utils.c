/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:35:47 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/14 13:29:44 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

//fonction qui free un double tableau attention le double tableau doit
// toujours finire par NULL
void	free_double_tab(char **tab)
{
	int	size;

	size = 0;
	while (tab[size])
		size++;
	while (size >= 0)
		free(tab[size--]);
	free(tab);
}
