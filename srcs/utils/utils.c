/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:35:47 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/03 13:31:15 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fonction qui free un double tableau
//attention le double tableau doit toujours finir par NULL
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

bool	ft_isspace(char c)
{
	return ((c == ' ') || (c >= 9 && c <= 13));
}

char	*ft_strjoin_char(char *s1, char ch)
{
	char	*str;
	size_t	i;

	if (ch)
		str = malloc(ft_strlen(s1) + 2);
	else
		str = malloc(ft_strlen(s1) + 1);
	if (!str)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	i = -1;
	if (s1)
	{
		while (s1[++i])
			str[i] = s1[i];
	}
	if (ch)
		str[ft_strlen(s1)] = ch;
	str[ft_strlen(s1) + 1] = '\0';
	if (s1)
		free(s1);
	return (str);
}

//return NULL si probleme de malloc
//return malloc(1) s'il ne trouve pas le path

char	*get_path(char *c, t_env *env, t_commande **lst_cmd)
{
	char	**all_path;
	char	*cmd;
	char	*path;
	int		i;

	i = -1;
	if (!ft_strncmp(c, "/", 1) || !ft_strncmp(c, "./", 2))
	{
		if (access(c, F_OK) != 0)
			return ((*lst_cmd)->exit_code = 127, ft_strdup(""));
		if (access(c, F_OK) != 0)
			return ((*lst_cmd)->exit_code = 126, ft_strdup(""));
		else
			return ((*lst_cmd)->exit_code = 0, ft_strdup(c));
	}
	if (!env)
		return (ft_strdup(""));
	while (env && (ft_strncmp("PATH", env->content, 4) != 0 || env->content[4] != '='))
		env = env->next;
	if (!env)
		return ((*lst_cmd)->exit_code = 127, ft_strdup(""));
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
		if (access(path, F_OK) != 0)
			(*lst_cmd)->exit_code = 127;
		else if (access(path, X_OK) != 0)
			(*lst_cmd)->exit_code = 126;
		else
			return ((*lst_cmd)->exit_code = 0, free_double_tab(all_path), free(cmd), path);
		free(path);
	}
	return (free_double_tab(all_path), free(cmd), ft_strdup(""));
}
