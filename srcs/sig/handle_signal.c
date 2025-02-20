/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:39:36 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/19 14:01:17 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal(int sig, siginfo_t *info, void *content)
{
	t_data	*data;

	(void) info;
	data = (t_data *) content;
	(void) data;
	if (sig == SIGINT)
		ft_printf("CTRL+C\n");
	if (sig == SIGQUIT)
		ft_printf("CTRL+\\\n");
}
