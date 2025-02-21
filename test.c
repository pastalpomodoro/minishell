#include <stdio.h>

int ff(int x)
{
    if (x == 5)
        return (x);
    ff(x+1);
}
int main()
{
    int x = 0;
    x = ff(x);
    printf("%d\n", x);
}