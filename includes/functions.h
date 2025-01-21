/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:35 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/21 15:58:06 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

/*****************************/
/********   UTILS   **********/
/*****************************/
void		free_double_tab(char **tab);
//			variadic_strjoin.c
char		*variadic_strjoin(unsigned int argc, ...);

/*****************************/
/********   PARSING   ********/
/*****************************/
int			picking(char *input);

/*****************************/
/********   TOKENS    ********/
/*****************************/
//			check_spaces.c
void		check_insert_spaces(char *line);
bool		inside_quotes(char **line);
//			insert_spaces.c
char		*insert_spaces(char *line, char *op, char *line_init);
//			split_token.c
int			split_token(char **line, t_tkn_lst **lst);
//			add_token.c
int			add_token(char **line, int size, t_tkn_lst **lst);
//			tkn_lst.c
t_tkn_lst	*new_token(char *val, t_token type);
t_tkn_lst	*get_first_tkn(t_tkn_lst *lst);
t_tkn_lst	*get_last_tkn(t_tkn_lst *lst);
void		tkn_add_back(t_tkn_lst **lst, t_tkn_lst *token);
void		tkn_lst_clear(t_tkn_lst **lst);

#endif
