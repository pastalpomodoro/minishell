/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/06 14:36:25 by rbaticle         ###   ########.fr       */
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

void	show_cmds(t_commande *cmd)
{
	int	i;

	while (cmd)
	{
		if (cmd->path)
			ft_printf("PATH: %s\n", cmd->path);
		if (cmd->cmd)
		{
			i = -1;
			while (i++, cmd->cmd[i])
				ft_printf("CMD: %s\n", cmd->cmd[i]);
		}
		ft_printf("INFILE: %d\n", cmd->infile);
		// if (cmd->outfile)
		ft_printf("OUTFILE: %s, OUTFILE_TYPE: %d\n", cmd->outfile,
				cmd->outfile_type);
		ft_printf("EXIT_CODE: %d\n", cmd->exit_code);
		cmd = cmd->next;
		printf("------------------------------------------\n");
	}
}
int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_data		data;
	t_commande	*cmd;
	// t_tkn_lst	*lst;

	(void) argv;
	if (argc > 1)
		return (1);
	data = init_data(NULL, env);
	while (1)
	{
		// input = ft_strdup("echo salut");
		input = readline("Minishell> ");
		if (input)
		{
			add_history(input);
			data.line = input;
			if (!ft_strcmp(input, "exit"))
				break ;
			// if (!ft_strncmp(input, "cd", 2))
			// 	ft_cd(ft_split(input, ' ')[1], data.env);
			// if (!ft_strcmp(input, "pwd"))
			// 	ft_pwd();
			// if (!ft_strcmp(input, "env"))
			// 	ft_env(data.env);
			// if (!ft_strncmp(input, "export", 6))
			// 	ft_export(ft_split(input, ' ')[1], &data.env);
			// if (!ft_strncmp(input, "unset", 5))
			// 	ft_unset(ft_split(input, ' ')[1], &data.env);
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
			cmd = creator(data.lst, data.env);
			if (cmd)
			{
				show_cmds(cmd);
				exec_manage(cmd, &data.env, env);
				free_cmd(&cmd);
			}
			printf("------------------------------------------\n");
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
