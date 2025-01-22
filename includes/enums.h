/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:19:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/14 17:46:03 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_token
{
	T_REDIRECT,
	T_CMD,
	T_PIPE,
	T_LITERAL,
	T_SIMPLE_QUOTE,
}	t_token;

#endif
