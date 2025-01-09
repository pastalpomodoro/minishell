#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct commande
{
    char *infile;
    char *outfile;
    char *cmd;
    char *util;
    
};


# include"libft/libft.h"
# include"printf/ft_printf.h"
# include<stdio.h>
# include<stdlib.h>
# include<readline/readline.h>
# include<readline/history.h>

/***************************/
/********   UTILS   ********/
/***************************/
void    free_double_tab(char **tab);

/*****************************/
/********   PARSING   ********/
/*****************************/
int picking(char *input);
#endif