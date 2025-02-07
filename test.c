#include <unistd.h>
# include <stdio.h>

int main()
{
    int pipe_fd[2];

    pipe(pipe_fd);
    printf("before: %d, %d\n", pipe_fd[0], pipe_fd[1]);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    printf("before: %d, %d", pipe_fd[0], pipe_fd[1]);
}