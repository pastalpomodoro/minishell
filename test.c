# include <curses.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>

// int child(int pipe_fd[2], char *path, char *cmd[])
// {
//     dup2(pipe_fd[1], STDOUT_FILENO);
//     execve(path, cmd, NULL);
// }
// int main()
// {
//     char *cmd[] = {"cat", NULL};
//     int pipe_fd[2];
//     pipe(pipe_fd);
//     int pid = fork();
//     if (pid == 0)
//         child(pipe_fd, "/bin/cat", cmd);
//     close(pipe_fd[1]);
//     char *cmd2[] = {"ls", NULL};
//     int pid2 = fork();
//     if (pid2 == 0)
//     {
//         dup2(pipe_fd[0], STDIN_FILENO);
//         execve("/bin/ls", cmd2, NULL);
//     }
//     waitpid(pid, NULL, 0);
//     waitpid(pid2, NULL, 0);
// }
int main()
{
    while ()
}