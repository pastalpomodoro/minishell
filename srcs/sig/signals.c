/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:39:36 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/11 19:36:05 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error_value;

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_error_value = 130;
	}
}

static void	handle_signal_in_cmd(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_error_value = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_printf("Quit (Core dumped)\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_error_value = 131;
	}
}

void	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
}

void	init_signal_in_cmd(void)
{
	signal(SIGQUIT, handle_signal_in_cmd);
	signal(SIGINT, handle_signal_in_cmd);
}
