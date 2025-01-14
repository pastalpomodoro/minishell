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
	T_AND,
	T_OR,
	T_PIPE,
	T_GREAT,
	T_LESS,
	T_CMD,
	T_O_PAR,
	T_C_PAR,
	T_DLESS,
	T_DGREAT,
	T_EXPORT
}	t_token;

#endif
