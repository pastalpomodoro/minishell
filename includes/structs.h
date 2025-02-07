/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:20:20 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/03 10:35:35 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "enums.h"

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_commande
{
	int					exit_code;
	int					infile;
	int					fd_out;
	int					outfile_type;//if 1==> , if 2==>>
	char				*outfile;
	char				**cmd;
	char				*path;
	struct s_commande	*next;
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

typedef struct s_data
{
	char		*line;
	t_tkn_lst	*lst;
	t_env		*env;
}	t_data;

#endif
