#include "../../includes/minishell.h"

int adding(t_tkn_lst **lst, char *input, int i, char c)
{
    int start;
    t_tkn_lst *node;

    i+=2;
    while (is_space(input[i], "\t\n\v\f\r ") == 0 && input[i])
        i++;
    start = i;
    while (is_space(input[i], "\t\n\v\f\r ") && input[i] != c && input[i])
        i++;
    node = my_new_node(ft_substr(input, start, i - start));
    if (!node)
        return (free_branche(*lst), 0);
    node->token = T_DLESS;
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
        if (input[i] == c && input[i + 1] == c)
        {
            i = adding(&lst, input, i, c);
            if (i == 0)
            {
                lst = my_new_node(NULL);
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

char *find_last_redir(char *input, char c)
{
    int i;
    int save;

    i = 0;
    save = ft_strlen(input);
    while (input[i])
    {
        if (input[i] == c)
        {
            i++;
            save = i;
        }
        i++;
    }
    i = save;
    while (input[i] && is_space(input[i], "<\t\n\v\f\r ") == 0)
        i++;
    save = i;
    while (is_space(input[i], "\t\n\v\f\r ") && input[i])
        i++;
    ft_printf("save: %d, i: %d\n", save, i);
    return(ft_substr(input, save, i - save));
}
