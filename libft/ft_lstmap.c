/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:18:08 by rbaticle          #+#    #+#             */
/*   Updated: 2024/10/03 10:26:29 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del) (void *))
{
	t_list	*new_lst;
	t_list	*e;

	new_lst = 0;
	if (!f || !del)
		return (0);
	while (lst)
	{
		e = ft_lstnew(f(lst->content));
		if (!e)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		ft_lstadd_back(&new_lst, e);
		lst = lst->next;
	}
	return (new_lst);
}
