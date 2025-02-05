
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

int main(int ac, char **av, char **env)
{
    (void)av;
    ac = 0;
    // int pid;
    char *cmd[] ={"grep", "je", NULL};
    char *path = "/usr/bin/grep";
    // int fd_in = open("infile", O_RDONLY);
    // int fd_out = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
    // pid = fork();
    // if (pid == 0)
    // {
        // dup2(0, STDIN_FILENO);
        // dup2(fd_out, STDOUT_FILENO);
        // close(fd_in);
        // close(fd_out);
    int i = 0;
    while(1)
    {
        i++;
    }
    execve(path, cmd, env);
    // }
}