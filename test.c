
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

void chepas(int i)
{
    int pid;
    if (i > 0)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("PID son: %d\n", pid);
            chepas(i - 1);
        }
        else
            printf("PID dad: %d\n", pid);
    }
}

int main()
{
    chepas(5);
}