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
int			is_space(char c, char *space);
void free_env(t_env *env);
char *get_path(char *c, t_env *env);

// /*****************************/
// /*******  LST_CREATOR  *******/
// /*****************************/
t_env *env_creator(char **env);

char *replace_var(t_env *env, char *str);

#endif
