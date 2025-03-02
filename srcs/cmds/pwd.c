/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:35:52 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/23 12:49:16 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		if (errno == EACCES)
			ft_printf("pwd: error retrieving current directory: getcwd: cannot\
access parent directories: No such file or directory\n");
		return (1);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
