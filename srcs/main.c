/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/04 16:53:16 by rbaticle         ###   ########.fr       */
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
	t_commande	*cmd;

	(void) argv;
	if (argc > 1)
		return (1);
	data = init_data(NULL, env);
	while (1)
	{
		// input = ft_strdup("grep je fais caca");
		input = readline("Minishell> ");
		if (input)
		{
			add_history(input);
			add_history(input);
			data.line = input;
			if (!ft_strcmp(input, "exit"))
				break ;
			// if (!ft_strncmp(input, "cd", 2))
			// 	ft_cd(ft_split(input, ' ')[1], data.env);
			// if (!ft_strcmp(input, "pwd"))
			// 	ft_pwd();
			get_tokens(&data);
			if (data.lst == NULL)
				exit(1);
			cmd = creator(data.lst, data.env);
			if (cmd)
			{
				int i = 0;
				while (cmd->cmd[i])
				{
					ft_printf("CMD: %s\n", cmd->cmd[i]);
					i++;
				}
				ft_printf("PATH: %s, INFILE: %d, OUTFILE: %d\n", cmd->path, cmd->infile, cmd->outfile);
				free_cmd_node(&cmd);
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
//bash --posix