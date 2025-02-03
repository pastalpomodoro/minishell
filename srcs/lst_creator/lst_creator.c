#include "../../includes/minishell.h"

int hard_in(t_tkn_lst *node)
{
    char *line;
    int pipe_fd[2];

    if (ft_strlen(node->value) == 0 && node->next == NULL)
        return (ft_printf("minishell: syntax error near unexpected token `newline'\n"), -1);
    if (pipe(pipe_fd) == -1)
        return (-2);
    while (1)
    {
        line = readline("> ");
        if (ft_strcmp(line, node->value) == 0)
            break;
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    free(line);
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}

int easy_in(t_tkn_lst *node)
{
    int fd;
    t_tkn_lst *next;

    next = node->next; 
    fd = open(node->value, O_RDONLY);
    if (ft_strlen(node->value) == 0 && node->next == NULL)
        return (ft_printf("minishell: syntax error near unexpected token `newline'\n"), -1);
    if (ft_strlen(node->value) == 0)
        return (ft_printf("minishell: syntax error near unexpected token `%s'\n", next->value), -1);
    if (fd < 0)
        ft_printf("minishell: %s: No such file or directory\n", node->value);
    return (fd);
}
int out(t_tkn_lst *node, int type)
{
    int fd;
    t_tkn_lst *next;

    next = node->next; 
    if (ft_strlen(node->value) == 0 && node->next == NULL)
        return (ft_printf("minishell: syntax error near unexpected token `newline'\n"), -1);
    if (ft_strlen(node->value) == 0)
        return (ft_printf("minishell: syntax error near unexpected token `%s'", next->value), -1);
    if (type == 1)//>
        fd = open(node->value, O_WRONLY | O_CREAT | O_TRUNC);
    if (type == 2)//>>
        fd = open(node->value, O_WRONLY | O_CREAT | O_APPEND);
    if (fd < 0)
        ft_printf("bash: %s: Permission denied", node->value);
    return (fd);
}
int redirect(t_tkn_lst *node, t_commande **cmd)
{
    t_tkn_lst *next;
    int i;
    int fd;

    i = 0;
    next = node->next;
    if (i++, ft_strcmp(node->value, "<<") == 0)
        fd = hard_in(next);
    else if (i++, ft_strcmp(node->value, "<") == 0)
        fd = easy_in(next);
    else if (i++, ft_strcmp(node->value, ">") == 0)
        fd = out(next, 1);
    else if (i++, ft_strcmp(node->value, ">>") == 0)
        fd = out(next, 2);
    if (fd < 0)
        return (fd);
    if (i < 3)
        (*cmd)->infile = fd;
    else if (i > 2)
        (*cmd)->outfile = fd;    
    return (fd);
}
t_commande *cmd_init()
{
    t_commande *cmd;

    cmd = malloc(sizeof(t_commande));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    cmd->path = NULL;
    cmd->next = NULL;
    cmd->infile = 0;
    cmd->outfile = 1;
    return (cmd);
}

t_commande *creator(t_tkn_lst *node, t_env *env)
{
    t_commande *cmd;

    cmd = cmd_init();
    if (!cmd)
        return (NULL);
    while (node)
    {
        if (node->token == T_REDIRECT)
        {
            if (redirect(node, &cmd) < 0)
                return (free(cmd), NULL);
            ft_printf("REDIRECT: %s\n", node->value);
        }
        // if (node->token == T_LITERAL)
        // {
        //     // i = cmd_creator(&cmd, node, env);
        //     // if (i < 0)
        //     //     return (i);
            
        // }
        // if (node->token == T_PIPE)
        // {
        //     (*cmd)->next = cmd_init();
        //     if (!(*cmd)->next)
        //         return (-2);
        //     cmd = (*cmd)->next; 
        // }
        node = node->next;
    }
    return (cmd);
    ft_printf("%s", env->content);
}