#include"../../minishell.h"

//fonction qui free un double tableau attentio le double tableau doit toutjour finire par NULL
void    free_double_tab(char **tab)
{
    int size;

    size = 0;
    while (tab[size])
        size++;
    while (size >= 0)
        free(tab[size--]);
    free(tab);
}
