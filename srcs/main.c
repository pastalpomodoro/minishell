/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/14 14:16:23 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("Minishell> ");
		if (input)
		{
			if (picking(input))
				ft_putstr_fd("Error\n", STDERR_FILENO);
			add_history(input);
		}
		if (!ft_strcmp(input, "exit"))
			break ;
		free(input);
	}
	free(input);
	rl_clear_history();
}
