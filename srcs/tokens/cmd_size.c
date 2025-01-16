/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:59:38 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/16 15:29:45 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_quote_size(char *line)
{
	int	size;

	size = 1;
	if (*line == '"')
	{
		line++;
		while (*line && *line != '"')
		{
			line++;
			size++;
		}
		size++;
	}
	if (*line == '\'')
	{
		line++;
		while (*line && *line != '\'')
		{
			line++;
			size++;
		}
		size++;
	}
	return (size);
}

static int	get_echo_size(char *line, t_token type)
{
	int		size;
	int		i;
	char	**split;

	split = ft_split(line, ' ');
	if (ft_strcmp(split[++i], "-n"))
	{
		i++;
		size = 8;
	}
	else
		size = 5;
	line += size;
	while (*line == ' ')
		line++;
	if (*line == '"' || *line == '\'')
		size += get_quote_size(line);
	else
		size += ft_strlen(split[i]);
	free_double_tab(split);
	return (size);
}

static int	get_cd_size(char *line, t_token type)
{
	int		size;
	int		i;

	size = 3;
	line += size;
	while (*line == ' ')
		line++;
	if (*line == '"')
	return (size);
}

int	get_cmd_size(char *line, t_token type)
{
	int	size;

	size = 0;
	if (type == T_CMD)
	{
		if (ft_strncmp(line, "echo", 4))
			size = get_echo_size(line, type);
		if (ft_strncmp(line, "pwd", 3))
			size = 3;
		if (ft_strncmp(line, "cd", 2))
			size = get_cd_size(line, type);
		if (size > ft_strlen(line))
			return (0);
	}
	return (0);
}
