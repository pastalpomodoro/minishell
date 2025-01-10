/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:24:32 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/10 19:25:16 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fonction qui va permettre de prendre tout ce qui est affiche sur le minishell
// et mettre chaque mot dans un double tableau
// exemple:  grep je > outfile.txt
//          [[grep], [je], [>], [outfile.txt], NULL]

int	picking(char *input)
{
	char	**all;
	int		i;

	i = 0;
	all = ft_split(input, ' ');
	if (!all)
		exit(0);
	while (all[i])
	{
		i++;
	}
	free_double_tab(all);
	return (1);
}
