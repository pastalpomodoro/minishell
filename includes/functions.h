/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:35 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/17 11:13:20 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

/***************************/
/********   UTILS   ********/
/***************************/
// void		free_double_tab(char **tab);
// void		free_prince(t_node *prince);
// t_node		*init_prince(void);
// t_tkn_lst	*my_new_node(char *val);
// void		free_branche(t_tkn_lst *node);
// void		my_node_addfront_branche(t_tkn_lst **node, t_tkn_lst *new);
// char		**ft_split2(char const *s, char *c);

// /*****************************/
// /*******  LST_CREATOR  *******/
// /*****************************/
int			is_space(char c, char *space);
// char		*get_path(char *c, char **env);
// t_tkn_lst	*fill_branche(char *input, char c);
// int         find_outfile(t_tkn_lst **node_out, char *input);
// int			fill_cmd(t_node *prince, char **env, char *input);
// t_node		*lst_creator(char *input, char **env);
// void pipe_split(char *input, char **env);


void chepas(char *input);

#endif
