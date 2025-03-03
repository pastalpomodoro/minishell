/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/03 13:30:43 by rbaticle         ###   ########.fr       */
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
	// t_tkn_lst	*lst;
	int i = 0;

	(void) argv;
	if (argc > 1)
		return (1);
	init_signal();
	data = init_data(NULL, env);
	while (1)
	{
		if (i == 0)
			// input = ft_strdup("(echo salut && echo ciao)");
		input = readline("Minishell> ");
		add_history(input);
		data.line = input;
		if (input == NULL || !ft_strncmp(input, "exit", 4))
			ft_exit("0", &data);
		get_tokens(&data);
		if (data.lst == NULL)
			exit(1);
		lst = data.lst;
		while (lst)
		{
			printf("TOKEN:$\nTYPE: %d$\nVALUE: %s$\n$\n", lst->token,
				lst->value);
			lst = lst->next;
		}
		cmd = creator(data.lst, data.env);
		if (cmd)
		{
			add_history(input);
			data.line = input;
			if (!ft_strncmp(input, "exit", 4))
				break;
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
			// cmd = creator(data.lst, data.env);
			// if (!cmd)
			// 	break ;
			and_or_execution(NULL, data.lst, data.env, env);
			// printf("\n");
			// int i = -1;
			// while (i++, env[i])
			// {
			// 	if (ft_strncmp(env[i], "SAL=", 4) == 0)
			// 		printf("%s\n", env[i]);	
			// }
			// free_cmd(&cmd);
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
