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
    //il faut while jusqua la ligne 78 et apres dans le while faire un strjoin ou j ajoute tout les T_literal et T_SIMPLE_QUOTE
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
int redirect(t_tkn_lst *node, t_env *env, t_commande **cmd)
{
    t_tkn_lst *next;
    int i;
    int fd;

    i = 0;
    next = node->next;
    if (i++, ft_strcmp(node->value, "<<") == 0)
        fd = hard_in(next);
    else if (i++, ft_strcmp(node->value, "<") == 0)
        fd = easy_in(next, env);
    else if (i++, ft_strcmp(node->value, ">") == 0)
        fd = out(next, env, 1);
    else if (i++, ft_strcmp(node->value, ">>") == 0)
        fd = out(next, env, 2);
    if (fd < 0)
        return (fd);
    if (i > 3)
        (*cmd)->infile = fd;
    else if (i > 2)
        (*cmd)->outfile = fd;    
    return (fd);
}
t_commande *cmd_init()
{
    t_commande *cmd;

    cmd = malloc(sizeof(cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    cmd->path = NULL;
    cmd->next = NULL;
    cmd->infile = -3;
    cmd->outfile = -3;
}
int cmd_creator(t_commande **cmd, t_tkn_lst *node, t_env *env)
{
    int size;
    int i;
    t_tkn_lst *temp;

    size = -1;
    cmd[0]->path = get_path(node->value, env);
    if (!cmd[0]->path)
        return (-1);
    temp = node;
    while (size++, (temp->token == T_LITERAL || temp->token == T_SIMPLE_QUOTE) && temp)
        temp = temp->token;
    cmd[0]->cmd = malloc(sizeof(t_commande *) * size);
    if (!cmd[0]->cmd)
        return (-1);
    i = -1;
    while (i++, (node->token == T_LITERAL || node->token == T_SIMPLE_QUOTE) && node)
    {
        if (node->token == T_LITERAL)
        {
            cmd[0]->cmd[i] = replace_var(env, node->value);
            if (!cmd[0]->cmd[i])
                return (-1);
        }
        else if (node->token == T_SIMPLE_QUOTE)
            cmd[0]->cmd[i] = node->value;
        node = node->next;
    }
    return (1);
}
// fonction qui return -2 sy probleme de malloc et moins 1 sy erreur comme : Erreur de fd, Erreur de path
int creator(t_tkn_lst *node, t_env *env, t_commande **cmd)
{
    t_commande *init;
    int i;

    (*cmd) = cmd_init();
    if (!(*cmd))
        return (NULL);
    while (node)
    {
        if (node->token == T_CMD)
        {
            i = cmd_creator(&cmd, node, env);
            if (i <-0)
                return (i);
        }
        else if (node->token == T_REDIRECT)
        {
            i = redirect(node, env, &cmd);
            if (i < 0)
                return (i);
        }  
        else if (node->token == T_PIPE)
        {
            (*cmd)->next = cmd_init();
            if (!(*cmd)->next)
                return (-2);
            cmd = (*cmd)->next; 
        }
        node = node->next;
    }
    return (init);
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

//cmd echo salutsalut