#include"../../minishell.h"

//fonction qui va permettre de prendre tout ce qui est affiche sur le minishell et mattre chaque mot dans un doubletableau
//exemple:  grep je > outfile.txt
//          [[grep], [je], [>], [outfile.txt], NULL]

int picking(char *input)
{
    char **all;
    int i;

    i = 0;
    all = ft_split(input, ' ');
    if (!all)
        exit(0);
    while (all[i])
    {
        i++;
    }
    free_double_tab(all);
    return (1);
}