/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:20:20 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/14 17:34:22 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "enums.h"

typedef struct s_commande
{
	char	*infile;
	char	*outfile;
	char	*cmd;
	char	*util;

}	t_commande;

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	char			*val;
	t_token			type;
}	t_node;

typedef struct s_tkn_lst
{
	t_token				token;
	char				*value;
	struct s_tkn_lst	*next;
	struct s_tkn_lst	*prev;
}	t_tkn_lst;

#endif
