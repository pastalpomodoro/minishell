#include "../../includes/minishell.h"

// static int if_mine(t_tkn_lst *node)
// {
//     if (!ft_strcmp("echo", node->value) || !ft_strcmp("cd", node->value)
//         || !ft_strcmp("env", node->value) || !ft_strcmp("export", node->value)
//         || !ft_strcmp("pwd", node->value) || !ft_strcmp("unset", node->value))

// }
int size_tab(t_tkn_lst *node)
{
    int size;

    size = 0;
    while (node && node->token == T_LITERAL)
    {
        node = node->next;
        size++;
    }
    return (size);
}

int cmd_creator(t_tkn_lst *node, t_commande **cmd, t_env *env)
{
    char *path;
    char **utils;
    int i;

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
    }
    return ((*cmd)->cmd = utils, 1);
}
