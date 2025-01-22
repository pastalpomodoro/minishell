/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:35 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/22 16:11:50 by rbaticle         ###   ########.fr       */
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
void		free_double_tab(char **tab);
//			variadic_strjoin.c
char		*variadic_strjoin(unsigned int argc, ...);

/*****************************/
/********   PARSING   ********/
/*****************************/

/*****************************/
/********   TOKENS    ********/
/*****************************/
//			tokenize.c
t_tkn_lst	*get_tokens(char *line);
//			check_spaces.c
char		*check_insert_spaces(char *line);
bool		inside_quotes(char *line, int *i);
//			insert_spaces.c
char		*insert_spaces(char *op, char *line_init, int *i);
//			split_token.c
int			split_token(char *line, t_tkn_lst **lst, int *i);
//			add_token.c
int			add_token(char *line, int size, t_tkn_lst **lst, int *i);
//			tkn_lst.c
t_tkn_lst	*new_token(char *val, t_token type);
t_tkn_lst	*get_first_tkn(t_tkn_lst *lst);
t_tkn_lst	*get_last_tkn(t_tkn_lst *lst);
void		tkn_add_back(t_tkn_lst **lst, t_tkn_lst *token);
void		tkn_lst_clear(t_tkn_lst **lst);

#endif
