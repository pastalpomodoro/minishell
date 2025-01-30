#include "includes/minishell.h"
#include <string.h>
int main()
{
    int save;
    int fd = open("infile", O_WRONLY | O_CREAT | O_TRUNC);
    save = dup(STDOUT_FILENO);

    dup2(fd, STDOUT_FILENO);
    close(fd);

    write(STDOUT_FILENO, "SALUT", 5);

    dup2(save, STDOUT_FILENO);

    write(STDOUT_FILENO, "CIAOO", 5);

    close(save);
}