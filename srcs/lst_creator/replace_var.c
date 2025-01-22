#include "../../includes/minishell.h"

int take_size_of_var(t_env *env, char *str)
{
    int i;
    int start;
    char *var;

    i = 0;
    start = i;
    while (is_space(str[i], "\t\n\v\f\r $") && str[i])
        i++;
    var = ft_substr(str, start, i - start);
    if (!var)
        return (-1);
    while (env)
    {
        if (ft_strncmp(env->content, var, ft_strlen(var)) == 0 && env->content[ft_strlen(var)] == '=')
            break;
        env = env->next;
    }
    if (!env)
        return (free(var), 0);
    i = 0;
    while (env->content[ft_strlen(var) + 1 + i])
        i++;
    free(var);
    return (i);
}
int take_size(t_env *env, char *str)
{
    int i;
    int size;
    int t;

    i = 0;
    size = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            t = take_size_of_var(env, &str[++i]);
            if (t < 0)
                return (-1);
            size += t;
            while (is_space(str[i], "\t\n\v\f\r $") && str[i])
                i++;
        }
        else
        {
            i++;
            size++;
        }
    }
    return (size);
}

char *take_value(t_env *env, char *str)
{
    int i;
    int j;
    int start;
    char *var;

    i = 0;
    start = i;
    while (is_space(str[i], "\t\n\v\f\r $") && str[i])
        i++;
    var = ft_substr(str, start, i - start);
    if (!var)
        return (NULL);
    while (env)
    {
        if (ft_strncmp(env->content, var, ft_strlen(var)) == 0 && env->content[ft_strlen(var)] == '=')
            break;
        env = env->next;
    }
    if (!env)
        return (free(var), "\0");
    j = ft_strlen(var);
    return (free(var), &env->content[j+1]);
}

char *replace_var(t_env *env, char *str)
{
    char *line;
    char *new;
    int size;
    int i;
    int f;

    size = take_size(env, str);
    if (size < 0)
        return (NULL);
    line = malloc(sizeof(char) * size + 1);
    if (!line)
        return (NULL);
    i = 0;
    size = 0;
    while (str[i])
    {
        if (str[i] != '$')
            line[size++] = str[i++];
        if (str[i] == '$')
        {
            f = 0;
            new = take_value(env, &str[++i]);
            if (!new)
                return (NULL);
            while (new[f])
                line[size++] = new[f++];
            while (is_space(str[i], "\t\n\v\f\r $") && str[i])
                i++;
        }
    }
    line[size] = '\0';
    return (line);
}
