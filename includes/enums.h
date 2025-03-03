/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:19:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/11 16:46:00 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

//	TOKENS
typedef enum e_token
{
	T_AND_OR,
	T_PIPE,
	T_REDIRECT,
	T_LITERAL,
	T_NULL,
	T_OPAR,
	T_CPAR,
	ERROR
}	t_token;

#endif
