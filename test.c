#include <unistd.h>
# include <stdio.h>
# include <string.h>

int main(int ac, char **av, char **env)
{
    ac = 0;
    (void)av;
    int i = 0;
    while (env[i])
        i++;
    printf("%d\n", i);
}