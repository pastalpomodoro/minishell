#include"../minishell.h"

int if_exit(char *input)
{
    char *exit = "exit";
    int i = 0;
    while (input[i])
    {
        if (exit[i] != input[i])
            return (0);
        i++;
    }
    return (1);
}

int main()
{
    char *input;
    while (1)
    {
        input = readline("Minishell> ");
        if (input) 
        {
            // printf("You entered: %s\n", input);
            add_history(input);
        }
        if (if_exit(input) == 1)
            break;
        
        free(input);
    }
    free(input);
    // rl_clear_history();
}