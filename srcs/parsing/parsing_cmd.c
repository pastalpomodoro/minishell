#include"../../includes/minishell.h"

int skip_redir(char *input, int i)
{
    i++;
    if (input[i] == '>' || input[i] == '<')
        i++;
    while (is_space(input[i], "\t\n\v\f\r ") == 0 && input[i])
        i++;
    while (is_space(input[i], "\t\n\v\f\r ") && input[i])
        i++;
    return (i);
}
char *take_cmd(char *input)
{
    int i;
    int start;
    char *cmd;

    i = 0;
    while (input[i])
    {
        if (input[i] == '>' || input[i] == '<')
            i = skip_redir(input, i);
        else if (is_space(input[i], "\t\n\v\f\r ") == 0)
            i++;
        else
        {
            start = i;
            while (input[i] && input[i] != '>' && input[i] != '<' )
                i++;
            cmd = ft_substr(input, start, i - start);
            if (!cmd)
                return (perror("Erreur malloc"), NULL);
            return (cmd);
        }
    }
    return (NULL);
}

void    free_prince(t_node *prince)
{
    if (prince->cmd != NULL)
        free_double_tab(prince->cmd);
    if (prince->path != NULL)
        free(prince->path);
    free(prince);
}

int fill_cmd(t_node *prince, char **env, char *input)
{
    char *temp;
    
    temp = take_cmd(input);
    if (!temp)
        return (free_prince(prince), 0);
    prince->cmd = ft_split2(temp, "\t\n\v\f\r ");
    if (!prince->cmd)
        return (free(temp), free_prince(prince), 0);
    prince->path = get_path(prince->cmd[0], env);
    if (prince->path)
        prince->type = T_CMD;
    else if (ft_strcmp("export", prince->cmd[0]) == 0)
        prince->type = T_EXPORT;
    else
        return (free(temp), free_prince(prince), ft_printf("No path found\n"), 0);
    return (free(temp), 1);
}