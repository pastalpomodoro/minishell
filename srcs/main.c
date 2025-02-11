/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/11 16:33:01 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	init_data(char *line, char **env)
{
	t_data	data;

	data.line = line;
	data.lst = NULL;
	data.env = env_creator(env);
	return (data);
}

int	show_token(t_tkn_lst *tmp)
{
	while (tmp)
	{
		printf("TOKEN:$\nTYPE: %d$\nVALUE: %s$\n$\n", tmp->token,
			tmp->value);
		tmp = tmp->next;
	}
	return (1);
}


int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_data		data;
	int i = 0;

	(void) argv;
	if (argc > 1)
		return (1);
	data = init_data(NULL, env);
	while (1)
	{
		if (i == 0)
			// input = ft_strdup("echo je suis une licorne || echo Error");
		input = readline("Minishell> ");
		if (input)
		{
			add_history(input);
			data.line = input;
			if (!ft_strncmp(input, "exit", 4))
				break;
				// ft_exit(ft_split(data.line, ' ')[1], &data);
			get_tokens(&data);
			if (data.lst == NULL)
				exit(1);
			// lst = data.lst;
			// while (lst)
			// {
			// 	printf("TOKEN:$\nTYPE: %d$\nVALUE: %s$\n$\n", lst->token,
			// 		lst->value);
			// 	lst = lst->next;
			// }
			exec_and_or(&data.env, data.lst, env);
			if (data.lst)
				tkn_lst_clear(&data.lst);
			free(data.line);
		}
	}
	free_env(data.env);
	if (data.line)
		free(data.line);
	rl_clear_history();
}
//bash --posix
