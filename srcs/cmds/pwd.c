#include "../../includes/minishell.h"

//je n ai pas gere le cas ou je fais cd ../
int ad_pwd_to_env(char *str, t_env *env)
{
    char *path;

    while (env)
    {
        if (ft_strncmp("PWD", env->content, 3) && env->content[3] == '=')
        {
            path = variadic_strjoin(3, env->content, "/", str);
            if (!path)
                return (-2);
            free(env->content);
            env->content = path;
            return (1);
        }
        env = env->next;
    }
    retunr (1);
}