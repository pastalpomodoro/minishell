/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/20 12:13:55 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_value;

t_data	init_data(char *line, char **env)
{
	t_data	data;

	data.and_or = true;
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
	t_data		data;

	(void) argv;
	if (argc > 1)
		return (1);
	data = init_data(NULL, env);
	while (1)
	{
		init_signal();
		data.line = readline("Minishell> ");
		add_history(data.line);
		if (data.line == NULL)
			ft_exit(g_error_value, &data, NULL);
		and_or_exec(NULL, &data, env, 0);
	}
	free_env(data.env);
	if (data.line)
		free(data.line);
	rl_clear_history();
}
