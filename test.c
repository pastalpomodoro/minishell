#include <unistd.h>
#include <fcntl.h>
int main()
{
    int pid;
    int pipe_fd[2];

    pid = fork();
    if (pid == 0)
    {
        pipe(pipe_fd);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
}