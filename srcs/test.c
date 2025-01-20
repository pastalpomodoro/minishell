#include"../includes/minishell.h"

void gg(char *input)
{
    int i;
    char c;
    char C;

    c = '\'';
    C = "\"";
    while (input[i])
    {
        if (input[i] == c)
        {
            while (input[i] && input[i] != c)
                i++;
        }
    }
}