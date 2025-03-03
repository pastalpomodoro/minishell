#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *s = malloc(5);
    int i = 0;
    while (i < 5)
    {
        s[i] = '1';
        i++;
    }
    free(s);
}