/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:35:59 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/20 22:28:20 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tkn_lst	*new_token(char *val, t_token type)
{
	t_tkn_lst	*t;

	t = malloc(sizeof(t_tkn_lst));
	if (t == NULL)
		return (NULL);
	t->value = val;
	t->token = type;
	t->next = NULL;
	t->prev = NULL;
	return (t);
}

t_tkn_lst	*get_first_tkn(t_tkn_lst *lst)
{
	t_tkn_lst	*tmp;

	if (lst == NULL)
		return (lst);
	tmp = lst;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	return (tmp);
}

t_tkn_lst	*get_last_tkn(t_tkn_lst *lst)
{
	t_tkn_lst	*tmp;

	if (lst == NULL)
		return (lst);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	tkn_add_back(t_tkn_lst **lst, t_tkn_lst *token)
{
	t_tkn_lst	*tmp;

	if (token == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = token;
		return ;
	}
	tmp = get_last_tkn(*lst);
	tmp->next = token;
	token->prev = tmp;
}

void	tkn_lst_clear(t_tkn_lst **lst)
{
	t_tkn_lst	*tmp;

	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
