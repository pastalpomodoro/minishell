#include "../includes/minishell.h"

void pipe_split(char *input, char **env)
{
    char **lines;
    int i;
    int size;
    t_node **cmds;
    // t_tkn_lst *temp;

    i = -1;
    size = 0;
    lines = ft_split(input, '|');
    if (!lines)
        return ;
    while (lines[size])
        size++;
    cmds = malloc(sizeof(t_node *) * size);
    if (!cmds)
        return ;
    while (i++, lines[i])
        cmds[i] = lst_creator(input, env);
    // temp = cmds[0]->left;
    // while (temp)
    // {
    //     ft_printf("%s\n", temp->value);
    //     temp = temp->next;
    // }
    // temp = cmds[0]->left;
    // free_prince(cmds[0]);
    // free_branche(temp);
    free_double_tab(lines);
    free(cmds);
    // ft_printf("\n");
}