#include"../../includes/minishell.h"

// int find(char *input, char c)
// {
//     int i;

//     while (input[i])
//     {
//         if (input[i] == c)
//         {

//         }
//     }
// }
//<<salut <<salut <salut

char *take_cmd(char *input)
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
            while (input[i] && input[i] != '>' && input[i] != '<' )
                i++;
            cmd = ft_substr(input, start, i - start);
            if (!cmd)
                return (perror(ERR_MALLOC), NULL);
            return (cmd);
        }
    }
    return (NULL);
}

int parsing(char *input)
{
    if (take_cmd(input))
    {
        ft_printf("%s\n", take_cmd(input));
        return (1);
    }
}