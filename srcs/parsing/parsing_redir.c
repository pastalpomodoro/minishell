#include "../../includes/minishell.h"

int adding(t_tkn_lst **lst, char *input, int i, char c)
{
    int start;
    int token;
    t_tkn_lst *node;

    token = 0;
    if (input[i] == c && input[i + 1] == c)
    {
        i++;
        token = 1;
    }
    i++;
    while (is_space(input[i], "\t\n\v\f\r ") == 0 && input[i])
        i++;
    start = i;
    while (is_space(input[i], "\t\n\v\f\r ") && input[i] != c && input[i])
        i++;
    node = my_new_node(ft_substr(input, start, i - start));
    if (!node)
        return (free_branche(*lst), 0);
    if (token == 1)
        node->token = T_DLESS;
    else
        node->token = T_LESS;
    my_node_addfront_branche(lst, node);
    return (i);
}
//me rappeler que quand il y a << il faut l executer dans tout les cas meme sy il y a une commande 
//me rapperler de free lst une foi que tout est finis ou sy il y a un probleme
t_tkn_lst *fill_branche(char *input, char c)
{
    int i;
    t_tkn_lst *lst;

    lst = NULL;
    i = 0;
    while (input[i])
    {
        if (input[i] == c)
        {
            i = adding(&lst, input, i, c);
            if (i == 0)
            {
                free_branche(lst);
                break;
            }
        }
        else
            i++;
    }
    if (!lst)
        return (lst);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

