#include "includes/minishell.h"
#include <string.h>
int main()
{
    int fd = open("salut", O_RDONLY);
    int fd1 = open("ciao", O_RDONLY);
    printf("%d\n%d", fd, fd1);
}