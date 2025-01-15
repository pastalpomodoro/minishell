#include"../../includes/minishell.h"

t_tkn_lst  *my_new_node(char *val)
{
    t_tkn_lst *new;

    new = malloc(sizeof(t_tkn_lst));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->prev = NULL;
    new->value = val;
    return (new);
}

void my_node_addfront(t_tkn_lst **node, t_tkn_lst *new)
{
    if (*node == NULL)
        *node = new;
    else
    {
        new->next = *node;
        *node = new;
    }
}
void free_branche(t_tkn_lst *node)
{
    t_tkn_lst *temp;

    while (node)
    {
        temp = node->next;
        if (node->value)
            free(node->value);
        free(node);
        node = temp;
    }
}
t_node *init_prince(void)
{
    t_node *prince;

    prince = malloc(sizeof(t_node));
    if (!prince)
        return (NULL);
    prince->cmd = NULL;
    prince->left = NULL;
    prince->next = NULL;
    prince->path = NULL;
    prince->right = NULL;
    return (prince);
}