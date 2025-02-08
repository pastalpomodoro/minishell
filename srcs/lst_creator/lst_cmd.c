#include "../../includes/minishell.h"

// static int if_mine(t_tkn_lst *node)
// {

// }
int	size_tab(t_tkn_lst *node)
{
	int	size;

	size = 0;
	while (node && node->token == T_LITERAL)
	{
		node = node->next;
		if (node && node->token == T_REDIRECT)
		{
			node = node->next;
			if (!node)
				break;
			node = node->next;
		}
		size++;
	}
	return (size);
}
int is_our_cmd(char *value)
{
    if (ft_strcmp("echo", value) || ft_strcmp("cd", value)
        || ft_strcmp("env", value) || ft_strcmp("export", value)
        || ft_strcmp("pwd", value) || ft_strcmp("unset", value) || ft_strcmp("exit", value))
		return (1);
}
int t_redirect(t_tkn_lst **node)
{
		if ((*node) && (*node)->token == T_REDIRECT)
		{
			(*node) = (*node)->next;
			if (!(*node))
				return (0);
			(*node) = (*node)->next;
		}
		return (1);
}

int	cmd_creator(t_tkn_lst *node, t_commande **cmd, t_env *env)
{
	char	*path;
	char	**utils;
	int		i;

	path = get_path(node->value, env);
	if (!path)
		return (-2);
	if (!ft_strlen(path))
		return ((*cmd)->exit_code = 127, ft_printf("%s: command not found\n", node->value), free(path), -1);
	(*cmd)->path = path;
	utils = malloc(sizeof(char *) * (size_tab(node) + 1));
	if (!utils)
		return (-2);
	i = 0;
	utils[i] = NULL;
	while (node && node->token == T_LITERAL)
	{
		utils[i] = ft_strdup(node->value);
		if (!utils[i])
			return (free_double_tab(utils), -2);
		i++;
		utils[i] = NULL;
		node = node->next;
		if (t_redirect(&node) == 0)
			break;
}
	return ((*cmd)->cmd = utils, 1);
}
