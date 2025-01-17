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

void	end_struct(t_tkn_lst *lst_in, t_tkn_lst *node_out, t_node *prince)
{
	if (lst_in)
	{
		while (lst_in->prev)
			lst_in = lst_in->prev;
	}
	prince->left = lst_in;
	prince->right = node_out;
}

void	free_out(t_tkn_lst *node_out)
{
	if (node_out)
	{
		if (node_out->value)
			free(node_out->value);
		free(node_out);
	}
}

t_node	*lst_creator(char *input, char **env)
{
	t_node		*prince;
	t_tkn_lst	*lst_in;
	t_tkn_lst	*node_out;

	lst_in = fill_branche(input, '<');
	prince = init_prince();
	if (!prince)
		return (free_branche(lst_in), NULL);
	find_outfile(&node_out, input);
	end_struct(lst_in, node_out, prince);
	if (fill_cmd(prince, env, input) == 0)
		return (free_branche(lst_in), free_out(node_out), NULL);
	return (prince);
}
	// free_out(node_out);
	// free_branche(lst_in);
	// free_prince(prince);

	// i = -1;
	// while (i++, prince->cmd[i])
	// 	ft_printf("CMD: %s TKN: %d\n", prince->cmd[i], prince->type);
	// ft_printf("PATH: %s\n\n", prince->path);
	// temp = prince->left;
	// if (temp)
	// 	ft_printf("LEFT: %s, tkn: %d\n", temp->value, temp->token);
	// else
	// 	ft_printf("LEFT: NULL\n");
	// temp = prince->right;
	// if (temp)
	// 	ft_printf("RIGHT: %s, tkn: %d\n\n", temp->value, temp->token);
	// else
	// 	ft_printf("RIGHT: NULL\n\n");
	// temp = lst_in;
	// // find_outfile(node_out, input);
	// while (temp)
	// {
	// 	ft_printf("<<: %s,  %d, LEN: %d\n", temp->value, temp->token, ft_strlen(temp->value));
	// 	temp = temp->prev;
	// }