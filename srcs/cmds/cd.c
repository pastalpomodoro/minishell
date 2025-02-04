/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:00:26 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/04 15:20:02 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_env(t_env *env)
{
	char	*val;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return (1);
	val = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (val == NULL)
		return (1);
	ft_export(val, env);
	free(val);
	return (0);
}

static int	cd_friend(char *val, t_env *env)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	tmp = variadic_strjoin(3, pwd, "/", val);
	if (tmp == NULL)
		return (free(pwd), 1);
	if (chdir(tmp))
		return (ft_printf("minishell: cd: %s: No such file or directory",
				tmp), free(tmp), free(pwd), 1);
	free(tmp);
	free(pwd);
	if (change_env(env))
		return (1);
	return (0);
}

int	ft_cd(char *val, t_env *env)
{
	char	*tmp;
	char	*pwd;

	if (!ft_strncmp(val, "/", 1))
	{
		if (chdir(val))
			return (ft_printf("minishell: cd: %s: No such file or directory",
					val), 1);
		if (change_env(env))
			return (1);
	}
	else
	{
		if (cd_friend(val, env))
			return (1);
	}
	return (0);
}
