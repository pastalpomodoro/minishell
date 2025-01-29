/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:20:54 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/29 14:24:16 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	init_data(char *line, char **env)
{
	t_data	data;

	data.line = line;
	data.lst = NULL;
	data.env = env_creator(env);
	return (data);
}
