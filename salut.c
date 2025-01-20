#include "includes/minishell.h"
#include <string.h>
int main()
{
    char *dst;

    dst = strlcat(dst, "salut", 5);
    printf("%s\n", dst);
}