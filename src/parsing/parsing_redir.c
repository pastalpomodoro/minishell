#include "../../minishell.h"
int skip_redir(char *input, int i)
{
    i++;
    while (is_space(input[i], "\t\n\v\f\r ") == 0 && input[i])
        i++;
    while (is_space(input[i], "\t\n\v\f\r ") && input[i])
        i++;
    return (i);
}
//fonction que sy le input est < infile grep CC > oufile 
//elle return un poiteur avec dedans grep CC ce poiteur faudra le free
//synon dans tout les cas elle return un poiteur avec dedans la commande que il faudra free
char *prepare_for_infile_and_outifle(char *input)
{
    int i;
    int start;
    char *cmd;

    i = 0;
    while (input[i])
    {
        if (input[i] == '>' || input[i] == '<')
            i = skip_redir(input, i);
        else if (is_space(input[i], "\t\n\v\f\r ") == 0)
            i++;
        else
        {
            start = i;
            while (input[i] && input[i] != '>' && input[i] != '<')
                i++;
            cmd = ft_substr(input, start, i - start);
            if (!cmd)
                return (perror(ERR_MALLOC), NULL);
            return (cmd);
        }
    }
    return (NULL);
}