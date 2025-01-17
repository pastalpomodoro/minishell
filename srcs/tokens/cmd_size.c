/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:59:38 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 13:39:22 by rbaticle         ###   ########.fr       */
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

static int	get_echo_size(char *line)
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

static int	get_cd_size(char *line)
{
	int		size;
	int		i;
	char	**split;

	split = ft_split(line, ' ');
	size = 3;
	line += size;
	while (*line == ' ')
		line++;
	if (*line == '"' || *line == '\'')
		size += get_quote_size(line);
	else
		size += ft_strlen(split[1]);
	free_double_tab(split);
	return (size);
}

static int	get_export_size(char *line)
{
	int	size;

	size = 7;
	line += size;
	while (*line == ' ')
		line++;
	if (*line == '$')
	{
		line++;
		size++;
	}
	// TODO: get export size
	return (size);
}

int	get_cmd_size(char *line, t_token type)
{
	int	size;

	size = 0;
	if (type == T_ECHO)
		size = get_echo_size(line);
	if (type == T_PWD)
		size = 3;
	if (type == T_CD)
		size = get_cd_size(line);
	if (type == T_EXPORT)
		size = get_export_size(line);
	if (size > ft_strlen(line))
		return (0);
	return (size);
}
