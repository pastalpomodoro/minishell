/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:35 by rbaticle          #+#    #+#             */
/*   Updated: 2025/02/03 11:44:49 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"
# include <curses.h>
# include <stdbool.h>

/*****************************/
/********   UTILS   **********/
/*****************************/
//			utils.c
void		free_double_tab(char **tab);
bool		ft_isspace(char c);
char		*ft_strjoin_char(char *s1, char ch);
char		*get_path(char *c, t_env *env);
//			variadic_strjoin.c
char		*variadic_strjoin(unsigned int argc, ...);

/*****************************/
/********    ENV    **********/
/*****************************/
//			env_creator.c
void		free_env(t_env *env);
t_env		*env_creator(char **env);
//			replace_var.c
char		*replace_vars(t_env *env, char *str);
//			search_env.c
char		*search_env(t_env *env, char *str);

/*****************************/
/********   PARSING   ********/
/*****************************/

/*****************************/
/********   TOKENS    ********/
/*****************************/
//			tokenize.c
t_tkn_lst	*get_tokens(t_data *data);
//			check_spaces.c
char		*check_insert_spaces(char *line);
bool		inside_quotes(char *line, int *i);
//			insert_spaces.c
char		*insert_spaces(char *op, char *line_init, int *i);
//			split_token.c
int			split_token(t_data *data, int *i);
//			add_token.c
int			add_token(t_data *data, int size, int *i);
//			tkn_lst.c
t_tkn_lst	*new_token(char *val, t_token type);
t_tkn_lst	*get_first_tkn(t_tkn_lst *lst);
t_tkn_lst	*get_last_tkn(t_tkn_lst *lst);
void		tkn_add_back(t_tkn_lst **lst, t_tkn_lst *token);
void		tkn_lst_clear(t_tkn_lst **lst);

/*****************************/
/******** LST_CREATOR ********/
/*****************************/
//          lst_redir.c
int redirect(t_tkn_lst *node, t_commande **cmd);
//          lst_creator.c
t_commande *creator(t_tkn_lst *node, t_env *env);

#endif
