/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:32:24 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/27 10:03:36 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

static bool	wildcard_rec(char *file, char *word, int n, int m)
{
	int	i;

	if (m == 0)
		return (n == 0);
	if (n == 0)
	{
		i = -1;
		while (++i < m)
		{
			if (word[i] != '*')
				return (false);
		}
		return (true);
	}
	if (file[n - 1] == word[m - 1] || word[m - 1] == '?')
		return (wildcard_rec(file, word, n - 1, m - 1));
	if (word[m - 1] == '*')
	{
		return (wildcard_rec(file, word, n, m - 1)
			|| wildcard_rec(file, word, n - 1, m));
	}
	return (false);
}

static char	*add_files(DIR *dir)
{
	char			*res;
	struct dirent	*entry;

	res = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, ".") != 0
			&& ft_strcmp(entry->d_name, "..") != 0
			&& ft_strncmp(entry->d_name, ".", 1) != 0)
		{
			res = strjoin_space(res, entry->d_name);
			if (res == NULL)
				return (NULL);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (res);
}

static char	**get_files_cwd(void)
{
	char			*res;
	char			**split;
	char			cwd[1024];
	DIR				*dir;

	g_error_value = MALLOC_ERROR;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		dir = opendir(cwd);
		if (dir == NULL)
		{
			g_error_value = ERROR_CWD;
			return (NULL);
		}
		res = add_files(dir);
	}
	else
		return (NULL);
	split = ft_split(res, ' ');
	free(res);
	return (split);
}

static int	replace_wildcard(char *word, char **res)
{
	char	**files;
	char	*tmp;
	int		i;

	files = get_files_cwd();
	if (files == NULL)
		return (g_error_value);
	i = -1;
	while (files[++i])
	{
		if (wildcard_rec(files[i], word, ft_strlen(files[i]), ft_strlen(word)))
		{
			if (*res == NULL)
				*res = ft_strdup(files[i]);
			else
			{
				tmp = variadic_strjoin(3, *res, " ", files[i]);
				free(*res);
				*res = tmp;
			}
			if (*res == NULL)
				return (free_double_tab(files), MALLOC_ERROR);
		}
	}
	return (free_double_tab(files), 0);
}

char	*get_wildcard(char *line)
{
	char	*res;
	char	**words;
	int		i;

	res = NULL;
	words = ft_split(line, ' ');
	i = -1;
	while (words[++i])
	{
		if (ft_strchr(words[i], '*'))
		{
			if (replace_wildcard(words[i], &res))
				return (free_double_tab(words), NULL);
		}
		else
		{
			res = strjoin_space(res, words[i]);
			if (res == NULL)
			{
				g_error_value = MALLOC_ERROR;
				return (free_double_tab(words), NULL);
			}
		}
	}
	return (free_double_tab(words), res);
}
