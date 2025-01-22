/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:35:47 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 11:09:41 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

int	is_space(char c, char *space)
{
	while (*space)
	{
		if (c == *space)
			return (0);
		space++;
	}
	return (1);
}

// //fonction qui free un double tableau attentio le double tableau doit
// // toutjours finire par NULL
void	free_double_tab(char **tab)
{
	int	size;

	size = 0;
	while (tab[size])
		size++;
	while (size >= 0)
		free(tab[size--]);
	free(tab);
}

//return NULL sy probleme de malloc et return malloc(1) sy il ne trouve pas le path
char *get_path(char *c, t_env *env)
{
	char **all_path;
	char *cmd;
	char *path;
	int i;

	i = -1;
	while (ft_strncmp("PATH", env->content, 4) != 0 || env->content[4] != '=')
		env = env->next;
	all_path = ft_split(&env->content[5], ':');
	if (!all_path)
		return (NULL);
	cmd = ft_strjoin("/", c);
	if (!cmd)
		return (NULL);
	while (i++, all_path[i])
	{
		path = ft_strjoin(all_path[i], cmd);
		if (!path)
			return (free_double_tab(all_path), free(cmd), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free_double_tab(all_path), free(cmd), path);
		free(path);
	}
	free_double_tab(all_path);
	return(free(cmd), ft_strdup("")); 
}
