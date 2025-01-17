/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:08:13 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 11:09:15 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

t_tkn_lst	*my_new_node(char *val)
{
	t_tkn_lst	*new;

	new = malloc(sizeof(t_tkn_lst));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->value = val;
	return (new);
}

void	my_node_addfront_branche(t_tkn_lst **node, t_tkn_lst *new)
{
	t_tkn_lst	*temp;

	if (*node == NULL)
		*node = new;
	else
	{
		temp = *node;
		new->next = *node;
		*node = new;
		temp->prev = *node;
	}
}

void	free_branche(t_tkn_lst *node)
{
	t_tkn_lst	*temp;

	while (node)
	{
		temp = node->next;
		if (node->value)
			free(node->value);
		free(node);
		node = temp;
	}
}

t_node	*init_prince(void)
{
	t_node	*prince;

	prince = malloc(sizeof(t_node));
	if (!prince)
		return (NULL);
	prince->cmd = NULL;
	prince->left = NULL;
	prince->next = NULL;
	prince->path = NULL;
	prince->right = NULL;
	return (prince);
}

t_tkn_lst	*my_node_addback_branche(t_tkn_lst *lst, t_tkn_lst *new)
{
	t_tkn_lst	*temp;

	if (lst)
	{
		while (lst->prev != NULL)
			lst = lst->prev;
		temp = lst;
		lst->prev = new;
		new->next = temp;
	}
	else
		lst = new;
	return (lst);
}
