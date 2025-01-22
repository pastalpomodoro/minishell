/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/22 21:43:00 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char		*input;
	t_tkn_lst	*lst;
	t_tkn_lst	*tmp;

	while (1)
	{
		input = readline("Minishell> ");
		if (input)
		{
			lst = get_tokens(input);
			if (lst == NULL)
				exit(1);
			tmp = lst;
			while (lst)
			{
				printf("TOKEN:\nTYPE: %d\nVALUE: %s\n\n", lst->token,
					lst->value);
				lst = lst->next;
			}
			add_history(input);
			tkn_lst_clear(&tmp);
		}
		if (!ft_strcmp(input, "exit"))
			break ;
		free(input);
	}
	free(input);
	rl_clear_history();
}
