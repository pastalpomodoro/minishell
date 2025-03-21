/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:49:37 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/18 14:00:40 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//return NULL si probleme de malloc
//return malloc(1) s'il ne trouve pas le path
static int	check_dir(char *value)
{
	int	i;

	i = 0;
	if (!ft_strncmp(value, "./", 2))
		i++;
	while (value[i])
	{
		if (value[i] == '/' && ft_strlen(&value[i]) > 3 && value[i + 3] == '/')
			i += 2;
		else if (value[i] == '/' && ft_strlen(&value[i]) > 3
			&& value[i + 3] != '/')
			return (0);
		i++;
	}
	printf("minishell: %s: Is a directory\n", value);
	return (1);
}

static char	*check_point_slash(char *c, t_commande **lst_cmd)
{
	if (check_dir(c))
		return ((*lst_cmd)->exit_code = 126, NULL);
	if (access(c, F_OK) != 0)
		return ((*lst_cmd)->exit_code = 127, printf(FILE_ERROR, c), NULL);
	if (access(c, X_OK) != 0)
		return ((*lst_cmd)->exit_code = 126, printf(PERM_ERROR, c), NULL);
	else
		return ((*lst_cmd)->exit_code = 0, ft_strdup(c));
}

static char	*join_path(char **all_path, char *cmd, t_commande **lst_cmd)
{
	char	*path;
	int		i;

	i = -1;
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
			return ((*lst_cmd)->exit_code = 0, free_double_tab(all_path),
				free(cmd), path);
		free(path);
	}
	return (free_double_tab(all_path), free(cmd), ft_strdup(""));
}

char	*get_path(char *c, t_env *env, t_commande **lst_cmd)
{
	char	**all_path;
	char	*cmd;

	if (!ft_strncmp(c, "/", 1) || !ft_strncmp(c, "./", 2))
		return (check_point_slash(c, lst_cmd));
	if (!env)
		return (ft_strdup(""));
	while (env && (ft_strncmp("PATH", env->content, 4) != 0
			|| env->content[4] != '='))
		env = env->next;
	if (!env)
		return ((*lst_cmd)->exit_code = 127, ft_strdup(""));
	all_path = ft_split(&env->content[5], ':');
	if (!all_path)
		return (NULL);
	cmd = ft_strjoin("/", c);
	if (!cmd)
		return (free_double_tab(all_path), NULL);
	return (join_path(all_path, cmd, lst_cmd));
}
