/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:20:20 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 11:14:01 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "enums.h"

typedef struct s_env
{
	char *content;
	struct s_env *next;
}				t_env;

typedef struct s_commande
{
	int	infile;
	int	outfile;
	char	*path;
	char	**cmd;
	struct s_commande *next;

}	t_commande;

typedef struct s_tkn_lst
{
	t_token				token;
	char				*value;
	struct s_tkn_lst	*next;
	struct s_tkn_lst	*prev;
}	t_tkn_lst;

typedef struct s_node
{
	struct s_node	*next;
	t_tkn_lst		*right;
	t_tkn_lst		*left;
	int 			infile;
	int 			outfile;
	t_token			type;
	char			*path;
	char			**cmd;
}	t_node;

#endif
