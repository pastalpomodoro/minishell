/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:01:39 by rbaticle          #+#    #+#             */
/*   Updated: 2024/10/03 10:39:26 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstcpy;

	if (*lst)
	{
		lstcpy = *lst;
		while (lstcpy)
		{
			if (!lstcpy->next)
			{
				lstcpy->next = new;
				return ;
			}
			lstcpy = lstcpy->next;
		}
	}
	else
		*lst = new;
}
