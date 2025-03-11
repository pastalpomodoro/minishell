/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:35 by rbaticle          #+#    #+#             */
/*   Updated: 2025/03/11 10:39:02 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"
# include <curses.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>

/*****************************/
/********   CMDS    **********/
/*****************************/
int			ft_echo(char **cmd);
int			ft_env(t_env *node);
int			ft_env_export(t_env *node);
int			ft_export(char *cmd, t_env **env);
int			ft_unset(char *cmd, t_env **env);
int			ft_pwd(void);
int			ft_cd(char *val, t_env *env);
void		ft_exit(int code, t_data *data, t_commande **cmd);

/*****************************/
/********   UTILS   **********/
/*****************************/
//			utils.c
void		free_double_tab(char **tab);
bool		ft_isspace(char c);
char		*ft_strjoin_char(char *s1, char ch);
char		*get_path(char *c, t_env *env, t_commande **cmd);
char		*strjoin_space(char *s1, char *s2);
//			lst_creator.c
void		free_cmd_node(t_commande **cmd);
void		free_cmd(t_commande **cmd, t_data *data);
//			variadic_strjoin.c
char		*variadic_strjoin(unsigned int argc, ...);

/*****************************/
/********    ENV    **********/
/*****************************/
//			env_creator.c
void		free_env(t_env *env);
int			env_add_last(t_env **env, t_env *to_add);
t_env		*env_creator(char **env);
t_env		*init_env(char *value);
//			replace_var.c
char		*replace_vars(t_env *env, char *str);
//			replace_var_utils.c
char		*handle_regular_char(char *res, char **line);
//			search_env.c
char		*search_env(t_env *env, char *str);
int			is_valid_input(char c, int first);

/*****************************/
/********   TOKENS    ********/
/*****************************/
//			tokenize.c
void		get_tokens(t_data *data);
//			check_spaces.c
char		*check_insert_spaces(char *line);
bool		inside_quotes(char *line, int *i);
//			insert_spaces.c
char		*insert_spaces(char *op, char *line_init, int *i);
//			delete_useless.c
char		*delete_useless(char *line);
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
//			get_wildcard.c
char		*get_wildcard(char *value);

/*****************************/
/******** LST_CREATOR ********/
/*****************************/
//          lst_creator.c
t_commande	*cmd_init(void);
//			lst_redir.c
int			redirect(t_tkn_lst *node, t_commande **cmd);
//			lst_cmd.c
int			cmd_creator(t_tkn_lst *node, t_commande **cmd, t_env *env);
//			lst_creator_utils.c
int			is_cmd(t_commande **cmd, t_tkn_lst *node, t_env *env, int *i);
int			is_redir(t_commande **cmd, t_tkn_lst **node);
int			is_parentesys(t_commande **cmd, t_tkn_lst *node);
int			is_and_or(t_commande **cmd, t_tkn_lst *node, int *i);
int			is_pipe(t_commande **cmd, t_tkn_lst *next, t_tkn_lst *node, int *i);
//			lst_creator.c
t_commande	*creator(t_tkn_lst *node, t_env *env);

/*****************************/
/********* EXECUTION *********/
/*****************************/
//			execution.c
int			exec_manage(t_commande *cmd, t_data *data, char **env);
int			and_or_exec(t_commande *cmd, t_data data, char **env, int p);

/*****************************/
/*********    SIG    *********/
/*****************************/
//			signals.c
void		init_signal(void);
void		init_signal_in_cmd(void);

#endif
