/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:24:32 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/14 16:07:12 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fonction qui va permettre de prendre tout ce qui est affiche sur le minishell
// et mettre chaque mot dans un double tableau
// exemple:  grep je > outfile.txt
//          [[grep], [je], [>], [outfile.txt], NULL]

t_node	*parse(char **split)
{
	t_node	arbre;
	int		i;

	i = 0;
	while (split[i])
	{
		if (!ft_strcmp(split[i], "export"))
			arbre = create_node(split[i]);
	}
}

int	picking(char *input)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split2(input, " \t\n\v\f\r");
	if (!split)
		return (1);
	parse(split);
	free_double_tab(split);
	return (0);
}
