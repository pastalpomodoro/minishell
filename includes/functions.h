/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:35 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/10 19:22:32 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

/***************************/
/********   UTILS   ********/
/***************************/
void	free_double_tab(char **tab);
void    free_prince(t_node *prince);
t_node *init_prince(void);
t_tkn_lst  *my_new_node(char *val);
void free_branche(t_tkn_lst *node);
t_tkn_lst *find_last_branche(t_tkn_lst *lst);
void my_node_addfront_branche(t_tkn_lst **node, t_tkn_lst *new);
char	**ft_split2(char const *s, char *c);

/*****************************/
/********   PARSING   ********/
/*****************************/
int     is_space(char c, char *space);
char	*get_path(char *c, char **env);
t_tkn_lst     *fill_branche(char *input, char c);
int fill_cmd(t_node *prince, char **env, char *input);
char *find_last_redir(char *input, char c);
int     parsing(char *input, char **env);

#endif
