#include "../../includes/minishell.h"

int ft_env(t_env *node)
{
    while (node)
    {
        ft_printf("%s\n", node->content);
        node = node->next;
    }
    return (1);
}