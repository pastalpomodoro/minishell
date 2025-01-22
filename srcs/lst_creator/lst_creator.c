/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:24:32 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 11:19:33 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int hard_in(t_tkn_lst *node)
{
    char *line;
    int *pipe_fd;

    if (ft_strlen(node->value) == 0 && node->next == NULL)
        return (ft_printf("minishell: syntax error near unexpected token `newline'\n"), -1);
    pipe_fd = malloc(sizeof(int) * 2);
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

int easy_in(t_tkn_lst *node, t_env *env)
{
    int fd;
    char *line;
    t_tkn_lst *next;

    next = node->next;
    if (node->token == T_LITERAL)
    {
        line = replace_var(env, node->value);
        if (!line)
            return (-2);
    }
    else
        line = node->value;
    fd = open(line, O_RDONLY);
    if (ft_strlen(node->value) == 0 && node->next == NULL)
        return (ft_printf("minishell: syntax error near unexpected token `newline'\n"), -1);
    if (ft_strlen(node->value) == 0)
        return (ft_printf("minishell: syntax error near unexpected token `%s'", next->value), -1);
    if (fd < 0)
        ft_printf("minishell: %s: No such file or directory", line);
    return (fd);
}
int out(t_tkn_lst *node, t_env *env, int type)
{
    int fd;
    char *file;
    t_tkn_lst *next;

    next = node->next;
    if (node->token == T_LITERAL)
    {
        file = replace_var(env, node->value);
        if (!file)
            return (-2);
    }
    else if (node->token == T_SIMPLE_QUOTE)
        file = node->value;
    if (ft_strlen(node->value) == 0 && node->next == NULL)
        return (ft_printf("minishell: syntax error near unexpected token `newline'\n"), -1);
    if (ft_strlen(node->value) == 0)
        return (ft_printf("minishell: syntax error near unexpected token `%s'", next->value), -1);
    if (type == 1)//>
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
    if (type == 2)//>>
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND);
    if (fd < 0)
        ft_printf("bash: %s: Permission denied", node->value);
    return (fd);
}
void redirect(t_tkn_lst *node, t_env *env)
{
    t_tkn_lst *next;
    int fd;

    next = node->next;
    if (ft_strcmp(node->value, "<<") == 0)
        fd = hard_in(next);
    else if (ft_strcmp(node->value, "<") == 0)
        fd = easy_in(next, env);
    else if (ft_strcmp(node->value, ">") == 0)
        fd = out(next, env, 1);
    else if (ft_strcmp(node->value, ">>") == 0)
        fd = out(next, env, 2);

}

void creator(t_tkn_lst *node, t_env *env)
{
    int i;

    i = 0;
    while (node)
    {
        if (node->token == T_CMD)
            ft_printf("FAIRE LA COMMANDE\n");
        else if (node->token == T_REDIRECT)
            redirect(node, env);
            //faire une foction qui check le type de redirection <<, <, >>, >, |, e qui apelle une fonction qui fais que quil faut faire en fonction de la redirection
        node = node->next;
    }
}
// t_node	*lst_creator(char *input, char **env)
// {
// 	t_node		*prince;
// 	t_tkn_lst	*lst_in;
// 	t_tkn_lst	*node_out;

// 	lst_in = fill_branche(input, '<');
// 	prince = init_prince();
// 	if (!prince)
// 		return (free_branche(lst_in), NULL);
// 	find_outfile(&node_out, input);
// 	end_struct(lst_in, node_out, prince);
// 	if (fill_cmd(prince, env, input) == 0)
// 		return (free_branche(lst_in), free_out(node_out), NULL);
// 	return (prince);
// }