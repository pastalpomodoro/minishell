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

//fonction qui free un double tableau attentio le double tableau doit
// toutjours finire par NULL
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

char	*return_path(char *cmd, char **allpath)
{
	int		i;
	char	*path;

	i = -1;
	while (i++, allpath[i])
	{
		path = ft_strjoin(allpath[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_double_tab(allpath);
			free(cmd);
			return (path);
		}
		free(path);
	}
	free(cmd);
	free_double_tab(allpath);
	return (NULL);
}

//fonction pour trouver le chemin d une commande grace au env
char	*get_path(char *c, char **env)
{
	int		i;
	char	**allpath;
	char	*cmd;

	i = -1;
	while (i++, env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
	}
	allpath = ft_split(env[i], ':');
	if (!allpath)
	{
		perror("Erreur dans le ft_split de allpath dans get_peth");
		return (NULL);
	}
	cmd = ft_strjoin("/", c);
	if (!cmd)
		return (perror("Erreur dans le strjoin de cmd dans +"), NULL);
	return (return_path(cmd, allpath));
}
