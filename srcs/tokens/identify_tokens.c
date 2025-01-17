/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:29:03 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 13:35:37 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	identify_cmd_type(char *line)
{
	if (ft_strncmp(line, "history", 7) == 0)
		return (T_HISTORY);
	if (ft_strncmp(line, "export", 6) == 0)
		return (T_EXPORT);
	if (ft_strncmp(line, "unset", 5) == 0)
		return (T_UNSET);
	if (ft_strncmp(line, "exit", 4) == 0)
		return (T_EXIT);
	if (ft_strncmp(line, "echo", 4) == 0)
		return (T_ECHO);
	if (ft_strncmp(line, "pwd", 3) == 0)
		return (T_PWD);
	if (ft_strncmp(line, "env", 3) == 0)
		return (T_ENV);
	if (ft_strncmp(line, "cd", 2) == 0)
		return (T_CD);
	if (ft_strncmp(line, "$?", 2) == 0)
		return (T_LAST_RETURN);
	return (ERROR);
}

t_token	identify_type(char *line)
{
	t_token	token;

	token = identify_cmd_type(line);
	if (token != ERROR)
		return (token);
	if (ft_strncmp(line, "&&", 2) == 0)
		return (T_AND);
	if (ft_strncmp(line, "||", 2) == 0)
		return (T_OR);
	if (ft_strncmp(line, ">>", 2) == 0)
		return (T_DGREAT);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (T_DLESS);
	if (ft_strncmp(line, "|", 1) == 0)
		return (T_PIPE);
	if (ft_strncmp(line, "(", 1) == 0)
		return (T_O_PAR);
	if (ft_strncmp(line, ")", 1) == 0)
		return (T_C_PAR);
	if (ft_strncmp(line, ">", 1) == 0)
		return (T_GREAT);
	if (ft_strncmp(line, "<", 1) == 0)
		return (T_LESS);
	return (ERROR);
}
