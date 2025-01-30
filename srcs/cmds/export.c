#include "../../includes/minishell.h"

int ft_export(char *cmd, t_env *env)
{
    t_env *temp;
    char *name;
    int i;

    i = 0;
    while (cmd[i] != '=')
        i++;
    name = ft_substr(cmd, 0, i);
    if (!name)
        return (-2);
    while (env)
    {
        temp = env;
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
    temp->next = init_env(cmd);
    if (!temp->next)
        return (free(name), -2);
    return (free(name), 1);
}
void del_node_env(t_env *node)
{
    free(node->content);
    free(node);
}
int ft_unset(char *cmd, t_env *env)
{
    t_env *temp;

    if (ft_strncmp(cmd, env->content, ft_strlen(cmd)) == 0 && env->content[ft_strlen(cmd)] == '=')
    {
        temp = env->next;
        del_node_env(env);
        env = temp;
        return (1);
    }
    while (env)
    {
        if (ft_strncmp(cmd, env->content, ft_strlen(cmd)) == 0 && env->content[ft_strlen(cmd)] == '=')
        {
            temp->next = env->next;
            del_node_env(env);
            return (1);
        }
        temp = env;
        env = env->next;
    }
    return (1);
}