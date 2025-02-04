/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/03 11:39:01 by rbaticle         ###   ########.fr       */
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

int show_tocken(t_tkn_lst *tmp)
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
	t_commande *cmd;

	(void) argv;
	if (argc > 1)
		return (1);
	data = init_data(NULL, env);
	while (1)
	{
		// input = ft_strdup("> >>");
		input = readline("Minishell> ");
		if (input)
		{
			data.line = input;
			if (!ft_strcmp(input, "exit"))
				break ;
			get_tokens(&data);
			if (data.lst == NULL)
				exit(1);
			cmd = creator(data.lst, data.env);
			if (cmd)
			{
				// ft_printf("INFILE: %d, \n", cmd->infile);
				// write(cmd->infile, "Succhiamelo", 10);
				write(cmd->outfile, "Vaffanculo", 10);
				if (cmd->infile > 2)
					close(cmd->infile);
				if (cmd->outfile > 2)
					close(cmd->outfile);
				free(cmd);
			}
			printf("------------------------------------------\n");
			if (input)
				add_history(data.line);
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
