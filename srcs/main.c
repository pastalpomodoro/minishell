/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/10 19:24:12 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_exit(char *input)
{
	char	*exit;
	int		i;

	exit = "exit";
	i = 0;
	while (input[i])
	{
		if (exit[i] != input[i])
			return (0);
		i++;
	}
	return (1);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("Minishell> ");
		if (input)
		{
			picking(input);
			add_history(input);
		}
		if (if_exit(input) == 1)
			break ;
		free(input);
	}
	free(input);
	rl_clear_history();
}
