/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/29 14:27:36 by rbaticle         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_data		data;
	t_tkn_lst	*tmp;

	data = init_data(NULL, env);
	input = ft_strdup(argv[argc - 1]);
	if (input)
	{
		data.line = input;
		data.lst = get_tokens(&data);
		if (data.lst == NULL)
			exit(1);
		tmp = data.lst;
		while (data.lst)
		{
			printf("TOKEN:\nTYPE: %d\nVALUE: %s\n\n", data.lst->token,
				data.lst->value);
			data.lst = data.lst->next;
		}
		if (input)
			add_history(input);
		if (tmp)
			tkn_lst_clear(&tmp);
	}
	if (input)
		free(input);
	rl_clear_history();
}
