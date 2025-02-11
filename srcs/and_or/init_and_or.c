#include "../../includes/minishell.h"


void free_node_and_or(t_and_or *node)
{
    free(node);
}

t_and_or *init_and_or()
{
    t_and_or *and_or;

    and_or = malloc(sizeof(t_and_or));
    if (!and_or)
        return (NULL);
    and_or->cmd = NULL;
    and_or->next = NULL;
    return (and_or);
}