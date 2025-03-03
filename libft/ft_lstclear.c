/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:10:08 by rbaticle          #+#    #+#             */
/*   Updated: 2024/10/03 10:44:49 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*e;
	t_list	*e2;

	e = *lst;
	while (e)
	{
		e2 = e->next;
		del(e->content);
		free(e);
		e = e2;
	}
	*lst = 0;
}
