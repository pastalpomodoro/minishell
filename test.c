
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

char* chepas(char *input)
{
    int button;
    int i = 0;

    button = 0;
    while (input[i])
    {
        if (input[i] == '\'' && button == 0)
        {
            button = 2;
            i++;
        }
        else if (input[i] == '\'' && button == 2)   
        {
            button = 0;
            i++;
        }
        if (input[i] == '"' && button == 0)
            button = 1;
        else if (input[i] == '"' && button == 1)
            button = 0;
        if (input[i] == '$' && (button == 0 || button == 1))

        if (input[i] == ' ' && button == 0)
            break;
        i++;
    }
    char *word = malloc(i);
    i = 0;
    int f = 0;
    while (input[i])
    {
        if (input[i] == '\'' && button == 0)
        {
            button = 2;
            i++;
        }
        else if (input[i] == '\'' && button == 2)   
        {
            button = 0;
            i++;
        }
        if (input[i] == '"' && button == 0)
            button = 1;
        else if (input[i] == '"' && button == 1)
            button = 0;
        // if (input[i] == '$' && (button == 0 || button == 1))
        //     fcn(&word[f], &input[i])
        if (input[i] == ' ' && button == 0)
            break;
        word[f] = input[i];
        i++;
        f++;
    }
    return (word);
}

int main()
{
    printf("%s\n", chepas("'salut tu'va bien"));
}