/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:24:32 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/10 19:25:16 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fonction qui va permettre de prendre tout ce qui est affiche sur le minishell
// et mettre chaque mot dans un double tableau
// exemple:  grep je > outfile.txt
//          [[grep], [je], [>], [outfile.txt], NULL]

int take_index_last_right(t_tkn_lst **node_out, char *input)
{
    int i;
    int save;

    i = 0;
    save = ft_strlen(input);
    while (input[i])
    {
        if (input[i] == '>' && input[i + 1] == '>')
        {
            node_out[0]->token = T_DGREAT;
            i+=2;
            save = i;
        }
        else if (input[i] == '>')
        {
            node_out[0]->token = T_GREAT;
            i++;
            save = i;
        }
        else 
            i++;
    }
    return (save);
}
int find_outfile(t_tkn_lst **node_out, char *input)
{
    int i;
    int start;
    char *file;

    node_out[0] = my_new_node(NULL);
    if (!node_out)
        return (ft_printf("Erreur malloc node_out find_outfile"), 0);
    i = take_index_last_right(node_out, input);
    while (is_space(input[i], "\t\n\v\f\r ") == 0 && input[i])
        i++;
    start = i;
    while (is_space(input[i], "\t\n\v\f\r ") && input[i])
        i++;
    file = ft_substr(input, start, i - start);
    if (!file)
        return (ft_printf("Malloc error in find outfile"), 0);
    if (ft_strlen(file) != 0)
        node_out[0]->value = file;
    else
    {
        free(file);
        free(node_out[0]);
        node_out[0] = NULL;
    }
    return (1);
}
void end_struct(t_tkn_lst *lst_in, t_tkn_lst *node_out, t_node *prince)
{
    if (lst_in)
    {
        while (lst_in->prev)
            lst_in = lst_in->prev;
    }
    prince->left = lst_in;
    prince->right = node_out;
}
void free_out(t_tkn_lst *node_out)
{
    if (node_out)
    {
        if (node_out->value)
            free(node_out->value);
        free(node_out);
    }
}
int parsing(char *input, char **env)
{
    t_node *prince;
    t_tkn_lst *lst_in;
    t_tkn_lst *temp;
    t_tkn_lst *node_out;

    lst_in = fill_branche(input, '<');
    prince = init_prince();
    if (!prince)
        return (free_branche(lst_in), 0);
    if (fill_cmd(prince, env, input) == 0)
        return (free_branche(lst_in), 0);
    int i =-1;
    while (i++, prince->cmd[i])
        ft_printf("CMD: %s TKN: %d\n", prince->cmd[i], prince->type);
    ft_printf("PATH: %s\n\n", prince->path);
    // node_out = NULL;
    find_outfile(&node_out, input);
    end_struct(lst_in, node_out, prince);
    temp = prince->left;
    if (temp)
        ft_printf("LEFT: %s, tkn: %d\n", temp->value, temp->token);
    else 
        ft_printf("LEFT: NULL\n");
    temp = prince->right;
    if (temp)
        ft_printf("RIGHT: %s, tkn: %d\n\n", temp->value, temp->token);
    else
        ft_printf("RIGHT: NULL\n\n");
    temp = lst_in;
    // find_outfile(node_out, input);
    while (temp)
    {
        ft_printf("<<: %s,  %d, LEN: %d\n", temp->value, temp->token, ft_strlen(temp->value));
        temp = temp->prev;
    }

    free_out(node_out);
    free_branche(lst_in);
    free_prince(prince);
    return (1);
    ft_printf("\n%s\n", env[0]);
}
