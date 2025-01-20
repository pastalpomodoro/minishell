#include "../../includes/minishell.h"

char *get_next_word(char *line, char *trim)
{
    int i;
    int start;
    char *word;

    i = 0;
    while (is_space(line[i], trim) == 0 && line[i])
        i++;
    start = i;
    while (is_space(line[i], trim) && line[i])
        i++;
    word = ft_substr(line, start, i - start);
    if (!word)
        return (NULL);
    return (word);
}

int here_doc(int pipe_fd[2], char *limiter)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
            return (-2);
        if (ft_strcmp(line, limiter) == 0)
            break;
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    free(line);
    return (1);
}
int take_fd_double(char *input)
{
    char *limiter;
    int pipe_fd[2];

    limiter = get_next_word(&input[1], "\t\n\v\f\r ");
    if (!limiter)
        return (-2);
    ft_printf("FILE here_doc: %s\n", limiter, ft_strlen(limiter));
    if (ft_strlen(limiter) == 0)
    {
        ft_printf("minishell: syntax error near unexpected token `newline'\n");
        return (free(limiter), -1);
    }
    if (pipe(pipe_fd) == -1)
        return (free(limiter), -2);
    if (here_doc(pipe_fd, limiter) == -2)
        return (free(limiter), -2);
    free(limiter);
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}
int take_fd(char *input)
{
    char *file;
    int fd;

    file = get_next_word(input, "\t\n\v\f\r ");
    if (!file)
        return (-2);
    ft_printf("FILE: %s\n", file);
    if (ft_strlen(file) == 0)
    {
        ft_printf("minishell: syntax error near unexpected token `newline'\n");
        return (free(file), -1);
    }
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (ft_printf("minishell: %s: No such file or directory\n", file), free(file), -1);
    free(file);
    return (fd);
}
int find_infile(char *input)
{
    int i;
    int fd;

    fd = 0;
    i = -1;
    while (i++, input[i])
    {
        if (input[i] == '<' && input[i + 1] == '<')
        {
            if (fd > 0)
                close(fd);
            fd = take_fd_double(&input[++i]);
            if (fd < 0)
                return (fd);
        }
        else if (input[i] == '<')
        {
            if (fd > 0)
                close(fd);
            fd = take_fd(&input[i + 1]);
            if (fd < 0)
                return (fd);
        }
    }
    return (fd);
}
void chepas(char *input)
{
    int fd;
    
    fd = find_infile(input);
    if (fd == -2)
    {
        free(input);
        exit(0);
    }
    if (fd == -1)
        return ;
    close(fd);
} 