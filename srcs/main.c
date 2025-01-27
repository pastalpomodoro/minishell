/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:01 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 11:20:55 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_exit(char *input)
{
	char	*exit;
	int		i;

	exit = "exit";
	i = 0;
	while (input[i])
	{
		if (exit[i] != input[i])
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **envi)
{
	// char	*input;
	t_env	*env;
	char *var;

	if (ac < 1)
		return (0);
	(void)av;
	env = env_creator(envi);
	var = get_path("grep", env);
	//salut salut salut salut
	ft_printf("PATH: %s, SIZE: %d\n", var, ft_strlen(var));
	free_env(env);
	free(var);
	// while (1)
	// {
	// 	input = readline("Minishell> ");
	// 	if (if_exit(input) == 1)
	// 		break ;
	// 	if (input)
	// 	{
	// 		// input = "<<infile grep je >outfile";
	// 		// chepas(input);
	// 		add_history(input);
	// 	}
	// 	free(input);
	// }
	// free_env(env);
	// free(input);
	// rl_clear_history();
}
//redir
//<<"$FILE"->$FILE
//<<'$FILE'->$FILE

//<'$FILE'->$FILE
//<"$FILE"->valeur de FILE

//>'$FILE'->$FILE
//>"$FILE"->file
//>>'$FILE'->$FILE
//>>"$FILE"->file

//comment ca marche?
//redirection et apres prendre tout les literal ou double cote comment non du file
//cmd et apres prendre tout les literal ou double cote comme utils de la commande