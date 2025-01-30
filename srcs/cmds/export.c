#include "../../includes/minishell.h"

int ft_export(char *cmd, t_env *env)
{
    char *name;
    int i;

    i = 0;
    while (cmd[i] != '=')
        i++;
    name = ft_substr(cmd, 0, i);
    if (!name)
        return (-2);
    while (env->next)
    {
        if (ft_strncmp(name, env->content, i) == 0 && env->content[i] == '=')
        {
            free(env->content);
            env->content = ft_strdup(cmd);
            if (!env->content)
                return (free(name), -2);
            return (free(name), 1);
        }
        env = env->next;
    }
    if (i ==-1)
        ft_printf(env->content);
    return (1);
}
void del_node_env(t_env *node)
{
    free(node->content);
    free(node);
}
// int ft_unset(char *cmd, t_env *env)
// {
//     t_env *temp;

//     while (env)
//     {

//     }
// }