/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 11:20:55 by rbaticle         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	*input;

	if (ac != 1)
		return (0);
	(void)av;
	while (1)
	{
		input = readline("Minishell> ");
		if (if_exit(input) == 1)
			break ;
		if (input)
		{
			// input = "<<infile grep je >outfile";
			parsing(input, env);
			add_history(input);
		}
		free(input);
	}
	free(input);
	rl_clear_history();
}
