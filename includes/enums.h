/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:19:14 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 13:37:32 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_token
{
	T_AND,
	T_OR,
	T_PIPE,
	T_GREAT,
	T_LESS,
	T_UNSET,
	T_ECHO,
	T_PWD,
	T_ENV,
	T_HISTORY,
	T_CD,
	T_LAST_RETURN,
	T_O_PAR,
	T_C_PAR,
	T_DLESS,
	T_DGREAT,
	T_EXPORT,
	T_EXIT,
	ERROR
}	t_token;

#endif
