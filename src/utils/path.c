#include"../../includes/minishell.h"
int     size_double_tab(char **tab)
{
        int     i;

        i = 0;
        while (tab[i] != NULL)
                i++;
        return (i);
}

void    free_double_tab(char **tab)
{
        int     i;

        i = size_double_tab(tab);
        while (i > 0)
                free(tab[--i]);
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
		{
			perror("Erreur dan le ft_strjoin de path dans get_path");
			return (NULL);
		}
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
	return (perror("No path found"), NULL);
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