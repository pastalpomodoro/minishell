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


int fill_branches(t_tkn_lst **lst_in, char *input)
{
    lst_in[0] = fill_branche(input, '<');
}

int parsing(char *input, char **env)
{
    t_node *prince;
    t_tkn_lst *lst_in;
    t_tkn_lst *temp;

    
    prince = init_prince();
    if (!prince)
        return (free_branche(lst_in), 0);
    if (add_last_redir(input, '<') == 0)
        return (free_branche(lst_in), free(prince), 0);
    if (fill_cmd(prince, env, input) == 0)
        return (free_branche(lst_in), 0);
    int i =-1;
    while (i++, prince->cmd[i])
        ft_printf("CMD: %s\n", prince->cmd[i]);
    ft_printf("PATH: %s\n\n", prince->path);
    temp = lst_in;
    while (temp)
    {
        ft_printf("<<: %s\n", temp->value);
        temp = temp->next;
    }
    free_branche(lst_in);
    free_prince(prince);
    return (1);
}
