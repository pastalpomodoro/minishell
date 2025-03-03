/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/03 14:31:51 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_value;

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
	t_commande	*cmd;

	(void) argv;
	if (argc > 1)
		return (1);
	init_signal();
	data = init_data(NULL, env);
	while (1)
	{
		input = readline("Minishell> ");
		add_history(input);
		data.line = input;
		if (input == NULL || !ft_strncmp(input, "exit", 4))
			ft_exit("0", &data);
		cmd = creator(&data.lst, data.env);
		if (cmd)
		{
			get_tokens(&data);
			if (data.lst == NULL)
				(free_cmd(&cmd), ft_exit(NULL, &data));
			and_or_execution(NULL, data.lst, data.env, env);
			tkn_lst_clear(&data.lst);
			free_cmd(&cmd);
		}
		free(data.line);
	}
	free_env(data.env);
	if (data.line)
		free(data.line);
	rl_clear_history();
}
//bash --posix
