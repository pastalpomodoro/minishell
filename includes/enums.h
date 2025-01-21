/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:19:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/21 11:45:18 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

//	TOKENS
typedef enum e_token
{
	T_REDIRECT,
	T_CMD,
	T_FILE,
	T_LITERAL,
	T_SIMPLE_QUOTE,
}	t_token;

#endif
